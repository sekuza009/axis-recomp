#!/usr/bin/env bash
# standalone/check3.sh <prefix>: a split batch's run-time check - the normal build and both fence builds
# (FENCE=1 guard pages after each split variable, FENCE=2 before), play.sh and play2.sh in each; the lines that
# matter (running, IN MATCH, axis.cfg, CANARY / FENCE / ORIGINAL / CRASH); the normal build rebuilt at the end.
# Takes ~35 minutes: run it in the background, alone (no build.sh, sweep or other play test at the same time).
R="C:/Users/Alexander/Desktop/Axis/recomp"
L="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/0b4df063-0171-44b1-8c17-2ffdad638f27/scratchpad"
cd "$R"
for F in 0 1 2; do
	if [ $F = 0 ]; then bash standalone/build.sh 2>&1 | grep -E " error|undefined" | head -3
	else FENCE=$F bash standalone/build.sh 2>&1 | grep -E " error|undefined" | head -3; fi
	for s in play play2; do
		p="$1$F$s"
		timeout 590 bash standalone/$s.sh $p 2>&1 | grep -E "game still|EXITED|MATCH|AXIS.CFG|^[<>] |SAVES CHANGED" | sed "s/^/$p: /" | cut -c1-140
		grep -E "CANARY|FENCE|ORIGINAL|CRASH|NO HEAP" "$L/$p-standalone.log" | cut -c1-220
	done
done
bash standalone/build.sh >/dev/null 2>&1; echo "normal build rebuilt"
