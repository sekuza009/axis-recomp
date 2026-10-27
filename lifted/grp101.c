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

static void lift_495610(X86 *m);

/* hud_drawEscMenu (0x495610), lifted by tools/lift.py */
static void lift_495610(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495610: sub esp, 0x104 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495616: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 495617: push esi */
	m->esi = m->ecx;	/* 495618: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49561a: push edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340c9cu)));	/* 49561b: fld dword ptr [esi + 0x2340c9c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a941cu)); FPOP();	/* 495621: fcomp dword ptr [0x4a941c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 495627: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 495629: test ah, 1 */
	if (m->zf) goto L_49564c;	/* 49562c: je 0x49564c */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a941cu)));	/* 49562e: fld dword ptr [0x4a941c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x2340c9cu));	/* 495634: fsub dword ptr [esi + 0x2340c9c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 49563a: fmul dword ptr [0x4a947c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 495640: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 495646: fstp dword ptr [esp + 0xc] */
	goto L_495654;	/* 49564a: jmp 0x495654 */
L_49564c:
	M32((DWORD)(m->esp + 0xcu)) = 0x3f800000u;	/* 49564c: mov dword ptr [esp + 0xc], 0x3f800000 */
L_495654:
	m->eax = M32((DWORD)(m->esi + 0x2340cf8u));	/* 495654: mov eax, dword ptr [esi + 0x2340cf8] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49565a: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_495eb0;	/* 49565d: ja 0x495eb0 */
	switch (m->eax) { case 0: goto L_49566a; case 1: goto L_495a4c; case 2: goto L_495b98; case 3: goto L_495ca5; case 4: goto L_495d4c; default: abort(); }	/* 495663: jmp dword ptr [eax*4 + 0x495ebc] */
L_49566a:
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 49566a: mov eax, dword ptr [esi + 8] */
	m->edi = 0xc8u;	/* 49566d: mov edi, 0xc8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495672: test eax, eax */
	if (!m->zf) goto L_495680;	/* 495674: jne 0x495680 */
	m->ecx = M32((DWORD)(m->esi + 0x234243eu));	/* 495676: mov ecx, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49567c: test ecx, ecx */
	if (m->sf == m->of) goto L_495685;	/* 49567e: jge 0x495685 */
L_495680:
	m->edi = 0xb4u;	/* 495680: mov edi, 0xb4 */
