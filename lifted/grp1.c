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

static void lift_47d320(X86 *m);
static void lift_487c80(X86 *m);
static void lift_487ba0(X86 *m);
static void lift_487c30(X86 *m);
static void lift_4548b0(X86 *m);
static void lift_454650(X86 *m);
static void lift_4545b0(X86 *m);
static void lift_41f050(X86 *m);
static void lift_41b300(X86 *m);
static void lift_43f640(X86 *m);
static void lift_490b30(X86 *m);
static void lift_490da0(X86 *m);
static void lift_4732f0(X86 *m);
static void lift_42c9f0(X86 *m);
static void lift_40e7a0(X86 *m);
static void lift_42e080(X86 *m);
static void lift_45ebc0(X86 *m);
static void lift_435770(X86 *m);
static void lift_42c6f0(X86 *m);
static void lift_40f340(X86 *m);
static void lift_47d2f0(X86 *m);

/* skel_ase_47d2f0 (0x47d2f0), lifted by tools/lift.py */
static void lift_47d2f0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 47d2f0: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47d2f4: sub esp, 0x10 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 47d2f7: push esi */
	m->esi = m->ecx;	/* 47d2f8: mov esi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47d2fa: push eax */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 47d2fb: lea ecx, [esp + 8] */
	m->esp -= 4; M32(m->esp) = 0x47d304u; native_call(m, 0x47d0f0u);	/* 47d2ff: call 0x47d0f0 */
	m->ecx = (DWORD)(m->esp + 0x4u);	/* 47d304: lea ecx, [esp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47d308: push ecx */
	m->ecx = m->esi;	/* 47d309: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x47d310u; native_call(m, 0x47d260u);	/* 47d30b: call 0x47d260 */
	m->esi = M32(m->esp); m->esp += 4;	/* 47d310: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47d311: add esp, 0x10 */
	m->esp += 4 + 4; return;	/* 47d314: ret 4 */
}

/* skel_ase_47d320 (0x47d320), lifted by tools/lift.py */
static void lift_47d320(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 47d320: mov eax, dword ptr [esp + 8] */
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47d324: sub esp, 0xc0 */
	m->ecx = (DWORD)(m->esp + 0x0u);	/* 47d32a: lea ecx, [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47d32e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47d32f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x47d335u; native_call(m, 0x47d9a0u);	/* 47d330: call 0x47d9a0 */
	m->edx = M32((DWORD)(m->esp + 0xd4u));	/* 47d335: mov edx, dword ptr [esp + 0xd4] */
	m->eax = (DWORD)(m->esp + 0x48u);	/* 47d33c: lea eax, [esp + 0x48] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47d340: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47d341: push eax */
	m->esp -= 4; M32(m->esp) = 0x47d347u; native_call(m, 0x47d9a0u);	/* 47d342: call 0x47d9a0 */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 47d347: lea ecx, [esp + 0x50] */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 47d34b: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47d34f: push ecx */
	m->eax = (DWORD)(m->esp + 0x94u);	/* 47d350: lea eax, [esp + 0x94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 47d357: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 47d358: push eax */
	m->esp -= 4; M32(m->esp) = 0x47d35eu; native_call(m, 0x47d380u);	/* 47d359: call 0x47d380 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47d35e: add esp, 0x1c */
	m->ecx = (DWORD)(m->esp + 0x80u);	/* 47d361: lea ecx, [esp + 0x80] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 47d368: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0xc8u));	/* 47d369: mov ecx, dword ptr [esp + 0xc8] */
	m->esp -= 4; M32(m->esp) = 0x47d375u; lift_47d2f0(m);	/* 47d370: call 0x47d2f0 */
	{ DWORD a_ = m->esp, b_ = 0xc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 47d375: add esp, 0xc0 */
	m->esp += 4 + 0; return;	/* 47d37b: ret  */
}

/* input_setCursorPos (0x487c80), lifted by tools/lift.py */
static void lift_487c80(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded18u));	/* 487c80: mov eax, dword ptr [0x4ded18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487c85: test eax, eax */
	if (m->zf) goto L_487c97;	/* 487c87: je 0x487c97 */
	m->esp -= 4; M32(m->esp) = 0x487c8fu; native_call(m, M32(0x4a92fcu));	/* 487c89: call dword ptr [0x4a92fc] */
	{ DWORD a_ = M32((DWORD)(0x4ded18u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487c8f: cmp dword ptr [0x4ded18], eax */
	if (!m->zf) goto L_487ca7;	/* 487c95: jne 0x487ca7 */
L_487c97:
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 487c97: mov eax, dword ptr [esp + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 487c9b: mov ecx, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487c9f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487ca0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x487ca7u; native_call(m, M32(0x4a9304u));	/* 487ca1: call dword ptr [0x4a9304] */
L_487ca7:
	m->esp += 4 + 0; return;	/* 487ca7: ret  */
}

/* input_asyncKeyDown (0x487ba0), lifted by tools/lift.py */
static void lift_487ba0(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded18u));	/* 487ba0: mov eax, dword ptr [0x4ded18] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487ba5: test eax, eax */
	if (m->zf) goto L_487bba;	/* 487ba7: je 0x487bba */
	m->esp -= 4; M32(m->esp) = 0x487bafu; native_call(m, M32(0x4a92fcu));	/* 487ba9: call dword ptr [0x4a92fc] */
	{ DWORD a_ = M32((DWORD)(0x4ded18u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487baf: cmp dword ptr [0x4ded18], eax */
	if (m->zf) goto L_487bba;	/* 487bb5: je 0x487bba */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 487bb7: xor eax, eax */
	m->esp += 4 + 0; return;	/* 487bb9: ret  */
L_487bba:
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 487bba: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487bbe: push eax */
	m->esp -= 4; M32(m->esp) = 0x487bc5u; native_call(m, M32(0x4a92f8u));	/* 487bbf: call dword ptr [0x4a92f8] */
	{ DWORD a_ = (m->eax & 0xffff), r_ = (0u - a_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ != 0; m->of = r_ == (1u << 15); m->eax = (m->eax & 0xffff0000u) | ((r_) & 0xffff); }	/* 487bc5: neg ax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 487bc8: sbb eax, eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 487bca: neg eax */
	m->esp += 4 + 0; return;	/* 487bcc: ret  */
}

/* input_getCursorPos (0x487c30), lifted by tools/lift.py */
static void lift_487c30(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded18u));	/* 487c30: mov eax, dword ptr [0x4ded18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487c35: sub esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487c38: test eax, eax */
	if (m->zf) goto L_487c4a;	/* 487c3a: je 0x487c4a */
	m->esp -= 4; M32(m->esp) = 0x487c42u; native_call(m, M32(0x4a92fcu));	/* 487c3c: call dword ptr [0x4a92fc] */
	{ DWORD a_ = M32((DWORD)(0x4ded18u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487c42: cmp dword ptr [0x4ded18], eax */
	if (!m->zf) goto L_487c69;	/* 487c48: jne 0x487c69 */
L_487c4a:
	m->eax = (DWORD)(m->esp + 0x0u);	/* 487c4a: lea eax, [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487c4e: push eax */
	m->esp -= 4; M32(m->esp) = 0x487c55u; native_call(m, M32(0x4a9300u));	/* 487c4f: call dword ptr [0x4a9300] */
	m->ecx = M32((DWORD)(m->esp + 0x0u));	/* 487c55: mov ecx, dword ptr [esp] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 487c59: mov edx, dword ptr [esp + 4] */
	M32((DWORD)(0xae2f18u)) = m->ecx;	/* 487c5d: mov dword ptr [0xae2f18], ecx */
	M32((DWORD)(0xae2f1cu)) = m->edx;	/* 487c63: mov dword ptr [0xae2f1c], edx */
L_487c69:
	m->eax = 0xae2f18u;	/* 487c69: mov eax, 0xae2f18 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487c6e: add esp, 8 */
	m->esp += 4 + 0; return;	/* 487c71: ret  */
}

/* net_ping (0x4548b0), lifted by tools/lift.py */
static void lift_4548b0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4548b0: sub esp, 0x24 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4548b3: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4548b4: push edi */
	M32((DWORD)(0xa0d798u)) = 0x0u;	/* 4548b5: mov dword ptr [0xa0d798], 0 */
	m->esp -= 4; M32(m->esp) = 0x4548c4u; native_call(m, 0x454e4cu);	/* 4548bf: call 0x454e4c */
	m->esi = m->eax;	/* 4548c4: mov esi, eax */
	m->ecx = 0x9u;	/* 4548c6: mov ecx, 9 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4548cb: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x8u);	/* 4548cd: lea edi, [esp + 8] */
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 4548d1: mov edx, dword ptr [esp + 0x30] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4548d5: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 4548d7: mov eax, dword ptr [esp + 0x34] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 4548db: lea ecx, [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4548df: push eax */
	{ DWORD v_ = 0x24u; m->esp -= 4; M32(m->esp) = v_; }	/* 4548e0: push 0x24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4548e2: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4548e3: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4548e5: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4548e7: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4548e9: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4548ea: push esi */
	M32((DWORD)(m->esp + 0x30u)) = 0xffffffffu;	/* 4548eb: mov dword ptr [esp + 0x30], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x4548f8u; native_call(m, 0x454e46u);	/* 4548f3: call 0x454e46 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4548f8: test eax, eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4548fa: mov eax, dword ptr [esp + 0x10] */
	if (!m->zf) goto L_454917;	/* 4548fe: jne 0x454917 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454900: test eax, eax */
	M32((DWORD)(0xa0d798u)) = m->eax;	/* 454902: mov dword ptr [0xa0d798], eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 454907: push esi */
	if (!m->cf && !m->zf) goto L_45492b;	/* 454908: ja 0x45492b */
	m->esp -= 4; M32(m->esp) = 0x45490fu; native_call(m, 0x454e40u);	/* 45490a: call 0x454e40 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45490f: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454910: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 454912: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454913: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 454916: ret  */
L_454917:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454917: test eax, eax */
	M32((DWORD)(0xa0d798u)) = 0x1u;	/* 454919: mov dword ptr [0xa0d798], 1 */
	if (m->zf) goto L_45492a;	/* 454923: je 0x45492a */
	M32((DWORD)(0xa0d798u)) = m->eax;	/* 454925: mov dword ptr [0xa0d798], eax */
L_45492a:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45492a: push esi */
L_45492b:
	m->esp -= 4; M32(m->esp) = 0x454930u; native_call(m, 0x454e40u);	/* 45492b: call 0x454e40 */
	m->eax = M32((DWORD)(0xa0d798u));	/* 454930: mov eax, dword ptr [0xa0d798] */
	m->edi = M32(m->esp); m->esp += 4;	/* 454935: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 454936: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454937: add esp, 0x24 */
	m->esp += 4 + 0; return;	/* 45493a: ret  */
}

/* net_454650 (0x454650), lifted by tools/lift.py */
static void lift_454650(X86 *m)
{
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 454650: mov ecx, dword ptr [esp + 8] */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 454654: mov edx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454658: xor eax, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45465a: push edx */
	M32((DWORD)(0xa0bf14u)) = m->eax;	/* 45465b: mov dword ptr [0xa0bf14], eax */
	M32((DWORD)(0xa0bf18u)) = m->eax;	/* 454660: mov dword ptr [0xa0bf18], eax */
	M32((DWORD)(0xa0d798u)) = m->eax;	/* 454665: mov dword ptr [0xa0d798], eax */
	M32((DWORD)(m->ecx*4 + 0xa0d384u)) = m->eax;	/* 45466a: mov dword ptr [ecx*4 + 0xa0d384], eax */
	m->esp -= 4; M32(m->esp) = 0x454676u; native_call(m, 0x4547c0u);	/* 454671: call 0x4547c0 */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 454676: push 0x3e8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45467b: push eax */
	m->esp -= 4; M32(m->esp) = 0x454681u; lift_4548b0(m);	/* 45467c: call 0x4548b0 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 454681: xor ecx, ecx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454683: add esp, 0xc */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 454686: cmp ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 454688: sbb eax, eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 45468a: neg eax */
	m->esp += 4 + 0; return;	/* 45468c: ret  */
}

/* net_4545b0 (0x4545b0), lifted by tools/lift.py */
static void lift_4545b0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d79cu));	/* 4545b0: mov eax, dword ptr [0xa0d79c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4545b5: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4545b6: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4545b7: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4545b8: xor esi, esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4545ba: push edi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4545bb: cmp eax, esi */
	M32((DWORD)(0xa0d798u)) = m->esi;	/* 4545bd: mov dword ptr [0xa0d798], esi */
	m->ebp = 0x1u;	/* 4545c3: mov ebp, 1 */
	if (m->zf || m->sf != m->of) goto L_454633;	/* 4545c8: jle 0x454633 */
	m->ebx = 0xa0bf20u;	/* 4545ca: mov ebx, 0xa0bf20 */
L_4545cf:
	{ DWORD a_ = M32((DWORD)(0xa0d7a0u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4545cf: cmp dword ptr [0xa0d7a0], ebp */
	if (m->zf) goto L_454633;	/* 4545d5: je 0x454633 */
	m->edi = m->ebx;	/* 4545d7: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4545d9: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4545dc: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4545de: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4545e0: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4545e2: dec ecx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4545e3: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_454626;	/* 4545e5: jle 0x454626 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4545e7: push esi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4545e8: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4545eeu; lift_454650(m);	/* 4545e9: call 0x454650 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4545ee: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4545f1: test eax, eax */
	if (m->zf) goto L_454614;	/* 4545f3: je 0x454614 */
	m->eax = M32((DWORD)(0xa0d798u));	/* 4545f5: mov eax, dword ptr [0xa0d798] */
	{ DWORD a_ = m->eax, b_ = 0x3e8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4545fa: cmp eax, 0x3e8 */
	if (m->zf || m->sf != m->of) goto L_45460b;	/* 4545ff: jle 0x45460b */
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 454601: sub eax, 0x190 */
	M32((DWORD)(0xa0d798u)) = m->eax;	/* 454606: mov dword ptr [0xa0d798], eax */
L_45460b:
	M32((DWORD)(m->esi*4 + 0xa0d384u)) = m->eax;	/* 45460b: mov dword ptr [esi*4 + 0xa0d384], eax */
	goto L_45461f;	/* 454612: jmp 0x45461f */
L_454614:
	M32((DWORD)(m->esi*4 + 0xa0d384u)) = 0x0u;	/* 454614: mov dword ptr [esi*4 + 0xa0d384], 0 */
L_45461f:
	M32((DWORD)(m->esi*4 + 0xa0bb14u)) = m->ebp;	/* 45461f: mov dword ptr [esi*4 + 0xa0bb14], ebp */
L_454626:
	m->eax = M32((DWORD)(0xa0d79cu));	/* 454626: mov eax, dword ptr [0xa0d79c] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 45462b: inc esi */
	{ DWORD a_ = m->ebx, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 45462c: add ebx, 0x14 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45462f: cmp esi, eax */
	if (m->sf != m->of) goto L_4545cf;	/* 454631: jl 0x4545cf */
L_454633:
	M32((DWORD)(0xa0d7a0u)) = m->ebp;	/* 454633: mov dword ptr [0xa0d7a0], ebp */
	m->esp -= 4; M32(m->esp) = 0x45463eu; native_call(m, 0x454740u);	/* 454639: call 0x454740 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45463e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45463f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 454640: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 454641: pop ebx */
	m->esp += 4 + 0; return;	/* 454642: ret  */
}

/* gfx_setMenuCamera (0x41f050), lifted by tools/lift.py */
static void lift_41f050(X86 *m)
{
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 41f050: fld dword ptr [0x4df02c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f056: push ecx */
	ST(0) = -ST(0);	/* 41f057: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41f059: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df028u)));	/* 41f05c: fld dword ptr [0x4df028] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f062: push ecx */
	ST(0) = -ST(0);	/* 41f063: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41f065: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df024u)));	/* 41f068: fld dword ptr [0x4df024] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41f06e: push ecx */
	ST(0) = -ST(0);	/* 41f06f: fchs  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 41f071: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x41f07au; native_call(m, M32(0x4a9214u));	/* 41f074: call dword ptr [0x4a9214] */
	m->esp -= 4; M32(m->esp) = 0x41f080u; native_call(m, M32(0x4a9218u));	/* 41f07a: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680380u)));	/* 41f080: fld dword ptr [0x680380] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f086: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f088: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f08a: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f08f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f091: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41f093: push 0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f095: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41f098: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68037cu)));	/* 41f09b: fld dword ptr [0x68037c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f0a1: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41f0a4: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680378u)));	/* 41f0a7: fld dword ptr [0x680378] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f0ad: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41f0b0: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 41f0b3: fld dword ptr [0x4df02c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f0b9: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41f0bc: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df028u)));	/* 41f0bf: fld dword ptr [0x4df028] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f0c5: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41f0c8: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df024u)));	/* 41f0cb: fld dword ptr [0x4df024] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41f0d1: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 41f0d4: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x41f0dcu; native_call(m, 0x4509d2u);	/* 41f0d7: call 0x4509d2 */
	m->esp += 4 + 0; return;	/* 41f0dc: ret  */
}

/* armc_41b300 (0x41b300), lifted by tools/lift.py */
static void lift_41b300(X86 *m)
{
	m->eax = M32((DWORD)(0x4dc798u));	/* 41b300: mov eax, dword ptr [0x4dc798] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b305: cmp eax, 1 */
	if (!m->zf) goto L_41b31f;	/* 41b308: jne 0x41b31f */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 41b30a: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b30f: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_41b3ca;	/* 41b312: ja 0x41b3ca */
	switch (m->eax) { case 0: goto L_41b339; case 1: goto L_41b341; case 2: goto L_41b351; case 3: goto L_41b349; case 4: goto L_41b351; case 5: goto L_41b382; default: abort(); }	/* 41b318: jmp dword ptr [eax*4 + 0x41b3cc] */
L_41b31f:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b31f: cmp eax, 3 */
	if (!m->zf) goto L_41b37d;	/* 41b322: jne 0x41b37d */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41b324: mov eax, dword ptr [0x4dc4b0] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b329: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_41b3ca;	/* 41b32c: ja 0x41b3ca */
	switch (m->eax) { case 0: goto L_41b339; case 1: goto L_41b341; case 2: goto L_41b351; case 3: goto L_41b349; case 4: goto L_41b351; case 5: goto L_41b382; default: abort(); }	/* 41b332: jmp dword ptr [eax*4 + 0x41b3e4] */
L_41b339:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9450u)));	/* 41b339: fld dword ptr [0x4a9450] */
	goto L_41b388;	/* 41b33f: jmp 0x41b388 */
L_41b341:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a93f4u)));	/* 41b341: fld dword ptr [0x4a93f4] */
	goto L_41b388;	/* 41b347: jmp 0x41b388 */
L_41b349:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a94a4u)));	/* 41b349: fld dword ptr [0x4a94a4] */
	goto L_41b388;	/* 41b34f: jmp 0x41b388 */
L_41b351:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a94a0u)));	/* 41b351: fld dword ptr [0x4a94a0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 41b357: fsub dword ptr [0x4df028] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 41b35d: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 41b363: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 41b369: fadd dword ptr [0x4df028] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 41b36f: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a949cu)));	/* 41b375: fld dword ptr [0x4a949c] */
	goto L_41b3ac;	/* 41b37b: jmp 0x41b3ac */
