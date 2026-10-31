r"""hooktable.py: the rebuilt functions the loaders switch in, (original address, C name), read from recomp.c as
tools/mkhooks.py reads them (HIT_TESTS, g_hooks3, install_hooks' own list); and each one's linker symbol.
As a script: hooktable.py <out.h> writes build/fn_syms.h for AXIS_DIRECT builds (see src/axis.h): per function
"extern void FN_name(void) __asm__("symbol");" and "enum { FNADDR_name = 0x... };"."""
import glob, os, re, struct, sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')


def hooks():
	t = open(os.path.join(ROOT, 'recomp.c'), encoding='utf-8-sig').read()
	out = []
	a = t.index('#define HIT_TESTS(X)'); b = t.index('\n', t.index('pilotSelect_hitTest', a))
	out += [(int(x, 16), n) for x, n in re.findall(r'X\((0x[0-9a-f]+), 0x[0-9a-f]+, 0x[0-9a-f]+, (\w+)\)', t[a:b])]
	a = t.index('g_hooks3[] = {'); b = t.index('\n};', a)
	out += [(int(x, 16), n) for x, fn, n in re.findall(r'\{ (0x[0-9a-f]+), \(void \*\)(\w+), "(\w+)" \}', t[a:b])]
	a = t.index('static void install_hooks(int state_ok)'); b = t.index('\n}\n', a)
	out += [(int(x, 16), n) for x, fn, n in re.findall(r'\thook\((0x[0-9a-f]+), \(void \*\)(\w+), "(\w+)"\);', t[a:b])]
	assert len({x for x, _ in out}) == len(out) and len({n for _, n in out}) == len(out), 'duplicate hook'
	return out


def coff_symbols(path):
	"""the external symbols an object defines"""
	b = open(path, 'rb').read()
	ptr, n = struct.unpack_from('<II', b, 8)
	strtab = ptr + n * 18
	out, i = [], 0
	while i < n:
		e = b[ptr + i * 18: ptr + i * 18 + 18]
		name = b[strtab + struct.unpack_from('<I', e, 4)[0]:].split(b'\0')[0] if e[:4] == b'\0\0\0\0' else e[:8].rstrip(b'\0')
		if struct.unpack_from('<h', e, 12)[0] > 0 and e[16] == 2:
			out.append(name.decode())
		i += 1 + e[17]
	return out


def symbols(objdir):
	"""C name -> linker symbol (_name, or _name@bytes for stdcall)"""
	sym = {}
	for o in glob.glob(os.path.join(objdir, '*.o')):
		for s in coff_symbols(o):
			m = re.match(r'_(\w+?)(@\d+)?$', s)
			if m:
				sym.setdefault(m.group(1), s)
	return sym


if __name__ == '__main__' and len(sys.argv) > 1 and sys.argv[1] != '-':
	sym = symbols(os.path.join(ROOT, 'build', 'obj'))
	lines = ['/* fn_syms.h (tools/hooktable.py): the rebuilt functions by linker symbol, for AXIS_DIRECT builds */']
	missing = []
	for a, n in sorted(hooks()):
		if n not in sym:
			missing.append(n); continue
		lines.append('extern void FN_%s(void) __asm__("%s"); enum { FNADDR_%s = 0x%x };' % (n, sym[n], n, a))
	if missing:
		sys.exit('no symbol for: ' + ', '.join(missing))
	open(sys.argv[1], 'w', newline='\n').write('\n'.join(lines) + '\n')
	print(len(lines) - 1, 'functions')
