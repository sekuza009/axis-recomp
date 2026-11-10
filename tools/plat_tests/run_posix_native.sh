#!/usr/bin/env bash
# the POSIX platform files' tests built and run on the machine itself (macOS, or a Linux with a compiler) - as
# run_posix.sh does through WSL. CC: the compiler (default cc). Usage: bash tools/plat_tests/run_posix_native.sh
set -e
cd "$(dirname "$0")"
OUT=../../build/plat_tests_native; mkdir -p "$OUT"
CC=${CC:-cc}
fails=0
for t in posix_files_test posix_registry_test posix_system_test posix_net_test posix_directplay_test; do
	EXTRA=; [ $t = posix_directplay_test ] && EXTRA="../../src/plat/posix/net.c ../../src/plat/posix/registry.c -Wno-unused-function -Wno-pointer-sign -Wno-format"
	$CC -O2 -w -DAXIS_PORTABLE -o "$OUT/$t" $t.c $EXTRA -lpthread
	echo "== $t"
	(cd /tmp && "$OLDPWD/$OUT/$t") || fails=$((fails + 1))
done
echo "the POSIX tests: $fails programs failed"
exit $fails
