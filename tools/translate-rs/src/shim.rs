use crate::cave::{self, branch, Cave};
use crate::elf::{Elf, Symbol};
use crate::iplfont::SWITCH_PATHS;
use crate::relocate::{relocate, relocate_at};
use crate::text::{MENU_SIZE, STORY_PATHS};
use crate::toolchain::{compiler_for_source, flags_for_source};
use anyhow::{anyhow, bail, Context, Result};
use std::collections::BTreeMap;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;

pub const NOP: [u8; 4] = [0x60, 0x00, 0x00, 0x00];

pub const FONT_SOURCE: &str = "sdk/os/font.c";

pub const FONT_FUNCTIONS: [&str; 2] = ["OSGetFontEncode", "OSLoadFont"];

pub const MENU_SOURCE: &str = "ui/ttl_main.cpp";

pub const MENU_FUNCTIONS: [&str; 7] = [
    "menu_sDispStart",
    "menu_sDispStartMsgWin",
    "configGet",
    "menu_sDispConfig",
    "menufncZoid_ConfigMenu",
    "menu_MissionDemoScrPlay1",
    "menu_MissionDemoScr_MenuAfter_SetMsg1",
];

/// Offset of the reserved save byte that holds the chosen font (GameSaveRecord.field_1CA9).
pub const SAVED_FONT: usize = 0x1CA9;

/// First of three unused TXT_Menu placeholder messages that hold the font labels.
pub const FONT_LABEL_MESSAGE: usize = 17;

/// Unused TXT_Menu placeholder that holds the title screen legal lines and the translation credit.
pub const TITLE_TEXT_MESSAGE: usize = 24;

/// Unused TXT_Menu placeholder that holds the help line of the TEXT FONT entry.
pub const FONT_HELP_MESSAGE: usize = 21;

/// First of two unused TXT_Menu placeholders that hold the words of the TEXT FONT label.
pub const FONT_ENTRY_MESSAGE: usize = 22;

/// Menu cursor value of the TEXT FONT entry; 0 to 6 are the game's entries and 7 is EXIT.
pub const FONT_ENTRY: usize = 8;

const FONT_DECLARATIONS: &str = concat!(
    "s32 OSInitFont(void *font);\n",
    "HSD_JObj *HSD_JObjLoadJoint(void *description);\n",
    "void HSD_JObjRemoveAll(HSD_JObj *joint);\n",
    "void HSD_JObjAddChild(HSD_JObj *joint, HSD_JObj *child);\n",
    "s32 sGetAnimJoint(void *context, HSD_JObj *target);\n",
    "void HSD_JObjAddAnim(HSD_JObj *joint, void *animation, void *material, void *shape);\n",
    "void HSD_JObjReqAnim(HSD_JObj *joint, f32 frame);\n",
    "void HSD_AObjSetRate(void *animation, f32 rate);\n",
    "f32 putAscMtxLR(f32 matrix[3][4], s32 font, char *text, s32 right_align);\n",
    "\nvoid configGet(void)\n{",
);

const ROW_LOOP: &str = concat!(
    "                sSetAnim1(archive, 5, jobj, i == csN ? 2 : 1);\n",
    "            jobjDispAll(jobj);\n",
    "        }\n",
);

const ROW_ANIMATION: &str = concat!(
    "        if (crO != crN) {\n",
    "            csA = a3[crO + 1];\n",
    "            if (csAO == csA && end != 0) {\n",
    "                crO = crN;\n",
    "                csA = a2[crO + 1];\n",
    "                csAO = -1;\n",
    "            }\n",
    "        } else if (csA == a1[crN + 1]) {\n",
    "            if (end != 0)\n",
    "                csA = a2[crN + 1];\n",
    "        } else {\n",
    "            csA = a2[crN + 1];\n",
    "        }\n",
);

const MENU_STEP: &str = concat!(
    "            subMenu();\n",
    "            getSubMenuT();\n",
    "            ret = menu_sDispConfig(arc, cur);\n",
);

const MENU_MOVE: &str = concat!(
    "                if (sPad1->field_57 != 0)\n",
    "                    csN--;\n",
    "                if (sPad1->field_58 != 0)\n",
    "                    csN++;\n",
    "                if (csN < 0)\n",
    "                    csN = 7;\n",
    "                if ((u32)csN > 7)\n",
    "                    csN = 0;\n",
);

const MENU_CLAMP: &str = concat!(
    "            if (csN < 0)\n",
    "                csN = 7;\n",
    "            if ((u32)csN > 7)\n",
    "                csN = 0;\n",
    "            if (sPad1->pressed_a != 0 && crN == -1) {",
);

const MENU_OPTIONS: &str =
    "                if ((u32)csN != 7) {\n                    saveSb = sbN;";

/// Offsets from the row centre to its label and from the label to the font name, as f32 bits.
const LABEL_X: u32 = 0xC0F0_0000;
const LABEL_Y: u32 = 0x0000_0000;
const VALUE_X: u32 = 0x4000_0000;
const WORD_GAP: u32 = 0x3F4C_CCCD;
const VALUE_GAP: u32 = 0x3F80_0000;
const LABEL_FONT: u32 = 4;
const VALUE_FONT: u32 = 3;

