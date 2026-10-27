"""lift.py <out.c> <entry-addr> [<callee-addr> ...] [+<native-addr> ...] [^<native-addr returning ST0> ...] [@<call site the patch DLL retargets> ...] [%<addr>=<patched bytes> ...] [&<cave lo>-<hi> ...] [-- <lifted-elsewhere-addr> ...]: translate whole functions instruction by instruction into C that
runs them on an emulated machine (struct X86: integer registers, flags, the stack, the x87 register stack as long
double, the FPU condition bits). Bit-exact by construction for the supported instructions:
  - float memory operands stay memory operands (x87_ldm/mulm/addm/subm/subrm/divm/divrm from recomp.c);
  - every store happens where the original stores it;
  - compares set C0/C2/C3 exactly as fcom does (unordered = all three), fnstsw copies them into AX.
Each listed address becomes  static void lift_<addr>(X86 *m);  a call to a listed address calls that function (the
return address is pushed and popped like the real one, so "ret N" cleans up the same way). Calling an unlisted
address is an error. The emitted file expects recomp.c's helpers (x87_* and LD) to be defined first.
Unsupported instructions stop the tool with the address, so nothing is silently skipped."""
import sys, os, csv, struct, capstone
TRACE = os.environ.get('LIFT_TRACE') == '1'   # emit TR(addr) before every instruction (debugging against a single-step trace)
from capstone import x86 as X
D = 'C:/Users/Alexander/Desktop/Axis/'
img = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', img, 0x3c)[0]; n = struct.unpack_from('<H', img, pe + 6)[0]; opt = struct.unpack_from('<H', img, pe + 20)[0]
SECS = [struct.unpack_from('<8sIIII', img, pe + 24 + opt + 40 * i) for i in range(n)]
def foff(va):
    for nm, vs, sva, rs, ro in SECS:
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
SIZES = {int(r['address'], 16): int(r['size']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))}
NAMES = {int(r['address'], 16): r['name'] for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))}

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
R32 = ['eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi']
R8 = {'al': ('eax', 0), 'cl': ('ecx', 0), 'dl': ('edx', 0), 'bl': ('ebx', 0),
      'ah': ('eax', 8), 'ch': ('ecx', 8), 'dh': ('edx', 8), 'bh': ('ebx', 8)}
R16 = {'ax': 'eax', 'cx': 'ecx', 'dx': 'edx', 'bx': 'ebx', 'si': 'esi', 'di': 'edi', 'bp': 'ebp'}

def addr_expr(ins, op):
    mm = op.mem
    if mm.segment:
        # fs:[0] = the SEH chain head: MSVC links its exception frame there and unlinks it on return. Lifted code
        # keeps it in g_lift_fs0 (no C++ exception is ever thrown through these functions)
        assert ins.reg_name(mm.segment) == 'fs' and not mm.base and not mm.index and mm.disp == 0, 'segment at %x' % ins.address
        return '(DWORD)&g_lift_fs0'
    parts = []
    if mm.base: parts.append('m->' + ins.reg_name(mm.base))
    if mm.index: parts.append('m->%s*%d' % (ins.reg_name(mm.index), mm.scale))
    parts.append('0x%xu' % (mm.disp & 0xffffffff))
    return '(DWORD)(' + ' + '.join(parts) + ')'

def rd(ins, op, size=None):
    """C expression reading an integer operand (as DWORD, zero-extended for 8/16 bit)"""
    if op.type == X.X86_OP_IMM: return '0x%xu' % (op.imm & 0xffffffff)
    if op.type == X.X86_OP_REG:
        r = ins.reg_name(op.reg)
        if r in R32: return 'm->' + r
        if r in R8: b, sh = R8[r]; return '((m->%s >> %d) & 0xff)' % (b, sh)
        if r in R16: return '(m->%s & 0xffff)' % R16[r]
        raise SystemExit('register %s at %x' % (r, ins.address))
    a = addr_expr(ins, op)
    return {4: 'M32(%s)' % a, 2: 'M16(%s)' % a, 1: 'M8(%s)' % a}[op.size]

def wr(ins, op, val):
    if op.type == X.X86_OP_REG:
        r = ins.reg_name(op.reg)
        if r in R32: return 'm->%s = %s;' % (r, val)
        if r in R8: b, sh = R8[r]; return 'm->%s = (m->%s & ~(0xffu << %d)) | (((%s) & 0xff) << %d);' % (b, b, sh, val, sh)
        if r in R16: return 'm->%s = (m->%s & 0xffff0000u) | ((%s) & 0xffff);' % (R16[r], R16[r], val)
        raise SystemExit('register %s at %x' % (r, ins.address))
    a = addr_expr(ins, op)
    return {4: 'M32(%s) = %s;' % (a, val), 2: 'M16(%s) = (WORD)(%s);' % (a, val), 1: 'M8(%s) = (BYTE)(%s);' % (a, val)}[op.size]

