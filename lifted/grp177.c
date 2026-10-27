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

static void lift_429170(X86 *m);
static void lift_495510(X86 *m);
static void lift_4953d0(X86 *m);
static void lift_495190(X86 *m);
static void lift_491f50(X86 *m);

/* hud_drawLockOn (0x491f50), lifted by tools/lift.py */
static void lift_491f50(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 491f50: sub esp, 0x20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 491f53: push ebx */
	m->ebx = M32((DWORD)(0x4a91f4u));	/* 491f54: mov ebx, dword ptr [0x4a91f4] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 491f5a: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 491f5b: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 491f5c: xor eax, eax */
	m->edx = (DWORD)(m->ecx + 0x2222148u);	/* 491f5e: lea edx, [ecx + 0x2222148] */
	m->ebp = (DWORD)(m->ecx + 0x1ed5250u);	/* 491f64: lea ebp, [ecx + 0x1ed5250] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 491f6a: push edi */
	m->edi = M32((DWORD)(0x4a920cu));	/* 491f6b: mov edi, dword ptr [0x4a920c] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 491f71: mov dword ptr [esp + 0x1c], ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 491f75: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 491f79: mov dword ptr [esp + 0x2c], edx */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 491f7d: mov dword ptr [esp + 0x18], ebp */
	goto L_491f87;	/* 491f81: jmp 0x491f87 */
L_491f83:
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 491f83: mov ecx, dword ptr [esp + 0x1c] */
L_491f87:
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->ecx + 0x234240du)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491f87: cmp eax, dword ptr [ecx + 0x234240d] */
	if (m->zf) goto L_492289;	/* 491f8d: je 0x492289 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xffff796cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491f93: cmp dword ptr [ebp - 0x8694], 1 */
	if (!m->zf) goto L_492289;	/* 491f9a: jne 0x492289 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 491fa0: cmp dword ptr [ebp], 1 */
	if (!m->zf) goto L_492289;	/* 491fa4: jne 0x492289 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 491faa: fld dword ptr [edx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 491fac: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 491fb2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 491fb4: test ah, 0x41 */
	if (!m->zf) goto L_492134;	/* 491fb7: jne 0x492134 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 491fbd: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 491fc0: fmul dword ptr [0x4a947c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 491fc6: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 491fca: fld dword ptr [edx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 491fcc: fmul dword ptr [0x4a947c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 491fd2: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 491fd6: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 491fda: fmul dword ptr [0x4a93d0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 491fe0: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 491fe6: fmul dword ptr [0x4a9518] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 491fec: fstp dword ptr [esp + 0x10] */
	m->esp -= 4; M32(m->esp) = 0x491ff5u; native_call(m, 0x4685b0u);	/* 491ff0: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 491ff5: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 491ff9: fild dword ptr [esp + 0x14] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 491ffd: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 492003: fdivr dword ptr [esp + 0x10] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 492007: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xffffffdcu)));	/* 49200c: fld dword ptr [ebp - 0x24] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 49200f: mov dword ptr [esp + 0x10], eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 492013: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492014: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 492016: sar eax, 1 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 492018: mov dword ptr [esp + 0x14], eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49201c: call 0x49ec14 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 492021: mov edx, dword ptr [esp + 0x14] */
	m->esi = m->eax;	/* 492025: mov esi, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xffffffe0u)));	/* 492027: fld dword ptr [ebp - 0x20] */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 49202a: sub esi, edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49202c: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 492031: mov ecx, dword ptr [esp + 0x14] */
	m->ebp = m->eax;	/* 492035: mov ebp, eax */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 492037: push 0xde1 */
	{ DWORD a_ = m->ebp, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 49203c: sub ebp, ecx */
	m->esp -= 4; M32(m->esp) = 0x492044u; native_call(m, M32(0x4a9224u));	/* 49203e: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 492044: mov eax, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->eax + 0xbc06a0u));	/* 492048: mov eax, dword ptr [eax + 0xbc06a0] */
	m->ecx = m->eax;	/* 49204e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 492050: and ecx, 0x800001ff */
	if (!m->sf) goto L_492060;	/* 492056: jns 0x492060 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 492058: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 492059: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49205f: inc ecx */
L_492060:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 492060: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 492061: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 492067: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492068: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 49206a: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 492070: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 492073: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x49207cu; native_call(m, 0x4566c0u);	/* 492077: call 0x4566c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 49207c: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 492082: fsub dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 492086: fst dword ptr [esp + 0x20] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 49208a: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49208e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 492090: test ah, 1 */
	if (m->zf) goto L_49209c;	/* 492093: je 0x49209c */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 492095: mov eax, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492099: push eax */
	goto L_4920a1;	/* 49209a: jmp 0x4920a1 */
L_49209c:
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 49209c: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4920a0: push ecx */
L_4920a1:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920a1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920a6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920ab: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4920b6u; native_call(m, M32(0x4a9228u));	/* 4920b0: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920b6: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4920beu; native_call(m, M32(0x4a921cu));	/* 4920b8: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920be: push 0x3f000000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920c3: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x4920cau; native_call(m, m->edi);	/* 4920c8: call edi */
	m->esp -= 4; M32(m->esp) = 0x4920cfu; native_call(m, 0x4685c0u);	/* 4920ca: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4920cf: sub eax, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4920d1: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4920d2: push esi */
	m->esp -= 4; M32(m->esp) = 0x4920d5u; native_call(m, m->ebx);	/* 4920d3: call ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920d5: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920da: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x4920e1u; native_call(m, m->edi);	/* 4920df: call edi */
	m->esp -= 4; M32(m->esp) = 0x4920e6u; native_call(m, 0x4685c0u);	/* 4920e1: call 0x4685c0 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4920e6: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4920ea: sub eax, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4920ec: push eax */
	m->eax = (DWORD)(m->edx + m->esi*1 + 0x0u);	/* 4920ed: lea eax, [edx + esi] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4920f0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4920f3u; native_call(m, m->ebx);	/* 4920f1: call ebx */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920f3: push 0x3f400000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4920f8: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x4920ffu; native_call(m, m->edi);	/* 4920fd: call edi */
	m->esp -= 4; M32(m->esp) = 0x492104u; native_call(m, 0x4685c0u);	/* 4920ff: call 0x4685c0 */
	m->ecx = m->eax;	/* 492104: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 492106: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49210a: sub ecx, ebp */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49210c: sub ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49210e: add eax, esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 492110: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492111: push eax */
	m->esp -= 4; M32(m->esp) = 0x492114u; native_call(m, m->ebx);	/* 492112: call ebx */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 492114: push 0x3f400000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 492119: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x492120u; native_call(m, m->edi);	/* 49211e: call edi */
	m->esp -= 4; M32(m->esp) = 0x492125u; native_call(m, 0x4685c0u);	/* 492120: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492125: sub eax, ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 492127: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49212b: sub eax, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49212d: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49212e: push esi */
	goto L_492272;	/* 49212f: jmp 0x492272 */
L_492134:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8u)));	/* 492134: fld dword ptr [ebp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 492137: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49213d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49213f: test ah, 0x41 */
	if (!m->zf) goto L_492289;	/* 492142: jne 0x492289 */
	m->esp -= 4; M32(m->esp) = 0x49214du; native_call(m, 0x4685b0u);	/* 492148: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 49214d: mov dword ptr [esp + 0x24], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 492151: fild dword ptr [esp + 0x24] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 492155: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9518u));	/* 49215b: fdivr dword ptr [0x4a9518] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 492161: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 492166: mov dword ptr [esp + 0x10], eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49216a: cdq  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xffffffdcu)));	/* 49216b: fld dword ptr [ebp - 0x24] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49216e: sub eax, edx */
	m->esi = m->eax;	/* 492170: mov esi, eax */
	{ DWORD a_ = m->esi, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 492172: sar esi, 1 */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 492174: mov dword ptr [esp + 0x14], esi */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 492178: call 0x49ec14 */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49217d: mov edx, dword ptr [esp + 0x18] */
	m->ebp = m->eax;	/* 492181: mov ebp, eax */
	{ DWORD a_ = m->ebp, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 492183: sub ebp, esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0xffffffe0u)));	/* 492185: fld dword ptr [edx - 0x20] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 492188: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49218d: mov ecx, dword ptr [esp + 0x14] */
	m->esi = m->eax;	/* 492191: mov esi, eax */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 492193: push 0xde1 */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 492198: sub esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x4921a0u; native_call(m, M32(0x4a9224u));	/* 49219a: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4921a0: mov eax, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->eax + 0xbc06a0u));	/* 4921a4: mov eax, dword ptr [eax + 0xbc06a0] */
	m->ecx = m->eax;	/* 4921aa: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4921ac: and ecx, 0x800001ff */
	if (!m->sf) goto L_4921bc;	/* 4921b2: jns 0x4921bc */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4921b4: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4921b5: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4921bb: inc ecx */
