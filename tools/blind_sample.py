r"""mkblind.py: a random sample of functions, struct fields and globals, each shown with its code / uses with its own
name replaced by a placeholder and all comments removed; packets/batch_<i>.txt for the namers, key.tsv the answers"""
import glob, os, random, re
R = 'C:/Users/Alexander/Desktop/Axis/recomp/src/'
OUT = os.path.join(os.environ.get("TEMP", "."), "blind")   # (packets and key outside the repo)
random.seed(20261106)


def nocom(s):
    a, b = s.find('*/'), s.find('/*')
    if a != -1 and (b == -1 or a < b):   # (a snippet starting inside a comment)
        s = s[a + 2:]
    s = re.sub(r'/\*.*?\*/', '', s, flags=re.S)
    s = re.sub(r'/\*.*$', '', s, flags=re.S)   # (one ending inside a comment)
    s = re.sub(r'//[^\n]*', '', s)
    return re.sub(r'[ \t]+\n', '\n', s)


files = {}
for p in glob.glob(R + '**/*.c', recursive=True) + glob.glob(R + '**/*.h', recursive=True):
    q = p.replace(os.sep, '/')
    if '/data/' in q or q.endswith(('scene.h', 'globals.h', 'objects.h', 'calls.h', 'fn_syms.h')):
        continue
    raw_t = open(p, encoding='latin-1').read()
    files[q.split('/src/')[1]] = re.sub(r'/\*.*?\*/|//[^\n]*', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), raw_t, flags=re.S)   # (comments blanked, lines kept)

# ---- functions with bodies
FN = {}
for f, t in files.items():
    if not f.endswith('.c'):
        continue
    for m in re.finditer(r'^([^\n;{}()#/*]*?)\(\s*(\w+)\s*\)\s*\(([^;{]*?)\)\s*\{', t, re.M | re.S):
        i, d = m.end() - 1, 0
        for j in range(i, len(t)):
            d += t[j] == '{'
            d -= t[j] == '}'
            if d == 0:
                break
        FN[m.group(2)] = (f, m.start(), t[m.start():j + 1])


def sites(name, skip_def=None, n=4, ctx=4):
    out = []
    for f, t in sorted(files.items()):
        lines = t.split('\n')
        for k, l in enumerate(lines):
            if re.search(r'\b%s\b' % re.escape(name), nocom(l)) and not re.match(r'\s*#define\s+%s\b' % name, l):
                if skip_def and f == skip_def[0] and skip_def[1] <= sum(len(x) + 1 for x in lines[:k]) <= skip_def[2]:
                    continue
                out.append((f, k, '\n'.join(lines[max(0, k - ctx):k + ctx + 1])))
    random.shuffle(out)
    return out[:n]


def hide(s, name, ph):
    return re.sub(r'\b%s\b' % re.escape(name), ph, s)


items = []
cands = [n for n, (f, a, b) in FN.items() if 3 <= b.count('\n') <= 90 and not n.startswith(('crt_', '_'))]
for n in random.sample(sorted(cands), 50):
    f, a, body = FN[n]
    ph = 'FUNC_%d' % len(items)
    use = sites(n, (f, a, a + len(body)), n=3, ctx=3)
    txt = 'A FUNCTION (file %s). Its definition:\n%s\n' % (f, hide(nocom(body), n, ph).strip())
    for uf, k, s in use:
        txt += '\nCalled in %s:\n%s\n' % (uf, hide(nocom(s), n, ph).strip())
    items.append((ph, n, 'function', txt))

# ---- struct fields (names declared by one struct only)
decl = {}
cur = None
for l in open(R + 'scene.fields', encoding='latin-1'):
    m = re.match(r'struct (\w+) ', l)
    if m:
        cur = m.group(1); continue
    m = re.match(r'^(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+(.*?)\s*(#.*)?$', l.rstrip())
    if m and cur:
        nm = re.search(r'(\w+)\s*((?:\[[^\]]*\])*)$', m.group(3))
        if nm and not nm.group(1).startswith(('unused', 'cleared', 'pad', 'gap')):
            decl.setdefault(nm.group(1), []).append((cur, m.group(1), m.group(3)))
uniq = sorted(n for n, v in decl.items() if len(v) == 1)
picked = 0
for n in random.sample(uniq, len(uniq)):
    if picked == 40:
        break
    s, off, d = decl[n][0]
    use = [(f, k, x) for f, k, x in sites(n, n=6, ctx=3) if re.search(r'(->|\.)\s*%s\b|offsetof\([^)]*\b%s\b' % (n, n), x)]
    if len(use) < 1:
        continue
    ph = 'FIELD_%d' % len(items)
    txt = 'A FIELD of struct %s at offset %s, declared `%s`. Its uses:\n' % (s, off, hide(d, n, ph))
    for uf, k, x in use:
        txt += '\nIn %s:\n%s\n' % (uf, hide(nocom(x), n, ph).strip())
    items.append((ph, '%s.%s' % (s, n), 'field', txt))
    picked += 1

# ---- globals
G = []
for l in open(R + 'globals.h', encoding='latin-1'):
    m = re.match(r'#define (g_\w+) GAME_VAR\(([^,]+),\s*(0x[0-9a-f]+)\)', l)
    if m and not re.match(r'g_(unused|dik|key)', m.group(1)):
        G.append((m.group(1), m.group(2), m.group(3)))
picked = 0
for n, t, a in random.sample(G, len(G)):
    if picked == 30:
        break
    use = sites(n, n=6, ctx=3)
    if len(use) < 2:
        continue
    ph = 'GLOBAL_%d' % len(items)
    txt = 'A GLOBAL VARIABLE of type `%s` (address %s). Its uses:\n' % (t, a)
    for uf, k, x in use:
        txt += '\nIn %s:\n%s\n' % (uf, hide(nocom(x), n, ph).strip())
    items.append((ph, n, 'global', txt))
    picked += 1

random.shuffle(items)
os.makedirs(OUT + '/packets', exist_ok=True)
nb = 4
for b in range(nb):
    part = items[b::nb]
    with open(OUT + '/packets/batch_%d.txt' % b, 'w', encoding='utf-8') as f:
        for ph, n, kind, txt in part:
            f.write('=' * 100 + '\n' + ph + '\n' + txt + '\n')
with open(OUT + '/key.tsv', 'w', encoding='utf-8') as f:
    for ph, n, kind, txt in items:
        f.write('%s\t%s\t%s\n' % (ph, kind, n))
print(len(items), 'items;', sum(1 for i in items if i[2] == 'function'), 'functions', sum(1 for i in items if i[2] == 'field'),
      'fields', sum(1 for i in items if i[2] == 'global'), 'globals')
