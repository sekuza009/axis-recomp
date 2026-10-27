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

static void lift_447b40(X86 *m);
static void lift_447c70(X86 *m);
static void lift_44aa30(X86 *m);
static void lift_445bd0(X86 *m);
static void lift_4532e0(X86 *m);
static void lift_447c30(X86 *m);

/* menu_447c30 (0x447c30), lifted by tools/lift.py */
static void lift_447c30(X86 *m)
{
	m->eax = M32((DWORD)(0x76d48cu));	/* 447c30: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447c35: push eax */
	m->esp -= 4; M32(m->esp) = 0x447c3bu; native_call(m, 0x401600u);	/* 447c36: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447c3b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447c3e: cmp eax, 1 */
	if (m->zf) goto L_447c57;	/* 447c41: je 0x447c57 */
	m->ecx = M32((DWORD)(0x9dae70u));	/* 447c43: mov ecx, dword ptr [0x9dae70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 447c49: push ecx */
	m->esp -= 4; M32(m->esp) = 0x447c4fu; native_call(m, 0x401600u);	/* 447c4a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447c4f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447c52: cmp eax, 1 */
	if (!m->zf) goto L_447c61;	/* 447c55: jne 0x447c61 */
L_447c57:
	M32((DWORD)(0x9f62e0u)) = 0x0u;	/* 447c57: mov dword ptr [0x9f62e0], 0 */
L_447c61:
	m->esp += 4 + 0; return;	/* 447c61: ret  */
}

