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

static void lift_479b40(X86 *m);

/* bullet_init (0x479b40), lifted by tools/lift.py */
static void lift_479b40(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 479b40: push ebp */
	m->ebp = m->esp;	/* 479b41: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 479b43: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x14cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479b46: sub esp, 0x14c */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 479b4c: mov eax, dword ptr [ebp + 8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 479b4f: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 479b50: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 479b51: push edi */
	m->edi = M32((DWORD)(m->ebp + 0x18u));	/* 479b52: mov edi, dword ptr [ebp + 0x18] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 479b55: lea edx, [eax + eax*4] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 479b58: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 479b5b: sub edx, eax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 479b5d: mov dword ptr [esp + 0x30], ecx */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 479b61: lea eax, [eax + edx*4] */
	m->edx = M32((DWORD)(m->edi + 0x4u));	/* 479b64: mov edx, dword ptr [edi + 4] */
	m->esi = (DWORD)(m->ecx + m->eax*8 + 0x202ef34u);	/* 479b67: lea esi, [ecx + eax*8 + 0x202ef34] */
	m->eax = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 479b6e: lea eax, [edx + edx*8] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 479b71: lea eax, [edx + eax*4] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 479b74: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 479b77: sub eax, edx */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 479b79: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x14d1ab4u);	/* 479b7c: lea eax, [ecx + edx*8 + 0x14d1ab4] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 479b83: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(m->ebp + 0xcu));	/* 479b87: mov eax, dword ptr [ebp + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 479b8a: test eax, eax */
	if (m->sf != m->of) goto L_479b92;	/* 479b8c: jl 0x479b92 */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 479b8e: mov dword ptr [esi], eax */
	goto L_479ba7;	/* 479b90: jmp 0x479ba7 */
L_479b92:
	m->edx = M32((DWORD)(m->ecx + 0x20a99bcu));	/* 479b92: mov edx, dword ptr [ecx + 0x20a99bc] */
	M32((DWORD)(m->esi + 0x0u)) = m->edx;	/* 479b98: mov dword ptr [esi], edx */
	m->eax = M32((DWORD)(m->ecx + 0x20a99bcu));	/* 479b9a: mov eax, dword ptr [ecx + 0x20a99bc] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 479ba0: inc eax */
	M32((DWORD)(m->ecx + 0x20a99bcu)) = m->eax;	/* 479ba1: mov dword ptr [ecx + 0x20a99bc], eax */
L_479ba7:
	m->ecx = M32((DWORD)(m->ebp + 0x10u));	/* 479ba7: mov ecx, dword ptr [ebp + 0x10] */
	M32((DWORD)(m->esi + 0x4u)) = 0x1u;	/* 479baa: mov dword ptr [esi + 4], 1 */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 479bb1: mov eax, dword ptr [edi + 4] */
	m->ebx = (DWORD)(m->edi + 0x8u);	/* 479bb4: lea ebx, [edi + 8] */
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 479bb7: mov dword ptr [esi + 8], eax */
	M32((DWORD)(m->esi + 0xcu)) = m->ecx;	/* 479bba: mov dword ptr [esi + 0xc], ecx */
	m->edx = M32((DWORD)(m->edi + 0x24u));	/* 479bbd: mov edx, dword ptr [edi + 0x24] */
	m->ecx = m->ebx;	/* 479bc0: mov ecx, ebx */
	M32((DWORD)(m->esi + 0x10u)) = m->edx;	/* 479bc2: mov dword ptr [esi + 0x10], edx */
	m->eax = (DWORD)(m->esi + 0x54u);	/* 479bc5: lea eax, [esi + 0x54] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 479bc8: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 479bca: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 479bcc: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 479bcf: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 479bd2: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 479bd5: mov dword ptr [eax + 8], ecx */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 479bd8: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 479bda: test eax, eax */
	m->eax = (DWORD)(m->edi + 0x18u);	/* 479bdc: lea eax, [edi + 0x18] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 479bdf: mov dword ptr [esp + 0x4c], eax */
	if (!m->zf) goto L_479fb0;	/* 479be3: jne 0x479fb0 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 479be9: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 479beb: mov dword ptr [esp + 0x10], edx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 479bef: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 479bf2: mov dword ptr [esp + 0x14], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 479bf6: mov ecx, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 479bfa: mov edx, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 479bfd: mov dword ptr [esp + 0x18], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2decu)));	/* 479c01: fld dword ptr [ecx + 0x2dec] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 479c07: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 479c0d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 479c0f: test ah, 0x41 */
	if (!m->zf) goto L_479d0b;	/* 479c12: jne 0x479d0b */
	m->eax = M32((DWORD)(m->ebp + 0x10u));	/* 479c18: mov eax, dword ptr [ebp + 0x10] */
	m->edx = m->eax;	/* 479c1b: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 479c1d: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 479c20: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 479c22: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 479c25: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 479c27: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 479c2a: add edx, eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 479c2c: mov eax, dword ptr [esp + 0x30] */
	FPUSH((long double)(int)M32((DWORD)(m->eax + m->edx*8 + 0x1cd93ccu)));	/* 479c30: fild dword ptr [eax + edx*8 + 0x1cd93cc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 479c37: fmul dword ptr [0x4a9418] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ecx + 0x2decu));	/* 479c3d: fsubr dword ptr [ecx + 0x2dec] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa448u));	/* 479c43: fmul dword ptr [0x4aa448] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 479c49: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 479c4f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 479c51: test ah, 1 */
	if (m->zf) goto L_479c5e;	/* 479c54: je 0x479c5e */
	ST(0) = ST(0); FPOP();	/* 479c56: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 479c58: fld dword ptr [0x4a93e8] */
L_479c5e:
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 479c5e: mov ecx, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 479c64: xor edx, edx */
	{ DWORD a_ = m->ecx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 479c66: and ecx, 0xfff */
	m->eax = M32((DWORD)(m->ecx*4 + 0xa106f8u));	/* 479c6c: mov eax, dword ptr [ecx*4 + 0xa106f8] */
	m->ecx = 0x64u;	/* 479c73: mov ecx, 0x64 */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 479c78: div ecx */
	m->eax = M32((DWORD)(0xa1efb8u));	/* 479c7a: mov eax, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 479c7f: inc eax */
	M32((DWORD)(0xa1efb8u)) = m->eax;	/* 479c80: mov dword ptr [0xa1efb8], eax */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479c85: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 479c8a: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 479c91: add edx, -0x32 */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 479c94: mov dword ptr [esp + 0x2c], edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 479c98: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 479c9a: div ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 479c9c: fild dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 479ca0: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 479ca2: fadd dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 479ca6: fstp dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(0xa1efb8u));	/* 479caa: mov eax, dword ptr [0xa1efb8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 479caf: inc eax */
	M32((DWORD)(0xa1efb8u)) = m->eax;	/* 479cb0: mov dword ptr [0xa1efb8], eax */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479cb5: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 479cba: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 479cc1: add edx, -0x32 */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 479cc4: mov dword ptr [esp + 0x2c], edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 479cc8: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 479cca: div ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 479ccc: fild dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 479cd0: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 479cd2: fadd dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 479cd6: fstp dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(0xa1efb8u));	/* 479cda: mov eax, dword ptr [0xa1efb8] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 479cdf: lea ecx, [esp + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 479ce3: inc eax */
	M32((DWORD)(0xa1efb8u)) = m->eax;	/* 479ce4: mov dword ptr [0xa1efb8], eax */
	{ DWORD a_ = m->edx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 479ce9: add edx, -0x32 */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 479cec: mov dword ptr [esp + 0x2c], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 479cf0: fild dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 479cf4: fmul st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 479cf6: fadd dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 479cfa: fstp dword ptr [esp + 0x18] */
	ST(0) = ST(0); FPOP();	/* 479cfe: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x479d05u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 479d00: call 0x467760 */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 479d05: mov ecx, dword ptr [esp + 0x28] */
	ST(0) = ST(0); FPOP();	/* 479d09: fstp st(0) */
L_479d0b:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x2dfcu)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479d0b: cmp dword ptr [ecx + 0x2dfc], 3 */
	if (!m->zf) goto L_479e76;	/* 479d12: jne 0x479e76 */
	m->esp -= 4; M32(m->esp) = 0x479d1eu; native_call(m, M32(0x4a9204u));	/* 479d18: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x479d24u; native_call(m, M32(0x4a9218u));	/* 479d1e: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 479d24: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 479d28: fadd dword ptr [ebx] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 479d2a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 479d2c: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 479d2e: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 479d33: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 479d35: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 479d37: push 0 */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 479d39: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 479d3d: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 479d41: fadd dword ptr [ebx + 4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479d44: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479d47: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479d4a: sub esp, 8 */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 479d4d: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 479d51: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 479d55: fadd dword ptr [ebx + 8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479d58: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479d5b: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479d5e: sub esp, 8 */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 479d61: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 479d65: fld dword ptr [esp + 0x60] */
	MDBL((DWORD)(m->esp + 0x28u)) = (double)ST(0); FPOP();	/* 479d69: fstp qword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 479d6d: fld dword ptr [esp + 0x5c] */
	MDBL((DWORD)(m->esp + 0x20u)) = (double)ST(0); FPOP();	/* 479d71: fstp qword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 479d75: fld dword ptr [esp + 0x58] */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 479d79: fstp qword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x10u)));	/* 479d7d: fld dword ptr [edi + 0x10] */
	MDBL((DWORD)(m->esp + 0x10u)) = (double)ST(0); FPOP();	/* 479d80: fstp qword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xcu)));	/* 479d84: fld dword ptr [edi + 0xc] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 479d87: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 479d8b: fld dword ptr [ebx] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 479d8d: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x479d95u; native_call(m, 0x4509d2u);	/* 479d90: call 0x4509d2 */
	m->edx = (DWORD)(m->esp + 0x118u);	/* 479d95: lea edx, [esp + 0x118] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 479d9c: push edx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 479d9d: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x479da8u; native_call(m, M32(0x4a9270u));	/* 479da2: call dword ptr [0x4a9270] */
	m->eax = (DWORD)(m->esp + 0x118u);	/* 479da8: lea eax, [esp + 0x118] */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 479daf: lea ecx, [esp + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 479db3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 479db4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x479dbau; native_call(m, 0x47d740u);	/* 479db5: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479dba: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x479dc3u; native_call(m, M32(0x4a9258u));	/* 479dbd: call dword ptr [0x4a9258] */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 479dc3: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0xe10u;	/* 479dc9: mov edi, 0xe10 */
	m->edx = m->ecx;	/* 479dce: mov edx, ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 479dd0: mov dword ptr [esp + 0x34], 0 */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 479dd8: and edx, 0xfff */
	M32((DWORD)(m->esp + 0x38u)) = 0x3e10d068u;	/* 479dde: mov dword ptr [esp + 0x38], 0x3e10d068 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f7d6d5du;	/* 479de6: mov dword ptr [esp + 0x3c], 0x3f7d6d5d */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 479dee: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 479df5: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 479df7: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 479df9: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 479dfa: mov dword ptr [0xa1efb8], ecx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 479e00: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 479e04: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 479e05: push 0 */
	m->esp -= 4; M32(m->esp) = 0x479e0cu; native_call(m, 0x4677c0u);	/* 479e07: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 479e0c: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x7cu));	/* 479e10: fmul dword ptr [esp + 0x7c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 479e14: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x6cu));	/* 479e18: fmul dword ptr [esp + 0x6c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 479e1c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 479e1e: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 479e22: fmul dword ptr [esp + 0x34] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 479e26: faddp st(1) */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 479e28: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 479e2c: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 479e33: fmul dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 479e37: fld dword ptr [esp + 0x70] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 479e3b: fmul dword ptr [esp + 0x38] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 479e3f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 479e41: fld dword ptr [esp + 0x60] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 479e45: fmul dword ptr [esp + 0x34] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 479e49: faddp st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 479e4b: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 479e4f: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 479e56: fmul dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 479e5a: fld dword ptr [esp + 0x74] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 479e5e: fmul dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 479e62: mov ecx, dword ptr [esp + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 479e66: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 479e68: fld dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 479e6c: fmul dword ptr [esp + 0x34] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 479e70: faddp st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 479e72: fstp dword ptr [esp + 0x18] */
L_479e76:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2de4u)));	/* 479e76: fld dword ptr [ecx + 0x2de4] */
	{ long double t = ST(0); FPUSH(t); }	/* 479e7c: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 479e7e: fmul dword ptr [esp + 0x10] */
	m->edi = (DWORD)(m->esi + 0x54u);	/* 479e82: lea edi, [esi + 0x54] */
	m->eax = (DWORD)(m->esi + 0x60u);	/* 479e85: lea eax, [esi + 0x60] */
	m->ecx = m->eax;	/* 479e88: mov ecx, eax */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 479e8a: fstp dword ptr [esp + 0x50] */
	{ long double t = ST(0); FPUSH(t); }	/* 479e8e: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 479e90: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 479e94: fstp dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 479e98: fmul dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 479e9c: fld dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 479ea0: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 479ea2: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 479ea6: fld dword ptr [esp + 0x54] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 479eaa: fadd dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 479ead: mov edx, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 479eb1: fstp dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 479eb5: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 479eb8: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 479eba: mov edx, dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 479ebe: fstp dword ptr [esp + 0x24] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 479ec2: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 479ec5: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 479ec9: mov dword ptr [ecx + 8], edx */
	m->ecx = (DWORD)(m->esp + 0x40u);	/* 479ecc: lea ecx, [esp + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 479ed0: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 479ed1: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 479ed5: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 479ed6: push edi */
	m->esp -= 4; M32(m->esp) = 0x479edcu; native_call(m, 0x471740u);	/* 479ed7: call 0x471740 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 479edc: xor edx, edx */
	M32((DWORD)(m->esi + 0x6cu)) = m->eax;	/* 479ede: mov dword ptr [esi + 0x6c], eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479ee1: cmp eax, edx */
	if (m->zf) goto L_479f59;	/* 479ee3: je 0x479f59 */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 479ee5: mov ecx, dword ptr [esp + 0x40] */
	m->eax = (DWORD)(m->esi + 0x60u);	/* 479ee9: lea eax, [esi + 0x60] */
	M32((DWORD)(m->esi + 0x60u)) = m->ecx;	/* 479eec: mov dword ptr [esi + 0x60], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 479eef: mov ecx, dword ptr [esp + 0x44] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 479ef3: mov dword ptr [eax + 4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x48u));	/* 479ef6: mov ecx, dword ptr [esp + 0x48] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 479efa: mov dword ptr [eax + 8], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 479efd: mov ecx, dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2de8u)));	/* 479f01: fld dword ptr [ecx + 0x2de8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 479f07: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 479f0d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 479f0f: test ah, 0x41 */
	if (!m->zf) goto L_479f81;	/* 479f12: jne 0x479f81 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 479f14: fld dword ptr [esp + 0x40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 479f18: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 479f1a: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 479f1e: fld dword ptr [esp + 0x44] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 479f22: fsub dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0);	/* 479f25: fst dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 479f29: fld dword ptr [esp + 0x48] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 479f2d: fsub dword ptr [edi + 8] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0);	/* 479f30: fst dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 479f34: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 479f38: fmul dword ptr [esp + 0x40] */
	{ long double t = ST(1); FPUSH(t); }	/* 479f3c: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 479f3e: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 479f40: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 479f42: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 479f44: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 479f46: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 479f48: fsqrt  */
	ST(2) = ST(0); FPOP();	/* 479f4a: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 479f4c: fstp st(0) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ecx + 0x2de8u));	/* 479f4e: fdiv dword ptr [ecx + 0x2de8] */
	MF((DWORD)(m->esi + 0x74u)) = (float)ST(0); FPOP();	/* 479f54: fstp dword ptr [esi + 0x74] */
	goto L_479f84;	/* 479f57: jmp 0x479f84 */
