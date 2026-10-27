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

static void lift_420730(X86 *m);
static void lift_4226b0(X86 *m);

/* setup_drawControlSlider (0x4226b0), lifted by tools/lift.py */
static void lift_4226b0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4226b0: push ecx */
	m->eax = M32((DWORD)(0x4ded88u));	/* 4226b1: mov eax, dword ptr [0x4ded88] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4226b6: push edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4226b7: test eax, eax */
	m->edi = 0x1u;	/* 4226b9: mov edi, 1 */
	if (m->zf) goto L_42275c;	/* 4226be: je 0x42275c */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4226c4: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4226c9: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4226cf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4226d0: push ecx */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4226d1: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x4226e0u; lift_420730(m);	/* 4226db: call 0x420730 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4226e0: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4226e3: sub eax, 0 */
	if (m->zf) goto L_422739;	/* 4226e6: je 0x422739 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4226e8: dec eax */
	if (m->zf) goto L_422721;	/* 4226e9: je 0x422721 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4226eb: dec eax */
	if (!m->zf) goto L_42275c;	/* 4226ec: jne 0x42275c */
	m->edx = M32((DWORD)(0x4ded68u));	/* 4226ee: mov edx, dword ptr [0x4ded68] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 4226f4: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4226fa: sub edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x108u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4226fc: sub edx, 0x108 */
	M32((DWORD)(m->esp + 0x4u)) = m->edx;	/* 422702: mov dword ptr [esp + 4], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 422706: fild dword ptr [esp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f4u));	/* 42270a: fmul dword ptr [0x4a94f4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 422710: call 0x49ec14 */
	m->ecx = m->edi;	/* 422715: mov ecx, edi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 422717: sub ecx, eax */
	M32((DWORD)(0x4de1c8u)) = m->ecx;	/* 422719: mov dword ptr [0x4de1c8], ecx */
	goto L_42275c;	/* 42271f: jmp 0x42275c */
L_422721:
	m->eax = M32((DWORD)(0x4de1c8u));	/* 422721: mov eax, dword ptr [0x4de1c8] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422726: cmp eax, 0x64 */
	if (m->sf == m->of) goto L_42275c;	/* 422729: jge 0x42275c */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 42272b: inc eax */
	M32((DWORD)(0x4dde90u)) = m->edi;	/* 42272c: mov dword ptr [0x4dde90], edi */
	M32((DWORD)(0x4de1c8u)) = m->eax;	/* 422732: mov dword ptr [0x4de1c8], eax */
	goto L_422752;	/* 422737: jmp 0x422752 */
L_422739:
	m->eax = M32((DWORD)(0x4de1c8u));	/* 422739: mov eax, dword ptr [0x4de1c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42273e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_42275c;	/* 422740: jle 0x42275c */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 422742: dec eax */
	M32((DWORD)(0x4dde90u)) = 0x0u;	/* 422743: mov dword ptr [0x4dde90], 0 */
	M32((DWORD)(0x4de1c8u)) = m->eax;	/* 42274d: mov dword ptr [0x4de1c8], eax */
L_422752:
	M32((DWORD)(0x4ddb98u)) = 0x40a00000u;	/* 422752: mov dword ptr [0x4ddb98], 0x40a00000 */
L_42275c:
	m->eax = M32((DWORD)(0x4ded94u));	/* 42275c: mov eax, dword ptr [0x4ded94] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422761: test eax, eax */
	if (m->zf) goto L_422821;	/* 422763: je 0x422821 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 422769: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 42276f: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 422775: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 422777: test ah, 0x41 */
	if (!m->zf) goto L_422821;	/* 42277a: jne 0x422821 */
	m->edx = M32((DWORD)(0x4ded6cu));	/* 422780: mov edx, dword ptr [0x4ded6c] */
	m->eax = M32((DWORD)(0x4ded68u));	/* 422786: mov eax, dword ptr [0x4ded68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42278b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42278c: push eax */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 42278d: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x42279cu; lift_420730(m);	/* 422797: call 0x420730 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42279c: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42279f: sub eax, 0 */
	if (m->zf) goto L_4227fe;	/* 4227a2: je 0x4227fe */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4227a4: dec eax */
	if (m->zf) goto L_4227db;	/* 4227a5: je 0x4227db */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4227a7: dec eax */
	if (!m->zf) goto L_422821;	/* 4227a8: jne 0x422821 */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4227aa: mov ecx, dword ptr [0x4ded68] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4227b0: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4227b5: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x108u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4227b7: sub ecx, 0x108 */
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 4227bd: mov dword ptr [esp + 4], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 4227c1: fild dword ptr [esp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f4u));	/* 4227c5: fmul dword ptr [0x4a94f4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4227cb: call 0x49ec14 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4227d0: sub edi, eax */
	M32((DWORD)(0x4de1c8u)) = m->edi;	/* 4227d2: mov dword ptr [0x4de1c8], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4227d8: pop edi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4227d9: pop ecx */
	m->esp += 4 + 0; return;	/* 4227da: ret  */
