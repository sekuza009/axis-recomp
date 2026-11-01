r"""img_strings.py [--dry | --check]: the image's texts written with their text.
  IMG(0x4b4418) at a string of .rdata / .data       -> STR(0x4b4418, "Data/Component.dat")
  IMG(0x74de24 + n * 0x80 [+ k]) (the message table) -> MSG(n, "DETECTION RANGE") [+ k]
STR / MSG are the same address as IMG (src/axis.h); the text is for the reader (shortened past 40 characters: "...").
--check: every STR / MSG in src/ against the data (the installed exe; msgeng.dat for the messages) - a text that
does not match is reported (exit 1)."""
import glob, os, re, struct, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
b = open('installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; nsec = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
secs = []
for i in range(nsec):
	nm, vs, va, rs, rp = struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i)
	secs.append((0x400000 + va, min(vs, rs), rp))
def raw(a, n):
	for base, size, rp in secs:
		if base <= a and a + n <= base + size:
			return b[rp + a - base:rp + a - base + n]
	return None
msgs = [l.rstrip('\r') for l in open('../initdata/msgeng.dat', 'rb').read().decode('latin-1').split('\n')]
msgs = [l[:0x7e] for l in msgs if l and not l.startswith('//')]
MSG0, LINE = 0x74de24, 0x80


def string_at(a):
	t = raw(a, 256)
	if not t or not t[0] or raw(a - 1, 1) not in (b'\0', None):
		return None
	k = t.find(b'\0')
	if k <= 0 or not all(32 <= c < 127 or c >= 0xa1 or c in (9, 10, 13) for c in t[:k]):
		return None
	return t[:k].decode('latin-1')


def lit(s):
	short = s if len(s) <= 40 else s[:37] + '...'
	out = ''
	for ch in short:
		c = ord(ch)
		if ch == '\\': out += '\\\\'
		elif ch == '"': out += '\\"'
		elif ch == '\n': out += '\\n'
		elif ch == '\r': out += '\\r'
		elif ch == '\t': out += '\\t'
		elif 32 <= c < 127: out += ch
		else: out += '\\%03o' % c
	return '"%s"' % out


def unlit(s):
	return re.sub(r'\\(\d{3}|.)', lambda m: chr(int(m.group(1), 8)) if m.group(1).isdigit() else
	              {'n': '\n', 'r': '\r', 't': '\t'}.get(m.group(1), m.group(1)), s[1:-1])


files = [f for f in glob.glob('src/**/*.[ch]', recursive=True)
         if os.path.basename(os.path.dirname(f)) != 'data' and not f.endswith(('axis.h', 'globals.h'))]
if '--check' in sys.argv:
	bad = 0
	for f in files:
		t = open(f, encoding='latin-1').read()
		for a, s in re.findall(r'\bSTR\((0x[0-9a-f]+), ("(?:\\.|[^"\\])*")\)', t):
			want, have = unlit(s), string_at(int(a, 16)) or ''
			if not (have == want or (want.endswith('...') and have.startswith(want[:-3]))):
				print('%s: STR(%s) is %r, the data %r' % (f, a, want, have)); bad += 1
		for n, s in re.findall(r'\bMSG\((\d+), ("(?:\\.|[^"\\])*")\)', t):
			want, have = unlit(s), msgs[int(n)] if int(n) < len(msgs) else ''
			if not (have == want or (want.endswith('...') and have.startswith(want[:-3]))):
				print('%s: MSG(%s) is %r, msgeng.dat %r' % (f, n, want, have)); bad += 1
	print('%d texts differ' % bad)
	sys.exit(1 if bad else 0)
total = {'STR': 0, 'MSG': 0}
for f in sorted(files):
	t = open(f, 'rb').read().decode('latin-1')
	def sub(m):
		a = int(m.group(1), 16)
		if MSG0 <= a < MSG0 + LINE * len(msgs):
			n, k = divmod(a - MSG0, LINE)
			total['MSG'] += 1
			return 'MSG(%d, %s)' % (n, lit(msgs[n])) + (' + %d' % k if k else '')
		s = string_at(a)
		if s is None:
			return m.group(0)
		total['STR'] += 1
		return 'STR(0x%x, %s)' % (a, lit(s))
	def raw_msg(m):   # (a plain message-table address: in a table, an argument - not an offset)
		a = int(m.group(2), 16)
		if not MSG0 <= a < MSG0 + LINE * len(msgs) or re.search(r'[-+]\s*$', m.group(1)) or \
		   re.search(r'\b[A-Z][A-Z_0-9]*\(\s*[^(),]*,\s*(?:[^(),]*,\s*)?$', m.group(1)) or re.search(r'\bcase\s*$', m.group(1)):
			return m.group(0)
		n, k = divmod(a - MSG0, LINE)
		total['MSG'] += 1
		return m.group(1) + 'MSG(%d, %s)' % (n, lit(msgs[n])) + (' + %d' % k if k else '')
	out = []
	for line in t.split('\n'):
		new = re.sub(r'\bIMG\((0x[0-9a-f]+)\)', sub, line)
		if '--raw' in sys.argv and not re.match(r'\s*(#define|/\*|\*)', new):
			new = re.sub(r'(^|[^\w.])(0x[0-9a-f]{6})\b(?!\s*[-+*])', lambda m: raw_msg(type('M', (), {'group': lambda s, i: (m.group(0), m.group(1), m.group(2))[i]})()), new)
		if new != line and re.search(r'/\*\s*"[^*]*"\s*\*/\s*$', new):   # (a comment that only quoted the text)
			new = re.sub(r'\s*/\*\s*"[^*]*"\s*\*/\s*$', '', new)
		out.append(new)
	if '--dry' not in sys.argv:
		open(f, 'wb').write('\n'.join(out).encode('latin-1'))
print(total)