L_479f59:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 479f59: mov ecx, dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2de8u)));	/* 479f5d: fld dword ptr [ecx + 0x2de8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 479f63: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 479f69: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 479f6b: test ah, 0x41 */
	if (!m->zf) goto L_479f81;	/* 479f6e: jne 0x479f81 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2de4u)));	/* 479f70: fld dword ptr [ecx + 0x2de4] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ecx + 0x2de8u));	/* 479f76: fdiv dword ptr [ecx + 0x2de8] */
	MF((DWORD)(m->esi + 0x74u)) = (float)ST(0); FPOP();	/* 479f7c: fstp dword ptr [esi + 0x74] */
	goto L_479f84;	/* 479f7f: jmp 0x479f84 */
L_479f81:
	M32((DWORD)(m->esi + 0x74u)) = m->edx;	/* 479f81: mov dword ptr [esi + 0x74], edx */
L_479f84:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x74u)));	/* 479f84: fld dword ptr [esi + 0x74] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 479f87: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 479f8d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 479f8f: test ah, 1 */
	if (!m->zf) goto L_479fa8;	/* 479f92: jne 0x479fa8 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x74u)));	/* 479f94: fld dword ptr [esi + 0x74] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 479f97: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 479f9d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 479f9f: test ah, 0x41 */
	if (!m->zf) goto L_47a038;	/* 479fa2: jne 0x47a038 */
