"""mkthunks64.py <out.s> <elf|coff|macho>: the 64-bit build's system-call thunks (PORTING.md, stage 6) - for each import
of src/import_list.h a symbol _plat_<name> (the name src/axis.h's IMPORT_FN calls) that jumps through its slot in
g_platSlots (standalone/host64.c), as the 32-bit build's jump through the game's import slots. Weak on ELF and Mach-O:
a platform file that defines plat_<name> itself (src/plat/posix) takes its place. x86-64."""
import os, re, sys

R = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
text = open(os.path.join(R, 'src', 'import_list.h')).read()
names = re.findall(r'X\((\w+), "[^"]*"\)', text[text.index('#define IMPORT_LIST(X)'):])   # (the list itself, in slot order)
out, fmt = sys.argv[1], sys.argv[2]
slots = '_g_platSlots' if fmt == 'macho' else 'g_platSlots'
lines = ['# plat_thunks64.s (tools/mkthunks64.py): the system calls through their slots (standalone/host64.c)', '\t.text']
for i, n in enumerate(names):
    s = '_plat_' + n
    if fmt == 'elf':
        lines += ['\t.weak %s' % s, '\t.type %s,@function' % s]
    elif fmt == 'macho':
        lines += ['\t.globl %s' % s, '\t.weak_definition %s' % s]
    else:
        lines += ['\t.globl %s' % s]
    lines += ['%s:' % s, '\tjmpq *%s+%d(%%rip)' % (slots, 8 * i)]
open(out, 'w', newline='\n').write('\n'.join(lines) + '\n')
print('%s: %d thunks' % (out, len(names)))
