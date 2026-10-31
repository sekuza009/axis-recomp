r"""global_contexts2.py addr...: every use of the unnamed globals at those addresses, with the line before and after
and the start of the using function's comment (what the function is for), to name them from"""
import glob, re, sys
addrs = [int(a, 16) for a in sys.argv[1:]]
texts = {f: open(f).read() for f in glob.glob('src/**/*.c', recursive=True)}
for a in addrs:
	print('==== 0x%x' % a)
	pat = re.compile(r'0x0*%x\b' % a)
	for f, t in texts.items():
		lines = t.split('\n')
		for i, l in enumerate(lines):
			if not pat.search(l):
				continue
			# the function around: the last line starting a definition, and the comment above it
			j = i
			while j > 0 and not re.match(r'^\w[\w \*]*?\(\w+\)\(', lines[j]):
				j -= 1
			k = j - 1
			while k > 0 and lines[k].strip() and not lines[k].startswith('}'):
				k -= 1
			comment = ' '.join(x.strip() for x in lines[k + 1:j])[:260]
			print('  %s:%d %s' % (f.split('src')[-1], i + 1, lines[j][:80] if j else '?'))
			if comment:
				print('     | ' + comment)
			for x in range(max(0, i - 1), min(len(lines), i + 2)):
				print('     ' + ('>' if x == i else ' ') + ' ' + lines[x].strip()[:170])
