"""Re-run the map loaders' reads and checks on a .bfd without the game (recomp/src/load/map_info.c, files.c,
loading.c, frame_loops.c script_processCommandBy, hud_message_box.c), plus the texture / skeleton names the load
looks up (Data/Image*.dat, Data/Skeleton.dat; a missing one is fatal in the game). Independent of bfd.py: it reads
the file the way each loader does (its own file position, sections skipped by their scrambled sizes).

usage: python verify.py test.bfd [map_index]     (map_index: g_mapIndex the file is loaded as; default: valhalla = 0)
"""
import sys, struct, os

GAME = r'C:\Users\Alexander\Desktop\Axis'
problems, notes = [], []


def bad(msg):
    problems.append(msg)


class F:
    """a FILE*, reading scrambled like file_readScrambled (xor 0x59, rotate left 1)"""
    T = bytes(((((x ^ 0x59) << 1) | ((x ^ 0x59) >> 7)) & 0xff) for x in range(256))

    def __init__(self, data):
        self.d, self.o = data, 0

    def read(self, n):          # crt_fread
        b = self.d[self.o:self.o + n]
        self.o += len(b)
        return b

    def rs(self, size, count=1):  # fread_scrambled: short reads past EOF are allowed (fread)
        return self.read(size * count).translate(self.T)

    def u32s(self):
        return struct.unpack('<I', self.rs(4))[0]

    def seek_cur(self, n):
        self.o += n


def i32(b, o):
    return struct.unpack_from('<i', b, o)[0]


def u32(b, o):
    return struct.unpack_from('<I', b, o)[0]


def f32(b, o):
    return struct.unpack_from('<f', b, o)[0]


def norm(s):            # path_normalize
    return s.upper().replace('/', '\\')


def archive_names(path):
    d = open(path, 'rb').read()
    n = struct.unpack_from('<i', d, 0)[0]
    return set(d[4 + i * 0x44:4 + i * 0x44 + 0x40].split(b'\0')[0].decode('latin1') for i in range(n))


TEX = set()
for k in range(6):
    TEX |= archive_names(os.path.join(GAME, 'Data', 'Image%d.dat' % k))
SKEL = archive_names(os.path.join(GAME, 'Data', 'Skeleton.dat'))


def texture(name):
    """tex_getIdByName: the normalized key (< 0x40, its strcpy buffer), its file the part before '*'"""
    key = norm(name)
    if len(key) >= 0x40:
        bad('texture key too long: %s' % key)
    base = key.split('*')[0]
    if base not in TEX:
        bad("can't find texture object (%s) - fatal" % key)
    return key


