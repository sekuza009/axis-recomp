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

static void lift_474fd0(X86 *m);
static void lift_474b50(X86 *m);

/* actor_setPartColor (0x474b50), lifted by tools/lift.py */
static void lift_474b50(X86 *m)
{
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 474b50: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 474b54: fmul dword ptr [0x4a9418] */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474b5a: sub esp, 0x100 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 474b60: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 474b61: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474b62: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 474b63: push edi */
	m->edi = m->ecx;	/* 474b64: mov edi, ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474b66: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 474b67: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x474b6fu; { long double r_ = native_call_fp(m, 0x46c100u); FPUSH(r_); }	/* 474b6a: call 0x46c100 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 474b6f: fmul dword ptr [0x4a93ec] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474b75: add esp, 4 */
	MF((DWORD)(m->esp + 0x11cu)) = (float)ST(0);	/* 474b78: fst dword ptr [esp + 0x11c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a945cu)); FPOP();	/* 474b7f: fcomp dword ptr [0x4a945c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474b85: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474b87: test ah, 0x41 */
	if (!m->zf) goto L_474ba0;	/* 474b8a: jne 0x474ba0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x11cu)));	/* 474b8c: fld dword ptr [esp + 0x11c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9460u));	/* 474b93: fsub dword ptr [0x4a9460] */
	MF((DWORD)(m->esp + 0x11cu)) = (float)ST(0); FPOP();	/* 474b99: fstp dword ptr [esp + 0x11c] */
L_474ba0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x11cu)));	/* 474ba0: fld dword ptr [esp + 0x11c] */
	m->esi = M32((DWORD)(m->esp + 0x114u));	/* 474ba7: mov esi, dword ptr [esp + 0x114] */
	m->ebp = M32((DWORD)(m->esp + 0x118u));	/* 474bae: mov ebp, dword ptr [esp + 0x118] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa418u));	/* 474bb5: fsub dword ptr [0x4aa418] */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 474bbb: lea eax, [esi + esi*2] */
	m->ecx = (DWORD)(m->esi + m->ebp*1 + 0x0u);	/* 474bbe: lea ecx, [esi + ebp] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 474bc1: shl eax, 0xb */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa414u));	/* 474bc4: fmul dword ptr [0x4aa414] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474bca: sub eax, esi */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 474bcc: fsub dword ptr [0x4aa264] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 474bd2: lea eax, [eax + eax*2] */
	m->ebx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 474bd5: lea ebx, [ecx + eax*8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 474bd8: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x120u)));	/* 474bdd: fld dword ptr [esp + 0x120] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u)); FPOP();	/* 474be4: fcomp dword ptr [0x4a9474] */
	M8((DWORD)(m->edi + m->ebx*2 + 0x15a950cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 474bea: mov byte ptr [edi + ebx*2 + 0x15a950c], al */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474bf1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474bf3: test ah, 1 */
	if (m->zf) goto L_474c05;	/* 474bf6: je 0x474c05 */
	M32((DWORD)(m->esp + 0x120u)) = 0xbf800000u;	/* 474bf8: mov dword ptr [esp + 0x120], 0xbf800000 */
	goto L_474c24;	/* 474c03: jmp 0x474c24 */
L_474c05:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x120u)));	/* 474c05: fld dword ptr [esp + 0x120] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 474c0c: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474c12: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474c14: test ah, 1 */
	if (!m->zf) goto L_474c24;	/* 474c17: jne 0x474c24 */
	M32((DWORD)(m->esp + 0x120u)) = 0x3f7fbe77u;	/* 474c19: mov dword ptr [esp + 0x120], 0x3f7fbe77 */
