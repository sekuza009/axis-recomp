r"""reuse_aliases.py <file.c>... [--dry]: where a function already has a typed alias of a pointer,
    Stage *st = (Stage *)s;
the casts after it that say the same thing, ((Stage *)s)->f, use the alias: st->f. Only when s is not assigned again
after the alias (the alias would still point at the old record). The code is the same (check: tools/objcmp.py)."""
import re, sys, os

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
files = [f for f in sys.argv[1:] if not f.startswith('--')]


def bodies(t):
	for m in re.finditer(r'\)\n\{\n', t):
		depth = 0
		start = t.index('{', m.start())
		for k in range(start, len(t)):
			depth += {'{': 1, '}': -1}.get(t[k], 0)
			if depth == 0:
				break
		yield start, k


total = 0
for path in files:
	raw = open(path, encoding='latin-1', newline='').read()
	crlf = '\r\n' in raw
	t = raw.replace('\r\n', '\n')
	edits = []
	for a, b in bodies(t):
		body = t[a:b]
		nb = body
		for d in re.finditer(r'^\s*(?:const )?(\w+) \*(\w+) = \((?:const )?\1 \*\)(\w+);', body, re.M):
			T, alias, v = d.group(1), d.group(2), d.group(3)
			if v.startswith('g_'):   # (a global: the original reads it again)
				continue
			rest = nb[nb.index(d.group(0)) + len(d.group(0)):]
			if re.search(r'(?<![\w.>])%s\s*(?:[-+*/|&^]?=(?!=)|\+\+|--)|(?:\+\+|--)%s\b' % (v, v), rest):
				continue
			if re.search(r'(?<![\w.>])%s\s*(?:[-+*/|&^]?=(?!=)|\+\+|--)|(?:\+\+|--)%s\b' % (alias, alias), rest):
				continue
			n = len(re.findall(r'\(\(%s \*\)%s\)' % (T, v), rest))
			if not n:
				continue
			new_rest = re.sub(r'(?<=[\w\])])\(\(%s \*\)%s\)' % (T, v), '(%s)' % alias, rest)
			new_rest = re.sub(r'(?<![\w\])])\(\(%s \*\)%s\)' % (T, v), alias, new_rest)
			nb = nb[:len(nb) - len(rest)] + new_rest
			total += n
			print('  %s: ((%s *)%s) -> %s x%d' % (path, T, v, alias, n))
		if nb != body:
			edits.append((a, b, nb))
	for a, b, nb in reversed(edits):
		t = t[:a] + nb + t[b:]
	if edits and not DRY:
		open(path, 'w', encoding='latin-1', newline='').write(t.replace('\n', '\r\n') if crlf else t)
print(total, 'casts replaced by aliases')
