"""edit.py FILE: exact-string replacements read from stdin as blocks 'old' / 'new' separated by lines '@@@' and
'===' (old === new @@@ ...); each old must occur exactly once (or N times with a first line '#N'). Keeps CRLF."""
import sys
p = sys.argv[1]
raw = open(p, 'rb').read().decode('latin-1')
crlf = '\r\n' in raw
t = raw.replace('\r\n', '\n')
for block in sys.stdin.read().split('\n@@@\n'):
    if not block.strip():
        continue
    old, new = block.split('\n===\n')
    n = 1
    if old.startswith('#') and old[1:].split('\n')[0].isdigit():
        n = int(old[1:].split('\n')[0]); old = old.split('\n', 1)[1]
    new = new.rstrip('\n') if not old.endswith('\n') else new
    c = t.count(old)
    if c != n:
        sys.exit('%s: %d matches (want %d) for:\n%s' % (p, c, n, old))
    t = t.replace(old, new)
open(p, 'wb').write((t.replace('\n', '\r\n') if crlf else t).encode('latin-1'))
print('ok', p)
