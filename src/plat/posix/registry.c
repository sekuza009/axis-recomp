/* plat/posix/registry.c: the game's registry settings for Linux, macOS and the like (portable build only; not built
   on Windows). The keys and values live in a text file - $AXIS_SETTINGS, else $XDG_CONFIG_HOME/axis/registry.txt,
   else ~/.config/axis/registry.txt - read at first use and written whenever a value is set or a key created:
       [80000001\SOFTWARE\AxisArena\Character]
       Name=1:41786973...     (the value's type, then its bytes in hex, exactly as written)
   The calls keep Windows' rules as the game relies on them: key and value names without regard to case, a failed
   open leaving *key as it was (2, ERROR_FILE_NOT_FOUND), a create telling a new key (1) from an existing one (2), a
   read of a missing value 2, of one larger than the room 234 (ERROR_MORE_DATA, the size needed given back), the
   bytes kept as written (a REG_SZ's padding too), closing an unknown handle 6 (ERROR_INVALID_HANDLE). */
#if defined(AXIS_PORTABLE) && !defined(_WIN32)
#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>

typedef struct { char name[128]; uint32_t type, size; unsigned char *data; } Value;
typedef struct { char path[256]; Value *values; int count; } Key;

static Key *g_keys;
static int g_keyCount, g_loaded;
static int g_open[64];   /* handle h (1..64) -> key index + 1 */

static const char *store_path(void)
{
	static char p[1024];
	const char *e = getenv("AXIS_SETTINGS");
	if (e && *e)
		return e;
	const char *x = getenv("XDG_CONFIG_HOME"), *home = getenv("HOME");
	if (x && *x)
		snprintf(p, sizeof p, "%s/axis/registry.txt", x);
	else
		snprintf(p, sizeof p, "%s/.config/axis/registry.txt", home ? home : ".");
	return p;
}

static Key *find_key(const char *path)
{
	for (int i = 0; i < g_keyCount; i++)
		if (!strcasecmp(g_keys[i].path, path))
			return &g_keys[i];
	return NULL;
}
static Key *add_key(const char *path)
{
	Key *more = realloc(g_keys, (g_keyCount + 1) * sizeof *g_keys);
	if (!more)
		return NULL;
	g_keys = more;
	Key *k = &g_keys[g_keyCount++];
	memset(k, 0, sizeof *k);
	snprintf(k->path, sizeof k->path, "%s", path);
	return k;
}
static Value *find_value(Key *k, const char *name)
{
	for (int i = 0; i < k->count; i++)
		if (!strcasecmp(k->values[i].name, name ? name : ""))
			return &k->values[i];
	return NULL;
}
static void set_value(Key *k, const char *name, uint32_t type, const void *data, uint32_t size)
{
	Value *v = find_value(k, name);
	if (!v) {
		Value *more = realloc(k->values, (k->count + 1) * sizeof *k->values);
		if (!more)
			return;
		k->values = more;
		v = &k->values[k->count++];
		memset(v, 0, sizeof *v);
		snprintf(v->name, sizeof v->name, "%s", name ? name : "");
	}
	free(v->data);
	v->data = malloc(size ? size : 1);
	if (v->data && size)
		memcpy(v->data, data, size);
	v->type = type;
	v->size = size;
}

static void load(void)
{
	if (g_loaded)
		return;
	g_loaded = 1;
	FILE *f = fopen(store_path(), "r");
	if (!f)
		return;
	char line[4096];
	Key *k = NULL;
	while (fgets(line, sizeof line, f)) {
		line[strcspn(line, "\r\n")] = 0;
		if (line[0] == '[') {
			char *e = strrchr(line, ']');
			if (e) {
				*e = 0;
				k = find_key(line + 1);
				if (!k)
					k = add_key(line + 1);
			}
			continue;
		}
		char *eq = strchr(line, '='), *colon = eq ? strchr(eq, ':') : NULL;
		if (!k || !eq || !colon)
			continue;
		*eq = 0;
		uint32_t type = (uint32_t)strtoul(eq + 1, NULL, 10);
		const char *hex = colon + 1;
		uint32_t size = (uint32_t)(strlen(hex) / 2);
		unsigned char *data = malloc(size ? size : 1);
		if (!data)
			continue;
		for (uint32_t i = 0; i < size; i++) {
			unsigned x;
			sscanf(hex + 2 * i, "%2x", &x);
			data[i] = (unsigned char)x;
		}
		set_value(k, line, type, data, size);
		free(data);
	}
	fclose(f);
}

