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

static void lift_44aa40(X86 *m);

/* menuState500_missionSelect (0x44aa40), lifted by tools/lift.py */
static void lift_44aa40(X86 *m)
{
	m->eax = M32((DWORD)(0x9f63b8u));	/* 44aa40: mov eax, dword ptr [0x9f63b8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44aa45: test eax, eax */
	if (m->zf) goto L_44aa4e;	/* 44aa47: je 0x44aa4e */
	m->esp -= 4; M32(m->esp) = 0x44aa4eu; native_call(m, 0x441740u);	/* 44aa49: call 0x441740 */
L_44aa4e:
	{ DWORD a_ = M32((DWORD)(0x9f62f8u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44aa4e: cmp dword ptr [0x9f62f8], 2 */
	if (m->zf) goto L_44aa5c;	/* 44aa55: je 0x44aa5c */
	m->esp -= 4; M32(m->esp) = 0x44aa5cu; native_call(m, 0x448140u);	/* 44aa57: call 0x448140 */
L_44aa5c:
	m->esp -= 4; M32(m->esp) = 0x44aa61u; native_call(m, 0x447cb0u);	/* 44aa5c: call 0x447cb0 */
	m->eax = M32((DWORD)(0x9f62f8u));	/* 44aa61: mov eax, dword ptr [0x9f62f8] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44aa66: cmp eax, 1 */
	if (m->zf) goto L_44aa9a;	/* 44aa69: je 0x44aa9a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44aa6b: test eax, eax */
	if (m->zf) goto L_44aa9a;	/* 44aa6d: je 0x44aa9a */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 44aa6f: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44aa74: test eax, eax */
	if (m->zf) goto L_44aa9b;	/* 44aa76: je 0x44aa9b */
	m->eax = M32((DWORD)(0x9f6314u));	/* 44aa78: mov eax, dword ptr [0x9f6314] */
	m->ecx = M32((DWORD)(0x9f6310u));	/* 44aa7d: mov ecx, dword ptr [0x9f6310] */
	m->edx = M32((DWORD)(0x9f630cu));	/* 44aa83: mov edx, dword ptr [0x9f630c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44aa89: push eax */
	m->eax = M32((DWORD)(0x9f6308u));	/* 44aa8a: mov eax, dword ptr [0x9f6308] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44aa8f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44aa90: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44aa91: push eax */
	m->esp -= 4; M32(m->esp) = 0x44aa97u; native_call(m, 0x428c30u);	/* 44aa92: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44aa97: add esp, 0x10 */
L_44aa9a:
	m->esp += 4 + 0; return;	/* 44aa9a: ret  */
L_44aa9b:
	m->eax = M32((DWORD)(0x9f6300u));	/* 44aa9b: mov eax, dword ptr [0x9f6300] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44aaa0: test eax, eax */
	if (!m->zf) goto L_44aa9a;	/* 44aaa2: jne 0x44aa9a */
	m->eax = M32((DWORD)(0x9f62e0u));	/* 44aaa4: mov eax, dword ptr [0x9f62e0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44aaa9: test eax, eax */
	if (m->zf) goto L_44aab2;	/* 44aaab: je 0x44aab2 */
	native_call(m, 0x44aa30u); return;	/* 44aaad: jmp 0x44aa30 */
L_44aab2:
	native_call(m, 0x44aa20u); return;	/* 44aab2: jmp 0x44aa20 */
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
