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

/* a light factor (0x2c bytes): kind 0 ambient, 1 directional, 2 a point light fading over its radius, 3 a point
   light falling off with the square of the distance */
typedef struct {
	u32 _00, _04;
	int type;
	u8 colour[4];   /* +0xc */
	float pos[3];   /* +0x10 */
	float dir[3];   /* +0x1c */
	float radius;   /* +0x28 */
} Light;

#define K(addr) ((const float *)(addr))
#define MUL(a, b) fmul_m(fld_m(a), b)
#define LIGHT_COUNT(factors) (*(const int *)((factors) + 0xb004))
#define g_unlit GAME_VAR(u32, 0xa1f278)   /* the colour of a vertex out of a light's reach */

static int clamp255(int v) { return v < 0xff ? v : 0xff; }

/* the original's imul: products wrap */
static int mul(int a, int b) { return (int)((u32)a * (u32)b); }

/* the factor 1 - dot scaled to 0 .. 256 (none below 0) */
static int facing(long double dot)
{
	int k = ftol(fmul_m(fsubr_m(dot, K(0x4a9424)), K(0x4aa264)));
	return k < 0 ? 0 : k;
}

/* a vertex's offset from a light at p: the vector into d, its squared length returned unrounded */
static long double offset(const float *v, const float *p, float *d)
{
	d[0] = f32(fsub_m(fld_m(&v[0]), &p[0]));
	d[1] = f32(fsub_m(fld_m(&v[1]), &p[1]));
	d[2] = f32(fsub_m(fld_m(&v[2]), &p[2]));
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

/* 0x463b80: the part's vertex colours (out, 4 bytes each) under the factors (count +0xb004, records from +4), the
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
				if (!(fadd_m(fld_m(&p[a]), &r) > part->min[a]) || fsub_m(fld_m(&p[a]), &r) >= part->max[a])
					reaches = 0;
			if (!reaches) {
				if (first == 1)
					memset(out, 0, part->count * 4);
				break;
			}
			long double rr = MUL(&r, &r);
			float r2 = f32(rr), inner = f32(fmul_m(rr, K(0x4a94f8)));
			float range = f32(fsub_m(fld_m(&r2), &inner));
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
					int k = ftol(fmul_m(fsubr_m(fdiv_m(fsub_m(fld_m(&d2), &inner), &range), K(0x4a9424)), K(0x4aa260)));
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
		case 3: {   /* a point light falling off with the squared distance beyond a fifth (0x4aa25c) of the squared
		               radius, its colour by how the normals face it */
			if (m) {
				p[0] = f32(((MUL(&m[8], &l->pos[2]) + MUL(&m[4], &l->pos[1])) + MUL(&l->pos[0], &m[0])) + m[12]);
				p[1] = f32(((MUL(&m[9], &l->pos[2]) + MUL(&m[5], &l->pos[1])) + MUL(&m[1], &l->pos[0])) + m[13]);
				p[2] = f32(((MUL(&m[10], &l->pos[2]) + MUL(&m[6], &l->pos[1])) + MUL(&m[2], &l->pos[0])) + m[14]);
			} else
				memcpy(p, l->pos, sizeof p);
			const float r = l->radius;
			long double rr = MUL(&r, &r);
			float r2 = f32(rr), inner = f32(fmul_m(rr, K(0x4aa25c)));
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
					int k = ftol(fdiv_m(fmul_m(fld_m(&inner), K(0x4aa260)), &d2));
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
			sys_errorTerminate((const char *)0x4c4a4c, l->type);
		}
	}
}
