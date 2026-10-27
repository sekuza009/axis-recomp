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

static void lift_4014c0(X86 *m);
static void lift_454a20(X86 *m);
static void lift_4549e0(X86 *m);
static void lift_403530(X86 *m);
static void lift_4034e0(X86 *m);
static void lift_407970(X86 *m);
static void lift_436940(X86 *m);
static void lift_44ac90(X86 *m);
static void lift_441770(X86 *m);
static void lift_4080c0(X86 *m);
static void lift_44ace0(X86 *m);
static void lift_435ce0(X86 *m);
static void lift_4370e0(X86 *m);
static void lift_454b40(X86 *m);
static void lift_454b00(X86 *m);
static void lift_453770(X86 *m);

/* arena_453770 (0x453770), lifted by tools/lift.py */
static void lift_453770(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x453775u; native_call(m, 0x4509e0u);	/* 453770: call 0x4509e0 */
	m->esp -= 4; M32(m->esp) = 0x45377au; native_call(m, 0x453790u);	/* 453775: call 0x453790 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45377a: test eax, eax */
	if (m->zf) goto L_453783;	/* 45377c: je 0x453783 */
	m->esp -= 4; M32(m->esp) = 0x453783u; native_call(m, 0x453920u);	/* 45377e: call 0x453920 */
L_453783:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453783: xor eax, eax */
	m->esp += 4 + 0; return;	/* 453785: ret  */
}

/* wnd_4014c0 (0x4014c0), lifted by tools/lift.py */
static void lift_4014c0(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x4014c5u; native_call(m, 0x401460u);	/* 4014c0: call 0x401460 */
	m->esp -= 4; M32(m->esp) = 0x4014cau; native_call(m, 0x401490u);	/* 4014c5: call 0x401490 */
	m->eax = M32((DWORD)(0x4d1e98u));	/* 4014ca: mov eax, dword ptr [0x4d1e98] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4014cf: test eax, eax */
	if (m->zf) goto L_4014e3;	/* 4014d1: je 0x4014e3 */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4014d3: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4014d5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4014d9u; native_call(m, M32((DWORD)(m->ecx + 0x8u)));	/* 4014d6: call dword ptr [ecx + 8] */
	M32((DWORD)(0x4d1e98u)) = 0x0u;	/* 4014d9: mov dword ptr [0x4d1e98], 0 */
L_4014e3:
	m->esp += 4 + 0; return;	/* 4014e3: ret  */
}

/* arena_454a20 (0x454a20), lifted by tools/lift.py */
static void lift_454a20(X86 *m)
{
	m->ecx = M32((DWORD)(0xa0d7a4u));	/* 454a20: mov ecx, dword ptr [0xa0d7a4] */
	m->eax = 0x1f4u;	/* 454a26: mov eax, 0x1f4 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454a2b: test ecx, ecx */
	if (m->zf) goto L_454a4b;	/* 454a2d: je 0x454a4b */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 454a2f: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 454a33: mov ecx, dword ptr [esp + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 454a37: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454a3b: push eax */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 454a3c: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454a40: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454a41: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454a42: push eax */
	m->esp -= 4; M32(m->esp) = 0x454a48u; native_call(m, 0x453e60u);	/* 454a43: call 0x453e60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454a48: add esp, 0x10 */
L_454a4b:
	m->esp += 4 + 0; return;	/* 454a4b: ret  */
}

/* arena_4549e0 (0x4549e0), lifted by tools/lift.py */
static void lift_4549e0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7a4u));	/* 4549e0: mov eax, dword ptr [0xa0d7a4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4549e5: test eax, eax */
	if (m->zf) goto L_454a1a;	/* 4549e7: je 0x454a1a */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4549e9: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4549ed: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4549f1: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4549f5: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4549f6: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4549fa: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4549fb: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4549ff: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 454a00: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454a04: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 454a05: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454a09: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 454a0a: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454a0e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454a0f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454a10: push ecx */
	m->esp -= 4; M32(m->esp) = 0x454a16u; native_call(m, 0x453cf0u);	/* 454a11: call 0x453cf0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454a16: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 454a19: ret  */
