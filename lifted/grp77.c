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

static void lift_40cf80(X86 *m);
static void lift_427830(X86 *m);
static void lift_427880(X86 *m);
static void lift_44f5f0(X86 *m);
static void lift_44f740(X86 *m);
static void lift_4434f0(X86 *m);

/* mainmenu_4434f0 (0x4434f0), lifted by tools/lift.py */
static void lift_4434f0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 4434f0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4434f5: test eax, eax */
	if (m->zf) goto L_44351c;	/* 4434f7: je 0x44351c */
	m->eax = M32((DWORD)(0x9dd914u));	/* 4434f9: mov eax, dword ptr [0x9dd914] */
	m->ecx = M32((DWORD)(0x9dd910u));	/* 4434fe: mov ecx, dword ptr [0x9dd910] */
	m->edx = M32((DWORD)(0x9dd90cu));	/* 443504: mov edx, dword ptr [0x9dd90c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44350a: push eax */
	m->eax = M32((DWORD)(0x9dd908u));	/* 44350b: mov eax, dword ptr [0x9dd908] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443510: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443511: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443512: push eax */
	m->esp -= 4; M32(m->esp) = 0x443518u; native_call(m, 0x428c30u);	/* 443513: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443518: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 44351b: ret  */
L_44351c:
	native_call(m, 0x442e10u); return;	/* 44351c: jmp 0x442e10 */
}

