r"""global_uses.py [minuses]: each unnamed global (used at least minuses times) with the functions that use it and
the code lines it appears on - for naming it from what the code does with it"""
import collections, glob, re, sys
minu = int(sys.argv[1]) if len(sys.argv) > 1 else 2
named, uses, texts = set(), collections.defaultdict(list), {}
for f in glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True):
    t = open(f).read(); texts[f] = t
    for m in re.finditer(r'#define\s+\w+\s+GAME_VAR\(\s*[\w ]+\*?\s*,\s*(0x[0-9a-f]+)\s*\)', t):
        named.add(int(m.group(1), 16))
for f, t in texts.items():
    if f.endswith('.h'):
        continue
    funcs = [(m.start(), m.group(1)) for m in re.finditer(r'^\w[\w \*]*?\((\w+)\)\(', t, re.M)]
    for m in re.finditer(r'GAME_VAR\(\s*([\w ]+\*?)\s*,\s*(0x[0-9a-f]{6,7})\s*\)', t):
        a = int(m.group(2), 16)
        if a in named:
            continue
        fn = '?'
        for pos, name in funcs:
            if pos < m.start():
                fn = name
        ls = t.rfind('\n', 0, m.start()) + 1; le = t.find('\n', m.start())
        uses[a].append((fn, m.group(1).strip(), t[ls:le].strip()))
for a in sorted(uses, key=lambda a: -len(uses[a])):
    if len(uses[a]) < minu:
        continue
    fns = collections.Counter(u[0] for u in uses[a])
    print('0x%x %d %s | %s' % (a, len(uses[a]), dict(collections.Counter(u[1] for u in uses[a])), ', '.join(fns)))
    for u in uses[a][:3]:
        print('     ', u[2][:150])
