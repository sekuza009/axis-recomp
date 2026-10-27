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

static void lift_420280(X86 *m);

/* main_loop (0x420280), lifted by tools/lift.py */
static void lift_420280(X86 *m)
{
	m->ecx = M32((DWORD)(0x76d3e8u));	/* 420280: mov ecx, dword ptr [0x76d3e8] */
	m->eax = 0x270fu;	/* 420286: mov eax, 0x270f */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42028b: cmp ecx, eax */
	if (!m->zf) goto L_4202c3;	/* 42028d: jne 0x4202c3 */
	{ DWORD a_ = M32((DWORD)(0x67ef0cu)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42028f: cmp dword ptr [0x67ef0c], eax */
	if (m->zf) goto L_42029c;	/* 420295: je 0x42029c */
	m->esp -= 4; M32(m->esp) = 0x42029cu; native_call(m, 0x41f970u);	/* 420297: call 0x41f970 */
L_42029c:
	m->eax = M32((DWORD)(0x68039cu));	/* 42029c: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4202a1: test eax, eax */
	if (!m->zf) goto L_4202af;	/* 4202a3: jne 0x4202af */
	m->esp -= 4; M32(m->esp) = 0x4202aau; native_call(m, 0x445c60u);	/* 4202a5: call 0x445c60 */
	m->esp -= 4; M32(m->esp) = 0x4202afu; native_call(m, 0x4012c0u);	/* 4202aa: call 0x4012c0 */
L_4202af:
	m->ecx = M32((DWORD)(0x9087b4u));	/* 4202af: mov ecx, dword ptr [0x9087b4] */
	m->esp -= 4; M32(m->esp) = 0x4202bau; native_call(m, 0x462050u);	/* 4202b5: call 0x462050 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4202ba: test eax, eax */
	if (!m->zf) goto L_4202c8;	/* 4202bc: jne 0x4202c8 */
	native_call(m, 0x420100u); return;	/* 4202be: jmp 0x420100 */
L_4202c3:
	native_call(m, 0x41fa40u); return;	/* 4202c3: jmp 0x41fa40 */
L_4202c8:
	m->esp += 4 + 0; return;	/* 4202c8: ret  */
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
