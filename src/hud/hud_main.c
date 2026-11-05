/* hud_main.c: the main HUD of the player the view follows (hud_drawMain): screen flashes, the alert ring, the
   counters and weapon slots, the gauge, the four timers, the actor's snapshot panel, the energy bar, the
   crosshair, and the mark or rank at the top right.

   Positions are worked out as the original does, each time from the screen size: a length of k HUD units is
   width * (1/640) * k or height * (1/480) * k, kept in extended precision, and some partial sums are rounded to
   floats on the way (stored); each such step is one statement here so the screen size is asked for in the same
   order. The patch DLL changes the energy bar's two lengths in memory at start-up (the operands at 0x493db8 ..
   0x494400 point to its own values), and the timers' text goes through the call at 0x49395f, which it retargets.

   On a screen wider than 4:3 the patch DLL moves each part of this HUD to the edge it belongs to (its glVertex2i
   hook), keeping 4:3 proportions. It used to recognise the parts by the return addresses of the original's calls;
   this rebuild names each part as it draws it instead (part(), wide.h). */
#include "../game.h"
#include <string.h>
#include "hud.h"
#include "../wide.h"

#define SX (1.0f / 640)          /* 0x4a9578 */
#define SY (1.0f / 480)          /* 0x4a9574 */

/* k HUD units across / down, in pixels, unrounded */
static long double wx(float k) { return (long double)gfx_getWidth() * SX * k; }
static long double hy(float k) { return (long double)gfx_getHeight() * SY * k; }
/* the screen size as a float */
static float wf(void) { return (float)gfx_getWidth(); }
static float hf(void) { return (float)gfx_getHeight(); }
/* a texel count to a texture coordinate (texture 256 or 255 texels across), rounded to a float */
static float tex256(int n) { return f32((long double)n * (1.0f / 256)); }
static float tex255(int n) { return f32((long double)n * (1.0f / 255)); }

/* the energy bar's length and left edge in HUD units: floats the patch DLL may move (it rewrites every operand that
   reads them, all to the same new address); read through the first of those operands */
#ifdef AXIS_DIRECT
/* (AxisRC.exe: where the installed exe's patch put them, its section .axnet: no patch DLL moves them now) */
#define ENERGY_HEIGHT GAME_VAR(float, 0xb68ce4)   /* 160 on disk */
#define ENERGY_WIDTH  GAME_VAR(float, 0xb68ce0)   /* 8 on disk */
#else
#define ENERGY_HEIGHT (*(const float *)RELOC(*(const u32 *)IMG(0x493db8)))   /* 160 on disk */
#define ENERGY_WIDTH  (*(const float *)RELOC(*(const u32 *)IMG(0x493f29)))   /* 8 on disk */
#endif

/* the alert ring: a quad strip around the screen centre, opaque at its inner edge and fading out 1.2 times further
   out, turning with the player's heading */
static void main_ring(Scene *scene, Player *player)
{
	int t = ftol((long double)game_clock() * 5.0f);
	float trig = g_trig[(t % 3600 + 3600) % 3600];
	int half = gfx_getHeight() / 2;
	float radius = f32(half / (long double)trig);
	glBegin(GL_QUAD_STRIP);
	for (int angle = 0; angle <= 3600; angle += 100) {
		if (player->homedOn == 1 && scene->sessionMode == 1)
			glColor4f(1.0f, 0.0f, 0.0f, 0.25f);
		else
			glColor4f(0.0f, 1.0f, 0.0f, 0.25f);
		int heading = ftol(player->detectionAngle);
		float v[2] = { 0.0f, f32(g_trig[(heading % 3600 + 3600) % 3600] * (long double)radius) };
		vec_rotate(v, angle);
		for (int pass = 0; pass < 2; pass++) {
			if (pass == 1) {
				if (player->homedOn == 1)
					glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
				else
					glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
				v[0] = f32(v[0] * 1.2f);
				v[1] = f32(v[1] * 1.2f);
			}
			int cy = gfx_getHeight() / 2;
			int dy = ftol(v[1]) - cy;
			int y = gfx_getHeight() + dy;
			int cx = gfx_getWidth() / 2;
			glVertex2i(cx + ftol(v[0]), y);
		}
	}
	glEnd();
}

