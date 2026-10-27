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

static void lift_450bc0(X86 *m);
static void lift_451270(X86 *m);
static void lift_451350(X86 *m);
static void lift_451090(X86 *m);
static void lift_450c20(X86 *m);
static void lift_450a60(X86 *m);
static void lift_450bb0(X86 *m);
static void lift_450bf0(X86 *m);

/* FUN_00450bf0 (0x450bf0), lifted by tools/lift.py */
static void lift_450bf0(X86 *m)
{
	m->ecx = M32((DWORD)(0xa0b404u));	/* 450bf0: mov ecx, dword ptr [0xa0b404] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 450bf6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450bf8: test ecx, ecx */
	if (m->zf) goto L_450c1b;	/* 450bfa: je 0x450c1b */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450bfc: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 450c00: mov eax, dword ptr [ecx] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450c02: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450c03: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450c07: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450c08: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450c0c: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450c0d: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450c11: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450c12: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450c16: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450c17: push ecx */
	m->esp -= 4; M32(m->esp) = 0x450c1bu; native_call(m, M32((DWORD)(m->eax + 0x68u)));	/* 450c18: call dword ptr [eax + 0x68] */
L_450c1b:
	m->esp += 4 + 0; return;	/* 450c1b: ret  */
}

/* arena_450bc0 (0x450bc0), lifted by tools/lift.py */
static void lift_450bc0(X86 *m)
{
	m->ecx = M32((DWORD)(0xa0b404u));	/* 450bc0: mov ecx, dword ptr [0xa0b404] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 450bc6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450bc8: test ecx, ecx */
	if (m->zf) goto L_450beb;	/* 450bca: je 0x450beb */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450bcc: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 450bd0: mov eax, dword ptr [ecx] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450bd2: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450bd3: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450bd7: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450bd8: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450bdc: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450bdd: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450be1: push edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 450be2: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450be6: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450be7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x450bebu; native_call(m, M32((DWORD)(m->eax + 0x64u)));	/* 450be8: call dword ptr [eax + 0x64] */
L_450beb:
	m->esp += 4 + 0; return;	/* 450beb: ret  */
}