L_454a1a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454a1a: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454a1c: ret  */
}

/* room_403530 (0x403530), lifted by tools/lift.py */
static void lift_403530(X86 *m)
{
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403530: push 0 */
	m->esp -= 4; M32(m->esp) = 0x403537u; native_call(m, 0x41e760u);	/* 403532: call 0x41e760 */
	m->ecx = M32((DWORD)(0x67ef00u));	/* 403537: mov ecx, dword ptr [0x67ef00] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40353d: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 403540: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_40355c;	/* 403542: jle 0x40355c */
	m->eax = 0x4d735cu;	/* 403544: mov eax, 0x4d735c */
L_403549:
	M32((DWORD)(m->eax + 0xfffffffcu)) = 0x0u;	/* 403549: mov dword ptr [eax - 4], 0 */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 403550: mov dword ptr [eax], 0 */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 403556: add eax, 8 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 403559: dec ecx */
	if (!m->zf) goto L_403549;	/* 40355a: jne 0x403549 */
L_40355c:
	m->esp += 4 + 0; return;	/* 40355c: ret  */
}

/* room_4034e0 (0x4034e0), lifted by tools/lift.py */
static void lift_4034e0(X86 *m)
{
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4034e0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4034e7u; native_call(m, 0x41e760u);	/* 4034e2: call 0x41e760 */
	m->ecx = M32((DWORD)(0x67ef00u));	/* 4034e7: mov ecx, dword ptr [0x67ef00] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4034ed: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4034f0: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_403505;	/* 4034f2: jle 0x403505 */
	m->eax = 0x4d7358u;	/* 4034f4: mov eax, 0x4d7358 */
L_4034f9:
	M32((DWORD)(m->eax + 0x0u)) = 0x1u;	/* 4034f9: mov dword ptr [eax], 1 */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4034ff: add eax, 8 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 403502: dec ecx */
	if (!m->zf) goto L_4034f9;	/* 403503: jne 0x4034f9 */
L_403505:
	M32((DWORD)(0x4d7408u)) = 0x0u;	/* 403505: mov dword ptr [0x4d7408], 0 */
	M32((DWORD)(0x4d7410u)) = 0x0u;	/* 40350f: mov dword ptr [0x4d7410], 0 */
	M32((DWORD)(0x4d7418u)) = 0x0u;	/* 403519: mov dword ptr [0x4d7418], 0 */
	m->esp += 4 + 0; return;	/* 403523: ret  */
}

/* lobbyJoin_keys (0x407970), lifted by tools/lift.py */
static void lift_407970(X86 *m)
{
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 407970: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 407975: push eax */
	m->esp -= 4; M32(m->esp) = 0x40797bu; native_call(m, 0x401600u);	/* 407976: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40797b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40797e: test eax, eax */
	if (m->zf) goto L_40798d;	/* 407980: je 0x40798d */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 407982: mov dword ptr [0x907b2c], 0 */
	m->esp += 4 + 0; return;	/* 40798c: ret  */
L_40798d:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 40798d: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407993: push ecx */
	m->esp -= 4; M32(m->esp) = 0x407999u; native_call(m, 0x401600u);	/* 407994: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407999: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40799c: test eax, eax */
	if (m->zf) goto L_4079b2;	/* 40799e: je 0x4079b2 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4079a0: push 2 */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 4079a2: mov dword ptr [0x907b2c], 0 */
	m->esp -= 4; M32(m->esp) = 0x4079b1u; native_call(m, 0x41e7a0u);	/* 4079ac: call 0x41e7a0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4079b1: pop ecx */
L_4079b2:
	m->esp += 4 + 0; return;	/* 4079b2: ret  */
}

