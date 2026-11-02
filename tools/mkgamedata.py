"""mkgamedata.py <out.bin>: the parts of AxisGL.exe (the installed, patched exe: installed.exe) that AxisRC.exe needs,
so it no longer reads the exe (see standalone/main.c): its header and, of .text, only the code bytes something still
reads (.rdata, .data and the data the game keeps in .text are C: src/data/, tools/mkdatasrc.py):
  - the bytes around every code address the rebuilds (src/) or the patch layer (axisnet_recomp.c) name: the call
    sites they follow, the instructions the patch layer checks before it changes them;
  - movie_playEnding's start (the patch layer finds it by its bytes).
Out: chunks of { u32 address, u32 length, bytes }, ended by a zero address. Nothing else of the game's code is in
it: the rebuilt functions' entries get their jumps from the loader."""
import struct, sys, re, glob, csv, os
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
# (.rdata, .data and the data the game keeps in .text are C: src/data/, tools/mkdatasrc.py)

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
	if os.path.basename(os.path.dirname(f)) == 'data':
		continue   # (src/data/: the data, its addresses are not code anything reads)
	patch_layer = f.endswith('axisnet_recomp.c')
	t = open(f, encoding='latin-1').read()
	# not read: comments; the call sites the patch layer keeps in its table (g_sites) and the rebuilds reach through
	# it (PATCHED_CALL / PATCHED_THISCALL / PATCHED_BLOCK's site, text_passes8's site argument)
	t = re.sub(r'/\*.*?\*/|//[^\n]*', ' ', t, flags=re.S)
	t = re.sub(r'static CallSite g_sites\[\] = \{.*?\n\};', ' ', t, flags=re.S)
	t = re.sub(r'PATCHED_(?:CALL|THISCALL|BLOCK)\(0x[0-9a-f]+', ' ', t)
	if patch_layer:   # (its call tables, call_is / call_set / call_site: AXIS_STANDALONE asks g_sites)
		t = re.sub(r'\{\s*0x4[0-9a-f]{5},\s*0x4[0-9a-f]{5},', ' ', t)
		t = re.sub(r'call_(?:is|set|site)\(0x4[0-9a-f]{5}(?:,\s*0x4[0-9a-f]{5})?', ' ', t)
		t = re.sub(r'at\[\] = \{0x429cc3, 0x429cf0\}', ' ', t)
	t = re.sub(r'text_passes8\(([^;]*?), 0x4[0-9a-f]{5}\)', r'text_passes8(\1)', t)
	for m in re.findall(r'0x(4[0-9a-f]{5})\b', t):
		a = int(m, 16)
		if text_lo <= a < text_hi and (patch_layer or a not in starts_set):   # (src: a function's entry is only called)
			want.append((a - 32, a + 64))
want.append((0x46c420, 0x46c420 + 64))   # movie_playEnding: found by its bytes
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
print('%d bytes: header %d, .text %d in %d pieces (of %d)' % (len(out), hdrsize, text_bytes, len(merged),
      text_hi - text_lo))
