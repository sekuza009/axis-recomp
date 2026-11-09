// gl_emu.cpp: see gl_emu.h. The stream's layout is standalone/glrec.c's: each command a header word (op | words
// << 16) and its words; ops 0 .. 39 the plain calls (named by the file's table), 64 .. the ones with data.
#include "gl_emu.h"

#include <cmath>
#include <cstdio>
#include <cstring>

namespace {

enum Plain {   // the plain calls this emulates, by name (the file's table gives each op's name)
	P_UNKNOWN, P_BEGIN, P_BINDTEXTURE, P_BLENDFUNC, P_CLEAR, P_CLEARCOLOR, P_CLEARDEPTH, P_COLOR3UB, P_COLOR4F,
	P_COLOR4UB, P_CULLFACE, P_DEPTHFUNC, P_DISABLE, P_DISABLECLIENT, P_ENABLE, P_ENABLECLIENT, P_END, P_FOGF, P_FOGI,
	P_FRONTFACE, P_HINT, P_LOADIDENTITY, P_MATRIXMODE, P_POLYGONMODE, P_POLYGONOFFSET, P_POPMATRIX, P_PUSHMATRIX,
	P_ROTATEF, P_SCALEF, P_TEXCOORD2D, P_TEXCOORD2F, P_TEXCOORD2I, P_TEXENVF, P_TEXPARAMETERF, P_TRANSLATEF,
	P_VERTEX2I, P_VERTEX3F, P_VIEWPORT, P_LOOKAT, P_ORTHO2D, P_PERSPECTIVE
};
const struct { const char *name; Plain kind; } k_names[] = {
	{ "glBegin", P_BEGIN }, { "glBindTexture", P_BINDTEXTURE }, { "glBlendFunc", P_BLENDFUNC }, { "glClear", P_CLEAR },
	{ "glClearColor", P_CLEARCOLOR }, { "glClearDepth", P_CLEARDEPTH }, { "glColor3ub", P_COLOR3UB },
	{ "glColor4f", P_COLOR4F }, { "glColor4ub", P_COLOR4UB }, { "glCullFace", P_CULLFACE }, { "glDepthFunc", P_DEPTHFUNC },
	{ "glDisable", P_DISABLE }, { "glDisableClientState", P_DISABLECLIENT }, { "glEnable", P_ENABLE },
	{ "glEnableClientState", P_ENABLECLIENT }, { "glEnd", P_END }, { "glFogf", P_FOGF }, { "glFogi", P_FOGI },
	{ "glFrontFace", P_FRONTFACE }, { "glHint", P_HINT }, { "glLoadIdentity", P_LOADIDENTITY },
	{ "glMatrixMode", P_MATRIXMODE }, { "glPolygonMode", P_POLYGONMODE }, { "glPolygonOffset", P_POLYGONOFFSET },
	{ "glPopMatrix", P_POPMATRIX }, { "glPushMatrix", P_PUSHMATRIX }, { "glRotatef", P_ROTATEF }, { "glScalef", P_SCALEF },
	{ "glTexCoord2d", P_TEXCOORD2D }, { "glTexCoord2f", P_TEXCOORD2F }, { "glTexCoord2i", P_TEXCOORD2I },
	{ "glTexEnvf", P_TEXENVF }, { "glTexParameterf", P_TEXPARAMETERF }, { "glTranslatef", P_TRANSLATEF },
	{ "glVertex2i", P_VERTEX2I }, { "glVertex3f", P_VERTEX3F }, { "glViewport", P_VIEWPORT }, { "gluLookAt", P_LOOKAT },
	{ "gluOrtho2D", P_ORTHO2D }, { "gluPerspective", P_PERSPECTIVE },
};
enum { OP_COLOR4UBV = 64, OP_FOGFV, OP_LOADMATRIX, OP_MULTMATRIX, OP_TEXCOORD2FV, OP_VERTEX3FV, OP_VERTEX4FV,
	OP_PIXELSTORE, OP_DRAW, OP_TEXIMAGE, OP_MIPMAPS, OP_TEXPARAMI };

float F(uint32_t w) { float f; memcpy(&f, &w, 4); return f; }
double D(const uint32_t *w) { double d; memcpy(&d, w, 8); return d; }

void identity(float *m) {
	memset(m, 0, 64);
	m[0] = m[5] = m[10] = m[15] = 1;
}
void mult(float *m, const float *b) {   // m = m * b (column-major)
	float p[16];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			p[i + 4 * j] = m[i] * b[4 * j] + m[i + 4] * b[4 * j + 1] + m[i + 8] * b[4 * j + 2] + m[i + 12] * b[4 * j + 3];
	memcpy(m, p, 64);
}
void mult_d(float *m, const double *d) {
	float f[16];
	for (int i = 0; i < 16; i++) f[i] = (float)d[i];
	mult(m, f);
}
void rotate(float *m, float angle, float x, float y, float z) {
	const double rad = (double)angle * (double)(float)(3.14159265358979323846 / 180.0);
	const float s = (float)sin(rad), c = (float)cos(rad);
	float r[16];
	identity(r);
	const float mag = sqrtf(x * x + y * y + z * z);
	if (mag <= 1.0e-4f) return;
	x /= mag; y /= mag; z /= mag;
	const float oc = 1.0f - c;
	r[0] = oc * x * x + c; r[4] = oc * x * y - z * s; r[8] = oc * z * x + y * s;
	r[1] = oc * x * y + z * s; r[5] = oc * y * y + c; r[9] = oc * y * z - x * s;
	r[2] = oc * z * x - y * s; r[6] = oc * y * z + x * s; r[10] = oc * z * z + c;
	mult(m, r);
}
void xform(const float *m, const float *v, float *o) {
	for (int i = 0; i < 4; i++)
		o[i] = m[i] * v[0] + m[i + 4] * v[1] + m[i + 8] * v[2] + m[i + 12] * v[3];
}
int levels_for(int w, int h) {
	int n = 1;
	while (w > 1 || h > 1) { w = w > 1 ? w / 2 : 1; h = h > 1 ? h / 2 : 1; n++; }
	return n;
}

} // namespace