L_41b37d:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41b37d: cmp eax, 2 */
	if (!m->zf) goto L_41b3ca;	/* 41b380: jne 0x41b3ca */
L_41b382:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9498u)));	/* 41b382: fld dword ptr [0x4a9498] */
L_41b388:
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 41b388: fsub dword ptr [0x4df028] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 41b38e: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 41b394: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 41b39a: fadd dword ptr [0x4df028] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 41b3a0: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9494u)));	/* 41b3a6: fld dword ptr [0x4a9494] */
L_41b3ac:
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 41b3ac: fsub dword ptr [0x4df02c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 41b3b2: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 41b3b8: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 41b3be: fadd dword ptr [0x4df02c] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 41b3c4: fstp dword ptr [0x4df02c] */
L_41b3ca:
	m->esp += 4 + 0; return;	/* 41b3ca: ret  */
}

/* app_43f640 (0x43f640), lifted by tools/lift.py */
static void lift_43f640(X86 *m)
{
	m->eax = M32((DWORD)(0x83a9c0u));	/* 43f640: mov eax, dword ptr [0x83a9c0] */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43f645: cmp eax, 7 */
	if (!m->cf && !m->zf) goto L_43f742;	/* 43f648: ja 0x43f742 */
	switch (m->eax) { case 0: goto L_43f655; case 1: goto L_43f674; case 2: goto L_43f693; case 3: goto L_43f6b2; case 4: goto L_43f6d1; case 5: goto L_43f6f0; case 6: goto L_43f70f; case 7: goto L_43f72e; default: abort(); }	/* 43f64e: jmp dword ptr [eax*4 + 0x43f750] */
L_43f655:
	m->eax = M32((DWORD)(0x83a9d8u));	/* 43f655: mov eax, dword ptr [0x83a9d8] */
	M32((DWORD)(0x5b1998u)) = 0x280u;	/* 43f65a: mov dword ptr [0x5b1998], 0x280 */
	M32((DWORD)(0x4e045cu)) = 0x1e0u;	/* 43f664: mov dword ptr [0x4e045c], 0x1e0 */
	M32((DWORD)(0x9da494u)) = m->eax;	/* 43f66e: mov dword ptr [0x9da494], eax */
	m->esp += 4 + 0; return;	/* 43f673: ret  */
L_43f674:
	m->eax = M32((DWORD)(0x83a9d8u));	/* 43f674: mov eax, dword ptr [0x83a9d8] */
	M32((DWORD)(0x5b1998u)) = 0x500u;	/* 43f679: mov dword ptr [0x5b1998], 0x500 */
	M32((DWORD)(0x4e045cu)) = 0x2d0u;	/* 43f683: mov dword ptr [0x4e045c], 0x2d0 */
	M32((DWORD)(0x9da494u)) = m->eax;	/* 43f68d: mov dword ptr [0x9da494], eax */
	m->esp += 4 + 0; return;	/* 43f692: ret  */
L_43f693:
	m->eax = M32((DWORD)(0x83a9d8u));	/* 43f693: mov eax, dword ptr [0x83a9d8] */
	M32((DWORD)(0x5b1998u)) = 0x640u;	/* 43f698: mov dword ptr [0x5b1998], 0x640 */
	M32((DWORD)(0x4e045cu)) = 0x384u;	/* 43f6a2: mov dword ptr [0x4e045c], 0x384 */
	M32((DWORD)(0x9da494u)) = m->eax;	/* 43f6ac: mov dword ptr [0x9da494], eax */
	m->esp += 4 + 0; return;	/* 43f6b1: ret  */
L_43f6b2:
	m->eax = M32((DWORD)(0x83a9d8u));	/* 43f6b2: mov eax, dword ptr [0x83a9d8] */
	M32((DWORD)(0x5b1998u)) = 0x780u;	/* 43f6b7: mov dword ptr [0x5b1998], 0x780 */
	M32((DWORD)(0x4e045cu)) = 0x438u;	/* 43f6c1: mov dword ptr [0x4e045c], 0x438 */
	M32((DWORD)(0x9da494u)) = m->eax;	/* 43f6cb: mov dword ptr [0x9da494], eax */
	m->esp += 4 + 0; return;	/* 43f6d0: ret  */
L_43f6d1:
	m->eax = M32((DWORD)(0x83a9d8u));	/* 43f6d1: mov eax, dword ptr [0x83a9d8] */
	M32((DWORD)(0x5b1998u)) = 0xa00u;	/* 43f6d6: mov dword ptr [0x5b1998], 0xa00 */
	M32((DWORD)(0x4e045cu)) = 0x5a0u;	/* 43f6e0: mov dword ptr [0x4e045c], 0x5a0 */
	M32((DWORD)(0x9da494u)) = m->eax;	/* 43f6ea: mov dword ptr [0x9da494], eax */
	m->esp += 4 + 0; return;	/* 43f6ef: ret  */
L_43f6f0:
	m->eax = M32((DWORD)(0x83a9d8u));	/* 43f6f0: mov eax, dword ptr [0x83a9d8] */
	M32((DWORD)(0x5b1998u)) = 0xf00u;	/* 43f6f5: mov dword ptr [0x5b1998], 0xf00 */
	M32((DWORD)(0x4e045cu)) = 0x870u;	/* 43f6ff: mov dword ptr [0x4e045c], 0x870 */
	M32((DWORD)(0x9da494u)) = m->eax;	/* 43f709: mov dword ptr [0x9da494], eax */
	m->esp += 4 + 0; return;	/* 43f70e: ret  */
L_43f70f:
	m->eax = M32((DWORD)(0x83a9d8u));	/* 43f70f: mov eax, dword ptr [0x83a9d8] */
	M32((DWORD)(0x5b1998u)) = 0x400u;	/* 43f714: mov dword ptr [0x5b1998], 0x400 */
	M32((DWORD)(0x4e045cu)) = 0x300u;	/* 43f71e: mov dword ptr [0x4e045c], 0x300 */
	M32((DWORD)(0x9da494u)) = m->eax;	/* 43f728: mov dword ptr [0x9da494], eax */
	m->esp += 4 + 0; return;	/* 43f72d: ret  */
L_43f72e:
	m->eax = M32((DWORD)(0x67eefcu));	/* 43f72e: mov eax, dword ptr [0x67eefc] */
	M32((DWORD)(0x5b1998u)) = m->eax;	/* 43f733: mov dword ptr [0x5b1998], eax */
	m->eax = M32((DWORD)(0x76d430u));	/* 43f738: mov eax, dword ptr [0x76d430] */
	M32((DWORD)(0x4e045cu)) = m->eax;	/* 43f73d: mov dword ptr [0x4e045c], eax */
L_43f742:
	m->eax = M32((DWORD)(0x83a9d8u));	/* 43f742: mov eax, dword ptr [0x83a9d8] */
	M32((DWORD)(0x9da494u)) = m->eax;	/* 43f747: mov dword ptr [0x9da494], eax */
	m->esp += 4 + 0; return;	/* 43f74c: ret  */
}

