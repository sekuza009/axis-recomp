"""Raw addresses and offsets in src comments replaced by names.
  data addresses (0x4a9000 .. 0xb6b000) exactly at a named global / constant  -> its name
  code addresses exactly at a named function (not the address label a comment starts with) -> its name
  +offsets >= 0x10000 in the comment right above a function whose this is a Scene / Stage, exactly at a field (or an
  array element / member inside one) -> the field path
A name the comment already mentions is not put in again (the number stays). --apply writes; else a dry run."""
import os, re, glob, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
apply = '--apply' in sys.argv
verbose = '-v' in sys.argv

# ---- globals and constants by address
gaddr = {}
for h in ('src/globals.h', 'src/objects.h'):
	for line in open(h, encoding='latin-1'):
		m = re.match(r'#define ([gk]_\w+) .*?\b(?:GAME_VAR\([^,]+,\s*|IMG\()(0x[0-9a-f]+)\)', line)
		if m:
			gaddr.setdefault(int(m.group(2), 16), m.group(1))
base = {v: k for k, v in gaddr.items()}
for line in open('src/objects.h', encoding='latin-1'):
	m = re.match(r'#define (g_\w+) .*?\((g_\w+) \+ (0x[0-9a-f]+|\d+)\)', line)
	if m and m.group(2) in base:
		gaddr.setdefault(base[m.group(2)] + int(m.group(3), 0), m.group(1))
# ---- functions by address
faddr = {}
for h in ('src/game.h', 'src/calls.h'):
	for m in re.finditer(r'GAME_(?:THIS)?FN\((\w+), (0x[0-9a-f]+)', open(h, encoding='latin-1').read()):
		faddr.setdefault(int(m.group(2), 16), m.group(1))
for p in glob.glob('src/**/*.c', recursive=True):
	for m in re.finditer(r'FN_ADDR\((\w+), (0x[0-9a-f]+)\)', open(p, encoding='latin-1').read()):
		faddr.setdefault(int(m.group(2), 16), m.group(1))

# ---- structs
PRIM = {'u8': 1, 'i8': 1, 'char': 1, 'signed char': 1, 'u16': 2, 'i16': 2, 'short': 2, 'u32': 4, 'i32': 4, 'int': 4,
        'float': 4, 'void *': 4}
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


def resolve(st, off, depth=0):
	"""the field path at exactly off in struct st, or None"""
	if depth > 4 or st not in structs:
		return None
	best = None
	for fo, fs, ty, name, dims in sorted(structs[st], key=lambda f: (f[1], f[0])):
		if not (fo <= off < fo + fs):
			continue
		rel = off - fo
		tname = ty.replace('*', '').strip()
		if dims:
			n = 1
			for d in dims:
				n *= d
			es = fs // n if n else fs
			k, rem = divmod(rel, es) if es else (0, rel)
			idx = '[%d]' % k if len(dims) == 1 else None
			if rel == 0:
				return name
			if idx is None:
				continue
			if k == 0:
				idx = '[]'
			if tname in ('u8', 'char', 'i8', 'signed char'):
				continue
			if rem == 0 and (tname not in structs or '*' in ty):
				return name + idx
			if tname in structs and '*' not in ty:
				sub = resolve(tname, rem, depth + 1)
				if sub:
					return name + idx + '.' + sub
				if rem == 0:
					return name + idx
			continue
		if rel == 0 and (tname not in structs or '*' in ty):
			best = best or name
			continue
		if tname in structs and '*' not in ty:
			sub = resolve(tname, rel, depth + 1)
			if sub:
				return name + '.' + sub
			if rel == 0:
				best = best or name
	return best


def this_struct(params, body, filetext):
	first = params.split(',')[0].strip()
	m = re.match(r'(?:const\s+)?(\w+)\s*\*\s*(\w+)$', first)
	if not m:
		return None
	ty, name = m.group(1), m.group(2)
	if ty in ('Scene', 'Stage'):
		return ty
	for src in (body, filetext):
		m2 = re.search(r'\(\s*(Scene|Stage)\s*\*\s*\)\s*\(?\s*%s\b' % re.escape(name), src)
		if m2:
			return m2.group(1)
	if re.search(r'SCENE_STAGE\(\s*%s\s*\)|STAGE\(\s*%s\s*\)' % (re.escape(name), re.escape(name)), body):
		return 'Scene'
	return None


stats = {'global': 0, 'func': 0, 'field': 0}
samples = []
files = [p for p in glob.glob('src/**/*.c', recursive=True) if 'data' not in os.path.dirname(p)]
for p in files:
	t = open(p, encoding='latin-1', newline='').read()
	out, pos = [], 0
	for cm in re.finditer(r'/\*.*?\*/', t, re.S):
		c = cm.group(0)
		after = t[cm.end():cm.end() + 400]
		fd = re.match(r'\s*\n[^\n;{]*?\((\w+)\)\s*\(([^)]*)\)\s*\{', after)
		st = None
		if fd:
			body_end = t.find('\n}', cm.end())
			st = this_struct(fd.group(2), t[cm.end():body_end], t)
		label_end = 0
		ml = re.match(r'/\*\s*(?:0x[0-9a-f]+(?:\s*(?:,|/|\.\.|and)\s*)?)+', c)
		if ml:
			label_end = ml.end()

		def sub_hex(m):
			if m.start() < label_end:
				return m.group(0)
			v = int(m.group(1), 16)
			name = None
			kind = None
			around = c[max(0, m.start() - 4):m.end() + 4]
			if '..' in around:
				return m.group(0)
			if 0x4a9000 <= v < 0xb6b000 and v in gaddr:
				name, kind = gaddr[v], 'global'
			elif 0x401000 <= v < 0x4a9000 and v in faddr:
				name, kind = faddr[v], 'func'
			if not name or re.search(r'\b%s\b' % re.escape(name), c):
				return m.group(0)
			stats[kind] += 1
			samples.append((p, m.group(0), name))
			return name

		def sub_off(m):
			v = int(m.group(1), 16)
			if not st or v < 0x10000:
				return m.group(0)
			path = resolve(st, v)
			if not path or re.search(r'\b%s\b' % re.escape(path.split('[')[0].split('.')[0]), c):
				return m.group(0)
			stats['field'] += 1
			samples.append((p, m.group(0), path))
			return path

		c2 = re.sub(r'(?<![\w+$\\])0x([0-9a-f]{6})\b(?!\s*\))?', sub_hex, c)
		c2 = re.sub(r'\+0x([0-9a-f]+)\b', sub_off, c2)
		out.append(t[pos:cm.start()])
		out.append(c2)
		pos = cm.end()
	out.append(t[pos:])
	nt = ''.join(out)
	if apply and nt != t:
		open(p, 'w', encoding='latin-1', newline='').write(nt)
print(stats)
if verbose:
	for s in samples:
		print('%-28s %-12s -> %s' % (os.path.basename(s[0]), s[1], s[2]))
