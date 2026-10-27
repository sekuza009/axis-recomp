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

static void lift_437e00(X86 *m);

/* room_437e00 (0x437e00), lifted by tools/lift.py */
static void lift_437e00(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437e00: sub esp, 0x4c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 437e03: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 437e04: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 437e05: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 437e06: push edi */
	M32((DWORD)(m->esp + 0x3cu)) = 0xffffffffu;	/* 437e07: mov dword ptr [esp + 0x3c], 0xffffffff */
	M32((DWORD)(m->esp + 0x50u)) = 0xc2200000u;	/* 437e0f: mov dword ptr [esp + 0x50], 0xc2200000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 437e17: mov dword ptr [esp + 0x54], 0 */
	M32((DWORD)(m->esp + 0x58u)) = 0x42200000u;	/* 437e1f: mov dword ptr [esp + 0x58], 0x42200000 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 437e27: xor ebp, ebp */
	m->ebx = 0x9daf88u;	/* 437e29: mov ebx, 0x9daf88 */
L_437e2e:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 437e2e: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437e33: test eax, eax */
	if (!m->zf) goto L_437e80;	/* 437e35: jne 0x437e80 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 437e37: mov eax, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437e3c: sub esp, 0x2c */
	m->ecx = 0xbu;	/* 437e3f: mov ecx, 0xb */
	m->esi = m->ebx;	/* 437e44: mov esi, ebx */
	m->edi = m->esp;	/* 437e46: mov edi, esp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 437e48: push eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 437e49: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 437e4b: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 437e51: push ecx */
	m->esp -= 4; M32(m->esp) = 0x437e57u; native_call(m, 0x41eea0u);	/* 437e52: call 0x41eea0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437e57: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437e5a: cmp eax, 1 */
	if (m->zf) goto L_437e77;	/* 437e5d: je 0x437e77 */
	{ DWORD a_ = m->ebx, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 437e5f: add ebx, 0x2c */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 437e62: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x9db090u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437e63: cmp ebx, 0x9db090 */
	if (m->sf != m->of) goto L_437e2e;	/* 437e69: jl 0x437e2e */
	M32((DWORD)(0x680398u)) = 0x0u;	/* 437e6b: mov dword ptr [0x680398], 0 */
	goto L_437eb9;	/* 437e75: jmp 0x437eb9 */
L_437e77:
	{ DWORD a_ = m->ebp, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437e77: cmp ebp, -1 */
	M32((DWORD)(m->esp + 0x3cu)) = m->ebp;	/* 437e7a: mov dword ptr [esp + 0x3c], ebp */
	if (!m->zf) goto L_437e8c;	/* 437e7e: jne 0x437e8c */
L_437e80:
	M32((DWORD)(0x680398u)) = 0x0u;	/* 437e80: mov dword ptr [0x680398], 0 */
	goto L_437eb9;	/* 437e8a: jmp 0x437eb9 */
L_437e8c:
	m->eax = M32((DWORD)(0x907b24u));	/* 437e8c: mov eax, dword ptr [0x907b24] */
	M32((DWORD)(0x680398u)) = 0x1u;	/* 437e91: mov dword ptr [0x680398], 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437e9b: cmp eax, ebp */
	if (m->zf) goto L_437eb9;	/* 437e9d: je 0x437eb9 */
	M32((DWORD)(0x907b24u)) = m->ebp;	/* 437e9f: mov dword ptr [0x907b24], ebp */
	M32((DWORD)(0x680cccu)) = 0x42200000u;	/* 437ea5: mov dword ptr [0x680ccc], 0x42200000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 437eaf: mov dword ptr [0x4df454], 0xbf800000 */
L_437eb9:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 437eb9: push 1 */
	m->esp -= 4; M32(m->esp) = 0x437ec0u; native_call(m, 0x41ef90u);	/* 437ebb: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437ec0: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 437ec3: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x437eceu; native_call(m, M32(0x4a9224u));	/* 437ec8: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 437ece: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 437ed4: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 437eda: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 437ee0: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 437ee6: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 437ee8: mov dword ptr [esp + 0x1c], eax */
	goto L_437ef2;	/* 437eec: jmp 0x437ef2 */
L_437eee:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 437eee: mov eax, dword ptr [esp + 0x1c] */
L_437ef2:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437ef2: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 437ef5: mov dword ptr [esp + 0x28], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 437efd: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x0u;	/* 437f05: mov dword ptr [esp + 0x44], 0 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3e800000u;	/* 437f0d: mov dword ptr [esp + 0x48], 0x3e800000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f000000u;	/* 437f15: mov dword ptr [esp + 0x38], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_437f47;	/* 437f1d: jle 0x437f47 */
	M32((DWORD)(m->esp + 0x28u)) = 0x3f000000u;	/* 437f1f: mov dword ptr [esp + 0x28], 0x3f000000 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 437f27: mov dword ptr [esp + 0x30], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3ef00000u;	/* 437f2f: mov dword ptr [esp + 0x44], 0x3ef00000 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3f200000u;	/* 437f37: mov dword ptr [esp + 0x48], 0x3f200000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 437f3f: mov dword ptr [esp + 0x38], 0x3f800000 */
L_437f47:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437f47: cmp eax, 2 */
	if (m->sf == m->of) goto L_437f7c;	/* 437f4a: jge 0x437f7c */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 437f4c: mov eax, dword ptr [0x4e0cd0] */
	m->edx = m->eax;	/* 437f51: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 437f53: and edx, 0x800001ff */
	if (!m->sf) goto L_437f63;	/* 437f59: jns 0x437f63 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 437f5b: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 437f5c: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 437f62: inc edx */
L_437f63:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 437f63: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 437f64: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 437f6a: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 437f6b: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 437f71: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 437f73: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 437f76: mov ecx, dword ptr [ecx + eax*4 + 4] */
	goto L_437fb5;	/* 437f7a: jmp 0x437fb5 */
L_437f7c:
	m->edx = (DWORD)(m->eax*4 + 0x0u);	/* 437f7c: lea edx, [eax*4] */
	m->eax = 0x4df910u;	/* 437f83: mov eax, 0x4df910 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 437f88: sub eax, edx */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 437f8a: mov eax, dword ptr [eax] */
	m->ecx = m->eax;	/* 437f8c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 437f8e: and ecx, 0x800001ff */
	if (!m->sf) goto L_437f9e;	/* 437f94: jns 0x437f9e */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 437f96: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 437f97: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 437f9d: inc ecx */
L_437f9e:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 437f9e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 437f9f: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 437fa5: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 437fa6: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 437fa8: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 437fae: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 437fb1: mov ecx, dword ptr [edx + eax*4 + 4] */
L_437fb5:
	m->esp -= 4; M32(m->esp) = 0x437fbau; native_call(m, 0x4566c0u);	/* 437fb5: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 437fba: mov dword ptr [esp + 0x18], 0 */
L_437fc2:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 437fc2: mov eax, dword ptr [esp + 0x18] */
	m->ecx = 0x3u;	/* 437fc6: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 437fcb: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 437fcc: idiv ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 437fce: mov dword ptr [esp + 0x2c], edx */
	m->esp -= 4; M32(m->esp) = 0x437fd7u; native_call(m, 0x41f050u);	/* 437fd2: call 0x41f050 */
	m->edx = M32((DWORD)(0x9dd698u));	/* 437fd7: mov edx, dword ptr [0x9dd698] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 437fdd: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 437fde: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 437fe0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x437fe8u; native_call(m, M32(0x4a9214u));	/* 437fe2: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437fe8: cmp dword ptr [esp + 0x18], 3 */
	if (m->sf == m->of) goto L_437ffa;	/* 437fed: jge 0x437ffa */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 437fef: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + m->eax*4 + 0x50u));	/* 437ff3: mov ecx, dword ptr [esp + eax*4 + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 437ff7: push ecx */
	goto L_438008;	/* 437ff8: jmp 0x438008 */
L_437ffa:
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 437ffa: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 437ffe: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + m->edx*4 + 0x54u)));	/* 437fff: fld dword ptr [esp + edx*4 + 0x54] */
	ST(0) = -ST(0);	/* 438003: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438005: fstp dword ptr [esp] */
