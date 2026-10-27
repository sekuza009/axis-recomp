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

static void lift_454940(X86 *m);
static void lift_454a50(X86 *m);
static void lift_454b70(X86 *m);
static void lift_454c80(X86 *m);
static void lift_435c20(X86 *m);
static void lift_4620e0(X86 *m);
static void lift_453090(X86 *m);
static void lift_441740(X86 *m);

/* menu_drawBackground (0x441740), lifted by tools/lift.py */
static void lift_441740(X86 *m)
{
	m->eax = M32((DWORD)(0x67fb3cu));	/* 441740: mov eax, dword ptr [0x67fb3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441745: push eax */
	m->esp -= 4; M32(m->esp) = 0x44174bu; native_call(m, 0x441260u);	/* 441746: call 0x441260 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44174b: push 1 */
	m->esp -= 4; M32(m->esp) = 0x441752u; native_call(m, 0x41ef90u);	/* 44174d: call 0x41ef90 */
	m->ecx = M32((DWORD)(0x67fb3cu));	/* 441752: mov ecx, dword ptr [0x67fb3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 441758: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44175eu; native_call(m, 0x429d70u);	/* 441759: call 0x429d70 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44175e: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 441761: ret  */
}

/* arena_454940 (0x454940), lifted by tools/lift.py */
static void lift_454940(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7a4u));	/* 454940: mov eax, dword ptr [0xa0d7a4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454945: test eax, eax */
	if (m->zf) goto L_454958;	/* 454947: je 0x454958 */
	m->esp -= 4; M32(m->esp) = 0x45494eu; native_call(m, 0x4549a0u);	/* 454949: call 0x4549a0 */
	M32((DWORD)(0xa0d7a4u)) = 0x0u;	/* 45494e: mov dword ptr [0xa0d7a4], 0 */
L_454958:
	m->esp -= 4; M32(m->esp) = 0x45495du; native_call(m, 0x453720u);	/* 454958: call 0x453720 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45495d: test eax, eax */
	if (!m->zf) goto L_45499b;	/* 45495f: jne 0x45499b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454961: push eax */
	m->esp -= 4; M32(m->esp) = 0x454967u; native_call(m, 0x453a30u);	/* 454962: call 0x453a30 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454967: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45496a: test eax, eax */
	if (m->zf) goto L_45498c;	/* 45496c: je 0x45498c */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 45496e: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454972: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 454973: push 0 */
	m->esp -= 4; M32(m->esp) = 0x45497au; native_call(m, 0x453a90u);	/* 454975: call 0x453a90 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45497a: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45497d: test eax, eax */
	if (m->zf) goto L_45499b;	/* 45497f: je 0x45499b */
	m->eax = 0x1u;	/* 454981: mov eax, 1 */
	M32((DWORD)(0xa0d7a4u)) = m->eax;	/* 454986: mov dword ptr [0xa0d7a4], eax */
	m->esp += 4 + 0; return;	/* 45498b: ret  */
L_45498c:
	M32((DWORD)(0xa0d7a4u)) = 0x0u;	/* 45498c: mov dword ptr [0xa0d7a4], 0 */
	m->esp -= 4; M32(m->esp) = 0x45499bu; native_call(m, 0x4549a0u);	/* 454996: call 0x4549a0 */
L_45499b:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45499b: xor eax, eax */
	m->esp += 4 + 0; return;	/* 45499d: ret  */
}

/* arena_454a50 (0x454a50), lifted by tools/lift.py */
static void lift_454a50(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7a8u));	/* 454a50: mov eax, dword ptr [0xa0d7a8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454a55: test eax, eax */
	if (m->zf) goto L_454a68;	/* 454a57: je 0x454a68 */
	m->esp -= 4; M32(m->esp) = 0x454a5eu; native_call(m, 0x454ac0u);	/* 454a59: call 0x454ac0 */
	M32((DWORD)(0xa0d7a8u)) = 0x0u;	/* 454a5e: mov dword ptr [0xa0d7a8], 0 */
