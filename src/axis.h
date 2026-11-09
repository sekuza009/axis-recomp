/* axis.h: conventions for the readable rebuild of AxisGL.exe.

   Every function here is a rebuild of one function of the game, checked bit-exact against the original by the
   recomp harness (recomp.c: the same random tests the lifted versions passed). Its comment names the original
   address. Rules that keep the code readable and exact at once:

   - Game data lives where the game keeps it: the scene object (scene.h, passed in like the original's "this") and
     named globals at fixed addresses (game.h).
   - A call to another game function is written as an ordinary call, text_drawSized(x, y, s, 8): game.h makes the
     name a call through the function's original address. So whichever version is installed (the original or a
     rebuild) runs, and the harness can put a stub there while it tests the caller. A rebuild is therefore defined
     with its name in parentheses, void (hud_drawFps)(Scene *s), which stops the call macro from expanding there.
   - Floating point is x87 (this tree is built with -mno-sse): float values are rounded where the original stores
     them; comparisons are written so NaN goes the way the original's fcomp / fnstsw test sends it; float-to-int
     conversions use ftol(), the original's __ftol (truncation, low 32 bits of the 64-bit result).
   - Imports (OpenGL, Win32) are called through the game's import table, as the original calls them. */
#ifndef AXIS_H
#define AXIS_H
#include <stdint.h>
#include <stddef.h>
#include "x87.h"   /* x87_fsin, x87_fsqrt ...: the instructions the original computes with */

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;

#define CDECL __attribute__((cdecl))
#define STDCALL __attribute__((stdcall))
#define THISCALL __attribute__((thiscall))

/* the game's image (its header, code bytes, data: 0x400000 .. 0xb6b000 in the original). In the harness (recomp.dll)
   it is where AxisGL.exe put it; AxisRC.exe (AXIS_DIRECT) keeps it in an array of its own, g_image
   (standalone/main.c), so the game no longer needs its original addresses. IMG(a) is the original address a there;
   RELOC(a) is IMG(a) for an address in the original range and a itself for any other (memory of AxisRC.exe's own,
   the heap): for values that may be either, e.g. a table of addresses read through GAME_VAR. The original range
   itself is kept unmapped (inaccessible) in AxisRC.exe, so an address missed here stops the game at once */
#define IMG_BASE 0x400000u
#define IMG_SIZE 0x76b000u
/* the 64-bit build (AXIS_64): the game's addresses stay 32-bit numbers - its records, tables and saved data hold them
   in 32-bit fields - measured from g_arena, a 4 GB block reserved for the game that reproduces the original's address
   space: the image's data at its original addresses (so IMG(a) is a itself), the heap, the stacks the game runs on and
   every buffer the game keeps an address of. AP(T, v) is the address v as a T pointer, AV(p) a pointer's address (0 and
   NULL each the other's); APTR(T) a record's pointer field (scene.h). In the 32-bit builds all three are the plain
   casts and pointer types they replace */
#if __SIZEOF_POINTER__ == 8
#define AXIS_64 1
extern unsigned char *g_arena;
static inline void *arena_ptr(u32 v) { return v ? (void *)(g_arena + v) : (void *)0; }
static inline u32 arena_ref(const void *p) { return p ? (u32)((const unsigned char *)p - g_arena) : 0; }
#define APTR(T) u32
/* (either takes a pointer as well, passed on as it is: AP(T, p) a plain cast, AV(v) of a number the number) */
#define AP(T, v) ((T *)__builtin_choose_expr(__builtin_classify_type(v) == 5, (void *)(uintptr_t)(v),                                              arena_ptr((u32)(uintptr_t)(v))))
#define AV(p) __builtin_choose_expr(__builtin_classify_type(p) == 5, arena_ref((const void *)(uintptr_t)(p)), (u32)(uintptr_t)(p))
#else
#define APTR(T) T *
#define AP(T, v) ((T *)(v))
#define AV(p) ((u32)(p))
#endif
/* a pointer stored in an APTR field (or a pointer global): AV(p) in the 64-bit build, p itself in the 32-bit ones */
#ifdef AXIS_64
#define AREF(p) AV(p)
#else
#define AREF(p) (p)
#endif
#ifdef AXIS_64
#define IMG(a) ((u32)(a))
#define RELOC(a) (a)
#elif defined(AXIS_DIRECT)
/* (its read-only data, 0x4a9000 .. 0x4ad000, and writable data, 0x4ad000 .. 0xb13000, are the structs g_rdata and
   g_data of src/data/layout.h; the rest - the header, the code bytes still read - is g_image) */
