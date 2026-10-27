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

static void lift_48b200(X86 *m);

/* match_inputState2 (0x48b200), lifted by tools/lift.py */
static void lift_48b200(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b200: sub esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b203: push esi */
	m->esi = m->ecx;	/* 48b204: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b206: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48b207: xor edi, edi */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x233cc28u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b209: cmp dword ptr [esi + 0x233cc28], edi */
	if (!m->zf) goto L_48b216;	/* 48b20f: jne 0x48b216 */
	m->esp -= 4; M32(m->esp) = 0x48b216u; native_call(m, 0x49df10u);	/* 48b211: call 0x49df10 */
L_48b216:
	m->ecx = m->esi;	/* 48b216: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48b21du; { long double r_ = native_call_fp(m, 0x461210u); FPUSH(r_); }	/* 48b218: call 0x461210 */
	ST(0) = ST(0); FPOP();	/* 48b21d: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 48b21f: fld dword ptr [esi + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x233cc34u));	/* 48b222: fadd dword ptr [esi + 0x233cc34] */
	MF((DWORD)(m->esi + 0x233cc34u)) = (float)ST(0);	/* 48b228: fst dword ptr [esi + 0x233cc34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340c90u)));	/* 48b22e: fld dword ptr [esi + 0x2340c90] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 48b234: fadd dword ptr [esi + 0x44] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 48b237: fstp dword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc40u)));	/* 48b23b: fld dword ptr [esi + 0x233cc40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48b241: fcomp dword ptr [0x4a93e8] */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 48b247: mov eax, dword ptr [esp + 8] */
	M32((DWORD)(m->esi + 0x2340c90u)) = m->eax;	/* 48b24b: mov dword ptr [esi + 0x2340c90], eax */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48b251: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48b253: test ah, 0x41 */
	if (!m->zf) goto L_48b27a;	/* 48b256: jne 0x48b27a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233cc40u)));	/* 48b258: fld dword ptr [esi + 0x233cc40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 48b25e: fsub dword ptr [esi + 0x44] */
	MF((DWORD)(m->esi + 0x233cc40u)) = (float)ST(0);	/* 48b261: fst dword ptr [esi + 0x233cc40] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48b267: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48b26d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48b26f: test ah, 1 */
	if (m->zf) goto L_48b27a;	/* 48b272: je 0x48b27a */
	M32((DWORD)(m->esi + 0x233cc40u)) = m->edi;	/* 48b274: mov dword ptr [esi + 0x233cc40], edi */
L_48b27a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2342f02u)));	/* 48b27a: fld dword ptr [esi + 0x2342f02] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48b280: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48b286: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48b288: test ah, 0x41 */
	if (!m->zf) goto L_48b2af;	/* 48b28b: jne 0x48b2af */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2342f02u)));	/* 48b28d: fld dword ptr [esi + 0x2342f02] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 48b293: fsub dword ptr [esi + 0x44] */
	MF((DWORD)(m->esi + 0x2342f02u)) = (float)ST(0);	/* 48b296: fst dword ptr [esi + 0x2342f02] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48b29c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48b2a2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48b2a4: test ah, 1 */
	if (m->zf) goto L_48b2af;	/* 48b2a7: je 0x48b2af */
	M32((DWORD)(m->esi + 0x2342f02u)) = m->edi;	/* 48b2a9: mov dword ptr [esi + 0x2342f02], edi */
L_48b2af:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d39u)));	/* 48b2af: fld dword ptr [esi + 0x2340d39] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48b2b5: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48b2bb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48b2bd: test ah, 0x41 */
	if (!m->zf) goto L_48b2e4;	/* 48b2c0: jne 0x48b2e4 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d39u)));	/* 48b2c2: fld dword ptr [esi + 0x2340d39] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x44u));	/* 48b2c8: fsub dword ptr [esi + 0x44] */
	MF((DWORD)(m->esi + 0x2340d39u)) = (float)ST(0);	/* 48b2cb: fst dword ptr [esi + 0x2340d39] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48b2d1: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48b2d7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48b2d9: test ah, 1 */
	if (m->zf) goto L_48b2e4;	/* 48b2dc: je 0x48b2e4 */
	M32((DWORD)(m->esi + 0x2340d39u)) = m->edi;	/* 48b2de: mov dword ptr [esi + 0x2340d39], edi */
