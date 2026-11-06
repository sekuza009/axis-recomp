#!/usr/bin/env bash
# range-trace build: build/AxisRC_rtrace.exe = the standalone objects + rtrace (shipped build untouched)
set -e
D=C:/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace
cd /c/Users/Alexander/Desktop/Axis/recomp
CC="python -m ziglang cc -target x86-windows-gnu"
python $D/gen.py $D/out/rt_walk.c | head -1
python - <<PY
t=open('standalone/main.c',encoding='latin-1',newline='').read()
assert '\tcrt_start();' in t
t=t.replace('\tcrt_start();','\t{ void trace_start(void); trace_start(); }\n\tcrt_start();',1)
open(r'$D/out/main_trace.c','w',encoding='latin-1',newline='').write(t)
PY
$CC -c -O2 -Wall -Istandalone -o $D/out/main_trace.o $D/out/main_trace.c
$CC -c -O2 -Wall -o $D/out/rtrace.o $D/rtrace.c
$CC -c -O2 -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -fno-strict-aliasing -w -DAXIS_DIRECT -Ibuild -Isrc -Isrc/menu -o $D/out/menu_records_test.o $D/menu_records_test.c
$CC -c -O1 -mno-sse -mno-sse2 -mfpmath=387 -fno-builtin -fno-strict-aliasing -w -DAXIS_DIRECT -Ibuild -Isrc -I$D -o $D/out/rt_walk.o $D/out/rt_walk.c
IV=../axisnet/iv32
$CC -O2 -Wl,--subsystem,windows -Wl,--image-base=0x10000 -Wl,--stack=0x100000 -o build/AxisRC_rtrace.exe $D/out/main_trace.o $D/out/rtrace.o $D/out/rt_walk.o build/standalone_crt.o build/gamedata.o build/standalone_hooks.o build/standalone_axisnet.o $(ls build/obj_direct/*.o | grep -v menu_menu_records.o) $D/out/menu_records_test.o $IV/iv32.o $IV/indeo3.o $IV/hpeldsp.o -lws2_32 -lole32 -loleaut32 -luser32 -lwinmm -lgdi32
python - build/AxisRC_rtrace.exe <<'PY'
import sys, struct
b = bytearray(open(sys.argv[1], 'rb').read()); pe = struct.unpack_from('<I', b, 0x3c)[0]
o = pe + 0x18 + 0x46; struct.pack_into('<H', b, o, struct.unpack_from('<H', b, o)[0] & ~0x40)
open(sys.argv[1], 'wb').write(b)
PY
echo built build/AxisRC_rtrace.exe
