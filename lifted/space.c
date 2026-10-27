/* ---- emulated machine for lifted functions (tools/lift.py) ---- */
#if 0 /* X86 comes from the earlier lifted file */
typedef struct { DWORD eax, ecx, edx, ebx, esp, ebp, esi, edi; int zf, sf, cf, of; long double fs[8]; int ft; DWORD fsw; } X86;
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

static void lift_46cbc0(X86 *m);
static void lift_482aa0(X86 *m);

/* space_walkNodes_482aa0 (0x482aa0), lifted by tools/lift.py */
static void lift_482aa0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 482aa0: sub esp, 0x20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 482aa3: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 482aa4: push esi */
	m->esi = m->ecx;	/* 482aa5: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x74u));	/* 482aa7: mov eax, dword ptr [esi + 0x74] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482aaa: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_482ddc;	/* 482aac: jle 0x482ddc */
	m->eax = M32((DWORD)(m->esi + 0x78u));	/* 482ab2: mov eax, dword ptr [esi + 0x78] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482ab5: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_482ddc;	/* 482ab7: jle 0x482ddc */
	m->eax = M32((DWORD)(m->esi + 0x7cu));	/* 482abd: mov eax, dword ptr [esi + 0x7c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482ac0: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_482ddc;	/* 482ac2: jle 0x482ddc */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 482ac8: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 482acc: mov ecx, dword ptr [esp + 0x34] */
	m->ebx = M32((DWORD)(m->esp + 0x3cu));	/* 482ad0: mov ebx, dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 482ad4: fld dword ptr [eax] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 482ad6: fadd dword ptr [ecx] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 482ad8: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 482adc: fld dword ptr [eax + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 482adf: fadd dword ptr [ecx + 4] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 482ae2: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 482ae6: fld dword ptr [eax + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 482ae9: fadd dword ptr [ecx + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 482aec: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 482af0: mov edx, dword ptr [esp + 0x20] */
	m->eax = m->ebx;	/* 482af4: mov eax, ebx */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 482af6: fstp dword ptr [esp + 0x24] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 482afa: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 482afc: mov ecx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 482b00: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 482b03: mov dword ptr [eax + 8], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x5cu)));	/* 482b06: fld dword ptr [esi + 0x5c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482b09: fsub dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x0u)); FPOP();	/* 482b0f: fcomp dword ptr [ebx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482b11: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482b13: test ah, 1 */
	if (m->zf) goto L_482ddc;	/* 482b16: je 0x482ddc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x60u)));	/* 482b1c: fld dword ptr [esi + 0x60] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482b1f: fsub dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x4u)); FPOP();	/* 482b25: fcomp dword ptr [ebx + 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482b28: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482b2a: test ah, 1 */
	if (m->zf) goto L_482ddc;	/* 482b2d: je 0x482ddc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x64u)));	/* 482b33: fld dword ptr [esi + 0x64] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482b36: fsub dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x8u)); FPOP();	/* 482b3c: fcomp dword ptr [ebx + 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482b3f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482b41: test ah, 1 */
	if (m->zf) goto L_482ddc;	/* 482b44: je 0x482ddc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 482b4a: fld dword ptr [esi + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482b4d: fadd dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x0u)); FPOP();	/* 482b53: fcomp dword ptr [ebx] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482b55: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482b57: test ah, 0x41 */
	if (!m->zf) goto L_482ddc;	/* 482b5a: jne 0x482ddc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 482b60: fld dword ptr [esi + 0x6c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482b63: fadd dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x4u)); FPOP();	/* 482b69: fcomp dword ptr [ebx + 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482b6c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482b6e: test ah, 0x41 */
	if (!m->zf) goto L_482ddc;	/* 482b71: jne 0x482ddc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 482b77: fld dword ptr [esi + 0x70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482b7a: fadd dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x8u)); FPOP();	/* 482b80: fcomp dword ptr [ebx + 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482b83: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482b85: test ah, 0x41 */
	if (!m->zf) goto L_482ddc;	/* 482b88: jne 0x482ddc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 482b8e: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 482b91: fsub dword ptr [esi + 0x64] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 482b94: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 482b95: push edi */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 482b96: fdiv dword ptr [esi + 0x80] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 482b9c: call 0x49ec14 */
	m->edi = M32((DWORD)(m->esi + 0x74u));	/* 482ba1: mov edi, dword ptr [esi + 0x74] */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 482ba4: mov dword ptr [esp + 0x44], eax */
	m->ecx = (DWORD)(m->edi + 0xffffffffu);	/* 482ba8: lea ecx, [edi - 1] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482bab: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_482bb3;	/* 482bad: jle 0x482bb3 */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 482baf: mov dword ptr [esp + 0x44], ecx */
