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

static void lift_496f20(X86 *m);

/* hud_496f20 (0x496f20), lifted by tools/lift.py */
static void lift_496f20(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496f20: sub esp, 0x98 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 496f26: lea eax, [esp + 0x58] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 496f2a: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 496f2b: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 496f2c: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496f2d: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496f2e: push eax */
	m->esi = m->ecx;	/* 496f2f: mov esi, ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 496f31: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x496f3cu; native_call(m, M32(0x4a9270u));	/* 496f36: call dword ptr [0x4a9270] */
	m->esp -= 4; M32(m->esp) = 0x496f42u; native_call(m, M32(0x4a9218u));	/* 496f3c: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3990u)));	/* 496f42: fld dword ptr [esi + 0x20f3990] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496f48: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 496f4b: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f398cu)));	/* 496f4e: fld dword ptr [esi + 0x20f398c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496f54: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 496f57: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3988u)));	/* 496f5a: fld dword ptr [esi + 0x20f3988] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496f60: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 496f63: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3984u)));	/* 496f66: fld dword ptr [esi + 0x20f3984] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496f6c: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 496f6f: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3980u)));	/* 496f72: fld dword ptr [esi + 0x20f3980] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496f78: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 496f7b: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f397cu)));	/* 496f7e: fld dword ptr [esi + 0x20f397c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496f84: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 496f87: fstp qword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496f8a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496f8c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496f8e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496f90: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496f92: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496f94: push 0 */
	m->esp -= 4; M32(m->esp) = 0x496f9bu; native_call(m, 0x4509d2u);	/* 496f96: call 0x4509d2 */
	m->eax = M32((DWORD)(m->esi + 0x9ee064u));	/* 496f9b: mov eax, dword ptr [esi + 0x9ee064] */
	m->ebp = M32((DWORD)(0x4a920cu));	/* 496fa1: mov ebp, dword ptr [0x4a920c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 496fa7: test eax, eax */
	if (m->zf) goto L_497252;	/* 496fa9: je 0x497252 */
	m->edi = M32((DWORD)(0x4a922cu));	/* 496faf: mov edi, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 496fb5: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x496fbcu; native_call(m, m->edi);	/* 496fba: call edi */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 496fbc: push 0xb44 */
	m->esp -= 4; M32(m->esp) = 0x496fc3u; native_call(m, m->edi);	/* 496fc1: call edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 496fc3: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x496fceu; native_call(m, M32(0x4a9224u));	/* 496fc8: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496fce: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496fd3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496fd8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496fdd: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496fe8u; native_call(m, M32(0x4a9228u));	/* 496fe2: call dword ptr [0x4a9228] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 496fe8: xor edi, edi */
	M32((DWORD)(m->esp + 0x18u)) = m->edi;	/* 496fea: mov dword ptr [esp + 0x18], edi */
	goto L_496ff4;	/* 496fee: jmp 0x496ff4 */
L_496ff0:
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 496ff0: mov edi, dword ptr [esp + 0x18] */
L_496ff4:
	m->eax = M32((DWORD)(m->esi + m->edi*4 + 0x9ee068u));	/* 496ff4: mov eax, dword ptr [esi + edi*4 + 0x9ee068] */
	m->ecx = m->eax;	/* 496ffb: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 496ffd: and ecx, 0x800001ff */
	if (!m->sf) goto L_49700d;	/* 497003: jns 0x49700d */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 497005: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 497006: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49700c: inc ecx */
L_49700d:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49700d: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49700e: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497014: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 497015: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 497017: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49701d: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 497020: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x497029u; native_call(m, 0x4566c0u);	/* 497024: call 0x4566c0 */
	m->ebx = (DWORD)(m->edi*8 + 0x0u);	/* 497029: lea ebx, [edi*8] */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 497030: mov dword ptr [esp + 0x14], 0 */
	{ DWORD a_ = m->ebx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 497038: sub ebx, edi */
	M32((DWORD)(m->esp + 0x44u)) = m->ebx;	/* 49703a: mov dword ptr [esp + 0x44], ebx */
	goto L_497044;	/* 49703e: jmp 0x497044 */
L_497040:
	m->ebx = M32((DWORD)(m->esp + 0x44u));	/* 497040: mov ebx, dword ptr [esp + 0x44] */
L_497044:
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 497044: push 5 */
	m->esp -= 4; M32(m->esp) = 0x49704cu; native_call(m, M32(0x4a921cu));	/* 497046: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 49704c: fild dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 497050: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 497054: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 497056: add eax, ebx */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 497058: mov dword ptr [esp + 0x10], edi */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4fcu));	/* 49705c: fmul dword ptr [0x4aa4fc] */
	m->ebx = (DWORD)(m->eax*8 + 0x0u);	/* 497062: lea ebx, [eax*8] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 497069: sub ebx, eax */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49706b: fstp dword ptr [esp + 0x4c] */