L_4921bc:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4921bc: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4921bd: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4921c3: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4921c4: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4921c6: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4921cc: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4921cf: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4921d8u; native_call(m, 0x4566c0u);	/* 4921d3: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4921d8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4921dd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4921e2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4921e7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4921f2u; native_call(m, M32(0x4a9228u));	/* 4921ec: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4921f2: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4921fau; native_call(m, M32(0x4a921cu));	/* 4921f4: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4921fa: push 0x3f400000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4921ff: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x492206u; native_call(m, m->edi);	/* 492204: call edi */
	m->esp -= 4; M32(m->esp) = 0x49220bu; native_call(m, 0x4685c0u);	/* 492206: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49220b: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49220d: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49220e: push ebp */
	m->esp -= 4; M32(m->esp) = 0x492211u; native_call(m, m->ebx);	/* 49220f: call ebx */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 492211: push 0x3f400000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 492216: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x49221du; native_call(m, m->edi);	/* 49221b: call edi */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49221d: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492221: add eax, ebp */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 492223: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x49222cu; native_call(m, 0x4685c0u);	/* 492227: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 49222c: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492230: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492232: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 492233: push ecx */
	m->esp -= 4; M32(m->esp) = 0x492236u; native_call(m, m->ebx);	/* 492234: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 492236: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49223b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x492242u; native_call(m, m->edi);	/* 492240: call edi */
	m->esp -= 4; M32(m->esp) = 0x492247u; native_call(m, 0x4685c0u);	/* 492242: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 492247: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 49224b: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49224f: sub eax, esi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492251: sub eax, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492253: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 492254: push edx */
	m->esp -= 4; M32(m->esp) = 0x492257u; native_call(m, m->ebx);	/* 492255: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 492257: push 0x3f800000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49225c: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x492263u; native_call(m, m->edi);	/* 492261: call edi */
	m->esp -= 4; M32(m->esp) = 0x492268u; native_call(m, 0x4685c0u);	/* 492263: call 0x4685c0 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 492268: sub eax, esi */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 49226a: mov esi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49226e: sub eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 492270: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 492271: push ebp */
L_492272:
	m->esp -= 4; M32(m->esp) = 0x492274u; native_call(m, m->ebx);	/* 492272: call ebx */
	m->esp -= 4; M32(m->esp) = 0x49227au; native_call(m, M32(0x4a9220u));	/* 492274: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49227a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x492285u; native_call(m, M32(0x4a922cu));	/* 49227f: call dword ptr [0x4a922c] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 492285: mov ebp, dword ptr [esp + 0x18] */
L_492289:
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 492289: mov eax, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 49228d: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 492291: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 492292: add edx, 4 */
	{ DWORD a_ = m->ebp, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 492295: add ebp, 0x8888 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49229b: cmp eax, 0x10 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 49229e: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 4922a2: mov dword ptr [esp + 0x2c], edx */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 4922a6: mov dword ptr [esp + 0x18], ebp */
	if (m->sf != m->of) goto L_491f83;	/* 4922aa: jl 0x491f83 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4922b0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4922b1: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4922b2: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4922b3: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4922b4: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 4922b7: ret  */
}

