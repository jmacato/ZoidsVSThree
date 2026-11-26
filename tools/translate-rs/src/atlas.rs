use crate::geometry::{Attribute, Geometry, Primitive, Vertex, GX_VA_POS, GX_VA_TEX0};
use crate::gx::Image;
use crate::hsd::{Archive, HEADER};
use crate::textures::{changed_blocks, merge};
use crate::{disc, Files};
use anyhow::{anyhow, bail, ensure, Context, Result};
use serde::Deserialize;
use std::cmp::Reverse;
use std::collections::{BTreeMap, BTreeSet, HashMap};
use std::path::{Path, PathBuf};

const AVENIR: &str = "/System/Library/Fonts/Avenir Next Condensed.ttc";
const LATIN_ROWS: [(usize, &str); 4] = [
    (7, "ABCDE"),
    (8, "FGHIJKLM"),
    (9, "NOPQRST"),
    (10, "UVWXYZ"),
];
const GLYPH_HEIGHT: usize = 12;
const PRECISION_BITS: u32 = 22;

#[derive(Clone, Debug, Deserialize)]
pub struct Word {
    pub pobj: String,
    pub en: String,
    pub font: Option<String>,
    pub height: Option<usize>,
    pub glyphs: Option<bool>,
    pub widen: Option<f64>,
    pub anchor: Option<String>,
}

#[derive(Clone, Debug, Deserialize)]
pub struct Spec {
    pub archive: String,
    pub atlas: String,
    pub free: Vec<[i64; 4]>,
    pub words: Vec<Word>,
}

/// One distinct word image and the atlas rectangle (x0, y0, x1, y1) it was drawn into.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Placement {
    pub text: String,
    pub font: String,
    pub height: usize,
    pub glyphs: bool,
    pub region: [usize; 4],
}

type WordKey = (String, String, usize, bool);
type Quad = Vec<Vertex>;
type ArrayRef = (Option<usize>, usize);

#[derive(Default)]
struct Pool {
    free: BTreeMap<Option<usize>, Vec<usize>>,
    values: BTreeMap<Option<usize>, HashMap<Vec<u64>, usize>>,
}

pub fn words_path() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR")).join("../../translation/atlas_text.json")
}

fn font_face(font: &str) -> Result<(&'static str, u32)> {
    match font {
        "thin" => Ok((AVENIR, 2)),
        "heavy" => Ok((AVENIR, 8)),
        other => bail!("unknown font {other:?}"),
    }
}

pub fn scene_offset(data: &[u8]) -> Result<usize> {
    let archive_word = |at: usize| -> Result<usize> {
        let raw = data
            .get(at..at + 4)
            .ok_or_else(|| anyhow!("archive is cut short at {at:#x}"))?;
        Ok(u32::from_be_bytes([raw[0], raw[1], raw[2], raw[3]]) as usize)
    };
    let data_size = archive_word(4)?;
    let reloc_count = archive_word(8)?;
    archive_word(HEADER + data_size + reloc_count * 4)
}

fn all_pobjs(geometry: &Geometry, scene: usize) -> Result<Vec<(usize, Vec<usize>)>> {
    let mut found = Vec::new();
    for (_, root) in geometry.models(scene)? {
        for (_, joint) in geometry.joints(Some(root), &[])? {
            for dobj in geometry.dobjs(joint)? {
                let images = geometry.images(dobj)?;
                for pobj in geometry.pobjs(dobj)? {
                    found.push((pobj, images.clone()));
                }
            }
        }
    }
    Ok(found)
}

fn quads(prims: &[(Primitive, Vec<Vertex>)]) -> Vec<Quad> {
    let mut found = Vec::new();
    for (kind, verts) in prims {
        match kind {
            Primitive::Quads => {
                found.extend(verts.as_chunks::<4>().0.iter().map(|quad| quad.to_vec()))
            }
            Primitive::Strip if verts.len() == 4 => found.push(vec![
                verts[0].clone(),
                verts[1].clone(),
                verts[3].clone(),
                verts[2].clone(),
            ]),
            _ => {}
        }
    }
    found
}

fn pixel(x: i32) -> i32 {
    (x + 32) >> 6
}

struct Shaped {
    index: u32,
    x_offset: i32,
    y_offset: i32,
    x_advance: i32,
    y_advance: i32,
}

