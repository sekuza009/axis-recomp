#!/usr/bin/env bash
# standalone/play.sh <prefix>: tools/test4.sh's play test (menus, a skirmish, screenshots <prefix>-*.png in the
# test4 scratchpad) for build/AxisRC.exe. Nothing of the installed game is swapped: AxisRC.exe is copied into the
# game folder for the run (it reads AxisGL.exe there) and removed after. RECOMP_SKIP passes through.
R="C:/Users/Alexander/Desktop/Axis/recomp"
O="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/06c80a09-9c49-4ed0-83b2-bff2cac60b6e/scratchpad"
S="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/0b4df063-0171-44b1-8c17-2ffdad638f27/scratchpad"
G="C:/Users/Alexander/Desktop/Axis"
P="$S/$1"
M="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/33e72afb-5455-4cef-9fc9-6e39a57131ea/scratchpad"   # gshot/k.sh copies that look for the AxisRC process
shot() { powershell -NoProfile -ExecutionPolicy Bypass -File "$M/gshot_rc.ps1" "$P-$1.png" 0.5 | tail -1; }
set -e
cmp -s "$G/AxisGL.exe" "$R/installed.exe" || { echo "installed exe differs from recomp/installed.exe - stop"; exit 1; }
test ! -e "$G/recomp.dll" || { echo "a recomp.dll is in the game folder (a harness run?) - stop"; exit 1; }
rm -rf "$R/Save.bak"; cp -r "$G/Save" "$R/Save.bak"; rm -f "$G/standalone.log"
cp -p "$G/initdata/axis.cfg" "$R/axis.cfg.bak"   # (the player's settings: put back after the run)
cp "$R/build/AxisRC.exe" "$G/AxisRC.exe"
set +e
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisRC.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
sleep 12
shot menu0
"$M/k_rc.sh" - 4 0x0D; shot menu1
"$M/k_rc.sh" - 4 0x49; shot menu2
"$M/k_rc.sh" - 4 0x4B; shot menu3
"$M/k_rc.sh" - 1.5 0x25 0x25 0x25; shot menu4
"$M/k_rc.sh" - 12 0x4F; "$M/k_rc.sh" - 2 0x1B 0x0D; "$M/k_rc.sh" - 6 0x0D
shot match1
sleep 30
shot match2
powershell -NoProfile -Command "if (Get-Process AxisRC -ErrorAction SilentlyContinue) { 'game still running' } else { 'GAME EXITED' }"
python "$R/tools/inmatch.py" "$P-match1.png" | cut -d" " -f1-4   # (the HUD up: the player spawned, not the loading screen or the free camera)
powershell -NoProfile -Command "Stop-Process -Name AxisRC -Force"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; rm -f "$G/AxisRC.exe" 2>/dev/null && test ! -e "$G/AxisRC.exe" && break; done
cmp -s "$R/installed.exe" "$G/AxisGL.exe" && echo "installed AxisGL.exe unchanged" || echo "AXISGL.EXE CHANGED"
diff -r "$R/Save.bak" "$G/Save" >/dev/null && echo "saves unchanged" || echo "SAVES CHANGED"
# axis.cfg as the run left it, compared (the settings read and written back unchanged), then the player's put back
cmp -s "$R/axis.cfg.bak" "$G/initdata/axis.cfg" && echo "axis.cfg unchanged" || { echo "AXIS.CFG CHANGED:"; diff "$R/axis.cfg.bak" "$G/initdata/axis.cfg"; }
cp -p "$R/axis.cfg.bak" "$G/initdata/axis.cfg"
grep -v "^  rebuilt " "$G/standalone.log"; grep -c "^  rebuilt " "$G/standalone.log"
mv "$G/standalone.log" "$P-standalone.log" 2>/dev/null
ls "$G"/*.dmp 2>/dev/null && echo "CRASH DUMPS"
exit 0
