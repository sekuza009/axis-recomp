#!/usr/bin/env bash
# build.sh: recomp.dll = the harness and lifted code (recomp.c, one translation unit) + the readable rebuilds
# (src/**/*.c, x87 maths: -mno-sse, see src/axis.h). scene.h is regenerated from scene.fields first.
set -e
cd "$(dirname "$0")"
python tools/mkscene.py >/dev/null
CC="python -m ziglang cc -target x86-windows-gnu"
mkdir -p build/obj
objs=()
for f in $(find src -name '*.c' | sort); do
	o="build/obj/$(echo "${f#src/}" | tr '/' '_' | sed 's/\.c$/.o/')"
	$CC -c -O2 -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -Wall -Wno-unused-function -o "$o" "$f"
	objs+=("$o")
done
$CC -shared -O2 -Wno-unused-label -o recomp.dll recomp.c "${objs[@]}"