/* the two counters at the bottom left (armor, shield) on their plate */
static void main_counters(Scene *scene, Player *player)
{
	float h = hf();
	int y0 = ftol(h - hy(74.0f));
	float w8 = f32(wx(8.0f));
	int x = ftol(wx(8.0f) + w8);
	glEnable(GL_TEXTURE_2D);
	tex_bind(g_textures->managers[scene->hudBarTexture / 512], scene->hudBarTexture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.7109375f);
	glVertex2i(x, gfx_getHeight() - y0);
	glTexCoord2f(1.0f, 0.7109375f);
	float xf = (float)x;
	int vy = gfx_getHeight() - y0;
	glVertex2i(ftol(wx(256.0f) + xf), vy);
	glTexCoord2f(1.0f, 1.0f);
	float y0f = (float)y0;
	h = hf();
	vy = ftol(h - (hy(74.0f) + y0f));
	glVertex2i(ftol(wx(256.0f) + xf), vy);
	glTexCoord2f(0.0f, 1.0f);
	h = hf();
	vy = ftol(h - (hy(74.0f) + y0f));
	glVertex2i(x, vy);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0; k < 2; k++) {
		float scale = f32(wx(0.9f));
		int dy = ftol(hy(37.0f) + y0f);
		int dx = ftol(wx(k == 0 ? 66.0f : 168.0f) + xf);
		hud_drawDigits(dx, dy, scale, k == 0 ? player->armor : player->shield, 3, 0);
	}
}

