#!/usr/bin/env bash
# test2.sh: run the game on the rebuilt functions without injection: temporarily install recomp\build\AxisGL.exe
# (its patch DLL loads recomp.dll at start-up) + recomp.dll, play a round-12 skirmish, then restore everything.
R="C:/Users/Alexander/Desktop/Axis/recomp"
O="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/06c80a09-9c49-4ed0-83b2-bff2cac60b6e/scratchpad"
G="C:/Users/Alexander/Desktop/Axis"
set -e
rm -rf "$R/Save.bak"; cp -r "$G/Save" "$R/Save.bak"; rm -f "$G/recomp.log"
cp "$G/AxisGL.exe" "$R/installed.exe"
cp "$R/build/AxisGL.exe" "$G/AxisGL.exe"; cp "$R/recomp.dll" "$G/recomp.dll"
set +e
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisGL.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"; sleep 24
"$O/k.sh" - 4 0x0D 0x49 0x4B; "$O/k.sh" - 1.5 0x25 0x25 0x25; "$O/k.sh" - 12 0x4F; "$O/k.sh" - 2 0x1B 0x0D; "$O/k.sh" - 6 0x0D
powershell -NoProfile -ExecutionPolicy Bypass -File "$O/gshot.ps1" "$R/match1.png" 0.3 | tail -1
sleep 30
powershell -NoProfile -ExecutionPolicy Bypass -File "$O/gshot.ps1" "$R/match2.png" 0.3 | tail -1
powershell -NoProfile -Command "if (Get-Process AxisGL -ErrorAction SilentlyContinue) { 'game still running' } else { 'GAME EXITED' }"
powershell -NoProfile -Command "Stop-Process -Name AxisGL -Force"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; cp "$R/installed.exe" "$G/AxisGL.exe" 2>/dev/null && break; done
cmp -s "$R/installed.exe" "$G/AxisGL.exe" && echo "installed AxisGL.exe restored (identical)" || echo "AXISGL.EXE NOT RESTORED"
rm -f "$G/recomp.dll"
diff -r "$R/Save.bak" "$G/Save" >/dev/null && echo "saves unchanged" || echo "SAVES CHANGED"
cat "$G/recomp.log" 2>/dev/null | grep -v hooked; mv "$G/recomp.log" "$R/recomp.log" 2>/dev/null
