/* armc_parts.c: the ARM CENTER's part-info records (0x80 bytes): what the screen shows of an actor type picked as
   a part or a weapon: its folder's last name, six values copied from its ActorItem, eight scaled. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, AP(u8, RELOC(obj)) + (offset))

/* ActorItem fields copied as they are (PartInfo field, ActorItem field) */
static const short copied[6][2] = { { offsetof(PartInfo, slotType), offsetof(ActorItem, slotType) }, { offsetof(PartInfo, ammoType), offsetof(ActorItem, ammoType) }, { offsetof(PartInfo, ammoPerShot), offsetof(ActorItem, ammoPerShot) }, { offsetof(PartInfo, burst), offsetof(ActorItem, burst) }, { offsetof(PartInfo, damageType), offsetof(ActorItem, damageType) }, { offsetof(PartInfo, damage), offsetof(ActorItem, damage) } };

/* and those scaled by a constant of the game (PartInfo field, ActorItem field, constant's address) */
static const struct { short dst, src; u32 scale; } scaled[8] = {
	{ offsetof(PartInfo, range), offsetof(ActorItem, range), ADDR(k_0_01f) }, { offsetof(PartInfo, speed), offsetof(ActorItem, velocity), ADDR(k_0_01f) }, { offsetof(PartInfo, spread), offsetof(ActorItem, spread), ADDR(k_0_1f) }, { offsetof(PartInfo, hitRange), offsetof(ActorItem, hitRange), ADDR(k_0_01f) }, { offsetof(PartInfo, splashRadius), offsetof(ActorItem, splashRadius), ADDR(k_0_01f) }, { offsetof(PartInfo, cycleTime), offsetof(ActorItem, cycleTime), OBJ(k_1000f) }, { offsetof(PartInfo, guidance), offsetof(ActorItem, guidance), ADDR(k_0_1f) }, { offsetof(PartInfo, targetingTime), offsetof(ActorItem, targetingTime), OBJ(k_1000f) } };

/* record rec for actor type idx; idx -1: the record emptied (its slotType -1) */
static void part_info(u8 *rec, int idx)
{
	if (idx == -1) {
		memset(rec, 0, 64);
		((PartInfo *)rec)->slotType = -1;
		memset(rec + offsetof(PartInfo, ammoType), 0, sizeof(PartInfo) - offsetof(PartInfo, ammoType));   /* ammoType .. the end */
		return;
	}
	ActorItem *info = &AP(Scene, g_scene)->actorItems[idx];

	/* the name: the folder path's part after its last slash */
	char path[128] = { 0 };
	strcpy(path, info->name);
	int n = (int)strlen(path), i = n - 1;
	while (i >= 0 && path[i] != '\\' && path[i] != '/')
		i--;
	memset(rec, 0, 64);
	if (i + 1 < n)
		memcpy(rec, path + i + 1, n - (i + 1));

	for (int k = 0; k < 6; k++)
		FIELD(int, rec, copied[k][0]) = FIELD(int, info, copied[k][1]);
	for (int k = 0; k < 8; k++) {
		if (k == 5)
			((PartInfo *)rec)->splashBorderDamage = ((ActorItem *)info)->splashBorderDamage;
		FIELD(float, rec, scaled[k].dst) =
			(float)((long double)FIELD(float, info, scaled[k].src) * GAME_VAR(float, scaled[k].scale));
	}
	BITS(((PartInfo *)rec)->weight) = BITS(((ActorItem *)info)->weight);
}

/* 0x41ca50: the PartInfo record of item slot slot (0 .. 5: four weapon slots, then the two extra-item slots 4 / 5;
   g_partRecords, 0x80 apart) made from actorItems[idx] (idx -1: emptied) */
void (armc_itemSlotRecord)(int slot, int idx) { part_info(g_partRecords + slot * 0x80, idx); }

/* 0x41cca0: the record of the item being looked at (g_viewedPart, 0x4dc150, the seventh of g_partRecords) from
   actorItems[idx]; for a special item (its ammoType -1) the record's ammoPerShot (g_viewedPartAmmoPerShot, 0x4dc198)
   is overwritten with idx, so armc_drawWeaponsScreen shows MSG(745) + idx (772 .. 780: the item's description lines) */
void (armc_viewedPartRecord)(int idx)
{
	part_info(g_viewedPart, idx);
	if (idx != -1 && g_viewedPartAmmoType == -1)
		g_viewedPartAmmoPerShot = idx;
}

/* ---- armc_readMechStats: the ARM CENTER's stats panel from the local player's actor in the scene (*g_scene): a speed (the
   root of +0x0 times a constant), the actor's values times the game's scale constants, its part's and weapon's
   records' values; every product extended precision, rounded once on store, the second factor from memory as in
   the original. Returns the scene ---- */
