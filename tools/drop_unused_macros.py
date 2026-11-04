r"""drop_unused_macros.py <file.c>... [--dry]: a .c file's local #define that nothing uses any more (no use of its name
between it and its #undef, or the file's end) is dropped with its #undef. Leftovers of the field conversions:
FIELD / AT / A / P accessors whose last use became a struct field. The code is unchanged (check: tools/objcmp.py)."""
import re, sys, os

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
files = [f for f in sys.argv[1:] if not f.startswith('--')]

total = 0
for path in files:
	raw = open(path, encoding='latin-1', newline='').read()
	crlf = '\r\n' in raw
	lines = raw.replace('\r\n', '\n').split('\n')
	drop, names = set(), []
	for i, line in enumerate(lines):
		m = re.match(r'^\s*#define (\w+)\b', line)
		if not m:
			continue
		name = m.group(1)
		k = i
		while lines[k].rstrip().endswith('\\'):   # (a macro continued over lines)
			k += 1
		end, undef = len(lines), None
		for j in range(k + 1, len(lines)):
			if re.match(r'^\s*#undef %s\s*$' % name, lines[j]):
				end, undef = j, j
				break
			if re.match(r'^\s*#define %s\b' % name, lines[j]):
				end = -1   # (defined again before any #undef: an #ifdef / #else pair, left alone)
				break
		if end < 0:
			continue
		text ='\n'.join(re.sub(r'/\*.*?\*/|//.*', '', l) for l in lines[k + 1:end])
		if re.search(r'\b%s\b' % name, text):
			continue
		drop.update(range(i, k + 1))
		if undef is not None:
			drop.add(undef)
		names.append(name)
	if not drop:
		continue
	print('%-36s %s' % (path, ', '.join(names)))
	total += len(names)
	if not DRY:
		t = '\n'.join(l for i, l in enumerate(lines) if i not in drop)
		open(path, 'w', encoding='latin-1', newline='').write(t.replace('\n', '\r\n') if crlf else t)
print(total, 'unused macros dropped')