def mask(op):
    return {4: '0xffffffffu', 2: '0xffffu', 1: '0xffu'}[op.size]

def sti(ins, k):
    return ins.operands[k].reg - X.X86_REG_ST0

JT = {}   # address of a "jmp [reg*4 + table]" -> (index register, [targets])
def jump_table(insns, k, start, size):
    # MSVC switch: "cmp r, N; ja default; jmp [r*4 + table]" (the index may also come from a byte table, then no
    # bound is visible): N + 1 entries, else entries while they point into the function (at most 256)
    i = insns[k]; op = i.operands[0]
    reg = i.reg_name(op.mem.index); n = None
    for j in range(k - 1, max(k - 4, -1), -1):
        p = insns[j]
        if p.mnemonic == 'cmp' and p.operands[0].type == X.X86_OP_REG and p.reg_name(p.operands[0].reg) == reg and p.operands[1].type == X.X86_OP_IMM:
            n = p.operands[1].imm + 1; break
        if p.mnemonic == 'cmp' and p.operands[0].type == X.X86_OP_REG and p.reg_name(p.operands[0].reg) == reg and p.operands[1].type == X.X86_OP_REG:
            # "mov r2, N ... cmp r, r2; ja default" (profile_processInput): the bound from the last mov to r2
            r2 = p.reg_name(p.operands[1].reg)
            for q in reversed(insns[max(j - 40, 0):j]):
                if q.operands and q.operands[0].type == X.X86_OP_REG and q.reg_name(q.operands[0].reg) == r2:
                    if q.mnemonic == 'mov' and q.operands[1].type == X.X86_OP_IMM: n = q.operands[1].imm + 1
                    break
            break
    out = []
    for e in range(n if n is not None else 256):
        t = struct.unpack_from('<I', img, foff(op.mem.disp + 4 * e))[0]
        if not (start <= t < start + size):
            # with a known bound, an entry may be another function: a tail call (emitted by stmt)
            assert n is None or t in SIZES, 'jump table entry outside the function at %x' % i.address
            if n is None: break
        out.append(t)
    return reg, out

def decode(start, size):
    # the function's instructions, skipping jump tables that lie inside it (a table right after its "jmp [r*4 +
    # table]", with code after it again: profile_processInput); bounded tables only
    insns, pos, end, skip = [], start, start + size, {}
    while pos < end:
        if pos in skip: pos = skip[pos]; continue
        i = next(md.disasm(img[foff(pos):foff(pos) + 16], pos, 1), None)
        if i is None or i.address + i.size > end: break
        insns.append(i); pos = i.address + i.size
        if i.mnemonic == 'jmp' and i.operands[0].type == X.X86_OP_MEM and not i.operands[0].mem.base and i.operands[0].mem.index and i.operands[0].mem.scale == 4:
            tb = i.operands[0].mem.disp
            if start <= tb < end:
                reg, ts = jump_table(insns, len(insns) - 1, start, size)
                if ts: skip[tb] = tb + 4 * len(ts)
    return insns

def is_iat(op):
    return op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index and 0x4a9000 <= op.mem.disp < 0x4a9400

