r"""promote_locals.py [--dry]: the game's data globals that only have local names (a "#define g_x GAME_VAR(T, 0x...)"
in game.h or one file) moved into src/globals.h, so the split tools see them (step 3b).

For each address of .data (0x4ad000 .. 0xb13000) without a globals.h name: the name kept is game.h's, else a g_
name defined in one file only (and not defined elsewhere for another address). That define is moved to globals.h
(the same text, so every use stays as it is); the address's other local defines become aliases of it
("#define g_panelSize3 g_flareSizeB", or "(*(T *)&g_name)" when their type differs); a second copy of the same define
in another file is removed. Addresses whose local names are not g_ names (X0, TIMER ...) are left as they are."""
import collections, glob, os, re, sys

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
HEADER = 'src/globals.h'
ghead = open(HEADER).read()
gaddr = {int(a, 16) for a in re.findall(r'#define \w+ GAME_VAR\([\w \*]+, (0x[0-9a-f]+)\)', ghead)}
files = sorted(f.replace('\\', '/') for f in glob.glob('src/**/*.[ch]', recursive=True)
               if os.sep + 'data' + os.sep not in f and not f.endswith('globals.h'))
texts = {f: open(f, 'rb').read().decode('latin-1') for f in files}
# (a define with its comment, which may run on over further lines up to its */)
DEF = re.compile(r'^[ \t]*#define[ \t]+(\w+)[ \t]+GAME_VAR\(([\w \*]+?)\s*,\s*(0x[0-9a-f]+)\)(?:[ \t]*/\*(?:(?!\*/).)*\*/)?[^\n]*\n', re.M | re.S)
defs = collections.defaultdict(list)    # address -> [(name, type, file, the line)]
where = collections.defaultdict(set)    # name -> files defining it (any address)
for f, t in texts.items():
	for m in DEF.finditer(t):
		n, ty, a = m.group(1), re.sub(r'\s+', ' ', m.group(2).strip()), int(m.group(3), 16)
		where[n].add((f, a))
		if 0x4ad000 <= a < 0xb13000 and a not in gaddr:
			defs[a].append((n, ty, f, m.group(0)))
moved, aliased, removed = [], 0, 0
new = dict(texts)
for a in sorted(defs):
	ds = defs[a]
	gnames = [d for d in ds if d[0].startswith('g_')]
	if not gnames:
		continue
	keep = next((d for d in gnames if d[2] == 'src/game.h'), None)
	if keep is None:
		cand = [d for d in gnames if all(x[1] == a for x in where[d[0]])]
		if not cand:
			continue
		keep = cand[0]
	name, ty = keep[0], keep[1]
	if any(x[1] != a for x in where[name]):
		continue   # (the same name for another address somewhere: left alone)
	for n, t2, f, line in ds:
		if n == name:
			new[f] = new[f].replace(line, '', 1)
			removed += 1
		else:
			alias = name if t2 == ty else '(*(%s *)&%s)' % (t2, name)
			comment = re.search(r'/\*.*?\*/', line, re.S)
			new[f] = new[f].replace(line, '#define %s %s%s\n' % (n, alias, ('   ' + comment.group(0)) if comment else ''), 1)
			aliased += 1
	comment = re.search(r'/\*.*?\*/', keep[3], re.S)
	moved.append('#define %s GAME_VAR(%s, 0x%x)%s' % (name, ty, a, ('   ' + comment.group(0)) if comment else ''))
print('%d names moved to globals.h, %d other local names made aliases, %d local defines removed' % (len(moved), aliased, removed - len(moved)))
if '--dry' in sys.argv:
	print('\n'.join(moved[:20]))
	sys.exit()
for f in files:
	if new[f] != texts[f]:
		open(f, 'wb').write(new[f].encode('latin-1'))
with open(HEADER, 'a', newline='\n') as h:
	h.write('/* moved from game.h and the files\' own defines (tools/promote_locals.py) */\n' + '\n'.join(moved) + '\n')
