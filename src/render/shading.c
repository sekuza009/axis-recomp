/* shading.c: a shape part's vertex colours lit by the scene's light factors */
#include "../game.h"
#include <string.h>

/* a shape part (0x80 bytes): flags (bit 1: unlit, full white), its vertices, normals and base colours (RGBA bytes),
   and its bounding box */
typedef struct {
	u32 flags;
	u8 _04[0x48];
	int count;
	const float *verts;     /* +0x50 */
	const float *normals;   /* +0x54 */
	const u8 *base;         /* +0x58 */
	u8 _5c[0xc];
	float min[3], max[3];   /* +0x68 */
} Part;

/* a light factor (0x2c bytes, scene.fields' Factor): kind 0 ambient, 1 directional, 2 a point light fading over its radius, 3 a point
   light falling off with the square of the distance */
typedef struct {
	u32 _00, _04;
	int type;
	u8 colour[4];   /* +0xc */
	float pos[3];   /* +0x10 */
	float dir[3];   /* +0x1c */
	float radius;   /* +0x28 */
} Light;

#define MUL(a, b) fmul_m(fld_m(a), b)
#define LIGHT_COUNT(factors) (((const LightFactors *)(factors))->count)

static int clamp255(int v) { return v < 0xff ? v : 0xff; }

/* the original's imul: products wrap */
static int mul(int a, int b) { return (int)((u32)a * (u32)b); }

/* the factor 1 - dot scaled to 0 .. 256 (none below 0) */
static int facing(long double dot)
{
	int k = ftol(fmul_m(fsubr_m(dot, &k_1f), &k_128f));
	return k < 0 ? 0 : k;
}

/* a vertex's offset from a light at p: the vector into d, its squared length returned unrounded */
static long double offset(const float *v, const float *p, float *d)
{
	d[0] = f32(FSUB(v[0], p[0]));
	d[1] = f32(FSUB(v[1], p[1]));
	d[2] = f32(FSUB(v[2], p[2]));
	return (MUL(&d[2], &d[2]) + MUL(&d[1], &d[1])) + MUL(&d[0], &d[0]);
}

/* one vertex's colour: written whole (alpha 255) when first, else added to what is there; each channel clamped */
static void put(u8 *o, int first, int r, int g, int b)
{
	if (first) {
		o[0] = (u8)clamp255(r);
		o[1] = (u8)clamp255(g);
		o[2] = (u8)clamp255(b);
		o[3] = 0xff;
	} else {
		o[0] = (u8)clamp255(r + o[0]);
		o[1] = (u8)clamp255(g + o[1]);
		o[2] = (u8)clamp255(b + o[2]);
	}
}

/* 0x463b80: the part's vertex colours (out, 4 bytes each) under the factors (count count, records from +4), the
   lights' positions and directions through the matrix when one is given. first = 1 writes the first factor (then
   it is 0), the others are added. No factors (when first) give black, an unlit part white; a point light (2) whose
   reach misses the part's box blackens it when first; an unknown kind is fatal. The original leaves eax to callers
   that ignore it */
