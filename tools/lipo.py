"""lipo.py <out> <in>...: Mach-O files of different processors (x86-64, arm64) joined into one universal ("fat") file, as
Apple's lipo -create does - the fat header (big-endian: magic, count; per file its CPU type and subtype, offset, size
and alignment), then each file at a 16 KB boundary. For the macOS builds made on other systems (zig has no lipo)."""
import struct, sys

out, ins = sys.argv[1], sys.argv[2:]
ALIGN = 14   # (2^14: Apple Silicon's page size)
slices = []
for p in ins:
    d = open(p, 'rb').read()
    magic, cputype, cpusub = struct.unpack_from('<III', d)
    if magic != 0xfeedfacf:
        sys.exit('%s: not a 64-bit Mach-O file' % p)
    slices.append((cputype, cpusub & 0x00ffffff, d))
off = 1 << ALIGN
head = struct.pack('>II', 0xcafebabe, len(slices))
body = b''
for cputype, cpusub, d in slices:
    head += struct.pack('>iiIII', cputype, cpusub, off + len(body), len(d), ALIGN)
    body += d + b'\0' * ((-len(d)) % (1 << ALIGN))
open(out, 'wb').write(head + b'\0' * (off - len(head)) + body)
print('%s: %d processors, %d bytes' % (out, len(slices), off + len(body)))
