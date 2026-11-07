r"""rename_types.py OLD=NEW ...: rename record types (scene.fields structs, game.h typedefs) through src/ (not the
generated src/data or src/scene.h: run tools/mkscene.py and tools/mkdatasrc.py after) and the tools that name them.
In code every whole word OLD; in comments and strings only where it names the type: OLD.field, OLD[, (OLD *),
OLD * / OLD *, "struct OLD", scene.fields' type column. A plain English use ("Top Player", "a Model") is left.
Refuses a NEW already used as a word in src. Line endings kept."""
import glob, os, re, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
pairs = [a.split('=') for a in sys.argv[1:]]
files = [f for f in glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True)
         if os.sep + 'data' + os.sep not in f and not f.endswith('scene.h')]
files.append(os.path.join(R, 'src', 'scene.fields'))
texts = {f: open(f, encoding='latin-1', newline='').read() for f in files}
for old, new in pairs:
	for f, t in texts.items():
		code = re.sub(r'/\*.*?\*/|//[^\n]*|#[^\n]*|"(?:[^"\\]|\\.)*"', '', t, flags=re.S)
		code = re.sub(r'\b(?:VT|DELETING)\(\w+,', '', code)   # (a class name only as a label: VT / DELETING take no type)
		if re.search(r'(?<![\w.])%s\b' % new, code) and not (old == 'Outline' and new == 'MenuOutline'):
			sys.exit('%s already used in %s' % (new, f))

SPLIT = re.compile(r'(/\*.*?\*/|//[^\n]*|"(?:[^"\\]|\\.)*")', re.S)
for f in files:
	t = texts[f]
	if f.endswith('scene.fields'):
		out = []
		for line in t.split('\n'):
			code, sep, cmt = line.partition('#')
			for old, new in pairs:
				code = re.sub(r'\b%s\b' % old, new, code)
				cmt = re.sub(r'\b%s(?=\.[a-z_]|\[| \*\)|\*)' % old, new, cmt)
			out.append(code + sep + cmt)
		nt = '\n'.join(out)
	else:
		parts = SPLIT.split(t)
		for k in range(len(parts)):
			for old, new in pairs:
				if k % 2 == 0:
					parts[k] = re.sub(r'(?<!\.)\b%s\b' % old, new, parts[k])
				else:
					parts[k] = re.sub(r'\b%s(?=\.[a-z_]|\[| \*\)| \*|\*)' % old, new, parts[k])
		nt = ''.join(parts)
	if nt != t:
		open(f, 'w', encoding='latin-1', newline='').write(nt)
		print('changed', os.path.relpath(f, R))
