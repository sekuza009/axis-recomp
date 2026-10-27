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

static void lift_483640(X86 *m);

/* script_processTriggers (0x483640), lifted by tools/lift.py */
static void lift_483640(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 483640: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 483641: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 483642: push esi */
	m->esi = m->ecx;	/* 483643: mov esi, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 483645: xor ebx, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 483647: push edi */
	m->eax = M32((DWORD)(m->esi + 0xe3c938u));	/* 483648: mov eax, dword ptr [esi + 0xe3c938] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48364e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_483708;	/* 483650: jle 0x483708 */
	m->ecx = (DWORD)(m->esi + 0xe3b044u);	/* 483656: lea ecx, [esi + 0xe3b044] */
L_48365c:
	m->eax = M32((DWORD)(m->ecx + 0xfffffffcu));	/* 48365c: mov eax, dword ptr [ecx - 4] */
	m->edi = 0x1u;	/* 48365f: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483664: cmp eax, edi */
	if (!m->zf) goto L_4836f6;	/* 483666: jne 0x4836f6 */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 48366c: mov edx, dword ptr [ecx] */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48366e: test dl, 1 */
	if (m->zf) goto L_48368c;	/* 483671: je 0x48368c */
	FPUSH((long double)(int)M32((DWORD)(m->esi + 0x20fcd40u)));	/* 483673: fild dword ptr [esi + 0x20fcd40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20fcd44u));	/* 483679: fadd dword ptr [esi + 0x20fcd44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x4u)); FPOP();	/* 48367f: fcomp dword ptr [ecx + 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 483682: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 483684: test ah, 1 */
	if (!m->zf) goto L_48368c;	/* 483687: jne 0x48368c */
	M32((DWORD)(m->ecx + 0xcu)) = m->edi;	/* 483689: mov dword ptr [ecx + 0xc], edi */
L_48368c:
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48368c: test dl, 2 */
	if (m->zf) goto L_4836f6;	/* 48368f: je 0x4836f6 */
	m->eax = M32((DWORD)(m->esi + 0x202e8d4u));	/* 483691: mov eax, dword ptr [esi + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 483697: test eax, eax */
	if (m->sf != m->of) goto L_4836f6;	/* 483699: jl 0x4836f6 */
	m->edi = m->eax;	/* 48369b: mov edi, eax */
	m->edx = M32((DWORD)(m->ecx + 0xfffffff8u));	/* 48369d: mov edx, dword ptr [ecx - 8] */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4836a0: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4836a3: add edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4836a5: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4836a8: add edi, eax */
	{ DWORD a_ = m->edi, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edi = r_; } }	/* 4836aa: shl edi, 4 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4836ad: add edi, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->edi*8 + 0x1cd94fcu)));	/* 4836af: fld dword ptr [esi + edi*8 + 0x1cd94fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x0u));	/* 4836b6: fsub dword ptr [edx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->edi*8 + 0x1cd9500u)));	/* 4836b8: fld dword ptr [esi + edi*8 + 0x1cd9500] */
	m->eax = (DWORD)(m->esi + m->edi*8 + 0x1cd94fcu);	/* 4836bf: lea eax, [esi + edi*8 + 0x1cd94fc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x4u));	/* 4836c6: fsub dword ptr [edx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4836c9: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edx + 0x8u));	/* 4836cc: fsub dword ptr [edx + 8] */
	{ long double t = ST(0); FPUSH(t); }	/* 4836cf: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 4836d1: fmul st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 4836d3: fld st(2) */
	ST(0) = ST(0) * ST(3);	/* 4836d5: fmul st(3) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4836d7: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 4836d9: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 4836db: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4836dd: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ecx + 0x8u)); FPOP();	/* 4836df: fcomp dword ptr [ecx + 8] */
	ST(0) = ST(0); FPOP();	/* 4836e2: fstp st(0) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4836e4: fnstsw ax */
	ST(0) = ST(0); FPOP();	/* 4836e6: fstp st(0) */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4836e8: test ah, 1 */
	ST(0) = ST(0); FPOP();	/* 4836eb: fstp st(0) */
	if (m->zf) goto L_4836f6;	/* 4836ed: je 0x4836f6 */
	M32((DWORD)(m->ecx + 0xcu)) = 0x1u;	/* 4836ef: mov dword ptr [ecx + 0xc], 1 */
L_4836f6:
	m->eax = M32((DWORD)(m->esi + 0xe3c938u));	/* 4836f6: mov eax, dword ptr [esi + 0xe3c938] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4836fc: inc ebx */
	{ DWORD a_ = m->ecx, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4836fd: add ecx, 0x1c */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483700: cmp ebx, eax */
	if (m->sf != m->of) goto L_48365c;	/* 483702: jl 0x48365c */
L_483708:
	m->eax = M32((DWORD)(m->esi + 0xe3c938u));	/* 483708: mov eax, dword ptr [esi + 0xe3c938] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48370e: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 483710: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48375d;	/* 483712: jle 0x48375d */
	m->ebx = (DWORD)(m->esi + 0xe3c618u);	/* 483714: lea ebx, [esi + 0xe3c618] */
	m->edi = (DWORD)(m->esi + 0xe3b050u);	/* 48371a: lea edi, [esi + 0xe3b050] */
L_483720:
	{ DWORD a_ = M32((DWORD)(m->edi + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483720: cmp dword ptr [edi], 1 */
	if (!m->zf) goto L_483746;	/* 483723: jne 0x483746 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 483725: push 0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 483727: push ebp */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 483728: push -1 */
	m->ecx = m->esi;	/* 48372a: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x483731u; native_call(m, 0x483770u);	/* 48372c: call 0x483770 */
	M32((DWORD)(m->edi + 0x0u)) = 0x0u;	/* 483731: mov dword ptr [edi], 0 */
	M32((DWORD)(m->edi + 0xfffffff0u)) = 0x0u;	/* 483737: mov dword ptr [edi - 0x10], 0 */
	M32((DWORD)(m->ebx + 0x0u)) = 0x1u;	/* 48373e: mov dword ptr [ebx], 1 */
	goto L_48374c;	/* 483744: jmp 0x48374c */
L_483746:
	M32((DWORD)(m->ebx + 0x0u)) = 0x0u;	/* 483746: mov dword ptr [ebx], 0 */
L_48374c:
	m->eax = M32((DWORD)(m->esi + 0xe3c938u));	/* 48374c: mov eax, dword ptr [esi + 0xe3c938] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 483752: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 483753: add ebx, 4 */
	{ DWORD a_ = m->edi, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 483756: add edi, 0x1c */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483759: cmp ebp, eax */
	if (m->sf != m->of) goto L_483720;	/* 48375b: jl 0x483720 */
L_48375d:
	m->edi = M32(m->esp); m->esp += 4;	/* 48375d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48375e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48375f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 483760: pop ebx */
	m->esp += 4 + 0; return;	/* 483761: ret  */
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
