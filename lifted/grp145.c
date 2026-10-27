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

static void lift_490440(X86 *m);
static void lift_476410(X86 *m);

/* match_476410 (0x476410), lifted by tools/lift.py */
static void lift_476410(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 476410: sub esp, 0x98 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 476416: push ebp */
	m->ebp = m->ecx;	/* 476417: mov ebp, ecx */
	m->ecx = M32((DWORD)(m->esp + 0xa0u));	/* 476419: mov ecx, dword ptr [esp + 0xa0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 476420: push esi */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 476421: lea eax, [ecx + ecx*2] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 476424: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 476427: lea eax, [eax + eax*4] */
	m->edx = M32((DWORD)(m->ebp + m->eax*4 + 0x20a9a34u));	/* 47642a: mov edx, dword ptr [ebp + eax*4 + 0x20a9a34] */
	m->esi = (DWORD)(m->ebp + m->eax*4 + 0x20a99c0u);	/* 476431: lea esi, [ebp + eax*4 + 0x20a99c0] */
	M32((DWORD)(m->esp + 0x8u)) = m->edx;	/* 476438: mov dword ptr [esp + 8], edx */
	m->eax = m->edx;	/* 47643c: mov eax, edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 47643e: fld dword ptr [esp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x70u)); FPOP();	/* 476442: fcomp dword ptr [esi + 0x70] */
	M32((DWORD)(m->esi + 0x6cu)) = m->eax;	/* 476445: mov dword ptr [esi + 0x6c], eax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 476448: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47644a: test ah, 0x41 */
	if (!m->zf) goto L_476462;	/* 47644d: jne 0x476462 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47644f: push ecx */
	m->ecx = m->ebp;	/* 476450: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x476457u; native_call(m, 0x4799f0u);	/* 476452: call 0x4799f0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 476457: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 476458: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 476459: add esp, 0x98 */
	m->esp += 4 + 8; return;	/* 47645f: ret 8 */
L_476462:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 476462: fld dword ptr [esi + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 476465: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47646b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47646d: test ah, 0x41 */
	if (!m->zf) goto L_47647f;	/* 476470: jne 0x47647f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 476472: fld dword ptr [esp + 8] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x70u));	/* 476476: fdiv dword ptr [esi + 0x70] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 476479: fstp dword ptr [esp + 8] */
	goto L_476487;	/* 47647d: jmp 0x476487 */
L_47647f:
	M32((DWORD)(m->esp + 0x8u)) = 0x0u;	/* 47647f: mov dword ptr [esp + 8], 0 */
L_476487:
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 476487: mov ecx, dword ptr [esi + 8] */
	m->eax = 0x66666667u;	/* 47648a: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 47648f: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 476491: sar edx, 1 */
	m->eax = m->edx;	/* 476493: mov eax, edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 476495: push ebx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 476496: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 476499: add edx, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47649b: push edi */
	{ DWORD a_ = m->edx, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47649c: cmp edx, 0xa */
	if (!m->cf && !m->zf) goto L_476820;	/* 47649f: ja 0x476820 */
	switch (m->edx) { case 0: goto L_4764ac; case 1: goto L_4764d5; case 2: goto L_476820; case 3: goto L_476820; case 4: goto L_476820; case 5: goto L_476785; case 6: goto L_4767a7; case 7: goto L_4767cc; case 8: goto L_476820; case 9: goto L_476820; case 10: goto L_476820; default: abort(); }	/* 4764a5: jmp dword ptr [edx*4 + 0x47683c] */
L_4764ac:
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4764ac: sub ecx, 2 */
	if (m->zf) goto L_4767f1;	/* 4764af: je 0x4767f1 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4764b5: dec ecx */
	if (!m->zf) goto L_476820;	/* 4764b6: jne 0x476820 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4764bc: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4764c2: fsub dword ptr [esp + 0x10] */
	{ long double t = ST(0); FPUSH(t); }	/* 4764c6: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4764c8: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa430u));	/* 4764ca: fmul dword ptr [0x4aa430] */
	goto L_47681b;	/* 4764d0: jmp 0x47681b */
L_4764d5:
	{ DWORD a_ = m->ecx, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4764d5: cmp ecx, 9 */
	if (!m->zf) goto L_476820;	/* 4764d8: jne 0x476820 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 4764de: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x1cu));	/* 4764e5: fmul dword ptr [esi + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 4764e8: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 4764ef: fmul dword ptr [esi + 0x20] */
	m->edi = (DWORD)(m->esi + 0x10u);	/* 4764f2: lea edi, [esi + 0x10] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4764f5: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 4764f9: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 476500: fmul dword ptr [esi + 0x24] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 476503: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 476507: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 476509: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47650d: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 476511: fadd dword ptr [edi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 476514: mov ecx, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 476518: mov dword ptr [esp + 0x14], ecx */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 47651c: lea ecx, [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 476520: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 476524: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 476528: fadd dword ptr [edi + 8] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 47652b: mov edx, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47652f: push ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 476530: mov dword ptr [esp + 0x1c], edx */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 476534: lea edx, [esp + 0x18] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 476538: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb4u)));	/* 47653c: fld dword ptr [esp + 0xb4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9554u));	/* 476543: fmul dword ptr [0x4a9554] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 476549: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47654d: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47654e: push edi */
	m->ecx = m->ebp;	/* 47654f: mov ecx, ebp */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 476551: fsubr dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 476555: mov dword ptr [esp + 0x28], eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 476559: fstp dword ptr [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x476562u; native_call(m, 0x471740u);	/* 47655d: call 0x471740 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 476562: xor ebx, ebx */
	m->edx = m->edi;	/* 476564: mov edx, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 476566: test eax, eax */
	if (m->zf) goto L_4765df;	/* 476568: je 0x4765df */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 47656a: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 47656e: mov ecx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 476572: mov dword ptr [edx], eax */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 476574: mov dword ptr [esp + 0x34], eax */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 476578: mov eax, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x2u;	/* 47657c: mov dword ptr [esp + 0x2c], 2 */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 476584: mov dword ptr [edx + 4], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 476587: mov ecx, dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 47658b: mov dword ptr [esp + 0x3c], ecx */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 47658f: mov dword ptr [esp + 0x38], eax */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 476593: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->esi + 0x6cu));	/* 476596: mov edx, dword ptr [esi + 0x6c] */
	M32((DWORD)(m->esi + 0x70u)) = m->edx;	/* 476599: mov dword ptr [esi + 0x70], edx */
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 47659c: mov ecx, dword ptr [0xa0e7e8] */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 4765a2: mov edx, dword ptr [0xa0e7ec] */
	m->eax = M32((DWORD)(0xa0e7f0u));	/* 4765a8: mov eax, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->esp + 0x40u)) = m->ecx;	/* 4765ad: mov dword ptr [esp + 0x40], ecx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 4765b1: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4765b5: push ecx */
	m->ecx = m->ebp;	/* 4765b6: mov ecx, ebp */
	M32((DWORD)(m->esp + 0x34u)) = m->ebx;	/* 4765b8: mov dword ptr [esp + 0x34], ebx */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 4765bc: mov dword ptr [esp + 0x48], edx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 4765c0: mov dword ptr [esp + 0x4c], eax */
	M32((DWORD)(m->esp + 0x50u)) = m->ebx;	/* 4765c4: mov dword ptr [esp + 0x50], ebx */
	M32((DWORD)(m->esp + 0x54u)) = m->ebx;	/* 4765c8: mov dword ptr [esp + 0x54], ebx */
	M32((DWORD)(m->esp + 0x58u)) = m->ebx;	/* 4765cc: mov dword ptr [esp + 0x58], ebx */
	M32((DWORD)(m->esp + 0x5cu)) = m->ebx;	/* 4765d0: mov dword ptr [esp + 0x5c], ebx */
	M32((DWORD)(m->esp + 0x60u)) = m->ebx;	/* 4765d4: mov dword ptr [esp + 0x60], ebx */
	m->esp -= 4; M32(m->esp) = 0x4765ddu; native_call(m, 0x479950u);	/* 4765d8: call 0x479950 */
	goto L_4765f3;	/* 4765dd: jmp 0x4765f3 */
L_4765df:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4765df: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4765e3: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 4765e7: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4765e9: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 4765ed: mov dword ptr [edx + 4], ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 4765f0: mov dword ptr [edx + 8], eax */
L_4765f3:
	m->esp -= 4; M32(m->esp) = 0x4765f9u; native_call(m, M32(0x4a9204u));	/* 4765f3: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x4765ffu; native_call(m, M32(0x4a9218u));	/* 4765f9: call dword ptr [0x4a9218] */
	m->ecx = M32((DWORD)(m->esi + 0x18u));	/* 4765ff: mov ecx, dword ptr [esi + 0x18] */
	m->edx = M32((DWORD)(m->esi + 0x14u));	/* 476602: mov edx, dword ptr [esi + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 476605: mov eax, dword ptr [edi] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476607: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476608: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476609: push eax */
	m->esp -= 4; M32(m->esp) = 0x476610u; native_call(m, M32(0x4a9214u));	/* 47660a: call dword ptr [0x4a9214] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 476610: fld dword ptr [esi + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 476613: fmul dword ptr [0x4a94c8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 476619: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47661a: push 0x3f800000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47661f: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476620: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 476621: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47662au; native_call(m, M32(0x4a91f8u));	/* 476624: call dword ptr [0x4a91f8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 47662a: fld dword ptr [esi + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 47662d: fmul dword ptr [0x4a94c8] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 476633: push 0x3f800000 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 476638: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 476639: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47663a: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47663b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x476644u; native_call(m, M32(0x4a91f8u));	/* 47663e: call dword ptr [0x4a91f8] */
	m->ecx = (DWORD)(m->esi + 0x2cu);	/* 476644: lea ecx, [esi + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476647: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 476648: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x476653u; native_call(m, M32(0x4a9270u));	/* 47664d: call dword ptr [0x4a9270] */
	m->esp -= 4; M32(m->esp) = 0x476659u; native_call(m, M32(0x4a9258u));	/* 476653: call dword ptr [0x4a9258] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x84u)));	/* 476659: fld dword ptr [esi + 0x84] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0xb0u));	/* 47665f: fsub dword ptr [esp + 0xb0] */
	MF((DWORD)(m->esi + 0x84u)) = (float)ST(0);	/* 476666: fst dword ptr [esi + 0x84] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47666c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 476672: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 476674: test ah, 0x41 */
	if (m->zf) goto L_476820;	/* 476677: je 0x476820 */
	m->edx = M32((DWORD)(0xa1efb8u));	/* 47667d: mov edx, dword ptr [0xa1efb8] */
	m->ecx = 0xau;	/* 476683: mov ecx, 0xa */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 476688: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 47668e: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 476695: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 476697: div ecx */
	{ DWORD a_ = M32((DWORD)(0xa1efb8u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0xa1efb8u)) = r_; }	/* 476699: inc dword ptr [0xa1efb8] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47669f: cmp edx, ebx */
	if (!m->zf) goto L_476719;	/* 4766a1: jne 0x476719 */
	m->edx = M32((DWORD)(m->edi + 0x0u));	/* 4766a3: mov edx, dword ptr [edi] */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 4766a5: mov ecx, dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 4766a8: mov eax, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 4766ab: mov dword ptr [esp + 0x34], edx */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 4766af: mov edx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 4766b5: mov dword ptr [esp + 0x3c], ecx */
	m->ecx = M32((DWORD)(0xa0e7f0u));	/* 4766b9: mov ecx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 4766bf: mov dword ptr [esp + 0x40], edx */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 4766c3: mov dword ptr [esp + 0x38], eax */
	m->eax = M32((DWORD)(0xa0e7ecu));	/* 4766c7: mov eax, dword ptr [0xa0e7ec] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 4766cc: lea edx, [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x48u)) = m->ecx;	/* 4766d0: mov dword ptr [esp + 0x48], ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4766d4: push edx */
	m->ecx = m->ebp;	/* 4766d5: mov ecx, ebp */
	M32((DWORD)(m->esp + 0x30u)) = 0x2u;	/* 4766d7: mov dword ptr [esp + 0x30], 2 */
	M32((DWORD)(m->esp + 0x34u)) = m->ebx;	/* 4766df: mov dword ptr [esp + 0x34], ebx */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 4766e3: mov dword ptr [esp + 0x48], eax */
	M32((DWORD)(m->esp + 0x50u)) = m->ebx;	/* 4766e7: mov dword ptr [esp + 0x50], ebx */
	M32((DWORD)(m->esp + 0x54u)) = m->ebx;	/* 4766eb: mov dword ptr [esp + 0x54], ebx */
	M32((DWORD)(m->esp + 0x58u)) = m->ebx;	/* 4766ef: mov dword ptr [esp + 0x58], ebx */
	M32((DWORD)(m->esp + 0x5cu)) = 0x0u;	/* 4766f3: mov dword ptr [esp + 0x5c], 0 */
	M32((DWORD)(m->esp + 0x60u)) = m->ebx;	/* 4766fb: mov dword ptr [esp + 0x60], ebx */
	m->esp -= 4; M32(m->esp) = 0x476704u; native_call(m, 0x479950u);	/* 4766ff: call 0x479950 */
	m->eax = M32((DWORD)(m->esi + 0x6cu));	/* 476704: mov eax, dword ptr [esi + 0x6c] */
	M32((DWORD)(m->esi + 0x84u)) = 0x3dcccccdu;	/* 476707: mov dword ptr [esi + 0x84], 0x3dcccccd */
	M32((DWORD)(m->esi + 0x70u)) = m->eax;	/* 476711: mov dword ptr [esi + 0x70], eax */
	goto L_476820;	/* 476714: jmp 0x476820 */
L_476719:
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 476719: mov ecx, dword ptr [edi] */
	m->edx = M32((DWORD)(m->edi + 0x4u));	/* 47671b: mov edx, dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 47671e: mov eax, dword ptr [edi + 8] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 476721: mov dword ptr [esp + 0x34], ecx */
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 476725: mov ecx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->esp + 0x38u)) = m->edx;	/* 47672b: mov dword ptr [esp + 0x38], edx */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 47672f: mov edx, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->esp + 0x40u)) = m->ecx;	/* 476735: mov dword ptr [esp + 0x40], ecx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 476739: lea ecx, [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 47673d: mov dword ptr [esp + 0x3c], eax */
	m->eax = M32((DWORD)(0xa0e7f0u));	/* 476741: mov eax, dword ptr [0xa0e7f0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476746: push ecx */
	m->ecx = m->ebp;	/* 476747: mov ecx, ebp */
	M32((DWORD)(m->esp + 0x30u)) = m->ebx;	/* 476749: mov dword ptr [esp + 0x30], ebx */
	M32((DWORD)(m->esp + 0x34u)) = m->ebx;	/* 47674d: mov dword ptr [esp + 0x34], ebx */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 476751: mov dword ptr [esp + 0x48], edx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 476755: mov dword ptr [esp + 0x4c], eax */
	M32((DWORD)(m->esp + 0x50u)) = m->ebx;	/* 476759: mov dword ptr [esp + 0x50], ebx */
	M32((DWORD)(m->esp + 0x54u)) = m->ebx;	/* 47675d: mov dword ptr [esp + 0x54], ebx */
	M32((DWORD)(m->esp + 0x58u)) = m->ebx;	/* 476761: mov dword ptr [esp + 0x58], ebx */
	M32((DWORD)(m->esp + 0x5cu)) = 0x0u;	/* 476765: mov dword ptr [esp + 0x5c], 0 */
	M32((DWORD)(m->esp + 0x60u)) = m->ebx;	/* 47676d: mov dword ptr [esp + 0x60], ebx */
	m->esp -= 4; M32(m->esp) = 0x476776u; native_call(m, 0x479950u);	/* 476771: call 0x479950 */
	M32((DWORD)(m->esi + 0x84u)) = 0x3dcccccdu;	/* 476776: mov dword ptr [esi + 0x84], 0x3dcccccd */
	goto L_476820;	/* 476780: jmp 0x476820 */