/// The glyph run raqm hands PIL: HarfBuzz shaping with FreeType's unhinted advances, in 26.6.
fn shape(face: &freetype::Face, path: &str, index: u32, text: &str) -> Result<Vec<Shaped>> {
    let bytes = std::fs::read(path).with_context(|| format!("read {path}"))?;
    let shaper = rustybuzz::Face::from_slice(&bytes, index)
        .ok_or_else(|| anyhow!("{path}: face {index} cannot be shaped"))?;
    let metrics = face
        .size_metrics()
        .ok_or_else(|| anyhow!("{path}: no size metrics"))?;
    let upem = i64::from(face.em_size());
    ensure!(upem > 0, "{path}: no em size");
    let (x_scale, y_scale): (i64, i64) = (metrics.x_scale, metrics.y_scale);
    let x_mult = (((x_scale * upem + (1 << 15)) >> 16) << 16) / upem;
    let y_mult = (((y_scale * upem + (1 << 15)) >> 16) << 16) / upem;
    let em = |value: i64, mult: i64| ((value * mult + 32768) >> 16) as i32;
    let mut buffer = rustybuzz::UnicodeBuffer::new();
    buffer.push_str(text);
    buffer.guess_segment_properties();
    let run = rustybuzz::shape(&shaper, &[], buffer);
    let mut shaped = Vec::new();
    for (info, position) in run.glyph_infos().iter().zip(run.glyph_positions()) {
        let glyph = u16::try_from(info.glyph_id)?;
        let units = i64::from(
            shaper
                .glyph_hor_advance(rustybuzz::ttf_parser::GlyphId(glyph))
                .unwrap_or(0),
        );
        let advance = (((units * x_scale + 32) / 64 + (1 << 9)) >> 10) as i32;
        let kerning = i64::from(position.x_advance) - units;
        shaped.push(Shaped {
            index: info.glyph_id,
            x_offset: em(i64::from(position.x_offset), x_mult),
            y_offset: em(i64::from(position.y_offset), y_mult),
            x_advance: advance + em(kerning, x_mult),
            y_advance: em(i64::from(position.y_advance), y_mult),
        });
    }
    Ok(shaped)
}

/// PIL's `ImageDraw.text` of white text on an 8-bit mask with a 4 pixel margin around `getbbox`.
fn draw_text(text: &str, font: &str, size: u32) -> Result<(Vec<u8>, usize, usize)> {
    use freetype::face::LoadFlag;
    let (path, index) = font_face(font)?;
    let library = freetype::Library::init()?;
    let face = library.new_face(path, index as isize)?;
    face.set_pixel_sizes(0, size)?;
    let run = shape(&face, path, index, text)?;
    let (mut position, mut x_min, mut x_max, mut y_min, mut y_max) = (0, 0, 0, 0, 0);
    for glyph in &run {
        let px = pixel(position + glyph.x_offset);
        let py = pixel(glyph.y_offset);
        position += glyph.x_advance;
        x_max = x_max.max(pixel(position));
        face.load_glyph(glyph.index, LoadFlag::DEFAULT)?;
        let bbox = face
            .glyph()
            .get_glyph()?
            .get_cbox(freetype::ffi::FT_GLYPH_BBOX_PIXELS);
        x_max = x_max.max(bbox.xMax as i32 + px);
        x_min = x_min.min(bbox.xMin as i32 + px);
        y_max = y_max.max(bbox.yMax as i32 + py);
        y_min = y_min.min(bbox.yMin as i32 + py);
    }
    let width = usize::try_from(x_max - x_min)?;
    let height = usize::try_from(y_max - y_min)?;
    let mut ink = vec![0u8; width * height];
    let (mut x, mut y, mut left, mut top) = (0, 0, 0, 0);
    for glyph in &run {
        face.load_glyph(glyph.index, LoadFlag::DEFAULT | LoadFlag::RENDER)?;
        let slot = face.glyph();
        top = top.max(slot.bitmap_top() + pixel(y + glyph.y_offset));
        left = left.min(slot.bitmap_left() + pixel(x + glyph.x_offset));
        x += glyph.x_advance;
        y += glyph.y_advance;
    }
    let (mut x, mut y) = (-left * 64, -top * 64);
    for glyph in &run {
        face.load_glyph(glyph.index, LoadFlag::DEFAULT | LoadFlag::RENDER)?;
        let slot = face.glyph();
        let bitmap = slot.bitmap();
        let xx = pixel(x + glyph.x_offset) + slot.bitmap_left();
        let yy = -(pixel(y + glyph.y_offset) + slot.bitmap_top());
        if bitmap.rows() > 0 && bitmap.width() > 0 {
            ensure!(
                matches!(bitmap.pixel_mode()?, freetype::bitmap::PixelMode::Gray),
                "{text:?}: glyph bitmap is not 8-bit grey"
            );
            let pitch = usize::try_from(bitmap.pitch())?;
            let source = bitmap.buffer();
            for row in 0..bitmap.rows() {
                let ty = yy + row;
                if ty < 0 || ty as usize >= height {
                    continue;
                }
                for column in 0..bitmap.width() {
                    let tx = xx + column;
                    if tx < 0 || tx as usize >= width {
                        continue;
                    }
                    let alpha = u32::from(source[row as usize * pitch + column as usize]);
                    let target = &mut ink[ty as usize * width + tx as usize];
                    if alpha > 0 {
                        *target = if *target > 0 {
                            let blend = u32::from(*target) * (255 - alpha) + 128;
                            (alpha + (((blend >> 8) + blend) >> 8)).min(255) as u8
                        } else {
                            alpha as u8
                        };
                    }
                }
            }
        }
        x += glyph.x_advance;
        y += glyph.y_advance;
    }
    let (mask_width, mask_height) = (width + 8, height + 8);
    let mut mask = vec![0u8; mask_width * mask_height];
    for row in 0..height {
        let at = (row + 4) * mask_width + 4;
        mask[at..at + width].copy_from_slice(&ink[row * width..(row + 1) * width]);
    }
    Ok((mask, mask_width, mask_height))
}

