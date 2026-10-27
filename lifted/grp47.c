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

static void lift_45d3e0(X86 *m);

/* actor_updateAllParts (0x45d3e0), lifted by tools/lift.py */
static void lift_45d3e0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45d3e0: sub esp, 0x10 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d3e3: push ebx */
	m->ebx = m->ecx;	/* 45d3e4: mov ebx, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 45d3e6: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d3ea: push ebp */
	m->eax = m->ecx;	/* 45d3eb: mov eax, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45d3ed: push esi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45d3ee: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45d3f1: add eax, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45d3f3: push edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45d3f4: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45d3f7: add eax, ecx */
	m->edi = 0x1u;	/* 45d3f9: mov edi, 1 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45d3fe: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45d401: add eax, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->ebx;	/* 45d403: mov dword ptr [esp + 0x10], ebx */
	m->esi = (DWORD)(m->ebx + m->eax*8 + 0x1cd93a8u);	/* 45d407: lea esi, [ebx + eax*8 + 0x1cd93a8] */
	m->eax = M32((DWORD)(m->ebx + m->eax*8 + 0x1cd94f4u));	/* 45d40e: mov eax, dword ptr [ebx + eax*8 + 0x1cd94f4] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d415: cmp eax, edi */
	if (!m->zf) goto L_45daee;	/* 45d417: jne 0x45daee */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x884cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d41d: cmp dword ptr [esi + 0x884c], edi */
	if (m->zf) goto L_45daee;	/* 45d423: je 0x45daee */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0xa08u)));	/* 45d429: fld dword ptr [ebx + 0xa08] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x3e8u));	/* 45d42f: fadd dword ptr [esi + 0x3e8] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 45d435: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3970u)));	/* 45d439: fld dword ptr [ebx + 0x20f3970] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 45d43f: fsub dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x154u)); FPOP();	/* 45d443: fcomp dword ptr [esi + 0x154] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d449: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d44b: test ah, 0x41 */
	if (m->zf) goto L_45daee;	/* 45d44e: je 0x45daee */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3974u)));	/* 45d454: fld dword ptr [ebx + 0x20f3974] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 45d45a: fsub dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x158u)); FPOP();	/* 45d45e: fcomp dword ptr [esi + 0x158] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d464: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d466: test ah, 0x41 */
	if (m->zf) goto L_45daee;	/* 45d469: je 0x45daee */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20f3978u)));	/* 45d46f: fld dword ptr [ebx + 0x20f3978] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 45d475: fsub dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x15cu)); FPOP();	/* 45d479: fcomp dword ptr [esi + 0x15c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d47f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d481: test ah, 0x41 */
	if (m->zf) goto L_45daee;	/* 45d484: je 0x45daee */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 45d48a: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3970u));	/* 45d48e: fadd dword ptr [ebx + 0x20f3970] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x154u)); FPOP();	/* 45d494: fcomp dword ptr [esi + 0x154] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d49a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d49c: test ah, 1 */
	if (!m->zf) goto L_45daee;	/* 45d49f: jne 0x45daee */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 45d4a5: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3974u));	/* 45d4a9: fadd dword ptr [ebx + 0x20f3974] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x158u)); FPOP();	/* 45d4af: fcomp dword ptr [esi + 0x158] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d4b5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d4b7: test ah, 1 */
	if (!m->zf) goto L_45daee;	/* 45d4ba: jne 0x45daee */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 45d4c0: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x20f3978u));	/* 45d4c4: fadd dword ptr [ebx + 0x20f3978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esi + 0x15cu)); FPOP();	/* 45d4ca: fcomp dword ptr [esi + 0x15c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d4d0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d4d2: test ah, 1 */
	if (!m->zf) goto L_45daee;	/* 45d4d5: jne 0x45daee */
	m->eax = M32((DWORD)(m->esi + 0x3f0u));	/* 45d4db: mov eax, dword ptr [esi + 0x3f0] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d4e1: test ah, 2 */
	if (m->zf) goto L_45d533;	/* 45d4e4: je 0x45d533 */
	m->eax = M32((DWORD)(m->ebx + 0x202e8d4u));	/* 45d4e6: mov eax, dword ptr [ebx + 0x202e8d4] */
	m->ebp = M32((DWORD)(m->esi + 0x8u));	/* 45d4ec: mov ebp, dword ptr [esi + 8] */
	m->edx = m->eax;	/* 45d4ef: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45d4f1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45d4f4: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45d4f6: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45d4f9: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45d4fb: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45d4fe: add edx, eax */
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(m->ebx + m->edx*8 + 0x1cd93b0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d500: cmp ebp, dword ptr [ebx + edx*8 + 0x1cd93b0] */
	if (m->sf != m->of) goto L_45d533;	/* 45d507: jl 0x45d533 */
	m->ebp = (DWORD)(m->esi + 0x4f0u);	/* 45d509: lea ebp, [esi + 0x4f0] */
	m->edx = 0xffu;	/* 45d50f: mov edx, 0xff */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d514: cmp ecx, eax */
	M8((DWORD)(m->ebp + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 45d516: mov byte ptr [ebp], dl */
	M8((DWORD)(m->ebp + 0x1u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 45d519: mov byte ptr [ebp + 1], dl */
	M8((DWORD)(m->ebp + 0x2u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 45d51c: mov byte ptr [ebp + 2], dl */
	if (!m->zf) goto L_45d52a;	/* 45d51f: jne 0x45d52a */
	M8((DWORD)(m->ebp + 0x3u)) = (BYTE)(0x40u);	/* 45d521: mov byte ptr [ebp + 3], 0x40 */
	goto L_45d908;	/* 45d525: jmp 0x45d908 */
L_45d52a:
	M8((DWORD)(m->ebp + 0x3u)) = (BYTE)(0x10u);	/* 45d52a: mov byte ptr [ebp + 3], 0x10 */
	goto L_45d908;	/* 45d52e: jmp 0x45d908 */
L_45d533:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x120u)));	/* 45d533: fld dword ptr [esi + 0x120] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9534u)); FPOP();	/* 45d539: fcomp dword ptr [0x4a9534] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d53f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d541: test ah, 0x41 */
	if (m->zf) goto L_45d5af;	/* 45d544: je 0x45d5af */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x120u)));	/* 45d546: fld dword ptr [esi + 0x120] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a974cu)); FPOP();	/* 45d54c: fcomp dword ptr [0x4a974c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x120u)));	/* 45d552: fld dword ptr [esi + 0x120] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d558: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d55a: test ah, 1 */
	if (m->zf) goto L_45d581;	/* 45d55d: je 0x45d581 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9748u));	/* 45d55f: fmul dword ptr [0x4a9748] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45d565: call 0x49ec14 */
	m->ebp = (DWORD)(m->esi + 0x4f0u);	/* 45d56a: lea ebp, [esi + 0x4f0] */
	M8((DWORD)(m->ebp + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 45d570: mov byte ptr [ebp], al */
	M8((DWORD)(m->ebp + 0x1u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 45d573: mov byte ptr [ebp + 1], al */
	M8((DWORD)(m->ebp + 0x2u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 45d576: mov byte ptr [ebp + 2], al */
	M8((DWORD)(m->ebp + 0x3u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 45d579: mov byte ptr [ebp + 3], al */
	goto L_45d908;	/* 45d57c: jmp 0x45d908 */
L_45d581:
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a974cu));	/* 45d581: fsub dword ptr [0x4a974c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9748u));	/* 45d587: fmul dword ptr [0x4a9748] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45d58d: call 0x49ec14 */
	m->edx = 0xffu;	/* 45d592: mov edx, 0xff */
	m->ebp = (DWORD)(m->esi + 0x4f0u);	/* 45d597: lea ebp, [esi + 0x4f0] */
	m->ecx = m->edx;	/* 45d59d: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45d59f: sub ecx, eax */
	M8((DWORD)(m->ebp + 0x0u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 45d5a1: mov byte ptr [ebp], cl */
	M8((DWORD)(m->ebp + 0x1u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 45d5a4: mov byte ptr [ebp + 1], cl */
	M8((DWORD)(m->ebp + 0x2u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 45d5a7: mov byte ptr [ebp + 2], cl */
	goto L_45d905;	/* 45d5aa: jmp 0x45d905 */
L_45d5af:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4ecu)));	/* 45d5af: fld dword ptr [esi + 0x4ec] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d5b5: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d5bb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d5bd: test ah, 0x41 */
	if (m->zf) goto L_45d840;	/* 45d5c0: je 0x45d840 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8854u)));	/* 45d5c6: fld dword ptr [esi + 0x8854] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d5cc: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d5d2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d5d4: test ah, 0x41 */
	if (m->zf) goto L_45d840;	/* 45d5d7: je 0x45d840 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 45d5dd: xor ebp, ebp */
L_45d5df:
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 45d5df: mov dword ptr [esp + 0x14], 0 */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45d5e7: mov eax, dword ptr [esp + 0x14] */
L_45d5eb:
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 45d5eb: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->ebx + 0x202e8d8u));	/* 45d5ef: mov edx, dword ptr [ebx + 0x202e8d8] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d5f5: cmp ecx, edx */
	m->ecx = M32((DWORD)(m->esp + 0x2cu));	/* 45d5f7: mov ecx, dword ptr [esp + 0x2c] */
	if (m->zf) goto L_45daf8;	/* 45d5fb: je 0x45daf8 */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d601: cmp ecx, 1 */
	if (m->zf) goto L_45da9a;	/* 45d604: je 0x45da9a */
	m->ecx = M32((DWORD)(m->esi + 0x3f0u));	/* 45d60a: mov ecx, dword ptr [esi + 0x3f0] */
	m->ebx = M32((DWORD)(m->esp + 0x28u));	/* 45d610: mov ebx, dword ptr [esp + 0x28] */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0xdu & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d614: test ch, 0xd */
	if (m->zf) goto L_45d662;	/* 45d617: je 0x45d662 */
	m->eax = M32((DWORD)(0x83a9c8u));	/* 45d619: mov eax, dword ptr [0x83a9c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45d61e: test eax, eax */
	if (m->zf) goto L_45d80d;	/* 45d620: je 0x45d80d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x87d4u)));	/* 45d626: fld dword ptr [esi + 0x87d4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x87c8u));	/* 45d62c: fsub dword ptr [esi + 0x87c8] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 45d632: fstp dword ptr [esp + 0x2c] */
	m->esp -= 4; M32(m->esp) = 0x45d63bu; native_call(m, 0x4685b0u);	/* 45d636: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 45d63b: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 45d63f: fild dword ptr [esp + 0x28] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 45d643: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 45d649: fmul dword ptr [0x4a9414] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x2cu)); FPOP();	/* 45d64f: fcomp dword ptr [esp + 0x2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d653: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d655: test ah, 0x41 */
	if (m->zf) goto L_45d80d;	/* 45d658: je 0x45d80d */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45d65e: mov eax, dword ptr [esp + 0x14] */
L_45d662:
	{ DWORD a_ = M32((DWORD)(0x83a9c8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d662: cmp dword ptr [0x83a9c8], 1 */
	if (m->zf) goto L_45d679;	/* 45d669: je 0x45d679 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45d66b: test ebp, ebp */
	if (m->zf) goto L_45d679;	/* 45d66d: je 0x45d679 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x3u)), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 45d66f: cmp byte ptr [ebp + 3], 0x10 */
	if (m->cf || m->zf) goto L_45d80d;	/* 45d673: jbe 0x45d80d */
L_45d679:
	m->ecx = M32((DWORD)(m->esi + 0x54cu));	/* 45d679: mov ecx, dword ptr [esi + 0x54c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45d67f: test ecx, ecx */
	if (m->sf != m->of) goto L_45daee;	/* 45d681: jl 0x45daee */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 45d687: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d68b: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45d68c: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d68e: push 1 */
	m->ecx = (DWORD)(m->edx + 0x9e3020u);	/* 45d690: lea ecx, [edx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d696: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d697: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d698: push ebx */
	m->ecx = (DWORD)(m->esi + 0x554u);	/* 45d699: lea ecx, [esi + 0x554] */
	m->esp -= 4; M32(m->esp) = 0x45d6a4u; native_call(m, 0x46fd20u);	/* 45d69f: call 0x46fd20 */
	m->edi = m->eax;	/* 45d6a4: mov edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x54cu));	/* 45d6a6: mov eax, dword ptr [esi + 0x54c] */
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d6ac: and edi, 1 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d6af: cmp eax, 1 */
	if (m->sf != m->of) goto L_45daee;	/* 45d6b2: jl 0x45daee */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45d6b8: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d6bc: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6c0: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6c1: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6c3: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45d6c5: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6cb: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6cc: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6cd: push ebx */
	m->ecx = (DWORD)(m->esi + 0xd54u);	/* 45d6ce: lea ecx, [esi + 0xd54] */
	m->esp -= 4; M32(m->esp) = 0x45d6d9u; native_call(m, 0x46fd20u);	/* 45d6d4: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d6d9: and edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x54cu));	/* 45d6db: mov eax, dword ptr [esi + 0x54c] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d6e1: cmp eax, 2 */
	if (m->sf != m->of) goto L_45daee;	/* 45d6e4: jl 0x45daee */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 45d6ea: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 45d6ee: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6f2: push edx */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6f3: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6f5: push 1 */
	{ DWORD a_ = m->eax, b_ = 0x9e3020u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45d6f7: add eax, 0x9e3020 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6fc: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6fd: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d6fe: push ebx */
	m->ecx = (DWORD)(m->esi + 0x1554u);	/* 45d6ff: lea ecx, [esi + 0x1554] */
	m->esp -= 4; M32(m->esp) = 0x45d70au; native_call(m, 0x46fd20u);	/* 45d705: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d70a: and edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x54cu));	/* 45d70c: mov eax, dword ptr [esi + 0x54c] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d712: cmp eax, 3 */
	if (m->sf != m->of) goto L_45daee;	/* 45d715: jl 0x45daee */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 45d71b: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 45d71f: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d723: push ecx */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45d724: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d726: push 1 */
	m->eax = (DWORD)(m->edx + 0x9e3020u);	/* 45d728: lea eax, [edx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d72e: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d72f: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d730: push ebx */
	m->ecx = (DWORD)(m->esi + 0x2524u);	/* 45d731: lea ecx, [esi + 0x2524] */
	m->esp -= 4; M32(m->esp) = 0x45d73cu; native_call(m, 0x46fd20u);	/* 45d737: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d73c: and edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x54cu));	/* 45d73e: mov eax, dword ptr [esi + 0x54c] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d744: cmp eax, 4 */
	if (m->sf != m->of) goto L_45daee;	/* 45d747: jl 0x45daee */
	m->eax = M32((DWORD)(m->esi + 0x550u));	/* 45d74d: mov eax, dword ptr [esi + 0x550] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45d753: test eax, eax */
	if (!m->zf) goto L_45d77a;	/* 45d755: jne 0x45d77a */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45d757: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d75b: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d75f: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45d760: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d762: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45d764: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d76a: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d76b: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d76c: push ebx */
	m->ecx = (DWORD)(m->esi + 0x34f4u);	/* 45d76d: lea ecx, [esi + 0x34f4] */
	m->esp -= 4; M32(m->esp) = 0x45d778u; native_call(m, 0x46fd20u);	/* 45d773: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d778: and edi, eax */
L_45d77a:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x54cu)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d77a: cmp dword ptr [esi + 0x54c], 5 */
	if (m->sf != m->of) goto L_45daee;	/* 45d781: jl 0x45daee */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 45d787: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 45d78b: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d78f: push edx */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45d790: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d792: push 1 */
	{ DWORD a_ = m->eax, b_ = 0x9e3020u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45d794: add eax, 0x9e3020 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d799: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d79a: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d79b: push ebx */
	m->ecx = (DWORD)(m->esi + 0x587cu);	/* 45d79c: lea ecx, [esi + 0x587c] */
	m->esp -= 4; M32(m->esp) = 0x45d7a7u; native_call(m, 0x46fd20u);	/* 45d7a2: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d7a7: and edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x54cu));	/* 45d7a9: mov eax, dword ptr [esi + 0x54c] */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d7af: cmp eax, 6 */
	if (m->sf != m->of) goto L_45daee;	/* 45d7b2: jl 0x45daee */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 45d7b8: mov ecx, dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 45d7bc: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7c0: push ecx */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7c1: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7c3: push 1 */
	m->eax = (DWORD)(m->edx + 0x9e3020u);	/* 45d7c5: lea eax, [edx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7cb: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7cc: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7cd: push ebx */
	m->ecx = (DWORD)(m->esi + 0x701cu);	/* 45d7ce: lea ecx, [esi + 0x701c] */
	m->esp -= 4; M32(m->esp) = 0x45d7d9u; native_call(m, 0x46fd20u);	/* 45d7d4: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d7d9: and edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x54cu));	/* 45d7db: mov eax, dword ptr [esi + 0x54c] */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d7e1: cmp eax, 7 */
	if (m->sf != m->of) goto L_45daee;	/* 45d7e4: jl 0x45daee */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45d7ea: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d7ee: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7f2: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7f3: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7f5: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45d7f7: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7fd: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7fe: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d7ff: push ebx */
	m->ecx = (DWORD)(m->esi + 0x40dcu);	/* 45d800: lea ecx, [esi + 0x40dc] */
	m->esp -= 4; M32(m->esp) = 0x45d80bu; native_call(m, 0x46fd20u);	/* 45d806: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d80b: and edi, eax */
L_45d80d:
	m->ecx = M32((DWORD)(m->esi + 0x3f0u));	/* 45d80d: mov ecx, dword ptr [esi + 0x3f0] */
	m->eax = m->ecx;	/* 45d813: mov eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45d815: and eax, 0x100 */
	if (!m->zf) goto L_45d825;	/* 45d81a: jne 0x45d825 */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0xcu & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d81c: test ch, 0xc */
	if (m->zf) goto L_45da96;	/* 45d81f: je 0x45da96 */
L_45d825:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45d825: test eax, eax */
	if (m->zf) goto L_45d929;	/* 45d827: je 0x45d929 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 45d82d: mov edx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->edx + 0x20f2f3cu));	/* 45d831: mov eax, dword ptr [edx + 0x20f2f3c] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 45d837: mov dword ptr [esp + 0x28], eax */
	goto L_45d94c;	/* 45d83b: jmp 0x45d94c */
L_45d840:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4ecu)));	/* 45d840: fld dword ptr [esi + 0x4ec] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d846: fcomp dword ptr [0x4a93e8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45d84c: xor eax, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 45d84e: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 45d852: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 45d856: mov dword ptr [esp + 0x1c], eax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d85a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d85c: test ah, 0x41 */
	if (!m->zf) goto L_45d87e;	/* 45d85f: jne 0x45d87e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4ecu)));	/* 45d861: fld dword ptr [esi + 0x4ec] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 45d867: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45d86d: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 45d872: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 45d876: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 45d87a: mov dword ptr [esp + 0x1c], eax */
L_45d87e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8854u)));	/* 45d87e: fld dword ptr [esi + 0x8854] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 45d884: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45d88a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d88c: test ah, 0x41 */
	if (!m->zf) goto L_45d8c5;	/* 45d88f: jne 0x45d8c5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8854u)));	/* 45d891: fld dword ptr [esi + 0x8854] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9744u));	/* 45d897: fmul dword ptr [0x4a9744] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45d89d: call 0x49ec14 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 45d8a2: mov edx, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 45d8a6: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45d8aa: add edx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 45d8ac: mov dword ptr [esp + 0x14], edx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 45d8b0: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45d8b1: sub eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 45d8b3: mov edx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45d8b7: sar eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45d8b9: add edx, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45d8bb: add ecx, eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 45d8bd: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 45d8c1: mov dword ptr [esp + 0x1c], ecx */
L_45d8c5:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 45d8c5: mov eax, dword ptr [esp + 0x14] */
	m->edx = 0xffu;	/* 45d8c9: mov edx, 0xff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d8ce: cmp eax, edx */
	if (m->zf || m->sf != m->of) goto L_45d8d6;	/* 45d8d0: jle 0x45d8d6 */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 45d8d2: mov dword ptr [esp + 0x14], edx */
L_45d8d6:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x18u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d8d6: cmp dword ptr [esp + 0x18], edx */
	if (m->zf || m->sf != m->of) goto L_45d8e0;	/* 45d8da: jle 0x45d8e0 */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 45d8dc: mov dword ptr [esp + 0x18], edx */
L_45d8e0:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x1cu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45d8e0: cmp dword ptr [esp + 0x1c], edx */
	if (m->zf || m->sf != m->of) goto L_45d8ea;	/* 45d8e4: jle 0x45d8ea */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 45d8e6: mov dword ptr [esp + 0x1c], edx */
L_45d8ea:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x14u))) & 0xff) << 0);	/* 45d8ea: mov al, byte ptr [esp + 0x14] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x18u))) & 0xff) << 0);	/* 45d8ee: mov cl, byte ptr [esp + 0x18] */
	m->ebp = (DWORD)(m->esi + 0x4f0u);	/* 45d8f2: lea ebp, [esi + 0x4f0] */
	M8((DWORD)(m->ebp + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 45d8f8: mov byte ptr [ebp], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x1cu))) & 0xff) << 0);	/* 45d8fb: mov al, byte ptr [esp + 0x1c] */
	M8((DWORD)(m->ebp + 0x1u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 45d8ff: mov byte ptr [ebp + 1], cl */
	M8((DWORD)(m->ebp + 0x2u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 45d902: mov byte ptr [ebp + 2], al */
L_45d905:
	M8((DWORD)(m->ebp + 0x3u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 45d905: mov byte ptr [ebp + 3], dl */
L_45d908:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45d908: test ebp, ebp */
	if (m->zf) goto L_45d5df;	/* 45d90a: je 0x45d5df */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0x3u)), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 45d910: cmp byte ptr [ebp + 3], 0x10 */
	if (!m->cf && !m->zf) goto L_45d5df;	/* 45d914: ja 0x45d5df */
	m->eax = (DWORD)(m->ebx + 0x20f2f48u);	/* 45d91a: lea eax, [ebx + 0x20f2f48] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 45d920: mov dword ptr [esp + 0x14], eax */
	goto L_45d5eb;	/* 45d924: jmp 0x45d5eb */
L_45d929:
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x8u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45d929: test ch, 8 */
	if (m->zf) goto L_45d93e;	/* 45d92c: je 0x45d93e */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d92e: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->ecx + 0x20f2f44u));	/* 45d932: mov edx, dword ptr [ecx + 0x20f2f44] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 45d938: mov dword ptr [esp + 0x28], edx */
	goto L_45d94c;	/* 45d93c: jmp 0x45d94c */
L_45d93e:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 45d93e: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->eax + 0x20f2f40u));	/* 45d942: mov ecx, dword ptr [eax + 0x20f2f40] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 45d948: mov dword ptr [esp + 0x28], ecx */
L_45d94c:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d94c: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 45d950: mov edx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->ecx + 0x20f2f88u);	/* 45d954: lea eax, [ecx + 0x20f2f88] */
	{ DWORD a_ = m->ecx, b_ = 0x9e3020u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45d95a: add ecx, 0x9e3020 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d960: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d961: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d962: push 1 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d964: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d965: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d966: push ebx */
	m->ecx = (DWORD)(m->esi + 0x554u);	/* 45d967: lea ecx, [esi + 0x554] */
	m->esp -= 4; M32(m->esp) = 0x45d972u; native_call(m, 0x46fd20u);	/* 45d96d: call 0x46fd20 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d972: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d976: and edi, eax */
	m->eax = (DWORD)(m->ecx + 0x20f2f88u);	/* 45d978: lea eax, [ecx + 0x20f2f88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d97e: push eax */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 45d97f: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d983: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d984: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45d986: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d98c: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d98d: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d98e: push ebx */
	m->ecx = (DWORD)(m->esi + 0xd54u);	/* 45d98f: lea ecx, [esi + 0xd54] */
	m->esp -= 4; M32(m->esp) = 0x45d99au; native_call(m, 0x46fd20u);	/* 45d995: call 0x46fd20 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d99a: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 45d99e: mov edx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d9a2: and edi, eax */
	m->eax = (DWORD)(m->ecx + 0x20f2f88u);	/* 45d9a4: lea eax, [ecx + 0x20f2f88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9aa: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9ab: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9ac: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45d9ae: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9b4: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9b5: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9b6: push ebx */
	m->ecx = (DWORD)(m->esi + 0x1554u);	/* 45d9b7: lea ecx, [esi + 0x1554] */
	m->esp -= 4; M32(m->esp) = 0x45d9c2u; native_call(m, 0x46fd20u);	/* 45d9bd: call 0x46fd20 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d9c2: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d9c6: and edi, eax */
	m->eax = (DWORD)(m->ecx + 0x20f2f88u);	/* 45d9c8: lea eax, [ecx + 0x20f2f88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9ce: push eax */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 45d9cf: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9d3: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9d4: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45d9d6: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9dc: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9dd: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45d9de: push ebx */
	m->ecx = (DWORD)(m->esi + 0x2524u);	/* 45d9df: lea ecx, [esi + 0x2524] */
	m->esp -= 4; M32(m->esp) = 0x45d9eau; native_call(m, 0x46fd20u);	/* 45d9e5: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45d9ea: and edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x550u));	/* 45d9ec: mov eax, dword ptr [esi + 0x550] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45d9f2: test eax, eax */
	if (!m->zf) goto L_45da1e;	/* 45d9f4: jne 0x45da1e */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45d9f6: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 45d9fa: mov edx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->ecx + 0x20f2f88u);	/* 45d9fe: lea eax, [ecx + 0x20f2f88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da04: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45da05: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45da06: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45da08: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45da0e: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da0f: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45da10: push ebx */
	m->ecx = (DWORD)(m->esi + 0x34f4u);	/* 45da11: lea ecx, [esi + 0x34f4] */
	m->esp -= 4; M32(m->esp) = 0x45da1cu; native_call(m, 0x46fd20u);	/* 45da17: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45da1c: and edi, eax */
