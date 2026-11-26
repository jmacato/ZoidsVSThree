use crate::atlas::write_floats;
use crate::geometry::Geometry;
use crate::hsd::HEADER;
use crate::scene::{self, Camera, Mat3, Scene, Vec3};
use crate::{disc, Files};
use anyhow::{anyhow, bail, Result};
use std::collections::{BTreeMap, BTreeSet};
use std::path::Path;

const CARD: f64 = 70.0;
const SETTING: f64 = 36.0;
const VS_RIGHT_EDGE: f64 = 156.0;
const PARTNER: f64 = 40.0;
const PARTNER_NAME: f64 = 120.0;
const ENTRY_ROW: f64 = 170.0;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Action {
    Stretch,
    Shift,
    Move,
}

#[derive(Clone, Copy, Debug)]
pub struct Entry {
    pub pattern: &'static str,
    pub model: usize,
    pub path: &'static [i32],
    pub action: Action,
    pub pixels: f64,
}

const fn entry(
    pattern: &'static str,
    model: usize,
    path: &'static [i32],
    action: Action,
    pixels: f64,
) -> Entry {
    Entry {
        pattern,
        model,
        path,
        action,
        pixels,
    }
}

const BP: &str = "chara/bp/bp[0-9][0-9].dat";
const PICTURE: &str = "menu/picture/s[pz][0-9][0-9].dat";
const FARM: &str = "menu/battle_menu/farm/farm.dat";
const BATTLE_ENTRY: &str = "menu/battle_menu/battle_entry.dat";
const VS_MENU: &str = "menu/vs_menu/vs_menu.dat";

pub const LAYOUT: [Entry; 30] = [
    entry(BP, 0, &[0, 1], Action::Stretch, PARTNER),
    entry(BP, 0, &[0, 1, 0], Action::Stretch, PARTNER),
    entry(BP, 0, &[0, 2], Action::Stretch, PARTNER_NAME),
    entry(PICTURE, 0, &[0, 1], Action::Stretch, CARD),
    entry(PICTURE, 0, &[0, 1, 0], Action::Shift, CARD),
    entry(FARM, 6, &[0, 0, 0], Action::Stretch, ENTRY_ROW),
    entry(FARM, 6, &[0, 1, 0], Action::Stretch, ENTRY_ROW),
    entry(FARM, 6, &[0, 2], Action::Move, -32.0),
    entry(FARM, 6, &[0, 2], Action::Stretch, CARD),
    entry(FARM, 6, &[0, 2, 3], Action::Stretch, CARD),
    entry(BATTLE_ENTRY, 4, &[0, 2], Action::Stretch, CARD),
    entry(BATTLE_ENTRY, 4, &[0, 2, 3], Action::Stretch, CARD),
    entry(BATTLE_ENTRY, 5, &[0, 1], Action::Stretch, CARD),
    entry(VS_MENU, 6, &[0, 1, 0, 0], Action::Move, VS_RIGHT_EDGE),
    entry(VS_MENU, 6, &[0, 1, 0, 1], Action::Move, VS_RIGHT_EDGE),
    entry(VS_MENU, 7, &[0, 1], Action::Stretch, CARD),
    entry(VS_MENU, 8, &[0], Action::Stretch, CARD),
    entry(VS_MENU, 9, &[0, 0], Action::Stretch, CARD),
    entry(VS_MENU, 9, &[0, 0, 1], Action::Shift, CARD),
    entry(VS_MENU, 9, &[0, 1], Action::Stretch, CARD),
    entry(FARM, 2, &[0, 0], Action::Stretch, CARD),
    entry(FARM, 2, &[0, 6], Action::Stretch, CARD),
    entry(FARM, 2, &[0, 6, 0], Action::Shift, CARD),
    entry(FARM, 7, &[0, 1], Action::Stretch, CARD),
    entry(FARM, 25, &[0, 1], Action::Move, -40.0),
    entry(FARM, 25, &[0, 2], Action::Move, 30.0),
    entry(FARM, 8, &[0, 0], Action::Stretch, CARD),
    entry(FARM, 8, &[0, 1], Action::Stretch, CARD),
    entry(FARM, 12, &[0], Action::Stretch, CARD),
    entry(FARM, 9, &[0, 6, 0], Action::Stretch, SETTING),
];

