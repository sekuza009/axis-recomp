# The godot branch

The rebuilt game on Godot 4 (PORTING.md). Windows first, 32-bit (the game library is x86 for now), Godot 4.7.

## What is here

- `extension/` - the GDExtension (C++, godot-cpp). `AxisReplay` plays a recorded stream of the game's drawing
  (an `AXGLREC1` file from the portable build: `AXIS_GLREC=1 AXIS_GLREC_DUMP=<file>`, standalone/glrec.c):
  `gl_emu.cpp` runs the recorded OpenGL 1.x calls on the CPU - matrix stacks, current colour and texture
  coordinate, caps, blending, depth, culling, fog, textures (gluBuild2DMipmaps' scaling and mip chain) - into
  ordered clears and draw batches in clip space; `axis_replay.cpp` executes them with Godot's RenderingDevice
  (one fixed-function shader: texture x colour by the texture environment, then fog; a pipeline per state) into a
  texture. `test/emu_test.cpp` runs gl_emu on the console.
- `extension/src/axis_game.cpp` - `AxisGame`, the game itself in Godot: axis.dll (the portable branch's
  `PORTABLE=3` build, copied to `project/bin/axis.dll`) loaded in-process with the game folder as AXIS_GAME_DIR,
  run frame by frame from `_process` (axis_api.h). Its drawing comes back each frame as a command stream (the
  host's frame callback) for the same renderer; Godot's keys (as DirectInput codes), mouse (captured: relative
  movement, buttons, wheel), focus and typed text are its input. The game's own window is created but kept hidden;
  its timer and socket messages still arrive through Godot's message loop, its sound plays with Godot's window.
  `host_win.c` holds the Windows calls (loading the DLL) apart from godot-cpp.
- `extension/src/axis_launcher.cpp`, `axis_movie.cpp` - `AxisLauncher` (the game's settings, the system's language)
  and `AxisMovie` (the game's movies decoded: standalone/avimovie.c with FFmpeg's indeo3 from ../axisnet/iv32) for
  the launcher (below).
- `project/` - the Godot project: `launcher.tscn` (the main scene: the launcher, below), `game.tscn` (the game),
  `main.tscn` shows the replay full-window. Command line after `--`:
  `<file.glrec> [--fps N] [--shot frame:file.png ...] [--quit-after N]`.

Run the game: `Godot --path project res://game.tscn -- --game-dir <the Axis folder>` (`--shot frame:file.png`,
`--quit-after N` for checks). The replay: `res://main.tscn -- <file.glrec>`.

## The launcher

`project/launcher.tscn` (the main scene) is AxisPlay.exe rewritten from its decompiled code (Ghidra; the
addresses in `launcher.gd` are AxisPlay.exe's). It keeps the original's look and behaviour:
- the 642 x 482 bordered window centred on the screen (drawn at that size, scaled to the screen's DPI), the
  background `Launcher\Resource\BackGround\MainBK.bmp`, eight buttons with their four pictures (normal, lit,
  pressed, grey) read from **the user's own AxisPlay.exe** (`pe_resources.gd`: its bitmaps, icon IDI_LAUNCHER and
  cursor CURSOR2), `Launcher\lsound\mmove.wav` when the pointer lights a button, `mclick.wav` on a press (which acts
  at once, as the original's);
- installed (MathFunc.tbl in the game folder): Install Game grey, the rest live; otherwise only Install Game, Help,
  Install DirectX and Quit;
- Play Game: a server chosen first (the server dialog), a render mode chosen (Video Setup), StartMode 1, then the
  game - `game.tscn` in the same program instead of AxisGL.exe;
- the dialogs as the original's templates (`launcher_ui.gd`, `launcher_dialog.gd`: classic grey dialogs in dialog
  units): Cinematics (Opening `interface.sra`; Ending `battle.sra` once EndMode is set - the movies decoded by
  `AxisMovie`, standalone/avimovie.c, full screen with their sound, Esc skips), Help (the readme in Notepad / the
  default editor, www.axisarena.net), Change Server (`Launcher\ServerList.dat` into
  `HKCU\SOFTWARE\AxisArena\SelectServer`; List Update runs GetList.exe), Video Setup;
- the settings under `HKCU\SOFTWARE\AxisArena` (`AxisLauncher`: the registry on Windows, the library's own text
  file elsewhere - src/plat/posix/registry.c - so the launcher and the game share them), the defaults the original
  writes at its start; the English or Korean texts by the system's language.

Differences: Video Setup's Direct3D, Savage and GLSetup choices are grey (this version has one renderer); Install
DirectX is grey off Windows (it runs DirectX 7's installer, after asking); Install Game runs
`Launcher\AxisInstall\Setup.exe` only where it exists. `--play` (after `--`) skips the launcher - the game's own
restart after a graphics change passes it, as the original game started AxisGL.exe itself. AxisRC.exe keeps the
original AxisPlay.exe.

## Building (Windows, zig as the compiler)

Set up once (outside the repo, C:/Users/Alexander/Tools/godot): Godot 4.7.2 (32-bit editor), godot-cpp (branch 4.5)
built against Godot 4.7's API (`--dump-extension-api`), SCons (`pip install scons`), and `zig-mingw/bin`: small
launchers named as MinGW tools that run zig (godot-cpp's MinGW cross mode needs them). Then, in `extension/`:

    python -m SCons platform=windows arch=x86_32 use_mingw=yes use_llvm=yes mingw_prefix=<zig-mingw> \
        target=template_debug use_static_cpp=no debug_symbols=yes custom_api_file=<extension_api.json> -j8

`debug_symbols=yes` matters: zig's linker drops a DLL's static constructors when it strips (`-s`), and godot-cpp
registers the engine classes from static constructors - without them every engine object fails ("Cannot find
instance binding callbacks for class 'Object'"). godot-cpp's own test suite passes this way (131 / 131).

Import the project once (`Godot --path project --headless --import`), then run it.

**64-bit (2026-11-09).** The official 64-bit editor (`Tools/godot/editor64`, Godot_v4.7.2-stable_win64) runs the
project directly - no large-address-aware copy needed. It needs:
- the game library `bin/axis64.dll` (`bash standalone/build64.sh windows`, then copy build/axis64.dll here; game.gd
  picks axis64.dll or axis.dll by Godot's architecture);
- the extension for x86_64, built against a godot-cpp of its own (`Tools/godot/godot-cpp64`: godot-cpp's generated
  bindings bake in the type sizes of the architecture they were made for, so the 32-bit checkout's cannot serve):

      GODOT_CPP=C:/Users/Alexander/Tools/godot/godot-cpp64 python -m SCons platform=windows arch=x86_64 use_mingw=yes           use_llvm=yes mingw_prefix=<zig-mingw> target=template_debug use_static_cpp=no debug_symbols=yes           custom_api_file=<extension_api.json> generate_bindings=yes -j8

  (the zig-mingw launchers named x86_64-w64-mingw32-<tool>.exe pick the 64-bit target from their name);
- for an export, `bash godot/export.sh release install 64` (the "Windows Desktop 64-bit" preset, the x86_64 export
  templates; installed to <Axis>/Godot64).

**Linux x86-64 (2026-11-09).** Cross-built on Windows with zig:
- the game library: `bash standalone/build64.sh linux-gnu` -> `build/libaxis64.so` (glibc 2.28, exports only
  `axis_*`), copied to `project/bin/`; game.gd picks it off Windows;
- the extension: `bash extension/build_linux.sh [debug|release]` (godot-cpp from `Tools/godot/godot-cpp64` - its
  generated 64-bit bindings serve Linux too - compiled with the flags its SCons uses; its archive kept in
  `extension/obj_linux_<mode>/`) -> `project/bin/libaxis_godot.linux.template_<mode>.x86_64.so` (`host_posix.c`
  instead of `host_win.c`: dlopen; the mouse is Godot's captured mode);
- the export: `bash godot/export.sh release install linux` (the "Linux 64-bit" preset; the linux export templates
  extracted from the .tpz into `%APPDATA%/Godot/export_templates/4.7.2.stable`) -> `<Axis>/GodotLinux`
  (`AxisGodot.x86_64`).
Saves and settings on Linux go to the user folder (`~/.local/share/axis`, laid over the game folder, which is never
written; `~/.config/axis/registry.txt` for the registry's values) - src/plat/posix/files.c. Checked in WSL (musl,
headless): the library loaded with dlopen and run; the Godot build itself still needs a real Linux desktop.

## Checked

The skirmish session's first 2,000 frames (title, menus) recorded with the game's own images at frames 500, 1,000
and 1,990 (`AXIS_GLREC_DUMP_SHOTS`), replayed in Godot (Vulkan, RTX 3080): 98.6 / 99.0 / 99.95% of the pixels
identical, all of them within 8 levels of 255 (the rest: glyph edges where a sample falls on a texel boundary).

The game live (2026-11-09): the skirmish session driven through Godot's window - the title, the profile manager,
the skirmish set-up, the match (moving, turning, firing, the HUD at 120 fps, the help screen) - played from Godot,
saves unchanged. Not yet: the chat and Esc-menu steps were not captured (the capture needs the window in front).
The 32-bit editor is not large-address-aware (2 GB): a 4K frame cannot be encoded to PNG in-process, so checks
capture Godot's window instead.

2026-11-09, face culling fixed: front faces were mapped to Vulkan's clockwise, inverting GL's culling - culled
surfaces (the arena's walls and floor, the backdrop seen from inside) drew their far sides and the backdrop vanished.
A match recorded with the game's own images (frames 6,000 / 7,000 / 8,000 of the skirmish session) and replayed:
before, 2% identical; now 99.5 / 99.1 / 99.2% identical, every pixel within 8 levels. (The menu recording had not
exercised culling.)

2026-11-09, measured from the menus into the match (a session recorded with the game's own image every 300 frames,
70 frames: title, profile, menu, set-up, loading, free camera, fighting with boost / damage / deaths, respawn, help,
Esc menu), replayed in Godot, both its render and what its window showed:
- the window showed the frame 32-44% darker: the game's blended drawing leaves partial alpha in the frame, which the
  game's window ignores and Godot drew over its background (glows and particles near black). The frame's alpha is
  now kept at 1 (no alpha writes, opaque clears): shown within 0.6% of the render.
- lines exactly between two pixel rows fell a row high (GL's tie-break turned by the y flip): nudged a hundredth of a
  pixel. Menu frames' pixels off by more than 32 levels: 0.12% -> 0.01% (single glyph-edge columns).
- full screen at the game's size the frame is shown pixel for pixel (its window's extra row above the screen, as the
  original's); otherwise scaled with smoothing (it was squeezed unsmoothed into 1280 x 720). --windowed for a window.
Result over the 70 frames: 97.7-100% of pixels identical, 99.99-100% within 8 levels of 255; the lowest identical
shares (64-95%, boost and flash frames) are 1-5 level rounding where a translucent full-screen layer blends.

2026-11-09, no OpenGL: AxisGame starts the game with AxisHostConfig.nogl - its GL calls are only recorded for Godot
(no context, no drawing into the hidden window), its matrix / viewport / fog queries answered by the software GL
state (standalone/glstate.c mode 3), the rest a driver would give answered by the recorder (standalone/glrec.c
glrec_nogl). `--gl` runs the game's OpenGL as before, for comparison. Checked: the live skirmish session (title,
profile, match, chat, help, death) plays and looks the same. (The loaded-module check cannot tell the modes apart:
NVIDIA's Vulkan driver, which Godot uses, is the same nvoglv32.dll.)

2026-11-09, sound through Godot: AxisGame gives the game an AxisSound table (src/axis_api.h): its sound buffers go
to AxisMixer (extension/src/axis_audio.cpp - DirectSound's behaviour: play from the start unless playing, looping,
volume in hundredths of a dB, its pan law, 8 / 16-bit PCM resampled to 44.1 kHz, the sum clipped) feeding a Godot
AudioStreamGenerator; its music files play through Godot's AudioStreamMP3 (time, length, the seek it loops with).
No DirectSound or DirectShow then. Checked (game.gd --audio-log <file>): the menu music and sounds, the match's
music and up to 20 sounds at once in the fighting.

2026-11-09, the mouse: in Godot's captured mode no movement reached the game (nor Godot's own events: Godot takes the
process's raw mouse input and its loop consumes the raw input messages). Now as the original reads it: the raw
counts (DirectInput's) from a raw-input reader with its own thread and message loop (host_win.c, the registration
taken back if Godot re-registers), the pointer hidden and kept in the window with ClipCursor while it has the focus;
Godot's motion events only as a fallback until the reader has had any. Checked: injected moves arrive as exact raw
counts (-150, 40 -> -150, 40) and move the menu pointer. game.gd --input-log <file> logs the mouse every second.

2026-11-09, measured against the original (AXIS_MOUSELOG, game.gd --frame-log):
- Menu mouse: the original's DirectInput mouse reports the cursor's movement as Windows moves it, so the display
  scaling (150% here) and the pointer speed apply: 100 counts injected came to the original as 150. The raw reader
  gave 100, so the mouse was 2/3 as fast. Now the movement is the cursor's, re-centred each frame (host_cursor_delta),
  which also gives 150. --raw-mouse keeps the unscaled raw counts.
- Loading: the original shows each frame it draws while it loads (one game step of ~1 s draws hundreds of frames).
  In Godot a step runs inside Godot's frame, so only its last frame was shown. Now a step that has run for more than
  30 ms shows its frames with RenderingServer.force_draw, up to ~120 a second (measured: ~117 shown in a 1 s load).

2026-11-09, Shift and the loading pace (measured against the original, AXIS_LOADLOG):
- Godot sends a Shift's press but not its release: the modifiers are released from Windows' key state each frame.
- The original's SwapBuffers waits for the display's refresh, so each frame of a step that draws several (the
  loading screen, the start-up screen, the fades) takes a refresh interval. Godot showed them without waiting: the
  load into a skirmish took 1093 ms (the original 1421) and the backdrop scrolled 86 ms of time (the original
  418). Now each such frame is shown with RenderingServer.force_draw (vsync) before the next is drawn: 1434 ms,
  425 ms scrolled, median frame 8.31 ms (the original 8.33).
- Godot's boot splash is off and the game starts after Godot's window is shown (the game's start-up screen is drawn
  in its first step).
- The start-up screen still showed only its last frame: in the game's first step its full-size frame texture was
  attached by a deferred call (after the step), and the TextureRect's redraw is deferred too. Now the texture is
  attached before each frame shown in a step (AxisReplay::apply_texture), and on a size change the view is laid out
  and drawn at once (game.gd refit_now, signal game_size_changed). Checked with --step-shots <dir>: Godot's display
  at frames 5 / 20 / 35 of the start-up step shows the logo and the progress bar advancing.

2026-11-09, the exported game: `bash godot/export.sh release install` (needs build/axis.dll from PORTABLE=3 and the
release extension: the build command above with target=template_release). Godot's 4.7.2 export templates are
installed in %APPDATA%/Godot/export_templates/4.7.2.stable (only the 32-bit Windows ones, from the official .tpz,
SHA-512 checked). The export: build/godot_export/ - AxisGodot.exe (Godot's 32-bit release runtime), AxisGodot.pck,
the extension DLL and axis.dll; `install` copies it to <Axis>/Godot. Exported, game.tscn is the main scene
(run/main_scene.template), axis.dll is loaded from beside the exe and the game's folder is the exe's own when it
holds initdata, else the one above it. --game-dir and the check options still apply.

2026-11-09: game.tscn is the main scene (the editor's Play runs the game; the replay is started by name,
res://main.tscn). To work in the editor: open godot/project/project.godot (Godot 4.7.2 32-bit,
C:/Users/Alexander/Tools/godot/editor); bin/ must hold the extension DLL and axis.dll (built as above).

2026-11-09, the editor: Godot's official 32-bit editor crashes on start-up here, any project (_beginthreadex
fails: the exe is not large-address-aware, 2 GB of address space, and the editor at 4K with a worker thread per
CPU thread - 24, 8 MB stacks - runs out). Use the copies marked large-address-aware (4 GB on 64-bit Windows):
C:/Users/Alexander/Tools/godot/editor/Godot_v4.7.2-stable_win32_4GB.exe (and _4GB_console.exe), made with pefile
(IMAGE_FILE_LARGE_ADDRESS_AWARE, checksum redone). Checked: the project opens and Play runs the game (embedded in
the editor's game window, windowed). Debug builds of the extension report a crash's place (crash_report.c: the
function, source line and calls from the PDBs via dbghelp, to stderr and axis_crash.txt).