fn font_row() -> String {
    format!(
        concat!(
            "{loop_end}",
            "        {{\n",
            "            HSD_JObj *row = GetChild(j27, 0, {entry}, -1, -1, -1);\n",
            "            u32 *table = *(u32 **)((u8 *)archive + 0x24);\n",
            "            u32 *model = (u32 *)((u32 *)table[0])[5];\n",
            "            u8 *last = (u8 *)GetChild(j28, 0, 6, -1, -1, -1);\n",
            "            f32 place[30];\n",
            "            f32 mtx[3][4];\n",
            "            f32 gap;\n",
            "            f32 step;\n",
            "            f32 left;\n",
            "            union {{ u32 u; f32 f; }} k;\n",
            "            s32 fresh = 0;\n",
            "            char *name;\n",
            "            char part[24];\n",
            "            s32 n;\n",
            "\n",
            "            if (row == 0) {{\n",
            "                u32 *desc = (u32 *)((u32 *)model[0])[2];\n",
            "                for (n = 0; n < 6; n++)\n",
            "                    desc = (u32 *)desc[3];\n",
            "                row = HSD_JObjLoadJoint(desc);\n",
            "                HSD_JObjRemoveAll(*(HSD_JObj **)((u8 *)row + 8));\n",
            "                *(HSD_JObj **)((u8 *)row + 8) = 0;\n",
            "                HSD_JObjAddChild(j27, row);\n",
            "                HiddenParts(GetChild(row, 0, 0, -1, -1, -1), 1);\n",
            "                fresh = 1;\n",
            "            }}\n",
            "            gap = *(f32 *)((u8 *)GetChild(j28, 0, 1, -1, -1, -1) + 0x60) - *(f32 *)((u8 *)GetChild(j28, 0, 0, -1, -1, -1) + 0x60);\n",
            "            step = *(f32 *)((u8 *)GetChild(j28, 0, 2, -1, -1, -1) + 0x60) - *(f32 *)((u8 *)GetChild(j28, 0, 1, -1, -1, -1) + 0x60);\n",
            "            if (gap < gap - gap ? step > gap : step < gap)\n",
            "                gap = step;\n",
            "            *(f32 *)((u8 *)place + 0x50) = *(f32 *)(last + 0x50);\n",
            "            *(f32 *)((u8 *)place + 0x60) = *(f32 *)(last + 0x60) + gap;\n",
            "            *(f32 *)((u8 *)place + 0x70) = *(f32 *)(last + 0x70);\n",
            "            jobjCopyPos((HSD_JObj *)place, row);\n",
            "            if (jobjAnim1(row) != 0 || fresh != 0) {{\n",
            "                u32 context[6];\n",
            "                n = csN == {entry} ? 2 : 1;\n",
            "                context[0] = (u32)j27;\n",
            "                context[1] = 0;\n",
            "                context[2] = model[0];\n",
            "                context[3] = model[1] != 0 ? ((u32 *)model[1])[n] : 0;\n",
            "                context[4] = model[2] != 0 ? ((u32 *)model[2])[n] : 0;\n",
            "                context[5] = model[3] != 0 ? ((u32 *)model[3])[n] : 0;\n",
            "                if (sGetAnimJoint(context, GetChild(j27, 0, 6, -1, -1, -1)) != 0) {{\n",
            "                    HSD_JObjAddAnim(row, (void *)context[3], (void *)context[4], (void *)context[5]);\n",
            "                    k.u = 0;\n",
            "                    HSD_JObjReqAnim(row, k.f);\n",
            "                    if (*(void **)((u8 *)row + 0x7C) != 0) {{\n",
            "                        k.u = 0x3F800000;\n",
            "                        HSD_AObjSetRate(*(void **)((u8 *)row + 0x7C), k.f);\n",
            "                    }}\n",
            "                }}\n",
            "            }}\n",
            "            if (crN != 6 && crO != 6) {{\n",
            "                jobjDispAll(row);\n",
            "                for (n = 0; n < 12; n++)\n",
            "                    ((f32 *)mtx)[n] = *(f32 *)((u8 *)row + 0x44 + n * 4);\n",
            "                k.u = 0x{label_x:08X};\n",
            "                mtx[0][3] += k.f;\n",
            "                k.u = 0x{label_y:08X};\n",
            "                mtx[1][3] += k.f;\n",
            "                left = mtx[0][3];\n",
            "                k.f = putAscMtxLR(mtx, {label_font}, GetMenuMsgAdr({label}), 0);\n",
            "                mtx[0][3] += k.f;\n",
            "                k.u = 0x{word_gap:08X};\n",
            "                mtx[0][3] += k.f;\n",
            "                putAscMtxLR(mtx, {label_font}, GetMenuMsgAdr({label} + 1), 0);\n",
            "                mtx[0][3] = left;\n",
            "                if (crN == {entry}) {{\n",
            "                    mtx[1][3] += gap;\n",
            "                    if (sbTA != 0 && sbTA != 1) {{\n",
            "                        SetAnimArc2(archive, 4, 0);\n",
            "                        sbTA = 0;\n",
            "                    }}\n",
            "                    if (jobjAnim(archive->joints[4]) != 0) {{\n",
            "                        SetAnimArc2(archive, 4, 1);\n",
            "                        sbTA = 1;\n",
            "                    }}\n",
            "                    last = (u8 *)GetChild(archive->joints[18], 0, 0, -1, -1, -1);\n",
            "                    *(f32 *)((u8 *)place + 0x50) = *(f32 *)(last + 0x50);\n",
            "                    *(f32 *)((u8 *)place + 0x60) = mtx[1][3];\n",
            "                    *(f32 *)((u8 *)place + 0x70) = *(f32 *)(last + 0x70);\n",
            "                    jobjCopyPos((HSD_JObj *)place, archive->joints[4]);\n",
            "                    jobjDispAll(archive->joints[4]);\n",
            "                    k.u = 0x{value_x:08X};\n",
            "                    mtx[0][3] += k.f;\n",
            "                    name = GetMenuMsgAdr({names} + IveSaveFlag.field_1CA9[0]);\n",
            "                    while (name != 0 && *name != 0) {{\n",
            "                        n = 0;\n",
            "                        while (*name != 0 && *name != 32 && n < 23)\n",
            "                            part[n++] = *name++;\n",
            "                        part[n] = 0;\n",
            "                        k.f = putAscMtxLR(mtx, {value_font}, part, 0);\n",
            "                        mtx[0][3] += k.f;\n",
            "                        k.u = 0x{value_gap:08X};\n",
            "                        mtx[0][3] += k.f;\n",
            "                        while (*name == 32)\n",
            "                            name++;\n",
            "                    }}\n",
            "                }} else if (sbT == -1 && sbTO == -1) {{\n",
            "                    sbTA = -1;\n",
            "                }}\n",
            "            }}\n",
            "        }}\n",
        ),
        loop_end = ROW_LOOP,
        entry = FONT_ENTRY,
        label = FONT_ENTRY_MESSAGE,
        names = FONT_LABEL_MESSAGE,
        label_x = LABEL_X,
        label_y = LABEL_Y,
        value_x = VALUE_X,
        word_gap = WORD_GAP,
        value_gap = VALUE_GAP,
        label_font = LABEL_FONT,
        value_font = VALUE_FONT,
    )
}