L_482bb3:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 482bb3: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 482bb5: fsub dword ptr [esi + 0x5c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 482bb8: fdiv dword ptr [esi + 0x84] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 482bbe: call 0x49ec14 */
	m->ebp = m->eax;	/* 482bc3: mov ebp, eax */
	m->eax = M32((DWORD)(m->esi + 0x78u));	/* 482bc5: mov eax, dword ptr [esi + 0x78] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 482bc8: dec eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ebp;	/* 482bc9: mov dword ptr [esp + 0x10], ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482bcd: cmp ebp, eax */
	if (m->zf || m->sf != m->of) goto L_482bd7;	/* 482bcf: jle 0x482bd7 */
	m->ebp = m->eax;	/* 482bd1: mov ebp, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ebp;	/* 482bd3: mov dword ptr [esp + 0x10], ebp */
L_482bd7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 482bd7: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 482bda: fsub dword ptr [esi + 0x60] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 482bdd: fdiv dword ptr [esi + 0x88] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 482be3: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esi + 0x7cu));	/* 482be8: mov ecx, dword ptr [esi + 0x7c] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 482beb: mov dword ptr [esp + 0x14], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 482bef: dec ecx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482bf0: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_482bfa;	/* 482bf2: jle 0x482bfa */
	m->eax = m->ecx;	/* 482bf4: mov eax, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 482bf6: mov dword ptr [esp + 0x14], eax */
L_482bfa:
	{ long long p_ = (long long)(int)m->edi * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 482bfa: imul edi, eax */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 482bfd: mov eax, dword ptr [esp + 0x44] */
	m->edx = M32((DWORD)(m->esi + 0x54u));	/* 482c01: mov edx, dword ptr [esi + 0x54] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 482c04: add edi, eax */
	{ long long p_ = (long long)(int)m->edi * (int)M32((DWORD)(m->esi + 0x78u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 482c06: imul edi, dword ptr [esi + 0x78] */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 482c0a: add edi, ebp */
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->edx + m->edi*2 + 0x0u))) & 0xffff);	/* 482c0c: mov ax, word ptr [edx + edi*2] */
	m->edi = M32(m->esp); m->esp += 4;	/* 482c10: pop edi */
	{ DWORD a_ = (m->eax & 0xffff), b_ = 0xffffu & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 482c11: cmp ax, 0xffff */
	m->ebp = M32(m->esp); m->esp += 4;	/* 482c15: pop ebp */
	if (m->zf) goto L_482ddc;	/* 482c16: je 0x482ddc */
	m->ecx = M32((DWORD)(m->esi + 0x44u));	/* 482c1c: mov ecx, dword ptr [esi + 0x44] */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 482c1f: push 0x50 */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 482c21: and eax, 0xffff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482c26: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482c27: push eax */
	m->esp -= 4; M32(m->esp) = 0x482c2du; lift_46cbc0(m);	/* 482c28: call 0x46cbc0 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 482c2d: fild dword ptr [esp + 0x14] */
	m->ecx = m->eax;	/* 482c31: mov ecx, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 482c33: add esp, 0xc */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482c36: test ecx, ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 482c38: fmul dword ptr [esi + 0x84] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 482c3e: fild dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 482c42: fmul dword ptr [esi + 0x88] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 482c48: fstp dword ptr [esp + 0x14] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x3cu)));	/* 482c4c: fild dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 482c50: fmul dword ptr [esi + 0x80] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 482c56: fstp dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 482c5a: fadd dword ptr [esi + 0x5c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 482c5d: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 482c61: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 482c65: fadd dword ptr [esi + 0x60] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 482c68: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 482c6c: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 482c70: fadd dword ptr [esi + 0x64] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 482c73: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 482c77: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 482c7b: fadd dword ptr [esi + 0x84] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 482c81: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 482c85: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 482c89: fadd dword ptr [esi + 0x88] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 482c8f: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 482c93: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 482c97: fadd dword ptr [esi + 0x80] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 482c9d: fstp dword ptr [esp + 0x24] */
	if (m->zf) goto L_482ddc;	/* 482ca1: je 0x482ddc */