L_495685:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495685: cmp eax, 1 */
	if (!m->zf) goto L_4956a7;	/* 495688: jne 0x4956a7 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49568a: cmp dword ptr [esi + 0x22e7184], eax */
	if (!m->zf) goto L_49569f;	/* 495690: jne 0x49569f */
	m->ecx = M32((DWORD)(m->esi + 0x234243eu));	/* 495692: mov ecx, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495698: test ecx, ecx */
	if (m->sf != m->of) goto L_49569f;	/* 49569a: jl 0x49569f */
	{ DWORD a_ = m->edi, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49569c: sub edi, 0x14 */
L_49569f:
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49569f: cmp eax, 1 */
	if (!m->zf) goto L_4956a7;	/* 4956a2: jne 0x4956a7 */
	{ DWORD a_ = m->edi, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4956a4: sub edi, 0x14 */
L_4956a7:
	m->ebx = M32((DWORD)(m->esp + 0xcu));	/* 4956a7: mov ebx, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4956ab: push ebp */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 4956ac: mov ebp, dword ptr [0x4a9228] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4956b2: push ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956b3: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956b8: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956bd: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x4956c4u; native_call(m, m->ebp);	/* 4956c2: call ebp */
	m->eax = (DWORD)(m->edi + 0x10u);	/* 4956c4: lea eax, [edi + 0x10] */
	m->ecx = m->esi;	/* 4956c7: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4956c9: push eax */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956ca: push 0x1a0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4956cf: push edi */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956d0: push 0xe0 */
	m->esp -= 4; M32(m->esp) = 0x4956dau; native_call(m, 0x495ed0u);	/* 4956d5: call 0x495ed0 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 4956da: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4d04b8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956de: push 0x4d04b8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4956e3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4956e9u; native_call(m, 0x49e9ddu);	/* 4956e4: call 0x49e9dd */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4956e9: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956ea: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956ef: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4956f4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4956feu; native_call(m, 0x44ad30u);	/* 4956f9: call 0x44ad30 */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 4956fe: lea edx, [esp + 0x2c] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495702: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495704: push edx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495705: push 0x140 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49570a: push edi */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 49570b: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495715u; native_call(m, 0x44ae10u);	/* 495710: call 0x44ae10 */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 495715: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495718: add esp, 0x2c */
	{ DWORD a_ = m->edi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49571b: add edi, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49571e: test eax, eax */
	if (!m->zf) goto L_495730;	/* 495720: jne 0x495730 */
	m->eax = M32((DWORD)(m->esi + 0x234243eu));	/* 495722: mov eax, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495728: test eax, eax */
	if (m->sf == m->of) goto L_4957de;	/* 49572a: jge 0x4957de */
L_495730:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495730: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495731: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495736: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49573b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495742u; native_call(m, m->ebp);	/* 495740: call ebp */
	m->eax = (DWORD)(m->edi + 0x10u);	/* 495742: lea eax, [edi + 0x10] */
	m->ecx = m->esi;	/* 495745: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495747: push eax */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495748: push 0x1a0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49574d: push edi */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49574e: push 0xe0 */
	m->esp -= 4; M32(m->esp) = 0x495758u; native_call(m, 0x495ed0u);	/* 495753: call 0x495ed0 */
	m->eax = M32((DWORD)(m->esi + 0x234243eu));	/* 495758: mov eax, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49575e: test eax, eax */
	if (m->sf == m->of) goto L_495781;	/* 495760: jge 0x495781 */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 495762: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495765: test eax, eax */
	if (!m->zf) goto L_495775;	/* 495767: jne 0x495775 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 495769: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4d04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49576d: push 0x4d04b0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495772: push ecx */
	goto L_49578b;	/* 495773: jmp 0x49578b */
L_495775:
	m->edx = (DWORD)(m->esp + 0x14u);	/* 495775: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x4d04a8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495779: push 0x4d04a8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49577e: push edx */
	goto L_49578b;	/* 49577f: jmp 0x49578b */
L_495781:
	m->eax = (DWORD)(m->esp + 0x14u);	/* 495781: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0x4d049cu; m->esp -= 4; M32(m->esp) = v_; }	/* 495785: push 0x4d049c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49578a: push eax */
L_49578b:
	m->esp -= 4; M32(m->esp) = 0x495790u; native_call(m, 0x49e9ddu);	/* 49578b: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 495790: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495796: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495799: test eax, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49579b: push ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49579c: push 0x3f000000 */
	if (!m->zf) goto L_4957af;	/* 4957a1: jne 0x4957af */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4957a3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4957a8: push 0x3f800000 */
	goto L_4957b9;	/* 4957ad: jmp 0x4957b9 */
L_4957af:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4957af: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4957b4: push 0x3f000000 */
L_4957b9:
	m->esp -= 4; M32(m->esp) = 0x4957beu; native_call(m, 0x44ad30u);	/* 4957b9: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4957be: add esp, 0x10 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 4957c1: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4957c5: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4957c7: push ecx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 4957c8: push 0x140 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4957cd: push edi */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 4957ce: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x4957d8u; native_call(m, 0x44ae10u);	/* 4957d3: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4957d8: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4957db: add edi, 0x28 */
L_4957de:
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 4957de: mov ecx, dword ptr [esi + 8] */
	m->eax = 0x1u;	/* 4957e1: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4957e6: cmp ecx, eax */
	if (!m->zf) goto L_495938;	/* 4957e8: jne 0x495938 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4957ee: cmp dword ptr [esi + 0x22e7184], eax */
	if (!m->zf) goto L_495893;	/* 4957f4: jne 0x495893 */
	m->ecx = M32((DWORD)(m->esi + 0x234243eu));	/* 4957fa: mov ecx, dword ptr [esi + 0x234243e] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495800: test ecx, ecx */
	if (m->sf != m->of) goto L_495893;	/* 495802: jl 0x495893 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495808: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495809: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49580e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495813: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x49581au; native_call(m, m->ebp);	/* 495818: call ebp */
	m->edx = (DWORD)(m->edi + 0x10u);	/* 49581a: lea edx, [edi + 0x10] */
	m->ecx = m->esi;	/* 49581d: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49581f: push edx */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495820: push 0x1a0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495825: push edi */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495826: push 0xe0 */
	m->esp -= 4; M32(m->esp) = 0x495830u; native_call(m, 0x495ed0u);	/* 49582b: call 0x495ed0 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 495830: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0x4d0494u; m->esp -= 4; M32(m->esp) = v_; }	/* 495834: push 0x4d0494 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495839: push eax */
	m->esp -= 4; M32(m->esp) = 0x49583fu; native_call(m, 0x49e9ddu);	/* 49583a: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 49583f: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495845: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495848: cmp eax, 1 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49584b: push ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49584c: push 0x3f000000 */
	if (!m->zf) goto L_49585f;	/* 495851: jne 0x49585f */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495853: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495858: push 0x3f800000 */
	goto L_495869;	/* 49585d: jmp 0x495869 */
L_49585f:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49585f: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495864: push 0x3f000000 */
L_495869:
	m->esp -= 4; M32(m->esp) = 0x49586eu; native_call(m, 0x44ad30u);	/* 495869: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49586e: add esp, 0x10 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 495871: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495875: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495877: push ecx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495878: push 0x140 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49587d: push edi */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 49587e: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495888u; native_call(m, 0x44ae10u);	/* 495883: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495888: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49588b: add edi, 0x28 */
	m->eax = 0x1u;	/* 49588e: mov eax, 1 */
L_495893:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x8u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495893: cmp dword ptr [esi + 8], eax */
	if (!m->zf) goto L_495938;	/* 495896: jne 0x495938 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49589c: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49589d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4958a2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4958a7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4958aeu; native_call(m, m->ebp);	/* 4958ac: call ebp */
	m->edx = (DWORD)(m->edi + 0x10u);	/* 4958ae: lea edx, [edi + 0x10] */
	m->ecx = m->esi;	/* 4958b1: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4958b3: push edx */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4958b4: push 0x1a0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4958b9: push edi */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4958ba: push 0xe0 */
	m->esp -= 4; M32(m->esp) = 0x4958c4u; native_call(m, 0x495ed0u);	/* 4958bf: call 0x495ed0 */
	m->eax = M32((DWORD)(m->esi + 0x2340d1du));	/* 4958c4: mov eax, dword ptr [esi + 0x2340d1d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4958ca: test eax, eax */
	if (!m->zf) goto L_4958da;	/* 4958cc: jne 0x4958da */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 4958ce: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0x4d048cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4958d2: push 0x4d048c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4958d7: push eax */
	goto L_4958e4;	/* 4958d8: jmp 0x4958e4 */
L_4958da:
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 4958da: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4d047cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4958de: push 0x4d047c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4958e3: push ecx */
L_4958e4:
	m->esp -= 4; M32(m->esp) = 0x4958e9u; native_call(m, 0x49e9ddu);	/* 4958e4: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 4958e9: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4958ef: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4958f2: cmp eax, 2 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4958f5: push ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4958f6: push 0x3f000000 */
	if (!m->zf) goto L_495909;	/* 4958fb: jne 0x495909 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4958fd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495902: push 0x3f800000 */
	goto L_495913;	/* 495907: jmp 0x495913 */
L_495909:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495909: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49590e: push 0x3f000000 */
L_495913:
	m->esp -= 4; M32(m->esp) = 0x495918u; native_call(m, 0x44ad30u);	/* 495913: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495918: add esp, 0x10 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 49591b: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 49591f: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495921: push edx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495922: push 0x140 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495927: push edi */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495928: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495932u; native_call(m, 0x44ae10u);	/* 49592d: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495932: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 495935: add edi, 0x28 */
L_495938:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495938: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495939: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49593e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495943: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x49594au; native_call(m, m->ebp);	/* 495948: call ebp */
	m->eax = (DWORD)(m->edi + 0x10u);	/* 49594a: lea eax, [edi + 0x10] */
	m->ecx = m->esi;	/* 49594d: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49594f: push eax */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495950: push 0x1a0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495955: push edi */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495956: push 0xe0 */
	m->esp -= 4; M32(m->esp) = 0x495960u; native_call(m, 0x495ed0u);	/* 49595b: call 0x495ed0 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 495960: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4b107cu; m->esp -= 4; M32(m->esp) = v_; }	/* 495964: push 0x4b107c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495969: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49596fu; native_call(m, 0x49e9ddu);	/* 49596a: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 49596f: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495975: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495978: cmp eax, 3 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49597b: push ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49597c: push 0x3f000000 */
	if (!m->zf) goto L_49598f;	/* 495981: jne 0x49598f */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495983: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495988: push 0x3f800000 */
	goto L_495999;	/* 49598d: jmp 0x495999 */
L_49598f:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49598f: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495994: push 0x3f000000 */
L_495999:
	m->esp -= 4; M32(m->esp) = 0x49599eu; native_call(m, 0x44ad30u);	/* 495999: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49599e: add esp, 0x10 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 4959a1: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959a5: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4959a7: push edx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959a8: push 0x140 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4959ad: push edi */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959ae: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x4959b8u; native_call(m, 0x44ae10u);	/* 4959b3: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4959b8: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4959bb: add edi, 0x28 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4959be: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959bf: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959c4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959c9: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4959d0u; native_call(m, m->ebp);	/* 4959ce: call ebp */
	m->eax = (DWORD)(m->edi + 0x10u);	/* 4959d0: lea eax, [edi + 0x10] */
	m->ecx = m->esi;	/* 4959d3: mov ecx, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4959d5: push eax */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959d6: push 0x1a0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4959db: push edi */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959dc: push 0xe0 */
	m->esp -= 4; M32(m->esp) = 0x4959e6u; native_call(m, 0x495ed0u);	/* 4959e1: call 0x495ed0 */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 4959e6: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4d0474u; m->esp -= 4; M32(m->esp) = v_; }	/* 4959ea: push 0x4d0474 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4959ef: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4959f5u; native_call(m, 0x49e9ddu);	/* 4959f0: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 4959f5: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4959fb: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4959fe: cmp eax, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 495a01: pop ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495a02: push ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a03: push 0x3f000000 */
	if (!m->zf) goto L_495a16;	/* 495a08: jne 0x495a16 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a0a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a0f: push 0x3f800000 */
	goto L_495a20;	/* 495a14: jmp 0x495a20 */
L_495a16:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a16: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a1b: push 0x3f000000 */
L_495a20:
	m->esp -= 4; M32(m->esp) = 0x495a25u; native_call(m, 0x44ad30u);	/* 495a20: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495a25: add esp, 0x10 */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 495a28: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a2c: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495a2e: push edx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a2f: push 0x140 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495a34: push edi */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a35: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495a3fu; native_call(m, 0x44ae10u);	/* 495a3a: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495a3f: add esp, 0x14 */
	m->edi = M32(m->esp); m->esp += 4;	/* 495a42: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 495a43: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 495a44: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495a45: add esp, 0x104 */
	m->esp += 4 + 0; return;	/* 495a4b: ret  */
L_495a4c:
	m->edi = M32((DWORD)(m->esp + 0xcu));	/* 495a4c: mov edi, dword ptr [esp + 0xc] */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 495a50: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495a56: push edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a57: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a5c: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a61: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x495a68u; native_call(m, m->ebx);	/* 495a66: call ebx */
	{ DWORD v_ = 0xd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a68: push 0xd8 */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a6d: push 0x1a0 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a72: push 0xc8 */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a77: push 0xe0 */
	m->ecx = m->esi;	/* 495a7c: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x495a83u; native_call(m, 0x495ed0u);	/* 495a7e: call 0x495ed0 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 495a83: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x4d0494u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a87: push 0x4d0494 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495a8c: push eax */
	m->esp -= 4; M32(m->esp) = 0x495a92u; native_call(m, 0x49e9ddu);	/* 495a8d: call 0x49e9dd */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495a92: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a93: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a98: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495a9d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495aa7u; native_call(m, 0x44ad30u);	/* 495aa2: call 0x44ad30 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 495aa7: lea ecx, [esp + 0x28] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495aab: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495aad: push ecx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495aae: push 0x140 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ab3: push 0xc8 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ab8: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495ac2u; native_call(m, 0x44ae10u);	/* 495abd: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495ac2: add esp, 0x2c */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495ac5: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ac6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495acb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ad0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495ad7u; native_call(m, m->ebx);	/* 495ad5: call ebx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ad7: push 0x100 */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495adc: push 0x1a0 */
	{ DWORD v_ = 0xf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ae1: push 0xf0 */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ae6: push 0xe0 */
	m->ecx = m->esi;	/* 495aeb: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x495af2u; native_call(m, 0x495ed0u);	/* 495aed: call 0x495ed0 */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 495af2: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x4b21b8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495af6: push 0x4b21b8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495afb: push edx */
	m->esp -= 4; M32(m->esp) = 0x495b01u; native_call(m, 0x49e9ddu);	/* 495afc: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 495b01: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495b07: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495b0a: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495b0c: push edi */
	if (!m->zf) goto L_495b1a;	/* 495b0d: jne 0x495b1a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b0f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b11: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b13: push 0x3f800000 */
	goto L_495b29;	/* 495b18: jmp 0x495b29 */
L_495b1a:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b1a: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b1f: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b24: push 0x3f000000 */
L_495b29:
	m->esp -= 4; M32(m->esp) = 0x495b2eu; native_call(m, 0x44ad30u);	/* 495b29: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495b2e: add esp, 0x10 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 495b31: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b35: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495b37: push eax */
	{ DWORD v_ = 0x110u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b38: push 0x110 */
	{ DWORD v_ = 0xf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b3d: push 0xf0 */
	{ DWORD v_ = 0x110u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b42: push 0x110 */
	m->esp -= 4; M32(m->esp) = 0x495b4cu; native_call(m, 0x44ae10u);	/* 495b47: call 0x44ae10 */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 495b4c: lea ecx, [esp + 0x24] */
	{ DWORD v_ = 0x4b21b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b50: push 0x4b21b0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495b55: push ecx */
	m->esp -= 4; M32(m->esp) = 0x495b5bu; native_call(m, 0x49e9ddu);	/* 495b56: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 495b5b: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495b61: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495b64: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495b67: push edi */
	if (!m->zf) goto L_495b75;	/* 495b68: jne 0x495b75 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b6a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b6f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b71: push 0 */
	goto L_495b84;	/* 495b73: jmp 0x495b84 */
L_495b75:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b75: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b7a: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b7f: push 0x3f000000 */
L_495b84:
	m->esp -= 4; M32(m->esp) = 0x495b89u; native_call(m, 0x44ad30u);	/* 495b84: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495b89: add esp, 0x10 */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 495b8c: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b90: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495b92: push edx */
	goto L_495e99;	/* 495b93: jmp 0x495e99 */
L_495b98:
	m->edi = M32((DWORD)(0x4a9228u));	/* 495b98: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495b9e: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ba3: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ba8: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495bad: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x495bb4u; native_call(m, m->edi);	/* 495bb2: call edi */
	{ DWORD v_ = 0xecu; m->esp -= 4; M32(m->esp) = v_; }	/* 495bb4: push 0xec */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495bb9: push 0x1a0 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 495bbe: push 0xdc */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495bc3: push 0xe0 */
	m->ecx = m->esi;	/* 495bc8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x495bcfu; native_call(m, 0x495ed0u);	/* 495bca: call 0x495ed0 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 495bcf: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x4d0464u; m->esp -= 4; M32(m->esp) = v_; }	/* 495bd3: push 0x4d0464 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495bd8: push eax */
	m->esp -= 4; M32(m->esp) = 0x495bdeu; native_call(m, 0x49e9ddu);	/* 495bd9: call 0x49e9dd */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 495bde: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495be2: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495be3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495be8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495bed: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495bf7u; native_call(m, 0x44ad30u);	/* 495bf2: call 0x44ad30 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 495bf7: lea ecx, [esp + 0x28] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495bfb: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495bfd: push ecx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495bfe: push 0x140 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 495c03: push 0xdc */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c08: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495c12u; native_call(m, 0x44ae10u);	/* 495c0d: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495c12: add esp, 0x2c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495c15: push ebx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c16: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c1b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c20: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495c27u; native_call(m, m->edi);	/* 495c25: call edi */
	{ DWORD v_ = 0x114u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c27: push 0x114 */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c2c: push 0x1a0 */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c31: push 0x104 */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c36: push 0xe0 */
	m->ecx = m->esi;	/* 495c3b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x495c42u; native_call(m, 0x495ed0u);	/* 495c3d: call 0x495ed0 */
	m->edi = 0x9dc92cu;	/* 495c42: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 495c47: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 495c4a: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 495c4c: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 495c50: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 495c52: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 495c54: sub edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 495c56: push ebx */
	m->eax = m->ecx;	/* 495c57: mov eax, ecx */
	m->esi = m->edi;	/* 495c59: mov esi, edi */
	m->edi = m->edx;	/* 495c5b: mov edi, edx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c5d: push 0x3f800000 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 495c62: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 495c65: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 495c67: mov ecx, eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c69: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 495c6e: and ecx, 3 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c71: push 0x3f800000 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 495c76: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x495c7du; native_call(m, 0x44ad30u);	/* 495c78: call 0x44ad30 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 495c7d: lea ecx, [esp + 0x20] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c81: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495c83: push ecx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c84: push 0x140 */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c89: push 0x104 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495c8e: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495c98u; native_call(m, 0x44ae10u);	/* 495c93: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495c98: add esp, 0x24 */
	m->edi = M32(m->esp); m->esp += 4;	/* 495c9b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 495c9c: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 495c9d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495c9e: add esp, 0x104 */
	m->esp += 4 + 0; return;	/* 495ca4: ret  */
L_495ca5:
	m->ebx = M32((DWORD)(0x4a9228u));	/* 495ca5: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495cab: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495cb0: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495cb5: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495cba: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x495cc1u; native_call(m, m->ebx);	/* 495cbf: call ebx */
	{ DWORD v_ = 0xd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495cc1: push 0xd8 */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495cc6: push 0x1a0 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ccb: push 0xc8 */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495cd0: push 0xe0 */
	m->ecx = m->esi;	/* 495cd5: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x495cdcu; native_call(m, 0x495ed0u);	/* 495cd7: call 0x495ed0 */
	m->eax = M32((DWORD)(m->esi + 0x23423a9u));	/* 495cdc: mov eax, dword ptr [esi + 0x23423a9] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495ce2: test eax, eax */
	if (!m->zf) goto L_495d01;	/* 495ce4: jne 0x495d01 */
	m->edx = M32((DWORD)(0x9dad94u));	/* 495ce6: mov edx, dword ptr [0x9dad94] */
	m->eax = M32((DWORD)(0x9f181cu));	/* 495cec: mov eax, dword ptr [0x9f181c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495cf1: cmp edx, eax */
	if (!m->zf) goto L_495d01;	/* 495cf3: jne 0x495d01 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 495cf5: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x4d044cu; m->esp -= 4; M32(m->esp) = v_; }	/* 495cf9: push 0x4d044c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495cfe: push eax */
	goto L_495d0b;	/* 495cff: jmp 0x495d0b */
L_495d01:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 495d01: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x4d0444u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d05: push 0x4d0444 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495d0a: push ecx */
L_495d0b:
	m->esp -= 4; M32(m->esp) = 0x495d10u; native_call(m, 0x49e9ddu);	/* 495d0b: call 0x49e9dd */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 495d10: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495d14: add esp, 8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495d17: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d18: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d1d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d22: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495d2cu; native_call(m, 0x44ad30u);	/* 495d27: call 0x44ad30 */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 495d2c: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d30: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495d32: push edx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d33: push 0x140 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d38: push 0xc8 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d3d: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495d47u; native_call(m, 0x44ae10u);	/* 495d42: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495d47: add esp, 0x24 */
	goto L_495dc9;	/* 495d4a: jmp 0x495dc9 */
L_495d4c:
	m->ebx = M32((DWORD)(0x4a9228u));	/* 495d4c: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d52: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d57: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d5c: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d61: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x495d68u; native_call(m, m->ebx);	/* 495d66: call ebx */
	{ DWORD v_ = 0xd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d68: push 0xd8 */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d6d: push 0x1a0 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d72: push 0xc8 */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d77: push 0xe0 */
	m->ecx = m->esi;	/* 495d7c: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x495d83u; native_call(m, 0x495ed0u);	/* 495d7e: call 0x495ed0 */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 495d83: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x4d0474u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d87: push 0x4d0474 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495d8c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x495d92u; native_call(m, 0x49e9ddu);	/* 495d8d: call 0x49e9dd */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 495d92: mov edi, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495d96: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d97: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495d9c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495da1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495dabu; native_call(m, 0x44ad30u);	/* 495da6: call 0x44ad30 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 495dab: lea edx, [esp + 0x28] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495daf: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495db1: push edx */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495db2: push 0x140 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 495db7: push 0xc8 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 495dbc: push 0x140 */
	m->esp -= 4; M32(m->esp) = 0x495dc6u; native_call(m, 0x44ae10u);	/* 495dc1: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495dc6: add esp, 0x2c */
L_495dc9:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495dc9: push edi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495dca: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495dcf: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495dd4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x495ddbu; native_call(m, m->ebx);	/* 495dd9: call ebx */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ddb: push 0x100 */
	{ DWORD v_ = 0x1a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495de0: push 0x1a0 */
	{ DWORD v_ = 0xf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495de5: push 0xf0 */
	{ DWORD v_ = 0xe0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495dea: push 0xe0 */
	m->ecx = m->esi;	/* 495def: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x495df6u; native_call(m, 0x495ed0u);	/* 495df1: call 0x495ed0 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 495df6: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x4d0440u; m->esp -= 4; M32(m->esp) = v_; }	/* 495dfa: push 0x4d0440 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495dff: push eax */
	m->esp -= 4; M32(m->esp) = 0x495e05u; native_call(m, 0x49e9ddu);	/* 495e00: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 495e05: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495e0b: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 495e0e: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495e10: push edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e11: push 0x3f000000 */
	if (!m->zf) goto L_495e24;	/* 495e16: jne 0x495e24 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e18: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e1d: push 0x3f800000 */
	goto L_495e2e;	/* 495e22: jmp 0x495e2e */
L_495e24:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e24: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e29: push 0x3f000000 */
L_495e2e:
	m->esp -= 4; M32(m->esp) = 0x495e33u; native_call(m, 0x44ad30u);	/* 495e2e: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495e33: add esp, 0x10 */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 495e36: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e3a: push 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 495e3c: push ecx */
	{ DWORD v_ = 0x110u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e3d: push 0x110 */
	{ DWORD v_ = 0xf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e42: push 0xf0 */
	{ DWORD v_ = 0x110u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e47: push 0x110 */
	m->esp -= 4; M32(m->esp) = 0x495e51u; native_call(m, 0x44ae10u);	/* 495e4c: call 0x44ae10 */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 495e51: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x4d043cu; m->esp -= 4; M32(m->esp) = v_; }	/* 495e55: push 0x4d043c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 495e5a: push edx */
	m->esp -= 4; M32(m->esp) = 0x495e60u; native_call(m, 0x49e9ddu);	/* 495e5b: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esi + 0x2340cfcu));	/* 495e60: mov eax, dword ptr [esi + 0x2340cfc] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495e66: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495e69: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 495e6c: push edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e6d: push 0x3f000000 */
	if (!m->zf) goto L_495e80;	/* 495e72: jne 0x495e80 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e74: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e79: push 0x3f800000 */
	goto L_495e8a;	/* 495e7e: jmp 0x495e8a */
L_495e80:
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e80: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e85: push 0x3f000000 */
L_495e8a:
	m->esp -= 4; M32(m->esp) = 0x495e8fu; native_call(m, 0x44ad30u);	/* 495e8a: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495e8f: add esp, 0x10 */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 495e92: lea eax, [esp + 0x10] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e96: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 495e98: push eax */
L_495e99:
	{ DWORD v_ = 0x170u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e99: push 0x170 */
	{ DWORD v_ = 0xf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 495e9e: push 0xf0 */
	{ DWORD v_ = 0x170u; m->esp -= 4; M32(m->esp) = v_; }	/* 495ea3: push 0x170 */
	m->esp -= 4; M32(m->esp) = 0x495eadu; native_call(m, 0x44ae10u);	/* 495ea8: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495ead: add esp, 0x14 */
L_495eb0:
	m->edi = M32(m->esp); m->esp += 4;	/* 495eb0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 495eb1: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 495eb2: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 495eb3: add esp, 0x104 */
	m->esp += 4 + 0; return;	/* 495eb9: ret  */
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
