/* dplay_calls.c: thin calls into DirectPlay (IDirectPlay4A g_dplay: Receive, Send, Close) and the lobby object's
   creation, and the connection slots' session listing by connection kind. */
#include "../game.h"

#define DP_CLOSE 0x10
#define DP_RECEIVE 0x64
#define DP_SEND 0x68
#define CLSCTX_INPROC_SERVER 1


/* 0x450bc0 (dplay_receive): the next message (from, to: player ids out; data and *size in / out); 0 without
   DirectPlay */
long (dplay_receive)(u32 *from, u32 *to, u32 flags, void *data, u32 *size)
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

/* 0x4539f0: the DirectPlay lobby object (class k_CLSID_DirectPlay, interface k_IID_IDirectPlay4A) into *out */
long (dplay_createLobby)(void **out)
{
	return CoCreateInstance((const void *)OBJ(k_CLSID_DirectPlay), NULL, CLSCTX_INPROC_SERVER, (const void *)OBJ(k_IID_IDirectPlay4A), out);
}

/* 0x453260: list the sessions through the slot of the connection kind in use */
int (dplay_listSessions)(void)
{
	switch (g_connectionKind) {
	case 0: return dplaySlot0_enum();
	case 1: return dplaySlot1_enum();
	case 2: return dplaySlot2_enum();
	case 3: return dplaySlot3_enum();
	}
	return 0;
}