typedef long double X;
static void mulf(u32 dst, const float *a, const float *b) { GAME_VAR(float, dst) = (float)fmul_m(fld_m(a), b); }
static void copyf(u32 dst, const float *src) { GAME_VAR(float, dst) = (float)fld_m(src); }   /* (an SNaN quieted) */

/* armc_readMechStats (0x41c510): the ARM CENTER's mech stats from the local player's Actor (*g_scene): the detection
   range (root of detectionRangeSq x 0.01), detection angle, hacking level, lock-on and target-keep times, the seven
   maxima (g_mechMaxima), mobility, the leg type's inertia and corrections, the booster type's thrust type
   (g_unusedMechStat), boost / recharge / rest times, the speeds and load (g_mechSpeeds); every product extended
   precision, rounded once on store, the second factor from memory as in the original. Returns the scene */
u8 *(armc_readMechStats)(void)
{
	u8 *g = AGET(u8, g_scene);
	Scene *sc = (Scene *)g;
	Stage *st = SCENE_STAGE(g);   /* (the scene's stage) */
	const Actor *A = &sc->players[sc->localPlayer];
	X s = fld_m(&A->detectionRangeSq);
	s = x87_fsqrt(s);
	s = s * k_0_01;
	g_mechDetectionRange = (float)s;
	mulf(ADDR(g_mechDetectionAngle), &A->detectionAngle, AP(const float, ADDR(k_0_1f)));
	g_mechHackingLevel = A->hackingLevel;
	mulf(ADDR(g_mechLockOnTime), &A->lockOnTime, AP(const float, ADDR(k_100f)));
	mulf(ADDR(g_mechTargetKeepTime), &A->targetKeepTime, k_1000f);
	for (int i = 0; i < 7; i++)
		g_mechMaxima[i] = ((const int *)&A->armorMax)[i];   /* armorMax, shieldMax, +0x24, ammoMax[4] */
	copyf(ADDR(g_mechMobility), &A->mobility);
	const PlayerRecord *record = &sc->playerRecords[A->player];
	const LegType *leg = &st->legTypes[record->parts[3]];
	copyf(ADDR(g_mechLegsInertia), &leg->inertia);
	mulf(ADDR(g_mechLegsSpeedCorrection), &leg->speedCorrection, AP(const float, ADDR(k_100f)));
	mulf(ADDR(g_mechLegsForwardBoost), &leg->forwardBoostCorrection, AP(const float, ADDR(k_100f)));
	mulf(ADDR(g_mechLegsSideBoost), &leg->sideBoostCorrection, AP(const float, ADDR(k_100f)));
	mulf(ADDR(g_mechLegsBackBoost), &leg->backBoostCorrection, AP(const float, ADDR(k_100f)));
	g_unusedMechStat = st->boosterTypes[record->parts[4]].thrustType;
	mulf(ADDR(g_mechBoostTime), &A->boostTime, k_1000f);
	mulf(ADDR(g_mechBoosterRecharge), &A->rechargeTime, k_1000f);
	mulf(ADDR(g_mechBoosterRestTime), &A->restTime, k_1000f);
	mulf(ADDR(g_mechNormalSpeed), &A->speed, k_0_036f);
	mulf(ADDR_AT(g_mechSpeeds, 1), AP(const float, ADDR(g_mechNormalSpeed)), &A->runTop[0]);
	g_mechMaxSpeedBwd = (float)-fmul_m(fld_m(AP(const float, ADDR(g_mechNormalSpeed))), &A->runTop[1]);
	mulf(ADDR_AT(g_mechSpeeds, 3), AP(const float, ADDR(g_mechNormalSpeed)), &A->runTop[2]);
	copyf(ADDR(g_loadLimit), &A->loadMax);
	copyf(ADDR_AT(g_mechSpeeds, 4), &A->load);
	return g;
}

/* a part's name for the panel: its folder path with '\' and '/' turned into '-', in a zeroed 64-byte field (through
   a zeroed 128-byte buffer; the terminator is not copied) */
static void panel_name(u32 dst, const char *name)
{
	char buf[128];
	memset(buf, 0, sizeof buf);
	strcpy(buf, name);
	int len = (int)strlen(buf);
	for (int i = len - 1; i >= 0; i--) {
		if (buf[i] == '\\')
			buf[i] = '-';
		if (buf[i] == '/')
			buf[i] = '-';
	}
	memset(AP(void, RELOC(dst)), 0, 64);
	if (len > 0)
		memcpy(AP(void, RELOC(dst)), buf, len);
}

