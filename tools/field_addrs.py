r"""field_addrs.py <file.c> <var> <Struct> <PTR> [--dry]: a float array field's address written as the field:
    (float *)(a + 0x154)  -> PTR->pos          (const float * too; a scalar float field: &PTR->f)
    memcpy(a + 0x4e0, a + 0x154, 12)  -> memcpy(PTR->deathPos, PTR->pos, 12)   (memcpy / memcmp arguments only)
Only offsets where src/scene.fields has a float array of the struct start. The code is the same (objcmp)."""
import re, sys, os
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
args = [a for a in sys.argv[1:] if not a.startswith('--')]
path, var, TYPE, PTR = args
arrs, scal, strs, cur = {}, {}, {}, None
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
	m = re.match(r'float\s+(\w+)$', decl)
	if m and cur == TYPE:
		scal[int(off, 16)] = m.group(1)
	m = re.match(r'char\s+(\w+)\s*\[\w+\]$', decl)
	if m and cur == TYPE:
		strs[int(off, 16)] = m.group(1)
t = open(path, encoding='latin-1', newline='').read()
n = 0
# only where PTR is defined (a "#define PTR ((T *)var)" up to its #undef or the end) when the file defines it;
# a PTR that is an expression ((Player *)ac) works everywhere
SPANS = None
if re.match(r'^\w+$', PTR) and PTR != var:   # (PTR the variable itself, already typed: everywhere)
	SPANS = []
	for d in re.finditer(r'(?m)^#define %s \(\(\w+ \*\)\(?%s\)?\)' % (PTR, var), t):
		u = re.compile(r'(?m)^#(?:undef|define) %s\b' % PTR).search(t, d.end())
		SPANS.append((d.end(), u.start() if u else len(t)))
inside = lambda p: SPANS is None or any(a <= p < b for a, b in SPANS)
def cast(m):
	global n
	if not inside(m.start()):
		return m.group(0)
	o = int(m.group(2), 16)
	if o in arrs:
		n += 1
		return '%s->%s' % (PTR, arrs[o])
	if o in scal:   # a scalar float field: its address
		n += 1
		return '&%s->%s' % (PTR, scal[o])
	return m.group(0)
t2 = re.sub(r'\((const )?float \*\)\(%s \+ (0x[0-9a-f]+)\)' % var, cast, t)
def mem(m):
	global n
	if not inside(m.start()):
		return m.group(0)
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


# a char array field's address: (char *)var + C, (const char *)var + C, (char *)(var + C) -> PTR->name (the same
# pointer; the cast's const kept where it was asked for)
def chars(m):
	global n
	if not inside(m.start()):
		return m.group(0)
	o = int(m.group(3) or m.group(4), 16)
	if o not in strs:
		return m.group(0)
	n += 1
	return '%s%s->%s' % ('(const char *)' if m.group(1) else '', PTR, strs[o])


t2 = re.sub(r'\((const )?(char) \*\)(?:%s \+ (0x[0-9a-f]+)\b(?!\s*[\[*/])|\(%s \+ (0x[0-9a-f]+)\))' % (var, var), chars, t2)
if t2 != t and '--dry' not in sys.argv:
	open(path, 'w', encoding='latin-1', newline='').write(t2)
print('%s: %d field addresses' % (path, n))
