#!/usr/bin/env bash
# The Godot version exported as a game: godot/export.sh [release|debug] [install] [64]
#   build/godot_export/ (32-bit) or build/godot_export64/ (64-bit, "64"): AxisGodot.exe, AxisGodot.pck, the extension
#   DLL and the game library - axis.dll (PORTABLE=3 bash standalone/build.sh) or axis64.dll (standalone/build64.sh
#   windows). install: copied to <Axis>/Godot (32-bit) or <Axis>/Godot64 (64-bit); the game's folder is the one above it.
set -e
cd "$(dirname "$0")/.."
MODE=${1:-release}
if [ "$3" = 64 ]; then
	ARCH=x86_64; LIB=axis64.dll; OUT=build/godot_export64; PRESET="Windows Desktop 64-bit"; DEST=/c/Users/Alexander/Desktop/Axis/Godot64
	GODOT=C:/Users/Alexander/Tools/godot/editor64/Godot_v4.7.2-stable_win64_console.exe
else
	ARCH=x86_32; LIB=axis.dll; OUT=build/godot_export; PRESET="Windows Desktop"; DEST=/c/Users/Alexander/Desktop/Axis/Godot
	GODOT=C:/Users/Alexander/Tools/godot/editor/Godot_v4.7.2-stable_win32_console.exe
fi
test -e build/$LIB || { echo "build/$LIB missing"; exit 1; }
test -e godot/project/bin/axis_godot.windows.template_$MODE.$ARCH.dll || { echo "the $MODE $ARCH extension is not built (godot/README.md)"; exit 1; }
rm -rf "$OUT"; mkdir -p "$OUT"
"$GODOT" --headless --path godot/project --export-$MODE "$PRESET" "$(cygpath -m "$PWD/$OUT")/AxisGodot.exe" 2>&1 | grep -viE '^\s*$|progress|step' | tail -5
cp build/$LIB "$OUT/$LIB"
ls -la "$OUT"
if [ "$2" = install ]; then
	mkdir -p "$DEST"
	cp "$OUT"/* "$DEST"/
	echo "installed to $DEST"
fi
