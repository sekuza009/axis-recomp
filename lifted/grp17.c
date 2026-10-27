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

static void lift_466910(X86 *m);
static void lift_463b80(X86 *m);

/* shape_getShadingColorBufferBy (0x463b80), lifted by tools/lift.py */
static void lift_463b80(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 463b80: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->esp, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463b84: sub esp, 0x80 */
	m->ecx = M32((DWORD)(m->eax + 0xb004u));	/* 463b8a: mov ecx, dword ptr [eax + 0xb004] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 463b90: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 463b91: push edi */
	m->edi = M32((DWORD)(m->esp + 0x90u));	/* 463b92: mov edi, dword ptr [esp + 0x90] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 463b99: test ecx, ecx */
	if (!m->zf && m->sf == m->of) goto L_463bb3;	/* 463b9b: jg 0x463bb3 */
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463b9d: cmp edi, 1 */
	if (!m->zf) goto L_463bb3;	/* 463ba0: jne 0x463bb3 */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 463ba2: mov ecx, dword ptr [esp + 0x94] */
	m->ecx = M32((DWORD)(m->ecx + 0x4cu));	/* 463ba9: mov ecx, dword ptr [ecx + 0x4c] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 463bac: shl ecx, 2 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463baf: xor eax, eax */
	goto L_463bc8;	/* 463bb1: jmp 0x463bc8 */
L_463bb3:
	m->ebx = M32((DWORD)(m->esp + 0x94u));	/* 463bb3: mov ebx, dword ptr [esp + 0x94] */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x0u)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463bba: test byte ptr [ebx], 2 */
	if (m->zf) goto L_463be6;	/* 463bbd: je 0x463be6 */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 463bbf: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 463bc2: shl ecx, 2 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463bc5: or eax, 0xffffffff */
L_463bc8:
	m->edi = M32((DWORD)(m->esp + 0x8cu));	/* 463bc8: mov edi, dword ptr [esp + 0x8c] */
	m->edx = m->ecx;	/* 463bcf: mov edx, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 463bd1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 463bd4: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 463bd6: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 463bd8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 463bdb: rep stosb byte ptr es:[edi], al */
	m->edi = M32(m->esp); m->esp += 4;	/* 463bdd: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 463bde: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463bdf: add esp, 0x80 */
	m->esp += 4 + 0; return;	/* 463be5: ret  */
L_463be6:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463be6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 463be8: test ecx, ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 463bea: mov dword ptr [esp + 0x30], eax */
	if (m->zf || m->sf != m->of) goto L_464a4c;	/* 463bee: jle 0x464a4c */
	m->edx = M32((DWORD)(m->esp + 0x8cu));	/* 463bf4: mov edx, dword ptr [esp + 0x8c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 463bfb: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 463bfc: push esi */
	m->esi = M32((DWORD)(m->esp + 0xa4u));	/* 463bfd: mov esi, dword ptr [esp + 0xa4] */
	goto L_463c1f;	/* 463c04: jmp 0x463c1f */
L_463c06:
	m->edi = M32((DWORD)(m->esp + 0x98u));	/* 463c06: mov edi, dword ptr [esp + 0x98] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 463c0d: mov eax, dword ptr [esp + 0x38] */
	m->edx = M32((DWORD)(m->esp + 0x94u));	/* 463c11: mov edx, dword ptr [esp + 0x94] */
	m->esi = M32((DWORD)(m->esp + 0xa4u));	/* 463c18: mov esi, dword ptr [esp + 0xa4] */
L_463c1f:
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 463c1f: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 463c22: xor ebp, ebp */
	m->eax = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 463c24: lea eax, [eax + ecx*2] */
	m->ecx = M32((DWORD)(m->esp + 0xa0u));	/* 463c27: mov ecx, dword ptr [esp + 0xa0] */
	m->ecx = (DWORD)(m->ecx + m->eax*4 + 0x4u);	/* 463c2e: lea ecx, [ecx + eax*4 + 4] */
	m->eax = M32((DWORD)(m->ecx + 0x8u));	/* 463c32: mov eax, dword ptr [ecx + 8] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463c35: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_464a1e;	/* 463c38: ja 0x464a1e */
	switch (m->eax) { case 0: goto L_464958; case 1: goto L_463c45; case 2: goto L_463ee4; case 3: goto L_464445; default: abort(); }	/* 463c3e: jmp dword ptr [eax*4 + 0x464a58] */
L_463c45:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463c45: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xcu))) & 0xff) << 0);	/* 463c47: mov al, byte ptr [ecx + 0xc] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 463c4a: mov dword ptr [esp + 0x18], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463c4e: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xdu))) & 0xff) << 0);	/* 463c50: mov al, byte ptr [ecx + 0xd] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 463c53: mov dword ptr [esp + 0x1c], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463c57: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xeu))) & 0xff) << 0);	/* 463c59: mov al, byte ptr [ecx + 0xe] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 463c5c: mov dword ptr [esp + 0x20], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463c60: xor eax, eax */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463c62: cmp esi, eax */
	if (m->zf) goto L_463cb5;	/* 463c64: je 0x463cb5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 463c66: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x24u));	/* 463c69: fmul dword ptr [ecx + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 463c6c: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x20u));	/* 463c6f: fmul dword ptr [ecx + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463c72: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1cu)));	/* 463c74: fld dword ptr [ecx + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 463c77: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463c79: faddp st(1) */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 463c7b: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 463c7f: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1cu));	/* 463c82: fmul dword ptr [ecx + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 463c85: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x24u));	/* 463c88: fmul dword ptr [ecx + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463c8b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 463c8d: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x20u));	/* 463c90: fmul dword ptr [ecx + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463c93: faddp st(1) */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 463c95: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 463c99: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x1cu));	/* 463c9c: fmul dword ptr [ecx + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 463c9f: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x24u));	/* 463ca2: fmul dword ptr [ecx + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463ca5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 463ca7: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x20u));	/* 463caa: fmul dword ptr [ecx + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463cad: faddp st(1) */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 463caf: fstp dword ptr [esp + 0x5c] */
	goto L_463ccc;	/* 463cb3: jmp 0x463ccc */
