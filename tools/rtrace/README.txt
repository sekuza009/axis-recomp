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

Second round (2026-11-06): gen.py follows pointers typed with a record (two levels, each record once a pass:
models, skeletons, the collision space, texture slots) and walks derived arrays (g_rankingRows ...); a 3 ms
pass samples Scene's small fields (one-frame input flags). build.sh links a test copy of menu_records.c
(menu_records_test.c: the SKIRMISH entry opens the unused mission list, screen 900, when AXISRC_MISSIONS is
set - make it from src/menu/menu_records.c by replacing the menuState500_enterSkirmish() call in the main
menu's action). mis_run.sh plays the mission list with a hand-made axis.mis (removed after); all2.sh runs
every session. The Ladder screens need DServer/axis_server.py running with --accounts on a scratch copy
(the password the game sends is lower case). 2304 of 3036 fields / globals seen non-zero.

Third round (2026-11-06): scripted sessions for the paths no earlier session reached. The menus' pointer
follows relative mouse motion only (about 0.756 of it in the half-size screenshot's pixels) and a click acts
where the pointer is: ui_lib.sh's goto / clk / at (clickhere.ps1 clicks without moving), typ / key, and
start_game / end_game (saves, axis.cfg and axisnet.ini backed up BEFORE anything is changed, put back after).
  sessA.sh  a hosted arena: the free camera's keys, the remaining controls, the chat cheat codes, the Esc
            menu, the time limit running out
  sessB.sh  the Ladder forms (local DServer, seeded accounts): new ID (O, then click the confirmation's OK),
            the account page, the ranking's pages and sorts, the create-room form
  sessC.sh  the arena create form, the player name, ARM CENTER entered from the player page
  sessD.sh  every shoulder item cycled in ARM CENTER (the extra items' flags and bonuses)
  sessE.sh  the setup screens: a key rebound, the mouse tab, sound and graphics toggles (ACCEPT)
  mp_loss.sh the two-copy game with each copy suspended 5 s (suspend.ps1): no packet was lost (DirectPlay
            delivers them late), so the skipped-packet path stays unreached
The fast pass also samples the local player's small fields (its one-frame inputs). 2386 of 3036 seen.

Fourth round (2026-11-07, the deep name audit): gen.py's COUNTED table follows pointers whose length is another
field of the record (Model.parts, ShapePart.prims, Skeleton.bones, Bone.posKeys / rotKeys, ViewVolume.quads, the
managers' items and name nodes) and the collision space's four pools (rt_follow_n; up to 4 levels deep). One hosted
DEATH MATCH with it: 66 names never seen before seen non-zero (tools/names/audit2026-11-07/data_deep_newly_seen.txt).