CUR = [0]
def lift_function(start, callees, out):
    CUR[0] = start
    size = SIZES[start]; o = foff(start)
    insns = decode(start, size)
    while insns and insns[-1].mnemonic in ('nop', 'int3'): insns.pop()     # alignment padding
    noreturn = insns[-1].mnemonic == 'call'     # ends in a call that does not return (exit, sys_fatalError ...)
    last = insns[-1].mnemonic
    assert last.startswith('ret') or last == 'jmp' or noreturn, 'function at %x does not end in ret/jmp (%s): its body continues past functions.csv' % (start, last)
    def inside(t): return start <= t < start + size or any(lo <= t < hi for lo, hi in CAVES)
    for lo, hi in CAVES:            # cave code after the body: reached only by jumps, it ends in a jump or ret
        ci = decode(lo, hi - lo)
        assert ci[-1].mnemonic == 'jmp' or ci[-1].mnemonic.startswith('ret'), 'cave %x ends in %s' % (lo, ci[-1].mnemonic)
        insns = insns + ci
    targets = set()
    for k, i in enumerate(insns):
        if i.mnemonic == 'jmp' and i.operands[0].type == X.X86_OP_MEM and not i.operands[0].mem.base and i.operands[0].mem.index and i.operands[0].mem.scale == 4:
            JT[i.address] = jump_table(insns, k, start, size)
            targets.update(t for t in JT[i.address][1] if inside(t))
            continue
        if i.mnemonic.startswith('j'):
            t = i.operands[0]
            if is_iat(t): continue          # tail call through the IAT (see stmt)
            assert t.type == X.X86_OP_IMM, 'indirect jump at %x' % i.address
            if not inside(t.imm) and i.mnemonic == 'jmp' and t.imm in SIZES: continue   # tail call
            assert inside(t.imm), 'jump out of the function at %x' % i.address
            targets.add(t.imm)
    alts = {}
    for a, pat in ALT.items():
        if not inside(a): continue
        code = bytes(0 if b is None else b for b in pat)
        pins = list(md.disasm(code, a))
        assert sum(x.size for x in pins) == len(pat), 'patched block at %x does not decode whole' % a
        assert a in [x.address for x in insns] and a + len(pat) in [x.address for x in insns] + [start + size], 'block %x not on instruction bounds' % a
        for x in pins:
            if x.mnemonic == 'call': DYN.add(x.address)
            elif x.mnemonic.startswith('j'):
                assert x.operands[0].type == X.X86_OP_IMM and inside(x.operands[0].imm), 'patched jump at %x' % x.address
                targets.add(x.operands[0].imm)
        if pins[-1].mnemonic not in ('jmp', 'ret'): targets.add(a + len(pat))
        alts[a] = (pat, pins)
    out.append('/* %s (0x%x), lifted by tools/lift.py */' % (NAMES.get(start, ''), start))
    out.append('static void lift_%x(X86 *m)\n{' % start)
    for i in insns:
        if i.address in targets: out.append('L_%x:' % i.address)
        if i.address in alts:
            pat, pins = alts[i.address]
            cond = ' && '.join('M8(0x%xu) == 0x%02x' % (i.address + k, b) for k, b in enumerate(pat) if b is not None)
            out.append('\tif (%s) {\t/* the patch DLL\'s block (%d bytes) */' % (cond, len(pat)))
            for x in pins:
                out.append('\t\t%s\t/* patched %x: %s %s */' % (stmt(x, callees), x.address, x.mnemonic, x.op_str))
            if pins[-1].mnemonic not in ('jmp', 'ret'): out.append('\t\tgoto L_%x;' % (i.address + len(pat)))
            out.append('\t}')
        s = stmt(i, callees)
        if TRACE: s = 'TR(0x%xu); ' % i.address + s
        out.append('\t%s\t/* %x: %s %s */' % (s, i.address, i.mnemonic, i.op_str))
    if noreturn: out.append('\tabort();\t/* the last call does not return */')
    out.append('}\n')

FMEM = {'fmul': 'x87_mulm', 'fadd': 'x87_addm', 'fsub': 'x87_subm', 'fsubr': 'x87_subrm', 'fdiv': 'x87_divm', 'fdivr': 'x87_divrm'}
# library functions called natively from lifted code (real code, real x87): __ftol takes ST0, pops it, returns EDX:EAX
NATIVE = {0x49ec14: '{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }'}
NATIVE_CALLS = set()   # filled from "+<addr>" arguments
NATIVE_FP = set()      # "^<addr>": native calls that return a float in ST0 (pushed onto the emulated x87 stack)
DYN = set()            # "@<call-site>": calls the patch DLL may retarget at run time (rel32 rewritten): the target is
                       # read from the live call instruction, as the patched original would call it
CAVES = []             # "&<lo>-<hi>": code caves the installed exe's functions jump into (0x4a8e20.. at the end of
                       # .text): lifted as part of the function that reaches them (they jump back into it)
ALT = {}               # "%<addr>=<hex bytes, ?? = any>": a block the patch DLL may overwrite with these bytes. The
                       # lifted code tests the live bytes and runs the patched block or the original (a call in
                       # the patched bytes goes to the target read from the live instruction)
FBIN = {'fmul': '*', 'fadd': '+', 'fsub': '-', 'fdiv': '/'}
JCC = {'je': 'm->zf', 'jne': '!m->zf', 'jz': 'm->zf', 'jnz': '!m->zf', 'jl': 'm->sf != m->of', 'jge': 'm->sf == m->of', 'jle': 'm->zf || m->sf != m->of',
       'jg': '!m->zf && m->sf == m->of', 'js': 'm->sf', 'jns': '!m->sf', 'jb': 'm->cf', 'jae': '!m->cf',
       'jbe': 'm->cf || m->zf', 'ja': '!m->cf && !m->zf'}

