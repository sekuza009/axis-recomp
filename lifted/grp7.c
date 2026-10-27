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

static void lift_40ce70(X86 *m);
static void lift_43df00(X86 *m);
static void lift_428890(X86 *m);
static void lift_428c30(X86 *m);
static void lift_468050(X86 *m);
static void lift_467e60(X86 *m);
static void lift_467f20(X86 *m);
static void lift_468450(X86 *m);
static void lift_46cd00(X86 *m);
static void lift_466c00(X86 *m);
static void lift_46afe0(X86 *m);
static void lift_487490(X86 *m);
static void lift_461210(X86 *m);
static void lift_43f300(X86 *m);
static void lift_44ba60(X86 *m);
static void lift_432400(X86 *m);
static void lift_433640(X86 *m);
static void lift_43e610(X86 *m);
static void lift_42f150(X86 *m);
static void lift_456520(X86 *m);
static void lift_473610(X86 *m);
static void lift_41b710(X86 *m);

/* armc_41b710 (0x41b710), lifted by tools/lift.py */
static void lift_41b710(X86 *m)
{
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b710: push 1 */
	m->esp -= 4; M32(m->esp) = 0x41b717u; native_call(m, 0x41ef90u);	/* 41b712: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41b717: add esp, 4 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b71a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b71f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b724: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b729: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41b734u; native_call(m, M32(0x4a9228u));	/* 41b72e: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41b734: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41b73fu; native_call(m, M32(0x4a9224u));	/* 41b739: call dword ptr [0x4a9224] */
	native_call(m, 0x41f050u); return;	/* 41b73f: jmp 0x41f050 */
}

/* menu_drawDimOverlay (0x40ce70), lifted by tools/lift.py */
static void lift_40ce70(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40ce70: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 40ce71: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a943cu));	/* 40ce77: fmul dword ptr [0x4a943c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4deb74u));	/* 40ce7d: fadd dword ptr [0x4deb74] */
	MF((DWORD)(0x4deb74u)) = (float)ST(0);	/* 40ce83: fst dword ptr [0x4deb74] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0);	/* 40ce89: fst dword ptr [esp] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 40ce8d: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 40ce93: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40ce95: test ah, 0x41 */
	if (!m->zf) goto L_40cea2;	/* 40ce98: jne 0x40cea2 */
	M32((DWORD)(m->esp + 0x0u)) = 0x3f800000u;	/* 40ce9a: mov dword ptr [esp], 0x3f800000 */
L_40cea2:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cea2: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40cea9u; native_call(m, 0x41ef90u);	/* 40cea4: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cea9: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40ceb2u; native_call(m, M32(0x4a9218u));	/* 40ceac: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(m->esp + 0x0u));	/* 40ceb2: mov eax, dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40ceb6: push eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ceb7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cebc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cec1: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cec6: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40ced0u; native_call(m, 0x41f0e0u);	/* 40cecb: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ced0: push 1 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ced2: push 0x1e0 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 40ced7: push 0x280 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cedc: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40cede: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40cee5u; native_call(m, 0x427970u);	/* 40cee0: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cee5: add esp, 0x2c */
	m->esp += 4 + 0; return;	/* 40cee8: ret  */
}

/* room_43df00 (0x43df00), lifted by tools/lift.py */
static void lift_43df00(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43df00: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 43df01: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a943cu));	/* 43df07: fmul dword ptr [0x4a943c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4deb74u));	/* 43df0d: fadd dword ptr [0x4deb74] */
	MF((DWORD)(0x4deb74u)) = (float)ST(0);	/* 43df13: fst dword ptr [0x4deb74] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0);	/* 43df19: fst dword ptr [esp] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 43df1d: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43df23: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43df25: test ah, 0x41 */
	if (!m->zf) goto L_43df32;	/* 43df28: jne 0x43df32 */
	M32((DWORD)(m->esp + 0x0u)) = 0x3f800000u;	/* 43df2a: mov dword ptr [esp], 0x3f800000 */
L_43df32:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43df32: push 2 */
	m->esp -= 4; M32(m->esp) = 0x43df39u; native_call(m, 0x41ef90u);	/* 43df34: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43df39: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x43df42u; native_call(m, M32(0x4a9218u));	/* 43df3c: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(m->esp + 0x0u));	/* 43df42: mov eax, dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43df46: push eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43df47: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43df4c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43df51: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43df56: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43df60u; native_call(m, 0x41f0e0u);	/* 43df5b: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4e045cu));	/* 43df60: mov ecx, dword ptr [0x4e045c] */
	m->edx = M32((DWORD)(0x5b1998u));	/* 43df66: mov edx, dword ptr [0x5b1998] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43df6c: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43df6e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43df6f: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43df70: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43df72: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43df79u; native_call(m, 0x427970u);	/* 43df74: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43df79: add esp, 0x2c */
	m->esp += 4 + 0; return;	/* 43df7c: ret  */
}

/* menu_428890 (0x428890), lifted by tools/lift.py */
static void lift_428890(X86 *m)
{
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 428890: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a950cu));	/* 428896: fmul dword ptr [0x4a950c] */
	m->eax = M32((DWORD)(0x9da908u));	/* 42889c: mov eax, dword ptr [0x9da908] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4288a1: inc eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4de1f0u));	/* 4288a2: fadd dword ptr [0x4de1f0] */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4288a8: cmp eax, 0x28 */
	M32((DWORD)(0x9da908u)) = m->eax;	/* 4288ab: mov dword ptr [0x9da908], eax */
	MF((DWORD)(0x4de1f0u)) = (float)ST(0);	/* 4288b0: fst dword ptr [0x4de1f0] */
	if (m->zf || m->sf != m->of) goto L_4288c2;	/* 4288b6: jle 0x4288c2 */
	M32((DWORD)(0x9da908u)) = 0x0u;	/* 4288b8: mov dword ptr [0x9da908], 0 */
L_4288c2:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9508u)); FPOP();	/* 4288c2: fcomp dword ptr [0x4a9508] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4288c8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4288ca: test ah, 0x41 */
	if (!m->zf) goto L_4288d9;	/* 4288cd: jne 0x4288d9 */
	M32((DWORD)(0x4de1f0u)) = 0x0u;	/* 4288cf: mov dword ptr [0x4de1f0], 0 */
L_4288d9:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4288d9: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4288da: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4288db: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4288dc: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4288e3u; native_call(m, 0x41ef90u);	/* 4288de: call 0x41ef90 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4288e3: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4de1f0u));	/* 4288e9: fsub dword ptr [0x4de1f0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4288ef: fstp dword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4288f2: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4288f4: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4288f9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428901u; native_call(m, M32(0x4a9228u));	/* 4288fb: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 428901: push 7 */
	m->esp -= 4; M32(m->esp) = 0x428909u; native_call(m, M32(0x4a921cu));	/* 428903: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 428909: mov esi, dword ptr [esp + 0x14] */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 42890d: mov edi, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428911: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428912: push edi */
	m->esp -= 4; M32(m->esp) = 0x428918u; native_call(m, 0x41ef60u);	/* 428913: call 0x41ef60 */
	m->ebx = (DWORD)(m->edi + 0x7u);	/* 428918: lea ebx, [edi + 7] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42891b: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42891c: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428922u; native_call(m, 0x41ef60u);	/* 42891d: call 0x41ef60 */
	{ DWORD a_ = m->esi, b_ = 0xfu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 428922: add esi, 0xf */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428925: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428926: push ebx */
	m->esp -= 4; M32(m->esp) = 0x42892cu; native_call(m, 0x41ef60u);	/* 428927: call 0x41ef60 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42892c: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42892d: push edi */
	m->esp -= 4; M32(m->esp) = 0x428933u; native_call(m, 0x41ef60u);	/* 42892e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428933: add esp, 0x20 */
	m->esp -= 4; M32(m->esp) = 0x42893cu; native_call(m, M32(0x4a9220u));	/* 428936: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 42893c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42893d: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 42893e: pop ebx */
	m->esp += 4 + 0; return;	/* 42893f: ret  */
}

/* menu_drawFrame (0x428c30), lifted by tools/lift.py */
static void lift_428c30(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428c30: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428c31: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428c32: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428c33: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428c34: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 428c35: push 2 */
	m->esp -= 4; M32(m->esp) = 0x428c3cu; native_call(m, 0x41ef90u);	/* 428c37: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428c3c: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x428c45u; native_call(m, M32(0x4a9218u));	/* 428c3f: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(0x4de740u));	/* 428c45: mov eax, dword ptr [0x4de740] */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 428c4a: mov esi, dword ptr [esp + 0x20] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 428c4e: mov ebx, dword ptr [esp + 0x1c] */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 428c52: mov edi, dword ptr [esp + 0x18] */
	m->ebp = M32((DWORD)(0x4a921cu));	/* 428c56: mov ebp, dword ptr [0x4a921c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 428c5c: cmp eax, 1 */
	if (!m->zf) goto L_428d6c;	/* 428c5f: jne 0x428d6c */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428c65: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428c6a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428c6f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428c74: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428c7cu; native_call(m, M32(0x4a9228u));	/* 428c76: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428c7c: push 1 */
	m->esp -= 4; M32(m->esp) = 0x428c80u; native_call(m, m->ebp);	/* 428c7e: call ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428c80: push ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428c81: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428c88u; native_call(m, 0x41ef60u);	/* 428c83: call 0x41ef60 */
	FPUSH((long double)(int)M32((DWORD)(0x76d428u)));	/* 428c88: fild dword ptr [0x76d428] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428c8e: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428c91: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 428c97: fmul dword ptr [0x4a9518] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 428c9d: fild dword ptr [esp + 0x20] */
	{ long double t = ST(1); FPUSH(t); }	/* 428ca1: fld st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 428ca3: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 428ca5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 428ca7: test ah, 0x41 */
	if (!m->zf) goto L_428cb2;	/* 428caa: jne 0x428cb2 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428cac: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428cad: push esi */
	ST(0) = ST(0); FPOP();	/* 428cae: fstp st(0) */
	goto L_428cb9;	/* 428cb0: jmp 0x428cb9 */
L_428cb2:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428cb2: push ebx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 428cb3: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428cb8: push eax */
L_428cb9:
	m->esp -= 4; M32(m->esp) = 0x428cbeu; native_call(m, 0x41ef60u);	/* 428cb9: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428cbe: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428cc7u; native_call(m, M32(0x4a9220u));	/* 428cc1: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428cc7: push 1 */
	m->esp -= 4; M32(m->esp) = 0x428ccbu; native_call(m, m->ebp);	/* 428cc9: call ebp */
	m->eax = M32((DWORD)(0x4e045cu));	/* 428ccb: mov eax, dword ptr [0x4e045c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428cd0: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428cd1: push edi */
	m->esp -= 4; M32(m->esp) = 0x428cd7u; native_call(m, 0x41ef60u);	/* 428cd2: call 0x41ef60 */
	FPUSH((long double)(int)M32((DWORD)(0x76d428u)));	/* 428cd7: fild dword ptr [0x76d428] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428cdd: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428ce0: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9514u));	/* 428ce6: fmul dword ptr [0x4a9514] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 428cec: fild dword ptr [esp + 0x24] */
	{ long double t = ST(1); FPUSH(t); }	/* 428cf0: fld st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 428cf2: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 428cf4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 428cf6: test ah, 0x41 */
	if (!m->zf) goto L_428d0c;	/* 428cf9: jne 0x428d0c */
	m->ecx = M32((DWORD)(0x4e045cu));	/* 428cfb: mov ecx, dword ptr [0x4e045c] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 428d01: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 428d05: sub ecx, eax */
	ST(0) = ST(0); FPOP();	/* 428d07: fstp st(0) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428d09: push ecx */
	goto L_428d1a;	/* 428d0a: jmp 0x428d1a */
L_428d0c:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 428d0c: call 0x49ec14 */
	m->edx = M32((DWORD)(0x4e045cu));	/* 428d11: mov edx, dword ptr [0x4e045c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 428d17: sub edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428d19: push edx */
L_428d1a:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428d1a: push edi */
	m->esp -= 4; M32(m->esp) = 0x428d20u; native_call(m, 0x41ef60u);	/* 428d1b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428d20: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428d29u; native_call(m, M32(0x4a9220u));	/* 428d23: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(0x76d428u));	/* 428d29: mov eax, dword ptr [0x76d428] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 428d2e: inc eax */
	M32((DWORD)(0x76d428u)) = m->eax;	/* 428d2f: mov dword ptr [0x76d428], eax */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 428d34: shl eax, 6 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 428d37: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 428d3b: fild dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428d3f: fmul dword ptr [0x4b071c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9510u)); FPOP();	/* 428d45: fcomp dword ptr [0x4a9510] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 428d4b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 428d4d: test ah, 0x41 */
	if (!m->zf) goto L_428d6c;	/* 428d50: jne 0x428d6c */
	m->edi = M32(m->esp); m->esp += 4;	/* 428d52: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 428d53: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 428d54: pop ebp */
	M32((DWORD)(0x4de740u)) = 0x2u;	/* 428d55: mov dword ptr [0x4de740], 2 */
	M32((DWORD)(0x76d428u)) = 0x0u;	/* 428d5f: mov dword ptr [0x76d428], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 428d69: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 428d6a: pop ecx */
	m->esp += 4 + 0; return;	/* 428d6b: ret  */
