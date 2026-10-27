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

static void lift_44cdd0(X86 *m);

/* menu_44cdd0 (0x44cdd0), lifted by tools/lift.py */
static void lift_44cdd0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 44cdd0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44cdd5: test eax, eax */
	if (!m->zf) goto L_44ce3a;	/* 44cdd7: jne 0x44ce3a */
	m->eax = M32((DWORD)(0x9f6838u));	/* 44cdd9: mov eax, dword ptr [0x9f6838] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44cdde: test eax, eax */
	if (m->zf) goto L_44ce3b;	/* 44cde0: je 0x44ce3b */
	{ DWORD a_ = M32((DWORD)(0x9f8e54u)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cde2: cmp dword ptr [0x9f8e54], 5 */
	if (m->zf) goto L_44ce3b;	/* 44cde9: je 0x44ce3b */
	m->eax = M32((DWORD)(0x6803a0u));	/* 44cdeb: mov eax, dword ptr [0x6803a0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cdf0: push eax */
	m->esp -= 4; M32(m->esp) = 0x44cdf6u; native_call(m, 0x401600u);	/* 44cdf1: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cdf6: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cdf9: cmp eax, 1 */
	if (m->zf) goto L_44ce12;	/* 44cdfc: je 0x44ce12 */
	m->ecx = M32((DWORD)(0x9dae70u));	/* 44cdfe: mov ecx, dword ptr [0x9dae70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ce04: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44ce0au; native_call(m, 0x401600u);	/* 44ce05: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ce0a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ce0d: cmp eax, 1 */
	if (!m->zf) goto L_44ce3a;	/* 44ce10: jne 0x44ce3a */
L_44ce12:
	M32((DWORD)(0x9f8e54u)) = 0x5u;	/* 44ce12: mov dword ptr [0x9f8e54], 5 */
	M32((DWORD)(0x9f8f30u)) = 0x0u;	/* 44ce1c: mov dword ptr [0x9f8f30], 0 */
	M32((DWORD)(0x9f8f14u)) = 0x42c80000u;	/* 44ce26: mov dword ptr [0x9f8f14], 0x42c80000 */
	M32((DWORD)(0x9f8e50u)) = 0x3d4ccccdu;	/* 44ce30: mov dword ptr [0x9f8e50], 0x3d4ccccd */
L_44ce3a:
	m->esp += 4 + 0; return;	/* 44ce3a: ret  */
L_44ce3b:
	m->edx = M32((DWORD)(0x9f8f10u));	/* 44ce3b: mov edx, dword ptr [0x9f8f10] */
	m->eax = (DWORD)(m->edx + 0xffffffffu);	/* 44ce41: lea eax, [edx - 1] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ce44: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_44ce3a;	/* 44ce47: ja 0x44ce3a */
	switch (m->eax) { case 0: goto L_44ce50; case 1: goto L_44ce55; case 2: goto L_44ce5a; case 3: goto L_44ce3a; case 4: goto L_44ce5f; case 5: goto L_44ce64; default: abort(); }	/* 44ce49: jmp dword ptr [eax*4 + 0x44ce6c] */
L_44ce50:
	native_call(m, 0x44c600u); return;	/* 44ce50: jmp 0x44c600 */
L_44ce55:
	native_call(m, 0x44c850u); return;	/* 44ce55: jmp 0x44c850 */
L_44ce5a:
	native_call(m, 0x44c8c0u); return;	/* 44ce5a: jmp 0x44c8c0 */
L_44ce5f:
	native_call(m, 0x44ca90u); return;	/* 44ce5f: jmp 0x44ca90 */
L_44ce64:
	native_call(m, 0x44cc60u); return;	/* 44ce64: jmp 0x44cc60 */
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
