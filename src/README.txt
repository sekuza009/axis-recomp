src/ - AxisGL.exe rebuilt as readable C (PRIVATE; never ship)

Every function here replaces one function of the game and is checked bit-exact against the original by the recomp
harness (../recomp.c runs the same random tests on both and compares memory, call logs and results), then played
in the game (../test3.sh). Each function's comment gives its original address.

Layout (by subsystem)
  axis.h        conventions: calling conventions, ftol, how game functions / imports / globals are reached
  game.h        the game's functions, globals and imports at their original addresses, by name
  wide.h/.c     the patch DLL's widescreen state, for the rebuilds that carry its fixes (below)
  scene.fields  the scene object's known fields -> scene.h (tools/mkscene.py; offsets checked when building)
  app/          the main loop
  menu/         the front end: key dispatch, screens, the profile screen's pages, textured quads (buttons, panels)
  text/         the bitmap fonts: the text passes, sizes
  hud/          the in-match HUD: overlays, the team box, lock-on marks
  replay/       the message box (match and replay)
  net/          DirectPlay (the arena's connection slots, Receive / Send) and the game's own server list
  msg/          the match's messages
  match/        the match's rules: teams, weapon cycling
  load/         loading: name lookups
  sound/        DirectSound buffers, the menu sounds
  render/       the stage (scene.fields: Stage, the scene's own object at +0x1f36c8): fog, the lists drawn each pass, the sky
  crt/          the game's C runtime where msvcrt.dll's differs from it (the standalone build): printf, atof

Building: ../build.sh (src/ is compiled as its own translation unit with x87 maths and linked into recomp.dll).

Standalone build: ../standalone/build.sh (after ../build.sh) links the same objects into build/AxisRC.exe, the
game as a program of its own: no injection, no change to the installed exe. Put it in the game folder and run it;
it reads AxisGL.exe there as data and does the loader's work itself (standalone/main.c): the game's sections at
0x400000 (inside AxisRC.exe's own .bss), its imports, the patch layer (../axisnet_recomp.c compiled in with
AXIS_STANDALONE), every rebuilt function switched in at its original's address (the table is generated from
recomp.c by tools/mkhooks.py), the x87 control word Windows gives the game (0x027f; MinGW's start-up left 0x037f),
then the game's own start-up. Every game function is rebuilt (also the packet layer after the runtime, 0x4a8300 ..);
the ones the patch layer or the installed exe's patches change carry those changes (wide.h, wide_carries).
The game's C runtime (Visual C++ 6, 0x49e000 ..) is replaced too (standalone/crt.c): its entries the rebuilds use
jump to msvcrt.dll's, its start-up is done in C (the C++ static constructors from the table at 0x4ad000, WinMain,
exit), and crt/ makes the two results that differ come out as VC6's: printf's -0.0 and signalling NaNs
(crt_format.c), and atof's rounding (crt_atof.c: VC6's 96-bit conversion rebuilt). recomp.c's "C runtime" tests
compare each with the game's own (AXISRC_GAMECRT=1 keeps the game's runtime). AxisGL.exe is not read at all: its
data is built into AxisRC.exe (build/gamedata.bin, tools/mkgamedata.py: the header, .rdata, the initialised .data,
and of .text only the bytes something reads: dinput's object formats, the call sites rebuilds follow and the
instructions the patch layer checks; AXISRC_IMAGE=1 maps the exe file instead, to compare). The compiler's jump
stubs that data points at are entries of their rebuilt function (tools/mkhooks.py), and rebuilds call imports
through their slots, not the game's jump stubs. AXISRC_POISON=1 checks this: every byte of the game's functions and runtime, except their entry jumps (and the
code bytes rebuilds read, tools/mkhooks.py), becomes int3, so any original code reached stops the game at its
address (logged). Data inside .text stays (the DirectInput object formats at 0x44f950 are read by dinput).
standalone.log (next to the exe) lists every function; RECOMP_SKIP=name,... keeps some on the original.
standalone/play.sh is the play test.

Changing a function
  1. Read it: the disassembly (python tools/disx.py 0xADDR) and Ghidra's pseudo-C (../decomp/out/src) for what the
     original does; its comment here gives its address.
  2. Edit it in its subsystem's file, using scene fields (add them to scene.fields) and named globals / functions
     (globals.h, game.h). Keep the original's order of calls and stores to memory the tests can see; write float
     compares so a NaN takes the original's branch; float-to-int through ftol().
  3. ../build.sh, then its state tests: RECOMP_ONLY=name,... bash ../test3.sh - every test bit-exact (the five
     functions that carry the patch DLL's fixes never are: menu_vertex, menu_drawRect, input_justPressed,
     input_updateMenuCursor, armc_rotateFromCursor). coverage.txt says how much of a function its test reaches.
  4. python tools/srcaudit.py (every function wired in, every patch-DLL call site followed), commit; then
     bash standalone/build.sh and bash standalone/check3.sh <prefix> (the three builds played: menus, a match,
     a hosted TCP game).

