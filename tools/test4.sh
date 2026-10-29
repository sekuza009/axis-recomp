#!/usr/bin/env bash
# test4.sh <prefix>: test3.sh's play test (recomp\build\AxisGL.exe + recomp.dll installed temporarily, a skirmish),
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
cp "$R/build/AxisGL.exe" "$G/AxisGL.exe"; cp "$R/recomp.dll" "$G/recomp.dll"
set +e
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisGL.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
for i in $(seq 1 750); do grep -q "recomp: done" "$G/recomp.log" 2>/dev/null && break; sleep 2; done
grep -q "recomp: done" "$G/recomp.log" 2>/dev/null && echo "recomp finished after ~$((i * 2)) s" || echo "RECOMP DID NOT FINISH"
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
grep "KEPT ORIGINAL\|replaces the patch\|crash" "$G/recomp.log"; grep -c "bit-exact" "$G/recomp.log"
mv "$G/recomp.log" "$P-recomp.log" 2>/dev/null
mv "$G/recomp.progress" "$P-recomp.progress" 2>/dev/null
mv "$G/recomp.passed" "$R/recomp.passed" 2>/dev/null   # the functions hooked: test5.sh (early) switches these in at start-up
