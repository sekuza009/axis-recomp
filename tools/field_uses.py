r"""field_uses.py Struct.field... [-C n]: every use of a scene.fields field in src by name (members after -> or ., and
offsetof), with the aliasing view too: a Scene field over the Stage region (Scene + 0x1f36c8) also shows the Stage
fields at those bytes and the other way round. -C n: n lines of context. For checking what a field does before
naming it."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
STAGE_IN_SCENE = 0x1f36c8
ctx = 0
args = sys.argv[1:]
if '-C' in args:
	i = args.index('-C'); ctx = int(args[i + 1]); del args[i:i + 2]

structs = {}
cur = None
for line in open('src/scene.fields', encoding='latin-1'):
	if line.startswith('struct '):
		cur = line.split()[1]; structs[cur] = []
		continue
	m = re.match(r'^(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+[\w ]+?\b(\w+)(\[[^\]]*\])?\s*(#.*)?$', line.rstrip())
	if m and cur:
		structs[cur].append((int(m.group(1), 0), int(m.group(2), 0), m.group(3), (m.group(5) or '').strip()))

files = [f for f in glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True)
         if os.path.basename(f) not in ('scene.h',) and os.sep + 'data' + os.sep not in f]
texts = {f: open(f, encoding='latin-1').read().split('\n') for f in files}


def show(name):
	pat = re.compile(r'(->|\.)\s*%s\b|offsetof\(\s*\w+\s*,\s*%s\b' % (name, name))
	n = 0
	for f, lines in texts.items():
		for i, l in enumerate(lines):
			if pat.search(l):
				n += 1
				lo, hi = max(0, i - ctx), min(len(lines), i + ctx + 1)
				for j in range(lo, hi):
					print('%s:%d:%s %s' % (f.replace(os.sep, '/'), j + 1, '>' if j == i else ' ', lines[j].strip()[:200]))
				if ctx:
					print('--')
	return n


def overlapping(struct, off, size):
	return [(o, s, n, c) for o, s, n, c in structs.get(struct, []) if o < off + size and off < o + s]


for a in args:
	st, name = a.split('.')
	hits = [x for x in structs[st] if x[2] == name]
	if not hits:
		print('no field', a); continue
	off, size, _, com = hits[0]
	print('=== %s.%s +%#x (%#x)  %s' % (st, name, off, size, com))
	n = show(name)
	print('  (%d uses by name; the name may be shared by other structs)' % n)
	other = []
	if st == 'Scene' and off >= STAGE_IN_SCENE:
		other = [('Stage',) + x for x in overlapping('Stage', off - STAGE_IN_SCENE, size)]
	elif st == 'Stage':
		other = [('Scene',) + x for x in overlapping('Scene', off + STAGE_IN_SCENE, size)]
	for s2, o, sz, n2, c in other:
		if n2 == name:
			continue
		print('  alias %s.%s +%#x  %s' % (s2, n2, o, c))
		show(n2)
