/* ---- emulated machine for lifted functions (tools/lift.py) ---- */
#if 0 /* X86 comes from the earlier lifted file */
typedef struct { DWORD eax, ecx, edx, ebx, esp, ebp, esi, edi; int zf, sf, cf, of; long double fs[8]; int ft; DWORD fsw; } X86;
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

static void lift_471400(X86 *m);

/* collision_moveActor (0x471400), lifted by tools/lift.py */
static void lift_471400(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 471400: sub esp, 0x18 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93e8u)));	/* 471403: fld dword ptr [0x4a93e8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 471409: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47140a: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47140b: push esi */
	m->esi = M32((DWORD)(m->esp + 0x2cu));	/* 47140c: mov esi, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 471410: push edi */
	m->edi = M32((DWORD)(m->esp + 0x34u));	/* 471411: mov edi, dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 471415: fld dword ptr [esi] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 471417: fadd dword ptr [edi] */
	m->ebp = M32((DWORD)(m->esp + 0x40u));	/* 471419: mov ebp, dword ptr [esp + 0x40] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47141d: xor edx, edx */
	m->eax = m->ebp;	/* 47141f: mov eax, ebp */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 471421: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 471425: fld dword ptr [edi + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 471428: fadd dword ptr [esi + 4] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 47142b: mov ebx, dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47142f: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 471433: fld dword ptr [edi + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 471436: fadd dword ptr [esi + 8] */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 471439: mov dword ptr [eax], ebx */
	m->ebx = M32((DWORD)(m->esp + 0x20u));	/* 47143b: mov ebx, dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47143f: fstp dword ptr [esp + 0x24] */
	M32((DWORD)(m->eax + 0x4u)) = m->ebx;	/* 471443: mov dword ptr [eax + 4], ebx */
	m->ebx = M32((DWORD)(m->esp + 0x24u));	/* 471446: mov ebx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->eax + 0x8u)) = m->ebx;	/* 47144a: mov dword ptr [eax + 8], ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x0u)));	/* 47144d: fld dword ptr [ebp] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x9ef91cu)); FPOP();	/* 471450: fcomp dword ptr [ecx + 0x9ef91c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471456: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471458: test ah, 1 */
	if (m->zf) goto L_471468;	/* 47145b: je 0x471468 */
	m->edx = M32((DWORD)(m->ecx + 0x9ef91cu));	/* 47145d: mov edx, dword ptr [ecx + 0x9ef91c] */
	M32((DWORD)(m->ebp + 0x0u)) = m->edx;	/* 471463: mov dword ptr [ebp], edx */
	goto L_471481;	/* 471466: jmp 0x471481 */
L_471468:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x0u)));	/* 471468: fld dword ptr [ebp] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x9ef928u)); FPOP();	/* 47146b: fcomp dword ptr [ecx + 0x9ef928] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471471: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471473: test ah, 0x41 */
	if (!m->zf) goto L_471486;	/* 471476: jne 0x471486 */
	m->eax = M32((DWORD)(m->ecx + 0x9ef928u));	/* 471478: mov eax, dword ptr [ecx + 0x9ef928] */
	M32((DWORD)(m->ebp + 0x0u)) = m->eax;	/* 47147e: mov dword ptr [ebp], eax */
L_471481:
	m->edx = 0x1u;	/* 471481: mov edx, 1 */
L_471486:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4u)));	/* 471486: fld dword ptr [ebp + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x9ef920u)); FPOP();	/* 471489: fcomp dword ptr [ecx + 0x9ef920] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47148f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 471491: test ah, 1 */
	if (m->zf) goto L_4714a1;	/* 471494: je 0x4714a1 */
	m->edx = M32((DWORD)(m->ecx + 0x9ef920u));	/* 471496: mov edx, dword ptr [ecx + 0x9ef920] */
	M32((DWORD)(m->ebp + 0x4u)) = m->edx;	/* 47149c: mov dword ptr [ebp + 4], edx */
	goto L_4714ba;	/* 47149f: jmp 0x4714ba */