L_49706f:
	m->eax = (DWORD)(m->ebx + m->edi*1 + 0xd3d60u);	/* 49706f: lea eax, [ebx + edi + 0xd3d60] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 497076: lea ecx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*4 + 0x0u)));	/* 497079: fld dword ptr [esi + ecx*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 49707c: fmul dword ptr [0x4a9708] */
	m->eax = (DWORD)(m->esi + m->ecx*4 + 0x0u);	/* 497082: lea eax, [esi + ecx*4] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 497085: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 497089: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 49708c: fmul dword ptr [0x4a9708] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 497092: mov edx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 497096: mov dword ptr [esp + 0x1c], edx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 49709a: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49709e: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 4970a1: fmul dword ptr [0x4a9708] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 4970a7: mov eax, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4970ab: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4970af: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4970b3: fstp dword ptr [esp + 0x40] */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 4970b7: mov ecx, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4970bb: test eax, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 4970bd: mov dword ptr [esp + 0x24], ecx */
	if (!m->zf) goto L_4970cb;	/* 4970c1: jne 0x4970cb */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9420u)));	/* 4970c3: fld dword ptr [0x4a9420] */
	goto L_4970de;	/* 4970c9: jmp 0x4970de */
L_4970cb:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 4970cb: fld dword ptr [0x4a93e8] */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4970d1: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x28u)) = 0xbc23d70au;	/* 4970d4: mov dword ptr [esp + 0x28], 0xbc23d70a */
	if (m->zf) goto L_4970e6;	/* 4970dc: je 0x4970e6 */
L_4970de:
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 4970de: mov dword ptr [esp + 0x28], 0 */
L_4970e6:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4970e6: test edi, edi */
	if (!m->zf) goto L_4970f2;	/* 4970e8: jne 0x4970f2 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9420u)));	/* 4970ea: fld dword ptr [0x4a9420] */
	goto L_497105;	/* 4970f0: jmp 0x497105 */
L_4970f2:
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4970f2: cmp edi, 6 */
	if (!m->zf) goto L_4970ff;	/* 4970f5: jne 0x4970ff */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4aa4f8u)));	/* 4970f7: fld dword ptr [0x4aa4f8] */
	goto L_497105;	/* 4970fd: jmp 0x497105 */
L_4970ff:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 4970ff: fld dword ptr [0x4a93e8] */
L_497105:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 497105: fild dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497109: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4fcu));	/* 49710a: fmul dword ptr [0x4aa4fc] */
	ST(0) = ST(0) + ST(1);	/* 497110: fadd st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 497112: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 497116: mov edx, dword ptr [esp + 0x14] */
	ST(0) = ST(0); FPOP();	/* 49711a: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 49711c: fld dword ptr [esp + 0x50] */
	ST(0) = ST(0) + ST(1);	/* 497120: fadd st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 497122: fstp dword ptr [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 497125: push edx */
	ST(0) = ST(0); FPOP();	/* 497126: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x49712au; native_call(m, m->ebp);	/* 497128: call ebp */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 49712a: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49712e: push eax */
	m->esp -= 4; M32(m->esp) = 0x497135u; native_call(m, M32(0x4a9290u));	/* 49712f: call dword ptr [0x4a9290] */
	m->eax = (DWORD)(m->ebx + m->edi*1 + 0xd3d67u);	/* 497135: lea eax, [ebx + edi + 0xd3d67] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49713c: lea ecx, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*4 + 0x0u)));	/* 49713f: fld dword ptr [esi + ecx*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497142: fmul dword ptr [0x4a9708] */
	m->eax = (DWORD)(m->esi + m->ecx*4 + 0x0u);	/* 497148: lea eax, [esi + ecx*4] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49714b: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 49714f: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497152: fmul dword ptr [0x4a9708] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 497158: mov edx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 49715c: mov dword ptr [esp + 0x1c], edx */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 497160: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 497164: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497167: fmul dword ptr [0x4a9708] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 49716d: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 497171: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->esi + 0x9ee064u));	/* 497175: mov eax, dword ptr [esi + 0x9ee064] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 49717b: fstp dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 49717f: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497183: cmp eax, 2 */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 497186: mov dword ptr [esp + 0x24], ecx */
	if (m->zf) goto L_4971b6;	/* 49718a: je 0x4971b6 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49718c: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 497190: test eax, eax */
	if (m->zf) goto L_4971b6;	/* 497192: je 0x4971b6 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 497194: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 497198: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 49719c: inc edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49719d: push ecx */
	M32((DWORD)(m->esp + 0x4cu)) = m->edx;	/* 49719e: mov dword ptr [esp + 0x4c], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4cu)));	/* 4971a2: fild dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9438u));	/* 4971a6: fmul dword ptr [0x4a9438] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 4971ac: fadd dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4971b0: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4971b3: push eax */
	goto L_4971d6;	/* 4971b4: jmp 0x4971d6 */
