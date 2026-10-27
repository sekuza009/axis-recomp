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

static void lift_483060(X86 *m);
static void lift_471740(X86 *m);
static void lift_4809f0(X86 *m);

/* space_traceUnit_4809f0 (0x4809f0), lifted by tools/lift.py */
static void lift_4809f0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xe4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4809f0: sub esp, 0xe4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4809f6: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4809f7: push ebp */
	m->ebp = m->ecx;	/* 4809f8: mov ebp, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4809fa: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4809fb: push edi */
	m->edi = 0x1u;	/* 4809fc: mov edi, 1 */
	m->eax = M32((DWORD)(m->ebp + 0x24u));	/* 480a01: mov eax, dword ptr [ebp + 0x24] */
	M32((DWORD)(m->esp + 0x30u)) = m->ebp;	/* 480a04: mov dword ptr [esp + 0x30], ebp */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480a08: cmp eax, edi */
	if (!m->zf) goto L_481095;	/* 480a0a: jne 0x481095 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 480a10: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 480a13: fsub dword ptr [ebp] */
	m->esi = M32((DWORD)(m->esp + 0xf8u));	/* 480a16: mov esi, dword ptr [esp + 0xf8] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 480a1d: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x10u)));	/* 480a21: fld dword ptr [ebp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 480a24: fsub dword ptr [ebp + 4] */
	m->eax = M32((DWORD)(m->esp + 0x64u));	/* 480a27: mov eax, dword ptr [esp + 0x64] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 480a2b: mov dword ptr [esp + 0x1c], eax */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 480a2f: fstp dword ptr [esp + 0x68] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x14u)));	/* 480a33: fld dword ptr [ebp + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x8u));	/* 480a36: fsub dword ptr [ebp + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 480a39: mov ecx, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 480a3d: mov dword ptr [esp + 0x20], ecx */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 480a41: fstp dword ptr [esp + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 480a45: fld dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 480a49: fmul dword ptr [0x4a942c] */
	m->edx = M32((DWORD)(m->esp + 0x6cu));	/* 480a4f: mov edx, dword ptr [esp + 0x6c] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 480a53: mov dword ptr [esp + 0x24], edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 480a57: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 480a5b: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 480a5f: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 480a65: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 480a69: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 480a6d: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 480a73: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 480a77: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x8u));	/* 480a7a: fsub dword ptr [ebp + 8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 480a7d: fdiv dword ptr [esp + 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 480a81: call 0x49ec14 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 480a86: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 480a88: mov dword ptr [esp + 0x2c], eax */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480a8c: cmp eax, ebx */
	if (m->sf == m->of) goto L_480a96;	/* 480a8e: jge 0x480a96 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebx;	/* 480a90: mov dword ptr [esp + 0x2c], ebx */
	goto L_480a9e;	/* 480a94: jmp 0x480a9e */
L_480a96:
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480a96: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_480a9e;	/* 480a98: jle 0x480a9e */
	M32((DWORD)(m->esp + 0x2cu)) = m->edi;	/* 480a9a: mov dword ptr [esp + 0x2c], edi */
L_480a9e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 480a9e: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 480aa0: fsub dword ptr [ebp] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 480aa3: fdiv dword ptr [esp + 0x1c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 480aa7: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480aac: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 480aae: mov dword ptr [esp + 0x54], eax */
	if (m->sf == m->of) goto L_480aba;	/* 480ab2: jge 0x480aba */
	M32((DWORD)(m->esp + 0x54u)) = m->ebx;	/* 480ab4: mov dword ptr [esp + 0x54], ebx */
	goto L_480ac2;	/* 480ab8: jmp 0x480ac2 */
L_480aba:
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480aba: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_480ac2;	/* 480abc: jle 0x480ac2 */
	M32((DWORD)(m->esp + 0x54u)) = m->edi;	/* 480abe: mov dword ptr [esp + 0x54], edi */
L_480ac2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 480ac2: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 480ac5: fsub dword ptr [ebp + 4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 480ac8: fdiv dword ptr [esp + 0x20] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 480acc: call 0x49ec14 */
	m->edi = m->eax;	/* 480ad1: mov edi, eax */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480ad3: cmp edi, ebx */
	M32((DWORD)(m->esp + 0x48u)) = m->edi;	/* 480ad5: mov dword ptr [esp + 0x48], edi */
	if (m->sf == m->of) goto L_480ae1;	/* 480ad9: jge 0x480ae1 */
	M32((DWORD)(m->esp + 0x48u)) = m->ebx;	/* 480adb: mov dword ptr [esp + 0x48], ebx */
	goto L_480aee;	/* 480adf: jmp 0x480aee */
L_480ae1:
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480ae1: cmp edi, 1 */
	if (m->zf || m->sf != m->of) goto L_480af2;	/* 480ae4: jle 0x480af2 */
	M32((DWORD)(m->esp + 0x48u)) = 0x1u;	/* 480ae6: mov dword ptr [esp + 0x48], 1 */
L_480aee:
	m->edi = M32((DWORD)(m->esp + 0x48u));	/* 480aee: mov edi, dword ptr [esp + 0x48] */
L_480af2:
	m->ebx = M32((DWORD)(m->esp + 0xfcu));	/* 480af2: mov ebx, dword ptr [esp + 0xfc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 480af9: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x8u));	/* 480afc: fsub dword ptr [ebp + 8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 480aff: fdiv dword ptr [esp + 0x24] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 480b03: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480b08: test eax, eax */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 480b0a: mov dword ptr [esp + 0x50], eax */
	if (m->sf == m->of) goto L_480b1a;	/* 480b0e: jge 0x480b1a */
	M32((DWORD)(m->esp + 0x50u)) = 0x0u;	/* 480b10: mov dword ptr [esp + 0x50], 0 */
	goto L_480b27;	/* 480b18: jmp 0x480b27 */
L_480b1a:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480b1a: cmp eax, 1 */
	if (m->zf || m->sf != m->of) goto L_480b27;	/* 480b1d: jle 0x480b27 */
	M32((DWORD)(m->esp + 0x50u)) = 0x1u;	/* 480b1f: mov dword ptr [esp + 0x50], 1 */
L_480b27:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 480b27: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 480b29: fsub dword ptr [ebp] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 480b2c: fdiv dword ptr [esp + 0x1c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 480b30: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480b35: test eax, eax */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 480b37: mov dword ptr [esp + 0x38], eax */
	if (m->sf == m->of) goto L_480b47;	/* 480b3b: jge 0x480b47 */
	M32((DWORD)(m->esp + 0x38u)) = 0x0u;	/* 480b3d: mov dword ptr [esp + 0x38], 0 */
	goto L_480b54;	/* 480b45: jmp 0x480b54 */
L_480b47:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480b47: cmp eax, 1 */
	if (m->zf || m->sf != m->of) goto L_480b54;	/* 480b4a: jle 0x480b54 */
	M32((DWORD)(m->esp + 0x38u)) = 0x1u;	/* 480b4c: mov dword ptr [esp + 0x38], 1 */
L_480b54:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 480b54: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 480b57: fsub dword ptr [ebp + 4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 480b5a: fdiv dword ptr [esp + 0x20] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 480b5e: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480b63: test eax, eax */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 480b65: mov dword ptr [esp + 0x34], eax */
	if (m->sf == m->of) goto L_480b75;	/* 480b69: jge 0x480b75 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 480b6b: mov dword ptr [esp + 0x34], 0 */
	goto L_480b82;	/* 480b73: jmp 0x480b82 */
L_480b75:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480b75: cmp eax, 1 */
	if (m->zf || m->sf != m->of) goto L_480b86;	/* 480b78: jle 0x480b86 */
	M32((DWORD)(m->esp + 0x34u)) = 0x1u;	/* 480b7a: mov dword ptr [esp + 0x34], 1 */
L_480b82:
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 480b82: mov eax, dword ptr [esp + 0x34] */
L_480b86:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 480b86: xor ecx, ecx */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480b88: cmp edi, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 480b8a: setg cl */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 480b8d: mov eax, dword ptr [esp + 0x50] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 480b91: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 480b92: and ecx, 2 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 480b95: xor edx, edx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 480b97: dec ecx */
	M32((DWORD)(m->esp + 0x74u)) = m->ecx;	/* 480b98: mov dword ptr [esp + 0x74], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 480b9c: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480ba0: cmp ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 480ba2: mov eax, dword ptr [esp + 0x54] */
	m->edx = (m->edx & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 480ba6: setg dl */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 480ba9: fld dword ptr [ebx] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 480bab: dec edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 480bac: xor ecx, ecx */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 480bae: fsub dword ptr [esi] */
	{ DWORD a_ = m->edx, b_ = 0x2u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 480bb0: and edx, 2 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 480bb3: dec edx */
	M32((DWORD)(m->esp + 0x94u)) = m->edx;	/* 480bb4: mov dword ptr [esp + 0x94], edx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 480bbb: mov edx, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480bbf: cmp eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 480bc1: mov edx, dword ptr [esp + 0x74] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 480bc5: setg cl */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 480bc8: dec ecx */
	MF((DWORD)(m->esp + 0xa4u)) = (float)ST(0); FPOP();	/* 480bc9: fstp dword ptr [esp + 0xa4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 480bd0: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 480bd3: fsub dword ptr [esi + 4] */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 480bd6: and ecx, 2 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 480bd9: dec ecx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 480bda: shl edx, 4 */
	M32((DWORD)(m->esp + 0xf0u)) = m->edx;	/* 480bdd: mov dword ptr [esp + 0xf0], edx */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 480be4: mov edx, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0xa8u)) = (float)ST(0); FPOP();	/* 480be8: fstp dword ptr [esp + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 480bef: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 480bf2: fsub dword ptr [esi + 8] */
	m->edx = (DWORD)(m->edx + m->edi*2 + 0x0u);	/* 480bf5: lea edx, [edx + edi*2] */
	M32((DWORD)(m->esp + 0x90u)) = m->ecx;	/* 480bf8: mov dword ptr [esp + 0x90], ecx */
	m->ecx = m->edi;	/* 480bff: mov ecx, edi */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0xau);	/* 480c01: lea eax, [eax + edx*2 + 0xa] */
	M32((DWORD)(m->esp + 0x4cu)) = m->ecx;	/* 480c05: mov dword ptr [esp + 0x4c], ecx */
	MF((DWORD)(m->esp + 0xacu)) = (float)ST(0); FPOP();	/* 480c09: fstp dword ptr [esp + 0xac] */
	m->edx = (DWORD)(m->ebp + m->eax*4 + 0x0u);	/* 480c10: lea edx, [ebp + eax*4] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 480c14: mov dword ptr [esp + 0x28], edx */
L_480c18:
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480c18: cmp ecx, edi */
	if (!m->zf) goto L_480c34;	/* 480c1a: jne 0x480c34 */
	m->eax = m->esi;	/* 480c1c: mov eax, esi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 480c1e: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 480c20: mov dword ptr [esp + 0x3c], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 480c24: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 480c27: mov dword ptr [esp + 0x40], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 480c2b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 480c2e: mov dword ptr [esp + 0x44], eax */
	goto L_480c8b;	/* 480c32: jmp 0x480c8b */
L_480c34:
	m->eax = M32((DWORD)(m->esp + 0x74u));	/* 480c34: mov eax, dword ptr [esp + 0x74] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480c38: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_480c42;	/* 480c3a: jle 0x480c42 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4cu)));	/* 480c3c: fild dword ptr [esp + 0x4c] */
	goto L_480c4d;	/* 480c40: jmp 0x480c4d */
L_480c42:
	m->edx = (DWORD)(m->ecx + 0x1u);	/* 480c42: lea edx, [ecx + 1] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 480c45: mov dword ptr [esp + 0x14], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 480c49: fild dword ptr [esp + 0x14] */
L_480c4d:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 480c4d: fmul dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 480c51: fadd dword ptr [ebp + 4] */
	{ long double t = ST(0); FPUSH(t); }	/* 480c54: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 480c56: fsub dword ptr [esi + 4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 480c59: fdiv dword ptr [esp + 0xa8] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 480c60: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xa4u)));	/* 480c64: fld dword ptr [esp + 0xa4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 480c6b: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 480c6f: fadd dword ptr [esi] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 480c71: fstp dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 480c75: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 480c79: fld dword ptr [esp + 0xac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 480c80: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 480c84: fadd dword ptr [esi + 8] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 480c87: fstp dword ptr [esp + 0x44] */
L_480c8b:
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->esp + 0x34u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480c8b: cmp ecx, dword ptr [esp + 0x34] */
	if (!m->zf) goto L_480cb0;	/* 480c8f: jne 0x480cb0 */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 480c91: mov eax, dword ptr [ebx] */
	M32((DWORD)(m->esp + 0x98u)) = m->eax;	/* 480c93: mov dword ptr [esp + 0x98], eax */
	m->ecx = M32((DWORD)(m->ebx + 0x4u));	/* 480c9a: mov ecx, dword ptr [ebx + 4] */
	M32((DWORD)(m->esp + 0x9cu)) = m->ecx;	/* 480c9d: mov dword ptr [esp + 0x9c], ecx */
	m->edx = M32((DWORD)(m->ebx + 0x8u));	/* 480ca4: mov edx, dword ptr [ebx + 8] */
	M32((DWORD)(m->esp + 0xa0u)) = m->edx;	/* 480ca7: mov dword ptr [esp + 0xa0], edx */
	goto L_480d0e;	/* 480cae: jmp 0x480d0e */
L_480cb0:
	m->eax = M32((DWORD)(m->esp + 0x74u));	/* 480cb0: mov eax, dword ptr [esp + 0x74] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480cb4: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_480cc3;	/* 480cb6: jle 0x480cc3 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 480cb8: inc ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 480cb9: mov dword ptr [esp + 0x14], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 480cbd: fild dword ptr [esp + 0x14] */
	goto L_480cc7;	/* 480cc1: jmp 0x480cc7 */
L_480cc3:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4cu)));	/* 480cc3: fild dword ptr [esp + 0x4c] */
L_480cc7:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 480cc7: fmul dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 480ccb: fadd dword ptr [ebp + 4] */
	{ long double t = ST(0); FPUSH(t); }	/* 480cce: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 480cd0: fsub dword ptr [esi + 4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 480cd3: fdiv dword ptr [esp + 0xa8] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 480cda: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xa4u)));	/* 480cde: fld dword ptr [esp + 0xa4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 480ce5: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 480ce9: fadd dword ptr [esi] */
	MF((DWORD)(m->esp + 0x98u)) = (float)ST(0); FPOP();	/* 480ceb: fstp dword ptr [esp + 0x98] */
	MF((DWORD)(m->esp + 0x9cu)) = (float)ST(0); FPOP();	/* 480cf2: fstp dword ptr [esp + 0x9c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 480cf9: fld dword ptr [esp + 0xac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 480d00: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 480d04: fadd dword ptr [esi + 8] */
	MF((DWORD)(m->esp + 0xa0u)) = (float)ST(0); FPOP();	/* 480d07: fstp dword ptr [esp + 0xa0] */
L_480d0e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x98u)));	/* 480d0e: fld dword ptr [esp + 0x98] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 480d15: fsub dword ptr [esp + 0x3c] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 480d19: mov edx, dword ptr [esp + 0x2c] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 480d1d: mov eax, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 480d21: mov dword ptr [esp + 0x70], edx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 480d25: mov dword ptr [esp + 0x14], eax */
	MF((DWORD)(m->esp + 0xb4u)) = (float)ST(0); FPOP();	/* 480d29: fstp dword ptr [esp + 0xb4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x9cu)));	/* 480d30: fld dword ptr [esp + 0x9c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 480d37: fsub dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0xb8u)) = (float)ST(0); FPOP();	/* 480d3b: fstp dword ptr [esp + 0xb8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xa0u)));	/* 480d42: fld dword ptr [esp + 0xa0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 480d49: fsub dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0xbcu)) = (float)ST(0); FPOP();	/* 480d4d: fstp dword ptr [esp + 0xbc] */
