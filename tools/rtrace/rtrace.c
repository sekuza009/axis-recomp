/* range trace sampler (test only): every 250 ms all leaves are read (the scene from a snapshot) and their
   statistics kept; every 5 s they are written to Axis\rtrace.tsv */
#include <windows.h>
#include <mmsystem.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "rtrace.h"

#define ND 16
typedef struct {
	unsigned long long n, nz;
	long long imin, imax;
	double fmin, fmax;
	unsigned nonfinite, denorm, floatlike, changes;
	unsigned long long vals[ND];
	int nd;              /* distinct values kept; ND + 1: more */
	unsigned pnull, pvalid, pimage, pbad;
	unsigned long long badptr;
	unsigned sn, snonterm, snonprint, sempty;
	char sample[48];
} St;
static St *g_st;
static int g_pass;

int rt_copy(const void *a, void *b, unsigned n)
{
	SIZE_T got = 0;
	return ReadProcessMemory(GetCurrentProcess(), a, b, n, &got) && got == n;
}

/* page committed and readable? (a small cache of pages, refreshed every 40 passes) */
static unsigned g_pc[8192], g_pcPass[8192];
static unsigned char g_pcOk[8192];
static int mapped(unsigned a)
{
	unsigned pg = a >> 12, h = (pg * 2654435761u) >> 19;
	if (g_pc[h] == pg && g_pcPass[h] + 40 > (unsigned)g_pass)
		return g_pcOk[h];
	MEMORY_BASIC_INFORMATION mi;
	int ok = VirtualQuery((void *)(uintptr_t)a, &mi, sizeof mi) == sizeof mi && mi.State == MEM_COMMIT &&
	         !(mi.Protect & (PAGE_NOACCESS | PAGE_GUARD));
	g_pc[h] = pg; g_pcPass[h] = g_pass; g_pcOk[h] = ok;
	return ok;
}

static void keep(St *s, unsigned long long v)
{
	if (s->nd > ND) return;
	for (int i = 0; i < s->nd; i++) if (s->vals[i] == v) return;
	if (s->nd == ND) { s->nd++; return; }
	s->vals[s->nd++] = v;
}

void rt_O(int id, const rt_u8 *p, int n, int esz)
{
	St *s = &g_st[id];
	char k = rt_leaves[id].kind;
	for (int i = 0; i < n; i++, p += esz) {
		long long v; double f = 0; unsigned long long raw = 0;
		switch (esz) {
		case 1: raw = *p; v = k == 'b' ? (signed char)*p : *p; break;
		case 2: raw = *(const unsigned short *)p; v = k == 'h' ? *(const short *)p : *(const unsigned short *)p; break;
		case 8: raw = *(const unsigned long long *)p; v = (long long)raw; if (k == 'd') f = *(const double *)p; break;
		default: raw = *(const unsigned *)p; v = k == 'u' || k == 'p' ? (long long)(unsigned)raw : (long long)(int)raw; break;
		}
		s->n++;
		if (!raw) { keep(s, 0); continue; }
		s->nz++;
		keep(s, raw);
		if (k == 'f' || k == 'd') {
			if (k == 'f') {
				unsigned b = (unsigned)raw;
				if ((b & 0x7f800000) == 0x7f800000) { s->nonfinite++; continue; }
				if (!(b & 0x7f800000) && (b & 0x7fffffff)) s->denorm++;   /* (not -0.0) */
				f = *(const float *)p;
			}
			if (!isfinite(f)) { s->nonfinite++; continue; }
			if (s->nz == 1 || f < s->fmin) s->fmin = f;
			if (s->nz == 1 || f > s->fmax) s->fmax = f;
			continue;
		}
		if (k == 'p') {
			unsigned a = (unsigned)raw;
			if (a - 0x400000u < 0x76b000u) s->pimage++;
			else if (mapped(a)) s->pvalid++;
			else { s->pbad++; s->badptr = a; }
			continue;
		}
		if (s->nz == 1 || v < s->imin) s->imin = v;
		if (s->nz == 1 || v > s->imax) s->imax = v;
		if (esz == 4) {
			unsigned b = (unsigned)raw & 0x7fffffffu, e = b >> 23;
			if (e >= 0x66 && e <= 0x98 && b >= 0x01000000u) s->floatlike++;
		}
	}
}