L_4714a1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4u)));	/* 4714a1: fld dword ptr [ebp + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x9ef92cu)); FPOP();	/* 4714a4: fcomp dword ptr [ecx + 0x9ef92c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4714aa: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4714ac: test ah, 0x41 */
	if (!m->zf) goto L_4714bf;	/* 4714af: jne 0x4714bf */
	m->eax = M32((DWORD)(m->ecx + 0x9ef92cu));	/* 4714b1: mov eax, dword ptr [ecx + 0x9ef92c] */
	M32((DWORD)(m->ebp + 0x4u)) = m->eax;	/* 4714b7: mov dword ptr [ebp + 4], eax */
L_4714ba:
	m->edx = 0x1u;	/* 4714ba: mov edx, 1 */
L_4714bf:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8u)));	/* 4714bf: fld dword ptr [ebp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x9ef924u)); FPOP();	/* 4714c2: fcomp dword ptr [ecx + 0x9ef924] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4714c8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4714ca: test ah, 1 */
	if (m->zf) goto L_4714da;	/* 4714cd: je 0x4714da */
	m->edx = M32((DWORD)(m->ecx + 0x9ef924u));	/* 4714cf: mov edx, dword ptr [ecx + 0x9ef924] */
	M32((DWORD)(m->ebp + 0x8u)) = m->edx;	/* 4714d5: mov dword ptr [ebp + 8], edx */
	goto L_4714fa;	/* 4714d8: jmp 0x4714fa */
L_4714da:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8u)));	/* 4714da: fld dword ptr [ebp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x9ef930u)); FPOP();	/* 4714dd: fcomp dword ptr [ecx + 0x9ef930] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4714e3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4714e5: test ah, 0x41 */
	if (!m->zf) goto L_4714f5;	/* 4714e8: jne 0x4714f5 */
	m->eax = M32((DWORD)(m->ecx + 0x9ef930u));	/* 4714ea: mov eax, dword ptr [ecx + 0x9ef930] */
	M32((DWORD)(m->ebp + 0x8u)) = m->eax;	/* 4714f0: mov dword ptr [ebp + 8], eax */
	goto L_4714fa;	/* 4714f3: jmp 0x4714fa */
L_4714f5:
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4714f5: cmp edx, 1 */
	if (!m->zf) goto L_471531;	/* 4714f8: jne 0x471531 */
L_4714fa:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x0u)));	/* 4714fa: fld dword ptr [ebp] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 4714fd: fsub dword ptr [esi] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4714ff: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4u)));	/* 471503: fld dword ptr [ebp + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 471506: fsub dword ptr [esi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 471509: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 47150d: mov dword ptr [esp + 0x10], edx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 471511: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8u)));	/* 471515: fld dword ptr [ebp + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 471518: fsub dword ptr [esi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 47151b: mov eax, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 47151f: mov dword ptr [esp + 0x14], eax */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 471523: fstp dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 471527: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47152b: mov dword ptr [esp + 0x18], edx */
	goto L_471545;	/* 47152f: jmp 0x471545 */
L_471531:
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 471531: mov eax, dword ptr [edi] */
	m->edx = M32((DWORD)(m->edi + 0x4u));	/* 471533: mov edx, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 471536: mov dword ptr [esp + 0x10], eax */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 47153a: mov eax, dword ptr [edi + 8] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 47153d: mov dword ptr [esp + 0x14], edx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 471541: mov dword ptr [esp + 0x18], eax */
L_471545:
	m->eax = M32((DWORD)(m->ecx + 0x13c9b24u));	/* 471545: mov eax, dword ptr [ecx + 0x13c9b24] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 47154b: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47154d: cmp eax, edi */
	M32((DWORD)(m->esp + 0x30u)) = m->edi;	/* 47154f: mov dword ptr [esp + 0x30], edi */
	if (m->zf || m->sf != m->of) goto L_4716eb;	/* 471553: jle 0x4716eb */
	m->edx = (DWORD)(m->ecx + 0x9ca0f8u);	/* 471559: lea edx, [ecx + 0x9ca0f8] */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 47155f: mov dword ptr [esp + 0x34], edx */
