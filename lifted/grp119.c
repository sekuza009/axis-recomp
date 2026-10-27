/* ---- emulated machine for lifted functions (tools/lift.py) ---- */
#if 0 /* X86 comes from the earlier lifted file */
typedef struct { DWORD eax, ecx, edx, ebx, esp, ebp, esi, edi; int zf, sf, cf, of; long double fs[8]; int ft; DWORD fsw; } X86;
#endif
#ifndef LIFT_FS0_DEFINED
#define LIFT_FS0_DEFINED
static DWORD g_lift_fs0;          /* the emulated fs:[0] (SEH chain head) */
#endif
#define M32(a) (*(DWORD *)(a))
#define M16(a) (*(WORD *)(a))
#define M8(a) (*(BYTE *)(a))
#define MF(a) (*(float *)(a))
#define MDBL(a) (*(double *)(a))
#define ST(i) (m->fs[m->ft - 1 - (i)])
#define FPUSH(v) (m->fs[m->ft++] = (v))
#define FPOP() (m->ft--)
#define FLAGS(r, bits) (m->zf = (r) == 0, m->sf = (int)(((r) >> ((bits) - 1)) & 1))
/* fcom: C0 = less, C3 = equal, all of C0/C2/C3 = unordered (status word bits 8, 10, 14) */
#define FCOM(a, b) do { long double a_ = (a), b_ = (b); \
	m->fsw = (a_ != a_ || b_ != b_) ? 0x4500u : a_ < b_ ? 0x0100u : a_ == b_ ? 0x4000u : 0; } while (0)

static void lift_410190(X86 *m);

/* armc_onStateEnter (0x410190), lifted by tools/lift.py */
static void lift_410190(X86 *m)
{
	m->eax = M32((DWORD)(0x4dc790u));	/* 410190: mov eax, dword ptr [0x4dc790] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410195: cmp eax, 1 */
	if (m->zf) goto L_4101cd;	/* 410198: je 0x4101cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41019a: test eax, eax */
	if (m->zf) goto L_4101cd;	/* 41019c: je 0x4101cd */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 41019e: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4101a3: test eax, eax */
	if (!m->zf) goto L_4101cd;	/* 4101a5: jne 0x4101cd */
	m->eax = M32((DWORD)(0x4dc798u));	/* 4101a7: mov eax, dword ptr [0x4dc798] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4101ac: dec eax */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4101ad: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_4101cd;	/* 4101b0: ja 0x4101cd */
	switch (m->eax) { case 0: goto L_4101b9; case 1: goto L_4101be; case 2: goto L_4101c3; case 3: goto L_4101c8; default: abort(); }	/* 4101b2: jmp dword ptr [eax*4 + 0x4101d0] */
L_4101b9:
	native_call(m, 0x40fb20u); return;	/* 4101b9: jmp 0x40fb20 */
L_4101be:
	native_call(m, 0x40fd30u); return;	/* 4101be: jmp 0x40fd30 */
L_4101c3:
	native_call(m, 0x40ff40u); return;	/* 4101c3: jmp 0x40ff40 */
L_4101c8:
	native_call(m, 0x410160u); return;	/* 4101c8: jmp 0x410160 */
L_4101cd:
	m->esp += 4 + 0; return;	/* 4101cd: ret  */
}

/* the lifter macros are local to this file (recomp.c has its own ST()) */
#undef M32
#undef M16
#undef M8
#undef MF
#undef MDBL
#undef ST
#undef FPUSH
#undef FPOP
#undef FLAGS
#undef FCOM
