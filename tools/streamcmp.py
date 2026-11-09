"""streamcmp.py <a> [b]: the drawing streams (AXGLREC1 files: tools/plat_tests/host*_test.c) summed up per frame - ops by
count and words - and with two files the frames compared op by op (the first difference shown)"""
import struct, sys
from collections import Counter

def read(path):
    d = open(path, 'rb').read()
    assert d[:8] == b'AXGLREC1'
    n, = struct.unpack_from('<I', d, 8)
    o = 12
    names = []
    for i in range(n):
        w, l = struct.unpack_from('<II', d, o)
        names.append((d[o + 8:o + 8 + l].decode(), w))
        o += 8 + l
    frames = []
    while o + 12 <= len(d):
        w, h, c = struct.unpack_from('<III', d, o)
        o += 12
        frames.append((w, h, struct.unpack_from('<%dI' % c, d, o)))
        o += 4 * c
    return names, frames

EXTRA = {64: 'Color4ubv', 65: 'Fogfv', 66: 'LoadMatrix', 67: 'MultMatrix', 68: 'TexCoord2fv', 69: 'Vertex3fv', 70: 'Vertex4fv',
         71: 'PixelStore', 72: 'Draw', 73: 'TexImage', 74: 'Mipmaps', 75: 'TexParami'}

def ops(names, words):
    """(op name, its words) in order"""
    out, i = [], 0
    while i < len(words):
        op = words[i] & 0xffff
        n = words[i] >> 16
        if op == 73:   # TexImage: 9 words then the bytes (count in word 9)
            nb = words[i + 9]
            n = 9 + (nb + 3) // 4
        elif op == 74:
            nb = words[i + 7]
            n = 7 + (nb + 3) // 4
        elif op == 72:   # Draw: mode count itype n, indices, then 3 arrays
            count, itype, nv = words[i + 2], words[i + 3], words[i + 4]
            sz = {0x1401: 1, 0x1403: 2}.get(itype, 4)
            j = i + 5 + (count * sz + 3) // 4
            for a in range(3):
                on = words[j]; j += 1
                if on:
                    s, t = words[j], words[j + 1]; j += 2
                    ts = {0x1400: 1, 0x1401: 1, 0x1402: 2, 0x1403: 2, 0x140a: 8}.get(t, 4)
                    j += (nv * s * ts + 3) // 4
            n = j - i - 1
        name = names[op][0] if op < len(names) else EXTRA.get(op, 'op%d' % op)
        out.append((name, words[i + 1:i + 1 + n]))
        i += 1 + n
    return out

a = read(sys.argv[1])
fa = a[1]
print('%s: %d frames' % (sys.argv[1], len(fa)))
if len(sys.argv) < 3:
    for k in (0, 1, len(fa) - 1):
        c = Counter(n for n, _ in ops(a[0], fa[k][2]))
        print(' frame %d (%dx%d): %d words; %s' % (k + 1, fa[k][0], fa[k][1], len(fa[k][2]), ', '.join('%s %d' % x for x in c.most_common(12))))
    sys.exit()
b = read(sys.argv[2])
fb = b[1]
print('%s: %d frames' % (sys.argv[2], len(fb)))
for k in range(min(len(fa), len(fb), int(sys.argv[3]) if len(sys.argv) > 3 else 10)):
    oa, ob = ops(a[0], fa[k][2]), ops(b[0], fb[k][2])
    ca, cb = Counter(n for n, _ in oa), Counter(n for n, _ in ob)
    same = sum(1 for x, y in zip(oa, ob) if x == y)
    diff = next((i for i, (x, y) in enumerate(zip(oa, ob)) if x != y), None)
    print('frame %d: %d / %d ops, %d identical%s' % (k + 1, len(oa), len(ob), same, '' if diff is None else '; first difference at op %d: %s %s | %s %s' % (diff, oa[diff][0], [hex(w) for w in oa[diff][1][:6]], ob[diff][0], [hex(w) for w in ob[diff][1][:6]])))
    if ca != cb:
        print('   op counts differ:', {k: (ca[k], cb[k]) for k in set(ca) | set(cb) if ca[k] != cb[k]})