void (shape_getShadingColorBufferBy)(u8 *out, int first, const Part *part, const u8 *factors, const float *m)
{
	if (LIGHT_COUNT(factors) <= 0 && first == 1) {
		memset(out, 0, part->count * 4);
		return;
	}
	if (part->flags & 2) {
		memset(out, 0xff, part->count * 4);
		return;
	}
	for (int i = 0; i < LIGHT_COUNT(factors); i++) {
		const Light *l = (const Light *)(factors + 4) + i;
		int R = l->colour[0], G = l->colour[1], B = l->colour[2];
		float p[3], d[3];
		switch (l->type) {
		case 0:   /* ambient */
			if (first == 1) {
				for (int j = 0; j < part->count; j++)
					memcpy(out + j * 4, l->colour, 4);
				first = 0;
			} else
				for (int j = 0; j < part->count; j++)
					put(out + j * 4, 0, R, G, B);
			break;
		case 1: {   /* directional: the base colour by how much each normal faces away from it */
			float L[3];
			if (m) {
				L[0] = f32((MUL(&m[8], &l->dir[2]) + MUL(&m[4], &l->dir[1])) + MUL(&l->dir[0], &m[0]));
				L[1] = f32((MUL(&m[1], &l->dir[0]) + MUL(&m[9], &l->dir[2])) + MUL(&m[5], &l->dir[1]));
				L[2] = f32((MUL(&m[2], &l->dir[0]) + MUL(&m[10], &l->dir[2])) + MUL(&m[6], &l->dir[1]));
			} else
				memcpy(L, l->dir, sizeof L);
			for (int j = 0; j < part->count; j++) {
				const float *n = part->normals + j * 3;
				const u8 *b = part->base + j * 4;
				int k = facing((MUL(&L[2], &n[2]) + MUL(&L[1], &n[1])) + MUL(&L[0], &n[0]));
				put(out + j * 4, first == 1, mul(mul(b[0], k), R) >> 16, mul(mul(b[1], k), G) >> 16, mul(mul(b[2], k), B) >> 16);
			}
			if (first == 1)
				first = 0;
			break;
		}
		case 2: {   /* a point light, full within a quarter of its squared radius and fading out to the radius */
			if (m) {
				p[0] = f32(((MUL(&m[8], &l->pos[2]) + MUL(&m[4], &l->pos[1])) + MUL(&m[0], &l->pos[0])) + m[12]);
				p[1] = f32(((MUL(&m[1], &l->pos[0]) + MUL(&m[9], &l->pos[2])) + MUL(&m[5], &l->pos[1])) + m[13]);
				p[2] = f32(((MUL(&m[2], &l->pos[0]) + MUL(&m[10], &l->pos[2])) + MUL(&m[6], &l->pos[1])) + m[14]);
			} else
				memcpy(p, l->pos, sizeof p);
			const float r = l->radius;
			int reaches = 1;
			for (int a = 0; a < 3; a++)
				if (!(FADD(p[a], r) > part->min[a]) || FSUB(p[a], r) >= part->max[a])
					reaches = 0;
			if (!reaches) {
				if (first == 1)
					memset(out, 0, part->count * 4);
				break;
			}
			long double rr = MUL(&r, &r);
			float r2 = f32(rr), inner = f32(fmul_m(rr, &k_0_2f));
			float range = f32(FSUB(r2, inner));
			for (int j = 0; j < part->count; j++) {
				const u8 *b = part->base + j * 4;
				long double dd = offset(part->verts + j * 3, p, d);
				float d2 = f32(dd);
				if (dd >= r2) {   /* out of reach */
					if (first == 1)
						memcpy(out + j * 4, &g_unlit, 4);
					continue;
				}
				if (d2 > inner) {
					int k = ftol(fmul_m(fsubr_m(fdiv_m(FSUB(d2, inner), &range), &k_1f), &k_256f));
					if (k > 0x100)
						k = 0x100;
					if (first == 1)
						Vec3_normalize(d);   /* (its result unused) */
					put(out + j * 4, first == 1, mul(mul(k, R) >> 8, b[0]) >> 8, mul(mul(k, G) >> 8, b[1]) >> 8,
					    mul(mul(k, B) >> 8, b[2]) >> 8);
				} else
					put(out + j * 4, first == 1, (b[0] * R) >> 8, (b[1] * G) >> 8, (b[2] * B) >> 8);
			}
			if (first == 1)
				first = 0;
			break;
		}
		case 3: {   /* a point light falling off with the squared distance beyond a fifth (k_0_04f) of the squared
		               radius, its colour by how the normals face it */
			if (m) {
				p[0] = f32(((MUL(&m[8], &l->pos[2]) + MUL(&m[4], &l->pos[1])) + MUL(&l->pos[0], &m[0])) + m[12]);
				p[1] = f32(((MUL(&m[9], &l->pos[2]) + MUL(&m[5], &l->pos[1])) + MUL(&m[1], &l->pos[0])) + m[13]);
				p[2] = f32(((MUL(&m[10], &l->pos[2]) + MUL(&m[6], &l->pos[1])) + MUL(&m[2], &l->pos[0])) + m[14]);
			} else
				memcpy(p, l->pos, sizeof p);
			const float r = l->radius;
			long double rr = MUL(&r, &r);
			float r2 = f32(rr), inner = f32(fmul_m(rr, &k_0_04f));
			for (int j = 0; j < part->count; j++) {
				const float *n = part->normals + j * 3;
				const u8 *b = part->base + j * 4;
				long double dd = offset(part->verts + j * 3, p, d);
				float d2 = f32(dd);
				if (dd >= r2) {
					if (first == 1)
						memcpy(out + j * 4, &g_unlit, 4);
					continue;
				}
				if (d2 > inner) {
					int k = ftol(fdiv_m(FMUL(inner, k_256f), &d2));
					if (k > 0x100)
						k = 0x100;
					int cr = mul(k, R) >> 8, cg = mul(k, G) >> 8, cb = mul(k, B) >> 8;
					Vec3_normalize(d);
					int f = facing((MUL(&d[2], &n[2]) + MUL(&d[1], &n[1])) + MUL(&d[0], &n[0]));
					put(out + j * 4, first == 1, mul(mul(b[0], cr), f) >> 16, mul(mul(b[1], cg), f) >> 16, mul(mul(b[2], cb), f) >> 16);
				} else
					put(out + j * 4, first == 1, (b[0] * R) >> 8, (b[1] * G) >> 8, (b[2] * B) >> 8);
			}
			if (first == 1)
				first = 0;
			break;
		}
		default:
			sys_errorTerminate((const char *)STR(0x4c4a4c, "light factor type(%d) not yet impleme..."), l->type);
		}
	}
}

