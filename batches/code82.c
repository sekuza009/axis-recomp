/* batch 81 (lifted/grp27.c) */
#include "lifted/grp27.c"
/* 0x4566c0 (thiscall) tex_bind(i): bind texture i through the cache of GL texture slots (0x14 bytes: slot number,
   owner texture, GL name, next, prev; a ring at +0xcd12c, +0xcd134 the slot reused next). A texture without a slot
   (+0xc0168 < 0) takes that one: loaded (tex_loadColorMask), tinted (flag 2), uploaded (flag 1: no mipmaps), the
   upload count +0xcd138 counted; one with a slot is reloaded the same way when flagged (+0xc018c), else just bound.
   The slot then becomes the newest: moved before the next-reused one, or, if it was that one, the ring advances and
   the new next-reused slot's owner loses it */
static THISCALL DWORD tex_bind(char *tm, DWORD i)
{
	DWORD v[1] = { i };
	return run_lifted(lift_4566c0, (DWORD)tm, 1, v);
}
