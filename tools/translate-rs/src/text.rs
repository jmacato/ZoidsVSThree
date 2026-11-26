use crate::elf::Elf;
use crate::{disc, Files};
use anyhow::{anyhow, bail, Context, Result};
use serde_json::Value;
use std::collections::HashMap;
use std::path::Path;

pub const MENU_PATH: &str = "etc/TXT_Menu.BIN";
pub const MENU_SIZE: usize = 16558;
pub const MESSAGE_LIMIT: usize = 399;
pub const CHOICE_LIMIT: usize = 79;
pub const STORY_PATH: &str = "etc/demo/text.BIN";
pub const STORY_PATHS: [&str; 3] = [STORY_PATH, "etc/CI.tcs", "etc/CI.tpl"];
pub const STORY_COUNT: usize = 4000;
pub const DETAIL_LIMIT: usize = 0x18D;

fn be32(data: &[u8], at: usize) -> u32 {
    u32::from_be_bytes([data[at], data[at + 1], data[at + 2], data[at + 3]])
}

pub fn encode_cp932(text: &str) -> Result<Vec<u8>> {
    let (raw, _, unmappable) = encoding_rs::SHIFT_JIS.encode(text);
    let widened = text
        .chars()
        .any(|c| matches!(c, '\u{a5}' | '\u{203e}' | '\u{2212}'));
    if unmappable || widened {
        bail!("{text:?} does not encode as cp932");
    }
    Ok(raw.into_owned())
}

pub fn pad_lines(en: &str, ja: &str, newline: &str) -> String {
    let wanted = ja.matches(newline).count();
    let present = en.matches(newline).count();
    let mut padded = en.to_owned();
    for _ in present..wanted {
        padded.push_str(newline);
    }
    padded
}

pub fn load(translation: &Path, name: &str) -> Result<Vec<Value>> {
    load_items(&translation.join(name))
}

pub fn load_items(path: &Path) -> Result<Vec<Value>> {
    let raw = std::fs::read_to_string(path).with_context(|| format!("read {}", path.display()))?;
    serde_json::from_str(&raw).with_context(|| format!("parse {}", path.display()))
}

pub fn item_text<'a>(item: &'a Value, key: &str) -> &'a str {
    item.get(key).and_then(Value::as_str).unwrap_or("")
}

pub fn item_label(item: &Value) -> String {
    match item.get("id") {
        Some(Value::String(id)) => id.clone(),
        Some(id) => id.to_string(),
        None => String::from("?"),
    }
}

pub fn item_cap(item: &Value) -> Result<usize> {
    item.get("cap")
        .and_then(Value::as_u64)
        .map(|cap| cap as usize)
        .ok_or_else(|| anyhow!("{}: no cap", item_label(item)))
}

pub fn parse_hex(text: &str) -> Result<usize> {
    let digits = text
        .strip_prefix("0x")
        .or_else(|| text.strip_prefix("0X"))
        .unwrap_or(text);
    usize::from_str_radix(digits, 16).with_context(|| format!("{text:?} is not hexadecimal"))
}

fn message_bytes(item: &Value, newline: &str) -> Result<Vec<u8>> {
    let en = item_text(item, "en");
    let ja = item_text(item, "ja");
    if en.is_empty() {
        encode_cp932(ja)
    } else {
        encode_cp932(&pad_lines(en, ja, newline))
    }
}

/// TXT_Menu.BIN contents and the offset of every message, in table order.
pub fn encode_menu(items: &[Value]) -> Result<(Vec<u8>, Vec<u32>, usize)> {
    let mut blob = Vec::new();
    let mut placed: HashMap<String, u32> = HashMap::new();
    let mut offsets = Vec::with_capacity(items.len());
    for item in items {
        let key = item
            .get("offset")
            .ok_or_else(|| anyhow!("message {}: no offset", item_label(item)))?
            .to_string();
        if let Some(&offset) = placed.get(&key) {
            offsets.push(offset);
            continue;
        }
        let raw = message_bytes(item, "\r\n")?;
        if raw.len() > MESSAGE_LIMIT {
            bail!(
                "message {} is {} bytes; the copy buffers hold {MESSAGE_LIMIT}",
                item_label(item),
                raw.len()
            );
        }
        let offset = u32::try_from(blob.len())?;
        placed.insert(key, offset);
        offsets.push(offset);
        blob.extend_from_slice(&raw);
        blob.push(0);
    }
    if blob.len() > MENU_SIZE {
        bail!(
            "{MENU_PATH} would be {} bytes, the game buffer holds {MENU_SIZE}",
            blob.len()
        );
    }
    blob.resize(MENU_SIZE, 0);
    let translated = items
        .iter()
        .filter(|item| !item_text(item, "en").is_empty())
        .count();
    Ok((blob, offsets, translated))
}