L_474c24:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x120u)));	/* 474c24: fld dword ptr [esp + 0x120] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 474c2b: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 474c31: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x124u)));	/* 474c36: fld dword ptr [esp + 0x124] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u)); FPOP();	/* 474c3d: fcomp dword ptr [0x4a9474] */
	M8((DWORD)(m->edi + m->ebx*2 + 0x15a9516u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 474c43: mov byte ptr [edi + ebx*2 + 0x15a9516], al */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474c4a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474c4c: test ah, 1 */
	if (m->zf) goto L_474c5e;	/* 474c4f: je 0x474c5e */
	M32((DWORD)(m->esp + 0x124u)) = 0xbf800000u;	/* 474c51: mov dword ptr [esp + 0x124], 0xbf800000 */
	goto L_474c7d;	/* 474c5c: jmp 0x474c7d */
L_474c5e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x124u)));	/* 474c5e: fld dword ptr [esp + 0x124] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 474c65: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474c6b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474c6d: test ah, 1 */
	if (!m->zf) goto L_474c7d;	/* 474c70: jne 0x474c7d */
	M32((DWORD)(m->esp + 0x124u)) = 0x3f7fbe77u;	/* 474c72: mov dword ptr [esp + 0x124], 0x3f7fbe77 */
L_474c7d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x124u)));	/* 474c7d: fld dword ptr [esp + 0x124] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 474c84: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 474c8a: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x128u)));	/* 474c8f: fld dword ptr [esp + 0x128] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 474c96: fmul dword ptr [0x4a9418] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474c9c: push ecx */
	M8((DWORD)(m->edi + m->ebx*2 + 0x15a9520u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 474c9d: mov byte ptr [edi + ebx*2 + 0x15a9520], al */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 474ca4: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x474cacu; { long double r_ = native_call_fp(m, 0x46c100u); FPUSH(r_); }	/* 474ca7: call 0x46c100 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 474cac: fmul dword ptr [0x4a93ec] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474cb2: add esp, 4 */
	MF((DWORD)(m->esp + 0x128u)) = (float)ST(0);	/* 474cb5: fst dword ptr [esp + 0x128] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a945cu)); FPOP();	/* 474cbc: fcomp dword ptr [0x4a945c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474cc2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474cc4: test ah, 0x41 */
	if (!m->zf) goto L_474cdd;	/* 474cc7: jne 0x474cdd */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x128u)));	/* 474cc9: fld dword ptr [esp + 0x128] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a9460u));	/* 474cd0: fsub dword ptr [0x4a9460] */
	MF((DWORD)(m->esp + 0x128u)) = (float)ST(0); FPOP();	/* 474cd6: fstp dword ptr [esp + 0x128] */
L_474cdd:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x128u)));	/* 474cdd: fld dword ptr [esp + 0x128] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa418u));	/* 474ce4: fsub dword ptr [0x4aa418] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa414u));	/* 474cea: fmul dword ptr [0x4aa414] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 474cf0: fsub dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 474cf6: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x12cu)));	/* 474cfb: fld dword ptr [esp + 0x12c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u)); FPOP();	/* 474d02: fcomp dword ptr [0x4a9474] */
	M8((DWORD)(m->edi + m->ebx*2 + 0x15a950du)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 474d08: mov byte ptr [edi + ebx*2 + 0x15a950d], al */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474d0f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474d11: test ah, 1 */
	if (m->zf) goto L_474d23;	/* 474d14: je 0x474d23 */
	M32((DWORD)(m->esp + 0x12cu)) = 0xbf800000u;	/* 474d16: mov dword ptr [esp + 0x12c], 0xbf800000 */
	goto L_474d42;	/* 474d21: jmp 0x474d42 */
L_474d23:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x12cu)));	/* 474d23: fld dword ptr [esp + 0x12c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 474d2a: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474d30: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474d32: test ah, 1 */
	if (!m->zf) goto L_474d42;	/* 474d35: jne 0x474d42 */
	M32((DWORD)(m->esp + 0x12cu)) = 0x3f7fbe77u;	/* 474d37: mov dword ptr [esp + 0x12c], 0x3f7fbe77 */
