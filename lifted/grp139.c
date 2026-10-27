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

static void lift_41e040(X86 *m);

/* menuState700_armCenter (0x41e040), lifted by tools/lift.py */
static void lift_41e040(X86 *m)
{
	m->eax = M32((DWORD)(0x4dc868u));	/* 41e040: mov eax, dword ptr [0x4dc868] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e045: test eax, eax */
	if (m->zf) goto L_41e057;	/* 41e047: je 0x41e057 */
	{ DWORD a_ = M32((DWORD)(0x4dc24cu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e049: cmp dword ptr [0x4dc24c], 2 */
	if (m->zf) goto L_41e057;	/* 41e050: je 0x41e057 */
	m->esp -= 4; M32(m->esp) = 0x41e057u; native_call(m, 0x441740u);	/* 41e052: call 0x441740 */
L_41e057:
	{ DWORD a_ = M32((DWORD)(0x4dc790u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e057: cmp dword ptr [0x4dc790], 2 */
	if (m->zf) goto L_41e07c;	/* 41e05e: je 0x41e07c */
	{ DWORD a_ = M32((DWORD)(0x4dc24cu)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e060: cmp dword ptr [0x4dc24c], 3 */
	if (!m->zf) goto L_41e06e;	/* 41e067: jne 0x41e06e */
	m->esp -= 4; M32(m->esp) = 0x41e06eu; native_call(m, 0x411ab0u);	/* 41e069: call 0x411ab0 */
L_41e06e:
	{ DWORD a_ = M32((DWORD)(0x4dc24cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e06e: cmp dword ptr [0x4dc24c], 1 */
	if (!m->zf) goto L_41e07c;	/* 41e075: jne 0x41e07c */
	m->esp -= 4; M32(m->esp) = 0x41e07cu; native_call(m, 0x411110u);	/* 41e077: call 0x411110 */
L_41e07c:
	m->esp -= 4; M32(m->esp) = 0x41e081u; native_call(m, 0x410b50u);	/* 41e07c: call 0x410b50 */
	m->eax = M32((DWORD)(0x4dc790u));	/* 41e081: mov eax, dword ptr [0x4dc790] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e086: cmp eax, 1 */
	if (m->zf) goto L_41e25e;	/* 41e089: je 0x41e25e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e08f: test eax, eax */
	if (m->zf) goto L_41e25e;	/* 41e091: je 0x41e25e */
	m->ecx = M32((DWORD)(0x90d1c4u));	/* 41e097: mov ecx, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e09d: test ecx, ecx */
	if (m->zf) goto L_41e0c4;	/* 41e09f: je 0x41e0c4 */
	m->eax = M32((DWORD)(0x4dcc9cu));	/* 41e0a1: mov eax, dword ptr [0x4dcc9c] */
	m->ecx = M32((DWORD)(0x4dcc98u));	/* 41e0a6: mov ecx, dword ptr [0x4dcc98] */
	m->edx = M32((DWORD)(0x4dcc94u));	/* 41e0ac: mov edx, dword ptr [0x4dcc94] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0b2: push eax */
	m->eax = M32((DWORD)(0x4dcc90u));	/* 41e0b3: mov eax, dword ptr [0x4dcc90] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0b8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0b9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0ba: push eax */
	m->esp -= 4; M32(m->esp) = 0x41e0c0u; native_call(m, 0x428c30u);	/* 41e0bb: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e0c0: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 41e0c3: ret  */
L_41e0c4:
	m->ecx = M32((DWORD)(0x4dc86cu));	/* 41e0c4: mov ecx, dword ptr [0x4dc86c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e0ca: test ecx, ecx */
	if (m->zf) goto L_41e137;	/* 41e0cc: je 0x41e137 */
	m->ecx = M32((DWORD)(0x4dc54cu));	/* 41e0ce: mov ecx, dword ptr [0x4dc54c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e0d4: test ecx, ecx */
	if (!m->zf) goto L_41e137;	/* 41e0d6: jne 0x41e137 */
	m->esp -= 4; M32(m->esp) = 0x41e0ddu; native_call(m, 0x40e5d0u);	/* 41e0d8: call 0x40e5d0 */
	m->ecx = M32((DWORD)(0x4dcb20u));	/* 41e0dd: mov ecx, dword ptr [0x4dcb20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0e3: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0e4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41e0ebu; native_call(m, 0x41ca50u);	/* 41e0e6: call 0x41ca50 */
	m->edx = M32((DWORD)(0x4dcb24u));	/* 41e0eb: mov edx, dword ptr [0x4dcb24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0f1: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0f2: push 1 */
	m->esp -= 4; M32(m->esp) = 0x41e0f9u; native_call(m, 0x41ca50u);	/* 41e0f4: call 0x41ca50 */
	m->eax = M32((DWORD)(0x4dcb28u));	/* 41e0f9: mov eax, dword ptr [0x4dcb28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0fe: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e0ff: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41e106u; native_call(m, 0x41ca50u);	/* 41e101: call 0x41ca50 */
	m->ecx = M32((DWORD)(0x4dcb2cu));	/* 41e106: mov ecx, dword ptr [0x4dcb2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e10c: push ecx */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e10d: push 3 */
	m->esp -= 4; M32(m->esp) = 0x41e114u; native_call(m, 0x41ca50u);	/* 41e10f: call 0x41ca50 */
	m->edx = M32((DWORD)(0x4dcb18u));	/* 41e114: mov edx, dword ptr [0x4dcb18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e11a: push edx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e11b: push 4 */
	m->esp -= 4; M32(m->esp) = 0x41e122u; native_call(m, 0x41ca50u);	/* 41e11d: call 0x41ca50 */
	m->eax = M32((DWORD)(0x4dcb1cu));	/* 41e122: mov eax, dword ptr [0x4dcb1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41e127: push eax */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e128: push 5 */
	m->esp -= 4; M32(m->esp) = 0x41e12fu; native_call(m, 0x41ca50u);	/* 41e12a: call 0x41ca50 */
	m->eax = M32((DWORD)(0x4dc790u));	/* 41e12f: mov eax, dword ptr [0x4dc790] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e134: add esp, 0x30 */
L_41e137:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e137: cmp eax, 2 */
	if (!m->zf) goto L_41e154;	/* 41e13a: jne 0x41e154 */
	m->eax = M32((DWORD)(0x4dcf10u));	/* 41e13c: mov eax, dword ptr [0x4dcf10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e141: test eax, eax */
	if (!m->zf) goto L_41e154;	/* 41e143: jne 0x41e154 */
	m->esp -= 4; M32(m->esp) = 0x41e14au; native_call(m, 0x41b300u);	/* 41e145: call 0x41b300 */
	m->esp -= 4; M32(m->esp) = 0x41e14fu; native_call(m, 0x41b710u);	/* 41e14a: call 0x41b710 */
	m->esp -= 4; M32(m->esp) = 0x41e154u; native_call(m, 0x41b400u);	/* 41e14f: call 0x41b400 */
L_41e154:
	m->esp -= 4; M32(m->esp) = 0x41e159u; native_call(m, 0x41dcf0u);	/* 41e154: call 0x41dcf0 */
	m->eax = M32((DWORD)(0x4dc798u));	/* 41e159: mov eax, dword ptr [0x4dc798] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41e15e: dec eax */
	if (m->zf) goto L_41e175;	/* 41e15f: je 0x41e175 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41e161: dec eax */
	if (m->zf) goto L_41e16e;	/* 41e162: je 0x41e16e */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 41e164: dec eax */
	if (!m->zf) goto L_41e17a;	/* 41e165: jne 0x41e17a */
	m->esp -= 4; M32(m->esp) = 0x41e16cu; native_call(m, 0x41e010u);	/* 41e167: call 0x41e010 */
	goto L_41e17a;	/* 41e16c: jmp 0x41e17a */
L_41e16e:
	m->esp -= 4; M32(m->esp) = 0x41e173u; native_call(m, 0x41dfe0u);	/* 41e16e: call 0x41dfe0 */
	goto L_41e17a;	/* 41e173: jmp 0x41e17a */
L_41e175:
	m->esp -= 4; M32(m->esp) = 0x41e17au; native_call(m, 0x41dfb0u);	/* 41e175: call 0x41dfb0 */
L_41e17a:
	m->eax = M32((DWORD)(0x4dbc68u));	/* 41e17a: mov eax, dword ptr [0x4dbc68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e17f: test eax, eax */
	if (m->zf) goto L_41e195;	/* 41e181: je 0x41e195 */
	m->esp -= 4; M32(m->esp) = 0x41e188u; native_call(m, 0x41dab0u);	/* 41e183: call 0x41dab0 */
	m->eax = M32((DWORD)(0x4dbc68u));	/* 41e188: mov eax, dword ptr [0x4dbc68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e18d: test eax, eax */
	if (!m->zf) goto L_41e22f;	/* 41e18f: jne 0x41e22f */
L_41e195:
	m->eax = M32((DWORD)(0x4dc54cu));	/* 41e195: mov eax, dword ptr [0x4dc54c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41e19a: test eax, eax */
	if (!m->zf) goto L_41e22f;	/* 41e19c: jne 0x41e22f */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1a2: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1a7: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1ac: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1b1: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1b6: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x41e1c0u; native_call(m, 0x41f0e0u);	/* 41e1bb: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1c0: push 1 */
	{ DWORD v_ = 0x118u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1c2: push 0x118 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1c7: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1cc: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1d1: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x41e1d8u; native_call(m, 0x427970u);	/* 41e1d3: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1d8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1dd: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1df: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1e4: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1e9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x41e1f3u; native_call(m, 0x41f0e0u);	/* 41e1ee: call 0x41f0e0 */
	{ DWORD v_ = 0x7572a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1f3: push 0x7572a4 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1f8: push 0x217 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 41e1fd: push 0xdc */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e202: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x41e209u; native_call(m, 0x4029d0u);	/* 41e204: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e209: add esp, 0x4c */
	{ DWORD v_ = 0x757324u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e20c: push 0x757324 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e211: push 0x217 */
	{ DWORD v_ = 0xf4u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e216: push 0xf4 */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 41e21b: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x41e222u; native_call(m, 0x4029d0u);	/* 41e21d: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e222: add esp, 0x10 */
	M32((DWORD)(0x4dc86cu)) = 0x1u;	/* 41e225: mov dword ptr [0x4dc86c], 1 */
L_41e22f:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 41e22f: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 41e235: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4dcfd8u));	/* 41e23b: fsubr dword ptr [0x4dcfd8] */
	MF((DWORD)(0x4dcfd8u)) = (float)ST(0);	/* 41e241: fst dword ptr [0x4dcfd8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94a8u)); FPOP();	/* 41e247: fcomp dword ptr [0x4a94a8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 41e24d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 41e24f: test ah, 1 */
	if (m->zf) goto L_41e25e;	/* 41e252: je 0x41e25e */
	M32((DWORD)(0x4dcfd8u)) = 0xc0000000u;	/* 41e254: mov dword ptr [0x4dcfd8], 0xc0000000 */
L_41e25e:
	m->esp += 4 + 0; return;	/* 41e25e: ret  */
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
