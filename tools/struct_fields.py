r"""struct_fields.py <file.c> <macro> <Type> <name> [--dry] [--list]: a file's accesses by offset through one of its
macros,  #define A(type, offset) GAME_VAR(type, actor + (offset)),  written as fields of a struct of src/scene.fields:
A(int, 0xec) -> AC->score, with  #define AC ((Player *)actor)  put after each definition of the macro (and #undef'd
with it). Offsets inside a struct member or an array of structs resolve through them (SC->players[3].score).

The rules (as tools/scene_fields.py, which this generalises):
  - an access converts when the field at its offset has its type (int and i32 alike) and starts there;
  - int and u32 views of one field both convert (the other signedness as *(u32 *)&AC->field: they may alias);
  - an offset the file also uses as another type (float / int punning) stays as it was everywhere: a field access
    and an access by address of another type are two types for one place, which the compiler may reorder;
  - unnamed offsets stay and are listed (--list): add their fields to src/scene.fields, run tools/mkscene.py, then
    this again.
Field addressing compiles to other code than byte offsets (block layout), so check with the harness's state tests
of the file's functions (RECOMP_ONLY=... test3.sh) and check3, not objcmp."""
import re, sys, os, collections

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
args = [a for a in sys.argv[1:] if not a.startswith('--')]
DRY, LIST = '--dry' in sys.argv, '--list' in sys.argv
PUNNED = '--punned' in sys.argv
path, macro, TYPE, PTR = args

SAME = {'int': 'i32', 'i32': 'i32', 'u32': 'u32', 'float': 'float', 'u8': 'u8', 'char': 'char', 'i8': 'i8',
        'signed char': 'i8', 'u16': 'u16', 'i16': 'i16', 'short': 'i16', 'double': 'double', 'void *': 'void *'}
SIZE = {'i32': 4, 'u32': 4, 'float': 4, 'u8': 1, 'char': 1, 'i8': 1, 'u16': 2, 'i16': 2, 'double': 8, 'void *': 4}

structs = {}   # name -> (size, [(offset, size, type, name, dims)])
cur = None
for l in open('src/scene.fields', encoding='latin-1'):
	l = l.split('#')[0].strip()
	if not l:
		continue
	if l.startswith('struct'):
		p = l.split()
		cur = p[1]; structs[cur] = (int(p[2], 0), []); continue
	off, size, decl = l.split(None, 2)
	m = re.match(r'(.+?)\s*\b(\w+)\s*((?:\[\w+\])*)$', decl)
	if not m:
		continue
	dims = [int(d, 0) for d in re.findall(r'\[(\w+)\]', m.group(3))]
	structs[cur][1].append((int(off, 16), int(size, 0), m.group(1).strip().replace(' *', ' *'), m.group(2), dims))


def resolve(stype, o):
	"""(path, element type) of the field starting at offset o of stype, or None"""
	for off, size, ty, name, dims in structs[stype][1]:
		if not off <= o < off + size:
			continue
		rel = o - off
		esize = SIZE.get(ty) or (4 if ty.endswith('*') else None) or (structs[ty][0] if ty in structs else None)
		if not esize:
			return None
		k, r = divmod(rel, esize)
		idx = ''
		if dims:
			for d in reversed(dims[1:]):
				pass
			# (a flat index into the dimensions, row-major)
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


t = open(path, encoding='latin-1', newline='').read()
# <macro>: a two-argument macro of the file (its base inside); FIELD:var: the three-argument FIELD(type, var, offset)
# on a variable that already has the struct's type (then <name> is that variable)
VARFORM = ':' in macro
FIXED = '=' in macro   # AI=int,AF=float,...: one-argument macros of a fixed type on one base (all counted together)
if FIXED:
	fixed = dict(x.split('=') for x in macro.split(','))
	ACCESS = re.compile(r'\b(%s)\((0x[0-9a-f]+|\d+)\)' % '|'.join(re.escape(k) for k in sorted(fixed, key=len, reverse=True)))
	macro = sorted(fixed)[0]
elif VARFORM:
	macro, var = macro.split(':')
	if macro == 'GV':   # GAME_VAR(type, var + offset) on a byte pointer: (Type *)var's field
		ACCESS = re.compile(r'\bGAME_VAR\(([^,()]+), %s \+ (0x[0-9a-f]+|\d+)\)' % re.escape(var))
	else:
		ACCESS = re.compile(r'\b%s\(([^,()]+), %s, (0x[0-9a-f]+|\d+)\)' % (re.escape(macro), re.escape(var)))
else:
	ACCESS = re.compile(r'\b%s\(([^,()]+), (0x[0-9a-f]+|\d+)\)' % re.escape(macro))


def size_of(ty):
	st = SAME.get(ty, ty)
	return SIZE.get(st) or (4 if st.endswith('*') else None)


