r"""drop_local_macros.py [--dry]: a .c file's local #define of a call macro that src/*.h already defines the same way
(the same expansion up to the parameters' names) is dropped, with the file's #undef of it. The code is unchanged
(check: tools/objcmp.py)."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
DEF = re.compile(r'^#define (\w+)\(([^)]*)\)\s+(.*?)\s*(?:/\*.*\*/)?\s*$')

def canon(params, body):
	ps = [p.strip() for p in params.split(',') if p.strip()]
	for k, p in enumerate(ps):
		body = re.sub(r'\b%s\b' % re.escape(p), '@%d' % k, body)
	return len(ps), re.sub(r'\s+', ' ', body.strip())

header = {}
for f in glob.glob('src/*.h'):
	for line in open(f, encoding='latin-1'):
		m = DEF.match(line.rstrip('\r\n'))
		if m:
			header.setdefault(m.group(1), canon(m.group(2), m.group(3)))

total = 0
for f in sorted(glob.glob('src/**/*.c', recursive=True)):
	if os.sep + 'data' + os.sep in f:
		continue
	b = open(f, 'rb').read()
	crlf = b.count(b'\r\n')
	lines = b.decode('latin-1').replace('\r\n', '\n').split('\n')
	drop, names = set(), set()
	for i, line in enumerate(lines):
		m = DEF.match(line)
		if m and m.group(1) in header and canon(m.group(2), m.group(3)) == header[m.group(1)]:
			drop.add(i)
			names.add(m.group(1))
	if not drop:
		continue
	for d in sorted(drop):   # (the first #undef of the name after each dropped #define: its own)
		name = DEF.match(lines[d]).group(1)
		for i in range(d + 1, len(lines)):
			if re.match(r'^#define %s\b' % name, lines[i]):
				break
			if re.match(r'^#undef %s\s*$' % name, lines[i]):
				drop.add(i)
				break
	print('%-36s %d lines (%s)' % (f, len(drop), ', '.join(sorted(names))))
	total += len(drop)
	if not DRY:
		t = '\n'.join(l for i, l in enumerate(lines) if i not in drop)
		if crlf:
			t = t.replace('\n', '\r\n')
		open(f, 'wb').write(t.encode('latin-1'))
print(total, 'lines dropped')