/* menu_titleEmblemTransition (0x429170), lifted by tools/lift.py */
static void lift_429170(X86 *m)
{
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 429170: push 2 */
	m->esp -= 4; M32(m->esp) = 0x429177u; native_call(m, 0x41ef90u);	/* 429172: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429177: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x429180u; native_call(m, M32(0x4a9218u));	/* 42917a: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 429180: fld dword ptr [0x4b071c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9534u)); FPOP();	/* 429186: fcomp dword ptr [0x4a9534] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42918c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42918e: test ah, 0x41 */
	if (!m->zf) goto L_42919d;	/* 429191: jne 0x42919d */
	M32((DWORD)(0x4b071cu)) = 0x3f800000u;	/* 429193: mov dword ptr [0x4b071c], 0x3f800000 */
L_42919d:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42919d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42919e: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42919f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4291a0: push edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4291a1: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4291acu; native_call(m, M32(0x4a9224u));	/* 4291a6: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x4df01cu));	/* 4291ac: mov eax, dword ptr [0x4df01c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4291b1: test eax, eax */
	if (m->zf) goto L_4291cd;	/* 4291b3: je 0x4291cd */
	FPUSH((long double)(int)M32((DWORD)(0x4e0458u)));	/* 4291b5: fild dword ptr [0x4e0458] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4291bb: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9530u));	/* 4291bc: fmul dword ptr [0x4a9530] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4291c2: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4291c8: fstp dword ptr [esp] */
	goto L_4291d2;	/* 4291cb: jmp 0x4291d2 */
L_4291cd:
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 4291cd: push 0x3f19999a */
L_4291d2:
	m->ebp = M32((DWORD)(0x4a9228u));	/* 4291d2: mov ebp, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4291d8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4291dd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4291e2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4291e9u; native_call(m, m->ebp);	/* 4291e7: call ebp */
	m->eax = M32((DWORD)(0x9dad6cu));	/* 4291e9: mov eax, dword ptr [0x9dad6c] */
	m->ecx = m->eax;	/* 4291ee: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4291f0: and ecx, 0x800001ff */
	if (!m->sf) goto L_429200;	/* 4291f6: jns 0x429200 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4291f8: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4291f9: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4291ff: inc ecx */
L_429200:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 429200: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429201: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429207: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429208: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 42920a: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429210: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 429213: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x42921cu; native_call(m, 0x4566c0u);	/* 429217: call 0x4566c0 */
	m->edi = M32((DWORD)(0x4a921cu));	/* 42921c: mov edi, dword ptr [0x4a921c] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429222: push 7 */
	m->esp -= 4; M32(m->esp) = 0x429226u; native_call(m, m->edi);	/* 429224: call edi */
	m->esi = M32((DWORD)(0x4a9208u));	/* 429226: mov esi, dword ptr [0x4a9208] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42922c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42922e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429230: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429232: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429236u; native_call(m, m->esi);	/* 429234: call esi */
	m->eax = M32((DWORD)(0x4e0458u));	/* 429236: mov eax, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->eax*4 + 0x4b065cu));	/* 42923b: mov eax, dword ptr [eax*4 + 0x4b065c] */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 429242: neg eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429244: push eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429245: push eax */
	m->esp -= 4; M32(m->esp) = 0x42924bu; native_call(m, 0x41ef60u);	/* 429246: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42924b: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42924e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429250: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429252: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429257: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42925bu; native_call(m, m->esi);	/* 429259: call esi */
	m->ecx = M32((DWORD)(0x4e0458u));	/* 42925b: mov ecx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->ecx*4 + 0x4b065cu));	/* 429261: mov eax, dword ptr [ecx*4 + 0x4b065c] */
	m->ecx = 0x140u;	/* 429268: mov ecx, 0x140 */
	m->edx = m->eax;	/* 42926d: mov edx, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42926f: sub ecx, eax */
	{ DWORD a_ = m->edx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->edx = r_; }	/* 429271: neg edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429273: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429274: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42927au; native_call(m, 0x41ef60u);	/* 429275: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42927a: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42927d: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429282: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429284: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429289: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42928du; native_call(m, m->esi);	/* 42928b: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 42928d: mov edx, dword ptr [0x4e0458] */
	m->ecx = 0xf0u;	/* 429293: mov ecx, 0xf0 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429298: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->edx = 0x140u;	/* 42929f: mov edx, 0x140 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4292a4: sub ecx, eax */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4292a6: sub edx, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4292a8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4292a9: push edx */
	m->esp -= 4; M32(m->esp) = 0x4292afu; native_call(m, 0x41ef60u);	/* 4292aa: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4292af: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4292b2: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4292b7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4292b9: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4292bb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4292bfu; native_call(m, m->esi);	/* 4292bd: call esi */
	m->eax = M32((DWORD)(0x4e0458u));	/* 4292bf: mov eax, dword ptr [0x4e0458] */
	m->ecx = 0xf0u;	/* 4292c4: mov ecx, 0xf0 */
	m->eax = M32((DWORD)(m->eax*4 + 0x4b065cu));	/* 4292c9: mov eax, dword ptr [eax*4 + 0x4b065c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4292d0: sub ecx, eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 4292d2: neg eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4292d4: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4292d5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4292dbu; native_call(m, 0x41ef60u);	/* 4292d6: call 0x41ef60 */
	m->ebx = M32((DWORD)(0x4a9220u));	/* 4292db: mov ebx, dword ptr [0x4a9220] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4292e1: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4292e6u; native_call(m, m->ebx);	/* 4292e4: call ebx */
	m->eax = M32((DWORD)(0x9dad70u));	/* 4292e6: mov eax, dword ptr [0x9dad70] */
	m->edx = m->eax;	/* 4292eb: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4292ed: and edx, 0x800001ff */
	if (!m->sf) goto L_4292fd;	/* 4292f3: jns 0x4292fd */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4292f5: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4292f6: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4292fc: inc edx */
L_4292fd:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4292fd: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4292fe: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 429304: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429305: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42930b: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42930d: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 429310: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x429319u; native_call(m, 0x4566c0u);	/* 429314: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429319: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42931du; native_call(m, m->edi);	/* 42931b: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42931d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42931f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429321: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429323: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429327u; native_call(m, m->esi);	/* 429325: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 429327: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 42932d: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = m->eax;	/* 429334: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0x140u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429336: add eax, 0x140 */
	{ DWORD a_ = m->ecx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->ecx = r_; }	/* 42933b: neg ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42933d: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42933e: push eax */
	m->esp -= 4; M32(m->esp) = 0x429344u; native_call(m, 0x41ef60u);	/* 42933f: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429344: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429347: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429349: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42934b: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429350: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429354u; native_call(m, m->esi);	/* 429352: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 429354: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 42935a: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = m->eax;	/* 429361: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0x280u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429363: add eax, 0x280 */
	{ DWORD a_ = m->ecx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->ecx = r_; }	/* 429368: neg ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42936a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42936b: push eax */
	m->esp -= 4; M32(m->esp) = 0x429371u; native_call(m, 0x41ef60u);	/* 42936c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429371: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429374: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429379: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42937b: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429380: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429384u; native_call(m, m->esi);	/* 429382: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 429384: mov edx, dword ptr [0x4e0458] */
	m->ecx = 0xf0u;	/* 42938a: mov ecx, 0xf0 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 42938f: mov eax, dword ptr [edx*4 + 0x4b065c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 429396: sub ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0x280u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429398: add eax, 0x280 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42939d: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42939e: push eax */
	m->esp -= 4; M32(m->esp) = 0x4293a4u; native_call(m, 0x41ef60u);	/* 42939f: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4293a4: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4293a7: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4293ac: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4293ae: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4293b0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4293b4u; native_call(m, m->esi);	/* 4293b2: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 4293b4: mov edx, dword ptr [0x4e0458] */
	m->ecx = 0xf0u;	/* 4293ba: mov ecx, 0xf0 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 4293bf: mov eax, dword ptr [edx*4 + 0x4b065c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4293c6: sub ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0x140u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4293c8: add eax, 0x140 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4293cd: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4293ce: push eax */
	m->esp -= 4; M32(m->esp) = 0x4293d4u; native_call(m, 0x41ef60u);	/* 4293cf: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4293d4: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4293d9u; native_call(m, m->ebx);	/* 4293d7: call ebx */
	m->eax = M32((DWORD)(0x9dad74u));	/* 4293d9: mov eax, dword ptr [0x9dad74] */
	m->edx = m->eax;	/* 4293de: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4293e0: and edx, 0x800001ff */
	if (!m->sf) goto L_4293f0;	/* 4293e6: jns 0x4293f0 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4293e8: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4293e9: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4293ef: inc edx */
L_4293f0:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4293f0: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4293f1: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4293f7: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4293f8: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4293fe: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429400: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 429403: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x42940cu; native_call(m, 0x4566c0u);	/* 429407: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42940c: push 7 */
	m->esp -= 4; M32(m->esp) = 0x429410u; native_call(m, m->edi);	/* 42940e: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429410: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429412: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429414: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429416: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42941au; native_call(m, m->esi);	/* 429418: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 42941a: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429420: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0xf0u);	/* 429427: lea ecx, [eax + 0xf0] */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 42942d: neg eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42942f: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429430: push eax */
	m->esp -= 4; M32(m->esp) = 0x429436u; native_call(m, 0x41ef60u);	/* 429431: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429436: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429439: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42943b: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42943d: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429442: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429446u; native_call(m, m->esi);	/* 429444: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 429446: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 42944c: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->edx = 0x140u;	/* 429453: mov edx, 0x140 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 429458: sub edx, eax */
	m->ecx = (DWORD)(m->eax + 0xf0u);	/* 42945a: lea ecx, [eax + 0xf0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429460: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429461: push edx */
	m->esp -= 4; M32(m->esp) = 0x429467u; native_call(m, 0x41ef60u);	/* 429462: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429467: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42946a: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42946f: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429471: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429476: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42947au; native_call(m, m->esi);	/* 429478: call esi */
	m->eax = M32((DWORD)(0x4e0458u));	/* 42947a: mov eax, dword ptr [0x4e0458] */
	m->edx = 0x140u;	/* 42947f: mov edx, 0x140 */
	m->eax = M32((DWORD)(m->eax*4 + 0x4b065cu));	/* 429484: mov eax, dword ptr [eax*4 + 0x4b065c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42948b: sub edx, eax */
	m->ecx = (DWORD)(m->eax + 0x1e0u);	/* 42948d: lea ecx, [eax + 0x1e0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429493: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429494: push edx */
	m->esp -= 4; M32(m->esp) = 0x42949au; native_call(m, 0x41ef60u);	/* 429495: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42949a: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42949d: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4294a2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4294a4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4294a6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4294aau; native_call(m, m->esi);	/* 4294a8: call esi */
	m->eax = M32((DWORD)(0x4e0458u));	/* 4294aa: mov eax, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->eax*4 + 0x4b065cu));	/* 4294af: mov eax, dword ptr [eax*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0x1e0u);	/* 4294b6: lea ecx, [eax + 0x1e0] */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 4294bc: neg eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4294be: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4294bf: push eax */
	m->esp -= 4; M32(m->esp) = 0x4294c5u; native_call(m, 0x41ef60u);	/* 4294c0: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4294c5: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4294cau; native_call(m, m->ebx);	/* 4294c8: call ebx */
	m->eax = M32((DWORD)(0x9dad78u));	/* 4294ca: mov eax, dword ptr [0x9dad78] */
	m->edx = m->eax;	/* 4294cf: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4294d1: and edx, 0x800001ff */
	if (!m->sf) goto L_4294e1;	/* 4294d7: jns 0x4294e1 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4294d9: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4294da: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4294e0: inc edx */
L_4294e1:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4294e1: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4294e2: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4294e8: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4294e9: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4294ef: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4294f1: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4294f4: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4294fdu; native_call(m, 0x4566c0u);	/* 4294f8: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4294fd: push 7 */
	m->esp -= 4; M32(m->esp) = 0x429501u; native_call(m, m->edi);	/* 4294ff: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429501: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429503: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429505: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429507: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42950bu; native_call(m, m->esi);	/* 429509: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 42950b: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429511: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0xf0u);	/* 429518: lea ecx, [eax + 0xf0] */
	{ DWORD a_ = m->eax, b_ = 0x140u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42951e: add eax, 0x140 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429523: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429524: push eax */
	m->esp -= 4; M32(m->esp) = 0x42952au; native_call(m, 0x41ef60u);	/* 429525: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42952a: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42952d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42952f: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429531: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429536: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42953au; native_call(m, m->esi);	/* 429538: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 42953a: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429540: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0xf0u);	/* 429547: lea ecx, [eax + 0xf0] */
	{ DWORD a_ = m->eax, b_ = 0x280u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42954d: add eax, 0x280 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429552: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429553: push eax */
	m->esp -= 4; M32(m->esp) = 0x429559u; native_call(m, 0x41ef60u);	/* 429554: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429559: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42955c: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429561: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429563: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429568: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42956cu; native_call(m, m->esi);	/* 42956a: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 42956c: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429572: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0x1e0u);	/* 429579: lea ecx, [eax + 0x1e0] */
	{ DWORD a_ = m->eax, b_ = 0x280u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42957f: add eax, 0x280 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429584: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429585: push eax */
	m->esp -= 4; M32(m->esp) = 0x42958bu; native_call(m, 0x41ef60u);	/* 429586: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42958b: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42958e: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429593: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429595: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429597: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42959bu; native_call(m, m->esi);	/* 429599: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 42959b: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 4295a1: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0x1e0u);	/* 4295a8: lea ecx, [eax + 0x1e0] */
	{ DWORD a_ = m->eax, b_ = 0x140u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4295ae: add eax, 0x140 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4295b3: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4295b4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4295bau; native_call(m, 0x41ef60u);	/* 4295b5: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4295ba: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4295bfu; native_call(m, m->ebx);	/* 4295bd: call ebx */
	m->eax = M32((DWORD)(0x4df01cu));	/* 4295bf: mov eax, dword ptr [0x4df01c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4295c4: test eax, eax */
	if (m->zf) goto L_4295e0;	/* 4295c6: je 0x4295e0 */
	FPUSH((long double)(int)M32((DWORD)(0x4e0458u)));	/* 4295c8: fild dword ptr [0x4e0458] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4295ce: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9530u));	/* 4295cf: fmul dword ptr [0x4a9530] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4295d5: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4295db: fstp dword ptr [esp] */
	goto L_429623;	/* 4295de: jmp 0x429623 */
L_4295e0:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de1e0u)));	/* 4295e0: fld dword ptr [0x4de1e0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 4295e6: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4295ec: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4295ee: test ah, 0x41 */
	if (!m->zf) goto L_4295ff;	/* 4295f1: jne 0x4295ff */
	M32((DWORD)(0x4de1e0u)) = 0x3f800000u;	/* 4295f3: mov dword ptr [0x4de1e0], 0x3f800000 */
	goto L_42961c;	/* 4295fd: jmp 0x42961c */
L_4295ff:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de1e0u)));	/* 4295ff: fld dword ptr [0x4de1e0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 429605: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42960b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42960d: test ah, 1 */
	if (m->zf) goto L_42961c;	/* 429610: je 0x42961c */
	M32((DWORD)(0x4de1e0u)) = 0x0u;	/* 429612: mov dword ptr [0x4de1e0], 0 */
