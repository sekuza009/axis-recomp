r"""objcmp.py dirA dirB: compare two builds' COFF objects by their code and data sections only (headers, symbol
tables and .debug* sections left out, as they change with any header edit): prints the objects whose generated
code or data differ"""
import glob, os, struct, sys


def sections(path):
    d = open(path, 'rb').read()
    n = struct.unpack_from('<H', d, 2)[0]
    symptr, nsyms = struct.unpack_from('<II', d, 8)
    strtab = symptr + nsyms * 18   # long section names ("/offset") live in the string table after the symbols
    out = {}
    for i in range(n):
        o = 20 + i * 40
        name = d[o:o + 8].rstrip(b'\0').decode('latin-1')
        if name.startswith('/'):
            s = strtab + int(name[1:])
            name = d[s:d.index(b'\0', s)].decode('latin-1')
        size, ptr = struct.unpack_from('<II', d, o + 16)
        nrel, = struct.unpack_from('<H', d, o + 32)
        relptr, = struct.unpack_from('<I', d, o + 24)
        if name.startswith('.debug') or name.startswith('.llvm'):
            continue
        # (a section without data in the file - .bss - by its size only: its pointer is 0, not its bytes)
        out.setdefault(name, []).append((d[ptr:ptr + size] if ptr else ('zeroed', size), d[relptr:relptr + nrel * 10]))
    return out


a, b = sys.argv[1], sys.argv[2]
bad = 0
for f in sorted(glob.glob(os.path.join(a, '*.o'))):
    g = os.path.join(b, os.path.basename(f))
    sa, sb = sections(f), sections(g)
    if {k: [x[0] for x in v] for k, v in sa.items()} != {k: [x[0] for x in v] for k, v in sb.items()}:
        print('code/data differ:', os.path.basename(f)); bad += 1
print('%d objects compared, %d differ in code or data' % (len(glob.glob(os.path.join(a, '*.o'))), bad))