L_438008:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438008: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43800a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438011u; native_call(m, 0x41ef20u);	/* 43800c: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 438011: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 438015: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438018: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_4381d8;	/* 43801b: ja 0x4381d8 */
	switch (m->eax) { case 0: goto L_438028; case 1: goto L_438055; case 2: goto L_438074; case 3: goto L_4381c4; default: abort(); }	/* 438021: jmp dword ptr [eax*4 + 0x4388c4] */
L_438028:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 438028: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 43802e: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438034: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 438035: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43803b: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43803e: push 0x3f333333 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438043: push 0 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438045: push 0x3f333333 */
	m->esp -= 4; M32(m->esp) = 0x438050u; native_call(m, M32(0x4a9228u));	/* 43804a: call dword ptr [0x4a9228] */
	goto L_4384b2;	/* 438050: jmp 0x4384b2 */
L_438055:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438055: push 0x3f333333 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43805a: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43805f: push 0x3dcccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438064: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43806fu; native_call(m, M32(0x4a9228u));	/* 438069: call dword ptr [0x4a9228] */
	goto L_4381e1;	/* 43806f: jmp 0x4381e1 */
L_438074:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438074: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 438078: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43807c: cmp ecx, eax */
	if (!m->zf) goto L_4381b7;	/* 43807e: jne 0x4381b7 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 438084: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9428u));	/* 43808a: fmul dword ptr [0x4a9428] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438090: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438091: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438097: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43809a: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43809f: push 0x3dcccccd */
