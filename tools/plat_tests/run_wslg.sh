#!/usr/bin/env bash
# the Linux export (<Axis>/GodotLinux, godot/export.sh release install linux) run on this PC's Linux desktop: WSL's
# Ubuntu-24.04 distribution with WSLg (its window on the Windows desktop). The game folder is the Windows one - only
# read: the game's writes go to the distribution's ~/.local/share/axis, its settings to ~/.config/axis/registry.txt.
# Godot's own output: /tmp/godot.log in the distribution. Extra arguments go to the game (after "--": e.g. --play).
# Set up once (as root): the libraries Godot loads - libx11-6 libxcursor1 libxinerama1 libxrandr2 libxi6 libxext6
# libxrender1 libgl1 libegl1 libvulkan1 mesa-vulkan-drivers libpulse0 libasound2t64 libfontconfig1 libwayland-client0
# libwayland-cursor0 libwayland-egl1 libxkbcommon0 libdbus-1-3 (and zenity, for message boxes nicer than xmessage).
# Vulkan there is Mesa's software renderer (llvmpipe): slow, but complete.
DISTRO=${WSL_UBUNTU:-Ubuntu-24.04}
ARGS=; [ $# -gt 0 ] && ARGS="-- $*"
MSYS_NO_PATHCONV=1 wsl.exe -d "$DISTRO" -u root -- bash -c "
export LD_LIBRARY_PATH=/usr/lib/wsl/lib PULSE_SERVER=unix:/mnt/wslg/PulseServer XDG_RUNTIME_DIR=/mnt/wslg/runtime-dir
cd /mnt/c/Users/Alexander/Desktop/Axis/GodotLinux && exec ./AxisGodot.x86_64 $ARGS > /tmp/godot.log 2>&1"