L_482ca7:
	m->eax = M32((DWORD)(m->ecx + 0x24u));	/* 482ca7: mov eax, dword ptr [ecx + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482caa: test eax, eax */
	if (m->zf) goto L_482de6;	/* 482cac: je 0x482de6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 482cb2: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 482cb6: fadd dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 482cba: fmul dword ptr [0x4a942c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x0u));	/* 482cc0: fcom dword ptr [ebx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 482cc2: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 482cc6: fadd dword ptr [esp + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482cca: fnstsw ax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 482ccc: fmul dword ptr [0x4a942c] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482cd2: test ah, 0x41 */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 482cd5: fstp dword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 482cd9: fld dword ptr [ebx + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x8u)); FPOP();	/* 482cdc: fcomp dword ptr [esp + 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482ce0: fnstsw ax */
	if (!m->zf) goto L_482d50;	/* 482ce2: jne 0x482d50 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 482ce4: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 482ce8: fadd dword ptr [esp + 0x18] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482cec: test ah, 1 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 482cef: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482cf5: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 482cf9: fld dword ptr [ebx + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x3cu)); FPOP();	/* 482cfc: fcomp dword ptr [esp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482d00: fnstsw ax */
	if (m->zf) goto L_482d26;	/* 482d02: je 0x482d26 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482d04: test ah, 1 */
	if (m->zf) goto L_482d12;	/* 482d07: je 0x482d12 */
	m->ecx = M32((DWORD)(m->ecx + 0x28u));	/* 482d09: mov ecx, dword ptr [ecx + 0x28] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 482d0c: fstp dword ptr [esp + 0x1c] */
	goto L_482d7c;	/* 482d10: jmp 0x482d7c */
L_482d12:
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 482d12: mov edx, dword ptr [esp + 8] */
	m->ecx = M32((DWORD)(m->ecx + 0x30u));	/* 482d16: mov ecx, dword ptr [ecx + 0x30] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 482d19: fstp dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 482d1d: mov dword ptr [esp + 0x20], edx */
	goto L_482dcc;	/* 482d21: jmp 0x482dcc */
L_482d26:
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482d26: test ah, 1 */
	if (m->zf) goto L_482d47;	/* 482d29: je 0x482d47 */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 482d2b: mov edx, dword ptr [esp + 8] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 482d2f: mov eax, dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->ecx + 0x38u));	/* 482d33: mov ecx, dword ptr [ecx + 0x38] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 482d36: mov dword ptr [esp + 0x14], edx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 482d3a: fstp dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 482d3e: mov dword ptr [esp + 0x24], eax */
	goto L_482dd4;	/* 482d42: jmp 0x482dd4 */
L_482d47:
	m->ecx = M32((DWORD)(m->ecx + 0x40u));	/* 482d47: mov ecx, dword ptr [ecx + 0x40] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 482d4a: fstp dword ptr [esp + 0x1c] */
	goto L_482dc4;	/* 482d4e: jmp 0x482dc4 */
L_482d50:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 482d50: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 482d54: fadd dword ptr [esp + 0x18] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482d58: test ah, 1 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 482d5b: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482d61: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 482d65: fld dword ptr [ebx + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x3cu)); FPOP();	/* 482d68: fcomp dword ptr [esp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482d6c: fnstsw ax */
	if (m->zf) goto L_482d9f;	/* 482d6e: je 0x482d9f */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482d70: test ah, 1 */
	if (m->zf) goto L_482d8e;	/* 482d73: je 0x482d8e */
	m->ecx = M32((DWORD)(m->ecx + 0x2cu));	/* 482d75: mov ecx, dword ptr [ecx + 0x2c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 482d78: fstp dword ptr [esp + 0x10] */
