"""indirect.py done.txt: the indirect calls of the unrebuilt game functions, by kind: "com" = call [reg + off]
after loading a vtable from an object (COM interfaces: DirectPlay, DirectSound, DirectInput...), "table" = call
[reg*4 + table] (function pointer tables), "reg" = call reg, "mem" = call [global]. Prints counts and, per
function, its kinds."""
import sys, csv, struct, capstone
from collections import Counter
D = 'C:/Users/Alexander/Desktop/Axis/'
done = {int(x, 16) for x in open(sys.argv[1]).read().split()}
b = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; n = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
secs = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i) for i in range(n)]
def off(va):
    for nm, vs, sva, rs, ro in secs:
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
tot = Counter(); per = []
for r in csv.DictReader(open(D + 'decomp/out/functions.csv')):
    a = int(r['address'], 16); sz = int(r['size'])
    if a >= 0x49e000 or a in done: continue
    kinds = Counter()
    for i in md.disasm(b[off(a):off(a) + sz], a):
        if i.mnemonic != 'call': continue
        op = i.operands[0]
        if op.type == capstone.x86.X86_OP_REG: kinds['reg'] += 1
        elif op.type == capstone.x86.X86_OP_MEM:
            if not op.mem.base and not op.mem.index:
                if not (0x4a9000 <= op.mem.disp < 0x4a9400): kinds['mem'] += 1
            elif op.mem.index: kinds['table'] += 1
            else: kinds['com'] += 1
    if kinds:
        per.append((r['name'], a, dict(kinds))); tot.update(kinds)
print(tot, len(per))
for nm, a, k in sorted(per, key=lambda x: -sum(x[2].values()))[:int(sys.argv[2]) if len(sys.argv) > 2 else 40]:
    print('%06x %-36s %s' % (a, nm, k))
