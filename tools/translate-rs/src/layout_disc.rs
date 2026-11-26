use crate::cave::{self, Cave};
use crate::{disc, Files};
use anyhow::{anyhow, bail, Context, Result};
use std::collections::BTreeMap;
use std::fs::{File, OpenOptions};
use std::io::{Read, Seek, SeekFrom, Write};
use std::path::Path;

fn be32_pair(iso: &Path, offset: u64) -> Result<(u64, u64)> {
    let mut file = File::open(iso).with_context(|| format!("open {}", iso.display()))?;
    file.seek(SeekFrom::Start(offset))?;
    let mut raw = [0u8; 8];
    file.read_exact(&mut raw)?;
    let first = u32::from_be_bytes([raw[0], raw[1], raw[2], raw[3]]);
    let second = u32::from_be_bytes([raw[4], raw[5], raw[6], raw[7]]);
    Ok((u64::from(first), u64::from(second)))
}

pub fn fst_entry_offset(iso: &Path, path: &str) -> Result<u64> {
    let (fst_offset, fst) = disc::raw_fst(iso)?;
    disc::fst_entries(&fst)?
        .into_iter()
        .find(|entry| !entry.directory && entry.path == path)
        .map(|entry| fst_offset + entry.index as u64 * 12)
        .ok_or_else(|| anyhow!("{path} not in the FST"))
}

pub fn reserved_ranges(iso: &Path) -> Result<Vec<(u64, u64)>> {
    let (fst_offset, fst_size) = be32_pair(iso, 0x424)?;
    let (loader_size, trailer_size) = be32_pair(iso, 0x2454)?;
    let dol_start = disc::dol_offset(iso)?;
    let dol_end = dol_start + disc::read_dol(iso)?.len() as u64;
    Ok(vec![
        (0, 0x2460 + loader_size + trailer_size),
        (dol_start, dol_end),
        (fst_offset, fst_offset + fst_size),
        (cave::DISC_OFFSET, cave::DISC_END),
    ])
}

pub fn place_sizes(iso: &Path, sizes: &BTreeMap<String, u64>) -> Result<BTreeMap<String, u64>> {
    let files = disc::read_fst(iso)?;
    let mut used = reserved_ranges(iso)?;
    for (path, &(offset, size)) in &files {
        let kept = match sizes.get(path) {
            Some(&length) => length <= u64::from(size),
            None => true,
        };
        if kept {
            used.push((u64::from(offset), u64::from(offset) + u64::from(size)));
        }
    }
    let disc_size = std::fs::metadata(iso)?.len();
    let mut placement = BTreeMap::new();
    for (path, &length) in sizes {
        let &(offset, size) = files
            .get(path)
            .ok_or_else(|| anyhow!("{path} is not on the disc"))?;
        if length <= u64::from(size) {
            placement.insert(path.clone(), u64::from(offset));
            continue;
        }
        let mut ranges = used.clone();
        ranges.sort_unstable();
        ranges.push((disc_size, disc_size));
        let mut cursor = 0u64;
        let mut found = None;
        for (start, end) in ranges {
            let gap_start = (cursor + 0x7FFF) & !0x7FFF;
            if start >= gap_start && start - gap_start >= length {
                found = Some(gap_start);
                break;
            }
            cursor = cursor.max(end);
        }
        let gap_start = found
            .filter(|gap_start| gap_start + length <= disc_size)
            .ok_or_else(|| anyhow!("no {length}-byte gap on the disc for {path}"))?;
        placement.insert(path.clone(), gap_start);
        used.push((gap_start, gap_start + length));
    }
    Ok(placement)
}

pub fn place_files(iso: &Path, replacements: &Files) -> Result<BTreeMap<String, u64>> {
    let sizes = replacements
        .iter()
        .map(|(path, data)| (path.clone(), data.len() as u64))
        .collect();
    place_sizes(iso, &sizes)
}

pub fn write_iso(
    iso: &Path,
    out: &Path,
    dol: &[u8],
    files: &Files,
) -> Result<BTreeMap<String, u64>> {
    let placement = place_files(iso, files)?;
    let mut entries = Vec::with_capacity(files.len());
    for path in files.keys() {
        entries.push(fst_entry_offset(iso, path)?);
    }
    let dol_start = disc::dol_offset(iso)?;
    if out.exists() {
        std::fs::remove_file(out)?;
    }
    std::fs::copy(iso, out)
        .with_context(|| format!("copy {} to {}", iso.display(), out.display()))?;
    let mut image = OpenOptions::new().write(true).open(out)?;
    image.seek(SeekFrom::Start(dol_start))?;
    image.write_all(dol)?;
    for ((path, data), entry) in files.iter().zip(entries) {
        let offset = placement[path];
        image.seek(SeekFrom::Start(offset))?;
        image.write_all(data)?;
        image.seek(SeekFrom::Start(entry + 4))?;
        image.write_all(&u32::try_from(offset)?.to_be_bytes())?;
        image.write_all(&u32::try_from(data.len())?.to_be_bytes())?;
    }
    image.flush()?;
    Ok(placement)
}

pub fn set_cave(dol: &mut [u8], dol_start: u64, cave: &Cave) -> Result<()> {
    if cave.is_empty() {
        return Ok(());
    }
    let field = |base: usize| base + cave::SLOT * 4;
    let header = dol
        .get(..0x100)
        .ok_or_else(|| anyhow!("the DOL has no header"))?;
    if [0, 72, 144]
        .iter()
        .any(|&base| header[field(base)..field(base) + 4] != [0; 4])
    {
        bail!("DOL text section {} is already in use", cave::SLOT);
    }
    let offset = u32::try_from(cave::DISC_OFFSET - dol_start)?;
    let size = u32::try_from(cave.section().len())?;
    for (base, value) in [(0, offset), (72, cave::ADDRESS), (144, size)] {
        dol[field(base)..field(base) + 4].copy_from_slice(&value.to_be_bytes());
    }
    Ok(())
}

pub fn write_iso_with_cave(
    iso: &Path,
    out: &Path,
    dol: &[u8],
    files: &Files,
    cave: &Cave,
) -> Result<BTreeMap<String, u64>> {
    if cave.is_empty() {
        return write_iso(iso, out, dol, files);
    }
    let dol_start = disc::dol_offset(iso)?;
    let (fst_offset, fst_size) = be32_pair(iso, 0x424)?;
    let used = disc::read_fst(iso)?
        .into_iter()
        .map(|(path, (offset, size))| (path, u64::from(offset), u64::from(size)))
        .chain([
            (String::from("the DOL"), dol_start, dol.len() as u64),
            (String::from("the FST"), fst_offset, fst_size),
        ]);
    for (path, offset, size) in used {
        if size != 0 && offset < cave::DISC_END && cave::DISC_OFFSET < offset + size {
            bail!("{path} at {offset:#X} occupies the code cave on the disc");
        }
    }
    let mut dol = dol.to_vec();
    set_cave(&mut dol, dol_start, cave)?;
    let placement = write_iso(iso, out, &dol, files)?;
    let mut image = OpenOptions::new().write(true).open(out)?;
    image.seek(SeekFrom::Start(cave::DISC_OFFSET))?;
    image.write_all(&cave.section())?;
    image.flush()?;
    Ok(placement)
}
