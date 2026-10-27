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

static void lift_445520(X86 *m);
static void lift_44dc60(X86 *m);
static void lift_40b550(X86 *m);
static void lift_43bde0(X86 *m);
static void lift_412450(X86 *m);

/* armc_412450 (0x412450), lifted by tools/lift.py */
static void lift_412450(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 412450: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 412451: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 412452: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 412453: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41245au; native_call(m, 0x41ef90u);	/* 412455: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41245a: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x412463u; native_call(m, M32(0x4a9218u));	/* 41245d: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 412463: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x41246eu; native_call(m, M32(0x4a9224u));	/* 412468: call dword ptr [0x4a9224] */
	m->edi = M32((DWORD)(0x4a9228u));	/* 41246e: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412474: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412479: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41247e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 412483: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x41248au; native_call(m, m->edi);	/* 412488: call edi */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 41248a: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 41248f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 412491: and ecx, 0x800001ff */
	if (!m->sf) goto L_4124a1;	/* 412497: jns 0x4124a1 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 412499: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 41249a: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4124a0: inc ecx */
L_4124a1:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4124a1: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4124a2: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4124a8: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4124a9: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4124ab: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4124b1: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4124b4: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4124bdu; native_call(m, 0x4566c0u);	/* 4124b8: call 0x4566c0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4124bd: xor eax, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4124bf: xor esi, esi */
L_4124c1:
	m->ebx = (DWORD)(m->eax + 0x1u);	/* 4124c1: lea ebx, [eax + 1] */
	m->eax = M32((DWORD)(0x4dc798u));	/* 4124c4: mov eax, dword ptr [0x4dc798] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4124c9: cmp eax, ebx */
	if (!m->zf) goto L_4124d4;	/* 4124cb: jne 0x4124d4 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4124cd: push 0x3f4ccccd */
	goto L_4124d9;	/* 4124d2: jmp 0x4124d9 */
L_4124d4:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4124d4: push 0x3ecccccd */
L_4124d9:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4124d9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4124de: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4124e3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4124eau; native_call(m, m->edi);	/* 4124e8: call edi */
	m->ecx = M32((DWORD)(0x4dcc94u));	/* 4124ea: mov ecx, dword ptr [0x4dcc94] */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 4124f0: mov eax, dword ptr [0x4dcc90] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4124f5: push 1 */
	m->edx = (DWORD)(m->ecx + 0x18u);	/* 4124f7: lea edx, [ecx + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4124fa: add ecx, -8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4124fd: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x70u);	/* 4124fe: lea edx, [esi + eax + 0x70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412502: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x10u);	/* 412503: lea eax, [esi + eax + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412507: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412508: push eax */
	m->esp -= 4; M32(m->esp) = 0x41250eu; native_call(m, 0x4282f0u);	/* 412509: call 0x4282f0 */
	{ DWORD a_ = m->esi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 41250e: add esi, 0x64 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 412511: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x12cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 412514: cmp esi, 0x12c */
	m->eax = m->ebx;	/* 41251a: mov eax, ebx */
	if (m->sf != m->of) goto L_4124c1;	/* 41251c: jl 0x4124c1 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41251e: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x412529u; native_call(m, M32(0x4a922cu));	/* 412523: call dword ptr [0x4a922c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 412529: xor eax, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 41252b: xor edi, edi */
	m->esi = 0x7565a4u;	/* 41252d: mov esi, 0x7565a4 */
L_412532:
	m->ebx = (DWORD)(m->eax + 0x1u);	/* 412532: lea ebx, [eax + 1] */
	m->eax = M32((DWORD)(0x4dc798u));	/* 412535: mov eax, dword ptr [0x4dc798] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41253a: cmp eax, ebx */
	if (!m->zf) goto L_41255b;	/* 41253c: jne 0x41255b */
	m->ecx = M32((DWORD)(0x4dbc64u));	/* 41253e: mov ecx, dword ptr [0x4dbc64] */
	m->edx = M32((DWORD)(0x4dbc60u));	/* 412544: mov edx, dword ptr [0x4dbc60] */
	m->eax = M32((DWORD)(0x4dbc5cu));	/* 41254a: mov eax, dword ptr [0x4dbc5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41254f: push ecx */
	m->ecx = M32((DWORD)(0x4dbc58u));	/* 412550: mov ecx, dword ptr [0x4dbc58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412556: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412557: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412558: push ecx */
	goto L_412576;	/* 412559: jmp 0x412576 */
L_41255b:
	m->edx = M32((DWORD)(0x4dc1dcu));	/* 41255b: mov edx, dword ptr [0x4dc1dc] */
	m->eax = M32((DWORD)(0x4dc1d8u));	/* 412561: mov eax, dword ptr [0x4dc1d8] */
	m->ecx = M32((DWORD)(0x4dc1d4u));	/* 412566: mov ecx, dword ptr [0x4dc1d4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41256c: push edx */
	m->edx = M32((DWORD)(0x4dc1d0u));	/* 41256d: mov edx, dword ptr [0x4dc1d0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412573: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412574: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412575: push edx */
L_412576:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 412576: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x412580u; native_call(m, 0x41f0e0u);	/* 41257b: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 412580: mov eax, dword ptr [0x4dcc90] */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 412585: mov edx, dword ptr [0x4dcc94] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41258b: add esp, 0x14 */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x70u);	/* 41258e: lea ecx, [edi + eax + 0x70] */
	m->eax = (DWORD)(m->edi + m->eax*1 + 0x10u);	/* 412592: lea eax, [edi + eax + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 412596: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 412597: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 412598: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 412599: push eax */
	m->esp -= 4; M32(m->esp) = 0x41259fu; native_call(m, 0x4029d0u);	/* 41259a: call 0x4029d0 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 41259f: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4125a5: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4125a8: add edi, 0x64 */
	{ DWORD a_ = m->esi, b_ = 0x756724u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4125ab: cmp esi, 0x756724 */
	m->eax = m->ebx;	/* 4125b1: mov eax, ebx */
	if (m->sf != m->of) goto L_412532;	/* 4125b3: jl 0x412532 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4125b9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4125ba: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4125bb: pop ebx */
	m->esp += 4 + 0; return;	/* 4125bc: ret  */
}

/* skirmish_445520 (0x445520), lifted by tools/lift.py */
static void lift_445520(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 445520: push esi */
	m->esi = M32((DWORD)(0x9ef1ecu));	/* 445521: mov esi, dword ptr [0x9ef1ec] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445527: test esi, esi */
	if (m->zf) goto L_4456a6;	/* 445529: je 0x4456a6 */
	m->eax = M32((DWORD)(0x9f105cu));	/* 44552f: mov eax, dword ptr [0x9f105c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445534: test eax, eax */
	if (!m->zf) goto L_4455d9;	/* 445536: jne 0x4455d9 */
	m->eax = M32((DWORD)(0x4d7348u));	/* 44553c: mov eax, dword ptr [0x4d7348] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445541: test eax, eax */
	if (!m->zf) goto L_4455d9;	/* 445543: jne 0x4455d9 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 445549: fld dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9f16b8u));	/* 44554f: fadd dword ptr [0x9f16b8] */
	MF((DWORD)(0x9f16b8u)) = (float)ST(0);	/* 445555: fst dword ptr [0x9f16b8] */
	FCOM(ST(0), (long double)*(const double *)(DWORD)(0x4a95e0u)); FPOP();	/* 44555b: fcomp qword ptr [0x4a95e0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 445561: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 445563: test ah, 0x41 */
	if (!m->zf) goto L_4455d9;	/* 445566: jne 0x4455d9 */
	m->eax = M32((DWORD)(0x9ef1f4u));	/* 445568: mov eax, dword ptr [0x9ef1f4] */
	m->edx = M32((DWORD)(0x9eeba4u));	/* 44556d: mov edx, dword ptr [0x9eeba4] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 445573: inc eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 445574: push ebx */
	M32((DWORD)(0x9ef1f4u)) = m->eax;	/* 445575: mov dword ptr [0x9ef1f4], eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44557a: push edi */
	m->ecx = (DWORD)(m->edx + m->eax*1 + 0x0u);	/* 44557b: lea ecx, [edx + eax] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44557e: add ecx, esi */
	{ DWORD a_ = M8((DWORD)(m->ecx + 0x0u)), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 445580: cmp byte ptr [ecx], 0xd */
	if (!m->zf) goto L_445591;	/* 445583: jne 0x445591 */
	{ DWORD a_ = M8((DWORD)(m->ecx + 0x1u)), b_ = 0xau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 445585: cmp byte ptr [ecx + 1], 0xa */
	if (!m->zf) goto L_445591;	/* 445589: jne 0x445591 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44558b: inc eax */
	M32((DWORD)(0x9ef1f4u)) = m->eax;	/* 44558c: mov dword ptr [0x9ef1f4], eax */
L_445591:
	m->ecx = (DWORD)(m->edx + m->eax*1 + 0x0u);	/* 445591: lea ecx, [edx + eax] */
	{ DWORD a_ = M8((DWORD)(m->ecx + m->esi*1 + 0x0u)), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 445594: test byte ptr [ecx + esi], 0x80 */
	if (m->zf) goto L_4455a0;	/* 445598: je 0x4455a0 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44559a: inc eax */
	M32((DWORD)(0x9ef1f4u)) = m->eax;	/* 44559b: mov dword ptr [0x9ef1f4], eax */
L_4455a0:
	m->ecx = (DWORD)(m->eax + 0x1u);	/* 4455a0: lea ecx, [eax + 1] */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4455a3: add esi, edx */
	m->ebx = m->ecx;	/* 4455a5: mov ebx, ecx */
	m->edi = 0x9f1064u;	/* 4455a7: mov edi, 0x9f1064 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4455ac: shr ecx, 2 */
	M32((DWORD)(0x9f16b8u)) = 0x0u;	/* 4455af: mov dword ptr [0x9f16b8], 0 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4455b9: add edx, eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4455bb: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9ef200u));	/* 4455bd: mov eax, dword ptr [0x9ef200] */
	m->ecx = m->ebx;	/* 4455c2: mov ecx, ebx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4455c4: and ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4455c7: cmp edx, eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4455c9: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4455cb: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4455cc: pop ebx */
	if (m->sf != m->of) goto L_4455d9;	/* 4455cd: jl 0x4455d9 */
	M32((DWORD)(0x9f105cu)) = 0x1u;	/* 4455cf: mov dword ptr [0x9f105c], 1 */
L_4455d9:
	{ DWORD v_ = 0x23eu; m->esp -= 4; M32(m->esp) = v_; }	/* 4455d9: push 0x23e */
	m->esp -= 4; M32(m->esp) = 0x4455e3u; native_call(m, 0x4017b0u);	/* 4455de: call 0x4017b0 */
	{ DWORD v_ = 0x76u; m->esp -= 4; M32(m->esp) = v_; }	/* 4455e3: push 0x76 */
	m->esp -= 4; M32(m->esp) = 0x4455eau; native_call(m, 0x4017c0u);	/* 4455e5: call 0x4017c0 */
	m->edx = M32((DWORD)(0x9f16acu));	/* 4455ea: mov edx, dword ptr [0x9f16ac] */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 4455f0: mov eax, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->edx, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4455f5: add edx, 0x40 */
	{ DWORD v_ = 0x9f1064u; m->esp -= 4; M32(m->esp) = v_; }	/* 4455f8: push 0x9f1064 */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4455fd: add eax, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445600: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445601: push eax */
	m->esp -= 4; M32(m->esp) = 0x445607u; native_call(m, 0x402620u);	/* 445602: call 0x402620 */
	m->eax = M32((DWORD)(0x9f105cu));	/* 445607: mov eax, dword ptr [0x9f105c] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44560c: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44560f: test eax, eax */
	if (!m->zf) goto L_44568f;	/* 445611: jne 0x44568f */
	m->eax = M32((DWORD)(0x4d7348u));	/* 445613: mov eax, dword ptr [0x4d7348] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445618: test eax, eax */
	if (!m->zf) goto L_44568f;	/* 44561a: jne 0x44568f */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44561c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445621: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445626: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44562b: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44562d: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x445637u; native_call(m, 0x41f0e0u);	/* 445632: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4d23ccu));	/* 445637: mov eax, dword ptr [0x4d23cc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44563c: push 1 */
	m->ecx = (DWORD)(m->eax + 0x11u);	/* 44563e: lea ecx, [eax + 0x11] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 445641: dec eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445642: push ecx */
	m->ecx = M32((DWORD)(0x4d23c8u));	/* 445643: mov ecx, dword ptr [0x4d23c8] */
	m->edx = (DWORD)(m->ecx + 0x8u);	/* 445649: lea edx, [ecx + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44564c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44564d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44564e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x445654u; native_call(m, 0x427970u);	/* 44564f: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445654: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445659: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44565e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 445663: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 445665: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44566fu; native_call(m, 0x41f0e0u);	/* 44566a: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4d23ccu));	/* 44566f: mov eax, dword ptr [0x4d23cc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 445674: push 1 */
	m->ecx = (DWORD)(m->eax + 0x11u);	/* 445676: lea ecx, [eax + 0x11] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 445679: dec eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44567a: push ecx */
	m->ecx = M32((DWORD)(0x4d23c8u));	/* 44567b: mov ecx, dword ptr [0x4d23c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445681: push ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445682: add ecx, -8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445685: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445686: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44568cu; native_call(m, 0x427970u);	/* 445687: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44568c: add esp, 0x50 */
L_44568f:
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 44568f: push 0x280 */
	m->esp -= 4; M32(m->esp) = 0x445699u; native_call(m, 0x4017b0u);	/* 445694: call 0x4017b0 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 445699: push 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x4456a3u; native_call(m, 0x4017c0u);	/* 44569e: call 0x4017c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4456a3: add esp, 8 */
L_4456a6:
	m->esi = M32(m->esp); m->esp += 4;	/* 4456a6: pop esi */
	m->esp += 4 + 0; return;	/* 4456a7: ret  */
}

/* profile_44dc60 (0x44dc60), lifted by tools/lift.py */
static void lift_44dc60(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc60: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc61: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc62: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc63: push 2 */
	m->esp -= 4; M32(m->esp) = 0x44dc6au; native_call(m, 0x41ef90u);	/* 44dc65: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44dc6a: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44dc73u; native_call(m, M32(0x4a9218u));	/* 44dc6d: call dword ptr [0x4a9218] */
	m->edi = M32((DWORD)(0x4a9228u));	/* 44dc73: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc79: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc7e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc83: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dc88: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44dc8fu; native_call(m, m->edi);	/* 44dc8d: call edi */
	m->eax = M32((DWORD)(0x4deb50u));	/* 44dc8f: mov eax, dword ptr [0x4deb50] */
	m->ecx = M32((DWORD)(0x9f8f24u));	/* 44dc94: mov ecx, dword ptr [0x9f8f24] */
	m->edx = M32((DWORD)(0x9f8f20u));	/* 44dc9a: mov edx, dword ptr [0x9f8f20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dca0: push eax */
	m->eax = M32((DWORD)(0x9f8ea8u));	/* 44dca1: mov eax, dword ptr [0x9f8ea8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dca6: push ecx */
	m->ecx = M32((DWORD)(0x9f8eacu));	/* 44dca7: mov ecx, dword ptr [0x9f8eac] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dcad: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dcae: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dcaf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44dcb5u; native_call(m, 0x427b60u);	/* 44dcb0: call 0x427b60 */
	m->eax = M32((DWORD)(0x9f8f20u));	/* 44dcb5: mov eax, dword ptr [0x9f8f20] */
	m->ecx = M32((DWORD)(0x9f8eacu));	/* 44dcba: mov ecx, dword ptr [0x9f8eac] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44dcc0: sub eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44dcc2: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44dcc3: sub eax, edx */
	m->edx = M32((DWORD)(0x9f8ebcu));	/* 44dcc5: mov edx, dword ptr [0x9f8ebc] */
	m->esi = m->eax;	/* 44dccb: mov esi, eax */
	m->eax = M32((DWORD)(0x9f8eb8u));	/* 44dccd: mov eax, dword ptr [0x9f8eb8] */
	{ DWORD a_ = m->esi, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 44dcd2: sar esi, 1 */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44dcd4: add esi, ecx */
	m->ecx = M32((DWORD)(0x9f8eb4u));	/* 44dcd6: mov ecx, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dcdc: push edx */
	m->edx = M32((DWORD)(0x9f8eb0u));	/* 44dcdd: mov edx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dce3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dce4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dce5: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dce6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44dcf0u; native_call(m, 0x41f0e0u);	/* 44dceb: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9f8ea8u));	/* 44dcf0: mov ecx, dword ptr [0x9f8ea8] */
	m->eax = M32((DWORD)(0x9f8f20u));	/* 44dcf6: mov eax, dword ptr [0x9f8f20] */
	m->edx = M32((DWORD)(0x9f8eacu));	/* 44dcfb: mov edx, dword ptr [0x9f8eac] */
	{ DWORD v_ = 0x751d24u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd01: push 0x751d24 */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44dd06: add ecx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd09: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd0a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd0b: push edx */
	m->esp -= 4; M32(m->esp) = 0x44dd11u; native_call(m, 0x4029d0u);	/* 44dd0c: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44dd11: add esp, 0x38 */
	{ DWORD a_ = m->esi, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44dd14: add esi, -0x32 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd17: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44dd22u; native_call(m, M32(0x4a9224u));	/* 44dd1c: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44dd22: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44dd27: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44dd29: and ecx, 0x800001ff */
	if (!m->sf) goto L_44dd39;	/* 44dd2f: jns 0x44dd39 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44dd31: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44dd32: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44dd38: inc ecx */
L_44dd39:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44dd39: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44dd3a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd40: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44dd41: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44dd43: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44dd49: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44dd4c: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44dd55u; native_call(m, 0x4566c0u);	/* 44dd50: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd55: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd5a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd5f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd64: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44dd6bu; native_call(m, m->edi);	/* 44dd69: call edi */
	m->eax = M32((DWORD)(0x9f8ea8u));	/* 44dd6b: mov eax, dword ptr [0x9f8ea8] */
	m->ebx = (DWORD)(m->esi + 0x60u);	/* 44dd70: lea ebx, [esi + 0x60] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd73: push 1 */
	m->ecx = (DWORD)(m->eax + 0x70u);	/* 44dd75: lea ecx, [eax + 0x70] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44dd78: add eax, 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd7b: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd7c: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd7d: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd7e: push esi */
	m->esp -= 4; M32(m->esp) = 0x44dd84u; native_call(m, 0x4282f0u);	/* 44dd7f: call 0x4282f0 */
	m->edx = M32((DWORD)(0x9f8ebcu));	/* 44dd84: mov edx, dword ptr [0x9f8ebc] */
	m->eax = M32((DWORD)(0x9f8eb8u));	/* 44dd8a: mov eax, dword ptr [0x9f8eb8] */
	m->ecx = M32((DWORD)(0x9f8eb4u));	/* 44dd8f: mov ecx, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd95: push edx */
	m->edx = M32((DWORD)(0x9f8eb0u));	/* 44dd96: mov edx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd9c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd9d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd9e: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44dd9f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44dda9u; native_call(m, 0x41f0e0u);	/* 44dda4: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8ea8u));	/* 44dda9: mov eax, dword ptr [0x9f8ea8] */
	{ DWORD v_ = 0x7517a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddae: push 0x7517a4 */
	{ DWORD a_ = m->eax, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ddb3: add eax, 0x58 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddb6: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddb7: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddb8: push esi */
	m->esp -= 4; M32(m->esp) = 0x44ddbeu; native_call(m, 0x4029d0u);	/* 44ddb9: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ddbe: add esp, 0x38 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddc1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddc6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddcb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddd0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44ddd7u; native_call(m, m->edi);	/* 44ddd5: call edi */
	m->ecx = M32((DWORD)(0x9f8f24u));	/* 44ddd7: mov ecx, dword ptr [0x9f8f24] */
	m->edx = M32((DWORD)(0x9f8f20u));	/* 44dddd: mov edx, dword ptr [0x9f8f20] */
	m->eax = M32((DWORD)(0x9f8ea8u));	/* 44dde3: mov eax, dword ptr [0x9f8ea8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44dde8: push ecx */
	m->ecx = M32((DWORD)(0x9f8eacu));	/* 44dde9: mov ecx, dword ptr [0x9f8eac] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddef: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddf0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ddf1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44ddf7u; native_call(m, 0x428b50u);	/* 44ddf2: call 0x428b50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ddf7: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44ddfa: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44ddfb: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44ddfc: pop ebx */
	m->esp += 4 + 0; return;	/* 44ddfd: ret  */
}

/* arena_drawCustomOption (0x40b550), lifted by tools/lift.py */
static void lift_40b550(X86 *m)
{
	m->eax = M32((DWORD)(0x680cd0u));	/* 40b550: mov eax, dword ptr [0x680cd0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40b555: test eax, eax */
	if (m->zf) goto L_40b55e;	/* 40b557: je 0x40b55e */
	m->esp -= 4; M32(m->esp) = 0x40b55eu; native_call(m, 0x40b420u);	/* 40b559: call 0x40b420 */
L_40b55e:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4db54au))) & 0xff) << 0);	/* 40b55e: mov al, byte ptr [0x4db54a] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40b563: test al, al */
	if (m->zf) goto L_40b5f1;	/* 40b565: je 0x40b5f1 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b56b: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b570: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b572: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b574: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b576: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40b580u; native_call(m, 0x41f0e0u);	/* 40b57b: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40b580: mov eax, dword ptr [0x4dbb04] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b585: push 1 */
	m->ecx = (DWORD)(m->eax + 0xd0u);	/* 40b587: lea ecx, [eax + 0xd0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b58d: add eax, 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b590: push ecx */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40b591: mov ecx, dword ptr [0x4dbb08] */
	m->edx = (DWORD)(m->ecx + 0xffffffeau);	/* 40b597: lea edx, [ecx - 0x16] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b59a: add ecx, 0xffffff6a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5a0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5a1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5a2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40b5a8u; native_call(m, 0x427970u);	/* 40b5a3: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5a8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5ad: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5af: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5b4: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5b9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x40b5c3u; native_call(m, 0x41f0e0u);	/* 40b5be: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb08u));	/* 40b5c3: mov eax, dword ptr [0x4dbb08] */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40b5c8: mov edx, dword ptr [0x4dbb04] */
	{ DWORD v_ = 0x4ad56cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5ce: push 0x4ad56c */
	{ DWORD a_ = m->edx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40b5d3: add edx, 0x88 */
	m->ecx = (DWORD)(m->eax + 0xffffffeau);	/* 40b5d9: lea ecx, [eax - 0x16] */
	{ DWORD a_ = m->eax, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b5dc: add eax, 0xffffff6a */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5e1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5e2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5e3: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b5e9u; native_call(m, 0x4029d0u);	/* 40b5e4: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b5e9: add esp, 0x4c */
	goto L_40b706;	/* 40b5ec: jmp 0x40b706 */
L_40b5f1:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5f1: push esi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b5f2: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40b5fdu; native_call(m, M32(0x4a9224u));	/* 40b5f7: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9da324u));	/* 40b5fd: mov eax, dword ptr [0x9da324] */
	m->ecx = m->eax;	/* 40b602: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b604: and ecx, 0x800001ff */
	if (!m->sf) goto L_40b614;	/* 40b60a: jns 0x40b614 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 40b60c: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40b60d: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 40b613: inc ecx */
L_40b614:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 40b614: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 40b615: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b61b: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b61c: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 40b61e: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40b624: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 40b627: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x40b630u; native_call(m, 0x4566c0u);	/* 40b62b: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b630: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b635: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b63a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b63f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b64au; native_call(m, M32(0x4a9228u));	/* 40b644: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b64a: push 7 */
	m->esp -= 4; M32(m->esp) = 0x40b652u; native_call(m, M32(0x4a921cu));	/* 40b64c: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 40b652: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b658: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b65a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40b65eu; native_call(m, m->esi);	/* 40b65c: call esi */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40b65e: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40b663: mov ecx, dword ptr [0x4dbb08] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b669: add eax, 0x50 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b66c: add ecx, 0xffffff6a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b672: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b673: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40b679u; native_call(m, 0x41ef60u);	/* 40b674: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b679: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b67c: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b67e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b685u; native_call(m, m->esi);	/* 40b683: call esi */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40b685: mov edx, dword ptr [0x4dbb04] */
	m->eax = M32((DWORD)(0x4dbb08u));	/* 40b68b: mov eax, dword ptr [0x4dbb08] */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40b690: add edx, 0x50 */
	{ DWORD a_ = m->eax, b_ = 0xffffffeau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b693: add eax, -0x16 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b696: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b697: push eax */
	m->esp -= 4; M32(m->esp) = 0x40b69du; native_call(m, 0x41ef60u);	/* 40b698: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b69d: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6a0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6a5: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x40b6acu; native_call(m, m->esi);	/* 40b6aa: call esi */
	m->ecx = M32((DWORD)(0x4dbb04u));	/* 40b6ac: mov ecx, dword ptr [0x4dbb04] */
	m->edx = M32((DWORD)(0x4dbb08u));	/* 40b6b2: mov edx, dword ptr [0x4dbb08] */
	{ DWORD a_ = m->ecx, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b6b8: add ecx, 0xd0 */
	{ DWORD a_ = m->edx, b_ = 0xffffffeau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 40b6be: add edx, -0x16 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6c1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6c2: push edx */
	m->esp -= 4; M32(m->esp) = 0x40b6c8u; native_call(m, 0x41ef60u);	/* 40b6c3: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b6c8: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6cb: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6d0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40b6d4u; native_call(m, m->esi);	/* 40b6d2: call esi */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40b6d4: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40b6d9: mov ecx, dword ptr [0x4dbb08] */
	{ DWORD a_ = m->eax, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b6df: add eax, 0xd0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b6e4: add ecx, 0xffffff6a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6ea: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6eb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40b6f1u; native_call(m, 0x41ef60u);	/* 40b6ec: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b6f1: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x40b6fau; native_call(m, M32(0x4a9220u));	/* 40b6f4: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b6fa: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40b705u; native_call(m, M32(0x4a922cu));	/* 40b6ff: call dword ptr [0x4a922c] */
	m->esi = M32(m->esp); m->esp += 4;	/* 40b705: pop esi */
L_40b706:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b706: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b70b: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b70d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b712: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b717: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40b721u; native_call(m, 0x41f0e0u);	/* 40b71c: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dbb04u));	/* 40b721: mov eax, dword ptr [0x4dbb04] */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40b726: mov ecx, dword ptr [0x4dbb08] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40b72c: push 0 */
	m->edx = (DWORD)(m->eax + 0xd0u);	/* 40b72e: lea edx, [eax + 0xd0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40b734: add eax, 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b737: push edx */
	m->edx = (DWORD)(m->ecx + 0xffffffeau);	/* 40b738: lea edx, [ecx - 0x16] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b73b: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40b73c: add ecx, 0xffffff6a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40b742: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40b743: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40b749u; native_call(m, 0x427970u);	/* 40b744: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40b749: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 40b74c: ret  */
}

/* room_drawCustomOption (0x43bde0), lifted by tools/lift.py */
static void lift_43bde0(X86 *m)
{
	m->eax = M32((DWORD)(0x680cd0u));	/* 43bde0: mov eax, dword ptr [0x680cd0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43bde5: test eax, eax */
	if (m->zf) goto L_43bdee;	/* 43bde7: je 0x43bdee */
	m->esp -= 4; M32(m->esp) = 0x43bdeeu; native_call(m, 0x43bcb0u);	/* 43bde9: call 0x43bcb0 */
L_43bdee:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4df9eau))) & 0xff) << 0);	/* 43bdee: mov al, byte ptr [0x4df9ea] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43bdf3: test al, al */
	if (m->zf) goto L_43be81;	/* 43bdf5: je 0x43be81 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43bdfb: push 0x3ecccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be00: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be02: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be04: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be06: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43be10u; native_call(m, 0x41f0e0u);	/* 43be0b: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43be10: mov eax, dword ptr [0x9dd1bc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be15: push 1 */
	m->ecx = (DWORD)(m->eax + 0xd0u);	/* 43be17: lea ecx, [eax + 0xd0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43be1d: add eax, 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43be20: push ecx */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43be21: mov ecx, dword ptr [0x9dd1c0] */
	m->edx = (DWORD)(m->ecx + 0xffffffeau);	/* 43be27: lea edx, [ecx - 0x16] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43be2a: add ecx, 0xffffff6a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43be30: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43be31: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43be32: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43be38u; native_call(m, 0x427970u);	/* 43be33: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be38: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be3d: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be3f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be44: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be49: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43be53u; native_call(m, 0x41f0e0u);	/* 43be4e: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1c0u));	/* 43be53: mov eax, dword ptr [0x9dd1c0] */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43be58: mov edx, dword ptr [0x9dd1bc] */
	{ DWORD v_ = 0x4ad56cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43be5e: push 0x4ad56c */
	{ DWORD a_ = m->edx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43be63: add edx, 0x88 */
	m->ecx = (DWORD)(m->eax + 0xffffffeau);	/* 43be69: lea ecx, [eax - 0x16] */
	{ DWORD a_ = m->eax, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43be6c: add eax, 0xffffff6a */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43be71: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43be72: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43be73: push eax */
	m->esp -= 4; M32(m->esp) = 0x43be79u; native_call(m, 0x4029d0u);	/* 43be74: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43be79: add esp, 0x4c */
	goto L_43bf96;	/* 43be7c: jmp 0x43bf96 */
L_43be81:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43be81: push esi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43be82: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43be8du; native_call(m, M32(0x4a9224u));	/* 43be87: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9da324u));	/* 43be8d: mov eax, dword ptr [0x9da324] */
	m->ecx = m->eax;	/* 43be92: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43be94: and ecx, 0x800001ff */
	if (!m->sf) goto L_43bea4;	/* 43be9a: jns 0x43bea4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43be9c: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43be9d: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43bea3: inc ecx */
L_43bea4:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43bea4: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43bea5: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43beab: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43beac: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43beae: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43beb4: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43beb7: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43bec0u; native_call(m, 0x4566c0u);	/* 43bebb: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bec0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bec5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43beca: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43becf: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43bedau; native_call(m, M32(0x4a9228u));	/* 43bed4: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 43beda: push 7 */
	m->esp -= 4; M32(m->esp) = 0x43bee2u; native_call(m, M32(0x4a921cu));	/* 43bedc: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 43bee2: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bee8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43beea: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43beeeu; native_call(m, m->esi);	/* 43beec: call esi */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43beee: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43bef3: mov ecx, dword ptr [0x9dd1c0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43bef9: add eax, 0x50 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43befc: add ecx, 0xffffff6a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf02: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf03: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43bf09u; native_call(m, 0x41ef60u);	/* 43bf04: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bf09: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf0c: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf0e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43bf15u; native_call(m, m->esi);	/* 43bf13: call esi */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43bf15: mov edx, dword ptr [0x9dd1bc] */
	m->eax = M32((DWORD)(0x9dd1c0u));	/* 43bf1b: mov eax, dword ptr [0x9dd1c0] */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43bf20: add edx, 0x50 */
	{ DWORD a_ = m->eax, b_ = 0xffffffeau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43bf23: add eax, -0x16 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf26: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf27: push eax */
	m->esp -= 4; M32(m->esp) = 0x43bf2du; native_call(m, 0x41ef60u);	/* 43bf28: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bf2d: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf30: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf35: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43bf3cu; native_call(m, m->esi);	/* 43bf3a: call esi */
	m->ecx = M32((DWORD)(0x9dd1bcu));	/* 43bf3c: mov ecx, dword ptr [0x9dd1bc] */
	m->edx = M32((DWORD)(0x9dd1c0u));	/* 43bf42: mov edx, dword ptr [0x9dd1c0] */
	{ DWORD a_ = m->ecx, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43bf48: add ecx, 0xd0 */
	{ DWORD a_ = m->edx, b_ = 0xffffffeau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43bf4e: add edx, -0x16 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf51: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf52: push edx */
	m->esp -= 4; M32(m->esp) = 0x43bf58u; native_call(m, 0x41ef60u);	/* 43bf53: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bf58: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf5b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf60: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43bf64u; native_call(m, m->esi);	/* 43bf62: call esi */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43bf64: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43bf69: mov ecx, dword ptr [0x9dd1c0] */
	{ DWORD a_ = m->eax, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43bf6f: add eax, 0xd0 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43bf74: add ecx, 0xffffff6a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf7a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf7b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43bf81u; native_call(m, 0x41ef60u);	/* 43bf7c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bf81: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x43bf8au; native_call(m, M32(0x4a9220u));	/* 43bf84: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf8a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43bf95u; native_call(m, M32(0x4a922cu));	/* 43bf8f: call dword ptr [0x4a922c] */
	m->esi = M32(m->esp); m->esp += 4;	/* 43bf95: pop esi */
L_43bf96:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf96: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf9b: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bf9d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfa2: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfa7: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43bfb1u; native_call(m, 0x41f0e0u);	/* 43bfac: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1bcu));	/* 43bfb1: mov eax, dword ptr [0x9dd1bc] */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43bfb6: mov ecx, dword ptr [0x9dd1c0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfbc: push 0 */
	m->edx = (DWORD)(m->eax + 0xd0u);	/* 43bfbe: lea edx, [eax + 0xd0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43bfc4: add eax, 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfc7: push edx */
	m->edx = (DWORD)(m->ecx + 0xffffffeau);	/* 43bfc8: lea edx, [ecx - 0x16] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfcb: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffff6au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43bfcc: add ecx, 0xffffff6a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfd2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bfd3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43bfd9u; native_call(m, 0x427970u);	/* 43bfd4: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bfd9: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43bfdc: ret  */
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
