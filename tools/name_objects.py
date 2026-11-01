r"""name_objects.py objects.csv [--dry]: the game's arrays, buffers and records named (step 3b).

Each line "address,element type,count,name[,note]" ('#' starts a comment): count elements of the type from the
address (an extent the code shows, or what is known of it - the note says which). The tool
  - defines the name in src/objects.h: #define name ((type *)IMG(0x...)) - the original address in the harness, the
    object's place in AxisRC.exe - and removes a file's or game.h's own #define of the same pointer;
  - writes the uses: (type *)IMG(0x...) -> name, any other IMG(0x...) at its start -> OBJ(name), inside it ->
    OBJ(name) + offset;
  - records it in tools/names/objects.txt, which tools/mkdatasrc.py makes members of g_rdata / g_data (with their
    extents, offsets checked).
An object that overlaps one already named stops the run; one that holds named globals too, unless --records (a
record or array of named globals: split out as a whole, they are offsets in it - tools/mkdatasrc.py)."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
SIZES = {'char': 1, 'u8': 1, 'signed char': 1, 'u16': 2, 'short': 2, 'int': 4, 'u32': 4, 'float': 4, 'double': 8, 'Colour': 16}
REG = 'tools/names/objects.txt'
known = [l.split() for l in open(REG)] if os.path.exists(REG) else []
rows = []
for line in open(sys.argv[1], encoding='utf-8'):
	line = line.split('#', 1)[0].strip()
	if line:
		p = [x.strip() for x in line.split(',')]
		rows.append((int(p[0], 16), p[1], int(p[2], 0), p[3], p[4] if len(p) > 4 else ''))
globals_addr = {int(a, 16): n for n, a in re.findall(r'#define (\w+) GAME_VAR\([\w \*]+, (0x[0-9a-f]+)\)', open('src/globals.h').read())}
spans = [(int(k[0], 16), int(k[0], 16) + SIZES.get(k[1].replace('_', ' '), 1) * int(k[2]), k[3]) for k in known]
bad = 0
for a, t, n, name, note in rows:
	if t not in SIZES:
		print('unknown type', t, name); bad += 1; continue
	end = a + SIZES[t] * n
	for lo, hi, other in spans:
		if lo < end and a < hi:
			print('%s overlaps %s' % (name, other)); bad += 1
	inner = [g for ga, g in globals_addr.items() if a <= ga < end]
	if inner and '--records' not in sys.argv:
		print('%s holds named globals %s (a record of them: --records)' % (name, ', '.join(inner[:4]))); bad += 1
	spans.append((a, end, name))
if bad:
	sys.exit('%d problems, nothing changed' % bad)
files = [f for f in glob.glob('src/**/*.[ch]', recursive=True)
         if os.path.basename(os.path.dirname(f)) != 'data' and not f.endswith(('axis.h', 'globals.h', 'objects.h'))]
count = 0
for f in files:
	t = open(f, 'rb').read().decode('latin-1')
	orig = t
	for a, ty, n, name, note in rows:
		end = a + SIZES[ty] * n
		# a file's (or game.h's) own pointer name for it goes: the name is objects.h's now
		t = re.sub(r'^[ \t]*#define[ \t]+%s[ \t]+\(\((?:const\s+)?[\w ]+\*\)IMG\(0x0*%x\)\)[^\n]*\r?\n' % (re.escape(name), a), '', t, flags=re.M)
		def cast(m):
			return name if re.sub(r'\s+', ' ', m.group(1).replace('const ', '')).strip() == ty + ' *' else m.group(0)
		t = re.sub(r'\(((?:const\s+)?%s\s*\*)\)\s*IMG\(0x0*%x\)' % (re.escape(ty), a), cast, t)
		def inside(m):
			v = int(m.group(1), 16)
			if v == a:
				return 'OBJ(%s)' % name
			if a < v < end:
				return '(OBJ(%s) + 0x%x)' % (name, v - a)
			return m.group(0)
		t = re.sub(r'\bIMG\((0x[0-9a-f]+)\)', inside, t)
		# a bare base with an index (GAME_VAR(int, 0x83a9cc + i * 4)): OBJ(name) + ..., in code (not comments)
		def bare(line):
			cut = line.find('/*')
			code, rest = (line, '') if cut < 0 else (line[:cut], line[cut:])
			if code.lstrip().startswith('*'):
				return line
			return re.sub(r'(?<![\w.])0x0*%x\b(?=\s*[-+])' % a, 'OBJ(%s)' % name, code) + rest
		t = '\n'.join(bare(l) for l in t.split('\n'))
	# a bare number at or inside a new object, outside IMG() (GAME_VAR(int, 0x... - k * 4) and the like): not
	# rewritten - written by hand, else that access stays at the old place once the object is split
	for i, l in enumerate(t.split('\n')):
		code = re.sub(r'/\*.*?\*/|//.*|"(?:\\.|[^"\\])*"|\bIMG\(0x[0-9a-f]+\)|#define\s+\w+\s+\(\([^)]*\)IMG\(0x[0-9a-f]+\)\)', '', l)
		for m in re.finditer(r'\b0x0*([0-9a-f]{6})\b', code):
			v = int(m.group(1), 16)
			for a, ty, n, name, note in rows:
				if a <= v < a + SIZES[ty] * n:
					print('WRITE BY HAND: %s:%d 0x%x is in %s: %s' % (f, i + 1, v, name, l.strip()[:100]))
	if t != orig:
		count += 1
		if '--dry' not in sys.argv:
			open(f, 'wb').write(t.encode('latin-1'))
if '--dry' not in sys.argv:
	hdr = 'src/objects.h'
	head = open(hdr).read() if os.path.exists(hdr) else (
		'/* objects.h: the game\'s arrays, buffers and records by name (tools/name_objects.py): each the original address in\n'
		'   the harness, its place in AxisRC.exe (IMG; in AxisRC.exe a member of g_rdata / g_data, src/data/layout.h).\n'
		'   OBJ(name) is its address as a number (src/axis.h). Element type, count: the extent known (see the note) */\n'
		'#pragma once\n')
	for a, ty, n, name, note in rows:
		head += '#define %s ((%s *)IMG(0x%x))   /* %s[%d]%s */\n' % (name, ty, a, ty, n, ('; ' + note) if note else '')
	open(hdr, 'w', newline='\n').write(head)
	with open(REG, 'a', newline='\n') as r:
		for a, ty, n, name, note in rows:
			r.write('0x%x %s %d %s\n' % (a, ty.replace(' ', '_'), n, name))
print('%d objects, %d files' % (len(rows), count))
