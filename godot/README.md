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
- `project/` - the Godot project: `main.tscn` shows the replay full-window. Command line after `--`:
  `<file.glrec> [--fps N] [--shot frame:file.png ...] [--quit-after N]`.

Run the game: `Godot --path project res://game.tscn -- --game-dir <the Axis folder>` (`--shot frame:file.png`,
`--quit-after N` for checks). The replay: `res://main.tscn -- <file.glrec>`.

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

## Checked

The skirmish session's first 2,000 frames (title, menus) recorded with the game's own images at frames 500, 1,000
and 1,990 (`AXIS_GLREC_DUMP_SHOTS`), replayed in Godot (Vulkan, RTX 3080): 98.6 / 99.0 / 99.95% of the pixels
identical, all of them within 8 levels of 255 (the rest: glyph edges where a sample falls on a texel boundary).

The game live (2026-11-09): the skirmish session driven through Godot's window - the title, the profile manager,
the skirmish set-up, the match (moving, turning, firing, the HUD at 120 fps, the help screen) - played from Godot,
saves unchanged. Not yet: the chat and Esc-menu steps were not captured (the capture needs the window in front).
The 32-bit editor is not large-address-aware (2 GB): a 4K frame cannot be encoded to PNG in-process, so checks
capture Godot's window instead.
