r"""img_casts.py [--dry] [files...]: an address of the game's image written as a pointer, (T *)0x4b0268, becomes
(T *)IMG(0x4b0268): the image's place in AxisRC.exe (src/axis.h; in the harness IMG(a) is a, so its objects do not
change - check with objcmp.py). Only literals right after a cast to a pointer type (one with a *: data, function
and array pointers); casts to integers are left as numbers (GAME_VAR relocates them when they are used)."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
LO, HI = 0x400000, 0xb6b000
files = [a for a in sys.argv[1:] if not a.startswith('--')] or [
	f for f in glob.glob('src/**/*.[ch]', recursive=True) if os.path.basename(os.path.dirname(f)) != 'data']
total = 0
for f in sorted(files):
	t = open(f, 'rb').read().decode('latin-1')
	mask = re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"', lambda m: '\0' * len(m.group(0)), t, flags=re.S)
	out, k, n = [], 0, 0
	for m in re.finditer(r'\)(\s*\(?\s*)(0x0*([0-9a-f]{6,7}))\b', mask):
		a = int(m.group(3), 16)
		if not LO <= a < HI:
			continue
		# the cast this ) closes
		depth, j = 0, m.start()
		while j >= 0:
			if mask[j] == ')': depth += 1
			elif mask[j] == '(':
				depth -= 1
				if depth == 0: break
			j -= 1
		cast = mask[j + 1:m.start()]
		if j < 0 or '*' not in cast or not re.fullmatch(r'[\w\s\*\(\)\[\],.]+', cast) or re.search(r'\b(sizeof|return)\b', cast):
			continue
		if re.search(r'\w\s*$', mask[max(0, j - 40):j]) and not re.search(r'\b(return|case|else)\s*$', mask[max(0, j - 40):j]):
			continue   # (a call's argument list, not a cast)
		out.append(t[k:m.start(2)] + 'IMG(%s)' % m.group(2))
		k = m.end(2); n += 1
	if n:
		total += n
		print('%-40s %d' % (f, n))
		if '--dry' not in sys.argv:
			open(f, 'wb').write((''.join(out) + t[k:]).encode('latin-1'))
print(total, 'casts')
