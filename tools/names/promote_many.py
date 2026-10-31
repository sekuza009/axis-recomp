r"""promote_many.py mapping.csv: like promote_globals.py, for a global that several files (or several scopes of one
file) name locally. Lines "address,type,local name,file,global name". Every "#define local GAME_VAR(type, address)"
of that file and its "#undef local" are removed and the local name renamed to the global one there; then the
global names are defined in src/globals.h and retype_uses.py writes the rest of the raw uses with them. A
global name that some other file uses for something else stops the run before anything is written."""
import collections, glob, os, re, subprocess, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
rows = []
for line in open(sys.argv[1], encoding='utf-8'):
	line = line.split('#', 1)[0].strip()
	if line:
		a, t, local, path, name = [x.strip() for x in line.split(',')]
		rows.append((int(a, 16), t, local, path.replace('\\', '/'), name))
texts = {f.replace('\\', '/'): open(f, 'rb').read().decode('latin-1')
         for f in glob.glob('src/**/*.[ch]', recursive=True)}
texts['recomp.c'] = open('recomp.c', 'rb').read().decode('latin-1')
files_of = collections.defaultdict(set)
for a, t, local, path, name in rows:
	files_of[name].add(path)
bad = 0
for a, t, local, path, name in rows:
	tp = re.escape(t).replace(r'\ ', r'\s*').replace(r'\*', r'\s*\*')
	d = re.compile(r'^[ \t]*#define[ \t]+%s[ \t]+GAME_VAR\(\s*%s\s*,\s*0x0*%x\s*\)' % (local, tp, a), re.M)
	other = re.compile(r'^[ \t]*#define[ \t]+%s[ \t]' % local, re.M)
	if path not in texts or not d.search(texts[path]):
		print('no local define of %s in %s' % (local, path)); bad += 1
	elif len(other.findall(texts[path])) != len(d.findall(texts[path])):
		print('%s in %s is defined for something else too' % (local, path)); bad += 1
	for f, u in texts.items():
		if f not in files_of[name] and re.search(r'\b%s\b' % name, u):
			print('%s already used in %s' % (name, f)); bad += 1
if bad:
	sys.exit('%d problems, nothing changed' % bad)
for a, t, local, path, name in rows:
	u = texts[path]
	u = re.sub(r'^[ \t]*#define[ \t]+%s[ \t]+GAME_VAR\([^\n]*\n' % local, '', u, flags=re.M)
	u = re.sub(r'^[ \t]*#undef[ \t]+%s[ \t]*\r?\n' % local, '', u, flags=re.M)
	u = re.sub(r'\b%s\b' % local, name, u)
	texts[path] = u
	open(path, 'wb').write(u.encode('latin-1'))
head = open('src/globals.h').read()
for a, t, name in sorted({(a, t, name) for a, t, local, path, name in rows}):
	head += '#define %s GAME_VAR(%s, 0x%x)\n' % (name, t, a)
open('src/globals.h', 'w', newline='\n').write(head)
subprocess.run([sys.executable, 'tools/names/retype_uses.py'], check=True)
print('%d promoted' % len({r[4] for r in rows}))