L_4971b6:
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4971b6: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4971ba: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4971be: inc ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 4971bf: mov dword ptr [esp + 0x48], ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4971c3: push ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4cu)));	/* 4971c4: fild dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4fcu));	/* 4971c8: fmul dword ptr [0x4aa4fc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 4971ce: fadd dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4971d2: fstp dword ptr [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4971d5: push edx */
L_4971d6:
	m->esp -= 4; M32(m->esp) = 0x4971d8u; native_call(m, m->ebp);	/* 4971d6: call ebp */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 4971d8: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4971dc: push eax */
	m->esp -= 4; M32(m->esp) = 0x4971e3u; native_call(m, M32(0x4a9290u));	/* 4971dd: call dword ptr [0x4a9290] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 4971e3: inc edi */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4971e4: cmp edi, 6 */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 4971e7: mov dword ptr [esp + 0x10], edi */
	if (m->zf || m->sf != m->of) goto L_49706f;	/* 4971eb: jle 0x49706f */
	m->esp -= 4; M32(m->esp) = 0x4971f7u; native_call(m, M32(0x4a9220u));	/* 4971f1: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4971f7: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4971fb: cmp eax, 1 */
	if (!m->zf) goto L_497208;	/* 4971fe: jne 0x497208 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9ee064u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497200: cmp dword ptr [esi + 0x9ee064], eax */
	if (m->zf) goto L_497216;	/* 497206: je 0x497216 */
L_497208:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 497208: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497209: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 49720c: mov dword ptr [esp + 0x14], eax */
	if (m->sf != m->of) goto L_497040;	/* 497210: jl 0x497040 */
L_497216:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 497216: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49721a: cmp eax, 4 */
	if (!m->zf) goto L_497228;	/* 49721d: jne 0x497228 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9ee064u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49721f: cmp dword ptr [esi + 0x9ee064], 1 */
	if (m->zf) goto L_497236;	/* 497226: je 0x497236 */
L_497228:
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 497228: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497229: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 49722c: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_496ff0;	/* 497230: jl 0x496ff0 */
L_497236:
	m->ebx = M32((DWORD)(0x4a9224u));	/* 497236: mov ebx, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 49723c: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x497243u; native_call(m, m->ebx);	/* 497241: call ebx */
	m->edi = M32((DWORD)(0x4a922cu));	/* 497243: mov edi, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 497249: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x497250u; native_call(m, m->edi);	/* 49724e: call edi */
	goto L_49725e;	/* 497250: jmp 0x49725e */
L_497252:
	m->ebx = M32((DWORD)(0x4a9224u));	/* 497252: mov ebx, dword ptr [0x4a9224] */
	m->edi = M32((DWORD)(0x4a922cu));	/* 497258: mov edi, dword ptr [0x4a922c] */
L_49725e:
	m->eax = M32((DWORD)(m->esi + 0x9eee48u));	/* 49725e: mov eax, dword ptr [esi + 0x9eee48] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 497264: test eax, eax */
	if (m->zf) goto L_4975e6;	/* 497266: je 0x4975e6 */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 49726c: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x497273u; native_call(m, m->edi);	/* 497271: call edi */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 497273: push 0xb44 */
	m->esp -= 4; M32(m->esp) = 0x49727au; native_call(m, m->edi);	/* 497278: call edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49727a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x497281u; native_call(m, m->ebx);	/* 49727f: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 497281: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 497286: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49728b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 497290: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x49729bu; native_call(m, M32(0x4a9228u));	/* 497295: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(m->esi + 0x9eee4cu));	/* 49729b: mov eax, dword ptr [esi + 0x9eee4c] */
	m->ecx = m->eax;	/* 4972a1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4972a3: and ecx, 0x800001ff */
	if (!m->sf) goto L_4972b3;	/* 4972a9: jns 0x4972b3 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4972ab: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4972ac: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4972b2: inc ecx */
L_4972b3:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4972b3: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4972b4: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4972ba: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4972bb: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4972bd: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4972c3: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4972c6: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4972cfu; native_call(m, 0x4566c0u);	/* 4972ca: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 4972cf: mov dword ptr [esp + 0x14], 0 */
	m->edi = (DWORD)(m->esi + 0x9eee5cu);	/* 4972d7: lea edi, [esi + 0x9eee5c] */
L_4972dd:
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 4972dd: push 5 */
	m->esp -= 4; M32(m->esp) = 0x4972e5u; native_call(m, M32(0x4a921cu));	/* 4972df: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4972e5: fild dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4972e9: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4972ed: xor ebx, ebx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4972ef: inc eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 4972f0: mov dword ptr [esp + 0x10], ebx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4972f4: fstp dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4972f8: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4972fc: fild dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 497300: fstp dword ptr [esp + 0x28] */
