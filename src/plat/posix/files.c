/* plat/posix/files.c: files for Linux, macOS and the like (portable build only; not built on Windows).
   The game names its files the Windows way: backslashes, and names whose case need not match the disk's
   ("Iftex/Cylinder" for iftex/cylinder.ptx). plat_path turns such a name into the file that is there: '\' becomes
   '/', and each part of the path is looked up without regard to case when it is not there as written (a part not
   found at all is kept as written, for files about to be made). On top of it:
   - plat.h's files: a file opened for reading, read and closed (the sounds' WAVs), deleted, the current directory;
   - the C runtime's path functions for a POSIX binding of the game's runtime entries: plat_fopen, plat_mkdir,
     plat_chdir, and Windows' directory listing (_findfirst / _findnext / _findclose: wildcards matched without
     regard to case, "." and ".." included, the names in the order NTFS lists them - sorted, case ignored - and
     VC6's 32-bit _finddata_t). */
#if defined(AXIS_PORTABLE) && !defined(_WIN32)
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH_ROOM 1024

/* in (the game's name) -> out (the disk's): 1 when the whole path exists, 0 when some part was not found (that part
   and those after it kept as written) */
int plat_path(const char *in, char *out, size_t room)
{
	char norm[PATH_ROOM];
	size_t n = 0;
	for (const char *p = in; *p && n + 1 < sizeof norm; p++) {
		char c = *p == '\\' ? '/' : *p;
		if (c == '/' && n && norm[n - 1] == '/')
			continue;   /* (doubled separators) */
		norm[n++] = c;
	}
	norm[n] = 0;
	char built[PATH_ROOM];
	size_t b = 0;
	const char *s = norm;
	if (*s == '/') {
		built[b++] = '/';
		s++;
	}
	built[b] = 0;
	int found = 1;
	while (*s) {
		const char *e = strchr(s, '/');
		size_t len = e ? (size_t)(e - s) : strlen(s);
		char part[256];
		if (len >= sizeof part)
			len = sizeof part - 1;
		memcpy(part, s, len);
		part[len] = 0;
		s += len + (e ? 1 : 0);
		if (b + len + 2 >= sizeof built)
			break;
		if (!strcmp(part, ".") || !strcmp(part, "..")) {
			memcpy(built + b, part, len + 1);
			b += len;
		} else {
			char want[PATH_ROOM];
			snprintf(want, sizeof want, "%s%s", built, part);
			struct stat st;
			if (found && stat(want, &st) != 0) {   /* not there as written: the same name in another case? */
				DIR *d = opendir(b ? built : ".");
				int hit = 0;
				if (d) {
					struct dirent *de;
					while ((de = readdir(d)))
						if (!strcasecmp(de->d_name, part)) {
							snprintf(part, sizeof part, "%s", de->d_name);
							hit = 1;
							break;
						}
					closedir(d);
				}
				if (!hit)
					found = 0;
			}
			memcpy(built + b, part, strlen(part) + 1);
			b += strlen(part);
		}
		if (*s || e) {
			built[b++] = '/';
			built[b] = 0;
		}
	}
	snprintf(out, room, "%s", built);
	return found;
}

/* ---- plat.h's files ---- */
void *plat_fileOpenRead(const char *path)
{
	char p[PATH_ROOM];
	plat_path(path, p, sizeof p);
	int fd = open(p, O_RDONLY);
	return fd < 0 ? (void *)(intptr_t)-1 : (void *)(intptr_t)fd;
}
int plat_fileRead(void *file, void *out, uint32_t size, uint32_t *done)
{
	uint32_t got = 0;
	while (got < size) {
		ssize_t r = read((int)(intptr_t)file, (char *)out + got, size - got);
		if (r < 0 && errno == EINTR)
			continue;
		if (r <= 0)
			break;
		got += (uint32_t)r;
	}
	if (done)
		*done = got;
	return 1;   /* (ReadFile succeeds at the end of the file too, with fewer bytes) */
}
int plat_fileClose(void *file) { return close((int)(intptr_t)file) == 0; }
uint32_t plat_fileDelete(const char *path)
{
	char p[PATH_ROOM];
	if (!plat_path(path, p, sizeof p))
		return 0;
	return unlink(p) == 0;
}
uint32_t plat_currentDirectory(uint32_t size, char *out)
{
	char p[PATH_ROOM];
	if (!getcwd(p, sizeof p))
		return 0;
	uint32_t n = (uint32_t)strlen(p);
	if (n + 1 > size)
		return n + 1;   /* (as Windows: the room needed) */
	memcpy(out, p, n + 1);
	return n;
}

