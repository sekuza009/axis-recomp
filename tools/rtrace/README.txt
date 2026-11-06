Range trace (test only): AxisRC with a sampler that records, every 250 ms, the observed values of every scene.fields
field (each instance reachable from the scene, the texture banks and the objects), every globals.h global and every
objects.h object, to Axis\rtrace_<pid>.tsv (min / max, up to 16 distinct values, NaN / denormal / float-bit counts,
pointer validity, string termination).
  gen.py       generates rt_walk.c (the walker) from scene.fields, globals.h, objects.h
  rtrace.c/.h  the sampler thread (snapshots the scene before walking it)
  build.sh     builds build/AxisRC_rtrace.exe from the standalone objects (run standalone/build.sh first)
  run_suite.sh standalone/suite.sh's scenarios with it; host_run.sh a host-only arena (map, game type);
               mp_run.sh a host + joined client on one PC (AXISRC_MULTI)
  analyze.py   merges runs and checks names / types against what was seen (flags 0/1, counts >= 0, float bits in
               ints, denormals in floats, NaN, bad pointers, strings, "stays 0" claims, comment ranges)
  review.py    one line per exercised field (name | declaration | observed | comment) for reading against the code
The scripts carry the scratchpad paths they were run from (D=...): set D to a working folder before reuse.
First run 2026-11-06: 21 sessions, 2135 of 3023 fields / globals exercised.
