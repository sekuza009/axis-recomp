"""mkthunks64.py <out.s> <elf|coff|macho> [x86_64|arm64]: the 64-bit build's system-call thunks (PORTING.md, stage 6) - for each import
of src/import_list.h a symbol _plat_<name> (the name src/axis.h's IMPORT_FN calls) that jumps through its slot in
g_platSlots (standalone/host64.c), as the 32-bit build's jump through the game's import slots. Weak on ELF and Mach-O:
a platform file that defines plat_<name> itself (src/plat/posix) takes its place; hidden (only the library uses them).
x86-64 (jmp through the slot) or arm64 (the slot's address by page, then br)."""
import os, re, sys

R = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
text = open(os.path.join(R, 'src', 'import_list.h')).read()
names = re.findall(r'X\((\w+), "[^"]*"\)', text[text.index('#define IMPORT_LIST(X)'):])   # (the list itself, in slot order)
out, fmt = sys.argv[1], sys.argv[2]
arch = sys.argv[3] if len(sys.argv) > 3 else 'x86_64'
slots = '_g_platSlots' if fmt == 'macho' else 'g_platSlots'
lines = ['# plat_thunks64.s (tools/mkthunks64.py): the system calls through their slots (standalone/host64.c)', '\t.text']
for i, n in enumerate(names):
    s = '_plat_' + n
    if fmt == 'elf':
        lines += ['\t.weak %s' % s, '\t.hidden %s' % s, '\t.type %s,@function' % s]
    elif fmt == 'macho':
        lines += ['\t.globl %s' % s, '\t.weak_definition %s' % s, '\t.private_extern %s' % s]
    else:
        lines += ['\t.globl %s' % s]
    if arch == 'arm64':
        if fmt == 'macho':
            page, off = '%s@PAGE' % slots, '%s@PAGEOFF' % slots
        else:
            page, off = slots, ':lo12:%s' % slots
        lines += ['\t.p2align 2', '%s:' % s, '\tadrp x16, %s' % page, '\tadd x16, x16, %s' % off,
                  '\tldr x16, [x16, #%d]' % (8 * i), '\tbr x16']
    else:
        lines += ['%s:' % s, '\tjmpq *%s+%d(%%rip)' % (slots, 8 * i)]
open(out, 'w', newline='\n').write('\n'.join(lines) + '\n')
print('%s: %d thunks' % (out, len(names)))