L_42961c:
	m->edx = M32((DWORD)(0x4de1e0u));	/* 42961c: mov edx, dword ptr [0x4de1e0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429622: push edx */
L_429623:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429623: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429628: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42962d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x429634u; native_call(m, m->ebp);	/* 429632: call ebp */
	m->eax = M32((DWORD)(0x9dad7cu));	/* 429634: mov eax, dword ptr [0x9dad7c] */
	m->ecx = m->eax;	/* 429639: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42963b: and ecx, 0x800001ff */
	if (!m->sf) goto L_42964b;	/* 429641: jns 0x42964b */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 429643: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 429644: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 42964a: inc ecx */
L_42964b:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 42964b: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42964c: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429652: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429653: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 429655: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42965b: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 42965e: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x429667u; native_call(m, 0x4566c0u);	/* 429662: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429667: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42966bu; native_call(m, m->edi);	/* 429669: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42966b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42966d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42966f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429671: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429675u; native_call(m, m->esi);	/* 429673: call esi */
	m->eax = M32((DWORD)(0x4e0458u));	/* 429675: mov eax, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->eax*4 + 0x4b065cu));	/* 42967a: mov eax, dword ptr [eax*4 + 0x4b065c] */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 429681: neg eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429683: push eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429684: push eax */
	m->esp -= 4; M32(m->esp) = 0x42968au; native_call(m, 0x41ef60u);	/* 429685: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42968a: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42968d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42968f: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429691: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429696: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42969au; native_call(m, m->esi);	/* 429698: call esi */
	m->ecx = M32((DWORD)(0x4e0458u));	/* 42969a: mov ecx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->ecx*4 + 0x4b065cu));	/* 4296a0: mov eax, dword ptr [ecx*4 + 0x4b065c] */
	m->ecx = 0x141u;	/* 4296a7: mov ecx, 0x141 */
	m->edx = m->eax;	/* 4296ac: mov edx, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4296ae: sub ecx, eax */
	{ DWORD a_ = m->edx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->edx = r_; }	/* 4296b0: neg edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4296b2: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4296b3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4296b9u; native_call(m, 0x41ef60u);	/* 4296b4: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4296b9: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4296bc: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4296c1: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4296c3: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4296c8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4296ccu; native_call(m, m->esi);	/* 4296ca: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 4296cc: mov edx, dword ptr [0x4e0458] */
	m->ecx = 0xf1u;	/* 4296d2: mov ecx, 0xf1 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 4296d7: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->edx = 0x141u;	/* 4296de: mov edx, 0x141 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4296e3: sub ecx, eax */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4296e5: sub edx, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4296e7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4296e8: push edx */
	m->esp -= 4; M32(m->esp) = 0x4296eeu; native_call(m, 0x41ef60u);	/* 4296e9: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4296ee: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4296f1: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4296f6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4296f8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4296fa: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4296feu; native_call(m, m->esi);	/* 4296fc: call esi */
	m->eax = M32((DWORD)(0x4e0458u));	/* 4296fe: mov eax, dword ptr [0x4e0458] */
	m->ecx = 0xf1u;	/* 429703: mov ecx, 0xf1 */
	m->eax = M32((DWORD)(m->eax*4 + 0x4b065cu));	/* 429708: mov eax, dword ptr [eax*4 + 0x4b065c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42970f: sub ecx, eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 429711: neg eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429713: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429714: push eax */
	m->esp -= 4; M32(m->esp) = 0x42971au; native_call(m, 0x41ef60u);	/* 429715: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42971a: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x42971fu; native_call(m, m->ebx);	/* 42971d: call ebx */
	m->eax = M32((DWORD)(0x9dad80u));	/* 42971f: mov eax, dword ptr [0x9dad80] */
	m->edx = m->eax;	/* 429724: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429726: and edx, 0x800001ff */
	if (!m->sf) goto L_429736;	/* 42972c: jns 0x429736 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 42972e: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42972f: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 429735: inc edx */
