r"""reloc_macros.py [--dry]: a file's own macros that make a pointer of a parameter - #define K(address)
((const float *)(address)) - relocate it: ((const float *)RELOC(address)), so K(0x4a973c) reaches the image where
AxisRC.exe keeps it (src/axis.h; in the harness RELOC(a) is a, so its objects do not change). RELOC leaves any
other value as it is, so a macro used with a pointer of AxisRC.exe's own is unaffected."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DEF = re.compile(r'^([ \t]*#define[ \t]+\w+\(([^)]*)\)[ \t]+)(.*)$')
total = 0
for f in sorted(glob.glob('src/**/*.[ch]', recursive=True)):
	if os.path.basename(os.path.dirname(f)) == 'data' or f.endswith(('axis.h', 'globals.h')):
		continue
	lines = open(f, 'rb').read().decode('latin-1').split('\n')
	n = 0
	for i, line in enumerate(lines):
		m = DEF.match(line)
		if not m:
			continue
		body = m.group(3)
		for p in [x.strip() for x in m.group(2).split(',') if x.strip() and x.strip() != '...']:
			# (T *)(p) or (T *)p, T a pointer type: the parameter as an address
			new = re.sub(r'(\((?:const\s+)?[\w ]+\*+\s*\))\s*\(\s*%s\s*\)' % re.escape(p), r'\1RELOC(%s)' % p, body)
			new = re.sub(r'(\((?:const\s+)?[\w ]+\*+\s*\))\s*%s\b(?!\s*[\[+\-*/.]|\s*->)' % re.escape(p), r'\1RELOC(%s)' % p, new)
			if new != body:
				body = new; n += 1
		if n and body != m.group(3):
			lines[i] = m.group(1) + body
	if n:
		total += n
		print('%-40s %d' % (f, n))
		if '--dry' not in sys.argv:
			open(f, 'wb').write('\n'.join(lines).encode('latin-1'))
print(total, 'macros')
