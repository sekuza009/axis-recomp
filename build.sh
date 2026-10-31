#!/usr/bin/env bash
# build.sh: recomp.dll = the harness and lifted code (recomp.c, one translation unit) + the readable rebuilds
# (src/**/*.c, x87 maths: -mno-sse, see src/axis.h). scene.h is regenerated from scene.fields first.
set -e
cd "$(dirname "$0")"
python tools/mkscene.py >/dev/null
CC="python -m ziglang cc -target x86-windows-gnu"
mkdir -p build/obj
objs=()
# (not src/data: the game's data as C is AxisRC.exe's; the harness runs inside the game's own image)
for f in $(find src -name '*.c' -not -path 'src/data/*' | sort); do
	o="build/obj/$(echo "${f#src/}" | tr '/' '_' | sed 's/\.c$/.o/')"
	$CC -c -O2 -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -Wall -Wno-unused-function -o "$o" "$f"
	objs+=("$o")
done
$CC -shared -O2 -Wno-unused-label -o recomp.dll recomp.c "${objs[@]}"
