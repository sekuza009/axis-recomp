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
	edits = []   # (start, end, text)
	for a, b in bodies(t):
		body = t[a:b]
		for d in re.finditer(r'^(\s*)(const )?u8 \*(\w+) = ([^;]+);', body, re.M):
			const, v, init = d.group(2) or '', d.group(3), d.group(4)
			casts = re.findall(r'\(\((?:const )?(\w+) \*\)%s\)' % v, body)
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
		open(path, 'w', encoding='latin-1', newline='').write(t)
print(total, 'locals retyped')
