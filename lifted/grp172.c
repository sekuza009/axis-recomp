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

static void lift_49d290(X86 *m);

/* match_combatInput (0x49d290), lifted by tools/lift.py */
static void lift_49d290(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d290: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d291: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49d292: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49d293: push edi */
	m->esi = m->ecx;	/* 49d294: mov esi, ecx */
	m->esp -= 4; M32(m->esp) = 0x49d29bu; native_call(m, 0x461f10u);	/* 49d296: call 0x461f10 */
	m->eax = M32((DWORD)(m->esi + 0x233c9e8u));	/* 49d29b: mov eax, dword ptr [esi + 0x233c9e8] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49d2a1: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d2a3: cmp eax, ebx */
	if (m->zf) goto L_49df04;	/* 49d2a5: je 0x49df04 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340d35u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d2ab: cmp dword ptr [esi + 0x2340d35], ebx */
	if (!m->zf) goto L_49dce7;	/* 49d2b1: jne 0x49dce7 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340cf4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49d2b7: cmp dword ptr [esi + 0x2340cf4], ebx */
	if (!m->zf) goto L_49dce7;	/* 49d2bd: jne 0x49dce7 */
	m->ecx = M32((DWORD)(m->esi + 0x233c9fcu));	/* 49d2c3: mov ecx, dword ptr [esi + 0x233c9fc] */
	m->ebx = 0x2u;	/* 49d2c9: mov ebx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d2ce: test ecx, ecx */
	m->edi = 0x1u;	/* 49d2d0: mov edi, 1 */
	if (!m->zf) goto L_49d6c6;	/* 49d2d5: jne 0x49d6c6 */
	m->eax = M32((DWORD)(m->esi + 0x2340cf0u));	/* 49d2db: mov eax, dword ptr [esi + 0x2340cf0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d2e1: test eax, eax */
	if (m->zf) goto L_49d30e;	/* 49d2e3: je 0x49d30e */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 49d2e5: mov eax, dword ptr [esi + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d2e8: test eax, eax */
	if (!m->zf) goto L_49d342;	/* 49d2ea: jne 0x49d342 */
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 49d2ec: mov eax, dword ptr [esi + 0x234240d] */
	m->edx = m->eax;	/* 49d2f2: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49d2f4: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49d2f7: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49d2f9: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49d2fc: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49d2fe: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49d301: add edx, eax */
	m->eax = M32((DWORD)(m->esi + m->edx*8 + 0x1eccb48u));	/* 49d303: mov eax, dword ptr [esi + edx*8 + 0x1eccb48] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d30a: test eax, eax */
	if (!m->zf) goto L_49d342;	/* 49d30c: jne 0x49d342 */
L_49d30e:
	m->eax = M32((DWORD)(0x4def50u));	/* 49d30e: mov eax, dword ptr [0x4def50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d313: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d319u; native_call(m, 0x401600u);	/* 49d314: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d319: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d31c: test eax, eax */
	if (!m->zf) goto L_49d337;	/* 49d31e: jne 0x49d337 */
	m->ecx = M32((DWORD)(0x4def54u));	/* 49d320: mov ecx, dword ptr [0x4def54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d326: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d32cu; native_call(m, 0x401600u);	/* 49d327: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d32c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d32f: test eax, eax */
	if (m->zf) goto L_49d71d;	/* 49d331: je 0x49d71d */
L_49d337:
	M32((DWORD)(m->esi + 0x23432cfu)) = m->edi;	/* 49d337: mov dword ptr [esi + 0x23432cf], edi */
	goto L_49d71d;	/* 49d33d: jmp 0x49d71d */
L_49d342:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d342: test ecx, ecx */
	if (!m->zf) goto L_49d6c6;	/* 49d344: jne 0x49d6c6 */
	m->eax = M32((DWORD)(0x4ded88u));	/* 49d34a: mov eax, dword ptr [0x4ded88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d34f: test eax, eax */
	if (m->zf) goto L_49d35f;	/* 49d351: je 0x49d35f */
	M32((DWORD)(m->esi + 0x234331bu)) = m->edi;	/* 49d353: mov dword ptr [esi + 0x234331b], edi */
	M32((DWORD)(m->esi + 0x2340c68u)) = m->edi;	/* 49d359: mov dword ptr [esi + 0x2340c68], edi */
L_49d35f:
	m->eax = M32((DWORD)(m->esi + 0x23424f2u));	/* 49d35f: mov eax, dword ptr [esi + 0x23424f2] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d365: test eax, eax */
	if (m->sf != m->of) goto L_49d384;	/* 49d367: jl 0x49d384 */
	m->eax = M32((DWORD)(0x4ded8cu));	/* 49d369: mov eax, dword ptr [0x4ded8c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d36e: test eax, eax */
	if (m->zf) goto L_49d384;	/* 49d370: je 0x49d384 */
	M32((DWORD)(m->esi + 0x234331fu)) = m->edi;	/* 49d372: mov dword ptr [esi + 0x234331f], edi */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d378: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d37e: mov dword ptr [esi + 0x23432cb], edi */
L_49d384:
	m->edx = M32((DWORD)(0x4dec90u));	/* 49d384: mov edx, dword ptr [0x4dec90] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d38a: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d390u; native_call(m, 0x401600u);	/* 49d38b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d390: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d393: test eax, eax */
	if (m->zf) goto L_49d3a9;	/* 49d395: je 0x49d3a9 */
	M32((DWORD)(m->esi + 0x23424f2u)) = m->edi;	/* 49d397: mov dword ptr [esi + 0x23424f2], edi */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d39d: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d3a3: mov dword ptr [esi + 0x23432cb], edi */
L_49d3a9:
	m->eax = M32((DWORD)(0x4dec8cu));	/* 49d3a9: mov eax, dword ptr [0x4dec8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d3ae: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d3b4u; native_call(m, 0x401600u);	/* 49d3af: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d3b4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d3b7: test eax, eax */
	if (m->zf) goto L_49d3cd;	/* 49d3b9: je 0x49d3cd */
	M32((DWORD)(m->esi + 0x23424f2u)) = m->ebx;	/* 49d3bb: mov dword ptr [esi + 0x23424f2], ebx */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d3c1: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d3c7: mov dword ptr [esi + 0x23432cb], edi */
L_49d3cd:
	m->ecx = M32((DWORD)(0x4deb5cu));	/* 49d3cd: mov ecx, dword ptr [0x4deb5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d3d3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d3d9u; native_call(m, 0x401600u);	/* 49d3d4: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d3d9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d3dc: test eax, eax */
	if (m->zf) goto L_49d3f6;	/* 49d3de: je 0x49d3f6 */
	M32((DWORD)(m->esi + 0x23424f2u)) = 0x3u;	/* 49d3e0: mov dword ptr [esi + 0x23424f2], 3 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d3ea: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d3f0: mov dword ptr [esi + 0x23432cb], edi */
L_49d3f6:
	m->edx = M32((DWORD)(0x4deb58u));	/* 49d3f6: mov edx, dword ptr [0x4deb58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d3fc: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d402u; native_call(m, 0x401600u);	/* 49d3fd: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d402: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d405: test eax, eax */
	if (m->zf) goto L_49d41f;	/* 49d407: je 0x49d41f */
	M32((DWORD)(m->esi + 0x23424f2u)) = 0x4u;	/* 49d409: mov dword ptr [esi + 0x23424f2], 4 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d413: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d419: mov dword ptr [esi + 0x23432cb], edi */
L_49d41f:
	m->eax = M32((DWORD)(0x4deb64u));	/* 49d41f: mov eax, dword ptr [0x4deb64] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d424: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d42au; native_call(m, 0x401600u);	/* 49d425: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d42a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d42d: test eax, eax */
	if (m->zf) goto L_49d447;	/* 49d42f: je 0x49d447 */
	M32((DWORD)(m->esi + 0x23424f2u)) = 0x5u;	/* 49d431: mov dword ptr [esi + 0x23424f2], 5 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d43b: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d441: mov dword ptr [esi + 0x23432cb], edi */
L_49d447:
	m->ecx = M32((DWORD)(0x4deb60u));	/* 49d447: mov ecx, dword ptr [0x4deb60] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d44d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d453u; native_call(m, 0x401600u);	/* 49d44e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d453: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d456: test eax, eax */
	if (m->zf) goto L_49d470;	/* 49d458: je 0x49d470 */
	M32((DWORD)(m->esi + 0x23424f2u)) = 0x6u;	/* 49d45a: mov dword ptr [esi + 0x23424f2], 6 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d464: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d46a: mov dword ptr [esi + 0x23432cb], edi */
L_49d470:
	m->edx = M32((DWORD)(0x4deb6cu));	/* 49d470: mov edx, dword ptr [0x4deb6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d476: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d47cu; native_call(m, 0x401600u);	/* 49d477: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d47c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d47f: test eax, eax */
	if (m->zf) goto L_49d499;	/* 49d481: je 0x49d499 */
	M32((DWORD)(m->esi + 0x23424f2u)) = 0x7u;	/* 49d483: mov dword ptr [esi + 0x23424f2], 7 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d48d: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d493: mov dword ptr [esi + 0x23432cb], edi */
L_49d499:
	m->eax = M32((DWORD)(0x4deb68u));	/* 49d499: mov eax, dword ptr [0x4deb68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d49e: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d4a4u; native_call(m, 0x401600u);	/* 49d49f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d4a4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d4a7: test eax, eax */
	if (m->zf) goto L_49d4c1;	/* 49d4a9: je 0x49d4c1 */
	M32((DWORD)(m->esi + 0x23424f2u)) = 0x8u;	/* 49d4ab: mov dword ptr [esi + 0x23424f2], 8 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d4b5: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d4bb: mov dword ptr [esi + 0x23432cb], edi */
L_49d4c1:
	m->ecx = M32((DWORD)(0x4deb70u));	/* 49d4c1: mov ecx, dword ptr [0x4deb70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d4c7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d4cdu; native_call(m, 0x401600u);	/* 49d4c8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d4cd: add esp, 4 */
	m->ebx = 0x9u;	/* 49d4d0: mov ebx, 9 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d4d5: test eax, eax */
	if (m->zf) goto L_49d4eb;	/* 49d4d7: je 0x49d4eb */
	M32((DWORD)(m->esi + 0x23424f2u)) = m->ebx;	/* 49d4d9: mov dword ptr [esi + 0x23424f2], ebx */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d4df: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d4e5: mov dword ptr [esi + 0x23432cb], edi */
L_49d4eb:
	m->edx = M32((DWORD)(0x4deb78u));	/* 49d4eb: mov edx, dword ptr [0x4deb78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d4f1: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d4f7u; native_call(m, 0x401600u);	/* 49d4f2: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d4f7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d4fa: test eax, eax */
	if (m->zf) goto L_49d514;	/* 49d4fc: je 0x49d514 */
	M32((DWORD)(m->esi + 0x23424f2u)) = 0x0u;	/* 49d4fe: mov dword ptr [esi + 0x23424f2], 0 */
	M32((DWORD)(m->esi + 0x2340c6cu)) = m->edi;	/* 49d508: mov dword ptr [esi + 0x2340c6c], edi */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->edi;	/* 49d50e: mov dword ptr [esi + 0x23432cb], edi */
L_49d514:
	M32((DWORD)(m->esi + 0x2343307u)) = 0x0u;	/* 49d514: mov dword ptr [esi + 0x2343307], 0 */
	m->eax = M32((DWORD)(0x4e0468u));	/* 49d51e: mov eax, dword ptr [0x4e0468] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d523: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d529u; native_call(m, 0x401600u);	/* 49d524: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d529: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d52c: test eax, eax */
	if (m->zf) goto L_49d54d;	/* 49d52e: je 0x49d54d */
	m->ecx = M32((DWORD)(0x67ef24u));	/* 49d530: mov ecx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d536: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d53cu; native_call(m, 0x401600u);	/* 49d537: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d53c: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 49d53f: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 49d541: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49d543: and eax, 0xa */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49d546: inc eax */
	M32((DWORD)(m->esi + 0x2343307u)) = m->eax;	/* 49d547: mov dword ptr [esi + 0x2343307], eax */
L_49d54d:
	m->edx = M32((DWORD)(0x4e046cu));	/* 49d54d: mov edx, dword ptr [0x4e046c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d553: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d559u; native_call(m, 0x401600u);	/* 49d554: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d559: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d55c: test eax, eax */
	if (m->zf) goto L_49d57e;	/* 49d55e: je 0x49d57e */
	m->eax = M32((DWORD)(0x67ef24u));	/* 49d560: mov eax, dword ptr [0x67ef24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d565: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d56bu; native_call(m, 0x401600u);	/* 49d566: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d56b: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 49d56e: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 49d570: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49d572: and eax, 0xa */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49d575: add eax, 2 */
	M32((DWORD)(m->esi + 0x2343307u)) = m->eax;	/* 49d578: mov dword ptr [esi + 0x2343307], eax */
L_49d57e:
	m->ecx = M32((DWORD)(0x4e0470u));	/* 49d57e: mov ecx, dword ptr [0x4e0470] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d584: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d58au; native_call(m, 0x401600u);	/* 49d585: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d58a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d58d: test eax, eax */
	if (m->zf) goto L_49d5b0;	/* 49d58f: je 0x49d5b0 */
	m->edx = M32((DWORD)(0x67ef24u));	/* 49d591: mov edx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d597: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d59du; native_call(m, 0x401600u);	/* 49d598: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d59d: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 49d5a0: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 49d5a2: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49d5a4: and eax, 0xa */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49d5a7: add eax, 3 */
	M32((DWORD)(m->esi + 0x2343307u)) = m->eax;	/* 49d5aa: mov dword ptr [esi + 0x2343307], eax */
L_49d5b0:
	m->eax = M32((DWORD)(0x4e0874u));	/* 49d5b0: mov eax, dword ptr [0x4e0874] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d5b5: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d5bbu; native_call(m, 0x401600u);	/* 49d5b6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d5bb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d5be: test eax, eax */
	if (m->zf) goto L_49d5e1;	/* 49d5c0: je 0x49d5e1 */
	m->ecx = M32((DWORD)(0x67ef24u));	/* 49d5c2: mov ecx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d5c8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d5ceu; native_call(m, 0x401600u);	/* 49d5c9: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d5ce: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 49d5d1: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 49d5d3: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49d5d5: and eax, 0xa */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49d5d8: add eax, 4 */
	M32((DWORD)(m->esi + 0x2343307u)) = m->eax;	/* 49d5db: mov dword ptr [esi + 0x2343307], eax */
L_49d5e1:
	m->edx = M32((DWORD)(0x4e0c78u));	/* 49d5e1: mov edx, dword ptr [0x4e0c78] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d5e7: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d5edu; native_call(m, 0x401600u);	/* 49d5e8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d5ed: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d5f0: test eax, eax */
	if (m->zf) goto L_49d612;	/* 49d5f2: je 0x49d612 */
	m->eax = M32((DWORD)(0x67ef24u));	/* 49d5f4: mov eax, dword ptr [0x67ef24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d5f9: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d5ffu; native_call(m, 0x401600u);	/* 49d5fa: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d5ff: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 49d602: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 49d604: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49d606: and eax, 0xa */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49d609: add eax, 5 */
	M32((DWORD)(m->esi + 0x2343307u)) = m->eax;	/* 49d60c: mov dword ptr [esi + 0x2343307], eax */
L_49d612:
	m->ecx = M32((DWORD)(0x4e0c7cu));	/* 49d612: mov ecx, dword ptr [0x4e0c7c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d618: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d61eu; native_call(m, 0x401600u);	/* 49d619: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d61e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d621: test eax, eax */
	if (m->zf) goto L_49d644;	/* 49d623: je 0x49d644 */
	m->edx = M32((DWORD)(0x67ef24u));	/* 49d625: mov edx, dword ptr [0x67ef24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d62b: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d631u; native_call(m, 0x401600u);	/* 49d62c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d631: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 49d634: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 49d636: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49d638: and eax, 0xa */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49d63b: add eax, 6 */
	M32((DWORD)(m->esi + 0x2343307u)) = m->eax;	/* 49d63e: mov dword ptr [esi + 0x2343307], eax */
L_49d644:
	m->eax = M32((DWORD)(0x4e0c80u));	/* 49d644: mov eax, dword ptr [0x4e0c80] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d649: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d64fu; native_call(m, 0x401600u);	/* 49d64a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d64f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d652: test eax, eax */
	if (m->zf) goto L_49d660;	/* 49d654: je 0x49d660 */
	M32((DWORD)(m->esi + 0x2343307u)) = 0x7u;	/* 49d656: mov dword ptr [esi + 0x2343307], 7 */
L_49d660:
	m->ecx = M32((DWORD)(0x4e0c84u));	/* 49d660: mov ecx, dword ptr [0x4e0c84] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d666: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d66cu; native_call(m, 0x401600u);	/* 49d667: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d66c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d66f: test eax, eax */
	if (m->zf) goto L_49d67d;	/* 49d671: je 0x49d67d */
	M32((DWORD)(m->esi + 0x2343307u)) = 0x8u;	/* 49d673: mov dword ptr [esi + 0x2343307], 8 */
L_49d67d:
	m->edx = M32((DWORD)(0x4e0c88u));	/* 49d67d: mov edx, dword ptr [0x4e0c88] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d683: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d689u; native_call(m, 0x401600u);	/* 49d684: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d689: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d68c: test eax, eax */
	if (m->zf) goto L_49d696;	/* 49d68e: je 0x49d696 */
	M32((DWORD)(m->esi + 0x2343307u)) = m->ebx;	/* 49d690: mov dword ptr [esi + 0x2343307], ebx */
L_49d696:
	m->eax = M32((DWORD)(0x4e0460u));	/* 49d696: mov eax, dword ptr [0x4e0460] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d69b: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d6a1u; native_call(m, 0x401600u);	/* 49d69c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d6a1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d6a4: test eax, eax */
	if (m->zf) goto L_49d6b2;	/* 49d6a6: je 0x49d6b2 */
	M32((DWORD)(m->esi + 0x2343307u)) = 0xau;	/* 49d6a8: mov dword ptr [esi + 0x2343307], 0xa */
L_49d6b2:
	m->eax = M32((DWORD)(m->esi + 0x2343307u));	/* 49d6b2: mov eax, dword ptr [esi + 0x2343307] */
	m->ebx = 0x2u;	/* 49d6b8: mov ebx, 2 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49d6bd: dec eax */
	M32((DWORD)(m->esi + 0x2343307u)) = m->eax;	/* 49d6be: mov dword ptr [esi + 0x2343307], eax */
	goto L_49d71d;	/* 49d6c4: jmp 0x49d71d */
L_49d6c6:
	m->ecx = M32((DWORD)(0x4def50u));	/* 49d6c6: mov ecx, dword ptr [0x4def50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d6cc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d6d2u; native_call(m, 0x401590u);	/* 49d6cd: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d6d2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d6d5: test eax, eax */
	if (!m->zf) goto L_49d6ec;	/* 49d6d7: jne 0x49d6ec */
	m->edx = M32((DWORD)(0x4def54u));	/* 49d6d9: mov edx, dword ptr [0x4def54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d6df: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d6e5u; native_call(m, 0x401590u);	/* 49d6e0: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d6e5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d6e8: test eax, eax */
	if (m->zf) goto L_49d6f2;	/* 49d6ea: je 0x49d6f2 */
L_49d6ec:
	M32((DWORD)(m->esi + 0x234327bu)) = m->edi;	/* 49d6ec: mov dword ptr [esi + 0x234327b], edi */
L_49d6f2:
	m->eax = M32((DWORD)(0x4def50u));	/* 49d6f2: mov eax, dword ptr [0x4def50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d6f7: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d6fdu; native_call(m, 0x401600u);	/* 49d6f8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d6fd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d700: test eax, eax */
	if (!m->zf) goto L_49d717;	/* 49d702: jne 0x49d717 */
	m->ecx = M32((DWORD)(0x4def54u));	/* 49d704: mov ecx, dword ptr [0x4def54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d70a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d710u; native_call(m, 0x401600u);	/* 49d70b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d710: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d713: test eax, eax */
	if (m->zf) goto L_49d71d;	/* 49d715: je 0x49d71d */
L_49d717:
	M32((DWORD)(m->esi + 0x234327fu)) = m->edi;	/* 49d717: mov dword ptr [esi + 0x234327f], edi */
L_49d71d:
	m->edx = M32((DWORD)(0x4def30u));	/* 49d71d: mov edx, dword ptr [0x4def30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d723: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d729u; native_call(m, 0x401590u);	/* 49d724: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d729: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d72c: test eax, eax */
	if (!m->zf) goto L_49d742;	/* 49d72e: jne 0x49d742 */
	m->eax = M32((DWORD)(0x4def34u));	/* 49d730: mov eax, dword ptr [0x4def34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d735: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d73bu; native_call(m, 0x401590u);	/* 49d736: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d73b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d73e: test eax, eax */
	if (m->zf) goto L_49d748;	/* 49d740: je 0x49d748 */
L_49d742:
	M32((DWORD)(m->esi + 0x234325fu)) = m->edi;	/* 49d742: mov dword ptr [esi + 0x234325f], edi */
L_49d748:
	m->ecx = M32((DWORD)(0x4def10u));	/* 49d748: mov ecx, dword ptr [0x4def10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d74e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d754u; native_call(m, 0x401590u);	/* 49d74f: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d754: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d757: test eax, eax */
	if (!m->zf) goto L_49d76e;	/* 49d759: jne 0x49d76e */
	m->edx = M32((DWORD)(0x4def14u));	/* 49d75b: mov edx, dword ptr [0x4def14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d761: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d767u; native_call(m, 0x401590u);	/* 49d762: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d767: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d76a: test eax, eax */
	if (m->zf) goto L_49d774;	/* 49d76c: je 0x49d774 */
L_49d76e:
	M32((DWORD)(m->esi + 0x234326bu)) = m->edi;	/* 49d76e: mov dword ptr [esi + 0x234326b], edi */
L_49d774:
	m->eax = M32((DWORD)(0x4def18u));	/* 49d774: mov eax, dword ptr [0x4def18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d779: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d77fu; native_call(m, 0x401590u);	/* 49d77a: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d77f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d782: test eax, eax */
	if (!m->zf) goto L_49d799;	/* 49d784: jne 0x49d799 */
	m->ecx = M32((DWORD)(0x4def1cu));	/* 49d786: mov ecx, dword ptr [0x4def1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d78c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d792u; native_call(m, 0x401590u);	/* 49d78d: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d792: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d795: test eax, eax */
	if (m->zf) goto L_49d79f;	/* 49d797: je 0x49d79f */
L_49d799:
	M32((DWORD)(m->esi + 0x234326fu)) = m->edi;	/* 49d799: mov dword ptr [esi + 0x234326f], edi */
L_49d79f:
	m->edx = M32((DWORD)(0x4def00u));	/* 49d79f: mov edx, dword ptr [0x4def00] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d7a5: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d7abu; native_call(m, 0x401590u);	/* 49d7a6: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d7ab: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d7ae: test eax, eax */
	if (!m->zf) goto L_49d7c4;	/* 49d7b0: jne 0x49d7c4 */
	m->eax = M32((DWORD)(0x4def04u));	/* 49d7b2: mov eax, dword ptr [0x4def04] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d7b7: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d7bdu; native_call(m, 0x401590u);	/* 49d7b8: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d7bd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d7c0: test eax, eax */
	if (m->zf) goto L_49d7ca;	/* 49d7c2: je 0x49d7ca */
L_49d7c4:
	M32((DWORD)(m->esi + 0x2343263u)) = m->edi;	/* 49d7c4: mov dword ptr [esi + 0x2343263], edi */
L_49d7ca:
	m->ecx = M32((DWORD)(0x4def08u));	/* 49d7ca: mov ecx, dword ptr [0x4def08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d7d0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d7d6u; native_call(m, 0x401590u);	/* 49d7d1: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d7d6: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d7d9: test eax, eax */
	if (!m->zf) goto L_49d7f0;	/* 49d7db: jne 0x49d7f0 */
	m->edx = M32((DWORD)(0x4def0cu));	/* 49d7dd: mov edx, dword ptr [0x4def0c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d7e3: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d7e9u; native_call(m, 0x401590u);	/* 49d7e4: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d7e9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d7ec: test eax, eax */
	if (m->zf) goto L_49d7f6;	/* 49d7ee: je 0x49d7f6 */
L_49d7f0:
	M32((DWORD)(m->esi + 0x2343267u)) = m->edi;	/* 49d7f0: mov dword ptr [esi + 0x2343267], edi */
L_49d7f6:
	m->eax = M32((DWORD)(0x4def40u));	/* 49d7f6: mov eax, dword ptr [0x4def40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d7fb: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d801u; native_call(m, 0x401590u);	/* 49d7fc: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d801: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d804: test eax, eax */
	if (!m->zf) goto L_49d81b;	/* 49d806: jne 0x49d81b */
	m->ecx = M32((DWORD)(0x4def44u));	/* 49d808: mov ecx, dword ptr [0x4def44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d80e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d814u; native_call(m, 0x401590u);	/* 49d80f: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d814: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d817: test eax, eax */
	if (m->zf) goto L_49d821;	/* 49d819: je 0x49d821 */
L_49d81b:
	M32((DWORD)(m->esi + 0x2343273u)) = m->edi;	/* 49d81b: mov dword ptr [esi + 0x2343273], edi */
L_49d821:
	m->edx = M32((DWORD)(0x4def48u));	/* 49d821: mov edx, dword ptr [0x4def48] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d827: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d82du; native_call(m, 0x401590u);	/* 49d828: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d82d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d830: test eax, eax */
	if (!m->zf) goto L_49d846;	/* 49d832: jne 0x49d846 */
	m->eax = M32((DWORD)(0x4def4cu));	/* 49d834: mov eax, dword ptr [0x4def4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d839: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d83fu; native_call(m, 0x401590u);	/* 49d83a: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d83f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d842: test eax, eax */
	if (m->zf) goto L_49d84c;	/* 49d844: je 0x49d84c */
L_49d846:
	M32((DWORD)(m->esi + 0x2343277u)) = m->edi;	/* 49d846: mov dword ptr [esi + 0x2343277], edi */
L_49d84c:
	m->ecx = M32((DWORD)(0x4def98u));	/* 49d84c: mov ecx, dword ptr [0x4def98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d852: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d858u; native_call(m, 0x401590u);	/* 49d853: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d858: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d85b: test eax, eax */
	if (!m->zf) goto L_49d872;	/* 49d85d: jne 0x49d872 */
	m->edx = M32((DWORD)(0x4def9cu));	/* 49d85f: mov edx, dword ptr [0x4def9c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d865: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d86bu; native_call(m, 0x401590u);	/* 49d866: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d86b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d86e: test eax, eax */
	if (m->zf) goto L_49d878;	/* 49d870: je 0x49d878 */
L_49d872:
	M32((DWORD)(m->esi + 0x234328bu)) = m->edi;	/* 49d872: mov dword ptr [esi + 0x234328b], edi */
L_49d878:
	m->eax = M32((DWORD)(0x4defe0u));	/* 49d878: mov eax, dword ptr [0x4defe0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d87d: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d883u; native_call(m, 0x401590u);	/* 49d87e: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d883: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d886: test eax, eax */
	if (!m->zf) goto L_49d89d;	/* 49d888: jne 0x49d89d */
	m->ecx = M32((DWORD)(0x4defe4u));	/* 49d88a: mov ecx, dword ptr [0x4defe4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d890: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d896u; native_call(m, 0x401590u);	/* 49d891: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d896: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d899: test eax, eax */
	if (m->zf) goto L_49d8a3;	/* 49d89b: je 0x49d8a3 */
L_49d89d:
	M32((DWORD)(m->esi + 0x234328fu)) = m->edi;	/* 49d89d: mov dword ptr [esi + 0x234328f], edi */
L_49d8a3:
	m->edx = M32((DWORD)(0x4def38u));	/* 49d8a3: mov edx, dword ptr [0x4def38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d8a9: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d8afu; native_call(m, 0x401590u);	/* 49d8aa: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d8af: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d8b2: test eax, eax */
	if (!m->zf) goto L_49d8c8;	/* 49d8b4: jne 0x49d8c8 */
	m->eax = M32((DWORD)(0x4def3cu));	/* 49d8b6: mov eax, dword ptr [0x4def3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d8bb: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d8c1u; native_call(m, 0x401590u);	/* 49d8bc: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d8c1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d8c4: test eax, eax */
	if (m->zf) goto L_49d8ce;	/* 49d8c6: je 0x49d8ce */
L_49d8c8:
	M32((DWORD)(m->esi + 0x2343283u)) = m->edi;	/* 49d8c8: mov dword ptr [esi + 0x2343283], edi */
L_49d8ce:
	M32((DWORD)(m->esi + 0x2343287u)) = 0xffffffffu;	/* 49d8ce: mov dword ptr [esi + 0x2343287], 0xffffffff */
	m->ecx = M32((DWORD)(0x4def78u));	/* 49d8d8: mov ecx, dword ptr [0x4def78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d8de: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d8e4u; native_call(m, 0x401590u);	/* 49d8df: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d8e4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d8e7: test eax, eax */
	if (!m->zf) goto L_49d8fe;	/* 49d8e9: jne 0x49d8fe */
	m->edx = M32((DWORD)(0x4def7cu));	/* 49d8eb: mov edx, dword ptr [0x4def7c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d8f1: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d8f7u; native_call(m, 0x401590u);	/* 49d8f2: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d8f7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d8fa: test eax, eax */
	if (m->zf) goto L_49d908;	/* 49d8fc: je 0x49d908 */
L_49d8fe:
	M32((DWORD)(m->esi + 0x2343287u)) = 0x0u;	/* 49d8fe: mov dword ptr [esi + 0x2343287], 0 */
L_49d908:
	m->eax = M32((DWORD)(0x4def80u));	/* 49d908: mov eax, dword ptr [0x4def80] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d90d: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d913u; native_call(m, 0x401590u);	/* 49d90e: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d913: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d916: test eax, eax */
	if (!m->zf) goto L_49d92d;	/* 49d918: jne 0x49d92d */
	m->ecx = M32((DWORD)(0x4def84u));	/* 49d91a: mov ecx, dword ptr [0x4def84] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d920: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d926u; native_call(m, 0x401590u);	/* 49d921: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d926: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d929: test eax, eax */
	if (m->zf) goto L_49d933;	/* 49d92b: je 0x49d933 */
L_49d92d:
	M32((DWORD)(m->esi + 0x2343287u)) = m->edi;	/* 49d92d: mov dword ptr [esi + 0x2343287], edi */
L_49d933:
	m->edx = M32((DWORD)(0x4def88u));	/* 49d933: mov edx, dword ptr [0x4def88] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d939: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d93fu; native_call(m, 0x401590u);	/* 49d93a: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d93f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d942: test eax, eax */
	if (!m->zf) goto L_49d958;	/* 49d944: jne 0x49d958 */
	m->eax = M32((DWORD)(0x4def8cu));	/* 49d946: mov eax, dword ptr [0x4def8c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d94b: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d951u; native_call(m, 0x401590u);	/* 49d94c: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d951: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d954: test eax, eax */
	if (m->zf) goto L_49d95e;	/* 49d956: je 0x49d95e */
L_49d958:
	M32((DWORD)(m->esi + 0x2343287u)) = m->ebx;	/* 49d958: mov dword ptr [esi + 0x2343287], ebx */
L_49d95e:
	m->ecx = M32((DWORD)(0x4def90u));	/* 49d95e: mov ecx, dword ptr [0x4def90] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d964: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d96au; native_call(m, 0x401590u);	/* 49d965: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d96a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d96d: test eax, eax */
	if (!m->zf) goto L_49d984;	/* 49d96f: jne 0x49d984 */
	m->edx = M32((DWORD)(0x4def94u));	/* 49d971: mov edx, dword ptr [0x4def94] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d977: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d97du; native_call(m, 0x401590u);	/* 49d978: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d97d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d980: test eax, eax */
	if (m->zf) goto L_49d98e;	/* 49d982: je 0x49d98e */
L_49d984:
	M32((DWORD)(m->esi + 0x2343287u)) = 0x3u;	/* 49d984: mov dword ptr [esi + 0x2343287], 3 */
L_49d98e:
	m->eax = M32((DWORD)(0x4def68u));	/* 49d98e: mov eax, dword ptr [0x4def68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d993: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d999u; native_call(m, 0x401590u);	/* 49d994: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d999: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d99c: test eax, eax */
	if (!m->zf) goto L_49d9b3;	/* 49d99e: jne 0x49d9b3 */
	m->ecx = M32((DWORD)(0x4def6cu));	/* 49d9a0: mov ecx, dword ptr [0x4def6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d9a6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49d9acu; native_call(m, 0x401590u);	/* 49d9a7: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d9ac: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d9af: test eax, eax */
	if (m->zf) goto L_49d9bd;	/* 49d9b1: je 0x49d9bd */
L_49d9b3:
	M32((DWORD)(m->esi + 0x2343287u)) = 0x4u;	/* 49d9b3: mov dword ptr [esi + 0x2343287], 4 */
L_49d9bd:
	m->edx = M32((DWORD)(0x4def70u));	/* 49d9bd: mov edx, dword ptr [0x4def70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49d9c3: push edx */
	m->esp -= 4; M32(m->esp) = 0x49d9c9u; native_call(m, 0x401590u);	/* 49d9c4: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d9c9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d9cc: test eax, eax */
	if (!m->zf) goto L_49d9e2;	/* 49d9ce: jne 0x49d9e2 */
	m->eax = M32((DWORD)(0x4def74u));	/* 49d9d0: mov eax, dword ptr [0x4def74] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49d9d5: push eax */
	m->esp -= 4; M32(m->esp) = 0x49d9dbu; native_call(m, 0x401590u);	/* 49d9d6: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49d9db: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49d9de: test eax, eax */
	if (m->zf) goto L_49d9ec;	/* 49d9e0: je 0x49d9ec */
L_49d9e2:
	M32((DWORD)(m->esi + 0x2343287u)) = 0x5u;	/* 49d9e2: mov dword ptr [esi + 0x2343287], 5 */
L_49d9ec:
	m->eax = M32((DWORD)(0x4ded6cu));	/* 49d9ec: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 49d9f1: mov ecx, dword ptr [0x4ded68] */
	M32((DWORD)(m->esi + 0x2343257u)) = m->ecx;	/* 49d9f7: mov dword ptr [esi + 0x2343257], ecx */
	M32((DWORD)(m->esi + 0x234325bu)) = m->eax;	/* 49d9fd: mov dword ptr [esi + 0x234325b], eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 49da03: fld dword ptr [esi + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94f8u)); FPOP();	/* 49da06: fcomp dword ptr [0x4a94f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49da0c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49da0e: test ah, 1 */
	if (m->zf) goto L_49da7e;	/* 49da11: je 0x49da7e */
	m->eax = M32((DWORD)(0x4df000u));	/* 49da13: mov eax, dword ptr [0x4df000] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49da18: test eax, eax */
	if (!m->zf) goto L_49da38;	/* 49da1a: jne 0x49da38 */
	m->esp -= 4; M32(m->esp) = 0x49da21u; native_call(m, 0x4685c0u);	/* 49da1c: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49da21: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49da22: sub eax, edx */
	m->edx = M32((DWORD)(m->esi + 0x234325bu));	/* 49da24: mov edx, dword ptr [esi + 0x234325b] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49da2a: sar eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49da2c: sub edx, eax */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 49da2e: mov dword ptr [esp + 0xc], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 49da32: fild dword ptr [esp + 0xc] */
	goto L_49da54;	/* 49da36: jmp 0x49da54 */
L_49da38:
	m->esp -= 4; M32(m->esp) = 0x49da3du; native_call(m, 0x4685c0u);	/* 49da38: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esi + 0x234325bu));	/* 49da3d: mov ecx, dword ptr [esi + 0x234325b] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49da43: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49da44: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49da46: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49da48: sub ecx, eax */
	M32((DWORD)(m->esp + 0xcu)) = m->ecx;	/* 49da4a: mov dword ptr [esp + 0xc], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 49da4e: fild dword ptr [esp + 0xc] */
	ST(0) = -ST(0);	/* 49da52: fchs  */
L_49da54:
	MF((DWORD)(m->esi + 0x2343293u)) = (float)ST(0); FPOP();	/* 49da54: fstp dword ptr [esi + 0x2343293] */
	m->esp -= 4; M32(m->esp) = 0x49da5fu; native_call(m, 0x4685b0u);	/* 49da5a: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49da5f: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49da60: sub eax, edx */
	m->edx = M32((DWORD)(m->esi + 0x2343257u));	/* 49da62: mov edx, dword ptr [esi + 0x2343257] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49da68: sar eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49da6a: sub edx, eax */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 49da6c: mov dword ptr [esp + 0xc], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 49da70: fild dword ptr [esp + 0xc] */
	ST(0) = -ST(0);	/* 49da74: fchs  */
	MF((DWORD)(m->esi + 0x2343297u)) = (float)ST(0); FPOP();	/* 49da76: fstp dword ptr [esi + 0x2343297] */
	goto L_49da8c;	/* 49da7c: jmp 0x49da8c */
L_49da7e:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49da7e: xor eax, eax */
	M32((DWORD)(m->esi + 0x2343293u)) = m->eax;	/* 49da80: mov dword ptr [esi + 0x2343293], eax */
	M32((DWORD)(m->esi + 0x2343297u)) = m->eax;	/* 49da86: mov dword ptr [esi + 0x2343297], eax */
L_49da8c:
	FPUSH((long double)(int)M32((DWORD)(0x4df008u)));	/* 49da8c: fild dword ptr [0x4df008] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa480u));	/* 49da92: fmul dword ptr [0x4aa480] */
	{ long double t = ST(0); FPUSH(t); }	/* 49da98: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 49da9a: fmulp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 49da9c: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49daa2: fmul dword ptr [0x4a942c] */
	{ long double t = ST(0); FPUSH(t); }	/* 49daa8: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343293u));	/* 49daaa: fmul dword ptr [esi + 0x2343293] */
	MF((DWORD)(m->esi + 0x2343293u)) = (float)ST(0); FPOP();	/* 49dab0: fstp dword ptr [esi + 0x2343293] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343297u));	/* 49dab6: fmul dword ptr [esi + 0x2343297] */
	MF((DWORD)(m->esi + 0x2343297u)) = (float)ST(0); FPOP();	/* 49dabc: fstp dword ptr [esi + 0x2343297] */
	m->esp -= 4; M32(m->esp) = 0x49dac7u; native_call(m, 0x4685b0u);	/* 49dac2: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49dac7: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49dac8: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49daca: sar eax, 1 */
	M32((DWORD)(0x4ded68u)) = m->eax;	/* 49dacc: mov dword ptr [0x4ded68], eax */
	m->esp -= 4; M32(m->esp) = 0x49dad6u; native_call(m, 0x4685c0u);	/* 49dad1: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49dad6: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49dad7: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49dad9: sar eax, 1 */
	M32((DWORD)(0x4ded6cu)) = m->eax;	/* 49dadb: mov dword ptr [0x4ded6c], eax */
	m->eax = M32((DWORD)(0x4defc8u));	/* 49dae0: mov eax, dword ptr [0x4defc8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49dae5: push eax */
	m->esp -= 4; M32(m->esp) = 0x49daebu; native_call(m, 0x401600u);	/* 49dae6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49daeb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49daee: test eax, eax */
	if (!m->zf) goto L_49db05;	/* 49daf0: jne 0x49db05 */
	m->ecx = M32((DWORD)(0x4defccu));	/* 49daf2: mov ecx, dword ptr [0x4defcc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49daf8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49dafeu; native_call(m, 0x401600u);	/* 49daf9: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dafe: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49db01: test eax, eax */
	if (m->zf) goto L_49db1e;	/* 49db03: je 0x49db1e */
L_49db05:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d39u)));	/* 49db05: fld dword ptr [esi + 0x2340d39] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49db0b: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49db11: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49db13: test ah, 0x41 */
	if (m->zf) goto L_49db1e;	/* 49db16: je 0x49db1e */
	M32((DWORD)(m->esi + 0x23432cfu)) = m->edi;	/* 49db18: mov dword ptr [esi + 0x23432cf], edi */
