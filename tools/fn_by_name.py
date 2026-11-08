"""fn_by_name.py: rewrites src (not src/data) so rebuilt functions are named without their address:
FN_ADDR(name, 0x...) -> FN(name), GAME_FN(name, 0x..., ...) -> CALL_FN(name, ...), GAME_THISFN -> CALL_THISFN, where
the address is name's own in src/fn_addrs.h (a mismatch is reported and left). The generated code is unchanged."""
import glob, os, re

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
addr = {n: int(a, 16) for n, a in re.findall(r'#define FNADDR_(\w+) (0x[0-9a-f]+)', open(os.path.join(R, 'src', 'fn_addrs.h')).read())}
bad = []

def sub(kind, new):
	def f(m):
		n, a = m.group(1), int(m.group(2), 16)
		if addr.get(n) != a:
			bad.append('%s(%s, %s)' % (kind, n, m.group(2)))
			return m.group(0)
		return new % n
	return f

changed = 0
for p in glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True):
	rel = os.path.relpath(p, os.path.join(R, 'src')).replace(os.sep, '/')
	if rel.startswith('data/') or rel in ('axis.h', 'fn_addrs.h'):
		continue
	t = open(p, encoding='latin-1', newline='').read()
	u = re.sub(r'\bFN_ADDR\((\w+), (0x[0-9a-f]+)\)', sub('FN_ADDR', 'FN(%s)'), t)
	u = re.sub(r'\bGAME_FN\((\w+), (0x[0-9a-f]+), ', sub('GAME_FN', 'CALL_FN(%s, '), u)
	u = re.sub(r'\bGAME_THISFN\((\w+), (0x[0-9a-f]+), ', sub('GAME_THISFN', 'CALL_THISFN(%s, '), u)
	if u != t:
		open(p, 'w', encoding='latin-1', newline='').write(u)
		changed += 1
print('%d files changed' % changed)
for b in bad:
	print('  left (not that name\'s address):', b)