L_480d54:
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esp + 0x2cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480d54: cmp edx, dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_480d74;	/* 480d58: jne 0x480d74 */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 480d5a: mov ecx, dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 480d5e: mov eax, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 480d62: mov dword ptr [esp + 0x58], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 480d66: mov ecx, dword ptr [esp + 0x44] */
	M32((DWORD)(m->esp + 0x5cu)) = m->eax;	/* 480d6a: mov dword ptr [esp + 0x5c], eax */
	M32((DWORD)(m->esp + 0x60u)) = m->ecx;	/* 480d6e: mov dword ptr [esp + 0x60], ecx */
	goto L_480dcc;	/* 480d72: jmp 0x480dcc */
L_480d74:
	m->eax = M32((DWORD)(m->esp + 0x94u));	/* 480d74: mov eax, dword ptr [esp + 0x94] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480d7b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_480d85;	/* 480d7d: jle 0x480d85 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x70u)));	/* 480d7f: fild dword ptr [esp + 0x70] */
	goto L_480d90;	/* 480d83: jmp 0x480d90 */
L_480d85:
	m->eax = (DWORD)(m->edx + 0x1u);	/* 480d85: lea eax, [edx + 1] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 480d88: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 480d8c: fild dword ptr [esp + 0x18] */
L_480d90:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 480d90: fmul dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x8u));	/* 480d94: fadd dword ptr [ebp + 8] */
	{ long double t = ST(0); FPUSH(t); }	/* 480d97: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 480d99: fsub dword ptr [esp + 0x44] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0xbcu));	/* 480d9d: fdiv dword ptr [esp + 0xbc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb4u)));	/* 480da4: fld dword ptr [esp + 0xb4] */
	ST(0) = ST(0) * ST(1);	/* 480dab: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 480dad: fadd dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 480db1: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb8u)));	/* 480db5: fld dword ptr [esp + 0xb8] */
	ST(0) = ST(0) * ST(1);	/* 480dbc: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 480dbe: fadd dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 480dc2: fstp dword ptr [esp + 0x5c] */
	ST(0) = ST(0); FPOP();	/* 480dc6: fstp st(0) */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 480dc8: fstp dword ptr [esp + 0x60] */
L_480dcc:
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esp + 0x50u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480dcc: cmp edx, dword ptr [esp + 0x50] */
	if (!m->zf) goto L_480dfe;	/* 480dd0: jne 0x480dfe */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 480dd2: mov ecx, dword ptr [esp + 0x98] */
	m->ebp = M32((DWORD)(m->esp + 0x9cu));	/* 480dd9: mov ebp, dword ptr [esp + 0x9c] */
	m->eax = M32((DWORD)(m->esp + 0xa0u));	/* 480de0: mov eax, dword ptr [esp + 0xa0] */
	M32((DWORD)(m->esp + 0x84u)) = m->ecx;	/* 480de7: mov dword ptr [esp + 0x84], ecx */
	M32((DWORD)(m->esp + 0x88u)) = m->ebp;	/* 480dee: mov dword ptr [esp + 0x88], ebp */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 480df5: mov dword ptr [esp + 0x8c], eax */
	goto L_480e66;	/* 480dfc: jmp 0x480e66 */
L_480dfe:
	m->eax = M32((DWORD)(m->esp + 0x94u));	/* 480dfe: mov eax, dword ptr [esp + 0x94] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480e05: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_480e16;	/* 480e07: jle 0x480e16 */
	m->ecx = (DWORD)(m->edx + 0x1u);	/* 480e09: lea ecx, [edx + 1] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 480e0c: mov dword ptr [esp + 0x18], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 480e10: fild dword ptr [esp + 0x18] */
	goto L_480e1a;	/* 480e14: jmp 0x480e1a */
L_480e16:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x70u)));	/* 480e16: fild dword ptr [esp + 0x70] */
L_480e1a:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 480e1a: fmul dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x8u));	/* 480e1e: fadd dword ptr [ebp + 8] */
	{ long double t = ST(0); FPUSH(t); }	/* 480e21: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 480e23: fsub dword ptr [esp + 0x44] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0xbcu));	/* 480e27: fdiv dword ptr [esp + 0xbc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb4u)));	/* 480e2e: fld dword ptr [esp + 0xb4] */
	ST(0) = ST(0) * ST(1);	/* 480e35: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 480e37: fadd dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 480e3b: fstp dword ptr [esp + 0x84] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb8u)));	/* 480e42: fld dword ptr [esp + 0xb8] */
	ST(0) = ST(0) * ST(1);	/* 480e49: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 480e4b: fadd dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 480e4f: fstp dword ptr [esp + 0x88] */
	m->ebp = M32((DWORD)(m->esp + 0x88u));	/* 480e56: mov ebp, dword ptr [esp + 0x88] */
	ST(0) = ST(0); FPOP();	/* 480e5d: fstp st(0) */
	MF((DWORD)(m->esp + 0x8cu)) = (float)ST(0); FPOP();	/* 480e5f: fstp dword ptr [esp + 0x8c] */
L_480e66:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 480e66: fld dword ptr [esp + 0x84] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 480e6d: fsub dword ptr [esp + 0x58] */
	m->eax = M32((DWORD)(m->esp + 0x90u));	/* 480e71: mov eax, dword ptr [esp + 0x90] */
	m->esi = M32((DWORD)(m->esp + 0x54u));	/* 480e78: mov esi, dword ptr [esp + 0x54] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 480e7c: mov edi, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 480e80: mov dword ptr [esp + 0x18], esi */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 480e84: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 480e88: fld dword ptr [esp + 0x88] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 480e8f: fsub dword ptr [esp + 0x5c] */
	m->ebx = (DWORD)(m->eax*4 + 0x0u);	/* 480e93: lea ebx, [eax*4] */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 480e9a: fstp dword ptr [esp + 0x68] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8cu)));	/* 480e9e: fld dword ptr [esp + 0x8c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 480ea5: fsub dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 480ea9: fstp dword ptr [esp + 0x6c] */
L_480ead:
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->esp + 0x54u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480ead: cmp esi, dword ptr [esp + 0x54] */
	if (!m->zf) goto L_480ed6;	/* 480eb1: jne 0x480ed6 */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 480eb3: mov ecx, dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0xccu)) = m->ecx;	/* 480eb7: mov dword ptr [esp + 0xcc], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 480ebe: mov ecx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->esp + 0xd0u)) = m->ecx;	/* 480ec2: mov dword ptr [esp + 0xd0], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x60u));	/* 480ec9: mov ecx, dword ptr [esp + 0x60] */
	M32((DWORD)(m->esp + 0xd4u)) = m->ecx;	/* 480ecd: mov dword ptr [esp + 0xd4], ecx */
	goto L_480f30;	/* 480ed4: jmp 0x480f30 */
L_480ed6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480ed6: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_480ee0;	/* 480ed8: jle 0x480ee0 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 480eda: fild dword ptr [esp + 0x18] */
	goto L_480eeb;	/* 480ede: jmp 0x480eeb */
L_480ee0:
	m->ecx = (DWORD)(m->esi + 0x1u);	/* 480ee0: lea ecx, [esi + 1] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 480ee3: mov dword ptr [esp + 0x10], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 480ee7: fild dword ptr [esp + 0x10] */
L_480eeb:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 480eeb: fmul dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 480eef: mov ecx, dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 480ef3: fadd dword ptr [ecx] */
	{ long double t = ST(0); FPUSH(t); }	/* 480ef5: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 480ef7: fsub dword ptr [esp + 0x58] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 480efb: fdiv dword ptr [esp + 0x64] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 480eff: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0xccu)) = (float)ST(0); FPOP();	/* 480f03: fstp dword ptr [esp + 0xcc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 480f0a: fld dword ptr [esp + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 480f0e: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 480f12: fadd dword ptr [esp + 0x5c] */
	MF((DWORD)(m->esp + 0xd0u)) = (float)ST(0); FPOP();	/* 480f16: fstp dword ptr [esp + 0xd0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x6cu)));	/* 480f1d: fld dword ptr [esp + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 480f21: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 480f25: fadd dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0xd4u)) = (float)ST(0); FPOP();	/* 480f29: fstp dword ptr [esp + 0xd4] */
L_480f30:
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->esp + 0x38u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480f30: cmp esi, dword ptr [esp + 0x38] */
	if (!m->zf) goto L_480f5b;	/* 480f34: jne 0x480f5b */
	m->eax = M32((DWORD)(m->esp + 0x84u));	/* 480f36: mov eax, dword ptr [esp + 0x84] */
	m->ecx = M32((DWORD)(m->esp + 0x8cu));	/* 480f3d: mov ecx, dword ptr [esp + 0x8c] */
	M32((DWORD)(m->esp + 0xc0u)) = m->eax;	/* 480f44: mov dword ptr [esp + 0xc0], eax */
	M32((DWORD)(m->esp + 0xc4u)) = m->ebp;	/* 480f4b: mov dword ptr [esp + 0xc4], ebp */
	M32((DWORD)(m->esp + 0xc8u)) = m->ecx;	/* 480f52: mov dword ptr [esp + 0xc8], ecx */
	goto L_480fbf;	/* 480f59: jmp 0x480fbf */
L_480f5b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480f5b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_480f76;	/* 480f5d: jle 0x480f76 */
	m->eax = (DWORD)(m->esi + 0x1u);	/* 480f5f: lea eax, [esi + 1] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 480f62: mov ecx, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 480f66: mov dword ptr [esp + 0x18], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 480f6a: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 480f6e: fmul dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 480f72: fadd dword ptr [ecx] */
	goto L_480f84;	/* 480f74: jmp 0x480f84 */
L_480f76:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 480f76: fild dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 480f7a: mov eax, dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 480f7e: fmul dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 480f82: fadd dword ptr [eax] */
L_480f84:
	{ long double t = ST(0); FPUSH(t); }	/* 480f84: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 480f86: fsub dword ptr [esp + 0x58] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 480f8a: fdiv dword ptr [esp + 0x64] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 480f8e: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0xc0u)) = (float)ST(0); FPOP();	/* 480f92: fstp dword ptr [esp + 0xc0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 480f99: fld dword ptr [esp + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 480f9d: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 480fa1: fadd dword ptr [esp + 0x5c] */
	MF((DWORD)(m->esp + 0xc4u)) = (float)ST(0); FPOP();	/* 480fa5: fstp dword ptr [esp + 0xc4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x6cu)));	/* 480fac: fld dword ptr [esp + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 480fb0: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 480fb4: fadd dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0xc8u)) = (float)ST(0); FPOP();	/* 480fb8: fstp dword ptr [esp + 0xc8] */
