"""vtables_by_name.py: src/vtables.h, each class's vtable address in .rdata as VTADDR_<Class>, collected from src's
VT(Class, 0x...) (tools/img_vtables.py writes those), which then become VT(Class) (src/axis.h). Run again after
img_vtables.py adds any: the classes already in vtables.h are kept. The generated code is unchanged."""
import glob, os, re, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
path = os.path.join(R, 'src', 'vtables.h')
vt = {}
if os.path.exists(path):
	vt = {c: int(a, 16) for c, a in re.findall(r'#define VTADDR_(\w+) (0x[0-9a-f]+)', open(path).read())}
files = [p for p in glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True)
         if not os.path.relpath(p, os.path.join(R, 'src')).replace(os.sep, '/').startswith('data/')]
for p in files:
	for c, a in re.findall(r'\bVT\((\w+), (0x[0-9a-f]+)\)', open(p, encoding='latin-1').read()):
		if vt.setdefault(c, int(a, 16)) != int(a, 16):
			sys.exit('two vtables for %s: 0x%x and %s' % (c, vt[c], a))
lines = ['/* vtables.h (tools/vtables_by_name.py): each class\'s vtable in .rdata, VTADDR_<Class> - VT(Class) in src/axis.h',
         '   (self[0] = VT(Scene) in a constructor) */', '#pragma once']
lines += ['#define VTADDR_%s 0x%x' % (c, a) for c, a in sorted(vt.items(), key=lambda x: x[1])]
open(path, 'w', newline='\n').write('\n'.join(lines) + '\n')
changed = 0
for p in files:
	t = open(p, encoding='latin-1', newline='').read()
	u = re.sub(r'\bVT\((\w+), 0x[0-9a-f]+\)', r'VT(\1)', t)
	if u != t:
		open(p, 'w', encoding='latin-1', newline='').write(u)
		changed += 1
print('%d classes, %d files changed' % (len(vt), changed))
