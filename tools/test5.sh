#!/usr/bin/env bash
# test5.sh <prefix>: the early play test: RECOMP_EARLY=1 - no tests; the functions the last full run hooked
# (recomp/recomp.passed) are switched in at start-up, so the game's own start-up runs on them too. Otherwise as test4.sh:
# (recomp/build/AxisGL.exe + recomp.dll installed temporarily, a skirmish),
# with screenshots of the menus as well as the match, saved as <prefix>-*.png here. RECOMP_SKIP passes through.
R="C:/Users/Alexander/Desktop/Axis/recomp"
O="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/06c80a09-9c49-4ed0-83b2-bff2cac60b6e/scratchpad"
S="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/0b4df063-0171-44b1-8c17-2ffdad638f27/scratchpad"
G="C:/Users/Alexander/Desktop/Axis"
P="$S/$1"
shot() { powershell -NoProfile -ExecutionPolicy Bypass -File "$O/gshot.ps1" "$P-$1.png" 0.5 | tail -1; }
set -e
cmp -s "$G/AxisGL.exe" "$R/installed.exe" || { echo "installed exe differs from recomp/installed.exe - stop"; exit 1; }
rm -rf "$R/Save.bak"; cp -r "$G/Save" "$R/Save.bak"; rm -f "$G/recomp.log"
test -f "$R/recomp.passed" || { echo "no recomp/recomp.passed: run test4.sh first"; exit 1; }
cp "$R/build/AxisGL.exe" "$G/AxisGL.exe"; cp "$R/recomp.dll" "$G/recomp.dll"; cp "$R/recomp.passed" "$G/recomp.passed"
export RECOMP_EARLY=1
set +e
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisGL.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
sleep 12   # (no tests: the game starts at once)
cat "$G/recomp_early.log" 2>/dev/null || echo "NO recomp_early.log"
sleep 4
shot menu0
"$O/k.sh" - 4 0x0D; shot menu1
"$O/k.sh" - 4 0x49; shot menu2
"$O/k.sh" - 4 0x4B; shot menu3
"$O/k.sh" - 1.5 0x25 0x25 0x25; shot menu4
"$O/k.sh" - 12 0x4F; "$O/k.sh" - 2 0x1B 0x0D; "$O/k.sh" - 6 0x0D
shot match1
sleep 30
shot match2
powershell -NoProfile -Command "if (Get-Process AxisGL -ErrorAction SilentlyContinue) { 'game still running' } else { 'GAME EXITED' }"
powershell -NoProfile -Command "Stop-Process -Name AxisGL -Force"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; cp "$R/installed.exe" "$G/AxisGL.exe" 2>/dev/null && break; done
cmp -s "$R/installed.exe" "$G/AxisGL.exe" && echo "installed AxisGL.exe restored (identical)" || echo "AXISGL.EXE NOT RESTORED"
rm -f "$G/recomp.dll"
diff -r "$R/Save.bak" "$G/Save" >/dev/null && echo "saves unchanged" || echo "SAVES CHANGED"
grep "KEPT ORIGINAL\|replaces the patch" "$G/recomp_early.log"
mv "$G/recomp_early.log" "$P-recomp_early.log" 2>/dev/null
rm -f "$G/recomp.passed"
