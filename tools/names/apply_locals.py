"""apply_locals.py [-n] REPO edits.tsv...: rename locals inside one function each (file, function, old, new).
Every word `old` in the function (definition line to closing brace), except member accesses (.old / ->old);
line endings kept. Skipped and reported: function not found (NOFN), `new` already used there (CLASH), `old`
declared more than once there (MULTI: a shadowing / second local - do by hand). -n: dry run."""
import re, sys

DRY = sys.argv[1] == '-n'
if DRY:
    sys.argv.pop(1)
R = sys.argv[1]
edits = []
for p in sys.argv[2:]:
    for line in open(p, encoding='latin-1'):
        f = line.rstrip('\r\n').split('\t')
        if len(f) >= 4 and f[0].startswith('src/'):
            edits.append(f[:4])
byfile = {}
for e in edits:
    byfile.setdefault(e[0], []).append(e)
TYPE = r'(?:\b(?:int|u8|u16|u32|s8|s16|s32|float|double|char|long|short|unsigned|void|X|[A-Z]\w*)\b[\s*]+(?:const\s+)?)'
bad = 0
for path, es in byfile.items():
    full = R + '/' + path
    t = open(full, encoding='latin-1', newline='').read()
    for _, fn, old, new in es:
        m = None
        for mm in re.finditer(r'(?m)^(?![\s#/])[^\n;]*?(?:\(%s\)|\b%s)\s*\(' % (re.escape(fn), re.escape(fn)), t):
            brace, semi = t.find('{', mm.end()), t.find(';', mm.end())
            if brace != -1 and (semi == -1 or brace < semi):
                m = mm
                break
        if not m:
            print('NOFN', path, fn, old, new); bad += 1; continue
        start = t.find('{', m.end())
        d, i = 0, start
        while i < len(t):
            if t[i] == '{':
                d += 1
            elif t[i] == '}':
                d -= 1
                if d == 0:
                    break
            i += 1
        body = t[m.start():i + 1]
        if re.search(r'(?<![\w.>])%s\b' % re.escape(new), body):
            print('CLASH', path, fn, old, new); bad += 1; continue
        decls = re.findall(TYPE + r'\b%s\s*(?:=|;|,|\[)' % re.escape(old), body)
        if len(decls) > 1:
            print('MULTI', len(decls), path, fn, old, new); bad += 1; continue
        if DRY:
            print('ok', path, fn, old, new, len(decls)); continue
        parts = re.split(r'(/[*].*?[*]/|//[^\n]*|"(?:[^"\\]|\\.)*")', body, flags=re.S)
        n = 0
        for k in range(0, len(parts), 2):
            parts[k], c = re.subn(r'(?<![\w.])(?<!->)\b%s\b' % re.escape(old), new, parts[k])
            n += c
        nb = ''.join(parts)
        t = t[:m.start()] + nb + t[i + 1:]
        print('%3d %s %s %s -> %s' % (n, path, fn, old, new))
    if not DRY:
        open(full, 'w', encoding='latin-1', newline='').write(t)
print('problems:', bad)
