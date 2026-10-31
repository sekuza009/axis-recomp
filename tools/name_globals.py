r"""name_globals.py mapping.csv [--dry]: name the game's global variables.

Each mapping line is "address,type,name" ('#' starts a comment), e.g. "0xa1efb8,u32,g_randPos". The name is defined
in src/globals.h as GAME_VAR(type, address), and every GAME_VAR(type, address) in src/ written with exactly that type
becomes the name (uses with another type stay as they are, so the generated code does not change). A name already
used anywhere, or an address src/ never uses with that type, stops the run before anything is written. --reuse
allows names already used (to promote a file's local #define of the same global, removed first)."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
HEADER = 'src/globals.h'
entries = []
for line in open(sys.argv[1], encoding='utf-8'):
    line = line.split('#', 1)[0].strip()
    if line:
        addr, typ, name = [x.strip() for x in line.split(',')]
        entries.append((int(addr, 16), typ, name))
files = sorted(glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True))
data = {f: open(f, 'rb').read().decode('latin-1') for f in files}
allt = '\n'.join(data.values()) + open('recomp.c', 'rb').read().decode('latin-1')


def pattern(addr, typ):
    t = re.escape(typ).replace(r'\ ', r'\s*').replace(r'\*', r'\s*\*')
    return re.compile(r'GAME_VAR\(\s*%s\s*,\s*0x0*%x\s*\)' % (t, addr))


bad = 0
for addr, typ, name in entries:
    if '--reuse' not in sys.argv and re.search(r'\b%s\b' % name, allt):
        print('already exists:', name); bad += 1
    if not any(pattern(addr, typ).search(t) for f, t in data.items() if f != HEADER.replace('/', os.sep)):
        print('no GAME_VAR(%s, 0x%x) in src' % (typ, addr)); bad += 1
if bad:
    sys.exit('%d problems, nothing changed' % bad)
count = 0
for f, t in data.items():
    if os.path.normpath(f) == os.path.normpath(HEADER):
        continue
    u = t
    for addr, typ, name in entries:
        u, n = pattern(addr, typ).subn(name, u)
        count += n
    if u != t and '--dry' not in sys.argv:
        open(f, 'wb').write(u.encode('latin-1'))
if '--dry' not in sys.argv:
    head = open(HEADER).read() if os.path.exists(HEADER) else (
        '/* globals.h: the game\'s global variables named (tools/name_globals.py adds them): each is the game\'s own\n'
        '   memory at its address, with the type it is used as. Uses with another type stay written out. */\n'
        '#pragma once\n\n')
    for addr, typ, name in sorted(entries):
        head += '#define %s GAME_VAR(%s, 0x%x)\n' % (name, typ, addr)
    open(HEADER, 'w', newline='\n').write(head)
print('%d names, %d uses %s' % (len(entries), count, 'would change' if '--dry' in sys.argv else 'changed'))
