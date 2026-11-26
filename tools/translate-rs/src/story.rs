use crate::iplfont::{self, Font, HANKAKU_BASE};
use crate::scene::Scene;
use crate::{disc, text};
use anyhow::{bail, Result};
use serde_json::Value;
use std::collections::{BTreeMap, HashMap};
use std::fmt;
use std::path::Path;

pub const ARCHIVE: &str = "menu/demo/demo.dat";
pub const SCRIPTS: &str = "etc/demo/DEMO_";
pub const NEWLINE: &str = "\r\n";
pub const LINE_HEIGHT: u32 = 24;
pub const WIDEN_CAP: f64 = 1.35;
const RECORD: usize = 22;

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub enum Context {
    Dialogue,
    Choice,
}

impl Context {
    pub const ALL: [Context; 2] = [Context::Dialogue, Context::Choice];

    pub fn name(self) -> &'static str {
        match self {
            Context::Dialogue => "dialogue",
            Context::Choice => "choice",
        }
    }

    fn joints(self) -> (usize, &'static [i32], &'static [i32]) {
        match self {
            Context::Dialogue => (0, &[0, 0, 0], &[0, 0, 2, 0]),
            Context::Choice => (2, &[0, 0, 0], &[0, 0, 0, 0]),
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Rect {
    pub width: f64,
    pub height: f64,
}

impl Rect {
    pub fn room(&self) -> f64 {
        self.width / self.height * f64::from(LINE_HEIGHT)
    }

    pub fn fixed_scale(&self, lines: usize) -> f32 {
        self.height as f32 / (LINE_HEIGHT as usize * lines) as f32
    }
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Overflow {
    pub needed: usize,
    pub word: String,
    pub word_width: u32,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub enum Problem {
    Characters,
    Overflow(Overflow),
    Bytes(usize),
    Shared(u64),
}

impl fmt::Display for Problem {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Problem::Characters => write!(f, "characters outside printable ASCII and CR LF"),
            Problem::Overflow(overflow) => write!(
                f,
                "needs {} lines, widest word {:?} is {} wide",
                overflow.needed, overflow.word, overflow.word_width
            ),
            Problem::Bytes(size) => write!(
                f,
                "{size} bytes with line padding, limit {}",
                text::MESSAGE_LIMIT
            ),
            Problem::Shared(owner) => write!(
                f,
                "shares its text with message {owner}, which is not in the same box"
            ),
        }
    }
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Fixed {
    pub text: String,
    pub padding: usize,
    pub capped: bool,
}

pub struct Entry {
    pub id: u64,
    pub context: Context,
    pub original: String,
    pub result: Result<Fixed, Problem>,
}

pub struct Plan {
    pub widths: Vec<u32>,
    pub rects: BTreeMap<Context, Rect>,
    pub counts: BTreeMap<Context, BTreeMap<usize, usize>>,
    pub lines: BTreeMap<Context, usize>,
    pub limits: BTreeMap<Context, f64>,
    pub entries: Vec<Entry>,
}

impl Plan {
    pub fn base(&self, context: Context) -> f64 {
        self.rects[&context].room() * self.lines[&context] as f64
    }

    pub fn limit(&self, context: Context) -> f64 {
        self.limits
            .get(&context)
            .copied()
            .unwrap_or_else(|| self.base(context))
    }

    pub fn widened(&self, context: Context) -> bool {
        self.limit(context) > self.base(context)
    }

    pub fn nominal_scale(&self, context: Context) -> f32 {
        if self.widened(context) {
            self.rects[&context].width as f32 / self.limit(context) as f32
        } else {
            self.rects[&context].fixed_scale(self.lines[&context])
        }
    }

    pub fn failures(&self) -> Vec<String> {
        self.entries
            .iter()
            .filter_map(|entry| {
                let problem = entry.result.as_ref().err()?;
                Some(format!(
                    "message {} ({}, {} lines, limit {:.1}): {problem}",
                    entry.id,
                    entry.context.name(),
                    self.lines[&entry.context],
                    self.limit(entry.context)
                ))
            })
            .collect()
    }
}

pub fn demo_messages(iso: &Path) -> Result<BTreeMap<u64, Context>> {
    let mut found = BTreeMap::new();
    for path in disc::read_fst(iso)?.keys() {
        if !path.starts_with(SCRIPTS) {
            continue;
        }
        let data = disc::read_file(iso, path)?;
        for raw in data.as_chunks::<RECORD>().0 {
            let field = |index: usize| i16::from_be_bytes([raw[index * 2], raw[index * 2 + 1]]);
            let command = field(0);
            if command == -2 {
                if let Ok(message) = u64::try_from(field(1)) {
                    found.entry(message).or_insert(Context::Choice);
                }
            } else if command >= 0 {
                if let Ok(message) = u64::try_from(field(6)) {
                    found.entry(message).or_insert(Context::Dialogue);
                }
            }
        }
    }
    Ok(found)
}

pub fn rect(scene: &Scene, context: Context) -> Result<Rect> {
    let (model, start, end) = context.joints();
    let a = scene.position(model, start)?;
    let b = scene.position(model, end)?;
    let rect = Rect {
        width: b[0] - a[0],
        height: a[1] - b[1],
    };
    if rect.width <= 0.0 || rect.height <= 0.0 {
        bail!("{} box in {ARCHIVE} is empty", context.name());
    }
    Ok(rect)
}

pub fn font_widths(font: &Font) -> Vec<u32> {
    (0..0x5F)
        .map(|c| u32::from(font.advance(HANKAKU_BASE + c)))
        .collect()
}

fn glyph(c: u8, widths: &[u32]) -> u32 {
    usize::from(c)
        .checked_sub(0x20)
        .and_then(|index| widths.get(index))
        .copied()
        .unwrap_or(0)
}

pub fn advance(line: &str, widths: &[u32]) -> u32 {
    line.bytes().map(|c| glyph(c, widths)).sum()
}

/// Widest line and height as sPutFontRect measures them, for ASCII text.
pub fn measure(message: &str, widths: &[u32]) -> (u32, u32) {
    let (mut widest, mut line, mut height) = (0, 0, 0);
    for c in message.bytes() {
        match c {
            b'\n' => {}
            b'\r' => {
                line = 0;
                height += LINE_HEIGHT;
            }
            _ => {
                line += glyph(c, widths);
                widest = widest.max(line);
            }
        }
    }
    (widest, height)
}

pub fn scale(rect: &Rect, message: &str, widths: &[u32]) -> Option<f32> {
    let (widest, height) = measure(message, widths);
    (widest != 0).then(|| {
        let x = rect.width as f32 / widest as f32;
        let y = rect.height as f32 / (height + LINE_HEIGHT) as f32;
        if x > y {
            y
        } else {
            x
        }
    })
}

fn item_id(item: &Value) -> Option<u64> {
    item.get("id").and_then(Value::as_u64)
}

pub fn line_counts(
    items: &[Value],
    contexts: &BTreeMap<u64, Context>,
) -> BTreeMap<Context, BTreeMap<usize, usize>> {
    let mut counts: BTreeMap<Context, BTreeMap<usize, usize>> = BTreeMap::new();
    for item in items {
        if let Some(&context) = item_id(item).and_then(|id| contexts.get(&id)) {
            let lines = text::item_text(item, "ja").matches(NEWLINE).count() + 1;
            *counts.entry(context).or_default().entry(lines).or_default() += 1;
        }
    }
    counts
}

pub fn fixed_lines(items: &[Value], contexts: &BTreeMap<u64, Context>) -> BTreeMap<Context, usize> {
    line_counts(items, contexts)
        .into_iter()
        .filter_map(|(context, counts)| Some((context, *counts.keys().next_back()?)))
        .collect()
}

pub fn content_lines(en: &str) -> Vec<&str> {
    let mut lines: Vec<&str> = en.split(NEWLINE).collect();
    while lines.len() > 1 && lines.last().is_some_and(|line| line.trim().is_empty()) {
        lines.pop();
    }
    lines
}

pub fn has_speaker(lines: &[&str]) -> bool {
    lines.len() >= 2 && !lines[0].starts_with('"') && lines[1].starts_with('"')
}

pub fn rewrap(en: &str, widths: &[u32], limit: f64, lines: usize) -> Result<String, Overflow> {
    let source = content_lines(en);
    let speaker = has_speaker(&source);
    let (head, body) = source.split_at(usize::from(speaker));
    let indent = if body.first().is_some_and(|line| line.starts_with('"')) {
        " "
    } else {
        ""
    };
    let mut out: Vec<String> = head.iter().map(|line| (*line).to_owned()).collect();
    let mut widest: (u32, &str) = (0, "");
    let mut over = false;
    if let Some(name) = head.first() {
        let width = advance(name, widths);
        if f64::from(width) > limit {
            widest = (width, name);
            over = true;
        }
    }
    let mut current: Option<String> = None;
    for word in body
        .iter()
        .flat_map(|line| line.split(' '))
        .filter(|word| !word.is_empty())
    {
        let width = advance(word, widths);
        if width > widest.0 {
            widest = (width, word);
        }
        if let Some(line) = current.as_mut() {
            let joined = format!("{line} {word}");
            if f64::from(advance(&joined, widths)) <= limit {
                *line = joined;
                continue;
            }
            out.extend(current.take());
        }
        let prefix = if out.len() > head.len() { indent } else { "" };
        let started = format!("{prefix}{word}");
        over |= f64::from(advance(&started, widths)) > limit;
        current = Some(started);
    }
    out.extend(current);
    if over || out.len() > lines {
        return Err(Overflow {
            needed: out.len(),
            word: widest.1.to_owned(),
            word_width: widest.0,
        });
    }
    let mut wrapped = out.join(NEWLINE);
    for _ in out.len().max(1)..lines {
        wrapped.push_str(NEWLINE);
    }
    Ok(wrapped)
}

fn printable(en: &str) -> bool {
    en.replace(NEWLINE, "")
        .bytes()
        .all(|c| (0x20..0x7F).contains(&c))
}

pub fn wrap_limit(texts: &[&str], widths: &[u32], base: f64, lines: usize) -> f64 {
    let mut limit = base;
    while limit + 1.0 <= base * WIDEN_CAP
        && texts
            .iter()
            .any(|en| rewrap(en, widths, limit, lines).is_err())
    {
        limit += 1.0;
    }
    limit
}

pub fn pad_width(wrapped: &str, widths: &[u32], limit: f64) -> Fixed {
    let mut lines: Vec<String> = wrapped.split(NEWLINE).map(str::to_owned).collect();
    let space = f64::from(glyph(b' ', widths));
    let widest = lines
        .iter()
        .map(|line| advance(line, widths))
        .max()
        .unwrap_or(0);
    let target = lines
        .iter()
        .rposition(|line| !line.trim().is_empty())
        .unwrap_or(0);
    let wanted = if space == 0.0 || f64::from(widest) > limit - space {
        0
    } else {
        ((limit - f64::from(advance(&lines[target], widths))) / space).floor() as usize
    };
    let padding = wanted.min(text::MESSAGE_LIMIT.saturating_sub(wrapped.len()));
    lines[target].push_str(&" ".repeat(padding));
    Fixed {
        text: lines.join(NEWLINE),
        padding,
        capped: padding < wanted,
    }
}

fn fixed_text(
    en: &str,
    widths: &[u32],
    limit: f64,
    lines: usize,
    widened: bool,
) -> Result<Fixed, Problem> {
    if !printable(en) {
        return Err(Problem::Characters);
    }
    let wrapped = rewrap(en, widths, limit, lines).map_err(Problem::Overflow)?;
    if wrapped.len() > text::MESSAGE_LIMIT {
        return Err(Problem::Bytes(wrapped.len()));
    }
    if widened {
        return Ok(pad_width(&wrapped, widths, limit));
    }
    Ok(Fixed {
        text: wrapped,
        padding: 0,
        capped: false,
    })
}

pub fn plan_with(
    items: &[Value],
    contexts: &BTreeMap<u64, Context>,
    rects: BTreeMap<Context, Rect>,
    widths: Vec<u32>,
    extra_lines: usize,
) -> Result<Plan> {
    let counts = line_counts(items, contexts);
    let mut lines = fixed_lines(items, contexts);
    for (&context, count) in lines.iter_mut() {
        if context == Context::Dialogue {
            *count += extra_lines;
        }
    }
    let mut owners: HashMap<String, u64> = HashMap::new();
    let mut entries = Vec::new();
    let mut limits = BTreeMap::new();
    for (&context, &count) in &lines {
        let texts: Vec<&str> = items
            .iter()
            .filter(|item| item_id(item).and_then(|id| contexts.get(&id)) == Some(&context))
            .map(|item| text::item_text(item, "en"))
            .filter(|en| !en.is_empty() && printable(en))
            .collect();
        let base = rects[&context].room() * count as f64;
        limits.insert(context, wrap_limit(&texts, &widths, base, count));
    }
    for item in items {
        let Some(id) = item_id(item) else { continue };
        let key = item
            .get("offset")
            .map_or_else(|| id.to_string(), Value::to_string);
        let owner = *owners.entry(key).or_insert(id);
        let Some(&context) = contexts.get(&id) else {
            continue;
        };
        if context == Context::Choice {
            continue;
        }
        let en = text::item_text(item, "en");
        if owner != id {
            if contexts.get(&owner) != Some(&context) {
                entries.push(Entry {
                    id,
                    context,
                    original: en.to_owned(),
                    result: Err(Problem::Shared(owner)),
                });
            }
            continue;
        }
        if en.is_empty() {
            continue;
        }
        let base = rects[&context].room() * lines[&context] as f64;
        let limit = limits[&context];
        entries.push(Entry {
            id,
            context,
            original: en.to_owned(),
            result: fixed_text(en, &widths, limit, lines[&context], limit > base),
        });
    }
    Ok(Plan {
        widths,
        rects,
        counts,
        lines,
        limits,
        entries,
    })
}

pub fn plan(iso: &Path, font: &str, items: &[Value], extra_lines: usize) -> Result<Plan> {
    let contexts = demo_messages(iso)?;
    let scene = Scene::new(disc::read_file(iso, ARCHIVE)?)?;
    let mut rects = BTreeMap::new();
    for context in Context::ALL {
        rects.insert(context, rect(&scene, context)?);
    }
    let widths = font_widths(&iplfont::story_font(font)?);
    plan_with(items, &contexts, rects, widths, extra_lines)
}

pub fn apply(iso: &Path, font: &str, items: &mut [Value]) -> Result<usize> {
    let mut plan = plan(iso, font, items, 0)?;
    if !plan.failures().is_empty() {
        plan = self::plan(iso, font, items, 1)?;
    }
    let failures = plan.failures();
    if !failures.is_empty() {
        bail!(
            "{} story messages do not fit the fixed text height in {font}; reword them:\n{}",
            failures.len(),
            failures.join("\n")
        );
    }
    let wrapped: HashMap<u64, &String> = plan
        .entries
        .iter()
        .filter_map(|entry| Some((entry.id, &entry.result.as_ref().ok()?.text)))
        .collect();
    let mut count = 0;
    for item in items.iter_mut() {
        if let Some(text) = item_id(item).and_then(|id| wrapped.get(&id)) {
            item["en"] = Value::String((*text).clone());
            count += 1;
        }
    }
    Ok(count)
}