pub const FONT_ENCODE: &str = concat!(
    "u16 OSGetFontEncode(void)\n",
    "{\n",
    "    static u16 fontEncode = 0xFFFF;\n",
    "    if (fontEncode <= 1) {\n",
    "        return fontEncode;\n",
    "    }\n",
    "    switch (*(int *)OSPhysicalToCached(0xCC)) {\n",
    "    case VI_NTSC:\n",
    "        fontEncode =\n",
    "            (__VIRegs[VI_DTV_STAT] & 2) ? OS_FONT_ENCODE_SJIS : OS_FONT_ENCODE_ANSI;\n",
    "        break;\n",
    "\n",
    "    case VI_PAL:\n",
    "    case VI_MPAL:\n",
    "    case VI_DEBUG:\n",
    "    case VI_DEBUG_PAL:\n",
    "    case VI_EURGB60:\n",
    "    default:\n",
    "        fontEncode = OS_FONT_ENCODE_ANSI;\n",
    "    }\n",
    "\n",
    "    return fontEncode;\n",
    "}",
);

pub const FONT_READ: &str = concat!(
    "static inline u32 ReadFont(void *img)\n",
    "{\n",
    "    if (OSGetFontEncode() == OS_FONT_ENCODE_SJIS) {\n",
    "        ReadROM(img, OS_FONT_ROM_SIZE_SJIS, 0x1AFF00);\n",
    "    } else {\n",
    "        ReadROM(img, OS_FONT_ROM_SIZE_ANSI, 0x1FCF00);\n",
    "    }\n",
    "\n",
    "    return GetFontSize(img);\n",
    "}",
);

fn name_words(path: &str, count: usize) -> Vec<u32> {
    let mut raw = path.as_bytes().to_vec();
    raw.resize(count * 4, 0);
    raw.as_chunks::<4>()
        .0
        .iter()
        .map(|word| u32::from_be_bytes(*word))
        .collect()
}

pub fn name_select(paths: &[&str], indent: &str) -> (usize, String) {
    name_select_into(paths, indent, "name")
}

