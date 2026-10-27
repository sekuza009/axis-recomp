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

static void lift_479af0(X86 *m);
static void lift_476890(X86 *m);

/* hud_476890 (0x476890), lifted by tools/lift.py */
static void lift_476890(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 476890: sub esp, 0x58 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 476893: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 476894: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x64u));	/* 476895: mov ebp, dword ptr [esp + 0x64] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 476899: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47689a: push edi */
	m->edi = m->ecx;	/* 47689b: mov edi, ecx */
	m->eax = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 47689d: lea eax, [ebp + ebp*2] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4768a1: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4768a4: lea eax, [eax + eax*4] */
	m->ecx = M32((DWORD)(m->edi + m->eax*4 + 0x20a99c8u));	/* 4768a7: mov ecx, dword ptr [edi + eax*4 + 0x20a99c8] */
	m->esi = (DWORD)(m->edi + m->eax*4 + 0x20a99c0u);	/* 4768ae: lea esi, [edi + eax*4 + 0x20a99c0] */
	{ DWORD a_ = m->ecx, b_ = 0x32u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4768b5: cmp ecx, 0x32 */
	if (m->sf == m->of) goto L_47695a;	/* 4768b8: jge 0x47695a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20f3970u)));	/* 4768be: fld dword ptr [edi + 0x20f3970] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xa08u));	/* 4768c4: fsub dword ptr [edi + 0xa08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x10u)); FPOP();	/* 4768ca: fcomp dword ptr [esi + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4768cd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4768cf: test ah, 0x41 */
	if (m->zf) goto L_479840;	/* 4768d2: je 0x479840 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20f3974u)));	/* 4768d8: fld dword ptr [edi + 0x20f3974] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xa08u));	/* 4768de: fsub dword ptr [edi + 0xa08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x14u)); FPOP();	/* 4768e4: fcomp dword ptr [esi + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4768e7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4768e9: test ah, 0x41 */
	if (m->zf) goto L_479840;	/* 4768ec: je 0x479840 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20f3978u)));	/* 4768f2: fld dword ptr [edi + 0x20f3978] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xa08u));	/* 4768f8: fsub dword ptr [edi + 0xa08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x18u)); FPOP();	/* 4768fe: fcomp dword ptr [esi + 0x18] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 476901: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 476903: test ah, 0x41 */
	if (m->zf) goto L_479840;	/* 476906: je 0x479840 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xa08u)));	/* 47690c: fld dword ptr [edi + 0xa08] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x20f3970u));	/* 476912: fadd dword ptr [edi + 0x20f3970] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x10u)); FPOP();	/* 476918: fcomp dword ptr [esi + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47691b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47691d: test ah, 1 */
	if (!m->zf) goto L_479840;	/* 476920: jne 0x479840 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0xa08u)));	/* 476926: fld dword ptr [edi + 0xa08] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x20f3974u));	/* 47692c: fadd dword ptr [edi + 0x20f3974] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x14u)); FPOP();	/* 476932: fcomp dword ptr [esi + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 476935: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 476937: test ah, 1 */
	if (!m->zf) goto L_479840;	/* 47693a: jne 0x479840 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x20f3978u)));	/* 476940: fld dword ptr [edi + 0x20f3978] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0xa08u));	/* 476946: fadd dword ptr [edi + 0xa08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x18u)); FPOP();	/* 47694c: fcomp dword ptr [esi + 0x18] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47694f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 476951: test ah, 1 */
	if (!m->zf) goto L_479840;	/* 476954: jne 0x479840 */
L_47695a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 47695a: fld dword ptr [esi + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47695d: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 476963: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 476965: test ah, 0x41 */
	if (!m->zf) goto L_476976;	/* 476968: jne 0x476976 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 47696a: fld dword ptr [esi + 0x6c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x70u));	/* 47696d: fdiv dword ptr [esi + 0x70] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 476970: fstp dword ptr [esp + 0x10] */
	goto L_47697e;	/* 476974: jmp 0x47697e */
L_476976:
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 476976: mov dword ptr [esp + 0x10], 0 */
L_47697e:
	m->eax = 0x66666667u;	/* 47697e: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 476983: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 476985: sar edx, 1 */
	m->eax = m->edx;	/* 476987: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 476989: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47698c: add edx, eax */
	{ DWORD a_ = m->edx, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47698e: cmp edx, 0xa */
	if (!m->cf && !m->zf) goto L_479840;	/* 476991: ja 0x479840 */
	switch (m->edx) { case 0: goto L_47699e; case 1: goto L_476fa6; case 2: goto L_4777f3; case 3: goto L_477e8a; case 4: goto L_4782f8; case 5: goto L_478472; case 6: goto L_47863b; case 7: goto L_478de9; case 8: goto L_4796e9; case 9: goto L_479736; case 10: goto L_479808; default: abort(); }	/* 476997: jmp dword ptr [edx*4 + 0x47984c] */
L_47699e:
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47699e: cmp ecx, 4 */
	if (!m->cf && !m->zf) goto L_479840;	/* 4769a1: ja 0x479840 */
	switch (m->ecx) { case 0: goto L_4769ae; case 1: goto L_476a7a; case 2: goto L_476b35; case 3: goto L_476d6b; case 4: goto L_476f26; default: abort(); }	/* 4769a7: jmp dword ptr [ecx*4 + 0x479878] */
L_4769ae:
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 4769ae: mov ecx, dword ptr [esi] */
	m->edi = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4769b0: mov edi, dword ptr [edi + 0x9ccfd4] */
	{ DWORD a_ = m->ecx, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4769b6: and ecx, 0x80000007 */
	if (!m->sf) goto L_4769c3;	/* 4769bc: jns 0x4769c3 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4769be: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4769bf: or ecx, 0xfffffff8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4769c2: inc ecx */
L_4769c3:
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4769c3: shl ecx, 5 */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 4769c6: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 4769ca: mov dword ptr [esp + 0x34], 0 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 4769d2: fild dword ptr [esp + 0x6c] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e000000u;	/* 4769d6: mov dword ptr [esp + 0x3c], 0x3e000000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4769de: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 4769e4: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4769e8: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 4769ec: fadd dword ptr [0x4aa274] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4769f2: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4769f6: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4769fc: fsub dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 476a00: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 476a06: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476a0b: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_476a17;	/* 476a10: jle 0x476a17 */
	m->eax = 0xffu;	/* 476a12: mov eax, 0xff */
L_476a17:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 476a17: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 476a1b: fadd dword ptr [0x4a9424] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 476a21: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 476a24: push 1 */
	m->edx = (DWORD)(m->esi + 0x10u);	/* 476a26: lea edx, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 476a29: push 2 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 476a2b: fmul dword ptr [0x4a93f4] */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 476a31: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476a35: push edx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 476a36: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476a3a: push eax */
	{ long double t = ST(0); FPUSH(t); }	/* 476a3b: fld st(0) */
	ST(0) = -ST(0);	/* 476a3d: fchs  */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0);	/* 476a3f: fst dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 476a43: fstp dword ptr [esp + 0x34] */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 476a47: add esi, 0x78 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476a4a: push ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0);	/* 476a4b: fst dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 476a4f: fstp dword ptr [esp + 0x40] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 476a53: push esi */
	{ DWORD v_ = 0x42c80000u; m->esp -= 4; M32(m->esp) = v_; }	/* 476a54: push 0x42c80000 */
L_476a59:
	m->ecx = M32((DWORD)(m->esp + 0x8cu));	/* 476a59: mov ecx, dword ptr [esp + 0x8c] */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 476a60: lea edx, [esp + 0x54] */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 476a64: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476a68: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476a69: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 476a6a: push edi */
	m->esp -= 4; M32(m->esp) = 0x476a70u; native_call(m, 0x484ca0u);	/* 476a6b: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 476a70: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 476a71: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 476a72: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 476a73: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 476a74: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 476a77: ret 8 */
L_476a7a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 476a7a: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 476a7e: fmul dword ptr [0x4a94cc] */
	m->edi = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 476a84: mov edi, dword ptr [edi + 0x9ccfd4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 476a8a: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476a8f: cmp eax, 7 */
	if (m->zf || m->sf != m->of) goto L_476a99;	/* 476a92: jle 0x476a99 */
	m->eax = 0x7u;	/* 476a94: mov eax, 7 */
L_476a99:
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 476a99: shl eax, 5 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 476a9c: mov dword ptr [esp + 0x6c], eax */
	m->ecx = (DWORD)(m->esi + 0x10u);	/* 476aa0: lea ecx, [esi + 0x10] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 476aa3: fild dword ptr [esp + 0x6c] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 476aa7: mov edx, dword ptr [ecx] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 476aa9: push 1 */
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 476aab: mov dword ptr [esp + 0x54], edx */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 476aaf: lea edx, [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 476ab3: fmul dword ptr [0x4a957c] */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 476ab9: mov eax, dword ptr [ecx + 4] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 476abc: push 2 */
	M32((DWORD)(m->esp + 0x5cu)) = m->eax;	/* 476abe: mov dword ptr [esp + 0x5c], eax */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 476ac2: lea eax, [esp + 0x30] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 476ac6: mov ecx, dword ptr [ecx + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476ac9: push edx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 476aca: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 476ace: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 476ad2: fadd dword ptr [0x4aa274] */
	M32((DWORD)(m->esp + 0x64u)) = m->ecx;	/* 476ad8: mov dword ptr [esp + 0x64], ecx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 476adc: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476ae0: push eax */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 476ae1: add esi, 0x78 */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 476ae4: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0xfffffff4u)));	/* 476ae8: fld dword ptr [esi - 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 476aeb: fmul dword ptr [0x4aa440] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476af1: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 476af2: push esi */
	M32((DWORD)(m->esp + 0x4cu)) = 0x0u;	/* 476af3: mov dword ptr [esp + 0x4c], 0 */
	M32((DWORD)(m->esp + 0x54u)) = 0x3e000000u;	/* 476afb: mov dword ptr [esp + 0x54], 0x3e000000 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x6cu));	/* 476b03: fadd dword ptr [esp + 0x6c] */
	M32((DWORD)(m->esp + 0x38u)) = 0xc3960000u;	/* 476b07: mov dword ptr [esp + 0x38], 0xc3960000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0xc3960000u;	/* 476b0f: mov dword ptr [esp + 0x3c], 0xc3960000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x43960000u;	/* 476b17: mov dword ptr [esp + 0x40], 0x43960000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x43960000u;	/* 476b1f: mov dword ptr [esp + 0x44], 0x43960000 */
	{ DWORD v_ = 0x43960000u; m->esp -= 4; M32(m->esp) = v_; }	/* 476b27: push 0x43960000 */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 476b2c: fstp dword ptr [esp + 0x70] */
	goto L_476a59;	/* 476b30: jmp 0x476a59 */
L_476b35:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 476b35: fld dword ptr [esi + 0x6c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9420u)); FPOP();	/* 476b38: fcomp dword ptr [0x4a9420] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 476b3e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 476b40: test ah, 1 */
	if (m->zf) goto L_476c1d;	/* 476b43: je 0x476c1d */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 476b49: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 476b4f: fsub dword ptr [esp + 0x10] */
	m->ebx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 476b53: mov ebx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 476b59: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 476b61: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 476b69: mov dword ptr [esp + 0x38], 0x3f200000 */
	{ long double t = ST(0); FPUSH(t); }	/* 476b71: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 476b73: fmul st(1) */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 476b75: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 476b7d: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 476b83: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 476b88: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 476b8a: fstp st(0) */
	if (m->sf == m->of) goto L_476b92;	/* 476b8c: jge 0x476b92 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 476b8e: xor eax, eax */
	goto L_476b9e;	/* 476b90: jmp 0x476b9e */
L_476b92:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476b92: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_476b9e;	/* 476b97: jle 0x476b9e */
	m->eax = 0xffu;	/* 476b99: mov eax, 0xff */
L_476b9e:
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 476b9e: mov ecx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 476ba1: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 476ba4: mov eax, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4160000u;	/* 476baa: mov dword ptr [esp + 0x20], 0xc4160000 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476bb2: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4160000u;	/* 476bb4: mov dword ptr [esp + 0x24], 0xc4160000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44160000u;	/* 476bbc: mov dword ptr [esp + 0x28], 0x44160000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44160000u;	/* 476bc4: mov dword ptr [esp + 0x2c], 0x44160000 */
	if (!m->zf) goto L_476bee;	/* 476bcc: jne 0x476bee */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3960000u;	/* 476bce: mov dword ptr [esp + 0x20], 0xc3960000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3960000u;	/* 476bd6: mov dword ptr [esp + 0x24], 0xc3960000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43960000u;	/* 476bde: mov dword ptr [esp + 0x28], 0x43960000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43960000u;	/* 476be6: mov dword ptr [esp + 0x2c], 0x43960000 */
L_476bee:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 476bee: push 1 */
	m->edx = (DWORD)(m->esi + 0x10u);	/* 476bf0: lea edx, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 476bf3: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 476bf5: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476bf9: push edx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 476bfa: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476bfe: push eax */
	m->edx = (DWORD)(m->esi + 0x78u);	/* 476bff: lea edx, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476c02: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476c03: push edx */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 476c04: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 476c08: push 0 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 476c0a: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476c0e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476c0f: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 476c10: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 476c17: push ebx */
	m->esp -= 4; M32(m->esp) = 0x476c1du; native_call(m, 0x484ca0u);	/* 476c18: call 0x484ca0 */
L_476c1d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 476c1d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa43cu));	/* 476c21: fmul dword ptr [0x4aa43c] */
	m->edi = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 476c27: mov edi, dword ptr [edi + 0x9ccfd4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 476c2d: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476c32: cmp eax, 0xf */
	if (m->zf || m->sf != m->of) goto L_476c3c;	/* 476c35: jle 0x476c3c */
	m->eax = 0xfu;	/* 476c37: mov eax, 0xf */
L_476c3c:
	m->edx = m->eax;	/* 476c3c: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 476c3e: and edx, 0x80000007 */
	if (!m->sf) goto L_476c4b;	/* 476c44: jns 0x476c4b */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 476c46: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 476c47: or edx, 0xfffffff8 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 476c4a: inc edx */
L_476c4b:
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 476c4b: shl edx, 5 */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 476c4e: mov dword ptr [esp + 0x6c], edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 476c52: cdq  */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 476c53: fild dword ptr [esp + 0x6c] */
	{ DWORD a_ = m->edx, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 476c57: and edx, 7 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 476c5a: add eax, edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 476c5c: fmul dword ptr [0x4a957c] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 476c62: sar eax, 3 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 476c65: add eax, 3 */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 476c68: shl eax, 5 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 476c6b: mov dword ptr [esp + 0x6c], eax */
	m->eax = m->ebp;	/* 476c6f: mov eax, ebp */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 476c71: fild dword ptr [esp + 0x6c] */
	{ DWORD a_ = m->eax, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 476c75: and eax, 0x80000003 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 476c7a: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 476c80: fstp dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 476c84: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 476c86: fadd dword ptr [0x4aa274] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 476c8c: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 476c90: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 476c94: fadd dword ptr [0x4aa274] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 476c9a: fstp dword ptr [esp + 0x1c] */
	if (!m->sf) goto L_476ca5;	/* 476c9e: jns 0x476ca5 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 476ca0: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 476ca1: or eax, 0xfffffffc */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 476ca4: inc eax */
L_476ca5:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476ca5: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_476d29;	/* 476ca8: ja 0x476d29 */
	switch (m->eax) { case 0: goto L_476cb1; case 1: goto L_476ccf; case 2: goto L_476ced; case 3: goto L_476d0b; default: abort(); }	/* 476caa: jmp dword ptr [eax*4 + 0x47988c] */
L_476cb1:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 476cb1: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 476cb5: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 476cb9: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 476cbd: mov dword ptr [esp + 0x34], eax */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 476cc1: fstp dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x38u)) = m->ecx;	/* 476cc5: mov dword ptr [esp + 0x38], ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 476cc9: mov dword ptr [esp + 0x3c], edx */
	goto L_476d2b;	/* 476ccd: jmp 0x476d2b */
L_476ccf:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 476ccf: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 476cd3: mov ecx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 476cd7: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 476cdb: mov dword ptr [esp + 0x34], eax */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 476cdf: fstp dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x38u)) = m->ecx;	/* 476ce3: mov dword ptr [esp + 0x38], ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 476ce7: mov dword ptr [esp + 0x3c], edx */
	goto L_476d2b;	/* 476ceb: jmp 0x476d2b */
L_476ced:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 476ced: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 476cf1: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 476cf5: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 476cf9: mov dword ptr [esp + 0x30], eax */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 476cfd: fstp dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 476d01: mov dword ptr [esp + 0x34], ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 476d05: mov dword ptr [esp + 0x3c], edx */
	goto L_476d2b;	/* 476d09: jmp 0x476d2b */
L_476d0b:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 476d0b: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 476d0f: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 476d13: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 476d17: mov dword ptr [esp + 0x30], eax */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 476d1b: fstp dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x34u)) = m->ecx;	/* 476d1f: mov dword ptr [esp + 0x34], ecx */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 476d23: mov dword ptr [esp + 0x3c], edx */
	goto L_476d2b;	/* 476d27: jmp 0x476d2b */
L_476d29:
	ST(0) = ST(0); FPOP();	/* 476d29: fstp st(0) */
L_476d2b:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 476d2b: push 1 */
	m->eax = (DWORD)(m->esi + 0x10u);	/* 476d2d: lea eax, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 476d30: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 476d32: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476d36: push eax */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 476d37: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476d3b: push ecx */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 476d3c: add esi, 0x78 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476d3f: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 476d40: push esi */
	M32((DWORD)(m->esp + 0x38u)) = 0xc3960000u;	/* 476d41: mov dword ptr [esp + 0x38], 0xc3960000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0xc3960000u;	/* 476d49: mov dword ptr [esp + 0x3c], 0xc3960000 */
	M32((DWORD)(m->esp + 0x40u)) = 0x43960000u;	/* 476d51: mov dword ptr [esp + 0x40], 0x43960000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x43960000u;	/* 476d59: mov dword ptr [esp + 0x44], 0x43960000 */
	{ DWORD v_ = 0x43960000u; m->esp -= 4; M32(m->esp) = v_; }	/* 476d61: push 0x43960000 */
	goto L_4782d7;	/* 476d66: jmp 0x4782d7 */