L_4380a4:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4380a4: push 0x3f800000 */
L_4380a9:
	m->esp -= 4; M32(m->esp) = 0x4380afu; native_call(m, M32(0x4a9228u));	/* 4380a9: call dword ptr [0x4a9228] */
L_4380af:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4380af: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4380b3: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4380b5: cmp eax, 3 */
	if (m->sf == m->of) goto L_438633;	/* 4380b8: jge 0x438633 */
	m->esp -= 4; M32(m->esp) = 0x4380c0u; native_call(m, m->ebx);	/* 4380be: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 4380c0: fild dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 4380c4: fst dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 4380c8: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4380ce: fstp dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4380d2: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4380d6: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4380d7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4380dbu; native_call(m, m->esi);	/* 4380d9: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4380db: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4380df: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4380e5: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 4380e9: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4380ef: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4380f3: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4380f7: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4380fd: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 438101: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438105: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438106: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 43810a: fild dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 43810e: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438112: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 438113: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 438119: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 43811f: fstp dword ptr [esp + 0x34] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 438123: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438127: push edx */
	m->esp -= 4; M32(m->esp) = 0x43812au; native_call(m, m->edi);	/* 438128: call edi */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 43812a: mov eax, dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 43812e: mov ecx, dword ptr [esp + 0x20] */
	m->edx = m->eax;	/* 438132: mov edx, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438134: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438135: push edx */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 438136: mov dword ptr [esp + 0x48], eax */
	m->esp -= 4; M32(m->esp) = 0x43813cu; native_call(m, m->esi);	/* 43813a: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 43813c: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438140: fsub dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 438146: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 43814a: mov edx, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 43814e: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 438152: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438156: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438157: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438158: push edx */
	m->esp -= 4; M32(m->esp) = 0x43815bu; native_call(m, m->edi);	/* 438159: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 43815b: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 43815f: fadd dword ptr [0x4a9424] */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 438165: mov ecx, dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 438169: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 43816f: fstp dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 438173: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438177: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438178: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43817bu; native_call(m, m->esi);	/* 438179: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 43817b: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 43817f: fsub dword ptr [0x4a9418] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 438185: mov edx, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 438189: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43818d: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 43818e: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438192: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438196: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438197: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43819au; native_call(m, m->edi);	/* 438198: call edi */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 43819a: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43819e: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43819f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4381a3u; native_call(m, m->esi);	/* 4381a1: call esi */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4381a3: mov eax, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4381a7: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 4381ab: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4381af: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4381b0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4381b1: push edx */
	goto L_43872f;	/* 4381b2: jmp 0x43872f */
