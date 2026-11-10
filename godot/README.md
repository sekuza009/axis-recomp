# The godot branch

The rebuilt game on Godot 4 (PORTING.md): the base for a remaster - Godot as the renderer. 64-bit (Windows, Linux,
macOS), Godot 4.7. (The 32-bit build was dropped on 2026-11-09: the portable build, AxisSDL - host/sdl on the portable
branch - is the original game on every system; this one is free to change the picture.)

## The remaster look (step 1)

`AxisReplay` / `AxisGame` apply effects to the finished **3D world** - the batches drawn with a perspective projection
(gl_emu marks them: `EmuBatch::persp`) - after the frame's last 3D batch and before the HUD and menus are drawn over
it, so the HUD, text and menu panels stay exactly the original's. Compute passes on Godot's RenderingDevice
(axis_replay.cpp, `run_post`): the world copied; bloom (a bright pass with a soft knee, saturated colours weighted
over pale surfaces - the game has nothing brighter than white - then a chain of half sizes down with a 13-tap filter
and back up with a tent); the composite written back into the frame: sharpening (limited to the neighbours' range),
the bloom added, exposure, contrast, saturation, warmth, a vignette, highlights rolled off above 0.9.

The settings are properties ("Remaster look" in the inspector): `look_enabled`, `bloom`, `bloom_threshold`,
`bloom_radius`, `exposure`, `contrast`, `saturation`, `warmth`, `vignette`, `sharpen`. game.tscn's Game node holds the
game's (on); they can be changed while the game runs from the editor's Remote scene tree. In game **Ctrl+F11** turns
the look on and off (the game does not see that key); `--no-look` starts with it off. main.tscn (the replay) has it
off, `--look` on - the recorded frames compared both ways. Checked on a recorded match (frames 6,000-8,000) and live:
menus without 3D are untouched; the title and menu backdrops and the arena get the look.


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

## The remaster's view of the game (steps 1b.1 and 1b.2: tags, camera)

**Tags.** The 64-bit game library says what it draws (src/render/draw_tags.h, portable branch): the kind each pass
of the match's frame queues under - sky, ground, map objects, actors, the actors' second pass (over a cleared depth
buffer), bullets, particles, items, markers, HUD - kept by the view volume for every queued record and sent as a tag
op before the drawing (glrec64.c's OP_TAG). gl_emu puts it in each batch (`EmuBatch::tag`). **Ctrl+F9** in game (or
`--tags`) is the tag view: each part tinted by its kind (yellow map objects, green ground, red actors, pink actor view,
orange bullets, cyan particles, purple items, blue sky, grey HUD). On the skirmish arena recorded the whole arena is
map objects (~600 triangles: no ground layers on that map), the mechs ~2,300, items, particles and the HUD.

**Camera.** Once per view volume drawn the game sends its camera (OP_CAMERA: the projection and view matrices).
`AxisReplay.get_camera_projection()` / `get_camera_view()` / `get_camera_viewport()` give them as Godot's types; the
world's points of chosen kinds come back from the frame with `get_world_triangles(mask)` / `get_world_samples(mask, n)`
(the clip coordinates gl_emu made, the viewport unfolded, projection x view inverted in doubles). remaster_view.gd
(`RemasterView`) makes a Godot **Camera3D** from them each frame: the view's inverse as its transform, a frustum
covering the whole frame at the projection's scale with its centre moved by the viewport's (the frame is one row
taller than the game's viewport: the original's window starts at y -1). **Ctrl+F10** (or `--overlay`): the map's
ground and objects rebuilt as a Godot mesh from the frame and drawn by Godot's own 3D renderer through that camera,
a green wireframe over the game's picture. `--camera-report <file>`: the check's numbers (every 300 frames in game, at
each --shot in the replay) - a sample of ~2,400 world points (map, actors, items) projected by the Camera3D
(unproject_position) against where the game drew them: on the recorded match mean 0.001 px, 99% within 0.011 px,
worst 0.56 px (frames 8,400 / 9,000 / 10,200).

`--record <file>` (game.gd): the game's drawing written as an AXGLREC1 file while it plays, for main.tscn to replay
(the camera and tags included).

## The picture: Godot draws the map (step 1b.3)

`picture_mode` (AxisReplay / AxisGame, "Remaster picture" in the inspector; **Ctrl+F12** in game cycles it,
`--picture N` on the command line):
- **0 Original**: the game's own drawing, exactly as before.
- **1 Original lighting**: the map drawn by Godot with the game's own lighting (its vertex colours: the light factors
  it computes per vertex) - unshaded materials, texture x colour as the game's texture environment does it.