L_480fbf:
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 480fbf: mov ecx, dword ptr [edi] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480fc1: test ecx, ecx */
	if (m->zf) goto L_481006;	/* 480fc3: je 0x481006 */
	m->edx = M32((DWORD)(m->esp + 0x10cu));	/* 480fc5: mov edx, dword ptr [esp + 0x10c] */
	m->eax = M32((DWORD)(m->esp + 0x108u));	/* 480fcc: mov eax, dword ptr [esp + 0x108] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 480fd3: push edx */
	m->edx = M32((DWORD)(m->esp + 0x108u));	/* 480fd4: mov edx, dword ptr [esp + 0x108] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 480fdb: push eax */
	m->eax = M32((DWORD)(m->esp + 0x108u));	/* 480fdc: mov eax, dword ptr [esp + 0x108] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 480fe3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 480fe4: push eax */
	m->edx = (DWORD)(m->esp + 0xd0u);	/* 480fe5: lea edx, [esp + 0xd0] */
	m->eax = (DWORD)(m->esp + 0xdcu);	/* 480fec: lea eax, [esp + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 480ff3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 480ff4: push eax */
	m->esp -= 4; M32(m->esp) = 0x480ffau; lift_4809f0(m);	/* 480ff5: call 0x4809f0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480ffa: test eax, eax */
	if (!m->zf) goto L_481315;	/* 480ffc: jne 0x481315 */
	m->edx = M32((DWORD)(m->esp + 0x70u));	/* 481002: mov edx, dword ptr [esp + 0x70] */
L_481006:
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->esp + 0x38u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481006: cmp esi, dword ptr [esp + 0x38] */
	if (m->zf) goto L_481022;	/* 48100a: je 0x481022 */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 48100c: mov ecx, dword ptr [esp + 0x90] */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 481013: add esi, ecx */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 481015: add edi, ebx */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 481017: mov dword ptr [esp + 0x18], esi */
	m->eax = m->ecx;	/* 48101b: mov eax, ecx */
	goto L_480ead;	/* 48101d: jmp 0x480ead */
L_481022:
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esp + 0x50u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481022: cmp edx, dword ptr [esp + 0x50] */
	if (m->zf) goto L_48104b;	/* 481026: je 0x48104b */
	m->eax = M32((DWORD)(m->esp + 0x94u));	/* 481028: mov eax, dword ptr [esp + 0x94] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 48102f: mov ecx, dword ptr [esp + 0x14] */
	m->ebp = M32((DWORD)(m->esp + 0x30u));	/* 481033: mov ebp, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 481037: add edx, eax */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 481039: shl eax, 3 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48103c: add ecx, eax */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 48103e: mov dword ptr [esp + 0x70], edx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 481042: mov dword ptr [esp + 0x14], ecx */
	goto L_480d54;	/* 481046: jmp 0x480d54 */
L_48104b:
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 48104b: mov eax, dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 48104f: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481053: cmp eax, ecx */
	if (m->zf) goto L_481313;	/* 481055: je 0x481313 */
	m->ecx = M32((DWORD)(m->esp + 0x74u));	/* 48105b: mov ecx, dword ptr [esp + 0x74] */
	m->esi = M32((DWORD)(m->esp + 0xf8u));	/* 48105f: mov esi, dword ptr [esp + 0xf8] */
	m->ebx = M32((DWORD)(m->esp + 0xfcu));	/* 481066: mov ebx, dword ptr [esp + 0xfc] */
	m->ebp = M32((DWORD)(m->esp + 0x30u));	/* 48106d: mov ebp, dword ptr [esp + 0x30] */
	m->edi = M32((DWORD)(m->esp + 0x48u));	/* 481071: mov edi, dword ptr [esp + 0x48] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 481075: add eax, ecx */
	m->ecx = M32((DWORD)(m->esp + 0xf0u));	/* 481077: mov ecx, dword ptr [esp + 0xf0] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 48107e: mov dword ptr [esp + 0x4c], eax */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 481082: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 481086: add eax, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 481088: mov ecx, dword ptr [esp + 0x4c] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 48108c: mov dword ptr [esp + 0x28], eax */
	goto L_480c18;	/* 481090: jmp 0x480c18 */
L_481095:
	m->ebp = M32((DWORD)(m->ebp + 0x18u));	/* 481095: mov ebp, dword ptr [ebp + 0x18] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481098: test ebp, ebp */
	if (m->zf) goto L_481313;	/* 48109a: je 0x481313 */
	m->esi = M32((DWORD)(m->esp + 0xf8u));	/* 4810a0: mov esi, dword ptr [esp + 0xf8] */
	m->edx = M32((DWORD)(m->esp + 0x104u));	/* 4810a7: mov edx, dword ptr [esp + 0x104] */
	m->edi = M32((DWORD)(m->esp + 0xfcu));	/* 4810ae: mov edi, dword ptr [esp + 0xfc] */
	m->eax = m->esi;	/* 4810b5: mov eax, esi */
	M32((DWORD)(m->edx + 0x0u)) = 0xff7fffffu;	/* 4810b7: mov dword ptr [edx], 0xff7fffff */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4810bd: or ecx, 0xffffffff */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 4810c0: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 4810c2: mov dword ptr [esp + 0x28], ecx */
	M32((DWORD)(m->esp + 0xd8u)) = m->edx;	/* 4810c6: mov dword ptr [esp + 0xd8], edx */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 4810cd: mov dword ptr [esp + 0x14], 0 */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 4810d5: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0xdcu)) = m->edx;	/* 4810d8: mov dword ptr [esp + 0xdc], edx */
	m->edx = m->edi;	/* 4810df: mov edx, edi */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 4810e1: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0xe0u)) = m->eax;	/* 4810e4: mov dword ptr [esp + 0xe0], eax */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 4810eb: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0xe4u)) = m->eax;	/* 4810ed: mov dword ptr [esp + 0xe4], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 4810f4: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0xe8u)) = m->eax;	/* 4810f7: mov dword ptr [esp + 0xe8], eax */
	m->eax = M32((DWORD)(m->esp + 0x108u));	/* 4810fe: mov eax, dword ptr [esp + 0x108] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 481105: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0xecu)) = m->edx;	/* 481108: mov dword ptr [esp + 0xec], edx */
	m->ebx = (DWORD)(m->eax + 0xfffffffcu);	/* 48110f: lea ebx, [eax - 4] */
