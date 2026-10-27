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

static void lift_4278d0(X86 *m);

/* setup_4278d0 (0x4278d0), lifted by tools/lift.py */
static void lift_4278d0(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x4278d5u; native_call(m, 0x423e50u);	/* 4278d0: call 0x423e50 */
	m->eax = M32((DWORD)(0x4ddcecu));	/* 4278d5: mov eax, dword ptr [0x4ddcec] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4278da: cmp eax, 1 */
	if (m->zf) goto L_42791a;	/* 4278dd: je 0x42791a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4278df: test eax, eax */
	if (m->zf) goto L_42791a;	/* 4278e1: je 0x42791a */
	{ DWORD a_ = M32((DWORD)(0x4ddac8u)), b_ = 0x29au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4278e3: cmp dword ptr [0x4ddac8], 0x29a */
	if (m->zf) goto L_42791a;	/* 4278ed: je 0x42791a */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 4278ef: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4278f4: test eax, eax */
	if (m->zf) goto L_42791b;	/* 4278f6: je 0x42791b */
	m->eax = M32((DWORD)(0x4dde8cu));	/* 4278f8: mov eax, dword ptr [0x4dde8c] */
	m->ecx = M32((DWORD)(0x4dde88u));	/* 4278fd: mov ecx, dword ptr [0x4dde88] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 427903: mov edx, dword ptr [0x4dde84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427909: push eax */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42790a: mov eax, dword ptr [0x4dde80] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42790f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427910: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427911: push eax */
	m->esp -= 4; M32(m->esp) = 0x427917u; native_call(m, 0x428c30u);	/* 427912: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427917: add esp, 0x10 */
L_42791a:
	m->esp += 4 + 0; return;	/* 42791a: ret  */
L_42791b:
	native_call(m, 0x425cd0u); return;	/* 42791b: jmp 0x425cd0 */
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
