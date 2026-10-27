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

static void lift_402620(X86 *m);
static void lift_4028b0(X86 *m);
static void lift_402c90(X86 *m);
static void lift_402740(X86 *m);
static void lift_4029d0(X86 *m);
static void lift_403210(X86 *m);
static void lift_402db0(X86 *m);
static void lift_429bc0(X86 *m);
static void lift_403170(X86 *m);

/* text_draw5 (0x403170), lifted by tools/lift.py */
static void lift_403170(X86 *m)
{
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 403170: push 2 */
	M32((DWORD)(0x4d23d8u)) = 0x6u;	/* 403172: mov dword ptr [0x4d23d8], 6 */
	m->esp -= 4; M32(m->esp) = 0x403181u; native_call(m, 0x41ef90u);	/* 40317c: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403181: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403184: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40318fu; native_call(m, M32(0x4a9224u));	/* 403189: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d444u));	/* 40318f: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 403194: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 40319a: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4031a0: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 4031a1: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4031a6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4031a7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4031a8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4031afu; native_call(m, M32(0x4a9228u));	/* 4031a9: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x76d448u));	/* 4031af: mov eax, dword ptr [0x76d448] */
	m->ecx = m->eax;	/* 4031b4: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4031b6: and ecx, 0x800001ff */
	if (!m->sf) goto L_4031c6;	/* 4031bc: jns 0x4031c6 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4031be: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4031bf: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4031c5: inc ecx */
L_4031c6:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4031c6: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4031c7: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4031cd: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4031ce: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4031d0: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4031d6: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4031d9: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4031e2u; native_call(m, 0x4566c0u);	/* 4031dd: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 4031e2: mov eax, dword ptr [esp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 4031e6: mov ecx, dword ptr [esp + 8] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 4031ea: mov edx, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4031ee: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4031ef: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4031f0: push edx */
	m->esp -= 4; M32(m->esp) = 0x4031f6u; native_call(m, 0x4031f6u + M32(0x4031f2u));	/* 0x403060 unless the patch DLL retargets it */	/* 4031f1: call 0x403060 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4031f6: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4031f9: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x403204u; native_call(m, M32(0x4a922cu));	/* 4031fe: call dword ptr [0x4a922c] */
	m->esp += 4 + 0; return;	/* 403204: ret  */
}

/* text_draw8 (0x402620), lifted by tools/lift.py */
static void lift_402620(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402620: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402621: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402622: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 402623: push 2 */
	M32((DWORD)(0x4d23d8u)) = 0x8u;	/* 402625: mov dword ptr [0x4d23d8], 8 */
	m->esp -= 4; M32(m->esp) = 0x402634u; native_call(m, 0x41ef90u);	/* 40262f: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402634: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402637: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402642u; native_call(m, M32(0x4a9224u));	/* 40263c: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d444u));	/* 402642: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 402647: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 40264d: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402653: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 402654: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402659: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40265a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40265b: push eax */
	m->esp -= 4; M32(m->esp) = 0x402662u; native_call(m, M32(0x4a9228u));	/* 40265c: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9dae1cu));	/* 402662: mov eax, dword ptr [0x9dae1c] */
	m->ecx = m->eax;	/* 402667: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402669: and ecx, 0x800001ff */
	if (!m->sf) goto L_402679;	/* 40266f: jns 0x402679 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402671: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402672: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402678: inc ecx */
L_402679:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402679: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40267a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402680: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402681: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402683: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402689: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40268c: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402695u; native_call(m, 0x4566c0u);	/* 402690: call 0x4566c0 */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 402695: mov esi, dword ptr [esp + 0x18] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 402699: mov edi, dword ptr [esp + 0x14] */
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 40269d: mov ebx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4026a1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4026a2: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4026a3: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4026a9u; native_call(m, 0x401870u);	/* 4026a4: call 0x401870 */
	m->eax = M32((DWORD)(0x76d360u));	/* 4026a9: mov eax, dword ptr [0x76d360] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4026ae: add esp, 0xc */
	m->ecx = m->eax;	/* 4026b1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4026b3: and ecx, 0x800001ff */
	if (!m->sf) goto L_4026c3;	/* 4026b9: jns 0x4026c3 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4026bb: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4026bc: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4026c2: inc ecx */
L_4026c3:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4026c3: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4026c4: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4026ca: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4026cb: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4026cd: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4026d3: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4026d6: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4026dfu; native_call(m, 0x4566c0u);	/* 4026da: call 0x4566c0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4026df: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4026e0: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4026e1: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4026e7u; native_call(m, 0x401aa0u);	/* 4026e2: call 0x401aa0 */
	m->eax = M32((DWORD)(0x76d448u));	/* 4026e7: mov eax, dword ptr [0x76d448] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4026ec: add esp, 0xc */
	m->ecx = m->eax;	/* 4026ef: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4026f1: and ecx, 0x800001ff */
	if (!m->sf) goto L_402701;	/* 4026f7: jns 0x402701 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4026f9: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4026fa: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402700: inc ecx */
L_402701:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402701: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402702: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402708: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402709: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40270b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402711: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402714: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40271du; native_call(m, 0x4566c0u);	/* 402718: call 0x4566c0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40271d: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40271e: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40271f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x402725u; native_call(m, 0x402725u + M32(0x402721u));	/* 0x402010 unless the patch DLL retargets it */	/* 402720: call 0x402010 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402725: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402728: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402733u; native_call(m, M32(0x4a922cu));	/* 40272d: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 402733: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 402734: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 402735: pop ebx */
	m->esp += 4 + 0; return;	/* 402736: ret  */
}

/* text_draw16 (0x4028b0), lifted by tools/lift.py */
static void lift_4028b0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4028b0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4028b1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4028b2: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4028b3: push 2 */
	M32((DWORD)(0x4d23d8u)) = 0xdu;	/* 4028b5: mov dword ptr [0x4d23d8], 0xd */
	m->esp -= 4; M32(m->esp) = 0x4028c4u; native_call(m, 0x41ef90u);	/* 4028bf: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4028c4: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4028c7: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4028d2u; native_call(m, M32(0x4a9224u));	/* 4028cc: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d444u));	/* 4028d2: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 4028d7: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 4028dd: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4028e3: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 4028e4: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4028e9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4028ea: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4028eb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4028f2u; native_call(m, M32(0x4a9228u));	/* 4028ec: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9dae1cu));	/* 4028f2: mov eax, dword ptr [0x9dae1c] */
	m->ecx = m->eax;	/* 4028f7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4028f9: and ecx, 0x800001ff */
	if (!m->sf) goto L_402909;	/* 4028ff: jns 0x402909 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402901: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402902: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402908: inc ecx */
