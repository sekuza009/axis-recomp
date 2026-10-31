/* menu_tunnel.c: the front end's 3D background: a tunnel of rings (TunnelRing, chained), each with an outer and an
   inner band of quads, six spinning flares and a spinning cage, under the menu camera. Every part walks the chain
   from its far end and draws at most the last two rings. Angles are in degrees; a spin past 360 starts again at
   -360 (sic). Floats the original only copies are passed on bit for bit (BITS). */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

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

/* 0x441190: the last ring of the chain at *head taken off and freed (free's result) */
u32 (tunnel_removeLastRing)(TunnelRing **head)
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
TunnelRing *(tunnel_addRing)(void)
{
	g_tunnelRings += 1;
	tunnel_appendRing(&g_tunnel);
	TunnelRing *ring = g_tunnel;
	for (; ring->next != NULL; ring = ring->next)
		BITS(ring->alpha) = 0x3f800000;
	return ring;
}

/* ---- 0x440e20: an intro camera path node for screen height h: two circles of 101 points (each stored twice, at
   heights +500 and -500), the path settings (taken from the linked node, +0x3530, when there is one), the box's
   corners, and six records whose heights step down ---- */
static long double fsin_(long double x) { __asm__("fsin" : "+t"(x)); return x; }
static long double fcos_(long double x) { __asm__("fcos" : "+t"(x)); return x; }

void (intro_cameraPath)(u8 *o, int h)
{
	typedef long double X;
	X H = h;
	FIELD(int, o, 0) = 0;
	FIELD(int, o, 4) = 0;
	FIELD(float, o, 8) = (float)(H * GAME_VAR(float, 0x4a95c0) + H * GAME_VAR(float, 0x4a95bc));
	FIELD(int, o, 0x3528) = 100;
	for (int pass = 0; pass < 2; pass++) {
		u32 base = 0x10;
		X radius = pass ? GAME_VAR(double, 0x4a95a8) : GAME_VAR(double, 0x4a95b0);
		if (pass) {   /* the second circle after the path's four fields */
			FIELD(int, o, 0x1930) = 0;
			if (FIELD(int, o, 0x3530))
				FIELD(int, o, 0x1930) = FIELD(int, FIELD(u8 *, o, 0x3530), 0x1930);
			FIELD(u32, o, 0x1934) = 0x3e4ccccd;   /* 0.2 */
			FIELD(int, o, 0x1938) = 0;
			FIELD(int, o, 0x1940) = 0;
			FIELD(int, o, 0x193c) = 0;
			base = 0x1944;
			if (FIELD(int, o, 0x3528) < 0)
				break;
		}
		for (int i = 0; ; ) {
			X a = (X)i * GAME_VAR(float, 0x4a95b8) * GAME_VAR(double, 0x4a9548) * GAME_VAR(double, 0x4a9540);
			u8 *r = o + base + i * 16;
			float s = f32(fsin_(a) * radius), c = f32(fcos_(a) * radius);
			FIELD(float, r, 0xc90) = s;
			FIELD(float, r, 0) = s;
			FIELD(float, r, 0xc94) = c;
			FIELD(float, r, 4) = c;
			FIELD(u32, r, 8) = 0x43fa0000;       /* 500 */
			FIELD(u32, r, 0xc98) = 0xc3fa0000;   /* -500 */
			if (!(++i <= FIELD(int, o, 0x3528)))
				break;
		}
	}
	FIELD(u32, o, 0x3264) = 0x43b40000;   /* 360 */
	if (FIELD(int, o, 0x3530))
		FIELD(int, o, 0x3264) = FIELD(int, FIELD(u8 *, o, 0x3530), 0x3264);
	static const struct { short offset; u32 value; } box[] = {
		{ 0x3268, 0xbf000000 }, { 0x326c, 0 }, { 0x3274, 0 }, { 0x3270, 0 }, { 0x3278, 0xc2480000 }, { 0x327c, 0x42480000 },
		{ 0x3280, 0x42440000 }, { 0x3288, 0x42480000 }, { 0x328c, 0x42480000 }, { 0x3290, 0x42440000 },
		{ 0x32a0, 0x42440000 }, { 0x32b0, 0x42440000 }, { 0x32c0, 0xc2440000 }, { 0x32d0, 0xc2440000 },
		{ 0x32e0, 0xc2440000 }, { 0x32f0, 0xc2440000 }, { 0x3298, 0x42480000 }, { 0x329c, 0xc2480000 },
		{ 0x32a8, 0xc2480000 }, { 0x32ac, 0xc2480000 }, { 0x32b8, 0xc2480000 }, { 0x32bc, 0x42480000 },
		{ 0x32c8, 0x42480000 }, { 0x32cc, 0x42480000 }, { 0x32d8, 0x42480000 }, { 0x32dc, 0xc2480000 },
		{ 0x32e8, 0xc2480000 }, { 0x32ec, 0xc2480000 }, { 0x32f8, 0 }, { 0x32fc, 0 }, { 0x3308, 0 },
		{ 0x330c, 0xbdcccccd } };   /* (+-50, +-49 ...) */
	X y = H * GAME_VAR(float, 0x4a95a4) - GAME_VAR(float, 0x4a9498);
	FIELD(float, o, 0x3300) = (float)y;
	y -= GAME_VAR(float, 0x4a95a0);
	for (unsigned i = 0; i < sizeof box / sizeof box[0]; i++)
		FIELD(u32, o, box[i].offset) = box[i].value;
	static const struct { signed char offset; u8 kind; } corner[] = {   /* 0: 0.0, 1: +50, 2: -50 */
		{ -4, 2 }, { 0, 1 }, { 4, 0 }, { 0xc, 1 }, { 0x10, 1 }, { 0x14, 0 }, { 0x1c, 1 }, { 0x20, 2 }, { 0x24, 0 },
		{ 0x2c, 2 }, { 0x30, 2 }, { 0x34, 0 }, { 0x3c, 0 }, { 0x40, 0 }, { 0x4c, 0 } };
	for (int j = 0; j < 6; j++) {
		u8 *r = o + 0x3314 + j * 0x58;
		for (unsigned i = 0; i < sizeof corner / sizeof corner[0]; i++)
			FIELD(u32, r, corner[i].offset) = corner[i].kind == 1 ? 0x42480000 : corner[i].kind == 2 ? 0xc2480000 : 0;
		FIELD(float, r, 0x44) = (float)(y - ((X)GAME_VAR(float, 0x4a9424) - (X)j * GAME_VAR(float, 0x4a93ec)));
	}
	static const struct { short offset; u32 value; } rest[] = {
		{ 0x3364, 0x3e19999a }, { 0x33bc, 0xbeb33333 }, { 0x3414, 0xbfc00000 }, { 0x346c, 0x3fc00000 },
		{ 0x34c4, 0xbe3851ec }, { 0x351c, 0x3e3851ec }, { 0x3520, 0x3f800000 } };
	for (unsigned i = 0; i < sizeof rest / sizeof rest[0]; i++)
		FIELD(u32, o, rest[i].offset) = rest[i].value;
	FIELD(int, o, 0x3524) = h;
}

