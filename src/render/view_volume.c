/* view_volume.c: the view volume: things added to its lists (an object's two points, a triangle, a quad, a
   camera-facing quad, a whole model), and the lists drawn; points are transformed by its matrices (columns) into clip
   space in the original's order; with flag 1 an entry is dropped again when all its points are outside the same clip
   plane; a full list sets its overflow flag. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, AP(u8, RELOC(obj)) + (offset))
#define VV ((ViewVolume *)vv)   /* the view volume (vv in each function) by its fields (src/scene.fields) */

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
	float *r = (float *)(AP(u8, FIELD(APTR(u8), vv, countAt - 4)) + n * size);
	FIELD(int, vv, countAt) = n + 1;
	return r;
}

/* 0x485120: a line from p to q in colour *colour (packed RGBA) into the 36-byte records of the list at segments
   (colour, then the two clip-space points); with flag 1 dropped again when both ends are outside one clip plane */
void THISCALL (ViewVolume_addSegment)(u8 *vv, const u32 *colour, const float *p, const float *q, int flag)
{
	float *r = next_record(vv, 0x908c, 0x90a0, 36);
	if (!r)
		return;
	const float *M = VV->clip;
	for (int c = 0; c < 4; c++)
		r[1 + c] = f32((X)M[8 + c] * p[2] + (X)M[4 + c] * p[1] + (X)p[0] * M[c] + M[12 + c]);
	r[5] = f32((X)M[4] * q[1] + (X)M[8] * q[2] + (X)q[0] * M[0] + M[12]);
	for (int c = 1; c < 4; c++)
		r[5 + c] = f32((X)M[c] * q[0] + (X)M[4 + c] * q[1] + (X)M[8 + c] * q[2] + M[12 + c]);
	if (flag == 1 && all_outside(outcode(r + 1) & outcode(r + 5))) {
		VV->segmentCount--;
		return;
	}
	*AP(u32, RELOC(r)) = *colour;
}

/* a quad record's fields besides its points: the texture id, two uv pairs (when it has a texture), the colour and its
   kind */
static void quad_fields(float *r, int id, const u32 *uv0, const u32 *uv1, const u32 *colour, u32 kind)
{
	((ViewQuad *)r)->texture = id;
	if (id >= 0) {
		BITS(((ViewQuad *)r)->uv0[0]) = uv0[0];
		BITS(((ViewQuad *)r)->uv0[1]) = uv0[1];
		BITS(((ViewQuad *)r)->uv1[0]) = uv1[0];
		BITS(((ViewQuad *)r)->uv1[1]) = uv1[1];
	}
	((ViewQuad *)r)->colour = *colour;
	((ViewQuad *)r)->kind = (int)kind;
}

/* whether the quad's four clip-space points (from r + 6) are all outside one plane */
static int quad_outside(const float *r)
{
	unsigned common = 0x111111;
	for (int k = 0; k < 4; k++)
		common &= outcode(r + 6 + k * 4);
	return all_outside(common);
}

/* 0x4848e0: a quad of four points p (into the 92-byte records of the list at quads; kind 2 depth-sorted, 3 drawn
   last) */
void THISCALL (ViewVolume_addQuad)(u8 *vv, int id, const u32 *uv0, const u32 *uv1, const u32 *colour, const float *p, u32 kind,
                           int flag)
{
	float *r = next_record(vv, 0x9070, 0x909c, 92);
	if (!r)
		return;
	const float *M = VV->clip;
	for (int k = 0; k < 4; k++) {
		const float *v = p + k * 3;
		float *o = r + 6 + k * 4;
		for (int c = 0; c < 4; c++)   /* two orders of addition, as in the original */
			o[c] = c == 0 || k == 0 ? f32((X)M[8 + c] * v[2] + (X)M[4 + c] * v[1] + (X)M[c] * v[0] + M[12 + c])
			                        : f32((X)M[8 + c] * v[2] + (X)M[c] * v[0] + (X)M[4 + c] * v[1] + M[12 + c]);
	}
	if (flag == 1 && quad_outside(r)) {
		VV->quadCount--;
		return;
	}
	quad_fields(r, id, uv0, uv1, colour, kind);
}

