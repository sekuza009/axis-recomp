/* arena.c: the 64-bit build's arena (PORTING.md, stage 6) - the 4 GB block the game's 32-bit addresses are measured
   from (g_arena, src/axis.h), laid out as the original's address space:

     0x00000000 .. 0x00010000   never mapped (a null address or a small offset read through faults)
     0x00010000 .. 0x00400000   the game's main stack (it runs on it: arena_call) - its locals' addresses go into its
                                records, as they did in the original
     0x00400000 .. 0x00b6b000   the image: its data at the original addresses (arena_placeData)
     0x01000000 .. 0xf0000000   the heap: malloc / operator new / GlobalAlloc ... (arena_malloc), threads' stacks too
     0xff000000 ..              never mapped: numbers handed out for things that are not memory (a system's function
                                kept by the game, fn_ref; handles)

   Reserved at once, committed as used (Windows: VirtualAlloc; elsewhere: mmap / mprotect). The heap is a plain
   boundary-tag allocator with size bins, one lock for all threads. The function table maps the original addresses
   the game holds (FN in src/axis.h) to the C functions (build/fn_table64.c, tools/mkfn64.py). Portable C but for the
   stack switch, written per processor (x86-64 System V and Windows x64; arm64 to come). */
#if defined(__x86_64__) || defined(__aarch64__) || defined(_M_X64)
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <pthread.h>
#endif

typedef uint32_t u32;
typedef uint8_t u8;

unsigned char *g_arena;

#define ARENA_SIZE 0x100000000ull
#define STACK_LO 0x00010000u
#define STACK_HI 0x00400000u
#define IMAGE_LO 0x00400000u
#define IMAGE_HI 0x00b6b000u
#define HEAP_LO 0x01000000u
#define HEAP_HI 0xf0000000u
#define TOKEN_LO 0xff000000u
#define COMMIT_STEP 0x100000u   /* (the heap committed 1 MB at a time) */