L_476d6b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 476d6b: fld dword ptr [esi + 0x6c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9420u)); FPOP();	/* 476d6e: fcomp dword ptr [0x4a9420] */
	m->ebp = M32((DWORD)(m->esp + 0x70u));	/* 476d74: mov ebp, dword ptr [esp + 0x70] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 476d78: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 476d7a: test ah, 1 */
	if (m->zf) goto L_476e52;	/* 476d7d: je 0x476e52 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 476d83: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 476d89: fsub dword ptr [esp + 0x10] */
	m->ebx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 476d8d: mov ebx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 476d93: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 476d9b: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 476da3: mov dword ptr [esp + 0x38], 0x3f200000 */
	{ long double t = ST(0); FPUSH(t); }	/* 476dab: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 476dad: fmul st(1) */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 476daf: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 476db7: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 476dbd: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 476dc2: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 476dc4: fstp st(0) */
	if (m->sf == m->of) goto L_476dcc;	/* 476dc6: jge 0x476dcc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 476dc8: xor eax, eax */
	goto L_476dd8;	/* 476dca: jmp 0x476dd8 */
L_476dcc:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476dcc: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_476dd8;	/* 476dd1: jle 0x476dd8 */
	m->eax = 0xffu;	/* 476dd3: mov eax, 0xff */
L_476dd8:
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 476dd8: mov edx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 476ddb: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 476dde: mov eax, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4c80000u;	/* 476de4: mov dword ptr [esp + 0x20], 0xc4c80000 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476dec: cmp edx, eax */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4c80000u;	/* 476dee: mov dword ptr [esp + 0x24], 0xc4c80000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44c80000u;	/* 476df6: mov dword ptr [esp + 0x28], 0x44c80000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44c80000u;	/* 476dfe: mov dword ptr [esp + 0x2c], 0x44c80000 */
	if (!m->zf) goto L_476e28;	/* 476e06: jne 0x476e28 */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4480000u;	/* 476e08: mov dword ptr [esp + 0x20], 0xc4480000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4480000u;	/* 476e10: mov dword ptr [esp + 0x24], 0xc4480000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44480000u;	/* 476e18: mov dword ptr [esp + 0x28], 0x44480000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44480000u;	/* 476e20: mov dword ptr [esp + 0x2c], 0x44480000 */
L_476e28:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 476e28: push 1 */
	m->eax = (DWORD)(m->esi + 0x10u);	/* 476e2a: lea eax, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 476e2d: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 476e2f: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476e33: push eax */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 476e34: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476e38: push ecx */
	m->eax = (DWORD)(m->esi + 0x78u);	/* 476e39: lea eax, [esi + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476e3c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476e3d: push eax */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 476e3e: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 476e42: push 0 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 476e44: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476e48: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476e49: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 476e4a: push ebx */
	m->ecx = m->ebp;	/* 476e4b: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x476e52u; native_call(m, 0x484ca0u);	/* 476e4d: call 0x484ca0 */
L_476e52:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 476e52: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa43cu));	/* 476e56: fmul dword ptr [0x4aa43c] */
	m->edi = M32((DWORD)(m->edi + 0x9ccfdcu));	/* 476e5c: mov edi, dword ptr [edi + 0x9ccfdc] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 476e62: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476e67: cmp eax, 0xf */
	if (m->zf || m->sf != m->of) goto L_476e71;	/* 476e6a: jle 0x476e71 */
	m->eax = 0xfu;	/* 476e6c: mov eax, 0xf */
L_476e71:
	m->ecx = m->eax;	/* 476e71: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 476e73: and ecx, 0x80000003 */
	if (!m->sf) goto L_476e80;	/* 476e79: jns 0x476e80 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 476e7b: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 476e7c: or ecx, 0xfffffffc */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 476e7f: inc ecx */
L_476e80:
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 476e80: shl ecx, 6 */
	M32((DWORD)(m->esp + 0x70u)) = m->ecx;	/* 476e83: mov dword ptr [esp + 0x70], ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 476e87: push 1 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x74u)));	/* 476e89: fild dword ptr [esp + 0x74] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 476e8d: cdq  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 476e8e: fmul dword ptr [0x4a957c] */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 476e94: and edx, 3 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 476e97: push 2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 476e99: add eax, edx */
	m->edx = (DWORD)(m->esi + 0x10u);	/* 476e9b: lea edx, [esi + 0x10] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 476e9e: sar eax, 2 */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 476ea1: fstp dword ptr [esp + 0x38] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 476ea5: shl eax, 6 */
	M32((DWORD)(m->esp + 0x78u)) = m->eax;	/* 476ea8: mov dword ptr [esp + 0x78], eax */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 476eac: lea eax, [esp + 0x30] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x78u)));	/* 476eb0: fild dword ptr [esp + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476eb4: push edx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 476eb5: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476eb9: push eax */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 476eba: add esi, 0x78 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 476ebd: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476ec3: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 476ec4: push esi */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 476ec5: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x44480000u; m->esp -= 4; M32(m->esp) = v_; }	/* 476ec9: push 0x44480000 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 476ece: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476ed2: push edx */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 476ed3: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 476ed7: fld dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 476edb: fadd dword ptr [0x4a941c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476ee1: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 476ee2: push edi */
	m->ecx = m->ebp;	/* 476ee3: mov ecx, ebp */
	M32((DWORD)(m->esp + 0x48u)) = 0xc4480000u;	/* 476ee5: mov dword ptr [esp + 0x48], 0xc4480000 */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 476eed: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 476ef1: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 476ef5: fadd dword ptr [0x4a941c] */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc4480000u;	/* 476efb: mov dword ptr [esp + 0x4c], 0xc4480000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x44480000u;	/* 476f03: mov dword ptr [esp + 0x50], 0x44480000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x44480000u;	/* 476f0b: mov dword ptr [esp + 0x54], 0x44480000 */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 476f13: fstp dword ptr [esp + 0x64] */
	m->esp -= 4; M32(m->esp) = 0x476f1cu; native_call(m, 0x484ca0u);	/* 476f17: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 476f1c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 476f1d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 476f1e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 476f1f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 476f20: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 476f23: ret 8 */
L_476f26:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1cu)));	/* 476f26: fld dword ptr [esi + 0x1c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xcu))) & 0xff) << 0);	/* 476f29: mov cl, byte ptr [esi + 0xc] */
	m->edi = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 476f2c: mov edi, dword ptr [edi + 0x9ccfd4] */
	ST(0) = -ST(0);	/* 476f32: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 476f34: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 476f38: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1cu)));	/* 476f3c: fld dword ptr [esi + 0x1c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 476f3f: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1cu)));	/* 476f43: fld dword ptr [esi + 0x1c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 476f46: push 1 */
	m->edx = (DWORD)(m->esi + 0x10u);	/* 476f48: lea edx, [esi + 0x10] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 476f4b: mov byte ptr [esi + 0x7b], cl */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 476f4e: push 3 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 476f50: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476f54: push edx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 476f55: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476f59: push eax */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 476f5a: add esi, 0x78 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 476f5d: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x84u));	/* 476f5e: mov ecx, dword ptr [esp + 0x84] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 476f65: push esi */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 476f66: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 476f6a: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 476f6c: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 476f70: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 476f71: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 476f72: push edi */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 476f73: fstp dword ptr [esp + 0x54] */
	M32((DWORD)(m->esp + 0x58u)) = 0x3f400000u;	/* 476f77: mov dword ptr [esp + 0x58], 0x3f400000 */
	M32((DWORD)(m->esp + 0x5cu)) = 0x3f400000u;	/* 476f7f: mov dword ptr [esp + 0x5c], 0x3f400000 */
	M32((DWORD)(m->esp + 0x60u)) = 0x3f800000u;	/* 476f87: mov dword ptr [esp + 0x60], 0x3f800000 */
	M32((DWORD)(m->esp + 0x64u)) = 0x3f800000u;	/* 476f8f: mov dword ptr [esp + 0x64], 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x476f9cu; native_call(m, 0x484ca0u);	/* 476f97: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 476f9c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 476f9d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 476f9e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 476f9f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 476fa0: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 476fa3: ret 8 */
L_476fa6:
	m->eax = (DWORD)(m->ecx + 0xfffffffbu);	/* 476fa6: lea eax, [ecx - 5] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 476fa9: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_479840;	/* 476fac: ja 0x479840 */
	switch (m->eax) { case 0: goto L_476fb9; case 1: goto L_4771f1; case 2: goto L_477429; case 3: goto L_477661; case 4: goto L_47771e; default: abort(); }	/* 476fb2: jmp dword ptr [eax*4 + 0x47989c] */
L_476fb9:
	m->edi = M32((DWORD)(m->edi + 0x9ccfe8u));	/* 476fb9: mov edi, dword ptr [edi + 0x9ccfe8] */
	{ DWORD a_ = m->ebp, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 476fbf: and ebp, 0x80000007 */
	if (!m->sf) goto L_476fcc;	/* 476fc5: jns 0x476fcc */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 476fc7: dec ebp */
	{ DWORD a_ = m->ebp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 476fc8: or ebp, 0xfffffff8 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 476fcb: inc ebp */
L_476fcc:
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7c8u)));	/* 476fcc: fld dword ptr [0xa0e7c8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 476fd2: fmul dword ptr [0x4a9558] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7ccu)));	/* 476fd8: fld dword ptr [0xa0e7cc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 476fde: fmul dword ptr [0x4a9558] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7d0u)));	/* 476fe4: fld dword ptr [0xa0e7d0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 476fea: fmul dword ptr [0x4a9558] */
	{ long double t = ST(0); FPUSH(t); }	/* 476ff0: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4cu));	/* 476ff2: fmul dword ptr [esi + 0x4c] */
	{ long double t = ST(2); FPUSH(t); }	/* 476ff5: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x3cu));	/* 476ff7: fmul dword ptr [esi + 0x3c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 476ffa: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x6cu)) = m->ebx;	/* 476ffc: mov dword ptr [esp + 0x6c], ebx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477000: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 477002: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2cu));	/* 477004: fmul dword ptr [esi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477007: faddp st(1) */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 477009: fstp dword ptr [esp + 0x44] */
	{ long double t = ST(0); FPUSH(t); }	/* 47700d: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x50u));	/* 47700f: fmul dword ptr [esi + 0x50] */
	{ long double t = ST(2); FPUSH(t); }	/* 477012: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x40u));	/* 477014: fmul dword ptr [esi + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477017: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 477019: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 47701b: fmul dword ptr [esi + 0x30] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47701e: faddp st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 477020: fstp dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x54u));	/* 477024: fmul dword ptr [esi + 0x54] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 477027: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 477029: fmul dword ptr [esi + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47702c: faddp st(1) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47702e: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 477030: fmul dword ptr [esi + 0x34] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477033: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1cu)));	/* 477035: fld dword ptr [esi + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 477038: fld dword ptr [esp + 0x44] */
	ST(0) = ST(0) * ST(1);	/* 47703c: fmul st(1) */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 47703e: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 477042: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(1);	/* 477046: fmul st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 477048: fstp dword ptr [esp + 0x48] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47704c: fxch st(1) */
	ST(0) = ST(0) * ST(1);	/* 47704e: fmul st(1) */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 477050: fstp dword ptr [esp + 0x4c] */
	ST(0) = ST(0); FPOP();	/* 477054: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 477056: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47705a: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47705e: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 477062: fmul dword ptr [esp + 0x4c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477066: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 477068: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 47706c: fmul dword ptr [esp + 0x48] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477070: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 477072: fsqrt  */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 477074: fst dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 477078: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 47707c: fadd dword ptr [esi + 0x10] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 47707f: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 477083: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 477087: fadd dword ptr [esi + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 47708a: mov ecx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x50u)) = m->ecx;	/* 47708e: mov dword ptr [esp + 0x50], ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 477092: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 477096: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 47709a: fadd dword ptr [esi + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 47709d: mov edx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 4770a1: mov dword ptr [esp + 0x54], edx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4770a5: fstp dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 4770a9: mov eax, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 4770ad: mov dword ptr [esp + 0x58], eax */
L_4770b1:
	m->ecx = (DWORD)(m->ebx + m->ebp*1 + 0x0u);	/* 4770b1: lea ecx, [ebx + ebp] */
	{ DWORD a_ = m->ecx, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4770b4: and ecx, 0x80000007 */
	if (!m->sf) goto L_4770c1;	/* 4770ba: jns 0x4770c1 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4770bc: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4770bd: or ecx, 0xfffffff8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4770c0: inc ecx */
L_4770c1:
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4770c1: shl ecx, 5 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 4770c4: mov dword ptr [esp + 0x1c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 4770c8: mov dword ptr [esp + 0x34], 0 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 4770d0: fild dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e000000u;	/* 4770d4: mov dword ptr [esp + 0x3c], 0x3e000000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4770dc: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 4770e2: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 4770e6: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 4770ea: fadd dword ptr [0x4aa274] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4770f0: fstp dword ptr [esp + 0x38] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 4770f4: fild dword ptr [esp + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a955cu));	/* 4770f8: fmul dword ptr [0x4a955c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4770fe: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 477104: fmul dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 477107: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47710d: call 0x49ec14 */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477112: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477115: push 1 */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 477117: lea edx, [esp + 0x54] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47711b: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 47711d: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477121: push edx */
	{ long double t = ST(0); FPUSH(t); }	/* 477122: fld st(0) */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477124: push eax */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 477125: lea ecx, [esp + 0x30] */
	ST(0) = -ST(0);	/* 477129: fchs  */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0);	/* 47712b: fst dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47712f: fstp dword ptr [esp + 0x34] */
	m->eax = (DWORD)(m->esi + 0x78u);	/* 477133: lea eax, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477136: push ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0);	/* 477137: fst dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x84u));	/* 47713b: mov ecx, dword ptr [esp + 0x84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477142: push eax */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 477143: fstp dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 477147: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47714b: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 47714d: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477151: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477152: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 477153: push edi */
	m->esp -= 4; M32(m->esp) = 0x477159u; native_call(m, 0x484ca0u);	/* 477154: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 477159: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 47715d: fmul dword ptr [0x4aa438] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 477163: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477164: cmp ebx, 0xa */
	M32((DWORD)(m->esp + 0x6cu)) = m->ebx;	/* 477167: mov dword ptr [esp + 0x6c], ebx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 47716b: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47716f: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 477173: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 477179: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47717d: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 477181: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 477187: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47718b: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 47718f: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 477195: fst dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 477199: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 47719d: fmul dword ptr [0x4a94fc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4771a3: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 4771a7: fmul dword ptr [0x4a94fc] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 4771ad: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4771b1: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 4771b5: fmul dword ptr [0x4a94fc] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 4771bb: fstp dword ptr [esp + 0x64] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 4771bf: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4771c3: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 4771c7: fld dword ptr [esp + 0x60] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 4771cb: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 4771cf: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 4771d3: fld dword ptr [esp + 0x58] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 4771d7: fadd dword ptr [esp + 0x64] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 4771db: fstp dword ptr [esp + 0x58] */
	if (m->sf != m->of) goto L_4770b1;	/* 4771df: jl 0x4770b1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4771e5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4771e6: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4771e7: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4771e8: pop ebx */
	ST(0) = ST(0); FPOP();	/* 4771e9: fstp st(0) */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4771eb: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 4771ee: ret 8 */
L_4771f1:
	m->edi = M32((DWORD)(m->edi + 0x9ccfe8u));	/* 4771f1: mov edi, dword ptr [edi + 0x9ccfe8] */
	{ DWORD a_ = m->ebp, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4771f7: and ebp, 0x80000007 */
	if (!m->sf) goto L_477204;	/* 4771fd: jns 0x477204 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 4771ff: dec ebp */
	{ DWORD a_ = m->ebp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 477200: or ebp, 0xfffffff8 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 477203: inc ebp */
L_477204:
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7c8u)));	/* 477204: fld dword ptr [0xa0e7c8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 47720a: fmul dword ptr [0x4a9558] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7ccu)));	/* 477210: fld dword ptr [0xa0e7cc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 477216: fmul dword ptr [0x4a9558] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7d0u)));	/* 47721c: fld dword ptr [0xa0e7d0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 477222: fmul dword ptr [0x4a9558] */
	{ long double t = ST(0); FPUSH(t); }	/* 477228: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4cu));	/* 47722a: fmul dword ptr [esi + 0x4c] */
	{ long double t = ST(2); FPUSH(t); }	/* 47722d: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x3cu));	/* 47722f: fmul dword ptr [esi + 0x3c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 477232: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x6cu)) = m->ebx;	/* 477234: mov dword ptr [esp + 0x6c], ebx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477238: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47723a: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2cu));	/* 47723c: fmul dword ptr [esi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47723f: faddp st(1) */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 477241: fstp dword ptr [esp + 0x44] */
	{ long double t = ST(0); FPUSH(t); }	/* 477245: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x50u));	/* 477247: fmul dword ptr [esi + 0x50] */
	{ long double t = ST(2); FPUSH(t); }	/* 47724a: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x40u));	/* 47724c: fmul dword ptr [esi + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47724f: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 477251: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 477253: fmul dword ptr [esi + 0x30] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477256: faddp st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 477258: fstp dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x54u));	/* 47725c: fmul dword ptr [esi + 0x54] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47725f: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 477261: fmul dword ptr [esi + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477264: faddp st(1) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 477266: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 477268: fmul dword ptr [esi + 0x34] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47726b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1cu)));	/* 47726d: fld dword ptr [esi + 0x1c] */
	{ long double t = ST(0); FPUSH(t); }	/* 477270: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 477272: fmul dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 477276: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47727a: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(1);	/* 47727e: fmul st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 477280: fstp dword ptr [esp + 0x48] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 477284: fxch st(1) */
	ST(0) = ST(0) * ST(1);	/* 477286: fmul st(1) */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 477288: fstp dword ptr [esp + 0x4c] */
	ST(0) = ST(0); FPOP();	/* 47728c: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47728e: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 477292: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 477296: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47729a: fmul dword ptr [esp + 0x4c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47729e: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4772a0: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 4772a4: fmul dword ptr [esp + 0x48] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4772a8: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 4772aa: fsqrt  */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 4772ac: fst dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4772b0: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 4772b4: fadd dword ptr [esi + 0x10] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4772b7: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4772bb: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4772bf: fadd dword ptr [esi + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4772c2: mov ecx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x50u)) = m->ecx;	/* 4772c6: mov dword ptr [esp + 0x50], ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4772ca: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4772ce: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4772d2: fadd dword ptr [esi + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 4772d5: mov edx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 4772d9: mov dword ptr [esp + 0x54], edx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4772dd: fstp dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 4772e1: mov eax, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 4772e5: mov dword ptr [esp + 0x58], eax */
