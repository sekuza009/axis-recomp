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

static void lift_452a30(X86 *m);
static void lift_452bd0(X86 *m);
static void lift_451b80(X86 *m);
static void lift_4060f0(X86 *m);
static void lift_4546d0(X86 *m);

/* net_startThread (0x4546d0), lifted by tools/lift.py */
static void lift_4546d0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4546d0: push esi */
	m->esi = M32((DWORD)(0x4a9170u));	/* 4546d1: mov esi, dword ptr [0x4a9170] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4546d7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4546d9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4546db: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4546dd: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4546e1u; native_call(m, m->esi);	/* 4546df: call esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4546e1: test eax, eax */
	M32((DWORD)(0xa0bb10u)) = m->eax;	/* 4546e3: mov dword ptr [0xa0bb10], eax */
	if (!m->zf) goto L_4546ec;	/* 4546e8: jne 0x4546ec */
	m->esi = M32(m->esp); m->esp += 4;	/* 4546ea: pop esi */
	m->esp += 4 + 0; return;	/* 4546eb: ret  */
L_4546ec:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4546ec: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4546ee: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4546f0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4546f2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4546f6u; native_call(m, m->esi);	/* 4546f4: call esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4546f6: test eax, eax */
	M32((DWORD)(0xa0bf1cu)) = m->eax;	/* 4546f8: mov dword ptr [0xa0bf1c], eax */
	if (!m->zf) goto L_454701;	/* 4546fd: jne 0x454701 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4546ff: pop esi */
	m->esp += 4 + 0; return;	/* 454700: ret  */
L_454701:
	{ DWORD v_ = 0xa0d784u; m->esp -= 4; M32(m->esp) = v_; }	/* 454701: push 0xa0d784 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 454706: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 454708: push 0 */
	{ DWORD v_ = 0x454560u; m->esp -= 4; M32(m->esp) = v_; }	/* 45470a: push 0x454560 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45470f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 454711: push 0 */
	m->esp -= 4; M32(m->esp) = 0x454719u; native_call(m, M32(0x4a9174u));	/* 454713: call dword ptr [0x4a9174] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454719: test eax, eax */
	M32((DWORD)(0xa0d788u)) = m->eax;	/* 45471b: mov dword ptr [0xa0d788], eax */
	if (!m->zf) goto L_454724;	/* 454720: jne 0x454724 */
	m->esi = M32(m->esp); m->esp += 4;	/* 454722: pop esi */
	m->esp += 4 + 0; return;	/* 454723: ret  */
L_454724:
	m->eax = M32((DWORD)(0xa0bb10u));	/* 454724: mov eax, dword ptr [0xa0bb10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454729: push eax */
	m->esp -= 4; M32(m->esp) = 0x454730u; native_call(m, M32(0x4a9178u));	/* 45472a: call dword ptr [0x4a9178] */
	m->eax = 0x1u;	/* 454730: mov eax, 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 454735: pop esi */
	m->esp += 4 + 0; return;	/* 454736: ret  */
}

