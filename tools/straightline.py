"""straightline.py addr... : symbolically run branch-free functions made only of constant stores and global copies,
and print the writes they make to absolute addresses, as C table rows { addr, size, value } or { addr, 4, G(src) }
(G(src) = the value src held when the function started; it is always read before any write to src).
Supports mov/xor/or/and/push/pop/lea/rep stosd/stosw/stosb/inc/dec/add/sub on registers and memory, with all
register values known constants. Stack writes are tracked (so bytes assembled in a local and copied out work) but
not reported. Stops at ret; fails loudly on anything else (branches, calls, unknown values)."""
import sys, struct, csv, capstone
from capstone import x86

D = 'C:/Users/Alexander/Desktop/Axis/'
b = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; n = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
S = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i) for i in range(n)]
def off(va):
    for nm, vs, sva, rs, ro in S:
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
sizes = {int(r['address'], 16): int(r['size']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))}
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True

R32 = ['eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi']
SUB = {'al': ('eax', 0, 8), 'cl': ('ecx', 0, 8), 'dl': ('edx', 0, 8), 'bl': ('ebx', 0, 8),
       'ah': ('eax', 8, 8), 'ch': ('ecx', 8, 8), 'dh': ('edx', 8, 8), 'bh': ('ebx', 8, 8),
       'ax': ('eax', 0, 16), 'cx': ('ecx', 0, 16), 'dx': ('edx', 0, 16), 'bx': ('ebx', 0, 16),
       'si': ('esi', 0, 16), 'di': ('edi', 0, 16), 'bp': ('ebp', 0, 16)}
STACK = 0x10000000

def run(addr):
    reg = {r: None for r in R32}; reg['esp'] = STACK
    mem = {}                      # byte address -> value (stack + globals)
    out = []                      # (addr, size, value) for non-stack writes, in order
    def rget(name):
        if name in reg:
            if reg[name] is None: raise ValueError('unknown ' + name)
            return reg[name]
        r, sh, w = SUB[name]
        if reg[r] is None: raise ValueError('unknown ' + r)
        if isinstance(reg[r], tuple): raise ValueError('sub-register of a copied value')
        return (reg[r] >> sh) & ((1 << w) - 1)
    def rset(name, v):
        if name in reg: reg[name] = v if isinstance(v, tuple) else v & 0xffffffff; return
        if isinstance(v, tuple): raise ValueError('copied value into a sub-register')
        r, sh, w = SUB[name]
        old = reg[r] if reg[r] is not None and not isinstance(reg[r], tuple) else 0
        m = ((1 << w) - 1) << sh
        reg[r] = (old & ~m) | ((v << sh) & m)
    def ea(i, op):
        m = op.mem
        a = m.disp
        if m.base: a += rget(i.reg_name(m.base))
        if m.index: a += rget(i.reg_name(m.index)) * m.scale
        return a & 0xffffffff
    def mread(a, size):
        if all(a + k not in mem for k in range(size)) and size == 4 and not (STACK - 0x10000 <= a < STACK + 0x100):
            return ('g', a)                       # original value of a game global (read before any write to it)
        v = 0
        for k in range(size):
            if a + k not in mem: raise ValueError('read of unknown memory %x' % (a + k))
            if isinstance(mem[a + k], tuple): raise ValueError('partial read of a copied value at %x' % (a + k))
            v |= mem[a + k] << (8 * k)
        return v
    def mwrite(a, size, v):
        if isinstance(v, tuple):
            if size != 4: raise ValueError('copy of size %d' % size)
            for k in range(size): mem[a + k] = (v, k)
            if not (STACK - 0x10000 <= a < STACK + 0x100): out.append((a, size, v))
            return
        for k in range(size): mem[a + k] = (v >> (8 * k)) & 0xff
        if not (STACK - 0x10000 <= a < STACK + 0x100): out.append((a, size, v & ((1 << (8 * size)) - 1)))
    def get(i, op):
        if op.type == x86.X86_OP_REG: return rget(i.reg_name(op.reg))
        if op.type == x86.X86_OP_IMM: return op.imm & ((1 << (8 * op.size)) - 1)
        return mread(ea(i, op), op.size)
    def put(i, op, v):
        if op.type == x86.X86_OP_REG: rset(i.reg_name(op.reg), v)
        else: mwrite(ea(i, op), op.size, v)
    o = off(addr)
    for i in md.disasm(b[o:o + sizes[addr]], addr):
        mn, ops = i.mnemonic, i.operands
        if mn == 'ret': return out
        if mn == 'mov': put(i, ops[0], get(i, ops[1]))
        elif mn in ('xor', 'or', 'and', 'add', 'sub'):
            if mn == 'xor' and ops[0].type == x86.X86_OP_REG and ops[1].type == x86.X86_OP_REG and ops[0].reg == ops[1].reg:
                put(i, ops[0], 0); continue
            a, c = get(i, ops[0]), get(i, ops[1])
            if isinstance(a, tuple) or isinstance(c, tuple): raise ValueError('arithmetic on a copied value at %x' % i.address)
            r = {'xor': a ^ c, 'or': a | c, 'and': a & c, 'add': a + c, 'sub': a - c}[mn]
            put(i, ops[0], r & ((1 << (8 * ops[0].size)) - 1))
        elif mn in ('inc', 'dec'): put(i, ops[0], (get(i, ops[0]) + (1 if mn == 'inc' else -1)) & ((1 << (8 * ops[0].size)) - 1))
        elif mn == 'lea': put(i, ops[0], ea(i, ops[1]))
        elif mn == 'push':
            v = get(i, ops[0]) if not (ops[0].type == x86.X86_OP_REG and reg.get(i.reg_name(ops[0].reg), 0) is None) else 0
            reg['esp'] -= 4; mwrite(reg['esp'], 4, v)
        elif mn == 'pop':
            rset(i.reg_name(ops[0].reg), mread(reg['esp'], 4)); reg['esp'] += 4
        elif mn.startswith('rep stos') or mn in ('stosd', 'stosw', 'stosb'):
            size = {'d': 4, 'w': 2, 'b': 1}[mn[-1]]
            cnt = rget('ecx') if mn.startswith('rep') else 1
            v = rget({4: 'eax', 2: 'ax', 1: 'al'}[size])
            for k in range(cnt): mwrite(reg['edi'] + k * size, size, v)
            reg['edi'] = (reg['edi'] + cnt * size) & 0xffffffff
            if mn.startswith('rep'): reg['ecx'] = 0
        else:
            raise ValueError('unsupported at %x: %s %s' % (i.address, mn, i.op_str))
    raise ValueError('no ret')

for a in sys.argv[1:]:
    a = int(a, 16)
    try:
        w = run(a)
        print('/* %06x: %d writes */' % (a, len(w)))
        print(', '.join(('{ 0x%x, %d, G(0x%x) }' % (x[0], x[1], x[2][1])) if isinstance(x[2], tuple) else '{ 0x%x, %d, 0x%x }' % x for x in w))
    except Exception as e:      # any failure just means "not a simple store list"
        print('/* %06x: FAILED %s */' % (a, e))