Widescreen fixes carried by rebuilds: the patch DLL (axisnet) used to fix four functions from outside, by replacing
them in memory (menu_vertex, menu_drawRect) or by recognising their OpenGL calls' return addresses
(gfx_setProjection2D3D, hud_drawMain), so their rebuilds could not take over. They now do the fix's part
themselves: menu/menu_2d.c (the menu cursor over the full screen, full-screen rectangles, the menus' 4:3 box and the
HUD's 16:9 box during a match) and hud/hud_main.c (each HUD part names the screen edge it is anchored to). The patch
DLL's state comes through wide.h; the test build of the patch DLL (../axisnet_recomp.c) hands it over and reads the
HUD part. While its menu fix is on, menu_vertex works in single precision as the patch DLL's own version did.

Status: every game function is rebuilt here (all 1368 hooked; the packet layer after the runtime too). recomp.c is
only the test harness: nothing is lifted any more.

Readable C: the conventions
  Records     src/scene.fields -> scene.h (tools/mkscene.py): packed structs at the game's offsets, every field's
              offset and size checked by a _Static_assert; anonymous unions allowed where the game keeps two views
              of the same bytes (Projectile: fade / trailPoints). Fields are named by use; "(unclear)", "(by use)"
              and names like valueE8 / cleared2340ca4 / unusedBe2ffc mark what is not understood yet. Scene fields
              over the Stage region (Scene + 0x1f36c8) alias Stage fields: look at both views before calling a
              field unused. Indexing past a field is undefined behaviour: use an array field or a byte offset
              ((u8 *)p + offsetof(T, f)).
  Objects     objects.h: the arrays and records at fixed addresses (g_sessionList, g_profileRecords ...).
              tools/names/objects.txt may give a scene.fields record as the type ("0xa05330 RankedPlayer 11
              g_netPlayerList"); run python tools/mkdatasrc.py after editing it (the standalone build's layout).
  Globals     globals.h: every fixed-address global by name; the game's float constants by value (k_1f, k_0_5f,
              k_1500f_4a9700 when the value's name is taken), used as &k_1f.
  Calls       by name through game.h / calls.h; *_bits variants pass floats as their bits (the original passes
              them as integers). An inline GAME_FN / IMPORT is left only where a name would be wrong: an OpenGL
              import whose eax the caller returns, a function the same file rebuilds (a direct call skips the
              harness's mock at the original address), an argument-count mismatch kept from the original.
  Pointers    a byte pointer used through one struct gets that type, or a typed alias (Stage *st = (Stage *)s);
              u32 * locals indexed as words stay.
  GAME_VAR    left in the helpers that take a global's address from a table of addresses (clears, copies, saves of
              groups of globals): the original's pattern.

The tools that did it (each keeps the code the same; check: python tools/objcmp.py base build/obj, the base from a
fresh ../build.sh of the commit before; where an object differs, the harness state tests:
RECOMP_ONLY=<the files' functions> bash ../test3.sh, all bit-exact; then bash standalone/check3.sh <prefix>)
  scene_fields.py, struct_fields.py, struct_elems.py, field_ptrs.py, field_addrs.py, offset_names.py
                      offsets -> struct fields (scene, stage, records; nested arrays; offset tables -> offsetof)
  retype_field.py, plain_writes.py   field types and stores
  plain_calls.py      inline game calls -> name(args) (calls.h generated)
  widen_returns.py    a void macro takes the return type its callers read
  compatible_calls.py calls that differ from their macro only in 4-byte ints / void * / an int-cast return
  drop_local_macros.py, drop_unused_macros.py   a file's copies of header macros, and macros nothing uses
  retype_locals.py    byte-pointer locals -> struct pointers (--alias=Type:name --min=N for typed aliases)
  reuse_aliases.py    casts that repeat a function's typed alias use the alias
  index_objects.py    GAME_VAR(T, OBJ(arr) + i * size) -> arr[i]
  name_constants.py   K(0x4a....) float constants -> &k_<value>f
  float_stores.py     BITS(x) = 0x43960000; -> x = 300.0f; (where the decimal rounds back to the same bits)

Traps met (see the commits for the stories)
  - zig's cache hides a cached file's warnings: check warnings with an extra -D on the compile line.
  - standalone/build.sh can leave build/obj other than build.sh's: take objcmp's base from a fresh build.sh.
  - RECOMP_ONLY takes a list of up to 32 KB (longer ran every test). Never wrap test3.sh in timeout: it is killed
    before it restores AxisGL.exe and leaves a hung game holding recomp.log.
  - A rewrite of address arithmetic must respect precedence: "0x14 - k * 4" is not "(0x14 - k) * 4" (a state test
    crashed on it). A rewrite of float bits as a float literal converts the value if the target is really an int:
    objcmp and the state tests catch both.
  - Dropping a local macro's #undef can also drop the clearing of a header macro of the same name.
