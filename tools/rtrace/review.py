r"""review.py nchunks runs/*.tsv: review/chunk_<i>.txt, one line per field / global seen non-zero:
name | declaration | observed | comment"""
import sys, os, re
sys.argv = [sys.argv[0]] + sys.argv[2:] if False else sys.argv
nch = int(sys.argv[1]); files = sys.argv[2:]
sys.argv = ['analyze.py'] + files
src = open('analyze.py').read().split("print('%d leaves")[0]
import io, contextlib
g = {}
with contextlib.redirect_stdout(io.StringIO()):
    exec(src, g)
M, info, fbits, show_vals = g['M'], g['info'], g['fbits'], g['show_vals']
lines = []
for name, m in sorted(M.items()):
    k = m['kind']
    if not m['nz'] and not m['sn']:
        continue
    decl, com = info.get(name, ('', ''))
    if k == 's':
        obs = 'strings: e.g. "%s"%s' % (m['sample'], ', some unterminated' if m['snonterm'] else '')
    elif k == 'p':
        obs = 'pointer: %d valid, %d original-image addresses, %d unmapped' % (m['pvalid'], m['pimage'], m['pbad'])
    elif k in 'fd':
        obs = 'float %g .. %g; values %s%s' % (m['fmin'] or 0, m['fmax'] or 0, show_vals(m, 'f'), '; NaN/inf seen' if m['nonfin'] else '')
    else:
        obs = 'int %s .. %s; values %s%s' % (m['imin'], m['imax'], show_vals(m, k), '; mostly float bits: %s' % ', '.join('%g' % fbits(v) for v in sorted(m['vals'])[:6]) if m['fl'] > 0.6 * m['nz'] else '')
    obs += '; non-zero in %d%% of samples; runs: %s' % (100 * m['nz'] // max(1, m['n']), ','.join(sorted(m['runs']))[:60])
    lines.append('%s | %s | %s | %s' % (name, decl[:80], obs, com))
os.makedirs('review', exist_ok=True)
per = (len(lines) + nch - 1) // nch
for i in range(nch):
    open('review/chunk_%d.txt' % i, 'w', encoding='utf-8').write('\n'.join(lines[i * per:(i + 1) * per]) + '\n')
print(len(lines), 'lines,', per, 'per chunk')
