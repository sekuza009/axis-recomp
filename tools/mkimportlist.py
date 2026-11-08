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
# --thunks out.s: the Windows platform's plat_<name> for each import (src/axis.h IMPORT_FN with AXIS_PORTABLE): a
# jump through the game's import slot in g_rdata, so whatever is in the slot (the network layer's hooks) is called
import sys
if '--thunks' in sys.argv:
	out = sys.argv[sys.argv.index('--thunks') + 1]
	s = ['\t# plat_imports.s (tools/mkimportlist.py): the Windows platform\'s system calls - each a jump through the',
	     '\t# game\'s import slot (in g_rdata at the original\'s offset from 0x4a9000)', '\t.text']
	for n, a, d in sorted(rows, key=lambda r: int(r[1], 16)):
		s += ['\t.globl _plat_%s' % n, '\t.p2align 4', '_plat_%s:\t# %s' % (n, d), '\tjmp *_g_rdata+0x%x' % (int(a, 16) - 0x4a9000)]
	open(out, 'w', newline='\n').write('\n'.join(s) + '\n')
print('%d imports' % len(rows))