bool EmuPipe::operator==(const EmuPipe &o) const {
	return prim == o.prim && blend == o.blend && (!blend || (src == o.src && dst == o.dst)) && depthTest == o.depthTest &&
	       (!depthTest || depthFunc == o.depthFunc) && cull == o.cull && (!cull || (cullFace == o.cullFace)) && frontFace == o.frontFace &&
	       offset == o.offset && (!offset || (offsetFactor == o.offsetFactor && offsetUnits == o.offsetUnits));
}
uint64_t EmuPipe::hash() const {
	uint64_t h = prim | (uint64_t)blend << 2 | (uint64_t)depthTest << 3 | (uint64_t)cull << 4 | (uint64_t)offset << 5;
	if (blend) h |= (uint64_t)(src & 0x1f) << 6 | (uint64_t)(dst & 0x1f) << 11;
	if (depthTest) h |= (uint64_t)(depthFunc & 7) << 16;
	if (cull) h |= (uint64_t)(cullFace & 0xf) << 19;
	h |= (uint64_t)(frontFace & 1) << 23;
	if (offset) { uint32_t a, b; memcpy(&a, &offsetFactor, 4); memcpy(&b, &offsetUnits, 4); h ^= (uint64_t)a << 24 ^ (uint64_t)b << 40; }
	return h;
}
bool EmuTexture::complete() const {
	if (levels.empty() || levels[0].empty()) return false;
	const bool mip = minFilter >= 0x2700 && minFilter <= 0x2703;
	if (!mip) return true;
	const int need = levels_for(sizes[0].first, sizes[0].second);
	if ((int)levels.size() < need) return false;
	for (int i = 0; i < need; i++) if (levels[i].empty()) return false;
	return true;
}

bool GLEmu::load(const std::string &p_path, std::string &error) {
	FILE *f = fopen(p_path.c_str(), "rb");
	if (!f) { error = "cannot open " + p_path; return false; }
	path = p_path;
	char magic[8];
	auto u32 = [&]() { uint32_t v = 0; if (fread(&v, 4, 1, f) != 1) v = 0xffffffffu; return v; };
	if (fread(magic, 1, 8, f) != 8 || memcmp(magic, "AXGLREC1", 8)) { fclose(f); error = "not an AXGLREC1 file"; return false; }
	uint32_t n = u32();
	plainNames.clear(); plainWords.clear(); plainKind.clear();
	for (uint32_t i = 0; i < n && i < 1024; i++) {
		uint32_t w = u32(), l = u32();
		std::string name(l < 256 ? l : 0, '\0');
		if (l >= 256 || fread(&name[0], 1, l, f) != l) { fclose(f); error = "a damaged table"; return false; }
		plainNames.push_back(name);
		plainWords.push_back((int)w);
		int kind = P_UNKNOWN;
		for (const auto &k : k_names) if (name == k.name) kind = k.kind;
		plainKind.push_back(kind);
	}
	// the frames: an index of where each one's words are
	frames.clear();
	for (;;) {
		uint32_t head[3];
		if (fread(head, 4, 3, f) != 3) break;
		Frame fr;
		fr.w = (int)head[0]; fr.h = (int)head[1]; fr.words = head[2];
		fr.offset = _ftelli64(f);
		if (_fseeki64(f, (long long)fr.words * 4, SEEK_CUR)) break;
		frames.push_back(fr);
	}
	fclose(f);
	restart();
	return !frames.empty() || (error = "no frames", false);
}