fn lanczos(x: f64) -> f64 {
    let sinc = |x: f64| {
        if x == 0.0 {
            1.0
        } else {
            let x = x * std::f64::consts::PI;
            x.sin() / x
        }
    };
    if (-3.0..3.0).contains(&x) {
        sinc(x) * sinc(x / 3.0)
    } else {
        0.0
    }
}

/// Pillow's 8-bit resampling coefficients: first source index and fixed-point weights per output.
fn coefficients(in_size: usize, out_size: usize) -> Vec<(usize, Vec<i32>)> {
    let scale = in_size as f64 / out_size as f64;
    let filterscale = scale.max(1.0);
    let support = 3.0 * filterscale;
    let ss = 1.0 / filterscale;
    (0..out_size)
        .map(|xx| {
            let center = (xx as f64 + 0.5) * scale;
            let xmin = ((center - support + 0.5) as i64).max(0);
            let xmax = ((center + support + 0.5) as i64).min(in_size as i64) - xmin;
            let mut weights: Vec<f64> = (0..xmax)
                .map(|x| lanczos(((x + xmin) as f64 - center + 0.5) * ss))
                .collect();
            let total: f64 = weights.iter().fold(0.0, |sum, w| sum + w);
            if total != 0.0 {
                for w in &mut weights {
                    *w /= total;
                }
            }
            let fixed = weights
                .iter()
                .map(|&w| {
                    let scaled = w * f64::from(1u32 << PRECISION_BITS);
                    if w < 0.0 {
                        (-0.5 + scaled) as i32
                    } else {
                        (0.5 + scaled) as i32
                    }
                })
                .collect();
            (xmin as usize, fixed)
        })
        .collect()
}

fn clip8(value: i32) -> u8 {
    (value >> PRECISION_BITS).clamp(0, 255) as u8
}