void rt_S(int id, const rt_u8 *p, int n, int slen)
{
	St *s = &g_st[id];
	for (int i = 0; i < n; i++, p += slen) {
		s->sn++;
		const rt_u8 *z = memchr(p, 0, slen);
		int len = z ? (int)(z - p) : slen;
		if (!z) s->snonterm++;
		if (!len) { s->sempty++; continue; }
		for (int j = 0; j < len; j++)
			if (p[j] < 0x20 && p[j] != '\n' && p[j] != '\r' && p[j] != '\t') { s->snonprint++; break; }
		if (!s->sample[0] || (len > 1 && !(g_pass % 37))) {
			int c = len < 47 ? len : 47;
			for (int j = 0; j < c; j++) s->sample[j] = p[j] >= 0x20 && p[j] < 0x7f ? p[j] : '.';
			s->sample[c] = 0;
		}
	}
}

static rt_u8 *g_snap;
static unsigned g_snapSize;
static const rt_u8 *g_seen[16];
static int g_nseen;
void rt_root(const rt_u8 *p, int type, unsigned size)
{
	if (!p) return;
	for (int i = 0; i < g_nseen; i++) if (g_seen[i] == p) return;
	if (g_nseen < 16) g_seen[g_nseen++] = p;
	if (size > g_snapSize) { free(g_snap); g_snap = malloc(size); g_snapSize = g_snap ? size : 0; }
	if (!g_snap || !rt_copy(p, g_snap, size)) return;
	if (!strcmp(rt_structNames[type], "Scene")) rt_walk_scene(g_snap);
	else rt_walk_any(type, g_snap);
}

/* a pointer to a record of known type: copied (its own buffer) and walked; two levels deep at most, each record
   once a pass, nothing over 4 MB */
static unsigned g_visit[8192], g_visitPass[8192];
static int g_depth;
void rt_follow(unsigned ptr, int type, unsigned size)
{
	if (!ptr || ptr - 0x400000u < 0x76b000u || g_depth >= 4 || size > (4u << 20))
		return;
	unsigned h = (ptr * 2654435761u) >> 19;
	for (int k = 0; k < 8; k++, h = (h + 1) & 8191) {
		if (g_visitPass[h] == (unsigned)g_pass && g_visit[h] == ptr) return;
		if (g_visitPass[h] != (unsigned)g_pass) { g_visitPass[h] = g_pass; g_visit[h] = ptr; break; }
	}
	rt_u8 *buf = malloc(size);
	if (!buf) return;
	if (rt_copy((const void *)(uintptr_t)ptr, buf, size)) {
		g_depth++;
		rt_walk_any(type, buf);
		g_depth--;
	}
	free(buf);
}

/* count records of size bytes at ptr (a pointer whose length is another field: Shape.parts, the space's pools ..),
   at most cap of them, each walked */
void rt_follow_n(unsigned ptr, int count, int cap, int type, unsigned size)
{
	if (count <= 0 || !ptr || ptr - 0x400000u < 0x76b000u || g_depth >= 4)
		return;
	unsigned n = count < cap ? (unsigned)count : (unsigned)cap;
	if (n * size > (4u << 20))
		n = (4u << 20) / size;
	unsigned h = (ptr * 2654435761u) >> 19;
	for (int k = 0; k < 8; k++, h = (h + 1) & 8191) {
		if (g_visitPass[h] == (unsigned)g_pass && g_visit[h] == ptr) return;
		if (g_visitPass[h] != (unsigned)g_pass) { g_visitPass[h] = g_pass; g_visit[h] = ptr; break; }
	}
	rt_u8 *buf = malloc(n * size);
	if (!buf) return;
	if (rt_copy((const void *)(uintptr_t)ptr, buf, n * size)) {
		g_depth++;
		for (unsigned i = 0; i < n; i++)
			rt_walk_any(type, buf + i * size);
		g_depth--;
	}
	free(buf);
}