extern unsigned char g_image[];
struct GameRdata;
struct GameData;
extern struct GameRdata g_rdata;
extern struct GameData g_data;
#define IMG(a) ((u32)(a) - 0x4a9000u < 0x4000u ? (u32)&g_rdata + ((u32)(a) - 0x4a9000u) : \
                (u32)(a) - 0x4ad000u < 0x666000u ? (u32)&g_data + ((u32)(a) - 0x4ad000u) : (u32)g_image + ((u32)(a) - IMG_BASE))
static inline u32 img_reloc(u32 a) { return a - IMG_BASE < IMG_SIZE ? IMG(a) : a; }
/* (of the operand's own type: a pointer stays a pointer, so RELOC(p) + 1 steps as p + 1 did) */
#ifdef AXIS_PORTABLE
/* (the portable build: every address the game holds at run time is a real one - src/data writes its pointers through
   IMG() - so only a compile-time constant (an original address written in the source, F(0x4a93ec)) is mapped; a run-time
   value never is, wherever the game is loaded. The test build keeps the original's range guarded to catch any original
   number still reaching here at run time) */
#define RELOC(a) ((__typeof__((a) + 0))(__builtin_constant_p((u32)(a)) ? img_reloc((u32)(a)) : (u32)(a)))
#else
#define RELOC(a) ((__typeof__((a) + 0))img_reloc((u32)(a)))
#endif
#else
#define IMG(a) (a)
#define RELOC(a) (a)
#endif

/* the game's C runtime by name (src/crt_addrs.h): CRT(name) its address, CRT_CALL(name, ret, arg types...)(args) a
   call (in AxisRC.exe standalone/crt.c puts msvcrt's or a rebuilt one there) */
#include "crt_addrs.h"
#define CRT(name) CRTADDR_##name
#ifdef AXIS_PORTABLE
/* (the portable build: the runtime entries are a table the loader fills - standalone/crt.c - not jumps in the
   image) */
enum { CRTIX_NONE = -1
#define CRT_IX_(n) , CRTIX_##n
CRT_ENTRIES(CRT_IX_)
#undef CRT_IX_
, CRT_COUNT };
#ifdef AXIS_64
extern void *g_crtFn[CRT_COUNT];
#else
extern u32 g_crtFn[CRT_COUNT];
#endif
#define CRT_FN(name) (g_crtFn[CRTIX_##name])
#else
#define CRT_FN(name) IMG(CRT(name))   /* an entry of the game's runtime as a value (to call through) */
#endif
#define CRT_CALL(name, ret, ...) ((ret (CDECL *)(__VA_ARGS__))CRT_FN(name))
/* the game's __ftol: ST0 truncated to 64 bits, EDX:EAX; callers keep the low 32 bits */
#ifdef AXIS_64
/* (the 64-bit build: the same truncation - an out-of-range value gives the x87's indefinite, whose low 32 bits are 0) */
static inline int ftol(long double x) { return (int)(long long)x; }
#else
static inline int ftol(long double x)
{
	long long r;
	__asm__ volatile("call *%1" : "=A"(r) : "r"(CRT_FN(ftol)), "t"(x) : "ecx", "st", "memory");
	return (int)r;
}
#endif

/* x rounded to a float, as the original's fstp dword does. Needed wherever a rounded value is used again in
   arithmetic: clang keeps x87 temporaries at 80 bits even through a (float) cast or a float variable, and rounds
   only when the value goes to memory (a store, an argument). */
static inline float f32(long double x)
{
	volatile float r = (float)x;
	return r;
}

