use anyhow::{bail, ensure, Result};

pub const I4: u32 = 0;
pub const I8: u32 = 1;
pub const IA4: u32 = 2;
pub const IA8: u32 = 3;
pub const RGB565: u32 = 4;
pub const RGB5A3: u32 = 5;
pub const RGBA8: u32 = 6;
pub const CI4: u32 = 8;
pub const CI8: u32 = 9;
pub const CI14X2: u32 = 10;
pub const CMPR: u32 = 14;

pub const FORMATS: [u32; 11] = [
    I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8, CI4, CI8, CI14X2, CMPR,
];

pub type Rgba = [u8; 4];

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Image {
    pub width: usize,
    pub height: usize,
    pub pixels: Vec<Rgba>,
}

impl Image {
    pub fn new(width: usize, height: usize) -> Self {
        Self {
            width,
            height,
            pixels: vec![[0; 4]; width * height],
        }
    }

    pub fn get(&self, x: usize, y: usize) -> Rgba {
        self.pixels[y * self.width + x]
    }

    pub fn set(&mut self, x: usize, y: usize, value: Rgba) {
        self.pixels[y * self.width + x] = value;
    }

    pub fn bytes(&self) -> Vec<u8> {
        self.pixels.iter().flatten().copied().collect()
    }
}

/// Block width, block height and bits per pixel, or None for an unknown format.
pub fn block(fmt: u32) -> Option<(usize, usize, usize)> {
    Some(match fmt {
        I4 | CI4 | CMPR => (8, 8, 4),
        I8 | IA4 | CI8 => (8, 4, 8),
        IA8 | RGB565 | RGB5A3 | CI14X2 => (4, 4, 16),
        RGBA8 => (4, 4, 32),
        _ => return None,
    })
}

pub fn name(fmt: u32) -> Option<&'static str> {
    Some(match fmt {
        I4 => "I4",
        I8 => "I8",
        IA4 => "IA4",
        IA8 => "IA8",
        RGB565 => "RGB565",
        RGB5A3 => "RGB5A3",
        RGBA8 => "RGBA8",
        CI4 => "CI4",
        CI8 => "CI8",
        CI14X2 => "CI14X2",
        CMPR => "CMPR",
        _ => return None,
    })
}

fn known(fmt: u32) -> Result<(usize, usize, usize)> {
    match block(fmt) {
        Some(found) => Ok(found),
        None => bail!("format {fmt}"),
    }
}

pub fn padded(width: usize, height: usize, fmt: u32) -> Result<(usize, usize)> {
    let (bw, bh, _) = known(fmt)?;
    Ok((width.div_ceil(bw) * bw, height.div_ceil(bh) * bh))
}

pub fn size(width: usize, height: usize, fmt: u32) -> Result<usize> {
    let (pw, ph) = padded(width, height, fmt)?;
    Ok(pw * ph * known(fmt)?.2 / 8)
}

pub fn untile(values: &[Rgba], width: usize, height: usize, fmt: u32) -> Result<Image> {
    let (bw, bh, _) = known(fmt)?;
    let (pw, ph) = padded(width, height, fmt)?;
    ensure!(
        values.len() == pw * ph,
        "{} pixels cannot fill a {pw}x{ph} texture",
        values.len()
    );
    let across = pw / bw;
    let mut image = Image::new(width, height);
    for y in 0..height {
        for x in 0..width {
            let tile = (y / bh) * across + x / bw;
            image.pixels[y * width + x] = values[tile * bw * bh + (y % bh) * bw + x % bw];
        }
    }
    Ok(image)
}

pub fn tile(image: &Image, fmt: u32) -> Result<Vec<Rgba>> {
    let (bw, bh, _) = known(fmt)?;
    let (pw, ph) = padded(image.width, image.height, fmt)?;
    ensure!(image.width > 0 && image.height > 0, "empty image");
    let mut out = Vec::with_capacity(pw * ph);
    for ty in (0..ph).step_by(bh) {
        for tx in (0..pw).step_by(bw) {
            for y in ty..ty + bh {
                for x in tx..tx + bw {
                    out.push(image.get(x.min(image.width - 1), y.min(image.height - 1)));
                }
            }
        }
    }
    Ok(out)
}

