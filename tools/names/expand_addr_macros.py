r"""expand_addr_macros.py [--dry]: a file's own address macros ("#define I(a) GAME_VAR(int, a)") used with a literal
address (I(0x4dcf00)) written out as GAME_VAR(int, 0x4dcf00), so that name_globals.py / retype_uses.py see them.
Uses with another argument keep the macro. The expansion is the macro's own, so the code does not change."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
DEF = re.compile(r'^[ \t]*#define[ \t]+(\w+)\(\s*(\w+)\s*\)[ \t]+GAME_VAR\(\s*([\w \*]+?)\s*,\s*\2\s*\)[ \t]*(?:/\*.*)?$')
UNDEF = re.compile(r'^[ \t]*#undef[ \t]+(\w+)')
total = 0
for f in sorted(glob.glob('src/**/*.c', recursive=True)):
	lines = open(f, 'rb').read().decode('latin-1').split('\n')
	macros, n = {}, 0
	for i, line in enumerate(lines):
		d, u = DEF.match(line.rstrip('\r')), UNDEF.match(line)
		if d:
			macros[d.group(1)] = d.group(3).strip()
			continue
		if u:
			macros.pop(u.group(1), None)
			continue
		if line.lstrip().startswith('#define'):
			continue
		for m, typ in macros.items():
			new = re.sub(r'(?<![\w.>])%s\(\s*(0x[0-9a-f]+)\s*\)' % m, lambda x: 'GAME_VAR(%s, %s)' % (typ, x.group(1)), line)
			if new != line:
				n += new.count('GAME_VAR(') - line.count('GAME_VAR(')
				line = new
		lines[i] = line
	if n:
		total += n
		print('%-40s %d' % (f, n))
		if '--dry' not in sys.argv:
			open(f, 'wb').write('\n'.join(lines).encode('latin-1'))
print(total, 'uses')
