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

static void lift_410ab0(X86 *m);

/* armc_processInput (0x410ab0), lifted by tools/lift.py */
static void lift_410ab0(X86 *m)
{
	m->eax = M32((DWORD)(0x4dc790u));	/* 410ab0: mov eax, dword ptr [0x4dc790] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410ab5: cmp eax, 1 */
	if (m->zf) goto L_410b11;	/* 410ab8: je 0x410b11 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410aba: test eax, eax */
	if (m->zf) goto L_410b11;	/* 410abc: je 0x410b11 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 410abe: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410ac3: test eax, eax */
	if (!m->zf) goto L_410b11;	/* 410ac5: jne 0x410b11 */
	m->eax = M32((DWORD)(0x6803a8u));	/* 410ac7: mov eax, dword ptr [0x6803a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410acc: push eax */
	m->esp -= 4; M32(m->esp) = 0x410ad2u; native_call(m, 0x401590u);	/* 410acd: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410ad2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410ad5: test eax, eax */
	if (m->zf) goto L_410b12;	/* 410ad7: je 0x410b12 */
	m->ecx = M32((DWORD)(0x9da4a0u));	/* 410ad9: mov ecx, dword ptr [0x9da4a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 410adf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x410ae5u; native_call(m, 0x401590u);	/* 410ae0: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410ae5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410ae8: test eax, eax */
	if (m->zf) goto L_410b12;	/* 410aea: je 0x410b12 */
	m->edx = M32((DWORD)(0x4e1508u));	/* 410aec: mov edx, dword ptr [0x4e1508] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410af2: push edx */
	m->esp -= 4; M32(m->esp) = 0x410af8u; native_call(m, 0x401600u);	/* 410af3: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410af8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410afb: test eax, eax */
	if (m->zf) goto L_410b12;	/* 410afd: je 0x410b12 */
	m->ecx = M32((DWORD)(0x4dd078u));	/* 410aff: mov ecx, dword ptr [0x4dd078] */
	m->eax = 0x1u;	/* 410b05: mov eax, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 410b0a: sub eax, ecx */
	M32((DWORD)(0x4dd078u)) = m->eax;	/* 410b0c: mov dword ptr [0x4dd078], eax */
L_410b11:
	m->esp += 4 + 0; return;	/* 410b11: ret  */
L_410b12:
	m->ecx = M32((DWORD)(0x4dc798u));	/* 410b12: mov ecx, dword ptr [0x4dc798] */
	m->eax = (DWORD)(m->ecx + 0xffffffffu);	/* 410b18: lea eax, [ecx - 1] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410b1b: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_410b11;	/* 410b1e: ja 0x410b11 */
	switch (m->eax) { case 0: goto L_410b27; case 1: goto L_410b2c; case 2: goto L_410b31; case 3: goto L_410b36; default: abort(); }	/* 410b20: jmp dword ptr [eax*4 + 0x410b3c] */
L_410b27:
	native_call(m, 0x4101e0u); return;	/* 410b27: jmp 0x4101e0 */
L_410b2c:
	native_call(m, 0x410500u); return;	/* 410b2c: jmp 0x410500 */
L_410b31:
	native_call(m, 0x410810u); return;	/* 410b31: jmp 0x410810 */
L_410b36:
	native_call(m, 0x48b420u); return;	/* 410b36: jmp 0x48b420 */
	;	/* 410b3b: nop  */
	;	/* 410b4c: nop  */
	;	/* 410b4d: nop  */
	;	/* 410b4e: nop  */
	;	/* 410b4f: nop  */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 410b50: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 410b51: fld dword ptr [0x4b071c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 410b57: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410b5d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410b5f: test ah, 0x41 */
	if (!m->zf) goto L_410b6e;	/* 410b62: jne 0x410b6e */
	M32((DWORD)(0x4b071cu)) = 0x3f800000u;	/* 410b64: mov dword ptr [0x4b071c], 0x3f800000 */
L_410b6e:
	m->ecx = M32((DWORD)(0x4dc24cu));	/* 410b6e: mov ecx, dword ptr [0x4dc24c] */
	M32((DWORD)(m->esp + 0x0u)) = 0xc4098000u;	/* 410b74: mov dword ptr [esp], 0xc4098000 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 410b7c: fld dword ptr [0x4a9474] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410b82: cmp ecx, 3 */
	if (!m->zf) goto L_410b97;	/* 410b85: jne 0x410b97 */
	ST(0) = ST(0); FPOP();	/* 410b87: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9470u)));	/* 410b89: fld dword ptr [0x4a9470] */
	M32((DWORD)(m->esp + 0x0u)) = 0xc4ce4000u;	/* 410b8f: mov dword ptr [esp], 0xc4ce4000 */
L_410b97:
	m->eax = M32((DWORD)(0x4dc790u));	/* 410b97: mov eax, dword ptr [0x4dc790] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 410b9c: push esi */
	m->esi = 0x1u;	/* 410b9d: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410ba2: cmp eax, esi */
	if (!m->zf) goto L_410d36;	/* 410ba4: jne 0x410d36 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df870u)));	/* 410baa: fld dword ptr [0x4df870] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 410bb0: fsub dword ptr [0x4df024] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410bb6: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410bbc: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 410bc2: fadd dword ptr [0x4df024] */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 410bc8: fstp dword ptr [0x4df024] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df874u)));	/* 410bce: fld dword ptr [0x4df874] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 410bd4: fsub dword ptr [0x4df028] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410bda: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410be0: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 410be6: fadd dword ptr [0x4df028] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 410bec: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df878u)));	/* 410bf2: fld dword ptr [0x4df878] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 410bf8: fsub dword ptr [0x4df02c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410bfe: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410c04: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 410c0a: fadd dword ptr [0x4df02c] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 410c10: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d388u)));	/* 410c16: fld dword ptr [0x76d388] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x680378u));	/* 410c1c: fsub dword ptr [0x680378] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410c22: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410c28: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680378u));	/* 410c2e: fadd dword ptr [0x680378] */
	MF((DWORD)(0x680378u)) = (float)ST(0); FPOP();	/* 410c34: fstp dword ptr [0x680378] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d38cu)));	/* 410c3a: fld dword ptr [0x76d38c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x68037cu));	/* 410c40: fsub dword ptr [0x68037c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410c46: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410c4c: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x68037cu));	/* 410c52: fadd dword ptr [0x68037c] */
	MF((DWORD)(0x68037cu)) = (float)ST(0); FPOP();	/* 410c58: fstp dword ptr [0x68037c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d390u)));	/* 410c5e: fld dword ptr [0x76d390] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x680380u));	/* 410c64: fsub dword ptr [0x680380] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410c6a: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410c70: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680380u));	/* 410c76: fadd dword ptr [0x680380] */
	MF((DWORD)(0x680380u)) = (float)ST(0);	/* 410c7c: fst dword ptr [0x680380] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 410c82: fld dword ptr [0x4e1870] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 410c88: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410c8e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410c90: test ah, 0x41 */
	if (!m->zf) goto L_410cad;	/* 410c93: jne 0x410cad */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 410c95: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a946cu));	/* 410c9b: fmul dword ptr [0x4a946c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4e1870u));	/* 410ca1: fsubr dword ptr [0x4e1870] */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 410ca7: fstp dword ptr [0x4e1870] */
