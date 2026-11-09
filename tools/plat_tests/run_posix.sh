#!/usr/bin/env bash
# the POSIX platform files checked on real Linux: built as static 32- and 64-bit Linux programs (zig cc) and run in
# WSL (Docker Desktop's distribution is enough). Usage: bash tools/plat_tests/run_posix.sh
set -e
cd "$(dirname "$0")"
OUT=../../build/plat_tests; mkdir -p "$OUT"
for t in posix_files_test; do
	python -m ziglang cc -target x86-linux-musl -static -O2 -Wall -o "$OUT/${t}_32" $t.c
	python -m ziglang cc -target x86_64-linux-musl -static -O2 -Wall -o "$OUT/${t}_64" $t.c
done
L=$(cd "$OUT" && pwd -W | sed 's#^\([A-Za-z]\):#/mnt/host/\L\1#')
DISTRO=${WSL_DISTRO:-docker-desktop}
for t in posix_files_test; do
	for b in 32 64; do
		echo "== $t ($b-bit)"
		wsl.exe -d "$DISTRO" -- sh -c "cp '$L/${t}_$b' /tmp/ && /tmp/${t}_$b" | tr -d '\0'
	done
done
