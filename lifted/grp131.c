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

static void lift_427920(X86 *m);
static void lift_445be0(X86 *m);
static void lift_44f860(X86 *m);
static void lift_452ec0(X86 *m);
static void lift_443530(X86 *m);

/* menuState300_frame (0x443530), lifted by tools/lift.py */
static void lift_443530(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x443535u; native_call(m, 0x441740u);	/* 443530: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x44353au; native_call(m, 0x442050u);	/* 443535: call 0x442050 */
	m->eax = M32((DWORD)(0x9eeab4u));	/* 44353a: mov eax, dword ptr [0x9eeab4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44353f: test eax, eax */
	if (m->zf) goto L_443548;	/* 443541: je 0x443548 */
	m->esp -= 4; M32(m->esp) = 0x443548u; native_call(m, 0x4434f0u);	/* 443543: call 0x4434f0 */
L_443548:
	{ DWORD a_ = M32((DWORD)(0x67ef14u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443548: cmp dword ptr [0x67ef14], 1 */
	if (!m->zf) goto L_44356a;	/* 44354f: jne 0x44356a */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443551: push 1 */
	m->esp -= 4; M32(m->esp) = 0x443558u; native_call(m, 0x441250u);	/* 443553: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443558: add esp, 4 */
	M32((DWORD)(0x67ef20u)) = 0x270fu;	/* 44355b: mov dword ptr [0x67ef20], 0x270f */
	native_call(m, 0x40ce70u); return;	/* 443565: jmp 0x40ce70 */
L_44356a:
	m->esp += 4 + 0; return;	/* 44356a: ret  */
}

/* menuState600_setup (0x427920), lifted by tools/lift.py */
static void lift_427920(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x427925u; native_call(m, 0x441740u);	/* 427920: call 0x441740 */
	m->eax = M32((DWORD)(0x4ddac8u));	/* 427925: mov eax, dword ptr [0x4ddac8] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42792a: cmp eax, 2 */
	if (!m->zf && m->sf == m->of) goto L_427957;	/* 42792d: jg 0x427957 */
	if (m->zf) goto L_42794d;	/* 42792f: je 0x42794d */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427931: sub eax, 0 */
	if (m->zf) goto L_427943;	/* 427934: je 0x427943 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 427936: dec eax */
	if (!m->zf) goto L_427968;	/* 427937: jne 0x427968 */
	m->esp -= 4; M32(m->esp) = 0x42793eu; native_call(m, 0x4230e0u);	/* 427939: call 0x4230e0 */
	native_call(m, 0x427880u); return;	/* 42793e: jmp 0x427880 */
L_427943:
	m->esp -= 4; M32(m->esp) = 0x427948u; native_call(m, 0x4230e0u);	/* 427943: call 0x4230e0 */
	native_call(m, 0x427830u); return;	/* 427948: jmp 0x427830 */
L_42794d:
	m->esp -= 4; M32(m->esp) = 0x427952u; native_call(m, 0x4230e0u);	/* 42794d: call 0x4230e0 */
	native_call(m, 0x4278d0u); return;	/* 427952: jmp 0x4278d0 */
L_427957:
	{ DWORD a_ = m->eax, b_ = 0x29au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 427957: cmp eax, 0x29a */
	if (!m->zf) goto L_427968;	/* 42795c: jne 0x427968 */
	m->esp -= 4; M32(m->esp) = 0x427963u; native_call(m, 0x4277c0u);	/* 42795e: call 0x4277c0 */
	native_call(m, 0x423330u); return;	/* 427963: jmp 0x423330 */
L_427968:
	m->esp += 4 + 0; return;	/* 427968: ret  */
}

/* menuState900_skirmishSetup (0x445be0), lifted by tools/lift.py */
static void lift_445be0(X86 *m)
{
	m->eax = M32((DWORD)(0x9eeba8u));	/* 445be0: mov eax, dword ptr [0x9eeba8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445be5: test eax, eax */
	if (m->zf) goto L_445bee;	/* 445be7: je 0x445bee */
	m->esp -= 4; M32(m->esp) = 0x445beeu; native_call(m, 0x441740u);	/* 445be9: call 0x441740 */
L_445bee:
	{ DWORD a_ = M32((DWORD)(0x9ef1f0u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445bee: cmp dword ptr [0x9ef1f0], 2 */
	if (m->zf) goto L_445bfc;	/* 445bf5: je 0x445bfc */
	m->esp -= 4; M32(m->esp) = 0x445bfcu; native_call(m, 0x4445a0u);	/* 445bf7: call 0x4445a0 */
L_445bfc:
	m->esp -= 4; M32(m->esp) = 0x445c01u; native_call(m, 0x444130u);	/* 445bfc: call 0x444130 */
	m->eax = M32((DWORD)(0x9ef1f0u));	/* 445c01: mov eax, dword ptr [0x9ef1f0] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445c06: cmp eax, 1 */
	if (m->zf) goto L_445c3a;	/* 445c09: je 0x445c3a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445c0b: test eax, eax */
	if (m->zf) goto L_445c3a;	/* 445c0d: je 0x445c3a */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 445c0f: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445c14: test eax, eax */
	if (m->zf) goto L_445c3b;	/* 445c16: je 0x445c3b */
	m->eax = M32((DWORD)(0x9f16b4u));	/* 445c18: mov eax, dword ptr [0x9f16b4] */
	m->ecx = M32((DWORD)(0x9f16b0u));	/* 445c1d: mov ecx, dword ptr [0x9f16b0] */
	m->edx = M32((DWORD)(0x9f16acu));	/* 445c23: mov edx, dword ptr [0x9f16ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445c29: push eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 445c2a: mov eax, dword ptr [0x9f16a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445c2f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445c30: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445c31: push eax */
	m->esp -= 4; M32(m->esp) = 0x445c37u; native_call(m, 0x428c30u);	/* 445c32: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445c37: add esp, 0x10 */
L_445c3a:
	m->esp += 4 + 0; return;	/* 445c3a: ret  */
L_445c3b:
	m->eax = M32((DWORD)(0x9ef1f8u));	/* 445c3b: mov eax, dword ptr [0x9ef1f8] */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445c40: cmp eax, 0xa */
	if (m->zf) goto L_445c4f;	/* 445c43: je 0x445c4f */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445c45: cmp eax, 0x14 */
	if (!m->zf) goto L_445c3a;	/* 445c48: jne 0x445c3a */
	native_call(m, 0x445bd0u); return;	/* 445c4a: jmp 0x445bd0 */
L_445c4f:
	native_call(m, 0x445bc0u); return;	/* 445c4f: jmp 0x445bc0 */
}

/* menuState210_frame (0x44f860), lifted by tools/lift.py */
static void lift_44f860(X86 *m)
{
	m->eax = M32((DWORD)(0x9f6838u));	/* 44f860: mov eax, dword ptr [0x9f6838] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f865: test eax, eax */
	if (m->zf) goto L_44f86e;	/* 44f867: je 0x44f86e */
	native_call(m, 0x44f850u); return;	/* 44f869: jmp 0x44f850 */
L_44f86e:
	m->esp -= 4; M32(m->esp) = 0x44f873u; native_call(m, 0x441740u);	/* 44f86e: call 0x441740 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda48u)));	/* 44f873: fld dword ptr [0x4dda48] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 44f879: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44f87f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44f881: test ah, 0x41 */
	if (m->zf) goto L_44f92d;	/* 44f884: je 0x44f92d */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44f88a: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44f88b: push edi */
	m->esi = 0x9f9070u;	/* 44f88c: mov esi, 0x9f9070 */
	m->edi = 0x1eu;	/* 44f891: mov edi, 0x1e */
L_44f896:
	{ DWORD a_ = M32((DWORD)(m->esi + 0xfffffff8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f896: cmp dword ptr [esi - 8], edi */
	if (m->zf || m->sf != m->of) goto L_44f8a0;	/* 44f899: jle 0x44f8a0 */
	m->esp -= 4; M32(m->esp) = 0x44f8a0u; native_call(m, 0x42b590u);	/* 44f89b: call 0x42b590 */
L_44f8a0:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8a0: cmp dword ptr [esi], edi */
	if (m->zf || m->sf != m->of) goto L_44f8a9;	/* 44f8a2: jle 0x44f8a9 */
	m->esp -= 4; M32(m->esp) = 0x44f8a9u; native_call(m, 0x42b590u);	/* 44f8a4: call 0x42b590 */
L_44f8a9:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8a9: cmp dword ptr [esi + 4], edi */
	if (m->zf || m->sf != m->of) goto L_44f8b3;	/* 44f8ac: jle 0x44f8b3 */
	m->esp -= 4; M32(m->esp) = 0x44f8b3u; native_call(m, 0x42b590u);	/* 44f8ae: call 0x42b590 */
L_44f8b3:
	{ DWORD a_ = M32((DWORD)(m->esi + 0xfffffffcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8b3: cmp dword ptr [esi - 4], edi */
	if (m->zf || m->sf != m->of) goto L_44f8bd;	/* 44f8b6: jle 0x44f8bd */
	m->esp -= 4; M32(m->esp) = 0x44f8bdu; native_call(m, 0x42b590u);	/* 44f8b8: call 0x42b590 */
L_44f8bd:
	{ DWORD a_ = M32((DWORD)(m->esi + 0xcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8bd: cmp dword ptr [esi + 0xc], edi */
	if (m->zf || m->sf != m->of) goto L_44f8c7;	/* 44f8c0: jle 0x44f8c7 */
	m->esp -= 4; M32(m->esp) = 0x44f8c7u; native_call(m, 0x42b590u);	/* 44f8c2: call 0x42b590 */
L_44f8c7:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8c7: cmp dword ptr [esi + 8], edi */
	if (m->zf || m->sf != m->of) goto L_44f8d1;	/* 44f8ca: jle 0x44f8d1 */
	m->esp -= 4; M32(m->esp) = 0x44f8d1u; native_call(m, 0x42b590u);	/* 44f8cc: call 0x42b590 */
L_44f8d1:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x10u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8d1: cmp dword ptr [esi + 0x10], edi */
	if (m->zf || m->sf != m->of) goto L_44f8db;	/* 44f8d4: jle 0x44f8db */
	m->esp -= 4; M32(m->esp) = 0x44f8dbu; native_call(m, 0x42b590u);	/* 44f8d6: call 0x42b590 */
L_44f8db:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x18u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8db: cmp dword ptr [esi + 0x18], edi */
	if (m->zf || m->sf != m->of) goto L_44f8e5;	/* 44f8de: jle 0x44f8e5 */
	m->esp -= 4; M32(m->esp) = 0x44f8e5u; native_call(m, 0x42b590u);	/* 44f8e0: call 0x42b590 */
L_44f8e5:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x14u)), b_ = 0x32u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8e5: cmp dword ptr [esi + 0x14], 0x32 */
	if (m->zf || m->sf != m->of) goto L_44f8f0;	/* 44f8e9: jle 0x44f8f0 */
	m->esp -= 4; M32(m->esp) = 0x44f8f0u; native_call(m, 0x42b590u);	/* 44f8eb: call 0x42b590 */
L_44f8f0:
	{ DWORD a_ = m->esi, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44f8f0: add esi, 0x4c */
	{ DWORD a_ = m->esi, b_ = 0x9f931cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f8f3: cmp esi, 0x9f931c */
	if (m->sf != m->of) goto L_44f896;	/* 44f8f9: jl 0x44f896 */
	m->eax = M32((DWORD)(0x9f8f10u));	/* 44f8fb: mov eax, dword ptr [0x9f8f10] */
	m->edi = M32(m->esp); m->esp += 4;	/* 44f900: pop edi */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44f901: dec eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f902: pop esi */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f903: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_44f92d;	/* 44f906: ja 0x44f92d */
	switch (m->eax) { case 0: goto L_44f90f; case 1: goto L_44f914; case 2: goto L_44f919; case 3: goto L_44f91e; case 4: goto L_44f923; case 5: goto L_44f928; default: abort(); }	/* 44f908: jmp dword ptr [eax*4 + 0x44f930] */
L_44f90f:
	native_call(m, 0x44f410u); return;	/* 44f90f: jmp 0x44f410 */
L_44f914:
	native_call(m, 0x44f4b0u); return;	/* 44f914: jmp 0x44f4b0 */
L_44f919:
	native_call(m, 0x44f5f0u); return;	/* 44f919: jmp 0x44f5f0 */
L_44f91e:
	native_call(m, 0x44f6c0u); return;	/* 44f91e: jmp 0x44f6c0 */
L_44f923:
	native_call(m, 0x44f740u); return;	/* 44f923: jmp 0x44f740 */
L_44f928:
	native_call(m, 0x44f810u); return;	/* 44f928: jmp 0x44f810 */
L_44f92d:
	m->esp += 4 + 0; return;	/* 44f92d: ret  */
}

/* arena_452ec0 (0x452ec0), lifted by tools/lift.py */
static void lift_452ec0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 452ec0: sub esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 452ec3: xor eax, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452ec5: push esi */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 452ec6: mov dword ptr [esp + 4], eax */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 452eca: mov dword ptr [esp + 8], eax */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 452ece: mov dword ptr [esp + 0xc], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 452ed2: mov dword ptr [esp + 0x10], eax */
	m->esp -= 4; M32(m->esp) = 0x452edbu; native_call(m, 0x4515a0u);	/* 452ed6: call 0x4515a0 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 452edb: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(0xa0b390u)) = 0x1u;	/* 452edf: mov dword ptr [0xa0b390], 1 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452ee9: test eax, eax */
	if (m->zf) goto L_452f26;	/* 452eeb: je 0x452f26 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452eed: push eax */
	m->esp -= 4; M32(m->esp) = 0x452ef3u; native_call(m, 0x4547d0u);	/* 452eee: call 0x4547d0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 452ef3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452ef6: test eax, eax */
	if (m->zf) goto L_452fc8;	/* 452ef8: je 0x452fc8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 452efe: push edi */
	m->edi = 0xa0d320u;	/* 452eff: mov edi, 0xa0d320 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 452f04: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 452f07: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 452f09: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 452f0b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 452f0d: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x8u);	/* 452f0f: lea edx, [esp + 8] */
	m->eax = m->ecx;	/* 452f13: mov eax, ecx */
	m->esi = m->edi;	/* 452f15: mov esi, edi */
	m->edi = m->edx;	/* 452f17: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 452f19: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 452f1c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 452f1e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 452f20: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 452f23: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 452f25: pop edi */
L_452f26:
	m->eax = M32((DWORD)(0xa0b384u));	/* 452f26: mov eax, dword ptr [0xa0b384] */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 452f2b: mov esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452f2f: test eax, eax */
	if (m->zf) goto L_452f51;	/* 452f31: je 0x452f51 */
	{ DWORD a_ = M32((DWORD)(0xa0b418u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452f33: cmp dword ptr [0xa0b418], esi */
	if (!m->zf) goto L_452f4c;	/* 452f39: jne 0x452f4c */
	m->esp -= 4; M32(m->esp) = 0x452f40u; native_call(m, 0x452fe0u);	/* 452f3b: call 0x452fe0 */
	M32((DWORD)(0xa0b384u)) = 0x0u;	/* 452f40: mov dword ptr [0xa0b384], 0 */
	goto L_452f51;	/* 452f4a: jmp 0x452f51 */
L_452f4c:
	m->esp -= 4; M32(m->esp) = 0x452f51u; native_call(m, 0x452fe0u);	/* 452f4c: call 0x452fe0 */
L_452f51:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 452f51: xor ecx, ecx */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452f53: cmp esi, 3 */
	M32((DWORD)(0xa0b418u)) = m->ecx;	/* 452f56: mov dword ptr [0xa0b418], ecx */
	M32((DWORD)(0xa0b418u)) = m->esi;	/* 452f5c: mov dword ptr [0xa0b418], esi */
	M32((DWORD)(0xa0b41cu)) = m->ecx;	/* 452f62: mov dword ptr [0xa0b41c], ecx */
	M32((DWORD)(0xa0b420u)) = m->ecx;	/* 452f68: mov dword ptr [0xa0b420], ecx */
	M32((DWORD)(0xa0b424u)) = m->ecx;	/* 452f6e: mov dword ptr [0xa0b424], ecx */
	M32((DWORD)(0xa0b428u)) = m->ecx;	/* 452f74: mov dword ptr [0xa0b428], ecx */
	if (!m->cf && !m->zf) goto L_452fc8;	/* 452f7a: ja 0x452fc8 */
	switch (m->esi) { case 0: goto L_452f83; case 1: goto L_452f8f; case 2: goto L_452f98; case 3: goto L_452fa1; default: abort(); }	/* 452f7c: jmp dword ptr [esi*4 + 0x452fd0] */
L_452f83:
	m->edx = (DWORD)(m->esp + 0x4u);	/* 452f83: lea edx, [esp + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452f87: push edx */
	m->esp -= 4; M32(m->esp) = 0x452f8du; native_call(m, 0x454940u);	/* 452f88: call 0x454940 */
	goto L_452fa8;	/* 452f8d: jmp 0x452fa8 */
L_452f8f:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452f8f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x452f96u; native_call(m, 0x454a50u);	/* 452f91: call 0x454a50 */
	goto L_452fa8;	/* 452f96: jmp 0x452fa8 */
L_452f98:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452f98: push 0 */
	m->esp -= 4; M32(m->esp) = 0x452f9fu; native_call(m, 0x454b70u);	/* 452f9a: call 0x454b70 */
	goto L_452fa8;	/* 452f9f: jmp 0x452fa8 */
L_452fa1:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 452fa1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x452fa8u; native_call(m, 0x454c80u);	/* 452fa3: call 0x454c80 */
L_452fa8:
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 452fa8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452fab: test eax, eax */
	if (m->zf) goto L_452fc8;	/* 452fad: je 0x452fc8 */
	M32((DWORD)(0xa0b384u)) = 0x1u;	/* 452faf: mov dword ptr [0xa0b384], 1 */
	M32((DWORD)(0xa0b388u)) = 0x1u;	/* 452fb9: mov dword ptr [0xa0b388], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 452fc3: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 452fc4: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 452fc7: ret  */
L_452fc8:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 452fc8: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 452fca: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 452fcb: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 452fce: ret  */
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
