r"""scene_fields.py <file.c> [--dry]: a file's scene accesses by offset, S(type, 0x234240d), written as the Scene
field there, SC->localPlayer (SC: the file's scene pointer as a Scene *, defined next to its S macro), where
src/scene.fields names one of the access's own type (int / i32 alike; an array's element by its index). Accesses
of another type than the field's (an int read as a float ...) stay as they are and are listed, as are offsets with
no field yet (add them to scene.fields, run tools/mkscene.py, then this again)."""
import re, sys, os, collections

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
path = [a for a in sys.argv[1:] if not a.startswith('--')][0]

SAME = {'int': 'i32', 'i32': 'i32', 'u32': 'u32', 'float': 'float', 'u8': 'u8', 'char': 'char', 'i8': 'i8',
        'signed char': 'i8', 'u16': 'u16', 'i16': 'i16', 'short': 'i16', 'double': 'double', 'void *': 'void *'}
SIZE = {'i32': 4, 'u32': 4, 'float': 4, 'u8': 1, 'char': 1, 'i8': 1, 'u16': 2, 'i16': 2, 'double': 8, 'void *': 4}

fields = {}   # offset -> (name, element type, element size, count or None)
cur = None
for l in open('src/scene.fields', encoding='latin-1'):
	l = l.split('#')[0].strip()
	if not l:
		continue
	if l.startswith('struct'):
		cur = l.split()[1]; continue
	if cur != 'Scene':
		continue
	off, size, decl = l.split(None, 2)
	m = re.match(r'(.+?)\s*\b(\w+)\s*(?:\[(\w+)\])?$', decl)
	if not m:
		continue
	ty, name, count = m.group(1).strip(), m.group(2), m.group(3)
	if ty not in SIZE:
		continue
	off, n = int(off, 16), int(count, 0) if count else None
	for k in range(n or 1):
		fields[off + k * SIZE[ty]] = (name if n is None else '%s[%d]' % (name, k), ty)

t = open(path, encoding='latin-1', newline='').read()
done, other, unknown = 0, collections.Counter(), collections.Counter()
# (an offset the file also reads or writes as another type stays S() everywhere: the field and the S() access would
# then be two types for one place, which the compiler, by C's aliasing rules, may reorder against each other)
kinds = collections.defaultdict(set)
for m in re.finditer(r'\bS\(([^,()]+), (0x[0-9a-f]+)\)', t):
	kinds[int(m.group(2), 16)].add(SAME.get(m.group(1).strip(), m.group(1).strip()))


def sub(m):
	global done
	ty, off = m.group(1).strip(), int(m.group(2), 16)
	f = fields.get(off)
	if not f:
		unknown[off] += 1
		return m.group(0)
	# (int and u32 may alias each other: an offset read both ways is converted, the other signedness as
	# *(u32 *)&SC->field)
	cls = lambda k: 'int32' if k in ('i32', 'u32') else k
	if {cls(k) for k in kinds[off]} == {cls(f[1])} and cls(f[1]) == 'int32' and SAME.get(ty) != f[1]:
		done += 1
		return '(*(%s *)&SC->%s)' % (ty, f[0])
	if kinds[off] != {f[1]} and not ({cls(k) for k in kinds[off]} == {cls(f[1])} == {'int32'}):
		other['%s %s as %s' % (hex(off), f[0], ty)] += 1
		return m.group(0)
	done += 1
	return 'SC->' + f[0]


nt = re.sub(r'\bS\(([^,()]+), (0x[0-9a-f]+)\)', sub, t)
if done and not DRY:
	# SC next to each S definition
	nt = re.sub(r'^(#define S\(type, offset\) GAME_VAR\(type, s \+ \(offset\)\)[^\n]*\n)(?!#define SC )',
	            r'\1#define SC ((Scene *)s)   /* the same scene by its fields (src/scene.fields) */\n', nt, flags=re.M)
	nt = re.sub(r'^#undef S\n(?!#undef SC\n)', '#undef S\n#undef SC\n', nt, flags=re.M)
	open(path, 'w', encoding='latin-1', newline='').write(nt)
print('%s: %d accesses by field; %d of another type than the field; %d (%d offsets) with no field yet' % (
	path, done, sum(other.values()), sum(unknown.values()), len(unknown)))
if '--list' in sys.argv:
	for k, n in other.most_common():
		print('  type:', k, n)
	for k, n in unknown.most_common():
		print('  no field: 0x%x %d' % (k, n))
