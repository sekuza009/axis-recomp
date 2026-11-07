#!/usr/bin/env bash
# standalone/keys_gl.sh <prefix> (the installed AxisGL.exe itself, unchanged: the reference) <key wait shot>...: AxisRC.exe from its start screen through the keys given, a screenshot
# after each (<prefix>-<shot>.png); else as play2.sh
# profiles (screenshots <prefix>-*.png in the test4 scratchpad), else as play.sh: 
# test4 scratchpad) for build/AxisRC.exe. Nothing of the installed game is swapped: AxisRC.exe is copied into the
# game folder for the run (it reads AxisGL.exe there) and removed after. RECOMP_SKIP passes through.
R="C:/Users/Alexander/Desktop/Axis/recomp"
O="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/06c80a09-9c49-4ed0-83b2-bff2cac60b6e/scratchpad"
S="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/0b4df063-0171-44b1-8c17-2ffdad638f27/scratchpad"
G="C:/Users/Alexander/Desktop/Axis"
P="$S/$1"
M="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/33e72afb-5455-4cef-9fc9-6e39a57131ea/scratchpad"   # gshot/k.sh copies that look for the AxisRC process
shot() { powershell -NoProfile -ExecutionPolicy Bypass -File "$M/gshot_gl.ps1" "$P-$1.png" 0.5 | tail -1; }
set -e
cmp -s "$G/AxisGL.exe" "$R/game.exe" || { echo "installed exe differs from recomp/game.exe - stop"; exit 1; }
test ! -e "$G/recomp.dll" || { echo "a recomp.dll is in the game folder (a harness run?) - stop"; exit 1; }
rm -rf "$R/Save.bak"; cp -r "$G/Save" "$R/Save.bak"; rm -f "$G/standalone.log"
cp -p "$G/initdata/axis.cfg" "$R/axis.cfg.bak"   # (the player's settings: put back after the run)
set +e
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisGL.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
sleep 12
shot menu0
# the steps: <key> <wait> <shot name> ... (key: a virtual-key code, or "-" for none)
shift
while [ $# -ge 3 ]; do
	[ "$1" != "-" ] && "$M/k_gl.sh" - "$2" "$1" || sleep "$2"
	shot "$3"
	shift 3
done
powershell -NoProfile -Command "if (Get-Process AxisGL -ErrorAction SilentlyContinue) { 'game still running' } else { 'GAME EXITED' }"
powershell -NoProfile -Command "Stop-Process -Name AxisGL -Force"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; true 2>/dev/null && test ! -e "$G/AxisRC.exe" && break; done
cmp -s "$R/game.exe" "$G/AxisGL.exe" && echo "installed AxisGL.exe unchanged" || echo "AXISGL.EXE CHANGED"
diff -r "$R/Save.bak" "$G/Save" >/dev/null && echo "saves unchanged" || echo "SAVES CHANGED"
# axis.cfg as the run left it, compared (the settings read and written back unchanged), then the player's put back
cmp -s "$R/axis.cfg.bak" "$G/initdata/axis.cfg" && echo "axis.cfg unchanged" || { echo "AXIS.CFG CHANGED:"; diff "$R/axis.cfg.bak" "$G/initdata/axis.cfg"; }
cp -p "$R/axis.cfg.bak" "$G/initdata/axis.cfg"
grep -v "^  rebuilt " "$G/standalone.log"; grep -c "^  rebuilt " "$G/standalone.log"
mv "$G/standalone.log" "$P-standalone.log" 2>/dev/null
ls "$G"/*.dmp 2>/dev/null && echo "CRASH DUMPS"
exit 0
