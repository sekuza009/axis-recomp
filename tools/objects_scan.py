r"""objects_scan.py [--list N]: the unnamed objects of the game's data that src/ reaches by IMG(0x...) - each distinct
address with its uses, the types it is cast to, and an extent where the code states one:
  memset / memcpy / memmove / strncpy (..., IMG(a) ..., n)   -> at least n bytes from a
  for (... = IMG(a); ... < IMG(b); ... += s)                   -> a .. b, stride s
  (T *)IMG(a) ... [k] with k a literal                        -> at least (k + 1) * sizeof T
The base for step 3b: naming these as arrays / records with their extents."""
import collections, glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
named = {int(a, 16) for a in re.findall(r'GAME_VAR\([\w \*]+, (0x[0-9a-f]+)\)', open('src/globals.h').read())}
uses = collections.defaultdict(list); casts = collections.defaultdict(collections.Counter); ext = collections.defaultdict(int)
loops = {}
for f in glob.glob('src/**/*.[ch]', recursive=True):
	if os.path.basename(os.path.dirname(f)) == 'data':
		continue
	t = open(f, encoding='latin-1').read()
	for m in re.finditer(r'\bIMG\((0x[0-9a-f]+)\)', t):
		a = int(m.group(1), 16)
		if a in named or a < 0x4a9000:
			continue
		ls = t.rfind('\n', 0, m.start()) + 1; le = t.find('\n', m.end())
		line = t[ls:le]
		uses[a].append(os.path.basename(f) + ': ' + line.strip()[:120])
		c = re.search(r'\(((?:const\s+)?[\w ]+?\s*\*+)\)\s*\(?\s*$', t[ls:m.start()])
		if c:
			casts[a][re.sub(r'\s+', ' ', c.group(1).replace('const ', ''))] += 1
	for m in re.finditer(r'\b(memset|memcpy|memmove|strncpy|crt_strncpy)\(([^;]*?)\);', t):
		args = m.group(2)
		n = re.search(r',\s*(0x[0-9a-f]+|\d+)\s*$', args)
		if not n:
			continue
		size = int(n.group(1), 0)
		for a in re.findall(r'IMG\((0x[0-9a-f]+)\)(?!\s*\+)', args):
			ext[int(a, 16)] = max(ext[int(a, 16)], size)
	for m in re.finditer(r'for \(\w+ \w+ = IMG\((0x[0-9a-f]+)\)[^;]*;\s*\w+ <=? IMG\((0x[0-9a-f]+)\);\s*\w+ \+= (0x[0-9a-f]+|\d+)', t):
		a, b, s = int(m.group(1), 16), int(m.group(2), 16), int(m.group(3), 0)
		loops[a] = (b, s); ext[a] = max(ext[a], b - a)
addrs = sorted(uses)
dat = [a for a in addrs if a >= 0x4ad000]; rd = [a for a in addrs if a < 0x4ad000]
print('distinct unnamed addresses: %d (.data %d, .rdata %d); uses %d; with an extent from the code: %d; loops %d' % (
	len(addrs), len(dat), len(rd), sum(len(v) for v in uses.values()), sum(1 for a in addrs if ext[a]), len(loops)))
hist = collections.Counter(min(len(uses[a]), 10) for a in addrs)
print('uses per address:', dict(sorted(hist.items())))
if '--list' in sys.argv:
	k = int(sys.argv[sys.argv.index('--list') + 1])
	for a in sorted(addrs, key=lambda a: -len(uses[a]))[:k]:
		print('0x%06x %3d uses  %-24s ext %-6s %s' % (a, len(uses[a]), ','.join('%s:%d' % x for x in casts[a].most_common(2)),
		      hex(ext[a]) if ext[a] else '-', uses[a][0][:100]))