L_410cad:
	FCOM(ST(0), ST(1)); FPOP();	/* 410cad: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410caf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410cb1: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 410cb4: fstp st(0) */
	if (!m->zf) goto L_411101;	/* 410cb6: jne 0x411101 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410cbc: cmp ecx, 3 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 410cbf: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df028u)) = 0xc3480000u;	/* 410cc9: mov dword ptr [0x4df028], 0xc3480000 */
	M32((DWORD)(0x4df02cu)) = 0x43c80000u;	/* 410cd3: mov dword ptr [0x4df02c], 0x43c80000 */
	if (m->zf) goto L_410ce9;	/* 410cdd: je 0x410ce9 */
	M32((DWORD)(0x4df02cu)) = 0x44bb8000u;	/* 410cdf: mov dword ptr [0x4df02c], 0x44bb8000 */
L_410ce9:
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 410ce9: fild dword ptr [0x5b1998] */
	M32((DWORD)(0x90d1c4u)) = m->esi;	/* 410cef: mov dword ptr [0x90d1c4], esi */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 410cf5: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0xc3480000u;	/* 410cff: mov dword ptr [0x68037c], 0xc3480000 */
	M32((DWORD)(0x680380u)) = 0x0u;	/* 410d09: mov dword ptr [0x680380], 0 */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(0x4e045cu));	/* 410d13: fidiv dword ptr [0x4e045c] */
	M32((DWORD)(0x4dc790u)) = 0x2u;	/* 410d19: mov dword ptr [0x4dc790], 2 */
	M32((DWORD)(0x4dc868u)) = 0x0u;	/* 410d23: mov dword ptr [0x4dc868], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410d2d: pop esi */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 410d2e: fstp dword ptr [0x4e1870] */
	m->ecx = M32(m->esp); m->esp += 4;	/* 410d34: pop ecx */
	m->esp += 4 + 0; return;	/* 410d35: ret  */