def stmt(i, callees):
    mn = i.mnemonic; ops = i.operands
    # ---- x87 ----
    if mn in ('fsin', 'fcos'):      # the real instruction on the value (C2, the out-of-range flag, is not kept)
        return '{ long double t_ = ST(0); __asm__("%s" : "+t"(t_)); ST(0) = t_; }' % mn
    if mn == 'fptan':               # ST0 = tan(ST0), then 1.0 pushed (the real instruction)
        return '{ long double t_ = ST(0), one_; __asm__("fptan" : "=t"(one_), "=u"(t_) : "0"(t_)); ST(0) = t_; FPUSH(one_); }'
    if mn == 'fpatan':              # ST1 = atan2(ST1, ST0), pop (the real instruction)
        return '{ long double x_ = ST(0), y_ = ST(1), r_; __asm__("fpatan" : "=t"(r_) : "0"(x_), "u"(y_) : "st(1)"); FPOP(); ST(0) = r_; }'
    if mn.startswith('f'):
        mem = ops and ops[-1].type == X.X86_OP_MEM
        if mem:
            sz = ops[-1].size; a = addr_expr(i, ops[-1])
        if mn == 'fld':
            if mem:
                if sz == 4: return 'FPUSH(x87_ldm((const float *)%s));' % a
                if sz == 8: return 'FPUSH((long double)*(const double *)%s);' % a
                raise SystemExit('fld size %d at %x' % (sz, i.address))
            return '{ long double t = ST(%d); FPUSH(t); }' % sti(i, 0)
        if mn == 'fild' and mem:
            if sz == 4: return 'FPUSH((long double)(int)M32(%s));' % a
            if sz == 2: return 'FPUSH((long double)(short)M16(%s));' % a
            if sz == 8: return 'FPUSH((long double)*(const long long *)%s);' % a
        if mn in ('fst', 'fstp'):
            pop = ' FPOP();' if mn == 'fstp' else ''
            if mem:
                if sz == 4: return 'MF(%s) = (float)ST(0);%s' % (a, pop)
                if sz == 8: return 'MDBL(%s) = (double)ST(0);%s' % (a, pop)
                raise SystemExit('fst size at %x' % i.address)
            return 'ST(%d) = ST(0);%s' % (sti(i, 0), pop)
        if mn in FMEM and mem and sz == 8:      # double operand: loaded exactly into 80 bits
            rev = mn.endswith('r'); opc = FBIN[mn[:-1] if rev else mn]
            d = '(long double)*(const double *)%s' % a
            return 'ST(0) = %s;' % ('%s %s ST(0)' % (d, opc) if rev else 'ST(0) %s %s' % (opc, d))
        if mn in ('fimul', 'fiadd', 'fisub', 'fisubr', 'fidiv', 'fidivr') and mem:
            base = 'f' + mn[2:]; rev = base.endswith('r'); opc = FBIN[base[:-1] if rev else base]
            v = '(long double)(int)M32(%s)' % a if sz == 4 else '(long double)(short)M16(%s)' % a
            return 'ST(0) = %s;' % ('%s %s ST(0)' % (v, opc) if rev else 'ST(0) %s %s' % (opc, v))
        if mn in FMEM and mem:
            assert sz == 4, 'non-float memory operand at %x' % i.address
            return 'ST(0) = %s(ST(0), (const float *)%s);' % (FMEM[mn], a)
        if mn in ('fmul', 'fadd', 'fsub', 'fsubr', 'fdiv', 'fdivr', 'fmulp', 'faddp', 'fsubp', 'fsubrp', 'fdivp', 'fdivrp'):
            # Intel semantics: the first operand is the destination; "fop st(k)" = st(0) op= st(k);
            # "fopp st(k)" / "fopp" = st(k or 1) op= st(0), then pop; the r-forms swap the operands
            p = mn.endswith('p'); base = mn[:-1] if p else mn
            regs = [sti(i, k) for k in range(len(ops))]
            if len(regs) == 2: d, s_ = regs
            elif p: d, s_ = (regs[0] if regs else 1), 0
            else: d, s_ = 0, regs[0]
            rev = base.endswith('r'); op = FBIN[base[:-1] if rev else base]
            x, y = ('ST(%d)' % s_, 'ST(%d)' % d) if rev else ('ST(%d)' % d, 'ST(%d)' % s_)
            return 'ST(%d) = %s %s %s;%s' % (d, x, op, y, ' FPOP();' if p else '')
        if mn == 'fchs': return 'ST(0) = -ST(0);'
        if mn == 'fabs': return 'ST(0) = fabsl(ST(0));'
        if mn == 'fsqrt': return '{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }'
        if mn == 'fxch':
            k = max([sti(i, j) for j in range(len(ops))] + [0]) or 1    # capstone lists "fxch st(1)" as (st0, st1)
            return '{ long double t = ST(0); ST(0) = ST(%d); ST(%d) = t; }' % (k, k)
        if mn in ('fcom', 'fcomp', 'fucom', 'fucomp'):
            if mem:
                rhs = {4: '(long double)*(const float *)%s', 8: '(long double)*(const double *)%s'}[sz] % a
            else:
                rhs = 'ST(%d)' % (sti(i, 0) if ops else 1)
            return 'FCOM(ST(0), %s);%s' % (rhs, ' FPOP();' if mn.endswith('p') else '')
        if mn in ('fcompp', 'fucompp'): return 'FCOM(ST(0), ST(1)); FPOP(); FPOP();'
        if mn == 'fnstsw': return 'm->eax = (m->eax & 0xffff0000u) | m->fsw;'
        raise SystemExit('x87 %s %s at %x' % (mn, i.op_str, i.address))
    # ---- integer ----
    if mn == 'mov':
        return wr(i, ops[0], rd(i, ops[1]))
    if mn == 'lea': return wr(i, ops[0], addr_expr(i, ops[1]))
    if mn == 'push': return '{ DWORD v_ = %s; m->esp -= 4; M32(m->esp) = v_; }' % rd(i, ops[0])   # operand read before esp moves
    if mn == 'pop': return '%s m->esp += 4;' % wr(i, ops[0], 'M32(m->esp)')
    if mn == 'pushal':   # eax ecx edx ebx (esp before) ebp esi edi
        return '{ DWORD e_ = m->esp; m->esp -= 32; M32(m->esp + 28) = m->eax; M32(m->esp + 24) = m->ecx; M32(m->esp + 20) = m->edx; ' \
               'M32(m->esp + 16) = m->ebx; M32(m->esp + 12) = e_; M32(m->esp + 8) = m->ebp; M32(m->esp + 4) = m->esi; M32(m->esp) = m->edi; }'
    if mn == 'popal':    # the saved esp is skipped
        return '{ m->edi = M32(m->esp); m->esi = M32(m->esp + 4); m->ebp = M32(m->esp + 8); m->ebx = M32(m->esp + 16); ' \
               'm->edx = M32(m->esp + 20); m->ecx = M32(m->esp + 24); m->eax = M32(m->esp + 28); m->esp += 32; }'
    if mn in ('add', 'sub', 'cmp', 'and', 'or', 'xor', 'test'):
        a, b, mk = rd(i, ops[0]), rd(i, ops[1]), mask(ops[0])
        bits = ops[0].size * 8
        r = {'add': '(a_ + b_) & %s' % mk, 'sub': '(a_ - b_) & %s' % mk, 'cmp': '(a_ - b_) & %s' % mk,
             'and': 'a_ & b_', 'test': 'a_ & b_', 'or': 'a_ | b_', 'xor': 'a_ ^ b_'}[mn]
        s = '{ DWORD a_ = %s, b_ = %s & %s, r_ = %s; FLAGS(r_, %d);' % (a, b, mk, r, bits)
        if mn == 'add': s += ' m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> %d) & 1;' % (bits - 1)
        elif mn in ('sub', 'cmp'): s += ' m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> %d) & 1;' % (bits - 1)
        else: s += ' m->cf = 0; m->of = 0;'
        if mn not in ('cmp', 'test'): s += ' ' + wr(i, ops[0], 'r_')
        return s + ' }'
    if mn in ('inc', 'dec'):
        a, mk, bits = rd(i, ops[0]), mask(ops[0]), ops[0].size * 8
        d = '+' if mn == 'inc' else '-'
        top = '0x%xu' % (1 << (bits - 1))
        of = '(r_ == %s)' % top if mn == 'inc' else '(a_ == %s)' % top
        return '{ DWORD a_ = %s, r_ = (a_ %s 1) & %s; FLAGS(r_, %d); m->of = %s; %s }' % (a, d, mk, bits, of, wr(i, ops[0], 'r_'))
    # string instructions (the direction flag is clear in MSVC code)
    SZ = {'b': (1, 'M8', 'BYTE', '0xffu'), 'w': (2, 'M16', 'WORD', '0xffffu'), 'd': (4, 'M32', 'DWORD', '0xffffffffu')}
    base = mn.split()[-1]; rep = mn.split()[0] if ' ' in mn else ''
    if base[:-1] in ('stos', 'movs', 'scas', 'cmps', 'lods') and base[-1] in SZ:
        n, M, T, mk = SZ[base[-1]]
        acc = {'b': '(m->eax & 0xffu)', 'w': '(m->eax & 0xffffu)', 'd': 'm->eax'}[base[-1]]
        if base.startswith('stos'): one = '%s(m->edi) = (%s)%s; m->edi += %d;' % (M, T, acc, n)
        elif base.startswith('movs'): one = '%s(m->edi) = %s(m->esi); m->esi += %d; m->edi += %d;' % (M, M, n, n)
        elif base.startswith('lods'): one = wr(i, i.operands[0], '%s(m->esi)' % M) + ' m->esi += %d;' % n
        elif base.startswith('scas'):
            one = ('{ DWORD a_ = %s, b_ = %s(m->edi), r_ = (a_ - b_) & %s; FLAGS(r_, %d); m->cf = a_ < b_; '
                   'm->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> %d) & 1); m->edi += %d; }' % (acc, M, mk, n * 8, n * 8 - 1, n))
        else:
            one = ('{ DWORD a_ = %s(m->esi), b_ = %s(m->edi), r_ = (a_ - b_) & %s; FLAGS(r_, %d); m->cf = a_ < b_; '
                   'm->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> %d) & 1); m->esi += %d; m->edi += %d; }' % (M, M, mk, n * 8, n * 8 - 1, n, n))
        if not rep: return one
        if rep == 'rep': return 'while (m->ecx) { %s m->ecx--; }' % one
        stop = 'm->zf' if rep in ('repne', 'repnz') else '!m->zf'   # repne stops on equal, repe on different
        return 'while (m->ecx) { %s m->ecx--; if (%s) break; }' % (one, stop)
    if mn in ('adc', 'sbb'):
        assert ops[0].size == 4, 'adc/sbb size at %x' % i.address
        a, b = rd(i, ops[0]), rd(i, ops[1])
        if mn == 'adc':
            body = ('unsigned long long w_ = (unsigned long long)a_ + b_ + c0_; DWORD r_ = (DWORD)w_; m->cf = (int)(w_ >> 32); '
                    'm->of = (int)(((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1);')
        else:
            body = ('DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; '
                    'm->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1);')
        return '{ DWORD a_ = %s, b_ = %s, c0_ = (DWORD)m->cf; %s FLAGS(r_, 32); %s }' % (a, b, body, wr(i, ops[0], 'r_'))
    if mn == 'neg':
        a = rd(i, ops[0]); mk = mask(ops[0]); bits = ops[0].size * 8
        return ('{ DWORD a_ = %s, r_ = (0u - a_) & %s; FLAGS(r_, %d); m->cf = a_ != 0; m->of = r_ == (1u << %d); %s }'
                % (a, mk, bits, bits - 1, wr(i, ops[0], 'r_')))
    if mn == 'not': return wr(i, ops[0], '~%s' % rd(i, ops[0]))
    if mn in ('shl', 'sal', 'shr', 'sar'):
        bits = ops[0].size * 8; mk = mask(ops[0])
        a = rd(i, ops[0]); c = rd(i, ops[1]) if len(ops) > 1 else '1u'
        sx = {32: '(int)a_', 16: '(int)(short)a_', 8: '(int)(signed char)a_'}[bits]
        if mn in ('shl', 'sal'): r, cf = '(a_ << c_) & %s' % mk, '(a_ >> (%d - c_)) & 1' % bits
        elif mn == 'shr': r, cf = 'a_ >> c_', '(a_ >> (c_ - 1)) & 1'
        else: r, cf = '(DWORD)(%s >> c_) & %s' % (sx, mk), '((DWORD)(%s >> (c_ - 1))) & 1' % sx
        # x86 masks the count to 5 bits; a zero count changes nothing (not even the flags)
        return ('{ DWORD a_ = %s, c_ = (%s) & 31; if (c_) { DWORD r_ = %s; m->cf = (int)(%s); FLAGS(r_, %d); m->of = 0; %s } }'
                % (a, c, r, cf, bits, wr(i, ops[0], 'r_')))
    if mn == 'imul' and len(ops) in (2, 3):
        a = rd(i, ops[1] if len(ops) == 3 else ops[0]); b = rd(i, ops[2] if len(ops) == 3 else ops[1])
        return ('{ long long p_ = (long long)(int)%s * (int)%s; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); '
                'm->cf = m->of = p_ != (long long)(int)r_; %s }' % (a, b, wr(i, ops[0], 'r_')))
    if mn in ('imul', 'mul') and len(ops) == 1:
        # edx:eax = eax * r/m32 (signed / unsigned); CF = OF = the high half is significant (SF/ZF are undefined)
        assert ops[0].size == 4
        if mn == 'imul':
            return ('{ long long p_ = (long long)(int)m->eax * (int)%s; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); '
                    'm->cf = m->of = p_ != (long long)(int)m->eax; }' % rd(i, ops[0]))
        return ('{ unsigned long long p_ = (unsigned long long)m->eax * %s; m->eax = (DWORD)p_; m->edx = (DWORD)(p_ >> 32); '
                'm->cf = m->of = m->edx != 0; }' % rd(i, ops[0]))
    if mn == 'cdq': return 'm->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;'
    if mn == 'nop': return ';'
    if mn in ('fsin', 'fcos'):      # the real instruction on the value (C2, the out-of-range flag, is not kept)
        return '{ long double t_ = ST(0); __asm__("%s" : "+t"(t_)); ST(0) = t_; }' % mn
    if mn == 'div':
        assert ops[0].size == 4
        return '{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = %s; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ %% d_); }' % rd(i, ops[0])
    if mn == 'idiv':
        assert ops[0].size == 4
        return '{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)%s; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ %% d_); }' % rd(i, ops[0])
    if mn.startswith('set') and ('j' + mn[3:]) in JCC: return wr(i, ops[0], '(%s) ? 1u : 0u' % JCC['j' + mn[3:]])
    if mn in ('movzx', 'movsx'):
        v = rd(i, ops[1])
        if mn == 'movsx': v = '(DWORD)(int)(%s)(%s)' % ({1: 'signed char', 2: 'short'}[ops[1].size], v)
        return wr(i, ops[0], v)
    if mn == 'jmp' and i.address in JT:
        reg, ts = JT[i.address]
        def case(t):   # inside: a jump; another function: a tail call, as for "jmp func" below
            if CUR[0] <= t < CUR[0] + SIZES[CUR[0]]: return 'goto L_%x;' % t
            if t in NATIVE_CALLS: return 'native_call(m, 0x%xu); return;' % t
            if t not in callees: raise SystemExit('tail call to unlisted %x at %x' % (t, i.address))
            return 'lift_%x(m); return;' % t
        return 'switch (m->%s) { %s default: abort(); }' % (reg, ' '.join('case %d: %s' % (k, case(t)) for k, t in enumerate(ts)))
    if mn == 'jmp' and is_iat(ops[0]):
        # tail call through the IAT: the import returns straight to our caller (native_call steps over the return
        # address slot and whatever the callee pops, as a ret would)
        return 'native_call(m, M32(0x%xu)); return;' % ops[0].mem.disp
    if mn == 'jmp' and ops[0].imm in SIZES and ops[0].imm != CUR[0]:
        # tail call to another function: it returns straight to our caller
        t = ops[0].imm
        if t in NATIVE_CALLS: return 'native_call(m, 0x%xu); return;' % t
        if t not in callees: raise SystemExit('tail call to unlisted %x at %x' % (t, i.address))
        return 'lift_%x(m); return;' % t
    if mn == 'jmp': return 'goto L_%x;' % ops[0].imm
    if mn in JCC: return 'if (%s) goto L_%x;' % (JCC[mn], ops[0].imm)
    if mn == 'call':
        if ops[0].type == X.X86_OP_MEM and not ops[0].mem.base and not ops[0].mem.index and 0x4a9000 <= ops[0].mem.disp < 0x4a9400:
            # an import (call through the IAT slot): native call to whatever the slot holds when it runs
            return 'm->esp -= 4; M32(m->esp) = 0x%xu; native_call(m, M32(0x%xu));' % (i.address + i.size, ops[0].mem.disp)
        if ops[0].type != X.X86_OP_IMM:
            # call reg (MSVC keeps an import's address in a register: mov esi, [glVertex2i] ... call esi), call [reg + off]
            # (COM methods) or call [global]: a native call to whatever address the operand holds when it runs
            return 'm->esp -= 4; M32(m->esp) = 0x%xu; native_call(m, %s);' % (i.address + i.size, rd(i, ops[0]))
        t = ops[0].imm
        if i.address in DYN:
            r = i.address + i.size
            return 'm->esp -= 4; M32(m->esp) = 0x%xu; native_call(m, 0x%xu + M32(0x%xu));	/* 0x%x unless the patch DLL retargets it */' % (r, r, r - 4, t)
        if t in NATIVE: return NATIVE[t]
        if t in NATIVE_FP:
            return 'm->esp -= 4; M32(m->esp) = 0x%xu; { long double r_ = native_call_fp(m, 0x%xu); FPUSH(r_); }' % (i.address + i.size, t)
        if t in NATIVE_CALLS and t >= 0xb00000:
            # patch code (the exe's .axnet section): its address differs between the installed exe and the test
            # exe (the embedded patch DLL builds differ), so take the target from the original call instruction
            r = i.address + i.size
            return 'm->esp -= 4; M32(m->esp) = 0x%xu; native_call(m, 0x%xu + M32(0x%xu));\t/* patch code (0x%x here) */' % (r, r, r - 4, t)
        if t in NATIVE_CALLS:      # real code: native_call() runs it on the emulated stack (x87 stack must be empty)
            return 'm->esp -= 4; M32(m->esp) = 0x%xu; native_call(m, 0x%xu);' % (i.address + i.size, t)
        if t not in callees: raise SystemExit('call to unlisted %x at %x' % (t, i.address))
        return 'm->esp -= 4; M32(m->esp) = 0x%xu; lift_%x(m);' % (i.address + i.size, t)
    if mn == 'ret':
        k = ops[0].imm if ops else 0
        return 'm->esp += 4 + %d; return;' % k
    raise SystemExit('unsupported %s %s at %x' % (mn, i.op_str, i.address))

