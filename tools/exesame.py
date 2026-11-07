r"""exesame.py a.exe b.exe: are two AxisRC.exe builds the same program, when a rename reordered the compiler's pointer
slots (.refptr, sorted by symbol name)? objcmp.py then reports the objects of the renamed globals' users as different,
though only which slot an instruction loads changed. Here: every differing .text word must load a slot holding the
same address in both exes, and the differing .rdata range must be the same words reordered; the other sections equal."""
import struct, sys


def load(p):
	d = open(p, 'rb').read()
	pe = struct.unpack_from('<I', d, 0x3c)[0]
	n, opt = struct.unpack_from('<H', d, pe + 6)[0], struct.unpack_from('<H', d, pe + 20)[0]
	base = struct.unpack_from('<I', d, pe + 52)[0]
	o, secs = pe + 24 + opt, {}
	for i in range(n):
		name = d[o:o + 8].rstrip(b'\0').decode()
		vs, va, rs, rp = struct.unpack_from('<IIII', d, o + 8)
		secs[name] = (va + base, d[rp:rp + rs])
		o += 40
	return secs


def word_at(secs, addr):
	for va, data in secs.values():
		if va <= addr <= va + len(data) - 4:
			return struct.unpack_from('<I', data, addr - va)[0]


a, b = load(sys.argv[1]), load(sys.argv[2])
ok = True
for name in sorted(set(a) | set(b)):
	if name in ('.buildid', '.text', '.rdata'):
		continue
	if a.get(name) != b.get(name):
		print('section %s differs' % name); ok = False
x, y = a['.text'][1], b['.text'][1]
if len(x) != len(y):
	print('.text sizes differ'); ok = False
else:
	diff, explained, bad = [i for i in range(len(x)) if x[i] != y[i]], set(), 0
	for i in diff:
		if i in explained:
			continue
		for s in range(i - 3, i + 1):
			u, v = struct.unpack_from('<I', x, s)[0], struct.unpack_from('<I', y, s)[0]
			wu, wv = word_at(a, u), word_at(b, v)
			if wu is not None and wu == wv:
				explained.update(range(s, s + 4)); break
		else:
			bad += 1
			if bad <= 10:
				print('.text differs at 0x%x' % (a['.text'][0] + i))
	print('.text: %d bytes differ, %d of them pointer-slot operands with the same target' % (len(diff), len(explained & set(diff))))
	ok &= bad == 0
x, y = a['.rdata'][1], b['.rdata'][1]
diff = [i for i in range(len(x)) if x[i] != y[i]]
if diff:
	lo, hi = diff[0] & ~3, (diff[-1] | 3) + 1
	same = sorted(struct.unpack_from('<%dI' % ((hi - lo) // 4), x, lo)) == sorted(struct.unpack_from('<%dI' % ((hi - lo) // 4), y, lo))
	print('.rdata: 0x%x .. 0x%x differs, %s' % (a['.rdata'][0] + lo, a['.rdata'][0] + hi, 'the same words reordered' if same else 'NOT a reordering'))
	ok &= same
print('the same program' if ok else 'DIFFERENT')
