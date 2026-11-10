/* plat/posix/files.c: files for Linux, macOS and the like (portable build only; not built on Windows).
   The game names its files the Windows way: backslashes, and names whose case need not match the disk's
   ("Iftex/Cylinder" for iftex/cylinder.ptx). plat_path turns such a name into the file that is there: '\' becomes
   '/', and each part of the path is looked up without regard to case when it is not there as written (a part not
   found at all is kept as written, for files about to be made). On top of it:
   - plat.h's files: a file opened for reading, read and closed (the sounds' WAVs), deleted, the current directory;
   - the C runtime's path functions for a POSIX binding of the game's runtime entries: plat_fopen, plat_mkdir,
     plat_chdir, and Windows' directory listing (_findfirst / _findnext / _findclose: wildcards matched without
     regard to case, "." and ".." included, the names in the order NTFS lists them - sorted, case ignored - and
     VC6's 32-bit _finddata_t);
   - the user folder: the game writes its saves, settings, replays and caches into its own folder, which on Linux and
     macOS is often not writable (a package, Steam). So every file the game writes goes to a user folder instead -
     $AXIS_USER_DIR, else $XDG_DATA_HOME/axis or ~/.local/share/axis (macOS: ~/Library/Application Support/Axis);
     AXIS_USER_DIR=- writes the game folder as before - laid over the game folder: a file is read from the user
     folder when it is there, else from the game folder; one written goes to the user folder (one changed in place -
     "r+", "a" - copied there first); one deleted from the game folder is only marked so (.axis-deleted in the user
     folder); a folder's listing shows both. The game folder itself is never written. The game's current directory
     (chdir "save") is kept here, not in the process, so a folder that is only in the user folder can be entered. */
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

/* ---- the user folder laid over the game folder ---- */
static int g_ovInit;
static char g_root[PATH_ROOM];   /* the game folder (the process's directory at the first file call) */
static char g_user[PATH_ROOM];   /* the user folder; "" when the game folder itself is written */
static char g_cwd[PATH_ROOM];    /* the game's current directory under the game folder ("" or e.g. "save") */
static char **g_gone;            /* the game folder's files deleted (their places, lower case) */
static int g_goneCount;

static int is_dir(const char *p) { struct stat st; return stat(p, &st) == 0 && S_ISDIR(st.st_mode); }
static void make_dirs(const char *path)   /* (mkdir -p) */
{
	char p[PATH_ROOM];
	snprintf(p, sizeof p, "%s", path);
	for (char *c = p + 1; *c; c++)
		if (*c == '/') {
			*c = 0;
			mkdir(p, 0777);
			*c = '/';
		}
	mkdir(p, 0777);
}
static void lower(char *s) { for (; *s; s++) *s = (char)tolower((unsigned char)*s); }
static int gone_at(const char *rel)
{
	char l[PATH_ROOM];
	snprintf(l, sizeof l, "%s", rel);
	lower(l);
	for (int i = 0; i < g_goneCount; i++)
		if (!strcmp(g_gone[i], l))
			return i;
	return -1;
}
static void gone_add(const char *rel)
{
	char **more = realloc(g_gone, (g_goneCount + 1) * sizeof *more);
	if (!more)
		return;
	g_gone = more;
	g_gone[g_goneCount] = strdup(rel);
	if (g_gone[g_goneCount])
		lower(g_gone[g_goneCount++]);
}
static void gone_set(const char *rel, int on)
{
	int i = gone_at(rel);
	if (on && i < 0)
		gone_add(rel);
	else if (!on && i >= 0) {
		free(g_gone[i]);
		g_gone[i] = g_gone[--g_goneCount];
	} else
		return;
	char p[PATH_ROOM + 32];
	snprintf(p, sizeof p, "%s/.axis-deleted", g_user);
	FILE *f = fopen(p, "w");
	if (!f)
		return;
	for (int k = 0; k < g_goneCount; k++)
		fprintf(f, "%s\n", g_gone[k]);
	fclose(f);
}

