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
# (the launcher's settings the game reads: a server list - here a local one - and the start mode)
[ -e registry.txt ] || printf '[80000001\\SOFTWARE\\AxisArena\\SelectServer]\nTcpDNS=1:3132372e302e302e3100\nLadderDNS=1:3132372e302e302e3100\nTcpPort=4:e4070000\nLadderPort=4:f8070000\n[80000001\\SOFTWARE\\AxisArena\\Launcher]\nStartMode=4:00000000\n' > registry.txt
cp "$B/axis64_test" /dev/shm/axis64_test
cp "$B/axis64_test_so" "$B/libaxis64_musl.so" /dev/shm/ 2>/dev/null
# (the user folder: AXIS_USER_DIR, default /dev/shm/axis64user; "-" writes the game folder)
U=${AXIS_USER_DIR:-/dev/shm/axis64user}
TEST=/dev/shm/axis64_test; [ -n "$AXIS_TEST_SO" ] && TEST=/dev/shm/axis64_test_so
set +e
AXIS_TEST_LIB=/dev/shm/libaxis64_musl.so AXIS_USER_DIR=\$U AXIS_TEST_ENDING=$AXIS_TEST_ENDING AXIS_SETTINGS=/dev/shm/axis64/registry.txt \$TEST /dev/shm/axis64 $FRAMES $STREAM
echo "exit \$?"
LOG=/dev/shm/axis64/standalone64.log; [ "\$U" != "-" ] && LOG=\$U/standalone64.log
echo "---- \$LOG"
head -80 \$LOG; grep -a "ending movie" \$LOG
[ "\$U" != "-" ] && { echo "---- the user folder \$U"; find \$U -type f | head -40; }
echo "---- the game folder's files changed during the run:"; find -L /dev/shm/axis64 -newer \$TEST -type f 2>/dev/null | grep -v "/Data/\|/Map/\|/Sound/\|/Music/" | head; echo "(end)"
EOF
MSYS_NO_PATHCONV=1 wsl.exe -d "$DISTRO" -- sh "$B/run64_inner.sh" | tr -d '\0'
