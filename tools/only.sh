#!/usr/bin/env bash
# only.sh name,name,...: install the test exe + recomp.dll, run only those state tests (RECOMP_NOHOOK=1, RECOMP_ONLY),
# wait for "recomp: done" or a crash, kill the game, restore the installed exe, print the results
R="$(cd "$(dirname "$0")/.." && pwd)"; G="$(cd "$R/.." && pwd)"
rm -f "$G/recomp.log" "$G/recomp.progress"
cmp -s "$G/AxisGL.exe" "$R/installed.exe" || { echo "installed exe differs from recomp/installed.exe - stop"; exit 1; }
cp "$R/build/AxisGL.exe" "$G/AxisGL.exe"; cp "$R/recomp.dll" "$G/recomp.dll"
export RECOMP_NOHOOK=1 RECOMP_ONLY="$1"
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisGL.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
for i in $(seq 1 120); do grep -q "recomp: done\|crash:" "$G/recomp.log" "$G/recomp.progress" 2>/dev/null && break; sleep 2; done
sleep 2
grep -q "recomp: done" "$G/recomp.log" 2>/dev/null || powershell -NoProfile -Command "if (Get-Process AxisGL -ErrorAction SilentlyContinue) { 'NOT DONE: game still running (hung?)' } else { 'NOT DONE: game exited' }"
powershell -NoProfile -Command "Stop-Process -Name AxisGL -Force -ErrorAction SilentlyContinue"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; cp "$R/installed.exe" "$G/AxisGL.exe" 2>/dev/null && break; done
cmp -s "$R/installed.exe" "$G/AxisGL.exe" && echo "restored" || echo "AXISGL.EXE NOT RESTORED"
rm -f "$G/recomp.dll"
grep -v "hooked\|KEPT ORIGINAL" "$G/recomp.log" | tail -n +22; echo "-- progress tail:"; tail -4 "$G/recomp.progress"
mv "$G/recomp.log" "$R/recomp.log"; mv "$G/recomp.progress" "$R/recomp.progress"
