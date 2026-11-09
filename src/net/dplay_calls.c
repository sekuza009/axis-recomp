/* dplay_calls.c: thin calls into DirectPlay (IDirectPlay4A g_dplay: Receive, Send, Close) and the lobby object's
   creation, and the connection slots' session listing by connection kind. */
#include "../game.h"
#include "../plat/plat.h"



/* 0x450bc0 (dplay_receive): the next message (from, to: player ids out; data and *size in / out); 0 without
   DirectPlay */
long (dplay_receive)(u32 *from, u32 *to, u32 flags, void *data, u32 *size)
{
	if (g_dplay == 0)
		return 0;
	return NET_RECEIVE(AP(void, g_dplay), from, to, flags, data, size);
}

/* 0x450bf0 (dplay_send): send data (size bytes) from one player to another; 0 without DirectPlay */
long (dplay_send)(u32 from, u32 to, u32 flags, const void *data, u32 size)
{
	if (g_dplay == 0)
		return 0;
	return NET_SEND(AP(void, g_dplay), from, to, flags, data, size);
}

/* 0x453a10: close a DirectPlay object's session and release it (Release's count; 0 for none) */
long (dplay_closeSession)(void *dplay)
{
	if (dplay == NULL)
		return 0;
	NET_CLOSE(dplay);
	return NET_RELEASE(dplay);
}

/* 0x4539f0: a plain DirectPlay object (CoCreateInstance of k_CLSID_DirectPlay, interface k_IID_IDirectPlay4A) into
   *out; CoCreateInstance's result */
long (dplay_createObject)(APTR(void) *out)
{
	return NET_CREATE(out);
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
