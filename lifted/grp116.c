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

static void lift_40f870(X86 *m);

/* armc_40f870 (0x40f870), lifted by tools/lift.py */
static void lift_40f870(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbe48u));	/* 40f870: mov eax, dword ptr [0x4dbe48] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40f875: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40f876: push edi */
	m->edi = M32((DWORD)(m->esp + 0xcu));	/* 40f877: mov edi, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->esi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40f87b: or esi, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f87e: cmp eax, edi */
	if (m->zf) goto L_40f8f9;	/* 40f880: je 0x40f8f9 */
	{ DWORD a_ = m->edi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f882: cmp edi, 5 */
	M32((DWORD)(0x4dbe48u)) = m->edi;	/* 40f885: mov dword ptr [0x4dbe48], edi */
	if (!m->cf && !m->zf) goto L_40f904;	/* 40f88b: ja 0x40f904 */
	switch (m->edi) { case 0: goto L_40f894; case 1: goto L_40f89c; case 2: goto L_40f8a4; case 3: goto L_40f8ac; case 4: goto L_40f8b4; case 5: goto L_40f8fc; default: abort(); }	/* 40f88d: jmp dword ptr [edi*4 + 0x40f930] */
L_40f894:
	m->esi = M32((DWORD)(0x4dcb20u));	/* 40f894: mov esi, dword ptr [0x4dcb20] */
	goto L_40f909;	/* 40f89a: jmp 0x40f909 */
L_40f89c:
	m->esi = M32((DWORD)(0x4dcb24u));	/* 40f89c: mov esi, dword ptr [0x4dcb24] */
	goto L_40f909;	/* 40f8a2: jmp 0x40f909 */
L_40f8a4:
	m->esi = M32((DWORD)(0x4dcb28u));	/* 40f8a4: mov esi, dword ptr [0x4dcb28] */
	goto L_40f909;	/* 40f8aa: jmp 0x40f909 */
L_40f8ac:
	m->esi = M32((DWORD)(0x4dcb2cu));	/* 40f8ac: mov esi, dword ptr [0x4dcb2c] */
	goto L_40f909;	/* 40f8b2: jmp 0x40f909 */
L_40f8b4:
	m->esi = M32((DWORD)(0x4dcb18u));	/* 40f8b4: mov esi, dword ptr [0x4dcb18] */
L_40f8ba:
	m->edx = M32((DWORD)(0x4dc778u));	/* 40f8ba: mov edx, dword ptr [0x4dc778] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f8c0: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40f8c2: test edx, edx */
	if (m->zf || m->sf != m->of) goto L_40f8dc;	/* 40f8c4: jle 0x40f8dc */
	m->ecx = 0x4dcca4u;	/* 40f8c6: mov ecx, 0x4dcca4 */
L_40f8cb:
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->ecx + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f8cb: cmp esi, dword ptr [ecx] */
	if (!m->zf) goto L_40f8d4;	/* 40f8cd: jne 0x40f8d4 */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 40f8cf: mov dword ptr [0x4dc77c], eax */
L_40f8d4:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40f8d4: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40f8d5: add ecx, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f8d8: cmp eax, edx */
	if (m->sf != m->of) goto L_40f8cb;	/* 40f8da: jl 0x40f8cb */
L_40f8dc:
	{ DWORD a_ = m->edi, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f8dc: cmp edi, 3 */
	if (!m->zf && m->sf == m->of) goto L_40f8f4;	/* 40f8df: jg 0x40f8f4 */
	m->eax = M32((DWORD)(0x9087b4u));	/* 40f8e1: mov eax, dword ptr [0x9087b4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40f8e6: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f8e7: push 0 */
	m->ecx = (DWORD)(m->eax + 0x1f36c8u);	/* 40f8e9: lea ecx, [eax + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x40f8f4u; native_call(m, 0x45e880u);	/* 40f8ef: call 0x45e880 */
L_40f8f4:
	m->esp -= 4; M32(m->esp) = 0x40f8f9u; native_call(m, 0x40f950u);	/* 40f8f4: call 0x40f950 */
L_40f8f9:
	m->edi = M32(m->esp); m->esp += 4;	/* 40f8f9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40f8fa: pop esi */
	m->esp += 4 + 0; return;	/* 40f8fb: ret  */
L_40f8fc:
	m->esi = M32((DWORD)(0x4dcb1cu));	/* 40f8fc: mov esi, dword ptr [0x4dcb1c] */
	goto L_40f8ba;	/* 40f902: jmp 0x40f8ba */
L_40f904:
	{ DWORD a_ = m->edi, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f904: cmp edi, 3 */
	if (!m->zf && m->sf == m->of) goto L_40f8ba;	/* 40f907: jg 0x40f8ba */
L_40f909:
	m->edx = M32((DWORD)(0x4dc244u));	/* 40f909: mov edx, dword ptr [0x4dc244] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f90f: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40f911: test edx, edx */
	if (m->zf || m->sf != m->of) goto L_40f8dc;	/* 40f913: jle 0x40f8dc */
	m->ecx = 0x4dc79cu;	/* 40f915: mov ecx, 0x4dc79c */
L_40f91a:
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->ecx + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f91a: cmp esi, dword ptr [ecx] */
	if (!m->zf) goto L_40f923;	/* 40f91c: jne 0x40f923 */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 40f91e: mov dword ptr [0x4dc77c], eax */
L_40f923:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40f923: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40f924: add ecx, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f927: cmp eax, edx */
	if (m->sf != m->of) goto L_40f91a;	/* 40f929: jl 0x40f91a */
	goto L_40f8dc;	/* 40f92b: jmp 0x40f8dc */
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