L_476785:
	{ DWORD a_ = m->ecx, b_ = 0x19u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 476785: sub ecx, 0x19 */
	if (m->zf) goto L_476791;	/* 476788: je 0x476791 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 47678a: dec ecx */
	if (!m->zf) goto L_476820;	/* 47678b: jne 0x476820 */
L_476791:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 476791: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 476797: fsub dword ptr [esp + 0x10] */
	{ long double t = ST(0); FPUSH(t); }	/* 47679b: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47679d: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9554u));	/* 47679f: fmul dword ptr [0x4a9554] */
	goto L_47681b;	/* 4767a5: jmp 0x47681b */
L_4767a7:
	m->eax = (DWORD)(m->ecx + 0xffffffe2u);	/* 4767a7: lea eax, [ecx - 0x1e] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4767aa: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_476820;	/* 4767ad: ja 0x476820 */
	switch (m->eax) { case 0: goto L_4767b6; case 1: goto L_4767b6; case 2: goto L_476807; case 3: goto L_476807; case 4: goto L_476807; default: abort(); }	/* 4767af: jmp dword ptr [eax*4 + 0x476868] */
L_4767b6:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4767b6: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4767bc: fsub dword ptr [esp + 0x10] */
	{ long double t = ST(0); FPUSH(t); }	/* 4767c0: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4767c2: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94bcu));	/* 4767c4: fmul dword ptr [0x4a94bc] */
	goto L_47681b;	/* 4767ca: jmp 0x47681b */
L_4767cc:
	m->eax = (DWORD)(m->ecx + 0xffffffddu);	/* 4767cc: lea eax, [ecx - 0x23] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4767cf: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_476820;	/* 4767d2: ja 0x476820 */
	switch (m->eax) { case 0: goto L_4767db; case 1: goto L_4767f1; case 2: goto L_476807; case 3: goto L_476807; default: abort(); }	/* 4767d4: jmp dword ptr [eax*4 + 0x47687c] */
L_4767db:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4767db: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4767e1: fsub dword ptr [esp + 0x10] */
	{ long double t = ST(0); FPUSH(t); }	/* 4767e5: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4767e7: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa430u));	/* 4767e9: fmul dword ptr [0x4aa430] */
	goto L_47681b;	/* 4767ef: jmp 0x47681b */
L_4767f1:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4767f1: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4767f7: fsub dword ptr [esp + 0x10] */
	{ long double t = ST(0); FPUSH(t); }	/* 4767fb: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4767fd: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa42cu));	/* 4767ff: fmul dword ptr [0x4aa42c] */
	goto L_47681b;	/* 476805: jmp 0x47681b */
L_476807:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 476807: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47680d: fsub dword ptr [esp + 0x10] */
	{ long double t = ST(0); FPUSH(t); }	/* 476811: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 476813: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a949cu));	/* 476815: fmul dword ptr [0x4a949c] */
L_47681b:
	MF((DWORD)(m->esi + 0x7cu)) = (float)ST(0); FPOP();	/* 47681b: fstp dword ptr [esi + 0x7c] */
	ST(0) = ST(0); FPOP();	/* 47681e: fstp st(0) */
L_476820:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 476820: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x74u));	/* 476827: fadd dword ptr [esi + 0x74] */
	m->edi = M32(m->esp); m->esp += 4;	/* 47682a: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47682b: pop ebx */
	MF((DWORD)(m->esi + 0x74u)) = (float)ST(0); FPOP();	/* 47682c: fstp dword ptr [esi + 0x74] */
	m->esi = M32(m->esp); m->esp += 4;	/* 47682f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 476830: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 476831: add esp, 0x98 */
	m->esp += 4 + 8; return;	/* 476837: ret 8 */
}

