#!/usr/bin/env bash
# host_run.sh tag map "TYPE" timeflag join wait: one host-only arena with the trace build; axis.cfg / saves /
# axisnet.ini backed up first and put back after. join 1: join a team after creating, then wait <wait> seconds.
. "C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/a529c516-7b14-4d0b-88d6-38bdabdd7de7/scratchpad/trace/mp_lib.sh"
tag=$1 map=$2 type=$3 time=$4 join=$5 wait=$6
true
cmp -s "$G/AxisGL.exe" "$R/installed.exe" || { echo "installed exe differs - stop"; exit 1; }
test ! -e "$G/AxisRC.exe" || { echo "AxisRC.exe in the game folder - stop"; exit 1; }
rm -rf "$SP/hbak"; mkdir -p "$SP/hbak"; cp -r "$G/Save" "$SP/hbak/Save"; cp -p "$G/initdata/axis.cfg" "$SP/hbak/axis.cfg"; cp -p "$G/axisnet.ini" "$SP/hbak/axisnet.ini"
printf '[net]\nmode=local\nupnp=0\n' > "$G/axisnet.ini"
python - "$G/initdata/axis.cfg" "$map" "$type" "$time" <<'PY'
import sys, re
p, m, ty, tm = sys.argv[1:]
t = open(p, encoding='latin-1', newline='').read()
t = re.sub(r'set_server map [^\r\n]*', 'set_server map ' + m, t)
t = re.sub(r'set_server type [^\r\n]*', 'set_server type ' + ty, t)
t = re.sub(r'set_server timeflag [^\r\n]*', 'set_server timeflag ' + tm, t)
t = re.sub(r'set_server customize [^\r\n]*', 'set_server customize OFF', t)
open(p, 'w', encoding='latin-1', newline='').write(t)
PY
rm -f "$G"/trace_*.log "$G/standalone.log"
cp "$R/build/AxisRC_rtrace.exe" "$G/AxisRC.exe"
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisRC.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
sleep 12
mk AxisRC 4 0x0D >/dev/null; mk AxisRC 5 0x49 >/dev/null; mk AxisRC 6 0x4D >/dev/null; mk AxisRC 5 0x43 >/dev/null; mk AxisRC 14 0x54 >/dev/null
shot AxisRC "$tag-a" >/dev/null
if [ "$join" = 1 ]; then
	mk AxisRC 2 0x1B >/dev/null; mk AxisRC 2 0x0D >/dev/null; mk AxisRC 4 0x0D >/dev/null
	shot AxisRC "$tag-b" >/dev/null
	sleep "$wait"
	shot AxisRC "$tag-c" >/dev/null
fi
powershell -NoProfile -Command "Stop-Process -Name AxisRC -Force -ErrorAction SilentlyContinue"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; rm -f "$G/AxisRC.exe" 2>/dev/null; test ! -e "$G/AxisRC.exe" && break; done
for f in $G/rtrace_*.tsv; do mv $f /c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/runs/host-${tag}_$(basename $f); done; rm -f $G/rtrace_*.tmp; rm -f "$G/standalone.log"
cp -p "$SP/hbak/axis.cfg" "$G/initdata/axis.cfg"; cp -p "$SP/hbak/axisnet.ini" "$G/axisnet.ini"
diff -r "$SP/hbak/Save" "$G/Save" >/dev/null || { if ls "$SP/hbak/Save"/*.axs >/dev/null 2>&1; then if ls "$SP/hbak/Save"/*.axs >/dev/null 2>&1; then rm -rf "$G/Save"; cp -r "$SP/hbak/Save" "$G/Save"; else echo "NO SAVE BACKUP in $SP/hbak/Save: Save left as it is"; fi; else echo "NO SAVE BACKUP in $SP/hbak/Save: Save left as it is"; fi; echo "$tag: saves restored"; }
cmp -s "$R/installed.exe" "$G/AxisGL.exe" || echo "AXISGL.EXE CHANGED"
ls "$G"/*.dmp 2>/dev/null && echo "CRASH DUMPS"
echo "$tag done"