/* net_452a30 (0x452a30), lifted by tools/lift.py */
static void lift_452a30(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452a30: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452a31: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 452a32: push edi */
	m->edi = M32((DWORD)(0x4a9184u));	/* 452a33: mov edi, dword ptr [0x4a9184] */
	m->esp -= 4; M32(m->esp) = 0x452a3bu; native_call(m, m->edi);	/* 452a39: call edi */
	m->ebx = m->eax;	/* 452a3b: mov ebx, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 452a3d: xor esi, esi */
L_452a3f:
	m->eax = M32((DWORD)(0xa055f8u));	/* 452a3f: mov eax, dword ptr [0xa055f8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452a44: push 0 */
	{ DWORD v_ = 0x5bu; m->esp -= 4; M32(m->esp) = v_; }	/* 452a46: push 0x5b */
	{ DWORD v_ = 0xa05260u; m->esp -= 4; M32(m->esp) = v_; }	/* 452a48: push 0xa05260 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452a4d: push eax */
	m->esp -= 4; M32(m->esp) = 0x452a53u; native_call(m, 0x4a82d4u);	/* 452a4e: call 0x4a82d4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452a53: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_452a59;	/* 452a55: jle 0x452a59 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 452a57: add esi, eax */
L_452a59:
	m->esp -= 4; M32(m->esp) = 0x452a5bu; native_call(m, m->edi);	/* 452a59: call edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452a5b: sub eax, ebx */
	{ DWORD a_ = m->eax, b_ = 0xbb8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452a5d: cmp eax, 0xbb8 */
	if (!m->cf && !m->zf) goto L_452a69;	/* 452a62: ja 0x452a69 */
	{ DWORD a_ = m->esi, b_ = 0x5bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452a64: cmp esi, 0x5b */
	if (m->cf) goto L_452a3f;	/* 452a67: jb 0x452a3f */
L_452a69:
	m->eax = M32((DWORD)(0xa052aau));	/* 452a69: mov eax, dword ptr [0xa052aa] */
	m->edi = M32(m->esp); m->esp += 4;	/* 452a6e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452a6f: pop esi */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452a70: cmp eax, 3 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452a73: pop ebx */
	if (!m->cf && !m->zf) goto L_452ada;	/* 452a74: ja 0x452ada */
	switch (m->eax) { case 0: goto L_452a7d; case 1: goto L_452a8b; case 2: goto L_452ab1; case 3: goto L_452ac6; default: abort(); }	/* 452a76: jmp dword ptr [eax*4 + 0x452adc] */
L_452a7d:
	{ DWORD v_ = 0xa05260u; m->esp -= 4; M32(m->esp) = v_; }	/* 452a7d: push 0xa05260 */
	m->esp -= 4; M32(m->esp) = 0x452a87u; native_call(m, 0x452af0u);	/* 452a82: call 0x452af0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 452a87: add esp, 4 */
	m->esp += 4 + 0; return;	/* 452a8a: ret  */
L_452a8b:
	m->ecx = M32((DWORD)(0xa0b368u));	/* 452a8b: mov ecx, dword ptr [0xa0b368] */
	M32((DWORD)(0xa0d79cu)) = m->ecx;	/* 452a91: mov dword ptr [0xa0d79c], ecx */
	m->esp -= 4; M32(m->esp) = 0x452a9cu; lift_4546d0(m);	/* 452a97: call 0x4546d0 */
	M32((DWORD)(0xa0b36cu)) = 0xcau;	/* 452a9c: mov dword ptr [0xa0b36c], 0xca */
	M32((DWORD)(0xa0b300u)) = 0x0u;	/* 452aa6: mov dword ptr [0xa0b300], 0 */
	m->esp += 4 + 0; return;	/* 452ab0: ret  */
L_452ab1:
	M32((DWORD)(0xa0b36cu)) = 0xcbu;	/* 452ab1: mov dword ptr [0xa0b36c], 0xcb */
	M32((DWORD)(0xa0b300u)) = 0x0u;	/* 452abb: mov dword ptr [0xa0b300], 0 */
	m->esp += 4 + 0; return;	/* 452ac5: ret  */
L_452ac6:
	M32((DWORD)(0xa0b36cu)) = 0x29u;	/* 452ac6: mov dword ptr [0xa0b36c], 0x29 */
	M32((DWORD)(0xa0b300u)) = 0x0u;	/* 452ad0: mov dword ptr [0xa0b300], 0 */
L_452ada:
	m->esp += 4 + 0; return;	/* 452ada: ret  */
}

/* net_452bd0 (0x452bd0), lifted by tools/lift.py */
static void lift_452bd0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452bd0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452bd1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 452bd2: push edi */
	m->edi = M32((DWORD)(0x4a9184u));	/* 452bd3: mov edi, dword ptr [0x4a9184] */
	m->esp -= 4; M32(m->esp) = 0x452bdbu; native_call(m, m->edi);	/* 452bd9: call edi */
	m->ebx = m->eax;	/* 452bdb: mov ebx, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 452bdd: xor esi, esi */
L_452bdf:
	m->eax = M32((DWORD)(0xa05630u));	/* 452bdf: mov eax, dword ptr [0xa05630] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452be4: push 0 */
	{ DWORD v_ = 0x79u; m->esp -= 4; M32(m->esp) = v_; }	/* 452be6: push 0x79 */
	{ DWORD v_ = 0xa0b280u; m->esp -= 4; M32(m->esp) = v_; }	/* 452be8: push 0xa0b280 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452bed: push eax */
	m->esp -= 4; M32(m->esp) = 0x452bf3u; native_call(m, 0x4a82d4u);	/* 452bee: call 0x4a82d4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452bf3: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_452bf9;	/* 452bf5: jle 0x452bf9 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 452bf7: add esi, eax */
L_452bf9:
	m->esp -= 4; M32(m->esp) = 0x452bfbu; native_call(m, m->edi);	/* 452bf9: call edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452bfb: sub eax, ebx */
	{ DWORD a_ = m->eax, b_ = 0xbb8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452bfd: cmp eax, 0xbb8 */
	if (!m->cf && !m->zf) goto L_452c09;	/* 452c02: ja 0x452c09 */
	{ DWORD a_ = m->esi, b_ = 0x79u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452c04: cmp esi, 0x79 */
	if (m->cf) goto L_452bdf;	/* 452c07: jb 0x452bdf */
L_452c09:
	m->eax = M32((DWORD)(0xa0b2e8u));	/* 452c09: mov eax, dword ptr [0xa0b2e8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 452c0e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452c0f: pop esi */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452c10: cmp eax, 3 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452c13: pop ebx */
	if (!m->cf && !m->zf) goto L_452c65;	/* 452c14: ja 0x452c65 */
	switch (m->eax) { case 0: goto L_452c1d; case 1: goto L_452c2b; case 2: goto L_452c51; case 3: goto L_452c51; default: abort(); }	/* 452c16: jmp dword ptr [eax*4 + 0x452c68] */
L_452c1d:
	{ DWORD v_ = 0xa0b280u; m->esp -= 4; M32(m->esp) = v_; }	/* 452c1d: push 0xa0b280 */
	m->esp -= 4; M32(m->esp) = 0x452c27u; native_call(m, 0x452c80u);	/* 452c22: call 0x452c80 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 452c27: add esp, 4 */
	m->esp += 4 + 0; return;	/* 452c2a: ret  */
L_452c2b:
	m->ecx = M32((DWORD)(0xa0b358u));	/* 452c2b: mov ecx, dword ptr [0xa0b358] */
	M32((DWORD)(0xa0d79cu)) = m->ecx;	/* 452c31: mov dword ptr [0xa0d79c], ecx */
	m->esp -= 4; M32(m->esp) = 0x452c3cu; lift_4546d0(m);	/* 452c37: call 0x4546d0 */
	M32((DWORD)(0xa0b34cu)) = 0xcau;	/* 452c3c: mov dword ptr [0xa0b34c], 0xca */
	M32((DWORD)(0xa0b300u)) = 0x0u;	/* 452c46: mov dword ptr [0xa0b300], 0 */
	m->esp += 4 + 0; return;	/* 452c50: ret  */
L_452c51:
	M32((DWORD)(0xa0b34cu)) = 0x28u;	/* 452c51: mov dword ptr [0xa0b34c], 0x28 */
	M32((DWORD)(0xa0b300u)) = 0x0u;	/* 452c5b: mov dword ptr [0xa0b300], 0 */
L_452c65:
	m->esp += 4 + 0; return;	/* 452c65: ret  */
}

/* net_connect (0x451b80), lifted by tools/lift.py */
static void lift_451b80(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451b80: sub esp, 0x1a0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451b86: push esi */
	m->esi = M32((DWORD)(m->esp + 0x1a8u));	/* 451b87: mov esi, dword ptr [esp + 0x1a8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451b8e: push esi */
	m->esp -= 4; M32(m->esp) = 0x451b94u; native_call(m, 0x451600u);	/* 451b8f: call 0x451600 */
	m->eax = m->esi;	/* 451b94: mov eax, esi */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451b96: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 451b99: sub eax, 0x64 */
	M32((DWORD)(0xa0b2fcu)) = 0x1u;	/* 451b9c: mov dword ptr [0xa0b2fc], 1 */
	if (m->zf) goto L_451cfa;	/* 451ba6: je 0x451cfa */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 451bac: dec eax */
	if (!m->zf) goto L_451e44;	/* 451bad: jne 0x451e44 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 451bb3: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451bb7: push eax */
	{ DWORD v_ = 0x202u; m->esp -= 4; M32(m->esp) = v_; }	/* 451bb8: push 0x202 */
	m->esp -= 4; M32(m->esp) = 0x451bc2u; native_call(m, 0x4a82c2u);	/* 451bbd: call 0x4a82c2 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 451bc2: test eax, eax */
	if (!m->zf) goto L_451e56;	/* 451bc4: jne 0x451e56 */
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->esp + 0x14u))) & 0xffff);	/* 451bca: mov ax, word ptr [esp + 0x14] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 451bcf: cmp al, 2 */
	if (!m->zf) goto L_451e51;	/* 451bd1: jne 0x451e51 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451bd7: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 451bd9: mov cl, ah */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 451bdb: cmp cl, al */
	if (!m->zf) goto L_451e51;	/* 451bdd: jne 0x451e51 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 451be3: xor esi, esi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451be5: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 451be6: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 451be8: push 2 */
	m->esp -= 4; M32(m->esp) = 0x451befu; native_call(m, 0x4a82bcu);	/* 451bea: call 0x4a82bc */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451bef: cmp eax, -1 */
	M32((DWORD)(0xa05630u)) = m->eax;	/* 451bf2: mov dword ptr [0xa05630], eax */
	if (!m->zf) goto L_451c0d;	/* 451bf7: jne 0x451c0d */
	m->esp -= 4; M32(m->esp) = 0x451bfeu; native_call(m, 0x4a8292u);	/* 451bf9: call 0x4a8292 */
	m->esp -= 4; M32(m->esp) = 0x451c03u; native_call(m, 0x451e60u);	/* 451bfe: call 0x451e60 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451c03: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 451c05: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451c06: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451c0c: ret  */
