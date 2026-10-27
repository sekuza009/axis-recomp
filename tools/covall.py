"""covall.py: instrument every lifted file for a coverage run: each function entry and each label records its
address once (a bit and a list, no calls: lifted code runs on its own stack, where calling the log could fault), and
recomp.c dumps the list ("COVHIT addr" lines in recomp.log) at the end of the run. Run tools/allstate.sh, then
tools/covreport.py; restore with "git checkout -- lifted recomp.c" (the instrumentation is never committed)."""
import os, re, glob
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
pre = ('#ifndef COV_DEFINED\n#define COV_DEFINED\n'
       'static unsigned char g_covbits[0x16000];   /* one bit per code byte from 0x400000 */\n'
       'static unsigned g_covlist[0x8000], g_covn;\n'
       'static void cov_hit(unsigned a) { unsigned k = a - 0x400000u; if (k < 0xb0000u && !(g_covbits[k >> 3] & (1 << (k & 7)))) '
       '{ g_covbits[k >> 3] |= 1 << (k & 7); if (g_covn < 0x8000) g_covlist[g_covn++] = a; } }\n'
       'static void say(const char *fmt, ...);\n'
       'static void cov_dump(void) { for (unsigned i = 0; i < g_covn; i++) say("COVHIT %x\\n", g_covlist[i]); }\n#endif\n')
n = 0
for p in sorted(glob.glob('lifted/*.c')):
    s = open(p, newline='').read()
    if 'cov_hit(' in s: continue
    nl = '\r\n' if '\r\n' in s else '\n'
    lines = s.split(nl); out = []; done = False; fn = None
    for l in lines:
        m = re.match(r'^static void lift_([0-9a-f]+)\(X86 \*m\)$', l)
        if m and not done:
            out.extend(pre.replace('\n', nl).split(nl)[:-1]); done = True
        out.append(l)
        if m: fn = m.group(1)
        elif fn and l == '{':
            out.append('\tcov_hit(0x%su);' % fn); fn = None
        lm = re.match(r'^L_([0-9a-f]+):$', l)
        if lm: out.append('\tcov_hit(0x%su);' % lm.group(1))
    open(p, 'w', newline='').write(nl.join(out)); n += 1
r = open('recomp.c', 'rb').read()
a = b'\tthaw();\r\n\tg_frozen = 0;\r\n'
if b'cov_dump();' not in r:
    assert r.count(a) == 1
    open('recomp.c', 'wb').write(r.replace(a, b'\tcov_dump();\r\n' + a))
print('instrumented', n, 'files and recomp.c')
