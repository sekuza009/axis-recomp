r"""whereis.py addr... : the function of AxisRC.exe (build/AxisRC.exe, linked at 0x10000 from build/obj_direct and
standalone objects) that holds each code address: its bytes around the address found in the objects' code (bytes a
relocation fills are skipped), the nearest function symbol before it. For the guard's and crash logs, as zig's
linker writes no map."""
import glob, os, struct, sys
import importlib.util
R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
spec = importlib.util.spec_from_file_location('ht', os.path.join(R, 'tools', 'hooktable.py'))
ht = importlib.util.module_from_spec(spec); spec.loader.exec_module(ht)
import pefile
pe = pefile.PE(os.path.join(R, 'build', 'AxisRC.exe'))
base = pe.OPTIONAL_HEADER.ImageBase


def sections(path):
	b = open(path, 'rb').read()
	nsec, = struct.unpack_from('<H', b, 2); ptr, nsym = struct.unpack_from('<II', b, 8); opt, = struct.unpack_from('<H', b, 16)
	strtab = ptr + nsym * 18
	out = []
	for i in range(nsec):
		s = b[20 + opt + 40 * i: 20 + opt + 40 * i + 40]
		size, raw_ptr, rel_ptr, nrel, ch = struct.unpack_from('<IIIH', s, 16)[0], struct.unpack_from('<I', s, 20)[0], struct.unpack_from('<I', s, 24)[0], struct.unpack_from('<H', s, 32)[0], struct.unpack_from('<I', s, 36)[0]
		if ch & 0x20 and raw_ptr:
			relocs = set()
			for r in range(nrel):
				off, = struct.unpack_from('<I', b, rel_ptr + r * 10)
				relocs |= set(range(off, off + 4))
			out.append((i + 1, b[raw_ptr:raw_ptr + size], relocs))
	syms = []
	k = 0
	while k < nsym:
		e = b[ptr + k * 18: ptr + k * 18 + 18]
		name = b[strtab + struct.unpack_from('<I', e, 4)[0]:].split(b'\0')[0] if e[:4] == b'\0\0\0\0' else e[:8].rstrip(b'\0')
		val, = struct.unpack_from('<I', e, 8); sec, = struct.unpack_from('<h', e, 12)
		if sec > 0 and e[16] in (2, 3) and not name.startswith(b'.'):
			syms.append((sec, val, name.decode('latin-1')))
		k += 1 + e[17]
	return out, syms


objs = glob.glob(os.path.join(R, 'build', 'obj_direct', '*.o')) + glob.glob(os.path.join(R, 'build', 'standalone_*.o'))
cache = {o: sections(o) for o in objs}
for arg in sys.argv[1:]:
	a = int(arg, 16)
	data = pe.get_data(a - base - 24, 48)
	best = None
	for o, (secs, syms) in cache.items():
		for sec, code, relocs in secs:
			if len(code) < 48:
				continue
			cands = set()
			for anchor in (16, 24, 32, 8, 0, 40):   # (6-byte runs of the window, one is free of relocations)
				pos = code.find(data[anchor:anchor + 6])
				while pos >= 0:
					if 0 <= pos - anchor <= len(code) - 48:
						cands.add(pos - anchor)
					pos = code.find(data[anchor:anchor + 6], pos + 1)
			for start in sorted(cands):
				ok = all(code[start + j] == data[j] or start + j in relocs for j in range(48))
				if ok:
					off = start + 24
					fn = max((s for s in syms if s[0] == sec and s[1] <= off), key=lambda s: s[1], default=None)
					best = (os.path.basename(o), fn[2] if fn else '?', off - (fn[1] if fn else 0))
					break
			if best: break
		if best: break
	print('%08x  %s' % (a, '%s  %s+0x%x' % best if best else 'not found'))
