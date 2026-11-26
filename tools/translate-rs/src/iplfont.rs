use anyhow::{anyhow, bail, ensure, Context, Result};
use freetype::face::LoadFlag;
use std::path::{Path, PathBuf};

pub const DISC_PATH: &str = "menu/demo/demo2.dat";
pub const HEADER_SIZE: usize = 0x30;
pub const HANKAKU_BASE: usize = 0x20C;
/// Cell of byte 0xA1, the first half-width katakana code.
pub const KATAKANA_BASE: usize = 0x26B;
/// Bold face drawn into the full-width Latin cells of every story font, for the title screen lines.
pub const TITLE_TTF: &str = "ChakraPetch-Bold.ttf";
/// Symbols of the title lines: the half-width katakana byte that selects each one and its character.
pub const TITLE_SYMBOLS: [(u8, char); 2] = [(0xA9, '\u{A9}'), (0xB7, '\u{B7}')];
pub const TEXT_SYMBOLS: [(u8, char); 1] = [(0xAA, '\u{A9}')];
/// ASCII character, font cell and full-width character of each title glyph.
pub const TITLE_GLYPHS: [(u8, usize, char); 93] = [
    (0x20, 0x000, '\u{3000}'),
    (0x21, 0x009, '\u{FF01}'),
    (0x23, 0x053, '\u{FF03}'),
    (0x24, 0x04F, '\u{FF04}'),
    (0x25, 0x052, '\u{FF05}'),
    (0x26, 0x054, '\u{FF06}'),
    (0x28, 0x029, '\u{FF08}'),
    (0x29, 0x02A, '\u{FF09}'),
    (0x2A, 0x055, '\u{FF0A}'),
    (0x2B, 0x03B, '\u{FF0B}'),
    (0x2C, 0x003, '\u{FF0C}'),
    (0x2D, 0x03C, '\u{FF0D}'),
    (0x2E, 0x004, '\u{FF0E}'),
    (0x2F, 0x01E, '\u{FF0F}'),
    (0x30, 0x093, '\u{FF10}'),
    (0x31, 0x094, '\u{FF11}'),
    (0x32, 0x095, '\u{FF12}'),
    (0x33, 0x096, '\u{FF13}'),
    (0x34, 0x097, '\u{FF14}'),
    (0x35, 0x098, '\u{FF15}'),
    (0x36, 0x099, '\u{FF16}'),
    (0x37, 0x09A, '\u{FF17}'),
    (0x38, 0x09B, '\u{FF18}'),
    (0x39, 0x09C, '\u{FF19}'),
    (0x3A, 0x006, '\u{FF1A}'),
    (0x3B, 0x007, '\u{FF1B}'),
    (0x3C, 0x042, '\u{FF1C}'),
    (0x3D, 0x040, '\u{FF1D}'),
    (0x3E, 0x043, '\u{FF1E}'),
    (0x3F, 0x008, '\u{FF1F}'),
    (0x40, 0x056, '\u{FF20}'),
    (0x41, 0x09D, '\u{FF21}'),
    (0x42, 0x09E, '\u{FF22}'),
    (0x43, 0x09F, '\u{FF23}'),
    (0x44, 0x0A0, '\u{FF24}'),
    (0x45, 0x0A1, '\u{FF25}'),
    (0x46, 0x0A2, '\u{FF26}'),
    (0x47, 0x0A3, '\u{FF27}'),
    (0x48, 0x0A4, '\u{FF28}'),
    (0x49, 0x0A5, '\u{FF29}'),
    (0x4A, 0x0A6, '\u{FF2A}'),
    (0x4B, 0x0A7, '\u{FF2B}'),
    (0x4C, 0x0A8, '\u{FF2C}'),
    (0x4D, 0x0A9, '\u{FF2D}'),
    (0x4E, 0x0AA, '\u{FF2E}'),
    (0x4F, 0x0AB, '\u{FF2F}'),
    (0x50, 0x0AC, '\u{FF30}'),
    (0x51, 0x0AD, '\u{FF31}'),
    (0x52, 0x0AE, '\u{FF32}'),
    (0x53, 0x0AF, '\u{FF33}'),
    (0x54, 0x0B0, '\u{FF34}'),
    (0x55, 0x0B1, '\u{FF35}'),
    (0x56, 0x0B2, '\u{FF36}'),
    (0x57, 0x0B3, '\u{FF37}'),
    (0x58, 0x0B4, '\u{FF38}'),
    (0x59, 0x0B5, '\u{FF39}'),
    (0x5A, 0x0B6, '\u{FF3A}'),
    (0x5B, 0x02D, '\u{FF3B}'),
    (0x5C, 0x01F, '\u{FF3C}'),
    (0x5D, 0x02E, '\u{FF3D}'),
    (0x5E, 0x00F, '\u{FF3E}'),
    (0x5F, 0x011, '\u{FF3F}'),
    (0x60, 0x00D, '\u{FF40}'),
    (0x61, 0x0B7, '\u{FF41}'),
    (0x62, 0x0B8, '\u{FF42}'),
    (0x63, 0x0B9, '\u{FF43}'),
    (0x64, 0x0BA, '\u{FF44}'),
    (0x65, 0x0BB, '\u{FF45}'),
    (0x66, 0x0BC, '\u{FF46}'),
    (0x67, 0x0BD, '\u{FF47}'),
    (0x68, 0x0BE, '\u{FF48}'),
    (0x69, 0x0BF, '\u{FF49}'),
    (0x6A, 0x0C0, '\u{FF4A}'),
    (0x6B, 0x0C1, '\u{FF4B}'),
    (0x6C, 0x0C2, '\u{FF4C}'),
    (0x6D, 0x0C3, '\u{FF4D}'),
    (0x6E, 0x0C4, '\u{FF4E}'),
    (0x6F, 0x0C5, '\u{FF4F}'),
    (0x70, 0x0C6, '\u{FF50}'),
    (0x71, 0x0C7, '\u{FF51}'),
    (0x72, 0x0C8, '\u{FF52}'),
    (0x73, 0x0C9, '\u{FF53}'),
    (0x74, 0x0CA, '\u{FF54}'),
    (0x75, 0x0CB, '\u{FF55}'),
    (0x76, 0x0CC, '\u{FF56}'),
    (0x77, 0x0CD, '\u{FF57}'),
    (0x78, 0x0CE, '\u{FF58}'),
    (0x79, 0x0CF, '\u{FF59}'),
    (0x7A, 0x0D0, '\u{FF5A}'),
    (0x7B, 0x02F, '\u{FF5B}'),
    (0x7C, 0x022, '\u{FF5C}'),
    (0x7D, 0x030, '\u{FF5D}'),
    (0x7E, 0x020, '\u{FF5E}'),
];