L_4381b7:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381b7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381b9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381bb: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381bd: push 0 */
	goto L_4380a9;	/* 4381bf: jmp 0x4380a9 */
L_4381c4:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381c4: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381c9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381ce: push 0x3f800000 */
	goto L_4380a4;	/* 4381d3: jmp 0x4380a4 */
L_4381d8:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4381d8: cmp eax, 1 */
	if (!m->zf) goto L_4384aa;	/* 4381db: jne 0x4384aa */
L_4381e1:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4381e1: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381e5: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4381e7: cmp eax, 3 */
	if (m->sf == m->of) goto L_438359;	/* 4381ea: jge 0x438359 */
	m->esp -= 4; M32(m->esp) = 0x4381f2u; native_call(m, m->ebx);	/* 4381f0: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381f2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4381f4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4381f8u; native_call(m, m->esi);	/* 4381f6: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4381f8: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4381fe: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438204: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438205: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43820b: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43820e: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438213: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x43821au; native_call(m, m->edi);	/* 438218: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 43821a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438220: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438226: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438228: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438229: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43822f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438234u; native_call(m, m->esi);	/* 438232: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438234: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438239: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43823e: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438245u; native_call(m, m->edi);	/* 438243: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438245: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 43824b: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438251: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438256: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 438257: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43825d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438262u; native_call(m, m->esi);	/* 438260: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438262: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438267: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43826c: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438273u; native_call(m, m->edi);	/* 438271: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438273: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438278: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43827cu; native_call(m, m->esi);	/* 43827a: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 43827c: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438282: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438288: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438289: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43828f: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438292: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438297: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x43829eu; native_call(m, m->edi);	/* 43829c: call edi */
	m->esp -= 4; M32(m->esp) = 0x4382a0u; native_call(m, m->ebp);	/* 43829e: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382a0: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4382a4u; native_call(m, m->ebx);	/* 4382a2: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4382a4: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4382aa: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382b0: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4382b2: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4382b3: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4382b9: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4382beu; native_call(m, m->esi);	/* 4382bc: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382be: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382c3: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382c8: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4382cfu; native_call(m, m->edi);	/* 4382cd: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382cf: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382d1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4382d8u; native_call(m, m->esi);	/* 4382d6: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4382d8: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4382de: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4382e4: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4382e5: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4382eb: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382ee: push 0x41200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382f3: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4382fau; native_call(m, m->edi);	/* 4382f8: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382fa: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4382ff: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438306u; native_call(m, m->esi);	/* 438304: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438306: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 43830c: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438312: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438313: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438319: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43831c: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438321: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438328u; native_call(m, m->edi);	/* 438326: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438328: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 43832e: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438334: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438339: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 43833a: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438340: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438345u; native_call(m, m->esi);	/* 438343: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438345: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43834a: push 0xc1200000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43834f: push 0xc1ef3333 */
	goto L_43872f;	/* 438354: jmp 0x43872f */
