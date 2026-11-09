/* fixes/kyrie.c (native build, AXIS_NATIVE): the KYRIE parts, a second SERAPHIM set in ARM CENTER wearing the
   unused marked textures (Shape\Geolite\MARK\KYRIE-*, gold markings), unlocked with SERAPHIM after the last mission.
   Ported from the patch layer (axisnet_recomp.c: mk_catalog, mk_find, mk_retex, mk_altmask), which wrapped four of
   the game's calls; here the functions that make those calls use the fixes below.
   Each part is a copy of the SERAPHIM record, added to the catalogue once it is loaded, named "KYRIE\<slot>" (the
   textures' name; ARM CENTER shows KYRIE-HEAD ...) with its model names prefixed "MARKED\". The Shape.dat lookup drops
   the prefix, so the same model loads under its own cache name, and right after it is read its parts' textures
   "Shape\Geolite\..." become "Shape\Geolite\MARK\...". The marked textures have no _COLOR mask, and a missing mask is
   filled solid red (all primary colour), so the mask lookup falls back to the original's, which is blank and the same
   size: the KYRIE parts take no part colours, like SERAPHIM. */
#ifdef AXIS_NATIVE
#include "../game.h"
#include "fixes.h"
#include <string.h>

#define MARKED "MARKED\\"

/* the five part slots: the catalogue's records and count, a record's size, its model names (two sets: the models
   and the low-detail ones, 0x44 apart), the SERAPHIM part's number, the slot's unlock table */
static const struct {
	const char *slot;
	u32 types, count, size, shapeNames, nameCount, seraphim;
} k_slots[5] = {
	{ "HEAD", offsetof(Stage, headTypes), offsetof(Stage, headTypeCount), sizeof(HeadType), offsetof(HeadType, shapeNames), 8, 19 },
	{ "CHEST", offsetof(Stage, chestTypes), offsetof(Stage, chestTypeCount), sizeof(ChestType), offsetof(ChestType, shapeNames), 8, 13 },
	{ "ARM", offsetof(Stage, armTypes), offsetof(Stage, armTypeCount), sizeof(ArmType), offsetof(ArmType, shapeNames), 16, 17 },
	{ "LEG", offsetof(Stage, legTypes), offsetof(Stage, legTypeCount), sizeof(LegType), offsetof(LegType, shapeNames), 16, 19 },
	{ "BOOSTER", offsetof(Stage, boosterTypes), offsetof(Stage, boosterTypeCount), sizeof(BoosterType), offsetof(BoosterType, shapeNames), 20, 15 },
};

static int same_prefix(const char *s, const char *prefix)   /* (case ignored) */
{
	for (; *prefix; s++, prefix++) {
		char a = *s, b = *prefix;
		if (a >= 'a' && a <= 'z') a -= 0x20;
		if (b >= 'a' && b <= 'z') b -= 0x20;
		if (a != b)
			return 0;
	}
	return 1;
}

static void add_kyrie(u8 *stage)
{
	for (int k = 0; k < 5; k++) {
		int *count = (int *)(stage + k_slots[k].count), n = *count;
		u32 size = k_slots[k].size;
		u8 *seraphim = stage + k_slots[k].types + k_slots[k].seraphim * size, *kyrie = stage + k_slots[k].types + n * size;
		char want[64];
		strcpy(want, "SERAPHIM\\");
		strcat(want, k_slots[k].slot);
		if (n != (int)k_slots[k].seraphim + 1 || strcmp((const char *)seraphim, want))   /* not the stock catalogue */
			continue;
		memcpy(kyrie, seraphim, size);
		memset(kyrie, 0, 0x40);
		strcpy((char *)kyrie, "KYRIE\\");
		strcat((char *)kyrie, k_slots[k].slot);
		for (u32 i = 0; i < k_slots[k].nameCount * 2; i++) {   /* the models, then the low-detail ones */
			char *name = (char *)kyrie + k_slots[k].shapeNames + i * 0x44;
			size_t len = strlen(name);
			if (!len || !strcmp(name, ".") || len + 7 >= 0x40)
				continue;
			memmove(name + 7, name, len + 1);
			memcpy(name, MARKED, 7);
		}
		*count = n + 1;
		int *level15 = (int *)(g_unlockTablesByProgress + k * 0x320 + 15 * 0x28);   /* level 15 (after the last mission): count, parts */
		if (level15[0] == 1 && level15[1] == (int)k_slots[k].seraphim) {
			level15[2] = n;
			level15[0] = 2;
		}
	}
}

/* catalogue_loadComponents, then the KYRIE parts */
int fix_catalogueLoad(void *stage, const char *path)
{
	int r = ((int (THISCALL *)(void *, const char *))(void *)FN_catalogue_loadComponents)(stage, path);
	add_kyrie((u8 *)stage);
	return r;
}

/* a Shape.dat entry by name (shapeDat_getItemFileBy), the MARKED\ prefix dropped; the next shape read takes it */
static int g_markedPending;

void *fix_shapeFind(const char *name)
{
	g_markedPending = same_prefix(name, MARKED);
	return ((void *(CDECL *)(const char *))(void *)FN_shapeDat_getItemFileBy)(g_markedPending ? name + 7 : name);
}

/* shape_read, then (for a marked model) its parts' textures moved to Shape\Geolite\MARK\ */
void fix_shapeRead(void *shape, void *file, void *at, int room)
{
	((void (THISCALL *)(void *, void *, void *, int))(void *)FN_shape_read)(shape, file, at, room);
	if (!g_markedPending)
		return;
	g_markedPending = 0;
	Shape *model = (Shape *)shape;
	for (int i = 0; i < model->partCount; i++) {
		char *tex = (AP(ShapePart, model->parts))[i].texName;
		size_t len = strlen(tex);
		if (!same_prefix(tex, "SHAPE\\GEOLITE\\") || same_prefix(tex + 14, "MARK") || len + 5 >= 0x40)
			continue;
		memmove(tex + 19, tex + 14, len - 14 + 1);
		memcpy(tex + 14, "MARK\\", 5);
	}
}

/* a texture's colour mask by name (tex_findByName); a marked texture's falls back to the original's
   (MARK\KYRIE-x_COLOR -> KYRIE-x_COLOR, in the caller's buffer: the mask reader looks the name up again) */
int fix_maskFind(void *manager, char *name)
{
	int r = ((int (THISCALL *)(void *, const char *))(void *)FN_tex_findByName)(manager, name);
	if (r >= 0)
		return r;
	size_t len = strlen(name);
	if (!same_prefix(name, "SHAPE\\GEOLITE\\MARK\\") || len < 6 || !same_prefix(name + len - 6, "_COLOR"))
		return -1;
	memmove(name + 14, name + 19, len - 19 + 1);
	return ((int (THISCALL *)(void *, const char *))(void *)FN_tex_findByName)(manager, name);
}
#endif
