r"""rename_fields.py old=new... [--comment=new:text]...: struct fields renamed in src (the .c and .h files but the
generated scene.h) and in src/scene.fields; then run tools/mkscene.py. Names are replaced only as members: after
-> or ., as offsetof(T, name), and as the declared name in scene.fields (so a word also used in comments or as a
local stays). --comment=new:text sets that field's comment in scene.fields (every struct declaring it;
--comment=Struct.new:text only that struct's).
The code is the same (check: tools/objcmp.py)."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
pairs = [a.split('=', 1) for a in sys.argv[1:] if '=' in a and not a.startswith('--')]
comments = dict(a[len('--comment='):].split(':', 1) for a in sys.argv[1:] if a.startswith('--comment='))


def rewrite(path, fn):
	raw = open(path, encoding='latin-1', newline='').read()
	new = fn(raw)
	if new != raw:
		open(path, 'w', encoding='latin-1', newline='').write(new)
		return 1
	return 0


def code(t):
	for old, new in pairs:
		t = re.sub(r'(->|\.)(\s*)%s\b' % re.escape(old), r'\1\2' + new, t)
		t = re.sub(r'(offsetof\(\s*\w+\s*,\s*)%s\b' % re.escape(old), r'\1' + new, t)
	return t


n = 0
for f in glob.glob('src/**/*.[ch]', recursive=True):
	if os.path.basename(f) == 'scene.h':
		continue
	n += rewrite(f, code)


def fields(t):
	out = []
	struct = ''
	for line in t.split('\n'):
		if line.startswith('struct '):
			struct = line.split()[1]
		m = re.match(r'^(\S+\s+\S+\s+[\w ]+?\b)(\w+)(\[[^\]]*\])?(\s*)(#.*)?(\r?)$', line)
		if m and not line.startswith(('#', 'struct ')):
			name = m.group(2)
			for old, new in pairs:
				if name == old:
					name = new
			pre, arr, sp, com, cr = m.group(1), m.group(3) or '', m.group(4), m.group(5), m.group(6)
			text = comments.get(struct + '.' + name, comments.get(name))   # (Struct.name: that struct's only)
			if text is not None:
				decl = pre + name + arr
				com = '# ' + text
				sp = ' ' * max(1, 64 - len(decl)) if len(decl) < 64 else ' '
			if name != m.group(2) or text is not None:
				line = pre + name + arr + (sp + com if com else '') + cr
		out.append(line)
	return '\n'.join(out)


n += rewrite('src/scene.fields', fields)
print(n, 'files changed')
