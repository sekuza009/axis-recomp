"""uninit.py [addr ...]: game functions that read a stack slot of their own frame before writing it on some path.
Such a read sees whatever an earlier call left on the stack - in the original game the frames of the functions
called before; with rebuilt (lifted) functions running elsewhere, different values - so these are the places
where the game can behave differently in play although every rebuilt function matches its tests.

Forward data flow over each function's control flow graph: the stack pointer is tracked relative to the entry
(push/pop/sub/add esp, calls with their callees' "ret N" taken from the callee or 0), slots are dword offsets below
the entry esp; a slot counts as written after a write to any of its bytes, after "lea reg, [esp + k]" (its address
escapes: a callee may fill it), and for string instructions conservatively. At joins a slot is written only if it is
on every incoming path. Functions using ebp as a frame pointer are handled through ebp = esp at "mov ebp, esp".
Prints function, address of the read and the slot (offset from the entry esp).

--partial: a slot whose address goes to a callee that may fill less than the whole buffer (fread, fgets, _read,
ReadFile, RegQueryValueExA, recv ...: PARTIAL below) stays unwritten - the reads of what a short read left behind.
The escape is decided at the next call (or string instruction) after the lea.
--unhooked: the functions that still run as the game's own code (not in recomp.c's hook table), the CRT included,
instead of the game's code below 0x49e000."""
import sys, csv, struct, capstone
from capstone import x86 as X
D = 'C:/Users/Alexander/Desktop/Axis/'
b = open(D + 'recomp/installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; n = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
secs = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i) for i in range(n)]
def off(va):
    for nm, vs, sva, rs, ro in secs:
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
fs = {int(r['address'], 16): (int(r['size']), r['name']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))}
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
def retpop(t):
    if t not in fs: return 0
    sz = fs[t][0]; o = off(t)
    if o is None: return 0
    for i in md.disasm(b[o:o + sz], t):
        if i.mnemonic == 'ret': return i.operands[0].imm if i.operands else 0
    return 0
ESP, EBP = X.X86_REG_ESP, X.X86_REG_EBP
# the import address table: "call [iat]" sites by name
iat = {}
_imp = struct.unpack_from('<I', b, pe + 24 + 104)[0]
def _roff(rva):
    for nm, vs, sva, rs, ro in secs:
        if sva <= rva < sva + max(vs, rs): return rva - sva + ro
_d = _roff(_imp)
while struct.unpack_from('<I', b, _d + 12)[0]:
    _oft, _ts, _fc, _nm, _ft = struct.unpack_from('<IIIII', b, _d)
    _t, _k = _roff(_oft or _ft), 0
    while struct.unpack_from('<I', b, _t + 4 * _k)[0]:
        _v = struct.unpack_from('<I', b, _t + 4 * _k)[0]
        iat[0x400000 + _ft + 4 * _k] = '#%d' % (_v & 0xffff) if _v & 0x80000000 else b[_roff(_v) + 2:b.index(b'\0', _roff(_v) + 2)].decode()
        _k += 1
    _d += 20
PARTIAL = {'fread', 'fgets', '_read', 'ReadFile', 'RegQueryValueExA', 'GetWindowTextA', 'GetCurrentDirectoryA',
           'GetModuleFileNameA', 'IcmpSendEcho', 'mciSendCommandA', 'glGetFloatv', 'glGetBooleanv', '#16', '#17'}
partial = '--partial' in sys.argv
def callee_name(i):
    op = i.operands[0]
    if op.type == X.X86_OP_IMM: return fs.get(op.imm, (0, '?'))[1]
    if op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index: return iat.get(op.mem.disp, '?')
    return '?'