- **2 Remaster**: the map lit by Godot - remaster_world.tscn's DirectionalLight3D (shadows) and WorldEnvironment, to be
  edited in the editor - with the game's own lighting kept as a base glow (`original_light`, 0.6).

How: remaster_view.gd keeps a second SubViewport with the same Camera3D (step 2) under remaster_world.tscn. Each frame
`AxisReplay.build_map_mesh()` rebuilds the map from that frame's own batches - the ground and map objects drawn as the
view volume's solid meshes, in the world (the camera inverted), textured with the game's textures (Texture2DRD over the
same RD textures), the game's culling kept (GL's counter-clockwise fronts turned to Godot's clockwise). An
AxisMapEffect (CompositorEffect, after Godot's transparent pass) then draws the game's frame during that viewport's
render: the game's solid map surfaces are drawn as always - their own depth, their own depth test - but coloured from
Godot's picture at each pixel, so Godot's map is seen exactly where the game's would be and everything the game draws
next (mechs, effects, items, the HUD) is hidden behind it as before. What stays the game's own: the sky, the map's
see-through parts (depth-sorted glows and beams - over the sky they need what is behind them) and additive surfaces.
Alpha-blended solid meshes are cutouts in Godot (the arena's central column is such a mesh with a clear texture: only
its glow shows).

Checked on the recorded skirmish (frames 8,400 / 9,000 / 10,200): mode 1 looks the same as the original (the pixels
differ by the texture filtering and the gamma round trip on a busy texture: 53-59% within 8 levels, 76-80% within 32);
live in a skirmish (mode 2): 120 fps, no long frames. `AXIS_MAP_STATS=1` prints the map batches' state.

## The game's lights in Godot (step 4)

Once per frame the 64-bit library sends the stage's three light pools (src/render/draw_tags.h `DRAW_LIGHTS`, glrec64's
OP_LIGHTS): the map's (from the map file), the dynamic ones (refilled every frame: a light at each mech, of its glow,
and at each particle that gives light - explosions, flashes) and the actors' own (an ambient and one from above, for the
mechs). `AxisReplay.get_lights()` gives them as {pool, kind, colour, position, direction, radius}.

remaster_world.gd (on remaster_world.tscn, its settings in the inspector) turns them into Godot's for the remaster
picture each frame: the map's ambient as the environment's ambient colour (`ambient_energy`), the map's and the dynamic
point lights as OmniLight3Ds of the game's colour and radius (`map_point_energy`, `dynamic_energy`, `dynamic_shadows`,
`max_point_lights`), a directional light of the map's as the Sun (else the Sun as placed: `sun_without_map_light`). The
game's kind 2 point light is full out to about half its radius and fades out at it: Godot's `omni_attenuation` 0
(constant, a smooth edge); Godot's default falls off with the distance squared, nearly nothing at the game's
distances. Godot's map world is in metres: the game's units x 0.01 (remaster_view.gd `WORLD_SCALE`; the camera, the
mesh and the lights scaled alike).