pub fn name_select_into(paths: &[&str], indent: &str, array: &str) -> (usize, String) {
    let count = paths
        .iter()
        .map(|path| path.len() / 4 + 1)
        .max()
        .unwrap_or(1);
    let words: Vec<Vec<u32>> = paths.iter().map(|path| name_words(path, count)).collect();
    let mut code = String::new();
    for (index, word) in words[0].iter().enumerate() {
        code.push_str(&format!("{indent}{array}[{index}] = 0x{word:08X};\n"));
    }
    for (font, other) in words.iter().enumerate().skip(1) {
        code.push_str(&format!("{indent}if (font == {font}) {{\n"));
        for (index, word) in other.iter().enumerate() {
            if *word != words[0][index] {
                code.push_str(&format!("{indent}    {array}[{index}] = 0x{word:08X};\n"));
            }
        }
        code.push_str(&format!("{indent}}}\n"));
    }
    (count, code)
}

pub fn switch_font_read() -> String {
    let (count, names) = name_select(&SWITCH_PATHS, "    ");
    format!(
        concat!(
            "static inline u32 ReadFont(void *img)\n{{\n    DVDFileInfo file;\n",
            "    u32 name[{count}];\n    u32 font = IveSaveFlag[0x{saved:X}];\n\n",
            "    if (font > 2)\n        font = 0;\n",
            "    TXT_Menu_dat[{spare}] = font + 1;\n{names}",
            "    if (!DVDOpen((char *)name, &file))\n        return 0;\n",
            "    DVDReadPrio(&file, img, (s32)file.length, 0, 2);\n    DVDClose(&file);\n",
            "    return GetFontSize(img);\n}}",
        ),
        count = count,
        saved = SAVED_FONT,
        spare = MENU_SIZE,
        names = names
    )
}

pub fn font_shim() -> Vec<(String, String)> {
    let pair = |old: &str, new: &str| (old.to_string(), new.to_string());
    vec![
        pair(
            "#include \"os_font.h\"\n",
            "#include \"os_font.h\"\n#include \"dvd_file.h\"\nextern u8 IveSaveFlag[];\nextern u8 TXT_Menu_dat[];\n",
        ),
        pair(
            FONT_ENCODE,
            "u16 OSGetFontEncode(void)\n{\n    return OS_FONT_ENCODE_SJIS;\n}",
        ),
        (FONT_READ.to_string(), switch_font_read()),
        pair(
            "        if (OSGetFontEncode() == OS_FONT_ENCODE_SJIS) {\n            int fontCode;",
            "        if (0) {\n            int fontCode;",
        ),
    ]
}

pub const STORY_READ: &str = concat!(
    "                menudemokeywait = 1;\n",
    "                menudemocur = 1;\n",
    "                if (menudemomsg == 0) {\n",
    "                    start = 16000;\n",
    "                } else {\n",
    "                    sReadLenPtr(\"etc/demo/text.bin\", &start, (menudemomsg - 1) * 4, 4);\n",
    "                }\n",
    "                sReadLenPtr(\"etc/demo/text.bin\", &end, menudemomsg * 4, 4);\n",
    "                size = sReadLenPtr(\"etc/demo/text.bin\", menudispwinstr, start, end - start);\n",
);

const TITLE_PASS: &str = concat!(
    "            if (menumode != 0 && menumode != 0 && menumode > 1 && menudispwinstr[0] != 0) {\n",
    "                sPutFontRectC(menudispwinstr, GetChild(((MenuArchive *)menu1p)->joints[7], 0, 0, -1, -1, -1), GetChild(((MenuArchive *)menu1p)->joints[7], 0, 0, 0, -1, -1), (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);\n",
    "            }\n",
);
const TITLE_WIDTHS: [u32; 3] = [0x41F0_0000, 0x41F0_0000, 0x41F0_0000];
const TITLE_TOP: u32 = 0xC18E_6666;
const HELP_RAISE: u32 = 0x3EDA_36E3;
const BAND_RAISE: u32 = 0x3ECC_CCCD;
const TITLE_STEP: u32 = 0x3FD0_0000;
const TITLE_HEIGHT: u32 = 0x3FC0_0000;
const TITLE_SHADOW: u32 = 0x3DCC_CCCD;

