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

static void lift_4101e0(X86 *m);
static void lift_410500(X86 *m);
static void lift_410810(X86 *m);
static void lift_40fb20(X86 *m);

/* armc_40fb20 (0x40fb20), lifted by tools/lift.py */
static void lift_40fb20(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded88u));	/* 40fb20: mov eax, dword ptr [0x4ded88] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40fb25: push esi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40fb26: test eax, eax */
	if (m->zf) goto L_40fce9;	/* 40fb28: je 0x40fce9 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 40fb2e: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 40fb33: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fb39: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fb3a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x40fb40u; native_call(m, 0x40e450u);	/* 40fb3b: call 0x40e450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fb40: add esp, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40fb43: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fb44: cmp eax, 0xf */
	if (!m->cf && !m->zf) goto L_40fce9;	/* 40fb47: ja 0x40fce9 */
	switch (m->eax) { case 0: goto L_40fb54; case 1: goto L_40fb76; case 2: goto L_40fb94; case 3: goto L_40fba7; case 4: goto L_40fce9; case 5: goto L_40fbba; case 6: goto L_40fbe7; case 7: goto L_40fbee; case 8: goto L_40fc03; case 9: goto L_40fc31; case 10: goto L_40fc5f; case 11: goto L_40fce9; case 12: goto L_40fce9; case 13: goto L_40fc88; case 14: goto L_40fcab; case 15: goto L_40fccd; default: abort(); }	/* 40fb4d: jmp dword ptr [eax*4 + 0x40fcec] */
L_40fb54:
	m->eax = M32((DWORD)(0x4dc798u));	/* 40fb54: mov eax, dword ptr [0x4dc798] */
	m->esi = 0x2u;	/* 40fb59: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fb5e: cmp eax, esi */
	if (m->zf) goto L_40fce9;	/* 40fb60: je 0x40fce9 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40fb66: push esi */
	m->esp -= 4; M32(m->esp) = 0x40fb6cu; native_call(m, 0x41e760u);	/* 40fb67: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fb6c: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40fb74u; native_call(m, 0x40f220u);	/* 40fb6f: call 0x40f220 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fb74: pop esi */
	m->esp += 4 + 0; return;	/* 40fb75: ret  */