/* FUN_00451270 (0x451270), lifted by tools/lift.py */
static void lift_451270(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451270: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 451271: mov esi, dword ptr [esp + 8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451275: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 451277: xor edx, edx */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 451279: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45127b: sub eax, 2 */
	if (m->zf) goto L_45128e;	/* 45127e: je 0x45128e */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 451280: sub eax, 4 */
	if (m->zf) goto L_45128e;	/* 451283: je 0x45128e */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 451285: dec eax */
	if (!m->zf) goto L_451298;	/* 451286: jne 0x451298 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 451288: mov ecx, dword ptr [esp + 0x10] */
	goto L_451298;	/* 45128c: jmp 0x451298 */
L_45128e:
	m->edx = 0x1u;	/* 45128e: mov edx, 1 */
	m->ecx = 0x8u;	/* 451293: mov ecx, 8 */
L_451298:
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 451298: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45129c: push ecx */
	m->ecx = M32((DWORD)(0xa0b424u));	/* 45129d: mov ecx, dword ptr [0xa0b424] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4512a3: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4512a4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4512a5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4512a6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4512acu; lift_450bf0(m);	/* 4512a7: call 0x450bf0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4512ac: add esp, 0x14 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4512af: pop esi */
	m->esp += 4 + 0; return;	/* 4512b0: ret  */
}

/* net_logMessage (0x451350), lifted by tools/lift.py */
static void lift_451350(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451350: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 451351: mov ecx, dword ptr [esp + 8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 451355: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451356: push esi */
	m->eax = (DWORD)(m->esp + 0x8u);	/* 451357: lea eax, [esp + 8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45135b: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45135c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45135d: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 45135e: mov dword ptr [esp + 0x14], 0 */
	m->esp -= 4; M32(m->esp) = 0x45136bu; native_call(m, 0x454190u);	/* 451366: call 0x454190 */
	m->esi = m->eax;	/* 45136b: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45136d: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 451370: test esi, esi */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 451372: mov dword ptr [esp + 0x14], esi */
	if (m->sf != m->of) goto L_4513e1;	/* 451376: jl 0x4513e1 */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 451378: mov edx, dword ptr [esp + 0xc] */
	m->edi = M32((DWORD)(m->edx + 0x8u));	/* 45137c: mov edi, dword ptr [edx + 8] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45137f: test edi, edi */
	if (!m->zf) goto L_451388;	/* 451381: jne 0x451388 */
	m->edi = 0x4b3e38u;	/* 451383: mov edi, 0x4b3e38 */
L_451388:
	m->esi = M32((DWORD)(0x4a9188u));	/* 451388: mov esi, dword ptr [0x4a9188] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45138e: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45138f: push edi */
	m->esp -= 4; M32(m->esp) = 0x451392u; native_call(m, m->esi);	/* 451390: call esi */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 451392: mov ebx, dword ptr [esp + 0x1c] */
	m->ebp = m->eax;	/* 451396: mov ebp, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 451398: push ebx */
	m->esp -= 4; M32(m->esp) = 0x45139bu; native_call(m, m->esi);	/* 451399: call esi */
	{ DWORD v_ = 0x4b3e30u; m->esp -= 4; M32(m->esp) = v_; }	/* 45139b: push 0x4b3e30 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4513a0: add ebp, eax */
	m->esp -= 4; M32(m->esp) = 0x4513a4u; native_call(m, m->esi);	/* 4513a2: call esi */
	m->eax = (DWORD)(m->eax + m->ebp*1 + 0x1u);	/* 4513a4: lea eax, [eax + ebp + 1] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4513a8: push eax */
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 4513a9: push 0x42 */
	m->esp -= 4; M32(m->esp) = 0x4513b1u; native_call(m, M32(0x4a9070u));	/* 4513ab: call dword ptr [0x4a9070] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4513b1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4513b8u; native_call(m, M32(0x4a9198u));	/* 4513b2: call dword ptr [0x4a9198] */
	m->esi = m->eax;	/* 4513b8: mov esi, eax */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4513ba: pop ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4513bb: test esi, esi */
	if (!m->zf) goto L_4513c6;	/* 4513bd: jne 0x4513c6 */
	m->esi = 0x8007000eu;	/* 4513bf: mov esi, 0x8007000e */
	goto L_4513e1;	/* 4513c4: jmp 0x4513e1 */
L_4513c6:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4513c6: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4513c7: push edi */
	{ DWORD v_ = 0x4b3e30u; m->esp -= 4; M32(m->esp) = v_; }	/* 4513c8: push 0x4b3e30 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4513cd: push esi */
	m->esp -= 4; M32(m->esp) = 0x4513d4u; native_call(m, M32(0x4a92f0u));	/* 4513ce: call dword ptr [0x4a92f0] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 4513d4: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4513d8: add esp, 0x10 */
	M32((DWORD)(m->ecx + 0x0u)) = m->esi;	/* 4513db: mov dword ptr [ecx], esi */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 4513dd: mov esi, dword ptr [esp + 0x14] */
L_4513e1:
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 4513e1: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4513e5: test eax, eax */
	if (m->zf) goto L_451407;	/* 4513e7: je 0x451407 */
	m->edi = M32((DWORD)(0x4a9078u));	/* 4513e9: mov edi, dword ptr [0x4a9078] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4513ef: push eax */
	m->esp -= 4; M32(m->esp) = 0x4513f2u; native_call(m, m->edi);	/* 4513f0: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4513f2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4513f9u; native_call(m, M32(0x4a918cu));	/* 4513f3: call dword ptr [0x4a918c] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 4513f9: mov edx, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4513fd: push edx */
	m->esp -= 4; M32(m->esp) = 0x451400u; native_call(m, m->edi);	/* 4513fe: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451400: push eax */
	m->esp -= 4; M32(m->esp) = 0x451407u; native_call(m, M32(0x4a9190u));	/* 451401: call dword ptr [0x4a9190] */
L_451407:
	m->eax = m->esi;	/* 451407: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 451409: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45140a: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45140b: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 45140c: pop ecx */
	m->esp += 4 + 0; return;	/* 45140d: ret  */
}

/* arena_451090 (0x451090), lifted by tools/lift.py */
static void lift_451090(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 451090: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 451091: push edi */
	m->edi = M32((DWORD)(m->esp + 0xcu));	/* 451092: mov edi, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 451096: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 451098: dec eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451099: cmp eax, 6 */
	if (!m->cf && !m->zf) goto L_45124a;	/* 45109c: ja 0x45124a */
	switch (m->eax) { case 0: goto L_4510a9; case 1: goto L_4510e7; case 2: goto L_45124a; case 3: goto L_45124a; case 4: goto L_45124a; case 5: goto L_4510fd; case 6: goto L_45113c; default: abort(); }	/* 4510a2: jmp dword ptr [eax*4 + 0x451250] */
L_4510a9:
	m->eax = M32((DWORD)(0x9fd948u));	/* 4510a9: mov eax, dword ptr [0x9fd948] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4510ae: test eax, eax */
	if (m->zf) goto L_4510bc;	/* 4510b0: je 0x4510bc */
	M32((DWORD)(0x9fd948u)) = 0x0u;	/* 4510b2: mov dword ptr [0x9fd948], 0 */
L_4510bc:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4510bc: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4510c0: add edi, 0xc */
	{ DWORD v_ = 0x9fd948u; m->esp -= 4; M32(m->esp) = v_; }	/* 4510c3: push 0x9fd948 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4510c8: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4510c9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4510cfu; lift_451350(m);	/* 4510ca: call 0x451350 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4510cf: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4510d2: test eax, eax */
	if (m->sf != m->of) goto L_45124a;	/* 4510d4: jl 0x45124a */
	m->edi = M32(m->esp); m->esp += 4;	/* 4510da: pop edi */
	M32((DWORD)(0x9fd95cu)) = 0x1u;	/* 4510db: mov dword ptr [0x9fd95c], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4510e5: pop esi */
	m->esp += 4 + 0; return;	/* 4510e6: ret  */
L_4510e7:
	m->ecx = M32((DWORD)(m->edi + 0x4u));	/* 4510e7: mov ecx, dword ptr [edi + 4] */
	M32((DWORD)(0x9fd94cu)) = m->ecx;	/* 4510ea: mov dword ptr [0x9fd94c], ecx */
	m->esp -= 4; M32(m->esp) = 0x4510f5u; native_call(m, 0x454130u);	/* 4510f0: call 0x454130 */
	m->esp -= 4; M32(m->esp) = 0x4510fau; native_call(m, 0x4515a0u);	/* 4510f5: call 0x4515a0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4510fa: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4510fb: pop esi */
	m->esp += 4 + 0; return;	/* 4510fc: ret  */
L_4510fd:
	m->edx = M32((DWORD)(0xa0b424u));	/* 4510fd: mov edx, dword ptr [0xa0b424] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 451103: mov al, byte ptr [edi + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451106: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451107: push eax */
	m->esp -= 4; M32(m->esp) = 0x45110du; native_call(m, 0x4514a0u);	/* 451108: call 0x4514a0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45110d: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45110f: add esp, 8 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 451112: mov al, byte ptr [edi + 4] */
	m->esi = 0x1u;	/* 451115: mov esi, 1 */
	m->ecx = m->eax;	/* 45111a: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45111c: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45111f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 451121: shl ecx, 4 */
	M32((DWORD)(m->ecx + 0x9f9840u)) = m->esi;	/* 451124: mov dword ptr [ecx + 0x9f9840], esi */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 45112a: mov dl, byte ptr [edi + 4] */
	M32((DWORD)(0x9f9838u)) = m->esi;	/* 45112d: mov dword ptr [0x9f9838], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 451133: pop edi */
	M8((DWORD)(0x9fd954u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 451134: mov byte ptr [0x9fd954], dl */
	m->esi = M32(m->esp); m->esp += 4;	/* 45113a: pop esi */
	m->esp += 4 + 0; return;	/* 45113b: ret  */
L_45113c:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 45113c: mov dl, byte ptr [edi + 4] */
	m->esi = 0x1u;	/* 45113f: mov esi, 1 */
	m->ecx = m->edx;	/* 451144: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451146: and ecx, 0xff */
	m->eax = m->ecx;	/* 45114c: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45114e: shl eax, 6 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 451151: add eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 451153: shl eax, 4 */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x9f9840u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 451156: cmp dword ptr [eax + 0x9f9840], esi */
	if (!m->zf) goto L_4511b2;	/* 45115c: jne 0x4511b2 */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x5u)), b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45115e: cmp dword ptr [edi + 5], 0x40 */
	if (!m->zf) goto L_45124a;	/* 451162: jne 0x45124a */
	M32((DWORD)(m->eax + 0x9f9848u)) = m->esi;	/* 451168: mov dword ptr [eax + 0x9f9848], esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45116e: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 451170: mov al, byte ptr [edi + 4] */
	m->edx = M32((DWORD)(m->edi + 0x5u));	/* 451173: mov edx, dword ptr [edi + 5] */
	m->ecx = m->eax;	/* 451176: mov ecx, eax */
	m->esi = (DWORD)(m->edi + 0x9u);	/* 451178: lea esi, [edi + 9] */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45117b: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45117e: add ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451180: xor eax, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 451182: shl ecx, 4 */
	M32((DWORD)(m->ecx + 0x9f984cu)) = m->edx;	/* 451185: mov dword ptr [ecx + 0x9f984c], edx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 45118b: mov al, byte ptr [edi + 4] */
	m->ecx = M32((DWORD)(m->edi + 0x5u));	/* 45118e: mov ecx, dword ptr [edi + 5] */
	m->edi = m->eax;	/* 451191: mov edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 451193: shl edi, 6 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 451196: add edi, eax */
	m->eax = m->ecx;	/* 451198: mov eax, ecx */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 45119a: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = 0x9f9850u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 45119d: add edi, 0x9f9850 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4511a3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4511a6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4511a8: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4511aa: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4511ad: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4511af: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4511b0: pop esi */
	m->esp += 4 + 0; return;	/* 4511b1: ret  */
L_4511b2:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4511b2: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x18u));	/* 4511b3: mov ebx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4511b7: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4511b8: push edx */
	m->esp -= 4; M32(m->esp) = 0x4511beu; native_call(m, 0x4514a0u);	/* 4511b9: call 0x4514a0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4511be: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4511c0: add esp, 8 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 4511c3: mov al, byte ptr [edi + 4] */
	m->ecx = m->eax;	/* 4511c6: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4511c8: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4511cb: add ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4511cd: xor eax, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4511cf: shl ecx, 4 */
	M32((DWORD)(m->ecx + 0x9f9840u)) = m->esi;	/* 4511d2: mov dword ptr [ecx + 0x9f9840], esi */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 4511d8: mov al, byte ptr [edi + 4] */
	m->edx = m->eax;	/* 4511db: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4511dd: shl edx, 6 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4511e0: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4511e2: shl edx, 4 */
	M32((DWORD)(m->edx + 0x9f9844u)) = m->ebx;	/* 4511e5: mov dword ptr [edx + 0x9f9844], ebx */
	m->eax = M32((DWORD)(m->edi + 0x5u));	/* 4511eb: mov eax, dword ptr [edi + 5] */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4511ee: cmp eax, 0x40 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4511f1: pop ebx */
	if (!m->zf) goto L_45124a;	/* 4511f2: jne 0x45124a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4511f4: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 4511f6: mov al, byte ptr [edi + 4] */
	m->ecx = m->eax;	/* 4511f9: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4511fb: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4511fe: add ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451200: xor eax, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 451202: shl ecx, 4 */
	M32((DWORD)(m->ecx + 0x9f9848u)) = m->esi;	/* 451205: mov dword ptr [ecx + 0x9f9848], esi */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 45120b: mov al, byte ptr [edi + 4] */
	m->edx = m->eax;	/* 45120e: mov edx, eax */
	m->esi = (DWORD)(m->edi + 0x9u);	/* 451210: lea esi, [edi + 9] */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 451213: shl edx, 6 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 451216: add edx, eax */
	m->eax = M32((DWORD)(m->edi + 0x5u));	/* 451218: mov eax, dword ptr [edi + 5] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45121b: shl edx, 4 */
	M32((DWORD)(m->edx + 0x9f984cu)) = m->eax;	/* 45121e: mov dword ptr [edx + 0x9f984c], eax */
	m->ecx = M32((DWORD)(m->edi + 0x5u));	/* 451224: mov ecx, dword ptr [edi + 5] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 451227: xor eax, eax */
	m->edx = m->ecx;	/* 451229: mov edx, ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4u))) & 0xff) << 0);	/* 45122b: mov al, byte ptr [edi + 4] */
	m->edi = m->eax;	/* 45122e: mov edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 451230: shl edi, 6 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 451233: add edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 451235: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = 0x9f9850u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 451238: add edi, 0x9f9850 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45123e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 451241: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 451243: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 451245: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 451248: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_45124a:
	m->edi = M32(m->esp); m->esp += 4;	/* 45124a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45124b: pop esi */
	m->esp += 4 + 0; return;	/* 45124c: ret  */
}

