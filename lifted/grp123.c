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

static void lift_4633c0(X86 *m);
static void lift_462f30(X86 *m);
static void lift_462f60(X86 *m);
static void lift_4633f0(X86 *m);
static void lift_462f90(X86 *m);
static void lift_462fd0(X86 *m);
static void lift_454c50(X86 *m);
static void lift_454d60(X86 *m);
static void lift_453720(X86 *m);
static void lift_406b60(X86 *m);
static void lift_403870(X86 *m);
static void lift_435f40(X86 *m);
static void lift_435e70(X86 *m);
static void lift_433c70(X86 *m);
static void lift_408110(X86 *m);
static void lift_422b70(X86 *m);
static void lift_422d20(X86 *m);
static void lift_407750(X86 *m);
static void lift_4220c0(X86 *m);
static void lift_406950(X86 *m);
static void lift_407300(X86 *m);
static void lift_407840(X86 *m);
static void lift_433d30(X86 *m);
static void lift_44f4b0(X86 *m);
static void lift_441810(X86 *m);
static void lift_463390(X86 *m);

/* msg_connectionLost (0x463390), lifted by tools/lift.py */
static void lift_463390(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 463390: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 463395: dec eax */
	if (m->zf) goto L_4633a2;	/* 463396: je 0x4633a2 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 463398: dec eax */
	if (!m->zf) goto L_4633b2;	/* 463399: jne 0x4633b2 */
	{ DWORD v_ = 0x4c4964u; m->esp -= 4; M32(m->esp) = v_; }	/* 46339b: push 0x4c4964 */
	goto L_4633a7;	/* 4633a0: jmp 0x4633a7 */
L_4633a2:
	{ DWORD v_ = 0x4c4938u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633a2: push 0x4c4938 */
L_4633a7:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633a7: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4633a9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4633afu; native_call(m, 0x4629f0u);	/* 4633aa: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4633af: add esp, 0xc */
L_4633b2:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633b2: push 0x64 */
	{ DWORD v_ = 0x15u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633b4: push 0x15 */
	m->esp -= 4; M32(m->esp) = 0x4633bbu; native_call(m, 0x456e50u);	/* 4633b6: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4633bb: add esp, 8 */
	m->esp += 4 + 0; return;	/* 4633be: ret  */
}

/* msg_networkUnstable (0x4633c0), lifted by tools/lift.py */
static void lift_4633c0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 4633c0: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4633c5: dec eax */
	if (m->zf) goto L_4633d2;	/* 4633c6: je 0x4633d2 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4633c8: dec eax */
	if (!m->zf) goto L_4633e2;	/* 4633c9: jne 0x4633e2 */
	{ DWORD v_ = 0x4c49c0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633cb: push 0x4c49c0 */
	goto L_4633d7;	/* 4633d0: jmp 0x4633d7 */
L_4633d2:
	{ DWORD v_ = 0x4c4990u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633d2: push 0x4c4990 */
L_4633d7:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633d7: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4633d9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4633dfu; native_call(m, 0x4629f0u);	/* 4633da: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4633df: add esp, 0xc */
L_4633e2:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633e2: push 0x64 */
	{ DWORD v_ = 0x15u; m->esp -= 4; M32(m->esp) = v_; }	/* 4633e4: push 0x15 */
	m->esp -= 4; M32(m->esp) = 0x4633ebu; native_call(m, 0x456e50u);	/* 4633e6: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4633eb: add esp, 8 */
	m->esp += 4 + 0; return;	/* 4633ee: ret  */
}

/* msg_serverEndsGame (0x462f30), lifted by tools/lift.py */
static void lift_462f30(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 462f30: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462f35: dec eax */
	if (m->zf) goto L_462f42;	/* 462f36: je 0x462f42 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462f38: dec eax */
	if (!m->zf) goto L_462f52;	/* 462f39: jne 0x462f52 */
	{ DWORD v_ = 0x4c47c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f3b: push 0x4c47c8 */
	goto L_462f47;	/* 462f40: jmp 0x462f47 */
L_462f42:
	{ DWORD v_ = 0x4c47acu; m->esp -= 4; M32(m->esp) = v_; }	/* 462f42: push 0x4c47ac */
L_462f47:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f47: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 462f49: push ecx */
	m->esp -= 4; M32(m->esp) = 0x462f4fu; native_call(m, 0x4629f0u);	/* 462f4a: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462f4f: add esp, 0xc */
L_462f52:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f52: push 0x64 */
	{ DWORD v_ = 0x16u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f54: push 0x16 */
	m->esp -= 4; M32(m->esp) = 0x462f5bu; native_call(m, 0x456e50u);	/* 462f56: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462f5b: add esp, 8 */
	m->esp += 4 + 0; return;	/* 462f5e: ret  */
}

/* msg_userEndsGame (0x462f60), lifted by tools/lift.py */
static void lift_462f60(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 462f60: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462f65: dec eax */
	if (m->zf) goto L_462f72;	/* 462f66: je 0x462f72 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462f68: dec eax */
	if (!m->zf) goto L_462f82;	/* 462f69: jne 0x462f82 */
	{ DWORD v_ = 0x4c4800u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f6b: push 0x4c4800 */
	goto L_462f77;	/* 462f70: jmp 0x462f77 */
L_462f72:
	{ DWORD v_ = 0x4c47e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f72: push 0x4c47e4 */
L_462f77:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f77: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 462f79: push ecx */
	m->esp -= 4; M32(m->esp) = 0x462f7fu; native_call(m, 0x4629f0u);	/* 462f7a: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462f7f: add esp, 0xc */
L_462f82:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f82: push 0x64 */
	{ DWORD v_ = 0x16u; m->esp -= 4; M32(m->esp) = v_; }	/* 462f84: push 0x16 */
	m->esp -= 4; M32(m->esp) = 0x462f8bu; native_call(m, 0x456e50u);	/* 462f86: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462f8b: add esp, 8 */
	m->esp += 4 + 0; return;	/* 462f8e: ret  */
}

/* msg_dataLoss (0x4633f0), lifted by tools/lift.py */
static void lift_4633f0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 4633f0: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4633f5: dec eax */
	if (m->zf) goto L_463409;	/* 4633f6: je 0x463409 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4633f8: dec eax */
	if (!m->zf) goto L_463420;	/* 4633f9: jne 0x463420 */
	m->eax = M32((DWORD)(m->ecx + 0x2342401u));	/* 4633fb: mov eax, dword ptr [ecx + 0x2342401] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 463401: push eax */
	{ DWORD v_ = 0x4c4a18u; m->esp -= 4; M32(m->esp) = v_; }	/* 463402: push 0x4c4a18 */
	goto L_463415;	/* 463407: jmp 0x463415 */
L_463409:
	m->edx = M32((DWORD)(m->ecx + 0x2342401u));	/* 463409: mov edx, dword ptr [ecx + 0x2342401] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46340f: push edx */
	{ DWORD v_ = 0x4c49f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 463410: push 0x4c49f0 */
L_463415:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 463415: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 463417: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46341du; native_call(m, 0x4629f0u);	/* 463418: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46341d: add esp, 0x10 */
L_463420:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 463420: push 0x64 */
	{ DWORD v_ = 0x15u; m->esp -= 4; M32(m->esp) = v_; }	/* 463422: push 0x15 */
	m->esp -= 4; M32(m->esp) = 0x463429u; native_call(m, 0x456e50u);	/* 463424: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463429: add esp, 8 */
	m->esp += 4 + 0; return;	/* 46342c: ret  */
}

/* msg_fragLimitReached (0x462f90), lifted by tools/lift.py */
static void lift_462f90(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 462f90: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462f95: dec eax */
	if (m->zf) goto L_462fa9;	/* 462f96: je 0x462fa9 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462f98: dec eax */
	if (!m->zf) goto L_462fc0;	/* 462f99: jne 0x462fc0 */
	m->eax = M32((DWORD)(m->ecx + 0x23423adu));	/* 462f9b: mov eax, dword ptr [ecx + 0x23423ad] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462fa1: push eax */
	{ DWORD v_ = 0x4c4838u; m->esp -= 4; M32(m->esp) = v_; }	/* 462fa2: push 0x4c4838 */
	goto L_462fb5;	/* 462fa7: jmp 0x462fb5 */
L_462fa9:
	m->edx = M32((DWORD)(m->ecx + 0x23423adu));	/* 462fa9: mov edx, dword ptr [ecx + 0x23423ad] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462faf: push edx */
	{ DWORD v_ = 0x4c4818u; m->esp -= 4; M32(m->esp) = v_; }	/* 462fb0: push 0x4c4818 */
L_462fb5:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 462fb5: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 462fb7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x462fbdu; native_call(m, 0x4629f0u);	/* 462fb8: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462fbd: add esp, 0x10 */
L_462fc0:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 462fc0: push 0x64 */
	{ DWORD v_ = 0x15u; m->esp -= 4; M32(m->esp) = v_; }	/* 462fc2: push 0x15 */
	m->esp -= 4; M32(m->esp) = 0x462fc9u; native_call(m, 0x456e50u);	/* 462fc4: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462fc9: add esp, 8 */
	m->esp += 4 + 0; return;	/* 462fcc: ret  */
}

/* msg_timeLimitReached (0x462fd0), lifted by tools/lift.py */
static void lift_462fd0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dae74u));	/* 462fd0: mov eax, dword ptr [0x9dae74] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462fd5: dec eax */
	if (m->zf) goto L_462fe9;	/* 462fd6: je 0x462fe9 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 462fd8: dec eax */
	if (!m->zf) goto L_463000;	/* 462fd9: jne 0x463000 */
	m->eax = M32((DWORD)(m->ecx + 0x23423b1u));	/* 462fdb: mov eax, dword ptr [ecx + 0x23423b1] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 462fe1: push eax */
	{ DWORD v_ = 0x4c4874u; m->esp -= 4; M32(m->esp) = v_; }	/* 462fe2: push 0x4c4874 */
	goto L_462ff5;	/* 462fe7: jmp 0x462ff5 */
L_462fe9:
	m->edx = M32((DWORD)(m->ecx + 0x23423b1u));	/* 462fe9: mov edx, dword ptr [ecx + 0x23423b1] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 462fef: push edx */
	{ DWORD v_ = 0x4c4850u; m->esp -= 4; M32(m->esp) = v_; }	/* 462ff0: push 0x4c4850 */
L_462ff5:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 462ff5: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 462ff7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x462ffdu; native_call(m, 0x4629f0u);	/* 462ff8: call 0x4629f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 462ffd: add esp, 0x10 */
L_463000:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 463000: push 0x64 */
	{ DWORD v_ = 0x15u; m->esp -= 4; M32(m->esp) = v_; }	/* 463002: push 0x15 */
	m->esp -= 4; M32(m->esp) = 0x463009u; native_call(m, 0x456e50u);	/* 463004: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 463009: add esp, 8 */
	m->esp += 4 + 0; return;	/* 46300c: ret  */
}

/* arena_454c50 (0x454c50), lifted by tools/lift.py */
static void lift_454c50(X86 *m)
{
	m->ecx = M32((DWORD)(0xa0d7acu));	/* 454c50: mov ecx, dword ptr [0xa0d7ac] */
	m->eax = 0x1f4u;	/* 454c56: mov eax, 0x1f4 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454c5b: test ecx, ecx */
	if (m->zf) goto L_454c7b;	/* 454c5d: je 0x454c7b */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 454c5f: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 454c63: mov ecx, dword ptr [esp + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 454c67: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454c6b: push eax */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 454c6c: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454c70: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454c71: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454c72: push eax */
	m->esp -= 4; M32(m->esp) = 0x454c78u; native_call(m, 0x453e60u);	/* 454c73: call 0x453e60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454c78: add esp, 0x10 */
L_454c7b:
	m->esp += 4 + 0; return;	/* 454c7b: ret  */
}

/* arena_454d60 (0x454d60), lifted by tools/lift.py */
static void lift_454d60(X86 *m)
{
	m->ecx = M32((DWORD)(0xa0d7b0u));	/* 454d60: mov ecx, dword ptr [0xa0d7b0] */
	m->eax = 0x1f4u;	/* 454d66: mov eax, 0x1f4 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454d6b: test ecx, ecx */
	if (m->zf) goto L_454d8b;	/* 454d6d: je 0x454d8b */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 454d6f: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0xcu));	/* 454d73: mov ecx, dword ptr [esp + 0xc] */
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 454d77: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454d7b: push eax */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 454d7c: mov eax, dword ptr [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d80: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454d81: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454d82: push eax */
	m->esp -= 4; M32(m->esp) = 0x454d88u; native_call(m, 0x453e60u);	/* 454d83: call 0x453e60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454d88: add esp, 0x10 */
L_454d8b:
	m->esp += 4 + 0; return;	/* 454d8b: ret  */
}

/* dplay_coInit (0x453720), lifted by tools/lift.py */
static void lift_453720(X86 *m)
{
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453720: xor eax, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 453722: push esi */
	M32((DWORD)(0xa0b42cu)) = m->eax;	/* 453723: mov dword ptr [0xa0b42c], eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 453728: push edi */
	M32((DWORD)(0xa0b430u)) = m->eax;	/* 453729: mov dword ptr [0xa0b430], eax */
	m->ecx = 0x190u;	/* 45372e: mov ecx, 0x190 */
	M32((DWORD)(0xa0b434u)) = m->eax;	/* 453733: mov dword ptr [0xa0b434], eax */
	m->edi = 0xa0b470u;	/* 453738: mov edi, 0xa0b470 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 45373d: rep stosd dword ptr es:[edi], eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45373f: push eax */
	M32((DWORD)(0xa0b438u)) = m->eax;	/* 453740: mov dword ptr [0xa0b438], eax */
	m->esp -= 4; M32(m->esp) = 0x45374bu; native_call(m, M32(0x4a93bcu));	/* 453745: call dword ptr [0x4a93bc] */
	m->esi = m->eax;	/* 45374b: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45374d: test esi, esi */
	if (m->sf != m->of) goto L_45375c;	/* 45374f: jl 0x45375c */
	m->esp -= 4; M32(m->esp) = 0x453756u; native_call(m, 0x453770u);	/* 453751: call 0x453770 */
	m->esi = m->eax;	/* 453756: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 453758: test esi, esi */
	if (m->sf == m->of) goto L_453766;	/* 45375a: jge 0x453766 */
L_45375c:
	m->esp -= 4; M32(m->esp) = 0x453761u; native_call(m, 0x453920u);	/* 45375c: call 0x453920 */
	m->eax = m->esi;	/* 453761: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 453763: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 453764: pop esi */
	m->esp += 4 + 0; return;	/* 453765: ret  */
L_453766:
	m->edi = M32(m->esp); m->esp += 4;	/* 453766: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 453767: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 453769: pop esi */
	m->esp += 4 + 0; return;	/* 45376a: ret  */
}

/* lobby_close (0x406b60), lifted by tools/lift.py */
static void lift_406b60(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 406b60: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406b65: test eax, eax */
	if (!m->zf) goto L_406bc9;	/* 406b67: jne 0x406bc9 */
	m->eax = M32((DWORD)(0x4ded88u));	/* 406b69: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406b6e: test eax, eax */
	if (m->zf) goto L_406bc9;	/* 406b70: je 0x406bc9 */
	{ DWORD a_ = M32((DWORD)(0x4dbb3cu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406b72: cmp dword ptr [0x4dbb3c], 2 */
	if (!m->zf) goto L_406bc9;	/* 406b79: jne 0x406bc9 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 406b7b: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 406b80: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 406b86: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 406b87: push ecx */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 406b88: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x406b97u; native_call(m, 0x4044e0u);	/* 406b92: call 0x4044e0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406b97: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406b9a: test eax, eax */
	if (!m->zf) goto L_406bc9;	/* 406b9c: jne 0x406bc9 */
	M32((DWORD)(0x4dbb10u)) = m->eax;	/* 406b9e: mov dword ptr [0x4dbb10], eax */
	M32((DWORD)(0x4dbb78u)) = m->eax;	/* 406ba3: mov dword ptr [0x4dbb78], eax */
	m->esp -= 4; M32(m->esp) = 0x406badu; native_call(m, 0x452fe0u);	/* 406ba8: call 0x452fe0 */
	m->edx = M32((DWORD)(0x4ded18u));	/* 406bad: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x378u; m->esp -= 4; M32(m->esp) = v_; }	/* 406bb3: push 0x378 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 406bb8: push edx */
	M32((DWORD)(0x4db8b4u)) = 0x0u;	/* 406bb9: mov dword ptr [0x4db8b4], 0 */
	m->esp -= 4; M32(m->esp) = 0x406bc9u; native_call(m, M32(0x4a9330u));	/* 406bc3: call dword ptr [0x4a9330] */
L_406bc9:
	m->esp += 4 + 0; return;	/* 406bc9: ret  */
}

/* FUN_00403870 (0x403870), lifted by tools/lift.py */
static void lift_403870(X86 *m)
{
	m->eax = M32((DWORD)(0x4e1510u));	/* 403870: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403875: push eax */
	m->esp -= 4; M32(m->esp) = 0x40387bu; native_call(m, 0x401600u);	/* 403876: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40387b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40387e: test eax, eax */
	if (m->zf) goto L_403887;	/* 403880: je 0x403887 */
	native_call(m, 0x403640u); return;	/* 403882: jmp 0x403640 */
L_403887:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 403887: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40388d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x403893u; native_call(m, 0x401600u);	/* 40388e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403893: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 403896: test eax, eax */
	if (m->zf) goto L_4038af;	/* 403898: je 0x4038af */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40389a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4038a1u; native_call(m, 0x41e760u);	/* 40389c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4038a1: add esp, 4 */
	M32((DWORD)(0x4db508u)) = 0x0u;	/* 4038a4: mov dword ptr [0x4db508], 0 */
L_4038ae:
	m->esp += 4 + 0; return;	/* 4038ae: ret  */
L_4038af:
	m->edx = M32((DWORD)(0x4e0cd4u));	/* 4038af: mov edx, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4038b5: push edx */
	m->esp -= 4; M32(m->esp) = 0x4038bbu; native_call(m, 0x401600u);	/* 4038b6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4038bb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4038be: test eax, eax */
	if (m->zf) goto L_4038c7;	/* 4038c0: je 0x4038c7 */
	native_call(m, 0x4034e0u); return;	/* 4038c2: jmp 0x4034e0 */
L_4038c7:
	m->eax = M32((DWORD)(0x4e0ce0u));	/* 4038c7: mov eax, dword ptr [0x4e0ce0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4038cc: push eax */
	m->esp -= 4; M32(m->esp) = 0x4038d2u; native_call(m, 0x401600u);	/* 4038cd: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4038d2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4038d5: test eax, eax */
	if (m->zf) goto L_4038ae;	/* 4038d7: je 0x4038ae */
	native_call(m, 0x403530u); return;	/* 4038d9: jmp 0x403530 */
}

/* room_435f40 (0x435f40), lifted by tools/lift.py */
static void lift_435f40(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 435f40: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435f45: test eax, eax */
	if (!m->zf) goto L_435fbc;	/* 435f47: jne 0x435fbc */
	m->eax = M32((DWORD)(0x4ded88u));	/* 435f49: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435f4e: test eax, eax */
	if (m->zf) goto L_435fbc;	/* 435f50: je 0x435fbc */
	{ DWORD a_ = M32((DWORD)(0x9dce48u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435f52: cmp dword ptr [0x9dce48], 2 */
	if (!m->zf) goto L_435fbc;	/* 435f59: jne 0x435fbc */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 435f5b: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 435f60: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435f66: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435f67: push ecx */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 435f68: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x435f77u; native_call(m, 0x432340u);	/* 435f72: call 0x432340 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435f77: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435f7a: test eax, eax */
	if (!m->zf) goto L_435fbc;	/* 435f7c: jne 0x435fbc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435f7e: push eax */
	m->esp -= 4; M32(m->esp) = 0x435f84u; native_call(m, 0x41e760u);	/* 435f7f: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435f84: add esp, 4 */
	M32((DWORD)(0x4dbb10u)) = 0x0u;	/* 435f87: mov dword ptr [0x4dbb10], 0 */
	M32((DWORD)(0x4dbb78u)) = 0x0u;	/* 435f91: mov dword ptr [0x4dbb78], 0 */
	m->esp -= 4; M32(m->esp) = 0x435fa0u; native_call(m, 0x452fe0u);	/* 435f9b: call 0x452fe0 */
	m->edx = M32((DWORD)(0x4ded18u));	/* 435fa0: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x378u; m->esp -= 4; M32(m->esp) = v_; }	/* 435fa6: push 0x378 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 435fab: push edx */
	M32((DWORD)(0x4db8b4u)) = 0x0u;	/* 435fac: mov dword ptr [0x4db8b4], 0 */
	m->esp -= 4; M32(m->esp) = 0x435fbcu; native_call(m, M32(0x4a9330u));	/* 435fb6: call dword ptr [0x4a9330] */
L_435fbc:
	m->esp += 4 + 0; return;	/* 435fbc: ret  */
}

/* room_435e70 (0x435e70), lifted by tools/lift.py */
static void lift_435e70(X86 *m)
{
	m->eax = M32((DWORD)(0x9dce48u));	/* 435e70: mov eax, dword ptr [0x9dce48] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435e75: cmp eax, 1 */
	if (m->zf) goto L_435f20;	/* 435e78: je 0x435f20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435e7e: test eax, eax */
	if (m->zf) goto L_435f20;	/* 435e80: je 0x435f20 */
	{ DWORD a_ = M32((DWORD)(0x9dd6d4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435e86: cmp dword ptr [0x9dd6d4], 1 */
	if (m->zf) goto L_435f20;	/* 435e8d: je 0x435f20 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 435e93: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435e98: test eax, eax */
	if (!m->zf) goto L_435f20;	/* 435e9a: jne 0x435f20 */
	m->eax = M32((DWORD)(0x68039cu));	/* 435ea0: mov eax, dword ptr [0x68039c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435ea5: test eax, eax */
	if (!m->zf) goto L_435f20;	/* 435ea7: jne 0x435f20 */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 435ea9: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435eae: test eax, eax */
	if (!m->zf) goto L_435f0c;	/* 435eb0: jne 0x435f0c */
	m->eax = M32((DWORD)(0x4ded88u));	/* 435eb2: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 435eb7: test eax, eax */
	if (m->zf) goto L_435f20;	/* 435eb9: je 0x435f20 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 435ebb: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 435ec0: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 435ec6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 435ec7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x435ecdu; native_call(m, 0x4322c0u);	/* 435ec8: call 0x4322c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435ecd: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435ed0: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_435f20;	/* 435ed3: ja 0x435f20 */
	switch (m->eax) { case 0: goto L_435edc; case 1: goto L_435ee1; case 2: goto L_435ee6; case 3: goto L_435eeb; case 4: goto L_435ef0; case 5: goto L_435f0c; default: abort(); }	/* 435ed5: jmp dword ptr [eax*4 + 0x435f24] */
L_435edc:
	native_call(m, 0x434020u); return;	/* 435edc: jmp 0x434020 */
L_435ee1:
	native_call(m, 0x4340e0u); return;	/* 435ee1: jmp 0x4340e0 */
L_435ee6:
	native_call(m, 0x4341a0u); return;	/* 435ee6: jmp 0x4341a0 */
L_435eeb:
	native_call(m, 0x434260u); return;	/* 435eeb: jmp 0x434260 */
L_435ef0:
	m->esp -= 4; M32(m->esp) = 0x435ef5u; native_call(m, 0x434b90u);	/* 435ef0: call 0x434b90 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 435ef5: cmp eax, 1 */
	if (m->zf) goto L_435f0c;	/* 435ef8: je 0x435f0c */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 435efa: push 5 */
	m->esp -= 4; M32(m->esp) = 0x435f01u; native_call(m, 0x41ee40u);	/* 435efc: call 0x41ee40 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 435f01: push 6 */
	m->esp -= 4; M32(m->esp) = 0x435f08u; native_call(m, 0x41e760u);	/* 435f03: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435f08: add esp, 8 */
	m->esp += 4 + 0; return;	/* 435f0b: ret  */
L_435f0c:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 435f0c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x435f13u; native_call(m, 0x41e760u);	/* 435f0e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 435f13: add esp, 4 */
	M32((DWORD)(0x9dce48u)) = 0x0u;	/* 435f16: mov dword ptr [0x9dce48], 0 */
L_435f20:
	m->esp += 4 + 0; return;	/* 435f20: ret  */
}

/* room_433c70 (0x433c70), lifted by tools/lift.py */
static void lift_433c70(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd888u));	/* 433c70: mov eax, dword ptr [0x9dd888] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 433c75: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 433c76: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 433c77: push eax */
	m->esp -= 4; M32(m->esp) = 0x433c7eu; native_call(m, M32(0x4a9344u));	/* 433c78: call dword ptr [0x4a9344] */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 433c7e: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 433c84: push ecx */
	m->esp -= 4; M32(m->esp) = 0x433c8bu; native_call(m, M32(0x4a935cu));	/* 433c85: call dword ptr [0x4a935c] */
	m->esi = 0x1u;	/* 433c8b: mov esi, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 433c90: push esi */
	m->esp -= 4; M32(m->esp) = 0x433c96u; native_call(m, 0x431600u);	/* 433c91: call 0x431600 */
	m->eax = M32((DWORD)(0x9dd1ccu));	/* 433c96: mov eax, dword ptr [0x9dd1cc] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433c9b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 433c9e: cmp eax, esi */
	if (!m->zf) goto L_433cdf;	/* 433ca0: jne 0x433cdf */
	m->ecx = 0x7u;	/* 433ca2: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433ca7: xor eax, eax */
	m->edi = 0x9dd1d8u;	/* 433ca9: mov edi, 0x9dd1d8 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 433cae: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 433cb0: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 433cb2: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433cb7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433cba: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433cbc: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433cbe: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433cc0: sub edi, ecx */
	M32((DWORD)(0x9dd1ccu)) = m->eax;	/* 433cc2: mov dword ptr [0x9dd1cc], eax */
	m->edx = m->ecx;	/* 433cc7: mov edx, ecx */
	m->esi = m->edi;	/* 433cc9: mov esi, edi */
	m->edi = 0x9dd1d8u;	/* 433ccb: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433cd0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433cd3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 433cd5: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433cd7: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433cda: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 433cdc: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433cdd: pop esi */
	m->esp += 4 + 0; return;	/* 433cde: ret  */
L_433cdf:
	{ DWORD a_ = M32((DWORD)(0x9dd6b0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 433cdf: cmp dword ptr [0x9dd6b0], esi */
	if (!m->zf) goto L_433d25;	/* 433ce5: jne 0x433d25 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433ce7: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 433ce9: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd1f6u)) = m->eax;	/* 433cee: mov dword ptr [0x9dd1f6], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433cf3: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd1fau)) = m->eax;	/* 433cf6: mov dword ptr [0x9dd1fa], eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433cfb: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433cfd: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433cff: sub edi, ecx */
	M32((DWORD)(0x9dd1feu)) = m->eax;	/* 433d01: mov dword ptr [0x9dd1fe], eax */
	m->edx = m->ecx;	/* 433d06: mov edx, ecx */
	m->esi = m->edi;	/* 433d08: mov esi, edi */
	m->edi = 0x9dd1f6u;	/* 433d0a: mov edi, 0x9dd1f6 */
	M32((DWORD)(0x4e1868u)) = m->eax;	/* 433d0f: mov dword ptr [0x4e1868], eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433d14: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433d17: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 433d19: mov ecx, edx */
	M32((DWORD)(0x9dd6b0u)) = m->eax;	/* 433d1b: mov dword ptr [0x9dd6b0], eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433d20: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433d23: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_433d25:
	m->edi = M32(m->esp); m->esp += 4;	/* 433d25: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433d26: pop esi */
	m->esp += 4 + 0; return;	/* 433d27: ret  */
}

/* lobby_keysQuit (0x408110), lifted by tools/lift.py */
static void lift_408110(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 408110: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408115: test eax, eax */
	if (!m->zf) goto L_4081e0;	/* 408117: jne 0x4081e0 */
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 40811d: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 408122: push eax */
	m->esp -= 4; M32(m->esp) = 0x408128u; native_call(m, 0x401600u);	/* 408123: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408128: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40812b: test eax, eax */
	if (m->zf) goto L_40813a;	/* 40812d: je 0x40813a */
	M32((DWORD)(0x4db55cu)) = 0x0u;	/* 40812f: mov dword ptr [0x4db55c], 0 */
	m->esp += 4 + 0; return;	/* 408139: ret  */
L_40813a:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 40813a: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 408140: push ecx */
	m->esp -= 4; M32(m->esp) = 0x408146u; native_call(m, 0x401600u);	/* 408141: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 408146: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408149: test eax, eax */
	if (m->zf) goto L_4081e0;	/* 40814b: je 0x4081e0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 408151: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 408152: push edi */
	M32((DWORD)(0x67ef14u)) = 0x1u;	/* 408153: mov dword ptr [0x67ef14], 1 */
	M32((DWORD)(0x67ef04u)) = 0x1u;	/* 40815d: mov dword ptr [0x67ef04], 1 */
	m->esp -= 4; M32(m->esp) = 0x40816cu; native_call(m, 0x457310u);	/* 408167: call 0x457310 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded42u)));	/* 40816c: movsx eax, byte ptr [0x4ded42] */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 408173: movsx edx, byte ptr [0x4ded40] */
	m->ecx = 0x8u;	/* 40817a: mov ecx, 8 */
	m->esi = 0x4ded20u;	/* 40817f: mov esi, 0x4ded20 */
	m->edi = 0x67fb44u;	/* 408184: mov edi, 0x67fb44 */
	M32((DWORD)(0x9da3e0u)) = m->eax;	/* 408189: mov dword ptr [0x9da3e0], eax */
	m->eax = M32((DWORD)(0x4ded44u));	/* 40818e: mov eax, dword ptr [0x4ded44] */
	M32((DWORD)(0x9dad94u)) = m->edx;	/* 408193: mov dword ptr [0x9dad94], edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 408199: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 40819b: movsx ecx, byte ptr [0x4ded43] */
	m->edx = m->eax;	/* 4081a2: mov edx, eax */
	M32((DWORD)(0x76d368u)) = m->ecx;	/* 4081a4: mov dword ptr [0x76d368], ecx */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4081aa: and edx, 0xff */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4081b0: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 4081b2: mov cl, ah */
	m->edi = M32(m->esp); m->esp += 4;	/* 4081b4: pop edi */
	M32((DWORD)(0x4df8e8u)) = m->edx;	/* 4081b5: mov dword ptr [0x4df8e8], edx */
	M32((DWORD)(0x76d408u)) = m->ecx;	/* 4081bb: mov dword ptr [0x76d408], ecx */
	M32((DWORD)(0x4dbb3cu)) = 0x0u;	/* 4081c1: mov dword ptr [0x4dbb3c], 0 */
	M32((DWORD)(0x4dbbf4u)) = 0x1u;	/* 4081cb: mov dword ptr [0x4dbbf4], 1 */
	M32((DWORD)(0x4db55cu)) = 0x0u;	/* 4081d5: mov dword ptr [0x4db55c], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4081df: pop esi */
L_4081e0:
	m->esp += 4 + 0; return;	/* 4081e0: ret  */
}

/* setup_topPageKeys (0x422b70), lifted by tools/lift.py */
static void lift_422b70(X86 *m)
{
	m->eax = M32((DWORD)(0x76d48cu));	/* 422b70: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422b75: push eax */
	m->esp -= 4; M32(m->esp) = 0x422b7bu; native_call(m, 0x401600u);	/* 422b76: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422b7b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422b7e: test eax, eax */
	if (m->zf) goto L_422bae;	/* 422b80: je 0x422bae */
	m->eax = M32((DWORD)(0x9dae10u));	/* 422b82: mov eax, dword ptr [0x9dae10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422b87: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_422bae;	/* 422b89: jle 0x422bae */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 422b8b: push 4 */
	m->esp -= 4; M32(m->esp) = 0x422b92u; native_call(m, 0x441250u);	/* 422b8d: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422b92: add esp, 4 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 422b95: mov dword ptr [0x67ef20], 0x12c */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 422b9f: mov dword ptr [0x4dda44], 0 */
	native_call(m, 0x48b420u); return;	/* 422ba9: jmp 0x48b420 */
L_422bae:
	m->ecx = M32((DWORD)(0x4e1524u));	/* 422bae: mov ecx, dword ptr [0x4e1524] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 422bb4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x422bbau; native_call(m, 0x401600u);	/* 422bb5: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422bba: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422bbd: cmp eax, 1 */
	if (!m->zf) goto L_422bd1;	/* 422bc0: jne 0x422bd1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422bc2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422bc9u; native_call(m, 0x41e760u);	/* 422bc4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422bc9: add esp, 4 */
	native_call(m, 0x420ad0u); return;	/* 422bcc: jmp 0x420ad0 */
L_422bd1:
	m->edx = M32((DWORD)(0x4e14ecu));	/* 422bd1: mov edx, dword ptr [0x4e14ec] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 422bd7: push edx */
	m->esp -= 4; M32(m->esp) = 0x422bddu; native_call(m, 0x401600u);	/* 422bd8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422bdd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422be0: cmp eax, 1 */
	if (!m->zf) goto L_422bf4;	/* 422be3: jne 0x422bf4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422be5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422becu; native_call(m, 0x41e760u);	/* 422be7: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422bec: add esp, 4 */
	native_call(m, 0x420b40u); return;	/* 422bef: jmp 0x420b40 */
L_422bf4:
	m->eax = M32((DWORD)(0x4e0cdcu));	/* 422bf4: mov eax, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422bf9: push eax */
	m->esp -= 4; M32(m->esp) = 0x422bffu; native_call(m, 0x401600u);	/* 422bfa: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422bff: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422c02: cmp eax, 1 */
	if (!m->zf) goto L_422c16;	/* 422c05: jne 0x422c16 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422c07: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422c0eu; native_call(m, 0x41e760u);	/* 422c09: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422c0e: add esp, 4 */
	native_call(m, 0x420ba0u); return;	/* 422c11: jmp 0x420ba0 */
L_422c16:
	m->ecx = M32((DWORD)(0x4e153cu));	/* 422c16: mov ecx, dword ptr [0x4e153c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 422c1c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x422c22u; native_call(m, 0x401600u);	/* 422c1d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422c22: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422c25: cmp eax, 1 */
	if (!m->zf) goto L_422c54;	/* 422c28: jne 0x422c54 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422c2a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422c31u; native_call(m, 0x41e760u);	/* 422c2c: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 422c31: push 4 */
	m->esp -= 4; M32(m->esp) = 0x422c38u; native_call(m, 0x441250u);	/* 422c33: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422c38: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 422c3b: mov dword ptr [0x67ef20], 0x12c */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 422c45: mov dword ptr [0x4dda44], 0 */
	native_call(m, 0x48b420u); return;	/* 422c4f: jmp 0x48b420 */
L_422c54:
	m->esp += 4 + 0; return;	/* 422c54: ret  */
}

/* setup_graphicTabKeys (0x422d20), lifted by tools/lift.py */
static void lift_422d20(X86 *m)
{
	m->eax = M32((DWORD)(0x4e0cd4u));	/* 422d20: mov eax, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 422d25: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 422d26: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422d27: push eax */
	m->esp -= 4; M32(m->esp) = 0x422d2du; native_call(m, 0x401600u);	/* 422d28: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422d2d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422d30: test eax, eax */
	if (m->zf) goto L_422dcb;	/* 422d32: je 0x422dcb */
	m->ecx = M32((DWORD)(0x83a9c4u));	/* 422d38: mov ecx, dword ptr [0x83a9c4] */
	m->eax = M32((DWORD)(0x4ddba4u));	/* 422d3e: mov eax, dword ptr [0x4ddba4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422d43: cmp ecx, eax */
	if (!m->zf) goto L_422da1;	/* 422d45: jne 0x422da1 */
	m->edx = M32((DWORD)(0x83a9c0u));	/* 422d47: mov edx, dword ptr [0x83a9c0] */
	m->eax = M32((DWORD)(0x4ddba0u));	/* 422d4d: mov eax, dword ptr [0x4ddba0] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422d52: cmp edx, eax */
	if (!m->zf) goto L_422da1;	/* 422d54: jne 0x422da1 */
	m->eax = M32((DWORD)(0x83a9ccu));	/* 422d56: mov eax, dword ptr [0x83a9cc] */
	m->ecx = M32((DWORD)(0x4ddbacu));	/* 422d5b: mov ecx, dword ptr [0x4ddbac] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422d61: cmp eax, ecx */
	if (!m->zf) goto L_422da1;	/* 422d63: jne 0x422da1 */
	m->ecx = M32((DWORD)(0x83a9d0u));	/* 422d65: mov ecx, dword ptr [0x83a9d0] */
	m->eax = M32((DWORD)(0x4ddbb0u));	/* 422d6b: mov eax, dword ptr [0x4ddbb0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422d70: cmp ecx, eax */
	if (!m->zf) goto L_422da1;	/* 422d72: jne 0x422da1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422d74: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422d7bu; native_call(m, 0x41e760u);	/* 422d76: call 0x41e760 */
	m->ecx = 0x7u;	/* 422d7b: mov ecx, 7 */
	m->esi = 0x4ddba0u;	/* 422d80: mov esi, 0x4ddba0 */
	m->edi = 0x83a9c0u;	/* 422d85: mov edi, 0x83a9c0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422d8a: add esp, 4 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 422d8d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x422d94u; native_call(m, 0x42d730u);	/* 422d8f: call 0x42d730 */
	m->edi = M32(m->esp); m->esp += 4;	/* 422d94: pop edi */
	M32((DWORD)(0x4ddcecu)) = 0x0u;	/* 422d95: mov dword ptr [0x4ddcec], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 422d9f: pop esi */
	m->esp += 4 + 0; return;	/* 422da0: ret  */
L_422da1:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422da1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422da8u; native_call(m, 0x41e760u);	/* 422da3: call 0x41e760 */
	m->ecx = 0x7u;	/* 422da8: mov ecx, 7 */
	m->esi = 0x4ddba0u;	/* 422dad: mov esi, 0x4ddba0 */
	m->edi = 0x83a9c0u;	/* 422db2: mov edi, 0x83a9c0 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 422db7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->esp -= 4; M32(m->esp) = 0x422dbeu; native_call(m, 0x42d730u);	/* 422db9: call 0x42d730 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 422dbe: push 1 */
	m->esp -= 4; M32(m->esp) = 0x422dc5u; native_call(m, 0x41e7a0u);	/* 422dc0: call 0x41e7a0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422dc5: add esp, 8 */
	m->edi = M32(m->esp); m->esp += 4;	/* 422dc8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422dc9: pop esi */
	m->esp += 4 + 0; return;	/* 422dca: ret  */
L_422dcb:
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 422dcb: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 422dd1: push edx */
	m->esp -= 4; M32(m->esp) = 0x422dd7u; native_call(m, 0x401600u);	/* 422dd2: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422dd7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422dda: test eax, eax */
	if (!m->zf) goto L_422df0;	/* 422ddc: jne 0x422df0 */
	m->eax = M32((DWORD)(0x76d48cu));	/* 422dde: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 422de3: push eax */
	m->esp -= 4; M32(m->esp) = 0x422de9u; native_call(m, 0x401600u);	/* 422de4: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422de9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422dec: test eax, eax */
	if (m->zf) goto L_422e04;	/* 422dee: je 0x422e04 */
L_422df0:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422df0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422df7u; native_call(m, 0x41e760u);	/* 422df2: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422df7: add esp, 4 */
	M32((DWORD)(0x4ddcecu)) = 0x0u;	/* 422dfa: mov dword ptr [0x4ddcec], 0 */
L_422e04:
	m->edi = M32(m->esp); m->esp += 4;	/* 422e04: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 422e05: pop esi */
	m->esp += 4 + 0; return;	/* 422e06: ret  */
}

/* lobbyTop_keys (0x407750), lifted by tools/lift.py */
static void lift_407750(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 407750: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407755: test eax, eax */
	if (!m->zf) goto L_40783d;	/* 407757: jne 0x40783d */
	{ DWORD a_ = M32((DWORD)(0x67ef14u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40775d: cmp dword ptr [0x67ef14], 1 */
	if (m->zf) goto L_40783d;	/* 407764: je 0x40783d */
	m->eax = M32((DWORD)(0x76d48cu));	/* 40776a: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40776f: push eax */
	m->esp -= 4; M32(m->esp) = 0x407775u; native_call(m, 0x401600u);	/* 407770: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407775: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407778: test eax, eax */
	if (m->zf) goto L_4077a5;	/* 40777a: je 0x4077a5 */
	m->eax = M32((DWORD)(0x9dae10u));	/* 40777c: mov eax, dword ptr [0x9dae10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407781: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4077a5;	/* 407783: jle 0x4077a5 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 407785: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40778cu; native_call(m, 0x41e760u);	/* 407787: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40778c: push 4 */
	m->esp -= 4; M32(m->esp) = 0x407793u; native_call(m, 0x441250u);	/* 40778e: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407793: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 407796: mov dword ptr [0x67ef20], 0x12c */
	native_call(m, 0x48b420u); return;	/* 4077a0: jmp 0x48b420 */
L_4077a5:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 4077a5: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4077ab: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4077b1u; native_call(m, 0x401600u);	/* 4077ac: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4077b1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4077b4: test eax, eax */
	if (m->zf) goto L_4077c7;	/* 4077b6: je 0x4077c7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4077b8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4077bfu; native_call(m, 0x41e760u);	/* 4077ba: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4077bf: add esp, 4 */
	native_call(m, 0x404c20u); return;	/* 4077c2: jmp 0x404c20 */
L_4077c7:
	m->edx = M32((DWORD)(0x4e1514u));	/* 4077c7: mov edx, dword ptr [0x4e1514] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4077cd: push edx */
	m->esp -= 4; M32(m->esp) = 0x4077d3u; native_call(m, 0x401600u);	/* 4077ce: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4077d3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4077d6: test eax, eax */
	if (m->zf) goto L_4077e9;	/* 4077d8: je 0x4077e9 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4077da: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4077e1u; native_call(m, 0x41e760u);	/* 4077dc: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4077e1: add esp, 4 */
	native_call(m, 0x404ac0u); return;	/* 4077e4: jmp 0x404ac0 */
L_4077e9:
	m->eax = M32((DWORD)(0x4e14f8u));	/* 4077e9: mov eax, dword ptr [0x4e14f8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4077ee: push eax */
	m->esp -= 4; M32(m->esp) = 0x4077f4u; native_call(m, 0x401600u);	/* 4077ef: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4077f4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4077f7: test eax, eax */
	if (m->zf) goto L_40780a;	/* 4077f9: je 0x40780a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4077fb: push 0 */
	m->esp -= 4; M32(m->esp) = 0x407802u; native_call(m, 0x41e760u);	/* 4077fd: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407802: add esp, 4 */
	native_call(m, 0x404b30u); return;	/* 407805: jmp 0x404b30 */
L_40780a:
	m->ecx = M32((DWORD)(0x4e153cu));	/* 40780a: mov ecx, dword ptr [0x4e153c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407810: push ecx */
	m->esp -= 4; M32(m->esp) = 0x407816u; native_call(m, 0x401600u);	/* 407811: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407816: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407819: test eax, eax */
	if (m->zf) goto L_40783d;	/* 40781b: je 0x40783d */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40781d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x407824u; native_call(m, 0x41e760u);	/* 40781f: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 407824: push 4 */
	m->esp -= 4; M32(m->esp) = 0x40782bu; native_call(m, 0x441250u);	/* 407826: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40782b: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 40782e: mov dword ptr [0x67ef20], 0x12c */
	native_call(m, 0x48b420u); return;	/* 407838: jmp 0x48b420 */
L_40783d:
	m->esp += 4 + 0; return;	/* 40783d: ret  */
}

/* setup_drawTopPage (0x4220c0), lifted by tools/lift.py */
static void lift_4220c0(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 4220c0: mov eax, dword ptr [0x4ded88] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4220c5: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4220c6: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4220c7: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4220c8: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4220ca: push edi */
	if (m->zf) goto L_422177;	/* 4220cb: je 0x422177 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4220d1: xor ebp, ebp */
	m->ebx = 0x4df918u;	/* 4220d3: mov ebx, 0x4df918 */
L_4220d8:
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4220d8: mov eax, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4220dd: sub esp, 0x2c */
	m->ecx = 0xbu;	/* 4220e0: mov ecx, 0xb */
	m->esi = m->ebx;	/* 4220e5: mov esi, ebx */
	m->edi = m->esp;	/* 4220e7: mov edi, esp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4220e9: push eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4220ea: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4220ec: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4220f2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4220f8u; native_call(m, 0x41eea0u);	/* 4220f3: call 0x41eea0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4220f8: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4220fb: cmp eax, 1 */
	if (m->zf) goto L_42210e;	/* 4220fe: je 0x42210e */
	{ DWORD a_ = m->ebx, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 422100: add ebx, 0x2c */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 422103: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x4df9c8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422104: cmp ebx, 0x4df9c8 */
	if (m->sf != m->of) goto L_4220d8;	/* 42210a: jl 0x4220d8 */
	goto L_422177;	/* 42210c: jmp 0x422177 */
L_42210e:
	{ DWORD a_ = m->ebp, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42210e: cmp ebp, 3 */
	if (!m->cf && !m->zf) goto L_422177;	/* 422111: ja 0x422177 */
	switch (m->ebp) { case 0: goto L_42211a; case 1: goto L_42212b; case 2: goto L_42213c; case 3: goto L_42214d; default: abort(); }	/* 422113: jmp dword ptr [ebp*4 + 0x4221b8] */
L_42211a:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42211a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422121u; native_call(m, 0x41e760u);	/* 42211c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422121: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x422129u; native_call(m, 0x420ad0u);	/* 422124: call 0x420ad0 */
	goto L_422177;	/* 422129: jmp 0x422177 */
L_42212b:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42212b: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422132u; native_call(m, 0x41e760u);	/* 42212d: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422132: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x42213au; native_call(m, 0x420b40u);	/* 422135: call 0x420b40 */
	goto L_422177;	/* 42213a: jmp 0x422177 */
L_42213c:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42213c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422143u; native_call(m, 0x41e760u);	/* 42213e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422143: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x42214bu; native_call(m, 0x420ba0u);	/* 422146: call 0x420ba0 */
	goto L_422177;	/* 42214b: jmp 0x422177 */
L_42214d:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42214d: push 4 */
	m->esp -= 4; M32(m->esp) = 0x422154u; native_call(m, 0x441250u);	/* 42214f: call 0x441250 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422154: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42215bu; native_call(m, 0x41e760u);	/* 422156: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42215b: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 42215e: mov dword ptr [0x67ef20], 0x12c */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 422168: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x422177u; native_call(m, 0x48b420u);	/* 422172: call 0x48b420 */
L_422177:
	m->eax = M32((DWORD)(0x4ded8cu));	/* 422177: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42217c: test eax, eax */
	if (m->zf) goto L_4221b3;	/* 42217e: je 0x4221b3 */
	m->eax = M32((DWORD)(0x9dae10u));	/* 422180: mov eax, dword ptr [0x9dae10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422185: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4221b3;	/* 422187: jle 0x4221b3 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 422189: push 0 */
	m->esp -= 4; M32(m->esp) = 0x422190u; native_call(m, 0x41e760u);	/* 42218b: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 422190: push 4 */
	m->esp -= 4; M32(m->esp) = 0x422197u; native_call(m, 0x441250u);	/* 422192: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 422197: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 42219a: mov dword ptr [0x67ef20], 0x12c */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4221a4: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x4221b3u; native_call(m, 0x48b420u);	/* 4221ae: call 0x48b420 */
L_4221b3:
	m->edi = M32(m->esp); m->esp += 4;	/* 4221b3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4221b4: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4221b5: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4221b6: pop ebx */
	m->esp += 4 + 0; return;	/* 4221b7: ret  */
}

/* lobby_406950 (0x406950), lifted by tools/lift.py */
static void lift_406950(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 406950: mov eax, dword ptr [0x90d1c4] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 406955: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 406956: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 406957: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406958: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40695a: push edi */
	if (!m->zf) goto L_406a49;	/* 40695b: jne 0x406a49 */
	{ DWORD a_ = M32((DWORD)(0x67ef14u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 406961: cmp dword ptr [0x67ef14], 1 */
	if (m->zf) goto L_406a49;	/* 406968: je 0x406a49 */
	m->eax = M32((DWORD)(0x4ded88u));	/* 40696e: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406973: test eax, eax */
	if (m->zf) goto L_406a17;	/* 406975: je 0x406a17 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 40697b: xor ebp, ebp */
	m->ebx = 0x5b1cf8u;	/* 40697d: mov ebx, 0x5b1cf8 */
L_406982:
	m->eax = M32((DWORD)(0x4ded6cu));	/* 406982: mov eax, dword ptr [0x4ded6c] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406987: sub esp, 0x2c */
	m->ecx = 0xbu;	/* 40698a: mov ecx, 0xb */
	m->esi = m->ebx;	/* 40698f: mov esi, ebx */
	m->edi = m->esp;	/* 406991: mov edi, esp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 406993: push eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 406994: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 406996: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40699c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4069a2u; native_call(m, 0x41eea0u);	/* 40699d: call 0x41eea0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4069a2: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4069a5: cmp eax, 1 */
	if (m->zf) goto L_4069b8;	/* 4069a8: je 0x4069b8 */
	{ DWORD a_ = m->ebx, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4069aa: add ebx, 0x2c */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 4069ad: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x5b1da8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4069ae: cmp ebx, 0x5b1da8 */
	if (m->sf != m->of) goto L_406982;	/* 4069b4: jl 0x406982 */
	goto L_406a17;	/* 4069b6: jmp 0x406a17 */
L_4069b8:
	{ DWORD a_ = m->ebp, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4069b8: cmp ebp, 3 */
	if (!m->cf && !m->zf) goto L_406a17;	/* 4069bb: ja 0x406a17 */
	switch (m->ebp) { case 0: goto L_4069c4; case 1: goto L_4069d5; case 2: goto L_4069e6; case 3: goto L_4069f7; default: abort(); }	/* 4069bd: jmp dword ptr [ebp*4 + 0x406a50] */
L_4069c4:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4069c4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4069cbu; native_call(m, 0x41e760u);	/* 4069c6: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4069cb: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4069d3u; native_call(m, 0x404ac0u);	/* 4069ce: call 0x404ac0 */
	goto L_406a17;	/* 4069d3: jmp 0x406a17 */
L_4069d5:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4069d5: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4069dcu; native_call(m, 0x41e760u);	/* 4069d7: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4069dc: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4069e4u; native_call(m, 0x404b30u);	/* 4069df: call 0x404b30 */
	goto L_406a17;	/* 4069e4: jmp 0x406a17 */
L_4069e6:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4069e6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4069edu; native_call(m, 0x41e760u);	/* 4069e8: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4069ed: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4069f5u; native_call(m, 0x404c20u);	/* 4069f0: call 0x404c20 */
	goto L_406a17;	/* 4069f5: jmp 0x406a17 */
L_4069f7:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4069f7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4069feu; native_call(m, 0x41e760u);	/* 4069f9: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4069fe: push 4 */
	m->esp -= 4; M32(m->esp) = 0x406a05u; native_call(m, 0x441250u);	/* 406a00: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406a05: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 406a08: mov dword ptr [0x67ef20], 0x12c */
	m->esp -= 4; M32(m->esp) = 0x406a17u; native_call(m, 0x48b420u);	/* 406a12: call 0x48b420 */
L_406a17:
	m->eax = M32((DWORD)(0x4ded8cu));	/* 406a17: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406a1c: test eax, eax */
	if (m->zf) goto L_406a49;	/* 406a1e: je 0x406a49 */
	m->eax = M32((DWORD)(0x9dae10u));	/* 406a20: mov eax, dword ptr [0x9dae10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 406a25: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_406a49;	/* 406a27: jle 0x406a49 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 406a29: push 0 */
	m->esp -= 4; M32(m->esp) = 0x406a30u; native_call(m, 0x41e760u);	/* 406a2b: call 0x41e760 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 406a30: push 4 */
	m->esp -= 4; M32(m->esp) = 0x406a37u; native_call(m, 0x441250u);	/* 406a32: call 0x441250 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 406a37: add esp, 8 */
	M32((DWORD)(0x67ef20u)) = 0x12cu;	/* 406a3a: mov dword ptr [0x67ef20], 0x12c */
	m->esp -= 4; M32(m->esp) = 0x406a49u; native_call(m, 0x48b420u);	/* 406a44: call 0x48b420 */
L_406a49:
	m->edi = M32(m->esp); m->esp += 4;	/* 406a49: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 406a4a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 406a4b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 406a4c: pop ebx */
	m->esp += 4 + 0; return;	/* 406a4d: ret  */
}

/* lobby_407300 (0x407300), lifted by tools/lift.py */
static void lift_407300(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbab0u));	/* 407300: mov eax, dword ptr [0x4dbab0] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 407305: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 407306: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407308: cmp eax, ebp */
	if (!m->zf) goto L_40740c;	/* 40730a: jne 0x40740c */
	{ DWORD a_ = M32((DWORD)(0x4db850u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407310: cmp dword ptr [0x4db850], ebp */
	if (!m->zf) goto L_40740c;	/* 407316: jne 0x40740c */
	{ DWORD a_ = M32((DWORD)(0x4db518u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40731c: cmp dword ptr [0x4db518], ebp */
	if (!m->zf) goto L_40740c;	/* 407322: jne 0x40740c */
	{ DWORD a_ = M32((DWORD)(0x4dbaccu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407328: cmp dword ptr [0x4dbacc], ebp */
	if (!m->zf) goto L_40740c;	/* 40732e: jne 0x40740c */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407334: cmp dword ptr [0x90d1c4], ebp */
	if (!m->zf) goto L_40740c;	/* 40733a: jne 0x40740c */
	{ DWORD a_ = M32((DWORD)(0x4ded8cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407340: cmp dword ptr [0x4ded8c], ebp */
	if (m->zf) goto L_407350;	/* 407346: je 0x407350 */
	M32((DWORD)(0x4db55cu)) = m->ebp;	/* 407348: mov dword ptr [0x4db55c], ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40734e: pop ebp */
	m->esp += 4 + 0; return;	/* 40734f: ret  */
L_407350:
	{ DWORD a_ = M32((DWORD)(0x4ded88u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407350: cmp dword ptr [0x4ded88], ebp */
	if (m->zf) goto L_40740c;	/* 407356: je 0x40740c */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 40735c: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 407361: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 407367: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407368: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40736eu; native_call(m, 0x404520u);	/* 407369: call 0x404520 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40736e: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 407371: sub eax, 0x10 */
	if (m->zf) goto L_407385;	/* 407374: je 0x407385 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 407376: dec eax */
	if (!m->zf) goto L_40740c;	/* 407377: jne 0x40740c */
	M32((DWORD)(0x4db55cu)) = m->ebp;	/* 40737d: mov dword ptr [0x4db55c], ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 407383: pop ebp */
	m->esp += 4 + 0; return;	/* 407384: ret  */
L_407385:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 407385: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 407386: push edi */
	M32((DWORD)(0x67ef14u)) = 0x1u;	/* 407387: mov dword ptr [0x67ef14], 1 */
	M32((DWORD)(0x67ef04u)) = 0x1u;	/* 407391: mov dword ptr [0x67ef04], 1 */
	m->esp -= 4; M32(m->esp) = 0x4073a0u; native_call(m, 0x457310u);	/* 40739b: call 0x457310 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded42u)));	/* 4073a0: movsx eax, byte ptr [0x4ded42] */
	m->edx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded40u)));	/* 4073a7: movsx edx, byte ptr [0x4ded40] */
	m->ecx = 0x8u;	/* 4073ae: mov ecx, 8 */
	m->esi = 0x4ded20u;	/* 4073b3: mov esi, 0x4ded20 */
	m->edi = 0x67fb44u;	/* 4073b8: mov edi, 0x67fb44 */
	M32((DWORD)(0x9da3e0u)) = m->eax;	/* 4073bd: mov dword ptr [0x9da3e0], eax */
	m->eax = M32((DWORD)(0x4ded44u));	/* 4073c2: mov eax, dword ptr [0x4ded44] */
	M32((DWORD)(0x9dad94u)) = m->edx;	/* 4073c7: mov dword ptr [0x9dad94], edx */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4073cd: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(0x4ded43u)));	/* 4073cf: movsx ecx, byte ptr [0x4ded43] */
	m->edx = m->eax;	/* 4073d6: mov edx, eax */
	M32((DWORD)(0x76d368u)) = m->ecx;	/* 4073d8: mov dword ptr [0x76d368], ecx */
	{ DWORD a_ = m->edx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4073de: and edx, 0xff */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4073e4: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 4073e6: mov cl, ah */
	m->edi = M32(m->esp); m->esp += 4;	/* 4073e8: pop edi */
	M32((DWORD)(0x4df8e8u)) = m->edx;	/* 4073e9: mov dword ptr [0x4df8e8], edx */
	M32((DWORD)(0x76d408u)) = m->ecx;	/* 4073ef: mov dword ptr [0x76d408], ecx */
	M32((DWORD)(0x4dbb3cu)) = m->ebp;	/* 4073f5: mov dword ptr [0x4dbb3c], ebp */
	M32((DWORD)(0x4dbbf4u)) = 0x1u;	/* 4073fb: mov dword ptr [0x4dbbf4], 1 */
	M32((DWORD)(0x4db55cu)) = m->ebp;	/* 407405: mov dword ptr [0x4db55c], ebp */
	m->esi = M32(m->esp); m->esp += 4;	/* 40740b: pop esi */
L_40740c:
	m->ebp = M32(m->esp); m->esp += 4;	/* 40740c: pop ebp */
	m->esp += 4 + 0; return;	/* 40740d: ret  */
}

/* lobbyPlayer_keys (0x407840), lifted by tools/lift.py */
static void lift_407840(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 407840: mov eax, dword ptr [0x4dbb3c] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 407845: push ebx */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407846: cmp eax, 1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 407849: push edi */
	if (m->zf) goto L_40795e;	/* 40784a: je 0x40795e */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 407850: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407852: cmp eax, ebx */
	if (m->zf) goto L_40795e;	/* 407854: je 0x40795e */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40785a: cmp dword ptr [0x90d1c4], ebx */
	if (!m->zf) goto L_40795e;	/* 407860: jne 0x40795e */
	{ DWORD a_ = M32((DWORD)(0x4dbbd0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 407866: cmp dword ptr [0x4dbbd0], ebx */
	if (m->zf) goto L_4078d0;	/* 40786c: je 0x4078d0 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40786e: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_40795e;	/* 407874: jne 0x40795e */
	m->edi = 0x9dc92cu;	/* 40787a: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40787f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 407882: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 407884: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 407886: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 407888: dec ecx */
	if (!m->zf) goto L_407894;	/* 407889: jne 0x407894 */
	M32((DWORD)(0x4dbbd0u)) = m->ebx;	/* 40788b: mov dword ptr [0x4dbbd0], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 407891: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 407892: pop ebx */
	m->esp += 4 + 0; return;	/* 407893: ret  */
L_407894:
	m->ecx = 0x8u;	/* 407894: mov ecx, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 407899: xor eax, eax */
	m->edi = 0x4db560u;	/* 40789b: mov edi, 0x4db560 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4078a0: push esi */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4078a1: rep stosd dword ptr es:[edi], eax */
	m->edi = 0x9dc92cu;	/* 4078a3: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4078a8: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4078ab: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4078ad: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4078af: sub edi, ecx */
	M32((DWORD)(0x4dbbd0u)) = m->ebx;	/* 4078b1: mov dword ptr [0x4dbbd0], ebx */
	m->eax = m->ecx;	/* 4078b7: mov eax, ecx */
	m->esi = m->edi;	/* 4078b9: mov esi, edi */
	m->edi = 0x4db560u;	/* 4078bb: mov edi, 0x4db560 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4078c0: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4078c3: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4078c5: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4078c7: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4078ca: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4078cc: pop esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4078cd: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4078ce: pop ebx */
	m->esp += 4 + 0; return;	/* 4078cf: ret  */
L_4078d0:
	m->ecx = M32((DWORD)(0x76d48cu));	/* 4078d0: mov ecx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4078d6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4078dcu; native_call(m, 0x401600u);	/* 4078d7: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4078dc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4078df: test eax, eax */
	if (m->zf) goto L_4078f2;	/* 4078e1: je 0x4078f2 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4078e3: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4078e9u; native_call(m, 0x41e760u);	/* 4078e4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4078e9: add esp, 4 */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 4078ec: mov dword ptr [0x4dbb3c], ebx */
L_4078f2:
	m->edx = M32((DWORD)(0x4e1510u));	/* 4078f2: mov edx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4078f8: push edx */
	m->esp -= 4; M32(m->esp) = 0x4078feu; native_call(m, 0x401600u);	/* 4078f9: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4078fe: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407901: test eax, eax */
	if (m->zf) goto L_407919;	/* 407903: je 0x407919 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 407905: push ebx */
	m->esp -= 4; M32(m->esp) = 0x40790bu; native_call(m, 0x41e760u);	/* 407906: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40790b: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x407913u; native_call(m, 0x4050a0u);	/* 40790e: call 0x4050a0 */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 407913: mov dword ptr [0x4dbb3c], ebx */
L_407919:
	m->eax = M32((DWORD)(0x4e0ce0u));	/* 407919: mov eax, dword ptr [0x4e0ce0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40791e: push eax */
	m->esp -= 4; M32(m->esp) = 0x407924u; native_call(m, 0x401600u);	/* 40791f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407924: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407927: test eax, eax */
	if (m->zf) goto L_40793c;	/* 407929: je 0x40793c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40792b: push ebx */
	m->esp -= 4; M32(m->esp) = 0x407931u; native_call(m, 0x41e760u);	/* 40792c: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407931: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x407939u; native_call(m, 0x4050f0u);	/* 407934: call 0x4050f0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 407939: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40793a: pop ebx */
	m->esp += 4 + 0; return;	/* 40793b: ret  */
L_40793c:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 40793c: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 407942: push ecx */
	m->esp -= 4; M32(m->esp) = 0x407948u; native_call(m, 0x401600u);	/* 407943: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407948: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40794b: test eax, eax */
	if (m->zf) goto L_40795e;	/* 40794d: je 0x40795e */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 40794f: push ebx */
	m->esp -= 4; M32(m->esp) = 0x407955u; native_call(m, 0x41e760u);	/* 407950: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 407955: add esp, 4 */
	M32((DWORD)(0x4dbb3cu)) = m->ebx;	/* 407958: mov dword ptr [0x4dbb3c], ebx */
L_40795e:
	m->edi = M32(m->esp); m->esp += 4;	/* 40795e: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 40795f: pop ebx */
	m->esp += 4 + 0; return;	/* 407960: ret  */
}

/* room_433d30 (0x433d30), lifted by tools/lift.py */
static void lift_433d30(X86 *m)
{
	m->eax = M32((DWORD)(0x68039cu));	/* 433d30: mov eax, dword ptr [0x68039c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 433d35: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 433d36: test eax, eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 433d38: push edi */
	m->esi = 0x1u;	/* 433d39: mov esi, 1 */
	if (m->zf) goto L_433d62;	/* 433d3e: je 0x433d62 */
	m->eax = M32((DWORD)(0x9dd888u));	/* 433d40: mov eax, dword ptr [0x9dd888] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 433d45: push eax */
	m->esp -= 4; M32(m->esp) = 0x433d4cu; native_call(m, M32(0x4a9344u));	/* 433d46: call dword ptr [0x4a9344] */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 433d4c: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 433d52: push ecx */
	m->esp -= 4; M32(m->esp) = 0x433d59u; native_call(m, M32(0x4a935cu));	/* 433d53: call dword ptr [0x4a935c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 433d59: push esi */
	m->esp -= 4; M32(m->esp) = 0x433d5fu; native_call(m, 0x431600u);	/* 433d5a: call 0x431600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 433d5f: add esp, 4 */
L_433d62:
	{ DWORD a_ = M32((DWORD)(0x9dd348u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 433d62: cmp dword ptr [0x9dd348], esi */
	if (!m->zf) goto L_433da2;	/* 433d68: jne 0x433da2 */
	m->ecx = 0x7u;	/* 433d6a: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433d6f: xor eax, eax */
	m->edi = 0x9dd1d8u;	/* 433d71: mov edi, 0x9dd1d8 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 433d76: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 433d78: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 433d7a: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433d7f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433d82: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433d84: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433d86: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433d88: sub edi, ecx */
	m->edx = m->ecx;	/* 433d8a: mov edx, ecx */
	m->esi = m->edi;	/* 433d8c: mov esi, edi */
	m->edi = 0x9dd1d8u;	/* 433d8e: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433d93: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433d96: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 433d98: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433d9a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433d9d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 433d9f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433da0: pop esi */
	m->esp += 4 + 0; return;	/* 433da1: ret  */
L_433da2:
	{ DWORD a_ = M32((DWORD)(0x9dd3f8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 433da2: cmp dword ptr [0x9dd3f8], esi */
	if (!m->zf) goto L_433de1;	/* 433da8: jne 0x433de1 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433daa: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 433dac: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd1f6u)) = m->eax;	/* 433db1: mov dword ptr [0x9dd1f6], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433db6: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd1fau)) = m->eax;	/* 433db9: mov dword ptr [0x9dd1fa], eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433dbe: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433dc0: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433dc2: sub edi, ecx */
	M32((DWORD)(0x9dd1feu)) = m->eax;	/* 433dc4: mov dword ptr [0x9dd1fe], eax */
	m->edx = m->ecx;	/* 433dc9: mov edx, ecx */
	m->esi = m->edi;	/* 433dcb: mov esi, edi */
	m->edi = 0x9dd1f6u;	/* 433dcd: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433dd2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433dd5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 433dd7: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433dd9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433ddc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 433dde: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433ddf: pop esi */
	m->esp += 4 + 0; return;	/* 433de0: ret  */
L_433de1:
	{ DWORD a_ = M32((DWORD)(0x9dd564u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 433de1: cmp dword ptr [0x9dd564], esi */
	if (!m->zf) goto L_433e20;	/* 433de7: jne 0x433e20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433de9: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 433deb: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd202u)) = m->eax;	/* 433df0: mov dword ptr [0x9dd202], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433df5: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd206u)) = m->eax;	/* 433df8: mov dword ptr [0x9dd206], eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433dfd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433dff: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433e01: sub edi, ecx */
	M32((DWORD)(0x9dd20au)) = m->eax;	/* 433e03: mov dword ptr [0x9dd20a], eax */
	m->edx = m->ecx;	/* 433e08: mov edx, ecx */
	m->esi = m->edi;	/* 433e0a: mov esi, edi */
	m->edi = 0x9dd202u;	/* 433e0c: mov edi, 0x9dd202 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433e11: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433e14: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 433e16: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433e18: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433e1b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 433e1d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433e1e: pop esi */
	m->esp += 4 + 0; return;	/* 433e1f: ret  */
L_433e20:
	{ DWORD a_ = M32((DWORD)(0x9dd6ccu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 433e20: cmp dword ptr [0x9dd6cc], esi */
	if (!m->zf) goto L_433e5d;	/* 433e26: jne 0x433e5d */
	m->ecx = 0xcu;	/* 433e28: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433e2d: xor eax, eax */
	m->edi = 0x9dd20eu;	/* 433e2f: mov edi, 0x9dd20e */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 433e34: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 433e36: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 433e38: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433e3d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 433e40: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 433e42: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 433e44: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 433e46: sub edi, ecx */
	m->eax = m->ecx;	/* 433e48: mov eax, ecx */
	m->esi = m->edi;	/* 433e4a: mov esi, edi */
	m->edi = 0x9dd20eu;	/* 433e4c: mov edi, 0x9dd20e */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 433e51: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 433e54: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 433e56: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 433e58: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 433e5b: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_433e5d:
	m->edi = M32(m->esp); m->esp += 4;	/* 433e5d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 433e5e: pop esi */
	m->esp += 4 + 0; return;	/* 433e5f: ret  */
}

/* profile_44f4b0 (0x44f4b0), lifted by tools/lift.py */
static void lift_44f4b0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f4b0: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44f4b1: push esi */
	m->esp -= 4; M32(m->esp) = 0x44f4b7u; native_call(m, 0x44d720u);	/* 44f4b2: call 0x44d720 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 44f4b7: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 44f4bc: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f4be: cmp eax, ebx */
	if (m->zf) goto L_44f4e7;	/* 44f4c0: je 0x44f4e7 */
	m->eax = M32((DWORD)(0x9f8f24u));	/* 44f4c2: mov eax, dword ptr [0x9f8f24] */
	m->ecx = M32((DWORD)(0x9f8f20u));	/* 44f4c7: mov ecx, dword ptr [0x9f8f20] */
	m->edx = M32((DWORD)(0x9f8ea8u));	/* 44f4cd: mov edx, dword ptr [0x9f8ea8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f4d3: push eax */
	m->eax = M32((DWORD)(0x9f8eacu));	/* 44f4d4: mov eax, dword ptr [0x9f8eac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f4d9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f4da: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f4db: push eax */
	m->esp -= 4; M32(m->esp) = 0x44f4e1u; native_call(m, 0x428c30u);	/* 44f4dc: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f4e1: add esp, 0x10 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f4e4: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44f4e5: pop ebx */
	m->esp += 4 + 0; return;	/* 44f4e6: ret  */
L_44f4e7:
	{ DWORD a_ = M32((DWORD)(0x9f8f34u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f4e7: cmp dword ptr [0x9f8f34], ebx */
	if (m->zf) goto L_44f4f7;	/* 44f4ed: je 0x44f4f7 */
	m->esp -= 4; M32(m->esp) = 0x44f4f4u; native_call(m, 0x44dc60u);	/* 44f4ef: call 0x44dc60 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f4f4: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44f4f5: pop ebx */
	m->esp += 4 + 0; return;	/* 44f4f6: ret  */
L_44f4f7:
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f4f7: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_44f5dd;	/* 44f4fd: jne 0x44f5dd */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44f503: push edi */
	m->edi = 0x9dc92cu;	/* 44f504: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44f509: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44f50c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44f50e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44f510: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44f512: dec ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 44f513: pop edi */
	if (m->zf) goto L_44f5c7;	/* 44f514: je 0x44f5c7 */
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44f51a: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x44f524u; native_call(m, 0x4343b0u);	/* 44f51f: call 0x4343b0 */
	m->esi = 0x1u;	/* 44f524: mov esi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f529: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f52c: cmp eax, esi */
	if (!m->zf) goto L_44f54f;	/* 44f52e: jne 0x44f54f */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f530: push 6 */
	m->esp -= 4; M32(m->esp) = 0x44f537u; native_call(m, 0x41e760u);	/* 44f532: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f537: add esp, 4 */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44f53a: mov dword ptr [0x9f8f10], esi */
	M32((DWORD)(0x90d1c4u)) = m->ebx;	/* 44f540: mov dword ptr [0x90d1c4], ebx */
	M32((DWORD)(0x9f8f34u)) = m->ebx;	/* 44f546: mov dword ptr [0x9f8f34], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f54c: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44f54d: pop ebx */
	m->esp += 4 + 0; return;	/* 44f54e: ret  */
L_44f54f:
	{ DWORD v_ = 0x9dc92cu; m->esp -= 4; M32(m->esp) = v_; }	/* 44f54f: push 0x9dc92c */
	m->esp -= 4; M32(m->esp) = 0x44f559u; native_call(m, 0x44b7e0u);	/* 44f554: call 0x44b7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f559: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f55c: cmp eax, esi */
	if (!m->zf) goto L_44f589;	/* 44f55e: jne 0x44f589 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f560: push 6 */
	m->esp -= 4; M32(m->esp) = 0x44f567u; native_call(m, 0x41e760u);	/* 44f562: call 0x41e760 */
	{ DWORD v_ = 0x81u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f567: push 0x81 */
	M32((DWORD)(0x90d1c4u)) = m->ebx;	/* 44f56c: mov dword ptr [0x90d1c4], ebx */
	M32((DWORD)(0x9f8f34u)) = m->ebx;	/* 44f572: mov dword ptr [0x9f8f34], ebx */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44f578: mov dword ptr [0x9f8f10], esi */
	m->esp -= 4; M32(m->esp) = 0x44f583u; native_call(m, 0x41ee40u);	/* 44f57e: call 0x41ee40 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f583: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f586: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44f587: pop ebx */
	m->esp += 4 + 0; return;	/* 44f588: ret  */
L_44f589:
	m->esp -= 4; M32(m->esp) = 0x44f58eu; native_call(m, 0x44b870u);	/* 44f589: call 0x44b870 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f58e: test eax, eax */
	if (m->zf) goto L_44f5b0;	/* 44f590: je 0x44f5b0 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f592: push 6 */
	m->esp -= 4; M32(m->esp) = 0x44f599u; native_call(m, 0x41e760u);	/* 44f594: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f599: add esp, 4 */
	M32((DWORD)(0x9f8f34u)) = m->esi;	/* 44f59c: mov dword ptr [0x9f8f34], esi */
	M32((DWORD)(0x90d1c4u)) = m->esi;	/* 44f5a2: mov dword ptr [0x90d1c4], esi */
	m->esp -= 4; M32(m->esp) = 0x44f5adu; native_call(m, 0x44de00u);	/* 44f5a8: call 0x44de00 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f5ad: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44f5ae: pop ebx */
	m->esp += 4 + 0; return;	/* 44f5af: ret  */
L_44f5b0:
	M32((DWORD)(0x9f8f10u)) = 0x6u;	/* 44f5b0: mov dword ptr [0x9f8f10], 6 */
	m->esp -= 4; M32(m->esp) = 0x44f5bfu; native_call(m, 0x44b750u);	/* 44f5ba: call 0x44b750 */
	m->esp -= 4; M32(m->esp) = 0x44f5c4u; native_call(m, 0x44de00u);	/* 44f5bf: call 0x44de00 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f5c4: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44f5c5: pop ebx */
	m->esp += 4 + 0; return;	/* 44f5c6: ret  */
L_44f5c7:
	M32((DWORD)(0x90d1c4u)) = m->ebx;	/* 44f5c7: mov dword ptr [0x90d1c4], ebx */
	M32((DWORD)(0x9f8f34u)) = m->ebx;	/* 44f5cd: mov dword ptr [0x9f8f34], ebx */
	M32((DWORD)(0x9f8f10u)) = 0x1u;	/* 44f5d3: mov dword ptr [0x9f8f10], 1 */
L_44f5dd:
	m->esp -= 4; M32(m->esp) = 0x44f5e2u; native_call(m, 0x44de00u);	/* 44f5dd: call 0x44de00 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f5e2: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44f5e3: pop ebx */
	m->esp += 4 + 0; return;	/* 44f5e4: ret  */
}

/* mainmenu_441810 (0x441810), lifted by tools/lift.py */
static void lift_441810(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 441810: mov eax, dword ptr [0x4ded88] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 441815: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441816: test eax, eax */
	if (m->zf) goto L_4418f6;	/* 441818: je 0x4418f6 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44181e: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 441823: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441829: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44182a: push ecx */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44182b: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x44183au; native_call(m, 0x440b70u);	/* 441835: call 0x440b70 */
	m->esi = m->eax;	/* 44183a: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44183c: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = 0x11u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44183f: cmp esi, 0x11 */
	if (!m->cf && !m->zf) goto L_4418f6;	/* 441842: ja 0x4418f6 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 441848: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4419b0u))) & 0xff) << 0);	/* 44184a: mov dl, byte ptr [esi + 0x4419b0] */
	switch (m->edx) { case 0: goto L_441857; case 1: goto L_441869; case 2: goto L_441894; case 3: goto L_4418a8; case 4: goto L_4418bc; case 5: goto L_4418c3; case 6: goto L_4418ca; case 7: goto L_4418d1; case 8: goto L_4418dd; default: abort(); }	/* 441850: jmp dword ptr [edx*4 + 0x44198c] */
L_441857:
	m->eax = M32((DWORD)(0x9dd92cu));	/* 441857: mov eax, dword ptr [0x9dd92c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44185c: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4418f6;	/* 44185e: jle 0x4418f6 */
	m->edx = m->eax;	/* 441864: mov edx, eax */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 441866: dec edx */
	goto L_441882;	/* 441867: jmp 0x441882 */
L_441869:
	m->eax = M32((DWORD)(0x9dd92cu));	/* 441869: mov eax, dword ptr [0x9dd92c] */
	m->ecx = M32((DWORD)(0x9dd928u));	/* 44186e: mov ecx, dword ptr [0x9dd928] */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 441874: add eax, 0xa */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441877: cmp eax, ecx */
	if (m->sf == m->of) goto L_4418f6;	/* 441879: jge 0x4418f6 */
	m->edx = M32((DWORD)(0x9dd92cu));	/* 44187b: mov edx, dword ptr [0x9dd92c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 441881: inc edx */
L_441882:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 441882: push 2 */
	M32((DWORD)(0x9dd92cu)) = m->edx;	/* 441884: mov dword ptr [0x9dd92c], edx */
	m->esp -= 4; M32(m->esp) = 0x44188fu; native_call(m, 0x41e760u);	/* 44188a: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44188f: add esp, 4 */
	goto L_4418f6;	/* 441892: jmp 0x4418f6 */
L_441894:
	m->eax = M32((DWORD)(0x4b2a7cu));	/* 441894: mov eax, dword ptr [0x4b2a7c] */
	m->ecx = 0x1u;	/* 441899: mov ecx, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44189e: sub ecx, eax */
	M32((DWORD)(0x4b2a7cu)) = m->ecx;	/* 4418a0: mov dword ptr [0x4b2a7c], ecx */
	goto L_4418f6;	/* 4418a6: jmp 0x4418f6 */
L_4418a8:
	m->eax = M32((DWORD)(0x9eeac0u));	/* 4418a8: mov eax, dword ptr [0x9eeac0] */
	m->edx = 0x1u;	/* 4418ad: mov edx, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4418b2: sub edx, eax */
	M32((DWORD)(0x9eeac0u)) = m->edx;	/* 4418b4: mov dword ptr [0x9eeac0], edx */
	goto L_4418f6;	/* 4418ba: jmp 0x4418f6 */
L_4418bc:
	m->esp -= 4; M32(m->esp) = 0x4418c1u; native_call(m, 0x4417f0u);	/* 4418bc: call 0x4417f0 */
	goto L_4418f6;	/* 4418c1: jmp 0x4418f6 */
L_4418c3:
	m->esp -= 4; M32(m->esp) = 0x4418c8u; native_call(m, 0x440df0u);	/* 4418c3: call 0x440df0 */
	goto L_4418f6;	/* 4418c8: jmp 0x4418f6 */
L_4418ca:
	m->esp -= 4; M32(m->esp) = 0x4418cfu; native_call(m, 0x441770u);	/* 4418ca: call 0x441770 */
	goto L_4418f6;	/* 4418cf: jmp 0x4418f6 */
L_4418d1:
	M32((DWORD)(0x9eeab4u)) = 0x0u;	/* 4418d1: mov dword ptr [0x9eeab4], 0 */
	goto L_4418f6;	/* 4418db: jmp 0x4418f6 */
L_4418dd:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4418dd: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4418e4u; native_call(m, 0x41e760u);	/* 4418df: call 0x41e760 */
	m->eax = M32((DWORD)(0x9dd92cu));	/* 4418e4: mov eax, dword ptr [0x9dd92c] */
	m->ecx = (DWORD)(m->eax + m->esi*1 + 0xfffffff8u);	/* 4418e9: lea ecx, [eax + esi - 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4418ed: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4418f3u; native_call(m, 0x4417c0u);	/* 4418ee: call 0x4417c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4418f3: add esp, 8 */
L_4418f6:
	m->eax = M32((DWORD)(0x4ded94u));	/* 4418f6: mov eax, dword ptr [0x4ded94] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4418fb: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4418fc: test eax, eax */
	if (m->zf) goto L_441988;	/* 4418fe: je 0x441988 */
	m->edx = M32((DWORD)(0x4ded6cu));	/* 441904: mov edx, dword ptr [0x4ded6c] */
	m->eax = M32((DWORD)(0x4ded68u));	/* 44190a: mov eax, dword ptr [0x4ded68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44190f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 441910: push eax */
	m->esp -= 4; M32(m->esp) = 0x441916u; native_call(m, 0x440b70u);	/* 441911: call 0x440b70 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 441916: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 441919: sub eax, 0 */
	if (m->zf) goto L_44194f;	/* 44191c: je 0x44194f */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44191e: dec eax */
	if (!m->zf) goto L_441988;	/* 44191f: jne 0x441988 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 441921: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 441927: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44192d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44192f: test ah, 1 */
	if (!m->zf) goto L_441988;	/* 441932: jne 0x441988 */
	m->ecx = M32((DWORD)(0x9dd92cu));	/* 441934: mov ecx, dword ptr [0x9dd92c] */
	m->eax = M32((DWORD)(0x9dd928u));	/* 44193a: mov eax, dword ptr [0x9dd928] */
	{ DWORD a_ = m->ecx, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44193f: add ecx, 0xa */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 441942: cmp ecx, eax */
	if (m->sf == m->of) goto L_44197e;	/* 441944: jge 0x44197e */
	m->edx = M32((DWORD)(0x9dd92cu));	/* 441946: mov edx, dword ptr [0x9dd92c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44194c: inc edx */
	goto L_44196e;	/* 44194d: jmp 0x44196e */
L_44194f:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dda44u)));	/* 44194f: fld dword ptr [0x4dda44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 441955: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44195b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44195d: test ah, 1 */
	if (!m->zf) goto L_441988;	/* 441960: jne 0x441988 */
	m->eax = M32((DWORD)(0x9dd92cu));	/* 441962: mov eax, dword ptr [0x9dd92c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 441967: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_44197e;	/* 441969: jle 0x44197e */
	m->edx = m->eax;	/* 44196b: mov edx, eax */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 44196d: dec edx */
L_44196e:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44196e: push 2 */
	M32((DWORD)(0x9dd92cu)) = m->edx;	/* 441970: mov dword ptr [0x9dd92c], edx */
	m->esp -= 4; M32(m->esp) = 0x44197bu; native_call(m, 0x41e760u);	/* 441976: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44197b: add esp, 4 */
L_44197e:
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44197e: mov dword ptr [0x4dda44], 0 */
L_441988:
	m->esp += 4 + 0; return;	/* 441988: ret  */
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
