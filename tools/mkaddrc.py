"""mkaddrc.py: src/addr_consts.h - every name the game's code takes the address of (ADDR(name), OBJ(name),
ADDR_AT(name, i)) with its original address as a constant, ADDRC_<name>. The 64-bit build's ADDR / OBJ are these
(src/axis.h): there an address is the original's number in g_arena, so a table of addresses stays a compile-time
constant as in the 32-bit builds. The values come from the harness's view of the names (src/ without AXIS_DIRECT, where
every name is at its original address): a small 32-bit program prints them (zig cc, run here)."""
import os, re, subprocess, sys, tempfile

R = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
names = {}
for d, _, fs in os.walk(os.path.join(R, 'src')):
    for f in fs:
        if f.endswith(('.c', '.h')) and f != 'addr_consts.h':
            t = open(os.path.join(d, f), encoding='latin-1').read()
            for m in re.finditer(r'\b(ADDR|OBJ|ADDR_AT)\(\s*([A-Za-z_]\w*)\s*[,)]', t):
                if m.group(2) != 'name':
                    names.setdefault(m.group(2), set()).add('ADDR' if m.group(1) == 'ADDR' else 'OBJ')
tmp = tempfile.mkdtemp()
src = os.path.join(tmp, 'addrc.c')
with open(src, 'w') as f:
    f.write('#include <stdio.h>\n#include "game.h"\nint main(void)\n{\n')
    for n in sorted(names):
        # (OBJ: an array / buffer's address; ADDR: a variable's)
        f.write('\tprintf("#define ADDRC_%s 0x%%xu\\n", (unsigned)%s(%s));\n' % (n, 'OBJ' if 'OBJ' in names[n] and 'ADDR' not in names[n] else 'ADDR', n))
    f.write('\treturn 0;\n}\n')
exe = os.path.join(tmp, 'addrc.exe')
subprocess.check_call([sys.executable, '-m', 'ziglang', 'cc', '-target', 'x86-windows-gnu', '-w', '-I', os.path.join(R, 'src'),
                       '-o', exe, src])
out = subprocess.check_output([exe]).decode()
with open(os.path.join(R, 'src', 'addr_consts.h'), 'w', newline='\n') as f:
    f.write('/* addr_consts.h (tools/mkaddrc.py): the original address of each name whose address the code takes - the 64-bit\n'
            '   build\'s ADDR / OBJ (src/axis.h) */\n#pragma once\n')
    f.write(out.replace('\r\n', '\n'))
print('addr_consts.h: %d names' % len(names))
