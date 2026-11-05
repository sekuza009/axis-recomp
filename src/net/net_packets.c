/* net_packets.c: the match's packet layer (linked after the C runtime in the exe, 0x4a8300 ..). Every packet is 64
   bytes; each player's packets are numbered 0..127 in turn (the number goes in the packet's first byte). Sent
   packets are kept (0xaef6a0: 16 players x 128 x 64 bytes) so a lost one can be sent again when its receiver asks:
   a packet whose first byte has bit 7 set is such a request, for the number in its low bits, from the player in its
   second byte. Received ones wait in the player table (g_netSlots) or, arriving ahead of their turn, in the history marked in 0xb0f6a0 (16 x 128 flags). */
#include "../game.h"
#include <string.h>

#define g_netClient g_slotTakenFlag           /* the packet layer is on (as a client) */
#define g_localSlot g_watchedSlot            /* the local player's slot */
#define g_send g_netSendPacket                                            /* the message sent */

/* 0x4a8300: the layer reset; host 1: on as a client. Returns the eax the fills leave (-1) */
u32 (netq_reset)(int host)
{
	g_netClient = host == 1;
	memset(g_ahead, 0, 0x800 * 4);
	memset(g_unused16, 0, 0x10 * 4);
	memset(g_nextNumber, 0xff, 0x10 * 4);
	g_netqCursor = 0;
	g_resends = 0;
	return 0xffffffff;
}

/* 0x4a8350: online, the network's incoming messages gathered (net_receiveAll, through its jump) */
u32 (netq_poll)(void)
{
	if (!g_netQueueOnline)
		return 0;
	return jmp_net_receiveAll();
}

/* 0x4a8360: a packet (size bytes, 64 expected: else an error message) numbered and sent to every player, a copy kept
   for resending. 0 when the layer is off */
u32 (net_sendPacketData)(int size, const void *data)
{
	if (!net_isClient())
		return 0;
	if (size != 0x40)
		sys_errorTerminate((const char *)STR(0x4d1640, "incorrect packet data size(%d/%d) - p..."), size, 0x40);
	u8 slot = g_localSlot;
	g_send->size = (short)size;
	memcpy(g_send->data, data, (u32)size);
	g_send->slot = slot;
	if (g_nextNumber[slot] < 0)
		g_nextNumber[slot] = 0;
	int number = g_nextNumber[slot];
	g_send->data[0] = (u8)number;
	memcpy(g_history + ((slot << 7) + number) * 0x40, g_send->data, (u32)size);
	g_nextNumber[slot] = (u8)(number + 1) & 0x7f;
	net_sendMessage(g_send, 0, size + 9);
	return 1;
}

/* the player's packet in turn taken: its arrived-ahead flag cleared, the next number due */
static void taken(int p)
{
	int number = g_nextNumber[p];
	g_ahead[(p << 7) + number] = 0;
	g_nextNumber[p] = (u8)(number + 1) & 0x7f;
	g_unused16[p] = 0;
}

/* 0x4a8450: the next packet from any player, starting with the one after the last (into *from, *size 64, data):
   1 a packet, 2 a resend request (answered here when it is for the local player's packets), 0 none. A packet that
   is not the one due from its player counts in g_resends and moves the expected number past it */
int (netq_receive)(int *from, int *size, void *data)
{
	if (!netq_online())
		return 0;
	int start = g_netqCursor;
	for (;;) {
		int p = g_netqCursor;
		if (net_playerInUse(p) && g_netSlots[g_netqCursor].waiting == 1)
			break;
		p = g_netqCursor;
		if (g_ahead[(p << 7) + g_nextNumber[p]] == 1) {   /* the one due arrived earlier */
			*from = p;
			*size = 0x40;
			memcpy(data, g_history + ((g_netqCursor << 7) + g_nextNumber[g_netqCursor]) * 0x40, 0x40);
			p = g_netqCursor;
			g_netSlots[p].waiting = 0;
			taken(p);
			return 1;
		}
		g_netqCursor = (p + 1) % 16;
		if (start == g_netqCursor)
			return 0;
	}
	*from = g_netqCursor;
	*size = 0x40;
	int p = g_netqCursor;
	memcpy(data, g_netSlots[p].packet, 0x40);
	p = g_netqCursor;
	int due = g_nextNumber[p];
	g_netSlots[p].waiting = 0;
	u8 head = g_netSlots[p].packet[0];
	int number = head & 0x7f;
	if (head & 0x80) {   /* a resend request */
		u8 local = g_localSlot;
		if (g_netSlots[p].packet[1] == local) {
			g_send->slot = local;
			g_send->size = 0x40;
			memcpy(g_send->data, g_history + ((local << 7) + number) * 0x40, 0x40);
			net_sendMessage(g_send, 0, *size + 9);
		}
		return 2;
	}
	if (due < 0) {
		g_nextNumber[p] = number;
	} else if (number != due) {   /* out of turn: skipped to */
		g_ahead[(p << 7) + number] = 0;
		g_nextNumber[p] = (u8)(number + 1) & 0x7f;
		g_unused16[p] = 0;
		g_resends++;
		return 1;
	}
	taken(p);
	return 1;
}

/* 0x4a86c0 .. 0x4a8730: the layer's flags and counters */
int (netq_online)(void) { return g_netQueueOnline; }
int (net_isClient)(void) { return g_netClient; }
int (net_hostGone)(void) { return g_netHostGone; }
int (net_localSlot)(void) { return g_localSlot; }
int (net_playerInUse)(int i) { return g_netSlots[i].used; }
void (netq_clearResends)(void) { g_resends = 0; }
int (netq_resends)(void) { return g_resends; }
