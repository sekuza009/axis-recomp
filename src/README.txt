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

Building: ../build.sh (src/ is compiled as its own translation unit with x87 maths and linked into recomp.dll).

Adding a function
  1. Read it: the disassembly (python tools/disx.py 0xADDR), Ghidra's pseudo-C (../decomp/out/src) and the lifted
     version (lifted/grpNN.c) with its notes in recomp.c / README.txt.
  2. Write it in the subsystem's file, defined as "ret (name)(args)", using scene fields (add them to scene.fields)
     and named globals / functions (add them to game.h). Keep the original's order of calls and stores to memory
     the tests can see; write float compares so a NaN takes the original's branch; float-to-int through ftol().
  3. (hand-written C in recomp.c: python tools/hand2src.py "decl" swaps its definition for the declaration)
     (python tools/extract_hand.py out.c "header" names... copies a family of them into a new src file first)
     python tools/tosrc.py "decl;call" (switches recomp.c from the lifted wrapper to it), ../build.sh,
     bash tools/only.sh name: it must stay bit-exact on every test. coverage.txt says how much of the function
     the test reaches; a weak test should be strengthened first.
  4. python tools/srcaudit.py (every src function wired in; every patch-DLL call site inside a rebuilt function
     followed), commit; play-test (test3.sh) after a few.

