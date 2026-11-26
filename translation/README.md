# Zoids VS. III English translation

The translation lives in `translation/` and is applied by the Rust tool in `tools/translate-rs`. It needs the Japanese disc image `build/Zoids vs. III (Japan).iso` (extract it from `Zoids vs. III (Japan).7z`) and the native compilers in `build/tools` that the decompilation already uses.

## Build

```sh
export CARGO_TARGET_DIR=build/translate-rs-target
cargo build --release --manifest-path tools/translate-rs/Cargo.toml
build/translate-rs-target/release/zvs3-translate
```

The result is `build/Zoids VS III (English, chakra).iso`. The disc carries all three story fonts (Chakra Petch, Xolonium, Saira Semi Condensed); players pick one under TEXT FONT on the CONFIG screen. `--font xolonium` or `--font saira` makes another font the default, `--out` picks another output path, and `--no-fixed-height` keeps the line breaks of the JSON files instead of wrapping dialogue to one text height. Story text is wrapped once per font; Xolonium is wider, so its dialogue boxes use four lines at a slightly smaller size.

## Files

- `translation/*.json`: every text with its Japanese (`ja`) and English (`en`). An empty `en` keeps the Japanese. `INVENTORY.md` lists the sources and limits, `GLOSSARY.md` the names and terms.
- `translation/textures/<archive>/<image offset>.png`: redrawn textures that the build applies.

## Code changes

The build compiles edited copies of decompiled functions and writes them into the DOL:

- `src/sdk/os/font.c`: `OSGetFontEncode` always reports the Shift-JIS font, and `OSLoadFont` reads the font file chosen in the save data (`menu/demo/demo2.dat`, `disp/partner01.dat` or `disp/partner02.dat`, all unused by the original game) instead of the console ROM.
- `src/ui/ttl_main.cpp`: `configGet` reloads the font when the saved choice changes, `menufncZoid_ConfigMenu` adds a TEXT FONT entry below VS MODE (cursor value 8) and changes the font with left and right while it is open, `menu_sDispConfig` draws that entry as a ninth row made from the VS MODE row's joint, with its label, help line and the font names in unused menu messages 17 to 19 and 21 to 23, and the two story readers (`menu_MissionDemoScrPlay1`, `menu_MissionDemoScr_MenuAfter_SetMsg1`) read the story file of the chosen font (`etc/demo/text.BIN`, `etc/CI.tcs` or `etc/CI.tpl`).
- The ttl_main functions grow, so they move to a code cave: a new DOL text section at 0x8039D6C0 (16 KiB, stored at disc offset 0x1F9000), with `OSInit` from `src/sdk/os/kernel.c` starting the heap after it.
- The `TXT_Menu` offset table in the DOL is rewritten for the English `etc/TXT_Menu.BIN`.

The font choice is the first reserved byte after the config values in the system save data (`GameSaveRecord.field_1CA9`).