/* x87 arithmetic with a float operand straight from memory (flds / fmuls / fadds ... dword [m]), where the original
   does that and a NaN can reach it: a signalling NaN taken from memory this way meets a quiet NaN differently from
   one loaded into a register first. x op *m, or *m op x for the reversed ones. */
static inline long double fld_m(const float *m) { long double x; __asm__("flds %1" : "=t"(x) : "m"(*m)); return x; }
static inline long double fmul_m(long double x, const float *m) { __asm__("fmuls %1" : "+t"(x) : "m"(*m)); return x; }
static inline long double fadd_m(long double x, const float *m) { __asm__("fadds %1" : "+t"(x) : "m"(*m)); return x; }
static inline long double fsub_m(long double x, const float *m) { __asm__("fsubs %1" : "+t"(x) : "m"(*m)); return x; }
static inline long double fsubr_m(long double x, const float *m) { __asm__("fsubrs %1" : "+t"(x) : "m"(*m)); return x; }
static inline long double fdiv_m(long double x, const float *m) { __asm__("fdivs %1" : "+t"(x) : "m"(*m)); return x; }
static inline long double fdivr_m(long double x, const float *m) { __asm__("fdivrs %1" : "+t"(x) : "m"(*m)); return x; }
/* the common two-instruction forms, a and b both floats in memory: flds a, then fmuls / fadds / fsubs / fdivs b (the
   result on the FPU, unrounded; f32() rounds it to a float) */
#define FMUL(a, b) fmul_m(fld_m(&(a)), &(b))
#define FADD(a, b) fadd_m(fld_m(&(a)), &(b))
#define FSUB(a, b) fsub_m(fld_m(&(a)), &(b))
#define FDIV(a, b) fdiv_m(fld_m(&(a)), &(b))

/* a float in memory as its 32 bits (also assignable): for values the original only copies, never loading them into
   the FPU (which would quiet a signalling NaN) */
#define BITS(lvalue) (*(u32 *)&(lvalue))


/* a game function at its original address, as a callable expression */
/* a function value the game holds (a handler table's entry, a vtable's method: a 32-bit number in the 64-bit build, the
   function's original address - FN_ADDR - which fn_ptr looks up) as a callable of type `type` */
#ifdef AXIS_64
void *fn_ptr(u32 address);
#define FNP(type, v) ((type)fn_ptr((u32)(v)))
#else
#define FNP(type, v) ((type)(v))
#endif
#define GAME_CDECL(addr, ret, ...) FNP(ret (CDECL *)(__VA_ARGS__), RELOC(addr))
#define GAME_THISCALL(addr, ret, ...) FNP(ret (THISCALL *)(__VA_ARGS__), RELOC(addr))
/* a rebuilt game function, by its C name and original address: in the harness (recomp.dll) a call to the address,
   where the harness's tests can stand a mock or the original in for it; in AxisRC.exe (built with AXIS_DIRECT) a
   direct call to the C function, its address checked against the hook table at compile time (build/fn_syms.h,
   tools/hooktable.py) */
#include "fn_addrs.h"   /* FNADDR_<name>: each rebuilt function's original address */
#ifdef AXIS_DIRECT
#include "fn_syms.h"
#define FN_CHECK(name, addr) (void)sizeof(char[(addr) == FNADDR_##name ? 1 : -1])
#define GAME_FN(name, addr, ret, ...) (FN_CHECK(name, addr), (ret (CDECL *)(__VA_ARGS__))(void *)FN_##name)
#define GAME_THISFN(name, addr, ret, ...) (FN_CHECK(name, addr), (ret (THISCALL *)(__VA_ARGS__))(void *)FN_##name)
/* a rebuilt function's address as a value (a callback, a table of handlers), constant enough for static data (the
   64-bit build: its original address, a 32-bit number like every other address the game holds - FNP calls it) */
