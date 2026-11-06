r"""analyze.py runs/*.tsv: merge the range-trace statistics and check every name / type against what was seen"""
import csv, glob, re, struct, sys
from collections import defaultdict
csv.field_size_limit(10 ** 8)
R = 'C:/Users/Alexander/Desktop/Axis/recomp/src/'

# ---- merge
M = {}
for path in sys.argv[1:]:
    rows = list(csv.reader(open(path, encoding='latin-1'), delimiter='\t'))
    for r in rows[1:]:
        if len(r) < 17:
            continue
        name, kind = r[0], r[1]
        n, nz, imin, imax, fmin, fmax = int(r[2]), int(r[3]), int(r[4]), int(r[5]), float(r[6]), float(r[7])
        nonfin, den, fl, nd = int(r[8]), int(r[9]), int(r[10]), int(r[11])
        vals = [int(v, 16) for v in r[12].split(',') if v]
        p = [int(x) for x in r[13].split(',')]
        s = [int(x) for x in r[15].split(',')]
        m = M.setdefault(name, dict(kind=kind, n=0, nz=0, imin=None, imax=None, fmin=None, fmax=None, nonfin=0, den=0,
                                    fl=0, vals=set(), many=False, pvalid=0, pimage=0, pbad=0, badptr=0, sn=0, snonterm=0,
                                    snonprint=0, sample='', runs=set()))
        m['n'] += n; m['nz'] += nz
        if nz:
            m['runs'].add(path.split('/')[-1].split('\\')[-1].split('_')[0])
            if kind not in 'fdps':
                m['imin'] = imin if m['imin'] is None else min(m['imin'], imin)
                m['imax'] = imax if m['imax'] is None else max(m['imax'], imax)
            if kind in 'fd' and nz > nonfin:
                m['fmin'] = fmin if m['fmin'] is None else min(m['fmin'], fmin)
                m['fmax'] = fmax if m['fmax'] is None else max(m['fmax'], fmax)
        m['nonfin'] += nonfin; m['den'] += den; m['fl'] += fl
        m['vals'] |= set(vals); m['many'] |= nd > 16
        if kind == 'p':
            m['pvalid'] += p[1]; m['pimage'] += p[2]; m['pbad'] += p[3]
            if p[3]: m['badptr'] = int(r[14], 16)
        m['sn'] += s[0]; m['snonterm'] += s[1]; m['snonprint'] += s[2]
        if r[16] and not m['sample']: m['sample'] = r[16]

# ---- declarations and comments
info = {}
cur = None
for line in open(R + 'scene.fields', encoding='latin-1'):
    mm = re.match(r'struct (\w+) ', line)
    if mm: cur = mm.group(1); continue
    mm = re.match(r'^(0x[0-9a-f]+|\d+)\s+(0x[0-9a-f]+|\d+)\s+(.*?)\s*(#.*)?$', line.rstrip())
    if mm and cur:
        nm = re.search(r'(\w+)\s*((\[[^\]]*\])*)$', mm.group(3))
        if nm: info['%s.%s' % (cur, nm.group(1))] = (mm.group(3), (mm.group(4) or '')[1:].strip())
for f in ('globals.h', 'objects.h'):
    for line in open(R + f, encoding='latin-1'):
        mm = re.match(r'#define (\w+) (.*?)(?:/\*(.*?)(\*/|$))?\s*$', line.rstrip())
        if mm: info[mm.group(1)] = (mm.group(2).strip(), (mm.group(3) or '').strip())


def fbits(v):
    return struct.unpack('<f', struct.pack('<I', v & 0xffffffff))[0]


def show_vals(m, k):
    vs = sorted(m['vals'])[:12]
    if k in 'f':
        return ', '.join('%g' % fbits(v) for v in vs) + (' ...' if m['many'] else '')
    return ', '.join(str(v - (1 << 32) if v >= 0x80000000 and k == 'i' else v) for v in vs) + (' ...' if m['many'] else '')


def words(name):
    base = name.split('.')[-1]
    base = re.sub(r'^g_', '', base)
    return [w.lower() for w in re.findall(r'[A-Z]?[a-z0-9]+|[A-Z]+(?![a-z])', base)]


issues = defaultdict(list)


def flag(rule, name, msg):
    issues[rule].append((name, msg))


FLAGW_FIRST = {'is', 'has', 'can', 'was', 'should', 'needs', 'any', 'did', 'got', 'want', 'wants', 'use', 'uses', 'show',
               'no', 'allow', 'allowed', 'must', 'skip', 'force', 'keep', 'hold', 'holds'}
