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

static void lift_481ae0(X86 *m);
static void lift_46ab30(X86 *m);
static void lift_4728e0(X86 *m);

/* load_4728e0 (0x4728e0), lifted by tools/lift.py */
static void lift_4728e0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4728e0: mov eax, dword ptr [esp + 4] */
	m->edx = M32((DWORD)(m->eax + 0x20u));	/* 4728e4: mov edx, dword ptr [eax + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4728e7: push edx */
	m->edx = M32((DWORD)(m->eax + 0x1cu));	/* 4728e8: mov edx, dword ptr [eax + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4728eb: push edx */
	m->edx = M32((DWORD)(m->eax + 0x48u));	/* 4728ec: mov edx, dword ptr [eax + 0x48] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4728ef: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4728f1: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4728f3: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4728f5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4728f6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4728fcu; native_call(m, 0x472400u);	/* 4728f7: call 0x472400 */
	m->esp += 4 + 4; return;	/* 4728fc: ret 4 */
}

/* load_481ae0 (0x481ae0), lifted by tools/lift.py */
static void lift_481ae0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481ae0: sub esp, 0x40 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 481ae3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 481ae4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 481ae5: push esi */
	m->esi = M32((DWORD)(m->esp + 0x50u));	/* 481ae6: mov esi, dword ptr [esp + 0x50] */
	m->ebp = m->ecx;	/* 481aea: mov ebp, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 481aec: push edi */
	m->edi = M32((DWORD)(m->esp + 0x58u));	/* 481aed: mov edi, dword ptr [esp + 0x58] */
	m->ebx = (DWORD)(m->esi + 0xcu);	/* 481af1: lea ebx, [esi + 0xc] */
	m->eax = M32((DWORD)(m->ebp + 0x8cu));	/* 481af4: mov eax, dword ptr [ebp + 0x8c] */
	m->ecx = m->edi;	/* 481afa: mov ecx, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481afc: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 481afd: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 481afe: push esi */
	m->esp -= 4; M32(m->esp) = 0x481b04u; native_call(m, 0x47fce0u);	/* 481aff: call 0x47fce0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481b04: test eax, eax */
	if (!m->zf) goto L_481b12;	/* 481b06: jne 0x481b12 */
	m->edi = M32(m->esp); m->esp += 4;	/* 481b08: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 481b09: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 481b0a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 481b0b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481b0c: add esp, 0x40 */
	m->esp += 4 + 12; return;	/* 481b0f: ret 0xc */
L_481b12:
	m->eax = M32((DWORD)(m->esi + 0x18u));	/* 481b12: mov eax, dword ptr [esi + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481b15: test eax, eax */
	if (m->zf) goto L_481b29;	/* 481b17: je 0x481b29 */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481b19: cmp dword ptr [eax], edi */
	if (!m->zf) goto L_481b29;	/* 481b1b: jne 0x481b29 */
	m->edi = M32(m->esp); m->esp += 4;	/* 481b1d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 481b1e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 481b1f: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481b20: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 481b22: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481b23: add esp, 0x40 */
	m->esp += 4 + 12; return;	/* 481b26: ret 0xc */
L_481b29:
	m->eax = M32((DWORD)(m->esi + 0x24u));	/* 481b29: mov eax, dword ptr [esi + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481b2c: test eax, eax */
	if (!m->zf) goto L_481d30;	/* 481b2e: jne 0x481d30 */
	m->ecx = m->ebp;	/* 481b34: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x481b3bu; native_call(m, 0x4816c0u);	/* 481b36: call 0x4816c0 */
	M32((DWORD)(m->eax + 0x0u)) = m->edi;	/* 481b3b: mov dword ptr [eax], edi */
	M32((DWORD)(m->eax + 0x4u)) = m->esi;	/* 481b3d: mov dword ptr [eax + 4], esi */
	m->ecx = M32((DWORD)(m->esi + 0x18u));	/* 481b40: mov ecx, dword ptr [esi + 0x18] */
	M32((DWORD)(m->eax + 0xcu)) = m->ecx;	/* 481b43: mov dword ptr [eax + 0xc], ecx */
	m->ecx = M32((DWORD)(m->esi + 0x18u));	/* 481b46: mov ecx, dword ptr [esi + 0x18] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481b49: test ecx, ecx */
	if (m->zf) goto L_481b50;	/* 481b4b: je 0x481b50 */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 481b4d: mov dword ptr [ecx + 8], eax */