#ifdef AXIS_64
#define FN_ADDR(name, addr) ((u32)(addr) + 0 * sizeof(char[(addr) == FNADDR_##name ? 1 : -1]))
#define FN_VIA(name, addr, stub) ((u32)(stub) + 0 * sizeof(char[(addr) == FNADDR_##name ? 1 : -1]))
/* the C function itself, for the system (a thread's procedure, a sort's comparison) */
#define FN_REAL(name) ((void *)FN_##name)
#else
#define FN_ADDR(name, addr) ((u32)(void *)FN_##name + 0 * sizeof(char[(addr) == FNADDR_##name ? 1 : -1]))
/* the same through a compiler jump stub at stub (the original's data points at the stub, which only jumps on) */
#define FN_VIA(name, addr, stub) FN_ADDR(name, addr)
#define FN_REAL(name) ((void *)FN_##name)
#endif
#else
#define GAME_FN(name, addr, ret, ...) GAME_CDECL(addr, ret, __VA_ARGS__)
#define GAME_THISFN(name, addr, ret, ...) GAME_THISCALL(addr, ret, __VA_ARGS__)
#define FN_ADDR(name, addr) (addr)
#define FN_VIA(name, addr, stub) (stub)
#endif
/* the same by name alone, the address from src/fn_addrs.h: FN(net_pingThreadProc) as a value (a callback, a
   handler table's entry); CALL_FN / CALL_THISFN(name, ret, arg types...)(args) a call with the caller's own types */
#define FN(name) FN_ADDR(name, FNADDR_##name)
#define CALL_FN(name, ret, ...) GAME_FN(name, FNADDR_##name, ret, __VA_ARGS__)
#define CALL_THISFN(name, ret, ...) GAME_THISFN(name, FNADDR_##name, ret, __VA_ARGS__)
/* a call the patch DLL may retarget at start-up (it rewrites the call instruction's target): the call goes to
   whatever the instruction at the original call site targets now, as the original's would (not in the native
   build: no patch DLL) */
#ifdef AXIS_NATIVE
#elif defined(AXIS_DIRECT)
/* (AxisRC.exe: none of the game's code runs; the patch layer keeps its retargets in a table: src/wide.c) */
void *wide_callSite(u32 site);
int wide_callAdded(u32 site, u32 at, const char *pattern);
#define PATCHED_CALL(site, ret, ...) ((ret (CDECL *)(__VA_ARGS__))wide_callSite(site))
#define PATCHED_THISCALL(site, ret, ...) ((ret (THISCALL *)(__VA_ARGS__))wide_callSite(site))
/* 1 when the patch DLL's rewritten block at `at`, which adds a call at `site`, is in */
#define PATCHED_BLOCK(site, at, pattern) wide_callAdded(site, at, pattern)
#else
#define PATCHED_CALL(site, ret, ...) ((ret (CDECL *)(__VA_ARGS__))(RELOC(site) + 5 + *(const i32 *)(RELOC(site) + 1)))
#define PATCHED_THISCALL(site, ret, ...) ((ret (THISCALL *)(__VA_ARGS__))(RELOC(site) + 5 + *(const i32 *)(RELOC(site) + 1)))
#define PATCHED_BLOCK(site, at, pattern) code_matches(at, pattern)
#endif
/* a call at one of the game's call sites the patch DLL may retarget, naming the function the game as shipped calls
   there: SITE_CALL(site, fn, ret, arg types)(args). The native build (AXIS_NATIVE: the fixes in the game's own code)
   calls fn itself; the others go through the call site (PATCHED_CALL) */
#ifdef AXIS_NATIVE
#define SITE_CALL(site, fn, ret, ...) ((ret (CDECL *)(__VA_ARGS__))(void *)FN_##fn)
#define SITE_THISCALL(site, fn, ret, ...) ((ret (THISCALL *)(__VA_ARGS__))(void *)FN_##fn)
#else
#define SITE_CALL(site, fn, ret, ...) PATCHED_CALL(site, ret, __VA_ARGS__)
#define SITE_THISCALL(site, fn, ret, ...) PATCHED_THISCALL(site, ret, __VA_ARGS__)
#endif
/* 1 when the game's code at addr currently reads as pattern (hex bytes separated by spaces, "??" for any byte): for
   a block the patch DLL rewrites at start-up, so the rebuild follows whichever version is in memory */
