// gl_emu.h: the game's recorded OpenGL 1.x drawing (standalone/glrec.c's stream, an "AXGLREC1" file) run on the CPU
// into an ordered list of clears and draw batches a modern renderer can execute: the fixed-function state kept
// here (matrix stacks, current colour and texture coordinate, caps, blending, depth, culling, fog, textures),
// primitives assembled into triangles / lines, vertices transformed to clip space (the viewport folded in, y
// flipped and depth mapped to 0..1 for Vulkan-style APIs), fog computed per vertex. No Godot dependency.
#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

struct EmuVertex {
	float pos[4];    // clip space, framebuffer-wide (the viewport applied), y down, z in 0..w
	float col[4];
	float uv[2];
	float fog;       // the fog factor (1: no fog)
	float pad;
};

// what a batch's pipeline depends on
struct EmuPipe {
	uint8_t prim = 0;         // 0 triangles, 1 lines, 2 points
	uint8_t blend = 0;
	uint16_t src = 1, dst = 0;   // GL blend factors
	uint8_t depthTest = 0;
	uint16_t depthFunc = 0x201;
	uint8_t cull = 0;
	uint16_t cullFace = 0x405, frontFace = 0x901;
	uint8_t offset = 0;
	float offsetFactor = 0, offsetUnits = 0;
	bool operator==(const EmuPipe &o) const;
	uint64_t hash() const;
};

struct EmuBatch {
	EmuPipe pipe;
	uint32_t first = 0, count = 0;
	uint32_t texture = 0;      // the GL texture name + 1; 0 untextured
	int minFilter = 0, magFilter = 0, wrapS = 0, wrapT = 0;   // its sampling at this draw (the fixes switch a texture to
	                                                          // nearest for one draw and back: pixel-sharp text)
	uint32_t env = 0x2100;     // the texture environment mode (GL_MODULATE ...)
	uint8_t fog = 0;
	float fogColor[4] = { 0, 0, 0, 0 };
	int scissor[4] = { 0, 0, 0, 0 };   // the viewport, framebuffer pixels, top-left origin
};

struct EmuCmd {
	enum { CLEAR, BATCH } kind;
	uint32_t clearMask = 0;
	float clearColor[4] = { 0, 0, 0, 0 };
	float clearDepth = 1;
	EmuBatch batch;
};

struct EmuTexture {
	std::vector<std::vector<uint8_t>> levels;   // RGBA8 per mip level
	std::vector<std::pair<int, int>> sizes;
	int minFilter = 0x2702, magFilter = 0x2601, wrapS = 0x2901, wrapT = 0x2901;
	uint32_t version = 0;   // bumped when the images change (the renderer remakes its copy); the filters and wrap
	                        // go with each batch instead
	bool mipped = true;   // the minifying filter uses the mip levels (the default GL_NEAREST_MIPMAP_LINEAR does)
	bool complete() const;
};

class GLEmu {
public:
	bool load(const std::string &path, std::string &error);
	int frame_count() const { return (int)frames.size(); }
	void frame_size(int i, int &w, int &h) const { w = frames[i].w; h = frames[i].h; }
	// one frame's commands into verts / cmds (frames in order: the state carries over; restart() to go back)
	void run_frame(int i);
	void restart();

	std::vector<EmuVertex> verts;
	std::vector<EmuCmd> cmds;
	std::unordered_map<uint32_t, EmuTexture> textures;
	uint32_t unknownOps = 0;

private:
	struct Frame { int w, h; long long offset; size_t words; };   // (the words' place in the file)
	std::string path;
	std::vector<uint32_t> data;   // the current frame's words (read from the file as it is run: a 32-bit process
	                              // cannot hold a long recording)
	std::vector<Frame> frames;
	std::vector<std::string> plainNames;
	std::vector<int> plainWords;
	std::vector<int> plainKind;   // which handler, by name

	// the state
	float mats[3][32][16];
	int depth[3], mode;
	float color[4], texcoord[2];
	bool texture2d, blend, depthTest, cull, fog, polyOffset;
	uint32_t blendSrc, blendDst, depthFunc, cullFace, frontFace, envMode, bound;
	uint32_t fogMode;
	float fogColor[4], fogStart, fogEnd, fogDensity, offsetFactor, offsetUnits;
	float clearColor[4], clearDepth;
	int viewport[4];
	int unpackAlign;
	int fbW, fbH;
	// glBegin .. glEnd
	int beginMode = -1;
	struct ObjVertex { float p[4]; float c[4]; float t[2]; };
	std::vector<ObjVertex> immediate;

	float *top() { return mats[mode][depth[mode]]; }
	void vertex(float x, float y, float z, float w);
	void assemble(int glMode, const std::vector<ObjVertex> &v, const uint32_t *index, size_t n);
	EmuVertex transform(const ObjVertex &v) const;
	void emit(int prim, const EmuVertex *v, int n);
	void plain(int kind, const uint32_t *a);
	void tex_image(uint32_t level, int w, int h, uint32_t fmt, uint32_t type, const uint8_t *p, size_t n);
	void tex_param(uint32_t pname, int v);
};