L_481b50:
	m->edx = M32((DWORD)(m->esi + 0x1cu));	/* 481b50: mov edx, dword ptr [esi + 0x1c] */
	M32((DWORD)(m->esi + 0x18u)) = m->eax;	/* 481b53: mov dword ptr [esi + 0x18], eax */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 481b56: inc edx */
	M32((DWORD)(m->esi + 0x1cu)) = m->edx;	/* 481b57: mov dword ptr [esi + 0x1c], edx */
	m->ecx = M32((DWORD)(m->ebp + 0x90u));	/* 481b5a: mov ecx, dword ptr [ebp + 0x90] */
	m->eax = m->edx;	/* 481b60: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481b62: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_481e98;	/* 481b64: jle 0x481e98 */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 481b6a: mov eax, dword ptr [esp + 0x5c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481b6e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_481e98;	/* 481b70: jle 0x481e98 */
	m->eax = (DWORD)(m->esi + 0x28u);	/* 481b76: lea eax, [esi + 0x28] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 481b79: xor edi, edi */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 481b7b: mov dword ptr [esp + 0x54], eax */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 481b7f: mov dword ptr [esp + 0x58], eax */
L_481b83:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 481b83: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 481b85: fsub dword ptr [esi] */
	m->edx = m->edi;	/* 481b87: mov edx, edi */
	{ DWORD a_ = m->edx, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 481b89: and edx, 0x80000001 */
	if (!m->sf) goto L_481b96;	/* 481b8f: jns 0x481b96 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 481b91: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 481b92: or edx, 0xfffffffe */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 481b95: inc edx */
L_481b96:
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 481b96: mov dword ptr [esp + 0x10], edx */
	m->eax = m->edi;	/* 481b9a: mov eax, edi */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x10u));	/* 481b9c: fimul dword ptr [esp + 0x10] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 481ba0: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 481ba1: and edx, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 481ba4: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 481ba6: sar eax, 2 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 481ba9: mov dword ptr [esp + 0x10], eax */
	m->eax = m->edi;	/* 481bad: mov eax, edi */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481baf: fmul dword ptr [0x4a942c] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 481bb5: cdq  */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 481bb6: fadd dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 481bb8: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 481bba: sar eax, 1 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 481bbc: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 481bc0: fld dword ptr [esi + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481bc3: fsub dword ptr [esi + 4] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x10u));	/* 481bc6: fimul dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481bca: and eax, 0x80000001 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481bcf: fmul dword ptr [0x4a942c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481bd5: fadd dword ptr [esi + 4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 481bd8: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 481bdc: fld dword ptr [esi + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 481bdf: fsub dword ptr [esi + 8] */
	if (!m->sf) goto L_481be9;	/* 481be2: jns 0x481be9 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 481be4: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481be5: or eax, 0xfffffffe */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 481be8: inc eax */