HEADER = '''/* ---- emulated machine for lifted functions (tools/lift.py) ---- */
typedef struct { DWORD eax, ecx, edx, ebx, esp, ebp, esi, edi; int zf, sf, cf, of; long double fs[8]; int ft; DWORD fsw; } X86;
#ifndef LIFT_FS0_DEFINED
#define LIFT_FS0_DEFINED
static DWORD g_lift_fs0;          /* the emulated fs:[0] (SEH chain head) */
#endif
#define M32(a) (*(DWORD *)(a))
#define M16(a) (*(WORD *)(a))
#define M8(a) (*(BYTE *)(a))
#define MF(a) (*(float *)(a))
#define MDBL(a) (*(double *)(a))
#define ST(i) (m->fs[m->ft - 1 - (i)])
#define FPUSH(v) (m->fs[m->ft++] = (v))
#define FPOP() (m->ft--)
#define FLAGS(r, bits) (m->zf = (r) == 0, m->sf = (int)(((r) >> ((bits) - 1)) & 1))
/* fcom: C0 = less, C3 = equal, all of C0/C2/C3 = unordered (status word bits 8, 10, 14) */
#define FCOM(a, b) do { long double a_ = (a), b_ = (b); \\
	m->fsw = (a_ != a_ || b_ != b_) ? 0x4500u : a_ < b_ ? 0x0100u : a_ == b_ ? 0x4000u : 0; } while (0)
'''

