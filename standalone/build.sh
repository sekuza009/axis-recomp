#!/usr/bin/env bash
# standalone/build.sh: build/AxisRC.exe, the rebuilt game as its own program (see main.c). Links the objects
# build.sh made for recomp.dll (run that first), the hook table generated from recomp.c, the network layer
# (axisnet_recomp.c with AXIS_STANDALONE) and the Windows platform code (platform.c, plus the movie decoder objects
# of ../axisnet/iv32).
# Linked at 0x10000 with ASLR off, so that main.c's g_space covers the game's 0x400000..; checked below.
set -e
cd "$(dirname "$0")/.."
# AxisRC.exe carries the game fixes in the game's own code (AXIS_NATIVE: src/fixes/, standalone/platform.c); the
# patch layer is only its network layer.
# PORTABLE=1: build/AxisRC_portable.exe - the portable branch's build (src/ with AXIS_PORTABLE: RELOC maps nothing; see
# PORTING.md). Still linked as AxisRC.exe is, so the original's range stays guarded and any original address left is caught.
# PORTABLE=2: build/AxisRC_reloc.exe - the same with the image an ordinary array and the exe linked with ASLR (no
# reserved or guarded range): the game loaded wherever Windows puts it.
# PATCHLAYER=1: build/AxisRC_patchlayer.exe - the earlier AxisRC.exe, where the patch layer (axisnet_recomp.c)
# applies the fixes from outside as the patch DLL does to AxisGL.exe (its objects in build/obj_patchlayer), for
# comparison. recomp.dll (build.sh) is unaffected either way: it is checked against AxisGL.exe and its patch DLL.
if [ -n "$NATIVE" ]; then echo "(NATIVE=1 is the default now: building AxisRC.exe)"; fi
if [ -n "$PATCHLAYER" ]; then OBJD=build/obj_patchlayer; NDEF=; OUT=AxisRC_patchlayer.exe; NSUF=_patchlayer;
elif [ "$PORTABLE" = 2 ]; then OBJD=build/obj_portable; NDEF="-DAXIS_NATIVE -DAXIS_PORTABLE -DAXIS_RELOCATABLE"; OUT=AxisRC_reloc.exe; NSUF=_reloc;
elif [ -n "$PORTABLE" ]; then OBJD=build/obj_portable; NDEF="-DAXIS_NATIVE -DAXIS_PORTABLE"; OUT=AxisRC_portable.exe; NSUF=_portable;
else OBJD=build/obj_direct; NDEF=-DAXIS_NATIVE; OUT=AxisRC.exe; NSUF=; fi
export OBJD NDEF
CC="python -m ziglang cc -target x86-windows-gnu"
test -n "$(ls build/obj/*.o 2>/dev/null)" || { echo "no build/obj: run build.sh first"; exit 1; }
python tools/mkhooks.py build/standalone_hooks.c
# (FENCE=1 / FENCE=2: a fence build, src/data/split.h - each split variable beside a guard page)
# src/ again with AXIS_DIRECT: calls between rebuilt functions direct, not through their original addresses (GAME_FN
# in src/axis.h; build/fn_syms.h gives each one's symbol and address). build/obj stays the harness's.
python tools/hooktable.py build/fn_syms.h
mkdir -p $OBJD
# (compiled in parallel, one job a core: zig's cache keeps each file's object by its source and flags)
# (-Wno-address-of-packed-member: g_rdata / g_data are packed only to pin each member to the game's address; the
# float constants taken by address, &k_1f, all sit 4-byte aligned as in the original)
export CC FENCE
find src -name '*.c' | sort | xargs -P "$(nproc)" -I{} sh -c '
	f={}; o="$OBJD/$(echo "${f#src/}" | tr "/" "_" | sed "s/\.c$/.o/")"
	$CC -c -O2 -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -fno-strict-aliasing -Wall -Wno-unused-function -Wno-address-of-packed-member -DAXIS_DIRECT $NDEF ${FENCE:+-DAXIS_FENCE=$FENCE} -Ibuild -o "$o" "$f" || exit 255'
python tools/mkgamedata.py build/gamedata.bin
# (the blob's hash in the source: zig caches objects by their source text, and .incbin's file is not part of it, so a
# new blob would otherwise link the old one)
printf '\t# gamedata.bin %s\n\t.section .rdata,"dr"\n\t.globl _g_gamedata\n\t.p2align 2\n_g_gamedata:\n\t.incbin "build/gamedata.bin"\n' \
	"$(sha1sum build/gamedata.bin | cut -c1-40)" > build/gamedata.s
$CC -c -o build/gamedata.o build/gamedata.s
# (the portable builds: their own loader, standalone/portable.c - no gamedata.bin, no hook table, no entry jumps)
if [ -n "$PORTABLE" ]; then
	python tools/mkimportlist.py > /dev/null
	$CC -c -O2 -Wall $NDEF -o build/standalone_main$NSUF.o standalone/portable.c
	LOADER="build/standalone_main$NSUF.o build/standalone_crt$NSUF.o"
else
	$CC -c -O2 -Wall $NDEF -o build/standalone_main$NSUF.o standalone/main.c
	LOADER="build/standalone_main$NSUF.o build/standalone_crt$NSUF.o build/gamedata.o build/standalone_hooks.o"
fi
PLAT=; if [ -z "$PATCHLAYER" ]; then $CC -c -O2 -Wall -o build/standalone_platform.o standalone/platform.c; PLAT=build/standalone_platform.o; fi
$CC -c -O2 -Wall $NDEF -o build/standalone_crt$NSUF.o standalone/crt.c
$CC -c -O2 -Istandalone -o build/standalone_hooks.o build/standalone_hooks.c
$CC -c -O2 -DAXIS_STANDALONE $NDEF -fno-omit-frame-pointer -I../axisnet -Ibuild -w -o build/standalone_axisnet$NSUF.o axisnet_recomp.c
IV=../axisnet/iv32
# (-Wl,--subsystem,windows, not -mwindows: zig ignores -mwindows, and a console exe opens a console window)
LINKBASE="-Wl,--image-base=0x10000"; test "$PORTABLE" = 2 && LINKBASE="-Wl,--dynamicbase"   # (PORTABLE=2: loaded anywhere)
$CC -O2 -Wl,--subsystem,windows $LINKBASE -Wl,--stack=0x100000 -o build/$OUT \
	$LOADER build/standalone_axisnet$NSUF.o $OBJD/*.o $PLAT $NEXTRA \
	$IV/iv32.o $IV/indeo3.o $IV/hpeldsp.o -lws2_32 -lole32 -loleaut32 -luser32 -lwinmm -lgdi32
python - build/$OUT "$PORTABLE" <<'EOF'
import sys, struct, pefile
reloc = sys.argv[2:] == ['2']   # (PORTABLE=2: loaded anywhere)
b = bytearray(open(sys.argv[1], 'rb').read()); pe = struct.unpack_from('<I', b, 0x3c)[0]
o = pe + 0x18 + 0x46; flags = struct.unpack_from('<H', b, o)[0]
struct.pack_into('<H', b, o, flags | 0x40 if reloc else flags & ~0x40)   # ASLR on for PORTABLE=2, else off
open(sys.argv[1], 'wb').write(b)
pe = pefile.PE(sys.argv[1])
o = pe.OPTIONAL_HEADER
if reloc:
    assert o.DllCharacteristics & 0x40 and o.DATA_DIRECTORY[5].Size, 'not relocatable (no ASLR flag or no relocations)'
    assert o.Subsystem == 2, 'not a GUI exe'
    print('built %s: relocatable, %d bytes of relocations, ASLR on' % (sys.argv[1], o.DATA_DIRECTORY[5].Size))
    sys.exit(0)
assert o.ImageBase == 0x10000 and not o.DllCharacteristics & 0x40, 'not at a fixed 0x10000'
assert o.Subsystem == 2, 'not a GUI exe (subsystem %d): it would open a console window' % o.Subsystem
sym = None
for s in pe.sections:
    lo, hi = o.ImageBase + s.VirtualAddress, o.ImageBase + s.VirtualAddress + s.Misc_VirtualSize
    print('  %-8s %08x..%08x' % (s.Name.rstrip(b'\0').decode(), lo, hi))
    if lo <= 0x400000 and hi >= 0xb6b000: sym = s
assert sym, 'no section covers 0x400000..0xb6b000 (the code grew past 0x400000?)'
print('built ' + sys.argv[1])
EOF