L_481be9:
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 481be9: mov dword ptr [esp + 0x10], eax */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x10u));	/* 481bed: fimul dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481bf1: fmul dword ptr [0x4a942c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 481bf7: fadd dword ptr [esi + 8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 481bfa: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 481bfe: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 481c00: fsub dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 481c02: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481c05: fsub dword ptr [esi + 4] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 481c08: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 481c0c: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 481c0f: fsub dword ptr [esi + 8] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 481c12: fstp dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481c16: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 481c1c: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481c20: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 481c26: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 481c2a: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481c2e: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 481c34: fstp dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 481c38: fadd dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 481c3c: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 481c40: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 481c44: fadd dword ptr [esp + 0x48] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 481c48: mov eax, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 481c4c: mov dword ptr [esp + 0x20], eax */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 481c50: lea eax, [esp + 0x20] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 481c54: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 481c58: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 481c5c: fadd dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 481c60: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481c64: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 481c65: mov dword ptr [esp + 0x28], ecx */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 481c69: lea ecx, [esp + 0x18] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 481c6d: fstp dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 481c71: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 481c75: push ecx */
	m->ecx = m->ebp;	/* 481c76: mov ecx, ebp */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 481c78: mov dword ptr [esp + 0x30], edx */
	m->esp -= 4; M32(m->esp) = 0x481c81u; native_call(m, 0x4818e0u);	/* 481c7c: call 0x4818e0 */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 481c81: mov ecx, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 481c85: inc edi */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 481c86: mov dword ptr [ecx], eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 481c88: add ecx, 4 */
	{ DWORD a_ = m->edi, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481c8b: cmp edi, 8 */
	M32((DWORD)(m->esi + 0x24u)) = 0x1u;	/* 481c8e: mov dword ptr [esi + 0x24], 1 */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 481c95: mov dword ptr [esp + 0x58], ecx */
	if (m->sf != m->of) goto L_481b83;	/* 481c99: jl 0x481b83 */
	m->edi = M32((DWORD)(m->esi + 0x18u));	/* 481c9f: mov edi, dword ptr [esi + 0x18] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481ca2: test edi, edi */
	if (m->zf) goto L_481cec;	/* 481ca4: je 0x481cec */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 481ca6: mov edx, dword ptr [esp + 0x5c] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 481caa: dec edx */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 481cab: mov dword ptr [esp + 0x5c], edx */
L_481caf:
	m->ebx = M32((DWORD)(m->esp + 0x54u));	/* 481caf: mov ebx, dword ptr [esp + 0x54] */
	M32((DWORD)(m->esp + 0x58u)) = 0x8u;	/* 481cb3: mov dword ptr [esp + 0x58], 8 */
L_481cbb:
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 481cbb: mov eax, dword ptr [esp + 0x5c] */
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 481cbf: mov ecx, dword ptr [edi] */
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 481cc1: mov edx, dword ptr [ebx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481cc3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 481cc4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481cc5: push edx */
	m->ecx = m->ebp;	/* 481cc6: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x481ccdu; lift_481ae0(m);	/* 481cc8: call 0x481ae0 */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 481ccd: mov eax, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 481cd1: add ebx, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 481cd4: dec eax */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 481cd5: mov dword ptr [esp + 0x58], eax */
	if (!m->zf) goto L_481cbb;	/* 481cd9: jne 0x481cbb */
	m->eax = m->edi;	/* 481cdb: mov eax, edi */
	m->edi = M32((DWORD)(m->edi + 0xcu));	/* 481cdd: mov edi, dword ptr [edi + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481ce0: push eax */
	m->ecx = m->ebp;	/* 481ce1: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x481ce8u; native_call(m, 0x481730u);	/* 481ce3: call 0x481730 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481ce8: test edi, edi */
	if (!m->zf) goto L_481caf;	/* 481cea: jne 0x481caf */
L_481cec:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481cec: xor eax, eax */
	m->edi = 0x8u;	/* 481cee: mov edi, 8 */
	M32((DWORD)(m->esi + 0x18u)) = m->eax;	/* 481cf3: mov dword ptr [esi + 0x18], eax */
	M32((DWORD)(m->esi + 0x1cu)) = m->eax;	/* 481cf6: mov dword ptr [esi + 0x1c], eax */
	m->esi = M32((DWORD)(m->esp + 0x54u));	/* 481cf9: mov esi, dword ptr [esp + 0x54] */
L_481cfd:
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 481cfd: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->eax + 0x1cu));	/* 481cff: mov ecx, dword ptr [eax + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481d02: test ecx, ecx */
	if (!m->zf && m->sf == m->of) goto L_481d1b;	/* 481d04: jg 0x481d1b */
	m->ecx = M32((DWORD)(m->eax + 0x24u));	/* 481d06: mov ecx, dword ptr [eax + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481d09: test ecx, ecx */
	if (!m->zf) goto L_481d1b;	/* 481d0b: jne 0x481d1b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481d0d: push eax */
	m->ecx = m->ebp;	/* 481d0e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x481d15u; native_call(m, 0x481980u);	/* 481d10: call 0x481980 */
	M32((DWORD)(m->esi + 0x0u)) = 0x0u;	/* 481d15: mov dword ptr [esi], 0 */
L_481d1b:
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 481d1b: add esi, 4 */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 481d1e: dec edi */
	if (!m->zf) goto L_481cfd;	/* 481d1f: jne 0x481cfd */
	m->edi = M32(m->esp); m->esp += 4;	/* 481d21: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 481d22: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 481d23: pop ebp */
	m->eax = 0x1u;	/* 481d24: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 481d29: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481d2a: add esp, 0x40 */
	m->esp += 4 + 12; return;	/* 481d2d: ret 0xc */
