r"""alias_names.py: Scene fields over the Stage region (Scene + 0x1f36c8 = Stage + 0) that overlap a Stage field of
another name - the same bytes named twice. Each pair should say the same thing (best: the same name, or one
saying '= Stage.x'). For the name review."""
import os, re

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
BASE = 0x1f36c8
structs, cur = {}, None
for line in open('src/scene.fields', encoding='latin-1'):
	if line.startswith('struct '):
		cur = line.split()[1]; structs[cur] = []; continue
	m = re.match(r'^(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+[\w ]+?\b(\w+)(\[[^\]]*\])?\s*(#.*)?$', line.rstrip())
	if m and cur:
		structs[cur].append((int(m.group(1), 0), int(m.group(2), 0), m.group(3), (m.group(5) or '').strip()))
n = 0
stage = sorted(structs['Stage'])
for off, size, name, com in sorted(structs['Scene']):
	if off < BASE:
		continue
	so = off - BASE
	hits = [f for f in stage if f[0] < so + size and so < f[0] + f[1] and f[1] < 0x10000]
	for f in hits:
		if f[2] == name or ('Stage.' + f[2]) in com:
			continue
		n += 1
		print('Scene.%-24s +%#x (%#x)  ~ Stage.%-24s +%#x (%#x)\n      %s\n      %s' % (name, off, size, f[2], f[0], f[1], com[:110], f[3][:110]))
print(n, 'pairs')
