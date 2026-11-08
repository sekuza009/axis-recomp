"""Make a test copy of a shipped AxisGL mission map (default: valhalla.bfd, map 0 / skirmish stage 1) whose data
exercises map features no shipped map uses. The source is only read; the result is written to a new file.

usage: python mkmap.py [source.bfd] [out.bfd] [--no-tex-trick] [--roundtrip-only]

What is added (see README.txt): a time trigger and an approach trigger, way-point / script commands 4, 10-14, 23,
24, 25, 26 (MESSAGE, 38 of them over time), 27 (scene path, modes 1 and 2), a bot path, spawn records with pitch / yaw /
scriptFlag, fog, floor mode 2, three ground layers, three animated map objects (flag 8 and flag 0x10), and a pair of
warp-zone items with warp pitches. Positions are for valhalla.bfd.
"""
import sys, os, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from bfd import *

# ---- Stage layout (recomp/src/scene.fields; checked against the original's case 26: in_ECX + 0x2104fe8 + n * 0x88) ----
STAGE_COMMANDS = 0xdc0f10      # u8 commands[10000][0x30]
STAGE_SPEAKERS = 0x2104fe8     # u8 speakers[100][0x88]   (never written by the game: always 0)
STAGE_TEXTS = 0x210850c        # u8 texts[1000][0x108]    (never written by the game: always 0)
SPEAKER_STRIDE, TEXT_STRIDE = 0x88, 0x108

SPACES = 0x20202020