/* actor_render (0x490440), lifted by tools/lift.py */
static void lift_490440(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490440: sub esp, 0x98 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 490446: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 490447: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490448: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490449: push edi */
	m->edi = M32((DWORD)(m->esp + 0xacu));	/* 49044a: mov edi, dword ptr [esp + 0xac] */
	m->ebx = m->ecx;	/* 490451: mov ebx, ecx */
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 490453: lea eax, [edi + edi*4] */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 490456: lea eax, [eax + eax*8] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 490459: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49045c: sub eax, edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + m->eax*4 + 0x131b0e0u)));	/* 49045e: fld dword ptr [ebx + eax*4 + 0x131b0e0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 490465: fcomp dword ptr [0x4a93e8] */
	m->ebp = (DWORD)(m->ebx + m->eax*4 + 0x131ae44u);	/* 49046b: lea ebp, [ebx + eax*4 + 0x131ae44] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490472: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490474: test ah, 0x40 */
	if (!m->zf) goto L_4905bf;	/* 490477: jne 0x4905bf */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 49047d: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x29cu));	/* 490484: fmul dword ptr [ebp + 0x29c] */
	m->eax = M32((DWORD)(m->ebp + 0x2a0u));	/* 49048a: mov eax, dword ptr [ebp + 0x2a0] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 490490: dec eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x298u));	/* 490491: fadd dword ptr [ebp + 0x298] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 490497: fstp dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 49049b: mov ecx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ebp + 0x298u)) = m->ecx;	/* 49049f: mov dword ptr [ebp + 0x298], ecx */
	if (m->zf) goto L_490556;	/* 4904a5: je 0x490556 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4904ab: dec eax */
	if (m->zf) goto L_490503;	/* 4904ac: je 0x490503 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4904ae: dec eax */
	if (!m->zf) goto L_4905b5;	/* 4904af: jne 0x4905b5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4904b5: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4904b9: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4904bf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4904c1: test ah, 1 */
	if (!m->zf) goto L_4904db;	/* 4904c4: jne 0x4904db */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4904c6: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 4904ca: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4904d0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4904d2: test ah, 0x41 */
	if (!m->zf) goto L_4905b5;	/* 4904d5: jne 0x4905b5 */