/* lobbyPlayer_draw (0x40cf80), lifted by tools/lift.py */
static void lift_40cf80(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x40cf85u; native_call(m, 0x4091b0u);	/* 40cf80: call 0x4091b0 */
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 40cf85: mov eax, dword ptr [0x4dbb3c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40cf8a: cmp eax, 1 */
	if (m->zf) goto L_40cfc7;	/* 40cf8d: je 0x40cfc7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40cf8f: test eax, eax */
	if (m->zf) goto L_40cfc7;	/* 40cf91: je 0x40cfc7 */
	{ DWORD a_ = M32((DWORD)(0x4db51cu)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40cf93: cmp dword ptr [0x4db51c], 5 */
	if (m->zf) goto L_40cfc7;	/* 40cf9a: je 0x40cfc7 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 40cf9c: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40cfa1: test eax, eax */
	if (m->zf) goto L_40cfc8;	/* 40cfa3: je 0x40cfc8 */
	m->eax = M32((DWORD)(0x4dbb74u));	/* 40cfa5: mov eax, dword ptr [0x4dbb74] */
	m->ecx = M32((DWORD)(0x4dbb70u));	/* 40cfaa: mov ecx, dword ptr [0x4dbb70] */
	m->edx = M32((DWORD)(0x4dbb6cu));	/* 40cfb0: mov edx, dword ptr [0x4dbb6c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40cfb6: push eax */
	m->eax = M32((DWORD)(0x4dbb68u));	/* 40cfb7: mov eax, dword ptr [0x4dbb68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cfbc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40cfbd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40cfbe: push eax */
	m->esp -= 4; M32(m->esp) = 0x40cfc4u; native_call(m, 0x428c30u);	/* 40cfbf: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40cfc4: add esp, 0x10 */
L_40cfc7:
	m->esp += 4 + 0; return;	/* 40cfc7: ret  */
L_40cfc8:
	native_call(m, 0x409bc0u); return;	/* 40cfc8: jmp 0x409bc0 */
}

/* setup_427830 (0x427830), lifted by tools/lift.py */
static void lift_427830(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x427835u; native_call(m, 0x423e50u);	/* 427830: call 0x423e50 */
	m->eax = M32((DWORD)(0x4ddcecu));	/* 427835: mov eax, dword ptr [0x4ddcec] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42783a: cmp eax, 1 */
	if (m->zf) goto L_42787a;	/* 42783d: je 0x42787a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42783f: test eax, eax */
	if (m->zf) goto L_42787a;	/* 427841: je 0x42787a */
	{ DWORD a_ = M32((DWORD)(0x4ddac8u)), b_ = 0x29au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 427843: cmp dword ptr [0x4ddac8], 0x29a */
	if (m->zf) goto L_42787a;	/* 42784d: je 0x42787a */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 42784f: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 427854: test eax, eax */
	if (m->zf) goto L_42787b;	/* 427856: je 0x42787b */
	m->eax = M32((DWORD)(0x4ddadcu));	/* 427858: mov eax, dword ptr [0x4ddadc] */
	m->ecx = M32((DWORD)(0x4ddad8u));	/* 42785d: mov ecx, dword ptr [0x4ddad8] */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 427863: mov edx, dword ptr [0x4ddad4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427869: push eax */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 42786a: mov eax, dword ptr [0x4ddad0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42786f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427870: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427871: push eax */
	m->esp -= 4; M32(m->esp) = 0x427877u; native_call(m, 0x428c30u);	/* 427872: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427877: add esp, 0x10 */
L_42787a:
	m->esp += 4 + 0; return;	/* 42787a: ret  */
L_42787b:
	native_call(m, 0x424810u); return;	/* 42787b: jmp 0x424810 */
}

/* setup_427880 (0x427880), lifted by tools/lift.py */
static void lift_427880(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x427885u; native_call(m, 0x423e50u);	/* 427880: call 0x423e50 */
	m->eax = M32((DWORD)(0x4ddcecu));	/* 427885: mov eax, dword ptr [0x4ddcec] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42788a: cmp eax, 1 */
	if (m->zf) goto L_4278ca;	/* 42788d: je 0x4278ca */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42788f: test eax, eax */
	if (m->zf) goto L_4278ca;	/* 427891: je 0x4278ca */
	{ DWORD a_ = M32((DWORD)(0x4ddac8u)), b_ = 0x29au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 427893: cmp dword ptr [0x4ddac8], 0x29a */
	if (m->zf) goto L_4278ca;	/* 42789d: je 0x4278ca */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 42789f: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4278a4: test eax, eax */
	if (m->zf) goto L_4278cb;	/* 4278a6: je 0x4278cb */
	m->eax = M32((DWORD)(0x4ddddcu));	/* 4278a8: mov eax, dword ptr [0x4ddddc] */
	m->ecx = M32((DWORD)(0x4dddd8u));	/* 4278ad: mov ecx, dword ptr [0x4dddd8] */
	m->edx = M32((DWORD)(0x4dddd4u));	/* 4278b3: mov edx, dword ptr [0x4dddd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4278b9: push eax */
	m->eax = M32((DWORD)(0x4dddd0u));	/* 4278ba: mov eax, dword ptr [0x4dddd0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4278bf: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4278c0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4278c1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4278c7u; native_call(m, 0x428c30u);	/* 4278c2: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4278c7: add esp, 0x10 */
L_4278ca:
	m->esp += 4 + 0; return;	/* 4278ca: ret  */
L_4278cb:
	native_call(m, 0x425460u); return;	/* 4278cb: jmp 0x425460 */
}

/* profile_44f5f0 (0x44f5f0), lifted by tools/lift.py */
static void lift_44f5f0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f5f0: push ecx */
	m->eax = M32((DWORD)(0x76d42cu));	/* 44f5f1: mov eax, dword ptr [0x76d42c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f5f6: test eax, eax */
	if (m->zf) goto L_44f686;	/* 44f5f8: je 0x44f686 */
	m->eax = M32((DWORD)(0x67ef34u));	/* 44f5fe: mov eax, dword ptr [0x67ef34] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44f603: push esi */
	m->esi = M32((DWORD)(0x4ded68u));	/* 44f604: mov esi, dword ptr [0x4ded68] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44f60a: sub eax, esi */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 44f60c: mov dword ptr [esp + 4], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 44f610: fild dword ptr [esp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44f614: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 44f61a: fmul dword ptr [0x4a941c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44f620: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x67fb38u));	/* 44f625: mov ecx, dword ptr [0x67fb38] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44f62b: add esi, eax */
	M32((DWORD)(0x4ded68u)) = m->esi;	/* 44f62d: mov dword ptr [0x4ded68], esi */
	m->esi = M32((DWORD)(0x4ded6cu));	/* 44f633: mov esi, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44f639: sub ecx, esi */
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 44f63b: mov dword ptr [esp + 4], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 44f63f: fild dword ptr [esp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44f643: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a941cu));	/* 44f649: fmul dword ptr [0x4a941c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44f64f: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bc0u)));	/* 44f654: fld dword ptr [0x680bc0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44f65a: fsub dword ptr [0x4b071c] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44f660: add esi, eax */
	M32((DWORD)(0x4ded6cu)) = m->esi;	/* 44f662: mov dword ptr [0x4ded6c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f668: pop esi */
	MF((DWORD)(0x680bc0u)) = (float)ST(0);	/* 44f669: fst dword ptr [0x680bc0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 44f66f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44f675: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44f677: test ah, 1 */
	if (m->zf) goto L_44f686;	/* 44f67a: je 0x44f686 */
	M32((DWORD)(0x76d42cu)) = 0x0u;	/* 44f67c: mov dword ptr [0x76d42c], 0 */
L_44f686:
	m->esp -= 4; M32(m->esp) = 0x44f68bu; native_call(m, 0x44d720u);	/* 44f686: call 0x44d720 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 44f68b: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f690: test eax, eax */
	if (m->zf) goto L_44f6b9;	/* 44f692: je 0x44f6b9 */
	m->edx = M32((DWORD)(0x9f8f28u));	/* 44f694: mov edx, dword ptr [0x9f8f28] */
	m->eax = M32((DWORD)(0x9f8f2cu));	/* 44f69a: mov eax, dword ptr [0x9f8f2c] */
	m->ecx = M32((DWORD)(0x9f8f0cu));	/* 44f69f: mov ecx, dword ptr [0x9f8f0c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f6a5: push edx */
	m->edx = M32((DWORD)(0x9f8f1cu));	/* 44f6a6: mov edx, dword ptr [0x9f8f1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f6ac: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f6ad: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f6ae: push edx */
	m->esp -= 4; M32(m->esp) = 0x44f6b4u; native_call(m, 0x428c30u);	/* 44f6af: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f6b4: add esp, 0x10 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44f6b7: pop ecx */
	m->esp += 4 + 0; return;	/* 44f6b8: ret  */
L_44f6b9:
	m->esp -= 4; M32(m->esp) = 0x44f6beu; native_call(m, 0x44e180u);	/* 44f6b9: call 0x44e180 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44f6be: pop ecx */
	m->esp += 4 + 0; return;	/* 44f6bf: ret  */
}

/* profile_44f740 (0x44f740), lifted by tools/lift.py */
static void lift_44f740(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f740: push ecx */
	m->eax = M32((DWORD)(0x76d42cu));	/* 44f741: mov eax, dword ptr [0x76d42c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f746: test eax, eax */
	if (m->zf) goto L_44f7d6;	/* 44f748: je 0x44f7d6 */
	m->eax = M32((DWORD)(0x67ef34u));	/* 44f74e: mov eax, dword ptr [0x67ef34] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44f753: push esi */
	m->esi = M32((DWORD)(0x4ded68u));	/* 44f754: mov esi, dword ptr [0x4ded68] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44f75a: sub eax, esi */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 44f75c: mov dword ptr [esp + 4], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 44f760: fild dword ptr [esp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44f764: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 44f76a: fmul dword ptr [0x4a94f8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44f770: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x67fb38u));	/* 44f775: mov ecx, dword ptr [0x67fb38] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44f77b: add esi, eax */
	M32((DWORD)(0x4ded68u)) = m->esi;	/* 44f77d: mov dword ptr [0x4ded68], esi */
	m->esi = M32((DWORD)(0x4ded6cu));	/* 44f783: mov esi, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44f789: sub ecx, esi */
	M32((DWORD)(m->esp + 0x4u)) = m->ecx;	/* 44f78b: mov dword ptr [esp + 4], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4u)));	/* 44f78f: fild dword ptr [esp + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44f793: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f8u));	/* 44f799: fmul dword ptr [0x4a94f8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44f79f: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bc0u)));	/* 44f7a4: fld dword ptr [0x680bc0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44f7aa: fsub dword ptr [0x4b071c] */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44f7b0: add esi, eax */
	M32((DWORD)(0x4ded6cu)) = m->esi;	/* 44f7b2: mov dword ptr [0x4ded6c], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f7b8: pop esi */
	MF((DWORD)(0x680bc0u)) = (float)ST(0);	/* 44f7b9: fst dword ptr [0x680bc0] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 44f7bf: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44f7c5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44f7c7: test ah, 1 */
	if (m->zf) goto L_44f7d6;	/* 44f7ca: je 0x44f7d6 */
	M32((DWORD)(0x76d42cu)) = 0x0u;	/* 44f7cc: mov dword ptr [0x76d42c], 0 */
L_44f7d6:
	m->esp -= 4; M32(m->esp) = 0x44f7dbu; native_call(m, 0x44d720u);	/* 44f7d6: call 0x44d720 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 44f7db: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f7e0: test eax, eax */
	if (m->zf) goto L_44f809;	/* 44f7e2: je 0x44f809 */
	m->edx = M32((DWORD)(0x9f93c0u));	/* 44f7e4: mov edx, dword ptr [0x9f93c0] */
	m->eax = M32((DWORD)(0x9f93bcu));	/* 44f7ea: mov eax, dword ptr [0x9f93bc] */
	m->ecx = M32((DWORD)(0x9f683cu));	/* 44f7ef: mov ecx, dword ptr [0x9f683c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f7f5: push edx */
	m->edx = M32((DWORD)(0x9f6834u));	/* 44f7f6: mov edx, dword ptr [0x9f6834] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f7fc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f7fd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f7fe: push edx */
	m->esp -= 4; M32(m->esp) = 0x44f804u; native_call(m, 0x428c30u);	/* 44f7ff: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f804: add esp, 0x10 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44f807: pop ecx */
	m->esp += 4 + 0; return;	/* 44f808: ret  */
L_44f809:
	m->esp -= 4; M32(m->esp) = 0x44f80eu; native_call(m, 0x44e3e0u);	/* 44f809: call 0x44e3e0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 44f80e: pop ecx */
	m->esp += 4 + 0; return;	/* 44f80f: ret  */
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
