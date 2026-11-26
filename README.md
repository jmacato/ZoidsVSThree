# Zoids VS. III decompilation

A matching decompilation of Zoids VS. III for the GameCube (Japan, game ID `GZVJDA`). All 3,430 functions of the game (1,230,468 bytes) compile from the C and C++ sources in this repository to the same bytes as the original executable, and the rebuilt `main.dol` is identical to the original.

This repository contains no game data and no compilers.

## Requirements

- macOS or Linux, with Rust 1.88 or later.
- Your own copy of the game as a disc image, `game.iso` in the repository root (SHA-256 `f72f576e3c0e37f9e0cf6d1bf0c61ad50c24a64e1da5f15b3a5bc997f2a59808`).
- Your own copy of the Metrowerks CodeWarrior for GameCube compilers, versions 1.2.5, 1.2.5n and 1.1p1.

Place each compiler, as an executable your system can run, at:

| Version | Path |
|---|---|
| 1.2.5 | `build/tools/mwcceppc-native` |
| 1.2.5n | `build/tools/mwcceppc-1.2.5n-native` |
| 1.1p1 | `build/tools/mwcceppc-1.1p1-native` |

To keep them elsewhere, pass `--compiler PATH` or set `MWCC=PATH` for the 1.2.5 compiler; the other two are looked up in the same directory under the names above.

## Usage

```sh
make verify   # compile every source file and compare each function with the original
make build    # write build/main.dol and check its SHA-1
```

Use a disc image at another path with `make verify ISO=path/to/game.iso`. A complete run ends with `PASS 3430 C/C++ functions, 1230468 bytes; complete DOL reconstruction matches da80f5bf908bccbc025dc35b434af95e97f2dccb.`

## Build the English translation

Put your disc image at `build/Zoids vs. III (Japan).iso`. Run:

```sh
cargo run --release --manifest-path tools/translate-rs/Cargo.toml --bin zvs3-translate
```

This writes `build/Zoids VS III (English, chakra).iso`. Pass `--iso PATH` and `--out PATH` to use other paths. The English text is in `translation/`.

## Layout

- `src/`: game code, Dolphin SDK, MusyX, MetroTRK and runtime sources.
- `include/`: headers.
- `tools/mwperm/`: the build and verify tool.
- `translation/`: English text and textures.
- `tools/translate-rs/`: the translation builder.

## License

GNU AGPL 3.0 only (`AGPL-3.0-only`). See `LICENSE`. If you distribute a modified version, or run one for users over a network, you must release its source under the same license. If you use this project's code or findings in your own work, see `NOTICE` for how to credit it.
