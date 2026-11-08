"""offset_scan.py: raw byte offsets still used in src (outside src/data) to reach into memory, by kind and file.
  python tools/offset_scan.py          counts
  python tools/offset_scan.py KIND     every line of that kind"""
import collections, glob, os, re, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
PAT = {
	# *(T *)(p + 0x10) / ((T *)(p + 0x10))[i]
	'CAST_DEREF': r'\*\s*\(\s*(?:const\s+)?\w+\s*\*+\s*\)\s*\(\s*\(?\s*(?:u8\s*\*\)\s*)?[\w>.\-\[\]]+\s*\+\s*0x[0-9a-f]+',
	# GAME_VAR(T, OBJ(g_x) + 0x10) / GAME_VAR(T, ADDR(g_x) + 0x10) / GAME_VAR(T, p + 0x10)
	'GAME_VAR_OFS': r'GAME_VAR\([^,()]+,\s*\(?\s*(?:OBJ|ADDR)?\(?\w+\)?\s*\+\s*0x[0-9a-f]+',
	# OBJ(g_x) + 0x10 / ADDR(g_x) + 0x10 anywhere else
	'GLOBAL_PLUS': r'\b(?:OBJ|ADDR)\(\w+\)\s*\+\s*(?:0x[0-9a-f]+|\d+)',
	# byte buffers: packet + 0x2c, buf[0x2b]
	'BYTE_PTR': r'\b(?:packet|pkt|buf|data|rec|record|msg|reply)\s*(?:\+\s*0x[0-9a-f]+|\[\s*0x[0-9a-f]+\s*\])',
	# FIELD(p, 0x10, T)-style helpers
	'FIELD_MACRO': r'\b(?:FIELD|F32|U32|I32|U16|U8|AT)\(\s*\w+\s*,\s*0x[0-9a-f]+',
}

def files():
	for f in sorted(glob.glob(os.path.join(R, 'src', '**', '*.c'), recursive=True)):
		rel = os.path.relpath(f, os.path.join(R, 'src')).replace(os.sep, '/')
		if not rel.startswith('data/'):
			yield rel, f

def lines(f):
	t = open(f, encoding='latin-1').read()
	t = re.sub(r'/\*.*?\*/', lambda m: '\n' * m.group(0).count('\n'), t, flags=re.S)
	return t.split('\n')

if len(sys.argv) > 1:
	p = re.compile(PAT[sys.argv[1]])
	for rel, f in files():
		for n, l in enumerate(lines(f), 1):
			if p.search(l):
				print('%s:%d: %s' % (rel, n, l.strip()[:200]))
	sys.exit()
tot = collections.Counter()
per = collections.defaultdict(collections.Counter)
for rel, f in files():
	for l in lines(f):
		for k, p in PAT.items():
			n = len(re.findall(p, l))
			if n:
				tot[k] += n
				per[k][rel] += n
for k in PAT:
	print('%6d %-13s %s' % (tot[k], k, ', '.join('%s=%d' % x for x in per[k].most_common(6))))
