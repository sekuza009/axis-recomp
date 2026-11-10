#!/usr/bin/env bash
# host/sdl/sdl3_linux.sh <SDL3 source tarball> <out folder>: SDL3 for AxisSDL's Linux build, run on a Linux machine (WSL's
# Ubuntu here) as root - built with zig for glibc 2.28, so AxisSDL runs on distributions back to about 2018: zig's own
# glibc 2.28 headers first, the system's development headers (X11, Wayland, PulseAudio, PipeWire, ALSA, D-Bus...) after
# them; those libraries are loaded at run time, so only their names are taken from the system. Writes <out>/lib/
# libSDL3.so.0.* and <out>/include (host/sdl/build.sh linux: SDL3_LINUX).
set -e
SRC=${1:?the SDL3 source tarball}; OUT=${2:?the out folder}
export DEBIAN_FRONTEND=noninteractive
apt-get install -y -qq build-essential cmake ninja-build pkg-config python3-venv libx11-dev libxext-dev libxrandr-dev \
	libxcursor-dev libxi-dev libxss-dev libxfixes-dev libxtst-dev libxkbcommon-dev libwayland-dev wayland-protocols \
	libegl-dev libgl-dev libpulse-dev libasound2-dev libdbus-1-dev libudev-dev libdrm-dev libgbm-dev libdecor-0-dev \
	libpipewire-0.3-dev > /tmp/sdl3_apt.log
[ -x /root/zigenv/bin/python ] || python3 -m venv /root/zigenv
/root/zigenv/bin/pip install -q ziglang==0.16.0
for t in cc ar ranlib; do
	extra=; [ $t = cc ] && extra="-target x86_64-linux-gnu.2.28 -idirafter /usr/include -idirafter /usr/include/x86_64-linux-gnu"
	printf '#!/bin/sh\nexec /root/zigenv/bin/python -m ziglang %s %s "$@"\n' $t "$extra" > /root/zig$t
	chmod +x /root/zig$t
done
W=$(mktemp -d)
tar xzf "$SRC" -C "$W"
cd "$W"/SDL3-*
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=/root/zigcc -DCMAKE_AR=/root/zigar \
	-DCMAKE_RANLIB=/root/zigranlib -DCMAKE_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu -DSDL_SHARED=ON -DSDL_STATIC=OFF \
	-DSDL_TESTS=OFF -DSDL_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX="$W/install" > /tmp/sdl3_cfg.log
grep -E "^--   SDL_(X11|WAYLAND|ALSA|PULSEAUDIO|PIPEWIRE) " /tmp/sdl3_cfg.log
cmake --build build > /tmp/sdl3_build.log
cmake --install build > /dev/null
echo "needs glibc up to $(objdump -T "$W"/install/lib/libSDL3.so.0 | grep -o 'GLIBC_[0-9.]*' | sort -uV | tail -1)"
rm -rf "$OUT" && mkdir -p "$OUT/lib"
cp "$W"/install/lib/libSDL3.so.0.* "$OUT/lib/"
cp -r "$W"/install/include "$OUT/"
