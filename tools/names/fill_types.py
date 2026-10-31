r"""fill_types.py in.txt out.csv: "address name" lines (# comments kept) into a name_globals.py CSV, each address
given the type src uses it with most (the other uses are left to retype_uses.py)"""
import collections, glob, re, sys

uses = collections.defaultdict(collections.Counter)
for f in glob.glob('src/**/*.c', recursive=True):
	for t, a in re.findall(r'GAME_VAR\(\s*([\w \*]+?)\s*,\s*(0x[0-9a-f]+)\s*\)', open(f, 'rb').read().decode('latin-1')):
		uses[int(a, 16)][re.sub(r'\s+', ' ', t)] += 1
out = []
for line in open(sys.argv[1]):
	s = line.strip()
	if not s or s.startswith('#'):
		out.append(s); continue
	a, name = s.split()[:2]
	c = uses.get(int(a, 16))
	if not c:
		print('no use of', a, name); continue
	out.append('%s,%s,%s' % (a, c.most_common(1)[0][0], name))
open(sys.argv[2], 'w', newline='\n').write('\n'.join(out) + '\n')