/* 0x484ca0: a camera-facing quad at p: p to camera space (the matrix at modelview; x and y rounded, z not), its corners
   (x + A.x, y + A.y), (x + B.x, y + A.y), (x + B.x, y + B.y), (x + A.x, y + B.y) at depth z + dz projected by the
   matrix at projection. Corners 0 and 3 are rounded to floats first, 1 and 2 are not, as in the original */
void THISCALL (ViewVolume_addBillboard)(u8 *vv, int id, const u32 *uv0, const u32 *uv1, float dz, const u32 *colour, const float *A,
                           const float *B, const float *p, u32 kind, int flag)
{
	float *r = next_record(vv, 0x9070, 0x909c, 92);
	if (!r)
		return;
	const float *V = VV->modelview, *P = VV->projection;
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
		VV->quadCount--;
		return;
	}
	quad_fields(r, id, uv0, uv1, colour, kind);
}

/* ((a * *ma + b * *mb) + c * *mc) + *t, each product a register times a float from memory */
static X row(X a, const float *ma, X b, const float *mb, X c, const float *mc, const float *t)
{
	X s = fmul_m(a, ma) + fmul_m(b, mb);
	s = s + fmul_m(c, mc);
	return fadd_m(s, t);
}
#define LD(f) fld_m(&(f))

/* 0x4842d0: a triangle (P: three points) into the 0x60-byte records of the list at triangles: taken through the model
   matrix M first when there is one (the first point's coordinates kept unrounded, the others rounded), then the view
   matrix (clip) into clip space (points); with cull 1 dropped when all three are outside one plane. The record:
   id, six words of info (when id >= 0), three more, raw, M; raw 1 keeps the untransformed points (w = 1) instead.
   Every sum in the original's operand order. Returns what the original leaves in eax: the count when full or culled,
   count + 1 for a null list, else raw, or p2.z's bits when raw is 1 */
int THISCALL (ViewVolume_addTriangle)(u8 *vv, int id, const u32 *info6, const u32 *info3, const float *P,
                                         const float *M, int raw, int cull)
{
	int n = VV->triangleCount;
	if (n >= VV->triangleLimit) {
		VV->trianglesFull = 1;
		return n;
	}
	float *rec = AP(float, (VV->triangles + n * 0x60));
	VV->triangleCount = n + 1;
	if (!rec)
		return n + 1;
	const float *V = VV->clip, *p1 = P + 3, *p2 = P + 6;
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
			VV->triangleCount -= 1;
			return VV->triangleCount;
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
	r[0x16] = AV(M);
	return ret;
}

/* 0x483fd0 (thiscall on a view volume): its owned block freed (ownsBlock), its lists cleared (ViewVolume_clear),
   then, if the driver has GL_EXT_vertex_array, the three entry points looked up (glArrays[0..2]) and entryPointsSet
   set. Run by the destructor (tail jump) and first thing in ViewVolume_initBy */
void THISCALL (ViewVolume_release)(u8 *view)
{
	ViewVolume *vw = (ViewVolume *)view;
	if (vw->ownsBlock == 1) {
		operator_delete(AP(void, vw->block));   /* operator delete */
		vw->block = 0;
		vw->ownsBlock = 0;
	}
	ViewVolume_clear(view);   /* ViewVolume_clear */
	const char *extensions = glGetString(0x1f03);   /* glGetString(GL_EXTENSIONS) */
	if (!extensions || !crt_strstr(extensions, AP(const char, STR(0x4c7b5c, "GL_EXT_vertex_array"))))   /* strstr */
		return;
	vw->entryPointsSet = 1;
	static const u32 names[3] = { STR(0x4c7b48, "glVertexPointerEXT"), STR(0x4c7b34, "glColorPointerEXT"), STR(0x4c7b1c, "glTexCoordPointerEXT") };   /* the three entry points' names */
	for (int k = 0; k < 3; k++)
		vw->glArrays[k] = FNREF(wglGetProcAddress(AP(const char, RELOC(names[k]))));   /* wglGetProcAddress */
}

/* a box corner (x stored as a float, y and z kept on the FPU) through the 4 x 4 matrix m into clip space: each row
   m[r] x + m[4 + r] y + m[8 + r] z + m[12 + r], the first two terms of a row being x and y (first corner) or y and z
   (the others), as the original sums them */