/* ---- the menu camera's move along the tunnel: its eye (0x4df024, three floats) and the point it looks at
   (0x680378), kept at 0x9dd930 / 0x9dd918; the move's state in g_keysBlocked (0 still, 1 / 3 moving in / out a ring,
   2 / 4 the view swinging up before them) ---- */
#define EYE ((float *)0x4df024)
#define LOOK ((float *)0x680378)
#define EYE_KEPT ((float *)0x9dd930)
#define LOOK_KEPT ((float *)0x9dd918)

static void camera_keep(void)
{
	for (int k = 0; k < 3; k++) {   /* (bit copies) */
		((u32 *)EYE_KEPT)[k] = ((const u32 *)EYE)[k];
		((u32 *)LOOK_KEPT)[k] = ((const u32 *)LOOK)[k];
	}
}

/* the view tipped up a ring's worth (2 frame times a frame) until it passes 90; then the move starts (next) */
static void swing(int next)
{
	long double angle = fadd_m(fld_m(&g_frameTime) + fld_m(&g_frameTime), &g_viewAngle);
	g_viewAngle = f32(angle);
	if (angle < *(const float *)0x4a9550 || __builtin_isnan(angle))
		return;
	BITS(g_viewAngle) = 0x42b40000;   /* 90 */
	g_keysBlocked = next;
	sound_playMenu(4);
}

/* the view lowered toward 45 (0x4a94e8) */
static void lower_view(const float *rate)
{
	if (g_viewAngle > *(const float *)0x4a94e8)
		g_viewAngle = rate ? f32(fsubr_m(fmul_m(fld_m(&g_frameTime), rate), &g_viewAngle))
		                   : f32(fsub_m(fld_m(&g_viewAngle), &g_frameTime));
}