L_410d36:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 410d36: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410d38: cmp eax, edx */
	ST(0) = ST(0); FPOP();	/* 410d3a: fstp st(0) */
	if (!m->zf) goto L_411101;	/* 410d3c: jne 0x411101 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4u)));	/* 410d42: fld dword ptr [esp + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 410d46: fadd dword ptr [0x4a9424] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x680380u)); FPOP();	/* 410d4c: fcomp dword ptr [0x680380] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df024u)));	/* 410d52: fld dword ptr [0x4df024] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db090u));	/* 410d58: fsub dword ptr [0x9db090] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410d5e: fnstsw ax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410d60: fmul dword ptr [0x4b071c] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410d66: test ah, 1 */
	if (m->zf) goto L_410e6b;	/* 410d69: je 0x410e6b */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410d6f: fmul dword ptr [0x4a93ec] */
	M32((DWORD)(0x4dc868u)) = m->esi;	/* 410d75: mov dword ptr [0x4dc868], esi */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 410d7b: fsubr dword ptr [0x4df024] */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 410d81: fstp dword ptr [0x4df024] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df028u)));	/* 410d87: fld dword ptr [0x4df028] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db094u));	/* 410d8d: fsub dword ptr [0x9db094] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410d93: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410d99: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 410d9f: fsubr dword ptr [0x4df028] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 410da5: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 410dab: fld dword ptr [0x4df02c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db098u));	/* 410db1: fsub dword ptr [0x9db098] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410db7: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410dbd: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 410dc3: fsubr dword ptr [0x4df02c] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 410dc9: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680378u)));	/* 410dcf: fld dword ptr [0x680378] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d3f8u));	/* 410dd5: fsub dword ptr [0x76d3f8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410ddb: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410de1: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x680378u));	/* 410de7: fsubr dword ptr [0x680378] */
	MF((DWORD)(0x680378u)) = (float)ST(0); FPOP();	/* 410ded: fstp dword ptr [0x680378] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68037cu)));	/* 410df3: fld dword ptr [0x68037c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d3fcu));	/* 410df9: fsub dword ptr [0x76d3fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410dff: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410e05: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x68037cu));	/* 410e0b: fsubr dword ptr [0x68037c] */
	MF((DWORD)(0x68037cu)) = (float)ST(0); FPOP();	/* 410e11: fstp dword ptr [0x68037c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680380u)));	/* 410e17: fld dword ptr [0x680380] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d400u));	/* 410e1d: fsub dword ptr [0x76d400] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410e23: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410e29: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x680380u));	/* 410e2f: fsubr dword ptr [0x680380] */
	MF((DWORD)(0x680380u)) = (float)ST(0); FPOP();	/* 410e35: fstp dword ptr [0x680380] */
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 410e3b: fild dword ptr [0x5b1998] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(0x4e045cu));	/* 410e41: fidiv dword ptr [0x4e045c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 410e47: fld dword ptr [0x4e1870] */
	FCOM(ST(0), ST(1)); FPOP();	/* 410e4d: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410e4f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410e51: test ah, 1 */
	if (m->zf) goto L_410f6a;	/* 410e54: je 0x410f6a */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 410e5a: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9468u));	/* 410e60: fmul dword ptr [0x4a9468] */
	goto L_410f5e;	/* 410e66: jmp 0x410f5e */