/// Rewrites ASCII as the full-width characters whose cells hold the bold title face.
pub fn title_text(text: &str) -> String {
    text.chars()
        .map(|character| {
            TITLE_GLYPHS
                .iter()
                .find(|glyph| char::from(glyph.0) == character)
                .map_or(character, |glyph| glyph.2)
        })
        .collect()
}
pub const CAP_TOP: i32 = 2;
pub const BASELINE: i32 = 19;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Header {
    pub font_type: u16,
    pub first_char: u16,
    pub last_char: u16,
    pub inval_char: u16,
    pub ascent: u16,
    pub descent: u16,
    pub width: u16,
    pub leading: u16,
    pub cell_width: u16,
    pub cell_height: u16,
    pub sheet_size: u32,
    pub sheet_format: u16,
    pub sheet_column: u16,
    pub sheet_row: u16,
    pub sheet_width: u16,
    pub sheet_height: u16,
    pub width_table: u16,
    pub sheet_image: u32,
    pub sheet_full_size: u32,
    pub colors: [u8; 4],
}

pub const SJIS_HEADER: Header = Header {
    font_type: 2,
    first_char: 0x8140,
    last_char: 0x9872,
    inval_char: 0x20,
    ascent: 24,
    descent: 0,
    width: 24,
    leading: 28,
    cell_width: 24,
    cell_height: 24,
    sheet_size: 0x20000,
    sheet_format: 0,
    sheet_column: 21,
    sheet_row: 21,
    sheet_width: 512,
    sheet_height: 512,
    width_table: 0x30,
    sheet_image: 0xEE4,
    sheet_full_size: 0x40000,
    colors: [0, 85, 170, 255],
};

