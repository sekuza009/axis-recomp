#!/usr/bin/env bash
# standalone/build64.sh [linux|linux-gnu|windows|macos-x86_64|macos-arm64|macos]: the 64-bit build (PORTING.md, stage 6) - src/ with the 64-bit loader
# (standalone/host64.c and its parts):
#   linux     - x86-64 Linux with musl (the platform from src/plat/posix): build/libaxis64_linux.a, build/axis64_test
#               (tools/plat_tests/host64_test.c linked with it: the game run headless, its frames counted),
#               build/libaxis64_musl.so and build/axis64_test_so (the same test loading it with dlopen) - for WSL's
#               musl-only Docker Desktop distribution;
#   linux-gnu - x86-64 Linux with glibc: build/libaxis64.so, the library a Linux host (Godot) loads;
#   windows   - x86-64 Windows: build/axis64.dll, build/axis64_test.exe;
#   macos-x86_64 / macos-arm64 - macOS 11+ on Intel / Apple Silicon: build/libaxis64_<arch>.dylib and
#               build/axis64_test_macos_<arch> (host64_test loading it with dlopen); macos - both, then
#               build/libaxis64.dylib, the universal library (tools/lipo.py).
# The Linux and macOS libraries export only the host API (standalone/axis64.map; hidden symbols). Needs build/fn_syms.h
# (python tools/hooktable.py build/fn_syms.h - standalone/build.sh runs it).
set -e
cd "$(dirname "$0")/.."
TARGET=${1:-linux}
if [ "$TARGET" = macos ]; then
	bash standalone/build64.sh macos-x86_64 && bash standalone/build64.sh macos-arm64
	python tools/lipo.py build/libaxis64.dylib build/libaxis64_x86_64.dylib build/libaxis64_arm64.dylib
	exit
fi
ARCH=x86_64
case "$TARGET" in
linux) TRIPLE=x86_64-linux-musl; FMT=elf ;;
linux-gnu) TRIPLE=x86_64-linux-gnu.2.28; FMT=elf ;;
windows) TRIPLE=x86_64-windows-gnu; FMT=coff ;;
macos-x86_64) TRIPLE=x86_64-macos.11.0; FMT=macho ;;
macos-arm64) TRIPLE=aarch64-macos.11.0; FMT=macho; ARCH=arm64 ;;
*) echo "unknown target $TARGET"; exit 1 ;;
esac
OBJD=build/obj64_$TARGET
mkdir -p "$OBJD"
CC="python -m ziglang cc -target $TRIPLE"
python tools/mkfn64.py
python tools/mkthunks64.py build/plat_thunks64_$TARGET.s $FMT $ARCH
DEFS="-DAXIS_DIRECT -DAXIS_NATIVE -DAXIS_PORTABLE -DAXIS_RELOCATABLE -DAXIS_DLL"
PIC=; [ "$FMT" != coff ] && PIC="-fPIC -fvisibility=hidden"   # (a shared library exporting only axis_*)
NPROC=$(nproc 2>/dev/null || sysctl -n hw.ncpu)
CFLAGS="$PIC -O2 -g -fno-omit-frame-pointer -fno-builtin -fno-strict-aliasing -Wall -Wno-unused-function -Wno-address-of-packed-member -Wno-unknown-attributes -Wno-ignored-attributes -Wno-unused-command-line-argument -Wno-pointer-sign"
export CC OBJD DEFS CFLAGS
# src/: all but the Windows platform (the 64-bit build's is the host one, src/plat/host; off Windows src/plat/posix) and
# posix/directplay.c (axisnet's DirectPlay is standalone/net64.c's here)
find src -name '*.c' | grep -v '^src/plat/win32/' | grep -v '^src/plat/posix/directplay.c' | sort | xargs -P "$NPROC" -I{} sh -c '
	f={}; o="$OBJD/$(echo "${f#src/}" | tr "/" "_" | sed "s/\.c$/.o/")"
	$CC -c $CFLAGS $DEFS -Ibuild -o "$o" "$f" 2> "$o.log" || { cat "$o.log"; exit 255; }'
LOADER="arena host64 crt64 glrec64 hostwin64 platform64 glstate net64 movie64"; [ "$TARGET" = windows ] && LOADER="$LOADER win64"
for f in $LOADER; do
	$CC -c $CFLAGS -DAXIS_PORTABLE -DAXIS_DLL -I../axisnet -Ithird_party/ffmpeg -o "$OBJD/sa_$f.o" "standalone/$f.c" || exit 1
done
# the ending movie's reader and decoder: avimovie.c and FFmpeg's indeo3 (third_party/ffmpeg, unmodified, LGPL 2.1+)
$CC -c $CFLAGS -DHAVE_AV_CONFIG_H -Ithird_party/ffmpeg -o "$OBJD/sa_avimovie.o" standalone/avimovie.c || exit 1
for f in indeo3 hpeldsp; do
	$CC -c $PIC -O2 -w -DHAVE_AV_CONFIG_H -Ithird_party/ffmpeg -o "$OBJD/ff_$f.o" "third_party/ffmpeg/libavcodec/$f.c" || exit 1
done
$CC -c $CFLAGS -Ibuild -o "$OBJD/sa_fn_table64.o" build/fn_table64.c
$CC -c -o "$OBJD/sa_thunks.o" build/plat_thunks64_$TARGET.s
rm -f build/libaxis64_$TARGET.a
python -m ziglang ar rcs build/libaxis64_$TARGET.a $OBJD/*.o
if [ "$TARGET" = windows ]; then
	# (the library for a host - Godot - and the headless test, linked with it statically)
	$CC -shared -o build/axis64.dll -Wl,--out-implib,build/libaxis64.dll.a -Wl,--whole-archive build/libaxis64_$TARGET.a -Wl,--no-whole-archive -lws2_32 -lwinmm -lole32 -loleaut32
	$CC $CFLAGS -o build/axis64_test.exe tools/plat_tests/host64_test.c build/libaxis64_$TARGET.a -lws2_32 -lwinmm -lole32 -loleaut32
	echo "built build/axis64.dll, build/axis64_test.exe"
elif [ "$FMT" = macho ]; then
	$CC -shared -o build/libaxis64_$ARCH.dylib -Wl,-install_name,@rpath/libaxis64.dylib -Wl,-force_load,build/libaxis64_$TARGET.a
	$CC -O2 -Wno-ignored-attributes -DAXIS_TEST_DLOPEN -o build/axis64_test_macos_$ARCH tools/plat_tests/host64_test.c
	echo "built build/libaxis64_$ARCH.dylib, build/axis64_test_macos_$ARCH"
elif [ "$TARGET" = linux-gnu ]; then
	$CC -shared -o build/libaxis64.so -Wl,--version-script=standalone/axis64.map -Wl,--whole-archive build/libaxis64_$TARGET.a -Wl,--no-whole-archive -lm -lpthread -ldl
	echo "built build/libaxis64.so"
else
	$CC $CFLAGS -static -o build/axis64_test tools/plat_tests/host64_test.c build/libaxis64_$TARGET.a -lm -lpthread
	$CC -shared -o build/libaxis64_musl.so -Wl,--version-script=standalone/axis64.map -Wl,--whole-archive build/libaxis64_$TARGET.a -Wl,--no-whole-archive -lm -lpthread
	$CC -dynamic -O2 -Wno-ignored-attributes -DAXIS_TEST_DLOPEN -o build/axis64_test_so tools/plat_tests/host64_test.c -ldl
	echo "built build/libaxis64_$TARGET.a, build/axis64_test, build/libaxis64_musl.so, build/axis64_test_so"
fi
