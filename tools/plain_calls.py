r"""plain_calls.py [--dry]: calls to game functions written by their plain name.

An inline call  GAME_FN(net_send, 0x4521c0, int, int, int)(0x1c, 0x65)  (also GAME_THISFN, and GAME_CDECL(0x..) of
the C runtime's entries) becomes  net_send(0x1c, 0x65)  through one macro per function in a header:
  - each function gets one signature from all its uses (the header macros and the inline calls): the return type its
    callers read (a caller that ignores it may write void: the same call), and per argument the type they agree on,
    or void * / const void * where they only differ in what a pointer points at;
  - an existing macro of src/*.h (game.h has most) is used, its type list respelled to that signature if needed;
  - a function with no macro gets one in src/calls.h (generated here; game.h includes it), named as the function
    (GAME_CDECL: the runtime entry's name from standalone/crt.c, crt_ in front);
  - a call that does not fit (another return type it reads, int against u32, a pointer where the others pass a
    number, another argument count) is left as it is and listed.
The macros expand to the same call, so the code is unchanged (check: tools/objcmp.py). Rebuilt functions are defined
as  type (name)(...)  so a macro of the same name leaves their definitions alone."""
import glob, os, re, sys, collections

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
LOOSE = '--loose' in sys.argv
CALLS_H = 'src/calls.h'


def balanced(t, i):
	depth = 0
	for j in range(i, len(t)):
		if t[j] == '(':
			depth += 1
		elif t[j] == ')':
			depth -= 1
			if depth == 0:
				return j + 1
	raise ValueError('unbalanced at %d' % i)


def split_top(s):
	out, depth, cur = [], 0, ''
	for ch in s:
		if ch in '([':
			depth += 1
		elif ch in ')]':
			depth -= 1
		if ch == ',' and depth == 0:
			out.append(cur.strip()); cur = ''
		else:
			cur += ch
	out.append(cur.strip())
	return out


def norm(s):
	s = re.sub(r'\s+', ' ', s).strip()
	return re.sub(r'\s*\*', ' *', s).replace('* *', '**').replace('( ', '(').replace(' )', ')')


crt = {}
ct = open('standalone/crt.c', encoding='latin-1').read()
for a, n in re.findall(r'\{ (0x[0-9a-f]+), "([^"]+)" \}', ct):
	if not n.startswith('?'):
		crt[int(a, 16)] = 'crt_' + n.lstrip('_')
for a, n in re.findall(r'jump\((0x[0-9a-f]+), (\w+)\);', ct):
	crt.setdefault(int(a, 16), n if n.startswith('crt_') else 'crt_' + n)

# the game's imports by their slot: src/imports.h (tools/mkimports.py), IMP_<name>; Winsock's lower-case names get a
# ws_ prefix as macros (bind, send ...: too common)
imports, imp_slot = {}, {}
fn_addr = {n: int(a, 16) for n, a in re.findall(r'#define FNADDR_(\w+) (0x[0-9a-f]+)', open('src/fn_addrs.h').read())}
for n, a, dll in re.findall(r'#define IMP_(\w+) (0x[0-9a-f]+) +/\* (\S+)', open('src/imports.h').read()):
	imports[int(a, 16)] = ('ws_' + n) if dll == 'WS2_32.dll' and n[0].islower() else n
	imp_slot[int(a, 16)] = n

HEAD = re.compile(r'\b(CALL_FN|CALL_THISFN|GAME_FN|GAME_THISFN|IMPORT_FN|IMPORT)\(|\bGAME_CDECL\((?=0x)')


def parse_call(t, m):
	kind = m.group(1) or 'GAME_CDECL'
	open_ = m.end() - 1
	close = balanced(t, open_)
	if close >= len(t) or t[close] != '(':
		return None
	inner = split_top(t[open_ + 1:close - 1])
	if kind in ('CALL_FN', 'CALL_THISFN'):   # (by name: the address from src/fn_addrs.h)
		kind = kind.replace('CALL_', 'GAME_')
		inner.insert(1, hex(fn_addr.get(inner[0], 0)))
	if kind == 'IMPORT_FN':
		kind, inner[0] = 'IMPORT', hex({v: k for k, v in imp_slot.items()}.get(inner[0], 0))
	if kind in ('GAME_CDECL', 'IMPORT'):
		addr, types, name = inner[0], inner[1:], None
	else:
		name, addr, types = inner[0], inner[1], inner[2:]
	try:
		addr = int(addr, 16)
	except ValueError:
		return None
	if kind == 'GAME_CDECL':
		name = crt.get(addr)
	elif kind == 'IMPORT':
		name = imports.get(addr)
	return kind, name, addr, [norm(x) for x in types], m.start(), open_, close


