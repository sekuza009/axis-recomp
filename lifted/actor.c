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

static void lift_46c1c0(X86 *m);
static void lift_46c100(X86 *m);
static void lift_46c140(X86 *m);

/* actor_46c140 (0x46c140), lifted by tools/lift.py */
static void lift_46c140(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 46c140: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c144: push eax */
	m->esp -= 4; M32(m->esp) = 0x46c14au; lift_46c100(m);	/* 46c145: call 0x46c100 */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 46c14a: mov ecx, dword ptr [esp + 8] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 46c14e: fstp dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c152: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46c158u; lift_46c100(m);	/* 46c153: call 0x46c100 */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 46c158: fstp dword ptr [esp + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 46c15c: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0xcu)); FPOP();	/* 46c160: fcomp dword ptr [esp + 0xc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c164: add esp, 8 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c167: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c169: test ah, 0x41 */
	if (!m->zf) goto L_46c194;	/* 46c16c: jne 0x46c194 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 46c16e: fld dword ptr [esp + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4u));	/* 46c172: fsub dword ptr [esp + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa288u));	/* 46c176: fcom dword ptr [0x4aa288] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c17c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c17e: test ah, 0x41 */
	if (!m->zf) goto L_46c1b7;	/* 46c181: jne 0x46c1b7 */
	ST(0) = ST(0); FPOP();	/* 46c183: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4u)));	/* 46c185: fld dword ptr [esp + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 46c189: fadd dword ptr [0x4a94c8] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 46c18f: fsubr dword ptr [esp + 8] */
	m->esp += 4 + 0; return;	/* 46c193: ret  */
L_46c194:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4u)));	/* 46c194: fld dword ptr [esp + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 46c198: fsub dword ptr [esp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa288u)); FPOP();	/* 46c19c: fcomp dword ptr [0x4aa288] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 46c1a2: fld dword ptr [esp + 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c1a6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c1a8: test ah, 0x41 */
	if (!m->zf) goto L_46c1b3;	/* 46c1ab: jne 0x46c1b3 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 46c1ad: fadd dword ptr [0x4a94c8] */
L_46c1b3:
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4u));	/* 46c1b3: fsub dword ptr [esp + 4] */
L_46c1b7:
	m->esp += 4 + 0; return;	/* 46c1b7: ret  */
}

/* actor_46c1c0 (0x46c1c0), lifted by tools/lift.py */
static void lift_46c1c0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 46c1c0: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46c1c4: push eax */
	m->esp -= 4; M32(m->esp) = 0x46c1cau; lift_46c100(m);	/* 46c1c5: call 0x46c100 */
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 46c1ca: mov ecx, dword ptr [esp + 8] */
	MF((DWORD)(m->esp + 0xcu)) = (float)ST(0); FPOP();	/* 46c1ce: fstp dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c1d2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46c1d8u; lift_46c100(m);	/* 46c1d3: call 0x46c100 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 46c1d8: fld dword ptr [esp + 0x10] */
	FCOM(ST(0), ST(1)); FPOP();	/* 46c1dc: fcomp st(1) */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c1de: add esp, 8 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c1e1: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c1e3: test ah, 0x41 */
	if (!m->zf) goto L_46c223;	/* 46c1e6: jne 0x46c223 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 46c1e8: fld dword ptr [esp + 8] */
	ST(0) = ST(0) - ST(1);	/* 46c1ec: fsub st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa288u));	/* 46c1ee: fcom dword ptr [0x4aa288] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c1f4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c1f6: test ah, 0x41 */
	if (!m->zf) goto L_46c25e;	/* 46c1f9: jne 0x46c25e */
	ST(0) = ST(0); FPOP();	/* 46c1fb: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 46c1fd: fld dword ptr [esp + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 46c201: fsub dword ptr [0x4a94c8] */
	ST(0) = ST(0) - ST(1);	/* 46c207: fsub st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 46c209: fmul dword ptr [esp + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46c20d: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 46c20f: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c215: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c217: test ah, 1 */
	if (m->zf) goto L_46c264;	/* 46c21a: je 0x46c264 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 46c21c: fadd dword ptr [0x4a94c8] */
	m->esp += 4 + 0; return;	/* 46c222: ret  */
L_46c223:
	{ long double t = ST(0); FPUSH(t); }	/* 46c223: fld st(0) */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 46c225: fsub dword ptr [esp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa288u)); FPOP();	/* 46c229: fcomp dword ptr [0x4aa288] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 46c22f: fld dword ptr [esp + 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c233: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c235: test ah, 0x41 */
	if (!m->zf) goto L_46c25c;	/* 46c238: jne 0x46c25c */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 46c23a: fadd dword ptr [0x4a94c8] */
	ST(0) = ST(0) - ST(1);	/* 46c240: fsub st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 46c242: fmul dword ptr [esp + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46c246: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94c8u));	/* 46c248: fcom dword ptr [0x4a94c8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c24e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c250: test ah, 1 */
	if (!m->zf) goto L_46c264;	/* 46c253: jne 0x46c264 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 46c255: fsub dword ptr [0x4a94c8] */
	m->esp += 4 + 0; return;	/* 46c25b: ret  */
L_46c25c:
	ST(0) = ST(0) - ST(1);	/* 46c25c: fsub st(1) */
L_46c25e:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0xcu));	/* 46c25e: fmul dword ptr [esp + 0xc] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 46c262: faddp st(1) */
L_46c264:
	m->esp += 4 + 0; return;	/* 46c264: ret  */
}

/* FUN_0046c100 (0x46c100), lifted by tools/lift.py */
static void lift_46c100(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c100: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 46c101: fld dword ptr [esp + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa284u));	/* 46c105: fmul dword ptr [0x4aa284] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 46c10b: call 0x49ec14 */
	M32((DWORD)(m->esp + 0x0u)) = m->eax;	/* 46c110: mov dword ptr [esp], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x0u)));	/* 46c114: fild dword ptr [esp] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 46c118: fmul dword ptr [0x4a94c8] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 46c11e: fsubr dword ptr [esp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 46c122: fcom dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 46c128: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46c12a: test ah, 1 */
	if (m->zf) goto L_46c135;	/* 46c12d: je 0x46c135 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 46c12f: fadd dword ptr [0x4a94c8] */
L_46c135:
	m->ecx = M32(m->esp); m->esp += 4;	/* 46c135: pop ecx */
	m->esp += 4 + 0; return;	/* 46c136: ret  */
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