/// Pillow's `Image.resize(size, LANCZOS)` for mode L.
fn resize(src: &[u8], width: usize, height: usize, out_w: usize, out_h: usize) -> Vec<u8> {
    let mut wide = src.to_vec();
    if out_w != width {
        let table = coefficients(width, out_w);
        wide = vec![0; out_w * height];
        for y in 0..height {
            for (x, (first, weights)) in table.iter().enumerate() {
                let mut sum = 1 << (PRECISION_BITS - 1);
                for (k, weight) in weights.iter().enumerate() {
                    sum += i32::from(src[y * width + first + k]) * weight;
                }
                wide[y * out_w + x] = clip8(sum);
            }
        }
    }
    if out_h == height {
        return wide;
    }
    let table = coefficients(height, out_h);
    let mut out = vec![0; out_w * out_h];
    for (y, (first, weights)) in table.iter().enumerate() {
        for x in 0..out_w {
            let mut sum = 1 << (PRECISION_BITS - 1);
            for (k, weight) in weights.iter().enumerate() {
                sum += i32::from(wide[(first + k) * out_w + x]) * weight;
            }
            out[y * out_w + x] = clip8(sum);
        }
    }
    out
}

pub fn render(text: &str, font: &str, height: usize) -> Result<Image> {
    let (mask, mask_width, mask_height) = draw_text(text, font, u32::try_from(height * 4)?)?;
    let scaled = (mask_width * height) as f64 / mask_height as f64;
    let width = (scaled.round_ties_even() as usize).max(1);
    let alpha = resize(&mask, mask_width, mask_height, width, height);
    let mut image = Image::new(width, height);
    for (pixel, &a) in image.pixels.iter_mut().zip(&alpha) {
        *pixel = [255, 255, 255, a];
    }
    Ok(image)
}

/// The atlas's own Latin capitals: letter to (x0, y0, x1, y1).
pub fn atlas_glyphs(pixels: &Image) -> BTreeMap<char, [usize; 4]> {
    let mut cells = BTreeMap::new();
    for (row, letters) in LATIN_ROWS {
        let top = row * GLYPH_HEIGHT;
        let columns: Vec<bool> = (0..pixels.width)
            .map(|x| {
                (top..(top + GLYPH_HEIGHT).min(pixels.height)).any(|y| {
                    let p = pixels.get(x, y);
                    p[0] > 160 && p[3] > 128
                })
            })
            .collect();
        let mut runs = Vec::new();
        let mut x = 0;
        while x < columns.len() {
            if columns[x] {
                let start = x;
                while x < columns.len() && columns[x] {
                    x += 1;
                }
                runs.push((start, x));
            }
            x += 1;
        }
        let skip = runs.len().saturating_sub(letters.chars().count());
        for (letter, &(start, end)) in letters.chars().zip(&runs[skip..]) {
            cells.insert(
                letter,
                [
                    start.saturating_sub(1),
                    top,
                    (end + 2).min(columns.len()),
                    top + GLYPH_HEIGHT,
                ],
            );
        }
    }
    cells
}

pub fn compose(pixels: &Image, text: &str, cells: &BTreeMap<char, [usize; 4]>) -> Result<Image> {
    const SPACE: usize = 4;
    let cell = |c: char| {
        cells
            .get(&c)
            .copied()
            .ok_or_else(|| anyhow!("the atlas has no glyph for {c:?}"))
    };
    let mut width = 2;
    for c in text.chars() {
        width += if c == ' ' {
            SPACE
        } else {
            let [x0, _, x1, _] = cell(c)?;
            ensure!(x1 - x0 >= 2, "glyph {c:?} is too narrow");
            x1 - x0 - 2
        };
    }
    let mut out = Image::new(width, GLYPH_HEIGHT);
    let mut x = 0;
    for c in text.chars() {
        if c == ' ' {
            x += SPACE;
            continue;
        }
        let [x0, y0, x1, y1] = cell(c)?;
        ensure!(y1 <= pixels.height, "glyph row for {c:?} leaves the atlas");
        for gy in 0..y1 - y0 {
            for gx in 0..x1 - x0 {
                let glyph = pixels.get(x0 + gx, y0 + gy);
                if glyph[3] > out.get(x + gx, gy)[3] {
                    out.set(x + gx, gy, glyph);
                }
            }
        }
        x += x1 - x0 - 2;
    }
    Ok(out)
}

