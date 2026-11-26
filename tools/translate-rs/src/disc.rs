use anyhow::{anyhow, bail, Context, Result};
use std::collections::BTreeMap;
use std::fs::File;
use std::io::{Read, Seek, SeekFrom};
use std::path::Path;

fn be32(data: &[u8], at: usize) -> u32 {
    u32::from_be_bytes([data[at], data[at + 1], data[at + 2], data[at + 3]])
}

fn read_at(iso: &Path, offset: u64, size: usize) -> Result<Vec<u8>> {
    let mut file = File::open(iso).with_context(|| format!("open {}", iso.display()))?;
    file.seek(SeekFrom::Start(offset))?;
    let mut data = vec![0; size];
    file.read_exact(&mut data)?;
    Ok(data)
}

/// Raw FST bytes with the disc offset they start at.
pub fn raw_fst(iso: &Path) -> Result<(u64, Vec<u8>)> {
    let header = read_at(iso, 0, 0x440)?;
    let offset = u64::from(be32(&header, 0x424));
    let size = be32(&header, 0x428) as usize;
    Ok((offset, read_at(iso, offset, size)?))
}

/// One FST entry: index, full path, and for files the data offset and size.
pub struct Entry {
    pub index: usize,
    pub path: String,
    pub directory: bool,
    pub offset: u32,
    pub size: u32,
}

pub fn fst_entries(fst: &[u8]) -> Result<Vec<Entry>> {
    let count = be32(fst, 8) as usize;
    let strings = &fst[count * 12..];
    let mut entries = Vec::new();
    let mut stack: Vec<(usize, String)> = vec![(count, String::new())];
    for index in 1..count {
        let word = be32(fst, index * 12);
        let offset = be32(fst, index * 12 + 4);
        let size = be32(fst, index * 12 + 8);
        while stack.last().is_some_and(|top| index >= top.0) {
            stack.pop();
        }
        let start = (word & 0x00FF_FFFF) as usize;
        let end = start
            + strings[start..]
                .iter()
                .position(|&b| b == 0)
                .ok_or_else(|| anyhow!("unterminated FST name"))?;
        let (name, _, bad) = encoding_rs::SHIFT_JIS.decode(&strings[start..end]);
        if bad {
            bail!("FST name at {start} is not Shift-JIS");
        }
        let prefix = stack.last().map(|top| top.1.clone()).unwrap_or_default();
        let directory = word >> 24 != 0;
        if directory {
            stack.push((size as usize, format!("{prefix}{name}/")));
        }
        entries.push(Entry {
            index,
            path: format!("{prefix}{name}"),
            directory,
            offset,
            size,
        });
    }
    Ok(entries)
}

/// File path to (offset, size), as disc.read_fst returned.
pub fn read_fst(iso: &Path) -> Result<BTreeMap<String, (u32, u32)>> {
    let (_, fst) = raw_fst(iso)?;
    Ok(fst_entries(&fst)?
        .into_iter()
        .filter(|entry| !entry.directory)
        .map(|entry| (entry.path, (entry.offset, entry.size)))
        .collect())
}

pub fn read_file(iso: &Path, path: &str) -> Result<Vec<u8>> {
    let files = read_fst(iso)?;
    let &(offset, size) = files
        .get(path)
        .ok_or_else(|| anyhow!("{path} is not on the disc"))?;
    read_at(iso, u64::from(offset), size as usize)
}

pub fn dol_offset(iso: &Path) -> Result<u64> {
    Ok(u64::from(be32(&read_at(iso, 0x420, 4)?, 0)))
}

pub fn read_dol(iso: &Path) -> Result<Vec<u8>> {
    let start = dol_offset(iso)?;
    let header = read_at(iso, start, 0x100)?;
    let end = (0..18)
        .filter(|&i| be32(&header, 144 + i * 4) != 0)
        .map(|i| be32(&header, i * 4) + be32(&header, 144 + i * 4))
        .max()
        .ok_or_else(|| anyhow!("empty DOL"))?;
    read_at(iso, start, end as usize)
}

fn dol_range(dol: &[u8], address: u32, size: usize) -> Option<usize> {
    (0..18).find_map(|i| {
        let offset = be32(dol, i * 4);
        let base = be32(dol, 72 + i * 4);
        let length = be32(dol, 144 + i * 4);
        (length != 0
            && base <= address
            && u64::from(address) + size as u64 <= u64::from(base) + u64::from(length))
        .then(|| (offset + address - base) as usize)
    })
}

pub fn dol_read(dol: &[u8], address: u32, size: usize) -> Result<&[u8]> {
    let start = dol_range(dol, address, 1)
        .ok_or_else(|| anyhow!("address {address:08X} is not in the DOL"))?;
    Ok(&dol[start..(start + size).min(dol.len())])
}

pub fn dol_write(dol: &mut [u8], address: u32, data: &[u8]) -> Result<()> {
    let start = dol_range(dol, address, data.len())
        .ok_or_else(|| anyhow!("address {address:08X} is not in the DOL"))?;
    dol[start..start + data.len()].copy_from_slice(data);
    Ok(())
}