fn title_text() -> (String, String) {
    (
        TITLE_PASS.to_string(),
        format!(
            concat!(
                "            if (menumode != 0) {{\n",
                "                volatile union {{ u32 u; f32 f; }} q;\n",
                "                volatile s32 n;\n",
                "                volatile s32 row;\n",
                "                volatile f32 top;\n",
                "                volatile f32 half;\n",
                "                volatile f32 ox;\n",
                "                volatile f32 oy;\n",
                "                volatile s32 pass;\n",
                "                f32 corner[2][32];\n",
                "                u32 width[3];\n",
                "                char line[200];\n",
                "                char *text;\n",
                "                GXColor ink;\n",
                "                GXColor clear;\n",
                "\n",
                "                width[0] = 0x{w0:08X};\n",
                "                width[1] = 0x{w1:08X};\n",
                "                width[2] = 0x{w2:08X};\n",
                "                text = GetMenuMsgAdr({message});\n",
                "                for (n = 0; n < 12; n++) {{\n",
                "                    corner[0][17 + n] = *(f32 *)((u8 *)GetChild(((MenuArchive *)menu1p)->joints[7], 0, 0, -1, -1, -1) + 0x44 + n * 4);\n",
                "                    corner[1][17 + n] = corner[0][17 + n];\n",
                "                }}\n",
                "                q.u = 0x{top:08X};\n",
                "                top = q.f;\n",
                "                *(u32 *)&clear = 0;\n",
                "                for (row = 0; row < 3; row++) {{\n",
                "                    n = 0;\n",
                "                    while (*text != 0 && *text != 13 && n < 199)\n",
                "                        line[n++] = *text++;\n",
                "                    line[n] = 0;\n",
                "                    while (*text == 13 || *text == 10)\n",
                "                        text++;\n",
                "                    q.u = width[row];\n",
                "                    half = q.f;\n",
                "                    *(u32 *)&ink = 0x000000FF;\n",
                "                    for (pass = 2; pass < 3; pass++) {{\n",
                "                        q.u = 0x{shadow:08X};\n",
                "                        ox = q.f;\n",
                "                        oy = q.f;\n",
                "                        if (pass & 1)\n",
                "                            ox = -ox;\n",
                "                        if (pass & 2)\n",
                "                            oy = -oy;\n",
                "                        corner[0][20] = ox - half;\n",
                "                        corner[1][20] = ox + half;\n",
                "                        corner[0][24] = top + oy;\n",
                "                        q.u = 0x{height:08X};\n",
                "                        corner[1][24] = corner[0][24] - q.f;\n",
                "                        sPutFontRectC(line, (HSD_JObj *)corner[0], (HSD_JObj *)corner[1], ink, clear, 0, 2);\n",
                "                    }}\n",
                "                    corner[0][20] = -half;\n",
                "                    corner[1][20] = half;\n",
                "                    corner[0][24] = top;\n",
                "                    corner[1][24] = top - q.f;\n",
                "                    *(u32 *)&ink = 0xFFFFFFFF;\n",
                "                    sPutFontRectC(line, (HSD_JObj *)corner[0], (HSD_JObj *)corner[1], ink, clear, 0, 2);\n",
                "                    q.u = 0x{step:08X};\n",
                "                    top -= q.f;\n",
                "                }}\n",
                "                if (menumode > 1 && menudispwinstr[0] != 0) {{\n",
                "                    for (n = 0; n < 12; n++) {{\n",
                "                        corner[0][17 + n] = *(f32 *)((u8 *)GetChild(((MenuArchive *)menu1p)->joints[7], 0, 0, -1, -1, -1) + 0x44 + n * 4);\n",
                "                        corner[1][17 + n] = *(f32 *)((u8 *)GetChild(((MenuArchive *)menu1p)->joints[7], 0, 0, 0, -1, -1) + 0x44 + n * 4);\n",
                "                    }}\n",
                "                    q.u = 0x{raise:08X};\n",
                "                    corner[0][24] += q.f;\n",
                "                    corner[1][24] += q.f;\n",
                "                    *(u32 *)&ink = 0xFFFFFFFF;\n",
                "                    sPutFontRectC(menudispwinstr, (HSD_JObj *)corner[0], (HSD_JObj *)corner[1], ink, clear, 0, 2);\n",
                "                }}\n",
                "            }}\n",
            ),
            message = TITLE_TEXT_MESSAGE,
            w0 = TITLE_WIDTHS[0],
            w1 = TITLE_WIDTHS[1],
            w2 = TITLE_WIDTHS[2],
            top = TITLE_TOP,
            step = TITLE_STEP,
            height = TITLE_HEIGHT,
            shadow = TITLE_SHADOW,
            raise = HELP_RAISE,
        ),
    )
}