L_45da1e:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45da1e: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ecx + 0x20f2f88u);	/* 45da22: lea eax, [ecx + 0x20f2f88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da28: push eax */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 45da29: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da2d: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45da2e: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45da30: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45da36: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da37: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45da38: push ebx */
	m->ecx = (DWORD)(m->esi + 0x587cu);	/* 45da39: lea ecx, [esi + 0x587c] */
	m->esp -= 4; M32(m->esp) = 0x45da44u; native_call(m, 0x46fd20u);	/* 45da3f: call 0x46fd20 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45da44: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 45da48: mov edx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45da4c: and edi, eax */
	m->eax = (DWORD)(m->ecx + 0x20f2f88u);	/* 45da4e: lea eax, [ecx + 0x20f2f88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da54: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45da55: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45da56: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45da58: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45da5e: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da5f: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45da60: push ebx */
	m->ecx = (DWORD)(m->esi + 0x701cu);	/* 45da61: lea ecx, [esi + 0x701c] */
	m->esp -= 4; M32(m->esp) = 0x45da6cu; native_call(m, 0x46fd20u);	/* 45da67: call 0x46fd20 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 45da6c: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45da70: and edi, eax */
	m->eax = (DWORD)(m->ecx + 0x20f2f88u);	/* 45da72: lea eax, [ecx + 0x20f2f88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da78: push eax */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 45da79: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da7d: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45da7e: push 1 */
	m->eax = (DWORD)(m->ecx + 0x9e3020u);	/* 45da80: lea eax, [ecx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45da86: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45da87: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45da88: push ebx */
	m->ecx = (DWORD)(m->esi + 0x40dcu);	/* 45da89: lea ecx, [esi + 0x40dc] */
	m->esp -= 4; M32(m->esp) = 0x45da94u; native_call(m, 0x46fd20u);	/* 45da8f: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45da94: and edi, eax */
