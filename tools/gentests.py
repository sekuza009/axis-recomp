"""gentests.py batch out_code out_tests out_spec addr... : a batch of stubbed tests for small functions. Each
function's callees are stubbed (tools/stubargs.py's lists, key tests in key mode), its integer globals
(tools/classify.py) get small random values, its buffer globals in writable sections random strings, and its
four argument slots point at random strings at BUF + 0x100 * i (a value or a pointer either way). Review the
stub lists and the globals before running: a global that is really a pointer needs a hand-written setup."""
import sys, re, subprocess, pefile
D = 'C:/Users/Alexander/Desktop/Axis/recomp/'
pe = pefile.PE(D + 'installed.exe')
writable = [(pe.OPTIONAL_HEADER.ImageBase + s.VirtualAddress, pe.OPTIONAL_HEADER.ImageBase + s.VirtualAddress + s.Misc_VirtualSize)
            for s in pe.sections if s.Characteristics & 0x80000000]

def run(tool, a):
    return subprocess.run(['python', D + 'tools/' + tool, a], capture_output=True, text=True).stdout

batch = int(sys.argv[1]); out_code, out_tests, out_spec = sys.argv[2:5]; addrs = sys.argv[5:]
code = ['/* batch %d: small functions tested with their callees stubbed (tools/gentests.py) */' % batch]
tests = ['/* batch %d */' % batch]
spec = []
for a in addrs:
    st = run('stubargs.py', a).strip()
    name, lst = st.split(' ', 1)[0], st.split(': ', 1)[1]
    cl = run('classify.py', a)
    ints, bufs = [], []
    for line in cl.splitlines():
        kind, vals = line.split(' ', 1)[0], line.split()[2:]
        for v in vals:
            x = int(v, 16)
            if not any(lo <= x < hi for lo, hi in writable): continue
            if kind == 'addr' and x < 0x4d0000: continue   # the exe's string constants (in .data): left as they are
            (bufs if kind == 'addr' else ints).append(x)
    hexa = a[2:] if a.startswith('0x') else a
    code.append('LIFT_PLAIN(%s, %s)' % (name, hexa))
    tests.append('static const DWORD g_gs_%s[] = %s;' % (hexa, lst))
    tests.append('static const DWORD g_gi_%s[] = { %s0 };' % (hexa, ''.join('0x%x, ' % x for x in ints)))
    tests.append('static const DWORD g_gb_%s[] = { %s0 };' % (hexa, ''.join('0x%x, ' % x for x in bufs)))
    tests.append('T_PLAIN(%s, 0x%s, gen_setup(g_gs_%s, g_gi_%s, g_gb_%s);, 0, g_a[0], g_a[1], g_a[2], g_a[3])' % (name, hexa, hexa, hexa, hexa))
    spec.append('%s %s 0 200 0' % (name, hexa))
open(out_code, 'w').write('\n'.join(code) + '\n')
open(out_tests, 'w').write('\n'.join(tests) + '\n')
open(out_spec, 'w').write('\n'.join(spec) + '\n')
print('\n'.join(tests))