void plat_userReset(void)   /* (the tests: the folders taken again from the environment and the process) */
{
	for (int i = 0; i < g_goneCount; i++)
		free(g_gone[i]);
	free(g_gone);
	g_gone = NULL;
	g_goneCount = 0;
	g_ovInit = 0;
	g_cwd[0] = 0;
}
static void ov_init(void)
{
	if (g_ovInit)
		return;
	g_ovInit = 1;
	if (!getcwd(g_root, sizeof g_root))
		strcpy(g_root, ".");
	const char *e = getenv("AXIS_USER_DIR"), *home = getenv("HOME");
	if (e && !strcmp(e, "-"))
		g_user[0] = 0;
	else if (e && *e)
		snprintf(g_user, sizeof g_user, "%s", e);
	else {
#ifdef __APPLE__
		snprintf(g_user, sizeof g_user, "%s/Library/Application Support/Axis", home ? home : ".");
#else
		const char *x = getenv("XDG_DATA_HOME");
		if (x && *x)
			snprintf(g_user, sizeof g_user, "%s/axis", x);
		else
			snprintf(g_user, sizeof g_user, "%s/.local/share/axis", home ? home : ".");
#endif
	}
	size_t n = strlen(g_user);
	while (n > 1 && g_user[n - 1] == '/')
		g_user[--n] = 0;
	if (!g_user[0])
		return;
	make_dirs(g_user);
	char p[PATH_ROOM + 32], line[PATH_ROOM];
	snprintf(p, sizeof p, "%s/.axis-deleted", g_user);
	FILE *f = fopen(p, "r");
	if (!f)
		return;
	while (fgets(line, sizeof line, f)) {
		line[strcspn(line, "\r\n")] = 0;
		if (line[0] && gone_at(line) < 0)
			gone_add(line);
	}
	fclose(f);
}
static int ov_on(void) { ov_init(); return g_user[0] != 0; }
/* the user folder ("" when the game folder is written): the loader's log goes there too */
const char *plat_userDir(void) { ov_init(); return g_user; }

/* the game's name -> its place under the game folder, '/'-separated, "." and ".." resolved, the game's spelling
   ("save/Alex.axs"; "" the game folder); 0 when it lies outside the game folder (rel: the name, absolute, then) */
static int ov_rel(const char *in, char *rel, size_t room)
{
	char norm[PATH_ROOM * 2];
	size_t n = 0;
	int abs = in[0] == '/' || in[0] == '\\';
	if (!abs && g_cwd[0])
		n = (size_t)snprintf(norm, sizeof norm, "%s/", g_cwd);
	for (const char *p = in; *p && n + 1 < sizeof norm; p++)
		norm[n++] = *p == '\\' ? '/' : *p;
	norm[n] = 0;
	const char *s = norm;
	size_t rl = strlen(g_root);
	if (abs && (strncasecmp(norm, g_root, rl) || (norm[rl] && norm[rl] != '/'))) {
		/* (another name for the same place - macOS's /tmp is /private/tmp: the longest part that exists resolved
		   through its links, the rest kept) */
		char canon[PATH_ROOM * 2], head[PATH_ROOM * 2];
		snprintf(head, sizeof head, "%s", norm);
		while (!realpath(head, canon)) {   /* (head: ever shorter prefixes of norm) */
			char *sl = strrchr(head, '/');
			if (!sl || sl == head) {
				canon[0] = 0;
				break;
			}
			*sl = 0;
		}
		if (canon[0]) {   /* (then the rest of norm, after the prefix that exists) */
			size_t c = strlen(canon);
			snprintf(canon + c, sizeof canon - c, "%s", norm + strlen(head));
		}
		if (!canon[0] || strncasecmp(canon, g_root, rl) || (canon[rl] && canon[rl] != '/')) {
			snprintf(rel, room, "%s", norm);
			return 0;
		}
		snprintf(norm, sizeof norm, "%s", canon);
	}
	if (abs)
		s = norm + rl;
	char out[PATH_ROOM] = "";
	size_t o = 0;
	while (*s) {
		while (*s == '/')
			s++;
		const char *e = strchr(s, '/');
		size_t len = e ? (size_t)(e - s) : strlen(s);
		if (!len)
			break;
		if (len == 2 && s[0] == '.' && s[1] == '.') {
			if (!o) {   /* (above the game folder) */
				snprintf(rel, room, "%s/%s", g_root, norm);
				return 0;
			}
			while (o && out[o - 1] != '/')
				o--;
			if (o)
				o--;
			out[o] = 0;
		} else if (!(len == 1 && s[0] == '.') && o + len + 2 < sizeof out) {
			if (o)
				out[o++] = '/';
			memcpy(out + o, s, len);
			o += len;
			out[o] = 0;
		}
		s += len;
	}
	snprintf(rel, room, "%s", out);
	return 1;
}
/* a place under a folder as the disk has it (plat_path: case ignored); 1 when it is there */
static int layer(const char *base, const char *rel, char *out, size_t room)
{
	char p[PATH_ROOM * 2];
	snprintf(p, sizeof p, rel[0] ? "%s/%s" : "%s", base, rel);
	return plat_path(p, out, room);
}
/* a game name's file: 1 in the user folder, 2 in the game folder, 0 in neither (out: where it would go in the user
   folder), -1 outside the game folder (out: the file itself). relOut (PATH_ROOM): its place under the game folder */
