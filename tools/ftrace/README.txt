Function trace (test only): build/AxisRC_ftrace.exe = src/ compiled with -finstrument-functions + ftrace.c, which
counts every rebuilt function's calls with the screens / match states it ran in (g_screen, matchState) and its
callers, written every 3 s to Axis\ftrace_<pid>.tsv (names from the PDB through dbghelp).
  build.sh   builds it (after standalone/build.sh); the mission-list test hook (AXISRC_MISSIONS) as rtrace's
  merge.py   merges runs into one line per src function (or NOT RUN), the evidence for the name audit
Sessions: the rtrace session scripts (tools/rtrace) with the exe and file names swapped.
First use 2026-11-07: the name audit (tools/names/audit2026-11-07): 1460 of 2030 functions seen running.