impl Header {
    pub fn pack(&self) -> [u8; HEADER_SIZE] {
        let mut raw = Vec::with_capacity(HEADER_SIZE);
        let short = |raw: &mut Vec<u8>, values: &[u16]| {
            for value in values {
                raw.extend_from_slice(&value.to_be_bytes());
            }
        };
        short(
            &mut raw,
            &[
                self.font_type,
                self.first_char,
                self.last_char,
                self.inval_char,
                self.ascent,
                self.descent,
                self.width,
                self.leading,
                self.cell_width,
                self.cell_height,
            ],
        );
        raw.extend_from_slice(&self.sheet_size.to_be_bytes());
        short(
            &mut raw,
            &[
                self.sheet_format,
                self.sheet_column,
                self.sheet_row,
                self.sheet_width,
                self.sheet_height,
                self.width_table,
            ],
        );
        raw.extend_from_slice(&self.sheet_image.to_be_bytes());
        raw.extend_from_slice(&self.sheet_full_size.to_be_bytes());
        raw.extend_from_slice(&self.colors);
        let mut packed = [0; HEADER_SIZE];
        packed.copy_from_slice(&raw);
        packed
    }

    pub fn unpack(raw: &[u8]) -> Result<Self> {
        ensure!(raw.len() >= HEADER_SIZE, "font header is cut short");
        let short = |at: usize| u16::from_be_bytes([raw[at], raw[at + 1]]);
        let long = |at: usize| u32::from_be_bytes([raw[at], raw[at + 1], raw[at + 2], raw[at + 3]]);
        Ok(Self {
            font_type: short(0),
            first_char: short(2),
            last_char: short(4),
            inval_char: short(6),
            ascent: short(8),
            descent: short(10),
            width: short(12),
            leading: short(14),
            cell_width: short(16),
            cell_height: short(18),
            sheet_size: long(20),
            sheet_format: short(24),
            sheet_column: short(26),
            sheet_row: short(28),
            sheet_width: short(30),
            sheet_height: short(32),
            width_table: short(34),
            sheet_image: long(36),
            sheet_full_size: long(40),
            colors: [raw[44], raw[45], raw[46], raw[47]],
        })
    }
}

fn word(data: &[u8], at: usize) -> Result<usize> {
    let raw = data
        .get(at..at + 4)
        .ok_or_else(|| anyhow!("Yay0 data is cut short at {at:#x}"))?;
    Ok(u32::from_be_bytes([raw[0], raw[1], raw[2], raw[3]]) as usize)
}

fn byte(data: &[u8], at: usize) -> Result<u8> {
    data.get(at)
        .copied()
        .ok_or_else(|| anyhow!("Yay0 data is cut short at {at:#x}"))
}

pub fn yay0_decode(data: &[u8]) -> Result<Vec<u8>> {
    let (size, links, chunks) = (word(data, 4)?, word(data, 8)?, word(data, 12)?);
    let mut out = Vec::with_capacity(size);
    let (mut mask_at, mut link_at, mut chunk_at) = (16, links, chunks);
    let (mut bits, mut mask) = (0, 0);
    while out.len() < size {
        if bits == 0 {
            mask = word(data, mask_at)?;
            mask_at += 4;
            bits = 32;
        }
        if mask & 0x8000_0000 != 0 {
            out.push(byte(data, chunk_at)?);
            chunk_at += 1;
        } else {
            let link =
                usize::from(byte(data, link_at)?) << 8 | usize::from(byte(data, link_at + 1)?);
            link_at += 2;
            let back = (link & 0xFFF) + 1;
            let mut count = link >> 12;
            if count == 0 {
                count = usize::from(byte(data, chunk_at)?) + 18;
                chunk_at += 1;
            } else {
                count += 2;
            }
            ensure!(back <= out.len(), "Yay0 link reaches before the output");
            for _ in 0..count {
                out.push(out[out.len() - back]);
            }
        }
        mask = mask << 1 & 0xFFFF_FFFF;
        bits -= 1;
    }
    Ok(out)
}

