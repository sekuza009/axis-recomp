#!/usr/bin/env bash
# every session again with the improved checker; results in runs2/
D=/c/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/rtrace; T=/c/Users/ALEXAN~1/AppData/Local/Temp/claude/C--Users-Alexander-Desktop-Axis/a529c516-7b14-4d0b-88d6-38bdabdd7de7/scratchpad/trace; G=/c/Users/Alexander/Desktop/Axis; R=$G/recomp
cd $R
grab() { for f in $G/rtrace_*.tsv; do test -e $f && mv $f $D/runs2/$1_$(basename $f); done; rm -f $G/rtrace_*.tmp; }
restore() { diff -r $D/bak2/Save $G/Save >/dev/null || { if ls "$D/bak2/Save"/*.axs >/dev/null 2>&1; then if ls "$D/bak2/Save"/*.axs >/dev/null 2>&1; then rm -rf "$G/Save"; cp -r "$D/bak2/Save" "$G/Save"; else echo "NO SAVE BACKUP in $D/bak2/Save: Save left as it is"; fi; else echo "NO SAVE BACKUP in $D/bak2/Save: Save left as it is"; fi; echo "  saves restored"; }; cmp -s $D/bak2/axis.cfg $G/initdata/axis.cfg || { cp -p $D/bak2/axis.cfg $G/initdata/axis.cfg; echo "  axis.cfg restored"; }; }
rm -rf $D/bak2; mkdir -p $D/bak2; cp -rp $G/Save $D/bak2/Save && cp -p $G/initdata/axis.cfg $D/bak2/axis.cfg || { echo "backup failed - stop"; exit 1; }   # (what restore puts back)
echo "== skirmish"; rm -f $G/rtrace_*; RC_EXE=$R/build/AxisRC_rtrace.exe bash $T/play_trace.sh rt2 2>&1 | grep -E 'running|EXITED|IN MATCH|CHANGED|unchanged|CRASH' | tr '\n' ' '; echo; grab skirmish; restore
eval "$(sed -n '/^declare -A S/,/^S\[replay\]/p' standalone/suite.sh)"
for n in profile mainmenu setup multi ladder armc replay; do echo "== $n"; rm -f $G/rtrace_*; RC_EXE=$R/build/AxisRC_rtrace.exe timeout 500 bash standalone/keys.sh "rt2_$n" ${S[$n]} 2>&1 | grep -E 'running|EXITED|CHANGED|unchanged|CRASH' | tr '\n' ' '; echo; grab $n; restore; done
echo "== ladder server"; rm -f $G/rtrace_*; RC_EXE=$R/build/AxisRC_rtrace.exe timeout 580 bash standalone/keys.sh lx2 0x0D 4 prof 0x49 5 main 0x4C 10 lad1 "@click 2070 1140" 2 pw 0x54 0.5 a 0x45 0.5 b 0x53 0.5 c 0x54 0.5 d 0x31 0.5 e 0x0D 4 typed "@click 1180 1445" 8 lobby 0x52 8 rank 0x1B 5 rankout 0x50 6 player 0x1B 5 playerout 0x4A 8 join 0x1B 6 joinout 0x43 8 create 0x4F 15 room - 40 inmatch 0x1B 8 left 0x0D 6 left2 0x1B 6 left3 2>&1 | grep -E 'running|EXITED|CHANGED|unchanged|CRASH' | tr '\n' ' '; echo; grab ladderserver; restore
echo "== missions"; bash $D/mis_run.sh 2>&1 | tail -4 | tr '\n' ' '; echo; for f in $D/runs/missions_*; do test -e $f && mv $f $D/runs2/; done
i=0; for ty in "DEATH MATCH" "TEAM DEATH MATCH" "KING ON THE HILL" "PLATOON MODE"; do i=$((i+1)); echo "== host $ty"; bash $D/host_run.sh h2_$i $((i * 5 % 22)) "$ty" 1 1 80 2>&1 | tail -2 | tr '\n' ' '; echo; for f in $D/runs/host-h2_$i*; do test -e $f && mv $f $D/runs2/; done; done
echo "== mp"; bash $D/mp_run.sh 2>&1 | tail -6 | tr '\n' ' '; echo; for f in $D/runs/mp_rtrace_*; do test -e $f && test $f -nt $D/all2.sh && mv $f $D/runs2/; done
echo ALL DONE