void GLEmu::restart() {
	for (int k = 0; k < 3; k++) { depth[k] = 0; identity(mats[k][0]); }
	mode = 0;
	color[0] = color[1] = color[2] = color[3] = 1;
	texcoord[0] = texcoord[1] = 0;
	texture2d = blend = depthTest = cull = fog = polyOffset = false;
	blendSrc = 1; blendDst = 0; depthFunc = 0x201; cullFace = 0x405; frontFace = 0x901; envMode = 0x2100; bound = 0;
	fogMode = 0x0800; fogColor[0] = fogColor[1] = fogColor[2] = fogColor[3] = 0; fogStart = 0; fogEnd = 1; fogDensity = 1;
	offsetFactor = offsetUnits = 0;
	clearColor[0] = clearColor[1] = clearColor[2] = clearColor[3] = 0; clearDepth = 1;
	viewport[0] = viewport[1] = 0; viewport[2] = viewport[3] = 0;
	unpackAlign = 4;
	textures.clear();
	beginMode = -1;
	immediate.clear();
	unknownOps = 0;
}

EmuVertex GLEmu::transform(const ObjVertex &v) const {
	EmuVertex o;
	float eye[4], clip[4];
	xform(mats[0][depth[0]], v.p, eye);
	xform(mats[1][depth[1]], eye, clip);
	// the viewport folded into the clip coordinates (framebuffer-wide), y flipped, depth -w..w -> 0..w
	const float W = (float)fbW, H = (float)fbH, vx = (float)viewport[0], vy = (float)viewport[1], vw = (float)viewport[2], vh = (float)viewport[3];
	o.pos[0] = clip[0] * (vw / W) + clip[3] * ((2 * vx + vw) / W - 1);
	o.pos[1] = -(clip[1] * (vh / H) + clip[3] * ((2 * vy + vh) / H - 1));
	o.pos[2] = (clip[2] + clip[3]) * 0.5f;
	o.pos[3] = clip[3];
	memcpy(o.col, v.c, 16);
	float t[4] = { v.t[0], v.t[1], 0, 1 }, tt[4];
	xform(mats[2][depth[2]], t, tt);
	o.uv[0] = tt[3] != 0 ? tt[0] / tt[3] : tt[0];
	o.uv[1] = tt[3] != 0 ? tt[1] / tt[3] : tt[1];
	o.fog = 1;
	if (fog) {
		const float c = fabsf(eye[2]);
		float f = fogMode == 0x2601 ? (fogEnd - c) / (fogEnd - fogStart) : fogMode == 0x0801 ? expf(-(fogDensity * c) * (fogDensity * c)) : expf(-fogDensity * c);
		o.fog = f < 0 ? 0 : f > 1 ? 1 : f;
	}
	o.pad = 0;
	return o;
}

void GLEmu::emit(int prim, const EmuVertex *v, int n) {
	EmuBatch b;
	b.pipe.prim = (uint8_t)prim;
	b.pipe.blend = blend; b.pipe.src = (uint16_t)blendSrc; b.pipe.dst = (uint16_t)blendDst;
	b.pipe.depthTest = depthTest; b.pipe.depthFunc = (uint16_t)depthFunc;
	b.pipe.cull = cull && prim == 0; b.pipe.cullFace = (uint16_t)cullFace; b.pipe.frontFace = (uint16_t)frontFace;
	b.pipe.offset = polyOffset && prim == 0; b.pipe.offsetFactor = offsetFactor; b.pipe.offsetUnits = offsetUnits;
	b.texture = 0;
	if (texture2d) {
		auto it = textures.find(bound);
		if (it != textures.end() && it->second.complete()) {
			b.texture = bound + 1;
			b.minFilter = it->second.minFilter; b.magFilter = it->second.magFilter;
			b.wrapS = it->second.wrapS; b.wrapT = it->second.wrapT;
		}
	}
	b.env = envMode;
	b.fog = fog;
	memcpy(b.fogColor, fogColor, 16);
	b.scissor[0] = viewport[0]; b.scissor[1] = fbH - viewport[1] - viewport[3]; b.scissor[2] = viewport[2]; b.scissor[3] = viewport[3];
	const uint32_t first = (uint32_t)verts.size();
	verts.insert(verts.end(), v, v + n);
	if (!cmds.empty() && cmds.back().kind == EmuCmd::BATCH) {
		EmuBatch &l = cmds.back().batch;
		if (l.pipe == b.pipe && l.texture == b.texture && l.minFilter == b.minFilter && l.magFilter == b.magFilter &&
		    l.wrapS == b.wrapS && l.wrapT == b.wrapT && l.env == b.env && l.fog == b.fog && (!b.fog || !memcmp(l.fogColor, b.fogColor, 16)) &&
		    !memcmp(l.scissor, b.scissor, 16) && l.first + l.count == first) {
			l.count += (uint32_t)n;
			return;
		}
	}
	EmuCmd c;
	c.kind = EmuCmd::BATCH;
	b.first = first;
	b.count = (uint32_t)n;
	c.batch = b;
	cmds.push_back(c);
}

