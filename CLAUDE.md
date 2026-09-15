# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repo is

Personal keyboard firmware configs. The only content this repo actually owns is `qmk-config/`;
`qmk_firmware/`, `zmk/` and `zmk-config/` are git submodules (upstream QMK, upstream ZMK, and a
personal ZMK config for a hillside48). Do not commit changes inside the submodules as part of
work on the configs.

## Build

```bash
cd qmk-config
./build.sh            # splitkb/halcyon/kyria/rev4  (default)
./build.sh kimiko     # keycapsss/kimiko/rev2
```

`build.sh` compiles and copies the firmware to the Windows desktop (`/mnt/c/Users/Kuba/Desktop`,
this is WSL). Override `QMK_HOME`, `QMK_BIN` or `DEST` via env if paths move.

The underlying command, if you need it directly:

```bash
cd qmk_firmware
~/.venv/bin/qmk compile -kb splitkb/halcyon/kyria/rev4 -km zaizu2 -j 4
```

Notes that will otherwise cost time:

- **The qmk CLI only exists in venvs**: `~/.venv/bin/qmk` (1.1.7, what `build.sh` uses) and
  `.venv/bin/qmk` (1.1.6). A bare `qmk` is not on `PATH` and `milc` is not installed system-wide.
- Every build ends with `cp: cannot create regular file '/home/jakub/qmk_userspace/...'`.
  Harmless — QMK copies to a userspace dir that does not exist here. The build still succeeded.
- The kimiko is AVR and nearly full (~94% of 28672 bytes). Adding features there can overflow.
- `build.sh` guesses the artifact name from board+keymap, so boards built through a converter
  (`-e CONVERT_TO=...`) will not be found by it.
- Flashing is manual; nothing here flashes a board.

## How the keymaps reach QMK

Each directory under `qmk-config/` is symlinked into the submodule as a keymap named `zaizu2`:

```
qmk_firmware/keyboards/splitkb/halcyon/kyria/keymaps/zaizu2 -> qmk-config/halcyon_kyria
qmk_firmware/keyboards/keycapsss/kimiko/rev2/keymaps/zaizu2 -> qmk-config/zaizu2
```

So `-km zaizu2` always picks up edits in this repo with no copy step, and `zaizu2` is the keymap
name on every board (the confusingly named `qmk-config/zaizu2/` directory is the *kimiko* keymap).
A new board needs its own directory here plus a matching symlink; the symlinks are not tracked by
git, so they must be recreated on a fresh clone.

## Keymap structure

Both keymaps share a layout: layers `_WIN` / `_MAC` (alternate base layers, swapped with `DF()`),
`_LOWER`, `_RAISE`, `_ADJUST`. Layer 0 in the `enum layers` declaration is the boot default —
reordering that enum is how the default base layer is changed. `DF()` is not persistent, so the
board returns to layer 0 after a power cycle.

`ENCODER_MAP_ENABLE` is on, so `encoder_map[]` must have an entry for every layer. Layer-specific
feature keys (RGB controls, `EE_CLR`, `QK_BOOT`, dynamic tapping term) live on `_ADJUST`, which is
reached with `MO(_ADJUST)` from `_LOWER` or `_RAISE`.

The ASCII-art comment above each `LAYOUT(...)` block is the readable form of the keymap — keep it
in sync when moving keys.

## RGB matrix gotchas

The halcyon kyria differs from the kimiko here, and the difference is not obvious:

- splitkb's `keyboards/splitkb/halcyon/kyria/rev4/keyboard.json` enables **all 43 animations**, and
  a keymap `config.h` can only *add* defines on top of the generated `info_config.h`. Trimming the
  effect list therefore requires `#undef ENABLE_RGB_MATRIX_*` for each unwanted effect (this is the
  approach QMK documents in `docs/squeezing_avr.md`). The kimiko enables none by default, so there
  a plain `#define` list is enough.
- QMK builds with `-Werror`, so redefining a value the keyboard already set (e.g.
  `RGB_MATRIX_DEFAULT_MODE`) is a **build error**. `#undef` it first.
- `RGB_MATRIX_SOLID_COLOR` is always compiled in; it is not gated by an `ENABLE_` define.
- **`RGB_MATRIX_DEFAULT_*` only applies when the EEPROM is reset.** On a previously flashed board
  the saved HSV/mode/on-off wins, so a hue change in `config.h` appears to do nothing until
  `EE_CLR` is pressed. When RGB looks "wrong" after a flash, suspect stale EEPROM before suspecting
  the config.
- Hue is 0-255 across the wheel: 0 red, ~21 orange, ~43 yellow. `RGB_MATRIX_HUE_STEP` is 8, so one
  press of the hue key moves 8.
- Brightness is capped by the board's `RGB_MATRIX_MAXIMUM_BRIGHTNESS` (128 on the halcyon, a USB
  current budget decision for 62 LEDs on a split).
- The halcyon's 62 LEDs are 50 per-key (`LED_FLAG_KEYLIGHT`) plus 12 underglow
  (`LED_FLAG_UNDERGLOW`) on the underside. `RGB_MATRIX_DEFAULT_FLAGS LED_FLAG_KEYLIGHT` keeps the
  underglow dark (it is covered on this build). Like the other defaults, flags live in EEPROM.
