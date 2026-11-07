#!/usr/bin/env bash
# two copies of the range-trace build: AxisRC hosts a TEAM DEATH MATCH arena, AxisRC2 joins over 127.0.0.1 and plays
. "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/a529c516-7b14-4d0b-88d6-38bdabdd7de7/scratchpad/trace/mp_lib.sh"
set -e
cmp -s "$G/AxisGL.exe" "$R/installed.exe" || { echo "installed exe differs - stop"; exit 1; }
test ! -e "$G/AxisRC.exe" || { echo "AxisRC.exe already in the game folder - stop"; exit 1; }
rm -rf "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak"; mkdir -p "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak"; cp -r "$G/Save" "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save"; cp -p "$G/initdata/axis.cfg" "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/axis.cfg"; cp -p "$G/axisnet.ini" "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/axisnet.ini"
printf '[net]\nmode=local\nupnp=0\nlog=1\n' > "$G/axisnet.ini"
rm -f "$G"/rtrace_* "$G/standalone.log" "$G/axisnet.log"
cp "$R/build/AxisRC_rtrace.exe" "$G/AxisRC.exe"; cp "$R/build/AxisRC_rtrace.exe" "$G/AxisRC2.exe"
set +e
export AXISRC_MULTI=1
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisRC.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
sleep 12
mk AxisRC 4 0x0D; mk AxisRC 5 0x49; mk AxisRC 6 0x4D; mk AxisRC 5 0x43; mk AxisRC 14 0x54
mk AxisRC 2 0x1B; mk AxisRC 2 0x0D; mk AxisRC 4 0x0D
shot AxisRC mph1
minimize AxisRC; sleep 2
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisRC2.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
sleep 12
mk AxisRC2 4 0x0D; mk AxisRC2 5 0x49; mk AxisRC2 6 0x4D; mk AxisRC2 5 0x4A; mk AxisRC2 4 0x50
drv AxisRC2 "scanmode off" "type 127.0.0.1"; sleep 1
mk AxisRC2 15 0x0D
mk AxisRC2 3 0x1B; mk AxisRC2 3 0x0D; mk AxisRC2 2 0x28; mk AxisRC2 8 0x0D
shot AxisRC2 mpc1
for i in 1 2 3; do
	vk AxisRC2 "key 0x57 down"; sleep 3; vk AxisRC2 "key 0x57 up"; vk AxisRC2 "rel 300 0"; vk AxisRC2 "mdown 960 540"; sleep 2; vk AxisRC2 "mup"
	vk AxisRC2 "key 0x41 down"; sleep 1.5; vk AxisRC2 "key 0x41 up"; vk AxisRC2 "key 0x20 down"; sleep 1.5; vk AxisRC2 "key 0x20 up"; vk AxisRC2 "key 0x09"; sleep 1
done
powershell -NoProfile -ExecutionPolicy Bypass -File "C:/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/suspend.ps1" AxisRC 5; sleep 6; powershell -NoProfile -ExecutionPolicy Bypass -File "C:/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/suspend.ps1" AxisRC2 5; sleep 6
vk AxisRC2 "key 0x0D"; sleep 0.5; vk AxisRC2 "type gg"; vk AxisRC2 "key 0x0D"; sleep 1
sleep 30
shot AxisRC2 mpc2
restore AxisRC; sleep 3; shot AxisRC mph2
sleep 10
running
powershell -NoProfile -Command "Stop-Process -Name AxisRC,AxisRC2 -Force -ErrorAction SilentlyContinue"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; rm -f "$G/AxisRC.exe" "$G/AxisRC2.exe" 2>/dev/null; test ! -e "$G/AxisRC.exe" -a ! -e "$G/AxisRC2.exe" && break; done
for f in $G/rtrace_*.tsv; do mv $f /c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/runs2/loss_$(basename $f); done; rm -f $G/rtrace_*.tmp
mv "$G/axisnet.log" "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mp_axisnet.log" 2>/dev/null; rm -f "$G/standalone.log"
cmp -s "$R/installed.exe" "$G/AxisGL.exe" && echo "installed AxisGL.exe unchanged" || echo "AXISGL.EXE CHANGED"
diff -r "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save" "$G/Save" >/dev/null && echo "saves unchanged" || { if ls "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save"/*.axs >/dev/null 2>&1; then rm -rf "$G/Save"; cp -r "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save" "$G/Save"; else echo "NO SAVE BACKUP in /c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save: Save left as it is"; fi; echo "saves restored"; }
cmp -s "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/axis.cfg" "$G/initdata/axis.cfg" && echo "axis.cfg unchanged" || { cp -p "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/axis.cfg" "$G/initdata/axis.cfg"; echo "axis.cfg restored"; }
cp -p "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/axisnet.ini" "$G/axisnet.ini"
ls "$G"/*.dmp 2>/dev/null && echo "CRASH DUMPS"
echo mp done