/* a light's colour (bytes +4 .. +6) at intensity i: each (c x i) / 256, added to base (when given), at most 255 */
static void light_mix(u8 *out, const u8 *light, int i, const u8 *base)
{
	for (int c = 0; c < 3; c++) {
		int v = light[4 + c] * i / 256 + (base ? base[c] : 0);
		out[c] = (u8)(v > 0xff ? 0xff : v);
	}
	out[3] = 0xff;
}

/* the intensity ((1 - d) x k_128f, at least 0) of a light at the cosine d */
static int light_level(long double d)
{
	int i = ftol(fmul_m(fld_m(&k_1f) - d, &k_128f));
	return i < 0 ? 0 : i;
}

/* 0x472400 (thiscall on the scene): a ground layer's vertex colours (RGBA into cols) over rows r0 .. r1 and columns
   c0 .. c1 of its grid (cols + 1 wide; normals at normals): for each directional light (the scene's 0x2c-byte light
   records from mapLights.records[].kind, mapLights.count of them: kind 1; 0 and 2 are skipped, another kind is a fatal message) the
   intensity from the normal against its direction (dir), the first written (first == 1), the rest added; a water
   layer (water 1) gets the light from straight above (from below, -1, for a layer of kind 1) in its 12 box colours
   (waterColours) too. A kind-2 layer only clears its light map (colours) and box colours. Its caller ignores the
   eax it leaves */
