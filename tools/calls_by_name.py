r"""calls_by_name.py [--dry]: every call of a rebuilt game function by its original address named.

1. Files' own call macros whose first parameter is the address (#define CALL(addr) GAME_CDECL(addr, u32, void)() and
   the like) are written out where they are used with a literal address.
2. GAME_CDECL(0x..., / GAME_THISCALL(0x..., of an address the loader switches to a rebuilt function (the hook table,
   tools/mkhooks.py) becomes GAME_FN(name, 0x..., / GAME_THISFN(name, 0x..., - in src/ and in game.h's name macros.
3. A call written GAME_FN(name, 0x..., types)(args) in a .c file for which game.h has a plain name macro with the same
   types ("#define m(a, b) GAME_FN(name, 0x..., types)(a, b)") becomes m(args); a trailing "/* name */" comment
   that only repeated the name goes.
In the harness (recomp.dll) GAME_FN is GAME_CDECL, so its objects do not change (check with objcmp.py); AxisRC.exe
compiles src/ with AXIS_DIRECT, where GAME_FN calls the C function itself (src/axis.h)."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
sys.argv, argv = sys.argv[:1] + ['-'], sys.argv
import importlib.util
spec = importlib.util.spec_from_file_location('hooktable', 'tools/hooktable.py')
ht = importlib.util.module_from_spec(spec); spec.loader.exec_module(ht)
hooked = {a: n for a, n in ht.hooks()}
dry = '--dry' in argv


def macro_args(s, i):
	"""the arguments of the parenthesised list starting at s[i] == '(' and the index after it"""
	depth, args, cur = 0, [], ''
	for j in range(i, len(s)):
		c = s[j]
		if c == '(':
			depth += 1
			if depth == 1:
				continue
		elif c == ')':
			depth -= 1
			if depth == 0:
				args.append(cur.strip())
				return args, j + 1
		elif c == ',' and depth == 1:
			args.append(cur.strip()); cur = ''
			continue
		cur += c
	raise ValueError('unbalanced')


# ---- 1. call macros taking the address
LOCAL = re.compile(r'^[ \t]*#define[ \t]+(\w+)\(([^)]*)\)[ \t]+(GAME_(?:CDECL|THISCALL)\((\w+),.*?)[ \t]*(?:/\*.*)?$')


def expand_local(text):
	lines, macros, n = text.split('\n'), {}, 0
	for i, line in enumerate(lines):
		m = LOCAL.match(line.rstrip('\r'))
		if m:
			params = [p.strip() for p in m.group(2).split(',')]
			if params and params[0] == m.group(4):
				macros[m.group(1)] = (params, m.group(3))
			continue
		u = re.match(r'^[ \t]*#undef[ \t]+(\w+)', line)
		if u:
			macros.pop(u.group(1), None); continue
		if line.lstrip().startswith('#define'):
			continue
		for name, (params, body) in macros.items():
			k = 0
			while True:
				m = re.compile(r'(?<![\w.>])%s\(\s*0x[0-9a-f]+\s*[,)]' % name).search(line, k)
				if not m:
					break
				start = m.start(); args, end = macro_args(line, start + len(name))
				if len(args) != len(params):
					k = end; continue
				out = body
				for p, a in zip(params, args):
					out = re.sub(r'\b%s\b' % re.escape(p), lambda _: a, out)
				line = line[:start] + out + line[end:]
				k = start + len(out); n += 1
		lines[i] = line
	return '\n'.join(lines), n


# ---- 2. address calls named
ADDR = re.compile(r'\bGAME_(CDECL|THISCALL)\(\s*(0x[0-9a-f]+)\s*,')


def name_calls(text):
	n = [0]

	def sub(m):
		a = int(m.group(2), 16)
		if a not in hooked:
			return m.group(0)
		n[0] += 1
		return 'GAME_%s(%s, %s,' % ('FN' if m.group(1) == 'CDECL' else 'THISFN', hooked[a], m.group(2))
	return ADDR.sub(sub, text), n[0]


def norm(s):
	return re.sub(r'\s+', ' ', s.strip())


total = {'expanded': 0, 'named': 0, 'by macro': 0}
gh = open('src/game.h', 'rb').read().decode('latin-1')
gh2, k = name_calls(gh)
total['named'] += k
if not dry:
	open('src/game.h', 'wb').write(gh2.encode('latin-1'))
# game.h's plain name macros: (fn, addr, types) -> macro name
plain = {}
for m in re.finditer(r'^#define[ \t]+(\w+)\(([^)]*)\)[ \t]+(GAME_(?:FN|THISFN)\(([^\n]*?)\))\(([^)\n]*)\)[ \t]*(?:/\*[^\n]*)?\r?$', gh2, re.M):
	params = [p.strip() for p in m.group(2).split(',') if p.strip()]
	args = [a.strip() for a in m.group(5).split(',') if a.strip()]
	if params != args or '...' in m.group(2):
		continue
	key = (m.group(3).split('(')[0], norm(m.group(4)))
	plain.setdefault(key, m.group(1))
undefs = set()
for f in sorted(glob.glob('src/**/*.c', recursive=True)):
	t = open(f, 'rb').read().decode('latin-1')
	undefs = set(re.findall(r'^[ \t]*#(?:undef|define)[ \t]+(\w+)', t, re.M))
	t, a = expand_local(t)
	t, b = name_calls(t)
	c = 0
	out, k = [], 0
	for m in re.finditer(r'\b(GAME_(?:FN|THISFN))\(', t):
		if m.start() < k:
			continue
		try:
			args, end = macro_args(t, m.end() - 1)
		except ValueError:
			continue
		key = (m.group(1), norm(', '.join(args)))
		name = plain.get(key)
		line_start = t.rfind('\n', 0, m.start()) + 1
		if (not name or name in undefs or end >= len(t) or t[end] != '(' or t[line_start:].lstrip().startswith('#define')):
			continue
		out.append(t[k:m.start()] + name)
		k = end; c += 1
	t = ''.join(out) + t[k:]
	# a comment that only repeated the function's name
	t = re.sub(r'((\w+)\([^\n]*?;)[ \t]+/\*[ \t]*\2[ \t]*\*/', r'\1', t)
	if a or b or c:
		print('%-36s expanded %3d, named %3d, by macro %3d' % (f, a, b, c))
		total['expanded'] += a; total['named'] += b; total['by macro'] += c
		if not dry:
			open(f, 'wb').write(t.encode('latin-1'))
print(total)