L_438359:
	m->esp -= 4; M32(m->esp) = 0x43835bu; native_call(m, m->ebx);	/* 438359: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 43835b: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438361: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438367: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438369: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43836a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x43836fu; native_call(m, m->esi);	/* 43836d: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43836f: push 0xc2200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438374: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438379: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438380u; native_call(m, m->edi);	/* 43837e: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438380: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438382: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438389u; native_call(m, m->esi);	/* 438387: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438389: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 43838f: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438395: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438396: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43839c: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43839f: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383a4: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4383abu; native_call(m, m->edi);	/* 4383a9: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383ab: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383b0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4383b7u; native_call(m, m->esi);	/* 4383b5: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4383b7: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4383bd: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4383c3: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4383c4: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4383ca: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383cd: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383d2: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4383d9u; native_call(m, m->edi);	/* 4383d7: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4383d9: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4383df: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383e5: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4383ea: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4383eb: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4383f0u; native_call(m, m->esi);	/* 4383ee: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383f0: push 0xc2200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383f5: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4383fa: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438401u; native_call(m, m->edi);	/* 4383ff: call edi */
	m->esp -= 4; M32(m->esp) = 0x438403u; native_call(m, m->ebp);	/* 438401: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 438403: push 7 */
	m->esp -= 4; M32(m->esp) = 0x438407u; native_call(m, m->ebx);	/* 438405: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438407: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438409: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43840du; native_call(m, m->esi);	/* 43840b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 43840d: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 438413: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438419: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 43841a: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438420: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438423: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438428: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x43842fu; native_call(m, m->edi);	/* 43842d: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 43842f: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 438435: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43843b: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43843d: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43843e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x438443u; native_call(m, m->esi);	/* 438441: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438443: push 0x42200000 */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438448: push 0x41200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43844d: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x438454u; native_call(m, m->edi);	/* 438452: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438454: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 43845a: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438460: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438465: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438466: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x43846bu; native_call(m, m->esi);	/* 438469: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43846b: push 0x42200000 */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438470: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 438475: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x43847cu; native_call(m, m->edi);	/* 43847a: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43847c: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438481: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438485u; native_call(m, m->esi);	/* 438483: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 438485: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 43848b: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438491: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438492: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 438498: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43849b: push 0xc1200000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4384a0: push 0x41ef3333 */
	goto L_43872f;	/* 4384a5: jmp 0x43872f */
L_4384aa:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4384aa: test eax, eax */
	if (!m->zf) goto L_4380af;	/* 4384ac: jne 0x4380af */
L_4384b2:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4384b2: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4384b6: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4384b8: cmp eax, 3 */
	if (m->sf == m->of) goto L_43857a;	/* 4384bb: jge 0x43857a */
	m->esp -= 4; M32(m->esp) = 0x4384c3u; native_call(m, m->ebx);	/* 4384c1: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4384c3: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4384c8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4384ccu; native_call(m, m->esi);	/* 4384ca: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4384cc: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4384d0: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4384d6: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 4384da: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4384e0: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4384e4: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4384e8: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4384ee: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4384f2: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4384f6: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4384f7: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4384fb: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4384ff: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438500: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x438507u; native_call(m, m->edi);	/* 438505: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438507: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43850c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438513u; native_call(m, m->esi);	/* 438511: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 438513: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 438517: fsub dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 43851d: mov ecx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 438521: fstp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 438525: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438529: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43852a: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43852b: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x438532u; native_call(m, m->edi);	/* 438530: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438532: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438537: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43853eu; native_call(m, m->esi);	/* 43853c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 43853e: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 438542: fsub dword ptr [0x4a9418] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 438548: mov edx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43854c: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 43854d: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438551: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438555: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438556: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x43855du; native_call(m, m->edi);	/* 43855b: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43855d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 438562: push 0 */
	m->esp -= 4; M32(m->esp) = 0x438566u; native_call(m, m->esi);	/* 438564: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 438566: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 43856a: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43856e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43856f: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438570: push 0xc1f00000 */
	goto L_43872f;	/* 438575: jmp 0x43872f */
