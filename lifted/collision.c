/* ---- emulated machine for lifted functions (tools/lift.py) ---- */
typedef struct { DWORD eax, ecx, edx, ebx, esp, ebp, esi, edi; int zf, sf, cf, of; long double fs[8]; int ft; DWORD fsw; } X86;
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

static void lift_47dd90(X86 *m);
static void lift_4722c0(X86 *m);
static void lift_467760(X86 *m);
static void lift_480210(X86 *m);
static void lift_480230(X86 *m);
static void lift_480250(X86 *m);
static void lift_4802b0(X86 *m);
static void lift_4802d0(X86 *m);
static void lift_480320(X86 *m);
static void lift_480370(X86 *m);
static void lift_4803c0(X86 *m);
static void lift_480400(X86 *m);
static void lift_4809d0(X86 *m);
static void lift_4804b0(X86 *m);

/* space_collideUnit (0x4804b0), lifted by tools/lift.py */
static void lift_4804b0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x78u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4804b0: sub esp, 0x78 */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 4804b3: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4804ba: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4804bb: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4804bc: push esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4804bd: fld dword ptr [eax] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4804bf: push edi */
	m->edi = M32((DWORD)(m->esp + 0x94u));	/* 4804c0: mov edi, dword ptr [esp + 0x94] */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 4804c7: mov dword ptr [esp + 0x2c], ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4804cb: xor ebx, ebx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 4804cd: fadd dword ptr [edi] */
	m->ecx = M32((DWORD)(m->esp + 0x9cu));	/* 4804cf: mov ecx, dword ptr [esp + 0x9c] */
	M32((DWORD)(m->esp + 0x14u)) = m->ebx;	/* 4804d6: mov dword ptr [esp + 0x14], ebx */
	M32((DWORD)(m->esp + 0x20u)) = m->ebx;	/* 4804da: mov dword ptr [esp + 0x20], ebx */
	M32((DWORD)(m->esp + 0x28u)) = m->ebx;	/* 4804de: mov dword ptr [esp + 0x28], ebx */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 4804e2: fstp dword ptr [esp + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4804e6: fld dword ptr [eax + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 4804e9: fadd dword ptr [edi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x6cu));	/* 4804ec: mov edx, dword ptr [esp + 0x6c] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 4804f0: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4804f4: fld dword ptr [eax + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 4804f7: fadd dword ptr [edi + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 4804fa: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x70u));	/* 4804fc: mov edx, dword ptr [esp + 0x70] */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 480500: fstp dword ptr [esp + 0x74] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 480504: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 480507: mov edx, dword ptr [esp + 0x74] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 48050b: mov dword ptr [ecx + 8], edx */
	m->ebp = M32((DWORD)(m->edi + 0x0u));	/* 48050e: mov ebp, dword ptr [edi] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 480510: mov ecx, dword ptr [eax] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 480512: mov edx, dword ptr [eax + 4] */
	m->esi = M32((DWORD)(m->eax + 0x8u));	/* 480515: mov esi, dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 480518: mov eax, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 48051b: mov dword ptr [esp + 0x34], eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 48051f: mov dword ptr [esp + 0x3c], ecx */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 480523: mov eax, dword ptr [edi + 8] */
	m->edi = M32((DWORD)(m->esp + 0xa0u));	/* 480526: mov edi, dword ptr [esp + 0xa0] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 48052d: mov dword ptr [esp + 0x40], edx */
	M32((DWORD)(m->esp + 0x44u)) = m->esi;	/* 480531: mov dword ptr [esp + 0x44], esi */
	M32((DWORD)(m->esp + 0x30u)) = m->ebp;	/* 480535: mov dword ptr [esp + 0x30], ebp */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 480539: mov dword ptr [esp + 0x38], eax */
L_48053d:
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 48053d: mov eax, dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 480541: mov dword ptr [esp + 0x6c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 480545: mov ecx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 480549: mov dword ptr [esp + 0x70], edx */
	m->ebx = M32((DWORD)(m->eax + 0x18u));	/* 48054d: mov ebx, dword ptr [eax + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0xb0u));	/* 480550: mov eax, dword ptr [esp + 0xb0] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 480557: mov edx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x74u)) = m->esi;	/* 48055b: mov dword ptr [esp + 0x74], esi */
	M32((DWORD)(m->esp + 0x18u)) = 0xffffffffu;	/* 48055f: mov dword ptr [esp + 0x18], 0xffffffff */
	M32((DWORD)(m->esp + 0x24u)) = 0x0u;	/* 480567: mov dword ptr [esp + 0x24], 0 */
	M32((DWORD)(m->esp + 0x10u)) = 0xff7fffffu;	/* 48056f: mov dword ptr [esp + 0x10], 0xff7fffff */
	M32((DWORD)(m->esp + 0x60u)) = m->ebp;	/* 480577: mov dword ptr [esp + 0x60], ebp */
	M32((DWORD)(m->esp + 0x64u)) = m->ecx;	/* 48057b: mov dword ptr [esp + 0x64], ecx */
	M32((DWORD)(m->esp + 0x68u)) = m->edx;	/* 48057f: mov dword ptr [esp + 0x68], edx */
	m->esi = (DWORD)(m->eax + 0xfffffff8u);	/* 480583: lea esi, [eax - 8] */
L_480586:
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 480586: mov ebp, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48058a: test ebx, ebx */
	if (!m->zf) goto L_480667;	/* 48058c: jne 0x480667 */
	m->eax = M32((DWORD)(m->esp + 0xb4u));	/* 480592: mov eax, dword ptr [esp + 0xb4] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 480599: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48059a: add esi, 0xc */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48059d: cmp ebp, eax */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 48059f: mov dword ptr [esp + 0x18], ebp */
	if (m->sf == m->of) goto L_4808d0;	/* 4805a3: jge 0x4808d0 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 4805a9: mov eax, dword ptr [esi + 4] */
	m->ebx = M32((DWORD)(m->esi + 0xfffffffcu));	/* 4805ac: mov ebx, dword ptr [esi - 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4805af: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 4805b3: fmul dword ptr [eax + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4805b6: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 4805ba: fmul dword ptr [eax + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4805bd: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4805bf: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4805c3: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4805c5: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 4805c7: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 4805ca: fstp dword ptr [esp + 0x6c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4805ce: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 4805d2: fmul dword ptr [eax + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4805d5: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 4805d9: fmul dword ptr [eax + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4805dc: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4805de: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4805e2: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4805e5: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 4805e7: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 4805ea: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4805ee: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 4805f2: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4805f5: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 4805f9: fmul dword ptr [eax + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4805fc: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4805fe: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 480602: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480605: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 480607: fadd dword ptr [eax + 0x38] */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 48060a: fstp dword ptr [esp + 0x74] */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 48060e: mov eax, dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 480611: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 480615: fmul dword ptr [eax + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 480618: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 48061c: fmul dword ptr [eax + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48061f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 480621: fld dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 480625: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480627: faddp st(1) */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 480629: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48062d: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 480631: fmul dword ptr [eax + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 480634: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 480638: fmul dword ptr [eax + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48063b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 48063d: fld dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 480641: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480644: faddp st(1) */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 480646: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48064a: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 48064e: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 480651: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 480655: fmul dword ptr [eax + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480658: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 48065a: fld dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 48065e: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480661: faddp st(1) */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 480663: fstp dword ptr [esp + 0x68] */
L_480667:
	{ DWORD a_ = m->ebx, b_ = M32((DWORD)(m->esp + 0x20u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 480667: cmp ebx, dword ptr [esp + 0x20] */
	if (m->zf) goto L_4808c8;	/* 48066b: je 0x4808c8 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480671: test ebp, ebp */
	if (m->sf == m->of) goto L_480680;	/* 480673: jge 0x480680 */
	m->ecx = M32((DWORD)(m->ebx + 0x0u));	/* 480675: mov ecx, dword ptr [ebx] */
	{ DWORD a_ = M8((DWORD)(m->ecx + 0x0u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 480677: test byte ptr [ecx], 1 */
	if (!m->zf) goto L_4808c8;	/* 48067a: jne 0x4808c8 */
L_480680:
	m->edx = M32((DWORD)(m->esp + 0xacu));	/* 480680: mov edx, dword ptr [esp + 0xac] */
	m->eax = (DWORD)(m->esp + 0x78u);	/* 480687: lea eax, [esp + 0x78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48068b: push edx */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 48068c: lea ecx, [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 480690: push eax */
	m->edx = (DWORD)(m->esp + 0x5cu);	/* 480691: lea edx, [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 480695: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0xa4u));	/* 480696: mov ecx, dword ptr [esp + 0xa4] */
	m->eax = (DWORD)(m->esp + 0x54u);	/* 48069d: lea eax, [esp + 0x54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4806a1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4806a2: push eax */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 4806a3: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4806a7: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0xa4u));	/* 4806a8: mov ecx, dword ptr [esp + 0xa4] */
	m->eax = (DWORD)(m->esp + 0x84u);	/* 4806af: lea eax, [esp + 0x84] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4806b6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4806b7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4806b8: push ecx */
	m->ecx = M32((DWORD)(m->ebx + 0x0u));	/* 4806b9: mov ecx, dword ptr [ebx] */
	m->esp -= 4; M32(m->esp) = 0x4806c0u; lift_47dd90(m);	/* 4806bb: call 0x47dd90 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4806c0: cmp eax, 1 */
	if (!m->zf) goto L_4808c8;	/* 4806c3: jne 0x4808c8 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4806c9: fld dword ptr [esp + 0x1c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 4806cd: fcomp dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4806d1: mov dword ptr [esp + 0x24], eax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4806d5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4806d7: test ah, 0x41 */
	if (!m->zf) goto L_4808c8;	/* 4806da: jne 0x4808c8 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4806e0: test ebp, ebp */
	if (m->sf == m->of) goto L_480751;	/* 4806e2: jge 0x480751 */
	m->edx = M32((DWORD)(m->esp + 0x9cu));	/* 4806e4: mov edx, dword ptr [esp + 0x9c] */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 4806eb: mov eax, dword ptr [esp + 0x48] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 4806ef: mov ecx, dword ptr [esp + 0x4c] */
	M32((DWORD)(m->esp + 0x20u)) = m->ebx;	/* 4806f3: mov dword ptr [esp + 0x20], ebx */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 4806f7: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 4806f9: mov eax, dword ptr [esp + 0x50] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 4806fd: mov dword ptr [edx + 4], ecx */
	m->ecx = m->edi;	/* 480700: mov ecx, edi */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 480702: mov dword ptr [edx + 8], eax */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 480705: mov edx, dword ptr [esp + 0x54] */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 480709: mov eax, dword ptr [esp + 0x58] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 48070d: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 48070f: mov edx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 480713: mov dword ptr [ecx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0xa8u));	/* 480716: mov eax, dword ptr [esp + 0xa8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 48071d: mov dword ptr [ecx + 8], edx */
	m->ecx = M32((DWORD)(m->esp + 0x78u));	/* 480720: mov ecx, dword ptr [esp + 0x78] */
	m->edx = M32((DWORD)(m->esp + 0x7cu));	/* 480724: mov edx, dword ptr [esp + 0x7c] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 480728: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x80u));	/* 48072a: mov ecx, dword ptr [esp + 0x80] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 480731: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x84u));	/* 480734: mov edx, dword ptr [esp + 0x84] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 48073b: mov dword ptr [eax + 8], ecx */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 48073e: mov dword ptr [eax + 0xc], edx */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 480741: mov eax, dword ptr [esp + 0x1c] */
	m->ebx = M32((DWORD)(m->ebx + 0xcu));	/* 480745: mov ebx, dword ptr [ebx + 0xc] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 480748: mov dword ptr [esp + 0x10], eax */
	goto L_480586;	/* 48074c: jmp 0x480586 */
L_480751:
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 480751: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x9cu));	/* 480753: mov ecx, dword ptr [esp + 0x9c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 48075a: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 48075e: fmul dword ptr [eax + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 480761: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 480765: fmul dword ptr [eax + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480768: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 48076a: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 48076e: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480770: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 480772: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 480775: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 480777: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 48077b: fmul dword ptr [eax + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 48077e: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 480782: fmul dword ptr [eax + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480785: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 480787: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 48078b: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48078e: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 480790: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 480793: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 480796: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 48079a: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 48079d: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 4807a1: fmul dword ptr [eax + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4807a4: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4807a6: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4807aa: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4807ad: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 4807af: fadd dword ptr [eax + 0x38] */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 4807b2: fstp dword ptr [ecx + 8] */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 4807b5: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0xa8u));	/* 4807b7: mov ecx, dword ptr [esp + 0xa8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 4807be: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 4807c2: fmul dword ptr [eax + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 4807c5: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 4807c9: fmul dword ptr [eax + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4807cc: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 4807ce: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4807d2: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4807d4: faddp st(1) */
	MF((DWORD)(m->edi + 0x0u)) = (float)ST(0); FPOP();	/* 4807d6: fstp dword ptr [edi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 4807d8: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 4807dc: fmul dword ptr [eax + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 4807df: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 4807e3: fmul dword ptr [eax + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4807e6: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 4807e8: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4807ec: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4807ef: faddp st(1) */
	MF((DWORD)(m->edi + 0x4u)) = (float)ST(0); FPOP();	/* 4807f1: fstp dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x5cu)));	/* 4807f4: fld dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 4807f8: fmul dword ptr [eax + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 4807fb: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 4807ff: fmul dword ptr [eax + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480802: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 480804: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 480808: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48080b: faddp st(1) */
	MF((DWORD)(m->edi + 0x8u)) = (float)ST(0); FPOP();	/* 48080d: fstp dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 480810: mov eax, dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 480812: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 480819: fmul dword ptr [eax + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 48081c: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 480823: fmul dword ptr [eax + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480826: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 480828: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x10u));	/* 48082c: fmul dword ptr [eax + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48082f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 480831: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 480835: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480837: faddp st(1) */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 480839: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 48083b: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 480842: fmul dword ptr [eax + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 480845: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x24u));	/* 48084c: fmul dword ptr [eax + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48084f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 480851: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x14u));	/* 480855: fmul dword ptr [eax + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480858: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 48085a: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 48085e: fmul dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->ebx;	/* 480861: mov dword ptr [esp + 0x20], ebx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480865: faddp st(1) */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 480867: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 48086a: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 480871: fmul dword ptr [eax + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 480874: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x28u));	/* 48087b: fmul dword ptr [eax + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48087e: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 480880: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x18u));	/* 480884: fmul dword ptr [eax + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480887: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 480889: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 48088d: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480890: faddp st(1) */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 480892: fstp dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 480895: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x3cu));	/* 48089c: fmul dword ptr [eax + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x80u)));	/* 48089f: fld dword ptr [esp + 0x80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x2cu));	/* 4808a6: fmul dword ptr [eax + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4808a9: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x7cu)));	/* 4808ab: fld dword ptr [esp + 0x7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x1cu));	/* 4808af: fmul dword ptr [eax + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4808b2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 4808b4: fld dword ptr [esp + 0x78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0xcu));	/* 4808b8: fmul dword ptr [eax + 0xc] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4808bb: mov eax, dword ptr [esp + 0x1c] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4808bf: mov dword ptr [esp + 0x10], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4808c3: faddp st(1) */
	MF((DWORD)(m->ecx + 0xcu)) = (float)ST(0); FPOP();	/* 4808c5: fstp dword ptr [ecx + 0xc] */
L_4808c8:
	m->ebx = M32((DWORD)(m->ebx + 0xcu));	/* 4808c8: mov ebx, dword ptr [ebx + 0xc] */
	goto L_480586;	/* 4808cb: jmp 0x480586 */
L_4808d0:
	{ DWORD a_ = M32((DWORD)(m->esp + 0x24u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4808d0: cmp dword ptr [esp + 0x24], 1 */
	if (!m->zf) goto L_4809c2;	/* 4808d5: jne 0x4809c2 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4808db: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 4808df: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4808e5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4808e7: test ah, 0x41 */
	if (!m->zf) goto L_4809c2;	/* 4808ea: jne 0x4809c2 */
	m->eax = M32((DWORD)(m->esp + 0x94u));	/* 4808f0: mov eax, dword ptr [esp + 0x94] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 4808f7: fld dword ptr [edi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4808fa: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 4808fd: fld dword ptr [edi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 480900: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480903: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 480905: fld dword ptr [edi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 480907: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480909: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 48090b: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 480911: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 480913: test ah, 0x41 */
	if (!m->zf) goto L_48098d;	/* 480916: jne 0x48098d */
	m->eax = M32((DWORD)(m->esp + 0x9cu));	/* 480918: mov eax, dword ptr [esp + 0x9c] */
	M32((DWORD)(m->esp + 0x14u)) = 0x1u;	/* 48091f: mov dword ptr [esp + 0x14], 1 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 480927: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 480929: mov dword ptr [esp + 0x3c], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 48092d: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 480930: mov dword ptr [esp + 0x40], edx */
	m->esi = M32((DWORD)(m->eax + 0x8u));	/* 480934: mov esi, dword ptr [eax + 8] */
	m->eax = m->edi;	/* 480937: mov eax, edi */
	M32((DWORD)(m->esp + 0x44u)) = m->esi;	/* 480939: mov dword ptr [esp + 0x44], esi */
	m->ebp = M32((DWORD)(m->eax + 0x0u));	/* 48093d: mov ebp, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x30u)) = m->ebp;	/* 48093f: mov dword ptr [esp + 0x30], ebp */
	m->ebx = M32((DWORD)(m->eax + 0x4u));	/* 480943: mov ebx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x34u)) = m->ebx;	/* 480946: mov dword ptr [esp + 0x34], ebx */
	m->ebx = M32((DWORD)(m->esp + 0xa4u));	/* 48094a: mov ebx, dword ptr [esp + 0xa4] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 480951: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 480954: mov dword ptr [esp + 0x38], eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 480958: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ebx + 0x0u)) = m->eax;	/* 48095c: mov dword ptr [ebx], eax */
	m->ebx = M32((DWORD)(m->esp + 0x28u));	/* 48095e: mov ebx, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 480962: test ebx, ebx */
	if (m->zf) goto L_48097e;	/* 480964: je 0x48097e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8cu)));	/* 480966: fld dword ptr [esp + 0x8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48096d: fmul dword ptr [0x4a93ec] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u)); FPOP();	/* 480973: fcomp dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 480977: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 480979: test ah, 0x41 */
	if (m->zf) goto L_4809c2;	/* 48097c: je 0x4809c2 */
L_48097e:
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 48097e: inc ebx */
	{ DWORD a_ = m->ebx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48097f: cmp ebx, 5 */
	M32((DWORD)(m->esp + 0x28u)) = m->ebx;	/* 480982: mov dword ptr [esp + 0x28], ebx */
	if (!m->zf && m->sf == m->of) goto L_4809c2;	/* 480986: jg 0x4809c2 */
	goto L_48053d;	/* 480988: jmp 0x48053d */
L_48098d:
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 48098d: mov ecx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->edi + 0x0u)) = m->ecx;	/* 480993: mov dword ptr [edi], ecx */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 480995: mov edx, dword ptr [0xa0e7ec] */
	m->ecx = M32((DWORD)(m->esp + 0xa4u));	/* 48099b: mov ecx, dword ptr [esp + 0xa4] */
	M32((DWORD)(m->edi + 0x4u)) = m->edx;	/* 4809a2: mov dword ptr [edi + 4], edx */
	m->eax = M32((DWORD)(0xa0e7f0u));	/* 4809a5: mov eax, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->edi + 0x8u)) = m->eax;	/* 4809aa: mov dword ptr [edi + 8], eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 4809ad: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4809ae: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4809af: pop ebp */
	M32((DWORD)(m->ecx + 0x0u)) = 0x0u;	/* 4809b0: mov dword ptr [ecx], 0 */
	m->eax = 0x1u;	/* 4809b6: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4809bb: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4809bc: add esp, 0x78 */
	m->esp += 4 + 44; return;	/* 4809bf: ret 0x2c */
L_4809c2:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4809c2: mov eax, dword ptr [esp + 0x14] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4809c6: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4809c7: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4809c8: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4809c9: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4809ca: add esp, 0x78 */
	m->esp += 4 + 44; return;	/* 4809cd: ret 0x2c */
}

/* collision_sphereVsUnit (0x47dd90), lifted by tools/lift.py */
static void lift_47dd90(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47dd90: sub esp, 0x84 */
	m->eax = M32((DWORD)(m->esp + 0x8cu));	/* 47dd96: mov eax, dword ptr [esp + 0x8c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 47dd9d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 47dd9e: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x98u));	/* 47dd9f: mov ebp, dword ptr [esp + 0x98] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 47dda6: fld dword ptr [eax] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 47dda8: fadd dword ptr [ebp] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47ddab: push esi */
	m->esi = M32((DWORD)(m->esp + 0xa4u));	/* 47ddac: mov esi, dword ptr [esp + 0xa4] */
	m->ebx = m->ecx;	/* 47ddb3: mov ebx, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 47ddb5: push edi */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 47ddb6: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 47ddba: fld dword ptr [eax + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 47ddbd: fadd dword ptr [ebp + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x60u));	/* 47ddc0: mov ecx, dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 47ddc4: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 47ddc8: fld dword ptr [eax + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x8u));	/* 47ddcb: fadd dword ptr [ebp + 8] */
	m->edx = M32((DWORD)(m->esp + 0x64u));	/* 47ddce: mov edx, dword ptr [esp + 0x64] */
	m->eax = m->esi;	/* 47ddd2: mov eax, esi */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 47ddd4: mov dword ptr [eax], ecx */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 47ddd6: fstp dword ptr [esp + 0x68] */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 47ddda: mov ecx, dword ptr [esp + 0x68] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 47ddde: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 47dde1: mov dword ptr [eax + 8], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x8u)));	/* 47dde4: fld dword ptr [ebp + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x54u));	/* 47dde7: fmul dword ptr [ebx + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x4u)));	/* 47ddea: fld dword ptr [ebp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x50u));	/* 47dded: fmul dword ptr [ebx + 0x50] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47ddf0: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4cu)));	/* 47ddf2: fld dword ptr [ebx + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 47ddf5: fmul dword ptr [ebp] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47ddf8: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47ddfa: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47de00: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47de02: test ah, 0x41 */
	if (!m->zf) goto L_47de16;	/* 47de05: jne 0x47de16 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47de07: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47de08: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47de09: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47de0a: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47de0c: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47de0d: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47de13: ret 0x24 */
L_47de16:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47de16: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x54u));	/* 47de19: fmul dword ptr [ebx + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47de1c: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x50u));	/* 47de1f: fmul dword ptr [ebx + 0x50] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47de22: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47de24: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebx + 0x4cu));	/* 47de26: fmul dword ptr [ebx + 0x4c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47de29: faddp st(1) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x58u));	/* 47de2b: fsub dword ptr [ebx + 0x58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 47de2e: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47de34: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47de36: test ah, 1 */
	if (m->zf) goto L_47de3d;	/* 47de39: je 0x47de3d */
	ST(0) = -ST(0);	/* 47de3b: fchs  */