/* hud_490b30 (0x490b30), lifted by tools/lift.py */
static void lift_490b30(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 490b30: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490b34: push esi */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 490b35: lea edx, [eax + eax*4] */
	m->edx = (DWORD)(m->edx + m->edx*8 + 0x0u);	/* 490b38: lea edx, [edx + edx*8] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 490b3b: shl edx, 2 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 490b3e: sub edx, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + m->edx*4 + 0x131ae50u))) & 0xff) << 0);	/* 490b40: mov al, byte ptr [ecx + edx*4 + 0x131ae50] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490b47: test al, 2 */
	m->edx = (DWORD)(m->ecx + m->edx*4 + 0x131ae44u);	/* 490b49: lea edx, [ecx + edx*4 + 0x131ae44] */
	if (!m->zf) goto L_490c48;	/* 490b50: jne 0x490c48 */
	m->esi = M32((DWORD)(m->edx + 0x27cu));	/* 490b56: mov esi, dword ptr [edx + 0x27c] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 490b5c: test esi, esi */
	if (m->zf) goto L_490c48;	/* 490b5e: je 0x490c48 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2cu)));	/* 490b64: fld dword ptr [esi + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0xa08u));	/* 490b67: fadd dword ptr [ecx + 0xa08] */
	MF((DWORD)(m->esp + 0x8u)) = (float)ST(0); FPOP();	/* 490b6d: fstp dword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x20f3970u)));	/* 490b71: fld dword ptr [ecx + 0x20f3970] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 490b77: fsub dword ptr [esp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x2bcu)); FPOP();	/* 490b7b: fcomp dword ptr [edx + 0x2bc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490b81: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490b83: test ah, 0x41 */
	if (m->zf) goto L_490c48;	/* 490b86: je 0x490c48 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x20f3974u)));	/* 490b8c: fld dword ptr [ecx + 0x20f3974] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 490b92: fsub dword ptr [esp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x2c0u)); FPOP();	/* 490b96: fcomp dword ptr [edx + 0x2c0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490b9c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490b9e: test ah, 0x41 */
	if (m->zf) goto L_490c48;	/* 490ba1: je 0x490c48 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x20f3978u)));	/* 490ba7: fld dword ptr [ecx + 0x20f3978] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x8u));	/* 490bad: fsub dword ptr [esp + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x2c4u)); FPOP();	/* 490bb1: fcomp dword ptr [edx + 0x2c4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490bb7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490bb9: test ah, 0x41 */
	if (m->zf) goto L_490c48;	/* 490bbc: je 0x490c48 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 490bc2: fld dword ptr [esp + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x20f3970u));	/* 490bc6: fadd dword ptr [ecx + 0x20f3970] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x2bcu)); FPOP();	/* 490bcc: fcomp dword ptr [edx + 0x2bc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490bd2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490bd4: test ah, 1 */
	if (!m->zf) goto L_490c48;	/* 490bd7: jne 0x490c48 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 490bd9: fld dword ptr [esp + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x20f3974u));	/* 490bdd: fadd dword ptr [ecx + 0x20f3974] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x2c0u)); FPOP();	/* 490be3: fcomp dword ptr [edx + 0x2c0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490be9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490beb: test ah, 1 */
	if (!m->zf) goto L_490c48;	/* 490bee: jne 0x490c48 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x8u)));	/* 490bf0: fld dword ptr [esp + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x20f3978u));	/* 490bf4: fadd dword ptr [ecx + 0x20f3978] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edx + 0x2c4u)); FPOP();	/* 490bfa: fcomp dword ptr [edx + 0x2c4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 490c00: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 490c02: test ah, 1 */
	if (!m->zf) goto L_490c48;	/* 490c05: jne 0x490c48 */
	m->eax = M32((DWORD)(m->edx + 0x288u));	/* 490c07: mov eax, dword ptr [edx + 0x288] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 490c0d: push 0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 490c0f: push -1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 490c11: push 1 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 490c13: test eax, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 490c15: push 0 */
	m->eax = (DWORD)(m->edx + 0xf4u);	/* 490c17: lea eax, [edx + 0xf4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 490c1d: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 490c1f: push eax */
	if (!m->zf) goto L_490c37;	/* 490c20: jne 0x490c37 */
	m->ecx = M32((DWORD)(m->edx + 0x280u));	/* 490c22: mov ecx, dword ptr [edx + 0x280] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 490c28: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 490c29: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490c2d: push esi */
	m->esp -= 4; M32(m->esp) = 0x490c33u; native_call(m, 0x4853c0u);	/* 490c2e: call 0x4853c0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 490c33: pop esi */
	m->esp += 4 + 8; return;	/* 490c34: ret 8 */
L_490c37:
	m->ecx = M32((DWORD)(m->edx + 0x284u));	/* 490c37: mov ecx, dword ptr [edx + 0x284] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 490c3d: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 490c3e: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490c42: push esi */
	m->esp -= 4; M32(m->esp) = 0x490c48u; native_call(m, 0x4853c0u);	/* 490c43: call 0x4853c0 */
L_490c48:
	m->esi = M32(m->esp); m->esp += 4;	/* 490c48: pop esi */
	m->esp += 4 + 8; return;	/* 490c49: ret 8 */
}

/* hud_490da0 (0x490da0), lifted by tools/lift.py */
static void lift_490da0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490da0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490da1: push edi */
	m->edi = m->ecx;	/* 490da2: mov edi, ecx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 490da4: xor esi, esi */
	m->eax = M32((DWORD)(m->edi + 0x13c9b24u));	/* 490da6: mov eax, dword ptr [edi + 0x13c9b24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 490dac: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_490ddd;	/* 490dae: jle 0x490ddd */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 490db0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 490db1: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 490db2: mov ebp, dword ptr [esp + 0x14] */
	m->ebx = (DWORD)(m->edi + 0x131ae48u);	/* 490db6: lea ebx, [edi + 0x131ae48] */
L_490dbc:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490dbc: cmp dword ptr [ebx], 1 */
	if (!m->zf) goto L_490dca;	/* 490dbf: jne 0x490dca */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 490dc1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490dc2: push esi */
	m->ecx = m->edi;	/* 490dc3: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x490dcau; lift_490b30(m);	/* 490dc5: call 0x490b30 */
L_490dca:
	m->eax = M32((DWORD)(m->edi + 0x13c9b24u));	/* 490dca: mov eax, dword ptr [edi + 0x13c9b24] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 490dd0: inc esi */
	{ DWORD a_ = m->ebx, b_ = 0x2ccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 490dd1: add ebx, 0x2cc */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490dd7: cmp esi, eax */
	if (m->sf != m->of) goto L_490dbc;	/* 490dd9: jl 0x490dbc */
	m->ebp = M32(m->esp); m->esp += 4;	/* 490ddb: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 490ddc: pop ebx */
L_490ddd:
	m->edi = M32(m->esp); m->esp += 4;	/* 490ddd: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 490dde: pop esi */
	m->esp += 4 + 4; return;	/* 490ddf: ret 4 */
}

/* game_setGameTypeFlags (0x4732f0), lifted by tools/lift.py */
static void lift_4732f0(X86 *m)
{
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 4732f0: mov edx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4732f4: xor eax, eax */
	M32((DWORD)(m->ecx + 0x20f3abcu)) = m->eax;	/* 4732f6: mov dword ptr [ecx + 0x20f3abc], eax */
	M32((DWORD)(m->ecx + 0x20f3ac0u)) = m->eax;	/* 4732fc: mov dword ptr [ecx + 0x20f3ac0], eax */
	M32((DWORD)(m->ecx + 0x20f3ac4u)) = m->eax;	/* 473302: mov dword ptr [ecx + 0x20f3ac4], eax */
	M32((DWORD)(m->ecx + 0x20f3ac8u)) = m->eax;	/* 473308: mov dword ptr [ecx + 0x20f3ac8], eax */
	M32((DWORD)(m->ecx + 0x20f3accu)) = m->eax;	/* 47330e: mov dword ptr [ecx + 0x20f3acc], eax */
	M32((DWORD)(m->ecx + 0x20f3ad0u)) = m->eax;	/* 473314: mov dword ptr [ecx + 0x20f3ad0], eax */
	M32((DWORD)(m->ecx + 0x20f3ad4u)) = m->eax;	/* 47331a: mov dword ptr [ecx + 0x20f3ad4], eax */
	M32((DWORD)(m->ecx + 0x20f3ad8u)) = m->eax;	/* 473320: mov dword ptr [ecx + 0x20f3ad8], eax */
	m->eax = (DWORD)(m->edx + 0xffffffffu);	/* 473326: lea eax, [edx - 1] */
	M32((DWORD)(m->ecx + 0x20f3ab8u)) = m->edx;	/* 473329: mov dword ptr [ecx + 0x20f3ab8], edx */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47332f: cmp eax, 0xc */
	if (!m->cf && !m->zf) goto L_47340f;	/* 473332: ja 0x47340f */
	switch (m->eax) { case 0: goto L_47333f; case 1: goto L_47334c; case 2: goto L_473359; case 3: goto L_47336d; case 4: goto L_47337a; case 5: goto L_47338e; case 6: goto L_47339b; case 7: goto L_4733af; case 8: goto L_4733bc; case 9: goto L_4733d0; case 10: goto L_4733dd; case 11: goto L_4733f1; case 12: goto L_4733fe; default: abort(); }	/* 473338: jmp dword ptr [eax*4 + 0x473414] */
L_47333f:
	M32((DWORD)(m->ecx + 0x20f3abcu)) = 0x1u;	/* 47333f: mov dword ptr [ecx + 0x20f3abc], 1 */
	m->esp += 4 + 4; return;	/* 473349: ret 4 */
L_47334c:
	M32((DWORD)(m->ecx + 0x20f3ac0u)) = 0x1u;	/* 47334c: mov dword ptr [ecx + 0x20f3ac0], 1 */
	m->esp += 4 + 4; return;	/* 473356: ret 4 */
L_473359:
	m->eax = 0x1u;	/* 473359: mov eax, 1 */
	M32((DWORD)(m->ecx + 0x20f3abcu)) = m->eax;	/* 47335e: mov dword ptr [ecx + 0x20f3abc], eax */
	M32((DWORD)(m->ecx + 0x20f3ac0u)) = m->eax;	/* 473364: mov dword ptr [ecx + 0x20f3ac0], eax */
	m->esp += 4 + 4; return;	/* 47336a: ret 4 */
L_47336d:
	M32((DWORD)(m->ecx + 0x20f3ac4u)) = 0x1u;	/* 47336d: mov dword ptr [ecx + 0x20f3ac4], 1 */
	m->esp += 4 + 4; return;	/* 473377: ret 4 */
L_47337a:
	m->eax = 0x1u;	/* 47337a: mov eax, 1 */
	M32((DWORD)(m->ecx + 0x20f3abcu)) = m->eax;	/* 47337f: mov dword ptr [ecx + 0x20f3abc], eax */
	M32((DWORD)(m->ecx + 0x20f3ac4u)) = m->eax;	/* 473385: mov dword ptr [ecx + 0x20f3ac4], eax */
	m->esp += 4 + 4; return;	/* 47338b: ret 4 */
L_47338e:
	M32((DWORD)(m->ecx + 0x20f3ac8u)) = 0x1u;	/* 47338e: mov dword ptr [ecx + 0x20f3ac8], 1 */
	m->esp += 4 + 4; return;	/* 473398: ret 4 */
L_47339b:
	m->eax = 0x1u;	/* 47339b: mov eax, 1 */
	M32((DWORD)(m->ecx + 0x20f3abcu)) = m->eax;	/* 4733a0: mov dword ptr [ecx + 0x20f3abc], eax */
	M32((DWORD)(m->ecx + 0x20f3ac8u)) = m->eax;	/* 4733a6: mov dword ptr [ecx + 0x20f3ac8], eax */
	m->esp += 4 + 4; return;	/* 4733ac: ret 4 */
L_4733af:
	M32((DWORD)(m->ecx + 0x20f3accu)) = 0x1u;	/* 4733af: mov dword ptr [ecx + 0x20f3acc], 1 */
	m->esp += 4 + 4; return;	/* 4733b9: ret 4 */
L_4733bc:
	m->eax = 0x1u;	/* 4733bc: mov eax, 1 */
	M32((DWORD)(m->ecx + 0x20f3abcu)) = m->eax;	/* 4733c1: mov dword ptr [ecx + 0x20f3abc], eax */
	M32((DWORD)(m->ecx + 0x20f3accu)) = m->eax;	/* 4733c7: mov dword ptr [ecx + 0x20f3acc], eax */
	m->esp += 4 + 4; return;	/* 4733cd: ret 4 */
L_4733d0:
	M32((DWORD)(m->ecx + 0x20f3ad0u)) = 0x1u;	/* 4733d0: mov dword ptr [ecx + 0x20f3ad0], 1 */
	m->esp += 4 + 4; return;	/* 4733da: ret 4 */
L_4733dd:
	m->eax = 0x1u;	/* 4733dd: mov eax, 1 */
	M32((DWORD)(m->ecx + 0x20f3abcu)) = m->eax;	/* 4733e2: mov dword ptr [ecx + 0x20f3abc], eax */
	M32((DWORD)(m->ecx + 0x20f3ad0u)) = m->eax;	/* 4733e8: mov dword ptr [ecx + 0x20f3ad0], eax */
	m->esp += 4 + 4; return;	/* 4733ee: ret 4 */
L_4733f1:
	M32((DWORD)(m->ecx + 0x20f3ad4u)) = 0x1u;	/* 4733f1: mov dword ptr [ecx + 0x20f3ad4], 1 */
	m->esp += 4 + 4; return;	/* 4733fb: ret 4 */
L_4733fe:
	m->eax = 0x1u;	/* 4733fe: mov eax, 1 */
	M32((DWORD)(m->ecx + 0x20f3abcu)) = m->eax;	/* 473403: mov dword ptr [ecx + 0x20f3abc], eax */
	M32((DWORD)(m->ecx + 0x20f3ad8u)) = m->eax;	/* 473409: mov dword ptr [ecx + 0x20f3ad8], eax */
L_47340f:
	m->esp += 4 + 4; return;	/* 47340f: ret 4 */
}

