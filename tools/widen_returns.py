r"""widen_returns.py [--dry]: let plain_calls.py convert the inline calls whose callers read a return value the
function's macro declares void.

plain_calls.py leaves a call  GAME_FN(menu_showMessage, 0x41ee40, u32, int)(0x44)  as it is when the macro in src/*.h
says  GAME_FN(menu_showMessage, 0x41ee40, void, int): the caller reads what the original leaves in eax. Where every
inline use agrees on one return type and its argument types are the macro's, the macro's return type becomes that
type (a caller that ignores the value makes the same call); then run plain_calls.py. Check with objcmp / the state
tests: the code of callers that ignore the value may be arranged differently."""
import glob, os, re, sys, collections

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv

def norm(s):
	return re.sub(r'\s+', ' ', s.strip())

def split_types(s):
	out, depth, cur = [], 0, ''
	for ch in s:
		if ch == '(':
			depth += 1
		elif ch == ')':
			depth -= 1
		if ch == ',' and depth == 0:
			out.append(norm(cur)); cur = ''
		else:
			cur += ch
	if cur.strip():
		out.append(norm(cur))
	return out

# the macros: name -> (file, the macro's text, kind, address, return type, argument types)
macros = {}
for f in glob.glob('src/*.h'):
	for m in re.finditer(r'^#define (\w+)\(([^)]*)\) (GAME_FN\(\w+, (0x[0-9a-f]+), |GAME_THISFN\(\w+, (0x[0-9a-f]+), |IMPORT\((0x[0-9a-f]+), |GAME_CDECL\((0x[0-9a-f]+), )([^)]*)\)',
	                     open(f, encoding='latin-1').read(), re.M):
		addr = m.group(4) or m.group(5) or m.group(6) or m.group(7)
		types = split_types(m.group(8))
		macros[m.group(1)] = (f, m.group(0), addr, types[0], types[1:])

# the inline uses: address -> set of (return type, argument types)
uses = collections.defaultdict(set)
for f in glob.glob('src/**/*.c', recursive=True):
	if os.sep + 'data' + os.sep in f:
		continue
	t = open(f, encoding='latin-1').read()
	for m in re.finditer(r'\b(?:GAME_FN|GAME_THISFN)\(\w+, (0x[0-9a-f]+), ([^()]*(?:\([^()]*\)[^()]*)*)\)\(', t):
		types = split_types(m.group(2))
		uses[m.group(1)].add((types[0], tuple(types[1:])))
	for m in re.finditer(r'\b(?:IMPORT|GAME_CDECL)\((0x[0-9a-f]+), ([^()]*(?:\([^()]*\)[^()]*)*)\)\(', t):
		types = split_types(m.group(2))
		uses[m.group(1)].add((types[0], tuple(types[1:])))

changed = 0
for name, (f, text, addr, ret, args) in sorted(macros.items()):
	if ret != 'void' or addr not in uses or name.startswith(('gl', 'operator_')):   # (imports that return nothing: their callers pass on eax)
		continue
	rets = {r for r, a in uses[addr] if r != 'void'}
	argsets = {a for r, a in uses[addr]}
	if len(rets) != 1 or argsets != {tuple(args)}:
		continue
	new_ret = rets.pop()
	new = text.replace(', void, ' if args else ', void)', ', %s, ' % new_ret if args else ', %s)' % new_ret, 1) if (', void, ' in text or ', void)' in text) else None
	if not new or new == text:
		continue
	print('%-32s %s: void -> %s' % (name, addr, new_ret))
	changed += 1
	if not DRY:
		b = open(f, 'rb').read()
		crlf = b.count(b'\r\n')
		s = b.decode('latin-1').replace('\r\n', '\n').replace(text, new, 1)
		if crlf:
			s = s.replace('\n', '\r\n')
		open(f, 'wb').write(s.encode('latin-1'))
print(changed, 'macros widened')
