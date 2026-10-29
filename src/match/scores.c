/* scores.c: the players' scores at the start of a match. */
#include "../game.h"

/* 0x4620e0 (thiscall on the scene): every player's kills, deaths, time and the other counts cleared and the team
   unset (and, in a network game, the player's flag-record slot 0x1755278 + i * 0x47fd2 set to -1); then the actor
   reset and the ranking */
void THISCALL (match_4620e0)(Scene *scene)
{
	for (int i = 0; i < 16; i++) {
		Player *p = &scene->players[i];
		p->statD8 = 0;
		p->kills = 0;
		p->deaths = 0;
		p->statF0 = 0;
		p->statF4 = 0;
		p->timePlayed = 0;
		p->stat100 = 0;
		p->team = -1;
		if (scene->network == 1)
			GAME_VAR(int, (u8 *)scene + 0x1755278 + i * 0x47fd2) = -1;
	}
	FUN_0045df90(STAGE(scene));
	msg_newKing(scene);
}
