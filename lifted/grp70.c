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

static void lift_423330(X86 *m);
static void lift_423e50(X86 *m);

/* setup_423e50 (0x423e50), lifted by tools/lift.py */
static void lift_423e50(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423e50: sub esp, 0x40 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 423e53: push 1 */
	m->esp -= 4; M32(m->esp) = 0x423e5au; native_call(m, 0x41ef90u);	/* 423e55: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423e5a: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 423e5d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x423e68u; native_call(m, M32(0x4a9224u));	/* 423e62: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x4ddcecu));	/* 423e68: mov eax, dword ptr [0x4ddcec] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423e6d: cmp eax, 1 */
	if (!m->zf) goto L_423e92;	/* 423e70: jne 0x423e92 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de038u)));	/* 423e72: fld dword ptr [0x4de038] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 423e78: fsub dword ptr [0x4a94fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 423e7e: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 423e84: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4de038u));	/* 423e8a: fsubr dword ptr [0x4de038] */
	goto L_423eb4;	/* 423e90: jmp 0x423eb4 */
L_423e92:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 423e92: test eax, eax */
	if (!m->zf) goto L_423eba;	/* 423e94: jne 0x423eba */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a942cu)));	/* 423e96: fld dword ptr [0x4a942c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4de038u));	/* 423e9c: fsub dword ptr [0x4de038] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 423ea2: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 423ea8: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4de038u));	/* 423eae: fadd dword ptr [0x4de038] */
L_423eb4:
	MF((DWORD)(0x4de038u)) = (float)ST(0); FPOP();	/* 423eb4: fstp dword ptr [0x4de038] */
L_423eba:
	m->eax = M32((DWORD)(0x4de038u));	/* 423eba: mov eax, dword ptr [0x4de038] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 423ebf: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 423ec0: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 423ec1: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 423ec2: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423ec3: push eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423ec4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423ec9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423ece: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423ed9u; native_call(m, M32(0x4a9228u));	/* 423ed3: call dword ptr [0x4a9228] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 423ed9: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 423edf: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 423ee5: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 423eeb: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 423ef1: xor eax, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 423ef3: mov dword ptr [esp + 0x24], eax */
L_423ef7:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423ef7: cmp eax, 3 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 423efa: mov dword ptr [esp + 0x1c], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3f000000u;	/* 423f02: mov dword ptr [esp + 0x34], 0x3f000000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x0u;	/* 423f0a: mov dword ptr [esp + 0x44], 0 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3e800000u;	/* 423f12: mov dword ptr [esp + 0x48], 0x3e800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f000000u;	/* 423f1a: mov dword ptr [esp + 0x3c], 0x3f000000 */
	if (!m->zf) goto L_423f4e;	/* 423f22: jne 0x423f4e */
	M32((DWORD)(m->esp + 0x1cu)) = 0x3f000000u;	/* 423f24: mov dword ptr [esp + 0x1c], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 423f2c: mov dword ptr [esp + 0x34], 0 */
	M32((DWORD)(m->esp + 0x44u)) = 0x3f000000u;	/* 423f34: mov dword ptr [esp + 0x44], 0x3f000000 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3f400000u;	/* 423f3c: mov dword ptr [esp + 0x48], 0x3f400000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f800000u;	/* 423f44: mov dword ptr [esp + 0x3c], 0x3f800000 */
	goto L_423f54;	/* 423f4c: jmp 0x423f54 */
L_423f4e:
	if (!m->cf && !m->zf) goto L_424041;	/* 423f4e: ja 0x424041 */
L_423f54:
	switch (m->eax) { case 0: goto L_423f5b; case 1: goto L_423f78; case 2: goto L_42474b; case 3: goto L_423f97; default: abort(); }	/* 423f54: jmp dword ptr [eax*4 + 0x424800] */
L_423f5b:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 423f5b: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 423f61: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423f67: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4de038u));	/* 423f68: fsubr dword ptr [0x4de038] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 423f6e: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423f71: push 0x3f800000 */
	goto L_423f82;	/* 423f76: jmp 0x423f82 */
L_423f78:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 423f78: push 0x3ecccccd */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423f7d: push 0x41200000 */
L_423f82:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423f82: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423f87: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423f92u; native_call(m, M32(0x4a9228u));	/* 423f8c: call dword ptr [0x4a9228] */
	goto L_42404a;	/* 423f92: jmp 0x42404a */
L_423f97:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de038u)));	/* 423f97: fld dword ptr [0x4de038] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 423f9d: fadd dword ptr [0x4a94f8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423fa3: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 423fa4: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423fa7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423fac: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423fb1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423fbcu; native_call(m, M32(0x4a9228u));	/* 423fb6: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 423fbc: mov eax, dword ptr [esp + 0x24] */
L_423fc0:
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 423fc0: shl eax, 2 */
	m->ecx = 0x5b1984u;	/* 423fc3: mov ecx, 0x5b1984 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 423fc8: sub ecx, eax */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 423fca: mov eax, dword ptr [ecx] */
	m->edx = m->eax;	/* 423fcc: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 423fce: and edx, 0x800001ff */
	if (!m->sf) goto L_423fde;	/* 423fd4: jns 0x423fde */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 423fd6: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 423fd7: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 423fdd: inc edx */
L_423fde:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423fde: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 423fdf: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 423fe5: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 423fe6: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 423fec: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 423fee: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 423ff1: mov ecx, dword ptr [ecx + eax*4 + 4] */
L_423ff5:
	m->esp -= 4; M32(m->esp) = 0x423ffau; native_call(m, 0x4566c0u);	/* 423ff5: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 423ffa: mov dword ptr [esp + 0x20], 0 */
L_424002:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 424002: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 424006: and eax, 0x80000001 */
	if (!m->sf) goto L_424012;	/* 42400b: jns 0x424012 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 42400d: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42400e: or eax, 0xfffffffe */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 424011: inc eax */
L_424012:
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 424012: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x42401bu; native_call(m, 0x41f050u);	/* 424016: call 0x41f050 */
	m->edx = M32((DWORD)(0x4ddd90u));	/* 42401b: mov edx, dword ptr [0x4ddd90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424021: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424022: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424024: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42402cu; native_call(m, M32(0x4a9214u));	/* 424026: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42402c: cmp dword ptr [esp + 0x20], 2 */
	if (m->sf == m->of) goto L_42407d;	/* 424031: jge 0x42407d */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 424033: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b04c4u));	/* 424037: mov ecx, dword ptr [eax*4 + 0x4b04c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42403e: push ecx */
	goto L_42408e;	/* 42403f: jmp 0x42408e */
L_424041:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 424041: cmp eax, 2 */
	if (m->sf == m->of) goto L_423fc0;	/* 424044: jge 0x423fc0 */
