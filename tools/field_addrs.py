r"""field_addrs.py <file.c> <var> <Struct> <PTR> [--dry]: a float array field's address written as the field:
    (float *)(a + 0x154)  -> PTR->pos          (const float * too)
    memcpy(a + 0x4e0, a + 0x154, 12)  -> memcpy(PTR->deathPos, PTR->pos, 12)   (memcpy / memcmp arguments only)
Only offsets where src/scene.fields has a float array of the struct start. The code is the same (objcmp)."""
import re, sys, os
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
args = [a for a in sys.argv[1:] if not a.startswith('--')]
path, var, TYPE, PTR = args
arrs, cur = {}, None
for l in open('src/scene.fields', encoding='latin-1'):
	l = l.split('#')[0].strip()
	if not l:
		continue
	if l.startswith('struct'):
		cur = l.split()[1]; continue
	off, size, decl = l.split(None, 2)
	m = re.match(r'float\s+(\w+)\s*\[\w+\]$', decl)
	if m and cur == TYPE:
		arrs[int(off, 16)] = m.group(1)
t = open(path, encoding='latin-1', newline='').read()
n = 0
def cast(m):
	global n
	f = arrs.get(int(m.group(2), 16))
	if not f:
		return m.group(0)
	n += 1
	return '%s->%s' % (PTR, f)
t2 = re.sub(r'\((const )?float \*\)\(%s \+ (0x[0-9a-f]+)\)' % var, cast, t)
def mem(m):
	global n
	argz = m.group(2)
	def one(a):
		global n
		am = re.fullmatch(r'(\s*)%s \+ (0x[0-9a-f]+)(\s*)' % var, a)
		if am and int(am.group(2), 16) in arrs:
			n += 1
			return '%s%s->%s%s' % (am.group(1), PTR, arrs[int(am.group(2), 16)], am.group(3))
		return a
	parts = argz.split(',')
	if len(parts) != 3:
		return m.group(0)
	return m.group(1) + ','.join(one(p) for p in parts[:2]) + ',' + parts[2] + ')'
t2 = re.sub(r'\b(mem(?:cpy|cmp)\()([^()]*(?:\([^()]*\)[^()]*)*)\)', mem, t2)
if t2 != t and '--dry' not in sys.argv:
	open(path, 'w', encoding='latin-1', newline='').write(t2)
print('%s: %d field addresses' % (path, n))