L_49db1e:
	m->edx = M32((DWORD)(0x4def58u));	/* 49db1e: mov edx, dword ptr [0x4def58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49db24: push edx */
	m->esp -= 4; M32(m->esp) = 0x49db2au; native_call(m, 0x401600u);	/* 49db25: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49db2a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49db2d: test eax, eax */
	if (!m->zf) goto L_49db43;	/* 49db2f: jne 0x49db43 */
	m->eax = M32((DWORD)(0x4def5cu));	/* 49db31: mov eax, dword ptr [0x4def5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49db36: push eax */
	m->esp -= 4; M32(m->esp) = 0x49db3cu; native_call(m, 0x401600u);	/* 49db37: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49db3c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49db3f: test eax, eax */
	if (m->zf) goto L_49db49;	/* 49db41: je 0x49db49 */
L_49db43:
	M32((DWORD)(m->esi + 0x23432ebu)) = m->edi;	/* 49db43: mov dword ptr [esi + 0x23432eb], edi */
L_49db49:
	m->ecx = M32((DWORD)(0x4def60u));	/* 49db49: mov ecx, dword ptr [0x4def60] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49db4f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49db55u; native_call(m, 0x401600u);	/* 49db50: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49db55: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49db58: test eax, eax */
	if (!m->zf) goto L_49db6f;	/* 49db5a: jne 0x49db6f */
	m->edx = M32((DWORD)(0x4def64u));	/* 49db5c: mov edx, dword ptr [0x4def64] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49db62: push edx */
	m->esp -= 4; M32(m->esp) = 0x49db68u; native_call(m, 0x401600u);	/* 49db63: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49db68: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49db6b: test eax, eax */
	if (m->zf) goto L_49db75;	/* 49db6d: je 0x49db75 */
