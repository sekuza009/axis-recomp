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

static void lift_40f0f0(X86 *m);
static void lift_40f950(X86 *m);

/* armc_40f950 (0x40f950), lifted by tools/lift.py */
static void lift_40f950(X86 *m)
{
	m->eax = M32((DWORD)(0x4dbe48u));	/* 40f950: mov eax, dword ptr [0x4dbe48] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f955: cmp eax, 3 */
	m->eax = M32((DWORD)(0x4dc77cu));	/* 40f958: mov eax, dword ptr [0x4dc77c] */
	if (!m->zf && m->sf == m->of) goto L_40f990;	/* 40f95d: jg 0x40f990 */
	m->ecx = M32((DWORD)(0x4dc244u));	/* 40f95f: mov ecx, dword ptr [0x4dc244] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f965: cmp eax, ecx */
	if (m->sf != m->of) goto L_40f97a;	/* 40f967: jl 0x40f97a */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f969: xor eax, eax */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 40f96b: mov dword ptr [0x4dc77c], eax */
	m->eax = M32((DWORD)(m->eax*4 + 0x4dc79cu));	/* 40f970: mov eax, dword ptr [eax*4 + 0x4dc79c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40f977: push eax */
	goto L_40f9b2;	/* 40f978: jmp 0x40f9b2 */
L_40f97a:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40f97a: test eax, eax */
	if (m->sf == m->of) goto L_40f986;	/* 40f97c: jge 0x40f986 */
	m->eax = (DWORD)(m->ecx + 0xffffffffu);	/* 40f97e: lea eax, [ecx - 1] */
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 40f981: mov dword ptr [0x4dc77c], eax */
L_40f986:
	m->eax = M32((DWORD)(m->eax*4 + 0x4dc79cu));	/* 40f986: mov eax, dword ptr [eax*4 + 0x4dc79c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40f98d: push eax */
	goto L_40f9b2;	/* 40f98e: jmp 0x40f9b2 */
L_40f990:
	m->ecx = M32((DWORD)(0x4dc778u));	/* 40f990: mov ecx, dword ptr [0x4dc778] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f996: cmp eax, ecx */
	if (m->sf != m->of) goto L_40f99e;	/* 40f998: jl 0x40f99e */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f99a: xor eax, eax */
	goto L_40f9a5;	/* 40f99c: jmp 0x40f9a5 */
L_40f99e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40f99e: test eax, eax */
	if (m->sf == m->of) goto L_40f9aa;	/* 40f9a0: jge 0x40f9aa */
	m->eax = (DWORD)(m->ecx + 0xffffffffu);	/* 40f9a2: lea eax, [ecx - 1] */
L_40f9a5:
	M32((DWORD)(0x4dc77cu)) = m->eax;	/* 40f9a5: mov dword ptr [0x4dc77c], eax */
L_40f9aa:
	m->ecx = M32((DWORD)(m->eax*4 + 0x4dcca4u));	/* 40f9aa: mov ecx, dword ptr [eax*4 + 0x4dcca4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40f9b1: push ecx */
L_40f9b2:
	m->esp -= 4; M32(m->esp) = 0x40f9b7u; native_call(m, 0x41cca0u);	/* 40f9b2: call 0x41cca0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40f9b7: add esp, 4 */
	{ DWORD v_ = 0x6u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f9ba: push 6 */
	m->esp -= 4; M32(m->esp) = 0x40f9c1u; native_call(m, 0x419000u);	/* 40f9bc: call 0x419000 */
	m->edx = M32((DWORD)(0x4dbe48u));	/* 40f9c1: mov edx, dword ptr [0x4dbe48] */
	m->ecx = M32((DWORD)(0x9087b4u));	/* 40f9c7: mov ecx, dword ptr [0x9087b4] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40f9cd: add esp, 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40f9d0: push edx */
	m->esp -= 4; M32(m->esp) = 0x40f9d6u; native_call(m, 0x461540u);	/* 40f9d1: call 0x461540 */
	native_call(m, 0x41c510u); return;	/* 40f9d6: jmp 0x41c510 */
}

/* armc_exit (0x40f0f0), lifted by tools/lift.py */
static void lift_40f0f0(X86 *m)
{
	m->eax = M32((DWORD)(0x4dc24cu));	/* 40f0f0: mov eax, dword ptr [0x4dc24c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f0f5: dec eax */
	if (m->zf) goto L_40f143;	/* 40f0f6: je 0x40f143 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f0f8: dec eax */
	if (m->zf) goto L_40f123;	/* 40f0f9: je 0x40f123 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 40f0fb: dec eax */
	if (!m->zf) goto L_40f166;	/* 40f0fc: jne 0x40f166 */
	m->esp -= 4; M32(m->esp) = 0x40f103u; native_call(m, 0x40e670u);	/* 40f0fe: call 0x40e670 */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 40f103: mov ecx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f107: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f109: cmp ecx, eax */
	M32((DWORD)(0x4dc790u)) = m->eax;	/* 40f10b: mov dword ptr [0x4dc790], eax */
	M32((DWORD)(0x4e1870u)) = 0x3dcccccdu;	/* 40f110: mov dword ptr [0x4e1870], 0x3dcccccd */
	if (m->zf) goto L_40f166;	/* 40f11a: je 0x40f166 */
	m->esp -= 4; M32(m->esp) = 0x40f121u; native_call(m, 0x40e930u);	/* 40f11c: call 0x40e930 */
	goto L_40f166;	/* 40f121: jmp 0x40f166 */
L_40f123:
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 40f123: mov ecx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f127: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f129: cmp ecx, eax */
	M32((DWORD)(0x4dc790u)) = m->eax;	/* 40f12b: mov dword ptr [0x4dc790], eax */
	M32((DWORD)(0x4e1870u)) = 0x3dcccccdu;	/* 40f130: mov dword ptr [0x4e1870], 0x3dcccccd */
	M32((DWORD)(0x4db51cu)) = m->eax;	/* 40f13a: mov dword ptr [0x4db51c], eax */
	if (m->zf) goto L_40f166;	/* 40f13f: je 0x40f166 */
	goto L_40f161;	/* 40f141: jmp 0x40f161 */
L_40f143:
	m->esp -= 4; M32(m->esp) = 0x40f148u; native_call(m, 0x40e670u);	/* 40f143: call 0x40e670 */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 40f148: mov ecx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 40f14c: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f14e: cmp ecx, eax */
	M32((DWORD)(0x4dc790u)) = m->eax;	/* 40f150: mov dword ptr [0x4dc790], eax */
	M32((DWORD)(0x4e1870u)) = 0x3dcccccdu;	/* 40f155: mov dword ptr [0x4e1870], 0x3dcccccd */
	if (m->zf) goto L_40f166;	/* 40f15f: je 0x40f166 */
L_40f161:
	m->esp -= 4; M32(m->esp) = 0x40f166u; native_call(m, 0x40e7a0u);	/* 40f161: call 0x40e7a0 */
L_40f166:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 40f166: push 4 */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 40f168: mov dword ptr [0x4df028], 0 */
	M32((DWORD)(0x4df02cu)) = 0x44c80000u;	/* 40f172: mov dword ptr [0x4df02c], 0x44c80000 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 40f17c: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0x0u;	/* 40f186: mov dword ptr [0x680380], 0 */
	M32((DWORD)(0x4dcf10u)) = 0x1u;	/* 40f190: mov dword ptr [0x4dcf10], 1 */
	M32((DWORD)(0x4b0704u)) = 0x41200000u;	/* 40f19a: mov dword ptr [0x4b0704], 0x41200000 */
	M32((DWORD)(0x4b0708u)) = 0x42400000u;	/* 40f1a4: mov dword ptr [0x4b0708], 0x42400000 */
	M32((DWORD)(0x4b070cu)) = 0x3e4ccccdu;	/* 40f1ae: mov dword ptr [0x4b070c], 0x3e4ccccd */
	M32((DWORD)(0x4b0710u)) = 0xbe4ccccdu;	/* 40f1b8: mov dword ptr [0x4b0710], 0xbe4ccccd */
	m->esp -= 4; M32(m->esp) = 0x40f1c7u; native_call(m, 0x41e760u);	/* 40f1c2: call 0x41e760 */
	{ DWORD v_ = 0x4b01ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 40f1c7: push 0x4b01cc */
	m->esp -= 4; M32(m->esp) = 0x40f1d1u; native_call(m, 0x457150u);	/* 40f1cc: call 0x457150 */
	m->eax = M32((DWORD)(0x76d410u));	/* 40f1d1: mov eax, dword ptr [0x76d410] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40f1d6: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f1d9: cmp eax, 1 */
	if (!m->zf) goto L_40f1f1;	/* 40f1dc: jne 0x40f1f1 */
	{ DWORD a_ = M32((DWORD)(0x9da49cu)), b_ = 0x66u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40f1de: cmp dword ptr [0x9da49c], 0x66 */
	if (!m->zf) goto L_40f1f1;	/* 40f1e5: jne 0x40f1f1 */
	M32((DWORD)(0x9da49cu)) = 0x67u;	/* 40f1e7: mov dword ptr [0x9da49c], 0x67 */
L_40f1f1:
	m->esp += 4 + 0; return;	/* 40f1f1: ret  */
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
