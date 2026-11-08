"""mkcrt.py: src/crt_addrs.h, the game's C runtime entries by name (CRTADDR_<name>), from standalone/crt.c's tables
(k_msvcrt: the entries AxisRC.exe takes from msvcrt.dll; jump(): the ones it rebuilds). Then, with --rewrite, src
(not src/data) is rewritten to use them: GAME_CDECL(0x49ea80, ...) -> CRT_CALL(strncpy, ...), IMG(0x49fd2d) ->
IMG(CRT(vectorConstruct)), RELOC(0x49ec14) -> RELOC(CRT(ftol)). The generated code is unchanged."""
import glob, os, re, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
SPECIAL = {'??3@YAXPAX@Z': 'operator_delete', '??2@YAPAXI@Z': 'operator_new', 'vector_construct': 'vectorConstruct',
           'vector_destruct': 'vectorDestruct'}


def entries():
	t = open(os.path.join(R, 'standalone', 'crt.c'), encoding='latin-1').read()
	out = {}
	for a, n in re.findall(r'\{ (0x[0-9a-f]+), "([^"]+)" \}', t):
		out[int(a, 16)] = SPECIAL.get(n, n.lstrip('_'))
	for a, n in re.findall(r'jump\((0x[0-9a-f]+), (\w+)\);', t):
		out[int(a, 16)] = SPECIAL.get(n, n[4:] if n.startswith('crt_') else n)
	return out


def main():
	e = entries()
	lines = ['/* crt_addrs.h (tools/mkcrt.py, from standalone/crt.c): the game\'s C runtime entries by name, CRTADDR_<name> -',
	         '   CRT_CALL(name, ret, arg types...)(args) calls one, CRT(name) is its address (src/axis.h) */',
	         '#pragma once']
	lines += ['#define CRTADDR_%s 0x%x' % (n, a) for a, n in sorted(e.items())]
	lines += ['/* every entry, as X(name) (the portable build\'s table of them, src/axis.h) */',
	          '#define CRT_ENTRIES(X) ' + ' '.join('X(%s)' % n for a, n in sorted(e.items()))]
	open(os.path.join(R, 'src', 'crt_addrs.h'), 'w', newline='\n').write('\n'.join(lines) + '\n')
	print('%d runtime entries' % len(e))
	if '--rewrite' not in sys.argv:
		return
	changed = 0
	for p in glob.glob(os.path.join(R, 'src', '**', '*.[ch]'), recursive=True):
		rel = os.path.relpath(p, os.path.join(R, 'src')).replace(os.sep, '/')
		if rel.startswith('data/') or rel == 'crt_addrs.h':
			continue
		t = open(p, encoding='latin-1', newline='').read()
		u = re.sub(r'\bGAME_CDECL\((0x[0-9a-f]+),', lambda m: 'CRT_CALL(%s,' % e[int(m.group(1), 16)] if int(m.group(1), 16) in e else m.group(0), t)
		u = re.sub(r'\b(IMG|RELOC)\((0x[0-9a-f]+)\)', lambda m: '%s(CRT(%s))' % (m.group(1), e[int(m.group(2), 16)]) if int(m.group(2), 16) in e else m.group(0), u)
		if u != t:
			open(p, 'w', encoding='latin-1', newline='').write(u)
			changed += 1
	print('%d files changed' % changed)


main()
