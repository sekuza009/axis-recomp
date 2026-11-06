r"""unread_fields.py: scene.fields fields the rebuilt C never reads - every member access by name is a plain store
(x->f = ..., not ==), no offsetof() names it, and no Scene / Stage field over the same bytes is read either. The C
being the whole game, these are fields the game only writes; their names should not suggest a use (names saying
unused / cleared / only are skipped). A name shared by several structs counts all of their uses (so a listed field
is unread in all of them)."""
import glob, os, re

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
STAGE_IN_SCENE = 0x1f36c8
structs, cur = {}, None
for line in open('src/scene.fields', encoding='latin-1'):
	if line.startswith('struct '):
		cur = line.split()[1]; structs[cur] = []; continue
	m = re.match(r'^(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+[\w ]+?\b(\w+)(\[[^\]]*\])?\s*(#.*)?$', line.rstrip())
	if m and cur:
		structs[cur].append((int(m.group(1), 0), int(m.group(2), 0), m.group(3), (m.group(5) or '').strip()))
code = ''
for f in glob.glob('src/**/*.[ch]', recursive=True):
	if os.path.basename(f) == 'scene.h' or os.sep + 'data' + os.sep in f:
		continue
	code += re.sub(r'/\*.*?\*/', ' ', open(f, encoding='latin-1').read(), flags=re.S)


def is_read(name):
	if re.search(r'offsetof\(\s*\w+\s*,\s*%s\b' % name, code):
		return True
	for m in re.finditer(r'(?:->|\.)\s*%s\b(\s*\[[^\]]*\])*\s*(=?)(=?)' % name, code):
		if m.group(2) == '=' and m.group(3) != '=':
			continue   # a plain store
		return True
	return False


def aliases(st, off, size):
	if st == 'Scene' and off >= STAGE_IN_SCENE:
		return [f for f in structs['Stage'] if f[0] < off - STAGE_IN_SCENE + size and off - STAGE_IN_SCENE < f[0] + f[1]]
	if st == 'Stage':
		return [f for f in structs['Scene'] if f[0] < off + STAGE_IN_SCENE + size and off + STAGE_IN_SCENE < f[0] + f[1]]
	return []


n = 0
for st, fields in structs.items():
	for off, size, name, com in fields:
		if re.search(r'unused|cleared|only|never read|not read|reserved|pad', name + ' ' + com, re.I):
			continue
		if is_read(name):
			continue
		if any(is_read(a[2]) for a in aliases(st, off, size) if a[2] != name):
			continue
		n += 1
		print('%-14s %-26s +%#x  %s' % (st, name, off, com[:110]))
print(n, 'fields never read')