L_429736:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429736: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 429737: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 42973d: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42973e: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429744: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429746: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 429749: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x429752u; native_call(m, 0x4566c0u);	/* 42974d: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429752: push 7 */
	m->esp -= 4; M32(m->esp) = 0x429756u; native_call(m, m->edi);	/* 429754: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429756: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429758: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42975a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42975c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429760u; native_call(m, m->esi);	/* 42975e: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 429760: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429766: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = m->eax;	/* 42976d: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0x13fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42976f: add eax, 0x13f */
	{ DWORD a_ = m->ecx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->ecx = r_; }	/* 429774: neg ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429776: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429777: push eax */
	m->esp -= 4; M32(m->esp) = 0x42977du; native_call(m, 0x41ef60u);	/* 429778: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42977d: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429780: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429782: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429784: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429789: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42978du; native_call(m, m->esi);	/* 42978b: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 42978d: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429793: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = m->eax;	/* 42979a: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0x280u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42979c: add eax, 0x280 */
	{ DWORD a_ = m->ecx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->ecx = r_; }	/* 4297a1: neg ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4297a3: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4297a4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4297aau; native_call(m, 0x41ef60u);	/* 4297a5: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4297aa: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4297ad: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4297b2: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4297b4: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4297b9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4297bdu; native_call(m, m->esi);	/* 4297bb: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 4297bd: mov edx, dword ptr [0x4e0458] */
	m->ecx = 0xf1u;	/* 4297c3: mov ecx, 0xf1 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 4297c8: mov eax, dword ptr [edx*4 + 0x4b065c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4297cf: sub ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0x280u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4297d1: add eax, 0x280 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4297d6: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4297d7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4297ddu; native_call(m, 0x41ef60u);	/* 4297d8: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4297dd: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4297e0: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4297e5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4297e7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4297e9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4297edu; native_call(m, m->esi);	/* 4297eb: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 4297ed: mov edx, dword ptr [0x4e0458] */
	m->ecx = 0xf1u;	/* 4297f3: mov ecx, 0xf1 */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 4297f8: mov eax, dword ptr [edx*4 + 0x4b065c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4297ff: sub ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0x13fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429801: add eax, 0x13f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429806: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429807: push eax */
	m->esp -= 4; M32(m->esp) = 0x42980du; native_call(m, 0x41ef60u);	/* 429808: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42980d: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x429812u; native_call(m, m->ebx);	/* 429810: call ebx */
	m->eax = M32((DWORD)(0x9dad84u));	/* 429812: mov eax, dword ptr [0x9dad84] */
	m->edx = m->eax;	/* 429817: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429819: and edx, 0x800001ff */
	if (!m->sf) goto L_429829;	/* 42981f: jns 0x429829 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 429821: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429822: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 429828: inc edx */
L_429829:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429829: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 42982a: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 429830: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429831: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429837: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429839: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 42983c: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x429845u; native_call(m, 0x4566c0u);	/* 429840: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429845: push 7 */
	m->esp -= 4; M32(m->esp) = 0x429849u; native_call(m, m->edi);	/* 429847: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429849: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42984b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42984d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42984f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429853u; native_call(m, m->esi);	/* 429851: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 429853: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429859: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 429860: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 429866: neg eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429868: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 429869: push eax */
	m->esp -= 4; M32(m->esp) = 0x42986fu; native_call(m, 0x41ef60u);	/* 42986a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42986f: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429872: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429874: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429876: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42987b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42987fu; native_call(m, m->esi);	/* 42987d: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 42987f: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429885: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->edx = 0x141u;	/* 42988c: mov edx, 0x141 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 429891: sub edx, eax */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 429893: lea ecx, [eax + 0xef] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429899: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42989a: push edx */
	m->esp -= 4; M32(m->esp) = 0x4298a0u; native_call(m, 0x41ef60u);	/* 42989b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4298a0: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4298a3: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4298a8: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4298aa: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4298af: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4298b3u; native_call(m, m->esi);	/* 4298b1: call esi */
	m->eax = M32((DWORD)(0x4e0458u));	/* 4298b3: mov eax, dword ptr [0x4e0458] */
	m->edx = 0x141u;	/* 4298b8: mov edx, 0x141 */
	m->eax = M32((DWORD)(m->eax*4 + 0x4b065cu));	/* 4298bd: mov eax, dword ptr [eax*4 + 0x4b065c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4298c4: sub edx, eax */
	m->ecx = (DWORD)(m->eax + 0x1e0u);	/* 4298c6: lea ecx, [eax + 0x1e0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4298cc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4298cd: push edx */
	m->esp -= 4; M32(m->esp) = 0x4298d3u; native_call(m, 0x41ef60u);	/* 4298ce: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4298d3: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4298d6: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4298db: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4298dd: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4298df: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4298e3u; native_call(m, m->esi);	/* 4298e1: call esi */
	m->eax = M32((DWORD)(0x4e0458u));	/* 4298e3: mov eax, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->eax*4 + 0x4b065cu));	/* 4298e8: mov eax, dword ptr [eax*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0x1e0u);	/* 4298ef: lea ecx, [eax + 0x1e0] */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 4298f5: neg eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4298f7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4298f8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4298feu; native_call(m, 0x41ef60u);	/* 4298f9: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4298fe: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x429903u; native_call(m, m->ebx);	/* 429901: call ebx */
	m->eax = M32((DWORD)(0x9dad88u));	/* 429903: mov eax, dword ptr [0x9dad88] */
	m->edx = m->eax;	/* 429908: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42990a: and edx, 0x800001ff */
	if (!m->sf) goto L_42991a;	/* 429910: jns 0x42991a */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 429912: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429913: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 429919: inc edx */
L_42991a:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42991a: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 42991b: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 429921: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429922: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429928: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 42992a: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 42992d: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x429936u; native_call(m, 0x4566c0u);	/* 429931: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429936: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42993au; native_call(m, m->edi);	/* 429938: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42993a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42993c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42993e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429940: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429944u; native_call(m, m->esi);	/* 429942: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 429944: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 42994a: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 429951: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, b_ = 0x13fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429957: add eax, 0x13f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42995c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42995d: push eax */
	m->esp -= 4; M32(m->esp) = 0x429963u; native_call(m, 0x41ef60u);	/* 42995e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429963: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429966: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429968: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42996a: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42996f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429973u; native_call(m, m->esi);	/* 429971: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 429973: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 429979: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0xefu);	/* 429980: lea ecx, [eax + 0xef] */
	{ DWORD a_ = m->eax, b_ = 0x280u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429986: add eax, 0x280 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42998b: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42998c: push eax */
	m->esp -= 4; M32(m->esp) = 0x429992u; native_call(m, 0x41ef60u);	/* 42998d: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429992: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429995: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42999a: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42999c: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4299a1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4299a5u; native_call(m, m->esi);	/* 4299a3: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 4299a5: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 4299ab: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0x1e0u);	/* 4299b2: lea ecx, [eax + 0x1e0] */
	{ DWORD a_ = m->eax, b_ = 0x280u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4299b8: add eax, 0x280 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4299bd: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4299be: push eax */
	m->esp -= 4; M32(m->esp) = 0x4299c4u; native_call(m, 0x41ef60u);	/* 4299bf: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4299c4: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4299c7: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4299cc: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4299ce: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4299d0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4299d4u; native_call(m, m->esi);	/* 4299d2: call esi */
	m->edx = M32((DWORD)(0x4e0458u));	/* 4299d4: mov edx, dword ptr [0x4e0458] */
	m->eax = M32((DWORD)(m->edx*4 + 0x4b065cu));	/* 4299da: mov eax, dword ptr [edx*4 + 0x4b065c] */
	m->ecx = (DWORD)(m->eax + 0x1e0u);	/* 4299e1: lea ecx, [eax + 0x1e0] */
	{ DWORD a_ = m->eax, b_ = 0x13fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4299e7: add eax, 0x13f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4299ec: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4299ed: push eax */
	m->esp -= 4; M32(m->esp) = 0x4299f3u; native_call(m, 0x41ef60u);	/* 4299ee: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4299f3: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4299f8u; native_call(m, m->ebx);	/* 4299f6: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de1d8u)));	/* 4299f8: fld dword ptr [0x4de1d8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 4299fe: fmul dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4de1e0u));	/* 429a04: fadd dword ptr [0x4de1e0] */
	MF((DWORD)(0x4de1e0u)) = (float)ST(0);	/* 429a0a: fst dword ptr [0x4de1e0] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(0x4a9528u)); FPOP();	/* 429a10: fcomp qword ptr [0x4a9528] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 429a16: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 429a18: test ah, 0x41 */
	if (!m->zf) goto L_429a31;	/* 429a1b: jne 0x429a31 */
	M32((DWORD)(0x4de1e0u)) = 0x3f666666u;	/* 429a1d: mov dword ptr [0x4de1e0], 0x3f666666 */
	M32((DWORD)(0x4de1d8u)) = 0xbc9374bcu;	/* 429a27: mov dword ptr [0x4de1d8], 0xbc9374bc */
L_429a31:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de1e0u)));	/* 429a31: fld dword ptr [0x4de1e0] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(0x4a9520u)); FPOP();	/* 429a37: fcomp qword ptr [0x4a9520] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 429a3d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 429a3f: test ah, 1 */
	if (m->zf) goto L_429a58;	/* 429a42: je 0x429a58 */
	M32((DWORD)(0x4de1d8u)) = 0x3c9374bcu;	/* 429a44: mov dword ptr [0x4de1d8], 0x3c9374bc */
	M32((DWORD)(0x4de1e0u)) = 0x3e4ccccdu;	/* 429a4e: mov dword ptr [0x4de1e0], 0x3e4ccccd */
L_429a58:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 429a58: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 429a5e: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4de1e8u));	/* 429a64: fadd dword ptr [0x4de1e8] */
	MF((DWORD)(0x4de1e8u)) = (float)ST(0);	/* 429a6a: fst dword ptr [0x4de1e8] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(0x4a94e0u)); FPOP();	/* 429a70: fcomp qword ptr [0x4a94e0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 429a76: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 429a78: test ah, 1 */
	if (!m->zf) goto L_429a87;	/* 429a7b: jne 0x429a87 */
	M32((DWORD)(0x4de1e8u)) = 0x3f800000u;	/* 429a7d: mov dword ptr [0x4de1e8], 0x3f800000 */