L_482d7c:
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 482d7c: mov edx, dword ptr [esp + 8] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 482d80: mov eax, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 482d84: mov dword ptr [esp + 0x20], edx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 482d88: mov dword ptr [esp + 0x24], eax */
	goto L_482dd4;	/* 482d8c: jmp 0x482dd4 */
L_482d8e:
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 482d8e: mov edx, dword ptr [esp + 8] */
	m->ecx = M32((DWORD)(m->ecx + 0x34u));	/* 482d92: mov ecx, dword ptr [ecx + 0x34] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 482d95: fstp dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 482d99: mov dword ptr [esp + 0x20], edx */
	goto L_482dcc;	/* 482d9d: jmp 0x482dcc */
L_482d9f:
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482d9f: test ah, 1 */
	if (m->zf) goto L_482dbd;	/* 482da2: je 0x482dbd */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 482da4: mov edx, dword ptr [esp + 8] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 482da8: mov eax, dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->ecx + 0x3cu));	/* 482dac: mov ecx, dword ptr [ecx + 0x3c] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 482daf: mov dword ptr [esp + 0x14], edx */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 482db3: fstp dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 482db7: mov dword ptr [esp + 0x24], eax */
	goto L_482dd4;	/* 482dbb: jmp 0x482dd4 */
L_482dbd:
	m->ecx = M32((DWORD)(m->ecx + 0x44u));	/* 482dbd: mov ecx, dword ptr [ecx + 0x44] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 482dc0: fstp dword ptr [esp + 0x10] */
L_482dc4:
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 482dc4: mov edx, dword ptr [esp + 8] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 482dc8: mov dword ptr [esp + 0x14], edx */
L_482dcc:
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 482dcc: mov eax, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 482dd0: mov dword ptr [esp + 0x18], eax */
L_482dd4:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482dd4: test ecx, ecx */
	if (!m->zf) goto L_482ca7;	/* 482dd6: jne 0x482ca7 */
L_482ddc:
	m->esi = M32(m->esp); m->esp += 4;	/* 482ddc: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 482ddd: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 482ddf: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 482de0: add esp, 0x20 */
	m->esp += 4 + 44; return;	/* 482de3: ret 0x2c */
L_482de6:
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 482de6: mov edx, dword ptr [esp + 0x54] */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 482dea: mov eax, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482dee: push edx */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 482def: mov edx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482df3: push eax */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 482df4: mov eax, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482df8: push edx */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 482df9: mov edx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482dfd: push eax */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 482dfe: mov eax, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482e02: push edx */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 482e03: mov edx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482e07: push eax */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 482e08: mov eax, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 482e0c: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482e0d: push edx */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 482e0e: mov edx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482e12: push eax */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 482e13: mov eax, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482e17: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482e18: push eax */
	m->esp -= 4; M32(m->esp) = 0x482e1eu; lift_4804b0(m);	/* 482e19: call 0x4804b0 */
	M32((DWORD)(m->esi + 0x98u)) = m->eax;	/* 482e1e: mov dword ptr [esi + 0x98], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 482e24: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 482e25: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 482e26: add esp, 0x20 */
	m->esp += 4 + 44; return;	/* 482e29: ret 0x2c */
}

/* FUN_0046cbc0 (0x46cbc0), lifted by tools/lift.py */
static void lift_46cbc0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 46cbc0: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46cbc4: cmp eax, -1 */
	if (!m->zf) goto L_46cbcc;	/* 46cbc7: jne 0x46cbcc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46cbc9: xor eax, eax */
	m->esp += 4 + 0; return;	/* 46cbcb: ret  */
L_46cbcc:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46cbcc: test eax, eax */
	if (m->sf == m->of) goto L_46cbd3;	/* 46cbce: jge 0x46cbd3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46cbd0: xor eax, eax */
	m->esp += 4 + 0; return;	/* 46cbd2: ret  */
L_46cbd3:
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0xcu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46cbd3: imul eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esp + 0x8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46cbd8: add eax, dword ptr [esp + 8] */
	m->esp += 4 + 0; return;	/* 46cbdc: ret  */
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