void THISCALL (light_computeLayerLightBy)(Stage *scene, u8 *layer, u8 *cols, int first, int r0, int c0, int r1, int c1)
{
	GroundLayer *gl = (GroundLayer *)layer;
	if (gl->kind == 2) {
		memset(((void *)(gl)->colours), 0xff, (gl->cols + 1) * (gl->rows + 1) * 4);
		if (gl->water == 1)
			memset(gl->waterColours, 0xff, 12 * 4);
		return;
	}
	const LightFactors *lights = &scene->mapLights;
	for (int li = 0; li < lights->count; li++) {
		const Factor *fc = &lights->records[li];
		const u8 *light = (const u8 *)&fc->kind;   /* (light_mix takes the factor from its kind on) */
		const float *dir = (const float *)fc->dir;   /* (a kind 1 light's direction) */
		int kind = fc->kind;
		if (kind == 0 || kind == 2)
			continue;
		if (kind != 1) {
			sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4c74a8, "light factor type(%d) not yet impleme..."), kind);
			continue;
		}
		for (int row = r0; row <= r1; row++)
			for (int col = c0; col <= c1; col++) {
				int v = (gl->cols + 1) * row + col;
				const float *n = ((const float *)(gl)->normals) + v * 3;
				int i = light_level(MUL(&n[1], &dir[1]) + MUL(&n[2], &dir[2]) + MUL(&dir[0], &n[0]));
				light_mix(cols + v * 4, light, i, first == 1 ? NULL : cols + v * 4);
			}
		if (gl->water == 1) {
			const float *above = gl->kind == 1 ? &k_m1f : &k_1f;
			int i = light_level(MUL(above, &dir[1]));
			u8 sky[4];
			light_mix(sky, light, i, first == 1 ? NULL : (const u8 *)gl->waterColours);
			for (int k = 0; k < 12; k++)
				memcpy(&gl->waterColours[k], sky, 4);
		}
		first = 0;
	}
}

/* the two indices of column c's edge between rows r and r + 1 added to the open strip (the layer's index heap indices,
   indexCount used, at most indexCapacity: past it a fatal message) */
static void strip_pair(u8 *layer, u32 *idx, int *n, int r, int c, int w)
{
	GroundLayer *gl = (GroundLayer *)layer;
	if (gl->indexCount + 2 > gl->indexCapacity)
		sys_fatalErrorN((char *)OBJ(g_logStage), (const char *)STR(0x4d052c, "primitiveElementIndexHeap overflow(%d..."), gl->indexCount + 2, gl->indexCapacity);
	idx[(*n)++] = r * w + c;
	gl->indexCount++;
	idx[(*n)++] = (r + 1) * w + c;
	gl->indexCount++;
}

/* a water vertex: v turned about the vertical by angle, moved to the camera, stored with its texture coordinates (its
   x and z over the layer's texture size texScale) */
static void water_point(u8 *scene, u8 *layer, u8 *part, int at, int tex_at, float *v, int angle)
{
	GroundLayer *gl = (GroundLayer *)layer;
	ShapePart *sp = (ShapePart *)part;
	Stage *st = (Stage *)scene;
	Vec3_rotateAxis(v, 2, angle);
	v[0] = f32(FADD(v[0], st->cameraPos[0]));
	v[2] = f32(FADD(v[2], st->cameraPos[2]));
	memcpy(sp->vertices + at, v, 12);
	float *t = (float *)(((u8 *)(sp)->texCoords) + tex_at);
	t[0] = f32(FDIV(v[0], gl->texScale));
	t[1] = f32(FDIV(v[2], gl->texScale));
}

/* 0x497d20 (thiscall on the scene): the ground's drawing lists for this frame. For each layer (0x20c bytes from
   groundLayers, groundLayerCount of them: origin +4, rows rows, columns cols, cell size cellSize, cell bitmap flat) the cells
   (bit 0 set) within the view range (cullMargin) of the camera (cameraPos / 78) become triangle strips (type 5, from the
   layer's primitive heap strips, stripCount of them, at most stripCapacity: a fatal message) of grid indices, into the part of the
   first terrain model (layerModel.parts, 0x80 bytes a layer: its colours, primCount). A water layer (water 1) gives the second
   model's part (waterModel.parts) its surface around the camera at its height (+8): rings of four and of eight (the second
   h x k_m1_5f out) with texture coordinates; otherwise that part has none. Both models then go to the view volume's
   queue (ViewVolume_projectObject). Its callers ignore the eax it leaves */