L_4904db:
	m->ecx = M32((DWORD)(m->ebp + 0x28cu));	/* 4904db: mov ecx, dword ptr [ebp + 0x28c] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4904e1: xor esi, esi */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4904e3: cmp ecx, esi */
	M32((DWORD)(m->ebp + 0x298u)) = m->esi;	/* 4904e5: mov dword ptr [ebp + 0x298], esi */
	M32((DWORD)(m->ebp + 0x29cu)) = m->esi;	/* 4904eb: mov dword ptr [ebp + 0x29c], esi */
	if (m->zf) goto L_4904f8;	/* 4904f1: je 0x4904f8 */
	m->esp -= 4; M32(m->esp) = 0x4904f8u; native_call(m, 0x480480u);	/* 4904f3: call 0x480480 */
L_4904f8:
	M32((DWORD)(m->ebp + 0x290u)) = m->esi;	/* 4904f8: mov dword ptr [ebp + 0x290], esi */
	goto L_4905b5;	/* 4904fe: jmp 0x4905b5 */
L_490503:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 490503: fld dword ptr [0x4a9424] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->ebp + 0x29cu));	/* 490509: fdiv dword ptr [ebp + 0x29c] */
	FPUSH((long double)(int)M32((DWORD)(m->ebx + 0x20fcd40u)));	/* 49050f: fild dword ptr [ebx + 0x20fcd40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20fcd44u));	/* 490515: fadd dword ptr [ebx + 0x20fcd44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94bcu));	/* 49051b: fmul dword ptr [0x4a94bc] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 490521: call 0x49ec14 */
	{ long double t = ST(0); FPUSH(t); }	/* 490526: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94bcu));	/* 490528: fmul dword ptr [0x4a94bc] */
	m->esi = m->eax;	/* 49052e: mov esi, eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 490530: call 0x49ec14 */
	m->ecx = m->eax;	/* 490535: mov ecx, eax */
	m->eax = m->esi;	/* 490537: mov eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 490539: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49053a: idiv ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 49053c: mov dword ptr [esp + 0x10], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 490540: fild dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 490544: fmul dword ptr [0x4a9480] */
	ST(0) = ST(0) / ST(1);	/* 49054a: fdiv st(1) */
	MF((DWORD)(m->ebp + 0x298u)) = (float)ST(0); FPOP();	/* 49054c: fstp dword ptr [ebp + 0x298] */
	ST(0) = ST(0); FPOP();	/* 490552: fstp st(0) */
	goto L_4905b5;	/* 490554: jmp 0x4905b5 */
L_490556:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 490556: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49055a: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490560: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490562: test ah, 1 */
	if (m->zf) goto L_490590;	/* 490565: je 0x490590 */
	m->ecx = M32((DWORD)(m->ebp + 0x28cu));	/* 490567: mov ecx, dword ptr [ebp + 0x28c] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 49056d: xor esi, esi */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49056f: cmp ecx, esi */
	M32((DWORD)(m->ebp + 0x298u)) = m->esi;	/* 490571: mov dword ptr [ebp + 0x298], esi */
	M32((DWORD)(m->ebp + 0x29cu)) = m->esi;	/* 490577: mov dword ptr [ebp + 0x29c], esi */
	if (m->zf) goto L_4904f8;	/* 49057d: je 0x4904f8 */
	m->esp -= 4; M32(m->esp) = 0x490588u; native_call(m, 0x480480u);	/* 490583: call 0x480480 */
	M32((DWORD)(m->ebp + 0x290u)) = m->esi;	/* 490588: mov dword ptr [ebp + 0x290], esi */
	goto L_4905b5;	/* 49058e: jmp 0x4905b5 */
