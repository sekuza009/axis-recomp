"""tosrc.py "decl;call" ...: move functions from recomp.c's lifted wrappers to their readable rebuild in src/.
For each function: its wrapper in recomp.c (LIFT_PLAIN / LIFT_PLAIN8 / a "static THISCALL DWORD name(...)
{ return run_lifted(...) }" line) becomes the declaration decl, and its test's rebuilt side calls the src
function: a T_PLAIN test gets the call expression call, with a1..a4 for its four arguments (as DWORDs); an ST test
whose rebuilt side calls name(...) keeps that call, wrapped as (call, 0) when decl returns void.

  python tools/tosrc.py "void main_loop(void);main_loop()" "int THISCALL main_462050(void *scene);"
"""
import os, re, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
p = 'recomp.c'; b = open(p, 'rb').read(); bom = b.startswith(b'\xef\xbb\xbf'); s = b.decode('utf-8-sig'); nl = '\r\n'
EXT = '/* readable rebuild in src/ (its own translation unit, see src/axis.h) */' + nl
for arg in sys.argv[1:]:
    decl, _, call = arg.partition(';')
    decl = decl.strip().rstrip(';') + ';'
    name = re.search(r'(\w+)\s*\(', decl).group(1)
    void = decl.startswith('void ')
    # the wrapper
    pats = [r'LIFT_PLAIN8?\(%s, [0-9a-f]+\)' % name,
            r'static THISCALL DWORD %s\([^)]*\) \{ (?:DWORD v\[\d\] = \{[^}]*\}; )?return run_lifted\([^;]*\); \}' % name,
            r'static THISCALL DWORD %s\([^)]*\)\r\n\{\r\n(?:\tDWORD v\[\d\] = \{[^}]*\};\r\n)?\treturn run_lifted\([^;]*\);\r\n\}' % name]
    for pat in pats:
        m = list(re.finditer(pat, s))
        if m: break
    if len(m) != 1: raise SystemExit('%s: wrapper not found once (%d)' % (name, len(m)))
    s = s[:m[0].start()] + EXT + decl + s[m[0].end():]
    # the test
    t = list(re.finditer(r'T_PLAIN\(%s, (0x[0-9a-f]+), (.*?), ([^,]+), ([^,]+), ([^,]+), ([^,]+), ([^,)]+)\)\r?\n' % name, s))
    if t:
        if len(t) != 1 or not call: raise SystemExit('%s: T_PLAIN test needs a call expression' % name)
        g = t[0].groups()
        c = call
        for k, a in enumerate(g[3:7]): c = re.sub(r'\ba%d\b' % (k + 1), '(DWORD)(%s)' % a.strip(), c)
        # a function that returns a value keeps it compared; a void one returns 0 on its side (the original's eax is
        # then compared against 0: when that fails, check the callers with tools/eaxuse.py and wrap the original side)
        ret = c if void else '(DWORD)(%s)' % c
        new = 'ST(%s, %s, CALL_PLAIN(%s, %s, %s, %s, %s, %s), %s%s' % (name, g[1], g[0], g[2], g[3], g[4], g[5], g[6],
                                                             '(%s, 0))' % c if void else ret + ')', nl)
        s = s[:t[0].start()] + new + s[t[0].end():]
    else:
        st = list(re.finditer(r'ST\(%s, .*' % name, s))
        if len(st) != 1: raise SystemExit('%s: test not found once' % name)
        if void:
            line = st[0].group(0)
            mm = re.search(r', (%s\([^()]*(?:\([^()]*\)[^()]*)*\))\)\s*$' % name, line)
            if mm:
                line2 = line[:mm.start(1)] + '(%s, 0)' % mm.group(1) + line[mm.end(1):]
                s = s.replace(line, line2, 1)
    print('moved', name)
open(p, 'wb').write((b'\xef\xbb\xbf' if bom else b'') + s.encode())
b = open(p, 'rb').read(); print(b.count(b'\r\n'), b.count(b'\n'))