L_454a68:
	m->esp -= 4; M32(m->esp) = 0x454a6du; native_call(m, 0x453720u);	/* 454a68: call 0x453720 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454a6d: test eax, eax */
	if (!m->zf) goto L_454ab1;	/* 454a6f: jne 0x454ab1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 454a71: push 1 */
	m->esp -= 4; M32(m->esp) = 0x454a78u; native_call(m, 0x453a30u);	/* 454a73: call 0x453a30 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454a78: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454a7b: test eax, eax */
	if (m->zf) goto L_454aa2;	/* 454a7d: je 0x454aa2 */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 454a7f: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454a83: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 454a84: push 1 */
	m->esp -= 4; M32(m->esp) = 0x454a8bu; native_call(m, 0x453a90u);	/* 454a86: call 0x453a90 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454a8b: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454a8e: test eax, eax */
	if (m->zf) goto L_454ab1;	/* 454a90: je 0x454ab1 */
	M32((DWORD)(0xa0d7a8u)) = 0x1u;	/* 454a92: mov dword ptr [0xa0d7a8], 1 */
	m->eax = 0x1u;	/* 454a9c: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 454aa1: ret  */
L_454aa2:
	M32((DWORD)(0xa0d7a8u)) = 0x0u;	/* 454aa2: mov dword ptr [0xa0d7a8], 0 */
	m->esp -= 4; M32(m->esp) = 0x454ab1u; native_call(m, 0x454ac0u);	/* 454aac: call 0x454ac0 */
L_454ab1:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454ab1: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454ab3: ret  */
}

/* arena_454b70 (0x454b70), lifted by tools/lift.py */
static void lift_454b70(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7acu));	/* 454b70: mov eax, dword ptr [0xa0d7ac] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454b75: test eax, eax */
	if (!m->zf) goto L_454bc3;	/* 454b77: jne 0x454bc3 */
	m->esp -= 4; M32(m->esp) = 0x454b7eu; native_call(m, 0x453720u);	/* 454b79: call 0x453720 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454b7e: test eax, eax */
	if (m->zf) goto L_454b85;	/* 454b80: je 0x454b85 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454b82: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454b84: ret  */
L_454b85:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 454b85: push 2 */
	m->esp -= 4; M32(m->esp) = 0x454b8cu; native_call(m, 0x453a30u);	/* 454b87: call 0x453a30 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454b8c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454b8f: test eax, eax */
	if (m->zf) goto L_454bb1;	/* 454b91: je 0x454bb1 */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 454b93: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454b97: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 454b98: push 2 */
	m->esp -= 4; M32(m->esp) = 0x454b9fu; native_call(m, 0x453a90u);	/* 454b9a: call 0x453a90 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454b9f: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454ba2: test eax, eax */
	if (m->zf) goto L_454bc0;	/* 454ba4: je 0x454bc0 */
	m->eax = 0x1u;	/* 454ba6: mov eax, 1 */
	M32((DWORD)(0xa0d7acu)) = m->eax;	/* 454bab: mov dword ptr [0xa0d7ac], eax */
	m->esp += 4 + 0; return;	/* 454bb0: ret  */
L_454bb1:
	M32((DWORD)(0xa0d7acu)) = 0x0u;	/* 454bb1: mov dword ptr [0xa0d7ac], 0 */
	m->esp -= 4; M32(m->esp) = 0x454bc0u; native_call(m, 0x454bd0u);	/* 454bbb: call 0x454bd0 */
L_454bc0:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454bc0: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454bc2: ret  */
L_454bc3:
	m->eax = 0x1u;	/* 454bc3: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 454bc8: ret  */
}

/* arena_454c80 (0x454c80), lifted by tools/lift.py */
static void lift_454c80(X86 *m)
{
	m->eax = M32((DWORD)(0xa0d7b0u));	/* 454c80: mov eax, dword ptr [0xa0d7b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454c85: test eax, eax */
	if (!m->zf) goto L_454cd3;	/* 454c87: jne 0x454cd3 */
	m->esp -= 4; M32(m->esp) = 0x454c8eu; native_call(m, 0x453720u);	/* 454c89: call 0x453720 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454c8e: test eax, eax */
	if (m->zf) goto L_454c95;	/* 454c90: je 0x454c95 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454c92: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454c94: ret  */
L_454c95:
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 454c95: push 3 */
	m->esp -= 4; M32(m->esp) = 0x454c9cu; native_call(m, 0x453a30u);	/* 454c97: call 0x453a30 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454c9c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454c9f: test eax, eax */
	if (m->zf) goto L_454cc1;	/* 454ca1: je 0x454cc1 */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 454ca3: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454ca7: push eax */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 454ca8: push 3 */
	m->esp -= 4; M32(m->esp) = 0x454cafu; native_call(m, 0x453a90u);	/* 454caa: call 0x453a90 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454caf: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454cb2: test eax, eax */
	if (m->zf) goto L_454cd0;	/* 454cb4: je 0x454cd0 */
	m->eax = 0x1u;	/* 454cb6: mov eax, 1 */
	M32((DWORD)(0xa0d7b0u)) = m->eax;	/* 454cbb: mov dword ptr [0xa0d7b0], eax */
	m->esp += 4 + 0; return;	/* 454cc0: ret  */
L_454cc1:
	M32((DWORD)(0xa0d7b0u)) = 0x0u;	/* 454cc1: mov dword ptr [0xa0d7b0], 0 */
	m->esp -= 4; M32(m->esp) = 0x454cd0u; native_call(m, 0x454ce0u);	/* 454ccb: call 0x454ce0 */
L_454cd0:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454cd0: xor eax, eax */
	m->esp += 4 + 0; return;	/* 454cd2: ret  */
L_454cd3:
	m->eax = 0x1u;	/* 454cd3: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 454cd8: ret  */
}

