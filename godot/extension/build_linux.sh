#!/usr/bin/env bash
# godot/extension/build_linux.sh [debug|release]: the extension for x86-64 Linux (glibc 2.28), cross-built on Windows
# with zig (godot-cpp's SCons Linux mode expects a Linux toolchain): godot-cpp from GODOT_CPP (default
# Tools/godot/godot-cpp64 - its generated 64-bit bindings serve every x86-64 platform), with the flags its SCons uses,
# then the extension's sources and the movie decoder -> project/bin/libaxis_godot.linux.template_<mode>.x86_64.so.
# godot-cpp's archive is kept in obj_linux_<mode>/ and made once; delete it to rebuild.
set -e
cd "$(dirname "$0")"
MODE=${1:-debug}
GC=${GODOT_CPP:-C:/Users/Alexander/Tools/godot/godot-cpp64}
ZIG=${ZIG:-C:/Users/Alexander/AppData/Roaming/Python/Python315/site-packages/ziglang/zig.exe}
OUT=obj_linux_$MODE
mkdir -p $OUT/gc $OUT/ext
T=x86_64-linux-gnu.2.28
DEFS="-DLINUX_ENABLED -DUNIX_ENABLED -DTHREADS_ENABLED -DHOT_RELOAD_ENABLED -DNDEBUG -DGDEXTENSION"
[ "$MODE" = debug ] && DEFS="$DEFS -DDEBUG_ENABLED"
FLAGS="-fPIC -fvisibility=hidden -O2 -Wwrite-strings"
INC="-I$GC/gdextension -I$GC/include -I$GC/gen/include"
export ZIG T DEFS FLAGS INC GC OUT
LIB=$OUT/libgodot-cpp.a
if [ ! -e $LIB ]; then
	echo "godot-cpp ($MODE): $(find $GC/src $GC/gen/src -name '*.cpp' | wc -l) files"
	find $GC/src $GC/gen/src -name '*.cpp' | xargs -P "$(nproc)" -I{} sh -c '
		f={}; o="$OUT/gc/$(echo "${f#$GC/}" | tr "/" "_" | sed "s/\.cpp$/.o/")"
		[ -e "$o" ] || "$ZIG" c++ -target $T -c -std=c++17 -fno-exceptions $FLAGS $DEFS -I$GC/src $INC -o "$o" "$f" || exit 255'
	ls $OUT/gc/*.o > $OUT/gc.rsp   # (a response file: the list is longer than a Windows command line)
	"$ZIG" ar rcs $LIB @$OUT/gc.rsp
fi
for f in src/*.cpp; do
	"$ZIG" c++ -target $T -c -std=c++17 -fno-exceptions $FLAGS $DEFS $INC -Isrc -o "$OUT/ext/$(basename "${f%.cpp}").o" "$f"
done
for f in src/*.c; do
	"$ZIG" cc -target $T -c $FLAGS -O2 -o "$OUT/ext/$(basename "${f%.c}").o" "$f"
done
# the movie decoder (../../standalone/avimovie.c, FFmpeg's indeo3 - LGPL 2.1+) and the settings' store (the library's
# registry.txt, src/plat/posix/registry.c)
FF=../../../axisnet/iv32/ffmpeg
for p in ../../standalone/avimovie.c $FF/libavcodec/indeo3.c $FF/libavcodec/hpeldsp.c ../../src/plat/posix/registry.c; do
	"$ZIG" cc -target $T -c $FLAGS -w -DHAVE_AV_CONFIG_H -DAXIS_PORTABLE -I$FF -o "$OUT/ext/x_$(basename "${p%.c}").o" "$p"
done
SO=../project/bin/libaxis_godot.linux.template_$MODE.x86_64.so
"$ZIG" c++ -target $T -shared -fPIC -o $SO $OUT/ext/*.o $LIB -ldl -lpthread
ls -la $SO
