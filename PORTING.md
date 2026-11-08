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
2. **No original-program plumbing.** The test harness (`recomp.c`, AXIS_DIRECT without AXIS_NATIVE), the patch layer
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
