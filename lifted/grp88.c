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

static void lift_43ede0(X86 *m);
static void lift_44f810(X86 *m);

/* profile_44f810 (0x44f810), lifted by tools/lift.py */
static void lift_44f810(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 44f810: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f815: test eax, eax */
	if (m->zf) goto L_44f83c;	/* 44f817: je 0x44f83c */
	m->eax = M32((DWORD)(0x9f682cu));	/* 44f819: mov eax, dword ptr [0x9f682c] */
	m->ecx = M32((DWORD)(0x9f6830u));	/* 44f81e: mov ecx, dword ptr [0x9f6830] */
	m->edx = M32((DWORD)(0x9f8c50u));	/* 44f824: mov edx, dword ptr [0x9f8c50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f82a: push eax */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44f82b: mov eax, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f830: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f831: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f832: push eax */
	m->esp -= 4; M32(m->esp) = 0x44f838u; native_call(m, 0x428c30u);	/* 44f833: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f838: add esp, 0x10 */
	m->esp += 4 + 0; return;	/* 44f83b: ret  */
L_44f83c:
	m->eax = M32((DWORD)(0x9f8d68u));	/* 44f83c: mov eax, dword ptr [0x9f8d68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f841: test eax, eax */
	if (m->zf) goto L_44f84a;	/* 44f843: je 0x44f84a */
	m->esp -= 4; M32(m->esp) = 0x44f84au; native_call(m, 0x44bc50u);	/* 44f845: call 0x44bc50 */
L_44f84a:
	native_call(m, 0x44e640u); return;	/* 44f84a: jmp 0x44e640 */
}

/* room_43ede0 (0x43ede0), lifted by tools/lift.py */
static void lift_43ede0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd350u));	/* 43ede0: mov eax, dword ptr [0x9dd350] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43ede5: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43ede6: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ede8: cmp eax, esi */
	if (m->zf) goto L_43ee7c;	/* 43edea: je 0x43ee7c */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43edf0: mov eax, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43edf5: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_43ee30;	/* 43edf8: ja 0x43ee30 */
	switch (m->eax) { case 0: goto L_43ee01; case 1: goto L_43ee16; case 2: goto L_43ee24; case 3: goto L_43ee0e; default: abort(); }	/* 43edfa: jmp dword ptr [eax*4 + 0x43ef60] */
L_43ee01:
	m->eax = M32((DWORD)(0xa0b324u));	/* 43ee01: mov eax, dword ptr [0xa0b324] */
	M32((DWORD)(m->eax + 0x0u)) = 0x25u;	/* 43ee06: mov dword ptr [eax], 0x25 */
	goto L_43ee30;	/* 43ee0c: jmp 0x43ee30 */
L_43ee0e:
	M32((DWORD)(0x9dd350u)) = m->esi;	/* 43ee0e: mov dword ptr [0x9dd350], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43ee14: pop esi */
	m->esp += 4 + 0; return;	/* 43ee15: ret  */
L_43ee16:
	m->ecx = M32((DWORD)(0xa0b324u));	/* 43ee16: mov ecx, dword ptr [0xa0b324] */
	M32((DWORD)(m->ecx + 0x0u)) = 0x23u;	/* 43ee1c: mov dword ptr [ecx], 0x23 */
	goto L_43ee30;	/* 43ee22: jmp 0x43ee30 */
L_43ee24:
	m->edx = M32((DWORD)(0xa0b324u));	/* 43ee24: mov edx, dword ptr [0xa0b324] */
	M32((DWORD)(m->edx + 0x0u)) = 0x26u;	/* 43ee2a: mov dword ptr [edx], 0x26 */
