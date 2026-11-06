#!/usr/bin/env bash
# session A: a hosted arena - the free camera's keys while watching, then joined: the remaining controls, the
# chat cheat codes, the Esc menu, the time limit running out
. "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/a529c516-7b14-4d0b-88d6-38bdabdd7de7/scratchpad/trace/mp_lib.sh"
D=/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace
cmp -s "$G/AxisGL.exe" "$R/installed.exe" || { echo "installed exe differs - stop"; exit 1; }
test ! -e "$G/AxisRC.exe" || { echo "AxisRC.exe in the game folder - stop"; exit 1; }
rm -rf "$D/abak"; mkdir -p "$D/abak"; cp -r "$G/Save" "$D/abak/Save"; cp -p "$G/initdata/axis.cfg" "$D/abak/axis.cfg"; cp -p "$G/axisnet.ini" "$D/abak/axisnet.ini"
printf '[net]\nmode=local\nupnp=0\n' > "$G/axisnet.ini"
python - "$G/initdata/axis.cfg" <<'PY'
import sys, re
p = sys.argv[1]; t = open(p, encoding='latin-1', newline='').read()
t = re.sub(r'set_server map [^\r\n]*', 'set_server map 3', t); t = re.sub(r'set_server type [^\r\n]*', 'set_server type DEATH MATCH', t)
t = re.sub(r'set_server timeflag [^\r\n]*', 'set_server timeflag 1', t); t = re.sub(r'set_server customize [^\r\n]*', 'set_server customize OFF', t)
open(p, 'w', encoding='latin-1', newline='').write(t)
PY
rm -f "$G"/rtrace_*; cp "$R/build/AxisRC_rtrace.exe" "$G/AxisRC.exe"
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisRC.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
sleep 12
mk AxisRC 4 0x0D >/dev/null; mk AxisRC 5 0x49 >/dev/null; mk AxisRC 6 0x4D >/dev/null; mk AxisRC 5 0x43 >/dev/null; mk AxisRC 14 0x54 >/dev/null
shot AxisRC sA-watch >/dev/null
hold() { vk AxisRC "key $1 down" >/dev/null; sleep $2; vk AxisRC "key $1 up" >/dev/null; sleep 0.3; }
tap() { vk AxisRC "key $1" >/dev/null; sleep ${2:-0.6}; }
# watching: the free camera
for k in 0x57 0x53 0x41 0x44 0x25 0x27 0x26 0x28 0x21 0x22 0x24 0x23 0x6B 0x6D 0x52 0x46 0x20 0x10 0x11; do hold $k 1; done
vk AxisRC "rel 300 0" >/dev/null; vk AxisRC "rel 0 -100" >/dev/null; vk AxisRC "mdown 960 540 right" >/dev/null; sleep 1; vk AxisRC "mup right" >/dev/null
for k in 0x70 0x71 0x72 0x73 0x74 0x75 0x76 0x77 0x78 0x79 0x7A 0x7B 0x09 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38 0x39 0x30; do tap $k; done
shot AxisRC sA-watch2 >/dev/null
# join and play
mk AxisRC 2 0x1B >/dev/null; mk AxisRC 2 0x0D >/dev/null; mk AxisRC 5 0x0D >/dev/null
shot AxisRC sA-play >/dev/null
hold 0x57 2; hold 0x52 1; hold 0x46 1; hold 0x25 1; hold 0x27 1; hold 0x20 1.5
vk AxisRC "mdown 960 540 right" >/dev/null; sleep 1.5; vk AxisRC "mup right" >/dev/null
vk AxisRC "mdown 960 540" >/dev/null; sleep 2; vk AxisRC "mup" >/dev/null
for k in 0x51 0x45 0x31 0x32 0x33 0x34 0x35 0x36 0x58 0x42 0x56 0x56 0x56 0x56; do tap $k; done
hold 0xA0 1.5; hold 0x09 1.5; tap 0x73; tap 0x74; tap 0x79; tap 0x79; tap 0x7A; tap 0x7A
# the cheat codes (chat)
for c in "give me a big head" "get back my head" "good bye friends"; do tap 0x0D 0.8; drv AxisRC "scanmode off" "type $c" >/dev/null; sleep 0.5; tap 0x0D 3; done
shot AxisRC sA-cheat >/dev/null
sleep 8; hold 0x57 2; vk AxisRC "mdown 960 540" >/dev/null; sleep 2; vk AxisRC "mup" >/dev/null
# the Esc menu
mk AxisRC 2 0x1B >/dev/null; shot AxisRC sA-esc >/dev/null; mk AxisRC 1 0x28 >/dev/null; mk AxisRC 1 0x28 >/dev/null; shot AxisRC sA-esc2 >/dev/null; mk AxisRC 2 0x1B >/dev/null
# the time limit runs out (1 minute)
sleep 45; shot AxisRC sA-end >/dev/null; sleep 20; shot AxisRC sA-end2 >/dev/null
running
powershell -NoProfile -Command "Stop-Process -Name AxisRC -Force -ErrorAction SilentlyContinue"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; rm -f "$G/AxisRC.exe" 2>/dev/null; test ! -e "$G/AxisRC.exe" && break; done
for f in $G/rtrace_*.tsv; do test -e $f && mv $f $D/runs2/sessA_$(basename $f); done; rm -f $G/rtrace_*.tmp "$G/standalone.log"
cp -p "$D/abak/axis.cfg" "$G/initdata/axis.cfg"; cp -p "$D/abak/axisnet.ini" "$G/axisnet.ini"
diff -r "$D/abak/Save" "$G/Save" >/dev/null && echo "saves unchanged" || { rm -rf "$G/Save"; cp -r "$D/abak/Save" "$G/Save"; echo "saves restored"; }
cmp -s "$R/installed.exe" "$G/AxisGL.exe" && echo "installed exe unchanged"
ls "$G"/*.dmp 2>/dev/null; echo sessA done
