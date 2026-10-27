"""stubargs.py addr... : for each function, its direct callees (calls and tail jumps out of it) with a proposed
argument count for callee_stubs: the pushes right before each call in the same basic block (saved registers at
the function's start excluded), the smallest over the call sites; a tail jump passes the function's own arguments
(0 recorded). Flags callees that pop their own arguments (ret N: CS_POP) and thiscall ones (ecx set right before
the call: CS_THIS). Review the output: fewer arguments than real is safe (less is compared), more is not."""
import sys, csv, re, subprocess
D = 'C:/Users/Alexander/Desktop/Axis/'
fs = {int(r['address'], 16): (int(r['size']), r['name']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))}

def dis(a):
    out = subprocess.run(['python', D + 'recomp/tools/disx.py', hex(a)], capture_output=True, text=True).stdout.splitlines()
    return [l.split(None, 2) for l in out[1:] if l.strip()]

def retn(a):
    for l in dis(a):
        if l[1] == 'ret' and len(l) > 2: return int(l[2], 0) // 4
    return 0

def reads_args(a):
    # a callee that never reads the stack above its return address (no [esp + x] / [ebp + x]) takes no arguments:
    # a push counted before a call to it belongs to a later call (g(a, f()): push a; call f; push eax; call g)
    return any(len(l) > 2 and re.search(r'\[e[sb]p \+ ', l[2]) for l in dis(a))

for arg in sys.argv[1:]:
    a = int(arg, 16); size, name = fs[a]
    ins = dis(a)
    labels = set()
    for l in ins:
        if l[1].startswith('j') and len(l) > 2 and l[2].startswith('0x'): labels.add(int(l[2], 16))
    res = {}
    prologue = True; pushes = 0
    for l in ins:
        addr = int(l[0], 16); op = l[1]; opd = l[2] if len(l) > 2 else ''
        if addr in labels: pushes = 0
        if op == 'push':
            # saved registers: any push of a callee-saved register before the function's first call (after a sub
            # esp or a mov too); an argument pushed from one of them there is missed, which only compares less
            if prologue and opd in ('ebx', 'esi', 'edi', 'ebp'): continue
            pushes += 1
        elif op == 'call':
            prologue = False
        if op in ('call', 'jmp') and opd.startswith('0x'):
            t = int(opd, 16)
            if a <= t < a + size or t not in fs or not (0x401000 <= t < 0x49e000): pushes = 0 if op == 'call' else pushes; continue
            n = pushes if op == 'call' else 0
            prev = res.get(t)
            res[t] = n if prev is None else min(prev, n)
            pushes = 0
        elif op.startswith('j') or op in ('ret', 'call'):   # an indirect call (an import) uses its own pushes
            pushes = 0
    parts = []
    for t, n in sorted(res.items()):
        r = retn(t)
        if not r and not reads_args(t): n = 0
        fl = ' | CS_POP' if r else ''
        if r and r != n: fl += ' /* ret %d */' % r
        parts.append('0x%x, %d%s' % (t, r if r else n, fl))
    print('%s 0x%x: { %s, 0 }' % (name, a, ', '.join(parts)))
