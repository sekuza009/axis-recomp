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

static void lift_454560(X86 *m);

/* net_454560 (0x454560), lifted by tools/lift.py */
static void lift_454560(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454560: sub esp, 8 */
	m->eax = M32((DWORD)(0xa0bb10u));	/* 454563: mov eax, dword ptr [0xa0bb10] */
	m->ecx = M32((DWORD)(0xa0bf1cu));	/* 454568: mov ecx, dword ptr [0xa0bf1c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45456e: push esi */
	m->esi = M32((DWORD)(0x4a917cu));	/* 45456f: mov esi, dword ptr [0x4a917c] */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 454575: mov dword ptr [esp + 4], eax */
	M32((DWORD)(m->esp + 0x8u)) = m->ecx;	/* 454579: mov dword ptr [esp + 8], ecx */
L_45457d:
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45457d: push -1 */
	m->edx = (DWORD)(m->esp + 0x8u);	/* 45457f: lea edx, [esp + 8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 454583: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454585: push edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 454586: push 2 */
	m->esp -= 4; M32(m->esp) = 0x45458au; native_call(m, m->esi);	/* 454588: call esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45458a: test eax, eax */
	if (!m->zf) goto L_454595;	/* 45458c: jne 0x454595 */
	m->esp -= 4; M32(m->esp) = 0x454593u; native_call(m, 0x4545b0u);	/* 45458e: call 0x4545b0 */
	goto L_45457d;	/* 454593: jmp 0x45457d */
L_454595:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 454595: cmp eax, 1 */
	if (!m->zf) goto L_45457d;	/* 454598: jne 0x45457d */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45459a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4545a2u; native_call(m, M32(0x4a9180u));	/* 45459c: call dword ptr [0x4a9180] */
	abort();	/* the last call does not return */
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