L_4227db:
	m->eax = M32((DWORD)(0x4de1c8u));	/* 4227db: mov eax, dword ptr [0x4de1c8] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4227e0: cmp eax, 0x64 */
	if (m->sf == m->of) goto L_422821;	/* 4227e3: jge 0x422821 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4227e5: inc eax */
	M32((DWORD)(0x4dde90u)) = m->edi;	/* 4227e6: mov dword ptr [0x4dde90], edi */
	M32((DWORD)(0x4de1c8u)) = m->eax;	/* 4227ec: mov dword ptr [0x4de1c8], eax */
	M32((DWORD)(0x4ddb98u)) = 0x40a00000u;	/* 4227f1: mov dword ptr [0x4ddb98], 0x40a00000 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4227fb: pop edi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4227fc: pop ecx */
	m->esp += 4 + 0; return;	/* 4227fd: ret  */
L_4227fe:
	m->eax = M32((DWORD)(0x4de1c8u));	/* 4227fe: mov eax, dword ptr [0x4de1c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422803: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_422821;	/* 422805: jle 0x422821 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 422807: dec eax */
	M32((DWORD)(0x4dde90u)) = 0x0u;	/* 422808: mov dword ptr [0x4dde90], 0 */
	M32((DWORD)(0x4de1c8u)) = m->eax;	/* 422812: mov dword ptr [0x4de1c8], eax */
	M32((DWORD)(0x4ddb98u)) = 0x40a00000u;	/* 422817: mov dword ptr [0x4ddb98], 0x40a00000 */
L_422821:
	m->edi = M32(m->esp); m->esp += 4;	/* 422821: pop edi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 422822: pop ecx */
	m->esp += 4 + 0; return;	/* 422823: ret  */
}

/* setup_420730 (0x420730), lifted by tools/lift.py */
static void lift_420730(X86 *m)
{
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 420730: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 420734: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 420735: mov esi, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 420739: xor eax, eax */
	m->ecx = 0x4ddda0u;	/* 42073b: mov ecx, 0x4ddda0 */
L_420740:
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->ecx + 0xfffffff8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420740: cmp esi, dword ptr [ecx - 8] */
	if (m->sf != m->of) goto L_420753;	/* 420743: jl 0x420753 */
	{ DWORD a_ = m->esi, b_ = M32((DWORD)(m->ecx + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420745: cmp esi, dword ptr [ecx] */
	if (!m->zf && m->sf == m->of) goto L_420753;	/* 420747: jg 0x420753 */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->ecx + 0xfffffffcu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420749: cmp edx, dword ptr [ecx - 4] */
	if (m->sf != m->of) goto L_420753;	/* 42074c: jl 0x420753 */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->ecx + 0x4u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42074e: cmp edx, dword ptr [ecx + 4] */
	if (m->zf || m->sf != m->of) goto L_420762;	/* 420751: jle 0x420762 */
L_420753:
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 420753: add ecx, 0x10 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 420756: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x4dddd0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 420757: cmp ecx, 0x4dddd0 */
	if (m->sf != m->of) goto L_420740;	/* 42075d: jl 0x420740 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42075f: or eax, 0xffffffff */
L_420762:
	m->esi = M32(m->esp); m->esp += 4;	/* 420762: pop esi */
	m->esp += 4 + 0; return;	/* 420763: ret  */
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