L_463cb5:
	{ DWORD a_ = m->ecx, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 463cb5: add ecx, 0x1c */
	m->esi = M32((DWORD)(m->ecx + 0x0u));	/* 463cb8: mov esi, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x54u)) = m->esi;	/* 463cba: mov dword ptr [esp + 0x54], esi */
	m->esi = M32((DWORD)(m->ecx + 0x4u));	/* 463cbe: mov esi, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x58u)) = m->esi;	/* 463cc1: mov dword ptr [esp + 0x58], esi */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 463cc5: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 463cc8: mov dword ptr [esp + 0x5c], ecx */
L_463ccc:
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 463ccc: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463ccf: cmp edi, 1 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 463cd2: mov dword ptr [esp + 0x10], eax */
	if (!m->zf) goto L_463dda;	/* 463cd6: jne 0x463dda */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463cdc: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_463dca;	/* 463cde: jle 0x463dca */
	m->edi = 0xfffffffeu;	/* 463ce4: mov edi, 0xfffffffe */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 463ce9: mov dword ptr [esp + 0x30], 0 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 463cf1: sub edi, edx */
	m->ebp = (DWORD)(m->edx + 0x2u);	/* 463cf3: lea ebp, [edx + 2] */
	M32((DWORD)(m->esp + 0x24u)) = m->edi;	/* 463cf6: mov dword ptr [esp + 0x24], edi */
	goto L_463d00;	/* 463cfa: jmp 0x463d00 */
L_463cfc:
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 463cfc: mov edi, dword ptr [esp + 0x24] */
L_463d00:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 463d00: mov eax, dword ptr [esp + 0x30] */
	m->esi = M32((DWORD)(m->ebx + 0x54u));	/* 463d04: mov esi, dword ptr [ebx + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 463d07: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->esi*1 + 0x8u));	/* 463d0b: fmul dword ptr [eax + esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 463d0f: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->esi*1 + 0x4u));	/* 463d13: fmul dword ptr [eax + esi + 4] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 463d17: add eax, esi */
	m->edx = M32((DWORD)(m->ebx + 0x58u));	/* 463d19: mov edx, dword ptr [ebx + 0x58] */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 463d1c: add edi, ebp */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463d1e: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 463d20: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 463d24: fmul dword ptr [eax] */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 463d26: add edi, edx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463d28: faddp st(1) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 463d2a: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 463d30: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 463d36: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 463d3b: test eax, eax */
	if (m->sf == m->of) goto L_463d41;	/* 463d3d: jge 0x463d41 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463d3f: xor eax, eax */
L_463d41:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 463d41: xor edx, edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 463d43: xor ecx, ecx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 463d45: mov dl, byte ptr [edi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x2u))) & 0xff) << 0);	/* 463d47: mov cl, byte ptr [edi + 2] */
	m->esi = m->edx;	/* 463d4a: mov esi, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 463d4c: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 463d4e: mov dl, byte ptr [edi + 1] */
	{ long long p_ = (long long)(int)m->ecx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 463d51: imul ecx, eax */
	{ long long p_ = (long long)(int)m->esi * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 463d54: imul esi, eax */
	{ long long p_ = (long long)(int)m->edx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 463d57: imul edx, eax */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 463d5a: imul ecx, dword ptr [esp + 0x20] */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 463d5f: imul esi, dword ptr [esp + 0x18] */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 463d64: imul edx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 463d69: sar ecx, 0x10 */
	{ DWORD a_ = m->esi, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 463d6c: sar esi, 0x10 */
	{ DWORD a_ = m->edx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463d6f: sar edx, 0x10 */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463d72: cmp ecx, 0xff */
	if (m->sf != m->of) goto L_463d7f;	/* 463d78: jl 0x463d7f */
	m->ecx = 0xffu;	/* 463d7a: mov ecx, 0xff */
L_463d7f:
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463d7f: cmp edx, 0xff */
	if (m->sf != m->of) goto L_463d8c;	/* 463d85: jl 0x463d8c */
	m->edx = 0xffu;	/* 463d87: mov edx, 0xff */
L_463d8c:
	{ DWORD a_ = m->esi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463d8c: cmp esi, 0xff */
	m->eax = m->esi;	/* 463d92: mov eax, esi */
	if (m->sf != m->of) goto L_463d9b;	/* 463d94: jl 0x463d9b */
	m->eax = 0xffu;	/* 463d96: mov eax, 0xff */
L_463d9b:
	m->esi = M32((DWORD)(m->esp + 0x30u));	/* 463d9b: mov esi, dword ptr [esp + 0x30] */
	M8((DWORD)(m->ebp + 0xfffffffeu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 463d9f: mov byte ptr [ebp - 2], al */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 463da2: mov eax, dword ptr [esp + 0x10] */
	M8((DWORD)(m->ebp + 0xffffffffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 463da6: mov byte ptr [ebp - 1], dl */
	M8((DWORD)(m->ebp + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 463da9: mov byte ptr [ebp], cl */
	M8((DWORD)(m->ebp + 0x1u)) = (BYTE)(0xffu);	/* 463dac: mov byte ptr [ebp + 1], 0xff */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 463db0: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 463db3: inc eax */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 463db4: add esi, 0xc */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 463db7: add ebp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463dba: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 463dbc: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x30u)) = m->esi;	/* 463dc0: mov dword ptr [esp + 0x30], esi */
	if (m->sf != m->of) goto L_463cfc;	/* 463dc4: jl 0x463cfc */
L_463dca:
	M32((DWORD)(m->esp + 0x98u)) = 0x0u;	/* 463dca: mov dword ptr [esp + 0x98], 0 */
	goto L_464a2c;	/* 463dd5: jmp 0x464a2c */
L_463dda:
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463dda: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_464a2c;	/* 463ddc: jle 0x464a2c */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 463de2: mov ecx, dword ptr [esp + 0x94] */
	m->eax = 0xfffffffeu;	/* 463de9: mov eax, 0xfffffffe */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 463dee: sub eax, ecx */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 463df0: mov dword ptr [esp + 0x30], 0 */
	m->edi = (DWORD)(m->ecx + 0x2u);	/* 463df8: lea edi, [ecx + 2] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 463dfb: mov dword ptr [esp + 0x24], eax */
L_463dff:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 463dff: mov eax, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->ebx + 0x54u));	/* 463e03: mov edx, dword ptr [ebx + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 463e06: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*1 + 0x8u));	/* 463e0a: fmul dword ptr [eax + edx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 463e0e: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*1 + 0x4u));	/* 463e12: fmul dword ptr [eax + edx + 4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 463e16: add eax, edx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 463e18: mov ecx, dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463e1c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 463e1e: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 463e22: fmul dword ptr [eax] */
	m->esi = (DWORD)(m->edi + m->ecx*1 + 0x0u);	/* 463e24: lea esi, [edi + ecx] */
	m->ecx = M32((DWORD)(m->ebx + 0x58u));	/* 463e27: mov ecx, dword ptr [ebx + 0x58] */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 463e2a: add esi, ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463e2c: faddp st(1) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 463e2e: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 463e34: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 463e3a: call 0x49ec14 */
	m->ebp = m->eax;	/* 463e3f: mov ebp, eax */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 463e41: test ebp, ebp */
	if (m->sf == m->of) goto L_463e47;	/* 463e43: jge 0x463e47 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 463e45: xor ebp, ebp */
L_463e47:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 463e47: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 463e49: xor edx, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 463e4b: mov cl, byte ptr [esi] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0xfffffffeu))) & 0xff) << 0);	/* 463e4d: mov dl, byte ptr [edi - 2] */
	{ long long p_ = (long long)(int)m->ecx * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 463e50: imul ecx, ebp */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 463e53: imul ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ecx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 463e58: sar ecx, 0x10 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 463e5b: add ecx, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 463e5d: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 463e5f: mov dl, byte ptr [esi + 1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463e62: xor eax, eax */
	{ long long p_ = (long long)(int)m->edx * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 463e64: imul edx, ebp */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 463e67: imul edx, dword ptr [esp + 0x1c] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0xffffffffu))) & 0xff) << 0);	/* 463e6c: mov al, byte ptr [edi - 1] */
	{ DWORD a_ = m->edx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 463e6f: sar edx, 0x10 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 463e72: add edx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463e74: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x2u))) & 0xff) << 0);	/* 463e76: mov al, byte ptr [esi + 2] */
	m->esi = m->eax;	/* 463e79: mov esi, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463e7b: xor eax, eax */
	{ long long p_ = (long long)(int)m->esi * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 463e7d: imul esi, ebp */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 463e80: imul esi, dword ptr [esp + 0x20] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 463e85: mov al, byte ptr [edi] */
	{ DWORD a_ = m->esi, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 463e87: sar esi, 0x10 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 463e8a: add esi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463e8c: cmp ecx, 0xff */
	if (m->sf != m->of) goto L_463e99;	/* 463e92: jl 0x463e99 */
	m->ecx = 0xffu;	/* 463e94: mov ecx, 0xff */
L_463e99:
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463e99: cmp edx, 0xff */
	M8((DWORD)(m->edi + 0xfffffffeu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 463e9f: mov byte ptr [edi - 2], cl */
	if (m->sf != m->of) goto L_463ea9;	/* 463ea2: jl 0x463ea9 */
	m->edx = 0xffu;	/* 463ea4: mov edx, 0xff */
L_463ea9:
	{ DWORD a_ = m->esi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463ea9: cmp esi, 0xff */
	M8((DWORD)(m->edi + 0xffffffffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 463eaf: mov byte ptr [edi - 1], dl */
	m->eax = m->esi;	/* 463eb2: mov eax, esi */
	if (m->sf != m->of) goto L_463ebb;	/* 463eb4: jl 0x463ebb */
	m->eax = 0xffu;	/* 463eb6: mov eax, 0xff */
L_463ebb:
	m->esi = M32((DWORD)(m->esp + 0x30u));	/* 463ebb: mov esi, dword ptr [esp + 0x30] */
	M8((DWORD)(m->edi + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 463ebf: mov byte ptr [edi], al */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 463ec1: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 463ec5: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 463ec8: inc eax */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 463ec9: add esi, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 463ecc: add edi, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463ecf: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 463ed1: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x30u)) = m->esi;	/* 463ed5: mov dword ptr [esp + 0x30], esi */
	if (m->sf != m->of) goto L_463dff;	/* 463ed9: jl 0x463dff */
	goto L_464a2c;	/* 463edf: jmp 0x464a2c */
L_463ee4:
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 463ee4: cmp esi, ebp */
	if (m->zf) goto L_463f40;	/* 463ee6: je 0x463f40 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 463ee8: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 463eeb: fmul dword ptr [ecx + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 463eee: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 463ef1: fmul dword ptr [ecx + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463ef4: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 463ef6: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 463ef8: fmul dword ptr [ecx + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463efb: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 463efd: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 463f00: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 463f04: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 463f07: fmul dword ptr [ecx + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 463f0a: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 463f0d: fmul dword ptr [ecx + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463f10: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 463f12: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 463f15: fmul dword ptr [ecx + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463f18: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 463f1a: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 463f1d: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 463f21: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 463f24: fmul dword ptr [ecx + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 463f27: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 463f2a: fmul dword ptr [ecx + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463f2d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 463f2f: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 463f32: fmul dword ptr [ecx + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 463f35: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 463f37: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 463f3a: fstp dword ptr [esp + 0x44] */
	goto L_463f58;	/* 463f3e: jmp 0x463f58 */
L_463f40:
	m->eax = (DWORD)(m->ecx + 0x10u);	/* 463f40: lea eax, [ecx + 0x10] */
	m->esi = M32((DWORD)(m->ecx + 0x10u));	/* 463f43: mov esi, dword ptr [ecx + 0x10] */
	M32((DWORD)(m->esp + 0x3cu)) = m->esi;	/* 463f46: mov dword ptr [esp + 0x3c], esi */
	m->esi = M32((DWORD)(m->eax + 0x4u));	/* 463f4a: mov esi, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x40u)) = m->esi;	/* 463f4d: mov dword ptr [esp + 0x40], esi */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 463f51: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 463f54: mov dword ptr [esp + 0x44], eax */
L_463f58:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 463f58: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x28u));	/* 463f5c: fadd dword ptr [ecx + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x68u)); FPOP();	/* 463f5f: fcomp dword ptr [ebx + 0x68] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 463f62: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463f64: test ah, 0x41 */
	if (!m->zf) goto L_46441a;	/* 463f67: jne 0x46441a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 463f6d: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x28u));	/* 463f71: fsub dword ptr [ecx + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x74u)); FPOP();	/* 463f74: fcomp dword ptr [ebx + 0x74] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 463f77: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463f79: test ah, 1 */
	if (m->zf) goto L_46441a;	/* 463f7c: je 0x46441a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 463f82: fld dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x28u));	/* 463f86: fadd dword ptr [ecx + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x6cu)); FPOP();	/* 463f89: fcomp dword ptr [ebx + 0x6c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 463f8c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463f8e: test ah, 0x41 */
	if (!m->zf) goto L_46441a;	/* 463f91: jne 0x46441a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 463f97: fld dword ptr [esp + 0x40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x28u));	/* 463f9b: fsub dword ptr [ecx + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x78u)); FPOP();	/* 463f9e: fcomp dword ptr [ebx + 0x78] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 463fa1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463fa3: test ah, 1 */
	if (m->zf) goto L_46441a;	/* 463fa6: je 0x46441a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 463fac: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x28u));	/* 463fb0: fadd dword ptr [ecx + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x70u)); FPOP();	/* 463fb3: fcomp dword ptr [ebx + 0x70] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 463fb6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463fb8: test ah, 0x41 */
	if (!m->zf) goto L_46441a;	/* 463fbb: jne 0x46441a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 463fc1: fld dword ptr [esp + 0x44] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x28u));	/* 463fc5: fsub dword ptr [ecx + 0x28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x7cu)); FPOP();	/* 463fc8: fcomp dword ptr [ebx + 0x7c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 463fcb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 463fcd: test ah, 1 */
	if (m->zf) goto L_46441a;	/* 463fd0: je 0x46441a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x28u)));	/* 463fd6: fld dword ptr [ecx + 0x28] */
	{ long double t = ST(0); FPUSH(t); }	/* 463fd9: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 463fdb: fmulp st(1) */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463fdd: xor eax, eax */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 463fdf: mov dword ptr [esp + 0x10], 0 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xcu))) & 0xff) << 0);	/* 463fe7: mov al, byte ptr [ecx + 0xc] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 463fea: fst dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 463fee: fmul dword ptr [0x4a94f8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 463ff4: mov dword ptr [esp + 0x18], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 463ff8: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xdu))) & 0xff) << 0);	/* 463ffa: mov al, byte ptr [ecx + 0xd] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 463ffd: mov dword ptr [esp + 0x1c], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464001: xor eax, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 464003: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 464007: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 46400b: fsub dword ptr [esp + 0x28] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xeu))) & 0xff) << 0);	/* 46400f: mov al, byte ptr [ecx + 0xe] */
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464012: cmp edi, 1 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 464015: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 464019: mov eax, dword ptr [ebx + 0x4c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 46401c: fstp dword ptr [esp + 0x34] */
	if (!m->zf) goto L_46421b;	/* 464020: jne 0x46421b */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464026: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46420b;	/* 464028: jle 0x46420b */
	m->edi = 0xfffffffeu;	/* 46402e: mov edi, 0xfffffffe */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 464033: mov dword ptr [esp + 0x30], 0 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46403b: sub edi, edx */
	m->ebp = (DWORD)(m->edx + 0x2u);	/* 46403d: lea ebp, [edx + 2] */
	M32((DWORD)(m->esp + 0x24u)) = m->edi;	/* 464040: mov dword ptr [esp + 0x24], edi */
	goto L_46404a;	/* 464044: jmp 0x46404a */
L_464046:
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 464046: mov edi, dword ptr [esp + 0x24] */
L_46404a:
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 46404a: mov eax, dword ptr [ebx + 0x50] */
	m->esi = M32((DWORD)(m->esp + 0x30u));	/* 46404d: mov esi, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 464051: add eax, esi */
	m->edx = M32((DWORD)(m->ebx + 0x58u));	/* 464053: mov edx, dword ptr [ebx + 0x58] */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 464056: add edi, edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 464058: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 46405a: fsub dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46405e: add edi, ebp */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 464060: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 464064: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 464067: fsub dword ptr [esp + 0x40] */
	m->ecx = M32((DWORD)(m->esp + 0x60u));	/* 46406b: mov ecx, dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 46406f: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 464073: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 464076: fsub dword ptr [esp + 0x44] */
	m->edx = M32((DWORD)(m->esp + 0x64u));	/* 46407a: mov edx, dword ptr [esp + 0x64] */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 46407e: mov dword ptr [esp + 0x48], ecx */
	M32((DWORD)(m->esp + 0x4cu)) = m->edx;	/* 464082: mov dword ptr [esp + 0x4c], edx */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 464086: fstp dword ptr [esp + 0x68] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 46408a: fld dword ptr [esp + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x68u));	/* 46408e: fmul dword ptr [esp + 0x68] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 464092: fld dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 464096: fmul dword ptr [esp + 0x64] */
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 46409a: mov eax, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 46409e: mov dword ptr [esp + 0x50], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4640a2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 4640a4: fld dword ptr [esp + 0x60] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 4640a8: fmul dword ptr [esp + 0x60] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4640ac: faddp st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4640ae: fst dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x2cu)); FPOP();	/* 4640b2: fcomp dword ptr [esp + 0x2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4640b6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4640b8: test ah, 1 */
	if (m->zf) goto L_4641e0;	/* 4640bb: je 0x4641e0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4640c1: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u)); FPOP();	/* 4640c5: fcomp dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4640c9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4640cb: test ah, 0x41 */
	if (!m->zf) goto L_46417e;	/* 4640ce: jne 0x46417e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4640d4: fld dword ptr [esp + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 4640d8: fsub dword ptr [esp + 0x28] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 4640dc: fdiv dword ptr [esp + 0x34] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4640e0: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 4640e6: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4640ec: call 0x49ec14 */
	m->esi = m->eax;	/* 4640f1: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4640f3: cmp esi, 0x100 */
	if (m->zf || m->sf != m->of) goto L_464100;	/* 4640f9: jle 0x464100 */
	m->esi = 0x100u;	/* 4640fb: mov esi, 0x100 */