pub fn write_menu_table(dol: &mut [u8], reference: &Elf, offsets: &[u32]) -> Result<()> {
    let symbol = reference
        .named("TXT_Menu")
        .first()
        .copied()
        .ok_or_else(|| anyhow!("TXT_Menu is not in the ELF"))?;
    if symbol.size as usize != offsets.len() * 4 {
        bail!(
            "TXT_Menu holds {} offsets, the translation has {}",
            symbol.size / 4,
            offsets.len()
        );
    }
    let table: Vec<u8> = offsets
        .iter()
        .flat_map(|offset| offset.to_be_bytes())
        .collect();
    disc::dol_write(dol, symbol.address, &table)
}

/// etc/demo/text.BIN rebuilt with the translated messages in place of the originals.
pub fn build_story(original: &[u8], items: &[Value]) -> Result<(Vec<u8>, usize)> {
    let header = STORY_COUNT * 4;
    let mut english: HashMap<usize, Vec<u8>> = HashMap::new();
    for item in items {
        if item_text(item, "en").is_empty() {
            continue;
        }
        let number =
            item.get("id")
                .and_then(Value::as_u64)
                .ok_or_else(|| anyhow!("story message without a numeric id"))? as usize;
        let mut raw = message_bytes(item, "\r\n")?;
        raw.push(0);
        if raw.len() > MESSAGE_LIMIT {
            bail!(
                "story message {number} is {} bytes, limit {MESSAGE_LIMIT}",
                raw.len()
            );
        }
        english.insert(number, raw);
    }
    let mut table = Vec::with_capacity(header);
    let mut body = Vec::new();
    for number in 0..STORY_COUNT {
        let start = if number == 0 {
            header
        } else {
            be32(original, (number - 1) * 4) as usize
        };
        let end = be32(original, number * 4) as usize;
        match english.get(&number) {
            Some(raw) => body.extend_from_slice(raw),
            None if end > start && end <= original.len() => {
                body.extend_from_slice(&original[start..end]);
            }
            None => {}
        }
        table.extend_from_slice(&u32::try_from(header + body.len())?.to_be_bytes());
    }
    table.extend_from_slice(&body);
    Ok((table, english.len()))
}

pub fn field_bytes(item: &Value) -> Result<Vec<u8>> {
    let padded = pad_lines(item_text(item, "en"), item_text(item, "ja"), "\r\n");
    if !padded.is_ascii() {
        bail!("{}: {padded:?} is not ASCII", item_label(item));
    }
    let mut raw = padded.into_bytes();
    let cap = item_cap(item)?;
    while raw.len() + 1 > cap && raw.ends_with(b"\r\n") {
        raw.truncate(raw.len() - 2);
    }
    if raw.len() + 1 > cap {
        bail!(
            "{}: {} bytes do not fit in {}",
            item_label(item),
            raw.len(),
            cap as i64 - 1
        );
    }
    raw.resize(cap, 0);
    Ok(raw)
}

fn splice(data: &mut Vec<u8>, offset: usize, width: usize, new: Vec<u8>) {
    let start = offset.min(data.len());
    let end = (offset + width).min(data.len());
    data.splice(start..end, new);
}

pub fn apply_fields(iso: &Path, items: &[Value], files: &mut Files) -> Result<usize> {
    let mut count = 0;
    for item in items {
        if item_text(item, "en").is_empty() {
            continue;
        }
        let data = field_bytes(item)?;
        let places = item
            .get("where")
            .and_then(Value::as_array)
            .ok_or_else(|| anyhow!("{}: no where list", item_label(item)))?;
        for place in places {
            let (path, offset) = place
                .as_str()
                .and_then(|place| place.rsplit_once(':'))
                .ok_or_else(|| anyhow!("{}: bad where entry {place}", item_label(item)))?;
            let offset = parse_hex(offset)?;
            if !files.contains_key(path) {
                files.insert(path.to_owned(), disc::read_file(iso, path)?);
            }
            if let Some(file) = files.get_mut(path) {
                splice(file, offset, data.len(), data.clone());
            }
        }
        count += 1;
    }
    Ok(count)
}

