#!/usr/bin/env bash
# godot/extension/build_posix.sh [debug|release] [linux|macos-x86_64|macos-arm64|macos]: the extension for Linux x86-64
# (glibc 2.28) or macOS 11+ (Intel, Apple Silicon, or "macos": both joined into one universal library - tools/lipo.py),
# cross-built with zig (godot-cpp's SCons modes for those systems expect their own toolchains): godot-cpp from GODOT_CPP
# (default Tools/godot/godot-cpp64 - its generated 64-bit bindings serve every 64-bit platform), with the flags its SCons
# uses, then the extension's sources, the movie decoder and the settings store ->
#   project/bin/libaxis_godot.linux.template_<mode>.x86_64.so, or ...macos.template_<mode>.<arch>.dylib / ....dylib
# godot-cpp's archive is kept in obj_<target>_<mode>/ and made once; delete it to rebuild. ZIG: zig's executable.
set -e
cd "$(dirname "$0")"
MODE=${1:-debug}
TARGET=${2:-linux}
if [ "$TARGET" = macos ]; then
	bash build_posix.sh $MODE macos-x86_64 && bash build_posix.sh $MODE macos-arm64
	B=../project/bin/libaxis_godot.macos.template_$MODE
	python ../../tools/lipo.py $B.dylib $B.x86_64.dylib $B.arm64.dylib
	exit
fi
GC=${GODOT_CPP:-C:/Users/Alexander/Tools/godot/godot-cpp64}
ZIG=${ZIG:-C:/Users/Alexander/AppData/Roaming/Python/Python315/site-packages/ziglang/zig.exe}
case "$TARGET" in
linux) T=x86_64-linux-gnu.2.28; OSDEF="-DLINUX_ENABLED"; SO=../project/bin/libaxis_godot.linux.template_$MODE.x86_64.so; LIBS="-ldl -lpthread" ;;
macos-x86_64) T=x86_64-macos.11.0; OSDEF="-DMACOS_ENABLED"; SO=../project/bin/libaxis_godot.macos.template_$MODE.x86_64.dylib; LIBS= ;;
macos-arm64) T=aarch64-macos.11.0; OSDEF="-DMACOS_ENABLED"; SO=../project/bin/libaxis_godot.macos.template_$MODE.arm64.dylib; LIBS= ;;
*) echo "unknown target $TARGET"; exit 1 ;;
esac
OUT=obj_${TARGET}_$MODE
mkdir -p $OUT/gc $OUT/ext
DEFS="$OSDEF -DUNIX_ENABLED -DTHREADS_ENABLED -DHOT_RELOAD_ENABLED -DNDEBUG -DGDEXTENSION"
[ "$MODE" = debug ] && DEFS="$DEFS -DDEBUG_ENABLED"
FLAGS="-fPIC -fvisibility=hidden -O2 -Wwrite-strings"
INC="-I$GC/gdextension -I$GC/include -I$GC/gen/include"
NPROC=$(nproc 2>/dev/null || sysctl -n hw.ncpu)
export ZIG T DEFS FLAGS INC GC OUT
LIB=$OUT/libgodot-cpp.a
if [ ! -e $LIB ]; then
	echo "godot-cpp ($TARGET, $MODE): $(find $GC/src $GC/gen/src -name '*.cpp' | wc -l) files"
	find $GC/src $GC/gen/src -name '*.cpp' | xargs -P "$NPROC" -I{} sh -c '
		f={}; o="$OUT/gc/$(echo "${f#$GC/}" | tr "/" "_" | sed "s/\.cpp$/.o/")"
		[ -e "$o" ] || "$ZIG" c++ -target $T -c -std=c++17 -fno-exceptions $FLAGS $DEFS -I$GC/src $INC -o "$o" "$f" 2>/dev/null || "$ZIG" c++ -target $T -c -std=c++17 -fno-exceptions $FLAGS $DEFS -I$GC/src $INC -o "$o" "$f" || exit 255'
	ls $OUT/gc/*.o > $OUT/gc.rsp   # (a response file: the list is longer than a Windows command line)
	"$ZIG" ar rcs $LIB @$OUT/gc.rsp
fi
for f in src/*.cpp; do
	"$ZIG" c++ -target $T -c -std=c++17 -fno-exceptions $FLAGS $DEFS $INC -Isrc -o "$OUT/ext/$(basename "${f%.cpp}").o" "$f" 2>/dev/null || "$ZIG" c++ -target $T -c -std=c++17 -fno-exceptions $FLAGS $DEFS $INC -Isrc -o "$OUT/ext/$(basename "${f%.cpp}").o" "$f"
done
for f in src/*.c; do
	"$ZIG" cc -target $T -c $FLAGS -o "$OUT/ext/$(basename "${f%.c}").o" "$f"
done
# the movie decoder (../../standalone/avimovie.c, FFmpeg's indeo3 - ../../third_party/ffmpeg, LGPL 2.1+) and the
# settings' store (the library's registry.txt, src/plat/posix/registry.c)
FF=../../third_party/ffmpeg
for p in ../../standalone/avimovie.c $FF/libavcodec/indeo3.c $FF/libavcodec/hpeldsp.c ../../src/plat/posix/registry.c; do
	"$ZIG" cc -target $T -c $FLAGS -w -DHAVE_AV_CONFIG_H -DAXIS_PORTABLE -I$FF -o "$OUT/ext/x_$(basename "${p%.c}").o" "$p"
done
"$ZIG" c++ -target $T -shared -fPIC -o $SO $OUT/ext/*.o $LIB $LIBS
ls -la $SO