/* menu_447b40 (0x447b40), lifted by tools/lift.py */
static void lift_447b40(X86 *m)
{
	m->eax = M32((DWORD)(0x76d48cu));	/* 447b40: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447b45: push eax */
	m->esp -= 4; M32(m->esp) = 0x447b4bu; native_call(m, 0x401600u);	/* 447b46: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447b4b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447b4e: cmp eax, 1 */
	if (!m->zf) goto L_447b58;	/* 447b51: jne 0x447b58 */
	native_call(m, 0x447960u); return;	/* 447b53: jmp 0x447960 */
L_447b58:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 447b58: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 447b5e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x447b64u; native_call(m, 0x401600u);	/* 447b5f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447b64: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447b67: cmp eax, 1 */
	if (!m->zf) goto L_447b71;	/* 447b6a: jne 0x447b71 */
	native_call(m, 0x4479d0u); return;	/* 447b6c: jmp 0x4479d0 */
L_447b71:
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 447b71: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 447b77: push edx */
	m->esp -= 4; M32(m->esp) = 0x447b7du; native_call(m, 0x401600u);	/* 447b78: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447b7d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447b80: cmp eax, 1 */
	if (!m->zf) goto L_447b8a;	/* 447b83: jne 0x447b8a */
	native_call(m, 0x447960u); return;	/* 447b85: jmp 0x447960 */
L_447b8a:
	m->eax = M32((DWORD)(0x9dae14u));	/* 447b8a: mov eax, dword ptr [0x9dae14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447b8f: push eax */
	m->esp -= 4; M32(m->esp) = 0x447b95u; native_call(m, 0x401600u);	/* 447b90: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447b95: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447b98: cmp eax, 1 */
	if (!m->zf) goto L_447bb5;	/* 447b9b: jne 0x447bb5 */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 447b9d: mov eax, dword ptr [0x9f63b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447ba2: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_447bb5;	/* 447ba4: jle 0x447bb5 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 447ba6: dec eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447ba7: push eax */
	M32((DWORD)(0x9f63b4u)) = m->eax;	/* 447ba8: mov dword ptr [0x9f63b4], eax */
	m->esp -= 4; M32(m->esp) = 0x447bb2u; native_call(m, 0x4479b0u);	/* 447bad: call 0x4479b0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447bb2: add esp, 4 */
L_447bb5:
	m->ecx = M32((DWORD)(0x9db974u));	/* 447bb5: mov ecx, dword ptr [0x9db974] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 447bbb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x447bc1u; native_call(m, 0x401600u);	/* 447bbc: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447bc1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447bc4: cmp eax, 1 */
	if (!m->zf) goto L_447bec;	/* 447bc7: jne 0x447bec */
	m->eax = M32((DWORD)(0x9f63b4u));	/* 447bc9: mov eax, dword ptr [0x9f63b4] */
	m->ecx = M32((DWORD)(0x9f181cu));	/* 447bce: mov ecx, dword ptr [0x9f181c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447bd4: cmp eax, ecx */
	if (m->sf == m->of) goto L_447bec;	/* 447bd6: jge 0x447bec */
	{ DWORD a_ = m->eax, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447bd8: cmp eax, 0xe */
	if (m->sf == m->of) goto L_447c2e;	/* 447bdb: jge 0x447c2e */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 447bdd: inc eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447bde: push eax */
	M32((DWORD)(0x9f63b4u)) = m->eax;	/* 447bdf: mov dword ptr [0x9f63b4], eax */
	m->esp -= 4; M32(m->esp) = 0x447be9u; native_call(m, 0x4479b0u);	/* 447be4: call 0x4479b0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447be9: add esp, 4 */
L_447bec:
	m->edx = M32((DWORD)(0x6803a8u));	/* 447bec: mov edx, dword ptr [0x6803a8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 447bf2: push edx */
	m->esp -= 4; M32(m->esp) = 0x447bf8u; native_call(m, 0x401590u);	/* 447bf3: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447bf8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447bfb: test eax, eax */
	if (m->zf) goto L_447c2e;	/* 447bfd: je 0x447c2e */
	m->eax = M32((DWORD)(0x4df9fcu));	/* 447bff: mov eax, dword ptr [0x4df9fc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 447c04: push eax */
	m->esp -= 4; M32(m->esp) = 0x447c0au; native_call(m, 0x401590u);	/* 447c05: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447c0a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447c0d: test eax, eax */
	if (m->zf) goto L_447c2e;	/* 447c0f: je 0x447c2e */
	m->ecx = M32((DWORD)(0x4df90cu));	/* 447c11: mov ecx, dword ptr [0x4df90c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 447c17: push ecx */
	m->esp -= 4; M32(m->esp) = 0x447c1du; native_call(m, 0x401600u);	/* 447c18: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 447c1d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447c20: test eax, eax */
	if (m->zf) goto L_447c2e;	/* 447c22: je 0x447c2e */
	M32((DWORD)(0x9f181cu)) = 0x10u;	/* 447c24: mov dword ptr [0x9f181c], 0x10 */
L_447c2e:
	m->esp += 4 + 0; return;	/* 447c2e: ret  */
}

/* menu_447c70 (0x447c70), lifted by tools/lift.py */
static void lift_447c70(X86 *m)
{
	m->eax = M32((DWORD)(0x9f62f8u));	/* 447c70: mov eax, dword ptr [0x9f62f8] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 447c75: cmp eax, 1 */
	if (m->zf) goto L_447ca3;	/* 447c78: je 0x447ca3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447c7a: test eax, eax */
	if (m->zf) goto L_447ca3;	/* 447c7c: je 0x447ca3 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 447c7e: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447c83: test eax, eax */
	if (!m->zf) goto L_447ca3;	/* 447c85: jne 0x447ca3 */
	m->eax = M32((DWORD)(0x9f6300u));	/* 447c87: mov eax, dword ptr [0x9f6300] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447c8c: test eax, eax */
	if (!m->zf) goto L_447ca3;	/* 447c8e: jne 0x447ca3 */
	m->eax = M32((DWORD)(0x9f62e0u));	/* 447c90: mov eax, dword ptr [0x9f62e0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 447c95: test eax, eax */
	if (m->zf) goto L_447c9e;	/* 447c97: je 0x447c9e */
	lift_447c30(m); return;	/* 447c99: jmp 0x447c30 */
L_447c9e:
	lift_447b40(m); return;	/* 447c9e: jmp 0x447b40 */
L_447ca3:
	m->esp += 4 + 0; return;	/* 447ca3: ret  */
}

/* missionsel_44aa30 (0x44aa30), lifted by tools/lift.py */
static void lift_44aa30(X86 *m)
{
	native_call(m, 0x449a50u); return;	/* 44aa30: jmp 0x449a50 */
}

/* skirmish_445bd0 (0x445bd0), lifted by tools/lift.py */
static void lift_445bd0(X86 *m)
{
	native_call(m, 0x4456b0u); return;	/* 445bd0: jmp 0x4456b0 */
}

/* jmp_net_getLocalAddress_4532e0 (0x4532e0), lifted by tools/lift.py */
static void lift_4532e0(X86 *m)
{
	native_call(m, 0x454220u); return;	/* 4532e0: jmp 0x454220 */
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
