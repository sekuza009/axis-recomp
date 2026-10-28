/* view_volume.c: things added to the view volume's lists for drawing: an object's two points, a quad of four points,
   and a camera-facing quad (a billboard). Points are transformed by the view volume's matrices (columns) into clip
   space, in the original's order of additions; with flag 1 the entry is dropped again when all its points are
   outside the same clip plane. A full list sets its overflow flag instead. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

typedef long double X;

/* a clip-space point's outcodes: per axis, below -w (1) or at least w (0x10), x in the low byte, y the next, z the
   next (fcom: an ordered >=) */
static unsigned outcode(const float *v)
{
	X minusW = -(X)v[3];
	unsigned code = 0;
	for (int a = 0; a < 3; a++) {
		if (minusW >= v[a])
			code |= 1u << (a * 8);
		else if (v[a] >= v[3])
			code |= 0x10u << (a * 8);
	}
	return code;
}
/* every point outside one x or y plane, or one z plane */
static int all_outside(unsigned common) { return (common & 0x11) || (common & 0x111100); }

/* the next record of a list (count at +countAt, its limit at +countAt - 8, the records at +countAt - 4); NULL with
   the overflow flag at +full set when the list is full */
static float *next_record(u8 *vv, int countAt, int full, int size)
{
	int n = FIELD(int, vv, countAt);
	if (n >= FIELD(int, vv, countAt - 8)) {
		FIELD(int, vv, full) = 1;
		return NULL;
	}
	float *r = (float *)(FIELD(u8 *, vv, countAt - 4) + n * size);
	FIELD(int, vv, countAt) = n + 1;
	return r;
}

/* 0x485120: an object's two points p and q (into the 36-byte records of the list at +0x908c); the object's first
   word kept with them */
void THISCALL (ViewVolume_add_485120)(u8 *vv, const u32 *object, const float *p, const float *q, int flag)
{
	float *r = next_record(vv, 0x908c, 0x90a0, 36);
	if (!r)
		return;
	const float *M = (const float *)(vv + 0x9130);
	for (int c = 0; c < 4; c++)
		r[1 + c] = f32((X)M[8 + c] * p[2] + (X)M[4 + c] * p[1] + (X)p[0] * M[c] + M[12 + c]);
	r[5] = f32((X)M[4] * q[1] + (X)M[8] * q[2] + (X)q[0] * M[0] + M[12]);
	for (int c = 1; c < 4; c++)
		r[5 + c] = f32((X)M[c] * q[0] + (X)M[4 + c] * q[1] + (X)M[8 + c] * q[2] + M[12 + c]);
	if (flag == 1 && all_outside(outcode(r + 1) & outcode(r + 5))) {
		FIELD(int, vv, 0x908c)--;
		return;
	}
	*(u32 *)r = *object;
}

/* a quad record's fields after its points: the texture id, two uv pairs (when it has a texture), the colour and a
   value */
static void quad_fields(float *r, int id, const u32 *uv0, const u32 *uv1, const u32 *colour, u32 extra)
{
	FIELD(int, r, 0) = id;
	if (id >= 0) {
		FIELD(u32, r, 4) = uv0[0];
		FIELD(u32, r, 8) = uv0[1];
		FIELD(u32, r, 0xc) = uv1[0];
		FIELD(u32, r, 0x10) = uv1[1];
	}
	FIELD(u32, r, 0x14) = *colour;
	FIELD(u32, r, 0x58) = extra;
}

/* whether the quad's four clip-space points (from r + 6) are all outside one plane */
static int quad_outside(const float *r)
{
	unsigned common = 0x111111;
	for (int k = 0; k < 4; k++)
		common &= outcode(r + 6 + k * 4);
	return all_outside(common);
}

/* 0x4848e0: a quad of four points p (into the 92-byte records of the list at +0x9070) */
void THISCALL (hud_4848e0)(u8 *vv, int id, const u32 *uv0, const u32 *uv1, const u32 *colour, const float *p, u32 extra,
                           int flag)
{
	float *r = next_record(vv, 0x9070, 0x909c, 92);
	if (!r)
		return;
	const float *M = (const float *)(vv + 0x9130);
	for (int k = 0; k < 4; k++) {
		const float *v = p + k * 3;
		float *o = r + 6 + k * 4;
		for (int c = 0; c < 4; c++)   /* two orders of addition, as in the original */
			o[c] = c == 0 || k == 0 ? f32((X)M[8 + c] * v[2] + (X)M[4 + c] * v[1] + (X)M[c] * v[0] + M[12 + c])
			                        : f32((X)M[8 + c] * v[2] + (X)M[c] * v[0] + (X)M[4 + c] * v[1] + M[12 + c]);
	}
	if (flag == 1 && quad_outside(r)) {
		FIELD(int, vv, 0x9070)--;
		return;
	}
	quad_fields(r, id, uv0, uv1, colour, extra);
}

