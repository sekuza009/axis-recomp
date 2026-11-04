r"""retype_locals.py <file.c>... [--dry]: a local byte pointer used only through one struct's cast,
    u8 *b = sk->bones + i * 0x70;   ...   ((Bone *)b)->parent   ...   b = other;
becomes that struct's pointer:
    Bone *b = (Bone *)(sk->bones + i * 0x70);   ...   b->parent   ...   b = (Bone *)(other);
Only when every other use of the name in the function is that cast or an assignment to the variable (so no byte
arithmetic on it is left to change meaning). The code is the same (check: tools/objcmp.py)."""
import re, sys, glob, os

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
files = [f for f in sys.argv[1:] if not f.startswith('--')]
MIN = int(next((x[6:] for x in sys.argv if x.startswith('--min=')), '1'))   # (--alias: at least this many casts)


def bodies(t):
	"""(start, end) of each function body: a '{' at the start of a line after a ')' line"""
	for m in re.finditer(r'\)\n\{\n', t):   # (a function's body: its brace alone at the line's start)
		depth, k = 0, m.end() - 2
		for k in range(t.index('{', m.start()), len(t)):
			depth += {'{': 1, '}': -1}.get(t[k], 0)
			if depth == 0:
				break
		yield t.index('{', m.start()), k


total = 0
for path in files:
	t = open(path, encoding='latin-1', newline='').read()
	crlf = '\r\n' in t
	t = t.replace('\r\n', '\n')   # (worked on with LF line ends, written back as found)
	edits = []   # (start, end, text)
	for a, b in bodies(t):
		body = t[a:b]
		# --alias=Type:name: a byte pointer (local or parameter) that also has byte uses, cast to Type for its fields:
		# a typed alias declared after it (Type *name = (Type *)v;) takes the casts over
		for opt in [x for x in sys.argv if x.startswith('--alias=')]:
			T, alias = opt[8:].split(':')
			for v in sorted(set(re.findall(r'\(\(%s \*\)(\w+)\)' % T, body))):
				head = t[t.rfind('\n', 0, t.rfind('(', 0, a)) + 1:a]
				d = re.search(r'^(\s*)(?:const )?u8 \*%s = [^;]+;\n' % v, body, re.M)
				if d:
					at, indent = d.end(), d.group(1)
				elif re.search(r'\bu8 \*%s\b' % v, head):
					at, indent = 2, '\t'   # (a parameter: after the body's opening brace)
				else:
					continue
				uses = re.findall(r'\(\(%s \*\)%s\)' % (T, v), body[at:])
				if len(uses) < MIN or re.search(r'\b%s\b' % alias, body):
					continue
				# (a variable assigned again after the alias would leave the alias on the old record)
				if re.search(r'(?<![\w.>])%s\s*(?:[-+*/|&^]?=(?!=)|\+\+|--)|(?:\+\+|--)%s\b' % (v, v), body[at:]):
					continue
				# (after a name or a closing bracket the first parenthesis is a call's: kept, "f((T *)v)" -> "f(alias)")
				body = body[:at] + '%s%s *%s = (%s *)%s;\n' % (indent, T, alias, T, v) + \
					re.sub(r'(?<=[\w\])])\(\(%s \*\)%s\)' % (T, v), '(%s)' % alias,
					       re.sub(r'(?<![\w\])])\(\(%s \*\)%s\)' % (T, v), alias, body[at:]))
				total += 1
				print('  %s: %s aliased as %s *%s' % (path, v, T, alias))
		for d in re.finditer(r'^(\s*)(const )?u8 \*(\w+) = ([^;]+);', body, re.M):
			const, v, init = d.group(2) or '', d.group(3), d.group(4)
			depth = 0   # (a second declarator on the line, ", *w = ...", at the initialiser's top level: skipped)
			second = False
			for ch in init:
				depth += {'(': 1, ')': -1, '[': 1, ']': -1}.get(ch, 0)
				second = second or (ch == ',' and depth == 0)
			if second:
				continue
			casts =re.findall(r'\(\((?:const )?(\w+) \*\)%s\)' % v, body)
			if not casts or len(set(casts)) != 1:
				continue
			T = casts[0]
			# every use of v: the declaration, the casts, assignments "v = ...;"
			ok = True
			for u in re.finditer(r'(?<![\w.>])%s(?!\w)' % v, body):
				s0 = u.start()
				if d.start(3) <= s0 < d.end(3):
					continue
				before = body[max(0, s0 - 30):s0]
				after = body[u.end():u.end() + 4]
				if re.search(r'\(\((?:const )?%s \*\)$' % T, before) and after.startswith(')'):
					continue
				if re.match(r'\s*=(?!=)', body[u.end():]) and re.search(r'(^|[;{}])\s*$', body[:s0]):
					continue
				ok = False
				break
			if not ok:
				continue
			# rewrite inside the body
			nb = body
			nb = re.sub(r'\(\((?:const )?%s \*\)%s\)' % (T, v), v, nb)
			nb = re.sub(r'(?m)^(\s*)%s(u8) \*%s = ([^;]+);' % (re.escape(const), v),
			            lambda m: '%s%s%s *%s = %s;' % (m.group(1), const, T, v,
			                                           'NULL' if m.group(3).strip() == 'NULL' else '(%s%s *)(%s)' % (const, T, m.group(3))), nb, count=1)
			nb = re.sub(r'(?m)((?:^|[;{}])\s*)%s = (?!\()([^;]+);' % v,
			            lambda m: '%s%s = %s;' % (m.group(1), v, 'NULL' if m.group(2).strip() == 'NULL' else '(%s%s *)(%s)' % (const, T, m.group(2))), nb)
			body = nb
			total += 1
			print('  %s: %s -> %s *' % (path, v, T))
		if body != t[a:b]:
			edits.append((a, b, body))
	for a, b, nbody in reversed(edits):
		t = t[:a] + nbody + t[b:]
	if edits and not DRY:
		open(path, 'w', encoding='latin-1', newline='').write(t.replace('\n', '\r\n') if crlf else t)
print(total, 'locals retyped')
