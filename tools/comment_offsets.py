r"""comment_offsets.py [--file=SUBSTR] [--apply=LIST]: the record-relative +0x.. offsets in the comment above each
function, matched against the fields its body uses: an offset that exactly one used field (of any scene.fields
struct, nested members included) sits at is proposed as that field's name. Prints one line per offset:
  id  file:line  +0x..  -> proposal (or ?: the candidates)  | the words before it
--apply=LIST: a file of 'id name' lines (the reviewed proposals; name may be any text) to write into the comments."""
import os, re, glob, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
only = next((a.split('=', 1)[1] for a in sys.argv if a.startswith('--file=')), None)
applyf = next((a.split('=', 1)[1] for a in sys.argv if a.startswith('--apply=')), None)

structs, sizes = {}, {}
cur = None
for line in open('src/scene.fields', encoding='latin-1'):
	m = re.match(r'struct (\w+) (0x[0-9a-f]+)', line)
	if m:
		cur = m.group(1)
		sizes[cur] = int(m.group(2), 16)
		structs[cur] = []
		continue
	m = re.match(r'(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+(.*?)\s*(\w+)((?:\[[^\]]*\])*)\s*(#.*)?$', line.rstrip())
	if cur and m:
		dims = [int(d, 0) for d in re.findall(r'\[([^\]]*)\]', m.group(5))]
		structs[cur].append((int(m.group(1), 0), int(m.group(2), 0), m.group(3).strip(), m.group(4), dims))

# every (offset -> field names) a struct has at its top level, with nested struct members as 'a.b'
flat = {}


def walk(st, base, prefix, out, depth=0):
	for fo, fs, ty, name, dims in structs.get(st, []):
		tname = ty.replace('*', '').strip()
		out.setdefault(base + fo, set()).add(prefix + name)
		if tname in structs and '*' not in ty and depth < 3:
			if dims:
				n = 1
				for d in dims:
					n *= d
				walk(tname, base + fo, prefix + name + '[].', out, depth + 1)
			else:
				walk(tname, base + fo, prefix + name + '.', out, depth + 1)


for st in structs:
	out = {}
	walk(st, 0, '', out)
	flat[st] = out
byname = {}
for st, out in flat.items():
	for off, names in out.items():
		for n in names:
			byname.setdefault(n.split('.')[-1].replace('[]', ''), set()).add((st, off, n))

items = []
for p in sorted(glob.glob('src/**/*.c', recursive=True)):
	if 'data' in os.path.dirname(p) or (only and only not in p.replace('\\', '/')):
		continue
	t = open(p, encoding='latin-1', newline='').read()
	for cm in re.finditer(r'/\*.*?\*/', t, re.S):
		c = cm.group(0)
		if not re.search(r'\+0x[0-9a-f]+', c):
			continue
		nxt = t.find('\n}', cm.end())
		body = t[cm.end():nxt if nxt > 0 else len(t)]
		used = set(re.findall(r'(?:->|\.)\s*(\w+)', body)) | set(re.findall(r'offsetof\(\w+,\s*(\w+)', body))
		for om in re.finditer(r'\+0x([0-9a-f]+)\b', c):
			off = int(om.group(1), 16)
			cands = set()
			for u in used:
				for st, o, full in byname.get(u, ()):
					if o == off:
						cands.add(full)
			line = t.count('\n', 0, cm.start() + om.start()) + 1
			before = re.sub(r'\s+', ' ', c[max(0, om.start() - 60):om.start()])
			after = re.sub(r'\s+', ' ', c[om.end():om.end() + 25])
			items.append((p, line, cm.start() + om.start(), om.group(0), sorted(cands), before, after))

if applyf:
	choice = {}
	for line in open(applyf, encoding='utf-8'):
		line = line.rstrip('\n')
		if not line.strip() or line.startswith('#'):
			continue
		k, _, name = line.partition(' ')
		choice[int(k)] = name
	byfile = {}
	for i, it in enumerate(items):
		if i in choice:
			byfile.setdefault(it[0], []).append((it[2], it[3], choice[i]))
	n = 0
	for p, reps in byfile.items():
		t = open(p, encoding='latin-1', newline='').read()
		for pos, old, new in sorted(reps, reverse=True):
			assert t[pos:pos + len(old)] == old, (p, pos, old)
			t = t[:pos] + new + t[pos + len(old):]
			n += 1
		open(p, 'w', encoding='latin-1', newline='').write(t)
	print(n, 'written')
else:
	for i, (p, line, pos, old, cands, before, after) in enumerate(items):
		prop = cands[0] if len(cands) == 1 else ('?' + '|'.join(cands[:4]) if cands else '?')
		v = int(old[3:], 16)
		if len(cands) != 1 and v >= 0x1000:
			alt = [s + ':' + sorted(flat[s][v], key=len)[0] for s in ('Scene', 'Stage', 'Player', 'PlayerRecord') if v in flat[s]]
			if alt:
				prop += ' {' + ', '.join(alt) + '}'
		print('%d %s:%d %s -> %s | ...%s[%s]%s' % (i, os.path.basename(p), line, old, prop, before[-55:], old, after))
	print(len(items), 'offsets;', sum(1 for it in items if len(it[4]) == 1), 'with one candidate')
