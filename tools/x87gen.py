"""x87gen.py <start> <end> reg=name ...: translate a straight-line run of x87 code (fld/fst/fstp/fmul/fadd/fsub/
fsubr/fdiv/fdivr with float memory operands or stack registers, the p-forms, fchs, fxch, fld st(i)) into C that keeps
the original's operand order: a float memory operand stays a memory operand (x87_mulm/addm/subm/subrm/divm/divrm),
"fld m" is LD(), and every store is emitted where the original stores (outputs may overlap inputs).
Memory operands [reg + off] are written name[off / 4] using the reg=name pairs (e.g. eax=a ecx=b edx=out).
Integer instructions in the range are ignored (check them by hand); a jump or call stops the translation."""
import sys, csv, struct, capstone
D = 'C:/Users/Alexander/Desktop/Axis/'
b = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; n = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
S = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i) for i in range(n)]
def off(va):
    for nm, vs, sva, rs, ro in S:
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
start, end = int(sys.argv[1], 16), int(sys.argv[2], 16)
names = dict(a.split('=') for a in sys.argv[3:])
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
st = []                                   # x87 stack, st[0] = top, C expressions (long double)
out = []
def mem(ins, op):
    m = op.mem
    assert m.index == 0 and m.base != 0, ins.op_str
    r = ins.reg_name(m.base)
    assert r in names, 'no name for ' + r
    assert m.disp % 4 == 0, ins.op_str
    return '%s[%d]' % (names[r], m.disp // 4)
def sti(op_str):
    return int(op_str.split('(')[1].split(')')[0]) if '(' in op_str else 0
MEMOP = {'fmul': 'x87_mulm', 'fadd': 'x87_addm', 'fsub': 'x87_subm', 'fsubr': 'x87_subrm', 'fdiv': 'x87_divm', 'fdivr': 'x87_divrm'}
BIN = {'fmul': '*', 'fadd': '+', 'fsub': '-', 'fdiv': '/'}
o = off(start)
for ins in md.disasm(b[o:o + (end - start)], start):
    mn = ins.mnemonic; ops = ins.operands
    if mn.startswith('j') or mn == 'call' or mn.startswith('ret'):
        out.append('	/* stopped at %x: %s %s */' % (ins.address, mn, ins.op_str)); break
    if not mn.startswith('f'): continue
    is_mem = ops and ops[-1].type == capstone.x86.X86_OP_MEM
    if is_mem: assert ins.op_str.startswith('dword'), '%x %s %s (only float memory operands)' % (ins.address, mn, ins.op_str)
    if mn == 'fld':
        st.insert(0, 'LD(%s)' % mem(ins, ops[0]) if is_mem else st[sti(ins.op_str)])
    elif mn in ('fst', 'fstp'):
        if is_mem: out.append('\t%s = (float)(%s);' % (mem(ins, ops[0]), st[0]))
        else: st[sti(ins.op_str)] = st[0]
        if mn == 'fstp': st.pop(0)
    elif mn in MEMOP and is_mem:
        st[0] = '%s(%s, &%s)' % (MEMOP[mn], st[0], mem(ins, ops[0]))
    elif mn in ('fmul', 'fadd', 'fsub', 'fsubr', 'fdiv', 'fdivr') or mn in ('fmulp', 'faddp', 'fsubp', 'fsubrp', 'fdivp', 'fdivrp'):
        p = mn.endswith('p'); base = mn[:-1] if p else mn
        regs = [sti(x) for x in ins.op_str.split(',')] if ins.op_str else ([1, 0] if p else None)
        if p and len(regs) == 1: regs = [regs[0], 0]
        if not p and len(regs) == 1: regs = [0, regs[0]]
        d, s_ = regs                      # st(d) = st(d) op st(s)  (Intel order)
        rev = base.endswith('r'); opc = BIN[base.rstrip('r')]
        x, y = (st[s_], st[d]) if rev else (st[d], st[s_])
        st[d] = '(%s %s %s)' % (x, opc, y)
        if p: st.pop(0)
    elif mn == 'fchs': st[0] = '(-%s)' % st[0]
    elif mn == 'fxch':
        i = sti(ins.op_str) or 1; st[0], st[i] = st[i], st[0]
    else:
        sys.exit('unhandled %x: %s %s' % (ins.address, mn, ins.op_str))
print('\n'.join(out))
if st: print('\t/* left on the x87 stack: %s */' % ', '.join(st))