L_42404a:
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 42404a: mov eax, dword ptr [0x4e0cd0] */
	m->ecx = m->eax;	/* 42404f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 424051: and ecx, 0x800001ff */
	if (!m->sf) goto L_424061;	/* 424057: jns 0x424061 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 424059: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42405a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 424060: inc ecx */
L_424061:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 424061: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 424062: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424068: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424069: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 42406b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 424071: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 424074: mov ecx, dword ptr [edx + eax*4 + 4] */
	goto L_423ff5;	/* 424078: jmp 0x423ff5 */
L_42407d:
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 42407d: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424081: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx*4 + 0x4b04c4u)));	/* 424082: fld dword ptr [edx*4 + 0x4b04c4] */
	ST(0) = -ST(0);	/* 424089: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42408b: fstp dword ptr [esp] */
L_42408e:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42408e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424090: push 0 */
	m->esp -= 4; M32(m->esp) = 0x424097u; native_call(m, 0x41ef20u);	/* 424092: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 424097: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42409b: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42409e: cmp eax, 1 */
	if (!m->zf) goto L_424370;	/* 4240a1: jne 0x424370 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4240a7: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4240ab: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4240ad: cmp eax, 2 */
	if (m->sf == m->of) goto L_42421f;	/* 4240b0: jge 0x42421f */
	m->esp -= 4; M32(m->esp) = 0x4240b8u; native_call(m, m->ebx);	/* 4240b6: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4240b8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4240ba: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4240beu; native_call(m, m->esi);	/* 4240bc: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4240be: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4240c4: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4240ca: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4240cb: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4240d1: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4240d4: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4240d9: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4240e0u; native_call(m, m->edi);	/* 4240de: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4240e0: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4240e6: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4240ec: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4240ee: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4240ef: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4240f5: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4240fau; native_call(m, m->esi);	/* 4240f8: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4240fa: push 0xc2200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4240ff: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 424104: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x42410bu; native_call(m, m->edi);	/* 424109: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42410b: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 424111: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424117: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42411c: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 42411d: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424123: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x424128u; native_call(m, m->esi);	/* 424126: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424128: push 0xc2200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42412d: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 424132: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x424139u; native_call(m, m->edi);	/* 424137: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424139: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42413e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x424142u; native_call(m, m->esi);	/* 424140: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 424142: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 424148: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42414e: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 42414f: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424155: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424158: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42415d: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x424164u; native_call(m, m->edi);	/* 424162: call edi */
	m->esp -= 4; M32(m->esp) = 0x424166u; native_call(m, m->ebp);	/* 424164: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424166: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42416au; native_call(m, m->ebx);	/* 424168: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42416a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 424170: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424176: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424178: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 424179: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42417f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x424184u; native_call(m, m->esi);	/* 424182: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424184: push 0x42200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424189: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42418e: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x424195u; native_call(m, m->edi);	/* 424193: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424195: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424197: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42419eu; native_call(m, m->esi);	/* 42419c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42419e: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4241a4: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4241aa: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4241ab: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4241b1: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4241b4: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4241b9: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4241c0u; native_call(m, m->edi);	/* 4241be: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4241c0: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4241c5: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4241ccu; native_call(m, m->esi);	/* 4241ca: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4241cc: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4241d2: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4241d8: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4241d9: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4241df: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4241e2: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4241e7: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4241eeu; native_call(m, m->edi);	/* 4241ec: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4241ee: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4241f4: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4241fa: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4241ff: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 424200: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424206: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x42420bu; native_call(m, m->esi);	/* 424209: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42420b: push 0x42200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424210: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 424215: push 0xc1ef3333 */
	goto L_424731;	/* 42421a: jmp 0x424731 */
L_42421f:
	m->esp -= 4; M32(m->esp) = 0x424221u; native_call(m, m->ebx);	/* 42421f: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 424221: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 424227: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42422d: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42422f: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424230: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x424235u; native_call(m, m->esi);	/* 424233: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424235: push 0xc2200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42423a: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42423f: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x424246u; native_call(m, m->edi);	/* 424244: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424246: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424248: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42424fu; native_call(m, m->esi);	/* 42424d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42424f: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 424255: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42425b: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 42425c: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424262: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424265: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42426a: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x424271u; native_call(m, m->edi);	/* 42426f: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424271: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424276: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42427du; native_call(m, m->esi);	/* 42427b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42427d: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 424283: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424289: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 42428a: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424290: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424293: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 424298: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x42429fu; native_call(m, m->edi);	/* 42429d: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42429f: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4242a5: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242ab: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4242b0: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4242b1: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4242b6u; native_call(m, m->esi);	/* 4242b4: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242b6: push 0xc2200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242bb: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242c0: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4242c7u; native_call(m, m->edi);	/* 4242c5: call edi */
	m->esp -= 4; M32(m->esp) = 0x4242c9u; native_call(m, m->ebp);	/* 4242c7: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242c9: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4242cdu; native_call(m, m->ebx);	/* 4242cb: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242cd: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242cf: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4242d3u; native_call(m, m->esi);	/* 4242d1: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4242d3: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4242d9: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4242df: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4242e0: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4242e6: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242e9: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4242ee: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4242f5u; native_call(m, m->edi);	/* 4242f3: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4242f5: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4242fb: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424301: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424303: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424304: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x424309u; native_call(m, m->esi);	/* 424307: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424309: push 0x42200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42430e: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 424313: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x42431au; native_call(m, m->edi);	/* 424318: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42431a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 424320: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424326: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42432b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42432c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x424331u; native_call(m, m->esi);	/* 42432f: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424331: push 0x42200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424336: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42433b: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x424342u; native_call(m, m->edi);	/* 424340: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424342: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424347: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42434bu; native_call(m, m->esi);	/* 424349: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42434b: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 424351: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424357: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 424358: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42435e: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424361: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 424366: push 0x41ef3333 */
	goto L_424731;	/* 42436b: jmp 0x424731 */
