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

static void lift_4319d0(X86 *m);

/* menu_processKeys (0x4319d0), lifted by tools/lift.py */
static void lift_4319d0(X86 *m)
{
	m->eax = M32((DWORD)(0x68039cu));	/* 4319d0: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4319d5: test eax, eax */
	if (!m->zf) goto L_431a91;	/* 4319d7: jne 0x431a91 */
	m->esp -= 4; M32(m->esp) = 0x4319e2u; native_call(m, 0x4012c0u);	/* 4319dd: call 0x4012c0 */
	m->eax = M32((DWORD)(0x680370u));	/* 4319e2: mov eax, dword ptr [0x680370] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4319e7: test eax, eax */
	if (!m->zf) goto L_431a91;	/* 4319e9: jne 0x431a91 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9da434u)));	/* 4319ef: fld dword ptr [0x9da434] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4319f5: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4319fb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4319fd: test ah, 0x41 */
	if (m->zf) goto L_431a91;	/* 431a00: je 0x431a91 */
	m->eax = M32((DWORD)(0x4df900u));	/* 431a06: mov eax, dword ptr [0x4df900] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 431a0b: test eax, eax */
	if (m->zf) goto L_431a14;	/* 431a0d: je 0x431a14 */
	native_call(m, 0x431950u); return;	/* 431a0f: jmp 0x431950 */
L_431a14:
	m->eax = M32((DWORD)(0x76d3e8u));	/* 431a14: mov eax, dword ptr [0x76d3e8] */
	{ DWORD a_ = m->eax, b_ = 0x258u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431a19: cmp eax, 0x258 */
	if (!m->zf && m->sf == m->of) goto L_431a61;	/* 431a1e: jg 0x431a61 */
	if (m->zf) goto L_431a5c;	/* 431a20: je 0x431a5c */
	{ DWORD a_ = m->eax, b_ = 0x12cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431a22: cmp eax, 0x12c */
	if (!m->zf && m->sf == m->of) goto L_431a46;	/* 431a27: jg 0x431a46 */
	if (m->zf) goto L_431a41;	/* 431a29: je 0x431a41 */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 431a2b: sub eax, 0xc8 */
	if (m->zf) goto L_431a3c;	/* 431a30: je 0x431a3c */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 431a32: sub eax, 0xa */
	if (!m->zf) goto L_431a91;	/* 431a35: jne 0x431a91 */
	native_call(m, 0x44cdd0u); return;	/* 431a37: jmp 0x44cdd0 */
L_431a3c:
	native_call(m, 0x4318b0u); return;	/* 431a3c: jmp 0x4318b0 */
L_431a41:
	native_call(m, 0x441e00u); return;	/* 431a41: jmp 0x441e00 */
L_431a46:
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 431a46: sub eax, 0x190 */
	if (m->zf) goto L_431a57;	/* 431a4b: je 0x431a57 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 431a4d: sub eax, 0x64 */
	if (!m->zf) goto L_431a91;	/* 431a50: jne 0x431a91 */
	native_call(m, 0x447c70u); return;	/* 431a52: jmp 0x447c70 */
L_431a57:
	native_call(m, 0x4081f0u); return;	/* 431a57: jmp 0x4081f0 */
L_431a5c:
	native_call(m, 0x4230a0u); return;	/* 431a5c: jmp 0x4230a0 */
L_431a61:
	{ DWORD a_ = m->eax, b_ = 0x384u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431a61: cmp eax, 0x384 */
	if (!m->zf && m->sf == m->of) goto L_431a85;	/* 431a66: jg 0x431a85 */
	if (m->zf) goto L_431a80;	/* 431a68: je 0x431a80 */
	{ DWORD a_ = m->eax, b_ = 0x2bcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 431a6a: sub eax, 0x2bc */
	if (m->zf) goto L_431a7b;	/* 431a6f: je 0x431a7b */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 431a71: sub eax, 0x64 */
	if (!m->zf) goto L_431a91;	/* 431a74: jne 0x431a91 */
	native_call(m, 0x4378e0u); return;	/* 431a76: jmp 0x4378e0 */
L_431a7b:
	native_call(m, 0x410ab0u); return;	/* 431a7b: jmp 0x410ab0 */
L_431a80:
	native_call(m, 0x4440f0u); return;	/* 431a80: jmp 0x4440f0 */
L_431a85:
	{ DWORD a_ = m->eax, b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 431a85: cmp eax, 0x270f */
	if (!m->zf) goto L_431a91;	/* 431a8a: jne 0x431a91 */
	native_call(m, 0x42ada0u); return;	/* 431a8c: jmp 0x42ada0 */
L_431a91:
	m->esp += 4 + 0; return;	/* 431a91: ret  */
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
