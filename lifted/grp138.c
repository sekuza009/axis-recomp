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

static void lift_41e010(X86 *m);
static void lift_41dfb0(X86 *m);
static void lift_41dfe0(X86 *m);

/* armc_41dfe0 (0x41dfe0), lifted by tools/lift.py */
static void lift_41dfe0(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbc68u));	/* 41dfe0: mov eax, dword ptr [0x4dbc68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41dfe5: test eax, eax */
	if (m->zf) goto L_41dfee;	/* 41dfe7: je 0x41dfee */
	m->esp -= 4; M32(m->esp) = 0x41dfeeu; native_call(m, 0x41d8a0u);	/* 41dfe9: call 0x41d8a0 */
L_41dfee:
	m->eax = M32((DWORD)(0x4dd078u));	/* 41dfee: mov eax, dword ptr [0x4dd078] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41dff3: test eax, eax */
	if (!m->zf) goto L_41e001;	/* 41dff5: jne 0x41e001 */
	m->esp -= 4; M32(m->esp) = 0x41dffcu; native_call(m, 0x412450u);	/* 41dff7: call 0x412450 */
	native_call(m, 0x419160u); return;	/* 41dffc: jmp 0x419160 */
L_41e001:
	m->esp += 4 + 0; return;	/* 41e001: ret  */
}

/* armc_41e010 (0x41e010), lifted by tools/lift.py */
static void lift_41e010(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbc68u));	/* 41e010: mov eax, dword ptr [0x4dbc68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e015: test eax, eax */
	if (m->zf) goto L_41e01e;	/* 41e017: je 0x41e01e */
	m->esp -= 4; M32(m->esp) = 0x41e01eu; native_call(m, 0x41d600u);	/* 41e019: call 0x41d600 */
L_41e01e:
	m->eax = M32((DWORD)(0x4dd078u));	/* 41e01e: mov eax, dword ptr [0x4dd078] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e023: test eax, eax */
	if (!m->zf) goto L_41e031;	/* 41e025: jne 0x41e031 */
	m->esp -= 4; M32(m->esp) = 0x41e02cu; native_call(m, 0x412450u);	/* 41e027: call 0x412450 */
	native_call(m, 0x41a280u); return;	/* 41e02c: jmp 0x41a280 */
L_41e031:
	m->esp += 4 + 0; return;	/* 41e031: ret  */
}

/* armc_41dfb0 (0x41dfb0), lifted by tools/lift.py */
static void lift_41dfb0(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbc68u));	/* 41dfb0: mov eax, dword ptr [0x4dbc68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41dfb5: test eax, eax */
	if (m->zf) goto L_41dfbe;	/* 41dfb7: je 0x41dfbe */
	m->esp -= 4; M32(m->esp) = 0x41dfbeu; native_call(m, 0x41d600u);	/* 41dfb9: call 0x41d600 */
L_41dfbe:
	{ DWORD a_ = M32((DWORD)(0x4dc24cu)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41dfbe: cmp dword ptr [0x4dc24c], 3 */
	if (m->zf) goto L_41dfcc;	/* 41dfc5: je 0x41dfcc */
	m->esp -= 4; M32(m->esp) = 0x41dfccu; native_call(m, 0x40d990u);	/* 41dfc7: call 0x40d990 */
L_41dfcc:
	m->eax = M32((DWORD)(0x4dd078u));	/* 41dfcc: mov eax, dword ptr [0x4dd078] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41dfd1: test eax, eax */
	if (!m->zf) goto L_41dfdf;	/* 41dfd3: jne 0x41dfdf */
	m->esp -= 4; M32(m->esp) = 0x41dfdau; native_call(m, 0x412450u);	/* 41dfd5: call 0x412450 */
	native_call(m, 0x412650u); return;	/* 41dfda: jmp 0x412650 */
L_41dfdf:
	m->esp += 4 + 0; return;	/* 41dfdf: ret  */
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
