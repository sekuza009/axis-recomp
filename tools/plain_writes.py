r"""plain_writes.py <file.c>... [--dry]: a statement that writes an integer field through the other signedness,
    (*(u32 *)&AC->player) = pp[0];
written as the plain assignment, AC->player = pp[0]; (the same bits stored: int and u32 are the same size and the
value converts without change of its bits). Only for fields src/scene.fields types i32 / u32, through the pointer
names the struct tools use (AC Player, SC / GS Scene, ST / STS Stage, BU Bullet, WI ActorInfo, PR Projectile);
never a float field (that would convert the value). Check: tools/objcmp.py."""
import re, sys, os

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
PTRS = {'AC': 'Player', 'SC': 'Scene', 'GS': 'Scene', 'ST': 'Stage', 'STS': 'Stage', 'BU': 'Bullet', 'WI': 'ActorInfo',
        'PR': 'Projectile'}
types, cur = {}, None
for l in open('src/scene.fields', encoding='latin-1'):
	l = l.split('#')[0].strip()
	if not l:
		continue
	if l.startswith('struct'):
		cur = l.split()[1]; continue
	m = re.match(r'\S+\s+\S+\s+(.+?)\s*\b(\w+)\s*(?:\[\w+\])*$', l)
	if m:
		types[(cur, m.group(2))] = m.group(1).strip()
def nice_float(w):
	"""a float's bit pattern as its shortest exact literal, written out (None: no plain one)"""
	import struct, math
	f = struct.unpack('<f', struct.pack('<I', w))[0]
	if not math.isfinite(f) or not (1e-6 <= abs(f) <= 1e9):
		return None
	for p in range(1, 9):
		s = '%.*g' % (p, f)
		if struct.unpack('<I', struct.pack('<f', float(s)))[0] == w:
			if 'e' in s:
				s = ('%.10f' % float(s)).rstrip('0')
			s = s if '.' in s else s + '.0'
			return (s + '0' if s.endswith('.') else s) + 'f'
	return None


total = 0
for path in [a for a in sys.argv[1:] if not a.startswith('--')]:
	t = open(path, encoding='latin-1', newline='').read()

	def sub(m):
		global total
		ptr, field = m.group(3), m.group(4)
		ty = types.get((PTRS.get(ptr), field))
		if ty not in ('i32', 'u32'):
			return m.group(0)
		total += 1
		return '%s%s->%s%s = ' % (m.group(1), ptr, field, m.group(5))

	nt = re.sub(r'(?m)((?:^|[;{}])[ \t]*)\(\*\((u32|int) \*\)&(\w+)->(\w+)((?:\[[^\]]+\])?)\) = ', sub, t)

	# a float field written with its bits as its own statement: BITS(X->f) = 0x41200000; -> X->f = 10.0f; and
	# (*(int *)&X->f) = 0; -> X->f = 0.0f; (the same store)
	def flt(m):
		global total
		ptr, field, idx, bits = m.group(2), m.group(3), m.group(4), m.group(5)
		if types.get((PTRS.get(ptr), field)) != 'float':
			return m.group(0)
		v = '0.0f' if bits == '0' else nice_float(int(bits, 16))
		if not v:
			return m.group(0)
		total += 1
		return '%s%s->%s%s = %s;' % (m.group(1), ptr, field, idx, v)

	for head in (r'BITS\((\w+)->(\w+)((?:\[[^\]]+\])?)\)', r'\(\*\((?:int|u32) \*\)&(\w+)->(\w+)((?:\[[^\]]+\])?)\)'):
		nt = re.sub(r'(?m)((?:^|[;{}])[ \t]*)%s = (0x[0-9a-f]{8}|0);' % head, flt, nt)
	if nt != t and '--dry' not in sys.argv:
		open(path, 'w', encoding='latin-1', newline='').write(nt)
print(total, 'writes made plain')
