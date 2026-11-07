import glob, os, re, sys
R = sys.argv[1]
out = []
files = glob.glob(os.path.join(R, 'src', '**', '*.c'), recursive=True) + glob.glob(os.path.join(R, 'src', '**', '*.h'), recursive=True)
for f in sorted(files):
    rel = os.path.relpath(f, R).replace(os.sep, '/')
    if rel.startswith('src/data/'):
        continue
    depth = 0
    for i, line in enumerate(open(f, encoding='latin-1'), 1):
        s = line.rstrip()
        if depth == 0 and s and not s[0].isspace() and s[0] not in '#/}*{' and not s.startswith('typedef') and not s.startswith('extern'):
            m = re.match(r'^(?:static\s+)?(?:const\s+)?(?:volatile\s+)?(?:unsigned\s+|signed\s+|struct\s+)?[A-Za-z_]\w*(?:\s+const)?[\s*]+(?:const\s+)?\**\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])*\s*(=|;|\[)', s)
            if m and '(' not in s.split('=')[0]:
                out.append('%s:%d\t%s\t%s' % (rel, i, m.group(1), s[:160]))
        depth += s.count('{') - s.count('}')
open(sys.argv[2], 'w').write('\n'.join(out) + '\n')
print(len(out))
