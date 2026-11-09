"""sym64.py <elf> <addr>...: the function each address is in (an ELF's symbol table: the 64-bit test program, static)"""
import struct, sys
d = open(sys.argv[1], 'rb').read()
shoff, = struct.unpack_from('<Q', d, 0x28)
shentsize, shnum, shstrndx = struct.unpack_from('<HHH', d, 0x3a)
secs = [struct.unpack_from('<IIQQQQIIQQ', d, shoff + i * shentsize) for i in range(shnum)]
syms = []
for s in secs:
    if s[1] == 2:   # SHT_SYMTAB
        strtab = secs[s[6]]
        for k in range(s[5] // 24):
            name, info, other, shndx, value, size = struct.unpack_from('<IBBHQQ', d, s[4] + k * 24)
            if info & 0xf == 2 and value:   # functions
                n = d[strtab[4] + name:d.index(b'\0', strtab[4] + name)].decode()
                syms.append((value, size, n))
syms.sort()
for a in sys.argv[2:]:
    x = int(a, 16)
    best = None
    for v, sz, n in syms:
        if v <= x:
            best = (v, sz, n)
        else:
            break
    print('%s  %s+0x%x' % (a, best[2], x - best[0]) if best else a + '  ?')