L_481d30:
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 481d30: mov eax, dword ptr [esp + 0x5c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 481d34: xor ecx, ecx */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 481d36: dec eax */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 481d37: mov dword ptr [esp + 0x54], ecx */
	M32((DWORD)(m->esp + 0x5cu)) = m->eax;	/* 481d3b: mov dword ptr [esp + 0x5c], eax */
	m->edi = (DWORD)(m->esi + 0x28u);	/* 481d3f: lea edi, [esi + 0x28] */
	goto L_481d48;	/* 481d42: jmp 0x481d48 */
L_481d44:
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 481d44: mov ecx, dword ptr [esp + 0x54] */
L_481d48:
	{ DWORD a_ = M32((DWORD)(m->edi + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481d48: cmp dword ptr [edi], 0 */
	if (!m->zf) goto L_481e51;	/* 481d4b: jne 0x481e51 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 481d51: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 481d53: fsub dword ptr [esi] */
	m->edx = m->ecx;	/* 481d55: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 481d57: and edx, 0x80000001 */
	if (!m->sf) goto L_481d64;	/* 481d5d: jns 0x481d64 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 481d5f: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 481d60: or edx, 0xfffffffe */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 481d63: inc edx */
L_481d64:
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 481d64: mov dword ptr [esp + 0x10], edx */
	m->eax = m->ecx;	/* 481d68: mov eax, ecx */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x10u));	/* 481d6a: fimul dword ptr [esp + 0x10] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 481d6e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 481d6f: and edx, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 481d72: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 481d74: sar eax, 2 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 481d77: mov dword ptr [esp + 0x10], eax */
	m->eax = m->ecx;	/* 481d7b: mov eax, ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481d7d: fmul dword ptr [0x4a942c] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 481d83: cdq  */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 481d84: fadd dword ptr [esi] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 481d86: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 481d88: sar eax, 1 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 481d8a: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 481d8e: fld dword ptr [esi + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481d91: fsub dword ptr [esi + 4] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x10u));	/* 481d94: fimul dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481d98: and eax, 0x80000001 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481d9d: fmul dword ptr [0x4a942c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481da3: fadd dword ptr [esi + 4] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 481da6: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 481daa: fld dword ptr [esi + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 481dad: fsub dword ptr [esi + 8] */
	if (!m->sf) goto L_481db7;	/* 481db0: jns 0x481db7 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 481db2: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481db3: or eax, 0xfffffffe */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 481db6: inc eax */
L_481db7:
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 481db7: mov dword ptr [esp + 0x10], eax */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esp + 0x10u));	/* 481dbb: fimul dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481dbf: fmul dword ptr [0x4a942c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 481dc5: fadd dword ptr [esi + 8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 481dc8: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 481dcc: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 481dce: fsub dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 481dd0: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 481dd3: fsub dword ptr [esi + 4] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 481dd6: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 481dda: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 481ddd: fsub dword ptr [esi + 8] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 481de0: fstp dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481de4: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 481dea: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481dee: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 481df4: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 481df8: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 481dfc: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 481e02: fstp dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 481e06: fadd dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 481e0a: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 481e0e: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 481e12: fadd dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 481e16: mov eax, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 481e1a: mov dword ptr [esp + 0x20], eax */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 481e1e: lea eax, [esp + 0x20] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 481e22: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 481e26: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 481e2a: fadd dword ptr [esp + 0x40] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 481e2e: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481e32: push eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 481e33: mov dword ptr [esp + 0x28], ecx */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 481e37: lea ecx, [esp + 0x18] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 481e3b: fstp dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 481e3f: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 481e43: push ecx */
	m->ecx = m->ebp;	/* 481e44: mov ecx, ebp */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 481e46: mov dword ptr [esp + 0x30], edx */
	m->esp -= 4; M32(m->esp) = 0x481e4fu; native_call(m, 0x4818e0u);	/* 481e4a: call 0x4818e0 */
	M32((DWORD)(m->edi + 0x0u)) = m->eax;	/* 481e4f: mov dword ptr [edi], eax */
L_481e51:
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 481e51: mov edx, dword ptr [esp + 0x5c] */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 481e55: mov eax, dword ptr [esp + 0x58] */
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 481e59: mov ecx, dword ptr [edi] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481e5b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481e5c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 481e5d: push ecx */
	m->ecx = m->ebp;	/* 481e5e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x481e65u; lift_481ae0(m);	/* 481e60: call 0x481ae0 */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 481e65: mov eax, dword ptr [edi] */
	m->ecx = M32((DWORD)(m->eax + 0x1cu));	/* 481e67: mov ecx, dword ptr [eax + 0x1c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481e6a: test ecx, ecx */
	if (!m->zf && m->sf == m->of) goto L_481e83;	/* 481e6c: jg 0x481e83 */
	m->ecx = M32((DWORD)(m->eax + 0x24u));	/* 481e6e: mov ecx, dword ptr [eax + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 481e71: test ecx, ecx */
	if (!m->zf) goto L_481e83;	/* 481e73: jne 0x481e83 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481e75: push eax */
	m->ecx = m->ebp;	/* 481e76: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x481e7du; native_call(m, 0x481980u);	/* 481e78: call 0x481980 */
	M32((DWORD)(m->edi + 0x0u)) = 0x0u;	/* 481e7d: mov dword ptr [edi], 0 */
