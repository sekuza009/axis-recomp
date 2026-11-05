r"""retype_unwrap.py <files>: ((u8 *)x) / ((const u8 *)x) wraps that are not needed:
  in comments (prose):                      always -> x
  in code, x only tested for truth:         if (((u8 *)x)) / while (...) / !((u8 *)x) / && ((u8 *)x) / ((u8 *)x) && /
                                            || / ? :  -> x
objcmp confirms the code is the same."""
import re, sys
W = r'\(\((?:const\s+)?u8 \*\)(\w+)\)'
for p in sys.argv[1:]:
	t = open(p, encoding='latin-1', newline='').read()
	o = t
	parts = re.split(r'(/\*.*?\*/|"(?:\\.|[^"\\\n])*")', t, flags=re.S)
	for i, s in enumerate(parts):
		if i % 2:
			if s.startswith('/*'):
				parts[i] = re.sub(W, r'\1', s)
			continue
		s = re.sub(r'\b(if|while)\s*\(\s*' + W + r'\s*\)', r'\1 (\2)', s)
		s = re.sub(r'!\s*' + W, r'!\1', s)
		s = re.sub(r'(&&|\|\|)\s*' + W + r'(?=\s*(?:&&|\|\||\)|\?))', r'\1 \2', s)
		s = re.sub(r'(?<=[(&|]\s)' + W + r'(?=\s*(?:&&|\|\|))', r'\1', s)
		s = re.sub(r'\(\s*' + W + r'\s*(&&|\|\|)', r'(\1 \2', s)
		parts[i] = s
	t = ''.join(parts)
	if t != o:
		open(p, 'w', encoding='latin-1', newline='').write(t)
		print(p)
