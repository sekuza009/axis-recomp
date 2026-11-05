r"""x87_macros.py [files]: fmul_m(fld_m(&a), &b) -> FMUL(a, b) (and fadd_m / fsub_m / fdiv_m -> FADD / FSUB / FDIV),
a and b any balanced expressions; the macros in axis.h expand back to the same calls, so the code is the same (check:
tools/objcmp.py). Comments and strings are left alone."""
import os, re, sys, glob
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
OPS = {'fmul_m': 'FMUL', 'fadd_m': 'FADD', 'fsub_m': 'FSUB', 'fdiv_m': 'FDIV'}
files = [f for f in sys.argv[1:] if not f.startswith('--')] or [p for p in glob.glob('src/**/*.c', recursive=True) if 'data' not in os.path.dirname(p)]


def balanced(s, i):
	"""the index just past the expression starting at s[i], ending at a top-level ',' or ')'"""
	d = 0
	while i < len(s):
		c = s[i]
		if c in '([':
			d += 1
		elif c in ')]':
			if d == 0:
				return i
			d -= 1
		elif c == ',' and d == 0:
			return i
		i += 1
	return -1


def convert(code):
	out, i, n = [], 0, 0
	rx = re.compile(r'\b(fmul_m|fadd_m|fsub_m|fdiv_m)\(fld_m\(&')
	while True:
		m = rx.search(code, i)
		if not m:
			out.append(code[i:])
			return ''.join(out), n
		a0 = m.end()
		a1 = balanced(code, a0)
		# fld_m(&a) closes, then ', &b)'
		if a1 < 0 or code[a1] != ')' or not code[a1 + 1:].startswith(', &'):
			out.append(code[i:m.end()])
			i = m.end()
			continue
		b0 = a1 + 4
		b1 = balanced(code, b0)
		if b1 < 0 or code[b1] != ')':
			out.append(code[i:m.end()])
			i = m.end()
			continue
		a, b = code[a0:a1].strip(), code[b0:b1].strip()
		# a lone '&x' argument whose expression starts with a cast or a dereference needs no change; keep it as written
		inner_a, _ = convert(a)
		inner_b, _ = convert(b)
		out.append(code[i:m.start()] + '%s(%s, %s)' % (OPS[m.group(1)], inner_a, inner_b))
		i = b1 + 1
		n += 1


total = 0
for p in files:
	t = open(p, encoding='latin-1', newline='').read()
	parts = re.split(r'(/\*.*?\*/|"(?:\\.|[^"\\\n])*")', t, flags=re.S)
	cnt = 0
	for k in range(0, len(parts), 2):
		parts[k], n = convert(parts[k])
		cnt += n
	if cnt:
		open(p, 'w', encoding='latin-1', newline='').write(''.join(parts))
		total += cnt
print(total, 'rewritten')