L_424370:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 424370: test eax, eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 424372: mov eax, dword ptr [esp + 0x20] */
	if (!m->zf) goto L_424515;	/* 424376: jne 0x424515 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42437c: cmp eax, 2 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42437f: push 7 */
	if (m->sf == m->of) goto L_42444e;	/* 424381: jge 0x42444e */
	m->esp -= 4; M32(m->esp) = 0x424389u; native_call(m, m->ebx);	/* 424387: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424389: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42438e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x424392u; native_call(m, m->esi);	/* 424390: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 424392: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 424396: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 42439c: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 4243a0: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4243a6: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4243aa: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4243ae: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4243b2: fmul dword ptr [0x4a9410] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 4243b8: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4243bc: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4243bd: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 4243c1: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 4243c7: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4243cb: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4243cf: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4243d3: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4243d4: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x4243dbu; native_call(m, m->edi);	/* 4243d9: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4243db: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4243e0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4243e7u; native_call(m, m->esi);	/* 4243e5: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4243e7: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4243eb: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4243f1: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4243f5: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4243f9: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4243fd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4243fe: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4243ff: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x424406u; native_call(m, m->edi);	/* 424404: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424406: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42440b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424412u; native_call(m, m->esi);	/* 424410: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 424412: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 424416: fsub dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 42441c: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424420: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 424421: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 424425: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424429: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42442a: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x424431u; native_call(m, m->edi);	/* 42442f: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424431: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424436: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42443au; native_call(m, m->esi);	/* 424438: call esi */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 42443a: mov eax, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 42443e: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424442: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424443: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424444: push 0xc1f00000 */
	goto L_424731;	/* 424449: jmp 0x424731 */
L_42444e:
	m->esp -= 4; M32(m->esp) = 0x424450u; native_call(m, m->ebx);	/* 42444e: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424450: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424455: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42445cu; native_call(m, m->esi);	/* 42445a: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 42445c: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 424460: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 424466: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 42446a: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 424470: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 424474: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 424478: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 42447c: fmul dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 424482: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424486: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 424487: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 42448b: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 424491: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 424495: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 424499: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42449d: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42449e: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4244a5u; native_call(m, m->edi);	/* 4244a3: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4244a5: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4244aa: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4244aeu; native_call(m, m->esi);	/* 4244ac: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4244ae: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4244b2: fadd dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4244b8: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4244bc: fstp dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4244c0: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4244c4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4244c5: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4244c6: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4244cdu; native_call(m, m->edi);	/* 4244cb: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4244cd: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4244d2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4244d6u; native_call(m, m->esi);	/* 4244d4: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4244d6: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4244da: fsub dword ptr [0x4a9410] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 4244e0: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4244e4: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4244e5: fstp dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4244e9: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4244ed: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4244ee: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x4244f5u; native_call(m, m->edi);	/* 4244f3: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4244f5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4244fa: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424501u; native_call(m, m->esi);	/* 4244ff: call esi */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 424501: mov edx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 424505: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424509: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42450a: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42450b: push 0x41f00000 */
	goto L_424731;	/* 424510: jmp 0x424731 */
L_424515:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 424515: cmp eax, 2 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424518: push 7 */
	if (m->sf == m->of) goto L_424627;	/* 42451a: jge 0x424627 */
	m->esp -= 4; M32(m->esp) = 0x424522u; native_call(m, m->ebx);	/* 424520: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 424522: fild dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 424526: fst dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 42452a: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 424530: fstp dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 424534: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424538: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424539: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42453du; native_call(m, m->esi);	/* 42453b: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 42453d: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 424541: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 424547: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 42454b: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 424551: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 424555: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 424559: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 42455d: fmul dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 424563: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424567: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 424568: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 42456c: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 424572: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 424576: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 42457a: fild dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 42457e: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424582: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 424583: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 424589: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 42458f: fstp dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 424593: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424597: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42459au; native_call(m, m->edi);	/* 424598: call edi */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 42459a: mov edx, dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 42459e: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = m->edx;	/* 4245a2: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4245a4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4245a5: push ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 4245a6: mov dword ptr [esp + 0x48], edx */
	m->esp -= 4; M32(m->esp) = 0x4245acu; native_call(m, m->esi);	/* 4245aa: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4245ac: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4245b0: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4245b6: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4245ba: mov ecx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4245be: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4245c2: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4245c6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4245c7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4245c8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4245cbu; native_call(m, m->edi);	/* 4245c9: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4245cb: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4245cf: fadd dword ptr [0x4a9424] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 4245d5: mov eax, dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 4245d9: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4245df: fstp dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 4245e3: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4245e7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4245e8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4245ebu; native_call(m, m->esi);	/* 4245e9: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4245eb: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4245ef: fsub dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4245f5: mov ecx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4245f9: mov eax, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4245fd: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4245fe: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 424602: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424606: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424607: push eax */
	m->esp -= 4; M32(m->esp) = 0x42460au; native_call(m, m->edi);	/* 424608: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 42460a: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42460e: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42460f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x424613u; native_call(m, m->esi);	/* 424611: call esi */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 424613: mov edx, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 424617: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 42461b: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42461f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424620: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424621: push ecx */
	goto L_424731;	/* 424622: jmp 0x424731 */
L_424627:
	m->esp -= 4; M32(m->esp) = 0x424629u; native_call(m, m->ebx);	/* 424627: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 424629: fild dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 42462d: mov eax, dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 424631: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 424637: fst dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 42463b: fadd dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 42463f: fstp dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 424643: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424647: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424648: push eax */
	m->esp -= 4; M32(m->esp) = 0x42464bu; native_call(m, m->esi);	/* 424649: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 42464b: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 42464f: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 424655: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 424659: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 42465f: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 424663: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 424667: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 42466b: fmul dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 424671: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424675: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 424676: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 42467a: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 424680: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 424684: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 424688: fild dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 42468c: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424690: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 424691: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 424697: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 42469d: fstp dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 4246a1: mov eax, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4246a5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4246a8u; native_call(m, m->edi);	/* 4246a6: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4246a8: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 4246ac: fadd dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4246b0: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4246b4: push ecx */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4246b5: fstp dword ptr [esp + 0x50] */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 4246b9: mov edx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4246bd: push edx */
	m->esp -= 4; M32(m->esp) = 0x4246c0u; native_call(m, m->esi);	/* 4246be: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4246c0: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4246c4: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4246ca: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 4246ce: mov edx, dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4246d2: fstp dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 4246d6: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4246da: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4246db: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4246dc: push edx */
	m->esp -= 4; M32(m->esp) = 0x4246dfu; native_call(m, m->edi);	/* 4246dd: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4246df: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 4246e3: fadd dword ptr [esp + 0x48] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 4246e7: mov ecx, dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4246eb: fstp dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4246ef: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4246f3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4246f4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4246f7u; native_call(m, m->esi);	/* 4246f5: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4246f7: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4246fb: fsub dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 424701: mov edx, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 424705: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424709: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 42470a: fstp dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 42470e: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424712: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424713: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424716u; native_call(m, m->edi);	/* 424714: call edi */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 424716: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 42471a: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42471e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42471f: push eax */
	m->esp -= 4; M32(m->esp) = 0x424722u; native_call(m, m->esi);	/* 424720: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 424722: mov ecx, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 424726: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 42472a: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42472e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42472f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424730: push eax */
