/* lists.c: the free lists of the loaders' pools: a node pushed on the front of a doubly linked list whose count
   goes down (it counts the entries still free). */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

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
void THISCALL (load_481730)(void *self, u8 *node) { push_front(self, node, 8, 0x28); }
/* 0x481980: links at +0x48 / +0x4c, head and count at +0x48 / +0x4c */
void THISCALL (load_481980)(void *self, u8 *node) { push_front(self, node, 0x48, 0x48); }

/* 0x441120: a new 0x3538-byte node (malloc'd; prev +0x3530, next +0x3534) appended to the list at *head, and set up
   by 0x440e20 with the value at 0x9dae10 (returns what that leaves in eax; 0 without memory) */
u32 (tunnel_appendRing)(u8 **head)
{
	u8 *first = *head;
	u8 *node = crt_malloc(0x3538);
	if (!node)
		return 0;
	if (!*head) {
		*head = node;
		FIELD(u8 *, node, 0x3530) = 0;
	} else {
		u8 *last = first;
		while (FIELD(u8 *, last, 0x3534))
			last = FIELD(u8 *, last, 0x3534);
		FIELD(u8 *, last, 0x3534) = node;
		FIELD(u8 *, node, 0x3530) = last;
	}
	FIELD(u8 *, node, 0x3534) = 0;
	return FUN_00440e20(node, GAME_VAR(int, 0x9dae10));
}
