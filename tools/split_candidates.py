r"""split_candidates.py [--list] [--out file]: the named globals of g_data (src/globals.h, 0x4ad000 .. 0xb13000) that can
be split into variables of their own - those reached only by their name:
  - no number anywhere AxisRC.exe is built from (src/ - but globals.h's definitions and Stage offsets in S() /
    FIELD() / after + -, the patch layer, src/data's pointer words) falls inside the global's extent;
  - its address is no record's base: ADDR(name) / &name never with arithmetic, never given to memset / memcpy /
    strcpy / a copy helper, never read as a wider type than its own ((*(T *)&name) of a larger T).
Each one split is then checked at run time: the fence build (variables beside guard pages) and the old place's
canary (standalone/main.c)."""
import collections, glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
SIZES = {'char': 1, 'u8': 1, 'signed char': 1, 'u16': 2, 'short': 2, 'int': 4, 'u32': 4, 'i32': 4, 'float': 4, 'double': 8}
def size_of(t):
	t = re.sub(r'\s+', ' ', t.strip()).replace('const ', '')
	return 4 if t.endswith('*') else SIZES.get(t, 4)
names = {n: (t.strip(), int(a, 16)) for n, t, a in re.findall(r'#define (\w+) GAME_VAR\(([\w \*]+), (0x[0-9a-f]+)\)', open('src/globals.h').read())}
cands = {n: (t, a, size_of(t)) for n, (t, a) in names.items() if 0x4ad000 <= a < 0xb13000}
objects = {}
for line in open('tools/names/objects.txt'):
	a, ty, n, name = line.split()
	objects[int(a, 16)] = name
def strip(t):
	return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: ' ' * len(m.group(0)), t, flags=re.S)
files = [f for f in glob.glob('src/**/*.[ch]', recursive=True) if not f.endswith(('globals.h', 'scene.h'))]
files += ['axisnet_recomp.c'] + glob.glob('standalone/*.c')
# the globals whose addresses are only in reviewed tables (tools/names/split_tables_ok.txt; each entry one 4-byte
# value): stored in a table is no reason to hold them back, if they are 4 bytes or more
sys.path.insert(0, os.path.join(os.getcwd(), 'tools'))
import split_tables
ok_tables, ok_except = set(), set()
for line in open('tools/names/split_tables_ok.txt'):
	w = line.split('#')[0].split()
	if w:
		ok_tables.add((w[0], w[1]))
		ok_except.update(x[1:] for x in w[2:] if x.startswith('-'))
in_tables = collections.defaultdict(set)
for key, (line, decl, inside) in split_tables.tables.items():
	for n in inside:
		in_tables[n].add(key)
table_ok = {n for n, keys in in_tables.items() if keys <= ok_tables and n not in ok_except and n in cands and cands[n][2] >= 4}
def enclosing_call(text):
	"""the name of the call whose argument list text ends inside (fadd_m(fmul_m(x, y), | -> fadd_m), else None"""
	depth = 0
	for i in range(len(text) - 1, -1, -1):
		if text[i] == ')':
			depth += 1
		elif text[i] == '(':
			if depth == 0:
				m = re.search(r'(\w+)\s*$', text[:i])
				return m.group(1) if m else None
			depth -= 1
	return None
