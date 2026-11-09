/* plat/win32/devices.c: the sound, music, input and network operations of plat.h for Windows (portable build only): each is the call
   the original makes - plat.h's master definitions, expanded here - so behaviour is the same as master's. Sound is
   DirectSound, music DirectShow's multimedia stream (both through the game's import slots, which the network layer
   may hook). */
#include "../../game.h"
#include <string.h>
#if defined(AXIS_PORTABLE) && !defined(AXIS_64)   /* (the 64-bit build: plat/host/devices.c) */
#undef AXIS_PORTABLE   /* (plat.h's master definitions: the original's calls) */
#include "../plat.h"
#define AXIS_PORTABLE

/* a host supplying the input (axis_api.h axis_host / axis_input; set by standalone/portable.c): no DirectInput
   devices - the keyboard's 256 bytes and the mouse's movement, wheel and buttons come from the host each frame */
int g_platHostInput;
unsigned char g_platKeys[256];
/* (a host without the game's window: its messages, timers and socket events delivered each frame - standalone/host_window.c) */
void (*g_platPump)(void);
int g_platMouse[3];          /* x, y, wheel since the last read */
unsigned g_platButtons;      /* bit 0 left, 1 right, 2 middle, 3 the fourth */
void *g_platHostWindow;      /* the host's window: sound has the focus with it */
#define HOST_DEVICE ((void *)0x41584953)   /* (a handle that is not one) */

/* a host playing the sound (axis_api.h AxisSound; set by standalone/portable.c): no DirectSound / DirectShow - the
   buffers are the host's (locked into a staging copy here, handed over at the unlock), the music its stream */
#include "../../axis_api.h"
const AxisSound *g_platSound;
void *g_platSoundUser;
#define HOST_PRIMARY ((void *)0x41585052)
#define HOST_MUSIC ((void *)0x41584d55)
typedef struct { u32 magic; void *h; u32 bytes; unsigned char *staging; } HostBuf;
#define HOSTBUF_MAGIC 0x41584246u
static HostBuf *host_buf(void *b) { return b && b != HOST_PRIMARY && b != HOST_DEVICE && ((HostBuf *)b)->magic == HOSTBUF_MAGIC ? (HostBuf *)b : NULL; }
static HostBuf *host_wrap(void *h, u32 bytes)
{
	if (!h) return NULL;
	HostBuf *b = (HostBuf *)operator_new(sizeof *b);
	b->magic = HOSTBUF_MAGIC;
	b->h = h;
	b->bytes = bytes;
	b->staging = NULL;
	return b;
}

#define HS g_platSound
#define HU g_platSoundUser
long plat_soundCreate(void **device) { if (HS) { *device = HOST_DEVICE; return 0; } return SND_CREATE(device); }
long plat_soundSetWindow(void *ds, void *window) { if (HS) return 0; return SND_SET_WINDOW(ds, g_platHostWindow ? g_platHostWindow : window); }
long plat_soundCreateBuffer(void *ds, void *desc, void **buffer)
{
	if (!HS)
		return SND_CREATE_BUFFER(ds, desc, buffer);
	const u32 *d = (const u32 *)desc;   /* DSBUFFERDESC: size, flags, bytes, reserved, the format */
	if (d[1] & 1) {   /* DSBCAPS_PRIMARYBUFFER: the mix itself, the host's */
		*buffer = HOST_PRIMARY;
		return 0;
	}
	HostBuf *b = host_wrap(HS->create(HU, AP(const void, d[4]), d[2]), d[2]);
	*buffer = b;
	return b ? 0 : (long)0x80004005;   /* E_FAIL */
}
long plat_soundDuplicate(void *ds, void *buffer, void **copy)
{
	if (!HS)
		return SND_DUPLICATE(ds, buffer, copy);
	HostBuf *s = host_buf(buffer), *b = s ? host_wrap(HS->duplicate(HU, s->h), s->bytes) : NULL;
	*copy = b;
	return b ? 0 : (long)0x80004005;
}
u32 plat_soundRelease(void *object)
{
	if (!HS)
		return SND_RELEASE(object);
	HostBuf *b = host_buf(object);
	if (b) {
		HS->release(HU, b->h);
		if (b->staging) operator_delete(b->staging);
		b->magic = 0;
		operator_delete(b);
	}
	return 0;
}
long plat_soundSetFormat(void *b, void *format) { if (HS) return 0; return SND_SET_FORMAT(b, format); }
long plat_soundPlay(void *b, u32 flags)
{
	if (!HS)
		return SND_PLAY(b, flags);
	HostBuf *h = host_buf(b);
	if (h) HS->play(HU, h->h, flags & 1);
	return 0;
}
long plat_soundSetVolume(void *b, int volume) { if (!HS) return SND_SET_VOLUME(b, volume); HostBuf *h = host_buf(b); if (h) HS->volume(HU, h->h, volume); return 0; }
long plat_soundSetPan(void *b, int pan) { if (!HS) return SND_SET_PAN(b, pan); HostBuf *h = host_buf(b); if (h) HS->pan(HU, h->h, pan); return 0; }
long plat_soundLock(void *b, u32 size, void **data, u32 *bytes)
{
	if (!HS)
		return SND_LOCK(b, size, data, bytes);
	HostBuf *h = host_buf(b);
	if (!h) return (long)0x80004005;
	if (size > h->bytes) size = h->bytes;
	if (!h->staging) h->staging = (unsigned char *)operator_new(h->bytes);
	*data = h->staging;
	*bytes = size;
	return 0;
}
long plat_soundUnlock(void *b, void *data, u32 bytes)
{
	if (!HS)
		return SND_UNLOCK(b, data, bytes);
	HostBuf *h = host_buf(b);
	if (h) {
		HS->write(HU, h->h, data, bytes);
		if (h->staging) { operator_delete(h->staging); h->staging = NULL; }
	}
	return 0;
}

