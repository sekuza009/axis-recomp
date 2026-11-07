"""list_locals.py REPO out.tsv: every local variable declared inside a function in src/ (not src/data), with the
function it's in: file:line  function  name  declaration. Short throwaway names (i, j, n, p, x, ...: <= 2 letters,
or a common working name) are left out."""
import glob, os, re, sys
R = sys.argv[1]
SKIP = set('''i j k n m p q s t x y z a b c d e f g h r u v w ok tmp res ret len idx cnt num val buf ptr src dst out
in end beg cur prev next lo hi row col pos off sz rc hr dw it pp sp ap fp lp bp tp np vp cp dp'''.split())
TYPES = r'(?:const\s+|static\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|long\s+)*[A-Za-z_]\w*'
DECL = re.compile(r'^\s+(' + TYPES + r')((?:\s*\*+\s*|\s+)(?:const\s+)?)([A-Za-z_]\w*)\s*(\[[^\]]*\])*\s*(=|;|,|\[)')
KW = {'return', 'goto', 'case', 'else', 'do', 'break', 'continue', 'sizeof', 'if', 'while', 'for', 'switch', 'default'}
FN = re.compile(r'^(?![\s#/{}])[^\n;=]*?(?:\((\w+)\)|(\w+))\s*\([^;]*$')
out = []
for f in sorted(glob.glob(os.path.join(R, 'src', '**', '*.c'), recursive=True)):
    rel = os.path.relpath(f, R).replace(os.sep, '/')
    if rel.startswith('src/data/'):
        continue
    depth, fn = 0, '?'
    for i, line in enumerate(open(f, encoding='latin-1'), 1):
        s = line.rstrip('\n')
        if depth == 0:
            m = FN.match(s)
            if m:
                fn = m.group(1) or m.group(2)
        elif depth > 0:
            code = s.split('//')[0]
            m = DECL.match(code)
            if m and m.group(1).split()[-1] not in KW and m.group(3) not in KW:
                names = [m.group(3)]
                # further names on a comma list (int a = 1, b, *c;)
                rest = code[m.end(3):]
                if '(' not in rest.split('=')[0]:
                    for extra in re.findall(r',\s*\**\s*([A-Za-z_]\w*)\s*(?=[=;,\[])', re.sub(r'\([^()]*\)', '', rest)):
                        names.append(extra)
                for n in names:
                    if n.lower() in SKIP or len(n) <= 2:
                        continue
                    out.append('%s:%d\t%s\t%s\t%s' % (rel, i, fn, n, s.strip()[:150]))
        depth += s.count('{') - s.count('}')
        if depth < 0:
            depth = 0
open(sys.argv[2], 'w', encoding='latin-1').write('\n'.join(out) + '\n')
print(len(out), 'locals;', len(set((o.split('\t')[1], o.split('\t')[2]) for o in out)), 'distinct per function')