L_43857a:
	m->esp -= 4; M32(m->esp) = 0x43857cu; native_call(m, m->ebx);	/* 43857a: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43857c: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438581: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x438588u; native_call(m, m->esi);	/* 438586: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 438588: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 43858c: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 438592: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 438596: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 43859c: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4385a0: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 4385a4: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4385aa: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4385ae: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4385b2: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4385b3: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4385b7: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4385bb: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4385bc: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4385c3u; native_call(m, m->edi);	/* 4385c1: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4385c3: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4385c8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4385ccu; native_call(m, m->esi);	/* 4385ca: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4385cc: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4385d0: fadd dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4385d6: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4385da: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4385de: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4385e2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4385e3: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4385e4: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4385ebu; native_call(m, m->edi);	/* 4385e9: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4385eb: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4385f0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4385f4u; native_call(m, m->esi);	/* 4385f2: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4385f4: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4385f8: fsub dword ptr [0x4a9418] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4385fe: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438602: push ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438603: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 438607: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43860b: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43860c: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x438613u; native_call(m, m->edi);	/* 438611: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438613: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438618: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43861fu; native_call(m, m->esi);	/* 43861d: call esi */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 43861f: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 438623: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438627: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438628: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438629: push 0x41f00000 */
	goto L_43872f;	/* 43862e: jmp 0x43872f */
L_438633:
	m->esp -= 4; M32(m->esp) = 0x438635u; native_call(m, m->ebx);	/* 438633: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 438635: fild dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 438639: mov ecx, dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9478u));	/* 43863d: fmul dword ptr [0x4a9478] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 438643: fst dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 438647: fadd dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 43864b: fstp dword ptr [esp + 0x24] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 43864f: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438653: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438654: push ecx */
	m->esp -= 4; M32(m->esp) = 0x438657u; native_call(m, m->esi);	/* 438655: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 438657: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 43865b: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 438661: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 438665: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 43866b: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 43866f: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 438673: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 438679: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 43867d: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438681: push edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438682: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 438686: fild dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 43868a: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43868e: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 43868f: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 438695: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 43869b: fstp dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 43869f: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4386a3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4386a6u; native_call(m, m->edi);	/* 4386a4: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4386a6: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 4386aa: fadd dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4386ae: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4386b2: push edx */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4386b3: fstp dword ptr [esp + 0x50] */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 4386b7: mov eax, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4386bb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4386beu; native_call(m, m->esi);	/* 4386bc: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4386be: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4386c2: fadd dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4386c8: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 4386cc: mov eax, dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4386d0: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4386d4: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4386d8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4386d9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4386da: push eax */
	m->esp -= 4; M32(m->esp) = 0x4386ddu; native_call(m, m->edi);	/* 4386db: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4386dd: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 4386e1: fadd dword ptr [esp + 0x48] */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 4386e5: mov edx, dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4386e9: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4386ed: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4386f1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4386f2: push edx */
	m->esp -= 4; M32(m->esp) = 0x4386f5u; native_call(m, m->esi);	/* 4386f3: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4386f5: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 4386f9: fsub dword ptr [0x4a9418] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4386ff: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 438703: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 438707: push eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 438708: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 43870c: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 438710: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 438711: push edx */
	m->esp -= 4; M32(m->esp) = 0x438714u; native_call(m, m->edi);	/* 438712: call edi */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 438714: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 438718: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43871c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43871d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x438720u; native_call(m, m->esi);	/* 43871e: call esi */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 438720: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 438724: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 438728: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43872c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43872d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43872e: push ecx */
