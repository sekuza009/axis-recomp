/* lists.c: list links: the free lists of the collision space's pools (a freed node or block pushed on the front of
   the doubly linked free list, the pool's count of nodes in use going down), and a ring appended to the menu tunnel's
   chain (tunnel_appendRing). */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* node's links (prev, next) at link, the list's head and count at head */
static void push_front(void *self, u8 *node, int link, int head)
{
	u8 *first = FIELD(u8 *, self, head);
	FIELD(u8 *, node, link) = NULL;
	FIELD(u8 *, node, link + 4) = first;
	if (first)
		FIELD(u8 *, first, link) = node;
	FIELD(u8 *, self, head) = node;
	FIELD(int, self, head + 4)--;
}

/* 0x481730: links at +8 / +0xc, head and count at +0x28 / +0x2c */
void THISCALL (space_freeNode)(void *self, u8 *node) { push_front(self, node, 8, 0x28); }
/* 0x481980: links at +0x48 / +0x4c, head and count at +0x48 / +0x4c */
void THISCALL (space_freeBlock)(void *self, u8 *node) { push_front(self, node, 0x48, 0x48); }

/* 0x441120: a new 0x3538-byte node (malloc'd; prev back, next next) appended to the list at *head, and set up
   by tunnelRing_build as ring number g_tunnelRings (returns what that leaves in eax; 0 without memory) */
u32 (tunnel_appendRing)(u8 **head)
{
	u8 *first = *head;
	u8 *node = crt_malloc(0x3538);
	if (!node)
		return 0;
	TunnelRing *ring = (TunnelRing *)node;
	if (!*head) {
		*head = node;
		ring->back = 0;
	} else {
		TunnelRing *last = (TunnelRing *)first;
		while (last->next)
			last = last->next;
		last->next = ring;
		ring->back = last;
	}
	ring->next = 0;
	return tunnelRing_build(node, g_tunnelRings);
}