L_4772e9:
	m->ecx = (DWORD)(m->ebx + m->ebp*1 + 0x0u);	/* 4772e9: lea ecx, [ebx + ebp] */
	{ DWORD a_ = m->ecx, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4772ec: and ecx, 0x80000007 */
	if (!m->sf) goto L_4772f9;	/* 4772f2: jns 0x4772f9 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4772f4: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4772f5: or ecx, 0xfffffff8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4772f8: inc ecx */
L_4772f9:
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4772f9: shl ecx, 5 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 4772fc: mov dword ptr [esp + 0x1c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477300: mov dword ptr [esp + 0x34], 0x3e000000 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 477308: fild dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 47730c: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 477314: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 47731a: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 47731e: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 477322: fadd dword ptr [0x4aa274] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 477328: fstp dword ptr [esp + 0x38] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 47732c: fild dword ptr [esp + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a955cu));	/* 477330: fmul dword ptr [0x4a955c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 477336: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 47733c: fmul dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 47733f: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477345: call 0x49ec14 */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47734a: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47734d: push 1 */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 47734f: lea edx, [esp + 0x54] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 477353: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 477355: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477359: push edx */
	{ long double t = ST(0); FPUSH(t); }	/* 47735a: fld st(0) */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47735c: push eax */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 47735d: lea ecx, [esp + 0x30] */
	ST(0) = -ST(0);	/* 477361: fchs  */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0);	/* 477363: fst dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 477367: fstp dword ptr [esp + 0x34] */
	m->eax = (DWORD)(m->esi + 0x78u);	/* 47736b: lea eax, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47736e: push ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0);	/* 47736f: fst dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x84u));	/* 477373: mov ecx, dword ptr [esp + 0x84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47737a: push eax */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 47737b: fstp dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 47737f: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477383: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 477385: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477389: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47738a: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47738b: push edi */
	m->esp -= 4; M32(m->esp) = 0x477391u; native_call(m, 0x484ca0u);	/* 47738c: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 477391: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 477395: fmul dword ptr [0x4aa438] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 47739b: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47739c: cmp ebx, 0xa */
	M32((DWORD)(m->esp + 0x6cu)) = m->ebx;	/* 47739f: mov dword ptr [esp + 0x6c], ebx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4773a3: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4773a7: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 4773ab: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4773b1: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4773b5: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 4773b9: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4773bf: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4773c3: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 4773c7: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 4773cd: fst dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4773d1: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 4773d5: fmul dword ptr [0x4a94fc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4773db: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 4773df: fmul dword ptr [0x4a94fc] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 4773e5: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4773e9: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 4773ed: fmul dword ptr [0x4a94fc] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 4773f3: fstp dword ptr [esp + 0x64] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 4773f7: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4773fb: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 4773ff: fld dword ptr [esp + 0x60] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 477403: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 477407: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 47740b: fld dword ptr [esp + 0x58] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 47740f: fadd dword ptr [esp + 0x64] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 477413: fstp dword ptr [esp + 0x58] */
	if (m->sf != m->of) goto L_4772e9;	/* 477417: jl 0x4772e9 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47741d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47741e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47741f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 477420: pop ebx */
	ST(0) = ST(0); FPOP();	/* 477421: fstp st(0) */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 477423: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 477426: ret 8 */
L_477429:
	m->edi = M32((DWORD)(m->edi + 0x9ccfe8u));	/* 477429: mov edi, dword ptr [edi + 0x9ccfe8] */
	{ DWORD a_ = m->ebp, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 47742f: and ebp, 0x80000007 */
	if (!m->sf) goto L_47743c;	/* 477435: jns 0x47743c */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 477437: dec ebp */
	{ DWORD a_ = m->ebp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 477438: or ebp, 0xfffffff8 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 47743b: inc ebp */
L_47743c:
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7c8u)));	/* 47743c: fld dword ptr [0xa0e7c8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 477442: fmul dword ptr [0x4a9558] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7ccu)));	/* 477448: fld dword ptr [0xa0e7cc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 47744e: fmul dword ptr [0x4a9558] */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e7d0u)));	/* 477454: fld dword ptr [0xa0e7d0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9558u));	/* 47745a: fmul dword ptr [0x4a9558] */
	{ long double t = ST(0); FPUSH(t); }	/* 477460: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4cu));	/* 477462: fmul dword ptr [esi + 0x4c] */
	{ long double t = ST(2); FPUSH(t); }	/* 477465: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x3cu));	/* 477467: fmul dword ptr [esi + 0x3c] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 47746a: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x6cu)) = m->ebx;	/* 47746c: mov dword ptr [esp + 0x6c], ebx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477470: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 477472: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2cu));	/* 477474: fmul dword ptr [esi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477477: faddp st(1) */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 477479: fstp dword ptr [esp + 0x44] */
	{ long double t = ST(0); FPUSH(t); }	/* 47747d: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x50u));	/* 47747f: fmul dword ptr [esi + 0x50] */
	{ long double t = ST(2); FPUSH(t); }	/* 477482: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x40u));	/* 477484: fmul dword ptr [esi + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 477487: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 477489: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 47748b: fmul dword ptr [esi + 0x30] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47748e: faddp st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 477490: fstp dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x54u));	/* 477494: fmul dword ptr [esi + 0x54] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 477497: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 477499: fmul dword ptr [esi + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47749c: faddp st(1) */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47749e: fxch st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4774a0: fmul dword ptr [esi + 0x34] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4774a3: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x1cu)));	/* 4774a5: fld dword ptr [esi + 0x1c] */
	{ long double t = ST(0); FPUSH(t); }	/* 4774a8: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 4774aa: fmul dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4774ae: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4774b2: fld dword ptr [esp + 0x48] */
	ST(0) = ST(0) * ST(1);	/* 4774b6: fmul st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4774b8: fstp dword ptr [esp + 0x48] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 4774bc: fxch st(1) */
	ST(0) = ST(0) * ST(1);	/* 4774be: fmul st(1) */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4774c0: fstp dword ptr [esp + 0x4c] */
	ST(0) = ST(0); FPOP();	/* 4774c4: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4774c6: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 4774ca: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4774ce: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 4774d2: fmul dword ptr [esp + 0x4c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4774d6: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4774d8: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 4774dc: fmul dword ptr [esp + 0x48] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4774e0: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 4774e2: fsqrt  */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 4774e4: fst dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4774e8: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 4774ec: fadd dword ptr [esi + 0x10] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4774ef: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4774f3: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4774f7: fadd dword ptr [esi + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 4774fa: mov ecx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x50u)) = m->ecx;	/* 4774fe: mov dword ptr [esp + 0x50], ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 477502: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 477506: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 47750a: fadd dword ptr [esi + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 47750d: mov edx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 477511: mov dword ptr [esp + 0x54], edx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 477515: fstp dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 477519: mov eax, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 47751d: mov dword ptr [esp + 0x58], eax */
L_477521:
	m->ecx = (DWORD)(m->ebx + m->ebp*1 + 0x0u);	/* 477521: lea ecx, [ebx + ebp] */
	{ DWORD a_ = m->ecx, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 477524: and ecx, 0x80000007 */
	if (!m->sf) goto L_477531;	/* 47752a: jns 0x477531 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 47752c: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47752d: or ecx, 0xfffffff8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 477530: inc ecx */
L_477531:
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 477531: shl ecx, 5 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 477534: mov dword ptr [esp + 0x1c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e800000u;	/* 477538: mov dword ptr [esp + 0x34], 0x3e800000 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 477540: fild dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3ec00000u;	/* 477544: mov dword ptr [esp + 0x3c], 0x3ec00000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 47754c: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 477552: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 477556: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 47755a: fadd dword ptr [0x4aa274] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 477560: fstp dword ptr [esp + 0x38] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 477564: fild dword ptr [esp + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a955cu));	/* 477568: fmul dword ptr [0x4a955c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47756e: fsubr dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 477574: fmul dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 477577: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47757d: call 0x49ec14 */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477582: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477585: push 1 */
	m->edx = (DWORD)(m->esp + 0x54u);	/* 477587: lea edx, [esp + 0x54] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47758b: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 47758d: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477591: push edx */
	{ long double t = ST(0); FPUSH(t); }	/* 477592: fld st(0) */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477594: push eax */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 477595: lea ecx, [esp + 0x30] */
	ST(0) = -ST(0);	/* 477599: fchs  */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0);	/* 47759b: fst dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47759f: fstp dword ptr [esp + 0x34] */
	m->eax = (DWORD)(m->esi + 0x78u);	/* 4775a3: lea eax, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4775a6: push ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0);	/* 4775a7: fst dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x84u));	/* 4775ab: mov ecx, dword ptr [esp + 0x84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4775b2: push eax */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4775b3: fstp dword ptr [esp + 0x44] */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 4775b7: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4775bb: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 4775bd: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4775c1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4775c2: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4775c3: push edi */
	m->esp -= 4; M32(m->esp) = 0x4775c9u; native_call(m, 0x484ca0u);	/* 4775c4: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4775c9: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 4775cd: fmul dword ptr [0x4aa438] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4775d3: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4775d4: cmp ebx, 0xa */
	M32((DWORD)(m->esp + 0x6cu)) = m->ebx;	/* 4775d7: mov dword ptr [esp + 0x6c], ebx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4775db: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4775df: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 4775e3: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4775e9: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 4775ed: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 4775f1: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 4775f7: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4775fb: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa438u));	/* 4775ff: fmul dword ptr [0x4aa438] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 477605: fst dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 477609: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 47760d: fmul dword ptr [0x4a94fc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 477613: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 477617: fmul dword ptr [0x4a94fc] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 47761d: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 477621: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 477625: fmul dword ptr [0x4a94fc] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 47762b: fstp dword ptr [esp + 0x64] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47762f: fadd dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 477633: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x60u)));	/* 477637: fld dword ptr [esp + 0x60] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x54u));	/* 47763b: fadd dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 47763f: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 477643: fld dword ptr [esp + 0x58] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x64u));	/* 477647: fadd dword ptr [esp + 0x64] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 47764b: fstp dword ptr [esp + 0x58] */
	if (m->sf != m->of) goto L_477521;	/* 47764f: jl 0x477521 */
	m->edi = M32(m->esp); m->esp += 4;	/* 477655: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 477656: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 477657: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 477658: pop ebx */
	ST(0) = ST(0); FPOP();	/* 477659: fstp st(0) */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47765b: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 47765e: ret 8 */
L_477661:
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 477661: mov eax, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477664: test eax, eax */
	if (!m->zf) goto L_477670;	/* 477666: jne 0x477670 */
	m->edi = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477668: mov edi, dword ptr [edi + 0x9ccfd4] */
	goto L_477676;	/* 47766e: jmp 0x477676 */
L_477670:
	m->edi = M32((DWORD)(m->edi + 0x9ccfe4u));	/* 477670: mov edi, dword ptr [edi + 0x9ccfe4] */
L_477676:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 477676: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 47767a: fmul dword ptr [0x4a94cc] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477680: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477685: cmp eax, 7 */
	if (m->zf || m->sf != m->of) goto L_47768f;	/* 477688: jle 0x47768f */
	m->eax = 0x7u;	/* 47768a: mov eax, 7 */
L_47768f:
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47768f: shl eax, 5 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 477692: mov dword ptr [esp + 0x6c], eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477696: push 1 */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x70u)));	/* 477698: fild dword ptr [esp + 0x70] */
	m->ecx = (DWORD)(m->esi + 0x10u);	/* 47769c: lea ecx, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47769f: push 2 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 4776a1: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4776a5: push ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4776a6: fmul dword ptr [0x4a957c] */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 4776ac: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4776b0: push edx */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4776b1: add esi, 0x78 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4776b4: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4776b5: push esi */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 4776b6: lea ecx, [esp + 0x50] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4776ba: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4776be: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 4776c2: fadd dword ptr [0x4aa274] */
	{ DWORD v_ = 0x43960000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4776c8: push 0x43960000 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 4776cd: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4776d1: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 4776d2: mov ecx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4776d9: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4776da: push edi */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 4776db: fstp dword ptr [esp + 0x60] */
	M32((DWORD)(m->esp + 0x5cu)) = 0x3f200000u;	/* 4776df: mov dword ptr [esp + 0x5c], 0x3f200000 */
	M32((DWORD)(m->esp + 0x64u)) = 0x3f400000u;	/* 4776e7: mov dword ptr [esp + 0x64], 0x3f400000 */
	M32((DWORD)(m->esp + 0x48u)) = 0xc3960000u;	/* 4776ef: mov dword ptr [esp + 0x48], 0xc3960000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc3960000u;	/* 4776f7: mov dword ptr [esp + 0x4c], 0xc3960000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x43960000u;	/* 4776ff: mov dword ptr [esp + 0x50], 0x43960000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x43960000u;	/* 477707: mov dword ptr [esp + 0x54], 0x43960000 */
	m->esp -= 4; M32(m->esp) = 0x477714u; native_call(m, 0x484ca0u);	/* 47770f: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 477714: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 477715: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 477716: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 477717: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 477718: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 47771b: ret 8 */
L_47771e:
	m->eax = m->ebp;	/* 47771e: mov eax, ebp */
	m->ecx = 0x5u;	/* 477720: mov ecx, 5 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 477725: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 477726: idiv ecx */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477728: cmp edx, 3 */
	if (!m->cf && !m->zf) goto L_47779c;	/* 47772b: ja 0x47779c */
	switch (m->edx) { case 0: goto L_477734; case 1: goto L_47774e; case 2: goto L_477768; case 3: goto L_477782; default: abort(); }	/* 47772d: jmp dword ptr [edx*4 + 0x4798b0] */
L_477734:
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 477734: mov ecx, dword ptr [esi + 0xc] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 477737: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47773a: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47773d: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 47773f: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 477742: lea eax, [ecx + edx*8] */
	m->ecx = (DWORD)(m->edi + m->eax*2 + 0x1561ea0u);	/* 477745: lea ecx, [edi + eax*2 + 0x1561ea0] */
	goto L_4777b4;	/* 47774c: jmp 0x4777b4 */
L_47774e:
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 47774e: mov ecx, dword ptr [esi + 0xc] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 477751: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 477754: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 477757: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 477759: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 47775c: lea eax, [ecx + edx*8] */
	m->ecx = (DWORD)(m->edi + m->eax*2 + 0x1569decu);	/* 47775f: lea ecx, [edi + eax*2 + 0x1569dec] */
	goto L_4777b4;	/* 477766: jmp 0x4777b4 */
L_477768:
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 477768: mov ecx, dword ptr [esi + 0xc] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 47776b: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47776e: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 477771: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 477773: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 477776: lea eax, [ecx + edx*8] */
	m->ecx = (DWORD)(m->edi + m->eax*2 + 0x1571d38u);	/* 477779: lea ecx, [edi + eax*2 + 0x1571d38] */
	goto L_4777b4;	/* 477780: jmp 0x4777b4 */
L_477782:
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 477782: mov ecx, dword ptr [esi + 0xc] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 477785: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 477788: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 47778b: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 47778d: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 477790: lea eax, [ecx + edx*8] */
	m->ecx = (DWORD)(m->edi + m->eax*2 + 0x1581984u);	/* 477793: lea ecx, [edi + eax*2 + 0x1581984] */
	goto L_4777b4;	/* 47779a: jmp 0x4777b4 */
L_47779c:
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 47779c: mov ecx, dword ptr [esi + 0xc] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 47779f: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4777a2: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4777a5: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4777a7: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 4777aa: lea eax, [ecx + edx*8] */
	m->ecx = (DWORD)(m->edi + m->eax*2 + 0x15915d0u);	/* 4777ad: lea ecx, [edi + eax*2 + 0x15915d0] */
L_4777b4:
	m->eax = m->ebp;	/* 4777b4: mov eax, ebp */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4777b6: push 0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4777b8: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ecx + 0x120u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4777b9: idiv dword ptr [ecx + 0x120] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4777bf: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4777c1: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4777c3: push 0 */
	{ DWORD a_ = m->esi, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4777c5: add esi, 0x2c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4777c8: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4777ca: push esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4777cb: push 0 */
	m->eax = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 4777cd: lea eax, [edx + edx*8] */
	m->edx = (DWORD)(m->edx + m->eax*2 + 0x0u);	/* 4777d0: lea edx, [edx + eax*2] */
	m->eax = M32((DWORD)(m->ecx + 0x11cu));	/* 4777d3: mov eax, dword ptr [ecx + 0x11c] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 4777d9: lea ecx, [eax + edx*4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4777dc: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 4777dd: mov ecx, dword ptr [esp + 0x90] */
	m->esp -= 4; M32(m->esp) = 0x4777e9u; native_call(m, 0x4853c0u);	/* 4777e4: call 0x4853c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4777e9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4777ea: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4777eb: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4777ec: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4777ed: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 4777f0: ret 8 */
L_4777f3:
	m->eax = (DWORD)(m->ecx + 0xfffffff6u);	/* 4777f3: lea eax, [ecx - 0xa] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4777f6: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_479840;	/* 4777f9: ja 0x479840 */
	switch (m->eax) { case 0: goto L_477806; case 1: goto L_477901; case 2: goto L_4779d1; case 3: goto L_477b64; case 4: goto L_477cf7; default: abort(); }	/* 4777ff: jmp dword ptr [eax*4 + 0x4798c0] */
L_477806:
	m->eax = M32((DWORD)(m->edi + 0x20f2e74u));	/* 477806: mov eax, dword ptr [edi + 0x20f2e74] */
	m->ebx = M32((DWORD)(m->esp + 0x70u));	/* 47780c: mov ebx, dword ptr [esp + 0x70] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477810: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 477812: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477814: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477816: push 0 */
	m->edx = (DWORD)(m->esi + 0x2cu);	/* 477818: lea edx, [esi + 0x2c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47781b: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47781d: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47781e: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477820: push eax */
	m->ecx = m->ebx;	/* 477821: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x477828u; native_call(m, 0x4853c0u);	/* 477823: call 0x4853c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 477828: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47782e: fsub dword ptr [esp + 0x10] */
	m->ebp = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477832: mov ebp, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 477838: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477840: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 477848: mov dword ptr [esp + 0x38], 0x3f200000 */
	{ long double t = ST(0); FPUSH(t); }	/* 477850: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477852: fmul st(1) */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 477854: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 47785c: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477862: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477867: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477869: fstp st(0) */
	if (m->sf == m->of) goto L_477871;	/* 47786b: jge 0x477871 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47786d: xor eax, eax */
	goto L_47787d;	/* 47786f: jmp 0x47787d */
L_477871:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477871: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_47787d;	/* 477876: jle 0x47787d */
	m->eax = 0xffu;	/* 477878: mov eax, 0xff */
L_47787d:
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 47787d: mov ecx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477880: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 477883: mov eax, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4160000u;	/* 477889: mov dword ptr [esp + 0x20], 0xc4160000 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477891: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4160000u;	/* 477893: mov dword ptr [esp + 0x24], 0xc4160000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44160000u;	/* 47789b: mov dword ptr [esp + 0x28], 0x44160000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44160000u;	/* 4778a3: mov dword ptr [esp + 0x2c], 0x44160000 */
	if (!m->zf) goto L_4778cd;	/* 4778ab: jne 0x4778cd */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3960000u;	/* 4778ad: mov dword ptr [esp + 0x20], 0xc3960000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3960000u;	/* 4778b5: mov dword ptr [esp + 0x24], 0xc3960000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43960000u;	/* 4778bd: mov dword ptr [esp + 0x28], 0x43960000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43960000u;	/* 4778c5: mov dword ptr [esp + 0x2c], 0x43960000 */
L_4778cd:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4778cd: push 1 */
	m->edx = (DWORD)(m->esi + 0x10u);	/* 4778cf: lea edx, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4778d2: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 4778d4: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4778d8: push edx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 4778d9: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4778dd: push eax */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4778de: add esi, 0x78 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4778e1: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4778e2: push esi */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 4778e3: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4778e7: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 4778e9: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4778ed: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4778ee: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4778ef: push ebp */
	m->ecx = m->ebx;	/* 4778f0: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4778f7u; native_call(m, 0x484ca0u);	/* 4778f2: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4778f7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4778f8: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4778f9: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4778fa: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4778fb: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 4778fe: ret 8 */
L_477901:
	m->edx = M32((DWORD)(m->edi + 0x20f2e7cu));	/* 477901: mov edx, dword ptr [edi + 0x20f2e7c] */
	m->ebx = M32((DWORD)(m->esp + 0x70u));	/* 477907: mov ebx, dword ptr [esp + 0x70] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47790b: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 47790d: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47790f: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477911: push 0 */
	m->ecx = (DWORD)(m->esi + 0x2cu);	/* 477913: lea ecx, [esi + 0x2c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477916: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477918: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477919: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47791b: push edx */
	m->ecx = m->ebx;	/* 47791c: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x477923u; native_call(m, 0x4853c0u);	/* 47791e: call 0x4853c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 477923: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 477929: fsub dword ptr [esp + 0x10] */
	m->ebp = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 47792d: mov ebp, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 477933: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 47793b: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 477943: mov dword ptr [esp + 0x38], 0x3f200000 */
	{ long double t = ST(0); FPUSH(t); }	/* 47794b: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47794d: fmul st(1) */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 47794f: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 477957: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47795d: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477962: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477964: fstp st(0) */
	if (m->sf == m->of) goto L_47796c;	/* 477966: jge 0x47796c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477968: xor eax, eax */
	goto L_477978;	/* 47796a: jmp 0x477978 */
L_47796c:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47796c: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477978;	/* 477971: jle 0x477978 */
	m->eax = 0xffu;	/* 477973: mov eax, 0xff */
L_477978:
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477978: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 47797b: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x202e8d8u));	/* 47797e: mov ecx, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4160000u;	/* 477984: mov dword ptr [esp + 0x20], 0xc4160000 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47798c: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4160000u;	/* 47798e: mov dword ptr [esp + 0x24], 0xc4160000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44160000u;	/* 477996: mov dword ptr [esp + 0x28], 0x44160000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44160000u;	/* 47799e: mov dword ptr [esp + 0x2c], 0x44160000 */
	if (!m->zf) goto L_478561;	/* 4779a6: jne 0x478561 */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3960000u;	/* 4779ac: mov dword ptr [esp + 0x20], 0xc3960000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3960000u;	/* 4779b4: mov dword ptr [esp + 0x24], 0xc3960000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43960000u;	/* 4779bc: mov dword ptr [esp + 0x28], 0x43960000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43960000u;	/* 4779c4: mov dword ptr [esp + 0x2c], 0x43960000 */
	goto L_478561;	/* 4779cc: jmp 0x478561 */