L_49db6f:
	M32((DWORD)(m->esi + 0x23432efu)) = m->edi;	/* 49db6f: mov dword ptr [esi + 0x23432ef], edi */
L_49db75:
	m->eax = M32((DWORD)(0x4deff0u));	/* 49db75: mov eax, dword ptr [0x4deff0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49db7a: push eax */
	m->esp -= 4; M32(m->esp) = 0x49db80u; native_call(m, 0x401600u);	/* 49db7b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49db80: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49db83: test eax, eax */
	if (!m->zf) goto L_49db9a;	/* 49db85: jne 0x49db9a */
	m->ecx = M32((DWORD)(0x4deff4u));	/* 49db87: mov ecx, dword ptr [0x4deff4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49db8d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49db93u; native_call(m, 0x401600u);	/* 49db8e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49db93: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49db96: test eax, eax */
	if (m->zf) goto L_49dbc1;	/* 49db98: je 0x49dbc1 */
L_49db9a:
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 49db9a: mov eax, dword ptr [esi + 0x233cc10] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49dba0: dec eax */
	if (m->zf) goto L_49dbbb;	/* 49dba1: je 0x49dbbb */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49dba3: dec eax */
	if (m->zf) goto L_49dbaf;	/* 49dba4: je 0x49dbaf */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49dba6: dec eax */
	M32((DWORD)(m->esi + 0x23424eeu)) = m->edi;	/* 49dba7: mov dword ptr [esi + 0x23424ee], edi */
	goto L_49dbc1;	/* 49dbad: jmp 0x49dbc1 */
