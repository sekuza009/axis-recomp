#!/usr/bin/env bash
# standalone/suite.sh [scenario...]: the comparison suite - each scenario (a key sequence, a screenshot after each
# step) in the installed AxisGL.exe (gl_), AxisRC with nothing split (ns_: build/AxisRC_nosplit.exe) and AxisRC
# (sp_: build/AxisRC.exe); tools/suite_compare.py then sets them side by side. Run alone, in the background; the
# screen and keyboard are the game's while it runs.
R="C:/Users/Alexander/Desktop/Axis/recomp"
L="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/0b4df063-0171-44b1-8c17-2ffdad638f27/scratchpad"
cd "$R"
declare -A S
S[profile]="0x0D 5 prof 0x4E 4 new 0x1B 3 back1 0x44 4 delete 0x1B 3 back2 0x1B 3 logout 0x1B 3 cancel"
S[mainmenu]="0x0D 4 prof 0x49 6 main - 4 main2 0x58 5 exitkey"
S[skirmish]="0x0D 4 prof 0x49 5 main 0x4B 5 rounds 0x25 2 left1 0x25 2 left2 0x25 2 left3 0x4F 14 loading - 12 match 0x1B 3 matchmenu 0x1B 3 back - 10 match2"
S[armc]="0x0D 4 prof 0x49 5 main 0x41 8 armc 0x48 4 head 0x27 4 head2 0x0D 4 headok 0x43 4 chest 0x27 4 chest2 0x1B 4 chestesc 0x57 4 weapon 0x27 4 weapon2 0x4C 4 colour 0x27 4 colour2"
S[setup]="0x0D 4 prof 0x49 5 main 0x53 6 setup 0x53 4 sound 0x1B 3 back1 0x47 4 graphic 0x1B 3 back2 0x43 4 control 0x1B 3 back3 0x1B 5 out"
S[multi]="0x0D 4 prof 0x49 5 main 0x4D 8 multi 0x50 5 player 0x1B 3 back1 0x43 5 create 0x1B 3 back2 0x4A 6 join 0x1B 4 back3"
S[ladder]="0x0D 4 prof 0x49 5 main 0x4C 8 ladder 0x50 5 id 0x1B 4 back1 0x1B 5 out"
S[replay]="0x0D 4 prof 0x49 5 main 0x70 5 replays 0x41 3 all 0x4F 20 play - 10 play2 0x1B 6 stop"
names="${*:-profile mainmenu skirmish armc setup multi ladder replay}"
for n in $names; do
	echo "== $n"
	timeout 400 bash standalone/keys_gl.sh "gl_$n" ${S[$n]} 2>&1 | grep -E "EXITED|AXIS.CFG|CHANGED" | sed "s/^/  gl: /"
	RC_EXE="$R/build/AxisRC_nosplit.exe" timeout 400 bash standalone/keys.sh "ns_$n" ${S[$n]} 2>&1 | grep -E "EXITED|AXIS.CFG|CHANGED" | sed "s/^/  ns: /"
	grep -E "CRASH|ORIGINAL|CANARY" "$L/ns_$n-standalone.log" 2>/dev/null | cut -c1-160 | sed "s/^/  ns: /"
	timeout 400 bash standalone/keys.sh "sp_$n" ${S[$n]} 2>&1 | grep -E "EXITED|AXIS.CFG|CHANGED" | sed "s/^/  sp: /"
	grep -E "CRASH|ORIGINAL|CANARY" "$L/sp_$n-standalone.log" 2>/dev/null | cut -c1-160 | sed "s/^/  sp: /"
done
echo "suite done"
