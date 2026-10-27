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

static void lift_48ed90(X86 *m);

/* item_update (0x48ed90), lifted by tools/lift.py */
static void lift_48ed90(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ed90: sub esp, 0x18 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed93: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed94: push edi */
	m->edi = m->ecx;	/* 48ed95: mov edi, ecx */
	m->edx = 0x1u;	/* 48ed97: mov edx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ed9c: xor ecx, ecx */
	M32((DWORD)(m->esp + 0xcu)) = m->edi;	/* 48ed9e: mov dword ptr [esp + 0xc], edi */
	m->eax = M32((DWORD)(m->edi + 0x202e8c8u));	/* 48eda2: mov eax, dword ptr [edi + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48eda8: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48edd0;	/* 48edaa: jle 0x48edd0 */
	m->eax = (DWORD)(m->edi + 0x1cd98e4u);	/* 48edac: lea eax, [edi + 0x1cd98e4] */
L_48edb2:
	{ DWORD a_ = M32((DWORD)(m->eax + 0xfffffc10u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48edb2: cmp dword ptr [eax - 0x3f0], edx */
	if (!m->zf) goto L_48edc0;	/* 48edb8: jne 0x48edc0 */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 48edba: mov dword ptr [eax], 0 */
L_48edc0:
	m->esi = M32((DWORD)(m->edi + 0x202e8c8u));	/* 48edc0: mov esi, dword ptr [edi + 0x202e8c8] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48edc6: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48edc7: add eax, 0x8888 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48edcc: cmp ecx, esi */
	if (m->sf != m->of) goto L_48edb2;	/* 48edce: jl 0x48edb2 */
L_48edd0:
	m->ecx = M32((DWORD)(m->edi + 0x20fcd38u));	/* 48edd0: mov ecx, dword ptr [edi + 0x20fcd38] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48edd6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48edd8: test ecx, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 48edda: mov dword ptr [esp + 0x10], eax */
	if (m->zf || m->sf != m->of) goto L_48f849;	/* 48edde: jle 0x48f849 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ede4: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48ede5: push ebp */
L_48ede6:
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48ede6: lea ecx, [eax + eax*4] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48ede9: xor edx, edx */
	m->esi = (DWORD)(m->edi + m->ecx*8 + 0x20fadf8u);	/* 48edeb: lea esi, [edi + ecx*8 + 0x20fadf8] */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 48edf2: mov dword ptr [esp + 0x10], esi */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 48edf6: mov ecx, dword ptr [esi] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48edf8: cmp ecx, edx */
	if (m->sf != m->of) goto L_48f834;	/* 48edfa: jl 0x48f834 */
	m->eax = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 48ee00: lea eax, [ecx + ecx*8] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ee03: shl eax, 4 */
	m->eax = (DWORD)(m->eax + m->edi*1 + 0x20f3ae0u);	/* 48ee06: lea eax, [eax + edi + 0x20f3ae0] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 48ee0d: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->esi + 0x20u));	/* 48ee11: mov eax, dword ptr [esi + 0x20] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ee14: sub eax, edx */
	if (m->zf) goto L_48ee6b;	/* 48ee16: je 0x48ee6b */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48ee18: dec eax */
	if (!m->zf) goto L_48f822;	/* 48ee19: jne 0x48f822 */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 48ee1f: mov ecx, dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 48ee23: fld dword ptr [esi + 0x24] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x48u)); FPOP();	/* 48ee26: fcomp dword ptr [ecx + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48ee29: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48ee2b: test ah, 0x41 */
	if (!m->zf) goto L_48f822;	/* 48ee2e: jne 0x48f822 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48ee34: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x47c35000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ee38: push 0x47c35000 */
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 48ee3d: lea ecx, [esi + 0xc] */
	m->edx = (DWORD)(m->eax + 0x20f397cu);	/* 48ee40: lea edx, [eax + 0x20f397c] */
	{ DWORD a_ = m->eax, b_ = 0x20f3970u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ee46: add eax, 0x20f3970 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ee4b: push edx */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 48ee4c: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ee50: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ee51: push eax */
	m->eax = M32((DWORD)(m->edx + 0x40u));	/* 48ee52: mov eax, dword ptr [edx + 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ee55: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ee5bu; native_call(m, 0x456ed0u);	/* 48ee56: call 0x456ed0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ee5b: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48ee5e: xor eax, eax */
	M32((DWORD)(m->esi + 0x20u)) = m->eax;	/* 48ee60: mov dword ptr [esi + 0x20], eax */
	M32((DWORD)(m->esi + 0x24u)) = m->eax;	/* 48ee63: mov dword ptr [esi + 0x24], eax */
	goto L_48f822;	/* 48ee66: jmp 0x48f822 */
L_48ee6b:
	{ DWORD a_ = m->ecx, b_ = 0x22u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ee6b: cmp ecx, 0x22 */
	if (m->zf) goto L_48ee80;	/* 48ee6e: je 0x48ee80 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 48ee70: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94acu));	/* 48ee74: fmul dword ptr [0x4a94ac] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x1cu));	/* 48ee7a: fadd dword ptr [esi + 0x1c] */
	MF((DWORD)(m->esi + 0x1cu)) = (float)ST(0); FPOP();	/* 48ee7d: fstp dword ptr [esi + 0x1c] */
L_48ee80:
	m->edi = M32((DWORD)(m->edi + 0x202e8c8u));	/* 48ee80: mov edi, dword ptr [edi + 0x202e8c8] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48ee86: xor ebx, ebx */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ee88: cmp edi, edx */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 48ee8a: mov dword ptr [esp + 0x24], edx */
	if (m->zf || m->sf != m->of) goto L_48f822;	/* 48ee8e: jle 0x48f822 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48ee94: mov eax, dword ptr [esp + 0x14] */
	m->ebp = (DWORD)(m->eax + 0x1cd9790u);	/* 48ee98: lea ebp, [eax + 0x1cd9790] */
L_48ee9e:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xfffffd64u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ee9e: cmp dword ptr [ebp - 0x29c], 1 */
	if (!m->zf) goto L_48ef1d;	/* 48eea5: jne 0x48ef1d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xfffffd6cu)));	/* 48eea7: fld dword ptr [ebp - 0x294] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0xcu));	/* 48eead: fsub dword ptr [esi + 0xc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 48eeb0: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48eeb6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48eeb8: test ah, 1 */
	if (m->zf) goto L_48eebf;	/* 48eebb: je 0x48eebf */
	ST(0) = -ST(0);	/* 48eebd: fchs  */
L_48eebf:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x0u)));	/* 48eebf: fld dword ptr [ebp] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a974cu));	/* 48eec2: fmul dword ptr [0x4a974c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 48eec8: fstp dword ptr [esp + 0x1c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu)); FPOP();	/* 48eecc: fcomp dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48eed0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48eed2: test ah, 1 */
	if (m->zf) goto L_48ef1d;	/* 48eed5: je 0x48ef1d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xfffffd70u)));	/* 48eed7: fld dword ptr [ebp - 0x290] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 48eedd: fsub dword ptr [esi + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 48eee0: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48eee6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48eee8: test ah, 1 */
	if (m->zf) goto L_48eeef;	/* 48eeeb: je 0x48eeef */
	ST(0) = -ST(0);	/* 48eeed: fchs  */
L_48eeef:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu)); FPOP();	/* 48eeef: fcomp dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48eef3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48eef5: test ah, 1 */
	if (m->zf) goto L_48ef1d;	/* 48eef8: je 0x48ef1d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xfffffd74u)));	/* 48eefa: fld dword ptr [ebp - 0x28c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 48ef00: fsub dword ptr [esi + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 48ef03: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48ef09: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48ef0b: test ah, 1 */
	if (m->zf) goto L_48ef12;	/* 48ef0e: je 0x48ef12 */
	ST(0) = -ST(0);	/* 48ef10: fchs  */