/// Vertex array offset, vertex index and stride.
pub type Key = (usize, usize, usize);

fn class_match(class: &[u8], c: u8) -> bool {
    let (negate, class) = match class.first() {
        Some(b'!') => (true, &class[1..]),
        _ => (false, class),
    };
    let mut found = false;
    let mut i = 0;
    while i < class.len() {
        if i + 2 < class.len() && class[i + 1] == b'-' {
            found |= class[i] <= c && c <= class[i + 2];
            i += 3;
        } else {
            found |= class[i] == c;
            i += 1;
        }
    }
    found != negate
}

pub fn fnmatch(name: &[u8], pattern: &[u8]) -> bool {
    let Some(&first) = pattern.first() else {
        return name.is_empty();
    };
    match first {
        b'*' => (0..=name.len()).any(|skip| fnmatch(&name[skip..], &pattern[1..])),
        b'?' => !name.is_empty() && fnmatch(&name[1..], &pattern[1..]),
        b'[' => {
            let close = pattern[2.min(pattern.len())..]
                .iter()
                .position(|&c| c == b']')
                .map(|at| at + 2);
            match close {
                Some(close) => {
                    !name.is_empty()
                        && class_match(&pattern[1..close], name[0])
                        && fnmatch(&name[1..], &pattern[close + 1..])
                }
                None => name.first() == Some(&b'[') && fnmatch(&name[1..], &pattern[1..]),
            }
        }
        c => name.first() == Some(&c) && fnmatch(&name[1..], &pattern[1..]),
    }
}

pub fn screen_delta(
    camera: &Camera,
    origin: Vec3,
    linear: &Mat3,
    pixels: f64,
) -> Result<(f64, f64)> {
    let base = scene::project(camera, origin, 640.0, 480.0);
    let mut jacobian = [[0.0; 3]; 2];
    for axis in 0..3 {
        let mut moved = origin;
        moved[axis] += 1e-3;
        let stepped = scene::project(camera, moved, 640.0, 480.0);
        jacobian[0][axis] = (stepped.0 - base.0) / 1e-3;
        jacobian[1][axis] = (stepped.1 - base.1) / 1e-3;
    }
    let columns = [
        [linear[0][0], linear[0][1]],
        [linear[1][0], linear[1][1]],
        [linear[2][0], linear[2][1]],
    ];
    let plane = scene::matmul(&jacobian, &columns);
    let solved = scene::solve(plane, [[pixels], [0.0]])?;
    Ok((solved[0][0], solved[1][0]))
}

/// Every position a joint's meshes reference, in first-seen order, as the Python dict held them.
pub fn mesh_vertices(geometry: &Geometry, joint: usize) -> Result<Vec<(Key, Vec3)>> {
    let mut order: Vec<(Key, Vec3)> = Vec::new();
    let mut seen: BTreeMap<Key, usize> = BTreeMap::new();
    for dobj in geometry.dobjs(joint)? {
        for pobj in geometry.pobjs(dobj)? {
            let attrs = geometry.attributes(pobj)?;
            let pos = attrs
                .iter()
                .find(|a| a.attr == crate::geometry::GX_VA_POS)
                .ok_or_else(|| anyhow!("pobj {pobj:#x}: no positions"))?;
            if pos.comp != 4 {
                bail!("pobj {pobj:#x}: positions are not float");
            }
            let array = pos
                .array
                .ok_or_else(|| anyhow!("pobj {pobj:#x}: positions have no array"))?;
            for (_, vertices) in geometry.vertices(pobj)? {
                for vertex in vertices {
                    let element = vertex
                        .pos
                        .ok_or_else(|| anyhow!("pobj {pobj:#x}: vertex without a position"))?;
                    let v = &element.values;
                    let value = [v[0], v[1], if v.len() > 2 { v[2] } else { 0.0 }];
                    let key = (array, element.index, pos.stride);
                    match seen.get(&key) {
                        Some(&at) => order[at].1 = value,
                        None => {
                            seen.insert(key, order.len());
                            order.push((key, value));
                        }
                    }
                }
            }
        }
    }
    Ok(order)
}