/* the top left: flag, emblem, the score icon and the score */
static void main_score(Scene *scene, Player *player, int p)
{
	char text[256];
	int x = 4;
	if (scene->playerRecords[p].flagShown == 1) {
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		hud_drawLeaderIcon(scene, p, 4, 8);
		x = 0x1c;
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	hud_drawNameIcon(scene, player->emblem, x, 8);
	x += 0x18;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	replay_drawIcon(scene, x, 8, 0);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(text, "%d", player->score);
	text_drawSized(x + 0x18, 8, text, 16);
}

/* the four weapon slots along the bottom right, 61 units apart: the selected one lit, each with its ammunition */
static void main_weapons(Scene *scene, Player *player)
{
	for (int i = 0, across = 0; across < 0xf4; i++, across += 0x3d) {
		float h = hf();
		int y0 = ftol(h - hy(50.0f));
		float acrossf = (float)across;
		float left = wf();
		left = f32(left - wx(8.0f));
		left = f32(left - wx(244.0f));
		int x = ftol(wx(acrossf) + left);
		int other = player->weapon != i;
		glEnable(GL_TEXTURE_2D);
		tex_bind(g_textures->managers[scene->hudBarTexture / 512], scene->hudBarTexture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		float t0 = tex256(other * 39 + 48);
		float s0 = f32(acrossf * (1.0f / 256));
		glTexCoord2f(s0, t0);
		glVertex2i(x, gfx_getHeight() - y0);
		float s1 = tex256(across + 61);
		glTexCoord2f(s1, t0);
		float xf = (float)x;
		int vy = gfx_getHeight() - y0;
		glVertex2i(ftol(wx(61.0f) + xf), vy);
		float t1 = tex256(other * 39 + 87);
		glTexCoord2f(s1, t1);
		float y0f = (float)y0;
		h = hf();
		vy = ftol(h - (hy(39.0f) + y0f));
		glVertex2i(ftol(wx(61.0f) + xf), vy);
		glTexCoord2f(s0, t1);
		h = hf();
		vy = ftol(h - (hy(39.0f) + y0f));
		glVertex2i(x, vy);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, player->weapon == i ? 1.0f : 0.5f);
		float scale = f32(wx(0.53f));
		float dyf = f32(hy(50.0f) + y0f);
		dyf = f32(dyf - hy(26.0f));
		long double unit = (long double)gfx_getHeight() * SY;
		int dy = ftol(unit + unit + dyf);
		float w28 = f32(wx(28.0f));
		int dx = ftol(wx(4.0f) + w28 + xf);
		hud_drawDigits(dx, dy, scale, player->ammo[i], 3, 0);
	}
}

/* the gauge at the bottom centre: the selected slot's cell of the menu texture (3 x 3 cells of 64 texels), its alpha the
   gauge (at most 1) */
static void main_gauge(Scene *scene, Player *player)
{
	float h = hf();
	h = f32(h - hy(8.0f));
	int y = ftol(h - hy(64.0f));
	float centre = f32(gfx_getWidth() / 2);
	int x = ftol(centre - wx(32.0f));
	glEnable(GL_TEXTURE_2D);
	tex_bind(g_textures->managers[scene->menuBoxTexture / 512], scene->menuBoxTexture % 512);
	float gauge = player->gauge;
	glColor4f(1.0f, 1.0f, 1.0f, gauge > 1.0f ? 1.0f : gauge);
	glBegin(GL_QUADS);
	glTexCoord2f(tex255(player->slot % 3 * 64), tex255((player->slot / 3 + 2) * 64));
	glVertex2i(x, gfx_getHeight() - y);
	glTexCoord2f(tex255((player->slot % 3 + 1) * 64), tex255((player->slot / 3 + 2) * 64));
	float xf = (float)x;
	int vy = gfx_getHeight() - y;
	glVertex2i(ftol(wx(64.0f) + xf), vy);
	glTexCoord2f(tex255((player->slot % 3 + 1) * 64), tex255((player->slot / 3 + 3) * 64));
	float yf = (float)y;
	h = hf();
	vy = ftol(h - (hy(64.0f) + yf));
	glVertex2i(ftol(wx(64.0f) + xf), vy);
	glTexCoord2f(tex255(player->slot % 3 * 64), tex255((player->slot / 3 + 3) * 64));
	h = hf();
	vy = ftol(h - (hy(64.0f) + yf));
	glVertex2i(x, vy);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* the four timers down the right side (those whose bit 8 + k is set in timerFlags): an icon from the emblem
   texture, and the seconds left once 30 or fewer */
static void main_timers(Scene *scene, Player *player)
{
	for (int k = 0; k < 4; k++) {
		if (!(player->timerFlags & 0x100 << k))
			continue;
		float left = player->timers[k];
		float h = f32(gfx_getHeight() / 2);
		h = f32(h - hy(96.0f));
		long double unit = (long double)gfx_getHeight() * SY;
		int y = ftol(unit * (k * 48) + h);
		float w = wf();
		w = f32(w - wx(8.0f));
		int x = ftol(w - wx(32.0f));
		glEnable(GL_TEXTURE_2D);
		tex_bind(g_textures->managers[scene->emblemTexture / 512], scene->emblemTexture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		float s0 = tex255(k * 32);
		glTexCoord2f(s0, 0x1.818182p-1f);                 /* 192 / 255 */
		glVertex2i(x, gfx_getHeight() - y);
		float s1 = tex255((k + 1) * 32);
		glTexCoord2f(s1, 0x1.818182p-1f);
		float xf = (float)x;
		int vy = gfx_getHeight() - y;
		glVertex2i(ftol(wx(32.0f) + xf), vy);
		glTexCoord2f(s1, 0x1.c1c1c2p-1f);                 /* 224 / 255 */
		float yf = (float)y;
		h = hf();
		vy = ftol(h - (hy(32.0f) + yf));
		glVertex2i(ftol(wx(32.0f) + xf), vy);
		glTexCoord2f(s0, 0x1.c1c1c2p-1f);
		h = hf();
		vy = ftol(h - (hy(32.0f) + yf));
		glVertex2i(x, vy);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		if (!(left > 30.0f)) {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			int seconds = ftol(left);
			int ty = ftol(hy(32.0f) + yf);
			int tx = ftol((wx(32.0f) - 22.0f) * 0.5f + xf);
			PATCHED_CALL(0x49395f, void, int, int, int, const char *, int)(tx, ty, 1, STR_2D, seconds);   /* font_penDraw */
		}
	}
}

/* the actor's snapshot (Actor/<name>/SnapShot, loaded once per actor type) at the bottom right, while not in the
   cockpit view (or for a spectator on camera 2) */
static void main_snapshot(Scene *scene, Player *player)
{
	char name[256];
	int x, y;
	if (scene->playing == 1) {
		float h = hf();
		h = f32(h - hy(8.0f));
		h = f32(h - hy(50.0f));
		h = f32(h - wx(8.0f));                        /* (sic: a width) */
		y = ftol(h - hy(64.0f));
		float w = wf();
		w = f32(w - wx(8.0f));
		x = ftol(w - wx(128.0f));
	}
	if (scene->playing == 0) {
		float h = hf();
		h = f32(h - hy(8.0f));
		h = f32(h - wx(8.0f));
		y = ftol(h - hy(64.0f));
		float w = wf();
		w = f32(w - wx(8.0f));
		x = ftol(w - wx(128.0f));
	}
	glEnable(GL_TEXTURE_2D);
	if (scene->snapshotTex[player->actorType] < 0) {
		sprintf(name, "Actor/%s/SnapShot", scene->actorInfo[player->actorType].name);
		scene->snapshotTex[player->actorType] = tex_getIdByName(g_textures, name, 0, 0, 0, 0, 0, 0, 0);
	}
	int id = scene->snapshotTex[player->actorType];
	tex_bind(g_textures->managers[id / 512], id % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2i(x, gfx_getHeight() - y);
	glTexCoord2f(1.0f, 0.0f);
	float xf = (float)x;
	int vy = gfx_getHeight() - y;
	glVertex2i(ftol(wx(128.0f) + xf), vy);
	glTexCoord2f(1.0f, 1.0f);
	float yf = (float)y;
	float h = hf();
	vy = ftol(h - (hy(64.0f) + yf));
	glVertex2i(ftol(wx(128.0f) + xf), vy);
	glTexCoord2f(0.0f, 1.0f);
	h = hf();
	vy = ftol(h - (hy(64.0f) + yf));
	glVertex2i(x, vy);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* the energy bar's top edge (y, pixels) when the bar is short by cut pixels: the height ENERGY_HEIGHT above the
   bottom margin of 22 units */
static int energy_top(int cut, int haveCut)
{
	float a = hf();
	float b = hf();
	b = f32(b - hy(22.0f));
	if (haveCut) {
		float cutf = (float)cut;
		return ftol(a - (b - (hy(ENERGY_HEIGHT) - cutf)));
	}
	return ftol(a - (b - hy(ENERGY_HEIGHT)));
}
static int energy_bottom(void)
{
	float a = hf();
	float b = hf();
	return ftol(a - (b - hy(22.0f)));
}
static int energy_right(void)
{
	float w8 = f32(wx(8.0f));
	return ftol(wx(ENERGY_WIDTH) + w8);
}

/* the energy bar on the left: a faint full-length background, the remaining energy (1 - energyUsed) in blue
   (boosted, timer 2 running), red (overheated, or blinking 4 times a second while warned) or white, and an
   outline */
static void main_energy(Player *player)
{
	int len = ftol(hy(ENERGY_HEIGHT));
	int cut = ftol((1.0L - player->energyUsed) * len);
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 0.25f);
	int y = energy_top(0, 0);
	glVertex2i(ftol(wx(8.0f)), y);
	y = energy_top(0, 0);
	glVertex2i(energy_right(), y);
	y = energy_top(cut, 1);
	glVertex2i(energy_right(), y);
	y = energy_top(cut, 1);
	glVertex2i(ftol(wx(8.0f)), y);

	if (player->timers[2] > 0.0f)
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	else if (player->overheat == 1 || (player->warned == 1 && ftol(player->spawnAge * 4.0f) % 2 != 0))
		glColor4f(1.0f, 0.0f, 0.0f, 0.75f);
	else
		glColor4f(1.0f, 1.0f, 1.0f, 0.75f);
	y = energy_top(cut, 1);
	glVertex2i(ftol(wx(8.0f)), y);
	y = energy_top(cut, 1);
	glVertex2i(energy_right(), y);
	y = energy_bottom();
	glVertex2i(energy_right(), y);
	y = energy_bottom();
	glVertex2i(ftol(wx(8.0f)), y);
	glEnd();

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	float a = hf();
	int y1 = ftol(a - hy(22.0f));
	int x1 = energy_right();
	float b = hf();
	b = f32(b - hy(22.0f));
	int y0 = ftol(b - hy(ENERGY_HEIGHT));
	hud_drawRectOutline(ftol(wx(8.0f)), y0, x1, y1);
}

/* the crosshair at the centre: 64 units, 72 while fireAnim (firing) > 0 (then at alpha 0.75) */
static void main_crosshair(Scene *scene, Player *player)
{
	int size = player->fireAnim > 0.0f ? 0x48 : 0x40;
	int w = hud_toScreenX(size), h = hud_toScreenY(size);
	int top = gfx_getHeight() / 2 - h / 2;
	int left = gfx_getWidth() / 2 - w / 2;
	glEnable(GL_TEXTURE_2D);
	tex_bind(g_textures->managers[scene->crosshairTexture / 512], scene->crosshairTexture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, player->fireAnim > 0.0f ? 0.75f : 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2i(left, gfx_getHeight() - top);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2i(w + left, gfx_getHeight() - top);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2i(w + left, gfx_getHeight() - top - h);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2i(left, gfx_getHeight() - top - h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* a 64-pixel mark in the top right corner, one cell of a 256-texel texture */
static void main_cornerMark(int x, int texture, float s0, float s1)
{
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(s0, 0.75f);
	glVertex2i(x, gfx_getHeight());
	glTexCoord2f(s1, 0.75f);
	glVertex2i(x + 0x40, gfx_getHeight());
	glTexCoord2f(s1, 1.0f);
	glVertex2i(x + 0x40, gfx_getHeight() - 0x40);
	glTexCoord2f(s0, 1.0f);
	glVertex2i(x, gfx_getHeight() - 0x40);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* the part of the HUD drawn next, for the patch DLL (HUD_*) */
static void part(int anchor) { *g_wide->hudPart = anchor; }

static void main_draw(Scene *scene)
{
	char text[256];
	int p = scene->playing == 1 ? scene->localPlayer : scene->watchedPlayer;
	Player *player = &scene->players[p];

	part(HUD_SCREEN);
	if (scene->playing == 1) {
		float flash = player->damageFlash;
		if (flash > 0.0f) {
			glColor4f(1.0f, 1.0f, 1.0f, flash);
			int h = gfx_getHeight();
			gfx_fillRect(0, 0, gfx_getWidth(), h);
		}
	}
	if (scene->playing == 1 && player->hitFlash > 0.0f) {
		glColor4f(1.0f, 0.0f, 0.0f, f32(player->hitFlash * 0.5f));
		int h = gfx_getHeight();
		gfx_fillRect(0, 0, gfx_getWidth(), h);
	}
	if (scene->playing == 1 && (player->homedOn == 1
	    || (player->actorType >= 0 && scene->actorInfo[player->actorType].targetingTime > 0.0f))) {
		part(HUD_PIXELS);
		main_ring(scene, player);
	}
	part(HUD_LEFT);
	if (scene->playing == 1)
		main_counters(scene, player);
	if (scene->playing == 1) {
		part(HUD_CENTRE);
		if (scene->ladderGame == 1)
			main_score(scene, player, p);
		part(HUD_RIGHT);
		if (scene->playing == 1)
			main_weapons(scene, player);
	}
	part(HUD_CENTRE);
	if (player->gauge > 0.0f && scene->playing == 1)
		main_gauge(scene, player);
	part(HUD_RIGHT);
	if (scene->playing == 1)
		main_timers(scene, player);
	if ((scene->playing == 1 && scene->selectedActor != p) || (scene->playing == 0 && scene->cameraSlot == 2))
		main_snapshot(scene, player);
	part(HUD_LEFT);
	if (scene->playing == 1)
		main_energy(player);
	part(HUD_CENTRE);
	if (scene->playing == 1 && player->state == 1)
		main_crosshair(scene, player);

	/* top right: the solo mark, the team mark, the leader mark (rank 1 with kills), else "rank/count" */
	part(HUD_CORNER);
	if (scene->kingOfTheHill == 1) {
		if (player->isKing == 1) {
			int x = gfx_getWidth() - 0x40;
			glEnable(GL_TEXTURE_2D);
			main_cornerMark(x, scene->markerTexture, 0.0f, 0.25f);
			return;
		}
	} else if (scene->platoon == 1) {
		if (player->isPlatoonLeader == 1) {
			int x = gfx_getWidth() - 0x40;
			glEnable(GL_TEXTURE_2D);
			main_cornerMark(x, scene->markerTexture, tex256((player->team + 1) * 64), tex256((player->team + 2) * 64));
		}
		return;
	} else if (scene->rank[p] == 1 && player->kills > 0) {
		int x = gfx_getWidth() - 0x40;
		glEnable(GL_TEXTURE_2D);
		main_cornerMark(x, scene->hudTexture, 0.0f, 0.25f);
		return;
	}
	part(HUD_RIGHT);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(text, "%d/%d ", scene->rank[p], scene->rankCount);
	text_drawSized(0x280 - (int)strlen(text) * 13, 8, text, 16);
}

/* 0x4926f0: the main HUD of the local player while playing (else of the watched player) */
void THISCALL (hud_drawMain)(Scene *scene)
{
	int was = *g_wide->hudPart;
	main_draw(scene);
	part(was);
}
