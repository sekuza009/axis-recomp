/* batch 101 (lifted/grp47.c) */
#include "lifted/grp47.c"
/* 0x45d3e0 (thiscall on the scene) actor_updateAllParts(actor, vv, draw): per frame for a live actor (+0x14c == 1,
   +0x884c != 1) near the camera (+0x154.. within the scene's range +0xa08 plus the actor's radius +0x3e8 of the
   camera +0x20f3970..): its tint (+0x4f0: hit flash from +0x120, damage glow from +0x4ec / +0x8854, a cloaked actor's
   fade by flag 0x200), then, for the viewing actor (+0x202e8d8) with draw set or for others, its eight object lists
   relit and drawn through hud_46fd20 (lights +0x20f2f3c.. by flags 0x100 / 0x400 / 0x800; the current weapon +0x140);
   a list that cannot be drawn is reloaded (FUN_0045e1f0 / actor_updateBody / FUN_0045e390 / FUN_0045e460 /
   FUN_0045e530 / actor_updatePart) */
static THISCALL DWORD actor_updateAllParts(char *sc, DWORD a, DWORD vv, DWORD draw)
{
	DWORD v[3] = { a, vv, draw };
	return run_lifted(lift_45d3e0, (DWORD)sc, 3, v);
}