static void corner(float *out, const float *m, const float *px, long double y, long double z, int x_first)
{
	for (int r = 0; r < 4; r++) {
		long double tx = fmul_m(fld_m(&m[r]), px), ty = fld_m(&m[4 + r]) * y, tz = fld_m(&m[8 + r]) * z;
		out[r] = f32(fadd_m(x_first ? (tx + ty) + tz : (ty + tz) + tx, &m[12 + r]));
	}
}

/* 0x4853c0 (thiscall on a view volume): every part of model with primitives queued for drawing under the matrix
   (none given: the current GL modelview into the volume's next matrix slot, matrices, matrixCount used of matrixLimit; full:
   matricesFull set and nothing queued). With cull 1 a part whose box (box low, box[3] high) lies wholly beyond one side
   of the clip volume (through the projection clip times the matrix) is left out. Each queued part goes to the end
   of its material's list (material, or the part's texture; plus one; the volume's 0x1c-byte entries entries, entryCount
   used of entryLimit: full sets entriesFull; a material's first entry is listed at materialOrder, materialCount of them; heads materialHeads,
   tails materialTails): the part, its colours (from colours, by the part's colourBase), the light factors, the colour (a tint added), the matrix,
   an extra matrix (multiplied after it; 0 none) */
void THISCALL (ViewVolume_queueModel)(u8 *view, u8 *model, u32 *colours, const float *matrix, u32 factors, u32 colour, int cull,
                                         int material, u32 extraMatrix)
{
	Shape *md = (Shape *)model;
	ViewVolume *vw = (ViewVolume *)view;
	if (md->partCount <= 0)
		return;
	float *m = (float *)matrix;
	if (!m) {
		if (vw->matrixCount >= vw->matrixLimit) {
			vw->matricesFull = 1;
			return;
		}
		m = AP(float, (vw->matrices + vw->matrixCount++ * 0x40));
		if (!m)
			return;
		glGetFloatv(0xba6, m);
	}
	float clip_m[16];
	Mat4_multiply(clip_m, vw->clip, m);
	for (int i = 0; i < md->partCount; i++) {
		u8 *part = AP(u8, md->parts + i * 0x80);
		ShapePart *sp = (ShapePart *)part;
		if (sp->primCount <= 0)
			continue;
		if (cull == 1) {
			const float *lo = sp->box, *hi = &sp->box[3];
			static const u8 pick[7][3] = { { 0, 1, 1 }, { 1, 1, 1 }, { 0, 1, 0 }, { 1, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 0, 0, 0 } };
			float c[8][4], p[3];
			for (int k = 0; k < 7; k++) {
				long double z = fld_m(pick[k][2] ? &hi[2] : &lo[2]), y = fld_m(pick[k][1] ? &hi[1] : &lo[1]);
				p[0] = f32(fld_m(pick[k][0] ? &hi[0] : &lo[0]));
				corner(c[k], clip_m, &p[0], y, z, k == 0);
			}
			p[0] = f32(fld_m(&hi[0]));
			p[1] = f32(fld_m(&lo[1]));
			p[2] = f32(fld_m(&lo[2]));
			Mat4_transformPoint(c[7], clip_m, p);
			u32 all = 0x111111;
			for (int k = 0; k < 8; k++) {
				long double w = c[k][3], nw = -w;
				u32 out = 0;
				for (int a = 0; a < 3; a++) {
					if (nw >= c[k][a])   /* (a NaN counts as inside, as fcom has it) */
						out |= 1u << (a * 8);
					else if (c[k][a] >= w)
						out |= 0x10u << (a * 8);
				}
				all &= out;
			}
			if ((all & 0x11) || (all & 0x111100))
				continue;
		}
		int list = (material >= 0 ? material : sp->texture) + 1;
		if (vw->entryCount >= vw->entryLimit) {
			vw->entriesFull = 1;
			return;
		}
		u32 *e = AP(u32, (vw->entries + vw->entryCount++ * 0x1c));
		if (!e)
			return;
		if (vw->materialHeads[list] == 0) {
			vw->materialOrder[vw->materialCount] = list;
			vw->materialCount++;
			vw->materialHeads[list] = AREF((u8 *)e);
		}
		u32 *tail = AP(u32, (vw)->materialTails[list]);
		if (tail)
			tail[6] = AV(e);
		vw->materialTails[list] = AREF((u8 *)e);
		e[0] = AV(part);
		e[1] = colours ? AV((colours + sp->colourBase)) : 0;
		e[2] = factors;
		e[3] = colour;
		e[4] = AV(m);
		e[5] = extraMatrix;
		e[6] = 0;
	}
}

