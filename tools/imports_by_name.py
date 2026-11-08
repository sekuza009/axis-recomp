"""imports_by_name.py: rewrites src (not src/data) so import-table slots are named: IMPORT(0x4a9198, ...) and
IMPORT(WS_SEND, ...) become IMPORT_FN(GlobalLock, ...) / IMPORT_FN(send, ...), RELOC(0x4a920c) of a slot becomes
RELOC(IMP_glTexCoord2f). Names from src/imports.h (tools/mkimports.py). The generated code is unchanged."""
import glob, os, re

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
names = {int(a, 16): n for n, a in re.findall(r'#define IMP_(\w+) (0x[0-9a-f]+)', open(os.path.join(R, 'src', 'imports.h')).read())}
ws = {}
wsh = os.path.join(R, 'src', 'net', 'winsock.h')
if os.path.exists(wsh):
	ws = {k: names[int(a, 16)] for k, a in re.findall(r'#define (WS_\w+) (0x[0-9a-f]+)', open(wsh).read())}

def slot(m):
	a = int(m.group(1), 16)
	if a not in names:
		raise SystemExit('no import at %s' % m.group(1))
	return names[a]

changed = 0
for f in glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True):
	rel = os.path.relpath(f, os.path.join(R, 'src')).replace(os.sep, '/')
	if rel.startswith('data/') or rel in ('imports.h', 'axis.h'):
		continue
	t = open(f, encoding='latin-1', newline='').read()
	u = re.sub(r'\bIMPORT\((0x[0-9a-f]+),', lambda m: 'IMPORT_FN(%s,' % slot(m), t)
	u = re.sub(r'\bIMPORT\((WS_\w+),', lambda m: 'IMPORT_FN(%s,' % ws[m.group(1)] if m.group(1) in ws else m.group(0), u)
	u = re.sub(r'\bRELOC\((0x4a9[0-3][0-9a-f]{2})\)', lambda m: 'RELOC(IMP_%s)' % slot(m) if int(m.group(1), 16) in names else m.group(0), u)
	if u != t:
		open(f, 'w', encoding='latin-1', newline='').write(u)
		changed += 1
print('%d files changed' % changed)
