"""classify.py <func-addr>: how a function uses each absolute global: float (x87 load/op), int (fild / integer use),
string (pushed or lea'd address, in a string area). Prints a summary and C setup lines."""
import re, subprocess, sys, os
os.chdir(r'C:\Users\Alexander\Desktop\Axis\recomp')
out = subprocess.run(['python', 'tools/disx.py', sys.argv[1]], capture_output=True, text=True).stdout
kind = {}
def add(a, k):
    kind.setdefault(a, set()).add(k)
for line in out.splitlines()[1:]:
    parts = line.split(None, 2)
    if len(parts) < 3: continue
    mn, ops = parts[1], parts[2]
    for m in re.finditer(r'(dword|word|byte|qword) ptr \[0x([0-9a-f]+)\]', ops):
        a = int(m.group(2), 16); size = m.group(1)
        if a < 0x4a9000 or a >= 0xb00000: continue
        if a < 0x4b0000: continue                       # IAT / float constants in .rdata
        if mn.startswith('fi'): add(a, 'int')
        elif mn.startswith('f'): add(a, 'float' if size == 'dword' else 'double')
        elif size == 'byte': add(a, 'byte')
        else: add(a, 'int')
    m = re.match(r'(push|mov\s+e..,)\s*0x([0-9a-f]{6})$', mn + ' ' + ops) if mn == 'push' else None
    if mn == 'push':
        m2 = re.fullmatch(r'0x([0-9a-f]{6})', ops.strip())
        if m2:
            a = int(m2.group(1), 16)
            if 0x4b0000 <= a < 0xb00000: add(a, 'addr')
    if mn in ('mov', 'lea'):
        m3 = re.search(r', 0x([0-9a-f]{6})$', ops)
        if m3:
            a = int(m3.group(1), 16)
            if 0x4b0000 <= a < 0xb00000: add(a, 'addr')
summary = {}
for a in sorted(kind):
    summary.setdefault('/'.join(sorted(kind[a])), []).append(a)
for k, v in sorted(summary.items()):
    print(k, len(v), ' '.join(hex(a) for a in v[:400]))
