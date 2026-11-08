"""Survey all shipped maps: round trip + a summary of sections (read only)."""
import sys, glob, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from bfd import *

verbose = '-v' in sys.argv
files = [a for a in sys.argv[1:] if a != '-v'] or sorted(glob.glob(r'C:\Users\Alexander\Desktop\Axis\Map\*.bfd'))
for fn in files:
    d = open(fn, 'rb').read()
    m = decode(d)
    ok = encode(m) == d
    g = m.ground
    print('%-22s rt=%s obj=%d play=%d cmd=%d wp=%d trig=%d pl=%d act=%d tails=%d/%d/%d/%d dir=%r fog=%d sky=%d lay=%d side=%d floor=%d map=%d mus=%d layers=%d trailer=%d lights=%d' % (
        os.path.basename(fn), ok, len(m.objects), len(m.play), len(m.commands), len(m.waypoints), len(m.triggers),
        len(m.players), len(m.actors), len(m.sec1_tail), len(m.sec2_tail), len(m.sec3_tail), len(m.sec4_tail),
        cstr(g['dir']), g['fogOn'], g['skyMode'], g['layerMode'], g['sideMode'], g['floorMode'], g['mapNumber'],
        g['musicKind'], len(g['layers']), len(m.trailer), len(g['lights'])))
    if verbose:
        from collections import Counter
        print(' opcodes', Counter(gu(c, 0) for c in m.commands))
        print(' obj flags', Counter(gi(o, 0x40) for o in m.objects), 'trig', Counter(gi(o, 0x44) for o in m.objects),
              'period', Counter(gi(o, 0x48) for o in m.objects))
        print(' play kinds', Counter(gu(p, 0) for p in m.play))
        for p in m.play:
            if gu(p, 0) != 2:
                print('  play', [gi(p, k) for k in (0, 4, 8, 12)], [round(gf(p, k), 2) for k in (16, 20, 24, 28, 32)])
        for i, t in enumerate(m.triggers):
            print('  trig', i, 'nwp', gi(t, 0), 'armed', gi(t, 8), 'flags', gu(t, 12), 'time', gf(t, 16), 'rad', gf(t, 20), 'fired', gi(t, 24))
        k = 0
        for i, w in enumerate(m.waypoints):
            n = gi(w, 12)
            print('  wp', i, [round(gf(w, j), 1) for j in (0, 4, 8)], 'ncmd', n,
                  [[gi(m.commands[k + j], 4 * q) for q in range(4)] for j in range(n)])
            k += n
        for i, p in enumerate(m.players):
            print('  player', i, gi(p, 0), gi(p, 4), cstr(p[8:0x28]), 'team', gi(p, 0x28), 'parts', [gi(p, 0x2c + 4 * q) for q in range(5)], 'items', [gi(p, 0x40 + 4 * q) for q in range(6)])
        for i, a in enumerate(m.actors):
            print('  actor', i, 'player', gi(a, 0), 'pos', [round(gf(a, 4 + 4 * q), 1) for q in range(3)], 'pitch', gf(a, 0x10), 'yaw', gf(a, 0x14),
                  'bot', gi(a, 0x18), 'u1c', gi(a, 0x1c), 'arm', gi(a, 0x20), 'sh', gi(a, 0x24), 'spd', gf(a, 0x28), 'turn', gf(a, 0x2c), 'range', gf(a, 0x30),
                  'u34', gf(a, 0x34), 'aim', gf(a, 0x38), 'sflag', gu(a, 0x3c), 'dodge', gf(a, 0x40), gf(a, 0x44), 'bp', [gf(a, 0x48 + 4 * q) for q in range(5)])
        print(' limits', [round(struct.unpack_from('<f', g['limits'], 4 * q)[0], 1) for q in range(12)])
        for h, img in g['layers']:
            print('  layer kind', gi(h, 0), 'origin', [gf(h, 4 + 4 * q) for q in range(3)], 'rows', gi(h, 0x1c), 'cols', gi(h, 0x20), 'cell', gf(h, 0x24), 'hs', gf(h, 0x28), 'tex', gf(h, 0x2c), 'water', gi(h, 0x30), 'rest nonzero', sum(1 for x in h[0x34:] if x))
