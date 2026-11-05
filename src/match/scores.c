/* scores.c: the players' scores at the start of a match. */
#include "../game.h"

/* 0x4620e0 (thiscall on the scene): every player's kills, deaths, time and the other counts cleared and the team
   unset (and, in a network game, the player's flag-record slot 0x1755278 + i * 0x47fd2 set to -1); then the actor
   reset and the ranking */
void THISCALL (scene_resetScores)(Scene *scene)
{
	for (int i = 0; i < 16; i++) {
		Player *p = &scene->players[i];
		p->inPlay = 0;
		p->kills = 0;
		p->deaths = 0;
		p->killsCounted = 0;
		p->deathsCounted = 0;
		p->timePlayed = 0;
		p->timeExtra = 0.0f;
		p->team = -1;
		if (scene->network == 1)
			scene->playerRecords[i].team = -1;
	}
	stage_clearActorRefs(STAGE(scene));
	scene_updateRanking(scene);
}

/* a mark taken by player i: the notice (local, or with the player's name) and its sound */
static void mark_notice(Scene *scene, int i, u32 local, u32 other)
{
	if (i == scene->localPlayer) {
		notice_printCentre(scene, (const char *)RELOC(local));
		sound_playVolume(6, 100);
	} else {
		notice_printCentre(scene, (const char *)RELOC(other), scene->players[i].name);
		sound_playVolume(7, 100);
	}
}

/* 0x462150 (thiscall on the scene): the ranking. The team counts (redTeamCount / blueTeamCount by the team's slot, noTeamCount
   the players flagged at 0x9f9840 without a team), then the players with a team in order of kills (fewer deaths
   first on a tie: ranking[], rank[] their places, ties sharing one), the local player's place. With the king mark
   (kingOfTheHill): the first player marked (markSolo, with a notice "you are" / "%s is" the new king when it changes)
   and put on team 0, the others on team 1. With the team leaders (platoon): per team the player with the most
   time (timePlayed + timeExtra) marked (markTeam, with a notice when it changes) */
void THISCALL (scene_updateRanking)(Scene *scene)
{
	scene->redTeamCount = scene->blueTeamCount = scene->noTeamCount = 0;
	for (int i = 0; i < 16; i++) {
		Player *p = &scene->players[i];
		if (p->team >= 0) {
			if (scene_teamSide(scene, p->team) == 0)
				scene->redTeamCount++;
			else if (scene_teamSide(scene, p->team) == 1)
				scene->blueTeamCount++;
		} else if (net_playerInUse(i) == 1 && p->team < 0)   /* the player's 0x9f9840 flag */
			scene->noTeamCount++;
	}
	for (int k = 0; k < 16; k++)
		scene->ranking[k] = scene->rank[k] = -1;
	scene->rankCount = 0;
	for (int k = 0; k < 16; k++) {
		int best = -1, bestKills = (int)0x80000000;
		for (int i = 0; i < 16; i++) {
			const Player *p = &scene->players[i];
			if (p->team < 0 || scene->rank[i] >= 0)
				continue;
			if (p->kills > bestKills
			    || (best >= 0 && p->kills == scene->players[best].kills && p->deaths < scene->players[best].deaths)) {
				bestKills = p->kills;
				best = i;
			}
		}
		if (best < 0)
			break;
		scene->rank[best] = k;
		scene->ranking[k] = best;
		scene->rankCount++;
	}
	int place = 0;
	for (int j = 0; j < scene->rankCount; j++) {
		if (j > 0) {
			const Player *cur = &scene->players[scene->ranking[j]], *prev = &scene->players[scene->ranking[j - 1]];
			if (cur->kills < prev->kills || (cur->kills == prev->kills && cur->deaths > prev->deaths))
				place = j;
		}
		scene->rank[scene->ranking[j]] = place + 1;
	}
	if (scene->localPlayer >= 0)
		scene->rankShown = scene->rank[scene->localPlayer];
	if (scene->kingOfTheHill == 1)
		for (int i = 0; i < 16; i++) {
			Player *p = &scene->players[i];
			if (p->team < 0)
				continue;
			if (i == scene->ranking[0]) {
				if (p->markSolo == 0)
					mark_notice(scene, i, STR(0x4c4644, "YOU ARE THE NEW KING!"), STR(0x4c4630, "%s IS THE NEW KING!"));
				p->markSolo = 1;
				player_setTeam(STAGE(scene), i, 0);
				scene->kingPlayer = i;
				if (scene->localPlayer == i)
					scene->localTeam = 0;
			} else {
				p->markSolo = 0;
				player_setTeam(STAGE(scene), i, 1);
				if (scene->localPlayer == i)
					scene->localTeam = 1;
			}
		}
	if (scene->platoon != 1)
		return;
	for (int t = 0; t < 2; t++) {
		int leader = -1;
		float most;
		BITS(most) = 0x800000;   /* the smallest normal float */
		for (int i = 0; i < 16; i++) {
			const Player *p = &scene->players[i];
			if (p->team != t)
				continue;
			long double time = fadd_m((long double)p->timePlayed, &p->timeExtra);
			if (time > (long double)most) {
				most = f32(time);
				leader = i;
			}
		}
		for (int i = 0; i < 16; i++) {
			Player *p = &scene->players[i];
			if (p->team != t)
				continue;
			if (i != leader)
				p->markTeam = 0;
			else if (p->markTeam == 0) {
				p->markTeam = 1;
				mark_notice(scene, i, STR(0x4c4614, "YOU ARE THE NEW COMMANDER!"), STR(0x4c45f8, "%s IS THE NEW COMMANDER!"));
			}
		}
		scene->teamLeaders[t] = leader;
	}
}
