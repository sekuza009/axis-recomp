"""mkgamedata.py <out.bin>: the part of AxisGL.exe (the installed, patched exe: installed.exe) that AxisRC.exe still
takes from it, so it never reads the exe (see standalone/main.c): its PE header (the sections and the import table
the loader resolves). Nothing of the game's code is in it (step 4, 2026-11-02):
  - .rdata, .data and the data the game keeps in .text and .axnet are C: src/data/ (tools/mkdatasrc.py);
  - no rebuilt function reads code bytes: the calls the patch layer retargets go through its call-site table
    (PATCHED_CALL, Wide.callSite), its other changes are state the rebuilds read (Wide), the energy bar's floats are
    named by address, the ICMP calls go through their import slots (all under AXIS_DIRECT);
  - the patch layer (axisnet_recomp.c, AXIS_STANDALONE) checks no signatures and rewrites no code: the image is the
    installed exe's (code_is / code_put);
  - the rebuilt functions' entries get their jumps from the loader.
(The harness build, recomp.dll in the real game, still reads and rewrites the game's code: its #else branches.)
Out: chunks of { u32 address, u32 length, bytes }, ended by a zero address."""
import struct, sys
R = 'C:/Users/Alexander/Desktop/Axis/recomp/'
b = open(R + 'installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]
hdrsize = struct.unpack_from('<I', b, pe + 24 + 60)[0]
chunks = [(0x400000, b[:hdrsize])]
out = bytearray()
for a, d in chunks: out += struct.pack('<II', a, len(d)) + d
out += struct.pack('<II', 0, 0)
open(sys.argv[1], 'wb').write(out)
print('%d bytes: the header (%d), no code' % (len(out), hdrsize))