L_481e83:
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 481e83: mov eax, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 481e87: add edi, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 481e8a: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 481e8b: cmp eax, 8 */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 481e8e: mov dword ptr [esp + 0x54], eax */
	if (m->sf != m->of) goto L_481d44;	/* 481e92: jl 0x481d44 */
L_481e98:
	m->edi = M32(m->esp); m->esp += 4;	/* 481e98: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 481e99: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 481e9a: pop ebp */
	m->eax = 0x1u;	/* 481e9b: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 481ea0: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481ea1: add esp, 0x40 */
	m->esp += 4 + 12; return;	/* 481ea4: ret 0xc */
}

/* skel_applyPose (0x46ab30), lifted by tools/lift.py */
static void lift_46ab30(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ab30: sub esp, 0x40 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab33: push ebx */
	m->ebx = m->ecx;	/* 46ab34: mov ebx, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab36: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x50u));	/* 46ab37: mov ebp, dword ptr [esp + 0x50] */
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ebx + 0x10u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ab3b: cmp ebp, dword ptr [ebx + 0x10] */
	if (m->sf != m->of) goto L_46ab82;	/* 46ab3e: jl 0x46ab82 */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 46ab40: mov eax, dword ptr [esp + 0x4c] */
	m->edx = 0x3f800000u;	/* 46ab44: mov edx, 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46ab49: xor ecx, ecx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46ab4b: pop ebp */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 46ab4c: mov dword ptr [eax], edx */
	M32((DWORD)(m->eax + 0x10u)) = m->ecx;	/* 46ab4e: mov dword ptr [eax + 0x10], ecx */
	M32((DWORD)(m->eax + 0x20u)) = m->ecx;	/* 46ab51: mov dword ptr [eax + 0x20], ecx */
	M32((DWORD)(m->eax + 0x30u)) = m->ecx;	/* 46ab54: mov dword ptr [eax + 0x30], ecx */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 46ab57: mov dword ptr [eax + 4], ecx */
	M32((DWORD)(m->eax + 0x14u)) = m->edx;	/* 46ab5a: mov dword ptr [eax + 0x14], edx */
	M32((DWORD)(m->eax + 0x24u)) = m->ecx;	/* 46ab5d: mov dword ptr [eax + 0x24], ecx */
	M32((DWORD)(m->eax + 0x34u)) = m->ecx;	/* 46ab60: mov dword ptr [eax + 0x34], ecx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 46ab63: mov dword ptr [eax + 8], ecx */
	M32((DWORD)(m->eax + 0x18u)) = m->ecx;	/* 46ab66: mov dword ptr [eax + 0x18], ecx */
	M32((DWORD)(m->eax + 0x28u)) = m->edx;	/* 46ab69: mov dword ptr [eax + 0x28], edx */
	M32((DWORD)(m->eax + 0x38u)) = m->ecx;	/* 46ab6c: mov dword ptr [eax + 0x38], ecx */
	M32((DWORD)(m->eax + 0xcu)) = m->ecx;	/* 46ab6f: mov dword ptr [eax + 0xc], ecx */
	M32((DWORD)(m->eax + 0x1cu)) = m->ecx;	/* 46ab72: mov dword ptr [eax + 0x1c], ecx */
	M32((DWORD)(m->eax + 0x2cu)) = m->ecx;	/* 46ab75: mov dword ptr [eax + 0x2c], ecx */
	M32((DWORD)(m->eax + 0x3cu)) = m->edx;	/* 46ab78: mov dword ptr [eax + 0x3c], edx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46ab7b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ab7c: add esp, 0x40 */
	m->esp += 4 + 12; return;	/* 46ab7f: ret 0xc */
L_46ab82:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab82: push esi */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 46ab83: lea eax, [esp + 0xc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab87: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab88: push eax */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ab89: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x46ab94u; native_call(m, M32(0x4a9270u));	/* 46ab8e: call dword ptr [0x4a9270] */
	m->edi = M32((DWORD)(m->ebx + 0x20u));	/* 46ab94: mov edi, dword ptr [ebx + 0x20] */
	M32((DWORD)(m->esp + 0x58u)) = m->edi;	/* 46ab97: mov dword ptr [esp + 0x58], edi */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 46ab9b: fild dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 46ab9f: fmul dword ptr [esp + 0x5c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 46aba3: call 0x49ec14 */
	m->esi = m->eax;	/* 46aba8: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46abaa: test esi, esi */
	if (m->sf == m->of) goto L_46abb2;	/* 46abac: jge 0x46abb2 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 46abae: xor esi, esi */
	goto L_46abb8;	/* 46abb0: jmp 0x46abb8 */
L_46abb2:
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46abb2: cmp esi, edi */
	if (m->sf != m->of) goto L_46abb8;	/* 46abb4: jl 0x46abb8 */
	m->esi = m->edi;	/* 46abb6: mov esi, edi */
L_46abb8:
	m->esp -= 4; M32(m->esp) = 0x46abbeu; native_call(m, M32(0x4a9218u));	/* 46abb8: call dword ptr [0x4a9218] */
	m->ecx = M32((DWORD)(m->ebx + 0x14u));	/* 46abbe: mov ecx, dword ptr [ebx + 0x14] */
	m->edi = (DWORD)(m->ebp*8 + 0x0u);	/* 46abc1: lea edi, [ebp*8] */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46abc8: sub edi, ebp */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 46abca: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46abcd: add edi, ecx */
	m->ebx = M32((DWORD)(m->edi + 0x60u));	/* 46abcf: mov ebx, dword ptr [edi + 0x60] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46abd2: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_46ac5b;	/* 46abd4: jle 0x46ac5b */
	m->ebp = M32((DWORD)(m->edi + 0x64u));	/* 46abda: mov ebp, dword ptr [edi + 0x64] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46abdd: xor ecx, ecx */
	m->eax = M32((DWORD)(m->ebp + 0x0u));	/* 46abdf: mov eax, dword ptr [ebp] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46abe2: cmp esi, eax */
	if (m->sf == m->of) goto L_46abea;	/* 46abe4: jge 0x46abea */
	m->esi = m->eax;	/* 46abe6: mov esi, eax */
	goto L_46ac0d;	/* 46abe8: jmp 0x46ac0d */
L_46abea:
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 46abea: dec ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46abeb: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_46ac0d;	/* 46abed: jle 0x46ac0d */
L_46abef:
	m->eax = (DWORD)(m->ebx + m->ecx*1 + 0x1u);	/* 46abef: lea eax, [ebx + ecx + 1] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46abf3: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46abf4: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46abf6: sar eax, 1 */
	m->edx = m->eax;	/* 46abf8: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46abfa: shl edx, 5 */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->edx + m->ebp*1 + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46abfd: cmp esi, dword ptr [edx + ebp] */
	if (m->sf == m->of) goto L_46ac07;	/* 46ac00: jge 0x46ac07 */
	m->ebx = (DWORD)(m->eax + 0xffffffffu);	/* 46ac02: lea ebx, [eax - 1] */
	goto L_46ac09;	/* 46ac05: jmp 0x46ac09 */
L_46ac07:
	m->ecx = m->eax;	/* 46ac07: mov ecx, eax */
L_46ac09:
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ac09: cmp ecx, ebx */
	if (m->sf != m->of) goto L_46abef;	/* 46ac0b: jl 0x46abef */
L_46ac0d:
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46ac0d: shl ecx, 5 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46ac10: add ecx, ebp */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 46ac12: mov eax, dword ptr [ecx + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46ac15: test eax, eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->eax;	/* 46ac17: mov dword ptr [esp + 0x5c], eax */
	if (m->zf || m->sf != m->of) goto L_46ac31;	/* 46ac1b: jle 0x46ac31 */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 46ac1d: mov edx, dword ptr [ecx] */
	m->eax = m->esi;	/* 46ac1f: mov eax, esi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46ac21: sub eax, edx */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 46ac23: mov dword ptr [esp + 0x58], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 46ac27: fild dword ptr [esp + 0x58] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x5cu));	/* 46ac2b: fidiv dword ptr [esp + 0x5c] */
	goto L_46ac37;	/* 46ac2f: jmp 0x46ac37 */
L_46ac31:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 46ac31: fld dword ptr [0x4a93e8] */
L_46ac37:
	{ long double t = ST(0); FPUSH(t); }	/* 46ac37: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1cu));	/* 46ac39: fmul dword ptr [ecx + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ac3c: push ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 46ac3d: fadd dword ptr [ecx + 0x10] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46ac40: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ac43: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 46ac44: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 46ac46: fmul dword ptr [ecx + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0xcu));	/* 46ac49: fadd dword ptr [ecx + 0xc] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46ac4c: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ac4f: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 46ac50: fmul dword ptr [ecx + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 46ac53: fadd dword ptr [ecx + 8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46ac56: fstp dword ptr [esp] */
	goto L_46ac67;	/* 46ac59: jmp 0x46ac67 */
L_46ac5b:
	m->ecx = M32((DWORD)(m->edi + 0x4cu));	/* 46ac5b: mov ecx, dword ptr [edi + 0x4c] */
	m->edx = M32((DWORD)(m->edi + 0x48u));	/* 46ac5e: mov edx, dword ptr [edi + 0x48] */
	m->eax = M32((DWORD)(m->edi + 0x44u));	/* 46ac61: mov eax, dword ptr [edi + 0x44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ac64: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ac65: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ac66: push eax */
L_46ac67:
	m->esp -= 4; M32(m->esp) = 0x46ac6du; native_call(m, M32(0x4a9214u));	/* 46ac67: call dword ptr [0x4a9214] */
	m->ebx = M32((DWORD)(m->edi + 0x68u));	/* 46ac6d: mov ebx, dword ptr [edi + 0x68] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46ac70: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_46ad81;	/* 46ac72: jle 0x46ad81 */
	m->edi = M32((DWORD)(m->edi + 0x6cu));	/* 46ac78: mov edi, dword ptr [edi + 0x6c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46ac7b: xor ecx, ecx */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 46ac7d: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ac7f: cmp esi, eax */
	if (m->sf == m->of) goto L_46ac87;	/* 46ac81: jge 0x46ac87 */
	m->esi = m->eax;	/* 46ac83: mov esi, eax */
	goto L_46aca8;	/* 46ac85: jmp 0x46aca8 */
L_46ac87:
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 46ac87: dec ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46ac88: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_46aca8;	/* 46ac8a: jle 0x46aca8 */
L_46ac8c:
	m->eax = (DWORD)(m->ebx + m->ecx*1 + 0x1u);	/* 46ac8c: lea eax, [ebx + ecx + 1] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46ac90: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46ac91: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46ac93: sar eax, 1 */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 46ac95: lea edx, [eax + eax*4] */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->edi + m->edx*8 + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ac98: cmp esi, dword ptr [edi + edx*8] */
	if (m->sf == m->of) goto L_46aca2;	/* 46ac9b: jge 0x46aca2 */
	m->ebx = (DWORD)(m->eax + 0xffffffffu);	/* 46ac9d: lea ebx, [eax - 1] */
	goto L_46aca4;	/* 46aca0: jmp 0x46aca4 */
L_46aca2:
	m->ecx = m->eax;	/* 46aca2: mov ecx, eax */
L_46aca4:
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46aca4: cmp ecx, ebx */
	if (m->sf != m->of) goto L_46ac8c;	/* 46aca6: jl 0x46ac8c */
L_46aca8:
	m->eax = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 46aca8: lea eax, [ecx + ecx*4] */
	m->edi = (DWORD)(m->edi + m->eax*8 + 0x0u);	/* 46acab: lea edi, [edi + eax*8] */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 46acae: mov eax, dword ptr [edi + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46acb1: test eax, eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->eax;	/* 46acb3: mov dword ptr [esp + 0x5c], eax */
	if (m->zf || m->sf != m->of) goto L_46accd;	/* 46acb7: jle 0x46accd */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->edi + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46acb9: sub esi, dword ptr [edi] */
	M32((DWORD)(m->esp + 0x58u)) = m->esi;	/* 46acbb: mov dword ptr [esp + 0x58], esi */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 46acbf: fild dword ptr [esp + 0x58] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esp + 0x5cu));	/* 46acc3: fidiv dword ptr [esp + 0x5c] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 46acc7: fstp dword ptr [esp + 0x58] */
	goto L_46acd5;	/* 46accb: jmp 0x46acd5 */
L_46accd:
	M32((DWORD)(m->esp + 0x58u)) = 0x0u;	/* 46accd: mov dword ptr [esp + 0x58], 0 */
L_46acd5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xcu)));	/* 46acd5: fld dword ptr [edi + 0xc] */
	m->esi = M32((DWORD)(0x4a91f8u));	/* 46acd8: mov esi, dword ptr [0x4a91f8] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0);	/* 46acde: fst dword ptr [esp + 0x5c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46ace2: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46ace8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46acea: test ah, 0x40 */
	if (m->zf) goto L_46ad0f;	/* 46aced: je 0x46ad0f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x10u)));	/* 46acef: fld dword ptr [edi + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46acf2: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46acf8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46acfa: test ah, 0x40 */
	if (m->zf) goto L_46ad0f;	/* 46acfd: je 0x46ad0f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x14u)));	/* 46acff: fld dword ptr [edi + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46ad02: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46ad08: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46ad0a: test ah, 0x40 */
	if (!m->zf) goto L_46ad2b;	/* 46ad0d: jne 0x46ad2b */
