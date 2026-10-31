"""mkgamedata.py <out.bin>: the parts of AxisGL.exe (the installed, patched exe: installed.exe) that AxisRC.exe needs,
so it no longer reads the exe (see standalone/main.c): its header, .rdata, .data's initialised part, and of .text
only what anything still reads there:
  - the bytes around every code address the rebuilds (src/) or the patch layer (axisnet_recomp.c) name: the call
    sites they follow, the instructions the patch layer checks before it changes them;
  - movie_playEnding's start (the patch layer finds it by its bytes);
  - data stored between functions that .rdata / .data point at (dinput's object formats at 0x44f950).
Out: chunks of { u32 address, u32 length, bytes }, ended by a zero address. Nothing else of the game's code is in
it: the rebuilt functions' entries get their jumps from the loader."""
import struct, sys, re, glob, csv
R = 'C:/Users/Alexander/Desktop/Axis/recomp/'
b = open(R + 'installed.exe', 'rb').read()
pe = struct.unpack_from('<I', b, 0x3c)[0]; nsec = struct.unpack_from('<H', b, pe + 6)[0]; opt = struct.unpack_from('<H', b, pe + 20)[0]
hdrsize = struct.unpack_from('<I', b, pe + 24 + 60)[0]
secs = {}
for i in range(nsec):
	nm, vs, va, rs, rp = struct.unpack_from('<8sIIII', b, pe + 24 + opt + 40 * i)
	secs[nm.rstrip(b'\0').decode()] = (0x400000 + va, vs, rs, rp)
def raw(a, n):
	for base, vs, rs, rp in secs.values():
		if base <= a and a + n <= base + rs: return b[rp + a - base: rp + a - base + n]
	raise ValueError(hex(a))

chunks = [(0x400000, b[:hdrsize])]
for name in ('.rdata', '.data'):
	base, vs, rs, rp = secs[name]
	data = b[rp:rp + min(rs, vs)]
	chunks.append((base, data.rstrip(b'\0') if name == '.data' else data))

text_lo, text_hi = secs['.text'][0], secs['.text'][0] + secs['.text'][1]
funcs = sorted((int(r['address'], 16), int(r['size'])) for r in csv.DictReader(open(R + '../decomp/out/functions.csv')))
starts = [a for a, _ in funcs]
def inside_function(a):
	import bisect
	k = bisect.bisect_right(starts, a) - 1
	return k >= 0 and starts[k] <= a < starts[k] + funcs[k][1]
want = []
# code addresses named in src/ and in the patch layer
starts_set = set(starts)
for f in glob.glob(R + 'src/**/*.[ch]', recursive=True) + [R + 'axisnet_recomp.c']:
	patch_layer = f.endswith('axisnet_recomp.c')
	for m in re.findall(r'0x(4[0-9a-f]{5})\b', open(f, encoding='latin-1').read()):
		a = int(m, 16)
		if text_lo <= a < text_hi and (patch_layer or a not in starts_set):   # (src: a function's entry is only called)
			want.append((a - 32, a + 64))
want.append((0x46c420, 0x46c420 + 64))   # movie_playEnding: found by its bytes
# data between functions pointed at from .rdata / .data (not the entries the loader jumps from: the hook table,
# with the compiler's jump stubs, build/standalone_hooks.c from tools/mkhooks.py)
entries = {int(a, 16) for a in re.findall(r'\{ 0x([0-9a-f]+), \(void \*\)', open(R + 'build/standalone_hooks.c').read())}
for name in ('.rdata', '.data'):
	base, vs, rs, rp = secs[name]
	for o in range(0, min(rs, vs) - 3, 4):
		v = struct.unpack_from('<I', b, rp + o)[0]
		if text_lo <= v < text_hi and v not in starts and v not in entries and not inside_function(v):
			nxt = next((s for s in starts if s > v), text_hi)
			want.append((v, nxt))   # (to the next function: dinput's keyboard objects are 4 KB)
want.sort()
merged = []
for lo, hi in want:
	lo, hi = max(lo, text_lo), min(hi, text_hi)
	if merged and lo <= merged[-1][1]: merged[-1][1] = max(merged[-1][1], hi)
	else: merged.append([lo, hi])
for lo, hi in merged: chunks.append((lo, raw(lo, hi - lo)))
out = bytearray()
for a, d in chunks: out += struct.pack('<II', a, len(d)) + d
out += struct.pack('<II', 0, 0)
open(sys.argv[1], 'wb').write(out)
text_bytes = sum(hi - lo for lo, hi in merged)
print('%d bytes: header %d, .rdata %d, .data %d (initialised), .text %d in %d pieces (of %d)' % (len(out), hdrsize,
      len(chunks[1][1]), len(chunks[2][1]), text_bytes, len(merged), text_hi - text_lo))