L_490590:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 490590: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 490594: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49059a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49059c: test ah, 0x41 */
	if (!m->zf) goto L_4905b5;	/* 49059f: jne 0x4905b5 */
	M32((DWORD)(m->ebp + 0x298u)) = 0x3f800000u;	/* 4905a1: mov dword ptr [ebp + 0x298], 0x3f800000 */
	M32((DWORD)(m->ebp + 0x29cu)) = 0x0u;	/* 4905ab: mov dword ptr [ebp + 0x29c], 0 */
L_4905b5:
	M32((DWORD)(m->ebp + 0x2a4u)) = 0x1u;	/* 4905b5: mov dword ptr [ebp + 0x2a4], 1 */
L_4905bf:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2a4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4905bf: cmp dword ptr [ebp + 0x2a4], 1 */
	if (!m->zf) goto L_4906d6;	/* 4905c6: jne 0x4906d6 */
	m->edx = M32((DWORD)(m->ebp + 0x298u));	/* 4905cc: mov edx, dword ptr [ebp + 0x298] */
	m->ecx = M32((DWORD)(m->ebp + 0x294u));	/* 4905d2: mov ecx, dword ptr [ebp + 0x294] */
	m->edi = (DWORD)(m->ebp + 0x174u);	/* 4905d8: lea edi, [ebp + 0x174] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4905de: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4905df: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4905e1: push edi */
	m->esp -= 4; M32(m->esp) = 0x4905e7u; native_call(m, 0x46ab30u);	/* 4905e2: call 0x46ab30 */
	m->eax = (DWORD)(m->ebp + 0x74u);	/* 4905e7: lea eax, [ebp + 0x74] */
	m->esi = (DWORD)(m->ebp + 0xf4u);	/* 4905ea: lea esi, [ebp + 0xf4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4905f0: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4905f1: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4905f2: push esi */
	m->esp -= 4; M32(m->esp) = 0x4905f8u; native_call(m, 0x47d380u);	/* 4905f3: call 0x47d380 */
	m->eax = (DWORD)(m->ebp + 0x134u);	/* 4905f8: lea eax, [ebp + 0x134] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4905fe: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4905ff: push eax */
	m->esp -= 4; M32(m->esp) = 0x490605u; native_call(m, 0x47d740u);	/* 490600: call 0x47d740 */
	m->ecx = (DWORD)(m->ebp + 0x1b4u);	/* 490605: lea ecx, [ebp + 0x1b4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49060b: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49060c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x490612u; native_call(m, 0x47d740u);	/* 49060d: call 0x47d740 */
	m->edx = (DWORD)(m->ebp + 0xb4u);	/* 490612: lea edx, [ebp + 0xb4] */
	m->edi = (DWORD)(m->ebp + 0x1f4u);	/* 490618: lea edi, [ebp + 0x1f4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49061e: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49061f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490620: push edi */
	m->esp -= 4; M32(m->esp) = 0x490626u; native_call(m, 0x47d380u);	/* 490621: call 0x47d380 */
	m->eax = (DWORD)(m->ebp + 0x234u);	/* 490626: lea eax, [ebp + 0x234] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49062c: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49062d: push eax */
	m->esp -= 4; M32(m->esp) = 0x490633u; native_call(m, 0x47d740u);	/* 49062e: call 0x47d740 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0xcu))) & 0xff) << 0);	/* 490633: mov al, byte ptr [ebp + 0xc] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490636: add esp, 0x30 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490639: test al, 2 */
	if (!m->zf) goto L_490663;	/* 49063b: jne 0x490663 */
	m->edx = M32((DWORD)(m->ebp + 0x27cu));	/* 49063d: mov edx, dword ptr [ebp + 0x27c] */
	m->eax = (DWORD)(m->ebp + 0x134u);	/* 490643: lea eax, [ebp + 0x134] */
	m->ecx = (DWORD)(m->ebx + 0x9ccffcu);	/* 490649: lea ecx, [ebx + 0x9ccffc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49064f: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x280u));	/* 490650: mov eax, dword ptr [ebp + 0x280] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 490656: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 490657: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 490658: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49065a: push eax */
	m->esp -= 4; M32(m->esp) = 0x490660u; native_call(m, 0x466910u);	/* 49065b: call 0x466910 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490660: add esp, 0x14 */
L_490663:
	m->eax = M32((DWORD)(m->ebp + 0x27cu));	/* 490663: mov eax, dword ptr [ebp + 0x27c] */
	M32((DWORD)(m->ebp + 0x2a4u)) = 0x0u;	/* 490669: mov dword ptr [ebp + 0x2a4], 0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 490673: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 490676: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 490679: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 49067c: fmul dword ptr [eax + 0x24] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49067f: add eax, 0x20 */
	m->edi = M32((DWORD)(m->esp + 0xacu));	/* 490682: mov edi, dword ptr [esp + 0xac] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 490689: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49068b: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 49068d: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49068f: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 490691: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->ebp + 0x2bcu)) = (float)ST(0); FPOP();	/* 490694: fstp dword ptr [ebp + 0x2bc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 49069a: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 49069d: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 4906a0: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4906a3: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4906a5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 4906a7: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4906aa: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4906ad: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4906af: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->ebp + 0x2c0u)) = (float)ST(0); FPOP();	/* 4906b2: fstp dword ptr [ebp + 0x2c0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 4906b8: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4906bb: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 4906be: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4906c1: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4906c3: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 4906c5: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4906c8: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4906cb: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4906cd: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->ebp + 0x2c4u)) = (float)ST(0); FPOP();	/* 4906d0: fstp dword ptr [ebp + 0x2c4] */
