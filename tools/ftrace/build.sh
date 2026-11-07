#!/usr/bin/env bash
# function-trace build: build/AxisRC_ftrace.exe = src/ compiled again with -finstrument-functions (build/obj_ftrace)
# + ftrace.c (counts each rebuilt function's calls, contexts and callers; see there). Shipped build untouched.
# Run standalone/build.sh first (the other objects come from it).
set -e
cd "$(dirname "$0")/../.."
F=tools/ftrace; O=build/obj_ftrace
CC="python -m ziglang cc -target x86-windows-gnu"
mkdir -p $O
python - <<PY
t=open('standalone/main.c',encoding='latin-1',newline='').read()
assert '\tcrt_start();' in t
t=t.replace('\tcrt_start();','\t{ void trace_start(void); trace_start(); }\n\tcrt_start();',1)
open('$O/main_trace.c','w',encoding='latin-1',newline='').write(t)
t=open('src/menu/menu_misc.c',encoding='latin-1',newline='').read()
a='*r = menuState500_enterSkirmish();'
assert t.count(a)==1
t=t.replace(a,'{ extern int g_testMissions; *r = g_testMissions ? (u32)menuState900_enterMissions() : menuState500_enterSkirmish(); }',1).replace('#include "../','#include "')
open('$O/menu_misc_test.c','w',encoding='latin-1',newline='').write(t)
PY
export CC O
find src -name '*.c' | sort | xargs -P "$(nproc)" -I{} sh -c '
	f={}; o="$O/$(echo "${f#src/}" | tr "/" "_" | sed "s/\.c$/.o/")"
	$CC -c -O2 -finstrument-functions -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -fno-strict-aliasing -w -DAXIS_DIRECT -DAXIS_NATIVE -Ibuild -o "$o" "$f" || exit 255'
$CC -c -O2 -finstrument-functions -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -fno-strict-aliasing -w -DAXIS_DIRECT -DAXIS_NATIVE -Ibuild -Isrc -Isrc/menu -o $O/menu_menu_misc.o $O/menu_misc_test.c
$CC -c -O2 -Wall -DAXIS_NATIVE -Istandalone -o $O/main_trace.o $O/main_trace.c
$CC -c -O2 -Wall -o $O/ftrace_rt.o $F/ftrace.c
IV=../axisnet/iv32
$CC -O2 -Wl,--subsystem,windows -Wl,--image-base=0x10000 -Wl,--stack=0x100000 -o build/AxisRC_ftrace.exe \
	$O/main_trace.o $O/ftrace_rt.o build/standalone_crt.o build/gamedata.o build/standalone_hooks.o build/standalone_axisnet.o \
	build/standalone_platform.o $(ls $O/*.o | grep -v -e main_trace.o -e ftrace_rt.o) \
	$IV/iv32.o $IV/indeo3.o $IV/hpeldsp.o -lws2_32 -lole32 -loleaut32 -luser32 -lwinmm -lgdi32 -ldbghelp
python - build/AxisRC_ftrace.exe <<'PY'
import sys, struct
b = bytearray(open(sys.argv[1], 'rb').read()); pe = struct.unpack_from('<I', b, 0x3c)[0]
o = pe + 0x18 + 0x46; struct.pack_into('<H', b, o, struct.unpack_from('<H', b, o)[0] & ~0x40)
open(sys.argv[1], 'wb').write(b)
PY
echo built build/AxisRC_ftrace.exe