def main():
    path = sys.argv[1]
    map_index = int(sys.argv[2]) if len(sys.argv) > 2 else 0
    data = open(path, 'rb').read()

    # ---- stage 3: map_loadGroundInfoFrom ----
    f = F(data)
    if struct.unpack('<I', f.read(4))[0] != 0x1201:
        bad('ground: version')
    secs = []
    for k in range(4):
        n = f.u32s(); secs.append((f.o, n)); f.seek_cur(n)
    gdir = f.rs(0x100).split(b'\0')[0].decode('latin1')
    cull = f32(f.rs(4), 0)
    lc = f.u32s(); nxt = f.u32s()
    if lc > 0x400:
        bad('light count %d > 0x400' % lc)
    f.rs(0x2c, lc); f.rs(4)
    clear_on = f.u32s(); f.rs(0x10)
    fog_on = f.u32s(); fogc = struct.unpack('<4f', f.rs(0x10))
    fs, fe, fd = struct.unpack('<3f', f.rs(12))
    sky, lay, side, floor = (f.u32s() for _ in range(4))
    if sky in (1, 2):
        if sky == 2:
            texture(gdir + '/SphereFloor')
        for s in ('SphereCeiling', 'SphereEast', 'SphereSouth', 'SphereWest', 'SphereNorth'):
            texture(gdir + '/' + s)
    if lay in (1, 2):
        if lay == 2:
            texture(gdir + '/SkyInnerLayer')
        texture(gdir + '/SkyOuterLayer')
    if 0 < side <= 2:
        for k in range(6):
            texture('%s/SideLayer%d' % (gdir, k + 1))
    if 0 < floor <= 2:
        for k in range(16):
            texture('%s/FloorAni%02d' % (gdir, k + 1))
    lim = struct.unpack('<12f', f.rs(0x30)); f.rs(4)
    map_number = f.u32s(); music = f.u32s()
    if map_number != map_index:
        bad('mapNumber %d != g_mapIndex %d: "file damaged!"' % (map_number, map_index))
    nl = f.u32s()
    if nl > 4:
        bad('groundLayerCount %d > 4 (groundLayers[4], unchecked: overflow)' % nl)
    pool = 0
    layers = []
    for i in range(nl):
        h = f.rs(0x20c)
        if len(h) < 0x20c:
            bad('layer %d short' % i); break
        texture('%s/Ground%dMap' % (gdir, i))
        img = f.rs(0x300, 0x100)
        kind, rows, cols = i32(h, 0), i32(h, 0x1c), i32(h, 0x20)
        if not (0 < rows <= 255 and 0 < cols <= 255):
            bad('layer %d rows/cols %d/%d outside the 256 x 256 image' % (i, rows, cols))
        pts = (rows + 1) * (cols + 1)
        for n in (pts, rows * cols, pts * 12, pts * 12, pts * 4, pts * 8, (cols + 200) * rows * 2 * 4, (rows * 200 + 4) * 12):
            if pool + n > 4000000:
                bad('layer data heap overflow')
            pool += n
        drawn = 0
        for r in range(rows):
            for c in range(cols):
                px = [img[(r + a) * 0x300 + (c + b) * 3:(r + a) * 0x300 + (c + b) * 3 + 3] for a in (0, 1) for b in (0, 1)]
                drawn += all(p[0] == p[1] == p[2] for p in px)
        layers.append((kind, rows, cols, drawn, i32(h, 0x30), [round(f32(h, 4 + 4 * k)) for k in range(3)]))
    notes.append('ground: dir %r cull %.0f lights %d fog %d (%.0f..%.0f) sky/layer/side/floor %d/%d/%d/%d map %d music %d layers %s pool %d'
                 % (gdir, cull, lc, fog_on, fs, fe, sky, lay, side, floor, map_number, music,
                    ['kind %d %dx%d drawn %d water %d at %s' % l for l in layers], pool))

    # ---- stage 4: map_loadObjectInfoFrom (version, a dword, the count, 0xb0 records in blocks of 56) ----
    f = F(data)
    if struct.unpack('<I', f.read(4))[0] != 0x1201:
        bad('objects: version')
    f.u32s(); count = i32(f.rs(4), 0)
    objs = []
    for i in range(count):
        if i % 56 == 0:
            blk = f.rs(0xb0, 56)
        objs.append(blk[(i % 56) * 0xb0:(i % 56 + 1) * 0xb0])
    if count > 1000:
        bad('objectPool overflow')
    if len(set(o[:0x40] for o in objs)) > 1000:
        bad('object type buffer overflow')
    for i, o in enumerate(objs):
        anim = o[0x4c:0x8c].split(b'\0')[0].decode('latin1')
        if anim:
            sk = norm('Stage/%s/%s' % ('VALHALLA' if map_index == 0 else '?', anim))
            if sk not in SKEL:
                bad('object %d animation skeleton %s missing' % (i, sk))
        fl = i32(o, 0x40)
        if fl & 0x18:
            notes.append('object %d %s flags %#x trigger %d period %d anim %r at %s' % (
                i, o[:0x40].split(b'\0')[0].decode(), fl, i32(o, 0x44), i32(o, 0x48), anim, [round(f32(o, 0x8c + 4 * k)) for k in range(3)]))

    # ---- stage 6: map_loadPlayInfoFrom (version, skip 1, a dword, count, 0x24 records in blocks of 0x71c) ----
    f = F(data)
    f.read(4)
    f.seek_cur(f.u32s()); f.u32s()
    count = i32(f.rs(4), 0)
    starts, items, start0 = [], [], None
    for i in range(count):
        if i % 0x71c == 0:
            blk = f.rs(0x24, 0x71c)
        r = blk[(i % 0x71c) * 0x24:(i % 0x71c + 1) * 0x24]
        k = u32(r, 0)
        if k == 0:
            start0 = r
        elif k == 1:
            starts.append(r)
            if len(starts) > 32:
                bad('numOfMultiPlayStartPoint overflow')
        elif k == 2:
            items.append(r)
            if len(items) > 200:
                bad('numOfItemPoint overflow')
    for i, r in enumerate(items):
        if i32(r, 4) in (24, 34):
            to = i32(r, 8)
            if not 0 <= to < len(items):
                bad('warp item %d leads to %d (no such item)' % (i, to))
            notes.append('warp item %d kind %d -> %d warpPitch %d at %s' % (i, i32(r, 4), to, i32(r, 12), [round(f32(r, 16 + 4 * k)) for k in range(3)]))

    # ---- stage 7: map_loadMissionInfoFrom (version, skip 2, a dword, commands, way points, triggers) ----
    f = F(data)
    f.read(4)
    for k in range(2):
        f.seek_cur(f.u32s())
    f.u32s()
    ncmd = i32(f.rs(4), 0)
    if not 0 <= ncmd <= 10000:
        bad('commandCount %d (commands[10000])' % ncmd)
    cmds = f.rs(0x30, ncmd)
    nwp = i32(f.rs(4), 0)
    if not 0 <= nwp <= 1000:
        bad('wayPointCount %d (wayPoints[1000])' % nwp)
    wps = f.rs(0x14, nwp)
    total, wstart = 0, []
    for i in range(nwp):
        wstart.append(total)
        total += i32(wps, i * 0x14 + 12)
    if total != ncmd:
        bad('mismatch between total num of actor commands %d / %d' % (total, ncmd))
    ntr = i32(f.rs(4), 0)
    if not 0 <= ntr <= 200:
        bad('triggerCount %d (triggers[200], triggerFired[200])' % ntr)
    trs = f.rs(0x1c, ntr)
    total, tstart = 0, []
    for i in range(ntr):
        tstart.append(total)
        n = i32(trs, i * 0x1c)
        if n <= 0:
            bad('trigger %d has no way point (entry 0 would run the next one\'s)' % i)
        total += n
    if total != nwp:
        bad('mismatch between total num of way points %d / %d' % (total, nwp))

    # the commands, as script_processCommandBy would run them (any way point may be run: bots walk them all)
    STAGE_COMMANDS, SPEAKERS, TEXTS = 0xdc0f10, 0x2104fe8, 0x210850c

    def stage_dword(addr):          # only the command table is ours; everything else is "unknown"
        off = (addr - STAGE_COMMANDS) & 0xffffffff
        if off + 4 <= ncmd * 0x30:
            return u32(cmds, off)
        return None

    ops = {}
    for t in range(ntr):
        tr = trs[t * 0x1c:(t + 1) * 0x1c]
        for w in range(tstart[t], tstart[t] + i32(tr, 0)):
            for c in range(wstart[w], wstart[w] + i32(wps, w * 0x14 + 12)):
                cm = cmds[c * 0x30:(c + 1) * 0x30]
                op = u32(cm, 0)
                ops[op] = ops.get(op, 0) + 1
                a = [u32(cm, 4 * k) for k in range(12)]
                if op in (0, 1, 2, 8) and not a[1] < ntr:
                    bad('trigger %d wp %d: command %d trigger index %d' % (t, w, op, a[1]))
                if op in (7, 19, 23):
                    path, point = (a[1], a[2]) if op != 23 else (a[2], a[3])
                    if not (path < ntr and point < i32(trs, path * 0x1c)):
                        bad('command %d path %d point %d out of range' % (op, path, point))
                if op in (15, 16, 17, 22, 23, 24) and not a[1] < 100 and not (op == 24 and a[1] == 0xffffffff):
                    bad('command %d actor %d' % (op, a[1]))
                if op == 15 and a[1] >= 100:
                    bad('command 15 record')
                if op == 26:
                    spk = stage_dword(SPEAKERS + a[1] * 0x88)
                    txt_at = (TEXTS + a[2] * 0x108) & 0xffffffff
                    txt = stage_dword(txt_at)
                    if not spk:
                        bad('command 26: speaker %#x does not reach a non-zero dword of our data: "invalid speaker" (fatal)' % a[1])
                    if not txt:
                        bad('command 26: text %#x does not reach a non-zero dword of our data: "invalid text" (fatal)' % a[2])
                    else:
                        base = (txt_at + 4 - STAGE_COMMANDS) & 0xffffffff
                        lines = []
                        for k in range(4):     # hud_drawMessageBox: strcpy into line[256] from +k*0x41
                            s = cmds[base + k * 0x41: base + k * 0x41 + 256]
                            if b'\0' not in s:
                                bad('message text line %d has no NUL within 256 bytes (stack overflow)' % k)
                            lines.append(s.split(b'\0')[0].decode('latin1').rstrip())
                    if not (i32(cm, 12) < 16 and i32(cm, 12) >= 0):
                        notes.append('command 26 colour %d (>= 16: drawn transparent)' % i32(cm, 12))
                    if a[4] == 0:
                        bad('command 26 4th argument is 0')
                if op == 27:
                    name = cm[4:36]
                    if b'\0' not in name:
                        bad('command 27 name not terminated within its 32 bytes')
                    if a[9] not in (0, 1, 2):
                        notes.append('command 27 mode %d' % a[9])
    for t in range(ntr):
        tr = trs[t * 0x1c:(t + 1) * 0x1c]
        fl = u32(tr, 12)
        if fl or t >= 21:
            w = tstart[t]
            notes.append('trigger %2d: way points %d armed %d flags %d time %.1f radius %.0f fired %d wp0 %s commands %s' % (
                t, i32(tr, 0), i32(tr, 8), fl, f32(tr, 16), f32(tr, 20) * 100, i32(tr, 24),
                [round(f32(wps, w * 0x14 + 4 * k)) for k in range(3)],
                [u32(cmds, c * 0x30) for c in range(wstart[w], wstart[w] + i32(wps, w * 0x14 + 12))][:8]))
    notes.append('command opcodes: %s' % [(k if k < 32 else hex(k), v) for k, v in sorted(ops.items())])

    # ---- stage 7 (mode 0): map_loadActorInfoFrom (version, skip 3, a dword, players, actors) ----
    f = F(data)
    f.read(4)
    for k in range(3):
        f.seek_cur(f.u32s())
    f.u32s()
    npl = i32(f.rs(4), 0)
    if not 0 <= npl <= 16:
        bad('mapPlayerCount %d (mapPlayers[16])' % npl)
    pl = f.rs(0x58, npl)
    nac = i32(f.rs(4), 0)
    if not 0 <= nac <= 100:
        bad('mapActorCount %d (mapActors[100])' % nac)
    ac = f.rs(0x5c, nac)
    for i in range(nac):
        a = ac[i * 0x5c:(i + 1) * 0x5c]
        if not 0 <= i32(a, 0) < npl:
            bad('actor %d player %d' % (i, i32(a, 0)))
        notes.append('spawn record %d: player %d pitch %.1f yaw %.1f scriptFlag %#x' % (i, i32(a, 0), f32(a, 0x10), f32(a, 0x14), u32(a, 0x3c)))

    for n in notes:
        print(n)
    print('PROBLEMS:' if problems else 'OK: no loader check fails', *problems, sep='\n  ')
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