def is_lvalue(m):
	"""the access is written (assigned, incremented) or its address taken"""
	after, before = t[m.end():m.end() + 3], t[max(0, m.start() - 2):m.start()]
	return re.match(r'\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|\s*(?:\+\+|--)', after) is not None or \
		before.endswith('&') and not before.endswith('&&') or before.endswith('++') or before.endswith('--')
typ = lambda m: fixed[m.group(1)] if FIXED else m.group(1).strip()


def nice_float(w):
	"""a float's bit pattern as its shortest exact literal (None: no plain one)"""
	import struct, math
	f = struct.unpack('<f', struct.pack('<I', w))[0]
	if w == 0 or not math.isfinite(f) or not (1e-6 <= abs(f) <= 1e9):
		return None
	for p in range(1, 9):
		s = '%.*g' % (p, f)
		if struct.unpack('<I', struct.pack('<f', float(s)))[0] == w:
			if 'e' in s:   # (written out: 100.0f, not 1e+02f)
				s = ('%.10f' % float(s)).rstrip('0')
			return (s if '.' in s else s + '.0').replace('.f', '.0f') + ('0' if s.endswith('.') else '') + 'f'
	return None


# a float field written with a float's bit pattern, M(u32, off) = 0x3f000000, becomes M(float, off) = 0.5f: the same
# store (the compiler moves the constant's bits), and the field is then used as one type
def float_literals(head_u32, write_float):
	"""head_u32(off) a regex of the u32 access, write_float(off) the float access; only an assignment that is its own
	statement (in a chain, a = b = 0x447a0000, the outer one would take the float's value converted, not its bits)"""
	def lit(m):
		f = resolve(TYPE, int(m.group(2), 0))
		v = '0.0f' if m.group(3) == '0' else nice_float(int(m.group(3), 16))
		if f and f[1] == 'float' and v:
			return '%s%s = %s;' % (m.group(1), write_float(m.group(2)), v)
		return m.group(0)
	# (an integer 0 is the same store as 0.0f: the bits of +0.0)
	return re.sub(r'(?<=[;{}\n])([ \t]*)%s = (0x[0-9a-f]{8}|0);' % head_u32, lit, t)


if not VARFORM and not FIXED:
	t = float_literals(r'\b%s\((?:u32|int), (0x[0-9a-f]+|\d+)\)' % re.escape(macro), lambda o: '%s(float, %s)' % (macro, o))
elif FIXED and 'u32' in fixed.values() and 'float' in fixed.values():
	FL = [k for k, v in fixed.items() if v == 'float'][0]
	ints = '|'.join(re.escape(k) for k, v in fixed.items() if v in ('u32', 'int'))
	t = float_literals(r'\b(?:%s)\((0x[0-9a-f]+|\d+)\)' % ints, lambda o: '%s(%s)' % (FL, o))
kinds = collections.defaultdict(set)
done, other, unknown = 0, collections.Counter(), collections.Counter()
cls = lambda k: 'int32' if k in ('i32', 'u32') else k


# --in=f,g: only inside those functions' bodies (a variable name can mean another record elsewhere in the file)
spans = None
for a in sys.argv:
	if a.startswith('--in='):
		spans = []
		for fn in a[5:].split(','):
			fm = re.search(r'\(%s\)\([^;{]*\)\s*\{' % re.escape(fn), t) or re.search(r'\b%s\([^;{]*\)\s*\{' % re.escape(fn), t)
			if not fm:
				raise SystemExit('no function ' + fn)
			depth, k = 0, fm.end() - 1
			for k in range(fm.end() - 1, len(t)):
				depth += {'{': 1, '}': -1}.get(t[k], 0)
				if depth == 0:
					break
			spans.append((fm.start(), k))


def inside(m):
	return spans is None or any(a <= m.start() < b for a, b in spans)


for m in ACCESS.finditer(t):
	if inside(m):
		kinds[int(m.group(2), 0)].add(SAME.get(typ(m), typ(m)))