void THISCALL (ground_buildDrawLists)(u8 *s, void *view, float h)
{
	Stage *st = (Stage *)s;
	const float *range = &st->cullMargin, *cam = st->cameraPos;
	float min_x = f32(fsub_m(fld_m(&cam[0]), range)), min_z = f32(fsub_m(fld_m(&cam[2]), range));
	float max_x = f32(fadd_m(fld_m(range), &cam[0])), max_z = f32(fadd_m(fld_m(&cam[2]), range));
	for (int i = 0; i < st->groundLayerCount; i++) {
		u8 *layer = (u8 *)&st->groundLayers[i];
		GroundLayer *gl = (GroundLayer *)layer;
		ShapePart *part = (ShapePart *)(st->layerModel.parts + i * 0x80);
		u8 *water = st->waterModel.parts + i * 0x80;
		ShapePart *sp = (ShapePart *)water;
		const float *size = &gl->cellSize, *origin = (const float *)(layer + 4);
		int c0 = !(origin[0] >= min_x) ? ftol(fdiv_m(FSUB(min_x, origin[0]), size)) : 0;
		int r0 = !(origin[2] >= min_z) ? ftol(fdiv_m(FSUB(min_z, origin[2]), size)) : 0;
		int cols = gl->cols, rows = gl->rows;
		long double e = fadd_m(fmul_m((long double)cols, size), &origin[0]);
		int c1 = (e > max_x ? cols - ftol(fdiv_m(fsub_m(e, &max_x), size)) : cols) - 1;
		e = fadd_m(fmul_m((long double)rows, size), &origin[0]);   /* (the x origin: the original's slip) */
		int r1 = (e > max_z ? rows - ftol(fdiv_m(fsub_m(e, &max_z), size)) : rows) - 1;
		BITS(part->colours) = BITS(gl->colours);
		int w = gl->cols + 1;
		gl->indexCount = 0;
		gl->stripCount = 0;
		for (int r = r0; r <= r1; r++) {
			int open = 0, n = 0, c = c0;
			u32 *prim = NULL;
			for (; c <= c1; c++) {
				if (gl->flat[r * gl->cols + c] & 1) {
					if (!open) {
						if (gl->stripCount >= gl->stripCapacity)
							sys_fatalErrorN((char *)OBJ(g_logStage), (const char *)STR(0x4d056c, "primitiveBuffer overflow(%d/%d)-proce..."), gl->stripCount + 1, gl->stripCapacity);
						prim = (u32 *)(gl->strips + gl->stripCount * 12);
						gl->stripCount++;
						open = 1;
						n = 0;
						prim[0] = 5;
						prim[1] = 0;
						prim[2] = (u32)(((u8 *)(gl)->indices) + gl->indexCount * 4);
					}
					strip_pair(layer, (u32 *)RELOC(prim[2]), &n, r, c, w);
				} else if (open) {
					open = 0;
					strip_pair(layer, (u32 *)RELOC(prim[2]), &n, r, c, w);
					prim[1] = n;
				}
			}
			if (open) {
				strip_pair(layer, (u32 *)RELOC(prim[2]), &n, r, c, w);
				prim[1] = n;
			}
		}
		part->primCount = gl->stripCount;
		if (gl->water != 1) {
			sp->primCount = 0;
			continue;
		}
		sp->primCount = 4;
		for (int ring = 0; ring < 2; ring++)   /* (the original makes the same ring twice) */
			for (int angle = 0, at = 0, tex_at = 0; angle < 3600; angle += 900, at += 0xc, tex_at += 8) {
				float v[3];
				v[0] = f32(-fld_m(range));
				v[1] = f32(fld_m(&gl->origin[1]));
				v[2] = v[0];
				water_point(s, layer, water, at, tex_at, v, angle);
			}
		u32 out = 0;
		float r2 = f32(fmul_m(fld_m(&h), k_m1_5f));
		memcpy(&out, &r2, 4);
		for (int k = 0, angle = 0; k < 8; k++, angle += 450) {
			float v[3];
			v[1] = f32(fld_m(&gl->origin[1]));
			GAME_VAR(int, &v[0]) = 0;
			GAME_VAR(u32, &v[2]) = out;
			water_point(s, layer, water, 0x30 + k * 0xc, 0x20 + k * 8, v, angle);
		}
	}
	ViewVolume_projectObject(view, (u8 *)&st->waterModel, 0, NULL, 0, NULL, 0, -1, 0);
	ViewVolume_projectObject(view, (u8 *)&st->layerModel, 0, NULL, 0, NULL, 0, -1, 0);
}