L_429a87:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de1e8u)));	/* 429a87: fld dword ptr [0x4de1e8] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(0x4a9520u)); FPOP();	/* 429a8d: fcomp qword ptr [0x4a9520] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 429a93: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 429a95: test ah, 1 */
	if (!m->zf) goto L_429ac5;	/* 429a98: jne 0x429ac5 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de1e8u)));	/* 429a9a: fld dword ptr [0x4de1e8] */
	ST(0) = ST(0) + ST(0);	/* 429aa0: fadd st(0), st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 429aa2: fsub dword ptr [0x4a94f8] */
	MF((DWORD)(0x4de1ecu)) = (float)ST(0);	/* 429aa8: fst dword ptr [0x4de1ec] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 429aae: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 429ab4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 429ab6: test ah, 0x41 */
	if (!m->zf) goto L_429ac5;	/* 429ab9: jne 0x429ac5 */
	M32((DWORD)(0x4de1ecu)) = 0x3f800000u;	/* 429abb: mov dword ptr [0x4de1ec], 0x3f800000 */
L_429ac5:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4de1e8u)));	/* 429ac5: fld dword ptr [0x4de1e8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 429acb: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 429ad1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 429ad3: test ah, 1 */
	if (m->zf) goto L_429bac;	/* 429ad6: je 0x429bac */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 429adc: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4de1e8u));	/* 429ae2: fsub dword ptr [0x4de1e8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 429ae8: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 429ae9: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429aec: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429af1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429af6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x429afdu; native_call(m, m->ebp);	/* 429afb: call ebp */
	m->eax = M32((DWORD)(0x76d3f0u));	/* 429afd: mov eax, dword ptr [0x76d3f0] */
	m->edx = m->eax;	/* 429b02: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429b04: and edx, 0x800001ff */
	if (!m->sf) goto L_429b14;	/* 429b0a: jns 0x429b14 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 429b0c: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429b0d: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 429b13: inc edx */
