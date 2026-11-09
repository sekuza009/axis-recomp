/* plat/host/devices.c: the sound, music, input and network operations of plat.h for the 64-bit build (PORTING.md,
   stage 6), where the host does them all: the sounds and the music are the host's (AxisHostConfig.sound), the keyboard
   and mouse the host's (axis_input), as plat/win32/devices.c has them under a host. The game keeps each handle as a
   32-bit number (APTR): a sound buffer is a record in the arena, the devices numbers that are never looked into. */
#include "../../game.h"
#if defined(AXIS_PORTABLE) && defined(AXIS_64)
#include <string.h>
#include "../../axis_api.h"

int g_platHostInput;
unsigned char g_platKeys[256];
void (*g_platPump)(void);
int g_platMouse[3];          /* x, y, wheel since the last read */
unsigned g_platButtons;      /* bit 0 left, 1 right, 2 middle, 3 the fourth */
void *g_platHostWindow;
const AxisSound *g_platSound;
void *g_platSoundUser;
void (*g_platMouseLog)(long dx, long dy);

/* the numbers handed out for the devices, the primary buffer and the music (above everything mapped) */
#define HOST_DEVICE 0xfe7f0010u
#define HOST_PRIMARY 0xfe7f0020u
#define HOST_MUSIC 0xfe7f0030u
static int is_token(const void *p) { return AV(p) >= 0xfe000000u; }

typedef struct { u32 magic; u32 bytes; void *h; unsigned char *staging; } HostBuf;
#define HOSTBUF_MAGIC 0x41584246u
static HostBuf *host_buf(void *b) { return b && !is_token(b) && ((HostBuf *)b)->magic == HOSTBUF_MAGIC ? (HostBuf *)b : NULL; }
static u32 host_wrap(void *h, u32 bytes)
{
	if (!h)
		return 0;
	HostBuf *b = (HostBuf *)operator_new(sizeof *b);
	b->magic = HOSTBUF_MAGIC;
	b->h = h;
	b->bytes = bytes;
	b->staging = NULL;
	return AV(b);
}
#define HS g_platSound
#define HU g_platSoundUser
#define E_FAIL_ ((long)(i32)0x80004005)   /* (negative as a long too: the game tests < 0) */

long plat_soundCreate(APTR(void) *device) { *device = HOST_DEVICE; return HS ? 0 : E_FAIL_; }
long plat_soundSetWindow(void *ds, void *window) { (void)ds; (void)window; return 0; }
long plat_soundCreateBuffer(void *ds, void *desc, APTR(void) *buffer)
{
	(void)ds;
	const u32 *d = (const u32 *)desc;   /* DSBUFFERDESC: size, flags, bytes, reserved, the format (an address) */
	if (!HS)
		return E_FAIL_;
	if (d[1] & 1) {   /* DSBCAPS_PRIMARYBUFFER: the mix itself, the host's */
		*buffer = HOST_PRIMARY;
		return 0;
	}
	*buffer = host_wrap(HS->create(HU, AP(const void, d[4]), d[2]), d[2]);
	return *buffer ? 0 : E_FAIL_;
}
long plat_soundDuplicate(void *ds, void *buffer, APTR(void) *copy)
{
	(void)ds;
	HostBuf *s = host_buf(buffer);
	*copy = s && HS ? host_wrap(HS->duplicate(HU, s->h), s->bytes) : 0;
	return *copy ? 0 : E_FAIL_;
}
u32 plat_soundRelease(void *object)
{
	HostBuf *b = host_buf(object);
	if (b && HS) {
		HS->release(HU, b->h);
		if (b->staging)
			operator_delete(b->staging);
		b->magic = 0;
		operator_delete(b);
	}
	return 0;
}
long plat_soundSetFormat(void *b, void *format) { (void)b; (void)format; return 0; }
long plat_soundPlay(void *b, u32 flags) { HostBuf *h = host_buf(b); if (h && HS) HS->play(HU, h->h, flags & 1); return 0; }
long plat_soundSetVolume(void *b, int volume) { HostBuf *h = host_buf(b); if (h && HS) HS->volume(HU, h->h, volume); return 0; }
long plat_soundSetPan(void *b, int pan) { HostBuf *h = host_buf(b); if (h && HS) HS->pan(HU, h->h, pan); return 0; }
long plat_soundLock(void *b, u32 size, void **data, u32 *bytes)
{
	HostBuf *h = host_buf(b);
	if (!h)
		return E_FAIL_;
	if (size > h->bytes)
		size = h->bytes;
	if (!h->staging)
		h->staging = (unsigned char *)operator_new(h->bytes);
	*data = h->staging;
	*bytes = size;
	return 0;
}
long plat_soundUnlock(void *b, void *data, u32 bytes)
{
	HostBuf *h = host_buf(b);
	if (h && HS) {
		HS->write(HU, h->h, data, bytes);
		if (h->staging) {
			operator_delete(h->staging);
			h->staging = NULL;
		}
	}
	return 0;
}