/* 0x484ca0: a camera-facing quad at p: p to camera space (the matrix at +0x90f0; x and y rounded, z not), its corners
   (x + A.x, y + A.y), (x + B.x, y + A.y), (x + B.x, y + B.y), (x + A.x, y + B.y) at depth z + dz projected by the
   matrix at +0x90b0. Corners 0 and 3 are rounded to floats first, 1 and 2 are not, as in the original */
void THISCALL (hud_484ca0)(u8 *vv, int id, const u32 *uv0, const u32 *uv1, float dz, const u32 *colour, const float *A,
                           const float *B, const float *p, u32 extra, int flag)
{
	float *r = next_record(vv, 0x9070, 0x909c, 92);
	if (!r)
		return;
	const float *V = (const float *)(vv + 0x90f0), *P = (const float *)(vv + 0x90b0);
	float cx = f32((X)V[4] * p[1] + (X)V[8] * p[2] + (X)p[0] * V[0] + V[12]);
	float cy = f32((X)V[5] * p[1] + (X)V[9] * p[2] + (X)V[1] * p[0] + V[13]);
	X z = (X)V[6] * p[1] + (X)V[10] * p[2] + (X)V[2] * p[0] + V[14];
	z += dz;
	X xs[4], ys[4];
	xs[0] = f32((X)cx + A[0]);
	ys[0] = f32((X)cy + A[1]);
	xs[1] = (X)cx + B[0];
	ys[1] = (X)cy + A[1];
	xs[2] = (X)cx + B[0];
	ys[2] = (X)cy + B[1];
	xs[3] = f32((X)cx + A[0]);
	ys[3] = f32((X)cy + B[1]);
	for (int k = 0; k < 4; k++)
		for (int c = 0; c < 4; c++)
			r[6 + k * 4 + c] = f32(z * P[8 + c] + ys[k] * P[4 + c] + xs[k] * P[c] + P[12 + c]);
	if (flag == 1 && quad_outside(r)) {
		FIELD(int, vv, 0x9070)--;
		return;
	}
	quad_fields(r, id, uv0, uv1, colour, extra);
}

/* ((a * *ma + b * *mb) + c * *mc) + *t, each product a register times a float from memory */
static X row(X a, const float *ma, X b, const float *mb, X c, const float *mc, const float *t)
{
	X s = fmul_m(a, ma) + fmul_m(b, mb);
	s = s + fmul_m(c, mc);
	return fadd_m(s, t);
}
#define LD(f) fld_m(&(f))

/* 0x4842d0: a triangle (P: three points) into the 0x60-byte records of the list at +0x905c: taken through the model
   matrix M first when there is one (the first point's coordinates kept unrounded, the others rounded), then the view
   matrix (+0x9130) into clip space (+0x28); with cull 1 dropped when all three are outside one plane. The record:
   id, six words of info (when id >= 0), three more, raw, M; raw 1 keeps the untransformed points (w = 1) instead.
   Every sum in the original's operand order. Returns what the original leaves in eax: the count when full or culled,
   count + 1 for a null list, else raw, or p2.z's bits when raw is 1 */