L_471563:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 471563: test edi, edi */
	if (!m->zf) goto L_47158f;	/* 471565: jne 0x47158f */
	ST(0) = ST(0); FPOP();	/* 471567: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 471569: fld dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47156d: fld dword ptr [esp + 0x18] */
	{ long double t = ST(0); FPUSH(t); }	/* 471571: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 471573: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 471575: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 471577: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 471579: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47157b: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47157f: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 471583: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 471585: fsqrt  */
	ST(2) = ST(0); FPOP();	/* 471587: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 471589: fstp st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 47158b: fadd dword ptr [esp + 0x2c] */
L_47158f:
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 47158f: lea eax, [edi + edi*4] */
	m->eax = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 471592: lea eax, [eax + eax*8] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ << c_; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 471595: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 471598: sub eax, edi */
	m->ebx = M32((DWORD)(m->ecx + m->eax*4 + 0x131ae48u));	/* 47159a: mov ebx, dword ptr [ecx + eax*4 + 0x131ae48] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 4715a1: lea edx, [ecx + eax*4] */
	m->eax = 0x1u;	/* 4715a4: mov eax, 1 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4715a9: cmp ebx, eax */
	if (!m->zf) goto L_4716dc;	/* 4715ab: jne 0x4716dc */
	{ DWORD a_ = M32((DWORD)(m->edx + 0x131b0d4u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4715b1: cmp dword ptr [edx + 0x131b0d4], eax */
	if (!m->zf) goto L_4716dc;	/* 4715b7: jne 0x4716dc */
	m->eax = M32((DWORD)(m->edx + 0x131b0d0u));	/* 4715bd: mov eax, dword ptr [edx + 0x131b0d0] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 4715c3: mov eax, dword ptr [eax + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4715c6: test eax, eax */
	M32((DWORD)(m->esp + 0x40u)) = m->eax;	/* 4715c8: mov dword ptr [esp + 0x40], eax */
	if (m->zf) goto L_4716dc;	/* 4715cc: je 0x4716dc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131af98u)));	/* 4715d2: fld dword ptr [edx + 0x131af98] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 4715d8: fmul dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131af88u)));	/* 4715db: fld dword ptr [edx + 0x131af88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4715e1: fmul dword ptr [esi + 4] */
	m->ebx = M32((DWORD)(m->edx + 0x131b0c0u));	/* 4715e4: mov ebx, dword ptr [edx + 0x131b0c0] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4715ea: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131af78u)));	/* 4715ec: fld dword ptr [edx + 0x131af78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 4715f2: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4715f4: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x131afa8u));	/* 4715f6: fadd dword ptr [edx + 0x131afa8] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 4715fc: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131af7cu)));	/* 471600: fld dword ptr [edx + 0x131af7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 471606: fmul dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131af9cu)));	/* 471608: fld dword ptr [edx + 0x131af9c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 47160e: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 471611: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131af8cu)));	/* 471613: fld dword ptr [edx + 0x131af8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 471619: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47161c: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x131afacu));	/* 47161e: fadd dword ptr [edx + 0x131afac] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 471624: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131af80u)));	/* 471628: fld dword ptr [edx + 0x131af80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 47162e: fmul dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131afa0u)));	/* 471630: fld dword ptr [edx + 0x131afa0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 471636: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 471639: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x131af90u)));	/* 47163b: fld dword ptr [edx + 0x131af90] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 471641: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 471644: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edx + 0x131afb0u));	/* 471646: fadd dword ptr [edx + 0x131afb0] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47164c: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x34u)));	/* 471650: fld dword ptr [ebx + 0x34] */
	ST(0) = ST(0) - ST(1);	/* 471653: fsub st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu)); FPOP();	/* 471655: fcomp dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471659: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47165b: test ah, 1 */
	if (m->zf) goto L_4716dc;	/* 47165e: je 0x4716dc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x38u)));	/* 471660: fld dword ptr [ebx + 0x38] */
	ST(0) = ST(0) - ST(1);	/* 471663: fsub st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x20u)); FPOP();	/* 471665: fcomp dword ptr [esp + 0x20] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471669: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47166b: test ah, 1 */
	if (m->zf) goto L_4716dc;	/* 47166e: je 0x4716dc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x3cu)));	/* 471670: fld dword ptr [ebx + 0x3c] */
	ST(0) = ST(0) - ST(1);	/* 471673: fsub st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 471675: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471679: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47167b: test ah, 1 */
	if (m->zf) goto L_4716dc;	/* 47167e: je 0x4716dc */
	{ long double t = ST(0); FPUSH(t); }	/* 471680: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x40u));	/* 471682: fadd dword ptr [ebx + 0x40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu)); FPOP();	/* 471685: fcomp dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471689: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47168b: test ah, 0x41 */
	if (!m->zf) goto L_4716dc;	/* 47168e: jne 0x4716dc */
	{ long double t = ST(0); FPUSH(t); }	/* 471690: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x44u));	/* 471692: fadd dword ptr [ebx + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x20u)); FPOP();	/* 471695: fcomp dword ptr [esp + 0x20] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 471699: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47169b: test ah, 0x41 */
	if (!m->zf) goto L_4716dc;	/* 47169e: jne 0x4716dc */
	{ long double t = ST(0); FPUSH(t); }	/* 4716a0: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x48u));	/* 4716a2: fadd dword ptr [ebx + 0x48] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 4716a5: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4716a9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4716ab: test ah, 0x41 */
	if (!m->zf) goto L_4716dc;	/* 4716ae: jne 0x4716dc */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 4716b0: mov eax, dword ptr [esp + 0x34] */
	m->ebx = M32((DWORD)(m->esp + 0x40u));	/* 4716b4: mov ebx, dword ptr [esp + 0x40] */
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->ebx;	/* 4716b8: mov dword ptr [eax - 4], ebx */
	m->ebx = (DWORD)(m->edx + 0x131b038u);	/* 4716bb: lea ebx, [edx + 0x131b038] */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 4716c1: mov dword ptr [eax], ebx */
	m->ebx = M32((DWORD)(m->esp + 0x30u));	/* 4716c3: mov ebx, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->edx, b_ = 0x131b078u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4716c7: add edx, 0x131b078 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4716cd: inc ebx */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4716ce: mov dword ptr [eax + 4], edx */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4716d1: add eax, 0xc */
	M32((DWORD)(m->esp + 0x30u)) = m->ebx;	/* 4716d4: mov dword ptr [esp + 0x30], ebx */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 4716d8: mov dword ptr [esp + 0x34], eax */
L_4716dc:
	m->eax = M32((DWORD)(m->ecx + 0x13c9b24u));	/* 4716dc: mov eax, dword ptr [ecx + 0x13c9b24] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 4716e2: inc edi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4716e3: cmp edi, eax */
	if (m->sf != m->of) goto L_471563;	/* 4716e5: jl 0x471563 */
L_4716eb:
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 4716eb: mov edx, dword ptr [esp + 0x30] */
	m->eax = (DWORD)(m->ecx + 0x9ca0f4u);	/* 4716ef: lea eax, [ecx + 0x9ca0f4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4716f5: push edx */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 4716f6: mov edx, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4716fa: push eax */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 4716fb: mov eax, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4716ff: push edx */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 471700: mov edx, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 471704: push eax */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 471705: mov eax, dword ptr [esp + 0x54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 471709: push edx */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 47170a: mov edx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47170e: push eax */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 47170f: mov eax, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 471713: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 471714: push edx */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 471715: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 471719: push eax */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 47171a: mov eax, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47171e: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47171f: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 471720: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xa10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 471721: add ecx, 0xa10 */
	ST(0) = ST(0); FPOP();	/* 471727: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x47172eu; lift_482e30(m);	/* 471729: call 0x482e30 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47172e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47172f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 471730: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 471731: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 471732: add esp, 0x18 */
	m->esp += 4 + 40; return;	/* 471735: ret 0x28 */
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
