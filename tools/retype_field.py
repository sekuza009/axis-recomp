r"""retype_field.py <Struct> <field> <newtype> [--dry]: a src/scene.fields field given its right type (an int / u32
field that holds a float, as its uses show), and every use in src/ rewritten to keep reading and writing the same
bits:
    (*(float *)&X->f)   -> X->f              (the float view becomes the field itself)
    ((u32)X->f)         -> BITS(X->f)        (a read of the old type's other signedness)
    X->f   (old u32)    -> BITS(X->f)        (the old type's view)
    X->f   (old i32)    -> (*(int *)&X->f)
    BITS(X->f), (*(int *)&X->f)              (views that stay right)
X is any p->f / p.f with the field's name (the name must belong to that struct only in src/scene.fields). Check
afterwards: tools/objcmp.py must show no object changed (a use missed would change its meaning, and its code).
See the rule in memory: a field's type does not change unless all its uses are rewritten this way."""
import re, sys, os, glob

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
args = [a for a in sys.argv[1:] if not a.startswith('--')]
STRUCT, FIELD, NEW = args
DRY = '--dry' in sys.argv

lines = open('src/scene.fields', encoding='latin-1', newline='').read().split('\n')
owners, cur, at = [], None, None
for i, l in enumerate(lines):
	c = l.split('#')[0].strip()
	if c.startswith('struct'):
		cur = c.split()[1]; continue
	m = re.match(r'(\S+\s+\S+\s+)(.+?)(\s*\b%s\b\s*(?:\[\w+\])*)(\s*)$' % FIELD, c)
	if m:
		owners.append(cur)
		if cur == STRUCT:
			at, OLD = i, m.group(2).strip()
			IS_ARRAY = '[' in m.group(3)
if owners != [STRUCT] or at is None:
	raise SystemExit('%s.%s: the name is in %s' % (STRUCT, FIELD, owners))
if OLD not in ('i32', 'u32'):
	raise SystemExit('old type %s: only i32 / u32 fields are retyped here' % OLD)
old_view = 'BITS(%s)' if OLD == 'u32' else '(*(int *)&%s)'

X = r'(?:\w+(?:\[[^\]]*\])?(?:->|\.))+%s(?:\[[^\]]*\])?' % FIELD
total = 0
for f in sorted(glob.glob('src/**/*.[ch]', recursive=True)):
	if os.sep + 'data' + os.sep in f or f.endswith('scene.h'):
		continue
	t = open(f, encoding='latin-1', newline='').read()
	if not re.search(r'\b%s\b' % FIELD, t):
		continue
	keep = []

	def stash(s):
		keep.append(s); return '\x00%d\x00' % (len(keep) - 1)
	n0 = len(re.findall(X, t))
	t2 = re.sub(r'\(\*\(%s \*\)&(%s)\)' % (re.escape(NEW), X), lambda m: stash(m.group(1)), t)
	t2 = re.sub(r'\(\((u32|int)\)(%s)\)' % X,
	            lambda m: stash(('BITS(%s)' if m.group(1) == 'u32' else '(*(int *)&%s)') % m.group(2)), t2)
	t2 = re.sub(r'BITS\((%s)\)' % X, lambda m: stash(m.group(0)), t2)
	t2 = re.sub(r'\(\*\((?:int|u32) \*\)&(%s)\)' % X, lambda m: stash(m.group(0)), t2)
	# (its address taken: the same address; only what it points to is typed anew)
	t2 = re.sub(r'(?<![&\w])&(%s)' % X, lambda m: stash(m.group(0)), t2)
	# (an array used whole, without an index - memcpy, sizeof - stays as it is: its address and size are unchanged)
	t2 = re.sub(X, lambda m: stash(m.group(0) if IS_ARRAY and not m.group(0).endswith(']') else old_view % m.group(0)), t2)
	t2 = re.sub(r'\x00(\d+)\x00', lambda m: keep[int(m.group(1))], t2)
	if t2 != t:
		total += n0
		print('  %s: %d uses' % (f, n0))
		if not DRY:
			open(f, 'w', encoding='latin-1', newline='').write(t2)
if not DRY:
	l = lines[at]
	lines[at] = re.sub(r'\b%s(\s+)%s\b' % (re.escape(OLD), FIELD), lambda m: NEW + ' ' * max(1, len(OLD) + len(m.group(1)) - len(NEW)) + FIELD, l, count=1)
	open('src/scene.fields', 'w', encoding='latin-1', newline='').write('\n'.join(lines))
print('%s.%s: %s -> %s, %d uses rewritten' % (STRUCT, FIELD, OLD, NEW, total))
