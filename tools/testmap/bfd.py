"""AxisGL .bfd map file: decode / encode.

Layout (recomp/src/load/map_info.c, files.c):
  u32 0x1201 (plain), then everything scrambled byte-wise (read: b = rol1(x ^ 0x59); write: x = ror1(b) ^ 0x59):
  section 1 objects  : u32 size, u32 count, count x ObjectInfo (0xb0)         map_loadObjectInfoFrom
  section 2 play     : u32 size, u32 count, count x 0x24 play records          map_loadPlayInfoFrom (skips 1 section)
  section 3 mission  : u32 size, u32 nCmd, nCmd x 0x30, u32 nWp, nWp x 0x14,  map_loadMissionInfoFrom (skips 2)
                       u32 nTrig, nTrig x 0x1c
  section 4 actors   : u32 size, u32 nPlayers, n x MapPlayer (0x58),          map_loadActorInfoFrom (skips 3)
                       u32 nActors, n x SpawnRecord (0x5c)
  section 5 ground   : (no size) dir[0x100], cullMargin, LightFactors          map_loadGroundInfoFrom (skips 4)
                       (count, nextFree, count x 0x2c, enabled), clearOn, clearColour[4], fogOn, fogColour[4],
                       fogStart, fogEnd, fogDensity, skyMode, layerMode, sideMode, floorMode,
                       levelLow[3], levelHigh[3], worldLow[3], worldHigh[3], unused float, mapNumber, musicKind,
                       layerCount, layerCount x (GroundLayer 0x20c + 256x256 RGB height image 0x30000)
  then whatever trailing bytes the file has (kept as is).
"""
import struct

MAGIC = 0x1201


def unscramble(b):
    t = bytes(((((x ^ 0x59) << 1) | ((x ^ 0x59) >> 7)) & 0xff) for x in range(256))
    return b.translate(t)


def scramble(b):
    t = bytes(((((x >> 1) | (x << 7)) & 0xff) ^ 0x59) for x in range(256))
    return b.translate(t)


class R:
    def __init__(self, d, o=0):
        self.d, self.o = d, o

    def u32(self):
        v = struct.unpack_from('<I', self.d, self.o)[0]
        self.o += 4
        return v

    def raw(self, n):
        v = self.d[self.o:self.o + n]
        if len(v) != n:
            raise ValueError('short read at %#x (%d of %d)' % (self.o, len(v), n))
        self.o += n
        return v


def u32(v):
    return struct.pack('<I', v & 0xffffffff)


class Map:
    pass


def decode(data):
    m = Map()
    m.magic = struct.unpack_from('<I', data, 0)[0]
    if m.magic != MAGIC:
        raise ValueError('version %#x is not 0x1201' % m.magic)
    body = unscramble(data[4:])
    r = R(body)
    # section 1: objects
    s1 = r.u32(); start = r.o
    n = r.u32(); m.objects = [bytearray(r.raw(0xb0)) for _ in range(n)]
    m.sec1_tail = r.raw(start + s1 - r.o)
    # section 2: play info
    s2 = r.u32(); start = r.o
    n = r.u32(); m.play = [bytearray(r.raw(0x24)) for _ in range(n)]
    m.sec2_tail = r.raw(start + s2 - r.o)
    # section 3: mission
    s3 = r.u32(); start = r.o
    n = r.u32(); m.commands = [bytearray(r.raw(0x30)) for _ in range(n)]
    n = r.u32(); m.waypoints = [bytearray(r.raw(0x14)) for _ in range(n)]
    n = r.u32(); m.triggers = [bytearray(r.raw(0x1c)) for _ in range(n)]
    m.sec3_tail = r.raw(start + s3 - r.o)
    # section 4: actors
    s4 = r.u32(); start = r.o
    n = r.u32(); m.players = [bytearray(r.raw(0x58)) for _ in range(n)]
    n = r.u32(); m.actors = [bytearray(r.raw(0x5c)) for _ in range(n)]
    m.sec4_tail = r.raw(start + s4 - r.o)
    # section 5: ground
    g = m.ground = {}
    g['dir'] = r.raw(0x100)
    g['cull'] = r.raw(4)
    lc = r.u32(); g['lightNext'] = r.raw(4)
    g['lights'] = [bytearray(r.raw(0x2c)) for _ in range(lc)]
    g['lightEnabled'] = r.raw(4)
    g['clearOn'] = r.u32(); g['clearColour'] = r.raw(0x10)
    g['fogOn'] = r.u32(); g['fogColour'] = r.raw(0x10)
    g['fogStart'], g['fogEnd'], g['fogDensity'] = r.raw(4), r.raw(4), r.raw(4)
    g['skyMode'], g['layerMode'], g['sideMode'], g['floorMode'] = r.u32(), r.u32(), r.u32(), r.u32()
    g['limits'] = r.raw(0x30)
    g['unused'] = r.raw(4)
    g['mapNumber'] = r.u32(); g['musicKind'] = r.u32()
    n = r.u32()
    g['layers'] = [[bytearray(r.raw(0x20c)), bytearray(r.raw(0x30000))] for _ in range(n)]
    m.trailer = body[r.o:]
    return m


def _sec(b):
    return u32(len(b)) + b


def encode(m):
    s1 = u32(len(m.objects)) + b''.join(m.objects) + m.sec1_tail
    s2 = u32(len(m.play)) + b''.join(m.play) + m.sec2_tail
    s3 = (u32(len(m.commands)) + b''.join(m.commands) + u32(len(m.waypoints)) + b''.join(m.waypoints)
          + u32(len(m.triggers)) + b''.join(m.triggers) + m.sec3_tail)
    s4 = u32(len(m.players)) + b''.join(m.players) + u32(len(m.actors)) + b''.join(m.actors) + m.sec4_tail
    g = m.ground
    s5 = (g['dir'] + g['cull'] + u32(len(g['lights'])) + g['lightNext'] + b''.join(g['lights']) + g['lightEnabled']
          + u32(g['clearOn']) + g['clearColour'] + u32(g['fogOn']) + g['fogColour']
          + g['fogStart'] + g['fogEnd'] + g['fogDensity']
          + u32(g['skyMode']) + u32(g['layerMode']) + u32(g['sideMode']) + u32(g['floorMode'])
          + g['limits'] + g['unused'] + u32(g['mapNumber']) + u32(g['musicKind'])
          + u32(len(g['layers'])) + b''.join(bytes(h) + bytes(img) for h, img in g['layers']))
    body = _sec(s1) + _sec(s2) + _sec(s3) + _sec(s4) + s5 + m.trailer
    return u32(m.magic) + scramble(body)


# ---- field helpers ----
def gi(b, o):
    return struct.unpack_from('<i', b, o)[0]


def gu(b, o):
    return struct.unpack_from('<I', b, o)[0]


def gf(b, o):
    return struct.unpack_from('<f', b, o)[0]


def si(b, o, v):
    struct.pack_into('<i', b, o, v)


def su(b, o, v):
    struct.pack_into('<I', b, o, v & 0xffffffff)


def sf(b, o, v):
    struct.pack_into('<f', b, o, v)


def cstr(b):
    return bytes(b).split(b'\0')[0].decode('latin1')