L_46ad0f:
	m->ecx = M32((DWORD)(m->edi + 0x14u));	/* 46ad0f: mov ecx, dword ptr [edi + 0x14] */
	m->edx = M32((DWORD)(m->edi + 0x10u));	/* 46ad12: mov edx, dword ptr [edi + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 46ad15: fld dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 46ad18: mov eax, dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ad1c: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa270u));	/* 46ad1d: fmul dword ptr [0x4aa270] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ad23: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ad24: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ad25: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46ad26: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x46ad2bu; native_call(m, m->esi);	/* 46ad29: call esi */
L_46ad2b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x1cu)));	/* 46ad2b: fld dword ptr [edi + 0x1c] */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0);	/* 46ad2e: fst dword ptr [esp + 0x5c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46ad32: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46ad38: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46ad3a: test ah, 0x40 */
	if (m->zf) goto L_46ad5f;	/* 46ad3d: je 0x46ad5f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20u)));	/* 46ad3f: fld dword ptr [edi + 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46ad42: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46ad48: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46ad4a: test ah, 0x40 */
	if (m->zf) goto L_46ad5f;	/* 46ad4d: je 0x46ad5f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x24u)));	/* 46ad4f: fld dword ptr [edi + 0x24] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46ad52: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46ad58: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46ad5a: test ah, 0x40 */
	if (!m->zf) goto L_46add5;	/* 46ad5d: jne 0x46add5 */