L_48b2e4:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u));	/* 48b2e4: fcom dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48b2ea: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48b2ec: test ah, 0x41 */
	if (!m->zf) goto L_48b36b;	/* 48b2ef: jne 0x48b36b */
	{ long double t = ST(0); FPUSH(t); }	/* 48b2f1: fld st(0) */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48b2f3: call 0x49ec14 */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 48b2f8: mov dword ptr [esp + 0xc], eax */
	m->ecx = M32((DWORD)(m->esi + 0x233cc30u));	/* 48b2fc: mov ecx, dword ptr [esi + 0x233cc30] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 48b302: fild dword ptr [esp + 0xc] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48b306: add ecx, eax */
	M32((DWORD)(m->esi + 0x233cc30u)) = m->ecx;	/* 48b308: mov dword ptr [esi + 0x233cc30], ecx */
	ST(0) = ST(1) - ST(0);	/* 48b30e: fsubr st(1) */
	MF((DWORD)(m->esi + 0x233cc34u)) = (float)ST(0); FPOP();	/* 48b310: fstp dword ptr [esi + 0x233cc34] */
	ST(0) = ST(0); FPOP();	/* 48b316: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 48b318: fld dword ptr [esp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 48b31c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48b322: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48b324: test ah, 0x41 */
	if (!m->zf) goto L_48b34b;	/* 48b327: jne 0x48b34b */
	FPUSH((long double)(int)M32((DWORD)(m->esi + 0x2340c80u)));	/* 48b329: fild dword ptr [esi + 0x2340c80] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 48b32f: fdiv dword ptr [esp + 8] */
	MF((DWORD)(m->esi + 0x2340c88u)) = (float)ST(0); FPOP();	/* 48b333: fstp dword ptr [esi + 0x2340c88] */
	FPUSH((long double)(int)M32((DWORD)(m->esi + 0x2340c84u)));	/* 48b339: fild dword ptr [esi + 0x2340c84] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 48b33f: fdiv dword ptr [esp + 8] */
	MF((DWORD)(m->esi + 0x2340c8cu)) = (float)ST(0); FPOP();	/* 48b343: fstp dword ptr [esi + 0x2340c8c] */
	goto L_48b357;	/* 48b349: jmp 0x48b357 */
L_48b34b:
	M32((DWORD)(m->esi + 0x2340c88u)) = m->edi;	/* 48b34b: mov dword ptr [esi + 0x2340c88], edi */
	M32((DWORD)(m->esi + 0x2340c8cu)) = m->edi;	/* 48b351: mov dword ptr [esi + 0x2340c8c], edi */
L_48b357:
	M32((DWORD)(m->esi + 0x2340c90u)) = m->edi;	/* 48b357: mov dword ptr [esi + 0x2340c90], edi */
	M32((DWORD)(m->esi + 0x2340c80u)) = m->edi;	/* 48b35d: mov dword ptr [esi + 0x2340c80], edi */
	M32((DWORD)(m->esi + 0x2340c84u)) = m->edi;	/* 48b363: mov dword ptr [esi + 0x2340c84], edi */
	goto L_48b36d;	/* 48b369: jmp 0x48b36d */
L_48b36b:
	ST(0) = ST(0); FPOP();	/* 48b36b: fstp st(0) */
L_48b36d:
	m->ecx = m->esi;	/* 48b36d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48b374u; native_call(m, 0x49d290u);	/* 48b36f: call 0x49d290 */
	m->ecx = m->esi;	/* 48b374: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48b37bu; native_call(m, 0x4988e0u);	/* 48b376: call 0x4988e0 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x233cc20u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b37b: cmp dword ptr [esi + 0x233cc20], 2 */
	if (!m->zf) goto L_48b38b;	/* 48b382: jne 0x48b38b */
	m->ecx = m->esi;	/* 48b384: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48b38bu; native_call(m, 0x48b38bu + M32(0x48b387u));	/* 0x4982f0 unless the patch DLL retargets it */	/* 48b386: call 0x4982f0 */
L_48b38b:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432cfu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b38b: cmp dword ptr [esi + 0x23432cf], 1 */
	if (!m->zf) goto L_48b3a1;	/* 48b392: jne 0x48b3a1 */
	m->esp -= 4; M32(m->esp) = 0x48b399u; native_call(m, 0x457310u);	/* 48b394: call 0x457310 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48b399: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48b39a: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 48b39c: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b39d: add esp, 8 */
	m->esp += 4 + 0; return;	/* 48b3a0: ret  */
L_48b3a1:
	m->eax = M32((DWORD)(m->esi + 0x233cc20u));	/* 48b3a1: mov eax, dword ptr [esi + 0x233cc20] */
	m->edi = M32(m->esp); m->esp += 4;	/* 48b3a7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48b3a8: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b3a9: add esp, 8 */
	m->esp += 4 + 0; return;	/* 48b3ac: ret  */
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