/* 0x41b750: the ARM CENTER's part panels' values for the local player's mech, nothing drawn: for its head, chest,
   arm, leg and booster (playerRecords[].parts[0..4]) the part's name ('\' and '/' as '-', g_headPanelName ..) and
   stats, some scaled by the game's constants; g_unusedArmcViewCountdown set to 1. Returns the booster's index
   (parts[4]) */
int (armc_readPartPanels)(void)
{
	u8 *g = AGET(u8, g_scene);
	Scene *sc = (Scene *)g;
	Stage *st = SCENE_STAGE(g);   /* (the scene's stage) */
	const PlayerRecord *record = &sc->playerRecords[sc->players[sc->localPlayer].player];
	const HeadType *head = &st->headTypes[record->parts[0]];   /* head */
	panel_name(OBJ(g_headPanelName), head->name);
	mulf(ADDR(g_headDetectionRange), &head->detectionRange, AP(const float, ADDR(k_0_01f)));
	mulf(ADDR(g_headDetectionAngle), &head->detectionAngle, AP(const float, ADDR(k_0_1f)));
	g_headHackingLevel = head->hackingLevel;
	mulf(ADDR(g_headLockOnTime), &head->lockOnTime, AP(const float, ADDR(k_100f)));
	mulf(ADDR(g_headTargetKeepTime), &head->targetKeepTime, k_1000f);
	copyf(ADDR(g_headWeight), &head->weight);
	const ChestType *chest = &st->chestTypes[record->parts[1]];   /* chest */
	panel_name(OBJ(g_chestPanelName), chest->name);
	copyf(ADDR(g_chestWeightLimit), &chest->weightLimit);
	g_chestMaxArmor = chest->maxArmor;
	g_chestMaxShield = chest->maxShield;
	const ArmType *arm = &st->armTypes[record->parts[2]];   /* arm */
	panel_name(OBJ(g_armPanelName), arm->name);
	for (int i = 0; i < 5; i++)
		g_armsStats[i] = arm->stats[i];
	copyf(ADDR(g_armsWeight), &arm->weight);
	const LegType *leg = &st->legTypes[record->parts[3]];   /* leg */
	panel_name(OBJ(g_legPanelName), leg->name);
	copyf(OBJ(g_legsStats), &leg->agility);
	copyf(ADDR_AT(g_legsStats, 1), &leg->inertia);
	mulf(ADDR(g_legsSpeedCorrection), &leg->speedCorrection, AP(const float, ADDR(k_100f)));
	mulf(ADDR_AT(g_legsStats, 3), &leg->forwardBoostCorrection, AP(const float, ADDR(k_100f)));
	mulf(ADDR_AT(g_legsStats, 4), &leg->sideBoostCorrection, AP(const float, ADDR(k_100f)));
	mulf(ADDR_AT(g_legsStats, 5), &leg->backBoostCorrection, AP(const float, ADDR(k_100f)));
	copyf(ADDR(g_legsWeight), &leg->weight);
	int boosterIndex = record->parts[4];
	const BoosterType *booster = &st->boosterTypes[boosterIndex];
	panel_name(OBJ(g_boosterPanelName), booster->name);
	g_boosterThrustType = booster->thrustType;
	for (int i = 0; i < 3; i++)
		mulf(ADDR(g_boosterActiveTime) + i * 4, &booster->times[i], k_1000f);
	for (int i = 0; i < 4; i++)
		mulf(ADDR(g_boosterNormalSpeed) + i * 4, &booster->speeds[i], k_0_036f);
	(*(u32 *)&g_unusedArmcViewCountdown) = 0x3f800000;
	copyf(ADDR(g_boosterWeight), &booster->weight);
	return boosterIndex;
}

/* 0x40f340: mech part `part` (0 .. 4: head, chest, arm, leg, booster) stepped through its list, back (dir 1) or on
   (wrapping at both ends): its cursor, the list's count and entries, the chosen part (OBJ(g_armcParts) + 4 * part), and
   the mech marked changed (g_mechChanged). Returns what the original leaves in eax: the new part on the even steps back
   and odd steps on, else the cursor (another part: the part number) */
u32 (armc_stepPart)(u32 part, int dir)
{
	static const struct { u32 cursor, count, list; } parts[5] = {
		{ ADDR(g_headCursor), ADDR(g_headCount), OBJ(g_headList) }, { ADDR(g_chestCursor), ADDR(g_chestCount), OBJ(g_chestList) }, { ADDR(g_armCursor), ADDR(g_armCount), OBJ(g_armList) },
		{ ADDR(g_legCursor), ADDR(g_legCount), OBJ(g_legList) }, { ADDR(g_boosterCursor), ADDR(g_boosterCount), OBJ(g_boosterList) } };
	g_mechChanged = 1;
	if (part > 4)
		return part;
	int *cursor = AP(int, RELOC(parts[part].cursor)), count = GAME_VAR(int, parts[part].count);
	if (dir == 1) {
		if (--*cursor < 0)
			*cursor = count - 1;
	} else if (++*cursor >= count)
		*cursor = 0;
	u32 chosen = (AP(const u32, RELOC(parts[part].list)))[*cursor];
	(*(u32 *)&g_armcParts[part]) = chosen;
	return (part & 1) == (dir == 1 ? 0u : 1u) ? chosen : (u32)*cursor;
}