L_481112:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481112: test ebp, ebp */
	if (!m->zf) goto L_4811f0;	/* 481114: jne 0x4811f0 */
	m->eax = M32((DWORD)(m->esp + 0x10cu));	/* 48111a: mov eax, dword ptr [esp + 0x10c] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 481121: inc ecx */
	{ DWORD a_ = m->ebx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 481122: add ebx, 0xc */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481125: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 481127: mov dword ptr [esp + 0x28], ecx */
	if (m->sf == m->of) goto L_481302;	/* 48112b: jge 0x481302 */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 481131: mov eax, dword ptr [ebx] */
	m->ebp = M32((DWORD)(m->ebx + 0xfffffff8u));	/* 481133: mov ebp, dword ptr [ebx - 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x10u)));	/* 481136: fld dword ptr [eax + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481139: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x20u)));	/* 48113c: fld dword ptr [eax + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 48113f: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 481142: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 481144: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 481146: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 481148: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 48114a: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->esp + 0xd8u)) = (float)ST(0); FPOP();	/* 48114d: fstp dword ptr [esp + 0xd8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x14u)));	/* 481154: fld dword ptr [eax + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481157: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x24u)));	/* 48115a: fld dword ptr [eax + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 48115d: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 481160: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 481162: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 481165: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 481167: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 481169: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->esp + 0xdcu)) = (float)ST(0); FPOP();	/* 48116c: fstp dword ptr [esp + 0xdc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x18u)));	/* 481173: fld dword ptr [eax + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481176: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x28u)));	/* 481179: fld dword ptr [eax + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 48117c: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48117f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 481181: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 481184: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 481186: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 481188: fadd dword ptr [eax + 0x38] */
	MF((DWORD)(m->esp + 0xe0u)) = (float)ST(0); FPOP();	/* 48118b: fstp dword ptr [esp + 0xe0] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 481192: mov eax, dword ptr [ebx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x10u)));	/* 481194: fld dword ptr [eax + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 481197: fmul dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x20u)));	/* 48119a: fld dword ptr [eax + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 48119d: fmul dword ptr [edi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4811a0: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 4811a2: fld dword ptr [edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4811a4: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4811a6: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 4811a8: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->esp + 0xe4u)) = (float)ST(0); FPOP();	/* 4811ab: fstp dword ptr [esp + 0xe4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x14u)));	/* 4811b2: fld dword ptr [eax + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 4811b5: fmul dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4811b8: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 4811bb: fmul dword ptr [edi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4811bd: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x24u)));	/* 4811bf: fld dword ptr [eax + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 4811c2: fmul dword ptr [edi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4811c5: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 4811c7: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->esp + 0xe8u)) = (float)ST(0); FPOP();	/* 4811ca: fstp dword ptr [esp + 0xe8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x18u)));	/* 4811d1: fld dword ptr [eax + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 4811d4: fmul dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4811d7: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 4811da: fmul dword ptr [edi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4811dc: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x28u)));	/* 4811de: fld dword ptr [eax + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 4811e1: fmul dword ptr [edi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4811e4: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 4811e6: fadd dword ptr [eax + 0x38] */
	MF((DWORD)(m->esp + 0xecu)) = (float)ST(0); FPOP();	/* 4811e9: fstp dword ptr [esp + 0xec] */
L_4811f0:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4811f0: test ecx, ecx */
	if (m->sf == m->of) goto L_481200;	/* 4811f2: jge 0x481200 */
	m->ecx = M32((DWORD)(m->ebp + 0x0u));	/* 4811f4: mov ecx, dword ptr [ebp] */
	{ DWORD a_ = M8((DWORD)(m->ecx + 0x0u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4811f7: test byte ptr [ecx], 1 */
	if (!m->zf) goto L_4812f6;	/* 4811fa: jne 0x4812f6 */
L_481200:
	m->edx = (DWORD)(m->esp + 0xb0u);	/* 481200: lea edx, [esp + 0xb0] */
	m->eax = (DWORD)(m->esp + 0x78u);	/* 481207: lea eax, [esp + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48120b: push edx */
	m->ecx = (DWORD)(m->esp + 0xe8u);	/* 48120c: lea ecx, [esp + 0xe8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481213: push eax */
	m->edx = (DWORD)(m->esp + 0xe0u);	/* 481214: lea edx, [esp + 0xe0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48121b: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x0u));	/* 48121c: mov ecx, dword ptr [ebp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48121f: push edx */
	m->esp -= 4; M32(m->esp) = 0x481225u; native_call(m, 0x47fb80u);	/* 481220: call 0x47fb80 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481225: cmp eax, 1 */
	if (!m->zf) goto L_4812f6;	/* 481228: jne 0x4812f6 */
	m->eax = M32((DWORD)(m->esp + 0x104u));	/* 48122e: mov eax, dword ptr [esp + 0x104] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 481235: fld dword ptr [esp + 0xb0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->eax + 0x0u)); FPOP();	/* 48123c: fcomp dword ptr [eax] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48123e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481240: test ah, 0x41 */
	if (!m->zf) goto L_4812f6;	/* 481243: jne 0x4812f6 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 481249: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48124d: test eax, eax */
	if (m->sf == m->of) goto L_481271;	/* 48124f: jge 0x481271 */
	m->ecx = M32((DWORD)(m->esp + 0x100u));	/* 481251: mov ecx, dword ptr [esp + 0x100] */
	m->edx = M32((DWORD)(m->esp + 0x78u));	/* 481258: mov edx, dword ptr [esp + 0x78] */
	m->eax = M32((DWORD)(m->esp + 0x7cu));	/* 48125c: mov eax, dword ptr [esp + 0x7c] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 481260: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 481262: mov edx, dword ptr [esp + 0x80] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 481269: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 48126c: mov dword ptr [ecx + 8], edx */
	goto L_4812df;	/* 48126f: jmp 0x4812df */
L_481271:
	m->eax = M32((DWORD)(m->ebx + 0xfffffffcu));	/* 481271: mov eax, dword ptr [ebx - 4] */
	m->ecx = M32((DWORD)(m->esp + 0x100u));	/* 481274: mov ecx, dword ptr [esp + 0x100] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 48127b: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 481282: fmul dword ptr [eax + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 481285: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 481289: fmul dword ptr [eax + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48128c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 48128e: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 481292: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 481294: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 481296: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 481299: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 48129b: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 4812a2: fmul dword ptr [eax + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 4812a5: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 4812a9: fmul dword ptr [eax + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4812ac: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 4812ae: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4812b2: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4812b5: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 4812b7: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 4812ba: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 4812bd: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 4812c4: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 4812c7: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 4812cb: fmul dword ptr [eax + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4812ce: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 4812d0: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4812d4: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4812d7: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 4812d9: fadd dword ptr [eax + 0x38] */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 4812dc: fstp dword ptr [ecx + 8] */
L_4812df:
	m->ecx = M32((DWORD)(m->esp + 0x104u));	/* 4812df: mov ecx, dword ptr [esp + 0x104] */
	m->eax = M32((DWORD)(m->esp + 0xb0u));	/* 4812e6: mov eax, dword ptr [esp + 0xb0] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 4812ed: mov dword ptr [ecx], eax */
	m->edx = M32((DWORD)(m->ebp + 0x0u));	/* 4812ef: mov edx, dword ptr [ebp] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 4812f2: mov dword ptr [esp + 0x14], edx */
L_4812f6:
	m->ebp = M32((DWORD)(m->ebp + 0xcu));	/* 4812f6: mov ebp, dword ptr [ebp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4812f9: mov ecx, dword ptr [esp + 0x28] */
	goto L_481112;	/* 4812fd: jmp 0x481112 */
L_481302:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 481302: mov eax, dword ptr [esp + 0x14] */
	m->edi = M32(m->esp); m->esp += 4;	/* 481306: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 481307: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 481308: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 481309: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48130a: add esp, 0xe4 */
	m->esp += 4 + 24; return;	/* 481310: ret 0x18 */
L_481313:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481313: xor eax, eax */
L_481315:
	m->edi = M32(m->esp); m->esp += 4;	/* 481315: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 481316: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 481317: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 481318: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481319: add esp, 0xe4 */
	m->esp += 4 + 24; return;	/* 48131f: ret 0x18 */
}

/* space_traceNodes (0x483060), lifted by tools/lift.py */
static void lift_483060(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xa0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483060: sub esp, 0xa0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 483066: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 483067: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 483068: push esi */
	m->esi = m->ecx;	/* 483069: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48306b: push edi */
	m->edi = M32((DWORD)(m->esi + 0x74u));	/* 48306c: mov edi, dword ptr [esi + 0x74] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48306f: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_48362d;	/* 483071: jle 0x48362d */
	m->ebx = M32((DWORD)(m->esi + 0x78u));	/* 483077: mov ebx, dword ptr [esi + 0x78] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48307a: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_48362d;	/* 48307c: jle 0x48362d */
	m->ebp = M32((DWORD)(m->esi + 0x7cu));	/* 483082: mov ebp, dword ptr [esi + 0x7c] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 483085: test ebp, ebp */
	if (m->zf || m->sf != m->of) goto L_48362d;	/* 483087: jle 0x48362d */
	m->eax = M32((DWORD)(m->esp + 0xb4u));	/* 48308d: mov eax, dword ptr [esp + 0xb4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 483094: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 483097: fsub dword ptr [esi + 0x64] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 48309a: fdiv dword ptr [esi + 0x80] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4830a0: call 0x49ec14 */
	m->ecx = m->eax;	/* 4830a5: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4830a7: test ecx, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 4830a9: mov dword ptr [esp + 0x1c], ecx */
	if (m->sf == m->of) goto L_4830b9;	/* 4830ad: jge 0x4830b9 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 4830af: mov dword ptr [esp + 0x1c], 0 */
	goto L_4830c4;	/* 4830b7: jmp 0x4830c4 */
L_4830b9:
	m->eax = (DWORD)(m->edi + 0xffffffffu);	/* 4830b9: lea eax, [edi - 1] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4830bc: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_4830c4;	/* 4830be: jle 0x4830c4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4830c0: mov dword ptr [esp + 0x1c], eax */
L_4830c4:
	m->ecx = M32((DWORD)(m->esp + 0xb4u));	/* 4830c4: mov ecx, dword ptr [esp + 0xb4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 4830cb: fld dword ptr [ecx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 4830cd: fsub dword ptr [esi + 0x5c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 4830d0: fdiv dword ptr [esi + 0x84] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4830d6: call 0x49ec14 */
	m->ecx = m->eax;	/* 4830db: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4830dd: test ecx, ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 4830df: mov dword ptr [esp + 0x2c], ecx */
	if (m->sf == m->of) goto L_4830ef;	/* 4830e3: jge 0x4830ef */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 4830e5: mov dword ptr [esp + 0x2c], 0 */
	goto L_4830fa;	/* 4830ed: jmp 0x4830fa */
L_4830ef:
	m->eax = (DWORD)(m->ebx + 0xffffffffu);	/* 4830ef: lea eax, [ebx - 1] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4830f2: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_4830fa;	/* 4830f4: jle 0x4830fa */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 4830f6: mov dword ptr [esp + 0x2c], eax */
L_4830fa:
	m->edx = M32((DWORD)(m->esp + 0xb4u));	/* 4830fa: mov edx, dword ptr [esp + 0xb4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x4u)));	/* 483101: fld dword ptr [edx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 483104: fsub dword ptr [esi + 0x60] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 483107: fdiv dword ptr [esi + 0x88] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48310d: call 0x49ec14 */
	m->ecx = m->eax;	/* 483112: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 483114: test ecx, ecx */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 483116: mov dword ptr [esp + 0x44], ecx */
	if (m->sf == m->of) goto L_483126;	/* 48311a: jge 0x483126 */
	M32((DWORD)(m->esp + 0x44u)) = 0x0u;	/* 48311c: mov dword ptr [esp + 0x44], 0 */
	goto L_483131;	/* 483124: jmp 0x483131 */
L_483126:
	m->eax = (DWORD)(m->ebp + 0xffffffffu);	/* 483126: lea eax, [ebp - 1] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483129: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_483131;	/* 48312b: jle 0x483131 */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 48312d: mov dword ptr [esp + 0x44], eax */
L_483131:
	m->eax = M32((DWORD)(m->esp + 0xb8u));	/* 483131: mov eax, dword ptr [esp + 0xb8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 483138: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 48313b: fsub dword ptr [esi + 0x64] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 48313e: fdiv dword ptr [esi + 0x80] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 483144: call 0x49ec14 */
	m->ecx = m->eax;	/* 483149: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48314b: test ecx, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 48314d: mov dword ptr [esp + 0x18], ecx */
	if (m->sf == m->of) goto L_48315d;	/* 483151: jge 0x48315d */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 483153: mov dword ptr [esp + 0x18], 0 */
	goto L_483168;	/* 48315b: jmp 0x483168 */
L_48315d:
	m->eax = (DWORD)(m->edi + 0xffffffffu);	/* 48315d: lea eax, [edi - 1] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483160: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_483168;	/* 483162: jle 0x483168 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 483164: mov dword ptr [esp + 0x18], eax */
L_483168:
	m->edi = M32((DWORD)(m->esp + 0xb8u));	/* 483168: mov edi, dword ptr [esp + 0xb8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 48316f: fld dword ptr [edi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 483171: fsub dword ptr [esi + 0x5c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 483174: fdiv dword ptr [esi + 0x84] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48317a: call 0x49ec14 */
	m->ecx = m->eax;	/* 48317f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 483181: test ecx, ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 483183: mov dword ptr [esp + 0x48], ecx */
	if (m->sf == m->of) goto L_483193;	/* 483187: jge 0x483193 */
	M32((DWORD)(m->esp + 0x48u)) = 0x0u;	/* 483189: mov dword ptr [esp + 0x48], 0 */
	goto L_48319e;	/* 483191: jmp 0x48319e */
L_483193:
	m->eax = (DWORD)(m->ebx + 0xffffffffu);	/* 483193: lea eax, [ebx - 1] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483196: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48319e;	/* 483198: jle 0x48319e */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 48319a: mov dword ptr [esp + 0x48], eax */
L_48319e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 48319e: fld dword ptr [edi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 4831a1: fsub dword ptr [esi + 0x60] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 4831a4: fdiv dword ptr [esi + 0x88] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4831aa: call 0x49ec14 */
	m->ecx = m->eax;	/* 4831af: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4831b1: test ecx, ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 4831b3: mov dword ptr [esp + 0x30], ecx */
	if (m->sf == m->of) goto L_4831c3;	/* 4831b7: jge 0x4831c3 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 4831b9: mov dword ptr [esp + 0x30], 0 */
	goto L_4831ce;	/* 4831c1: jmp 0x4831ce */
L_4831c3:
	m->eax = (DWORD)(m->ebp + 0xffffffffu);	/* 4831c3: lea eax, [ebp - 1] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4831c6: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_4831ce;	/* 4831c8: jle 0x4831ce */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 4831ca: mov dword ptr [esp + 0x30], eax */
L_4831ce:
	m->ebp = M32((DWORD)(m->esp + 0x44u));	/* 4831ce: mov ebp, dword ptr [esp + 0x44] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4831d2: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4831d6: xor ebx, ebx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4831d8: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4831dc: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4831e0: cmp ebp, ecx */
	m->ebx = (m->ebx & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 4831e2: setg bl */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 4831e5: dec ebx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4831e6: xor ecx, ecx */
	{ DWORD a_ = m->ebx, b_ = 0x2u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4831e8: and ebx, 2 */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 4831eb: dec ebx */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4831ec: cmp edx, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 4831ee: setg cl */
	m->edx = M32((DWORD)(m->esp + 0x48u));	/* 4831f1: mov edx, dword ptr [esp + 0x48] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4831f5: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4831f6: and ecx, 2 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4831f9: xor eax, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 4831fb: fld dword ptr [edi] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4831fd: dec ecx */
	M32((DWORD)(m->esp + 0x78u)) = m->ebx;	/* 4831fe: mov dword ptr [esp + 0x78], ebx */
	M32((DWORD)(m->esp + 0x4cu)) = m->ecx;	/* 483202: mov dword ptr [esp + 0x4c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 483206: mov ecx, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48320a: cmp ecx, edx */
	m->edx = M32((DWORD)(m->esp + 0xb4u));	/* 48320c: mov edx, dword ptr [esp + 0xb4] */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 483213: setg al */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x0u));	/* 483216: fsub dword ptr [edx] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 483218: dec eax */
	m->ecx = m->ebp;	/* 483219: mov ecx, ebp */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48321b: and eax, 2 */
	M32((DWORD)(m->esp + 0x40u)) = m->ecx;	/* 48321e: mov dword ptr [esp + 0x40], ecx */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 483222: fstp dword ptr [esp + 0x88] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 483229: fld dword ptr [edi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x4u));	/* 48322c: fsub dword ptr [edx + 4] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48322f: dec eax */
	M32((DWORD)(m->esp + 0x68u)) = m->eax;	/* 483230: mov dword ptr [esp + 0x68], eax */
	MF((DWORD)(m->esp + 0x8cu)) = (float)ST(0); FPOP();	/* 483234: fstp dword ptr [esp + 0x8c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 48323b: fld dword ptr [edi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x8u));	/* 48323e: fsub dword ptr [edx + 8] */
	MF((DWORD)(m->esp + 0x90u)) = (float)ST(0); FPOP();	/* 483241: fstp dword ptr [esp + 0x90] */
L_483248:
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483248: cmp ecx, ebp */
	if (!m->zf) goto L_48326c;	/* 48324a: jne 0x48326c */
	m->ebx = m->edx;	/* 48324c: mov ebx, edx */
	m->ebp = M32((DWORD)(m->ebx + 0x0u));	/* 48324e: mov ebp, dword ptr [ebx] */
	M32((DWORD)(m->esp + 0x34u)) = m->ebp;	/* 483250: mov dword ptr [esp + 0x34], ebp */
	m->ebp = M32((DWORD)(m->ebx + 0x4u));	/* 483254: mov ebp, dword ptr [ebx + 4] */
	M32((DWORD)(m->esp + 0x38u)) = m->ebp;	/* 483257: mov dword ptr [esp + 0x38], ebp */
	m->ebp = M32((DWORD)(m->esp + 0x4cu));	/* 48325b: mov ebp, dword ptr [esp + 0x4c] */
	m->ebx = M32((DWORD)(m->ebx + 0x8u));	/* 48325f: mov ebx, dword ptr [ebx + 8] */
	M32((DWORD)(m->esp + 0x3cu)) = m->ebx;	/* 483262: mov dword ptr [esp + 0x3c], ebx */
	m->ebx = M32((DWORD)(m->esp + 0x78u));	/* 483266: mov ebx, dword ptr [esp + 0x78] */
	goto L_4832c5;	/* 48326a: jmp 0x4832c5 */
L_48326c:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48326c: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_483276;	/* 48326e: jle 0x483276 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x40u)));	/* 483270: fild dword ptr [esp + 0x40] */
	goto L_483281;	/* 483274: jmp 0x483281 */
L_483276:
	m->ebp = (DWORD)(m->ecx + 0x1u);	/* 483276: lea ebp, [ecx + 1] */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 483279: mov dword ptr [esp + 0x14], ebp */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 48327d: fild dword ptr [esp + 0x14] */
L_483281:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 483281: fmul dword ptr [esi + 0x88] */
	m->ebp = M32((DWORD)(m->esp + 0x4cu));	/* 483287: mov ebp, dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 48328b: fadd dword ptr [esi + 0x60] */
	{ long double t = ST(0); FPUSH(t); }	/* 48328e: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x4u));	/* 483290: fsub dword ptr [edx + 4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x8cu));	/* 483293: fdiv dword ptr [esp + 0x8c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 48329a: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 48329e: fld dword ptr [esp + 0x88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4832a5: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x0u));	/* 4832a9: fadd dword ptr [edx] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 4832ab: fstp dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4832af: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x90u)));	/* 4832b3: fld dword ptr [esp + 0x90] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4832ba: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x8u));	/* 4832be: fadd dword ptr [edx + 8] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4832c1: fstp dword ptr [esp + 0x3c] */
L_4832c5:
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->esp + 0x30u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4832c5: cmp ecx, dword ptr [esp + 0x30] */
	if (!m->zf) goto L_4832e1;	/* 4832c9: jne 0x4832e1 */
	m->edx = M32((DWORD)(m->edi + 0x0u));	/* 4832cb: mov edx, dword ptr [edi] */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 4832cd: mov dword ptr [esp + 0x5c], edx */
	m->edx = M32((DWORD)(m->edi + 0x4u));	/* 4832d1: mov edx, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x60u)) = m->edx;	/* 4832d4: mov dword ptr [esp + 0x60], edx */
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 4832d8: mov edx, dword ptr [edi + 8] */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 4832db: mov dword ptr [esp + 0x64], edx */
	goto L_483336;	/* 4832df: jmp 0x483336 */
L_4832e1:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4832e1: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_4832f2;	/* 4832e3: jle 0x4832f2 */
	m->edi = (DWORD)(m->ecx + 0x1u);	/* 4832e5: lea edi, [ecx + 1] */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 4832e8: mov dword ptr [esp + 0x14], edi */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4832ec: fild dword ptr [esp + 0x14] */
	goto L_4832f6;	/* 4832f0: jmp 0x4832f6 */
L_4832f2:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x40u)));	/* 4832f2: fild dword ptr [esp + 0x40] */
L_4832f6:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 4832f6: fmul dword ptr [esi + 0x88] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 4832fc: fadd dword ptr [esi + 0x60] */
	{ long double t = ST(0); FPUSH(t); }	/* 4832ff: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x4u));	/* 483301: fsub dword ptr [edx + 4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x8cu));	/* 483304: fdiv dword ptr [esp + 0x8c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 48330b: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 48330f: fld dword ptr [esp + 0x88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 483316: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x0u));	/* 48331a: fadd dword ptr [edx] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 48331c: fstp dword ptr [esp + 0x5c] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 483320: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x90u)));	/* 483324: fld dword ptr [esp + 0x90] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48332b: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x8u));	/* 48332f: fadd dword ptr [edx + 8] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 483332: fstp dword ptr [esp + 0x64] */
L_483336:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 483336: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 48333a: fsub dword ptr [esp + 0x34] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 48333e: mov ebx, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 483342: fstp dword ptr [esp + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 483346: fld dword ptr [esp + 0x60] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 48334a: fsub dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 48334e: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 483352: fld dword ptr [esp + 0x64] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 483356: fsub dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 48335a: fstp dword ptr [esp + 0x74] */
L_48335e:
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 48335e: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x14u)) = m->ebx;	/* 483362: mov dword ptr [esp + 0x14], ebx */
	{ DWORD a_ = m->ebx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483366: cmp ebx, edx */
	if (!m->zf) goto L_483384;	/* 483368: jne 0x483384 */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 48336a: mov edx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 48336e: mov dword ptr [esp + 0x20], edx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 483372: mov edx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 483376: mov dword ptr [esp + 0x24], edx */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 48337a: mov edx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 48337e: mov dword ptr [esp + 0x28], edx */
	goto L_4833ce;	/* 483382: jmp 0x4833ce */
L_483384:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 483384: test ebp, ebp */
	if (m->zf || m->sf != m->of) goto L_48338e;	/* 483386: jle 0x48338e */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 483388: fild dword ptr [esp + 0x14] */
	goto L_483399;	/* 48338c: jmp 0x483399 */
L_48338e:
	m->edx = (DWORD)(m->ebx + 0x1u);	/* 48338e: lea edx, [ebx + 1] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 483391: mov dword ptr [esp + 0x10], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 483395: fild dword ptr [esp + 0x10] */
L_483399:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 483399: fmul dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 48339f: fadd dword ptr [esi + 0x64] */
	{ long double t = ST(0); FPUSH(t); }	/* 4833a2: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 4833a4: fsub dword ptr [esp + 0x3c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x74u));	/* 4833a8: fdiv dword ptr [esp + 0x74] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x6cu)));	/* 4833ac: fld dword ptr [esp + 0x6c] */
	ST(0) = ST(0) * ST(1);	/* 4833b0: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 4833b2: fadd dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4833b6: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 4833ba: fld dword ptr [esp + 0x70] */
	ST(0) = ST(0) * ST(1);	/* 4833be: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 4833c0: fadd dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4833c4: fstp dword ptr [esp + 0x24] */
	ST(0) = ST(0); FPOP();	/* 4833c8: fstp st(0) */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4833ca: fstp dword ptr [esp + 0x28] */
L_4833ce:
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->esp + 0x18u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4833ce: cmp ebx, dword ptr [esp + 0x18] */
	if (!m->zf) goto L_4833ee;	/* 4833d2: jne 0x4833ee */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 4833d4: mov edx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x50u)) = m->edx;	/* 4833d8: mov dword ptr [esp + 0x50], edx */
	m->edx = M32((DWORD)(m->esp + 0x60u));	/* 4833dc: mov edx, dword ptr [esp + 0x60] */
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 4833e0: mov dword ptr [esp + 0x54], edx */
	m->edx = M32((DWORD)(m->esp + 0x64u));	/* 4833e4: mov edx, dword ptr [esp + 0x64] */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 4833e8: mov dword ptr [esp + 0x58], edx */
	goto L_483438;	/* 4833ec: jmp 0x483438 */
