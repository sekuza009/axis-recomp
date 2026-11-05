r"""compatible_calls.py <file.c>... [--dry]: inline calls plain_calls.py left because their types differ from the
function's macro only in ways that make the same call:
  - int / u32 / unsigned / long / i32 (one 4-byte integer for another), in the return or an argument,
  - an argument the macro takes as void * / const void * (any pointer converts), or one the call spelled void *,
  - a return the call ignores (void) or reads as another 4-byte integer (then cast: ((u32)name(args))).
Each becomes  name(args)  through the macro. Check: tools/objcmp.py (and the state tests where it differs)."""
import re, sys, os, glob

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
files = [f for f in sys.argv[1:] if not f.startswith('--')]
INT4 = {'int', 'u32', 'unsigned', 'long', 'i32', 'unsigned int', 'DWORD'}


def split_types(s):
	out, depth, cur = [], 0, ''
	for ch in s:
		depth += {'(': 1, ')': -1}.get(ch, 0)
		if ch == ',' and depth == 0:
			out.append(re.sub(r'\s+', ' ', cur.strip())); cur = ''
		else:
			cur += ch
	if cur.strip():
		out.append(re.sub(r'\s+', ' ', cur.strip()))
	return out


def balanced(t, i):
	depth = 0
	for k in range(i, len(t)):
		depth += {'(': 1, ')': -1}.get(t[k], 0)
		if depth == 0 and t[k] == ')':
			return k
	return -1


macros = {}   # address -> (name, params count, return, argument types)
for f in glob.glob('src/*.h'):
	for m in re.finditer(r'^#define (\w+)\(([^)]*)\) (?:GAME_FN\(\w+, (0x[0-9a-f]+), |GAME_THISFN\(\w+, (0x[0-9a-f]+), |IMPORT\((0x[0-9a-f]+), |GAME_CDECL\((0x[0-9a-f]+), )([^()]*(?:\([^()]*\)[^()]*)*)\)\(',
	                     open(f, encoding='latin-1').read(), re.M):
		addr = m.group(3) or m.group(4) or m.group(5) or m.group(6)
		params = [p for p in m.group(2).split(',') if p.strip()]
		types = split_types(m.group(7))
		if '...' in types:
			continue
		macros.setdefault(addr, (m.group(1), len(params), types[0], types[1:]))


def compatible_arg(call, mac):
	return call == mac or (call in INT4 and mac in INT4) or mac in ('void *', 'const void *') or \
		(call in ('void *', 'const void *') and mac.endswith('*') and ('const' in mac or 'const' not in call))


total = 0
for path in files:
	raw = open(path, encoding='latin-1', newline='').read()
	crlf = '\r\n' in raw
	t = raw.replace('\r\n', '\n')
	# (names the file defines itself - a macro, an #undef, a function of its own: a call by name would reach the
	# rebuilt one directly, past the harness's mock at the original's address)
	local = set(re.findall(r'^\s*#(?:define|undef) (\w+)\b', t, re.M)) | \
		set(re.findall(r'^[\w ]*?\*?\s*\(?(\w+)\)?\s*\([^;{]*\)\s*\n?\{', t, re.M))
	out, pos, n = [], 0, 0
	for m in re.finditer(r'\b(?:GAME_FN\(\w+, (0x[0-9a-f]+), |GAME_THISFN\(\w+, (0x[0-9a-f]+), |IMPORT\((0x[0-9a-f]+), |GAME_CDECL\((0x[0-9a-f]+), )', t):
		if m.start() < pos:
			continue
		addr = m.group(1) or m.group(2) or m.group(3) or m.group(4)
		if addr not in macros:
			continue
		name, nparams, mret, margs = macros[addr]
		if name in local:
			continue
		tend = balanced(t, t.index('(', m.start()))
		types = split_types(t[m.end():tend])
		if t[tend + 1:tend + 2] != '(':
			continue
		aend = balanced(t, tend + 1)
		args = t[tend + 2:aend]
		ret, cargs = types[0], types[1:]
		if cargs == ['void']:
			cargs = []
		margs_ = [] if margs == ['void'] else margs
		if len(cargs) != len(margs_) or len(margs_) != nparams:
			continue
		if not all(compatible_arg(c, a) for c, a in zip(cargs, margs_)):
			continue
		if ret == mret or ret == 'void':
			new = '%s(%s)' % (name, args)
		elif ret in INT4 and mret in INT4:
			new = '((%s)%s(%s))' % (ret, name, args)
		else:
			continue
		if cargs == margs_ and ret == mret:
			continue   # (plain_calls.py's own case)
		out.append(t[pos:m.start()] + new)
		pos = aend + 1
		n += 1
	if not n:
		continue
	out.append(t[pos:])
	print('%-36s %d' % (path, n))
	total += n
	if not DRY:
		s = ''.join(out)
		open(path, 'w', encoding='latin-1', newline='').write(s.replace('\n', '\r\n') if crlf else s)
print(total, 'calls by name')