L_43ee30:
	m->eax = M32((DWORD)(0x9dd6acu));	/* 43ee30: mov eax, dword ptr [0x9dd6ac] */
	{ DWORD v_ = 0x65u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ee35: push 0x65 */
	{ DWORD v_ = 0x15u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ee37: push 0x15 */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43ee39: lea ecx, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x5u);	/* 43ee3c: lea edx, [eax + eax*4 + 5] */
	m->eax = M32((DWORD)(0xa0b324u));	/* 43ee40: mov eax, dword ptr [0xa0b324] */
	m->ecx = (DWORD)(m->ecx + m->ecx*1 + 0x1u);	/* 43ee45: lea ecx, [ecx + ecx + 1] */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43ee49: shl edx, 1 */
	M32((DWORD)(0x9dd83cu)) = m->ecx;	/* 43ee4b: mov dword ptr [0x9dd83c], ecx */
	M32((DWORD)(0x9dd7dcu)) = m->edx;	/* 43ee51: mov dword ptr [0x9dd7dc], edx */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 43ee57: mov dword ptr [eax + 4], ecx */
	m->esp -= 4; M32(m->esp) = 0x43ee5fu; native_call(m, 0x4521c0u);	/* 43ee5a: call 0x4521c0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ee5f: add esp, 8 */
	M32((DWORD)(0x9dd350u)) = m->esi;	/* 43ee62: mov dword ptr [0x9dd350], esi */
	M32((DWORD)(0x4dba80u)) = 0x447a0000u;	/* 43ee68: mov dword ptr [0x4dba80], 0x447a0000 */
	M32((DWORD)(0x9dd6b8u)) = 0x1u;	/* 43ee72: mov dword ptr [0x9dd6b8], 1 */
L_43ee7c:
	m->esp -= 4; M32(m->esp) = 0x43ee81u; native_call(m, 0x4388e0u);	/* 43ee7c: call 0x4388e0 */
	m->eax = M32((DWORD)(0x9dce48u));	/* 43ee81: mov eax, dword ptr [0x9dce48] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ee86: cmp eax, 1 */
	if (m->zf) goto L_43ef5d;	/* 43ee89: je 0x43ef5d */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ee8f: cmp eax, esi */
	if (m->zf) goto L_43ef5d;	/* 43ee91: je 0x43ef5d */
	{ DWORD a_ = M32((DWORD)(0x9dd834u)), b_ = 0x63u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ee97: cmp dword ptr [0x9dd834], 0x63 */
	if (m->zf) goto L_43ef5d;	/* 43ee9e: je 0x43ef5d */
	{ DWORD a_ = M32((DWORD)(0x90d1c4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43eea4: cmp dword ptr [0x90d1c4], esi */
	if (m->zf) goto L_43eee8;	/* 43eeaa: je 0x43eee8 */
	m->ecx = M32((DWORD)(0x9dcee4u));	/* 43eeac: mov ecx, dword ptr [0x9dcee4] */
	m->edx = M32((DWORD)(0x9dcee0u));	/* 43eeb2: mov edx, dword ptr [0x9dcee0] */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43eeb8: mov eax, dword ptr [0x9dcedc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43eebd: push ecx */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43eebe: mov ecx, dword ptr [0x9dced8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43eec4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43eec5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43eec6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43eeccu; native_call(m, 0x428c30u);	/* 43eec7: call 0x428c30 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 43eecc: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43eed1: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43eed4: cmp eax, esi */
	if (!m->zf) goto L_43ef5d;	/* 43eed6: jne 0x43ef5d */
	M32((DWORD)(0x9dd350u)) = 0x1u;	/* 43eedc: mov dword ptr [0x9dd350], 1 */
	m->esi = M32(m->esp); m->esp += 4;	/* 43eee6: pop esi */
	m->esp += 4 + 0; return;	/* 43eee7: ret  */
L_43eee8:
	{ DWORD a_ = M32((DWORD)(0x9dd6b8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43eee8: cmp dword ptr [0x9dd6b8], esi */
	if (m->zf) goto L_43ef58;	/* 43eeee: je 0x43ef58 */
	{ DWORD a_ = M32((DWORD)(0x76d40cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43eef0: cmp dword ptr [0x76d40c], esi */
	if (m->zf) goto L_43ef29;	/* 43eef6: je 0x43ef29 */
	m->esp -= 4; M32(m->esp) = 0x43eefdu; native_call(m, 0x435770u);	/* 43eef8: call 0x435770 */
	m->edx = M32((DWORD)(0x9dd1d0u));	/* 43eefd: mov edx, dword ptr [0x9dd1d0] */
	m->eax = M32((DWORD)(0x9dd6acu));	/* 43ef03: mov eax, dword ptr [0x9dd6ac] */
	M32((DWORD)(0x9dd6b8u)) = m->esi;	/* 43ef08: mov dword ptr [0x9dd6b8], esi */
	M32((DWORD)(0x9dd3b0u)) = 0x1u;	/* 43ef0e: mov dword ptr [0x9dd3b0], 1 */
	M32((DWORD)(0x76d40cu)) = m->esi;	/* 43ef18: mov dword ptr [0x76d40c], esi */
	M32((DWORD)(0x9dd300u)) = m->edx;	/* 43ef1e: mov dword ptr [0x9dd300], edx */
	M32((DWORD)(0x9dd1b4u)) = m->eax;	/* 43ef24: mov dword ptr [0x9dd1b4], eax */
L_43ef29:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 43ef29: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4ad498u));	/* 43ef2f: fmul dword ptr [0x4ad498] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4dba80u));	/* 43ef35: fsubr dword ptr [0x4dba80] */
	MF((DWORD)(0x4dba80u)) = (float)ST(0);	/* 43ef3b: fst dword ptr [0x4dba80] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 43ef41: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 43ef47: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43ef49: test ah, 1 */
	if (m->zf) goto L_43ef58;	/* 43ef4c: je 0x43ef58 */
	M32((DWORD)(0x4dba80u)) = 0x447a0000u;	/* 43ef4e: mov dword ptr [0x4dba80], 0x447a0000 */
L_43ef58:
	m->esp -= 4; M32(m->esp) = 0x43ef5du; native_call(m, 0x43d060u);	/* 43ef58: call 0x43d060 */
L_43ef5d:
	m->esi = M32(m->esp); m->esp += 4;	/* 43ef5d: pop esi */
	m->esp += 4 + 0; return;	/* 43ef5e: ret  */
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