L_497304:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xfffffff8u)));	/* 497304: fld dword ptr [edi - 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497307: fmul dword ptr [0x4a9708] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 49730d: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xfffffffcu)));	/* 497311: fld dword ptr [edi - 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497314: fmul dword ptr [0x4a9708] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 49731a: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49731e: push ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 49731f: mov dword ptr [esp + 0x20], ecx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 497323: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 497327: fld dword ptr [edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497329: fmul dword ptr [0x4a9708] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 49732f: mov edx, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 497333: mov dword ptr [esp + 0x24], edx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 497337: fstp dword ptr [esp + 0x44] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 49733b: fild dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 49733f: mov eax, dword ptr [esp + 0x44] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 497343: mov dword ptr [esp + 0x28], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 497347: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49734b: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x9ef0acu));	/* 49734f: fadd dword ptr [esi + 0x9ef0ac] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 497355: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 497358: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x9ef0a8u));	/* 49735c: fadd dword ptr [esi + 0x9ef0a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497362: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 497363: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x497368u; native_call(m, m->ebp);	/* 497366: call ebp */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 497368: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49736c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x497373u; native_call(m, M32(0x4a9290u));	/* 49736d: call dword ptr [0x4a9290] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4cu)));	/* 497373: fld dword ptr [edi + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497376: fmul dword ptr [0x4a9708] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49737c: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x50u)));	/* 497380: fld dword ptr [edi + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497383: fmul dword ptr [0x4a9708] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 497389: mov edx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 49738d: mov dword ptr [esp + 0x1c], edx */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 497391: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x54u)));	/* 497395: fld dword ptr [edi + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497398: fmul dword ptr [0x4a9708] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 49739e: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4973a2: mov dword ptr [esp + 0x20], eax */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 4973a6: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4973aa: fld dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 4973ae: mov ecx, dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x9ef0acu));	/* 4973b2: fadd dword ptr [esi + 0x9ef0ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4973b8: push ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 4973b9: mov dword ptr [esp + 0x28], ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4973bd: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4973c0: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x9ef0a8u));	/* 4973c4: fadd dword ptr [esi + 0x9ef0a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4973ca: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4973cb: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4973d0u; native_call(m, m->ebp);	/* 4973ce: call ebp */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 4973d0: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4973d4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4973dbu; native_call(m, M32(0x4a9290u));	/* 4973d5: call dword ptr [0x4a9290] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4973db: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4973dc: add edi, 0xc */
	{ DWORD a_ = m->ebx, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4973df: cmp ebx, 6 */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 4973e2: mov dword ptr [esp + 0x10], ebx */
	if (m->zf || m->sf != m->of) goto L_497304;	/* 4973e6: jle 0x497304 */
	m->esp -= 4; M32(m->esp) = 0x4973f2u; native_call(m, M32(0x4a9220u));	/* 4973ec: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4973f2: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4973f6: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4973f9: mov dword ptr [esp + 0x14], eax */
	if (m->sf != m->of) goto L_4972dd;	/* 4973fd: jl 0x4972dd */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9eee48u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 497403: cmp dword ptr [esi + 0x9eee48], 2 */
	if (!m->zf) goto L_4975c4;	/* 49740a: jne 0x4975c4 */
	m->eax = M32((DWORD)(m->esi + 0x9eee50u));	/* 497410: mov eax, dword ptr [esi + 0x9eee50] */
	m->ecx = m->eax;	/* 497416: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 497418: and ecx, 0x800001ff */
	if (!m->sf) goto L_497428;	/* 49741e: jns 0x497428 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 497420: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 497421: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 497427: inc ecx */
L_497428:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 497428: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 497429: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49742f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 497430: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 497432: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 497438: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 49743b: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x497444u; native_call(m, 0x4566c0u);	/* 49743f: call 0x4566c0 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 497444: mov dword ptr [esp + 0x14], 0 */
	m->edi = (DWORD)(m->esi + 0x9eee5cu);	/* 49744c: lea edi, [esi + 0x9eee5c] */
L_497452:
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 497452: push 5 */
	m->esp -= 4; M32(m->esp) = 0x49745au; native_call(m, M32(0x4a921cu));	/* 497454: call dword ptr [0x4a921c] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 49745a: fild dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 49745e: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 497462: xor ebx, ebx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 497464: inc eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 497465: mov dword ptr [esp + 0x10], ebx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 497469: fstp dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 49746d: mov dword ptr [esp + 0x14], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 497471: fild dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 497475: fstp dword ptr [esp + 0x28] */
L_497479:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xfffffff8u)));	/* 497479: fld dword ptr [edi - 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 49747c: fmul dword ptr [0x4a9708] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xfffffffcu)));	/* 497482: fld dword ptr [edi - 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497485: fmul dword ptr [0x4a9708] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 49748b: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 49748f: fld dword ptr [edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497491: fmul dword ptr [0x4a9708] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 497497: fstp dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9508u));	/* 49749b: fmul dword ptr [0x4a9508] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4974a1: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 4974a5: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9508u));	/* 4974a9: fmul dword ptr [0x4a9508] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4974af: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4974b3: push ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 4974b4: mov dword ptr [esp + 0x20], ecx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4974b8: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 4974bc: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9508u));	/* 4974c0: fmul dword ptr [0x4a9508] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 4974c6: mov edx, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 4974ca: mov dword ptr [esp + 0x24], edx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4974ce: fstp dword ptr [esp + 0x44] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 4974d2: fild dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 4974d6: mov eax, dword ptr [esp + 0x44] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4974da: mov dword ptr [esp + 0x28], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 4974de: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x9ef0acu)));	/* 4974e2: fld dword ptr [esi + 0x9ef0ac] */
	ST(0) = ST(0) + ST(0);	/* 4974e8: fadd st(0), st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 4974ea: fadd dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4974ee: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x9ef0a8u)));	/* 4974f1: fld dword ptr [esi + 0x9ef0a8] */
	ST(0) = ST(0) + ST(0);	/* 4974f7: fadd st(0), st(0) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4974f9: push ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 4974fa: fadd dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4974fe: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x497503u; native_call(m, m->ebp);	/* 497501: call ebp */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 497503: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497507: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49750eu; native_call(m, M32(0x4a9290u));	/* 497508: call dword ptr [0x4a9290] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4cu)));	/* 49750e: fld dword ptr [edi + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497511: fmul dword ptr [0x4a9708] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x50u)));	/* 497517: fld dword ptr [edi + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 49751a: fmul dword ptr [0x4a9708] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 497520: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x54u)));	/* 497524: fld dword ptr [edi + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 497527: fmul dword ptr [0x4a9708] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 49752d: fstp dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9508u));	/* 497531: fmul dword ptr [0x4a9508] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 497537: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 49753b: fld dword ptr [esp + 0x60] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9508u));	/* 49753f: fmul dword ptr [0x4a9508] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 497545: mov edx, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 497549: mov dword ptr [esp + 0x1c], edx */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49754d: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 497551: fld dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9508u));	/* 497555: fmul dword ptr [0x4a9508] */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 49755b: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 49755f: mov dword ptr [esp + 0x20], eax */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 497563: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x9ef0acu)));	/* 497567: fld dword ptr [esi + 0x9ef0ac] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 49756d: mov ecx, dword ptr [esp + 0x34] */
	ST(0) = ST(0) + ST(0);	/* 497571: fadd st(0), st(0) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497573: push ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 497574: mov dword ptr [esp + 0x28], ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 497578: fadd dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 49757c: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x9ef0a8u)));	/* 49757f: fld dword ptr [esi + 0x9ef0a8] */
	ST(0) = ST(0) + ST(0);	/* 497585: fadd st(0), st(0) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497587: push ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 497588: fadd dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 49758c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x497591u; native_call(m, m->ebp);	/* 49758f: call ebp */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 497591: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 497595: push edx */
	m->esp -= 4; M32(m->esp) = 0x49759cu; native_call(m, M32(0x4a9290u));	/* 497596: call dword ptr [0x4a9290] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 49759c: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49759d: add edi, 0xc */
	{ DWORD a_ = m->ebx, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4975a0: cmp ebx, 6 */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 4975a3: mov dword ptr [esp + 0x10], ebx */
	if (m->zf || m->sf != m->of) goto L_497479;	/* 4975a7: jle 0x497479 */
	m->esp -= 4; M32(m->esp) = 0x4975b3u; native_call(m, M32(0x4a9220u));	/* 4975ad: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4975b3: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4975b7: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 4975ba: mov dword ptr [esp + 0x14], eax */
	if (m->sf != m->of) goto L_497452;	/* 4975be: jl 0x497452 */
L_4975c4:
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 4975c4: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x4975cfu; native_call(m, M32(0x4a9224u));	/* 4975c9: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4975cf: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4975dau; native_call(m, M32(0x4a922cu));	/* 4975d4: call dword ptr [0x4a922c] */
	m->ebx = M32((DWORD)(0x4a9224u));	/* 4975da: mov ebx, dword ptr [0x4a9224] */
	m->edi = M32((DWORD)(0x4a922cu));	/* 4975e0: mov edi, dword ptr [0x4a922c] */
L_4975e6:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9708u)));	/* 4975e6: fld dword ptr [0x4a9708] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0xacu));	/* 4975ec: fdiv dword ptr [esp + 0xac] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4975f3: fstp dword ptr [esp + 0x10] */
	m->esp -= 4; M32(m->esp) = 0x4975fdu; native_call(m, M32(0x4a9218u));	/* 4975f7: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4975fd: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3990u));	/* 497601: fmul dword ptr [esi + 0x20f3990] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497607: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49760a: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 49760d: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 497611: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20f398cu));	/* 497615: fmul dword ptr [esi + 0x20f398c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49761b: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49761e: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x10u)) = (double)ST(0); FPOP();	/* 497621: fstp qword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 497625: fld dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3988u));	/* 497629: fmul dword ptr [esi + 0x20f3988] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49762f: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497632: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 497635: fstp qword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 497639: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3984u));	/* 49763d: fmul dword ptr [esi + 0x20f3984] */
	MDBL((DWORD)(m->esp + 0x10u)) = (double)ST(0); FPOP();	/* 497643: fstp qword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3974u)));	/* 497647: fld dword ptr [esi + 0x20f3974] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3980u));	/* 49764d: fadd dword ptr [esi + 0x20f3980] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 497653: fmul dword ptr [esp + 0x40] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 497657: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 49765b: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20f397cu));	/* 49765f: fmul dword ptr [esi + 0x20f397c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 497665: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 497668: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3974u));	/* 49766c: fmul dword ptr [esi + 0x20f3974] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 497672: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 497674: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497676: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 497679: fstp qword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49767c: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49767e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x497685u; native_call(m, 0x4509d2u);	/* 497680: call 0x4509d2 */
	m->eax = M32((DWORD)(m->esi + 0x9ef0b0u));	/* 497685: mov eax, dword ptr [esi + 0x9ef0b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49768b: test eax, eax */
	if (m->zf) goto L_497818;	/* 49768d: je 0x497818 */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 497693: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x49769au; native_call(m, m->edi);	/* 497698: call edi */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 49769a: push 0xb44 */
	m->esp -= 4; M32(m->esp) = 0x4976a1u; native_call(m, m->edi);	/* 49769f: call edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4976a1: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4976a8u; native_call(m, m->ebx);	/* 4976a6: call ebx */
	m->eax = M32((DWORD)(m->esi + 0x9ef0b0u));	/* 4976a8: mov eax, dword ptr [esi + 0x9ef0b0] */
	M32((DWORD)(m->esp + 0x14u)) = 0x4502e653u;	/* 4976ae: mov dword ptr [esp + 0x14], 0x4502e653 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4976b6: cmp eax, 1 */
	if (m->zf) goto L_4976c3;	/* 4976b9: je 0x4976c3 */
	M32((DWORD)(m->esp + 0x14u)) = 0x4582e653u;	/* 4976bb: mov dword ptr [esp + 0x14], 0x4582e653 */