L_45da96:
	m->ebx = M32((DWORD)(m->esp + 0x10u));	/* 45da96: mov ebx, dword ptr [esp + 0x10] */
L_45da9a:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45da9a: test edi, edi */
	M32((DWORD)(m->esi + 0x550u)) = 0x0u;	/* 45da9c: mov dword ptr [esi + 0x550], 0 */
	if (!m->zf) goto L_45daee;	/* 45daa6: jne 0x45daee */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 45daa8: mov eax, dword ptr [esp + 0x24] */
	m->ecx = m->ebx;	/* 45daac: mov ecx, ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45daae: push eax */
	m->esp -= 4; M32(m->esp) = 0x45dab4u; native_call(m, 0x45e1f0u);	/* 45daaf: call 0x45e1f0 */
	m->ebp = M32((DWORD)(m->esp + 0x24u));	/* 45dab4: mov ebp, dword ptr [esp + 0x24] */
	m->ecx = m->ebx;	/* 45dab8: mov ecx, ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45daba: push ebp */
	m->esp -= 4; M32(m->esp) = 0x45dac0u; native_call(m, 0x45e2c0u);	/* 45dabb: call 0x45e2c0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45dac0: push ebp */
	m->ecx = m->ebx;	/* 45dac1: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45dac8u; native_call(m, 0x45e390u);	/* 45dac3: call 0x45e390 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45dac8: push ebp */
	m->ecx = m->ebx;	/* 45dac9: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45dad0u; native_call(m, 0x45e460u);	/* 45dacb: call 0x45e460 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45dad0: push ebp */
	m->ecx = m->ebx;	/* 45dad1: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45dad8u; native_call(m, 0x45e530u);	/* 45dad3: call 0x45e530 */
