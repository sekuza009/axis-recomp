/* plat/win32/registry.c: plat.h's settings for Windows (portable build only): the registry itself, as the original
   uses it (plat.h's master definitions, expanded here, through the game's import slots) - the launcher and DServer
   read and write the same keys. */
#include "../../game.h"
#ifdef AXIS_PORTABLE
#undef AXIS_PORTABLE   /* (plat.h's master definitions: the original's calls) */
#include "../plat.h"
#define AXIS_PORTABLE

int plat_regOpen(u32 root, const char *path, u32 *key) { return REG_OPEN(root, path, 0, 0xf003f, key); }
int plat_regCreate(u32 root, const char *path, u32 *key, u32 *disposition)
{
	return REG_CREATE(root, path, 0, NULL, 0, 0xf003f, NULL, key, disposition);
}
int plat_regQuery(u32 key, const char *name, u32 *type, void *data, u32 *size) { return REG_QUERY(key, name, 0, type, data, size); }
int plat_regSet(u32 key, const char *name, u32 type, const void *data, u32 size) { return REG_SET(key, name, 0, type, data, size); }
u32 plat_regClose(u32 key) { return REG_CLOSE(key); }
#endif
