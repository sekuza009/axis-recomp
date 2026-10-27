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

static void lift_4399c0(X86 *m);
static void lift_409bc0(X86 *m);
static void lift_41f100(X86 *m);

/* intro_41f100 (0x41f100), lifted by tools/lift.py */
static void lift_41f100(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 41f100: push ebp */
	m->ebp = m->esp;	/* 41f101: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 41f103: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f106: sub esp, 0x10 */
	m->eax = M32((DWORD)(0x76d35cu));	/* 41f109: mov eax, dword ptr [0x76d35c] */
	m->ecx = M32((DWORD)(0x76d358u));	/* 41f10e: mov ecx, dword ptr [0x76d358] */
	m->edx = M32((DWORD)(0x76d354u));	/* 41f114: mov edx, dword ptr [0x76d354] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f11a: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 41f11b: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f11c: push eax */
	m->eax = M32((DWORD)(0x76d350u));	/* 41f11d: mov eax, dword ptr [0x76d350] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f122: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f123: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f124: push eax */
	m->esp -= 4; M32(m->esp) = 0x41f12bu; native_call(m, M32(0x4a91e0u));	/* 41f125: call dword ptr [0x4a91e0] */
	{ DWORD v_ = 0x4100u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f12b: push 0x4100 */
	m->esp -= 4; M32(m->esp) = 0x41f136u; native_call(m, M32(0x4a91e8u));	/* 41f130: call dword ptr [0x4a91e8] */
	m->esi = M32((DWORD)(0x4a9228u));	/* 41f136: mov esi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f13c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f141: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f146: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f14b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41f152u; native_call(m, m->esi);	/* 41f150: call esi */
	m->edi = M32((DWORD)(0x4a9224u));	/* 41f152: mov edi, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xbe2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f158: push 0xbe2 */
	m->esp -= 4; M32(m->esp) = 0x41f15fu; native_call(m, m->edi);	/* 41f15d: call edi */
	{ DWORD v_ = 0x303u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f15f: push 0x303 */
	{ DWORD v_ = 0x302u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f164: push 0x302 */
	m->esp -= 4; M32(m->esp) = 0x41f16fu; native_call(m, M32(0x4a91ecu));	/* 41f169: call dword ptr [0x4a91ec] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f16f: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41f176u; native_call(m, 0x41ef90u);	/* 41f171: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f176: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x41f17fu; native_call(m, M32(0x4a9218u));	/* 41f179: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f17f: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41f186u; native_call(m, m->edi);	/* 41f184: call edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f186: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f18b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f190: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f195: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41f19cu; native_call(m, m->esi);	/* 41f19a: call esi */
	m->eax = M32((DWORD)(0x76d3f0u));	/* 41f19c: mov eax, dword ptr [0x76d3f0] */
	m->ecx = m->eax;	/* 41f1a1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41f1a3: and ecx, 0x800001ff */
	if (!m->sf) goto L_41f1b3;	/* 41f1a9: jns 0x41f1b3 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 41f1ab: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41f1ac: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 41f1b2: inc ecx */
L_41f1b3:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 41f1b3: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 41f1b4: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1ba: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41f1bb: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 41f1bd: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 41f1c3: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 41f1c6: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x41f1cfu; native_call(m, 0x4566c0u);	/* 41f1ca: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1cf: push 7 */
	m->esp -= 4; M32(m->esp) = 0x41f1d7u; native_call(m, M32(0x4a921cu));	/* 41f1d1: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a9208u));	/* 41f1d7: mov esi, dword ptr [0x4a9208] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1dd: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1df: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1e1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1e3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41f1e7u; native_call(m, m->esi);	/* 41f1e5: call esi */
	{ DWORD v_ = 0x3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1e7: push 0x3c */
	{ DWORD v_ = 0xa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1e9: push 0xa0 */
	m->esp -= 4; M32(m->esp) = 0x41f1f3u; native_call(m, 0x41ef60u);	/* 41f1ee: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f1f3: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1f6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1f8: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1fa: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f1ff: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41f203u; native_call(m, m->esi);	/* 41f201: call esi */
	{ DWORD v_ = 0x3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f203: push 0x3c */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f205: push 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x41f20fu; native_call(m, 0x41ef60u);	/* 41f20a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f20f: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f212: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f217: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f219: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f21e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41f222u; native_call(m, m->esi);	/* 41f220: call esi */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f222: push 0x13c */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f227: push 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x41f231u; native_call(m, 0x41ef60u);	/* 41f22c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f231: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f234: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f239: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f23b: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f23d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41f241u; native_call(m, m->esi);	/* 41f23f: call esi */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f241: push 0x13c */
	{ DWORD v_ = 0xa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f246: push 0xa0 */
	m->esp -= 4; M32(m->esp) = 0x41f250u; native_call(m, 0x41ef60u);	/* 41f24b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f250: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x41f259u; native_call(m, M32(0x4a9220u));	/* 41f253: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f259: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41f264u; native_call(m, M32(0x4a922cu));	/* 41f25e: call dword ptr [0x4a922c] */
	m->esi = M32((DWORD)(0x4dda34u));	/* 41f264: mov esi, dword ptr [0x4dda34] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41f26a: xor edi, edi */
	{ DWORD a_ = m->esi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 41f26c: shl esi, 4 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41f26f: test esi, esi */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 41f271: mov dword ptr [esp + 0x14], edi */
	if (m->zf || m->sf != m->of) goto L_41f34f;	/* 41f275: jle 0x41f34f */
L_41f27b:
	{ DWORD a_ = m->edi, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f27b: cmp edi, 0xc8 */
	if (m->sf == m->of) goto L_41f34f;	/* 41f281: jge 0x41f34f */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 41f287: fild dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 41f28b: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 41f28d: fmul dword ptr [0x4a9404] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 41f293: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 41f299: fstp dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94d8u));	/* 41f29d: fmul dword ptr [0x4a94d8] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 41f2a3: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 41f2a7: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41f2ab: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f2b1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f2b3: test ah, 1 */
	if (m->zf) goto L_41f2c0;	/* 41f2b6: je 0x41f2c0 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 41f2b8: mov dword ptr [esp + 0x14], 0 */
L_41f2c0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 41f2c0: fld dword ptr [esp + 0xc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41f2c4: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f2ca: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f2cc: test ah, 1 */
	if (m->zf) goto L_41f2d9;	/* 41f2cf: je 0x41f2d9 */
	M32((DWORD)(m->esp + 0xcu)) = 0x0u;	/* 41f2d1: mov dword ptr [esp + 0xc], 0 */
L_41f2d9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 41f2d9: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 41f2dd: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f2e3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f2e5: test ah, 0x41 */
	if (!m->zf) goto L_41f2f2;	/* 41f2e8: jne 0x41f2f2 */
	M32((DWORD)(m->esp + 0x14u)) = 0x3f800000u;	/* 41f2ea: mov dword ptr [esp + 0x14], 0x3f800000 */
L_41f2f2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 41f2f2: fld dword ptr [esp + 0xc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 41f2f6: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f2fc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f2fe: test ah, 0x41 */
	if (!m->zf) goto L_41f30b;	/* 41f301: jne 0x41f30b */
	M32((DWORD)(m->esp + 0xcu)) = 0x3f800000u;	/* 41f303: mov dword ptr [esp + 0xc], 0x3f800000 */
L_41f30b:
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 41f30b: mov eax, dword ptr [esp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 41f30f: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f313: push 0x3f800000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f318: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f319: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f31b: push ecx */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f31c: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x41f326u; native_call(m, 0x41f0e0u);	/* 41f321: call 0x41f0e0 */
	m->eax = (DWORD)(m->edi + 0x14u);	/* 41f326: lea eax, [edi + 0x14] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f329: push 1 */
	{ DWORD v_ = 0x1deu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f32b: push 0x1de */
	m->edx = (DWORD)(m->eax + 0x1u);	/* 41f330: lea edx, [eax + 1] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f333: push edx */
	{ DWORD v_ = 0x1dau; m->esp -= 4; M32(m->esp) = v_; }	/* 41f334: push 0x1da */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f339: push eax */
	m->esp -= 4; M32(m->esp) = 0x41f33fu; native_call(m, 0x427970u);	/* 41f33a: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f33f: add esp, 0x28 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 41f342: inc edi */
	{ DWORD a_ = m->edi, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f343: cmp edi, esi */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 41f345: mov dword ptr [esp + 0x14], edi */
	if (m->sf != m->of) goto L_41f27b;	/* 41f349: jl 0x41f27b */
L_41f34f:
	{ DWORD a_ = m->esi, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f34f: cmp esi, 0xc8 */
	if (m->zf || m->sf != m->of) goto L_41f442;	/* 41f355: jle 0x41f442 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41f35b: xor edi, edi */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 41f35d: mov dword ptr [esp + 0x14], edi */
L_41f361:
	m->eax = (DWORD)(m->edi + 0xc8u);	/* 41f361: lea eax, [edi + 0xc8] */
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f367: cmp eax, 0x190 */
	if (m->sf == m->of) goto L_41f442;	/* 41f36c: jge 0x41f442 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 41f372: fild dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9404u));	/* 41f376: fmul dword ptr [0x4a9404] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 41f37c: fst dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 41f380: fld dword ptr [0x4a9424] */
	ST(0) = ST(0) - ST(1);	/* 41f386: fsub st(1) */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 41f388: fstp dword ptr [esp + 0xc] */
	ST(0) = ST(0); FPOP();	/* 41f38c: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41f38e: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41f392: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f398: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f39a: test ah, 1 */
	if (m->zf) goto L_41f3a7;	/* 41f39d: je 0x41f3a7 */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 41f39f: mov dword ptr [esp + 0x10], 0 */
L_41f3a7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 41f3a7: fld dword ptr [esp + 0xc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41f3ab: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f3b1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f3b3: test ah, 1 */
	if (m->zf) goto L_41f3c0;	/* 41f3b6: je 0x41f3c0 */
	M32((DWORD)(m->esp + 0xcu)) = 0x0u;	/* 41f3b8: mov dword ptr [esp + 0xc], 0 */
L_41f3c0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41f3c0: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 41f3c4: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f3ca: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f3cc: test ah, 0x41 */
	if (!m->zf) goto L_41f3d9;	/* 41f3cf: jne 0x41f3d9 */
	M32((DWORD)(m->esp + 0x10u)) = 0x3f800000u;	/* 41f3d1: mov dword ptr [esp + 0x10], 0x3f800000 */
L_41f3d9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 41f3d9: fld dword ptr [esp + 0xc] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 41f3dd: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f3e3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f3e5: test ah, 0x41 */
	if (!m->zf) goto L_41f3f2;	/* 41f3e8: jne 0x41f3f2 */
	M32((DWORD)(m->esp + 0xcu)) = 0x3f800000u;	/* 41f3ea: mov dword ptr [esp + 0xc], 0x3f800000 */
L_41f3f2:
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 41f3f2: mov ecx, dword ptr [esp + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 41f3f6: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f3fa: push 0x3f800000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f3ff: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f400: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f401: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f403: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x41f40du; native_call(m, 0x41f0e0u);	/* 41f408: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f40d: push 1 */
	m->eax = (DWORD)(m->edi + 0xddu);	/* 41f40f: lea eax, [edi + 0xdd] */
	{ DWORD v_ = 0x1deu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f415: push 0x1de */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f41a: push eax */
	m->ecx = (DWORD)(m->edi + 0xdcu);	/* 41f41b: lea ecx, [edi + 0xdc] */
	{ DWORD v_ = 0x1dau; m->esp -= 4; M32(m->esp) = v_; }	/* 41f421: push 0x1da */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f426: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41f42cu; native_call(m, 0x427970u);	/* 41f427: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f42c: add esp, 0x28 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 41f42f: inc edi */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 41f430: mov dword ptr [esp + 0x14], edi */
	m->edx = (DWORD)(m->edi + 0xc8u);	/* 41f434: lea edx, [edi + 0xc8] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f43a: cmp edx, esi */
	if (m->sf != m->of) goto L_41f361;	/* 41f43c: jl 0x41f361 */
L_41f442:
	{ DWORD a_ = m->esi, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f442: cmp esi, 0x190 */
	if (m->zf || m->sf != m->of) goto L_41f520;	/* 41f448: jle 0x41f520 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41f44e: xor edi, edi */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 41f450: mov dword ptr [esp + 0x14], edi */
L_41f454:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 41f454: fild dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 41f458: fmul dword ptr [0x4a9420] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 41f45e: fst dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 41f462: fadd dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 41f468: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 41f46c: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41f470: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f476: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f478: test ah, 1 */
	if (m->zf) goto L_41f485;	/* 41f47b: je 0x41f485 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 41f47d: mov dword ptr [esp + 0x14], 0 */
L_41f485:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41f485: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 41f489: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f48f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f491: test ah, 1 */
	if (m->zf) goto L_41f49e;	/* 41f494: je 0x41f49e */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 41f496: mov dword ptr [esp + 0x10], 0 */
L_41f49e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 41f49e: fld dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 41f4a2: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f4a8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f4aa: test ah, 0x41 */
	if (!m->zf) goto L_41f4b7;	/* 41f4ad: jne 0x41f4b7 */
	M32((DWORD)(m->esp + 0x14u)) = 0x3f800000u;	/* 41f4af: mov dword ptr [esp + 0x14], 0x3f800000 */
L_41f4b7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 41f4b7: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 41f4bb: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41f4c1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41f4c3: test ah, 0x41 */
	if (!m->zf) goto L_41f4d0;	/* 41f4c6: jne 0x41f4d0 */
	M32((DWORD)(m->esp + 0x10u)) = 0x3f800000u;	/* 41f4c8: mov dword ptr [esp + 0x10], 0x3f800000 */
L_41f4d0:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 41f4d0: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 41f4d4: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4d8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4dd: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4df: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4e0: push ecx */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4e1: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x41f4ebu; native_call(m, 0x41f0e0u);	/* 41f4e6: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4eb: push 1 */
	m->edx = (DWORD)(m->edi + 0x1a5u);	/* 41f4ed: lea edx, [edi + 0x1a5] */
	{ DWORD v_ = 0x1deu; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4f3: push 0x1de */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4f8: push edx */
	m->eax = (DWORD)(m->edi + 0x1a4u);	/* 41f4f9: lea eax, [edi + 0x1a4] */
	{ DWORD v_ = 0x1dau; m->esp -= 4; M32(m->esp) = v_; }	/* 41f4ff: push 0x1da */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41f504: push eax */
	m->esp -= 4; M32(m->esp) = 0x41f50au; native_call(m, 0x427970u);	/* 41f505: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f50a: add esp, 0x28 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 41f50d: inc edi */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 41f50e: mov dword ptr [esp + 0x14], edi */
	m->ecx = (DWORD)(m->edi + 0x190u);	/* 41f512: lea ecx, [edi + 0x190] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41f518: cmp ecx, esi */
	if (m->sf != m->of) goto L_41f454;	/* 41f51a: jl 0x41f454 */
L_41f520:
	m->esp -= 4; M32(m->esp) = 0x41f526u; native_call(m, M32(0x4a91f0u));	/* 41f520: call dword ptr [0x4a91f0] */
	m->edx = M32((DWORD)(0x76d480u));	/* 41f526: mov edx, dword ptr [0x76d480] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f52c: push edx */
	m->esp -= 4; M32(m->esp) = 0x41f533u; native_call(m, M32(0x4a9028u));	/* 41f52d: call dword ptr [0x4a9028] */
	m->edi = M32(m->esp); m->esp += 4;	/* 41f533: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41f534: pop esi */
	m->esp = m->ebp;	/* 41f535: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 41f537: pop ebp */
	m->esp += 4 + 0; return;	/* 41f538: ret  */
}

/* room_4399c0 (0x4399c0), lifted by tools/lift.py */
static void lift_4399c0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 4399c0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4399c5: sub esp, 0x24 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4399c8: test eax, eax */
	if (m->zf) goto L_4399f2;	/* 4399ca: je 0x4399f2 */
	m->eax = M32((DWORD)(0x9dd6f4u));	/* 4399cc: mov eax, dword ptr [0x9dd6f4] */
	m->ecx = M32((DWORD)(0x9dd6f0u));	/* 4399d1: mov ecx, dword ptr [0x9dd6f0] */
	m->edx = M32((DWORD)(0x9dd6ecu));	/* 4399d7: mov edx, dword ptr [0x9dd6ec] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4399dd: push eax */
	m->eax = M32((DWORD)(0x9dd6e8u));	/* 4399de: mov eax, dword ptr [0x9dd6e8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4399e3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4399e4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4399e5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4399ebu; native_call(m, 0x428c30u);	/* 4399e6: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4399eb: add esp, 0x10 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4399ee: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 4399f1: ret  */
L_4399f2:
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 4399f2: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 4399f8: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4399fe: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4399ff: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 439a00: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 439a01: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a02: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a03: push edx */
	m->esp -= 4; M32(m->esp) = 0x439a09u; native_call(m, 0x432240u);	/* 439a04: call 0x432240 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 439a09: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 439a0b: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x439a14u; native_call(m, 0x41ef90u);	/* 439a0f: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439a14: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x439a1du; native_call(m, M32(0x4a9218u));	/* 439a17: call dword ptr [0x4a9218] */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 439a1d: mov ebp, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439a23: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439a28: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439a2d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439a32: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x439a39u; native_call(m, m->ebp);	/* 439a37: call ebp */
	m->eax = M32((DWORD)(0x4deb50u));	/* 439a39: mov eax, dword ptr [0x4deb50] */
	m->ecx = M32((DWORD)(0x9dd6f4u));	/* 439a3e: mov ecx, dword ptr [0x9dd6f4] */
	m->edx = M32((DWORD)(0x9dd6f0u));	/* 439a44: mov edx, dword ptr [0x9dd6f0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439a4a: push eax */
	m->eax = M32((DWORD)(0x9dd6ecu));	/* 439a4b: mov eax, dword ptr [0x9dd6ec] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a50: push ecx */
	m->ecx = M32((DWORD)(0x9dd6e8u));	/* 439a51: mov ecx, dword ptr [0x9dd6e8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a57: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439a58: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a59: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439a5fu; native_call(m, 0x427a90u);	/* 439a5a: call 0x427a90 */
	m->edx = M32((DWORD)(0x9dceccu));	/* 439a5f: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 439a65: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 439a6a: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a70: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 439a71: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439a77: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a78: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a79: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 439a7a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x439a84u; native_call(m, 0x41f0e0u);	/* 439a7f: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd6ecu));	/* 439a84: mov eax, dword ptr [0x9dd6ec] */
	m->ecx = M32((DWORD)(0x9dd6e8u));	/* 439a89: mov ecx, dword ptr [0x9dd6e8] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439a8f: add eax, 0x10 */
	{ DWORD v_ = 0x7588a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 439a92: push 0x7588a4 */
	{ DWORD a_ = m->ecx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439a97: add ecx, 0x40 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439a9a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439a9b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439aa1u; native_call(m, 0x4028b0u);	/* 439a9c: call 0x4028b0 */
	m->edx = M32((DWORD)(0x9dceccu));	/* 439aa1: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 439aa7: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 439aac: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439ab2: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 439ab3: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439ab9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439aba: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439abb: push edx */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 439abc: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x439ac6u; native_call(m, 0x41f0e0u);	/* 439ac1: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439ac6: add esp, 0x48 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 439ac9: xor edi, edi */
	m->esi = 0x758924u;	/* 439acb: mov esi, 0x758924 */
L_439ad0:
	m->eax = M32((DWORD)(0x9dd6ecu));	/* 439ad0: mov eax, dword ptr [0x9dd6ec] */
	m->edx = M32((DWORD)(0x9dd6e8u));	/* 439ad5: mov edx, dword ptr [0x9dd6e8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 439adb: push esi */
	{ DWORD a_ = m->edx, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 439adc: add edx, 0x30 */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x3cu);	/* 439adf: lea ecx, [edi + eax + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439ae3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439ae4: push edx */
	m->esp -= 4; M32(m->esp) = 0x439aeau; native_call(m, 0x402620u);	/* 439ae5: call 0x402620 */
	m->eax = M32((DWORD)(0x9dd6ecu));	/* 439aea: mov eax, dword ptr [0x9dd6ec] */
	m->ecx = M32((DWORD)(0x9dd6e8u));	/* 439aef: mov ecx, dword ptr [0x9dd6e8] */
	m->eax = (DWORD)(m->edi + m->eax*1 + 0x50u);	/* 439af5: lea eax, [edi + eax + 0x50] */
	m->edx = (DWORD)(m->ecx + 0x200u);	/* 439af9: lea edx, [ecx + 0x200] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439aff: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439b00: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439b01: add ecx, 0x84 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439b07: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439b08: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439b0eu; native_call(m, 0x427a40u);	/* 439b09: call 0x427a40 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 439b0e: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439b14: add esp, 0x1c */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 439b17: add edi, 0x30 */
	{ DWORD a_ = m->esi, b_ = 0x758b24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 439b1a: cmp esi, 0x758b24 */
	if (m->sf != m->of) goto L_439ad0;	/* 439b20: jl 0x439ad0 */
	m->eax = M32((DWORD)(0x9dd348u));	/* 439b22: mov eax, dword ptr [0x9dd348] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439b27: test eax, eax */
	if (m->zf) goto L_439b34;	/* 439b29: je 0x439b34 */
	m->eax = M32((DWORD)(0x68039cu));	/* 439b2b: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439b30: test eax, eax */
	if (!m->zf) goto L_439b57;	/* 439b32: jne 0x439b57 */
L_439b34:
	m->eax = M32((DWORD)(0x9dd6ecu));	/* 439b34: mov eax, dword ptr [0x9dd6ec] */
	m->ecx = M32((DWORD)(0x9dd6e8u));	/* 439b39: mov ecx, dword ptr [0x9dd6e8] */
	{ DWORD a_ = m->eax, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439b3f: add eax, 0x3c */
	{ DWORD v_ = 0x9dd1d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 439b42: push 0x9dd1d8 */
	{ DWORD a_ = m->ecx, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439b47: add ecx, 0x94 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439b4d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439b4e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439b54u; native_call(m, 0x402620u);	/* 439b4f: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439b54: add esp, 0xc */
L_439b57:
	m->eax = M32((DWORD)(0x9dd3f8u));	/* 439b57: mov eax, dword ptr [0x9dd3f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439b5c: test eax, eax */
	if (m->zf) goto L_439b69;	/* 439b5e: je 0x439b69 */
	m->eax = M32((DWORD)(0x68039cu));	/* 439b60: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439b65: test eax, eax */
	if (!m->zf) goto L_439bc6;	/* 439b67: jne 0x439bc6 */
L_439b69:
	m->edi = 0x9dd1f6u;	/* 439b69: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 439b6e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 439b71: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 439b73: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 439b75: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 439b77: dec ecx */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 439b78: lea edi, [esp + 0x14] */
	m->edx = m->ecx;	/* 439b7c: mov edx, ecx */
	m->ecx = 0x7u;	/* 439b7e: mov ecx, 7 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 439b83: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439b85: test edx, edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 439b87: stosw word ptr es:[edi], ax */
	if (m->zf || m->sf != m->of) goto L_439ba2;	/* 439b89: jle 0x439ba2 */
	m->ecx = m->edx;	/* 439b8b: mov ecx, edx */
	m->eax = 0x2a2a2a2au;	/* 439b8d: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 439b92: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 439b96: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 439b99: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 439b9b: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 439b9d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 439ba0: rep stosb byte ptr es:[edi], al */
L_439ba2:
	m->ecx = M32((DWORD)(0x9dd6ecu));	/* 439ba2: mov ecx, dword ptr [0x9dd6ec] */
	m->edx = M32((DWORD)(0x9dd6e8u));	/* 439ba8: mov edx, dword ptr [0x9dd6e8] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 439bae: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x6cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439bb2: add ecx, 0x6c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439bb5: push eax */
	{ DWORD a_ = m->edx, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 439bb6: add edx, 0x94 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439bbc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439bbd: push edx */
	m->esp -= 4; M32(m->esp) = 0x439bc3u; native_call(m, 0x402620u);	/* 439bbe: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439bc3: add esp, 0xc */
L_439bc6:
	m->eax = M32((DWORD)(0x9dd564u));	/* 439bc6: mov eax, dword ptr [0x9dd564] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439bcb: test eax, eax */
	if (m->zf) goto L_439bd8;	/* 439bcd: je 0x439bd8 */
	m->eax = M32((DWORD)(0x68039cu));	/* 439bcf: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439bd4: test eax, eax */
	if (!m->zf) goto L_439c38;	/* 439bd6: jne 0x439c38 */
L_439bd8:
	m->edi = 0x9dd202u;	/* 439bd8: mov edi, 0x9dd202 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 439bdd: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 439be0: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 439be2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 439be4: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 439be6: dec ecx */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 439be7: lea edi, [esp + 0x14] */
	m->edx = m->ecx;	/* 439beb: mov edx, ecx */
	m->ecx = 0x7u;	/* 439bed: mov ecx, 7 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 439bf2: rep stosd dword ptr es:[edi], eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439bf4: test edx, edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 439bf6: stosw word ptr es:[edi], ax */
	if (m->zf || m->sf != m->of) goto L_439c11;	/* 439bf8: jle 0x439c11 */
	m->ecx = m->edx;	/* 439bfa: mov ecx, edx */
	m->eax = 0x2a2a2a2au;	/* 439bfc: mov eax, 0x2a2a2a2a */
	m->edi = (DWORD)(m->esp + 0x14u);	/* 439c01: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 439c05: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 439c08: rep stosd dword ptr es:[edi], eax */
	m->ecx = m->edx;	/* 439c0a: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 439c0c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = (BYTE)(m->eax & 0xffu); m->edi += 1; m->ecx--; }	/* 439c0f: rep stosb byte ptr es:[edi], al */
L_439c11:
	m->ecx = M32((DWORD)(0x9dd6ecu));	/* 439c11: mov ecx, dword ptr [0x9dd6ec] */
	m->edx = M32((DWORD)(0x9dd6e8u));	/* 439c17: mov edx, dword ptr [0x9dd6e8] */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 439c1d: lea eax, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439c21: add ecx, 0x9c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439c27: push eax */
	{ DWORD a_ = m->edx, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 439c28: add edx, 0x94 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439c2e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439c2f: push edx */
	m->esp -= 4; M32(m->esp) = 0x439c35u; native_call(m, 0x402620u);	/* 439c30: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439c35: add esp, 0xc */
L_439c38:
	m->eax = M32((DWORD)(0x9dd6ccu));	/* 439c38: mov eax, dword ptr [0x9dd6cc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439c3d: test eax, eax */
	if (m->zf) goto L_439c4a;	/* 439c3f: je 0x439c4a */
	m->eax = M32((DWORD)(0x68039cu));	/* 439c41: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439c46: test eax, eax */
	if (!m->zf) goto L_439c6f;	/* 439c48: jne 0x439c6f */
L_439c4a:
	m->eax = M32((DWORD)(0x9dd6ecu));	/* 439c4a: mov eax, dword ptr [0x9dd6ec] */
	m->ecx = M32((DWORD)(0x9dd6e8u));	/* 439c4f: mov ecx, dword ptr [0x9dd6e8] */
	{ DWORD a_ = m->eax, b_ = 0xccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439c55: add eax, 0xcc */
	{ DWORD v_ = 0x9dd20eu; m->esp -= 4; M32(m->esp) = v_; }	/* 439c5a: push 0x9dd20e */
	{ DWORD a_ = m->ecx, b_ = 0x94u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439c5f: add ecx, 0x94 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439c65: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439c66: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439c6cu; native_call(m, 0x402620u);	/* 439c67: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439c6c: add esp, 0xc */
L_439c6f:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 439c6f: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 439c71: xor esi, esi */
	m->edi = 0x7517a4u;	/* 439c73: mov edi, 0x7517a4 */
L_439c78:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439c78: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x439c83u; native_call(m, M32(0x4a9224u));	/* 439c7d: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 439c83: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 439c88: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 439c8a: and edx, 0x800001ff */
	if (!m->sf) goto L_439c9a;	/* 439c90: jns 0x439c9a */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 439c92: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 439c93: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 439c99: inc edx */
L_439c9a:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439c9a: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 439c9b: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 439ca1: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 439ca2: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439ca8: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 439caa: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 439cad: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x439cb6u; native_call(m, 0x4566c0u);	/* 439cb1: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 439cb6: mov eax, dword ptr [esp + 0x10] */
	m->edx = (DWORD)(m->ebx + 0x4u);	/* 439cba: lea edx, [ebx + 4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 439cbd: cmp eax, edx */
	if (!m->zf) goto L_439d1a;	/* 439cbf: jne 0x439d1a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439cc1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439cc6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439ccb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439cd0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x439cd7u; native_call(m, m->ebp);	/* 439cd5: call ebp */
	m->ecx = M32((DWORD)(0x9dd6f4u));	/* 439cd7: mov ecx, dword ptr [0x9dd6f4] */
	m->eax = M32((DWORD)(0x9dd6e8u));	/* 439cdd: mov eax, dword ptr [0x9dd6e8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439ce2: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 439ce4: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439ce7: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439cea: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xfau);	/* 439ceb: lea edx, [esi + eax + 0xfa] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439cf2: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x5au);	/* 439cf3: lea eax, [esi + eax + 0x5a] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439cf7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439cf8: push eax */
	m->esp -= 4; M32(m->esp) = 0x439cfeu; native_call(m, 0x4283e0u);	/* 439cf9: call 0x4283e0 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 439cfe: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 439d04: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 439d0a: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d0f: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 439d10: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d16: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439d17: push eax */
	goto L_439d71;	/* 439d18: jmp 0x439d71 */
L_439d1a:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 439d1a: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439d1f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439d24: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439d29: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x439d30u; native_call(m, m->ebp);	/* 439d2e: call ebp */
	m->ecx = M32((DWORD)(0x9dd6f4u));	/* 439d30: mov ecx, dword ptr [0x9dd6f4] */
	m->eax = M32((DWORD)(0x9dd6e8u));	/* 439d36: mov eax, dword ptr [0x9dd6e8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439d3b: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 439d3d: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439d40: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d43: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xfau);	/* 439d44: lea edx, [esi + eax + 0xfa] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d4b: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x5au);	/* 439d4c: lea eax, [esi + eax + 0x5a] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d50: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439d51: push eax */
	m->esp -= 4; M32(m->esp) = 0x439d57u; native_call(m, 0x4283e0u);	/* 439d52: call 0x4283e0 */
	m->ecx = M32((DWORD)(0x9dd344u));	/* 439d57: mov ecx, dword ptr [0x9dd344] */
	m->edx = M32((DWORD)(0x9dd340u));	/* 439d5d: mov edx, dword ptr [0x9dd340] */
	m->eax = M32((DWORD)(0x9dd33cu));	/* 439d63: mov eax, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d68: push ecx */
	m->ecx = M32((DWORD)(0x9dd338u));	/* 439d69: mov ecx, dword ptr [0x9dd338] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d6f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439d70: push eax */
L_439d71:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d71: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 439d72: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x439d7cu; native_call(m, 0x41f0e0u);	/* 439d77: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd6e8u));	/* 439d7c: mov eax, dword ptr [0x9dd6e8] */
	m->ecx = M32((DWORD)(0x9dd6f4u));	/* 439d81: mov ecx, dword ptr [0x9dd6f4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439d87: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439d8a: add ecx, -0x38 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xfau);	/* 439d8d: lea edx, [esi + eax + 0xfa] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 439d94: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d95: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x5au);	/* 439d96: lea edx, [esi + eax + 0x5a] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d9a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439d9b: push edx */
	m->esp -= 4; M32(m->esp) = 0x439da1u; native_call(m, 0x4029d0u);	/* 439d9c: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439da1: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 439da4: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 439daa: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 439dab: add esi, 0xc8 */
	{ DWORD a_ = m->edi, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 439db1: cmp edi, 0x7518a4 */
	if (m->sf != m->of) goto L_439c78;	/* 439db7: jl 0x439c78 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439dbd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439dc2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439dc7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439dcc: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x439dd3u; native_call(m, m->ebp);	/* 439dd1: call ebp */
	m->eax = M32((DWORD)(0x9dd6f4u));	/* 439dd3: mov eax, dword ptr [0x9dd6f4] */
	m->ecx = M32((DWORD)(0x9dd6f0u));	/* 439dd8: mov ecx, dword ptr [0x9dd6f0] */
	m->edx = M32((DWORD)(0x9dd6ecu));	/* 439dde: mov edx, dword ptr [0x9dd6ec] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439de4: push eax */
	m->eax = M32((DWORD)(0x9dd6e8u));	/* 439de5: mov eax, dword ptr [0x9dd6e8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439dea: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439deb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439dec: push eax */
	m->esp -= 4; M32(m->esp) = 0x439df2u; native_call(m, 0x428a00u);	/* 439ded: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439df2: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 439df5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 439df6: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 439df7: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 439df8: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439df9: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 439dfc: ret  */
}

/* arena_409bc0 (0x409bc0), lifted by tools/lift.py */
static void lift_409bc0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409bc0: push ecx */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 409bc1: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 409bc6: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 409bcc: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 409bcd: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 409bce: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 409bcf: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409bd0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409bd1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x409bd7u; native_call(m, 0x404460u);	/* 409bd2: call 0x404460 */
	m->esi = m->eax;	/* 409bd7: mov esi, eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 409bd9: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->esi;	/* 409bdb: mov dword ptr [esp + 0x1c], esi */
	m->esp -= 4; M32(m->esp) = 0x409be4u; native_call(m, 0x41ef90u);	/* 409bdf: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409be4: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x409bedu; native_call(m, M32(0x4a9218u));	/* 409be7: call dword ptr [0x4a9218] */
	m->edi = M32((DWORD)(0x4a9228u));	/* 409bed: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409bf3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409bf8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409bfd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409c02: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409c09u; native_call(m, m->edi);	/* 409c07: call edi */
	m->edx = M32((DWORD)(0x4deb50u));	/* 409c09: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x4dbb74u));	/* 409c0f: mov eax, dword ptr [0x4dbb74] */
	m->ecx = M32((DWORD)(0x4dbb70u));	/* 409c14: mov ecx, dword ptr [0x4dbb70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c1a: push edx */
	m->edx = M32((DWORD)(0x4dbb6cu));	/* 409c1b: mov edx, dword ptr [0x4dbb6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409c21: push eax */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 409c22: mov eax, dword ptr [0x4dbb68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c27: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c28: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409c29: push eax */
	m->esp -= 4; M32(m->esp) = 0x409c2fu; native_call(m, 0x427a90u);	/* 409c2a: call 0x427a90 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409c2f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409c34: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409c39: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409c3e: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 409c40: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x409c4au; native_call(m, 0x41f0e0u);	/* 409c45: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb74u));	/* 409c4a: mov ecx, dword ptr [0x4dbb74] */
	m->edx = M32((DWORD)(0x4dbb70u));	/* 409c50: mov edx, dword ptr [0x4dbb70] */
	m->eax = M32((DWORD)(0x4dbb6cu));	/* 409c56: mov eax, dword ptr [0x4dbb6c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409c5b: add ecx, -0x20 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409c5e: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c60: push ecx */
	m->ecx = M32((DWORD)(0x4dbb68u));	/* 409c61: mov ecx, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->edx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 409c67: add edx, -0x20 */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409c6a: add eax, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c6d: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409c6e: add ecx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409c71: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c72: push ecx */
	m->esp -= 4; M32(m->esp) = 0x409c78u; native_call(m, 0x427970u);	/* 409c73: call 0x427970 */
	m->edx = M32((DWORD)(0x4dbaa4u));	/* 409c78: mov edx, dword ptr [0x4dbaa4] */
	m->eax = M32((DWORD)(0x4dbaa0u));	/* 409c7e: mov eax, dword ptr [0x4dbaa0] */
	m->ecx = M32((DWORD)(0x4dba9cu));	/* 409c83: mov ecx, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c89: push edx */
	m->edx = M32((DWORD)(0x4dba98u));	/* 409c8a: mov edx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409c90: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c91: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409c92: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 409c93: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x409c9du; native_call(m, 0x41f0e0u);	/* 409c98: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb6cu));	/* 409c9d: mov eax, dword ptr [0x4dbb6c] */
	m->ecx = M32((DWORD)(0x4dbb68u));	/* 409ca2: mov ecx, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409ca8: add esp, 0x50 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409cab: add eax, 0x10 */
	{ DWORD a_ = m->ecx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409cae: add ecx, 0x50 */
	{ DWORD v_ = 0x751fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 409cb1: push 0x751fa4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409cb6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409cb7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x409cbdu; native_call(m, 0x4028b0u);	/* 409cb8: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409cbd: add esp, 0xc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 409cc0: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x409ccbu; native_call(m, M32(0x4a9224u));	/* 409cc5: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 409ccb: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 409cd0: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 409cd2: and edx, 0x800001ff */
	if (!m->sf) goto L_409ce2;	/* 409cd8: jns 0x409ce2 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 409cda: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 409cdb: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 409ce1: inc edx */
L_409ce2:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409ce2: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 409ce3: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 409ce9: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 409cea: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409cf0: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 409cf2: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 409cf5: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x409cfeu; native_call(m, 0x4566c0u);	/* 409cf9: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409cfe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d03: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d08: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d0d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409d14u; native_call(m, m->edi);	/* 409d12: call edi */
	m->edx = M32((DWORD)(0x4dbb6cu));	/* 409d14: mov edx, dword ptr [0x4dbb6c] */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 409d1a: mov eax, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 409d1f: add edx, 0x64 */
	{ DWORD v_ = 0x752024u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d22: push 0x752024 */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409d27: add eax, 0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409d2a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409d2b: push eax */
	m->esp -= 4; M32(m->esp) = 0x409d31u; native_call(m, 0x402620u);	/* 409d2c: call 0x402620 */
	m->ecx = M32((DWORD)(0x4dbb6cu));	/* 409d31: mov ecx, dword ptr [0x4dbb6c] */
	m->edx = M32((DWORD)(0x4dbb68u));	/* 409d37: mov edx, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->ecx, b_ = 0x96u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409d3d: add ecx, 0x96 */
	{ DWORD v_ = 0x752124u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d43: push 0x752124 */
	{ DWORD a_ = m->edx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 409d48: add edx, 0x40 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409d4b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409d4c: push edx */
	m->esp -= 4; M32(m->esp) = 0x409d52u; native_call(m, 0x402620u);	/* 409d4d: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d52: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d57: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d5c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d61: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d66: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x409d70u; native_call(m, 0x41f0e0u);	/* 409d6b: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x68039cu));	/* 409d70: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409d75: add esp, 0x2c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 409d78: test eax, eax */
	if (!m->zf) goto L_409d9f;	/* 409d7a: jne 0x409d9f */
	m->eax = M32((DWORD)(0x4dbb6cu));	/* 409d7c: mov eax, dword ptr [0x4dbb6c] */
	m->ecx = M32((DWORD)(0x4dbb68u));	/* 409d81: mov ecx, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409d87: add eax, 0x64 */
	{ DWORD v_ = 0x4db560u; m->esp -= 4; M32(m->esp) = v_; }	/* 409d8a: push 0x4db560 */
	{ DWORD a_ = m->ecx, b_ = 0xc2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409d8f: add ecx, 0xc2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409d95: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409d96: push ecx */
	m->esp -= 4; M32(m->esp) = 0x409d9cu; native_call(m, 0x402620u);	/* 409d97: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409d9c: add esp, 0xc */
L_409d9f:
	m->eax = M32((DWORD)(0x4dbbd0u));	/* 409d9f: mov eax, dword ptr [0x4dbbd0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 409da4: test eax, eax */
	if (!m->zf) goto L_409eb9;	/* 409da6: jne 0x409eb9 */
	{ DWORD a_ = m->esi, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 409dac: sub esi, 0 */
	if (m->zf) goto L_409e35;	/* 409daf: je 0x409e35 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 409db5: sub esi, 2 */
	if (!m->zf) goto L_409eb9;	/* 409db8: jne 0x409eb9 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409dbe: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 409dc3: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 409dc8: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 409dcd: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 409dd2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x409ddcu; native_call(m, 0x41f0e0u);	/* 409dd7: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dbb6cu));	/* 409ddc: mov edx, dword ptr [0x4dbb6c] */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 409de2: mov eax, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->edx, b_ = 0x96u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 409de7: add edx, 0x96 */
	{ DWORD v_ = 0x752124u; m->esp -= 4; M32(m->esp) = v_; }	/* 409ded: push 0x752124 */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409df2: add eax, 0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409df5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409df6: push eax */
	m->esp -= 4; M32(m->esp) = 0x409dfcu; native_call(m, 0x402620u);	/* 409df7: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409dfc: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e01: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 409e03: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e08: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e0d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x409e17u; native_call(m, 0x41f0e0u);	/* 409e12: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dbb6cu));	/* 409e17: mov ecx, dword ptr [0x4dbb6c] */
	m->edx = M32((DWORD)(0x4dbb68u));	/* 409e1d: mov edx, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->ecx, b_ = 0x95u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409e23: add ecx, 0x95 */
	{ DWORD v_ = 0x752124u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e29: push 0x752124 */
	{ DWORD a_ = m->edx, b_ = 0x3fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 409e2e: add edx, 0x3f */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409e31: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409e32: push edx */
	goto L_409eb1;	/* 409e33: jmp 0x409eb1 */
L_409e35:
	m->eax = M32((DWORD)(0x68039cu));	/* 409e35: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 409e3a: test eax, eax */
	if (!m->zf) goto L_409eb9;	/* 409e3c: jne 0x409eb9 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e3e: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 409e43: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 409e48: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 409e4d: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e52: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x409e5cu; native_call(m, 0x41f0e0u);	/* 409e57: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb6cu));	/* 409e5c: mov eax, dword ptr [0x4dbb6c] */
	m->ecx = M32((DWORD)(0x4dbb68u));	/* 409e61: mov ecx, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409e67: add eax, 0x64 */
	{ DWORD v_ = 0x4db560u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e6a: push 0x4db560 */
	{ DWORD a_ = m->ecx, b_ = 0xc2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409e6f: add ecx, 0xc2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409e75: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409e76: push ecx */
	m->esp -= 4; M32(m->esp) = 0x409e7cu; native_call(m, 0x402620u);	/* 409e77: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e7c: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e81: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 409e83: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e88: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 409e8d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x409e97u; native_call(m, 0x41f0e0u);	/* 409e92: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dbb6cu));	/* 409e97: mov edx, dword ptr [0x4dbb6c] */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 409e9d: mov eax, dword ptr [0x4dbb68] */
	{ DWORD a_ = m->edx, b_ = 0x63u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 409ea2: add edx, 0x63 */
	{ DWORD v_ = 0x4db560u; m->esp -= 4; M32(m->esp) = v_; }	/* 409ea5: push 0x4db560 */
	{ DWORD a_ = m->eax, b_ = 0xc1u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409eaa: add eax, 0xc1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409eaf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409eb0: push eax */
L_409eb1:
	m->esp -= 4; M32(m->esp) = 0x409eb6u; native_call(m, 0x402620u);	/* 409eb1: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409eb6: add esp, 0x40 */
L_409eb9:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 409eb9: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 409ebb: xor esi, esi */
	m->ebx = 0x7521a4u;	/* 409ebd: mov ebx, 0x7521a4 */
L_409ec2:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 409ec2: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x409ecdu; native_call(m, M32(0x4a9224u));	/* 409ec7: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 409ecd: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 409ed2: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 409ed4: and ecx, 0x800001ff */
	if (!m->sf) goto L_409ee4;	/* 409eda: jns 0x409ee4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 409edc: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 409edd: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 409ee3: inc ecx */
L_409ee4:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 409ee4: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 409ee5: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409eeb: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 409eec: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 409eee: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 409ef4: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 409ef7: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x409f00u; native_call(m, 0x4566c0u);	/* 409efb: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f00: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f05: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f0a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f0f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409f16u; native_call(m, m->edi);	/* 409f14: call edi */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 409f16: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebp + 0x3u);	/* 409f1a: lea eax, [ebp + 3] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 409f1d: cmp ecx, eax */
	if (!m->zf) goto L_409f89;	/* 409f1f: jne 0x409f89 */
	m->eax = M32((DWORD)(0x4dbbd0u));	/* 409f21: mov eax, dword ptr [0x4dbbd0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 409f26: test eax, eax */
	if (!m->zf) goto L_409f89;	/* 409f28: jne 0x409f89 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f2a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f2f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f34: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f39: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409f40u; native_call(m, m->edi);	/* 409f3e: call edi */
	m->ecx = M32((DWORD)(0x4dbb6cu));	/* 409f40: mov ecx, dword ptr [0x4dbb6c] */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 409f46: mov eax, dword ptr [0x4dbb68] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f4b: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfcu);	/* 409f4d: lea edx, [ecx + 0xfc] */
	{ DWORD a_ = m->ecx, b_ = 0xdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409f53: add ecx, 0xdc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409f59: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x96u);	/* 409f5a: lea edx, [esi + eax + 0x96] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409f61: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x32u);	/* 409f62: lea eax, [esi + eax + 0x32] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409f66: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409f67: push eax */
	m->esp -= 4; M32(m->esp) = 0x409f6du; native_call(m, 0x4282f0u);	/* 409f68: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4dbaa4u));	/* 409f6d: mov ecx, dword ptr [0x4dbaa4] */
	m->edx = M32((DWORD)(0x4dbaa0u));	/* 409f73: mov edx, dword ptr [0x4dbaa0] */
	m->eax = M32((DWORD)(0x4dba9cu));	/* 409f79: mov eax, dword ptr [0x4dba9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409f7e: push ecx */
	m->ecx = M32((DWORD)(0x4dba98u));	/* 409f7f: mov ecx, dword ptr [0x4dba98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409f85: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409f86: push eax */
	goto L_409fe6;	/* 409f87: jmp 0x409fe6 */
L_409f89:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 409f89: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f8e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f93: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 409f98: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x409f9fu; native_call(m, m->edi);	/* 409f9d: call edi */
	m->ecx = M32((DWORD)(0x4dbb6cu));	/* 409f9f: mov ecx, dword ptr [0x4dbb6c] */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 409fa5: mov eax, dword ptr [0x4dbb68] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 409faa: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfcu);	/* 409fac: lea edx, [ecx + 0xfc] */
	{ DWORD a_ = m->ecx, b_ = 0xdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409fb2: add ecx, 0xdc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409fb8: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x96u);	/* 409fb9: lea edx, [esi + eax + 0x96] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409fc0: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x32u);	/* 409fc1: lea eax, [esi + eax + 0x32] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409fc5: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409fc6: push eax */
	m->esp -= 4; M32(m->esp) = 0x409fccu; native_call(m, 0x4282f0u);	/* 409fc7: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4db8acu));	/* 409fcc: mov ecx, dword ptr [0x4db8ac] */
	m->edx = M32((DWORD)(0x4db8a8u));	/* 409fd2: mov edx, dword ptr [0x4db8a8] */
	m->eax = M32((DWORD)(0x4db8a4u));	/* 409fd8: mov eax, dword ptr [0x4db8a4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409fdd: push ecx */
	m->ecx = M32((DWORD)(0x4db8a0u));	/* 409fde: mov ecx, dword ptr [0x4db8a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 409fe4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 409fe5: push eax */
L_409fe6:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 409fe6: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 409fe7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x409ff1u; native_call(m, 0x41f0e0u);	/* 409fec: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 409ff1: mov eax, dword ptr [0x4dbb68] */
	m->ecx = M32((DWORD)(0x4dbb6cu));	/* 409ff6: mov ecx, dword ptr [0x4dbb6c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 409ffc: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xe4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 409fff: add ecx, 0xe4 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x96u);	/* 40a005: lea edx, [esi + eax + 0x96] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a00c: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a00d: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x32u);	/* 40a00e: lea edx, [esi + eax + 0x32] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a012: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a013: push edx */
	m->esp -= 4; M32(m->esp) = 0x40a019u; native_call(m, 0x4029d0u);	/* 40a014: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a019: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 40a01c: add ebx, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 40a022: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40a023: add esi, 0x78 */
	{ DWORD a_ = m->ebx, b_ = 0x752324u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40a026: cmp ebx, 0x752324 */
	if (m->sf != m->of) goto L_409ec2;	/* 40a02c: jl 0x409ec2 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a032: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a037: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a03c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40a041: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40a048u; native_call(m, m->edi);	/* 40a046: call edi */
	m->eax = M32((DWORD)(0x4dbb74u));	/* 40a048: mov eax, dword ptr [0x4dbb74] */
	m->ecx = M32((DWORD)(0x4dbb70u));	/* 40a04d: mov ecx, dword ptr [0x4dbb70] */
	m->edx = M32((DWORD)(0x4dbb6cu));	/* 40a053: mov edx, dword ptr [0x4dbb6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a059: push eax */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 40a05a: mov eax, dword ptr [0x4dbb68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a05f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40a060: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40a061: push eax */
	m->esp -= 4; M32(m->esp) = 0x40a067u; native_call(m, 0x428a00u);	/* 40a062: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40a067: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 40a06a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40a06b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40a06c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40a06d: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 40a06e: pop ecx */
	m->esp += 4 + 0; return;	/* 40a06f: ret  */
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