/* menu_436940 (0x436940), lifted by tools/lift.py */
static void lift_436940(X86 *m)
{
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 436940: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 436945: push eax */
	m->esp -= 4; M32(m->esp) = 0x43694bu; native_call(m, 0x401600u);	/* 436946: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43694b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43694e: test eax, eax */
	if (m->zf) goto L_43695d;	/* 436950: je 0x43695d */
	M32((DWORD)(0x9dd850u)) = 0x0u;	/* 436952: mov dword ptr [0x9dd850], 0 */
	m->esp += 4 + 0; return;	/* 43695c: ret  */
L_43695d:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 43695d: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 436963: push ecx */
	m->esp -= 4; M32(m->esp) = 0x436969u; native_call(m, 0x401600u);	/* 436964: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 436969: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43696c: test eax, eax */
	if (m->zf) goto L_436982;	/* 43696e: je 0x436982 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 436970: push 2 */
	M32((DWORD)(0x9dd850u)) = 0x0u;	/* 436972: mov dword ptr [0x9dd850], 0 */
	m->esp -= 4; M32(m->esp) = 0x436981u; native_call(m, 0x41e7a0u);	/* 43697c: call 0x41e7a0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 436981: pop ecx */
L_436982:
	m->esp += 4 + 0; return;	/* 436982: ret  */
}

/* match_44ac90 (0x44ac90), lifted by tools/lift.py */
static void lift_44ac90(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ac90: push esi */
	m->esp -= 4; M32(m->esp) = 0x44ac96u; native_call(m, 0x401460u);	/* 44ac91: call 0x401460 */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 44ac96: mov esi, dword ptr [esp + 0x10] */
	m->eax = 0x1u;	/* 44ac9a: mov eax, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ac9f: push esi */
	M32((DWORD)(0x68039cu)) = m->eax;	/* 44aca0: mov dword ptr [0x68039c], eax */
	M32((DWORD)(0x9f67e8u)) = m->eax;	/* 44aca5: mov dword ptr [0x9f67e8], eax */
	m->esp -= 4; M32(m->esp) = 0x44acafu; native_call(m, 0x431560u);	/* 44acaa: call 0x431560 */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 44acaf: mov eax, dword ptr [esp + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 44acb3: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44acb7: push esi */
	M32((DWORD)(0x9f63c8u)) = m->eax;	/* 44acb8: mov dword ptr [0x9f63c8], eax */
	M32((DWORD)(0x9f63c4u)) = m->ecx;	/* 44acbd: mov dword ptr [0x9f63c4], ecx */
	M32((DWORD)(0x9da434u)) = 0x41a00000u;	/* 44acc3: mov dword ptr [0x9da434], 0x41a00000 */
	m->esp -= 4; M32(m->esp) = 0x44acd2u; native_call(m, 0x43f460u);	/* 44accd: call 0x43f460 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44acd2: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44acd5: pop esi */
	m->esp += 4 + 0; return;	/* 44acd6: ret  */
}

/* mainmenu_441770 (0x441770), lifted by tools/lift.py */
static void lift_441770(X86 *m)
{
	m->edx = M32((DWORD)(0x9dd928u));	/* 441770: mov edx, dword ptr [0x9dd928] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 441776: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441778: test edx, edx */
	if (m->zf || m->sf != m->of) goto L_4417b7;	/* 44177a: jle 0x4417b7 */
	m->ecx = 0x9ddac8u;	/* 44177c: mov ecx, 0x9ddac8 */
L_441781:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441781: cmp dword ptr [ecx], 1 */
	if (m->zf) goto L_44178f;	/* 441784: je 0x44178f */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 441786: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 441787: add ecx, 0x44 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44178a: cmp eax, edx */
	if (m->sf != m->of) goto L_441781;	/* 44178c: jl 0x441781 */
	m->esp += 4 + 0; return;	/* 44178e: ret  */
L_44178f:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44178f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x441796u; native_call(m, 0x41e760u);	/* 441791: call 0x41e760 */
	m->eax = M32((DWORD)(0x9dd928u));	/* 441796: mov eax, dword ptr [0x9dd928] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44179b: add esp, 4 */
	M32((DWORD)(0x9eeab8u)) = m->eax;	/* 44179e: mov dword ptr [0x9eeab8], eax */
	M32((DWORD)(0x9db994u)) = 0x1u;	/* 4417a3: mov dword ptr [0x9db994], 1 */
	M32((DWORD)(0x9eeab4u)) = 0x0u;	/* 4417ad: mov dword ptr [0x9eeab4], 0 */
L_4417b7:
	m->esp += 4 + 0; return;	/* 4417b7: ret  */
}

/* lobby_keysBack (0x4080c0), lifted by tools/lift.py */
static void lift_4080c0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 4080c0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4080c5: test eax, eax */
	if (!m->zf) goto L_40810b;	/* 4080c7: jne 0x40810b */
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 4080c9: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4080ce: push eax */
	m->esp -= 4; M32(m->esp) = 0x4080d4u; native_call(m, 0x401600u);	/* 4080cf: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4080d4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4080d7: test eax, eax */
	if (m->zf) goto L_4080e6;	/* 4080d9: je 0x4080e6 */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 4080db: mov dword ptr [0x907b2c], 0 */
	m->esp += 4 + 0; return;	/* 4080e5: ret  */
L_4080e6:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 4080e6: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4080ec: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4080f2u; native_call(m, 0x401600u);	/* 4080ed: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4080f2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4080f5: test eax, eax */
	if (m->zf) goto L_40810b;	/* 4080f7: je 0x40810b */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4080f9: push 2 */
	M32((DWORD)(0x907b2cu)) = 0x0u;	/* 4080fb: mov dword ptr [0x907b2c], 0 */
	m->esp -= 4; M32(m->esp) = 0x40810au; native_call(m, 0x41e7a0u);	/* 408105: call 0x41e7a0 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 40810a: pop ecx */
L_40810b:
	m->esp += 4 + 0; return;	/* 40810b: ret  */
}

