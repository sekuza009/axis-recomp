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

static void lift_45e0c0(X86 *m);

/* actor_updateAll (0x45e0c0), lifted by tools/lift.py */
static void lift_45e0c0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e0c0: push esi */
	m->esi = m->ecx;	/* 45e0c1: mov esi, ecx */
	m->eax = M32((DWORD)(m->esi + 0x2149308u));	/* 45e0c3: mov eax, dword ptr [esi + 0x2149308] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e0c9: test eax, eax */
	if (m->zf) goto L_45e0da;	/* 45e0cb: je 0x45e0da */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x214930cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45e0cd: cmp dword ptr [esi + 0x214930c], 1 */
	if (m->zf) goto L_45e160;	/* 45e0d4: je 0x45e160 */
L_45e0da:
	m->eax = M32((DWORD)(m->esi + 0x202e8c8u));	/* 45e0da: mov eax, dword ptr [esi + 0x202e8c8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e0e0: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 45e0e1: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45e0e3: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_45e114;	/* 45e0e5: jle 0x45e114 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45e0e7: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45e0e8: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 45e0e9: mov ebp, dword ptr [esp + 0x14] */
	m->ebx = (DWORD)(m->esi + 0x1cd94b0u);	/* 45e0ed: lea ebx, [esi + 0x1cd94b0] */
L_45e0f3:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45e0f3: cmp dword ptr [ebx], 1 */
	if (!m->zf) goto L_45e101;	/* 45e0f6: jne 0x45e101 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 45e0f8: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45e0f9: push edi */
	m->ecx = m->esi;	/* 45e0fa: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x45e101u; native_call(m, 0x4580b0u);	/* 45e0fc: call 0x4580b0 */
L_45e101:
	m->eax = M32((DWORD)(m->esi + 0x202e8c8u));	/* 45e101: mov eax, dword ptr [esi + 0x202e8c8] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 45e107: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 45e108: add ebx, 0x8888 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45e10e: cmp edi, eax */
	if (m->sf != m->of) goto L_45e0f3;	/* 45e110: jl 0x45e0f3 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45e112: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45e113: pop ebx */
L_45e114:
	m->ecx = m->esi;	/* 45e114: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x45e11bu; native_call(m, 0x483640u);	/* 45e116: call 0x483640 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xcu)));	/* 45e11b: fld dword ptr [esp + 0xc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20fcd44u));	/* 45e11f: fadd dword ptr [esi + 0x20fcd44] */
	m->edi = M32(m->esp); m->esp += 4;	/* 45e125: pop edi */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 45e126: fcom dword ptr [0x4a9424] */
	MF((DWORD)(m->esi + 0x20fcd44u)) = (float)ST(0);	/* 45e12c: fst dword ptr [esi + 0x20fcd44] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 45e132: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 45e134: test ah, 0x41 */
	if (!m->zf) goto L_45e15e;	/* 45e137: jne 0x45e15e */
	{ long double t = ST(0); FPUSH(t); }	/* 45e139: fld st(0) */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 45e13b: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esi + 0x20fcd40u));	/* 45e140: mov ecx, dword ptr [esi + 0x20fcd40] */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 45e146: mov dword ptr [esp + 8], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x8u)));	/* 45e14a: fild dword ptr [esp + 8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45e14e: add ecx, eax */
	M32((DWORD)(m->esi + 0x20fcd40u)) = m->ecx;	/* 45e150: mov dword ptr [esi + 0x20fcd40], ecx */
	ST(0) = ST(1) - ST(0);	/* 45e156: fsubr st(1) */
	MF((DWORD)(m->esi + 0x20fcd44u)) = (float)ST(0); FPOP();	/* 45e158: fstp dword ptr [esi + 0x20fcd44] */
L_45e15e:
	ST(0) = ST(0); FPOP();	/* 45e15e: fstp st(0) */
L_45e160:
	m->esi = M32(m->esp); m->esp += 4;	/* 45e160: pop esi */
	m->esp += 4 + 4; return;	/* 45e161: ret 4 */
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
