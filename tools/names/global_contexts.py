r"""global_contexts.py [skip] [count]: the most-used globals src/ still writes as GAME_VAR(type, 0x...) without a
name, with their types and the comment text around each mention, for naming them"""
import collections, glob, re, sys
skip = int(sys.argv[1]) if len(sys.argv) > 1 else 0
count = int(sys.argv[2]) if len(sys.argv) > 2 else 60
uses, types, named, texts = collections.Counter(), collections.defaultdict(collections.Counter), set(), {}
for f in glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True):
    t = open(f).read(); texts[f] = t
    for m in re.finditer(r'#define\s+\w+\s+GAME_VAR\(\s*[\w ]+\*?\s*,\s*(0x[0-9a-f]+)\s*\)', t):
        named.add(int(m.group(1), 16))
    for m in re.finditer(r'GAME_VAR\(\s*([\w ]+\*?)\s*,\s*(0x[0-9a-f]{6,7})\s*\)', t):
        a = int(m.group(2), 16); uses[a] += 1; types[a][m.group(1).strip()] += 1
raw = sorted([(a, n) for a, n in uses.items() if a not in named], key=lambda x: -x[1])[skip:skip + count]
for a, n in raw:
    h = '0x%x' % a
    ctx = []
    for f, t in texts.items():
        for m in re.finditer(r'/\*(?:(?!\*/).)*?%s\b(?:(?!\*/).)*?\*/' % h, t, re.S):
            s = ' '.join(m.group(0).split()); i = s.find(h)
            ctx.append(s[max(0, i - 80):i + 30])
        for m in re.finditer(r'.*GAME_VAR\([^)]*%s\)[^\n]*' % h, t):
            line = m.group(0).strip()
            if '/*' in line:
                ctx.append('code: ' + line[-110:])
    print('%s %d %s' % (h, n, dict(types[a])))
    for c in ctx[:3]:
        print('    ', c)