/* the music: 100 ns units as the original's stream has them */
long plat_musicCreate(void **stream) { if (HS) { *stream = HOST_MUSIC; return 0; } return MUS_CREATE(stream); }
long plat_musicInit(void *s) { if (HS) return 0; return MUS_INIT(s); }
long plat_musicAddAudio(void *s) { if (HS) return 0; return MUS_ADD_AUDIO(s); }
long plat_musicOpen(void *s, const void *wideName)
{
	if (!HS)
		return MUS_OPEN(s, wideName);
	char name[264];
	const unsigned short *w = (const unsigned short *)wideName;
	int i = 0;
	for (; w[i] && i < 263; i++) name[i] = w[i] < 128 ? (char)w[i] : '_';   /* (the game's music names are ASCII) */
	name[i] = 0;
	return HS->music_open(HU, name) == 0 ? 0 : (long)0x80004005;
}
u32 plat_musicSetState(void *s, u32 state) { if (HS) { HS->music_run(HU, state != 0); return 0; } return MUS_SET_STATE(s, state); }
long plat_musicDuration(void *s, void *time)
{
	if (!HS)
		return MUS_DURATION(s, time);
	unsigned long long t = (unsigned long long)(HS->music_length(HU) * 1e7);
	memcpy(time, &t, 8);
	return 0;
}
u32 plat_musicTime(void *s, u32 *time)
{
	if (!HS)
		return MUS_TIME(s, time);
	unsigned long long t = (unsigned long long)(HS->music_time(HU) * 1e7);
	memcpy(time, &t, 8);
	return 0;
}
u32 plat_musicSeek(void *s, u32 low, u32 high)
{
	if (!HS)
		return MUS_SEEK(s, low, high);
	HS->music_seek(HU, (double)((unsigned long long)high << 32 | low) / 1e7);
	return 0;
}
long plat_musicRelease(void *s) { if (HS) { HS->music_close(HU); return 0; } return MUS_RELEASE(s); }