L_46ad5f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 46ad5f: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x18u));	/* 46ad63: fmul dword ptr [edi + 0x18] */
	m->ecx = M32((DWORD)(m->edi + 0x24u));	/* 46ad66: mov ecx, dword ptr [edi + 0x24] */
	m->edx = M32((DWORD)(m->edi + 0x20u));	/* 46ad69: mov edx, dword ptr [edi + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 46ad6c: mov eax, dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ad70: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa270u));	/* 46ad71: fmul dword ptr [0x4aa270] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ad77: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ad78: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ad79: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46ad7a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x46ad7fu; native_call(m, m->esi);	/* 46ad7d: call esi */
	goto L_46add5;	/* 46ad7f: jmp 0x46add5 */
L_46ad81:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x54u)));	/* 46ad81: fld dword ptr [edi + 0x54] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0);	/* 46ad84: fst dword ptr [esp + 0x58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46ad88: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46ad8e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46ad90: test ah, 0x40 */
	if (m->zf) goto L_46adb5;	/* 46ad93: je 0x46adb5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x58u)));	/* 46ad95: fld dword ptr [edi + 0x58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46ad98: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46ad9e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46ada0: test ah, 0x40 */
	if (m->zf) goto L_46adb5;	/* 46ada3: je 0x46adb5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x5cu)));	/* 46ada5: fld dword ptr [edi + 0x5c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 46ada8: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46adae: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46adb0: test ah, 0x40 */
	if (!m->zf) goto L_46add5;	/* 46adb3: jne 0x46add5 */
