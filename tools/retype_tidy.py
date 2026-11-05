r"""retype_tidy.py <files>: casts retype_var.py leaves doubled:
  (T *)((u8 *)&X)          -> &X
  ((const T *)((u8 *)v))   -> v      ((T *)((u8 *)v)) -> v
The compiler (no new warnings) and objcmp confirm."""
import re, sys
for p in sys.argv[1:]:
	t = open(p, encoding='latin-1', newline='').read()
	o = t
	t = re.sub(r'\((?:const\s+)?[A-Z]\w*\s*\*\)\s*\(\(u8 \*\)(&[^;,()]+(?:\[[^\]]*\])?(?:\([^()]*\))?)\)', r'\1', t)
	t = re.sub(r'\(\((?:const\s+)?[A-Z]\w*\s*\*\)\s*\(\(u8 \*\)(\w+)\)\)', r'\1', t)
	if t != o:
		open(p, 'w', encoding='latin-1', newline='').write(t)
		print(p)
