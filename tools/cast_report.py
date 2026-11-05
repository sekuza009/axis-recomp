r"""cast_report.py: the struct casts ((T *)v)-> left, by function and variable: how many, the types, and whether v is a
parameter, a local declared once / several times, or something else (a global, an expression)."""
import os, re, glob, collections
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
rows = []
for p in sorted(glob.glob('src/**/*.c', recursive=True)):
	if 'data' in os.path.dirname(p):
		continue
	t = open(p, encoding='latin-1').read()
	for m in re.finditer(r'\((\w+)\)\s*\(([^)]*)\)\s*\n\{', t):
		a = m.end() - 1
		depth = 0
		for b in range(a, len(t)):
			depth += {'{': 1, '}': -1}.get(t[b], 0)
			if depth == 0:
				break
		body = t[a:b]
		casts = collections.defaultdict(lambda: [0, set()])
		for T, v in re.findall(r'\(\((?:const\s+)?([A-Z]\w*)\s*\*\)\s*(\w+)\)\s*->', body):
			casts[v][0] += 1
			casts[v][1].add(T)
		for v, (n, Ts) in casts.items():
			if re.search(r'\b%s\b' % re.escape(v), m.group(2)):
				kind = 'param'
			else:
				d = len(re.findall(r'\*\s*%s\s*[=;,\[)]' % re.escape(v), body))
				kind = 'local x%d' % d if d else 'other'
			rows.append((n, os.path.basename(p), m.group(1), v, '/'.join(sorted(Ts)), kind))
for r in sorted(rows, reverse=True):
	print('%3d %-18s %-30s %-10s %-22s %s' % r)
print(sum(r[0] for r in rows), 'casts in', len(rows), 'variables')
