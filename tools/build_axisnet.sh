#!/usr/bin/env bash
# build_axisnet.sh: axisnet_recomp.dll (the patch DLL's test build, axisnet_recomp.c) as ../axisnet/build.bat builds
# axisnet.dll, then build/AxisGL.exe with it embedded (build_testexe.py). Run after changing axisnet_recomp.c.
set -e
cd "$(dirname "$0")/.."
IV=../axisnet/iv32
python -m ziglang cc -target x86-windows-gnu -shared -O2 -I../axisnet -o axisnet_recomp.dll axisnet_recomp.c \
	$IV/iv32.o $IV/indeo3.o $IV/hpeldsp.o -lws2_32 -lole32 -loleaut32 -luser32 -lwinmm -lgdi32 -fno-omit-frame-pointer
python build_testexe.py
