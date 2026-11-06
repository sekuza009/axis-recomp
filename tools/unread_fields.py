import re, subprocess, os
R = 'C:/Users/Alexander/Desktop/Axis/recomp/'
cur, cands = None, []
for line in open(R + 'src/scene.fields', encoding='latin-1'):
    if line.startswith('struct '):
        cur = line.split()[1]; continue
    m = re.match(r'^(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+[\w *]+?\b(\w+)(\[[^\]]*\])?\s*(#.*)?$', line.rstrip())
    if not (m and cur): continue
    name, com = m.group(3), (m.group(5) or '')
    if re.match(r'(unused|cleared)', name) or re.search(r'never read|not read|nothing reads|never touched|written, never|set, never|only zeroed|only written', com):
        cands.append((cur, name, com[:110]))
print(len(cands), 'fields claimed never read')
for s, f, com in cands:
    out = subprocess.run(['python', 'tools/field_uses.py', '%s.%s' % (s, f)], cwd=R, capture_output=True, text=True).stdout
    uses = [l for l in out.splitlines() if re.search(r'(->|\.)\s*%s\b' % f, l) or 'offsetof' in l]
    reads = []
    for l in uses:
        code = re.sub(r'/\*.*?\*/', '', l.split(':', 2)[-1])
        code = re.sub(r'(->|\.)\s*%s\b(\[[^\]]*\])*\s*(=(?!=)|\+\+|--)' % f, ' WRITE ', code)   # stores
        code = re.sub(r'\b(memset|zero\w*|clear\w*)\s*\([^;]*%s' % f, ' WRITE ', code)
        if re.search(r'(->|\.)\s*%s\b' % f, code) or 'offsetof' in code:
            reads.append(l.strip()[:160])
    print('%-14s %-16s uses %2d, reads %d  %s' % (s, f, len(uses), len(reads), com[:70]))
    for r in reads[:4]: print('      ', r)
