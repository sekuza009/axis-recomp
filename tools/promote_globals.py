r"""promote_globals.py mapping.csv [--dry]: make a file's local name for a game global into a name in src/globals.h.

Each mapping line is "address,type,local name,file,global name" ('#' starts a comment). The file's
"#define local GAME_VAR(type, address)" is removed, the local name renamed to the global one in that file, and then
tools/name_globals.py (with --reuse) defines the global name and replaces the raw GAME_VAR(type, address) uses in
every file. A global name already used elsewhere (outside that file) stops the run before anything is written."""
import glob, os, re, subprocess, sys, tempfile

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
rows = []
for line in open(sys.argv[1], encoding='utf-8'):
    line = line.split('#', 1)[0].strip()
    if line:
        addr, typ, local, path, glob_name = [x.strip() for x in line.split(',')]
        rows.append((int(addr, 16), typ, local, path.replace('\\', '/'), glob_name))
texts = {f.replace('\\', '/'): open(f, 'rb').read().decode('latin-1')
         for f in glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True)}
texts['recomp.c'] = open('recomp.c', 'rb').read().decode('latin-1')
bad = 0
for addr, typ, local, path, name in rows:
    t = texts.get(path)
    d = re.compile(r'^[ \t]*#define[ \t]+%s[ \t]+GAME_VAR\(\s*%s\s*,\s*0x0*%x\s*\)[^\n]*\n' %
                   (local, re.escape(typ).replace(r'\ ', r'\s*').replace(r'\*', r'\s*\*'), addr), re.M)
    if t is None or len(d.findall(t)) != 1:
        print('no single local define of %s in %s' % (local, path)); bad += 1
    if name != local and any(re.search(r'\b%s\b' % name, u) for f, u in texts.items()):
        print('already exists:', name); bad += 1
    if name == local and any(re.search(r'\b%s\b' % name, u) for f, u in texts.items() if f != path):
        print('used outside %s: %s' % (path, name)); bad += 1
if bad:
    sys.exit('%d problems, nothing changed' % bad)
if '--dry' in sys.argv:
    sys.exit('%d promotions would be made' % len(rows))
for addr, typ, local, path, name in rows:
    t = texts[path]
    d = re.compile(r'^[ \t]*#define[ \t]+%s[ \t]+GAME_VAR\(\s*%s\s*,\s*0x0*%x\s*\)[^\n]*\n' %
                   (local, re.escape(typ).replace(r'\ ', r'\s*').replace(r'\*', r'\s*\*'), addr), re.M)
    t = d.sub('', t, count=1)
    t = re.sub(r'\b%s\b' % local, name, t)
    texts[path] = t
    open(path, 'wb').write(t.encode('latin-1'))
with tempfile.NamedTemporaryFile('w', suffix='.csv', delete=False) as m:
    for addr, typ, local, path, name in rows:
        m.write('0x%x,%s,%s\n' % (addr, typ, name))
subprocess.run([sys.executable, 'tools/name_globals.py', m.name, '--reuse'], check=True)
os.unlink(m.name)
print('%d promoted' % len(rows))
