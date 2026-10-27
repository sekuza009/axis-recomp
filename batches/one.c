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

static void lift_48b5c0(X86 *m);

/* map_loadMissionInfoFrom (0x48b5c0), lifted by tools/lift.py */
static void lift_48b5c0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b5c0: sub esp, 0x108 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5c6: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x110u));	/* 48b5c7: mov ebx, dword ptr [esp + 0x110] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5ce: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5cf: push edi */
	m->edi = m->ecx;	/* 48b5d0: mov edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5d2: push ebx */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 48b5d3: lea ecx, [esp + 0x18] */
	m->eax = (DWORD)(m->edi + 0x108u);	/* 48b5d7: lea eax, [edi + 0x108] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5dd: push eax */
	{ DWORD v_ = 0x4c77f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5de: push 0x4c77f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5e3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b5e9u; native_call(m, 0x49e9ddu);	/* 48b5e4: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 48b5e9: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5ed: push 0x4ad170 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5f2: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b5f8u; native_call(m, 0x49e9cau);	/* 48b5f3: call 0x49e9ca */
	m->esi = m->eax;	/* 48b5f8: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b5fa: add esp, 0x18 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b5fd: test esi, esi */
	if (!m->zf) goto L_48b618;	/* 48b5ff: jne 0x48b618 */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 48b601: lea eax, [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b605: push eax */
	{ DWORD v_ = 0x4c7decu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b606: push 0x4c7dec */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b60b: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48b615u; native_call(m, 0x46c710u);	/* 48b610: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b615: add esp, 0xc */
L_48b618:
	{ DWORD v_ = 0x4c77b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b618: push 0x4c77b4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b61d: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b61f: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b621: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b627u; native_call(m, 0x470fc0u);	/* 48b622: call 0x470fc0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b627: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b628: push 1 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 48b62a: lea ecx, [esp + 0x28] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b62e: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b630: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b636u; native_call(m, 0x49e836u);	/* 48b631: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 48b636: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b63a: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x1201u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b63d: cmp eax, 0x1201 */
	if (m->zf) goto L_48b657;	/* 48b642: je 0x48b657 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b644: push ebx */
	{ DWORD v_ = 0x4c7768u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b645: push 0x4c7768 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b64a: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48b654u; native_call(m, 0x46c710u);	/* 48b64f: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b654: add esp, 0xc */
L_48b657:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b657: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b658: push 1 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 48b65a: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b65e: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b660: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b666u; native_call(m, 0x46cbe0u);	/* 48b661: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 48b666: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b66a: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b66c: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b66d: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b673u; native_call(m, 0x49e91eu);	/* 48b66e: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b673: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b674: push 1 */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 48b676: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b67a: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b67c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b682u; native_call(m, 0x46cbe0u);	/* 48b67d: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 48b682: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b686: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b688: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b689: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b68fu; native_call(m, 0x49e91eu);	/* 48b68a: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b68f: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b690: push 1 */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 48b692: lea eax, [esp + 0x4c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b696: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b698: push eax */
	m->esp -= 4; M32(m->esp) = 0x48b69eu; native_call(m, 0x46cbe0u);	/* 48b699: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b69e: add esp, 0x48 */
	{ DWORD v_ = 0x4c7ddcu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6a1: push 0x4c7ddc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6a6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6a8: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6aa: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b6b0u; native_call(m, 0x470fc0u);	/* 48b6ab: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6b0: add esp, 0x10 */
	m->ecx = m->edi;	/* 48b6b3: mov ecx, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6b5: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b6bbu; native_call(m, 0x48b460u);	/* 48b6b6: call 0x48b460 */
	{ DWORD v_ = 0x4c7dccu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6bb: push 0x4c7dcc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6c0: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6c2: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6c4: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b6cau; native_call(m, 0x470fc0u);	/* 48b6c5: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6ca: add esp, 0x10 */
	m->ecx = m->edi;	/* 48b6cd: mov ecx, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6cf: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b6d5u; native_call(m, 0x48b4a0u);	/* 48b6d0: call 0x48b4a0 */
	{ DWORD v_ = 0x4c7dbcu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6d5: push 0x4c7dbc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6da: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6dc: push 0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6de: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b6e4u; native_call(m, 0x470fc0u);	/* 48b6df: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6e4: add esp, 0x10 */
	m->ecx = m->edi;	/* 48b6e7: mov ecx, edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6e9: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b6efu; native_call(m, 0x48b530u);	/* 48b6ea: call 0x48b530 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b6ef: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b6f5u; native_call(m, 0x49e7e0u);	/* 48b6f0: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6f5: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48b6f8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48b6f9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48b6fa: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b6fb: add esp, 0x108 */
	m->esp += 4 + 4; return;	/* 48b701: ret 4 */
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
