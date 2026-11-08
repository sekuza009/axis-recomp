#!/usr/bin/env bash
# both traces in one exe (test only): build/AxisRC_trace2.exe = src/ instrumented (tools/ftrace: every rebuilt
# function's calls, contexts, callers -> Axis\ftrace_<pid>.tsv) + the range sampler (tools/rtrace: every field /
# global's values -> Axis\rtrace_<pid>.tsv). One play session then gives both. Run tools/ftrace/build.sh first (it
# makes build/obj_ftrace) and set D to the rtrace working folder (gen.py, rtrace.c, out/ as tools/rtrace/build.sh).
set -e
cd "$(dirname "$0")/../.."
: "${D:?set D to the rtrace working folder}"
O=build/obj_ftrace
CC="python -m ziglang cc -target x86-windows-gnu"
python $D/gen.py $D/out/rt_walk.c | head -1
python - <<PY
t=open('standalone/main.c',encoding='latin-1',newline='').read()
assert '\tcrt_start();' in t
t=t.replace('\tcrt_start();','\t{ void trace_start(void); void ftrace_start(void); trace_start(); ftrace_start(); }\n\tcrt_start();',1)
open('$O/main_both.c','w',encoding='latin-1',newline='').write(t)
PY
$CC -c -O2 -Wall -DAXIS_NATIVE -Istandalone -o $O/main_both.o $O/main_both.c
# ftrace's start renamed (rtrace's trace_start owns g_testMissions and the single-instance bypass)
$CC -c -O2 -Wall -Dtrace_start=ftrace_start -Dg_testMissions=ftrace_unusedMissions -o $O/ftrace_both.o tools/ftrace/ftrace.c
$CC -c -O2 -Wall -o $O/rtrace_both.o $D/rtrace.c
$CC -c -O1 -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -fno-strict-aliasing -w -DAXIS_DIRECT -DAXIS_NATIVE -Ibuild -Isrc -I$D -o $O/rt_walk_both.o $D/out/rt_walk.c
IV=../axisnet/iv32
$CC -O2 -Wl,--subsystem,windows -Wl,--image-base=0x10000 -Wl,--stack=0x100000 -o build/AxisRC_trace2.exe \
	$O/main_both.o $O/ftrace_both.o $O/rtrace_both.o $O/rt_walk_both.o build/standalone_crt.o build/gamedata.o \
	build/standalone_hooks.o build/standalone_axisnet.o build/standalone_platform.o \
	$(ls $O/*.o | grep -v -e main_trace.o -e ftrace_rt.o -e main_both.o -e ftrace_both.o -e rtrace_both.o -e rt_walk_both.o) \
	$IV/iv32.o $IV/indeo3.o $IV/hpeldsp.o -lws2_32 -lole32 -loleaut32 -luser32 -lwinmm -lgdi32 -ldbghelp
python - build/AxisRC_trace2.exe <<'PY'
import sys, struct
b = bytearray(open(sys.argv[1], 'rb').read()); pe = struct.unpack_from('<I', b, 0x3c)[0]
o = pe + 0x18 + 0x46; struct.pack_into('<H', b, o, struct.unpack_from('<H', b, o)[0] & ~0x40)
open(sys.argv[1], 'wb').write(b)
PY
echo built build/AxisRC_trace2.exe
