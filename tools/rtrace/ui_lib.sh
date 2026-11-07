# pointer driving for the menus: the game's pointer follows relative motion only (about 0.756 of it, in the
# half-size screenshot's pixels) and clicks act where it is
. "/c/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/a529c516-7b14-4d0b-88d6-38bdabdd7de7/scratchpad/trace/mp_lib.sh"
D=/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace
P=${P:-AxisRC}
goto() { vk $P "rel -6000 -6000" >/dev/null; sleep 0.2; vk $P "rel $(python -c "print(round(($1 - 10) / 0.756), round(($2 - 10) / 0.756))")" >/dev/null; sleep 0.3; }
clk() { vk $P "focus" >/dev/null; powershell -NoProfile -ExecutionPolicy Bypass -File "$(cygpath -w $D)\clickhere.ps1" >/dev/null; sleep ${1:-1.5}; }
at() { goto $1 $2; clk ${3:-1.5}; }
typ() { drv $P "scanmode off" "type $1" >/dev/null; sleep 0.4; }
key() { mk $P ${2:-1} $1 >/dev/null; }
sh() { shot $P "$1" >/dev/null; }
start_game() {
	cmp -s "$G/AxisGL.exe" "$R/installed.exe" || { echo "installed exe differs - stop"; exit 1; }
	test ! -e "$G/AxisRC.exe" || { echo "AxisRC.exe in the game folder - stop"; exit 1; }
	rm -rf "$D/ubak"; mkdir -p "$D/ubak"; cp -r "$G/Save" "$D/ubak/Save"; cp -p "$G/initdata/axis.cfg" "$D/ubak/axis.cfg"; cp -p "$G/axisnet.ini" "$D/ubak/axisnet.ini"
	rm -f "$G"/rtrace_*; cp "$R/build/AxisRC_rtrace.exe" "$G/AxisRC.exe"
	powershell -NoProfile -Command "Start-Process -FilePath 'C:\Users\Alexander\Desktop\Axis\AxisRC.exe' -WorkingDirectory 'C:\Users\Alexander\Desktop\Axis'"
	sleep 12; key 0x0D 4; key 0x49 5
}
end_game() {
	running
	powershell -NoProfile -Command "Stop-Process -Name AxisRC,AxisRC2 -Force -ErrorAction SilentlyContinue"
	for i in 1 2 3 4 5 6 7 8 9 10; do sleep 1; rm -f "$G/AxisRC.exe" "$G/AxisRC2.exe" 2>/dev/null; test ! -e "$G/AxisRC.exe" -a ! -e "$G/AxisRC2.exe" && break; done
	for f in $G/rtrace_*.tsv; do test -e $f && mv $f $D/runs2/$1_$(basename $f); done; rm -f $G/rtrace_*.tmp "$G/standalone.log"
	cp -p "$D/ubak/axis.cfg" "$G/initdata/axis.cfg"; cp -p "$D/ubak/axisnet.ini" "$G/axisnet.ini"
	diff -r "$D/ubak/Save" "$G/Save" >/dev/null && echo "saves unchanged" || { if ls "$D/ubak/Save"/*.axs >/dev/null 2>&1; then rm -rf "$G/Save"; cp -r "$D/ubak/Save" "$G/Save"; else echo "NO SAVE BACKUP in $D/ubak/Save: Save left as it is"; fi; echo "saves restored"; }
	cmp -s "$R/installed.exe" "$G/AxisGL.exe" && echo "installed exe unchanged"; ls "$G"/*.dmp 2>/dev/null; echo "$1 done"
}
