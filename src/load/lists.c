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
