// emu_test.cpp: gl_emu run over a recorded stream on the console - per frame its clears, batches and vertices,
// and any op it does not know. Build: zig c++ -O2 -I../src emu_test.cpp ../src/gl_emu.cpp -o emu_test.exe
#include "gl_emu.h"
#include <cstdio>

int main(int argc, char **argv) {
	if (argc < 2) { printf("usage: emu_test <file.glrec>\n"); return 1; }
	GLEmu emu;
	std::string err;
	if (!emu.load(argv[1], err)) { printf("load: %s\n", err.c_str()); return 1; }
	size_t maxVerts = 0, maxBatches = 0, totalBatches = 0;
	for (int i = 0; i < emu.frame_count(); i++) {
		emu.run_frame(i);
		size_t batches = 0, clears = 0;
		for (const EmuCmd &c : emu.cmds) (c.kind == EmuCmd::BATCH ? batches : clears)++;
		totalBatches += batches;
		if (emu.verts.size() > maxVerts) maxVerts = emu.verts.size();
		if (batches > maxBatches) maxBatches = batches;
		if (i < 3 || i % 500 == 0) {
			int w, h;
			emu.frame_size(i, w, h);
			printf("frame %d (%dx%d): %zu clears, %zu batches, %zu vertices, %zu textures, unknown ops %u\n", i, w, h, clears, batches,
			       emu.verts.size(), emu.textures.size(), emu.unknownOps);
		}
	}
	printf("%d frames: at most %zu batches and %zu vertices a frame, %zu batches in all; unknown ops %u\n", emu.frame_count(),
	       maxBatches, maxVerts, totalBatches, emu.unknownOps);
	return 0;
}
