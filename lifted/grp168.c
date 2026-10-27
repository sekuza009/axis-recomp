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

static void lift_41fa40(X86 *m);

/* menu_frame (0x41fa40), lifted by tools/lift.py */
static void lift_41fa40(X86 *m)
{
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41fa40: fld dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4dda44u));	/* 41fa46: fadd dword ptr [0x4dda44] */
	MF((DWORD)(0x4dda44u)) = (float)ST(0);	/* 41fa4c: fst dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94ecu)); FPOP();	/* 41fa52: fcomp dword ptr [0x4a94ec] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41fa58: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41fa5a: test ah, 0x41 */
	if (!m->zf) goto L_41fa69;	/* 41fa5d: jne 0x41fa69 */
	M32((DWORD)(0x4dda44u)) = 0x42c80000u;	/* 41fa5f: mov dword ptr [0x4dda44], 0x42c80000 */
L_41fa69:
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41fa69: mov eax, dword ptr [0x76d3e8] */
	m->ecx = M32((DWORD)(0x67ef0cu));	/* 41fa6e: mov ecx, dword ptr [0x67ef0c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fa74: cmp eax, ecx */
	if (m->zf) goto L_41fa7d;	/* 41fa76: je 0x41fa7d */
	m->esp -= 4; M32(m->esp) = 0x41fa7du; native_call(m, 0x41f970u);	/* 41fa78: call 0x41f970 */
L_41fa7d:
	m->eax = M32((DWORD)(0x9da49cu));	/* 41fa7d: mov eax, dword ptr [0x9da49c] */
	{ DWORD a_ = m->eax, b_ = 0x69u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fa82: cmp eax, 0x69 */
	if (m->zf) goto L_41fa96;	/* 41fa85: je 0x41fa96 */
	{ DWORD a_ = m->eax, b_ = 0x68u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fa87: cmp eax, 0x68 */
	if (m->zf) goto L_41fa96;	/* 41fa8a: je 0x41fa96 */
	m->esp -= 4; M32(m->esp) = 0x41fa91u; native_call(m, 0x445e40u);	/* 41fa8c: call 0x445e40 */
	m->esp -= 4; M32(m->esp) = 0x41fa96u; native_call(m, 0x4319d0u);	/* 41fa91: call 0x4319d0 */
L_41fa96:
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x12cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fa96: cmp dword ptr [0x76d3e8], 0x12c */
	if (!m->zf) goto L_41fb4e;	/* 41faa0: jne 0x41fb4e */
	m->eax = M32((DWORD)(0x9db994u));	/* 41faa6: mov eax, dword ptr [0x9db994] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41faab: test eax, eax */
	if (m->zf) goto L_41fb4e;	/* 41faad: je 0x41fb4e */
	m->eax = M32((DWORD)(0x4df900u));	/* 41fab3: mov eax, dword ptr [0x4df900] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fab8: test eax, eax */
	if (!m->zf) goto L_41fb4e;	/* 41faba: jne 0x41fb4e */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41fac0: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9468u));	/* 41fac6: fmul dword ptr [0x4a9468] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4e1870u));	/* 41facc: fsubr dword ptr [0x4e1870] */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 41fad2: fstp dword ptr [0x4e1870] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 41fad8: fld dword ptr [0x4df02c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 41fade: fadd dword ptr [0x4a9418] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 41fae4: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda48u)));	/* 41faea: fld dword ptr [0x4dda48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 41faf0: fadd dword ptr [0x4b071c] */
	MF((DWORD)(0x4dda48u)) = (float)ST(0);	/* 41faf6: fst dword ptr [0x4dda48] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 41fafc: fld dword ptr [0x4e1870] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9420u)); FPOP();	/* 41fb02: fcomp dword ptr [0x4a9420] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41fb08: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41fb0a: test ah, 1 */
	if (m->zf) goto L_41fb19;	/* 41fb0d: je 0x41fb19 */
	M32((DWORD)(0x4e1870u)) = 0x3c23d70au;	/* 41fb0f: mov dword ptr [0x4e1870], 0x3c23d70a */
L_41fb19:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f4u)); FPOP();	/* 41fb19: fcomp dword ptr [0x4a93f4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41fb1f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41fb21: test ah, 1 */
	if (!m->zf) goto L_41fb4e;	/* 41fb24: jne 0x41fb4e */
	M32((DWORD)(0x76d3e8u)) = 0x270fu;	/* 41fb26: mov dword ptr [0x76d3e8], 0x270f */
	M32((DWORD)(0x67ef20u)) = 0x270fu;	/* 41fb30: mov dword ptr [0x67ef20], 0x270f */
	M32((DWORD)(0x9db990u)) = 0x1u;	/* 41fb3a: mov dword ptr [0x9db990], 1 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 41fb44: mov dword ptr [0x4dda44], 0 */
