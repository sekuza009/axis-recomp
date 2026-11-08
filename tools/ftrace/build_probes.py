"""build_probes.py: the record probes (tools/ftrace/probe.c) put into the function-trace build: copies of the source
files below with a probe_record() call added at each place, compiled as tools/ftrace/build.sh compiles src/ (over
the same object names in build/obj_ftrace), and probe.c itself. Run after tools/ftrace/build.sh and before
build_both.sh (which links every object in build/obj_ftrace). src/ is not changed."""
import os, subprocess, sys

R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..')
os.chdir(R)
O = 'build/obj_ftrace'
DECL = 'void probe_record(const char *type, const void *p, int size);\n'
PROBES = {
	'src/net/network.c': [
		('static void send_packet(u8 *s, u8 *packet)\n{\n', 'probe_record("pkt", packet, 0x40);\n', 1),
		('void THISCALL (net_processGamePacket)(u8 *g, u32 from, int size, const char *pkt)\n{\n\tif (size != 0x40)\n\t\treturn;\n',
		 'probe_record("pkt", pkt, 0x40);\n', 1),
		('\tconst DPSessionDesc2 *dd = (const DPSessionDesc2 *)desc;\n', 'if (dd) probe_record("DPSessionDesc2", dd, sizeof *dd);\n', 1),
	],
	'src/match/frame_loops.c': [
		('\tconst ParticleDesc *pd = (const ParticleDesc *)desc;\n', 'probe_record("ParticleDesc", pd, sizeof *pd);\n', 2),
		('void THISCALL (object_initObjectBy)(Stage *s, int i, const ObjectInfo *info)\n{\n', 'probe_record("ObjectInfo", info, sizeof *info);\n', 1),
	],
	'src/app/classes.c': [
		('\tint iw = bmp->width, ih = bmp->height;\n', 'probe_record("BmpFile", bmp, sizeof *bmp);\n', 1),
	],
}
CC = ['python', '-m', 'ziglang', 'cc', '-target', 'x86-windows-gnu']
FLAGS = ['-c', '-O2', '-finstrument-functions', '-mno-sse', '-mno-sse2', '-mfpmath=387', '-fno-builtin',
         '-fno-strict-aliasing', '-w', '-DAXIS_DIRECT', '-DAXIS_NATIVE', '-Ibuild']
for path, edits in PROBES.items():
	t = open(path, encoding='latin-1', newline='').read()
	if '\r\n' in t:   # (CRLF files: the anchors in their line endings)
		edits = [(a.replace('\n', '\r\n'), c.replace('\n', '\r\n'), n) for a, c, n in edits]
	for anchor, call, count in edits:
		if t.count(anchor) != count:
			sys.exit('%s: the anchor is there %d times, not %d: %r' % (path, t.count(anchor), count, anchor[:60]))
		t = t.replace(anchor, anchor + '\t' + call)
	i = t.index('#include "../game.h"') + len('#include "../game.h"')
	t = t[:i] + '\n' + DECL.rstrip('\n') + t[i:]
	# (the copy sits beside the original for its includes, and is removed whatever happens)
	copy = os.path.join(os.path.dirname(path), 'probe_tmp_' + os.path.basename(path))
	obj = os.path.join(O, path[len('src/'):].replace('/', '_')[:-2] + '.o')
	try:
		open(copy, 'w', encoding='latin-1', newline='').write(t)
		r = subprocess.run(CC + FLAGS + ['-o', obj, copy])
	finally:
		if os.path.exists(copy):
			os.remove(copy)
	if r.returncode:
		sys.exit('compile failed: ' + path)
	print('probed', path)
r = subprocess.run(CC + ['-c', '-O2', '-Wall', '-o', os.path.join(O, 'probe_rt.o'), 'tools/ftrace/probe.c'])
if r.returncode:
	sys.exit('probe.c failed')
print('probes in', O)