static inline int code_matches(u32 addr, const char *pattern)
{
	const u8 *code = AP(const u8, RELOC(addr));
	for (const char *p = pattern; *p; code++) {
		if (p[0] != '?') {
			unsigned hi = p[0] <= '9' ? p[0] - '0' : p[0] - 'a' + 10, lo = p[1] <= '9' ? p[1] - '0' : p[1] - 'a' + 10;
			if (*code != (u8)(hi * 16 + lo))
				return 0;
		}
		p += 2;
		while (*p == ' ')
			p++;
	}
	return 1;
}
/* a COM method of obj (DirectInput, DirectSound...): the vtable entry at byte offset, called stdcall with obj first */
#define COM(obj, offset, ret, ...) ((ret (STDCALL *)(void *, ##__VA_ARGS__))(*(void ***)(obj))[(offset) / 4])
#define COM_RELEASE 0x08

/* an import, through the game's import table slot */
#define IMPORT(slot, ret, ...) ((ret (STDCALL *)(__VA_ARGS__))*(const u32 *)IMG(slot))
/* the same by the function's name (its slot: IMP_<name>, src/imports.h): IMPORT_FN(GlobalLock, void *, void *)(h) */
#include "imports.h"
#ifdef AXIS_PORTABLE
/* (the portable build: a system call is a call to the platform's function plat_<name> - src/plat/plat.h; the
   Windows platform's are jumps through the import slots, build/plat_imports.s from tools/mkimportlist.py - not a
   load from the slot at the call site) */
#include "import_list.h"
#define PLAT_IMPORT_DECL_(n, d) void plat_##n(void) __asm__("_plat_" #n);
IMPORT_LIST(PLAT_IMPORT_DECL_)
#undef PLAT_IMPORT_DECL_
#define IMPORT_FN(name, ret, ...) ((ret (STDCALL *)(__VA_ARGS__))(void *)plat_##name)
#else
#define IMPORT_FN(name, ret, ...) IMPORT(IMP_##name, ret, __VA_ARGS__)
#endif
/* a global of the game at its address (an original one or, for memory reached through a pointer, any) */
#define GAME_VAR(type, addr) (*AP(type, RELOC(addr)))
/* a named global's address (src/globals.h): the original's in the harness, its place in AxisRC.exe - a constant
   either way (in AxisRC.exe every name is a member of g_rdata / g_data or IMG()'s place: src/data/layout_names.h) */
#ifdef AXIS_64
/* (the 64-bit build: the original address itself, a constant - src/addr_consts.h, tools/mkaddrc.py) */
#include "addr_consts.h"
#define ADDR(name) ADDRC_##name
#define ADDR_AT(name, i) (ADDRC_##name + (u32)(i) * (u32)sizeof (name)[0])
#define ADDR_ATF(name, i, member) (ADDR_AT(name, i) + (u32)__builtin_offsetof(__typeof__((name)[0]), member))
#else
#define ADDR(name) AV(&(name))
/* the address of element i of a named array */
#define ADDR_AT(name, i) ((u32)&(name)[i])
/* the address of a member of element i (member: a field, its index or both: x, pos[1], a.b) */
#define ADDR_ATF(name, i, member) ((u32)&(name)[i].member)
#endif
/* an array / buffer / record of src/objects.h (a pointer name) as an address number */
#ifdef AXIS_64
#define OBJ(name) ADDRC_##name
#else
#define OBJ(name) AV(name)
#endif
/* a text of the image by its address, with the text for the reader (tools/img_strings.py checks it against the
   data): STR(0x4b4418, "Data/Component.dat"); MSG(n, text) is line n of the message table (0x80 bytes a line from
   0x74de24, read from msgeng.dat at start-up). Both the address as IMG() gives it */
#define STR(addr, text) IMG(addr)
#define MSG(n, text) (OBJ(g_messages) + (n) * 0x80)   /* (g_messages: src/objects.h) */
/* a class's vtable in .rdata by the class's name (src/vtables.h: tools/img_vtables.py finds them,
   tools/vtables_by_name.py lists them): self[0] = VT(Scene) */
#include "vtables.h"
#define VT(cls) IMG(VTADDR_##cls)

#endif