L_49dbaf:
	M32((DWORD)(m->esi + 0x23424eeu)) = 0x3u;	/* 49dbaf: mov dword ptr [esi + 0x23424ee], 3 */
	goto L_49dbc1;	/* 49dbb9: jmp 0x49dbc1 */
L_49dbbb:
	M32((DWORD)(m->esi + 0x23424eeu)) = m->ebx;	/* 49dbbb: mov dword ptr [esi + 0x23424ee], ebx */
L_49dbc1:
	m->edx = M32((DWORD)(0x4defa8u));	/* 49dbc1: mov edx, dword ptr [0x4defa8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49dbc7: push edx */
	m->esp -= 4; M32(m->esp) = 0x49dbcdu; native_call(m, 0x401600u);	/* 49dbc8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dbcd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49dbd0: test eax, eax */
	if (!m->zf) goto L_49dbe6;	/* 49dbd2: jne 0x49dbe6 */
	m->eax = M32((DWORD)(0x4defacu));	/* 49dbd4: mov eax, dword ptr [0x4defac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49dbd9: push eax */
	m->esp -= 4; M32(m->esp) = 0x49dbdfu; native_call(m, 0x401600u);	/* 49dbda: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dbdf: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49dbe2: test eax, eax */
	if (m->zf) goto L_49dc01;	/* 49dbe4: je 0x49dc01 */
