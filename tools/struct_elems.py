r"""struct_elems.py <file.c> <spec> <Type> <ptr> [--in=f,g] [--dry] [--list]: accesses to an element of an array field
of a struct, by the struct's base, its offset and an index:
  GV:s            GAME_VAR(type, s + 0x1cd93cc + owner * 0x8888)   -> ST->actors[owner].steadiness
                  GAME_VAR(type, s + 0x202e8d4)                    -> ST->playerActor  (no index: a plain field)
  OI=int@0x8888,OF=float@0x8888   OI(j, 0x1cd94f4)  (a macro of the file: GAME_VAR(int, s + (offset) + (j) * 0x8888))
                                                   -> ST->actors[j].state
The element's field must have the access's type (int / i32 alike); an offset the file reaches as two types (float /
int) stays everywhere (see tools/struct_fields.py). Fields come from src/scene.fields. Check: tools/objcmp.py, else
the harness state tests."""
import re, sys, os, collections

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
args = [a for a in sys.argv[1:] if not a.startswith('--')]
DRY, LIST = '--dry' in sys.argv, '--list' in sys.argv
path, spec, TYPE, PTR = args
SAME = {'int': 'i32', 'i32': 'i32', 'u32': 'u32', 'float': 'float', 'u8': 'u8', 'char': 'char', 'i8': 'i8',
        'signed char': 'i8', 'u16': 'u16', 'i16': 'i16', 'short': 'i16', 'double': 'double'}
SIZE = {'i32': 4, 'u32': 4, 'float': 4, 'u8': 1, 'char': 1, 'i8': 1, 'u16': 2, 'i16': 2, 'double': 8}

structs, cur = {}, None
for l in open('src/scene.fields', encoding='latin-1'):
	l = l.split('#')[0].strip()
	if not l:
		continue
	if l.startswith('struct'):
		p = l.split(); cur = p[1]; structs[cur] = (int(p[2], 0), []); continue
	off, size, decl = l.split(None, 2)
	m = re.match(r'(.+?)\s*\b(\w+)\s*((?:\[\w+\])*)$', decl)
	if m:
		structs[cur][1].append((int(off, 16), int(size, 0), m.group(1).strip(), m.group(2), [int(d, 0) for d in re.findall(r'\[(\w+)\]', m.group(3))]))


def esize(ty):
	return SIZE.get(ty) or (4 if ty.endswith('*') else None) or (structs[ty][0] if ty in structs else None)


def resolve(stype, o):
	for off, size, ty, name, dims in structs[stype][1]:
		if not off <= o < off + size:
			continue
		es = esize(ty)
		if not es:
			return None
		k, r = divmod(o - off, es)
		idx = ''
		if dims:
			parts, rest = [], k
			for d in reversed(dims):
				parts.append(rest % d); rest //= d
			idx = ''.join('[%d]' % x for x in reversed(parts))
		elif k:
			return None
		if ty in structs:
			sub = resolve(ty, r)
			return ('%s%s.%s' % (name, idx, sub[0]), sub[1]) if sub else None
		return ('%s%s' % (name, idx), ty) if r == 0 else None
	return None


def resolve_elem(stype, c, n):
	"""(array field name, element path, type) for absolute offset c of an element of stride n (index 0's)"""
	for off, size, ty, name, dims in structs[stype][1]:
		if len(dims) == 1 and esize(ty) == n and off <= c < off + n and ty in structs:
			sub = resolve(ty, c - off)
			if sub:
				return name, sub[0], sub[1]
	return None


t = open(path, encoding='latin-1', newline='').read()
spans = None
for a in sys.argv:
	if a.startswith('--in='):
		spans = []
		for fn in a[5:].split(','):
			fm = re.search(r'\(%s\)\([^;{]*\)\s*\{' % re.escape(fn), t)
			if not fm:
				raise SystemExit('no function ' + fn)
			depth, k = 0, fm.end() - 1
			for k in range(fm.end() - 1, len(t)):
				depth += {'{': 1, '}': -1}.get(t[k], 0)
				if depth == 0:
					break
			spans.append((fm.start(), k))
inside = lambda p: spans is None or any(a <= p < b for a, b in spans)
cls = lambda k: 'int32' if k in ('i32', 'u32') else k


def calls(head):
	"""(start, end, inner text) of each call of the macro / GAME_VAR"""
	for m in re.finditer(head, t):
		depth = 0
		for j in range(m.end() - 1, len(t)):
			depth += {'(': 1, ')': -1}.get(t[j], 0)
			if depth == 0:
				break
		yield m.start(), j + 1, t[m.end():j], m


found = []   # (start, end, type, offset, index expr or None, stride)
if spec.startswith('GV:'):
	var = spec[3:]
	for a, b, inner, m in calls(r'\bGAME_VAR\('):
		pm = re.match(r'^([^,()]+), %s \+ (0x[0-9a-f]+)(?: \+ (\(?[\w\->.\[\]]+\)?|\([^()]*(?:\([^()]*\)[^()]*)*\)) \* (0x[0-9a-f]+|\d+))?$' % re.escape(var), inner)
		if pm:
			found.append((a, b, pm.group(1).strip(), int(pm.group(2), 16), pm.group(3), int(pm.group(4), 0) if pm.group(4) else None))
else:
	macros = {}
	for x in spec.split(','):
		k, rest = x.split('=')
		ty, n = rest.split('@')
		macros[k] = (ty, int(n, 0))
	for a, b, inner, m in calls(r'\b(%s)\(' % '|'.join(sorted(macros, key=len, reverse=True))):
		parts = inner.rsplit(', ', 1)
		if len(parts) == 2 and re.match(r'^0x[0-9a-f]+$', parts[1]):
			ty, n = macros[m.group(1)]
			found.append((a, b, ty, int(parts[1], 16), parts[0], n))
found = [f for f in found if inside(f[0])]

kinds = collections.defaultdict(set)
for a, b, ty, c, ix, n in found:
	kinds[c].add(cls(SAME.get(ty, ty)))
out, pos, done, left = [], 0, 0, collections.Counter()
for a, b, ty, c, ix, n in found:
	if ix is None:
		f = resolve(TYPE, c)
		text = f and '%s->%s' % (PTR, f[0])
		fty = f and f[1]
	else:
		e = resolve_elem(TYPE, c, n)
		ix2 = ix[1:-1] if ix.startswith('(') and ix.endswith(')') and ix.count('(') == 1 else ix
		text = e and '%s->%s[%s].%s' % (PTR, e[0], ix2, e[1])
		fty = e and e[2]
	if not text or len(kinds[c]) != 1 or cls(SAME.get(ty, ty)) != cls(fty):
		left[hex(c)] += 1
		continue
	if SAME.get(ty, ty) != fty:
		continue   # (int / u32 views: left as they are here)
	out.append(t[pos:a]); out.append(text); pos = b; done += 1
out.append(t[pos:])
if done and not DRY:
	open(path, 'w', encoding='latin-1', newline='').write(''.join(out))
print('%s %s: %d by field; %d left' % (path, spec, done, sum(left.values())))
if LIST:
	for k, v in left.most_common():
		print('  left:', k, v)