int THISCALL (ViewVolume_transformObject)(u8 *vv, int id, const u32 *info6, const u32 *info3, const float *P,
                                         const float *M, int raw, int cull)
{
	int n = FIELD(int, vv, 0x905c);
	if (n >= FIELD(int, vv, 0x9054)) {
		FIELD(int, vv, 0x9098) = 1;
		return n;
	}
	float *rec = (float *)(FIELD(u8 *, vv, 0x9058) + n * 0x60);
	FIELD(int, vv, 0x905c) = n + 1;
	if (!rec)
		return n + 1;
	const float *V = (const float *)(vv + 0x9130), *p1 = P + 3, *p2 = P + 6;
	float *R = rec + 10;
	if (M) {
		X x0 = row(LD(P[0]), &M[0], LD(M[4]), &P[1], LD(P[2]), &M[8], &M[12]);
		X y0 = row(LD(M[9]), &P[2], LD(M[5]), &P[1], LD(M[1]), &P[0], &M[13]);
		X z0 = row(LD(P[2]), &M[10], LD(P[0]), &M[2], LD(M[6]), &P[1], &M[14]);
		float x1 = f32(row(LD(p1[0]), &M[0], LD(p1[2]), &M[8], LD(p1[1]), &M[4], &M[12]));
		float y1 = f32(row(LD(p1[2]), &M[9], LD(p1[1]), &M[5], LD(p1[0]), &M[1], &M[13]));
		float z1 = f32(row(LD(p1[2]), &M[10], LD(p1[1]), &M[6], LD(p1[0]), &M[2], &M[14]));
		float x2 = f32(row(LD(p2[2]), &M[8], LD(p2[1]), &M[4], LD(M[0]), &p2[0], &M[12]));
		float y2 = f32(row(LD(p2[2]), &M[9], LD(p2[1]), &M[5], LD(M[1]), &p2[0], &M[13]));
		float z2 = f32(row(LD(p2[0]), &M[2], LD(p2[2]), &M[10], LD(p2[1]), &M[6], &M[14]));
		for (int c = 0; c < 4; c++)
			R[c] = f32(row(z0, &V[8 + c], y0, &V[4 + c], x0, &V[c], &V[12 + c]));
		for (int c = 0; c < 4; c++)
			R[4 + c] = f32(row(LD(z1), &V[8 + c], LD(y1), &V[4 + c], LD(x1), &V[c], &V[12 + c]));
		for (int c = 0; c < 4; c++)
			R[8 + c] = f32(row(LD(z2), &V[8 + c], LD(y2), &V[4 + c], LD(x2), &V[c], &V[12 + c]));
	} else {
		R[0] = f32(row(LD(V[8]), &P[2], LD(V[4]), &P[1], LD(P[0]), &V[0], &V[12]));
		R[1] = f32(row(LD(V[1]), &P[0], LD(V[9]), &P[2], LD(V[5]), &P[1], &V[13]));
		R[2] = f32(row(LD(V[2]), &P[0], LD(V[10]), &P[2], LD(V[6]), &P[1], &V[14]));
		R[3] = f32(row(LD(V[3]), &P[0], LD(V[11]), &P[2], LD(V[7]), &P[1], &V[15]));
		Mat4_transformPoint(R + 4, V, p1);
		Mat4_transformPoint(R + 8, V, p2);
	}
	if (cull == 1) {
		unsigned common = 0x111111;
		for (int k = 0; k < 3; k++)
			common &= outcode(R + k * 4);
		if (common & 0x111111) {
			FIELD(int, vv, 0x905c) -= 1;
			return FIELD(int, vv, 0x905c);
		}
	}
	u32 *r = (u32 *)rec;
	r[0] = (u32)id;
	if (id >= 0)
		memcpy(r + 1, info6, 24);
	memcpy(r + 7, info3, 12);
	r[0x17] = (u32)raw;
	int ret = raw;
	if (raw == 1) {
		rec[10] = (float)LD(P[0]);   /* through the FPU, as the original's fld / fstp */
		rec[11] = (float)LD(P[1]);
		rec[12] = (float)LD(P[2]);
		r[13] = 0x3f800000;
		memcpy(r + 14, p1, 12);
		r[17] = 0x3f800000;
		memcpy(r + 18, p2, 12);
		r[21] = 0x3f800000;
		ret = ((const int *)p2)[2];
	}
	r[0x16] = (u32)M;
	return ret;
}

/* 0x483fd0: the view's vertex buffer freed (when it owns one, +0xc) and reset; if the driver has GL_EXT_vertex_array,
   its three entry points looked up (+0x14 .. +0x1c) and the flag (+0x10) set */
void THISCALL (gfx_initVertexArrayExt)(u8 *view)
{
	if (FIELD(int, view, 0xc) == 1) {
		GAME_CDECL(0x49ef24, void, void *)(FIELD(void *, view, 8));   /* operator delete */
		FIELD(void *, view, 8) = 0;
		FIELD(int, view, 0xc) = 0;
	}
	GAME_THISCALL(0x483fc0, void, void *)(view);   /* load_483fc0 */
	const char *extensions = IMPORT(0x4a9278, const char *, u32)(0x1f03);   /* glGetString(GL_EXTENSIONS) */
	if (!extensions || !GAME_CDECL(0x4a0090, char *, const char *, const char *)(extensions, (const char *)0x4c7b5c))   /* strstr */
		return;
	FIELD(int, view, 0x10) = 1;
	static const u32 names[3] = { 0x4c7b48, 0x4c7b34, 0x4c7b1c };   /* the three entry points' names */
	for (int k = 0; k < 3; k++)
		FIELD(void *, view, 0x14 + k * 4) = IMPORT(0x4a928c, void *, const char *)((const char *)names[k]);   /* wglGetProcAddress */
}
