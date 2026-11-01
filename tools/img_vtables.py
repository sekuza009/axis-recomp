r"""img_vtables.py [--dry]: a vtable's address (an IMG(0x...) at a word of .rdata whose value is a rebuilt function's
entry, named <Class>_deletingDtor / _dtor / ...) written VT(Class, 0x...) - the class named after that first entry
(src/axis.h: VT is IMG). For self[0] = VT(Scene, 0x4aa258) and the like."""
import glob, os, re, struct, sys, importlib.util

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
spec = importlib.util.spec_from_file_location('ht', 'tools/hooktable.py'); ht = importlib.util.module_from_spec(spec); spec.loader.exec_module(ht)
hooked = {a: n for a, n in ht.hooks()}
b = open('installed.exe', 'rb').read()
def word(a):
	return struct.unpack_from('<I', b, 0x1000 + (a - 0x4a9000) + (0x4a9000 - 0x4a9000))[0]
# .rdata's file offset
pe = struct.unpack_from('<I', b, 0x3c)[0]; nsec = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
for i in range(nsec):
	nm, vs, va, rs, rp = struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i)
	if nm.rstrip(b'\0') == b'.rdata':
		rd_va, rd_rp, rd_n = 0x400000 + va, rp, min(vs, rs)
def rdata_word(a):
	return struct.unpack_from('<I', b, rd_rp + a - rd_va)[0] if rd_va <= a < rd_va + rd_n - 3 else None
total = 0
for f in sorted(glob.glob('src/**/*.[ch]', recursive=True)):
	if os.path.basename(os.path.dirname(f)) == 'data':
		continue
	t = open(f, 'rb').read().decode('latin-1')
	n = [0]
	def sub(m):
		a = int(m.group(1), 16)
		w = rdata_word(a)
		fn = hooked.get(w) if w else None
		if not fn or not re.search(r'_(deletingDtor|dtor|ctor|clear|release|reset)$', fn):
			return m.group(0)
		n[0] += 1
		return 'VT(%s, 0x%x)' % (fn.split('_')[0], a)
	u = re.sub(r'\bIMG\((0x4a[9a][0-9a-f]{3}|0x4ab[0-9a-f]{3}|0x4ac[0-9a-f]{3})\)', sub, t)
	if n[0]:
		total += n[0]; print('%-40s %d' % (f, n[0]))
		if '--dry' not in sys.argv:
			open(f, 'wb').write(u.encode('latin-1'))
print(total, 'vtables named')
