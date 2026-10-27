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

static void lift_41e730(X86 *m);
static void lift_435ab0(X86 *m);
static void lift_427a40(X86 *m);
static void lift_406bd0(X86 *m);
static void lift_440d70(X86 *m);
static void lift_407270(X86 *m);
static void lift_4302d0(X86 *m);
static void lift_44b990(X86 *m);
static void lift_427970(X86 *m);
static void lift_44b420(X86 *m);
static void lift_4460d0(X86 *m);
static void lift_487cb0(X86 *m);
static void lift_4532f0(X86 *m);
static void lift_44f850(X86 *m);

/* profile_44f850 (0x44f850), lifted by tools/lift.py */
static void lift_44f850(X86 *m)
{
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f850: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44f857u; native_call(m, 0x41e7a0u);	/* 44f852: call 0x41e7a0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44f857: pop ecx */
	m->esp += 4 + 0; return;	/* 44f858: ret  */
}

/* intro_41e730 (0x41e730), lifted by tools/lift.py */
static void lift_41e730(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e730: sub esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x41e738u; { long double r_ = native_call_fp(m, 0x4301e0u); FPUSH(r_); }	/* 41e733: call 0x4301e0 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41e738: fstp qword ptr [esp] */
L_41e73c:
	m->esp -= 4; M32(m->esp) = 0x41e741u; { long double r_ = native_call_fp(m, 0x4301e0u); FPUSH(r_); }	/* 41e73c: call 0x4301e0 */
	ST(0) = ST(0) - (long double)*(const double *)(DWORD)(m->esp + 0x0u);	/* 41e741: fsub qword ptr [esp] */
	ST(0) = ST(0) * (long double)*(const double *)(DWORD)(0x4a94d0u);	/* 41e745: fmul qword ptr [0x4a94d0] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(m->esp + 0xcu)); FPOP();	/* 41e74b: fcomp qword ptr [esp + 0xc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41e74f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41e751: test ah, 1 */
	if (!m->zf) goto L_41e73c;	/* 41e754: jne 0x41e73c */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e756: add esp, 8 */
	m->esp += 4 + 0; return;	/* 41e759: ret  */
}

/* room_435ab0 (0x435ab0), lifted by tools/lift.py */
static void lift_435ab0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 435ab0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435ab5: test eax, eax */
	if (!m->zf) goto L_435afc;	/* 435ab7: jne 0x435afc */
	m->eax = M32((DWORD)(0x4ded88u));	/* 435ab9: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435abe: test eax, eax */
	if (m->zf) goto L_435afc;	/* 435ac0: je 0x435afc */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 435ac2: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 435ac7: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435acd: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435ace: push ecx */
	m->esp -= 4; M32(m->esp) = 0x435ad4u; native_call(m, 0x4321c0u);	/* 435acf: call 0x4321c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435ad4: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 435ad7: sub eax, 0 */
	if (m->zf) goto L_435aea;	/* 435ada: je 0x435aea */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 435adc: dec eax */
	if (!m->zf) goto L_435afc;	/* 435add: jne 0x435afc */
	M32((DWORD)(0x9dd850u)) = 0x0u;	/* 435adf: mov dword ptr [0x9dd850], 0 */
	m->esp += 4 + 0; return;	/* 435ae9: ret  */
L_435aea:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 435aea: push 2 */
	M32((DWORD)(0x9dd850u)) = 0x0u;	/* 435aec: mov dword ptr [0x9dd850], 0 */
	m->esp -= 4; M32(m->esp) = 0x435afbu; native_call(m, 0x41e7a0u);	/* 435af6: call 0x41e7a0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 435afb: pop ecx */
L_435afc:
	m->esp += 4 + 0; return;	/* 435afc: ret  */
}

/* FUN_00427a40 (0x427a40), lifted by tools/lift.py */
static void lift_427a40(X86 *m)
{
	m->eax = M32((DWORD)(0x9da48cu));	/* 427a40: mov eax, dword ptr [0x9da48c] */
	m->ecx = M32((DWORD)(0x9da488u));	/* 427a45: mov ecx, dword ptr [0x9da488] */
	m->edx = M32((DWORD)(0x9da484u));	/* 427a4b: mov edx, dword ptr [0x9da484] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427a51: push eax */
	m->eax = M32((DWORD)(0x9da480u));	/* 427a52: mov eax, dword ptr [0x9da480] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a57: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a58: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427a59: push eax */
	m->esp -= 4; M32(m->esp) = 0x427a60u; native_call(m, M32(0x4a9228u));	/* 427a5a: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427a60: push 1 */
	m->esp -= 4; M32(m->esp) = 0x427a68u; native_call(m, M32(0x4a921cu));	/* 427a62: call dword ptr [0x4a921c] */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 427a68: mov ecx, dword ptr [esp + 8] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 427a6c: mov edx, dword ptr [esp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a70: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a71: push edx */
	m->esp -= 4; M32(m->esp) = 0x427a77u; native_call(m, 0x41ef60u);	/* 427a72: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 427a77: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 427a7b: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427a7f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a80: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427a86u; native_call(m, 0x41ef60u);	/* 427a81: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427a86: add esp, 0x10 */
	native_call(m, M32(0x4a9220u)); return;	/* 427a89: jmp dword ptr [0x4a9220] */
}

/* lobby_406bd0 (0x406bd0), lifted by tools/lift.py */
static void lift_406bd0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 406bd0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406bd5: test eax, eax */
	if (!m->zf) goto L_406c2f;	/* 406bd7: jne 0x406c2f */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 406bd9: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406bde: test eax, eax */
	if (m->zf) goto L_406bec;	/* 406be0: je 0x406bec */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 406be2: mov dword ptr [0x907b2c], 0 */
L_406bec:
	m->eax = M32((DWORD)(0x4ded88u));	/* 406bec: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406bf1: test eax, eax */
	if (m->zf) goto L_406c2f;	/* 406bf3: je 0x406c2f */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 406bf5: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 406bfa: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 406c00: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 406c01: push ecx */
	m->esp -= 4; M32(m->esp) = 0x406c07u; native_call(m, 0x4045a0u);	/* 406c02: call 0x4045a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406c07: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 406c0a: sub eax, 0 */
	if (m->zf) goto L_406c1d;	/* 406c0d: je 0x406c1d */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 406c0f: dec eax */
	if (!m->zf) goto L_406c2f;	/* 406c10: jne 0x406c2f */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 406c12: mov dword ptr [0x907b2c], 0 */
	m->esp += 4 + 0; return;	/* 406c1c: ret  */
L_406c1d:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 406c1d: push 2 */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 406c1f: mov dword ptr [0x907b2c], 0 */
	m->esp -= 4; M32(m->esp) = 0x406c2eu; native_call(m, 0x41e7a0u);	/* 406c29: call 0x41e7a0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 406c2e: pop ecx */
L_406c2f:
	m->esp += 4 + 0; return;	/* 406c2f: ret  */
}