/* cfg_parseGraphic (0x42c9f0), lifted by tools/lift.py */
static void lift_42c9f0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9f0: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 42c9f1: mov esi, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9f5: push esi */
	{ DWORD v_ = 0x4b1b78u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c9f6: push 0x4b1b78 */
	m->esp -= 4; M32(m->esp) = 0x42ca00u; native_call(m, 0x49f167u);	/* 42c9fb: call 0x49f167 */
	m->eax = M32((DWORD)(0x83a9c0u));	/* 42ca00: mov eax, dword ptr [0x83a9c0] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ca05: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42ca08: cmp eax, 7 */
	if (!m->cf && !m->zf) goto L_42ca5a;	/* 42ca0b: ja 0x42ca5a */
	switch (m->eax) { case 0: goto L_42ca14; case 1: goto L_42ca1c; case 2: goto L_42ca24; case 3: goto L_42ca2c; case 4: goto L_42ca34; case 5: goto L_42ca3c; case 6: goto L_42ca44; case 7: goto L_42ca4c; default: abort(); }	/* 42ca0d: jmp dword ptr [eax*4 + 0x42cb7c] */
L_42ca14:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca14: push esi */
	{ DWORD v_ = 0x4b1b6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca15: push 0x4b1b6c */
	goto L_42ca52;	/* 42ca1a: jmp 0x42ca52 */
L_42ca1c:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca1c: push esi */
	{ DWORD v_ = 0x4ac84cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca1d: push 0x4ac84c */
	goto L_42ca52;	/* 42ca22: jmp 0x42ca52 */
L_42ca24:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca24: push esi */
	{ DWORD v_ = 0x4ac870u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca25: push 0x4ac870 */
	goto L_42ca52;	/* 42ca2a: jmp 0x42ca52 */
L_42ca2c:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca2c: push esi */
	{ DWORD v_ = 0x4ac894u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca2d: push 0x4ac894 */
	goto L_42ca52;	/* 42ca32: jmp 0x42ca52 */
L_42ca34:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca34: push esi */
	{ DWORD v_ = 0x4ac8b8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca35: push 0x4ac8b8 */
	goto L_42ca52;	/* 42ca3a: jmp 0x42ca52 */
L_42ca3c:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca3c: push esi */
	{ DWORD v_ = 0x4ac8dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca3d: push 0x4ac8dc */
	goto L_42ca52;	/* 42ca42: jmp 0x42ca52 */
L_42ca44:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca44: push esi */
	{ DWORD v_ = 0x4ac900u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca45: push 0x4ac900 */
	goto L_42ca52;	/* 42ca4a: jmp 0x42ca52 */
L_42ca4c:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca4c: push esi */
	{ DWORD v_ = 0x4ac920u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca4d: push 0x4ac920 */
L_42ca52:
	m->esp -= 4; M32(m->esp) = 0x42ca57u; native_call(m, 0x49f167u);	/* 42ca52: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ca57: add esp, 8 */
L_42ca5a:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca5a: push esi */
	{ DWORD v_ = 0x4b1b00u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca5b: push 0x4b1b00 */
	m->esp -= 4; M32(m->esp) = 0x42ca65u; native_call(m, 0x49f167u);	/* 42ca60: call 0x49f167 */
	m->eax = M32((DWORD)(0x83a9c4u));	/* 42ca65: mov eax, dword ptr [0x83a9c4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ca6a: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42ca6d: test eax, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca6f: push esi */
	if (!m->zf) goto L_42ca79;	/* 42ca70: jne 0x42ca79 */
	{ DWORD v_ = 0x4b1afcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca72: push 0x4b1afc */
	goto L_42ca7e;	/* 42ca77: jmp 0x42ca7e */
L_42ca79:
	{ DWORD v_ = 0x4b1af8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca79: push 0x4b1af8 */
L_42ca7e:
	m->esp -= 4; M32(m->esp) = 0x42ca83u; native_call(m, 0x49f167u);	/* 42ca7e: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ca83: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca86: push esi */
	{ DWORD v_ = 0x4b1adcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca87: push 0x4b1adc */
	m->esp -= 4; M32(m->esp) = 0x42ca91u; native_call(m, 0x49f167u);	/* 42ca8c: call 0x49f167 */
	m->eax = M32((DWORD)(0x83a9c8u));	/* 42ca91: mov eax, dword ptr [0x83a9c8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42ca96: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42ca99: test eax, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca9b: push esi */
	if (!m->zf) goto L_42caa5;	/* 42ca9c: jne 0x42caa5 */
	{ DWORD v_ = 0x4b1ad4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42ca9e: push 0x4b1ad4 */
	goto L_42caaa;	/* 42caa3: jmp 0x42caaa */
L_42caa5:
	{ DWORD v_ = 0x4b1accu; m->esp -= 4; M32(m->esp) = v_; }	/* 42caa5: push 0x4b1acc */
L_42caaa:
	m->esp -= 4; M32(m->esp) = 0x42caafu; native_call(m, 0x49f167u);	/* 42caaa: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42caaf: add esp, 8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cab2: push edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cab3: push esi */
	{ DWORD v_ = 0x4b1aacu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cab4: push 0x4b1aac */
	m->esp -= 4; M32(m->esp) = 0x42cabeu; native_call(m, 0x49f167u);	/* 42cab9: call 0x49f167 */
	m->eax = M32((DWORD)(0x83a9ccu));	/* 42cabe: mov eax, dword ptr [0x83a9cc] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cac3: add esp, 8 */
	m->edi = 0x1u;	/* 42cac6: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42cacb: cmp eax, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cacd: push esi */
	if (!m->zf) goto L_42cad7;	/* 42cace: jne 0x42cad7 */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cad0: push 0x4b17e4 */
	goto L_42cadc;	/* 42cad5: jmp 0x42cadc */
L_42cad7:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cad7: push 0x4b17dc */
L_42cadc:
	m->esp -= 4; M32(m->esp) = 0x42cae1u; native_call(m, 0x49f167u);	/* 42cadc: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cae1: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cae4: push esi */
	{ DWORD v_ = 0x4b1a94u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cae5: push 0x4b1a94 */
	m->esp -= 4; M32(m->esp) = 0x42caefu; native_call(m, 0x49f167u);	/* 42caea: call 0x49f167 */
	m->eax = M32((DWORD)(0x83a9d0u));	/* 42caef: mov eax, dword ptr [0x83a9d0] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42caf4: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42caf7: cmp eax, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42caf9: push esi */
	if (!m->zf) goto L_42cb03;	/* 42cafa: jne 0x42cb03 */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cafc: push 0x4b17e4 */
	goto L_42cb08;	/* 42cb01: jmp 0x42cb08 */
L_42cb03:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb03: push 0x4b17dc */
L_42cb08:
	m->esp -= 4; M32(m->esp) = 0x42cb0du; native_call(m, 0x49f167u);	/* 42cb08: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cb0d: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb10: push esi */
	{ DWORD v_ = 0x4b1a7cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb11: push 0x4b1a7c */
	m->esp -= 4; M32(m->esp) = 0x42cb1bu; native_call(m, 0x49f167u);	/* 42cb16: call 0x49f167 */
	m->eax = M32((DWORD)(0x83a9d4u));	/* 42cb1b: mov eax, dword ptr [0x83a9d4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cb20: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42cb23: cmp eax, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb25: push esi */
	if (!m->zf) goto L_42cb2f;	/* 42cb26: jne 0x42cb2f */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb28: push 0x4b17e4 */
	goto L_42cb34;	/* 42cb2d: jmp 0x42cb34 */
L_42cb2f:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb2f: push 0x4b17dc */
L_42cb34:
	m->esp -= 4; M32(m->esp) = 0x42cb39u; native_call(m, 0x49f167u);	/* 42cb34: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cb39: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb3c: push esi */
	{ DWORD v_ = 0x4b1a64u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb3d: push 0x4b1a64 */
	m->esp -= 4; M32(m->esp) = 0x42cb47u; native_call(m, 0x49f167u);	/* 42cb42: call 0x49f167 */
	m->eax = M32((DWORD)(0x83a9d8u));	/* 42cb47: mov eax, dword ptr [0x83a9d8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cb4c: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42cb4f: cmp eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 42cb51: pop edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb52: push esi */
	if (!m->zf) goto L_42cb5c;	/* 42cb53: jne 0x42cb5c */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb55: push 0x4b17e4 */
	goto L_42cb61;	/* 42cb5a: jmp 0x42cb61 */
L_42cb5c:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb5c: push 0x4b17dc */
L_42cb61:
	m->esp -= 4; M32(m->esp) = 0x42cb66u; native_call(m, 0x49f167u);	/* 42cb61: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cb66: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb69: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42cb6a: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42cb74u; native_call(m, 0x49f167u);	/* 42cb6f: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42cb74: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42cb77: pop esi */
	m->esp += 4 + 0; return;	/* 42cb78: ret  */
}

/* armc_saveSelection (0x40e7a0), lifted by tools/lift.py */
static void lift_40e7a0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40e7a0: push esi */
	m->esp -= 4; M32(m->esp) = 0x40e7a6u; native_call(m, 0x40d990u);	/* 40e7a1: call 0x40d990 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 40e7a6: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40e7a8: xor eax, eax */
L_40e7aa:
	m->ecx = M32((DWORD)(m->eax + 0x4dc4b8u));	/* 40e7aa: mov ecx, dword ptr [eax + 0x4dc4b8] */
	m->edx = M32((DWORD)(m->eax + 0x4dc4bcu));	/* 40e7b0: mov edx, dword ptr [eax + 0x4dc4bc] */
	M32((DWORD)(m->eax + 0x4dcfe0u)) = m->ecx;	/* 40e7b6: mov dword ptr [eax + 0x4dcfe0], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c0u));	/* 40e7bc: mov ecx, dword ptr [eax + 0x4dc4c0] */
	M32((DWORD)(m->eax + 0x4dcfe4u)) = m->edx;	/* 40e7c2: mov dword ptr [eax + 0x4dcfe4], edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4c4u));	/* 40e7c8: mov edx, dword ptr [eax + 0x4dc4c4] */
	M32((DWORD)(m->eax + 0x4dcfe8u)) = m->ecx;	/* 40e7ce: mov dword ptr [eax + 0x4dcfe8], ecx */
	m->ecx = M32((DWORD)(m->eax + 0x4dc4c8u));	/* 40e7d4: mov ecx, dword ptr [eax + 0x4dc4c8] */
	M32((DWORD)(m->eax + 0x4dcfecu)) = m->edx;	/* 40e7da: mov dword ptr [eax + 0x4dcfec], edx */
	m->edx = M32((DWORD)(m->eax + 0x4dc4ccu));	/* 40e7e0: mov edx, dword ptr [eax + 0x4dc4cc] */
	M32((DWORD)(m->eax + 0x4dcff0u)) = m->ecx;	/* 40e7e6: mov dword ptr [eax + 0x4dcff0], ecx */
	M32((DWORD)(m->eax + 0x4dcff4u)) = m->edx;	/* 40e7ec: mov dword ptr [eax + 0x4dcff4], edx */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40e7f2: add eax, 0x18 */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e7f5: cmp eax, 0x90 */
	if (m->sf != m->of) goto L_40e7aa;	/* 40e7fa: jl 0x40e7aa */
	m->eax = M32((DWORD)(0x4dc760u));	/* 40e7fc: mov eax, dword ptr [0x4dc760] */
	m->ecx = M32((DWORD)(0x4dc764u));	/* 40e801: mov ecx, dword ptr [0x4dc764] */
	m->edx = M32((DWORD)(0x4dc768u));	/* 40e807: mov edx, dword ptr [0x4dc768] */
	M32((DWORD)(0x4dc878u)) = m->eax;	/* 40e80d: mov dword ptr [0x4dc878], eax */
	m->eax = M32((DWORD)(0x4dc76cu));	/* 40e812: mov eax, dword ptr [0x4dc76c] */
	M32((DWORD)(0x4dc87cu)) = m->ecx;	/* 40e817: mov dword ptr [0x4dc87c], ecx */
	m->ecx = M32((DWORD)(0x4dc770u));	/* 40e81d: mov ecx, dword ptr [0x4dc770] */
	M32((DWORD)(0x4dc880u)) = m->edx;	/* 40e823: mov dword ptr [0x4dc880], edx */
	m->edx = M32((DWORD)(0x4dcb20u));	/* 40e829: mov edx, dword ptr [0x4dcb20] */
	M32((DWORD)(0x4dc884u)) = m->eax;	/* 40e82f: mov dword ptr [0x4dc884], eax */
	m->eax = M32((DWORD)(0x4dcb24u));	/* 40e834: mov eax, dword ptr [0x4dcb24] */
	M32((DWORD)(0x4dc888u)) = m->ecx;	/* 40e839: mov dword ptr [0x4dc888], ecx */
	m->ecx = M32((DWORD)(0x4dcb28u));	/* 40e83f: mov ecx, dword ptr [0x4dcb28] */
	M32((DWORD)(0x4dcf20u)) = m->edx;	/* 40e845: mov dword ptr [0x4dcf20], edx */
	m->edx = M32((DWORD)(0x4dcb2cu));	/* 40e84b: mov edx, dword ptr [0x4dcb2c] */
	M32((DWORD)(0x4dcf24u)) = m->eax;	/* 40e851: mov dword ptr [0x4dcf24], eax */
	m->eax = M32((DWORD)(0x4dcb18u));	/* 40e856: mov eax, dword ptr [0x4dcb18] */
	M32((DWORD)(0x4dcf28u)) = m->ecx;	/* 40e85b: mov dword ptr [0x4dcf28], ecx */
	m->ecx = M32((DWORD)(0x4dcb1cu));	/* 40e861: mov ecx, dword ptr [0x4dcb1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40e867: push edi */
	M32((DWORD)(0x4dcf2cu)) = m->edx;	/* 40e868: mov dword ptr [0x4dcf2c], edx */
	M32((DWORD)(0x4dcf18u)) = m->eax;	/* 40e86e: mov dword ptr [0x4dcf18], eax */
	M32((DWORD)(0x4dcf1cu)) = m->ecx;	/* 40e873: mov dword ptr [0x4dcf1c], ecx */
	m->esp -= 4; M32(m->esp) = 0x40e87eu; native_call(m, 0x40d990u);	/* 40e879: call 0x40d990 */
	m->eax = M32((DWORD)(0x4dc760u));	/* 40e87e: mov eax, dword ptr [0x4dc760] */
	m->edi = 0x13u;	/* 40e883: mov edi, 0x13 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e888: cmp eax, edi */
	goto L_40e892;	/* 40e88a: jmp 0x40e892 */
	M32((DWORD)(0x4dc760u)) = m->esi;	/* 40e88c: mov dword ptr [0x4dc760], esi */
L_40e892:
	m->eax = M32((DWORD)(0x4dc764u));	/* 40e892: mov eax, dword ptr [0x4dc764] */
	m->edx = 0xdu;	/* 40e897: mov edx, 0xd */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e89c: cmp eax, edx */
	goto L_40e8a6;	/* 40e89e: jmp 0x40e8a6 */
	M32((DWORD)(0x4dc764u)) = m->esi;	/* 40e8a0: mov dword ptr [0x4dc764], esi */
L_40e8a6:
	m->eax = M32((DWORD)(0x4dc768u));	/* 40e8a6: mov eax, dword ptr [0x4dc768] */
	m->ecx = 0x11u;	/* 40e8ab: mov ecx, 0x11 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e8b0: cmp eax, ecx */
	goto L_40e8ba;	/* 40e8b2: jmp 0x40e8ba */
	M32((DWORD)(0x4dc768u)) = m->esi;	/* 40e8b4: mov dword ptr [0x4dc768], esi */
L_40e8ba:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40e8ba: push ebx */
	m->ebx = M32((DWORD)(0x4dc770u));	/* 40e8bb: mov ebx, dword ptr [0x4dc770] */
	m->eax = 0xfu;	/* 40e8c1: mov eax, 0xf */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e8c6: cmp ebx, eax */
	goto L_40e8d0;	/* 40e8c8: jmp 0x40e8d0 */
	M32((DWORD)(0x4dc770u)) = m->esi;	/* 40e8ca: mov dword ptr [0x4dc770], esi */
L_40e8d0:
	{ DWORD a_ = M32((DWORD)(0x4dc76cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e8d0: cmp dword ptr [0x4dc76c], edi */
	goto L_40e8de;	/* 40e8d6: jmp 0x40e8de */
	M32((DWORD)(0x4dc76cu)) = m->esi;	/* 40e8d8: mov dword ptr [0x4dc76c], esi */
L_40e8de:
	{ DWORD a_ = M32((DWORD)(0x4dc878u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e8de: cmp dword ptr [0x4dc878], edi */
	goto L_40e8ec;	/* 40e8e4: jmp 0x40e8ec */
	M32((DWORD)(0x4dc878u)) = m->esi;	/* 40e8e6: mov dword ptr [0x4dc878], esi */
L_40e8ec:
	m->ebx = M32((DWORD)(0x4dc87cu));	/* 40e8ec: mov ebx, dword ptr [0x4dc87c] */
	{ DWORD a_ = m->ebx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e8f2: cmp ebx, edx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40e8f4: pop ebx */
	goto L_40e8fd;	/* 40e8f5: jmp 0x40e8fd */
	M32((DWORD)(0x4dc87cu)) = m->esi;	/* 40e8f7: mov dword ptr [0x4dc87c], esi */
L_40e8fd:
	{ DWORD a_ = M32((DWORD)(0x4dc880u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e8fd: cmp dword ptr [0x4dc880], ecx */
	goto L_40e90b;	/* 40e903: jmp 0x40e90b */
	M32((DWORD)(0x4dc880u)) = m->esi;	/* 40e905: mov dword ptr [0x4dc880], esi */
L_40e90b:
	{ DWORD a_ = M32((DWORD)(0x4dc888u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e90b: cmp dword ptr [0x4dc888], eax */
	goto L_40e919;	/* 40e911: jmp 0x40e919 */
	M32((DWORD)(0x4dc888u)) = m->esi;	/* 40e913: mov dword ptr [0x4dc888], esi */
L_40e919:
	m->eax = M32((DWORD)(0x4dc884u));	/* 40e919: mov eax, dword ptr [0x4dc884] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40e91e: cmp eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 40e920: pop edi */
	goto L_40e929;	/* 40e921: jmp 0x40e929 */
	M32((DWORD)(0x4dc884u)) = m->esi;	/* 40e923: mov dword ptr [0x4dc884], esi */
L_40e929:
	m->esp -= 4; M32(m->esp) = 0x40e92eu; native_call(m, 0x447010u);	/* 40e929: call 0x447010 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40e92e: pop esi */
	m->esp += 4 + 0; return;	/* 40e92f: ret  */
}

/* cfg_42e080 (0x42e080), lifted by tools/lift.py */
static void lift_42e080(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e080: sub esp, 0x10c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42e086: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x114u));	/* 42e087: mov ebp, dword ptr [esp + 0x114] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42e08e: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42e08f: push edi */
	M32((DWORD)(m->esp + 0xcu)) = 0x0u;	/* 42e090: mov dword ptr [esp + 0xc], 0 */
L_42e098:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42e098: push ebp */
	m->eax = (DWORD)(m->esp + 0x98u);	/* 42e099: lea eax, [esp + 0x98] */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e0a0: push 0x50 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42e0a2: push eax */
	m->esp -= 4; M32(m->esp) = 0x42e0a8u; native_call(m, 0x49ecd7u);	/* 42e0a3: call 0x49ecd7 */
	m->edi = (DWORD)(m->esp + 0xa0u);	/* 42e0a8: lea edi, [esp + 0xa0] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e0af: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e0b2: xor eax, eax */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e0b4: push 0x4ad5dc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e0b9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42e0bb: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42e0bd: dec ecx */
	M8((DWORD)(m->esp + m->ecx*1 + 0xa3u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 42e0be: mov byte ptr [esp + ecx + 0xa3], al */
	m->ecx = (DWORD)(m->esp + 0xa4u);	/* 42e0c5: lea ecx, [esp + 0xa4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e0cc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42e0d2u; native_call(m, 0x49ec3bu);	/* 42e0cd: call 0x49ec3b */
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e0d2: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e0d7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42e0deu; native_call(m, 0x49ec3bu);	/* 42e0d9: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e0de: add esp, 0x1c */
	m->ecx = 0x21u;	/* 42e0e1: mov ecx, 0x21 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e0e6: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x10u);	/* 42e0e8: lea edi, [esp + 0x10] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 42e0ec: rep stosd dword ptr es:[edi], eax */
L_42e0ee:
	{ DWORD v_ = 0x4ad5dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42e0ee: push 0x4ad5dc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e0f3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42e0fau; native_call(m, 0x49ec3bu);	/* 42e0f5: call 0x49ec3b */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e0fa: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e0fd: test eax, eax */
	if (m->zf) goto L_42e12e;	/* 42e0ff: je 0x42e12e */
	m->edi = m->eax;	/* 42e101: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e103: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e106: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42e108: lea edx, [esp + 0x10] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e10c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42e10e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42e110: sub edi, ecx */
	m->esi = m->edi;	/* 42e112: mov esi, edi */
	m->edi = m->edx;	/* 42e114: mov edi, edx */
	m->edx = m->ecx;	/* 42e116: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e118: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42e11b: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 42e11d: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 42e11f: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42e120: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42e123: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42e125: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e127: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 42e12a: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_42e0ee;	/* 42e12c: jmp 0x42e0ee */
L_42e12e:
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 42e12e: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e132: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_42e1fd;	/* 42e135: ja 0x42e1fd */
	switch (m->eax) { case 0: goto L_42e142; case 1: goto L_42e159; case 2: goto L_42e170; case 3: goto L_42e1be; default: abort(); }	/* 42e13b: jmp dword ptr [eax*4 + 0x42e22c] */
L_42e142:
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42e142: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42e146: push eax */
	m->esp -= 4; M32(m->esp) = 0x42e14cu; native_call(m, 0x49ec09u);	/* 42e147: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e14c: add esp, 4 */
	M32((DWORD)(0x4e0c90u)) = m->eax;	/* 42e14f: mov dword ptr [0x4e0c90], eax */
	goto L_42e1fd;	/* 42e154: jmp 0x42e1fd */
L_42e159:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 42e159: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e15d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42e163u; native_call(m, 0x49ec09u);	/* 42e15e: call 0x49ec09 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e163: add esp, 4 */
	M32((DWORD)(0x4e0c94u)) = m->eax;	/* 42e166: mov dword ptr [0x4e0c94], eax */
	goto L_42e1fd;	/* 42e16b: jmp 0x42e1fd */
L_42e170:
	m->esi = 0x4b21bcu;	/* 42e170: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42e175: lea eax, [esp + 0x10] */
L_42e179:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e179: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e17b: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e17d: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e1aa;	/* 42e17f: jne 0x42e1aa */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e181: test cl, cl */
	if (m->zf) goto L_42e199;	/* 42e183: je 0x42e199 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e185: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e188: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e18a: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e1aa;	/* 42e18d: jne 0x42e1aa */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e18f: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e192: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e195: test cl, cl */
	if (!m->zf) goto L_42e179;	/* 42e197: jne 0x42e179 */
L_42e199:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e199: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e19b: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e19d: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e19f: sete cl */
	M32((DWORD)(0x4e0c98u)) = m->ecx;	/* 42e1a2: mov dword ptr [0x4e0c98], ecx */
	goto L_42e1fd;	/* 42e1a8: jmp 0x42e1fd */
L_42e1aa:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e1aa: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e1ac: sbb eax, -1 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e1af: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e1b1: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e1b3: sete cl */
	M32((DWORD)(0x4e0c98u)) = m->ecx;	/* 42e1b6: mov dword ptr [0x4e0c98], ecx */
	goto L_42e1fd;	/* 42e1bc: jmp 0x42e1fd */
L_42e1be:
	m->esi = 0x4b21bcu;	/* 42e1be: mov esi, 0x4b21bc */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 42e1c3: lea eax, [esp + 0x10] */
L_42e1c7:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 42e1c7: mov dl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e1c9: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e1cb: cmp dl, byte ptr [esi] */
	if (!m->zf) goto L_42e1eb;	/* 42e1cd: jne 0x42e1eb */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e1cf: test cl, cl */
	if (m->zf) goto L_42e1e7;	/* 42e1d1: je 0x42e1e7 */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 42e1d3: mov dl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->edx >> 0) & 0xff)) & 0xff) << 0);	/* 42e1d6: mov cl, dl */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42e1d8: cmp dl, byte ptr [esi + 1] */
	if (!m->zf) goto L_42e1eb;	/* 42e1db: jne 0x42e1eb */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42e1dd: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42e1e0: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42e1e3: test cl, cl */
	if (!m->zf) goto L_42e1c7;	/* 42e1e5: jne 0x42e1c7 */
L_42e1e7:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 42e1e7: xor eax, eax */
	goto L_42e1f0;	/* 42e1e9: jmp 0x42e1f0 */
L_42e1eb:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e1eb: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 42e1ed: sbb eax, -1 */
L_42e1f0:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42e1f0: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42e1f2: test eax, eax */
	m->ecx = (m->ecx & ~(0xffu << 0)) | ((((m->zf) ? 1u : 0u) & 0xff) << 0);	/* 42e1f4: sete cl */
	M32((DWORD)(0x4e0c9cu)) = m->ecx;	/* 42e1f7: mov dword ptr [0x4e0c9c], ecx */
L_42e1fd:
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 42e1fd: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 42e201: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42e202: cmp eax, 4 */
	M32((DWORD)(m->esp + 0xcu)) = m->eax;	/* 42e205: mov dword ptr [esp + 0xc], eax */
	if (m->sf != m->of) goto L_42e098;	/* 42e209: jl 0x42e098 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42e20f: push ebp */
	m->edx = (DWORD)(m->esp + 0x98u);	/* 42e210: lea edx, [esp + 0x98] */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 42e217: push 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42e219: push edx */
	m->esp -= 4; M32(m->esp) = 0x42e21fu; native_call(m, 0x49ecd7u);	/* 42e21a: call 0x49ecd7 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e21f: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 42e222: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42e223: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42e224: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42e225: add esp, 0x10c */
	m->esp += 4 + 0; return;	/* 42e22b: ret  */
}

/* actor_45ebc0 (0x45ebc0), lifted by tools/lift.py */
static void lift_45ebc0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 45ebc0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45ebc4: push esi */
	m->edx = m->eax;	/* 45ebc5: mov edx, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 45ebc7: push edi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45ebc8: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45ebcb: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45ebcd: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45ebd0: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 45ebd2: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 45ebd5: add edx, eax */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x1cd93a8u);	/* 45ebd7: lea eax, [ecx + edx*8 + 0x1cd93a8] */
	m->edx = M32((DWORD)(m->ecx + m->edx*8 + 0x1cd94b0u));	/* 45ebde: mov edx, dword ptr [ecx + edx*8 + 0x1cd94b0] */
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ebe5: cmp edx, 1 */
	if (!m->zf) goto L_45ed80;	/* 45ebe8: jne 0x45ed80 */
	m->ecx = M32((DWORD)(m->ecx + 0x20f3ab8u));	/* 45ebee: mov ecx, dword ptr [ecx + 0x20f3ab8] */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45ebf4: add ecx, -2 */
	{ DWORD a_ = m->ecx, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ebf7: cmp ecx, 9 */
	if (!m->cf && !m->zf) goto L_45ed4f;	/* 45ebfa: ja 0x45ed4f */
	switch (m->ecx) { case 0: goto L_45ec07; case 1: goto L_45ec07; case 2: goto L_45ec48; case 3: goto L_45ec48; case 4: goto L_45ec8f; case 5: goto L_45ec8f; case 6: goto L_45ecd6; case 7: goto L_45ecd6; case 8: goto L_45ed1d; case 9: goto L_45ed1d; default: abort(); }	/* 45ec00: jmp dword ptr [ecx*4 + 0x45ed88] */
L_45ec07:
	m->edx = 0xau;	/* 45ec07: mov edx, 0xa */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45ec0c: xor esi, esi */
	M32((DWORD)(m->eax + 0x1cu)) = m->edx;	/* 45ec0e: mov dword ptr [eax + 0x1c], edx */
	M32((DWORD)(m->eax + 0x20u)) = m->edx;	/* 45ec11: mov dword ptr [eax + 0x20], edx */
	M32((DWORD)(m->eax + 0x128u)) = m->edx;	/* 45ec14: mov dword ptr [eax + 0x128], edx */
	M32((DWORD)(m->eax + 0x12cu)) = m->esi;	/* 45ec1a: mov dword ptr [eax + 0x12c], esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45ec20: xor ecx, ecx */
	m->edi = 0x64u;	/* 45ec22: mov edi, 0x64 */
L_45ec27:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ec27: cmp ecx, esi */
	if (!m->zf) goto L_45ec36;	/* 45ec29: jne 0x45ec36 */
	M32((DWORD)(m->eax + 0x28u)) = m->edi;	/* 45ec2b: mov dword ptr [eax + 0x28], edi */
	M32((DWORD)(m->eax + 0x130u)) = m->edx;	/* 45ec2e: mov dword ptr [eax + 0x130], edx */
	goto L_45ec3d;	/* 45ec34: jmp 0x45ec3d */
L_45ec36:
	M32((DWORD)(m->eax + m->ecx*4 + 0x130u)) = m->esi;	/* 45ec36: mov dword ptr [eax + ecx*4 + 0x130], esi */
L_45ec3d:
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45ec3d: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ec3e: cmp ecx, 4 */
	if (m->sf != m->of) goto L_45ec27;	/* 45ec41: jl 0x45ec27 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45ec43: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45ec44: pop esi */
	m->esp += 4 + 4; return;	/* 45ec45: ret 4 */
L_45ec48:
	m->ecx = 0x96u;	/* 45ec48: mov ecx, 0x96 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45ec4d: xor esi, esi */
	M32((DWORD)(m->eax + 0x1cu)) = m->ecx;	/* 45ec4f: mov dword ptr [eax + 0x1c], ecx */
	M32((DWORD)(m->eax + 0x20u)) = m->ecx;	/* 45ec52: mov dword ptr [eax + 0x20], ecx */
	M32((DWORD)(m->eax + 0x128u)) = m->ecx;	/* 45ec55: mov dword ptr [eax + 0x128], ecx */
	M32((DWORD)(m->eax + 0x12cu)) = m->esi;	/* 45ec5b: mov dword ptr [eax + 0x12c], esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45ec61: xor ecx, ecx */
	m->edi = 0x64u;	/* 45ec63: mov edi, 0x64 */
	m->edx = 0x32u;	/* 45ec68: mov edx, 0x32 */
L_45ec6d:
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ec6d: cmp ecx, 1 */
	if (!m->zf) goto L_45ec7d;	/* 45ec70: jne 0x45ec7d */
	M32((DWORD)(m->eax + 0x2cu)) = m->edi;	/* 45ec72: mov dword ptr [eax + 0x2c], edi */
	M32((DWORD)(m->eax + 0x134u)) = m->edx;	/* 45ec75: mov dword ptr [eax + 0x134], edx */
	goto L_45ec84;	/* 45ec7b: jmp 0x45ec84 */
L_45ec7d:
	M32((DWORD)(m->eax + m->ecx*4 + 0x130u)) = m->esi;	/* 45ec7d: mov dword ptr [eax + ecx*4 + 0x130], esi */
L_45ec84:
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45ec84: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ec85: cmp ecx, 4 */
	if (m->sf != m->of) goto L_45ec6d;	/* 45ec88: jl 0x45ec6d */
	m->edi = M32(m->esp); m->esp += 4;	/* 45ec8a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45ec8b: pop esi */
	m->esp += 4 + 4; return;	/* 45ec8c: ret 4 */
L_45ec8f:
	m->ecx = 0x96u;	/* 45ec8f: mov ecx, 0x96 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45ec94: xor esi, esi */
	M32((DWORD)(m->eax + 0x1cu)) = m->ecx;	/* 45ec96: mov dword ptr [eax + 0x1c], ecx */
	M32((DWORD)(m->eax + 0x20u)) = m->ecx;	/* 45ec99: mov dword ptr [eax + 0x20], ecx */
	M32((DWORD)(m->eax + 0x128u)) = m->ecx;	/* 45ec9c: mov dword ptr [eax + 0x128], ecx */
	M32((DWORD)(m->eax + 0x12cu)) = m->esi;	/* 45eca2: mov dword ptr [eax + 0x12c], esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45eca8: xor ecx, ecx */
	m->edi = 0x64u;	/* 45ecaa: mov edi, 0x64 */
	m->edx = 0x32u;	/* 45ecaf: mov edx, 0x32 */
L_45ecb4:
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ecb4: cmp ecx, 2 */
	if (!m->zf) goto L_45ecc4;	/* 45ecb7: jne 0x45ecc4 */
	M32((DWORD)(m->eax + 0x30u)) = m->edi;	/* 45ecb9: mov dword ptr [eax + 0x30], edi */
	M32((DWORD)(m->eax + 0x138u)) = m->edx;	/* 45ecbc: mov dword ptr [eax + 0x138], edx */
	goto L_45eccb;	/* 45ecc2: jmp 0x45eccb */
L_45ecc4:
	M32((DWORD)(m->eax + m->ecx*4 + 0x130u)) = m->esi;	/* 45ecc4: mov dword ptr [eax + ecx*4 + 0x130], esi */
L_45eccb:
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45eccb: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45eccc: cmp ecx, 4 */
	if (m->sf != m->of) goto L_45ecb4;	/* 45eccf: jl 0x45ecb4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45ecd1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45ecd2: pop esi */
	m->esp += 4 + 4; return;	/* 45ecd3: ret 4 */
L_45ecd6:
	m->ecx = 0x96u;	/* 45ecd6: mov ecx, 0x96 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 45ecdb: xor esi, esi */
	M32((DWORD)(m->eax + 0x1cu)) = m->ecx;	/* 45ecdd: mov dword ptr [eax + 0x1c], ecx */
	M32((DWORD)(m->eax + 0x20u)) = m->ecx;	/* 45ece0: mov dword ptr [eax + 0x20], ecx */
	M32((DWORD)(m->eax + 0x128u)) = m->ecx;	/* 45ece3: mov dword ptr [eax + 0x128], ecx */
	M32((DWORD)(m->eax + 0x12cu)) = m->esi;	/* 45ece9: mov dword ptr [eax + 0x12c], esi */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45ecef: xor ecx, ecx */
	m->edi = 0x64u;	/* 45ecf1: mov edi, 0x64 */
	m->edx = 0x32u;	/* 45ecf6: mov edx, 0x32 */
L_45ecfb:
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ecfb: cmp ecx, 3 */
	if (!m->zf) goto L_45ed0b;	/* 45ecfe: jne 0x45ed0b */
	M32((DWORD)(m->eax + 0x34u)) = m->edi;	/* 45ed00: mov dword ptr [eax + 0x34], edi */
	M32((DWORD)(m->eax + 0x13cu)) = m->edx;	/* 45ed03: mov dword ptr [eax + 0x13c], edx */
	goto L_45ed12;	/* 45ed09: jmp 0x45ed12 */
L_45ed0b:
	M32((DWORD)(m->eax + m->ecx*4 + 0x130u)) = m->esi;	/* 45ed0b: mov dword ptr [eax + ecx*4 + 0x130], esi */
L_45ed12:
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 45ed12: inc ecx */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45ed13: cmp ecx, 4 */
	if (m->sf != m->of) goto L_45ecfb;	/* 45ed16: jl 0x45ecfb */
	m->edi = M32(m->esp); m->esp += 4;	/* 45ed18: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45ed19: pop esi */
	m->esp += 4 + 4; return;	/* 45ed1a: ret 4 */
L_45ed1d:
	m->ecx = 0x96u;	/* 45ed1d: mov ecx, 0x96 */
	M32((DWORD)(m->eax + 0x12cu)) = 0x0u;	/* 45ed22: mov dword ptr [eax + 0x12c], 0 */
	M32((DWORD)(m->eax + 0x1cu)) = m->ecx;	/* 45ed2c: mov dword ptr [eax + 0x1c], ecx */
	M32((DWORD)(m->eax + 0x20u)) = m->ecx;	/* 45ed2f: mov dword ptr [eax + 0x20], ecx */
	M32((DWORD)(m->eax + 0x128u)) = m->ecx;	/* 45ed32: mov dword ptr [eax + 0x128], ecx */
	{ DWORD a_ = m->eax, b_ = 0x130u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45ed38: add eax, 0x130 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45ed3d: xor ecx, ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 45ed3f: pop edi */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 45ed40: mov dword ptr [eax], ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 45ed42: pop esi */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 45ed43: mov dword ptr [eax + 4], ecx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 45ed46: mov dword ptr [eax + 8], ecx */
	M32((DWORD)(m->eax + 0xcu)) = m->ecx;	/* 45ed49: mov dword ptr [eax + 0xc], ecx */
	m->esp += 4 + 4; return;	/* 45ed4c: ret 4 */
L_45ed4f:
	m->ecx = M32((DWORD)(m->eax + 0x20u));	/* 45ed4f: mov ecx, dword ptr [eax + 0x20] */
	m->edx = M32((DWORD)(m->eax + 0x1cu));	/* 45ed52: mov edx, dword ptr [eax + 0x1c] */
	M32((DWORD)(m->eax + 0x12cu)) = m->ecx;	/* 45ed55: mov dword ptr [eax + 0x12c], ecx */
	M32((DWORD)(m->eax + 0x128u)) = m->edx;	/* 45ed5b: mov dword ptr [eax + 0x128], edx */
	m->ecx = (DWORD)(m->eax + 0x130u);	/* 45ed61: lea ecx, [eax + 0x130] */
	m->esi = 0x4u;	/* 45ed67: mov esi, 4 */
L_45ed6c:
	m->eax = M32((DWORD)(m->ecx + 0xfffffef8u));	/* 45ed6c: mov eax, dword ptr [ecx - 0x108] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45ed72: add ecx, 4 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 45ed75: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 45ed76: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 45ed78: sar eax, 1 */
	M32((DWORD)(m->ecx + 0xfffffffcu)) = m->eax;	/* 45ed7a: mov dword ptr [ecx - 4], eax */
	{ DWORD a_ = m->esi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->esi = r_; }	/* 45ed7d: dec esi */
	if (!m->zf) goto L_45ed6c;	/* 45ed7e: jne 0x45ed6c */
L_45ed80:
	m->edi = M32(m->esp); m->esp += 4;	/* 45ed80: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45ed81: pop esi */
	m->esp += 4 + 4; return;	/* 45ed82: ret 4 */
}

/* room_435770 (0x435770), lifted by tools/lift.py */
static void lift_435770(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435770: sub esp, 8 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a94ecu)));	/* 435773: fld dword ptr [0x4a94ec] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 435779: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43577a: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43577b: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43577c: push edi */
	M32((DWORD)(m->esp + 0x10u)) = 0x49742400u;	/* 43577d: mov dword ptr [esp + 0x10], 0x49742400 */
	m->edx = 0x9dcef4u;	/* 435785: mov edx, 0x9dcef4 */
	m->ebx = 0x1u;	/* 43578a: mov ebx, 1 */
L_43578f:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43578f: xor esi, esi */
	m->ecx = 0x7u;	/* 435791: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 435796: xor eax, eax */
	m->edi = m->edx;	/* 435798: mov edi, edx */
	M32((DWORD)(m->edx + 0xfffffffcu)) = m->esi;	/* 43579a: mov dword ptr [edx - 4], esi */
	{ DWORD a_ = m->edx, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43579d: add edx, 0x44 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4357a0: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 4357a2: stosw word ptr es:[edi], ax */
	M32((DWORD)(m->edx + 0xffffffdau)) = m->esi;	/* 4357a4: mov dword ptr [edx - 0x26], esi */
	M32((DWORD)(m->edx + 0xffffffeau)) = m->esi;	/* 4357a7: mov dword ptr [edx - 0x16], esi */
	M32((DWORD)(m->edx + 0xffffffdeu)) = m->esi;	/* 4357aa: mov dword ptr [edx - 0x22], esi */
	M32((DWORD)(m->edx + 0xffffffe2u)) = m->esi;	/* 4357ad: mov dword ptr [edx - 0x1e], esi */
	M32((DWORD)(m->edx + 0xffffffe6u)) = m->esi;	/* 4357b0: mov dword ptr [edx - 0x1a], esi */
	M32((DWORD)(m->edx + 0xffffffeeu)) = m->ebx;	/* 4357b3: mov dword ptr [edx - 0x12], ebx */
	{ DWORD a_ = m->edx, b_ = 0x9dd19cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4357b6: cmp edx, 0x9dd19c */
	if (m->sf != m->of) goto L_43578f;	/* 4357bc: jl 0x43578f */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4357be: xor ebp, ebp */
L_4357c0:
	m->ebx = m->ebp;	/* 4357c0: mov ebx, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4357c2: or ecx, 0xffffffff */
	{ DWORD a_ = m->ebx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 4357c5: shl ebx, 5 */
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4357c8: sub ebx, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4357ca: xor eax, eax */
	{ DWORD a_ = m->ebx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 4357cc: shl ebx, 1 */
	m->esi = (DWORD)(m->ebx + 0xa05330u);	/* 4357ce: lea esi, [ebx + 0xa05330] */
	m->edi = m->esi;	/* 4357d4: mov edi, esi */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4357d6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4357d8: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4357da: dec ecx */
	if (m->zf) goto L_435924;	/* 4357db: je 0x435924 */
	m->eax = M32((DWORD)(0x9dd6acu));	/* 4357e1: mov eax, dword ptr [0x9dd6ac] */
	m->edx = m->ebp;	/* 4357e6: mov edx, ebp */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4357e8: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4357eb: add edx, ebp */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4357ed: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4357f0: shl edx, 2 */
	m->ecx = (DWORD)(m->ebp + m->eax*2 + 0x1u);	/* 4357f3: lea ecx, [ebp + eax*2 + 1] */
	m->edi = m->esi;	/* 4357f7: mov edi, esi */
	m->eax = (DWORD)(m->edx + 0x9dcef4u);	/* 4357f9: lea eax, [edx + 0x9dcef4] */
	M32((DWORD)(m->edx + 0x9dcef0u)) = m->ecx;	/* 4357ff: mov dword ptr [edx + 0x9dcef0], ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 435805: mov dword ptr [esp + 0x14], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 435809: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43580c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43580e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 435810: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 435812: sub edi, ecx */
	m->eax = m->ecx;	/* 435814: mov eax, ecx */
	m->esi = m->edi;	/* 435816: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 435818: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43581c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43581f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 435821: mov ecx, eax */
	m->eax = M32((DWORD)(m->ebx + 0xa05366u));	/* 435823: mov eax, dword ptr [ebx + 0xa05366] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 435829: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43582c: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->ebx + 0xa0535eu));	/* 43582e: mov ecx, dword ptr [ebx + 0xa0535e] */
	M32((DWORD)(m->edx + 0x9dcf12u)) = m->ecx;	/* 435834: mov dword ptr [edx + 0x9dcf12], ecx */
	m->ecx = M32((DWORD)(m->ebx + 0xa0536au));	/* 43583a: mov ecx, dword ptr [ebx + 0xa0536a] */
	M32((DWORD)(m->edx + 0x9dcf2au)) = m->eax;	/* 435840: mov dword ptr [edx + 0x9dcf2a], eax */
	m->eax = M32((DWORD)(m->ebx + 0xa05352u));	/* 435846: mov eax, dword ptr [ebx + 0xa05352] */
	M32((DWORD)(m->edx + 0x9dcf22u)) = m->ecx;	/* 43584c: mov dword ptr [edx + 0x9dcf22], ecx */
	m->ecx = M32((DWORD)(m->ebx + 0xa05356u));	/* 435852: mov ecx, dword ptr [ebx + 0xa05356] */
	M32((DWORD)(m->edx + 0x9dcf16u)) = m->eax;	/* 435858: mov dword ptr [edx + 0x9dcf16], eax */
	m->eax = M32((DWORD)(m->ebx + 0xa0535au));	/* 43585e: mov eax, dword ptr [ebx + 0xa0535a] */
	M32((DWORD)(m->edx + 0x9dcf1au)) = m->ecx;	/* 435864: mov dword ptr [edx + 0x9dcf1a], ecx */
	m->ecx = M32((DWORD)(m->ebx + 0xa05362u));	/* 43586a: mov ecx, dword ptr [ebx + 0xa05362] */
	M32((DWORD)(m->edx + 0x9dcf1eu)) = m->eax;	/* 435870: mov dword ptr [edx + 0x9dcf1e], eax */
	M32((DWORD)(m->edx + 0x9dcf26u)) = m->ecx;	/* 435876: mov dword ptr [edx + 0x9dcf26], ecx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43587c: test ebp, ebp */
	if (!m->zf) goto L_435896;	/* 43587e: jne 0x435896 */
	m->eax = M32((DWORD)(0x9dd384u));	/* 435880: mov eax, dword ptr [0x9dd384] */
	m->ecx = M32((DWORD)(0x9dd328u));	/* 435885: mov ecx, dword ptr [0x9dd328] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 43588b: mov dword ptr [esp + 0x10], eax */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43588f: mov eax, dword ptr [0x9dd1d0] */
	goto L_4358d7;	/* 435894: jmp 0x4358d7 */
L_435896:
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 435896: mov eax, dword ptr [0x9dd1d0] */
	m->ecx = M32((DWORD)(m->edx + 0x9dceacu));	/* 43589b: mov ecx, dword ptr [edx + 0x9dceac] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4358a1: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_435909;	/* 4358a4: ja 0x435909 */
	switch (m->eax) { case 0: goto L_4358ad; case 1: goto L_4358c5; case 2: goto L_4358cd; case 3: goto L_4358b9; default: abort(); }	/* 4358a6: jmp dword ptr [eax*4 + 0x435948] */
L_4358ad:
	m->esi = M32((DWORD)(m->edx + 0x9dcee6u));	/* 4358ad: mov esi, dword ptr [edx + 0x9dcee6] */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 4358b3: mov dword ptr [esp + 0x10], esi */
	goto L_4358d7;	/* 4358b7: jmp 0x4358d7 */
L_4358b9:
	m->esi = M32((DWORD)(m->edx + 0x9dcedeu));	/* 4358b9: mov esi, dword ptr [edx + 0x9dcede] */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 4358bf: mov dword ptr [esp + 0x10], esi */
	goto L_4358d7;	/* 4358c3: jmp 0x4358d7 */
L_4358c5:
	FPUSH((long double)(int)M32((DWORD)(m->edx + 0x9dced6u)));	/* 4358c5: fild dword ptr [edx + 0x9dced6] */
	goto L_4358d3;	/* 4358cb: jmp 0x4358d3 */
L_4358cd:
	FPUSH((long double)(int)M32((DWORD)(m->edx + 0x9dceceu)));	/* 4358cd: fild dword ptr [edx + 0x9dcece] */
L_4358d3:
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 4358d3: fstp dword ptr [esp + 0x10] */
L_4358d7:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4358d7: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_435909;	/* 4358da: ja 0x435909 */
	switch (m->eax) { case 0: goto L_4358e3; case 1: goto L_4358f7; case 2: goto L_435901; case 3: goto L_4358ed; default: abort(); }	/* 4358dc: jmp dword ptr [eax*4 + 0x435958] */
L_4358e3:
	ST(0) = ST(0); FPOP();	/* 4358e3: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x9dcf2au)));	/* 4358e5: fld dword ptr [edx + 0x9dcf2a] */
	goto L_435909;	/* 4358eb: jmp 0x435909 */
L_4358ed:
	ST(0) = ST(0); FPOP();	/* 4358ed: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + 0x9dcf22u)));	/* 4358ef: fld dword ptr [edx + 0x9dcf22] */
	goto L_435909;	/* 4358f5: jmp 0x435909 */
L_4358f7:
	ST(0) = ST(0); FPOP();	/* 4358f7: fstp st(0) */
	FPUSH((long double)(int)M32((DWORD)(m->edx + 0x9dcf1au)));	/* 4358f9: fild dword ptr [edx + 0x9dcf1a] */
	goto L_435909;	/* 4358ff: jmp 0x435909 */
L_435901:
	ST(0) = ST(0); FPOP();	/* 435901: fstp st(0) */
	FPUSH((long double)(int)M32((DWORD)(m->edx + 0x9dcf12u)));	/* 435903: fild dword ptr [edx + 0x9dcf12] */
L_435909:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x10u));	/* 435909: fcom dword ptr [esp + 0x10] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43590d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43590f: test ah, 0x40 */
	if (m->zf) goto L_43591a;	/* 435912: je 0x43591a */
	M32((DWORD)(m->edx + 0x9dcef0u)) = m->ecx;	/* 435914: mov dword ptr [edx + 0x9dcef0], ecx */
L_43591a:
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 43591a: inc ebp */
	{ DWORD a_ = m->ebp, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43591b: cmp ebp, 0xa */
	if (m->sf != m->of) goto L_4357c0;	/* 43591e: jl 0x4357c0 */
L_435924:
	m->ecx = m->ebp;	/* 435924: mov ecx, ebp */
	m->edi = M32(m->esp); m->esp += 4;	/* 435926: pop edi */
	MF((DWORD)(0x9dd384u)) = (float)ST(0); FPOP();	/* 435927: fstp dword ptr [0x9dd384] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43592d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 435930: add ecx, ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 435932: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 435933: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 435934: pop ebx */
	m->edx = M32((DWORD)(m->ecx*4 + 0x9dceacu));	/* 435935: mov edx, dword ptr [ecx*4 + 0x9dceac] */
	M32((DWORD)(0x9dd328u)) = m->edx;	/* 43593c: mov dword ptr [0x9dd328], edx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435942: add esp, 8 */
	m->esp += 4 + 0; return;	/* 435945: ret  */
}

/* cfg_parseServer (0x42c6f0), lifted by tools/lift.py */
static void lift_42c6f0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c6f0: sub esp, 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6f3: push esi */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 42c6f4: mov esi, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6f8: push esi */
	{ DWORD v_ = 0x4b19f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c6f9: push 0x4b19f0 */
	m->esp -= 4; M32(m->esp) = 0x42c703u; native_call(m, 0x49f167u);	/* 42c6fe: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c703: push esi */
	{ DWORD v_ = 0x4ded20u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c704: push 0x4ded20 */
	m->esp -= 4; M32(m->esp) = 0x42c70eu; native_call(m, 0x49f167u);	/* 42c709: call 0x49f167 */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c70e: push 0x4b182c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c713: push esi */
	m->esp -= 4; M32(m->esp) = 0x42c719u; native_call(m, 0x49f135u);	/* 42c714: call 0x49f135 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c719: push esi */
	{ DWORD v_ = 0x4b19e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c71a: push 0x4b19e0 */
	m->esp -= 4; M32(m->esp) = 0x42c724u; native_call(m, 0x49f167u);	/* 42c71f: call 0x49f167 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 42c724: movsx ecx, byte ptr [0x4ded40] */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 42c72b: lea eax, [esp + 0x24] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 42c72f: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c731: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c732: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c738u; native_call(m, 0x49fb53u);	/* 42c733: call 0x49fb53 */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 42c738: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c73c: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c73d: push edx */
	m->esp -= 4; M32(m->esp) = 0x42c743u; native_call(m, 0x49f167u);	/* 42c73e: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c743: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c744: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42c74eu; native_call(m, 0x49f167u);	/* 42c749: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c74e: push esi */
	{ DWORD v_ = 0x4b19c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c74f: push 0x4b19c8 */
	m->esp -= 4; M32(m->esp) = 0x42c759u; native_call(m, 0x49f167u);	/* 42c754: call 0x49f167 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded41u)));	/* 42c759: movsx ecx, byte ptr [0x4ded41] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c760: add esp, 0x44 */
	m->eax = (DWORD)(m->esp + 0x4u);	/* 42c763: lea eax, [esp + 4] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 42c767: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c769: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c76a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c770u; native_call(m, 0x49fb53u);	/* 42c76b: call 0x49fb53 */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42c770: lea edx, [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c774: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c775: push edx */
	m->esp -= 4; M32(m->esp) = 0x42c77bu; native_call(m, 0x49f167u);	/* 42c776: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c77b: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c77c: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42c786u; native_call(m, 0x49f167u);	/* 42c781: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c786: push esi */
	{ DWORD v_ = 0x4b19b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c787: push 0x4b19b0 */
	m->esp -= 4; M32(m->esp) = 0x42c791u; native_call(m, 0x49f167u);	/* 42c78c: call 0x49f167 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded42u))) & 0xff) << 0);	/* 42c791: mov al, byte ptr [0x4ded42] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c796: add esp, 0x24 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 42c799: cmp al, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c79b: push esi */
	if (!m->zf) goto L_42c7a5;	/* 42c79c: jne 0x42c7a5 */
	{ DWORD v_ = 0x4b17e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c79e: push 0x4b17e4 */
	goto L_42c7aa;	/* 42c7a3: jmp 0x42c7aa */
L_42c7a5:
	{ DWORD v_ = 0x4b17dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7a5: push 0x4b17dc */
L_42c7aa:
	m->esp -= 4; M32(m->esp) = 0x42c7afu; native_call(m, 0x49f167u);	/* 42c7aa: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c7af: add esp, 8 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7b2: push esi */
	{ DWORD v_ = 0x4b199cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7b3: push 0x4b199c */
	m->esp -= 4; M32(m->esp) = 0x42c7bdu; native_call(m, 0x49f167u);	/* 42c7b8: call 0x49f167 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 42c7bd: movsx eax, byte ptr [0x4ded43] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c7c4: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42c7c7: cmp eax, 0xe */
	if (!m->cf && !m->zf) goto L_42c843;	/* 42c7ca: ja 0x42c843 */
	switch (m->eax) { case 0: goto L_42c843; case 1: goto L_42c7d3; case 2: goto L_42c7db; case 3: goto L_42c7e3; case 4: goto L_42c7eb; case 5: goto L_42c7f3; case 6: goto L_42c7fb; case 7: goto L_42c803; case 8: goto L_42c80b; case 9: goto L_42c813; case 10: goto L_42c81b; case 11: goto L_42c823; case 12: goto L_42c82b; case 13: goto L_42c833; case 14: goto L_42c83b; default: abort(); }	/* 42c7cc: jmp dword ptr [eax*4 + 0x42c8cc] */
L_42c7d3:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7d3: push esi */
	{ DWORD v_ = 0x4b1988u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7d4: push 0x4b1988 */
	goto L_42c849;	/* 42c7d9: jmp 0x42c849 */
L_42c7db:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7db: push esi */
	{ DWORD v_ = 0x4b1978u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7dc: push 0x4b1978 */
	goto L_42c849;	/* 42c7e1: jmp 0x42c849 */
L_42c7e3:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7e3: push esi */
	{ DWORD v_ = 0x4b1964u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7e4: push 0x4b1964 */
	goto L_42c849;	/* 42c7e9: jmp 0x42c849 */
L_42c7eb:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7eb: push esi */
	{ DWORD v_ = 0x4b1954u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7ec: push 0x4b1954 */
	goto L_42c849;	/* 42c7f1: jmp 0x42c849 */
L_42c7f3:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7f3: push esi */
	{ DWORD v_ = 0x4b1940u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7f4: push 0x4b1940 */
	goto L_42c849;	/* 42c7f9: jmp 0x42c849 */
L_42c7fb:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7fb: push esi */
	{ DWORD v_ = 0x4b192cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c7fc: push 0x4b192c */
	goto L_42c849;	/* 42c801: jmp 0x42c849 */
L_42c803:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c803: push esi */
	{ DWORD v_ = 0x4b1914u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c804: push 0x4b1914 */
	goto L_42c849;	/* 42c809: jmp 0x42c849 */
L_42c80b:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c80b: push esi */
	{ DWORD v_ = 0x4b1904u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c80c: push 0x4b1904 */
	goto L_42c849;	/* 42c811: jmp 0x42c849 */
L_42c813:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c813: push esi */
	{ DWORD v_ = 0x4b18f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c814: push 0x4b18f0 */
	goto L_42c849;	/* 42c819: jmp 0x42c849 */
L_42c81b:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c81b: push esi */
	{ DWORD v_ = 0x4b18dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c81c: push 0x4b18dc */
	goto L_42c849;	/* 42c821: jmp 0x42c849 */
L_42c823:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c823: push esi */
	{ DWORD v_ = 0x4b18c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c824: push 0x4b18c4 */
	goto L_42c849;	/* 42c829: jmp 0x42c849 */
L_42c82b:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c82b: push esi */
	{ DWORD v_ = 0x4b18b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c82c: push 0x4b18b0 */
	goto L_42c849;	/* 42c831: jmp 0x42c849 */
L_42c833:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c833: push esi */
	{ DWORD v_ = 0x4b18a0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c834: push 0x4b18a0 */
	goto L_42c849;	/* 42c839: jmp 0x42c849 */
L_42c83b:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c83b: push esi */
	{ DWORD v_ = 0x4b1888u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c83c: push 0x4b1888 */
	goto L_42c849;	/* 42c841: jmp 0x42c849 */
L_42c843:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c843: push esi */
	{ DWORD v_ = 0x4b1878u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c844: push 0x4b1878 */
L_42c849:
	m->esp -= 4; M32(m->esp) = 0x42c84eu; native_call(m, 0x49f167u);	/* 42c849: call 0x49f167 */
	m->ecx = M32((DWORD)(0x4ded44u));	/* 42c84e: mov ecx, dword ptr [0x4ded44] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c854: add esp, 8 */
	m->eax = (DWORD)(m->esp + 0x4u);	/* 42c857: lea eax, [esp + 4] */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42c85b: and ecx, 0xff */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 42c861: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c863: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c864: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c86au; native_call(m, 0x49fb53u);	/* 42c865: call 0x49fb53 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c86a: push esi */
	{ DWORD v_ = 0x4b1860u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c86b: push 0x4b1860 */
	m->esp -= 4; M32(m->esp) = 0x42c875u; native_call(m, 0x49f167u);	/* 42c870: call 0x49f167 */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 42c875: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c879: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c87a: push edx */
	m->esp -= 4; M32(m->esp) = 0x42c880u; native_call(m, 0x49f167u);	/* 42c87b: call 0x49f167 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c880: push esi */
	{ DWORD v_ = 0x4b182cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42c881: push 0x4b182c */
	m->esp -= 4; M32(m->esp) = 0x42c88bu; native_call(m, 0x49f167u);	/* 42c886: call 0x49f167 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42c88b: xor ecx, ecx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 42c88d: lea eax, [esp + 0x28] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded45u))) & 0xff) << 0);	/* 42c891: mov cl, byte ptr [0x4ded45] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 42c897: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42c899: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c89a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42c8a0u; native_call(m, 0x49fb53u);	/* 42c89b: call 0x49fb53 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c8a0: push esi */
	{ DWORD v_ = 0x4b1848u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c8a1: push 0x4b1848 */
	m->esp -= 4; M32(m->esp) = 0x42c8abu; native_call(m, 0x49f167u);	/* 42c8a6: call 0x49f167 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 42c8ab: lea edx, [esp + 0x3c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c8af: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42c8b0: push edx */
	m->esp -= 4; M32(m->esp) = 0x42c8b6u; native_call(m, 0x49f167u);	/* 42c8b1: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c8b6: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42c8b9: push esi */
	{ DWORD v_ = 0x4b1844u; m->esp -= 4; M32(m->esp) = v_; }	/* 42c8ba: push 0x4b1844 */
	m->esp -= 4; M32(m->esp) = 0x42c8c4u; native_call(m, 0x49f167u);	/* 42c8bf: call 0x49f167 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c8c4: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 42c8c7: pop esi */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42c8c8: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 42c8cb: ret  */
}

/* armc_40f340 (0x40f340), lifted by tools/lift.py */
static void lift_40f340(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 40f340: mov eax, dword ptr [esp + 8] */
	m->ecx = 0x1u;	/* 40f344: mov ecx, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f349: cmp eax, ecx */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 40f34b: mov eax, dword ptr [esp + 4] */
	if (!m->zf) goto L_40f45e;	/* 40f34f: jne 0x40f45e */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f355: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_40f555;	/* 40f358: ja 0x40f555 */
	switch (m->eax) { case 0: goto L_40f365; case 1: goto L_40f396; case 2: goto L_40f3c9; case 3: goto L_40f3fa; case 4: goto L_40f42d; default: abort(); }	/* 40f35e: jmp dword ptr [eax*4 + 0x40f55c] */
L_40f365:
	m->eax = M32((DWORD)(0x4dcc8cu));	/* 40f365: mov eax, dword ptr [0x4dcc8c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f36a: dec eax */
	M32((DWORD)(0x4dcc8cu)) = m->eax;	/* 40f36b: mov dword ptr [0x4dcc8c], eax */
	if (!m->sf) goto L_40f37d;	/* 40f370: jns 0x40f37d */
	m->eax = M32((DWORD)(0x4dc780u));	/* 40f372: mov eax, dword ptr [0x4dc780] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f377: dec eax */
	M32((DWORD)(0x4dcc8cu)) = m->eax;	/* 40f378: mov dword ptr [0x4dcc8c], eax */
L_40f37d:
	m->edx = M32((DWORD)(0x4dcc8cu));	/* 40f37d: mov edx, dword ptr [0x4dcc8c] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f383: mov dword ptr [0x4dcc58], ecx */
	m->eax = M32((DWORD)(m->edx*4 + 0x4dc3e8u));	/* 40f389: mov eax, dword ptr [edx*4 + 0x4dc3e8] */
	M32((DWORD)(0x4dc760u)) = m->eax;	/* 40f390: mov dword ptr [0x4dc760], eax */
	m->esp += 4 + 0; return;	/* 40f395: ret  */
L_40f396:
	m->eax = M32((DWORD)(0x4dcf3cu));	/* 40f396: mov eax, dword ptr [0x4dcf3c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f39b: dec eax */
	M32((DWORD)(0x4dcf3cu)) = m->eax;	/* 40f39c: mov dword ptr [0x4dcf3c], eax */
	if (!m->sf) goto L_40f3b0;	/* 40f3a1: jns 0x40f3b0 */
	m->edx = M32((DWORD)(0x4dcc60u));	/* 40f3a3: mov edx, dword ptr [0x4dcc60] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 40f3a9: dec edx */
	M32((DWORD)(0x4dcf3cu)) = m->edx;	/* 40f3aa: mov dword ptr [0x4dcf3c], edx */
L_40f3b0:
	m->eax = M32((DWORD)(0x4dcf3cu));	/* 40f3b0: mov eax, dword ptr [0x4dcf3c] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f3b5: mov dword ptr [0x4dcc58], ecx */
	m->edx = M32((DWORD)(m->eax*4 + 0x4dcd6cu));	/* 40f3bb: mov edx, dword ptr [eax*4 + 0x4dcd6c] */
	M32((DWORD)(0x4dc764u)) = m->edx;	/* 40f3c2: mov dword ptr [0x4dc764], edx */
	m->esp += 4 + 0; return;	/* 40f3c8: ret  */
L_40f3c9:
	m->eax = M32((DWORD)(0x4dbc7cu));	/* 40f3c9: mov eax, dword ptr [0x4dbc7c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f3ce: dec eax */
	M32((DWORD)(0x4dbc7cu)) = m->eax;	/* 40f3cf: mov dword ptr [0x4dbc7c], eax */
	if (!m->sf) goto L_40f3e1;	/* 40f3d4: jns 0x40f3e1 */
	m->eax = M32((DWORD)(0x4dca90u));	/* 40f3d6: mov eax, dword ptr [0x4dca90] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f3db: dec eax */
	M32((DWORD)(0x4dbc7cu)) = m->eax;	/* 40f3dc: mov dword ptr [0x4dbc7c], eax */
L_40f3e1:
	m->edx = M32((DWORD)(0x4dbc7cu));	/* 40f3e1: mov edx, dword ptr [0x4dbc7c] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f3e7: mov dword ptr [0x4dcc58], ecx */
	m->eax = M32((DWORD)(m->edx*4 + 0x4dc964u));	/* 40f3ed: mov eax, dword ptr [edx*4 + 0x4dc964] */
	M32((DWORD)(0x4dc768u)) = m->eax;	/* 40f3f4: mov dword ptr [0x4dc768], eax */
	m->esp += 4 + 0; return;	/* 40f3f9: ret  */
L_40f3fa:
	m->eax = M32((DWORD)(0x4dcea4u));	/* 40f3fa: mov eax, dword ptr [0x4dcea4] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f3ff: dec eax */
	M32((DWORD)(0x4dcea4u)) = m->eax;	/* 40f400: mov dword ptr [0x4dcea4], eax */
	if (!m->sf) goto L_40f414;	/* 40f405: jns 0x40f414 */
	m->edx = M32((DWORD)(0x4dca94u));	/* 40f407: mov edx, dword ptr [0x4dca94] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 40f40d: dec edx */
	M32((DWORD)(0x4dcea4u)) = m->edx;	/* 40f40e: mov dword ptr [0x4dcea4], edx */
L_40f414:
	m->eax = M32((DWORD)(0x4dcea4u));	/* 40f414: mov eax, dword ptr [0x4dcea4] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f419: mov dword ptr [0x4dcc58], ecx */
	m->edx = M32((DWORD)(m->eax*4 + 0x4dc89cu));	/* 40f41f: mov edx, dword ptr [eax*4 + 0x4dc89c] */
	M32((DWORD)(0x4dc76cu)) = m->edx;	/* 40f426: mov dword ptr [0x4dc76c], edx */
	m->esp += 4 + 0; return;	/* 40f42c: ret  */
L_40f42d:
	m->eax = M32((DWORD)(0x4dcb30u));	/* 40f42d: mov eax, dword ptr [0x4dcb30] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f432: dec eax */
	M32((DWORD)(0x4dcb30u)) = m->eax;	/* 40f433: mov dword ptr [0x4dcb30], eax */
	if (!m->sf) goto L_40f445;	/* 40f438: jns 0x40f445 */
	m->eax = M32((DWORD)(0x4dc890u));	/* 40f43a: mov eax, dword ptr [0x4dc890] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f43f: dec eax */
	M32((DWORD)(0x4dcb30u)) = m->eax;	/* 40f440: mov dword ptr [0x4dcb30], eax */
L_40f445:
	m->edx = M32((DWORD)(0x4dcb30u));	/* 40f445: mov edx, dword ptr [0x4dcb30] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f44b: mov dword ptr [0x4dcc58], ecx */
	m->eax = M32((DWORD)(m->edx*4 + 0x4dbd7cu));	/* 40f451: mov eax, dword ptr [edx*4 + 0x4dbd7c] */
	M32((DWORD)(0x4dc770u)) = m->eax;	/* 40f458: mov dword ptr [0x4dc770], eax */
	m->esp += 4 + 0; return;	/* 40f45d: ret  */
L_40f45e:
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f45e: cmp eax, 4 */
	if (!m->cf && !m->zf) goto L_40f555;	/* 40f461: ja 0x40f555 */
	switch (m->eax) { case 0: goto L_40f46e; case 1: goto L_40f49e; case 2: goto L_40f4cd; case 3: goto L_40f4fd; case 4: goto L_40f52c; default: abort(); }	/* 40f467: jmp dword ptr [eax*4 + 0x40f570] */
L_40f46e:
	m->eax = M32((DWORD)(0x4dcc8cu));	/* 40f46e: mov eax, dword ptr [0x4dcc8c] */
	m->edx = M32((DWORD)(0x4dc780u));	/* 40f473: mov edx, dword ptr [0x4dc780] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40f479: inc eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f47a: cmp eax, edx */
	M32((DWORD)(0x4dcc8cu)) = m->eax;	/* 40f47c: mov dword ptr [0x4dcc8c], eax */
	if (m->sf != m->of) goto L_40f48a;	/* 40f481: jl 0x40f48a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f483: xor eax, eax */
	M32((DWORD)(0x4dcc8cu)) = m->eax;	/* 40f485: mov dword ptr [0x4dcc8c], eax */
L_40f48a:
	m->edx = M32((DWORD)(m->eax*4 + 0x4dc3e8u));	/* 40f48a: mov edx, dword ptr [eax*4 + 0x4dc3e8] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f491: mov dword ptr [0x4dcc58], ecx */
	M32((DWORD)(0x4dc760u)) = m->edx;	/* 40f497: mov dword ptr [0x4dc760], edx */
	m->esp += 4 + 0; return;	/* 40f49d: ret  */
L_40f49e:
	m->eax = M32((DWORD)(0x4dcf3cu));	/* 40f49e: mov eax, dword ptr [0x4dcf3c] */
	m->edx = M32((DWORD)(0x4dcc60u));	/* 40f4a3: mov edx, dword ptr [0x4dcc60] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40f4a9: inc eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f4aa: cmp eax, edx */
	M32((DWORD)(0x4dcf3cu)) = m->eax;	/* 40f4ac: mov dword ptr [0x4dcf3c], eax */
	if (m->sf != m->of) goto L_40f4ba;	/* 40f4b1: jl 0x40f4ba */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f4b3: xor eax, eax */
	M32((DWORD)(0x4dcf3cu)) = m->eax;	/* 40f4b5: mov dword ptr [0x4dcf3c], eax */
L_40f4ba:
	m->eax = M32((DWORD)(m->eax*4 + 0x4dcd6cu));	/* 40f4ba: mov eax, dword ptr [eax*4 + 0x4dcd6c] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f4c1: mov dword ptr [0x4dcc58], ecx */
	M32((DWORD)(0x4dc764u)) = m->eax;	/* 40f4c7: mov dword ptr [0x4dc764], eax */
	m->esp += 4 + 0; return;	/* 40f4cc: ret  */
L_40f4cd:
	m->eax = M32((DWORD)(0x4dbc7cu));	/* 40f4cd: mov eax, dword ptr [0x4dbc7c] */
	m->edx = M32((DWORD)(0x4dca90u));	/* 40f4d2: mov edx, dword ptr [0x4dca90] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40f4d8: inc eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f4d9: cmp eax, edx */
	M32((DWORD)(0x4dbc7cu)) = m->eax;	/* 40f4db: mov dword ptr [0x4dbc7c], eax */
	if (m->sf != m->of) goto L_40f4e9;	/* 40f4e0: jl 0x40f4e9 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f4e2: xor eax, eax */
	M32((DWORD)(0x4dbc7cu)) = m->eax;	/* 40f4e4: mov dword ptr [0x4dbc7c], eax */
L_40f4e9:
	m->edx = M32((DWORD)(m->eax*4 + 0x4dc964u));	/* 40f4e9: mov edx, dword ptr [eax*4 + 0x4dc964] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f4f0: mov dword ptr [0x4dcc58], ecx */
	M32((DWORD)(0x4dc768u)) = m->edx;	/* 40f4f6: mov dword ptr [0x4dc768], edx */
	m->esp += 4 + 0; return;	/* 40f4fc: ret  */
L_40f4fd:
	m->eax = M32((DWORD)(0x4dcea4u));	/* 40f4fd: mov eax, dword ptr [0x4dcea4] */
	m->edx = M32((DWORD)(0x4dca94u));	/* 40f502: mov edx, dword ptr [0x4dca94] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40f508: inc eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f509: cmp eax, edx */
	M32((DWORD)(0x4dcea4u)) = m->eax;	/* 40f50b: mov dword ptr [0x4dcea4], eax */
	if (m->sf != m->of) goto L_40f519;	/* 40f510: jl 0x40f519 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f512: xor eax, eax */
	M32((DWORD)(0x4dcea4u)) = m->eax;	/* 40f514: mov dword ptr [0x4dcea4], eax */
L_40f519:
	m->eax = M32((DWORD)(m->eax*4 + 0x4dc89cu));	/* 40f519: mov eax, dword ptr [eax*4 + 0x4dc89c] */
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f520: mov dword ptr [0x4dcc58], ecx */
	M32((DWORD)(0x4dc76cu)) = m->eax;	/* 40f526: mov dword ptr [0x4dc76c], eax */
	m->esp += 4 + 0; return;	/* 40f52b: ret  */
L_40f52c:
	m->eax = M32((DWORD)(0x4dcb30u));	/* 40f52c: mov eax, dword ptr [0x4dcb30] */
	m->edx = M32((DWORD)(0x4dc890u));	/* 40f531: mov edx, dword ptr [0x4dc890] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 40f537: inc eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f538: cmp eax, edx */
	M32((DWORD)(0x4dcb30u)) = m->eax;	/* 40f53a: mov dword ptr [0x4dcb30], eax */
	if (m->sf != m->of) goto L_40f548;	/* 40f53f: jl 0x40f548 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f541: xor eax, eax */
	M32((DWORD)(0x4dcb30u)) = m->eax;	/* 40f543: mov dword ptr [0x4dcb30], eax */
L_40f548:
	m->edx = M32((DWORD)(m->eax*4 + 0x4dbd7cu));	/* 40f548: mov edx, dword ptr [eax*4 + 0x4dbd7c] */
	M32((DWORD)(0x4dc770u)) = m->edx;	/* 40f54f: mov dword ptr [0x4dc770], edx */
L_40f555:
	M32((DWORD)(0x4dcc58u)) = m->ecx;	/* 40f555: mov dword ptr [0x4dcc58], ecx */
	m->esp += 4 + 0; return;	/* 40f55b: ret  */
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