def is_ptr(s):
	return s.endswith('*')


headers = sorted(h for h in glob.glob('src/**/*.h', recursive=True) if os.sep + 'data' + os.sep not in h and not h.endswith('calls.h'))
files = sorted(f for f in glob.glob('src/**/*.c', recursive=True) if os.sep + 'data' + os.sep not in f)
DEF = re.compile(r'^#define (\w+)\(([^)]*)\) +(?=CALL_FN\(|CALL_THISFN\(|GAME_FN\(|GAME_THISFN\(|GAME_CDECL\(0x|IMPORT_FN\(|IMPORT\()', re.M)


def header_macros(t):
	"""the pass-through macros of a header: (macro name, params, parsed call)"""
	for d in DEF.finditer(t):
		m = HEAD.match(t, d.end())
		p = m and parse_call(t, m)
		if not p:
			continue
		close = p[6]
		args = [x.strip() for x in split_top(t[close + 1:balanced(t, close) - 1]) if x.strip()]
		params = [x.strip() for x in d.group(2).split(',') if x.strip()]
		if args == params:
			yield d.group(1), params, p


def define_spans(t):
	return [(m.start(), m.end()) for m in re.finditer(r'^#define [^\n]*(?:\\\n[^\n]*)*', t, re.M)]


# 1. every signature of every function
uses = collections.defaultdict(collections.Counter)   # (kind, addr) -> Counter(types)
names = {}
hmacros = collections.defaultdict(list)                # (kind, addr) -> [(header, macro name)]
hsig = {}                                             # (kind, addr) -> the first header macro's types
for h in headers + ([CALLS_H] if os.path.exists(CALLS_H) else []):
	t = open(h, encoding='latin-1').read()
	for mac, params, p in header_macros(t):
		kind, name, addr, types = p[:4]
		uses[(kind, addr)][tuple(types)] += 1
		names.setdefault((kind, addr), name)
		hmacros[(kind, addr)].append((h, mac))
		hsig.setdefault((kind, addr), tuple(types))
for f in files:
	t = open(f, encoding='latin-1').read()
	spans = define_spans(t)
	for m in HEAD.finditer(t):
		if any(a <= m.start() < b for a, b in spans):
			continue
		p = parse_call(t, m)
		if p:
			uses[(p[0], p[2])][tuple(p[3])] += 1
			names.setdefault((p[0], p[2]), p[1])


# 2. one signature each (None: the uses disagree)
def canonical(k):
	"""the return type the header macro has (else the most common), and the arguments of the uses with it"""
	ret = hsig[k][0] if k in hsig else uses[k].most_common(1)[0][0][0]
	sigs = [s for s in uses[k] if s[0] == ret]
	n = {len(s) for s in sigs}
	if len(n) != 1 or any('...' in s for s in sigs):
		return None
	out = [ret]
	for i in range(1, n.pop()):
		col = {s[i] for s in sigs}
		if len(col) == 1:
			out.append(col.pop())
		elif all(is_ptr(c) for c in col):
			out.append('const void *' if any(c.startswith('const') for c in col) else 'void *')
		else:
			return None
	return tuple(out)


canon = {k: canonical(k) for k in uses}


def fits(sig, c):
	# (the same return type: a call through another function type can change what the compiler merges, e.g. two
	# switch cases' calls, though not what runs)
	return len(sig) == len(c) and sig[0] == c[0] and \
		all(a == b or (is_ptr(a) and b in ('void *', 'const void *')) for a, b in zip(sig[1:], c[1:]))


def head_text(kind, name, addr, types):
	if kind == 'IMPORT':
		return 'IMPORT_FN(%s, %s)' % (imp_slot[addr], ', '.join(types))
	return ('GAME_CDECL(0x%x, %s)' % (addr, ', '.join(types))) if kind == 'GAME_CDECL' else \
	       '%s(%s, %s)' % (kind.replace('GAME_', 'CALL_'), name, ', '.join(types))


# 3. the macro of each function: an existing one (respelled to the signature) or a new one
macro_of = {}
respell = collections.defaultdict(dict)   # header -> {macro: (kind, addr)}
for k, hs in hmacros.items():
	if canon.get(k):
		h, mac = hs[0]
		macro_of[k] = mac
		respell[h][mac] = k