// GL primitives (index: the order to take v in; NULL: 0 .. n-1) into triangles / lines / points
void GLEmu::assemble(int m, const std::vector<ObjVertex> &v, const uint32_t *index, size_t n) {
	std::vector<EmuVertex> t(n);
	for (size_t i = 0; i < n; i++)
		t[i] = transform(v[index ? index[i] : i]);
	std::vector<EmuVertex> out;
	auto tri = [&](size_t a, size_t b, size_t c) { out.push_back(t[a]); out.push_back(t[b]); out.push_back(t[c]); };
	switch (m) {
	case 0: emit(2, t.data(), (int)n); return;   // GL_POINTS
	case 1: for (size_t i = 0; i + 1 < n; i += 2) { out.push_back(t[i]); out.push_back(t[i + 1]); } emit(1, out.data(), (int)out.size()); return;
	case 2: case 3:   // GL_LINE_LOOP, GL_LINE_STRIP
		for (size_t i = 0; i + 1 < n; i++) { out.push_back(t[i]); out.push_back(t[i + 1]); }
		if (m == 2 && n > 2) { out.push_back(t[n - 1]); out.push_back(t[0]); }
		emit(1, out.data(), (int)out.size());
		return;
	case 4: for (size_t i = 0; i + 2 < n; i += 3) tri(i, i + 1, i + 2); break;
	case 5: for (size_t i = 2; i < n; i++) { if (i % 2) tri(i - 1, i - 2, i); else tri(i - 2, i - 1, i); } break;
	case 6: case 9: for (size_t i = 2; i < n; i++) tri(0, i - 1, i); break;   // GL_TRIANGLE_FAN, GL_POLYGON
	case 7: for (size_t i = 0; i + 3 < n; i += 4) { tri(i, i + 1, i + 2); tri(i, i + 2, i + 3); } break;
	case 8: for (size_t i = 0; i + 3 < n; i += 2) { tri(i, i + 1, i + 3); tri(i, i + 3, i + 2); } break;
	default: unknownOps++; return;
	}
	if (!out.empty()) emit(0, out.data(), (int)out.size());
}

void GLEmu::vertex(float x, float y, float z, float w) {
	ObjVertex v;
	v.p[0] = x; v.p[1] = y; v.p[2] = z; v.p[3] = w;
	memcpy(v.c, color, 16);
	v.t[0] = texcoord[0]; v.t[1] = texcoord[1];
	immediate.push_back(v);
}

// a texture image to RGBA8 (rows at the unpack alignment)
void GLEmu::tex_image(uint32_t level, int w, int h, uint32_t fmt, uint32_t type, const uint8_t *p, size_t n) {
	EmuTexture &t = textures[bound];
	if (t.levels.size() <= level) { t.levels.resize(level + 1); t.sizes.resize(level + 1); }
	std::vector<uint8_t> &out = t.levels[level];
	out.assign((size_t)w * h * 4, 255);
	t.sizes[level] = { w, h };
	t.version++;
	if (!p || type != 0x1401) { if (p && type != 0x1401) unknownOps++; return; }   // (only GL_UNSIGNED_BYTE seen)
	const int comps = fmt == 0x1907 ? 3 : fmt == 0x1908 ? 4 : fmt == 0x190a ? 2 : fmt == 0x80e0 ? 3 : fmt == 0x80e1 ? 4 : 1;
	const size_t row = (size_t)w * comps, a = unpackAlign > 0 ? unpackAlign : 1, stride = (row + a - 1) / a * a;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			const size_t at = (size_t)y * stride + (size_t)x * comps;
			if (at + comps > n) continue;
			const uint8_t *s = p + at;
			uint8_t *d = &out[((size_t)y * w + x) * 4];
			switch (fmt) {
			case 0x1907: d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = 255; break;          // GL_RGB
			case 0x1908: memcpy(d, s, 4); break;                                             // GL_RGBA
			case 0x80e0: d[0] = s[2]; d[1] = s[1]; d[2] = s[0]; d[3] = 255; break;          // GL_BGR
			case 0x80e1: d[0] = s[2]; d[1] = s[1]; d[2] = s[0]; d[3] = s[3]; break;         // GL_BGRA
			case 0x1909: d[0] = d[1] = d[2] = s[0]; d[3] = 255; break;                      // GL_LUMINANCE
			case 0x190a: d[0] = d[1] = d[2] = s[0]; d[3] = s[1]; break;                     // GL_LUMINANCE_ALPHA
			case 0x1906: d[0] = d[1] = d[2] = 255; d[3] = s[0]; break;                      // GL_ALPHA
			default: d[0] = d[1] = d[2] = s[0]; d[3] = 255; break;
			}
		}
}