/* 0x441260: one frame of the tunnel camera's move, worked on the ring before the last of the chain at ring. The
   frame time is held at 2 at most; a step is 30 frame times (0x4b2a74, and as a float 0x4b2a78); a ring is 1100
   steps (950 when entering the menus, 0x4deb48, which starts the eye and look point at 0; 2200 in the ARM CENTER,
   0x67ef14). Still (0): the flares at full alpha, the view lowered, the camera kept once asked (0x4b2a70), and the
   menus entered when the network is ready (0x76d410, 0x9da49c 0x65). Moving in (1) / out (3): eye and look point a
   step down / up the tunnel; once a ring's worth is done, the camera back at the kept place a ring further, the
   ring turned (by -1100, -2200 in the ARM CENTER, or +1100), a ring added (in) or the last one taken off (out),
   the screen's state 0x67ef20 into 0x76d3e8 and the camera kept; moving out also lowers the view. 2 / 4 swing the
   view up and start 1 / 3. The caller ignores the eax it leaves */
void (armc_enter)(TunnelRing *ring)
{
	if (g_frameTime > *(const float *)0x4a9418)
		BITS(g_frameTime) = 0x40000000;   /* 2 */
	int step = ftol(fmul_m(fld_m(&g_frameTime), (const float *)0x4a940c));
	int ringLength = 0x44c;
	GAME_VAR(int, 0x4b2a74) = step;
	GAME_VAR(float, 0x4b2a78) = (float)step;
	if (g_enteringMenus) {
		ringLength = 0x3b6;
		EYE[0] = EYE[1] = LOOK[0] = LOOK[1] = 0.0f;
	}
	if (g_quitAsked)
		ringLength = 0x898;
	TunnelRing *r = ring;
	for (TunnelRing *last = ring; last->next != NULL; last = last->next)
		r = last;
	const float *stepF = (const float *)0x4b2a78;
	int state = g_keysBlocked;
	switch (state) {
	case 0:
		BITS(r->alpha) = 0x3f800000;
		lower_view(NULL);
		if (g_keepCameraAsked) {
			camera_keep();
			g_keepCameraAsked = 0;
		}
		if (g_startedFromLobby == 1 && g_lobbyReply == 0x65) {
			GAME_VAR(int, 0x4dc24c) = 1;
			menu_enterMenus();
			g_enteringMenus = 0;
			g_lobbyReply = 0x66;
		}
		return;
	case 1:
	case 3:
		if (state == 1) {
			EYE[2] = f32(fsub_m(fld_m(&EYE[2]), stepF));
			LOOK[2] = f32(fsub_m(fld_m(&LOOK[2]), stepF));
		} else {
			EYE[2] = f32(fadd_m(fld_m(&EYE[2]), stepF));
			LOOK[2] = f32(fadd_m(fld_m(&LOOK[2]), stepF));
		}
		r->moveSteps += step;
		if (r->moveSteps >= ringLength) {
			if (state == 1)
				r->turn = f32(fsub_m(fld_m(&r->turn), (const float *)(g_quitAsked ? 0x4a95c8 : 0x4a95c4)));
			else
				r->turn = f32(fadd_m(fld_m(&r->turn), (const float *)0x4a95c4));
			r->moveSteps = 0;
			for (int k = 0; k < 2; k++) {
				((u32 *)EYE)[k] = ((const u32 *)EYE_KEPT)[k];
				((u32 *)LOOK)[k] = ((const u32 *)LOOK_KEPT)[k];
			}
			if (state == 1) {
				EYE[2] = f32(fld_m(&EYE_KEPT[2]) - (long double)ringLength);
				LOOK[2] = f32(fld_m(&LOOK_KEPT[2]) - (long double)ringLength);
			} else {
				EYE[2] = f32(fadd_m((long double)ringLength, &EYE_KEPT[2]));
				LOOK[2] = f32(fadd_m((long double)ringLength, &LOOK_KEPT[2]));
			}
			g_keysBlocked = 0;
			BITS(r->alpha) = 0x3f800000;
			if (state == 1)
				tunnel_addRing();
			else {
				g_tunnelRings--;
				tunnel_removeLastRing(&g_tunnel);
			}
			GAME_VAR(int, 0x76d3e8) = GAME_VAR(int, 0x67ef20);
			g_tunnelFlyingIn = 1;
			g_keepCameraAsked = 1;
			camera_keep();
			if (state == 1) {
				g_enteringMenus = 0;
				return;
			}
		} else if (state == 1)
			return;
		lower_view((const float *)0x4a942c);
		return;
	case 2:
	case 4:
		swing(state - 1);
		return;
	}
}
#undef EYE
#undef LOOK
#undef EYE_KEPT
#undef LOOK_KEPT
