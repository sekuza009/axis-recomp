r"""split_overreach.py: places in src that take a split global's address (ADDR(g_x) / &g_x) and reach past its own
bytes - a helper writing a rectangle (set_box(ADDR(g_left), x0, y0, x1, y1)), a group copied as words, or an offset
added to the address (ADDR(g_x) + 4, PANEL_Y(ADDR(g_x))). A split global (tools/names/split.txt) is a variable of its
own in AxisRC.exe, so its neighbours in the original are no longer next to it: such a reach lands in padding.
Prints each suspect line with the split names; the size each helper reaches is listed in HELPERS."""
import glob, os, re

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
split = {l.split('#')[0].strip() for l in open(os.path.join(R, 'tools', 'names', 'split.txt'))} - {''}
sizes = {}
for h in ('globals.h', 'objects.h'):
	for m in re.finditer(r'(?m)^#define (\w+) (?:GAME_VAR\(([^,]+), 0x[0-9a-f]+\)|\(\(([\w ]+?)\s*\*\)IMG\(0x[0-9a-f]+\)\)\s*/\*\s*[\w ]+?\[(\w+)\])',
	                     open(os.path.join(R, 'src', h), encoding='latin-1').read()):
		name = m.group(1)
		sizes[name] = 'scalar' if m.group(2) else 'array[%s]' % m.group(4)
HELPERS = r'set_box|rect_spec|options_panel|memcpy|memset|copy_words|store_words|apply_stores|STORE|RA\('
hits = []
for f in sorted(glob.glob(os.path.join(R, 'src', '**', '*.c'), recursive=True)):
	if os.sep + 'data' + os.sep in f:
		continue
	for i, line in enumerate(open(f, encoding='latin-1'), 1):
		code = re.sub(r'/\*.*?\*/', '', line)
		names = [n for n in re.findall(r'(?:ADDR\(|&)(g_\w+)', code) if n in split and sizes.get(n) == 'scalar']
		if not names:
			continue
		offset = re.search(r'ADDR\((g_\w+)\)\s*[+-]\s*(0x[0-9a-f]+|\d+)', code)
		helper = re.search(HELPERS + r'|PANEL_\w+\(|GAME_VAR\([^,]+,\s*\(?ADDR', code)
		if offset or helper:
			hits.append('%s:%d  [%s]  %s' % (os.path.relpath(f, R).replace(os.sep, '/'), i, ','.join(sorted(set(names))), line.strip()[:200]))
print('\n'.join(hits))
print('%d suspect lines' % len(hits))
