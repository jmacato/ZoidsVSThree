use crate::hsd::{Archive, HEADER};
use anyhow::{anyhow, bail, Result};

pub const GX_VA_POS: u32 = 9;
pub const GX_VA_TEX0: u32 = 13;
pub const GX_VA_NULL: u32 = 0xFF;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Primitive {
    Quads,
    Triangles,
    Strip,
    Fan,
}

impl Primitive {
    pub fn from_opcode(op: u8) -> Option<Self> {
        Some(match op {
            0x80 => Self::Quads,
            0x90 => Self::Triangles,
            0x98 => Self::Strip,
            0xA0 => Self::Fan,
            _ => return None,
        })
    }

    pub fn name(self) -> &'static str {
        match self {
            Self::Quads => "quads",
            Self::Triangles => "triangles",
            Self::Strip => "strip",
            Self::Fan => "fan",
        }
    }
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Attribute {
    pub attr: u32,
    pub kind: u32,
    pub count: u32,
    pub comp: u32,
    pub frac: u8,
    pub stride: usize,
    pub array: Option<usize>,
}

/// One indexed attribute of a vertex: the Python tuple (index, values, attr).
#[derive(Clone, Debug, PartialEq)]
pub struct Element {
    pub index: usize,
    pub values: Vec<f64>,
    pub attr: Attribute,
}

/// The Python vertex dict, which only ever holds GX_VA_POS and GX_VA_TEX0.
#[derive(Clone, Debug, Default, PartialEq)]
pub struct Vertex {
    pub pos: Option<Element>,
    pub tex0: Option<Element>,
}

impl Vertex {
    pub fn get(&self, attr: u32) -> Option<&Element> {
        match attr {
            GX_VA_POS => self.pos.as_ref(),
            GX_VA_TEX0 => self.tex0.as_ref(),
            _ => None,
        }
    }

    pub fn contains(&self, attr: u32) -> bool {
        self.get(attr).is_some()
    }
}

pub struct Geometry<'a> {
    pub archive: &'a Archive,
}

impl<'a> Geometry<'a> {
    pub fn new(archive: &'a Archive) -> Self {
        Self { archive }
    }

    pub fn word(&self, offset: usize) -> Result<u32> {
        self.archive.word(offset)
    }

    pub fn ptr(&self, offset: usize) -> Result<Option<usize>> {
        self.archive.pointer(offset)
    }

    pub fn floats(&self, offset: usize, count: usize) -> Result<Vec<f32>> {
        Ok(self
            .archive
            .bytes(offset, count * 4)?
            .as_chunks::<4>()
            .0
            .iter()
            .map(|raw| f32::from_be_bytes([raw[0], raw[1], raw[2], raw[3]]))
            .collect())
    }

    /// (model index, root joint) for every model of the scene that has a joint.
    pub fn models(&self, scene: usize) -> Result<Vec<(usize, usize)>> {
        let mut found = Vec::new();
        let Some(table) = self.ptr(scene)? else {
            return Ok(found);
        };
        let mut index = 0;
        while let Some(model) = self.ptr(table + index * 4)? {
            if let Some(joint) = self.ptr(model)? {
                found.push((index, joint));
            }
            index += 1;
        }
        Ok(found)
    }

    /// (path, joint) in depth-first order, starting at `joint` and its siblings.
    pub fn joints(&self, joint: Option<usize>, path: &[usize]) -> Result<Vec<(Vec<usize>, usize)>> {
        let mut found = Vec::new();
        self.walk(joint, path, &mut found)?;
        Ok(found)
    }

    fn walk(
        &self,
        mut joint: Option<usize>,
        path: &[usize],
        found: &mut Vec<(Vec<usize>, usize)>,
    ) -> Result<()> {
        let mut index = 0;
        while let Some(current) = joint {
            let mut here = path.to_vec();
            here.push(index);
            found.push((here.clone(), current));
            self.walk(self.ptr(current + 0x08)?, &here, found)?;
            joint = self.ptr(current + 0x0C)?;
            index += 1;
        }
        Ok(())
    }

    fn chain(&self, mut item: Option<usize>) -> Result<Vec<usize>> {
        let mut found = Vec::new();
        while let Some(current) = item {
            found.push(current);
            item = self.ptr(current + 0x04)?;
        }
        Ok(found)
    }

    pub fn dobjs(&self, joint: usize) -> Result<Vec<usize>> {
        let flags = self.word(joint + 0x04)?;
        let first = if flags & (1 << 14) == 0 {
            self.ptr(joint + 0x10)?
        } else {
            None
        };
        self.chain(first)
    }