/* mainmenu_440d70 (0x440d70), lifted by tools/lift.py */
static void lift_440d70(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 440d70: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 440d71: xor esi, esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 440d73: push edi */
	M32((DWORD)(0x9dd928u)) = m->esi;	/* 440d74: mov dword ptr [0x9dd928], esi */
	M32((DWORD)(0x9dd92cu)) = m->esi;	/* 440d7a: mov dword ptr [0x9dd92c], esi */
	M32((DWORD)(0x9dd944u)) = m->esi;	/* 440d80: mov dword ptr [0x9dd944], esi */
	M32((DWORD)(0x9eea88u)) = m->esi;	/* 440d86: mov dword ptr [0x9eea88], esi */
	M32((DWORD)(0x90d1c4u)) = 0x1u;	/* 440d8c: mov dword ptr [0x90d1c4], 1 */
	M32((DWORD)(0x9dd908u)) = 0x50u;	/* 440d96: mov dword ptr [0x9dd908], 0x50 */
	M32((DWORD)(0x9dd90cu)) = 0x28u;	/* 440da0: mov dword ptr [0x9dd90c], 0x28 */
	M32((DWORD)(0x9dd910u)) = 0x230u;	/* 440daa: mov dword ptr [0x9dd910], 0x230 */
	M32((DWORD)(0x9dd914u)) = 0x1b8u;	/* 440db4: mov dword ptr [0x9dd914], 0x1b8 */
	m->edx = 0x9ddac8u;	/* 440dbe: mov edx, 0x9ddac8 */
L_440dc3:
	m->ecx = 0x10u;	/* 440dc3: mov ecx, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 440dc8: xor eax, eax */
	m->edi = (DWORD)(m->edx + 0xffffffc0u);	/* 440dca: lea edi, [edx - 0x40] */
	{ DWORD a_ = m->edx, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 440dcd: add edx, 0x44 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 440dd0: rep stosd dword ptr es:[edi], eax */
	M32((DWORD)(m->edx + 0xffffffbcu)) = m->esi;	/* 440dd2: mov dword ptr [edx - 0x44], esi */
	{ DWORD a_ = m->edx, b_ = 0x9eeac8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 440dd5: cmp edx, 0x9eeac8 */
	if (m->sf != m->of) goto L_440dc3;	/* 440ddb: jl 0x440dc3 */
	m->esp -= 4; M32(m->esp) = 0x440de2u; native_call(m, 0x440a20u);	/* 440ddd: call 0x440a20 */
	m->esp -= 4; M32(m->esp) = 0x440de7u; native_call(m, 0x440c60u);	/* 440de2: call 0x440c60 */
	m->edi = M32(m->esp); m->esp += 4;	/* 440de7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 440de8: pop esi */
	m->esp += 4 + 0; return;	/* 440de9: ret  */
}

/* lobby_407270 (0x407270), lifted by tools/lift.py */
static void lift_407270(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbab0u));	/* 407270: mov eax, dword ptr [0x4dbab0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407275: test eax, eax */
	if (!m->zf) goto L_4072f3;	/* 407277: jne 0x4072f3 */
	m->eax = M32((DWORD)(0x4db850u));	/* 407279: mov eax, dword ptr [0x4db850] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40727e: test eax, eax */
	if (!m->zf) goto L_4072f3;	/* 407280: jne 0x4072f3 */
	m->eax = M32((DWORD)(0x4db518u));	/* 407282: mov eax, dword ptr [0x4db518] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407287: test eax, eax */
	if (!m->zf) goto L_4072f3;	/* 407289: jne 0x4072f3 */
	m->eax = M32((DWORD)(0x4dbaccu));	/* 40728b: mov eax, dword ptr [0x4dbacc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407290: test eax, eax */
	if (!m->zf) goto L_4072f3;	/* 407292: jne 0x4072f3 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 407294: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407299: test eax, eax */
	if (!m->zf) goto L_4072f3;	/* 40729b: jne 0x4072f3 */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 40729d: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4072a2: test eax, eax */
	if (m->zf) goto L_4072b0;	/* 4072a4: je 0x4072b0 */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 4072a6: mov dword ptr [0x907b2c], 0 */
L_4072b0:
	m->eax = M32((DWORD)(0x4ded88u));	/* 4072b0: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4072b5: test eax, eax */
	if (m->zf) goto L_4072f3;	/* 4072b7: je 0x4072f3 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4072b9: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4072be: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4072c4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4072c5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4072cbu; native_call(m, 0x4045a0u);	/* 4072c6: call 0x4045a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4072cb: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4072ce: sub eax, 0 */
	if (m->zf) goto L_4072e1;	/* 4072d1: je 0x4072e1 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4072d3: dec eax */
	if (!m->zf) goto L_4072f3;	/* 4072d4: jne 0x4072f3 */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 4072d6: mov dword ptr [0x907b2c], 0 */
	m->esp += 4 + 0; return;	/* 4072e0: ret  */
L_4072e1:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4072e1: push 2 */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 4072e3: mov dword ptr [0x907b2c], 0 */
	m->esp -= 4; M32(m->esp) = 0x4072f2u; native_call(m, 0x41e7a0u);	/* 4072ed: call 0x41e7a0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4072f2: pop ecx */
L_4072f3:
	m->esp += 4 + 0; return;	/* 4072f3: ret  */
}

/* timer_init (0x4302d0), lifted by tools/lift.py */
static void lift_4302d0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4302d0: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 4302d3: lea eax, [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4302d7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4302deu; native_call(m, M32(0x4a913cu));	/* 4302d8: call dword ptr [0x4a913c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4302de: test eax, eax */
	if (!m->zf) goto L_4302ef;	/* 4302e0: jne 0x4302ef */
	{ DWORD v_ = 0x4b24d4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4302e2: push 0x4b24d4 */
	m->esp -= 4; M32(m->esp) = 0x4302ecu; native_call(m, 0x41edf0u);	/* 4302e7: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4302ec: add esp, 4 */
L_4302ef:
	m->ecx = M32((DWORD)(m->esp + 0x0u));	/* 4302ef: mov ecx, dword ptr [esp] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 4302f3: mov edx, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4302f7: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4302f8: xor esi, esi */
	M32((DWORD)(0x4df030u)) = m->ecx;	/* 4302fa: mov dword ptr [0x4df030], ecx */
	M32((DWORD)(0x4df034u)) = m->edx;	/* 430300: mov dword ptr [0x4df034], edx */
	M32((DWORD)(0x67ef1cu)) = m->esi;	/* 430306: mov dword ptr [0x67ef1c], esi */
L_43030c:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43030c: test edx, edx */
	if (!m->zf) goto L_430329;	/* 43030e: jne 0x430329 */
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 430310: mov dword ptr [esp + 4], ecx */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 430314: mov dword ptr [esp + 8], edx */
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0x4u));	/* 430318: fild qword ptr [esp + 4] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(0x4a9580u)); FPOP();	/* 43031c: fcomp qword ptr [0x4a9580] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 430322: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 430324: test ah, 0x41 */
	if (!m->zf) goto L_430337;	/* 430327: jne 0x430337 */
L_430329:
	m->eax = m->edx;	/* 430329: mov eax, edx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 43032b: inc esi */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43032c: shl eax, 0x1f */
	{ DWORD a_ = m->ecx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43032f: shr ecx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 430331: or ecx, eax */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 430333: shr edx, 1 */
	goto L_43030c;	/* 430335: jmp 0x43030c */
L_430337:
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 430337: mov dword ptr [esp + 4], ecx */
	M32((DWORD)(m->esp + 0x8u)) = 0x0u;	/* 43033b: mov dword ptr [esp + 8], 0 */
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0x4u));	/* 430343: fild qword ptr [esp + 4] */
	M32((DWORD)(0x67ef1cu)) = m->esi;	/* 430347: mov dword ptr [0x67ef1c], esi */
	M32((DWORD)(0x9db980u)) = 0x0u;	/* 43034d: mov dword ptr [0x9db980], 0 */
	M32((DWORD)(0x9db984u)) = 0x0u;	/* 430357: mov dword ptr [0x9db984], 0 */
	M32((DWORD)(0x9db988u)) = 0x0u;	/* 430361: mov dword ptr [0x9db988], 0 */
	ST(0) = (long double)*(const double *)(DWORD)(0x4a94e0u) / ST(0);	/* 43036b: fdivr qword ptr [0x4a94e0] */
	M32((DWORD)(0x9db98cu)) = 0x0u;	/* 430371: mov dword ptr [0x9db98c], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 43037b: pop esi */
	MDBL((DWORD)(0x4ded58u)) = (double)ST(0); FPOP();	/* 43037c: fstp qword ptr [0x4ded58] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 430382: add esp, 8 */
	m->esp += 4 + 0; return;	/* 430385: ret  */
}

/* profile_selectAndLoad (0x44b990), lifted by tools/lift.py */
static void lift_44b990(X86 *m)
{
	m->eax = M32((DWORD)(0x9f9008u));	/* 44b990: mov eax, dword ptr [0x9f9008] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44b995: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44b996: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44b997: push edi */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44b998: lea edx, [eax + eax*8] */
	m->edi = 0x9dc92cu;	/* 44b99b: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44b9a0: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44b9a3: xor eax, eax */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44b9a5: shl edx, 3 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44b9a8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44b9aa: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44b9ac: sub edi, ecx */
	m->ebx = (DWORD)(m->edx + 0x9f684cu);	/* 44b9ae: lea ebx, [edx + 0x9f684c] */
	m->eax = m->ecx;	/* 44b9b4: mov eax, ecx */
	m->esi = m->edi;	/* 44b9b6: mov esi, edi */
	m->edi = m->ebx;	/* 44b9b8: mov edi, ebx */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 44b9ba: push 0x4b2adc */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44b9bf: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44b9c2: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44b9c4: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44b9c6: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44b9c9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f8d30u));	/* 44b9cb: mov ecx, dword ptr [0x9f8d30] */
	M32((DWORD)(m->edx + 0x9f688cu)) = m->ecx;	/* 44b9d1: mov dword ptr [edx + 0x9f688c], ecx */
	m->esp -= 4; M32(m->esp) = 0x44b9dcu; native_call(m, 0x49f8a6u);	/* 44b9d7: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44b9dc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44b9df: test eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 44b9e1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44b9e2: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44b9e3: pop ebx */
	if (m->zf) goto L_44b9fd;	/* 44b9e4: je 0x44b9fd */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 44b9e6: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x44b9f0u; native_call(m, 0x49f94au);	/* 44b9eb: call 0x49f94a */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 44b9f0: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x44b9fau; native_call(m, 0x49f8a6u);	/* 44b9f5: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44b9fa: add esp, 8 */