L_464100:
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 464100: lea ecx, [esp + 0x48] */
	m->esp -= 4; M32(m->esp) = 0x464109u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 464104: call 0x467760 */
	m->ecx = m->esi;	/* 464109: mov ecx, esi */
	m->eax = m->esi;	/* 46410b: mov eax, esi */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 46410d: imul ecx, dword ptr [esp + 0x18] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 464112: imul eax, dword ptr [esp + 0x1c] */
	ST(0) = ST(0); FPOP();	/* 464117: fstp st(0) */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 464119: imul esi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46411e: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 464120: mov dl, byte ptr [edi] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 464122: sar ecx, 8 */
	{ long long p_ = (long long)(int)m->ecx * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 464125: imul ecx, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464128: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 46412a: mov dl, byte ptr [edi + 1] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46412d: sar eax, 8 */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 464130: imul eax, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464133: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x2u))) & 0xff) << 0);	/* 464135: mov dl, byte ptr [edi + 2] */
	{ DWORD a_ = m->esi, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 464138: sar esi, 8 */
	{ long long p_ = (long long)(int)m->esi * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 46413b: imul esi, edx */
	{ DWORD a_ = m->esi, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46413e: sar esi, 8 */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 464141: sar ecx, 8 */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 464144: sar eax, 8 */
	{ DWORD a_ = m->esi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464147: cmp esi, 0xff */
	m->edx = m->esi;	/* 46414d: mov edx, esi */
	if (m->sf != m->of) goto L_464156;	/* 46414f: jl 0x464156 */
	m->edx = 0xffu;	/* 464151: mov edx, 0xff */
L_464156:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464156: cmp eax, 0xff */
	if (m->sf != m->of) goto L_464162;	/* 46415b: jl 0x464162 */
	m->eax = 0xffu;	/* 46415d: mov eax, 0xff */
L_464162:
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464162: cmp ecx, 0xff */
	if (m->sf != m->of) goto L_46416f;	/* 464168: jl 0x46416f */
	m->ecx = 0xffu;	/* 46416a: mov ecx, 0xff */
L_46416f:
	M8((DWORD)(m->ebp + 0xfffffffeu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 46416f: mov byte ptr [ebp - 2], cl */
	M8((DWORD)(m->ebp + 0xffffffffu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 464172: mov byte ptr [ebp - 1], al */
	M8((DWORD)(m->ebp + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 464175: mov byte ptr [ebp], dl */
	M8((DWORD)(m->ebp + 0x1u)) = (BYTE)(0xffu);	/* 464178: mov byte ptr [ebp + 1], 0xff */
	goto L_4641e9;	/* 46417c: jmp 0x4641e9 */
L_46417e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46417e: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464180: xor ecx, ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 464182: mov al, byte ptr [edi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 464184: mov cl, byte ptr [edi + 1] */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 464187: imul ecx, dword ptr [esp + 0x1c] */
	m->esi = m->eax;	/* 46418c: mov esi, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46418e: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x2u))) & 0xff) << 0);	/* 464190: mov al, byte ptr [edi + 2] */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 464193: imul esi, dword ptr [esp + 0x18] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 464198: imul eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46419d: sar eax, 8 */
	{ DWORD a_ = m->esi, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4641a0: sar esi, 8 */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4641a3: sar ecx, 8 */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4641a6: cmp eax, 0xff */
	m->edx = m->eax;	/* 4641ab: mov edx, eax */
	if (m->sf != m->of) goto L_4641b4;	/* 4641ad: jl 0x4641b4 */
	m->edx = 0xffu;	/* 4641af: mov edx, 0xff */
L_4641b4:
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4641b4: cmp ecx, 0xff */
	m->eax = m->ecx;	/* 4641ba: mov eax, ecx */
	if (m->sf != m->of) goto L_4641c3;	/* 4641bc: jl 0x4641c3 */
	m->eax = 0xffu;	/* 4641be: mov eax, 0xff */
L_4641c3:
	{ DWORD a_ = m->esi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4641c3: cmp esi, 0xff */
	m->ecx = m->esi;	/* 4641c9: mov ecx, esi */
	if (m->sf != m->of) goto L_46416f;	/* 4641cb: jl 0x46416f */
	m->ecx = 0xffu;	/* 4641cd: mov ecx, 0xff */
	M8((DWORD)(m->ebp + 0xffffffffu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4641d2: mov byte ptr [ebp - 1], al */
	M8((DWORD)(m->ebp + 0xfffffffeu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4641d5: mov byte ptr [ebp - 2], cl */
	M8((DWORD)(m->ebp + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4641d8: mov byte ptr [ebp], dl */
	M8((DWORD)(m->ebp + 0x1u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4641db: mov byte ptr [ebp + 1], cl */
	goto L_4641e9;	/* 4641de: jmp 0x4641e9 */
L_4641e0:
	m->ecx = M32((DWORD)(0xa1f278u));	/* 4641e0: mov ecx, dword ptr [0xa1f278] */
	M32((DWORD)(m->ebp + 0xfffffffeu)) = m->ecx;	/* 4641e6: mov dword ptr [ebp - 2], ecx */
L_4641e9:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4641e9: mov eax, dword ptr [esp + 0x10] */
	m->esi = M32((DWORD)(m->esp + 0x30u));	/* 4641ed: mov esi, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 4641f1: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4641f4: inc eax */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4641f5: add esi, 0xc */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4641f8: add ebp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4641fb: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4641fd: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x30u)) = m->esi;	/* 464201: mov dword ptr [esp + 0x30], esi */
	if (m->sf != m->of) goto L_464046;	/* 464205: jl 0x464046 */
L_46420b:
	M32((DWORD)(m->esp + 0x98u)) = 0x0u;	/* 46420b: mov dword ptr [esp + 0x98], 0 */
	goto L_464a2c;	/* 464216: jmp 0x464a2c */
L_46421b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46421b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_464a2c;	/* 46421d: jle 0x464a2c */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 464223: mov ecx, dword ptr [esp + 0x94] */
	m->eax = 0xfffffffeu;	/* 46422a: mov eax, 0xfffffffe */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46422f: sub eax, ecx */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 464231: mov dword ptr [esp + 0x30], 0 */
	m->esi = (DWORD)(m->ecx + 0x2u);	/* 464239: lea esi, [ecx + 2] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 46423c: mov dword ptr [esp + 0x24], eax */
L_464240:
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 464240: mov eax, dword ptr [ebx + 0x50] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 464243: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 464247: add eax, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 464249: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 46424b: fsub dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 46424f: fstp dword ptr [esp + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 464253: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 464256: fsub dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->esp + 0x6cu));	/* 46425a: mov edx, dword ptr [esp + 0x6c] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 46425e: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 464262: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 464265: fsub dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x70u));	/* 464269: mov eax, dword ptr [esp + 0x70] */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 46426d: mov dword ptr [esp + 0x48], edx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 464271: mov dword ptr [esp + 0x4c], eax */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 464275: fstp dword ptr [esp + 0x74] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 464279: fld dword ptr [esp + 0x74] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x74u));	/* 46427d: fmul dword ptr [esp + 0x74] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 464281: fld dword ptr [esp + 0x70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x70u));	/* 464285: fmul dword ptr [esp + 0x70] */
	m->ecx = M32((DWORD)(m->esp + 0x74u));	/* 464289: mov ecx, dword ptr [esp + 0x74] */
	M32((DWORD)(m->esp + 0x50u)) = m->ecx;	/* 46428d: mov dword ptr [esp + 0x50], ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 464291: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x6cu)));	/* 464293: fld dword ptr [esp + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x6cu));	/* 464297: fmul dword ptr [esp + 0x6c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46429b: faddp st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 46429d: fst dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x2cu)); FPOP();	/* 4642a1: fcomp dword ptr [esp + 0x2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4642a5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4642a7: test ah, 1 */
	if (m->zf) goto L_4643f3;	/* 4642aa: je 0x4643f3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4642b0: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u)); FPOP();	/* 4642b4: fcomp dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4642b8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4642ba: test ah, 0x41 */
	if (!m->zf) goto L_46437a;	/* 4642bd: jne 0x46437a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4642c3: fld dword ptr [esp + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 4642c7: fsub dword ptr [esp + 0x28] */
	m->ebp = M32((DWORD)(m->ebx + 0x58u));	/* 4642cb: mov ebp, dword ptr [ebx + 0x58] */
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 4642ce: mov edi, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ebp, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4642d2: add ebp, edi */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 4642d4: fdiv dword ptr [esp + 0x34] */
	{ DWORD a_ = m->ebp, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4642d8: add ebp, esi */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4642da: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 4642e0: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4642e6: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4642eb: cmp eax, 0x100 */
	if (m->zf || m->sf != m->of) goto L_4642f7;	/* 4642f0: jle 0x4642f7 */
	m->eax = 0x100u;	/* 4642f2: mov eax, 0x100 */
L_4642f7:
	m->ecx = m->eax;	/* 4642f7: mov ecx, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4642f9: xor edx, edx */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 4642fb: imul ecx, dword ptr [esp + 0x18] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x0u))) & 0xff) << 0);	/* 464300: mov dl, byte ptr [ebp] */
	m->edi = m->eax;	/* 464303: mov edi, eax */
	{ long long p_ = (long long)(int)m->edi * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 464305: imul edi, dword ptr [esp + 0x1c] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46430a: imul eax, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46430f: sar ecx, 8 */
	{ long long p_ = (long long)(int)m->ecx * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 464312: imul ecx, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464315: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xfffffffeu))) & 0xff) << 0);	/* 464317: mov dl, byte ptr [esi - 2] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46431a: sar ecx, 8 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46431d: add ecx, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46431f: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x1u))) & 0xff) << 0);	/* 464321: mov dl, byte ptr [ebp + 1] */
	{ DWORD a_ = m->edi, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 464324: sar edi, 8 */
	{ long long p_ = (long long)(int)m->edi * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 464327: imul edi, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46432a: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xffffffffu))) & 0xff) << 0);	/* 46432c: mov dl, byte ptr [esi - 1] */
	{ DWORD a_ = m->edi, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 46432f: sar edi, 8 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 464332: add edi, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464334: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x2u))) & 0xff) << 0);	/* 464336: mov dl, byte ptr [ebp + 2] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 464339: sar eax, 8 */
	{ long long p_ = (long long)(int)m->eax * (int)m->edx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46433c: imul eax, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46433f: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 464341: mov dl, byte ptr [esi] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 464343: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 464346: add eax, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464348: cmp ecx, 0xff */
	if (m->sf != m->of) goto L_464355;	/* 46434e: jl 0x464355 */
	m->ecx = 0xffu;	/* 464350: mov ecx, 0xff */
L_464355:
	M8((DWORD)(m->esi + 0xfffffffeu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 464355: mov byte ptr [esi - 2], cl */
	{ DWORD a_ = m->edi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464358: cmp edi, 0xff */
	m->ecx = m->edi;	/* 46435e: mov ecx, edi */
	if (m->sf != m->of) goto L_464367;	/* 464360: jl 0x464367 */
	m->ecx = 0xffu;	/* 464362: mov ecx, 0xff */
L_464367:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464367: cmp eax, 0xff */
	M8((DWORD)(m->esi + 0xffffffffu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 46436c: mov byte ptr [esi - 1], cl */
	if (m->sf != m->of) goto L_464376;	/* 46436f: jl 0x464376 */
	m->eax = 0xffu;	/* 464371: mov eax, 0xff */
L_464376:
	M8((DWORD)(m->esi + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 464376: mov byte ptr [esi], al */
	goto L_4643f3;	/* 464378: jmp 0x4643f3 */
L_46437a:
	m->ecx = M32((DWORD)(m->ebx + 0x58u));	/* 46437a: mov ecx, dword ptr [ebx + 0x58] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 46437d: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 464381: add ecx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464383: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 464385: add ecx, esi */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464387: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xfffffffeu))) & 0xff) << 0);	/* 464389: mov dl, byte ptr [esi - 2] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x0u))) & 0xff) << 0);	/* 46438c: mov al, byte ptr [ecx] */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46438e: imul eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 464393: sar eax, 8 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 464396: add eax, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464398: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x1u))) & 0xff) << 0);	/* 46439a: mov dl, byte ptr [ecx + 1] */
	m->edi = m->edx;	/* 46439d: mov edi, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46439f: xor edx, edx */
	{ long long p_ = (long long)(int)m->edi * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 4643a1: imul edi, dword ptr [esp + 0x1c] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xffffffffu))) & 0xff) << 0);	/* 4643a6: mov dl, byte ptr [esi - 1] */
	{ DWORD a_ = m->edi, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4643a9: sar edi, 8 */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4643ac: add edi, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4643ae: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0x2u))) & 0xff) << 0);	/* 4643b0: mov dl, byte ptr [ecx + 2] */
	m->ecx = m->edx;	/* 4643b3: mov ecx, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4643b5: xor edx, edx */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 4643b7: imul ecx, dword ptr [esp + 0x20] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4643bc: mov dl, byte ptr [esi] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4643be: sar ecx, 8 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4643c1: add ecx, edx */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4643c3: cmp eax, 0xff */
	if (m->sf != m->of) goto L_4643cf;	/* 4643c8: jl 0x4643cf */
	m->eax = 0xffu;	/* 4643ca: mov eax, 0xff */
