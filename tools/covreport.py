"""covreport.py [recomp.log]: per lifted function, which of its labels the state tests reached (COVHIT lines from a
tools/covall.py run). Writes coverage.txt (worst first) and prints a summary. Functions are found in lifted/*.c (the
uninstrumented files: run after "git checkout -- lifted recomp.c"). Lifts nothing uses (hand-written rebuilds replaced
them, or the function stays native) are listed apart."""
import os, re, glob, sys, csv
os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
log = sys.argv[1] if len(sys.argv) > 1 else 'recomp.log'
hit = set(int(x, 16) for x in re.findall(r'COVHIT ([0-9a-f]+)', open(log, errors='replace').read()))
names = {int(r['address'], 16): r['name'] for r in csv.DictReader(open('../decomp/out/functions.csv'))}
allsrc = open('recomp.c', errors='replace').read() + ''.join(open(q, errors='replace').read() for q in glob.glob('lifted/*.c'))
def used(a):   # referenced other than by its own declaration and definition: a wrapper, a hook or a lifted caller
    return (len(re.findall(r'lift_%x(?![0-9a-f])' % a, allsrc)) > 2 or     # LIFT_PLAIN* builds lift_<addr> by pasting
            re.search(r'LIFT_PLAIN\w*\(\w+, %x\)' % a, allsrc) is not None)
rows = []; unused = []
for p in sorted(glob.glob('lifted/*.c')):
    s = open(p, errors='replace').read()
    for m in re.finditer(r'^static void lift_([0-9a-f]+)\(X86 \*m\)\n\{\n(.*?)^\}', s, re.M | re.S):
        a = int(m.group(1), 16)
        if not used(a): unused.append((a, names.get(a, '?'))); continue
        labs = [int(x, 16) for x in re.findall(r'^L_([0-9a-f]+):', m.group(2), re.M)]
        got = [l for l in labs if l in hit]
        rows.append((a, names.get(a, '?'), a in hit, len(labs), len(got), [l for l in labs if l not in hit], os.path.basename(p)))
def score(r): return (r[2], (r[4] / r[3]) if r[3] else 1.0)
rows.sort(key=score)
with open('coverage.txt', 'w', newline='\r\n') as f:
    f.write('lifted function coverage from the state tests (labels reached / labels); "NOT ENTERED" = no test ran it\n')
    for a, n, ent, tot, g, miss, fl in rows:
        st = 'NOT-ENTERED' if not ent else '%d/%d' % (g, tot) if tot else 'no-labels'
        f.write('%06x %-36s %-12s %-10s %s\n' % (a, n, st, fl, ' '.join('%x' % x for x in miss[:12]) + (' ...' if len(miss) > 12 else '')))
    f.write('\nlifts nothing uses (hand-written rebuilds or native functions): %s\n' % ' '.join(n for a, n in unused))
ent = sum(1 for r in rows if r[2]); tl = sum(r[3] for r in rows); tg = sum(r[4] for r in rows)
full = sum(1 for r in rows if r[2] and r[3] == r[4])
print('%d lifted functions in use: %d entered, %d fully covered; labels %d / %d (%.1f%%)' % (len(rows), ent, full, tg, tl, 100.0 * tg / max(tl, 1)))
print('%d lifts nothing uses: %s' % (len(unused), ' '.join(n for a, n in unused)))
print('worst:'); [print('  %06x %-36s %s' % (r[0], r[1], 'NOT ENTERED' if not r[2] else '%d/%d' % (r[4], r[3]))) for r in rows[:25]]