L_4833ee:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4833ee: test ebp, ebp */
	if (m->zf || m->sf != m->of) goto L_4833ff;	/* 4833f0: jle 0x4833ff */
	m->edx = (DWORD)(m->ebx + 0x1u);	/* 4833f2: lea edx, [ebx + 1] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 4833f5: mov dword ptr [esp + 0x14], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4833f9: fild dword ptr [esp + 0x14] */
	goto L_483403;	/* 4833fd: jmp 0x483403 */
L_4833ff:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4833ff: fild dword ptr [esp + 0x14] */
L_483403:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 483403: fmul dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 483409: fadd dword ptr [esi + 0x64] */
	{ long double t = ST(0); FPUSH(t); }	/* 48340c: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 48340e: fsub dword ptr [esp + 0x3c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x74u));	/* 483412: fdiv dword ptr [esp + 0x74] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x6cu)));	/* 483416: fld dword ptr [esp + 0x6c] */
	ST(0) = ST(0) * ST(1);	/* 48341a: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 48341c: fadd dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 483420: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 483424: fld dword ptr [esp + 0x70] */
	ST(0) = ST(0) * ST(1);	/* 483428: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 48342a: fadd dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 48342e: fstp dword ptr [esp + 0x54] */
	ST(0) = ST(0); FPOP();	/* 483432: fstp st(0) */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 483434: fstp dword ptr [esp + 0x58] */
L_483438:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 483438: fld dword ptr [esp + 0x50] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 48343c: fsub dword ptr [esp + 0x20] */
	m->edi = M32((DWORD)(m->esp + 0x2cu));	/* 483440: mov edi, dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0); FPOP();	/* 483444: fstp dword ptr [esp + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 483448: fld dword ptr [esp + 0x54] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 48344c: fsub dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x80u)) = (float)ST(0); FPOP();	/* 483450: fstp dword ptr [esp + 0x80] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 483457: fld dword ptr [esp + 0x58] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 48345b: fsub dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 48345f: fstp dword ptr [esp + 0x84] */
L_483466:
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 483466: mov edx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 48346a: mov dword ptr [esp + 0x14], edi */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48346e: cmp edi, edx */
	if (!m->zf) goto L_483495;	/* 483470: jne 0x483495 */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 483472: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0xa0u)) = m->edx;	/* 483476: mov dword ptr [esp + 0xa0], edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 48347d: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0xa4u)) = m->edx;	/* 483481: mov dword ptr [esp + 0xa4], edx */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 483488: mov edx, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0xa8u)) = m->edx;	/* 48348c: mov dword ptr [esp + 0xa8], edx */
	goto L_4834f4;	/* 483493: jmp 0x4834f4 */
L_483495:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 483495: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48349f;	/* 483497: jle 0x48349f */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 483499: fild dword ptr [esp + 0x14] */
	goto L_4834aa;	/* 48349d: jmp 0x4834aa */
L_48349f:
	m->edx = (DWORD)(m->edi + 0x1u);	/* 48349f: lea edx, [edi + 1] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 4834a2: mov dword ptr [esp + 0x10], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 4834a6: fild dword ptr [esp + 0x10] */
L_4834aa:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 4834aa: fmul dword ptr [esi + 0x84] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 4834b0: fadd dword ptr [esi + 0x5c] */
	{ long double t = ST(0); FPUSH(t); }	/* 4834b3: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 4834b5: fsub dword ptr [esp + 0x20] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x7cu));	/* 4834b9: fdiv dword ptr [esp + 0x7c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4834bd: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0xa0u)) = (float)ST(0); FPOP();	/* 4834c1: fstp dword ptr [esp + 0xa0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 4834c8: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4834cf: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 4834d3: fadd dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0xa4u)) = (float)ST(0); FPOP();	/* 4834d7: fstp dword ptr [esp + 0xa4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 4834de: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4834e5: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 4834e9: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0xa8u)) = (float)ST(0); FPOP();	/* 4834ed: fstp dword ptr [esp + 0xa8] */
L_4834f4:
	m->ebp = M32((DWORD)(m->esp + 0x48u));	/* 4834f4: mov ebp, dword ptr [esp + 0x48] */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4834f8: cmp edi, ebp */
	if (!m->zf) goto L_48351f;	/* 4834fa: jne 0x48351f */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 4834fc: mov eax, dword ptr [esp + 0x50] */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 483500: mov edx, dword ptr [esp + 0x54] */
	M32((DWORD)(m->esp + 0x94u)) = m->eax;	/* 483504: mov dword ptr [esp + 0x94], eax */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 48350b: mov eax, dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0x98u)) = m->edx;	/* 48350f: mov dword ptr [esp + 0x98], edx */
	M32((DWORD)(m->esp + 0x9cu)) = m->eax;	/* 483516: mov dword ptr [esp + 0x9c], eax */
	goto L_48357e;	/* 48351d: jmp 0x48357e */
L_48351f:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48351f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_483530;	/* 483521: jle 0x483530 */
	m->edx = (DWORD)(m->edi + 0x1u);	/* 483523: lea edx, [edi + 1] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 483526: mov dword ptr [esp + 0x14], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 48352a: fild dword ptr [esp + 0x14] */
	goto L_483534;	/* 48352e: jmp 0x483534 */
L_483530:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 483530: fild dword ptr [esp + 0x14] */
L_483534:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 483534: fmul dword ptr [esi + 0x84] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 48353a: fadd dword ptr [esi + 0x5c] */
	{ long double t = ST(0); FPUSH(t); }	/* 48353d: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 48353f: fsub dword ptr [esp + 0x20] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x7cu));	/* 483543: fdiv dword ptr [esp + 0x7c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 483547: fstp dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x94u)) = (float)ST(0); FPOP();	/* 48354b: fstp dword ptr [esp + 0x94] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 483552: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 483559: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 48355d: fadd dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x98u)) = (float)ST(0); FPOP();	/* 483561: fstp dword ptr [esp + 0x98] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 483568: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48356f: fmul dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 483573: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x9cu)) = (float)ST(0); FPOP();	/* 483577: fstp dword ptr [esp + 0x9c] */
L_48357e:
	m->eax = m->ecx;	/* 48357e: mov eax, ecx */
	m->edx = M32((DWORD)(m->esi + 0x54u));	/* 483580: mov edx, dword ptr [esi + 0x54] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esi + 0x74u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 483583: imul eax, dword ptr [esi + 0x74] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 483587: add eax, ebx */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esi + 0x78u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 483589: imul eax, dword ptr [esi + 0x78] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48358d: add eax, edi */
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->edx + m->eax*2 + 0x0u))) & 0xffff);	/* 48358f: mov ax, word ptr [edx + eax*2] */
	{ DWORD a_ = (m->eax & 0xffff), b_ = 0xffffu & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 483593: cmp ax, 0xffff */
	if (m->zf) goto L_4835e6;	/* 483597: je 0x4835e6 */
	m->ecx = M32((DWORD)(m->esp + 0xc4u));	/* 483599: mov ecx, dword ptr [esp + 0xc4] */
	m->edx = M32((DWORD)(m->esp + 0xc0u));	/* 4835a0: mov edx, dword ptr [esp + 0xc0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4835a7: push ecx */
	m->ecx = (DWORD)(m->esp + 0xb0u);	/* 4835a8: lea ecx, [esp + 0xb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4835af: push edx */
	m->edx = M32((DWORD)(m->esp + 0xc4u));	/* 4835b0: mov edx, dword ptr [esp + 0xc4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4835b7: push ecx */
	m->ecx = (DWORD)(m->esp + 0xa0u);	/* 4835b8: lea ecx, [esp + 0xa0] */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4835bf: and eax, 0xffff */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4835c4: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4835c5: push ecx */
	m->edx = (DWORD)(m->esp + 0xb4u);	/* 4835c6: lea edx, [esp + 0xb4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4835cd: lea ecx, [eax + eax*4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4835d0: push edx */
	m->edx = M32((DWORD)(m->esi + 0x44u));	/* 4835d1: mov edx, dword ptr [esi + 0x44] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4835d4: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4835d7: add ecx, edx */
	m->esp -= 4; M32(m->esp) = 0x4835deu; lift_4809f0(m);	/* 4835d9: call 0x4809f0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4835de: test eax, eax */
	if (!m->zf) goto L_48362f;	/* 4835e0: jne 0x48362f */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 4835e2: mov ecx, dword ptr [esp + 0x40] */
L_4835e6:
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 4835e6: mov eax, dword ptr [esp + 0x68] */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4835ea: cmp edi, ebp */
	if (m->zf) goto L_4835f5;	/* 4835ec: je 0x4835f5 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4835ee: add edi, eax */
	goto L_483466;	/* 4835f0: jmp 0x483466 */
L_4835f5:
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->esp + 0x18u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4835f5: cmp ebx, dword ptr [esp + 0x18] */
	if (m->zf) goto L_483606;	/* 4835f9: je 0x483606 */
	m->ebp = M32((DWORD)(m->esp + 0x4cu));	/* 4835fb: mov ebp, dword ptr [esp + 0x4c] */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4835ff: add ebx, ebp */
	goto L_48335e;	/* 483601: jmp 0x48335e */
L_483606:
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->esp + 0x30u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483606: cmp ecx, dword ptr [esp + 0x30] */
	if (m->zf) goto L_48362d;	/* 48360a: je 0x48362d */
	m->ebx = M32((DWORD)(m->esp + 0x78u));	/* 48360c: mov ebx, dword ptr [esp + 0x78] */
	m->edi = M32((DWORD)(m->esp + 0xb8u));	/* 483610: mov edi, dword ptr [esp + 0xb8] */
	m->edx = M32((DWORD)(m->esp + 0xb4u));	/* 483617: mov edx, dword ptr [esp + 0xb4] */
	m->ebp = M32((DWORD)(m->esp + 0x44u));	/* 48361e: mov ebp, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483622: add ecx, ebx */
	M32((DWORD)(m->esp + 0x40u)) = m->ecx;	/* 483624: mov dword ptr [esp + 0x40], ecx */
	goto L_483248;	/* 483628: jmp 0x483248 */
L_48362d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48362d: xor eax, eax */
L_48362f:
	m->edi = M32(m->esp); m->esp += 4;	/* 48362f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 483630: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 483631: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 483632: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483633: add esp, 0xa0 */
	m->esp += 4 + 20; return;	/* 483639: ret 0x14 */
}

