"""map_lights.py [game folder] [--csv out.csv]: every map's lighting read from its file, as the game reads it
(src/load/map_info.c map_loadGroundInfoFrom): Map/<name>.bfd - a version word (0x1201), then scrambled (each byte
rol1(b ^ 0x59)): four blocks skipped (a size, then that many bytes), the map's directory (0x100), the view range, the
light pool (LightFactors_read: count, next free, count x 0x2c-byte Factor records, enabled), the clear colour (on +
RGBA floats), the fog (on, RGBA, start, end, density) and the background's modes (sky sphere, sky layers, sides,
floor). The maps in mapinfo.dat's order (skirmish round N is map N). For the Godot remaster: which maps have lights of
their own, of what kinds and colours, a sky, fog."""
import os, struct, sys

GAME = sys.argv[1] if len(sys.argv) > 1 and not sys.argv[1].startswith('--') else 'C:/Users/Alexander/Desktop/Axis'


def rol1(b):
    return ((b << 1) | (b >> 7)) & 0xff


class Reader:
    def __init__(self, data, pos):
        self.d, self.p = data, pos

    def raw(self, n):
        out = bytes(rol1(b ^ 0x59) for b in self.d[self.p:self.p + n])
        self.p += n
        return out

    def u32(self):
        return struct.unpack('<I', self.raw(4))[0]

    def f32(self, n=1):
        v = struct.unpack('<%df' % n, self.raw(4 * n))
        return v if n > 1 else v[0]


def map_names():
    d = open(os.path.join(GAME, 'initdata', 'mapinfo.dat'), 'rb').read()
    n = struct.unpack_from('<i', d, 0x80)[0]
    out, o = [], 0x84
    for i in range(n):
        nm = d[o:o + 32].split(b'\0')[0]
        out.append(bytes(255 - b for b in nm).decode('latin1').strip())
        o += 32 + 0x50
    return out


def find_file(name):
    for f in os.listdir(os.path.join(GAME, 'Map')):
        if f.lower() == name.lower() + '.bfd':
            return os.path.join(GAME, 'Map', f)
    return None


def read_map(path):
    d = open(path, 'rb').read()
    if struct.unpack_from('<I', d, 0)[0] != 0x1201:
        return {'error': 'version %#x' % struct.unpack_from('<I', d, 0)[0]}
    r = Reader(d, 4)
    for _ in range(4):
        n = r.u32()
        r.p += n
    directory = r.raw(0x100).split(b'\0')[0].decode('latin1')
    view = r.f32()
    count, next_free = r.u32(), r.u32()
    lights = []
    for i in range(count):
        rec = r.raw(0x2c)
        idx, used, kind, colour = struct.unpack_from('<iiiI', rec, 0)
        pos = struct.unpack_from('<3f', rec, 0x10)
        direction = struct.unpack_from('<3f', rec, 0x1c)
        radius = struct.unpack_from('<f', rec, 0x28)[0]
        if used == 1:
            lights.append({'kind': kind, 'colour': (colour & 0xff, (colour >> 8) & 0xff, (colour >> 16) & 0xff),
                           'pos': pos, 'dir': direction, 'radius': radius})
    enabled = r.u32()
    clear_on = r.u32()
    clear = r.f32(4)
    fog_on = r.u32()
    fog_colour = r.f32(4)
    fog_start, fog_end, fog_density = r.f32(), r.f32(), r.f32()
    modes = [r.u32() for _ in range(4)]
    return {'dir': directory, 'view': view, 'lights': lights, 'enabled': enabled, 'clear_on': clear_on, 'clear': clear,
            'fog_on': fog_on, 'fog_colour': fog_colour, 'fog': (fog_start, fog_end, fog_density), 'modes': modes}


def hexc(c):
    return '#%02x%02x%02x' % c


def main():
    names = map_names()
    rows = []
    for i, name in enumerate(names):
        path = find_file(name)
        if not path:
            print('%2d %-16s (no file)' % (i, name))
            continue
        m = read_map(path)
        if 'error' in m:
            print('%2d %-16s %s' % (i, name, m['error']))
            continue
        kinds = {0: [], 1: [], 2: [], 3: []}
        for l in m['lights']:
            kinds.setdefault(l['kind'], []).append(l)
        colours = {}
        for l in kinds[2] + kinds[3]:
            colours[hexc(l['colour'])] = colours.get(hexc(l['colour']), 0) + 1
        sky = [n for n, v in zip(('sphere', 'layers', 'sides', 'floor'), m['modes']) if v]
        rows.append((i, name, m, kinds, colours, sky))
        amb = ','.join(hexc(l['colour']) for l in kinds[0]) or '-'
        dirs = ' '.join(hexc(l['colour']) for l in kinds[1]) or '-'
        pts = len(kinds[2]) + len(kinds[3])
        radii = sorted(set(round(l['radius']) for l in kinds[2] + kinds[3]))
        print('%2d %-16s ambient %-8s directional %d %-24s point %3d %s%s  sky %s  fog %s  clear %s' % (
            i, name, amb, len(kinds[1]), dirs, pts,
            ' '.join('%s x%d' % (c, n) for c, n in sorted(colours.items(), key=lambda x: -x[1])[:5]),
            (' radius %s' % (radii if len(radii) <= 4 else '%d..%d' % (radii[0], radii[-1]))) if pts else '',
            '+'.join(sky) or 'none',
            ('on %s %.0f..%.0f' % (hexc(tuple(int(c * 255) for c in m['fog_colour'][:3])), m['fog'][0], m['fog'][1])) if m['fog_on'] else 'off',
            hexc(tuple(int(c * 255) for c in m['clear'][:3])) if m['clear_on'] else 'off'))
    if '--csv' in sys.argv:
        out = sys.argv[sys.argv.index('--csv') + 1]
        with open(out, 'w') as f:
            f.write('index,map,ambient,directional,point,point_colours,sky,fog,clear\n')
            for i, name, m, kinds, colours, sky in rows:
                f.write('%d,%s,%s,%d,%d,%s,%s,%s,%s\n' % (i, name, ' '.join(hexc(l['colour']) for l in kinds[0]), len(kinds[1]),
                                                          len(kinds[2]) + len(kinds[3]), ' '.join('%s:%d' % kv for kv in colours.items()),
                                                          '+'.join(sky), m['fog_on'], m['clear_on']))


if __name__ == '__main__':
    main()