def wrap_index(target, base, stride):
    """the u32 index n with base + n * stride == target (mod 2^32): the game indexes speakers / texts with the
    command's raw dword in 32-bit arithmetic, so an index past the array reaches any 8-aligned address of the stage"""
    delta = (target - base) & 0xffffffff
    assert stride % 8 == 0 and (stride // 8) % 2 == 1
    if delta % 8:
        raise ValueError('target %#x not reachable from %#x with stride %#x' % (target, base, stride))
    q = stride // 8
    n = (delta // 8) * pow(q, -1, 1 << 29) % (1 << 29)
    assert (n * stride) & 0xffffffff == delta
    return n


def fbits(x):
    return struct.unpack('<I', struct.pack('<f', x))[0]


def cmd(op, *args):
    """a 0x30-byte command: the opcode and up to 11 dwords (ints, floats as their bits, or bytes spread over dwords)"""
    b = bytearray(0x30)
    su(b, 0, op)
    o = 4
    for a in args:
        if isinstance(a, float):
            su(b, o, fbits(a)); o += 4
        elif isinstance(a, (bytes, bytearray)):
            b[o:o + len(a)] = a; o += len(a)
        else:
            su(b, o, a); o += 4
    assert o <= 0x30
    return b


class MsgCmd(bytearray):
    """a MESSAGE command whose speaker / text indices are filled in once the commands are laid out"""
    block = None


def scene_cmd(name, mode):
    nm = name.encode('ascii')
    assert len(nm) < 32
    return cmd(27, nm.ljust(32, b'\0'), mode)


# ---- the mission section as triggers -> way points -> commands ----
class WP:
    def __init__(self, pos, cmds=None, rec=None):
        self.rec = bytearray(rec) if rec else bytearray(0x14)
        sf(self.rec, 0, pos[0]); sf(self.rec, 4, pos[1]); sf(self.rec, 8, pos[2])
        self.cmds = cmds or []


class Trig:
    def __init__(self, armed=0, flags=0, time=0.0, radius=0.0, fired=0, wps=None, rec=None, name=''):
        self.rec = bytearray(rec) if rec else bytearray(0x1c)
        if rec is None:
            si(self.rec, 8, armed); su(self.rec, 12, flags); sf(self.rec, 16, time); sf(self.rec, 20, radius); si(self.rec, 24, fired)
        self.wps = wps or []
        self.name = name


def mission_split(m):
    trigs, w, c = [], 0, 0
    for t in m.triggers:
        tr = Trig(rec=t, name='shipped')
        for _ in range(gi(t, 0)):
            wr = m.waypoints[w]; w += 1
            n = gi(wr, 12)
            wp = WP((gf(wr, 0), gf(wr, 4), gf(wr, 8)), [bytearray(x) for x in m.commands[c:c + n]], rec=wr)
            c += n
            tr.wps.append(wp)
        trigs.append(tr)
    assert w == len(m.waypoints) and c == len(m.commands), 'mission runs do not add up'
    return trigs


def mission_join(m, trigs):
    m.commands, m.waypoints, m.triggers = [], [], []
    for t in trigs:
        si(t.rec, 0, len(t.wps)); su(t.rec, 4, 0)            # count; the pointer is set at load
        m.triggers.append(t.rec)
        for wp in t.wps:
            si(wp.rec, 12, len(wp.cmds)); su(wp.rec, 16, 0)
            m.waypoints.append(wp.rec)
            m.commands.extend(wp.cmds)


def global_cmd_index(trigs, ti, wi):
    n = 0
    for i, t in enumerate(trigs):
        for j, wp in enumerate(t.wps):
            if (i, j) == (ti, wi):
                return n
            n += len(wp.cmds)
    raise KeyError


# ---- message texts kept in the command table (a never-run way point), 6 commands = 0x120 bytes per block ----
TEXTS = [
    ['AXIS TEST MAP (valhalla)', 'TIME TRIGGER FIRED (trigger 21, match clock 20 s)', 'commands 23, 24, 26, 27 mode 1', 'message slot 4th arg 7'],
    ['APPROACH TRIGGER FIRED (trigger 22)', 'player within 6000 of the arena centre', 'commands 23, 24, 26, 27 mode 2', ''],
    ['MESSAGE CHAIN  A', 'one of 36 timed triggers (24 .. 59), 2 s apart', 'ring of 32: msgRead moves on after 32', ''],
    ['MESSAGE CHAIN  B', 'colour index = trigger number % 17', '16: drawn transparent', ''],
    ['MESSAGE CHAIN  C (last: commands 25 + 26)', 'held actor let go (command 25)', '', ''],
]


def text_blocks():
    out = []
    for lines in TEXTS:
        blk = bytearray(struct.pack('<I', SPACES))          # the data command's opcode word (no-op: > 31)
        blk += b'TXT '                                      # the text block's "exists" dword (not 0)
        for k in range(4):
            s = lines[k].encode('ascii')
            assert len(s) <= 0x40 and b'$' not in s
            blk += s.ljust(0x40, b' ') + b'\0'
        blk += b' ' * (0x120 - len(blk))
        assert len(blk) == 0x120
        out += [bytearray(blk[i:i + 0x30]) for i in range(0, 0x120, 0x30)]
    # every command's opcode word must be a no-op (> 31) should anything ever run them
    assert all(gu(c, 0) > 31 for c in out)
    return out


# ---- ground layer images (256 x 256 RGB; grey pixels are heights, others: height 0 and the cell not drawn) ----
def layer_image(rows, cols, bump, hole):
    img = bytearray(0x30000)
    cr, cc = rows / 2, cols / 2
    for r in range(256):
        for c in range(256):
            if r <= rows and c <= cols:
                d = max(abs(r - cr) / max(cr, 1), abs(c - cc) / max(cc, 1))
                g = int(round(bump * max(0.0, 1.0 - d)))
            else:
                g = 0
            o = r * 0x300 + c * 3
            img[o:o + 3] = bytes((g, g, g))
    for (r, c) in hole:                                     # a red pixel: the cells around it are not drawn
        o = r * 0x300 + c * 3
        img[o:o + 3] = b'\xff\x00\x00'
    return img


def layer_header(kind, origin, rows, cols, cell, hscale, texscale, water):
    h = bytearray(0x20c)
    si(h, 0, kind)
    for k in range(3):
        sf(h, 4 + 4 * k, origin[k])
    hi = (origin[0] + cols * cell, origin[1], origin[2] + rows * cell)   # (the shipped layers keep the far corner here)
    for k in range(3):
        sf(h, 0x10 + 4 * k, hi[k])
    si(h, 0x1c, rows); si(h, 0x20, cols)
    sf(h, 0x24, cell); sf(h, 0x28, hscale); sf(h, 0x2c, texscale); si(h, 0x30, water)
    return h


CENTRE = (800.8, 39100.0, 3447.4)          # valhalla\dom\ring-00, the arena centre


def build(m, tex_trick=True):
    log = []
    # ---------------- mission ----------------
    trigs = mission_split(m)
    nship = len(trigs)
    # bot commands on the shipped (bot navigation) way points: run with the bot as the actor when it reaches them
    for t in trigs:
        for j, wp in enumerate(t.wps):
            wp.cmds.append(cmd(11))                         # scriptFlag 1
            if j % 4 == 1:
                wp.cmds.append(cmd(14))                     # invulnerable
            elif j % 4 == 3:
                wp.cmds.append(cmd(4, 2.0))                 # botWait 2 s
            elif j % 8 == 6:
                wp.cmds.append(cmd(12))                     # reset: wait, invulnerable, look / follow
    log.append('shipped triggers 0..%d: commands 11 / 14 / 4 / 12 added to their %d way points' % (nship - 1, sum(len(t.wps) for t in trigs)))

    T_TIME, T_APPROACH, T_BOTPATH = nship, nship + 1, nship + 2
    T_CHAIN0, NCHAIN = nship + 3, 36
    T_DATA = T_CHAIN0 + NCHAIN
    HIGH = 90000.0                                          # way points no bot can reach (path candidates need 1500 on each axis)

    def msg(block, colour, d):                              # the speaker / text indices are filled in once laid out
        c = MsgCmd(cmd(26, 0, 0, colour, d))
        c.block = block
        return c

    t_time = Trig(armed=1, flags=1, time=20.0, wps=[WP((CENTRE[0], HIGH, CENTRE[2]), [
        cmd(23, 1, T_BOTPATH, 0),                           # actor 1 (the first bot) walks the bot path
        msg(0, 2, 7),
        scene_cmd('TestSceneHold', 1),                      # scriptMode 1, scriptHoldsPlay 1 (one frame)
        cmd(24, 2, 3, 1),                                   # actor 2 held out of play (outOfPlay 1), mode 3
    ])], name='time')
    t_app = Trig(armed=1, flags=2, radius=60.0, wps=[WP((CENTRE[0], 36500.0, CENTRE[2]), [
        msg(1, 5, 11),
        cmd(23, 1, T_BOTPATH, 0),
        cmd(24, 2, 4, 2),                                   # actor 2 held (again), value 2
        scene_cmd('TestSceneApproach', 2),                  # scriptMode 2
    ])], name='approach')
    # the bot path: three points copied from shipped way points near the centre (76, 78, 79)
    t_bot = Trig(armed=0, flags=0, wps=[
        WP((676.8, 39369.0, 2813.0), [cmd(11), cmd(14), cmd(4, 3.0)]),
        WP((3285.7, 38769.0, 3150.1), [cmd(10), cmd(13, 60.0)]),
        WP((5975.8, 38169.0, 3927.0), [cmd(12), cmd(11)]),
    ], name='botpath')
    chain = []
    for k in range(NCHAIN):
        cmds = [msg(2 + (k % 2) if k < NCHAIN - 1 else 4, (T_CHAIN0 + k) % 17, k + 1)]
        if k == NCHAIN - 1:
            cmds.insert(0, cmd(25))                         # the held actor let go
        chain.append(Trig(armed=1, flags=1, time=30.0 + 2.0 * k, wps=[WP((CENTRE[0] + 100.0 * k, HIGH, CENTRE[2]), cmds)], name='chain%d' % k))
    data = text_blocks()
    t_data = Trig(armed=0, flags=0, wps=[WP((CENTRE[0], HIGH + 5000.0, CENTRE[2]), data)], name='textdata')
    trigs += [t_time, t_app, t_bot] + chain + [t_data]
    assert len(trigs) - 1 == T_DATA

    # the MESSAGE indices: speaker -> the first data command's opcode word (0x20202020), text k -> block k's "TXT " word
    d0 = global_cmd_index(trigs, T_DATA, 0)
    spk = wrap_index(STAGE_COMMANDS + 0x30 * d0, STAGE_SPEAKERS, SPEAKER_STRIDE)
    nmsg = 0
    for t in trigs:
        for wp in t.wps:
            for c in wp.cmds:
                if isinstance(c, MsgCmd):
                    txt = wrap_index(STAGE_COMMANDS + 0x30 * (d0 + 6 * c.block) + 4, STAGE_TEXTS, TEXT_STRIDE)
                    su(c, 4, spk); su(c, 8, txt)
                    nmsg += 1
    mission_join(m, trigs)
    log.append('triggers %d time (20 s), %d approach (radius 6000 at %s), %d bot path, %d..%d message chain (30..%d s), %d text data'
               % (T_TIME, T_APPROACH, (CENTRE[0], 36500.0, CENTRE[2]), T_BOTPATH, T_CHAIN0, T_CHAIN0 + NCHAIN - 1, 30 + 2 * (NCHAIN - 1), T_DATA))
    log.append('MESSAGE commands: %d, speaker index %#x, data commands from %d' % (nmsg, spk, d0))

    # ---------------- actors: spawn records with pitch, yaw, scriptFlag ----------------
    for i, (pitch, yaw, flag) in ((1, (30.0, 450.0, 0x5a)), (2, (-20.0, 1350.0, 2))):
        if i < len(m.actors):
            a = m.actors[i]
            sf(a, 0x10, pitch); sf(a, 0x14, yaw); su(a, 0x3c, flag)
    log.append('spawn records 1, 2: pitch 30 / -20, yaw 450 / 1350, scriptFlag 0x5a / 2')

    # ---------------- objects: proximity (flag 8) and timed (flag 0x10) animated ones ----------------
    base = next(o for o in m.objects if cstr(o[:0x40]).lower() == 'valhalla\\addon\\ribet')
    def obj(pos, flags, trigger, period, anim):
        o = bytearray(base)
        si(o, 0x40, flags); si(o, 0x44, trigger); si(o, 0x48, period)
        o[0x4c:0x8c] = anim.encode('ascii').ljust(0x40, b'\0')
        for k in range(3):
            sf(o, 0x8c + 4 * k, pos[k])
        return o
    first_obj = len(m.objects)
    m.objects += [
        obj((676.8, 39400.0, 2813.0), 8, 15, 1000, 'L-RING-1'),      # starts when an actor is within 1500, back when all leave
        obj((CENTRE[0], 39600.0, CENTRE[2] + 800.0), 0x10, 0, 1000, 'S-RING-1'),   # no wait: forwards, backwards, again
        obj((CENTRE[0], 39600.0, CENTRE[2] - 800.0), 0x10, 1, 2000, 'L-RING-1'),   # waits 100 s (trigger 1 x 100)
    ]
    log.append('objects %d (flag 8, radius 1500), %d (flag 0x10, wait 0), %d (flag 0x10, wait 100 s)' % (first_obj, first_obj + 1, first_obj + 2))

    # ---------------- play info: a warp-zone pair (kind 34) with warp pitches ----------------
    nitems = sum(1 for p in m.play if gu(p, 0) == 2)
    def item(kind, warp_to, warp_pitch, pos, pitch, angle):
        p = bytearray(0x24)
        su(p, 0, 2); si(p, 4, kind); si(p, 8, warp_to); si(p, 12, warp_pitch)
        for k in range(3):
            sf(p, 16 + 4 * k, pos[k])
        sf(p, 28, pitch); sf(p, 32, angle)
        return p
    A, B = nitems, nitems + 1
    m.play += [item(34, B, -10, (3285.7, 38621.0, 3150.1), 0.0, 0.0),        # over shipped way point 78
               item(34, A, 15, (-8779.7, 39021.0, 14149.2), 0.0, 45.0)]      # over shipped way point 0
    log.append('items %d / %d: warp zones (kind 34) to each other, warpPitch -10 / 15' % (A, B))

    # ---------------- ground: fog, floor mode 2, layers ----------------
    g = m.ground
    g['fogOn'] = 1
    g['fogColour'] = struct.pack('<4f', 0.35, 0.40, 0.55, 1.0)
    g['fogStart'], g['fogEnd'] = struct.pack('<f', 20000.0), struct.pack('<f', 60000.0)
    log.append('fog on (start 20000, end 60000)')
    if tex_trick:
        d = cstr(g['dir'])
        nd = d + '/SphereFloor*'
        assert len(nd) < 0x40
        g['dir'] = nd.encode('ascii').ljust(0x100, b'\0')
        g['floorMode'] = 2
        g['layers'] = [
            [layer_header(0, (CENTRE[0] - 2400.0, 50000.0, CENTRE[2] - 2400.0), 16, 16, 300.0, 8.0, 2000.0, 0),
             layer_image(16, 16, 100, [(8, 8), (8, 9)])],
            [layer_header(1, (CENTRE[0] + 4000.0, 52000.0, CENTRE[2] - 1600.0), 8, 8, 400.0, 10.0, 2000.0, 0),
             layer_image(8, 8, 60, [])],
            [layer_header(2, (-100000.0, 20000.0, -100000.0), 10, 10, 20000.0, 0.0, 5000.0, 1),
             layer_image(10, 10, 0, [])],
        ]
        log.append('texture dir %r (every ground-file texture is SphereFloor); floor mode 2; 3 ground layers (kinds 0, 1, 2 + water)' % nd)
    return log


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    src = args[0] if args else r'C:\Users\Alexander\Desktop\Axis\Map\valhalla.bfd'
    out = args[1] if len(args) > 1 else os.path.join(os.path.dirname(os.path.abspath(__file__)), 'test.bfd')
    if os.path.abspath(out).lower() == os.path.abspath(src).lower():
        sys.exit('refusing to overwrite the source')
    if os.path.abspath(out).lower().startswith(r'c:\users\alexander\desktop\axis'):
        sys.exit('refusing to write into the game folder')
    data = open(src, 'rb').read()
    m = decode(data)
    rt = encode(m) == data
    print('round trip of %s: %s' % (src, 'identical' if rt else 'DIFFERENT'))
    if not rt:
        sys.exit(1)
    if '--roundtrip-only' in sys.argv:
        return
    for line in build(m, tex_trick='--no-tex-trick' not in sys.argv):
        print(' ', line)
    out_data = encode(m)
    m2 = decode(out_data)
    assert encode(m2) == out_data
    open(out, 'wb').write(out_data)
    print('wrote %s (%d bytes)' % (out, len(out_data)))


if __name__ == '__main__':
    main()