L_49dbe6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d39u)));	/* 49dbe6: fld dword ptr [esi + 0x2340d39] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49dbec: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49dbf2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49dbf4: test ah, 0x41 */
	if (m->zf) goto L_49dc01;	/* 49dbf7: je 0x49dc01 */
	M32((DWORD)(m->esi + 0x23432fbu)) = m->edi;	/* 49dbf9: mov dword ptr [esi + 0x23432fb], edi */
	goto L_49dc40;	/* 49dbff: jmp 0x49dc40 */
L_49dc01:
	m->ecx = M32((DWORD)(0x4defb0u));	/* 49dc01: mov ecx, dword ptr [0x4defb0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49dc07: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49dc0du; native_call(m, 0x401600u);	/* 49dc08: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dc0d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49dc10: test eax, eax */
	if (!m->zf) goto L_49dc27;	/* 49dc12: jne 0x49dc27 */
	m->edx = M32((DWORD)(0x4defb4u));	/* 49dc14: mov edx, dword ptr [0x4defb4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49dc1a: push edx */
	m->esp -= 4; M32(m->esp) = 0x49dc20u; native_call(m, 0x401600u);	/* 49dc1b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dc20: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49dc23: test eax, eax */
	if (m->zf) goto L_49dc40;	/* 49dc25: je 0x49dc40 */