L_479fa8:
	M32((DWORD)(m->esi + 0x74u)) = m->edx;	/* 479fa8: mov dword ptr [esi + 0x74], edx */
	goto L_47a038;	/* 479fab: jmp 0x47a038 */
L_479fb0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 479fb0: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 479fb2: fsub dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 479fb4: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 479fb8: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 479fbb: fsub dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 479fbe: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 479fc2: mov dword ptr [esp + 0x10], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 479fc6: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 479fca: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 479fcd: fsub dword ptr [ebx + 8] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 479fd0: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 479fd4: mov dword ptr [esp + 0x14], eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 479fd8: fstp dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 479fdc: mov ecx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 479fe0: mov dword ptr [esp + 0x18], ecx */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 479fe4: lea ecx, [esp + 0x10] */
	m->esp -= 4; M32(m->esp) = 0x479fedu; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 479fe8: call 0x467760 */
	m->edi = M32((DWORD)(m->edi + 0x14u));	/* 479fed: mov edi, dword ptr [edi + 0x14] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 479ff0: test edi, edi */
	ST(0) = ST(0); FPOP();	/* 479ff2: fstp st(0) */
	if (m->sf != m->of) goto L_47a011;	/* 479ff4: jl 0x47a011 */
	m->edx = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 479ff6: lea edx, [edi + edi*4] */
	m->eax = (DWORD)(m->edi + m->edx*4 + 0x0u);	/* 479ff9: lea eax, [edi + edx*4] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 479ffc: mov edx, dword ptr [esp + 0x30] */
	m->ecx = (DWORD)(m->edi + m->eax*2 + 0x0u);	/* 47a000: lea ecx, [edi + eax*2] */
	m->eax = M32((DWORD)(m->edx + 0xa24u));	/* 47a003: mov eax, dword ptr [edx + 0xa24] */
	m->ecx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 47a009: lea ecx, [eax + ecx*4] */
	M32((DWORD)(m->esi + 0x6cu)) = m->ecx;	/* 47a00c: mov dword ptr [esi + 0x6c], ecx */
	goto L_47a018;	/* 47a00f: jmp 0x47a018 */
