r"""float_stores.py <file.c>... [--dry]: a float stored as its bit pattern in a statement of its own,
    BITS(GS->emblemTime) = 0x43960000;   /* 300 */
becomes the float:
    GS->emblemTime = 300.0f;
when the bits are a number with a short exact decimal form (the literal rounds back to the same bits) and the
target is a float lvalue (a field declared float in src/scene.fields, or anything the compiler then accepts: a
build error means it was not). Chained stores (a = b = bits) are left: they would convert the value, not its bits.
The comment that only repeated the number goes. Check: tools/objcmp.py."""
import re, sys, struct, os

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
files = [f for f in sys.argv[1:] if not f.startswith('--')]


def literal(bits):
	v = struct.unpack('<f', struct.pack('<I', bits))[0]
	if v != v or abs(v) == float('inf') or (v == 0 and bits != 0):
		return None
	for digits in range(1, 8):
		s = '%.*g' % (digits, v)
		try:
			back = struct.unpack('<I', struct.pack('<f', float(s)))[0]
		except OverflowError:
			continue
		if back == bits:
			if 'e' in s:
				return None
			if '.' not in s:
				s += '.0'
			return s + 'f'
	return None


total = 0
for path in files:
	raw = open(path, encoding='latin-1', newline='').read()
	crlf = '\r\n' in raw
	t = raw.replace('\r\n', '\n')
	n = [0]

	def rep(m):
		lit = literal(int(m.group(3), 16))
		if not lit:
			return m.group(0)
		n[0] += 1
		comment = m.group(4) or ''
		if re.fullmatch(r'[ \t]*/\*\s*-?[\d.]+\s*\*/', comment):   # (only the number again: dropped)
			comment = ''
		return '%s%s = %s;%s' % (m.group(1), m.group(2), lit, comment)
	# (an int field holding a float's bits would take the number converted: objcmp shows it - check every change)
	t2 = re.sub(r'(?m)^(\s*)BITS\(([^()=;]*(?:\([^()]*\)[^()=;]*)*)\) = (0x[0-9a-f]{8});([ \t]*/\*[^*]*\*/)?', rep, t)
	if n[0]:
		print('%-36s %d' % (path, n[0]))
		total += n[0]
		if not DRY:
			open(path, 'w', encoding='latin-1', newline='').write(t2.replace('\n', '\r\n') if crlf else t2)
print(total, 'float stores written as floats')
