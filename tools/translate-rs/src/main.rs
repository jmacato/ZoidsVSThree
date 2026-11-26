use anyhow::{anyhow, bail, Result};
use std::collections::BTreeMap;
use std::path::PathBuf;
use zvs_translate::elf::Elf;
use zvs_translate::shim::{
    shim_code, FONT_ENTRY_MESSAGE, FONT_HELP_MESSAGE, FONT_LABEL_MESSAGE, TITLE_TEXT_MESSAGE,
};
use zvs_translate::text::Texts;
use zvs_translate::{cave, disc, iplfont, layout_disc, story, text, textures, Files};

const USAGE: &str = "usage: zvs3-translate [--root REPO] [--iso JAPAN_ISO] [--out ISO] [--font chakra|xolonium|saira] [--no-fixed-height]";

fn main() -> Result<()> {
    let mut values: BTreeMap<String, PathBuf> = BTreeMap::new();
    let mut fixed_height = true;
    let mut args = std::env::args().skip(1);
    while let Some(key) = args.next() {
        if key == "--no-fixed-height" {
            fixed_height = false;
            continue;
        }
        if !["--root", "--iso", "--out", "--font"].contains(&key.as_str()) {
            bail!("unknown option {key}\n{USAGE}");
        }
        values.insert(
            key,
            PathBuf::from(args.next().ok_or_else(|| anyhow!(USAGE))?),
        );
    }
    let root = match values.get("--root") {
        Some(root) => root.clone(),
        None => PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("../.."),
    };
    let root = std::fs::canonicalize(root)?;
    let build = root.join("build");
    let iso = values
        .get("--iso")
        .cloned()
        .unwrap_or_else(|| build.join("Zoids vs. III (Japan).iso"));
    let font = values.get("--font").map_or_else(
        || String::from("chakra"),
        |value| value.to_string_lossy().into_owned(),
    );
    let out = values
        .get("--out")
        .cloned()
        .unwrap_or_else(|| build.join(format!("Zoids VS III (English, {font}).iso")));
    let translation = root.join("translation");

    let reference = Elf::new(disc::read_file(&iso, "zoidR.elf")?)?;
    let work = build.join(format!("translate-work-{}", std::process::id()));
    std::fs::create_dir_all(&work)?;
    let shim = shim_code(&reference, &root, &work);
    std::fs::remove_dir_all(&work)?;
    let shim = shim?;

    let mut dol = disc::read_dol(&iso)?;
    for (address, code) in &shim.patches {
        disc::dol_write(&mut dol, *address, code)?;
    }
    let mut files = Files::new();
    let fonts = iplfont::font_order(&font)?;
    let mut menu = text::load(&translation, "TXT_Menu.json")?;
    for (index, (_, label)) in fonts.iter().enumerate() {
        let item = menu
            .get_mut(FONT_LABEL_MESSAGE + index)
            .ok_or_else(|| anyhow!("TXT_Menu has no message {}", FONT_LABEL_MESSAGE + index))?;
        item["en"] = label.to_uppercase().into();
    }
    for (message, text) in [
        (FONT_HELP_MESSAGE, "Choose the font for story text."),
        (FONT_ENTRY_MESSAGE, "TEXT"),
        (FONT_ENTRY_MESSAGE + 1, "FONT"),
        (
            TITLE_TEXT_MESSAGE,
            "\u{FF69}1983-2004 TOMY \u{FF69}ShoPro\u{FF77}TV Tokyo\r\nZOIDS is a trademark of TOMY Company, Ltd. and used under license.\r\nDecomp, Translation \u{FF69} Jumar Macato \u{FF77} AGPL-3.0 \u{FF77} Patch 1.0.0",
        ),
    ] {
        let item = menu
            .get_mut(message)
            .ok_or_else(|| anyhow!("TXT_Menu has no message {message}"))?;
        item["en"] = if message == TITLE_TEXT_MESSAGE {
            iplfont::title_text(text).into()
        } else {
            text.into()
        };
    }
    let story_items = text::load(&translation, "story.json")?;
    let mut stories = Vec::new();
    let mut fixed = None;
    for (name, _) in &fonts {
        let mut items = story_items.clone();
        if fixed_height {
            let count = story::apply(&iso, name, &mut items)?;
            fixed.get_or_insert(count);
        }
        stories.push(items);
    }
    let texts = Texts {
        menu: &menu,
        stories: &stories,
    };
    let mut report =
        text::build_text(&iso, &translation, &reference, &texts, &mut dol, &mut files)?;
    if let Some(fixed) = fixed {
        report.push(format!("{fixed} story messages at fixed height"));
    }
    for ((name, _), path) in fonts.iter().zip(iplfont::SWITCH_PATHS) {
        files.insert(path.to_string(), iplfont::story_font(name)?.encode()?);
    }
    let texture_dir = translation.join("textures");
    if texture_dir.is_dir() {
        let count = textures::texture_patches_from(&texture_dir, &iso, &mut files)?;
        report.push(format!("{count} textures"));
    }
    layout_disc::write_iso_with_cave(&iso, &out, &dol, &files, &shim.cave)?;
    for (name, (address, size)) in &shim.moved {
        println!("{name} moved to {address:08X}, {size} bytes");
    }
    println!(
        "{}, {} functions patched, {} of {} code cave bytes, {} files replaced -> {}",
        report.join(", "),
        shim.patches.len(),
        shim.cave.data.len(),
        cave::CAPACITY,
        files.len(),
        out.display()
    );
    Ok(())
}
