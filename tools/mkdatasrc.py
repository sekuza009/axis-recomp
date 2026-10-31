r"""mkdatasrc.py: the game's initialised data as C (src/data/): .rdata, .data's initialised part and the data stored
in .text (DirectInput's object formats), from installed.exe (the patched exe, as AxisRC.exe's built-in data was).

Every byte comes out exactly; the form is chosen for reading:
  - a word that is a rebuilt function's address (or a compiler jump stub's to one) is FN_ADDR(name, addr) /
    FN_VIA(name, addr, stub): the C function in AxisRC.exe (vtables, the start-up tables, callbacks);
  - text (printable bytes, or the EUC-KR of the Korean messages, ended by a NUL) is a string literal;
  - a word src/ reads as a float, or any word that reads as a short float (1.5, 640, 0.001), is a float; a double
    the same; a word naming a global of the game (an address in its data) carries the name as a comment;
  - other words are hex, odd bytes hex bytes.
Runs of one kind are arrays; a named global (src/globals.h) starts its own, named init_<name>. Zeros of 8 bytes or
more are left out (the image starts zeroed). Out: src/data/{rdata,data,text_data}.c, each with a table of its
pieces { address, bytes, size } that standalone/main.c copies into place (data.h)."""
import collections, csv, glob, math, os, re, struct, sys, importlib.util

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
spec = importlib.util.spec_from_file_location('ht', os.path.join(R, 'tools', 'hooktable.py'))
ht = importlib.util.module_from_spec(spec); spec.loader.exec_module(ht)
hooked = {a: n for a, n in ht.hooks()}

b = open(os.path.join(R, 'installed.exe'), 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; nsec = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
secs = {}
for i in range(nsec):
	nm, vs, va, rs, rp = struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i)
	secs[nm.rstrip(b'\0').decode()] = (0x400000 + va, vs, rs, rp)
def raw(a, n):
	for base, vs, rs, rp in secs.values():
		if base <= a and a + n <= base + rs:
			return b[rp + a - base: rp + a - base + n]
	raise ValueError(hex(a))
text_lo, text_hi = secs['.text'][0], secs['.text'][0] + secs['.text'][1]

# the compiler's jump stubs to rebuilt functions
stubs = {}
for name in ('.rdata', '.data'):
	base, vs, rs, rp = secs[name]
	for o in range(0, min(rs, vs) - 3, 4):
		v = struct.unpack_from('<I', b, rp + o)[0]
		if text_lo <= v < text_hi - 5 and v not in hooked and raw(v, 1) == b'\xe9':
			to = v + 5 + struct.unpack_from('<i', raw(v + 1, 4))[0]
			if to in hooked:
				stubs[v] = to

# names and the types src/ uses
names, types = {}, collections.defaultdict(collections.Counter)
for m in re.finditer(r'#define (\w+) GAME_VAR\(([\w \*]+), (0x[0-9a-f]+)\)', open(os.path.join(R, 'src', 'globals.h')).read()):
	names[int(m.group(3), 16)] = m.group(1)
	types[int(m.group(3), 16)][m.group(2).strip()] += 5
for f in glob.glob(os.path.join(R, 'src', '**', '*.c'), recursive=True):
	for t, a in re.findall(r'GAME_VAR\(\s*([\w ]+?)\s*,\s*(0x[0-9a-f]+)\s*\)', open(f, encoding='latin-1').read()):
		types[int(a, 16)][t] += 1
def typed(a):
	c = types.get(a)
	return c.most_common(1)[0][0] if c else None

# the regions
regions = []
for name, out in (('.rdata', 'rdata'), ('.data', 'data')):
	base, vs, rs, rp = secs[name]
	d = b[rp:rp + min(rs, vs)]
	if name == '.data':
		d = d.rstrip(b'\0')
	regions.append((out, name, base, d))
# data in .text pointed at from the data (not a function's entry or inside one): to the next function
funcs = sorted((int(r['address'], 16), int(r['size'])) for r in csv.DictReader(open(os.path.join(R, '..', 'decomp', 'out', 'functions.csv'))))
starts = [a for a, _ in funcs]
import bisect
def inside(a):
	k = bisect.bisect_right(starts, a) - 1
	return k >= 0 and starts[k] <= a < starts[k] + funcs[k][1]
tpieces = []
for _, _, base, d in regions:
	for o in range(0, len(d) - 3, 4):
		v = struct.unpack_from('<I', d, o)[0]
		if text_lo <= v < text_hi and v not in starts and v not in hooked and v not in stubs and not inside(v):
			nxt = next((s for s in starts if s > v), text_hi)
			tpieces.append([v, nxt])
tpieces.sort(); merged = []
for lo, hi in tpieces:
	if merged and lo <= merged[-1][1]: merged[-1][1] = max(merged[-1][1], hi)
	else: merged.append([lo, hi])


def nice_float(w):
	f = struct.unpack('<f', struct.pack('<I', w))[0]
	if w == 0 or not math.isfinite(f) or not (1e-4 <= abs(f) <= 1e7):
		return None
	for p in range(1, 8):
		s = '%.*g' % (p, f)
		if struct.unpack('<I', struct.pack('<f', float(s)))[0] == w:
			return s
	return None


