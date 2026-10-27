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

static void lift_462050(X86 *m);
static void lift_4202d0(X86 *m);

/* FUN_004202d0 (0x4202d0), lifted by tools/lift.py */
static void lift_4202d0(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x4202d5u; native_call(m, 0x4572b0u);	/* 4202d0: call 0x4572b0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9da434u)));	/* 4202d5: fld dword ptr [0x9da434] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4202db: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4202e1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4202e3: test ah, 0x41 */
	if (!m->zf) goto L_4202fa;	/* 4202e6: jne 0x4202fa */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9da434u)));	/* 4202e8: fld dword ptr [0x9da434] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 4202ee: fsub dword ptr [0x4b071c] */
	MF((DWORD)(0x9da434u)) = (float)ST(0); FPOP();	/* 4202f4: fstp dword ptr [0x9da434] */
L_4202fa:
	native_call(m, 0x420280u); return;	/* 4202fa: jmp 0x420280 */
}

/* main_462050 (0x462050), lifted by tools/lift.py */
static void lift_462050(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 462050: push esi */
	m->esi = m->ecx;	/* 462051: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc20u));	/* 462053: mov eax, dword ptr [esi + 0x233cc20] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462059: dec eax */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46205a: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_4620c6;	/* 46205d: ja 0x4620c6 */
	switch (m->eax) { case 0: goto L_462066; case 1: goto L_462075; case 2: goto L_46209a; case 3: goto L_4620b4; default: abort(); }	/* 46205f: jmp dword ptr [eax*4 + 0x4620d0] */
L_462066:
	m->ecx = m->esi;	/* 462066: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x46206du; native_call(m, 0x468750u);	/* 462068: call 0x468750 */
	M32((DWORD)(m->esi + 0x233cc20u)) = m->eax;	/* 46206d: mov dword ptr [esi + 0x233cc20], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 462073: pop esi */
	m->esp += 4 + 0; return;	/* 462074: ret  */
L_462075:
	m->ecx = m->esi;	/* 462075: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x46207cu; native_call(m, 0x48b200u);	/* 462077: call 0x48b200 */
	M32((DWORD)(m->esi + 0x233cc20u)) = m->eax;	/* 46207c: mov dword ptr [esi + 0x233cc20], eax */
	m->eax = M32((DWORD)(m->esi + 0x233c9e8u));	/* 462082: mov eax, dword ptr [esi + 0x233c9e8] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462088: cmp eax, 1 */
	if (!m->zf) goto L_4620c6;	/* 46208b: jne 0x4620c6 */
	m->esp -= 4; M32(m->esp) = 0x462092u; native_call(m, 0x4685d0u);	/* 46208d: call 0x4685d0 */
	m->eax = M32((DWORD)(m->esi + 0x233cc20u));	/* 462092: mov eax, dword ptr [esi + 0x233cc20] */
	m->esi = M32(m->esp); m->esp += 4;	/* 462098: pop esi */
	m->esp += 4 + 0; return;	/* 462099: ret  */
L_46209a:
	m->ecx = m->esi;	/* 46209a: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4620a1u; native_call(m, 0x48a370u);	/* 46209c: call 0x48a370 */
	M32((DWORD)(m->esi + 0x233cc20u)) = m->eax;	/* 4620a1: mov dword ptr [esi + 0x233cc20], eax */
	m->esp -= 4; M32(m->esp) = 0x4620acu; native_call(m, 0x4685d0u);	/* 4620a7: call 0x4685d0 */
	m->eax = M32((DWORD)(m->esi + 0x233cc20u));	/* 4620ac: mov eax, dword ptr [esi + 0x233cc20] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4620b2: pop esi */
	m->esp += 4 + 0; return;	/* 4620b3: ret  */
L_4620b4:
	m->ecx = m->esi;	/* 4620b4: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4620bbu; native_call(m, 0x487f00u);	/* 4620b6: call 0x487f00 */
	M32((DWORD)(m->esi + 0x233cc20u)) = m->eax;	/* 4620bb: mov dword ptr [esi + 0x233cc20], eax */
	m->esp -= 4; M32(m->esp) = 0x4620c6u; native_call(m, 0x4685d0u);	/* 4620c1: call 0x4685d0 */
L_4620c6:
	m->eax = M32((DWORD)(m->esi + 0x233cc20u));	/* 4620c6: mov eax, dword ptr [esi + 0x233cc20] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4620cc: pop esi */
	m->esp += 4 + 0; return;	/* 4620cd: ret  */
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