L_451c0d:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 451c0d: xor edx, edx */
	m->ecx = (DWORD)(m->esp + 0x4u);	/* 451c0f: lea ecx, [esp + 4] */
	M32((DWORD)(m->esp + 0x4u)) = m->edx;	/* 451c13: mov dword ptr [esp + 4], edx */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 451c17: push 0x10 */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 451c19: mov dword ptr [esp + 0xc], edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451c1d: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 451c1e: mov dword ptr [esp + 0x14], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451c22: push eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 451c23: mov dword ptr [esp + 0x1c], edx */
	M16((DWORD)(m->esp + 0x10u)) = (WORD)(0x2u);	/* 451c27: mov word ptr [esp + 0x10], 2 */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 451c2e: mov dword ptr [esp + 0x14], esi */
	m->esp -= 4; M32(m->esp) = 0x451c37u; native_call(m, 0x4a82b6u);	/* 451c32: call 0x4a82b6 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451c37: cmp eax, -1 */
	if (m->zf) goto L_451e56;	/* 451c3a: je 0x451e56 */
	{ DWORD v_ = 0xa055e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 451c40: push 0xa055e4 */
	M16((DWORD)(m->esp + 0x8u)) = (WORD)(0x2u);	/* 451c45: mov word ptr [esp + 8], 2 */
	m->esp -= 4; M32(m->esp) = 0x451c51u; native_call(m, 0x4a82b0u);	/* 451c4c: call 0x4a82b0 */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(0xa05326u))) & 0xffff);	/* 451c51: mov dx, word ptr [0xa05326] */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 451c58: mov dword ptr [esp + 8], eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451c5c: push edx */
	m->esp -= 4; M32(m->esp) = 0x451c62u; native_call(m, 0x4a82aau);	/* 451c5d: call 0x4a82aa */
	M16((DWORD)(m->esp + 0x6u)) = (WORD)((m->eax & 0xffff));	/* 451c62: mov word ptr [esp + 6], ax */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 451c67: mov eax, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451c6b: cmp eax, -1 */
	if (!m->zf) goto L_451c8d;	/* 451c6e: jne 0x451c8d */
	{ DWORD v_ = 0xa055e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 451c70: push 0xa055e4 */
	m->esp -= 4; M32(m->esp) = 0x451c7au; native_call(m, 0x4a82a4u);	/* 451c75: call 0x4a82a4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451c7a: cmp eax, esi */
	if (m->zf) goto L_451e07;	/* 451c7c: je 0x451e07 */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 451c82: mov eax, dword ptr [eax + 0xc] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 451c85: mov ecx, dword ptr [eax] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 451c87: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 451c89: mov dword ptr [esp + 8], edx */
L_451c8d:
	m->ecx = M32((DWORD)(0xa05630u));	/* 451c8d: mov ecx, dword ptr [0xa05630] */
	m->eax = (DWORD)(m->esp + 0x4u);	/* 451c93: lea eax, [esp + 4] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 451c97: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451c99: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451c9a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x451ca0u; native_call(m, 0x4a829eu);	/* 451c9b: call 0x4a829e */
	{ DWORD a_ = m->eax, b_ = 0x274du & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451ca0: cmp eax, 0x274d */
	if (!m->zf) goto L_451cc4;	/* 451ca5: jne 0x451cc4 */
	m->esp -= 4; M32(m->esp) = 0x451cacu; native_call(m, 0x4a8292u);	/* 451ca7: call 0x4a8292 */
	m->esp -= 4; M32(m->esp) = 0x451cb1u; native_call(m, 0x451e60u);	/* 451cac: call 0x451e60 */
	M32((DWORD)(0xa05630u)) = m->esi;	/* 451cb1: mov dword ptr [0xa05630], esi */
	m->eax = 0x2u;	/* 451cb7: mov eax, 2 */
	m->esi = M32(m->esp); m->esp += 4;	/* 451cbc: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451cbd: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451cc3: ret  */
L_451cc4:
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451cc4: cmp eax, -1 */
	if (!m->zf) goto L_451ce3;	/* 451cc7: jne 0x451ce3 */
	m->esp -= 4; M32(m->esp) = 0x451cceu; native_call(m, 0x4a8292u);	/* 451cc9: call 0x4a8292 */
	m->esp -= 4; M32(m->esp) = 0x451cd3u; native_call(m, 0x451e60u);	/* 451cce: call 0x451e60 */
	M32((DWORD)(0xa05630u)) = m->esi;	/* 451cd3: mov dword ptr [0xa05630], esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451cd9: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 451cdb: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451cdc: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451ce2: ret  */
L_451ce3:
	M32((DWORD)(0xa0b380u)) = 0xc9u;	/* 451ce3: mov dword ptr [0xa0b380], 0xc9 */
	m->eax = 0x1u;	/* 451ced: mov eax, 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 451cf2: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451cf3: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451cf9: ret  */
L_451cfa:
	m->edx = (DWORD)(m->esp + 0x14u);	/* 451cfa: lea edx, [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451cfe: push edx */
	{ DWORD v_ = 0x202u; m->esp -= 4; M32(m->esp) = v_; }	/* 451cff: push 0x202 */
	m->esp -= 4; M32(m->esp) = 0x451d09u; native_call(m, 0x4a82c2u);	/* 451d04: call 0x4a82c2 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 451d09: test eax, eax */
	if (!m->zf) goto L_451e56;	/* 451d0b: jne 0x451e56 */
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->esp + 0x14u))) & 0xffff);	/* 451d11: mov ax, word ptr [esp + 0x14] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 451d16: cmp al, 2 */
	if (!m->zf) goto L_451e51;	/* 451d18: jne 0x451e51 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451d1e: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 451d20: mov cl, ah */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 451d22: cmp cl, al */
	if (!m->zf) goto L_451e51;	/* 451d24: jne 0x451e51 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 451d2a: xor esi, esi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451d2c: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 451d2d: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 451d2f: push 2 */
	m->esp -= 4; M32(m->esp) = 0x451d36u; native_call(m, 0x4a82bcu);	/* 451d31: call 0x4a82bc */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451d36: cmp eax, -1 */
	M32((DWORD)(0xa055f8u)) = m->eax;	/* 451d39: mov dword ptr [0xa055f8], eax */
	if (!m->zf) goto L_451d54;	/* 451d3e: jne 0x451d54 */
	m->esp -= 4; M32(m->esp) = 0x451d45u; native_call(m, 0x4a8292u);	/* 451d40: call 0x4a8292 */
	m->esp -= 4; M32(m->esp) = 0x451d4au; native_call(m, 0x451e60u);	/* 451d45: call 0x451e60 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451d4a: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 451d4c: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451d4d: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451d53: ret  */