L_4779d1:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4779d1: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4779d7: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4779db: mov eax, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f600000u;	/* 4779e1: mov dword ptr [esp + 0x30], 0x3f600000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 4779e9: mov dword ptr [esp + 0x6c], eax */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 4779ed: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 4779f5: mov dword ptr [esp + 0x38], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 4779fd: mov dword ptr [esp + 0x3c], 0x3e800000 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 477a05: fst dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 477a09: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477a0b: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 477a0d: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477a13: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477a18: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477a1a: fstp st(0) */
	if (m->sf == m->of) goto L_477a22;	/* 477a1c: jge 0x477a22 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477a1e: xor eax, eax */
	goto L_477a2e;	/* 477a20: jmp 0x477a2e */
L_477a22:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477a22: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477a2e;	/* 477a27: jle 0x477a2e */
	m->eax = 0xffu;	/* 477a29: mov eax, 0xff */
L_477a2e:
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 477a2e: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477a31: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 477a33: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 477a35: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 477a39: push ebx */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 477a3a: lea edx, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 477a3e: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477a41: push ecx */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477a42: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477a45: push edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 477a46: mov edx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 477a4d: push ebp */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 477a4e: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477a52: push 0 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 477a54: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477a58: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477a59: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 477a5a: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477a61: push edx */
	M32((DWORD)(m->esp + 0x48u)) = 0xc2480000u;	/* 477a62: mov dword ptr [esp + 0x48], 0xc2480000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc2480000u;	/* 477a6a: mov dword ptr [esp + 0x4c], 0xc2480000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x42480000u;	/* 477a72: mov dword ptr [esp + 0x50], 0x42480000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x42480000u;	/* 477a7a: mov dword ptr [esp + 0x54], 0x42480000 */
	m->esp -= 4; M32(m->esp) = 0x477a87u; native_call(m, 0x484ca0u);	/* 477a82: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 477a87: fld dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477a8b: mov eax, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 477a91: mov dword ptr [esp + 0x30], 0x3f000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 477a99: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477a9b: fmul st(1) */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 477a9d: mov dword ptr [esp + 0x6c], eax */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477aa1: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 477aa9: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 477ab1: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 477ab9: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477abf: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477ac4: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477ac6: fstp st(0) */
	if (m->sf == m->of) goto L_477ace;	/* 477ac8: jge 0x477ace */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477aca: xor eax, eax */
	goto L_477ada;	/* 477acc: jmp 0x477ada */
L_477ace:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477ace: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477ada;	/* 477ad3: jle 0x477ada */
	m->eax = 0xffu;	/* 477ad5: mov eax, 0xff */
L_477ada:
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 477ada: mov ecx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477add: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 477ae0: mov eax, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3480000u;	/* 477ae6: mov dword ptr [esp + 0x20], 0xc3480000 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477aee: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3480000u;	/* 477af0: mov dword ptr [esp + 0x24], 0xc3480000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43480000u;	/* 477af8: mov dword ptr [esp + 0x28], 0x43480000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43480000u;	/* 477b00: mov dword ptr [esp + 0x2c], 0x43480000 */
	if (!m->zf) goto L_477b2a;	/* 477b08: jne 0x477b2a */
	M32((DWORD)(m->esp + 0x20u)) = 0xc2c80000u;	/* 477b0a: mov dword ptr [esp + 0x20], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc2c80000u;	/* 477b12: mov dword ptr [esp + 0x24], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x42c80000u;	/* 477b1a: mov dword ptr [esp + 0x28], 0x42c80000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x42c80000u;	/* 477b22: mov dword ptr [esp + 0x2c], 0x42c80000 */
L_477b2a:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477b2a: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 477b2c: push 2 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 477b2e: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 477b32: push ebx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 477b33: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477b37: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477b38: push eax */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 477b39: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 477b40: push ebp */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 477b41: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477b45: push 0 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 477b47: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477b4b: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 477b4c: mov ecx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477b53: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477b54: push eax */
	m->esp -= 4; M32(m->esp) = 0x477b5au; native_call(m, 0x484ca0u);	/* 477b55: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 477b5a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 477b5b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 477b5c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 477b5d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 477b5e: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 477b61: ret 8 */
L_477b64:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 477b64: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 477b6a: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477b6e: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f600000u;	/* 477b74: mov dword ptr [esp + 0x30], 0x3f600000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 477b7c: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477b80: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 477b88: mov dword ptr [esp + 0x38], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 477b90: mov dword ptr [esp + 0x3c], 0x3e800000 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 477b98: fst dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 477b9c: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477b9e: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 477ba0: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477ba6: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477bab: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477bad: fstp st(0) */
	if (m->sf == m->of) goto L_477bb5;	/* 477baf: jge 0x477bb5 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477bb1: xor eax, eax */
	goto L_477bc1;	/* 477bb3: jmp 0x477bc1 */
L_477bb5:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477bb5: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477bc1;	/* 477bba: jle 0x477bc1 */
	m->eax = 0xffu;	/* 477bbc: mov eax, 0xff */
L_477bc1:
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 477bc1: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477bc4: push 1 */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477bc6: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 477bc9: push 2 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 477bcb: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 477bcf: push ebx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 477bd0: lea eax, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 477bd4: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477bd7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477bd8: push eax */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 477bd9: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 477be0: push ebp */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 477be1: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477be5: push 0 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 477be7: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477beb: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 477bec: mov ecx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477bf3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477bf4: push eax */
	M32((DWORD)(m->esp + 0x48u)) = 0xc2c80000u;	/* 477bf5: mov dword ptr [esp + 0x48], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc2c80000u;	/* 477bfd: mov dword ptr [esp + 0x4c], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x42c80000u;	/* 477c05: mov dword ptr [esp + 0x50], 0x42c80000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x42c80000u;	/* 477c0d: mov dword ptr [esp + 0x54], 0x42c80000 */
	m->esp -= 4; M32(m->esp) = 0x477c1au; native_call(m, 0x484ca0u);	/* 477c15: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 477c1a: fld dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477c1e: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 477c24: mov dword ptr [esp + 0x30], 0x3f000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 477c2c: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477c2e: fmul st(1) */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 477c30: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477c34: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 477c3c: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 477c44: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 477c4c: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477c52: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477c57: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477c59: fstp st(0) */
	if (m->sf == m->of) goto L_477c61;	/* 477c5b: jge 0x477c61 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477c5d: xor eax, eax */
	goto L_477c6d;	/* 477c5f: jmp 0x477c6d */
L_477c61:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477c61: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477c6d;	/* 477c66: jle 0x477c6d */
	m->eax = 0xffu;	/* 477c68: mov eax, 0xff */
L_477c6d:
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 477c6d: mov edx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477c70: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 477c73: mov eax, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4160000u;	/* 477c79: mov dword ptr [esp + 0x20], 0xc4160000 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477c81: cmp edx, eax */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4160000u;	/* 477c83: mov dword ptr [esp + 0x24], 0xc4160000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44160000u;	/* 477c8b: mov dword ptr [esp + 0x28], 0x44160000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44160000u;	/* 477c93: mov dword ptr [esp + 0x2c], 0x44160000 */
	if (!m->zf) goto L_477cbd;	/* 477c9b: jne 0x477cbd */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3960000u;	/* 477c9d: mov dword ptr [esp + 0x20], 0xc3960000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3960000u;	/* 477ca5: mov dword ptr [esp + 0x24], 0xc3960000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43960000u;	/* 477cad: mov dword ptr [esp + 0x28], 0x43960000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43960000u;	/* 477cb5: mov dword ptr [esp + 0x2c], 0x43960000 */
L_477cbd:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477cbd: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 477cbf: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 477cc1: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 477cc5: push ebx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 477cc6: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477cca: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477ccb: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x80u));	/* 477ccc: mov ecx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 477cd3: push ebp */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 477cd4: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477cd8: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 477cda: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477cde: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477cdf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477ce0: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 477ce1: mov ecx, dword ptr [esp + 0x98] */
	m->esp -= 4; M32(m->esp) = 0x477cedu; native_call(m, 0x484ca0u);	/* 477ce8: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 477ced: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 477cee: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 477cef: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 477cf0: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 477cf1: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 477cf4: ret 8 */
L_477cf7:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 477cf7: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 477cfd: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477d01: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f600000u;	/* 477d07: mov dword ptr [esp + 0x30], 0x3f600000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 477d0f: mov dword ptr [esp + 0x6c], edx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477d13: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 477d1b: mov dword ptr [esp + 0x38], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 477d23: mov dword ptr [esp + 0x3c], 0x3e800000 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 477d2b: fst dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 477d2f: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477d31: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 477d33: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477d39: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477d3e: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477d40: fstp st(0) */
	if (m->sf == m->of) goto L_477d48;	/* 477d42: jge 0x477d48 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477d44: xor eax, eax */
	goto L_477d54;	/* 477d46: jmp 0x477d54 */
L_477d48:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477d48: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477d54;	/* 477d4d: jle 0x477d54 */
	m->eax = 0xffu;	/* 477d4f: mov eax, 0xff */
L_477d54:
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477d54: mov byte ptr [esi + 0x7b], al */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 477d57: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477d5a: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 477d5c: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 477d5e: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 477d62: push ebx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 477d63: lea ecx, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 477d67: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477d6a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477d6b: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x80u));	/* 477d6c: mov ecx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 477d73: push ebp */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 477d74: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477d78: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 477d7a: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477d7e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477d7f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477d80: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 477d81: mov ecx, dword ptr [esp + 0x98] */
	M32((DWORD)(m->esp + 0x48u)) = 0xc2c80000u;	/* 477d88: mov dword ptr [esp + 0x48], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc2c80000u;	/* 477d90: mov dword ptr [esp + 0x4c], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x42c80000u;	/* 477d98: mov dword ptr [esp + 0x50], 0x42c80000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x42c80000u;	/* 477da0: mov dword ptr [esp + 0x54], 0x42c80000 */
	m->esp -= 4; M32(m->esp) = 0x477dadu; native_call(m, 0x484ca0u);	/* 477da8: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 477dad: fld dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477db1: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 477db7: mov dword ptr [esp + 0x30], 0x3f000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 477dbf: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477dc1: fmul st(1) */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 477dc3: mov dword ptr [esp + 0x6c], edx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477dc7: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 477dcf: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 477dd7: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 477ddf: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477de5: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477dea: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477dec: fstp st(0) */
	if (m->sf == m->of) goto L_477df4;	/* 477dee: jge 0x477df4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477df0: xor eax, eax */
	goto L_477e00;	/* 477df2: jmp 0x477e00 */
L_477df4:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477df4: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477e00;	/* 477df9: jle 0x477e00 */
	m->eax = 0xffu;	/* 477dfb: mov eax, 0xff */
L_477e00:
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477e00: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 477e03: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x202e8d8u));	/* 477e06: mov ecx, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4160000u;	/* 477e0c: mov dword ptr [esp + 0x20], 0xc4160000 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477e14: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4160000u;	/* 477e16: mov dword ptr [esp + 0x24], 0xc4160000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44160000u;	/* 477e1e: mov dword ptr [esp + 0x28], 0x44160000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44160000u;	/* 477e26: mov dword ptr [esp + 0x2c], 0x44160000 */
	if (!m->zf) goto L_477e50;	/* 477e2e: jne 0x477e50 */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3960000u;	/* 477e30: mov dword ptr [esp + 0x20], 0xc3960000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3960000u;	/* 477e38: mov dword ptr [esp + 0x24], 0xc3960000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43960000u;	/* 477e40: mov dword ptr [esp + 0x28], 0x43960000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43960000u;	/* 477e48: mov dword ptr [esp + 0x2c], 0x43960000 */
L_477e50:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477e50: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 477e52: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 477e54: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 477e58: push ebx */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 477e59: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477e5d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477e5e: push edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 477e5f: mov edx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 477e66: push ebp */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 477e67: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477e6b: push 0 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 477e6d: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477e71: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477e72: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 477e73: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477e7a: push edx */
	m->esp -= 4; M32(m->esp) = 0x477e80u; native_call(m, 0x484ca0u);	/* 477e7b: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 477e80: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 477e81: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 477e82: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 477e83: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 477e84: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 477e87: ret 8 */
L_477e8a:
	{ DWORD a_ = m->ecx, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 477e8a: sub ecx, 0xf */
	if (m->zf) goto L_47814b;	/* 477e8d: je 0x47814b */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 477e93: dec ecx */
	if (m->zf) goto L_477f9e;	/* 477e94: je 0x477f9e */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 477e9a: sub ecx, 2 */
	if (!m->zf) goto L_479840;	/* 477e9d: jne 0x479840 */
	m->ecx = M32((DWORD)(m->edi + 0x20f2e80u));	/* 477ea3: mov ecx, dword ptr [edi + 0x20f2e80] */
	m->ebx = M32((DWORD)(m->esp + 0x70u));	/* 477ea9: mov ebx, dword ptr [esp + 0x70] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477ead: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 477eaf: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477eb1: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477eb3: push 0 */
	m->eax = (DWORD)(m->esi + 0x2cu);	/* 477eb5: lea eax, [esi + 0x2c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477eb8: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477eba: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477ebb: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477ebd: push ecx */
	m->ecx = m->ebx;	/* 477ebe: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x477ec5u; native_call(m, 0x4853c0u);	/* 477ec0: call 0x4853c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 477ec5: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 477ecb: fsub dword ptr [esp + 0x10] */
	m->ebp = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477ecf: mov ebp, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 477ed5: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477edd: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 477ee5: mov dword ptr [esp + 0x38], 0x3f200000 */
	{ long double t = ST(0); FPUSH(t); }	/* 477eed: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477eef: fmul st(1) */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 477ef1: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 477ef9: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477eff: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477f04: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477f06: fstp st(0) */
	if (m->sf == m->of) goto L_477f0e;	/* 477f08: jge 0x477f0e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477f0a: xor eax, eax */
	goto L_477f1a;	/* 477f0c: jmp 0x477f1a */
L_477f0e:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477f0e: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477f1a;	/* 477f13: jle 0x477f1a */
	m->eax = 0xffu;	/* 477f15: mov eax, 0xff */
L_477f1a:
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 477f1a: mov edx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477f1d: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 477f20: mov eax, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4160000u;	/* 477f26: mov dword ptr [esp + 0x20], 0xc4160000 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477f2e: cmp edx, eax */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4160000u;	/* 477f30: mov dword ptr [esp + 0x24], 0xc4160000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44160000u;	/* 477f38: mov dword ptr [esp + 0x28], 0x44160000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44160000u;	/* 477f40: mov dword ptr [esp + 0x2c], 0x44160000 */
	if (!m->zf) goto L_477f6a;	/* 477f48: jne 0x477f6a */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3960000u;	/* 477f4a: mov dword ptr [esp + 0x20], 0xc3960000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3960000u;	/* 477f52: mov dword ptr [esp + 0x24], 0xc3960000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43960000u;	/* 477f5a: mov dword ptr [esp + 0x28], 0x43960000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43960000u;	/* 477f62: mov dword ptr [esp + 0x2c], 0x43960000 */
L_477f6a:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 477f6a: push 1 */
	m->eax = (DWORD)(m->esi + 0x10u);	/* 477f6c: lea eax, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 477f6f: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 477f71: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477f75: push eax */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 477f76: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477f7a: push ecx */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 477f7b: add esi, 0x78 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 477f7e: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 477f7f: push esi */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 477f80: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 477f84: push 0 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 477f86: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 477f8a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 477f8b: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 477f8c: push ebp */
	m->ecx = m->ebx;	/* 477f8d: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x477f94u; native_call(m, 0x484ca0u);	/* 477f8f: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 477f94: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 477f95: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 477f96: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 477f97: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 477f98: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 477f9b: ret 8 */
L_477f9e:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 477f9e: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 477fa4: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 477fa8: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 477fae: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 477fb6: mov dword ptr [esp + 0x6c], edx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 477fba: mov dword ptr [esp + 0x34], 0x3e000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 477fc2: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 477fc4: fmul st(1) */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 477fc6: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 477fce: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 477fd6: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 477fdc: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 477fe1: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 477fe3: fstp st(0) */
	if (m->sf == m->of) goto L_477feb;	/* 477fe5: jge 0x477feb */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 477fe7: xor eax, eax */
	goto L_477ff7;	/* 477fe9: jmp 0x477ff7 */
L_477feb:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 477feb: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_477ff7;	/* 477ff0: jle 0x477ff7 */
	m->eax = 0xffu;	/* 477ff2: mov eax, 0xff */
L_477ff7:
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 477ff7: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 477ffa: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x202e8d8u));	/* 477ffd: mov ecx, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4160000u;	/* 478003: mov dword ptr [esp + 0x20], 0xc4160000 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47800b: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4160000u;	/* 47800d: mov dword ptr [esp + 0x24], 0xc4160000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44160000u;	/* 478015: mov dword ptr [esp + 0x28], 0x44160000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44160000u;	/* 47801d: mov dword ptr [esp + 0x2c], 0x44160000 */
	if (!m->zf) goto L_478047;	/* 478025: jne 0x478047 */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3960000u;	/* 478027: mov dword ptr [esp + 0x20], 0xc3960000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3960000u;	/* 47802f: mov dword ptr [esp + 0x24], 0xc3960000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43960000u;	/* 478037: mov dword ptr [esp + 0x28], 0x43960000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43960000u;	/* 47803f: mov dword ptr [esp + 0x2c], 0x43960000 */