FLAGW_LAST = {'_','flag', 'done', 'pending', 'shown', 'open', 'opened', 'active', 'enabled', 'ready', 'held', 'down',
              'pressed', 'changed', 'valid', 'locked', 'visible', 'paused', 'gone', 'taken', 'used', 'full', 'dirty',
              'on', 'off', 'set', 'loaded', 'started', 'finished', 'over', 'connected', 'joined', 'quit', 'leaving',
              'left', 'busy', 'waiting', 'blocked', 'empty', 'alive', 'dead', 'enabled', 'ok', 'failed', 'won', 'lost'}
COUNTW = {'count', 'counts', 'total', 'num', 'number', 'total'}
INDEXW = {'index', 'slot', 'cursor', 'chosen', 'selected', 'pick', 'row', 'id'}
ANGLEW = {'yaw', 'pitch', 'roll', 'angle', 'heading', 'turn'}

exercised = 0
for name, m in sorted(M.items()):
    k = m['kind']
    if not m['nz'] and not m['sn']:
        continue
    exercised += 1
    decl, com = info.get(name, ('', ''))
    w = words(name)
    vals = m['vals']
    isint = k in 'iuBbhwq'
    # flags
    if isint and w and (w[0] in FLAGW_FIRST or w[-1] in FLAGW_LAST) and w[-1] not in ('left', 'right', 'top', 'bottom') and not re.match(r'g_(dik|key)', name) and not m['many'] and not vals <= {0, 1}:
        flag('flag name, values other than 0/1', name, show_vals(m, k) + '   # ' + com[:110])
    if isint and w and w[-1] in COUNTW and m['imin'] is not None and m['imin'] < 0:
        flag('count name, negative values', name, 'min %d max %d   # %s' % (m['imin'], m['imax'], com[:110]))
    if isint and w and w[-1] in INDEXW and m['imin'] is not None and m['imin'] < -1:
        flag('index name, values below -1', name, 'min %d max %d   # %s' % (m['imin'], m['imax'], com[:110]))
    if k in 'iu' and m['nz'] >= 5 and m['fl'] > 0.6 * m['nz']:
        flag('int field holding float bits', name, '%d of %d non-zero samples float-like: %s   # %s' % (
            m['fl'], m['nz'], ', '.join('%g' % fbits(v) for v in sorted(vals)[:8]), com[:100]))
    if k == 'f' and m['nz'] >= 5 and m['den'] > 0.6 * m['nz'] and not (not m['many'] and vals <= {0, 0x80000000}):
        flag('float field holding integers', name, '%d of %d non-zero samples denormal: %s   # %s' % (
            m['den'], m['nz'], ', '.join(str(v) for v in sorted(vals)[:8]), com[:100]))
    if k in 'fd' and m['nonfin']:
        flag('float field NaN / infinite', name, '%d samples   # %s' % (m['nonfin'], com[:110]))
    if k == 'p' and m['pbad'] and not re.search(r'(dc|wnd|window|font|handle|hedit|event|thread|module|instance|icon|brush|bitmap|hglrc|context|surface|device|buffer)$', name.lower()) and not re.match(r'g_h[A-Z]', name):
        flag('pointer to unmapped memory', name, '%d samples (e.g. %08x), %d valid, %d image   # %s' % (
            m['pbad'], m['badptr'], m['pvalid'], m['pimage'], com[:100]))
    if k == 's' and (m['snonterm'] or m['snonprint']):
        flag('string unterminated / control characters', name, '%d of %d unterminated, %d with control chars; "%s"   # %s' % (
            m['snonterm'], m['sn'], m['snonprint'], m['sample'], com[:90]))
    if k == 'f' and w and w[-1] in ANGLEW and m['fmax'] is not None and max(abs(m['fmin']), abs(m['fmax'])) > 1e6:
        flag('angle out of any sane range', name, '%g .. %g   # %s' % (m['fmin'], m['fmax'], com[:100]))
    leaf = name.split('.')[-1]
    if (re.match(r'(g_)?cleared', leaf) or re.search(r'only (zeroed|cleared)|never set|always 0|always off', com)) and m['nz']:
        flag('said to stay 0, seen non-zero', name, show_vals(m, k) + '   # ' + com[:110])
    # ranges written in the comment: "A .. B" (integers) when the comment gives exactly one
    rg = re.findall(r'(?<![\w.])(-?\d+) \.\. (-?\d+)(?![\w.])', com)
    if isint and len(rg) == 1 and m['imin'] is not None and not m['many']:
        lo, hi = int(rg[0][0]), int(rg[0][1])
        if lo < hi and (m['imin'] < lo or m['imax'] > hi) and not (m['imin'] == -1 and lo == 0 and 'none' in com):
            flag('outside the range its comment gives', name, 'seen %s; comment %d .. %d   # %s' % (show_vals(m, k), lo, hi, com[:100]))

print('%d leaves, %d exercised (seen non-zero)' % (len(M), exercised))
for rule in sorted(issues):
    print('\n## %s (%d)' % (rule, len(issues[rule])))
    for n, msg in issues[rule]:
        print('  %-34s %s' % (n, msg))