L_43872f:
	m->esp -= 4; M32(m->esp) = 0x438731u; native_call(m, m->edi);	/* 43872f: call edi */
	m->esp -= 4; M32(m->esp) = 0x438733u; native_call(m, m->ebp);	/* 438731: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 438733: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 438737: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438738: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 43873b: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_437fc2;	/* 43873f: jl 0x437fc2 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 438745: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 438749: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43874a: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 43874d: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_437eee;	/* 438751: jl 0x437eee */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 438757: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x438762u; native_call(m, M32(0x4a922cu));	/* 43875c: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 438762: mov eax, dword ptr [0x680398] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 438767: test eax, eax */
	if (m->zf) goto L_4387cd;	/* 438769: je 0x4387cd */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 43876b: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 438771: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 438777: fadd dword ptr [0x680ccc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 43877d: fst dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 438783: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 438789: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43878b: test ah, 0x41 */
	if (m->zf) goto L_4387a6;	/* 43878e: je 0x4387a6 */
	M32((DWORD)(0x680cccu)) = 0x40000000u;	/* 438790: mov dword ptr [0x680ccc], 0x40000000 */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 43879a: mov dword ptr [0x4df454], 0x3f800000 */
	goto L_4387cd;	/* 4387a4: jmp 0x4387cd */
L_4387a6:
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 4387a6: fld dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 4387ac: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4387b2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4387b4: test ah, 1 */
	if (!m->zf) goto L_4387cd;	/* 4387b7: jne 0x4387cd */
	M32((DWORD)(0x680cccu)) = 0x42180000u;	/* 4387b9: mov dword ptr [0x680ccc], 0x42180000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 4387c3: mov dword ptr [0x4df454], 0xbf800000 */
L_4387cd:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 4387cd: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 4387d3: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 4387d9: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 4387df: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4387e5: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4387eb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4387ed: test ah, 0x41 */
	if (m->zf) goto L_438808;	/* 4387f0: je 0x438808 */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 4387f2: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 4387fc: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_43882f;	/* 438806: jmp 0x43882f */
L_438808:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 438808: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 43880e: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 438814: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 438816: test ah, 1 */
	if (!m->zf) goto L_43882f;	/* 438819: jne 0x43882f */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 43881b: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 438825: mov dword ptr [0x4df010], 0xbf800000 */
L_43882f:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 43882f: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 438835: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 43883b: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 438841: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 438847: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43884d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43884f: test ah, 1 */
	if (!m->zf) goto L_43885e;	/* 438852: jne 0x43885e */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 438854: mov dword ptr [0x4e14fc], 0 */
L_43885e:
	m->esi = M32((DWORD)(m->esp + 0x3cu));	/* 43885e: mov esi, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->esi, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438862: cmp esi, -1 */
	if (m->zf) goto L_4388bc;	/* 438865: je 0x4388bc */
	{ DWORD a_ = M32((DWORD)(0x9dce48u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 438867: cmp dword ptr [0x9dce48], 2 */
	if (!m->zf) goto L_4388bc;	/* 43886e: jne 0x4388bc */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 438870: push 2 */
	m->esp -= 4; M32(m->esp) = 0x438877u; native_call(m, 0x41ef90u);	/* 438872: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 438877: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x438880u; native_call(m, M32(0x4a9218u));	/* 43887a: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438880: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 438885: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43888a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43888f: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 438894: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43889eu; native_call(m, 0x41f0e0u);	/* 438899: call 0x41f0e0 */
	{ DWORD a_ = m->esi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 43889e: shl esi, 7 */
	{ DWORD a_ = m->esi, b_ = 0x750ba4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4388a1: add esi, 0x750ba4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4388a7: push esi */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 4388a8: push 0x280 */
	{ DWORD v_ = 0x1bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 4388ad: push 0x1bc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4388b2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4388b9u; native_call(m, 0x4029d0u);	/* 4388b4: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4388b9: add esp, 0x24 */
L_4388bc:
	m->edi = M32(m->esp); m->esp += 4;	/* 4388bc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4388bd: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4388be: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4388bf: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4388c0: add esp, 0x4c */
	m->esp += 4 + 0; return;	/* 4388c3: ret  */
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
