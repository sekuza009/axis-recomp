"""Message-table addresses in comments (0x74de24 + n * 0x80) -> MSG(n, "text") as the code writes them."""
import os, re, glob, subprocess, sys
os.chdir(r'C:\Users\Alexander\Desktop\Axis\recomp')
BASE, END = 0x74de24, 0x74de24 + 128256
apply = '--apply' in sys.argv
cache = {}


def text(n):
	if n not in cache:
		out = subprocess.run([sys.executable, 'tools/names/msgtext.py', hex(BASE + n * 0x80)], capture_output=True, text=True).stdout
		m = re.match(r'\S+\s+#\d+\s+(.*)', out.split('\n')[0])
		cache[n] = m.group(1).strip() if m else None
	return cache[n]


count = 0
for p in glob.glob('src/**/*.c', recursive=True):
	if 'data' in os.path.dirname(p):
		continue
	t = open(p, encoding='latin-1', newline='').read()

	def fix_comment(cm):
		global count
		c = cm.group(0)

		def sub(m):
			global count
			v = int(m.group(1), 16)
			if not (BASE <= v < END) or (v - BASE) % 0x80:
				return m.group(0)
			n = (v - BASE) // 0x80
			s = text(n)
			if s is None or n >= 1000 or '*/' in s or 'MSG(%d,' % n in c:
				return m.group(0)
			if len(s) > 40:
				s = s[:37] + '...'
			count += 1
			if not apply:
				print('%-20s %s -> MSG(%d, "%s")' % (os.path.basename(p), m.group(0), n, s))
			return 'MSG(%d, "%s")' % (n, s)
		return re.sub(r'(?<![\w+])0x([0-9a-f]{6})\b', sub, c)

	nt = re.sub(r'/\*.*?\*/', fix_comment, t, flags=re.S)
	if apply and nt != t:
		open(p, 'w', encoding='latin-1', newline='').write(nt)
print(count, 'replaced' if apply else 'to replace')
