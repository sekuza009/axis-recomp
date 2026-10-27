#!/usr/bin/env bash
# local_build.sh <test.c> <out.exe> [-I dirs...]: build a tools/local_main.c harness exe. It is linked at 0x10000 with
# the ASLR flag cleared, so its .bss array g_space covers 0x400000 (see local_main.c).
set -e
T="$1"; O="$2"; shift 2
python -m ziglang cc -target x86-windows-gnu -O2 -Wl,--image-base=0x10000 -I"$(dirname "$0")" "$@" -o "$O" "$T"
python -c "
import struct, sys
p = sys.argv[1]; b = bytearray(open(p, 'rb').read()); pe = struct.unpack_from('<I', b, 0x3c)[0]
o = pe + 0x18 + 0x46; struct.pack_into('<H', b, o, struct.unpack_from('<H', b, o)[0] & ~0x40); open(p, 'wb').write(b)
" "$O"
