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
