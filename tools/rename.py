r"""rename.py mapping.csv [--dry]: rename functions everywhere they are spelled out.

Each line of the mapping is "old,new" ('#' starts a comment). Whole-word replacement in src/**/*.c, src/**/*.h,
recomp.c (its declarations, tests and hook table) and ../decomp/symbols.csv (so a Ghidra re-export matches), byte for
byte, so CRLF and LF files keep their line endings. A new name that already appears anywhere, an old name that does
not, or a name used twice in the mapping stops the whole run before anything is written."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
pairs = []
for line in open(sys.argv[1], encoding='utf-8'):
    line = line.split('#', 1)[0].strip()
    if line:
        old, new = [x.strip() for x in line.split(',')]
        pairs.append((old, new))
files = sorted(glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True)) + ['recomp.c']
if os.path.exists('../decomp/symbols.csv'):
    files.append('../decomp/symbols.csv')
data = {f: open(f, 'rb').read() for f in files}
allt = b'\n'.join(data.values())
olds, news, bad = set(), set(), 0
for old, new in pairs:
    if not re.fullmatch(r'[A-Za-z_]\w*', new):
        print('bad name:', new); bad += 1
    if old in olds or new in news or new in olds:
        print('used twice:', old, new); bad += 1
    olds.add(old); news.add(new)
    if not re.search(rb'\b(su_|or_|nw_)?%s\b' % old.encode(), allt):
        print('not found:', old); bad += 1
    if re.search(rb'\b(su_|or_|nw_)?%s\b' % new.encode(), allt):
        print('already exists:', new); bad += 1
if bad:
    sys.exit('%d problems, nothing renamed' % bad)
# the harness pastes su_ / or_ / nw_ onto a test's name (its setup, original and rebuilt runs)
pat = re.compile(rb'\b(su_|or_|nw_)?(%s)\b' % b'|'.join(re.escape(o.encode()) for o, _ in pairs))
table = {o.encode(): n.encode() for o, n in pairs}
changed = 0
for f, t in data.items():
    u = pat.sub(lambda m: (m.group(1) or b'') + table[m.group(2)], t)
    if u != t:
        changed += 1
        if '--dry' not in sys.argv:
            open(f, 'wb').write(u)
print('%d names, %d files %s' % (len(pairs), changed, 'would change' if '--dry' in sys.argv else 'changed'))