pub fn menu_shim(font_buffer: u32) -> Vec<(String, String)> {
    let pair = |old: &str, new: String| (old.to_string(), new);
    vec![
        pair(
            "    VsBpLimit = IveSaveFlag.cfg_bplimit;\n    configSet();\n}",
            format!(
                concat!(
                    "    VsBpLimit = IveSaveFlag.cfg_bplimit;\n",
                    "    if (IveSaveFlag.field_1CA9[0] > 2)\n",
                    "        IveSaveFlag.field_1CA9[0] = 0;\n",
                    "    if (TXT_Menu_dat[{spare}] != 0 && IveSaveFlag.field_1CA9[0] + 1 != TXT_Menu_dat[{spare}])\n",
                    "        OSInitFont(*(void **)0x{buffer:08X});\n",
                    "    configSet();\n}}",
                ),
                spare = MENU_SIZE,
                buffer = font_buffer
            ),
        ),
        pair(
            "void configGet(void)\n{",
            FONT_DECLARATIONS.to_string(),
        ),
        pair(
            "        help = helpTBL[csN];\n        if (csN < 0)\n            help = -1;\n",
            format!(
                concat!(
                    "        help = helpTBL[csN];\n        if (csN < 0)\n            help = -1;\n",
                    "        if (csN == {entry})\n            help = {help};\n",
                ),
                entry = FONT_ENTRY,
                help = FONT_HELP_MESSAGE
            ),
        ),
        pair(
            STORY_READ,
            {
                let (count, names) = name_select_into(&STORY_PATHS, "                ", "story");
                format!(
                    concat!(
                        "                menudemokeywait = 1;\n",
                        "                menudemocur = 1;\n",
                        "                u32 font = IveSaveFlag.field_1CA9[0];\n",
                        "                u32 story[{count}];\n",
                        "{names}",
                        "                if (menudemomsg == 0) {{\n",
                        "                    start = 16000;\n",
                        "                }} else {{\n",
                        "                    sReadLenPtr((char *)story, &start, (menudemomsg - 1) * 4, 4);\n",
                        "                }}\n",
                        "                sReadLenPtr((char *)story, &end, menudemomsg * 4, 4);\n",
                        "                size = sReadLenPtr((char *)story, menudispwinstr, start, end - start);\n",
                    ),
                    count = count,
                    names = names
                )
            },
        ),
        pair(ROW_LOOP, font_row()),
        pair(
            ROW_ANIMATION,
            ROW_ANIMATION
                .replace("crO + 1", "(crO > 6 ? -1 : crO) + 1")
                .replace("crN + 1", "(crN > 6 ? -1 : crN) + 1"),
        ),
        pair(
            MENU_STEP,
            format!(
                concat!(
                    "            if (crN != {entry}) {{\n",
                    "                subMenu();\n",
                    "                getSubMenuT();\n",
                    "            }} else if (sPad1->field_59 != 0 || sPad1->field_5A != 0) {{\n",
                    "                configPut();\n",
                    "                if (sPad1->field_5A != 0)\n",
                    "                    IveSaveFlag.field_1CA9[0] = IveSaveFlag.field_1CA9[0] < 2 ? IveSaveFlag.field_1CA9[0] + 1 : 0;\n",
                    "                else\n",
                    "                    IveSaveFlag.field_1CA9[0] = IveSaveFlag.field_1CA9[0] > 0 ? IveSaveFlag.field_1CA9[0] - 1 : 2;\n",
                    "                configGet();\n",
                    "                SeSelectB();\n",
                    "            }}\n",
                    "            ret = menu_sDispConfig(arc, cur);\n",
                ),
                entry = FONT_ENTRY
            ),
        ),
        pair(
            MENU_MOVE,
            concat!(
                "                if (sPad1->field_57 != 0)\n",
                "                    csN = csN == 0 ? 7 : csN == 7 ? 8 : csN == 8 ? 6 : csN - 1;\n",
                "                if (sPad1->field_58 != 0)\n",
                "                    csN = csN == 6 ? 8 : csN == 8 ? 7 : csN == 7 ? 0 : csN + 1;\n",
            )
            .to_string(),
        ),
        pair(MENU_CLAMP, MENU_CLAMP.replace("csN > 7", "csN > 8")),
        pair(MENU_OPTIONS, MENU_OPTIONS.replace("csN != 7", "csN < 7")),
        title_text(),
        pair(
            "        jobjAnim(((MenuArchive *)menu1p)->joints[15]);\n        HSD_JObjDispAll(child, 0, 7, 0);\n",
            format!(
                concat!(
                    "        jobjAnim(((MenuArchive *)menu1p)->joints[15]);\n",
                    "        {{\n",
                    "            volatile union {{ u32 u; f32 f; }} q;\n",
                    "            volatile f32 y;\n",
                    "\n",
                    "            q.u = 0x{raise:08X};\n",
                    "            y = *(f32 *)((u8 *)child + 0x3C);\n",
                    "            *(f32 *)((u8 *)child + 0x3C) = y + q.f;\n",
                    "            HSD_JObjSetMtxDirtySub(child);\n",
                    "            HSD_JObjDispAll(child, 0, 7, 0);\n",
                    "            *(f32 *)((u8 *)child + 0x3C) = y;\n",
                    "            HSD_JObjSetMtxDirtySub(child);\n",
                    "        }}\n",
                ),
                raise = BAND_RAISE,
            ),
        ),
    ]
}

pub const STAFF_SOURCE: &str = "text/dispAscii.c";
const STAFF_FUNCTIONS: [&str; 1] = ["dispAscii"];
const STAFF_SCROLL: &str = concat!(
    "        if (entry->scroll_y > 100.0f) {\n",
    "            entry->text[0] = 0;\n",
    "            entry->scroll_y = 0.0f;\n",
    "        }\n",
);
const STAFF_OUTLINE: u32 = 0x3E4C_CCCD;
const STAFF_SHADOWS: [(i8, i8); 1] = [(1, -1)];

