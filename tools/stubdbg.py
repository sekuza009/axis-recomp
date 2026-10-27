"""stubdbg.py: patch recomp.c so every callee stub logs its address once ("STUBDBG addr" lines in recomp.log); build,
run tools/only.sh, grep STUBDBG, then restore recomp.c (keep a copy first) and rebuild."""
import os
os.chdir(r'C:\Users\Alexander\Desktop\Axis\recomp')
p = 'recomp.c'; b = open(p, 'rb').read(); s = b.decode('utf-8-sig')
a = '\tg_stubPop = fl & CS_POP ? 4u * (DWORD)n : 0;'
assert s.count(a) == 1
s = s.replace(a, a + '\r\n\t{ static DWORD seen[256]; static int ns; int i = 0; while (i < ns && seen[i] != g_stubAddr[k]) i++; if (i == ns && ns < 256) { seen[ns++] = g_stubAddr[k]; say("STUBDBG %08lx\\n", g_stubAddr[k]); } }')
open(p, 'wb').write(b'\xef\xbb\xbf' + s.encode()); print('ok')
