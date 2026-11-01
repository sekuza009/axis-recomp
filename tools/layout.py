r"""layout.py [--pages] [--free out.txt]: which pages (4 KB) of the game's image can become C variables (step 3b), and
what blocks the others.

A page can be carved when everything on it is reached only by name:
  - every address of the page AxisRC.exe is built from (src/ - not globals.h' own definitions -, the patch layer,
    standalone/) is the start of a named global (src/globals.h): IMG(0x...), a plain literal, a src/data word
    pointing there - those become the global's address (ADDR(name));
  - no named global of it is used by address other than as (*(type *)&name) or &name (an extent beyond its type);
  - no initialised byte of it outside the names' extents (data no name holds);
  - each name's extent (the largest type it is read as) inside carvable pages.
Without names a page is free when nothing refers to it and it holds no initialised data (its bytes are never
used: such pages need no variables). Out: counts; --pages each page's blockers; --free the carvable pages' names."""
import collections, glob, os, re, struct, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
LO, HI = 0x4a9000, 0xb6b000
SIZES = {'char': 1, 'u8': 1, 'signed char': 1, 'u16': 2, 'short': 2, 'i16': 2, 'int': 4, 'u32': 4, 'i32': 4, 'float': 4,
         'long': 4, 'double': 8, 'va_list': 4, 'Cleanup': 4}


def size_of(t):
	t = re.sub(r'\s+', ' ', t.strip()).replace('const ', '').replace('volatile ', '')
	return 4 if t.endswith('*') else SIZES.get(t)


def strip(t):
	return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: ' ' * len(m.group(0)), t, flags=re.S)


names = {}
for m in re.finditer(r'#define (\w+) GAME_VAR\(([\w \*]+), (0x[0-9a-f]+)\)', open(os.path.join(R, 'src', 'globals.h')).read()):
	names[m.group(1)] = (m.group(2).strip(), int(m.group(3), 16))
starts = {a: n for n, (t, a) in names.items()}
extent = {n: size_of(t) or 0 for n, (t, a) in names.items()}
# the arrays, buffers and records of src/objects.h (tools/names/objects.txt), with their extents
OBJ_SIZES = {'char': 1, 'u8': 1, 'signed_char': 1, 'u16': 2, 'short': 2, 'int': 4, 'u32': 4, 'float': 4, 'double': 8, 'Colour': 16}
for line in open(os.path.join(R, 'tools', 'names', 'objects.txt')):
	a, ty, n, name = line.split()
	names[name] = ('u8', int(a, 16))
	starts[int(a, 16)] = name
	extent[name] = OBJ_SIZES[ty] * int(n)

files = [f for f in glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True) if not f.endswith(('globals.h', 'scene.h'))]
files += [os.path.join(R, 'axisnet_recomp.c')] + glob.glob(os.path.join(R, 'standalone', '*.[ch]'))
refs = collections.defaultdict(list)    # page -> [(file, address)] that are not a name's start
named_refs = collections.Counter()      # name -> references by address (start)
taken = collections.defaultdict(list)
for f in files:
	code = strip(open(f, 'rb').read().decode('latin-1'))
	data = os.path.basename(os.path.dirname(f)) == 'data'
	base = os.path.basename(f)
	for line in code.split('\n'):
		if data and re.match(r'\s*\{ 0x[0-9a-f]+, \w+, sizeof', line):
			continue   # (a piece's placement: handled with the page's own data)
		if re.match(r'\s*#define\s+\w+\s+GAME_VAR\(', line) and not data:
			continue
		for m in re.finditer(r'(?<![\w.])0x0*([0-9a-f]{5,7})\b', line):
			a = int(m.group(1), 16)
			if not LO <= a < HI:
				continue
			pre = line[:m.start()]
			if re.search(r'[-+]\s*$', pre) and not data:
				continue   # (an offset added to something: an object's own field, not an image address)
			if a in starts and not re.match(r'\s*[-+*]', line[m.end():m.end() + 3]):
				named_refs[starts[a]] += 1
			else:
				refs[a >> 12].append((base, a))
		for m in re.finditer(r'&\s*(g_\w+|k_\w+)\b', line):
			n = m.group(1)
			if n in names:
				c = re.search(r'\(\*\(([\w \*]+?) ?\*\)\s*$', line[:m.start()])
				if c and size_of(c.group(1)):
					extent[n] = max(extent[n], size_of(c.group(1)))
				elif not re.match(r'\s*[,)]', line[m.end():]):
					taken[n].append(base)   # (&name used in arithmetic or indexed: the extent is unknown)

b = open(os.path.join(R, 'installed.exe'), 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; nsec = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
init = bytearray(HI - LO)
for i in range(nsec):
	nm, vs, va, rs, rp = struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i)
	if nm.rstrip(b'\0') in (b'.rdata', b'.data'):
		d = b[rp:rp + min(rs, vs)]
		init[0x400000 + va - LO:0x400000 + va - LO + len(d)] = d
covered = bytearray(HI - LO)
for n, (t, a) in names.items():
	for k in range(max(extent[n], 1)):
		if LO <= a + k < HI:
			covered[a + k - LO] = 1

pages = {}
for p in range(LO >> 12, HI >> 12):
	ns = [n for n, (t, a) in names.items() if a >> 12 == p]
	why = []
	if refs.get(p):
		why.append('%d references inside objects or to unnamed data (%s)' % (len(refs[p]), ', '.join(sorted({'%s 0x%x' % x for x in refs[p]}))[:110]))
	if [n for n in ns if n in taken]:
		why.append('&name used as an address: ' + ', '.join(n for n in ns if n in taken)[:80])
	if [n for n in ns if not size_of(names[n][0])]:
		why.append('untyped: ' + ', '.join(n for n in ns if not size_of(names[n][0])))
	stray = sum(1 for k in range((p << 12) - LO, ((p + 1) << 12) - LO) if init[k] and not covered[k])
	if stray:
		why.append('%d initialised bytes no name holds' % stray)
	pages[p] = (ns, why)
changed = True
while changed:
	changed = False
	for p, (ns, why) in pages.items():
		if why:
			continue
		for n in ns:
			t, a = names[n]
			q = (a + max(extent[n], 1) - 1) >> 12
			if q != p and pages.get(q, ([], ['?']))[1]:
				why.append('%s reaches a blocked page' % n); changed = True

free_named = sorted(p for p, (ns, why) in pages.items() if not why and ns)
free_empty = [p for p, (ns, why) in pages.items() if not why and not ns]
print('pages %d: carvable with names %d (%d names), unused %d, blocked %d' % (
	len(pages), len(free_named), sum(len(pages[p][0]) for p in free_named), len(free_empty), sum(1 for p in pages.values() if p[1])))
print('names %d; used by address beyond their type: %d; references not at a name\'s start: %d' % (
	len(names), len(taken), sum(len(v) for v in refs.values())))
if '--pages' in sys.argv:
	for p, (ns, why) in sorted(pages.items()):
		if ns or why:
			print('%06x %-5s %3d names  %s' % (p << 12, 'FREE' if not why else '', len(ns), '; '.join(why)[:200]))
if '--free' in sys.argv:
	with open(sys.argv[sys.argv.index('--free') + 1], 'w', newline='\n') as f:
		for p in free_named:
			for n in sorted(pages[p][0], key=lambda n: names[n][1]):
				f.write('%s %s 0x%x %d\n' % (n, names[n][0], names[n][1], max(extent[n], 1)))
