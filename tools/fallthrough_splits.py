import csv, struct, capstone
D = 'C:/Users/Alexander/Desktop/Axis/'
b = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; n = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
S = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i) for i in range(n)]
def off(va):
    for nm, vs, sva, rs, ro in S:
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
rows = sorted(csv.DictReader(open(D + 'decomp/out/functions.csv')), key=lambda r: int(r['address'], 16))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
for p, r in zip(rows, rows[1:]):
    a, pa = int(r['address'], 16), int(p['address'], 16)
    end = pa + int(p.get('extent') or p['size'])
    if end != a:      # a gap (padding) between them: no fall-through
        continue
    o = off(pa); last = None
    for i in md.disasm(b[o:o + (a - pa)], pa): last = i
    if last and last.address + last.size == a and not (last.mnemonic in ('ret', 'jmp', 'int3', 'hlt') or last.mnemonic.startswith('ret')):
        print('%s %s (callers %s) <- falls in from %s, last %s %s' % (r['address'], r['name'], r['callers'], p['name'], last.mnemonic, last.op_str))