/* collision_rayTrace (0x471740), lifted by tools/lift.py */
static void lift_471740(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x214u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 471740: sub esp, 0x214 */
	m->edx = M32((DWORD)(m->ecx + 0x13c9b24u));	/* 471746: mov edx, dword ptr [ecx + 0x13c9b24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47174c: xor eax, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47174e: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x220u));	/* 47174f: mov ebx, dword ptr [esp + 0x220] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 471756: cmp edx, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 471758: mov dword ptr [esp + 0x28], ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 47175c: mov dword ptr [esp + 0x2c], eax */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 471760: mov dword ptr [esp + 0x58], eax */
	if (m->zf || m->sf != m->of) goto L_472282;	/* 471764: jle 0x472282 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47176a: push ebp */
	m->eax = (DWORD)(m->ecx + 0x9ca0f8u);	/* 47176b: lea eax, [ecx + 0x9ca0f8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 471771: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 471772: push edi */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 471773: mov dword ptr [esp + 0x60], eax */
	m->esi = (DWORD)(m->ecx + 0x131af88u);	/* 471777: lea esi, [ecx + 0x131af88] */
L_47177d:
	m->eax = M32((DWORD)(m->esi + 0xfffffec0u));	/* 47177d: mov eax, dword ptr [esi - 0x140] */
	m->edi = 0x1u;	/* 471783: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 471788: cmp eax, edi */
	if (!m->zf) goto L_472262;	/* 47178a: jne 0x472262 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x14cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 471790: cmp dword ptr [esi + 0x14c], edi */
	if (!m->zf) goto L_472262;	/* 471796: jne 0x472262 */
	m->edx = M32((DWORD)(m->esi + 0x148u));	/* 47179c: mov edx, dword ptr [esi + 0x148] */
	m->eax = M32((DWORD)(m->edx + 0x8u));	/* 4717a2: mov eax, dword ptr [edx + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4717a5: test eax, eax */
	if (m->zf) goto L_472262;	/* 4717a7: je 0x472262 */
	m->eax = M32((DWORD)(m->esp + 0x228u));	/* 4717ad: mov eax, dword ptr [esp + 0x228] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4717b4: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4717b5: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 4717b8: fmul dword ptr [esi + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4717bb: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xfffffff0u));	/* 4717bd: fmul dword ptr [esi - 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4717c0: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4717c2: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 4717c5: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4717c7: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 4717c9: fadd dword ptr [esi + 0x20] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4717cc: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4717d0: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4717d3: fmul dword ptr [esi + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4717d6: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4717d9: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4717dc: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4717de: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xfffffff4u));	/* 4717e0: fmul dword ptr [esi - 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4717e3: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 4717e5: fadd dword ptr [esi + 0x24] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 4717e8: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4717ec: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4717ef: fmul dword ptr [esi + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4717f2: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 4717f5: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4717f8: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4717fa: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xfffffff8u));	/* 4717fc: fmul dword ptr [esi - 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4717ff: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 471801: fadd dword ptr [esi + 0x28] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 471804: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 471808: fld dword ptr [ebx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xfffffff0u));	/* 47180a: fmul dword ptr [esi - 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 47180d: fld dword ptr [ebx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 471810: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 471812: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 471814: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 471817: fmul dword ptr [ebx + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47181a: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 47181c: fadd dword ptr [esi + 0x20] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47181f: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 471823: fld dword ptr [ebx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 471826: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 471829: fld dword ptr [ebx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xfffffff4u));	/* 47182b: fmul dword ptr [esi - 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47182e: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 471830: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 471833: fmul dword ptr [ebx + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 471836: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 471838: fadd dword ptr [esi + 0x24] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47183b: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 47183f: fld dword ptr [ebx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 471842: fmul dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 471845: fld dword ptr [ebx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0xfffffff8u));	/* 471847: fmul dword ptr [esi - 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47184a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 47184c: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47184f: fmul dword ptr [ebx + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 471852: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 471854: fadd dword ptr [esi + 0x28] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 471857: fst dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47185b: fsub dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47185f: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471862: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471866: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47186a: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47186b: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47186e: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471872: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471876: push ecx */
	m->ecx = (DWORD)(m->esp + 0x200u);	/* 471877: lea ecx, [esp + 0x200] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47187e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x471886u; native_call(m, 0x4722c0u);	/* 471881: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471886: mov ecx, dword ptr [eax] */
	m->ebp = M32((DWORD)(m->esi + 0x138u));	/* 471888: mov ebp, dword ptr [esi + 0x138] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47188e: mov dword ptr [esp + 0x10], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471892: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 471895: mov dword ptr [esp + 0x14], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471899: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 47189c: mov dword ptr [esp + 0x18], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4718a0: fld dword ptr [esp + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x34u)); FPOP();	/* 4718a4: fcomp dword ptr [ebp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4718a7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4718a9: test ah, 0x41 */
	if (m->zf) goto L_4718b2;	/* 4718ac: je 0x4718b2 */
	m->edx = m->edi;	/* 4718ae: mov edx, edi */
	goto L_4718c9;	/* 4718b0: jmp 0x4718c9 */
L_4718b2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4718b2: fld dword ptr [esp + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x40u)); FPOP();	/* 4718b6: fcomp dword ptr [ebp + 0x40] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4718b9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4718bb: test ah, 1 */
	if (!m->zf) goto L_4718c7;	/* 4718be: jne 0x4718c7 */
	m->edx = 0x10u;	/* 4718c0: mov edx, 0x10 */
	goto L_4718c9;	/* 4718c5: jmp 0x4718c9 */
L_4718c7:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4718c7: xor edx, edx */
L_4718c9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4718c9: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x38u)); FPOP();	/* 4718cd: fcomp dword ptr [ebp + 0x38] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4718d0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4718d2: test ah, 0x41 */
	if (m->zf) goto L_4718dc;	/* 4718d5: je 0x4718dc */
	{ DWORD a_ = ((m->edx >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->edx = (m->edx & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 4718d7: or dh, 1 */
	goto L_4718ed;	/* 4718da: jmp 0x4718ed */
L_4718dc:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 4718dc: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x44u)); FPOP();	/* 4718e0: fcomp dword ptr [ebp + 0x44] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4718e3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4718e5: test ah, 1 */
	if (!m->zf) goto L_4718ed;	/* 4718e8: jne 0x4718ed */
	{ DWORD a_ = ((m->edx >> 8) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->edx = (m->edx & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 4718ea: or dh, 0x10 */
L_4718ed:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4718ed: fld dword ptr [esp + 0x30] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x3cu)); FPOP();	/* 4718f1: fcomp dword ptr [ebp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4718f4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4718f6: test ah, 0x41 */
	if (m->zf) goto L_471903;	/* 4718f9: je 0x471903 */
	{ DWORD a_ = m->edx, b_ = 0x10000u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4718fb: or edx, 0x10000 */
	goto L_471917;	/* 471901: jmp 0x471917 */
L_471903:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 471903: fld dword ptr [esp + 0x30] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x48u)); FPOP();	/* 471907: fcomp dword ptr [ebp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47190a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47190c: test ah, 1 */
	if (!m->zf) goto L_471917;	/* 47190f: jne 0x471917 */
	{ DWORD a_ = m->edx, b_ = 0x100000u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 471911: or edx, 0x100000 */
L_471917:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 471917: fld dword ptr [esp + 0x1c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x34u)); FPOP();	/* 47191b: fcomp dword ptr [ebp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47191e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471920: test ah, 0x41 */
	if (m->zf) goto L_471929;	/* 471923: je 0x471929 */
	m->ecx = m->edi;	/* 471925: mov ecx, edi */
	goto L_471940;	/* 471927: jmp 0x471940 */
L_471929:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 471929: fld dword ptr [esp + 0x1c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x40u)); FPOP();	/* 47192d: fcomp dword ptr [ebp + 0x40] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471930: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471932: test ah, 1 */
	if (!m->zf) goto L_47193e;	/* 471935: jne 0x47193e */
	m->ecx = 0x10u;	/* 471937: mov ecx, 0x10 */
	goto L_471940;	/* 47193c: jmp 0x471940 */
L_47193e:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47193e: xor ecx, ecx */
L_471940:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 471940: fld dword ptr [esp + 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x38u)); FPOP();	/* 471944: fcomp dword ptr [ebp + 0x38] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471947: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471949: test ah, 0x41 */
	if (m->zf) goto L_471953;	/* 47194c: je 0x471953 */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 47194e: or ch, 1 */
	goto L_471964;	/* 471951: jmp 0x471964 */
