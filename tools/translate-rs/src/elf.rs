use anyhow::{anyhow, bail, Result};
use std::collections::HashMap;
use std::path::Path;

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub struct Section {
    pub name: String,
    pub kind: u32,
    pub flags: u32,
    pub address: u32,
    pub offset: u32,
    pub size: u32,
    pub link: u32,
    pub info: u32,
    pub alignment: u32,
    pub entry_size: u32,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct Symbol {
    pub name: String,
    pub address: u32,
    pub size: u32,
    pub info: u8,
    pub section: usize,
}

impl Symbol {
    pub fn kind(&self) -> u8 {
        self.info & 15
    }

    pub fn binding(&self) -> u8 {
        self.info >> 4
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct Relocation {
    pub section: usize,
    pub address: u32,
    pub kind: u32,
    pub symbol: usize,
    pub addend: i32,
}

pub struct Elf {
    pub data: Vec<u8>,
    pub kind: u16,
    pub sections: Vec<Section>,
    pub symbols: Vec<Symbol>,
    pub relocations: Vec<Relocation>,
    functions: Vec<Symbol>,
    names: HashMap<String, Vec<usize>>,
}

fn be16(data: &[u8], at: usize) -> Result<u16> {
    let bytes = data
        .get(at..at + 2)
        .ok_or_else(|| anyhow!("ELF read past the end at {at:#X}"))?;
    Ok(u16::from_be_bytes([bytes[0], bytes[1]]))
}

fn be32(data: &[u8], at: usize) -> Result<u32> {
    let bytes = data
        .get(at..at + 4)
        .ok_or_else(|| anyhow!("ELF read past the end at {at:#X}"))?;
    Ok(u32::from_be_bytes([bytes[0], bytes[1], bytes[2], bytes[3]]))
}

fn clamped(data: &[u8], start: usize, size: usize) -> &[u8] {
    let start = start.min(data.len());
    let end = start.saturating_add(size).min(data.len());
    &data[start..end]
}

fn string(data: &[u8], offset: usize) -> Result<String> {
    let tail = data.get(offset..).unwrap_or(&[]);
    let end = tail.iter().position(|&b| b == 0).unwrap_or(tail.len());
    if !tail[..end].is_ascii() {
        bail!("ELF name is not ASCII.");
    }
    Ok(String::from_utf8_lossy(&tail[..end]).into_owned())
}

impl Elf {
    pub fn new(data: Vec<u8>) -> Result<Self> {
        if data.get(..7) != Some(b"\x7fELF\x01\x02\x01") {
            bail!("Expected a big-endian ELF32 file.");
        }
        let kind = be16(&data, 16)?;
        if be16(&data, 18)? != 20 {
            bail!("Expected PowerPC machine code.");
        }
        let table_offset = be32(&data, 32)? as usize;
        let entry_size = be16(&data, 46)? as usize;
        let count = be16(&data, 48)? as usize;
        let names_index = be16(&data, 50)? as usize;
        let mut entries = Vec::with_capacity(count);
        for index in 0..count {
            let mut entry = [0u32; 10];
            for (field, value) in entry.iter_mut().enumerate() {
                *value = be32(&data, table_offset + index * entry_size + field * 4)?;
            }
            entries.push(entry);
        }
        let names = entries
            .get(names_index)
            .ok_or_else(|| anyhow!("ELF has no section name table."))?;
        let strings = clamped(&data, names[4] as usize, names[5] as usize);
        let sections = entries
            .iter()
            .map(|entry| {
                Ok(Section {
                    name: string(strings, entry[0] as usize)?,
                    kind: entry[1],
                    flags: entry[2],
                    address: entry[3],
                    offset: entry[4],
                    size: entry[5],
                    link: entry[6],
                    info: entry[7],
                    alignment: entry[8],
                    entry_size: entry[9],
                })
            })
            .collect::<Result<Vec<_>>>()?;
        let table = sections
            .iter()
            .find(|section| section.kind == 2)
            .ok_or_else(|| anyhow!("ELF has no symbol table."))?;
        let names = sections
            .get(table.link as usize)
            .ok_or_else(|| anyhow!("ELF symbol table has no string table."))?;
        if names.kind == 8 {
            bail!("BSS has no file bytes.");
        }
        let strings = clamped(&data, names.offset as usize, names.size as usize);
        let mut symbols = Vec::with_capacity(table.size as usize / 16);
        for offset in (table.offset as usize..(table.offset + table.size) as usize).step_by(16) {
            symbols.push(Symbol {
                name: string(strings, be32(&data, offset)? as usize)?,
                address: be32(&data, offset + 4)?,
                size: be32(&data, offset + 8)?,
                info: data[offset + 12],
                section: be16(&data, offset + 14)? as usize,
            });
        }
        let mut relocations = Vec::new();
        for section in &sections {
            if section.kind != 4 {
                continue;
            }
            let start = section.offset as usize;
            for offset in (start..start + section.size as usize).step_by(12) {
                let info = be32(&data, offset + 4)?;
                relocations.push(Relocation {
                    section: section.info as usize,
                    address: be32(&data, offset)?,
                    kind: info & 255,
                    symbol: (info >> 8) as usize,
                    addend: be32(&data, offset + 8)? as i32,
                });
            }
        }
        let functions = symbols
            .iter()
            .filter(|symbol| {
                symbol.kind() == 2
                    && symbol.size != 0
                    && 0 < symbol.section
                    && symbol.section < sections.len()
                    && sections[symbol.section].flags & 4 != 0
            })
            .cloned()
            .collect();
        let mut names: HashMap<String, Vec<usize>> = HashMap::new();
        for (index, symbol) in symbols.iter().enumerate() {
            names.entry(symbol.name.clone()).or_default().push(index);
        }
        Ok(Self {
            data,
            kind,
            sections,
            symbols,
            relocations,
            functions,
            names,
        })
    }

    pub fn read(path: &Path) -> Result<Self> {
        Self::new(std::fs::read(path).map_err(|error| anyhow!("{}: {error}", path.display()))?)
    }

    pub fn section_data(&self, section: &Section) -> Result<&[u8]> {
        if section.kind == 8 {
            bail!("BSS has no file bytes.");
        }
        Ok(clamped(
            &self.data,
            section.offset as usize,
            section.size as usize,
        ))
    }

    pub fn symbol_data(&self, symbol: &Symbol) -> Result<&[u8]> {
        let section = self
            .sections
            .get(symbol.section)
            .ok_or_else(|| anyhow!("Symbol has no section: {}", symbol.name))?;
        let base = if self.kind == 2 { section.address } else { 0 };
        let offset = i64::from(symbol.address) - i64::from(base);
        if offset < 0 || offset + i64::from(symbol.size) > i64::from(section.size) {
            bail!("Symbol exceeds its section: {}", symbol.name);
        }
        Ok(clamped(
            self.section_data(section)?,
            offset as usize,
            symbol.size as usize,
        ))
    }

    pub fn functions(&self) -> &[Symbol] {
        &self.functions
    }

    pub fn named(&self, name: &str) -> Vec<&Symbol> {
        self.names
            .get(name)
            .map(|indices| indices.iter().map(|&index| &self.symbols[index]).collect())
            .unwrap_or_default()
    }
}
