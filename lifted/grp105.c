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

static void lift_4012c0(X86 *m);
static void lift_4012e0(X86 *m);
static void lift_401460(X86 *m);
static void lift_4013a0(X86 *m);
static void lift_401490(X86 *m);
static void lift_467b70(X86 *m);
static void lift_401410(X86 *m);
static void lift_401310(X86 *m);

/* input_initKeyboard (0x401310), lifted by tools/lift.py */
static void lift_401310(X86 *m)
{
	m->eax = M32((DWORD)(0x4d1fa8u));	/* 401310: mov eax, dword ptr [0x4d1fa8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401315: test eax, eax */
	if (m->zf) goto L_40131f;	/* 401317: je 0x40131f */
	m->eax = 0x1u;	/* 401319: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 40131e: ret  */
L_40131f:
	m->eax = M32((DWORD)(0x4d1e98u));	/* 40131f: mov eax, dword ptr [0x4d1e98] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 401324: push 0 */
	{ DWORD v_ = 0x4d1fa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 401326: push 0x4d1fa0 */
	{ DWORD v_ = 0x4a9688u; m->esp -= 4; M32(m->esp) = v_; }	/* 40132b: push 0x4a9688 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 401330: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401332: push eax */
	m->esp -= 4; M32(m->esp) = 0x401336u; native_call(m, M32((DWORD)(m->ecx + 0xcu)));	/* 401333: call dword ptr [ecx + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401336: test eax, eax */
	if (m->sf == m->of) goto L_40133d;	/* 401338: jge 0x40133d */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40133a: xor eax, eax */
	m->esp += 4 + 0; return;	/* 40133c: ret  */
L_40133d:
	m->eax = M32((DWORD)(0x4d1fa0u));	/* 40133d: mov eax, dword ptr [0x4d1fa0] */
	{ DWORD v_ = 0x4a95f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 401342: push 0x4a95f8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401347: push eax */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 401348: mov edx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x40134du; native_call(m, M32((DWORD)(m->edx + 0x2cu)));	/* 40134a: call dword ptr [edx + 0x2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40134d: test eax, eax */
	if (m->sf == m->of) goto L_401354;	/* 40134f: jge 0x401354 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 401351: xor eax, eax */
	m->esp += 4 + 0; return;	/* 401353: ret  */
L_401354:
	m->eax = M32((DWORD)(0x4d1fa0u));	/* 401354: mov eax, dword ptr [0x4d1fa0] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 401359: mov edx, dword ptr [esp + 4] */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 40135d: push 6 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40135f: push edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 401360: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401362: push eax */
	m->esp -= 4; M32(m->esp) = 0x401366u; native_call(m, M32((DWORD)(m->ecx + 0x34u)));	/* 401363: call dword ptr [ecx + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401366: test eax, eax */
	if (m->sf == m->of) goto L_40136d;	/* 401368: jge 0x40136d */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40136a: xor eax, eax */
	m->esp += 4 + 0; return;	/* 40136c: ret  */
L_40136d:
	m->eax = M32((DWORD)(0x4d1fa0u));	/* 40136d: mov eax, dword ptr [0x4d1fa0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401372: push eax */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 401373: mov ecx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x401378u; native_call(m, M32((DWORD)(m->ecx + 0x1cu)));	/* 401375: call dword ptr [ecx + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401378: test eax, eax */
	goto L_40137f;	/* 40137a: jmp 0x40137f */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40137c: xor eax, eax */
	m->esp += 4 + 0; return;	/* 40137e: ret  */
L_40137f:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40137f: push edi */
	m->ecx = 0x100u;	/* 401380: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 401385: xor eax, eax */
	m->edi = 0x4d1a98u;	/* 401387: mov edi, 0x4d1a98 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 40138c: rep stosd dword ptr es:[edi], eax */
	m->eax = 0x1u;	/* 40138e: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 401393: pop edi */
	M32((DWORD)(0x4d1fa8u)) = m->eax;	/* 401394: mov dword ptr [0x4d1fa8], eax */
	m->esp += 4 + 0; return;	/* 401399: ret  */
}

/* input_reacquireKeyboard (0x4012c0), lifted by tools/lift.py */
static void lift_4012c0(X86 *m)
{
	m->eax = M32((DWORD)(0x4d1fa0u));	/* 4012c0: mov eax, dword ptr [0x4d1fa0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4012c5: test eax, eax */
	if (m->zf) goto L_4012d9;	/* 4012c7: je 0x4012d9 */
	m->ecx = M32((DWORD)(0x4d1fa8u));	/* 4012c9: mov ecx, dword ptr [0x4d1fa8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4012cf: test ecx, ecx */
	if (m->zf) goto L_4012d9;	/* 4012d1: je 0x4012d9 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4012d3: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4012d5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4012d9u; native_call(m, M32((DWORD)(m->ecx + 0x1cu)));	/* 4012d6: call dword ptr [ecx + 0x1c] */
L_4012d9:
	m->esp += 4 + 0; return;	/* 4012d9: ret  */
}

/* input_reacquireMouse (0x4012e0), lifted by tools/lift.py */
static void lift_4012e0(X86 *m)
{
	m->eax = M32((DWORD)(0x4d1fa4u));	/* 4012e0: mov eax, dword ptr [0x4d1fa4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4012e5: test eax, eax */
	if (!m->zf) goto L_4012ea;	/* 4012e7: jne 0x4012ea */
	m->esp += 4 + 0; return;	/* 4012e9: ret  */
L_4012ea:
	m->ecx = M32((DWORD)(0x4ad17cu));	/* 4012ea: mov ecx, dword ptr [0x4ad17c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4012f0: test ecx, ecx */
	if (m->zf) goto L_401300;	/* 4012f2: je 0x401300 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4012f4: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4012f6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4012fau; native_call(m, M32((DWORD)(m->ecx + 0x1cu)));	/* 4012f7: call dword ptr [ecx + 0x1c] */
	m->eax = 0x1u;	/* 4012fa: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 4012ff: ret  */
L_401300:
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 401300: mov edx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401302: push eax */
	m->esp -= 4; M32(m->esp) = 0x401306u; native_call(m, M32((DWORD)(m->edx + 0x20u)));	/* 401303: call dword ptr [edx + 0x20] */
	m->eax = 0x1u;	/* 401306: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 40130b: ret  */
}

/* input_releaseKeyboard (0x401460), lifted by tools/lift.py */
static void lift_401460(X86 *m)
{
	m->eax = M32((DWORD)(0x4d1fa0u));	/* 401460: mov eax, dword ptr [0x4d1fa0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401465: test eax, eax */
	if (m->zf) goto L_401484;	/* 401467: je 0x401484 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 401469: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40146b: push eax */
	m->esp -= 4; M32(m->esp) = 0x40146fu; native_call(m, M32((DWORD)(m->ecx + 0x20u)));	/* 40146c: call dword ptr [ecx + 0x20] */
	m->eax = M32((DWORD)(0x4d1fa0u));	/* 40146f: mov eax, dword ptr [0x4d1fa0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401474: push eax */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 401475: mov edx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x40147au; native_call(m, M32((DWORD)(m->edx + 0x8u)));	/* 401477: call dword ptr [edx + 8] */
	M32((DWORD)(0x4d1fa0u)) = 0x0u;	/* 40147a: mov dword ptr [0x4d1fa0], 0 */
L_401484:
	M32((DWORD)(0x4d1fa8u)) = 0x0u;	/* 401484: mov dword ptr [0x4d1fa8], 0 */
	m->esp += 4 + 0; return;	/* 40148e: ret  */
}

/* input_4013a0 (0x4013a0), lifted by tools/lift.py */
static void lift_4013a0(X86 *m)
{
	m->eax = M32((DWORD)(0x4d1facu));	/* 4013a0: mov eax, dword ptr [0x4d1fac] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4013a5: test eax, eax */
	if (m->zf) goto L_4013af;	/* 4013a7: je 0x4013af */
	m->eax = 0x1u;	/* 4013a9: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 4013ae: ret  */
L_4013af:
	m->eax = M32((DWORD)(0x4d1e98u));	/* 4013af: mov eax, dword ptr [0x4d1e98] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4013b4: push 0 */
	{ DWORD v_ = 0x4d1fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4013b6: push 0x4d1fa4 */
	{ DWORD v_ = 0x4a9698u; m->esp -= 4; M32(m->esp) = v_; }	/* 4013bb: push 0x4a9698 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4013c0: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4013c2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4013c6u; native_call(m, M32((DWORD)(m->ecx + 0xcu)));	/* 4013c3: call dword ptr [ecx + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4013c6: test eax, eax */
	if (m->sf == m->of) goto L_4013cd;	/* 4013c8: jge 0x4013cd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4013ca: xor eax, eax */
	m->esp += 4 + 0; return;	/* 4013cc: ret  */
L_4013cd:
	m->eax = M32((DWORD)(0x4d1fa4u));	/* 4013cd: mov eax, dword ptr [0x4d1fa4] */
	{ DWORD v_ = 0x4a9610u; m->esp -= 4; M32(m->esp) = v_; }	/* 4013d2: push 0x4a9610 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4013d7: push eax */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 4013d8: mov edx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x4013ddu; native_call(m, M32((DWORD)(m->edx + 0x2cu)));	/* 4013da: call dword ptr [edx + 0x2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4013dd: test eax, eax */
	if (m->sf == m->of) goto L_4013e4;	/* 4013df: jge 0x4013e4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4013e1: xor eax, eax */
	m->esp += 4 + 0; return;	/* 4013e3: ret  */
L_4013e4:
	m->eax = M32((DWORD)(0x4d1fa4u));	/* 4013e4: mov eax, dword ptr [0x4d1fa4] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 4013e9: mov edx, dword ptr [esp + 4] */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 4013ed: push 5 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4013ef: push edx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4013f0: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4013f2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4013f6u; native_call(m, M32((DWORD)(m->ecx + 0x34u)));	/* 4013f3: call dword ptr [ecx + 0x34] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4013f6: test eax, eax */
	if (m->sf == m->of) goto L_4013fd;	/* 4013f8: jge 0x4013fd */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4013fa: xor eax, eax */
	m->esp += 4 + 0; return;	/* 4013fc: ret  */
L_4013fd:
	m->eax = 0x1u;	/* 4013fd: mov eax, 1 */
	M32((DWORD)(0x4d1facu)) = m->eax;	/* 401402: mov dword ptr [0x4d1fac], eax */
	m->esp += 4 + 0; return;	/* 401407: ret  */
}

/* wnd_401490 (0x401490), lifted by tools/lift.py */
static void lift_401490(X86 *m)
{
	m->eax = M32((DWORD)(0x4d1fa4u));	/* 401490: mov eax, dword ptr [0x4d1fa4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401495: test eax, eax */
	if (m->zf) goto L_4014b4;	/* 401497: je 0x4014b4 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 401499: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40149b: push eax */
	m->esp -= 4; M32(m->esp) = 0x40149fu; native_call(m, M32((DWORD)(m->ecx + 0x20u)));	/* 40149c: call dword ptr [ecx + 0x20] */
	m->eax = M32((DWORD)(0x4d1fa4u));	/* 40149f: mov eax, dword ptr [0x4d1fa4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4014a4: push eax */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 4014a5: mov edx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x4014aau; native_call(m, M32((DWORD)(m->edx + 0x8u)));	/* 4014a7: call dword ptr [edx + 8] */
	M32((DWORD)(0x4d1fa4u)) = 0x0u;	/* 4014aa: mov dword ptr [0x4d1fa4], 0 */
L_4014b4:
	M32((DWORD)(0x4d1facu)) = 0x0u;	/* 4014b4: mov dword ptr [0x4d1fac], 0 */
	m->esp += 4 + 0; return;	/* 4014be: ret  */
}

/* wnd_467b70 (0x467b70), lifted by tools/lift.py */
static void lift_467b70(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e804u));	/* 467b70: mov eax, dword ptr [0xa0e804] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 467b75: test eax, eax */
	if (m->zf) goto L_467b89;	/* 467b77: je 0x467b89 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 467b79: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 467b7b: push eax */
	m->esp -= 4; M32(m->esp) = 0x467b7fu; native_call(m, M32((DWORD)(m->ecx + 0x8u)));	/* 467b7c: call dword ptr [ecx + 8] */
	M32((DWORD)(0xa0e804u)) = 0x0u;	/* 467b7f: mov dword ptr [0xa0e804], 0 */
L_467b89:
	m->esp += 4 + 0; return;	/* 467b89: ret  */
}

/* input_createDirectInput (0x401410), lifted by tools/lift.py */
static void lift_401410(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 401410: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 401414: push esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 401415: push 0 */
	{ DWORD v_ = 0x4d1e98u; m->esp -= 4; M32(m->esp) = v_; }	/* 401417: push 0x4d1e98 */
	{ DWORD v_ = 0x700u; m->esp -= 4; M32(m->esp) = v_; }	/* 40141c: push 0x700 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401421: push eax */
	m->esp -= 4; M32(m->esp) = 0x401427u; native_call(m, 0x4509c0u);	/* 401422: call 0x4509c0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401427: test eax, eax */
	if (m->sf == m->of) goto L_40142f;	/* 401429: jge 0x40142f */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40142b: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 40142d: pop esi */
	m->esp += 4 + 0; return;	/* 40142e: ret  */
L_40142f:
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 40142f: mov esi, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 401433: push esi */
	m->esp -= 4; M32(m->esp) = 0x401439u; lift_401310(m);	/* 401434: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401439: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40143c: test eax, eax */
	if (!m->zf) goto L_401442;	/* 40143e: jne 0x401442 */
	m->esi = M32(m->esp); m->esp += 4;	/* 401440: pop esi */
	m->esp += 4 + 0; return;	/* 401441: ret  */
L_401442:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 401442: push esi */
	m->esp -= 4; M32(m->esp) = 0x401448u; lift_4013a0(m);	/* 401443: call 0x4013a0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401448: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 40144b: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 40144d: sbb eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 40144f: pop esi */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 401450: neg eax */
	m->esp += 4 + 0; return;	/* 401452: ret  */
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
