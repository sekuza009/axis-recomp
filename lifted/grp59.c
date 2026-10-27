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

static void lift_460cb0(X86 *m);

/* app_requireCd (0x460cb0), lifted by tools/lift.py */
static void lift_460cb0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460cb0: sub esp, 0xc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 460cb3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 460cb4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 460cb5: push esi */
	m->ebx = m->ecx;	/* 460cb6: mov ebx, ecx */
	m->esp -= 4; M32(m->esp) = 0x460cbdu; native_call(m, 0x401000u);	/* 460cb8: call 0x401000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 460cbd: test eax, eax */
	if (!m->zf) goto L_460cd4;	/* 460cbf: jne 0x460cd4 */
	m->eax = M32((DWORD)(0x4b4568u));	/* 460cc1: mov eax, dword ptr [0x4b4568] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 460cc6: push eax */
	{ DWORD v_ = 0xa0e778u; m->esp -= 4; M32(m->esp) = v_; }	/* 460cc7: push 0xa0e778 */
	m->esp -= 4; M32(m->esp) = 0x460cd1u; native_call(m, 0x46c710u);	/* 460ccc: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 460cd1: add esp, 8 */
L_460cd4:
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 460cd4: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 460cd8: mov edx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->ebx + 0x4u)) = m->ecx;	/* 460cdc: mov dword ptr [ebx + 4], ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 460cdf: xor ebp, ebp */
	M32((DWORD)(m->ebx + 0x8u)) = m->edx;	/* 460ce1: mov dword ptr [ebx + 8], edx */
	M32((DWORD)(m->ebx + 0x1f1664u)) = m->ebp;	/* 460ce4: mov dword ptr [ebx + 0x1f1664], ebp */
	M32((DWORD)(m->ebx + 0x1f1ca8u)) = m->ebp;	/* 460cea: mov dword ptr [ebx + 0x1f1ca8], ebp */
	M32((DWORD)(m->ebx + 0x1f1cacu)) = m->ebp;	/* 460cf0: mov dword ptr [ebx + 0x1f1cac], ebp */
	M32((DWORD)(m->ebx + 0x1f1cb0u)) = m->ebp;	/* 460cf6: mov dword ptr [ebx + 0x1f1cb0], ebp */
	M32((DWORD)(m->ebx + 0x233c9e8u)) = m->ebp;	/* 460cfc: mov dword ptr [ebx + 0x233c9e8], ebp */
	M32((DWORD)(m->ebx + 0x233c9ecu)) = m->ebp;	/* 460d02: mov dword ptr [ebx + 0x233c9ec], ebp */
	M32((DWORD)(m->ebx + 0x233c9f0u)) = m->ebp;	/* 460d08: mov dword ptr [ebx + 0x233c9f0], ebp */
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 460d0e: mov eax, dword ptr [ebx + 8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 460d11: push edi */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460d12: cmp eax, 3 */
	M32((DWORD)(m->ebx + 0x1f35bcu)) = m->ebp;	/* 460d15: mov dword ptr [ebx + 0x1f35bc], ebp */
	if (!m->zf) goto L_460d8d;	/* 460d1b: jne 0x460d8d */
	m->eax = M32((DWORD)(0x9eeab8u));	/* 460d1d: mov eax, dword ptr [0x9eeab8] */
	M32((DWORD)(m->esp + 0x20u)) = m->ebp;	/* 460d22: mov dword ptr [esp + 0x20], ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460d26: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_460d8d;	/* 460d28: jle 0x460d8d */
	m->edi = 0x9dda88u;	/* 460d2a: mov edi, 0x9dda88 */
	M32((DWORD)(m->esp + 0x24u)) = m->edi;	/* 460d2f: mov dword ptr [esp + 0x24], edi */
L_460d33:
	{ DWORD a_ = M32((DWORD)(m->edi + 0x40u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460d33: cmp dword ptr [edi + 0x40], 1 */
	if (!m->zf) goto L_460d73;	/* 460d37: jne 0x460d73 */
	m->eax = M32((DWORD)(m->ebx + 0x1f35bcu));	/* 460d39: mov eax, dword ptr [ebx + 0x1f35bc] */
	m->ecx = m->eax;	/* 460d3f: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 460d41: shl ecx, 6 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 460d44: inc eax */
	m->edx = (DWORD)(m->ecx + m->ebx*1 + 0x1f1cbcu);	/* 460d45: lea edx, [ecx + ebx + 0x1f1cbc] */
	M32((DWORD)(m->ebx + 0x1f35bcu)) = m->eax;	/* 460d4c: mov dword ptr [ebx + 0x1f35bc], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 460d52: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 460d55: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 460d57: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 460d59: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 460d5b: sub edi, ecx */
	m->eax = m->ecx;	/* 460d5d: mov eax, ecx */
	m->esi = m->edi;	/* 460d5f: mov esi, edi */
	m->edi = m->edx;	/* 460d61: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 460d63: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 460d66: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 460d68: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 460d6a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 460d6d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 460d6f: mov edi, dword ptr [esp + 0x24] */
L_460d73:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 460d73: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(0x9eeab8u));	/* 460d77: mov ecx, dword ptr [0x9eeab8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 460d7d: inc eax */
	{ DWORD a_ = m->edi, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 460d7e: add edi, 0x44 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460d81: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 460d83: mov dword ptr [esp + 0x20], eax */
	M32((DWORD)(m->esp + 0x24u)) = m->edi;	/* 460d87: mov dword ptr [esp + 0x24], edi */
	if (m->sf != m->of) goto L_460d33;	/* 460d8b: jl 0x460d33 */
L_460d8d:
	m->esi = (DWORD)(m->ebx + 0x1f36c8u);	/* 460d8d: lea esi, [ebx + 0x1f36c8] */
	M32((DWORD)(m->ebx + 0x1f35c0u)) = m->ebp;	/* 460d93: mov dword ptr [ebx + 0x1f35c0], ebp */
	m->ecx = m->esi;	/* 460d99: mov ecx, esi */
	M32((DWORD)(m->ebx + 0x1f35c4u)) = m->ebp;	/* 460d9b: mov dword ptr [ebx + 0x1f35c4], ebp */
	m->esp -= 4; M32(m->esp) = 0x460da6u; native_call(m, 0x470a70u);	/* 460da1: call 0x470a70 */
	m->ecx = m->esi;	/* 460da6: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x460dadu; native_call(m, 0x470ad0u);	/* 460da8: call 0x470ad0 */
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 460dad: mov eax, dword ptr [ebx + 8] */
	m->edi = 0x2u;	/* 460db0: mov edi, 2 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 460db5: cmp eax, edi */
	if (!m->zf) goto L_460e4b;	/* 460db7: jne 0x460e4b */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 460dbd: push ebp */
	m->ecx = m->esi;	/* 460dbe: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x460dc5u; native_call(m, 0x45dfe0u);	/* 460dc0: call 0x45dfe0 */
	m->eax = 0xc7c35000u;	/* 460dc5: mov eax, 0xc7c35000 */
	M32((DWORD)(m->ebx + 0x2221f9cu)) = m->ebp;	/* 460dca: mov dword ptr [ebx + 0x2221f9c], ebp */
	M32((DWORD)(m->ebx + 0xbe2fccu)) = m->eax;	/* 460dd0: mov dword ptr [ebx + 0xbe2fcc], eax */
	M32((DWORD)(m->ebx + 0xbe2fd0u)) = m->eax;	/* 460dd6: mov dword ptr [ebx + 0xbe2fd0], eax */
	M32((DWORD)(m->ebx + 0xbe2fd4u)) = m->eax;	/* 460ddc: mov dword ptr [ebx + 0xbe2fd4], eax */
	m->eax = 0x47c35000u;	/* 460de2: mov eax, 0x47c35000 */
	M32((DWORD)(m->ebx + 0xbe2fd8u)) = m->eax;	/* 460de7: mov dword ptr [ebx + 0xbe2fd8], eax */
	M32((DWORD)(m->ebx + 0xbe2fdcu)) = m->eax;	/* 460ded: mov dword ptr [ebx + 0xbe2fdc], eax */
	M32((DWORD)(m->ebx + 0xbe2fe0u)) = m->eax;	/* 460df3: mov dword ptr [ebx + 0xbe2fe0], eax */
	m->edx = M32((DWORD)(m->ebx + 0xbe2fccu));	/* 460df9: mov edx, dword ptr [ebx + 0xbe2fcc] */
	m->ecx = (DWORD)(m->ebx + 0xbe2fe4u);	/* 460dff: lea ecx, [ebx + 0xbe2fe4] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 460e05: push ebp */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 460e06: mov dword ptr [ecx], edx */
	m->eax = M32((DWORD)(m->ebx + 0xbe2fd0u));	/* 460e08: mov eax, dword ptr [ebx + 0xbe2fd0] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 460e0e: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(m->ebx + 0xbe2fd4u));	/* 460e11: mov edx, dword ptr [ebx + 0xbe2fd4] */
	m->eax = (DWORD)(m->ebx + 0xbe2ff0u);	/* 460e17: lea eax, [ebx + 0xbe2ff0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 460e1d: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->ebx + 0xbe2fd8u));	/* 460e20: mov ecx, dword ptr [ebx + 0xbe2fd8] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 460e26: mov dword ptr [eax], ecx */
	m->edx = M32((DWORD)(m->ebx + 0xbe2fdcu));	/* 460e28: mov edx, dword ptr [ebx + 0xbe2fdc] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 460e2e: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(m->ebx + 0xbe2fe0u));	/* 460e31: mov ecx, dword ptr [ebx + 0xbe2fe0] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 460e37: mov dword ptr [eax + 8], ecx */
	m->ecx = m->esi;	/* 460e3a: mov ecx, esi */
	M32((DWORD)(m->ebx + 0xbe2ffcu)) = 0x3f800000u;	/* 460e3c: mov dword ptr [ebx + 0xbe2ffc], 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x460e4bu; native_call(m, 0x4732f0u);	/* 460e46: call 0x4732f0 */
L_460e4b:
	M32((DWORD)(m->ebx + 0x233c9fcu)) = m->ebp;	/* 460e4b: mov dword ptr [ebx + 0x233c9fc], ebp */
	M32((DWORD)(m->ebx + 0x233ca00u)) = m->ebp;	/* 460e51: mov dword ptr [ebx + 0x233ca00], ebp */
	m->eax = M32((DWORD)(0xa0e7a8u));	/* 460e57: mov eax, dword ptr [0xa0e7a8] */
	m->edx = (DWORD)(m->ebx + 0x233ca04u);	/* 460e5c: lea edx, [ebx + 0x233ca04] */
	M32((DWORD)(m->ebx + 0x233ca04u)) = m->eax;	/* 460e62: mov dword ptr [ebx + 0x233ca04], eax */
	m->ecx = M32((DWORD)(0xa0e7acu));	/* 460e68: mov ecx, dword ptr [0xa0e7ac] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 460e6e: mov dword ptr [edx + 4], ecx */
	m->eax = M32((DWORD)(0xa0e7b0u));	/* 460e71: mov eax, dword ptr [0xa0e7b0] */
	m->ecx = (DWORD)(m->ebx + 0x233ca10u);	/* 460e76: lea ecx, [ebx + 0x233ca10] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 460e7c: mov dword ptr [edx + 8], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7c8u)));	/* 460e7f: fld dword ptr [0xa0e7c8] */
	ST(0) = -ST(0);	/* 460e85: fchs  */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 460e87: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7ccu)));	/* 460e8b: fld dword ptr [0xa0e7cc] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 460e91: mov edx, dword ptr [esp + 0x10] */
	ST(0) = -ST(0);	/* 460e95: fchs  */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 460e97: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7d0u)));	/* 460e9b: fld dword ptr [0xa0e7d0] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 460ea1: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 460ea5: mov dword ptr [ecx], edx */
	ST(0) = -ST(0);	/* 460ea7: fchs  */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 460ea9: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 460ead: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 460eb1: mov dword ptr [ecx + 4], eax */
	m->eax = (DWORD)(m->ebx + 0x233ca1cu);	/* 460eb4: lea eax, [ebx + 0x233ca1c] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 460eba: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(0xa0e7d8u));	/* 460ebd: mov ecx, dword ptr [0xa0e7d8] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 460ec3: mov dword ptr [eax], ecx */
	m->edx = M32((DWORD)(0xa0e7dcu));	/* 460ec5: mov edx, dword ptr [0xa0e7dc] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 460ecb: mov dword ptr [eax + 4], edx */
	m->ecx = M32((DWORD)(0xa0e7e0u));	/* 460ece: mov ecx, dword ptr [0xa0e7e0] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 460ed4: mov dword ptr [eax + 8], ecx */
	M32((DWORD)(m->ebx + 0x233ca28u)) = m->ebp;	/* 460ed7: mov dword ptr [ebx + 0x233ca28], ebp */
	M32((DWORD)(m->ebx + 0x233ca2cu)) = m->ebp;	/* 460edd: mov dword ptr [ebx + 0x233ca2c], ebp */
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 460ee3: mov eax, dword ptr [ebx + 8] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 460ee6: sub eax, edi */
	if (m->zf) goto L_460f01;	/* 460ee8: je 0x460f01 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 460eea: dec eax */
	if (m->zf) goto L_460ef5;	/* 460eeb: je 0x460ef5 */
	M32((DWORD)(m->ebx + 0x233cc20u)) = m->edi;	/* 460eed: mov dword ptr [ebx + 0x233cc20], edi */
	goto L_460f0b;	/* 460ef3: jmp 0x460f0b */
