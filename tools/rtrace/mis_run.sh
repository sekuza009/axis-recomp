. "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/a529c516-7b14-4d0b-88d6-38bdabdd7de7/scratchpad/trace/mp_lib.sh"
test ! -e "$G/initdata/axis.mis" || { echo "an axis.mis exists - stop"; exit 1; }
test ! -e "$G/AxisRC.exe" || { echo "AxisRC.exe in the game folder - stop"; exit 1; }
rm -rf "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak"; mkdir -p "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak"; cp -r "$G/Save" "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save"; cp -p "$G/initdata/axis.cfg" "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/axis.cfg"
cp "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/a529c516-7b14-4d0b-88d6-38bdabdd7de7/scratchpad/trace/axis.mis" "$G/initdata/axis.mis"; cp "$R/build/AxisRC_rtrace.exe" "$G/AxisRC.exe"; rm -f "$G"/rtrace_*
export AXISRC_MISSIONS=1
powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisRC.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
sleep 12
mk AxisRC 4 0x0D >/dev/null; mk AxisRC 5 0x49 >/dev/null; mk AxisRC 6 0x4B >/dev/null; shot AxisRC rmis1
mk AxisRC 2 0x28 >/dev/null; mk AxisRC 2 0x26 >/dev/null; mk AxisRC 1 0x41 >/dev/null; sleep 15; shot AxisRC rmis2
mk AxisRC 3 0x4E >/dev/null; mk AxisRC 3 0x50 >/dev/null; mk AxisRC 3 0x4E >/dev/null; shot AxisRC rmis3
mk AxisRC 3 0x1B >/dev/null; mk AxisRC 2 0x28 >/dev/null; mk AxisRC 1 0x41 >/dev/null; sleep 12; shot AxisRC rmis4
mk AxisRC 3 0x1B >/dev/null; mk AxisRC 5 0x1B >/dev/null; shot AxisRC rmis5
running
powershell -NoProfile -Command "Stop-Process -Name AxisRC -Force -ErrorAction SilentlyContinue"
for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; rm -f "$G/AxisRC.exe" 2>/dev/null; test ! -e "$G/AxisRC.exe" && break; done
rm -f "$G/initdata/axis.mis"; rm -f "$G/standalone.log"
for f in $G/rtrace_*.tsv; do test -e $f && mv $f /c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/runs/missions_$(basename $f); done; rm -f $G/rtrace_*.tmp
diff -r "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save" "$G/Save" >/dev/null && echo "saves unchanged" || { if ls "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save"/*.axs >/dev/null 2>&1; then rm -rf "$G/Save"; cp -r "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save" "$G/Save"; else echo "NO SAVE BACKUP in /c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/Save: Save left as it is"; fi; echo "saves restored"; }
cmp -s "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/axis.cfg" "$G/initdata/axis.cfg" && echo "axis.cfg unchanged" || { cp -p "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace/mbak/axis.cfg" "$G/initdata/axis.cfg"; echo "axis.cfg restored"; }
cmp -s "$R/installed.exe" "$G/AxisGL.exe" && echo "installed exe unchanged"
ls "$G/initdata/axis.mis" 2>/dev/null; echo mis done