L_4643cf:
	M8((DWORD)(m->esi + 0xfffffffeu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4643cf: mov byte ptr [esi - 2], al */
	{ DWORD a_ = m->edi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4643d2: cmp edi, 0xff */
	m->eax = m->edi;	/* 4643d8: mov eax, edi */
	if (m->sf != m->of) goto L_4643e1;	/* 4643da: jl 0x4643e1 */
	m->eax = 0xffu;	/* 4643dc: mov eax, 0xff */
L_4643e1:
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4643e1: cmp ecx, 0xff */
	M8((DWORD)(m->esi + 0xffffffffu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4643e7: mov byte ptr [esi - 1], al */
	if (m->sf != m->of) goto L_4643f1;	/* 4643ea: jl 0x4643f1 */
	m->ecx = 0xffu;	/* 4643ec: mov ecx, 0xff */
L_4643f1:
	M8((DWORD)(m->esi + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4643f1: mov byte ptr [esi], cl */
L_4643f3:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4643f3: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->esp + 0x30u));	/* 4643f7: mov edi, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 4643fb: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4643fe: inc eax */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4643ff: add edi, 0xc */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 464402: add esi, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464405: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 464407: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x30u)) = m->edi;	/* 46440b: mov dword ptr [esp + 0x30], edi */
	if (m->sf != m->of) goto L_464240;	/* 46440f: jl 0x464240 */
	goto L_464a2c;	/* 464415: jmp 0x464a2c */
L_46441a:
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46441a: cmp edi, 1 */
	if (!m->zf) goto L_464a2c;	/* 46441d: jne 0x464a2c */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 464423: mov ecx, dword ptr [ebx + 0x4c] */
	m->edi = M32((DWORD)(m->esp + 0x94u));	/* 464426: mov edi, dword ptr [esp + 0x94] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46442d: shl ecx, 2 */
	m->edx = m->ecx;	/* 464430: mov edx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464432: xor eax, eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 464434: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 464437: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 464439: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46443b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 46443e: rep stosb byte ptr es:[edi], al */
	goto L_464a2c;	/* 464440: jmp 0x464a2c */
L_464445:
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464445: cmp esi, ebp */
	if (m->zf) goto L_4644a1;	/* 464447: je 0x4644a1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 464449: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 46444c: fmul dword ptr [ecx + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 46444f: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 464452: fmul dword ptr [ecx + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 464455: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x10u)));	/* 464457: fld dword ptr [ecx + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 46445a: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46445c: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 46445e: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 464461: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 464465: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 464468: fmul dword ptr [ecx + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 46446b: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 46446e: fmul dword ptr [ecx + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 464471: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 464473: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 464476: fmul dword ptr [ecx + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 464479: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 46447b: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 46447e: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 464482: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x18u));	/* 464485: fmul dword ptr [ecx + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 464488: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x14u));	/* 46448b: fmul dword ptr [ecx + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46448e: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 464490: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x10u));	/* 464493: fmul dword ptr [ecx + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 464496: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 464498: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 46449b: fstp dword ptr [esp + 0x44] */
	goto L_4644b9;	/* 46449f: jmp 0x4644b9 */
L_4644a1:
	m->eax = (DWORD)(m->ecx + 0x10u);	/* 4644a1: lea eax, [ecx + 0x10] */
	m->edx = M32((DWORD)(m->ecx + 0x10u));	/* 4644a4: mov edx, dword ptr [ecx + 0x10] */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 4644a7: mov dword ptr [esp + 0x3c], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 4644ab: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 4644ae: mov dword ptr [esp + 0x40], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 4644b2: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 4644b5: mov dword ptr [esp + 0x44], eax */
L_4644b9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x28u)));	/* 4644b9: fld dword ptr [ecx + 0x28] */
	{ long double t = ST(0); FPUSH(t); }	/* 4644bc: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 4644be: fmulp st(1) */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4644c0: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4644c2: xor eax, eax */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xcu))) & 0xff) << 0);	/* 4644c4: mov dl, byte ptr [ecx + 0xc] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xdu))) & 0xff) << 0);	/* 4644c7: mov al, byte ptr [ecx + 0xd] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 4644ca: fst dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa25cu));	/* 4644ce: fmul dword ptr [0x4aa25c] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 4644d4: mov dword ptr [esp + 0x18], edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4644d8: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xeu))) & 0xff) << 0);	/* 4644da: mov dl, byte ptr [ecx + 0xe] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4644dd: mov dword ptr [esp + 0x1c], eax */
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 4644e1: mov eax, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4644e4: cmp edi, 1 */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4644e7: fstp dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 4644eb: mov dword ptr [esp + 0x20], edx */
	M32((DWORD)(m->esp + 0x10u)) = m->ebp;	/* 4644ef: mov dword ptr [esp + 0x10], ebp */
	if (!m->zf) goto L_464724;	/* 4644f3: jne 0x464724 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4644f9: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_464714;	/* 4644fb: jle 0x464714 */
	m->eax = M32((DWORD)(m->esp + 0x94u));	/* 464501: mov eax, dword ptr [esp + 0x94] */
	m->edi = 0xfffffffeu;	/* 464508: mov edi, 0xfffffffe */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 46450d: xor esi, esi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46450f: sub edi, eax */
	m->ecx = (DWORD)(m->eax + 0x2u);	/* 464511: lea ecx, [eax + 2] */
	M32((DWORD)(m->esp + 0x34u)) = m->esi;	/* 464514: mov dword ptr [esp + 0x34], esi */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 464518: mov dword ptr [esp + 0x30], ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->edi;	/* 46451c: mov dword ptr [esp + 0x24], edi */
	goto L_464535;	/* 464520: jmp 0x464535 */