L_474d42:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x12cu)));	/* 474d42: fld dword ptr [esp + 0x12c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 474d49: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 474d4f: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x130u)));	/* 474d54: fld dword ptr [esp + 0x130] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u)); FPOP();	/* 474d5b: fcomp dword ptr [0x4a9474] */
	M8((DWORD)(m->edi + m->ebx*2 + 0x15a9517u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 474d61: mov byte ptr [edi + ebx*2 + 0x15a9517], al */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474d68: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474d6a: test ah, 1 */
	if (m->zf) goto L_474d7c;	/* 474d6d: je 0x474d7c */
	M32((DWORD)(m->esp + 0x130u)) = 0xbf800000u;	/* 474d6f: mov dword ptr [esp + 0x130], 0xbf800000 */
	goto L_474d9b;	/* 474d7a: jmp 0x474d9b */
L_474d7c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x130u)));	/* 474d7c: fld dword ptr [esp + 0x130] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 474d83: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 474d89: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 474d8b: test ah, 1 */
	if (!m->zf) goto L_474d9b;	/* 474d8e: jne 0x474d9b */
	M32((DWORD)(m->esp + 0x130u)) = 0x3f7fbe77u;	/* 474d90: mov dword ptr [esp + 0x130], 0x3f7fbe77 */
