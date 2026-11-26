# Zoids VS. III text inventory

Every place the game shows Japanese, how it is extracted, and how it goes back in. `tools/translate-rs` holds both steps: the `extract` binary writes the JSON files in this folder from the Japanese disc, and `zvs3-translate` builds the English disc from them.

## Script text

| Source | File | Entries | Notes |
| --- | --- | --- | --- |
| Menu help lines and dialog boxes | `etc/TXT_Menu.BIN` -> `TXT_Menu.json` | 1178 slots, 102 distinct texts | Offsets are the `TXT_Menu` table in the DOL. The game copies 16558 bytes into a fixed buffer, so the English file must stay within that size. |
| Story scenes | `etc/demo/text.BIN` -> `story.json` | 1807 | A table of 4000 end offsets followed by the text. The game reads each message by offset, so English can be longer than the Japanese (399 bytes per message). Choice menus are one message with two lines of at most 79 bytes. The build wraps dialogue to one text height. |
| Mission info | `menu/map_info_dat/*.mg` -> `map_info.json` | 567 distinct | 13056-byte records. Title 100, victory 80, defeat 80 bytes; per unit (17 of them, 0x24C bytes each from 0x12C): name 32, text 100, panel heading 50 at +0x114, panel text at +0x146 (262). Drawn with `sPutFontRect`, which shrinks text to fit its box. |
| Tutorial messages | `menu/map_info_dat/*.msg` -> `help.json` | 18 | 0x110-byte records, text at +0x10 (256 bytes). |
| Zoid, part, pilot names | `etc/n_Zoid.dat`, `n_Parts.dat`, `n_Person.dat` -> `names.json` | 872 distinct | Zoid record 0x7FC: name 31 bytes, variant line 41 bytes at +0x1F. Part record 0x124: name 51, short name 21 at +0x33. Pilot record 0x68: name 32. List rows use the menu sprite font: uppercase A-Z, 0-9, `/-()&!?*+`, space and lowercase m only. |
| Part and pilot descriptions | `weapon/ID/wpNNN.txt`, `chara/manNNN.txt` -> `details.json` | 538 | Whole files, read into a 397-byte buffer. |
| DOL strings | `main.dol` -> `dol_strings.json` | 167 found, most are debug output | Disc errors, memory card messages, on-screen labels and the ten AI state names are translated. Each must fit the original byte size. |
| Disc banner | `OPENING.BNR` -> `banner.json` | 5 | Title, maker and description shown by the IPL and emulators. |

The staff roll is text: `epilogue.json` is written to `epilogue/epilogue.txt`, which the game scrolls with the story font. The original file is 98 empty lines and the Japanese credits are seven pictures in `epilogue/ending.dat` (images 0x10E4C0 to 0x28E4C0); the build blanks those pictures. `dispAscii` draws one black copy of each line down and right of the white text so it reads over the bright ending scene. Name spellings come from the publisher's English credits left on the disc (`epilogue/epilogue.txt.#`) where it has them. The first lines credit the translation and state the license.

The disc also carries the English script of Zoids: Battle Legends (`etc/demo_US`, `menu/map_info_dat_US`). The game never loads it. It is the reference for official spellings of the VS. II cast and parts.

## Textures

Found with `dump_textures` (menu, disp, epilogue and ascii archives, 784 unique textures) and Tesseract `jpn` over the dump, then checked on screen in the emulator.

| Texture | Fix |
| --- | --- |
| `menu/battle_menu/battle_entry.dat` image 0xA2C0, pilot rating labels 武器 / 旋回 / 格闘 | Redrawn as SHOT / TURN / MELEE with `label_art` (the pilot record fields are bullet, turn and melee bonuses). |
| `menu/loading/loading.dat` images 0x3580 and 0x7580, ロード中です and the stick warning | Blanked; the same texture already says NOW LOADING and DO NOT TOUCH THE CONTROL STICK OR C STICK. |
| `disp/order.dat` image 0x1880, partner orders カクトウ / ホウゲキ / ゴエイ / エンゴ | Redrawn as MELEE / SHOOT / GUARD / COVER. |
| `disp/div/pause.dat` image 0x4760, 勝利 + 条件 on the pause screen | Redrawn as one outlined word, OBJECTIVE, split across the two side-by-side cells. |
| `menu/battle_menu/detail.dat` image 0x9B40, the stat labels of the Setting Detail and part detail screens (耐久力, 移動力, 防御力, 格闘性能±値, 旋回性能, 索敵範囲, 重量 and so on) | Redrawn in English. Labels are assembled from shared cells, some stored a quarter turn clockwise, so each cell holds one word: DURABILITY (HP), SPEED (SP), DEFENSE (DP), ATTACK (AP), MELEE / SHOT / TURN + ABILITY, +/-, SCAN / RADAR / ATTACK + RANGE, RDS, LOCK-ON COUNT, WT. Words are sized to fit their cells without squeezing. |
| `menu/battle_menu/farm/farm.dat` image 0x40F80, 飛行 / ゾイド / 禁止 | Redrawn as NO FLYING ZOIDS. The game draws the three cells side by side, so the line is cut across them. |
| `menu/vs_menu/vs_menu.dat` image 0x22620, 完了 and its glow | Redrawn as READY with a blurred copy for the glow. |
| `menu/picture/m77.dat` image 0x220, the placeholder map picture of the third tutorial (チュートリアル03 / MAP_OBJ有り / :ST77) | Redrawn as TUTORIAL 03 / MAP WITH OBJECTS / :ST77. |
| `menu/yokoku/yokokuNN.dat`, the 128x64 name plate of each battle preview and versus banner (ビット / バラッド and 38 more) | Redrawn with the spellings from `names.json`; the upper name is right-aligned and the lower one left-aligned as in the original. |
| `disp/top_g01.dat` to `top_g04.dat` image 0x200, tutorial control cards | Labels and captions repainted in English (CONTROL STICK / Move Zoid, L TRIGGER / Enemy Search OFF, and so on). |

Left as is: the ゾイドバーサスIII katakana under the logo (part of the logo); kana and kanji cells in the `ascii/*.dat` fonts; the 任務完了, 失敗 and 決定 cells of the shared glyph sheet (no mesh in message, pause, battle entry, farm or VS menu archives samples them, checked with `list_pobjs`); `disp/partnerNN.dat` (never loaded; portraits come from `chara/bp`); archives in `backup/`, `badkup/` and the `*x.dat` copies, which the game never loads.

## Font

Story and info text is drawn with the console's built-in font. The build patches the font loader so the game reads one of three Latin fonts from the disc instead, chosen under TEXT FONT on the CONFIG screen. README.md lists the code changes.