L_464522:
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 464522: mov ecx, dword ptr [esp + 0x30] */
	m->esi = M32((DWORD)(m->esp + 0x34u));	/* 464526: mov esi, dword ptr [esp + 0x34] */
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 46452a: mov edi, dword ptr [esp + 0x24] */
	m->ebx = M32((DWORD)(m->esp + 0x9cu));	/* 46452e: mov ebx, dword ptr [esp + 0x9c] */
L_464535:
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 464535: mov edx, dword ptr [ebx + 0x50] */
	m->eax = m->esi;	/* 464538: mov eax, esi */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46453a: add eax, edx */
	m->edx = M32((DWORD)(m->ebx + 0x58u));	/* 46453c: mov edx, dword ptr [ebx + 0x58] */
	m->ebp = M32((DWORD)(m->ebx + 0x54u));	/* 46453f: mov ebp, dword ptr [ebx + 0x54] */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 464542: add edi, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 464544: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 464546: fsub dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46454a: add edi, edx */
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46454c: add esi, ebp */
	MF((DWORD)(m->esp + 0x78u)) = (float)ST(0); FPOP();	/* 46454e: fstp dword ptr [esp + 0x78] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 464552: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 464555: fsub dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0); FPOP();	/* 464559: fstp dword ptr [esp + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 46455d: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 464560: fsub dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x78u));	/* 464564: mov eax, dword ptr [esp + 0x78] */
	m->edx = M32((DWORD)(m->esp + 0x7cu));	/* 464568: mov edx, dword ptr [esp + 0x7c] */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 46456c: mov dword ptr [esp + 0x48], eax */
	M32((DWORD)(m->esp + 0x4cu)) = m->edx;	/* 464570: mov dword ptr [esp + 0x4c], edx */
	MF((DWORD)(m->esp + 0x80u)) = (float)ST(0); FPOP();	/* 464574: fstp dword ptr [esp + 0x80] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 46457b: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x80u));	/* 464582: fmul dword ptr [esp + 0x80] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 464589: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x7cu));	/* 46458d: fmul dword ptr [esp + 0x7c] */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 464591: mov eax, dword ptr [esp + 0x80] */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 464598: mov dword ptr [esp + 0x50], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46459c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 46459e: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 4645a2: fmul dword ptr [esp + 0x78] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4645a6: faddp st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4645a8: fst dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x2cu)); FPOP();	/* 4645ac: fcomp dword ptr [esp + 0x2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4645b0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4645b2: test ah, 1 */
	if (m->zf) goto L_4646d9;	/* 4645b5: je 0x4646d9 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4645bb: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u)); FPOP();	/* 4645bf: fcomp dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4645c3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4645c5: test ah, 0x41 */
	if (!m->zf) goto L_464676;	/* 4645c8: jne 0x464676 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4645ce: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 4645d2: fmul dword ptr [0x4aa260] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 4645d8: fdiv dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4645dc: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4645e1: cmp eax, 0x100 */
	if (m->zf || m->sf != m->of) goto L_4645ed;	/* 4645e6: jle 0x4645ed */
	m->eax = 0x100u;	/* 4645e8: mov eax, 0x100 */