fn free_mask(
    width: usize,
    height: usize,
    used: &[[f64; 4]],
    regions: &[[i64; 4]],
) -> Result<Vec<bool>> {
    let mut free = vec![false; width * height];
    let clamp = |value: i64, limit: usize| -> Result<usize> {
        ensure!(value >= 0, "negative atlas coordinate {value}");
        Ok((value as usize).min(limit))
    };
    let mut fill = |x0: i64, y0: i64, x1: i64, y1: i64, value: bool| -> Result<()> {
        let (x0, x1) = (clamp(x0, width)?, clamp(x1, width)?);
        for y in clamp(y0, height)?..clamp(y1, height)? {
            for x in x0..x1 {
                free[y * width + x] = value;
            }
        }
        Ok(())
    };
    for &[x0, y0, x1, y1] in regions {
        fill(x0, y0, x1, y1, true)?;
    }
    for &[u0, v0, u1, v1] in used {
        fill(
            (u0 as i64 - 1).max(0),
            (v0 as i64 - 1).max(0),
            u1.ceil() as i64 + 1,
            v1.ceil() as i64 + 1,
            false,
        )?;
    }
    Ok(free)
}

fn allocate(
    free: &mut [bool],
    cols: usize,
    rows: usize,
    width: usize,
    height: usize,
) -> Option<(usize, usize)> {
    if width > cols || height > rows {
        return None;
    }
    let stride = cols + 1;
    let mut integral = vec![0u32; stride * (rows + 1)];
    for y in 0..rows {
        for x in 0..cols {
            integral[(y + 1) * stride + x + 1] = u32::from(free[y * cols + x])
                + integral[y * stride + x + 1]
                + integral[(y + 1) * stride + x]
                - integral[y * stride + x];
        }
    }
    for y in 0..=rows - height {
        for x in 0..=cols - width {
            let total = integral[(y + height) * stride + x + width] + integral[y * stride + x]
                - integral[y * stride + x + width]
                - integral[(y + height) * stride + x];
            if total as usize == width * height {
                for fy in y.saturating_sub(1)..(y + height + 1).min(rows) {
                    for fx in x.saturating_sub(1)..(x + width + 1).min(cols) {
                        free[fy * cols + fx] = false;
                    }
                }
                return Some((x, y));
            }
        }
    }
    None
}

fn tex(vertex: &Vertex, pobj: usize) -> Result<&[f64]> {
    vertex
        .tex0
        .as_ref()
        .map(|element| element.values.as_slice())
        .filter(|values| values.len() >= 2)
        .ok_or_else(|| anyhow!("pobj {pobj:#x}: vertex without texture coordinates"))
}

fn pos(vertex: &Vertex, pobj: usize) -> Result<&[f64]> {
    vertex
        .pos
        .as_ref()
        .map(|element| element.values.as_slice())
        .filter(|values| values.len() >= 3)
        .ok_or_else(|| anyhow!("pobj {pobj:#x}: vertex without a 3D position"))
}

fn span(values: impl Iterator<Item = f64>) -> (f64, f64) {
    values.fold((f64::INFINITY, f64::NEG_INFINITY), |(low, high), v| {
        (low.min(v), high.max(v))
    })
}

/// Quads that sample at least 2x2 texels (the glyphs) and the rest.
fn split_quads(
    geometry: &Geometry,
    pobj: usize,
    size: (usize, usize),
) -> Result<(Vec<Quad>, Vec<Quad>)> {
    let (mut glyphs, mut kept) = (Vec::new(), Vec::new());
    for quad in quads(&geometry.vertices(pobj)?) {
        let mut us = Vec::new();
        let mut vs = Vec::new();
        for vertex in &quad {
            let uv = tex(vertex, pobj)?;
            us.push(uv[0] * size.0 as f64);
            vs.push(uv[1] * size.1 as f64);
        }
        let (u, v) = (span(us.into_iter()), span(vs.into_iter()));
        if u.1 - u.0 >= 2.0 && v.1 - v.0 >= 2.0 {
            glyphs.push(quad);
        } else {
            kept.push(quad);
        }
    }
    Ok((glyphs, kept))
}

fn claim(pool: &mut Pool, attr: &Attribute, value: &[f64], preferred: &[usize]) -> Result<usize> {
    let key: Vec<u64> = value.iter().map(|v| (v + 0.0).to_bits()).collect();
    let cache = pool.values.entry(attr.array).or_default();
    if let Some(&index) = cache.get(&key) {
        return Ok(index);
    }
    let free = pool.free.entry(attr.array).or_default();
    let index = preferred
        .iter()
        .copied()
        .find(|index| free.contains(index))
        .or_else(|| free.first().copied())
        .ok_or_else(|| {
            anyhow!(
                "vertex array {:#x}: not enough private vertices to rewrite",
                attr.array.unwrap_or(0)
            )
        })?;
    free.retain(|&other| other != index);
    cache.insert(key, index);
    Ok(index)
}