L_478047:
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 478047: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47804a: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47804c: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 47804e: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 478052: push ebx */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 478053: lea edx, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 478057: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47805a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47805b: push edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 47805c: mov edx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478063: push ebp */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 478064: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478068: push 0 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 47806a: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47806e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47806f: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 478070: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478077: push edx */
	m->esp -= 4; M32(m->esp) = 0x47807du; native_call(m, 0x484ca0u);	/* 478078: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47807d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 478081: fmul dword ptr [0x4a94cc] */
	m->edi = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478087: mov edi, dword ptr [edi + 0x9ccfd4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47808d: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478092: cmp eax, 7 */
	if (m->zf || m->sf != m->of) goto L_47809c;	/* 478095: jle 0x47809c */
	m->eax = 0x7u;	/* 478097: mov eax, 7 */
L_47809c:
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47809c: shl eax, 4 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 47809f: mov dword ptr [esp + 0x6c], eax */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 4780a3: mov eax, dword ptr [ebx] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 4780a5: fild dword ptr [esp + 0x6c] */
	m->ecx = M32((DWORD)(m->ebx + 0x4u));	/* 4780a9: mov ecx, dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->ebx + 0x8u));	/* 4780ac: mov edx, dword ptr [ebx + 8] */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 4780af: mov dword ptr [esp + 0x50], eax */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 4780b3: mov dword ptr [esp + 0x54], ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 4780b7: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4780bd: push 1 */
	m->eax = (DWORD)(m->esp + 0x54u);	/* 4780bf: lea eax, [esp + 0x54] */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 4780c3: mov dword ptr [esp + 0x5c], edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4780c7: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 4780c9: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4780cd: push eax */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4780ce: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4780d2: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 4780d6: fadd dword ptr [0x4a958c] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 4780dc: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4780e0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4780e1: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4780e2: push ebp */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4780e3: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 4780e7: fld dword ptr [esi + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 4780ea: fmul dword ptr [0x4a93f4] */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 4780f0: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4780f4: push 0 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 4780f6: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4780fa: push eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x74u));	/* 4780fb: fadd dword ptr [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4780ff: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 478100: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 478107: push edi */
	M32((DWORD)(m->esp + 0x5cu)) = 0x3f700000u;	/* 478108: mov dword ptr [esp + 0x5c], 0x3f700000 */
	M32((DWORD)(m->esp + 0x64u)) = 0x3f800000u;	/* 478110: mov dword ptr [esp + 0x64], 0x3f800000 */
	M32((DWORD)(m->esp + 0x48u)) = 0xc2c80000u;	/* 478118: mov dword ptr [esp + 0x48], 0xc2c80000 */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0); FPOP();	/* 478120: fstp dword ptr [esp + 0x7c] */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc2c80000u;	/* 478124: mov dword ptr [esp + 0x4c], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x42c80000u;	/* 47812c: mov dword ptr [esp + 0x50], 0x42c80000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x42c80000u;	/* 478134: mov dword ptr [esp + 0x54], 0x42c80000 */
	m->esp -= 4; M32(m->esp) = 0x478141u; native_call(m, 0x484ca0u);	/* 47813c: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 478141: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 478142: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 478143: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 478144: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 478145: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 478148: ret 8 */
L_47814b:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 47814b: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 478151: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478155: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 47815b: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 478163: mov dword ptr [esp + 0x6c], edx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 478167: mov dword ptr [esp + 0x34], 0x3e000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 47816f: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 478171: fmul st(1) */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 478173: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 47817b: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 478183: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478189: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47818e: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 478190: fstp st(0) */
	if (m->sf == m->of) goto L_478198;	/* 478192: jge 0x478198 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478194: xor eax, eax */
	goto L_4781a4;	/* 478196: jmp 0x4781a4 */
L_478198:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478198: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_4781a4;	/* 47819d: jle 0x4781a4 */
	m->eax = 0xffu;	/* 47819f: mov eax, 0xff */
L_4781a4:
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4781a4: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 4781a7: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x202e8d8u));	/* 4781aa: mov ecx, dword ptr [edi + 0x202e8d8] */
	M32((DWORD)(m->esp + 0x20u)) = 0xc4160000u;	/* 4781b0: mov dword ptr [esp + 0x20], 0xc4160000 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4781b8: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = 0xc4160000u;	/* 4781ba: mov dword ptr [esp + 0x24], 0xc4160000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x44160000u;	/* 4781c2: mov dword ptr [esp + 0x28], 0x44160000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x44160000u;	/* 4781ca: mov dword ptr [esp + 0x2c], 0x44160000 */
	if (!m->zf) goto L_4781f4;	/* 4781d2: jne 0x4781f4 */
	M32((DWORD)(m->esp + 0x20u)) = 0xc3960000u;	/* 4781d4: mov dword ptr [esp + 0x20], 0xc3960000 */
	M32((DWORD)(m->esp + 0x24u)) = 0xc3960000u;	/* 4781dc: mov dword ptr [esp + 0x24], 0xc3960000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x43960000u;	/* 4781e4: mov dword ptr [esp + 0x28], 0x43960000 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x43960000u;	/* 4781ec: mov dword ptr [esp + 0x2c], 0x43960000 */