The skirmish arena has no point lights of its own (its map pool is one white ambient: its look is in its textures and
vertex colours); its dynamic lights - the mechs' glow, the explosions - light the walls around them per pixel (up to 13
at once in the recorded match). `AXIS_LIGHT_LIST=1` (main.tscn, at a --shot) prints the frame's lights;
`AXIS_LIGHT_TEST=<energy>` adds a white light at the camera (a check that Godot's lights reach the map).

## Godot draws the mechs and items (step 5)

`godot_kinds` (AxisReplay / AxisGame, "Remaster picture"; flags by tag) says which kinds Godot draws in picture modes
1 and 2: by default the ground, map objects, actors (the mechs) and items. The actors come through each frame already
posed and animated (the game's own skinning), so they are rebuilt in the world like the map (build_map_mesh: one mesh
of every chosen kind, by material) and the game colours its own surfaces of those kinds from Godot's picture - their
occlusion exactly the game's, their light Godot's, their shadows cast on the arena by the Sun. Normals are smoothed
where faces within 60 degrees share a position (the mechs' curved armour; a box's edges stay sharp). What stays the
game's: the actors' view pass (the first-person weapon, drawn over a cleared depth buffer), bullets, particles and the
see-through and additive parts. Checked on the recorded skirmish (mode 1: the mech as the original's) and live (mode 2,
120 fps, no long frames in the match).

## Godot draws the effects (step 6)

In the remaster picture (mode 2) Godot also draws the effects: bullets, particles and explosions, and the see-through
and additive parts of the map, mechs and items (the depth-sorted triangles and billboards the game draws already
projected - unprojected with the frame's camera like the rest). `godot_class()` (axis_replay.cpp) decides for each batch:
a solid surface, a cutout, or an effect - alpha-blended, additive with source alpha, additive with one - or the game's
own. Effects are unlit (they give light: step 4's lights), blended by Godot without writing depth, and kept in the
game's back-to-front order: a surface per run of one material, in the game's order, its render priority (-128 .. 127)
by run. The frame's geometry is split over meshes of at most 256 surfaces (Godot's limit: `build_map_meshes()`). The
game colours its own batches of those kinds from Godot's picture, which has the blending done already.

Not in mode 1: Godot blends in linear light, the game in its gamma, so glows come out a little brighter - mode 1 keeps
the game's own effects to look as the original. Not in a frame that draws the sky: Godot does not draw the sky yet
(sky.c draws it from several viewpoints of its own), and an effect over it needs what is behind it; such frames keep
the game's effects. The skirmish arena has no sky. Checked on the recorded skirmish's explosion frames and live (mode 2:
120 fps, no long frames in the match).

## Godot draws the sky (step 6b)

The skirmish rounds' maps are mapinfo.dat's in order (round N, map N: 11 Abyss, 12 Metropolis, 13 StarField, 14
Netsphere - the arena of the earlier recordings); sess5/godot_sky.sh in the scratchpad drives a round of the skirmish screen.
Abyss has a sky, 33 point lights and 3 directional lights of its own.

sky.c draws the sky from several viewpoints of its own (the sphere and the cloud layers from the origin looking along
the camera, the side walls and the floor from heights of their own), all with the camera's projection. So
`build_sky_meshes()` takes each sky triangle back to the camera's space by inverting the projection only: where it is
seen, whichever view drew it. remaster_view.gd renders them in a viewport of their own (a child of the map's, so drawn
first; its camera at the eye looking down -z), in the game's order (a surface per batch, render priority by order, no
depth test, the fog per vertex), and that picture is the map world's background (BG_CANVAS). The sky's colours stay in
the game's gamma while its layers blend - blended in linear light a dark layer under a bright one all but vanishes
(Abyss's purple nebula under its clouds did) - and the finished sky is taken to linear light once (sky_back's shader).
The frame's clear colour shows through it as in the game. With the sky Godot's, the remaster picture's effects are
Godot's on every map (frame_effects()). `AXIS_SKY_ONLY=<n>` renders one sky part alone (a check).

Lights, from Abyss: every directional light of the map is used (the first as the Sun, with shadows; the rest without),
turned round (`turn_directional_lights`: the game shades with the normals stored in its models, which point the other
way from their faces, so its lights in effect shine against their direction - turned, its warm, teal and grey lights
fall where the original's do), and the lit map materials use Godot's wrapped diffuse light (`diffuse_lambert_wrap`) as
the game's is: half light at right angles to a light (shading.c facing(): (1 - n.L) x 128). Checked on the recorded
Abyss round (all three modes) and live (mode 2: 120 fps; one 162 ms frame in the match, when the player died).

## Building (Windows, zig as the compiler)

**Since 2026-11-09 64-bit only**: the extension `arch=x86_64` against `Tools/godot/godot-cpp64` (SConstruct's default),
the game library `bin/axis64.dll` (`bash standalone/build64.sh windows`), the 64-bit editor `Tools/godot/editor64`
(the .bat files use it), `bash godot/export.sh release install` -> <Axis>/Godot64. The 32-bit notes below are history.

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
- the extension: `bash extension/build_posix.sh [debug|release] linux` (godot-cpp from `Tools/godot/godot-cpp64` - its
  generated 64-bit bindings serve Linux too - compiled with the flags its SCons uses; its archive kept in
  `extension/obj_linux_<mode>/`) -> `project/bin/libaxis_godot.linux.template_<mode>.x86_64.so` (`host_posix.c`
  instead of `host_win.c`: dlopen; the mouse is Godot's captured mode);
- the export: `bash godot/export.sh release install linux` (the "Linux 64-bit" preset; the linux export templates
  extracted from the .tpz into `%APPDATA%/Godot/export_templates/4.7.2.stable`) -> `<Axis>/GodotLinux`
  (`AxisGodot.x86_64`).
Saves and settings on Linux go to the user folder (`~/.local/share/axis`, laid over the game folder, which is never
written; `~/.config/axis/registry.txt` for the registry's values) - src/plat/posix/files.c. Checked in WSL (musl,
headless): the library loaded with dlopen and run. **Run on a Linux desktop (2026-11-09):** the export under WSLg
(Ubuntu 24.04; `tools/plat_tests/run_wslg.sh`) - the launcher (its first-time flow: the server dialog, the render
mode message, Video Setup, settings in registry.txt), Play into the game, keyboard, mouse (captured), sound, a login;
the saves and axis.cfg written to ~/.local/share/axis, the Windows game folder untouched. There Vulkan is Mesa's
software renderer and message boxes fall back to xmessage without zenity / kdialog.

**macOS 11+, Intel and Apple Silicon (2026-11-09).** Cross-built on Windows with zig, as Linux:
- the game library: `bash standalone/build64.sh macos` -> `build/libaxis64.dylib` (universal: x86_64 + arm64, joined
  by tools/lipo.py; arm64 has no x87 - src/x87.h and axis.h's float helpers in plain C there), copied to `project/bin/`;
- the extension: `bash extension/build_posix.sh [debug|release] macos` (the Linux script, generalised: `linux`,
  `macos-x86_64`, `macos-arm64`, `macos`) -> `project/bin/libaxis_godot.macos.template_<mode>.dylib` (universal; the
  arm64 parts ad-hoc signed by zig's linker);
- the export: `bash godot/export.sh release install macos` (the "macOS" preset: universal, Godot's built-in ad-hoc
  signing; the macos.zip template extracted from the .tpz) -> `build/godot_export_macos/AxisGodot.zip`, the app with the
  game library in Contents/Frameworks (axis.gdextension's dependencies). The game folder is the one holding the app
  (or the one above it - AxisFiles). Not notarised: on a Mac, open it the first time with right-click > Open (or
  `xattr -dr com.apple.quarantine "Axis (Godot).app"`).
Checked on GitHub's macOS runners (.github/workflows/macos.yml): the library built natively, the POSIX tests, the x87
replacements against the x87's results, the library loaded with dlopen.

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
