#!/usr/bin/env bash
# Build a keymap from this repo and drop the firmware on the Windows desktop.
#
# Usage: ./build.sh [target]
#   halcyon  splitkb/halcyon/kyria/rev4   (default)
#   kimiko   keycapsss/kimiko/rev2
#
# The keymaps here are symlinked into qmk_firmware/keyboards/<board>/keymaps/zaizu2,
# so edits in this repo are picked up with no copying.

set -euo pipefail

QMK_HOME="${QMK_HOME:-$HOME/dev/keyboards/qmk_firmware}"
QMK_BIN="${QMK_BIN:-$HOME/.venv/bin/qmk}"   # the CLI is in a venv, not on PATH
KEYMAP=zaizu2
DEST="${DEST:-/mnt/c/Users/Kuba/Desktop}"

case "${1:-halcyon}" in
    halcyon) KEYBOARD=splitkb/halcyon/kyria/rev4 ;;
    kimiko)  KEYBOARD=keycapsss/kimiko/rev2 ;;
    *)       echo "unknown target: $1 (expected 'halcyon' or 'kimiko')" >&2; exit 1 ;;
esac

[ -x "$QMK_BIN" ] || { echo "qmk CLI not found at $QMK_BIN" >&2; exit 1; }

cd "$QMK_HOME"
"$QMK_BIN" compile -kb "$KEYBOARD" -km "$KEYMAP" -j "$(nproc)"

# QMK names the artifact after the board and keymap; .uf2 for RP2040, .hex for AVR.
name="${KEYBOARD//\//_}_${KEYMAP}"
for ext in uf2 hex bin; do
    if [ -f "$name.$ext" ]; then
        firmware="$name.$ext"
        break
    fi
done
[ -n "${firmware:-}" ] || { echo "no firmware produced for $name" >&2; exit 1; }

if [ -d "$DEST" ]; then
    cp "$firmware" "$DEST/"
    echo "copied $firmware -> $DEST/"
else
    echo "$DEST not found, firmware left at $QMK_HOME/$firmware"
fi