L_44b9fd:
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 44b9fd: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x44ba07u; native_call(m, 0x49f8a6u);	/* 44ba02: call 0x49f8a6 */
	m->eax = M32((DWORD)(0x9f9008u));	/* 44ba07: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ba0c: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44ba0f: inc eax */
	{ DWORD a_ = m->eax, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ba10: cmp eax, 0xd */
	M32((DWORD)(0x9f9008u)) = m->eax;	/* 44ba13: mov dword ptr [0x9f9008], eax */
	if (!m->zf && m->sf == m->of) goto L_44ba30;	/* 44ba18: jg 0x44ba30 */
	m->edx = M32((DWORD)(0x9f8c4cu));	/* 44ba1a: mov edx, dword ptr [0x9f8c4c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44ba20: dec eax */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44ba21: add edx, eax */
	M32((DWORD)(0x9f8c5cu)) = m->eax;	/* 44ba23: mov dword ptr [0x9f8c5c], eax */
	M32((DWORD)(0x9f8d74u)) = m->edx;	/* 44ba28: mov dword ptr [0x9f8d74], edx */
	goto L_44ba4a;	/* 44ba2e: jmp 0x44ba4a */
L_44ba30:
	{ DWORD a_ = m->eax, b_ = 0xfffffff3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ba30: add eax, -0xd */
	M32((DWORD)(0x9f8c5cu)) = 0xcu;	/* 44ba33: mov dword ptr [0x9f8c5c], 0xc */
	M32((DWORD)(0x9f8c4cu)) = m->eax;	/* 44ba3d: mov dword ptr [0x9f8c4c], eax */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ba42: add eax, 0xc */
	M32((DWORD)(0x9f8d74u)) = m->eax;	/* 44ba45: mov dword ptr [0x9f8d74], eax */
L_44ba4a:
	m->esp -= 4; M32(m->esp) = 0x44ba4fu; native_call(m, 0x446590u);	/* 44ba4a: call 0x446590 */
	native_call(m, 0x44b7a0u); return;	/* 44ba4f: jmp 0x44b7a0 */
}

/* menu_drawRect (0x427970), lifted by tools/lift.py */
static void lift_427970(X86 *m)
{
	m->eax = M32((DWORD)(0x9da48cu));	/* 427970: mov eax, dword ptr [0x9da48c] */
	m->ecx = M32((DWORD)(0x9da488u));	/* 427975: mov ecx, dword ptr [0x9da488] */
	m->edx = M32((DWORD)(0x9da484u));	/* 42797b: mov edx, dword ptr [0x9da484] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427981: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 427982: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427983: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427984: push eax */
	m->eax = M32((DWORD)(0x9da480u));	/* 427985: mov eax, dword ptr [0x9da480] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42798a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42798b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42798c: push eax */
	m->esp -= 4; M32(m->esp) = 0x427993u; native_call(m, M32(0x4a9228u));	/* 42798d: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 427993: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 427997: test eax, eax */
	if (m->zf) goto L_4279dc;	/* 427999: je 0x4279dc */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42799b: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4279a3u; native_call(m, M32(0x4a921cu));	/* 42799d: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 4279a3: mov esi, dword ptr [esp + 0x14] */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 4279a7: mov edi, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279ab: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279ac: push edi */
	m->esp -= 4; M32(m->esp) = 0x4279b2u; native_call(m, 0x41ef60u);	/* 4279ad: call 0x41ef60 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279b2: push esi */
	m->esi = M32((DWORD)(m->esp + 0x24u));	/* 4279b3: mov esi, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279b7: push esi */
	m->esp -= 4; M32(m->esp) = 0x4279bdu; native_call(m, 0x41ef60u);	/* 4279b8: call 0x41ef60 */
	m->ebx = M32((DWORD)(m->esp + 0x2cu));	/* 4279bd: mov ebx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4279c1: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279c2: push esi */
	m->esp -= 4; M32(m->esp) = 0x4279c8u; native_call(m, 0x41ef60u);	/* 4279c3: call 0x41ef60 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4279c8: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279c9: push edi */
	m->esp -= 4; M32(m->esp) = 0x4279cfu; native_call(m, 0x41ef60u);	/* 4279ca: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4279cf: add esp, 0x20 */
	m->esp -= 4; M32(m->esp) = 0x4279d8u; native_call(m, M32(0x4a9220u));	/* 4279d2: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4279d8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4279d9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4279da: pop ebx */
	m->esp += 4 + 0; return;	/* 4279db: ret  */
L_4279dc:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4279dc: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4279dd: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4279e5u; native_call(m, M32(0x4a921cu));	/* 4279df: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 4279e5: mov esi, dword ptr [esp + 0x18] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 4279e9: mov edi, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279ed: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279ee: push edi */
	m->esp -= 4; M32(m->esp) = 0x4279f4u; native_call(m, 0x41ef60u);	/* 4279ef: call 0x41ef60 */
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 4279f4: mov ebx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279f8: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4279f9: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4279ffu; native_call(m, 0x41ef60u);	/* 4279fa: call 0x41ef60 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4279ff: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a00: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427a06u; native_call(m, 0x41ef60u);	/* 427a01: call 0x41ef60 */
	m->ebp = M32((DWORD)(m->esp + 0x38u));	/* 427a06: mov ebp, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427a0a: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a0b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427a11u; native_call(m, 0x41ef60u);	/* 427a0c: call 0x41ef60 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427a11: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a12: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427a18u; native_call(m, 0x41ef60u);	/* 427a13: call 0x41ef60 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427a18: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427a19: push edi */
	m->esp -= 4; M32(m->esp) = 0x427a1fu; native_call(m, 0x41ef60u);	/* 427a1a: call 0x41ef60 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427a1f: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427a20: push edi */
	m->esp -= 4; M32(m->esp) = 0x427a26u; native_call(m, 0x41ef60u);	/* 427a21: call 0x41ef60 */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 427a26: dec esi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 427a27: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427a28: push edi */
	m->esp -= 4; M32(m->esp) = 0x427a2eu; native_call(m, 0x41ef60u);	/* 427a29: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427a2e: add esp, 0x40 */
	m->esp -= 4; M32(m->esp) = 0x427a37u; native_call(m, M32(0x4a9220u));	/* 427a31: call dword ptr [0x4a9220] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 427a37: pop ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 427a38: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 427a39: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 427a3a: pop ebx */
	m->esp += 4 + 0; return;	/* 427a3b: ret  */
}

/* menuState210_enter (0x44b420), lifted by tools/lift.py */
static void lift_44b420(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44b420: push esi */
	m->eax = 0x3cu;	/* 44b421: mov eax, 0x3c */
	m->esi = 0x10eu;	/* 44b426: mov esi, 0x10e */
	M32((DWORD)(0x9f8e48u)) = m->eax;	/* 44b42b: mov dword ptr [0x9f8e48], eax */
	M32((DWORD)(0x9f8e4cu)) = m->eax;	/* 44b430: mov dword ptr [0x9f8e4c], eax */
	M32((DWORD)(0x9f8f28u)) = m->esi;	/* 44b435: mov dword ptr [0x9f8f28], esi */
	M32((DWORD)(0x9f93c0u)) = m->esi;	/* 44b43b: mov dword ptr [0x9f93c0], esi */
	m->edx = 0x78u;	/* 44b441: mov edx, 0x78 */
	m->ecx = 0x96u;	/* 44b446: mov ecx, 0x96 */
	m->eax = 0x208u;	/* 44b44b: mov eax, 0x208 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44b450: xor esi, esi */
	M32((DWORD)(0x9f8ea0u)) = 0x244u;	/* 44b452: mov dword ptr [0x9f8ea0], 0x244 */
	M32((DWORD)(0x9f8ea4u)) = 0x1a4u;	/* 44b45c: mov dword ptr [0x9f8ea4], 0x1a4 */
	M32((DWORD)(0x9f8eacu)) = m->edx;	/* 44b466: mov dword ptr [0x9f8eac], edx */
	M32((DWORD)(0x9f8ea8u)) = m->ecx;	/* 44b46c: mov dword ptr [0x9f8ea8], ecx */
	M32((DWORD)(0x9f8f20u)) = m->eax;	/* 44b472: mov dword ptr [0x9f8f20], eax */
	M32((DWORD)(0x9f8f24u)) = 0x118u;	/* 44b477: mov dword ptr [0x9f8f24], 0x118 */
	M32((DWORD)(0x9f8f1cu)) = m->edx;	/* 44b481: mov dword ptr [0x9f8f1c], edx */
	M32((DWORD)(0x9f8f0cu)) = m->ecx;	/* 44b487: mov dword ptr [0x9f8f0c], ecx */
	M32((DWORD)(0x9f8f2cu)) = m->eax;	/* 44b48d: mov dword ptr [0x9f8f2c], eax */
	M32((DWORD)(0x9f6834u)) = m->edx;	/* 44b492: mov dword ptr [0x9f6834], edx */
	M32((DWORD)(0x9f683cu)) = m->ecx;	/* 44b498: mov dword ptr [0x9f683c], ecx */
	M32((DWORD)(0x9f93bcu)) = m->eax;	/* 44b49e: mov dword ptr [0x9f93bc], eax */
	M32((DWORD)(0x9f8c54u)) = 0x1eu;	/* 44b4a3: mov dword ptr [0x9f8c54], 0x1e */
	M32((DWORD)(0x9f8c50u)) = 0x14u;	/* 44b4ad: mov dword ptr [0x9f8c50], 0x14 */
	M32((DWORD)(0x9f6830u)) = 0x262u;	/* 44b4b7: mov dword ptr [0x9f6830], 0x262 */
	M32((DWORD)(0x9f682cu)) = 0x1c2u;	/* 44b4c1: mov dword ptr [0x9f682c], 0x1c2 */
	M32((DWORD)(0x9f8d70u)) = m->esi;	/* 44b4cb: mov dword ptr [0x9f8d70], esi */
	M32((DWORD)(0x9f6840u)) = m->esi;	/* 44b4d1: mov dword ptr [0x9f6840], esi */
	M32((DWORD)(0x9f8c4cu)) = m->esi;	/* 44b4d7: mov dword ptr [0x9f8c4c], esi */
	M32((DWORD)(0x9f8c5cu)) = m->esi;	/* 44b4dd: mov dword ptr [0x9f8c5c], esi */
	M32((DWORD)(0x9f8d74u)) = m->esi;	/* 44b4e3: mov dword ptr [0x9f8d74], esi */
	M32((DWORD)(0x9f8c58u)) = m->esi;	/* 44b4e9: mov dword ptr [0x9f8c58], esi */
	M32((DWORD)(0x680bb4u)) = m->esi;	/* 44b4ef: mov dword ptr [0x680bb4], esi */
	M32((DWORD)(0x76d37cu)) = m->esi;	/* 44b4f5: mov dword ptr [0x76d37c], esi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 44b4fb: mov dword ptr [0x76d42c], esi */
	m->esp -= 4; M32(m->esp) = 0x44b506u; native_call(m, 0x4474a0u);	/* 44b501: call 0x4474a0 */
	m->eax = M32((DWORD)(0x9f8c58u));	/* 44b506: mov eax, dword ptr [0x9f8c58] */
	{ DWORD a_ = m->eax, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44b50b: cmp eax, 0xd */
	M32((DWORD)(0x9f8d74u)) = m->eax;	/* 44b50e: mov dword ptr [0x9f8d74], eax */
	M32((DWORD)(0x9f8c5cu)) = m->eax;	/* 44b513: mov dword ptr [0x9f8c5c], eax */
	if (m->sf != m->of) goto L_44b52c;	/* 44b518: jl 0x44b52c */
	{ DWORD a_ = m->eax, b_ = 0xfffffff4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44b51a: add eax, -0xc */
	M32((DWORD)(0x9f8c5cu)) = 0xcu;	/* 44b51d: mov dword ptr [0x9f8c5c], 0xc */
	M32((DWORD)(0x9f8c4cu)) = m->eax;	/* 44b527: mov dword ptr [0x9f8c4c], eax */
L_44b52c:
	m->ecx = M32((DWORD)(0x9f9008u));	/* 44b52c: mov ecx, dword ptr [0x9f9008] */
	m->eax = 0x1u;	/* 44b532: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44b537: cmp ecx, esi */
	if (!m->zf) goto L_44b540;	/* 44b539: jne 0x44b540 */
	M32((DWORD)(0x9f8d70u)) = m->eax;	/* 44b53b: mov dword ptr [0x9f8d70], eax */
L_44b540:
	M32((DWORD)(0x4de740u)) = m->eax;	/* 44b540: mov dword ptr [0x4de740], eax */
	M32((DWORD)(0x76d428u)) = m->esi;	/* 44b545: mov dword ptr [0x76d428], esi */
	M32((DWORD)(0x90d1c4u)) = m->eax;	/* 44b54b: mov dword ptr [0x90d1c4], eax */
	M32((DWORD)(0x9f8f10u)) = m->eax;	/* 44b550: mov dword ptr [0x9f8f10], eax */
	m->esp -= 4; M32(m->esp) = 0x44b55au; native_call(m, 0x44af30u);	/* 44b555: call 0x44af30 */
	m->esp -= 4; M32(m->esp) = 0x44b55fu; native_call(m, 0x44b030u);	/* 44b55a: call 0x44b030 */
	m->esp -= 4; M32(m->esp) = 0x44b564u; native_call(m, 0x44b080u);	/* 44b55f: call 0x44b080 */
	m->esp -= 4; M32(m->esp) = 0x44b569u; native_call(m, 0x44b0b0u);	/* 44b564: call 0x44b0b0 */
	m->esp -= 4; M32(m->esp) = 0x44b56eu; native_call(m, 0x44b100u);	/* 44b569: call 0x44b100 */
	m->esp -= 4; M32(m->esp) = 0x44b573u; native_call(m, 0x44b150u);	/* 44b56e: call 0x44b150 */
	m->esp -= 4; M32(m->esp) = 0x44b578u; native_call(m, 0x44b1a0u);	/* 44b573: call 0x44b1a0 */
	M32((DWORD)(0x9f8eb0u)) = 0x0u;	/* 44b578: mov dword ptr [0x9f8eb0], 0 */
	M32((DWORD)(0x9f8eb4u)) = 0x3f800000u;	/* 44b582: mov dword ptr [0x9f8eb4], 0x3f800000 */
	M32((DWORD)(0x9f8eb8u)) = 0x3f800000u;	/* 44b58c: mov dword ptr [0x9f8eb8], 0x3f800000 */
	M32((DWORD)(0x9f8ebcu)) = 0x3f800000u;	/* 44b596: mov dword ptr [0x9f8ebc], 0x3f800000 */
	M32((DWORD)(0x9f8d58u)) = 0x0u;	/* 44b5a0: mov dword ptr [0x9f8d58], 0 */
	M32((DWORD)(0x9f8d5cu)) = 0x3f19999au;	/* 44b5aa: mov dword ptr [0x9f8d5c], 0x3f19999a */
	M32((DWORD)(0x9f8d60u)) = 0x3f19999au;	/* 44b5b4: mov dword ptr [0x9f8d60], 0x3f19999a */
	M32((DWORD)(0x9f8d64u)) = 0x3f800000u;	/* 44b5be: mov dword ptr [0x9f8d64], 0x3f800000 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44b5c8: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x4dda48u)) = 0x0u;	/* 44b5d2: mov dword ptr [0x4dda48], 0 */
	M32((DWORD)(0x9f6838u)) = m->esi;	/* 44b5dc: mov dword ptr [0x9f6838], esi */
	M32((DWORD)(0x9f900cu)) = m->esi;	/* 44b5e2: mov dword ptr [0x9f900c], esi */
	M32((DWORD)(0x9f8f18u)) = 0x0u;	/* 44b5e8: mov dword ptr [0x9f8f18], 0 */
	m->esp -= 4; M32(m->esp) = 0x44b5f7u; native_call(m, 0x44b7a0u);	/* 44b5f2: call 0x44b7a0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44b5f7: pop esi */
	m->esp += 4 + 0; return;	/* 44b5f8: ret  */
}

/* profile_scanSaves (0x4460d0), lifted by tools/lift.py */
static void lift_4460d0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x248u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4460d0: sub esp, 0x248 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4460d6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4460d7: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4460d8: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4460d9: push edi */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4460da: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x4460e4u; native_call(m, 0x49f8a6u);	/* 4460df: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4460e4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4460e7: test eax, eax */
	if (m->zf) goto L_44611b;	/* 4460e9: je 0x44611b */
	{ DWORD v_ = 0x9dae7cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4460eb: push 0x9dae7c */
	m->esp -= 4; M32(m->esp) = 0x4460f5u; native_call(m, 0x49f8a6u);	/* 4460f0: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4460f5: add esp, 4 */
	{ DWORD v_ = 0x4b2accu; m->esp -= 4; M32(m->esp) = v_; }	/* 4460f8: push 0x4b2acc */
	m->esp -= 4; M32(m->esp) = 0x446103u; native_call(m, M32(0x4a9104u));	/* 4460fd: call dword ptr [0x4a9104] */
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 446103: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x44610du; native_call(m, 0x49f8a6u);	/* 446108: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44610d: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 446110: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 446111: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 446112: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 446113: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x248u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446114: add esp, 0x248 */
	m->esp += 4 + 0; return;	/* 44611a: ret  */
L_44611b:
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 44611b: lea eax, [esp + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44611f: push eax */
	{ DWORD v_ = 0x4b2ac4u; m->esp -= 4; M32(m->esp) = v_; }	/* 446120: push 0x4b2ac4 */
	m->esp -= 4; M32(m->esp) = 0x44612au; native_call(m, 0x49f694u);	/* 446125: call 0x49f694 */
	m->ebx = m->eax;	/* 44612a: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44612c: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44612f: test ebx, ebx */
	if (m->sf == m->of) goto L_446152;	/* 446131: jge 0x446152 */
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 446133: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x44613du; native_call(m, 0x49f8a6u);	/* 446138: call 0x49f8a6 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44613d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x446144u; native_call(m, 0x445f70u);	/* 44613f: call 0x445f70 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446144: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 446147: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 446148: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 446149: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44614a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x248u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44614b: add esp, 0x248 */
	m->esp += 4 + 0; return;	/* 446151: ret  */
L_446152:
	m->edi = (DWORD)(m->esp + 0x50u);	/* 446152: lea edi, [esp + 0x50] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446156: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446159: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44615b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44615d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44615f: sub edi, ecx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 446161: lea eax, [esp + 0x3c] */
	m->edx = m->ecx;	/* 446165: mov edx, ecx */
	m->esi = m->edi;	/* 446167: mov esi, edi */
	m->edi = 0x9f1ac4u;	/* 446169: mov edi, 0x9f1ac4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44616e: push eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44616f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446172: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 446174: mov ecx, edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446176: push ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446177: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44617a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x1u;	/* 44617c: mov edi, 1 */
	M32((DWORD)(m->esp + 0x18u)) = m->edi;	/* 446181: mov dword ptr [esp + 0x18], edi */
	m->esp -= 4; M32(m->esp) = 0x44618au; native_call(m, 0x49f75eu);	/* 446185: call 0x49f75e */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44618a: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44618d: test eax, eax */
	if (!m->zf) goto L_4461d4;	/* 44618f: jne 0x4461d4 */
	m->ebp = 0x9f1b04u;	/* 446191: mov ebp, 0x9f1b04 */
L_446196:
	m->edi = (DWORD)(m->esp + 0x50u);	/* 446196: lea edi, [esp + 0x50] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44619a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44619d: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44619f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4461a1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4461a3: sub edi, ecx */
	m->eax = (DWORD)(m->esp + 0x3cu);	/* 4461a5: lea eax, [esp + 0x3c] */
	m->edx = m->ecx;	/* 4461a9: mov edx, ecx */
	m->esi = m->edi;	/* 4461ab: mov esi, edi */
	m->edi = m->ebp;	/* 4461ad: mov edi, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4461af: push eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4461b0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4461b3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4461b5: mov ecx, edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4461b7: push ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4461b8: and ecx, 3 */
	{ DWORD a_ = m->ebp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4461bb: add ebp, 0x40 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4461be: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esp + 0x18u)) = r_; }	/* 4461c0: inc dword ptr [esp + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x4461c9u; native_call(m, 0x49f75eu);	/* 4461c4: call 0x49f75e */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4461c9: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4461cc: test eax, eax */
	if (m->zf) goto L_446196;	/* 4461ce: je 0x446196 */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 4461d0: mov edi, dword ptr [esp + 0x10] */
L_4461d4:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4461d4: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4461dau; native_call(m, 0x49f823u);	/* 4461d5: call 0x49f823 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4461da: add esp, 4 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 4461dd: mov dword ptr [esp + 0x14], 0 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4461e5: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_446319;	/* 4461e7: jle 0x446319 */
	m->ebp = 0x9f688cu;	/* 4461ed: mov ebp, 0x9f688c */
	m->ebx = 0x9f1ac4u;	/* 4461f2: mov ebx, 0x9f1ac4 */
	M32((DWORD)(m->esp + 0x18u)) = m->edi;	/* 4461f7: mov dword ptr [esp + 0x18], edi */
L_4461fb:
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 4461fb: push 0x4ad170 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 446200: push ebx */
	m->esp -= 4; M32(m->esp) = 0x446206u; native_call(m, 0x49e9cau);	/* 446201: call 0x49e9ca */
	m->esi = m->eax;	/* 446206: mov esi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 446208: push 0 */
	{ DWORD v_ = 0x4e20u; m->esp -= 4; M32(m->esp) = v_; }	/* 44620a: push 0x4e20 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44620f: push esi */
	m->esp -= 4; M32(m->esp) = 0x446215u; native_call(m, 0x49e91eu);	/* 446210: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 446215: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 446216: push 1 */
	m->ecx = (DWORD)(m->esp + 0x170u);	/* 446218: lea ecx, [esp + 0x170] */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 44621f: push 0x104 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 446224: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44622au; native_call(m, 0x49e836u);	/* 446225: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44622a: push esi */
	m->esp -= 4; M32(m->esp) = 0x446230u; native_call(m, 0x49e7e0u);	/* 44622b: call 0x49e7e0 */
	m->edx = (DWORD)(m->esp + 0x17cu);	/* 446230: lea edx, [esp + 0x17c] */
	{ DWORD v_ = 0x7eu; m->esp -= 4; M32(m->esp) = v_; }	/* 446237: push 0x7e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 446239: push edx */
	m->esp -= 4; M32(m->esp) = 0x44623fu; native_call(m, 0x445f10u);	/* 44623a: call 0x445f10 */
	m->ecx = 0x41u;	/* 44623f: mov ecx, 0x41 */
	m->esi = (DWORD)(m->esp + 0x184u);	/* 446244: lea esi, [esp + 0x184] */
	m->edi = 0x9f61d8u;	/* 44624b: mov edi, 0x9f61d8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446250: xor eax, eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446252: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = 0x8u;	/* 446254: mov ecx, 8 */
	m->edi = (DWORD)(m->esp + 0x4cu);	/* 446259: lea edi, [esp + 0x4c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44625d: rep stosd dword ptr es:[edi], eax */
	m->edi = m->ebx;	/* 44625f: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 446261: or ecx, 0xffffffff */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446264: add esp, 0x30 */
	m->esi = m->ebx;	/* 446267: mov esi, ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 446269: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44626b: not ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44626d: add ecx, -5 */
	m->edi = (DWORD)(m->esp + 0x1cu);	/* 446270: lea edi, [esp + 0x1c] */
	m->eax = m->ecx;	/* 446274: mov eax, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 446276: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 446279: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44627b: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44627d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 446280: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b0fa0u;	/* 446282: mov edi, 0x4b0fa0 */
	m->esi = 0x9f61d8u;	/* 446287: mov esi, 0x9f61d8 */
L_44628c:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 44628c: mov cl, byte ptr [esi] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 44628e: mov dl, byte ptr [edi] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((((m->ecx >> 0) & 0xff)) & 0xff) << 0);	/* 446290: mov al, cl */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 446292: cmp cl, dl */
	if (!m->zf) goto L_4462b4;	/* 446294: jne 0x4462b4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 446296: test al, al */
	if (m->zf) goto L_4462b0;	/* 446298: je 0x4462b0 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 44629a: mov dl, byte ptr [esi + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 44629d: mov cl, byte ptr [edi + 1] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 4462a0: mov al, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4462a2: cmp dl, cl */
	if (!m->zf) goto L_4462b4;	/* 4462a4: jne 0x4462b4 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4462a6: add esi, 2 */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4462a9: add edi, 2 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4462ac: test al, al */
	if (!m->zf) goto L_44628c;	/* 4462ae: jne 0x44628c */
L_4462b0:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4462b0: xor eax, eax */
	goto L_4462b9;	/* 4462b2: jmp 0x4462b9 */
L_4462b4:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4462b4: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4462b6: sbb eax, -1 */
L_4462b9:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4462b9: test eax, eax */
	if (m->zf) goto L_4462c6;	/* 4462bb: je 0x4462c6 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4462bd: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4462c4u; native_call(m, M32(0x4a9104u));	/* 4462be: call dword ptr [0x4a9104] */
	goto L_446303;	/* 4462c4: jmp 0x446303 */
L_4462c6:
	m->edi = (DWORD)(m->esp + 0x1cu);	/* 4462c6: lea edi, [esp + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4462ca: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4462cd: xor eax, eax */
	m->edx = (DWORD)(m->ebp + 0xffffffc0u);	/* 4462cf: lea edx, [ebp - 0x40] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4462d2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4462d4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4462d6: sub edi, ecx */
	m->eax = m->ecx;	/* 4462d8: mov eax, ecx */
	m->esi = m->edi;	/* 4462da: mov esi, edi */
	m->edi = m->edx;	/* 4462dc: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4462de: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4462e1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4462e3: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4462e5: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4462e9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4462ec: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x254u));	/* 4462ee: mov ecx, dword ptr [esp + 0x254] */
	M32((DWORD)(m->ebp + 0x0u)) = m->ecx;	/* 4462f5: mov dword ptr [ebp], ecx */
	M32((DWORD)(m->ebp + 0xffffffbcu)) = m->eax;	/* 4462f8: mov dword ptr [ebp - 0x44], eax */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4462fb: inc eax */
	{ DWORD a_ = m->ebp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4462fc: add ebp, 0x48 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4462ff: mov dword ptr [esp + 0x14], eax */
L_446303:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 446303: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ebx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 446307: add ebx, 0x40 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44630a: dec eax */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 44630b: mov dword ptr [esp + 0x18], eax */
	if (!m->zf) goto L_4461fb;	/* 44630f: jne 0x4461fb */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 446315: mov edi, dword ptr [esp + 0x10] */
L_446319:
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 446319: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x446323u; native_call(m, 0x49f8a6u);	/* 44631e: call 0x49f8a6 */
	m->esp -= 4; M32(m->esp) = 0x446328u; native_call(m, 0x4474a0u);	/* 446323: call 0x4474a0 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 446328: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44632c: push edx */
	m->esp -= 4; M32(m->esp) = 0x446332u; native_call(m, 0x445f70u);	/* 44632d: call 0x445f70 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446332: add esp, 8 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 446335: xor edx, edx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 446337: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_44638d;	/* 446339: jle 0x44638d */
	m->ebp = 0x9f684cu;	/* 44633b: mov ebp, 0x9f684c */
L_446340:
	m->esi = 0x9f8fe8u;	/* 446340: mov esi, 0x9f8fe8 */
	m->eax = m->ebp;	/* 446345: mov eax, ebp */
L_446347:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 446347: mov bl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 0);	/* 446349: mov cl, bl */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 44634b: cmp bl, byte ptr [esi] */
	if (!m->zf) goto L_44636b;	/* 44634d: jne 0x44636b */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44634f: test cl, cl */
	if (m->zf) goto L_446367;	/* 446351: je 0x446367 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 446353: mov bl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 0);	/* 446356: mov cl, bl */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 446358: cmp bl, byte ptr [esi + 1] */
	if (!m->zf) goto L_44636b;	/* 44635b: jne 0x44636b */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44635d: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 446360: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 446363: test cl, cl */
	if (!m->zf) goto L_446347;	/* 446365: jne 0x446347 */
L_446367:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 446367: xor eax, eax */
	goto L_446370;	/* 446369: jmp 0x446370 */
L_44636b:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 44636b: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 44636d: sbb eax, -1 */
L_446370:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 446370: test eax, eax */
	if (m->zf) goto L_446387;	/* 446372: je 0x446387 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 446374: inc edx */
	{ DWORD a_ = m->ebp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 446375: add ebp, 0x48 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 446378: cmp edx, edi */
	if (m->sf != m->of) goto L_446340;	/* 44637a: jl 0x446340 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44637c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44637d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44637e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44637f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x248u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446380: add esp, 0x248 */
	m->esp += 4 + 0; return;	/* 446386: ret  */
L_446387:
	M32((DWORD)(0x9f8c58u)) = m->edx;	/* 446387: mov dword ptr [0x9f8c58], edx */
L_44638d:
	m->edi = M32(m->esp); m->esp += 4;	/* 44638d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44638e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44638f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 446390: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x248u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 446391: add esp, 0x248 */
	m->esp += 4 + 0; return;	/* 446397: ret  */
}

/* autoplay_startRecording (0x487cb0), lifted by tools/lift.py */
static void lift_487cb0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487cb0: sub esp, 0x104 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 487cb6: push ebx */
	m->ebx = m->ecx;	/* 487cb7: mov ebx, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487cb9: push ebp */
	m->ebp = 0x1u;	/* 487cba: mov ebp, 1 */
	m->eax = M32((DWORD)(m->ebx + 0x2340d1du));	/* 487cbf: mov eax, dword ptr [ebx + 0x2340d1d] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487cc5: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487cc6: cmp eax, ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 487cc8: push edi */
	if (!m->zf) goto L_487cd0;	/* 487cc9: jne 0x487cd0 */
	m->esp -= 4; M32(m->esp) = 0x487cd0u; native_call(m, 0x487ed0u);	/* 487ccb: call 0x487ed0 */
L_487cd0:
	m->edi = M32((DWORD)(m->esp + 0x118u));	/* 487cd0: mov edi, dword ptr [esp + 0x118] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487cd7: test edi, edi */
	if (m->zf) goto L_487d30;	/* 487cd9: je 0x487d30 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 487cdb: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 487cde: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 487ce0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 487ce2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 487ce4: sub edi, ecx */
	m->edx = (DWORD)(m->ebx + 0x2340d0cu);	/* 487ce6: lea edx, [ebx + 0x2340d0c] */
	m->eax = m->ecx;	/* 487cec: mov eax, ecx */
	m->esi = m->edi;	/* 487cee: mov esi, edi */
	m->edi = m->edx;	/* 487cf0: mov edi, edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487cf2: push edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 487cf3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 487cf6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 487cf8: mov ecx, eax */
	{ DWORD v_ = 0x4c7cc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487cfa: push 0x4c7cc8 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 487cff: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 487d02: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 487d04: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487d08: push ecx */
	m->esp -= 4; M32(m->esp) = 0x487d0eu; native_call(m, 0x49e9ddu);	/* 487d09: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 487d0e: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 487d12: push 0x4b2ab0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487d17: push edx */
	m->esp -= 4; M32(m->esp) = 0x487d1du; native_call(m, 0x49e9cau);	/* 487d18: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487d1d: add esp, 0x14 */
	M32((DWORD)(m->ebx + 0x2340d08u)) = m->eax;	/* 487d20: mov dword ptr [ebx + 0x2340d08], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487d26: test eax, eax */
	if (m->zf) goto L_487ec2;	/* 487d28: je 0x487ec2 */
	goto L_487d9c;	/* 487d2e: jmp 0x487d9c */
L_487d30:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 487d30: xor esi, esi */
	m->edi = (DWORD)(m->ebx + 0x2340d0cu);	/* 487d32: lea edi, [ebx + 0x2340d0c] */
L_487d38:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487d38: push esi */
	{ DWORD v_ = 0x4c7cb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487d39: push 0x4c7cb8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 487d3e: push edi */
	m->esp -= 4; M32(m->esp) = 0x487d44u; native_call(m, 0x49e9ddu);	/* 487d3f: call 0x49e9dd */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 487d44: push edi */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 487d45: lea eax, [esp + 0x24] */
	{ DWORD v_ = 0x4c7cc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487d49: push 0x4c7cc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487d4e: push eax */
	m->esp -= 4; M32(m->esp) = 0x487d54u; native_call(m, 0x49e9ddu);	/* 487d4f: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 487d54: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487d58: push ecx */
	m->esp -= 4; M32(m->esp) = 0x487d5eu; native_call(m, 0x46ca70u);	/* 487d59: call 0x46ca70 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487d5e: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487d61: test eax, eax */
	if (m->zf) goto L_487d7c;	/* 487d63: je 0x487d7c */
	{ DWORD a_ = m->esi, b_ = 0x3e7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487d65: cmp esi, 0x3e7 */
	if (m->zf) goto L_487ec2;	/* 487d6b: je 0x487ec2 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 487d71: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x3e8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487d72: cmp esi, 0x3e8 */
	if (m->sf != m->of) goto L_487d38;	/* 487d78: jl 0x487d38 */
	goto L_487d9c;	/* 487d7a: jmp 0x487d9c */
L_487d7c:
	m->edx = (DWORD)(m->esp + 0x14u);	/* 487d7c: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 487d80: push 0x4b2ab0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487d85: push edx */
	m->esp -= 4; M32(m->esp) = 0x487d8bu; native_call(m, 0x49e9cau);	/* 487d86: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487d8b: add esp, 8 */
	M32((DWORD)(m->ebx + 0x2340d08u)) = m->eax;	/* 487d8e: mov dword ptr [ebx + 0x2340d08], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487d94: test eax, eax */
	if (m->zf) goto L_487ec2;	/* 487d96: je 0x487ec2 */
L_487d9c:
	m->eax = M32((DWORD)(m->ebx + 0x2340d08u));	/* 487d9c: mov eax, dword ptr [ebx + 0x2340d08] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 487da2: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487da6: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487da7: push ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 487da8: xor esi, esi */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487daa: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487dac: push ecx */
	M32((DWORD)(m->ebx + 0x2340d1du)) = m->ebp;	/* 487dad: mov dword ptr [ebx + 0x2340d1d], ebp */
	M32((DWORD)(m->ebx + 0x2340d29u)) = m->esi;	/* 487db3: mov dword ptr [ebx + 0x2340d29], esi */
	M32((DWORD)(m->esp + 0x20u)) = 0x1201u;	/* 487db9: mov dword ptr [esp + 0x20], 0x1201 */
	m->esp -= 4; M32(m->esp) = 0x487dc6u; native_call(m, 0x46cc30u);	/* 487dc1: call 0x46cc30 */
	m->edx = M32((DWORD)(m->ebx + 0x2340d08u));	/* 487dc6: mov edx, dword ptr [ebx + 0x2340d08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487dcc: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487dcd: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487dce: push 4 */
	{ DWORD v_ = 0x5ae9c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487dd0: push 0x5ae9c4 */
	m->esp -= 4; M32(m->esp) = 0x487ddau; native_call(m, 0x46cc30u);	/* 487dd5: call 0x46cc30 */
	m->eax = M32((DWORD)(m->ebx + 0x2340d08u));	/* 487dda: mov eax, dword ptr [ebx + 0x2340d08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487de0: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487de1: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487de2: push 4 */
	{ DWORD v_ = 0x9dad94u; m->esp -= 4; M32(m->esp) = v_; }	/* 487de4: push 0x9dad94 */
	m->esp -= 4; M32(m->esp) = 0x487deeu; native_call(m, 0x46cc30u);	/* 487de9: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->ebx + 0x2340d08u));	/* 487dee: mov ecx, dword ptr [ebx + 0x2340d08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487df4: push ecx */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 487df5: push 0x20 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487df7: push ebp */
	{ DWORD v_ = 0x67fb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 487df8: push 0x67fb44 */
	m->esp -= 4; M32(m->esp) = 0x487e02u; native_call(m, 0x46cc30u);	/* 487dfd: call 0x46cc30 */
	m->edx = M32((DWORD)(m->ebx + 0x2340d08u));	/* 487e02: mov edx, dword ptr [ebx + 0x2340d08] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487e08: add esp, 0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487e0b: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487e0c: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487e0d: push 4 */
	{ DWORD v_ = 0x9da3e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 487e0f: push 0x9da3e0 */
	m->esp -= 4; M32(m->esp) = 0x487e19u; native_call(m, 0x46cc30u);	/* 487e14: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->ebx + 0x2340d08u));	/* 487e19: mov ecx, dword ptr [ebx + 0x2340d08] */
	m->eax = M32((DWORD)(m->ebx + 0x22e7180u));	/* 487e1f: mov eax, dword ptr [ebx + 0x22e7180] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487e25: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487e26: push ebp */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 487e27: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487e2b: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487e2d: push edx */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 487e2e: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x487e37u; native_call(m, 0x46cc30u);	/* 487e32: call 0x46cc30 */
	m->eax = M32((DWORD)(m->ebx + 0x2340d08u));	/* 487e37: mov eax, dword ptr [ebx + 0x2340d08] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487e3d: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487e3e: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487e3f: push 4 */
	{ DWORD v_ = 0x4df8e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487e41: push 0x4df8e8 */
	m->esp -= 4; M32(m->esp) = 0x487e4bu; native_call(m, 0x46cc30u);	/* 487e46: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->ebx + 0x2340d08u));	/* 487e4b: mov ecx, dword ptr [ebx + 0x2340d08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487e51: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487e52: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487e53: push 4 */
	{ DWORD v_ = 0x76d408u; m->esp -= 4; M32(m->esp) = v_; }	/* 487e55: push 0x76d408 */
	m->esp -= 4; M32(m->esp) = 0x487e5fu; native_call(m, 0x46cc30u);	/* 487e5a: call 0x46cc30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487e5f: add esp, 0x40 */
	m->edi = (DWORD)(m->ebx + 0x2343012u);	/* 487e62: lea edi, [ebx + 0x2343012] */
L_487e68:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487e68: push esi */
	m->esp -= 4; M32(m->esp) = 0x487e6eu; native_call(m, 0x4a8700u);	/* 487e69: call 0x4a8700 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487e6e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487e71: cmp eax, ebp */
	if (!m->zf) goto L_487e7a;	/* 487e73: jne 0x487e7a */
	M32((DWORD)(m->edi + 0xfffffffcu)) = m->ebp;	/* 487e75: mov dword ptr [edi - 4], ebp */
	M32((DWORD)(m->edi + 0x0u)) = m->ebp;	/* 487e78: mov dword ptr [edi], ebp */
L_487e7a:
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 487e7a: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 487e7b: add edi, 0x10 */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487e7e: cmp esi, 0x10 */
	if (m->sf != m->of) goto L_487e68;	/* 487e81: jl 0x487e68 */
	m->edx = M32((DWORD)(m->ebx + 0x234240du));	/* 487e83: mov edx, dword ptr [ebx + 0x234240d] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 487e89: shl edx, 4 */
	M32((DWORD)(m->edx + m->ebx*1 + 0x234300au)) = m->ebp;	/* 487e8c: mov dword ptr [edx + ebx + 0x234300a], ebp */
	m->ecx = M32((DWORD)(m->ebx + 0x234240du));	/* 487e93: mov ecx, dword ptr [ebx + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 487e99: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 487e9c: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 487e9f: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 487ea1: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 487ea4: lea ecx, [ecx + eax*8] */
	M32((DWORD)(m->ebx + m->ecx*2 + 0x179d1feu)) = 0x0u;	/* 487ea7: mov dword ptr [ebx + ecx*2 + 0x179d1fe], 0 */
	m->edx = M32((DWORD)(m->ebx + 0x234240du));	/* 487eb2: mov edx, dword ptr [ebx + 0x234240d] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 487eb8: shl edx, 4 */
	M32((DWORD)(m->edx + m->ebx*1 + 0x2343006u)) = m->ebp;	/* 487ebb: mov dword ptr [edx + ebx + 0x2343006], ebp */
L_487ec2:
	m->edi = M32(m->esp); m->esp += 4;	/* 487ec2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 487ec3: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 487ec4: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 487ec5: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487ec6: add esp, 0x104 */
	m->esp += 4 + 4; return;	/* 487ecc: ret 4 */
}

/* dplay_enumConnections (0x4532f0), lifted by tools/lift.py */
static void lift_4532f0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0bac8u));	/* 4532f0: mov eax, dword ptr [0xa0bac8] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4532f5: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->esp, b_ = 0x500u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4532f9: sub esp, 0x500 */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4532ff: shl eax, 7 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 453302: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453303: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 453304: push edi */
	m->edi = M32((DWORD)(m->ecx + 0x8u));	/* 453305: mov edi, dword ptr [ecx + 8] */
	m->edx = (DWORD)(m->esp + m->eax*1 + 0xcu);	/* 453308: lea edx, [esp + eax + 0xc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45330c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45330f: xor eax, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453311: push edx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 453312: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 453314: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 453316: sub edi, ecx */
	m->eax = m->ecx;	/* 453318: mov eax, ecx */
	m->esi = m->edi;	/* 45331a: mov esi, edi */
	m->edi = m->edx;	/* 45331c: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45331e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 453321: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 453323: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 453325: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 453328: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x45332fu; native_call(m, 0x49fab5u);	/* 45332a: call 0x49fab5 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 45332f: push 0x10 */
	m->esp -= 4; M32(m->esp) = 0x453336u; native_call(m, 0x49f1aau);	/* 453331: call 0x49f1aa */
	m->ebx = m->eax;	/* 453336: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453338: add esp, 8 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45333b: test ebx, ebx */
	if (m->zf) goto L_453546;	/* 45333d: je 0x453546 */
	m->ecx = M32((DWORD)(m->esp + 0x510u));	/* 453343: mov ecx, dword ptr [esp + 0x510] */
	m->edx = m->ebx;	/* 45334a: mov edx, ebx */
	m->esi = M32((DWORD)(m->esp + 0x518u));	/* 45334c: mov esi, dword ptr [esp + 0x518] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 453353: mov eax, dword ptr [ecx] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453355: push esi */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 453356: mov dword ptr [edx], eax */
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 453358: push 0x42 */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 45335a: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 45335d: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->ecx + 0x8u));	/* 453360: mov eax, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 453363: mov dword ptr [edx + 8], eax */
	m->ecx = M32((DWORD)(m->ecx + 0xcu));	/* 453366: mov ecx, dword ptr [ecx + 0xc] */
	M32((DWORD)(m->edx + 0xcu)) = m->ecx;	/* 453369: mov dword ptr [edx + 0xc], ecx */
	m->esp -= 4; M32(m->esp) = 0x453372u; native_call(m, M32(0x4a9070u));	/* 45336c: call dword ptr [0x4a9070] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453372: push eax */
	m->esp -= 4; M32(m->esp) = 0x453379u; native_call(m, M32(0x4a9198u));	/* 453373: call dword ptr [0x4a9198] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453379: test eax, eax */
	M32((DWORD)(0xa0bab0u)) = m->eax;	/* 45337b: mov dword ptr [0xa0bab0], eax */
	if (m->zf) goto L_453546;	/* 453380: je 0x453546 */
	m->ecx = m->esi;	/* 453386: mov ecx, esi */
	m->esi = M32((DWORD)(m->esp + 0x514u));	/* 453388: mov esi, dword ptr [esp + 0x514] */
	m->edx = m->ecx;	/* 45338f: mov edx, ecx */
	m->edi = m->eax;	/* 453391: mov edi, eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 453393: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 453396: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 453398: mov ecx, edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45339a: push 1 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45339c: and ecx, 3 */
	{ DWORD v_ = 0x4b3e64u; m->esp -= 4; M32(m->esp) = v_; }	/* 45339f: push 0x4b3e64 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4533a4: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(0xa0bac8u));	/* 4533a6: mov eax, dword ptr [0xa0bac8] */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4533ab: shl eax, 7 */
	m->ecx = (DWORD)(m->esp + m->eax*1 + 0x14u);	/* 4533ae: lea ecx, [esp + eax + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4533b2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4533b8u; native_call(m, 0x454d90u);	/* 4533b3: call 0x454d90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4533b8: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4533bb: test eax, eax */
	if (m->zf) goto L_4533f3;	/* 4533bd: je 0x4533f3 */
	m->edx = m->ebx;	/* 4533bf: mov edx, ebx */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 4533c1: mov eax, dword ptr [edx] */
	M32((DWORD)(0xa0b3a0u)) = m->eax;	/* 4533c3: mov dword ptr [0xa0b3a0], eax */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 4533c8: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(0xa0b3a4u)) = m->ecx;	/* 4533cb: mov dword ptr [0xa0b3a4], ecx */
	m->eax = M32((DWORD)(m->edx + 0x8u));	/* 4533d1: mov eax, dword ptr [edx + 8] */
	M32((DWORD)(0xa0b3a8u)) = m->eax;	/* 4533d4: mov dword ptr [0xa0b3a8], eax */
	m->ecx = M32((DWORD)(m->edx + 0xcu));	/* 4533d9: mov ecx, dword ptr [edx + 0xc] */
	m->edx = M32((DWORD)(0xa0bab0u));	/* 4533dc: mov edx, dword ptr [0xa0bab0] */
	M32((DWORD)(0xa0b3acu)) = m->ecx;	/* 4533e2: mov dword ptr [0xa0b3ac], ecx */
	M32((DWORD)(0xa0bae0u)) = m->edx;	/* 4533e8: mov dword ptr [0xa0bae0], edx */
	goto L_45352d;	/* 4533ee: jmp 0x45352d */
L_4533f3:
	m->eax = M32((DWORD)(0xa0bac8u));	/* 4533f3: mov eax, dword ptr [0xa0bac8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4533f8: push 1 */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4533fa: shl eax, 7 */
	{ DWORD v_ = 0x4b3e60u; m->esp -= 4; M32(m->esp) = v_; }	/* 4533fd: push 0x4b3e60 */
	m->ecx = (DWORD)(m->esp + m->eax*1 + 0x14u);	/* 453402: lea ecx, [esp + eax + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453406: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45340cu; native_call(m, 0x454d90u);	/* 453407: call 0x454d90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45340c: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45340f: test eax, eax */
	if (m->zf) goto L_453447;	/* 453411: je 0x453447 */
	m->edx = m->ebx;	/* 453413: mov edx, ebx */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 453415: mov eax, dword ptr [edx] */
	M32((DWORD)(0xa0b450u)) = m->eax;	/* 453417: mov dword ptr [0xa0b450], eax */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 45341c: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(0xa0b454u)) = m->ecx;	/* 45341f: mov dword ptr [0xa0b454], ecx */
	m->eax = M32((DWORD)(m->edx + 0x8u));	/* 453425: mov eax, dword ptr [edx + 8] */
	M32((DWORD)(0xa0b458u)) = m->eax;	/* 453428: mov dword ptr [0xa0b458], eax */
	m->ecx = M32((DWORD)(m->edx + 0xcu));	/* 45342d: mov ecx, dword ptr [edx + 0xc] */
	m->edx = M32((DWORD)(0xa0bab0u));	/* 453430: mov edx, dword ptr [0xa0bab0] */
	M32((DWORD)(0xa0b45cu)) = m->ecx;	/* 453436: mov dword ptr [0xa0b45c], ecx */
	M32((DWORD)(0xa0bae4u)) = m->edx;	/* 45343c: mov dword ptr [0xa0bae4], edx */
	goto L_45352d;	/* 453442: jmp 0x45352d */
L_453447:
	m->eax = M32((DWORD)(0xa0bac8u));	/* 453447: mov eax, dword ptr [0xa0bac8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45344c: push 1 */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45344e: shl eax, 7 */
	{ DWORD v_ = 0x4b3e58u; m->esp -= 4; M32(m->esp) = v_; }	/* 453451: push 0x4b3e58 */
	m->ecx = (DWORD)(m->esp + m->eax*1 + 0x14u);	/* 453456: lea ecx, [esp + eax + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45345a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x453460u; native_call(m, 0x454d90u);	/* 45345b: call 0x454d90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453460: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453463: test eax, eax */
	if (!m->zf) goto L_4534fe;	/* 453465: jne 0x4534fe */
	m->edx = M32((DWORD)(0xa0bac8u));	/* 45346b: mov edx, dword ptr [0xa0bac8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 453471: push 1 */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 453473: shl edx, 7 */
	{ DWORD v_ = 0x4b3e50u; m->esp -= 4; M32(m->esp) = v_; }	/* 453476: push 0x4b3e50 */
	m->eax = (DWORD)(m->esp + m->edx*1 + 0x14u);	/* 45347b: lea eax, [esp + edx + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45347f: push eax */
	m->esp -= 4; M32(m->esp) = 0x453485u; native_call(m, 0x454d90u);	/* 453480: call 0x454d90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453485: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453488: test eax, eax */
	if (!m->zf) goto L_4534fe;	/* 45348a: jne 0x4534fe */
	m->ecx = M32((DWORD)(0xa0bac8u));	/* 45348c: mov ecx, dword ptr [0xa0bac8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 453492: push 1 */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 453494: shl ecx, 7 */
	{ DWORD v_ = 0x4b3e48u; m->esp -= 4; M32(m->esp) = v_; }	/* 453497: push 0x4b3e48 */
	m->edx = (DWORD)(m->esp + m->ecx*1 + 0x14u);	/* 45349c: lea edx, [esp + ecx + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4534a0: push edx */
	m->esp -= 4; M32(m->esp) = 0x4534a6u; native_call(m, 0x454d90u);	/* 4534a1: call 0x454d90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4534a6: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4534a9: test eax, eax */
	if (!m->zf) goto L_4534cd;	/* 4534ab: jne 0x4534cd */
	m->eax = M32((DWORD)(0xa0bac8u));	/* 4534ad: mov eax, dword ptr [0xa0bac8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4534b2: push 1 */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4534b4: shl eax, 7 */
	{ DWORD v_ = 0x4b3e40u; m->esp -= 4; M32(m->esp) = v_; }	/* 4534b7: push 0x4b3e40 */
	m->ecx = (DWORD)(m->esp + m->eax*1 + 0x14u);	/* 4534bc: lea ecx, [esp + eax + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4534c0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4534c6u; native_call(m, 0x454d90u);	/* 4534c1: call 0x454d90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4534c6: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4534c9: test eax, eax */
	if (m->zf) goto L_45352d;	/* 4534cb: je 0x45352d */
L_4534cd:
	m->edx = m->ebx;	/* 4534cd: mov edx, ebx */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 4534cf: mov eax, dword ptr [edx] */
	M32((DWORD)(0xa0bab8u)) = m->eax;	/* 4534d1: mov dword ptr [0xa0bab8], eax */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 4534d6: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(0xa0babcu)) = m->ecx;	/* 4534d9: mov dword ptr [0xa0babc], ecx */
	m->eax = M32((DWORD)(m->edx + 0x8u));	/* 4534df: mov eax, dword ptr [edx + 8] */
	M32((DWORD)(0xa0bac0u)) = m->eax;	/* 4534e2: mov dword ptr [0xa0bac0], eax */
	m->ecx = M32((DWORD)(m->edx + 0xcu));	/* 4534e7: mov ecx, dword ptr [edx + 0xc] */
	m->edx = M32((DWORD)(0xa0bab0u));	/* 4534ea: mov edx, dword ptr [0xa0bab0] */
	M32((DWORD)(0xa0bac4u)) = m->ecx;	/* 4534f0: mov dword ptr [0xa0bac4], ecx */
	M32((DWORD)(0xa0baecu)) = m->edx;	/* 4534f6: mov dword ptr [0xa0baec], edx */
	goto L_45352d;	/* 4534fc: jmp 0x45352d */
L_4534fe:
	m->eax = m->ebx;	/* 4534fe: mov eax, ebx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 453500: mov ecx, dword ptr [eax] */
	M32((DWORD)(0xa0b408u)) = m->ecx;	/* 453502: mov dword ptr [0xa0b408], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 453508: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(0xa0b40cu)) = m->edx;	/* 45350b: mov dword ptr [0xa0b40c], edx */
	m->ecx = M32((DWORD)(m->eax + 0x8u));	/* 453511: mov ecx, dword ptr [eax + 8] */
	M32((DWORD)(0xa0b410u)) = m->ecx;	/* 453514: mov dword ptr [0xa0b410], ecx */
	m->edx = M32((DWORD)(m->eax + 0xcu));	/* 45351a: mov edx, dword ptr [eax + 0xc] */
	m->eax = M32((DWORD)(0xa0bab0u));	/* 45351d: mov eax, dword ptr [0xa0bab0] */
	M32((DWORD)(0xa0b414u)) = m->edx;	/* 453522: mov dword ptr [0xa0b414], edx */
	M32((DWORD)(0xa0bae8u)) = m->eax;	/* 453528: mov dword ptr [0xa0bae8], eax */
L_45352d:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45352d: push ebx */
	m->esp -= 4; M32(m->esp) = 0x453533u; native_call(m, 0x49ef24u);	/* 45352e: call 0x49ef24 */
	m->eax = M32((DWORD)(0xa0bac8u));	/* 453533: mov eax, dword ptr [0xa0bac8] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453538: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45353b: cmp eax, 9 */
	if (m->sf == m->of) goto L_453546;	/* 45353e: jge 0x453546 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 453540: inc eax */
	M32((DWORD)(0xa0bac8u)) = m->eax;	/* 453541: mov dword ptr [0xa0bac8], eax */
L_453546:
	m->edi = M32(m->esp); m->esp += 4;	/* 453546: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 453547: pop esi */
	m->eax = 0x1u;	/* 453548: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45354d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x500u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45354e: add esp, 0x500 */
	m->esp += 4 + 24; return;	/* 453554: ret 0x18 */
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