L_429b14:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 429b14: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 429b15: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 429b1b: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 429b1c: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 429b22: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 429b24: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 429b27: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x429b30u; native_call(m, 0x4566c0u);	/* 429b2b: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b30: push 7 */
	m->esp -= 4; M32(m->esp) = 0x429b34u; native_call(m, m->edi);	/* 429b32: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b34: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b36: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b38: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b3a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429b3eu; native_call(m, m->esi);	/* 429b3c: call esi */
	{ DWORD v_ = 0x3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 429b3e: push 0x3c */
	{ DWORD v_ = 0xa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b40: push 0xa0 */
	m->esp -= 4; M32(m->esp) = 0x429b4au; native_call(m, 0x41ef60u);	/* 429b45: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429b4a: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b4d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b4f: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b51: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b56: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429b5au; native_call(m, m->esi);	/* 429b58: call esi */
	{ DWORD v_ = 0x3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 429b5a: push 0x3c */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b5c: push 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x429b66u; native_call(m, 0x41ef60u);	/* 429b61: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429b66: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b69: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b6e: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b70: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b75: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429b79u; native_call(m, m->esi);	/* 429b77: call esi */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 429b79: push 0x13c */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b7e: push 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x429b88u; native_call(m, 0x41ef60u);	/* 429b83: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429b88: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b8b: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b90: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b92: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b94: push 0 */
	m->esp -= 4; M32(m->esp) = 0x429b98u; native_call(m, m->esi);	/* 429b96: call esi */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 429b98: push 0x13c */
	{ DWORD v_ = 0xa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 429b9d: push 0xa0 */
	m->esp -= 4; M32(m->esp) = 0x429ba7u; native_call(m, 0x41ef60u);	/* 429ba2: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 429ba7: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x429bacu; native_call(m, m->ebx);	/* 429baa: call ebx */
L_429bac:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 429bac: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x429bb7u; native_call(m, M32(0x4a922cu));	/* 429bb1: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 429bb7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 429bb8: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 429bb9: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 429bba: pop ebx */
	m->esp += 4 + 0; return;	/* 429bbb: ret  */
}

/* hud_drawFps (0x495510), lifted by tools/lift.py */
static void lift_495510(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495510: sub esp, 0x100 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 495516: push esi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495517: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49551c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495521: push 0x3f800000 */
	m->esi = m->ecx;	/* 495526: mov esi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495528: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495533u; native_call(m, M32(0x4a9228u));	/* 49552d: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 495533: push 3 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495535: push 8 */
	{ DWORD v_ = 0x1d9u; m->esp -= 4; M32(m->esp) = v_; }	/* 495537: push 0x1d9 */
	m->ecx = m->esi;	/* 49553c: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x495543u; native_call(m, 0x496820u);	/* 49553e: call 0x496820 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495543: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495548: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49554d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495552: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x49555cu; native_call(m, 0x44ad30u);	/* 495557: call 0x44ad30 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x38u)));	/* 49555c: fld dword ptr [esi + 0x38] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49555f: add esp, 8 */
	m->eax = (DWORD)(m->esp + 0xcu);	/* 495562: lea eax, [esp + 0xc] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 495566: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4d0434u; m->esp -= 4; M32(m->esp) = v_; }	/* 495569: push 0x4d0434 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49556e: push eax */
	m->esp -= 4; M32(m->esp) = 0x495574u; native_call(m, 0x49e9ddu);	/* 49556f: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 495574: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495578: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49557a: push ecx */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 49557b: push 8 */
	{ DWORD v_ = 0x1f1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49557d: push 0x1f1 */
	m->esp -= 4; M32(m->esp) = 0x495587u; native_call(m, 0x44ad60u);	/* 495582: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495587: add esp, 0x20 */
	m->esi = M32(m->esp); m->esp += 4;	/* 49558a: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49558b: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 495591: ret  */
}

/* hud_4953d0 (0x4953d0), lifted by tools/lift.py */
static void lift_4953d0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4953d0: sub esp, 0x100 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4953d6: push esi */
	m->esi = m->ecx;	/* 4953d7: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x2340d35u));	/* 4953d9: mov eax, dword ptr [esi + 0x2340d35] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4953df: dec eax */
	if (m->zf) goto L_49547e;	/* 4953e0: je 0x49547e */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4953e6: dec eax */
	if (!m->zf) goto L_495502;	/* 4953e7: jne 0x495502 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4953ed: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4953f2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4953f4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4953f6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4953feu; native_call(m, M32(0x4a9228u));	/* 4953f8: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x188u; m->esp -= 4; M32(m->esp) = v_; }	/* 4953fe: push 0x188 */
	{ DWORD v_ = 0x230u; m->esp -= 4; M32(m->esp) = v_; }	/* 495403: push 0x230 */
	{ DWORD v_ = 0x158u; m->esp -= 4; M32(m->esp) = v_; }	/* 495408: push 0x158 */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 49540d: push 0x50 */
	m->esp -= 4; M32(m->esp) = 0x495414u; native_call(m, 0x4950a0u);	/* 49540f: call 0x4950a0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495414: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495419: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49541e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495423: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x49542du; native_call(m, 0x44ad30u);	/* 495428: call 0x44ad30 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc34u)));	/* 49542d: fld dword ptr [esi + 0x233cc34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 495433: fcomp dword ptr [0x4a942c] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495439: add esp, 0x20 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49543c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49543e: test ah, 1 */
	if (m->zf) goto L_495461;	/* 495441: je 0x495461 */
L_495443:
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495443: push 8 */
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 495445: push 0x9dc92c */
	{ DWORD v_ = 0x168u; m->esp -= 4; M32(m->esp) = v_; }	/* 49544a: push 0x168 */
	{ DWORD v_ = 0x60u; m->esp -= 4; M32(m->esp) = v_; }	/* 49544f: push 0x60 */
	m->esp -= 4; M32(m->esp) = 0x495456u; native_call(m, 0x44ad60u);	/* 495451: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495456: add esp, 0x10 */
	m->esi = M32(m->esp); m->esp += 4;	/* 495459: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49545a: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 495460: ret  */
L_495461:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 495461: push 0x9dc92c */
	m->eax = (DWORD)(m->esp + 0x8u);	/* 495466: lea eax, [esp + 8] */
	{ DWORD v_ = 0x4d0430u; m->esp -= 4; M32(m->esp) = v_; }	/* 49546a: push 0x4d0430 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49546f: push eax */
	m->esp -= 4; M32(m->esp) = 0x495475u; native_call(m, 0x49e9ddu);	/* 495470: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 495475: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495479: push 8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49547b: push ecx */
	goto L_4954f3;	/* 49547c: jmp 0x4954f3 */
L_49547e:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49547e: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495483: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495485: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495487: push 0 */
	m->esp -= 4; M32(m->esp) = 0x49548fu; native_call(m, M32(0x4a9228u));	/* 495489: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x188u; m->esp -= 4; M32(m->esp) = v_; }	/* 49548f: push 0x188 */
	{ DWORD v_ = 0x230u; m->esp -= 4; M32(m->esp) = v_; }	/* 495494: push 0x230 */
	{ DWORD v_ = 0x158u; m->esp -= 4; M32(m->esp) = v_; }	/* 495499: push 0x158 */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 49549e: push 0x50 */
	m->esp -= 4; M32(m->esp) = 0x4954a5u; native_call(m, 0x4950a0u);	/* 4954a0: call 0x4950a0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4954a5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4954aa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4954af: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4954b4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4954beu; native_call(m, 0x44ad30u);	/* 4954b9: call 0x44ad30 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc34u)));	/* 4954be: fld dword ptr [esi + 0x233cc34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 4954c4: fcomp dword ptr [0x4a942c] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4954ca: add esp, 0x20 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4954cd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4954cf: test ah, 1 */
	if (!m->zf) goto L_495443;	/* 4954d2: jne 0x495443 */
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4954d8: push 0x9dc92c */
	m->edx = (DWORD)(m->esp + 0x8u);	/* 4954dd: lea edx, [esp + 8] */
	{ DWORD v_ = 0x4d0430u; m->esp -= 4; M32(m->esp) = v_; }	/* 4954e1: push 0x4d0430 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4954e6: push edx */
	m->esp -= 4; M32(m->esp) = 0x4954ecu; native_call(m, 0x49e9ddu);	/* 4954e7: call 0x49e9dd */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 4954ec: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4954f0: push 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4954f2: push eax */
L_4954f3:
	{ DWORD v_ = 0x168u; m->esp -= 4; M32(m->esp) = v_; }	/* 4954f3: push 0x168 */
	{ DWORD v_ = 0x60u; m->esp -= 4; M32(m->esp) = v_; }	/* 4954f8: push 0x60 */
	m->esp -= 4; M32(m->esp) = 0x4954ffu; native_call(m, 0x44ad60u);	/* 4954fa: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4954ff: add esp, 0x1c */
L_495502:
	m->esi = M32(m->esp); m->esp += 4;	/* 495502: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495503: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 495509: ret  */
}

/* replay_drawMessage (0x495190), lifted by tools/lift.py */
static void lift_495190(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495190: sub esp, 0x10c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495196: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 495197: push ebp */
	m->ebp = m->ecx;	/* 495198: mov ebp, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49519a: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49519b: push edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc40u)));	/* 49519c: fld dword ptr [ebp + 0x233cc40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 4951a2: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4951a8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4951aa: test ah, 1 */
	if (!m->zf) goto L_4951b9;	/* 4951ad: jne 0x4951b9 */
	M32((DWORD)(m->esp + 0x10u)) = 0x3f800000u;	/* 4951af: mov dword ptr [esp + 0x10], 0x3f800000 */
	goto L_4951e0;	/* 4951b7: jmp 0x4951e0 */
L_4951b9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc40u)));	/* 4951b9: fld dword ptr [ebp + 0x233cc40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4951bf: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4951c5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4951c7: test ah, 1 */
	if (!m->zf) goto L_4951d8;	/* 4951ca: jne 0x4951d8 */
	m->eax = M32((DWORD)(m->ebp + 0x233cc40u));	/* 4951cc: mov eax, dword ptr [ebp + 0x233cc40] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4951d2: mov dword ptr [esp + 0x10], eax */
	goto L_4951e0;	/* 4951d6: jmp 0x4951e0 */
L_4951d8:
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 4951d8: mov dword ptr [esp + 0x10], 0 */
L_4951e0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4951e0: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4951e4: fmul dword ptr [0x4a942c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4951ea: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4951eb: fstp dword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4951ee: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4951f0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4951f2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4951fau; native_call(m, M32(0x4a9228u));	/* 4951f4: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4951fa: push 0x6c */
	{ DWORD v_ = 0x264u; m->esp -= 4; M32(m->esp) = v_; }	/* 4951fc: push 0x264 */
	{ DWORD v_ = 0x24u; m->esp -= 4; M32(m->esp) = v_; }	/* 495201: push 0x24 */
	{ DWORD v_ = 0x1cu; m->esp -= 4; M32(m->esp) = v_; }	/* 495203: push 0x1c */
	m->esp -= 4; M32(m->esp) = 0x49520au; native_call(m, 0x4950a0u);	/* 495205: call 0x4950a0 */
	m->eax = M32((DWORD)(m->ebp + 0x233c59cu));	/* 49520a: mov eax, dword ptr [ebp + 0x233c59c] */
	m->ecx = M32((DWORD)(m->ebp + 0x233c598u));	/* 495210: mov ecx, dword ptr [ebp + 0x233c598] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495216: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495219: cmp eax, ecx */
	if (!m->cf) goto L_4952fa;	/* 49521b: jae 0x4952fa */
	{ DWORD a_ = m->eax, b_ = 0x1fu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 495221: and eax, 0x1f */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 495224: lea ecx, [eax + eax*4] */
	m->esi = (DWORD)(m->ebp + m->ecx*4 + 0x233c318u);	/* 495227: lea esi, [ebp + ecx*4 + 0x233c318] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49522e: test esi, esi */
	M32((DWORD)(m->esp + 0x18u)) = m->esi;	/* 495230: mov dword ptr [esp + 0x18], esi */
	if (m->zf) goto L_4952fa;	/* 495234: je 0x4952fa */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 49523a: mov dword ptr [esp + 0x14], 0 */
	m->ebx = 0x28u;	/* 495242: mov ebx, 0x28 */
	goto L_49524d;	/* 495247: jmp 0x49524d */
L_495249:
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 495249: mov esi, dword ptr [esp + 0x18] */
L_49524d:
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 49524d: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495250: cmp eax, 0x10 */
	if (m->sf == m->of) goto L_495274;	/* 495253: jge 0x495274 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 495255: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 495259: shl eax, 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49525c: push edx */
	m->ecx = M32((DWORD)(m->eax + 0xa1f108u));	/* 49525d: mov ecx, dword ptr [eax + 0xa1f108] */
	m->edx = M32((DWORD)(m->eax + 0xa1f104u));	/* 495263: mov edx, dword ptr [eax + 0xa1f104] */
	m->eax = M32((DWORD)(m->eax + 0xa1f100u));	/* 495269: mov eax, dword ptr [eax + 0xa1f100] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49526f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495270: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495271: push eax */
	goto L_495285;	/* 495272: jmp 0x495285 */
L_495274:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495274: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495276: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49527b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495280: push 0x3f800000 */
L_495285:
	m->esp -= 4; M32(m->esp) = 0x49528au; native_call(m, 0x44ad30u);	/* 495285: call 0x44ad30 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 49528a: mov eax, dword ptr [esi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 49528d: mov edx, dword ptr [esp + 0x24] */
	m->ecx = m->eax;	/* 495291: mov ecx, eax */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495293: add esp, 0x10 */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 495296: shl ecx, 5 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 495299: add ecx, eax */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 49529b: push 8 */
	m->eax = (DWORD)(m->edx + m->ecx*8 + 0x0u);	/* 49529d: lea eax, [edx + ecx*8] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4952a0: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 4952a3: lea edx, [esp + 0x20] */
	m->edi = (DWORD)(m->eax + m->ebp*1 + 0x22fbbd8u);	/* 4952a7: lea edi, [eax + ebp + 0x22fbbd8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4952ae: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4952b0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4952b2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4952b4: sub edi, ecx */
	m->eax = m->ecx;	/* 4952b6: mov eax, ecx */
	m->esi = m->edi;	/* 4952b8: mov esi, edi */
	m->edi = m->edx;	/* 4952ba: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4952bc: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4952bf: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4952c1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4952c3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4952c6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 4952c8: lea ecx, [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4952cc: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4952cd: push ebx */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 4952ce: push 0x20 */
	m->esp -= 4; M32(m->esp) = 0x4952d5u; native_call(m, 0x44ad60u);	/* 4952d0: call 0x44ad60 */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 4952d5: mov edx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ebx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4952d9: add ebx, 0x10 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4952dc: add esp, 0x10 */
	{ DWORD a_ = m->edx, b_ = 0x41u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4952df: add edx, 0x41 */
	{ DWORD a_ = m->ebx, b_ = 0x68u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4952e2: cmp ebx, 0x68 */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 4952e5: mov dword ptr [esp + 0x14], edx */
	if (m->sf != m->of) goto L_495249;	/* 4952e9: jl 0x495249 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4952ef: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4952f0: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4952f1: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4952f2: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4952f3: add esp, 0x10c */
	m->esp += 4 + 0; return;	/* 4952f9: ret  */
L_4952fa:
	m->esi = M32((DWORD)(m->ebp + 0x2342efau));	/* 4952fa: mov esi, dword ptr [ebp + 0x2342efa] */
	m->eax = M32((DWORD)(m->ebp + 0x2342ef6u));	/* 495300: mov eax, dword ptr [ebp + 0x2342ef6] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495306: cmp esi, eax */
	if (!m->cf) goto L_4953a9;	/* 495308: jae 0x4953a9 */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 49530e: mov edi, dword ptr [esp + 0x10] */
L_495312:
	m->eax = m->esi;	/* 495312: mov eax, esi */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 495314: xor edx, edx */
	m->ecx = 0x5u;	/* 495316: mov ecx, 5 */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 49531b: div ecx */
	m->eax = m->edx;	/* 49531d: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49531f: shl eax, 5 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 495322: add eax, edx */
	m->ebx = (DWORD)(m->ebp + m->eax*8 + 0x23429ceu);	/* 495324: lea ebx, [ebp + eax*8 + 0x23429ce] */
	m->eax = M32((DWORD)(m->ebp + m->eax*8 + 0x23429ceu));	/* 49532b: mov eax, dword ptr [ebp + eax*8 + 0x23429ce] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495332: cmp eax, ecx */
	if (!m->cf && !m->zf) goto L_495379;	/* 495334: ja 0x495379 */
	switch (m->eax) { case 0: goto L_49533d; case 1: goto L_495349; case 2: goto L_495351; case 3: goto L_49535d; case 4: goto L_495364; case 5: goto L_495364; default: abort(); }	/* 495336: jmp dword ptr [eax*4 + 0x4953b4] */
L_49533d:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49533d: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49533e: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495340: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495345: push 0 */
	goto L_495371;	/* 495347: jmp 0x495371 */
L_495349:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495349: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49534a: push 0x3f800000 */
	goto L_495367;	/* 49534f: jmp 0x495367 */
L_495351:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495351: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495352: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495357: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495359: push 0 */
	goto L_495371;	/* 49535b: jmp 0x495371 */
L_49535d:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49535d: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49535e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495360: push 0 */
	goto L_49536c;	/* 495362: jmp 0x49536c */
L_495364:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495364: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495365: push 0 */
L_495367:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495367: push 0x3f800000 */
L_49536c:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49536c: push 0x3f800000 */
L_495371:
	m->esp -= 4; M32(m->esp) = 0x495376u; native_call(m, 0x44ad30u);	/* 495371: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495376: add esp, 0x10 */
L_495379:
	m->eax = M32((DWORD)(m->ebp + 0x2342efau));	/* 495379: mov eax, dword ptr [ebp + 0x2342efa] */
	m->ecx = m->esi;	/* 49537f: mov ecx, esi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 495381: sub ecx, eax */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 495383: add ebx, 4 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 495386: shl ecx, 4 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495389: push 8 */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49538b: add ecx, 0x28 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49538e: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49538f: push ecx */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 495390: push 0x20 */
	m->esp -= 4; M32(m->esp) = 0x495397u; native_call(m, 0x44ad60u);	/* 495392: call 0x44ad60 */
	m->eax = M32((DWORD)(m->ebp + 0x2342ef6u));	/* 495397: mov eax, dword ptr [ebp + 0x2342ef6] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49539d: add esp, 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4953a0: inc esi */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4953a1: cmp esi, eax */
	if (m->cf) goto L_495312;	/* 4953a3: jb 0x495312 */
L_4953a9:
	m->edi = M32(m->esp); m->esp += 4;	/* 4953a9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4953aa: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4953ab: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4953ac: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4953ad: add esp, 0x10c */
	m->esp += 4 + 0; return;	/* 4953b3: ret  */
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
