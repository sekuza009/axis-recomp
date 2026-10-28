"""eaxuse.py addr...: who reads a function's eax? Follows tail jumps and 'call; ret' wrappers up to real call sites
and prints the instructions after each, so a leftover return value can be shown to be dead."""
import sys, struct, csv, capstone
sys.argv, args = sys.argv[:1], sys.argv[1:]
sys.path.insert(0, __import__('os').path.dirname(__file__))
import disx
b = disx.b; md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
fns = sorted((int(r['address'], 16), int(r['size']), r['name']) for r in csv.DictReader(open(disx.D + 'decomp/out/functions.csv')))
def owner(va):
    for a, s, n in fns:
        if a <= va < a + s: return a, n
    return None, None
text = [(sva, rs, ro) for nm, vs, sva, rs, ro in disx.S if nm.startswith(b'.text')]
def callers(tgt):
    for sva, rs, ro in text:
        for o in range(ro, ro + rs - 5):
            if b[o] in (0xe8, 0xe9):
                va = o - ro + sva + 0x400000
                if va + 5 + struct.unpack_from('<i', b, o + 1)[0] == tgt: yield va, b[o], o
seen = set(); todo = [int(a, 16) for a in args]
while todo:
    t = todo.pop()
    if t in seen: continue
    seen.add(t)
    for va, op, o in callers(t):
        a, n = owner(va)
        nxt = list(md.disasm(b[o + 5:o + 25], va + 5))[:3]
        print('%06x <- %06x %s %s :: %s' % (t, va, 'call' if op == 0xe8 else 'jmp ', n,
              ' | '.join('%s %s' % (i.mnemonic, i.op_str) for i in nxt) if op == 0xe8 else '(tail)'))
        if a and (op == 0xe9 or (nxt and nxt[0].mnemonic in ('ret', 'pop', 'add') and 'eax' not in nxt[0].op_str and
                                 any(i.mnemonic == 'ret' for i in nxt))):
            todo.append(a)