/* match_44ace0 (0x44ace0), lifted by tools/lift.py */
static void lift_44ace0(X86 *m)
{
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ace0: push edi */
	m->ecx = 0x100u;	/* 44ace1: mov ecx, 0x100 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44ace6: xor eax, eax */
	m->edi = 0x9f63e4u;	/* 44ace8: mov edi, 0x9f63e4 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 44aced: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dc92cu;	/* 44acef: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44acf4: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44acf7: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44acf9: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44acfb: dec ecx */
	if (m->zf) goto L_44ad16;	/* 44acfc: je 0x44ad16 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44acfe: push esi */
	m->ecx = 0x100u;	/* 44acff: mov ecx, 0x100 */
	m->esi = 0x9dc92cu;	/* 44ad04: mov esi, 0x9dc92c */
	m->edi = 0x9f63e4u;	/* 44ad09: mov edi, 0x9f63e4 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44ad0e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	M32((DWORD)(0x9f67e8u)) = m->eax;	/* 44ad10: mov dword ptr [0x9f67e8], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 44ad15: pop esi */
L_44ad16:
	M32((DWORD)(0x68039cu)) = m->eax;	/* 44ad16: mov dword ptr [0x68039c], eax */
	m->esp -= 4; M32(m->esp) = 0x44ad20u; native_call(m, 0x431590u);	/* 44ad1b: call 0x431590 */
	m->eax = M32((DWORD)(0x4ded18u));	/* 44ad20: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ad25: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ad2bu; native_call(m, 0x401310u);	/* 44ad26: call 0x401310 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ad2b: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44ad2e: pop edi */
	m->esp += 4 + 0; return;	/* 44ad2f: ret  */
}

