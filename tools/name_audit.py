r"""name_audit.py [--all]: functions whose name shares no word with their description comment (the comment right
above the definition), for review: a name made before the function was understood can say something else than it
does (msg_newKing built the whole ranking, sound_updateListener added the scores to the title). Name words are
split at _ and case changes; a word matches a comment word with the same first five letters (sets / setup). Words
that say little (get, set, update, draw, the subsystem prefix's 'app' ...) are not counted.
--all: also list the matched ones with their score."""
import glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
WEAK = {'get', 'set', 'update', 'draw', 'do', 'run', 'process', 'handle', 'init', 'make', 'by', 'the', 'a', 'to',
        'of', 'and', 'all', 'one', 'new', 'app', 'sys', 'misc', 'small', 'stub', 'is', 'on', 'off', 'from', 'with',
        'bits', 'n', 'x', 'at', 'in', 'for', 'or', 'it', 'its', 'thiscall', 'this', 'fn', 'func'}
DEF = re.compile(r'^\w[\w \*]*?\((\w+)\)\(', re.M)   # (as tools/srcaudit.py finds them)


def words(name):
	parts = re.findall(r'[A-Z]?[a-z]+|[A-Z]+(?![a-z])|\d+', name)
	return [p.lower() for p in parts if p.lower() not in WEAK and len(p) > 1 and not p.isdigit()]


def stem(w):
	return w[:5]


rows = []
for f in glob.glob('src/**/*.c', recursive=True):
	if os.sep + 'data' + os.sep in f:
		continue
	t = open(f, encoding='latin-1').read()
	for m in DEF.finditer(t):
		name = m.group(1)
		line_end = t.find('\n', m.start())
		line = t[m.start():line_end if line_end >= 0 else len(t)]
		before = t[:m.start()].rstrip()
		if '/*' in line and line.rstrip().endswith('*/'):   # (a one-line function's comment after it)
			comment = line[line.rindex('/*'):]
		elif before.endswith('*/'):
			comment = before[before.rfind('/*'):]
		else:
			continue
		if len(re.findall(r'[A-Za-z]{3,}', re.sub(r'0x[0-9a-f]+', '', comment))) < 4:   # (an address or a heading only)
			continue
		cw = {stem(w.lower()) for w in re.findall(r'[A-Za-z]+', comment)}
		cw |= {stem(w) for n in re.findall(r'\b\w+_\w+\b', comment) for w in words(n)}
		nw = words(name.split('_', 1)[1] if '_' in name else name)
		if not nw:
			continue
		hit = [w for w in nw if stem(w) in cw]
		rows.append((len(hit) / len(nw), name, f.replace(os.sep, '/'), ' '.join(comment.split())[:150]))
rows.sort()
for score, name, f, c in rows:
	if score == 0 or '--all' in sys.argv:
		print('%.2f %-34s %s\n      %s' % (score, name, f, c))
print(sum(1 for r in rows if r[0] == 0), 'of', len(rows), 'functions share no word with their comment')
