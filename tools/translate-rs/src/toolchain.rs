use anyhow::{bail, Result};
use std::fs;
use std::path::{Component, Path, PathBuf};

const FLAGS: [&str; 20] = [
    "-c",
    "-O4,p",
    "-inline",
    "auto",
    "-fp",
    "hardware",
    "-fp_contract",
    "on",
    "-enum",
    "int",
    "-proc",
    "gekko",
    "-Cpp_exceptions",
    "off",
    "-RTTI",
    "off",
    "-nodefaults",
    "-nosyspath",
    "-align",
    "powerpc",
];

const SDK_1_2_5N: [&str; 11] = [
    "gx", "dsp", "ai", "ar", "exi", "si", "pad", "dvd", "card", "vi", "musyx",
];

const OS_1_2_5N: [&str; 15] = [
    "alarm.c",
    "interrupt.c",
    "message.c",
    "memory_protection.c",
    "mutex.c",
    "reboot.c",
    "thread.c",
    "time.c",
    "kernel.c",
    "cache.c",
    "error.c",
    "font.c",
    "sram.c",
    "reset_switch.c",
    "audio_system.c",
];

const LEVEL_4_GAME: [&str; 5] = [
    "src/camera/beSide.c",
    "src/thp/audio_codec.c",
    "src/thp/thp_decompress.c",
    "src/thp/video_tables.c",
    "src/zoid/resolveIKJoint1.c",
];

fn relative_name(root: &Path, path: &Path) -> Option<String> {
    let path = fs::canonicalize(path).ok()?;
    let root = fs::canonicalize(root).ok()?;
    let parts: Vec<String> = path
        .strip_prefix(&root)
        .ok()?
        .components()
        .filter_map(|part| match part {
            Component::Normal(name) => Some(name.to_string_lossy().into_owned()),
            _ => None,
        })
        .collect();
    Some(parts.join("/"))
}

pub fn version_for_source(root: &Path, path: &Path) -> &'static str {
    let Some(name) = relative_name(root, path) else {
        return "1.2.5";
    };
    if name.starts_with("src/sdk/trk/") {
        return "1.1p1";
    }
    let sdk = SDK_1_2_5N
        .iter()
        .any(|part| name.starts_with(&format!("src/sdk/{part}/")));
    let os = name
        .strip_prefix("src/sdk/os/")
        .is_some_and(|file| OS_1_2_5N.contains(&file));
    if sdk || os || name == "src/runtime/bootstrap.c" {
        "1.2.5n"
    } else {
        "1.2.5"
    }
}

pub fn compiler_for_source(root: &Path, path: &Path) -> Result<PathBuf> {
    let file = match version_for_source(root, path) {
        "1.1p1" => "mwcceppc-1.1p1-native",
        "1.2.5n" => "mwcceppc-1.2.5n-native",
        _ => "mwcceppc-native",
    };
    let compiler = root.join("build/tools").join(file);
    if !compiler.is_file() {
        bail!(
            "{} is missing; build the native compilers first",
            compiler.display()
        );
    }
    Ok(compiler)
}

pub fn flags_for_source(root: &Path, path: &Path) -> Vec<String> {
    let mut flags: Vec<String> = FLAGS.iter().map(|flag| flag.to_string()).collect();
    flags.push("-i".to_string());
    flags.push(root.join("include").to_string_lossy().into_owned());
    let Some(name) = relative_name(root, path) else {
        return flags;
    };
    if name.starts_with("src/runtime/math/") && name.ends_with(".c") {
        flags[3] = "off".to_string();
    } else if name.starts_with("src/sdk/trk/") {
        flags[3] = "deferred".to_string();
        flags.extend(["-sdata", "0", "-sdata2", "0"].map(String::from));
        if name.ends_with("/targimpl.c") || name.ends_with("/dolphin_trk_glue.c") {
            flags.extend(["-opt", "nopeephole"].map(String::from));
        }
    } else if name.starts_with("src/")
        && !name.starts_with("src/sdk/")
        && !name.starts_with("src/runtime/")
        && !LEVEL_4_GAME.contains(&name.as_str())
    {
        flags.extend(["-opt", "level=0,schedule,functions,peephole"].map(String::from));
    }
    flags
}