L_428d6c:
	{ DWORD a_ = M32((DWORD)(0x4de740u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 428d6c: cmp dword ptr [0x4de740], 2 */
	if (!m->zf) goto L_428f14;	/* 428d73: jne 0x428f14 */
	FPUSH((long double)(int)M32((DWORD)(0x76d428u)));	/* 428d79: fild dword ptr [0x76d428] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428d7f: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 428d85: fmul dword ptr [0x4a93ec] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 428d8b: fcom dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 428d91: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 428d93: test ah, 0x41 */
	if (!m->zf) goto L_428d9e;	/* 428d96: jne 0x428d9e */
	ST(0) = ST(0); FPOP();	/* 428d98: fstp st(0) */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428d9a: push 0 */
	goto L_428dac;	/* 428d9c: jmp 0x428dac */
L_428d9e:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 428d9e: fld dword ptr [0x4a9424] */
	ST(0) = ST(0) - ST(1);	/* 428da4: fsub st(1) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428da6: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 428da7: fstp dword ptr [esp] */
	ST(0) = ST(0); FPOP();	/* 428daa: fstp st(0) */
L_428dac:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428dac: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428db1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428db6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428dbeu; native_call(m, M32(0x4a9228u));	/* 428db8: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428dbe: push 1 */
	m->esp -= 4; M32(m->esp) = 0x428dc2u; native_call(m, m->ebp);	/* 428dc0: call ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428dc2: push ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428dc3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428dcau; native_call(m, 0x41ef60u);	/* 428dc5: call 0x41ef60 */
	m->eax = M32((DWORD)(0x5b1998u));	/* 428dca: mov eax, dword ptr [0x5b1998] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428dcf: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428dd0: push eax */
	m->esp -= 4; M32(m->esp) = 0x428dd6u; native_call(m, 0x41ef60u);	/* 428dd1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428dd6: add esp, 0x10 */
	m->esp -= 4; M32(m->esp) = 0x428ddfu; native_call(m, M32(0x4a9220u));	/* 428dd9: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428ddf: push 1 */
	m->esp -= 4; M32(m->esp) = 0x428de3u; native_call(m, m->ebp);	/* 428de1: call ebp */
	m->ecx = M32((DWORD)(0x4e045cu));	/* 428de3: mov ecx, dword ptr [0x4e045c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428de9: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428dea: push edi */
	m->esp -= 4; M32(m->esp) = 0x428df0u; native_call(m, 0x41ef60u);	/* 428deb: call 0x41ef60 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428df0: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428df2: push edi */
	m->esp -= 4; M32(m->esp) = 0x428df8u; native_call(m, 0x41ef60u);	/* 428df3: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428df8: add esp, 0x10 */
	m->esp -= 4; M32(m->esp) = 0x428e01u; native_call(m, M32(0x4a9220u));	/* 428dfb: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428e01: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428e06: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428e0b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428e10: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428e18u; native_call(m, M32(0x4a9228u));	/* 428e12: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428e18: push 1 */
	m->esp -= 4; M32(m->esp) = 0x428e1cu; native_call(m, m->ebp);	/* 428e1a: call ebp */
	FPUSH((long double)(int)M32((DWORD)(0x76d428u)));	/* 428e1c: fild dword ptr [0x76d428] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428e22: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 428e28: fmul dword ptr [0x4a9518] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 428e2e: fild dword ptr [esp + 0x20] */
	{ long double t = ST(1); FPUSH(t); }	/* 428e32: fld st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 428e34: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 428e36: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 428e38: test ah, 0x41 */
	if (!m->zf) goto L_428e4e;	/* 428e3b: jne 0x428e4e */
	m->eax = M32((DWORD)(0x5b1998u));	/* 428e3d: mov eax, dword ptr [0x5b1998] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 428e42: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 428e46: sub eax, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428e48: push edx */
	ST(0) = ST(0); FPOP();	/* 428e49: fstp st(0) */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428e4b: push eax */
	goto L_428e61;	/* 428e4c: jmp 0x428e61 */
L_428e4e:
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 428e4e: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428e52: push ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 428e53: call 0x49ec14 */
	m->edx = M32((DWORD)(0x5b1998u));	/* 428e58: mov edx, dword ptr [0x5b1998] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 428e5e: sub edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428e60: push edx */
L_428e61:
	m->esp -= 4; M32(m->esp) = 0x428e66u; native_call(m, 0x41ef60u);	/* 428e61: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 428e66: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(0x5b1998u));	/* 428e6a: mov ecx, dword ptr [0x5b1998] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428e70: add esp, 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428e73: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428e74: push ecx */
	m->esp -= 4; M32(m->esp) = 0x428e7au; native_call(m, 0x41ef60u);	/* 428e75: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428e7a: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428e83u; native_call(m, M32(0x4a9220u));	/* 428e7d: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428e83: push 1 */
	m->esp -= 4; M32(m->esp) = 0x428e87u; native_call(m, m->ebp);	/* 428e85: call ebp */
	FPUSH((long double)(int)M32((DWORD)(0x76d428u)));	/* 428e87: fild dword ptr [0x76d428] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428e8d: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9514u));	/* 428e93: fmul dword ptr [0x4a9514] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 428e99: fild dword ptr [esp + 0x24] */
	{ long double t = ST(1); FPUSH(t); }	/* 428e9d: fld st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 428e9f: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 428ea1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 428ea3: test ah, 0x41 */
	if (!m->zf) goto L_428eb1;	/* 428ea6: jne 0x428eb1 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 428ea8: mov edx, dword ptr [esp + 0x24] */
	ST(0) = ST(0); FPOP();	/* 428eac: fstp st(0) */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428eae: push edx */
	goto L_428eb7;	/* 428eaf: jmp 0x428eb7 */
L_428eb1:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 428eb1: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428eb6: push eax */
L_428eb7:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428eb7: push esi */
	m->esp -= 4; M32(m->esp) = 0x428ebdu; native_call(m, 0x41ef60u);	/* 428eb8: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428ebd: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428ec0: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428ec2: push esi */
	m->esp -= 4; M32(m->esp) = 0x428ec8u; native_call(m, 0x41ef60u);	/* 428ec3: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428ec8: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428ed1u; native_call(m, M32(0x4a9220u));	/* 428ecb: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(0x76d428u));	/* 428ed1: mov eax, dword ptr [0x76d428] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 428ed6: inc eax */
	M32((DWORD)(0x76d428u)) = m->eax;	/* 428ed7: mov dword ptr [0x76d428], eax */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 428edc: shl eax, 6 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 428edf: mov dword ptr [esp + 0x10], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 428ee3: fild dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428ee7: fmul dword ptr [0x4b071c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9510u)); FPOP();	/* 428eed: fcomp dword ptr [0x4a9510] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 428ef3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 428ef5: test ah, 0x41 */
	if (!m->zf) goto L_428f14;	/* 428ef8: jne 0x428f14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 428efa: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 428efb: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 428efc: pop ebp */
	M32((DWORD)(0x4de740u)) = 0x3u;	/* 428efd: mov dword ptr [0x4de740], 3 */
	M32((DWORD)(0x76d428u)) = 0x0u;	/* 428f07: mov dword ptr [0x76d428], 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 428f11: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 428f12: pop ecx */
	m->esp += 4 + 0; return;	/* 428f13: ret  */
L_428f14:
	{ DWORD a_ = M32((DWORD)(0x4de740u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 428f14: cmp dword ptr [0x4de740], 3 */
	if (!m->zf) goto L_4290bc;	/* 428f1b: jne 0x4290bc */
	FPUSH((long double)(int)M32((DWORD)(0x76d428u)));	/* 428f21: fild dword ptr [0x76d428] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428f27: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 428f2d: fmul dword ptr [0x4a93ec] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 428f33: fcom dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 428f39: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 428f3b: test ah, 0x41 */
	if (!m->zf) goto L_428f46;	/* 428f3e: jne 0x428f46 */
	ST(0) = ST(0); FPOP();	/* 428f40: fstp st(0) */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428f42: push 0 */
	goto L_428f54;	/* 428f44: jmp 0x428f54 */
L_428f46:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 428f46: fld dword ptr [0x4a9424] */
	ST(0) = ST(0) - ST(1);	/* 428f4c: fsub st(1) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428f4e: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 428f4f: fstp dword ptr [esp] */
	ST(0) = ST(0); FPOP();	/* 428f52: fstp st(0) */
L_428f54:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428f54: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428f56: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428f5b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428f63u; native_call(m, M32(0x4a9228u));	/* 428f5d: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428f63: push 1 */
	m->esp -= 4; M32(m->esp) = 0x428f67u; native_call(m, m->ebp);	/* 428f65: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 428f67: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428f6b: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428f6c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428f73u; native_call(m, 0x41ef60u);	/* 428f6e: call 0x41ef60 */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 428f73: mov ecx, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(0x5b1998u));	/* 428f77: mov edx, dword ptr [0x5b1998] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428f7d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 428f7e: push edx */
	m->esp -= 4; M32(m->esp) = 0x428f84u; native_call(m, 0x41ef60u);	/* 428f7f: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428f84: add esp, 0x10 */
	m->esp -= 4; M32(m->esp) = 0x428f8du; native_call(m, M32(0x4a9220u));	/* 428f87: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428f8d: push 1 */
	m->esp -= 4; M32(m->esp) = 0x428f91u; native_call(m, m->ebp);	/* 428f8f: call ebp */
	m->eax = M32((DWORD)(0x4e045cu));	/* 428f91: mov eax, dword ptr [0x4e045c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 428f96: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428f97: push esi */
	m->esp -= 4; M32(m->esp) = 0x428f9du; native_call(m, 0x41ef60u);	/* 428f98: call 0x41ef60 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428f9d: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428f9f: push esi */
	m->esp -= 4; M32(m->esp) = 0x428fa5u; native_call(m, 0x41ef60u);	/* 428fa0: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428fa5: add esp, 0x10 */
	m->esp -= 4; M32(m->esp) = 0x428faeu; native_call(m, M32(0x4a9220u));	/* 428fa8: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 428fae: push 0x3e99999a */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428fb3: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428fb8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428fba: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 428fbc: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x428fc6u; native_call(m, 0x41f0e0u);	/* 428fc1: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 428fc6: mov ecx, dword ptr [esp + 0x38] */
	m->eax = 0x66666667u;	/* 428fca: mov eax, 0x66666667 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 428fcf: sub ecx, ebx */
	m->ebp = M32((DWORD)(0x76d428u));	/* 428fd1: mov ebp, dword ptr [0x76d428] */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 428fd7: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 428fd9: sar edx, 2 */
	m->ecx = m->edx;	/* 428fdc: mov ecx, edx */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428fde: add esp, 0x14 */
	{ DWORD a_ = m->ecx, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 428fe1: shr ecx, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 428fe4: add edx, ecx */
	{ long long p_ = (long long)(int)m->edx * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 428fe6: imul edx, ebp */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 428fe9: mov dword ptr [esp + 0x10], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 428fed: fild dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 428ff1: fmul dword ptr [0x4b071c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 428ff7: fild dword ptr [esp + 0x1c] */
	ST(0) = ST(0) + ST(1);	/* 428ffb: fadd st(1) */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 428ffd: fild dword ptr [esp + 0x24] */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 429001: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 429003: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 429005: test ah, 1 */
	if (m->zf) goto L_429035;	/* 429008: je 0x429035 */
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42900a: sub esi, edi */
	m->eax = 0x66666667u;	/* 42900c: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->esi; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 429011: imul esi */
	ST(0) = ST(0); FPOP();	/* 429013: fstp st(0) */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 429015: sar edx, 2 */
	m->eax = m->edx;	/* 429018: mov eax, edx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 42901a: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42901e: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 429021: add edx, eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 429023: push 1 */
	m->esi = m->edx;	/* 429025: mov esi, edx */
	{ long long p_ = (long long)(int)m->edx * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 429027: imul edx, ebp */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 42902a: mov dword ptr [esp + 0x28], edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42902e: push ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 42902f: fild dword ptr [esp + 0x2c] */
	goto L_429061;	/* 429033: jmp 0x429061 */
L_429035:
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 429035: sub esi, edi */
	m->eax = 0x66666667u;	/* 429037: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->esi; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 42903c: imul esi */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 42903e: sar edx, 2 */
	m->eax = m->edx;	/* 429041: mov eax, edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 429043: push 1 */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429045: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 429048: add edx, eax */
	m->esi = m->edx;	/* 42904a: mov esi, edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 42904c: call 0x49ec14 */
	m->ecx = m->esi;	/* 429051: mov ecx, esi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429053: add eax, ebx */
	{ long long p_ = (long long)(int)m->ecx * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 429055: imul ecx, ebp */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 429058: mov dword ptr [esp + 0x28], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42905c: push eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 42905d: fild dword ptr [esp + 0x2c] */
L_429061:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 429061: fmul dword ptr [0x4b071c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 429067: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42906c: add eax, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42906e: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42906f: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 429070: push edi */
	m->esp -= 4; M32(m->esp) = 0x429076u; native_call(m, 0x427970u);	/* 429071: call 0x427970 */
	m->eax = M32((DWORD)(0x76d428u));	/* 429076: mov eax, dword ptr [0x76d428] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42907b: add esp, 0x14 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 42907e: inc eax */
	{ long long p_ = (long long)(int)m->esi * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 42907f: imul esi, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->esi;	/* 429082: mov dword ptr [esp + 0x24], esi */
	M32((DWORD)(0x76d428u)) = m->eax;	/* 429086: mov dword ptr [0x76d428], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 42908b: fild dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 42908f: fmul dword ptr [0x4b071c] */
	ST(0) = ST(0) + (long double)(int)M32((DWORD)(m->esp + 0x18u));	/* 429095: fiadd dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 429099: fild dword ptr [esp + 0x20] */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 42909d: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42909f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4290a1: test ah, 0x41 */
	if (m->zf) goto L_4290bc;	/* 4290a4: je 0x4290bc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4290a6: xor eax, eax */
	M32((DWORD)(0x4de740u)) = 0x1u;	/* 4290a8: mov dword ptr [0x4de740], 1 */
	M32((DWORD)(0x76d428u)) = m->eax;	/* 4290b2: mov dword ptr [0x76d428], eax */
	M32((DWORD)(0x90d1c4u)) = m->eax;	/* 4290b7: mov dword ptr [0x90d1c4], eax */
L_4290bc:
	m->edi = M32(m->esp); m->esp += 4;	/* 4290bc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4290bd: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4290be: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4290bf: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4290c0: pop ecx */
	m->esp += 4 + 0; return;	/* 4290c1: ret  */
}

/* glWindow_restoreDisplayMode (0x468050), lifted by tools/lift.py */
static void lift_468050(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e940u));	/* 468050: mov eax, dword ptr [0xa0e940] */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468055: sub esp, 0x94 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46805b: cmp eax, 1 */
	if (!m->zf) goto L_4680a2;	/* 46805e: jne 0x4680a2 */
	m->eax = M32((DWORD)(0xa0e92cu));	/* 468060: mov eax, dword ptr [0xa0e92c] */
	m->ecx = M32((DWORD)(0xa0e814u));	/* 468065: mov ecx, dword ptr [0xa0e814] */
	m->edx = M32((DWORD)(0xa0e91cu));	/* 46806b: mov edx, dword ptr [0xa0e91c] */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 468071: mov dword ptr [esp + 0x6c], eax */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 468075: lea eax, [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468079: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46807b: push eax */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 46807c: mov dword ptr [esp + 0x78], ecx */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 468080: mov dword ptr [esp + 0x70], edx */
	M16((DWORD)(m->esp + 0x2cu)) = (WORD)(0x94u);	/* 468084: mov word ptr [esp + 0x2c], 0x94 */
	M32((DWORD)(m->esp + 0x30u)) = 0x1c0000u;	/* 46808b: mov dword ptr [esp + 0x30], 0x1c0000 */
	m->esp -= 4; M32(m->esp) = 0x468099u; native_call(m, M32(0x4a9314u));	/* 468093: call dword ptr [0x4a9314] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468099: test eax, eax */
	if (!m->zf) goto L_4680ae;	/* 46809b: jne 0x4680ae */
	M32((DWORD)(0xa0e940u)) = m->eax;	/* 46809d: mov dword ptr [0xa0e940], eax */
L_4680a2:
	m->eax = 0x1u;	/* 4680a2: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4680a7: add esp, 0x94 */
	m->esp += 4 + 0; return;	/* 4680ad: ret  */
L_4680ae:
	{ DWORD v_ = 0x4c4ed4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4680ae: push 0x4c4ed4 */
	m->esp -= 4; M32(m->esp) = 0x4680b8u; native_call(m, 0x46c840u);	/* 4680b3: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4680b8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4680bb: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4680bd: add esp, 0x94 */
	m->esp += 4 + 0; return;	/* 4680c3: ret  */
}

/* glWindow_setupPixelFormat (0x467e60), lifted by tools/lift.py */
static void lift_467e60(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467e60: sub esp, 0x28 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0xa0e818u))) & 0xff) << 0);	/* 467e63: mov al, byte ptr [0xa0e818] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0xa0e924u))) & 0xff) << 0);	/* 467e68: mov cl, byte ptr [0xa0e924] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 467e6e: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467e6f: push esi */
	m->esi = M32((DWORD)(m->esp + 0x34u));	/* 467e70: mov esi, dword ptr [esp + 0x34] */
	m->edx = (DWORD)(m->esp + 0x8u);	/* 467e74: lea edx, [esp + 8] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 467e78: xor ebx, ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467e7a: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467e7b: push esi */
	M16((DWORD)(m->esp + 0x10u)) = (WORD)(0x28u);	/* 467e7c: mov word ptr [esp + 0x10], 0x28 */
	M16((DWORD)(m->esp + 0x12u)) = (WORD)(0x1u);	/* 467e83: mov word ptr [esp + 0x12], 1 */
	M32((DWORD)(m->esp + 0x14u)) = 0x21u;	/* 467e8a: mov dword ptr [esp + 0x14], 0x21 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebx;	/* 467e92: mov dword ptr [esp + 0x2c], ebx */
	M8((DWORD)(m->esp + 0x18u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 467e96: mov byte ptr [esp + 0x18], bl */
	M8((DWORD)(m->esp + 0x19u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 467e9a: mov byte ptr [esp + 0x19], al */
	M8((DWORD)(m->esp + 0x27u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 467e9e: mov byte ptr [esp + 0x27], cl */
	M8((DWORD)(m->esp + 0x22u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 467ea2: mov byte ptr [esp + 0x22], bl */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 467ea6: mov byte ptr [esp + 0x28], bl */
	m->esp -= 4; M32(m->esp) = 0x467eb0u; native_call(m, M32(0x4a902cu));	/* 467eaa: call dword ptr [0x4a902c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467eb0: cmp eax, ebx */
	if (!m->zf) goto L_467ec9;	/* 467eb2: jne 0x467ec9 */
	{ DWORD v_ = 0x4c4e5cu; m->esp -= 4; M32(m->esp) = v_; }	/* 467eb4: push 0x4c4e5c */
	m->esp -= 4; M32(m->esp) = 0x467ebeu; native_call(m, 0x46c840u);	/* 467eb9: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467ebe: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467ec1: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 467ec3: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467ec4: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467ec5: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 467ec8: ret  */
L_467ec9:
	{ DWORD a_ = M8((DWORD)(m->esp + 0xcu)), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 467ec9: test byte ptr [esp + 0xc], 0x80 */
	if (m->zf) goto L_467ee5;	/* 467ece: je 0x467ee5 */
	{ DWORD v_ = 0x4c4e30u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ed0: push 0x4c4e30 */
	m->esp -= 4; M32(m->esp) = 0x467edau; native_call(m, 0x46c840u);	/* 467ed5: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467eda: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467edd: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 467edf: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467ee0: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467ee1: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 467ee4: ret  */
L_467ee5:
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 467ee5: lea ecx, [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 467ee9: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467eea: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467eeb: push esi */
	m->esp -= 4; M32(m->esp) = 0x467ef2u; native_call(m, M32(0x4a9030u));	/* 467eec: call dword ptr [0x4a9030] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467ef2: test eax, eax */
	if (!m->zf) goto L_467f0b;	/* 467ef4: jne 0x467f0b */
	{ DWORD v_ = 0x4c4df8u; m->esp -= 4; M32(m->esp) = v_; }	/* 467ef6: push 0x4c4df8 */
	m->esp -= 4; M32(m->esp) = 0x467f00u; native_call(m, 0x46c840u);	/* 467efb: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467f00: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 467f03: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 467f05: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467f06: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467f07: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 467f0a: ret  */
L_467f0b:
	m->esi = M32(m->esp); m->esp += 4;	/* 467f0b: pop esi */
	m->eax = 0x1u;	/* 467f0c: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467f11: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467f12: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 467f15: ret  */
}

/* glWindow_setDisplayModeBy (0x467f20), lifted by tools/lift.py */
static void lift_467f20(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e938u));	/* 467f20: mov eax, dword ptr [0xa0e938] */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467f25: sub esp, 0x94 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467f2b: test eax, eax */
	if (!m->zf) goto L_467f41;	/* 467f2d: jne 0x467f41 */
	m->esp -= 4; M32(m->esp) = 0x467f35u; native_call(m, M32(0x4a9320u));	/* 467f2f: call dword ptr [0x4a9320] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467f35: push eax */
	m->esp -= 4; M32(m->esp) = 0x467f3cu; native_call(m, M32(0x4a9318u));	/* 467f36: call dword ptr [0x4a9318] */
	M32((DWORD)(0xa0e938u)) = m->eax;	/* 467f3c: mov dword ptr [0xa0e938], eax */
L_467f41:
	m->ecx = M32((DWORD)(0xa0e940u));	/* 467f41: mov ecx, dword ptr [0xa0e940] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 467f47: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 467f48: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 467f49: push esi */
	m->esi = M32((DWORD)(0x4a9034u));	/* 467f4a: mov esi, dword ptr [0x4a9034] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 467f50: push edi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467f51: test ecx, ecx */
	if (!m->zf) goto L_467f83;	/* 467f53: jne 0x467f83 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 467f55: push 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467f57: push eax */
	m->esp -= 4; M32(m->esp) = 0x467f5au; native_call(m, m->esi);	/* 467f58: call esi */
	M32((DWORD)(0xa0e92cu)) = m->eax;	/* 467f5a: mov dword ptr [0xa0e92c], eax */
	m->eax = M32((DWORD)(0xa0e938u));	/* 467f5f: mov eax, dword ptr [0xa0e938] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 467f64: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467f66: push eax */
	m->esp -= 4; M32(m->esp) = 0x467f69u; native_call(m, m->esi);	/* 467f67: call esi */
	m->ecx = M32((DWORD)(0xa0e938u));	/* 467f69: mov ecx, dword ptr [0xa0e938] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 467f6f: push 0xc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 467f71: push ecx */
	M32((DWORD)(0xa0e814u)) = m->eax;	/* 467f72: mov dword ptr [0xa0e814], eax */
	m->esp -= 4; M32(m->esp) = 0x467f79u; native_call(m, m->esi);	/* 467f77: call esi */
	M32((DWORD)(0xa0e91cu)) = m->eax;	/* 467f79: mov dword ptr [0xa0e91c], eax */
	m->eax = M32((DWORD)(0xa0e938u));	/* 467f7e: mov eax, dword ptr [0xa0e938] */
L_467f83:
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 467f83: push 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467f85: push eax */
	m->esp -= 4; M32(m->esp) = 0x467f88u; native_call(m, m->esi);	/* 467f86: call esi */
	m->ebx = M32((DWORD)(m->esp + 0xa8u));	/* 467f88: mov ebx, dword ptr [esp + 0xa8] */
	m->edi = M32((DWORD)(m->esp + 0xb0u));	/* 467f8f: mov edi, dword ptr [esp + 0xb0] */
	m->ebp = M32((DWORD)(m->esp + 0xacu));	/* 467f96: mov ebp, dword ptr [esp + 0xac] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467f9d: cmp eax, ebx */
	if (!m->zf) goto L_467fd2;	/* 467f9f: jne 0x467fd2 */
	m->edx = M32((DWORD)(0xa0e938u));	/* 467fa1: mov edx, dword ptr [0xa0e938] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 467fa7: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 467fa9: push edx */
	m->esp -= 4; M32(m->esp) = 0x467facu; native_call(m, m->esi);	/* 467faa: call esi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467fac: cmp eax, ebp */
	if (!m->zf) goto L_467fd2;	/* 467fae: jne 0x467fd2 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467fb0: test edi, edi */
	if (m->zf) goto L_467fc2;	/* 467fb2: je 0x467fc2 */
	m->eax = M32((DWORD)(0xa0e938u));	/* 467fb4: mov eax, dword ptr [0xa0e938] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 467fb9: push 0xc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467fbb: push eax */
	m->esp -= 4; M32(m->esp) = 0x467fbeu; native_call(m, m->esi);	/* 467fbc: call esi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 467fbe: cmp eax, edi */
	if (!m->zf) goto L_467fd2;	/* 467fc0: jne 0x467fd2 */
L_467fc2:
	m->edi = M32(m->esp); m->esp += 4;	/* 467fc2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 467fc3: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 467fc4: pop ebp */
	m->eax = 0x1u;	/* 467fc5: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 467fca: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 467fcb: add esp, 0x94 */
	m->esp += 4 + 0; return;	/* 467fd1: ret  */
L_467fd2:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467fd2: test edi, edi */
	M32((DWORD)(m->esp + 0x7cu)) = m->ebx;	/* 467fd4: mov dword ptr [esp + 0x7c], ebx */
	M32((DWORD)(m->esp + 0x80u)) = m->ebp;	/* 467fd8: mov dword ptr [esp + 0x80], ebp */
	if (!m->zf) goto L_467ff2;	/* 467fdf: jne 0x467ff2 */
	M16((DWORD)(m->esp + 0x34u)) = (WORD)(0x94u);	/* 467fe1: mov word ptr [esp + 0x34], 0x94 */
	M32((DWORD)(m->esp + 0x38u)) = 0x180000u;	/* 467fe8: mov dword ptr [esp + 0x38], 0x180000 */
	goto L_468005;	/* 467ff0: jmp 0x468005 */
L_467ff2:
	M32((DWORD)(m->esp + 0x78u)) = m->edi;	/* 467ff2: mov dword ptr [esp + 0x78], edi */
	M16((DWORD)(m->esp + 0x34u)) = (WORD)(0x94u);	/* 467ff6: mov word ptr [esp + 0x34], 0x94 */
	M32((DWORD)(m->esp + 0x38u)) = 0x1c0000u;	/* 467ffd: mov dword ptr [esp + 0x38], 0x1c0000 */
L_468005:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 468005: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468009: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46800b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x468012u; native_call(m, M32(0x4a9314u));	/* 46800c: call dword ptr [0x4a9314] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468012: test eax, eax */
	if (!m->zf) goto L_46802b;	/* 468014: jne 0x46802b */
	m->edi = M32(m->esp); m->esp += 4;	/* 468016: pop edi */
	m->eax = 0x1u;	/* 468017: mov eax, 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 46801c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46801d: pop ebp */
	M32((DWORD)(0xa0e940u)) = m->eax;	/* 46801e: mov dword ptr [0xa0e940], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 468023: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468024: add esp, 0x94 */
	m->esp += 4 + 0; return;	/* 46802a: ret  */
L_46802b:
	{ DWORD v_ = 0x4c4e94u; m->esp -= 4; M32(m->esp) = v_; }	/* 46802b: push 0x4c4e94 */
	m->esp -= 4; M32(m->esp) = 0x468035u; native_call(m, 0x46c840u);	/* 468030: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468035: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 468038: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 46803a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46803b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46803c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46803d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46803e: add esp, 0x94 */
	m->esp += 4 + 0; return;	/* 468044: ret  */
}

/* glWindow_resize (0x468450), lifted by tools/lift.py */
static void lift_468450(X86 *m)
{
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 468450: mov ecx, dword ptr [esp + 8] */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 468454: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468458: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468459: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46845a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46845c: push 0 */
	M32((DWORD)(0xa0e810u)) = m->eax;	/* 46845e: mov dword ptr [0xa0e810], eax */
	M32((DWORD)(0xa0e928u)) = m->ecx;	/* 468463: mov dword ptr [0xa0e928], ecx */
	m->esp -= 4; M32(m->esp) = 0x46846fu; native_call(m, M32(0x4a91d4u));	/* 468469: call dword ptr [0x4a91d4] */
	{ DWORD a_ = M32((DWORD)(0xa0e920u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46846f: cmp dword ptr [0xa0e920], 1 */
	if (!m->zf) goto L_4684a3;	/* 468476: jne 0x4684a3 */
	m->eax = M32((DWORD)(0xa0e928u));	/* 468478: mov eax, dword ptr [0xa0e928] */
	m->ecx = M32((DWORD)(0xa0e810u));	/* 46847d: mov ecx, dword ptr [0xa0e810] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 468483: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468485: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468486: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46848cu; lift_467f20(m);	/* 468487: call 0x467f20 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46848c: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46848f: test eax, eax */
	if (!m->zf) goto L_4684a3;	/* 468491: jne 0x4684a3 */
	{ DWORD v_ = 0x4c500cu; m->esp -= 4; M32(m->esp) = v_; }	/* 468493: push 0x4c500c */
	m->esp -= 4; M32(m->esp) = 0x46849du; native_call(m, 0x46c840u);	/* 468498: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46849d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4684a0: xor eax, eax */
	m->esp += 4 + 0; return;	/* 4684a2: ret  */
L_4684a3:
	M32((DWORD)(0x4c4de8u)) = 0xffffffffu;	/* 4684a3: mov dword ptr [0x4c4de8], 0xffffffff */
	m->eax = 0x1u;	/* 4684ad: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 4684b2: ret  */
}

/* image_initBy (0x46cd00), lifted by tools/lift.py */
static void lift_46cd00(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd00: push esi */
	m->esi = m->ecx;	/* 46cd01: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 46cd03: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cd06: test eax, eax */
	if (m->zf) goto L_46cd13;	/* 46cd08: je 0x46cd13 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd0a: push eax */
	m->esp -= 4; M32(m->esp) = 0x46cd10u; native_call(m, 0x49e7e0u);	/* 46cd0b: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cd10: add esp, 4 */
L_46cd13:
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 46cd13: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd17: push 0x4ad170 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd1c: push eax */
	m->esp -= 4; M32(m->esp) = 0x46cd22u; native_call(m, 0x49e9cau);	/* 46cd1d: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cd22: add esp, 8 */
	M32((DWORD)(m->esi + 0x4u)) = m->eax;	/* 46cd25: mov dword ptr [esi + 4], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cd28: test eax, eax */
	if (!m->zf) goto L_46cd30;	/* 46cd2a: jne 0x46cd30 */
	m->esi = M32(m->esp); m->esp += 4;	/* 46cd2c: pop esi */
	m->esp += 4 + 4; return;	/* 46cd2d: ret 4 */
L_46cd30:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd30: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd31: push 1 */
	m->ecx = (DWORD)(m->esi + 0x8u);	/* 46cd33: lea ecx, [esi + 8] */
	{ DWORD v_ = 0xeu; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd36: push 0xe */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd38: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46cd3eu; native_call(m, 0x49e836u);	/* 46cd39: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cd3e: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cd41: cmp eax, 1 */
	if (!m->cf) goto L_46cd58;	/* 46cd44: jae 0x46cd58 */
	{ DWORD v_ = 0x4c5948u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd46: push 0x4c5948 */
	{ DWORD v_ = 0xa1f0f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd4b: push 0xa1f0f0 */
	m->esp -= 4; M32(m->esp) = 0x46cd55u; native_call(m, 0x46c710u);	/* 46cd50: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cd55: add esp, 8 */
L_46cd58:
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 46cd58: mov edx, dword ptr [esi + 4] */
	m->eax = (DWORD)(m->esi + 0x16u);	/* 46cd5b: lea eax, [esi + 0x16] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd5e: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd5f: push 1 */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd61: push 0x28 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd63: push eax */
	m->esp -= 4; M32(m->esp) = 0x46cd69u; native_call(m, 0x49e836u);	/* 46cd64: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cd69: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cd6c: cmp eax, 1 */
	if (!m->cf) goto L_46cd83;	/* 46cd6f: jae 0x46cd83 */
	{ DWORD v_ = 0x4c592cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd71: push 0x4c592c */
	{ DWORD v_ = 0xa1f0f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd76: push 0xa1f0f0 */
	m->esp -= 4; M32(m->esp) = 0x46cd80u; native_call(m, 0x46c710u);	/* 46cd7b: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cd80: add esp, 8 */
L_46cd83:
	{ DWORD a_ = M16((DWORD)(m->esi + 0x24u)), b_ = 0x18u & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 46cd83: cmp word ptr [esi + 0x24], 0x18 */
	if (!m->zf) goto L_46cd91;	/* 46cd88: jne 0x46cd91 */
	m->eax = M32((DWORD)(m->esi + 0x26u));	/* 46cd8a: mov eax, dword ptr [esi + 0x26] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cd8d: test eax, eax */
	if (m->zf) goto L_46cda3;	/* 46cd8f: je 0x46cda3 */
L_46cd91:
	{ DWORD v_ = 0x4c5908u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd91: push 0x4c5908 */
	{ DWORD v_ = 0xa1f0f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46cd96: push 0xa1f0f0 */
	m->esp -= 4; M32(m->esp) = 0x46cda0u; native_call(m, 0x46c710u);	/* 46cd9b: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46cda0: add esp, 8 */
L_46cda3:
	m->ecx = M32((DWORD)(m->esi + 0x1au));	/* 46cda3: mov ecx, dword ptr [esi + 0x1a] */
	m->edx = M32((DWORD)(m->esi + 0x1eu));	/* 46cda6: mov edx, dword ptr [esi + 0x1e] */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 46cda9: mov eax, dword ptr [esi + 4] */
	M32((DWORD)(m->esi + 0x3eu)) = m->ecx;	/* 46cdac: mov dword ptr [esi + 0x3e], ecx */
	M32((DWORD)(m->esi + 0x42u)) = m->edx;	/* 46cdaf: mov dword ptr [esi + 0x42], edx */
	m->esi = M32(m->esp); m->esp += 4;	/* 46cdb2: pop esi */
	m->esp += 4 + 4; return;	/* 46cdb3: ret 4 */
}

/* shapeDat_initBy (0x466c00), lifted by tools/lift.py */
static void lift_466c00(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e79cu));	/* 466c00: mov eax, dword ptr [0xa0e79c] */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466c05: sub esp, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466c0b: test eax, eax */
	if (!m->zf && m->sf == m->of) goto L_466ccd;	/* 466c0d: jg 0x466ccd */
	m->eax = M32((DWORD)(0xa0e7a4u));	/* 466c13: mov eax, dword ptr [0xa0e7a4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466c18: test eax, eax */
	if (!m->zf) goto L_466ccd;	/* 466c1a: jne 0x466ccd */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 466c20: lea eax, [esp] */
	{ DWORD v_ = 0x4c4d20u; m->esp -= 4; M32(m->esp) = v_; }	/* 466c24: push 0x4c4d20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466c29: push eax */
	m->esp -= 4; M32(m->esp) = 0x466c2fu; native_call(m, 0x49e9ddu);	/* 466c2a: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 466c2f: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 466c33: push 0x4ad170 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466c38: push ecx */
	m->esp -= 4; M32(m->esp) = 0x466c3eu; native_call(m, 0x49e9cau);	/* 466c39: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466c3e: add esp, 0x10 */
	M32((DWORD)(0xa0e7a4u)) = m->eax;	/* 466c41: mov dword ptr [0xa0e7a4], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466c46: test eax, eax */
	if (!m->zf) goto L_466c66;	/* 466c48: jne 0x466c66 */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 466c4a: lea edx, [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466c4e: push edx */
	{ DWORD v_ = 0x4b3ee4u; m->esp -= 4; M32(m->esp) = v_; }	/* 466c4f: push 0x4b3ee4 */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 466c54: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x466c5eu; native_call(m, 0x46c710u);	/* 466c59: call 0x46c710 */
	m->eax = M32((DWORD)(0xa0e7a4u));	/* 466c5e: mov eax, dword ptr [0xa0e7a4] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466c63: add esp, 0xc */
L_466c66:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466c66: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 466c67: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 466c69: push 4 */
	{ DWORD v_ = 0xa0e79cu; m->esp -= 4; M32(m->esp) = v_; }	/* 466c6b: push 0xa0e79c */
	m->esp -= 4; M32(m->esp) = 0x466c75u; native_call(m, 0x49e836u);	/* 466c70: call 0x49e836 */
	m->eax = M32((DWORD)(0xa0e79cu));	/* 466c75: mov eax, dword ptr [0xa0e79c] */
	m->ecx = m->eax;	/* 466c7a: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 466c7c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 466c7f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 466c81: shl ecx, 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466c84: push ecx */
	m->esp -= 4; M32(m->esp) = 0x466c8au; native_call(m, 0x49f1aau);	/* 466c85: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466c8a: add esp, 0x14 */
	M32((DWORD)(0xa0e7a0u)) = m->eax;	/* 466c8d: mov dword ptr [0xa0e7a0], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466c92: test eax, eax */
	if (!m->zf) goto L_466cb4;	/* 466c94: jne 0x466cb4 */
	m->edx = M32((DWORD)(0xa0e79cu));	/* 466c96: mov edx, dword ptr [0xa0e79c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466c9c: push edx */
	{ DWORD v_ = 0x4b3eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 466c9d: push 0x4b3eb4 */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 466ca2: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x466cacu; native_call(m, 0x46c710u);	/* 466ca7: call 0x46c710 */
	m->eax = M32((DWORD)(0xa0e7a0u));	/* 466cac: mov eax, dword ptr [0xa0e7a0] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466cb1: add esp, 0xc */
L_466cb4:
	m->ecx = M32((DWORD)(0xa0e7a4u));	/* 466cb4: mov ecx, dword ptr [0xa0e7a4] */
	m->edx = M32((DWORD)(0xa0e79cu));	/* 466cba: mov edx, dword ptr [0xa0e79c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466cc0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466cc1: push edx */
	{ DWORD v_ = 0x44u; m->esp -= 4; M32(m->esp) = v_; }	/* 466cc2: push 0x44 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466cc4: push eax */
	m->esp -= 4; M32(m->esp) = 0x466ccau; native_call(m, 0x49e836u);	/* 466cc5: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466cca: add esp, 0x10 */
L_466ccd:
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466ccd: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 466cd3: ret  */
}

/* skelDat_initBy (0x46afe0), lifted by tools/lift.py */
static void lift_46afe0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0eab4u));	/* 46afe0: mov eax, dword ptr [0xa0eab4] */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46afe5: sub esp, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46afeb: test eax, eax */
	if (!m->zf && m->sf == m->of) goto L_46b0ad;	/* 46afed: jg 0x46b0ad */
	m->eax = M32((DWORD)(0xa0eabcu));	/* 46aff3: mov eax, dword ptr [0xa0eabc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46aff8: test eax, eax */
	if (!m->zf) goto L_46b0ad;	/* 46affa: jne 0x46b0ad */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 46b000: lea eax, [esp] */
	{ DWORD v_ = 0x4c54b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b004: push 0x4c54b4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b009: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b00fu; native_call(m, 0x49e9ddu);	/* 46b00a: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 46b00f: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b013: push 0x4ad170 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b018: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46b01eu; native_call(m, 0x49e9cau);	/* 46b019: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b01e: add esp, 0x10 */
	M32((DWORD)(0xa0eabcu)) = m->eax;	/* 46b021: mov dword ptr [0xa0eabc], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46b026: test eax, eax */
	if (!m->zf) goto L_46b046;	/* 46b028: jne 0x46b046 */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 46b02a: lea edx, [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b02e: push edx */
	{ DWORD v_ = 0x4b3ee4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b02f: push 0x4b3ee4 */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b034: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46b03eu; native_call(m, 0x46c710u);	/* 46b039: call 0x46c710 */
	m->eax = M32((DWORD)(0xa0eabcu));	/* 46b03e: mov eax, dword ptr [0xa0eabc] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b043: add esp, 0xc */
L_46b046:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b046: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b047: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b049: push 4 */
	{ DWORD v_ = 0xa0eab4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b04b: push 0xa0eab4 */
	m->esp -= 4; M32(m->esp) = 0x46b055u; native_call(m, 0x49e836u);	/* 46b050: call 0x49e836 */
	m->eax = M32((DWORD)(0xa0eab4u));	/* 46b055: mov eax, dword ptr [0xa0eab4] */
	m->ecx = m->eax;	/* 46b05a: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b05c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46b05f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b061: shl ecx, 2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b064: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46b06au; native_call(m, 0x49f1aau);	/* 46b065: call 0x49f1aa */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b06a: add esp, 0x14 */
	M32((DWORD)(0xa0eab8u)) = m->eax;	/* 46b06d: mov dword ptr [0xa0eab8], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46b072: test eax, eax */
	if (!m->zf) goto L_46b094;	/* 46b074: jne 0x46b094 */
	m->edx = M32((DWORD)(0xa0eab4u));	/* 46b076: mov edx, dword ptr [0xa0eab4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b07c: push edx */
	{ DWORD v_ = 0x4b3eb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b07d: push 0x4b3eb4 */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b082: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46b08cu; native_call(m, 0x46c710u);	/* 46b087: call 0x46c710 */
	m->eax = M32((DWORD)(0xa0eab8u));	/* 46b08c: mov eax, dword ptr [0xa0eab8] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b091: add esp, 0xc */
L_46b094:
	m->ecx = M32((DWORD)(0xa0eabcu));	/* 46b094: mov ecx, dword ptr [0xa0eabc] */
	m->edx = M32((DWORD)(0xa0eab4u));	/* 46b09a: mov edx, dword ptr [0xa0eab4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b0a0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b0a1: push edx */
	{ DWORD v_ = 0x44u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b0a2: push 0x44 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b0a4: push eax */
	m->esp -= 4; M32(m->esp) = 0x46b0aau; native_call(m, 0x49e836u);	/* 46b0a5: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b0aa: add esp, 0x10 */
L_46b0ad:
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b0ad: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 46b0b3: ret  */
}

/* timer_getGameTime (0x487490), lifted by tools/lift.py */
static void lift_487490(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487490: sub esp, 0x20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 487493: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487494: push esi */
	m->esi = m->ecx;	/* 487495: mov esi, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 487497: xor ebx, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 487499: push edi */
	m->edi = M32((DWORD)(0x4a9140u));	/* 48749a: mov edi, dword ptr [0x4a9140] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4874a0: cmp dword ptr [esi + 4], ebx */
	if (!m->zf) goto L_4874ff;	/* 4874a3: jne 0x4874ff */
	m->eax = (DWORD)(m->esi + 0xcu);	/* 4874a5: lea eax, [esi + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4874a8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4874afu; native_call(m, M32(0x4a913cu));	/* 4874a9: call dword ptr [0x4a913c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4874af: test eax, eax */
	if (!m->zf) goto L_4874c5;	/* 4874b1: jne 0x4874c5 */
	{ DWORD v_ = 0x4c7b80u; m->esp -= 4; M32(m->esp) = v_; }	/* 4874b3: push 0x4c7b80 */
	{ DWORD v_ = 0xae2f00u; m->esp -= 4; M32(m->esp) = v_; }	/* 4874b8: push 0xae2f00 */
	m->esp -= 4; M32(m->esp) = 0x4874c2u; native_call(m, 0x46c710u);	/* 4874bd: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4874c2: add esp, 8 */
L_4874c5:
	m->ecx = (DWORD)(m->esi + 0x14u);	/* 4874c5: lea ecx, [esi + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4874c8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4874cbu; native_call(m, m->edi);	/* 4874c9: call edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4874cb: test eax, eax */
	if (!m->zf) goto L_4874e1;	/* 4874cd: jne 0x4874e1 */
	{ DWORD v_ = 0x4c7b80u; m->esp -= 4; M32(m->esp) = v_; }	/* 4874cf: push 0x4c7b80 */
	{ DWORD v_ = 0xae2f00u; m->esp -= 4; M32(m->esp) = v_; }	/* 4874d4: push 0xae2f00 */
	m->esp -= 4; M32(m->esp) = 0x4874deu; native_call(m, 0x46c710u);	/* 4874d9: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4874de: add esp, 8 */
L_4874e1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x34u)));	/* 4874e1: fld dword ptr [esi + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4874e4: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4874ea: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4874ec: test ah, 0x41 */
	if (m->zf) goto L_4874f8;	/* 4874ef: je 0x4874f8 */
	M32((DWORD)(m->esi + 0x34u)) = 0x3d888889u;	/* 4874f1: mov dword ptr [esi + 0x34], 0x3d888889 */
L_4874f8:
	M32((DWORD)(m->esi + 0x4u)) = 0x1u;	/* 4874f8: mov dword ptr [esi + 4], 1 */
L_4874ff:
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 4874ff: mov eax, dword ptr [esi + 8] */
	m->edx = (DWORD)(m->esp + 0xcu);	/* 487502: lea edx, [esp + 0xc] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 487506: push ebp */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 487507: inc eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487508: push edx */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 487509: mov dword ptr [esi + 8], eax */
	m->esp -= 4; M32(m->esp) = 0x48750eu; native_call(m, m->edi);	/* 48750c: call edi */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48750e: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esi + 0x14u));	/* 487512: mov ecx, dword ptr [esi + 0x14] */
	m->ebp = M32((DWORD)(m->esi + 0x18u));	/* 487515: mov ebp, dword ptr [esi + 0x18] */
	m->edx = m->eax;	/* 487518: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48751a: sub edx, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 48751c: mov ecx, dword ptr [esp + 0x14] */
	m->edi = m->ecx;	/* 487520: mov edi, ecx */
	M32((DWORD)(m->esi + 0x1cu)) = m->edx;	/* 487522: mov dword ptr [esi + 0x1c], edx */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 487525: mov edx, dword ptr [esi + 0x24] */
	M32((DWORD)(m->esi + 0x14u)) = m->eax;	/* 487528: mov dword ptr [esi + 0x14], eax */
	{ DWORD a_ = m->edi, b_ = m->ebp, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->edi = r_; }	/* 48752b: sbb edi, ebp */
	M32((DWORD)(m->esi + 0x18u)) = m->ecx;	/* 48752d: mov dword ptr [esi + 0x18], ecx */
	M32((DWORD)(m->esi + 0x20u)) = m->edi;	/* 487530: mov dword ptr [esi + 0x20], edi */
	m->eax = M32((DWORD)(m->esi + 0x1cu));	/* 487533: mov eax, dword ptr [esi + 0x1c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 487536: add edx, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 487538: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esi + 0x24u)) = m->edx;	/* 48753c: mov dword ptr [esi + 0x24], edx */
	m->eax = M32((DWORD)(m->esi + 0x28u));	/* 48753f: mov eax, dword ptr [esi + 0x28] */
	m->ecx = m->edi;	/* 487542: mov ecx, edi */
	m->edi = M32((DWORD)(m->esi + 0xcu));	/* 487544: mov edi, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->ecx, c0_ = (DWORD)m->cf; unsigned long long w_ = (unsigned long long)a_ + b_ + c0_; DWORD r_ = (DWORD)w_; m->cf = (int)(w_ >> 32); m->of = (int)(((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 487547: adc eax, ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 487549: mov dword ptr [esp + 0x2c], ecx */
	m->ecx = M32((DWORD)(m->esi + 0x10u));	/* 48754d: mov ecx, dword ptr [esi + 0x10] */
	M32((DWORD)(m->esi + 0x28u)) = m->eax;	/* 487550: mov dword ptr [esi + 0x28], eax */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 487553: mov edx, dword ptr [esi + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487556: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 487558: mov dword ptr [esp + 0x20], edx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 48755c: mov dword ptr [esp + 0x24], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 487560: mov dword ptr [esp + 0x10], edi */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 487564: mov dword ptr [esp + 0x14], ecx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 487568: pop ebp */
	if (m->sf != m->of) goto L_4875a5;	/* 487569: jl 0x4875a5 */
	if (!m->zf && m->sf == m->of) goto L_487571;	/* 48756b: jg 0x487571 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48756d: cmp edx, edi */
	if (m->cf || m->zf) goto L_4875a5;	/* 48756f: jbe 0x4875a5 */
L_487571:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487571: cmp eax, ebx */
	if (m->sf != m->of) goto L_487599;	/* 487573: jl 0x487599 */
	if (!m->zf && m->sf == m->of) goto L_48757b;	/* 487575: jg 0x48757b */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487577: cmp edx, ebx */
	if (m->cf || m->zf) goto L_487599;	/* 487579: jbe 0x487599 */
L_48757b:
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0xcu));	/* 48757b: fild qword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 48757f: mov eax, dword ptr [esi + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->ebx;	/* 487582: mov dword ptr [esp + 0x18], ebx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 487586: mov dword ptr [esp + 0x14], eax */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x14u));	/* 48758a: fimul dword ptr [esp + 0x14] */
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0x1cu));	/* 48758e: fild qword ptr [esp + 0x1c] */
	ST(1) = ST(1) / ST(0); FPOP();	/* 487592: fdivp st(1) */
	MF((DWORD)(m->esi + 0x2cu)) = (float)ST(0); FPOP();	/* 487594: fstp dword ptr [esi + 0x2c] */
	goto L_48759c;	/* 487597: jmp 0x48759c */
L_487599:
	M32((DWORD)(m->esi + 0x2cu)) = m->ebx;	/* 487599: mov dword ptr [esi + 0x2c], ebx */
L_48759c:
	M32((DWORD)(m->esi + 0x24u)) = m->ebx;	/* 48759c: mov dword ptr [esi + 0x24], ebx */
	M32((DWORD)(m->esi + 0x8u)) = m->ebx;	/* 48759f: mov dword ptr [esi + 8], ebx */
	M32((DWORD)(m->esi + 0x28u)) = m->ebx;	/* 4875a2: mov dword ptr [esi + 0x28], ebx */
L_4875a5:
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0x24u));	/* 4875a5: fild qword ptr [esp + 0x24] */
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0xcu));	/* 4875a9: fild qword ptr [esp + 0xc] */
	ST(1) = ST(1) / ST(0); FPOP();	/* 4875ad: fdivp st(1) */
	MF((DWORD)(m->esi + 0x30u)) = (float)ST(0);	/* 4875af: fst dword ptr [esi + 0x30] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x34u)); FPOP();	/* 4875b2: fcomp dword ptr [esi + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4875b5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4875b7: test ah, 0x41 */
	if (!m->zf) goto L_4875c2;	/* 4875ba: jne 0x4875c2 */
	m->ecx = M32((DWORD)(m->esi + 0x34u));	/* 4875bc: mov ecx, dword ptr [esi + 0x34] */
	M32((DWORD)(m->esi + 0x30u)) = m->ecx;	/* 4875bf: mov dword ptr [esi + 0x30], ecx */
L_4875c2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x30u)));	/* 4875c2: fld dword ptr [esi + 0x30] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4875c5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4875c6: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4875c7: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4875c8: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 4875cb: ret  */
}

/* armc_461210 (0x461210), lifted by tools/lift.py */
static void lift_461210(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 461210: push esi */
	m->esi = m->ecx;	/* 461211: mov esi, ecx */
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 461213: lea ecx, [esi + 0xc] */
	m->esp -= 4; M32(m->esp) = 0x46121bu; lift_487490(m);	/* 461216: call 0x487490 */
	m->eax = M32((DWORD)(m->esi + 0x70u));	/* 46121b: mov eax, dword ptr [esi + 0x70] */
	m->ecx = 0xau;	/* 46121e: mov ecx, 0xa */
	MF((DWORD)(m->esi + m->eax*4 + 0x48u)) = (float)ST(0); FPOP();	/* 461223: fstp dword ptr [esi + eax*4 + 0x48] */
	m->eax = M32((DWORD)(m->esi + 0x70u));	/* 461227: mov eax, dword ptr [esi + 0x70] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46122a: inc eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46122b: cdq  */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 46122c: fld dword ptr [0x4a93e8] */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 461232: idiv ecx */
	m->eax = (DWORD)(m->esi + 0x48u);	/* 461234: lea eax, [esi + 0x48] */
	M32((DWORD)(m->esi + 0x70u)) = m->edx;	/* 461237: mov dword ptr [esi + 0x70], edx */
L_46123a:
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 46123a: fadd dword ptr [eax] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46123c: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 46123f: dec ecx */
	if (!m->zf) goto L_46123a;	/* 461240: jne 0x46123a */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a955cu));	/* 461242: fmul dword ptr [0x4a955c] */
	MF((DWORD)(m->esi + 0x44u)) = (float)ST(0);	/* 461248: fst dword ptr [esi + 0x44] */
	m->esi = M32(m->esp); m->esp += 4;	/* 46124b: pop esi */
	m->esp += 4 + 0; return;	/* 46124c: ret  */
}

/* sys_checkClockTampering (0x43f300), lifted by tools/lift.py */
static void lift_43f300(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f300: sub esp, 8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f303: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f304: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f305: push edi */
	m->edi = M32((DWORD)(0x4a910cu));	/* 43f306: mov edi, dword ptr [0x4a910c] */
	{ DWORD v_ = 0x9dd8d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f30c: push 0x9dd8d0 */
	m->esp -= 4; M32(m->esp) = 0x43f313u; native_call(m, m->edi);	/* 43f311: call edi */
	m->ebx = M32((DWORD)(0x4a9364u));	/* 43f313: mov ebx, dword ptr [0x4a9364] */
	m->esp -= 4; M32(m->esp) = 0x43f31bu; native_call(m, m->ebx);	/* 43f319: call ebx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(0x9dd8d8u))) & 0xffff);	/* 43f31b: mov cx, word ptr [0x9dd8d8] */
	m->edx = m->eax;	/* 43f322: mov edx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f324: xor eax, eax */
	{ DWORD a_ = (m->ecx & 0xffff), b_ = M16((DWORD)(0x9dd880u)) & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 43f326: cmp cx, word ptr [0x9dd880] */
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(0x9dd8dau))) & 0xffff);	/* 43f32d: mov ax, word ptr [0x9dd8da] */
	M32((DWORD)(0x9dd8e0u)) = m->edx;	/* 43f333: mov dword ptr [0x9dd8e0], edx */
	if (m->cf || m->zf) goto L_43f33e;	/* 43f339: jbe 0x43f33e */
	{ DWORD a_ = m->eax, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43f33b: add eax, 0x3c */
L_43f33e:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f33e: xor ecx, ecx */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(0x9dd882u))) & 0xffff);	/* 43f340: mov cx, word ptr [0x9dd882] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f347: cmp eax, ecx */
	if (m->cf || m->zf) goto L_43f37b;	/* 43f349: jbe 0x43f37b */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 43f34b: lea ecx, [ecx + ecx*2] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 43f34e: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 43f351: lea ecx, [ecx + ecx*4] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43f354: shl ecx, 2 */
	m->esi = m->ecx;	/* 43f357: mov esi, ecx */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43f359: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(0x9dd884u));	/* 43f35c: mov eax, dword ptr [0x9dd884] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43f361: shl ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43f364: sub ecx, esi */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f366: and eax, 0xffff */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43f36b: sub ecx, eax */
	m->eax = M32((DWORD)(0x9dd8dcu));	/* 43f36d: mov eax, dword ptr [0x9dd8dc] */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f372: and eax, 0xffff */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43f377: add ecx, eax */
	goto L_43f393;	/* 43f379: jmp 0x43f393 */
L_43f37b:
	m->eax = M32((DWORD)(0x9dd884u));	/* 43f37b: mov eax, dword ptr [0x9dd884] */
	m->ecx = M32((DWORD)(0x9dd8dcu));	/* 43f380: mov ecx, dword ptr [0x9dd8dc] */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f386: and eax, 0xffff */
	{ DWORD a_ = m->ecx, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43f38b: and ecx, 0xffff */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43f391: sub ecx, eax */
L_43f393:
	m->esi = M32((DWORD)(0x9dd8e8u));	/* 43f393: mov esi, dword ptr [0x9dd8e8] */
	m->eax = 0x10624dd3u;	/* 43f399: mov eax, 0x10624dd3 */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43f39e: sub edx, esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43f3a0: xor esi, esi */
	{ unsigned long long p_ = (unsigned long long)m->eax * m->edx; m->eax = (DWORD)p_; m->edx = (DWORD)(p_ >> 32); m->cf = m->of = m->edx != 0; }	/* 43f3a2: mul edx */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43f3a4: shr edx, 6 */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 43f3a7: mov dword ptr [esp + 0xc], edx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 43f3ab: mov dword ptr [esp + 0x10], esi */
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0xcu));	/* 43f3af: fild qword ptr [esp + 0xc] */
	M32((DWORD)(m->esp + 0xcu)) = m->ecx;	/* 43f3b3: mov dword ptr [esp + 0xc], ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 43f3b7: mov dword ptr [esp + 0x10], esi */
	M32((DWORD)(0x9dd860u)) = m->ecx;	/* 43f3bb: mov dword ptr [0x9dd860], ecx */
	M32((DWORD)(0x9dd8ecu)) = m->edx;	/* 43f3c1: mov dword ptr [0x9dd8ec], edx */
	{ long double t = ST(0); FPUSH(t); }	/* 43f3c7: fld st(0) */
	ST(0) = ST(0) * (long double)*(const double *)(DWORD)(0x4a9598u);	/* 43f3c9: fmul qword ptr [0x4a9598] */
	FPUSH((long double)*(const long long *)(DWORD)(m->esp + 0xcu));	/* 43f3cf: fild qword ptr [esp + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 43f3d3: faddp st(1) */
	FCOM(ST(0), ST(1)); FPOP();	/* 43f3d5: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43f3d7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43f3d9: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 43f3dc: fstp st(0) */
	if (m->zf) goto L_43f43a;	/* 43f3de: je 0x43f43a */
	{ DWORD a_ = M32((DWORD)(0x9dae74u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f3e0: cmp dword ptr [0x9dae74], 1 */
	if (!m->zf) goto L_43f3f0;	/* 43f3e7: jne 0x43f3f0 */
	{ DWORD v_ = 0x4b2914u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f3e9: push 0x4b2914 */
	goto L_43f3f5;	/* 43f3ee: jmp 0x43f3f5 */
L_43f3f0:
	{ DWORD v_ = 0x4b2888u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f3f0: push 0x4b2888 */
L_43f3f5:
	m->esp -= 4; M32(m->esp) = 0x43f3fau; native_call(m, 0x41edf0u);	/* 43f3f5: call 0x41edf0 */
	m->eax = M32((DWORD)(0x9dd904u));	/* 43f3fa: mov eax, dword ptr [0x9dd904] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f3ff: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f402: cmp eax, esi */
	if (m->zf) goto L_43f423;	/* 43f404: je 0x43f423 */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 43f406: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f40c: push esi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f40d: push esi */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f40e: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f410: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43f417u; native_call(m, M32(0x4a9328u));	/* 43f411: call dword ptr [0x4a9328] */
	m->edi = M32(m->esp); m->esp += 4;	/* 43f417: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43f418: pop esi */
	m->eax = 0x1u;	/* 43f419: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43f41e: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f41f: add esp, 8 */
	m->esp += 4 + 0; return;	/* 43f422: ret  */
L_43f423:
	{ DWORD v_ = 0x9dd878u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f423: push 0x9dd878 */
	m->esp -= 4; M32(m->esp) = 0x43f42au; native_call(m, m->edi);	/* 43f428: call edi */
	m->esp -= 4; M32(m->esp) = 0x43f42cu; native_call(m, m->ebx);	/* 43f42a: call ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 43f42c: pop edi */
	M32((DWORD)(0x9dd8e8u)) = m->eax;	/* 43f42d: mov dword ptr [0x9dd8e8], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 43f432: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43f433: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43f435: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f436: add esp, 8 */
	m->esp += 4 + 0; return;	/* 43f439: ret  */
L_43f43a:
	{ DWORD v_ = 0x9dd878u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f43a: push 0x9dd878 */
	m->esp -= 4; M32(m->esp) = 0x43f441u; native_call(m, m->edi);	/* 43f43f: call edi */
	m->esp -= 4; M32(m->esp) = 0x43f443u; native_call(m, m->ebx);	/* 43f441: call ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 43f443: pop edi */
	M32((DWORD)(0x9dd8e8u)) = m->eax;	/* 43f444: mov dword ptr [0x9dd8e8], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 43f449: pop esi */
	m->eax = 0x1u;	/* 43f44a: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43f44f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f450: add esp, 8 */
	m->esp += 4 + 0; return;	/* 43f453: ret  */
}

/* profile_deleteFiles (0x44ba60), lifted by tools/lift.py */
static void lift_44ba60(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ba60: sub esp, 0x84 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ba66: push ebx */
	m->ebx = M32((DWORD)(0x9f8d74u));	/* 44ba67: mov ebx, dword ptr [0x9f8d74] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44ba6d: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ba6e: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ba6f: push edi */
	{ DWORD v_ = 0x4b2adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 44ba70: push 0x4b2adc */
	m->esp -= 4; M32(m->esp) = 0x44ba7au; native_call(m, 0x49f8a6u);	/* 44ba75: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ba7a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44ba7d: test eax, eax */
	if (!m->zf) goto L_44bb0e;	/* 44ba7f: jne 0x44bb0e */
	m->ecx = 0x20u;	/* 44ba85: mov ecx, 0x20 */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 44ba8a: lea edi, [esp + 0x14] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44ba8e: rep stosd dword ptr es:[edi], eax */
	m->eax = (DWORD)(m->ebx + m->ebx*8 + 0x0u);	/* 44ba90: lea eax, [ebx + ebx*8] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44ba93: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 44ba96: lea edx, [esp + 0x14] */
	m->edi = (DWORD)(m->eax*8 + 0x9f684cu);	/* 44ba9a: lea edi, [eax*8 + 0x9f684c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44baa1: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44baa3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44baa5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44baa7: sub edi, ecx */
	m->eax = m->ecx;	/* 44baa9: mov eax, ecx */
	m->esi = m->edi;	/* 44baab: mov esi, edi */
	m->edi = m->edx;	/* 44baad: mov edi, edx */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 44baaf: lea edx, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44bab3: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44bab6: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 44bab8: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44baba: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44babc: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44babf: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4b2afcu;	/* 44bac1: mov edi, 0x4b2afc */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44bac6: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44bac9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44bacb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44bacd: sub edi, ecx */
	m->esi = m->edi;	/* 44bacf: mov esi, edi */
	m->ebp = m->ecx;	/* 44bad1: mov ebp, ecx */
	m->edi = m->edx;	/* 44bad3: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44bad5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44bad8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebp;	/* 44bada: mov ecx, ebp */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44badc: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44badd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44bae0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebp;	/* 44bae2: mov ecx, ebp */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 44bae4: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44bae8: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44baeb: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44baec: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = M32((DWORD)(0x4a9104u));	/* 44baee: mov esi, dword ptr [0x4a9104] */
	m->esp -= 4; M32(m->esp) = 0x44baf6u; native_call(m, m->esi);	/* 44baf4: call esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44baf6: test eax, eax */
	if (!m->zf) goto L_44bb01;	/* 44baf8: jne 0x44bb01 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 44bafa: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44bafe: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44bb01u; native_call(m, m->esi);	/* 44baff: call esi */
L_44bb01:
	{ DWORD v_ = 0x4b2a80u; m->esp -= 4; M32(m->esp) = v_; }	/* 44bb01: push 0x4b2a80 */
	m->esp -= 4; M32(m->esp) = 0x44bb0bu; native_call(m, 0x49f8a6u);	/* 44bb06: call 0x49f8a6 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44bb0b: add esp, 4 */
L_44bb0e:
	m->edx = M32((DWORD)(0x9f9008u));	/* 44bb0e: mov edx, dword ptr [0x9f9008] */
	m->ebp = m->ebx;	/* 44bb14: mov ebp, ebx */
	m->esi = (DWORD)(m->edx + 0xffffffffu);	/* 44bb16: lea esi, [edx - 1] */
	{ DWORD a_ = m->ebx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44bb19: cmp ebx, esi */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 44bb1b: mov dword ptr [esp + 0x10], esi */
	if (m->sf == m->of) goto L_44bb58;	/* 44bb1f: jge 0x44bb58 */
	m->edx = m->esi;	/* 44bb21: mov edx, esi */
	m->eax = (DWORD)(m->ebx + m->ebx*8 + 0x0u);	/* 44bb23: lea eax, [ebx + ebx*8] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44bb26: sub edx, ebx */
	m->eax = (DWORD)(m->eax*8 + 0x9f684cu);	/* 44bb28: lea eax, [eax*8 + 0x9f684c] */
	m->ebp = (DWORD)(m->edx + m->ebx*1 + 0x0u);	/* 44bb2f: lea ebp, [edx + ebx] */
L_44bb32:
	m->ebx = (DWORD)(m->eax + 0x48u);	/* 44bb32: lea ebx, [eax + 0x48] */
	m->ecx = 0x10u;	/* 44bb35: mov ecx, 0x10 */
	m->esi = m->ebx;	/* 44bb3a: mov esi, ebx */
	m->edi = m->eax;	/* 44bb3c: mov edi, eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44bb3e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(m->eax + 0x44u));	/* 44bb40: mov ecx, dword ptr [eax + 0x44] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 44bb43: dec edx */
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->ecx;	/* 44bb44: mov dword ptr [eax - 4], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x88u));	/* 44bb47: mov ecx, dword ptr [eax + 0x88] */
	M32((DWORD)(m->eax + 0x40u)) = m->ecx;	/* 44bb4d: mov dword ptr [eax + 0x40], ecx */
	m->eax = m->ebx;	/* 44bb50: mov eax, ebx */
	if (!m->zf) goto L_44bb32;	/* 44bb52: jne 0x44bb32 */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 44bb54: mov esi, dword ptr [esp + 0x10] */
L_44bb58:
	m->edx = (DWORD)(m->ebp + m->ebp*8 + 0x0u);	/* 44bb58: lea edx, [ebp + ebp*8] */
	m->ecx = 0x10u;	/* 44bb5c: mov ecx, 0x10 */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44bb61: shl edx, 3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44bb64: xor eax, eax */
	m->edi = (DWORD)(m->edx + 0x9f684cu);	/* 44bb66: lea edi, [edx + 0x9f684c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44bb6c: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44bb6e: xor ecx, ecx */
	m->eax = m->esi;	/* 44bb70: mov eax, esi */
	M32((DWORD)(m->edx + 0x9f6848u)) = m->ecx;	/* 44bb72: mov dword ptr [edx + 0x9f6848], ecx */
	M32((DWORD)(m->edx + 0x9f688cu)) = 0xffffffffu;	/* 44bb78: mov dword ptr [edx + 0x9f688c], 0xffffffff */
	m->edx = M32((DWORD)(0x9f8d74u));	/* 44bb82: mov edx, dword ptr [0x9f8d74] */
	m->edi = M32(m->esp); m->esp += 4;	/* 44bb88: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44bb89: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44bb8a: pop ebp */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44bb8b: cmp edx, eax */
	M32((DWORD)(0x9f9008u)) = m->eax;	/* 44bb8d: mov dword ptr [0x9f9008], eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44bb92: pop ebx */
	if (m->sf != m->of) goto L_44bbe2;	/* 44bb93: jl 0x44bbe2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44bb95: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_44bbbd;	/* 44bb97: jg 0x44bbbd */
	M32((DWORD)(0x9f8c5cu)) = m->ecx;	/* 44bb99: mov dword ptr [0x9f8c5c], ecx */
	M32((DWORD)(0x9f8c4cu)) = m->ecx;	/* 44bb9f: mov dword ptr [0x9f8c4c], ecx */
	M32((DWORD)(0x9f8d74u)) = m->ecx;	/* 44bba5: mov dword ptr [0x9f8d74], ecx */
	M32((DWORD)(0x9f9008u)) = m->ecx;	/* 44bbab: mov dword ptr [0x9f9008], ecx */
	m->esp -= 4; M32(m->esp) = 0x44bbb6u; native_call(m, 0x447320u);	/* 44bbb1: call 0x447320 */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44bbb6: add esp, 0x84 */
	m->esp += 4 + 0; return;	/* 44bbbc: ret  */
L_44bbbd:
	m->eax = M32((DWORD)(0x9f8c5cu));	/* 44bbbd: mov eax, dword ptr [0x9f8c5c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44bbc2: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_44bbce;	/* 44bbc4: jle 0x44bbce */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44bbc6: dec eax */
	M32((DWORD)(0x9f8c5cu)) = m->eax;	/* 44bbc7: mov dword ptr [0x9f8c5c], eax */
	goto L_44bbd4;	/* 44bbcc: jmp 0x44bbd4 */
L_44bbce:
	{ DWORD a_ = M32((DWORD)(0x9f8c4cu)), r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); M32((DWORD)(0x9f8c4cu)) = r_; }	/* 44bbce: dec dword ptr [0x9f8c4c] */
L_44bbd4:
	m->edx = M32((DWORD)(0x9f8c4cu));	/* 44bbd4: mov edx, dword ptr [0x9f8c4c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44bbda: add edx, eax */
	M32((DWORD)(0x9f8d74u)) = m->edx;	/* 44bbdc: mov dword ptr [0x9f8d74], edx */
L_44bbe2:
	m->esp -= 4; M32(m->esp) = 0x44bbe7u; native_call(m, 0x447320u);	/* 44bbe2: call 0x447320 */
	m->esp -= 4; M32(m->esp) = 0x44bbecu; native_call(m, 0x44b7a0u);	/* 44bbe7: call 0x44b7a0 */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44bbec: add esp, 0x84 */
	m->esp += 4 + 0; return;	/* 44bbf2: ret  */
}

/* reg_writeCharacterSettings (0x432400), lifted by tools/lift.py */
static void lift_432400(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 432400: sub esp, 8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 432403: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 432406: xor eax, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 432408: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 432409: push edi */
	m->edi = 0x9dd1d8u;	/* 43240a: mov edi, 0x9dd1d8 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43240f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 432411: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 432413: sub edi, ecx */
	m->eax = m->ecx;	/* 432415: mov eax, ecx */
	m->esi = m->edi;	/* 432417: mov esi, edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 432419: shr ecx, 2 */
	m->edi = 0x9dd570u;	/* 43241c: mov edi, 0x9dd570 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 432421: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 432423: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 432425: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 432427: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43242a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43242c: or ecx, 0xffffffff */
	m->edi = 0x9dd20eu;	/* 43242f: mov edi, 0x9dd20e */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 432434: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 432436: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 432438: sub edi, ecx */
	m->edx = m->ecx;	/* 43243a: mov edx, ecx */
	m->esi = m->edi;	/* 43243c: mov esi, edi */
	m->edi = 0x9dd5a6u;	/* 43243e: mov edi, 0x9dd5a6 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 432443: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 432446: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 432448: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43244a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43244d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x9dd570u;	/* 43244f: mov edi, 0x9dd570 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 432454: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 432457: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 432459: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43245b: sub edi, ecx */
	m->eax = m->ecx;	/* 43245d: mov eax, ecx */
	m->esi = m->edi;	/* 43245f: mov esi, edi */
	m->edi = 0x76d450u;	/* 432461: mov edi, 0x76d450 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 432466: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 432469: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43246b: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43246d: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43246f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 432472: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0x4df9c8u;	/* 432474: mov edi, 0x4df9c8 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 432479: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43247c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43247e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 432480: sub edi, ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9e9u))) & 0xff) << 0);	/* 432482: mov al, byte ptr [0x4df9e9] */
	m->edx = m->ecx;	/* 432487: mov edx, ecx */
	m->esi = m->edi;	/* 432489: mov esi, edi */
	m->edi = 0x5b1b30u;	/* 43248b: mov edi, 0x5b1b30 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 432490: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 432493: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 432495: mov ecx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9e8u))) & 0xff) << 0);	/* 432497: mov dl, byte ptr [0x4df9e8] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43249d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4324a0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9ebu))) & 0xff) << 0);	/* 4324a2: mov cl, byte ptr [0x4df9eb] */
	M8((DWORD)(0x5b1b51u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4324a8: mov byte ptr [0x5b1b51], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9ecu))) & 0xff) << 0);	/* 4324ad: mov al, byte ptr [0x4df9ec] */
	M8((DWORD)(0x5b1b53u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4324b2: mov byte ptr [0x5b1b53], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9edu))) & 0xff) << 0);	/* 4324b8: mov cl, byte ptr [0x4df9ed] */
	M8((DWORD)(0x5b1b54u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4324be: mov byte ptr [0x5b1b54], al */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 4324c3: lea eax, [esp + 0xc] */
	M8((DWORD)(0x5b1b50u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4324c7: mov byte ptr [0x5b1b50], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9eau))) & 0xff) << 0);	/* 4324cd: mov dl, byte ptr [0x4df9ea] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4324d3: push eax */
	{ DWORD v_ = 0xf003fu; m->esp -= 4; M32(m->esp) = v_; }	/* 4324d4: push 0xf003f */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4324d9: push 0 */
	{ DWORD v_ = 0x4b179cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4324db: push 0x4b179c */
	{ DWORD v_ = 0x80000001u; m->esp -= 4; M32(m->esp) = v_; }	/* 4324e0: push 0x80000001 */
	M8((DWORD)(0x5b1b55u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4324e5: mov byte ptr [0x5b1b55], cl */
	M8((DWORD)(0x5b1b52u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4324eb: mov byte ptr [0x5b1b52], dl */
	m->esp -= 4; M32(m->esp) = 0x4324f7u; native_call(m, M32(0x4a9004u));	/* 4324f1: call dword ptr [0x4a9004] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4324f7: test eax, eax */
	if (!m->zf) goto L_432601;	/* 4324f9: jne 0x432601 */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 4324ff: mov ecx, dword ptr [esp + 0xc] */
	m->esi = M32((DWORD)(0x4a9000u));	/* 432503: mov esi, dword ptr [0x4a9000] */
	{ DWORD v_ = 0x1eu; m->esp -= 4; M32(m->esp) = v_; }	/* 432509: push 0x1e */
	{ DWORD v_ = 0x9dd570u; m->esp -= 4; M32(m->esp) = v_; }	/* 43250b: push 0x9dd570 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 432510: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 432512: push eax */
	{ DWORD v_ = 0x4b1794u; m->esp -= 4; M32(m->esp) = v_; }	/* 432513: push 0x4b1794 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 432518: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43251bu; native_call(m, m->esi);	/* 432519: call esi */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 43251b: mov edx, dword ptr [esp + 0xc] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 43251f: push 0x20 */
	{ DWORD v_ = 0x5b1b30u; m->esp -= 4; M32(m->esp) = v_; }	/* 432521: push 0x5b1b30 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 432526: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 432528: push 0 */
	{ DWORD v_ = 0x4b1788u; m->esp -= 4; M32(m->esp) = v_; }	/* 43252a: push 0x4b1788 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43252f: push edx */
	m->esp -= 4; M32(m->esp) = 0x432532u; native_call(m, m->esi);	/* 432530: call esi */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b50u)));	/* 432532: movsx eax, byte ptr [0x5b1b50] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 432539: mov edx, dword ptr [esp + 0xc] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 43253d: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 432541: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 432543: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 432544: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 432546: push 0 */
	{ DWORD v_ = 0x4b1784u; m->esp -= 4; M32(m->esp) = v_; }	/* 432548: push 0x4b1784 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43254d: push edx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 43254e: mov dword ptr [esp + 0x20], eax */
	m->esp -= 4; M32(m->esp) = 0x432554u; native_call(m, m->esi);	/* 432552: call esi */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b51u)));	/* 432554: movsx eax, byte ptr [0x5b1b51] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 43255b: mov edx, dword ptr [esp + 0xc] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 43255f: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 432563: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 432565: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 432566: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 432568: push 0 */
	{ DWORD v_ = 0x4b1778u; m->esp -= 4; M32(m->esp) = v_; }	/* 43256a: push 0x4b1778 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43256f: push edx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 432570: mov dword ptr [esp + 0x20], eax */
	m->esp -= 4; M32(m->esp) = 0x432576u; native_call(m, m->esi);	/* 432574: call esi */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b53u)));	/* 432576: movsx eax, byte ptr [0x5b1b53] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 43257d: mov edx, dword ptr [esp + 0xc] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 432581: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 432585: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 432587: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 432588: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43258a: push 0 */
	{ DWORD v_ = 0x4b176cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43258c: push 0x4b176c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 432591: push edx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 432592: mov dword ptr [esp + 0x20], eax */
	m->esp -= 4; M32(m->esp) = 0x432598u; native_call(m, m->esi);	/* 432596: call esi */
	m->eax = M32((DWORD)(0x5b1b54u));	/* 432598: mov eax, dword ptr [0x5b1b54] */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 43259d: mov edx, dword ptr [esp + 0xc] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4325a1: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325a5: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4325a7: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325a8: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325aa: push 0 */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4325ac: and eax, 0xff */
	{ DWORD v_ = 0x4b1760u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325b1: push 0x4b1760 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4325b6: push edx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4325b7: mov dword ptr [esp + 0x20], eax */
	m->esp -= 4; M32(m->esp) = 0x4325bdu; native_call(m, m->esi);	/* 4325bb: call esi */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 4325bd: mov edx, dword ptr [esp + 0xc] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4325c1: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325c5: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4325c7: push ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4325c8: xor eax, eax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325ca: push 4 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b55u))) & 0xff) << 0);	/* 4325cc: mov al, byte ptr [0x5b1b55] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325d1: push 0 */
	{ DWORD v_ = 0x4b1754u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325d3: push 0x4b1754 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4325d8: push edx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4325d9: mov dword ptr [esp + 0x20], eax */
	m->esp -= 4; M32(m->esp) = 0x4325dfu; native_call(m, m->esi);	/* 4325dd: call esi */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x5b1b52u)));	/* 4325df: movsx eax, byte ptr [0x5b1b52] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4325e6: lea ecx, [esp + 8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325ea: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4325ec: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325ed: push 4 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4325ef: mov dword ptr [esp + 0x14], eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325f3: push 0 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4325f5: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = 0x4b1748u; m->esp -= 4; M32(m->esp) = v_; }	/* 4325f9: push 0x4b1748 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4325fe: push edx */
	m->esp -= 4; M32(m->esp) = 0x432601u; native_call(m, m->esi);	/* 4325ff: call esi */
