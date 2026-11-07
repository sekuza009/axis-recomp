r"""merge.py out.tsv runs/*.tsv: the function-trace runs merged, one line per function of src/:
name  file  calls  contexts  sessions  callers (name xN; '+off' dropped)  - with the functions never seen as 'NOT RUN'.
Contexts: s<screen> front-end screen, m<matchState> in a match (0 over, 1 loading, 2 playing, 3 free camera, 4 replay)."""
import collections, glob, os, re, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
calls = collections.Counter(); ctx = collections.defaultdict(set); sess = collections.defaultdict(set)
callers = collections.defaultdict(collections.Counter)
for path in sys.argv[2:]:
	s = os.path.basename(path).split('_ftrace')[0]
	for line in open(path, encoding='latin-1'):
		p = line.rstrip('\n').split('\t')
		if len(p) < 4:
			continue
		name = p[0].split('+')[0]
		calls[name] += int(p[1])
		ctx[name].update(c for c in p[2].split(',') if c)
		sess[name].add(s)
		for c in p[3].split(','):
			m = re.match(r'(\S+?)(?:\+[0-9a-f]+)? x(\d+)$', c.strip())
			if m:
				callers[name][m.group(1)] += int(m.group(2))

# every function defined in src (as srcaudit finds them, plus statics)
DEF = re.compile(r'^(?![\s#/{}])[^\n;=(]*?(?:\((\w+)\)|(\w+))\([^;{]*?\)\s*(?:/\*[^\n]*\*/\s*)?\n?\{', re.M)
where = {}
for f in glob.glob(os.path.join(R, 'src', '**', '*.c'), recursive=True):
	if os.sep + 'data' + os.sep in f:
		continue
	t = open(f, encoding='latin-1').read()
	for m in DEF.finditer(t):
		n = m.group(1) or m.group(2)
		if n not in ('if', 'while', 'for', 'switch', 'return', 'sizeof'):
			where.setdefault(n, os.path.relpath(f, os.path.join(R, 'src')).replace('\\', '/'))

for n in re.findall(r'FN_(\w+)\(void\)', open(os.path.join(R, 'build', 'fn_syms.h')).read()):   # (macro-made ones too)
	if n not in where:
		for f in glob.glob(os.path.join(R, 'src', '**', '*.c'), recursive=True):
			if re.search(r'\b%s\b' % n, open(f, encoding='latin-1').read()):
				where[n] = os.path.relpath(f, os.path.join(R, 'src')).replace(os.sep, '/'); break
for junk in ('DELETING', '__attribute__', '__declspec'):
	where.pop(junk, None)

def order(c):
	return (c[0], int(re.sub(r'\D', '', c) or 99))

with open(sys.argv[1], 'w', encoding='latin-1') as o:
	for n in sorted(set(where) | set(calls)):
		if n in calls:
			cs = ', '.join('%s x%d' % kv for kv in callers[n].most_common(10))
			o.write('%s\t%s\t%d\t%s\t%s\t%s\n' % (n, where.get(n, '-'), calls[n], ','.join(sorted(ctx[n], key=order)),
			                                     ','.join(sorted(sess[n])), cs))
		else:
			o.write('%s\t%s\tNOT RUN\n' % (n, where[n]))
run = sum(1 for n in where if n in calls)
print('%d src functions, %d seen running, %d not run; %d traced names outside src' %
      (len(where), run, len(where) - run, len(set(calls) - set(where))))
