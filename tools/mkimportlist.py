"""mkimportlist.py: src/import_list.h from src/imports.h - every import of the game as X(name, "DLL"), for the portable
build, which fills the import slots (in g_rdata) by name itself instead of walking the original's import directory
(its header bytes). Imports the game made by ordinal (Winsock) are looked up by their exported name. Run from anywhere."""
import os, re

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
src = open(os.path.join(R, 'src', 'imports.h'), encoding='latin-1').read()
rows = re.findall(r'#define IMP_(\w+) (0x[0-9a-f]+)\s+/\* (\S+) \*/', src)
assert len(rows) == src.count('#define IMP_'), 'an import without its DLL comment'
lines = ['/* import_list.h (tools/mkimportlist.py, from imports.h): every import of the game as X(name, "DLL"), in slot',
         '   order; the portable build\'s loader fills each slot, IMP_<name>, by name (standalone/portable.c) */',
         '#pragma once',
         '#define IMPORT_LIST(X) \\']
lines += ['\tX(%s, "%s") \\' % (n, d) for n, a, d in sorted(rows, key=lambda r: int(r[1], 16))]
lines.append('')
open(os.path.join(R, 'src', 'import_list.h'), 'w', newline='\n').write('\n'.join(lines) + '\n')
print('%d imports' % len(rows))
