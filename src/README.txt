src/ - AxisGL.exe rebuilt as readable C (PRIVATE; never ship)

Every function here replaces one function of the game and is checked bit-exact against the original by the recomp
harness (../recomp.c runs the same random tests on both and compares memory, call logs and results), then played
in the game (../test3.sh). Each function's comment gives its original address.

Layout (by subsystem)
  axis.h        conventions: calling conventions, ftol, how game functions / imports / globals are reached
  game.h        the game's functions, globals and imports at their original addresses, by name
  scene.fields  the scene object's known fields -> scene.h (tools/mkscene.py; offsets checked when building)
  app/          the main loop
  menu/         the front end: key dispatch, screens, the profile screen's pages
  text/         the bitmap fonts: the text passes, sizes
  hud/          the in-match HUD: overlays, the team box, lock-on marks
  replay/       the message box (match and replay)

Building: ../build.sh (src/ is compiled as its own translation unit with x87 maths and linked into recomp.dll).

Adding a function
  1. Read it: the disassembly (python tools/disx.py 0xADDR), Ghidra's pseudo-C (../decomp/out/src) and the lifted
     version (lifted/grpNN.c) with its notes in recomp.c / README.txt.
  2. Write it in the subsystem's file, defined as "ret (name)(args)", using scene fields (add them to scene.fields)
     and named globals / functions (add them to game.h). Keep the original's order of calls and stores to memory
     the tests can see; write float compares so a NaN takes the original's branch; float-to-int through ftol().
  3. python tools/tosrc.py "decl;call" (switches recomp.c from the lifted wrapper to it), ../build.sh,
     bash tools/only.sh name: it must stay bit-exact on every test. coverage.txt says how much of the function
     the test reaches; a weak test should be strengthened first.
  4. Commit; play-test (test3.sh) after a few.

Done so far (43): main_loop, FUN_004202d0, main_462050 | menu_processKeys, menu_44cdd0, menuState500_missionSelect,
menu_drawVersion, menu_drawCursor, profile_44c850 / 44c8c0 / 44ca90 / 44cc60 | text_draw5 / 8 / 16 / 32,
text_draw8b, text_drawBox16, hud_403210, hud_402db0, text_drawSized, hud_44ae10 (text/ complete) | hud_pass,
hud_drawRanking, hud_drawLockOn, hud_496240, hud_4950a0, hud_46bd00, hud_drawFps, hud_4953d0, hud_4955a0,
hud_drawPressFire, hud_drawReadyStart, hud_drawClock,
hud_drawMatchResult, hud_drawRecordIndicator, hud_drawNameIcon, hud_drawLeaderIcon,
hud_drawEscMenu, hud_495ed0 | replay_drawMessage, replay_drawFollowedName.