L_4645ed:
	m->ebx = m->eax;	/* 4645ed: mov ebx, eax */
	m->ebp = m->eax;	/* 4645ef: mov ebp, eax */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 4645f1: imul eax, dword ptr [esp + 0x20] */
	{ long long p_ = (long long)(int)m->ebx * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebx = r_; }	/* 4645f6: imul ebx, dword ptr [esp + 0x18] */
	{ long long p_ = (long long)(int)m->ebp * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebp = r_; }	/* 4645fb: imul ebp, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 464600: sar eax, 8 */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 464603: lea ecx, [esp + 0x48] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 464607: mov dword ptr [esp + 0x14], eax */
	{ DWORD a_ = m->ebx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 46460b: sar ebx, 8 */
	{ DWORD a_ = m->ebp, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 46460e: sar ebp, 8 */
	m->esp -= 4; M32(m->esp) = 0x464616u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 464611: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 464616: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 464618: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 46461c: fmul dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 46461f: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 464623: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 464626: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 464628: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 46462c: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46462e: faddp st(1) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 464630: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 464636: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 46463c: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464641: test eax, eax */
	if (m->sf == m->of) goto L_464647;	/* 464643: jge 0x464647 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464645: xor eax, eax */
L_464647:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464647: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464649: xor edx, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 46464b: mov cl, byte ptr [edi] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 46464d: mov dl, byte ptr [edi + 1] */
	m->esi = m->ecx;	/* 464650: mov esi, ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464652: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x2u))) & 0xff) << 0);	/* 464654: mov cl, byte ptr [edi + 2] */
	{ long long p_ = (long long)(int)m->esi * (int)m->ebx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 464657: imul esi, ebx */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x14u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 46465a: imul ecx, dword ptr [esp + 0x14] */
	{ long long p_ = (long long)(int)m->edx * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 46465f: imul edx, ebp */
	{ long long p_ = (long long)(int)m->esi * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 464662: imul esi, eax */
	{ long long p_ = (long long)(int)m->edx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 464665: imul edx, eax */
	{ long long p_ = (long long)(int)m->ecx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 464668: imul ecx, eax */
	{ DWORD a_ = m->esi, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46466b: sar esi, 0x10 */
	{ DWORD a_ = m->edx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 46466e: sar edx, 0x10 */
	{ DWORD a_ = m->ecx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 464671: sar ecx, 0x10 */
	goto L_46469e;	/* 464674: jmp 0x46469e */
L_464676:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464676: xor edx, edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464678: xor ecx, ecx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 46467a: mov dl, byte ptr [edi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x2u))) & 0xff) << 0);	/* 46467c: mov cl, byte ptr [edi + 2] */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 46467f: imul ecx, dword ptr [esp + 0x20] */
	m->esi = m->edx;	/* 464684: mov esi, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464686: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x1u))) & 0xff) << 0);	/* 464688: mov dl, byte ptr [edi + 1] */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 46468b: imul esi, dword ptr [esp + 0x18] */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 464690: imul edx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esi, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 464695: sar esi, 8 */
	{ DWORD a_ = m->edx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 464698: sar edx, 8 */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46469b: sar ecx, 8 */
L_46469e:
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46469e: cmp ecx, 0xff */
	if (m->sf != m->of) goto L_4646ab;	/* 4646a4: jl 0x4646ab */
	m->ecx = 0xffu;	/* 4646a6: mov ecx, 0xff */
L_4646ab:
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4646ab: cmp edx, 0xff */
	if (m->sf != m->of) goto L_4646b8;	/* 4646b1: jl 0x4646b8 */
	m->edx = 0xffu;	/* 4646b3: mov edx, 0xff */
L_4646b8:
	{ DWORD a_ = m->esi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4646b8: cmp esi, 0xff */
	m->ebx = m->esi;	/* 4646be: mov ebx, esi */
	if (m->sf != m->of) goto L_4646c7;	/* 4646c0: jl 0x4646c7 */
	m->ebx = 0xffu;	/* 4646c2: mov ebx, 0xff */
L_4646c7:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4646c7: mov eax, dword ptr [esp + 0x30] */
	M8((DWORD)(m->eax + 0xfffffffeu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4646cb: mov byte ptr [eax - 2], bl */
	M8((DWORD)(m->eax + 0xffffffffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 4646ce: mov byte ptr [eax - 1], dl */
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4646d1: mov byte ptr [eax], cl */
	M8((DWORD)(m->eax + 0x1u)) = (BYTE)(0xffu);	/* 4646d3: mov byte ptr [eax + 1], 0xff */
	goto L_4646e5;	/* 4646d7: jmp 0x4646e5 */
L_4646d9:
	m->eax = M32((DWORD)(0xa1f278u));	/* 4646d9: mov eax, dword ptr [0xa1f278] */
	M32((DWORD)(m->ecx + 0xfffffffeu)) = m->eax;	/* 4646de: mov dword ptr [ecx - 2], eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4646e1: mov eax, dword ptr [esp + 0x30] */
L_4646e5:
	m->edx = M32((DWORD)(m->esp + 0x9cu));	/* 4646e5: mov edx, dword ptr [esp + 0x9c] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4646ec: mov ecx, dword ptr [esp + 0x10] */
	m->esi = M32((DWORD)(m->esp + 0x34u));	/* 4646f0: mov esi, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4646f4: add eax, 4 */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 4646f7: mov dword ptr [esp + 0x30], eax */
	m->eax = M32((DWORD)(m->edx + 0x4cu));	/* 4646fb: mov eax, dword ptr [edx + 0x4c] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4646fe: inc ecx */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4646ff: add esi, 0xc */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464702: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 464704: mov dword ptr [esp + 0x10], ecx */
	M32((DWORD)(m->esp + 0x34u)) = m->esi;	/* 464708: mov dword ptr [esp + 0x34], esi */
	if (m->sf != m->of) goto L_464522;	/* 46470c: jl 0x464522 */
	m->ebx = m->edx;	/* 464712: mov ebx, edx */
L_464714:
	M32((DWORD)(m->esp + 0x98u)) = 0x0u;	/* 464714: mov dword ptr [esp + 0x98], 0 */
	goto L_464a2c;	/* 46471f: jmp 0x464a2c */
L_464724:
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464724: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_464a2c;	/* 464726: jle 0x464a2c */
	m->eax = M32((DWORD)(m->esp + 0x94u));	/* 46472c: mov eax, dword ptr [esp + 0x94] */
	m->ebp = 0xfffffffeu;	/* 464733: mov ebp, 0xfffffffe */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 464738: xor ecx, ecx */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46473a: sub ebp, eax */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 46473c: mov dword ptr [esp + 0x34], ecx */
	m->edi = (DWORD)(m->eax + 0x2u);	/* 464740: lea edi, [eax + 2] */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 464743: mov dword ptr [esp + 0x24], ebp */
L_464747:
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 464747: mov edx, dword ptr [ebx + 0x50] */
	m->eax = m->ecx;	/* 46474a: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46474c: add eax, edx */
	m->esi = M32((DWORD)(m->ebx + 0x54u));	/* 46474e: mov esi, dword ptr [ebx + 0x54] */
	m->edx = m->ecx;	/* 464751: mov edx, ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 464753: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 464755: fsub dword ptr [esp + 0x3c] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 464759: add edx, esi */
	m->esi = (DWORD)(m->edi + m->ebp*1 + 0x0u);	/* 46475b: lea esi, [edi + ebp] */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 46475e: mov dword ptr [esp + 0x30], edx */
	m->edx = M32((DWORD)(m->ebx + 0x58u));	/* 464762: mov edx, dword ptr [ebx + 0x58] */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 464765: fstp dword ptr [esp + 0x84] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 46476c: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 46476f: fsub dword ptr [esp + 0x40] */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 464773: add esi, edx */
	MF((DWORD)(m->esp + 0x88u)) = (float)ST(0); FPOP();	/* 464775: fstp dword ptr [esp + 0x88] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 46477c: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 46477f: fsub dword ptr [esp + 0x44] */
	m->eax = M32((DWORD)(m->esp + 0x84u));	/* 464783: mov eax, dword ptr [esp + 0x84] */
	m->edx = M32((DWORD)(m->esp + 0x88u));	/* 46478a: mov edx, dword ptr [esp + 0x88] */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 464791: mov dword ptr [esp + 0x48], eax */
	M32((DWORD)(m->esp + 0x4cu)) = m->edx;	/* 464795: mov dword ptr [esp + 0x4c], edx */
	MF((DWORD)(m->esp + 0x8cu)) = (float)ST(0); FPOP();	/* 464799: fstp dword ptr [esp + 0x8c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8cu)));	/* 4647a0: fld dword ptr [esp + 0x8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x8cu));	/* 4647a7: fmul dword ptr [esp + 0x8c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x88u)));	/* 4647ae: fld dword ptr [esp + 0x88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x88u));	/* 4647b5: fmul dword ptr [esp + 0x88] */
	m->eax = M32((DWORD)(m->esp + 0x8cu));	/* 4647bc: mov eax, dword ptr [esp + 0x8c] */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 4647c3: mov dword ptr [esp + 0x50], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4647c7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 4647c9: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x84u));	/* 4647d0: fmul dword ptr [esp + 0x84] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4647d7: faddp st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4647d9: fst dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x2cu)); FPOP();	/* 4647dd: fcomp dword ptr [esp + 0x2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4647e1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4647e3: test ah, 1 */
	if (m->zf) goto L_464935;	/* 4647e6: je 0x464935 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4647ec: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u)); FPOP();	/* 4647f0: fcomp dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4647f4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4647f6: test ah, 0x41 */
	if (!m->zf) goto L_4648b9;	/* 4647f9: jne 0x4648b9 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4647ff: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 464803: fmul dword ptr [0x4aa260] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 464809: fdiv dword ptr [esp + 0x14] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 46480d: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464812: cmp eax, 0x100 */
	if (m->zf || m->sf != m->of) goto L_46481e;	/* 464817: jle 0x46481e */
	m->eax = 0x100u;	/* 464819: mov eax, 0x100 */
L_46481e:
	m->ebp = m->eax;	/* 46481e: mov ebp, eax */
	m->ebx = m->eax;	/* 464820: mov ebx, eax */
	{ long long p_ = (long long)(int)m->eax * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 464822: imul eax, dword ptr [esp + 0x20] */
	{ long long p_ = (long long)(int)m->ebp * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebp = r_; }	/* 464827: imul ebp, dword ptr [esp + 0x18] */
	{ long long p_ = (long long)(int)m->ebx * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebx = r_; }	/* 46482c: imul ebx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 464831: sar eax, 8 */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 464834: lea ecx, [esp + 0x48] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 464838: mov dword ptr [esp + 0x14], eax */
	{ DWORD a_ = m->ebp, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 46483c: sar ebp, 8 */
	{ DWORD a_ = m->ebx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 46483f: sar ebx, 8 */
	m->esp -= 4; M32(m->esp) = 0x464847u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 464842: call 0x467760 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 464847: mov eax, dword ptr [esp + 0x30] */
	ST(0) = ST(0); FPOP();	/* 46484b: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 46484d: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 464851: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 464854: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 464858: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46485b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 46485d: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 464861: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 464863: faddp st(1) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 464865: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 46486b: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 464871: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 464876: test eax, eax */
	if (m->sf == m->of) goto L_46487c;	/* 464878: jge 0x46487c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46487a: xor eax, eax */
L_46487c:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46487c: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46487e: xor edx, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 464880: mov cl, byte ptr [esi] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0xfffffffeu))) & 0xff) << 0);	/* 464882: mov dl, byte ptr [edi - 2] */
	{ long long p_ = (long long)(int)m->ecx * (int)m->ebp; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 464885: imul ecx, ebp */
	{ long long p_ = (long long)(int)m->ecx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 464888: imul ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46488b: sar ecx, 0x10 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46488e: add ecx, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464890: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 464892: mov dl, byte ptr [esi + 1] */
	{ long long p_ = (long long)(int)m->edx * (int)m->ebx; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 464895: imul edx, ebx */
	{ long long p_ = (long long)(int)m->edx * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 464898: imul edx, eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46489b: xor ebx, ebx */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0xffffffffu))) & 0xff) << 0);	/* 46489d: mov bl, byte ptr [edi - 1] */
	{ DWORD a_ = m->edx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4648a0: sar edx, 0x10 */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4648a3: add edx, ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4648a5: xor ebx, ebx */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x2u))) & 0xff) << 0);	/* 4648a7: mov bl, byte ptr [esi + 2] */
	m->esi = m->ebx;	/* 4648aa: mov esi, ebx */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x14u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 4648ac: imul esi, dword ptr [esp + 0x14] */
	{ long long p_ = (long long)(int)m->esi * (int)m->eax; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 4648b1: imul esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4648b4: sar esi, 0x10 */
	goto L_4648ef;	/* 4648b7: jmp 0x4648ef */
L_4648b9:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4648b9: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4648bb: xor edx, edx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4648bd: mov cl, byte ptr [esi] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0xfffffffeu))) & 0xff) << 0);	/* 4648bf: mov dl, byte ptr [edi - 2] */
	{ long long p_ = (long long)(int)m->ecx * (int)M32((DWORD)(m->esp + 0x18u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 4648c2: imul ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4648c7: sar ecx, 8 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4648ca: add ecx, edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4648cc: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x1u))) & 0xff) << 0);	/* 4648ce: mov dl, byte ptr [esi + 1] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4648d1: xor eax, eax */
	{ long long p_ = (long long)(int)m->edx * (int)M32((DWORD)(m->esp + 0x1cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 4648d3: imul edx, dword ptr [esp + 0x1c] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0xffffffffu))) & 0xff) << 0);	/* 4648d8: mov al, byte ptr [edi - 1] */
	{ DWORD a_ = m->edx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4648db: sar edx, 8 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4648de: add edx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4648e0: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x2u))) & 0xff) << 0);	/* 4648e2: mov al, byte ptr [esi + 2] */
	m->esi = m->eax;	/* 4648e5: mov esi, eax */
	{ long long p_ = (long long)(int)m->esi * (int)M32((DWORD)(m->esp + 0x20u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->esi = r_; }	/* 4648e7: imul esi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->esi, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 4648ec: sar esi, 8 */
L_4648ef:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4648ef: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x0u))) & 0xff) << 0);	/* 4648f1: mov al, byte ptr [edi] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4648f3: add esi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4648f5: cmp ecx, 0xff */
	if (m->sf != m->of) goto L_464902;	/* 4648fb: jl 0x464902 */
	m->ecx = 0xffu;	/* 4648fd: mov ecx, 0xff */
