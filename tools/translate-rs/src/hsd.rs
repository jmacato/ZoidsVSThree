use crate::gx;
use anyhow::{anyhow, ensure, Result};
use std::collections::{BTreeMap, BTreeSet};

pub const HEADER: usize = 0x20;

#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct Texture {
    pub desc: usize,
    pub image: usize,
    pub width: usize,
    pub height: usize,
    pub format: u32,
    pub tlut: usize,
    pub tlut_format: u32,
    pub tlut_count: usize,
}

pub struct Archive {
    pub data: Vec<u8>,
    pub file_size: usize,
    pub data_size: usize,
    pub reloc_count: usize,
    pub relocs: BTreeSet<usize>,
}

fn be32(bytes: &[u8]) -> u32 {
    u32::from_be_bytes([bytes[0], bytes[1], bytes[2], bytes[3]])
}

fn be16(bytes: &[u8]) -> u16 {
    u16::from_be_bytes([bytes[0], bytes[1]])
}

impl Archive {
    pub fn new(data: Vec<u8>) -> Result<Self> {
        ensure!(data.len() >= 12, "archive is shorter than its header");
        let file_size = be32(&data[0..]) as usize;
        let data_size = be32(&data[4..]) as usize;
        let reloc_count = be32(&data[8..]) as usize;
        let table = HEADER + data_size;
        let end = table + 4 * reloc_count;
        ensure!(end <= data.len(), "relocation table runs past the archive");
        let relocs = data[table..end]
            .as_chunks::<4>()
            .0
            .iter()
            .map(|word| be32(word) as usize)
            .collect();
        Ok(Self {
            data,
            file_size,
            data_size,
            reloc_count,
            relocs,
        })
    }

    /// Bytes at a data-section offset; fails when the range leaves the file.
    pub fn bytes(&self, offset: usize, size: usize) -> Result<&[u8]> {
        self.data
            .get(HEADER + offset..HEADER + offset + size)
            .ok_or_else(|| anyhow!("offset {offset:#x}+{size} is outside the archive"))
    }

    pub fn word(&self, offset: usize) -> Result<u32> {
        Ok(be32(self.bytes(offset, 4)?))
    }

    pub fn half(&self, offset: usize) -> Result<u16> {
        Ok(be16(self.bytes(offset, 2)?))
    }

    pub fn float(&self, offset: usize) -> Result<f32> {
        Ok(f32::from_bits(self.word(offset)?))
    }

    pub fn pointer(&self, offset: usize) -> Result<Option<usize>> {
        if self.relocs.contains(&offset) {
            Ok(Some(self.word(offset)? as usize))
        } else {
            Ok(None)
        }
    }

    pub fn image_desc(&self, offset: usize) -> Result<Option<Texture>> {
        if offset + 0x18 > self.data_size || !self.relocs.contains(&offset) {
            return Ok(None);
        }
        let image = self.word(offset)? as usize;
        let width = usize::from(self.half(offset + 4)?);
        let height = usize::from(self.half(offset + 6)?);
        let format = self.word(offset + 8)?;
        if gx::block(format).is_none()
            || !(0 < width && width <= 1024 && 0 < height && height <= 1024)
            || width % 4 != 0
            || height % 4 != 0
        {
            return Ok(None);
        }
        let mipmap = self.word(offset + 12)?;
        let min_lod = self.float(offset + 16)?;
        let max_lod = self.float(offset + 20)?;
        if mipmap > 1 || !((0.0..=16.0).contains(&min_lod) && (0.0..=16.0).contains(&max_lod)) {
            return Ok(None);
        }
        if image + gx::size(width, height, format)? > self.data_size {
            return Ok(None);
        }
        Ok(Some(Texture {
            desc: offset,
            image,
            width,
            height,
            format,
            ..Texture::default()
        }))
    }

    /// Palette data offset, format and entry count.
    pub fn tlut_desc(&self, offset: Option<usize>) -> Result<Option<(usize, u32, usize)>> {
        let Some(offset) = offset else {
            return Ok(None);
        };
        if !self.relocs.contains(&offset) || offset + 14 > self.data_size {
            return Ok(None);
        }
        let format = self.word(offset + 4)?;
        let count = usize::from(self.half(offset + 12)?);
        if format > 2 || !(0 < count && count <= 16384) {
            return Ok(None);
        }
        Ok(Some((self.word(offset)? as usize, format, count)))
    }

    pub fn textures(&self) -> Result<Vec<Texture>> {
        let mut found: BTreeMap<usize, Texture> = BTreeMap::new();
        for &site in &self.relocs {
            if let Some(texture) = self.image_desc(site)? {
                found.entry(texture.image).or_insert(texture);
            }
        }
        for &site in &self.relocs {
            let Some(texture) = self.image_desc(self.word(site)? as usize)? else {
                continue;
            };
            if ![gx::CI4, gx::CI8, gx::CI14X2].contains(&texture.format) {
                continue;
            }
            let tlut = self.tlut_desc(self.pointer(site + 4)?)?;
            let current = found
                .get_mut(&texture.image)
                .ok_or_else(|| anyhow!("texture {:#x} was not indexed", texture.image))?;
            if let Some((tlut, tlut_format, tlut_count)) = tlut {
                if current.tlut_count == 0 {
                    current.tlut = tlut;
                    current.tlut_format = tlut_format;
                    current.tlut_count = tlut_count;
                }
            }
        }
        Ok(found.into_values().collect())
    }

    fn clamped(&self, start: usize, size: usize) -> &[u8] {
        let start = start.min(self.data.len());
        &self.data[start..(start + size).min(self.data.len())]
    }

    pub fn palette(&self, texture: &Texture) -> Result<Vec<gx::Rgba>> {
        let raw = self.clamped(HEADER + texture.tlut, texture.tlut_count * 2);
        gx::palette(raw, texture.tlut_format, texture.tlut_count)
    }

    fn tlut(&self, texture: &Texture) -> Result<Option<Vec<gx::Rgba>>> {
        if texture.tlut_count == 0 {
            return Ok(None);
        }
        self.palette(texture).map(Some)
    }

    pub fn decode(&self, texture: &Texture) -> Result<gx::Image> {
        let size = gx::size(texture.width, texture.height, texture.format)?;
        let raw = self.clamped(HEADER + texture.image, size);
        let tlut = self.tlut(texture)?;
        gx::decode(
            raw,
            texture.width,
            texture.height,
            texture.format,
            tlut.as_deref(),
        )
    }

    /// File offset of the texture data and the image encoded in the texture's format.
    pub fn encoded(&self, texture: &Texture, image: &gx::Image) -> Result<(usize, Vec<u8>)> {
        let tlut = self.tlut(texture)?;
        Ok((
            HEADER + texture.image,
            gx::encode(image, texture.format, tlut.as_deref())?,
        ))
    }
}
