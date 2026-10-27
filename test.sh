#!/usr/bin/env bash
# test.sh: start the installed game, inject recomp.dll at the title screen (compare + switch to rebuilt
# functions), play a round-12 skirmish for a while with screenshots, then kill the game and check saves.
R="C:/Users/Alexander/Desktop/Axis/recomp"
O="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/06c80a09-9c49-4ed0-83b2-bff2cac60b6e/scratchpad"
G="C:/Users/Alexander/Desktop/Axis"
rm -rf "$R/Save.bak"; cp -r "$G/Save" "$R/Save.bak"; rm -f "$G/recomp.log"
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisGL.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"; sleep 10
PID=$(powershell -NoProfile -Command "(Get-Process AxisGL).Id" | tr -d '\r')
"$R/inject.exe" "$PID" "$R/recomp.dll"
sleep 14                                    # 8 s delay + comparisons + hooks
"$O/k.sh" - 4 0x0D 0x49 0x4B; "$O/k.sh" - 1.5 0x25 0x25 0x25; "$O/k.sh" - 12 0x4F; "$O/k.sh" - 2 0x1B 0x0D; "$O/k.sh" - 6 0x0D
powershell -NoProfile -ExecutionPolicy Bypass -File "$O/gshot.ps1" "$R/match1.png" 0.3 | tail -1
sleep 20
powershell -NoProfile -ExecutionPolicy Bypass -File "$O/gshot.ps1" "$R/match2.png" 0.3 | tail -1
powershell -NoProfile -Command "if (Get-Process AxisGL -ErrorAction SilentlyContinue) { 'game still running' } else { 'GAME EXITED' }"
powershell -NoProfile -Command "Stop-Process -Name AxisGL -Force"; sleep 3
diff -r "$R/Save.bak" "$G/Save" >/dev/null && echo "saves unchanged" || echo "SAVES CHANGED"
cat "$G/recomp.log"; mv "$G/recomp.log" "$R/recomp.log"
