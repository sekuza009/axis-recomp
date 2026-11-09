#!/usr/bin/env bash
# standalone/build64.sh [linux]: the 64-bit build (PORTING.md, stage 6) - src/ with the 64-bit loader (standalone/
# host64.c and its parts), for x86-64 Linux (static, musl; the platform from src/plat/posix). Makes build/obj64_linux,
# build/libaxis64_linux.a (the game as a library) and build/axis64_test (tools/plat_tests/host64_test.c: the game run
# headless, its frames counted). Needs build/fn_syms.h (standalone/build.sh makes it).
set -e
cd "$(dirname "$0")/.."
TARGET=${1:-linux}
case "$TARGET" in
linux) TRIPLE=x86_64-linux-musl; FMT=elf ;;
windows) TRIPLE=x86_64-windows-gnu; FMT=coff ;;
*) echo "unknown target $TARGET"; exit 1 ;;
esac
OBJD=build/obj64_$TARGET
mkdir -p "$OBJD"
CC="python -m ziglang cc -target $TRIPLE"
python tools/mkfn64.py
python tools/mkthunks64.py build/plat_thunks64_$TARGET.s $FMT
DEFS="-DAXIS_DIRECT -DAXIS_NATIVE -DAXIS_PORTABLE -DAXIS_RELOCATABLE -DAXIS_DLL"
CFLAGS="-O2 -g -fno-omit-frame-pointer -fno-builtin -fno-strict-aliasing -Wall -Wno-unused-function -Wno-address-of-packed-member -Wno-unknown-attributes -Wno-ignored-attributes -Wno-unused-command-line-argument -Wno-pointer-sign"
export CC OBJD DEFS CFLAGS
# src/: all but the Windows platform (the 64-bit build's is the host one, src/plat/host; off Windows src/plat/posix) and
# posix/directplay.c (axisnet's DirectPlay is standalone/net64.c's here)
find src -name '*.c' | grep -v '^src/plat/win32/' | grep -v '^src/plat/posix/directplay.c' | sort | xargs -P "$(nproc)" -I{} sh -c '
	f={}; o="$OBJD/$(echo "${f#src/}" | tr "/" "_" | sed "s/\.c$/.o/")"
	$CC -c $CFLAGS $DEFS -Ibuild -o "$o" "$f" 2> "$o.log" || { cat "$o.log"; exit 255; }'
LOADER="arena host64 crt64 glrec64 hostwin64 platform64 glstate net64"; [ "$TARGET" = windows ] && LOADER="$LOADER win64"
for f in $LOADER; do
	$CC -c $CFLAGS -DAXIS_PORTABLE -I../axisnet -o "$OBJD/sa_$f.o" "standalone/$f.c" || exit 1
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
else
	$CC $CFLAGS -static -o build/axis64_test tools/plat_tests/host64_test.c build/libaxis64_$TARGET.a -lm -lpthread
	echo "built build/libaxis64_$TARGET.a, build/axis64_test"
fi