L_451d54:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 451d54: xor edx, edx */
	m->ecx = (DWORD)(m->esp + 0x4u);	/* 451d56: lea ecx, [esp + 4] */
	M32((DWORD)(m->esp + 0x4u)) = m->edx;	/* 451d5a: mov dword ptr [esp + 4], edx */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 451d5e: push 0x10 */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 451d60: mov dword ptr [esp + 0xc], edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451d64: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 451d65: mov dword ptr [esp + 0x14], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451d69: push eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 451d6a: mov dword ptr [esp + 0x1c], edx */
	M16((DWORD)(m->esp + 0x10u)) = (WORD)(0x2u);	/* 451d6e: mov word ptr [esp + 0x10], 2 */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 451d75: mov dword ptr [esp + 0x14], esi */
	m->esp -= 4; M32(m->esp) = 0x451d7eu; native_call(m, 0x4a82b6u);	/* 451d79: call 0x4a82b6 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451d7e: cmp eax, -1 */
	if (m->zf) goto L_451e56;	/* 451d81: je 0x451e56 */
	{ DWORD v_ = 0xa055e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 451d87: push 0xa055e4 */
	M16((DWORD)(m->esp + 0x8u)) = (WORD)(0x2u);	/* 451d8c: mov word ptr [esp + 8], 2 */
	m->esp -= 4; M32(m->esp) = 0x451d98u; native_call(m, 0x4a82b0u);	/* 451d93: call 0x4a82b0 */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(0xa05326u))) & 0xffff);	/* 451d98: mov dx, word ptr [0xa05326] */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 451d9f: mov dword ptr [esp + 8], eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451da3: push edx */
	m->esp -= 4; M32(m->esp) = 0x451da9u; native_call(m, 0x4a82aau);	/* 451da4: call 0x4a82aa */
	M16((DWORD)(m->esp + 0x6u)) = (WORD)((m->eax & 0xffff));	/* 451da9: mov word ptr [esp + 6], ax */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 451dae: mov eax, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451db2: cmp eax, -1 */
	if (!m->zf) goto L_451dd0;	/* 451db5: jne 0x451dd0 */
	{ DWORD v_ = 0xa055e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 451db7: push 0xa055e4 */
	m->esp -= 4; M32(m->esp) = 0x451dc1u; native_call(m, 0x4a82a4u);	/* 451dbc: call 0x4a82a4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451dc1: cmp eax, esi */
	if (m->zf) goto L_451e07;	/* 451dc3: je 0x451e07 */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 451dc5: mov eax, dword ptr [eax + 0xc] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 451dc8: mov ecx, dword ptr [eax] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 451dca: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 451dcc: mov dword ptr [esp + 8], edx */
L_451dd0:
	m->ecx = M32((DWORD)(0xa055f8u));	/* 451dd0: mov ecx, dword ptr [0xa055f8] */
	m->eax = (DWORD)(m->esp + 0x4u);	/* 451dd6: lea eax, [esp + 4] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 451dda: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451ddc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451ddd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x451de3u; native_call(m, 0x4a829eu);	/* 451dde: call 0x4a829e */
	{ DWORD a_ = m->eax, b_ = 0x274du & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451de3: cmp eax, 0x274d */
	if (!m->zf) goto L_451e1b;	/* 451de8: jne 0x451e1b */
	m->esp -= 4; M32(m->esp) = 0x451defu; native_call(m, 0x4a8292u);	/* 451dea: call 0x4a8292 */
	m->esp -= 4; M32(m->esp) = 0x451df4u; native_call(m, 0x451e60u);	/* 451def: call 0x451e60 */
	M32((DWORD)(0xa055f8u)) = m->esi;	/* 451df4: mov dword ptr [0xa055f8], esi */
	m->eax = 0x2u;	/* 451dfa: mov eax, 2 */
	m->esi = M32(m->esp); m->esp += 4;	/* 451dff: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451e00: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451e06: ret  */
L_451e07:
	{ DWORD v_ = 0x2726u; m->esp -= 4; M32(m->esp) = v_; }	/* 451e07: push 0x2726 */
	m->esp -= 4; M32(m->esp) = 0x451e11u; native_call(m, 0x4a8298u);	/* 451e0c: call 0x4a8298 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451e11: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 451e13: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451e14: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451e1a: ret  */
L_451e1b:
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451e1b: cmp eax, -1 */
	if (!m->zf) goto L_451e3a;	/* 451e1e: jne 0x451e3a */
	m->esp -= 4; M32(m->esp) = 0x451e25u; native_call(m, 0x4a8292u);	/* 451e20: call 0x4a8292 */
	m->esp -= 4; M32(m->esp) = 0x451e2au; native_call(m, 0x451e60u);	/* 451e25: call 0x451e60 */
	M32((DWORD)(0xa055f8u)) = m->esi;	/* 451e2a: mov dword ptr [0xa055f8], esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451e30: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 451e32: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451e33: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451e39: ret  */
L_451e3a:
	M32((DWORD)(0xa0b380u)) = 0xc8u;	/* 451e3a: mov dword ptr [0xa0b380], 0xc8 */
L_451e44:
	m->eax = 0x1u;	/* 451e44: mov eax, 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 451e49: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451e4a: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451e50: ret  */
L_451e51:
	m->esp -= 4; M32(m->esp) = 0x451e56u; native_call(m, 0x4a8292u);	/* 451e51: call 0x4a8292 */
L_451e56:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451e56: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 451e58: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x1a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 451e59: add esp, 0x1a0 */
	m->esp += 4 + 0; return;	/* 451e5f: ret  */
}

/* lobby_openConnection (0x4060f0), lifted by tools/lift.py */
static void lift_4060f0(X86 *m)
{
	m->eax = M32((DWORD)(0x4db718u));	/* 4060f0: mov eax, dword ptr [0x4db718] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4060f5: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4060f6: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4060f8: cmp eax, esi */
	if (!m->zf) goto L_406152;	/* 4060fa: jne 0x406152 */
	m->esp -= 4; M32(m->esp) = 0x406101u; native_call(m, 0x451e60u);	/* 4060fc: call 0x451e60 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 406101: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x406108u; lift_451b80(m);	/* 406103: call 0x451b80 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406108: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40610b: cmp eax, esi */
	if (!m->zf) goto L_40611d;	/* 40610d: jne 0x40611d */
	{ DWORD v_ = 0x3du; m->esp -= 4; M32(m->esp) = v_; }	/* 40610f: push 0x3d */
	m->esp -= 4; M32(m->esp) = 0x406116u; native_call(m, 0x41ee40u);	/* 406111: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406116: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 406119: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 40611b: pop esi */
	m->esp += 4 + 0; return;	/* 40611c: ret  */
L_40611d:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40611d: cmp eax, 2 */
	if (!m->zf) goto L_406130;	/* 406120: jne 0x406130 */
	{ DWORD v_ = 0x46u; m->esp -= 4; M32(m->esp) = v_; }	/* 406122: push 0x46 */
	m->esp -= 4; M32(m->esp) = 0x406129u; native_call(m, 0x41ee40u);	/* 406124: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406129: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40612c: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 40612e: pop esi */
	m->esp += 4 + 0; return;	/* 40612f: ret  */
L_406130:
	m->eax = M32((DWORD)(0x4ded18u));	/* 406130: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 406135: push 0x64 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 406137: push eax */
	m->esp -= 4; M32(m->esp) = 0x40613du; native_call(m, 0x452170u);	/* 406138: call 0x452170 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40613d: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406140: test eax, eax */
	if (!m->zf) goto L_406152;	/* 406142: jne 0x406152 */
	{ DWORD v_ = 0x3eu; m->esp -= 4; M32(m->esp) = v_; }	/* 406144: push 0x3e */
	m->esp -= 4; M32(m->esp) = 0x40614bu; native_call(m, 0x41ee40u);	/* 406146: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40614b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40614e: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 406150: pop esi */
	m->esp += 4 + 0; return;	/* 406151: ret  */
L_406152:
	m->ecx = M32((DWORD)(0xa0b31cu));	/* 406152: mov ecx, dword ptr [0xa0b31c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 406158: push edi */
	m->edi = 0x1u;	/* 406159: mov edi, 1 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 40615e: push 0x64 */
	M32((DWORD)(0x4db718u)) = m->edi;	/* 406160: mov dword ptr [0x4db718], edi */
	M32((DWORD)(0x4dbaacu)) = m->edi;	/* 406166: mov dword ptr [0x4dbaac], edi */
	M32((DWORD)(0x4dba88u)) = m->edi;	/* 40616c: mov dword ptr [0x4dba88], edi */
	M32((DWORD)(0x4ded60u)) = 0x2u;	/* 406172: mov dword ptr [0x4ded60], 2 */
	M32((DWORD)(0x4df018u)) = m->esi;	/* 40617c: mov dword ptr [0x4df018], esi */
	M32((DWORD)(0x4db8b8u)) = m->esi;	/* 406182: mov dword ptr [0x4db8b8], esi */
	M32((DWORD)(0x4db858u)) = m->edi;	/* 406188: mov dword ptr [0x4db858], edi */
	M32((DWORD)(0x76d484u)) = m->esi;	/* 40618e: mov dword ptr [0x76d484], esi */
	M32((DWORD)(0x680bb8u)) = m->esi;	/* 406194: mov dword ptr [0x680bb8], esi */
	M32((DWORD)(0x4dba8cu)) = m->esi;	/* 40619a: mov dword ptr [0x4dba8c], esi */
	M32((DWORD)(0xa0b36cu)) = m->esi;	/* 4061a0: mov dword ptr [0xa0b36c], esi */
	M32((DWORD)(0x9087b0u)) = m->esi;	/* 4061a6: mov dword ptr [0x9087b0], esi */
	M32((DWORD)(0x67ef30u)) = m->esi;	/* 4061ac: mov dword ptr [0x67ef30], esi */
	M32((DWORD)(0x4dbaa8u)) = m->edi;	/* 4061b2: mov dword ptr [0x4dbaa8], edi */
	M32((DWORD)(0x4dbac8u)) = m->esi;	/* 4061b8: mov dword ptr [0x4dbac8], esi */
	M32((DWORD)(0x76d41cu)) = m->esi;	/* 4061be: mov dword ptr [0x76d41c], esi */
	M32((DWORD)(0x4dba80u)) = 0x447a0000u;	/* 4061c4: mov dword ptr [0x4dba80], 0x447a0000 */
	M32((DWORD)(0x680bb0u)) = m->esi;	/* 4061ce: mov dword ptr [0x680bb0], esi */
	M32((DWORD)(0x4df818u)) = m->esi;	/* 4061d4: mov dword ptr [0x4df818], esi */
	{ DWORD v_ = 0xdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4061da: push 0xd */
	M32((DWORD)(m->ecx + 0x0u)) = 0x180001u;	/* 4061dc: mov dword ptr [ecx], 0x180001 */
	m->esp -= 4; M32(m->esp) = 0x4061e7u; native_call(m, 0x4521c0u);	/* 4061e2: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4061e7: add esp, 8 */
	m->eax = m->edi;	/* 4061ea: mov eax, edi */
	M32((DWORD)(0x4db8b4u)) = m->esi;	/* 4061ec: mov dword ptr [0x4db8b4], esi */
	M32((DWORD)(0x5b1914u)) = 0x1eu;	/* 4061f2: mov dword ptr [0x5b1914], 0x1e */
	m->edi = M32(m->esp); m->esp += 4;	/* 4061fc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4061fd: pop esi */
	m->esp += 4 + 0; return;	/* 4061fe: ret  */
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