L_48ef12:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu)); FPOP();	/* 48ef12: fcomp dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48ef16: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48ef18: test ah, 1 */
	if (!m->zf) goto L_48ef31;	/* 48ef1b: jne 0x48ef31 */
L_48ef1d:
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 48ef1d: inc edx */
	{ DWORD a_ = m->ebp, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 48ef1e: add ebp, 0x8888 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ef24: cmp edx, edi */
	if (m->sf != m->of) goto L_48ee9e;	/* 48ef26: jl 0x48ee9e */
	goto L_48f822;	/* 48ef2c: jmp 0x48f822 */
L_48ef31:
	m->eax = 0x66666667u;	/* 48ef31: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 48ef36: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48ef38: sar edx, 2 */
	m->eax = m->edx;	/* 48ef3b: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ef3d: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48ef40: add edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ef42: cmp edx, 3 */
	if (!m->cf && !m->zf) goto L_48f8e0;	/* 48ef45: ja 0x48f8e0 */
	switch (m->edx) { case 0: goto L_48ef52; case 1: goto L_48f1b6; case 2: goto L_48f5cf; case 3: goto L_48f5cf; default: abort(); }	/* 48ef4b: jmp dword ptr [edx*4 + 0x48f8f8] */
L_48ef52:
	m->eax = m->ecx;	/* 48ef52: mov eax, ecx */
	m->edi = 0xau;	/* 48ef54: mov edi, 0xa */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48ef59: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48ef5a: idiv edi */
	{ DWORD a_ = m->edx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ef5c: cmp edx, 5 */
	if (!m->cf && !m->zf) goto L_48f5b7;	/* 48ef5f: ja 0x48f5b7 */
	switch (m->edx) { case 0: goto L_48ef6c; case 1: goto L_48efcc; case 2: goto L_48f02e; case 3: goto L_48f090; case 4: goto L_48f0f2; case 5: goto L_48f154; default: abort(); }	/* 48ef65: jmp dword ptr [edx*4 + 0x48f908] */
L_48ef6c:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48ef6c: test byte ptr [ebp + 8], 0x10 */
	if (!m->zf) goto L_48f822;	/* 48ef70: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd48u));	/* 48ef76: mov esi, dword ptr [ebp - 0x2b8] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc40u));	/* 48ef7c: mov eax, dword ptr [ebp - 0x3c0] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 48ef82: inc esi */
	m->ecx = m->esi;	/* 48ef83: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd48u)) = m->esi;	/* 48ef85: mov dword ptr [ebp - 0x2b8], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ef8b: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48ef95;	/* 48ef8d: jle 0x48ef95 */
	M32((DWORD)(m->ebp + 0xfffffd48u)) = m->eax;	/* 48ef8f: mov dword ptr [ebp - 0x2b8], eax */
L_48ef95:
	m->ecx = 0x4c82f4u;	/* 48ef95: mov ecx, 0x4c82f4 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48ef9a: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48efa0: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48efa2: je 0x48f537 */
	m->edi = m->ecx;	/* 48efa8: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48efaa: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48efad: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48efaf: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48efb1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48efb3: sub edi, ecx */
	m->eax = m->ecx;	/* 48efb5: mov eax, ecx */
	m->esi = m->edi;	/* 48efb7: mov esi, edi */
	m->edi = m->edx;	/* 48efb9: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48efbb: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48efbe: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48efc0: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48efc2: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48efc5: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48efc7: jmp 0x48f53a */
L_48efcc:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48efcc: test byte ptr [ebp + 8], 0x10 */
	if (!m->zf) goto L_48f822;	/* 48efd0: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd48u));	/* 48efd6: mov esi, dword ptr [ebp - 0x2b8] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc40u));	/* 48efdc: mov eax, dword ptr [ebp - 0x3c0] */
	{ DWORD a_ = m->esi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48efe2: add esi, 0x28 */
	m->ecx = m->esi;	/* 48efe5: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd48u)) = m->esi;	/* 48efe7: mov dword ptr [ebp - 0x2b8], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48efed: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48eff7;	/* 48efef: jle 0x48eff7 */
	M32((DWORD)(m->ebp + 0xfffffd48u)) = m->eax;	/* 48eff1: mov dword ptr [ebp - 0x2b8], eax */
L_48eff7:
	m->ecx = 0x4c82e4u;	/* 48eff7: mov ecx, 0x4c82e4 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48effc: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f002: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f004: je 0x48f537 */
	m->edi = m->ecx;	/* 48f00a: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f00c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f00f: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f011: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f013: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f015: sub edi, ecx */
	m->eax = m->ecx;	/* 48f017: mov eax, ecx */
	m->esi = m->edi;	/* 48f019: mov esi, edi */
	m->edi = m->edx;	/* 48f01b: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f01d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f020: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f022: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f024: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f027: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f029: jmp 0x48f53a */
L_48f02e:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x20u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f02e: test byte ptr [ebp + 8], 0x20 */
	if (!m->zf) goto L_48f822;	/* 48f032: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd4cu));	/* 48f038: mov esi, dword ptr [ebp - 0x2b4] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc44u));	/* 48f03e: mov eax, dword ptr [ebp - 0x3bc] */
	{ DWORD a_ = m->esi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f044: add esi, 0x28 */
	m->ecx = m->esi;	/* 48f047: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd4cu)) = m->esi;	/* 48f049: mov dword ptr [ebp - 0x2b4], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f04f: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f059;	/* 48f051: jle 0x48f059 */
	M32((DWORD)(m->ebp + 0xfffffd4cu)) = m->eax;	/* 48f053: mov dword ptr [ebp - 0x2b4], eax */
L_48f059:
	m->ecx = 0x4c82d4u;	/* 48f059: mov ecx, 0x4c82d4 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f05e: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f064: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f066: je 0x48f537 */
	m->edi = m->ecx;	/* 48f06c: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f06e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f071: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f073: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f075: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f077: sub edi, ecx */
	m->eax = m->ecx;	/* 48f079: mov eax, ecx */
	m->esi = m->edi;	/* 48f07b: mov esi, edi */
	m->edi = m->edx;	/* 48f07d: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f07f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f082: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f084: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f086: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f089: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f08b: jmp 0x48f53a */
L_48f090:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f090: test byte ptr [ebp + 8], 0x40 */
	if (!m->zf) goto L_48f822;	/* 48f094: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd50u));	/* 48f09a: mov esi, dword ptr [ebp - 0x2b0] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc48u));	/* 48f0a0: mov eax, dword ptr [ebp - 0x3b8] */
	{ DWORD a_ = m->esi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f0a6: add esi, 0x28 */
	m->ecx = m->esi;	/* 48f0a9: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd50u)) = m->esi;	/* 48f0ab: mov dword ptr [ebp - 0x2b0], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f0b1: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f0bb;	/* 48f0b3: jle 0x48f0bb */
	M32((DWORD)(m->ebp + 0xfffffd50u)) = m->eax;	/* 48f0b5: mov dword ptr [ebp - 0x2b0], eax */
L_48f0bb:
	m->ecx = 0x4c82c0u;	/* 48f0bb: mov ecx, 0x4c82c0 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f0c0: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f0c6: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f0c8: je 0x48f537 */
	m->edi = m->ecx;	/* 48f0ce: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f0d0: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f0d3: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f0d5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f0d7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f0d9: sub edi, ecx */
	m->eax = m->ecx;	/* 48f0db: mov eax, ecx */
	m->esi = m->edi;	/* 48f0dd: mov esi, edi */
	m->edi = m->edx;	/* 48f0df: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f0e1: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f0e4: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f0e6: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f0e8: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f0eb: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f0ed: jmp 0x48f53a */
L_48f0f2:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f0f2: test byte ptr [ebp + 8], 0x80 */
	if (!m->zf) goto L_48f822;	/* 48f0f6: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd54u));	/* 48f0fc: mov esi, dword ptr [ebp - 0x2ac] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc4cu));	/* 48f102: mov eax, dword ptr [ebp - 0x3b4] */
	{ DWORD a_ = m->esi, b_ = 0xfu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f108: add esi, 0xf */
	m->ecx = m->esi;	/* 48f10b: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd54u)) = m->esi;	/* 48f10d: mov dword ptr [ebp - 0x2ac], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f113: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f11d;	/* 48f115: jle 0x48f11d */
	M32((DWORD)(m->ebp + 0xfffffd54u)) = m->eax;	/* 48f117: mov dword ptr [ebp - 0x2ac], eax */
L_48f11d:
	m->ecx = 0x4c82acu;	/* 48f11d: mov ecx, 0x4c82ac */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f122: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f128: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f12a: je 0x48f537 */
	m->edi = m->ecx;	/* 48f130: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f132: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f135: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f137: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f139: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f13b: sub edi, ecx */
	m->eax = m->ecx;	/* 48f13d: mov eax, ecx */
	m->esi = m->edi;	/* 48f13f: mov esi, edi */
	m->edi = m->edx;	/* 48f141: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f143: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f146: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f148: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f14a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f14d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f14f: jmp 0x48f53a */
L_48f154:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f154: test byte ptr [ebp + 8], 0x80 */
	if (!m->zf) goto L_48f822;	/* 48f158: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd54u));	/* 48f15e: mov esi, dword ptr [ebp - 0x2ac] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc4cu));	/* 48f164: mov eax, dword ptr [ebp - 0x3b4] */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f16a: add esi, 5 */
	m->ecx = m->esi;	/* 48f16d: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd54u)) = m->esi;	/* 48f16f: mov dword ptr [ebp - 0x2ac], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f175: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f17f;	/* 48f177: jle 0x48f17f */
	M32((DWORD)(m->ebp + 0xfffffd54u)) = m->eax;	/* 48f179: mov dword ptr [ebp - 0x2ac], eax */
L_48f17f:
	m->ecx = 0x4c8298u;	/* 48f17f: mov ecx, 0x4c8298 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f184: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f18a: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f18c: je 0x48f537 */
	m->edi = m->ecx;	/* 48f192: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f194: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f197: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f199: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f19b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f19d: sub edi, ecx */
	m->eax = m->ecx;	/* 48f19f: mov eax, ecx */
	m->esi = m->edi;	/* 48f1a1: mov esi, edi */
	m->edi = m->edx;	/* 48f1a3: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f1a5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f1a8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f1aa: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f1ac: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f1af: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f1b1: jmp 0x48f53a */
L_48f1b6:
	m->eax = m->ecx;	/* 48f1b6: mov eax, ecx */
	m->edi = 0xau;	/* 48f1b8: mov edi, 0xa */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48f1bd: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48f1be: idiv edi */
	{ DWORD a_ = m->edx, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f1c0: cmp edx, 9 */
	if (!m->cf && !m->zf) goto L_48f5b7;	/* 48f1c3: ja 0x48f5b7 */
	switch (m->edx) { case 0: goto L_48f1d0; case 1: goto L_48f232; case 2: goto L_48f294; case 3: goto L_48f2f6; case 4: goto L_48f358; case 5: goto L_48f3bd; case 6: goto L_48f41f; case 7: goto L_48f481; case 8: goto L_48f4dc; case 9: goto L_48f552; default: abort(); }	/* 48f1c9: jmp dword ptr [edx*4 + 0x48f920] */
L_48f1d0:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f1d0: test byte ptr [ebp + 8], 1 */
	if (!m->zf) goto L_48f822;	/* 48f1d4: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd40u));	/* 48f1da: mov esi, dword ptr [ebp - 0x2c0] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc34u));	/* 48f1e0: mov eax, dword ptr [ebp - 0x3cc] */
	{ DWORD a_ = m->esi, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f1e6: add esi, 0xa */
	m->ecx = m->esi;	/* 48f1e9: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->esi;	/* 48f1eb: mov dword ptr [ebp - 0x2c0], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f1f1: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f1fb;	/* 48f1f3: jle 0x48f1fb */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->eax;	/* 48f1f5: mov dword ptr [ebp - 0x2c0], eax */
L_48f1fb:
	m->ecx = 0x4c828cu;	/* 48f1fb: mov ecx, 0x4c828c */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f200: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f206: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f208: je 0x48f537 */
	m->edi = m->ecx;	/* 48f20e: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f210: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f213: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f215: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f217: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f219: sub edi, ecx */
	m->eax = m->ecx;	/* 48f21b: mov eax, ecx */
	m->esi = m->edi;	/* 48f21d: mov esi, edi */
	m->edi = m->edx;	/* 48f21f: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f221: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f224: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f226: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f228: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f22b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f22d: jmp 0x48f53a */
L_48f232:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f232: test byte ptr [ebp + 8], 1 */
	if (!m->zf) goto L_48f822;	/* 48f236: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd40u));	/* 48f23c: mov esi, dword ptr [ebp - 0x2c0] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc34u));	/* 48f242: mov eax, dword ptr [ebp - 0x3cc] */
	{ DWORD a_ = m->esi, b_ = 0x19u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f248: add esi, 0x19 */
	m->ecx = m->esi;	/* 48f24b: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->esi;	/* 48f24d: mov dword ptr [ebp - 0x2c0], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f253: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f25d;	/* 48f255: jle 0x48f25d */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->eax;	/* 48f257: mov dword ptr [ebp - 0x2c0], eax */
L_48f25d:
	m->ecx = 0x4c8280u;	/* 48f25d: mov ecx, 0x4c8280 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f262: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f268: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f26a: je 0x48f537 */
	m->edi = m->ecx;	/* 48f270: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f272: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f275: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f277: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f279: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f27b: sub edi, ecx */
	m->eax = m->ecx;	/* 48f27d: mov eax, ecx */
	m->esi = m->edi;	/* 48f27f: mov esi, edi */
	m->edi = m->edx;	/* 48f281: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f283: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f286: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f288: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f28a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f28d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f28f: jmp 0x48f53a */
L_48f294:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f294: test byte ptr [ebp + 8], 1 */
	if (!m->zf) goto L_48f822;	/* 48f298: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd40u));	/* 48f29e: mov esi, dword ptr [ebp - 0x2c0] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc34u));	/* 48f2a4: mov eax, dword ptr [ebp - 0x3cc] */
	{ DWORD a_ = m->esi, b_ = 0x32u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f2aa: add esi, 0x32 */
	m->ecx = m->esi;	/* 48f2ad: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->esi;	/* 48f2af: mov dword ptr [ebp - 0x2c0], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f2b5: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f2bf;	/* 48f2b7: jle 0x48f2bf */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->eax;	/* 48f2b9: mov dword ptr [ebp - 0x2c0], eax */
L_48f2bf:
	m->ecx = 0x4c8274u;	/* 48f2bf: mov ecx, 0x4c8274 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f2c4: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f2ca: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f2cc: je 0x48f537 */
	m->edi = m->ecx;	/* 48f2d2: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f2d4: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f2d7: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f2d9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f2db: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f2dd: sub edi, ecx */
	m->eax = m->ecx;	/* 48f2df: mov eax, ecx */
	m->esi = m->edi;	/* 48f2e1: mov esi, edi */
	m->edi = m->edx;	/* 48f2e3: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f2e5: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f2e8: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f2ea: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f2ec: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f2ef: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f2f1: jmp 0x48f53a */
L_48f2f6:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f2f6: test byte ptr [ebp + 8], 1 */
	if (!m->zf) goto L_48f822;	/* 48f2fa: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd40u));	/* 48f300: mov esi, dword ptr [ebp - 0x2c0] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc34u));	/* 48f306: mov eax, dword ptr [ebp - 0x3cc] */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f30c: add esi, 0x64 */
	m->ecx = m->esi;	/* 48f30f: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->esi;	/* 48f311: mov dword ptr [ebp - 0x2c0], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f317: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f321;	/* 48f319: jle 0x48f321 */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->eax;	/* 48f31b: mov dword ptr [ebp - 0x2c0], eax */
L_48f321:
	m->ecx = 0x4c8268u;	/* 48f321: mov ecx, 0x4c8268 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f326: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f32c: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f32e: je 0x48f537 */
	m->edi = m->ecx;	/* 48f334: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f336: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f339: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f33b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f33d: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f33f: sub edi, ecx */
	m->eax = m->ecx;	/* 48f341: mov eax, ecx */
	m->esi = m->edi;	/* 48f343: mov esi, edi */
	m->edi = m->edx;	/* 48f345: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f347: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f34a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f34c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f34e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f351: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f353: jmp 0x48f53a */
L_48f358:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f358: test byte ptr [ebp + 8], 2 */
	if (!m->zf) goto L_48f822;	/* 48f35c: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd40u));	/* 48f362: mov esi, dword ptr [ebp - 0x2c0] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc34u));	/* 48f368: mov eax, dword ptr [ebp - 0x3cc] */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f36e: add esi, 0x64 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48f371: add eax, 0x64 */
	m->ecx = m->esi;	/* 48f374: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->esi;	/* 48f376: mov dword ptr [ebp - 0x2c0], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f37c: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f386;	/* 48f37e: jle 0x48f386 */
	M32((DWORD)(m->ebp + 0xfffffd40u)) = m->eax;	/* 48f380: mov dword ptr [ebp - 0x2c0], eax */
L_48f386:
	m->ecx = 0x4c8254u;	/* 48f386: mov ecx, 0x4c8254 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f38b: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f391: test ecx, ecx */
	if (m->zf) goto L_48f8b7;	/* 48f393: je 0x48f8b7 */
	m->edi = m->ecx;	/* 48f399: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f39b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f39e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f3a0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f3a2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f3a4: sub edi, ecx */
	m->eax = m->ecx;	/* 48f3a6: mov eax, ecx */
	m->esi = m->edi;	/* 48f3a8: mov esi, edi */
	m->edi = m->edx;	/* 48f3aa: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f3ac: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f3af: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f3b1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f3b3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f3b6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f8ba;	/* 48f3b8: jmp 0x48f8ba */
L_48f3bd:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x4u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f3bd: test byte ptr [ebp + 8], 4 */
	if (!m->zf) goto L_48f822;	/* 48f3c1: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd44u));	/* 48f3c7: mov esi, dword ptr [ebp - 0x2bc] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc38u));	/* 48f3cd: mov eax, dword ptr [ebp - 0x3c8] */
	{ DWORD a_ = m->esi, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f3d3: add esi, 0xa */
	m->ecx = m->esi;	/* 48f3d6: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->esi;	/* 48f3d8: mov dword ptr [ebp - 0x2bc], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f3de: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f3e8;	/* 48f3e0: jle 0x48f3e8 */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->eax;	/* 48f3e2: mov dword ptr [ebp - 0x2bc], eax */
L_48f3e8:
	m->eax = 0x4c8248u;	/* 48f3e8: mov eax, 0x4c8248 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f3ed: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f3f3: test eax, eax */
	if (m->zf) goto L_48f537;	/* 48f3f5: je 0x48f537 */
	m->edi = m->eax;	/* 48f3fb: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f3fd: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f400: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f402: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f404: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f406: sub edi, ecx */
	m->eax = m->ecx;	/* 48f408: mov eax, ecx */
	m->esi = m->edi;	/* 48f40a: mov esi, edi */
	m->edi = m->edx;	/* 48f40c: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f40e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f411: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f413: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f415: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f418: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f41a: jmp 0x48f53a */
L_48f41f:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x4u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f41f: test byte ptr [ebp + 8], 4 */
	if (!m->zf) goto L_48f822;	/* 48f423: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd44u));	/* 48f429: mov esi, dword ptr [ebp - 0x2bc] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc38u));	/* 48f42f: mov eax, dword ptr [ebp - 0x3c8] */
	{ DWORD a_ = m->esi, b_ = 0x19u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f435: add esi, 0x19 */
	m->ecx = m->esi;	/* 48f438: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->esi;	/* 48f43a: mov dword ptr [ebp - 0x2bc], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f440: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f44a;	/* 48f442: jle 0x48f44a */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->eax;	/* 48f444: mov dword ptr [ebp - 0x2bc], eax */
L_48f44a:
	m->ecx = 0x4c823cu;	/* 48f44a: mov ecx, 0x4c823c */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f44f: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f455: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f457: je 0x48f537 */
	m->edi = m->ecx;	/* 48f45d: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f45f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f462: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f464: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f466: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f468: sub edi, ecx */
	m->eax = m->ecx;	/* 48f46a: mov eax, ecx */
	m->esi = m->edi;	/* 48f46c: mov esi, edi */
	m->edi = m->edx;	/* 48f46e: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f470: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f473: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f475: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f477: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f47a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f47c: jmp 0x48f53a */
L_48f481:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x4u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f481: test byte ptr [ebp + 8], 4 */
	if (!m->zf) goto L_48f822;	/* 48f485: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd44u));	/* 48f48b: mov esi, dword ptr [ebp - 0x2bc] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc38u));	/* 48f491: mov eax, dword ptr [ebp - 0x3c8] */
	{ DWORD a_ = m->esi, b_ = 0x32u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f497: add esi, 0x32 */
	m->ecx = m->esi;	/* 48f49a: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->esi;	/* 48f49c: mov dword ptr [ebp - 0x2bc], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f4a2: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f4ac;	/* 48f4a4: jle 0x48f4ac */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->eax;	/* 48f4a6: mov dword ptr [ebp - 0x2bc], eax */
L_48f4ac:
	m->ecx = 0x4c8230u;	/* 48f4ac: mov ecx, 0x4c8230 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f4b1: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f4b7: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f4b9: je 0x48f537 */
	m->edi = m->ecx;	/* 48f4bb: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f4bd: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f4c0: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f4c2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f4c4: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f4c6: sub edi, ecx */
	m->eax = m->ecx;	/* 48f4c8: mov eax, ecx */
	m->esi = m->edi;	/* 48f4ca: mov esi, edi */
	m->edi = m->edx;	/* 48f4cc: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f4ce: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f4d1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f4d3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f4d5: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f4d8: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f4da: jmp 0x48f53a */
L_48f4dc:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x4u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f4dc: test byte ptr [ebp + 8], 4 */
	if (!m->zf) goto L_48f822;	/* 48f4e0: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd44u));	/* 48f4e6: mov esi, dword ptr [ebp - 0x2bc] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc38u));	/* 48f4ec: mov eax, dword ptr [ebp - 0x3c8] */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f4f2: add esi, 0x64 */
	m->ecx = m->esi;	/* 48f4f5: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->esi;	/* 48f4f7: mov dword ptr [ebp - 0x2bc], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f4fd: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f507;	/* 48f4ff: jle 0x48f507 */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->eax;	/* 48f501: mov dword ptr [ebp - 0x2bc], eax */
L_48f507:
	m->ecx = 0x4c8224u;	/* 48f507: mov ecx, 0x4c8224 */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f50c: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f512: test ecx, ecx */
	if (m->zf) goto L_48f537;	/* 48f514: je 0x48f537 */
	m->edi = m->ecx;	/* 48f516: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f518: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f51b: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f51d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f51f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f521: sub edi, ecx */
	m->eax = m->ecx;	/* 48f523: mov eax, ecx */
	m->esi = m->edi;	/* 48f525: mov esi, edi */
	m->edi = m->edx;	/* 48f527: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f529: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f52c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f52e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f530: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f533: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f53a;	/* 48f535: jmp 0x48f53a */
L_48f537:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 48f537: mov byte ptr [edx], 0 */
L_48f53a:
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 48f53a: mov esi, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ebp + 0x14cu)) = 0x0u;	/* 48f53e: mov dword ptr [ebp + 0x14c], 0 */
	m->ebx = 0x1u;	/* 48f548: mov ebx, 1 */
	goto L_48f7e9;	/* 48f54d: jmp 0x48f7e9 */
L_48f552:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x8u)), b_ = 0x8u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f552: test byte ptr [ebp + 8], 8 */
	if (!m->zf) goto L_48f822;	/* 48f556: jne 0x48f822 */
	m->esi = M32((DWORD)(m->ebp + 0xfffffd44u));	/* 48f55c: mov esi, dword ptr [ebp - 0x2bc] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffc38u));	/* 48f562: mov eax, dword ptr [ebp - 0x3c8] */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48f568: add esi, 0x64 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48f56b: add eax, 0x64 */
	m->ecx = m->esi;	/* 48f56e: mov ecx, esi */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->esi;	/* 48f570: mov dword ptr [ebp - 0x2bc], esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f576: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_48f580;	/* 48f578: jle 0x48f580 */
	M32((DWORD)(m->ebp + 0xfffffd44u)) = m->eax;	/* 48f57a: mov dword ptr [ebp - 0x2bc], eax */
L_48f580:
	m->ecx = 0x4c820cu;	/* 48f580: mov ecx, 0x4c820c */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f585: lea edx, [ebp + 0x10c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f58b: test ecx, ecx */
	if (m->zf) goto L_48f8b7;	/* 48f58d: je 0x48f8b7 */
	m->edi = m->ecx;	/* 48f593: mov edi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f595: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f598: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f59a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f59c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f59e: sub edi, ecx */
	m->eax = m->ecx;	/* 48f5a0: mov eax, ecx */
	m->esi = m->edi;	/* 48f5a2: mov esi, edi */
	m->edi = m->edx;	/* 48f5a4: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f5a6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f5a9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f5ab: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f5ad: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f5b0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f8ba;	/* 48f5b2: jmp 0x48f8ba */
L_48f5b7:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48f5b7: push ecx */
	{ DWORD v_ = 0x4c81d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48f5b8: push 0x4c81d0 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48f5bd: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48f5c7u; native_call(m, 0x46c710u);	/* 48f5c2: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48f5c7: add esp, 0xc */
	goto L_48f822;	/* 48f5ca: jmp 0x48f822 */
L_48f5cf:
	m->eax = m->ecx;	/* 48f5cf: mov eax, ecx */
	m->ecx = 0xau;	/* 48f5d1: mov ecx, 0xa */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48f5d6: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 48f5d7: idiv ecx */
	{ DWORD a_ = m->edx, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f5d9: cmp edx, 7 */
	if (!m->cf && !m->zf) goto L_48f822;	/* 48f5dc: ja 0x48f822 */
	switch (m->edx) { case 0: goto L_48f5e9; case 1: goto L_48f627; case 2: goto L_48f822; case 3: goto L_48f665; case 4: goto L_48f6c5; case 5: goto L_48f822; case 6: goto L_48f822; case 7: goto L_48f880; default: abort(); }	/* 48f5e2: jmp dword ptr [edx*4 + 0x48f948] */
L_48f5e9:
	m->eax = 0x4c81c4u;	/* 48f5e9: mov eax, 0x4c81c4 */
	M32((DWORD)(m->ebp + 0xcu)) = 0x41f00000u;	/* 48f5ee: mov dword ptr [ebp + 0xc], 0x41f00000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f5f5: test eax, eax */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f5f7: lea edx, [ebp + 0x10c] */
	if (m->zf) goto L_48f8b7;	/* 48f5fd: je 0x48f8b7 */
	m->edi = m->eax;	/* 48f603: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f605: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f608: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f60a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f60c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f60e: sub edi, ecx */
	m->eax = m->ecx;	/* 48f610: mov eax, ecx */
	m->esi = m->edi;	/* 48f612: mov esi, edi */
	m->edi = m->edx;	/* 48f614: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f616: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f619: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f61b: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f61d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f620: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f8ba;	/* 48f622: jmp 0x48f8ba */
L_48f627:
	m->eax = 0x4c81b4u;	/* 48f627: mov eax, 0x4c81b4 */
	M32((DWORD)(m->ebp + 0x10u)) = 0x41f00000u;	/* 48f62c: mov dword ptr [ebp + 0x10], 0x41f00000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f633: test eax, eax */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f635: lea edx, [ebp + 0x10c] */
	if (m->zf) goto L_48f8b7;	/* 48f63b: je 0x48f8b7 */
	m->edi = m->eax;	/* 48f641: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f643: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f646: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f648: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f64a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f64c: sub edi, ecx */
	m->eax = m->ecx;	/* 48f64e: mov eax, ecx */
	m->esi = m->edi;	/* 48f650: mov esi, edi */
	m->edi = m->edx;	/* 48f652: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f654: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f657: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f659: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f65b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f65e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f8ba;	/* 48f660: jmp 0x48f8ba */
L_48f665:
	m->eax = 0x4c81a4u;	/* 48f665: mov eax, 0x4c81a4 */
	M32((DWORD)(m->ebp + 0x14u)) = 0x41f00000u;	/* 48f66a: mov dword ptr [ebp + 0x14], 0x41f00000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f671: test eax, eax */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f673: lea edx, [ebp + 0x10c] */
	if (m->zf) goto L_48f69c;	/* 48f679: je 0x48f69c */
	m->edi = m->eax;	/* 48f67b: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f67d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f680: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f682: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f684: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f686: sub edi, ecx */
	m->eax = m->ecx;	/* 48f688: mov eax, ecx */
	m->esi = m->edi;	/* 48f68a: mov esi, edi */
	m->edi = m->edx;	/* 48f68c: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f68e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f691: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f693: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f695: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f698: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f69f;	/* 48f69a: jmp 0x48f69f */
L_48f69c:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 48f69c: mov byte ptr [edx], 0 */
L_48f69f:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48f69f: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 48f6a3: mov ecx, dword ptr [esp + 0x18] */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 48f6a7: mov esi, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ebp + 0x14cu)) = 0x0u;	/* 48f6ab: mov dword ptr [ebp + 0x14c], 0 */
	M32((DWORD)(m->edx + 0x20fcd3cu)) = m->ecx;	/* 48f6b5: mov dword ptr [edx + 0x20fcd3c], ecx */
	m->ebx = 0x1u;	/* 48f6bb: mov ebx, 1 */
	goto L_48f7e9;	/* 48f6c0: jmp 0x48f7e9 */
L_48f6c5:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 48f6c5: mov ecx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->ebp + 0xfffffd28u));	/* 48f6c9: mov eax, dword ptr [ebp - 0x2d8] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ecx + 0x202e8d4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f6cf: cmp eax, dword ptr [ecx + 0x202e8d4] */
	if (!m->zf) goto L_48f7d6;	/* 48f6d5: jne 0x48f7d6 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x158u)));	/* 48f6db: fld dword ptr [ebp + 0x158] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48f6e1: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48f6e7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48f6e9: test ah, 0x41 */
	if (m->zf) goto L_48f7d6;	/* 48f6ec: je 0x48f7d6 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 48f6f2: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->ebp + 0x150u));	/* 48f6f6: mov eax, dword ptr [ebp + 0x150] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f6fc: cmp eax, edx */
	if (m->zf) goto L_48f7d6;	/* 48f6fe: je 0x48f7d6 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 48f704: mov eax, dword ptr [esi + 4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48f707: lea eax, [eax + eax*4] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x20fae04u);	/* 48f70a: lea edx, [ecx + eax*8 + 0x20fae04] */
	m->eax = (DWORD)(m->ebp + 0xfffffd98u);	/* 48f711: lea eax, [ebp - 0x268] */
	m->edi = M32((DWORD)(m->edx + 0x0u));	/* 48f717: mov edi, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->edi;	/* 48f719: mov dword ptr [eax], edi */
	m->edi = M32((DWORD)(m->edx + 0x4u));	/* 48f71b: mov edi, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edi;	/* 48f71e: mov dword ptr [eax + 4], edi */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 48f721: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 48f724: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 48f727: mov eax, dword ptr [esi + 4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48f72a: lea eax, [eax + eax*4] */
	FPUSH((long double)(int)M32((DWORD)(m->ecx + m->eax*8 + 0x20fae00u)));	/* 48f72d: fild dword ptr [ecx + eax*8 + 0x20fae00] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48f734: fmul dword ptr [0x4a9418] */
	MF((DWORD)(m->ebp + 0xfffffda4u)) = (float)ST(0); FPOP();	/* 48f73a: fstp dword ptr [ebp - 0x25c] */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 48f740: mov eax, dword ptr [esi + 4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48f743: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->ecx + m->edx*8 + 0x20fae14u));	/* 48f746: mov eax, dword ptr [ecx + edx*8 + 0x20fae14] */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f74d: lea edx, [ebp + 0x10c] */
	M32((DWORD)(m->ebp + 0xfffffda8u)) = m->eax;	/* 48f753: mov dword ptr [ebp - 0x258], eax */
	m->ecx = M32((DWORD)(m->esi + 0x4u));	/* 48f759: mov ecx, dword ptr [esi + 4] */
	m->eax = 0x4c8198u;	/* 48f75c: mov eax, 0x4c8198 */
	M32((DWORD)(m->ebp + 0x150u)) = m->ecx;	/* 48f761: mov dword ptr [ebp + 0x150], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f767: test eax, eax */
	if (m->zf) goto L_48f78c;	/* 48f769: je 0x48f78c */
	m->edi = m->eax;	/* 48f76b: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f76d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f770: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f772: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f774: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f776: sub edi, ecx */
	m->eax = m->ecx;	/* 48f778: mov eax, ecx */
	m->esi = m->edi;	/* 48f77a: mov esi, edi */
	m->edi = m->edx;	/* 48f77c: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f77e: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f781: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f783: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f785: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f788: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f78f;	/* 48f78a: jmp 0x48f78f */
L_48f78c:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 48f78c: mov byte ptr [edx], 0 */
L_48f78f:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48f78f: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ebp + 0x14cu)) = 0x0u;	/* 48f793: mov dword ptr [ebp + 0x14c], 0 */
	M32((DWORD)(m->ebp + 0x160u)) = 0x3f800000u;	/* 48f79d: mov dword ptr [ebp + 0x160], 0x3f800000 */
	M32((DWORD)(m->ebp + 0x158u)) = 0x40000000u;	/* 48f7a7: mov dword ptr [ebp + 0x158], 0x40000000 */
	m->ecx = M32((DWORD)(m->eax + 0x202e8d0u));	/* 48f7b1: mov ecx, dword ptr [eax + 0x202e8d0] */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 48f7b7: mov esi, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ebp + 0xfffffd1cu)) = m->ecx;	/* 48f7bb: mov dword ptr [ebp - 0x2e4], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x202e8d0u));	/* 48f7c1: mov ecx, dword ptr [eax + 0x202e8d0] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48f7c7: inc ecx */
	M32((DWORD)(m->esp + 0x24u)) = 0x1u;	/* 48f7c8: mov dword ptr [esp + 0x24], 1 */
	M32((DWORD)(m->eax + 0x202e8d0u)) = m->ecx;	/* 48f7d0: mov dword ptr [eax + 0x202e8d0], ecx */
L_48f7d6:
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 48f7d6: mov ecx, dword ptr [esp + 0x24] */
	m->eax = 0x1u;	/* 48f7da: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f7df: cmp ecx, eax */
	M32((DWORD)(m->ebp + 0x154u)) = m->eax;	/* 48f7e1: mov dword ptr [ebp + 0x154], eax */
	if (!m->zf) goto L_48f822;	/* 48f7e7: jne 0x48f822 */
L_48f7e9:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 48f7e9: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x47c35000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48f7ed: push 0x47c35000 */
	m->edx = (DWORD)(m->esi + 0xcu);	/* 48f7f2: lea edx, [esi + 0xc] */
	m->ecx = (DWORD)(m->eax + 0x20f397cu);	/* 48f7f5: lea ecx, [eax + 0x20f397c] */
	{ DWORD a_ = m->eax, b_ = 0x20f3970u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48f7fb: add eax, 0x20f3970 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48f800: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48f801: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48f802: push eax */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 48f803: mov eax, dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->eax + 0x44u));	/* 48f807: mov ecx, dword ptr [eax + 0x44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48f80a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48f810u; native_call(m, 0x456ed0u);	/* 48f80b: call 0x456ed0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48f810: add esp, 0x14 */
	{ DWORD a_ = m->ebx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f813: cmp ebx, 1 */
	if (!m->zf) goto L_48f822;	/* 48f816: jne 0x48f822 */
	M32((DWORD)(m->esi + 0x20u)) = m->ebx;	/* 48f818: mov dword ptr [esi + 0x20], ebx */
	M32((DWORD)(m->esi + 0x24u)) = 0x0u;	/* 48f81b: mov dword ptr [esi + 0x24], 0 */
L_48f822:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 48f822: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 48f826: fadd dword ptr [esi + 0x24] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 48f829: mov edi, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 48f82d: mov eax, dword ptr [esp + 0x18] */
	MF((DWORD)(m->esi + 0x24u)) = (float)ST(0); FPOP();	/* 48f831: fstp dword ptr [esi + 0x24] */
L_48f834:
	m->ecx = M32((DWORD)(m->edi + 0x20fcd38u));	/* 48f834: mov ecx, dword ptr [edi + 0x20fcd38] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48f83a: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f83b: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 48f83d: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_48ede6;	/* 48f841: jl 0x48ede6 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48f847: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48f848: pop ebx */
L_48f849:
	m->eax = M32((DWORD)(m->edi + 0x202e8c8u));	/* 48f849: mov eax, dword ptr [edi + 0x202e8c8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f84f: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f851: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48f878;	/* 48f853: jle 0x48f878 */
	m->eax = (DWORD)(m->edi + 0x1cd98e0u);	/* 48f855: lea eax, [edi + 0x1cd98e0] */
L_48f85b:
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 48f85b: mov edx, dword ptr [eax + 4] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f85e: test edx, edx */
	if (!m->zf) goto L_48f868;	/* 48f860: jne 0x48f868 */
	M32((DWORD)(m->eax + 0x0u)) = 0xffffffffu;	/* 48f862: mov dword ptr [eax], 0xffffffff */
L_48f868:
	m->edx = M32((DWORD)(m->edi + 0x202e8c8u));	/* 48f868: mov edx, dword ptr [edi + 0x202e8c8] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48f86e: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48f86f: add eax, 0x8888 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48f874: cmp ecx, edx */
	if (m->sf != m->of) goto L_48f85b;	/* 48f876: jl 0x48f85b */
L_48f878:
	m->edi = M32(m->esp); m->esp += 4;	/* 48f878: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48f879: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48f87a: add esp, 0x18 */
	m->esp += 4 + 4; return;	/* 48f87d: ret 4 */
L_48f880:
	m->eax = 0x4c8188u;	/* 48f880: mov eax, 0x4c8188 */
	M32((DWORD)(m->ebp + 0x18u)) = 0x41f00000u;	/* 48f885: mov dword ptr [ebp + 0x18], 0x41f00000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48f88c: test eax, eax */
	m->edx = (DWORD)(m->ebp + 0x10cu);	/* 48f88e: lea edx, [ebp + 0x10c] */
	if (m->zf) goto L_48f8b7;	/* 48f894: je 0x48f8b7 */
	m->edi = m->eax;	/* 48f896: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f898: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48f89b: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48f89d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48f89f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48f8a1: sub edi, ecx */
	m->eax = m->ecx;	/* 48f8a3: mov eax, ecx */
	m->esi = m->edi;	/* 48f8a5: mov esi, edi */
	m->edi = m->edx;	/* 48f8a7: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48f8a9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48f8ac: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48f8ae: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48f8b0: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48f8b3: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_48f8ba;	/* 48f8b5: jmp 0x48f8ba */
L_48f8b7:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 48f8b7: mov byte ptr [edx], 0 */
L_48f8ba:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48f8ba: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 48f8be: mov ecx, dword ptr [esp + 0x18] */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 48f8c2: mov esi, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ebp + 0x14cu)) = 0x0u;	/* 48f8c6: mov dword ptr [ebp + 0x14c], 0 */
	m->ebx = 0x1u;	/* 48f8d0: mov ebx, 1 */
	M32((DWORD)(m->edx + 0x20fcd3cu)) = m->ecx;	/* 48f8d5: mov dword ptr [edx + 0x20fcd3c], ecx */
	goto L_48f7e9;	/* 48f8db: jmp 0x48f7e9 */
L_48f8e0:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48f8e0: push ecx */
	{ DWORD v_ = 0x4c81d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48f8e1: push 0x4c81d0 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48f8e6: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48f8f0u; native_call(m, 0x46c5f0u);	/* 48f8eb: call 0x46c5f0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48f8f0: add esp, 0xc */
	goto L_48f822;	/* 48f8f3: jmp 0x48f822 */
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