long plat_inputCreate(void *instance, void **input) { if (g_platHostInput) { *input = HOST_DEVICE; return 0; } return IN_CREATE(instance, input); }
long plat_inputCreateKeyboard(void *di, void **keyboard) { if (g_platHostInput) { *keyboard = HOST_DEVICE; return 0; } return IN_CREATE_KEYBOARD(di, keyboard); }
long plat_inputCreateMouse(void *di, void **mouse) { if (g_platHostInput) { *mouse = HOST_DEVICE; return 0; } return IN_CREATE_MOUSE(di, mouse); }
long plat_inputSetKeyboardFormat(void *k) { return g_platHostInput ? 0 : IN_SET_KEYBOARD_FORMAT(k); }
long plat_inputSetMouseFormat(void *m) { return g_platHostInput ? 0 : IN_SET_MOUSE_FORMAT(m); }
long plat_inputSetWindow(void *d, void *window, u32 mode) { return g_platHostInput ? 0 : IN_SET_WINDOW(d, window, mode); }
long plat_inputAcquire(void *d) { return g_platHostInput ? 0 : IN_ACQUIRE(d); }
long plat_inputUnacquire(void *d) { return g_platHostInput ? 0 : IN_UNACQUIRE(d); }
/* (a check: each mouse read's movement to the loader's mouse log - standalone/portable.c, AXIS_MOUSELOG) */
void (*g_platMouseLog)(long dx, long dy);
static long input_read(void *d, u32 size, void *state);
long plat_inputRead(void *d, u32 size, void *state)
{
	long r = input_read(d, size, state);
	if (g_platMouseLog && size == 0x10 && r >= 0)
		g_platMouseLog(((long *)state)[0], ((long *)state)[1]);
	return r;
}
static long input_read(void *d, u32 size, void *state)
{
	if (!g_platHostInput)
		return IN_READ(d, size, state);
	if (size == 0x100) {   /* the keyboard: DIK codes, bit 7 held */
		memcpy(state, g_platKeys, 0x100);
		return 0;
	}
	if (size == 0x10) {    /* DIMOUSESTATE: movement x, y, wheel since the last read, 4 buttons */
		long *m = (long *)state;
		unsigned char *b = (unsigned char *)state + 12;
		m[0] = g_platMouse[0];
		m[1] = g_platMouse[1];
		m[2] = g_platMouse[2];
		g_platMouse[0] = g_platMouse[1] = g_platMouse[2] = 0;
		for (int i = 0; i < 4; i++)
			b[i] = g_platButtons >> i & 1 ? 0x80 : 0;
		return 0;
	}
	return 0;
}
long plat_inputRelease(void *object) { return g_platHostInput || object == HOST_DEVICE ? 0 : IN_RELEASE(object); }
/* network */
long plat_netCreate(void **out) { return NET_CREATE(out); }
long plat_netLobbyCreate(void **out) { return NET_LOBBY_CREATE(out); }
long plat_netRelease(void *o) { return NET_RELEASE(o); }
long plat_netClose(void *p) { return NET_CLOSE(p); }
u32 plat_netDestroyPlayer(void *p, u32 id) { return NET_DESTROY_PLAYER(p, id); }
int plat_netEnumSessions(void *p, void *desc, void *callback) { return NET_ENUM_SESSIONS(p, desc, callback); }
int plat_netGetPlayerName(void *p, u32 id, void *name, u32 *size) { return NET_GET_PLAYER_NAME(p, id, name, size); }
int plat_netCreatePlayer(void *p, u32 *id, void *name) { return NET_CREATE_PLAYER(p, id, name); }
int plat_netOpen(void *p, void *desc, u32 flags) { return NET_OPEN(p, desc, flags); }
int plat_netLobbyGetConnection(void *l, void *buffer, u32 *size) { return NET_LOBBY_GET_CONNECTION(l, buffer, size); }
int plat_netLobbySetConnection(void *l, void *connection) { return NET_LOBBY_SET_CONNECTION(l, connection); }
int plat_netLobbyConnect(void *l, void **out) { return NET_LOBBY_CONNECT(l, out); }
int plat_netEnumConnections(void *p, void *callback) { return NET_ENUM_CONNECTIONS(p, callback); }
int plat_netLobbyAddress(void *l, void *elements, u32 n, void *block, u32 *size) { return NET_LOBBY_ADDRESS(l, elements, n, block, size); }
int plat_netInitConnection(void *p, void *connection) { return NET_INIT_CONNECTION(p, connection); }
int plat_netGetCaps(void *p, u32 *caps) { return NET_GET_CAPS(p, caps); }
long plat_netReceive(void *p, u32 *from, u32 *to, u32 flags, void *data, u32 *size) { return NET_RECEIVE(p, from, to, flags, data, size); }
long plat_netSend(void *p, u32 from, u32 to, u32 flags, const void *data, u32 size) { return NET_SEND(p, from, to, flags, data, size); }
#endif
