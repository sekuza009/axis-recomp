"""mkfn64.py: the 64-bit build's function names and table (PORTING.md, stage 6), from build/fn_syms.h (tools/hooktable.py):

- build/fn_syms64.h: each rebuilt function by its symbol, as fn_syms.h has it for the 32-bit builds - here the plain C
  name (no stdcall decoration), with the platform's label prefix (__USER_LABEL_PREFIX__: none on Linux and Windows
  x64, "_" on macOS);
- build/fn_table64.c: every function the game can hold as a value - FN(name), its original address - with its C
  function, in address order, for fn_ptr (standalone/arena.c); also the jump stubs the data points at (FN_VIA in
  src/data, the compiler's stubs of the original that only jump on), each with the function it jumps to."""
import os, re

R = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
syms = re.findall(r'extern void FN_(\w+)\(void\) __asm__\("_(\w+?)(?:@\d+)?"\);', open(os.path.join(R, 'build', 'fn_syms.h')).read())
addrs = dict((n, int(a, 16)) for n, a in re.findall(r'#define FNADDR_(\w+) (0x[0-9a-f]+)', open(os.path.join(R, 'src', 'fn_addrs.h')).read()))
out = ['/* fn_syms64.h (tools/mkfn64.py): the rebuilt functions by symbol, for the 64-bit build (AXIS_64) */',
       '#define FN64_STR_(x) #x', '#define FN64_STR(x) FN64_STR_(x)']
for n, s in syms:
    assert n == s, (n, s)
    out.append('extern void FN_%s(void) __asm__(FN64_STR(__USER_LABEL_PREFIX__) "%s");' % (n, n))
open(os.path.join(R, 'build', 'fn_syms64.h'), 'w', newline='\n').write('\n'.join(out) + '\n')

table = {}
for n, _ in syms:
    if n in addrs:
        table[addrs[n]] = n
for d in ('data.c', 'rdata.c', 'text_data.c'):
    t = open(os.path.join(R, 'src', 'data', d), encoding='latin-1').read()
    for n, a, stub in re.findall(r'FN_VIA\((\w+), (0x[0-9a-f]+), (0x[0-9a-f]+)\)', t):
        table.setdefault(int(stub, 16), n)
out = ['/* fn_table64.c (tools/mkfn64.py): the functions the game holds as values, by original address (FN in src/axis.h),',
       '   for fn_ptr (standalone/arena.c), in address order */',
       '#include "fn_syms64.h"',
       'typedef struct { unsigned address; void (*fn)(void); } FnEntry;',
       'const FnEntry g_fnTable[] = {']
out += ['\t{ 0x%x, FN_%s },' % (a, n) for a, n in sorted(table.items())]
out += ['};', 'const unsigned g_fnCount = %d;' % len(table)]
open(os.path.join(R, 'build', 'fn_table64.c'), 'w', newline='\n').write('\n'.join(out) + '\n')
print('fn_syms64.h: %d functions; fn_table64.c: %d entries' % (len(syms), len(table)))