L_41fb4e:
	m->esp -= 4; M32(m->esp) = 0x41fb53u; native_call(m, 0x41f820u);	/* 41fb4e: call 0x41f820 */
	m->eax = M32((DWORD)(0x76d3e8u));	/* 41fb53: mov eax, dword ptr [0x76d3e8] */
	{ DWORD a_ = m->eax, b_ = 0x1f4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fb58: cmp eax, 0x1f4 */
	if (!m->zf && m->sf == m->of) goto L_41fbaa;	/* 41fb5d: jg 0x41fbaa */
	if (m->zf) goto L_41fba3;	/* 41fb5f: je 0x41fba3 */
	{ DWORD a_ = m->eax, b_ = 0xd2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fb61: cmp eax, 0xd2 */
	if (!m->zf && m->sf == m->of) goto L_41fb89;	/* 41fb66: jg 0x41fb89 */
	if (m->zf) goto L_41fb82;	/* 41fb68: je 0x41fb82 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41fb6a: sub eax, 0x64 */
	if (m->zf) goto L_41fb7b;	/* 41fb6d: je 0x41fb7b */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41fb6f: sub eax, 0x64 */
	if (!m->zf) goto L_41fbe0;	/* 41fb72: jne 0x41fbe0 */
	m->esp -= 4; M32(m->esp) = 0x41fb79u; native_call(m, 0x41f8d0u);	/* 41fb74: call 0x41f8d0 */
	goto L_41fbe0;	/* 41fb79: jmp 0x41fbe0 */
L_41fb7b:
	m->esp -= 4; M32(m->esp) = 0x41fb80u; native_call(m, 0x41f540u);	/* 41fb7b: call 0x41f540 */
	goto L_41fbe0;	/* 41fb80: jmp 0x41fbe0 */
L_41fb82:
	m->esp -= 4; M32(m->esp) = 0x41fb87u; native_call(m, 0x44f860u);	/* 41fb82: call 0x44f860 */
	goto L_41fbe0;	/* 41fb87: jmp 0x41fbe0 */
L_41fb89:
	{ DWORD a_ = m->eax, b_ = 0x12cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41fb89: sub eax, 0x12c */
	if (m->zf) goto L_41fb9c;	/* 41fb8e: je 0x41fb9c */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41fb90: sub eax, 0x64 */
	if (!m->zf) goto L_41fbe0;	/* 41fb93: jne 0x41fbe0 */
	m->esp -= 4; M32(m->esp) = 0x41fb9au; native_call(m, 0x40d450u);	/* 41fb95: call 0x40d450 */
	goto L_41fbe0;	/* 41fb9a: jmp 0x41fbe0 */
L_41fb9c:
	m->esp -= 4; M32(m->esp) = 0x41fba1u; native_call(m, 0x443530u);	/* 41fb9c: call 0x443530 */
	goto L_41fbe0;	/* 41fba1: jmp 0x41fbe0 */
L_41fba3:
	m->esp -= 4; M32(m->esp) = 0x41fba8u; native_call(m, 0x44aa40u);	/* 41fba3: call 0x44aa40 */
	goto L_41fbe0;	/* 41fba8: jmp 0x41fbe0 */
L_41fbaa:
	{ DWORD a_ = m->eax, b_ = 0x320u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fbaa: cmp eax, 0x320 */
	if (!m->zf && m->sf == m->of) goto L_41fbd4;	/* 41fbaf: jg 0x41fbd4 */
	if (m->zf) goto L_41fbcd;	/* 41fbb1: je 0x41fbcd */
	{ DWORD a_ = m->eax, b_ = 0x258u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41fbb3: sub eax, 0x258 */
	if (m->zf) goto L_41fbc6;	/* 41fbb8: je 0x41fbc6 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41fbba: sub eax, 0x64 */
	if (!m->zf) goto L_41fbe0;	/* 41fbbd: jne 0x41fbe0 */
	m->esp -= 4; M32(m->esp) = 0x41fbc4u; native_call(m, 0x41e040u);	/* 41fbbf: call 0x41e040 */
	goto L_41fbe0;	/* 41fbc4: jmp 0x41fbe0 */
L_41fbc6:
	m->esp -= 4; M32(m->esp) = 0x41fbcbu; native_call(m, 0x427920u);	/* 41fbc6: call 0x427920 */
	goto L_41fbe0;	/* 41fbcb: jmp 0x41fbe0 */
L_41fbcd:
	m->esp -= 4; M32(m->esp) = 0x41fbd2u; native_call(m, 0x43ef70u);	/* 41fbcd: call 0x43ef70 */
	goto L_41fbe0;	/* 41fbd2: jmp 0x41fbe0 */
L_41fbd4:
	{ DWORD a_ = m->eax, b_ = 0x384u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fbd4: cmp eax, 0x384 */
	if (!m->zf) goto L_41fbe0;	/* 41fbd9: jne 0x41fbe0 */
	m->esp -= 4; M32(m->esp) = 0x41fbe0u; native_call(m, 0x445be0u);	/* 41fbdb: call 0x445be0 */
L_41fbe0:
	m->eax = M32((DWORD)(0x4df900u));	/* 41fbe0: mov eax, dword ptr [0x4df900] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fbe5: test eax, eax */
	if (m->zf) goto L_41fbee;	/* 41fbe7: je 0x41fbee */
	m->esp -= 4; M32(m->esp) = 0x41fbeeu; native_call(m, 0x4290d0u);	/* 41fbe9: call 0x4290d0 */
L_41fbee:
	m->eax = M32((DWORD)(0x68039cu));	/* 41fbee: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fbf3: test eax, eax */
	if (m->zf) goto L_41fc0d;	/* 41fbf5: je 0x41fc0d */
	m->ecx = M32((DWORD)(0x9da3dcu));	/* 41fbf7: mov ecx, dword ptr [0x9da3dc] */
	m->edx = M32((DWORD)(0x9da3d8u));	/* 41fbfd: mov edx, dword ptr [0x9da3d8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41fc03: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41fc04: push edx */
	m->esp -= 4; M32(m->esp) = 0x41fc0au; native_call(m, 0x428940u);	/* 41fc05: call 0x428940 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41fc0a: add esp, 8 */
L_41fc0d:
	m->esp -= 4; M32(m->esp) = 0x41fc13u; native_call(m, M32(0x4a9218u));	/* 41fc0d: call dword ptr [0x4a9218] */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41fc13: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_41fc2d;	/* 41fc1d: je 0x41fc2d */
	m->eax = M32((DWORD)(0x9f6838u));	/* 41fc1f: mov eax, dword ptr [0x9f6838] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fc24: test eax, eax */
	if (!m->zf) goto L_41fc2d;	/* 41fc26: jne 0x41fc2d */
	m->esp -= 4; M32(m->esp) = 0x41fc2du; native_call(m, 0x41fc2du + M32(0x41fc29u));	/* 0x429bc0 unless the patch DLL retargets it */	/* 41fc28: call 0x429bc0 */
L_41fc2d:
	{ DWORD v_ = 0xbe2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41fc2d: push 0xbe2 */
	m->esp -= 4; M32(m->esp) = 0x41fc38u; native_call(m, M32(0x4a922cu));	/* 41fc32: call dword ptr [0x4a922c] */
	m->esp -= 4; M32(m->esp) = 0x41fc3eu; native_call(m, M32(0x4a91f0u));	/* 41fc38: call dword ptr [0x4a91f0] */
	m->eax = M32((DWORD)(0x76d480u));	/* 41fc3e: mov eax, dword ptr [0x76d480] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41fc43: push eax */
	m->esp -= 4; M32(m->esp) = 0x41fc4au; native_call(m, M32(0x4a9028u));	/* 41fc44: call dword ptr [0x4a9028] */
	m->eax = M32((DWORD)(0x4e0464u));	/* 41fc4a: mov eax, dword ptr [0x4e0464] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41fc4f: dec eax */
	if (m->zf) goto L_41fc76;	/* 41fc50: je 0x41fc76 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41fc52: dec eax */
	if (!m->zf) goto L_41fc9b;	/* 41fc53: jne 0x41fc9b */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 41fc55: fld dword ptr [0x68038c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94e8u)); FPOP();	/* 41fc5b: fcomp dword ptr [0x4a94e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41fc61: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41fc63: test ah, 1 */
	if (m->zf) goto L_41fc9b;	/* 41fc66: je 0x41fc9b */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 41fc68: fld dword ptr [0x68038c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 41fc6e: fadd dword ptr [0x4a93d0] */
	goto L_41fc95;	/* 41fc74: jmp 0x41fc95 */
L_41fc76:
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 41fc76: fld dword ptr [0x68038c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 41fc7c: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41fc82: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41fc84: test ah, 0x41 */
	if (!m->zf) goto L_41fc9b;	/* 41fc87: jne 0x41fc9b */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68038cu)));	/* 41fc89: fld dword ptr [0x68038c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 41fc8f: fsub dword ptr [0x4a93d0] */
L_41fc95:
	MF((DWORD)(0x68038cu)) = (float)ST(0); FPOP();	/* 41fc95: fstp dword ptr [0x68038c] */
L_41fc9b:
	m->esp -= 4; M32(m->esp) = 0x41fca0u; { long double r_ = native_call_fp(m, 0x4301e0u); FPUSH(r_); }	/* 41fc9b: call 0x4301e0 */
	m->eax = M32((DWORD)(0x83a9d4u));	/* 41fca0: mov eax, dword ptr [0x83a9d4] */
	MDBL((DWORD)(0x9db980u)) = (double)ST(0);	/* 41fca5: fst qword ptr [0x9db980] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41fcab: test eax, eax */
	if (m->zf) goto L_41fcfd;	/* 41fcad: je 0x41fcfd */
	MDBL((DWORD)(0x4dd550u)) = (double)ST(0);	/* 41fcaf: fst qword ptr [0x4dd550] */
	m->eax = M32((DWORD)(0x4dd0b0u));	/* 41fcb5: mov eax, dword ptr [0x4dd0b0] */
	{ long double t = ST(0); FPUSH(t); }	/* 41fcba: fld st(0) */
	ST(0) = ST(0) - (long double)*(const double *)(DWORD)(0x4dd0a0u);	/* 41fcbc: fsub qword ptr [0x4dd0a0] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 41fcc2: inc eax */
	M32((DWORD)(0x4dd0b0u)) = m->eax;	/* 41fcc3: mov dword ptr [0x4dd0b0], eax */
	MDBL((DWORD)(0x4dd978u)) = (double)ST(0);	/* 41fcc8: fst qword ptr [0x4dd978] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(0x4a94e0u)); FPOP();	/* 41fcce: fcomp qword ptr [0x4a94e0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41fcd4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41fcd6: test ah, 1 */
	if (!m->zf) goto L_41fcfd;	/* 41fcd9: jne 0x41fcfd */
	FPUSH((long double)(int)M32((DWORD)(0x4dd0b0u)));	/* 41fcdb: fild dword ptr [0x4dd0b0] */
	M32((DWORD)(0x4dd0b0u)) = 0x0u;	/* 41fce1: mov dword ptr [0x4dd0b0], 0 */
	ST(0) = ST(0) / (long double)*(const double *)(DWORD)(0x4dd978u);	/* 41fceb: fdiv qword ptr [0x4dd978] */
	MF((DWORD)(0x4dd980u)) = (float)ST(0); FPOP();	/* 41fcf1: fstp dword ptr [0x4dd980] */
	MDBL((DWORD)(0x4dd0a0u)) = (double)ST(0);	/* 41fcf7: fst qword ptr [0x4dd0a0] */
L_41fcfd:
	{ long double t = ST(0); FPUSH(t); }	/* 41fcfd: fld st(0) */
	ST(0) = ST(0) - (long double)*(const double *)(DWORD)(0x4dd0c8u);	/* 41fcff: fsub qword ptr [0x4dd0c8] */
	ST(0) = (long double)*(const double *)(DWORD)(0x4a94e0u) / ST(0);	/* 41fd05: fdivr qword ptr [0x4a94e0] */
	MDBL((DWORD)(0x4dd558u)) = (double)ST(0);	/* 41fd0b: fst qword ptr [0x4dd558] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a94dcu));	/* 41fd11: fdivr dword ptr [0x4a94dc] */
	MF((DWORD)(0x4b071cu)) = (float)ST(0);	/* 41fd17: fst dword ptr [0x4b071c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a944cu)); FPOP();	/* 41fd1d: fcomp dword ptr [0x4a944c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41fd23: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41fd25: test ah, 0x41 */
	if (!m->zf) goto L_41fd34;	/* 41fd28: jne 0x41fd34 */
	M32((DWORD)(0x4b071cu)) = 0x3f800000u;	/* 41fd2a: mov dword ptr [0x4b071c], 0x3f800000 */
L_41fd34:
	MDBL((DWORD)(0x4dd0c8u)) = (double)ST(0); FPOP();	/* 41fd34: fstp qword ptr [0x4dd0c8] */
	m->esp += 4 + 0; return;	/* 41fd3a: ret  */
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
