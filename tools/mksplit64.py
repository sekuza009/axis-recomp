"""mksplit64.py: src/data/split64.h - the 64-bit build's split variables (src/data/split.h): each back at its original
address in the game's address space, g_arena (src/axis.h, AXIS_64), the bytes there being the game's own memory, as
in the original - no variable of its own. Read from src/data/data.c's definitions (type, name, count, address)."""
import os, re

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'src', 'data')
rows = re.findall(r'^((?:signed |unsigned )?\w+) (\w+)\[(\d+)\] __attribute__\(\(aligned\(16\)\)\);   /\* (0x[0-9a-f]+) \*/$',
                  open(os.path.join(R, 'data.c')).read(), re.M)
out = ['/* split64.h (tools/mksplit64.py): the 64-bit build\'s split variables (split.h) at their original addresses in',
       '   g_arena - the game\'s address space (src/axis.h, AXIS_64) - as arrays of their types */', '#pragma once']
seen = set()
for typ, name, count, addr in rows:
    if name in seen:
        continue
    seen.add(name)
    out.append('#define %s (*(%s (*)[%s])(g_arena + %s))' % (name, typ, count, addr))
open(os.path.join(R, 'split64.h'), 'w', newline='\n').write('\n'.join(out) + '\n')
print('split64.h: %d variables' % len(seen))