Widescreen fixes carried by rebuilds: the patch DLL (axisnet) used to fix four functions from outside, by replacing
them in memory (menu_vertex, menu_drawRect) or by recognising their OpenGL calls' return addresses
(gfx_setProjection2D3D, hud_drawMain), so their rebuilds could not take over. They now do the fix's part
themselves: menu/menu_2d.c (the menu cursor over the full screen, full-screen rectangles, the menus' 4:3 box and the
HUD's 16:9 box during a match) and hud/hud_main.c (each HUD part names the screen edge it is anchored to). The patch
DLL's state comes through wide.h; the test build of the patch DLL (../axisnet_recomp.c) hands it over and reads the
HUD part. While its menu fix is on, menu_vertex works in single precision as the patch DLL's own version did.

Done so far (1108: every hand-written rebuild, and the lifted ones being rewritten - recomp.c keeps the rest): main_loop, FUN_004202d0, main_462050 | menu_processKeys, menu_44cdd0, menuState500_missionSelect,
menu_drawVersion, menu_drawCursor, profile_44c850 / 44c8c0 / 44ca90 / 44cc60,
menu_drawTexQuad_4282f0 / 4284d0 / 4285c0 / 4286b0 / 4287a0, profile_4283e0, menu_drawTexturedRect_427a90 / 427b60 / 428a00 / 428b50, menu_titleEmblemTransition,
menu_drawBackground3D (the 3D tunnel) |
edit fields (arena_editTextField_404cd0 / 404d70 / 404f90 / 405010, arena_editNumberField_404e10 / 404ed0, room_4339e0 / 433a80 /
433b00 / 433bb0 / 434020 / 4340e0 / 4341a0 / 434260 / 434320) | the arena map list (room_403490 / 4034e0 / 403530 / 403560 / 403590 /
403640), room_435ab0 / 435ce0 / 434da0 / 435f40 / 43df00 (room clicks, fade) |
the ARM CENTER mech (armc_461320 / 461370, match_4613a0, armc_set{Head,Chest,Arm,Leg,Booster}Index, armc_461510 / 461250), armc_41dfb0 / 41dfe0 / 41e010 / 41b710 / 4125c0,
armc_drawStatLabel, armc_45ddc0, the item slots (armc_40f870 / 40f950 / 40f9e0 / 40e5d0),
armc_drawPartScreen, armc_exit, armc_41b300 (the preview camera) | msg: msg_serverEndsGame / userEndsGame / connectionLost /
networkUnstable / fragLimitReached / timeLimitReached / dataLoss, msg_4629f0 (msg_print), msg_playerLeft,
msg_cheatUsed, msg_playerConnected, msg_kill, msg_chatLine, msg_playerJoinedTeam | match: scene_findTeam,
scene_teamSide | setup: setup_drawTab, setup_processTabKeys, setup_topPageKeys / soundTabKeys /
graphicTabKeys, setup_427830 / 427880 / 4278d0 | profile_41e7a0 (quit with a code), profile_44f850, profile_44b600 / 44b670 /
44b6e0 / 44f810 | devices and sound: input_reacquireKeyboard / reacquireMouse / releaseKeyboard,
wnd_401490 / 4014c0 / 467b70, sound_playMenu, dsbuf_play / setVolume, music_shutdown, gfx_swapBuffers | front-end states: menu_drawBackground, mainmenu_4434f0, menuState300_frame,
menu_443ef0 / 4440f0, mission_4479b0, mission_unlockCheat, menu_447c30 / 447b40 / 447c70 | net: arena_450bc0 (Receive), FUN_00450bf0 (Send), dplay_closeSession, arena_4539f0,
arena_453260, net_454650 / 454690 / 454740 | app: ViewVolume_dtor and the ViewVolume / Console / Stage deleting destructors,
the current directory, the message box, mci_pause | FUN_0041ef20 (rotate x, y, z), FUN_00405200, FUN_0041edc0 | sys_messageBox, match_44ac90, FUN_0043f980, menu_436940,
lobbyJoin_keys, FUN_0041ed70, mainmenu_441770, menuState600_setup | load_4014f0 / load_401540 (a key held), input_createDirectInput, load_401290
(array constructor) | match_45dd80, FUN_004050a0, match_44aee0 | the 31 rectangle hit tests and arena_404520 (menu/hit_tests.c) | armc_backupColours, armc_41ced0, armc_40ed20, armc_40e670, menu_40e6c0,
armc_40f830 | app/statics.c: 21 class-name records, 6 global object inits, 26 atexit registrations,
12 empty functions | app/classes.c: 74 class lifecycles, member clears, getters and setters | app/statics.c: 26 start-up pairs (object or
class-name record, then atexit), 18 constant colours | app/small.c: 42 one-line pieces (clears, flags, getters,
setters, list toggles, string lengths) | menu/layouts.c: the 30 screen button layouts | profile scrambling / name checks / colours, the name tables' searches
(load/names.c), weapon cycling (match/weapons.c), map stepping, the sliding panels | the store-table initialisers
(app/store_tables.c, 9), the depth sorts (render/depth_sort.c), the glyph quads (text/glyph_quads.c, 8) | the front end's records, list paging and resets (menu/menu_records.c, menu/menu_init.c, app/resets.c), room dialogs
(menu/room_dialogs.c), setup tabs, menu cameras (menu/menu_cameras.c), ARM CENTER part info (menu/armc_parts.c), font cell tables
(text/glyph_cells.c), PTX video tables (app/ptx_tables.c), actor slots and pools (match/actor_slots.c), HUD notices
(match/notices.c), map objects (match/map_objects.c), shape tints (render/shape_colours.c), session tables and merges
(net/net_tables.c, net/net_sessions.c), scrambled file blocks (load/files.c), frees (app/frees.c) | net: the DirectPlay slots (arena_454940 .. 454d60, 20) and
arena_453770 | text_draw5 / 8 / 16 / 32,
text_draw8b, text_drawBox16, hud_403210, hud_402db0, text_drawSized, hud_44ae10 (text/ complete) | hud_pass,
hud_drawRanking, hud_drawLockOn, hud_496240, hud_4950a0, hud_46bd00, hud_drawFps, hud_4953d0, hud_4955a0,
hud_drawPressFire, hud_drawReadyStart, hud_drawClock,
hud_drawMatchResult, hud_drawRecordIndicator, hud_drawNameIcon, hud_drawLeaderIcon,
hud_drawEscMenu, hud_495ed0,
hud_drawPlayerMarkers, hud_drawMain, replay_drawIcon | hud_472900 (fog), hud_490b30, hud_490da0, hud_45e170, hud_479af0, hud_48f970 (objects, actors, projectiles, items to the view volume), data_46f7a0, hud_46fd20 (object lists), hud_496f20 (the sky) | replay_drawMessage, replay_drawFollowedName | menu_vertex, menu_drawRect, gfx_setProjection2D3D
(menu/menu_2d.c) | the ARM CENTER colour sliders (menu/armc_colours.c), rotations, the 2D turn, angle wrap,
triangle normal and point transform (render/rotations.c), the collision space's pools (load/space_pools.c), the
no-CD stubs and small methods (app/small.c), the lobby's and room's screens (menu/lobby_states.c), player name and
team, weapon selection, the volume, cheat codes, the PTX video decoder (app/ptx_decode.c), Johab syllables and chat
line widths (text/text_codes.c), the session sort, the follow target, the free menu camera's moves, address strings, object animation,
the texture tints and RGB <-> HSV (render/tex_colours.c), actor / bullet slots freed and player records
reset, the screens' set-ups (menu/screen_enter.c), key bindings, the setup camera, shape bounds and bullet trails
(render/trails.c), the view volume's lists and object transform (render/view_volume.c), collision triangles,
their trace and the triangle / box test (load/collision_tris.c), quaternion <-> axis-angle / matrix, the PTX inverse
DCT, the stage's mesh records, the ARM CENTER's stats and part panels, the intro camera path | the clock (app/timer.c: timer_init,
intro_41e730), ptx_error, net_454560, net_452d70, match_4620e0 (match/scores.c), the skirmish list keys and briefing
(menu/skirmish.c), the map-select keys (the held-key repeat in menu/key_repeat.h), the loading screen (app/loading.c),
sound_loadWav, glWindow_init, the ARM CENTER's frame, entry, previews and keys (menu/armc_misc.c, menu/armc_keys.c) |
setup_controlTabKeys, menu_frame (app/main_loop.c), net_connect, the pilot's campaign file (load/files.c: profile_save opens or
makes it, profile_load starts a new one, profile_saveProgress), the part panels and mech tints, profile_44de00, loading_draw.
| the start-up screens (menuState100_intro, intro_41f100), the display mode switch and restore, reg_writeCharacterSettings,
the profile screen's frame and panels, room_434820, the server login dialog, the briefing window, the PTX reader
(ptx_open / ptx_decode), net_sendLocalInfo.
Left lifted on purpose for now: armc_buildPartLists and app_init (they run into patch-DLL code mid-function).
