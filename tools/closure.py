"""closure.py done.txt [max-funcs]: the next rebuild groups once every "ready" function is rebuilt. For each game function
not rebuilt yet, its closure = itself plus every not-rebuilt game function it reaches through direct calls (library
code: the MSVC CRT at 0x49e000+, the 0x4a8xxx thunks and patch code, and IAT imports end the walk). A closure can be
rebuilt as one group (callees first). Prints the groups with at most max-funcs functions (default 4), smallest total
size first, with the library functions they use; groups contained in a printed larger one are not repeated.
A * marks functions our patches changed (bytes differ from retail, decomp/bin/AxisGL.exe): the reference is the
patched build, so rebuild those from it and check they do not jump into patch code."""
import sys, csv, struct, capstone
D = 'C:/Users/Alexander/Desktop/Axis/'
done = {int(x, 16) for x in open(sys.argv[1]).read().split()}
MAXF = int(sys.argv[2]) if len(sys.argv) > 2 else 4
b = open(D + 'recomp/installed.exe', 'rb').read(); retail = open(D + 'decomp/bin/AxisGL.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; n = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
secs = [struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i) for i in range(n)]
def off(va):
    for nm, vs, sva, rs, ro in secs:
        if sva <= va - 0x400000 < sva + rs: return va - 0x400000 - sva + ro
fs = {int(r['address'], 16): (int(r['size']), r['name']) for r in csv.DictReader(open(D + 'decomp/out/functions.csv'))}
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
LIB = 0x49e000
callees, indirect = {}, set()
for a, (sz, name) in fs.items():
    if a >= LIB: continue
    o = off(a); cs = set()
    for i in md.disasm(b[o:o + sz], a):
        if i.mnemonic == 'call' or (i.mnemonic == 'jmp' and i.op_str.startswith('0x')):
            if i.op_str.startswith('0x'):
                t = int(i.op_str, 16)
                if t in fs and not (a <= t < a + sz): cs.add(t)
            elif i.mnemonic == 'call' and i.operands[0].type == capstone.x86.X86_OP_MEM and (i.operands[0].mem.base or i.operands[0].mem.index):
                indirect.add(a)                     # COM methods / function-pointer tables: callee unknown
            # call reg: MSVC's cached import address (mov esi, [import] ... call esi) - library like the IAT calls
    callees[a] = cs
todo = [a for a in callees if a not in done]
def closure(a):
    seen, st = set(), [a]
    while st:
        x = st.pop()
        if x in seen: continue
        seen.add(x)
        for t in callees.get(x, ()):
            if t < LIB and t not in done: st.append(t)
    return seen
groups = []
for a in todo:
    c = closure(a)
    if len(c) <= MAXF and not (c & indirect):
        groups.append((sum(fs[x][0] for x in c), a, c))
groups.sort()
def patched(x):
    o = off(x); sz = fs[x][0]
    return retail[o:o + sz] != b[o:o + sz]
def label(x): return fs[x][1] + ('*' if patched(x) else '')
printed = []
for size, a, c in groups:
    if any(c <= p for p in printed): continue
    printed.append(c)
    libs = sorted({fs[t][1] for x in c for t in callees[x] if t >= LIB})
    print('%5d  %-34s + %s   %s' % (size, label(a), ', '.join(label(x) for x in sorted(c) if x != a) or '-', ' '.join(libs)))
print('%d functions not rebuilt, %d with indirect calls; %d groups of <= %d printed' % (len(todo), len(set(todo) & indirect), len(printed), MAXF))
