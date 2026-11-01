r"""img_census.py [kind]: the IMG(0x...) uses left in src/ by what they point at - the message table (0x80-byte lines
from 0x74de24, read from msgeng.dat), a string of .rdata / .data, inside a named global, other .rdata / .data, the
code (0x401000 .. 0x4a9000), the rest - with examples of a kind"""
import collections, glob, os, re, struct, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
names = sorted((int(a, 16), n, t.strip()) for n, t, a in re.findall(r'#define (\w+) GAME_VAR\(([\w \*]+), (0x[0-9a-f]+)\)', open('src/globals.h').read()))
starts = {a for a, _, _ in names}
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
def is_string(a):
	t = raw(a, 64)
	if not t or not t[0] or (raw(a - 1, 1) not in (b'\0', None)):
		return False
	k = t.find(b'\0')
	return k > 0 and all(32 <= c < 127 or c >= 0xa1 or c in (9, 10, 13) for c in t[:k])
c = collections.Counter(); ex = collections.defaultdict(list)
for f in glob.glob('src/**/*.[ch]', recursive=True):
	if os.path.basename(os.path.dirname(f)) == 'data':
		continue
	for line in open(f, encoding='latin-1'):
		for m in re.finditer(r'\bIMG\((0x[0-9a-f]+)\)', line):
			a = int(m.group(1), 16)
			if 0x74de24 <= a < 0x74de24 + 0x80 * 2000 and (a - 0x74de24) % 0x80 == 0: k = 'message table line'
			elif 0x74de24 <= a < 0x74de24 + 0x80 * 2000: k = 'message table, inside a line'
			elif a < 0x4a9000: k = 'code'
			elif is_string(a): k = 'string'
			else:
				inside = [n for s, n, t in names if s < a < s + 4]
				k = 'inside a named global' if inside else ('.rdata other' if a < 0x4ad000 else '.data other')
			c[k] += 1; ex[k].append(os.path.basename(f) + ': ' + line.strip()[:130])
print(dict(c.most_common()))
for k in sys.argv[1:]:
	print('==', k); print('\n'.join(ex[k][:15]))