static int ov_find(const char *in, char *out, size_t room, char *relOut)
{
	char rel[PATH_ROOM], u[PATH_ROOM];
	if (!ov_rel(in, rel, sizeof rel)) {
		if (relOut)
			relOut[0] = 0;
		plat_path(rel, out, room);
		return -1;
	}
	if (relOut)
		snprintf(relOut, PATH_ROOM, "%s", rel);
	if (layer(g_user, rel, u, sizeof u)) {
		snprintf(out, room, "%s", u);
		return 1;
	}
	if (gone_at(rel) < 0 && layer(g_root, rel, out, room))
		return 2;
	snprintf(out, room, "%s", u);
	return 0;
}
static void copy_file(const char *from, const char *to)
{
	FILE *a = fopen(from, "rb"), *b = a ? fopen(to, "wb") : NULL;
	char buf[65536];
	size_t n;
	while (b && (n = fread(buf, 1, sizeof buf, a)) > 0)
		fwrite(buf, 1, n, b);
	if (a)
		fclose(a);
	if (b)
		fclose(b);
}
/* a file about to be written: its place in the user folder - its folders made, and with copy the game folder's
   file copied there first when there is one */
static void ov_writable(const char *in, int copy, char *out, size_t room)
{
	char rel[PATH_ROOM], at[PATH_ROOM], u[PATH_ROOM];
	int where = ov_find(in, at, sizeof at, rel);
	if (where == -1 || where == 1) {
		snprintf(out, room, "%s", at);
		return;
	}
	layer(g_user, rel, u, sizeof u);
	char dir[PATH_ROOM];
	snprintf(dir, sizeof dir, "%s", u);
	char *slash = strrchr(dir, '/');
	if (slash) {
		*slash = 0;
		make_dirs(dir);
	}
	if (where == 2 && copy)
		copy_file(at, u);
	gone_set(rel, 0);
	snprintf(out, room, "%s", u);
}