L_402909:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402909: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40290a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402910: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402911: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402913: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402919: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40291c: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402925u; native_call(m, 0x4566c0u);	/* 402920: call 0x4566c0 */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 402925: mov esi, dword ptr [esp + 0x18] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 402929: mov edi, dword ptr [esp + 0x14] */
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 40292d: mov ebx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402931: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402932: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402933: push ebx */
	m->esp -= 4; M32(m->esp) = 0x402939u; native_call(m, 0x401870u);	/* 402934: call 0x401870 */
	m->eax = M32((DWORD)(0x76d360u));	/* 402939: mov eax, dword ptr [0x76d360] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40293e: add esp, 0xc */
	m->ecx = m->eax;	/* 402941: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402943: and ecx, 0x800001ff */
	if (!m->sf) goto L_402953;	/* 402949: jns 0x402953 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40294b: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40294c: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402952: inc ecx */
L_402953:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402953: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402954: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40295a: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40295b: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40295d: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402963: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402966: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40296fu; native_call(m, 0x4566c0u);	/* 40296a: call 0x4566c0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40296f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402970: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402971: push ebx */
	m->esp -= 4; M32(m->esp) = 0x402977u; native_call(m, 0x401aa0u);	/* 402972: call 0x401aa0 */
	m->eax = M32((DWORD)(0x9dad90u));	/* 402977: mov eax, dword ptr [0x9dad90] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40297c: add esp, 0xc */
	m->ecx = m->eax;	/* 40297f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402981: and ecx, 0x800001ff */
	if (!m->sf) goto L_402991;	/* 402987: jns 0x402991 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402989: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40298a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402990: inc ecx */
L_402991:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402991: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402992: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402998: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402999: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40299b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4029a1: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4029a4: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4029adu; native_call(m, 0x4566c0u);	/* 4029a8: call 0x4566c0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4029ad: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4029ae: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4029af: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4029b5u; native_call(m, 0x4029b5u + M32(0x4029b1u));	/* 0x402210 unless the patch DLL retargets it */	/* 4029b0: call 0x402210 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4029b5: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4029b8: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4029c3u; native_call(m, M32(0x4a922cu));	/* 4029bd: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4029c3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4029c4: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4029c5: pop ebx */
	m->esp += 4 + 0; return;	/* 4029c6: ret  */
}

/* text_draw32 (0x402c90), lifted by tools/lift.py */
static void lift_402c90(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402c90: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402c91: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402c92: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 402c93: push 2 */
	M32((DWORD)(0x4d23d8u)) = 0x1au;	/* 402c95: mov dword ptr [0x4d23d8], 0x1a */
	m->esp -= 4; M32(m->esp) = 0x402ca4u; native_call(m, 0x41ef90u);	/* 402c9f: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402ca4: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402ca7: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402cb2u; native_call(m, M32(0x4a9224u));	/* 402cac: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d444u));	/* 402cb2: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 402cb7: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 402cbd: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402cc3: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 402cc4: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402cc9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402cca: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402ccb: push eax */
	m->esp -= 4; M32(m->esp) = 0x402cd2u; native_call(m, M32(0x4a9228u));	/* 402ccc: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9dae1cu));	/* 402cd2: mov eax, dword ptr [0x9dae1c] */
	m->ecx = m->eax;	/* 402cd7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402cd9: and ecx, 0x800001ff */
	if (!m->sf) goto L_402ce9;	/* 402cdf: jns 0x402ce9 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402ce1: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402ce2: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402ce8: inc ecx */
L_402ce9:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402ce9: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402cea: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402cf0: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402cf1: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402cf3: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402cf9: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402cfc: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402d05u; native_call(m, 0x4566c0u);	/* 402d00: call 0x4566c0 */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 402d05: mov esi, dword ptr [esp + 0x18] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 402d09: mov edi, dword ptr [esp + 0x14] */
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 402d0d: mov ebx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402d11: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402d12: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402d13: push ebx */
	m->esp -= 4; M32(m->esp) = 0x402d19u; native_call(m, 0x401ce0u);	/* 402d14: call 0x401ce0 */
	m->eax = M32((DWORD)(0x76d360u));	/* 402d19: mov eax, dword ptr [0x76d360] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402d1e: add esp, 0xc */
	m->ecx = m->eax;	/* 402d21: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402d23: and ecx, 0x800001ff */
	if (!m->sf) goto L_402d33;	/* 402d29: jns 0x402d33 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402d2b: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402d2c: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402d32: inc ecx */
L_402d33:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402d33: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402d34: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402d3a: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402d3b: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402d3d: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402d43: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402d46: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402d4fu; native_call(m, 0x4566c0u);	/* 402d4a: call 0x4566c0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402d4f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402d50: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402d51: push ebx */
	m->esp -= 4; M32(m->esp) = 0x402d57u; native_call(m, 0x401e70u);	/* 402d52: call 0x401e70 */
	m->eax = M32((DWORD)(0x9dad90u));	/* 402d57: mov eax, dword ptr [0x9dad90] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402d5c: add esp, 0xc */
	m->ecx = m->eax;	/* 402d5f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402d61: and ecx, 0x800001ff */
	if (!m->sf) goto L_402d71;	/* 402d67: jns 0x402d71 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402d69: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402d6a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402d70: inc ecx */
L_402d71:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402d71: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402d72: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402d78: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402d79: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402d7b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402d81: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402d84: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402d8du; native_call(m, 0x4566c0u);	/* 402d88: call 0x4566c0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402d8d: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402d8e: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402d8f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x402d95u; native_call(m, 0x402d95u + M32(0x402d91u));	/* 0x402420 unless the patch DLL retargets it */	/* 402d90: call 0x402420 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402d95: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402d98: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402da3u; native_call(m, M32(0x4a922cu));	/* 402d9d: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 402da3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 402da4: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 402da5: pop ebx */
	m->esp += 4 + 0; return;	/* 402da6: ret  */
}

/* text_draw8b (0x402740), lifted by tools/lift.py */
static void lift_402740(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 402740: mov eax, dword ptr [esp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 402744: mov ecx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402748: sub eax, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40274a: push ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40274b: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40274c: sub eax, edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40274e: push esi */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 40274f: mov esi, dword ptr [esp + 0x18] */
	m->edx = m->eax;	/* 402753: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 402755: sar edx, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402757: push edi */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 402758: add edx, ecx */
	m->edi = m->esi;	/* 40275a: mov edi, esi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40275c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40275f: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 402761: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 402763: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402765: dec ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 402766: xor edi, edi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 402768: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_40278e;	/* 40276a: jle 0x40278e */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x5du) & 0xff) << 0);	/* 40276c: mov bl, 0x5d */
