/* menu_tunnel.c: the front end's 3D background: a tunnel of rings (TunnelRing, chained), each with an outer and an
   inner band of quads, six spinning flares and a spinning cage, under the menu camera. Every part walks the chain
   from its far end and draws at most the last two rings. Angles are in degrees; a spin past 360 starts again at
   -360 (sic). Floats the original only copies are passed on bit for bit (BITS). */
#include "../game.h"

static void bind(int texture)
{
	tex_bind(g_textures->managers[texture / 512], texture % 512);
}

/* the last ring of the chain and the number of rings */
static TunnelRing *last_ring(TunnelRing *ring, int *count)
{
	int n = 1;
	while (ring->next != NULL) {
		ring = ring->next;
		n++;
	}
	*count = n;
	return ring;
}

/* a band of the tunnel: ring->cells quads between its two circles of points (circle[0] near, circle[1] far), the
   texture repeating five times around (the cells counted again in each fifth; step = 5 / cells) and 20 times
   along. The first coordinate comes from the cell number itself, the second from it rounded to a float */
static void band_quads(const TunnelRing *ring, const float (*circle)[201][4], float step)
{
	glBegin(GL_QUADS);
	int fifth = ring->cells / 5;
	for (int i = 0; i < ring->cells; i++) {
		int cell = i < fifth ? i : i < fifth * 2 ? i - fifth : i < fifth * 3 ? i - fifth * 2
		           : i < fifth * 4 ? i - fifth * 3 : i - fifth * 4;
		float s0 = f32((long double)cell * step), s1 = f32(((long double)f32(cell) + 1.0f) * step);
		glTexCoord2f(s0, 0.0f);
		glVertex3f_stored(circle[0][i]);
		glTexCoord2f(s1, 0.0f);
		glVertex3f_stored(circle[0][i + 1]);
		glTexCoord2f(s1, 20.0f);
		glVertex3f_stored(circle[1][i + 1]);
		glTexCoord2f(s0, 20.0f);
		glVertex3f_stored(circle[1][i]);
	}
	glEnd();
}

/* a spin moved on by speed per time unit (five times faster while g_keysBlocked is 1 or 3 when fast) */
static long double spun(float spin, float speed, int fast)
{
	long double d = (long double)g_frameTime * speed;
	if (fast && (g_keysBlocked == 1 || g_keysBlocked == 3))
		d = d * 5.0f;
	return d + spin;
}

/* the outer bands, in a pulsing blue-green; each turned by its spin about the tunnel's axis (upside down) */
static void outer_bands(TunnelRing *first)
{
	int n, drawn = 0;
	TunnelRing *ring = last_ring(first, &n);
	if (g_texturesOff == 0)
		bind(g_tunnelTexture);
	for (int pass = 0; n != 0 && pass < 2; pass++, n--, drawn++) {
		gfx_setMenuCamera();
		glTranslatef_bits(0, 0, BITS(ring->depth));
		gfx_rotateXYZ(0x43340000u /* 180 */, 0, BITS(ring->spin));
		if (g_texturesOff == 0) {
			float step = f32(5.0f / (long double)ring->cells);
			float blue = (float)(1.0f - (long double)g_pulse);
			glColor4f_bits(0, BITS(g_pulse), BITS(blue), 0x3f4ccccdu /* 0.8 */);
			band_quads(ring, ring->outer, step);
		}
		ring->spin = f32(spun(ring->spin, ring->spinSpeed, 1));
		if (ring->spin >= 360.0f)
			ring->spin = -360.0f;
		ring = ring->back;
	}
	/* (unclear) the camera matrix pushed for the first ring is let go after the second */
	if (drawn == 2)
		glPopMatrix();
}

/* the inner bands, in the opposite pulse (red); in the fast modes the outer spin moves on instead (sic) */
static void inner_bands(TunnelRing *first)
{
	int n;
	TunnelRing *ring = last_ring(first, &n);
	for (int pass = 0; n != 0 && pass < 2; pass++, n--) {
		gfx_setMenuCamera();
		glTranslatef_bits(0, 0, BITS(ring->depth));
		gfx_rotateXYZ(0x43340000u /* 180 */, 0, BITS(ring->innerSpin));
		if (g_texturesOff == 0) {
			float step = f32(5.0f / (long double)ring->cells);
			float red = (float)(1.0f - (long double)g_pulse);
			glColor4f_bits(BITS(red), BITS(g_pulse), BITS(g_pulse), 0x3f19999au /* 0.6 */);
			band_quads(ring, ring->inner, step);
		}
		if (g_keysBlocked == 1 || g_keysBlocked == 3)
			ring->spin = f32(spun(ring->spin, ring->spinSpeed, 1));
		else
			ring->innerSpin = f32(spun(ring->innerSpin, ring->innerSpeed, 0));
		if (ring->innerSpin >= 360.0f)
			ring->innerSpin = -360.0f;
		ring = ring->back;
	}
}

/* the pulse goes back and forth between 0.05 and 0.95 (tested before rounding at the top) */
static void pulse(void)
{
	long double p = (long double)g_pulseStep * g_frameTime + g_pulse;
	g_pulse = f32(p);
	if (p >= 0.95f) {
		g_pulse = 0.95f;
		g_pulseStep = -0.01f;
	} else if (!(g_pulse > 0.05f)) {
		g_pulse = 0.05f;
		g_pulseStep = 0.01f;
	}
}

