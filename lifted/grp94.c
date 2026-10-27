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

static void lift_430bf0(X86 *m);

/* intro_430bf0 (0x430bf0), lifted by tools/lift.py */
static void lift_430bf0(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 430bf0: push edi */
	m->ecx = 0x300u;	/* 430bf1: mov ecx, 0x300 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 430bf6: xor eax, eax */
	m->edi = 0x67ef38u;	/* 430bf8: mov edi, 0x67ef38 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 430bfd: rep stosd dword ptr es:[edi], eax */
	m->esp -= 4; M32(m->esp) = 0x430c04u; native_call(m, 0x430ab0u);	/* 430bff: call 0x430ab0 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 430c04: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x430c0fu; native_call(m, 0x41f100u);	/* 430c0a: call 0x41f100 */
	{ DWORD v_ = 0x40000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c0f: push 0x40000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c14: push 0 */
	m->esp -= 4; M32(m->esp) = 0x430c1bu; native_call(m, 0x41e730u);	/* 430c16: call 0x41e730 */
	m->esp -= 4; M32(m->esp) = 0x430c20u; native_call(m, 0x42f2b0u);	/* 430c1b: call 0x42f2b0 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 430c20: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x430c2bu; native_call(m, 0x41f100u);	/* 430c26: call 0x41f100 */
	{ DWORD v_ = 0x40000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c2b: push 0x40000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c30: push 0 */
	m->esp -= 4; M32(m->esp) = 0x430c37u; native_call(m, 0x41e730u);	/* 430c32: call 0x41e730 */
	m->esp -= 4; M32(m->esp) = 0x430c3cu; native_call(m, 0x42f500u);	/* 430c37: call 0x42f500 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 430c3c: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x430c47u; native_call(m, 0x41f100u);	/* 430c42: call 0x41f100 */
	{ DWORD v_ = 0x40000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c47: push 0x40000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c4c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x430c53u; native_call(m, 0x41e730u);	/* 430c4e: call 0x41e730 */
	m->esp -= 4; M32(m->esp) = 0x430c58u; native_call(m, 0x42f690u);	/* 430c53: call 0x42f690 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 430c58: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x430c63u; native_call(m, 0x41f100u);	/* 430c5e: call 0x41f100 */
	{ DWORD v_ = 0x40000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c63: push 0x40000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c68: push 0 */
	m->esp -= 4; M32(m->esp) = 0x430c6fu; native_call(m, 0x41e730u);	/* 430c6a: call 0x41e730 */
	m->esp -= 4; M32(m->esp) = 0x430c74u; native_call(m, 0x42f8e0u);	/* 430c6f: call 0x42f8e0 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 430c74: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x430c7fu; native_call(m, 0x41f100u);	/* 430c7a: call 0x41f100 */
	{ DWORD v_ = 0x40000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c7f: push 0x40000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 430c84: push 0 */
	m->esp -= 4; M32(m->esp) = 0x430c8bu; native_call(m, 0x41e730u);	/* 430c86: call 0x41e730 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430c8b: add esp, 0x28 */
	m->esp -= 4; M32(m->esp) = 0x430c93u; native_call(m, 0x430bd0u);	/* 430c8e: call 0x430bd0 */
	{ DWORD a_ = M32((DWORD)(0x4dda34u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dda34u)) = r_; }	/* 430c93: inc dword ptr [0x4dda34] */
	m->esp -= 4; M32(m->esp) = 0x430c9eu; native_call(m, 0x41f100u);	/* 430c99: call 0x41f100 */
	m->edi = M32(m->esp); m->esp += 4;	/* 430c9e: pop edi */
	m->esp += 4 + 0; return;	/* 430c9f: ret  */
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