L_4976c3:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4976c3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4976c8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4976cd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4976d2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4976ddu; native_call(m, M32(0x4a9228u));	/* 4976d7: call dword ptr [0x4a9228] */
	m->eax = (DWORD)(m->esi + 0x9ef0d4u);	/* 4976dd: lea eax, [esi + 0x9ef0d4] */
	m->ecx = (DWORD)(m->esi + 0x9ef0b4u);	/* 4976e3: lea ecx, [esi + 0x9ef0b4] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 4976e9: mov dword ptr [esp + 0x28], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 4976ed: mov dword ptr [esp + 0x18], ecx */
	M32((DWORD)(m->esp + 0x44u)) = 0x6u;	/* 4976f1: mov dword ptr [esp + 0x44], 6 */
L_4976f9:
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4976f9: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 4976fd: mov eax, dword ptr [edx] */
	m->ecx = m->eax;	/* 4976ff: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 497701: and ecx, 0x800001ff */
	if (!m->sf) goto L_497711;	/* 497707: jns 0x497711 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 497709: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49770a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 497710: inc ecx */
L_497711:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 497711: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 497712: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497718: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 497719: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 49771b: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 497721: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 497724: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x49772du; native_call(m, 0x4566c0u);	/* 497728: call 0x4566c0 */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 49772d: push 5 */
	m->esp -= 4; M32(m->esp) = 0x497735u; native_call(m, M32(0x4a921cu));	/* 49772f: call dword ptr [0x4a921c] */
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 497735: mov edi, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 497739: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 49773b: mov dword ptr [esp + 0x10], ebx */
L_49773f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xfffffff8u)));	/* 49773f: fld dword ptr [edi - 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4f4u));	/* 497742: fmul dword ptr [0x4aa4f4] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 497748: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49774c: push 0 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 49774e: mov dword ptr [esp + 0x24], eax */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 497752: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 497756: fld dword ptr [edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4f4u));	/* 497758: fmul dword ptr [0x4aa4f4] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 49775e: fstp dword ptr [esp + 0x28] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 497762: fild dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9438u));	/* 497766: fmul dword ptr [0x4a9438] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49776c: fstp dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 497770: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497774: push ecx */
	m->esp -= 4; M32(m->esp) = 0x497777u; native_call(m, m->ebp);	/* 497775: call ebp */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 497777: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49777b: push edx */
	m->esp -= 4; M32(m->esp) = 0x497782u; native_call(m, M32(0x4a9290u));	/* 49777c: call dword ptr [0x4a9290] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xfffffff8u)));	/* 497782: fld dword ptr [edi - 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4f4u));	/* 497785: fmul dword ptr [0x4aa4f4] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49778b: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49778f: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 497794: push eax */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 497795: mov dword ptr [esp + 0x28], 0 */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 49779d: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 4977a1: fld dword ptr [edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4f4u));	/* 4977a3: fmul dword ptr [0x4aa4f4] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4977a9: fstp dword ptr [esp + 0x2c] */
	m->esp -= 4; M32(m->esp) = 0x4977afu; native_call(m, m->ebp);	/* 4977ad: call ebp */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 4977af: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4977b3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4977bau; native_call(m, M32(0x4a9290u));	/* 4977b4: call dword ptr [0x4a9290] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4977ba: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4977bb: add edi, 0xc */
	{ DWORD a_ = m->ebx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4977be: cmp ebx, 3 */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 4977c1: mov dword ptr [esp + 0x10], ebx */
	if (m->zf || m->sf != m->of) goto L_49773f;	/* 4977c5: jle 0x49773f */
	m->esp -= 4; M32(m->esp) = 0x4977d1u; native_call(m, M32(0x4a9220u));	/* 4977cb: call dword ptr [0x4a9220] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4977d1: mov edx, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 4977d5: mov ecx, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 4977d9: mov eax, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4977dd: add edx, 4 */
	{ DWORD a_ = m->ecx, b_ = 0x60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4977e0: add ecx, 0x60 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4977e3: dec eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 4977e4: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 4977e8: mov dword ptr [esp + 0x28], ecx */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 4977ec: mov dword ptr [esp + 0x44], eax */
	if (!m->zf) goto L_4976f9;	/* 4977f0: jne 0x4976f9 */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 4977f6: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x497801u; native_call(m, M32(0x4a9224u));	/* 4977fb: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 497801: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x49780cu; native_call(m, M32(0x4a922cu));	/* 497806: call dword ptr [0x4a922c] */
	m->ebx = M32((DWORD)(0x4a9224u));	/* 49780c: mov ebx, dword ptr [0x4a9224] */
	m->edi = M32((DWORD)(0x4a922cu));	/* 497812: mov edi, dword ptr [0x4a922c] */
L_497818:
	m->esp -= 4; M32(m->esp) = 0x49781eu; native_call(m, M32(0x4a9218u));	/* 497818: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3990u)));	/* 49781e: fld dword ptr [esi + 0x20f3990] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497824: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 497827: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f398cu)));	/* 49782a: fld dword ptr [esi + 0x20f398c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497830: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 497833: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3988u)));	/* 497836: fld dword ptr [esi + 0x20f3988] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49783c: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 49783f: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3984u)));	/* 497842: fld dword ptr [esi + 0x20f3984] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497848: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 49784b: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3974u)));	/* 49784e: fld dword ptr [esi + 0x20f3974] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3980u));	/* 497854: fadd dword ptr [esi + 0x20f3980] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49785a: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49785d: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 497860: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f397cu)));	/* 497864: fld dword ptr [esi + 0x20f397c] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 49786a: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3974u)));	/* 49786d: fld dword ptr [esi + 0x20f3974] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 497873: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 497875: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497877: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 49787a: fstp qword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49787d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49787f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x497886u; native_call(m, 0x4509d2u);	/* 497881: call 0x4509d2 */
	m->eax = M32((DWORD)(m->esi + 0x9ef30cu));	/* 497886: mov eax, dword ptr [esi + 0x9ef30c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49788c: test eax, eax */
	if (m->zf) goto L_497a6b;	/* 49788e: je 0x497a6b */
	m->edx = M32((DWORD)(m->esi + 0x9ee060u));	/* 497894: mov edx, dword ptr [esi + 0x9ee060] */
	m->eax = M32((DWORD)(m->esi + 0x9ee05cu));	/* 49789a: mov eax, dword ptr [esi + 0x9ee05c] */
	m->ecx = M32((DWORD)(m->esi + 0x9ee058u));	/* 4978a0: mov ecx, dword ptr [esi + 0x9ee058] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4978a6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4978a7: push eax */
	m->edx = (DWORD)(m->esi + 0x9ee048u);	/* 4978a8: lea edx, [esi + 0x9ee048] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4978ae: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4978af: push edx */
	m->ecx = m->esi;	/* 4978b0: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4978b7u; native_call(m, 0x472900u);	/* 4978b2: call 0x472900 */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 4978b7: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x4978beu; native_call(m, m->ebx);	/* 4978bc: call ebx */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 4978be: push 0xb44 */
	m->esp -= 4; M32(m->esp) = 0x4978c5u; native_call(m, m->edi);	/* 4978c3: call edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4978c5: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4978ccu; native_call(m, m->ebx);	/* 4978ca: call ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4978cc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4978d1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4978d6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4978db: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4978e6u; native_call(m, M32(0x4a9228u));	/* 4978e0: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(m->esi + 0x9ef8fcu));	/* 4978e6: mov eax, dword ptr [esi + 0x9ef8fc] */
	m->eax = M32((DWORD)(m->esi + m->eax*4 + 0x9ef310u));	/* 4978ec: mov eax, dword ptr [esi + eax*4 + 0x9ef310] */
	m->ecx = m->eax;	/* 4978f3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4978f5: and ecx, 0x800001ff */
	if (!m->sf) goto L_497905;	/* 4978fb: jns 0x497905 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4978fd: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4978fe: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 497904: inc ecx */
L_497905:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 497905: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 497906: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49790c: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49790d: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 49790f: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 497915: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 497918: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x497921u; native_call(m, 0x4566c0u);	/* 49791c: call 0x4566c0 */
	m->edi = (DWORD)(m->esi + 0x9ef358u);	/* 497921: lea edi, [esi + 0x9ef358] */
	M32((DWORD)(m->esp + 0x18u)) = 0xau;	/* 497927: mov dword ptr [esp + 0x18], 0xa */
L_49792f:
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 49792f: push 5 */
	m->esp -= 4; M32(m->esp) = 0x497937u; native_call(m, M32(0x4a921cu));	/* 497931: call dword ptr [0x4a921c] */
	M32((DWORD)(m->esp + 0x44u)) = 0xbu;	/* 497937: mov dword ptr [esp + 0x44], 0xb */
L_49793f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 49793f: fld dword ptr [esp + 0xac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0xfffffff8u));	/* 497946: fmul dword ptr [edi - 8] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 497949: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 49794d: fld dword ptr [esp + 0xac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0xfffffffcu));	/* 497954: fmul dword ptr [edi - 4] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 497957: mov eax, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49795b: mov dword ptr [esp + 0x1c], eax */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49795f: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 497963: fld dword ptr [esp + 0xac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 49796a: fmul dword ptr [edi] */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 49796c: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497970: push ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 497971: mov dword ptr [esp + 0x24], ecx */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 497975: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 497979: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3978u));	/* 49797d: fadd dword ptr [esi + 0x20f3978] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 497983: mov edx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 497987: mov dword ptr [esp + 0x28], edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4f0u));	/* 49798b: fmul dword ptr [0x4aa4f0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 497991: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 497994: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3970u));	/* 497998: fadd dword ptr [esi + 0x20f3970] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49799e: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4f0u));	/* 49799f: fmul dword ptr [0x4aa4f0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4979a5: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x4979aau; native_call(m, m->ebp);	/* 4979a8: call ebp */
	m->ebx = M32((DWORD)(0x4a9290u));	/* 4979aa: mov ebx, dword ptr [0x4a9290] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 4979b0: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4979b4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4979b7u; native_call(m, m->ebx);	/* 4979b5: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 4979b7: fld dword ptr [esp + 0xac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x7cu));	/* 4979be: fmul dword ptr [edi + 0x7c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4979c1: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 4979c5: fld dword ptr [esp + 0xac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x80u));	/* 4979cc: fmul dword ptr [edi + 0x80] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4979d2: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4979d6: push ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 4979d7: mov dword ptr [esp + 0x20], ecx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4979db: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 4979df: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x84u));	/* 4979e6: fmul dword ptr [edi + 0x84] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 4979ec: mov edx, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 4979f0: mov dword ptr [esp + 0x24], edx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4979f4: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4979f8: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3978u));	/* 4979fc: fadd dword ptr [esi + 0x20f3978] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 497a02: mov eax, dword ptr [esp + 0x44] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 497a06: mov dword ptr [esp + 0x28], eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4f0u));	/* 497a0a: fmul dword ptr [0x4aa4f0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 497a10: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 497a13: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3970u));	/* 497a17: fadd dword ptr [esi + 0x20f3970] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497a1d: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4f0u));	/* 497a1e: fmul dword ptr [0x4aa4f0] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 497a24: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x497a29u; native_call(m, m->ebp);	/* 497a27: call ebp */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 497a29: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 497a2d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x497a30u; native_call(m, m->ebx);	/* 497a2e: call ebx */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 497a30: mov eax, dword ptr [esp + 0x44] */
	{ DWORD a_ = m->edi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 497a34: add edi, 0xc */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 497a37: dec eax */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 497a38: mov dword ptr [esp + 0x44], eax */
	if (!m->zf) goto L_49793f;	/* 497a3c: jne 0x49793f */
	m->esp -= 4; M32(m->esp) = 0x497a48u; native_call(m, M32(0x4a9220u));	/* 497a42: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 497a48: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 497a4c: dec eax */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 497a4d: mov dword ptr [esp + 0x18], eax */
	if (!m->zf) goto L_49792f;	/* 497a51: jne 0x49792f */
	m->esi = M32((DWORD)(0x4a922cu));	/* 497a57: mov esi, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 497a5d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x497a64u; native_call(m, m->esi);	/* 497a62: call esi */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 497a64: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x497a6bu; native_call(m, m->esi);	/* 497a69: call esi */
L_497a6b:
	m->edx = (DWORD)(m->esp + 0x68u);	/* 497a6b: lea edx, [esp + 0x68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 497a6f: push edx */
	m->esp -= 4; M32(m->esp) = 0x497a76u; native_call(m, M32(0x4a926cu));	/* 497a70: call dword ptr [0x4a926c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 497a76: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 497a77: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 497a78: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 497a79: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 497a7a: add esp, 0x98 */
	m->esp += 4 + 4; return;	/* 497a80: ret 4 */
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