/* a flare's corners as a square of half-size size (x, y; the negated ones go through the FPU, the others are
   copied) */
static void square(Flare *f, float *size)
{
	float neg = f32(-(long double)*size);
	f->corners[0][0] = neg;
	BITS(f->corners[0][1]) = BITS(*size);
	BITS(f->corners[1][0]) = BITS(*size);
	BITS(f->corners[1][1]) = BITS(*size);
	BITS(f->corners[2][0]) = BITS(*size);
	f->corners[2][1] = f32(-(long double)*size);
	f->corners[3][0] = f32(-(long double)*size);
	f->corners[3][1] = f32(-(long double)*size);
}

/* six flares per ring (texture k counted down from g_flareTextures), faded by the ring's alpha, each at its place
   and spin; flares 2 and 3 are squares of the breathing sizes g_flareSizeA / g_flareSizeB */
static void flares(TunnelRing *first)
{
	int n;
	TunnelRing *ring = last_ring(first, &n);
	for (int pass = 0; n != 0 && pass < 2; pass++, n--) {
		for (int k = 0; k < 6; k++) {
			Flare *f = &ring->flares[k];
			glColor4f_bits(0x3f800000u, 0x3f800000u, 0x3f800000u, BITS(ring->alpha));
			gfx_setMenuCamera();
			if (g_texturesOff == 0)
				bind(g_flareTextures[-k]);
			if (k == 2)
				square(f, &g_flareSizeA);
			else if (k == 3)
				square(f, &g_flareSizeB);
			glTranslatef_stored(f->pos);
			gfx_rotateXYZ(0, 0, BITS(f->spin));
			if (g_texturesOff == 0) {
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f_stored(f->corners[0]);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f_stored(f->corners[1]);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f_stored(f->corners[2]);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f_stored(f->corners[3]);
				glEnd();
			}
			long double s = spun(f->spin, f->spinSpeed, 0);
			f->spin = f32(s);
			if (s > 360.0f)
				f->spin = -360.0f;
			if (!(f->spin >= -360.0f))
				f->spin = 360.0f;
		}
		ring = ring->back;
	}
}

/* the breathing sizes of flares 2 and 3: they grow and shrink between 10 and 48 at 0.2 per time unit. B is tested
   for the lower limit after rounding, A before (as the original keeps it on the FPU) */
static void breathe(void)
{
	long double b = (long double)g_flareStepB + g_flareSizeB;
	g_flareSizeB = f32(b);
	if (b >= 48.0f)
		g_flareStepB = (float)((long double)g_frameTime * -0.2f);
	if (!(g_flareSizeB > 10.0f))
		g_flareStepB = (float)((long double)g_frameTime * 0.2f);
	long double a = (long double)g_flareStepA + g_flareSizeA;
	g_flareSizeA = f32(a);
	if (a >= 48.0f)
		g_flareStepA = (float)((long double)g_frameTime * -0.2f);
	if (!(a > 10.0f))
		g_flareStepA = (float)((long double)g_frameTime * 0.2f);
}

/* a cage per ring: the four sides of a box between its eight corners (0..3 one end, 4..7 the other), grey */
static void cages(TunnelRing *first)
{
	int n;
	TunnelRing *ring = last_ring(first, &n);
	for (int pass = 0; n != 0 && pass < 2; pass++, n--) {
		gfx_setMenuCamera();
		glTranslatef_stored(ring->cagePos);
		gfx_rotateXYZ(0, 0, BITS(ring->cageSpin));
		if (g_texturesOff == 0) {
			bind(g_cageTexture);
			glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
			for (int side = 0; side < 4; side++) {
				int a = side, b = (side + 1) % 4;
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f_stored(ring->cage[a]);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f_stored(ring->cage[b]);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f_stored(ring->cage[b + 4]);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f_stored(ring->cage[a + 4]);
				glEnd();
			}
		}
		long double s = spun(ring->cageSpin, ring->cageSpeed, 0);
		ring->cageSpin = f32(s);
		if (s >= 360.0f)
			ring->cageSpin = -360.0f;
		ring = ring->back;
	}
}

/* 0x429d70: the background, drawn from the tunnel's first ring; g_texturesOff leaves out everything textured but
   still moves it all on */
void (menu_drawBackground3D)(TunnelRing *first)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	outer_bands(first);
	inner_bands(first);
	pulse();
	flares(first);
	breathe();
	cages(first);
	glDisable(GL_TEXTURE_2D);
}

#define g_tunnel GAME_VAR(TunnelRing *, 0x67fb3c)   /* the first ring */
#define g_tunnelRings GAME_VAR(int, 0x9dae10)

/* 0x441190: the last ring of the chain at *head taken off and freed (free's result) */
u32 (FUN_00441190)(TunnelRing **head)
{
	TunnelRing *first = *head, *last = first, *prev = first;
	while (last->next != NULL) {
		prev = last;
		last = last->next;
	}
	if (first == last)
		*head = last->next;
	else
		prev->next = last->next;
	return crt_free(last);
}

/* 0x441200: one more ring added; every ring but the new last one at full alpha; the last ring */
TunnelRing *(FUN_00441200)(void)
{
	g_tunnelRings += 1;
	FUN_00441120(&g_tunnel);
	TunnelRing *ring = g_tunnel;
	for (; ring->next != NULL; ring = ring->next)
		BITS(ring->alpha) = 0x3f800000;
	return ring;
}