L_4906d6:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x288u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4906d6: cmp dword ptr [ebp + 0x288], 1 */
	if (!m->zf) goto L_490738;	/* 4906dd: jne 0x490738 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0xcu)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4906df: test byte ptr [ebp + 0xc], 2 */
	if (!m->zf) goto L_490738;	/* 4906e3: jne 0x490738 */
	m->ecx = M32((DWORD)(m->ebp + 0x27cu));	/* 4906e5: mov ecx, dword ptr [ebp + 0x27c] */
	m->esi = M32((DWORD)(m->ebp + 0x280u));	/* 4906eb: mov esi, dword ptr [ebp + 0x280] */
	m->edi = M32((DWORD)(m->ebp + 0x284u));	/* 4906f1: mov edi, dword ptr [ebp + 0x284] */
	m->eax = (DWORD)(m->ebp + 0x134u);	/* 4906f7: lea eax, [ebp + 0x134] */
	m->ecx = M32((DWORD)(m->ecx + 0x18u));	/* 4906fd: mov ecx, dword ptr [ecx + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490700: push eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 490701: shl ecx, 2 */
	m->edx = m->ecx;	/* 490704: mov edx, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 490706: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 490709: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 49070b: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49070d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 490710: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edx = M32((DWORD)(m->ebp + 0x27cu));	/* 490712: mov edx, dword ptr [ebp + 0x27c] */
	m->eax = M32((DWORD)(m->ebp + 0x284u));	/* 490718: mov eax, dword ptr [ebp + 0x284] */
	m->ecx = (DWORD)(m->ebx + 0x9d8010u);	/* 49071e: lea ecx, [ebx + 0x9d8010] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 490724: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 490725: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 490726: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490728: push eax */
	m->esp -= 4; M32(m->esp) = 0x49072eu; native_call(m, 0x466910u);	/* 490729: call 0x466910 */
	m->edi = M32((DWORD)(m->esp + 0xc0u));	/* 49072e: mov edi, dword ptr [esp + 0xc0] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490735: add esp, 0x14 */
L_490738:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0xcu)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490738: test byte ptr [ebp + 0xc], 1 */
	if (m->zf) goto L_4909a3;	/* 49073c: je 0x4909a3 */
	{ DWORD a_ = M32((DWORD)(0x83a9c8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490742: cmp dword ptr [0x83a9c8], 1 */
	if (!m->zf) goto L_4909a3;	/* 490749: jne 0x4909a3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a94u)));	/* 49074f: fld dword ptr [ebx + 0x20f3a94] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x60u));	/* 490755: fmul dword ptr [ebp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a84u)));	/* 490758: fld dword ptr [ebx + 0x20f3a84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x5cu));	/* 49075e: fmul dword ptr [ebp + 0x5c] */
	m->esi = (DWORD)(m->ebp + 0x58u);	/* 490761: lea esi, [ebp + 0x58] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 490764: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a74u)));	/* 490766: fld dword ptr [ebx + 0x20f3a74] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 49076c: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49076e: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3aa4u));	/* 490770: fadd dword ptr [ebx + 0x20f3aa4] */
	MF((DWORD)(m->ebp + 0x2acu)) = (float)ST(0); FPOP();	/* 490776: fstp dword ptr [ebp + 0x2ac] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a98u)));	/* 49077c: fld dword ptr [ebx + 0x20f3a98] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 490782: fmul dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a78u)));	/* 490785: fld dword ptr [ebx + 0x20f3a78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 49078b: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49078d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a88u)));	/* 49078f: fld dword ptr [ebx + 0x20f3a88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 490795: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 490798: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3aa8u));	/* 49079a: fadd dword ptr [ebx + 0x20f3aa8] */
	MF((DWORD)(m->ebp + 0x2b0u)) = (float)ST(0); FPOP();	/* 4907a0: fstp dword ptr [ebp + 0x2b0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a9cu)));	/* 4907a6: fld dword ptr [ebx + 0x20f3a9c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 4907ac: fmul dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a7cu)));	/* 4907af: fld dword ptr [ebx + 0x20f3a7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 4907b5: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4907b7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a8cu)));	/* 4907b9: fld dword ptr [ebx + 0x20f3a8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4907bf: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4907c2: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3aacu));	/* 4907c4: fadd dword ptr [ebx + 0x20f3aac] */
	MF((DWORD)(m->ebp + 0x2b4u)) = (float)ST(0); FPOP();	/* 4907ca: fstp dword ptr [ebp + 0x2b4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3aa0u)));	/* 4907d0: fld dword ptr [ebx + 0x20f3aa0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 4907d6: fmul dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a80u)));	/* 4907d9: fld dword ptr [ebx + 0x20f3a80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 4907df: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4907e1: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3a90u)));	/* 4907e3: fld dword ptr [ebx + 0x20f3a90] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4907e9: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4907ec: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3ab0u));	/* 4907ee: fadd dword ptr [ebx + 0x20f3ab0] */
	MF((DWORD)(m->ebp + 0x2b8u)) = (float)ST(0); FPOP();	/* 4907f4: fstp dword ptr [ebp + 0x2b8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2b8u)));	/* 4907fa: fld dword ptr [ebp + 0x2b8] */
	ST(0) = -ST(0);	/* 490800: fchs  */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 490802: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2acu)));	/* 490806: fld dword ptr [ebp + 0x2ac] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 49080c: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490810: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490812: test ah, 0x41 */
	if (!m->zf) goto L_4908cb;	/* 490815: jne 0x4908cb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2b0u)));	/* 49081b: fld dword ptr [ebp + 0x2b0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 490821: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490825: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490827: test ah, 0x41 */
	if (!m->zf) goto L_4908cb;	/* 49082a: jne 0x4908cb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2b4u)));	/* 490830: fld dword ptr [ebp + 0x2b4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 490836: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49083a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49083c: test ah, 0x41 */
	if (!m->zf) goto L_4908cb;	/* 49083f: jne 0x4908cb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2acu)));	/* 490845: fld dword ptr [ebp + 0x2ac] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x2b8u)); FPOP();	/* 49084b: fcomp dword ptr [ebp + 0x2b8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490851: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490853: test ah, 1 */
	if (m->zf) goto L_4908cb;	/* 490856: je 0x4908cb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2b0u)));	/* 490858: fld dword ptr [ebp + 0x2b0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x2b8u)); FPOP();	/* 49085e: fcomp dword ptr [ebp + 0x2b8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490864: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490866: test ah, 1 */
	if (m->zf) goto L_4908cb;	/* 490869: je 0x4908cb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2b4u)));	/* 49086b: fld dword ptr [ebp + 0x2b4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x2b8u)); FPOP();	/* 490871: fcomp dword ptr [ebp + 0x2b8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490877: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490879: test ah, 1 */
	if (m->zf) goto L_4908cb;	/* 49087c: je 0x4908cb */
	m->ecx = (DWORD)(m->esp + 0x9cu);	/* 49087e: lea ecx, [esp + 0x9c] */
	m->edx = (DWORD)(m->ebx + 0x20f3970u);	/* 490885: lea edx, [ebx + 0x20f3970] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49088b: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49088c: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49088d: push edx */
	m->ecx = m->ebx;	/* 49088e: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x490895u; native_call(m, 0x471740u);	/* 490890: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 490895: test eax, eax */
	if (!m->zf) goto L_4908cb;	/* 490897: jne 0x4908cb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 490899: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 4908a0: fmul dword ptr [0x4a947c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x2a8u));	/* 4908a6: fadd dword ptr [ebp + 0x2a8] */
	MF((DWORD)(m->ebp + 0x2a8u)) = (float)ST(0);	/* 4908ac: fst dword ptr [ebp + 0x2a8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 4908b2: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4908b8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4908ba: test ah, 0x41 */
	if (!m->zf) goto L_4908fb;	/* 4908bd: jne 0x4908fb */
	M32((DWORD)(m->ebp + 0x2a8u)) = 0x3f800000u;	/* 4908bf: mov dword ptr [ebp + 0x2a8], 0x3f800000 */
	goto L_4908fb;	/* 4908c9: jmp 0x4908fb */