L_47a011:
	M32((DWORD)(m->esi + 0x6cu)) = 0x0u;	/* 47a011: mov dword ptr [esi + 0x6c], 0 */
L_47a018:
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 47a018: mov edx, dword ptr [esp + 0x4c] */
	m->eax = (DWORD)(m->esi + 0x60u);	/* 47a01c: lea eax, [esi + 0x60] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 47a01f: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47a021: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 47a023: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 47a026: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47a029: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esi + 0x74u)) = 0x41200000u;	/* 47a02c: mov dword ptr [esi + 0x74], 0x41200000 */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 47a033: mov dword ptr [eax + 8], edx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47a036: xor edx, edx */
L_47a038:
	m->edi = (DWORD)(m->esi + 0x78u);	/* 47a038: lea edi, [esi + 0x78] */
	m->eax = m->ebx;	/* 47a03b: mov eax, ebx */
	M32((DWORD)(m->esi + 0x70u)) = m->edx;	/* 47a03d: mov dword ptr [esi + 0x70], edx */
	m->ecx = m->edi;	/* 47a040: mov ecx, edi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47a042: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47a044: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47a046: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47a049: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47a04c: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47a04f: mov dword ptr [ecx + 8], eax */
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 47a052: mov edx, dword ptr [ebx] */
	m->ecx = (DWORD)(m->esi + 0x84u);	/* 47a054: lea ecx, [esi + 0x84] */
	M32((DWORD)(m->esi + 0x84u)) = m->edx;	/* 47a05a: mov dword ptr [esi + 0x84], edx */
	m->eax = M32((DWORD)(m->ebx + 0x4u));	/* 47a060: mov eax, dword ptr [ebx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47a063: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(m->ebx + 0x8u));	/* 47a066: mov edx, dword ptr [ebx + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47a069: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 47a06c: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47a070: xor edx, edx */
	M32((DWORD)(m->esi + 0x9cu)) = m->edx;	/* 47a072: mov dword ptr [esi + 0x9c], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2de8u)));	/* 47a078: fld dword ptr [ecx + 0x2de8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47a07e: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47a084: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47a086: test ah, 0x41 */
	if (!m->zf) goto L_47a0c6;	/* 47a089: jne 0x47a0c6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2de8u)));	/* 47a08b: fld dword ptr [ecx + 0x2de8] */
	{ long double t = ST(0); FPUSH(t); }	/* 47a091: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47a093: fmul dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->esi + 0xa0u);	/* 47a097: lea eax, [esi + 0xa0] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47a09d: fstp dword ptr [esp + 0x1c] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 47a0a1: mov ebx, dword ptr [esp + 0x1c] */
	{ long double t = ST(0); FPUSH(t); }	/* 47a0a5: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 47a0a7: fmul dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 47a0ab: mov dword ptr [eax], ebx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47a0ad: fstp dword ptr [esp + 0x20] */
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 47a0b1: mov ebx, dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47a0b5: fmul dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x4u)) = m->ebx;	/* 47a0b9: mov dword ptr [eax + 4], ebx */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47a0bc: fstp dword ptr [esp + 0x24] */
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 47a0c0: mov ebx, dword ptr [esp + 0x24] */
	goto L_47a0fb;	/* 47a0c4: jmp 0x47a0fb */