/* the fast pass: Scene's small fields (input flags and the like live one frame) */
extern const int rt_sceneFast[][4];
extern const int rt_sceneFastCount;
static void fast_pass(void)
{
	const rt_u8 *sc = rt_scene();
	if (!sc) return;
	rt_u8 buf[64];
	extern const int rt_playerFast[][4], rt_playerFastCount, rt_localPlayerAt, rt_playersAt, rt_playerSize;
	int local = -1;
	if (rt_copy(sc + rt_localPlayerAt, &local, 4) && local >= 0 && local < 16) {
		const rt_u8 *pl = sc + rt_playersAt + local * rt_playerSize;
		for (int i = 0; i < rt_playerFastCount; i++) {
			const int *f = rt_playerFast[i];
			if (rt_copy(pl + f[1], buf, f[2] * f[3]))
				rt_O(f[0], buf, f[2], f[3]);
		}
	}
	for (int i = 0; i < rt_sceneFastCount; i++) {
		const int *f = rt_sceneFast[i];
		if (rt_copy(sc + f[1], buf, f[2] * f[3]))
			rt_O(f[0], buf, f[2], f[3]);
	}
}

static void dump(void)
{
	char tmp[MAX_PATH];
	sprintf(tmp, "C:/Users/Alexander/Desktop/Axis/rtrace_%lu.tmp", GetCurrentProcessId());
	FILE *f = fopen(tmp, "w");
	if (!f) return;
	fprintf(f, "name\tkind\tn\tnz\timin\timax\tfmin\tfmax\tnonfinite\tdenorm\tfloatlike\tnd\tvals\tpnull_valid_image_bad\tbadptr\tstr_n_nonterm_nonprint_empty\tsample\tpasses=%d\n", g_pass);
	for (int i = 0; i < rt_leafCount; i++) {
		St *s = &g_st[i];
		const Leaf *l = &rt_leaves[i];
		fprintf(f, "%s\t%c\t%llu\t%llu\t%lld\t%lld\t%.6g\t%.6g\t%u\t%u\t%u\t%d\t", l->name, l->kind, s->n + s->sn, s->nz,
		        s->imin, s->imax, s->fmin, s->fmax, s->nonfinite, s->denorm, s->floatlike, s->nd);
		for (int j = 0; j < s->nd && j < ND; j++) fprintf(f, "%s%llx", j ? "," : "", s->vals[j]);
		fprintf(f, "\t%u,%u,%u,%u\t%llx\t%u,%u,%u,%u\t%s\n", (unsigned)(s->n - s->nz), s->pvalid, s->pimage, s->pbad,
		        s->badptr, s->sn, s->snonterm, s->snonprint, s->sempty, s->sample);
	}
	fclose(f);
	char path[MAX_PATH];
	sprintf(path, "C:/Users/Alexander/Desktop/Axis/rtrace_%lu.tsv", GetCurrentProcessId());
	MoveFileExA(tmp, path, MOVEFILE_REPLACE_EXISTING);
}

static DWORD WINAPI run(void *unused)
{
	DWORD last = GetTickCount();
	DWORD full = 0;
	timeBeginPeriod(1);
	for (;;) {
		Sleep(3);
		fast_pass();
		if (GetTickCount() - full < 250)
			continue;
		full = GetTickCount();
		g_pass++;
		g_nseen = 0;
		rt_walk_static();      /* (the scene through g_scene's pointer: rt_root snapshots it) */
		rt_walk_textures();
		if (GetTickCount() - last > 5000) { dump(); last = GetTickCount(); }
	}
	return 0;
}

extern unsigned char g_rdata[];
static HWND WINAPI find_window(LPCSTR cls, LPCSTR name)
{
	if ((ULONG_PTR)cls > 0xffff && !strcmp(cls, "AXIS"))
		return NULL;
	return FindWindowA(cls, name);
}
int g_testMissions;
void trace_start(void)
{
	g_testMissions = GetEnvironmentVariableA("AXISRC_MISSIONS", NULL, 0) != 0;
	if (GetEnvironmentVariableA("AXISRC_MULTI", NULL, 0)) {
		DWORD old;
		void **slot = (void **)(g_rdata + (0x4a92cc - 0x4a9000));
		VirtualProtect(slot, 4, PAGE_READWRITE, &old);
		*slot = (void *)find_window;
		VirtualProtect(slot, 4, old, &old);
	}
	g_st = calloc(rt_leafCount, sizeof(St));
	CreateThread(NULL, 0, run, NULL, 0, NULL);
}
