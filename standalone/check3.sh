#!/usr/bin/env bash
# standalone/check3.sh <prefix>: a split batch's run-time check - the normal build and both fence builds
# (FENCE=1 guard pages after each split variable, FENCE=2 before): all three built first (build/AxisRC_f<n>.exe,
# the normal one last so build/AxisRC.exe stays it), then play.sh in each and play2.sh in the two fence builds (the
# same code under the guard pages; the canary watch runs in all three); the lines that matter (running, IN MATCH,
# axis.cfg, CANARY / FENCE / ORIGINAL / CRASH). Takes ~10 minutes: run it in the background, alone (no build.sh,
# sweep or other play test at the same time).
R="C:/Users/Alexander/Desktop/Axis/recomp"
L="C:/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/0b4df063-0171-44b1-8c17-2ffdad638f27/scratchpad"
cd "$R"
out=$(python tools/split_aliases.py) || { echo "$out" | tail -5; echo "names reach split objects' old places - stop"; exit 1; }
python tools/mkdatasrc.py > /dev/null   # (split.txt / objects.txt as they stand: build.sh does not regenerate src/data)
for F in 1 2 0; do
	rm -f build/AxisRC.exe
	if [ $F = 0 ]; then bash standalone/build.sh > build/check3_build.log 2>&1
	else FENCE=$F bash standalone/build.sh > build/check3_build.log 2>&1; fi
	st=$?
	grep -E " error|undefined" build/check3_build.log | head -3
	[ $st = 0 ] && [ -e build/AxisRC.exe ] || { echo "build (FENCE=$F) failed - stop"; exit 1; }
	cp build/AxisRC.exe build/AxisRC_f$F.exe || exit 1
done
for F in 0 1 2; do
	runs="play play2"
	[ $F = 0 ] && runs="play"
	for s in $runs; do
		p="$1$F$s"
		RC_EXE="$R/build/AxisRC_f$F.exe" timeout 590 bash standalone/$s.sh $p 2>&1 | grep -E "game still|EXITED|MATCH|AXIS.CFG|^[<>] |SAVES CHANGED" | sed "s/^/$p: /" | cut -c1-140
		grep -E "CANARY|FENCE|ORIGINAL|CRASH|NO HEAP" "$L/$p-standalone.log" | cut -c1-220
	done
done
echo "done (build/AxisRC.exe is the normal build)"