L_46adb5:
	m->ecx = M32((DWORD)(m->edi + 0x5cu));	/* 46adb5: mov ecx, dword ptr [edi + 0x5c] */
	m->edx = M32((DWORD)(m->edi + 0x58u));	/* 46adb8: mov edx, dword ptr [edi + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x50u)));	/* 46adbb: fld dword ptr [edi + 0x50] */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 46adbe: mov eax, dword ptr [esp + 0x58] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46adc2: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa270u));	/* 46adc3: fmul dword ptr [0x4aa270] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46adc9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46adca: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46adcb: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 46adcc: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x46add5u; native_call(m, M32(0x4a91f8u));	/* 46adcf: call dword ptr [0x4a91f8] */
L_46add5:
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 46add5: mov ecx, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46add9: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 46adda: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x46ade5u; native_call(m, M32(0x4a9270u));	/* 46addf: call dword ptr [0x4a9270] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 46ade5: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ade9: push edx */
	m->esp -= 4; M32(m->esp) = 0x46adf0u; native_call(m, M32(0x4a926cu));	/* 46adea: call dword ptr [0x4a926c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46adf0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46adf1: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46adf2: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46adf3: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46adf4: add esp, 0x40 */
	m->esp += 4 + 12; return;	/* 46adf7: ret 0xc */
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