def analyse(a):
    sz, name = fs[a]
    o = off(a)
    ins = list(md.disasm(b[o:o + sz], a))
    idx = {i.address: k for k, i in enumerate(ins)}
    # state: (esp offset, ebp offset or None, frozenset of written slots)
    best = {}
    work = [(0, (0, None, frozenset(), 0, frozenset()))]
    reports = set()
    steps = 0
    while work and steps < 200000:
        steps += 1
        k, (sp, bp, wr, ab, pend) = work.pop()  # ab: esp before the pending call's arguments; pend: escaped slots
        while k < len(ins):
            i = ins[k]
            key = i.address
            if key in best:
                osp, obp, owr = best[key]
                if osp != sp: break                     # inconsistent stack depth (unknown pops): drop the path
                nwr = owr & wr
                if nwr == owr: break
                best[key] = (sp, bp, nwr); wr = nwr
            else:
                best[key] = (sp, bp, wr)
            m = i.mnemonic
            def slot(op):
                mm = op.mem
                if mm.index: return None
                if mm.base == ESP: return sp + mm.disp
                if mm.base == EBP and bp is not None: return bp + mm.disp
                return None
            ops = i.operands
            # reads
            for j, op in enumerate(ops):
                if op.type != X.X86_OP_MEM: continue
                s = slot(op)
                if s is None or s >= 0: continue          # >= 0: return address / arguments
                is_dest = j == 0 and m not in ('cmp', 'test', 'push') and not m.startswith('f') or m in ('fstp', 'fst', 'fistp', 'fist', 'fnstsw', 'fnstcw')
                if m == 'lea': continue
                pure_write = is_dest and m in ('mov', 'movzx', 'movsx', 'fstp', 'fst', 'fistp', 'fist', 'fnstsw', 'fnstcw', 'setne', 'sete') or m.startswith('set') and j == 0
                if j == 0 and len(ops) == 2 and ops[1].type == X.X86_OP_IMM and (m == 'and' and ops[1].imm == 0 or m == 'or' and ops[1].imm in (-1, 0xffffffff)):
                    pure_write = True                     # and [x], 0 / or [x], -1: the value does not depend on the old one
                if pure_write: continue
                if (s & ~3) not in wr and (s + op.size - 1) & ~3 not in wr:
                    reports.add((i.address, s))
            # writes
            for j, op in enumerate(ops):
                if op.type == X.X86_OP_MEM and j == 0 and m not in ('cmp', 'test', 'push') and m != 'lea':
                    s = slot(op)
                    if s is not None and s < 0:
                        wr = wr | {s & ~3, (s + op.size - 1) & ~3}
            if m == 'lea' and ops[1].type == X.X86_OP_MEM:
                s = slot(ops[1])
                if s is not None and s < 0:                  # address escapes: assume the whole frame below may be filled
                    if partial: pend = pend | frozenset(range(s & ~3, 0, 4))
                    else: wr = wr | frozenset(range(s & ~3, 0, 4))
            if m in ('rep stosd', 'rep movsd', 'stosd', 'movsd', 'rep stosb', 'rep movsb', 'stosb', 'movsb'):
                wr, pend = wr | pend, frozenset()
            if m == 'call' and pend:
                if callee_name(i) not in PARTIAL: wr = wr | pend
                pend = frozenset()
            # esp/ebp tracking
            if m == 'push':
                sp -= 4; wr = wr | {sp}
                nx = ins[k + 1] if k + 1 < len(ins) else None
                if (ops[0].type == X.X86_OP_REG and nx is not None and nx.mnemonic in ('mov', 'lea', 'xor')
                        and nx.operands[0].type == X.X86_OP_REG and nx.operands[0].reg == ops[0].reg):
                    ab = sp                                # push reg; mov reg, ...: a register saved, not an argument
            elif m == 'pop': sp += 4
            elif m == 'pushal': sp -= 32; wr = wr | frozenset(range(sp, sp + 32, 4))
            elif m == 'popal': sp += 32
            elif m in ('sub', 'add') and ops[0].type == X.X86_OP_REG and ops[0].reg == ESP and ops[1].type == X.X86_OP_IMM:
                sp += ops[1].imm if m == 'add' else -ops[1].imm
                ab = sp
            elif m == 'mov' and ops[0].type == X.X86_OP_REG and ops[0].reg == EBP and ops[1].type == X.X86_OP_REG and ops[1].reg == ESP:
                bp = sp
            elif m == 'call':
                if ops[0].type == X.X86_OP_IMM:
                    t = ops[0].imm
                    if t == 0x49ec14: pass                 # __ftol
                    elif t in (0x49fe00, 0x4a0c90) or fs.get(t, (0, ''))[1] == '_chkstk':
                        sp -= 0                            # _chkstk: handled by the sub that follows in MSVC 6? (eax = size)
                    sp += retpop(t)
                else:
                    sp = ab                                # import / register call: stdcall, pops what was pushed for it
                ab = sp
            if m.startswith('j') and ops and ops[0].type == X.X86_OP_IMM:
                t = ops[0].imm
                if t in idx: work.append((idx[t], (sp, bp, wr, ab, pend)))
                if m == 'jmp': break
            if m.startswith('ret') or (m == 'jmp'): break
            k += 1
    return sorted(reports)

args = [x for x in sys.argv[1:] if not x.startswith('--')]
if '--unhooked' in sys.argv:
    import re
    r = open(D + 'recomp/recomp.c').read()
    hooked = {int(x, 16) for x in re.findall(r'\{ 0x([0-9a-f]+), \(void \*\)\w+, "\w+" \}', r) + re.findall(r'hook\(0x([0-9a-f]+),', r)}
    targets = sorted(x for x in fs if x not in hooked and not fs[x][1].startswith('Unwind@'))
else:
    targets = [int(x, 16) for x in args] or sorted(x for x in fs if x < 0x49e000)
for a in targets:
    if a not in fs: continue
    try: r = analyse(a)
    except Exception as e: print('%06x %s: error %s' % (a, fs[a][1], e)); continue
    if r: print('%06x %-30s %s' % (a, fs[a][1], ' '.join('%x:%d' % (x, s) for x, s in r[:8])))