def sub(m):
	global done
	if not inside(m):
		return m.group(0)
	ty, off = typ(m), int(m.group(2), 0)
	f = resolve(TYPE, off)
	if not f:
		unknown[off] += 1
		return m.group(0)
	name, fty = f
	views = {cls(k) for k in kinds[off]}
	if kinds[off] == {fty} or (fty.endswith('*') and kinds[off] == {fty.replace(' ', '')}) :
		done += 1
		return '%s->%s' % (PTR, name)
	if views == {cls(fty)} == {'int32'}:
		done += 1
		if SAME.get(ty, ty) == fty:
			return '%s->%s' % (PTR, name)
		# (a plain assignment that is its own statement stores the same bits through the field's own type)
		if re.match(r'\s*=(?!=)', t[m.end():m.end() + 3]) and re.search(r'(?:^|[;{}])\s*$', t[max(0, m.start() - 200):m.start()]):
			return '%s->%s' % (PTR, name)
		return ('(*(%s *)&%s->%s)' if is_lvalue(m) else '((%s)%s->%s)') % (ty, PTR, name)
	# --punned: the field read or written as another type of its size (its bits): BITS(p->f) for a u32 / int view of
	# a float field, *(T *)&p->f otherwise. Safe since the build has -fno-strict-aliasing (2026-11-03): the views of
	# one place are no longer assumed apart
	if PUNNED and size_of(ty) == size_of(fty) and size_of(ty):
		done += 1
		st = SAME.get(ty, ty)
		if st == fty or (cls(st) == cls(fty) == 'int32' and not is_lvalue(m)):
			return '%s->%s' % (PTR, name) if st == fty else '((%s)%s->%s)' % (ty, PTR, name)
		# a pointer field read as another pointer type: a cast (no punning; a write is left for a plain assignment)
		if st.endswith('*') and fty.endswith('*'):
			if is_lvalue(m):
				done -= 1
				other['%s %s as %s (a pointer written)' % (hex(off), name, ty)] += 1
				return m.group(0)
			return '((%s)%s->%s)' % (ty, PTR, name)
		if ty == 'u32':
			return 'BITS(%s->%s)' % (PTR, name)
		return '(*(%s *)&%s->%s)' % (ty, PTR, name)
	other['%s %s as %s' % (hex(off), name, '/'.join(sorted(kinds[off])))] += 1
	return m.group(0)


nt = ACCESS.sub(sub, t)

# indexed: M(type, 0x130 + expr * 4) on an array field of that element type and size -> PTR->ammo[expr]
if not VARFORM:
	head = re.compile(r'\b(%s)\(' % '|'.join(re.escape(k) for k in (sorted(fixed, key=len, reverse=True) if FIXED else [macro])))
	out, pos = [], 0
	for m in head.finditer(nt):
		if m.start() < pos:
			continue
		depth, j = 0, m.end() - 1
		for j in range(m.end() - 1, len(nt)):
			depth += {'(': 1, ')': -1}.get(nt[j], 0)
			if depth == 0:
				break
		inner = nt[m.end():j]
		if FIXED:
			ty, offarg = fixed[m.group(1)], inner
		else:
			parts = inner.split(', ', 1)
			if len(parts) != 2:
				continue
			ty, offarg = parts[0].strip(), parts[1]
		im = re.match(r'^(0x[0-9a-f]+|\d+) \+ (.+) \* (0x[0-9a-f]+|\d+)$', offarg, re.S)
		if not im:
			continue
		base, expr, n = int(im.group(1), 0), im.group(2), int(im.group(3), 0)
		hitf = [f for f in structs[TYPE][1] if f[0] == base and len(f[4]) == 1 and SIZE.get(f[2]) == n and SAME.get(ty) == f[2]]
		if not hitf:
			continue
		out.append(nt[pos:m.start()]); out.append('%s->%s[%s]' % (PTR, hitf[0][3], expr)); pos = j + 1
		done += 1
	if out:
		out.append(nt[pos:]); nt = ''.join(out)

# (the pointer macro is only inserted when PTR is a name: an expression - ((T *)p) - is written out at each use)
if done and not DRY and FIXED and re.match(r'^\w+$', PTR):
	d = re.compile(r'^(#define (?:%s)\(offset\) GAME_VAR\(\w+, (\w+) \+ \(offset\)\)[^\n]*\n)(?!#define %s )' % ('|'.join(fixed), PTR), re.M)
	nt = d.sub(lambda m: m.group(1) + '#define %s ((%s *)%s)   /* the same by its fields (src/scene.fields) */\n' % (PTR, TYPE, m.group(2)), nt, count=1)
elif done and not DRY and not VARFORM and re.match(r'^\w+$', PTR):
	d = re.compile(r'^(#define %s\(type, offset\) GAME_VAR\(type, (\w+) \+ \(offset\)\)[^\n]*\n)(?!#define %s )' % (re.escape(macro), PTR), re.M)
	nt = d.sub(lambda m: m.group(1) + '#define %s ((%s *)%s)   /* the same by its fields (src/scene.fields) */\n' % (PTR, TYPE, m.group(2)), nt)
	nt = re.sub(r'^#undef %s\n(?!#undef %s\n)' % (re.escape(macro), PTR), '#undef %s\n#undef %s\n' % (macro, PTR), nt, flags=re.M)
if done and not DRY:
	open(path, 'w', encoding='latin-1', newline='').write(nt)
print('%s %s: %d by field; %d punned (left); %d (%d offsets) with no field' % (
	path, macro, done, sum(other.values()), sum(unknown.values()), len(unknown)))
if LIST:
	for k, n in other.most_common():
		print('  punned:', k, n)
	for k, n in sorted(unknown.items()):
		print('  no field: 0x%x %d' % (k, n))
