r"""layout.py [--pages] [--csv out]: what still ties the game's globals to their original addresses, page by page
(4 KB of the image 0x4a9000 .. 0xb6b000), for step 3 (globals as C variables in AxisRC.exe).

A page can become variables when nothing reaches it but the names: no address literal in it anywhere AxisRC.exe
is built from (src/ - but globals.h's own definitions and src/data's placement of pieces -, the patch layer,
standalone/), no named global of it used by address other than as (*(type *)&name), no initialised bytes in it
that no name covers, and every name's extent (the largest type it is read as) inside convertible pages.

Out: counts, and with --pages each page's state and what blocks it."""
import collections, glob, os, re, struct, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
LO, HI = 0x4a9000, 0xb6b000
SIZES = {'char': 1, 'u8': 1, 'signed char': 1, 'u16': 2, 'short': 2, 'i16': 2, 'int': 4, 'u32': 4, 'i32': 4, 'float': 4,
         'long': 4, 'double': 8, 'va_list': 4, 'Cleanup': 4}


def size_of(t):
	t = re.sub(r'\s+', ' ', t.strip()).replace('const ', '')
	if t.endswith('*'):
		return 4
	return SIZES.get(t)


def strip_comments(t):
	return re.sub(r'/\*.*?\*/|//[^\n]*', lambda m: ' ' * len(m.group(0)), t, flags=re.S)


names = {}   # name -> (type, address)
for m in re.finditer(r'#define (\w+) GAME_VAR\(([\w \*]+), (0x[0-9a-f]+)\)', open(os.path.join(R, 'src', 'globals.h')).read()):
	names[m.group(1)] = (m.group(2).strip(), int(m.group(3), 16))
by_addr = collections.defaultdict(list)
for n, (t, a) in names.items():
	by_addr[a].append(n)

files = [f for f in glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True) if not f.endswith('globals.h')]
files += [os.path.join(R, 'axisnet_recomp.c')] + glob.glob(os.path.join(R, 'standalone', '*.[ch]'))
raw = collections.defaultdict(list)       # page -> [(file, literal)]
extent = {n: size_of(t) or 0 for n, (t, a) in names.items()}
untyped = {n for n, (t, a) in names.items() if size_of(t) is None}
addr_taken = collections.defaultdict(list)
name_re = re.compile(r'\b(g_\w+|k_\w+)\b')
for f in files:
	text = open(f, 'rb').read().decode('latin-1')
	code = strip_comments(text)
	data = os.path.basename(os.path.dirname(f)) == 'data'
	for line in code.split('\n'):
		if data and re.match(r'\s*\{ 0x[0-9a-f]+, \w+, sizeof', line):
			continue   # (a piece's placement)
		if re.match(r'\s*#define\s+\w+\s+GAME_VAR\(', line) and not data:
			continue   # (a file's own name for a global: the literal is that global's own)
		for m in re.finditer(r'(?<![\w.])0x0*([0-9a-f]{5,7})\b', line):
			a = int(m.group(1), 16)
			if LO <= a < HI:
				raw[a >> 12].append((os.path.basename(f), a))
		# names used by address: (*(T *)&name) is a read as T; anything else takes the address
		for m in re.finditer(r'&\s*(g_\w+|k_\w+)\b', line):
			n = m.group(1)
			if n not in names:
				continue
			before = line[:m.start()]
			c = re.search(r'\(\*\(([\w \*]+?) ?\*\)\s*$', before)
			if c and size_of(c.group(1)):
				extent[n] = max(extent[n], size_of(c.group(1)))
			else:
				addr_taken[n].append((os.path.basename(f), line.strip()[:100]))

# initialised bytes not covered by a name (the installed exe's .rdata / .data)
b = open(os.path.join(R, 'installed.exe'), 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; nsec = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
init = bytearray(HI - LO)
for i in range(nsec):
	nm, vs, va, rs, rp = struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i)
	base = 0x400000 + va
	if nm.rstrip(b'\0') in (b'.rdata', b'.data'):
		d = b[rp:rp + min(rs, vs)]
		init[base - LO:base - LO + len(d)] = d
covered = bytearray(HI - LO)
for n, (t, a) in names.items():
	for k in range(max(extent[n], 1)):
		if LO <= a + k < HI:
			covered[a + k - LO] = 1

pages = {}
for p in range(LO >> 12, HI >> 12):
	ns = [n for n, (t, a) in names.items() if a >> 12 == p]
	why = []
	if raw.get(p):
		why.append('%d raw address literals (%s)' % (len(raw[p]), ', '.join(sorted({'%s 0x%x' % x for x in raw[p]}))[:120]))
	taken = [n for n in ns if addr_taken.get(n)]
	if taken:
		why.append('address taken: ' + ', '.join(taken)[:100])
	if [n for n in ns if n in untyped]:
		why.append('untyped: ' + ', '.join(n for n in ns if n in untyped))
	lo, hi = (p << 12) - LO, ((p + 1) << 12) - LO
	stray = sum(1 for k in range(lo, hi) if init[k] and not covered[k])
	if stray:
		why.append('%d initialised bytes no name covers' % stray)
	pages[p] = (ns, why)
# a name reaching past its page needs the next page free too
changed = True
while changed:
	changed = False
	for p, (ns, why) in pages.items():
		if why:
			continue
		for n in ns:
			t, a = names[n]
			if (a + max(extent[n], 1) - 1) >> 12 != p and pages.get((a + extent[n] - 1) >> 12, ([], ['?']))[1]:
				why.append('%s reaches a blocked page' % n); changed = True

free = [p for p, (ns, why) in pages.items() if not why and ns]
empty_free = [p for p, (ns, why) in pages.items() if not why and not ns]
print('pages: %d; with names and free to convert: %d (%d names); without names or references: %d; blocked: %d' % (
	len(pages), len(free), sum(len(pages[p][0]) for p in free), len(empty_free), sum(1 for p in pages.values() if p[1])))
print('names: %d; read by address in other ways: %d; raw literals in all: %d' % (
	len(names), len(addr_taken), sum(len(v) for v in raw.values())))
if '--pages' in sys.argv:
	for p, (ns, why) in sorted(pages.items()):
		if ns or why:
			print('%06x %-5s %3d names  %s' % (p << 12, 'FREE' if not why else '', len(ns), '; '.join(why)[:230]))
if '--csv' in sys.argv:
	with open(sys.argv[sys.argv.index('--csv') + 1], 'w', newline='\n') as f:
		for p in sorted(free):
			for n in pages[p][0]:
				f.write('%s,%s,0x%x,%d\n' % (n, names[n][0], names[n][1], max(extent[n], 1)))