static FILE *g_arenaLog;
static void alog(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
static void alog(const char *fmt, ...)
{
	va_list a;
	va_start(a, fmt);
	vfprintf(g_arenaLog ? g_arenaLog : stderr, fmt, a);
	va_end(a);
	fflush(g_arenaLog ? g_arenaLog : stderr);
}
void arena_setLog(FILE *f) { g_arenaLog = f; }

/* ---- the lock (the heap and the token tables) */
#ifdef _WIN32
static SRWLOCK g_lock = SRWLOCK_INIT;
static void lock(void) { AcquireSRWLockExclusive(&g_lock); }
static void unlock(void) { ReleaseSRWLockExclusive(&g_lock); }
#else
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static void lock(void) { pthread_mutex_lock(&g_lock); }
static void unlock(void) { pthread_mutex_unlock(&g_lock); }
#endif

static int commit(u32 lo, u32 hi)
{
#ifdef _WIN32
	return VirtualAlloc(g_arena + lo, hi - lo, MEM_COMMIT, PAGE_READWRITE) != NULL;
#else
	return mprotect(g_arena + lo, hi - lo, PROT_READ | PROT_WRITE) == 0;
#endif
}

/* the block reserved, the stack and the image committed; 0 when the system would not give 4 GB of address space */
int arena_init(void)
{
	if (g_arena)
		return 1;
#ifdef _WIN32
	g_arena = VirtualAlloc(NULL, ARENA_SIZE, MEM_RESERVE, PAGE_NOACCESS);
#else
	void *p = mmap(NULL, ARENA_SIZE, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
	g_arena = p == MAP_FAILED ? NULL : p;
#endif
	if (!g_arena) {
		alog("arena: 4 GB of address space not available\n");
		return 0;
	}
	if (!commit(STACK_LO, STACK_HI) || !commit(IMAGE_LO, IMAGE_HI)) {
		alog("arena: the stack / image could not be committed\n");
		return 0;
	}
	return 1;
}

/* the game's data put in place: pieces of (address, bytes, size), ended by a 0 address (src/data: g_rdataPieces ...) */
typedef struct { u32 address; const void *bytes; u32 size; } DataPiece;
void arena_placeData(const DataPiece *pieces)
{
	for (const DataPiece *p = pieces; p->address; p++)
		memcpy(g_arena + p->address, p->bytes, p->size);
}

/* ---- the heap: chunks [header 16 bytes][payload], 16-byte aligned. Header: the chunk's size with two flags (bit 0
   this one in use, bit 1 the one before it in use), the size of the one before (valid when that one is free), and
   when free the list links (arena offsets). The free lists by size: 64 exact bins for 32 .. 1024 bytes in steps of
   16, then one bin per power of two. */
typedef struct {
	u32 size;       /* | IN_USE | PREV_IN_USE */
	u32 prevSize;
	u32 next, prev; /* (free chunks) */
} Chunk;
#define IN_USE 1u
#define PREV_IN_USE 2u
#define FLAGS 3u
#define HDR 16u
#define MIN_CHUNK 32u
#define NBINS 96
static u32 g_bins[NBINS];   /* each list's first chunk (0: empty) */
static u32 g_top = HEAP_LO, g_committed = HEAP_LO;   /* the unused rest starts at g_top */
static size_t g_inUse, g_peak;

#define CH(off) ((Chunk *)(g_arena + (off)))
static u32 csize(u32 c) { return CH(c)->size & ~FLAGS; }

static int bin_of(u32 size)
{
	if (size <= 1024)
		return (int)(size >> 4) - 2;   /* (32 -> 0 .. 1024 -> 62) */
	int b = 63;
	for (u32 s = size >> 11; s && b < NBINS - 1; s >>= 1)
		b++;
	return b;
}
static void unlink_chunk(u32 c)
{
	Chunk *k = CH(c);
	if (k->prev)
		CH(k->prev)->next = k->next;
	else
		g_bins[bin_of(csize(c))] = k->next;
	if (k->next)
		CH(k->next)->prev = k->prev;
}
static void link_chunk(u32 c)
{
	int b = bin_of(csize(c));
	Chunk *k = CH(c);
	k->prev = 0;
	k->next = g_bins[b];
	if (k->next)
		CH(k->next)->prev = c;
	g_bins[b] = c;
}
/* the chunk after c learns whether c is in use (and c's size, when c is free) */
static void tell_next(u32 c, int used)
{
	u32 n = c + csize(c);
	if (n >= g_top)
		return;
	if (used)
		CH(n)->size |= PREV_IN_USE;
	else {
		CH(n)->size &= ~PREV_IN_USE;
		CH(n)->prevSize = csize(c);
	}
}
/* c (free, unlinked) cut to size; the rest freed */
static void split(u32 c, u32 size)
{
	u32 all = csize(c);
	if (all - size < MIN_CHUNK)
		return;
	CH(c)->size = size | (CH(c)->size & FLAGS);
	u32 r = c + size;
	CH(r)->size = (all - size) | PREV_IN_USE;
	tell_next(r, 0);
	link_chunk(r);
}

static u32 take(u32 size)
{
	for (int b = bin_of(size); b < NBINS; b++)
		for (u32 c = g_bins[b]; c; c = CH(c)->next)
			if (csize(c) >= size) {
				unlink_chunk(c);
				split(c, size);
				CH(c)->size |= IN_USE;
				tell_next(c, 1);
				return c;
			}
	/* from the top */
	if (size > HEAP_HI - g_top)
		return 0;
	u32 c = g_top;
	if (c + size > g_committed) {
		u32 to = (c + size + COMMIT_STEP - 1) & ~(COMMIT_STEP - 1);
		if (to > HEAP_HI || !commit(g_committed, to))
			return 0;
		g_committed = to;
	}
	g_top = c + size;
	/* (the chunk before the top is in use unless the top was given back by a free - then it merged into the top) */
	CH(c)->size = size | IN_USE | PREV_IN_USE;
	return c;
}

void *arena_malloc(size_t n)
{
	if (n > 0x7ffff000u)
		return NULL;
	u32 size = (u32)((n + HDR + 15) & ~(size_t)15);
	if (size < MIN_CHUNK)
		size = MIN_CHUNK;
	lock();
	u32 c = take(size);
	if (c) {
		g_inUse += csize(c);
		if (g_inUse > g_peak)
			g_peak = g_inUse;
	}
	unlock();
	if (!c) {
		alog("arena: out of heap (%zu bytes asked, %zu in use)\n", n, g_inUse);
		return NULL;
	}
	return g_arena + c + HDR;
}

static int is_heap(const void *p)
{
	uintptr_t o = (uintptr_t)((const u8 *)p - g_arena);
	return o >= HEAP_LO + HDR && o < g_top && !(o & 15);
}

void arena_free(void *p)
{
	if (!p)
		return;
	if (!is_heap(p)) {
		alog("arena: free of %p, not a heap block (ignored)\n", p);
		return;
	}
	lock();
	u32 c = (u32)((u8 *)p - g_arena) - HDR;
	if (!(CH(c)->size & IN_USE)) {
		unlock();
		alog("arena: double free at %08x (ignored)\n", c);
		return;
	}
	g_inUse -= csize(c);
	CH(c)->size &= ~IN_USE;
	/* merged with the free chunk after it, and the one before */
	u32 n = c + csize(c);
	if (n < g_top && !(CH(n)->size & IN_USE)) {
		unlink_chunk(n);
		CH(c)->size = (csize(c) + csize(n)) | (CH(c)->size & FLAGS);
	}
	if (!(CH(c)->size & PREV_IN_USE)) {
		u32 b = c - CH(c)->prevSize;
		unlink_chunk(b);
		CH(b)->size = (csize(b) + csize(c)) | (CH(b)->size & FLAGS);
		c = b;
	}
	if (c + csize(c) == g_top)   /* (the last chunk: back to the top) */
		g_top = c;
	else {
		tell_next(c, 0);
		link_chunk(c);
	}
	unlock();
}

size_t arena_msize(const void *p)
{
	if (!p || !is_heap(p))
		return 0;
	return csize((u32)((const u8 *)p - g_arena) - HDR) - HDR;
}

void *arena_realloc(void *p, size_t n)
{
	if (!p)
		return arena_malloc(n);
	if (!n) {
		arena_free(p);
		return NULL;
	}
	size_t have = arena_msize(p);
	if (n <= have)
		return p;
	void *q = arena_malloc(n);
	if (q) {
		memcpy(q, p, have);
		arena_free(p);
	}
	return q;
}

void *arena_calloc(size_t a, size_t b)
{
	if (b && a > (size_t)-1 / b)
		return NULL;
	void *p = arena_malloc(a * b);
	if (p)
		memset(p, 0, a * b);
	return p;
}

void arena_stats(size_t *inUse, size_t *peak, u32 *top)
{
	*inUse = g_inUse;
	*peak = g_peak;
	*top = g_top;
}

/* ---- the stack switch: fn(arg) run with the stack pointer at top (16-byte aligned), back on the caller's stack
   after. Windows x64 also keeps the thread's stack bounds (its TIB: StackBase, StackLimit, DeallocationStack) for
   stack probes and unwinding: they are moved to the arena stack for the call and put back after. */
typedef void ArenaFn(void *arg);
#if defined(__x86_64__) && defined(_WIN32)
void arena_switch(void *arg, ArenaFn *fn, void *top, void *bottom);
__asm__(
	".text\n"
	".globl arena_switch\n"
	"arena_switch:\n"
	"\tpushq %rbp\n"
	"\tmovq %rsp, %rbp\n"
	"\tpushq %r12\n"
	"\tpushq %r13\n"
	"\tpushq %r14\n"
	"\tpushq %r15\n"
	"\tmovq %gs:0x08, %r12\n"      /* StackBase */
	"\tmovq %gs:0x10, %r13\n"      /* StackLimit */
	"\tmovq %gs:0x1478, %r14\n"    /* DeallocationStack */
	"\tmovq %r8, %gs:0x08\n"
	"\tmovq %r9, %gs:0x10\n"
	"\tmovq %r9, %gs:0x1478\n"
	"\tmovq %rsp, %r15\n"
	"\tmovq %r8, %rsp\n"
	"\tandq $-16, %rsp\n"
	"\tsubq $32, %rsp\n"           /* (the callee's home space) */
	"\tcallq *%rdx\n"
	"\tmovq %r15, %rsp\n"
	"\tmovq %r12, %gs:0x08\n"
	"\tmovq %r13, %gs:0x10\n"
	"\tmovq %r14, %gs:0x1478\n"
	"\tpopq %r15\n"
	"\tpopq %r14\n"
	"\tpopq %r13\n"
	"\tpopq %r12\n"
	"\tpopq %rbp\n"
	"\tretq\n");
#elif defined(__x86_64__)
void arena_switch(void *arg, ArenaFn *fn, void *top, void *bottom) __asm__("arena_switch_");
__asm__(
	".text\n"
	".globl arena_switch_\n"
	"arena_switch_:\n"
	"\tpushq %rbp\n"
	"\tmovq %rsp, %rbp\n"
	"\tmovq %rdx, %rsp\n"
	"\tandq $-16, %rsp\n"
	"\tcallq *%rsi\n"
	"\tmovq %rbp, %rsp\n"
	"\tpopq %rbp\n"
	"\tretq\n");
#elif defined(__aarch64__)
void arena_switch(void *arg, ArenaFn *fn, void *top, void *bottom) __asm__("arena_switch_");
__asm__(
	".text\n"
	".globl arena_switch_\n"
	"arena_switch_:\n"
	"\tstp x29, x30, [sp, #-16]!\n"
	"\tmov x29, sp\n"
	"\tand x2, x2, #-16\n"
	"\tmov sp, x2\n"
	"\tblr x1\n"
	"\tmov sp, x29\n"
	"\tldp x29, x30, [sp], #16\n"
	"\tret\n");
#endif

static _Thread_local int t_onArena;   /* (this thread already runs on an arena stack: calls go straight on) */

/* fn(arg) on the game's main stack (a nested call, already there, straight on) */
void arena_call(ArenaFn *fn, void *arg)
{
	if (t_onArena) {
		fn(arg);
		return;
	}
	t_onArena = 1;
	arena_switch(arg, fn, g_arena + STACK_HI - 64, g_arena + STACK_LO);
	t_onArena = 0;
}

/* fn(arg) on a stack of its own in the arena, for a thread the game starts (its stack freed after) */
void arena_callOnNewStack(ArenaFn *fn, void *arg, u32 size)
{
	u8 *stack = arena_malloc(size);
	if (!stack) {
		alog("arena: no stack for a thread\n");
		return;
	}
	t_onArena = 1;
	arena_switch(arg, fn, stack + size - 64, stack);
	t_onArena = 0;
	arena_free(stack);
}

/* ---- functions the game holds as values */
typedef struct { u32 address; void (*fn)(void); } FnEntry;
extern const FnEntry g_fnTable[];
extern const unsigned g_fnCount;
#define FNREF_LO 0xff800000u
#define FNREF_MAX 4096
static void *g_fnRefs[FNREF_MAX];
static unsigned g_fnRefCount;

void *fn_ptr(u32 address)
{
	if (!address)
		return NULL;
	if (address >= FNREF_LO) {
		u32 i = (address - FNREF_LO) / 16;
		if (i < g_fnRefCount)
			return g_fnRefs[i];
	} else {
		unsigned lo = 0, hi = g_fnCount;
		while (lo < hi) {
			unsigned mid = (lo + hi) / 2;
			if (g_fnTable[mid].address < address)
				lo = mid + 1;
			else
				hi = mid;
		}
		if (lo < g_fnCount && g_fnTable[lo].address == address)
			return (void *)g_fnTable[lo].fn;
	}
	alog("arena: no function at %08x (called from %p)\n", address, __builtin_return_address(0));
	abort();
}

/* a system's function kept by the game: its number (the same one again for the same function) */
u32 fn_ref(void *fn)
{
	if (!fn)
		return 0;
	lock();
	for (unsigned i = 0; i < g_fnRefCount; i++)
		if (g_fnRefs[i] == fn) {
			unlock();
			return FNREF_LO + i * 16;
		}
	u32 r = 0;
	if (g_fnRefCount < FNREF_MAX) {
		g_fnRefs[g_fnRefCount] = fn;
		r = FNREF_LO + g_fnRefCount++ * 16;
	}
	unlock();
	return r;
}

/* the original address of a C function the game may hold (the reverse of fn_ptr), 0 for none */
u32 fn_address(void *fn)
{
	for (unsigned i = 0; i < g_fnCount; i++)
		if ((void *)g_fnTable[i].fn == fn)
			return g_fnTable[i].address;
	return 0;
}

/* ---- a pointer outside the arena turned into an address (AV of a pointer the game should not keep: the C library's
   memory, a string of the loader's...): reported, the first 64 sites with their callers */
void arena_bad(const void *p, const void *caller)
{
	static int n;
	if (n++ < 64)
		alog("arena: address of %p outside the arena taken (at %p)\n", p, caller);
}
#endif