L_471953:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 471953: fld dword ptr [esp + 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x44u)); FPOP();	/* 471957: fcomp dword ptr [ebp + 0x44] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47195a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47195c: test ah, 1 */
	if (!m->zf) goto L_471964;	/* 47195f: jne 0x471964 */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ecx = (m->ecx & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 471961: or ch, 0x10 */
L_471964:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471964: fld dword ptr [esp + 0x24] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x3cu)); FPOP();	/* 471968: fcomp dword ptr [ebp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47196b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47196d: test ah, 0x41 */
	if (m->zf) goto L_47197a;	/* 471970: je 0x47197a */
	{ DWORD a_ = m->ecx, b_ = 0x10000u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 471972: or ecx, 0x10000 */
	goto L_47198e;	/* 471978: jmp 0x47198e */
L_47197a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47197a: fld dword ptr [esp + 0x24] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x48u)); FPOP();	/* 47197e: fcomp dword ptr [ebp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471981: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471983: test ah, 1 */
	if (!m->zf) goto L_47198e;	/* 471986: jne 0x47198e */
	{ DWORD a_ = m->ecx, b_ = 0x100000u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 471988: or ecx, 0x100000 */
L_47198e:
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47198e: test edx, ecx */
	if (!m->zf) goto L_47225e;	/* 471990: jne 0x47225e */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471996: test dl, 1 */
	if (m->zf) goto L_471a79;	/* 471999: je 0x471a79 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x34u)));	/* 47199f: fld dword ptr [ebp + 0x34] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 4719a2: fsub dword ptr [esp + 0x28] */
	{ long double t = ST(0); FPUSH(t); }	/* 4719a6: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4719a8: fmul dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0xe0u)) = (float)ST(0); FPOP();	/* 4719ac: fstp dword ptr [esp + 0xe0] */
	{ long double t = ST(0); FPUSH(t); }	/* 4719b3: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 4719b5: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0xe4u)) = (float)ST(0); FPOP();	/* 4719b9: fstp dword ptr [esp + 0xe4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 4719c0: fmul dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe0u)));	/* 4719c4: fld dword ptr [esp + 0xe0] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4719cb: fdiv dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x110u)) = (float)ST(0); FPOP();	/* 4719cf: fstp dword ptr [esp + 0x110] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe4u)));	/* 4719d6: fld dword ptr [esp + 0xe4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4719dd: fdiv dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x114u)) = (float)ST(0); FPOP();	/* 4719e1: fstp dword ptr [esp + 0x114] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4719e8: fdiv dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x110u)));	/* 4719ec: fld dword ptr [esp + 0x110] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 4719f3: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4719f7: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x114u)));	/* 4719fb: fld dword ptr [esp + 0x114] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 471a02: fadd dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x48u));	/* 471a06: mov edx, dword ptr [esp + 0x48] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 471a0a: mov dword ptr [esp + 0x28], edx */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 471a0e: fstp dword ptr [esp + 0x4c] */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 471a12: mov eax, dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471a16: fadd dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 471a1a: mov dword ptr [esp + 0x2c], eax */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 471a1e: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 471a22: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 471a26: fsub dword ptr [esp + 0x48] */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 471a2a: mov edx, dword ptr [esp + 0x50] */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 471a2e: mov dword ptr [esp + 0x30], edx */
	MF((DWORD)(m->esp + 0x8cu)) = (float)ST(0); FPOP();	/* 471a32: fstp dword ptr [esp + 0x8c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 471a39: fld dword ptr [esp + 0x20] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 471a3d: fsub dword ptr [esp + 0x4c] */
	m->eax = M32((DWORD)(m->esp + 0x8cu));	/* 471a41: mov eax, dword ptr [esp + 0x8c] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 471a48: mov dword ptr [esp + 0x10], eax */
	MF((DWORD)(m->esp + 0x90u)) = (float)ST(0); FPOP();	/* 471a4c: fstp dword ptr [esp + 0x90] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471a53: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 471a57: fsub dword ptr [esp + 0x50] */
	m->edx = M32((DWORD)(m->esp + 0x90u));	/* 471a5b: mov edx, dword ptr [esp + 0x90] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 471a62: mov dword ptr [esp + 0x14], edx */
	MF((DWORD)(m->esp + 0x94u)) = (float)ST(0); FPOP();	/* 471a66: fstp dword ptr [esp + 0x94] */
	m->eax = M32((DWORD)(m->esp + 0x94u));	/* 471a6d: mov eax, dword ptr [esp + 0x94] */
	goto L_471b57;	/* 471a74: jmp 0x471b57 */
L_471a79:
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471a79: test dl, 0x10 */
	if (m->zf) goto L_471b5b;	/* 471a7c: je 0x471b5b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x40u)));	/* 471a82: fld dword ptr [ebp + 0x40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 471a85: fsub dword ptr [esp + 0x28] */
	{ long double t = ST(0); FPUSH(t); }	/* 471a89: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 471a8b: fmul dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0xf8u)) = (float)ST(0); FPOP();	/* 471a8f: fstp dword ptr [esp + 0xf8] */
	{ long double t = ST(0); FPUSH(t); }	/* 471a96: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 471a98: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0xfcu)) = (float)ST(0); FPOP();	/* 471a9c: fstp dword ptr [esp + 0xfc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471aa3: fmul dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xf8u)));	/* 471aa7: fld dword ptr [esp + 0xf8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 471aae: fdiv dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x128u)) = (float)ST(0); FPOP();	/* 471ab2: fstp dword ptr [esp + 0x128] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xfcu)));	/* 471ab9: fld dword ptr [esp + 0xfc] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 471ac0: fdiv dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x12cu)) = (float)ST(0); FPOP();	/* 471ac4: fstp dword ptr [esp + 0x12c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 471acb: fdiv dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x128u)));	/* 471acf: fld dword ptr [esp + 0x128] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 471ad6: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 471ada: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x12cu)));	/* 471ade: fld dword ptr [esp + 0x12c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 471ae5: fadd dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 471ae9: mov edx, dword ptr [esp + 0x54] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 471aed: mov dword ptr [esp + 0x28], edx */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 471af1: fstp dword ptr [esp + 0x58] */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 471af5: mov eax, dword ptr [esp + 0x58] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471af9: fadd dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 471afd: mov dword ptr [esp + 0x2c], eax */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 471b01: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 471b05: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 471b09: fsub dword ptr [esp + 0x54] */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 471b0d: mov edx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 471b11: mov dword ptr [esp + 0x30], edx */
	MF((DWORD)(m->esp + 0xa4u)) = (float)ST(0); FPOP();	/* 471b15: fstp dword ptr [esp + 0xa4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 471b1c: fld dword ptr [esp + 0x20] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x58u));	/* 471b20: fsub dword ptr [esp + 0x58] */
	m->eax = M32((DWORD)(m->esp + 0xa4u));	/* 471b24: mov eax, dword ptr [esp + 0xa4] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 471b2b: mov dword ptr [esp + 0x10], eax */
	MF((DWORD)(m->esp + 0xa8u)) = (float)ST(0); FPOP();	/* 471b2f: fstp dword ptr [esp + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471b36: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 471b3a: fsub dword ptr [esp + 0x5c] */
	m->edx = M32((DWORD)(m->esp + 0xa8u));	/* 471b3e: mov edx, dword ptr [esp + 0xa8] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 471b45: mov dword ptr [esp + 0x14], edx */
	MF((DWORD)(m->esp + 0xacu)) = (float)ST(0); FPOP();	/* 471b49: fstp dword ptr [esp + 0xac] */
	m->eax = M32((DWORD)(m->esp + 0xacu));	/* 471b50: mov eax, dword ptr [esp + 0xac] */
L_471b57:
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 471b57: mov dword ptr [esp + 0x18], eax */
L_471b5b:
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471b5b: test cl, 1 */
	if (m->zf) goto L_471c23;	/* 471b5e: je 0x471c23 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x34u)));	/* 471b64: fld dword ptr [ebp + 0x34] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471b67: fsub dword ptr [esp + 0x1c] */
	{ long double t = ST(0); FPUSH(t); }	/* 471b6b: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 471b6d: fmul dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0xd4u)) = (float)ST(0); FPOP();	/* 471b71: fstp dword ptr [esp + 0xd4] */
	{ long double t = ST(0); FPUSH(t); }	/* 471b78: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 471b7a: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0xd8u)) = (float)ST(0); FPOP();	/* 471b7e: fstp dword ptr [esp + 0xd8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471b85: fmul dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xd4u)));	/* 471b89: fld dword ptr [esp + 0xd4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 471b90: fdiv dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0xecu)) = (float)ST(0); FPOP();	/* 471b94: fstp dword ptr [esp + 0xec] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xd8u)));	/* 471b9b: fld dword ptr [esp + 0xd8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 471ba2: fdiv dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0xf0u)) = (float)ST(0); FPOP();	/* 471ba6: fstp dword ptr [esp + 0xf0] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 471bad: fdiv dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 471bb1: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xecu));	/* 471bb5: fsub dword ptr [esp + 0xec] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 471bbc: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 471bc0: fld dword ptr [esp + 0x20] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xf0u));	/* 471bc4: fsub dword ptr [esp + 0xf0] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 471bcb: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471bcf: push ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 471bd0: mov dword ptr [esp + 0x20], ecx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 471bd4: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 471bd8: fld dword ptr [esp + 0x28] */
	ST(0) = ST(0) - ST(1);	/* 471bdc: fsub st(1) */
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 471bde: mov edx, dword ptr [esp + 0x44] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 471be2: mov dword ptr [esp + 0x24], edx */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 471be6: fstp dword ptr [esp + 0x48] */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 471bea: mov eax, dword ptr [esp + 0x48] */
	ST(0) = ST(0); FPOP();	/* 471bee: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 471bf0: fld dword ptr [esp + 0x48] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 471bf4: fsub dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 471bf8: mov dword ptr [esp + 0x28], eax */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471bfc: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 471bff: fld dword ptr [esp + 0x44] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471c03: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471c07: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471c08: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 471c0b: fld dword ptr [esp + 0x44] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471c0f: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471c13: push ecx */
	m->ecx = (DWORD)(m->esp + 0x218u);	/* 471c14: lea ecx, [esp + 0x218] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471c1b: fstp dword ptr [esp] */
	goto L_471d34;	/* 471c1e: jmp 0x471d34 */
L_471c23:
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471c23: test cl, 0x10 */
	if (m->zf) goto L_471d4d;	/* 471c26: je 0x471d4d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x40u)));	/* 471c2c: fld dword ptr [ebp + 0x40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471c2f: fsub dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 471c33: fld dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471c37: push ecx */
	ST(0) = ST(0) * ST(1);	/* 471c38: fmul st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471c3a: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471c3d: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 471c3e: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471c40: fmul dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471c44: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471c47: push ecx */
	m->ecx = (DWORD)(m->esp + 0x170u);	/* 471c48: lea ecx, [esp + 0x170] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471c4f: fmul dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471c53: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x471c5bu; native_call(m, 0x4722c0u);	/* 471c56: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471c5b: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471c5d: push ecx */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 471c5e: mov dword ptr [esp + 0x6c], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471c62: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 471c65: mov dword ptr [esp + 0x70], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471c69: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x74u)) = m->eax;	/* 471c6c: mov dword ptr [esp + 0x74], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 471c70: fld dword ptr [esp + 0x74] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 471c74: fdiv dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471c78: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 471c7b: fld dword ptr [esp + 0x70] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 471c7f: fdiv dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471c83: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471c84: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 471c87: fld dword ptr [esp + 0x70] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471c8b: fdiv dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471c8f: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1d0u);	/* 471c90: lea ecx, [esp + 0x1d0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471c97: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x471c9fu; native_call(m, 0x4722c0u);	/* 471c9a: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471c9f: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471ca1: fld dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471ca5: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471ca8: push ecx */
	M32((DWORD)(m->esp + 0xc4u)) = m->edx;	/* 471ca9: mov dword ptr [esp + 0xc4], edx */
	M32((DWORD)(m->esp + 0xc0u)) = m->ecx;	/* 471cb0: mov dword ptr [esp + 0xc0], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471cb7: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0xc8u)) = m->eax;	/* 471cba: mov dword ptr [esp + 0xc8], eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xc8u));	/* 471cc1: fsub dword ptr [esp + 0xc8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471cc8: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471ccb: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xc4u));	/* 471ccf: fsub dword ptr [esp + 0xc4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471cd6: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471cd7: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471cda: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xc4u));	/* 471cde: fsub dword ptr [esp + 0xc4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471ce5: push ecx */
	m->ecx = (DWORD)(m->esp + 0x188u);	/* 471ce6: lea ecx, [esp + 0x188] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471ced: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x471cf5u; native_call(m, 0x4722c0u);	/* 471cf0: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471cf5: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471cf7: push ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 471cf8: mov dword ptr [esp + 0x20], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471cfc: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 471cff: mov dword ptr [esp + 0x24], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471d03: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 471d06: mov dword ptr [esp + 0x28], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 471d0a: fld dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 471d0e: fsub dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471d12: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471d15: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471d19: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471d1d: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471d1e: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471d21: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471d25: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471d29: push ecx */
	m->ecx = (DWORD)(m->esp + 0x14cu);	/* 471d2a: lea ecx, [esp + 0x14c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471d31: fstp dword ptr [esp] */
L_471d34:
	m->esp -= 4; M32(m->esp) = 0x471d39u; native_call(m, 0x4722c0u);	/* 471d34: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471d39: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 471d3b: mov dword ptr [esp + 0x10], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471d3f: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 471d42: mov dword ptr [esp + 0x14], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471d46: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 471d49: mov dword ptr [esp + 0x18], eax */
L_471d4d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 471d4d: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x38u)); FPOP();	/* 471d51: fcomp dword ptr [ebp + 0x38] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471d54: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471d56: test ah, 0x41 */
	if (m->zf) goto L_471d62;	/* 471d59: je 0x471d62 */
	m->ecx = 0x100u;	/* 471d5b: mov ecx, 0x100 */
	goto L_471d79;	/* 471d60: jmp 0x471d79 */
L_471d62:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 471d62: fld dword ptr [esp + 0x2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x44u)); FPOP();	/* 471d66: fcomp dword ptr [ebp + 0x44] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471d69: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471d6b: test ah, 1 */
	if (!m->zf) goto L_471d77;	/* 471d6e: jne 0x471d77 */
	m->ecx = 0x1000u;	/* 471d70: mov ecx, 0x1000 */
	goto L_471d79;	/* 471d75: jmp 0x471d79 */
L_471d77:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 471d77: xor ecx, ecx */
L_471d79:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 471d79: fld dword ptr [esp + 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x38u)); FPOP();	/* 471d7d: fcomp dword ptr [ebp + 0x38] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471d80: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471d82: test ah, 0x41 */
	if (m->zf) goto L_471d8e;	/* 471d85: je 0x471d8e */
	m->edi = 0x100u;	/* 471d87: mov edi, 0x100 */
	goto L_471da5;	/* 471d8c: jmp 0x471da5 */
L_471d8e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 471d8e: fld dword ptr [esp + 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x44u)); FPOP();	/* 471d92: fcomp dword ptr [ebp + 0x44] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471d95: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471d97: test ah, 1 */
	if (!m->zf) goto L_471da3;	/* 471d9a: jne 0x471da3 */
	m->edi = 0x1000u;	/* 471d9c: mov edi, 0x1000 */
	goto L_471da5;	/* 471da1: jmp 0x471da5 */
L_471da3:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 471da3: xor edi, edi */
L_471da5:
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 471da5: test ecx, edi */
	if (!m->zf) goto L_47225e;	/* 471da7: jne 0x47225e */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471dad: test ch, 1 */
	if (m->zf) goto L_471e79;	/* 471db0: je 0x471e79 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x38u)));	/* 471db6: fld dword ptr [ebp + 0x38] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 471db9: fsub dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471dbd: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 471dbe: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 471dc0: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x108u)) = (float)ST(0); FPOP();	/* 471dc4: fstp dword ptr [esp + 0x108] */
	{ long double t = ST(0); FPUSH(t); }	/* 471dcb: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471dcd: fmul dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x10cu)) = (float)ST(0); FPOP();	/* 471dd1: fstp dword ptr [esp + 0x10c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471dd8: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x108u)));	/* 471ddc: fld dword ptr [esp + 0x108] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471de3: fdiv dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x120u)) = (float)ST(0); FPOP();	/* 471de7: fstp dword ptr [esp + 0x120] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10cu)));	/* 471dee: fld dword ptr [esp + 0x10c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471df5: fdiv dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x124u)) = (float)ST(0); FPOP();	/* 471df9: fstp dword ptr [esp + 0x124] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471e00: fdiv dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 471e04: fadd dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471e08: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x124u)));	/* 471e0b: fld dword ptr [esp + 0x124] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471e12: fadd dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471e16: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471e17: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x124u)));	/* 471e1a: fld dword ptr [esp + 0x124] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471e21: fadd dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471e25: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1a0u);	/* 471e26: lea ecx, [esp + 0x1a0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471e2d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x471e35u; native_call(m, 0x4722c0u);	/* 471e30: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471e35: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471e37: fld dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471e3b: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471e3e: push ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 471e3f: mov dword ptr [esp + 0x30], edx */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 471e43: mov dword ptr [esp + 0x2c], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471e47: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 471e4a: mov dword ptr [esp + 0x34], eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 471e4e: fsub dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471e52: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471e55: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471e59: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471e5d: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471e5e: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471e61: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471e65: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471e69: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1e8u);	/* 471e6a: lea ecx, [esp + 0x1e8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471e71: fstp dword ptr [esp] */
	goto L_471f62;	/* 471e74: jmp 0x471f62 */