taken = set(m for hs in hmacros.values() for _, m in hs)
new = {}
for k, c in canon.items():
	if c and k not in macro_of and names.get(k) and names[k] not in taken:
		macro_of[k] = names[k]; taken.add(names[k]); new[names[k]] = k

# 4. the inline calls
changed, left = {}, []
for f in files:
	t = open(f, encoding='latin-1', newline='').read()
	spans = define_spans(t)
	out, pos = [], 0
	for m in HEAD.finditer(t):
		if m.start() < pos or any(a <= m.start() < b for a, b in spans):
			continue
		p = parse_call(t, m)
		if not p:
			continue
		kind, name, addr, types, start, _, close = p
		k = (kind, addr)
		mac, c = macro_of.get(k), canon.get(k)
		where = '%s %s' % (name or '?', hex(addr))
		if not c:
			left.append((f, where, 'its uses disagree: ' + ' / '.join(', '.join(s) for s in uses[k]))); continue
		if not mac:
			left.append((f, where, 'no name')); continue
		if not fits(tuple(types), c):
			# --loose: a call whose value is not used (a statement of its own) may go through the macro's return
			# type; the caller then checks that its object is unchanged (tools/objcmp.py) and keeps only such files
			statement = re.search(r'(?:[;{}]|\belse)\s*$', t[max(0, start - 200):start]) and \
				t[balanced(t, close):balanced(t, close) + 1] == ';'
			loose_ok = LOOSE and statement and fits((c[0],) + tuple(types[1:]), c)
			if not loose_ok:
				left.append((f, where, 'does not fit ' + ', '.join(c))); continue
		if re.search(r'^#(?:define|undef) %s\b' % mac, t, re.M) or re.search(r'\bstatic\b[^;{(]*\b%s\s*\(' % mac, t):
			left.append((f, where, 'the file has its own ' + mac)); continue
		out.append(t[pos:start]); out.append(mac); pos = close
	if out:
		out.append(t[pos:])
		nt = ''.join(out)
		if nt != t:
			changed[f] = len(out) // 2
			if not DRY:
				open(f, 'w', encoding='latin-1', newline='').write(nt)

# 5. the headers: respelled macros, and calls.h
nrespelled = 0
for h, macs in respell.items():
	t = open(h, encoding='latin-1', newline='').read()
	out, pos = [], 0
	for d in DEF.finditer(t):
		mac = d.group(1)
		if mac not in macs:
			continue
		m = HEAD.match(t, d.end())
		p = parse_call(t, m)
		kind, name, addr, types, start, open_, close = p
		c = canon[(kind, addr)]
		if tuple(types) == c:
			continue
		out.append(t[pos:start]); out.append(head_text(kind, name, addr, c)); pos = close
		nrespelled += 1
	if out:
		out.append(t[pos:])
		if not DRY:
			open(h, 'w', encoding='latin-1', newline='').write(''.join(out))
if new and not DRY:
	lines = ['/* calls.h: game functions (and the C runtime\'s entries) called by their plain name, for those game.h had no',
	         '   macro for: each is the call by address in the test build and the direct call in AxisRC.exe (src/axis.h',
	         '   GAME_FN). Generated by tools/plain_calls.py; game.h includes it. */',
	         '#ifndef CALLS_H', '#define CALLS_H']
	if os.path.exists(CALLS_H):
		old = open(CALLS_H, encoding='latin-1').read().split('\n')
		lines = [l for l in old if l and l != '#endif']
	for mac, k in sorted(new.items(), key=lambda x: x[1][1]):
		c = canon[k]
		ps = [] if c[1:] in ((), ('void',)) else ['a%d' % i for i in range(len(c) - 1)]
		lines.append('#define %s(%s) %s(%s)' % (mac, ', '.join(ps), head_text(k[0], names[k], k[1], c), ', '.join(ps)))
	lines.append('#endif')
	open(CALLS_H, 'w', encoding='latin-1', newline='\n').write('\n'.join(lines) + '\n')

print('%d files, %d calls by name; %d new macros in %s; %d macros respelled; %d calls left' % (
	len(changed), sum(changed.values()), len(new), CALLS_H, nrespelled, len(left)))
reasons = collections.Counter(r.split(':')[0].split(' ')[0] + ' ' + r.split(':')[0].split(' ')[1] for _, _, r in left)
print('  left:', dict(reasons))
if '--list' in sys.argv:
	for x in left:
		print('  left: %s %s (%s)' % x)
