/* plat/win32/files.c: plat.h's files for Windows (portable build only): each the call the original makes (plat.h's
   master definitions, expanded here, through the game's import slots). */
#include "../../game.h"
#ifdef AXIS_PORTABLE
#undef AXIS_PORTABLE   /* (plat.h's master definitions: the original's calls) */
#include "../plat.h"
#define AXIS_PORTABLE

void *plat_fileOpenRead(const char *path) { return FILE_OPEN_READ(path); }
int plat_fileRead(void *file, void *out, u32 size, u32 *done) { return FILE_READ(file, out, size, done); }
int plat_fileClose(void *file) { return FILE_CLOSE(file); }
u32 plat_fileDelete(const char *path) { return FILE_DELETE(path); }
u32 plat_currentDirectory(u32 size, char *out) { return FILE_CURRENT_DIRECTORY(size, out); }
#endif
