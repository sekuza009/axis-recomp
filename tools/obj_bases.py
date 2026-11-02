r"""obj_bases.py [--dry]: GAME_VAR(type, 0x... + index) whose base is in a named object of src/objects.h written
GAME_VAR(type, OBJ(name) [+ offset] + index): the object's place in either build - so a table read by index follows
its object when it is split out of g_data (tools/names/split.txt). Only GAME_VAR's address (not S() / FIELD()
offsets). In the harness OBJ(name) is the address, so the objects do not change (check with objcmp.py)."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
SIZES = {'char': 1, 'u8': 1, 'signed char': 1, 'u16': 2, 'short': 2, 'int': 4, 'u32': 4, 'float': 4, 'double': 8, 'u64': 8, 'i64': 8, 'Colour': 16}
objs = []
for line in open('tools/names/objects.txt'):
	a, ty, n, name = line.split()
	objs.append((int(a, 16), int(a, 16) + SIZES[ty.replace('_', ' ')] * int(n), name))
total = 0
for f in sorted(glob.glob('src/**/*.[ch]', recursive=True)):
	if os.path.basename(os.path.dirname(f)) == 'data' or f.endswith(('axis.h', 'globals.h', 'objects.h')):
		continue
	t = open(f, 'rb').read().decode('latin-1')
	n = [0]
	def sub(m):
		a = int(m.group(2), 16)
		for lo, hi, name in objs:
			if lo <= a < hi:
				n[0] += 1
				return '%sOBJ(%s)%s +' % (m.group(1), name, ' + 0x%x' % (a - lo) if a > lo else '')
		return m.group(0)
	u = re.sub(r'(\bGAME_VAR\(\s*[\w \*]+?,\s*\(?\s*)(0x[0-9a-f]{6,7})\s*\+', sub, t)
	u = re.sub(r'(\b(?:I32|F32|F64)\(\s*\(?\s*)(0x[0-9a-f]{6,7})\s*\+', sub, u)   # (files' GAME_VAR wrappers)
	if n[0]:
		total += n[0]; print('%-40s %d' % (f, n[0]))
		if '--dry' not in sys.argv:
			open(f, 'wb').write(u.encode('latin-1'))
print(total, 'bases')
