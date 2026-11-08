"""obj_index.py [--dry]: an array of src/objects.h reached by a byte offset - OBJ(g_x) + 0x64 - written as the
element (and field) instead: (u32)&g_x[25], or for a record type of src/scene.fields (u32)&g_x[2].field /
(u32)&g_x[2].field[1]. Only a whole term (the offset a constant, the next token ',' ')' '}' or ';'); byte arrays
(u8 / char: the index is the offset) and offsets inside no field are left. The generated code is unchanged
(check with tools/objcmp.py)."""
import glob, os, re, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
SZ = {'u8': 1, 'char': 1, 'signed char': 1, 'u16': 2, 'short': 2, 's16': 2, 'int': 4, 'u32': 4, 'i32': 4, 'float': 4,
      'double': 8}

# the records: name -> (size, [(offset, size, name, dims, element size)])
recs = {}
cur = None
for line in open(os.path.join(R, 'src', 'scene.fields'), encoding='latin-1'):
	m = re.match(r'struct (\w+) (0x[0-9a-f]+|\d+)', line)
	if m:
		cur = recs.setdefault(m.group(1), (int(m.group(2), 0), []))
		continue
	m = re.match(r'(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+([^#]+?)\s*(?:#|$)', line)
	if cur is None or not m or m.group(3).startswith('union'):
		continue
	d = re.match(r'(.*?)(\w+)((?:\[\w+\])*)$', m.group(3).strip())
	if not d:
		continue
	dims = [int(x, 0) for x in re.findall(r'\[(\w+)\]', d.group(3))]
	cur[1].append((int(m.group(1), 0), int(m.group(2), 0), d.group(2), dims, d.group(1).strip()))

# and game.h's small records of one scalar type: typedef struct { float r, g, b, a; } Colour;
for t, members, name in re.findall(r'typedef struct \{ ([\w ]+?) (\w+(?:, \w+)*); \} (\w+);', open(os.path.join(R, 'src', 'game.h'), encoding='latin-1').read()):
	if t in SZ and name not in recs:
		s = SZ[t]
		names_ = members.split(', ')
		recs[name] = (s * len(names_), [(k * s, s, n, [], t) for k, n in enumerate(names_)])

objs = {}
for line in open(os.path.join(R, 'src', 'objects.h'), encoding='latin-1'):
	m = re.match(r'#define (\w+) \(\(([\w ]+?)\s*\*\)IMG\(0x[0-9a-f]+\)\)', line)
	if m:
		objs[m.group(1)] = m.group(2).strip()


def element(name, off):
	"""the element expression at byte offset off of object name, or None"""
	t = objs.get(name)
	if t in SZ:
		s = SZ[t]
		return None if s == 1 or off % s else '%s[%d]' % (name, off // s)
	if t not in recs:
		return None
	size, fields = recs[t]
	i, o = divmod(off, size)
	path = '%s[%d]' % (name, i)
	while True:
		for fo, fs, fn, dims, ft in fields:
			if fo <= o < fo + fs:
				break
		else:
			return None
		o -= fo
		path += '.' + fn
		if dims:
			n = 1
			for x in dims:
				n *= x
			es = fs // n
			if o % es:
				if ft in recs and len(dims) == 1:
					k, o = divmod(o, es)
					path += '[%d]' % k
					size, fields = recs[ft]
					continue
				return None
			k = o // es
			for j, x in enumerate(dims):
				rest = 1
				for y in dims[j + 1:]:
					rest *= y
				path += '[%d]' % (k // rest)
				k %= rest
			return path
		if o == 0:
			return path
		if ft in recs:
			size, fields = recs[ft]
			continue
		return None


# a parenthesised term (not a call's parentheses: no name before the '('), or a bare one
TERM = re.compile(r'(?<![\w)\]])\(\s*\bOBJ\((\w+)\)\s*\+\s*(0x[0-9a-f]+|\d+)\s*\)(?=\s*[,)};])'
                  r'|\bOBJ\((\w+)\)\s*\+\s*(0x[0-9a-f]+|\d+)(?=\s*[,)};])')
dry = '--dry' in sys.argv
total = left = 0
for p in sorted(glob.glob(os.path.join(R, 'src', '**', '*.c'), recursive=True)):
	rel = os.path.relpath(p, os.path.join(R, 'src')).replace(os.sep, '/')
	if rel.startswith('data/'):
		continue
	t = open(p, encoding='latin-1', newline='').read()

	def sub(m):
		global total, left
		name, off = (m.group(1), m.group(2)) if m.group(1) else (m.group(3), m.group(4))
		e = element(name, int(off, 0))
		if e is None:
			left += 1
			return m.group(0)
		total += 1
		return '(u32)&%s' % e
	u = TERM.sub(sub, t)
	if u != t and not dry:
		open(p, 'w', encoding='latin-1', newline='').write(u)
print('%d terms by element%s; %d left (byte arrays, no field there)' % (total, ' (dry)' if dry else '', left))
