r"""split_aliases.py: names defined outside src/globals.h as GAME_VAR(type, 0x...) (game.h's own list, a file's
local names) whose address lies in an object or global split out of g_data (tools/names/split.txt). In AxisRC.exe
such a name still reaches the old place (IMG routes the original address there; only globals.h's names and
objects.h's are mapped to the split variables, src/data/layout_names.h): write it from the split name instead
(g_x -> (g_record[k]), or the global's own name). Exit status 1 when there are any."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
SIZES = {'char': 1, 'u8': 1, 'signed char': 1, 'u16': 2, 'short': 2, 'int': 4, 'u32': 4, 'float': 4, 'double': 8, 'Colour': 16}
split = {l.split('#')[0].strip() for l in open('tools/names/split.txt')} - {''}
spans = []
for n, t, a in re.findall(r'#define (\w+) GAME_VAR\(([\w \*]+), (0x[0-9a-f]+)\)', open('src/globals.h').read()):
	if n in split:
		t = re.sub(r'\s+', ' ', t.strip()).replace('const ', '')
		spans.append((int(a, 16), int(a, 16) + (4 if t.endswith('*') else SIZES.get(t, 4)), n))
for line in open('tools/names/objects.txt'):
	a, ty, cnt, name = line.split()
	if name in split:
		spans.append((int(a, 16), int(a, 16) + SIZES.get(ty.replace('_', ' '), 1) * int(cnt), name))
found = 0
# constants that only look like addresses (tools/names/split_consts_ok.txt: file and number)
consts = set()
for line in open('tools/names/split_consts_ok.txt'):
	w = line.split('#')[0].split()
	if w:
		consts.add((w[0], int(w[1], 16)))
for f in sorted(glob.glob('src/**/*.[ch]', recursive=True)) + sorted(glob.glob('standalone/*.c')):   # (not axisnet_recomp.c: its IMG goes through axis_dataAt, standalone/main.c)
	if f.endswith(('globals.h', 'scene.h', 'main.c')) or os.sep + 'data' + os.sep in f:
		continue   # (scene.h: struct paddings / offsets; standalone/main.c: the sizes of its own blocks)
	text = open(f, 'rb').read().decode('latin-1')
	# comments and strings blanked (line breaks kept): only code's numbers count
	code = re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), text, flags=re.S)
	for i, l in enumerate(code.split('\n')):
		if f.endswith('objects.h') or 'offsetof(Stage' in l or 'fog_and_modes[] =' in l:
			continue   # (the objects' own definitions; Stage offsets - added to a stage's base, not addresses)
		for m in re.finditer(r'(?<![\w.])0x0*([0-9a-f]{6})\b', l):
			a = int(m.group(1), 16)
			pre = l[:m.start()]
			if re.search(r'\b(S|A|G|R|P|U|AI|AU|AF|OF|FIELD\w*|PLAYER\w*|STAGE\w*)\([^()]*,\s*$', pre):
				continue   # (an offset, not an address)
			if re.search(r'[-+]\s*$', pre):
				# (after + or -: an offset from a base pointer (s + 0x9ee058: a Stage's) - or an address with an index
				# in front of it (F(i + 0x4df870)): the latter reported to review unless the base is a known pointer)
				if not re.search(r'\b(s|g|stage|scene|self|st|sc|rec|mesh|model|shape|actor|a|e|m|tm|vv|view|game|obj)\s*[-+]\s*$', pre):
					for lo, hi, n in spans:
						if lo <= a < hi:
							print('REVIEW %s:%d 0x%x after +/- is in split %s: %s' % (f, i + 1, a, n, text.split('\n')[i].strip()[:90]))
				continue
			if (f.replace(os.sep, '/'), a) in consts:
				continue
			for lo, hi, n in spans:
				if lo <= a < hi:
					print('%s:%d 0x%x is in split %s at +0x%x: %s' % (f, i + 1, a, n, a - lo, text.split('\n')[i].strip()[:100]))
					found += 1
review = 0
# a record base outside the split objects whose reach runs into one: ADDR(name) / &name made a pointer, with an
# offset added, or given to a copy (its size the reach, else 0x40 bytes) - the record's rest is read at the old place
gaddr = {n: int(a, 16) for n, a in re.findall(r'#define (\w+) GAME_VAR\([\w \*]+, (0x[0-9a-f]+)\)', open('src/globals.h').read())}
for f in sorted(glob.glob('src/**/*.[ch]', recursive=True)):
	if os.sep + 'data' + os.sep in f:
		continue
	text = open(f, 'rb').read().decode('latin-1')
	code = re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), text, flags=re.S)
	for i, l in enumerate(code.split('\n')):
		for m in re.finditer(r'\bADDR\((\w+)\)|&\s*(g_\w+)\b', l):
			n = m.group(1) or m.group(2)
			if n not in gaddr:
				continue
			before, after = l[:m.start()], l[m.end():]
			copy = re.search(r'\b(memset|memcpy|memmove|strncpy|crt_strncpy|\w+_copy\w*)\s*\([^;]*$', before)
			based = re.search(r'\(\s*(?:const\s+)?[\w ]+\*\s*\)\s*$', before) or re.match(r'\s*[-+]', after) or re.search(r'[-+]\s*$', before)
			if re.search(r'\(\*\(\s*(?:const\s+)?[\w ]+\*\s*\)\s*$', before) and not re.match(r'\s*\)\s*[-+]', after):
				based = None   # ((*(u32 *)&g_x): one value read as another type - split_candidates.py checks the width)
			if not (copy or based):
				continue
			size = re.match(r'[^;]*?,\s*(0x[0-9a-f]+|\d+)\s*\)', after) if copy else None
			a = gaddr[n]
			reach = int(size.group(1), 0) if size else 0x40
			# (a base inside a record split whole reaches no further than that record's end: it moves as one)
			reach = min([reach] + [hi - a for lo, hi, s in spans if lo <= a < hi])
			for lo, hi, s in spans:
				if a < lo < a + reach and not lo <= a < hi:
					print('REVIEW %s:%d %s (0x%x, a record base reaching 0x%x) runs into split %s: %s' % (f, i + 1, n, a, reach, s, text.split('\n')[i].strip()[:90]))
					review += 1
# an object made a pointer to a record ((GameSettings *)OBJ(name)): the record reaches 0x40 bytes past it
oaddr = {}
for line in open('tools/names/objects.txt'):
	a, ty, cnt, name = line.split()
	oaddr[name] = int(a, 16)
for f in sorted(glob.glob('src/**/*.c', recursive=True)):
	if os.sep + 'data' + os.sep in f:
		continue
	text = open(f, 'rb').read().decode('latin-1')
	for i, l in enumerate(text.split('\n')):
		for m in re.finditer(r'\(\s*(?:const\s+)?([A-Z]\w*)\s*\*\s*\)\s*OBJ\((\w+)\)', l):
			if m.group(2) not in oaddr:
				continue
			a = oaddr[m.group(2)]
			for lo, hi, s in spans:
				if a < lo < a + 0x40 and not lo <= a < hi:
					print('REVIEW %s:%d %s (0x%x) made a %s * runs into split %s' % (f, i + 1, m.group(2), a, m.group(1), s))
					review += 1
# a loop that starts in one place and ends at another (for (p = IMG(a); p < ADDR(g_x); ...)): once one of them is
# split the two are no longer in one block - the bound must be written from the start (start + count * stride)
def where(tok):
	m = re.match(r'(?:IMG|RELOC)\((0x[0-9a-f]+)\)|(?:OBJ|ADDR)\((\w+)\)|0x([0-9a-f]{6})$', tok)
	if not m:
		return None
	a = int(m.group(1) or '0x' + (m.group(3) or '0'), 16) if not m.group(2) else gaddr.get(m.group(2), oaddr.get(m.group(2)))
	if a is None:
		return None
	for lo, hi, s in spans:
		if lo <= a < hi:
			return s
	return 'g_data' if 0x4ad000 <= a < 0xb13000 else 'elsewhere'
for f in sorted(glob.glob('src/**/*.c', recursive=True)):
	if os.sep + 'data' + os.sep in f:
		continue
	text = open(f, 'rb').read().decode('latin-1')
	for i, l in enumerate(text.split('\n')):
		ms = list(re.finditer(r'for \([^;]*?\b(\w+) = \(?((?:IMG|OBJ|ADDR|RELOC)\(\w+\))[^;]*; \1 (?:<|<=|!=) \(?((?:IMG|OBJ|ADDR|RELOC)\(\w+\))', l))
		# (or a helper given a start and an end: layouts.c's rect_spec / rects_column / rects_row)
		# (the start may be inside an object, (OBJ(x) + 0x90): the end must be in the same one)
		ms += list(re.finditer(r'\b()(?:rect_spec|rects_column|rects_row)\(\(?(\w+\(\w+\))(?: \+ 0x[0-9a-f]+\))?, \(?(\w+\(\w+\))', l))
		for m in ms:
			a, b = where(m.group(2)), where(m.group(3))
			if a and b and a != b:
				print('%s:%d a loop from %s (%s) to %s (%s): write its end from its start: %s' % (f, i + 1, m.group(2), a, m.group(3), b, l.strip()[:80]))
				found += 1
# a range in the old block that holds split data inside it: a loop between two plain addresses (bare numbers or
# IMG()), or a memset / memcpy / receive of a constant size from one - it walks the old place
def addr_of(tok):
	m = re.match(r'(?:IMG|RELOC)\((0x[0-9a-f]+)\)$|\(?(0x[0-9a-f]{6})\)?$', tok.strip())
	return int(m.group(1) or m.group(2), 16) if m else None
def inside(lo, hi):
	return [s for a, b, s in spans if lo < b and a < hi and not (a == lo)]
for f in sorted(glob.glob('src/**/*.c', recursive=True)):
	if os.sep + 'data' + os.sep in f:
		continue
	text = open(f, 'rb').read().decode('latin-1')
	code = re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), text, flags=re.S)
	for i, l in enumerate(code.split('\n')):
		for m in re.finditer(r'for \([^;]*?\b(\w+) = ((?:IMG|RELOC)\(0x[0-9a-f]+\)|0x[0-9a-f]{6})\s*;\s*\1\s*(<|<=|!=)\s*((?:IMG|RELOC)\(0x[0-9a-f]+\)|0x[0-9a-f]{6})\s*;', l):
			lo, hi = addr_of(m.group(2)), addr_of(m.group(4))
			if lo and hi and 0x4ad000 <= lo < hi:
				for s in inside(lo, hi + (4 if m.group(3) == '<=' else 0)):
					print('%s:%d a loop over 0x%x .. 0x%x walks over split %s: %s' % (f, i + 1, lo, hi, s, text.split('\n')[i].strip()[:80]))
					found += 1
		for m in re.finditer(r'\b(?:memset|memcpy|memmove|reply_read)\s*\(\s*(?:\([^()]*\)\s*)?((?:IMG|RELOC)\(0x[0-9a-f]+\))\s*,[^;]*?,\s*(0x[0-9a-f]+|\d+)\s*\)', l):
			lo, size = addr_of(m.group(1)), int(m.group(2), 0)
			if lo and 0x4ad000 <= lo < 0xb13000:
				for s in inside(lo, lo + size):
					print('%s:%d %d bytes from 0x%x cover split %s: %s' % (f, i + 1, size, lo, s, text.split('\n')[i].strip()[:80]))
					found += 1
print('%d names reach a split object\'s old place; %d record bases to review (REVIEW: a pointer to one value, or a '
      'reach that stops short, is fine)' % (found, review))
sys.exit(1 if found else 0)