/* room_435c20 (0x435c20), lifted by tools/lift.py */
static void lift_435c20(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded8cu));	/* 435c20: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435c25: test eax, eax */
	if (m->zf) goto L_435c38;	/* 435c27: je 0x435c38 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435c29: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435c30u; native_call(m, 0x41e760u);	/* 435c2b: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435c30: add esp, 4 */
	native_call(m, 0x434640u); return;	/* 435c33: jmp 0x434640 */
L_435c38:
	m->eax = M32((DWORD)(0x4ded88u));	/* 435c38: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435c3d: test eax, eax */
	if (m->zf) goto L_435c71;	/* 435c3f: je 0x435c71 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 435c41: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 435c46: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435c4c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435c4d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x435c53u; native_call(m, 0x432240u);	/* 435c4e: call 0x432240 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435c53: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435c56: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_435c71;	/* 435c59: ja 0x435c71 */
	switch (m->eax) { case 0: goto L_435c62; case 1: goto L_435c72; case 2: goto L_435c82; case 3: goto L_435c92; case 4: goto L_435ca2; case 5: goto L_435cb1; default: abort(); }	/* 435c5b: jmp dword ptr [eax*4 + 0x435cc0] */
L_435c62:
	m->esp -= 4; M32(m->esp) = 0x435c67u; native_call(m, 0x433d30u);	/* 435c62: call 0x433d30 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435c67: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435c6eu; native_call(m, 0x433e60u);	/* 435c69: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435c6e: add esp, 4 */
L_435c71:
	m->esp += 4 + 0; return;	/* 435c71: ret  */
L_435c72:
	m->esp -= 4; M32(m->esp) = 0x435c77u; native_call(m, 0x433d30u);	/* 435c72: call 0x433d30 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 435c77: push 1 */
	m->esp -= 4; M32(m->esp) = 0x435c7eu; native_call(m, 0x433e60u);	/* 435c79: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435c7e: add esp, 4 */
	m->esp += 4 + 0; return;	/* 435c81: ret  */
L_435c82:
	m->esp -= 4; M32(m->esp) = 0x435c87u; native_call(m, 0x433d30u);	/* 435c82: call 0x433d30 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 435c87: push 2 */
	m->esp -= 4; M32(m->esp) = 0x435c8eu; native_call(m, 0x433e60u);	/* 435c89: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435c8e: add esp, 4 */
	m->esp += 4 + 0; return;	/* 435c91: ret  */
L_435c92:
	m->esp -= 4; M32(m->esp) = 0x435c97u; native_call(m, 0x433d30u);	/* 435c92: call 0x433d30 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 435c97: push 3 */
	m->esp -= 4; M32(m->esp) = 0x435c9eu; native_call(m, 0x433e60u);	/* 435c99: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435c9e: add esp, 4 */
	m->esp += 4 + 0; return;	/* 435ca1: ret  */
L_435ca2:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435ca2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435ca9u; native_call(m, 0x41e760u);	/* 435ca4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435ca9: add esp, 4 */
	native_call(m, 0x4346c0u); return;	/* 435cac: jmp 0x4346c0 */
L_435cb1:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435cb1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435cb8u; native_call(m, 0x41e760u);	/* 435cb3: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435cb8: add esp, 4 */
	native_call(m, 0x434640u); return;	/* 435cbb: jmp 0x434640 */
}

/* match_4620e0 (0x4620e0), lifted by tools/lift.py */
static void lift_4620e0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4620e0: push esi */
	m->esi = m->ecx;	/* 4620e1: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4620e3: push edi */
	m->edi = 0x10u;	/* 4620e4: mov edi, 0x10 */
	m->edx = (DWORD)(m->esi + 0x1755278u);	/* 4620e9: lea edx, [esi + 0x1755278] */
	m->eax = (DWORD)(m->esi + 0x1eccb54u);	/* 4620ef: lea eax, [esi + 0x1eccb54] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4620f5: xor ecx, ecx */