def float_lit(s):
	return repr(float(s)) + 'f'


def nice_double(lo, hi):
	q = struct.unpack('<d', struct.pack('<II', lo, hi))[0]
	if not math.isfinite(q) or (q != 0 and not (1e-6 <= abs(q) <= 1e9)):
		return None
	for p in range(1, 16):
		s = '%.*g' % (p, q)
		if struct.pack('<d', float(s)) == struct.pack('<II', lo, hi):
			return s if ('.' in s or 'e' in s) else s + '.0'
	return None


def is_text(d, o):
	"""the length of a string at d[o] (without its NUL) when it reads as one, else 0: printable ASCII (tab and line
	breaks too) and the EUC-KR pairs of Korean text; two or three characters only when plain ASCII"""
	n = 0
	while o + n < len(d) and d[o + n]:
		c = d[o + n]
		if 0xb0 <= c <= 0xc8 and o + n + 1 < len(d) and 0xa1 <= d[o + n + 1] <= 0xfe:
			n += 2; continue
		if not (32 <= c < 127 or c in (9, 10, 13)):
			return 0
		n += 1
	if o + n >= len(d) or n < 2:
		return 0
	t = d[o:o + n]
	high = any(c >= 0x80 for c in t)
	if n < 4 and (high or not any(chr(c).isalnum() for c in t)):
		return 0
	if sum(1 for c in t if chr(c).isalnum() or c >= 0xa1 or c in (32, 37)) < n * 0.5:
		return 0
	return n


def c_string(t):
	out, prev_hex = '', False
	for c in t:
		ch = chr(c)
		if ch == '\\': s = '\\\\'
		elif ch == '"': s = '\\"'
		elif ch == '\n': s = '\\n'
		elif ch == '\r': s = '\\r'
		elif ch == '\t': s = '\\t'
		elif 32 <= c < 127:
			s = ('""' if prev_hex and ch in '0123456789abcdefABCDEF' else '') + ch
		else:
			out += '\\x%02x' % c; prev_hex = True; continue
		out += s; prev_hex = False
	return '"%s"' % out


def generate(region_name, section, base, d, comment):
	"""items (address, kind, text, size) for the region's bytes"""
	items, o = [], 0
	n = len(d)
	while o < n:
		a = base + o
		if o % 4 == 0 and o + 4 <= n:
			w = struct.unpack_from('<I', d, o)[0]
			t = typed(a)
			if w in hooked:
				items.append((a, 'u32', 'FN_ADDR(%s, 0x%x)' % (hooked[w], w), 4)); o += 4; continue
			if w in stubs:
				items.append((a, 'u32', 'FN_VIA(%s, 0x%x, 0x%x)' % (hooked[stubs[w]], stubs[w], w), 4)); o += 4; continue
			if o % 8 == 0 and o + 8 <= n and t == 'double':
				lo, hi = struct.unpack_from('<II', d, o)
				s = nice_double(lo, hi)
				if s:
					items.append((a, 'double', s, 8)); o += 8; continue
			# zeros: a gap of 8 or more, else words
			if w == 0:
				z = o
				while z < n and d[z] == 0: z += 1
				if z - o >= 8 or z == n:
					o = z - (z - o) % 4 if z < n and (z - o) % 4 and False else z
					continue
			ln = is_text(d, o)
			if ln < 4 and 0x4a9000 <= w < 0xb6b000:
				ln = 0   # (an address in the image that happens to read as two or three letters)
			if ln and t not in ('float', 'int', 'u32', 'double') and not (t or '').endswith('*'):
				end = o + ln + 1
				items.append((a, 'char', c_string(d[o:o + ln]), ln + 1)); o = end; continue
			f = nice_float(w)
			if t == 'float' or (f and t not in ('int', 'u32', 'u8', 'char', 'u16', 'short') and w > 0xffff):
				if f or t == 'float':
					items.append((a, 'float' if f else 'u32', float_lit(f) if f else '0x%08x' % w, 4)); o += 4; continue
			note = None
			if 0x1000 <= w < 0x100000:   # an import's hint / name entry (the import table's offsets from 0x400000)
				try:
					m = re.match(rb'[A-Za-z_][A-Za-z0-9_]{3,}\0', raw(0x400000 + w + 2, 64))
					if m:
						note = 'import ' + m.group(0)[:-1].decode()
				except ValueError:
					pass
			if 0x4a9000 <= w < 0xb6b000:
				note = ('&' + names[w]) if w in names else None
				try:
					tgt = raw(w, 200)
					k = is_text(tgt, 0)
					if k:
						note = c_string(tgt[:min(k, 48)]) + ('...' if k > 48 else '')
				except ValueError:
					pass
			items.append((a, 'u32', '0x%08x' % w + ('   /* %s */' % note.replace('*/', '* /') if note else ''), 4)); o += 4; continue
		# not word-aligned, or a short tail
		ln = is_text(d, o) if d[o] else 0
		if ln:
			items.append((a, 'char', c_string(d[o:o + ln]), ln + 1)); o += ln + 1; continue
		if d[o] == 0:
			o += 1; continue
		items.append((a, 'u8', '0x%02x' % d[o], 1)); o += 1
	# runs: the same kind, consecutive, not across a named global
	runs = []
	for it in items:
		a, kind, text, size = it
		if (runs and kind == runs[-1]['kind'] and kind != 'char' and runs[-1]['end'] == a and a not in names):
			runs[-1]['items'].append(it); runs[-1]['end'] = a + size
		else:
			runs.append({'kind': kind, 'start': a, 'end': a + size, 'items': [it]})
	lines = ['/* %s: the game\'s %s (%s .. 0x%x), generated by tools/mkdatasrc.py from the installed (patched) exe.' %
	         (region_name, comment, '0x%x' % base, base + len(d)),
	         '   Each piece is copied to its address at start-up (standalone/main.c); see tools/mkdatasrc.py for the forms. */',
	         '#include "../game.h"', '#include "data.h"', '']
	table = []
	for r in runs:
		a = r['start']
		label = ('init_' + names[a]) if a in names else 'd_%06x' % a
		if label in (x[1] for x in table):
			label += '_%06x' % a
		kind = r['kind']
		ctype = {'u32': 'u32', 'float': 'float', 'double': 'double', 'u8': 'u8', 'char': 'char'}[kind]
		if kind == 'char':
			lines.append('static const char %s[] = %s;' % (label, r['items'][0][2]))
		else:
			per = {'u32': 6, 'float': 6, 'double': 4, 'u8': 16}[kind]
			vals = [x[2] for x in r['items']]
			if any('/*' in v or 'FN_' in v for v in vals):
				per = 1 if any('/*' in v for v in vals) else 2
			body = []
			for k in range(0, len(vals), per):
				row = vals[k:k + per]
				if per == 1 and '/*' in row[0]:   # (the comment after the comma)
					v, c = row[0].split('/*', 1)
					body.append('\t%s,   /*%s' % (v.rstrip(), c))
				else:
					body.append('\t' + ', '.join(row) + ',')
			if len(vals) <= per and not any('/*' in v for v in vals):
				lines.append('static const %s %s[] = { %s };' % (ctype, label, ', '.join(vals)))
			else:
				lines.append('static const %s %s[] = {   /* 0x%x */' % (ctype, label, a))
				lines += body
				lines.append('};')
		table.append((a, label, r['end'] - a))
	lines.append('')
	lines.append('const DataPiece g_%sPieces[] = {' % region_name)
	for a, label, size in table:
		lines.append('\t{ 0x%x, %s, sizeof %s },' % (a, label, label))
	lines.append('\t{ 0, 0, 0 }')
	lines.append('};')
	return lines, sum(1 for _ in table), sum(s for _, _, s in table)