pub fn write_floats(data: &mut [u8], offset: usize, values: &[f64]) -> Result<()> {
    let start = HEADER + offset;
    let target = data
        .get_mut(start..start + 4 * values.len())
        .ok_or_else(|| anyhow!("offset {offset:#x} is outside the archive"))?;
    for (raw, &value) in target.as_chunks_mut::<4>().0.iter_mut().zip(values) {
        *raw = (value as f32).to_be_bytes();
    }
    Ok(())
}

fn index_byte(index: usize, pobj: usize) -> Result<u8> {
    u8::try_from(index).with_context(|| format!("pobj {pobj:#x}: index {index} needs 16 bits"))
}

#[allow(clippy::too_many_arguments)]
fn rewrite(
    data: &mut [u8],
    geometry: &Geometry,
    pool: &mut Pool,
    pobj: usize,
    region: [usize; 4],
    size: (usize, usize),
    widen: f64,
    aspect: Option<f64>,
    anchor: &str,
) -> Result<()> {
    let attrs = geometry.attributes(pobj)?;
    let find = |wanted: u32| {
        attrs
            .iter()
            .find(|a| a.attr == wanted)
            .ok_or_else(|| anyhow!("pobj {pobj:#x}: no attribute {wanted}"))
    };
    let (pos_attr, tex_attr) = (find(GX_VA_POS)?, find(GX_VA_TEX0)?);
    if pos_attr.comp != 4 || tex_attr.comp != 4 || attrs.iter().any(|a| a.kind != 1 && a.kind != 2)
    {
        bail!("pobj {pobj:#x}: unsupported vertex format");
    }
    let (glyphs, kept) = split_quads(geometry, pobj, size)?;
    let template = glyphs
        .first()
        .ok_or_else(|| anyhow!("pobj {pobj:#x}: no glyph quads"))?;
    let vertices: Vec<&Vertex> = glyphs.iter().flatten().collect();
    let mut positions = Vec::new();
    for vertex in &vertices {
        positions.push(pos(vertex, pobj)?);
    }
    let (mut x0, mut x1) = span(positions.iter().map(|p| p[0]));
    let (y0, y1) = span(positions.iter().map(|p| p[1]));
    let center = (x0 + x1) / 2.0;
    match aspect.filter(|&aspect| aspect != 0.0) {
        Some(aspect) if anchor == "right" => x0 = x1 - aspect * (y1 - y0),
        Some(aspect) => x1 = x0 + aspect * (y1 - y0),
        None => {
            (x0, x1) = (
                center + (x0 - center) * widen,
                center + (x1 - center) * widen,
            );
        }
    }
    let z = positions[0][2];
    let indices = |attr: u32| -> Vec<usize> {
        vertices
            .iter()
            .filter_map(|vertex| vertex.get(attr).map(|element| element.index))
            .collect()
    };
    let (preferred_pos, preferred_tex) = (indices(GX_VA_POS), indices(GX_VA_TEX0));
    let mut middle = [0.0; 4];
    for vertex in template {
        let (p, t) = (pos(vertex, pobj)?, tex(vertex, pobj)?);
        for (sum, value) in middle.iter_mut().zip([p[0], p[1], t[0], t[1]]) {
            *sum += value;
        }
    }
    let [tx, ty, tu, tv] = middle.map(|sum| sum / 4.0);
    let (u0, u1) = (
        region[0] as f64 / size.0 as f64,
        region[2] as f64 / size.0 as f64,
    );
    let (v0, v1) = (
        region[1] as f64 / size.1 as f64,
        region[3] as f64 / size.1 as f64,
    );
    let (pos_array, tex_array) = match (pos_attr.array, tex_attr.array) {
        (Some(pos_array), Some(tex_array)) => (pos_array, tex_array),
        _ => bail!("pobj {pobj:#x}: attribute without an array"),
    };
    let mut stream = Vec::new();
    for vertex in template {
        let (p, t) = (pos(vertex, pobj)?, tex(vertex, pobj)?);
        ensure!(
            t.len() == 2,
            "pobj {pobj:#x}: texture coordinates are not 2D"
        );
        let position = [
            if p[0] <= tx { x0 } else { x1 },
            if p[1] <= ty { y0 } else { y1 },
            z,
        ];
        let texcoord = [
            if t[0] <= tu { u0 } else { u1 },
            if t[1] <= tv { v0 } else { v1 },
        ];
        let pos_index = claim(pool, pos_attr, &position, &preferred_pos)?;
        let tex_index = claim(pool, tex_attr, &texcoord, &preferred_tex)?;
        write_floats(data, pos_array + pos_index * pos_attr.stride, &position)?;
        write_floats(data, tex_array + tex_index * tex_attr.stride, &texcoord)?;
        for attr in &attrs {
            stream.push(match attr.attr {
                GX_VA_POS => index_byte(pos_index, pobj)?,
                GX_VA_TEX0 => index_byte(tex_index, pobj)?,
                _ => 0,
            });
        }
    }
    for vertex in kept.iter().flatten() {
        for attr in &attrs {
            let index = vertex.get(attr.attr).map_or(0, |element| element.index);
            stream.push(index_byte(index, pobj)?);
        }
    }
    let start = HEADER
        + geometry
            .ptr(pobj + 0x10)?
            .ok_or_else(|| anyhow!("pobj {pobj:#x} has no display list"))?;
    let count = HEADER + pobj + 0x0E;
    let length = usize::from(u16::from_be_bytes([data[count], data[count + 1]])) * 32;
    let mut block = vec![0x80 | (data[start] & 0x07)];
    block.extend_from_slice(&u16::try_from(4 * (1 + kept.len()))?.to_be_bytes());
    block.extend_from_slice(&stream);
    if block.len() > length {
        bail!("pobj {pobj:#x}: rewritten display list does not fit");
    }
    block.resize(length, 0);
    data[start..start + length].copy_from_slice(&block);
    Ok(())
}

