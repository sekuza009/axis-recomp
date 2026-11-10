#!/usr/bin/env bash
# host/sdl/build.sh [windows] [install]: AxisSDL - the game as a program of its own (host/sdl/main.cpp) - linked with the 64-bit
# game library (standalone/build64.sh <target> first) and SDL3, built with zig:
#   windows - build/sdl/windows/AxisSDL.exe and SDL3.dll (SDL3's MinGW development files in SDL3_MINGW, default
#             Tools/sdl3/SDL3-3.4.20/x86_64-w64-mingw32)
set -e
cd "$(dirname "$0")/../.."
TARGET=${1:-windows}
case "$TARGET" in
windows)
	T=x86_64-windows-gnu
	SDL=${SDL3_MINGW:-C:/Users/Alexander/Tools/sdl3/SDL3-3.4.20/x86_64-w64-mingw32}
	LIB=build/libaxis64_windows.a
	OUT=build/sdl/windows; EXE=AxisSDL.exe; SDLLIB=$SDL/lib/libSDL3.dll.a
	SYSLIBS="-lws2_32 -lwinmm -lole32 -loleaut32 -Wl,--subsystem,windows"
	;;
*) echo "unknown target $TARGET"; exit 1 ;;
esac
test -e $LIB || { echo "$LIB missing: bash standalone/build64.sh $TARGET"; exit 1; }
mkdir -p $OUT/obj
CC="python -m ziglang cc -target $T"
CXX="python -m ziglang c++ -target $T"
FLAGS="-O2 -g -Wall -Wno-unused-function -Wno-ignored-attributes -I$SDL/include"
$CC -c $FLAGS -o $OUT/obj/gl_play.o host/sdl/gl_play.c
$CXX -c -std=c++17 $FLAGS -o $OUT/obj/axis_audio.o host/sdl/axis_audio.cpp
$CXX -c -std=c++17 $FLAGS -Wno-unused-variable -o $OUT/obj/main.o host/sdl/main.cpp
$CXX -o $OUT/$EXE $OUT/obj/main.o $OUT/obj/gl_play.o $OUT/obj/axis_audio.o $LIB $SDLLIB $SYSLIBS
[ "$TARGET" = windows ] && cp $SDL/bin/SDL3.dll $OUT/
ls -la $OUT
# (the replay check: host/sdl/glplay_check.cpp - gl_play against the original's own images)
$CXX -std=c++17 $FLAGS -o $OUT/glplay_check${EXE##AxisSDL} host/sdl/glplay_check.cpp $OUT/obj/gl_play.o $SDLLIB $( [ "$TARGET" = windows ] && echo -Wl,--subsystem,console )
# (install: build/sdl/<target> copied to <Axis>/AxisSDL - the game folder is the one above it)
if [ "$2" = install ] && [ "$TARGET" = windows ]; then
	mkdir -p /c/Users/Alexander/Desktop/Axis/AxisSDL
	cp $OUT/AxisSDL.exe $OUT/SDL3.dll /c/Users/Alexander/Desktop/Axis/AxisSDL/
	echo "installed to /c/Users/Alexander/Desktop/Axis/AxisSDL"
fi
