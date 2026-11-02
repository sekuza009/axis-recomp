r"""img_names.py [--dry]: an address of the image that is a named global's (src/globals.h) written with its name:
IMG(0x4ded68) -> ADDR(g_mouseX), (u32)&g_mouseX (src/axis.h). In the harness that is the original address as
before (its objects do not change: check with objcmp.py); in AxisRC.exe the global's place (a member of g_rdata /
g_data, src/data/layout_names.h). Where two names share an address, the one listed first in globals.h."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
names = {}
for n, a in re.findall(r'#define (\w+) GAME_VAR\([\w \*]+, (0x[0-9a-f]+)\)', open('src/globals.h').read()):
	names.setdefault(int(a, 16), n)
total = 0
for f in sorted(glob.glob('src/**/*.[ch]', recursive=True)):
	if os.path.basename(os.path.dirname(f)) == 'data' or f.endswith(('globals.h', 'axis.h', 'objects.h')):   # (objects.h: the objects' own IMG definitions stay)
		continue
	t = open(f, 'rb').read().decode('latin-1')
	n = [0]

	def sub(m):
		a = int(m.group(1), 16)
		if a not in names:
			return m.group(0)
		n[0] += 1
		return 'ADDR(%s)' % names[a]
	# (not inside a #define of that same name, nor where a file names it itself)
	out = []
	for line in t.split('\n'):
		if re.match(r'\s*#define\s+\w+\s', line) and re.search(r'GAME_VAR\(', line):
			out.append(line); continue
		out.append(re.sub(r'\bIMG\((0x[0-9a-f]+)\)', sub, line))
	if n[0]:
		total += n[0]
		print('%-40s %d' % (f, n[0]))
		if '--dry' not in sys.argv:
			open(f, 'wb').write('\n'.join(out).encode('latin-1'))
print(total, 'addresses named')