L_424731:
	m->esp -= 4; M32(m->esp) = 0x424733u; native_call(m, m->edi);	/* 424731: call edi */
	m->esp -= 4; M32(m->esp) = 0x424735u; native_call(m, m->ebp);	/* 424733: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 424735: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 424739: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42473a: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 42473d: mov dword ptr [esp + 0x20], eax */
	if (m->sf != m->of) goto L_424002;	/* 424741: jl 0x424002 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 424747: mov eax, dword ptr [esp + 0x24] */
L_42474b:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 42474b: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42474c: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 42474f: mov dword ptr [esp + 0x24], eax */
	if (m->sf != m->of) goto L_423ef7;	/* 424753: jl 0x423ef7 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 424759: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x424764u; native_call(m, M32(0x4a922cu));	/* 42475e: call dword ptr [0x4a922c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 424764: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 42476a: fmul dword ptr [0x4b071c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 424770: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 424771: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 424772: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 424773: pop ebx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 424774: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 42477a: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 424780: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 424786: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 424788: test ah, 0x41 */
	if (m->zf) goto L_4247a3;	/* 42478b: je 0x4247a3 */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 42478d: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 424797: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_4247ca;	/* 4247a1: jmp 0x4247ca */
L_4247a3:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 4247a3: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 4247a9: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4247af: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4247b1: test ah, 1 */
	if (!m->zf) goto L_4247ca;	/* 4247b4: jne 0x4247ca */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 4247b6: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 4247c0: mov dword ptr [0x4df010], 0xbf800000 */
L_4247ca:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 4247ca: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 4247d0: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 4247d6: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 4247dc: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 4247e2: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4247e8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4247ea: test ah, 1 */
	if (!m->zf) goto L_4247f9;	/* 4247ed: jne 0x4247f9 */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 4247ef: mov dword ptr [0x4e14fc], 0 */
L_4247f9:
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4247f9: add esp, 0x40 */
	m->esp += 4 + 0; return;	/* 4247fc: ret  */
}

/* setup_423330 (0x423330), lifted by tools/lift.py */
static void lift_423330(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423330: sub esp, 0x44 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 423333: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 423334: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 423335: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 423336: push edi */
	M32((DWORD)(m->esp + 0x3cu)) = 0xffffffffu;	/* 423337: mov dword ptr [esp + 0x3c], 0xffffffff */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 42333f: xor ebp, ebp */
	m->ebx = 0x4df918u;	/* 423341: mov ebx, 0x4df918 */
L_423346:
	m->eax = M32((DWORD)(0x4dda60u));	/* 423346: mov eax, dword ptr [0x4dda60] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42334b: test eax, eax */
	if (!m->zf) goto L_423398;	/* 42334d: jne 0x423398 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 42334f: mov eax, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423354: sub esp, 0x2c */
	m->ecx = 0xbu;	/* 423357: mov ecx, 0xb */
	m->esi = m->ebx;	/* 42335c: mov esi, ebx */
	m->edi = m->esp;	/* 42335e: mov edi, esp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423360: push eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 423361: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 423363: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423369: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42336fu; native_call(m, 0x41eea0u);	/* 42336a: call 0x41eea0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42336f: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423372: cmp eax, 1 */
	if (m->zf) goto L_42338f;	/* 423375: je 0x42338f */
	{ DWORD a_ = m->ebx, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 423377: add ebx, 0x2c */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 42337a: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x4df9c8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42337b: cmp ebx, 0x4df9c8 */
	if (m->sf != m->of) goto L_423346;	/* 423381: jl 0x423346 */
	M32((DWORD)(0x680398u)) = 0x0u;	/* 423383: mov dword ptr [0x680398], 0 */
	goto L_4233d1;	/* 42338d: jmp 0x4233d1 */
L_42338f:
	{ DWORD a_ = m->ebp, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42338f: cmp ebp, -1 */
	M32((DWORD)(m->esp + 0x3cu)) = m->ebp;	/* 423392: mov dword ptr [esp + 0x3c], ebp */
	if (!m->zf) goto L_4233a4;	/* 423396: jne 0x4233a4 */
L_423398:
	M32((DWORD)(0x680398u)) = 0x0u;	/* 423398: mov dword ptr [0x680398], 0 */
	goto L_4233d1;	/* 4233a2: jmp 0x4233d1 */
L_4233a4:
	m->eax = M32((DWORD)(0x907b24u));	/* 4233a4: mov eax, dword ptr [0x907b24] */
	M32((DWORD)(0x680398u)) = 0x1u;	/* 4233a9: mov dword ptr [0x680398], 1 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4233b3: cmp eax, ebp */
	if (m->zf) goto L_4233d1;	/* 4233b5: je 0x4233d1 */
	M32((DWORD)(0x907b24u)) = m->ebp;	/* 4233b7: mov dword ptr [0x907b24], ebp */
	M32((DWORD)(0x680cccu)) = 0x42200000u;	/* 4233bd: mov dword ptr [0x680ccc], 0x42200000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 4233c7: mov dword ptr [0x4df454], 0xbf800000 */
L_4233d1:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4233d1: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4233d8u; native_call(m, 0x41ef90u);	/* 4233d3: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4233d8: add esp, 4 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4233db: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4233e6u; native_call(m, M32(0x4a9224u));	/* 4233e0: call dword ptr [0x4a9224] */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 4233e6: mov ebx, dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 4233ec: mov esi, dword ptr [0x4a920c] */
	m->edi = M32((DWORD)(0x4a9210u));	/* 4233f2: mov edi, dword ptr [0x4a9210] */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 4233f8: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4233fe: xor eax, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 423400: mov dword ptr [esp + 0x24], eax */
	goto L_42340a;	/* 423404: jmp 0x42340a */
L_423406:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 423406: mov eax, dword ptr [esp + 0x24] */
L_42340a:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42340a: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 42340d: mov dword ptr [esp + 0x1c], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3f000000u;	/* 423415: mov dword ptr [esp + 0x34], 0x3f000000 */
	M32((DWORD)(m->esp + 0x48u)) = 0x0u;	/* 42341d: mov dword ptr [esp + 0x48], 0 */
	M32((DWORD)(m->esp + 0x4cu)) = 0x3e800000u;	/* 423425: mov dword ptr [esp + 0x4c], 0x3e800000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3f000000u;	/* 42342d: mov dword ptr [esp + 0x40], 0x3f000000 */
	if (m->zf || m->sf != m->of) goto L_42345f;	/* 423435: jle 0x42345f */
	M32((DWORD)(m->esp + 0x1cu)) = 0x3f000000u;	/* 423437: mov dword ptr [esp + 0x1c], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 42343f: mov dword ptr [esp + 0x34], 0 */
	M32((DWORD)(m->esp + 0x48u)) = 0x3f000000u;	/* 423447: mov dword ptr [esp + 0x48], 0x3f000000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0x3f400000u;	/* 42344f: mov dword ptr [esp + 0x4c], 0x3f400000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x3f800000u;	/* 423457: mov dword ptr [esp + 0x40], 0x3f800000 */
L_42345f:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42345f: cmp eax, 2 */
	if (m->sf == m->of) goto L_423494;	/* 423462: jge 0x423494 */
	m->eax = M32((DWORD)(0x4e0cd0u));	/* 423464: mov eax, dword ptr [0x4e0cd0] */
	m->edx = m->eax;	/* 423469: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42346b: and edx, 0x800001ff */
	if (!m->sf) goto L_42347b;	/* 423471: jns 0x42347b */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 423473: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 423474: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 42347a: inc edx */
L_42347b:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42347b: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 42347c: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 423482: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 423483: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 423489: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42348b: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 42348e: mov ecx, dword ptr [ecx + eax*4 + 4] */
	goto L_4234cd;	/* 423492: jmp 0x4234cd */
L_423494:
	m->edx = (DWORD)(m->eax*4 + 0x0u);	/* 423494: lea edx, [eax*4] */
	m->eax = 0x5b1984u;	/* 42349b: mov eax, 0x5b1984 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4234a0: sub eax, edx */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 4234a2: mov eax, dword ptr [eax] */
	m->ecx = m->eax;	/* 4234a4: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4234a6: and ecx, 0x800001ff */
	if (!m->sf) goto L_4234b6;	/* 4234ac: jns 0x4234b6 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4234ae: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4234af: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4234b5: inc ecx */
L_4234b6:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4234b6: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4234b7: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4234bd: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4234be: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4234c0: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4234c6: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4234c9: mov ecx, dword ptr [edx + eax*4 + 4] */
L_4234cd:
	m->esp -= 4; M32(m->esp) = 0x4234d2u; native_call(m, 0x4566c0u);	/* 4234cd: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 4234d2: mov dword ptr [esp + 0x20], 0 */
L_4234da:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4234da: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4234de: and eax, 0x80000001 */
	if (!m->sf) goto L_4234ea;	/* 4234e3: jns 0x4234ea */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4234e5: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4234e6: or eax, 0xfffffffe */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4234e9: inc eax */
L_4234ea:
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 4234ea: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x4234f3u; native_call(m, 0x41f050u);	/* 4234ee: call 0x41f050 */
	m->eax = M32((DWORD)(0x4ddd90u));	/* 4234f3: mov eax, dword ptr [0x4ddd90] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4234f8: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4234f9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4234fb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423503u; native_call(m, M32(0x4a9214u));	/* 4234fd: call dword ptr [0x4a9214] */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x20u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423503: cmp dword ptr [esp + 0x20], 2 */
	if (m->sf == m->of) goto L_423518;	/* 423508: jge 0x423518 */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 42350a: mov ecx, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->ecx*4 + 0x4b04c4u));	/* 42350e: mov edx, dword ptr [ecx*4 + 0x4b04c4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423515: push edx */
	goto L_423529;	/* 423516: jmp 0x423529 */
L_423518:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 423518: mov eax, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42351c: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax*4 + 0x4b04c4u)));	/* 42351d: fld dword ptr [eax*4 + 0x4b04c4] */
	ST(0) = -ST(0);	/* 423524: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 423526: fstp dword ptr [esp] */