fn rgb565(value: i32) -> [i32; 4] {
    let r = (value >> 11) & 31;
    let g = (value >> 5) & 63;
    let b = value & 31;
    [
        (r << 3) | (r >> 2),
        (g << 2) | (g >> 4),
        (b << 3) | (b >> 2),
        255,
    ]
}

fn rgb5a3(value: i32) -> [i32; 4] {
    if value & 0x8000 != 0 {
        let (r, g, b) = ((value >> 10) & 31, (value >> 5) & 31, value & 31);
        [
            (r << 3) | (r >> 2),
            (g << 3) | (g >> 2),
            (b << 3) | (b >> 2),
            255,
        ]
    } else {
        let a = (value >> 12) & 7;
        [
            ((value >> 8) & 15) * 17,
            ((value >> 4) & 15) * 17,
            (value & 15) * 17,
            (a << 5) | (a << 2) | (a >> 1),
        ]
    }
}

fn ia8(value: i32) -> [i32; 4] {
    let i = value & 255;
    [i, i, i, value >> 8]
}

fn narrow(value: [i32; 4]) -> Rgba {
    value.map(|channel| channel as u8)
}

fn words(data: &[u8]) -> impl Iterator<Item = i32> + '_ {
    data.as_chunks::<2>()
        .0
        .iter()
        .map(|pair| i32::from(u16::from_be_bytes([pair[0], pair[1]])))
}

pub fn palette(data: &[u8], fmt: u32, count: usize) -> Result<Vec<Rgba>> {
    let convert = match fmt {
        0 => ia8,
        1 => rgb565,
        2 => rgb5a3,
        _ => bail!("palette format {fmt}"),
    };
    let data = &data[..data.len().min(count * 2)];
    ensure!(
        data.len().is_multiple_of(2),
        "palette has an odd byte count"
    );
    Ok(words(data).map(|value| narrow(convert(value))).collect())
}

fn nibbles(data: &[u8]) -> impl Iterator<Item = u8> + '_ {
    data.iter().flat_map(|&raw| [raw >> 4, raw & 15])
}

pub fn decode(
    data: &[u8],
    width: usize,
    height: usize,
    fmt: u32,
    tlut: Option<&[Rgba]>,
) -> Result<Image> {
    let data = &data[..data.len().min(size(width, height, fmt)?)];
    let grey = |i: u8| [i, i, i, 255];
    let rgba: Vec<Rgba> = match fmt {
        I4 => nibbles(data).map(|i| grey(i * 17)).collect(),
        I8 => data.iter().map(|&i| grey(i)).collect(),
        IA4 => data
            .iter()
            .map(|&raw| {
                let i = (raw & 15) * 17;
                [i, i, i, (raw >> 4) * 17]
            })
            .collect(),
        IA8 => words(data).map(|value| narrow(ia8(value))).collect(),
        RGB565 => words(data).map(|value| narrow(rgb565(value))).collect(),
        RGB5A3 => words(data).map(|value| narrow(rgb5a3(value))).collect(),
        RGBA8 => data
            .as_chunks::<64>()
            .0
            .iter()
            .flat_map(|raw| {
                (0..16).map(move |i| {
                    [
                        raw[i * 2 + 1],
                        raw[32 + i * 2],
                        raw[32 + i * 2 + 1],
                        raw[i * 2],
                    ]
                })
            })
            .collect(),
        CI4 | CI8 | CI14X2 => {
            let index: Vec<usize> = match fmt {
                CI4 => nibbles(data).map(usize::from).collect(),
                CI8 => data.iter().map(|&i| usize::from(i)).collect(),
                _ => words(data).map(|value| (value & 0x3FFF) as usize).collect(),
            };
            match tlut {
                Some(colors) => {
                    ensure!(!colors.is_empty(), "empty palette");
                    index
                        .iter()
                        .map(|&i| colors[i.min(colors.len() - 1)])
                        .collect()
                }
                None => index.iter().map(|&i| grey(i.min(255) as u8)).collect(),
            }
        }
        CMPR => decode_cmpr(data)?,
        _ => bail!("format {fmt}"),
    };
    untile(&rgba, width, height, fmt)
}

