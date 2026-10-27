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

static void lift_460c20(X86 *m);
static void lift_460c40(X86 *m);

/* Console_ctor (0x460c40), lifted by tools/lift.py */
static void lift_460c40(X86 *m)
{
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 460c40: push -1 */
	{ DWORD v_ = 0x4a8b76u; m->esp -= 4; M32(m->esp) = v_; }	/* 460c42: push 0x4a8b76 */
	m->eax = M32((DWORD)&g_lift_fs0);	/* 460c47: mov eax, dword ptr fs:[0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 460c4d: push eax */
	M32((DWORD)&g_lift_fs0) = m->esp;	/* 460c4e: mov dword ptr fs:[0], esp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 460c55: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 460c56: push esi */
	m->esi = m->ecx;	/* 460c57: mov esi, ecx */
	M32((DWORD)(m->esp + 0x4u)) = m->esi;	/* 460c59: mov dword ptr [esp + 4], esi */
	M32((DWORD)(m->esi + 0x0u)) = 0x4aa238u;	/* 460c5d: mov dword ptr [esi], 0x4aa238 */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 460c63: lea ecx, [esi + 0x1f36c8] */
	M32((DWORD)(m->esp + 0x10u)) = 0x1u;	/* 460c69: mov dword ptr [esp + 0x10], 1 */
	m->esp -= 4; M32(m->esp) = 0x460c76u; native_call(m, 0x46ff70u);	/* 460c71: call 0x46ff70 */
	m->ecx = (DWORD)(m->esi + 0x74u);	/* 460c76: lea ecx, [esi + 0x74] */
	M8((DWORD)(m->esp + 0x10u)) = (BYTE)(0x0u);	/* 460c79: mov byte ptr [esp + 0x10], 0 */
	m->esp -= 4; M32(m->esp) = 0x460c83u; native_call(m, 0x483fb0u);	/* 460c7e: call 0x483fb0 */
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 460c83: lea ecx, [esi + 0xc] */
	M32((DWORD)(m->esp + 0x10u)) = 0xffffffffu;	/* 460c86: mov dword ptr [esp + 0x10], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x460c93u; native_call(m, 0x487470u);	/* 460c8e: call 0x487470 */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 460c93: mov ecx, dword ptr [esp + 8] */
	m->esi = M32(m->esp); m->esp += 4;	/* 460c97: pop esi */
	M32((DWORD)&g_lift_fs0) = m->ecx;	/* 460c98: mov dword ptr fs:[0], ecx */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460c9f: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 460ca2: ret  */
}

/* Console_deletingDtor (0x460c20), lifted by tools/lift.py */
static void lift_460c20(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 460c20: push esi */
	m->esi = m->ecx;	/* 460c21: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x460c28u; lift_460c40(m);	/* 460c23: call 0x460c40 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x8u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 460c28: test byte ptr [esp + 8], 1 */
	if (m->zf) goto L_460c38;	/* 460c2d: je 0x460c38 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 460c2f: push esi */
	m->esp -= 4; M32(m->esp) = 0x460c35u; native_call(m, 0x49ef24u);	/* 460c30: call 0x49ef24 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460c35: add esp, 4 */
L_460c38:
	m->eax = m->esi;	/* 460c38: mov eax, esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 460c3a: pop esi */
	m->esp += 4 + 4; return;	/* 460c3b: ret 4 */
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