L_423529:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423529: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42352b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423532u; native_call(m, 0x41ef20u);	/* 42352d: call 0x41ef20 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 423532: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423536: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423539: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_42371a;	/* 42353c: ja 0x42371a */
	switch (m->eax) { case 0: goto L_423549; case 1: goto L_423579; case 2: goto L_423598; case 3: goto L_4235c6; default: abort(); }	/* 423542: jmp dword ptr [eax*4 + 0x423e3c] */
L_423549:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 423549: fld dword ptr [0x9db978] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9430u));	/* 42354f: fmul dword ptr [0x4a9430] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423555: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 423556: fsubr dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42355c: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42355f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423564: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423569: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423574u; native_call(m, M32(0x4a9228u));	/* 42356e: call dword ptr [0x4a9228] */
	goto L_4239f4;	/* 423574: jmp 0x4239f4 */
L_423579:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 423579: push 0x3ecccccd */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42357e: push 0x41200000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423583: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423588: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423593u; native_call(m, M32(0x4a9228u));	/* 42358d: call dword ptr [0x4a9228] */
	goto L_423723;	/* 423593: jmp 0x423723 */
L_423598:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 423598: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 42359c: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4235a0: cmp eax, ecx */
	if (!m->zf) goto L_4235bc;	/* 4235a2: jne 0x4235bc */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 4235a4: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9428u));	/* 4235aa: fmul dword ptr [0x4a9428] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4235b0: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4235b1: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4235b7: fstp dword ptr [esp] */
	goto L_4235ef;	/* 4235ba: jmp 0x4235ef */
L_4235bc:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4235bc: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4235be: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4235c0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4235c2: push 0 */
	goto L_4235fe;	/* 4235c4: jmp 0x4235fe */