L_464902:
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464902: cmp edx, 0xff */
	M8((DWORD)(m->edi + 0xfffffffeu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 464908: mov byte ptr [edi - 2], cl */
	if (m->sf != m->of) goto L_464912;	/* 46490b: jl 0x464912 */
	m->edx = 0xffu;	/* 46490d: mov edx, 0xff */
L_464912:
	{ DWORD a_ = m->esi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464912: cmp esi, 0xff */
	M8((DWORD)(m->edi + 0xffffffffu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 464918: mov byte ptr [edi - 1], dl */
	m->eax = m->esi;	/* 46491b: mov eax, esi */
	if (m->sf != m->of) goto L_464924;	/* 46491d: jl 0x464924 */
	m->eax = 0xffu;	/* 46491f: mov eax, 0xff */
L_464924:
	m->ebp = M32((DWORD)(m->esp + 0x24u));	/* 464924: mov ebp, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 464928: mov ecx, dword ptr [esp + 0x34] */
	m->ebx = M32((DWORD)(m->esp + 0x9cu));	/* 46492c: mov ebx, dword ptr [esp + 0x9c] */
	M8((DWORD)(m->edi + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 464933: mov byte ptr [edi], al */
L_464935:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 464935: mov eax, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->ebx + 0x4cu));	/* 464939: mov edx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46493c: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46493d: add ecx, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 464940: add edi, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464943: cmp eax, edx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 464945: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 464949: mov dword ptr [esp + 0x34], ecx */
	if (m->sf != m->of) goto L_464747;	/* 46494d: jl 0x464747 */
	goto L_464a2c;	/* 464953: jmp 0x464a2c */
L_464958:
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464958: cmp edi, 1 */
	if (!m->zf) goto L_464984;	/* 46495b: jne 0x464984 */
	m->esi = M32((DWORD)(m->ebx + 0x4cu));	/* 46495d: mov esi, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464960: xor eax, eax */
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464962: cmp esi, ebp */
	if (m->zf || m->sf != m->of) goto L_464978;	/* 464964: jle 0x464978 */
	m->esi = m->edx;	/* 464966: mov esi, edx */
L_464968:
	m->edx = M32((DWORD)(m->ecx + 0xcu));	/* 464968: mov edx, dword ptr [ecx + 0xc] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46496b: inc eax */
	M32((DWORD)(m->esi + 0x0u)) = m->edx;	/* 46496c: mov dword ptr [esi], edx */
	m->edx = M32((DWORD)(m->ebx + 0x4cu));	/* 46496e: mov edx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 464971: add esi, 4 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464974: cmp eax, edx */
	if (m->sf != m->of) goto L_464968;	/* 464976: jl 0x464968 */
L_464978:
	M32((DWORD)(m->esp + 0x98u)) = m->ebp;	/* 464978: mov dword ptr [esp + 0x98], ebp */
	goto L_464a2c;	/* 46497f: jmp 0x464a2c */
L_464984:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464984: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 464986: xor edx, edx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xcu))) & 0xff) << 0);	/* 464988: mov al, byte ptr [ecx + 0xc] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xdu))) & 0xff) << 0);	/* 46498b: mov dl, byte ptr [ecx + 0xd] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 46498e: mov dword ptr [esp + 0x18], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 464992: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + 0xeu))) & 0xff) << 0);	/* 464994: mov al, byte ptr [ecx + 0xe] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 464997: mov dword ptr [esp + 0x1c], edx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 46499b: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 46499f: mov eax, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4649a2: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4649a4: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_464a2c;	/* 4649a6: jle 0x464a2c */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 4649ac: mov ecx, dword ptr [esp + 0x94] */
	m->eax = (DWORD)(m->ecx + 0x2u);	/* 4649b3: lea eax, [ecx + 2] */