fn cmpr_colors(c0: i32, c1: i32) -> [[i32; 4]; 4] {
    let (p0, p1) = (rgb565(c0), rgb565(c1));
    let mut p2 = [0, 0, 0, 255];
    let mut p3 = [0; 4];
    if c0 > c1 {
        for channel in 0..3 {
            p2[channel] = (2 * p0[channel] + p1[channel]) / 3;
            p3[channel] = (p0[channel] + 2 * p1[channel]) / 3;
        }
        p3[3] = 255;
    } else {
        for channel in 0..3 {
            p2[channel] = (p0[channel] + p1[channel]) / 2;
        }
    }
    [p0, p1, p2, p3]
}

pub fn decode_cmpr(data: &[u8]) -> Result<Vec<Rgba>> {
    ensure!(
        data.len().is_multiple_of(32),
        "CMPR data is not whole 8x8 tiles"
    );
    let mut out = vec![[0u8; 4]; data.len() * 2];
    for (tile, raw) in data.as_chunks::<32>().0.iter().enumerate() {
        for (sub, block) in raw.as_chunks::<8>().0.iter().enumerate() {
            let c0 = (i32::from(block[0]) << 8) | i32::from(block[1]);
            let c1 = (i32::from(block[2]) << 8) | i32::from(block[3]);
            let colors = cmpr_colors(c0, c1);
            for y in 0..4 {
                for x in 0..4 {
                    let index = (block[4 + y] >> (6 - 2 * x)) & 3;
                    let at = tile * 64 + (sub / 2 * 4 + y) * 8 + sub % 2 * 4 + x;
                    out[at] = narrow(colors[usize::from(index)]);
                }
            }
        }
    }
    Ok(out)
}

fn to565(rgb: [i32; 3]) -> i32 {
    ((rgb[0] >> 3) << 11) | ((rgb[1] >> 2) << 5) | (rgb[2] >> 3)
}

fn cmpr_block(block: &[[i32; 4]; 16]) -> [u8; 8] {
    let transparent = block.map(|pixel| pixel[3] < 128);
    let any_transparent = transparent.contains(&true);
    let all_transparent = !transparent.contains(&false);
    let solid: Vec<[i32; 3]> = block
        .iter()
        .zip(transparent)
        .filter(|&(_, clear)| all_transparent || !clear)
        .map(|(pixel, _)| [pixel[0], pixel[1], pixel[2]])
        .collect();
    let mut axis = [0i32; 3];
    for (channel, span) in axis.iter_mut().enumerate() {
        let lo = solid.iter().map(|pixel| pixel[channel]).min().unwrap_or(0);
        let hi = solid.iter().map(|pixel| pixel[channel]).max().unwrap_or(0);
        *span = hi - lo;
    }
    let (mut first, mut last) = (0, 0);
    let mut best = (i32::MIN, i32::MAX);
    for (index, pixel) in solid.iter().enumerate() {
        let projection = pixel[0] * axis[0] + pixel[1] * axis[1] + pixel[2] * axis[2];
        if projection > best.0 {
            best.0 = projection;
            first = index;
        }
        if projection < best.1 {
            best.1 = projection;
            last = index;
        }
    }
    let (mut c0, mut c1) = (to565(solid[first]), to565(solid[last]));
    if any_transparent {
        if c0 > c1 {
            std::mem::swap(&mut c0, &mut c1);
        }
    } else if c0 < c1 {
        std::mem::swap(&mut c0, &mut c1);
    } else if c0 == c1 {
        if c0 == 0 {
            c0 = 1;
            c1 = 0;
        } else {
            c1 = c0 - 1;
        }
    }
    let colors = cmpr_colors(c0, c1);
    let choices = if c0 > c1 { 4 } else { 3 };
    let mut bits = 0u32;
    for (pixel, clear) in block.iter().zip(transparent) {
        let mut index = 0;
        let mut nearest = i64::MAX;
        for (candidate, color) in colors.iter().take(choices).enumerate() {
            let distance: i64 = (0..3)
                .map(|channel| i64::from(pixel[channel] - color[channel]).pow(2))
                .sum();
            if distance < nearest {
                nearest = distance;
                index = candidate as u32;
            }
        }
        bits = (bits << 2) | if clear { 3 } else { index };
    }
    let mut out = [0u8; 8];
    out[0..2].copy_from_slice(&(c0 as u16).to_be_bytes());
    out[2..4].copy_from_slice(&(c1 as u16).to_be_bytes());
    out[4..8].copy_from_slice(&bits.to_be_bytes());
    out
}