if __name__ == '__main__':
    # lift.py <out.c> <addr>... [-- <addr already lifted in an earlier file>...]
    args = [a for a in sys.argv[2:] if not a.startswith('+') and not a.startswith('^') and not a.startswith('@') and not a.startswith('%') and not a.startswith('&')]; ext = []
    DYN.update(int(a[1:], 16) for a in sys.argv[2:] if a.startswith('@'))
    for a in sys.argv[2:]:
        if a.startswith('&'):
            lo, hi = a[1:].split('-'); CAVES.append((int(lo, 16), int(hi, 16)))
        if a.startswith('%'):
            at, hx = a[1:].split('=')
            ALT[int(at, 16)] = [None if hx[k:k + 2] == '??' else int(hx[k:k + 2], 16) for k in range(0, len(hx), 2)]
    NATIVE_FP.update(int(a[1:], 16) for a in sys.argv[2:] if a.startswith('^'))
    NATIVE_CALLS.update(int(a[1:], 16) for a in sys.argv[2:] if a.startswith('+'))
    later = '--' in args
    if later: ext = [int(a, 16) for a in args[args.index('--') + 1:]]; args = args[:args.index('--')]
    outp = sys.argv[1]; addrs = [int(a, 16) for a in args]
    header = HEADER
    if later:   # an earlier lifted file already defines X86 ("--" marks a later file)
        header = header.replace('typedef struct {', '#if 0 /* X86 comes from the earlier lifted file */\ntypedef struct {')
        header = header.replace(' } X86;', ' } X86;\n#endif')
    out = [header]
    for a in addrs[1:] + addrs[:1]:
        out.append('static void lift_%x(X86 *m);' % a)
    out.append('')
    for a in addrs:
        lift_function(a, set(addrs) | set(ext), out)
    out.append('/* the lifter macros are local to this file (recomp.c has its own ST()) */')
    for name in ('M32', 'M16', 'M8', 'MF', 'MDBL', 'ST', 'FPUSH', 'FPOP', 'FLAGS', 'FCOM'):
        out.append('#undef ' + name)
    open(outp, 'w', newline='\n').write('\n'.join(out) + '\n')
    print('lifted', ', '.join('%x' % a for a in addrs))