L_4781f4:
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 4781f4: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4781f7: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4781f9: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 4781fb: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4781ff: push ebx */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 478200: lea edx, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 478204: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478207: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478208: push edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 478209: mov edx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478210: push ebp */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 478211: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478215: push 0 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 478217: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47821b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47821c: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 47821d: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478224: push edx */
	m->esp -= 4; M32(m->esp) = 0x47822au; native_call(m, 0x484ca0u);	/* 478225: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47822a: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 47822e: fmul dword ptr [0x4a94cc] */
	m->edi = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478234: mov edi, dword ptr [edi + 0x9ccfd4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47823a: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47823f: cmp eax, 7 */
	if (m->zf || m->sf != m->of) goto L_478249;	/* 478242: jle 0x478249 */
	m->eax = 0x7u;	/* 478244: mov eax, 7 */
L_478249:
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 478249: shl eax, 4 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 47824c: mov dword ptr [esp + 0x6c], eax */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 478250: mov eax, dword ptr [ebx] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x6cu)));	/* 478252: fild dword ptr [esp + 0x6c] */
	m->ecx = M32((DWORD)(m->ebx + 0x4u));	/* 478256: mov ecx, dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->ebx + 0x8u));	/* 478259: mov edx, dword ptr [ebx + 8] */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 47825c: mov dword ptr [esp + 0x50], eax */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 478260: mov dword ptr [esp + 0x54], ecx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 478264: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47826a: push 1 */
	m->eax = (DWORD)(m->esp + 0x54u);	/* 47826c: lea eax, [esp + 0x54] */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 478270: mov dword ptr [esp + 0x5c], edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 478274: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 478276: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47827a: push eax */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 47827b: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47827f: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 478283: fadd dword ptr [0x4a958c] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 478289: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47828d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47828e: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47828f: push ebp */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 478290: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 478294: fld dword ptr [esi + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 478297: fmul dword ptr [0x4a93f4] */
	M32((DWORD)(m->esp + 0x4cu)) = 0x3f700000u;	/* 47829d: mov dword ptr [esp + 0x4c], 0x3f700000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x3f800000u;	/* 4782a5: mov dword ptr [esp + 0x54], 0x3f800000 */
	M32((DWORD)(m->esp + 0x38u)) = 0xc2c80000u;	/* 4782ad: mov dword ptr [esp + 0x38], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0xc2c80000u;	/* 4782b5: mov dword ptr [esp + 0x3c], 0xc2c80000 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x6cu));	/* 4782bd: fadd dword ptr [esp + 0x6c] */
	M32((DWORD)(m->esp + 0x40u)) = 0x42c80000u;	/* 4782c1: mov dword ptr [esp + 0x40], 0x42c80000 */
	M32((DWORD)(m->esp + 0x44u)) = 0x42c80000u;	/* 4782c9: mov dword ptr [esp + 0x44], 0x42c80000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4782d1: push 0 */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 4782d3: fstp dword ptr [esp + 0x70] */
L_4782d7:
	m->eax = (DWORD)(m->esp + 0x54u);	/* 4782d7: lea eax, [esp + 0x54] */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 4782db: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4782df: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4782e0: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 4782e1: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4782e8: push edi */
	m->esp -= 4; M32(m->esp) = 0x4782eeu; native_call(m, 0x484ca0u);	/* 4782e9: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4782ee: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4782ef: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4782f0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4782f1: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4782f2: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 4782f5: ret 8 */
L_4782f8:
	m->eax = (DWORD)(m->ecx + 0xffffffecu);	/* 4782f8: lea eax, [ecx - 0x14] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4782fb: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_479840;	/* 4782fe: ja 0x479840 */
	switch (m->eax) { case 0: goto L_47830b; case 1: goto L_47834b; case 2: goto L_47838b; case 3: goto L_479840; case 4: goto L_478414; default: abort(); }	/* 478304: jmp dword ptr [eax*4 + 0x4798d4] */
L_47830b:
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 47830b: mov edx, dword ptr [esi + 0xc] */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 47830e: mov eax, dword ptr [edi + 0x202e8d8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478314: cmp edx, eax */
	if (m->zf) goto L_479840;	/* 478316: je 0x479840 */
	m->ecx = M32((DWORD)(m->edi + 0x20f2e78u));	/* 47831c: mov ecx, dword ptr [edi + 0x20f2e78] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478322: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 478324: push -1 */
	m->eax = (DWORD)(m->esi + 0x78u);	/* 478326: lea eax, [esi + 0x78] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478329: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47832b: push eax */
	{ DWORD a_ = m->esi, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 47832c: add esi, 0x2c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47832f: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 478331: push esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478332: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478334: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 478335: mov ecx, dword ptr [esp + 0x90] */
	m->esp -= 4; M32(m->esp) = 0x478341u; native_call(m, 0x4853c0u);	/* 47833c: call 0x4853c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 478341: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 478342: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 478343: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 478344: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 478345: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 478348: ret 8 */
L_47834b:
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 47834b: mov edx, dword ptr [esi + 0xc] */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 47834e: mov eax, dword ptr [edi + 0x202e8d8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478354: cmp edx, eax */
	if (m->zf) goto L_479840;	/* 478356: je 0x479840 */
	m->ecx = M32((DWORD)(m->edi + 0x20f2e84u));	/* 47835c: mov ecx, dword ptr [edi + 0x20f2e84] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478362: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 478364: push -1 */
	m->eax = (DWORD)(m->esi + 0x78u);	/* 478366: lea eax, [esi + 0x78] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478369: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47836b: push eax */
	{ DWORD a_ = m->esi, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 47836c: add esi, 0x2c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47836f: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 478371: push esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478372: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478374: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 478375: mov ecx, dword ptr [esp + 0x90] */
	m->esp -= 4; M32(m->esp) = 0x478381u; native_call(m, 0x4853c0u);	/* 47837c: call 0x4853c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 478381: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 478382: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 478383: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 478384: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 478385: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 478388: ret 8 */
L_47838b:
	{ DWORD a_ = M32((DWORD)(m->esi + 0xcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47838b: cmp dword ptr [esi + 0xc], 1 */
	if (m->zf) goto L_479840;	/* 47838f: je 0x479840 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478395: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 47839b: fadd dword ptr [0x4a93f4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4783a1: push 1 */
	m->edx = (DWORD)(m->esi + 0x10u);	/* 4783a3: lea edx, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4783a6: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 4783a8: lea eax, [esp + 0x30] */
	{ long double t = ST(0); FPUSH(t); }	/* 4783ac: fld st(0) */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4783ae: push edx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 4783af: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4783b3: push eax */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4783b4: add esi, 0x78 */
	ST(0) = -ST(0);	/* 4783b7: fchs  */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0);	/* 4783b9: fst dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 4783bd: fstp dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4783c1: push ecx */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4783c2: mov ecx, dword ptr [edi + 0x9ccfd4] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0);	/* 4783c8: fst dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4783cc: fstp dword ptr [esp + 0x40] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4783d0: push esi */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 4783d1: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4783d5: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 4783d7: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4783db: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4783dc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4783dd: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 4783de: mov ecx, dword ptr [esp + 0x98] */
	M32((DWORD)(m->esp + 0x58u)) = 0x3f600000u;	/* 4783e5: mov dword ptr [esp + 0x58], 0x3f600000 */
	M32((DWORD)(m->esp + 0x5cu)) = 0x3e800000u;	/* 4783ed: mov dword ptr [esp + 0x5c], 0x3e800000 */
	M32((DWORD)(m->esp + 0x60u)) = 0x3f800000u;	/* 4783f5: mov dword ptr [esp + 0x60], 0x3f800000 */
	M32((DWORD)(m->esp + 0x64u)) = 0x3ec00000u;	/* 4783fd: mov dword ptr [esp + 0x64], 0x3ec00000 */
	m->esp -= 4; M32(m->esp) = 0x47840au; native_call(m, 0x484ca0u);	/* 478405: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47840a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47840b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47840c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47840d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47840e: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 478411: ret 8 */
L_478414:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 478414: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47841a: fsub dword ptr [esp + 0x10] */
	{ long double t = ST(0); FPUSH(t); }	/* 47841e: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 478420: fmul st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 478422: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478428: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47842d: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 47842f: fstp st(0) */
	if (m->sf == m->of) goto L_478437;	/* 478431: jge 0x478437 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478433: xor eax, eax */
	goto L_478443;	/* 478435: jmp 0x478443 */
L_478437:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478437: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478443;	/* 47843c: jle 0x478443 */
	m->eax = 0xffu;	/* 47843e: mov eax, 0xff */
L_478443:
	m->ecx = M32((DWORD)(m->esp + 0x70u));	/* 478443: mov ecx, dword ptr [esp + 0x70] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478447: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 478449: push -1 */
	m->edx = (DWORD)(m->esi + 0x78u);	/* 47844b: lea edx, [esi + 0x78] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47844e: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x20f2e88u));	/* 478451: mov eax, dword ptr [edi + 0x20f2e88] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478457: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478459: push edx */
	{ DWORD a_ = m->esi, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 47845a: add esi, 0x2c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47845d: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47845f: push esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478460: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478462: push eax */
	m->esp -= 4; M32(m->esp) = 0x478468u; native_call(m, 0x4853c0u);	/* 478463: call 0x4853c0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 478468: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 478469: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47846a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47846b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47846c: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 47846f: ret 8 */
L_478472:
	{ DWORD a_ = m->ecx, b_ = 0x19u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 478472: sub ecx, 0x19 */
	if (m->zf) goto L_478595;	/* 478475: je 0x478595 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 47847b: dec ecx */
	if (!m->zf) goto L_479840;	/* 47847c: jne 0x479840 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478482: cmp dword ptr [esi + 0xc], 1 */
	if (m->zf) goto L_479840;	/* 478486: je 0x479840 */
	m->edx = M32((DWORD)(m->edi + 0x20f2e90u));	/* 47848c: mov edx, dword ptr [edi + 0x20f2e90] */
	m->ebx = M32((DWORD)(m->esp + 0x70u));	/* 478492: mov ebx, dword ptr [esp + 0x70] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478496: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 478498: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47849a: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47849c: push 0 */
	m->ecx = (DWORD)(m->esi + 0x2cu);	/* 47849e: lea ecx, [esi + 0x2c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4784a1: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4784a3: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4784a4: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4784a6: push edx */
	m->ecx = m->ebx;	/* 4784a7: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4784aeu; native_call(m, 0x4853c0u);	/* 4784a9: call 0x4853c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4784ae: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4784b4: fsub dword ptr [esp + 0x10] */
	m->ebp = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4784b8: mov ebp, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 4784be: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 4784c6: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 4784ce: mov dword ptr [esp + 0x38], 0x3f200000 */
	{ long double t = ST(0); FPUSH(t); }	/* 4784d6: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4784d8: fmul st(1) */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 4784da: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 4784e2: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4784e8: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4784ed: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 4784ef: fstp st(0) */
	if (m->sf == m->of) goto L_4784f7;	/* 4784f1: jge 0x4784f7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4784f3: xor eax, eax */
	goto L_478503;	/* 4784f5: jmp 0x478503 */
L_4784f7:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4784f7: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478503;	/* 4784fc: jle 0x478503 */
	m->eax = 0xffu;	/* 4784fe: mov eax, 0xff */
L_478503:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478503: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9450u));	/* 478509: fadd dword ptr [0x4a9450] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47850f: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 478512: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x202e8d8u));	/* 478515: mov ecx, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 47851b: fld st(0) */
	ST(0) = -ST(0);	/* 47851d: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 47851f: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478523: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478527: cmp eax, ecx */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478529: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 47852d: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_47855f;	/* 478531: jne 0x47855f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 478533: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478537: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47853d: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 478541: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478545: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47854b: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 47854f: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478555: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 478559: fstp dword ptr [esp + 0x2c] */
	goto L_478561;	/* 47855d: jmp 0x478561 */
L_47855f:
	ST(0) = ST(0); FPOP();	/* 47855f: fstp st(0) */
L_478561:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 478561: push 1 */
	m->ecx = (DWORD)(m->esi + 0x10u);	/* 478563: lea ecx, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 478566: push 2 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 478568: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47856c: push ecx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 47856d: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478571: push edx */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 478572: add esi, 0x78 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478575: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 478576: push esi */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 478577: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47857b: push 0 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 47857d: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478581: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478582: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478583: push ebp */
	m->ecx = m->ebx;	/* 478584: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x47858bu; native_call(m, 0x484ca0u);	/* 478586: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47858b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47858c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47858d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47858e: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47858f: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 478592: ret 8 */
L_478595:
	{ DWORD a_ = M32((DWORD)(m->esi + 0xcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478595: cmp dword ptr [esi + 0xc], 1 */
	if (m->zf) goto L_479840;	/* 478599: je 0x479840 */
	m->ecx = M32((DWORD)(m->edi + 0x20f2e8cu));	/* 47859f: mov ecx, dword ptr [edi + 0x20f2e8c] */
	m->ebx = M32((DWORD)(m->esp + 0x70u));	/* 4785a5: mov ebx, dword ptr [esp + 0x70] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4785a9: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4785ab: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4785ad: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4785af: push 0 */
	m->eax = (DWORD)(m->esi + 0x2cu);	/* 4785b1: lea eax, [esi + 0x2c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4785b4: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4785b6: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4785b7: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4785b9: push ecx */
	m->ecx = m->ebx;	/* 4785ba: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x4785c1u; native_call(m, 0x4853c0u);	/* 4785bc: call 0x4853c0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4785c1: push 1 */
	m->edx = (DWORD)(m->esi + 0x10u);	/* 4785c3: lea edx, [esi + 0x10] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4785c6: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 4785c8: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4785cc: push edx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 4785cd: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4785d1: push eax */
	{ DWORD a_ = m->esi, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4785d2: add esi, 0x78 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4785d5: push ecx */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4785d6: mov ecx, dword ptr [edi + 0x9ccfd4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4785dc: push esi */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 4785dd: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4785e1: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 4785e3: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4785e7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4785e8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4785e9: push ecx */
	m->ecx = m->ebx;	/* 4785ea: mov ecx, ebx */
	M32((DWORD)(m->esp + 0x58u)) = 0x3f000000u;	/* 4785ec: mov dword ptr [esp + 0x58], 0x3f000000 */
	M32((DWORD)(m->esp + 0x5cu)) = 0x3e000000u;	/* 4785f4: mov dword ptr [esp + 0x5c], 0x3e000000 */
	M32((DWORD)(m->esp + 0x60u)) = 0x3f200000u;	/* 4785fc: mov dword ptr [esp + 0x60], 0x3f200000 */
	M32((DWORD)(m->esp + 0x64u)) = 0x3e800000u;	/* 478604: mov dword ptr [esp + 0x64], 0x3e800000 */
	M32((DWORD)(m->esp + 0x48u)) = 0xc3fa0000u;	/* 47860c: mov dword ptr [esp + 0x48], 0xc3fa0000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc3fa0000u;	/* 478614: mov dword ptr [esp + 0x4c], 0xc3fa0000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x43fa0000u;	/* 47861c: mov dword ptr [esp + 0x50], 0x43fa0000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x43fa0000u;	/* 478624: mov dword ptr [esp + 0x54], 0x43fa0000 */
	m->esp -= 4; M32(m->esp) = 0x478631u; native_call(m, 0x484ca0u);	/* 47862c: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 478631: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 478632: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 478633: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 478634: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 478635: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 478638: ret 8 */
L_47863b:
	m->eax = (DWORD)(m->ecx + 0xffffffe2u);	/* 47863b: lea eax, [ecx - 0x1e] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47863e: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_479840;	/* 478641: ja 0x479840 */
	switch (m->eax) { case 0: goto L_47864e; case 1: goto L_4787e9; case 2: goto L_478984; case 3: goto L_478afb; case 4: goto L_478c72; default: abort(); }	/* 478647: jmp dword ptr [eax*4 + 0x4798e8] */
L_47864e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47864e: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 478652: fmul dword ptr [0x4a94cc] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478658: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 47865e: mov dword ptr [esp + 0x6c], edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478662: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478667: cmp eax, 7 */
	if (m->zf || m->sf != m->of) goto L_478671;	/* 47866a: jle 0x478671 */
	m->eax = 0x7u;	/* 47866c: mov eax, 7 */
L_478671:
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 478671: shl eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 478674: mov dword ptr [esp + 0x1c], eax */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 478678: lea ebx, [esi + 0x10] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 47867b: fild dword ptr [esp + 0x1c] */
	m->eax = m->ebx;	/* 47867f: mov eax, ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 478681: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 478683: push 2 */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 478685: lea ebp, [esi + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 478688: fmul dword ptr [0x4a957c] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47868e: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f700000u;	/* 478690: mov dword ptr [esp + 0x3c], 0x3f700000 */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 478698: mov dword ptr [esp + 0x58], ecx */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 47869c: lea ecx, [esp + 0x58] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 4786a0: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4786a3: push ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4786a4: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4786a8: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 4786ac: fadd dword ptr [0x4a958c] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 4786b2: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x60u)) = m->edx;	/* 4786b5: mov dword ptr [esp + 0x60], edx */
	M32((DWORD)(m->esp + 0x64u)) = m->eax;	/* 4786b9: mov dword ptr [esp + 0x64], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 4786bd: lea edx, [esp + 0x34] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4786c1: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4786c5: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 4786c9: fmul dword ptr [0x4a93f4] */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 4786cf: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4786d3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4786d4: push eax */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 4786d5: mov eax, dword ptr [esp + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x68u));	/* 4786dc: fadd dword ptr [esp + 0x68] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4786e0: push ebp */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 4786e1: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x42c80000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4786e5: push 0x42c80000 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 4786ea: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4786ee: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 4786ef: mov ecx, dword ptr [esp + 0x90] */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 4786f6: fstp dword ptr [esp + 0x74] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4786fa: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4786fb: push eax */
	M32((DWORD)(m->esp + 0x64u)) = 0x3f800000u;	/* 4786fc: mov dword ptr [esp + 0x64], 0x3f800000 */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(0xffu);	/* 478704: mov byte ptr [esi + 0x7b], 0xff */
	M32((DWORD)(m->esp + 0x48u)) = 0xc2c80000u;	/* 478708: mov dword ptr [esp + 0x48], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc2c80000u;	/* 478710: mov dword ptr [esp + 0x4c], 0xc2c80000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x42c80000u;	/* 478718: mov dword ptr [esp + 0x50], 0x42c80000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x42c80000u;	/* 478720: mov dword ptr [esp + 0x54], 0x42c80000 */
	m->esp -= 4; M32(m->esp) = 0x47872du; native_call(m, 0x484ca0u);	/* 478728: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 47872d: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 478733: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478737: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 47873d: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 478745: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 478749: mov dword ptr [esp + 0x34], 0x3e000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 478751: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 478753: fmul st(1) */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 478755: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 47875d: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 478765: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47876b: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 478770: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 478772: fstp st(0) */
	if (m->sf == m->of) goto L_47877a;	/* 478774: jge 0x47877a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478776: xor eax, eax */
	goto L_478786;	/* 478778: jmp 0x478786 */
L_47877a:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47877a: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478786;	/* 47877f: jle 0x478786 */
	m->eax = 0xffu;	/* 478781: mov eax, 0xff */
L_478786:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478786: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93fcu));	/* 47878c: fadd dword ptr [0x4a93fc] */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 478792: mov edx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 478795: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 478798: mov eax, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 47879e: fld st(0) */
	ST(0) = -ST(0);	/* 4787a0: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 4787a2: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4787a6: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4787aa: cmp edx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 4787ac: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 4787b0: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_478f8f;	/* 4787b4: jne 0x478f8f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4787ba: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4787be: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4787c4: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4787c8: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4787cc: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4787d2: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4787d6: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 4787dc: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4787e0: fstp dword ptr [esp + 0x2c] */
	goto L_478f91;	/* 4787e4: jmp 0x478f91 */
L_4787e9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4787e9: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 4787ed: fmul dword ptr [0x4a94cc] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4787f3: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 4787f9: mov dword ptr [esp + 0x6c], edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4787fd: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478802: cmp eax, 7 */
	if (m->zf || m->sf != m->of) goto L_47880c;	/* 478805: jle 0x47880c */
	m->eax = 0x7u;	/* 478807: mov eax, 7 */
L_47880c:
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47880c: shl eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47880f: mov dword ptr [esp + 0x1c], eax */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 478813: lea ebx, [esi + 0x10] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 478816: fild dword ptr [esp + 0x1c] */
	m->eax = m->ebx;	/* 47881a: mov eax, ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47881c: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47881e: push 2 */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 478820: lea ebp, [esi + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 478823: fmul dword ptr [0x4a957c] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 478829: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f700000u;	/* 47882b: mov dword ptr [esp + 0x3c], 0x3f700000 */
	M32((DWORD)(m->esp + 0x58u)) = m->ecx;	/* 478833: mov dword ptr [esp + 0x58], ecx */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 478837: lea ecx, [esp + 0x58] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47883b: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47883e: push ecx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 47883f: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 478843: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 478847: fadd dword ptr [0x4a958c] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47884d: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x60u)) = m->edx;	/* 478850: mov dword ptr [esp + 0x60], edx */
	M32((DWORD)(m->esp + 0x64u)) = m->eax;	/* 478854: mov dword ptr [esp + 0x64], eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 478858: lea edx, [esp + 0x34] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 47885c: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478860: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 478866: fadd dword ptr [0x4a93f4] */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 47886c: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478870: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478871: push eax */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 478872: mov eax, dword ptr [esp + 0x80] */
	{ long double t = ST(0); FPUSH(t); }	/* 478879: fld st(0) */
	ST(0) = -ST(0);	/* 47887b: fchs  */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 47887d: fst dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 478881: fstp dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478885: push ebp */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 478886: lea ecx, [esp + 0x50] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0);	/* 47888a: fst dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 47888e: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 478892: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 478896: fmul dword ptr [0x4a93f4] */
	{ DWORD v_ = 0x42c80000u; m->esp -= 4; M32(m->esp) = v_; }	/* 47889c: push 0x42c80000 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 4788a1: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4788a5: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 4788a6: mov ecx, dword ptr [esp + 0x90] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x74u));	/* 4788ad: fadd dword ptr [esp + 0x74] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4788b1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4788b2: push eax */
	M32((DWORD)(m->esp + 0x64u)) = 0x3f800000u;	/* 4788b3: mov dword ptr [esp + 0x64], 0x3f800000 */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(0xffu);	/* 4788bb: mov byte ptr [esi + 0x7b], 0xff */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0); FPOP();	/* 4788bf: fstp dword ptr [esp + 0x7c] */
	m->esp -= 4; M32(m->esp) = 0x4788c8u; native_call(m, 0x484ca0u);	/* 4788c3: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4788c8: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4788ce: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4788d2: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 4788d8: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 4788e0: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 4788e4: mov dword ptr [esp + 0x34], 0x3e000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 4788ec: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4788ee: fmul st(1) */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 4788f0: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 4788f8: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 478900: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478906: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47890b: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 47890d: fstp st(0) */
	if (m->sf == m->of) goto L_478915;	/* 47890f: jge 0x478915 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478911: xor eax, eax */
	goto L_478921;	/* 478913: jmp 0x478921 */
L_478915:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478915: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478921;	/* 47891a: jle 0x478921 */
	m->eax = 0xffu;	/* 47891c: mov eax, 0xff */
L_478921:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478921: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93fcu));	/* 478927: fadd dword ptr [0x4a93fc] */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 47892d: mov edx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 478930: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 478933: mov eax, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 478939: fld st(0) */
	ST(0) = -ST(0);	/* 47893b: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 47893d: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478941: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478945: cmp edx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478947: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 47894b: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_478f8f;	/* 47894f: jne 0x478f8f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 478955: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478959: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47895f: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 478963: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478967: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47896d: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478971: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478977: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47897b: fstp dword ptr [esp + 0x2c] */
	goto L_478f91;	/* 47897f: jmp 0x478f91 */
L_478984:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 478984: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47898a: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 47898e: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f600000u;	/* 478994: mov dword ptr [esp + 0x30], 0x3f600000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 47899c: mov dword ptr [esp + 0x6c], edx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 4789a0: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 4789a8: mov dword ptr [esp + 0x38], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 4789b0: mov dword ptr [esp + 0x3c], 0x3e800000 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4789b8: fst dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 4789bc: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 4789be: fmulp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 4789c0: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 4789c2: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4789c8: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4789cd: test eax, eax */
	if (m->sf == m->of) goto L_4789d5;	/* 4789cf: jge 0x4789d5 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4789d1: xor eax, eax */
	goto L_4789e1;	/* 4789d3: jmp 0x4789e1 */
L_4789d5:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4789d5: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_4789e1;	/* 4789da: jle 0x4789e1 */
	m->eax = 0xffu;	/* 4789dc: mov eax, 0xff */
L_4789e1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 4789e1: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 4789e7: fadd dword ptr [0x4a93f0] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4789ed: mov byte ptr [esi + 0x7b], al */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 4789f0: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4789f3: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4789f5: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 4789f7: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4789fb: push ebx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4789fc: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 478a00: fmul dword ptr [esp + 0x1c] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 478a04: lea ecx, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 478a08: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478a0b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478a0c: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x80u));	/* 478a0d: mov ecx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478a14: push ebp */
	{ long double t = ST(0); FPUSH(t); }	/* 478a15: fld st(0) */
	ST(0) = -ST(0);	/* 478a17: fchs  */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 478a19: fst dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 478a1d: fstp dword ptr [esp + 0x3c] */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 478a21: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x43480000u; m->esp -= 4; M32(m->esp) = v_; }	/* 478a25: push 0x43480000 */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0);	/* 478a2a: fst dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 478a2e: fstp dword ptr [esp + 0x48] */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 478a32: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478a36: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478a37: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478a38: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 478a39: mov ecx, dword ptr [esp + 0x98] */
	m->esp -= 4; M32(m->esp) = 0x478a45u; native_call(m, 0x484ca0u);	/* 478a40: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 478a45: fld dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478a49: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 478a4f: mov dword ptr [esp + 0x30], 0x3f000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 478a57: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 478a59: fmul st(1) */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 478a5b: mov dword ptr [esp + 0x6c], edx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 478a5f: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 478a67: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 478a6f: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 478a77: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478a7d: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 478a82: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 478a84: fstp st(0) */
	if (m->sf == m->of) goto L_478a8c;	/* 478a86: jge 0x478a8c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478a88: xor eax, eax */
	goto L_478a98;	/* 478a8a: jmp 0x478a98 */
L_478a8c:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478a8c: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478a98;	/* 478a91: jle 0x478a98 */
	m->eax = 0xffu;	/* 478a93: mov eax, 0xff */
L_478a98:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478a98: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 478a9e: fadd dword ptr [0x4a93d0] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 478aa4: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 478aa7: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x202e8d8u));	/* 478aaa: mov ecx, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 478ab0: fld st(0) */
	ST(0) = -ST(0);	/* 478ab2: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 478ab4: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478ab8: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478abc: cmp eax, ecx */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478abe: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 478ac2: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_479366;	/* 478ac6: jne 0x479366 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 478acc: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478ad0: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 478ad6: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 478ada: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478ade: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478ae4: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478ae8: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478aee: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 478af2: fstp dword ptr [esp + 0x2c] */
	goto L_479368;	/* 478af6: jmp 0x479368 */
L_478afb:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 478afb: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 478b01: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478b05: mov eax, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f600000u;	/* 478b0b: mov dword ptr [esp + 0x30], 0x3f600000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 478b13: mov dword ptr [esp + 0x6c], eax */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 478b17: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 478b1f: mov dword ptr [esp + 0x38], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 478b27: mov dword ptr [esp + 0x3c], 0x3e800000 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 478b2f: fst dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 478b33: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 478b35: fmulp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 478b37: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 478b39: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478b3f: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 478b44: test eax, eax */
	if (m->sf == m->of) goto L_478b4c;	/* 478b46: jge 0x478b4c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478b48: xor eax, eax */
	goto L_478b58;	/* 478b4a: jmp 0x478b58 */
L_478b4c:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478b4c: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478b58;	/* 478b51: jle 0x478b58 */
	m->eax = 0xffu;	/* 478b53: mov eax, 0xff */
L_478b58:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478b58: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 478b5e: fadd dword ptr [0x4a93f0] */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 478b64: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 478b67: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 478b69: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 478b6b: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 478b6f: push ebx */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 478b70: lea edx, [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 478b74: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 478b78: fmul dword ptr [esp + 0x1c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 478b7c: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478b7f: push ecx */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 478b80: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478b83: push edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 478b84: mov edx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478b8b: push ebp */
	{ long double t = ST(0); FPUSH(t); }	/* 478b8c: fld st(0) */
	ST(0) = -ST(0);	/* 478b8e: fchs  */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 478b90: fst dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 478b94: fstp dword ptr [esp + 0x3c] */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 478b98: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x43480000u; m->esp -= 4; M32(m->esp) = v_; }	/* 478b9c: push 0x43480000 */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0);	/* 478ba1: fst dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 478ba5: fstp dword ptr [esp + 0x48] */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 478ba9: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478bad: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478bae: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 478baf: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478bb6: push edx */
	m->esp -= 4; M32(m->esp) = 0x478bbcu; native_call(m, 0x484ca0u);	/* 478bb7: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 478bbc: fld dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478bc0: mov eax, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 478bc6: mov dword ptr [esp + 0x30], 0x3f000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 478bce: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 478bd0: fmul st(1) */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 478bd2: mov dword ptr [esp + 0x6c], eax */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 478bd6: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 478bde: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 478be6: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 478bee: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478bf4: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 478bf9: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 478bfb: fstp st(0) */
	if (m->sf == m->of) goto L_478c03;	/* 478bfd: jge 0x478c03 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478bff: xor eax, eax */
	goto L_478c0f;	/* 478c01: jmp 0x478c0f */
L_478c03:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478c03: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478c0f;	/* 478c08: jle 0x478c0f */
	m->eax = 0xffu;	/* 478c0a: mov eax, 0xff */
L_478c0f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478c0f: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 478c15: fadd dword ptr [0x4a93d0] */
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 478c1b: mov ecx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 478c1e: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 478c21: mov eax, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 478c27: fld st(0) */
	ST(0) = -ST(0);	/* 478c29: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 478c2b: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478c2f: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478c33: cmp ecx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478c35: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 478c39: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_479512;	/* 478c3d: jne 0x479512 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 478c43: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478c47: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 478c4d: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 478c51: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478c55: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478c5b: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478c5f: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478c65: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 478c69: fstp dword ptr [esp + 0x2c] */
	goto L_479514;	/* 478c6d: jmp 0x479514 */