pub fn encode_cmpr(image: &Image) -> Result<Vec<u8>> {
    let pixels = tile(image, CMPR)?;
    let mut out = Vec::with_capacity(pixels.len() / 2);
    for tile in pixels.as_chunks::<64>().0 {
        for sub in 0..4 {
            let mut block = [[0i32; 4]; 16];
            for (index, pixel) in block.iter_mut().enumerate() {
                let at = (sub / 2 * 4 + index / 4) * 8 + sub % 2 * 4 + index % 4;
                *pixel = tile[at].map(i32::from);
            }
            out.extend_from_slice(&cmpr_block(&block));
        }
    }
    Ok(out)
}

fn nearest(pixel: [i32; 4], tlut: &[Rgba]) -> usize {
    let mut index = 0;
    let mut best = i32::MAX;
    for (candidate, color) in tlut.iter().enumerate() {
        let distance: i32 = (0..4)
            .map(|channel| (pixel[channel] - i32::from(color[channel])).pow(2))
            .sum();
        if distance < best {
            best = distance;
            index = candidate;
        }
    }
    index
}

pub fn encode(image: &Image, fmt: u32, tlut: Option<&[Rgba]>) -> Result<Vec<u8>> {
    if fmt == CMPR {
        return encode_cmpr(image);
    }
    let pixels: Vec<[i32; 4]> = tile(image, fmt)?
        .iter()
        .map(|pixel| pixel.map(i32::from))
        .collect();
    let intensity = |p: &[i32; 4]| (p[0] * 30 + p[1] * 59 + p[2] * 11) / 100;
    let wide = |values: Vec<i32>| -> Vec<u8> {
        values
            .iter()
            .flat_map(|&value| (value as u16).to_be_bytes())
            .collect()
    };
    Ok(match fmt {
        I4 => pixels
            .as_chunks::<2>()
            .0
            .iter()
            .map(|pair| {
                let v = [
                    (intensity(&pair[0]) + 8) / 17,
                    (intensity(&pair[1]) + 8) / 17,
                ];
                ((v[0] << 4) | v[1]) as u8
            })
            .collect(),
        I8 => pixels.iter().map(|p| intensity(p) as u8).collect(),
        IA4 => pixels
            .iter()
            .map(|p| ((((p[3] + 8) / 17) << 4) | ((intensity(p) + 8) / 17)) as u8)
            .collect(),
        IA8 => wide(pixels.iter().map(|p| (p[3] << 8) | intensity(p)).collect()),
        RGB565 => wide(pixels.iter().map(|p| to565([p[0], p[1], p[2]])).collect()),
        RGB5A3 => wide(
            pixels
                .iter()
                .map(|p| {
                    if p[3] >= 224 {
                        0x8000 | ((p[0] >> 3) << 10) | ((p[1] >> 3) << 5) | (p[2] >> 3)
                    } else {
                        ((p[3] >> 5) << 12) | ((p[0] >> 4) << 8) | ((p[1] >> 4) << 4) | (p[2] >> 4)
                    }
                })
                .collect(),
        ),
        RGBA8 => pixels
            .as_chunks::<16>()
            .0
            .iter()
            .flat_map(|block| {
                let ar = block.iter().flat_map(|p| [p[3] as u8, p[0] as u8]);
                let gb = block.iter().flat_map(|p| [p[1] as u8, p[2] as u8]);
                ar.chain(gb).collect::<Vec<u8>>()
            })
            .collect(),
        CI4 | CI8 => {
            let Some(tlut) = tlut else {
                bail!("cannot encode format {fmt} without a palette");
            };
            ensure!(!tlut.is_empty(), "empty palette");
            let index: Vec<usize> = pixels.iter().map(|&p| nearest(p, tlut)).collect();
            if fmt == CI8 {
                index.iter().map(|&i| i as u8).collect()
            } else {
                index
                    .as_chunks::<2>()
                    .0
                    .iter()
                    .map(|pair| ((pair[0] << 4) | pair[1]) as u8)
                    .collect()
            }
        }
        _ => bail!("cannot encode format {fmt}"),
    })
}