L_49dc27:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2340d39u)));	/* 49dc27: fld dword ptr [esi + 0x2340d39] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49dc2d: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49dc33: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49dc35: test ah, 0x41 */
	if (m->zf) goto L_49dc40;	/* 49dc38: je 0x49dc40 */
	M32((DWORD)(m->esi + 0x23432ffu)) = m->edi;	/* 49dc3a: mov dword ptr [esi + 0x23432ff], edi */
L_49dc40:
	m->eax = M32((DWORD)(0x4deff8u));	/* 49dc40: mov eax, dword ptr [0x4deff8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49dc45: push eax */
	m->esp -= 4; M32(m->esp) = 0x49dc4bu; native_call(m, 0x401600u);	/* 49dc46: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dc4b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49dc4e: test eax, eax */
	if (!m->zf) goto L_49dc65;	/* 49dc50: jne 0x49dc65 */
	m->ecx = M32((DWORD)(0x4deffcu));	/* 49dc52: mov ecx, dword ptr [0x4deffc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49dc58: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49dc5eu; native_call(m, 0x401600u);	/* 49dc59: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dc5e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49dc61: test eax, eax */
	if (m->zf) goto L_49dc6b;	/* 49dc63: je 0x49dc6b */
L_49dc65:
	M32((DWORD)(m->esi + 0x2343303u)) = m->edi;	/* 49dc65: mov dword ptr [esi + 0x2343303], edi */
