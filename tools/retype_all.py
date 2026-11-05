r"""retype_all.py [--dry] [--file=SUBSTR]: retype_var.py for every u8 * local that a function only casts to one struct
type ((T *)v)->...; parameters and declarator lists are left (retype_var refuses them). Check with tools/objcmp.py."""
import os, re, glob, sys, subprocess
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
dry = '--dry' in sys.argv
only = next((a.split('=', 1)[1] for a in sys.argv if a.startswith('--file=')), None)
done = 0
for p in sorted(glob.glob('src/**/*.c', recursive=True)):
	if 'data' in os.path.dirname(p) or (only and only not in p.replace('\\', '/')):
		continue
	t = open(p, encoding='latin-1').read()
	jobs = []
	for m in re.finditer(r'\((\w+)\)\s*\([^)]*\)\s*\n\{', t):
		a = m.end() - 1
		depth = 0
		for b in range(a, len(t)):
			depth += {'{': 1, '}': -1}.get(t[b], 0)
			if depth == 0:
				break
		body = t[a:b]
		casts = {}
		for T, v in re.findall(r'\(\(([A-Z]\w*)\s*\*\)\s*(\w+)\)\s*->', body):
			casts.setdefault(v, set()).add(T)
		for v, Ts in casts.items():
			if len(Ts) != 1 or not re.search(r'\bu8\s*\*\s*%s\b' % re.escape(v), body):
				continue
			if re.search(r'\((?:const\s+)?\w+\s*\*\s*\)\s*%s\b(?!\))' % re.escape(v), body.replace('((%s *)%s)' % (list(Ts)[0], v), '')):
				pass
			jobs.append((m.group(1), v, list(Ts)[0]))
	for fn, v, T in jobs:
		r = subprocess.run([sys.executable, 'tools/retype_var.py', p, fn, v, T] + (['--dry'] if dry else []), capture_output=True, text=True)
		msg = (r.stdout + r.stderr).strip()
		if r.returncode == 0:
			done += 1
		print('%s: %s' % (os.path.basename(p), msg))
	if not dry:
		t2 = open(p, encoding='latin-1', newline='').read()
		t3 = re.sub(r'RELOC\(\(\(u8 \*\)(\w+)\)\)', r'RELOC(\1)', t2)
		if t3 != t2:
			open(p, 'w', encoding='latin-1', newline='').write(t3)
print(done, 'retyped')
