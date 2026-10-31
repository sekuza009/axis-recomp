/* dplay_calls.c: thin calls into DirectPlay (IDirectPlay4A g_dplay: Receive, Send, Close) and the lobby object's
   creation, and the connection slots' session listing by connection kind. */
#include "../game.h"

#define DP_CLOSE 0x10
#define DP_RECEIVE 0x64
#define DP_SEND 0x68
#define CLSCTX_INPROC_SERVER 1

#define g_dplay GAME_VAR(void *, 0xa0b404)            /* IDirectPlay4A */
#define g_connectionKind GAME_VAR(int, 0xa0b418)      /* the connection kind in use: its slot (0 .. 3) */

/* 0x450bc0 (arena_450bc0): the next message (from, to: player ids out; data and *size in / out); 0 without
   DirectPlay */
long (arena_450bc0)(u32 *from, u32 *to, u32 flags, void *data, u32 *size)
{
	if (g_dplay == NULL)
		return 0;
	return COM(g_dplay, DP_RECEIVE, long, u32 *, u32 *, u32, void *, u32 *)(g_dplay, from, to, flags, data, size);
}

/* 0x450bf0 (dplay_send): send data (size bytes) from one player to another; 0 without DirectPlay */
long (dplay_send)(u32 from, u32 to, u32 flags, const void *data, u32 size)
{
	if (g_dplay == NULL)
		return 0;
	return COM(g_dplay, DP_SEND, long, u32, u32, u32, const void *, u32)(g_dplay, from, to, flags, data, size);
}

/* 0x453a10: close a DirectPlay object's session and release it (Release's count; 0 for none) */
long (dplay_closeSession)(void *dplay)
{
	if (dplay == NULL)
		return 0;
	COM(dplay, DP_CLOSE, long)(dplay);
	return COM(dplay, COM_RELEASE, long)(dplay);
}

/* 0x4539f0: the DirectPlay lobby object (class 0x4a9668, interface 0x4a9678) into *out */
long (arena_4539f0)(void **out)
{
	return CoCreateInstance((const void *)0x4a9668, NULL, CLSCTX_INPROC_SERVER, (const void *)0x4a9678, out);
}

/* 0x453260: list the sessions through the slot of the connection kind in use */
int (arena_453260)(void)
{
	switch (g_connectionKind) {
	case 0: return arena_4549c0();
	case 1: return arena_454ae0();
	case 2: return arena_454bf0();
	case 3: return arena_454d00();
	}
	return 0;
}