L_410e6b:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410e6b: fmul dword ptr [0x4a942c] */
	M32((DWORD)(0x4dc868u)) = m->esi;	/* 410e71: mov dword ptr [0x4dc868], esi */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 410e77: fsubr dword ptr [0x4df024] */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 410e7d: fstp dword ptr [0x4df024] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df028u)));	/* 410e83: fld dword ptr [0x4df028] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db094u));	/* 410e89: fsub dword ptr [0x9db094] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410e8f: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410e95: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 410e9b: fsubr dword ptr [0x4df028] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 410ea1: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 410ea7: fld dword ptr [0x4df02c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db098u));	/* 410ead: fsub dword ptr [0x9db098] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410eb3: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410eb9: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 410ebf: fsubr dword ptr [0x4df02c] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 410ec5: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680378u)));	/* 410ecb: fld dword ptr [0x680378] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d3f8u));	/* 410ed1: fsub dword ptr [0x76d3f8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410ed7: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410edd: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x680378u));	/* 410ee3: fsubr dword ptr [0x680378] */
	MF((DWORD)(0x680378u)) = (float)ST(0); FPOP();	/* 410ee9: fstp dword ptr [0x680378] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68037cu)));	/* 410eef: fld dword ptr [0x68037c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d3fcu));	/* 410ef5: fsub dword ptr [0x76d3fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410efb: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410f01: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x68037cu));	/* 410f07: fsubr dword ptr [0x68037c] */
	MF((DWORD)(0x68037cu)) = (float)ST(0); FPOP();	/* 410f0d: fstp dword ptr [0x68037c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680380u)));	/* 410f13: fld dword ptr [0x680380] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d400u));	/* 410f19: fsub dword ptr [0x76d400] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410f1f: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410f25: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x680380u));	/* 410f2b: fsubr dword ptr [0x680380] */
	MF((DWORD)(0x680380u)) = (float)ST(0); FPOP();	/* 410f31: fstp dword ptr [0x680380] */
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 410f37: fild dword ptr [0x5b1998] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(0x4e045cu));	/* 410f3d: fidiv dword ptr [0x4e045c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 410f43: fld dword ptr [0x4e1870] */
	FCOM(ST(0), ST(1)); FPOP();	/* 410f49: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410f4b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410f4d: test ah, 1 */
	if (m->zf) goto L_410f6a;	/* 410f50: je 0x410f6a */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 410f52: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 410f58: fmul dword ptr [0x4a9420] */
L_410f5e:
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e1870u));	/* 410f5e: fadd dword ptr [0x4e1870] */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 410f64: fstp dword ptr [0x4e1870] */
L_410f6a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4u)));	/* 410f6a: fld dword ptr [esp + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 410f6e: fadd dword ptr [0x4a9420] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x680380u)); FPOP();	/* 410f74: fcomp dword ptr [0x680380] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410f7a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410f7c: test ah, 1 */
	if (!m->zf) goto L_4110ff;	/* 410f7f: jne 0x4110ff */
	m->eax = M32((DWORD)(0x76d3f8u));	/* 410f85: mov eax, dword ptr [0x76d3f8] */
	M32((DWORD)(0x4dc790u)) = 0x2u;	/* 410f8a: mov dword ptr [0x4dc790], 2 */
	M32((DWORD)(0x680378u)) = m->eax;	/* 410f94: mov dword ptr [0x680378], eax */
	m->eax = M32((DWORD)(0x76d3fcu));	/* 410f99: mov eax, dword ptr [0x76d3fc] */
	M32((DWORD)(0x68037cu)) = m->eax;	/* 410f9e: mov dword ptr [0x68037c], eax */
	m->eax = M32((DWORD)(0x76d400u));	/* 410fa3: mov eax, dword ptr [0x76d400] */
	M32((DWORD)(0x680380u)) = m->eax;	/* 410fa8: mov dword ptr [0x680380], eax */
	m->eax = M32((DWORD)(0x9db090u));	/* 410fad: mov eax, dword ptr [0x9db090] */
	M32((DWORD)(0x4df024u)) = m->eax;	/* 410fb2: mov dword ptr [0x4df024], eax */
	m->eax = M32((DWORD)(0x9db094u));	/* 410fb7: mov eax, dword ptr [0x9db094] */
	M32((DWORD)(0x4df028u)) = m->eax;	/* 410fbc: mov dword ptr [0x4df028], eax */
	m->eax = M32((DWORD)(0x9db098u));	/* 410fc1: mov eax, dword ptr [0x9db098] */
	M32((DWORD)(0x4df02cu)) = m->eax;	/* 410fc6: mov dword ptr [0x4df02c], eax */
	m->eax = m->ecx;	/* 410fcb: mov eax, ecx */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410fcd: dec eax */
	M32((DWORD)(0x4dc798u)) = m->edx;	/* 410fce: mov dword ptr [0x4dc798], edx */
	if (m->zf) goto L_4110b8;	/* 410fd4: je 0x4110b8 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410fda: dec eax */
	if (m->zf) goto L_411018;	/* 410fdb: je 0x411018 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410fdd: dec eax */
	if (!m->zf) goto L_4110e4;	/* 410fde: jne 0x4110e4 */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 410fe4: fstp dword ptr [0x4e1870] */
	m->eax = 0x320u;	/* 410fea: mov eax, 0x320 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 410fef: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 410ff9: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 410ffe: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 411003: mov dword ptr [0x67ef20], eax */
	M32((DWORD)(0x4dc24cu)) = m->edx;	/* 411008: mov dword ptr [0x4dc24c], edx */
	m->esp -= 4; M32(m->esp) = 0x411013u; native_call(m, 0x433360u);	/* 41100e: call 0x433360 */
	goto L_4110e6;	/* 411013: jmp 0x4110e6 */