L_4908cb:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 4908cb: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 4908d2: fmul dword ptr [0x4a947c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ebp + 0x2a8u));	/* 4908d8: fsubr dword ptr [ebp + 0x2a8] */
	MF((DWORD)(m->ebp + 0x2a8u)) = (float)ST(0);	/* 4908de: fst dword ptr [ebp + 0x2a8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4908e4: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4908ea: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4908ec: test ah, 1 */
	if (m->zf) goto L_4908fb;	/* 4908ef: je 0x4908fb */
	M32((DWORD)(m->ebp + 0x2a8u)) = 0x0u;	/* 4908f1: mov dword ptr [ebp + 0x2a8], 0 */
L_4908fb:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0xcu)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4908fb: test byte ptr [ebp + 0xc], 1 */
	if (m->zf) goto L_4909a3;	/* 4908ff: je 0x4909a3 */
	{ DWORD a_ = M32((DWORD)(0x83a9c8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490905: cmp dword ptr [0x83a9c8], 1 */
	if (!m->zf) goto L_4909a3;	/* 49090c: jne 0x4909a3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2a8u)));	/* 490912: fld dword ptr [ebp + 0x2a8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 490918: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49091e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490920: test ah, 0x41 */
	if (!m->zf) goto L_4909a3;	/* 490923: jne 0x4909a3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2a8u)));	/* 490925: fld dword ptr [ebp + 0x2a8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 49092b: fmul dword ptr [0x4a9744] */
	m->eax = M32((DWORD)(m->ebp + 0x274u));	/* 490931: mov eax, dword ptr [ebp + 0x274] */
	m->edi = M32((DWORD)(m->ebp + 0x278u));	/* 490937: mov edi, dword ptr [ebp + 0x278] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 49093d: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x20u)) = 0x4u;	/* 490941: mov dword ptr [esp + 0x20], 4 */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 490949: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 49094e: mov ecx, dword ptr [esi] */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 490950: mov edx, dword ptr [esi + 4] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 490953: mov dword ptr [esp + 0x24], eax */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 490957: mov eax, dword ptr [esi + 8] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 49095a: mov dword ptr [esp + 0x30], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49095e: xor eax, eax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 490960: mov dword ptr [esp + 0x28], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 490964: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x40u)) = m->eax;	/* 490968: mov dword ptr [esp + 0x40], eax */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 49096c: mov dword ptr [esp + 0x44], eax */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 490970: mov dword ptr [esp + 0x48], eax */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 490974: mov dword ptr [esp + 0x4c], eax */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 490978: mov dword ptr [esp + 0x50], eax */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 49097c: mov dword ptr [esp + 0x2c], edx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 490980: mov edx, dword ptr [esp + 0x1c] */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 490984: lea eax, [esp + 0x20] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 490988: mov dword ptr [esp + 0x34], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49098c: push eax */
	m->ecx = m->ebx;	/* 49098d: mov ecx, ebx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edi;	/* 49098f: mov dword ptr [esp + 0x3c], edi */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 490993: mov dword ptr [esp + 0x40], edx */
	m->esp -= 4; M32(m->esp) = 0x49099cu; native_call(m, 0x479950u);	/* 490997: call 0x479950 */
	m->edi = M32((DWORD)(m->esp + 0xacu));	/* 49099c: mov edi, dword ptr [esp + 0xac] */
L_4909a3:
	m->eax = M32((DWORD)(m->ebp + 0xcu));	/* 4909a3: mov eax, dword ptr [ebp + 0xc] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x8u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4909a6: test al, 8 */
	if (m->zf) goto L_490a84;	/* 4909a8: je 0x490a84 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8c8u));	/* 4909ae: mov eax, dword ptr [ebx + 0x202e8c8] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4aa4a4u)));	/* 4909b4: fld dword ptr [0x4aa4a4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4909ba: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_490a0f;	/* 4909bc: jle 0x490a0f */
	m->ecx = (DWORD)(m->ebx + 0x1cd9504u);	/* 4909be: lea ecx, [ebx + 0x1cd9504] */
	m->edx = m->eax;	/* 4909c4: mov edx, eax */
L_4909c6:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0xfffffff0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4909c6: cmp dword ptr [ecx - 0x10], 1 */
	if (!m->zf) goto L_490a06;	/* 4909ca: jne 0x490a06 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xfffffff8u)));	/* 4909cc: fld dword ptr [ecx - 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x58u));	/* 4909cf: fsub dword ptr [ebp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xfffffffcu)));	/* 4909d2: fld dword ptr [ecx - 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x5cu));	/* 4909d5: fsub dword ptr [ebp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 4909d8: fld dword ptr [ecx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x60u));	/* 4909da: fsub dword ptr [ebp + 0x60] */
	{ long double t = ST(0); FPUSH(t); }	/* 4909dd: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4909df: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 4909e1: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 4909e3: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4909e5: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 4909e7: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 4909e9: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4909eb: faddp st(1) */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 4909ed: fst dword ptr [esp + 0x10] */
	ST(3) = ST(0); FPOP();	/* 4909f1: fstp st(3) */
	ST(0) = ST(0); FPOP();	/* 4909f3: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 4909f5: fstp st(0) */
	FCOM(ST(0), ST(1)); FPOP();	/* 4909f7: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4909f9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4909fb: test ah, 1 */
	if (m->zf) goto L_490a06;	/* 4909fe: je 0x490a06 */
	ST(0) = ST(0); FPOP();	/* 490a00: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 490a02: fld dword ptr [esp + 0x10] */
L_490a06:
	{ DWORD a_ = m->ecx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 490a06: add ecx, 0x8888 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 490a0c: dec edx */
	if (!m->zf) goto L_4909c6;	/* 490a0d: jne 0x4909c6 */
L_490a0f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x29cu)));	/* 490a0f: fld dword ptr [ebp + 0x29c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 490a15: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490a1b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490a1d: test ah, 0x40 */
	if (m->zf) goto L_490a52;	/* 490a20: je 0x490a52 */
	FPUSH((long double)(int)M32((DWORD)(m->ebp + 0x10u)));	/* 490a22: fild dword ptr [ebp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 490a25: fmul dword ptr [0x4a93f4] */
	{ long double t = ST(0); FPUSH(t); }	/* 490a2b: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 490a2d: fmul st(1) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 490a2f: fxch st(1) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 490a31: fxch st(2) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 490a33: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490a35: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490a37: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 490a3a: fstp st(0) */
	if (m->zf) goto L_490b22;	/* 490a3c: je 0x490b22 */
	FPUSH((long double)(int)M32((DWORD)(m->ebp + 0x14u)));	/* 490a42: fild dword ptr [ebp + 0x14] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 490a45: push 1 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 490a47: fmul dword ptr [0x4a9480] */
	goto L_490b03;	/* 490a4d: jmp 0x490b03 */
