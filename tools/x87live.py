"""x87live.py: for every call in the game code, the x87 stack depth at the call (values the caller keeps live across
it), found by following each function's control flow. A rebuilt callee called with depth d may use at most 8 - d
x87 registers, or it overwrites the caller's values (the x87 stack wraps around). Prints the callees called with
d > 0 and the deepest d, plus [rebuilt] if tools/done.txt lists them."""
import csv, struct, capstone
from collections import defaultdict
D = 'C:/Users/Alexander/Desktop/Axis/'
b = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
nm, vs, va, rs, ro = struct.unpack_from('<8sIIII', b, pe + 24 + opt)
fs = [(int(r['address'], 16), int(r['size']), r['name']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))]
names = {a: n for a, s, n in fs}
done = {int(x, 16) for x in open(D + 'recomp/tools/done.txt').read().split()}
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
PUSH = {'fld', 'fild', 'fld1', 'fldz', 'fldpi', 'fldl2e', 'fldln2', 'fldlg2', 'fldl2t'}
POP1 = {'fstp', 'fistp', 'fcomp', 'fucomp', 'faddp', 'fsubp', 'fmulp', 'fdivp', 'fsubrp', 'fdivrp', 'ficomp', 'fbstp'}
POP2 = {'fcompp', 'fucompp'}
FTOL = 0x49ec14
deepest = defaultdict(int); where = {}
for a, sz, name in fs:
    if a >= 0x49e000: continue
    o = a - 0x400000 - va + ro
    ins = list(md.disasm(b[o:o + sz], a))
    idx = {i.address: k for k, i in enumerate(ins)}
    depth_at = {}
    work = [(0, 0)]
    while work:
        k, d = work.pop()
        while k < len(ins):
            i = ins[k]
            if i.address in depth_at:
                break
            depth_at[i.address] = d
            m = i.mnemonic
            if m == 'call':
                if i.op_str.startswith('0x'):
                    t = int(i.op_str, 16)
                    if d > 0 and t != FTOL and d > deepest[t]: deepest[t] = d; where[t] = (name, i.address)
                    if t == FTOL: d -= 1
                    elif t in names and names[t] in ('timer_now',) or t == 0x46c100: d += 1   # known ST0 results
            elif m in PUSH: d += 1
            elif m in POP1: d -= 1
            elif m in POP2: d -= 2
            if m.startswith('j') and i.op_str.startswith('0x'):
                t = int(i.op_str, 16)
                if t in idx: work.append((idx[t], d))
                if m == 'jmp': break
            if m.startswith('ret') or (m == 'jmp' and not i.op_str.startswith('0x')): break
            k += 1
rows = sorted(deepest.items(), key=lambda kv: -kv[1])
for t, d in rows:
    print('d=%d %06x %-34s %s  (e.g. from %s at %x)' % (d, t, names.get(t, '?'), '[rebuilt]' if t in done else '', where[t][0], where[t][1]))