/* the music: 100 ns units as the original's stream has them */
long plat_musicCreate(APTR(void) *stream) { *stream = HOST_MUSIC; return HS ? 0 : E_FAIL_; }
long plat_musicInit(void *s) { (void)s; return 0; }
long plat_musicAddAudio(void *s) { (void)s; return 0; }
long plat_musicOpen(void *s, const void *wideName)
{
	(void)s;
	char name[264];
	const unsigned short *w = (const unsigned short *)wideName;
	int i = 0;
	for (; w[i] && i < 263; i++)
		name[i] = w[i] < 128 ? (char)w[i] : '_';   /* (the game's music names are ASCII) */
	name[i] = 0;
	return HS && HS->music_open(HU, name) == 0 ? 0 : E_FAIL_;
}
u32 plat_musicSetState(void *s, u32 state) { (void)s; if (HS) HS->music_run(HU, state != 0); return 0; }
long plat_musicDuration(void *s, void *time)
{
	(void)s;
	unsigned long long t = HS ? (unsigned long long)(HS->music_length(HU) * 1e7) : 0;
	memcpy(time, &t, 8);
	return 0;
}
u32 plat_musicTime(void *s, u32 *time)
{
	(void)s;
	unsigned long long t = HS ? (unsigned long long)(HS->music_time(HU) * 1e7) : 0;
	memcpy(time, &t, 8);
	return 0;
}
u32 plat_musicSeek(void *s, u32 low, u32 high)
{
	(void)s;
	if (HS)
		HS->music_seek(HU, (double)((unsigned long long)high << 32 | low) / 1e7);
	return 0;
}
long plat_musicRelease(void *s) { (void)s; if (HS) HS->music_close(HU); return 0; }

long plat_inputCreate(void *instance, APTR(void) *input) { (void)instance; *input = HOST_DEVICE; return 0; }
long plat_inputCreateKeyboard(void *di, APTR(void) *keyboard) { (void)di; *keyboard = HOST_DEVICE; return 0; }
long plat_inputCreateMouse(void *di, APTR(void) *mouse) { (void)di; *mouse = HOST_DEVICE; return 0; }
long plat_inputSetKeyboardFormat(void *k) { (void)k; return 0; }
long plat_inputSetMouseFormat(void *m) { (void)m; return 0; }
long plat_inputSetWindow(void *d, void *window, u32 mode) { (void)d; (void)window; (void)mode; return 0; }
long plat_inputAcquire(void *d) { (void)d; return 0; }
long plat_inputUnacquire(void *d) { (void)d; return 0; }
long plat_inputRead(void *d, u32 size, void *state)
{
	(void)d;
	if (size == 0x100) {   /* the keyboard: DIK codes, bit 7 held */
		memcpy(state, g_platKeys, 0x100);
		return 0;
	}
	if (size == 0x10) {    /* DIMOUSESTATE: movement x, y, wheel since the last read (32-bit LONGs), 4 buttons */
		i32 *m = (i32 *)state;
		unsigned char *b = (unsigned char *)state + 12;
		m[0] = g_platMouse[0];
		m[1] = g_platMouse[1];
		m[2] = g_platMouse[2];
		g_platMouse[0] = g_platMouse[1] = g_platMouse[2] = 0;
		for (int i = 0; i < 4; i++)
			b[i] = g_platButtons >> i & 1 ? 0x80 : 0;
		if (g_platMouseLog)
			g_platMouseLog(m[0], m[1]);
	}
	return 0;
}
long plat_inputRelease(void *object) { (void)object; return 0; }

/* (network: standalone/net64.c - axisnet's DirectPlay, the records translated) */
#endif
