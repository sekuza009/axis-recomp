#!/usr/bin/env bash
# The Godot version exported as a game: godot/export.sh [release|debug] [install]
#   build/godot_export/: AxisGodot.exe, AxisGodot.pck, the extension DLL and axis.dll (built first: PORTABLE=3).
#   install: copied to <Axis>/Godot (the game's folder is the one above it; AxisGodot.exe finds it on its own).
set -e
cd "$(dirname "$0")/.."
MODE=${1:-release}
GODOT=C:/Users/Alexander/Tools/godot/editor/Godot_v4.7.2-stable_win32_console.exe
OUT=build/godot_export
test -e build/axis.dll || { echo "build/axis.dll missing: PORTABLE=3 bash standalone/build.sh"; exit 1; }
test -e godot/project/bin/axis_godot.windows.template_$MODE.x86_32.dll || { echo "the $MODE extension is not built (godot/README.md)"; exit 1; }
rm -rf "$OUT"; mkdir -p "$OUT"
"$GODOT" --headless --path godot/project --export-$MODE "Windows Desktop" "$(cygpath -m "$PWD/$OUT")/AxisGodot.exe" 2>&1 | grep -viE '^\s*$|progress|step' | tail -5
cp build/axis.dll "$OUT/axis.dll"
ls -la "$OUT"
if [ "$2" = install ]; then
	DEST=/c/Users/Alexander/Desktop/Axis/Godot
	mkdir -p "$DEST"
	cp "$OUT"/* "$DEST"/
	echo "installed to $DEST"
fi