L_45dad8:
	m->ecx = M32((DWORD)(m->esi + 0x49cu));	/* 45dad8: mov ecx, dword ptr [esi + 0x49c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dade: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45dadf: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45dae0: push ebp */
	m->ecx = m->ebx;	/* 45dae1: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x45dae8u; native_call(m, 0x45e600u);	/* 45dae3: call 0x45e600 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 45dae8: inc edi */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45dae9: cmp edi, 6 */
	if (m->sf != m->of) goto L_45dad8;	/* 45daec: jl 0x45dad8 */
L_45daee:
	m->edi = M32(m->esp); m->esp += 4;	/* 45daee: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45daef: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45daf0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45daf1: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45daf2: add esp, 0x10 */
	m->esp += 4 + 12; return;	/* 45daf5: ret 0xc */
L_45daf8:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45daf8: test ecx, ecx */
	if (m->zf) goto L_45da9a;	/* 45dafa: je 0x45da9a */
	m->ecx = M32((DWORD)(m->esi + 0x140u));	/* 45dafc: mov ecx, dword ptr [esi + 0x140] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45db02: cmp ecx, 4 */
	if (!m->zf) goto L_45db21;	/* 45db05: jne 0x45db21 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45db07: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45db08: push -1 */
	m->ecx = (DWORD)(m->ebx + 0x9e3020u);	/* 45db0a: lea ecx, [ebx + 0x9e3020] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45db10: push 1 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45db12: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45db13: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 45db14: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45db18: push ecx */
	m->ecx = (DWORD)(m->esi + 0x587cu);	/* 45db19: lea ecx, [esi + 0x587c] */
	goto L_45db4b;	/* 45db1f: jmp 0x45db4b */