pub fn apply_details(items: &[Value], files: &mut Files) -> Result<usize> {
    let mut count = 0;
    for item in items {
        let en = item_text(item, "en");
        if en.is_empty() {
            continue;
        }
        if !en.is_ascii() {
            bail!("{}: {en:?} is not ASCII", item_label(item));
        }
        if en.len() > DETAIL_LIMIT {
            bail!(
                "{}: {} bytes, the detail buffer holds {DETAIL_LIMIT}",
                item_label(item),
                en.len()
            );
        }
        files.insert(item_label(item), en.as_bytes().to_vec());
        count += 1;
    }
    Ok(count)
}

pub fn build_epilogue(items: &[Value]) -> Result<Vec<u8>> {
    let lines: Vec<&str> = items.iter().map(|item| item_text(item, "en")).collect();
    let mut raw = encode_cp932(&lines.join("\r\n").replace('\u{A9}', "\u{FF6A}"))?;
    raw.extend_from_slice(b"\r\n\0");
    Ok(raw)
}

pub fn build_banner(iso: &Path, items: &[Value]) -> Result<Vec<u8>> {
    let mut data = disc::read_file(iso, "OPENING.BNR")?;
    for item in items {
        if item_text(item, "en").is_empty() {
            continue;
        }
        let offset = parse_hex(item_text(item, "offset"))?;
        splice(&mut data, offset, item_cap(item)?, field_bytes(item)?);
    }
    Ok(data)
}

pub fn write_dol_strings(dol: &mut [u8], items: &[Value]) -> Result<usize> {
    let mut count = 0;
    for item in items {
        let en = item_text(item, "en");
        if en.is_empty() {
            continue;
        }
        if !en.is_ascii() {
            bail!("{}: {en:?} is not ASCII", item_label(item));
        }
        let cap = item_cap(item)?;
        if en.len() + 1 > cap {
            bail!(
                "{}: {} bytes do not fit in {}",
                item_label(item),
                en.len(),
                cap - 1
            );
        }
        let mut raw = en.as_bytes().to_vec();
        raw.resize(cap, 0);
        let address = u32::try_from(parse_hex(item_text(item, "id"))?)?;
        disc::dol_write(dol, address, &raw)?;
        count += 1;
    }
    Ok(count)
}

pub struct Texts<'a> {
    pub menu: &'a [Value],
    pub stories: &'a [Vec<Value>],
}

pub fn build_text(
    iso: &Path,
    translation: &Path,
    reference: &Elf,
    texts: &Texts,
    dol: &mut [u8],
    files: &mut Files,
) -> Result<Vec<String>> {
    let (blob, offsets, menu) = encode_menu(texts.menu)?;
    write_menu_table(dol, reference, &offsets)?;
    files.insert(MENU_PATH.to_string(), blob);
    if texts.stories.len() > STORY_PATHS.len() {
        bail!(
            "{} story sets, the disc holds {}",
            texts.stories.len(),
            STORY_PATHS.len()
        );
    }
    let original = disc::read_file(iso, STORY_PATH)?;
    let mut lines = 0;
    for (path, items) in STORY_PATHS.iter().zip(texts.stories) {
        let (story, count) = build_story(&original, items)?;
        lines = count;
        files.insert(path.to_string(), story);
    }
    let strings = write_dol_strings(dol, &load(translation, "dol_strings.json")?)?;
    let map_info = apply_fields(iso, &load(translation, "map_info.json")?, files)?;
    let help = apply_fields(iso, &load(translation, "help.json")?, files)?;
    let names = apply_fields(iso, &load(translation, "names.json")?, files)?;
    let details = apply_details(&load(translation, "details.json")?, files)?;
    let staff = load(translation, "epilogue.json")?;
    files.insert(
        String::from("epilogue/epilogue.txt"),
        build_epilogue(&staff)?,
    );
    files.insert(
        String::from("OPENING.BNR"),
        build_banner(iso, &load(translation, "banner.json")?)?,
    );
    Ok(vec![
        format!("{menu}/{} menu messages", offsets.len()),
        format!("{lines} story messages"),
        format!("{strings} DOL strings"),
        format!("{map_info} map info strings"),
        format!("{help} help messages"),
        format!("{names} names"),
        format!("{details} descriptions"),
        format!("{} staff roll lines", staff.len()),
    ])
}