pub fn staff_shim() -> Vec<(String, String)> {
    let mut code = format!(
        concat!(
            "{scroll}",
            "        if (entry->text[0] != 0 && entry->text[0] != 33) {{\n",
            "            volatile union {{ u32 u; f32 f; }} k;\n",
            "            volatile f32 x0;\n",
            "            volatile f32 y0;\n",
            "            volatile f32 x1;\n",
            "            volatile f32 y1;\n",
            "            volatile f32 d;\n",
            "            GXColor ink;\n",
            "            GXColor clear;\n",
            "\n",
            "            k.u = 0x{offset:08X};\n",
            "            d = k.f;\n",
            "            x0 = j0->matrix[0][3];\n",
            "            y0 = j0->matrix[1][3];\n",
            "            x1 = j1->matrix[0][3];\n",
            "            y1 = j1->matrix[1][3];\n",
            "            *(u32 *)&clear = 0;\n",
            "            *(u32 *)&ink = 0x000000FF;\n",
        ),
        scroll = STAFF_SCROLL,
        offset = STAFF_OUTLINE,
    );
    for (x, y) in STAFF_SHADOWS {
        let (sx, sy) = (if x < 0 { '-' } else { '+' }, if y < 0 { '-' } else { '+' });
        code.push_str(&format!(
            concat!(
                "            j0->matrix[0][3] = x0 {sx} d;\n",
                "            j0->matrix[1][3] = y0 {sy} d;\n",
                "            j1->matrix[0][3] = x1 {sx} d;\n",
                "            j1->matrix[1][3] = y1 {sy} d;\n",
                "            sPutFontRect(entry->text, j0, j1, ink, clear, 0, 2);\n",
            ),
            sx = sx,
            sy = sy,
        ));
    }
    code.push_str(concat!(
        "            j0->matrix[0][3] = x0;\n",
        "            j0->matrix[1][3] = y0;\n",
        "            j1->matrix[0][3] = x1;\n",
        "            j1->matrix[1][3] = y1;\n",
        "            *(u32 *)&ink = 0xFFFFFFFF;\n",
        "            sPutFontRect(entry->text, j0, j1, ink, clear, 0, 2);\n",
        "        }\n",
    ));
    vec![(STAFF_SCROLL.to_string(), code)]
}

pub const KERNEL_SOURCE: &str = "sdk/os/kernel.c";

pub const KERNEL_FUNCTION: &str = "OSInit";

pub const KERNEL_ARENA: &str = "OSSetArenaLo(!BootInfo->arenaLo ? &__ArenaLo : BootInfo->arenaLo);";

pub const KERNEL_STACK: &str =
    "OSSetArenaLo((void *)(((u32)(char *)&_stack_addr + 0x1F) & 0xFFFFFFE0));";

pub fn kernel_shim(reference: &Elf) -> Result<Vec<(String, String)>> {
    let end = cave::ADDRESS + cave::CAPACITY as u32;
    let stack = original(reference, "_stack_addr")?.address;
    let rise = end
        .checked_sub(stack)
        .filter(|rise| rise + 0x1F < 0x8000 && end.is_multiple_of(32))
        .ok_or_else(|| anyhow!("the code cave end {end:08X} is out of reach of _stack_addr"))?;
    Ok(vec![
        (
            KERNEL_ARENA.to_string(),
            format!("OSSetArenaLo(!BootInfo->arenaLo ? (void *)0x{end:08X} : BootInfo->arenaLo);"),
        ),
        (
            KERNEL_STACK.to_string(),
            format!(
                "OSSetArenaLo((void *)(((u32)(char *)&_stack_addr + 0x{:X}) & 0xFFFFFFE0));",
                rise + 0x1F
            ),
        ),
    ])
}

pub struct Source {
    pub name: &'static str,
    pub edits: Vec<(String, String)>,
    pub functions: Vec<&'static str>,
}

pub fn sources(reference: &Elf) -> Result<Vec<Source>> {
    let buffer = original(reference, "FontData")?.address;
    Ok(vec![
        Source {
            name: FONT_SOURCE,
            edits: font_shim(),
            functions: FONT_FUNCTIONS.to_vec(),
        },
        Source {
            name: MENU_SOURCE,
            edits: menu_shim(buffer),
            functions: MENU_FUNCTIONS.to_vec(),
        },
        Source {
            name: STAFF_SOURCE,
            edits: staff_shim(),
            functions: STAFF_FUNCTIONS.to_vec(),
        },
    ])
}

pub struct Shim {
    pub patches: BTreeMap<u32, Vec<u8>>,
    pub cave: Cave,
    pub moved: BTreeMap<&'static str, (u32, usize)>,
}

pub fn compile_object(root: &Path, path: &Path, original: &Path, work: &Path) -> Result<Elf> {
    let compiler = compiler_for_source(root, original)?;
    let name = path
        .file_name()
        .ok_or_else(|| anyhow!("{} has no file name", path.display()))?
        .to_string_lossy();
    let stem = path
        .file_stem()
        .ok_or_else(|| anyhow!("{} has no file name", path.display()))?;
    let output = work.join(stem).with_extension("o");
    let result = Command::new(&compiler)
        .args(flags_for_source(root, original))
        .arg("-i")
        .arg(original.parent().unwrap_or(Path::new("")))
        .arg("-i")
        .arg(path.parent().unwrap_or(Path::new("")))
        .arg(path)
        .arg("-o")
        .arg(&output)
        .current_dir(root)
        .output()
        .with_context(|| format!("run {}", compiler.display()))?;
    if !result.status.success() {
        bail!(
            "{name}: compile failed ({})\n{}{}",
            result.status,
            String::from_utf8_lossy(&result.stdout),
            String::from_utf8_lossy(&result.stderr)
        );
    }
    Elf::read(&output)
}