pub fn yay0_store(data: &[u8]) -> Result<Vec<u8>> {
    let masks = data.len().div_ceil(32) * 4;
    let links = u32::try_from(16 + masks)?;
    let mut out = b"Yay0".to_vec();
    out.extend_from_slice(&u32::try_from(data.len())?.to_be_bytes());
    out.extend_from_slice(&links.to_be_bytes());
    out.extend_from_slice(&links.to_be_bytes());
    out.resize(16 + masks, 0xFF);
    out.extend_from_slice(data);
    out.resize(out.len().div_ceil(32) * 32, 0);
    Ok(out)
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Font {
    pub raw: Vec<u8>,
    pub header: Header,
}

impl Font {
    pub fn new(raw: Vec<u8>) -> Result<Self> {
        let header = Header::unpack(&raw)?;
        Ok(Self { raw, header })
    }

    pub fn load(data: &[u8]) -> Result<Self> {
        Self::new(yay0_decode(data)?)
    }

    pub fn blank(header: Header) -> Self {
        let sheets = header.sheet_full_size / header.sheet_size;
        let mut raw = vec![0; (header.sheet_image + sheets * header.sheet_size / 2) as usize];
        raw[..HEADER_SIZE].copy_from_slice(&header.pack());
        Self { raw, header }
    }

    /// Sheet number and the cell's left and top pixel on it.
    pub fn glyph_place(&self, code: usize) -> (usize, usize, usize) {
        let columns = usize::from(self.header.sheet_column);
        let per_sheet = columns * usize::from(self.header.sheet_row);
        let (sheet, index) = (code / per_sheet, code % per_sheet);
        (
            sheet,
            index % columns * usize::from(self.header.cell_width),
            index / columns * usize::from(self.header.cell_height),
        )
    }

    pub fn pixel_offset(&self, sheet: usize, x: usize, y: usize) -> usize {
        let base = self.header.sheet_image as usize + sheet * self.header.sheet_size as usize / 2;
        base + usize::from(self.header.sheet_width) * 2 * (y / 8)
            + (x / 8) * 16
            + (y % 8) * 2
            + (x % 8) / 4
    }

    /// `levels` holds one 2-bit value per cell pixel, row by row.
    pub fn set_glyph(&mut self, code: usize, levels: &[u8], advance: u8) -> Result<()> {
        let (width, height) = (
            usize::from(self.header.cell_width),
            usize::from(self.header.cell_height),
        );
        ensure!(
            levels.len() == width * height,
            "glyph {code:#x} is not one cell"
        );
        let (sheet, left, top) = self.glyph_place(code);
        for y in 0..height {
            for x in 0..width {
                let at = self.pixel_offset(sheet, left + x, top + y);
                let shift = 6 - (x % 4) * 2;
                let target = self
                    .raw
                    .get_mut(at)
                    .ok_or_else(|| anyhow!("glyph {code:#x} is outside the sheets"))?;
                *target = *target & !(3 << shift) | (levels[y * width + x] & 3) << shift;
            }
        }
        let at = usize::from(self.header.width_table) + code;
        *self
            .raw
            .get_mut(at)
            .ok_or_else(|| anyhow!("glyph {code:#x} is outside the width table"))? = advance;
        Ok(())
    }

    pub fn advance(&self, code: usize) -> u8 {
        self.raw[usize::from(self.header.width_table) + code]
    }

    pub fn encode(&self) -> Result<Vec<u8>> {
        yay0_store(&self.raw)
    }
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

/// An 8-bit text mask and where its top left corner sits relative to the drawing point.
pub struct Mask {
    pub pixels: Vec<u8>,
    pub width: usize,
    pub height: usize,
    pub left: i32,
    pub top: i32,
}

/// A TrueType face at one pixel size, measured and drawn as PIL's `FreeTypeFont` does with raqm.
pub struct Face {
    face: freetype::Face,
    bytes: Vec<u8>,
    path: PathBuf,
    pub size: u32,
}

impl Face {
    pub fn new(ttf: &Path, size: u32) -> Result<Self> {
        let bytes = std::fs::read(ttf).with_context(|| format!("read {}", ttf.display()))?;
        let library = freetype::Library::init()?;
        let face = library.new_face(ttf, 0)?;
        face.set_pixel_sizes(0, size)?;
        Ok(Self {
            face,
            bytes,
            path: ttf.to_path_buf(),
            size,
        })
    }

    fn shape(&self, text: &str) -> Result<Vec<Shaped>> {
        let shaper = rustybuzz::Face::from_slice(&self.bytes, 0)
            .ok_or_else(|| anyhow!("{}: the face cannot be shaped", self.path.display()))?;
        let metrics = self
            .face
            .size_metrics()
            .ok_or_else(|| anyhow!("{}: no size metrics", self.path.display()))?;
        let upem = i64::from(self.face.em_size());
        ensure!(upem > 0, "{}: no em size", self.path.display());
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

    /// Width, height and the "la" anchor offset of the run's pixel box.
    fn extent(&self, run: &[Shaped]) -> Result<(usize, usize, i32, i32)> {
        let (mut position, mut x_min, mut x_max, mut y_min, mut y_max) = (0, 0, 0, 0, 0);
        for glyph in run {
            let px = pixel(position + glyph.x_offset);
            let py = pixel(glyph.y_offset);
            position += glyph.x_advance;
            x_max = x_max.max(pixel(position));
            self.face.load_glyph(glyph.index, LoadFlag::DEFAULT)?;
            let bbox = self
                .face
                .glyph()
                .get_glyph()?
                .get_cbox(freetype::ffi::FT_GLYPH_BBOX_PIXELS);
            x_max = x_max.max(bbox.xMax as i32 + px);
            x_min = x_min.min(bbox.xMin as i32 + px);
            y_max = y_max.max(bbox.yMax as i32 + py);
            y_min = y_min.min(bbox.yMin as i32 + py);
        }
        let ascender = if run.is_empty() {
            0
        } else {
            let metrics = self
                .face
                .size_metrics()
                .ok_or_else(|| anyhow!("{}: no size metrics", self.path.display()))?;
            pixel(i32::try_from(metrics.ascender)?)
        };
        Ok((
            usize::try_from(x_max - x_min)?,
            usize::try_from(y_max - y_min)?,
            x_min,
            ascender - y_max,
        ))
    }

    /// `FreeTypeFont.getbbox(text)`: left, top, right, bottom.
    pub fn bbox(&self, text: &str) -> Result<[i32; 4]> {
        let (width, height, left, top) = self.extent(&self.shape(text)?)?;
        Ok([left, top, left + width as i32, top + height as i32])
    }

    /// `FreeTypeFont.getlength(text)`.
    pub fn length(&self, text: &str) -> Result<f64> {
        let total: i32 = self.shape(text)?.iter().map(|glyph| glyph.x_advance).sum();
        Ok(f64::from(total) / 64.0)
    }

    /// PIL getmask2 for mode L.
    pub fn mask(&self, text: &str) -> Result<Mask> {
        let run = self.shape(text)?;
        let (width, height, x_offset, y_offset) = self.extent(&run)?;
        let mut ink = vec![0u8; width * height];
        let render = LoadFlag::DEFAULT | LoadFlag::RENDER;
        let (mut x, mut y, mut left, mut top) = (0, 0, 0, 0);
        for glyph in &run {
            self.face.load_glyph(glyph.index, render)?;
            let slot = self.face.glyph();
            top = top.max(slot.bitmap_top() + pixel(y + glyph.y_offset));
            left = left.min(slot.bitmap_left() + pixel(x + glyph.x_offset));
            x += glyph.x_advance;
            y += glyph.y_advance;
        }
        let (mut x, mut y) = (-left * 64, -top * 64);
        for glyph in &run {
            self.face.load_glyph(glyph.index, render)?;
            let slot = self.face.glyph();
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
        Ok(Mask {
            pixels: ink,
            width,
            height,
            left: x_offset,
            top: y_offset,
        })
    }
}

fn face_at(ttf: &Path, size: u32, variation: Option<&[f64]>) -> Result<Face> {
    if variation.is_some_and(|axes| !axes.is_empty()) {
        bail!("{}: variable font axes are not supported", ttf.display());
    }
    Face::new(ttf, size)
}

pub fn fitted_face(ttf: &Path, cell: i32, variation: Option<&[f64]>) -> Result<Face> {
    for size in (9..=40).rev() {
        let face = face_at(ttf, size, variation)?;
        let [_, top, _, bottom] = face.bbox("H")?;
        let mut lowest = i32::MIN;
        for c in "gjpqy".chars() {
            lowest = lowest.max(face.bbox(c.encode_utf8(&mut [0; 4]))?[3]);
        }
        let descent = lowest - bottom;
        let mut widest = f64::NEG_INFINITY;
        for c in '\u{21}'..'\u{7f}' {
            widest = widest.max(face.length(c.encode_utf8(&mut [0; 4]))?);
        }
        if bottom - top <= BASELINE - CAP_TOP + 1
            && CAP_TOP + bottom - top + descent <= cell
            && widest <= f64::from(cell)
        {
            return Ok(face);
        }
    }
    bail!("{}: no size fits a {cell}-pixel cell", ttf.display())
}

fn argsort(values: &[u8; 4]) -> [u8; 4] {
    let mut order = [0, 1, 2, 3];
    order.sort_by_key(|&index| values[usize::from(index)]);
    order
}

pub fn latin_font(ttf: &Path, variation: Option<&[f64]>) -> Result<Font> {
    let font = Font::blank(SJIS_HEADER);
    let face = fitted_face(ttf, i32::from(font.header.cell_height), variation)?;
    draw_font(font, &face)
}

pub const FIXED_CAP: i32 = 17;
pub const FIXED_CELL_WIDTH: u16 = 32;

pub fn fixed_face(ttf: &Path) -> Result<Face> {
    for size in (9..=40).rev() {
        let face = Face::new(ttf, size)?;
        let [_, top, _, bottom] = face.bbox("H")?;
        let mut lowest = i32::MIN;
        let mut widest = f64::NEG_INFINITY;
        for c in (0x21_u8..0x7f).map(char::from) {
            let text = c.to_string();
            lowest = lowest.max(face.bbox(&text)?[3]);
            widest = widest.max(face.length(&text)?);
        }
        if bottom - top <= FIXED_CAP
            && CAP_TOP + bottom - top + lowest - bottom <= i32::from(SJIS_HEADER.cell_height)
            && widest <= f64::from(FIXED_CELL_WIDTH)
        {
            return Ok(face);
        }
    }
    bail!(
        "{}: no size gives a {FIXED_CAP}-pixel cap height",
        ttf.display()
    )
}

pub fn fixed_font(ttf: &Path) -> Result<Font> {
    let header = Header {
        width: FIXED_CELL_WIDTH,
        cell_width: FIXED_CELL_WIDTH,
        sheet_column: SJIS_HEADER.sheet_width / FIXED_CELL_WIDTH,
        ..SJIS_HEADER
    };
    let face = fixed_face(ttf)?;
    let font = draw_font(Font::blank(header), &face)?;
    let symbols: Vec<(usize, char)> = TEXT_SYMBOLS
        .iter()
        .map(|symbol| (KATAKANA_BASE + usize::from(symbol.0) - 0xA1, symbol.1))
        .collect();
    let font = draw_glyphs(font, &face, &symbols)?;
    let bold = fixed_face(
        &Path::new(env!("CARGO_MANIFEST_DIR"))
            .join("../translate/fonts")
            .join(TITLE_TTF),
    )?;
    let glyphs: Vec<(usize, char)> = TITLE_GLYPHS
        .iter()
        .map(|glyph| (glyph.1, char::from(glyph.0)))
        .chain(
            TITLE_SYMBOLS
                .iter()
                .map(|symbol| (KATAKANA_BASE + usize::from(symbol.0) - 0xA1, symbol.1)),
        )
        .collect();
    draw_glyphs(font, &bold, &glyphs)
}

fn draw_font(font: Font, face: &Face) -> Result<Font> {
    let glyphs: Vec<(usize, char)> = (0x20u8..0x7F)
        .map(|code| (HANKAKU_BASE + usize::from(code) - 0x20, char::from(code)))
        .collect();
    draw_glyphs(font, face, &glyphs)
}

fn draw_glyphs(mut font: Font, face: &Face, glyphs: &[(usize, char)]) -> Result<Font> {
    let levels = argsort(&font.header.colors);
    let (cell_width, cell_height) = (
        usize::from(font.header.cell_width),
        usize::from(font.header.cell_height),
    );
    let h_top = face.bbox("H")?[1];
    for &(place, character) in glyphs {
        let mut buffer = [0; 4];
        let text: &str = character.encode_utf8(&mut buffer);
        let shift = if character == ' ' {
            0
        } else {
            face.bbox(text)?[0].min(0)
        };
        let Mask {
            pixels: mask,
            width,
            height,
            left,
            top,
        } = face.mask(text)?;
        let (left, top) = (left - shift, top + CAP_TOP - h_top);
        let mut cell = vec![levels[0]; cell_width * cell_height];
        for row in 0..height {
            let y = top + row as i32;
            if y < 0 || y as usize >= cell_height {
                continue;
            }
            for column in 0..width {
                let x = left + column as i32;
                if x < 0 || x as usize >= cell_width {
                    continue;
                }
                let value = f32::from(mask[row * width + column]) / 255.0;
                let level = (value * 3.0).round_ties_even().clamp(0.0, 3.0) as usize;
                cell[y as usize * cell_width + x as usize] = levels[level];
            }
        }
        let advance = (face.length(text)? - f64::from(shift))
            .round_ties_even()
            .clamp(1.0, cell_width as f64) as u8;
        font.set_glyph(place, &cell, advance)?;
    }
    Ok(font)
}

pub const STORY_FONTS: [(&str, &str); 3] = [
    ("chakra", "ChakraPetch-Medium.ttf"),
    ("xolonium", "Xolonium-Regular.ttf"),
    ("saira", "SairaSemiCondensed-Medium.ttf"),
];

pub fn story_ttf(name: &str) -> Result<PathBuf> {
    let file = STORY_FONTS
        .iter()
        .find(|font| font.0 == name)
        .ok_or_else(|| anyhow!("unknown font {name}; use chakra, xolonium or saira"))?
        .1;
    Ok(Path::new(env!("CARGO_MANIFEST_DIR"))
        .join("../translate/fonts")
        .join(file))
}

pub fn story_font(name: &str) -> Result<Font> {
    fixed_font(&story_ttf(name)?)
}

pub const SWITCH_PATHS: [&str; 3] = [DISC_PATH, "disp/partner01.dat", "disp/partner02.dat"];

pub const STORY_FONT_LABELS: [&str; 3] = ["Chakra Petch", "Xolonium", "Saira Semi Condensed"];

pub fn font_order(default: &str) -> Result<Vec<(&'static str, &'static str)>> {
    let names = STORY_FONTS.iter().map(|font| font.0).zip(STORY_FONT_LABELS);
    let first: Vec<_> = names.clone().filter(|font| font.0 == default).collect();
    if first.is_empty() {
        bail!("unknown font {default}; use chakra, xolonium or saira");
    }
    Ok(first
        .into_iter()
        .chain(names.filter(|font| font.0 != default))
        .collect())
}
