#!/usr/bin/env bash
# standalone/build.sh: build/AxisRC.exe, the rebuilt game as its own program (see main.c). Links the objects
# build.sh made for recomp.dll (run that first), the hook table generated from recomp.c, and the patch layer
# (axisnet_recomp.c with AXIS_STANDALONE, plus the movie decoder objects of ../axisnet/iv32).
# Linked at 0x10000 with ASLR off, so that main.c's g_space covers the game's 0x400000..; checked below.
set -e
cd "$(dirname "$0")/.."
CC="python -m ziglang cc -target x86-windows-gnu"
test -n "$(ls build/obj/*.o 2>/dev/null)" || { echo "no build/obj: run build.sh first"; exit 1; }
python tools/mkhooks.py build/standalone_hooks.c
# (FENCE=1 / FENCE=2: a fence build, src/data/split.h - each split variable beside a guard page)
# src/ again with AXIS_DIRECT: calls between rebuilt functions direct, not through their original addresses (GAME_FN
# in src/axis.h; build/fn_syms.h gives each one's symbol and address). build/obj stays the harness's.
python tools/hooktable.py build/fn_syms.h
mkdir -p build/obj_direct
# (compiled in parallel, one job a core: zig's cache keeps each file's object by its source and flags)
export CC FENCE
find src -name '*.c' | sort | xargs -P "$(nproc)" -I{} sh -c '
	f={}; o="build/obj_direct/$(echo "${f#src/}" | tr "/" "_" | sed "s/\.c$/.o/")"
	$CC -c -O2 -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -Wall -Wno-unused-function -DAXIS_DIRECT ${FENCE:+-DAXIS_FENCE=$FENCE} -Ibuild -o "$o" "$f" || exit 255'
python tools/mkgamedata.py build/gamedata.bin
# (the blob's hash in the source: zig caches objects by their source text, and .incbin's file is not part of it, so a
# new blob would otherwise link the old one)
printf '\t# gamedata.bin %s\n\t.section .rdata,"dr"\n\t.globl _g_gamedata\n\t.p2align 2\n_g_gamedata:\n\t.incbin "build/gamedata.bin"\n' \
	"$(sha1sum build/gamedata.bin | cut -c1-40)" > build/gamedata.s
$CC -c -o build/gamedata.o build/gamedata.s
$CC -c -O2 -Wall -o build/standalone_main.o standalone/main.c
$CC -c -O2 -Wall -o build/standalone_crt.o standalone/crt.c
$CC -c -O2 -Istandalone -o build/standalone_hooks.o build/standalone_hooks.c
$CC -c -O2 -DAXIS_STANDALONE -fno-omit-frame-pointer -I../axisnet -Ibuild -w -o build/standalone_axisnet.o axisnet_recomp.c
IV=../axisnet/iv32
# (-Wl,--subsystem,windows, not -mwindows: zig ignores -mwindows, and a console exe opens a console window)
$CC -O2 -Wl,--subsystem,windows -Wl,--image-base=0x10000 -Wl,--stack=0x100000 -o build/AxisRC.exe \
	build/standalone_main.o build/standalone_crt.o build/gamedata.o build/standalone_hooks.o build/standalone_axisnet.o build/obj_direct/*.o \
	$IV/iv32.o $IV/indeo3.o $IV/hpeldsp.o -lws2_32 -lole32 -loleaut32 -luser32 -lwinmm -lgdi32
python - build/AxisRC.exe <<'EOF'
import sys, struct, pefile
b = bytearray(open(sys.argv[1], 'rb').read()); pe = struct.unpack_from('<I', b, 0x3c)[0]
o = pe + 0x18 + 0x46; struct.pack_into('<H', b, o, struct.unpack_from('<H', b, o)[0] & ~0x40)   # ASLR off
open(sys.argv[1], 'wb').write(b)
pe = pefile.PE(sys.argv[1])
o = pe.OPTIONAL_HEADER
assert o.ImageBase == 0x10000 and not o.DllCharacteristics & 0x40, 'not at a fixed 0x10000'
assert o.Subsystem == 2, 'not a GUI exe (subsystem %d): it would open a console window' % o.Subsystem
sym = None
for s in pe.sections:
    lo, hi = o.ImageBase + s.VirtualAddress, o.ImageBase + s.VirtualAddress + s.Misc_VirtualSize
    print('  %-8s %08x..%08x' % (s.Name.rstrip(b'\0').decode(), lo, hi))
    if lo <= 0x400000 and hi >= 0xb6b000: sym = s
assert sym, 'no section covers 0x400000..0xb6b000 (the code grew past 0x400000?)'
print('built build/AxisRC.exe')
EOF
