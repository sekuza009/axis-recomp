r"""code_offsets.py [--list] [--file=SUBSTR]: what is left of raw record access in the code (comments and strings
left out): GAME_VAR / FIELD / *(T *)(p + k) reads and writes at a constant offset, array indexing by byte strides
(p + i * 0x..), and struct casts ((T *)x)->f. Prints counts per kind and per file; --list the lines."""
import os, re, glob, sys, collections
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
listing = '--list' in sys.argv
only = next((a.split('=', 1)[1] for a in sys.argv if a.startswith('--file=')), None)
KINDS = {
	'GAME_VAR offset': re.compile(r'GAME_VAR\([^,()]+(?:\([^()]*\))?[^,()]*,\s*[^)]*?\+\s*(0x[0-9a-f]+|\d{2,})\b'),
	'FIELD': re.compile(r'\bFIELD\('),
	'cast deref offset': re.compile(r'\*\s*\(\s*\w[\w\s]*\*+\s*\)\s*\(\s*[\w>.\-\[\]]+\s*\+\s*(0x[0-9a-f]+|\d{2,})\s*\)'),
	'byte stride': re.compile(r'\+\s*\(?\s*\w+\s*\*\s*0x[0-9a-f]{2,}\b'),
	'struct cast ->': re.compile(r'\(\(\s*[A-Z]\w*\s*\*\s*\)\s*[\w>.\-\[\]()]+\)\s*->'),
}


def strip(t):
	t = re.sub(r'/\*.*?\*/', lambda m: ' ' * len(m.group(0)), t, flags=re.S)
	t = re.sub(r'"(?:\\.|[^"\\])*"', '""', t)
	return t


counts = collections.Counter()
perfile = collections.defaultdict(collections.Counter)
for p in sorted(glob.glob('src/**/*.c', recursive=True)):
	if 'data' in os.path.dirname(p) or (only and only not in p.replace('\\', '/')):
		continue
	t = strip(open(p, encoding='latin-1').read())
	for n, line in enumerate(t.split('\n'), 1):
		if line.lstrip().startswith('#define') or 'STR(' in line and False:
			continue
		for k, rx in KINDS.items():
			c = len(rx.findall(line))
			if c:
				counts[k] += c
				perfile[os.path.basename(p)][k] += c
				if listing:
					print('%s:%d [%s] %s' % (os.path.basename(p), n, k, line.strip()[:150]))
for k, c in counts.items():
	print('%-20s %d' % (k, c))
if not listing:
	for f, c in sorted(perfile.items(), key=lambda x: -sum(x[1].values()))[:25]:
		print('%-24s %s' % (f, dict(c)))
