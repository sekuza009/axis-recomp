r"""retype_uses.py [--dry] [file...]: every raw GAME_VAR(type, 0x...) of a global that has a name written with the
name: the names of src/globals.h and src/game.h everywhere, a file's own #define names where they are defined (from
the #define to its #undef; they win there). A use with another type than the name's (GAME_VAR(u32, 0x...) for a
float, say: the bits copied) becomes (*(type *)&name), the same access, so the generated code does not change
(check with objcmp.py). #define lines are left as they are."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
DEF = re.compile(r'^[ \t]*#define[ \t]+(\w+)[ \t]+GAME_VAR\(\s*([\w \*]+?)\s*,\s*(0x[0-9a-f]+)\s*\)[ \t]*(?:/\*.*)?$')
UNDEF = re.compile(r'^[ \t]*#undef[ \t]+(\w+)')
USE = re.compile(r'GAME_VAR\(\s*([\w \*]+?)\s*,\s*(0x[0-9a-f]+)\s*\)')


def norm(t):
	return re.sub(r'\s+', ' ', t.strip())


common = {}
for h in ('src/game.h', 'src/globals.h'):
	for line in open(h, 'rb').read().decode('latin-1').split('\n'):
		m = DEF.match(line.rstrip('\r'))
		if m:
			common[int(m.group(3), 16)] = (m.group(1), norm(m.group(2)))
files = [a for a in sys.argv[1:] if not a.startswith('--')] or sorted(glob.glob('src/**/*.[ch]', recursive=True))
total = 0
for f in files:
	if os.path.basename(f) in ('globals.h', 'game.h'):
		continue
	lines = open(f, 'rb').read().decode('latin-1').split('\n')
	scope = dict(common)   # address -> (name, type), as it stands at this line
	shadowed = {}          # name -> the address its #define took (to restore at #undef)
	n = [0]

	def sub(m):
		a = int(m.group(2), 16)
		if a not in scope:
			return m.group(0)
		name, typ = scope[a]
		t = norm(m.group(1))
		n[0] += 1
		return name if t == typ else '(*(%s%s*)&%s)' % (t, '' if t.endswith('*') else ' ', name)
	for i, line in enumerate(lines):
		d, u = DEF.match(line.rstrip('\r')), UNDEF.match(line)
		if d:
			a = int(d.group(3), 16)
			shadowed[d.group(1)] = (a, scope.get(a))
			scope[a] = (d.group(1), norm(d.group(2)))
			continue
		if u:
			if u.group(1) in shadowed:
				a, old = shadowed.pop(u.group(1))
				if old:
					scope[a] = old
				else:
					scope.pop(a, None)
			continue
		if re.match(r'\s*#define\s', line):
			continue
		lines[i] = USE.sub(sub, line)
	if n[0]:
		total += n[0]
		print('%-40s %d' % (f, n[0]))
		if '--dry' not in sys.argv:
			open(f, 'wb').write('\n'.join(lines).encode('latin-1'))
print(total, 'uses')
