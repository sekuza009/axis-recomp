import re, sys
S = sys.argv[1]
c = open(S + '/code57.c').read()
spec = []
for m in re.finditer(r'LIFT_PLAIN8?\((\w+), ([0-9a-f]+)\)', c):
    spec.append((m.group(1), m.group(2)))
for m in re.finditer(r'static (?:THISCALL|WINAPI) DWORD (\w+)\([^\n]*?run_lifted\(lift_([0-9a-f]+)', c):
    spec.append((m.group(1), m.group(2)))
for m in re.finditer(r'static DWORD WINAPI (\w+)\([^\n]*?run_lifted\(lift_([0-9a-f]+)', c):
    spec.append((m.group(1), m.group(2)))
seen, out = set(), []
for n, a in spec:
    if n in seen: continue
    seen.add(n)
    out.append('%s %s %d 40 0' % (n, a, 1 if n == 'input_asyncKeyPressed' else 0))
open(S + '/spec57.txt', 'w').write('\n'.join(out) + '\n')
print(len(out))