L_460ef5:
	M32((DWORD)(m->ebx + 0x233cc20u)) = 0x1u;	/* 460ef5: mov dword ptr [ebx + 0x233cc20], 1 */
	goto L_460f0b;	/* 460eff: jmp 0x460f0b */
L_460f01:
	M32((DWORD)(m->ebx + 0x233cc20u)) = 0x3u;	/* 460f01: mov dword ptr [ebx + 0x233cc20], 3 */
L_460f0b:
	M32((DWORD)(m->ebx + 0x233cc28u)) = m->ebp;	/* 460f0b: mov dword ptr [ebx + 0x233cc28], ebp */
	M32((DWORD)(m->ebx + 0x233cc30u)) = m->ebp;	/* 460f11: mov dword ptr [ebx + 0x233cc30], ebp */
	M32((DWORD)(m->ebx + 0x233cc34u)) = m->ebp;	/* 460f17: mov dword ptr [ebx + 0x233cc34], ebp */
	M32((DWORD)(m->ebx + 0x233cc40u)) = m->ebp;	/* 460f1d: mov dword ptr [ebx + 0x233cc40], ebp */
	M32((DWORD)(m->ebx + 0x233cc44u)) = m->ebp;	/* 460f23: mov dword ptr [ebx + 0x233cc44], ebp */
	M32((DWORD)(m->ebx + 0x233cc50u)) = 0x43960000u;	/* 460f29: mov dword ptr [ebx + 0x233cc50], 0x43960000 */
	M32((DWORD)(m->ebx + 0x233cc54u)) = 0x40400000u;	/* 460f33: mov dword ptr [ebx + 0x233cc54], 0x40400000 */
	M32((DWORD)(m->ebx + 0x233cc58u)) = 0x40a00000u;	/* 460f3d: mov dword ptr [ebx + 0x233cc58], 0x40a00000 */
	M32((DWORD)(m->ebx + 0x233cc5cu)) = 0x41700000u;	/* 460f47: mov dword ptr [ebx + 0x233cc5c], 0x41700000 */
	M32((DWORD)(m->ebx + 0x2340ca4u)) = m->ebp;	/* 460f51: mov dword ptr [ebx + 0x2340ca4], ebp */
	M32((DWORD)(m->ebx + 0x2340ca8u)) = m->ebp;	/* 460f57: mov dword ptr [ebx + 0x2340ca8], ebp */
	M32((DWORD)(m->ebx + 0x2340cacu)) = m->ebp;	/* 460f5d: mov dword ptr [ebx + 0x2340cac], ebp */
	M32((DWORD)(m->ebx + 0x2340cb0u)) = m->ebp;	/* 460f63: mov dword ptr [ebx + 0x2340cb0], ebp */
	M32((DWORD)(m->ebx + 0x2340cb4u)) = m->ebp;	/* 460f69: mov dword ptr [ebx + 0x2340cb4], ebp */
	M32((DWORD)(m->ebx + 0x2340cb8u)) = m->ebp;	/* 460f6f: mov dword ptr [ebx + 0x2340cb8], ebp */
	M32((DWORD)(m->ebx + 0x2340cbcu)) = m->ebp;	/* 460f75: mov dword ptr [ebx + 0x2340cbc], ebp */
	M32((DWORD)(m->ebx + 0x2340cc0u)) = m->ebp;	/* 460f7b: mov dword ptr [ebx + 0x2340cc0], ebp */
	M32((DWORD)(m->ebx + 0x2340cc4u)) = m->ebp;	/* 460f81: mov dword ptr [ebx + 0x2340cc4], ebp */
	M32((DWORD)(m->ebx + 0x2340cc8u)) = m->ebp;	/* 460f87: mov dword ptr [ebx + 0x2340cc8], ebp */
	M32((DWORD)(m->ebx + 0x2340cccu)) = m->ebp;	/* 460f8d: mov dword ptr [ebx + 0x2340ccc], ebp */
	M32((DWORD)(m->ebx + 0x2340cd0u)) = 0x1u;	/* 460f93: mov dword ptr [ebx + 0x2340cd0], 1 */
	M32((DWORD)(m->ebx + 0x2340cd4u)) = m->ebp;	/* 460f9d: mov dword ptr [ebx + 0x2340cd4], ebp */
	M32((DWORD)(m->ebx + 0x2340cd8u)) = m->ebp;	/* 460fa3: mov dword ptr [ebx + 0x2340cd8], ebp */
	M32((DWORD)(m->ebx + 0x2340cdcu)) = m->ebp;	/* 460fa9: mov dword ptr [ebx + 0x2340cdc], ebp */
	M32((DWORD)(m->ebx + 0x2340ce0u)) = m->ebp;	/* 460faf: mov dword ptr [ebx + 0x2340ce0], ebp */
	M32((DWORD)(m->ebx + 0x2340ce4u)) = m->ebp;	/* 460fb5: mov dword ptr [ebx + 0x2340ce4], ebp */
	M32((DWORD)(m->ebx + 0x2340ce8u)) = m->ebp;	/* 460fbb: mov dword ptr [ebx + 0x2340ce8], ebp */
	M32((DWORD)(m->ebx + 0x2340cecu)) = m->ebp;	/* 460fc1: mov dword ptr [ebx + 0x2340cec], ebp */
	M32((DWORD)(m->ebx + 0x2340cf0u)) = m->ebp;	/* 460fc7: mov dword ptr [ebx + 0x2340cf0], ebp */
	M32((DWORD)(m->ebx + 0x2340cf4u)) = m->ebp;	/* 460fcd: mov dword ptr [ebx + 0x2340cf4], ebp */
	M32((DWORD)(m->ebx + 0x2340cf8u)) = m->ebp;	/* 460fd3: mov dword ptr [ebx + 0x2340cf8], ebp */
	M32((DWORD)(m->ebx + 0x2340cfcu)) = m->ebp;	/* 460fd9: mov dword ptr [ebx + 0x2340cfc], ebp */
	M32((DWORD)(m->ebx + 0x2340d00u)) = m->ebp;	/* 460fdf: mov dword ptr [ebx + 0x2340d00], ebp */
	M32((DWORD)(m->ebx + 0x2340d04u)) = m->ebp;	/* 460fe5: mov dword ptr [ebx + 0x2340d04], ebp */
	M32((DWORD)(m->ebx + 0x2340d1du)) = m->ebp;	/* 460feb: mov dword ptr [ebx + 0x2340d1d], ebp */
	M32((DWORD)(m->ebx + 0x2340d21u)) = m->ebp;	/* 460ff1: mov dword ptr [ebx + 0x2340d21], ebp */
	M32((DWORD)(m->ebx + 0x2340d25u)) = m->ebp;	/* 460ff7: mov dword ptr [ebx + 0x2340d25], ebp */
	M32((DWORD)(m->ebx + 0x2340d29u)) = m->ebp;	/* 460ffd: mov dword ptr [ebx + 0x2340d29], ebp */
	M32((DWORD)(m->ebx + 0x2340d2du)) = m->ebp;	/* 461003: mov dword ptr [ebx + 0x2340d2d], ebp */
	M32((DWORD)(m->ebx + 0x2340d31u)) = m->ebp;	/* 461009: mov dword ptr [ebx + 0x2340d31], ebp */
	m->ecx = m->ebx;	/* 46100f: mov ecx, ebx */
	M32((DWORD)(m->ebx + 0x2340d35u)) = m->ebp;	/* 461011: mov dword ptr [ebx + 0x2340d35], ebp */
	m->esp -= 4; M32(m->esp) = 0x46101cu; native_call(m, 0x4636d0u);	/* 461017: call 0x4636d0 */
	M32((DWORD)(m->ebx + 0x2342395u)) = m->ebp;	/* 46101c: mov dword ptr [ebx + 0x2342395], ebp */
	M32((DWORD)(m->ebx + 0x2342399u)) = m->ebp;	/* 461022: mov dword ptr [ebx + 0x2342399], ebp */
	{ DWORD a_ = m->esi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 461028: or esi, 0xffffffff */
	M32((DWORD)(m->ebx + 0x234239du)) = m->ebp;	/* 46102b: mov dword ptr [ebx + 0x234239d], ebp */
	M32((DWORD)(m->ebx + 0x23423a1u)) = m->ebp;	/* 461031: mov dword ptr [ebx + 0x23423a1], ebp */
	M32((DWORD)(m->ebx + 0x23423a5u)) = m->ebp;	/* 461037: mov dword ptr [ebx + 0x23423a5], ebp */
	M32((DWORD)(m->ebx + 0x23423a9u)) = m->ebp;	/* 46103d: mov dword ptr [ebx + 0x23423a9], ebp */
	M32((DWORD)(m->ebx + 0x23423adu)) = m->ebp;	/* 461043: mov dword ptr [ebx + 0x23423ad], ebp */
	M32((DWORD)(m->ebx + 0x23423b1u)) = m->ebp;	/* 461049: mov dword ptr [ebx + 0x23423b1], ebp */
	M32((DWORD)(m->ebx + 0x23423b5u)) = m->esi;	/* 46104f: mov dword ptr [ebx + 0x23423b5], esi */
	M32((DWORD)(m->ebx + 0x23423c9u)) = m->ebp;	/* 461055: mov dword ptr [ebx + 0x23423c9], ebp */
	M32((DWORD)(m->ebx + 0x23423cdu)) = m->ebp;	/* 46105b: mov dword ptr [ebx + 0x23423cd], ebp */
	M32((DWORD)(m->ebx + 0x23423d1u)) = m->ebp;	/* 461061: mov dword ptr [ebx + 0x23423d1], ebp */
	M32((DWORD)(m->ebx + 0x23423d5u)) = m->ebp;	/* 461067: mov dword ptr [ebx + 0x23423d5], ebp */
	M32((DWORD)(m->ebx + 0x23423d9u)) = m->ebp;	/* 46106d: mov dword ptr [ebx + 0x23423d9], ebp */
	M32((DWORD)(m->ebx + 0x23423ddu)) = m->ebp;	/* 461073: mov dword ptr [ebx + 0x23423dd], ebp */
	M32((DWORD)(m->ebx + 0x23423e1u)) = m->ebp;	/* 461079: mov dword ptr [ebx + 0x23423e1], ebp */
	M32((DWORD)(m->ebx + 0x23423fdu)) = m->ebp;	/* 46107f: mov dword ptr [ebx + 0x23423fd], ebp */
	M32((DWORD)(m->ebx + 0x2342409u)) = m->ebp;	/* 461085: mov dword ptr [ebx + 0x2342409], ebp */
	M32((DWORD)(m->ebx + 0x234325fu)) = m->ebp;	/* 46108b: mov dword ptr [ebx + 0x234325f], ebp */
	M32((DWORD)(m->ebx + 0x2343263u)) = m->ebp;	/* 461091: mov dword ptr [ebx + 0x2343263], ebp */
	M32((DWORD)(m->ebx + 0x2343267u)) = m->ebp;	/* 461097: mov dword ptr [ebx + 0x2343267], ebp */
	M32((DWORD)(m->ebx + 0x234326bu)) = m->ebp;	/* 46109d: mov dword ptr [ebx + 0x234326b], ebp */
	M32((DWORD)(m->ebx + 0x234326fu)) = m->ebp;	/* 4610a3: mov dword ptr [ebx + 0x234326f], ebp */
	M32((DWORD)(m->ebx + 0x2343273u)) = m->ebp;	/* 4610a9: mov dword ptr [ebx + 0x2343273], ebp */
	M32((DWORD)(m->ebx + 0x2343277u)) = m->ebp;	/* 4610af: mov dword ptr [ebx + 0x2343277], ebp */
	M32((DWORD)(m->ebx + 0x234327bu)) = m->ebp;	/* 4610b5: mov dword ptr [ebx + 0x234327b], ebp */
	M32((DWORD)(m->ebx + 0x234327fu)) = m->ebp;	/* 4610bb: mov dword ptr [ebx + 0x234327f], ebp */
	M32((DWORD)(m->ebx + 0x2343283u)) = m->ebp;	/* 4610c1: mov dword ptr [ebx + 0x2343283], ebp */
	M32((DWORD)(m->ebx + 0x2343287u)) = m->esi;	/* 4610c7: mov dword ptr [ebx + 0x2343287], esi */
	M32((DWORD)(m->ebx + 0x234328bu)) = m->ebp;	/* 4610cd: mov dword ptr [ebx + 0x234328b], ebp */
	M32((DWORD)(m->ebx + 0x234328fu)) = m->ebp;	/* 4610d3: mov dword ptr [ebx + 0x234328f], ebp */
	M32((DWORD)(m->ebx + 0x2343293u)) = m->ebp;	/* 4610d9: mov dword ptr [ebx + 0x2343293], ebp */
	M32((DWORD)(m->ebx + 0x2343297u)) = m->ebp;	/* 4610df: mov dword ptr [ebx + 0x2343297], ebp */
	M32((DWORD)(m->ebx + 0x234329bu)) = m->ebp;	/* 4610e5: mov dword ptr [ebx + 0x234329b], ebp */
	M32((DWORD)(m->ebx + 0x234329fu)) = m->ebp;	/* 4610eb: mov dword ptr [ebx + 0x234329f], ebp */
	M32((DWORD)(m->ebx + 0x23432a3u)) = m->ebp;	/* 4610f1: mov dword ptr [ebx + 0x23432a3], ebp */
	M32((DWORD)(m->ebx + 0x23432a7u)) = m->ebp;	/* 4610f7: mov dword ptr [ebx + 0x23432a7], ebp */
	M32((DWORD)(m->ebx + 0x23432abu)) = m->ebp;	/* 4610fd: mov dword ptr [ebx + 0x23432ab], ebp */
	M32((DWORD)(m->ebx + 0x23432afu)) = m->ebp;	/* 461103: mov dword ptr [ebx + 0x23432af], ebp */
	M32((DWORD)(m->ebx + 0x23432b3u)) = m->ebp;	/* 461109: mov dword ptr [ebx + 0x23432b3], ebp */
	M32((DWORD)(m->ebx + 0x23432b7u)) = m->ebp;	/* 46110f: mov dword ptr [ebx + 0x23432b7], ebp */
	M32((DWORD)(m->ebx + 0x23432bbu)) = m->ebp;	/* 461115: mov dword ptr [ebx + 0x23432bb], ebp */
	M32((DWORD)(m->ebx + 0x23432bfu)) = m->ebp;	/* 46111b: mov dword ptr [ebx + 0x23432bf], ebp */
	M32((DWORD)(m->ebx + 0x23432c3u)) = m->ebp;	/* 461121: mov dword ptr [ebx + 0x23432c3], ebp */
	M32((DWORD)(m->ebx + 0x23432c7u)) = m->ebp;	/* 461127: mov dword ptr [ebx + 0x23432c7], ebp */
	M32((DWORD)(m->ebx + 0x23432cbu)) = m->ebp;	/* 46112d: mov dword ptr [ebx + 0x23432cb], ebp */
	M32((DWORD)(m->ebx + 0x23432cfu)) = m->ebp;	/* 461133: mov dword ptr [ebx + 0x23432cf], ebp */
	M32((DWORD)(m->ebx + 0x23432d3u)) = m->ebp;	/* 461139: mov dword ptr [ebx + 0x23432d3], ebp */
	M32((DWORD)(m->ebx + 0x23432d7u)) = m->ebp;	/* 46113f: mov dword ptr [ebx + 0x23432d7], ebp */
	M32((DWORD)(m->ebx + 0x23432dbu)) = m->ebp;	/* 461145: mov dword ptr [ebx + 0x23432db], ebp */
	M32((DWORD)(m->ebx + 0x23432dfu)) = m->ebp;	/* 46114b: mov dword ptr [ebx + 0x23432df], ebp */
	M32((DWORD)(m->ebx + 0x23432e3u)) = m->ebp;	/* 461151: mov dword ptr [ebx + 0x23432e3], ebp */
	M32((DWORD)(m->ebx + 0x23432e7u)) = m->ebp;	/* 461157: mov dword ptr [ebx + 0x23432e7], ebp */
	M32((DWORD)(m->ebx + 0x23432ebu)) = m->ebp;	/* 46115d: mov dword ptr [ebx + 0x23432eb], ebp */
	M32((DWORD)(m->ebx + 0x23432efu)) = m->ebp;	/* 461163: mov dword ptr [ebx + 0x23432ef], ebp */
	M32((DWORD)(m->ebx + 0x23432f3u)) = m->ebp;	/* 461169: mov dword ptr [ebx + 0x23432f3], ebp */
	M32((DWORD)(m->ebx + 0x23432f7u)) = m->ebp;	/* 46116f: mov dword ptr [ebx + 0x23432f7], ebp */
	M32((DWORD)(m->ebx + 0x23432fbu)) = m->ebp;	/* 461175: mov dword ptr [ebx + 0x23432fb], ebp */
	M32((DWORD)(m->ebx + 0x23432ffu)) = m->ebp;	/* 46117b: mov dword ptr [ebx + 0x23432ff], ebp */
	M32((DWORD)(m->ebx + 0x2343303u)) = m->ebp;	/* 461181: mov dword ptr [ebx + 0x2343303], ebp */
	M32((DWORD)(m->ebx + 0x234330bu)) = m->ebp;	/* 461187: mov dword ptr [ebx + 0x234330b], ebp */
	M32((DWORD)(m->ebx + 0x234330fu)) = m->ebp;	/* 46118d: mov dword ptr [ebx + 0x234330f], ebp */
	M32((DWORD)(m->ebx + 0x2343313u)) = m->ebp;	/* 461193: mov dword ptr [ebx + 0x2343313], ebp */
	m->ecx = m->ebx;	/* 461199: mov ecx, ebx */
	M32((DWORD)(m->ebx + 0x2343317u)) = m->ebp;	/* 46119b: mov dword ptr [ebx + 0x2343317], ebp */
	m->esp -= 4; M32(m->esp) = 0x4611a6u; native_call(m, 0x463480u);	/* 4611a1: call 0x463480 */
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 4611a6: mov eax, dword ptr [ebx + 8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4611a9: pop edi */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4611aa: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_4611be;	/* 4611ad: ja 0x4611be */
	switch (m->eax) { case 0: goto L_4611be; case 1: goto L_4611b6; case 2: goto L_4611be; case 3: goto L_4611b6; default: abort(); }	/* 4611af: jmp dword ptr [eax*4 + 0x4611f4] */
L_4611b6:
	M32((DWORD)(m->ebx + 0x234240du)) = m->esi;	/* 4611b6: mov dword ptr [ebx + 0x234240d], esi */
	goto L_4611c4;	/* 4611bc: jmp 0x4611c4 */
L_4611be:
	M32((DWORD)(m->ebx + 0x234240du)) = m->ebp;	/* 4611be: mov dword ptr [ebx + 0x234240d], ebp */
L_4611c4:
	M32((DWORD)(m->ebx + 0x2342411u)) = m->ebp;	/* 4611c4: mov dword ptr [ebx + 0x2342411], ebp */
	M32((DWORD)(m->ebx + 0x2342415u)) = m->ebp;	/* 4611ca: mov dword ptr [ebx + 0x2342415], ebp */
	M32((DWORD)(m->ebx + 0x2342419u)) = m->ebp;	/* 4611d0: mov dword ptr [ebx + 0x2342419], ebp */
	M32((DWORD)(m->ebx + 0x234241du)) = m->esi;	/* 4611d6: mov dword ptr [ebx + 0x234241d], esi */
	M32((DWORD)(m->ebx + 0x2342421u)) = m->ebp;	/* 4611dc: mov dword ptr [ebx + 0x2342421], ebp */
	M32((DWORD)(m->ebx + 0x2343253u)) = m->ebp;	/* 4611e2: mov dword ptr [ebx + 0x2343253], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 4611e8: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4611e9: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4611ea: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4611eb: add esp, 0xc */
	m->esp += 4 + 8; return;	/* 4611ee: ret 8 */
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
