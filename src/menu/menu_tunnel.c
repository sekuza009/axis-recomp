/* menu_tunnel.c: the front end's 3D background: a tunnel of rings (TunnelRing, chained), each with an outer and an
   inner band of quads, six spinning flares and a spinning cage, under the menu camera. Every part walks the chain
   from its far end and draws at most the last two rings. Angles are in degrees; a spin past 360 starts again at
   -360 (sic). Floats the original only copies are passed on bit for bit (BITS). */
#include "../game.h"


static void bind(int texture)
{
	tex_bind(g_textures->banks[texture / 512], texture % 512);
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

/* a spin moved on by speed per time unit (five times faster while g_menuCameraMove is 1 or 3 when fast) */
static long double spun(float spin, float speed, int fast)
{
	long double d = (long double)g_frameTime * speed;
	if (fast && (g_menuCameraMove == 1 || g_menuCameraMove == 3))
		d = d * 5.0f;
	return d + spin;
}

/* the outer bands, in a pulsing blue-green; each turned by its spin about the tunnel's axis (upside down) */
static void outer_bands(TunnelRing *first)
{
	int n, drawn = 0;
	TunnelRing *ring = last_ring(first, &n);
	if (g_simpleMenu == 0)
		bind(g_ringBandTexture);
	for (int pass = 0; n != 0 && pass < 2; pass++, n--, drawn++) {
		gfx_setMenuCamera();
		glTranslatef_bits(0, 0, BITS(ring->depth));
		gfx_rotateXYZ(0x43340000u /* 180 */, 0, BITS(ring->spin));
		if (g_simpleMenu == 0) {
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
	/* a stray pop after two rings (sic): nothing on the menu path pushes a matrix (gfx_setMenuCamera loads the
	   identity; the original's 21 glPushMatrix calls are all in ARM CENTER panels, match drawing, particles and
	   bullets, each popped there), so this only underflows the modelview stack (GL_STACK_UNDERFLOW, no effect) */
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
		if (g_simpleMenu == 0) {
			float step = f32(5.0f / (long double)ring->cells);
			float red = (float)(1.0f - (long double)g_pulse);
			glColor4f_bits(BITS(red), BITS(g_pulse), BITS(g_pulse), 0x3f19999au /* 0.6 */);
			band_quads(ring, ring->inner, step);
		}
		if (g_menuCameraMove == 1 || g_menuCameraMove == 3)
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
			if (g_simpleMenu == 0)
				bind(g_flareTextures[-k]);
			if (k == 2)
				square(f, &g_flareSizeA);
			else if (k == 3)
				square(f, &g_flareSizeB);
			glTranslatef_stored(f->pos);
			gfx_rotateXYZ(0, 0, BITS(f->spin));
			if (g_simpleMenu == 0) {
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
		if (g_simpleMenu == 0) {
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

/* 0x429d70: the background, drawn from the tunnel's first ring; g_simpleMenu leaves out everything textured but
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
	tunnel_appendRing(&g_menuTunnel);
	TunnelRing *ring = g_menuTunnel;
	for (; ring->next != NULL; ring = ring->next)
		ring->alpha = 1.0f;
	return ring;
}

/* ---- tunnelRing_build: the background tunnel's ring number index (its depth -1100 x index): two circles of 101 points (each
   stored twice, at heights +500 and -500), the spins (taken from the ring before, when there is one), the cage's
   corners (+-50, +-50, +-49), and six flares whose heights step down, with their speeds ---- */

void (tunnelRing_build)(u8 *o, int index)
{
	TunnelRing *tr = (TunnelRing *)o;
	typedef long double X;
	X H = index;
	tr->cleared0 = 0;
	tr->cleared4 = 0;
	tr->depth = (float)(H * k_m1000f + H * k_m100f);
	tr->cells = 100;
	for (int pass = 0; pass < 2; pass++) {
		float (*band)[201][4] = tr->outer;
		X radius = pass ? k_23 : k_25;
		if (pass) {   /* the second circle after the path's four fields */
			(*(int *)&tr->spin) = 0;
			if (tr->back)
				BITS(tr->spin) = BITS(tr->back->spin);
			tr->spinSpeed = 0.2f;
			tr->cleared1938 = 0;
			(*(int *)&tr->depthShift) = 0;
			tr->moveSteps = 0;
			band = tr->inner;
			if (tr->cells < 0)
				break;
		}
		for (int i = 0; ; ) {
			X a = (X)i * k_3_6f * k_pi * k_oneOver180;
			float s = f32(x87_fsin(a) * radius), c = f32(x87_fcos(a) * radius);
			band[1][i][0] = s;
			band[0][i][0] = s;
			band[1][i][1] = c;
			band[0][i][1] = c;
			BITS(band[0][i][2]) = 0x43fa0000;   /* 500: the near circle */
			BITS(band[1][i][2]) = 0xc3fa0000;   /* -500: the far one */
			if (!(++i <= tr->cells))
				break;
		}
	}
	BITS(tr->innerSpin) = 0x43b40000;   /* 360 */
	if (tr->back)
		BITS(tr->innerSpin) = BITS(tr->back->innerSpin);
	tr->innerSpeed = -0.5f;
	BITS(tr->cleared326c[0]) = BITS(tr->cleared326c[1]) = BITS(tr->cleared326c[2]) = 0;
	X y = H * k_m1100f - k_550f;
	tr->cagePos[2] = (float)y;
	y -= k_49f;
	static const signed char cx[8] = { -1, 1, 1, -1, -1, 1, 1, -1 }, cy[8] = { 1, 1, -1, -1, 1, 1, -1, -1 };
	for (int k = 0; k < 8; k++) {   /* (their pads kept) */
		BITS(tr->cage[k][0]) = cx[k] > 0 ? 0x42480000 : 0xc2480000;   /* +-50 */
		BITS(tr->cage[k][1]) = cy[k] > 0 ? 0x42480000 : 0xc2480000;
		BITS(tr->cage[k][2]) = k < 4 ? 0x42440000 : 0xc2440000;        /* +-49 */
	}
	BITS(tr->cagePos[0]) = BITS(tr->cagePos[1]) = 0;
	BITS(tr->cageSpin) = 0;
	tr->cageSpeed = -0.1f;
	static const signed char corner[12] = { -1, 1, 0, 1, 1, 0, 1, -1, 0, -1, -1, 0 };   /* a flare's four corners' x, y, z: +-50 (pads kept) */
	static const u32 speed[6] = { 0x3e19999a, 0xbeb33333, 0xbfc00000, 0x3fc00000, 0xbe3851ec, 0x3e3851ec };   /* 0.15, -0.35, -1.5, 1.5, -0.18, 0.18 */
	for (int j = 0; j < 6; j++) {
		Flare *f = &tr->flares[j];
		for (int i = 0; i < 12; i++)
			BITS(f->corners[i / 3][i % 3]) = corner[i] > 0 ? 0x42480000 : corner[i] < 0 ? 0xc2480000 : 0;
		BITS(f->pos[0]) = BITS(f->pos[1]) = 0;
		BITS(f->spin) = 0;
		f->pos[2] = (float)(y - ((X)k_1f - (X)j * k_tenthsToDegrees));
		BITS(f->spinSpeed) = speed[j];
	}
	tr->alpha = 1.0f;
	tr->ringIndex = index;
}

/* ---- the menu camera's move along the tunnel: its eye (g_menuEyeX, three floats) and the point it looks at
   (g_menuCameraLook), kept at g_menuEyeKeptX / g_menuLookKeptX; the move's state in g_menuCameraMove (0 still, 1 / 3 moving in / out a ring,
   2 / 4 the view swinging up before them) ---- */
#define EYE ((float *)ADDR(g_menuEyeX))
#define LOOK ((float *)ADDR(g_menuCameraLook))
#define EYE_KEPT ((float *)ADDR(g_menuEyeKeptX))
#define LOOK_KEPT ((float *)ADDR(g_menuLookKeptX))

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
	if (angle < k_90f || __builtin_isnan(angle))
		return;
	BITS(g_viewAngle) = 0x42b40000;   /* 90 */
	g_menuCameraMove = next;
	sound_playMenu(4);
}

/* the view lowered toward 45 (k_45f) */
static void lower_view(const float *rate)
{
	if (g_viewAngle > k_45f)
		g_viewAngle = rate ? f32(fsubr_m(fmul_m(fld_m(&g_frameTime), rate), &g_viewAngle))
		                   : f32(FSUB(g_viewAngle, g_frameTime));
}

/* 0x441260: one frame of the tunnel camera's move, worked on the ring before the last of the chain at ring. The
   frame time is held at 2 at most; a step is 30 frame times (g_tunnelStep, and as a float g_tunnelStepF); a ring is 1100
   steps (950 when entering the menus, g_enteringMenus, which starts the eye and look point at 0; 2200 in the ARM CENTER,
   g_leavingForMatch). Still (0): the flares at full alpha, the view lowered, the camera kept once asked (g_keepCameraAsked), and the
   menus entered when the network is ready (g_launchedForNetGame, g_launchStartStep 0x65). Moving in (1) / out (3): eye and look point a
   step down / up the tunnel; once a ring's worth is done, the camera back at the kept place a ring further, the
   ring turned (by -1100, -2200 in the ARM CENTER, or +1100), a ring added (in) or the last one taken off (out),
   the screen's state g_nextScreen into g_screen and the camera kept; moving out also lowers the view. 2 / 4 swing the
   view up and start 1 / 3. The caller ignores the eax it leaves */
void (menuTunnel_advance)(TunnelRing *ring)
{
	if (g_frameTime > k_10f)
		g_frameTime = 2.0f;
	int step = ftol(fmul_m(fld_m(&g_frameTime), k_30f));
	int ringLength = 0x44c;
	g_tunnelStep = step;
	g_tunnelStepF = (float)step;
	if (g_enteringMenus) {
		ringLength = 0x3b6;
		EYE[0] = EYE[1] = LOOK[0] = LOOK[1] = 0.0f;
	}
	if (g_leavingForMatch)
		ringLength = 0x898;
	TunnelRing *r = ring;
	for (TunnelRing *last = ring; last->next != NULL; last = last->next)
		r = last;
	const float *stepF = (const float *)ADDR(g_tunnelStepF);
	int state = g_menuCameraMove;
	switch (state) {
	case 0:
		r->alpha = 1.0f;
		lower_view(NULL);
		if (g_keepCameraAsked) {
			camera_keep();
			g_keepCameraAsked = 0;
		}
		if (g_launchedForNetGame == 1 && g_launchStartStep == 0x65) {
			g_armcFrom = 1;
			armc_open();
			g_enteringMenus = 0;
			g_launchStartStep = 0x66;
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
				r->depthShift = f32(fsub_m(fld_m(&r->depthShift), (const float *)(g_leavingForMatch ? ADDR(k_2200f) : OBJ(k_1100f))));
			else
				r->depthShift = f32(fadd_m(fld_m(&r->depthShift), k_1100f));
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
			g_menuCameraMove = 0;
			r->alpha = 1.0f;
			if (state == 1)
				tunnel_addRing();
			else {
				g_tunnelRings--;
				tunnel_removeLastRing(&g_menuTunnel);
			}
			g_menuState = g_nextScreen;
			g_tunnelFlyingIn = 1;
			g_keepCameraAsked = 1;
			camera_keep();
			if (state == 1) {
				g_enteringMenus = 0;
				return;
			}
		} else if (state == 1)
			return;
		lower_view((const float *)ADDR(k_0_5f));
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
