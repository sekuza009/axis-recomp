"""cands3.py done.txt: unrebuilt game functions whose calls all go to rebuilt code or to the "library" (the MSVC CRT at
0x49e000+, import thunks there, and IAT imports). Prints size, address, name and the library functions each one
uses (IAT imports as DLL!name). Library calls stay calls to the original library code in a rebuild."""
import sys, csv, struct, capstone
D = 'C:/Users/Alexander/Desktop/Axis/'
done = {int(x, 16) for x in open(sys.argv[1]).read().split()}
b = open(D + 'recomp/installed.exe', 'rb').read(); ret = open(D + 'decomp/bin/AxisGL.exe', 'rb').read()
def secs(x):
    pe = struct.unpack_from('<I', x, 0x3c)[0]; n = struct.unpack_from('<H', x, pe + 6)[0]; opt = struct.unpack_from('<H', x, pe + 20)[0]
    return [struct.unpack_from('<8sIIII', x, pe + 24 + opt + 40 * i) for i in range(n)]
def off(x, va):
    for nm, vs, sva, rs, ro in secs(x):
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
pe = struct.unpack_from('<I', b, 0x3c)[0]
imp_rva, _ = struct.unpack_from('<II', b, pe + 0x18 + 96 + 8 * 1)
iatname = {}
o = off(b, 0x400000 + imp_rva)
while True:
    oft, ts, fc, nm, ft = struct.unpack_from('<IIIII', b, o)
    if nm == 0: break
    dll = b[off(b, 0x400000 + nm):].split(b'\0')[0].decode().split('.')[0]
    k = 0
    while True:
        thunk = struct.unpack_from('<I', b, off(b, 0x400000 + (oft or ft)) + 4 * k)[0]
        if thunk == 0: break
        fn = '#%d' % (thunk & 0xffff) if thunk & 0x80000000 else b[off(b, 0x400000 + thunk + 2):].split(b'\0')[0].decode()
        iatname[0x400000 + ft + 4 * k] = dll + '!' + fn; k += 1
    o += 20
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
fs = [(int(r['address'], 16), int(r['size']), r['name']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))]
names = {a: n for a, s, n in fs}
for a, sz, name in sorted(fs, key=lambda f: f[1]):
    if a >= 0x49e000 or a in done: continue
    o1, o2 = off(ret, a), off(b, a)
    if o1 is None or o2 is None or ret[o1:o1 + sz] != b[o2:o2 + sz]: continue
    bad = False; libs = set()
    for i in md.disasm(b[o2:o2 + sz], a):
        if i.mnemonic in ('call', 'jmp'):
            op = i.operands[0]
            if op.type == capstone.x86.X86_OP_IMM:
                t = op.imm
                if i.mnemonic == 'jmp' and a <= t < a + sz: continue
                if t in done: continue
                if t >= 0x49e000: libs.add(names.get(t, hex(t))); continue
                bad = True
            elif op.type == capstone.x86.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0 and op.mem.disp in iatname:
                libs.add(iatname[op.mem.disp])
            else: bad = True
        elif i.mnemonic.startswith('j') and i.op_str.startswith('0x'):
            t = int(i.op_str, 16)
            if not a <= t < a + sz and t not in done:
                if t >= 0x49e000: libs.add(names.get(t, hex(t)))
                else: bad = True
    tail = list(md.disasm(b[o2:o2 + sz], a))[-1].mnemonic
    if not (tail.startswith('ret') or tail == 'jmp'): bad = True        # body cut short: it falls through into the next one
    if not bad: print('%5d %06x %-36s %s' % (sz, a, name, ' '.join(sorted(libs))))