L_4649b6:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4649b6: xor ecx, ecx */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 4649b8: mov ebp, dword ptr [esp + 0x1c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xfffffffeu))) & 0xff) << 0);	/* 4649bc: mov cl, byte ptr [eax - 2] */
	m->esi = m->ecx;	/* 4649bf: mov esi, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4649c1: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4649c5: add esi, ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4649c7: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xffffffffu))) & 0xff) << 0);	/* 4649c9: mov cl, byte ptr [eax - 1] */
	m->edi = m->ecx;	/* 4649cc: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4649ce: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 4649d0: mov cl, byte ptr [eax] */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4649d2: add edi, ebp */
	m->ebp = m->ecx;	/* 4649d4: mov ebp, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4649d6: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4649da: add ebp, ecx */
	{ DWORD a_ = m->esi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4649dc: cmp esi, 0xff */
	m->ecx = m->esi;	/* 4649e2: mov ecx, esi */
	if (m->sf != m->of) goto L_4649eb;	/* 4649e4: jl 0x4649eb */
	m->ecx = 0xffu;	/* 4649e6: mov ecx, 0xff */
L_4649eb:
	M8((DWORD)(m->eax + 0xfffffffeu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4649eb: mov byte ptr [eax - 2], cl */
	{ DWORD a_ = m->edi, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4649ee: cmp edi, 0xff */
	m->ecx = m->edi;	/* 4649f4: mov ecx, edi */
	if (m->sf != m->of) goto L_4649fd;	/* 4649f6: jl 0x4649fd */
	m->ecx = 0xffu;	/* 4649f8: mov ecx, 0xff */
L_4649fd:
	M8((DWORD)(m->eax + 0xffffffffu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4649fd: mov byte ptr [eax - 1], cl */
	{ DWORD a_ = m->ebp, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464a00: cmp ebp, 0xff */
	m->ecx = m->ebp;	/* 464a06: mov ecx, ebp */
	if (m->sf != m->of) goto L_464a0f;	/* 464a08: jl 0x464a0f */
	m->ecx = 0xffu;	/* 464a0a: mov ecx, 0xff */
L_464a0f:
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 464a0f: mov byte ptr [eax], cl */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 464a11: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 464a14: inc edx */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 464a15: add eax, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464a18: cmp edx, ecx */
	if (m->sf != m->of) goto L_4649b6;	/* 464a1a: jl 0x4649b6 */
	goto L_464a2c;	/* 464a1c: jmp 0x464a2c */
L_464a1e:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 464a1e: push eax */
	{ DWORD v_ = 0x4c4a4cu; m->esp -= 4; M32(m->esp) = v_; }	/* 464a1f: push 0x4c4a4c */
	m->esp -= 4; M32(m->esp) = 0x464a29u; native_call(m, 0x46c950u);	/* 464a24: call 0x46c950 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464a29: add esp, 8 */
L_464a2c:
	m->edx = M32((DWORD)(m->esp + 0xa0u));	/* 464a2c: mov edx, dword ptr [esp + 0xa0] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 464a33: mov eax, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 464a37: inc eax */
	m->ecx = M32((DWORD)(m->edx + 0xb004u));	/* 464a38: mov ecx, dword ptr [edx + 0xb004] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 464a3e: mov dword ptr [esp + 0x38], eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 464a42: cmp eax, ecx */
	if (m->sf != m->of) goto L_463c06;	/* 464a44: jl 0x463c06 */
	m->esi = M32(m->esp); m->esp += 4;	/* 464a4a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 464a4b: pop ebp */
L_464a4c:
	m->edi = M32(m->esp); m->esp += 4;	/* 464a4c: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 464a4d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 464a4e: add esp, 0x80 */
	m->esp += 4 + 0; return;	/* 464a54: ret  */
}

/* FUN_00466910 (0x466910), lifted by tools/lift.py */
static void lift_466910(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466910: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 466911: mov ebx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466915: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 466916: xor esi, esi */
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 466918: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46691b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_46695b;	/* 46691d: jle 0x46695b */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46691f: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 466920: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 466924: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 466925: xor edi, edi */
L_466927:
	m->eax = M32((DWORD)(m->ebx + 0x14u));	/* 466927: mov eax, dword ptr [ebx + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 46692a: mov ecx, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 46692e: mov edx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 466932: add eax, edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 466934: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466935: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 466936: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46693a: push eax */
	m->eax = M32((DWORD)(m->eax + 0x48u));	/* 46693b: mov eax, dword ptr [eax + 0x48] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46693e: push edx */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 46693f: lea edx, [ecx + eax*4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466942: push edx */
	m->esp -= 4; M32(m->esp) = 0x466948u; lift_463b80(m);	/* 466943: call 0x463b80 */
	m->eax = M32((DWORD)(m->ebx + 0x10u));	/* 466948: mov eax, dword ptr [ebx + 0x10] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46694b: add esp, 0x14 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 46694e: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46694f: add edi, 0x80 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466955: cmp esi, eax */
	if (m->sf != m->of) goto L_466927;	/* 466957: jl 0x466927 */
	m->edi = M32(m->esp); m->esp += 4;	/* 466959: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46695a: pop ebp */
L_46695b:
	m->esi = M32(m->esp); m->esp += 4;	/* 46695b: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46695c: pop ebx */
	m->esp += 4 + 0; return;	/* 46695d: ret  */
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
