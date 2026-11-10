#!/usr/bin/env bash
# The Godot version exported as a game: godot/export.sh [release|debug] [install] [windows|linux|macos]
#   build/godot_export64/ (Windows, the default; "64" too): AxisGodot.exe, AxisGodot.pck, the extension DLL and the
#   game library axis64.dll (standalone/build64.sh windows) or, linux, build/godot_export_linux/ (AxisGodot.x86_64, libaxis64.so - standalone/build64.sh linux-gnu - and
#   the extension's .so: godot/extension/build_linux.sh). install: copied to <Axis>/Godot64 or GodotLinux; the
#   game's folder is the one above it.
set -e
cd "$(dirname "$0")/.."
MODE=${1:-release}
if [ "$3" = macos ]; then
	ARCH=universal; LIB=libaxis64.dylib; OUT=build/godot_export_macos; PRESET="macOS"; DEST=/c/Users/Alexander/Desktop/Axis/GodotMac
	GODOT=C:/Users/Alexander/Tools/godot/editor64/Godot_v4.7.2-stable_win64_console.exe
	EXT=libaxis_godot.macos.template_$MODE.dylib; BIN=AxisGodot.zip   # (the .app in a zip; the library inside it)
elif [ "$3" = linux ]; then
	ARCH=x86_64; LIB=libaxis64.so; OUT=build/godot_export_linux; PRESET="Linux 64-bit"; DEST=/c/Users/Alexander/Desktop/Axis/GodotLinux
	GODOT=C:/Users/Alexander/Tools/godot/editor64/Godot_v4.7.2-stable_win64_console.exe
	EXT=libaxis_godot.linux.template_$MODE.$ARCH.so; BIN=AxisGodot.x86_64
else   # (Windows, 64-bit: the 32-bit Godot build was dropped on 2026-11-09 - AxisSDL is the original on every system)
	ARCH=x86_64; LIB=axis64.dll; OUT=build/godot_export64; PRESET="Windows Desktop"; DEST=/c/Users/Alexander/Desktop/Axis/Godot64
	GODOT=C:/Users/Alexander/Tools/godot/editor64/Godot_v4.7.2-stable_win64_console.exe
fi
test -e build/$LIB || { echo "build/$LIB missing"; exit 1; }
EXT=${EXT:-axis_godot.windows.template_$MODE.$ARCH.dll}; BIN=${BIN:-AxisGodot.exe}
test -e godot/project/bin/$EXT || { echo "the $MODE $ARCH extension ($EXT) is not built (godot/README.md)"; exit 1; }
rm -rf "$OUT"; mkdir -p "$OUT"
"$GODOT" --headless --path godot/project --export-$MODE "$PRESET" "$(cygpath -m "$PWD/$OUT")/$BIN" 2>&1 | grep -viE '^\s*$|progress|step' | tail -5
[ "$3" = macos ] || cp build/$LIB "$OUT/$LIB"   # (macOS: in the app already - axis.gdextension's dependencies)
ls -la "$OUT"
if [ "$2" = install ]; then
	mkdir -p "$DEST"
	cp "$OUT"/* "$DEST"/
	echo "installed to $DEST"
fi
