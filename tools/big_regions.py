r"""big_regions.py [n]: the largest unnamed stretches of g_data (src/data/layout.h's _gap_ padding) that src/ still
refers into, with the references - candidates for naming as big objects (which can then be split and guarded)"""
import collections, glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
gaps = [(int(a, 16), int(n, 16)) for a, n in re.findall(r'u8 _gap_([0-9a-f]+)\[0x([0-9a-f]+)\]', open('src/data/layout.h').read())
        if int(a, 16) >= 0x4ad000]
refs = collections.Counter(); where = collections.defaultdict(list)
for f in glob.glob('src/**/*.[ch]', recursive=True):
	if os.path.basename(os.path.dirname(f)) == 'data':
		continue
	for line in open(f, encoding='latin-1'):
		for a in re.findall(r'(?<![\w+])\s?(0x[0-9a-f]{6})\b', line):
			v = int(a, 16)
			refs[v] += 1
			if len(where[v]) < 2:
				where[v].append(os.path.basename(f) + ': ' + line.strip()[:110])
for a, n in sorted(gaps, key=lambda g: -g[1])[:int(sys.argv[1]) if len(sys.argv) > 1 else 30]:
	inside = sorted((r, c) for r, c in refs.items() if a <= r < a + n)
	if inside:
		print('0x%06x %8d bytes  %3d refs at %s' % (a, n, sum(c for _, c in inside), ', '.join('0x%x' % r for r, _ in inside[:6])))
		print('      ' + where[inside[0][0]][0])
