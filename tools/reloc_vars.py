r"""reloc_vars.py [--dry]: pointer casts of integers that may hold an original address of the game's image - a
variable the file declares as u32 / int / DWORD..., or a field / element named for an address (at, addr, site,
window ...) - relocate them: (u32 *)addr -> (u32 *)RELOC(addr) (src/axis.h; in the harness RELOC(a) is a, so its
objects do not change). RELOC leaves any other value (AxisRC.exe's own memory, the heap, the relocated image) as it
is, so a cast of a value that is no image address is unaffected."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
INT = r'(?:u32|i32|int|unsigned(?:\s+int)?|DWORD|UINT|long|unsigned\s+long|uintptr_t)'
FIELDS = r'(?:at|addr|address|site|where|window|base|slot|table|text|name|format|title|line|to|from|src|dst|rect|record|buffer|edited\[\d+\]|modes|kinds|row5)'
files = [a for a in sys.argv[1:] if not a.startswith('--')] or [
	f for f in glob.glob('src/**/*.[ch]', recursive=True) if os.path.basename(os.path.dirname(f)) != 'data' and not f.endswith('axis.h')]
total = 0
for f in sorted(files):
	t = open(f, 'rb').read().decode('latin-1')
	mask = re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: '\0' * len(m.group(0)), t, flags=re.S)
	ints = set()
	for m in re.finditer(r'\b%s\s+(?=\w)' % INT, mask):   # every name of a declaration: u32 s = 1, d = 2;
		decl = re.match(r'[^;{}]*', mask[m.end():]).group(0)
		depth, part, parts = 0, '', []
		for ch in decl:
			if ch in '([': depth += 1
			elif ch in ')]':
				depth -= 1
				if depth < 0: break
			if ch == ',' and depth == 0:
				parts.append(part); part = ''; continue
			part += ch
		parts.append(part)
		for p in parts:
			n = re.match(r'\s*(\w+)\s*(?:=|$|\[)', p)
			if n:
				ints.add(n.group(1))
	ints |= set(re.findall(r'\b%s\s+(\w+)\s*[,)]' % INT, mask))   # (parameters)
	ints -= {'int', 'u32', 'void', 'const', 'unsigned', 'double', 'float', 'char', 'short', 'long', 'signed', 'u8', 'u16'}
	# arrays of integers and pointers to them: their elements may be addresses (tables of strings, of globals)
	tables = set(re.findall(r'\b%s\s*\*\s*(?:const\s+)?(\w+)' % INT, mask)) | set(re.findall(r'\b%s\s+(\w+)\s*\[' % INT, mask))
	tables |= set(re.findall(r'\b%s\s+(?:\w+\s*\[[^\]]*\](?:\[[^\]]*\])*\s*(?:=\s*\{[^;]*?\})?\s*,\s*)+(\w+)\s*\[' % INT, mask))
	operand = r'(?:(?:%s)\b(?!\s*(?:\(|->|\.))|[\w\]\)]+(?:\.|->)%s\b|\w+\[[^\]]+\](?:\[\d+\])*(?:\.%s\b)?)' % (
		'|'.join(sorted(map(re.escape, ints), key=len, reverse=True)) or 'NONAME', FIELDS, FIELDS)
	pat = re.compile(r'(\((?:const\s+)?(?:volatile\s+)?[\w ]+\*+\s*\))\s*(\(?)(%s)' % operand)
	out, k, n = [], 0, 0
	for m in pat.finditer(mask):
		if m.group(2):   # (T *)(x + ...): relocate x
			pass
		name = m.group(3)
		if name.startswith('RELOC') or name.startswith('IMG'):
			continue
		# an element / field: only for arrays and fields of integers by name, and tables of addresses
		if '[' in name and name.split('[')[0] not in tables and not re.search(r'\b(at|addr|address|site|table|tables|cleared|panels|copy|rect|title|zero|fields?|strings|clocks|steps|pages|page|close|open|sections|setters|actions|control|levels|kept|speeds|bonuses|shown|ints|values?|value)\b', name):
			continue
		start, end = m.start(3), m.end(3)
		out.append(t[k:start] + 'RELOC(' + t[start:end] + ')')
		k = end; n += 1
	if n:
		total += n
		print('%-40s %d' % (f, n))
		if '--dry' not in sys.argv:
			open(f, 'wb').write((''.join(out) + t[k:]).encode('latin-1'))
print(total, 'casts')