L_47de3d:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x98u)); FPOP();	/* 47de3d: fcomp dword ptr [esp + 0x98] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47de44: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47de46: test ah, 1 */
	if (!m->zf) goto L_47de5a;	/* 47de49: jne 0x47de5a */
	m->edi = M32(m->esp); m->esp += 4;	/* 47de4b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47de4c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47de4d: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47de4e: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47de50: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47de51: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47de57: ret 0x24 */
L_47de5a:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 47de5a: xor edx, edx */
	m->edi = (DWORD)(m->esp + 0x78u);	/* 47de5c: lea edi, [esp + 0x78] */
	m->ecx = (DWORD)(m->ebx + 0x64u);	/* 47de60: lea ecx, [ebx + 0x64] */
L_47de63:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xfffffff8u)));	/* 47de63: fld dword ptr [ecx - 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 47de66: fmul dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xfffffffcu)));	/* 47de68: fld dword ptr [ecx - 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 47de6b: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47de6e: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 47de70: fld dword ptr [ecx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 47de72: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47de75: faddp st(1) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 47de77: fsub dword ptr [ecx + 4] */
	MF((DWORD)(m->edi + 0x0u)) = (float)ST(0);	/* 47de7a: fst dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x98u)); FPOP();	/* 47de7c: fcomp dword ptr [esp + 0x98] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47de83: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47de85: test ah, 1 */
	if (m->zf) goto L_47e04e;	/* 47de88: je 0x47e04e */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 47de8e: inc edx */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 47de8f: add ecx, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 47de92: add edi, 4 */
	{ DWORD a_ = m->edx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47de95: cmp edx, 3 */
	if (m->sf != m->of) goto L_47de63;	/* 47de98: jl 0x47de63 */
	m->ecx = M32((DWORD)(m->esp + 0x9cu));	/* 47de9a: mov ecx, dword ptr [esp + 0x9c] */
	m->edx = m->ecx;	/* 47dea1: mov edx, ecx */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 47dea3: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47dea5: mov dword ptr [esp + 0x60], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 47dea9: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x64u)) = m->eax;	/* 47deac: mov dword ptr [esp + 0x64], eax */
	m->eax = M32((DWORD)(m->ebp + 0x0u));	/* 47deb0: mov eax, dword ptr [ebp] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 47deb3: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 47deb6: mov dword ptr [esp + 0x38], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47deba: fld dword ptr [esp + 0x38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47debe: fcomp dword ptr [0x4a93e8] */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 47dec4: mov eax, dword ptr [ebp + 8] */
	M32((DWORD)(m->esp + 0x68u)) = m->edx;	/* 47dec7: mov dword ptr [esp + 0x68], edx */
	m->edx = M32((DWORD)(m->ebp + 0x4u));	/* 47decb: mov edx, dword ptr [ebp + 4] */
	M32((DWORD)(m->esp + 0x40u)) = m->eax;	/* 47dece: mov dword ptr [esp + 0x40], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47ded2: fld dword ptr [esp + 0x38] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ded6: fnstsw ax */
	M32((DWORD)(m->esp + 0x3cu)) = m->edx;	/* 47ded8: mov dword ptr [esp + 0x3c], edx */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47dedc: test ah, 1 */
	if (m->zf) goto L_47dee3;	/* 47dedf: je 0x47dee3 */
	ST(0) = -ST(0);	/* 47dee1: fchs  */
L_47dee3:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47dee3: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47dee9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47deeb: test ah, 1 */
	if (m->zf) goto L_47dfb4;	/* 47deee: je 0x47dfb4 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47def4: fld dword ptr [esp + 0x3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47def8: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47defe: fld dword ptr [esp + 0x3c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47df02: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47df04: test ah, 1 */
	if (m->zf) goto L_47df0b;	/* 47df07: je 0x47df0b */
	ST(0) = -ST(0);	/* 47df09: fchs  */
L_47df0b:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47df0b: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47df11: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47df13: test ah, 1 */
	if (m->zf) goto L_47dfb4;	/* 47df16: je 0x47dfb4 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47df1c: fld dword ptr [esp + 0x40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47df20: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47df26: fld dword ptr [esp + 0x40] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47df2a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47df2c: test ah, 1 */
	if (m->zf) goto L_47df33;	/* 47df2f: je 0x47df33 */
	ST(0) = -ST(0);	/* 47df31: fchs  */
L_47df33:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47df33: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47df39: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47df3b: test ah, 1 */
	if (m->zf) goto L_47dfb4;	/* 47df3e: je 0x47dfb4 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4cu)));	/* 47df40: fld dword ptr [ebx + 0x4c] */
	ST(0) = -ST(0);	/* 47df43: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x50u)));	/* 47df45: fld dword ptr [ebx + 0x50] */
	ST(0) = -ST(0);	/* 47df48: fchs  */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 47df4a: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x54u)));	/* 47df4e: fld dword ptr [ebx + 0x54] */
	ST(0) = -ST(0);	/* 47df51: fchs  */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 47df53: fstp dword ptr [esp + 0x40] */
	{ long double t = ST(0); FPUSH(t); }	/* 47df57: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 47df59: fadd dword ptr [ecx] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 47df5b: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47df5f: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 47df63: fadd dword ptr [ecx + 4] */
	m->edx = M32((DWORD)(m->esp + 0x54u));	/* 47df66: mov edx, dword ptr [esp + 0x54] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 47df6a: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47df6e: fld dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 47df72: fadd dword ptr [ecx + 8] */
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 47df75: mov eax, dword ptr [esp + 0x58] */
	m->ecx = m->esi;	/* 47df79: mov ecx, esi */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 47df7b: fstp dword ptr [esp + 0x5c] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47df7f: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 47df81: mov edx, dword ptr [esp + 0x5c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x98u));	/* 47df85: fmul dword ptr [esp + 0x98] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47df8c: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47df8f: mov dword ptr [ecx + 8], edx */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 47df92: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47df96: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x98u));	/* 47df9a: fmul dword ptr [esp + 0x98] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 47dfa1: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47dfa5: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x98u));	/* 47dfa9: fmul dword ptr [esp + 0x98] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 47dfb0: fstp dword ptr [esp + 0x40] */
L_47dfb4:
	m->eax = (DWORD)(m->esp + 0x78u);	/* 47dfb4: lea eax, [esp + 0x78] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 47dfb8: xor ecx, ecx */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 47dfba: mov dword ptr [esp + 0x34], eax */
