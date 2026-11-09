#!/usr/bin/env bash
# the 64-bit build run headless on Linux (WSL): a scratch game folder in /dev/shm/axis64 (WSL's /tmp is too small) -
# the game's data folders linked (read only), its saves, settings and loose files copied (the game writes there) - then
# build/axis64_test. Usage: bash tools/plat_tests/run64.sh [frames] [stream file name in build/]
set -e
cd "$(dirname "$0")/../.."
G=/mnt/host/c/Users/Alexander/Desktop/Axis
B=$(cd build && pwd -W | sed 's#^\([A-Za-z]\):#/mnt/host/\L\1#')
DISTRO=${WSL_DISTRO:-docker-desktop}
FRAMES=${1:-300}
STREAM=; [ -n "$2" ] && STREAM="$B/$2"
# (the commands as a file: wsl.exe's command line loses a script's variables)
cat > build/run64_inner.sh <<EOF
set -e
mkdir -p /dev/shm/axis64
cd /dev/shm/axis64
for d in Data Map Sound Music; do [ -e "\$d" ] || ln -s "$G/\$d" "\$d"; done
[ -d Save ] || cp -r "$G/Save" Save
[ -d initdata ] || cp -r "$G/initdata" initdata
for f in Chat.scp Help.txt MATHFUNC.TBL axisnet.ini AxisPlay.exe; do [ -e "\$f" ] || cp "$G/\$f" .; done
cp "$B/axis64_test" /dev/shm/axis64_test
set +e
AXIS_SETTINGS=/dev/shm/axis64/registry.txt /dev/shm/axis64_test /dev/shm/axis64 $FRAMES $STREAM
echo "exit \$?"
echo '---- standalone64.log'
head -80 /dev/shm/axis64/standalone64.log
EOF
MSYS_NO_PATHCONV=1 wsl.exe -d "$DISTRO" -- sh "$B/run64_inner.sh" | tr -d '\0'