/* ---- plat.h's files ---- */
void *plat_fileOpenRead(const char *path)
{
	char p[PATH_ROOM];
	if (ov_on())
		ov_find(path, p, sizeof p, NULL);
	else
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
	if (ov_on()) {   /* (the user folder's copy removed; the game folder's only marked deleted) */
		char rel[PATH_ROOM], g[PATH_ROOM];
		int where = ov_find(path, p, sizeof p, rel), ok = 0;
		if (where == -1)
			return unlink(p) == 0;
		if (where == 1)
			ok = unlink(p) == 0;
		if (gone_at(rel) < 0 && layer(g_root, rel, g, sizeof g)) {
			gone_set(rel, 1);
			ok = 1;
		}
		return (uint32_t)ok;
	}
	if (!plat_path(path, p, sizeof p))
		return 0;
	return unlink(p) == 0;
}
uint32_t plat_currentDirectory(uint32_t size, char *out)
{
	char p[PATH_ROOM];
	if (ov_on())
		snprintf(p, sizeof p, g_cwd[0] ? "%s/%s" : "%s", g_root, g_cwd);
	else if (!getcwd(p, sizeof p))
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
	if (ov_on()) {
		int write = strchr(mode, 'w') || strchr(mode, 'a') || strchr(mode, '+');
		int keep = strchr(mode, 'a') || (strchr(mode, '+') && !strchr(mode, 'w'));   /* (changed in place: copied first) */
		if (write)
			ov_writable(path, keep, p, sizeof p);
		else
			ov_find(path, p, sizeof p, NULL);
	} else
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
	if (ov_on()) {   /* (there in either folder: EEXIST, as Windows; else made in the user folder) */
		int where = ov_find(path, p, sizeof p, NULL);
		if (where == -1)
			return mkdir(p, 0777);
		if (where > 0) {
			errno = EEXIST;
			return -1;
		}
		make_dirs(p);
		return is_dir(p) ? 0 : -1;
	}
	plat_path(path, p, sizeof p);
	return mkdir(p, 0777);
}
int plat_chdir(const char *path)
{
	char p[PATH_ROOM];
	if (ov_on()) {   /* (the game's current directory kept here: a folder in either folder) */
		char rel[PATH_ROOM];
		int where = ov_find(path, p, sizeof p, rel);
		if (where <= 0 || !is_dir(p)) {
			char g[PATH_ROOM];
			if (where == -1 || !(layer(g_root, rel, g, sizeof g) && is_dir(g))) {
				errno = ENOENT;
				return -1;
			}
		}
		snprintf(g_cwd, sizeof g_cwd, "%s", rel);
		return 0;
	}
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
	char **names;
	char **paths;   /* (each name's file: the user folder's or the game folder's) */
	int count, next, room;
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

static int fill(Find *f, FindData *out)
{
	while (f->next < f->count) {
		const char *name = f->names[f->next], *path = f->paths[f->next];
		f->next++;
		struct stat st;
		if (stat(path, &st) != 0)
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
	for (int i = 0; i < f->count; i++) {
		free(f->names[i]);
		free(f->paths[i]);
	}
	free(f->names);
	free(f->paths);
	free(f);
}

/* a folder's matching names added - those already listed (the user folder's) kept, and with rel (the game folder's
   listing) the ones deleted left out */
static void list_dir(Find *f, const char *dir, const char *mask, const char *rel)
{
	DIR *d = opendir(dir);
	if (!d)
		return;
	struct dirent *de;
	while ((de = readdir(d))) {
		if (!wild(mask, de->d_name))
			continue;
		int dup = 0;
		for (int i = 0; i < f->count && !dup; i++)
			dup = !strcasecmp(f->names[i], de->d_name);
		if (dup)
			continue;
		if (rel && strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
			char r[PATH_ROOM * 2];
			snprintf(r, sizeof r, rel[0] ? "%s/%s" : "%s%s", rel, de->d_name);
			if (gone_at(r) >= 0)
				continue;
		}
		if (f->count == f->room) {
			int room = f->room ? f->room * 2 : 32;
			char **n = realloc(f->names, room * sizeof *n);
			if (!n)
				break;
			f->names = n;
			char **p = realloc(f->paths, room * sizeof *p);
			if (!p)
				break;
			f->paths = p;
			f->room = room;
		}
		char full[PATH_ROOM * 2];
		snprintf(full, sizeof full, "%s/%s", dir, de->d_name);
		f->names[f->count] = strdup(de->d_name);
		f->paths[f->count++] = strdup(full);
	}
	closedir(d);
}
/* the names sorted as NTFS lists them (case ignored), their paths with them */
static void sort_names(Find *f)
{
	for (int i = 1; i < f->count; i++)
		for (int j = i; j > 0 && strcasecmp(f->names[j - 1], f->names[j]) > 0; j--) {
			char *t = f->names[j];
			f->names[j] = f->names[j - 1];
			f->names[j - 1] = t;
			t = f->paths[j];
			f->paths[j] = f->paths[j - 1];
			f->paths[j - 1] = t;
		}
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
	char dirName[PATH_ROOM];
	if (slash) {
		*slash = 0;
		snprintf(dirName, sizeof dirName, "%s", p[0] ? p : "/");
	} else
		strcpy(dirName, ".");
	Find *f = calloc(1, sizeof *f);
	if (!f)
		return -1;
	char d1[PATH_ROOM], d2[PATH_ROOM], rel[PATH_ROOM];
	int any = 0;
	if (ov_on() && ov_rel(dirName, rel, sizeof rel)) {   /* (both folders' entries) */
		if (layer(g_user, rel, d1, sizeof d1) && is_dir(d1)) {
			list_dir(f, d1, mask, NULL);
			any = 1;
		}
		if (layer(g_root, rel, d2, sizeof d2) && is_dir(d2)) {
			list_dir(f, d2, mask, rel);
			any = 1;
		}
	} else {
		plat_path(ov_on() ? rel : dirName, d1, sizeof d1);
		if (is_dir(d1)) {
			list_dir(f, d1, mask, NULL);
			any = 1;
		}
	}
	sort_names(f);
	if (!any || fill(f, (FindData *)data) != 0) {
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
