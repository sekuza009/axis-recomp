"""make_lists.py: the names checked by one reviewer only (everything except the 1,165 uncertain ones), as review lists:
F1..F3 functions (seen running), D1..D3 data names (fields, globals, objects; seen holding a value), L1..L3 locals
(by file), R1 file-local tables + record types + typedefs + files."""
import os, re, subprocess, sys
R = 'C:/Users/Alexander/Desktop/Axis/recomp/'
A = R + 'tools/names/audit2026-11-07/'
O = 'C:/Users/ALEXAN~1/AppData/Local/Temp/claude/fca37c0dc9bd4171/3a18fdb3-2d6d-49f5-93d8-8cffd7d6280e/scratchpad/audit5/'
unc = set()
for f in ('uncertain_U1.txt', 'uncertain_U2.txt', 'uncertain_U3.txt'):
	for l in open(A + f, encoding='latin-1'):
		unc.add(l.split('|')[0].strip())

def split(items, n, prefix):
	k = (len(items) + n - 1) // n
	for i in range(n):
		part = items[i * k:(i + 1) * k]
		open(O + '%s%d.txt' % (prefix, i + 1), 'w', encoding='latin-1').write('\n'.join(part) + '\n')
		print(prefix + str(i + 1), len(part))

# functions: every definition in src (merge.py's pattern) minus the uncertain (never run) ones
DEF = re.compile(r'^(?![\s#/{}])[^\n;=(]*?(?:\((\w+)\)|(\w+))\([^;{]*?\)\s*(?:/\*[^\n]*\*/\s*)?\n?\{', re.M)
funcs = []
for root, d, fs in os.walk(R + 'src'):
	if 'data' in root.replace('\\', '/').split('/'):
		continue
	for f in sorted(fs):
		if f.endswith('.c'):
			rel = os.path.relpath(os.path.join(root, f), R + 'src').replace('\\', '/')
			for m in DEF.finditer(open(os.path.join(root, f), encoding='latin-1').read()):
				n = m.group(1) or m.group(2)
				if n not in ('if', 'while', 'for', 'switch', 'return', 'sizeof') and n not in unc:
					funcs.append('%s | %s' % (n, rel))
funcs = sorted(set(funcs), key=lambda s: (s.split(' | ')[1], s))
split(funcs, 3, 'F')

# data: every record field, global and object, minus the uncertain ones
fields = open(R + 'src/scene.fields', encoding='latin-1').read()
data, cur = [], None
for line in fields.split('\n'):
	m = re.match(r'struct (\w+) ', line)
	if m:
		cur = m.group(1); continue
	m = re.match(r'(?:0x)?[0-9a-f]+\s+(?:0x)?[0-9a-f]+\s+(?:struct\s+)?[\w]+\s*\**\s*(\w+)', line)
	if cur and m:
		n = '%s.%s' % (cur, m.group(1))
		if n not in unc:
			data.append(n)
for h in ('globals.h', 'objects.h'):
	for m in re.finditer(r'(?m)^#define ([gk]_\w+) ', open(R + 'src/' + h, encoding='latin-1').read()):
		if m.group(1) not in unc:
			data.append(m.group(1))
split(data, 3, 'D')

# locals: by file (the lister's output), three groups of files
subprocess.run([sys.executable, O + '../audit3/list_locals.py', R, O + 'locals.tsv'], check=True)
rows = [l for l in open(O + 'locals.tsv', encoding='latin-1') if not re.match(r'[^\t]*\t[^\t]*\t(ADDR|offsetof|STR|OBJ|FN_ADDR|IMG|RELOC|GAME_\w+|[A-Z_0-9]+)\t', l)]
files = sorted(set(r.split(':')[0] for r in rows))
cnt = {f: sum(1 for r in rows if r.startswith(f + ':')) for f in files}
groups, acc, g = [[], [], []], 0, 0
tot = sum(cnt.values())
for f in files:
	if acc > tot * (g + 1) / 3 and g < 2:
		g += 1
	groups[g].append(f); acc += cnt[f]
for i, fs in enumerate(groups):
	sel = [r.rstrip('\n') for r in rows if r.split(':')[0] in fs]
	open(O + 'L%d.txt' % (i + 1), 'w', encoding='latin-1').write('\n'.join(sel) + '\n')
	print('L%d' % (i + 1), len(sel), 'locals in', len(fs), 'files')

# the rest: file-local tables, record types, typedefs, files
rest = [l.rstrip('\n') for l in open(O + '../audit3/statics.txt', encoding='latin-1')]
rest += ['struct %s' % s for s in re.findall(r'(?m)^struct (\w+) ', fields)]
rest += ['typedef %s' % t for t in re.findall(r'\}\s*(\w+);', open(R + 'src/game.h', encoding='latin-1').read())]
for root, d, fs in os.walk(R + 'src'):
	if 'data' in root.replace('\\', '/').split('/'):
		continue
	rest += ['file ' + os.path.relpath(os.path.join(root, f), R).replace('\\', '/') for f in sorted(fs) if f.endswith(('.c', '.h'))]
open(O + 'R1.txt', 'w', encoding='latin-1').write('\n'.join(rest) + '\n')
print('R1', len(rest))
