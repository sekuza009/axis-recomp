"""covlift.py <lifted.c>: log label hits (COVHIT addr count at the 1st, 10th, 100th and 1000th hit) of the lifted
function(s) into recomp.log via say(). Restore the file from its .cov.bak copy afterwards."""
import sys, re, shutil
p = sys.argv[1]
shutil.copy(p, p + '.cov.bak')
s = open(p, newline='').read()
nl = '\r\n' if '\r\n' in s else '\n'
lines = s.split(nl)
out = []
pre = ('static unsigned short g_covn[0x40000];' + nl +
       'static void say(const char *fmt, ...);' + nl +
       'static void cov_hit(unsigned a) { unsigned k = a & 0x3ffff, c = ++g_covn[k]; '
       'if (c == 1 || c == 10 || c == 100 || c == 1000) say("COVHIT %x %u\\n", a, c); }')
done = False
for l in lines:
    m = re.match(r'^L_([0-9a-f]+):$', l)
    if not done and l.startswith('static void lift_'):
        out.append(pre); done = True
    out.append(l)
    if m:
        out.append('\tcov_hit(0x%su);' % m.group(1))
open(p, 'w', newline='').write(nl.join(out))
print('instrumented', p)
