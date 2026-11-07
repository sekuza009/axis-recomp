#!/usr/bin/env bash
# the suite's scenarios through keys.sh with the range-trace build; saves / axis.cfg backed up here and put back after each
D=C:/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace
G=C:/Users/Alexander/Desktop/Axis; R=$G/recomp
cd $R
rm -rf $D/bak; mkdir -p $D/bak $D/runs; cp -r $G/Save $D/bak/Save; cp -p $G/initdata/axis.cfg $D/bak/axis.cfg
eval "$(sed -n '/^declare -A S/,/^S\[replay\]/p' standalone/suite.sh)"
for n in "$@"; do
	rm -f $G/rtrace_*
	RC_EXE=$R/build/AxisRC_rtrace.exe timeout 500 bash standalone/keys.sh "rt_$n" ${S[$n]} 2>&1 | grep -E "EXITED|running|CHANGED|unchanged|CRASH" | tr '\n' ' '
	echo
	for f in $G/rtrace_*.tsv; do test -e $f && mv $f $D/runs/${n}_$(basename $f); done; rm -f $G/rtrace_*.tmp
	diff -r $D/bak/Save $G/Save >/dev/null || { if ls "$D/bak/Save"/*.axs >/dev/null 2>&1; then rm -rf "$G/Save"; cp -r "$D/bak/Save" "$G/Save"; else echo "NO SAVE BACKUP in $D/bak/Save: Save left as it is"; fi; echo "  $n: saves restored"; }
	cmp -s $D/bak/axis.cfg $G/initdata/axis.cfg || { cp -p $D/bak/axis.cfg $G/initdata/axis.cfg; echo "  $n: axis.cfg restored"; }
	echo "$n done"
done