/* room_435ce0 (0x435ce0), lifted by tools/lift.py */
static void lift_435ce0(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 435ce0: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435ce5: test eax, eax */
	if (m->zf) goto L_435d2f;	/* 435ce7: je 0x435d2f */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 435ce9: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 435cee: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435cf4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435cf5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x435cfbu; native_call(m, 0x432280u);	/* 435cf6: call 0x432280 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435cfb: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 435cfe: sub eax, 0 */
	if (m->zf) goto L_435d1b;	/* 435d01: je 0x435d1b */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 435d03: dec eax */
	if (!m->zf) goto L_435d2f;	/* 435d04: jne 0x435d2f */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435d06: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435d0du; native_call(m, 0x41e760u);	/* 435d08: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435d0d: add esp, 4 */
	M32((DWORD)(0x9dd6c4u)) = 0x2u;	/* 435d10: mov dword ptr [0x9dd6c4], 2 */
	m->esp += 4 + 0; return;	/* 435d1a: ret  */
L_435d1b:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435d1b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435d22u; native_call(m, 0x41e760u);	/* 435d1d: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435d22: add esp, 4 */
	M32((DWORD)(0x9dd6c4u)) = 0x1u;	/* 435d25: mov dword ptr [0x9dd6c4], 1 */
L_435d2f:
	m->esp += 4 + 0; return;	/* 435d2f: ret  */
}

/* menu_4370e0 (0x4370e0), lifted by tools/lift.py */
static void lift_4370e0(X86 *m)
{
	m->eax = M32((DWORD)(0x4e1510u));	/* 4370e0: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4370e5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4370ebu; native_call(m, 0x401600u);	/* 4370e6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4370eb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4370ee: cmp eax, 1 */
	if (!m->zf) goto L_437108;	/* 4370f1: jne 0x437108 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4370f3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4370fau; native_call(m, 0x41e760u);	/* 4370f5: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4370fa: add esp, 4 */
	M32((DWORD)(0x9dd6c4u)) = 0x1u;	/* 4370fd: mov dword ptr [0x9dd6c4], 1 */
	m->esp += 4 + 0; return;	/* 437107: ret  */
L_437108:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 437108: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43710e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x437114u; native_call(m, 0x401600u);	/* 43710f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437114: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437117: cmp eax, 1 */
	if (!m->zf) goto L_437130;	/* 43711a: jne 0x437130 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43711c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x437123u; native_call(m, 0x41e760u);	/* 43711e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 437123: add esp, 4 */
	M32((DWORD)(0x9dd6c4u)) = 0x2u;	/* 437126: mov dword ptr [0x9dd6c4], 2 */
L_437130:
	m->esp += 4 + 0; return;	/* 437130: ret  */
}

/* arena_454b40 (0x454b40), lifted by tools/lift.py */
static void lift_454b40(X86 *m)
{
	m->ecx = M32((DWORD)(0xa0d7a8u));	/* 454b40: mov ecx, dword ptr [0xa0d7a8] */
	m->eax = 0x1f4u;	/* 454b46: mov eax, 0x1f4 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454b4b: test ecx, ecx */
	if (m->zf) goto L_454b6b;	/* 454b4d: je 0x454b6b */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 454b4f: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 454b53: mov ecx, dword ptr [esp + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 454b57: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454b5b: push eax */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 454b5c: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454b60: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454b61: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454b62: push eax */
	m->esp -= 4; M32(m->esp) = 0x454b68u; native_call(m, 0x453e60u);	/* 454b63: call 0x453e60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454b68: add esp, 0x10 */
L_454b6b:
	m->esp += 4 + 0; return;	/* 454b6b: ret  */
}

/* arena_454b00 (0x454b00), lifted by tools/lift.py */
static void lift_454b00(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7a8u));	/* 454b00: mov eax, dword ptr [0xa0d7a8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454b05: test eax, eax */
	if (m->zf) goto L_454b3a;	/* 454b07: je 0x454b3a */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 454b09: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 454b0d: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 454b11: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454b15: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 454b16: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454b1a: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 454b1b: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454b1f: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 454b20: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454b24: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 454b25: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454b29: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 454b2a: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454b2e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454b2f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454b30: push ecx */
	m->esp -= 4; M32(m->esp) = 0x454b36u; native_call(m, 0x453cf0u);	/* 454b31: call 0x453cf0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454b36: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 454b39: ret  */
L_454b3a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454b3a: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454b3c: ret  */
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