fn word_key(word: &Word) -> WordKey {
    (
        word.en.clone(),
        word.font.clone().unwrap_or_else(|| "thin".to_string()),
        word.height.unwrap_or(12),
        word.glyphs.unwrap_or(false),
    )
}

fn hex(text: &str) -> Result<usize> {
    usize::from_str_radix(text, 16).with_context(|| format!("{text:?} is not a hex offset"))
}

pub fn patch_archive(data: &mut [u8], spec: &Spec) -> Result<Vec<Placement>> {
    let archive = Archive::new(data.to_vec())?;
    let geometry = Geometry::new(&archive);
    let scene = scene_offset(data)?;
    let image = hex(&spec.atlas)?;
    let atlas = archive
        .textures()?
        .into_iter()
        .find(|texture| texture.image == image)
        .ok_or_else(|| anyhow!("{}: no texture at {image:#x}", spec.archive))?;
    let size = (atlas.width, atlas.height);
    let mut targets = BTreeSet::new();
    for word in &spec.words {
        targets.insert(hex(&word.pobj)?);
    }
    let mut references: BTreeMap<ArrayRef, BTreeSet<usize>> = BTreeMap::new();
    let mut used = Vec::new();
    for (pobj, images) in all_pobjs(&geometry, scene)? {
        let attrs = geometry.attributes(pobj)?;
        let prims = geometry.vertices(pobj)?;
        for attr in &attrs {
            for vertex in prims.iter().flat_map(|(_, vertices)| vertices) {
                if let Some(element) = vertex.get(attr.attr) {
                    references
                        .entry((attr.array, element.index))
                        .or_default()
                        .insert(pobj);
                }
            }
        }
        if images.contains(&atlas.image) && !targets.contains(&pobj) {
            for quad in quads(&prims) {
                let uvs: Vec<&[f64]> = quad
                    .iter()
                    .filter_map(|vertex| vertex.tex0.as_ref())
                    .map(|element| element.values.as_slice())
                    .collect();
                if !uvs.is_empty() {
                    let u = span(uvs.iter().map(|uv| uv[0] * size.0 as f64));
                    let v = span(uvs.iter().map(|uv| uv[1] * size.1 as f64));
                    used.push([u.0, v.0, u.1, v.1]);
                }
            }
        }
    }
    let mut reserved = BTreeSet::new();
    for &pobj in &targets {
        let attrs = geometry.attributes(pobj)?;
        for vertex in split_quads(&geometry, pobj, size)?.1.iter().flatten() {
            for attr in &attrs {
                if let Some(element) = vertex.get(attr.attr) {
                    reserved.insert((attr.array, element.index));
                }
            }
        }
    }
    let mut pool = Pool::default();
    for (&(array, index), users) in &references {
        if users.is_subset(&targets) && !reserved.contains(&(array, index)) {
            pool.free.entry(array).or_default().push(index);
        }
    }
    let original = archive.decode(&atlas)?;
    let mut pixels = original.clone();
    let mut free = free_mask(size.0, size.1, &used, &spec.free)?;
    for (pixel, _) in pixels.pixels.iter_mut().zip(&free).filter(|(_, &f)| f) {
        *pixel = [0; 4];
    }
    let cells = atlas_glyphs(&original);
    let mut images: Vec<(WordKey, Image)> = Vec::new();
    for word in &spec.words {
        let key = word_key(word);
        if images.iter().any(|(other, _)| *other == key) {
            continue;
        }
        let image = if key.3 {
            compose(&original, &key.0, &cells)?
        } else {
            render(&key.0, &key.1, key.2)?
        };
        images.push((key, image));
    }
    images.sort_by_key(|(_, image)| Reverse(image.width * image.height));
    let mut regions: Vec<(WordKey, [usize; 4])> = Vec::new();
    for (key, image) in &images {
        let (x, y) = allocate(&mut free, size.0, size.1, image.width, image.height)
            .ok_or_else(|| anyhow!("{}: no atlas room for {:?}", spec.archive, key.0))?;
        for row in 0..image.height {
            for column in 0..image.width {
                pixels.set(x + column, y + row, image.get(column, row));
            }
        }
        regions.push((key.clone(), [x, y, x + image.width, y + image.height]));
    }
    for word in &spec.words {
        let key = word_key(word);
        let region = regions
            .iter()
            .find(|(other, _)| *other == key)
            .map(|(_, region)| *region)
            .ok_or_else(|| anyhow!("{}: {:?} was not placed", spec.archive, key.0))?;
        let aspect = key
            .3
            .then(|| (region[2] - region[0]) as f64 / (region[3] - region[1]) as f64);
        rewrite(
            data,
            &geometry,
            &mut pool,
            hex(&word.pobj)?,
            region,
            size,
            word.widen.unwrap_or(1.0),
            aspect,
            word.anchor.as_deref().unwrap_or("left"),
        )?;
    }
    let (start, encoded) = archive.encoded(&atlas, &pixels)?;
    let (tiles, tile_size) = changed_blocks(&original, &pixels, atlas.format)?;
    let merged = merge(
        &data[start..start + encoded.len()],
        &encoded,
        &tiles,
        tile_size,
    );
    data[start..start + encoded.len()].copy_from_slice(&merged);
    Ok(regions
        .into_iter()
        .map(|((text, font, height, glyphs), region)| Placement {
            text,
            font,
            height,
            glyphs,
            region,
        })
        .collect())
}

pub fn load_specs(words: &Path) -> Result<Vec<Spec>> {
    let text =
        std::fs::read_to_string(words).with_context(|| format!("read {}", words.display()))?;
    serde_json::from_str(&text).with_context(|| format!("parse {}", words.display()))
}

pub fn atlas_patches_from(words: &Path, iso: &Path, files: &mut Files) -> Result<usize> {
    let mut count = 0;
    for spec in load_specs(words)? {
        if !files.contains_key(&spec.archive) {
            files.insert(spec.archive.clone(), disc::read_file(iso, &spec.archive)?);
        }
        let data = files
            .get_mut(&spec.archive)
            .ok_or_else(|| anyhow!("{} is missing", spec.archive))?;
        patch_archive(data, &spec)?;
        count += spec.words.len();
    }
    Ok(count)
}

pub fn atlas_patches(iso: &Path, files: &mut Files) -> Result<usize> {
    atlas_patches_from(&words_path(), iso, files)
}