L_45db21:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45db21: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45db22: cmp ecx, 5 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45db25: push -1 */
	m->ecx = (DWORD)(m->ebx + 0x9e3020u);	/* 45db27: lea ecx, [ebx + 0x9e3020] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45db2d: push 1 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45db2f: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45db30: push ecx */
	if (!m->zf) goto L_45db40;	/* 45db31: jne 0x45db40 */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 45db33: mov edx, dword ptr [esp + 0x3c] */
	m->ecx = (DWORD)(m->esi + 0x701cu);	/* 45db37: lea ecx, [esi + 0x701c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45db3d: push edx */
	goto L_45db4b;	/* 45db3e: jmp 0x45db4b */
L_45db40:
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 45db40: mov eax, dword ptr [esp + 0x3c] */
	m->ecx = (DWORD)(m->esi + 0x40dcu);	/* 45db44: lea ecx, [esi + 0x40dc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45db4a: push eax */
L_45db4b:
	m->esp -= 4; M32(m->esp) = 0x45db50u; native_call(m, 0x46fd20u);	/* 45db4b: call 0x46fd20 */
	m->ecx = M32((DWORD)(m->esi + 0x3f0u));	/* 45db50: mov ecx, dword ptr [esi + 0x3f0] */
	m->edi = m->eax;	/* 45db56: mov edi, eax */
	m->eax = m->ecx;	/* 45db58: mov eax, ecx */
	{ DWORD a_ = m->edi, b_ = 0x1u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45db5a: and edi, 1 */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45db5d: and eax, 0x100 */
	if (!m->zf) goto L_45db6d;	/* 45db62: jne 0x45db6d */
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0xcu & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45db64: test ch, 0xc */
	if (m->zf) goto L_45da9a;	/* 45db67: je 0x45da9a */
L_45db6d:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45db6d: test eax, eax */
	if (m->zf) goto L_45db79;	/* 45db6f: je 0x45db79 */
	m->eax = M32((DWORD)(m->ebx + 0x20f2f3cu));	/* 45db71: mov eax, dword ptr [ebx + 0x20f2f3c] */
	goto L_45db8c;	/* 45db77: jmp 0x45db8c */
L_45db79:
	{ DWORD a_ = ((m->ecx >> 8) & 0xff), b_ = 0x8u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45db79: test ch, 8 */
	if (m->zf) goto L_45db86;	/* 45db7c: je 0x45db86 */
	m->eax = M32((DWORD)(m->ebx + 0x20f2f44u));	/* 45db7e: mov eax, dword ptr [ebx + 0x20f2f44] */
	goto L_45db8c;	/* 45db84: jmp 0x45db8c */
L_45db86:
	m->eax = M32((DWORD)(m->ebx + 0x20f2f40u));	/* 45db86: mov eax, dword ptr [ebx + 0x20f2f40] */
L_45db8c:
	m->ecx = M32((DWORD)(m->esi + 0x140u));	/* 45db8c: mov ecx, dword ptr [esi + 0x140] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45db92: cmp ecx, 4 */
	if (!m->zf) goto L_45dbc0;	/* 45db95: jne 0x45dbc0 */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 45db97: mov edx, dword ptr [esp + 0x28] */
	m->ecx = (DWORD)(m->ebx + 0x20f2f88u);	/* 45db9b: lea ecx, [ebx + 0x20f2f88] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dba1: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45dba2: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45dba3: push 1 */
	m->eax = (DWORD)(m->ebx + 0x9e3020u);	/* 45dba5: lea eax, [ebx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbab: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbac: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbad: push edx */
	m->ecx = (DWORD)(m->esi + 0x587cu);	/* 45dbae: lea ecx, [esi + 0x587c] */
	m->esp -= 4; M32(m->esp) = 0x45dbb9u; native_call(m, 0x46fd20u);	/* 45dbb4: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45dbb9: and edi, eax */
	goto L_45da9a;	/* 45dbbb: jmp 0x45da9a */
L_45dbc0:
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 45dbc0: mov edx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ecx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45dbc4: cmp ecx, 5 */
	m->ecx = (DWORD)(m->ebx + 0x20f2f88u);	/* 45dbc7: lea ecx, [ebx + 0x20f2f88] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbcd: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbce: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbcf: push 1 */
	m->eax = (DWORD)(m->ebx + 0x9e3020u);	/* 45dbd1: lea eax, [ebx + 0x9e3020] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbd7: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbd8: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45dbd9: push edx */
	if (!m->zf) goto L_45dbee;	/* 45dbda: jne 0x45dbee */
	m->ecx = (DWORD)(m->esi + 0x701cu);	/* 45dbdc: lea ecx, [esi + 0x701c] */
	m->esp -= 4; M32(m->esp) = 0x45dbe7u; native_call(m, 0x46fd20u);	/* 45dbe2: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45dbe7: and edi, eax */
	goto L_45da9a;	/* 45dbe9: jmp 0x45da9a */
L_45dbee:
	m->ecx = (DWORD)(m->esi + 0x40dcu);	/* 45dbee: lea ecx, [esi + 0x40dc] */
	m->esp -= 4; M32(m->esp) = 0x45dbf9u; native_call(m, 0x46fd20u);	/* 45dbf4: call 0x46fd20 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45dbf9: and edi, eax */
	goto L_45da9a;	/* 45dbfb: jmp 0x45da9a */
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
