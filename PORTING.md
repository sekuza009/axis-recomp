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
4. **The host drives the frame.** The game's own WinMain loop becomes `axis_init` / `axis_frame(dt, input)` /
   `axis_shutdown`; a small Windows host (`host/win32`) calls them, so the library has no message loop of its own.
5. **Library build.** `axis.dll` (or a static library) with that API, plus the Windows host exe; play-tested against
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