fn find(text: &[u8], pattern: &[u8], from: usize) -> Option<usize> {
    text[from..]
        .windows(pattern.len())
        .position(|window| window == pattern)
        .map(|at| from + at)
}

fn replace_count(text: &[u8], old: &str, new: &str, name: &str, count: usize) -> Result<Vec<u8>> {
    let pattern = old.as_bytes();
    let mut places = Vec::new();
    let mut from = 0;
    while let Some(at) = find(text, pattern, from) {
        places.push(at);
        from = at + pattern.len();
    }
    if places.len() != count {
        bail!(
            "shim anchor found {} times in {name}, expected {count}: {old:?}",
            places.len()
        );
    }
    let mut output = Vec::new();
    let mut last = 0;
    for at in places {
        output.extend_from_slice(&text[last..at]);
        output.extend_from_slice(new.as_bytes());
        last = at + pattern.len();
    }
    output.extend_from_slice(&text[last..]);
    Ok(output)
}

fn compile_source(root: &Path, work: &Path, name: &str, edits: &[(String, String)]) -> Result<Elf> {
    let original = root.join("src").join(name);
    let file = original
        .file_name()
        .ok_or_else(|| anyhow!("{name} has no file name"))?;
    let directory = work.join(name.replace('/', "_"));
    fs::create_dir_all(&directory)?;
    let path = directory.join(file);
    let mut text = fs::read(&original).with_context(|| format!("read {}", original.display()))?;
    for (old, new) in edits {
        let count = if old == STORY_READ { 2 } else { 1 };
        text = replace_count(&text, old, new, name, count)?;
    }
    fs::write(&path, text)?;
    compile_object(root, &path, &original, &directory)
}

fn original<'a>(reference: &'a Elf, name: &str) -> Result<&'a Symbol> {
    reference
        .named(name)
        .first()
        .copied()
        .ok_or_else(|| anyhow!("{name} is not in the original ELF"))
}

fn compiled_size(compiled: &Elf, function: &str, name: &str) -> Result<u32> {
    compiled
        .functions()
        .iter()
        .find(|item| item.name == function)
        .map(|item| item.size)
        .ok_or_else(|| anyhow!("{function} is not in the compiled {name}"))
}

fn in_place(compiled: &Elf, reference: &Elf, target: &Symbol, size: u32) -> Result<Vec<u8>> {
    let resized = Symbol {
        size,
        ..target.clone()
    };
    let mut code = relocate(compiled, reference, &resized)?;
    while code.len() < target.size as usize {
        code.extend_from_slice(&NOP);
    }
    Ok(code)
}

fn kernel_patch(reference: &Elf, root: &Path, work: &Path) -> Result<(u32, Vec<u8>)> {
    let edits = kernel_shim(reference)?;
    let compiled = compile_source(root, work, KERNEL_SOURCE, &edits)?;
    let target = original(reference, KERNEL_FUNCTION)?;
    let size = compiled_size(&compiled, KERNEL_FUNCTION, KERNEL_SOURCE)?;
    if size != target.size {
        bail!(
            "{KERNEL_FUNCTION} with the arena above the code cave is {size} bytes, the original is {}",
            target.size
        );
    }
    Ok((
        target.address,
        in_place(&compiled, reference, target, size)?,
    ))
}

pub fn shim_code(reference: &Elf, root: &Path, work: &Path) -> Result<Shim> {
    let work: PathBuf = fs::canonicalize(work)?;
    let mut patches = BTreeMap::new();
    let mut cave = Cave::default();
    let mut moved = BTreeMap::new();
    for Source {
        name,
        edits,
        functions,
    } in sources(reference)?
    {
        let compiled = compile_source(root, &work, name, &edits)?;
        for function in functions {
            let target = original(reference, function)?;
            let size = compiled_size(&compiled, function, name)?;
            if size <= target.size {
                patches.insert(
                    target.address,
                    in_place(&compiled, reference, target, size)?,
                );
                continue;
            }
            let address = cave.next();
            let code = relocate_at(&compiled, reference, target, address)?;
            cave.push(function, &code)?;
            let mut stub = branch(target.address, address)?.to_vec();
            while stub.len() < target.size as usize {
                stub.extend_from_slice(&NOP);
            }
            patches.insert(target.address, stub);
            moved.insert(function, (address, code.len()));
        }
    }
    if !cave.is_empty() {
        let (address, code) = kernel_patch(reference, root, &work)?;
        patches.insert(address, code);
    }
    Ok(Shim {
        patches,
        cave,
        moved,
    })
}