L_49dc6b:
	m->edx = M32((DWORD)(0x4df8d0u));	/* 49dc6b: mov edx, dword ptr [0x4df8d0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49dc71: push edx */
	m->esp -= 4; M32(m->esp) = 0x49dc77u; native_call(m, 0x401600u);	/* 49dc72: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dc77: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49dc7a: test eax, eax */
	if (m->zf) goto L_49def5;	/* 49dc7c: je 0x49def5 */
	m->ecx = M32((DWORD)(m->esi + 0x2340ce8u));	/* 49dc82: mov ecx, dword ptr [esi + 0x2340ce8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49dc88: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49dc8a: cmp ecx, eax */
	if (!m->zf) goto L_49dca7;	/* 49dc8c: jne 0x49dca7 */
	{ DWORD v_ = 0x4c7d00u; m->esp -= 4; M32(m->esp) = v_; }	/* 49dc8e: push 0x4c7d00 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49dc93: push esi */
	M32((DWORD)(m->esi + 0x2340ce8u)) = m->edi;	/* 49dc94: mov dword ptr [esi + 0x2340ce8], edi */
	m->esp -= 4; M32(m->esp) = 0x49dc9fu; native_call(m, 0x463450u);	/* 49dc9a: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dc9f: add esp, 8 */
	goto L_49def5;	/* 49dca2: jmp 0x49def5 */
L_49dca7:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340ce4u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49dca7: cmp dword ptr [esi + 0x2340ce4], eax */
	if (!m->zf) goto L_49dcc8;	/* 49dcad: jne 0x49dcc8 */
	{ DWORD v_ = 0x4c7cf0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49dcaf: push 0x4c7cf0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49dcb4: push esi */
	M32((DWORD)(m->esi + 0x2340ce4u)) = m->edi;	/* 49dcb5: mov dword ptr [esi + 0x2340ce4], edi */
	m->esp -= 4; M32(m->esp) = 0x49dcc0u; native_call(m, 0x463450u);	/* 49dcbb: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dcc0: add esp, 8 */
	goto L_49def5;	/* 49dcc3: jmp 0x49def5 */
L_49dcc8:
	{ DWORD v_ = 0x4c7ce4u; m->esp -= 4; M32(m->esp) = v_; }	/* 49dcc8: push 0x4c7ce4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49dccd: push esi */
	M32((DWORD)(m->esi + 0x2340ce8u)) = m->eax;	/* 49dcce: mov dword ptr [esi + 0x2340ce8], eax */
	M32((DWORD)(m->esi + 0x2340ce4u)) = m->eax;	/* 49dcd4: mov dword ptr [esi + 0x2340ce4], eax */
	m->esp -= 4; M32(m->esp) = 0x49dcdfu; native_call(m, 0x463450u);	/* 49dcda: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dcdf: add esp, 8 */
	goto L_49def5;	/* 49dce2: jmp 0x49def5 */
L_49dce7:
	m->eax = M32((DWORD)(m->esi + 0x2340cf4u));	/* 49dce7: mov eax, dword ptr [esi + 0x2340cf4] */
	m->edi = 0x1u;	/* 49dced: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49dcf2: cmp eax, edi */
	if (!m->zf) goto L_49def5;	/* 49dcf4: jne 0x49def5 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 49dcfa: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 49dcff: mov ecx, dword ptr [0x4ded68] */
	M32((DWORD)(m->esi + 0x2343257u)) = m->ecx;	/* 49dd05: mov dword ptr [esi + 0x2343257], ecx */
	M32((DWORD)(m->esi + 0x234325bu)) = m->eax;	/* 49dd0b: mov dword ptr [esi + 0x234325b], eax */
	{ DWORD a_ = M32((DWORD)(0x4df000u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49dd11: cmp dword ptr [0x4df000], ebx */
	if (!m->zf) goto L_49dd35;	/* 49dd17: jne 0x49dd35 */
	m->esp -= 4; M32(m->esp) = 0x49dd1eu; native_call(m, 0x4685c0u);	/* 49dd19: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49dd1e: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49dd1f: sub eax, edx */
	m->edx = M32((DWORD)(m->esi + 0x234325bu));	/* 49dd21: mov edx, dword ptr [esi + 0x234325b] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49dd27: sar eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49dd29: sub edx, eax */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 49dd2b: mov dword ptr [esp + 0xc], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 49dd2f: fild dword ptr [esp + 0xc] */
	goto L_49dd51;	/* 49dd33: jmp 0x49dd51 */
L_49dd35:
	m->esp -= 4; M32(m->esp) = 0x49dd3au; native_call(m, 0x4685c0u);	/* 49dd35: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esi + 0x234325bu));	/* 49dd3a: mov ecx, dword ptr [esi + 0x234325b] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49dd40: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49dd41: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49dd43: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49dd45: sub ecx, eax */
	M32((DWORD)(m->esp + 0xcu)) = m->ecx;	/* 49dd47: mov dword ptr [esp + 0xc], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 49dd4b: fild dword ptr [esp + 0xc] */
	ST(0) = -ST(0);	/* 49dd4f: fchs  */
L_49dd51:
	MF((DWORD)(m->esi + 0x2343293u)) = (float)ST(0); FPOP();	/* 49dd51: fstp dword ptr [esi + 0x2343293] */
	m->esp -= 4; M32(m->esp) = 0x49dd5cu; native_call(m, 0x4685b0u);	/* 49dd57: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49dd5c: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49dd5d: sub eax, edx */
	m->edx = M32((DWORD)(m->esi + 0x2343257u));	/* 49dd5f: mov edx, dword ptr [esi + 0x2343257] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49dd65: sar eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49dd67: sub edx, eax */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 49dd69: mov dword ptr [esp + 0xc], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0xcu)));	/* 49dd6d: fild dword ptr [esp + 0xc] */
	MF((DWORD)(m->esi + 0x2343297u)) = (float)ST(0);	/* 49dd71: fst dword ptr [esi + 0x2343297] */
	FPUSH((long double)(int)M32((DWORD)(0x4df008u)));	/* 49dd77: fild dword ptr [0x4df008] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa480u));	/* 49dd7d: fmul dword ptr [0x4aa480] */
	{ long double t = ST(0); FPUSH(t); }	/* 49dd83: fld st(0) */
	ST(1) = ST(1) * ST(0); FPOP();	/* 49dd85: fmulp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 49dd87: fadd dword ptr [0x4a9424] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49dd8d: fmul dword ptr [0x4a942c] */
	{ long double t = ST(0); FPUSH(t); }	/* 49dd93: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343293u));	/* 49dd95: fmul dword ptr [esi + 0x2343293] */
	MF((DWORD)(m->esi + 0x2343293u)) = (float)ST(0); FPOP();	/* 49dd9b: fstp dword ptr [esi + 0x2343293] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 49dda1: fxch st(1) */
	ST(0) = ST(0) * ST(1);	/* 49dda3: fmul st(1) */
	MF((DWORD)(m->esi + 0x2343297u)) = (float)ST(0); FPOP();	/* 49dda5: fstp dword ptr [esi + 0x2343297] */
	ST(0) = ST(0); FPOP();	/* 49ddab: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x49ddb2u; native_call(m, 0x4685b0u);	/* 49ddad: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49ddb2: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49ddb3: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49ddb5: sar eax, 1 */
	M32((DWORD)(0x4ded68u)) = m->eax;	/* 49ddb7: mov dword ptr [0x4ded68], eax */
	m->esp -= 4; M32(m->esp) = 0x49ddc1u; native_call(m, 0x4685c0u);	/* 49ddbc: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49ddc1: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49ddc2: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49ddc4: sar eax, 1 */
	M32((DWORD)(0x4ded6cu)) = m->eax;	/* 49ddc6: mov dword ptr [0x4ded6c], eax */
	if (M8(0x49ddcbu) == 0x56 && M8(0x49ddccu) == 0xe8 && M8(0x49ddd1u) == 0x59 && M8(0x49ddd2u) == 0xe9 && M8(0x49ddd3u) == 0x4c && M8(0x49ddd4u) == 0x00 && M8(0x49ddd5u) == 0x00 && M8(0x49ddd6u) == 0x00) {	/* the patch DLL's block (12 bytes) */
		{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* patched 49ddcb: push esi */
		m->esp -= 4; M32(m->esp) = 0x49ddd1u; native_call(m, 0x49ddd1u + M32(0x49ddcdu));	/* 0x49ddd1 unless the patch DLL retargets it */	/* patched 49ddcc: call 0x49ddd1 */
		m->ecx = M32(m->esp); m->esp += 4;	/* patched 49ddd1: pop ecx */
		goto L_49de23;	/* patched 49ddd2: jmp 0x49de23 */
	}
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2343293u)));	/* 49ddcb: fld dword ptr [esi + 0x2343293] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9558u)); FPOP();	/* 49ddd1: fcomp dword ptr [0x4a9558] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49ddd7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49ddd9: test ah, 1 */
	if (!m->zf) goto L_49ddf1;	/* 49dddc: jne 0x49ddf1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2343297u)));	/* 49ddde: fld dword ptr [esi + 0x2343297] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9558u)); FPOP();	/* 49dde4: fcomp dword ptr [0x4a9558] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49ddea: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49ddec: test ah, 1 */
	if (m->zf) goto L_49ddf7;	/* 49ddef: je 0x49ddf7 */
