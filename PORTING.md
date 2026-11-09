# The portable branch

Goal: the rebuilt game as a platform-independent C library that a host (first a plain Windows host, then Godot on its
own `godot` branch) drives frame by frame. Decided 2026-11-08:

- Windows first: the library stays 32-bit x86 at first (Godot exports 32-bit Windows); the 64-bit pass (Linux,
  Steam Deck, Mac) comes later.
- No crossplay with AxisGL / AxisRC: the port may change netcode and maths. `master` stays the bit-exact reference
  (tools/objcmp.py, the harness), used to check behaviour.
- A full release with the game's assets is the aim - only with a licence from the rights holder. Code and asset
  handling are kept apart so the engine-only route (players' own game files) stays open.

`python tools/port_scan.py` counts what still ties src/ to Windows, x86 and the original's layout.

## Stages

1. **No fixed addresses.** *(done 2026-11-08: PORTABLE=1 / PORTABLE=2 builds, below)* AxisRC.exe is linked at 0x10000 with ASLR off and the original's range reserved as a guard;
   the data lives in one block at the original's offsets (g_data / g_rdata, IMG()). A DLL is loaded anywhere: the
   image-range guard and the fixed link become optional (a debug build keeps them), and the data block is reached only
   through its symbols.
2. **No original-program plumbing.** *(done 2026-11-08: standalone/portable.c, below)* The test harness (`recomp.c`, AXIS_DIRECT without AXIS_NATIVE), the patch layer
   (`src/wide.c`, PATCHED_ / SITE_ call sites, code_matches), the per-function entry jumps and gamedata.bin's code
   bytes are not part of the portable build (they stay on master).
3. **A platform interface.** Every OS / graphics / sound / input / network call goes through `src/plat/plat.h`
   (window, timer, files, input, audio, rendering, sockets, sessions); `plat/win32/` implements it with today's
   calls (OpenGL 1.x, DirectInput, DirectSound, Winsock, DirectPlay via axisnet). The 211 IMPORT_FN and 68 COM call
   sites move behind it.
4. **The host drives the frame.** *(first pass done 2026-11-08: src/axis_api.h, below)* The game's own WinMain loop becomes `axis_init` / `axis_frame(dt, input)` /
   `axis_shutdown`; a small Windows host (`host/win32`) calls them, so the library has no message loop of its own.
5. **Library build.** *(first pass done 2026-11-08: PORTABLE=3, below)* `axis.dll` (or a static library) with that API, plus the Windows host exe; play-tested against
   master's behaviour (the scripted sessions, replays).
6. **Later: 64-bit.** Pointers kept in 32-bit fields (u32 addresses in records and tables, ADDR / OBJ), the x87
   helpers, stdcall / thiscall, the inline assembly.

The `godot` branch starts from stage 5: a GDExtension calling the same API, the drawing first recorded and replayed
in Godot, then replaced piece by piece.

## Progress

- 2026-11-08, stage 1: `RELOC()` maps only compile-time constants in the portable build (src/data already writes
  every pointer through `IMG()`). `PORTABLE=1 bash standalone/build.sh` (build/AxisRC_portable.exe) keeps the
  original's range guarded: the skirmish, setup, profile, hosted-arena, two-copy, menu-tour and quit sessions ran
  with no original address used. `PORTABLE=2` (build/AxisRC_reloc.exe) makes the image an ordinary array and links
  with ASLR and relocations: loaded at 0x90000 (image at 0x19b000) it played the skirmish session. Next: stage 2.
- 2026-11-08, stage 2: the portable builds use their own loader, `standalone/portable.c`, in place of main.c. Nothing
  of AxisGL.exe is built in any more: no gamedata.bin (header bytes), no hook table or jumps at the original functions'
  entries, no jumps for the C runtime - its 38 entries are a table (`g_crtFn`, `CRT_FN(name)` in src/axis.h, filled by
  standalone/crt.c; the list is `CRT_ENTRIES` in crt_addrs.h, tools/mkcrt.py). The 228 imports are filled by name
  from `src/import_list.h` (tools/mkimportlist.py, from imports.h), and the network layer hooks its slots by name
  (axisnet_recomp.c's hook_import_ex with AXIS_PORTABLE). Of g_image only text_data's pages (DirectInput's object
  formats) stay accessible; any other use is logged and stops the game. The patch layer's call sites (PATCHED_ /
  SITE_, src/wide.c) already compile out of native builds; they stay in src/ for master.
- 2026-11-08, stage 3 (first pass): `src/plat/plat.h`. The 68 COM call sites (sound, music, input, network) are
  named operations (`SND_PLAY(buffer, flags)`, `IN_READ(device, size, state)`, `NET_SEND(...)`...): on master the
  same call as before (the harness objects are unchanged), in the portable build `plat_*` functions,
  src/plat/win32/devices.c. Every plain system call (OpenGL, window, timers, registry, sockets: the 228 imports) is
  `plat_<name>` in the portable build (src/axis.h IMPORT_FN), the Windows platform's being jumps through the import
  slots (build/plat_imports.s). Still Windows-shaped (DirectSound buffers, OpenGL 1.x calls, Win32 messages): the
  next passes group the window / message loop (stage 4) and give rendering, input and sound neutral shapes.
- 2026-11-08, stage 4 (first pass): `src/axis_api.h` - `axis_init` (the original WinMain's start-up: in the portable
  build src/app/win32.c's game_WinMain is compiled as axis_init and returns before its loop), `axis_frame` (the
  loop's body: typed text read, app_frame), `axis_running`, `axis_textInput`, `axis_shutdown`. The Windows host's
  loop (standalone/portable.c host_run) pumps the messages and calls axis_frame. The game still owns its window and
  ends the process itself on quitting (stage 5). Sessions: all seven passed.
  Correction: the two-copy session (mp1) needs AXISRC_MULTI, which only the trace builds honoured, so in the
  stage 1-3 runs above its second copy stopped at the "already running" check and the session tested nothing.
  portable.c now honours AXISRC_MULTI too; with it the stage-4 build played the two-copy team match (both
  players in, chat across).
- 2026-11-08, stage 5 (first pass): `PORTABLE=3 bash standalone/build.sh` builds `build/axis.dll` (the game, with its
  data, C runtime table, platform layer and network layer; relocatable, ASLR) and `build/AxisHost.exe`
  (host/win32/main.c: nothing of the game - it loads axis.dll from the game folder and calls `axis_load`,
  `axis_init`, then pumps messages and calls `axis_frame` until the game stops). axis.dll exports only the API of
  src/axis_api.h. Still to do for a clean library: the game creates its own window and GL context, and its logs go to the game
  folder as AxisRC's did.
- 2026-11-08, quitting hands back to the host: in the portable builds the window procedure's ExitProcess calls are
  `axis_ended(code)` (the frames stop; each was followed by the procedure's return, which now runs) and
  `axis_exit` returns the code to the host, the game's exit list not run (as the original ended there).
  `axis_frame` runs no frame once stopped. The quit, profile and skirmish sessions with axis.dll: "the game quit
  (code 0): back to the host", the host then ending itself.
- 2026-11-08, rendering seam, step 1 - the GL state the game reads back (standalone/glstate.c, AXIS_GLSTATE).
  The game uses OpenGL's matrix stack as maths, not only for drawing: it reads the modelview matrix back for actor
  body matrices, collision, weapons' aiming (gluLookAt) and the view volume (16 call sites), and asks for the
  projection, viewport and fog. A platform without OpenGL must answer those itself; glstate.c keeps that state in
  software (matrix stacks, gluLookAt / gluPerspective / gluOrtho2D, viewport, fog), in front of the GL slots.
  AXIS_GLSTATE=1 compares every answer with the driver's (glstate.log); =2 gives the game the software answers.
  Measured over a skirmish (NVIDIA RTX 3080, driver 617.42): projection, viewport and fog exact in every query;
  modelview 70% bit-exact (1.75 of 2.52 million), the rest within ~1e-7 relative. The driver's rotation: sine and
  cosine in double from the angle times pi/180 held as a float (found from the logged calls, tools/glprobe); axis-
  aligned unit rotations built directly (exact); other axes normalised with an approximate reciprocal square root
  close to - but not exactly - the 0x5f3759df trick with two Newton steps (tools/glprobe/fitc.c). Not pursued
  further: the original game's own maths already depends on the player's GPU driver in those last bits (an AMD or
  Intel driver rounds differently), so a port only has to stay that close.
- 2026-11-08, rendering seam, step 2 - the drawing recorded and proved complete (standalone/glrec.c, AXIS_GLREC=1).
  Every GL / GLU call is still executed and also appended to a command stream, with the data behind its pointers
  copied in (matrices, vectors, the vertex arrays each glDrawElements reads, texture pixels), so the stream stands
  alone; queries are not recorded. At each SwapBuffers the stream is replayed into a second, hidden GL context
  drawing into its own window's back buffer, and every 30th frame both images are compared pixel for pixel
  (glrec.log). Two things had to be found: the fixes' pixel-sharp text (standalone/platform.c) set texture filters
  with glTexParameteri outside the import slots (now routed so a layer can see it - a platform port must take it
  over too); and a framebuffer object rounds sample positions differently from a window's buffer, so the replay
  draws into a window as the game does. Result over the seven sessions: 5,551 frames compared, all identical.
- 2026-11-08, AXIS_GLREC_DUMP=<file> (with AXIS_GLREC): the stream written to a file for a replayer elsewhere -
  "AXGLREC1", the plain calls' table, then per frame its window size and words (format: standalone/glrec.c). The
  skirmish session's first 2,000 frames (title, menus): 114 MB, the first frame 8.6 MB (the texture uploads), then
  a median of ~32 KB a frame at 3840 x 2161.
- 2026-11-08, Godot set up (outside the repo): Godot 4.7.2 stable, 32-bit editor (SHA-512 checked) and godot-cpp
  4.5 in C:/Users/Alexander/Tools/godot; godot-cpp builds for x86_32 with zig through small launcher exes named as
  MinGW tools (zig-mingw/launcher.c; SHOBJSUFFIX .o, as zig needs). The 32-bit editor loads its test extension and
  registers its class, but the test fails: no engine class has its instance-binding callbacks ("Cannot find instance
  binding callbacks for class 'Object'"), with the 4.5 and the 4.7 API alike. Not yet understood - the next thing
  to settle before the godot branch builds on godot-cpp (a C extension on gdextension_interface.h is the fallback).
