r"""index_objects.py <file.c>... [--dry]: an element of a named object (src/objects.h) read through its address,
    GAME_VAR(u32, OBJ(g_randTable) + (at & 0xfff) * 4)      GAME_VAR(int, OBJ(g_lobbyTopOutlines) + 0x84)
becomes an index into it:
    (*(u32 *)&g_randTable[at & 0xfff])                     g_lobbyTopOutlines[0x21]
when the access is one element of the object's type (the same type: plain; another of the same size: through a
pointer of the access's type, so reads and stores keep their type). The code is the same (check: tools/objcmp.py)."""
import re, sys, os

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
files = [f for f in sys.argv[1:] if not f.startswith('--')]
SIZE = {'u8': 1, 'char': 1, 'signed char': 1, 'u16': 2, 'short': 2, 'u32': 4, 'int': 4, 'i32': 4, 'float': 4, 'unsigned': 4}

objs = {}
for m in re.finditer(r'^#define (\w+) \(\((\w[\w ]*?) \*\)IMG\(0x[0-9a-f]+\)\)', open('src/objects.h', encoding='latin-1').read(), re.M):
	if m.group(2) in SIZE:
		objs[m.group(1)] = m.group(2)


def top_level_op(e):
	"""e has an operator outside parentheses (so "e * 4" is not "(e) * 4")"""
	depth = 0
	for k, ch in enumerate(e):
		depth += {'(': 1, ')': -1, '[': 1, ']': -1}.get(ch, 0)
		if depth == 0 and ch in '+-*/%&|^<>?' and not (ch == '-' and k == 0):
			return True
		if depth < 0:
			return True
	return depth != 0


def index_of(expr, size):
	"""expr (the byte offset) as an element index, or None"""
	expr = expr.strip()
	m = re.fullmatch(r'0x[0-9a-f]+|\d+', expr)
	if m:
		v = int(expr, 0)
		return None if v % size else hex(v // size) if v // size > 9 else str(v // size)
	if size == 1:
		return expr
	m = re.fullmatch(r'(.+?) \* %d' % size, expr) or re.fullmatch(r'%d \* (.+)' % size, expr)
	if m and not top_level_op(m.group(1)):
		e = m.group(1)
		return e[1:-1] if e.startswith('(') and e.endswith(')') and e[1:-1].count('(') == e[1:-1].count(')') else e
	return None


def balanced_end(t, i):
	depth = 0
	for k in range(i, len(t)):
		if t[k] == '(':
			depth += 1
		elif t[k] == ')':
			depth -= 1
			if depth == 0:
				return k
	return -1


total = 0
for path in files:
	raw = open(path, encoding='latin-1', newline='').read()
	crlf = '\r\n' in raw
	t = raw.replace('\r\n', '\n')
	out, pos, n = [], 0, 0
	for m in re.finditer(r'\bGAME_VAR\((\w[\w ]*?), OBJ\((\w+)\)', t):
		if m.start() < pos:
			continue
		T, name = m.group(1), m.group(2)
		end = balanced_end(t, m.start() + len('GAME_VAR'))
		inner = t[m.end():end]   # what follows OBJ(name) inside GAME_VAR( .. )
		if name not in objs or T not in SIZE or SIZE[T] != SIZE[objs[name]]:
			continue
		if inner.strip() == '':
			idx = '0'
		elif inner.startswith(' + '):
			idx = index_of(inner[3:], SIZE[T])
		else:
			idx = None
		if idx is None:
			continue
		elem = '%s[%s]' % (name, idx)
		new = elem if T == objs[name] else '(*(%s *)&%s)' % (T, elem)
		out.append(t[pos:m.start()] + new)
		pos = end + 1
		n += 1
	if not n:
		continue
	out.append(t[pos:])
	print('%-36s %d' % (path, n))
	total += n
	if not DRY:
		t = ''.join(out)
		open(path, 'w', encoding='latin-1', newline='').write(t.replace('\n', '\r\n') if crlf else t)
print(total, 'object elements indexed')
