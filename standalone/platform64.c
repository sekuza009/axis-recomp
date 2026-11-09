/* platform64.c: the services the native build's fixes use (src/fixes/settings.h) in the 64-bit build - standalone/
   platform.c's, under a host: the settings from axisnet.ini in the game folder, the focus from the host, the pixel-sharp
   text's texture filters recorded for the host (glrec64.c), the ending movie (movie64.c). */
#if defined(__x86_64__) || defined(__aarch64__)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../src/fixes/settings.h"

void hlog(const char *fmt, ...);   /* host64.c */
Settings g_settings = { 1, 1, 16.0f / 9.0f, 1, 1.0f, 1.0f };
int g_platformHostFocus = -1;

/* a value of axisnet.ini ([section] key=value; case ignored), or def */
static void ini_get(const char *section, const char *key, const char *def, char *out, size_t room)
{
	snprintf(out, room, "%s", def);
#ifdef _WIN32
	FILE *f = fopen("axisnet.ini", "r");
#else   /* (the user folder's when there is one: src/plat/posix/files.c) */
	FILE *plat_fopen(const char *path, const char *mode);
	FILE *f = plat_fopen("axisnet.ini", "r");
#endif
	if (!f)
		return;
	char line[256];
	int in = 0;
	while (fgets(line, sizeof line, f)) {
		char *p = line;
		while (*p == ' ' || *p == '\t')
			p++;
		p[strcspn(p, "\r\n")] = 0;
		if (*p == '[') {
			char *e = strchr(p, ']');
			if (e) *e = 0;
			in = !strcasecmp(p + 1, section);
			continue;
		}
		char *eq = strchr(p, '=');
		if (!in || !eq)
			continue;
		*eq = 0;
		char *k = p, *v = eq + 1;
		for (char *t = eq - 1; t >= k && (*t == ' ' || *t == '\t'); t--)
			*t = 0;
		while (*v == ' ' || *v == '\t')
			v++;
		if (!strcasecmp(k, key)) {
			snprintf(out, room, "%s", v);
			break;
		}
	}
	fclose(f);
}

void platform_loadSettings(void)
{
	char v[32];
	ini_get("hud", "menu43", "1", v, sizeof v);
	g_settings.menu43 = atoi(v);
	ini_get("hud", "proportional", "1", v, sizeof v);
	g_settings.hudProportional = atoi(v);
	ini_get("hud", "sharptext", "1", v, sizeof v);
	g_settings.sharpText = atoi(v);
	ini_get("hud", "maxaspect", "1.7778", v, sizeof v);
	g_settings.hudMaxAspect = (float)atof(v);
	ini_get("input", "menusens", "1", v, sizeof v);
	g_settings.menuSens = (float)atof(v);
	ini_get("input", "escmenusens", "1", v, sizeof v);
	g_settings.escMenuSens = (float)atof(v);
}

extern int (*host64_focus)(void);
int platform_isForeground(void *window) { (void)window; return host64_focus ? host64_focus() : 1; }
unsigned platform_ticks(void)
{
	struct timespec t;
	timespec_get(&t, TIME_UTC);
	return (unsigned)(t.tv_sec * 1000u + t.tv_nsec / 1000000);
}
float platform_pointerSpeed(void) { return 1.0f; }   /* (the host's pointer speed is its own) */
void platform_mouseButtons(int bits) { (void)bits; }
void platform_watchWindow(void *window, void **editField, void **mouseDevice) { (void)window; (void)editField; (void)mouseDevice; }
int glrec64_texNearest(int saved[2]);
void glrec64_texRestore(const int saved[2]);
int platform_texNearest(int saved[2]) { return glrec64_texNearest(saved); }
void platform_texRestore(const int saved[2]) { glrec64_texRestore(saved); }
/* the ending movie: started here, shown over the host's next frames (movie64.c; host64.c axis_frame) */
extern const void *g_platSound;   /* (the host's AxisSound: src/plat/host/devices.c) */
extern void *g_platSoundUser;
int movie64_start(const char *path, const void *sound, void *user);
void platform_playMovie(void *owner, const char *file, int w, int h)
{
	(void)owner; (void)w; (void)h;
	movie64_start(file, g_platSound, g_platSoundUser);
}
#endif