L_478c72:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 478c72: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 478c78: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478c7c: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f600000u;	/* 478c82: mov dword ptr [esp + 0x30], 0x3f600000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 478c8a: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 478c8e: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 478c96: mov dword ptr [esp + 0x38], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 478c9e: mov dword ptr [esp + 0x3c], 0x3e800000 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 478ca6: fst dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 478caa: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 478cac: fmulp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 478cae: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 478cb0: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478cb6: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 478cbb: test eax, eax */
	if (m->sf == m->of) goto L_478cc3;	/* 478cbd: jge 0x478cc3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478cbf: xor eax, eax */
	goto L_478ccf;	/* 478cc1: jmp 0x478ccf */
L_478cc3:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478cc3: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478ccf;	/* 478cc8: jle 0x478ccf */
	m->eax = 0xffu;	/* 478cca: mov eax, 0xff */
L_478ccf:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478ccf: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 478cd5: fadd dword ptr [0x4a93f0] */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 478cdb: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 478cde: push 1 */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 478ce0: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 478ce3: push 2 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 478ce5: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 478ce9: push ebx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 478cea: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 478cee: fmul dword ptr [esp + 0x1c] */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 478cf2: lea eax, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 478cf6: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478cf9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478cfa: push eax */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 478cfb: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478d02: push ebp */
	{ long double t = ST(0); FPUSH(t); }	/* 478d03: fld st(0) */
	ST(0) = -ST(0);	/* 478d05: fchs  */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 478d07: fst dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 478d0b: fstp dword ptr [esp + 0x3c] */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 478d0f: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x43480000u; m->esp -= 4; M32(m->esp) = v_; }	/* 478d13: push 0x43480000 */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0);	/* 478d18: fst dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 478d1c: fstp dword ptr [esp + 0x48] */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 478d20: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478d24: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 478d25: mov ecx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478d2c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478d2d: push eax */
	m->esp -= 4; M32(m->esp) = 0x478d33u; native_call(m, 0x484ca0u);	/* 478d2e: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 478d33: fld dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478d37: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 478d3d: mov dword ptr [esp + 0x30], 0x3f000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 478d45: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 478d47: fmul st(1) */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 478d49: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 478d4d: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 478d55: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 478d5d: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 478d65: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478d6b: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 478d70: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 478d72: fstp st(0) */
	if (m->sf == m->of) goto L_478d7a;	/* 478d74: jge 0x478d7a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478d76: xor eax, eax */
	goto L_478d86;	/* 478d78: jmp 0x478d86 */
L_478d7a:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478d7a: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478d86;	/* 478d7f: jle 0x478d86 */
	m->eax = 0xffu;	/* 478d81: mov eax, 0xff */
L_478d86:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478d86: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 478d8c: fadd dword ptr [0x4a93d0] */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 478d92: mov edx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 478d95: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 478d98: mov eax, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 478d9e: fld st(0) */
	ST(0) = -ST(0);	/* 478da0: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 478da2: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478da6: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478daa: cmp edx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478dac: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 478db0: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_478f8f;	/* 478db4: jne 0x478f8f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 478dba: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478dbe: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 478dc4: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 478dc8: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478dcc: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478dd2: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478dd6: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478ddc: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 478de0: fstp dword ptr [esp + 0x2c] */
	goto L_478f91;	/* 478de4: jmp 0x478f91 */
L_478de9:
	m->eax = (DWORD)(m->ecx + 0xffffffddu);	/* 478de9: lea eax, [ecx - 0x23] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478dec: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_479840;	/* 478def: ja 0x479840 */
	switch (m->eax) { case 0: goto L_478dfc; case 1: goto L_478fcb; case 2: goto L_4791f6; case 3: goto L_4793a2; case 4: goto L_47954e; default: abort(); }	/* 478df5: jmp dword ptr [eax*4 + 0x4798fc] */
L_478dfc:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 478dfc: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa43cu));	/* 478e00: fmul dword ptr [0x4aa43c] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfdcu));	/* 478e06: mov edx, dword ptr [edi + 0x9ccfdc] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 478e0c: mov dword ptr [esp + 0x6c], edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478e10: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478e15: cmp eax, 0xf */
	if (m->zf || m->sf != m->of) goto L_478e1f;	/* 478e18: jle 0x478e1f */
	m->eax = 0xfu;	/* 478e1a: mov eax, 0xf */
L_478e1f:
	m->ecx = m->eax;	/* 478e1f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 478e21: and ecx, 0x80000003 */
	if (!m->sf) goto L_478e2e;	/* 478e27: jns 0x478e2e */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 478e29: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 478e2a: or ecx, 0xfffffffc */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 478e2d: inc ecx */
L_478e2e:
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 478e2e: shl ecx, 6 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 478e31: mov dword ptr [esp + 0x1c], ecx */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 478e35: lea ebx, [esi + 0x10] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 478e38: fild dword ptr [esp + 0x1c] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 478e3c: cdq  */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 478e3d: fmul dword ptr [0x4a957c] */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 478e43: and edx, 3 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 478e46: push 1 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 478e48: add eax, edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 478e4a: push 2 */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 478e4c: sar eax, 2 */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 478e4f: fstp dword ptr [esp + 0x38] */
	{ DWORD a_ = m->eax, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 478e53: shl eax, 6 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 478e56: mov dword ptr [esp + 0x24], eax */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 478e5a: lea edx, [esp + 0x30] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 478e5e: fild dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 478e62: push ebx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 478e63: lea eax, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 478e67: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478e6a: push edx */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 478e6b: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478e71: push eax */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 478e72: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478e79: push ebp */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 478e7a: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x44fa0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 478e7e: push 0x44fa0000 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 478e83: lea edx, [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 478e87: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 478e8b: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 478e8f: fadd dword ptr [0x4a941c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478e95: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 478e96: mov ecx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478e9d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478e9e: push eax */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 478e9f: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 478ea3: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 478ea7: fadd dword ptr [0x4a941c] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(0xffu);	/* 478ead: mov byte ptr [esi + 0x7b], 0xff */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 478eb1: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478eb5: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9554u));	/* 478ebb: fadd dword ptr [0x4a9554] */
	{ long double t = ST(0); FPUSH(t); }	/* 478ec1: fld st(0) */
	ST(0) = -ST(0);	/* 478ec3: fchs  */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0);	/* 478ec5: fst dword ptr [esp + 0x48] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 478ec9: fstp dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0);	/* 478ecd: fst dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 478ed1: fstp dword ptr [esp + 0x54] */
	m->esp -= 4; M32(m->esp) = 0x478edau; native_call(m, 0x484ca0u);	/* 478ed5: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 478eda: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 478ee0: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478ee4: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 478eea: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 478ef2: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 478ef6: mov dword ptr [esp + 0x34], 0x3e000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 478efe: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 478f00: fmul st(1) */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 478f02: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 478f0a: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 478f12: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478f18: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 478f1d: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 478f1f: fstp st(0) */
	if (m->sf == m->of) goto L_478f27;	/* 478f21: jge 0x478f27 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 478f23: xor eax, eax */
	goto L_478f33;	/* 478f25: jmp 0x478f33 */
L_478f27:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478f27: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_478f33;	/* 478f2c: jle 0x478f33 */
	m->eax = 0xffu;	/* 478f2e: mov eax, 0xff */
L_478f33:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 478f33: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa434u));	/* 478f39: fadd dword ptr [0x4aa434] */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 478f3f: mov edx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 478f42: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 478f45: mov eax, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 478f4b: fld st(0) */
	ST(0) = -ST(0);	/* 478f4d: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 478f4f: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478f53: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478f57: cmp edx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478f59: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 478f5d: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_478f8f;	/* 478f61: jne 0x478f8f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 478f63: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478f67: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 478f6d: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 478f71: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478f75: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 478f7b: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 478f7f: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 478f85: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 478f89: fstp dword ptr [esp + 0x2c] */
	goto L_478f91;	/* 478f8d: jmp 0x478f91 */
L_478f8f:
	ST(0) = ST(0); FPOP();	/* 478f8f: fstp st(0) */
L_478f91:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 478f91: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 478f93: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 478f95: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 478f99: push ebx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 478f9a: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478f9e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478f9f: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x80u));	/* 478fa0: mov ecx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 478fa7: push ebp */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 478fa8: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 478fac: push 0 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 478fae: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 478fb2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 478fb3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 478fb4: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 478fb5: mov ecx, dword ptr [esp + 0x98] */
	m->esp -= 4; M32(m->esp) = 0x478fc1u; native_call(m, 0x484ca0u);	/* 478fbc: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 478fc1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 478fc2: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 478fc3: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 478fc4: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 478fc5: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 478fc8: ret 8 */
L_478fcb:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 478fcb: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa43cu));	/* 478fcf: fmul dword ptr [0x4aa43c] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 478fd5: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 478fdb: mov dword ptr [esp + 0x6c], edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 478fdf: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 478fe4: cmp eax, 0xf */
	if (m->zf || m->sf != m->of) goto L_478fee;	/* 478fe7: jle 0x478fee */
	m->eax = 0xfu;	/* 478fe9: mov eax, 0xf */
L_478fee:
	m->ecx = m->eax;	/* 478fee: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x80000007u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 478ff0: and ecx, 0x80000007 */
	if (!m->sf) goto L_478ffd;	/* 478ff6: jns 0x478ffd */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 478ff8: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 478ff9: or ecx, 0xfffffff8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 478ffc: inc ecx */
L_478ffd:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 478ffd: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 478ffe: and edx, 7 */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 479001: shl ecx, 5 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 479004: add eax, edx */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 479006: mov dword ptr [esp + 0x1c], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 47900a: fild dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47900e: sar eax, 3 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 479011: add eax, 3 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 479014: fmul dword ptr [0x4a957c] */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47901a: shl eax, 5 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47901d: mov dword ptr [esp + 0x1c], eax */
	m->eax = m->ebp;	/* 479021: mov eax, ebp */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 479023: fild dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = 0x80000003u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479027: and eax, 0x80000003 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 47902c: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 479032: fstp dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 479036: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 479038: fadd dword ptr [0x4aa274] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 47903e: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 479042: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4aa274u));	/* 479046: fadd dword ptr [0x4aa274] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47904c: fstp dword ptr [esp + 0x1c] */
	if (!m->sf) goto L_479057;	/* 479050: jns 0x479057 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 479052: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffcu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479053: or eax, 0xfffffffc */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 479056: inc eax */
L_479057:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479057: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_4790db;	/* 47905a: ja 0x4790db */
	switch (m->eax) { case 0: goto L_479063; case 1: goto L_479081; case 2: goto L_47909f; case 3: goto L_4790bd; default: abort(); }	/* 47905c: jmp dword ptr [eax*4 + 0x479910] */
L_479063:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 479063: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 479067: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 47906b: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 47906f: mov dword ptr [esp + 0x34], edx */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 479073: fstp dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 479077: mov dword ptr [esp + 0x38], eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 47907b: mov dword ptr [esp + 0x3c], ecx */
	goto L_4790dd;	/* 47907f: jmp 0x4790dd */
L_479081:
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 479081: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 479085: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 479089: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 47908d: mov dword ptr [esp + 0x34], edx */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 479091: fstp dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 479095: mov dword ptr [esp + 0x38], eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 479099: mov dword ptr [esp + 0x3c], ecx */
	goto L_4790dd;	/* 47909d: jmp 0x4790dd */
L_47909f:
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 47909f: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4790a3: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 4790a7: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 4790ab: mov dword ptr [esp + 0x30], edx */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4790af: fstp dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 4790b3: mov dword ptr [esp + 0x34], eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 4790b7: mov dword ptr [esp + 0x3c], ecx */
	goto L_4790dd;	/* 4790bb: jmp 0x4790dd */
L_4790bd:
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4790bd: mov edx, dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4790c1: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4790c5: mov ecx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 4790c9: mov dword ptr [esp + 0x30], edx */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4790cd: fstp dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 4790d1: mov dword ptr [esp + 0x34], eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 4790d5: mov dword ptr [esp + 0x3c], ecx */
	goto L_4790dd;	/* 4790d9: jmp 0x4790dd */
L_4790db:
	ST(0) = ST(0); FPOP();	/* 4790db: fstp st(0) */
L_4790dd:
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 4790dd: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4790e0: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4790e2: push 2 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 4790e4: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4790e8: push ebx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 4790e9: lea eax, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 4790ed: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4790f0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4790f1: push eax */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 4790f2: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4790f9: push ebp */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 4790fa: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x447a0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4790fe: push 0x447a0000 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 479103: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 479107: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 479108: mov ecx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47910f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 479110: push eax */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(0xffu);	/* 479111: mov byte ptr [esi + 0x7b], 0xff */
	M32((DWORD)(m->esp + 0x48u)) = 0xc47a0000u;	/* 479115: mov dword ptr [esp + 0x48], 0xc47a0000 */
	M32((DWORD)(m->esp + 0x4cu)) = 0xc47a0000u;	/* 47911d: mov dword ptr [esp + 0x4c], 0xc47a0000 */
	M32((DWORD)(m->esp + 0x50u)) = 0x447a0000u;	/* 479125: mov dword ptr [esp + 0x50], 0x447a0000 */
	M32((DWORD)(m->esp + 0x54u)) = 0x447a0000u;	/* 47912d: mov dword ptr [esp + 0x54], 0x447a0000 */
	m->esp -= 4; M32(m->esp) = 0x47913au; native_call(m, 0x484ca0u);	/* 479135: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 47913a: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 479140: fsub dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 479144: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 47914a: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 479152: mov dword ptr [esp + 0x6c], ecx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 479156: mov dword ptr [esp + 0x34], 0x3e000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 47915e: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 479160: fmul st(1) */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 479162: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 47916a: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 479172: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 479178: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47917d: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 47917f: fstp st(0) */
	if (m->sf == m->of) goto L_479187;	/* 479181: jge 0x479187 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479183: xor eax, eax */
	goto L_479193;	/* 479185: jmp 0x479193 */
L_479187:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479187: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_479193;	/* 47918c: jle 0x479193 */
	m->eax = 0xffu;	/* 47918e: mov eax, 0xff */
L_479193:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 479193: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9554u));	/* 479199: fadd dword ptr [0x4a9554] */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 47919f: mov edx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4791a2: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 4791a5: mov eax, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 4791ab: fld st(0) */
	ST(0) = -ST(0);	/* 4791ad: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 4791af: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4791b3: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4791b7: cmp edx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 4791b9: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 4791bd: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_478f8f;	/* 4791c1: jne 0x478f8f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4791c7: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4791cb: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4791d1: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4791d5: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4791d9: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4791df: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4791e3: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 4791e9: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4791ed: fstp dword ptr [esp + 0x2c] */
	goto L_478f91;	/* 4791f1: jmp 0x478f91 */
L_4791f6:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4791f6: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4791fc: fsub dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 479200: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f600000u;	/* 479206: mov dword ptr [esp + 0x30], 0x3f600000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 47920e: mov dword ptr [esp + 0x6c], edx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 479212: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 47921a: mov dword ptr [esp + 0x38], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 479222: mov dword ptr [esp + 0x3c], 0x3e800000 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 47922a: fst dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 47922e: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 479230: fmulp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 479232: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 479234: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47923a: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47923f: test eax, eax */
	if (m->sf == m->of) goto L_479247;	/* 479241: jge 0x479247 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479243: xor eax, eax */
	goto L_479253;	/* 479245: jmp 0x479253 */
L_479247:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479247: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_479253;	/* 47924c: jle 0x479253 */
	m->eax = 0xffu;	/* 47924e: mov eax, 0xff */
L_479253:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 479253: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 479259: fadd dword ptr [0x4a93f0] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47925f: mov byte ptr [esi + 0x7b], al */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 479262: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 479265: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 479267: push 2 */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 479269: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47926d: push ebx */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47926e: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 479272: fmul dword ptr [esp + 0x1c] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 479276: lea ecx, [esp + 0x2c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 47927a: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47927d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47927e: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x80u));	/* 47927f: mov ecx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 479286: push ebp */
	{ long double t = ST(0); FPUSH(t); }	/* 479287: fld st(0) */
	ST(0) = -ST(0);	/* 479289: fchs  */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 47928b: fst dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 47928f: fstp dword ptr [esp + 0x3c] */
	m->edx = (DWORD)(m->esp + 0x50u);	/* 479293: lea edx, [esp + 0x50] */
	{ DWORD v_ = 0x43480000u; m->esp -= 4; M32(m->esp) = v_; }	/* 479297: push 0x43480000 */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0);	/* 47929c: fst dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4792a0: fstp dword ptr [esp + 0x48] */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 4792a4: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4792a8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4792a9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4792aa: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x98u));	/* 4792ab: mov ecx, dword ptr [esp + 0x98] */
	m->esp -= 4; M32(m->esp) = 0x4792b7u; native_call(m, 0x484ca0u);	/* 4792b2: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4792b7: fld dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4792bb: mov edx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 4792c1: mov dword ptr [esp + 0x30], 0x3f000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 4792c9: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4792cb: fmul st(1) */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 4792cd: mov dword ptr [esp + 0x6c], edx */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 4792d1: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 4792d9: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 4792e1: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 4792e9: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4792ef: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4792f4: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 4792f6: fstp st(0) */
	if (m->sf == m->of) goto L_4792fe;	/* 4792f8: jge 0x4792fe */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4792fa: xor eax, eax */
	goto L_47930a;	/* 4792fc: jmp 0x47930a */
L_4792fe:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4792fe: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_47930a;	/* 479303: jle 0x47930a */
	m->eax = 0xffu;	/* 479305: mov eax, 0xff */
L_47930a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 47930a: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 479310: fadd dword ptr [0x4a93d0] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 479316: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 479319: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x202e8d8u));	/* 47931c: mov ecx, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 479322: fld st(0) */
	ST(0) = -ST(0);	/* 479324: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 479326: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47932a: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47932e: cmp eax, ecx */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 479330: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 479334: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_479366;	/* 479338: jne 0x479366 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47933a: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 47933e: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 479344: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 479348: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 47934c: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 479352: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 479356: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 47935c: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 479360: fstp dword ptr [esp + 0x2c] */
	goto L_479368;	/* 479364: jmp 0x479368 */
L_479366:
	ST(0) = ST(0); FPOP();	/* 479366: fstp st(0) */
L_479368:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 479368: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 47936a: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 47936c: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 479370: push ebx */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 479371: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 479375: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 479376: push edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 479377: mov edx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47937e: push ebp */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 47937f: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 479383: push 0 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 479385: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 479389: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47938a: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 47938b: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 479392: push edx */
	m->esp -= 4; M32(m->esp) = 0x479398u; native_call(m, 0x484ca0u);	/* 479393: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 479398: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 479399: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47939a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47939b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47939c: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 47939f: ret 8 */
