r"""str_check.py: every STR(0xaddr, "text") and MSG-free string in src checked against the original's bytes at that
address (installed.exe): the text (a C literal, unescaped; one ending in "..." compared up to the dots) must be what
the game has there. The harness builds by address, so a changed literal does not show in tools/objcmp.py - this
does (a rename that touched a string, say)."""
import ast, glob, os, re, struct, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
b = open('installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]
nsec = struct.unpack_from('<H', b, pe + 6)[0]
opt = struct.unpack_from('<H', b, pe + 20)[0]
secs = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * k) for k in range(nsec)]


def at(a, n):
	for nm, vs, va, rs, rp in secs:
		if 0x400000 + va <= a < 0x400000 + va + rs:
			o = rp + a - 0x400000 - va
			return b[o:o + n]
	return None


bad = n = 0
for f in glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True):
	if os.sep + 'data' + os.sep in f:
		continue
	t = open(f, encoding='latin-1').read()
	for m in re.finditer(r'\bSTR\((0x[0-9a-f]+), ("(?:[^"\\]|\\.)*")\)', t):
		a = int(m.group(1), 16)
		try:
			s = ast.literal_eval(m.group(2).replace('\\x', '\\x'))
		except Exception:
			continue
		s = s.encode('latin-1', 'replace')
		dots = s.endswith(b'...')
		want = s[:-3] if dots else s + b'\0'
		have = at(a, len(want))
		n += 1
		if have is None or have != want:
			bad += 1
			line = t.count('\n', 0, m.start()) + 1
			print('%s:%d: STR(%s) is %r in the source, %r in the game' % (f.replace(os.sep, '/'), line, m.group(1), want, have))
print(n, 'strings checked,', bad, 'differ')
sys.exit(1 if bad else 0)