/* ---- ViewVolume_draw: drawing what was queued ---- */

typedef void (STDCALL *ArrayFn)(int size, u32 type, int stride, int count, const void *p);   /* glArrays.. (an extension's) */

/* the fog range (start, end) back with fog on, when it was on; else fog off */
static void fog_set(u8 on, const float *range)
{
	if (on == 1) {
		glFogf_stored(GL_FOG_START, BITS(range[0]));
		glFogf_stored(GL_FOG_END, BITS(range[1]));
		glEnable(GL_FOG);
	} else
		glDisable(GL_FOG);
}

static void load_matrices(const float *projection, const float *modelview)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(projection);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(modelview);
}

static void identity_matrices(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* texture t (an id: manager t / 512, slot t % 512) bound, counted in textureBinds */
static void bind(u8 *vv, int t)
{
	glEnable(GL_TEXTURE_2D);
	tex_bind(AP(TextureManager, g_textures)->banks[t / 512], t % 512);
	VV->textureBinds++;
}

/* a queued record's texture: bound, or texturing off for none (< 0) or mode 2 (untextured) */
static void use_texture(u8 *vv, int t, int mode)
{
	if (t >= 0 && mode != 2)
		bind(vv, t);
	else
		glDisable(GL_TEXTURE_2D);
}

/* texture t's scrolling (its record's scrollMode): 1 / 2 v / u up by b, 3 / 4 down, else none */
static int tex_scroll(int t) { return ((TextureBank *)AP(TextureManager, g_textures)->banks[t / 512])->records[t % 512].scrollMode; }

static void scroll(float *uv, int n, int kind, const float *b)
{
	for (int i = 0; i < n; i++) {
		float *c = &uv[2 * i + (kind == 1 || kind == 3)];
		if (kind == 1 || kind == 2)
			*c = (float)fadd_m(fld_m(b), c);
		else if (kind == 3 || kind == 4)
			*c = (float)fsub_m(fld_m(c), b);
	}
}

/* the colour buffer (colours, room for colourLimit vertices) about to take the mesh's colours: 0 when they do not fit;
   the most so far kept in colourMost */
static int fits(u8 *vv, const u8 *mesh)
{
	int n = ((const ShapePart *)mesh)->vertexCount;
	if (n > VV->colourLimit)
		return 0;
	if (VV->colourMost < n)
		VV->colourMost = n;
	return 1;
}

/* the inverse of m, or the identity when it has none */
static void invert(float *inv, const float *m)
{
	if (!Mat4_invert(inv, m)) {
		memset(inv, 0, 64);
		inv[0] = inv[5] = inv[10] = inv[15] = 1.0f;
	}
}

/* an item's vertex colours: its own (+4), the mesh's (colours), or either lit by the factors (+8, through the inverse
   of the item's matrix) and / or tinted (+0xc) in the colour buffer. NULL when the mesh does not fit the buffer */
static const u32 *item_colours(u8 *vv, const u32 *it, const u8 *mesh)
{
	u8 *buf = AP(u8, VV->colours);
	const u8 *colours = AP(const u8, RELOC(it[1])), *factors = AP(const u8, RELOC(it[2]));
	float inv[16];
	if (colours) {
		if (mesh[0] & 2)
			return (const u32 *)colours;
		if (factors) {
			if (!fits(vv, mesh))
				return NULL;
			memcpy(buf, colours, (u32)((const ShapePart *)mesh)->vertexCount * 4);
			invert(inv, AP(const float, RELOC(it[4])));
			shape_getShadingColorBufferBy(buf, 0, mesh, factors, inv);
			if (it[3])
				part_addColour(buf, 0, (const u32 *)mesh, AP(const u8, RELOC(it[3])));
			return (const u32 *)buf;
		}
		if (it[3]) {
			if (!fits(vv, mesh))
				return NULL;
			memcpy(buf, colours, (u32)((const ShapePart *)mesh)->vertexCount * 4);
			part_addColour(buf, 0, (const u32 *)mesh, AP(const u8, RELOC(it[3])));
			return (const u32 *)buf;
		}
		return (const u32 *)colours;
	}
	if ((mesh[0] & 2) && !it[3])
		return (AP(const u32, ((const ShapePart *)mesh)->colours));
	if (factors) {
		invert(inv, AP(const float, RELOC(it[4])));
		if (!fits(vv, mesh))
			return NULL;
		shape_getShadingColorBufferBy(buf, 1, mesh, factors, inv);
		if (it[3])
			part_addColour(buf, 0, (const u32 *)mesh, AP(const u8, RELOC(it[3])));
		return (const u32 *)buf;
	}
	if (it[3]) {
		if (!fits(vv, mesh))
			return NULL;
		part_addColour(buf, 1, (const u32 *)mesh, AP(const u8, RELOC(it[3])));
		return (const u32 *)buf;
	}
	return (AP(const u32, ((const ShapePart *)mesh)->colours));
}

/* an opaque mesh from vertex arrays (an extension's array functions at glArrays[0] / glArrays[1] / glArrays[2] when set): positions,
   colours, texture coordinates when textured (a copy in uvs when the texture scrolls), under the item's matrices;
   culling by flags 4 (none) / 8 (front), flag 0x10 no depth test; its polygons (primCount, prims: mode, count,
   indices) counted as triangles in trianglesDrawn */
static void draw_opaque(u8 *vv, const u32 *it, const u8 *mesh, const u32 *col, int id, const float *b, float *uvs)
{
	ArrayFn fn;
	glEnableClientState(0x8074);
	if ((fn = FNP(ArrayFn, VV->glArrays[0])))
		fn(3, 0x1406, 0, ((const ShapePart *)mesh)->vertexCount, (AP(void, ((const ShapePart *)mesh)->vertices)));
	else
		glVertexPointer(3, 0x1406, 0, (AP(void, ((const ShapePart *)mesh)->vertices)));
	glEnableClientState(0x8076);
	if ((fn = FNP(ArrayFn, VV->glArrays[1])))
		fn(4, 0x1401, 0, ((const ShapePart *)mesh)->vertexCount, col);
	else
		glColorPointer(4, 0x1401, 0, col);
	if (id > 0) {
		const float *uv = (AP(const float, ((const ShapePart *)mesh)->texCoords));
		int kind = tex_scroll(id - 1);
		if (kind) {
			memcpy(uvs, uv, (u32)((const ShapePart *)mesh)->vertexCount * 8);
			scroll(uvs, ((const ShapePart *)mesh)->vertexCount, kind, b);
			uv = uvs;
		}
		glEnableClientState(0x8078);
		if ((fn = FNP(ArrayFn, VV->glArrays[2])))
			fn(2, 0x1406, 0, ((const ShapePart *)mesh)->vertexCount, uv);
		else
			glTexCoordPointer(2, 0x1406, 0, uv);
	} else
		glDisableClientState(0x8078);
	glPushMatrix();
	glMultMatrixf(AP(const float, RELOC(it[4])));
	if (it[5])
		glMultMatrixf(AP(const float, RELOC(it[5])));
	if (mesh[0] & 4)
		glDisable(0xb44);
	else {
		glEnable(0xb44);
		glCullFace(mesh[0] & 8 ? 0x404 : 0x405);
	}
	if (mesh[0] & 0x10)
		glDisable(GL_DEPTH_TEST);
	else
		glEnable(GL_DEPTH_TEST);
	for (int p = 0; p < ((const ShapePart *)mesh)->primCount; p++) {
		const u32 *pg = (AP(const u32, ((const ShapePart *)mesh)->prims)) + p * 3;
		glDrawElements(pg[0], pg[1], 0x1405, AP(const void, RELOC(pg[2])));
		int c = (int)pg[1];
		if (pg[0] == 4)
			VV->trianglesDrawn += c / 3;
		else if (pg[0] == 5 || pg[0] == 6)
			VV->trianglesDrawn += c - 2;
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(0xb44);
	glPopMatrix();
}

/* per point and coordinate (x, y, z), the order the original sums the three products in */
static const char k_texturedOrder[] = "201201102" "201021210" "201021021";
static const char k_plainOrder[] = "102021021" "021210210" "201210021";

/* point p through M (columns) */
static void through(float *out, const float *M, const float *p, const char *order)
{
	for (int r = 0; r < 3; r++, order += 3) {
		int a = order[0] - '0', b = order[1] - '0', c = order[2] - '0';
		out[r] = (float)row(LD(p[a]), &M[4 * a + r], LD(p[b]), &M[4 * b + r], LD(p[c]), &M[4 * c + r], &M[12 + r]);
	}
}

/* a transparent mesh: its triangle lists (mode 4) one triangle at a time through the item's matrices (the product
   of both when there are two) into the view volume's list, with texture coordinates (scrolled) when textured */
static void draw_transparent(u8 *vv, const u32 *it, const u8 *mesh, const u32 *col, int id, const float *b)
{
	for (int p = 0; p < ((const ShapePart *)mesh)->primCount; p++) {
		const u32 *pg = (AP(const u32, ((const ShapePart *)mesh)->prims)) + p * 3;
		int count = (int)pg[1];
		const u32 *idx = AP(const u32, RELOC(pg[2]));
		float product[16];
		const float *M = AP(const float, RELOC(it[4]));
		if (it[5]) {
			Mat4_multiply(product, AP(const float, RELOC(it[4])), AP(const float, RELOC(it[5])));
			M = product;
		}
		if (pg[0] != 4 || count <= 0)
			continue;
		for (u32 t = ((u32)count + 2) / 3; t; t--, idx += 3) {
			float uv[6], P[9];
			u32 c[3];
			const char *order = id > 0 ? k_texturedOrder : k_plainOrder;
			if (id > 0) {
				for (int k = 0; k < 3; k++)
					memcpy(&uv[2 * k], (AP(const float, ((const ShapePart *)mesh)->texCoords)) + idx[k] * 2, 8);
				int kind = tex_scroll(id - 1);
				if (kind)
					scroll(uv, 3, kind, b);
			}
			for (int k = 0; k < 3; k++)
				c[k] = col[idx[k]];
			for (int k = 0; k < 3; k++)
				through(P + 3 * k, M, (AP(const float, ((const ShapePart *)mesh)->vertices)) + idx[k] * 3, order + 9 * k);
			if (id > 0)
				ViewVolume_addTriangle(vv, id - 1, (const u32 *)uv, c, P, NULL, 2, 1);
			else
				ViewVolume_addTriangle(vv, 0, NULL, c, P, NULL, 2, 1);
		}
	}
}

/* a queued triangle (0x60-byte record): colours (+0x1c), texture coordinates (+4) when textured, clip-space points
   (points, w used by four) */
static void triangle(const u32 *r, int textured, int four)
{
	for (int k = 0; k < 3; k++) {
		glColor4ubv(r + 7 + k);
		if (textured)
			glTexCoord2fv(r + 1 + 2 * k);
		if (four)
			glVertex4fv(r + 10 + 4 * k);
		else
			glVertex3fv((const float *)(RELOC(r) + 10 + 4 * k));
	}
}

/* a queued billboard (0x5c-byte record): colour (colour), its four points (points[3] back to points) with the corners'
   texture coordinates (from +4 and uv1) when textured */
static void billboard(const u32 *r, int textured)
{
	glColor4ubv(r + 5);
	if (textured) {
		glTexCoord2fv(r + 1);
		glVertex4fv(r + 0x12);
		glTexCoord2f_bits(r[3], r[2]);
		glVertex4fv(r + 0xe);
		glTexCoord2fv(r + 3);
		glVertex4fv(r + 10);
		glTexCoord2f_bits(r[1], r[4]);
	} else {
		glVertex4fv(r + 0x12);
		glVertex4fv(r + 0xe);
		glVertex4fv(r + 10);
	}
	glVertex4fv(r + 6);
}

static const float k_third = -0.33333334f, k_half = -0.5f;   /* the depth keys: minus the mean z */

/* 0x485af0: draw what ViewVolume_queueModel queued (mode 1 wireframe, 2 untextured; b the texture scroll).
   Under the view volume's matrices (projection / modelview) and the caller's fog: per material (count materialCount, ids materialOrder:
   0 none, else the texture id + 1) its item chain (materialHeads + id * 4: mesh, colours, factors, tint, matrix, second
   matrix, next), opaque meshes drawn, transparent ones (flag 1, or a second matrix) queued as triangles. Then the
   queued triangles with the first list kind (1) as they are, the lines (segments), and the rest depth-sorted and
   merged back to front with the billboards (kind 2), billboards of kind 3 last; the fog range mapped through the
   projection (projection[10]..) for the identity-matrix passes. A mesh too big for the colour buffer is retried forever,
   as the original does */
void THISCALL (ViewVolume_draw)(u8 *vv, int mode, float b)
{
	float projection[16], modelview[16], mapped[2] = { 0, 0 };
	float range[17] = { 0, 0 };   /* the fog range; as in the original's frame, a whole matrix fits after each value */
	float uvs[0x7cc];
	u8 fog;
	glGetFloatv(0xba7, projection);
	glGetFloatv(0xba6, modelview);
	if (mode == 1) {
		glPolygonMode(0x408, 0x1b01);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	glGetBooleanv(GL_FOG, &fog);
	if (fog == 1) {
		glGetFloatv(GL_FOG_START, &range[0]);
		glGetFloatv(GL_FOG_END, &range[1]);
		for (int k = 0; k < 2; k++) {
			X z = -fld_m(&range[k]);
			float x = f32(fadd_m(fmul_m(z, &VV->projection[10]), &VV->projection[14]));
			X w = fadd_m(fmul_m(z, &VV->projection[11]), &VV->projection[15]);
			mapped[k] = (float)(fld_m(&x) / w);
		}
	}
	load_matrices(&VV->projection[0], &VV->modelview[0]);
	fog_set(fog, range);
	VV->colourMost = 0;

	for (int i = 0; i < VV->materialCount; i++) {
		int id = VV->materialOrder[i];
		const u32 *it = AP(const u32, VV->materialHeads[id]);
		if (id > 0 && mode != 2)
			bind(vv, id - 1);
		do {
			VV->meshesDrawn++;
			const u8 *mesh = AP(const u8, RELOC(it[0]));
			const u32 *col = item_colours(vv, it, mesh);
			if (!col)
				continue;
			if (!(mesh[0] & 1) && !it[5])
				draw_opaque(vv, it, mesh, col, id, &b, uvs);
			else
				draw_transparent(vv, it, mesh, col, id, &b);
			it = AP(const u32, RELOC(it[6]));
		} while (it);
		if (id > 0)
			glDisable(GL_TEXTURE_2D);
	}

	/* the queued triangles of kind 1, each under its own matrix (matrix) */
	load_matrices(&VV->projection[0], &VV->modelview[0]);
	fog_set(fog, range);
	int cur = -1;
	glEnable(0xb44);
	glCullFace(0x405);
	glEnable(0x8037);
	glPolygonOffset(-1.0f, -1.0f);
	for (int i = 0; i < VV->triangleCount; i++) {
		const u32 *r = AP(const u32, (VV->triangles + i * 0x60));
		if (r[0x17] != 1)
			continue;
		glPushMatrix();
		if (r[0x16])
			glMultMatrixf(AP(const float, RELOC(r[0x16])));
		if ((int)r[0] != cur) {
			cur = (int)r[0];
			use_texture(vv, cur, mode);
		}
		glBegin(4);
		triangle(r, cur >= 0, 0);
		glEnd();
		VV->trianglesDrawn++;
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(0x8037);

	/* the lines (0x24 bytes: colour, two points) */
	identity_matrices();
	fog_set(fog, mapped);
	glBegin(GL_LINES);
	glColor4ub(0xff, 0xff, 0xff, 0xff);
	for (int i = 0; i < VV->segmentCount; i++) {
		const u8 *l = AP(const u8, VV->segments + i * 0x24);
		glColor3ub(l[0], l[1], l[2]);
		glVertex4fv(l + 4);
		glVertex4fv(l + 0x14);
	}
	glEnd();

	/* the depth lists (record, key): triangles of kind 2, billboards of kinds 2 and 3 */
	VV->triangleOrderCount = 0;
	for (int i = 0; i < VV->triangleCount; i++) {
		u8 *r = AP(u8, VV->triangles + i * 0x60);
		if (((ViewTriangle *)r)->kind != 2)
			continue;
		AP(APTR(u8), VV->triangleOrder)[VV->triangleOrderCount * 2] = AREF(r);
		X z = fadd_m(FADD(((ViewTriangle *)r)->points[2][2], ((ViewTriangle *)r)->points[1][2]), &((ViewTriangle *)r)->points[0][2]);
		(AP(float, VV->triangleOrder))[VV->triangleOrderCount * 2 + 1] = (float)fmul_m(z, &k_third);
		VV->triangleOrderCount++;
	}
	VV->quadOrderACount = 0;
	VV->quadOrderBCount = 0;
	for (int i = 0; i < VV->quadCount; i++) {
		u8 *r = AP(u8, VV->quads + i * 0x5c);
		int list = ((ViewQuad *)r)->kind == 2 ? offsetof(ViewVolume, quadOrderA) : ((ViewQuad *)r)->kind == 3 ? offsetof(ViewVolume, quadOrderB) : 0;
		if (!list)
			continue;
		AP(APTR(u8), FIELD(APTR(APTR(u8)), vv, list))[FIELD(int, vv, list + 4) * 2] = AREF(r);
		X z = FADD(((ViewQuad *)r)->points[1][2], ((ViewQuad *)r)->points[0][2]);
		AP(float, FIELD(APTR(float), vv, list))[FIELD(int, vv, list + 4) * 2 + 1] = (float)fmul_m(z, &k_half);
		FIELD(int, vv, list + 4)++;
	}

	/* triangles and billboards merged back to front (triangles fogged when fog is on, billboards never) */
	identity_matrices();
	fog_set(fog, mapped);
	render_depthSortTriangles((AP(u32, VV->triangleOrder)), 0, VV->triangleOrderCount - 1);
	render_depthSortBillboards((AP(u32, VV->quadOrderA)), 0, VV->quadOrderACount - 1);
	int ia = 0, ib = 0, drawingTriangles = 0;
	cur = -1;
	glDisable(0xb44);
	glDisable(GL_FOG);
	glBegin(GL_QUADS);
	const float *a = VV->triangleOrderCount > 0 ? (AP(const float, VV->triangleOrder)) : NULL;
	const float *q = VV->quadOrderACount > 0 ? (AP(const float, VV->quadOrderA)) : NULL;
	while (a || q) {
		if (a && (!q || !(fld_m(&a[1]) >= fld_m(&q[1])))) {
			if (drawingTriangles != 1) {
				glEnd();
				if (fog)
					glEnable(GL_FOG);
				glBegin(4);
				drawingTriangles = 1;
			}
			const u32 *r = AP(const u32, *(const u32 *)a);
			if ((int)r[0] != cur) {
				glEnd();
				cur = (int)r[0];
				use_texture(vv, cur, mode);
				glBegin(4);
			}
			triangle(r, cur >= 0, 1);
			VV->trianglesDrawn++;
			ia++;
			a = ia < VV->triangleOrderCount ? (AP(const float, VV->triangleOrder)) + ia * 2 : NULL;
		} else {
			if (drawingTriangles != 0) {
				glEnd();
				glDisable(GL_FOG);
				glBegin(GL_QUADS);
				drawingTriangles = 0;
			}
			const u32 *r = AP(const u32, *(const u32 *)q);
			if ((int)r[0] != cur) {
				glEnd();
				cur = (int)r[0];
				use_texture(vv, cur, mode);
				glBegin(GL_QUADS);
			}
			billboard(r, cur >= 0);
			VV->trianglesDrawn += 2;
			ib++;
			q = ib < VV->quadOrderACount ? (AP(const float, VV->quadOrderA)) + ib * 2 : NULL;
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	identity_matrices();
	glDisable(GL_FOG);

	/* the billboards of kind 3, unfogged, without depth test */
	render_depthSortBillboards((AP(u32, VV->quadOrderB)), 0, VV->quadOrderBCount - 1);
	cur = -1;
	glDisable(0xb44);
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	for (int i = 0; i < VV->quadOrderBCount; i++) {
		const u32 *r = AP(const u32, AP(APTR(const u32), VV->quadOrderB)[i * 2]);
		if ((int)r[0] != cur) {
			glEnd();
			cur = (int)r[0];
			use_texture(vv, cur, mode);
			glBegin(GL_QUADS);
		}
		billboard(r, cur >= 0);
		VV->trianglesDrawn += 2;
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	fog_set(fog, range);
	if (mode == 1)
		glPolygonMode(0x408, 0x1b02);
	load_matrices(projection, modelview);
}