L_4235c6:
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4235c6: mov edx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 4235ca: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4235ce: cmp eax, edx */
	if (!m->zf) goto L_4235ea;	/* 4235d0: jne 0x4235ea */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 4235d2: fld dword ptr [0x680ccc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 4235d8: fmul dword ptr [0x4a9420] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4235de: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4235df: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4235e5: fstp dword ptr [esp] */
	goto L_4235ef;	/* 4235e8: jmp 0x4235ef */
L_4235ea:
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 4235ea: push 0x3f19999a */
L_4235ef:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4235ef: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4235f4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4235f9: push 0x3f800000 */
L_4235fe:
	m->esp -= 4; M32(m->esp) = 0x423604u; native_call(m, M32(0x4a9228u));	/* 4235fe: call dword ptr [0x4a9228] */
L_423604:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 423604: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 423608: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42360a: cmp eax, 2 */
	if (m->sf == m->of) goto L_423b91;	/* 42360d: jge 0x423b91 */
	m->esp -= 4; M32(m->esp) = 0x423615u; native_call(m, m->ebx);	/* 423613: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 423615: fild dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 423619: fst dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 42361d: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 423623: fstp dword ptr [esp + 0x2c] */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 423627: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42362b: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42362c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423630u; native_call(m, m->esi);	/* 42362e: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 423630: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 423634: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 42363a: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 42363e: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 423644: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 423648: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 42364c: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 423650: fmul dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 423656: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42365a: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 42365b: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 42365f: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 423665: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 423669: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 42366d: fild dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 423671: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423675: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 423676: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 42367c: fsub dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 423682: fstp dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 423686: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42368a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42368du; native_call(m, m->edi);	/* 42368b: call edi */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 42368d: mov edx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 423691: mov eax, dword ptr [esp + 0x2c] */
	m->ecx = m->edx;	/* 423695: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423697: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423698: push ecx */
	M32((DWORD)(m->esp + 0x4cu)) = m->edx;	/* 423699: mov dword ptr [esp + 0x4c], edx */
	m->esp -= 4; M32(m->esp) = 0x42369fu; native_call(m, m->esi);	/* 42369d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 42369f: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4236a3: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4236a9: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4236ad: mov ecx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4236b1: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4236b5: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4236b9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4236ba: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4236bb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4236beu; native_call(m, m->edi);	/* 4236bc: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 4236be: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4236c2: fadd dword ptr [0x4a9424] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 4236c8: mov eax, dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 4236cc: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4236d2: fstp dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 4236d6: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4236da: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4236db: push eax */
	m->esp -= 4; M32(m->esp) = 0x4236deu; native_call(m, m->esi);	/* 4236dc: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4236de: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 4236e2: fsub dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4236e8: mov ecx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4236ec: mov eax, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4236f0: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4236f1: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4236f5: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4236f9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4236fa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4236fdu; native_call(m, m->edi);	/* 4236fb: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4236fd: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423701: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423702: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423706u; native_call(m, m->esi);	/* 423704: call esi */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 423706: mov edx, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 42370a: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 42370e: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423712: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423713: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423714: push ecx */
	goto L_423c9b;	/* 423715: jmp 0x423c9b */
L_42371a:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42371a: cmp eax, 1 */
	if (!m->zf) goto L_4239ec;	/* 42371d: jne 0x4239ec */
L_423723:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 423723: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 423727: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423729: cmp eax, 2 */
	if (m->sf == m->of) goto L_42389b;	/* 42372c: jge 0x42389b */
	m->esp -= 4; M32(m->esp) = 0x423734u; native_call(m, m->ebx);	/* 423732: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423734: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423736: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42373au; native_call(m, m->esi);	/* 423738: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42373a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 423740: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423746: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 423747: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42374d: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423750: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 423755: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x42375cu; native_call(m, m->edi);	/* 42375a: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42375c: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 423762: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423768: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42376a: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 42376b: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 423771: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x423776u; native_call(m, m->esi);	/* 423774: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423776: push 0xc2200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42377b: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 423780: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x423787u; native_call(m, m->edi);	/* 423785: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 423787: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 42378d: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423793: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423798: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 423799: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42379f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4237a4u; native_call(m, m->esi);	/* 4237a2: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237a4: push 0xc2200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237a9: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237ae: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4237b5u; native_call(m, m->edi);	/* 4237b3: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237b5: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237ba: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4237beu; native_call(m, m->esi);	/* 4237bc: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4237be: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4237c4: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4237ca: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4237cb: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4237d1: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237d4: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237d9: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4237e0u; native_call(m, m->edi);	/* 4237de: call edi */
	m->esp -= 4; M32(m->esp) = 0x4237e2u; native_call(m, m->ebp);	/* 4237e0: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237e2: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4237e6u; native_call(m, m->ebx);	/* 4237e4: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4237e6: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4237ec: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4237f2: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4237f4: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4237f5: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4237fb: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x423800u; native_call(m, m->esi);	/* 4237fe: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423800: push 0x42200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423805: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42380a: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x423811u; native_call(m, m->edi);	/* 42380f: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423811: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423813: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42381au; native_call(m, m->esi);	/* 423818: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42381a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 423820: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423826: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 423827: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42382d: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423830: push 0x41400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 423835: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x42383cu; native_call(m, m->edi);	/* 42383a: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42383c: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423841: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423848u; native_call(m, m->esi);	/* 423846: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 423848: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 42384e: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423854: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 423855: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42385b: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42385e: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 423863: push 0xc1ef3333 */
	m->esp -= 4; M32(m->esp) = 0x42386au; native_call(m, m->edi);	/* 423868: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42386a: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 423870: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423876: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42387b: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 42387c: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 423882: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x423887u; native_call(m, m->esi);	/* 423885: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423887: push 0x42200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42388c: push 0xc1400000 */
	{ DWORD v_ = 0xc1ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 423891: push 0xc1ef3333 */
	goto L_423c9b;	/* 423896: jmp 0x423c9b */
L_42389b:
	m->esp -= 4; M32(m->esp) = 0x42389du; native_call(m, m->ebx);	/* 42389b: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42389d: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 4238a3: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238a9: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4238ab: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4238ac: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4238b1u; native_call(m, m->esi);	/* 4238af: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238b1: push 0xc2200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238b6: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238bb: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4238c2u; native_call(m, m->edi);	/* 4238c0: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238c2: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238c4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4238cbu; native_call(m, m->esi);	/* 4238c9: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4238cb: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4238d1: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4238d7: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4238d8: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4238de: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238e1: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238e6: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4238edu; native_call(m, m->edi);	/* 4238eb: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238ed: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4238f2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4238f9u; native_call(m, m->esi);	/* 4238f7: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4238f9: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4238ff: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423905: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 423906: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42390c: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42390f: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 423914: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x42391bu; native_call(m, m->edi);	/* 423919: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42391b: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 423921: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423927: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42392c: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42392d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x423932u; native_call(m, m->esi);	/* 423930: call esi */
	{ DWORD v_ = 0xc2200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423932: push 0xc2200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423937: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42393c: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x423943u; native_call(m, m->edi);	/* 423941: call edi */
	m->esp -= 4; M32(m->esp) = 0x423945u; native_call(m, m->ebp);	/* 423943: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 423945: push 7 */
	m->esp -= 4; M32(m->esp) = 0x423949u; native_call(m, m->ebx);	/* 423947: call ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423949: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42394b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42394fu; native_call(m, m->esi);	/* 42394d: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 42394f: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 423955: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42395b: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 42395c: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 423962: fstp dword ptr [esp] */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423965: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42396a: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x423971u; native_call(m, m->edi);	/* 42396f: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 423971: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 423977: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42397d: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42397f: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 423980: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x423985u; native_call(m, m->esi);	/* 423983: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423985: push 0x42200000 */
	{ DWORD v_ = 0x41400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42398a: push 0x41400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 42398f: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x423996u; native_call(m, m->edi);	/* 423994: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 423996: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 42399c: fmul dword ptr [0x4a9404] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239a2: push 0x3f000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4239a7: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4239a8: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4239adu; native_call(m, m->esi);	/* 4239ab: call esi */
	{ DWORD v_ = 0x42200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239ad: push 0x42200000 */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239b2: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239b7: push 0x41ef3333 */
	m->esp -= 4; M32(m->esp) = 0x4239beu; native_call(m, m->edi);	/* 4239bc: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239be: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239c3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4239c7u; native_call(m, m->esi);	/* 4239c5: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e14fcu)));	/* 4239c7: fld dword ptr [0x4e14fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9408u));	/* 4239cd: fmul dword ptr [0x4a9408] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4239d3: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 4239d4: fsubr dword ptr [0x4a9414] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4239da: fstp dword ptr [esp] */
	{ DWORD v_ = 0xc1400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239dd: push 0xc1400000 */
	{ DWORD v_ = 0x41ef3333u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239e2: push 0x41ef3333 */
	goto L_423c9b;	/* 4239e7: jmp 0x423c9b */
L_4239ec:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4239ec: test eax, eax */
	if (!m->zf) goto L_423604;	/* 4239ee: jne 0x423604 */
L_4239f4:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4239f4: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4239f8: push 7 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4239fa: cmp eax, 2 */
	if (m->sf == m->of) goto L_423aca;	/* 4239fd: jge 0x423aca */
	m->esp -= 4; M32(m->esp) = 0x423a05u; native_call(m, m->ebx);	/* 423a03: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423a05: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423a0a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423a0eu; native_call(m, m->esi);	/* 423a0c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 423a0e: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 423a12: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 423a18: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9414u)));	/* 423a1c: fld dword ptr [0x4a9414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 423a22: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 423a26: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 423a2a: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 423a2e: fmul dword ptr [0x4a9410] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 423a34: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423a38: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 423a39: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 423a3d: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 423a43: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 423a47: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 423a4b: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423a4f: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423a50: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x423a57u; native_call(m, m->edi);	/* 423a55: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423a57: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423a5c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423a63u; native_call(m, m->esi);	/* 423a61: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 423a63: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 423a67: fsub dword ptr [0x4a9414] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 423a6d: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 423a71: fstp dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 423a75: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423a79: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423a7a: push eax */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423a7b: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x423a82u; native_call(m, m->edi);	/* 423a80: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423a82: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423a87: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423a8eu; native_call(m, m->esi);	/* 423a8c: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 423a8e: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 423a92: fsub dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 423a98: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423a9c: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 423a9d: fstp dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 423aa1: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423aa5: push edx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423aa6: push 0xc1f00000 */
	m->esp -= 4; M32(m->esp) = 0x423aadu; native_call(m, m->edi);	/* 423aab: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423aad: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423ab2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423ab6u; native_call(m, m->esi);	/* 423ab4: call esi */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 423ab6: mov eax, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 423aba: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423abe: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423abf: push ecx */
	{ DWORD v_ = 0xc1f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423ac0: push 0xc1f00000 */
	goto L_423c9b;	/* 423ac5: jmp 0x423c9b */
L_423aca:
	m->esp -= 4; M32(m->esp) = 0x423accu; native_call(m, m->ebx);	/* 423aca: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423acc: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423ad1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423ad8u; native_call(m, m->esi);	/* 423ad6: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 423ad8: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 423adc: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 423ae2: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 423ae6: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 423aec: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 423af0: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 423af4: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 423af8: fmul dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 423afe: mov edx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423b02: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 423b03: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 423b07: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 423b0d: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 423b11: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 423b15: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423b19: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b1a: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x423b21u; native_call(m, m->edi);	/* 423b1f: call edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b21: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b26: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423b2au; native_call(m, m->esi);	/* 423b28: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 423b2a: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 423b2e: fadd dword ptr [0x4a9414] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 423b34: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 423b38: fstp dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 423b3c: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423b40: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423b41: push edx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b42: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x423b49u; native_call(m, m->edi);	/* 423b47: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b49: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b4e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423b52u; native_call(m, m->esi);	/* 423b50: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 423b52: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 423b56: fsub dword ptr [0x4a9410] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 423b5c: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423b60: push eax */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 423b61: fstp dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 423b65: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423b69: push ecx */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b6a: push 0x41f00000 */
	m->esp -= 4; M32(m->esp) = 0x423b71u; native_call(m, m->edi);	/* 423b6f: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b71: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b76: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x423b7du; native_call(m, m->esi);	/* 423b7b: call esi */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 423b7d: mov edx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 423b81: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423b85: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423b86: push eax */
	{ DWORD v_ = 0x41f00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423b87: push 0x41f00000 */
	goto L_423c9b;	/* 423b8c: jmp 0x423c9b */
L_423b91:
	m->esp -= 4; M32(m->esp) = 0x423b93u; native_call(m, m->ebx);	/* 423b91: call ebx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 423b93: fild dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 423b97: mov eax, dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 423b9b: fmul dword ptr [0x4a941c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 423ba1: fst dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 423ba5: fadd dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 423ba9: fstp dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 423bad: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423bb1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423bb2: push eax */
	m->esp -= 4; M32(m->esp) = 0x423bb5u; native_call(m, m->esi);	/* 423bb3: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 423bb5: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 423bb9: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 423bbf: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9400u)));	/* 423bc3: fld dword ptr [0x4a9400] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 423bc9: fsub dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 423bcd: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 423bd1: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 423bd5: fmul dword ptr [0x4a9410] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 423bdb: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423bdf: push ecx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 423be0: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9410u)));	/* 423be4: fld dword ptr [0x4a9410] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 423bea: fsub dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 423bee: fstp dword ptr [esp + 0x18] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 423bf2: fild dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 423bf6: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423bfa: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 423bfb: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 423c01: fsubr dword ptr [0x4a940c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 423c07: fstp dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 423c0b: mov eax, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423c0f: push eax */
	m->esp -= 4; M32(m->esp) = 0x423c12u; native_call(m, m->edi);	/* 423c10: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 423c12: fld dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 423c16: fadd dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 423c1a: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c1e: push ecx */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 423c1f: fstp dword ptr [esp + 0x54] */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 423c23: mov edx, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c27: push edx */
	m->esp -= 4; M32(m->esp) = 0x423c2au; native_call(m, m->esi);	/* 423c28: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 423c2a: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 423c2e: fadd dword ptr [0x4a9414] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 423c34: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 423c38: mov edx, dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 423c3c: fstp dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 423c40: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423c44: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c45: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c46: push edx */
	m->esp -= 4; M32(m->esp) = 0x423c49u; native_call(m, m->edi);	/* 423c47: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 423c49: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 423c4d: fadd dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x50u));	/* 423c51: mov ecx, dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 423c55: fstp dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 423c59: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423c5d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c5e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x423c61u; native_call(m, m->esi);	/* 423c5f: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 423c61: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9410u));	/* 423c65: fsub dword ptr [0x4a9410] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 423c6b: mov edx, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 423c6f: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c73: push edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 423c74: fstp dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 423c78: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423c7c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c7d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x423c80u; native_call(m, m->edi);	/* 423c7e: call edi */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 423c80: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 423c84: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c88: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423c89: push eax */
	m->esp -= 4; M32(m->esp) = 0x423c8cu; native_call(m, m->esi);	/* 423c8a: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 423c8c: mov ecx, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 423c90: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 423c94: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c98: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 423c99: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 423c9a: push eax */
L_423c9b:
	m->esp -= 4; M32(m->esp) = 0x423c9du; native_call(m, m->edi);	/* 423c9b: call edi */
	m->esp -= 4; M32(m->esp) = 0x423c9fu; native_call(m, m->ebp);	/* 423c9d: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 423c9f: mov eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 423ca3: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423ca4: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 423ca7: mov dword ptr [esp + 0x20], eax */
	if (m->sf != m->of) goto L_4234da;	/* 423cab: jl 0x4234da */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 423cb1: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 423cb5: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423cb6: cmp eax, 4 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 423cb9: mov dword ptr [esp + 0x24], eax */
	if (m->sf != m->of) goto L_423406;	/* 423cbd: jl 0x423406 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 423cc3: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x423cceu; native_call(m, M32(0x4a922cu));	/* 423cc8: call dword ptr [0x4a922c] */
	m->eax = M32((DWORD)(0x680398u));	/* 423cce: mov eax, dword ptr [0x680398] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 423cd3: test eax, eax */
	if (m->zf) goto L_423d39;	/* 423cd5: je 0x423d39 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 423cd7: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4df454u));	/* 423cdd: fmul dword ptr [0x4df454] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680cccu));	/* 423ce3: fadd dword ptr [0x680ccc] */
	MF((DWORD)(0x680cccu)) = (float)ST(0);	/* 423ce9: fst dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 423cef: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 423cf5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 423cf7: test ah, 0x41 */
	if (m->zf) goto L_423d12;	/* 423cfa: je 0x423d12 */
	M32((DWORD)(0x680cccu)) = 0x40000000u;	/* 423cfc: mov dword ptr [0x680ccc], 0x40000000 */
	M32((DWORD)(0x4df454u)) = 0x3f800000u;	/* 423d06: mov dword ptr [0x4df454], 0x3f800000 */
	goto L_423d39;	/* 423d10: jmp 0x423d39 */
L_423d12:
	FPUSH(x87_ldm((const float *)(DWORD)(0x680cccu)));	/* 423d12: fld dword ptr [0x680ccc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 423d18: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 423d1e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 423d20: test ah, 1 */
	if (!m->zf) goto L_423d39;	/* 423d23: jne 0x423d39 */
	M32((DWORD)(0x680cccu)) = 0x42180000u;	/* 423d25: mov dword ptr [0x680ccc], 0x42180000 */
	M32((DWORD)(0x4df454u)) = 0xbf800000u;	/* 423d2f: mov dword ptr [0x4df454], 0xbf800000 */
L_423d39:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df010u)));	/* 423d39: fld dword ptr [0x4df010] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 423d3f: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9db978u));	/* 423d45: fadd dword ptr [0x9db978] */
	MF((DWORD)(0x9db978u)) = (float)ST(0);	/* 423d4b: fst dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 423d51: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 423d57: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 423d59: test ah, 0x41 */
	if (m->zf) goto L_423d74;	/* 423d5c: je 0x423d74 */
	M32((DWORD)(0x9db978u)) = 0x0u;	/* 423d5e: mov dword ptr [0x9db978], 0 */
	M32((DWORD)(0x4df010u)) = 0x3f800000u;	/* 423d68: mov dword ptr [0x4df010], 0x3f800000 */
	goto L_423d9b;	/* 423d72: jmp 0x423d9b */
L_423d74:
	FPUSH(x87_ldm((const float *)(DWORD)(0x9db978u)));	/* 423d74: fld dword ptr [0x9db978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 423d7a: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 423d80: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 423d82: test ah, 1 */
	if (!m->zf) goto L_423d9b;	/* 423d85: jne 0x423d9b */
	M32((DWORD)(0x9db978u)) = 0x42c80000u;	/* 423d87: mov dword ptr [0x9db978], 0x42c80000 */
	M32((DWORD)(0x4df010u)) = 0xbf800000u;	/* 423d91: mov dword ptr [0x4df010], 0xbf800000 */
L_423d9b:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4deda8u)));	/* 423d9b: fld dword ptr [0x4deda8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 423da1: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e14fcu));	/* 423da7: fadd dword ptr [0x4e14fc] */
	MF((DWORD)(0x4e14fcu)) = (float)ST(0);	/* 423dad: fst dword ptr [0x4e14fc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f0u)); FPOP();	/* 423db3: fcomp dword ptr [0x4a93f0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 423db9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 423dbb: test ah, 1 */
	if (!m->zf) goto L_423dca;	/* 423dbe: jne 0x423dca */
	M32((DWORD)(0x4e14fcu)) = 0x0u;	/* 423dc0: mov dword ptr [0x4e14fc], 0 */
L_423dca:
	m->esi = M32((DWORD)(m->esp + 0x3cu));	/* 423dca: mov esi, dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->esi, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423dce: cmp esi, -1 */
	if (m->zf) goto L_423e31;	/* 423dd1: je 0x423e31 */
	{ DWORD a_ = M32((DWORD)(0x4ddcecu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 423dd3: cmp dword ptr [0x4ddcec], 2 */
	if (!m->zf) goto L_423e31;	/* 423dda: jne 0x423e31 */
	m->eax = M32((DWORD)(0x680370u));	/* 423ddc: mov eax, dword ptr [0x680370] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 423de1: test eax, eax */
	if (!m->zf) goto L_423e31;	/* 423de3: jne 0x423e31 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 423de5: push 2 */
	m->esp -= 4; M32(m->esp) = 0x423decu; native_call(m, 0x41ef90u);	/* 423de7: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423dec: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x423df5u; native_call(m, M32(0x4a9218u));	/* 423def: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423df5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423dfa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423dff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 423e04: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 423e09: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x423e13u; native_call(m, 0x41f0e0u);	/* 423e0e: call 0x41f0e0 */
	{ DWORD a_ = m->esi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 423e13: shl esi, 7 */
	{ DWORD a_ = m->esi, b_ = 0x7506a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 423e16: add esi, 0x7506a4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 423e1c: push esi */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 423e1d: push 0x280 */
	{ DWORD v_ = 0x1bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 423e22: push 0x1bc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 423e27: push 0 */
	m->esp -= 4; M32(m->esp) = 0x423e2eu; native_call(m, 0x4029d0u);	/* 423e29: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423e2e: add esp, 0x24 */
L_423e31:
	m->edi = M32(m->esp); m->esp += 4;	/* 423e31: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 423e32: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 423e33: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 423e34: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 423e35: add esp, 0x44 */
	m->esp += 4 + 0; return;	/* 423e38: ret  */
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