L_411018:
	m->ecx = M32((DWORD)(0x4db840u));	/* 411018: mov ecx, dword ptr [0x4db840] */
	m->eax = 0x190u;	/* 41101e: mov eax, 0x190 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 411023: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 411028: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 41102d: mov dword ptr [0x67ef20], eax */
	m->eax = M32((DWORD)(0x4db844u));	/* 411032: mov eax, dword ptr [0x4db844] */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 411037: fstp dword ptr [0x4e1870] */
	M32((DWORD)(0x4df024u)) = m->ecx;	/* 41103d: mov dword ptr [0x4df024], ecx */
	m->ecx = M32((DWORD)(0x4db848u));	/* 411043: mov ecx, dword ptr [0x4db848] */
	M32((DWORD)(0x4df028u)) = m->eax;	/* 411049: mov dword ptr [0x4df028], eax */
	m->eax = M32((DWORD)(0x4dbab8u));	/* 41104e: mov eax, dword ptr [0x4dbab8] */
	M32((DWORD)(0x4df02cu)) = m->ecx;	/* 411053: mov dword ptr [0x4df02c], ecx */
	m->ecx = M32((DWORD)(0x4dbabcu));	/* 411059: mov ecx, dword ptr [0x4dbabc] */
	M32((DWORD)(0x680378u)) = m->eax;	/* 41105f: mov dword ptr [0x680378], eax */
	m->eax = M32((DWORD)(0x4dbac0u));	/* 411064: mov eax, dword ptr [0x4dbac0] */
	M32((DWORD)(0x68037cu)) = m->ecx;	/* 411069: mov dword ptr [0x68037c], ecx */
	M32((DWORD)(0x680380u)) = m->eax;	/* 41106f: mov dword ptr [0x680380], eax */
	M32((DWORD)(0x9db090u)) = 0x0u;	/* 411074: mov dword ptr [0x9db090], 0 */
	M32((DWORD)(0x9db094u)) = 0x0u;	/* 41107e: mov dword ptr [0x9db094], 0 */
	M32((DWORD)(0x9db098u)) = 0xc4c1c000u;	/* 411088: mov dword ptr [0x9db098], 0xc4c1c000 */
	M32((DWORD)(0x76d3f8u)) = 0x0u;	/* 411092: mov dword ptr [0x76d3f8], 0 */
	M32((DWORD)(0x76d3fcu)) = 0x0u;	/* 41109c: mov dword ptr [0x76d3fc], 0 */
	M32((DWORD)(0x76d400u)) = 0xc4ce4000u;	/* 4110a6: mov dword ptr [0x76d400], 0xc4ce4000 */
	M32((DWORD)(0x4dc24cu)) = m->edx;	/* 4110b0: mov dword ptr [0x4dc24c], edx */
	goto L_4110e6;	/* 4110b6: jmp 0x4110e6 */
L_4110b8:
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 4110b8: fstp dword ptr [0x4e1870] */
	m->eax = 0x12cu;	/* 4110be: mov eax, 0x12c */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4110c3: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 4110cd: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 4110d2: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 4110d7: mov dword ptr [0x67ef20], eax */
	M32((DWORD)(0x4dc24cu)) = m->edx;	/* 4110dc: mov dword ptr [0x4dc24c], edx */
	goto L_4110e6;	/* 4110e2: jmp 0x4110e6 */
L_4110e4:
	ST(0) = ST(0); FPOP();	/* 4110e4: fstp st(0) */
L_4110e6:
	{ DWORD a_ = M32((DWORD)(0x76d410u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4110e6: cmp dword ptr [0x76d410], esi */
	if (!m->zf) goto L_411101;	/* 4110ec: jne 0x411101 */
	{ DWORD a_ = M32((DWORD)(0x9da49cu)), b_ = 0x67u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4110ee: cmp dword ptr [0x9da49c], 0x67 */
	if (!m->zf) goto L_411101;	/* 4110f5: jne 0x411101 */
	m->esp -= 4; M32(m->esp) = 0x4110fcu; native_call(m, 0x40d840u);	/* 4110f7: call 0x40d840 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4110fc: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4110fd: pop ecx */
	m->esp += 4 + 0; return;	/* 4110fe: ret  */
L_4110ff:
	ST(0) = ST(0); FPOP();	/* 4110ff: fstp st(0) */
L_411101:
	m->esi = M32(m->esp); m->esp += 4;	/* 411101: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 411102: pop ecx */
	m->esp += 4 + 0; return;	/* 411103: ret  */
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