static void make_dirs(const char *file)
{
	char d[1024];
	snprintf(d, sizeof d, "%s", file);
	for (char *p = d + 1; *p; p++)
		if (*p == '/') {
			*p = 0;
			mkdir(d, 0755);
			*p = '/';
		}
}
static void save(void)
{
	const char *p = store_path();
	char tmp[1100];
	snprintf(tmp, sizeof tmp, "%s.tmp", p);
	make_dirs(p);
	FILE *f = fopen(tmp, "w");
	if (!f)
		return;
	for (int i = 0; i < g_keyCount; i++) {
		fprintf(f, "[%s]\n", g_keys[i].path);
		for (int j = 0; j < g_keys[i].count; j++) {
			Value *v = &g_keys[i].values[j];
			fprintf(f, "%s=%u:", v->name, v->type);
			for (uint32_t b = 0; b < v->size; b++)
				fprintf(f, "%02x", v->data[b]);
			fputc('\n', f);
		}
	}
	if (fclose(f) == 0)
		rename(tmp, p);   /* (whole, or not at all) */
}

static void full_path(char *out, size_t room, uint32_t root, const char *path)
{
	snprintf(out, room, "%08x\\%s", root, path);
	for (char *c = out; *c; c++)
		if (*c == '/')
			*c = '\\';
}
static int new_handle(Key *k)
{
	for (int h = 0; h < 64; h++)
		if (!g_open[h]) {
			g_open[h] = (int)(k - g_keys) + 1;
			return h + 1;
		}
	return 0;
}
static Key *key_of(uint32_t h)
{
	if (h < 1 || h > 64 || !g_open[h - 1])
		return NULL;
	return &g_keys[g_open[h - 1] - 1];
}

int plat_regOpen(uint32_t root, const char *path, uint32_t *key)
{
	load();
	char full[300];
	full_path(full, sizeof full, root, path);
	Key *k = find_key(full);
	if (!k)
		return 2;   /* ERROR_FILE_NOT_FOUND; *key as it was */
	int h = new_handle(k);
	if (!h)
		return 8;   /* ERROR_NOT_ENOUGH_MEMORY */
	*key = (uint32_t)h;
	return 0;
}
int plat_regCreate(uint32_t root, const char *path, uint32_t *key, uint32_t *disposition)
{
	load();
	char full[300];
	full_path(full, sizeof full, root, path);
	Key *k = find_key(full);
	uint32_t how = 2;   /* REG_OPENED_EXISTING_KEY */
	if (!k) {
		k = add_key(full);
		if (!k)
			return 8;
		how = 1;   /* REG_CREATED_NEW_KEY */
		save();
	}
	int h = new_handle(k);
	if (!h)
		return 8;
	*key = (uint32_t)h;
	if (disposition)
		*disposition = how;
	return 0;
}
int plat_regQuery(uint32_t key, const char *name, uint32_t *type, void *data, uint32_t *size)
{
	Key *k = key_of(key);
	if (!k)
		return 6;   /* ERROR_INVALID_HANDLE */
	Value *v = find_value(k, name);
	if (!v)
		return 2;
	if (type)
		*type = v->type;
	if (!size)
		return data ? 87 : 0;   /* ERROR_INVALID_PARAMETER */
	if (data && *size < v->size) {
		*size = v->size;
		return 234;   /* ERROR_MORE_DATA */
	}
	if (data)
		memcpy(data, v->data, v->size);
	*size = v->size;
	return 0;
}
int plat_regSet(uint32_t key, const char *name, uint32_t type, const void *data, uint32_t size)
{
	Key *k = key_of(key);
	if (!k)
		return 6;
	set_value(k, name, type, data, size);
	save();
	return 0;
}
uint32_t plat_regClose(uint32_t key)
{
	if (!key_of(key))
		return 6;
	g_open[key - 1] = 0;
	return 0;
}
#endif