L_471e79:
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471e79: test ch, 0x10 */
	if (m->zf) goto L_471f7b;	/* 471e7c: je 0x471f7b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 471e82: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 471e85: fsub dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471e89: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 471e8a: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 471e8c: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x138u)) = (float)ST(0); FPOP();	/* 471e90: fstp dword ptr [esp + 0x138] */
	{ long double t = ST(0); FPUSH(t); }	/* 471e97: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471e99: fmul dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x13cu)) = (float)ST(0); FPOP();	/* 471e9d: fstp dword ptr [esp + 0x13c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471ea4: fmul dword ptr [esp + 0x1c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471ea8: fdiv dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471eac: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x13cu)));	/* 471eaf: fld dword ptr [esp + 0x13c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471eb6: fdiv dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471eba: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471ebb: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x13cu)));	/* 471ebe: fld dword ptr [esp + 0x13c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471ec5: fdiv dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471ec9: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1b8u);	/* 471eca: lea ecx, [esp + 0x1b8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471ed1: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x471ed9u; native_call(m, 0x4722c0u);	/* 471ed4: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471ed9: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471edb: push ecx */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 471edc: mov dword ptr [esp + 0x78], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471ee0: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x7cu)) = m->edx;	/* 471ee3: mov dword ptr [esp + 0x7c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471ee7: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 471eea: mov dword ptr [esp + 0x80], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 471ef1: fld dword ptr [esp + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 471ef8: fadd dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471efc: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 471eff: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471f03: fadd dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471f07: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471f08: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 471f0b: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471f0f: fadd dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471f13: push ecx */
	m->ecx = (DWORD)(m->esp + 0x158u);	/* 471f14: lea ecx, [esp + 0x158] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471f1b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x471f23u; native_call(m, 0x4722c0u);	/* 471f1e: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471f23: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471f25: fld dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471f29: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471f2c: push ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 471f2d: mov dword ptr [esp + 0x30], edx */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 471f31: mov dword ptr [esp + 0x2c], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471f35: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 471f38: mov dword ptr [esp + 0x34], eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 471f3c: fsub dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471f40: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471f43: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471f47: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471f4b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471f4c: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 471f4f: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 471f53: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471f57: push ecx */
	m->ecx = (DWORD)(m->esp + 0x164u);	/* 471f58: lea ecx, [esp + 0x164] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471f5f: fstp dword ptr [esp] */
L_471f62:
	m->esp -= 4; M32(m->esp) = 0x471f67u; native_call(m, 0x4722c0u);	/* 471f62: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471f67: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 471f69: mov dword ptr [esp + 0x10], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471f6d: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 471f70: mov dword ptr [esp + 0x14], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471f74: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 471f77: mov dword ptr [esp + 0x18], eax */
L_471f7b:
	{ DWORD a_ = m->edi, b_ = 0x100u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 471f7b: test edi, 0x100 */
	if (m->zf) goto L_4720a6;	/* 471f81: je 0x4720a6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x38u)));	/* 471f87: fld dword ptr [ebp + 0x38] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 471f8a: fsub dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 471f8e: fld dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471f92: push ecx */
	ST(0) = ST(0) * ST(1);	/* 471f93: fmul st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471f95: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471f98: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 471f99: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471f9b: fmul dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471f9f: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471fa2: push ecx */
	m->ecx = (DWORD)(m->esp + 0x17cu);	/* 471fa3: lea ecx, [esp + 0x17c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471faa: fmul dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471fae: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x471fb6u; native_call(m, 0x4722c0u);	/* 471fb1: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 471fb6: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471fb8: push ecx */
	M32((DWORD)(m->esp + 0x84u)) = m->ecx;	/* 471fb9: mov dword ptr [esp + 0x84], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 471fc0: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x88u)) = m->edx;	/* 471fc3: mov dword ptr [esp + 0x88], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 471fca: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 471fcd: mov dword ptr [esp + 0x8c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8cu)));	/* 471fd4: fld dword ptr [esp + 0x8c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471fdb: fdiv dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471fdf: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 471fe2: fld dword ptr [esp + 0x88] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 471fe9: fdiv dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471fed: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 471fee: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 471ff1: fld dword ptr [esp + 0x88] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 471ff8: fdiv dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 471ffc: push ecx */
	m->ecx = (DWORD)(m->esp + 0x194u);	/* 471ffd: lea ecx, [esp + 0x194] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 472004: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47200cu; native_call(m, 0x4722c0u);	/* 472007: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47200c: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47200e: fld dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 472012: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472015: push ecx */
	M32((DWORD)(m->esp + 0xa0u)) = m->edx;	/* 472016: mov dword ptr [esp + 0xa0], edx */
	M32((DWORD)(m->esp + 0x9cu)) = m->ecx;	/* 47201d: mov dword ptr [esp + 0x9c], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 472024: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0xa4u)) = m->eax;	/* 472027: mov dword ptr [esp + 0xa4], eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xa4u));	/* 47202e: fsub dword ptr [esp + 0xa4] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 472035: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472038: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xa0u));	/* 47203c: fsub dword ptr [esp + 0xa0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472043: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 472044: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472047: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xa0u));	/* 47204b: fsub dword ptr [esp + 0xa0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472052: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1acu);	/* 472053: lea ecx, [esp + 0x1ac] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47205a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x472062u; native_call(m, 0x4722c0u);	/* 47205d: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 472062: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472064: push ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 472065: mov dword ptr [esp + 0x20], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 472069: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 47206c: mov dword ptr [esp + 0x24], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 472070: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 472073: mov dword ptr [esp + 0x28], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 472077: fld dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47207b: fsub dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47207f: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472082: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 472086: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47208a: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47208b: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47208e: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 472092: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472096: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1c4u);	/* 472097: lea ecx, [esp + 0x1c4] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47209e: fstp dword ptr [esp] */
	goto L_4721cc;	/* 4720a1: jmp 0x4721cc */
L_4720a6:
	{ DWORD a_ = m->edi, b_ = 0x1000u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4720a6: test edi, 0x1000 */
	if (m->zf) goto L_4721d1;	/* 4720ac: je 0x4721d1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 4720b2: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 4720b5: fsub dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4720b9: fld dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4720bd: push ecx */
	ST(0) = ST(0) * ST(1);	/* 4720be: fmul st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4720c0: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4720c3: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 4720c4: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 4720c6: fmul dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4720ca: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4720cd: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1dcu);	/* 4720ce: lea ecx, [esp + 0x1dc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 4720d5: fmul dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4720d9: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4720e1u; native_call(m, 0x4722c0u);	/* 4720dc: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4720e1: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4720e3: push ecx */
	M32((DWORD)(m->esp + 0xb4u)) = m->ecx;	/* 4720e4: mov dword ptr [esp + 0xb4], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 4720eb: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0xb8u)) = m->edx;	/* 4720ee: mov dword ptr [esp + 0xb8], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 4720f5: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0xbcu)) = m->eax;	/* 4720f8: mov dword ptr [esp + 0xbc], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xbcu)));	/* 4720ff: fld dword ptr [esp + 0xbc] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 472106: fdiv dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47210a: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb8u)));	/* 47210d: fld dword ptr [esp + 0xb8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 472114: fdiv dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472118: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 472119: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb8u)));	/* 47211c: fld dword ptr [esp + 0xb8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 472123: fdiv dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472127: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1f4u);	/* 472128: lea ecx, [esp + 0x1f4] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47212f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x472137u; native_call(m, 0x4722c0u);	/* 472132: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 472137: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472139: fld dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47213d: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472140: push ecx */
	M32((DWORD)(m->esp + 0xd0u)) = m->edx;	/* 472141: mov dword ptr [esp + 0xd0], edx */
	M32((DWORD)(m->esp + 0xccu)) = m->ecx;	/* 472148: mov dword ptr [esp + 0xcc], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47214f: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0xd4u)) = m->eax;	/* 472152: mov dword ptr [esp + 0xd4], eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xd4u));	/* 472159: fsub dword ptr [esp + 0xd4] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 472160: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472163: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xd0u));	/* 472167: fsub dword ptr [esp + 0xd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47216e: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47216f: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472172: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xd0u));	/* 472176: fsub dword ptr [esp + 0xd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47217d: push ecx */
	m->ecx = (DWORD)(m->esp + 0x20cu);	/* 47217e: lea ecx, [esp + 0x20c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 472185: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47218du; native_call(m, 0x4722c0u);	/* 472188: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47218d: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47218f: push ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 472190: mov dword ptr [esp + 0x20], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 472194: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 472197: mov dword ptr [esp + 0x24], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47219b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 47219e: mov dword ptr [esp + 0x28], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4721a2: fld dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 4721a6: fsub dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4721aa: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4721ad: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 4721b1: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4721b5: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4721b6: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4721b9: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 4721bd: fsub dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4721c1: push ecx */
	m->ecx = (DWORD)(m->esp + 0x224u);	/* 4721c2: lea ecx, [esp + 0x224] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4721c9: fstp dword ptr [esp] */
L_4721cc:
	m->esp -= 4; M32(m->esp) = 0x4721d1u; native_call(m, 0x4722c0u);	/* 4721cc: call 0x4722c0 */
L_4721d1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4721d1: fld dword ptr [esp + 0x30] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x3cu)); FPOP();	/* 4721d5: fcomp dword ptr [ebp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4721d8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4721da: test ah, 0x41 */
	if (m->zf) goto L_4721e6;	/* 4721dd: je 0x4721e6 */
	m->ecx = 0x10000u;	/* 4721df: mov ecx, 0x10000 */
	goto L_4721fd;	/* 4721e4: jmp 0x4721fd */
L_4721e6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4721e6: fld dword ptr [esp + 0x30] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x48u)); FPOP();	/* 4721ea: fcomp dword ptr [ebp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4721ed: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4721ef: test ah, 1 */
	if (!m->zf) goto L_4721fb;	/* 4721f2: jne 0x4721fb */
	m->ecx = 0x100000u;	/* 4721f4: mov ecx, 0x100000 */
	goto L_4721fd;	/* 4721f9: jmp 0x4721fd */
L_4721fb:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4721fb: xor ecx, ecx */
L_4721fd:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4721fd: fld dword ptr [esp + 0x24] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x3cu)); FPOP();	/* 472201: fcomp dword ptr [ebp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472204: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472206: test ah, 0x41 */
	if (m->zf) goto L_472212;	/* 472209: je 0x472212 */
	m->eax = 0x10000u;	/* 47220b: mov eax, 0x10000 */
	goto L_472229;	/* 472210: jmp 0x472229 */
L_472212:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472212: fld dword ptr [esp + 0x24] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x48u)); FPOP();	/* 472216: fcomp dword ptr [ebp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472219: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47221b: test ah, 1 */
	if (!m->zf) goto L_472227;	/* 47221e: jne 0x472227 */
	m->eax = 0x100000u;	/* 472220: mov eax, 0x100000 */
	goto L_472229;	/* 472225: jmp 0x472229 */
L_472227:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472227: xor eax, eax */
L_472229:
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472229: test ecx, eax */
	if (!m->zf) goto L_47225e;	/* 47222b: jne 0x47225e */
	m->ecx = M32((DWORD)(m->esi + 0x148u));	/* 47222d: mov ecx, dword ptr [esi + 0x148] */
	m->eax = M32((DWORD)(m->esp + 0x60u));	/* 472233: mov eax, dword ptr [esp + 0x60] */
	m->edx = M32((DWORD)(m->ecx + 0x8u));	/* 472237: mov edx, dword ptr [ecx + 8] */
	m->ecx = (DWORD)(m->esi + 0xb0u);	/* 47223a: lea ecx, [esi + 0xb0] */
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->edx;	/* 472240: mov dword ptr [eax - 4], edx */
	m->edx = (DWORD)(m->esi + 0xf0u);	/* 472243: lea edx, [esi + 0xf0] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 472249: mov dword ptr [eax], ecx */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47224b: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 47224e: mov edx, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 472252: inc edx */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 472253: add eax, 0xc */
	M32((DWORD)(m->esp + 0x38u)) = m->edx;	/* 472256: mov dword ptr [esp + 0x38], edx */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47225a: mov dword ptr [esp + 0x60], eax */
L_47225e:
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 47225e: mov ecx, dword ptr [esp + 0x34] */
L_472262:
	m->eax = M32((DWORD)(m->esp + 0x64u));	/* 472262: mov eax, dword ptr [esp + 0x64] */
	m->edx = M32((DWORD)(m->ecx + 0x13c9b24u));	/* 472266: mov edx, dword ptr [ecx + 0x13c9b24] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 47226c: inc eax */
	{ DWORD a_ = m->esi, b_ = 0x2ccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 47226d: add esi, 0x2cc */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472273: cmp eax, edx */
	M32((DWORD)(m->esp + 0x64u)) = m->eax;	/* 472275: mov dword ptr [esp + 0x64], eax */
	if (m->sf != m->of) goto L_47177d;	/* 472279: jl 0x47177d */
	m->edi = M32(m->esp); m->esp += 4;	/* 47227f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 472280: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 472281: pop ebp */
L_472282:
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 472282: mov eax, dword ptr [esp + 0x2c] */
	m->edx = (DWORD)(m->ecx + 0x9ca0f4u);	/* 472286: lea edx, [ecx + 0x9ca0f4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47228c: push eax */
	m->eax = M32((DWORD)(m->esp + 0x228u));	/* 47228d: mov eax, dword ptr [esp + 0x228] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 472294: push edx */
	m->edx = M32((DWORD)(m->esp + 0x224u));	/* 472295: mov edx, dword ptr [esp + 0x224] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47229c: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47229d: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47229e: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xa10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47229f: add ecx, 0xa10 */
	m->esp -= 4; M32(m->esp) = 0x4722aau; lift_483060(m);	/* 4722a5: call 0x483060 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4722aa: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x214u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4722ab: add esp, 0x214 */
	m->esp += 4 + 12; return;	/* 4722b1: ret 0xc */
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