L_47dfbe:
	m->edi = (DWORD)(m->ecx + 0x1u);	/* 47dfbe: lea edi, [ecx + 1] */
	m->ebp = 0x3u;	/* 47dfc1: mov ebp, 3 */
	m->eax = m->edi;	/* 47dfc6: mov eax, edi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 47dfc8: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ebp; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 47dfc9: idiv ebp */
	m->ebp = m->edx;	/* 47dfcb: mov ebp, edx */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 47dfcd: mov edx, dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x0u)));	/* 47dfd1: fld dword ptr [edx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47dfd3: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47dfd9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47dfdb: test ah, 0x41 */
	if (m->zf) goto L_47e05d;	/* 47dfde: je 0x47e05d */
	m->ecx = m->edi;	/* 47dfe0: mov ecx, edi */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47dfe2: add edx, 4 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47dfe5: cmp ecx, 3 */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 47dfe8: mov dword ptr [esp + 0x34], edx */
	if (m->sf != m->of) goto L_47dfbe;	/* 47dfec: jl 0x47dfbe */
	m->eax = M32((DWORD)(m->ebx + 0x54u));	/* 47dfee: mov eax, dword ptr [ebx + 0x54] */
	m->ecx = M32((DWORD)(m->ebx + 0x50u));	/* 47dff1: mov ecx, dword ptr [ebx + 0x50] */
	m->edx = M32((DWORD)(m->ebx + 0x4cu));	/* 47dff4: mov edx, dword ptr [ebx + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47dff7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47dff8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47dff9: push edx */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 47dffa: lea ecx, [esp + 0x34] */
	m->esp -= 4; M32(m->esp) = 0x47e003u; lift_480210(m);	/* 47dffe: call 0x480210 */
	m->eax = (DWORD)(m->esp + 0x60u);	/* 47e003: lea eax, [esp + 0x60] */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 47e007: lea ecx, [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47e00b: push eax */
	m->esp -= 4; M32(m->esp) = 0x47e011u; lift_4802b0(m);	/* 47e00c: call 0x4802b0 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x58u));	/* 47e011: fsub dword ptr [ebx + 0x58] */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 47e014: lea ecx, [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e018: push ecx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 47e019: lea ecx, [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 47e01d: fstp dword ptr [esp + 0x54] */
	m->esp -= 4; M32(m->esp) = 0x47e026u; lift_4802b0(m);	/* 47e021: call 0x4802b0 */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0);	/* 47e026: fst dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47e02a: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e030: fld dword ptr [esp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e034: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e036: test ah, 1 */
	if (m->zf) goto L_47e03d;	/* 47e039: je 0x47e03d */
	ST(0) = -ST(0);	/* 47e03b: fchs  */
L_47e03d:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47e03d: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e043: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e045: test ah, 1 */
	if (m->zf) goto L_47f800;	/* 47e048: je 0x47f800 */
L_47e04e:
	m->edi = M32(m->esp); m->esp += 4;	/* 47e04e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47e04f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47e050: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47e051: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47e053: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47e054: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47e05a: ret 0x24 */
L_47e05d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47e05d: fld dword ptr [esi + 8] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 47e060: lea eax, [ecx + ecx*2] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e063: push ecx */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + m->eax*4 + 0xcu));	/* 47e064: fsub dword ptr [ebx + eax*4 + 0xc] */
	m->edi = (DWORD)(m->ebx + m->eax*4 + 0x0u);	/* 47e068: lea edi, [ebx + eax*4] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e06b: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47e06e: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47e071: fsub dword ptr [edi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e074: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e075: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47e078: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47e07a: fsub dword ptr [edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e07d: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e07e: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e085: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e08du; lift_4722c0(m);	/* 47e088: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e08d: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47e08f: mov dword ptr [esp + 0x10], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e093: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 47e096: mov dword ptr [esp + 0x14], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e09a: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 47e09d: mov dword ptr [esp + 0x18], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e0a1: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47e0a5: fmul dword ptr [edi + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e0a8: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47e0ac: fmul dword ptr [edi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e0af: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47e0b1: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47e0b5: fmul dword ptr [edi + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e0b8: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47e0ba: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e0c0: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e0c2: test ah, 1 */
	if (m->zf) goto L_47e82b;	/* 47e0c5: je 0x47e82b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x98u)));	/* 47e0cb: fld dword ptr [esp + 0x98] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x98u));	/* 47e0d2: fmul dword ptr [esp + 0x98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e0d9: push ecx */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 47e0da: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47e0de: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 47e0e1: fsub dword ptr [edi + 0xc] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e0e4: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47e0e7: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47e0ea: fsub dword ptr [edi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e0ed: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e0ee: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47e0f1: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47e0f3: fsub dword ptr [edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e0f6: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e0f7: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e0fe: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e106u; lift_4722c0(m);	/* 47e101: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e106: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47e108: mov dword ptr [esp + 0x10], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e10c: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 47e10f: mov dword ptr [esp + 0x14], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e113: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 47e116: mov dword ptr [esp + 0x18], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e11a: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e11e: fld dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47e122: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47e126: fmul dword ptr [esp + 0x10] */
	{ long double t = ST(1); FPUSH(t); }	/* 47e12a: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 47e12c: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e12e: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47e130: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47e132: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e134: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x34u)); FPOP();	/* 47e136: fcomp dword ptr [esp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e13a: fnstsw ax */
	ST(0) = ST(0); FPOP();	/* 47e13c: fstp st(0) */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e13e: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 47e141: fstp st(0) */
	if (!m->zf) goto L_47e154;	/* 47e143: jne 0x47e154 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47e145: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47e146: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47e147: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47e148: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47e14a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47e14b: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47e151: ret 0x24 */
L_47e154:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47e154: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 47e158: fsub dword ptr [edi + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e15b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e15c: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47e15f: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47e163: fsub dword ptr [edi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e166: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e167: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47e16a: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47e16e: fsub dword ptr [edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e171: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e172: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e179: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e181u; lift_4722c0(m);	/* 47e17c: call 0x4722c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47e181: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 47e185: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47e189: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47e18d: fmul dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e191: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47e193: mov dword ptr [esp + 0x10], ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e197: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47e199: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47e19d: fmul dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e1a1: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 47e1a4: mov dword ptr [esp + 0x14], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e1a8: mov eax, dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e1ab: faddp st(1) */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 47e1ad: mov dword ptr [esp + 0x18], eax */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0);	/* 47e1b1: fst dword ptr [esp + 0x50] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47e1b5: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 47e1bb: fld dword ptr [esp + 0x50] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e1bf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e1c1: test ah, 1 */
	if (m->zf) goto L_47e1c8;	/* 47e1c4: je 0x47e1c8 */
	ST(0) = -ST(0);	/* 47e1c6: fchs  */
L_47e1c8:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47e1c8: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e1ce: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e1d0: test ah, 1 */
	if (m->zf) goto L_47e1e4;	/* 47e1d3: je 0x47e1e4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47e1d5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47e1d6: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47e1d7: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47e1d8: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47e1da: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47e1db: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47e1e1: ret 0x24 */
L_47e1e4:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47e1e4: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 47e1e8: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e1ec: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47e1f0: fmul dword ptr [esp + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e1f4: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e1f6: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47e1fa: fmul dword ptr [esp + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e1fe: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e200: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e204: fld dword ptr [esp + 0x14] */
	{ long double t = ST(2); FPUSH(t); }	/* 47e208: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47e20a: fmul st(3) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47e20c: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47e210: fmul dword ptr [esp + 0x10] */
	{ long double t = ST(2); FPUSH(t); }	/* 47e214: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47e216: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e218: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47e21a: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 47e21c: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e21e: faddp st(1) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47e220: fsub dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47e224: fmul dword ptr [esp + 0x50] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e228: fsubp st(1) */
	ST(2) = ST(0); FPOP();	/* 47e22a: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 47e22c: fstp st(0) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u));	/* 47e22e: fcom dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e234: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e236: test ah, 1 */
	if (m->zf) goto L_47e24e;	/* 47e239: je 0x47e24e */
	m->edi = M32(m->esp); m->esp += 4;	/* 47e23b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47e23c: pop esi */
	ST(0) = ST(0); FPOP();	/* 47e23d: fstp st(0) */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47e23f: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47e240: xor eax, eax */
	ST(0) = ST(0); FPOP();	/* 47e242: fstp st(0) */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47e244: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47e245: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47e24b: ret 0x24 */
L_47e24e:
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47e24e: fsqrt  */
	{ long double t = ST(0); FPUSH(t); }	/* 47e250: fld st(0) */
	ST(0) = ST(0) - ST(2);	/* 47e252: fsub st(2) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47e254: fdiv dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47e258: fstp dword ptr [esp + 0x34] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47e25c: fxch st(1) */
	ST(0) = -ST(0);	/* 47e25e: fchs  */
	ST(0) = ST(0) - ST(1);	/* 47e260: fsub st(1) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47e262: fdiv dword ptr [esp + 0x50] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47e266: fxch st(1) */
	ST(0) = ST(0); FPOP();	/* 47e268: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e26a: fld dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47e26e: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e274: fld dword ptr [esp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e278: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e27a: test ah, 1 */
	if (m->zf) goto L_47e281;	/* 47e27d: je 0x47e281 */
	ST(0) = -ST(0);	/* 47e27f: fchs  */
L_47e281:
	{ long double t = ST(1); FPUSH(t); }	/* 47e281: fld st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47e283: fcomp dword ptr [0x4a93e8] */
	{ long double t = ST(1); FPUSH(t); }	/* 47e289: fld st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e28b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e28d: test ah, 1 */
	if (m->zf) goto L_47e294;	/* 47e290: je 0x47e294 */
	ST(0) = -ST(0);	/* 47e292: fchs  */
L_47e294:
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47e294: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP();	/* 47e296: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e298: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e29a: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 47e29d: fstp st(0) */
	if (m->zf) goto L_47e2a7;	/* 47e29f: je 0x47e2a7 */
	ST(0) = ST(0); FPOP();	/* 47e2a1: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e2a3: fld dword ptr [esp + 0x34] */
L_47e2a7:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 47e2a7: fcom dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e2ad: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e2af: test ah, 0x41 */
	if (!m->zf) goto L_47e2be;	/* 47e2b2: jne 0x47e2be */
	ST(0) = ST(0); FPOP();	/* 47e2b4: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 47e2b6: fld dword ptr [0x4a9424] */
	goto L_47e2d3;	/* 47e2bc: jmp 0x47e2d3 */
L_47e2be:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u));	/* 47e2be: fcom dword ptr [0x4a9474] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e2c4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e2c6: test ah, 1 */
	if (m->zf) goto L_47e2d3;	/* 47e2c9: je 0x47e2d3 */
	ST(0) = ST(0); FPOP();	/* 47e2cb: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 47e2cd: fld dword ptr [0x4a9474] */
L_47e2d3:
	{ long double t = ST(0); FPUSH(t); }	/* 47e2d3: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47e2d5: fmul dword ptr [esp + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e2d9: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e2da: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e2dd: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 47e2de: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47e2e0: fmul dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e2e4: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47e2e7: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(1);	/* 47e2eb: fmul st(1) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e2ed: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e2ee: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e2f5: fstp dword ptr [esp] */
	ST(0) = ST(0); FPOP();	/* 47e2f8: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x47e2ffu; lift_4722c0(m);	/* 47e2fa: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e2ff: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47e301: fld dword ptr [esp + 0x68] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e305: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e308: push ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47e309: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47e30d: mov dword ptr [esp + 0x14], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e311: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47e314: mov dword ptr [esp + 0x1c], eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47e318: fadd dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e31c: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47e31f: fld dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47e323: fadd dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e327: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e328: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e32b: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x68u));	/* 47e32f: fadd dword ptr [esp + 0x68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e333: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47e334: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e338: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e340u; lift_4722c0(m);	/* 47e33b: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e340: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47e342: fld dword ptr [esi + 8] */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 47e345: mov dword ptr [esp + 0x54], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e349: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 47e34c: mov dword ptr [esp + 0x58], edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e350: push ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e351: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47e354: mov dword ptr [esp + 0x60], eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 47e358: fsub dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e35c: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47e35f: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 47e362: fsub dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e366: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e367: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47e36a: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 47e36c: fsub dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e370: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e371: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e378: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e380u; lift_4722c0(m);	/* 47e37b: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e380: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 47e382: mov dword ptr [esp + 0x44], ecx */
	m->ecx = M32((DWORD)(m->esp + 0xb0u));	/* 47e386: mov ecx, dword ptr [esp + 0xb0] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e38d: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 47e390: mov dword ptr [esp + 0x48], edx */
	m->edx = m->esi;	/* 47e394: mov edx, esi */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e396: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 47e399: mov dword ptr [esp + 0x4c], eax */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 47e39d: mov eax, dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47e3a1: fld dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47e3a5: fld dword ptr [esp + 0x48] */
	{ long double t = ST(0); FPUSH(t); }	/* 47e3a9: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47e3ab: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47e3ad: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47e3af: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e3b1: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47e3b3: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47e3b7: fmul dword ptr [esp + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e3bb: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47e3bd: fsqrt  */
	ST(2) = ST(0); FPOP();	/* 47e3bf: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 47e3c1: fstp st(0) */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 47e3c3: fstp dword ptr [ecx] */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 47e3c5: mov ecx, dword ptr [esp + 0x58] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47e3c9: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 47e3cb: mov eax, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47e3cf: mov dword ptr [edx + 4], ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e3d2: push ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47e3d3: mov dword ptr [edx + 8], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47e3d6: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 47e3d9: fsub dword ptr [edi + 0xc] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e3dc: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47e3df: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47e3e2: fsub dword ptr [edi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e3e5: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e3e6: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47e3e9: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47e3eb: fsub dword ptr [edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e3ee: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e3ef: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e3f6: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e3feu; lift_4722c0(m);	/* 47e3f9: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e3fe: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 47e400: mov dword ptr [esp + 0x28], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e404: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 47e407: mov dword ptr [esp + 0x2c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e40b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 47e40e: mov dword ptr [esp + 0x30], eax */
	m->eax = M32((DWORD)(m->esp + 0xb8u));	/* 47e412: mov eax, dword ptr [esp + 0xb8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47e419: test eax, eax */
	if (!m->zf) goto L_47e5eb;	/* 47e41b: jne 0x47e5eb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47e421: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 47e425: fmul dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47e429: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47e42d: fmul dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e431: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e432: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e434: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47e437: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47e43b: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47e43f: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47e443: fmul dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e447: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e448: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e44a: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47e44d: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47e451: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e455: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 47e459: fmul dword ptr [esp + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e45d: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e45e: lea ecx, [esp + 0x84] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e465: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e467: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e46fu; lift_4722c0(m);	/* 47e46a: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e46f: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47e471: mov dword ptr [esp + 0x10], ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e475: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e476: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 47e47a: fmul dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e47e: mov edx, dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47e481: fld dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47e485: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e489: mov eax, dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47e48c: fmul dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47e490: mov dword ptr [esp + 0x1c], eax */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e494: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e496: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47e499: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47e49d: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e4a1: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47e4a5: fmul dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e4a9: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e4aa: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e4ac: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47e4af: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47e4b3: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e4b7: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47e4bb: fmul dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e4bf: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47e4c0: lea ecx, [esp + 0x1c] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e4c4: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e4c6: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e4ceu; lift_4722c0(m);	/* 47e4c9: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e4ce: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 47e4d0: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47e4d4: lea ecx, [esp + 0x1c] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e4d8: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 47e4db: mov dword ptr [esp + 0x20], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e4df: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47e4e2: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x47e4ebu; lift_467760(m);	/* 47e4e6: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47e4eb: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e4f1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e4f3: test ah, 1 */
	if (!m->zf) goto L_47f62e;	/* 47e4f6: jne 0x47f62e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47e4fc: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47e500: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47e504: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e508: fmul dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e50c: push ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e50d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47e50f: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e513: fmul dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e517: faddp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 47e519: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47e51b: fmul dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47e51f: fstp dword ptr [esp + 0x20] */
	{ long double t = ST(0); FPUSH(t); }	/* 47e523: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e525: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47e529: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47e52d: fmul dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 47e531: fst dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47e535: fsub dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e539: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47e53c: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47e540: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e544: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e545: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47e548: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47e54c: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e550: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e551: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e558: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e560u; lift_4722c0(m);	/* 47e55b: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e560: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e562: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47e563: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e567: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47e56a: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e56e: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47e571: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47e575: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47e579: fmul dword ptr [esp + 0xa8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e580: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e583: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47e587: fmul dword ptr [esp + 0xa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e58e: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e58f: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e592: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xacu));	/* 47e596: fmul dword ptr [esp + 0xac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e59d: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47e59e: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e5a2: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e5aau; lift_4722c0(m);	/* 47e5a5: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e5aa: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e5ac: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47e5ad: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e5b1: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47e5b4: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e5b8: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47e5bb: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47e5bf: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47e5c3: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e5c7: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e5ca: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e5ce: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e5d2: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e5d3: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e5d6: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e5da: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e5de: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47e5df: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e5e3: fstp dword ptr [esp] */
	goto L_47f60d;	/* 47e5e6: jmp 0x47f60d */
L_47e5eb:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47e5eb: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 47e5ef: fmul dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47e5f2: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 47e5f6: fmul dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e5f8: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e5f9: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e5fb: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e5fe: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 47e602: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47e604: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 47e608: fmul dword ptr [eax + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e60b: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e60c: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e60e: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e611: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 47e615: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47e618: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 47e61c: fmul dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e61f: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47e620: lea ecx, [esp + 0x78] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e624: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e626: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e62eu; lift_4722c0(m);	/* 47e629: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e62e: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 47e630: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47e634: lea ecx, [esp + 0x1c] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e638: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 47e63b: mov dword ptr [esp + 0x20], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e63f: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47e642: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x47e64bu; lift_467760(m);	/* 47e646: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47e64b: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e651: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e653: test ah, 1 */
	if (!m->zf) goto L_47e764;	/* 47e656: jne 0x47e764 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47e65c: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47e660: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47e664: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e668: fmul dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e66c: push ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e66d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47e66f: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e673: fmul dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e677: faddp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 47e679: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47e67b: fmul dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47e67f: fstp dword ptr [esp + 0x20] */
	{ long double t = ST(0); FPUSH(t); }	/* 47e683: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e685: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47e689: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47e68d: fmul dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 47e691: fst dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47e695: fsub dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e699: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47e69c: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47e6a0: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e6a4: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e6a5: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47e6a8: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47e6ac: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e6b0: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47e6b1: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e6b5: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e6bdu; lift_4722c0(m);	/* 47e6b8: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e6bd: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e6bf: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47e6c0: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e6c4: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47e6c7: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e6cb: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47e6ce: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47e6d2: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47e6d6: fmul dword ptr [esp + 0xa8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e6dd: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e6e0: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47e6e4: fmul dword ptr [esp + 0xa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e6eb: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e6ec: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e6ef: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xacu));	/* 47e6f3: fmul dword ptr [esp + 0xac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e6fa: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47e6fb: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e702: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e70au; lift_4722c0(m);	/* 47e705: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e70a: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e70c: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47e70d: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e711: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47e714: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e718: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47e71b: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47e71f: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47e723: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e727: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e72a: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e72e: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e732: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e733: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e736: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47e73a: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e73e: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47e73f: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e743: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e74bu; lift_4722c0(m);	/* 47e746: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47e74b: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47e752: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47e754: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e756: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47e759: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e75c: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47e75f: mov dword ptr [ecx + 8], eax */
	goto L_47e784;	/* 47e762: jmp 0x47e784 */
L_47e764:
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47e764: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 47e76b: mov edx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47e771: mov dword ptr [ecx], edx */
	m->eax = M32((DWORD)(0xa0e7ecu));	/* 47e773: mov eax, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47e778: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 47e77b: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47e781: mov dword ptr [ecx + 8], edx */
L_47e784:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47e784: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47e788: fmul dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47e78c: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 47e790: fmul dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e794: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e795: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e797: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47e79a: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47e79e: fmul dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47e7a2: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47e7a6: fmul dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e7aa: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e7ab: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e7ad: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e7b0: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 47e7b4: fmul dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47e7b8: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47e7bc: fmul dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e7c0: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47e7c1: lea ecx, [esp + 0x78] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e7c5: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e7c7: fstp dword ptr [esp] */
L_47e7ca:
	m->esp -= 4; M32(m->esp) = 0x47e7cfu; lift_4722c0(m);	/* 47e7ca: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e7cf: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 47e7d1: mov dword ptr [esp + 0x28], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e7d5: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 47e7d8: mov dword ptr [esp + 0x2c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e7dc: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 47e7df: mov dword ptr [esp + 0x30], eax */
L_47e7e3:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47e7e3: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 47e7e7: fmul dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47e7e9: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 47e7ed: fmul dword ptr [esi + 4] */
	m->eax = M32((DWORD)(m->esp + 0xb4u));	/* 47e7f0: mov eax, dword ptr [esp + 0xb4] */
	m->edi = M32(m->esp); m->esp += 4;	/* 47e7f7: pop edi */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e7f8: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47e7fa: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 47e7fe: fmul dword ptr [esi + 8] */
	m->esi = M32(m->esp); m->esp += 4;	/* 47e801: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47e802: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47e803: pop ebx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e804: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e806: fld dword ptr [esp + 0x18] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 47e80a: fstp dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47e80c: fld dword ptr [esp + 0x1c] */
	MF((DWORD)(m->eax + 0x4u)) = (float)ST(0); FPOP();	/* 47e810: fstp dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47e813: fld dword ptr [esp + 0x20] */
	MF((DWORD)(m->eax + 0x8u)) = (float)ST(0); FPOP();	/* 47e817: fstp dword ptr [eax + 8] */
	MF((DWORD)(m->eax + 0xcu)) = (float)ST(0); FPOP();	/* 47e81a: fstp dword ptr [eax + 0xc] */
	m->eax = 0x1u;	/* 47e81d: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47e822: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47e828: ret 0x24 */
L_47e82b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47e82b: fld dword ptr [esi + 8] */
	m->ecx = (DWORD)(m->ebp + m->ebp*2 + 0x0u);	/* 47e82e: lea ecx, [ebp + ebp*2] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e832: push ecx */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + m->ecx*4 + 0xcu));	/* 47e833: fsub dword ptr [ebx + ecx*4 + 0xc] */
	m->ebx = (DWORD)(m->ebx + m->ecx*4 + 0x4u);	/* 47e837: lea ebx, [ebx + ecx*4 + 4] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e83b: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47e83e: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47e841: fsub dword ptr [ebx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e844: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e845: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47e848: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47e84a: fsub dword ptr [ebx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e84c: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47e84d: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e851: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e859u; lift_4722c0(m);	/* 47e854: call 0x4722c0 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47e859: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 47e85b: mov dword ptr [esp + 0x10], edx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 47e85f: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47e862: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 47e866: mov edx, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47e869: mov dword ptr [esp + 0x18], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e86d: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47e871: fmul dword ptr [edi + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e874: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47e878: fmul dword ptr [edi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e87b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47e87d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47e881: fmul dword ptr [edi + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e884: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47e886: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x98u)));	/* 47e88c: fld dword ptr [esp + 0x98] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x98u));	/* 47e893: fmul dword ptr [esp + 0x98] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e89a: fnstsw ax */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47e89c: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47e8a0: fld dword ptr [esi + 8] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e8a3: test ah, 0x41 */
	if (!m->zf) goto L_47ef99;	/* 47e8a6: jne 0x47ef99 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47e8ac: fsub dword ptr [ebx + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e8af: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e8b0: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47e8b3: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47e8b6: fsub dword ptr [ebx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e8b9: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e8ba: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47e8bd: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47e8bf: fsub dword ptr [ebx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e8c1: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47e8c2: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e8c6: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e8ceu; lift_4722c0(m);	/* 47e8c9: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e8ce: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47e8d0: mov dword ptr [esp + 0x10], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e8d4: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 47e8d7: mov dword ptr [esp + 0x14], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e8db: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 47e8de: mov dword ptr [esp + 0x18], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e8e2: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e8e6: fld dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47e8ea: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47e8ee: fmul dword ptr [esp + 0x10] */
	{ long double t = ST(1); FPUSH(t); }	/* 47e8f2: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 47e8f4: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e8f6: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47e8f8: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47e8fa: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e8fc: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x34u)); FPOP();	/* 47e8fe: fcomp dword ptr [esp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e902: fnstsw ax */
	ST(0) = ST(0); FPOP();	/* 47e904: fstp st(0) */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e906: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 47e909: fstp st(0) */
	if (!m->zf) goto L_47e91c;	/* 47e90b: jne 0x47e91c */
	m->edi = M32(m->esp); m->esp += 4;	/* 47e90d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47e90e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47e90f: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47e910: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47e912: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47e913: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47e919: ret 0x24 */
L_47e91c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47e91c: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47e920: fsub dword ptr [ebx + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e923: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e924: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47e927: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47e92b: fsub dword ptr [ebx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e92e: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e92f: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47e932: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47e936: fsub dword ptr [ebx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47e938: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47e939: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47e93d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47e945u; lift_4722c0(m);	/* 47e940: call 0x4722c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47e945: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 47e949: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47e94d: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47e951: fmul dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47e955: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47e957: mov dword ptr [esp + 0x10], ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e95b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47e95d: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47e961: fmul dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47e965: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 47e968: mov dword ptr [esp + 0x14], edx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e96c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47e96e: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 47e972: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e976: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47e97a: fmul dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47e97e: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 47e981: mov dword ptr [esp + 0x18], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e985: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e987: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47e98b: fmul dword ptr [esp + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e98f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47e991: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47e995: fld dword ptr [esp + 0x14] */
	{ long double t = ST(2); FPUSH(t); }	/* 47e999: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47e99b: fmul st(3) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47e99d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47e9a1: fmul dword ptr [esp + 0x10] */
	{ long double t = ST(2); FPUSH(t); }	/* 47e9a5: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47e9a7: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e9a9: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47e9ab: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 47e9ad: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47e9af: faddp st(1) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47e9b1: fsub dword ptr [esp + 0x34] */
	ST(0) = ST(0) * ST(5);	/* 47e9b5: fmul st(5) */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47e9b7: fsubp st(1) */
	ST(2) = ST(0); FPOP();	/* 47e9b9: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 47e9bb: fstp st(0) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u));	/* 47e9bd: fcom dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47e9c3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47e9c5: test ah, 1 */
	if (m->zf) goto L_47e9df;	/* 47e9c8: je 0x47e9df */
	ST(0) = ST(0); FPOP();	/* 47e9ca: fstp st(0) */
	m->edi = M32(m->esp); m->esp += 4;	/* 47e9cc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47e9cd: pop esi */
	ST(0) = ST(0); FPOP();	/* 47e9ce: fstp st(0) */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47e9d0: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47e9d1: xor eax, eax */
	ST(0) = ST(0); FPOP();	/* 47e9d3: fstp st(0) */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47e9d5: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47e9d6: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47e9dc: ret 0x24 */
L_47e9df:
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47e9df: fsqrt  */
	{ long double t = ST(0); FPUSH(t); }	/* 47e9e1: fld st(0) */
	ST(0) = ST(0) - ST(2);	/* 47e9e3: fsub st(2) */
	ST(0) = ST(0) / ST(3);	/* 47e9e5: fdiv st(3) */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47e9e7: fstp dword ptr [esp + 0x34] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47e9eb: fxch st(1) */
	ST(0) = -ST(0);	/* 47e9ed: fchs  */
	ST(0) = ST(0) - ST(1);	/* 47e9ef: fsub st(1) */
	ST(2) = ST(0) / ST(2); FPOP();	/* 47e9f1: fdivrp st(2) */
	ST(0) = ST(0); FPOP();	/* 47e9f3: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e9f5: fld dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47e9f9: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47e9ff: fld dword ptr [esp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ea03: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ea05: test ah, 1 */
	if (m->zf) goto L_47ea0c;	/* 47ea08: je 0x47ea0c */
	ST(0) = -ST(0);	/* 47ea0a: fchs  */
L_47ea0c:
	{ long double t = ST(1); FPUSH(t); }	/* 47ea0c: fld st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47ea0e: fcomp dword ptr [0x4a93e8] */
	{ long double t = ST(1); FPUSH(t); }	/* 47ea14: fld st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ea16: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ea18: test ah, 1 */
	if (m->zf) goto L_47ea1f;	/* 47ea1b: je 0x47ea1f */
	ST(0) = -ST(0);	/* 47ea1d: fchs  */
L_47ea1f:
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47ea1f: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP();	/* 47ea21: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ea23: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ea25: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 47ea28: fstp st(0) */
	if (m->zf) goto L_47ea32;	/* 47ea2a: je 0x47ea32 */
	ST(0) = ST(0); FPOP();	/* 47ea2c: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47ea2e: fld dword ptr [esp + 0x34] */
L_47ea32:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 47ea32: fcom dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ea38: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ea3a: test ah, 0x41 */
	if (!m->zf) goto L_47ea49;	/* 47ea3d: jne 0x47ea49 */
	ST(0) = ST(0); FPOP();	/* 47ea3f: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 47ea41: fld dword ptr [0x4a9424] */
	goto L_47ea5e;	/* 47ea47: jmp 0x47ea5e */
L_47ea49:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u));	/* 47ea49: fcom dword ptr [0x4a9474] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ea4f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ea51: test ah, 1 */
	if (m->zf) goto L_47ea5e;	/* 47ea54: je 0x47ea5e */
	ST(0) = ST(0); FPOP();	/* 47ea56: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 47ea58: fld dword ptr [0x4a9474] */
L_47ea5e:
	{ long double t = ST(0); FPUSH(t); }	/* 47ea5e: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47ea60: fmul dword ptr [esp + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ea64: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ea65: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ea68: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 47ea69: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47ea6b: fmul dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ea6f: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47ea72: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(1);	/* 47ea76: fmul st(1) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ea78: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47ea79: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ea7d: fstp dword ptr [esp] */
	ST(0) = ST(0); FPOP();	/* 47ea80: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x47ea87u; lift_4722c0(m);	/* 47ea82: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47ea87: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47ea89: fld dword ptr [esp + 0x68] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ea8d: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ea90: push ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47ea91: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47ea95: mov dword ptr [esp + 0x14], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ea99: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47ea9c: mov dword ptr [esp + 0x1c], eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47eaa0: fadd dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eaa4: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47eaa7: fld dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47eaab: fadd dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eaaf: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eab0: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47eab3: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x68u));	/* 47eab7: fadd dword ptr [esp + 0x68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eabb: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47eabc: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eac3: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47eacbu; lift_4722c0(m);	/* 47eac6: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47eacb: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47eacd: fld dword ptr [esi + 8] */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 47ead0: mov dword ptr [esp + 0x54], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ead4: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 47ead7: mov dword ptr [esp + 0x58], edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eadb: push ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47eadc: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47eadf: mov dword ptr [esp + 0x60], eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 47eae3: fsub dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eae7: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47eaea: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 47eaed: fsub dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eaf1: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eaf2: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47eaf5: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 47eaf7: fsub dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eafb: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47eafc: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eb00: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47eb08u; lift_4722c0(m);	/* 47eb03: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47eb08: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 47eb0a: mov dword ptr [esp + 0x44], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47eb0e: fld dword ptr [esp + 0x44] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47eb12: mov edx, dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 47eb15: fmul dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 47eb19: mov dword ptr [esp + 0x48], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47eb1d: mov eax, dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47eb20: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47eb24: fmul dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 47eb28: mov dword ptr [esp + 0x4c], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47eb2c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47eb2e: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47eb32: fmul dword ptr [esp + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47eb36: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47eb38: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47eb3e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47eb40: test ah, 0x41 */
	if (m->zf) goto L_47eb62;	/* 47eb43: je 0x47eb62 */
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 47eb45: mov ecx, dword ptr [0xa0e7e8] */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 47eb4b: mov edx, dword ptr [0xa0e7ec] */
	m->eax = M32((DWORD)(0xa0e7f0u));	/* 47eb51: mov eax, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 47eb56: mov dword ptr [esp + 0x44], ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 47eb5a: mov dword ptr [esp + 0x48], edx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 47eb5e: mov dword ptr [esp + 0x4c], eax */
L_47eb62:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47eb62: fld dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47eb66: fld dword ptr [esp + 0x48] */
	{ long double t = ST(0); FPUSH(t); }	/* 47eb6a: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47eb6c: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47eb6e: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47eb70: fmul st(3) */
	m->ecx = M32((DWORD)(m->esp + 0xb0u));	/* 47eb72: mov ecx, dword ptr [esp + 0xb0] */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 47eb79: mov eax, dword ptr [esp + 0x54] */
	m->edx = m->esi;	/* 47eb7d: mov edx, esi */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47eb7f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47eb81: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47eb85: fmul dword ptr [esp + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47eb89: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47eb8b: fsqrt  */
	ST(2) = ST(0); FPOP();	/* 47eb8d: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 47eb8f: fstp st(0) */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 47eb91: fstp dword ptr [ecx] */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 47eb93: mov ecx, dword ptr [esp + 0x58] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47eb97: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 47eb99: mov eax, dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eb9d: push ecx */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47eb9e: mov dword ptr [edx + 4], ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47eba1: mov dword ptr [edx + 8], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47eba4: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 47eba7: fsub dword ptr [ebx + 8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ebaa: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47ebad: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 47ebb0: fsub dword ptr [ebx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ebb3: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ebb4: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47ebb7: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 47ebb9: fsub dword ptr [ebx] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ebbb: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47ebbc: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ebc0: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47ebc8u; lift_4722c0(m);	/* 47ebc3: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47ebc8: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 47ebca: mov dword ptr [esp + 0x28], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ebce: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 47ebd1: mov dword ptr [esp + 0x2c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ebd5: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 47ebd8: mov dword ptr [esp + 0x30], eax */
	m->eax = M32((DWORD)(m->esp + 0xb8u));	/* 47ebdc: mov eax, dword ptr [esp + 0xb8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47ebe3: test eax, eax */
	if (!m->zf) goto L_47edb5;	/* 47ebe5: jne 0x47edb5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47ebeb: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 47ebef: fmul dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47ebf3: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47ebf7: fmul dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ebfb: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ebfc: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ebfe: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47ec01: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47ec05: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47ec09: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47ec0d: fmul dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ec11: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ec12: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ec14: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47ec17: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47ec1b: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47ec1f: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 47ec23: fmul dword ptr [esp + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ec27: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47ec28: lea ecx, [esp + 0x78] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ec2c: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ec2e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47ec36u; lift_4722c0(m);	/* 47ec31: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47ec36: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47ec38: mov dword ptr [esp + 0x10], ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ec3c: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47ec3d: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 47ec41: fmul dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ec45: mov edx, dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47ec48: fld dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47ec4c: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ec50: mov eax, dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47ec53: fmul dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47ec57: mov dword ptr [esp + 0x1c], eax */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ec5b: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ec5d: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47ec60: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47ec64: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47ec68: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47ec6c: fmul dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ec70: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ec71: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ec73: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47ec76: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47ec7a: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47ec7e: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47ec82: fmul dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ec86: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47ec87: lea ecx, [esp + 0x84] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ec8e: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ec90: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47ec98u; lift_4722c0(m);	/* 47ec93: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47ec98: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 47ec9a: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47ec9e: lea ecx, [esp + 0x1c] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47eca2: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 47eca5: mov dword ptr [esp + 0x20], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47eca9: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47ecac: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x47ecb5u; lift_467760(m);	/* 47ecb0: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47ecb5: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ecbb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ecbd: test ah, 1 */
	if (!m->zf) goto L_47f62e;	/* 47ecc0: jne 0x47f62e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47ecc6: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47ecca: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47ecce: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47ecd2: fmul dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ecd6: push ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47ecd7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47ecd9: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47ecdd: fmul dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47ece1: faddp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 47ece3: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47ece5: fmul dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47ece9: fstp dword ptr [esp + 0x20] */
	{ long double t = ST(0); FPUSH(t); }	/* 47eced: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47ecef: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47ecf3: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47ecf7: fmul dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 47ecfb: fst dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47ecff: fsub dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ed03: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47ed06: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47ed0a: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ed0e: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ed0f: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47ed12: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47ed16: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ed1a: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47ed1b: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ed1f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47ed27u; lift_4722c0(m);	/* 47ed22: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47ed27: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ed29: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47ed2a: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ed2e: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47ed31: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ed35: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47ed38: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47ed3c: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47ed40: fmul dword ptr [esp + 0xa8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ed47: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47ed4a: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47ed4e: fmul dword ptr [esp + 0xa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ed55: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ed56: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47ed59: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xacu));	/* 47ed5d: fmul dword ptr [esp + 0xac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ed64: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47ed65: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ed6c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47ed74u; lift_4722c0(m);	/* 47ed6f: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47ed74: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ed76: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47ed77: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ed7b: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47ed7e: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ed82: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47ed85: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47ed89: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47ed8d: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ed91: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47ed94: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47ed98: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ed9c: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ed9d: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47eda0: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47eda4: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eda8: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47eda9: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47edad: fstp dword ptr [esp] */
	goto L_47f60d;	/* 47edb0: jmp 0x47f60d */
L_47edb5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47edb5: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 47edb9: fmul dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47edbc: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 47edc0: fmul dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47edc2: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47edc3: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47edc5: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47edc8: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 47edcc: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47edce: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 47edd2: fmul dword ptr [eax + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47edd5: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47edd6: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47edd8: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47eddb: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 47eddf: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47ede2: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 47ede6: fmul dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ede9: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47edea: lea ecx, [esp + 0x78] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47edee: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47edf0: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47edf8u; lift_4722c0(m);	/* 47edf3: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47edf8: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 47edfa: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47edfe: lea ecx, [esp + 0x1c] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ee02: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 47ee05: mov dword ptr [esp + 0x20], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ee09: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47ee0c: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x47ee15u; lift_467760(m);	/* 47ee10: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47ee15: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47ee1b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47ee1d: test ah, 1 */
	if (!m->zf) goto L_47ef2e;	/* 47ee20: jne 0x47ef2e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47ee26: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47ee2a: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47ee2e: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47ee32: fmul dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ee36: push ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47ee37: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47ee39: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47ee3d: fmul dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47ee41: faddp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 47ee43: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47ee45: fmul dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47ee49: fstp dword ptr [esp + 0x20] */
	{ long double t = ST(0); FPUSH(t); }	/* 47ee4d: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47ee4f: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47ee53: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47ee57: fmul dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 47ee5b: fst dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47ee5f: fsub dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ee63: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47ee66: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47ee6a: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ee6e: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ee6f: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47ee72: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47ee76: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ee7a: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47ee7b: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ee7f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47ee87u; lift_4722c0(m);	/* 47ee82: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47ee87: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ee89: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47ee8a: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ee8e: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47ee91: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ee95: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47ee98: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47ee9c: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47eea0: fmul dword ptr [esp + 0xa8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eea7: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47eeaa: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47eeae: fmul dword ptr [esp + 0xa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eeb5: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eeb6: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47eeb9: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xacu));	/* 47eebd: fmul dword ptr [esp + 0xac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eec4: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47eec5: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eecc: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47eed4u; lift_4722c0(m);	/* 47eecf: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47eed4: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eed6: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47eed7: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47eedb: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47eede: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47eee2: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47eee5: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47eee9: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47eeed: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eef1: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47eef4: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47eef8: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47eefc: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47eefd: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47ef00: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47ef04: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ef08: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47ef09: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ef0d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47ef15u; lift_4722c0(m);	/* 47ef10: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47ef15: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47ef1c: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47ef1e: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47ef20: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47ef23: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47ef26: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47ef29: mov dword ptr [ecx + 8], eax */
	goto L_47ef4e;	/* 47ef2c: jmp 0x47ef4e */
L_47ef2e:
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47ef2e: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 47ef35: mov edx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47ef3b: mov dword ptr [ecx], edx */
	m->eax = M32((DWORD)(0xa0e7ecu));	/* 47ef3d: mov eax, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47ef42: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 47ef45: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47ef4b: mov dword ptr [ecx + 8], edx */
L_47ef4e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47ef4e: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47ef52: fmul dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47ef56: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 47ef5a: fmul dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ef5e: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ef5f: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ef61: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47ef64: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47ef68: fmul dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47ef6c: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47ef70: fmul dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ef74: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ef75: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ef77: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47ef7a: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 47ef7e: fmul dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47ef82: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47ef86: fmul dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ef8a: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47ef8b: lea ecx, [esp + 0x78] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47ef8f: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ef91: fstp dword ptr [esp] */
	goto L_47e7ca;	/* 47ef94: jmp 0x47e7ca */
L_47ef99:
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 47ef99: fsub dword ptr [edi + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47ef9c: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47ef9d: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47efa0: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47efa3: fsub dword ptr [edi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47efa6: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47efa7: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47efaa: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47efac: fsub dword ptr [edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47efaf: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47efb0: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47efb4: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47efbcu; lift_4722c0(m);	/* 47efb7: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47efbc: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47efbe: mov dword ptr [esp + 0x10], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47efc2: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 47efc5: mov dword ptr [esp + 0x14], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47efc9: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 47efcc: mov dword ptr [esp + 0x18], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47efd0: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47efd4: fmul dword ptr [edi + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47efd7: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47efdb: fmul dword ptr [edi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47efde: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47efe0: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47efe4: fmul dword ptr [edi + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47efe7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47efe9: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47efed: fld dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47eff1: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47eff5: fmul dword ptr [esp + 0x10] */
	{ long double t = ST(1); FPUSH(t); }	/* 47eff9: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 47effb: fmul st(2) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47effd: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47efff: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47f001: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f003: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47f005: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 47f007: fmul st(4) */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f009: fsubp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x34u)); FPOP();	/* 47f00b: fcomp dword ptr [esp + 0x34] */
	ST(0) = ST(0); FPOP();	/* 47f00f: fstp st(0) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f011: fnstsw ax */
	ST(0) = ST(0); FPOP();	/* 47f013: fstp st(0) */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f015: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 47f018: fstp st(0) */
	if (!m->zf) goto L_47f02b;	/* 47f01a: jne 0x47f02b */
	m->edi = M32(m->esp); m->esp += 4;	/* 47f01c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47f01d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47f01e: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47f01f: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47f021: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47f022: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47f028: ret 0x24 */
L_47f02b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47f02b: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 47f02f: fsub dword ptr [edi + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f032: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f033: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47f036: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47f03a: fsub dword ptr [edi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f03d: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f03e: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47f041: fld dword ptr [esp + 0x68] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47f045: fsub dword ptr [edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f048: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f049: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f04d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f055u; lift_4722c0(m);	/* 47f050: call 0x4722c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47f055: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47f059: fmul dword ptr [edi + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47f05c: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47f060: fmul dword ptr [edi + 0x30] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f063: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47f065: mov dword ptr [esp + 0x10], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f069: mov edx, dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f06c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47f06e: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47f072: fmul dword ptr [edi + 0x28] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f075: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 47f078: mov dword ptr [esp + 0x14], edx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 47f07c: mov dword ptr [esp + 0x18], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f080: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f082: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47f086: fmul dword ptr [edi + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f089: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47f08d: fmul dword ptr [edi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f090: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47f092: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47f096: fmul dword ptr [edi + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f099: faddp st(1) */
	MF((DWORD)(m->esp + 0x84u)) = (float)ST(0); FPOP();	/* 47f09b: fstp dword ptr [esp + 0x84] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47f0a2: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 47f0a6: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47f0aa: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47f0ae: fmul dword ptr [esp + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f0b2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47f0b4: fld dword ptr [esp + 0x40] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47f0b8: fmul dword ptr [esp + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f0bc: faddp st(1) */
	{ long double t = ST(1); FPUSH(t); }	/* 47f0be: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 47f0c0: fmul st(2) */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f0c2: fsubp st(1) */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0);	/* 47f0c4: fst dword ptr [esp + 0x50] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47f0c8: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 47f0ce: fld dword ptr [esp + 0x50] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f0d2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f0d4: test ah, 1 */
	if (m->zf) goto L_47f0db;	/* 47f0d7: je 0x47f0db */
	ST(0) = -ST(0);	/* 47f0d9: fchs  */
L_47f0db:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47f0db: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f0e1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f0e3: test ah, 1 */
	if (m->zf) goto L_47f0f9;	/* 47f0e6: je 0x47f0f9 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47f0e8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47f0e9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47f0ea: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47f0eb: xor eax, eax */
	ST(0) = ST(0); FPOP();	/* 47f0ed: fstp st(0) */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47f0ef: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47f0f0: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47f0f6: ret 0x24 */
L_47f0f9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47f0f9: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 47f0fd: fmul dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f101: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47f105: fmul dword ptr [esp + 0x3c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f109: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f10b: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47f10f: fmul dword ptr [esp + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f113: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 47f115: fld dword ptr [esp + 0x84] */
	ST(0) = ST(0) * ST(2);	/* 47f11c: fmul st(2) */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f11e: fsubp st(1) */
	ST(1) = ST(0); FPOP();	/* 47f120: fstp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f122: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f126: fld dword ptr [esp + 0x14] */
	{ long double t = ST(2); FPUSH(t); }	/* 47f12a: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47f12c: fmul st(3) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47f12e: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 47f132: fmul dword ptr [esp + 0x10] */
	{ long double t = ST(2); FPUSH(t); }	/* 47f136: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47f138: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f13a: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 47f13c: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 47f13e: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f140: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x84u)));	/* 47f142: fld dword ptr [esp + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x84u));	/* 47f149: fmul dword ptr [esp + 0x84] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f150: fsubp st(1) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47f152: fsub dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47f156: fmul dword ptr [esp + 0x50] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f15a: fsubp st(1) */
	ST(2) = ST(0); FPOP();	/* 47f15c: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 47f15e: fstp st(0) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u));	/* 47f160: fcom dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f166: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f168: test ah, 1 */
	if (m->zf) goto L_47f180;	/* 47f16b: je 0x47f180 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47f16d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47f16e: pop esi */
	ST(0) = ST(0); FPOP();	/* 47f16f: fstp st(0) */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47f171: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 47f172: xor eax, eax */
	ST(0) = ST(0); FPOP();	/* 47f174: fstp st(0) */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47f176: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47f177: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47f17d: ret 0x24 */
L_47f180:
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47f180: fsqrt  */
	{ long double t = ST(0); FPUSH(t); }	/* 47f182: fld st(0) */
	ST(0) = ST(0) - ST(2);	/* 47f184: fsub st(2) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47f186: fdiv dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47f18a: fstp dword ptr [esp + 0x34] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47f18e: fxch st(1) */
	ST(0) = -ST(0);	/* 47f190: fchs  */
	ST(0) = ST(0) - ST(1);	/* 47f192: fsub st(1) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47f194: fdiv dword ptr [esp + 0x50] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47f198: fxch st(1) */
	ST(0) = ST(0); FPOP();	/* 47f19a: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f19c: fld dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47f1a0: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f1a6: fld dword ptr [esp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f1aa: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f1ac: test ah, 1 */
	if (m->zf) goto L_47f1b3;	/* 47f1af: je 0x47f1b3 */
	ST(0) = -ST(0);	/* 47f1b1: fchs  */
L_47f1b3:
	{ long double t = ST(1); FPUSH(t); }	/* 47f1b3: fld st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47f1b5: fcomp dword ptr [0x4a93e8] */
	{ long double t = ST(1); FPUSH(t); }	/* 47f1bb: fld st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f1bd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f1bf: test ah, 1 */
	if (m->zf) goto L_47f1c6;	/* 47f1c2: je 0x47f1c6 */
	ST(0) = -ST(0);	/* 47f1c4: fchs  */
L_47f1c6:
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47f1c6: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP();	/* 47f1c8: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f1ca: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f1cc: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 47f1cf: fstp st(0) */
	if (m->zf) goto L_47f1d9;	/* 47f1d1: je 0x47f1d9 */
	ST(0) = ST(0); FPOP();	/* 47f1d3: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f1d5: fld dword ptr [esp + 0x34] */
L_47f1d9:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 47f1d9: fcom dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f1df: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f1e1: test ah, 0x41 */
	if (!m->zf) goto L_47f1f0;	/* 47f1e4: jne 0x47f1f0 */
	ST(0) = ST(0); FPOP();	/* 47f1e6: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 47f1e8: fld dword ptr [0x4a9424] */
	goto L_47f205;	/* 47f1ee: jmp 0x47f205 */
L_47f1f0:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u));	/* 47f1f0: fcom dword ptr [0x4a9474] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f1f6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f1f8: test ah, 1 */
	if (m->zf) goto L_47f205;	/* 47f1fb: je 0x47f205 */
	ST(0) = ST(0); FPOP();	/* 47f1fd: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 47f1ff: fld dword ptr [0x4a9474] */
L_47f205:
	{ long double t = ST(0); FPUSH(t); }	/* 47f205: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47f207: fmul dword ptr [esp + 0x40] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f20b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f20c: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f20f: push ecx */
	{ long double t = ST(0); FPUSH(t); }	/* 47f210: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47f212: fmul dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f216: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 47f219: fld dword ptr [esp + 0x40] */
	ST(0) = ST(0) * ST(1);	/* 47f21d: fmul st(1) */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f21f: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f220: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f224: fstp dword ptr [esp] */
	ST(0) = ST(0); FPOP();	/* 47f227: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x47f22eu; lift_4722c0(m);	/* 47f229: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f22e: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47f230: fld dword ptr [esp + 0x68] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f234: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f237: push ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47f238: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47f23c: mov dword ptr [esp + 0x14], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f240: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47f243: mov dword ptr [esp + 0x1c], eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47f247: fadd dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f24b: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 47f24e: fld dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47f252: fadd dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f256: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f257: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f25a: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x68u));	/* 47f25e: fadd dword ptr [esp + 0x68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f262: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47f263: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f26a: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f272u; lift_4722c0(m);	/* 47f26d: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f272: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47f274: fld dword ptr [esi + 8] */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 47f277: mov dword ptr [esp + 0x54], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f27b: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 47f27e: mov dword ptr [esp + 0x58], edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f282: push ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f283: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 47f286: mov dword ptr [esp + 0x60], eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x60u));	/* 47f28a: fsub dword ptr [esp + 0x60] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f28e: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47f291: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 47f294: fsub dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f298: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f299: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47f29c: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 47f29e: fsub dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f2a2: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f2a3: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f2a7: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f2afu; lift_4722c0(m);	/* 47f2aa: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f2af: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 47f2b1: mov dword ptr [esp + 0x44], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47f2b5: fld dword ptr [esp + 0x44] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f2b9: mov edx, dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 47f2bc: fmul dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 47f2c0: mov dword ptr [esp + 0x48], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f2c4: mov eax, dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47f2c7: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47f2cb: fmul dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 47f2cf: mov dword ptr [esp + 0x4c], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f2d3: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47f2d5: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 47f2d9: fmul dword ptr [esp + 0x40] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f2dd: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47f2df: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f2e5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f2e7: test ah, 0x41 */
	if (m->zf) goto L_47f309;	/* 47f2ea: je 0x47f309 */
	m->ecx = M32((DWORD)(0xa0e7e8u));	/* 47f2ec: mov ecx, dword ptr [0xa0e7e8] */
	m->edx = M32((DWORD)(0xa0e7ecu));	/* 47f2f2: mov edx, dword ptr [0xa0e7ec] */
	m->eax = M32((DWORD)(0xa0e7f0u));	/* 47f2f8: mov eax, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 47f2fd: mov dword ptr [esp + 0x44], ecx */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 47f301: mov dword ptr [esp + 0x48], edx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 47f305: mov dword ptr [esp + 0x4c], eax */
L_47f309:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47f309: fld dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 47f30d: fld dword ptr [esp + 0x48] */
	{ long double t = ST(0); FPUSH(t); }	/* 47f311: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 47f313: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 47f315: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 47f317: fmul st(3) */
	m->ecx = M32((DWORD)(m->esp + 0xb0u));	/* 47f319: mov ecx, dword ptr [esp + 0xb0] */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 47f320: mov eax, dword ptr [esp + 0x54] */
	m->edx = m->esi;	/* 47f324: mov edx, esi */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f326: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 47f328: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47f32c: fmul dword ptr [esp + 0x44] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f330: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 47f332: fsqrt  */
	ST(2) = ST(0); FPOP();	/* 47f334: fstp st(2) */
	ST(0) = ST(0); FPOP();	/* 47f336: fstp st(0) */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 47f338: fstp dword ptr [ecx] */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 47f33a: mov ecx, dword ptr [esp + 0x58] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47f33e: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 47f340: mov eax, dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f344: push ecx */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47f345: mov dword ptr [edx + 4], ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47f348: mov dword ptr [edx + 8], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 47f34b: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 47f34e: fsub dword ptr [edi + 0xc] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f351: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 47f354: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 47f357: fsub dword ptr [edi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f35a: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f35b: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 47f35e: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 47f360: fsub dword ptr [edi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f363: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f364: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f368: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f370u; lift_4722c0(m);	/* 47f36b: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f370: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47f372: mov dword ptr [esp + 0x10], ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f376: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f377: fld dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f37b: mov edx, dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47f37e: fmul dword ptr [edi + 0x2c] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47f381: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f385: mov eax, dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f388: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47f38c: fmul dword ptr [edi + 0x28] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47f38f: mov dword ptr [esp + 0x1c], eax */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f393: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f395: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f398: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47f39c: fmul dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f39f: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47f3a3: fmul dword ptr [edi + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f3a6: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f3a7: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f3a9: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f3ac: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47f3b0: fmul dword ptr [edi + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47f3b3: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47f3b7: fmul dword ptr [edi + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f3ba: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47f3bb: lea ecx, [esp + 0x84] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f3c2: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f3c4: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f3ccu; lift_4722c0(m);	/* 47f3c7: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f3cc: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47f3ce: mov dword ptr [esp + 0x10], ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f3d2: push ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f3d3: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47f3d6: mov dword ptr [esp + 0x18], edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f3da: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47f3de: fmul dword ptr [edi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f3e1: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47f3e5: fmul dword ptr [edi + 0x2c] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f3e8: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47f3eb: mov dword ptr [esp + 0x1c], eax */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f3ef: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f3f1: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f3f4: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47f3f8: fmul dword ptr [edi + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f3fb: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 47f3ff: fmul dword ptr [edi + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f402: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f403: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f405: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47f408: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47f40c: fmul dword ptr [edi + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f40f: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47f413: fmul dword ptr [edi + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f416: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47f417: lea ecx, [esp + 0x1c] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f41b: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f41d: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f425u; lift_4722c0(m);	/* 47f420: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f425: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 47f427: mov dword ptr [esp + 0x28], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f42b: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 47f42e: mov dword ptr [esp + 0x2c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f432: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 47f435: mov dword ptr [esp + 0x30], eax */
	m->eax = M32((DWORD)(m->esp + 0xb8u));	/* 47f439: mov eax, dword ptr [esp + 0xb8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47f440: test eax, eax */
	if (!m->zf) goto L_47f653;	/* 47f442: jne 0x47f653 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47f448: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 47f44c: fmul dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47f450: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 47f454: fmul dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f458: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f459: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f45b: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47f45e: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47f462: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 47f466: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47f46a: fmul dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f46e: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f46f: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f471: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47f474: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47f478: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f47c: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 47f480: fmul dword ptr [esp + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f484: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f485: lea ecx, [esp + 0x78] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f489: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f48b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f493u; lift_4722c0(m);	/* 47f48e: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f493: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 47f495: mov dword ptr [esp + 0x10], ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f499: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f49a: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 47f49e: fmul dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f4a2: mov edx, dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47f4a5: fld dword ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47f4a9: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f4ad: mov eax, dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47f4b0: fmul dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47f4b4: mov dword ptr [esp + 0x1c], eax */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f4b8: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f4ba: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47f4bd: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47f4c1: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47f4c5: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47f4c9: fmul dword ptr [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f4cd: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f4ce: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f4d0: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47f4d3: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 47f4d7: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f4db: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47f4df: fmul dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f4e3: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47f4e4: lea ecx, [esp + 0x84] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f4eb: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f4ed: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f4f5u; lift_4722c0(m);	/* 47f4f0: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f4f5: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 47f4f7: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47f4fb: lea ecx, [esp + 0x1c] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f4ff: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 47f502: mov dword ptr [esp + 0x20], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f506: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47f509: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x47f512u; lift_467760(m);	/* 47f50d: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47f512: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f518: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f51a: test ah, 1 */
	if (!m->zf) goto L_47f62e;	/* 47f51d: jne 0x47f62e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f523: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47f527: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47f52b: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47f52f: fmul dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f533: push ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f534: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47f536: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47f53a: fmul dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f53e: faddp st(1) */
	{ long double t = ST(0); FPUSH(t); }	/* 47f540: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x20u));	/* 47f542: fmul dword ptr [esp + 0x20] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47f546: fstp dword ptr [esp + 0x20] */
	{ long double t = ST(0); FPUSH(t); }	/* 47f54a: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47f54c: fmul dword ptr [esp + 0x24] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47f550: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47f554: fmul dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0);	/* 47f558: fst dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47f55c: fsub dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f560: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47f563: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47f567: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f56b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f56c: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47f56f: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47f573: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f577: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f578: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f57c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f584u; lift_4722c0(m);	/* 47f57f: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f584: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f586: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47f587: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f58b: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47f58e: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f592: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47f595: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f599: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47f59d: fmul dword ptr [esp + 0xa8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f5a4: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f5a7: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47f5ab: fmul dword ptr [esp + 0xa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f5b2: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f5b3: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 47f5b6: fld dword ptr [esp + 0xac] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47f5bd: fmul dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f5c1: push ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 47f5c2: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f5c9: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f5d1u; lift_4722c0(m);	/* 47f5cc: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f5d1: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f5d3: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47f5d4: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f5d8: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47f5db: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f5df: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47f5e2: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f5e6: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x28u));	/* 47f5ea: fadd dword ptr [esp + 0x28] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f5ee: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f5f1: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47f5f5: fadd dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f5f9: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f5fa: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47f5fd: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 47f601: fadd dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f605: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47f606: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f60a: fstp dword ptr [esp] */
L_47f60d:
	m->esp -= 4; M32(m->esp) = 0x47f612u; lift_4722c0(m);	/* 47f60d: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47f612: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47f619: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47f61b: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f61d: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47f620: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f623: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47f626: mov dword ptr [ecx + 8], eax */
	goto L_47e7e3;	/* 47f629: jmp 0x47e7e3 */
L_47f62e:
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47f62e: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 47f635: mov edx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47f63b: mov dword ptr [ecx], edx */
	m->eax = M32((DWORD)(0xa0e7ecu));	/* 47f63d: mov eax, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47f642: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 47f645: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47f64b: mov dword ptr [ecx + 8], edx */
	goto L_47e7e3;	/* 47f64e: jmp 0x47e7e3 */
L_47f653:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47f653: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 47f657: fmul dword ptr [eax + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47f65a: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 47f65e: fmul dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f660: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f661: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f663: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f666: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 47f66a: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 47f66c: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 47f670: fmul dword ptr [eax + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f673: push ecx */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f674: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f676: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f679: fld dword ptr [esp + 0x34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 47f67d: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 47f680: fld dword ptr [esp + 0x38] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 47f684: fmul dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f687: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f688: lea ecx, [esp + 0x78] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 47f68c: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f68e: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f696u; lift_4722c0(m);	/* 47f691: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f696: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 47f698: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47f69c: lea ecx, [esp + 0x1c] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f6a0: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 47f6a3: mov dword ptr [esp + 0x20], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f6a7: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47f6aa: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x47f6b3u; lift_467760(m);	/* 47f6ae: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47f6b3: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f6b9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f6bb: test ah, 1 */
	if (!m->zf) goto L_47f7cf;	/* 47f6be: jne 0x47f7cf */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f6c4: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 47f6c8: fmul dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47f6cc: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47f6d0: fmul dword ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f6d4: push ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f6d5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 47f6d7: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 47f6db: fmul dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47f6df: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 47f6e1: fld dword ptr [esp + 0x20] */
	ST(0) = ST(0) * ST(1);	/* 47f6e5: fmul st(1) */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 47f6e7: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47f6eb: fld dword ptr [esp + 0x24] */
	ST(0) = ST(0) * ST(1);	/* 47f6ef: fmul st(1) */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 47f6f1: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47f6f5: fld dword ptr [esp + 0x28] */
	ST(0) = ST(0) * ST(1);	/* 47f6f9: fmul st(1) */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 47f6fb: fstp dword ptr [esp + 0x28] */
	ST(0) = ST(0); FPOP();	/* 47f6ff: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 47f701: fld dword ptr [esp + 0x28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x50u));	/* 47f705: fsub dword ptr [esp + 0x50] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f709: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47f70c: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47f710: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f714: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f715: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 47f718: fld dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 47f71c: fsub dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f720: push ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f721: lea ecx, [esp + 0x78] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f725: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f72du; lift_4722c0(m);	/* 47f728: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f72d: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f72f: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 47f730: mov dword ptr [esp + 0x14], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f734: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 47f737: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f73b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 47f73e: mov dword ptr [esp + 0x1c], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 47f742: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47f746: fmul dword ptr [esp + 0xa8] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f74d: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f750: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xa8u));	/* 47f754: fmul dword ptr [esp + 0xa8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f75b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f75c: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47f75f: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xacu));	/* 47f763: fmul dword ptr [esp + 0xac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f76a: push ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47f76b: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f76f: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x47f777u; lift_4722c0(m);	/* 47f772: call 0x4722c0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f777: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x78u)) = m->ecx;	/* 47f779: mov dword ptr [esp + 0x78], ecx */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47f77d: lea ecx, [esp + 0x78] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f781: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f784: push ecx */
	M32((DWORD)(m->esp + 0x80u)) = m->edx;	/* 47f785: mov dword ptr [esp + 0x80], edx */
	m->edx = (DWORD)(m->esp + 0x8cu);	/* 47f78c: lea edx, [esp + 0x8c] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f793: mov eax, dword ptr [eax + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f796: push edx */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 47f797: lea ecx, [esp + 0x24] */
	M32((DWORD)(m->esp + 0x88u)) = m->eax;	/* 47f79b: mov dword ptr [esp + 0x88], eax */
	m->esp -= 4; M32(m->esp) = 0x47f7a7u; lift_4802d0(m);	/* 47f7a2: call 0x4802d0 */
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47f7a7: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47f7ae: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47f7b0: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f7b2: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47f7b5: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f7b8: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47f7bb: mov dword ptr [ecx + 8], eax */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 47f7be: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f7c2: push eax */
	m->ecx = (DWORD)(m->esp + 0x8cu);	/* 47f7c3: lea ecx, [esp + 0x8c] */
	goto L_47fb25;	/* 47f7ca: jmp 0x47fb25 */
L_47f7cf:
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47f7cf: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 47f7d6: mov edx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47f7dc: mov dword ptr [ecx], edx */
	m->eax = M32((DWORD)(0xa0e7ecu));	/* 47f7de: mov eax, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47f7e3: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 47f7e6: mov edx, dword ptr [0xa0e7f0] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 47f7ec: lea eax, [esp + 0x1c] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47f7f0: mov dword ptr [ecx + 8], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f7f3: push eax */
	m->ecx = (DWORD)(m->esp + 0x8cu);	/* 47f7f4: lea ecx, [esp + 0x8c] */
	goto L_47fb25;	/* 47f7fb: jmp 0x47fb25 */
L_47f800:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 47f800: fld dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x98u));	/* 47f804: fadd dword ptr [esp + 0x98] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47f80b: fdiv dword ptr [esp + 0x34] */
	ST(0) = -ST(0);	/* 47f80f: fchs  */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 47f811: fld dword ptr [esp + 0x50] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x98u));	/* 47f815: fsub dword ptr [esp + 0x98] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 47f81c: fdiv dword ptr [esp + 0x34] */
	ST(0) = -ST(0);	/* 47f820: fchs  */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47f822: fstp dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 47f826: fcom dword ptr [0x4a93e8] */
	{ long double t = ST(0); FPUSH(t); }	/* 47f82c: fld st(0) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f82e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f830: test ah, 1 */
	if (m->zf) goto L_47f837;	/* 47f833: je 0x47f837 */
	ST(0) = -ST(0);	/* 47f835: fchs  */
L_47f837:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f837: fld dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47f83b: fcomp dword ptr [0x4a93e8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f841: fld dword ptr [esp + 0x34] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f845: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f847: test ah, 1 */
	if (m->zf) goto L_47f84e;	/* 47f84a: je 0x47f84e */
	ST(0) = -ST(0);	/* 47f84c: fchs  */
L_47f84e:
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 47f84e: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP();	/* 47f850: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f852: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f854: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 47f857: fstp st(0) */
	if (m->zf) goto L_47f861;	/* 47f859: je 0x47f861 */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 47f85b: fstp dword ptr [esp + 0x34] */
	goto L_47f86b;	/* 47f85f: jmp 0x47f86b */
L_47f861:
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 47f861: mov edx, dword ptr [esp + 0x34] */
	ST(0) = ST(0); FPOP();	/* 47f865: fstp st(0) */
	M32((DWORD)(m->esp + 0x34u)) = m->edx;	/* 47f867: mov dword ptr [esp + 0x34], edx */
L_47f86b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f86b: fld dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 47f86f: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f875: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f877: test ah, 0x41 */
	if (!m->zf) goto L_47f886;	/* 47f87a: jne 0x47f886 */
	M32((DWORD)(m->esp + 0x34u)) = 0x3f800000u;	/* 47f87c: mov dword ptr [esp + 0x34], 0x3f800000 */
	goto L_47f89f;	/* 47f884: jmp 0x47f89f */
L_47f886:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 47f886: fld dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9474u)); FPOP();	/* 47f88a: fcomp dword ptr [0x4a9474] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f890: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f892: test ah, 1 */
	if (m->zf) goto L_47f89f;	/* 47f895: je 0x47f89f */
	M32((DWORD)(m->esp + 0x34u)) = 0xbf800000u;	/* 47f897: mov dword ptr [esp + 0x34], 0xbf800000 */
L_47f89f:
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 47f89f: mov eax, dword ptr [esp + 0x34] */
	m->ecx = (DWORD)(m->esp + 0x88u);	/* 47f8a3: lea ecx, [esp + 0x88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f8aa: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f8ab: push ecx */
	m->ecx = (DWORD)(m->esp + 0x40u);	/* 47f8ac: lea ecx, [esp + 0x40] */
	m->esp -= 4; M32(m->esp) = 0x47f8b5u; lift_480370(m);	/* 47f8b0: call 0x480370 */
	m->edx = (DWORD)(m->esp + 0x6cu);	/* 47f8b5: lea edx, [esp + 0x6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f8b9: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f8ba: push edx */
	m->ecx = (DWORD)(m->esp + 0x68u);	/* 47f8bb: lea ecx, [esp + 0x68] */
	m->esp -= 4; M32(m->esp) = 0x47f8c4u; lift_4802d0(m);	/* 47f8bf: call 0x4802d0 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f8c4: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 47f8c6: mov dword ptr [esp + 0x54], ecx */
	m->ecx = (DWORD)(m->esp + 0x54u);	/* 47f8ca: lea ecx, [esp + 0x54] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f8ce: mov edx, dword ptr [eax + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f8d1: push ecx */
	M32((DWORD)(m->esp + 0x5cu)) = m->edx;	/* 47f8d2: mov dword ptr [esp + 0x5c], edx */
	m->edx = (DWORD)(m->esp + 0x8cu);	/* 47f8d6: lea edx, [esp + 0x8c] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f8dd: mov eax, dword ptr [eax + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f8e0: push edx */
	m->ecx = m->esi;	/* 47f8e1: mov ecx, esi */
	M32((DWORD)(m->esp + 0x64u)) = m->eax;	/* 47f8e3: mov dword ptr [esp + 0x64], eax */
	m->esp -= 4; M32(m->esp) = 0x47f8ecu; lift_480320(m);	/* 47f8e7: call 0x480320 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47f8ec: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 47f8ee: mov dword ptr [esp + 0x44], ecx */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 47f8f2: lea ecx, [esp + 0x44] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47f8f6: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 47f8f9: mov dword ptr [esp + 0x48], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47f8fd: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 47f900: mov dword ptr [esp + 0x4c], eax */
	m->esp -= 4; M32(m->esp) = 0x47f909u; lift_480400(m);	/* 47f904: call 0x480400 */
	m->ecx = M32((DWORD)(m->esp + 0xb0u));	/* 47f909: mov ecx, dword ptr [esp + 0xb0] */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 47f910: mov eax, dword ptr [esp + 0x54] */
	m->edx = m->esi;	/* 47f914: mov edx, esi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47f916: push esi */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 47f917: fstp dword ptr [ecx] */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 47f919: mov ecx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 47f91d: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x60u));	/* 47f91f: mov eax, dword ptr [esp + 0x60] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47f923: mov dword ptr [edx + 4], ecx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 47f926: lea ecx, [esp + 0x2c] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47f92a: mov dword ptr [edx + 8], eax */
	m->esp -= 4; M32(m->esp) = 0x47f932u; lift_4802b0(m);	/* 47f92d: call 0x4802b0 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x58u));	/* 47f932: fsub dword ptr [ebx + 0x58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47f935: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f93b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f93d: test ah, 1 */
	if (m->zf) goto L_47f94b;	/* 47f940: je 0x47f94b */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 47f942: lea ecx, [esp + 0x28] */
	m->esp -= 4; M32(m->esp) = 0x47f94bu; lift_480230(m);	/* 47f946: call 0x480230 */
L_47f94b:
	m->eax = M32((DWORD)(m->esp + 0xb8u));	/* 47f94b: mov eax, dword ptr [esp + 0xb8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 47f952: test eax, eax */
	if (!m->zf) goto L_47fa48;	/* 47f954: jne 0x47fa48 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 47f95a: lea ecx, [esp + 0x28] */
	m->edx = (DWORD)(m->esp + 0x88u);	/* 47f95e: lea edx, [esp + 0x88] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f965: push ecx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 47f966: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f96a: push edx */
	m->ecx = (DWORD)(m->esp + 0x74u);	/* 47f96b: lea ecx, [esp + 0x74] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f96f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f970: push ecx */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 47f971: lea ecx, [esp + 0x48] */
	m->esp -= 4; M32(m->esp) = 0x47f97au; lift_480250(m);	/* 47f975: call 0x480250 */
	m->ecx = m->eax;	/* 47f97a: mov ecx, eax */
	m->esp -= 4; M32(m->esp) = 0x47f981u; lift_480250(m);	/* 47f97c: call 0x480250 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47f981: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 47f983: mov dword ptr [esp + 0x1c], edx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 47f987: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 47f98a: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47f98e: lea ecx, [esp + 0x1c] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 47f992: mov edx, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 47f995: mov dword ptr [esp + 0x24], edx */
	m->esp -= 4; M32(m->esp) = 0x47f99eu; lift_467760(m);	/* 47f999: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47f99e: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47f9a4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47f9a6: test ah, 1 */
	if (!m->zf) goto L_47fa23;	/* 47f9a9: jne 0x47fa23 */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 47f9ab: lea eax, [esp + 0x1c] */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 47f9af: lea ecx, [esp + 0x44] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9b3: push eax */
	m->esp -= 4; M32(m->esp) = 0x47f9b9u; lift_4802b0(m);	/* 47f9b4: call 0x4802b0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9b9: push ecx */
	m->ecx = (DWORD)(m->esp + 0x8cu);	/* 47f9ba: lea ecx, [esp + 0x8c] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47f9c1: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9c4: push ecx */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 47f9c5: lea ecx, [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x47f9ceu; lift_4803c0(m);	/* 47f9c9: call 0x4803c0 */
	m->edx = M32((DWORD)(m->esp + 0xa4u));	/* 47f9ce: mov edx, dword ptr [esp + 0xa4] */
	m->eax = (DWORD)(m->esp + 0x88u);	/* 47f9d5: lea eax, [esp + 0x88] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9dc: push edx */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 47f9dd: lea ecx, [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9e1: push eax */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 47f9e2: lea edx, [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9e6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9e7: push edx */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 47f9e8: lea ecx, [esp + 0x2c] */
	m->esp -= 4; M32(m->esp) = 0x47f9f1u; lift_480320(m);	/* 47f9ec: call 0x480320 */
	m->ecx = m->eax;	/* 47f9f1: mov ecx, eax */
	m->esp -= 4; M32(m->esp) = 0x47f9f8u; lift_480370(m);	/* 47f9f3: call 0x480370 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9f8: push eax */
	m->eax = (DWORD)(m->esp + 0x7cu);	/* 47f9f9: lea eax, [esp + 0x7c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47f9fd: push eax */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 47f9fe: lea ecx, [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x47fa07u; lift_4802d0(m);	/* 47fa02: call 0x4802d0 */
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47fa07: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47fa0e: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47fa10: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47fa12: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 47fa15: mov dword ptr [ecx + 4], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47fa18: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 47fa1b: mov dword ptr [ecx + 8], eax */
	goto L_47fb43;	/* 47fa1e: jmp 0x47fb43 */
L_47fa23:
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47fa23: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 47fa2a: mov edx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47fa30: mov dword ptr [ecx], edx */
	m->eax = M32((DWORD)(0xa0e7ecu));	/* 47fa32: mov eax, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47fa37: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 47fa3a: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47fa40: mov dword ptr [ecx + 8], edx */
	goto L_47fb43;	/* 47fa43: jmp 0x47fb43 */
L_47fa48:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47fa48: push eax */
	m->eax = (DWORD)(m->esp + 0x8cu);	/* 47fa49: lea eax, [esp + 0x8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47fa50: push eax */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 47fa51: lea ecx, [esp + 0x30] */
	m->esp -= 4; M32(m->esp) = 0x47fa5au; lift_480250(m);	/* 47fa55: call 0x480250 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47fa5a: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 47fa5c: mov dword ptr [esp + 0x1c], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47fa60: lea ecx, [esp + 0x1c] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 47fa64: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 47fa67: mov dword ptr [esp + 0x20], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47fa6b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 47fa6e: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x47fa77u; lift_467760(m);	/* 47fa72: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 47fa77: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47fa7d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47fa7f: test ah, 1 */
	if (!m->zf) goto L_47faf9;	/* 47fa82: jne 0x47faf9 */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 47fa84: lea ecx, [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47fa88: push ecx */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 47fa89: lea ecx, [esp + 0x48] */
	m->esp -= 4; M32(m->esp) = 0x47fa92u; lift_4802b0(m);	/* 47fa8d: call 0x4802b0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47fa92: push ecx */
	m->edx = (DWORD)(m->esp + 0x8cu);	/* 47fa93: lea edx, [esp + 0x8c] */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 47fa9a: lea ecx, [esp + 0x20] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47fa9e: fstp dword ptr [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47faa1: push edx */
	m->esp -= 4; M32(m->esp) = 0x47faa7u; lift_4803c0(m);	/* 47faa2: call 0x4803c0 */
	m->eax = M32((DWORD)(m->esp + 0xa4u));	/* 47faa7: mov eax, dword ptr [esp + 0xa4] */
	m->ecx = (DWORD)(m->esp + 0x88u);	/* 47faae: lea ecx, [esp + 0x88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47fab5: push eax */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 47fab6: lea edx, [esp + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47faba: push ecx */
	m->eax = (DWORD)(m->esp + 0x74u);	/* 47fabb: lea eax, [esp + 0x74] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47fabf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47fac0: push eax */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 47fac1: lea ecx, [esp + 0x2c] */
	m->esp -= 4; M32(m->esp) = 0x47facau; lift_480320(m);	/* 47fac5: call 0x480320 */
	m->ecx = m->eax;	/* 47faca: mov ecx, eax */
	m->esp -= 4; M32(m->esp) = 0x47fad1u; lift_480370(m);	/* 47facc: call 0x480370 */
	m->ecx = (DWORD)(m->esp + 0x78u);	/* 47fad1: lea ecx, [esp + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47fad5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47fad6: push ecx */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 47fad7: lea ecx, [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x47fae0u; lift_4802d0(m);	/* 47fadb: call 0x4802d0 */
	m->edx = M32((DWORD)(m->esp + 0xacu));	/* 47fae0: mov edx, dword ptr [esp + 0xac] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 47fae7: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 47fae9: mov dword ptr [edx], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 47faeb: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 47faee: mov dword ptr [edx + 4], ecx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 47faf1: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 47faf4: mov dword ptr [edx + 8], eax */
	goto L_47fb19;	/* 47faf7: jmp 0x47fb19 */
L_47faf9:
	m->ecx = M32((DWORD)(m->esp + 0xacu));	/* 47faf9: mov ecx, dword ptr [esp + 0xac] */
	m->edx = M32((DWORD)(0xa0e7e8u));	/* 47fb00: mov edx, dword ptr [0xa0e7e8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 47fb06: mov dword ptr [ecx], edx */
	m->eax = M32((DWORD)(0xa0e7ecu));	/* 47fb08: mov eax, dword ptr [0xa0e7ec] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 47fb0d: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 47fb10: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 47fb16: mov dword ptr [ecx + 8], edx */
L_47fb19:
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 47fb19: lea eax, [esp + 0x1c] */
	m->ecx = (DWORD)(m->esp + 0x88u);	/* 47fb1d: lea ecx, [esp + 0x88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47fb24: push eax */
L_47fb25:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47fb25: push ecx */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 47fb26: lea ecx, [esp + 0x30] */
	m->esp -= 4; M32(m->esp) = 0x47fb2fu; lift_480250(m);	/* 47fb2a: call 0x480250 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 47fb2f: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 47fb31: mov dword ptr [esp + 0x28], edx */
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 47fb35: mov ecx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x2cu)) = m->ecx;	/* 47fb38: mov dword ptr [esp + 0x2c], ecx */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 47fb3c: mov edx, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 47fb3f: mov dword ptr [esp + 0x30], edx */
L_47fb43:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47fb43: push esi */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 47fb44: lea ecx, [esp + 0x2c] */
	m->esp -= 4; M32(m->esp) = 0x47fb4du; lift_4802b0(m);	/* 47fb48: call 0x4802b0 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 47fb4d: mov eax, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 47fb51: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47fb55: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 47fb56: mov ecx, dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47fb5a: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47fb5d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47fb5e: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0xc0u));	/* 47fb5f: mov ecx, dword ptr [esp + 0xc0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47fb66: push edx */
	m->esp -= 4; M32(m->esp) = 0x47fb6cu; lift_4809d0(m);	/* 47fb67: call 0x4809d0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 47fb6c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 47fb6d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 47fb6e: pop ebp */
	m->eax = 0x1u;	/* 47fb6f: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 47fb74: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47fb75: add esp, 0x84 */
	m->esp += 4 + 36; return;	/* 47fb7b: ret 0x24 */
}

/* Vec3_set (0x4722c0), lifted by tools/lift.py */
static void lift_4722c0(X86 *m)
{
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 4722c0: mov edx, dword ptr [esp + 8] */
	m->eax = m->ecx;	/* 4722c4: mov eax, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 4722c6: mov ecx, dword ptr [esp + 4] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 4722ca: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 4722cc: mov ecx, dword ptr [esp + 0xc] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4722d0: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 4722d3: mov dword ptr [eax + 8], ecx */
	m->esp += 4 + 12; return;	/* 4722d6: ret 0xc */
}

/* Vec3_normalize (0x467760), lifted by tools/lift.py */
static void lift_467760(X86 *m)
{
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 467760: fld dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 467763: fld dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 467766: fld dword ptr [ecx] */
	{ long double t = ST(0); FPUSH(t); }	/* 467768: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 46776a: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 46776c: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 46776e: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 467770: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 467772: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 467774: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 467776: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 467778: fsqrt  */
	ST(3) = ST(0); FPOP();	/* 46777a: fstp st(3) */
	ST(0) = ST(0); FPOP();	/* 46777c: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 46777e: fstp st(0) */
	{ long double t = ST(0); FPUSH(t); }	/* 467780: fld st(0) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa268u)); FPOP();	/* 467782: fcomp dword ptr [0x4aa268] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 467788: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46778a: test ah, 1 */
	if (m->zf) goto L_46779e;	/* 46778d: je 0x46779e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46778f: xor eax, eax */
	M32((DWORD)(m->ecx + 0x0u)) = 0x3f800000u;	/* 467791: mov dword ptr [ecx], 0x3f800000 */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 467797: mov dword ptr [ecx + 8], eax */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 46779a: mov dword ptr [ecx + 4], eax */
	m->esp += 4 + 0; return;	/* 46779d: ret  */
L_46779e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 46779e: fld dword ptr [ecx] */
	ST(0) = ST(0) / ST(1);	/* 4677a0: fdiv st(1) */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 4677a2: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 4677a4: fld dword ptr [ecx + 4] */
	ST(0) = ST(0) / ST(1);	/* 4677a7: fdiv st(1) */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 4677a9: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 4677ac: fld dword ptr [ecx + 8] */
	ST(0) = ST(0) / ST(1);	/* 4677af: fdiv st(1) */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 4677b1: fstp dword ptr [ecx + 8] */
	m->esp += 4 + 0; return;	/* 4677b4: ret  */
}

/* this_set_480210 (0x480210), lifted by tools/lift.py */
static void lift_480210(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 480210: mov eax, dword ptr [esp + 4] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 480214: mov edx, dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 480218: mov dword ptr [ecx], eax */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 48021a: mov eax, dword ptr [esp + 0xc] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 48021e: mov dword ptr [ecx + 4], edx */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 480221: mov dword ptr [ecx + 8], eax */
	m->esp += 4 + 12; return;	/* 480224: ret 0xc */
}

/* collision_480230 (0x480230), lifted by tools/lift.py */
static void lift_480230(X86 *m)
{
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 480230: fld dword ptr [ecx] */
	ST(0) = -ST(0);	/* 480232: fchs  */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 480234: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 480236: fld dword ptr [ecx + 4] */
	ST(0) = -ST(0);	/* 480239: fchs  */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 48023b: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 48023e: fld dword ptr [ecx + 8] */
	ST(0) = -ST(0);	/* 480241: fchs  */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 480243: fstp dword ptr [ecx + 8] */
	m->esp += 4 + 0; return;	/* 480246: ret  */
}

/* Vec3_cross (0x480250), lifted by tools/lift.py */
static void lift_480250(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 480250: sub esp, 0xc */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 480253: mov eax, dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 480257: fld dword ptr [ecx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 48025a: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 48025d: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 480260: fmul dword ptr [ecx + 8] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 480263: fsubp st(1) */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 480265: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 480269: fld dword ptr [ecx + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 48026c: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 48026e: fld dword ptr [ecx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 480270: fmul dword ptr [eax + 8] */
	m->edx = M32((DWORD)(m->esp + 0x0u));	/* 480273: mov edx, dword ptr [esp] */
	ST(1) = ST(1) - ST(0); FPOP();	/* 480277: fsubp st(1) */
	MF((DWORD)(m->esp + 0x4u)) = (float)ST(0); FPOP();	/* 480279: fstp dword ptr [esp + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 48027d: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 480280: fmul dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 480282: fld dword ptr [ecx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 480285: fmul dword ptr [eax] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 480287: mov eax, dword ptr [esp + 0x10] */
	m->ecx = m->eax;	/* 48028b: mov ecx, eax */
	ST(1) = ST(1) - ST(0); FPOP();	/* 48028d: fsubp st(1) */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 48028f: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 480291: mov edx, dword ptr [esp + 4] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 480295: fstp dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 480299: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 48029c: mov edx, dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 4802a0: mov dword ptr [ecx + 8], edx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4802a3: add esp, 0xc */
	m->esp += 4 + 8; return;	/* 4802a6: ret 8 */
}

/* Vec3_dot (0x4802b0), lifted by tools/lift.py */
static void lift_4802b0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4802b0: mov eax, dword ptr [esp + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4802b4: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 4802b7: fmul dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4802ba: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 4802bd: fmul dword ptr [ecx + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4802c0: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4802c2: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 4802c4: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4802c6: faddp st(1) */
	m->esp += 4 + 4; return;	/* 4802c8: ret 4 */
}

/* Vec3_add (0x4802d0), lifted by tools/lift.py */
static void lift_4802d0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4802d0: sub esp, 0xc */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4802d3: mov eax, dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4802d7: fld dword ptr [eax] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 4802d9: fadd dword ptr [ecx] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4802db: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4802df: fld dword ptr [eax + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 4802e2: fadd dword ptr [ecx + 4] */
	m->edx = M32((DWORD)(m->esp + 0x0u));	/* 4802e5: mov edx, dword ptr [esp] */
	MF((DWORD)(m->esp + 0x4u)) = (float)ST(0); FPOP();	/* 4802e9: fstp dword ptr [esp + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4802ed: fld dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4802f0: mov eax, dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 4802f4: fadd dword ptr [ecx + 8] */
	m->ecx = m->eax;	/* 4802f7: mov ecx, eax */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 4802f9: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 4802fb: mov edx, dword ptr [esp + 4] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 4802ff: fstp dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 480303: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 480306: mov edx, dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 48030a: mov dword ptr [ecx + 8], edx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48030d: add esp, 0xc */
	m->esp += 4 + 8; return;	/* 480310: ret 8 */
}

/* Vec3_sub (0x480320), lifted by tools/lift.py */
static void lift_480320(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 480320: sub esp, 0xc */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 480323: mov eax, dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 480327: fld dword ptr [ecx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 480329: fsub dword ptr [eax] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48032b: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 48032f: fld dword ptr [ecx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 480332: fsub dword ptr [eax + 4] */
	m->edx = M32((DWORD)(m->esp + 0x0u));	/* 480335: mov edx, dword ptr [esp] */
	MF((DWORD)(m->esp + 0x4u)) = (float)ST(0); FPOP();	/* 480339: fstp dword ptr [esp + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 48033d: fld dword ptr [ecx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 480340: fsub dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 480343: mov eax, dword ptr [esp + 0x10] */
	m->ecx = m->eax;	/* 480347: mov ecx, eax */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 480349: fstp dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 48034d: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 48034f: mov edx, dword ptr [esp + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 480353: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 480356: mov edx, dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 48035a: mov dword ptr [ecx + 8], edx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48035d: add esp, 0xc */
	m->esp += 4 + 8; return;	/* 480360: ret 8 */
}

/* Vec3_scale (0x480370), lifted by tools/lift.py */
static void lift_480370(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 480370: sub esp, 0xc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 480373: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 480377: fmul dword ptr [ecx] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 480379: mov eax, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48037d: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 480381: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 480385: fmul dword ptr [ecx + 4] */
	m->edx = M32((DWORD)(m->esp + 0x0u));	/* 480388: mov edx, dword ptr [esp] */
	MF((DWORD)(m->esp + 0x4u)) = (float)ST(0); FPOP();	/* 48038c: fstp dword ptr [esp + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 480390: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 480394: fmul dword ptr [ecx + 8] */
	m->ecx = m->eax;	/* 480397: mov ecx, eax */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 480399: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 48039b: mov edx, dword ptr [esp + 4] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 48039f: fstp dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 4803a3: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 4803a6: mov edx, dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 4803aa: mov dword ptr [ecx + 8], edx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4803ad: add esp, 0xc */
	m->esp += 4 + 8; return;	/* 4803b0: ret 8 */
}

/* collision_4803c0 (0x4803c0), lifted by tools/lift.py */
static void lift_4803c0(X86 *m)
{
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 4803c0: fld dword ptr [esp + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 4803c4: fmul dword ptr [ecx] */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4803c6: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4803ca: push esi */
	m->edx = m->eax;	/* 4803cb: mov edx, eax */
	MF((DWORD)(m->ecx + 0x0u)) = (float)ST(0); FPOP();	/* 4803cd: fstp dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 4803cf: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 4803d3: fmul dword ptr [ecx + 4] */
	MF((DWORD)(m->ecx + 0x4u)) = (float)ST(0); FPOP();	/* 4803d6: fstp dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 4803d9: fld dword ptr [esp + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 4803dd: fmul dword ptr [ecx + 8] */
	MF((DWORD)(m->ecx + 0x8u)) = (float)ST(0); FPOP();	/* 4803e0: fstp dword ptr [ecx + 8] */
	m->esi = M32((DWORD)(m->ecx + 0x0u));	/* 4803e3: mov esi, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->esi;	/* 4803e5: mov dword ptr [edx], esi */
	m->esi = M32((DWORD)(m->ecx + 0x4u));	/* 4803e7: mov esi, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->esi;	/* 4803ea: mov dword ptr [edx + 4], esi */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 4803ed: mov ecx, dword ptr [ecx + 8] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4803f0: pop esi */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 4803f1: mov dword ptr [edx + 8], ecx */
	m->esp += 4 + 8; return;	/* 4803f4: ret 8 */
}

/* SQRT_wrap_480400 (0x480400), lifted by tools/lift.py */
static void lift_480400(X86 *m)
{
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x8u)));	/* 480400: fld dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x4u)));	/* 480403: fld dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 480406: fld dword ptr [ecx] */
	{ long double t = ST(0); FPUSH(t); }	/* 480408: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 48040a: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 48040c: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 48040e: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480410: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 480412: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 480414: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 480416: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 480418: fsqrt  */
	ST(3) = ST(0); FPOP();	/* 48041a: fstp st(3) */
	ST(0) = ST(0); FPOP();	/* 48041c: fstp st(0) */
	ST(0) = ST(0); FPOP();	/* 48041e: fstp st(0) */
	m->esp += 4 + 0; return;	/* 480420: ret  */
}

/* Vec4_set (0x4809d0), lifted by tools/lift.py */
static void lift_4809d0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4809d0: mov eax, dword ptr [esp + 4] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 4809d4: mov edx, dword ptr [esp + 8] */
	M32((DWORD)(m->ecx + 0x0u)) = m->eax;	/* 4809d8: mov dword ptr [ecx], eax */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 4809da: mov eax, dword ptr [esp + 0xc] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 4809de: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 4809e1: mov edx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 4809e5: mov dword ptr [ecx + 8], eax */
	M32((DWORD)(m->ecx + 0xcu)) = m->edx;	/* 4809e8: mov dword ptr [ecx + 0xc], edx */
	m->esp += 4 + 16; return;	/* 4809eb: ret 0x10 */
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