void GLEmu::tex_param(uint32_t pname, int v) {
	EmuTexture &t = textures[bound];
	if (pname == 0x2801) t.minFilter = v;
	else if (pname == 0x2800) t.magFilter = v;
	else if (pname == 0x2802) t.wrapS = v;
	else if (pname == 0x2803) t.wrapT = v;
	else return;
	const bool mip = t.minFilter >= 0x2700 && t.minFilter <= 0x2703;
	if (mip != t.mipped) {   // (whether the mip levels are used changes the renderer's copy)
		t.mipped = mip;
		t.version++;
	}
}

void GLEmu::plain(int kind, const uint32_t *a) {
	switch (kind) {
	case P_BEGIN: beginMode = (int)a[0]; immediate.clear(); break;
	case P_END: if (beginMode >= 0) assemble(beginMode, immediate, nullptr, immediate.size()); beginMode = -1; break;
	case P_BINDTEXTURE: bound = a[1]; break;
	case P_BLENDFUNC: blendSrc = a[0]; blendDst = a[1]; break;
	case P_CLEAR: {
		EmuCmd c;
		c.kind = EmuCmd::CLEAR;
		c.clearMask = a[0];
		memcpy(c.clearColor, clearColor, 16);
		c.clearDepth = clearDepth;
		cmds.push_back(c);
		break;
	}
	case P_CLEARCOLOR: for (int i = 0; i < 4; i++) clearColor[i] = F(a[i]); break;
	case P_CLEARDEPTH: clearDepth = (float)D(a); break;
	case P_COLOR3UB: color[0] = (a[0] & 255) / 255.0f; color[1] = (a[1] & 255) / 255.0f; color[2] = (a[2] & 255) / 255.0f; color[3] = 1; break;
	case P_COLOR4UB: for (int i = 0; i < 4; i++) color[i] = (a[i] & 255) / 255.0f; break;
	case P_COLOR4F: for (int i = 0; i < 4; i++) color[i] = F(a[i]); break;
	case P_CULLFACE: cullFace = a[0]; break;
	case P_DEPTHFUNC: depthFunc = a[0]; break;
	case P_ENABLE: case P_DISABLE: {
		const bool on = kind == P_ENABLE;
		switch (a[0]) {
		case 0x0de1: texture2d = on; break;
		case 0x0be2: blend = on; break;
		case 0x0b71: depthTest = on; break;
		case 0x0b44: cull = on; break;
		case 0x0b60: fog = on; break;
		case 0x8037: polyOffset = on; break;
		}
		break;
	}
	case P_FOGF: case P_FOGI: {
		const float v = kind == P_FOGF ? F(a[1]) : (float)(int)a[1];
		if (a[0] == 0x0b62) fogDensity = v;
		else if (a[0] == 0x0b63) fogStart = v;
		else if (a[0] == 0x0b64) fogEnd = v;
		else if (a[0] == 0x0b65) fogMode = kind == P_FOGF ? (uint32_t)v : a[1];
		break;
	}
	case P_FRONTFACE: frontFace = a[0]; break;
	case P_LOADIDENTITY: identity(top()); break;
	case P_MATRIXMODE: if (a[0] >= 0x1700 && a[0] <= 0x1702) mode = (int)(a[0] - 0x1700); break;
	case P_POLYGONOFFSET: offsetFactor = F(a[0]); offsetUnits = F(a[1]); break;
	case P_PUSHMATRIX: if (depth[mode] < 31) { memcpy(mats[mode][depth[mode] + 1], top(), 64); depth[mode]++; } break;
	case P_POPMATRIX: if (depth[mode] > 0) depth[mode]--; break;
	case P_ROTATEF: rotate(top(), F(a[0]), F(a[1]), F(a[2]), F(a[3])); break;
	case P_SCALEF: { float *m = top(); for (int i = 0; i < 4; i++) { m[i] *= F(a[0]); m[4 + i] *= F(a[1]); m[8 + i] *= F(a[2]); } break; }
	case P_TRANSLATEF: {
		float *m = top();
		const float x = F(a[0]), y = F(a[1]), z = F(a[2]);
		for (int i = 0; i < 4; i++) m[12 + i] = m[i] * x + m[4 + i] * y + m[8 + i] * z + m[12 + i];
		break;
	}
	case P_TEXCOORD2D: texcoord[0] = (float)D(a); texcoord[1] = (float)D(a + 2); break;
	case P_TEXCOORD2F: texcoord[0] = F(a[0]); texcoord[1] = F(a[1]); break;
	case P_TEXCOORD2I: texcoord[0] = (float)(int)a[0]; texcoord[1] = (float)(int)a[1]; break;
	case P_TEXENVF: if (a[1] == 0x2200) envMode = (uint32_t)F(a[2]); break;
	case P_TEXPARAMETERF: tex_param(a[1], (int)F(a[2])); break;
	case P_VERTEX2I: vertex((float)(int)a[0], (float)(int)a[1], 0, 1); break;
	case P_VERTEX3F: vertex(F(a[0]), F(a[1]), F(a[2]), 1); break;
	case P_VIEWPORT: for (int i = 0; i < 4; i++) viewport[i] = (int)a[i]; break;
	case P_LOOKAT: {
		const double ex = D(a), ey = D(a + 2), ez = D(a + 4), cx = D(a + 6), cy = D(a + 8), cz = D(a + 10), ux = D(a + 12), uy = D(a + 14), uz = D(a + 16);
		float f[3] = { (float)(cx - ex), (float)(cy - ey), (float)(cz - ez) }, up[3] = { (float)ux, (float)uy, (float)uz }, s[3], u[3];
		float r = sqrtf(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
		if (r != 0) { f[0] /= r; f[1] /= r; f[2] /= r; }
		s[0] = f[1] * up[2] - f[2] * up[1]; s[1] = f[2] * up[0] - f[0] * up[2]; s[2] = f[0] * up[1] - f[1] * up[0];
		r = sqrtf(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
		if (r != 0) { s[0] /= r; s[1] /= r; s[2] /= r; }
		u[0] = s[1] * f[2] - s[2] * f[1]; u[1] = s[2] * f[0] - s[0] * f[2]; u[2] = s[0] * f[1] - s[1] * f[0];
		float m[16];
		identity(m);
		m[0] = s[0]; m[4] = s[1]; m[8] = s[2];
		m[1] = u[0]; m[5] = u[1]; m[9] = u[2];
		m[2] = -f[0]; m[6] = -f[1]; m[10] = -f[2];
		mult(top(), m);
		float *t = top();
		const float x = (float)-ex, y = (float)-ey, z = (float)-ez;
		for (int i = 0; i < 4; i++) t[12 + i] = t[i] * x + t[4 + i] * y + t[8 + i] * z + t[12 + i];
		break;
	}
	case P_PERSPECTIVE: {
		const double fovy = D(a), aspect = D(a + 2), zn = D(a + 4), zf = D(a + 6);
		const double rad = fovy / 2 * 3.14159265358979323846 / 180, dz = zf - zn, sine = sin(rad);
		if (dz == 0 || sine == 0 || aspect == 0) break;
		const double cot = cos(rad) / sine;
		double m[16] = { 0 };
		m[0] = cot / aspect; m[5] = cot; m[10] = -(zf + zn) / dz; m[11] = -1; m[14] = -2 * zn * zf / dz;
		mult_d(top(), m);
		break;
	}
	case P_ORTHO2D: {
		const float L = (float)D(a), R = (float)D(a + 2), B = (float)D(a + 4), T = (float)D(a + 6);
		float m[16];
		identity(m);
		m[0] = 2.0f / (R - L); m[12] = -(R + L) / (R - L);
		m[5] = 2.0f / (T - B); m[13] = -(T + B) / (T - B);
		m[10] = -1; m[14] = 0;
		mult(top(), m);
		break;
	}
	case P_DISABLECLIENT: case P_ENABLECLIENT: case P_HINT: case P_POLYGONMODE: break;
	default: unknownOps++; break;
	}
}

bool GLEmu::load_header(const uint8_t *b, size_t n, std::string &error) {
	if (n < 12 || memcmp(b, "AXGLREC1", 8)) { error = "not an AXGLREC1 header"; return false; }
	uint32_t count;
	memcpy(&count, b + 8, 4);
	size_t o = 12;
	plainNames.clear(); plainWords.clear(); plainKind.clear();
	for (uint32_t i = 0; i < count; i++) {
		if (o + 8 > n) { error = "a short header"; return false; }
		uint32_t w, l;
		memcpy(&w, b + o, 4);
		memcpy(&l, b + o + 4, 4);
		if (o + 8 + l > n) { error = "a short header"; return false; }
		std::string name((const char *)b + o + 8, l);
		o += 8 + l;
		plainNames.push_back(name);
		plainWords.push_back((int)w);
		int kind = P_UNKNOWN;
		for (const auto &k : k_names) if (name == k.name) kind = k.kind;
		plainKind.push_back(kind);
	}
	frames.clear();
	restart();
	return true;
}

void GLEmu::run_frame(int i) {
	const Frame &fr = frames[i];
	data.resize(fr.words);
	{
		FILE *f = fopen(path.c_str(), "rb");
		if (!f || _fseeki64(f, fr.offset, SEEK_SET) || fread(data.data(), 4, fr.words, f) != fr.words) {
			if (f) fclose(f);
			unknownOps++;
			return;
		}
		fclose(f);
	}
	run_words(data.data(), fr.words, fr.w, fr.h);
}

void GLEmu::run_words(const uint32_t *words, size_t n, int width, int height) {
	verts.clear();
	cmds.clear();
	fbW = width > 0 ? width : 1;
	fbH = height > 0 ? height : 1;
	if (viewport[2] == 0) { viewport[2] = fbW; viewport[3] = fbH; }   // (a new context's viewport: the window)
	const uint32_t *p = words, *end = p + n;
	while (p < end) {
		const uint32_t h = *p++, op = h & 0xffff, words = h >> 16;
		if (op < plainKind.size()) {
			plain(plainKind[op], p);
			p += words;
			continue;
		}
		switch (op) {
		case OP_COLOR4UBV: { const uint8_t *b = (const uint8_t *)p; for (int k = 0; k < 4; k++) color[k] = b[k] / 255.0f; p += 1; break; }
		case OP_FOGFV:
			if (p[0] == 0x0b66) for (int k = 0; k < 4; k++) fogColor[k] = F(p[1 + k]);
			else { uint32_t a[2] = { p[0], p[1] }; plain(P_FOGF, a); }
			p += 5;
			break;
		case OP_LOADMATRIX: memcpy(top(), p, 64); p += 16; break;
		case OP_MULTMATRIX: mult(top(), (const float *)p); p += 16; break;
		case OP_TEXCOORD2FV: texcoord[0] = F(p[0]); texcoord[1] = F(p[1]); p += 2; break;
		case OP_VERTEX3FV: vertex(F(p[0]), F(p[1]), F(p[2]), 1); p += 3; break;
		case OP_VERTEX4FV: vertex(F(p[0]), F(p[1]), F(p[2]), F(p[3])); p += 4; break;
		case OP_PIXELSTORE: if (p[0] == 0x0cf5) unpackAlign = (int)p[1]; p += 2; break;
		case OP_TEXPARAMI: tex_param(p[1], (int)p[2]); p += 3; break;
		case OP_DRAW: {
			const uint32_t m = p[0], count = p[1], itype = p[2], n = p[3];
			p += 4;
			std::vector<uint32_t> idx(count);
			const size_t isz = itype == 0x1401 ? 1 : itype == 0x1403 ? 2 : 4;
			for (uint32_t k = 0; k < count; k++) {
				uint32_t v = 0;
				memcpy(&v, (const uint8_t *)p + k * isz, isz);
				idx[k] = v;
			}
			p += (count * isz + 3) / 4;
			std::vector<ObjVertex> vs(n);
			for (auto &v : vs) { v.p[0] = v.p[1] = v.p[2] = 0; v.p[3] = 1; memcpy(v.c, color, 16); v.t[0] = texcoord[0]; v.t[1] = texcoord[1]; }
			for (int arr = 0; arr < 3; arr++) {
				if (!*p++) continue;
				const int size = (int)p[0];
				const uint32_t type = p[1];
				p += 2;
				const uint8_t *b = (const uint8_t *)p;
				const int ts = type == 0x1401 || type == 0x1400 ? 1 : type == 0x1402 || type == 0x1403 ? 2 : type == 0x140a ? 8 : 4;
				for (uint32_t k = 0; k < n; k++) {
					const uint8_t *e = b + (size_t)k * size * ts;
					float c[4] = { 0, 0, 0, 1 };
					for (int j = 0; j < size && j < 4; j++) {
						if (type == 0x1406) { memcpy(&c[j], e + j * 4, 4); }
						else if (type == 0x1401) c[j] = arr == 1 ? e[j] / 255.0f : e[j];
						else if (type == 0x140a) { double d; memcpy(&d, e + j * 8, 8); c[j] = (float)d; }
						else if (type == 0x1404) { int32_t v; memcpy(&v, e + j * 4, 4); c[j] = (float)v; }
						else if (type == 0x1402) { int16_t v; memcpy(&v, e + j * 2, 2); c[j] = (float)v; }
					}
					if (arr == 0) { vs[k].p[0] = c[0]; vs[k].p[1] = c[1]; vs[k].p[2] = size > 2 ? c[2] : 0; vs[k].p[3] = size > 3 ? c[3] : 1; }
					else if (arr == 1) { memcpy(vs[k].c, c, 16); if (size < 4) vs[k].c[3] = 1; }
					else { vs[k].t[0] = c[0]; vs[k].t[1] = c[1]; }
				}
				p += ((size_t)n * size * ts + 3) / 4;
			}
			assemble((int)m, vs, idx.data(), idx.size());
			break;
		}
		case OP_TEXIMAGE: {
			const uint32_t level = p[1], w = p[3], h = p[4], fmt = p[6], type = p[7], n = p[8];
			tex_image(level, (int)w, (int)h, fmt, type, n ? (const uint8_t *)(p + 9) : nullptr, n);
			p += 9 + (n + 3) / 4;
			break;
		}
		case OP_MIPMAPS: {   // gluBuild2DMipmaps: the image scaled to a power of two (down), then halved to 1 x 1
			const int w = (int)p[2], h = (int)p[3];
			const uint32_t fmt = p[4], type = p[5], n = p[6];
			const uint8_t *src = n ? (const uint8_t *)(p + 7) : nullptr;
			p += 7 + (n + 3) / 4;
			EmuTexture &t = textures[bound];
			t.levels.clear();
			t.sizes.clear();
			tex_image(0, w, h, fmt, type, src, n);
			std::vector<uint8_t> base = t.levels[0];
			int pw = 1, ph = 1;
			while (pw * 2 <= w) pw *= 2;
			while (ph * 2 <= h) ph *= 2;
			if (pw != w || ph != h) {   // (box-sampled to the power-of-two size)
				std::vector<uint8_t> s((size_t)pw * ph * 4);
				for (int y = 0; y < ph; y++)
					for (int x = 0; x < pw; x++) {
						const int x0 = x * w / pw, x1 = ((x + 1) * w + pw - 1) / pw, y0 = y * h / ph, y1 = ((y + 1) * h + ph - 1) / ph;
						for (int c = 0; c < 4; c++) {
							unsigned sum = 0, cnt = 0;
							for (int yy = y0; yy < y1; yy++) for (int xx = x0; xx < x1; xx++) { sum += base[((size_t)yy * w + xx) * 4 + c]; cnt++; }
							s[((size_t)y * pw + x) * 4 + c] = (uint8_t)(cnt ? (sum + cnt / 2) / cnt : 0);
						}
					}
				base.swap(s);
				t.levels[0] = base;
				t.sizes[0] = { pw, ph };
			}
			int cw = pw, ch = ph;
			while (cw > 1 || ch > 1) {
				const int nw = cw > 1 ? cw / 2 : 1, nh = ch > 1 ? ch / 2 : 1;
				std::vector<uint8_t> s((size_t)nw * nh * 4);
				const std::vector<uint8_t> &b = t.levels.back();
				for (int y = 0; y < nh; y++)
					for (int x = 0; x < nw; x++)
						for (int c = 0; c < 4; c++) {
							const int xa = x * 2, xb = cw > 1 ? x * 2 + 1 : x * 2, ya = y * 2, yb = ch > 1 ? y * 2 + 1 : y * 2;
							const unsigned sum = b[((size_t)ya * cw + xa) * 4 + c] + b[((size_t)ya * cw + xb) * 4 + c] + b[((size_t)yb * cw + xa) * 4 + c] + b[((size_t)yb * cw + xb) * 4 + c];
							s[((size_t)y * nw + x) * 4 + c] = (uint8_t)((sum + 2) / 4);
						}
				t.levels.push_back(std::move(s));
				t.sizes.push_back({ nw, nh });
				cw = nw;
				ch = nh;
			}
			t.version++;
			break;
		}
		default: unknownOps++; return;   // (an unknown op: the rest of the frame cannot be read)
		}
	}
}
