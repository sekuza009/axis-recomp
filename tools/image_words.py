"""image_words.py: words in src/data that hold an address of the original's image (0x401000 .. 0xb6b000) as a plain
number - what a relocatable build must turn into real pointers - by file and by what they point at (a named global
from globals.h / objects.h, a rebuilt function, a string, or nothing known)."""
import collections, glob, os, re

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
names = {}
for h in ('globals.h', 'objects.h'):
	for m in re.finditer(r'#define (\w+) (?:GAME_VAR\([^,]+, |\(\([\w ]+\s*\*\)IMG\()(0x[0-9a-f]+)', open(os.path.join(R, 'src', h), encoding='latin-1').read()):
		names[int(m.group(2), 16)] = m.group(1)
fns = {int(a, 16): n for n, a in re.findall(r'#define FNADDR_(\w+) (0x[0-9a-f]+)', open(os.path.join(R, 'src', 'fn_addrs.h')).read())}
kinds = collections.Counter()
per = collections.Counter()
for f in glob.glob(os.path.join(R, 'src', 'data', '*.c')):
	t = open(f, encoding='latin-1').read()
	t = re.sub(r'/\*.*?\*/', '', t, flags=re.S)
	for m in re.finditer(r'\b0x([0-9a-f]{8})\b', t):
		v = int(m.group(1), 16)
		if not 0x401000 <= v < 0xb6b000:
			continue
		if v in fns:
			k = 'a rebuilt function'
		elif v in names:
			k = 'a named global'
		elif 0x4a9000 <= v < 0x4ad000:
			k = 'read-only data (strings, tables)'
		elif v < 0x4a9000:
			k = 'code (not rebuilt / inside a function)'
		else:
			k = 'data, unnamed spot'
		kinds[k] += 1
		per[os.path.basename(f)] += 1
print('image addresses as numbers in src/data:', sum(kinds.values()))
for k, n in kinds.most_common():
	print('  %5d  %s' % (n, k))
print('by file:', dict(per))
