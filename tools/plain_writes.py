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
	if nt != t and '--dry' not in sys.argv:
		open(path, 'w', encoding='latin-1', newline='').write(nt)
print(total, 'writes made plain')