L_40fb76:
	{ DWORD a_ = M32((DWORD)(0x4dc798u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fb76: cmp dword ptr [0x4dc798], 3 */
	if (m->zf) goto L_40fce9;	/* 40fb7d: je 0x40fce9 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fb83: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fb8au; native_call(m, 0x41e760u);	/* 40fb85: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fb8a: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x40fb92u; native_call(m, 0x40f320u);	/* 40fb8d: call 0x40f320 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fb92: pop esi */
	m->esp += 4 + 0; return;	/* 40fb93: ret  */
L_40fb94:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fb94: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fb9bu; native_call(m, 0x41e760u);	/* 40fb96: call 0x41e760 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fb9b: push 1 */
	m->esp -= 4; M32(m->esp) = 0x40fba2u; native_call(m, 0x40f0f0u);	/* 40fb9d: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fba2: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fba5: pop esi */
	m->esp += 4 + 0; return;	/* 40fba6: ret  */
L_40fba7:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fba7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fbaeu; native_call(m, 0x41e760u);	/* 40fba9: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fbae: push 0 */
	m->esp -= 4; M32(m->esp) = 0x40fbb5u; native_call(m, 0x40f0f0u);	/* 40fbb0: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fbb5: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fbb8: pop esi */
	m->esp += 4 + 0; return;	/* 40fbb9: ret  */
L_40fbba:
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 40fbba: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40fbbf: test eax, eax */
	if (m->zf) goto L_40fce9;	/* 40fbc1: je 0x40fce9 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fbc7: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fbceu; native_call(m, 0x41e760u);	/* 40fbc9: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fbce: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = 0x0u;	/* 40fbd1: mov dword ptr [0x4dbc6c], 0 */
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 40fbdb: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fbe5: pop esi */
	m->esp += 4 + 0; return;	/* 40fbe6: ret  */
L_40fbe7:
	m->esi = 0x1u;	/* 40fbe7: mov esi, 1 */
	goto L_40fc64;	/* 40fbec: jmp 0x40fc64 */
L_40fbee:
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 40fbee: mov eax, dword ptr [0x4dbc6c] */
	m->esi = 0x2u;	/* 40fbf3: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fbf8: cmp eax, esi */
	if (m->zf) goto L_40fce9;	/* 40fbfa: je 0x40fce9 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40fc00: push esi */
	goto L_40fc6e;	/* 40fc01: jmp 0x40fc6e */
L_40fc03:
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 40fc03: mov eax, dword ptr [0x4dbc6c] */
	m->esi = 0x3u;	/* 40fc08: mov esi, 3 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fc0d: cmp eax, esi */
	if (m->zf) goto L_40fce9;	/* 40fc0f: je 0x40fce9 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fc15: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fc1cu; native_call(m, 0x41e760u);	/* 40fc17: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fc1c: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = m->esi;	/* 40fc1f: mov dword ptr [0x4dbc6c], esi */
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 40fc25: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fc2f: pop esi */
	m->esp += 4 + 0; return;	/* 40fc30: ret  */
L_40fc31:
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 40fc31: mov eax, dword ptr [0x4dbc6c] */
	m->esi = 0x4u;	/* 40fc36: mov esi, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fc3b: cmp eax, esi */
	if (m->zf) goto L_40fce9;	/* 40fc3d: je 0x40fce9 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fc43: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fc4au; native_call(m, 0x41e760u);	/* 40fc45: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fc4a: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = m->esi;	/* 40fc4d: mov dword ptr [0x4dbc6c], esi */
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 40fc53: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fc5d: pop esi */
	m->esp += 4 + 0; return;	/* 40fc5e: ret  */
L_40fc5f:
	m->esi = 0x5u;	/* 40fc5f: mov esi, 5 */
L_40fc64:
	{ DWORD a_ = M32((DWORD)(0x4dbc6cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fc64: cmp dword ptr [0x4dbc6c], esi */
	if (m->zf) goto L_40fce9;	/* 40fc6a: je 0x40fce9 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fc6c: push 2 */
L_40fc6e:
	m->esp -= 4; M32(m->esp) = 0x40fc73u; native_call(m, 0x41e760u);	/* 40fc6e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fc73: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = m->esi;	/* 40fc76: mov dword ptr [0x4dbc6c], esi */
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 40fc7c: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fc86: pop esi */
	m->esp += 4 + 0; return;	/* 40fc87: ret  */
L_40fc88:
	{ DWORD a_ = M32((DWORD)(0x4dbc6cu)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fc88: cmp dword ptr [0x4dbc6c], 5 */
	if (m->zf) goto L_40fce9;	/* 40fc8f: je 0x40fce9 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fc91: push 8 */
	m->esp -= 4; M32(m->esp) = 0x40fc98u; native_call(m, 0x41e760u);	/* 40fc93: call 0x41e760 */
	m->edx = M32((DWORD)(0x4dbc6cu));	/* 40fc98: mov edx, dword ptr [0x4dbc6c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fc9e: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40fca0: push edx */
	m->esp -= 4; M32(m->esp) = 0x40fca6u; native_call(m, 0x40f340u);	/* 40fca1: call 0x40f340 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fca6: add esp, 0xc */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fca9: pop esi */
	m->esp += 4 + 0; return;	/* 40fcaa: ret  */
L_40fcab:
	{ DWORD a_ = M32((DWORD)(0x4dbc6cu)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40fcab: cmp dword ptr [0x4dbc6c], 5 */
	if (m->zf) goto L_40fce9;	/* 40fcb2: je 0x40fce9 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fcb4: push 8 */
	m->esp -= 4; M32(m->esp) = 0x40fcbbu; native_call(m, 0x41e760u);	/* 40fcb6: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 40fcbb: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fcc0: push 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40fcc2: push eax */
	m->esp -= 4; M32(m->esp) = 0x40fcc8u; native_call(m, 0x40f340u);	/* 40fcc3: call 0x40f340 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fcc8: add esp, 0xc */
	m->esi = M32(m->esp); m->esp += 4;	/* 40fccb: pop esi */
	m->esp += 4 + 0; return;	/* 40fccc: ret  */
L_40fccd:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 40fccd: push 2 */
	m->esp -= 4; M32(m->esp) = 0x40fcd4u; native_call(m, 0x41e760u);	/* 40fccf: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dceacu));	/* 40fcd4: mov eax, dword ptr [0x4dceac] */
	m->ecx = 0x1u;	/* 40fcd9: mov ecx, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40fcde: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 40fce1: sub ecx, eax */
	M32((DWORD)(0x4dceacu)) = m->ecx;	/* 40fce3: mov dword ptr [0x4dceac], ecx */
L_40fce9:
	m->esi = M32(m->esp); m->esp += 4;	/* 40fce9: pop esi */
	m->esp += 4 + 0; return;	/* 40fcea: ret  */
}

/* armc_4101e0 (0x4101e0), lifted by tools/lift.py */
static void lift_4101e0(X86 *m)
{
	m->eax = M32((DWORD)(0x4e1538u));	/* 4101e0: mov eax, dword ptr [0x4e1538] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4101e5: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4101e6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4101ecu; native_call(m, 0x401600u);	/* 4101e7: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4101ec: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4101ef: test eax, eax */
	if (m->zf) goto L_410215;	/* 4101f1: je 0x410215 */
	m->eax = M32((DWORD)(0x4dc798u));	/* 4101f3: mov eax, dword ptr [0x4dc798] */
	m->esi = 0x2u;	/* 4101f8: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4101fd: cmp eax, esi */
	if (m->zf) goto L_4104f1;	/* 4101ff: je 0x4104f1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 410205: push esi */
	m->esp -= 4; M32(m->esp) = 0x41020bu; native_call(m, 0x41e760u);	/* 410206: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41020b: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x410213u; native_call(m, 0x40f220u);	/* 41020e: call 0x40f220 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410213: pop esi */
	m->esp += 4 + 0; return;	/* 410214: ret  */
L_410215:
	m->ecx = M32((DWORD)(0x4e1504u));	/* 410215: mov ecx, dword ptr [0x4e1504] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41021b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x410221u; native_call(m, 0x401600u);	/* 41021c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410221: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410224: test eax, eax */
	if (m->zf) goto L_410246;	/* 410226: je 0x410246 */
	{ DWORD a_ = M32((DWORD)(0x4dc798u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410228: cmp dword ptr [0x4dc798], 3 */
	if (m->zf) goto L_4104f1;	/* 41022f: je 0x4104f1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410235: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41023cu; native_call(m, 0x41e760u);	/* 410237: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41023c: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x410244u; native_call(m, 0x40f320u);	/* 41023f: call 0x40f320 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410244: pop esi */
	m->esp += 4 + 0; return;	/* 410245: ret  */
L_410246:
	m->edx = M32((DWORD)(0x4e151cu));	/* 410246: mov edx, dword ptr [0x4e151c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41024c: push edx */
	m->esp -= 4; M32(m->esp) = 0x410252u; native_call(m, 0x401600u);	/* 41024d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410252: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410255: test eax, eax */
	if (m->zf) goto L_410277;	/* 410257: je 0x410277 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410259: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410260u; native_call(m, 0x41e760u);	/* 41025b: call 0x41e760 */
	m->ecx = M32((DWORD)(0x4dceacu));	/* 410260: mov ecx, dword ptr [0x4dceac] */
	m->eax = 0x1u;	/* 410266: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41026b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 41026e: sub eax, ecx */
	M32((DWORD)(0x4dceacu)) = m->eax;	/* 410270: mov dword ptr [0x4dceac], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 410275: pop esi */
	m->esp += 4 + 0; return;	/* 410276: ret  */
L_410277:
	m->ecx = M32((DWORD)(0x4e14f0u));	/* 410277: mov ecx, dword ptr [0x4e14f0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41027d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x410283u; native_call(m, 0x401600u);	/* 41027e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410283: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410286: test eax, eax */
	if (m->zf) goto L_4102b7;	/* 410288: je 0x4102b7 */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 41028a: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41028f: test eax, eax */
	if (m->zf) goto L_4104f1;	/* 410291: je 0x4104f1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410297: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41029eu; native_call(m, 0x41e760u);	/* 410299: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41029e: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = 0x0u;	/* 4102a1: mov dword ptr [0x4dbc6c], 0 */
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 4102ab: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4102b5: pop esi */
	m->esp += 4 + 0; return;	/* 4102b6: ret  */
L_4102b7:
	m->edx = M32((DWORD)(0x4e10e4u));	/* 4102b7: mov edx, dword ptr [0x4e10e4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4102bd: push edx */
	m->esp -= 4; M32(m->esp) = 0x4102c3u; native_call(m, 0x401600u);	/* 4102be: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4102c3: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4102c6: test eax, eax */
	if (m->zf) goto L_4102d4;	/* 4102c8: je 0x4102d4 */
	m->esi = 0x1u;	/* 4102ca: mov esi, 1 */
	goto L_410354;	/* 4102cf: jmp 0x410354 */
L_4102d4:
	m->eax = M32((DWORD)(0x4e1524u));	/* 4102d4: mov eax, dword ptr [0x4e1524] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4102d9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4102dfu; native_call(m, 0x401600u);	/* 4102da: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4102df: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4102e2: test eax, eax */
	if (m->zf) goto L_4102fb;	/* 4102e4: je 0x4102fb */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 4102e6: mov eax, dword ptr [0x4dbc6c] */
	m->esi = 0x2u;	/* 4102eb: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4102f0: cmp eax, esi */
	if (m->zf) goto L_4104f1;	/* 4102f2: je 0x4104f1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4102f8: push esi */
	goto L_410362;	/* 4102f9: jmp 0x410362 */
L_4102fb:
	m->ecx = M32((DWORD)(0x4e14ecu));	/* 4102fb: mov ecx, dword ptr [0x4e14ec] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 410301: push ecx */
	m->esp -= 4; M32(m->esp) = 0x410307u; native_call(m, 0x401600u);	/* 410302: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410307: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41030a: test eax, eax */
	if (m->zf) goto L_41033c;	/* 41030c: je 0x41033c */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 41030e: mov eax, dword ptr [0x4dbc6c] */
	m->esi = 0x3u;	/* 410313: mov esi, 3 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410318: cmp eax, esi */
	if (m->zf) goto L_4104f1;	/* 41031a: je 0x4104f1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410320: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410327u; native_call(m, 0x41e760u);	/* 410322: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410327: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = m->esi;	/* 41032a: mov dword ptr [0x4dbc6c], esi */
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 410330: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41033a: pop esi */
	m->esp += 4 + 0; return;	/* 41033b: ret  */
L_41033c:
	m->edx = M32((DWORD)(0x4e0cd8u));	/* 41033c: mov edx, dword ptr [0x4e0cd8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410342: push edx */
	m->esp -= 4; M32(m->esp) = 0x410348u; native_call(m, 0x401600u);	/* 410343: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410348: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41034b: test eax, eax */
	if (m->zf) goto L_41037c;	/* 41034d: je 0x41037c */
	m->esi = 0x4u;	/* 41034f: mov esi, 4 */
L_410354:
	{ DWORD a_ = M32((DWORD)(0x4dbc6cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410354: cmp dword ptr [0x4dbc6c], esi */
	if (m->zf) goto L_4104f1;	/* 41035a: je 0x4104f1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410360: push 2 */
L_410362:
	m->esp -= 4; M32(m->esp) = 0x410367u; native_call(m, 0x41e760u);	/* 410362: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410367: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = m->esi;	/* 41036a: mov dword ptr [0x4dbc6c], esi */
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 410370: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41037a: pop esi */
	m->esp += 4 + 0; return;	/* 41037b: ret  */
L_41037c:
	m->eax = M32((DWORD)(0x4e0cd4u));	/* 41037c: mov eax, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410381: push eax */
	m->esp -= 4; M32(m->esp) = 0x410387u; native_call(m, 0x401600u);	/* 410382: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410387: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41038a: test eax, eax */
	if (m->zf) goto L_4103a4;	/* 41038c: je 0x4103a4 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41038e: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410395u; native_call(m, 0x41e760u);	/* 410390: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410395: add esp, 4 */
	M32((DWORD)(0x4dbc6cu)) = 0x5u;	/* 410398: mov dword ptr [0x4dbc6c], 5 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4103a2: pop esi */
	m->esp += 4 + 0; return;	/* 4103a3: ret  */
L_4103a4:
	m->ecx = M32((DWORD)(0x9db0a0u));	/* 4103a4: mov ecx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4103aa: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4103b0u; native_call(m, 0x401600u);	/* 4103ab: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4103b0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4103b3: test eax, eax */
	if (m->zf) goto L_4103e4;	/* 4103b5: je 0x4103e4 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4103b7: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4103beu; native_call(m, 0x41e760u);	/* 4103b9: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 4103be: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4103c3: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4103c6: dec eax */
	M32((DWORD)(0x4dbc6cu)) = m->eax;	/* 4103c7: mov dword ptr [0x4dbc6c], eax */
	if (!m->sf) goto L_4103d8;	/* 4103cc: jns 0x4103d8 */
	M32((DWORD)(0x4dbc6cu)) = 0x5u;	/* 4103ce: mov dword ptr [0x4dbc6c], 5 */
L_4103d8:
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 4103d8: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4103e2: pop esi */
	m->esp += 4 + 0; return;	/* 4103e3: ret  */
L_4103e4:
	m->edx = M32((DWORD)(0x76d330u));	/* 4103e4: mov edx, dword ptr [0x76d330] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4103ea: push edx */
	m->esp -= 4; M32(m->esp) = 0x4103f0u; native_call(m, 0x401600u);	/* 4103eb: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4103f0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4103f3: test eax, eax */
	if (m->zf) goto L_410427;	/* 4103f5: je 0x410427 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4103f7: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4103feu; native_call(m, 0x41e760u);	/* 4103f9: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 4103fe: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410403: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 410406: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410407: cmp eax, 5 */
	M32((DWORD)(0x4dbc6cu)) = m->eax;	/* 41040a: mov dword ptr [0x4dbc6c], eax */
	if (m->zf || m->sf != m->of) goto L_41041b;	/* 41040f: jle 0x41041b */
	M32((DWORD)(0x4dbc6cu)) = 0x0u;	/* 410411: mov dword ptr [0x4dbc6c], 0 */
L_41041b:
	M32((DWORD)(0x4dcfd8u)) = 0x3f800000u;	/* 41041b: mov dword ptr [0x4dcfd8], 0x3f800000 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410425: pop esi */
	m->esp += 4 + 0; return;	/* 410426: ret  */
L_410427:
	m->eax = M32((DWORD)(0x9dae14u));	/* 410427: mov eax, dword ptr [0x9dae14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41042c: push eax */
	m->esp -= 4; M32(m->esp) = 0x410432u; native_call(m, 0x401600u);	/* 41042d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410432: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410435: test eax, eax */
	if (m->zf) goto L_410460;	/* 410437: je 0x410460 */
	{ DWORD a_ = M32((DWORD)(0x4dbc6cu)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410439: cmp dword ptr [0x4dbc6c], 5 */
	if (m->zf) goto L_4104f1;	/* 410440: je 0x4104f1 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 410446: push 8 */
	m->esp -= 4; M32(m->esp) = 0x41044du; native_call(m, 0x41e760u);	/* 410448: call 0x41e760 */
	m->ecx = M32((DWORD)(0x4dbc6cu));	/* 41044d: mov ecx, dword ptr [0x4dbc6c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 410453: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 410455: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41045bu; native_call(m, 0x40f340u);	/* 410456: call 0x40f340 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41045b: add esp, 0xc */
	m->esi = M32(m->esp); m->esp += 4;	/* 41045e: pop esi */
	m->esp += 4 + 0; return;	/* 41045f: ret  */
L_410460:
	m->edx = M32((DWORD)(0x9db974u));	/* 410460: mov edx, dword ptr [0x9db974] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410466: push edx */
	m->esp -= 4; M32(m->esp) = 0x41046cu; native_call(m, 0x401600u);	/* 410467: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41046c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41046f: test eax, eax */
	if (m->zf) goto L_410495;	/* 410471: je 0x410495 */
	{ DWORD a_ = M32((DWORD)(0x4dbc6cu)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410473: cmp dword ptr [0x4dbc6c], 5 */
	if (m->zf) goto L_4104f1;	/* 41047a: je 0x4104f1 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 41047c: push 8 */
	m->esp -= 4; M32(m->esp) = 0x410483u; native_call(m, 0x41e760u);	/* 41047e: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dbc6cu));	/* 410483: mov eax, dword ptr [0x4dbc6c] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410488: push 2 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41048a: push eax */
	m->esp -= 4; M32(m->esp) = 0x410490u; native_call(m, 0x40f340u);	/* 41048b: call 0x40f340 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410490: add esp, 0xc */
	m->esi = M32(m->esp); m->esp += 4;	/* 410493: pop esi */
	m->esp += 4 + 0; return;	/* 410494: ret  */
L_410495:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 410495: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41049b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4104a1u; native_call(m, 0x401600u);	/* 41049c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4104a1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4104a4: test eax, eax */
	if (m->zf) goto L_4104bb;	/* 4104a6: je 0x4104bb */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4104a8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4104afu; native_call(m, 0x41e760u);	/* 4104aa: call 0x41e760 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4104af: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4104b6u; native_call(m, 0x40f0f0u);	/* 4104b1: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4104b6: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4104b9: pop esi */
	m->esp += 4 + 0; return;	/* 4104ba: ret  */
L_4104bb:
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 4104bb: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4104c1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4104c7u; native_call(m, 0x401600u);	/* 4104c2: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4104c7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4104ca: test eax, eax */
	if (!m->zf) goto L_4104e0;	/* 4104cc: jne 0x4104e0 */
	m->eax = M32((DWORD)(0x76d48cu));	/* 4104ce: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4104d3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4104d9u; native_call(m, 0x401600u);	/* 4104d4: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4104d9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4104dc: test eax, eax */
	if (m->zf) goto L_4104f1;	/* 4104de: je 0x4104f1 */
L_4104e0:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4104e0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4104e7u; native_call(m, 0x41e760u);	/* 4104e2: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4104e7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4104eeu; native_call(m, 0x40f0f0u);	/* 4104e9: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4104ee: add esp, 8 */
L_4104f1:
	m->esi = M32(m->esp); m->esp += 4;	/* 4104f1: pop esi */
	m->esp += 4 + 0; return;	/* 4104f2: ret  */
}

/* armc_410500 (0x410500), lifted by tools/lift.py */
static void lift_410500(X86 *m)
{
	m->eax = M32((DWORD)(0x76d48cu));	/* 410500: mov eax, dword ptr [0x76d48c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 410505: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410506: push eax */
	m->esp -= 4; M32(m->esp) = 0x41050cu; native_call(m, 0x401600u);	/* 410507: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41050c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41050f: test eax, eax */
	if (m->zf) goto L_410526;	/* 410511: je 0x410526 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 410513: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41051au; native_call(m, 0x41e760u);	/* 410515: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41051a: push 0 */
	m->esp -= 4; M32(m->esp) = 0x410521u; native_call(m, 0x40f0f0u);	/* 41051c: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410521: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410524: pop esi */
	m->esp += 4 + 0; return;	/* 410525: ret  */
L_410526:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 410526: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41052c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x410532u; native_call(m, 0x401600u);	/* 41052d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410532: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410535: test eax, eax */
	if (m->zf) goto L_41054c;	/* 410537: je 0x41054c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 410539: push 0 */
	m->esp -= 4; M32(m->esp) = 0x410540u; native_call(m, 0x41e760u);	/* 41053b: call 0x41e760 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 410540: push 1 */
	m->esp -= 4; M32(m->esp) = 0x410547u; native_call(m, 0x40f0f0u);	/* 410542: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410547: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41054a: pop esi */
	m->esp += 4 + 0; return;	/* 41054b: ret  */
L_41054c:
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 41054c: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410552: push edx */
	m->esp -= 4; M32(m->esp) = 0x410558u; native_call(m, 0x401600u);	/* 410553: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410558: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41055b: test eax, eax */
	if (m->zf) goto L_410572;	/* 41055d: je 0x410572 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 41055f: push 0 */
	m->esp -= 4; M32(m->esp) = 0x410566u; native_call(m, 0x41e760u);	/* 410561: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 410566: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41056du; native_call(m, 0x40f0f0u);	/* 410568: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41056d: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410570: pop esi */
	m->esp += 4 + 0; return;	/* 410571: ret  */
L_410572:
	m->eax = M32((DWORD)(0x4e1514u));	/* 410572: mov eax, dword ptr [0x4e1514] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410577: push eax */
	m->esp -= 4; M32(m->esp) = 0x41057du; native_call(m, 0x401600u);	/* 410578: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41057d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410580: test eax, eax */
	if (m->zf) goto L_4105a9;	/* 410582: je 0x4105a9 */
	{ DWORD a_ = M32((DWORD)(0x4dc798u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410584: cmp dword ptr [0x4dc798], 1 */
	if (m->zf) goto L_410803;	/* 41058b: je 0x410803 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 410591: push 0 */
	m->esp -= 4; M32(m->esp) = 0x410598u; native_call(m, 0x40f870u);	/* 410593: call 0x40f870 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410598: push 2 */
	m->esp -= 4; M32(m->esp) = 0x41059fu; native_call(m, 0x41e760u);	/* 41059a: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41059f: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4105a7u; native_call(m, 0x40f200u);	/* 4105a2: call 0x40f200 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4105a7: pop esi */
	m->esp += 4 + 0; return;	/* 4105a8: ret  */
L_4105a9:
	m->ecx = M32((DWORD)(0x4e1504u));	/* 4105a9: mov ecx, dword ptr [0x4e1504] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4105af: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4105b5u; native_call(m, 0x401600u);	/* 4105b0: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4105b5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4105b8: test eax, eax */
	if (m->zf) goto L_4105e1;	/* 4105ba: je 0x4105e1 */
	{ DWORD a_ = M32((DWORD)(0x4dc798u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4105bc: cmp dword ptr [0x4dc798], 3 */
	if (m->zf) goto L_410803;	/* 4105c3: je 0x410803 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4105c9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4105d0u; native_call(m, 0x40f870u);	/* 4105cb: call 0x40f870 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4105d0: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4105d7u; native_call(m, 0x41e760u);	/* 4105d2: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4105d7: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4105dfu; native_call(m, 0x40f320u);	/* 4105da: call 0x40f320 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4105df: pop esi */
	m->esp += 4 + 0; return;	/* 4105e0: ret  */
L_4105e1:
	m->edx = M32((DWORD)(0x4e151cu));	/* 4105e1: mov edx, dword ptr [0x4e151c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4105e7: push edx */
	m->esp -= 4; M32(m->esp) = 0x4105edu; native_call(m, 0x401600u);	/* 4105e8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4105ed: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4105f0: test eax, eax */
	if (m->zf) goto L_410612;	/* 4105f2: je 0x410612 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4105f4: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4105fbu; native_call(m, 0x41e760u);	/* 4105f6: call 0x41e760 */
	m->ecx = M32((DWORD)(0x4dceacu));	/* 4105fb: mov ecx, dword ptr [0x4dceac] */
	m->eax = 0x1u;	/* 410601: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410606: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 410609: sub eax, ecx */
	M32((DWORD)(0x4dceacu)) = m->eax;	/* 41060b: mov dword ptr [0x4dceac], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 410610: pop esi */
	m->esp += 4 + 0; return;	/* 410611: ret  */
L_410612:
	m->ecx = M32((DWORD)(0x4e0468u));	/* 410612: mov ecx, dword ptr [0x4e0468] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 410618: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41061eu; native_call(m, 0x401600u);	/* 410619: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41061e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410621: test eax, eax */
	if (m->zf) goto L_410631;	/* 410623: je 0x410631 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 410625: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41062cu; native_call(m, 0x40f870u);	/* 410627: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41062c: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41062f: pop esi */
	m->esp += 4 + 0; return;	/* 410630: ret  */
L_410631:
	m->edx = M32((DWORD)(0x4e046cu));	/* 410631: mov edx, dword ptr [0x4e046c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410637: push edx */
	m->esp -= 4; M32(m->esp) = 0x41063du; native_call(m, 0x401600u);	/* 410638: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41063d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410640: test eax, eax */
	if (m->zf) goto L_410650;	/* 410642: je 0x410650 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 410644: push 1 */
	m->esp -= 4; M32(m->esp) = 0x41064bu; native_call(m, 0x40f870u);	/* 410646: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41064b: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41064e: pop esi */
	m->esp += 4 + 0; return;	/* 41064f: ret  */
L_410650:
	m->eax = M32((DWORD)(0x4e0470u));	/* 410650: mov eax, dword ptr [0x4e0470] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410655: push eax */
	m->esp -= 4; M32(m->esp) = 0x41065bu; native_call(m, 0x401600u);	/* 410656: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41065b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41065e: test eax, eax */
	if (m->zf) goto L_41066e;	/* 410660: je 0x41066e */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410662: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410669u; native_call(m, 0x40f870u);	/* 410664: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410669: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41066c: pop esi */
	m->esp += 4 + 0; return;	/* 41066d: ret  */
L_41066e:
	m->ecx = M32((DWORD)(0x4e0874u));	/* 41066e: mov ecx, dword ptr [0x4e0874] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 410674: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41067au; native_call(m, 0x401600u);	/* 410675: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41067a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41067d: test eax, eax */
	if (m->zf) goto L_41068d;	/* 41067f: je 0x41068d */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 410681: push 3 */
	m->esp -= 4; M32(m->esp) = 0x410688u; native_call(m, 0x40f870u);	/* 410683: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410688: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41068b: pop esi */
	m->esp += 4 + 0; return;	/* 41068c: ret  */
L_41068d:
	m->edx = M32((DWORD)(0x4e0c78u));	/* 41068d: mov edx, dword ptr [0x4e0c78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410693: push edx */
	m->esp -= 4; M32(m->esp) = 0x410699u; native_call(m, 0x401600u);	/* 410694: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410699: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41069c: test eax, eax */
	if (m->zf) goto L_4106ac;	/* 41069e: je 0x4106ac */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4106a0: push 4 */
	m->esp -= 4; M32(m->esp) = 0x4106a7u; native_call(m, 0x40f870u);	/* 4106a2: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4106a7: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4106aa: pop esi */
	m->esp += 4 + 0; return;	/* 4106ab: ret  */
L_4106ac:
	m->eax = M32((DWORD)(0x4e0c7cu));	/* 4106ac: mov eax, dword ptr [0x4e0c7c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4106b1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4106b7u; native_call(m, 0x401600u);	/* 4106b2: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4106b7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4106ba: test eax, eax */
	if (m->zf) goto L_4106ca;	/* 4106bc: je 0x4106ca */
	{ DWORD v_ = 0x5u; m->esp -= 4; M32(m->esp) = v_; }	/* 4106be: push 5 */
	m->esp -= 4; M32(m->esp) = 0x4106c5u; native_call(m, 0x40f870u);	/* 4106c0: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4106c5: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4106c8: pop esi */
	m->esp += 4 + 0; return;	/* 4106c9: ret  */
L_4106ca:
	m->ecx = M32((DWORD)(0x9db974u));	/* 4106ca: mov ecx, dword ptr [0x9db974] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4106d0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4106d6u; native_call(m, 0x401600u);	/* 4106d1: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4106d6: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4106d9: test eax, eax */
	if (m->zf) goto L_410735;	/* 4106db: je 0x410735 */
	m->eax = M32((DWORD)(0x4dc77cu));	/* 4106dd: mov eax, dword ptr [0x4dc77c] */
	m->ecx = M32((DWORD)(0x4dbe48u));	/* 4106e2: mov ecx, dword ptr [0x4dbe48] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4106e8: inc eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4106e9: test ecx, ecx */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 4106eb: mov dword ptr [0x4dc77c], eax */
	if (!m->zf) goto L_410706;	/* 4106f0: jne 0x410706 */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(0x4dc244u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4106f2: cmp eax, dword ptr [0x4dc244] */
	if (m->sf != m->of) goto L_41071f;	/* 4106f8: jl 0x41071f */
	M32((DWORD)(0x4dc77cu)) = 0x1u;	/* 4106fa: mov dword ptr [0x4dc77c], 1 */
	goto L_41071f;	/* 410704: jmp 0x41071f */
L_410706:
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410706: cmp ecx, 3 */
	if (m->zf || m->sf != m->of) goto L_41071f;	/* 410709: jle 0x41071f */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41070b: push eax */
	m->esp -= 4; M32(m->esp) = 0x410711u; native_call(m, 0x40f830u);	/* 41070c: call 0x40f830 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410711: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410714: cmp eax, 1 */
	if (!m->zf) goto L_41071f;	/* 410717: jne 0x41071f */
	{ DWORD a_ = M32((DWORD)(0x4dc77cu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(0x4dc77cu)) = r_; }	/* 410719: inc dword ptr [0x4dc77c] */
L_41071f:
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 41071f: push 8 */
	m->esp -= 4; M32(m->esp) = 0x410726u; native_call(m, 0x41e760u);	/* 410721: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410726: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x41072eu; native_call(m, 0x40f950u);	/* 410729: call 0x40f950 */
	m->esp -= 4; M32(m->esp) = 0x410733u; native_call(m, 0x40f9e0u);	/* 41072e: call 0x40f9e0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410733: pop esi */
	m->esp += 4 + 0; return;	/* 410734: ret  */
L_410735:
	m->edx = M32((DWORD)(0x9dae14u));	/* 410735: mov edx, dword ptr [0x9dae14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41073b: push edx */
	m->esp -= 4; M32(m->esp) = 0x410741u; native_call(m, 0x401600u);	/* 41073c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410741: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410744: test eax, eax */
	if (m->zf) goto L_41079c;	/* 410746: je 0x41079c */
	m->eax = M32((DWORD)(0x4dc77cu));	/* 410748: mov eax, dword ptr [0x4dc77c] */
	m->ecx = M32((DWORD)(0x4dbe48u));	/* 41074d: mov ecx, dword ptr [0x4dbe48] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410753: dec eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410754: test ecx, ecx */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 410756: mov dword ptr [0x4dc77c], eax */
	if (!m->zf) goto L_410768;	/* 41075b: jne 0x410768 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41075d: test eax, eax */
	if (!m->zf) goto L_410786;	/* 41075f: jne 0x410786 */
	m->eax = M32((DWORD)(0x4dc244u));	/* 410761: mov eax, dword ptr [0x4dc244] */
	goto L_410780;	/* 410766: jmp 0x410780 */
L_410768:
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410768: cmp ecx, 3 */
	if (m->zf || m->sf != m->of) goto L_410786;	/* 41076b: jle 0x410786 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41076d: push eax */
	m->esp -= 4; M32(m->esp) = 0x410773u; native_call(m, 0x40f830u);	/* 41076e: call 0x40f830 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410773: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410776: cmp eax, 1 */
	if (!m->zf) goto L_410786;	/* 410779: jne 0x410786 */
	m->eax = M32((DWORD)(0x4dc77cu));	/* 41077b: mov eax, dword ptr [0x4dc77c] */
L_410780:
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410780: dec eax */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 410781: mov dword ptr [0x4dc77c], eax */
L_410786:
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 410786: push 8 */
	m->esp -= 4; M32(m->esp) = 0x41078du; native_call(m, 0x41e760u);	/* 410788: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41078d: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x410795u; native_call(m, 0x40f950u);	/* 410790: call 0x40f950 */
	m->esp -= 4; M32(m->esp) = 0x41079au; native_call(m, 0x40f9e0u);	/* 410795: call 0x40f9e0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41079a: pop esi */
	m->esp += 4 + 0; return;	/* 41079b: ret  */
L_41079c:
	m->ecx = M32((DWORD)(0x9db0a0u));	/* 41079c: mov ecx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4107a2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4107a8u; native_call(m, 0x401600u);	/* 4107a3: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4107a8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4107ab: test eax, eax */
	if (m->zf) goto L_4107d1;	/* 4107ad: je 0x4107d1 */
	m->edx = M32((DWORD)(0x4dbe48u));	/* 4107af: mov edx, dword ptr [0x4dbe48] */
	m->esi = (DWORD)(m->edx + 0xffffffffu);	/* 4107b5: lea esi, [edx - 1] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4107b8: test esi, esi */
	if (m->sf == m->of) goto L_4107c1;	/* 4107ba: jge 0x4107c1 */
	m->esi = 0x5u;	/* 4107bc: mov esi, 5 */
L_4107c1:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4107c1: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4107c8u; native_call(m, 0x41e760u);	/* 4107c3: call 0x41e760 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4107c8: push esi */
	m->esp -= 4; M32(m->esp) = 0x4107ceu; native_call(m, 0x40f870u);	/* 4107c9: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4107ce: add esp, 8 */
L_4107d1:
	m->eax = M32((DWORD)(0x76d330u));	/* 4107d1: mov eax, dword ptr [0x76d330] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4107d6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4107dcu; native_call(m, 0x401600u);	/* 4107d7: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4107dc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4107df: test eax, eax */
	if (m->zf) goto L_410803;	/* 4107e1: je 0x410803 */
	m->ecx = M32((DWORD)(0x4dbe48u));	/* 4107e3: mov ecx, dword ptr [0x4dbe48] */
	m->esi = (DWORD)(m->ecx + 0x1u);	/* 4107e9: lea esi, [ecx + 1] */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4107ec: cmp esi, 5 */
	if (m->zf || m->sf != m->of) goto L_4107f3;	/* 4107ef: jle 0x4107f3 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4107f1: xor esi, esi */
L_4107f3:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4107f3: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4107fau; native_call(m, 0x41e760u);	/* 4107f5: call 0x41e760 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4107fa: push esi */
	m->esp -= 4; M32(m->esp) = 0x410800u; native_call(m, 0x40f870u);	/* 4107fb: call 0x40f870 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410800: add esp, 8 */
L_410803:
	m->esi = M32(m->esp); m->esp += 4;	/* 410803: pop esi */
	m->esp += 4 + 0; return;	/* 410804: ret  */
}

/* armc_410810 (0x410810), lifted by tools/lift.py */
static void lift_410810(X86 *m)
{
	m->eax = M32((DWORD)(0x4e1510u));	/* 410810: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 410815: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410816: push eax */
	m->esp -= 4; M32(m->esp) = 0x41081cu; native_call(m, 0x401600u);	/* 410817: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41081c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41081f: test eax, eax */
	if (m->zf) goto L_410836;	/* 410821: je 0x410836 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 410823: push 0 */
	m->esp -= 4; M32(m->esp) = 0x41082au; native_call(m, 0x41e760u);	/* 410825: call 0x41e760 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 41082a: push 1 */
	m->esp -= 4; M32(m->esp) = 0x410831u; native_call(m, 0x40f0f0u);	/* 41082c: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410831: add esp, 8 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410834: pop esi */
	m->esp += 4 + 0; return;	/* 410835: ret  */
L_410836:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 410836: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41083c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x410842u; native_call(m, 0x401600u);	/* 41083d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410842: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410845: test eax, eax */
	if (!m->zf) goto L_410a99;	/* 410847: jne 0x410a99 */
	m->edx = M32((DWORD)(0x4e1514u));	/* 41084d: mov edx, dword ptr [0x4e1514] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410853: push edx */
	m->esp -= 4; M32(m->esp) = 0x410859u; native_call(m, 0x401600u);	/* 410854: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410859: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41085c: test eax, eax */
	if (m->zf) goto L_410871;	/* 41085e: je 0x410871 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410860: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410867u; native_call(m, 0x41e760u);	/* 410862: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410867: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x41086fu; native_call(m, 0x40f200u);	/* 41086a: call 0x40f200 */
	m->esi = M32(m->esp); m->esp += 4;	/* 41086f: pop esi */
	m->esp += 4 + 0; return;	/* 410870: ret  */
L_410871:
	m->eax = M32((DWORD)(0x4e1538u));	/* 410871: mov eax, dword ptr [0x4e1538] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410876: push eax */
	m->esp -= 4; M32(m->esp) = 0x41087cu; native_call(m, 0x401600u);	/* 410877: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41087c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41087f: test eax, eax */
	if (m->zf) goto L_4108a5;	/* 410881: je 0x4108a5 */
	m->eax = M32((DWORD)(0x4dc798u));	/* 410883: mov eax, dword ptr [0x4dc798] */
	m->esi = 0x2u;	/* 410888: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41088d: cmp eax, esi */
	if (m->zf) goto L_410aaa;	/* 41088f: je 0x410aaa */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 410895: push esi */
	m->esp -= 4; M32(m->esp) = 0x41089bu; native_call(m, 0x41e760u);	/* 410896: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41089b: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x4108a3u; native_call(m, 0x40f220u);	/* 41089e: call 0x40f220 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4108a3: pop esi */
	m->esp += 4 + 0; return;	/* 4108a4: ret  */
L_4108a5:
	m->ecx = M32((DWORD)(0x4e14f0u));	/* 4108a5: mov ecx, dword ptr [0x4e14f0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4108ab: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4108b1u; native_call(m, 0x401600u);	/* 4108ac: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4108b1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4108b4: test eax, eax */
	if (m->zf) goto L_4108db;	/* 4108b6: je 0x4108db */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 4108b8: mov eax, dword ptr [0x4dc4b0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4108bd: test eax, eax */
	if (m->zf) goto L_410aaa;	/* 4108bf: je 0x410aaa */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4108c5: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4108ccu; native_call(m, 0x41e760u);	/* 4108c7: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4108cc: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = 0x0u;	/* 4108cf: mov dword ptr [0x4dc4b0], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4108d9: pop esi */
	m->esp += 4 + 0; return;	/* 4108da: ret  */
L_4108db:
	m->edx = M32((DWORD)(0x4e10e4u));	/* 4108db: mov edx, dword ptr [0x4e10e4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4108e1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4108e7u; native_call(m, 0x401600u);	/* 4108e2: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4108e7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4108ea: test eax, eax */
	if (m->zf) goto L_410912;	/* 4108ec: je 0x410912 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 4108ee: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x1u;	/* 4108f3: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4108f8: cmp eax, esi */
	if (m->zf) goto L_410aaa;	/* 4108fa: je 0x410aaa */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410900: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410907u; native_call(m, 0x41e760u);	/* 410902: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410907: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 41090a: mov dword ptr [0x4dc4b0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 410910: pop esi */
	m->esp += 4 + 0; return;	/* 410911: ret  */
L_410912:
	m->eax = M32((DWORD)(0x4e1524u));	/* 410912: mov eax, dword ptr [0x4e1524] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410917: push eax */
	m->esp -= 4; M32(m->esp) = 0x41091du; native_call(m, 0x401600u);	/* 410918: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41091d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410920: test eax, eax */
	if (m->zf) goto L_410947;	/* 410922: je 0x410947 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 410924: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x2u;	/* 410929: mov esi, 2 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41092e: cmp eax, esi */
	if (m->zf) goto L_410aaa;	/* 410930: je 0x410aaa */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 410936: push esi */
	m->esp -= 4; M32(m->esp) = 0x41093cu; native_call(m, 0x41e760u);	/* 410937: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41093c: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 41093f: mov dword ptr [0x4dc4b0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 410945: pop esi */
	m->esp += 4 + 0; return;	/* 410946: ret  */
L_410947:
	m->ecx = M32((DWORD)(0x4e14ecu));	/* 410947: mov ecx, dword ptr [0x4e14ec] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41094d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x410953u; native_call(m, 0x401600u);	/* 41094e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410953: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410956: test eax, eax */
	if (m->zf) goto L_41097e;	/* 410958: je 0x41097e */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 41095a: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x3u;	/* 41095f: mov esi, 3 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410964: cmp eax, esi */
	if (m->zf) goto L_410aaa;	/* 410966: je 0x410aaa */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 41096c: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410973u; native_call(m, 0x41e760u);	/* 41096e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410973: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 410976: mov dword ptr [0x4dc4b0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 41097c: pop esi */
	m->esp += 4 + 0; return;	/* 41097d: ret  */
L_41097e:
	m->edx = M32((DWORD)(0x4e0cd8u));	/* 41097e: mov edx, dword ptr [0x4e0cd8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410984: push edx */
	m->esp -= 4; M32(m->esp) = 0x41098au; native_call(m, 0x401600u);	/* 410985: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41098a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 41098d: test eax, eax */
	if (m->zf) goto L_4109b5;	/* 41098f: je 0x4109b5 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 410991: mov eax, dword ptr [0x4dc4b0] */
	m->esi = 0x4u;	/* 410996: mov esi, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41099b: cmp eax, esi */
	if (m->zf) goto L_410aaa;	/* 41099d: je 0x410aaa */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4109a3: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4109aau; native_call(m, 0x41e760u);	/* 4109a5: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4109aa: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = m->esi;	/* 4109ad: mov dword ptr [0x4dc4b0], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4109b3: pop esi */
	m->esp += 4 + 0; return;	/* 4109b4: ret  */
L_4109b5:
	m->eax = M32((DWORD)(0x4e0cd4u));	/* 4109b5: mov eax, dword ptr [0x4e0cd4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4109ba: push eax */
	m->esp -= 4; M32(m->esp) = 0x4109c0u; native_call(m, 0x401600u);	/* 4109bb: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4109c0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4109c3: test eax, eax */
	if (m->zf) goto L_4109e2;	/* 4109c5: je 0x4109e2 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4109c7: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4109ceu; native_call(m, 0x41e760u);	/* 4109c9: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4109ce: add esp, 4 */
	M32((DWORD)(0x4dc4b0u)) = 0x5u;	/* 4109d1: mov dword ptr [0x4dc4b0], 5 */
	m->esp -= 4; M32(m->esp) = 0x4109e0u; native_call(m, 0x40f590u);	/* 4109db: call 0x40f590 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4109e0: pop esi */
	m->esp += 4 + 0; return;	/* 4109e1: ret  */
L_4109e2:
	m->ecx = M32((DWORD)(0x4e151cu));	/* 4109e2: mov ecx, dword ptr [0x4e151c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4109e8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4109eeu; native_call(m, 0x401600u);	/* 4109e9: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4109ee: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4109f1: test eax, eax */
	if (m->zf) goto L_410a13;	/* 4109f3: je 0x410a13 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4109f5: push 2 */
	m->esp -= 4; M32(m->esp) = 0x4109fcu; native_call(m, 0x41e760u);	/* 4109f7: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dceacu));	/* 4109fc: mov eax, dword ptr [0x4dceac] */
	m->edx = 0x1u;	/* 410a01: mov edx, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410a06: add esp, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 410a09: sub edx, eax */
	M32((DWORD)(0x4dceacu)) = m->edx;	/* 410a0b: mov dword ptr [0x4dceac], edx */
	m->esi = M32(m->esp); m->esp += 4;	/* 410a11: pop esi */
	m->esp += 4 + 0; return;	/* 410a12: ret  */
L_410a13:
	m->eax = M32((DWORD)(0x9db0a0u));	/* 410a13: mov eax, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 410a18: push eax */
	m->esp -= 4; M32(m->esp) = 0x410a1eu; native_call(m, 0x401600u);	/* 410a19: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410a1e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410a21: test eax, eax */
	if (m->zf) goto L_410a4d;	/* 410a23: je 0x410a4d */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410a25: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410a2cu; native_call(m, 0x41e760u);	/* 410a27: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 410a2c: mov eax, dword ptr [0x4dc4b0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410a31: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410a34: dec eax */
	M32((DWORD)(0x4dc4b0u)) = m->eax;	/* 410a35: mov dword ptr [0x4dc4b0], eax */
	if (!m->sf) goto L_410aaa;	/* 410a3a: jns 0x410aaa */
	M32((DWORD)(0x4dc4b0u)) = 0x5u;	/* 410a3c: mov dword ptr [0x4dc4b0], 5 */
	m->esp -= 4; M32(m->esp) = 0x410a4bu; native_call(m, 0x40f590u);	/* 410a46: call 0x40f590 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410a4b: pop esi */
	m->esp += 4 + 0; return;	/* 410a4c: ret  */
L_410a4d:
	m->ecx = M32((DWORD)(0x76d330u));	/* 410a4d: mov ecx, dword ptr [0x76d330] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 410a53: push ecx */
	m->esp -= 4; M32(m->esp) = 0x410a59u; native_call(m, 0x401600u);	/* 410a54: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410a59: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410a5c: test eax, eax */
	if (m->zf) goto L_410a86;	/* 410a5e: je 0x410a86 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 410a60: push 2 */
	m->esp -= 4; M32(m->esp) = 0x410a67u; native_call(m, 0x41e760u);	/* 410a62: call 0x41e760 */
	m->eax = M32((DWORD)(0x4dc4b0u));	/* 410a67: mov eax, dword ptr [0x4dc4b0] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410a6c: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 410a6f: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410a70: cmp eax, 5 */
	M32((DWORD)(0x4dc4b0u)) = m->eax;	/* 410a73: mov dword ptr [0x4dc4b0], eax */
	if (m->zf || m->sf != m->of) goto L_410aaa;	/* 410a78: jle 0x410aaa */
	M32((DWORD)(0x4dc4b0u)) = 0x0u;	/* 410a7a: mov dword ptr [0x4dc4b0], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410a84: pop esi */
	m->esp += 4 + 0; return;	/* 410a85: ret  */
L_410a86:
	m->edx = M32((DWORD)(0x76d48cu));	/* 410a86: mov edx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 410a8c: push edx */
	m->esp -= 4; M32(m->esp) = 0x410a92u; native_call(m, 0x401600u);	/* 410a8d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410a92: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 410a95: test eax, eax */
	if (m->zf) goto L_410aaa;	/* 410a97: je 0x410aaa */
L_410a99:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 410a99: push 0 */
	m->esp -= 4; M32(m->esp) = 0x410aa0u; native_call(m, 0x41e760u);	/* 410a9b: call 0x41e760 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 410aa0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x410aa7u; native_call(m, 0x40f0f0u);	/* 410aa2: call 0x40f0f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 410aa7: add esp, 8 */
L_410aaa:
	m->esi = M32(m->esp); m->esp += 4;	/* 410aaa: pop esi */
	m->esp += 4 + 0; return;	/* 410aab: ret  */
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