/* ---- the C runtime's path functions ---- */
FILE *plat_fopen(const char *path, const char *mode)
{
	char p[PATH_ROOM], m[8];
	plat_path(path, p, sizeof p);
	size_t k = 0;
	for (const char *c = mode; *c && k + 1 < sizeof m; c++)
		if (*c != 't')   /* (text mode: Windows only; 'b' is accepted and ignored) */
			m[k++] = *c;
	m[k] = 0;
	return fopen(p, m);
}
int plat_mkdir(const char *path)
{
	char p[PATH_ROOM];
	plat_path(path, p, sizeof p);
	return mkdir(p, 0777);
}
int plat_chdir(const char *path)
{
	char p[PATH_ROOM];
	plat_path(path, p, sizeof p);
	return chdir(p);
}

/* VC6's _finddata_t (32-bit time_t and size) */
typedef struct {
	uint32_t attrib;
	int32_t timeCreate, timeAccess, timeWrite;
	uint32_t size;
	char name[260];
} FindData;

typedef struct {
	char dir[PATH_ROOM];
	char **names;
	int count, next;
} Find;

/* Windows' wildcards: '*' any run, '?' any one character; case ignored ("*.*" also matches names without a dot) */
static int wild(const char *p, const char *s)
{
	if (!strcmp(p, "*.*"))
		return 1;
	for (; *p; p++, s++) {
		if (*p == '*') {
			for (const char *t = s;; t++) {
				if (wild(p + 1, t))
					return 1;
				if (!*t)
					return 0;
			}
		}
		if (!*s)
			return 0;
		if (*p != '?' && tolower((unsigned char)*p) != tolower((unsigned char)*s))
			return 0;
	}
	return !*s;
}
static int by_name(const void *a, const void *b) { return strcasecmp(*(char *const *)a, *(char *const *)b); }

static int fill(Find *f, FindData *out)
{
	while (f->next < f->count) {
		const char *name = f->names[f->next++];
		char p[PATH_ROOM * 2];
		snprintf(p, sizeof p, "%s%s", f->dir, name);
		struct stat st;
		if (stat(p, &st) != 0)
			continue;
		memset(out, 0, sizeof *out);
		out->attrib = S_ISDIR(st.st_mode) ? 0x10 : 0x20;   /* _A_SUBDIR, else _A_ARCH as NTFS shows files */
		out->timeCreate = (int32_t)st.st_ctime;
		out->timeAccess = (int32_t)st.st_atime;
		out->timeWrite = (int32_t)st.st_mtime;
		out->size = (uint32_t)st.st_size;
		snprintf(out->name, sizeof out->name, "%s", name);
		return 0;
	}
	return -1;
}

static void find_free(Find *f)
{
	for (int i = 0; i < f->count; i++)
		free(f->names[i]);
	free(f->names);
	free(f);
}

intptr_t plat_findfirst(const char *pattern, void *data)
{
	char p[PATH_ROOM];
	snprintf(p, sizeof p, "%s", pattern);
	for (char *c = p; *c; c++)
		if (*c == '\\')
			*c = '/';
	char *slash = strrchr(p, '/');
	const char *mask = slash ? slash + 1 : p;
	Find *f = calloc(1, sizeof *f);
	if (!f)
		return -1;
	if (slash) {
		*slash = 0;
		plat_path(p, f->dir, sizeof f->dir - 1);
		strcat(f->dir, "/");
	}
	DIR *d = opendir(slash ? f->dir : ".");
	if (!d) {
		free(f);
		errno = ENOENT;
		return -1;
	}
	int room = 0;
	struct dirent *de;
	while ((de = readdir(d)))
		if (wild(mask, de->d_name)) {
			if (f->count == room) {
				room = room ? room * 2 : 32;
				char **more = realloc(f->names, room * sizeof *more);
				if (!more)
					break;
				f->names = more;
			}
			f->names[f->count++] = strdup(de->d_name);
		}
	closedir(d);
	qsort(f->names, f->count, sizeof *f->names, by_name);
	if (fill(f, (FindData *)data) != 0) {
		find_free(f);
		errno = ENOENT;
		return -1;
	}
	return (intptr_t)f;
}
int plat_findnext(intptr_t handle, void *data)
{
	if (handle == -1)
		return -1;
	return fill((Find *)handle, (FindData *)data);
}
int plat_findclose(intptr_t handle)
{
	if (handle == -1)
		return -1;
	find_free((Find *)handle);
	return 0;
}
#endif
