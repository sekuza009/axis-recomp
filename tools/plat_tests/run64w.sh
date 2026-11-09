#!/usr/bin/env bash
# the 64-bit build run headless on Windows (build/axis64_test.exe, standalone/build64.sh windows), on a scratch
# game folder (the data folders joined in read only, the saves, settings and loose files copied) - the user's registry
# key HKCU\SOFTWARE\AxisArena exported before and imported back after. Usage: run64w.sh <scratch dir> [frames] [stream]
set -e
cd "$(dirname "$0")/../.."
D=$1; FRAMES=${2:-300}; STREAM=$3
G=/c/Users/Alexander/Desktop/Axis
: built by standalone/build64.sh windows
mkdir -p "$D"
WD=$(cd "$D" && pwd -W)
for d in Data Map Sound Music; do
	[ -e "$D/$d" ] || powershell -NoProfile -Command "New-Item -ItemType Junction -Path '$WD/$d' -Target 'C:/Users/Alexander/Desktop/Axis/$d' | Out-Null"
done
[ -d "$D/Save" ] || cp -r "$G/Save" "$D/Save"
[ -d "$D/initdata" ] || cp -r "$G/initdata" "$D/initdata"
for f in Chat.scp Help.txt MATHFUNC.TBL axisnet.ini AxisPlay.exe; do [ -e "$D/$f" ] || cp "$G/$f" "$D/"; done
REG="$WD\AxisArena_before.reg"
MSYS_NO_PATHCONV=1 reg export 'HKCU\SOFTWARE\AxisArena' "$REG" /y > /dev/null
set +e
./build/axis64_test.exe "$WD" $FRAMES $STREAM
echo "exit $?"
MSYS_NO_PATHCONV=1 reg import "$REG" > /dev/null 2>&1 && echo "registry restored"