os.makedirs(os.path.join(R, 'src', 'data'), exist_ok=True)
total = []
for out, section, base, d in regions:
	lines, k, size = generate(out, section, base, d, {'rdata': 'read-only data', 'data': 'initialised data'}[out])
	open(os.path.join(R, 'src', 'data', out + '.c'), 'w', newline='\n', encoding='latin-1').write('\n'.join(lines) + '\n')
	total.append('%s: %d pieces, %d bytes' % (out, k, size))
# .text's data, as one region per piece
tl = ['/* text_data: data the game keeps in its .text between functions (DirectInput\'s object formats), generated by',
      '   tools/mkdatasrc.py from the installed exe; copied into place at start-up like the rest of src/data. */',
      '#include "../game.h"', '#include "data.h"', '']
ttable = []
for lo, hi in merged:
	lines, k, size = generate('t', '.text', lo, raw(lo, hi - lo), '')
	body = [l for l in lines[5:] if not l.startswith(('const DataPiece', '\t{ 0x', '\t{ 0, 0, 0 }', '};')) or l == '};' and False]
	# (re-collect the pieces from the generated table lines)
	for l in lines:
		m = re.match(r'\t\{ (0x[0-9a-f]+), (\w+), sizeof \w+ \},', l)
		if m:
			ttable.append((m.group(1), m.group(2)))
	tl += [l for l in lines[5:lines.index('const DataPiece g_tPieces[] = {') - 1]]
tl += ['', 'const DataPiece g_text_dataPieces[] = {'] + ['\t{ %s, %s, sizeof %s },' % (a, l, l) for a, l in ttable] + ['\t{ 0, 0, 0 }', '};']
open(os.path.join(R, 'src', 'data', 'text_data.c'), 'w', newline='\n', encoding='latin-1').write('\n'.join(tl) + '\n')
total.append('text_data: %d pieces' % len(ttable))
open(os.path.join(R, 'src', 'data', 'data.h'), 'w', newline='\n').write('''/* data.h: a piece of the game's initialised data (src/data/*.c, tools/mkdatasrc.py): its address and bytes */
#pragma once
typedef struct { u32 address; const void *bytes; u32 size; } DataPiece;
extern const DataPiece g_rdataPieces[], g_dataPieces[], g_text_dataPieces[];
''')
print('; '.join(total))
print('the .text pieces the blob keeps no more:', ['0x%x-0x%x' % (lo, hi) for lo, hi in merged])