ptr_ok = {l.split('#')[0].strip() for l in open('tools/names/split_ptr_ok.txt')} - {''}   # (reviewed: one value)
numbers = collections.Counter()
based = {}
why = collections.defaultdict(set)
for f in files:
	code = strip(open(f, 'rb').read().decode('latin-1'))
	data = os.path.basename(os.path.dirname(f)) == 'data'
	for line in code.split('\n'):
		if data and re.match(r'\s*\{ 0x[0-9a-f]+, \w+, (?:sizeof \w+|\d+) \},', line):
			continue
		for m in re.finditer(r'(?<![\w.])0x0*([0-9a-f]{6})\b', line):
			v = int(m.group(1), 16)
			pre = line[:m.start()]
			if re.search(r'[-+]\s*$', pre) and not data:
				continue
			if re.search(r'\b(S|A|G|R|P|I|U|AI|AU|AF|OF|FIELD\w*|PLAYER\w*|STAGE\w*|W16|W32)\([^()]*,\s*$', pre):
				continue
			if f == 'axisnet_recomp.c' and re.search(r'\bIMG\(\s*$', pre) and re.match(r'\s*\)', line[m.end():]):
				continue   # (the patch layer's IMG(0x...) of .data goes through axis_dataAt: to the split variable)
			numbers[v] += 1
			if re.match(r'\s*\+', line[m.end():]):   # (a base with an index added: what follows it is reached too)
				based[v] = True
		for m in re.finditer(r'\bADDR\((\w+)\)|&\s*(\w+)\b', line):
			n = m.group(1) or m.group(2)
			if n not in cands:
				continue
			after, before = line[m.end():m.end() + 4], line[:m.start()]
			if re.match(r'\s*[-+]', after) or re.search(r'[-+]\s*$', before):
				why[n].add('address arithmetic')
			# (one value: a float given to an FPU helper, fld_m((const float *)ADDR(x)) / fadd_m(a, (const float *)ADDR(x)),
			# or 4 bytes read / written, crt_fwrite((void *)ADDR(x), 4, 1, f))
			one = (re.search(r'\(\s*(?:const\s+)?float\s*\*\s*\)\s*$', before) and enclosing_call(re.sub(r'\(\s*(?:const\s+)?float\s*\*\s*\)\s*$', '', before))
			       in ('fld_m', 'fadd_m', 'fsub_m', 'fsubr_m', 'fmul_m', 'fdiv_m', 'fdivr_m')) \
				or (re.search(r'\b(?:crt_fread|crt_fwrite|fread_scrambled|file_writeScrambled)\(\s*\(\s*(?:const\s+)?void\s*\*\s*\)\s*$', before)
				    and re.match(r'\s*,\s*4\s*,\s*1\b', after + line[m.end() + 4:m.end() + 12]))
			if re.search(r'\(\s*(?:const\s+)?[\w ]+\*\s*\)\s*$', before) and m.group(1) and not one and n not in ptr_ok:
				why[n].add('address arithmetic (made a pointer: indexed)')
			if m.group(1) and re.search(r'\{[^}]*$', before) and re.search(r'=\s*\{', before) and n not in table_ok:
				why[n].add('address arithmetic (stored in a table: a base the code indexes)')
			if re.search(r'\b(memset|memcpy|memmove|strcpy|strncpy|crt_strncpy|lstrcpyA|strcat|sprintf|rect_copy|\w+_copy\w*|clear)\s*\([^;]*$', before):
				why[n].add('given to %s' % re.search(r'\b(memset|memcpy|memmove|strcpy|strncpy|crt_strncpy|lstrcpyA|strcat|sprintf|rect_copy|\w+_copy\w*|clear)\s*\([^;]*$', before).group(1))
			c = re.search(r'\(\*\(([\w \*]+?) ?\*\)\s*$', before)
			if c and size_of(c.group(1)) > cands[n][2]:
				why[n].add('read as the wider %s' % c.group(1).strip())
for n, (t, a, size) in cands.items():
	inside = [v for v in numbers if a <= v < a + size]
	if inside:
		why[n].add('numbers inside it: %s' % ', '.join('0x%x' % v for v in sorted(inside)[:3]))
# a record's base reaches past itself: the globals after it (a size given to memset / memcpy / ..., else 0x40
# bytes) are held back too
reach = {}
for f in files:
	code = strip(open(f, 'rb').read().decode('latin-1'))
	for m in re.finditer(r'\b(?:memset|memcpy|memmove|strncpy|crt_strncpy|\w+_copy\w*)\s*\(([^;]*?)\);', code):
		size = re.search(r',\s*(0x[0-9a-f]+|\d+)\s*$', m.group(1))
		for n in re.findall(r'\bADDR\((\w+)\)|&\s*(g_\w+)', m.group(1)):
			n = n[0] or n[1]
			if n in cands and size:
				reach[n] = max(reach.get(n, 0), int(size.group(1), 0))
for v in based:   # a raw base with an index: the globals after it (0x40 bytes) are held back
	for m2, (t2, a2, s2) in cands.items():
		if v <= a2 < v + 0x40:
			why[m2].add('after an indexed base 0x%x' % v)
# the objects split whole (tools/names/split.txt): a base inside one reaches no further than its end (the record
# moves as one; its named globals are offsets in it), and the globals inside one are split already
OSIZES = dict(SIZES, Colour=16)
split = {l.split('#')[0].strip() for l in open('tools/names/split.txt')} - {''}
split_objects = []
for line in open('tools/names/objects.txt'):
	oa, oty, ocnt, oname = line.split()
	if oname in split:
		split_objects.append((int(oa, 16), int(oa, 16) + OSIZES.get(oty.replace('_', ' '), 1) * int(ocnt)))
def in_split(a):
	return next((hi for lo, hi in split_objects if lo <= a < hi), None)
for n in [n for n in cands if in_split(cands[n][1])]:
	del cands[n]
for n in list(cands):
	if any(w.startswith(('address arithmetic', 'given')) for w in why[n]):
		t, a, size = cands[n]
		end = a + max(reach.get(n, 0x40), size)
		if in_split(a):
			end = min(end, in_split(a))
		for m2, (t2, a2, s2) in cands.items():
			if a < a2 < end:
				why[m2].add('after the record base %s' % n)
ok = sorted(n for n in cands if not why[n])
print('named globals of g_data: %d; splittable: %d; held back: %d' % (len(cands), len(ok), len(cands) - len(ok)))
c = collections.Counter(re.sub(r':.*|to \w+', '', w).strip() for n in cands for w in why[n])
print(dict(c))
if '--list' in sys.argv:
	for n in sorted(cands, key=lambda n: cands[n][1]):
		if why[n]:
			print('  %-28s 0x%06x  %s' % (n, cands[n][1], '; '.join(sorted(why[n]))[:120]))
if '--out' in sys.argv:
	open(sys.argv[sys.argv.index('--out') + 1], 'w', newline='\n').write('\n'.join(ok) + '\n')
