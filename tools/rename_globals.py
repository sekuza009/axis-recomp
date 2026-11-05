r"""rename_globals.py old=new... : globals renamed everywhere they are spelled out - src (.c, .h, scene.fields; the
standalone layout's old_v copies too), tools/names, recomp.c, ../decomp/symbols.csv - as whole words, byte for byte
(CRLF kept). A new name already in use, or an old one used nowhere, stops the run before anything is written.
Then run python tools/mkdatasrc.py (the standalone layout) and check with tools/objcmp.py."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
pairs = [a.split('=', 1) for a in sys.argv[1:]]
files = [f for f in glob.glob('src/**/*.[ch]', recursive=True) + ['src/scene.fields', 'recomp.c', 'axisnet_recomp.c', '../decomp/symbols.csv']
         + glob.glob('tools/names/*') if os.path.isfile(f)]
texts = {f: open(f, encoding='latin-1', newline='').read() for f in files}
bad = 0
for old, new in pairs:
	if not any(re.search(r'\b%s\b' % re.escape(old), t) for t in texts.values()):
		print('not found:', old); bad += 1
	if any(re.search(r'\b%s(_v)?\b' % re.escape(new), t) for t in texts.values()):
		print('already in use:', new); bad += 1
if bad:
	sys.exit('%d problems, nothing renamed' % bad)
n = 0
for f, t in texts.items():
	u = t
	for old, new in pairs:
		u = re.sub(r'\b%s(_v)?\b' % re.escape(old), lambda m, new=new: new + (m.group(1) or ''), u)
	if u != t:
		open(f, 'w', encoding='latin-1', newline='').write(u)
		n += 1
print(len(pairs), 'names,', n, 'files changed')
