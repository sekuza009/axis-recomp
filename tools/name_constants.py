r"""name_constants.py [--dry]: the game's float constants read through their address, K(0x4a9424) / F(0x4a9424)
(a file's  #define K(a) ((const float *)RELOC(a))), named by value in src/globals.h like the others
(k_1f, k_0_5f, k_m2f; k_1500f_4a9700 when the value's name is taken) and written as their address: &k_1f.
The values come from installed.exe's .rdata. The code is the same (check: tools/objcmp.py)."""
import glob, os, re, struct, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
DRY = '--dry' in sys.argv
b = open('installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; nsec = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
secs = []
for i in range(nsec):
	nm, vs, va, rs, rp = struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i)
	secs.append((0x400000 + va, rs, rp))


def value(a):
	for base, rs, rp in secs:
		if base <= a and a + 4 <= base + rs:
			return struct.unpack_from('<f', b, rp + a - base)[0]
	return None


def value_name(v):
	if v != v or v in (float('inf'), float('-inf')):
		return None
	s = ('%.7g' % v)
	if 'e' in s:
		return None
	s = s.replace('-', 'm').replace('.', '_')
	return 'k_%sf' % s


g = open('src/globals.h', encoding='latin-1').read()
names = {int(m.group(2), 16): '&' + m.group(1) for m in re.finditer(r'^#define (k_\w+) GAME_VAR\(float, (0x[0-9a-f]+)\)', g, re.M)}
o = open('src/objects.h', encoding='latin-1').read()
for m in re.finditer(r'^#define (\w+) \(\((?:const )?float \*\)IMG\((0x[0-9a-f]+)\)\)', o, re.M):   # (a float object: already a pointer)
	names.setdefault(int(m.group(2), 16), m.group(1))
taken = set(re.findall(r'^#define (\w+)\b', g + o, re.M))
MAC = re.compile(r'\b([KF])\((0x4a[9a-c][0-9a-f]{3})\)')

files = [f for f in glob.glob('src/**/*.c', recursive=True) if os.sep + 'data' + os.sep not in f]
wanted = set()
for f in files:
	t = open(f, encoding='latin-1').read()
	for mac in set(m.group(1) for m in MAC.finditer(t)):
		if re.search(r'^#define %s\((\w+)\) \(\(const float \*\)RELOC\(\1\)\)' % mac, t, re.M):
			wanted |= {int(m.group(2), 16) for m in MAC.finditer(t) if m.group(1) == mac}
new_defs = []
for a in sorted(wanted):
	if a in names:
		continue
	v = value(a)
	n = value_name(v) if v is not None else None
	if not n:
		continue
	if n in taken:
		n = '%s_%x' % (n, a)
	names[a] = '&' + n
	taken.add(n)
	new_defs.append('#define %s GAME_VAR(float, %s)   /* %.9g */' % (n, hex(a), v))
print(len(new_defs), 'constants named')
if new_defs and not DRY:
	with open('src/globals.h', 'a', encoding='latin-1', newline='') as out:
		out.write('/* float constants of .rdata named by value (tools/name_constants.py) */\n' + '\n'.join(new_defs) + '\n')

total = 0
for f in files:
	raw = open(f, encoding='latin-1', newline='').read()
	t = raw
	n = 0
	for mac in ('K', 'F'):
		if not re.search(r'^#define %s\((\w+)\) \(\(const float \*\)RELOC\(\1\)\)' % mac, t, re.M):
			continue
		def rep(m):
			nonlocal_n[0] += 1
			return names[int(m.group(2), 16)]
		nonlocal_n = [0]
		t = re.sub(r'\b(%s)\((0x4a[9a-c][0-9a-f]{3})\)' % mac, lambda m: rep(m) if int(m.group(2), 16) in names else m.group(0), t)
		n += nonlocal_n[0]
	if n:
		print('%-36s %d' % (f, n))
		total += n
		if not DRY:
			open(f, 'w', encoding='latin-1', newline='').write(t)
print(total, 'constant uses by name')