L_49ddf1:
	M32((DWORD)(m->esi + 0x234330bu)) = m->edi;	/* 49ddf1: mov dword ptr [esi + 0x234330b], edi */
L_49ddf7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2343293u)));	/* 49ddf7: fld dword ptr [esi + 0x2343293] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9560u)); FPOP();	/* 49ddfd: fcomp dword ptr [0x4a9560] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49de03: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49de05: test ah, 0x41 */
	if (m->zf) goto L_49de1d;	/* 49de08: je 0x49de1d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x2343297u)));	/* 49de0a: fld dword ptr [esi + 0x2343297] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9560u)); FPOP();	/* 49de10: fcomp dword ptr [0x4a9560] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49de16: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49de18: test ah, 0x41 */
	if (!m->zf) goto L_49de23;	/* 49de1b: jne 0x49de23 */
L_49de1d:
	M32((DWORD)(m->esi + 0x234330fu)) = m->edi;	/* 49de1d: mov dword ptr [esi + 0x234330f], edi */
L_49de23:
	m->eax = M32((DWORD)(0x4def50u));	/* 49de23: mov eax, dword ptr [0x4def50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49de28: push eax */
	m->esp -= 4; M32(m->esp) = 0x49de2eu; native_call(m, 0x401600u);	/* 49de29: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49de2e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49de31: test eax, eax */
	if (!m->zf) goto L_49de48;	/* 49de33: jne 0x49de48 */
	m->ecx = M32((DWORD)(0x4def54u));	/* 49de35: mov ecx, dword ptr [0x4def54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49de3b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49de41u; native_call(m, 0x401600u);	/* 49de3c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49de41: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49de44: test eax, eax */
	if (m->zf) goto L_49de4e;	/* 49de46: je 0x49de4e */
L_49de48:
	M32((DWORD)(m->esi + 0x2343313u)) = m->edi;	/* 49de48: mov dword ptr [esi + 0x2343313], edi */
L_49de4e:
	M32((DWORD)(m->esi + 0x2343293u)) = m->ebx;	/* 49de4e: mov dword ptr [esi + 0x2343293], ebx */
	M32((DWORD)(m->esi + 0x2343297u)) = m->ebx;	/* 49de54: mov dword ptr [esi + 0x2343297], ebx */
	m->edx = M32((DWORD)(0x9dae14u));	/* 49de5a: mov edx, dword ptr [0x9dae14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49de60: push edx */
	m->esp -= 4; M32(m->esp) = 0x49de66u; native_call(m, 0x401600u);	/* 49de61: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49de66: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49de69: test eax, eax */
	if (!m->zf) goto L_49de7f;	/* 49de6b: jne 0x49de7f */
	m->eax = M32((DWORD)(0x9db0a0u));	/* 49de6d: mov eax, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49de72: push eax */
	m->esp -= 4; M32(m->esp) = 0x49de78u; native_call(m, 0x401600u);	/* 49de73: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49de78: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49de7b: test eax, eax */
	if (m->zf) goto L_49de85;	/* 49de7d: je 0x49de85 */
L_49de7f:
	M32((DWORD)(m->esi + 0x234330bu)) = m->edi;	/* 49de7f: mov dword ptr [esi + 0x234330b], edi */
L_49de85:
	m->ecx = M32((DWORD)(0x9db974u));	/* 49de85: mov ecx, dword ptr [0x9db974] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49de8b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49de91u; native_call(m, 0x401600u);	/* 49de8c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49de91: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49de94: test eax, eax */
	if (!m->zf) goto L_49deab;	/* 49de96: jne 0x49deab */
	m->edx = M32((DWORD)(0x76d330u));	/* 49de98: mov edx, dword ptr [0x76d330] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49de9e: push edx */
	m->esp -= 4; M32(m->esp) = 0x49dea4u; native_call(m, 0x401600u);	/* 49de9f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dea4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49dea7: test eax, eax */
	if (m->zf) goto L_49deb1;	/* 49dea9: je 0x49deb1 */
L_49deab:
	M32((DWORD)(m->esi + 0x234330fu)) = m->edi;	/* 49deab: mov dword ptr [esi + 0x234330f], edi */
L_49deb1:
	m->eax = M32((DWORD)(0x9dae70u));	/* 49deb1: mov eax, dword ptr [0x9dae70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49deb6: push eax */
	m->esp -= 4; M32(m->esp) = 0x49debcu; native_call(m, 0x401600u);	/* 49deb7: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49debc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49debf: test eax, eax */
	if (!m->zf) goto L_49ded6;	/* 49dec1: jne 0x49ded6 */
	m->ecx = M32((DWORD)(0x5b1da8u));	/* 49dec3: mov ecx, dword ptr [0x5b1da8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49dec9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x49decfu; native_call(m, 0x401600u);	/* 49deca: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49decf: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49ded2: test eax, eax */
	if (m->zf) goto L_49dedc;	/* 49ded4: je 0x49dedc */
L_49ded6:
	M32((DWORD)(m->esi + 0x2343313u)) = m->edi;	/* 49ded6: mov dword ptr [esi + 0x2343313], edi */
L_49dedc:
	m->edx = M32((DWORD)(0x6803a0u));	/* 49dedc: mov edx, dword ptr [0x6803a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49dee2: push edx */
	m->esp -= 4; M32(m->esp) = 0x49dee8u; native_call(m, 0x401600u);	/* 49dee3: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49dee8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49deeb: test eax, eax */
	if (m->zf) goto L_49def5;	/* 49deed: je 0x49def5 */
	M32((DWORD)(m->esi + 0x2343317u)) = m->edi;	/* 49deef: mov dword ptr [esi + 0x2343317], edi */
L_49def5:
	m->esp -= 4; M32(m->esp) = 0x49defau; native_call(m, 0x4a86e0u);	/* 49def5: call 0x4a86e0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49defa: test eax, eax */
	if (m->zf) goto L_49df04;	/* 49defc: je 0x49df04 */
	M32((DWORD)(m->esi + 0x23432cfu)) = m->edi;	/* 49defe: mov dword ptr [esi + 0x23432cf], edi */
L_49df04:
	m->edi = M32(m->esp); m->esp += 4;	/* 49df04: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 49df05: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49df06: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 49df07: pop ecx */
	m->esp += 4 + 0; return;	/* 49df08: ret  */
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
