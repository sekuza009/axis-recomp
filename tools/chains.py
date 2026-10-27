"""chains.py <addr>: compact listing of a function made of "index -> stride -> load" chains (MSVC strength-reduced
multiplies). Registers holding k*X (X = the last value loaded) are folded, so a load prints as
  [base + idx*stride + off] with idx named after the load that produced it (L1, L2, ...). Other instructions are
printed as they are, with folded registers substituted; register copies of a loaded value are printed too."""
import sys, csv, struct, re, capstone
D = 'C:/Users/Alexander/Desktop/Axis/'
b = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; n = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
S = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i) for i in range(n)]
def off(va):
    for nm, vs, sva, rs, ro in S:
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
sz = {int(r['address'], 16): int(r['size']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))}
a = int(sys.argv[1], 16); o = off(a)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
R = {}            # reg -> (name, k): reg = k * name
nl = [0]
def val(r): return R.get(r)
def mem_str(op, ins):
    m = op.mem; base = ins.reg_name(m.base) if m.base else None; idx = ins.reg_name(m.index) if m.index else None
    parts = []; disp = m.disp
    if base and val(base): nm, k = val(base); parts.append('%s*0x%x' % (nm, k)); base = None
    if idx and val(idx): nm, k = val(idx); parts.append('%s*0x%x' % (nm, k * m.scale)); idx = None
    if base: parts.insert(0, base)
    if idx: parts.append('%s*%d' % (idx, m.scale) if m.scale > 1 else idx)
    parts.append('0x%x' % (disp & 0xffffffff) if disp >= 0 else '-0x%x' % -disp)
    return '[' + ' + '.join(parts) + ']'
for ins in md.disasm(b[o:o + sz[a]], a):
    ops = ins.operands; mn = ins.mnemonic
    dst = ins.reg_name(ops[0].reg) if ops and ops[0].type == capstone.x86.X86_OP_REG else None
    src = ops[1] if len(ops) > 1 else None
    folded = False
    if mn == 'mov' and dst and src.type == capstone.x86.X86_OP_REG and val(ins.reg_name(src.reg)):
        R[dst] = val(ins.reg_name(src.reg)); folded = True
        if R[dst][1] == 1: print('%x  %s = %s   (copy of %s)' % (ins.address, dst, ins.reg_name(src.reg), R[dst][0]))
    elif mn in ('shl',) and dst and val(dst) and src.type == capstone.x86.X86_OP_IMM:
        nm, k = val(dst); R[dst] = (nm, k << src.imm); folded = True
    elif mn in ('add', 'sub') and dst and val(dst) and src.type == capstone.x86.X86_OP_REG and val(ins.reg_name(src.reg)) and val(ins.reg_name(src.reg))[0] == val(dst)[0]:
        nm, k = val(dst); k2 = val(ins.reg_name(src.reg))[1]; R[dst] = (nm, k + k2 if mn == 'add' else k - k2); folded = True
    elif mn == 'lea' and dst and ops[1].mem.disp == 0:
        m = ops[1].mem; bs = ins.reg_name(m.base) if m.base else None; ix = ins.reg_name(m.index) if m.index else None
        vb = val(bs) if bs else ('', 0); vi = val(ix) if ix else ('', 0)
        if (not bs or vb) and (not ix or vi) and (vb or vi):
            nm = (vb or vi)[0]
            if (not vb or vb[0] == nm) and (not vi or vi[0] == nm):
                R[dst] = (nm, (vb[1] if vb else 0) + (vi[1] if vi else 0) * m.scale); folded = True
    if folded: continue
    txt = ins.op_str
    for op in ops:
        if op.type == capstone.x86.X86_OP_MEM:
            txt = re.sub(r'\[[^\]]*\]', mem_str(op, ins), txt, count=1)
    if dst and mn in ('mov', 'movsx', 'movzx') and src.type == capstone.x86.X86_OP_MEM:
        nl[0] += 1; R[dst] = ('L%d' % nl[0], 1); print('%x  L%d = %s %s' % (ins.address, nl[0], mn, txt)); continue
    if dst and mn not in ('cmp', 'test', 'push'): R.pop(dst, None)
    if mn in ('rep stosd', 'repne scasb', 'rep movsd', 'rep movsb'): R.pop('ecx', None); R.pop('edi', None); R.pop('esi', None)
    print('%x  %s %s' % (ins.address, mn, txt))