L_474d9b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x130u)));	/* 474d9b: fld dword ptr [esp + 0x130] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 474da2: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 474da8: call 0x49ec14 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 474dad: push esi */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 474dae: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x4c77f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 474db2: push 0x4c77f8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474db7: push edx */
	M8((DWORD)(m->edi + m->ebx*2 + 0x15a9521u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 474db8: mov byte ptr [edi + ebx*2 + 0x15a9521], al */
	m->esp -= 4; M32(m->esp) = 0x474dc4u; native_call(m, 0x49e9ddu);	/* 474dbf: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474dc4: add esp, 0xc */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 474dc7: cmp ebp, 4 */
	if (!m->cf && !m->zf) goto L_474fa0;	/* 474dca: ja 0x474fa0 */
	switch (m->ebp) { case 0: goto L_474dd7; case 1: goto L_474e35; case 2: goto L_474e93; case 3: goto L_474ef1; case 4: goto L_474f4f; default: abort(); }	/* 474dd0: jmp dword ptr [ebp*4 + 0x474fb0] */
L_474dd7:
	m->eax = M32((DWORD)(m->esp + 0x130u));	/* 474dd7: mov eax, dword ptr [esp + 0x130] */
	m->ecx = M32((DWORD)(m->esp + 0x12cu));	/* 474dde: mov ecx, dword ptr [esp + 0x12c] */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474de5: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474dec: push eax */
	m->eax = M32((DWORD)(m->esp + 0x128u));	/* 474ded: mov eax, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474df4: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x128u));	/* 474df5: mov ecx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474dfc: push edx */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474dfd: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474e04: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474e05: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474e06: push edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 474e07: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 474e0b: push 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474e0d: push eax */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 474e0e: lea eax, [esi + esi*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 474e11: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474e14: sub eax, esi */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 474e16: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 474e19: lea edx, [esi + ecx*8] */
	m->ecx = (DWORD)(m->edi + m->edx*2 + 0x1561ea0u);	/* 474e1c: lea ecx, [edi + edx*2 + 0x1561ea0] */
	m->esp -= 4; M32(m->esp) = 0x474e28u; native_call(m, 0x467580u);	/* 474e23: call 0x467580 */
	m->edi = M32(m->esp); m->esp += 4;	/* 474e28: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 474e29: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474e2a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474e2b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474e2c: add esp, 0x100 */
	m->esp += 4 + 32; return;	/* 474e32: ret 0x20 */
L_474e35:
	m->eax = M32((DWORD)(m->esp + 0x130u));	/* 474e35: mov eax, dword ptr [esp + 0x130] */
	m->ecx = M32((DWORD)(m->esp + 0x12cu));	/* 474e3c: mov ecx, dword ptr [esp + 0x12c] */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474e43: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474e4a: push eax */
	m->eax = M32((DWORD)(m->esp + 0x128u));	/* 474e4b: mov eax, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474e52: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x128u));	/* 474e53: mov ecx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474e5a: push edx */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474e5b: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474e62: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474e63: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474e64: push edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 474e65: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 474e69: push 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474e6b: push eax */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 474e6c: lea eax, [esi + esi*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 474e6f: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474e72: sub eax, esi */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 474e74: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 474e77: lea edx, [esi + ecx*8] */
	m->ecx = (DWORD)(m->edi + m->edx*2 + 0x1569decu);	/* 474e7a: lea ecx, [edi + edx*2 + 0x1569dec] */
	m->esp -= 4; M32(m->esp) = 0x474e86u; native_call(m, 0x467580u);	/* 474e81: call 0x467580 */
	m->edi = M32(m->esp); m->esp += 4;	/* 474e86: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 474e87: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474e88: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474e89: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474e8a: add esp, 0x100 */
	m->esp += 4 + 32; return;	/* 474e90: ret 0x20 */
L_474e93:
	m->eax = M32((DWORD)(m->esp + 0x130u));	/* 474e93: mov eax, dword ptr [esp + 0x130] */
	m->ecx = M32((DWORD)(m->esp + 0x12cu));	/* 474e9a: mov ecx, dword ptr [esp + 0x12c] */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474ea1: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474ea8: push eax */
	m->eax = M32((DWORD)(m->esp + 0x128u));	/* 474ea9: mov eax, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474eb0: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x128u));	/* 474eb1: mov ecx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474eb8: push edx */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474eb9: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474ec0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474ec1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474ec2: push edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 474ec3: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 474ec7: push 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474ec9: push eax */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 474eca: lea eax, [esi + esi*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 474ecd: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474ed0: sub eax, esi */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 474ed2: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 474ed5: lea edx, [esi + ecx*8] */
	m->ecx = (DWORD)(m->edi + m->edx*2 + 0x1571d38u);	/* 474ed8: lea ecx, [edi + edx*2 + 0x1571d38] */
	m->esp -= 4; M32(m->esp) = 0x474ee4u; native_call(m, 0x467580u);	/* 474edf: call 0x467580 */
	m->edi = M32(m->esp); m->esp += 4;	/* 474ee4: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 474ee5: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474ee6: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474ee7: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474ee8: add esp, 0x100 */
	m->esp += 4 + 32; return;	/* 474eee: ret 0x20 */
L_474ef1:
	m->eax = M32((DWORD)(m->esp + 0x130u));	/* 474ef1: mov eax, dword ptr [esp + 0x130] */
	m->ecx = M32((DWORD)(m->esp + 0x12cu));	/* 474ef8: mov ecx, dword ptr [esp + 0x12c] */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474eff: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474f06: push eax */
	m->eax = M32((DWORD)(m->esp + 0x128u));	/* 474f07: mov eax, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474f0e: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x128u));	/* 474f0f: mov ecx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474f16: push edx */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474f17: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474f1e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474f1f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474f20: push edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 474f21: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 474f25: push 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474f27: push eax */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 474f28: lea eax, [esi + esi*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 474f2b: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474f2e: sub eax, esi */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 474f30: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 474f33: lea edx, [esi + ecx*8] */
	m->ecx = (DWORD)(m->edi + m->edx*2 + 0x1581984u);	/* 474f36: lea ecx, [edi + edx*2 + 0x1581984] */
	m->esp -= 4; M32(m->esp) = 0x474f42u; native_call(m, 0x467580u);	/* 474f3d: call 0x467580 */
	m->edi = M32(m->esp); m->esp += 4;	/* 474f42: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 474f43: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474f44: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474f45: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474f46: add esp, 0x100 */
	m->esp += 4 + 32; return;	/* 474f4c: ret 0x20 */
L_474f4f:
	m->eax = M32((DWORD)(m->esp + 0x130u));	/* 474f4f: mov eax, dword ptr [esp + 0x130] */
	m->ecx = M32((DWORD)(m->esp + 0x12cu));	/* 474f56: mov ecx, dword ptr [esp + 0x12c] */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474f5d: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474f64: push eax */
	m->eax = M32((DWORD)(m->esp + 0x128u));	/* 474f65: mov eax, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474f6c: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x128u));	/* 474f6d: mov ecx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474f74: push edx */
	m->edx = M32((DWORD)(m->esp + 0x128u));	/* 474f75: mov edx, dword ptr [esp + 0x128] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474f7c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474f7d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 474f7e: push edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 474f7f: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 474f83: push 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 474f85: push eax */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 474f86: lea eax, [esi + esi*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 474f89: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 474f8c: sub eax, esi */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 474f8e: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 474f91: lea edx, [esi + ecx*8] */
	m->ecx = (DWORD)(m->edi + m->edx*2 + 0x15915d0u);	/* 474f94: lea ecx, [edi + edx*2 + 0x15915d0] */
	m->esp -= 4; M32(m->esp) = 0x474fa0u; native_call(m, 0x467580u);	/* 474f9b: call 0x467580 */
L_474fa0:
	m->edi = M32(m->esp); m->esp += 4;	/* 474fa0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 474fa1: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 474fa2: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 474fa3: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 474fa4: add esp, 0x100 */
	m->esp += 4 + 32; return;	/* 474faa: ret 0x20 */
}

/* actor_applyRemoteColours (0x474fd0), lifted by tools/lift.py */
static void lift_474fd0(X86 *m)
{
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x20u)));	/* 474fd0: movsx eax, byte ptr [esp + 0x20] */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x1cu)));	/* 474fd5: movsx edx, byte ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 474fda: mov dword ptr [esp + 0x20], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474fde: push ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 474fdf: fild dword ptr [esp + 0x24] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x1cu)));	/* 474fe3: movsx eax, byte ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa420u));	/* 474fe8: fmul dword ptr [0x4aa420] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 474fee: mov dword ptr [esp + 0x24], edx */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x18u)));	/* 474ff2: movsx edx, byte ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 474ff7: fstp dword ptr [esp] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 474ffa: fild dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 474ffe: push ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 474fff: mov dword ptr [esp + 0x28], eax */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x18u)));	/* 475003: movsx eax, byte ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa420u));	/* 475008: fmul dword ptr [0x4aa420] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47500e: fstp dword ptr [esp] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 475011: fild dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475015: push ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 475016: mov dword ptr [esp + 0x2c], edx */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x18u)));	/* 47501a: movsx edx, byte ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa41cu));	/* 47501f: fmul dword ptr [0x4aa41c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 475025: fstp dword ptr [esp] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x2cu)));	/* 475028: fild dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47502c: push ecx */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 47502d: mov dword ptr [esp + 0x30], eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 475031: mov eax, dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa420u));	/* 475035: fmul dword ptr [0x4aa420] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47503b: fstp dword ptr [esp] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x30u)));	/* 47503e: fild dword ptr [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475042: push ecx */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 475043: mov dword ptr [esp + 0x34], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 475047: mov edx, dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa420u));	/* 47504b: fmul dword ptr [0x4aa420] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 475051: fstp dword ptr [esp] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x34u)));	/* 475054: fild dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 475058: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa41cu));	/* 475059: fmul dword ptr [0x4aa41c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47505f: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 475062: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 475063: push edx */
	m->esp -= 4; M32(m->esp) = 0x475069u; lift_474b50(m);	/* 475064: call 0x474b50 */
	m->esp += 4 + 32; return;	/* 475069: ret 0x20 */
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