L_4620f7:
	M32((DWORD)(m->eax + 0xfffffff4u)) = m->ecx;	/* 4620f7: mov dword ptr [eax - 0xc], ecx */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 4620fa: mov dword ptr [eax], ecx */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 4620fc: mov dword ptr [eax + 4], ecx */
	M32((DWORD)(m->eax + 0xcu)) = m->ecx;	/* 4620ff: mov dword ptr [eax + 0xc], ecx */
	M32((DWORD)(m->eax + 0x10u)) = m->ecx;	/* 462102: mov dword ptr [eax + 0x10], ecx */
	M32((DWORD)(m->eax + 0x18u)) = m->ecx;	/* 462105: mov dword ptr [eax + 0x18], ecx */
	M32((DWORD)(m->eax + 0x1cu)) = m->ecx;	/* 462108: mov dword ptr [eax + 0x1c], ecx */
	M32((DWORD)(m->eax + 0x34u)) = 0xffffffffu;	/* 46210b: mov dword ptr [eax + 0x34], 0xffffffff */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 462112: cmp dword ptr [esi + 8], 1 */
	if (!m->zf) goto L_46211e;	/* 462116: jne 0x46211e */
	M32((DWORD)(m->edx + 0x0u)) = 0xffffffffu;	/* 462118: mov dword ptr [edx], 0xffffffff */
L_46211e:
	{ DWORD a_ = m->eax, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46211e: add eax, 0x8888 */
	{ DWORD a_ = m->edx, b_ = 0x47fd2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 462123: add edx, 0x47fd2 */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 462129: dec edi */
	if (!m->zf) goto L_4620f7;	/* 46212a: jne 0x4620f7 */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 46212c: lea ecx, [esi + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x462137u; native_call(m, 0x45df90u);	/* 462132: call 0x45df90 */
	m->ecx = m->esi;	/* 462137: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x46213eu; native_call(m, 0x462150u);	/* 462139: call 0x462150 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46213e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46213f: pop esi */
	m->esp += 4 + 0; return;	/* 462140: ret  */
}

/* arena_453090 (0x453090), lifted by tools/lift.py */
static void lift_453090(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b418u));	/* 453090: mov eax, dword ptr [0xa0b418] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 453095: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_453169;	/* 453098: ja 0x453169 */
	switch (m->eax) { case 0: goto L_4530a5; case 1: goto L_4530d6; case 2: goto L_453107; case 3: goto L_453138; default: abort(); }	/* 45309e: jmp dword ptr [eax*4 + 0x45316c] */
L_4530a5:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4530a5: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4530a9: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4530ad: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4530b1: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4530b2: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530b6: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4530b7: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530bb: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4530bc: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4530c0: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4530c1: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530c5: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4530c6: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530ca: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4530cb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530cc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4530d2u; native_call(m, 0x4549e0u);	/* 4530cd: call 0x4549e0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4530d2: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 4530d5: ret  */
L_4530d6:
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4530d6: mov edx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4530da: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4530de: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530e2: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4530e3: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4530e7: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4530e8: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530ec: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 4530ed: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530f1: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4530f2: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4530f6: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4530f7: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530fb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4530fc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4530fd: push eax */
	m->esp -= 4; M32(m->esp) = 0x453103u; native_call(m, 0x454b00u);	/* 4530fe: call 0x454b00 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453103: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 453106: ret  */
L_453107:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 453107: mov ecx, dword ptr [esp + 0x20] */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 45310b: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 45310f: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453113: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 453114: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453118: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 453119: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45311d: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 45311e: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453122: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 453123: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 453127: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 453128: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45312c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45312d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45312e: push edx */
	m->esp -= 4; M32(m->esp) = 0x453134u; native_call(m, 0x454c10u);	/* 45312f: call 0x454c10 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453134: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 453137: ret  */
L_453138:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 453138: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 45313c: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 453140: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453144: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 453145: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453149: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 45314a: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45314e: push edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 45314f: mov edx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 453153: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 453154: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 453158: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 453159: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45315d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45315e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45315f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x453165u; native_call(m, 0x454d20u);	/* 453160: call 0x454d20 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 453165: add esp, 0x20 */
	m->esp += 4 + 0; return;	/* 453168: ret  */
L_453169:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453169: xor eax, eax */
	m->esp += 4 + 0; return;	/* 45316b: ret  */
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