    pub fn images(&self, dobj: usize) -> Result<Vec<usize>> {
        let tobj = match self.ptr(dobj + 0x08)? {
            Some(mobj) => self.ptr(mobj + 0x08)?,
            None => None,
        };
        let mut found = Vec::new();
        for tobj in self.chain(tobj)? {
            if let Some(desc) = self.ptr(tobj + 0x4C)? {
                found.push(self.word(desc)? as usize);
            }
        }
        Ok(found)
    }

    pub fn attributes(&self, pobj: usize) -> Result<Vec<Attribute>> {
        let mut attrs = Vec::new();
        let Some(mut desc) = self.ptr(pobj + 0x08)? else {
            return Ok(attrs);
        };
        loop {
            let attr = self.word(desc)?;
            let kind = self.word(desc + 4)?;
            let count = self.word(desc + 8)?;
            let comp = self.word(desc + 12)?;
            let frac = self.archive.bytes(desc + 16, 1)?[0];
            if attr == GX_VA_NULL {
                break;
            }
            let stride = usize::from(self.archive.half(desc + 18)?);
            let array = self.ptr(desc + 0x14)?;
            attrs.push(Attribute {
                attr,
                kind,
                count,
                comp,
                frac,
                stride,
                array,
            });
            desc += 0x18;
        }
        Ok(attrs)
    }

    pub fn component(&self, attr: &Attribute, index: usize) -> Result<Vec<f64>> {
        let width = match attr.comp {
            0 | 1 => 1,
            2 | 3 => 2,
            4 => 4,
            other => bail!("component type {other}"),
        };
        let n = match attr.attr {
            GX_VA_POS => 2 + attr.count as usize,
            GX_VA_TEX0 => 1 + attr.count as usize,
            _ => 1,
        };
        let array = attr
            .array
            .ok_or_else(|| anyhow!("attribute {} has no array", attr.attr))?;
        let raw = self.archive.bytes(array + index * attr.stride, n * width)?;
        let scale = 2f64.powi(i32::from(attr.frac));
        Ok(raw
            .chunks_exact(width)
            .map(|v| match attr.comp {
                0 => f64::from(v[0]) / scale,
                1 => f64::from(v[0] as i8) / scale,
                2 => f64::from(u16::from_be_bytes([v[0], v[1]])) / scale,
                3 => f64::from(i16::from_be_bytes([v[0], v[1]])) / scale,
                _ => f64::from(f32::from_be_bytes([v[0], v[1], v[2], v[3]])),
            })
            .collect())
    }

    pub fn vertices(&self, pobj: usize) -> Result<Vec<(Primitive, Vec<Vertex>)>> {
        let attrs = self.attributes(pobj)?;
        let start = self
            .ptr(pobj + 0x10)?
            .ok_or_else(|| anyhow!("pobj {pobj:#x} has no display list"))?;
        let length = usize::from(self.archive.half(pobj + 0x0E)?) * 32;
        let all = &self.archive.data;
        let from = (HEADER + start).min(all.len());
        let data = &all[from..(from + length).min(all.len())];
        let short = || anyhow!("pobj {pobj:#x}: display list is cut short");
        let mut cursor = 0;
        let mut prims = Vec::new();
        while cursor < data.len() {
            let Some(primitive) = Primitive::from_opcode(data[cursor]) else {
                break;
            };
            let count = data.get(cursor + 1..cursor + 3).ok_or_else(short)?;
            let count = u16::from_be_bytes([count[0], count[1]]);
            cursor += 3;
            let mut verts = Vec::with_capacity(usize::from(count));
            for _ in 0..count {
                let mut vertex = Vertex::default();
                for attr in &attrs {
                    let index = match attr.kind {
                        2 => {
                            let index = *data.get(cursor).ok_or_else(short)?;
                            cursor += 1;
                            usize::from(index)
                        }
                        3 => {
                            let raw = data.get(cursor..cursor + 2).ok_or_else(short)?;
                            cursor += 2;
                            usize::from(u16::from_be_bytes([raw[0], raw[1]]))
                        }
                        _ => {
                            cursor += 1;
                            continue;
                        }
                    };
                    if attr.attr == GX_VA_POS || attr.attr == GX_VA_TEX0 {
                        let element = Element {
                            index,
                            values: self.component(attr, index)?,
                            attr: attr.clone(),
                        };
                        if attr.attr == GX_VA_POS {
                            vertex.pos = Some(element);
                        } else {
                            vertex.tex0 = Some(element);
                        }
                    }
                }
                verts.push(vertex);
            }
            prims.push((primitive, verts));
        }
        Ok(prims)
    }

    pub fn pobjs(&self, dobj: usize) -> Result<Vec<usize>> {
        self.chain(self.ptr(dobj + 0x0C)?)
    }
}