L_40276e:
	{ DWORD a_ = M8((DWORD)(m->eax + m->esi*1 + 0x0u)), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40276e: cmp byte ptr [eax + esi], 0x24 */
	if (!m->zf) goto L_402789;	/* 402772: jne 0x402789 */
	{ DWORD a_ = M8((DWORD)(m->eax + m->esi*1 + 0x1u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402774: cmp byte ptr [eax + esi + 1], 0x5b */
	if (!m->zf) goto L_402789;	/* 402779: jne 0x402789 */
	{ DWORD a_ = M8((DWORD)(m->eax + m->esi*1 + 0x3u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40277b: cmp byte ptr [eax + esi + 3], bl */
	if (!m->zf) goto L_402789;	/* 40277f: jne 0x402789 */
	{ DWORD a_ = M8((DWORD)(m->eax + m->esi*1 + 0x5u)), b_ = 0x0u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402781: cmp byte ptr [eax + esi + 5], 0 */
	if (m->zf) goto L_402789;	/* 402786: je 0x402789 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 402788: inc edi */
L_402789:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 402789: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40278a: cmp eax, ecx */
	if (m->sf != m->of) goto L_40276e;	/* 40278c: jl 0x40276e */
L_40278e:
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 40278e: lea eax, [edi + edi*4] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 402791: push 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402793: sub eax, ecx */
	M32((DWORD)(0x4d23d8u)) = 0x8u;	/* 402795: mov dword ptr [0x4d23d8], 8 */
	m->edi = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 40279f: lea edi, [edx + eax*4] */
	m->esp -= 4; M32(m->esp) = 0x4027a7u; native_call(m, 0x41ef90u);	/* 4027a2: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4027a7: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4027aa: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4027b5u; native_call(m, M32(0x4a9224u));	/* 4027af: call dword ptr [0x4a9224] */
	m->ecx = M32((DWORD)(0x76d444u));	/* 4027b5: mov ecx, dword ptr [0x76d444] */
	m->edx = M32((DWORD)(0x76d440u));	/* 4027bb: mov edx, dword ptr [0x76d440] */
	m->eax = M32((DWORD)(0x76d43cu));	/* 4027c1: mov eax, dword ptr [0x76d43c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4027c6: push ecx */
	m->ecx = M32((DWORD)(0x76d438u));	/* 4027c7: mov ecx, dword ptr [0x76d438] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4027cd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4027ce: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4027cf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4027d6u; native_call(m, M32(0x4a9228u));	/* 4027d0: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9dae1cu));	/* 4027d6: mov eax, dword ptr [0x9dae1c] */
	m->edx = m->eax;	/* 4027db: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4027dd: and edx, 0x800001ff */
	if (!m->sf) goto L_4027ed;	/* 4027e3: jns 0x4027ed */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4027e5: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4027e6: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4027ec: inc edx */
L_4027ed:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4027ed: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4027ee: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4027f4: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4027f5: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4027fb: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4027fd: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 402800: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402809u; native_call(m, 0x4566c0u);	/* 402804: call 0x4566c0 */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 402809: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40280d: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40280e: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40280f: push edi */
	m->esp -= 4; M32(m->esp) = 0x402815u; native_call(m, 0x401870u);	/* 402810: call 0x401870 */
	m->eax = M32((DWORD)(0x76d360u));	/* 402815: mov eax, dword ptr [0x76d360] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40281a: add esp, 0xc */
	m->edx = m->eax;	/* 40281d: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40281f: and edx, 0x800001ff */
	if (!m->sf) goto L_40282f;	/* 402825: jns 0x40282f */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 402827: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402828: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 40282e: inc edx */
L_40282f:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40282f: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 402830: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402836: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402837: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40283d: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40283f: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 402842: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40284bu; native_call(m, 0x4566c0u);	/* 402846: call 0x4566c0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40284b: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40284c: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40284d: push edi */
	m->esp -= 4; M32(m->esp) = 0x402853u; native_call(m, 0x401aa0u);	/* 40284e: call 0x401aa0 */
	m->eax = M32((DWORD)(0x76d448u));	/* 402853: mov eax, dword ptr [0x76d448] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402858: add esp, 0xc */
	m->edx = m->eax;	/* 40285b: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40285d: and edx, 0x800001ff */
	if (!m->sf) goto L_40286d;	/* 402863: jns 0x40286d */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 402865: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402866: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 40286c: inc edx */
L_40286d:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40286d: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 40286e: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402874: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402875: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40287b: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40287d: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 402880: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402889u; native_call(m, 0x4566c0u);	/* 402884: call 0x4566c0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402889: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40288a: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40288b: push edi */
	m->esp -= 4; M32(m->esp) = 0x402891u; native_call(m, 0x402891u + M32(0x40288du));	/* 0x402010 unless the patch DLL retargets it */	/* 40288c: call 0x402010 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402891: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402894: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40289fu; native_call(m, M32(0x4a922cu));	/* 402899: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 40289f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4028a0: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4028a1: pop ebx */
	m->esp += 4 + 0; return;	/* 4028a2: ret  */
}

/* text_drawBox16 (0x4029d0), lifted by tools/lift.py */
static void lift_4029d0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x130u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4029d0: sub esp, 0x130 */
	m->ecx = 0x19u;	/* 4029d6: mov ecx, 0x19 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4029db: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x68u);	/* 4029dd: lea edx, [esp + 0x68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4029e1: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4029e2: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4029e3: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4029e4: push edi */
	m->edi = (DWORD)(m->esp + 0x78u);	/* 4029e5: lea edi, [esp + 0x78] */
	m->ebp = M32((DWORD)(m->esp + 0x148u));	/* 4029e9: mov ebp, dword ptr [esp + 0x148] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4029f0: rep stosd dword ptr es:[edi], eax */
	m->edi = M32((DWORD)(m->esp + 0x150u));	/* 4029f2: mov edi, dword ptr [esp + 0x150] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4029f9: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4029fc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4029fe: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 402a00: sub edi, ecx */
	m->eax = m->ecx;	/* 402a02: mov eax, ecx */
	m->esi = m->edi;	/* 402a04: mov esi, edi */
	m->edi = m->edx;	/* 402a06: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 402a08: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 402a0b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 402a0d: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402a0f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 402a12: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_402a14:
	m->edi = (DWORD)(m->esp + 0x78u);	/* 402a14: lea edi, [esp + 0x78] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402a18: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 402a1b: xor eax, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 402a1d: xor esi, esi */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 402a1f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 402a21: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402a23: dec ecx */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 402a24: lea edi, [esp + 0x14] */
	m->ebx = m->ecx;	/* 402a28: mov ebx, ecx */
	m->ecx = 0x19u;	/* 402a2a: mov ecx, 0x19 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 402a2f: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x19u;	/* 402a31: mov ecx, 0x19 */
	m->edi = (DWORD)(m->esp + 0xdcu);	/* 402a36: lea edi, [esp + 0xdc] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 402a3d: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 402a3f: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 402a44: mov dword ptr [esp + 0x10], esi */
	{ DWORD a_ = m->eax, b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402a48: cmp eax, 0x270f */
	if (m->zf) goto L_402a6b;	/* 402a4d: je 0x402a6b */
	{ DWORD a_ = m->ebx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402a4f: cmp ebx, esi */
	if (m->zf || m->sf != m->of) goto L_402a6b;	/* 402a51: jle 0x402a6b */
L_402a53:
	{ DWORD a_ = M8((DWORD)(m->esp + m->esi*1 + 0x78u)), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402a53: cmp byte ptr [esp + esi + 0x78], 0x7c */
	if (!m->zf) goto L_402a66;	/* 402a58: jne 0x402a66 */
	{ DWORD a_ = M8((DWORD)(m->esp + m->esi*1 + 0x79u)), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402a5a: cmp byte ptr [esp + esi + 0x79], 0x7c */
	if (!m->zf) goto L_402c15;	/* 402a5f: jne 0x402c15 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402a65: inc esi */
L_402a66:
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402a66: inc esi */
	{ DWORD a_ = m->esi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402a67: cmp esi, ebx */
	if (m->sf != m->of) goto L_402a53;	/* 402a69: jl 0x402a53 */
L_402a6b:
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 402a6b: lea ecx, [esp + 0x78] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402a6f: push ebx */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 402a70: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402a74: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402a75: push edx */
	m->esp -= 4; M32(m->esp) = 0x402a7bu; native_call(m, 0x49ea80u);	/* 402a76: call 0x49ea80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402a7b: add esp, 0xc */
L_402a7e:
	m->eax = M32((DWORD)(m->esp + 0x14cu));	/* 402a7e: mov eax, dword ptr [esp + 0x14c] */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 402a85: mov ecx, dword ptr [esp + 0x144] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402a8c: sub eax, ecx */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 402a8e: lea edi, [esp + 0x14] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402a92: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402a93: sub eax, edx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 402a95: xor esi, esi */
	m->ebx = m->eax;	/* 402a97: mov ebx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 402a99: xor eax, eax */
	{ DWORD a_ = m->ebx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 402a9b: sar ebx, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 402a9d: add ebx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402a9f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 402aa2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 402aa4: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402aa6: dec ecx */
	m->edi = m->ecx;	/* 402aa7: mov edi, ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 402aa9: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_402ad0;	/* 402aab: jle 0x402ad0 */
L_402aad:
	{ DWORD a_ = M8((DWORD)(m->esp + m->eax*1 + 0x14u)), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402aad: cmp byte ptr [esp + eax + 0x14], 0x24 */
	if (!m->zf) goto L_402acb;	/* 402ab2: jne 0x402acb */
	{ DWORD a_ = M8((DWORD)(m->esp + m->eax*1 + 0x15u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402ab4: cmp byte ptr [esp + eax + 0x15], 0x5b */
	if (!m->zf) goto L_402acb;	/* 402ab9: jne 0x402acb */
	{ DWORD a_ = M8((DWORD)(m->esp + m->eax*1 + 0x17u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402abb: cmp byte ptr [esp + eax + 0x17], 0x5d */
	if (!m->zf) goto L_402acb;	/* 402ac0: jne 0x402acb */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + m->eax*1 + 0x19u))) & 0xff) << 0);	/* 402ac2: mov cl, byte ptr [esp + eax + 0x19] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 402ac6: test cl, cl */
	if (m->zf) goto L_402acb;	/* 402ac8: je 0x402acb */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402aca: inc esi */
L_402acb:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 402acb: inc eax */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402acc: cmp eax, edi */
	if (m->sf != m->of) goto L_402aad;	/* 402ace: jl 0x402aad */
L_402ad0:
	m->eax = (DWORD)(m->esp + 0x14u);	/* 402ad0: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402ad4: push eax */
	m->esp -= 4; M32(m->esp) = 0x402adau; native_call(m, 0x402590u);	/* 402ad5: call 0x402590 */
	m->ecx = (DWORD)(m->esi + m->esi*4 + 0x0u);	/* 402ada: lea ecx, [esi + esi*4] */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 402add: lea edx, [eax + eax*2] */
	m->esi = m->ecx;	/* 402ae0: mov esi, ecx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 402ae2: push 2 */
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 402ae4: sub esi, edi */
	M32((DWORD)(0x4d23d8u)) = 0xdu;	/* 402ae6: mov dword ptr [0x4d23d8], 0xd */
	{ DWORD a_ = m->esi, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 402af0: shl esi, 2 */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 402af3: sub esi, edx */
	{ DWORD a_ = m->esi, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 402af5: add esi, ebx */
	m->esp -= 4; M32(m->esp) = 0x402afcu; native_call(m, 0x41ef90u);	/* 402af7: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402afc: add esp, 8 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402aff: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402b0au; native_call(m, M32(0x4a9224u));	/* 402b04: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d444u));	/* 402b0a: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 402b0f: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 402b15: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402b1b: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 402b1c: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402b21: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402b22: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402b23: push eax */
	m->esp -= 4; M32(m->esp) = 0x402b2au; native_call(m, M32(0x4a9228u));	/* 402b24: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9dae1cu));	/* 402b2a: mov eax, dword ptr [0x9dae1c] */
	m->ecx = m->eax;	/* 402b2f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402b31: and ecx, 0x800001ff */
	if (!m->sf) goto L_402b41;	/* 402b37: jns 0x402b41 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402b39: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402b3a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402b40: inc ecx */
L_402b41:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402b41: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402b42: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402b48: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402b49: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402b4b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402b51: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402b54: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402b5du; native_call(m, 0x4566c0u);	/* 402b58: call 0x4566c0 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 402b5d: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402b61: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402b62: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402b63: push esi */
	m->esp -= 4; M32(m->esp) = 0x402b69u; native_call(m, 0x401870u);	/* 402b64: call 0x401870 */
	m->eax = M32((DWORD)(0x76d360u));	/* 402b69: mov eax, dword ptr [0x76d360] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402b6e: add esp, 0xc */
	m->ecx = m->eax;	/* 402b71: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402b73: and ecx, 0x800001ff */
	if (!m->sf) goto L_402b83;	/* 402b79: jns 0x402b83 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402b7b: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402b7c: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402b82: inc ecx */
L_402b83:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402b83: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402b84: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402b8a: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402b8b: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402b8d: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402b93: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402b96: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402b9fu; native_call(m, 0x4566c0u);	/* 402b9a: call 0x4566c0 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 402b9f: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402ba3: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402ba4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402ba5: push esi */
	m->esp -= 4; M32(m->esp) = 0x402babu; native_call(m, 0x401aa0u);	/* 402ba6: call 0x401aa0 */
	m->eax = M32((DWORD)(0x9dad90u));	/* 402bab: mov eax, dword ptr [0x9dad90] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402bb0: add esp, 0xc */
	m->ecx = m->eax;	/* 402bb3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402bb5: and ecx, 0x800001ff */
	if (!m->sf) goto L_402bc5;	/* 402bbb: jns 0x402bc5 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402bbd: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402bbe: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402bc4: inc ecx */
L_402bc5:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402bc5: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402bc6: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402bcc: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402bcd: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402bcf: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402bd5: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402bd8: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402be1u; native_call(m, 0x4566c0u);	/* 402bdc: call 0x4566c0 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 402be1: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402be5: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402be6: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402be7: push esi */
	m->esp -= 4; M32(m->esp) = 0x402bedu; native_call(m, 0x402bedu + M32(0x402be9u));	/* 0x402210 unless the patch DLL retargets it */	/* 402be8: call 0x402210 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402bed: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402bf0: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402bfbu; native_call(m, M32(0x4a922cu));	/* 402bf5: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 402bfb: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 402bff: add ebp, 0x11 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 402c02: test eax, eax */
	if (!m->zf) goto L_402a14;	/* 402c04: jne 0x402a14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 402c0a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 402c0b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 402c0c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 402c0d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x130u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402c0e: add esp, 0x130 */
	m->esp += 4 + 0; return;	/* 402c14: ret  */
L_402c15:
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 402c15: lea ecx, [esp + 0x78] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402c19: push esi */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 402c1a: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402c1e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402c1f: push edx */
	M32((DWORD)(m->esp + 0x1cu)) = 0x1u;	/* 402c20: mov dword ptr [esp + 0x1c], 1 */
	m->esp -= 4; M32(m->esp) = 0x402c2du; native_call(m, 0x49ea80u);	/* 402c28: call 0x49ea80 */
	{ DWORD a_ = m->ebx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 402c2d: sub ebx, esi */
	m->eax = (DWORD)(m->esp + m->esi*1 + 0x85u);	/* 402c2f: lea eax, [esp + esi + 0x85] */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 402c36: dec ebx */
	m->ecx = (DWORD)(m->esp + 0xe8u);	/* 402c37: lea ecx, [esp + 0xe8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402c3e: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402c3f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402c40: push ecx */
	m->esp -= 4; M32(m->esp) = 0x402c46u; native_call(m, 0x49ea80u);	/* 402c41: call 0x49ea80 */
	m->ecx = 0x19u;	/* 402c46: mov ecx, 0x19 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 402c4b: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x90u);	/* 402c4d: lea edi, [esp + 0x90] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402c54: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 402c57: rep stosd dword ptr es:[edi], eax */
	m->edi = (DWORD)(m->esp + 0xdcu);	/* 402c59: lea edi, [esp + 0xdc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402c60: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 402c63: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 402c65: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 402c67: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x78u);	/* 402c69: lea edx, [esp + 0x78] */
	m->eax = m->ecx;	/* 402c6d: mov eax, ecx */
	m->esi = m->edi;	/* 402c6f: mov esi, edi */
	m->edi = m->edx;	/* 402c71: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 402c73: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 402c76: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 402c78: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402c7a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 402c7d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_402a7e;	/* 402c7f: jmp 0x402a7e */
}

/* hud_403210 (0x403210), lifted by tools/lift.py */
static void lift_403210(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 403210: mov eax, dword ptr [esp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 403214: mov ecx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 403218: sub eax, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40321a: push ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40321b: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40321c: sub eax, edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 40321e: push ebp */
	m->ebx = m->eax;	/* 40321f: mov ebx, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403221: push esi */
	m->esi = M32((DWORD)(m->esp + 0x1cu));	/* 403222: mov esi, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 403226: push edi */
	{ DWORD a_ = m->ebx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 403227: sar ebx, 1 */
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 403229: add ebx, ecx */
	m->edi = m->esi;	/* 40322b: mov edi, esi */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40322d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 403230: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 403232: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 403234: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 403236: dec ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 403237: xor ebp, ebp */
	m->edi = m->ecx;	/* 403239: mov edi, ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40323b: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_403262;	/* 40323d: jle 0x403262 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((0x5bu) & 0xff) << 0);	/* 40323f: mov dl, 0x5b */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((0x5du) & 0xff) << 0);	/* 403241: mov cl, 0x5d */
L_403243:
	{ DWORD a_ = M8((DWORD)(m->eax + m->esi*1 + 0x0u)), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 403243: cmp byte ptr [eax + esi], 0x24 */
	if (!m->zf) goto L_40325d;	/* 403247: jne 0x40325d */
	{ DWORD a_ = M8((DWORD)(m->eax + m->esi*1 + 0x1u)), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 403249: cmp byte ptr [eax + esi + 1], dl */
	if (!m->zf) goto L_40325d;	/* 40324d: jne 0x40325d */
	{ DWORD a_ = M8((DWORD)(m->eax + m->esi*1 + 0x3u)), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40324f: cmp byte ptr [eax + esi + 3], cl */
	if (!m->zf) goto L_40325d;	/* 403253: jne 0x40325d */
	{ DWORD a_ = M8((DWORD)(m->eax + m->esi*1 + 0x5u)), b_ = 0x0u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 403255: cmp byte ptr [eax + esi + 5], 0 */
	if (m->zf) goto L_40325d;	/* 40325a: je 0x40325d */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40325c: inc ebp */
L_40325d:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40325d: inc eax */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40325e: cmp eax, edi */
	if (m->sf != m->of) goto L_403243;	/* 403260: jl 0x403243 */
L_403262:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 403262: push 2 */
	M32((DWORD)(0x4d23d8u)) = 0x6u;	/* 403264: mov dword ptr [0x4d23d8], 6 */
	m->esp -= 4; M32(m->esp) = 0x403273u; native_call(m, 0x41ef90u);	/* 40326e: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403273: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403276: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x403281u; native_call(m, M32(0x4a9224u));	/* 40327b: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d444u));	/* 403281: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 403286: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 40328c: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403292: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 403293: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403298: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 403299: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40329a: push eax */
	m->esp -= 4; M32(m->esp) = 0x4032a1u; native_call(m, M32(0x4a9228u));	/* 40329b: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x76d448u));	/* 4032a1: mov eax, dword ptr [0x76d448] */
	m->ecx = m->eax;	/* 4032a6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4032a8: and ecx, 0x800001ff */
	if (!m->sf) goto L_4032b8;	/* 4032ae: jns 0x4032b8 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4032b0: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4032b1: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4032b7: inc ecx */
L_4032b8:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4032b8: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4032b9: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4032bf: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4032c0: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4032c2: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4032c8: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4032cb: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4032d4u; native_call(m, 0x4566c0u);	/* 4032cf: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4032d4: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4032d8: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4032d9: push eax */
	m->eax = (DWORD)(m->ebp + m->ebp*4 + 0x0u);	/* 4032da: lea eax, [ebp + ebp*4] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4032de: sub eax, edi */
	m->ecx = (DWORD)(m->ebx + m->eax*2 + 0x0u);	/* 4032e0: lea ecx, [ebx + eax*2] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4032e3: add eax, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4032e5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4032ebu; native_call(m, 0x4032ebu + M32(0x4032e7u));	/* 0x403060 unless the patch DLL retargets it */	/* 4032e6: call 0x403060 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4032eb: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4032ee: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4032f9u; native_call(m, M32(0x4a922cu));	/* 4032f3: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4032f9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4032fa: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4032fb: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4032fc: pop ebx */
	m->esp += 4 + 0; return;	/* 4032fd: ret  */
}

/* hud_402db0 (0x402db0), lifted by tools/lift.py */
static void lift_402db0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x130u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402db0: sub esp, 0x130 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402db6: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 402db9: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x68u);	/* 402dbb: lea edx, [esp + 0x68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402dbf: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402dc0: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402dc1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402dc2: push edi */
	m->edi = M32((DWORD)(m->esp + 0x150u));	/* 402dc3: mov edi, dword ptr [esp + 0x150] */
	m->ebp = M32((DWORD)(m->esp + 0x148u));	/* 402dca: mov ebp, dword ptr [esp + 0x148] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 402dd1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 402dd3: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 402dd5: sub edi, ecx */
	m->eax = m->ecx;	/* 402dd7: mov eax, ecx */
	m->esi = m->edi;	/* 402dd9: mov esi, edi */
	m->edi = m->edx;	/* 402ddb: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 402ddd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 402de0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 402de2: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402de4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 402de7: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_402de9:
	m->edi = (DWORD)(m->esp + 0x78u);	/* 402de9: lea edi, [esp + 0x78] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402ded: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 402df0: xor eax, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 402df2: xor esi, esi */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 402df4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 402df6: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402df8: dec ecx */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 402df9: lea edi, [esp + 0x14] */
	m->ebx = m->ecx;	/* 402dfd: mov ebx, ecx */
	m->ecx = 0x19u;	/* 402dff: mov ecx, 0x19 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 402e04: rep stosd dword ptr es:[edi], eax */
	m->ecx = 0x19u;	/* 402e06: mov ecx, 0x19 */
	m->edi = (DWORD)(m->esp + 0xdcu);	/* 402e0b: lea edi, [esp + 0xdc] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 402e12: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 402e14: mov eax, dword ptr [0x76d3e8] */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 402e19: mov dword ptr [esp + 0x10], esi */
	{ DWORD a_ = m->eax, b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402e1d: cmp eax, 0x270f */
	if (m->zf) goto L_402e40;	/* 402e22: je 0x402e40 */
	{ DWORD a_ = m->ebx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402e24: cmp ebx, esi */
	if (m->zf || m->sf != m->of) goto L_402e40;	/* 402e26: jle 0x402e40 */
L_402e28:
	{ DWORD a_ = M8((DWORD)(m->esp + m->esi*1 + 0x78u)), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402e28: cmp byte ptr [esp + esi + 0x78], 0x7c */
	if (!m->zf) goto L_402e3b;	/* 402e2d: jne 0x402e3b */
	{ DWORD a_ = M8((DWORD)(m->esp + m->esi*1 + 0x79u)), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402e2f: cmp byte ptr [esp + esi + 0x79], 0x7c */
	if (!m->zf) goto L_402fea;	/* 402e34: jne 0x402fea */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402e3a: inc esi */
L_402e3b:
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402e3b: inc esi */
	{ DWORD a_ = m->esi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402e3c: cmp esi, ebx */
	if (m->sf != m->of) goto L_402e28;	/* 402e3e: jl 0x402e28 */
L_402e40:
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 402e40: lea ecx, [esp + 0x78] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402e44: push ebx */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 402e45: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402e49: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402e4a: push edx */
	m->esp -= 4; M32(m->esp) = 0x402e50u; native_call(m, 0x49ea80u);	/* 402e4b: call 0x49ea80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402e50: add esp, 0xc */
L_402e53:
	m->eax = M32((DWORD)(m->esp + 0x14cu));	/* 402e53: mov eax, dword ptr [esp + 0x14c] */
	m->ecx = M32((DWORD)(m->esp + 0x144u));	/* 402e5a: mov ecx, dword ptr [esp + 0x144] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402e61: sub eax, ecx */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 402e63: lea edi, [esp + 0x14] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402e67: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402e68: sub eax, edx */
	m->esi = m->eax;	/* 402e6a: mov esi, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 402e6c: xor eax, eax */
	{ DWORD a_ = m->esi, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 402e6e: sar esi, 1 */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 402e70: add esi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402e72: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 402e75: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 402e77: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402e79: dec ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 402e7a: xor edi, edi */
	m->ebx = m->ecx;	/* 402e7c: mov ebx, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 402e7e: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_402ea5;	/* 402e80: jle 0x402ea5 */
L_402e82:
	{ DWORD a_ = M8((DWORD)(m->esp + m->eax*1 + 0x14u)), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402e82: cmp byte ptr [esp + eax + 0x14], 0x24 */
	if (!m->zf) goto L_402ea0;	/* 402e87: jne 0x402ea0 */
	{ DWORD a_ = M8((DWORD)(m->esp + m->eax*1 + 0x15u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402e89: cmp byte ptr [esp + eax + 0x15], 0x5b */
	if (!m->zf) goto L_402ea0;	/* 402e8e: jne 0x402ea0 */
	{ DWORD a_ = M8((DWORD)(m->esp + m->eax*1 + 0x17u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402e90: cmp byte ptr [esp + eax + 0x17], 0x5d */
	if (!m->zf) goto L_402ea0;	/* 402e95: jne 0x402ea0 */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + m->eax*1 + 0x19u))) & 0xff) << 0);	/* 402e97: mov cl, byte ptr [esp + eax + 0x19] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 402e9b: test cl, cl */
	if (m->zf) goto L_402ea0;	/* 402e9d: je 0x402ea0 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 402e9f: inc edi */
L_402ea0:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 402ea0: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402ea1: cmp eax, ebx */
	if (m->sf != m->of) goto L_402e82;	/* 402ea3: jl 0x402e82 */
L_402ea5:
	m->eax = (DWORD)(m->esp + 0x14u);	/* 402ea5: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402ea9: push eax */
	m->esp -= 4; M32(m->esp) = 0x402eafu; native_call(m, 0x402590u);	/* 402eaa: call 0x402590 */
	m->ecx = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 402eaf: lea ecx, [edi + edi*4] */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 402eb2: lea edx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 402eb5: sub ecx, ebx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 402eb7: push 2 */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 402eb9: shl ecx, 3 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 402ebc: sub ecx, edx */
	M32((DWORD)(0x4d23d8u)) = 0x12u;	/* 402ebe: mov dword ptr [0x4d23d8], 0x12 */
	m->esi = (DWORD)(m->ecx + m->esi*1 + 0x4u);	/* 402ec8: lea esi, [ecx + esi + 4] */
	m->esp -= 4; M32(m->esp) = 0x402ed1u; native_call(m, 0x41ef90u);	/* 402ecc: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402ed1: add esp, 8 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402ed4: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402edfu; native_call(m, M32(0x4a9224u));	/* 402ed9: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d444u));	/* 402edf: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 402ee4: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 402eea: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402ef0: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 402ef1: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402ef6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402ef7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402ef8: push eax */
	m->esp -= 4; M32(m->esp) = 0x402effu; native_call(m, M32(0x4a9228u));	/* 402ef9: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9dae1cu));	/* 402eff: mov eax, dword ptr [0x9dae1c] */
	m->ecx = m->eax;	/* 402f04: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402f06: and ecx, 0x800001ff */
	if (!m->sf) goto L_402f16;	/* 402f0c: jns 0x402f16 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402f0e: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402f0f: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402f15: inc ecx */
L_402f16:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402f16: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402f17: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402f1d: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402f1e: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402f20: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402f26: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402f29: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402f32u; native_call(m, 0x4566c0u);	/* 402f2d: call 0x4566c0 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 402f32: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402f36: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402f37: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402f38: push esi */
	m->esp -= 4; M32(m->esp) = 0x402f3eu; native_call(m, 0x401ce0u);	/* 402f39: call 0x401ce0 */
	m->eax = M32((DWORD)(0x76d360u));	/* 402f3e: mov eax, dword ptr [0x76d360] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402f43: add esp, 0xc */
	m->ecx = m->eax;	/* 402f46: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402f48: and ecx, 0x800001ff */
	if (!m->sf) goto L_402f58;	/* 402f4e: jns 0x402f58 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402f50: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402f51: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402f57: inc ecx */
L_402f58:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402f58: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402f59: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402f5f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402f60: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402f62: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402f68: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402f6b: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402f74u; native_call(m, 0x4566c0u);	/* 402f6f: call 0x4566c0 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 402f74: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402f78: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402f79: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402f7a: push esi */
	m->esp -= 4; M32(m->esp) = 0x402f80u; native_call(m, 0x401e70u);	/* 402f7b: call 0x401e70 */
	m->eax = M32((DWORD)(0x9dad90u));	/* 402f80: mov eax, dword ptr [0x9dad90] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402f85: add esp, 0xc */
	m->ecx = m->eax;	/* 402f88: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402f8a: and ecx, 0x800001ff */
	if (!m->sf) goto L_402f9a;	/* 402f90: jns 0x402f9a */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 402f92: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 402f93: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 402f99: inc ecx */
L_402f9a:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 402f9a: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 402f9b: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402fa1: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402fa2: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 402fa4: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402faa: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 402fad: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x402fb6u; native_call(m, 0x4566c0u);	/* 402fb1: call 0x4566c0 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 402fb6: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402fba: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402fbb: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402fbc: push esi */
	m->esp -= 4; M32(m->esp) = 0x402fc2u; native_call(m, 0x402fc2u + M32(0x402fbeu));	/* 0x402420 unless the patch DLL retargets it */	/* 402fbd: call 0x402420 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402fc2: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402fc5: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402fd0u; native_call(m, M32(0x4a922cu));	/* 402fca: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 402fd0: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 402fd4: add ebp, 0x21 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 402fd7: test eax, eax */
	if (!m->zf) goto L_402de9;	/* 402fd9: jne 0x402de9 */
	m->edi = M32(m->esp); m->esp += 4;	/* 402fdf: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 402fe0: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 402fe1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 402fe2: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x130u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402fe3: add esp, 0x130 */
	m->esp += 4 + 0; return;	/* 402fe9: ret  */
L_402fea:
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 402fea: lea ecx, [esp + 0x78] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402fee: push esi */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 402fef: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402ff3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402ff4: push edx */
	M32((DWORD)(m->esp + 0x1cu)) = 0x1u;	/* 402ff5: mov dword ptr [esp + 0x1c], 1 */
	m->esp -= 4; M32(m->esp) = 0x403002u; native_call(m, 0x49ea80u);	/* 402ffd: call 0x49ea80 */
	{ DWORD a_ = m->ebx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 403002: sub ebx, esi */
	m->eax = (DWORD)(m->esp + m->esi*1 + 0x85u);	/* 403004: lea eax, [esp + esi + 0x85] */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 40300b: dec ebx */
	m->ecx = (DWORD)(m->esp + 0xe8u);	/* 40300c: lea ecx, [esp + 0xe8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 403013: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403014: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403015: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40301bu; native_call(m, 0x49ea80u);	/* 403016: call 0x49ea80 */
	m->ecx = 0x19u;	/* 40301b: mov ecx, 0x19 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 403020: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x90u);	/* 403022: lea edi, [esp + 0x90] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403029: add esp, 0x18 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40302c: rep stosd dword ptr es:[edi], eax */
	m->edi = (DWORD)(m->esp + 0xdcu);	/* 40302e: lea edi, [esp + 0xdc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403035: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 403038: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 40303a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40303c: sub edi, ecx */
	m->edx = (DWORD)(m->esp + 0x78u);	/* 40303e: lea edx, [esp + 0x78] */
	m->eax = m->ecx;	/* 403042: mov eax, ecx */
	m->esi = m->edi;	/* 403044: mov esi, edi */
	m->edi = m->edx;	/* 403046: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 403048: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 40304b: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 40304d: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40304f: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 403052: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_402e53;	/* 403054: jmp 0x402e53 */
}

/* menu_drawCursor (0x429bc0), lifted by tools/lift.py */
static void lift_429bc0(X86 *m)
{
	m->eax = M32((DWORD)(0x4df03cu));	/* 429bc0: mov eax, dword ptr [0x4df03c] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429bc5: sub esp, 0x10 */
	m->ecx = m->eax;	/* 429bc8: mov ecx, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 429bca: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 429bcb: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 429bcc: push esi */
	m->esi = M32((DWORD)(0x4ded68u));	/* 429bcd: mov esi, dword ptr [0x4ded68] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 429bd3: push edi */
	m->edi = M32((DWORD)(0x4ded6cu));	/* 429bd4: mov edi, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->ecx, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 429bda: and ecx, 0x80000003 */
	if (!m->sf) goto L_429be7;	/* 429be0: jns 0x429be7 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 429be2: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 429be3: or ecx, 0xfffffffc */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 429be6: inc ecx */
L_429be7:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 429be7: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429be8: and edx, 3 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 429beb: push 2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429bed: add eax, edx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 429bef: mov dword ptr [esp + 0x14], ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429bf3: sar eax, 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 429bf6: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x429bffu; native_call(m, 0x41ef90u);	/* 429bfa: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429bff: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 429c02: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x429c0du; native_call(m, M32(0x4a9224u));	/* 429c07: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429c0d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429c12: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429c17: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429c1c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x429c27u; native_call(m, M32(0x4a9228u));	/* 429c21: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x4e152cu));	/* 429c27: mov eax, dword ptr [0x4e152c] */
	m->edx = m->eax;	/* 429c2c: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429c2e: and edx, 0x800001ff */
	if (!m->sf) goto L_429c3e;	/* 429c34: jns 0x429c3e */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 429c36: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429c37: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 429c3d: inc edx */
L_429c3e:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429c3e: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 429c3f: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 429c45: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429c46: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429c4c: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429c4e: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 429c51: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x429c5au; native_call(m, 0x4566c0u);	/* 429c55: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429c5a: push 7 */
	m->esp -= 4; M32(m->esp) = 0x429c62u; native_call(m, M32(0x4a921cu));	/* 429c5c: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 429c62: fild dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(0x4a920cu));	/* 429c66: mov ebx, dword ptr [0x4a920c] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 429c6c: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 429c70: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 429c76: fstp dword ptr [esp + 0x1c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 429c7a: fild dword ptr [esp + 0x10] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 429c7e: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 429c82: push ebp */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 429c83: fst dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 429c87: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 429c8d: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 429c91: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429c95: push edx */
	m->esp -= 4; M32(m->esp) = 0x429c98u; native_call(m, m->ebx);	/* 429c96: call ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 429c98: push edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 429c99: push esi */
	m->esp -= 4; M32(m->esp) = 0x429c9fu; native_call(m, 0x41ef60u);	/* 429c9a: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 429c9f: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 429ca3: fadd dword ptr [0x4a9424] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429ca9: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 429cac: fmul dword ptr [0x4a941c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 429cb2: push ebp */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 429cb3: fstp dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 429cb7: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429cbb: push eax */
	m->esp -= 4; M32(m->esp) = 0x429cbeu; native_call(m, m->ebx);	/* 429cbc: call ebx */
	m->ebp = (DWORD)(m->esi + 0x2fu);	/* 429cbe: lea ebp, [esi + 0x2f] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 429cc1: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 429cc2: push ebp */
	m->esp -= 4; M32(m->esp) = 0x429cc8u; native_call(m, 0x429cc8u + M32(0x429cc4u));	/* 0x41ef60 unless the patch DLL retargets it */	/* 429cc3: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 429cc8: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 429ccc: fadd dword ptr [0x4a9424] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 429cd2: mov edx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429cd6: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 429cd9: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 429cdf: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 429ce3: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429ce7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429ce8: push edx */
	m->esp -= 4; M32(m->esp) = 0x429cebu; native_call(m, m->ebx);	/* 429ce9: call ebx */
	{ DWORD a_ = m->edi, b_ = 0x2fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 429ceb: add edi, 0x2f */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 429cee: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 429cef: push ebp */
	m->esp -= 4; M32(m->esp) = 0x429cf5u; native_call(m, 0x429cf5u + M32(0x429cf1u));	/* 0x41ef60 unless the patch DLL retargets it */	/* 429cf0: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 429cf5: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 429cf9: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429cfd: add esp, 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429d00: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429d01: push ecx */
	m->esp -= 4; M32(m->esp) = 0x429d04u; native_call(m, m->ebx);	/* 429d02: call ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 429d04: push edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 429d05: push esi */
	m->esp -= 4; M32(m->esp) = 0x429d0bu; native_call(m, 0x41ef60u);	/* 429d06: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429d0b: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x429d14u; native_call(m, M32(0x4a9220u));	/* 429d0e: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 429d14: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x429d1fu; native_call(m, M32(0x4a922cu));	/* 429d19: call dword ptr [0x4a922c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 429d1f: fld dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df910u));	/* 429d25: fadd dword ptr [0x4df910] */
	m->edi = M32(m->esp); m->esp += 4;	/* 429d2b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 429d2c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 429d2d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 429d2e: pop ebx */
	MF((DWORD)(0x4df910u)) = (float)ST(0);	/* 429d2f: fst dword ptr [0x4df910] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 429d35: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 429d3b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 429d3d: test ah, 1 */
	if (!m->zf) goto L_429d66;	/* 429d40: jne 0x429d66 */
	m->eax = M32((DWORD)(0x4df03cu));	/* 429d42: mov eax, dword ptr [0x4df03c] */
	M32((DWORD)(0x4df910u)) = 0x0u;	/* 429d47: mov dword ptr [0x4df910], 0 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 429d51: inc eax */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 429d52: cmp eax, 0xf */
	M32((DWORD)(0x4df03cu)) = m->eax;	/* 429d55: mov dword ptr [0x4df03c], eax */
	if (m->sf != m->of) goto L_429d66;	/* 429d5a: jl 0x429d66 */
	M32((DWORD)(0x4df03cu)) = 0x0u;	/* 429d5c: mov dword ptr [0x4df03c], 0 */
L_429d66:
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429d66: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 429d69: ret  */
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
