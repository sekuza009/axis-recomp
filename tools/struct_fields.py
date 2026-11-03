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
		esize = SIZE.get(ty) or (structs[ty][0] if ty in structs else None)
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
	ACCESS = re.compile(r'\b%s\(([^,()]+), %s, (0x[0-9a-f]+|\d+)\)' % (re.escape(macro), re.escape(var)))
else:
	ACCESS = re.compile(r'\b%s\(([^,()]+), (0x[0-9a-f]+|\d+)\)' % re.escape(macro))


def is_lvalue(m):
	"""the access is written (assigned, incremented) or its address taken"""
	after, before = t[m.end():m.end() + 3], t[max(0, m.start() - 2):m.start()]
	return re.match(r'\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|\s*(?:\+\+|--)', after) is not None or \
		before.endswith('&') and not before.endswith('&&') or before.endswith('++') or before.endswith('--')
typ = lambda m: fixed[m.group(1)] if FIXED else m.group(1).strip()
kinds = collections.defaultdict(set)
for m in ACCESS.finditer(t):
	kinds[int(m.group(2), 0)].add(SAME.get(typ(m), typ(m)))
done, other, unknown = 0, collections.Counter(), collections.Counter()
cls = lambda k: 'int32' if k in ('i32', 'u32') else k


def sub(m):
	global done
	ty, off = typ(m), int(m.group(2), 0)
	f = resolve(TYPE, off)
	if not f:
		unknown[off] += 1
		return m.group(0)
	name, fty = f
	views = {cls(k) for k in kinds[off]}
	if kinds[off] == {fty}:
		done += 1
		return '%s->%s' % (PTR, name)
	if views == {cls(fty)} == {'int32'}:
		done += 1
		if SAME.get(ty) == fty:
			return '%s->%s' % (PTR, name)
		return ('(*(%s *)&%s->%s)' if is_lvalue(m) else '((%s)%s->%s)') % (ty, PTR, name)
	other['%s %s as %s' % (hex(off), name, '/'.join(sorted(kinds[off])))] += 1
	return m.group(0)


nt = ACCESS.sub(sub, t)
if done and not DRY and FIXED:
	d = re.compile(r'^(#define (?:%s)\(offset\) GAME_VAR\(\w+, (\w+) \+ \(offset\)\)[^\n]*\n)(?!#define %s )' % ('|'.join(fixed), PTR), re.M)
	nt = d.sub(lambda m: m.group(1) + '#define %s ((%s *)%s)   /* the same by its fields (src/scene.fields) */\n' % (PTR, TYPE, m.group(2)), nt, count=1)
elif done and not DRY and not VARFORM:
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
