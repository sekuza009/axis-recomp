r"""names_to_symbols.py mapping.csv ...: add the naming pass's names to ../decomp/symbols.csv (address,func,name,comment)
for every old name that carries its address (FUN_0046c580, match_4799f0, ...) and whose address the file does not list
yet, so a Ghidra re-export (decomp/scripts) shows them. Keeps the file's line endings."""
import os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
path = '../decomp/symbols.csv'
raw = open(path, 'rb').read()
eol = b'\r\n' if b'\r\n' in raw else b'\n'
have = set(m.lower() for m in re.findall(rb'^([0-9a-fA-F]{8}),', raw, re.M))
add = []
for mf in sys.argv[1:]:
    for line in open(mf, encoding='utf-8'):
        line = line.split('#', 1)[0].strip()
        if not line:
            continue
        old, new = [x.strip() for x in line.split(',')]
        m = re.search(r'([0-9a-f]{6,8})$', old)
        if not m:
            continue
        addr = m.group(1).rjust(8, '0').encode()
        if addr not in have:
            add.append(addr + b',func,' + new.encode() + b',naming pass (was ' + old.encode() + b')')
            have.add(addr)
if add:
    if not raw.endswith(eol):
        raw += eol
    raw += eol.join(add) + eol
    open(path, 'wb').write(raw)
print(len(add), 'names added to', path)