L_47a0c6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x60u)));	/* 47a0c6: fld dword ptr [esi + 0x60] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x54u));	/* 47a0c9: fsub dword ptr [esi + 0x54] */
	m->eax = (DWORD)(m->esi + 0xa0u);	/* 47a0cc: lea eax, [esi + 0xa0] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47a0d2: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x64u)));	/* 47a0d6: fld dword ptr [esi + 0x64] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x58u));	/* 47a0d9: fsub dword ptr [esi + 0x58] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 47a0dc: mov ebx, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47a0e0: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 47a0e4: fld dword ptr [esi + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 47a0e7: fsub dword ptr [esi + 0x5c] */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 47a0ea: mov dword ptr [eax], ebx */
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 47a0ec: mov ebx, dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47a0f0: fstp dword ptr [esp + 0x24] */
	M32((DWORD)(m->eax + 0x4u)) = m->ebx;	/* 47a0f4: mov dword ptr [eax + 4], ebx */
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 47a0f7: mov ebx, dword ptr [esp + 0x24] */
L_47a0fb:
	M32((DWORD)(m->eax + 0x8u)) = m->ebx;	/* 47a0fb: mov dword ptr [eax + 8], ebx */
	m->ebx = M32((DWORD)(0xa0e7e8u));	/* 47a0fe: mov ebx, dword ptr [0xa0e7e8] */
	m->eax = (DWORD)(m->esi + 0xacu);	/* 47a104: lea eax, [esi + 0xac] */
	M32((DWORD)(m->esi + 0xacu)) = m->ebx;	/* 47a10a: mov dword ptr [esi + 0xac], ebx */
	m->ebx = M32((DWORD)(0xa0e7ecu));	/* 47a110: mov ebx, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->eax + 0x4u)) = m->ebx;	/* 47a116: mov dword ptr [eax + 4], ebx */
	m->ebx = M32((DWORD)(0xa0e7f0u));	/* 47a119: mov ebx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->esi + 0xb8u)) = 0xffffffffu;	/* 47a11f: mov dword ptr [esi + 0xb8], 0xffffffff */
	M32((DWORD)(m->esi + 0xc0u)) = m->edx;	/* 47a129: mov dword ptr [esi + 0xc0], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ebx;	/* 47a12f: mov dword ptr [eax + 8], ebx */
	m->ebx = M32((DWORD)(m->ebp + 0x14u));	/* 47a132: mov ebx, dword ptr [ebp + 0x14] */
	M32((DWORD)(m->esi + 0xbcu)) = m->ebx;	/* 47a135: mov dword ptr [esi + 0xbc], ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2e0cu)));	/* 47a13b: fld dword ptr [ecx + 0x2e0c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47a141: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47a147: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47a149: test ah, 0x41 */
	if (!m->zf) goto L_47a1c1;	/* 47a14c: jne 0x47a1c1 */
	{ DWORD a_ = m->ebx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a14e: cmp ebx, edx */
	if (m->sf == m->of) goto L_47a1c1;	/* 47a150: jge 0x47a1c1 */
	m->ebx = M32((DWORD)(m->esp + 0x30u));	/* 47a152: mov ebx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 47a156: mov eax, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ebx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a159: cmp eax, dword ptr [ebx + 0x202e8d4] */
	if (!m->zf) goto L_47a1c5;	/* 47a15f: jne 0x47a1c5 */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 47a161: mov eax, dword ptr [esp + 0x4c] */
	m->edx = (DWORD)(m->esi + 0xc4u);	/* 47a165: lea edx, [esi + 0xc4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 47a16b: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa444u));	/* 47a16d: fmul dword ptr [0x4aa444] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 47a173: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa444u));	/* 47a176: fmul dword ptr [0x4aa444] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 47a17c: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 47a180: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa444u));	/* 47a183: fmul dword ptr [0x4aa444] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 47a189: fstp dword ptr [esp + 0x58] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47a18d: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47a18f: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 47a193: fld dword ptr [esp + 0x54] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47a197: fadd dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 47a19a: mov eax, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47a19e: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 47a1a2: fld dword ptr [esp + 0x58] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47a1a6: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47a1a9: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 47a1ab: mov eax, dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47a1af: fstp dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 47a1b3: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 47a1b6: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47a1ba: mov dword ptr [edx + 8], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47a1bd: xor edx, edx */
	goto L_47a1c5;	/* 47a1bf: jmp 0x47a1c5 */
L_47a1c1:
	m->ebx = M32((DWORD)(m->esp + 0x30u));	/* 47a1c1: mov ebx, dword ptr [esp + 0x30] */
L_47a1c5:
	m->eax = M32((DWORD)(m->ebp + 0x1cu));	/* 47a1c5: mov eax, dword ptr [ebp + 0x1c] */
	M32((DWORD)(m->esi + 0xd0u)) = m->edx;	/* 47a1c8: mov dword ptr [esi + 0xd0], edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a1ce: cmp eax, edx */
	M32((DWORD)(m->esi + 0x4e4u)) = m->edx;	/* 47a1d0: mov dword ptr [esi + 0x4e4], edx */
	if (!m->zf) goto L_47a2c1;	/* 47a1d6: jne 0x47a2c1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x2df0u)));	/* 47a1dc: fld dword ptr [ecx + 0x2df0] */
	m->ecx = M32((DWORD)(m->ecx + 0x2dfcu));	/* 47a1e2: mov ecx, dword ptr [ecx + 0x2dfc] */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 47a1e8: mov eax, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->ecx, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47a1eb: add ecx, 0xa */
	M32((DWORD)(m->esp + 0xa0u)) = m->eax;	/* 47a1ee: mov dword ptr [esp + 0xa0], eax */
	M32((DWORD)(m->esp + 0x9cu)) = m->ecx;	/* 47a1f5: mov dword ptr [esp + 0x9c], ecx */
	m->ecx = m->edi;	/* 47a1fc: mov ecx, edi */
	MF((DWORD)(m->esp + 0xc8u)) = (float)ST(0); FPOP();	/* 47a1fe: fstp dword ptr [esp + 0xc8] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 47a205: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0xc0u)) = m->edx;	/* 47a207: mov dword ptr [esp + 0xc0], edx */
	M32((DWORD)(m->esp + 0xa4u)) = m->eax;	/* 47a20e: mov dword ptr [esp + 0xa4], eax */
	M32((DWORD)(m->esp + 0xc4u)) = m->edx;	/* 47a215: mov dword ptr [esp + 0xc4], edx */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 47a21c: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0xccu)) = m->edx;	/* 47a21f: mov dword ptr [esp + 0xcc], edx */
	M32((DWORD)(m->esp + 0xa8u)) = m->eax;	/* 47a226: mov dword ptr [esp + 0xa8], eax */
	m->eax = M32((DWORD)(0xa0e7b8u));	/* 47a22d: mov eax, dword ptr [0xa0e7b8] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 47a232: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0xb0u)) = m->eax;	/* 47a235: mov dword ptr [esp + 0xb0], eax */
	m->eax = M32((DWORD)(0xa0e7c0u));	/* 47a23c: mov eax, dword ptr [0xa0e7c0] */
	M32((DWORD)(m->esp + 0xacu)) = m->ecx;	/* 47a241: mov dword ptr [esp + 0xac], ecx */
	m->ecx = M32((DWORD)(0xa0e7bcu));	/* 47a248: mov ecx, dword ptr [0xa0e7bc] */
	m->edx = (DWORD)(m->esp + 0x9cu);	/* 47a24e: lea edx, [esp + 0x9c] */
	M32((DWORD)(m->esp + 0xb4u)) = m->ecx;	/* 47a255: mov dword ptr [esp + 0xb4], ecx */
	m->ecx = M32((DWORD)(m->esi + 0x10u));	/* 47a25c: mov ecx, dword ptr [esi + 0x10] */
	M32((DWORD)(m->esp + 0xbcu)) = m->ecx;	/* 47a25f: mov dword ptr [esp + 0xbc], ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a266: push edx */
	m->ecx = m->ebx;	/* 47a267: mov ecx, ebx */
	M32((DWORD)(m->esp + 0xbcu)) = m->eax;	/* 47a269: mov dword ptr [esp + 0xbc], eax */
	m->esp -= 4; M32(m->esp) = 0x47a275u; native_call(m, 0x479950u);	/* 47a270: call 0x479950 */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 47a275: mov eax, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->eax + 0x2e00u));	/* 47a279: mov eax, dword ptr [eax + 0x2e00] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47a27f: test eax, eax */
	if (m->sf != m->of) goto L_47a2c1;	/* 47a281: jl 0x47a2c1 */
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 47a283: mov ecx, dword ptr [esi + 0xc] */
	m->edx = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 47a286: mov edx, dword ptr [ebx + 0x202e8d4] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47a28c: cmp ecx, edx */
	if (!m->zf) goto L_47a2a4;	/* 47a28e: jne 0x47a2a4 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a290: push 0x64 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47a292: push eax */
	m->esp -= 4; M32(m->esp) = 0x47a298u; native_call(m, 0x456e50u);	/* 47a293: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a298: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47a29b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47a29c: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47a29d: pop ebx */
	m->esp = m->ebp;	/* 47a29e: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47a2a0: pop ebp */
	m->esp += 4 + 24; return;	/* 47a2a1: ret 0x18 */
L_47a2a4:
	m->edx = (DWORD)(m->ebx + 0x20f397cu);	/* 47a2a4: lea edx, [ebx + 0x20f397c] */
	{ DWORD v_ = 0x47435000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2aa: push 0x47435000 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2af: push edx */
	{ DWORD a_ = m->ebx, b_ = 0x20f3970u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 47a2b0: add ebx, 0x20f3970 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2b6: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2b7: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47a2b8: push eax */
	m->esp -= 4; M32(m->esp) = 0x47a2beu; native_call(m, 0x456ed0u);	/* 47a2b9: call 0x456ed0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47a2be: add esp, 0x14 */
L_47a2c1:
	m->edi = M32(m->esp); m->esp += 4;	/* 47a2c1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47a2c2: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47a2c3: pop ebx */
	m->esp = m->ebp;	/* 47a2c4: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47a2c6: pop ebp */
	m->esp += 4 + 24; return;	/* 47a2c7: ret 0x18 */
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
