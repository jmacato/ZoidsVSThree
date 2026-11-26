pub mod atlas;
pub mod cave;
pub mod disc;
pub mod elf;
pub mod geometry;
pub mod gx;
pub mod hsd;
pub mod iplfont;
pub mod layout;
pub mod layout_disc;
pub mod relocate;
pub mod scene;
pub mod shim;
pub mod story;
pub mod text;
pub mod textures;
pub mod toolchain;

use std::collections::BTreeMap;

/// Disc path to replacement contents, as the build collects them.
pub type Files = BTreeMap<String, Vec<u8>>;
