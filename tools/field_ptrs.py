r"""field_ptrs.py <file.c> <var> <Struct> <PTR> [--in=f,g] [--dry]: a member's address as a whole operand written
by its field:
    VECTOR(s + 0x9ee080, 0xc, 0x126)   -> VECTOR((u8 *)PTR->skySphere, 0xc, 0x126)
    Model_ctor(s + 0xdc0a78)           -> Model_ctor((u8 *)&PTR->layerModel)
Only where src/scene.fields has a field of Struct starting at the offset and the sum is a whole argument or operand
(followed by ',' or ')'; not by more arithmetic). var must be a u8 * (the cast keeps the expression's type). --in limits
it to the named functions' bodies. The code is the same (objcmp)."""
import os, re, sys
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
args = [a for a in sys.argv[1:] if not a.startswith('--')]
path, var, TYPE, PTR = args
DRY = '--dry' in sys.argv
IN = None
for a in sys.argv:
	if a.startswith('--in='):
		IN = a[5:].split(',')
fields, cur = {}, None
for l in open('src/scene.fields', encoding='latin-1'):
	l = l.split('#')[0].strip()
	if not l:
		continue
	if l.startswith('struct'):
		cur = l.split()[1]
		continue
	if cur != TYPE:
		continue
	off, size, decl = l.split(None, 2)
	m = re.match(r'(.*?)(\w+)\s*((?:\[[^\]]*\])*)$', decl)
	fields[int(off, 16)] = (m.group(2), bool(m.group(3)))
t = open(path, encoding='latin-1', newline='').read()
spans = [(0, len(t))]
if IN:
	spans = []
	for f in IN:
		m = re.search(r'\(%s\)\s*\(' % re.escape(f), t) or re.search(r'\b%s\s*\(' % re.escape(f), t)
		if not m:
			print('no function', f)
			continue
		b = t.index('\n{', m.end())
		e = t.index('\n}', b)
		spans.append((b, e))
n = 0
def rep(m):
	global n
	o = int(m.group(1), 16)
	if o not in fields:
		return m.group(0)
	name, arr = fields[o]
	n += 1
	return '(u8 *)%s%s->%s%s' % ('' if arr else '&', PTR, name, m.group(2))
out, last = [], 0
for b, e in sorted(spans):
	out.append(t[last:b])
	out.append(re.sub(r'(?<![\w>.])%s \+ (0x[0-9a-f]+)\b(\s*[,)])' % re.escape(var), rep, t[b:e]))
	last = e
out.append(t[last:])
if not DRY:
	open(path, 'w', encoding='latin-1', newline='').write(''.join(out))
print('%s: %d member addresses' % (path, n))