L_432601:
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 432601: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 432605: push eax */
	m->esp -= 4; M32(m->esp) = 0x43260cu; native_call(m, M32(0x4a900cu));	/* 432606: call dword ptr [0x4a900c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 43260c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43260d: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43260e: add esp, 8 */
	m->esp += 4 + 0; return;	/* 432611: ret  */
}

/* room_433640 (0x433640), lifted by tools/lift.py */
static void lift_433640(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 433640: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 433641: push edi */
	m->edi = 0x4df9eeu;	/* 433642: mov edi, 0x4df9ee */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433647: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43364a: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43364c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43364e: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 433650: dec ecx */
	m->edi = 0x4df9c8u;	/* 433651: mov edi, 0x4df9c8 */
	m->edx = (m->edx & ~(0xffu << 0)) | ((((!m->zf) ? 1u : 0u) & 0xff) << 0);	/* 433656: setne dl */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433659: or ecx, 0xffffffff */
	M8((DWORD)(0x4df9f6u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 43365c: mov byte ptr [0x4df9f6], dl */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433662: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433664: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433666: sub edi, ecx */
	m->eax = m->ecx;	/* 433668: mov eax, ecx */
	m->esi = m->edi;	/* 43366a: mov esi, edi */
	m->edi = 0x5b1b30u;	/* 43366c: mov edi, 0x5b1b30 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433671: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433674: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 433676: mov ecx, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9e9u))) & 0xff) << 0);	/* 433678: mov al, byte ptr [0x4df9e9] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43367d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433680: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9e8u))) & 0xff) << 0);	/* 433682: mov cl, byte ptr [0x4df9e8] */
	M8((DWORD)(0x5b1b51u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 433688: mov byte ptr [0x5b1b51], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9ebu))) & 0xff) << 0);	/* 43368d: mov al, byte ptr [0x4df9eb] */
	M8((DWORD)(0x5b1b50u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 433692: mov byte ptr [0x5b1b50], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9eau))) & 0xff) << 0);	/* 433698: mov cl, byte ptr [0x4df9ea] */
	M8((DWORD)(0x5b1b53u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 43369e: mov byte ptr [0x5b1b53], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9edu))) & 0xff) << 0);	/* 4336a3: mov al, byte ptr [0x4df9ed] */
	M8((DWORD)(0x5b1b52u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4336a8: mov byte ptr [0x5b1b52], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9ecu))) & 0xff) << 0);	/* 4336ae: mov cl, byte ptr [0x4df9ec] */
	M8((DWORD)(0x5b1b55u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4336b4: mov byte ptr [0x5b1b55], al */
	M8((DWORD)(0x5b1b54u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4336b9: mov byte ptr [0x5b1b54], cl */
	m->edi = 0x4df9eeu;	/* 4336bf: mov edi, 0x4df9ee */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4336c4: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4336c7: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4336c9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4336cb: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4336cd: sub edi, ecx */
	m->eax = m->ecx;	/* 4336cf: mov eax, ecx */
	m->esi = m->edi;	/* 4336d1: mov esi, edi */
	m->edi = 0x5b1b56u;	/* 4336d3: mov edi, 0x5b1b56 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4336d8: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4336db: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4336dd: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4336df: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4336e2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M8((DWORD)(0x5b1b5eu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4336e4: mov byte ptr [0x5b1b5e], dl */
	m->esp -= 4; M32(m->esp) = 0x4336efu; lift_432400(m);	/* 4336ea: call 0x432400 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4336ef: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4336f0: pop esi */
	m->esp += 4 + 0; return;	/* 4336f1: ret  */
}

/* room_43e610 (0x43e610), lifted by tools/lift.py */
static void lift_43e610(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd6c4u));	/* 43e610: mov eax, dword ptr [0x9dd6c4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43e615: push esi */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 43e616: dec eax */
	m->esi = 0x0u;	/* 43e617: mov esi, 0 */
	if (m->zf) goto L_43e62d;	/* 43e61c: je 0x43e62d */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 43e61e: dec eax */
	if (!m->zf) goto L_43e638;	/* 43e61f: jne 0x43e638 */
	M32((DWORD)(0x9dd834u)) = 0x4du;	/* 43e621: mov dword ptr [0x9dd834], 0x4d */
	goto L_43e632;	/* 43e62b: jmp 0x43e632 */
L_43e62d:
	m->esp -= 4; M32(m->esp) = 0x43e632u; native_call(m, 0x434820u);	/* 43e62d: call 0x434820 */
L_43e632:
	M32((DWORD)(0x9dd6c4u)) = m->esi;	/* 43e632: mov dword ptr [0x9dd6c4], esi */
L_43e638:
	{ DWORD a_ = M32((DWORD)(0x9dd6a4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e638: cmp dword ptr [0x9dd6a4], esi */
	if (m->zf) goto L_43e6cf;	/* 43e63e: je 0x43e6cf */
	m->eax = M32((DWORD)(0xa0b37cu));	/* 43e644: mov eax, dword ptr [0xa0b37c] */
	{ DWORD a_ = m->eax, b_ = 0x2au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e649: cmp eax, 0x2a */
	if (!m->cf && !m->zf) goto L_43e6b9;	/* 43e64c: ja 0x43e6b9 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e64e: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x43e6ecu))) & 0xff) << 0);	/* 43e650: mov cl, byte ptr [eax + 0x43e6ec] */
	switch (m->ecx) { case 0: goto L_43e6cf; case 1: goto L_43e689; case 2: goto L_43e65d; case 3: goto L_43e6b9; case 4: goto L_43e6a1; case 5: goto L_43e6b9; default: abort(); }	/* 43e656: jmp dword ptr [ecx*4 + 0x43e6d4] */
L_43e65d:
	M32((DWORD)(0x9dd834u)) = 0x63u;	/* 43e65d: mov dword ptr [0x9dd834], 0x63 */
	M32((DWORD)(0x9dd838u)) = m->esi;	/* 43e667: mov dword ptr [0x9dd838], esi */
	m->esp -= 4; M32(m->esp) = 0x43e672u; native_call(m, 0x432620u);	/* 43e66d: call 0x432620 */
	m->esp -= 4; M32(m->esp) = 0x43e677u; lift_432400(m);	/* 43e672: call 0x432400 */
	M32((DWORD)(0xa0b37cu)) = m->esi;	/* 43e677: mov dword ptr [0xa0b37c], esi */
	M32((DWORD)(0x9dd84cu)) = 0x1u;	/* 43e67d: mov dword ptr [0x9dd84c], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e687: pop esi */
	m->esp += 4 + 0; return;	/* 43e688: ret  */
L_43e689:
	{ DWORD v_ = 0x22u; m->esp -= 4; M32(m->esp) = v_; }	/* 43e689: push 0x22 */
	M32((DWORD)(0x9dd838u)) = m->esi;	/* 43e68b: mov dword ptr [0x9dd838], esi */
	m->esp -= 4; M32(m->esp) = 0x43e696u; native_call(m, 0x41ee40u);	/* 43e691: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e696: add esp, 4 */
	M32((DWORD)(0xa0b37cu)) = m->esi;	/* 43e699: mov dword ptr [0xa0b37c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e69f: pop esi */
	m->esp += 4 + 0; return;	/* 43e6a0: ret  */
L_43e6a1:
	M32((DWORD)(0x9dd838u)) = m->esi;	/* 43e6a1: mov dword ptr [0x9dd838], esi */
	M32((DWORD)(0xa0b37cu)) = m->esi;	/* 43e6a7: mov dword ptr [0xa0b37c], esi */
	M32((DWORD)(0x9dd850u)) = 0x1u;	/* 43e6ad: mov dword ptr [0x9dd850], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e6b7: pop esi */
	m->esp += 4 + 0; return;	/* 43e6b8: ret  */
L_43e6b9:
	{ DWORD v_ = 0x2au; m->esp -= 4; M32(m->esp) = v_; }	/* 43e6b9: push 0x2a */
	M32((DWORD)(0x9dd838u)) = m->esi;	/* 43e6bb: mov dword ptr [0x9dd838], esi */
	m->esp -= 4; M32(m->esp) = 0x43e6c6u; native_call(m, 0x41ee40u);	/* 43e6c1: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e6c6: add esp, 4 */
	M32((DWORD)(0xa0b37cu)) = m->esi;	/* 43e6c9: mov dword ptr [0xa0b37c], esi */
L_43e6cf:
	m->esi = M32(m->esp); m->esp += 4;	/* 43e6cf: pop esi */
	m->esp += 4 + 0; return;	/* 43e6d0: ret  */
}

/* gfx_initGLState (0x42f150), lifted by tools/lift.py */
static void lift_42f150(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42f150: push esi */
	m->esi = M32((DWORD)(0x4a924cu));	/* 42f151: mov esi, dword ptr [0x4a924c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42f157: push edi */
	{ DWORD v_ = 0x1102u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f158: push 0x1102 */
	{ DWORD v_ = 0xc50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f15d: push 0xc50 */
	m->esp -= 4; M32(m->esp) = 0x42f164u; native_call(m, m->esi);	/* 42f162: call esi */
	{ DWORD v_ = 0x46040000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f164: push 0x46040000 */
	{ DWORD v_ = 0x2200u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f169: push 0x2200 */
	{ DWORD v_ = 0x2300u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f16e: push 0x2300 */
	m->esp -= 4; M32(m->esp) = 0x42f179u; native_call(m, M32(0x4a91c8u));	/* 42f173: call dword ptr [0x4a91c8] */
	{ DWORD v_ = 0x303u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f179: push 0x303 */
	{ DWORD v_ = 0x302u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f17e: push 0x302 */
	m->esp -= 4; M32(m->esp) = 0x42f189u; native_call(m, M32(0x4a91ecu));	/* 42f183: call dword ptr [0x4a91ec] */
	{ DWORD v_ = 0x1102u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f189: push 0x1102 */
	{ DWORD v_ = 0xc51u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f18e: push 0xc51 */
	m->esp -= 4; M32(m->esp) = 0x42f195u; native_call(m, m->esi);	/* 42f193: call esi */
	{ DWORD v_ = 0x1102u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f195: push 0x1102 */
	{ DWORD v_ = 0xc52u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f19a: push 0xc52 */
	m->esp -= 4; M32(m->esp) = 0x42f1a1u; native_call(m, m->esi);	/* 42f19f: call esi */
	{ DWORD v_ = 0x203u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1a1: push 0x203 */
	m->esp -= 4; M32(m->esp) = 0x42f1acu; native_call(m, M32(0x4a91ccu));	/* 42f1a6: call dword ptr [0x4a91cc] */
	{ DWORD v_ = 0x1102u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1ac: push 0x1102 */
	{ DWORD v_ = 0xc54u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1b1: push 0xc54 */
	m->esp -= 4; M32(m->esp) = 0x42f1b8u; native_call(m, m->esi);	/* 42f1b6: call esi */
	m->edi = M32((DWORD)(0x4a9224u));	/* 42f1b8: mov edi, dword ptr [0x4a9224] */
	{ DWORD v_ = 0x1d01u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1be: push 0x1d01 */
	m->esp -= 4; M32(m->esp) = 0x42f1c5u; native_call(m, m->edi);	/* 42f1c3: call edi */
	m->esi = M32((DWORD)(0x4a922cu));	/* 42f1c5: mov esi, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1cb: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x42f1d2u; native_call(m, m->esi);	/* 42f1d0: call esi */
	{ DWORD v_ = 0xbe2u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1d2: push 0xbe2 */
	m->esp -= 4; M32(m->esp) = 0x42f1d9u; native_call(m, m->edi);	/* 42f1d7: call edi */
	{ DWORD v_ = 0xb10u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1d9: push 0xb10 */
	m->esp -= 4; M32(m->esp) = 0x42f1e0u; native_call(m, m->esi);	/* 42f1de: call esi */
	{ DWORD v_ = 0xb20u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1e0: push 0xb20 */
	m->esp -= 4; M32(m->esp) = 0x42f1e7u; native_call(m, m->esi);	/* 42f1e5: call esi */
	{ DWORD v_ = 0xb41u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1e7: push 0xb41 */
	m->esp -= 4; M32(m->esp) = 0x42f1eeu; native_call(m, m->esi);	/* 42f1ec: call esi */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1ee: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x42f1f5u; native_call(m, m->edi);	/* 42f1f3: call edi */
	{ DWORD v_ = 0xb50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1f5: push 0xb50 */
	m->esp -= 4; M32(m->esp) = 0x42f1fcu; native_call(m, m->esi);	/* 42f1fa: call esi */
	{ DWORD v_ = 0x4000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f1fc: push 0x4000 */
	m->esp -= 4; M32(m->esp) = 0x42f203u; native_call(m, m->esi);	/* 42f201: call esi */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f203: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x42f20au; native_call(m, m->esi);	/* 42f208: call esi */
	{ DWORD v_ = 0x1b02u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f20a: push 0x1b02 */
	{ DWORD v_ = 0x408u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f20f: push 0x408 */
	m->esp -= 4; M32(m->esp) = 0x42f21au; native_call(m, M32(0x4a91c4u));	/* 42f214: call dword ptr [0x4a91c4] */
	{ DWORD v_ = 0x901u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f21a: push 0x901 */
	m->esp -= 4; M32(m->esp) = 0x42f225u; native_call(m, M32(0x4a91c0u));	/* 42f21f: call dword ptr [0x4a91c0] */
	{ DWORD v_ = 0x405u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f225: push 0x405 */
	m->esp -= 4; M32(m->esp) = 0x42f230u; native_call(m, M32(0x4a91d0u));	/* 42f22a: call dword ptr [0x4a91d0] */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f230: push 0xb44 */
	m->esp -= 4; M32(m->esp) = 0x42f237u; native_call(m, m->esi);	/* 42f235: call esi */
	m->esi = M32((DWORD)(0x4a91fcu));	/* 42f237: mov esi, dword ptr [0x4a91fc] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f23d: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x42f244u; native_call(m, m->esi);	/* 42f242: call esi */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 42f244: fild dword ptr [esp + 0xc] */
	{ DWORD v_ = 0x40d38800u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f248: push 0x40d38800 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f24d: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f24f: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f254: push 0 */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x20u));	/* 42f256: fidiv dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42f25a: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42f25d: sub esp, 8 */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 42f260: fstp dword ptr [0x4e1870] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 42f266: fld dword ptr [0x4e1870] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 42f26c: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 42f270: fld dword ptr [0x68038c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 42f276: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x42f27eu; native_call(m, 0x4509c6u);	/* 42f279: call 0x4509c6 */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 42f27e: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x42f285u; native_call(m, m->esi);	/* 42f283: call esi */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 42f285: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 42f289: mov ecx, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42f28d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42f28e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42f294u; native_call(m, 0x42f0f0u);	/* 42f28f: call 0x42f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42f294: add esp, 8 */
	M32((DWORD)(0x5ae9bcu)) = 0x1u;	/* 42f297: mov dword ptr [0x5ae9bc], 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42f2a1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42f2a2: pop esi */
	m->esp += 4 + 0; return;	/* 42f2a3: ret  */
}

/* tex_upload (0x456520), lifted by tools/lift.py */
static void lift_456520(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 456520: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456521: push esi */
	m->ebx = 0x1u;	/* 456522: mov ebx, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456527: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 456528: push ebx */
	m->esi = m->ecx;	/* 456529: mov esi, ecx */
	{ DWORD v_ = 0xcf5u; m->esp -= 4; M32(m->esp) = v_; }	/* 45652b: push 0xcf5 */
	m->esp -= 4; M32(m->esp) = 0x456536u; native_call(m, M32(0x4a9268u));	/* 456530: call dword ptr [0x4a9268] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 456536: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45653a: push eax */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45653b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x456546u; native_call(m, M32(0x4a9264u));	/* 456540: call dword ptr [0x4a9264] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x14u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456546: cmp dword ptr [esp + 0x14], ebx */
	if (!m->zf) goto L_45656a;	/* 45654a: jne 0x45656a */
	m->edi = M32((DWORD)(0x4a9260u));	/* 45654c: mov edi, dword ptr [0x4a9260] */
	{ DWORD v_ = 0x46240400u; m->esp -= 4; M32(m->esp) = v_; }	/* 456552: push 0x46240400 */
	{ DWORD v_ = 0x2802u; m->esp -= 4; M32(m->esp) = v_; }	/* 456557: push 0x2802 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45655c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x456563u; native_call(m, m->edi);	/* 456561: call edi */
	{ DWORD v_ = 0x46240400u; m->esp -= 4; M32(m->esp) = v_; }	/* 456563: push 0x46240400 */
	goto L_456586;	/* 456568: jmp 0x456586 */
L_45656a:
	m->edi = M32((DWORD)(0x4a9260u));	/* 45656a: mov edi, dword ptr [0x4a9260] */
	{ DWORD v_ = 0x46240000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456570: push 0x46240000 */
	{ DWORD v_ = 0x2802u; m->esp -= 4; M32(m->esp) = v_; }	/* 456575: push 0x2802 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45657a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x456581u; native_call(m, m->edi);	/* 45657f: call edi */
	{ DWORD v_ = 0x46240000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456581: push 0x46240000 */
L_456586:
	{ DWORD v_ = 0x2803u; m->esp -= 4; M32(m->esp) = v_; }	/* 456586: push 0x2803 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45658b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x456592u; native_call(m, m->edi);	/* 456590: call edi */
	m->eax = M32((DWORD)(m->esi + 0xc0120u));	/* 456592: mov eax, dword ptr [esi + 0xc0120] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456598: cmp eax, ebx */
	m->eax = M32((DWORD)(m->esi + 0xc0124u));	/* 45659a: mov eax, dword ptr [esi + 0xc0124] */
	if (!m->zf) goto L_45663f;	/* 4565a0: jne 0x45663f */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4565a6: cmp eax, ebx */
	if (!m->zf) goto L_4565c2;	/* 4565a8: jne 0x4565c2 */
	{ DWORD v_ = 0x46180400u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565aa: push 0x46180400 */
	{ DWORD v_ = 0x2800u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565af: push 0x2800 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565b4: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4565bbu; native_call(m, m->edi);	/* 4565b9: call edi */
	{ DWORD v_ = 0x461c0c00u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565bb: push 0x461c0c00 */
	goto L_4565d8;	/* 4565c0: jmp 0x4565d8 */
L_4565c2:
	{ DWORD v_ = 0x46180000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565c2: push 0x46180000 */
	{ DWORD v_ = 0x2800u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565c7: push 0x2800 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565cc: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4565d3u; native_call(m, m->edi);	/* 4565d1: call edi */
	{ DWORD v_ = 0x461c0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565d3: push 0x461c0000 */
L_4565d8:
	{ DWORD v_ = 0x2801u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565d8: push 0x2801 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565dd: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4565e4u; native_call(m, m->edi);	/* 4565e2: call edi */
	m->ecx = M32((DWORD)(m->esi + 0xc011cu));	/* 4565e4: mov ecx, dword ptr [esi + 0xc011c] */
	m->edx = M32((DWORD)(m->esi + 0xc0118u));	/* 4565ea: mov edx, dword ptr [esi + 0xc0118] */
	m->edi = (DWORD)(m->esi + 0x114u);	/* 4565f0: lea edi, [esi + 0x114] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4565f6: push edi */
	{ DWORD v_ = 0x1401u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565f7: push 0x1401 */
	{ DWORD v_ = 0x1908u; m->esp -= 4; M32(m->esp) = v_; }	/* 4565fc: push 0x1908 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 456601: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456603: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456604: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 456605: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 456607: push 0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 456609: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x456614u; native_call(m, M32(0x4a91e4u));	/* 45660e: call dword ptr [0x4a91e4] */
	m->eax = M32((DWORD)(m->esi + 0xc011cu));	/* 456614: mov eax, dword ptr [esi + 0xc011c] */
	m->ecx = M32((DWORD)(m->esi + 0xc0118u));	/* 45661a: mov ecx, dword ptr [esi + 0xc0118] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456620: push edi */
	{ DWORD v_ = 0x1401u; m->esp -= 4; M32(m->esp) = v_; }	/* 456621: push 0x1401 */
	{ DWORD v_ = 0x1908u; m->esp -= 4; M32(m->esp) = v_; }	/* 456626: push 0x1908 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45662b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45662c: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45662d: push 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45662f: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x456639u; native_call(m, 0x4a82ecu);	/* 456634: call 0x4a82ec */
	m->edi = M32(m->esp); m->esp += 4;	/* 456639: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45663a: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45663b: pop ebx */
	m->esp += 4 + 8; return;	/* 45663c: ret 8 */
L_45663f:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45663f: cmp eax, ebx */
	if (!m->zf) goto L_45665b;	/* 456641: jne 0x45665b */
	{ DWORD v_ = 0x46180400u; m->esp -= 4; M32(m->esp) = v_; }	/* 456643: push 0x46180400 */
	{ DWORD v_ = 0x2800u; m->esp -= 4; M32(m->esp) = v_; }	/* 456648: push 0x2800 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45664d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x456654u; native_call(m, m->edi);	/* 456652: call edi */
	{ DWORD v_ = 0x46180400u; m->esp -= 4; M32(m->esp) = v_; }	/* 456654: push 0x46180400 */
	goto L_456671;	/* 456659: jmp 0x456671 */
L_45665b:
	{ DWORD v_ = 0x46180000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45665b: push 0x46180000 */
	{ DWORD v_ = 0x2800u; m->esp -= 4; M32(m->esp) = v_; }	/* 456660: push 0x2800 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 456665: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x45666cu; native_call(m, m->edi);	/* 45666a: call edi */
	{ DWORD v_ = 0x46180000u; m->esp -= 4; M32(m->esp) = v_; }	/* 45666c: push 0x46180000 */
L_456671:
	{ DWORD v_ = 0x2801u; m->esp -= 4; M32(m->esp) = v_; }	/* 456671: push 0x2801 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 456676: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x45667du; native_call(m, m->edi);	/* 45667b: call edi */
	m->eax = M32((DWORD)(m->esi + 0xc011cu));	/* 45667d: mov eax, dword ptr [esi + 0xc011c] */
	m->ecx = M32((DWORD)(m->esi + 0xc0118u));	/* 456683: mov ecx, dword ptr [esi + 0xc0118] */
	m->edx = (DWORD)(m->esi + 0x114u);	/* 456689: lea edx, [esi + 0x114] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45668f: push edx */
	{ DWORD v_ = 0x1401u; m->esp -= 4; M32(m->esp) = v_; }	/* 456690: push 0x1401 */
	{ DWORD v_ = 0x1908u; m->esp -= 4; M32(m->esp) = v_; }	/* 456695: push 0x1908 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45669a: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45669c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45669d: push ecx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 45669e: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4566a0: push 0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4566a2: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4566adu; native_call(m, M32(0x4a91e4u));	/* 4566a7: call dword ptr [0x4a91e4] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4566ad: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4566ae: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4566af: pop ebx */
	m->esp += 4 + 8; return;	/* 4566b0: ret 8 */
}

/* tex_upload2 (0x473610), lifted by tools/lift.py */
static void lift_473610(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473610: sub esp, 0xc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473613: push ebx */
	m->ebx = m->ecx;	/* 473614: mov ebx, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 473616: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 473617: push esi */
	m->esi = (DWORD)(m->ebx + 0x15a952au);	/* 473618: lea esi, [ebx + 0x15a952a] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47361e: push edi */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 47361f: mov dword ptr [esp + 0x10], ebx */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 473623: mov dword ptr [esp + 0x18], 0 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 47362b: xor edi, edi */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 47362d: mov dword ptr [esp + 0x14], esi */
	m->eax = 0x1u;	/* 473631: mov eax, 1 */
L_473636:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x608u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 473636: cmp dword ptr [esi + 0x608], eax */
	if (!m->zf) goto L_4736c4;	/* 47363c: jne 0x4736c4 */
	m->eax = m->edi;	/* 473642: mov eax, edi */
	m->ecx = m->edi;	/* 473644: mov ecx, edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 473646: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 473647: and edx, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47364a: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47364c: sar eax, 2 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47364f: shl eax, 4 */
	{ DWORD a_ = m->ecx, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 473652: and ecx, 0x80000003 */
	if (!m->sf) goto L_47365f;	/* 473658: jns 0x47365f */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 47365a: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47365b: or ecx, 0xfffffffc */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 47365e: inc ecx */
L_47365f:
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 47365f: lea ecx, [ecx + ecx*2] */
	m->edx = m->esi;	/* 473662: mov edx, esi */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 473664: shl ecx, 3 */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473667: shl eax, 7 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47366a: add eax, ecx */
	m->esi = (DWORD)(m->ebx + m->eax*4 + 0x20fcfe4u);	/* 47366c: lea esi, [ebx + eax*4 + 0x20fcfe4] */
	m->ebx = 0x10u;	/* 473673: mov ebx, 0x10 */
L_473678:
	m->eax = m->edx;	/* 473678: mov eax, edx */
	m->ecx = m->esi;	/* 47367a: mov ecx, esi */
	m->edx = 0x18u;	/* 47367c: mov edx, 0x18 */
L_473681:
	m->ebp = M32((DWORD)(m->eax + 0x0u));	/* 473681: mov ebp, dword ptr [eax] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473683: add eax, 4 */
	M32((DWORD)(m->ecx + 0x0u)) = m->ebp;	/* 473686: mov dword ptr [ecx], ebp */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 473688: add ecx, 4 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 47368b: dec edx */
	if (!m->zf) goto L_473681;	/* 47368c: jne 0x473681 */
	{ DWORD a_ = m->esi, b_ = 0x200u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 47368e: add esi, 0x200 */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 473694: dec ebx */
	m->edx = m->eax;	/* 473695: mov edx, eax */
	if (!m->zf) goto L_473678;	/* 473697: jne 0x473678 */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 473699: mov esi, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esi + 0x604u));	/* 47369d: mov eax, dword ptr [esi + 0x604] */
	M32((DWORD)(m->esi + 0x608u)) = 0x0u;	/* 4736a3: mov dword ptr [esi + 0x608], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4736ad: test eax, eax */
	m->eax = 0x1u;	/* 4736af: mov eax, 1 */
	if (!m->zf) goto L_4736c0;	/* 4736b4: jne 0x4736c0 */
	M32((DWORD)(m->esi + 0x604u)) = m->eax;	/* 4736b6: mov dword ptr [esi + 0x604], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4736bc: mov dword ptr [esp + 0x18], eax */
L_4736c0:
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 4736c0: mov ebx, dword ptr [esp + 0x10] */
L_4736c4:
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 4736c4: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x47fd2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4736c5: add esi, 0x47fd2 */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4736cb: cmp edi, 0x10 */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 4736ce: mov dword ptr [esp + 0x14], esi */
	if (m->sf != m->of) goto L_473636;	/* 4736d2: jl 0x473636 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4736d8: cmp dword ptr [esp + 0x18], eax */
	if (!m->zf) goto L_473773;	/* 4736dc: jne 0x473773 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4736e2: push eax */
	{ DWORD v_ = 0xcf5u; m->esp -= 4; M32(m->esp) = v_; }	/* 4736e3: push 0xcf5 */
	m->esp -= 4; M32(m->esp) = 0x4736eeu; native_call(m, M32(0x4a9268u));	/* 4736e8: call dword ptr [0x4a9268] */
	m->eax = M32((DWORD)(m->ebx + 0x20fcfe0u));	/* 4736ee: mov eax, dword ptr [ebx + 0x20fcfe0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4736f4: push eax */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4736f5: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x473700u; native_call(m, M32(0x4a9264u));	/* 4736fa: call dword ptr [0x4a9264] */
	m->esi = M32((DWORD)(0x4a9260u));	/* 473700: mov esi, dword ptr [0x4a9260] */
	{ DWORD v_ = 0x46240000u; m->esp -= 4; M32(m->esp) = v_; }	/* 473706: push 0x46240000 */
	{ DWORD v_ = 0x2802u; m->esp -= 4; M32(m->esp) = v_; }	/* 47370b: push 0x2802 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 473710: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x473717u; native_call(m, m->esi);	/* 473715: call esi */
	{ DWORD v_ = 0x46240000u; m->esp -= 4; M32(m->esp) = v_; }	/* 473717: push 0x46240000 */
	{ DWORD v_ = 0x2803u; m->esp -= 4; M32(m->esp) = v_; }	/* 47371c: push 0x2803 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 473721: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x473728u; native_call(m, m->esi);	/* 473726: call esi */
	{ DWORD v_ = 0x46180400u; m->esp -= 4; M32(m->esp) = v_; }	/* 473728: push 0x46180400 */
	{ DWORD v_ = 0x2800u; m->esp -= 4; M32(m->esp) = v_; }	/* 47372d: push 0x2800 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 473732: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x473739u; native_call(m, m->esi);	/* 473737: call esi */
	{ DWORD v_ = 0x46180400u; m->esp -= 4; M32(m->esp) = v_; }	/* 473739: push 0x46180400 */
	{ DWORD v_ = 0x2801u; m->esp -= 4; M32(m->esp) = v_; }	/* 47373e: push 0x2801 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 473743: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x47374au; native_call(m, m->esi);	/* 473748: call esi */
	{ DWORD a_ = m->ebx, b_ = 0x20fcfe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 47374a: add ebx, 0x20fcfe4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 473750: push ebx */
	{ DWORD v_ = 0x1401u; m->esp -= 4; M32(m->esp) = v_; }	/* 473751: push 0x1401 */
	{ DWORD v_ = 0x1908u; m->esp -= 4; M32(m->esp) = v_; }	/* 473756: push 0x1908 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47375b: push 0 */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 47375d: push 0x40 */
	{ DWORD v_ = 0x80u; m->esp -= 4; M32(m->esp) = v_; }	/* 47375f: push 0x80 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 473764: push 4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 473766: push 0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 473768: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x473773u; native_call(m, M32(0x4a91e4u));	/* 47376d: call dword ptr [0x4a91e4] */
L_473773:
	m->edi = M32(m->esp); m->esp += 4;	/* 473773: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 473774: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 473775: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 473776: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 473777: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 47377a: ret  */
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
