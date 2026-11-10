# AxisSDL - the portable build as a program of its own

The original game, with its fixes, on Windows, Linux and macOS, without Godot: the 64-bit game library
(src/axis_api.h, `standalone/build64.sh`) linked into a small SDL3 program.

- **Drawing:** the game's own OpenGL 1.x calls, recorded by the library each frame, played one by one on a real
  OpenGL context (`gl_play.c`); GLU is the system's (Windows' glu32, as the original used), else gl_play's own.
  At DESKTOP the game is shown 1:1; another resolution is scaled to fit with its shape kept.
- **Window:** borderless, one row taller than the screen from y = -1 - the original fix's window, so the driver keeps it
  an ordinary window (instant Alt-Tab); `--windowed` for a resizable window.
- **Input:** SDL's keys as DirectInput's key codes; the mouse relative, with the system's pointer speed (what the
  original's DirectInput reported); text fields get keys and characters as Windows sends them.
- **Sound:** the game's buffers mixed as DirectSound mixes them (`axis_audio.cpp`, shared with the Godot host), its MP3
  music decoded with dr_mp3 (third_party/dr_libs, public domain / MIT-0).
- **Network:** the library's - axisnet's DirectPlay, as every other build: plays with AxisRC.exe, AxisGL.exe and the
  Godot builds.
- Saves and settings: the game folder on Windows, the user folder elsewhere (src/plat/posix/files.c).
- **Launcher** (`launcher.cpp`): AxisPlay.exe rewritten, as the Godot build's launcher.gd (godot branch) - the 642 x 482
  window with MainBK.bmp, the eight buttons with their four pictures, the icon and cursor read from the user's own
  AxisPlay.exe, the hover / click sounds, the install-state rules, Play Game (server and render-mode checks, StartMode
  1, then the game in this program), Cinematics (the movies decoded by the library's avimovie.c, full screen with
  sound, Esc skips), Help, Change Server (ServerList.dat into SelectServer), Install DirectX (Windows), Video Setup
  (OpenGL only), Install Game, Quit; the settings in the registry (Windows) or the library's registry.txt. On Windows
  the dialogs are the original's own - its dialog templates from AxisPlay.exe, run by Windows; elsewhere message boxes
  with the same choices. `--play` skips the launcher (the game's restart after a graphics change passes it).

Build (Windows, with zig): `bash standalone/build64.sh windows`, then `bash host/sdl/build.sh windows` ->
`build/sdl/windows/AxisSDL.exe` + `SDL3.dll` (SDL3's MinGW development files: SDL3_MINGW). Put both in a folder inside
the game folder (or the game folder itself); `--game-dir <folder>` overrides.

Linux x86-64 (cross-built with zig): `bash standalone/build64.sh linux-gnu`, then `bash host/sdl/build.sh linux` ->
`build/sdl/linux/AxisSDL` + `libSDL3.so.0` (found beside it: rpath $ORIGIN). SDL3 for Linux (SDL3_LINUX: lib/, include/)
was built from the release source in WSL's Ubuntu 24.04 (cmake, with the X11 / Wayland / PulseAudio / PipeWire / ALSA
development headers), so it needs glibc 2.38 or newer (current distributions, SteamOS); for older systems SDL3 is to be
built against an older glibc.

Checked (2026-11-09, Windows x64, RTX 3080): the title, menus and a skirmish at 120 fps with sound; two copies in one
match over the network; the drawing against the original - a session recorded by the native 32-bit build (real
OpenGL) and its own images at frames 600, 1800, 2900, replayed with gl_play (`glplay_check`): 97.8-98.0% of the pixels
identical, all within 8 levels (sub-pixel rounding; with gl_play's own GLU instead of glu32: 96%).
Linux (2026-11-09, WSLg on Ubuntu 24.04; OpenGL through Mesa's D3D12 driver on the RTX 3080): the title, login, menus,
a skirmish, chat typing, sound; the game folder (the Windows one) only read - its writes (axis.cfg, axisuser.dat, the
launcher marks) in ~/.local/share/axis. Under WSLg the window is a plain one (`--windowed`: Wayland places windows
itself) and vsync does not hold (the game ran at 270-350 fps).