/* ---- the unlocked part lists ---- */

/* one level's entry (0x28 bytes) of an unlock table: a count and up to nine part numbers */
typedef struct { int count; int parts[9]; } Unlock;

/* the level's parts appended to the list at list (its length at *len); dword by dword, as rep movsd copies */
static int append_parts(const Unlock *entry, u32 list, int len)
{
	int n = entry->count;
	if ((int)((u32)n + 1) <= 1)   /* none (the original's test: n + 1 > 1, wrapping) */
		return len;
	for (int i = 0; i < n; i++)
		(AP(int, RELOC(list)))[len + i] = entry->parts[i];
	return len + n;
}

/* the unlocked level: opened from the Ladder game room (g_armcFrom 3) the player's level (g_pilotLevel) less one;
   else the progress (0x9f181c) as the exe's patch reads it (its helper at 0xb68e80): up to 14 as it is, 15 becomes
   14, 16 and above 15. (The original's check after it, 0x7f and above becoming 14, can no longer be met.) */
static int unlocked_level(int fromRoom)
{
	if (fromRoom)
		return g_pilotLevel - 1;
	int level = g_progress;
	if (level >= 15)
		level = level < 16 ? 14 : 15;
	if (level >= 0x7f)
		level = 14;
	return level;
}

/* 0x40da40: the unlocked part lists up to a level (g_unlockedLevel, also g_armcLevel): for each level up to it, of the table
   set (opened from the Ladder game room, g_armcFrom 3: g_unlockTablesLadder; else, the arena's network play included,
   g_unlockTablesByProgress; seven tables 0x320 bytes apart, an Unlock a level), the first five
   tables' parts appended to the five part lists (g_headList / g_chestList / g_armList / g_legList / g_boosterList, lengths
   g_headCount / g_chestCount / g_armCount / g_legCount / g_boosterCount), the last two's to the two lists that start with -1
   (g_weaponListTable / g_extraListTable, lengths g_weaponCount / g_extraCount). The lengths are read from memory at each step as the
   original does (a list long enough to run over them would change them); the caller ignores the eax it leaves */
void (armc_buildPartLists)(void)
{
	int fromRoom = g_armcFrom == 3;
	int level = unlocked_level(fromRoom);
	g_armcLevel = level;
	g_unlockedLevel = level;
	static const u32 lists[5] = { OBJ(g_headList), OBJ(g_chestList), OBJ(g_armList), OBJ(g_legList), OBJ(g_boosterList) };
	static const u32 lengths[5] = { ADDR(g_headCount), ADDR(g_chestCount), ADDR(g_armCount), ADDR(g_legCount), ADDR(g_boosterCount) };
	for (int k = 0; k < 5; k++)
		GAME_VAR(int, lengths[k]) = 0;
	u32 tables = fromRoom ? OBJ(g_unlockTablesLadder) : OBJ(g_unlockTablesByProgress);
#define TABLE(k, lv) (AP(const Unlock, RELOC(tables)) + (k) * 20 + (lv))   /* (20 levels a part kind) */
	if (level >= 0) {
		int last = 0;   /* the fifth list's length: the original keeps it in a register until the end */
		for (int lv = 0; lv <= level; lv++) {
			for (int k = 0; k < 4; k++)
				GAME_VAR(int, lengths[k]) = append_parts(TABLE(k, lv), lists[k], GAME_VAR(int, lengths[k]));
			last = append_parts(TABLE(4, lv), lists[4], last);
		}
		g_boosterCount = last;
	}
	/* the two lists that start with -1; their lengths too stored once at the end */
	static const u32 extra[2] = { OBJ(g_weaponListTable), OBJ(g_extraListTable) };
	static const u32 extra_len[2] = { ADDR(g_weaponCount), ADDR(g_extraCount) };
	for (int j = 0; j < 2; j++) {
		GAME_VAR(int, extra[j]) = -1;
		GAME_VAR(int, extra_len[j]) = 1;
		int top = g_unlockedLevel, len = 1;
		if (top < 0)
			continue;
		for (int lv = 0; lv <= top; lv++)
			len = append_parts(TABLE(5 + j, lv), extra[j], len);
		GAME_VAR(int, extra_len[j]) = len;
	}
#undef TABLE
}