/* net_sendLocalInfo (0x450c20), lifted by tools/lift.py */
static void lift_450c20(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450c20: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 450c21: mov esi, dword ptr [esp + 8] */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 450c25: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 450c27: sub eax, 3 */
	if (m->zf) goto L_450e04;	/* 450c2a: je 0x450e04 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 450c30: sub eax, 2 */
	if (!m->zf) goto L_45107f;	/* 450c33: jne 0x45107f */
	m->eax = M32((DWORD)(0x9fd94cu));	/* 450c39: mov eax, dword ptr [0x9fd94c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450c3e: test eax, eax */
	if (!m->zf) goto L_450c4e;	/* 450c40: jne 0x450c4e */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 450c42: mov eax, dword ptr [esi + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450c45: push eax */
	m->esp -= 4; M32(m->esp) = 0x450c4bu; native_call(m, 0x451530u);	/* 450c46: call 0x451530 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450c4b: add esp, 4 */
L_450c4e:
	m->eax = M32((DWORD)(0xa0baf8u));	/* 450c4e: mov eax, dword ptr [0xa0baf8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450c53: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450c55: je 0x45107f */
	m->eax = M32((DWORD)(0xa0b418u));	/* 450c5b: mov eax, dword ptr [0xa0b418] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450c60: test eax, eax */
	if (!m->zf) goto L_45107f;	/* 450c62: jne 0x45107f */
	m->eax = M32((DWORD)(0xa0b380u));	/* 450c68: mov eax, dword ptr [0xa0b380] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 450c6d: sub eax, 0xc8 */
	if (m->zf) goto L_450cf8;	/* 450c72: je 0x450cf8 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 450c78: dec eax */
	if (!m->zf) goto L_45107f;	/* 450c79: jne 0x45107f */
	m->eax = M32((DWORD)(0xa0b364u));	/* 450c7f: mov eax, dword ptr [0xa0b364] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450c84: test eax, eax */
	if (!m->zf) goto L_45107f;	/* 450c86: jne 0x45107f */
	m->eax = M32((DWORD)(0xa05630u));	/* 450c8c: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450c91: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450c93: je 0x45107f */
	m->eax = M32((DWORD)(0xa0b32cu));	/* 450c99: mov eax, dword ptr [0xa0b32c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450c9e: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450ca0: je 0x45107f */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 450ca6: mov ecx, dword ptr [0xa0b328] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 450cac: mov dl, byte ptr [ecx] */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 450cae: mov byte ptr [eax], dl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 450cb0: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b32cu));	/* 450cb5: mov edx, dword ptr [0xa0b32c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x67u))) & 0xff) << 0);	/* 450cbb: mov cl, byte ptr [eax + 0x67] */
	M8((DWORD)(m->edx + 0x67u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450cbe: mov byte ptr [edx + 0x67], cl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 450cc1: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b32cu));	/* 450cc6: mov edx, dword ptr [0xa0b32c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x65u))) & 0xff) << 0);	/* 450ccc: mov cl, byte ptr [eax + 0x65] */
	M8((DWORD)(m->edx + 0x65u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450ccf: mov byte ptr [edx + 0x65], cl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 450cd2: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b32cu));	/* 450cd7: mov edx, dword ptr [0xa0b32c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x64u))) & 0xff) << 0);	/* 450cdd: mov cl, byte ptr [eax + 0x64] */
	M8((DWORD)(m->edx + 0x64u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450ce0: mov byte ptr [edx + 0x64], cl */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x9fd950u))) & 0xff) << 0);	/* 450ce3: mov al, byte ptr [0x9fd950] */
	m->ecx = M32((DWORD)(0xa0b32cu));	/* 450ce8: mov ecx, dword ptr [0xa0b32c] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ - 1) & 0xffu; FLAGS(r_, 8); m->of = (a_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 450cee: dec al */
	M8((DWORD)(m->ecx + 0x63u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450cf0: mov byte ptr [ecx + 0x63], al */
	goto L_450ed3;	/* 450cf3: jmp 0x450ed3 */
L_450cf8:
	m->eax = M32((DWORD)(0xa0b360u));	/* 450cf8: mov eax, dword ptr [0xa0b360] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450cfd: test eax, eax */
	if (!m->zf) goto L_45107f;	/* 450cff: jne 0x45107f */
	m->eax = M32((DWORD)(0xa055f8u));	/* 450d05: mov eax, dword ptr [0xa055f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450d0a: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450d0c: je 0x45107f */
	m->eax = M32((DWORD)(0xa0b314u));	/* 450d12: mov eax, dword ptr [0xa0b314] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450d17: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450d19: je 0x45107f */
	m->edx = M32((DWORD)(0xa0b310u));	/* 450d1f: mov edx, dword ptr [0xa0b310] */
	m->esi = M32((DWORD)(0x4a911cu));	/* 450d25: mov esi, dword ptr [0x4a911c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x0u))) & 0xff) << 0);	/* 450d2b: mov cl, byte ptr [edx] */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450d2d: mov byte ptr [eax], cl */
	m->edx = M32((DWORD)(0xa0b310u));	/* 450d2f: mov edx, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 450d35: mov ecx, dword ptr [0xa0b314] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x49u))) & 0xff) << 0);	/* 450d3b: mov al, byte ptr [edx + 0x49] */
	M8((DWORD)(m->ecx + 0x49u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450d3e: mov byte ptr [ecx + 0x49], al */
	m->edx = M32((DWORD)(0xa0b310u));	/* 450d41: mov edx, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 450d47: mov ecx, dword ptr [0xa0b314] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x47u))) & 0xff) << 0);	/* 450d4d: mov al, byte ptr [edx + 0x47] */
	M8((DWORD)(m->ecx + 0x47u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450d50: mov byte ptr [ecx + 0x47], al */
	m->edx = M32((DWORD)(0xa0b310u));	/* 450d53: mov edx, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 450d59: mov ecx, dword ptr [0xa0b314] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x48u))) & 0xff) << 0);	/* 450d5f: mov al, byte ptr [edx + 0x48] */
	M8((DWORD)(m->ecx + 0x48u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450d62: mov byte ptr [ecx + 0x48], al */
	m->edx = M32((DWORD)(0xa0b310u));	/* 450d65: mov edx, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 450d6b: mov ecx, dword ptr [0xa0b314] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x46u))) & 0xff) << 0);	/* 450d71: mov al, byte ptr [edx + 0x46] */
	M8((DWORD)(m->ecx + 0x46u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450d74: mov byte ptr [ecx + 0x46], al */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x9fd950u))) & 0xff) << 0);	/* 450d77: mov dl, byte ptr [0x9fd950] */
	m->eax = M32((DWORD)(0xa0b314u));	/* 450d7d: mov eax, dword ptr [0xa0b314] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), r_ = (a_ - 1) & 0xffu; FLAGS(r_, 8); m->of = (a_ == 0x80u); m->edx = (m->edx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 450d82: dec dl */
	M8((DWORD)(m->eax + 0x45u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 450d84: mov byte ptr [eax + 0x45], dl */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 450d87: mov ecx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b314u));	/* 450d8d: mov eax, dword ptr [0xa0b314] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x43u))) & 0xff) << 0);	/* 450d92: mov dl, byte ptr [ecx + 0x43] */
	M8((DWORD)(m->eax + 0x43u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 450d95: mov byte ptr [eax + 0x43], dl */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 450d98: mov ecx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b314u));	/* 450d9e: mov eax, dword ptr [0xa0b314] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x44u))) & 0xff) << 0);	/* 450da3: mov dl, byte ptr [ecx + 0x44] */
	M8((DWORD)(m->eax + 0x44u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 450da6: mov byte ptr [eax + 0x44], dl */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 450da9: mov ecx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b314u));	/* 450daf: mov eax, dword ptr [0xa0b314] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x52u))) & 0xff) << 0);	/* 450db4: mov dl, byte ptr [ecx + 0x52] */
	M8((DWORD)(m->eax + 0x52u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 450db7: mov byte ptr [eax + 0x52], dl */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 450dba: mov ecx, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b314u));	/* 450dc0: mov edx, dword ptr [0xa0b314] */
	{ DWORD a_ = m->ecx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 450dc6: add ecx, 0x53 */
	{ DWORD a_ = m->edx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 450dc9: add edx, 0x53 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450dcc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450dcd: push edx */
	m->esp -= 4; M32(m->esp) = 0x450dd0u; native_call(m, m->esi);	/* 450dce: call esi */
	m->eax = M32((DWORD)(0xa0b310u));	/* 450dd0: mov eax, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 450dd5: mov ecx, dword ptr [0xa0b314] */
	{ DWORD a_ = m->eax, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 450ddb: add eax, 0x33 */
	{ DWORD a_ = m->ecx, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 450dde: add ecx, 0x33 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450de1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450de2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x450de5u; native_call(m, m->esi);	/* 450de3: call esi */
	m->edx = M32((DWORD)(0xa0b310u));	/* 450de5: mov edx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b314u));	/* 450deb: mov eax, dword ptr [0xa0b314] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 450df0: inc edx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 450df1: inc eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450df2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450df3: push eax */
	m->esp -= 4; M32(m->esp) = 0x450df6u; native_call(m, m->esi);	/* 450df4: call esi */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 450df6: push 0x64 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 450df8: push 0xc */
	m->esp -= 4; M32(m->esp) = 0x450dffu; native_call(m, 0x4521c0u);	/* 450dfa: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450dff: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 450e02: pop esi */
	m->esp += 4 + 0; return;	/* 450e03: ret  */
L_450e04:
	m->eax = M32((DWORD)(0xa0baf8u));	/* 450e04: mov eax, dword ptr [0xa0baf8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450e09: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450e0b: je 0x45107f */
	m->esp -= 4; M32(m->esp) = 0x450e16u; native_call(m, 0x451450u);	/* 450e11: call 0x451450 */
	M8((DWORD)(0x9f9424u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450e16: mov byte ptr [0x9f9424], al */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 450e1b: mov ecx, dword ptr [esi + 8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 450e1e: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450e20: push ecx */
	{ DWORD v_ = 0x9f9420u; m->esp -= 4; M32(m->esp) = v_; }	/* 450e21: push 0x9f9420 */
	m->esp -= 4; M32(m->esp) = 0x450e2bu; lift_451270(m);	/* 450e26: call 0x451270 */
	m->eax = M32((DWORD)(0xa0baf8u));	/* 450e2b: mov eax, dword ptr [0xa0baf8] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450e30: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450e33: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450e35: je 0x45107f */
	m->eax = M32((DWORD)(0xa0b418u));	/* 450e3b: mov eax, dword ptr [0xa0b418] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450e40: test eax, eax */
	if (!m->zf) goto L_45107f;	/* 450e42: jne 0x45107f */
	m->eax = M32((DWORD)(0xa0b380u));	/* 450e48: mov eax, dword ptr [0xa0b380] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 450e4d: sub eax, 0xc8 */
	if (m->zf) goto L_450f6f;	/* 450e52: je 0x450f6f */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 450e58: dec eax */
	if (!m->zf) goto L_45107f;	/* 450e59: jne 0x45107f */
	m->eax = M32((DWORD)(0xa0b364u));	/* 450e5f: mov eax, dword ptr [0xa0b364] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450e64: test eax, eax */
	if (!m->zf) goto L_45107f;	/* 450e66: jne 0x45107f */
	m->eax = M32((DWORD)(0xa05630u));	/* 450e6c: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450e71: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450e73: je 0x45107f */
	m->eax = M32((DWORD)(0xa0b32cu));	/* 450e79: mov eax, dword ptr [0xa0b32c] */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 450e7e: mov edx, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450e81: test eax, eax */
	M32((DWORD)(0x9fd950u)) = m->edx;	/* 450e83: mov dword ptr [0x9fd950], edx */
	if (m->zf) goto L_45107f;	/* 450e89: je 0x45107f */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x1u);	/* 450e8f: mov byte ptr [eax], 1 */
	m->eax = M32((DWORD)(0xa0b328u));	/* 450e92: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b32cu));	/* 450e97: mov edx, dword ptr [0xa0b32c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x67u))) & 0xff) << 0);	/* 450e9d: mov cl, byte ptr [eax + 0x67] */
	M8((DWORD)(m->edx + 0x67u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450ea0: mov byte ptr [edx + 0x67], cl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 450ea3: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b32cu));	/* 450ea8: mov edx, dword ptr [0xa0b32c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x65u))) & 0xff) << 0);	/* 450eae: mov cl, byte ptr [eax + 0x65] */
	M8((DWORD)(m->edx + 0x65u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450eb1: mov byte ptr [edx + 0x65], cl */
	m->eax = M32((DWORD)(0xa0b328u));	/* 450eb4: mov eax, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b32cu));	/* 450eb9: mov edx, dword ptr [0xa0b32c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x64u))) & 0xff) << 0);	/* 450ebf: mov cl, byte ptr [eax + 0x64] */
	M8((DWORD)(m->edx + 0x64u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450ec2: mov byte ptr [edx + 0x64], cl */
	m->eax = M32((DWORD)(0xa0b32cu));	/* 450ec5: mov eax, dword ptr [0xa0b32c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x9fd950u))) & 0xff) << 0);	/* 450eca: mov cl, byte ptr [0x9fd950] */
	M8((DWORD)(m->eax + 0x63u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450ed0: mov byte ptr [eax + 0x63], cl */
L_450ed3:
	m->edx = M32((DWORD)(0xa0b328u));	/* 450ed3: mov edx, dword ptr [0xa0b328] */
	m->ecx = M32((DWORD)(0xa0b32cu));	/* 450ed9: mov ecx, dword ptr [0xa0b32c] */
	m->esi = M32((DWORD)(0x4a911cu));	/* 450edf: mov esi, dword ptr [0x4a911c] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x61u))) & 0xff) << 0);	/* 450ee5: mov al, byte ptr [edx + 0x61] */
	M8((DWORD)(m->ecx + 0x61u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450ee8: mov byte ptr [ecx + 0x61], al */
	m->edx = M32((DWORD)(0xa0b328u));	/* 450eeb: mov edx, dword ptr [0xa0b328] */
	m->ecx = M32((DWORD)(0xa0b32cu));	/* 450ef1: mov ecx, dword ptr [0xa0b32c] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x62u))) & 0xff) << 0);	/* 450ef7: mov al, byte ptr [edx + 0x62] */
	M8((DWORD)(m->ecx + 0x62u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450efa: mov byte ptr [ecx + 0x62], al */
	m->edx = M32((DWORD)(0xa0b328u));	/* 450efd: mov edx, dword ptr [0xa0b328] */
	m->ecx = M32((DWORD)(0xa0b32cu));	/* 450f03: mov ecx, dword ptr [0xa0b32c] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x66u))) & 0xff) << 0);	/* 450f09: mov al, byte ptr [edx + 0x66] */
	M8((DWORD)(m->ecx + 0x66u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450f0c: mov byte ptr [ecx + 0x66], al */
	m->edx = M32((DWORD)(0xa0b328u));	/* 450f0f: mov edx, dword ptr [0xa0b328] */
	m->ecx = M32((DWORD)(0xa0b32cu));	/* 450f15: mov ecx, dword ptr [0xa0b32c] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x70u))) & 0xff) << 0);	/* 450f1b: mov al, byte ptr [edx + 0x70] */
	M8((DWORD)(m->ecx + 0x70u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 450f1e: mov byte ptr [ecx + 0x70], al */
	m->edx = M32((DWORD)(0xa0b328u));	/* 450f21: mov edx, dword ptr [0xa0b328] */
	m->eax = M32((DWORD)(0xa0b32cu));	/* 450f27: mov eax, dword ptr [0xa0b32c] */
	{ DWORD a_ = m->edx, b_ = 0x71u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 450f2c: add edx, 0x71 */
	{ DWORD a_ = m->eax, b_ = 0x71u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 450f2f: add eax, 0x71 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450f32: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450f33: push eax */
	m->esp -= 4; M32(m->esp) = 0x450f36u; native_call(m, m->esi);	/* 450f34: call esi */
	m->ecx = M32((DWORD)(0xa0b328u));	/* 450f36: mov ecx, dword ptr [0xa0b328] */
	m->edx = M32((DWORD)(0xa0b32cu));	/* 450f3c: mov edx, dword ptr [0xa0b32c] */
	{ DWORD a_ = m->ecx, b_ = 0x43u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 450f42: add ecx, 0x43 */
	{ DWORD a_ = m->edx, b_ = 0x43u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 450f45: add edx, 0x43 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450f48: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450f49: push edx */
	m->esp -= 4; M32(m->esp) = 0x450f4cu; native_call(m, m->esi);	/* 450f4a: call esi */
	m->eax = M32((DWORD)(0xa0b328u));	/* 450f4c: mov eax, dword ptr [0xa0b328] */
	m->ecx = M32((DWORD)(0xa0b32cu));	/* 450f51: mov ecx, dword ptr [0xa0b32c] */
	{ DWORD a_ = m->eax, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 450f57: add eax, 0x33 */
	{ DWORD a_ = m->ecx, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 450f5a: add ecx, 0x33 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450f5d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450f5e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x450f61u; native_call(m, m->esi);	/* 450f5f: call esi */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 450f61: push 0x65 */
	{ DWORD v_ = 0x14u; m->esp -= 4; M32(m->esp) = v_; }	/* 450f63: push 0x14 */
	m->esp -= 4; M32(m->esp) = 0x450f6au; native_call(m, 0x4521c0u);	/* 450f65: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450f6a: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 450f6d: pop esi */
	m->esp += 4 + 0; return;	/* 450f6e: ret  */
L_450f6f:
	m->eax = M32((DWORD)(0xa0b360u));	/* 450f6f: mov eax, dword ptr [0xa0b360] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450f74: test eax, eax */
	if (!m->zf) goto L_45107f;	/* 450f76: jne 0x45107f */
	m->eax = M32((DWORD)(0xa055f8u));	/* 450f7c: mov eax, dword ptr [0xa055f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450f81: test eax, eax */
	if (m->zf) goto L_45107f;	/* 450f83: je 0x45107f */
	m->eax = M32((DWORD)(0xa0b314u));	/* 450f89: mov eax, dword ptr [0xa0b314] */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 450f8e: mov edx, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450f91: test eax, eax */
	M32((DWORD)(0x9fd950u)) = m->edx;	/* 450f93: mov dword ptr [0x9fd950], edx */
	if (m->zf) goto L_45107f;	/* 450f99: je 0x45107f */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 450f9f: mov ecx, dword ptr [0xa0b310] */
	m->esi = M32((DWORD)(0x4a911cu));	/* 450fa5: mov esi, dword ptr [0x4a911c] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 450fab: mov dl, byte ptr [ecx] */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 450fad: mov byte ptr [eax], dl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 450faf: mov eax, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b314u));	/* 450fb4: mov edx, dword ptr [0xa0b314] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x49u))) & 0xff) << 0);	/* 450fba: mov cl, byte ptr [eax + 0x49] */
	M8((DWORD)(m->edx + 0x49u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450fbd: mov byte ptr [edx + 0x49], cl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 450fc0: mov eax, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b314u));	/* 450fc5: mov edx, dword ptr [0xa0b314] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x47u))) & 0xff) << 0);	/* 450fcb: mov cl, byte ptr [eax + 0x47] */
	M8((DWORD)(m->edx + 0x47u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450fce: mov byte ptr [edx + 0x47], cl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 450fd1: mov eax, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b314u));	/* 450fd6: mov edx, dword ptr [0xa0b314] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x48u))) & 0xff) << 0);	/* 450fdc: mov cl, byte ptr [eax + 0x48] */
	M8((DWORD)(m->edx + 0x48u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450fdf: mov byte ptr [edx + 0x48], cl */
	m->eax = M32((DWORD)(0xa0b310u));	/* 450fe2: mov eax, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b314u));	/* 450fe7: mov edx, dword ptr [0xa0b314] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x46u))) & 0xff) << 0);	/* 450fed: mov cl, byte ptr [eax + 0x46] */
	M8((DWORD)(m->edx + 0x46u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450ff0: mov byte ptr [edx + 0x46], cl */
	m->eax = M32((DWORD)(0xa0b314u));	/* 450ff3: mov eax, dword ptr [0xa0b314] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x9fd950u))) & 0xff) << 0);	/* 450ff8: mov cl, byte ptr [0x9fd950] */
	M8((DWORD)(m->eax + 0x45u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 450ffe: mov byte ptr [eax + 0x45], cl */
	m->edx = M32((DWORD)(0xa0b310u));	/* 451001: mov edx, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 451007: mov ecx, dword ptr [0xa0b314] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x43u))) & 0xff) << 0);	/* 45100d: mov al, byte ptr [edx + 0x43] */
	M8((DWORD)(m->ecx + 0x43u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 451010: mov byte ptr [ecx + 0x43], al */
	m->edx = M32((DWORD)(0xa0b310u));	/* 451013: mov edx, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 451019: mov ecx, dword ptr [0xa0b314] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x44u))) & 0xff) << 0);	/* 45101f: mov al, byte ptr [edx + 0x44] */
	M8((DWORD)(m->ecx + 0x44u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 451022: mov byte ptr [ecx + 0x44], al */
	m->edx = M32((DWORD)(0xa0b310u));	/* 451025: mov edx, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 45102b: mov ecx, dword ptr [0xa0b314] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x52u))) & 0xff) << 0);	/* 451031: mov al, byte ptr [edx + 0x52] */
	M8((DWORD)(m->ecx + 0x52u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 451034: mov byte ptr [ecx + 0x52], al */
	m->edx = M32((DWORD)(0xa0b310u));	/* 451037: mov edx, dword ptr [0xa0b310] */
	m->eax = M32((DWORD)(0xa0b314u));	/* 45103d: mov eax, dword ptr [0xa0b314] */
	{ DWORD a_ = m->edx, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 451042: add edx, 0x53 */
	{ DWORD a_ = m->eax, b_ = 0x53u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 451045: add eax, 0x53 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 451048: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 451049: push eax */
	m->esp -= 4; M32(m->esp) = 0x45104cu; native_call(m, m->esi);	/* 45104a: call esi */
	m->ecx = M32((DWORD)(0xa0b310u));	/* 45104c: mov ecx, dword ptr [0xa0b310] */
	m->edx = M32((DWORD)(0xa0b314u));	/* 451052: mov edx, dword ptr [0xa0b314] */
	{ DWORD a_ = m->ecx, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 451058: add ecx, 0x33 */
	{ DWORD a_ = m->edx, b_ = 0x33u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45105b: add edx, 0x33 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45105e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45105f: push edx */
	m->esp -= 4; M32(m->esp) = 0x451062u; native_call(m, m->esi);	/* 451060: call esi */
	m->eax = M32((DWORD)(0xa0b310u));	/* 451062: mov eax, dword ptr [0xa0b310] */
	m->ecx = M32((DWORD)(0xa0b314u));	/* 451067: mov ecx, dword ptr [0xa0b314] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45106d: inc eax */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45106e: inc ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45106f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 451070: push ecx */
	m->esp -= 4; M32(m->esp) = 0x451073u; native_call(m, m->esi);	/* 451071: call esi */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 451073: push 0x64 */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 451075: push 0xc */
	m->esp -= 4; M32(m->esp) = 0x45107cu; native_call(m, 0x4521c0u);	/* 451077: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45107c: add esp, 8 */
L_45107f:
	m->esi = M32(m->esp); m->esp += 4;	/* 45107f: pop esi */
	m->esp += 4 + 0; return;	/* 451080: ret  */
}

/* arena_450a60 (0x450a60), lifted by tools/lift.py */
static void lift_450a60(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450a60: sub esp, 0xc */
	m->eax = M32((DWORD)(0x9fd940u));	/* 450a63: mov eax, dword ptr [0x9fd940] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 450a68: push ebx */
	m->ebx = M32((DWORD)(0x4a918cu));	/* 450a69: mov ebx, dword ptr [0x4a918c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 450a6f: push ebp */
	m->ebp = M32((DWORD)(0x4a9190u));	/* 450a70: mov ebp, dword ptr [0x4a9190] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450a76: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 450a77: push edi */
	m->edi = M32((DWORD)(0x4a9078u));	/* 450a78: mov edi, dword ptr [0x4a9078] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 450a7e: xor esi, esi */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 450a80: mov dword ptr [esp + 0x10], eax */
L_450a84:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 450a84: lea ecx, [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 450a88: xor eax, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450a8a: push ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 450a8b: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 450a8f: mov dword ptr [esp + 0x1c], eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450a93: push esi */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 450a94: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 450a98: push 1 */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 450a9a: lea eax, [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450a9e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450a9f: push eax */
	m->esp -= 4; M32(m->esp) = 0x450aa5u; lift_450bc0(m);	/* 450aa0: call 0x450bc0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450aa5: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = 0x887700beu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 450aa8: cmp eax, 0x887700be */
	if (m->zf) goto L_450b7c;	/* 450aad: je 0x450b7c */
	{ DWORD a_ = m->eax, b_ = 0x887703e8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 450ab3: cmp eax, 0x887703e8 */
	if (m->zf) goto L_450b7c;	/* 450ab8: je 0x450b7c */
	{ DWORD a_ = m->eax, b_ = 0x8877001eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 450abe: cmp eax, 0x8877001e */
	if (!m->zf) goto L_450b2a;	/* 450ac3: jne 0x450b2a */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450ac5: test esi, esi */
	if (!m->zf) goto L_450af2;	/* 450ac7: jne 0x450af2 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 450ac9: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450acd: push ecx */
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 450ace: push 0x42 */
	m->esp -= 4; M32(m->esp) = 0x450ad6u; native_call(m, M32(0x4a9070u));	/* 450ad0: call dword ptr [0x4a9070] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450ad6: push eax */
	m->esp -= 4; M32(m->esp) = 0x450addu; native_call(m, M32(0x4a9198u));	/* 450ad7: call dword ptr [0x4a9198] */
	m->esi = m->eax;	/* 450add: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450adf: test esi, esi */
	if (m->zf) goto L_450b9c;	/* 450ae1: je 0x450b9c */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 450ae7: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(0x9fd940u)) = m->eax;	/* 450aeb: mov dword ptr [0x9fd940], eax */
	goto L_450a84;	/* 450af0: jmp 0x450a84 */
L_450af2:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450af2: push esi */
	m->esp -= 4; M32(m->esp) = 0x450af5u; native_call(m, m->edi);	/* 450af3: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450af5: push eax */
	m->esp -= 4; M32(m->esp) = 0x450af8u; native_call(m, m->ebx);	/* 450af6: call ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450af8: push esi */
	m->esp -= 4; M32(m->esp) = 0x450afbu; native_call(m, m->edi);	/* 450af9: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450afb: push eax */
	m->esp -= 4; M32(m->esp) = 0x450afeu; native_call(m, m->ebp);	/* 450afc: call ebp */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 450afe: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 450b02: push edx */
	{ DWORD v_ = 0x42u; m->esp -= 4; M32(m->esp) = v_; }	/* 450b03: push 0x42 */
	m->esp -= 4; M32(m->esp) = 0x450b0bu; native_call(m, M32(0x4a9070u));	/* 450b05: call dword ptr [0x4a9070] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450b0b: push eax */
	m->esp -= 4; M32(m->esp) = 0x450b12u; native_call(m, M32(0x4a9198u));	/* 450b0c: call dword ptr [0x4a9198] */
	m->esi = m->eax;	/* 450b12: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450b14: test esi, esi */
	if (m->zf) goto L_450b9c;	/* 450b16: je 0x450b9c */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 450b1c: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(0x9fd940u)) = m->eax;	/* 450b20: mov dword ptr [0x9fd940], eax */
	goto L_450a84;	/* 450b25: jmp 0x450a84 */
L_450b2a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450b2a: test eax, eax */
	if (!m->zf) goto L_450b82;	/* 450b2c: jne 0x450b82 */
	m->ecx = M32((DWORD)(0x9fd940u));	/* 450b2e: mov ecx, dword ptr [0x9fd940] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 450b34: cmp ecx, 4 */
	if (m->cf) goto L_450b82;	/* 450b37: jb 0x450b82 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 450b39: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450b3d: test eax, eax */
	if (!m->zf) goto L_450b4f;	/* 450b3f: jne 0x450b4f */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450b41: push esi */
	m->esp -= 4; M32(m->esp) = 0x450b47u; lift_450c20(m);	/* 450b42: call 0x450c20 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450b47: add esp, 4 */
	goto L_450a84;	/* 450b4a: jmp 0x450a84 */
L_450b4f:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x0u)), b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 450b4f: cmp dword ptr [esi], 7 */
	if (!m->zf) goto L_450b71;	/* 450b52: jne 0x450b71 */
	{ DWORD a_ = m->ecx, b_ = 0x49u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 450b54: cmp ecx, 0x49 */
	if (m->cf || m->zf) goto L_450b71;	/* 450b57: jbe 0x450b71 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450b59: test esi, esi */
	if (m->zf) goto L_450b9c;	/* 450b5b: je 0x450b9c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450b5d: push esi */
	m->esp -= 4; M32(m->esp) = 0x450b60u; native_call(m, m->edi);	/* 450b5e: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450b60: push eax */
	m->esp -= 4; M32(m->esp) = 0x450b63u; native_call(m, m->ebx);	/* 450b61: call ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450b63: push esi */
	m->esp -= 4; M32(m->esp) = 0x450b66u; native_call(m, m->edi);	/* 450b64: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450b66: push eax */
	m->esp -= 4; M32(m->esp) = 0x450b69u; native_call(m, m->ebp);	/* 450b67: call ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 450b69: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 450b6a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 450b6b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 450b6c: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450b6d: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 450b70: ret  */
L_450b71:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450b71: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 450b72: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450b73: push esi */
	m->esp -= 4; M32(m->esp) = 0x450b79u; lift_451090(m);	/* 450b74: call 0x451090 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450b79: add esp, 0xc */
L_450b7c:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450b7c: test esi, esi */
	if (m->zf) goto L_450b9c;	/* 450b7e: je 0x450b9c */
	goto L_450b86;	/* 450b80: jmp 0x450b86 */
L_450b82:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 450b82: test esi, esi */
	if (m->zf) goto L_450b9c;	/* 450b84: je 0x450b9c */
L_450b86:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450b86: push esi */
	m->esp -= 4; M32(m->esp) = 0x450b89u; native_call(m, m->edi);	/* 450b87: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450b89: push eax */
	m->esp -= 4; M32(m->esp) = 0x450b8cu; native_call(m, m->ebx);	/* 450b8a: call ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 450b8c: push esi */
	m->esp -= 4; M32(m->esp) = 0x450b8fu; native_call(m, m->edi);	/* 450b8d: call edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 450b8f: push eax */
	m->esp -= 4; M32(m->esp) = 0x450b92u; native_call(m, m->ebp);	/* 450b90: call ebp */
	M32((DWORD)(0x9fd940u)) = 0x0u;	/* 450b92: mov dword ptr [0x9fd940], 0 */
L_450b9c:
	m->edi = M32(m->esp); m->esp += 4;	/* 450b9c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 450b9d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 450b9e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 450b9f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 450ba0: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 450ba3: ret  */
}

/* FUN_00450bb0 (0x450bb0), lifted by tools/lift.py */
static void lift_450bb0(X86 *m)
{
	lift_450a60(m); return;	/* 450bb0: jmp 0x450a60 */
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
