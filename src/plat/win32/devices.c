/* plat/win32/devices.c: the sound, music, input and network operations of plat.h for Windows (portable build only): each is the call
   the original makes - plat.h's master definitions, expanded here - so behaviour is the same as master's. Sound is
   DirectSound, music DirectShow's multimedia stream (both through the game's import slots, which the network layer
   may hook). */
#include "../../game.h"
#include <string.h>
#ifdef AXIS_PORTABLE
#undef AXIS_PORTABLE   /* (plat.h's master definitions: the original's calls) */
#include "../plat.h"
#define AXIS_PORTABLE

/* a host supplying the input (axis_api.h axis_host / axis_input; set by standalone/portable.c): no DirectInput
   devices - the keyboard's 256 bytes and the mouse's movement, wheel and buttons come from the host each frame */
int g_platHostInput;
unsigned char g_platKeys[256];
int g_platMouse[3];          /* x, y, wheel since the last read */
unsigned g_platButtons;      /* bit 0 left, 1 right, 2 middle, 3 the fourth */
void *g_platHostWindow;      /* the host's window: sound has the focus with it */
#define HOST_DEVICE ((void *)0x41584953)   /* (a handle that is not one) */

long plat_soundCreate(void **device) { return SND_CREATE(device); }
long plat_soundSetWindow(void *ds, void *window) { return SND_SET_WINDOW(ds, g_platHostWindow ? g_platHostWindow : window); }
long plat_soundCreateBuffer(void *ds, void *desc, void **buffer) { return SND_CREATE_BUFFER(ds, desc, buffer); }
long plat_soundDuplicate(void *ds, void *buffer, void **copy) { return SND_DUPLICATE(ds, buffer, copy); }
u32 plat_soundRelease(void *object) { return SND_RELEASE(object); }
long plat_soundSetFormat(void *b, void *format) { return SND_SET_FORMAT(b, format); }
long plat_soundPlay(void *b, u32 flags) { return SND_PLAY(b, flags); }
long plat_soundSetVolume(void *b, int volume) { return SND_SET_VOLUME(b, volume); }
long plat_soundSetPan(void *b, int pan) { return SND_SET_PAN(b, pan); }
long plat_soundLock(void *b, u32 size, void **data, u32 *bytes) { return SND_LOCK(b, size, data, bytes); }
long plat_soundUnlock(void *b, void *data, u32 bytes) { return SND_UNLOCK(b, data, bytes); }

long plat_musicCreate(void **stream) { return MUS_CREATE(stream); }
long plat_musicInit(void *s) { return MUS_INIT(s); }
long plat_musicAddAudio(void *s) { return MUS_ADD_AUDIO(s); }
long plat_musicOpen(void *s, const void *wideName) { return MUS_OPEN(s, wideName); }
u32 plat_musicSetState(void *s, u32 state) { return MUS_SET_STATE(s, state); }
long plat_musicDuration(void *s, void *time) { return MUS_DURATION(s, time); }
u32 plat_musicTime(void *s, u32 *time) { return MUS_TIME(s, time); }
u32 plat_musicSeek(void *s, u32 low, u32 high) { return MUS_SEEK(s, low, high); }
long plat_musicRelease(void *s) { return MUS_RELEASE(s); }

long plat_inputCreate(void *instance, void **input) { if (g_platHostInput) { *input = HOST_DEVICE; return 0; } return IN_CREATE(instance, input); }
long plat_inputCreateKeyboard(void *di, void **keyboard) { if (g_platHostInput) { *keyboard = HOST_DEVICE; return 0; } return IN_CREATE_KEYBOARD(di, keyboard); }
long plat_inputCreateMouse(void *di, void **mouse) { if (g_platHostInput) { *mouse = HOST_DEVICE; return 0; } return IN_CREATE_MOUSE(di, mouse); }
long plat_inputSetKeyboardFormat(void *k) { return g_platHostInput ? 0 : IN_SET_KEYBOARD_FORMAT(k); }
long plat_inputSetMouseFormat(void *m) { return g_platHostInput ? 0 : IN_SET_MOUSE_FORMAT(m); }
long plat_inputSetWindow(void *d, void *window, u32 mode) { return g_platHostInput ? 0 : IN_SET_WINDOW(d, window, mode); }
long plat_inputAcquire(void *d) { return g_platHostInput ? 0 : IN_ACQUIRE(d); }
long plat_inputUnacquire(void *d) { return g_platHostInput ? 0 : IN_UNACQUIRE(d); }
long plat_inputRead(void *d, u32 size, void *state)
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
