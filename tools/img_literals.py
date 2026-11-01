r"""img_literals.py [--dry] [--list]: the remaining address literals of the game's image in src/ - in tables, as
arguments, assigned - written IMG(0x...) (src/axis.h; in the harness IMG(a) is a, so its objects do not change).

Only a value that is a known address of the image counts: a global's (src/globals.h), the start of a piece of
src/data (each string, each table), what a word of src/data points at, or what src/ already writes as IMG(0x...);
and not where a literal is an offset: after + or -, as the offset of an access macro (S(type, 0x...),
FIELD(type, obj, 0x...)...), in scene.h. So a Stage offset (0x9ccfd4) or a float's bits stay numbers."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
LO, HI = 0x401000, 0xb6b000
known = set()
for m in re.finditer(r'GAME_VAR\([\w \*]+, (0x[0-9a-f]+)\)', open('src/globals.h').read()):
	known.add(int(m.group(1), 16))
for f in glob.glob('src/data/*.c'):
	t = open(f, encoding='latin-1').read()
	known |= {int(a, 16) for a in re.findall(r'\{ (0x[0-9a-f]+), \w+, sizeof', t)}
	known |= {int(a, 16) for a in re.findall(r'IMG\((0x[0-9a-f]+)\)', t)}
srcs = [f for f in glob.glob('src/**/*.[ch]', recursive=True)
        if os.path.basename(os.path.dirname(f)) != 'data' and not f.endswith(('globals.h', 'scene.h', 'axis.h'))]
for f in srcs:
	known |= {int(a, 16) for a in re.findall(r'IMG\((0x[0-9a-f]+)\)', open(f, encoding='latin-1').read())}
OFFSET_MACRO = re.compile(r'\b(?!GAME_VAR\b|GAME_FN\b|GAME_THISFN\b|FN_ADDR\b|IMG\b|RELOC\b|IMPORT\b)[A-Za-z_]\w*\(\s*(?:[^(),]+,\s*){1,2}$')
total = 0
for f in sorted(srcs):
	t = open(f, 'rb').read().decode('latin-1')
	mask = re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: '\0' * len(m.group(0)), t, flags=re.S)
	out, k, n = [], 0, 0
	# statements (to ';' or a line's end outside braces) that already use IMG: their other addresses go along, so
	# that a call's start and end, a table's entries, are all relocated or none (rect_spec(IMG(start), end, ...))
	with_img = []
	if '--siblings' in sys.argv:
		for s in re.finditer(r'[^;{}]*(?:\{[^{}]*(?:\{[^{}]*\}[^{}]*)*\}[^;{}]*)*;', mask):
			if 'IMG(0x' in s.group(0):
				with_img.append((s.start(), s.end()))
		for s in re.finditer(r'\bfor\s*\(', mask):   # (a for's header is one unit: its start, test and step)
			depth, j = 0, s.end() - 1
			while j < len(mask):
				depth += {'(': 1, ')': -1}.get(mask[j], 0)
				if depth == 0:
					break
				j += 1
			if 'IMG(0x' in mask[s.start():j]:
				with_img.append((s.start(), j))
	def in_img_statement(pos):
		return any(lo <= pos < hi for lo, hi in with_img)
	for m in re.finditer(r'(?<![\w.])0x0*([0-9a-f]{6,7})\b', mask):
		a = int(m.group(1), 16)
		# (an address into the original's .rdata or initialised .data, 0x4a9000 .. 0x4d2000, counts as known too:
		# vtables, tables, constants - no number of the game is 4.8 .. 5 million, and as a float's bits it would be
		# a denormal)
		if not LO <= a < HI or (a not in known and not 0x4a9000 <= a < 0x4d2000 and not in_img_statement(m.start())):
			continue
		line_start = mask.rfind('\n', 0, m.start()) + 1
		pre = mask[line_start:m.start()]
		if re.search(r'IMG\(\s*$|FN_ADDR\(\w+,\s*$|FN_VIA\(\w+,\s*0x\w+,\s*$|GAME_(?:THIS)?FN\(\w+,\s*$|\bcase\s*$', pre):
			continue
		if re.search(r'[-+]\s*$', pre) or re.match(r'\s*[-+*]', mask[m.end():m.end() + 3]) and not re.search(r'[,({=]\s*$', pre):
			continue   # (an offset, or a base with an offset added: GAME_VAR relocates those)
		if re.search(r'\b(K|F|T|FMT)\(\s*$', pre):
			continue   # (a file's own pointer macro: it relocates its argument itself)
		if re.search(r'\b(IMPORT|GAME_CDECL|GAME_THISCALL|PATCHED_CALL|PATCHED_THISCALL|code_matches)\(\s*$', pre):
			continue   # (relocated by the macro itself)
		if re.search(r'GAME_VAR\([^()]*,\s*$', pre):
			continue   # (relocated by GAME_VAR itself)
		if OFFSET_MACRO.search(pre) and not re.search(r'\b(memcpy|memset|strcpy|strcmp|sprintf|text_\w+|\w+_draw\w*)\(', pre[-60:]):
			# the second / third argument of an access macro: S(int, 0x...), FIELD(type, obj, 0x...) - an offset
			mac = OFFSET_MACRO.search(pre).group(0)
			if re.match(r'(S|A|G|R|P|F|I|U|AI|AU|AF|OF|FIELD\w*|PLAYER\w*|STAGE\w*|W16|W32|BITS)\(', mac):
				continue
		if re.match(r'\s*#define\s+\w+\s+\(?\s*0x', mask[line_start:m.end()]) and not re.search(r'\(\s*$', pre):
			pass
		if '--list' in sys.argv:
			print('%s: %s' % (f, t[line_start:mask.find('\n', m.end())].strip()[:150]))
		out.append(t[k:m.start()] + 'IMG(' + t[m.start():m.end()] + ')')
		k = m.end(); n += 1
	if n:
		total += n
		if '--list' not in sys.argv:
			print('%-40s %d' % (f, n))
		if '--dry' not in sys.argv and '--list' not in sys.argv:
			open(f, 'wb').write((''.join(out) + t[k:]).encode('latin-1'))
print(total, 'literals')
