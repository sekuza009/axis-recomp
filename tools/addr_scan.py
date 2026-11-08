"""addr_scan.py: raw addresses still written in src (outside src/data), by kind, with the files that have the most.
  python tools/addr_scan.py            counts per kind
  python tools/addr_scan.py KIND       every line of that kind (KIND: a key of PAT, e.g. STR)"""
import collections, glob, os, re, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
PAT = {
	'STR': r'\bSTR\(0x[0-9a-f]+',
	'FN_ADDR': r'\bFN_ADDR\(\w+,\s*0x[0-9a-f]+',
	'IMPORT': r'\bIMPORT\(0x[0-9a-f]+',
	'GAME_FN': r'\bGAME_(?:THIS)?FN\(\w+,\s*0x[0-9a-f]+',
	'CALL': r'\bCALL_\w+\(0x[0-9a-f]+',
	'IMG': r'\bIMG\(0x[0-9a-f]+',
	'GAME_VAR': r'GAME_VAR\([^,()]+,\s*0x[0-9a-f]+',
	'RELOC': r'\bRELOC\(0x[0-9a-f]+',
	'BARE': r'(?<![\w(,] )(?<![\w(])0x4[0-9a-f]{5}\b',
}

def files():
	for f in sorted(glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True)):
		rel = os.path.relpath(f, os.path.join(R, 'src')).replace(os.sep, '/')
		if not rel.startswith('data/'):
			yield rel, f

def strip_comments(line, state):
	out = ''
	i = 0
	while i < len(line):
		if state[0]:
			j = line.find('*/', i)
			if j < 0:
				return out
			state[0] = False
			i = j + 2
		else:
			j = line.find('/*', i)
			if j < 0:
				return out + line[i:]
			out += line[i:j]
			state[0] = True
			i = j + 2
	return out

if len(sys.argv) > 1:
	p = re.compile(PAT[sys.argv[1]])
	for rel, f in files():
		st = [False]
		for n, line in enumerate(open(f, encoding='latin-1'), 1):
			if p.search(strip_comments(line, st)):
				print('%s:%d: %s' % (rel, n, line.strip()[:200]))
	sys.exit()
tot = collections.Counter()
per = collections.defaultdict(collections.Counter)
for rel, f in files():
	st = [False]
	for line in open(f, encoding='latin-1'):
		code = strip_comments(line, st)
		for k, p in PAT.items():
			n = len(re.findall(p, code))
			if n:
				tot[k] += n
				per[k][rel] += n
for k in PAT:
	print('%6d %-9s %s' % (tot[k], k, ', '.join('%s=%d' % x for x in per[k].most_common(5))))