#[allow(clippy::too_many_arguments)]
pub fn edit(
    data: &mut [u8],
    scene: &Scene,
    camera: &Camera,
    model: usize,
    path: &[i32],
    action: Action,
    pixels: f64,
    moved: &mut BTreeSet<Key>,
) -> Result<()> {
    let geometry = Geometry::new(&scene.archive);
    let (joint, world) = scene.world(model, path)?;
    if action == Action::Move {
        let parent = scene::matmul(&world, &scene::inverse(&scene.local(joint)?)?);
        let (dx, dy) = screen_delta(
            camera,
            scene::translation(&world),
            &scene::linear(&parent),
            pixels,
        )?;
        let at = joint + 0x2C;
        let read = |offset: usize| -> Result<f64> {
            let raw = data
                .get(HEADER + offset..HEADER + offset + 4)
                .ok_or_else(|| anyhow!("joint {joint:#x} is outside the archive"))?;
            Ok(f64::from(f32::from_be_bytes([
                raw[0], raw[1], raw[2], raw[3],
            ])))
        };
        let (x, y) = (read(at)?, read(at + 4)?);
        return write_floats(data, at, &[x + dx, y + dy]);
    }
    let vertices = mesh_vertices(&geometry, joint)?;
    if vertices.is_empty() {
        bail!("model {model} joint {path:?}: no mesh");
    }
    let screen: Vec<f64> = vertices
        .iter()
        .map(|(_, v)| scene::project(camera, scene::transform(&world, *v), 640.0, 480.0).0)
        .collect();
    let low = screen.iter().copied().fold(f64::INFINITY, f64::min);
    let high = screen.iter().copied().fold(f64::NEG_INFINITY, f64::max);
    let middle = (low + high) / 2.0;
    let mut mean = [0.0; 3];
    for (_, v) in &vertices {
        for axis in 0..3 {
            mean[axis] += v[axis];
        }
    }
    let mean = mean.map(|sum| sum / vertices.len() as f64);
    let center = scene::transform(&world, mean);
    let (dx, dy) = screen_delta(camera, center, &scene::linear(&world), pixels)?;
    for ((key, value), x) in vertices.iter().zip(screen) {
        let held = if pixels > 0.0 {
            x <= middle
        } else {
            x >= middle
        };
        if moved.contains(key) || (action == Action::Stretch && held) {
            continue;
        }
        moved.insert(*key);
        let (array, index, stride) = *key;
        write_floats(
            data,
            array + index * stride,
            &[value[0] + dx, value[1] + dy],
        )?;
    }
    Ok(())
}

pub fn layout_patches(iso: &Path, files: &mut Files) -> Result<usize> {
    let mut count = 0;
    let names: Vec<String> = disc::read_fst(iso)?.into_keys().collect();
    let mut moved: BTreeMap<String, BTreeSet<Key>> = BTreeMap::new();
    for entry in LAYOUT {
        let mut matching: Vec<&String> = names
            .iter()
            .filter(|name| fnmatch(name.as_bytes(), entry.pattern.as_bytes()))
            .collect();
        matching.sort();
        for name in matching {
            if !files.contains_key(name) {
                files.insert(name.clone(), disc::read_file(iso, name)?);
            }
            let data = files
                .get_mut(name)
                .ok_or_else(|| anyhow!("{name} is missing"))?;
            let scene = Scene::new(data.clone())?;
            let camera = scene.camera()?;
            edit(
                data,
                &scene,
                &camera,
                entry.model,
                entry.path,
                entry.action,
                entry.pixels,
                moved.entry(name.clone()).or_default(),
            )?;
            count += 1;
        }
    }
    Ok(count)
}