L_4793a2:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 4793a2: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4793a8: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 4793ac: mov eax, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f600000u;	/* 4793b2: mov dword ptr [esp + 0x30], 0x3f600000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 4793ba: mov dword ptr [esp + 0x6c], eax */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 4793be: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f800000u;	/* 4793c6: mov dword ptr [esp + 0x38], 0x3f800000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 4793ce: mov dword ptr [esp + 0x3c], 0x3e800000 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 4793d6: fst dword ptr [esp + 0x14] */
	{ long double t = ST(0); FPUSH(t); }	/* 4793da: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 4793dc: fmulp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 4793de: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 4793e0: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4793e6: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4793eb: test eax, eax */
	if (m->sf == m->of) goto L_4793f3;	/* 4793ed: jge 0x4793f3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4793ef: xor eax, eax */
	goto L_4793ff;	/* 4793f1: jmp 0x4793ff */
L_4793f3:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4793f3: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_4793ff;	/* 4793f8: jle 0x4793ff */
	m->eax = 0xffu;	/* 4793fa: mov eax, 0xff */
L_4793ff:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 4793ff: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f0u));	/* 479405: fadd dword ptr [0x4a93f0] */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 47940b: lea ebx, [esi + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47940e: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 479410: push 2 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 479412: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 479416: push ebx */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 479417: lea edx, [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 47941b: fstp dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47941f: fmul dword ptr [esp + 0x1c] */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 479423: lea ebp, [esi + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 479426: push ecx */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 479427: mov byte ptr [esi + 0x7b], al */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47942a: push edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 47942b: mov edx, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 479432: push ebp */
	{ long double t = ST(0); FPUSH(t); }	/* 479433: fld st(0) */
	ST(0) = -ST(0);	/* 479435: fchs  */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0);	/* 479437: fst dword ptr [esp + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 47943b: fstp dword ptr [esp + 0x3c] */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 47943f: lea eax, [esp + 0x50] */
	{ DWORD v_ = 0x43480000u; m->esp -= 4; M32(m->esp) = v_; }	/* 479443: push 0x43480000 */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0);	/* 479448: fst dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 47944c: fstp dword ptr [esp + 0x48] */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 479450: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 479454: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 479455: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 479456: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47945d: push edx */
	m->esp -= 4; M32(m->esp) = 0x479463u; native_call(m, 0x484ca0u);	/* 47945e: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 479463: fld dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 479467: mov eax, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 47946d: mov dword ptr [esp + 0x30], 0x3f000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 479475: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 479477: fmul st(1) */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 479479: mov dword ptr [esp + 0x6c], eax */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 47947d: mov dword ptr [esp + 0x34], 0x3e000000 */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 479485: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 47948d: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 479495: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47949b: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4794a0: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 4794a2: fstp st(0) */
	if (m->sf == m->of) goto L_4794aa;	/* 4794a4: jge 0x4794aa */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4794a6: xor eax, eax */
	goto L_4794b6;	/* 4794a8: jmp 0x4794b6 */
L_4794aa:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4794aa: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_4794b6;	/* 4794af: jle 0x4794b6 */
	m->eax = 0xffu;	/* 4794b1: mov eax, 0xff */
L_4794b6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 4794b6: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 4794bc: fadd dword ptr [0x4a93d0] */
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 4794c2: mov ecx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4794c5: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 4794c8: mov eax, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 4794ce: fld st(0) */
	ST(0) = -ST(0);	/* 4794d0: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 4794d2: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4794d6: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4794da: cmp ecx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 4794dc: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 4794e0: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_479512;	/* 4794e4: jne 0x479512 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4794e6: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4794ea: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4794f0: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4794f4: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4794f8: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4794fe: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 479502: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 479508: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 47950c: fstp dword ptr [esp + 0x2c] */
	goto L_479514;	/* 479510: jmp 0x479514 */
L_479512:
	ST(0) = ST(0); FPOP();	/* 479512: fstp st(0) */
L_479514:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 479514: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 479516: push 2 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 479518: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47951c: push ebx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 47951d: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 479521: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 479522: push eax */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 479523: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47952a: push ebp */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 47952b: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 47952f: push 0 */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 479531: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 479535: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x90u));	/* 479536: mov ecx, dword ptr [esp + 0x90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47953d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47953e: push eax */
	m->esp -= 4; M32(m->esp) = 0x479544u; native_call(m, 0x484ca0u);	/* 47953f: call 0x484ca0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 479544: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 479545: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 479546: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 479547: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479548: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 47954b: ret 8 */
L_47954e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47954e: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94ccu));	/* 479552: fmul dword ptr [0x4a94cc] */
	m->ecx = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 479558: mov ecx, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 47955e: mov dword ptr [esp + 0x6c], ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 479562: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479567: cmp eax, 7 */
	if (m->zf || m->sf != m->of) goto L_479571;	/* 47956a: jle 0x479571 */
	m->eax = 0x7u;	/* 47956c: mov eax, 7 */
L_479571:
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 479571: shl eax, 4 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 479574: mov dword ptr [esp + 0x1c], eax */
	m->ebx = (DWORD)(m->esi + 0x10u);	/* 479578: lea ebx, [esi + 0x10] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 47957b: fild dword ptr [esp + 0x1c] */
	m->edx = m->ebx;	/* 47957f: mov edx, ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 479581: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 479583: push 2 */
	m->ebp = (DWORD)(m->esi + 0x78u);	/* 479585: lea ebp, [esi + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 479588: fmul dword ptr [0x4a957c] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 47958e: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3f700000u;	/* 479590: mov dword ptr [esp + 0x3c], 0x3f700000 */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 479598: mov dword ptr [esp + 0x58], eax */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 47959c: lea eax, [esp + 0x58] */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 4795a0: mov ecx, dword ptr [edx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4795a3: push eax */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4795a4: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4795a8: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 4795ac: fadd dword ptr [0x4a958c] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 4795b2: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x60u)) = m->ecx;	/* 4795b5: mov dword ptr [esp + 0x60], ecx */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 4795b9: mov dword ptr [esp + 0x64], edx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 4795bd: lea ecx, [esp + 0x34] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4795c1: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 4795c5: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 4795cb: fadd dword ptr [0x4a93f4] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 4795d1: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4795d5: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4795d6: push edx */
	m->edx = M32((DWORD)(m->esp + 0x80u));	/* 4795d7: mov edx, dword ptr [esp + 0x80] */
	{ long double t = ST(0); FPUSH(t); }	/* 4795de: fld st(0) */
	ST(0) = -ST(0);	/* 4795e0: fchs  */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 4795e2: fst dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4795e6: fstp dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4795ea: push ebp */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 4795eb: lea eax, [esp + 0x50] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0);	/* 4795ef: fst dword ptr [esp + 0x40] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4795f3: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4795f7: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 4795fb: fmul dword ptr [0x4a93f4] */
	{ DWORD v_ = 0x42c80000u; m->esp -= 4; M32(m->esp) = v_; }	/* 479601: push 0x42c80000 */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 479606: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47960a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47960b: push ecx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x78u));	/* 47960c: fadd dword ptr [esp + 0x78] */
	m->ecx = M32((DWORD)(m->esp + 0x94u));	/* 479610: mov ecx, dword ptr [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 479617: push edx */
	M32((DWORD)(m->esp + 0x64u)) = 0x3f800000u;	/* 479618: mov dword ptr [esp + 0x64], 0x3f800000 */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(0xffu);	/* 479620: mov byte ptr [esi + 0x7b], 0xff */
	MF((DWORD)(m->esp + 0x7cu)) = (float)ST(0); FPOP();	/* 479624: fstp dword ptr [esp + 0x7c] */
	m->esp -= 4; M32(m->esp) = 0x47962du; native_call(m, 0x484ca0u);	/* 479628: call 0x484ca0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 47962d: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 479633: fsub dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->edi + 0x9ccfd4u));	/* 479637: mov eax, dword ptr [edi + 0x9ccfd4] */
	M32((DWORD)(m->esp + 0x30u)) = 0x3f000000u;	/* 47963d: mov dword ptr [esp + 0x30], 0x3f000000 */
	M32((DWORD)(m->esp + 0x6cu)) = m->eax;	/* 479645: mov dword ptr [esp + 0x6c], eax */
	M32((DWORD)(m->esp + 0x34u)) = 0x3e000000u;	/* 479649: mov dword ptr [esp + 0x34], 0x3e000000 */
	{ long double t = ST(0); FPUSH(t); }	/* 479651: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 479653: fmul st(1) */
	M32((DWORD)(m->esp + 0x38u)) = 0x3f200000u;	/* 479655: mov dword ptr [esp + 0x38], 0x3f200000 */
	M32((DWORD)(m->esp + 0x3cu)) = 0x3e800000u;	/* 47965d: mov dword ptr [esp + 0x3c], 0x3e800000 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa264u));	/* 479665: fmul dword ptr [0x4aa264] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47966b: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 479670: test eax, eax */
	ST(0) = ST(0); FPOP();	/* 479672: fstp st(0) */
	if (m->sf == m->of) goto L_47967a;	/* 479674: jge 0x47967a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479676: xor eax, eax */
	goto L_479686;	/* 479678: jmp 0x479686 */
L_47967a:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47967a: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_479686;	/* 47967f: jle 0x479686 */
	m->eax = 0xffu;	/* 479681: mov eax, 0xff */
L_479686:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x80u)));	/* 479686: fld dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a93fcu));	/* 47968c: fadd dword ptr [0x4a93fc] */
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 479692: mov ecx, dword ptr [esi + 0xc] */
	M8((DWORD)(m->esi + 0x7bu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 479695: mov byte ptr [esi + 0x7b], al */
	m->eax = M32((DWORD)(m->edi + 0x202e8d8u));	/* 479698: mov eax, dword ptr [edi + 0x202e8d8] */
	{ long double t = ST(0); FPUSH(t); }	/* 47969e: fld st(0) */
	ST(0) = -ST(0);	/* 4796a0: fchs  */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 4796a2: fst dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4796a6: fstp dword ptr [esp + 0x24] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4796aa: cmp ecx, eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 4796ac: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0);	/* 4796b0: fst dword ptr [esp + 0x2c] */
	if (!m->zf) goto L_479512;	/* 4796b4: jne 0x479512 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 4796ba: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4796be: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 4796c4: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 4796c8: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4796cc: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4796d2: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4796d6: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 4796dc: fst dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4796e0: fstp dword ptr [esp + 0x2c] */
	goto L_479514;	/* 4796e4: jmp 0x479514 */
L_4796e9:
	m->eax = (DWORD)(m->ecx + 0xffffffd8u);	/* 4796e9: lea eax, [ecx - 0x28] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4796ec: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_479840;	/* 4796ef: ja 0x479840 */
	switch (m->eax) { case 0: goto L_4796fc; case 1: goto L_4796fc; case 2: goto L_4796fc; case 3: goto L_4796fc; case 4: goto L_4796fc; default: abort(); }	/* 4796f5: jmp dword ptr [eax*4 + 0x479920] */
L_4796fc:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 4796fc: fld dword ptr [esi + 0x6c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 4796ff: fcomp dword ptr [0x4a9424] */
	m->edi = M32((DWORD)(m->edi + 0x9ccff4u));	/* 479705: mov edi, dword ptr [edi + 0x9ccff4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47970b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47970d: test ah, 0x41 */
	if (!m->zf) goto L_479799;	/* 479710: jne 0x479799 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93fcu)));	/* 479716: fld dword ptr [0x4a93fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x6cu));	/* 47971c: fsub dword ptr [esi + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 47971f: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 479725: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47972a: test eax, eax */
	if (m->sf == m->of) goto L_4797fc;	/* 47972c: jge 0x4797fc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479732: xor eax, eax */
	goto L_479787;	/* 479734: jmp 0x479787 */
L_479736:
	m->eax = (DWORD)(m->ecx + 0xffffffd3u);	/* 479736: lea eax, [ecx - 0x2d] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479739: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_479840;	/* 47973c: ja 0x479840 */
	switch (m->eax) { case 0: goto L_479749; case 1: goto L_4796fc; case 2: goto L_4796fc; case 3: goto L_4796fc; case 4: goto L_4797ca; default: abort(); }	/* 479742: jmp dword ptr [eax*4 + 0x479934] */
L_479749:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 479749: fld dword ptr [esi + 0x6c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 47974c: fcomp dword ptr [0x4a9424] */
	m->edi = M32((DWORD)(m->edi + 0x9ccff4u));	/* 479752: mov edi, dword ptr [edi + 0x9ccff4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 479758: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47975a: test ah, 0x41 */
	if (!m->zf) goto L_479799;	/* 47975d: jne 0x479799 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93fcu)));	/* 47975f: fld dword ptr [0x4a93fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x6cu));	/* 479765: fsub dword ptr [esi + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 479768: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 47976e: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 479773: test eax, eax */
	if (m->sf == m->of) goto L_47977b;	/* 479775: jge 0x47977b */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 479777: xor eax, eax */
	goto L_479787;	/* 479779: jmp 0x479787 */
L_47977b:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47977b: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_479787;	/* 479780: jle 0x479787 */
L_479782:
	m->eax = 0xffu;	/* 479782: mov eax, 0xff */
L_479787:
	M8((DWORD)(m->esi + 0xd7u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 479787: mov byte ptr [esi + 0xd7], al */
	M8((DWORD)(m->esi + 0xdbu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 47978d: mov byte ptr [esi + 0xdb], al */
	M8((DWORD)(m->esi + 0xdfu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 479793: mov byte ptr [esi + 0xdf], al */
L_479799:
	m->ecx = M32((DWORD)(m->esi + 0x28u));	/* 479799: mov ecx, dword ptr [esi + 0x28] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47979c: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47979e: push 1 */
	m->edx = (DWORD)(m->esi + 0x84u);	/* 4797a0: lea edx, [esi + 0x84] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4797a6: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x7cu));	/* 4797a7: mov ecx, dword ptr [esp + 0x7c] */
	m->eax = (DWORD)(m->esi + 0xd4u);	/* 4797ab: lea eax, [esi + 0xd4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4797b1: push edx */
	{ DWORD a_ = m->esi, b_ = 0xb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4797b2: add esi, 0xb4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4797b8: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4797b9: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4797ba: push edi */
	m->esp -= 4; M32(m->esp) = 0x4797c0u; native_call(m, 0x4842d0u);	/* 4797bb: call 0x4842d0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4797c0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4797c1: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4797c2: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4797c3: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4797c4: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 4797c7: ret 8 */
L_4797ca:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 4797ca: fld dword ptr [esi + 0x6c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 4797cd: fcomp dword ptr [0x4a9424] */
	m->edi = M32((DWORD)(m->edi + 0x9ccff4u));	/* 4797d3: mov edi, dword ptr [edi + 0x9ccff4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4797d9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4797db: test ah, 0x41 */
	if (!m->zf) goto L_479799;	/* 4797de: jne 0x479799 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93fcu)));	/* 4797e0: fld dword ptr [0x4a93fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x6cu));	/* 4797e6: fsub dword ptr [esi + 0x6c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa260u));	/* 4797e9: fmul dword ptr [0x4aa260] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4797ef: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4797f4: test eax, eax */
	if (m->sf == m->of) goto L_4797fc;	/* 4797f6: jge 0x4797fc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4797f8: xor eax, eax */
	goto L_479787;	/* 4797fa: jmp 0x479787 */
L_4797fc:
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4797fc: cmp eax, 0xff */
	if (m->zf || m->sf != m->of) goto L_479787;	/* 479801: jle 0x479787 */
	goto L_479782;	/* 479803: jmp 0x479782 */
L_479808:
	{ DWORD a_ = m->ecx, b_ = 0x32u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479808: cmp ecx, 0x32 */
	if (!m->zf) goto L_479840;	/* 47980b: jne 0x479840 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 47980d: push 1 */
	m->ecx = (DWORD)(m->esi + 0xfcu);	/* 47980f: lea ecx, [esi + 0xfc] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 479815: push 2 */
	m->edx = (DWORD)(m->esi + 0xf8u);	/* 479817: lea edx, [esi + 0xf8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47981d: push ecx */
	m->eax = (DWORD)(m->esi + 0xf0u);	/* 47981e: lea eax, [esi + 0xf0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 479824: push edx */
	m->edx = M32((DWORD)(m->esi + 0xe4u));	/* 479825: mov edx, dword ptr [esi + 0xe4] */
	m->ecx = (DWORD)(m->esi + 0xe8u);	/* 47982b: lea ecx, [esi + 0xe8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 479831: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 479832: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x88u));	/* 479833: mov ecx, dword ptr [esp + 0x88] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47983a: push edx */
	m->esp -= 4; M32(m->esp) = 0x479840u; native_call(m, 0x4848e0u);	/* 47983b: call 0x4848e0 */
L_479840:
	m->edi = M32(m->esp); m->esp += 4;	/* 479840: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 479841: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 479842: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 479843: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 479844: add esp, 0x58 */
	m->esp += 4 + 8; return;	/* 479847: ret 8 */
}

/* hud_479af0 (0x479af0), lifted by tools/lift.py */
static void lift_479af0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 479af0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 479af1: push edi */
	m->edi = m->ecx;	/* 479af2: mov edi, ecx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 479af4: xor esi, esi */
	m->eax = M32((DWORD)(m->edi + 0x20f2da0u));	/* 479af6: mov eax, dword ptr [edi + 0x20f2da0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 479afc: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_479b2d;	/* 479afe: jle 0x479b2d */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 479b00: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 479b01: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 479b02: mov ebp, dword ptr [esp + 0x14] */
	m->ebx = (DWORD)(m->edi + 0x20a99c4u);	/* 479b06: lea ebx, [edi + 0x20a99c4] */
L_479b0c:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479b0c: cmp dword ptr [ebx], 1 */
	if (!m->zf) goto L_479b1a;	/* 479b0f: jne 0x479b1a */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 479b11: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 479b12: push esi */
	m->ecx = m->edi;	/* 479b13: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x479b1au; lift_476890(m);	/* 479b15: call 0x476890 */
L_479b1a:
	m->eax = M32((DWORD)(m->edi + 0x20f2da0u));	/* 479b1a: mov eax, dword ptr [edi + 0x20f2da0] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 479b20: inc esi */
	{ DWORD a_ = m->ebx, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 479b21: add ebx, 0x12c */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 479b27: cmp esi, eax */
	if (m->sf != m->of) goto L_479b0c;	/* 479b29: jl 0x479b0c */
	m->ebp = M32(m->esp); m->esp += 4;	/* 479b2b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 479b2c: pop ebx */
L_479b2d:
	m->edi = M32(m->esp); m->esp += 4;	/* 479b2d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 479b2e: pop esi */
	m->esp += 4 + 4; return;	/* 479b2f: ret 4 */
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