L_490a52:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x29cu)), b_ = 0x3f800000u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490a52: cmp dword ptr [ebp + 0x29c], 0x3f800000 */
	if (!m->zf) goto L_490b20;	/* 490a5c: jne 0x490b20 */
	FPUSH((long double)(int)M32((DWORD)(m->ebp + 0x10u)));	/* 490a62: fild dword ptr [ebp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 490a65: fmul dword ptr [0x4a93f4] */
	{ long double t = ST(0); FPUSH(t); }	/* 490a6b: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 490a6d: fmul st(1) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 490a6f: fxch st(1) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 490a71: fxch st(2) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 490a73: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490a75: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490a77: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 490a7a: fstp st(0) */
	if (!m->zf) goto L_490b22;	/* 490a7c: jne 0x490b22 */
	goto L_490af8;	/* 490a82: jmp 0x490af8 */
L_490a84:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490a84: test al, 0x10 */
	if (m->zf) goto L_490b22;	/* 490a86: je 0x490b22 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x29cu)));	/* 490a8c: fld dword ptr [ebp + 0x29c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 490a92: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490a98: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490a9a: test ah, 0x40 */
	if (m->zf) goto L_490aec;	/* 490a9d: je 0x490aec */
	FPUSH((long double)(int)M32((DWORD)(m->ebp + 0x10u)));	/* 490a9f: fild dword ptr [ebp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 490aa2: fmul dword ptr [0x4a93f4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x2c8u)); FPOP();	/* 490aa8: fcomp dword ptr [ebp + 0x2c8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490aae: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490ab0: test ah, 0x41 */
	if (!m->zf) goto L_490ad5;	/* 490ab3: jne 0x490ad5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 490ab5: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x2c8u));	/* 490abc: fadd dword ptr [ebp + 0x2c8] */
	m->edi = M32(m->esp); m->esp += 4;	/* 490ac2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 490ac3: pop esi */
	MF((DWORD)(m->ebp + 0x2c8u)) = (float)ST(0); FPOP();	/* 490ac4: fstp dword ptr [ebp + 0x2c8] */
	m->ebp = M32(m->esp); m->esp += 4;	/* 490aca: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 490acb: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490acc: add esp, 0x98 */
	m->esp += 4 + 8; return;	/* 490ad2: ret 8 */
L_490ad5:
	FPUSH((long double)(int)M32((DWORD)(m->ebp + 0x14u)));	/* 490ad5: fild dword ptr [ebp + 0x14] */
	M32((DWORD)(m->ebp + 0x2c8u)) = 0x0u;	/* 490ad8: mov dword ptr [ebp + 0x2c8], 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 490ae2: push 1 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9480u));	/* 490ae4: fmul dword ptr [0x4a9480] */
	goto L_490b03;	/* 490aea: jmp 0x490b03 */
L_490aec:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x29cu)), b_ = 0x3f800000u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490aec: cmp dword ptr [ebp + 0x29c], 0x3f800000 */
	if (!m->zf) goto L_490b22;	/* 490af6: jne 0x490b22 */
L_490af8:
	FPUSH((long double)(int)M32((DWORD)(m->ebp + 0x14u)));	/* 490af8: fild dword ptr [ebp + 0x14] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 490afb: push 1 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa4a0u));	/* 490afd: fmul dword ptr [0x4aa4a0] */
L_490b03:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 490b03: push ecx */
	{ DWORD a_ = m->ebp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 490b04: add ebp, 0x18 */
	m->ecx = m->ebx;	/* 490b07: mov ecx, ebx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 490b09: fstp dword ptr [esp] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 490b0c: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490b0d: push edi */
	m->esp -= 4; M32(m->esp) = 0x490b13u; native_call(m, 0x490df0u);	/* 490b0e: call 0x490df0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 490b13: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 490b14: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 490b15: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 490b16: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490b17: add esp, 0x98 */
	m->esp += 4 + 8; return;	/* 490b1d: ret 8 */
L_490b20:
	ST(0) = ST(0); FPOP();	/* 490b20: fstp st(0) */
L_490b22:
	m->edi = M32(m->esp); m->esp += 4;	/* 490b22: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 490b23: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 490b24: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 490b25: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x98u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490b26: add esp, 0x98 */
	m->esp += 4 + 8; return;	/* 490b2c: ret 8 */
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
