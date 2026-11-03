r"""offset_names.py <Struct> <file.c>:<first>-<last> ... [--dry]: in the given lines (a table of field offsets), each
hex constant of at least 0x100000 that is exactly where a field of <Struct> starts (src/scene.fields) written as
offsetof(<Struct>, field). The same constant: the code and data do not change (check: tools/objcmp.py). Only for
tables whose entries are offsets into the struct (not addresses, sizes or counts) - give the lines by hand."""
import re, sys, os

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
args = [a for a in sys.argv[1:] if not a.startswith('--')]
STRUCT, specs = args[0], args[1:]
fields, cur = {}, None
for l in open('src/scene.fields', encoding='latin-1'):
	l = l.split('#')[0].strip()
	if not l:
		continue
	if l.startswith('struct'):
		cur = l.split()[1]
		continue
	off, size, decl = l.split(None, 2)
	m = re.match(r'(.+?)\s*\b(\w+)\s*((?:\[\w+\])*)$', decl)
	if m and cur == STRUCT:
		fields.setdefault(int(off, 16), m.group(2))
total = 0
for spec in specs:
	path, rng = spec.rsplit(':', 1)
	a, b = (int(x) for x in rng.split('-'))
	text = open(path, encoding='latin-1', newline='').read()
	lines = text.split('\n')
	for i in range(a - 1, b):
		def sub(m):
			global total
			v = int(m.group(0), 16)
			if v < 0x100000 or v not in fields:
				return m.group(0)
			total += 1
			return 'offsetof(%s, %s)' % (STRUCT, fields[v])
		lines[i] = re.sub(r'\b0x[0-9a-f]+\b', sub, lines[i])
	if '--dry' not in sys.argv:
		open(path, 'w', encoding='latin-1', newline='').write('\n'.join(lines))
print(total, 'offsets named')
