#!/usr/bin/env bash
# standalone/build_nosplit.sh: build/AxisRC_nosplit.exe - AxisRC.exe with nothing split out of g_data (the reference
# for what the splits change); tools/names/split.txt is put back and checked, and the normal build rebuilt after.
R="C:/Users/Alexander/Desktop/Axis/recomp"
cd "$R"
keep="$R/build/split.txt.keep"
cp tools/names/split.txt "$keep" || exit 1
restore() { cp "$keep" tools/names/split.txt; python tools/mkdatasrc.py > /dev/null; }
trap restore EXIT
: > tools/names/split.txt
python tools/mkdatasrc.py > /dev/null
bash standalone/build.sh 2>&1 | grep -E " error|undefined"
cp build/AxisRC.exe build/AxisRC_nosplit.exe
restore
trap - EXIT
cmp -s "$keep" tools/names/split.txt && echo "split.txt restored ($(wc -l < tools/names/split.txt) lines)" || { echo "SPLIT.TXT NOT RESTORED"; exit 1; }
bash standalone/build.sh 2>&1 | grep -E " error|undefined"
echo "built build/AxisRC_nosplit.exe and build/AxisRC.exe"
