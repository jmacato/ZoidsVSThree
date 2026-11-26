use crate::gx::{self, Image};
use crate::hsd::Archive;
use crate::{disc, Files};
use anyhow::{anyhow, bail, ensure, Context, Result};
use std::fs::File;
use std::io::BufReader;
use std::path::{Path, PathBuf};

pub fn overrides_dir() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR")).join("../../translation/textures")
}

/// Per block, whether the edit differs from the original, and the encoded size of one block.
pub fn changed_blocks(original: &Image, edited: &Image, fmt: u32) -> Result<(Vec<bool>, usize)> {
    let (bw, bh, bits) = gx::block(fmt).ok_or_else(|| anyhow!("format {fmt}"))?;
    let (pw, ph) = gx::padded(original.width, original.height, fmt)?;
    let same = original.width == edited.width && original.height == edited.height;
    let mut tiles = Vec::with_capacity(pw / bw * (ph / bh));
    for ty in (0..ph).step_by(bh) {
        for tx in (0..pw).step_by(bw) {
            let rows = ty..(ty + bh).min(original.height);
            let columns = tx..(tx + bw).min(original.width);
            let equal = same
                && rows.clone().all(|y| {
                    columns
                        .clone()
                        .all(|x| original.get(x, y) == edited.get(x, y))
                });
            tiles.push(!equal);
        }
    }
    Ok((tiles, bw * bh * bits / 8))
}

pub fn merge(old: &[u8], new: &[u8], tiles: &[bool], tile_size: usize) -> Vec<u8> {
    let mut out = old.to_vec();
    for (index, _) in tiles.iter().enumerate().filter(|(_, &changed)| changed) {
        let range = index * tile_size..(index + 1) * tile_size;
        out[range.clone()].copy_from_slice(&new[range]);
    }
    out
}

/// The PNG as PIL's `Image.open(path).convert("RGBA")` returns it, for 8-bit PNGs without tRNS.
pub fn load_png(path: &Path) -> Result<Image> {
    let file = File::open(path).with_context(|| format!("open {}", path.display()))?;
    let mut decoder = png::Decoder::new(BufReader::new(file));
    decoder.set_transformations(png::Transformations::IDENTITY);
    let mut reader = decoder.read_info()?;
    let mut buffer = vec![0; reader.output_buffer_size()];
    let frame = reader.next_frame(&mut buffer)?;
    ensure!(
        frame.bit_depth == png::BitDepth::Eight && reader.info().trns.is_none(),
        "{}: only 8-bit PNGs without tRNS are supported",
        path.display()
    );
    let (width, height) = (frame.width as usize, frame.height as usize);
    let channels = match frame.color_type {
        png::ColorType::Rgba => 4,
        png::ColorType::Rgb => 3,
        png::ColorType::GrayscaleAlpha => 2,
        png::ColorType::Grayscale => 1,
        png::ColorType::Indexed => bail!("{}: palette PNGs are not supported", path.display()),
    };
    let mut image = Image::new(width, height);
    for y in 0..height {
        let row = &buffer[y * frame.line_size..][..width * channels];
        for (x, p) in row.chunks_exact(channels).enumerate() {
            let pixel = match channels {
                4 => [p[0], p[1], p[2], p[3]],
                3 => [p[0], p[1], p[2], 255],
                2 => [p[0], p[0], p[0], p[1]],
                _ => [p[0], p[0], p[0], 255],
            };
            image.set(x, y, pixel);
        }
    }
    Ok(image)
}

fn collect(folder: &Path, found: &mut Vec<PathBuf>) -> Result<()> {
    for entry in std::fs::read_dir(folder).with_context(|| format!("list {}", folder.display()))? {
        let path = entry?.path();
        if path.is_dir() {
            collect(&path, found)?;
        }
        if path.extension().is_some_and(|ext| ext == "png") {
            found.push(path);
        }
    }
    Ok(())
}

/// Every override as (PNG path, archive disc path, image offset), in the order they are applied.
pub fn overrides(folder: &Path) -> Result<Vec<(PathBuf, String, usize)>> {
    let mut found = Vec::new();
    if folder.is_dir() {
        collect(folder, &mut found)?;
    }
    found.sort();
    found
        .into_iter()
        .map(|png| {
            let bad = || anyhow!("{}: not an override path", png.display());
            let parent = png.parent().ok_or_else(bad)?.strip_prefix(folder)?;
            let archive = parent
                .iter()
                .map(|part| part.to_str().ok_or_else(bad))
                .collect::<Result<Vec<_>>>()?
                .join("/");
            let stem = png
                .file_stem()
                .and_then(|stem| stem.to_str())
                .ok_or_else(bad)?;
            let image = usize::from_str_radix(stem, 16).with_context(bad)?;
            Ok((png, archive, image))
        })
        .collect()
}

pub fn texture_patches_from(folder: &Path, iso: &Path, files: &mut Files) -> Result<usize> {
    let mut count = 0;
    for (png, path, image) in overrides(folder)? {
        if !files.contains_key(&path) {
            files.insert(path.clone(), disc::read_file(iso, &path)?);
        }
        let data = files
            .get_mut(&path)
            .ok_or_else(|| anyhow!("{path} is missing"))?;
        let archive = Archive::new(data.clone())?;
        let texture = archive
            .textures()?
            .into_iter()
            .find(|texture| texture.image == image)
            .ok_or_else(|| anyhow!("{}: no texture at {image:#x} in {path}", png.display()))?;
        let original = archive.decode(&texture)?;
        let edited = load_png(&png)?;
        ensure!(
            edited.width == original.width && edited.height == original.height,
            "{}: {}x{}, texture is {}x{}",
            png.display(),
            edited.width,
            edited.height,
            texture.width,
            texture.height
        );
        let (start, encoded) = archive.encoded(&texture, &edited)?;
        let (tiles, tile_size) = changed_blocks(&original, &edited, texture.format)?;
        let merged = merge(
            &data[start..start + encoded.len()],
            &encoded,
            &tiles,
            tile_size,
        );
        data[start..start + encoded.len()].copy_from_slice(&merged);
        count += 1;
    }
    Ok(count)
}

pub fn texture_patches(iso: &Path, files: &mut Files) -> Result<usize> {
    texture_patches_from(&overrides_dir(), iso, files)
}
