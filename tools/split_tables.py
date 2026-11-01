r"""split_tables.py: the tables (static initialisers) that hold named globals' addresses (ADDR(name)) - the reason
tools/split_candidates.py holds those globals back - grouped by table: file:line, the table's declaration, and
the globals in it. A table whose code only reads / writes each entry's one value can be listed in
tools/names/split_tables_ok.txt (file:table name), which split_candidates.py then accepts."""
import collections, glob, os, re

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
names = set(re.findall(r'#define (\w+) GAME_VAR\([\w \*]+, 0x[0-9a-f]+\)', open('src/globals.h').read()))
tables = collections.OrderedDict()
for f in sorted(glob.glob('src/**/*.c', recursive=True)):
	if os.sep + 'data' + os.sep in f:
		continue
	text = open(f, 'rb').read().decode('latin-1')
	for m in re.finditer(r'(\b[\w \*]+?\b(\w+)\s*(?:\[[^\]]*\])*)\s*=\s*\{', text):
		# the initialiser: balanced braces from here
		i, depth = m.end() - 1, 0
		for j in range(i, len(text)):
			depth += {'{': 1, '}': -1}.get(text[j], 0)
			if depth == 0:
				break
		body = text[i:j + 1]
		inside = [n for n in re.findall(r'\bADDR\((\w+)\)', body) if n in names]
		if inside:
			line = text.count('\n', 0, m.start()) + 1
			tables[(f.replace(os.sep, '/'), m.group(2))] = (line, ' '.join(m.group(1).split())[:70], inside)
if __name__ == '__main__':
	for (f, t), (line, decl, inside) in tables.items():
		print('%s:%d %s: %d - %s' % (f, line, decl, len(inside), ' '.join(inside)[:150]))
