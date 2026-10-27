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

static void lift_4988e0(X86 *m);

/* game_processGameMode (0x4988e0), lifted by tools/lift.py */
static void lift_4988e0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4988e0: sub esp, 0x2a0 */
	m->eax = M32((DWORD)(0x9f67ecu));	/* 4988e6: mov eax, dword ptr [0x9f67ec] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4988eb: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4988ec: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4988ed: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4988ee: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4988ef: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4988f1: cmp eax, edi */
	m->ebp = m->ecx;	/* 4988f3: mov ebp, ecx */
	M32((DWORD)(m->esp + 0x9cu)) = 0x4b21b8u;	/* 4988f5: mov dword ptr [esp + 0x9c], 0x4b21b8 */
	M32((DWORD)(m->esp + 0xa0u)) = 0x4b21b0u;	/* 498900: mov dword ptr [esp + 0xa0], 0x4b21b0 */
	M32((DWORD)(m->esp + 0xa4u)) = 0x4d06ecu;	/* 49890b: mov dword ptr [esp + 0xa4], 0x4d06ec */
	m->ebx = 0x1u;	/* 498916: mov ebx, 1 */
	if (m->zf) goto L_498ab7;	/* 49891b: je 0x498ab7 */
	{ DWORD a_ = M32((DWORD)(0x76d410u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498921: cmp dword ptr [0x76d410], edi */
	if (m->zf) goto L_498ab7;	/* 498927: je 0x498ab7 */
	{ DWORD v_ = 0x4b21a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 49892d: push 0x4b21a4 */
	{ DWORD v_ = 0x4d06e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 498932: push 0x4d06e0 */
	m->esp -= 4; M32(m->esp) = 0x49893cu; native_call(m, 0x49e9cau);	/* 498937: call 0x49e9ca */
	m->ecx = M32((DWORD)(0x4df8e8u));	/* 49893c: mov ecx, dword ptr [0x4df8e8] */
	m->edx = M32((DWORD)(0x9dad94u));	/* 498942: mov edx, dword ptr [0x9dad94] */
	m->esi = m->eax;	/* 498948: mov esi, eax */
	m->eax = M32((DWORD)(m->ebp + 0x2342976u));	/* 49894a: mov eax, dword ptr [ebp + 0x2342976] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498950: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498953: cmp eax, ebx */
	m->eax = M32((DWORD)(0x76d408u));	/* 498955: mov eax, dword ptr [0x76d408] */
	M32((DWORD)(m->esp + 0x3cu)) = m->esi;	/* 49895a: mov dword ptr [esp + 0x3c], esi */
	{ DWORD v_ = 0x4dedd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 49895e: push 0x4dedd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498963: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498964: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498965: push edx */
	{ DWORD v_ = 0x67fb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 498966: push 0x67fb44 */
	if (!m->zf && m->sf == m->of) goto L_498974;	/* 49896b: jg 0x498974 */
	{ DWORD v_ = 0x4d069cu; m->esp -= 4; M32(m->esp) = v_; }	/* 49896d: push 0x4d069c */
	goto L_498979;	/* 498972: jmp 0x498979 */
L_498974:
	{ DWORD v_ = 0x4d0658u; m->esp -= 4; M32(m->esp) = v_; }	/* 498974: push 0x4d0658 */
L_498979:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 498979: push esi */
	m->esp -= 4; M32(m->esp) = 0x49897fu; native_call(m, 0x49f135u);	/* 49897a: call 0x49f135 */
	m->eax = M32((DWORD)(m->ebp + 0x2342976u));	/* 49897f: mov eax, dword ptr [ebp + 0x2342976] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498985: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498988: cmp eax, edi */
	M32((DWORD)(m->esp + 0x28u)) = m->edi;	/* 49898a: mov dword ptr [esp + 0x28], edi */
	if (m->zf || m->sf != m->of) goto L_498a93;	/* 49898e: jle 0x498a93 */
	m->ebx = (DWORD)(m->ebp + 0x23428f6u);	/* 498994: lea ebx, [ebp + 0x23428f6] */
L_49899a:
	m->eax = M32((DWORD)(0x76d368u));	/* 49899a: mov eax, dword ptr [0x76d368] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49899f: cmp eax, 1 */
	if (m->zf) goto L_4989c7;	/* 4989a2: je 0x4989c7 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4989a4: cmp eax, 3 */
	if (m->zf) goto L_4989c7;	/* 4989a7: je 0x4989c7 */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4989a9: cmp eax, 5 */
	if (m->zf) goto L_4989c7;	/* 4989ac: je 0x4989c7 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4989ae: cmp eax, 7 */
	if (m->zf) goto L_4989c7;	/* 4989b1: je 0x4989c7 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4989b3: cmp eax, 9 */
	if (m->zf) goto L_4989c7;	/* 4989b6: je 0x4989c7 */
	{ DWORD a_ = m->eax, b_ = 0xbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4989b8: cmp eax, 0xb */
	if (m->zf) goto L_4989c7;	/* 4989bb: je 0x4989c7 */
	M32((DWORD)(m->esp + 0x40u)) = 0x2u;	/* 4989bd: mov dword ptr [esp + 0x40], 2 */
	goto L_4989e5;	/* 4989c5: jmp 0x4989e5 */
L_4989c7:
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 4989c7: mov eax, dword ptr [ebx] */
	m->ecx = m->eax;	/* 4989c9: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4989cb: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4989ce: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4989d0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4989d3: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4989d5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4989d8: add ecx, eax */
	m->edx = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb88u));	/* 4989da: mov edx, dword ptr [ebp + ecx*8 + 0x1eccb88] */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 4989e1: mov dword ptr [esp + 0x40], edx */
L_4989e5:
	m->ecx = 0x10u;	/* 4989e5: mov ecx, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4989ea: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0xc4u);	/* 4989ec: lea edi, [esp + 0xc4] */
	m->esi = (DWORD)(m->esp + 0xc4u);	/* 4989f3: lea esi, [esp + 0xc4] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4989fa: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 4989fc: mov eax, dword ptr [ebx] */
	M32((DWORD)(m->esp + 0x38u)) = m->esi;	/* 4989fe: mov dword ptr [esp + 0x38], esi */
	m->ecx = m->eax;	/* 498a02: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498a04: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498a07: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498a09: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498a0c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498a0e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498a11: add ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 498a13: xor eax, eax */
	m->edx = (DWORD)(m->ebp + m->ecx*8 + 0x0u);	/* 498a15: lea edx, [ebp + ecx*8] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 498a19: or ecx, 0xffffffff */
	m->edi = (DWORD)(m->edx + 0x1eccb08u);	/* 498a1c: lea edi, [edx + 0x1eccb08] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 498a22: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 498a24: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 498a26: sub edi, ecx */
	m->eax = m->ecx;	/* 498a28: mov eax, ecx */
	m->esi = m->edi;	/* 498a2a: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x38u));	/* 498a2c: mov edi, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498a30: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 498a33: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 498a35: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x78u));	/* 498a37: mov eax, dword ptr [esp + 0x78] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 498a3b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 498a3e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->edx + 0x1eccb58u));	/* 498a40: mov ecx, dword ptr [edx + 0x1eccb58] */
	m->edx = M32((DWORD)(m->edx + 0x1eccb54u));	/* 498a46: mov edx, dword ptr [edx + 0x1eccb54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498a4c: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 498a4d: mov ecx, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498a51: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498a52: push eax */
	m->edx = M32((DWORD)(m->esp + m->ecx*4 + 0xa8u));	/* 498a53: mov edx, dword ptr [esp + ecx*4 + 0xa8] */
	m->ecx = M32((DWORD)(m->esp + 0x48u));	/* 498a5a: mov ecx, dword ptr [esp + 0x48] */
	m->eax = (DWORD)(m->esp + 0xd0u);	/* 498a5e: lea eax, [esp + 0xd0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498a65: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498a66: push eax */
	{ DWORD v_ = 0x4d062cu; m->esp -= 4; M32(m->esp) = v_; }	/* 498a67: push 0x4d062c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498a6c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x498a72u; native_call(m, 0x49f135u);	/* 498a6d: call 0x49f135 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 498a72: mov eax, dword ptr [esp + 0x44] */
	m->ecx = M32((DWORD)(m->ebp + 0x2342976u));	/* 498a76: mov ecx, dword ptr [ebp + 0x2342976] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498a7c: add esp, 0x1c */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 498a7f: inc eax */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 498a80: add ebx, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498a83: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 498a85: mov dword ptr [esp + 0x28], eax */
	if (m->sf != m->of) goto L_49899a;	/* 498a89: jl 0x49899a */
	m->esi = M32((DWORD)(m->esp + 0x3cu));	/* 498a8f: mov esi, dword ptr [esp + 0x3c] */
L_498a93:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 498a93: push esi */
	m->esp -= 4; M32(m->esp) = 0x498a99u; native_call(m, 0x49e7e0u);	/* 498a94: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498a99: add esp, 4 */
	M32((DWORD)(0x9f67ecu)) = 0x0u;	/* 498a9c: mov dword ptr [0x9f67ec], 0 */
	M32((DWORD)(0x9f67f0u)) = 0x1u;	/* 498aa6: mov dword ptr [0x9f67f0], 1 */
	m->ebx = 0x1u;	/* 498ab0: mov ebx, 1 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 498ab5: xor edi, edi */
L_498ab7:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9e8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498ab7: cmp dword ptr [ebp + 0x233c9e8], edi */
	if (!m->zf) goto L_498ad6;	/* 498abd: jne 0x498ad6 */
	M32((DWORD)(m->ebp + 0x233cc20u)) = m->ebx;	/* 498abf: mov dword ptr [ebp + 0x233cc20], ebx */
	M32((DWORD)(m->ebp + 0x233cc28u)) = m->edi;	/* 498ac5: mov dword ptr [ebp + 0x233cc28], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 498acb: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 498acc: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 498acd: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 498ace: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498acf: add esp, 0x2a0 */
	m->esp += 4 + 0; return;	/* 498ad5: ret  */
L_498ad6:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343303u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498ad6: cmp dword ptr [ebp + 0x2343303], ebx */
	if (!m->zf) goto L_498ae4;	/* 498adc: jne 0x498ae4 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340cecu)), b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; M32((DWORD)(m->ebp + 0x2340cecu)) = r_; }	/* 498ade: xor dword ptr [ebp + 0x2340cec], ebx */
L_498ae4:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23432cfu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498ae4: cmp dword ptr [ebp + 0x23432cf], ebx */
	if (!m->zf) goto L_498b00;	/* 498aea: jne 0x498b00 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340cecu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498aec: cmp dword ptr [ebp + 0x2340cec], ebx */
	if (!m->zf) goto L_498b16;	/* 498af2: jne 0x498b16 */
	M32((DWORD)(m->ebp + 0x2340cecu)) = m->edi;	/* 498af4: mov dword ptr [ebp + 0x2340cec], edi */
	M32((DWORD)(m->ebp + 0x23432cfu)) = m->edi;	/* 498afa: mov dword ptr [ebp + 0x23432cf], edi */
L_498b00:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340cecu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b00: cmp dword ptr [ebp + 0x2340cec], ebx */
	if (!m->zf) goto L_498b16;	/* 498b06: jne 0x498b16 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234327fu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b08: cmp dword ptr [ebp + 0x234327f], ebx */
	if (!m->zf) goto L_498b16;	/* 498b0e: jne 0x498b16 */
	M32((DWORD)(m->ebp + 0x2340cecu)) = m->edi;	/* 498b10: mov dword ptr [ebp + 0x2340cec], edi */
L_498b16:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340cf4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b16: cmp dword ptr [ebp + 0x2340cf4], ebx */
	if (!m->zf) goto L_498b2a;	/* 498b1c: jne 0x498b2a */
	m->ecx = m->ebp;	/* 498b1e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498b25u; native_call(m, 0x49ca70u);	/* 498b20: call 0x49ca70 */
	goto L_498bc4;	/* 498b25: jmp 0x498bc4 */
L_498b2a:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23432cfu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b2a: cmp dword ptr [ebp + 0x23432cf], ebx */
	if (!m->zf) goto L_498c5b;	/* 498b30: jne 0x498c5b */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a1u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b36: cmp dword ptr [ebp + 0x23423a1], edi */
	if (!m->zf) goto L_498bc4;	/* 498b3c: jne 0x498bc4 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 498b42: push 0x64 */
	{ DWORD v_ = 0x9u; m->esp -= 4; M32(m->esp) = v_; }	/* 498b44: push 9 */
	m->esp -= 4; M32(m->esp) = 0x498b4bu; native_call(m, 0x456e50u);	/* 498b46: call 0x456e50 */
	m->eax = M32((DWORD)(m->ebp + 0x2340cf0u));	/* 498b4b: mov eax, dword ptr [ebp + 0x2340cf0] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 498b51: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b54: cmp eax, edi */
	if (m->zf) goto L_498b85;	/* 498b56: je 0x498b85 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b58: cmp dword ptr [ebp + 8], edi */
	if (!m->zf) goto L_498b91;	/* 498b5b: jne 0x498b91 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342415u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b5d: cmp dword ptr [ebp + 0x2342415], ebx */
	if (!m->zf) goto L_498b91;	/* 498b63: jne 0x498b91 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498b65: mov eax, dword ptr [ebp + 0x234240d] */
	m->edx = m->eax;	/* 498b6b: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498b6d: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498b70: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498b72: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498b75: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498b77: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498b7a: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb48u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498b7c: cmp dword ptr [ebp + edx*8 + 0x1eccb48], edi */
	if (!m->zf) goto L_498b91;	/* 498b83: jne 0x498b91 */
L_498b85:
	M32((DWORD)(m->ebp + 0x2340d04u)) = m->edi;	/* 498b85: mov dword ptr [ebp + 0x2340d04], edi */
	M32((DWORD)(m->ebp + 0x2340cf0u)) = m->ebx;	/* 498b8b: mov dword ptr [ebp + 0x2340cf0], ebx */
L_498b91:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498b91: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 498b97: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498b99: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498b9c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498b9e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498ba1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498ba3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498ba6: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb48u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498ba8: cmp dword ptr [ebp + ecx*8 + 0x1eccb48], edi */
	if (!m->zf) goto L_498bb4;	/* 498baf: jne 0x498bb4 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 498bb1: push edi */
	goto L_498bb6;	/* 498bb2: jmp 0x498bb6 */
L_498bb4:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 498bb4: push 4 */
L_498bb6:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 498bb6: push edi */
	m->ecx = m->ebp;	/* 498bb7: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498bbeu; native_call(m, 0x49ca20u);	/* 498bb9: call 0x49ca20 */
	M32((DWORD)(m->ebp + 0x23432cfu)) = m->edi;	/* 498bbe: mov dword ptr [ebp + 0x23432cf], edi */
L_498bc4:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23432cfu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498bc4: cmp dword ptr [ebp + 0x23432cf], ebx */
	if (!m->zf) goto L_498c5b;	/* 498bca: jne 0x498c5b */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498bd0: cmp dword ptr [ebp + 4], edi */
	if (!m->zf) goto L_498c2c;	/* 498bd3: jne 0x498c2c */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a1u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498bd5: cmp dword ptr [ebp + 0x23423a1], edi */
	if (!m->zf) goto L_498c55;	/* 498bdb: jne 0x498c55 */
	M32((DWORD)(m->ebp + 0x23423a1u)) = m->ebx;	/* 498bdd: mov dword ptr [ebp + 0x23423a1], ebx */
	M32((DWORD)(m->ebp + 0x23423a5u)) = 0x40400000u;	/* 498be3: mov dword ptr [ebp + 0x23423a5], 0x40400000 */
	m->esp -= 4; M32(m->esp) = 0x498bf2u; native_call(m, 0x457310u);	/* 498bed: call 0x457310 */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 498bf2: mov eax, dword ptr [ebp + 8] */
	m->ecx = m->ebp;	/* 498bf5: mov ecx, ebp */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498bf7: cmp eax, edi */
	if (!m->zf) goto L_498c08;	/* 498bf9: jne 0x498c08 */
	m->esp -= 4; M32(m->esp) = 0x498c00u; native_call(m, 0x462f60u);	/* 498bfb: call 0x462f60 */
	M32((DWORD)(0x9f67f4u)) = m->ebx;	/* 498c00: mov dword ptr [0x9f67f4], ebx */
	goto L_498c55;	/* 498c06: jmp 0x498c55 */
L_498c08:
	m->esp -= 4; M32(m->esp) = 0x498c0du; native_call(m, 0x462f30u);	/* 498c08: call 0x462f30 */
	m->ecx = m->ebp;	/* 498c0d: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498c14u; native_call(m, 0x463670u);	/* 498c0f: call 0x463670 */
	M32((DWORD)(m->ebp + 0x23423b5u)) = 0x2u;	/* 498c14: mov dword ptr [ebp + 0x23423b5], 2 */
	M32((DWORD)(m->ebp + 0x23423b9u)) = m->edi;	/* 498c1e: mov dword ptr [ebp + 0x23423b9], edi */
	M32((DWORD)(0x9f67f4u)) = m->ebx;	/* 498c24: mov dword ptr [0x9f67f4], ebx */
	goto L_498c55;	/* 498c2a: jmp 0x498c55 */
L_498c2c:
	M32((DWORD)(m->ebp + 0x23423a1u)) = m->ebx;	/* 498c2c: mov dword ptr [ebp + 0x23423a1], ebx */
	M32((DWORD)(m->ebp + 0x23423a5u)) = m->edi;	/* 498c32: mov dword ptr [ebp + 0x23423a5], edi */
	m->esp -= 4; M32(m->esp) = 0x498c3du; native_call(m, 0x457310u);	/* 498c38: call 0x457310 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498c3d: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498c43: cmp eax, edi */
	if (m->sf != m->of) goto L_498c4f;	/* 498c45: jl 0x498c4f */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498c47: push eax */
	m->ecx = m->ebp;	/* 498c48: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498c4fu; native_call(m, 0x463530u);	/* 498c4a: call 0x463530 */
L_498c4f:
	M32((DWORD)(0x9f67f4u)) = m->edi;	/* 498c4f: mov dword ptr [0x9f67f4], edi */
L_498c55:
	M32((DWORD)(m->ebp + 0x23432cfu)) = m->edi;	/* 498c55: mov dword ptr [ebp + 0x23432cf], edi */
L_498c5b:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498c5b: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498c61: cmp eax, edi */
	if (m->sf != m->of) goto L_498d05;	/* 498c63: jl 0x498d05 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342419u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498c69: cmp dword ptr [ebp + 0x2342419], edi */
	if (!m->zf) goto L_498d05;	/* 498c6f: jne 0x498d05 */
	m->edx = m->eax;	/* 498c75: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498c77: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498c7a: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498c7c: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498c7f: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498c81: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498c84: add edx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x2342442u));	/* 498c86: mov eax, dword ptr [ebp + 0x2342442] */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb4cu)) = m->eax;	/* 498c8c: mov dword ptr [ebp + edx*8 + 0x1eccb4c], eax */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498c93: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 498c99: mov ecx, eax */
	m->edx = M32((DWORD)(m->ebp + 0x2342442u));	/* 498c9b: mov edx, dword ptr [ebp + 0x2342442] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498ca1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498ca4: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498ca6: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498ca9: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498cab: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498cae: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb50u)) = m->edx;	/* 498cb0: mov dword ptr [ebp + ecx*8 + 0x1eccb50], edx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498cb7: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 498cbd: mov ecx, eax */
	m->edx = M32((DWORD)(m->ebp + 0x2342446u));	/* 498cbf: mov edx, dword ptr [ebp + 0x2342446] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498cc5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498cc8: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498cca: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498ccd: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498ccf: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498cd2: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb5cu)) = m->edx;	/* 498cd4: mov dword ptr [ebp + ecx*8 + 0x1eccb5c], edx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498cdb: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 498ce1: mov ecx, eax */
	m->edx = M32((DWORD)(m->ebp + 0x2342446u));	/* 498ce3: mov edx, dword ptr [ebp + 0x2342446] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498ce9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498cec: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498cee: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498cf1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498cf3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498cf6: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb68u)) = m->edx;	/* 498cf8: mov dword ptr [ebp + ecx*8 + 0x1eccb68], edx */
	M32((DWORD)(m->ebp + 0x2342419u)) = m->ebx;	/* 498cff: mov dword ptr [ebp + 0x2342419], ebx */
L_498d05:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342421u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498d05: cmp dword ptr [ebp + 0x2342421], edi */
	if (!m->zf) goto L_498d70;	/* 498d0b: jne 0x498d70 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498d0d: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498d13: cmp eax, edi */
	if (m->sf != m->of) goto L_498d70;	/* 498d15: jl 0x498d70 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498d17: cmp dword ptr [ebp + 8], ebx */
	if (!m->zf) goto L_498d70;	/* 498d1a: jne 0x498d70 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498d1c: push eax */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 498d1d: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x498d28u; native_call(m, 0x4734d0u);	/* 498d23: call 0x4734d0 */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 498d28: mov edx, dword ptr [ebp + 0x234240d] */
	m->ecx = (DWORD)(m->edx + m->edx*2 + 0x0u);	/* 498d2e: lea ecx, [edx + edx*2] */
	{ DWORD a_ = m->ecx, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498d31: shl ecx, 0xb */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498d34: sub ecx, edx */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 498d36: lea ecx, [ecx + ecx*2] */
	m->edx = (DWORD)(m->edx + m->ecx*8 + 0x0u);	/* 498d39: lea edx, [edx + ecx*8] */
	M32((DWORD)(m->ebp + m->edx*2 + 0x179d1fau)) = m->eax;	/* 498d3c: mov dword ptr [ebp + edx*2 + 0x179d1fa], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 498d43: mov ecx, dword ptr [ebp + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 498d49: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 498d4c: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 498d4f: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 498d51: lea eax, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 498d54: lea ecx, [ecx + eax*8] */
	M32((DWORD)(m->ebp + m->ecx*2 + 0x179d1feu)) = m->edi;	/* 498d57: mov dword ptr [ebp + ecx*2 + 0x179d1fe], edi */
	M32((DWORD)(m->ebp + 0x2342425u)) = 0x40a00000u;	/* 498d5e: mov dword ptr [ebp + 0x2342425], 0x40a00000 */
	M32((DWORD)(m->ebp + 0x2342421u)) = m->ebx;	/* 498d68: mov dword ptr [ebp + 0x2342421], ebx */
	goto L_498db0;	/* 498d6e: jmp 0x498db0 */
L_498d70:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2342425u)));	/* 498d70: fld dword ptr [ebp + 0x2342425] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 498d76: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 498d7c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 498d7e: test ah, 0x41 */
	if (!m->zf) goto L_498db0;	/* 498d81: jne 0x498db0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2342425u)));	/* 498d83: fld dword ptr [ebp + 0x2342425] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 498d89: fsub dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x2342425u)) = (float)ST(0);	/* 498d8c: fst dword ptr [ebp + 0x2342425] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 498d92: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 498d98: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 498d9a: test ah, 1 */
	if (m->zf) goto L_498db0;	/* 498d9d: je 0x498db0 */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 498d9f: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x498daau; native_call(m, 0x473610u);	/* 498da5: call 0x473610 */
	M32((DWORD)(m->ebp + 0x2342425u)) = m->edi;	/* 498daa: mov dword ptr [ebp + 0x2342425], edi */
L_498db0:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234240du)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498db0: cmp dword ptr [ebp + 0x234240d], edi */
	if (m->sf == m->of) goto L_498ea9;	/* 498db6: jge 0x498ea9 */
	m->esp -= 4; M32(m->esp) = 0x498dc1u; native_call(m, 0x4a86d0u);	/* 498dbc: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498dc1: test eax, eax */
	if (m->zf) goto L_498ea9;	/* 498dc3: je 0x498ea9 */
	m->edx = M32((DWORD)(0x4d05a4u));	/* 498dc9: mov edx, dword ptr [0x4d05a4] */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 498dcf: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498dd5: push edx */
	m->ecx = m->esi;	/* 498dd6: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498dddu; native_call(m, 0x498dddu + M32(0x498dd9u));	/* 0x473780 unless the patch DLL retargets it */	/* 498dd8: call 0x473780 */
	m->esp -= 4; M32(m->esp) = 0x498de2u; native_call(m, 0x4a86f0u);	/* 498ddd: call 0x4a86f0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498de2: push eax */
	m->ecx = m->esi;	/* 498de3: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x234240du)) = m->eax;	/* 498de5: mov dword ptr [ebp + 0x234240d], eax */
	m->esp -= 4; M32(m->esp) = 0x498df0u; native_call(m, 0x4743e0u);	/* 498deb: call 0x4743e0 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498df0: mov eax, dword ptr [ebp + 0x234240d] */
	m->ebx = (DWORD)(m->ebp + 0x2342429u);	/* 498df6: lea ebx, [ebp + 0x2342429] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 498dfc: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498dfd: push eax */
	m->ecx = m->esi;	/* 498dfe: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x498e05u; native_call(m, 0x473940u);	/* 498e00: call 0x473940 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498e05: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 498e0b: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498e0d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498e10: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498e12: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498e15: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498e17: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498e1a: add ecx, eax */
	{ DWORD a_ = m->ebx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498e1c: cmp ebx, edi */
	m->edx = (DWORD)(m->ebp + m->ecx*8 + 0x1eccb08u);	/* 498e1e: lea edx, [ebp + ecx*8 + 0x1eccb08] */
	if (m->zf) goto L_498e48;	/* 498e25: je 0x498e48 */
	m->edi = m->ebx;	/* 498e27: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 498e29: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 498e2c: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 498e2e: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 498e30: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 498e32: sub edi, ecx */
	m->eax = m->ecx;	/* 498e34: mov eax, ecx */
	m->esi = m->edi;	/* 498e36: mov esi, edi */
	m->edi = m->edx;	/* 498e38: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498e3a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 498e3d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 498e3f: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 498e41: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 498e44: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_498e4b;	/* 498e46: jmp 0x498e4b */
L_498e48:
	M8((DWORD)(m->edx + 0x0u)) = (BYTE)(0x0u);	/* 498e48: mov byte ptr [edx], 0 */
L_498e4b:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498e4b: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 498e51: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498e53: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498e56: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498e58: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498e5b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498e5d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498e60: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb7cu)) = m->eax;	/* 498e62: mov dword ptr [ebp + ecx*8 + 0x1eccb7c], eax */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 498e69: mov edx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498e6f: push edx */
	m->ecx = m->ebp;	/* 498e70: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498e77u; native_call(m, 0x462b50u);	/* 498e72: call 0x462b50 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498e77: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 498e7d: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498e80: shl ecx, 0xb */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498e83: sub ecx, eax */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 498e85: lea ecx, [ecx + ecx*2] */
	m->edx = (DWORD)(m->eax + m->ecx*8 + 0x0u);	/* 498e88: lea edx, [eax + ecx*8] */
	m->ecx = (DWORD)(m->ebp + m->edx*2 + 0x1755234u);	/* 498e8b: lea ecx, [ebp + edx*2 + 0x1755234] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498e92: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498e93: push eax */
	m->ecx = m->ebp;	/* 498e94: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498e9bu; native_call(m, 0x4634e0u);	/* 498e96: call 0x4634e0 */
	m->ecx = m->ebp;	/* 498e9b: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498ea2u; native_call(m, 0x48e680u);	/* 498e9d: call 0x48e680 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 498ea2: xor edi, edi */
	m->ebx = 0x1u;	/* 498ea4: mov ebx, 1 */
L_498ea9:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498ea9: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498eaf: cmp eax, edi */
	if (m->sf != m->of) goto L_498fd1;	/* 498eb1: jl 0x498fd1 */
	m->edx = m->eax;	/* 498eb7: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498eb9: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498ebc: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498ebe: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498ec1: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 498ec3: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 498ec6: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb78u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498ec8: cmp dword ptr [ebp + edx*8 + 0x1eccb78], edi */
	if (!m->zf) goto L_498fd1;	/* 498ecf: jne 0x498fd1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342399u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498ed5: cmp dword ptr [ebp + 0x2342399], edi */
	if (!m->zf) goto L_498fd1;	/* 498edb: jne 0x498fd1 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 498ee1: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498ee4: shl ecx, 0xb */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498ee7: sub ecx, eax */
	m->ecx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 498ee9: lea ecx, [ecx + ecx*2] */
	m->edx = (DWORD)(m->eax + m->ecx*8 + 0x0u);	/* 498eec: lea edx, [eax + ecx*8] */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*2 + 0x179d1feu)), b_ = 0x180u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498eef: cmp dword ptr [ebp + edx*2 + 0x179d1fe], 0x180 */
	if (!m->zf) goto L_498fd1;	/* 498efa: jne 0x498fd1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234327fu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498f00: cmp dword ptr [ebp + 0x234327f], ebx */
	if (m->zf) goto L_498f14;	/* 498f06: je 0x498f14 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342415u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498f08: cmp dword ptr [ebp + 0x2342415], ebx */
	if (!m->zf) goto L_498fd1;	/* 498f0e: jne 0x498fd1 */
L_498f14:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498f14: cmp dword ptr [ebp + 0x22e7184], ebx */
	if (!m->zf) goto L_498f7e;	/* 498f1a: jne 0x498f7e */
	m->eax = M32((DWORD)(m->ebp + 0x234243eu));	/* 498f1c: mov eax, dword ptr [ebp + 0x234243e] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498f22: cmp eax, edi */
	if (m->sf != m->of) goto L_498f32;	/* 498f24: jl 0x498f32 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498f26: push eax */
	m->ecx = m->ebp;	/* 498f27: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498f2eu; native_call(m, 0x463710u);	/* 498f29: call 0x463710 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498f2e: test eax, eax */
	if (m->sf == m->of) goto L_498f7e;	/* 498f30: jge 0x498f7e */
L_498f32:
	m->eax = M32((DWORD)(m->ebp + 0x234241du));	/* 498f32: mov eax, dword ptr [ebp + 0x234241d] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498f38: cmp eax, edi */
	if (m->sf != m->of) goto L_498f63;	/* 498f3a: jl 0x498f63 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498f3c: cmp dword ptr [ebp + 8], edi */
	if (m->zf) goto L_498f63;	/* 498f3f: je 0x498f63 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498f41: push eax */
	m->ecx = m->ebp;	/* 498f42: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498f49u; native_call(m, 0x463740u);	/* 498f44: call 0x463740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 498f49: test eax, eax */
	if (!m->zf) goto L_498f58;	/* 498f4b: jne 0x498f58 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 498f4d: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 498f4e: push ebx */
	m->ecx = m->ebp;	/* 498f4f: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498f56u; native_call(m, 0x49ca20u);	/* 498f51: call 0x49ca20 */
	goto L_498fcb;	/* 498f56: jmp 0x498fcb */
L_498f58:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 498f58: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 498f59: push ebx */
	m->ecx = m->ebp;	/* 498f5a: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498f61u; native_call(m, 0x49ca20u);	/* 498f5c: call 0x49ca20 */
	goto L_498fcb;	/* 498f61: jmp 0x498fcb */
L_498f63:
	m->eax = M32((DWORD)(m->ebp + 0x234297eu));	/* 498f63: mov eax, dword ptr [ebp + 0x234297e] */
	m->ecx = M32((DWORD)(m->ebp + 0x2342982u));	/* 498f69: mov ecx, dword ptr [ebp + 0x2342982] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498f6f: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_498f58;	/* 498f71: jg 0x498f58 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 498f73: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 498f74: push ebx */
	m->ecx = m->ebp;	/* 498f75: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498f7cu; native_call(m, 0x49ca20u);	/* 498f77: call 0x49ca20 */
	goto L_498fcb;	/* 498f7c: jmp 0x498fcb */
L_498f7e:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234243eu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498f7e: cmp dword ptr [ebp + 0x234243e], edi */
	if (m->sf == m->of) goto L_498fc5;	/* 498f84: jge 0x498fc5 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 498f86: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498f8c: push ecx */
	m->ecx = m->ebp;	/* 498f8d: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498f94u; native_call(m, 0x4613a0u);	/* 498f8f: call 0x4613a0 */
	m->edx = M32((DWORD)(m->ebp + 0x234243eu));	/* 498f94: mov edx, dword ptr [ebp + 0x234243e] */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498f9a: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498fa0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498fa1: push eax */
	m->ecx = m->ebp;	/* 498fa2: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498fa9u; native_call(m, 0x462d30u);	/* 498fa4: call 0x462d30 */
	m->edx = M32((DWORD)(m->ebp + 0x234243eu));	/* 498fa9: mov edx, dword ptr [ebp + 0x234243e] */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498faf: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = (DWORD)(m->ebp + 0x2342429u);	/* 498fb5: lea ecx, [ebp + 0x2342429] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 498fbb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 498fbc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 498fbd: push eax */
	m->ecx = m->ebp;	/* 498fbe: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x498fc5u; native_call(m, 0x4635b0u);	/* 498fc0: call 0x4635b0 */
L_498fc5:
	M32((DWORD)(m->ebp + 0x2340d00u)) = m->ebx;	/* 498fc5: mov dword ptr [ebp + 0x2340d00], ebx */
L_498fcb:
	M32((DWORD)(m->ebp + 0x2342415u)) = m->edi;	/* 498fcb: mov dword ptr [ebp + 0x2342415], edi */
L_498fd1:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 498fd1: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498fd7: cmp eax, edi */
	if (m->sf != m->of) goto L_49903f;	/* 498fd9: jl 0x49903f */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234243eu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498fdb: cmp dword ptr [ebp + 0x234243e], edi */
	if (m->sf != m->of) goto L_49903f;	/* 498fe1: jl 0x49903f */
	m->ecx = m->eax;	/* 498fe3: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498fe5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498fe8: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498fea: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498fed: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 498fef: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 498ff2: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb78u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498ff4: cmp dword ptr [ebp + ecx*8 + 0x1eccb78], edi */
	if (!m->zf) goto L_49903f;	/* 498ffb: jne 0x49903f */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340d35u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 498ffd: cmp dword ptr [ebp + 0x2340d35], edi */
	if (!m->zf) goto L_49903f;	/* 499003: jne 0x49903f */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342399u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499005: cmp dword ptr [ebp + 0x2342399], edi */
	if (!m->zf) goto L_49903f;	/* 49900b: jne 0x49903f */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a1u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49900d: cmp dword ptr [ebp + 0x23423a1], edi */
	if (!m->zf) goto L_49903f;	/* 499013: jne 0x49903f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 499015: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc48u));	/* 499018: fadd dword ptr [ebp + 0x233cc48] */
	MF((DWORD)(m->ebp + 0x233cc48u)) = (float)ST(0);	/* 49901e: fst dword ptr [ebp + 0x233cc48] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 499024: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49902a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49902c: test ah, 1 */
	if (!m->zf) goto L_499045;	/* 49902f: jne 0x499045 */
	M32((DWORD)(m->ebp + 0x233cc48u)) = m->edi;	/* 499031: mov dword ptr [ebp + 0x233cc48], edi */
	M32((DWORD)(m->ebp + 0x2340d00u)) = m->ebx;	/* 499037: mov dword ptr [ebp + 0x2340d00], ebx */
	goto L_499045;	/* 49903d: jmp 0x499045 */
L_49903f:
	M32((DWORD)(m->ebp + 0x233cc48u)) = m->edi;	/* 49903f: mov dword ptr [ebp + 0x233cc48], edi */
L_499045:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340d00u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499045: cmp dword ptr [ebp + 0x2340d00], ebx */
	if (m->zf) goto L_499090;	/* 49904b: je 0x499090 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e71a0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49904d: cmp dword ptr [ebp + 0x22e71a0], ebx */
	if (!m->zf) goto L_4993f2;	/* 499053: jne 0x4993f2 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 499059: mov eax, dword ptr [ebp + 0x234240d] */
	m->edx = m->eax;	/* 49905f: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499061: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499064: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499066: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499069: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49906b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49906e: add edx, eax */
	m->ecx = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccbbcu));	/* 499070: mov ecx, dword ptr [ebp + edx*8 + 0x1eccbbc] */
	m->eax = (DWORD)(m->ebp + m->edx*8 + 0x0u);	/* 499077: lea eax, [ebp + edx*8] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49907b: cmp ecx, 3 */
	if (!m->zf) goto L_4993f2;	/* 49907e: jne 0x4993f2 */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x1eccf4cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499084: cmp dword ptr [eax + 0x1eccf4c], ebx */
	if (!m->zf) goto L_4993f2;	/* 49908a: jne 0x4993f2 */
L_499090:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342411u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499090: cmp dword ptr [ebp + 0x2342411], edi */
	if (!m->zf) goto L_499112;	/* 499096: jne 0x499112 */
	m->eax = M32((DWORD)(m->ebp + 0x2342472u));	/* 499098: mov eax, dword ptr [ebp + 0x2342472] */
	m->ecx = M32((DWORD)(m->ebp + 0x234246eu));	/* 49909e: mov ecx, dword ptr [ebp + 0x234246e] */
	m->edx = M32((DWORD)(m->ebp + 0x234246au));	/* 4990a4: mov edx, dword ptr [ebp + 0x234246a] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4990aa: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x2342466u));	/* 4990ab: mov eax, dword ptr [ebp + 0x2342466] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990b1: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x2342462u));	/* 4990b2: mov ecx, dword ptr [ebp + 0x2342462] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990b8: push edx */
	m->edx = M32((DWORD)(m->ebp + 0x234245eu));	/* 4990b9: mov edx, dword ptr [ebp + 0x234245e] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4990bf: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x234245au));	/* 4990c0: mov eax, dword ptr [ebp + 0x234245a] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990c6: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x2342456u));	/* 4990c7: mov ecx, dword ptr [ebp + 0x2342456] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990cd: push edx */
	m->edx = M32((DWORD)(m->ebp + 0x2342452u));	/* 4990ce: mov edx, dword ptr [ebp + 0x2342452] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4990d4: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x234244eu));	/* 4990d5: mov eax, dword ptr [ebp + 0x234244e] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990db: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x234244au));	/* 4990dc: mov ecx, dword ptr [ebp + 0x234244a] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990e2: push edx */
	m->edx = M32((DWORD)(m->ebp + 0x234243eu));	/* 4990e3: mov edx, dword ptr [ebp + 0x234243e] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4990e9: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x234243au));	/* 4990ea: mov eax, dword ptr [ebp + 0x234243a] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990f0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990f1: push edx */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 4990f2: mov edx, dword ptr [ebp + 0x234240d] */
	m->ecx = (DWORD)(m->ebp + 0x2342429u);	/* 4990f8: lea ecx, [ebp + 0x2342429] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4990fe: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4990ff: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 499100: push edx */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 499101: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x49910cu; native_call(m, 0x474210u);	/* 499107: call 0x474210 */
	M32((DWORD)(m->ebp + 0x2342411u)) = m->ebx;	/* 49910c: mov dword ptr [ebp + 0x2342411], ebx */
L_499112:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499112: cmp dword ptr [ebp + 0x22e7184], ebx */
	if (!m->zf) goto L_499177;	/* 499118: jne 0x499177 */
	m->eax = M32((DWORD)(m->ebp + 0x234243eu));	/* 49911a: mov eax, dword ptr [ebp + 0x234243e] */
	m->ecx = m->ebp;	/* 499120: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499122: push eax */
	m->esp -= 4; M32(m->esp) = 0x499128u; native_call(m, 0x463740u);	/* 499123: call 0x463740 */
	m->ecx = (DWORD)(m->eax*4 + 0x4a97fcu);	/* 499128: lea ecx, [eax*4 + 0x4a97fc] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 49912f: xor esi, esi */
	m->ebx = (DWORD)(m->eax*4 + 0x4a9824u);	/* 499131: lea ebx, [eax*4 + 0x4a9824] */
	m->edi = (DWORD)(m->eax*4 + 0x4a9810u);	/* 499138: lea edi, [eax*4 + 0x4a9810] */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 49913f: mov dword ptr [esp + 0x3c], ecx */
L_499143:
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 499143: mov edx, dword ptr [ebx] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 499145: mov ecx, dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 499149: mov eax, dword ptr [edi] */
	{ DWORD v_ = 0x3f7fbe77u; m->esp -= 4; M32(m->esp) = v_; }	/* 49914b: push 0x3f7fbe77 */
	{ DWORD v_ = 0xbf800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 499150: push 0xbf800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 499155: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 499157: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 499158: mov edx, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49915a: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49915b: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 499161: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 499162: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499163: push eax */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 499164: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x49916fu; native_call(m, 0x474b50u);	/* 49916a: call 0x474b50 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49916f: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499170: cmp esi, 5 */
	if (m->sf != m->of) goto L_499143;	/* 499173: jl 0x499143 */
	goto L_4991d4;	/* 499175: jmp 0x4991d4 */
L_499177:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 499177: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49917d: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49917f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499182: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499184: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499187: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499189: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49918c: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb48u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49918e: cmp dword ptr [ebp + ecx*8 + 0x1eccb48], edi */
	if (!m->zf) goto L_4991d4;	/* 499195: jne 0x4991d4 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 499197: xor ebx, ebx */
	m->edi = (DWORD)(m->ebp + 0x1f36c8u);	/* 499199: lea edi, [ebp + 0x1f36c8] */
	m->esi = (DWORD)(m->ebp + 0x23424a2u);	/* 49919f: lea esi, [ebp + 0x23424a2] */
L_4991a5:
	m->edx = M32((DWORD)(m->esi + 0x28u));	/* 4991a5: mov edx, dword ptr [esi + 0x28] */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 4991a8: mov eax, dword ptr [esi] */
	m->ecx = M32((DWORD)(m->esi + 0xffffffd8u));	/* 4991aa: mov ecx, dword ptr [esi - 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4991ad: push edx */
	m->edx = M32((DWORD)(m->esi + 0x24u));	/* 4991ae: mov edx, dword ptr [esi + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4991b1: push eax */
	m->eax = M32((DWORD)(m->esi + 0xfffffffcu));	/* 4991b2: mov eax, dword ptr [esi - 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4991b5: push ecx */
	m->ecx = M32((DWORD)(m->esi + 0xffffffd4u));	/* 4991b6: mov ecx, dword ptr [esi - 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4991b9: push edx */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 4991ba: mov edx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4991c0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4991c1: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4991c2: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4991c3: push edx */
	m->ecx = m->edi;	/* 4991c4: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4991cbu; native_call(m, 0x474b50u);	/* 4991c6: call 0x474b50 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4991cb: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4991cc: add esi, 8 */
	{ DWORD a_ = m->ebx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4991cf: cmp ebx, 5 */
	if (m->sf != m->of) goto L_4991a5;	/* 4991d2: jl 0x4991a5 */
L_4991d4:
	m->ecx = M32((DWORD)(m->ebp + 0x22ee4bcu));	/* 4991d4: mov ecx, dword ptr [ebp + 0x22ee4bc] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4991da: xor edx, edx */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4991dc: cmp ecx, edx */
	if (m->zf || m->sf != m->of) goto L_49932a;	/* 4991de: jle 0x49932a */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 4991e4: mov esi, dword ptr [0xa1efb8] */
	m->eax = m->esi;	/* 4991ea: mov eax, esi */
	{ DWORD a_ = m->eax, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4991ec: and eax, 0xfff */
	m->eax = M32((DWORD)(m->eax*4 + 0xa106f8u));	/* 4991f1: mov eax, dword ptr [eax*4 + 0xa106f8] */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 4991f8: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4991fa: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 4991fb: mov dword ptr [0xa1efb8], esi */
	m->ebx = M32((DWORD)(m->ebp + 0x22ee4bcu));	/* 499201: mov ebx, dword ptr [ebp + 0x22ee4bc] */
	m->ecx = m->ebx;	/* 499207: mov ecx, ebx */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 499209: dec ebx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49920a: test ecx, ecx */
	if (m->sf != m->of) goto L_4992cd;	/* 49920c: jl 0x4992cd */
	m->edi = M32((DWORD)(m->ebp + 0x2221f90u));	/* 499212: mov edi, dword ptr [ebp + 0x2221f90] */
L_499218:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 499218: xor esi, esi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49921a: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_4992cd;	/* 49921c: jle 0x4992cd */
	m->ecx = (DWORD)(m->ebp + 0x1eccbccu);	/* 499222: lea ecx, [ebp + 0x1eccbcc] */
L_499228:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0xfffffff0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499228: cmp dword ptr [ecx - 0x10], 1 */
	if (!m->zf) goto L_4992a8;	/* 49922c: jne 0x4992a8 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xfffffff8u)));	/* 49922e: fld dword ptr [ecx - 8] */
	m->eax = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 499231: lea eax, [edx + edx*4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + m->eax*4 + 0x22ee23cu));	/* 499234: fsub dword ptr [ebp + eax*4 + 0x22ee23c] */
	m->eax = (DWORD)(m->ebp + m->eax*4 + 0x22ee23cu);	/* 49923b: lea eax, [ebp + eax*4 + 0x22ee23c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 499242: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xfffffffcu)));	/* 499246: fld dword ptr [ecx - 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 499249: fsub dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49924c: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 499250: fld dword ptr [ecx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 499252: fsub dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 499255: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 499259: mov dword ptr [esp + 0x1c], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 49925d: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 499261: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x28cu)));	/* 499265: fld dword ptr [ecx + 0x28c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 49926b: fmul dword ptr [0x4a93d0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 499271: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 499275: fmul dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 499279: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 49927d: fmul dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 499281: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 499285: mov eax, dword ptr [esp + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 499289: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 49928b: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 49928f: fmul dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 499293: mov dword ptr [esp + 0x24], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 499297: faddp st(1) */
	{ long double t = ST(1); FPUSH(t); }	/* 499299: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 49929b: fmul st(2) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 49929d: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49929f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4992a1: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 4992a4: fstp st(0) */
	if (m->zf) goto L_4992b8;	/* 4992a6: je 0x4992b8 */
L_4992a8:
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4992a8: inc esi */
	{ DWORD a_ = m->ecx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4992a9: add ecx, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4992af: cmp esi, edi */
	if (m->sf == m->of) goto L_4992cd;	/* 4992b1: jge 0x4992cd */
	goto L_499228;	/* 4992b3: jmp 0x499228 */
L_4992b8:
	m->eax = (DWORD)(m->edx + 0x1u);	/* 4992b8: lea eax, [edx + 1] */
	m->ecx = m->ebx;	/* 4992bb: mov ecx, ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4992bd: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x22ee4bcu)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4992be: idiv dword ptr [ebp + 0x22ee4bc] */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 4992c4: dec ebx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4992c5: test ecx, ecx */
	if (m->sf == m->of) goto L_499218;	/* 4992c7: jge 0x499218 */
L_4992cd:
	m->ecx = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 4992cd: lea ecx, [edx + edx*4] */
	m->eax = (DWORD)(m->edx + m->edx*4 + 0x8bb893u);	/* 4992d0: lea eax, [edx + edx*4 + 0x8bb893] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->eax*4 + 0x0u)));	/* 4992d7: fld dword ptr [ebp + eax*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->ecx*4 + 0x22ee248u)));	/* 4992db: fld dword ptr [ebp + ecx*4 + 0x22ee248] */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 4992e2: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = (DWORD)(m->ebp + m->ecx*4 + 0x0u);	/* 4992e8: lea ecx, [ebp + ecx*4] */
	{ DWORD a_ = m->ecx, b_ = 0x22ee23cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4992ec: add ecx, 0x22ee23c */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 4992f2: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x84u)) = 0x0u;	/* 4992f9: mov dword ptr [esp + 0x84], 0 */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 499304: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x88u)) = m->edx;	/* 499306: mov dword ptr [esp + 0x88], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 49930d: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x8cu)) = m->edx;	/* 499310: mov dword ptr [esp + 0x8c], edx */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 499317: mov ecx, dword ptr [ecx + 8] */
	MF((DWORD)(m->esp + 0x94u)) = (float)ST(0); FPOP();	/* 49931a: fstp dword ptr [esp + 0x94] */
	M32((DWORD)(m->esp + 0x90u)) = m->ecx;	/* 499321: mov dword ptr [esp + 0x90], ecx */
	goto L_499374;	/* 499328: jmp 0x499374 */
L_49932a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x22ee234u)));	/* 49932a: fld dword ptr [ebp + 0x22ee234] */
	M32((DWORD)(m->esp + 0x84u)) = m->edx;	/* 499330: mov dword ptr [esp + 0x84], edx */
	m->edx = (DWORD)(m->ebp + 0x22ee228u);	/* 499337: lea edx, [ebp + 0x22ee228] */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49933d: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 499343: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 499345: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x88u)) = m->ecx;	/* 49934c: mov dword ptr [esp + 0x88], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 499353: mov ecx, dword ptr [edx + 4] */
	MF((DWORD)(m->esp + 0x94u)) = (float)ST(0); FPOP();	/* 499356: fstp dword ptr [esp + 0x94] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 49935d: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->esp + 0x8cu)) = m->ecx;	/* 499360: mov dword ptr [esp + 0x8c], ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x22ee238u)));	/* 499367: fld dword ptr [ebp + 0x22ee238] */
	M32((DWORD)(m->esp + 0x90u)) = m->edx;	/* 49936d: mov dword ptr [esp + 0x90], edx */
L_499374:
	MF((DWORD)(m->esp + 0x98u)) = (float)ST(0); FPOP();	/* 499374: fstp dword ptr [esp + 0x98] */
	m->ecx = (DWORD)(m->esp + 0x80u);	/* 49937b: lea ecx, [esp + 0x80] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 499382: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499383: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 499384: push -1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499386: push eax */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 499387: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x499392u; native_call(m, 0x45dd80u);	/* 49938d: call 0x45dd80 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d1du));	/* 499392: mov eax, dword ptr [ebp + 0x2340d1d] */
	m->esi = 0x1u;	/* 499398: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49939d: cmp eax, esi */
	if (!m->zf) goto L_4993b1;	/* 49939f: jne 0x4993b1 */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 4993a1: mov edx, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4993a7: shl edx, 4 */
	M32((DWORD)(m->edx + m->ebp*1 + 0x234300au)) = m->esi;	/* 4993aa: mov dword ptr [edx + ebp + 0x234300a], esi */
L_4993b1:
	{ DWORD v_ = 0x4d0618u; m->esp -= 4; M32(m->esp) = v_; }	/* 4993b1: push 0x4d0618 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4993b6: push ebp */
	M32((DWORD)(m->ebp + 0x233c9fcu)) = m->esi;	/* 4993b7: mov dword ptr [ebp + 0x233c9fc], esi */
	m->esp -= 4; M32(m->esp) = 0x4993c2u; native_call(m, 0x463450u);	/* 4993bd: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4993c2: add esp, 8 */
	M32((DWORD)(m->ebp + 0x23423c1u)) = 0x40400000u;	/* 4993c5: mov dword ptr [ebp + 0x23423c1], 0x40400000 */
	m->ecx = m->ebp;	/* 4993cf: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x23423c5u)) = 0xffffffffu;	/* 4993d1: mov dword ptr [ebp + 0x23423c5], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x4993e0u; native_call(m, 0x462150u);	/* 4993db: call 0x462150 */
	M32((DWORD)(m->ebp + 0x23432cbu)) = m->esi;	/* 4993e0: mov dword ptr [ebp + 0x23432cb], esi */
	M32((DWORD)(m->ebp + 0x2340d00u)) = 0x0u;	/* 4993e6: mov dword ptr [ebp + 0x2340d00], 0 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4993f0: xor edi, edi */
L_4993f2:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4993f2: cmp dword ptr [ebp + 8], edi */
	if (!m->zf) goto L_4996d7;	/* 4993f5: jne 0x4996d7 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 4993fb: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 499401: test eax, eax */
	if (m->sf != m->of) goto L_4996d7;	/* 499403: jl 0x4996d7 */
	m->ecx = m->eax;	/* 499409: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49940b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49940e: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499410: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499413: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499415: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499418: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb48u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49941a: cmp dword ptr [ebp + ecx*8 + 0x1eccb48], 1 */
	if (!m->zf) goto L_4996d7;	/* 499422: jne 0x4996d7 */
	m->eax = M32((DWORD)(m->ebp + 0x2342399u));	/* 499428: mov eax, dword ptr [ebp + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49942e: test eax, eax */
	if (!m->zf) goto L_4996d7;	/* 499430: jne 0x4996d7 */
	m->eax = M32((DWORD)(m->ebp + 0x1ecca6cu));	/* 499436: mov eax, dword ptr [ebp + 0x1ecca6c] */
	M32((DWORD)(m->esp + 0x5cu)) = 0x0u;	/* 49943c: mov dword ptr [esp + 0x5c], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 499444: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4996d7;	/* 499446: jle 0x4996d7 */
	m->edx = (DWORD)(m->ebp + 0x1eca67cu);	/* 49944c: lea edx, [ebp + 0x1eca67c] */
	m->eax = (DWORD)(m->ebp + 0x1eccb78u);	/* 499452: lea eax, [ebp + 0x1eccb78] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 499458: mov dword ptr [esp + 0x28], edx */
	M32((DWORD)(m->esp + 0x40u)) = m->eax;	/* 49945c: mov dword ptr [esp + 0x40], eax */
L_499460:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 499460: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x18u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499464: cmp dword ptr [ecx + 0x18], 1 */
	if (!m->zf) goto L_4996a7;	/* 499468: jne 0x4996a7 */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 49946e: mov edx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 499472: mov eax, dword ptr [edx] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 499474: test eax, eax */
	if (m->zf) goto L_49948d;	/* 499476: je 0x49948d */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499478: cmp eax, 1 */
	if (!m->zf) goto L_4996a7;	/* 49947b: jne 0x4996a7 */
	m->eax = m->edx;	/* 499481: mov eax, edx */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x44u)), b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499483: cmp dword ptr [eax + 0x44], 3 */
	if (!m->zf) goto L_4996a7;	/* 499487: jne 0x4996a7 */
L_49948d:
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 49948d: mov ecx, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->ecx + 0x0u));	/* 499491: mov ecx, dword ptr [ecx] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 499493: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 499496: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 499499: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49949b: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 49949e: lea eax, [ecx + edx*8] */
	m->ecx = (DWORD)(m->ebp + m->eax*2 + 0x1755230u);	/* 4994a1: lea ecx, [ebp + eax*2 + 0x1755230] */
	m->eax = M32((DWORD)(m->ebp + 0x22e7184u));	/* 4994a8: mov eax, dword ptr [ebp + 0x22e7184] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4994ae: cmp eax, 1 */
	M32((DWORD)(m->esp + 0x38u)) = m->ecx;	/* 4994b1: mov dword ptr [esp + 0x38], ecx */
	if (!m->zf) goto L_499511;	/* 4994b5: jne 0x499511 */
	m->edx = m->ecx;	/* 4994b7: mov edx, ecx */
	m->ecx = m->ebp;	/* 4994b9: mov ecx, ebp */
	m->eax = M32((DWORD)(m->edx + 0x48u));	/* 4994bb: mov eax, dword ptr [edx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4994be: push eax */
	m->esp -= 4; M32(m->esp) = 0x4994c4u; native_call(m, 0x463740u);	/* 4994bf: call 0x463740 */
	m->ecx = (DWORD)(m->eax*4 + 0x4a97fcu);	/* 4994c4: lea ecx, [eax*4 + 0x4a97fc] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4994cb: xor esi, esi */
	m->edi = (DWORD)(m->eax*4 + 0x4a9824u);	/* 4994cd: lea edi, [eax*4 + 0x4a9824] */
	m->ebx = (DWORD)(m->eax*4 + 0x4a9810u);	/* 4994d4: lea ebx, [eax*4 + 0x4a9810] */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 4994db: mov dword ptr [esp + 0x3c], ecx */
L_4994df:
	m->edx = M32((DWORD)(m->edi + 0x0u));	/* 4994df: mov edx, dword ptr [edi] */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 4994e1: mov eax, dword ptr [ebx] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 4994e3: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = 0x3f7fbe77u; m->esp -= 4; M32(m->esp) = v_; }	/* 4994e7: push 0x3f7fbe77 */
	{ DWORD v_ = 0xbf800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4994ec: push 0xbf800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4994f1: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4994f3: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 4994f4: mov edx, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4994f6: push eax */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 4994f7: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4994fb: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4994fc: push esi */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 4994fd: mov ecx, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4994ff: push ecx */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 499500: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x49950bu; native_call(m, 0x474b50u);	/* 499506: call 0x474b50 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49950b: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49950c: cmp esi, 5 */
	if (m->sf != m->of) goto L_4994df;	/* 49950f: jl 0x4994df */
L_499511:
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 499511: mov esi, dword ptr [esp + 0x28] */
	m->ecx = 0x17u;	/* 499515: mov ecx, 0x17 */
	m->edi = (DWORD)(m->esp + 0x104u);	/* 49951a: lea edi, [esp + 0x104] */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 499521: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(m->ebp + 0x22ee4bcu));	/* 499523: mov ecx, dword ptr [ebp + 0x22ee4bc] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 499529: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_499647;	/* 49952b: jle 0x499647 */
	m->esi = M32((DWORD)(0xa1efb8u));	/* 499531: mov esi, dword ptr [0xa1efb8] */
	m->edx = m->esi;	/* 499537: mov edx, esi */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 499539: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 49953f: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 499546: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 499548: div ecx */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49954a: inc esi */
	M32((DWORD)(0xa1efb8u)) = m->esi;	/* 49954b: mov dword ptr [0xa1efb8], esi */
	m->ebx = M32((DWORD)(m->ebp + 0x22ee4bcu));	/* 499551: mov ebx, dword ptr [ebp + 0x22ee4bc] */
	m->eax = m->ebx;	/* 499557: mov eax, ebx */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 499559: dec ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49955a: test eax, eax */
	if (m->sf != m->of) goto L_499619;	/* 49955c: jl 0x499619 */
	m->edi = M32((DWORD)(m->ebp + 0x2221f90u));	/* 499562: mov edi, dword ptr [ebp + 0x2221f90] */
L_499568:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 499568: xor esi, esi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49956a: test edi, edi */
	if (m->zf || m->sf != m->of) goto L_499619;	/* 49956c: jle 0x499619 */
	m->ecx = (DWORD)(m->ebp + 0x1eccbccu);	/* 499572: lea ecx, [ebp + 0x1eccbcc] */
L_499578:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0xfffffff0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499578: cmp dword ptr [ecx - 0x10], 1 */
	if (!m->zf) goto L_4995f4;	/* 49957c: jne 0x4995f4 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xfffffff8u)));	/* 49957e: fld dword ptr [ecx - 8] */
	m->eax = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 499581: lea eax, [edx + edx*4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + m->eax*4 + 0x22ee23cu));	/* 499584: fsub dword ptr [ebp + eax*4 + 0x22ee23c] */
	m->eax = (DWORD)(m->ebp + m->eax*4 + 0x22ee23cu);	/* 49958b: lea eax, [ebp + eax*4 + 0x22ee23c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 499592: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xfffffffcu)));	/* 499596: fld dword ptr [ecx - 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 499599: fsub dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49959c: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 4995a0: fld dword ptr [ecx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4995a2: fsub dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4995a5: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4995a9: mov dword ptr [esp + 0x1c], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4995ad: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 4995b1: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x28cu)));	/* 4995b5: fld dword ptr [ecx + 0x28c] */
	ST(0) = ST(0) + ST(0);	/* 4995bb: fadd st(0), st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4995bd: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 4995c1: fmul dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4995c5: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 4995c9: fmul dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4995cd: mov dword ptr [esp + 0x20], eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4995d1: mov eax, dword ptr [esp + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4995d5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 4995d7: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 4995db: fmul dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4995df: mov dword ptr [esp + 0x24], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4995e3: faddp st(1) */
	{ long double t = ST(1); FPUSH(t); }	/* 4995e5: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 4995e7: fmul st(2) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 4995e9: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4995eb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4995ed: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 4995f0: fstp st(0) */
	if (m->zf) goto L_499604;	/* 4995f2: je 0x499604 */
L_4995f4:
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4995f4: inc esi */
	{ DWORD a_ = m->ecx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4995f5: add ecx, 0x8888 */
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4995fb: cmp esi, edi */
	if (m->sf == m->of) goto L_499619;	/* 4995fd: jge 0x499619 */
	goto L_499578;	/* 4995ff: jmp 0x499578 */
L_499604:
	m->eax = (DWORD)(m->edx + 0x1u);	/* 499604: lea eax, [edx + 1] */
	m->ecx = m->ebx;	/* 499607: mov ecx, ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 499609: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x22ee4bcu)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49960a: idiv dword ptr [ebp + 0x22ee4bc] */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 499610: dec ebx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 499611: test ecx, ecx */
	if (m->sf == m->of) goto L_499568;	/* 499613: jge 0x499568 */
L_499619:
	m->edx = (DWORD)(m->edx + m->edx*4 + 0x0u);	/* 499619: lea edx, [edx + edx*4] */
	m->eax = (DWORD)(m->ebp + m->edx*4 + 0x22ee23cu);	/* 49961c: lea eax, [ebp + edx*4 + 0x22ee23c] */
	m->ecx = M32((DWORD)(m->ebp + m->edx*4 + 0x22ee23cu));	/* 499623: mov ecx, dword ptr [ebp + edx*4 + 0x22ee23c] */
	M32((DWORD)(m->esp + 0x108u)) = m->ecx;	/* 49962a: mov dword ptr [esp + 0x108], ecx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 499631: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x10cu)) = m->edx;	/* 499634: mov dword ptr [esp + 0x10c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 49963b: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x110u)) = m->eax;	/* 49963e: mov dword ptr [esp + 0x110], eax */
	goto L_49966e;	/* 499645: jmp 0x49966e */
L_499647:
	m->ecx = (DWORD)(m->ebp + 0x22ee228u);	/* 499647: lea ecx, [ebp + 0x22ee228] */
	m->edx = M32((DWORD)(m->ebp + 0x22ee228u));	/* 49964d: mov edx, dword ptr [ebp + 0x22ee228] */
	M32((DWORD)(m->esp + 0x108u)) = m->edx;	/* 499653: mov dword ptr [esp + 0x108], edx */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 49965a: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x10cu)) = m->eax;	/* 49965d: mov dword ptr [esp + 0x10c], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 499664: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->esp + 0x110u)) = m->ecx;	/* 499667: mov dword ptr [esp + 0x110], ecx */
L_49966e:
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 49966e: mov eax, dword ptr [esp + 0x5c] */
	m->edx = (DWORD)(m->esp + 0x104u);	/* 499672: lea edx, [esp + 0x104] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 499679: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49967a: push eax */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49967b: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x499686u; native_call(m, 0x45de20u);	/* 499681: call 0x45de20 */
	m->ecx = M32((DWORD)(m->esp + 0x40u));	/* 499686: mov ecx, dword ptr [esp + 0x40] */
	m->eax = M32((DWORD)(m->ecx + 0xffffffd0u));	/* 49968a: mov eax, dword ptr [ecx - 0x30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49968d: test eax, eax */
	if (!m->zf) goto L_4996a7;	/* 49968f: jne 0x4996a7 */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 499691: mov edx, dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 499695: mov ecx, dword ptr [esp + 0x28] */
	m->eax = M32((DWORD)(m->edx + 0x48u));	/* 499699: mov eax, dword ptr [edx + 0x48] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 49969c: mov edx, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49969e: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49969f: push edx */
	m->ecx = m->ebp;	/* 4996a0: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x4996a7u; native_call(m, 0x462d30u);	/* 4996a2: call 0x462d30 */
L_4996a7:
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 4996a7: mov eax, dword ptr [esp + 0x5c] */
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 4996ab: mov esi, dword ptr [esp + 0x28] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 4996af: mov edx, dword ptr [esp + 0x40] */
	m->ecx = M32((DWORD)(m->ebp + 0x1ecca6cu));	/* 4996b3: mov ecx, dword ptr [ebp + 0x1ecca6c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4996b9: inc eax */
	{ DWORD a_ = m->esi, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4996ba: add esi, 0x5c */
	{ DWORD a_ = m->edx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4996bd: add edx, 0x8888 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4996c3: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x5cu)) = m->eax;	/* 4996c5: mov dword ptr [esp + 0x5c], eax */
	M32((DWORD)(m->esp + 0x28u)) = m->esi;	/* 4996c9: mov dword ptr [esp + 0x28], esi */
	M32((DWORD)(m->esp + 0x40u)) = m->edx;	/* 4996cd: mov dword ptr [esp + 0x40], edx */
	if (m->sf != m->of) goto L_499460;	/* 4996d1: jl 0x499460 */
L_4996d7:
	m->eax = M32((DWORD)(m->ebp + 0x233c9fcu));	/* 4996d7: mov eax, dword ptr [ebp + 0x233c9fc] */
	m->esi = 0x1u;	/* 4996dd: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4996e2: cmp eax, esi */
	if (!m->zf) goto L_4996fd;	/* 4996e4: jne 0x4996fd */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233cc10u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4996e6: cmp dword ptr [ebp + 0x233cc10], esi */
	if (!m->zf) goto L_4996fd;	/* 4996ec: jne 0x4996fd */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 4996ee: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 4996f4: lea ecx, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4996fa: push eax */
	goto L_499705;	/* 4996fb: jmp 0x499705 */
L_4996fd:
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 4996fd: lea ecx, [ebp + 0x1f36c8] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 499703: push -1 */
L_499705:
	m->esp -= 4; M32(m->esp) = 0x49970au; native_call(m, 0x45dfb0u);	/* 499705: call 0x45dfb0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 49970a: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9554u));	/* 49970d: fmul dword ptr [0x4a9554] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0);	/* 499713: fst dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x1f4164u)));	/* 499717: fld dword ptr [ebp + 0x1f4164] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 49971d: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 49971f: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499721: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499723: test ah, 0x41 */
	if (!m->zf) goto L_499732;	/* 499726: jne 0x499732 */
	m->ecx = M32((DWORD)(m->ebp + 0x1f4164u));	/* 499728: mov ecx, dword ptr [ebp + 0x1f4164] */
	M32((DWORD)(m->esp + 0x3cu)) = m->ecx;	/* 49972e: mov dword ptr [esp + 0x3c], ecx */
L_499732:
	m->esp -= 4; M32(m->esp) = 0x499737u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 499732: call 0x4686d0 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa2a8u));	/* 499737: fmul dword ptr [0x4aa2a8] */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23432cbu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49973d: cmp dword ptr [ebp + 0x23432cb], esi */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 499743: fmul dword ptr [ebp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa504u));	/* 499746: fmul dword ptr [0x4aa504] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 49974c: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 499750: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a945cu));	/* 499753: fmul dword ptr [0x4a945c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 499759: fstp dword ptr [esp + 0x38] */
	if (!m->zf) goto L_4997a2;	/* 49975d: jne 0x4997a2 */
	m->eax = (DWORD)(m->ebp + 0x233cb20u);	/* 49975f: lea eax, [ebp + 0x233cb20] */
	m->ecx = 0xau;	/* 499765: mov ecx, 0xa */
L_49976a:
	m->edx = M32((DWORD)(m->eax + 0xffffff10u));	/* 49976a: mov edx, dword ptr [eax - 0xf0] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 499770: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->eax + 0xffffff38u));	/* 499772: mov edx, dword ptr [eax - 0xc8] */
	M32((DWORD)(m->eax + 0x28u)) = m->edx;	/* 499778: mov dword ptr [eax + 0x28], edx */
	m->edx = M32((DWORD)(m->eax + 0xffffff60u));	/* 49977b: mov edx, dword ptr [eax - 0xa0] */
	M32((DWORD)(m->eax + 0x50u)) = m->edx;	/* 499781: mov dword ptr [eax + 0x50], edx */
	m->edx = M32((DWORD)(m->eax + 0xffffff88u));	/* 499784: mov edx, dword ptr [eax - 0x78] */
	M32((DWORD)(m->eax + 0x78u)) = m->edx;	/* 499787: mov dword ptr [eax + 0x78], edx */
	m->edx = M32((DWORD)(m->eax + 0xffffffb0u));	/* 49978a: mov edx, dword ptr [eax - 0x50] */
	M32((DWORD)(m->eax + 0xa0u)) = m->edx;	/* 49978d: mov dword ptr [eax + 0xa0], edx */
	m->edx = M32((DWORD)(m->eax + 0xffffffd8u));	/* 499793: mov edx, dword ptr [eax - 0x28] */
	M32((DWORD)(m->eax + 0xc8u)) = m->edx;	/* 499796: mov dword ptr [eax + 0xc8], edx */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49979c: add eax, 4 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 49979f: dec ecx */
	if (!m->zf) goto L_49976a;	/* 4997a0: jne 0x49976a */
L_4997a2:
	m->eax = M32((DWORD)(m->ebp + 0x233c9fcu));	/* 4997a2: mov eax, dword ptr [ebp + 0x233c9fc] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4997a8: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4997aa: sub eax, ebx */
	if (m->zf) goto L_4998f0;	/* 4997ac: je 0x4998f0 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4997b2: dec eax */
	if (!m->zf) goto L_499b63;	/* 4997b3: jne 0x499b63 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4997b9: cmp dword ptr [ebp + 8], ebx */
	if (m->zf) goto L_4997cb;	/* 4997bc: je 0x4997cb */
	m->esp -= 4; M32(m->esp) = 0x4997c3u; native_call(m, 0x4a86d0u);	/* 4997be: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4997c3: test eax, eax */
	if (m->zf) goto L_499b63;	/* 4997c5: je 0x499b63 */
L_4997cb:
	m->eax = M32((DWORD)(m->ebp + 0x2342399u));	/* 4997cb: mov eax, dword ptr [ebp + 0x2342399] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4997d1: cmp eax, esi */
	if (m->zf) goto L_4997e1;	/* 4997d3: je 0x4997e1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a1u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4997d5: cmp dword ptr [ebp + 0x23423a1], esi */
	if (!m->zf) goto L_499843;	/* 4997db: jne 0x499843 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4997dd: cmp eax, esi */
	if (!m->zf) goto L_499827;	/* 4997df: jne 0x499827 */
L_4997e1:
	m->eax = M32((DWORD)(m->ebp + 0x23428f6u));	/* 4997e1: mov eax, dword ptr [ebp + 0x23428f6] */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 4997e7: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4997ed: cmp eax, ecx */
	if (m->zf) goto L_499827;	/* 4997ef: je 0x499827 */
	m->ecx = M32((DWORD)(m->ebp + 0x233cc10u));	/* 4997f1: mov ecx, dword ptr [ebp + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4997f7: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x2343293u));	/* 4997fb: fmul dword ptr [ebp + 0x2343293] */
	m->eax = (DWORD)(m->ebp + m->ecx*4 + 0x233cb20u);	/* 499801: lea eax, [ebp + ecx*4 + 0x233cb20] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 499808: fsubr dword ptr [eax] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 49980a: fstp dword ptr [eax] */
	m->edx = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49980c: mov edx, dword ptr [ebp + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 499812: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x2343297u));	/* 499816: fmul dword ptr [ebp + 0x2343297] */
	m->eax = (DWORD)(m->ebp + m->edx*4 + 0x233cb48u);	/* 49981c: lea eax, [ebp + edx*4 + 0x233cb48] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 499823: fsubr dword ptr [eax] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 499825: fstp dword ptr [eax] */
L_499827:
	M32((DWORD)(m->ebp + 0x234327bu)) = m->ebx;	/* 499827: mov dword ptr [ebp + 0x234327b], ebx */
	M32((DWORD)(m->ebp + 0x2343287u)) = 0xffffffffu;	/* 49982d: mov dword ptr [ebp + 0x2343287], 0xffffffff */
	M32((DWORD)(m->ebp + 0x23432ebu)) = m->ebx;	/* 499837: mov dword ptr [ebp + 0x23432eb], ebx */
	M32((DWORD)(m->ebp + 0x23432efu)) = m->ebx;	/* 49983d: mov dword ptr [ebp + 0x23432ef], ebx */
L_499843:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343273u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499843: cmp dword ptr [ebp + 0x2343273], esi */
	if (!m->zf) goto L_49985d;	/* 499849: jne 0x49985d */
	M32((DWORD)(m->ebp + 0x234325fu)) = m->esi;	/* 49984b: mov dword ptr [ebp + 0x234325f], esi */
	M32((DWORD)(m->ebp + 0x2343263u)) = m->esi;	/* 499851: mov dword ptr [ebp + 0x2343263], esi */
	M32((DWORD)(m->ebp + 0x2343267u)) = m->ebx;	/* 499857: mov dword ptr [ebp + 0x2343267], ebx */
L_49985d:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343277u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49985d: cmp dword ptr [ebp + 0x2343277], esi */
	if (!m->zf) goto L_499877;	/* 499863: jne 0x499877 */
	M32((DWORD)(m->ebp + 0x234325fu)) = m->esi;	/* 499865: mov dword ptr [ebp + 0x234325f], esi */
	M32((DWORD)(m->ebp + 0x2343267u)) = m->esi;	/* 49986b: mov dword ptr [ebp + 0x2343267], esi */
	M32((DWORD)(m->ebp + 0x2343263u)) = m->ebx;	/* 499871: mov dword ptr [ebp + 0x2343263], ebx */
L_499877:
	m->eax = M32((DWORD)(m->ebp + 0x23432efu));	/* 499877: mov eax, dword ptr [ebp + 0x23432ef] */
	m->ecx = M32((DWORD)(m->ebp + 0x23432ebu));	/* 49987d: mov ecx, dword ptr [ebp + 0x23432eb] */
	m->edx = M32((DWORD)(m->ebp + 0x2343287u));	/* 499883: mov edx, dword ptr [ebp + 0x2343287] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499889: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x2343283u));	/* 49988a: mov eax, dword ptr [ebp + 0x2343283] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 499890: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x234325fu));	/* 499891: mov ecx, dword ptr [ebp + 0x234325f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 499897: push edx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 499898: fld dword ptr [esp + 0x34] */
	m->edx = M32((DWORD)(m->ebp + 0x234327bu));	/* 49989c: mov edx, dword ptr [ebp + 0x234327b] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4998a2: push eax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x2343297u));	/* 4998a3: fmul dword ptr [ebp + 0x2343297] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4998a9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4998aa: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4998ab: push ecx */
	m->eax = M32((DWORD)(m->ebp + 0x234326fu));	/* 4998ac: mov eax, dword ptr [ebp + 0x234326f] */
	m->edx = M32((DWORD)(m->ebp + 0x2343267u));	/* 4998b2: mov edx, dword ptr [ebp + 0x2343267] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4998b8: fstp dword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 4998bb: fld dword ptr [esp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x2343293u));	/* 4998bf: fmul dword ptr [ebp + 0x2343293] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4998c5: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x234326bu));	/* 4998c6: mov ecx, dword ptr [ebp + 0x234326b] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4998cc: fstp dword ptr [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4998cf: push eax */
	m->eax = M32((DWORD)(m->ebp + 0x2343263u));	/* 4998d0: mov eax, dword ptr [ebp + 0x2343263] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4998d6: push ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 4998d7: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4998dd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4998de: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4998df: push ecx */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 4998e0: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x4998ebu; native_call(m, 0x45eb20u);	/* 4998e6: call 0x45eb20 */
	goto L_499b63;	/* 4998eb: jmp 0x499b63 */
L_4998f0:
	m->eax = M32((DWORD)(m->ebp + 0x23424f2u));	/* 4998f0: mov eax, dword ptr [ebp + 0x23424f2] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4998f6: cmp eax, ebx */
	if (m->sf != m->of) goto L_499940;	/* 4998f8: jl 0x499940 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340c64u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4998fa: cmp dword ptr [ebp + 0x2340c64], ebx */
	if (m->sf != m->of) goto L_499940;	/* 499900: jl 0x499940 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499902: cmp eax, 2 */
	if (m->zf) goto L_499b63;	/* 499905: je 0x499b63 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2343297u)));	/* 49990b: fld dword ptr [ebp + 0x2343297] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + m->eax*4 + 0x233cb48u));	/* 499911: fadd dword ptr [ebp + eax*4 + 0x233cb48] */
	MF((DWORD)(m->ebp + m->eax*4 + 0x233cb48u)) = (float)ST(0); FPOP();	/* 499918: fstp dword ptr [ebp + eax*4 + 0x233cb48] */
	m->edx = M32((DWORD)(m->ebp + 0x23424f2u));	/* 49991f: mov edx, dword ptr [ebp + 0x23424f2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2343293u)));	/* 499925: fld dword ptr [ebp + 0x2343293] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + m->edx*4 + 0x233cb20u));	/* 49992b: fadd dword ptr [ebp + edx*4 + 0x233cb20] */
	m->eax = (DWORD)(m->ebp + m->edx*4 + 0x233cb20u);	/* 499932: lea eax, [ebp + edx*4 + 0x233cb20] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 499939: fstp dword ptr [eax] */
	goto L_499b63;	/* 49993b: jmp 0x499b63 */
L_499940:
	m->ecx = M32((DWORD)(0xa0e7ecu));	/* 499940: mov ecx, dword ptr [0xa0e7ec] */
	m->eax = M32((DWORD)(0xa0e7e8u));	/* 499946: mov eax, dword ptr [0xa0e7e8] */
	m->edx = M32((DWORD)(0xa0e7f0u));	/* 49994b: mov edx, dword ptr [0xa0e7f0] */
	M32((DWORD)(m->esp + 0x54u)) = m->ecx;	/* 499951: mov dword ptr [esp + 0x54], ecx */
	m->ecx = M32((DWORD)(m->ebp + 0x234326bu));	/* 499955: mov ecx, dword ptr [ebp + 0x234326b] */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 49995b: mov dword ptr [esp + 0x50], eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49995f: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499961: cmp ecx, ebx */
	M32((DWORD)(m->esp + 0x58u)) = m->edx;	/* 499963: mov dword ptr [esp + 0x58], edx */
	if (m->zf) goto L_49996b;	/* 499967: je 0x49996b */
	m->eax = m->esi;	/* 499969: mov eax, esi */
L_49996b:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234326fu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49996b: cmp dword ptr [ebp + 0x234326f], ebx */
	if (m->zf) goto L_499975;	/* 499971: je 0x499975 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 499973: or al, 0x10 */
L_499975:
	m->ecx = M32((DWORD)(m->ebp + 0x234325fu));	/* 499975: mov ecx, dword ptr [ebp + 0x234325f] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49997b: cmp ecx, ebx */
	if (!m->zf) goto L_499999;	/* 49997d: jne 0x499999 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343263u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49997f: cmp dword ptr [ebp + 0x2343263], ebx */
	if (m->zf) goto L_49998a;	/* 499985: je 0x49998a */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 499987: or ah, 1 */
L_49998a:
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49998a: cmp ecx, ebx */
	if (!m->zf) goto L_499999;	/* 49998c: jne 0x499999 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343267u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49998e: cmp dword ptr [ebp + 0x2343267], ebx */
	if (m->zf) goto L_499999;	/* 499994: je 0x499999 */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 8)) | (((r_) & 0xff) << 8); }	/* 499996: or ah, 0x10 */
L_499999:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499999: cmp eax, ebx */
	if (m->zf) goto L_499a49;	/* 49999b: je 0x499a49 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4999a1: fld dword ptr [esp + 0x3c] */
	ST(0) = -ST(0);	/* 4999a5: fchs  */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 4999a7: fstp dword ptr [esp + 0x58] */
	{ DWORD a_ = m->eax, b_ = 0x110u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4999ab: cmp eax, 0x110 */
	M32((DWORD)(m->esp + 0x50u)) = 0x0u;	/* 4999b0: mov dword ptr [esp + 0x50], 0 */
	M32((DWORD)(m->esp + 0x54u)) = 0x0u;	/* 4999b8: mov dword ptr [esp + 0x54], 0 */
	if (!m->cf && !m->zf) goto L_4999ef;	/* 4999c0: ja 0x4999ef */
	if (m->zf) goto L_4999e8;	/* 4999c2: je 0x4999e8 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4999c4: dec eax */
	if (m->zf) goto L_4999e1;	/* 4999c5: je 0x4999e1 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4999c7: sub eax, 0xf */
	if (m->zf) goto L_4999da;	/* 4999ca: je 0x4999da */
	{ DWORD a_ = m->eax, b_ = 0xf1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4999cc: sub eax, 0xf1 */
	if (!m->zf) goto L_499a1c;	/* 4999d1: jne 0x499a1c */
	{ DWORD v_ = 0xfffff3b2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4999d3: push 0xfffff3b2 */
	goto L_499a11;	/* 4999d8: jmp 0x499a11 */
L_4999da:
	{ DWORD v_ = 0xfffffc7cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4999da: push 0xfffffc7c */
	goto L_499a11;	/* 4999df: jmp 0x499a11 */
L_4999e1:
	{ DWORD v_ = 0xfffff574u; m->esp -= 4; M32(m->esp) = v_; }	/* 4999e1: push 0xfffff574 */
	goto L_499a11;	/* 4999e6: jmp 0x499a11 */
L_4999e8:
	{ DWORD v_ = 0xfffffe3eu; m->esp -= 4; M32(m->esp) = v_; }	/* 4999e8: push 0xfffffe3e */
	goto L_499a11;	/* 4999ed: jmp 0x499a11 */
L_4999ef:
	{ DWORD a_ = m->eax, b_ = 0x1000u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4999ef: sub eax, 0x1000 */
	if (m->zf) goto L_499a0c;	/* 4999f4: je 0x499a0c */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4999f6: dec eax */
	if (m->zf) goto L_499a05;	/* 4999f7: je 0x499a05 */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4999f9: sub eax, 0xf */
	if (!m->zf) goto L_499a1c;	/* 4999fc: jne 0x499a1c */
	{ DWORD v_ = 0xfffffabau; m->esp -= 4; M32(m->esp) = v_; }	/* 4999fe: push 0xfffffaba */
	goto L_499a11;	/* 499a03: jmp 0x499a11 */
L_499a05:
	{ DWORD v_ = 0xfffff736u; m->esp -= 4; M32(m->esp) = v_; }	/* 499a05: push 0xfffff736 */
	goto L_499a11;	/* 499a0a: jmp 0x499a11 */
L_499a0c:
	{ DWORD v_ = 0xfffff8f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 499a0c: push 0xfffff8f8 */
L_499a11:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 499a11: push 2 */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 499a13: lea ecx, [esp + 0x58] */
	m->esp -= 4; M32(m->esp) = 0x499a1cu; native_call(m, 0x4677c0u);	/* 499a17: call 0x4677c0 */
L_499a1c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 499a1c: fld dword ptr [ebp + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 499a22: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499a27: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 499a28: push esi */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 499a29: lea ecx, [esp + 0x58] */
	m->esp -= 4; M32(m->esp) = 0x499a32u; native_call(m, 0x4677c0u);	/* 499a2d: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 499a32: fld dword ptr [ebp + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 499a38: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499a3d: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 499a3e: push 2 */
	m->ecx = (DWORD)(m->esp + 0x58u);	/* 499a40: lea ecx, [esp + 0x58] */
	m->esp -= 4; M32(m->esp) = 0x499a49u; native_call(m, 0x4677c0u);	/* 499a44: call 0x4677c0 */
L_499a49:
	m->eax = M32((DWORD)(m->ebp + 0x234325fu));	/* 499a49: mov eax, dword ptr [ebp + 0x234325f] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499a4f: cmp eax, ebx */
	if (m->zf) goto L_499a5b;	/* 499a51: je 0x499a5b */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343263u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499a53: cmp dword ptr [ebp + 0x2343263], ebx */
	if (!m->zf) goto L_499a63;	/* 499a59: jne 0x499a63 */
L_499a5b:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343273u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499a5b: cmp dword ptr [ebp + 0x2343273], ebx */
	if (m->zf) goto L_499a6f;	/* 499a61: je 0x499a6f */
L_499a63:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 499a63: fld dword ptr [esp + 0x54] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 499a67: fadd dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 499a6b: fstp dword ptr [esp + 0x54] */
L_499a6f:
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499a6f: cmp eax, ebx */
	if (m->zf) goto L_499a7b;	/* 499a71: je 0x499a7b */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343267u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499a73: cmp dword ptr [ebp + 0x2343267], ebx */
	if (!m->zf) goto L_499a83;	/* 499a79: jne 0x499a83 */
L_499a7b:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343277u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499a7b: cmp dword ptr [ebp + 0x2343277], ebx */
	if (m->zf) goto L_499a8f;	/* 499a81: je 0x499a8f */
L_499a83:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 499a83: fld dword ptr [esp + 0x54] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x3cu));	/* 499a87: fsub dword ptr [esp + 0x3c] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 499a8b: fstp dword ptr [esp + 0x54] */
L_499a8f:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343283u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499a8f: cmp dword ptr [ebp + 0x2343283], ebx */
	if (m->zf) goto L_499ac1;	/* 499a95: je 0x499ac1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 499a97: fld dword ptr [esp + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 499a9b: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 499aa1: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 499aa5: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 499aa9: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 499aaf: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 499ab3: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 499ab7: fmul dword ptr [0x4a9534] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 499abd: fstp dword ptr [esp + 0x58] */
L_499ac1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 499ac1: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x2343293u));	/* 499ac5: fmul dword ptr [ebp + 0x2343293] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ebp + 0x233ca28u));	/* 499acb: fsubr dword ptr [ebp + 0x233ca28] */
	MF((DWORD)(m->ebp + 0x233ca28u)) = (float)ST(0);	/* 499ad1: fst dword ptr [ebp + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a972cu)); FPOP();	/* 499ad7: fcomp dword ptr [0x4a972c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499add: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499adf: test ah, 0x41 */
	if (!m->zf) goto L_499aee;	/* 499ae2: jne 0x499aee */
	M32((DWORD)(m->ebp + 0x233ca28u)) = 0x445e8000u;	/* 499ae4: mov dword ptr [ebp + 0x233ca28], 0x445e8000 */
L_499aee:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 499aee: fld dword ptr [ebp + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9728u)); FPOP();	/* 499af4: fcomp dword ptr [0x4a9728] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499afa: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499afc: test ah, 1 */
	if (m->zf) goto L_499b0b;	/* 499aff: je 0x499b0b */
	M32((DWORD)(m->ebp + 0x233ca28u)) = 0xc45e8000u;	/* 499b01: mov dword ptr [ebp + 0x233ca28], 0xc45e8000 */
L_499b0b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 499b0b: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x2343297u));	/* 499b0f: fmul dword ptr [ebp + 0x2343297] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233ca2cu));	/* 499b15: fadd dword ptr [ebp + 0x233ca2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94c8u));	/* 499b1b: fcom dword ptr [0x4a94c8] */
	MF((DWORD)(m->ebp + 0x233ca2cu)) = (float)ST(0);	/* 499b21: fst dword ptr [ebp + 0x233ca2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499b27: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499b29: test ah, 1 */
	if (!m->zf) goto L_499b3c;	/* 499b2c: jne 0x499b3c */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 499b2e: fsub dword ptr [0x4a94c8] */
	MF((DWORD)(m->ebp + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 499b34: fstp dword ptr [ebp + 0x233ca2c] */
	goto L_499b3e;	/* 499b3a: jmp 0x499b3e */
L_499b3c:
	ST(0) = ST(0); FPOP();	/* 499b3c: fstp st(0) */
L_499b3e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 499b3e: fld dword ptr [ebp + 0x233ca2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 499b44: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499b4a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499b4c: test ah, 1 */
	if (m->zf) goto L_499b63;	/* 499b4f: je 0x499b63 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 499b51: fld dword ptr [ebp + 0x233ca2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 499b57: fadd dword ptr [0x4a94c8] */
	MF((DWORD)(m->ebp + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 499b5d: fstp dword ptr [ebp + 0x233ca2c] */
L_499b63:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234328bu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499b63: cmp dword ptr [ebp + 0x234328b], ebx */
	if (m->zf) goto L_499b99;	/* 499b69: je 0x499b99 */
	m->esp -= 4; M32(m->esp) = 0x499b70u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 499b6b: call 0x4686d0 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 499b70: fsub dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 499b74: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 499b75: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x499b7du; native_call(m, 0x4686e0u);	/* 499b78: call 0x4686e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 499b7d: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x499b85u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 499b80: call 0x4686d0 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 499b85: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499b8b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499b8d: test ah, 1 */
	if (m->zf) goto L_499bcd;	/* 499b90: je 0x499bcd */
	{ DWORD v_ = 0x41200000u; m->esp -= 4; M32(m->esp) = v_; }	/* 499b92: push 0x41200000 */
	goto L_499bc5;	/* 499b97: jmp 0x499bc5 */
L_499b99:
	m->esp -= 4; M32(m->esp) = 0x499b9eu; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 499b99: call 0x4686d0 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 499b9e: fadd dword ptr [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 499ba2: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 499ba3: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x499babu; native_call(m, 0x4686e0u);	/* 499ba6: call 0x4686e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 499bab: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x499bb3u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 499bae: call 0x4686d0 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94dcu)); FPOP();	/* 499bb3: fcomp dword ptr [0x4a94dc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499bb9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499bbb: test ah, 0x41 */
	if (!m->zf) goto L_499bcd;	/* 499bbe: jne 0x499bcd */
	{ DWORD v_ = 0x42700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 499bc0: push 0x42700000 */
L_499bc5:
	m->esp -= 4; M32(m->esp) = 0x499bcau; native_call(m, 0x4686e0u);	/* 499bc5: call 0x4686e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 499bca: add esp, 4 */
L_499bcd:
	m->eax = M32((DWORD)(m->ebp + 0x2340c78u));	/* 499bcd: mov eax, dword ptr [ebp + 0x2340c78] */
	m->edi = M32((DWORD)(m->ebp + 0x2340c80u));	/* 499bd3: mov edi, dword ptr [ebp + 0x2340c80] */
	m->ecx = M32((DWORD)(m->ebp + 0x2340c7cu));	/* 499bd9: mov ecx, dword ptr [ebp + 0x2340c7c] */
	m->edx = M32((DWORD)(m->ebp + 0x2340c84u));	/* 499bdf: mov edx, dword ptr [ebp + 0x2340c84] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 499be5: add edi, eax */
	m->eax = M32((DWORD)(m->ebp + 0x23423a1u));	/* 499be7: mov eax, dword ptr [ebp + 0x23423a1] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499bed: add edx, ecx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499bef: cmp eax, ebx */
	M32((DWORD)(m->ebp + 0x2340c80u)) = m->edi;	/* 499bf1: mov dword ptr [ebp + 0x2340c80], edi */
	M32((DWORD)(m->ebp + 0x2340c84u)) = m->edx;	/* 499bf7: mov dword ptr [ebp + 0x2340c84], edx */
	M32((DWORD)(m->ebp + 0x2340c78u)) = m->ebx;	/* 499bfd: mov dword ptr [ebp + 0x2340c78], ebx */
	M32((DWORD)(m->ebp + 0x2340c7cu)) = m->ebx;	/* 499c03: mov dword ptr [ebp + 0x2340c7c], ebx */
	if (!m->zf) goto L_499c74;	/* 499c09: jne 0x499c74 */
	m->esp -= 4; M32(m->esp) = 0x499c10u; native_call(m, 0x4a8350u);	/* 499c0b: call 0x4a8350 */
	m->edx = (DWORD)(m->esp + 0x170u);	/* 499c10: lea edx, [esp + 0x170] */
	m->eax = (DWORD)(m->esp + 0x7cu);	/* 499c17: lea eax, [esp + 0x7c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 499c1b: push edx */
	m->ecx = (DWORD)(m->esp + 0x7cu);	/* 499c1c: lea ecx, [esp + 0x7c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499c20: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 499c21: push ecx */
	m->esp -= 4; M32(m->esp) = 0x499c27u; native_call(m, 0x4a8450u);	/* 499c22: call 0x4a8450 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 499c27: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499c2a: cmp eax, ebx */
	if (m->zf) goto L_499c74;	/* 499c2c: je 0x499c74 */
L_499c2e:
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499c2e: cmp eax, esi */
	if (!m->zf) goto L_499c4b;	/* 499c30: jne 0x499c4b */
	m->eax = M32((DWORD)(m->esp + 0x7cu));	/* 499c32: mov eax, dword ptr [esp + 0x7c] */
	m->ecx = M32((DWORD)(m->esp + 0x78u));	/* 499c36: mov ecx, dword ptr [esp + 0x78] */
	m->edx = (DWORD)(m->esp + 0x170u);	/* 499c3a: lea edx, [esp + 0x170] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 499c41: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499c42: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 499c43: push ecx */
	m->ecx = m->ebp;	/* 499c44: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x499c4bu; native_call(m, 0x48c830u);	/* 499c46: call 0x48c830 */
L_499c4b:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340c7cu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebp + 0x2340c7cu)) = r_; }	/* 499c4b: inc dword ptr [ebp + 0x2340c7c] */
	m->esp -= 4; M32(m->esp) = 0x499c56u; native_call(m, 0x4a8350u);	/* 499c51: call 0x4a8350 */
	m->edx = (DWORD)(m->esp + 0x170u);	/* 499c56: lea edx, [esp + 0x170] */
	m->eax = (DWORD)(m->esp + 0x7cu);	/* 499c5d: lea eax, [esp + 0x7c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 499c61: push edx */
	m->ecx = (DWORD)(m->esp + 0x7cu);	/* 499c62: lea ecx, [esp + 0x7c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499c66: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 499c67: push ecx */
	m->esp -= 4; M32(m->esp) = 0x499c6du; native_call(m, 0x4a8450u);	/* 499c68: call 0x4a8450 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 499c6d: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499c70: cmp eax, ebx */
	if (!m->zf) goto L_499c2e;	/* 499c72: jne 0x499c2e */
L_499c74:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233cc20u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499c74: cmp dword ptr [ebp + 0x233cc20], esi */
	if (m->zf) goto L_49ca14;	/* 499c7a: je 0x49ca14 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342399u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499c80: cmp dword ptr [ebp + 0x2342399], esi */
	if (!m->zf) goto L_499cf7;	/* 499c86: jne 0x499cf7 */
	m->eax = M32((DWORD)(m->ebp + 0x23423b1u));	/* 499c88: mov eax, dword ptr [ebp + 0x23423b1] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499c8e: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_499ca6;	/* 499c90: jle 0x499ca6 */
	m->edx = m->eax;	/* 499c92: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499c94: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499c97: sub edx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x22f0408u));	/* 499c99: mov eax, dword ptr [ebp + 0x22f0408] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499c9f: shl edx, 2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499ca2: cmp eax, edx */
	if (m->sf == m->of) goto L_499cf7;	/* 499ca4: jge 0x499cf7 */
L_499ca6:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 499ca6: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x234239du));	/* 499cac: fsub dword ptr [ebp + 0x234239d] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 499cb2: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499cb8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499cba: test ah, 1 */
	if (m->zf) goto L_499cf7;	/* 499cbd: je 0x499cf7 */
	m->eax = M32((DWORD)(m->ebp + 0x2221fb0u));	/* 499cbf: mov eax, dword ptr [ebp + 0x2221fb0] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499cc5: cmp eax, ebx */
	if (m->sf != m->of) goto L_499cf7;	/* 499cc7: jl 0x499cf7 */
	m->ecx = m->eax;	/* 499cc9: mov ecx, eax */
	m->edx = 0x2u;	/* 499ccb: mov edx, 2 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499cd0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499cd3: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499cd5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499cd8: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499cda: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499cdd: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccbbcu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499cdf: cmp dword ptr [ebp + ecx*8 + 0x1eccbbc], edx */
	if (!m->zf) goto L_499cfc;	/* 499ce6: jne 0x499cfc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 499ce8: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9468u));	/* 499ceb: fmul dword ptr [0x4a9468] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 499cf1: fstp dword ptr [esp + 0x38] */
	goto L_499d03;	/* 499cf5: jmp 0x499d03 */
L_499cf7:
	m->edx = 0x2u;	/* 499cf7: mov edx, 2 */
L_499cfc:
	m->eax = M32((DWORD)(m->ebp + 0x44u));	/* 499cfc: mov eax, dword ptr [ebp + 0x44] */
	M32((DWORD)(m->esp + 0x38u)) = m->eax;	/* 499cff: mov dword ptr [esp + 0x38], eax */
L_499d03:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340ce0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d03: cmp dword ptr [ebp + 0x2340ce0], ebx */
	if (!m->zf) goto L_49a124;	/* 499d09: jne 0x49a124 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340cf4u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d0f: cmp dword ptr [ebp + 0x2340cf4], esi */
	if (!m->zf) goto L_499d20;	/* 499d15: jne 0x499d20 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d17: cmp dword ptr [ebp + 8], ebx */
	if (m->zf) goto L_49a124;	/* 499d1a: je 0x49a124 */
L_499d20:
	m->ecx = M32((DWORD)(m->ebp + 0x233c9fcu));	/* 499d20: mov ecx, dword ptr [ebp + 0x233c9fc] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d26: cmp ecx, ebx */
	if (!m->zf) goto L_499d56;	/* 499d28: jne 0x499d56 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23424f2u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d2a: cmp dword ptr [ebp + 0x23424f2], edx */
	if (!m->zf) goto L_499d56;	/* 499d30: jne 0x499d56 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 499d32: mov eax, dword ptr [ebp + 0x2340c64] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d38: cmp eax, ebx */
	if (m->sf != m->of) goto L_499d56;	/* 499d3a: jl 0x499d56 */
	m->ecx = m->eax;	/* 499d3c: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499d3e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499d41: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499d43: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499d46: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499d48: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499d4b: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccfc0u)) = m->esi;	/* 499d4d: mov dword ptr [ebp + ecx*8 + 0x1eccfc0], esi */
	goto L_499d84;	/* 499d54: jmp 0x499d84 */
L_499d56:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d56: cmp ecx, esi */
	if (!m->zf) goto L_499d84;	/* 499d58: jne 0x499d84 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233cc10u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d5a: cmp dword ptr [ebp + 0x233cc10], edx */
	if (!m->zf) goto L_499d84;	/* 499d60: jne 0x499d84 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 499d62: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d68: cmp eax, ebx */
	if (m->sf != m->of) goto L_499d84;	/* 499d6a: jl 0x499d84 */
	m->edx = m->eax;	/* 499d6c: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499d6e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499d71: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499d73: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499d76: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499d78: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499d7b: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccfc0u)) = m->esi;	/* 499d7d: mov dword ptr [ebp + edx*8 + 0x1eccfc0], esi */
L_499d84:
	m->edi = M32((DWORD)(m->esp + 0x38u));	/* 499d84: mov edi, dword ptr [esp + 0x38] */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 499d88: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 499d8e: push edi */
	m->ecx = m->esi;	/* 499d8f: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499d96u; native_call(m, 0x496e40u);	/* 499d91: call 0x496e40 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 499d96: push edi */
	m->ecx = m->esi;	/* 499d97: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499d9eu; native_call(m, 0x45e0c0u);	/* 499d99: call 0x45e0c0 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342399u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499d9e: cmp dword ptr [ebp + 0x2342399], 1 */
	if (m->zf) goto L_499db0;	/* 499da5: je 0x499db0 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a1u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499da7: cmp dword ptr [ebp + 0x23423a1], 1 */
	if (!m->zf) goto L_499db7;	/* 499dae: jne 0x499db7 */
L_499db0:
	m->ecx = m->esi;	/* 499db0: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499db7u; native_call(m, 0x47cfd0u);	/* 499db2: call 0x47cfd0 */
L_499db7:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 499db7: push edi */
	m->ecx = m->esi;	/* 499db8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499dbfu; native_call(m, 0x47d000u);	/* 499dba: call 0x47d000 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 499dbf: push edi */
	m->ecx = m->esi;	/* 499dc0: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499dc7u; native_call(m, 0x479a90u);	/* 499dc2: call 0x479a90 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 499dc7: push edi */
	m->ecx = m->esi;	/* 499dc8: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499dcfu; native_call(m, 0x48ed90u);	/* 499dca: call 0x48ed90 */
	m->ecx = m->esi;	/* 499dcf: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499dd6u; native_call(m, 0x472310u);	/* 499dd1: call 0x472310 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 499dd6: push edi */
	m->ecx = m->esi;	/* 499dd7: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499ddeu; native_call(m, 0x490d40u);	/* 499dd9: call 0x490d40 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 499dde: push edi */
	m->ecx = m->esi;	/* 499ddf: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499de6u; native_call(m, 0x48fd50u);	/* 499de1: call 0x48fd50 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499de6: cmp dword ptr [ebp + 8], 1 */
	if (!m->zf) goto L_499e88;	/* 499dea: jne 0x499e88 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2342405u)));	/* 499df0: fld dword ptr [ebp + 0x2342405] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 499df6: fsub dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x2342405u)) = (float)ST(0);	/* 499df9: fst dword ptr [ebp + 0x2342405] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 499dff: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499e05: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499e07: test ah, 1 */
	if (m->zf) goto L_499e59;	/* 499e0a: je 0x499e59 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 499e0c: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499e12: cmp eax, ebx */
	if (m->sf != m->of) goto L_499e59;	/* 499e14: jl 0x499e59 */
	m->ecx = m->eax;	/* 499e16: mov ecx, eax */
	m->edi = 0x1u;	/* 499e18: mov edi, 1 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499e1d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499e20: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499e22: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499e25: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499e27: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499e2a: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccbbcu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499e2c: cmp dword ptr [ebp + ecx*8 + 0x1eccbbc], edi */
	if (!m->zf) goto L_499e5e;	/* 499e33: jne 0x499e5e */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 499e35: push eax */
	m->ecx = m->esi;	/* 499e36: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x499e3du; native_call(m, 0x45ee40u);	/* 499e38: call 0x45ee40 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 499e3d: test eax, eax */
	if (!m->zf) goto L_499e4d;	/* 499e3f: jne 0x499e4d */
	M32((DWORD)(m->ebp + 0x23423fdu)) = m->edi;	/* 499e41: mov dword ptr [ebp + 0x23423fd], edi */
	M32((DWORD)(m->ebp + 0x2342401u)) = m->ebx;	/* 499e47: mov dword ptr [ebp + 0x2342401], ebx */
L_499e4d:
	M32((DWORD)(m->ebp + 0x2342405u)) = 0x41a00000u;	/* 499e4d: mov dword ptr [ebp + 0x2342405], 0x41a00000 */
	goto L_499e5e;	/* 499e57: jmp 0x499e5e */
L_499e59:
	m->edi = 0x1u;	/* 499e59: mov edi, 1 */
L_499e5e:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423fdu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499e5e: cmp dword ptr [ebp + 0x23423fd], edi */
	if (!m->zf) goto L_499e88;	/* 499e64: jne 0x499e88 */
	m->ecx = m->ebp;	/* 499e66: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x499e6du; native_call(m, 0x4633f0u);	/* 499e68: call 0x4633f0 */
	M32((DWORD)(m->ebp + 0x23423a1u)) = m->edi;	/* 499e6d: mov dword ptr [ebp + 0x23423a1], edi */
	M32((DWORD)(m->ebp + 0x23423a5u)) = 0x40400000u;	/* 499e73: mov dword ptr [ebp + 0x23423a5], 0x40400000 */
	m->esp -= 4; M32(m->esp) = 0x499e82u; native_call(m, 0x457310u);	/* 499e7d: call 0x457310 */
	M32((DWORD)(m->ebp + 0x23423fdu)) = m->ebx;	/* 499e82: mov dword ptr [ebp + 0x23423fd], ebx */
L_499e88:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9fcu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499e88: cmp dword ptr [ebp + 0x233c9fc], ebx */
	if (!m->zf) goto L_49a124;	/* 499e8e: jne 0x49a124 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 499e94: mov eax, dword ptr [ebp + 0x2340c64] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499e9a: cmp eax, ebx */
	if (m->sf != m->of) goto L_499ec3;	/* 499e9c: jl 0x499ec3 */
	m->edx = m->eax;	/* 499e9e: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499ea0: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499ea3: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499ea5: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499ea8: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 499eaa: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 499ead: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb88u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499eaf: cmp dword ptr [ebp + edx*8 + 0x1eccb88], ebx */
	if (m->sf == m->of) goto L_499ec3;	/* 499eb6: jge 0x499ec3 */
	{ DWORD a_ = m->edi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 499eb8: or edi, 0xffffffff */
	M32((DWORD)(m->ebp + 0x2340c64u)) = m->edi;	/* 499ebb: mov dword ptr [ebp + 0x2340c64], edi */
	goto L_499ec6;	/* 499ec1: jmp 0x499ec6 */
L_499ec3:
	{ DWORD a_ = m->edi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 499ec3: or edi, 0xffffffff */
L_499ec6:
	m->eax = M32((DWORD)(m->ebp + 0x2343307u));	/* 499ec6: mov eax, dword ptr [ebp + 0x2343307] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499ecc: cmp eax, ebx */
	if (m->sf != m->of) goto L_499f1b;	/* 499ece: jl 0x499f1b */
	m->ecx = m->eax;	/* 499ed0: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499ed2: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499ed5: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499ed7: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499eda: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499edc: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499edf: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb88u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499ee1: cmp dword ptr [ebp + ecx*8 + 0x1eccb88], ebx */
	if (m->sf != m->of) goto L_499fe5;	/* 499ee8: jl 0x499fe5 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23424f2u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499eee: cmp dword ptr [ebp + 0x23424f2], ebx */
	if (m->sf == m->of) goto L_499f00;	/* 499ef4: jge 0x499f00 */
	M32((DWORD)(m->ebp + 0x23424f2u)) = 0x1u;	/* 499ef6: mov dword ptr [ebp + 0x23424f2], 1 */
L_499f00:
	M32((DWORD)(m->ebp + 0x2340c64u)) = m->eax;	/* 499f00: mov dword ptr [ebp + 0x2340c64], eax */
	M32((DWORD)(m->ebp + 0x233cc38u)) = m->ebx;	/* 499f06: mov dword ptr [ebp + 0x233cc38], ebx */
	M32((DWORD)(m->ebp + 0x2340c68u)) = 0x1u;	/* 499f0c: mov dword ptr [ebp + 0x2340c68], 1 */
	goto L_499fe5;	/* 499f16: jmp 0x499fe5 */
L_499f1b:
	m->edx = M32((DWORD)(m->ebp + 0x2221f90u));	/* 499f1b: mov edx, dword ptr [ebp + 0x2221f90] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499f21: cmp edx, ebx */
	if (m->zf || m->sf != m->of) goto L_499fe5;	/* 499f23: jle 0x499fe5 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234331bu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499f29: cmp dword ptr [ebp + 0x234331b], 1 */
	if (m->zf) goto L_499f49;	/* 499f30: je 0x499f49 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc38u)));	/* 499f32: fld dword ptr [ebp + 0x233cc38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa278u)); FPOP();	/* 499f38: fcomp dword ptr [0x4aa278] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 499f3e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 499f40: test ah, 0x41 */
	if (!m->zf) goto L_499fe5;	/* 499f43: jne 0x499fe5 */
L_499f49:
	m->esi = M32((DWORD)(m->ebp + 0x2340c64u));	/* 499f49: mov esi, dword ptr [ebp + 0x2340c64] */
	m->eax = (DWORD)(m->esi + 0x1u);	/* 499f4f: lea eax, [esi + 1] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499f52: cmp eax, edx */
	if (m->zf) goto L_499fab;	/* 499f54: je 0x499fab */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499f56: cmp eax, esi */
	if (m->zf) goto L_499fe5;	/* 499f58: je 0x499fe5 */
	m->ecx = m->eax;	/* 499f5e: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499f60: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499f63: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499f65: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499f68: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 499f6a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499f6d: add ecx, eax */
	m->ecx = (DWORD)(m->ebp + m->ecx*8 + 0x1eccb88u);	/* 499f6f: lea ecx, [ebp + ecx*8 + 0x1eccb88] */
L_499f76:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499f76: cmp dword ptr [ecx], ebx */
	if (m->sf == m->of) goto L_499f8b;	/* 499f78: jge 0x499f8b */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 499f7a: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 499f7b: add ecx, 0x8888 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499f81: cmp eax, edx */
	if (m->sf == m->of) goto L_499fab;	/* 499f83: jge 0x499fab */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499f85: cmp eax, esi */
	if (!m->zf) goto L_499f76;	/* 499f87: jne 0x499f76 */
	goto L_499fe5;	/* 499f89: jmp 0x499fe5 */
L_499f8b:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23424f2u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499f8b: cmp dword ptr [ebp + 0x23424f2], ebx */
	if (m->sf == m->of) goto L_499f9d;	/* 499f91: jge 0x499f9d */
	M32((DWORD)(m->ebp + 0x23424f2u)) = 0x1u;	/* 499f93: mov dword ptr [ebp + 0x23424f2], 1 */
L_499f9d:
	M32((DWORD)(m->ebp + 0x2340c64u)) = m->eax;	/* 499f9d: mov dword ptr [ebp + 0x2340c64], eax */
	M32((DWORD)(m->ebp + 0x233cc38u)) = m->ebx;	/* 499fa3: mov dword ptr [ebp + 0x233cc38], ebx */
	goto L_499fe5;	/* 499fa9: jmp 0x499fe5 */
L_499fab:
	m->edx = (DWORD)(m->ebp + 0x22ee228u);	/* 499fab: lea edx, [ebp + 0x22ee228] */
	M32((DWORD)(m->ebp + 0x2340c64u)) = m->edi;	/* 499fb1: mov dword ptr [ebp + 0x2340c64], edi */
	m->eax = (DWORD)(m->ebp + 0x233ca04u);	/* 499fb7: lea eax, [ebp + 0x233ca04] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 499fbd: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 499fbf: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 499fc1: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 499fc4: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 499fc7: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 499fca: mov dword ptr [eax + 8], edx */
	m->eax = M32((DWORD)(m->ebp + 0x22ee234u));	/* 499fcd: mov eax, dword ptr [ebp + 0x22ee234] */
	M32((DWORD)(m->ebp + 0x233ca28u)) = m->eax;	/* 499fd3: mov dword ptr [ebp + 0x233ca28], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x22ee238u));	/* 499fd9: mov ecx, dword ptr [ebp + 0x22ee238] */
	M32((DWORD)(m->ebp + 0x233ca2cu)) = m->ecx;	/* 499fdf: mov dword ptr [ebp + 0x233ca2c], ecx */
L_499fe5:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340c64u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499fe5: cmp dword ptr [ebp + 0x2340c64], ebx */
	if (m->sf != m->of) goto L_49a0f6;	/* 499feb: jl 0x49a0f6 */
	m->eax = M32((DWORD)(m->ebp + 0x234331fu));	/* 499ff1: mov eax, dword ptr [ebp + 0x234331f] */
	m->esi = 0x1u;	/* 499ff7: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 499ffc: cmp eax, esi */
	if (!m->zf) goto L_49a01a;	/* 499ffe: jne 0x49a01a */
	m->eax = M32((DWORD)(m->ebp + 0x23424f2u));	/* 49a000: mov eax, dword ptr [ebp + 0x23424f2] */
	m->ecx = 0xau;	/* 49a006: mov ecx, 0xa */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49a00b: inc eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49a00c: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49a00d: idiv ecx */
	M32((DWORD)(m->ebp + 0x23424f2u)) = m->edx;	/* 49a00f: mov dword ptr [ebp + 0x23424f2], edx */
	goto L_49a0f6;	/* 49a015: jmp 0x49a0f6 */
L_49a01a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc3cu)));	/* 49a01a: fld dword ptr [ebp + 0x233cc3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa47cu)); FPOP();	/* 49a020: fcomp dword ptr [0x4aa47c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a026: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a028: test ah, 0x41 */
	if (!m->zf) goto L_49a0f6;	/* 49a02b: jne 0x49a0f6 */
	m->ecx = M32((DWORD)(0xa1efb8u));	/* 49a031: mov ecx, dword ptr [0xa1efb8] */
	m->edi = 0x64u;	/* 49a037: mov edi, 0x64 */
	m->edx = m->ecx;	/* 49a03c: mov edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0xfffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49a03e: and edx, 0xfff */
	m->eax = M32((DWORD)(m->edx*4 + 0xa106f8u));	/* 49a044: mov eax, dword ptr [edx*4 + 0xa106f8] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49a04b: xor edx, edx */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->edi; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 49a04d: div edi */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49a04f: inc ecx */
	M32((DWORD)(0xa1efb8u)) = m->ecx;	/* 49a050: mov dword ptr [0xa1efb8], ecx */
	{ DWORD a_ = m->edx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a056: cmp edx, 5 */
	M32((DWORD)(m->ebp + 0x23424f2u)) = m->edx;	/* 49a059: mov dword ptr [ebp + 0x23424f2], edx */
	if (m->sf == m->of) goto L_49a06c;	/* 49a05f: jge 0x49a06c */
	M32((DWORD)(m->ebp + 0x23424f2u)) = m->ebx;	/* 49a061: mov dword ptr [ebp + 0x23424f2], ebx */
	goto L_49a0f0;	/* 49a067: jmp 0x49a0f0 */
L_49a06c:
	{ DWORD a_ = m->edx, b_ = 0x23u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a06c: cmp edx, 0x23 */
	if (m->sf == m->of) goto L_49a079;	/* 49a06f: jge 0x49a079 */
	M32((DWORD)(m->ebp + 0x23424f2u)) = m->esi;	/* 49a071: mov dword ptr [ebp + 0x23424f2], esi */
	goto L_49a0f0;	/* 49a077: jmp 0x49a0f0 */
L_49a079:
	{ DWORD a_ = m->edx, b_ = 0x2du & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a079: cmp edx, 0x2d */
	if (m->sf == m->of) goto L_49a08a;	/* 49a07c: jge 0x49a08a */
	M32((DWORD)(m->ebp + 0x23424f2u)) = 0x2u;	/* 49a07e: mov dword ptr [ebp + 0x23424f2], 2 */
	goto L_49a0f0;	/* 49a088: jmp 0x49a0f0 */
L_49a08a:
	{ DWORD a_ = m->edx, b_ = 0x32u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a08a: cmp edx, 0x32 */
	if (m->sf == m->of) goto L_49a09b;	/* 49a08d: jge 0x49a09b */
	M32((DWORD)(m->ebp + 0x23424f2u)) = 0x3u;	/* 49a08f: mov dword ptr [ebp + 0x23424f2], 3 */
	goto L_49a0f0;	/* 49a099: jmp 0x49a0f0 */
L_49a09b:
	{ DWORD a_ = m->edx, b_ = 0x37u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a09b: cmp edx, 0x37 */
	if (m->sf == m->of) goto L_49a0ac;	/* 49a09e: jge 0x49a0ac */
	M32((DWORD)(m->ebp + 0x23424f2u)) = 0x4u;	/* 49a0a0: mov dword ptr [ebp + 0x23424f2], 4 */
	goto L_49a0f0;	/* 49a0aa: jmp 0x49a0f0 */
L_49a0ac:
	{ DWORD a_ = m->edx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a0ac: cmp edx, 0x3c */
	if (m->sf == m->of) goto L_49a0bd;	/* 49a0af: jge 0x49a0bd */
	M32((DWORD)(m->ebp + 0x23424f2u)) = 0x5u;	/* 49a0b1: mov dword ptr [ebp + 0x23424f2], 5 */
	goto L_49a0f0;	/* 49a0bb: jmp 0x49a0f0 */
L_49a0bd:
	{ DWORD a_ = m->edx, b_ = 0x41u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a0bd: cmp edx, 0x41 */
	if (m->sf == m->of) goto L_49a0ce;	/* 49a0c0: jge 0x49a0ce */
	M32((DWORD)(m->ebp + 0x23424f2u)) = 0x6u;	/* 49a0c2: mov dword ptr [ebp + 0x23424f2], 6 */
	goto L_49a0f0;	/* 49a0cc: jmp 0x49a0f0 */
L_49a0ce:
	{ DWORD a_ = m->edx, b_ = 0x46u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a0ce: cmp edx, 0x46 */
	if (m->sf == m->of) goto L_49a0df;	/* 49a0d1: jge 0x49a0df */
	M32((DWORD)(m->ebp + 0x23424f2u)) = 0x7u;	/* 49a0d3: mov dword ptr [ebp + 0x23424f2], 7 */
	goto L_49a0f0;	/* 49a0dd: jmp 0x49a0f0 */
L_49a0df:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49a0df: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = 0x4bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a0e1: cmp edx, 0x4b */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 49a0e4: setge al */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49a0e7: add eax, 8 */
	M32((DWORD)(m->ebp + 0x23424f2u)) = m->eax;	/* 49a0ea: mov dword ptr [ebp + 0x23424f2], eax */
L_49a0f0:
	M32((DWORD)(m->ebp + 0x233cc3cu)) = m->ebx;	/* 49a0f0: mov dword ptr [ebp + 0x233cc3c], ebx */
L_49a0f6:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340c68u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a0f6: cmp dword ptr [ebp + 0x2340c68], ebx */
	if (!m->zf) goto L_49a10d;	/* 49a0fc: jne 0x49a10d */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc38u)));	/* 49a0fe: fld dword ptr [ebp + 0x233cc38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49a104: fadd dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x233cc38u)) = (float)ST(0); FPOP();	/* 49a107: fstp dword ptr [ebp + 0x233cc38] */
L_49a10d:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340c6cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a10d: cmp dword ptr [ebp + 0x2340c6c], ebx */
	if (!m->zf) goto L_49a124;	/* 49a113: jne 0x49a124 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 49a115: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc3cu));	/* 49a118: fadd dword ptr [ebp + 0x233cc3c] */
	MF((DWORD)(m->ebp + 0x233cc3cu)) = (float)ST(0); FPOP();	/* 49a11e: fstp dword ptr [ebp + 0x233cc3c] */
L_49a124:
	m->eax = M32((DWORD)(m->ebp + 0x2221f90u));	/* 49a124: mov eax, dword ptr [ebp + 0x2221f90] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 49a12a: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a12c: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_49a15d;	/* 49a12e: jle 0x49a15d */
	m->esi = (DWORD)(m->ebp + 0x1ed52d8u);	/* 49a130: lea esi, [ebp + 0x1ed52d8] */
L_49a136:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a136: cmp dword ptr [esi], 1 */
	if (!m->zf) goto L_49a14c;	/* 49a139: jne 0x49a14c */
	m->ecx = M32((DWORD)(m->esi + 0xffff7c58u));	/* 49a13b: mov ecx, dword ptr [esi - 0x83a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a141: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a142: push edi */
	m->ecx = m->ebp;	/* 49a143: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a14au; native_call(m, 0x4630c0u);	/* 49a145: call 0x4630c0 */
	M32((DWORD)(m->esi + 0x0u)) = m->ebx;	/* 49a14a: mov dword ptr [esi], ebx */
L_49a14c:
	m->eax = M32((DWORD)(m->ebp + 0x2221f90u));	/* 49a14c: mov eax, dword ptr [ebp + 0x2221f90] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 49a152: inc edi */
	{ DWORD a_ = m->esi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 49a153: add esi, 0x8888 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a159: cmp edi, eax */
	if (m->sf != m->of) goto L_49a136;	/* 49a15b: jl 0x49a136 */
L_49a15d:
	m->edx = M32((DWORD)(m->ebp + 0x44u));	/* 49a15d: mov edx, dword ptr [ebp + 0x44] */
	m->ecx = m->ebp;	/* 49a160: mov ecx, ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a162: push edx */
	m->esp -= 4; M32(m->esp) = 0x49a168u; native_call(m, 0x462ac0u);	/* 49a163: call 0x462ac0 */
	m->eax = M32((DWORD)(m->ebp + 0x234328fu));	/* 49a168: mov eax, dword ptr [ebp + 0x234328f] */
	m->edi = 0x1u;	/* 49a16e: mov edi, 1 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a173: cmp eax, edi */
	if (!m->zf) goto L_49a181;	/* 49a175: jne 0x49a181 */
	M32((DWORD)(m->ebp + 0x233cc40u)) = 0x40a00000u;	/* 49a177: mov dword ptr [ebp + 0x233cc40], 0x40a00000 */
L_49a181:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a181: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a187: cmp eax, ebx */
	if (m->sf != m->of) goto L_49a1ce;	/* 49a189: jl 0x49a1ce */
	m->ecx = m->eax;	/* 49a18b: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a18d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a190: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a192: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a195: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a197: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a19a: add ecx, eax */
	m->eax = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccbbcu));	/* 49a19c: mov eax, dword ptr [ebp + ecx*8 + 0x1eccbbc] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a1a3: cmp eax, edi */
	m->ecx = (DWORD)(m->ebp + m->ecx*8 + 0x0u);	/* 49a1a5: lea ecx, [ebp + ecx*8] */
	if (!m->zf) goto L_49a1ce;	/* 49a1a9: jne 0x49a1ce */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccfa4u)));	/* 49a1ab: fld dword ptr [ecx + 0x1eccfa4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49a1b1: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a1b7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a1b9: test ah, 0x40 */
	if (m->zf) goto L_49a1ce;	/* 49a1bc: je 0x49a1ce */
	{ DWORD a_ = m->ecx, b_ = 0x1eccf64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a1be: add ecx, 0x1eccf64 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a1c4: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49a1c5: push ebp */
	m->esp -= 4; M32(m->esp) = 0x49a1cbu; native_call(m, 0x463450u);	/* 49a1c6: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a1cb: add esp, 8 */
L_49a1ce:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x23423c1u)));	/* 49a1ce: fld dword ptr [ebp + 0x23423c1] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49a1d4: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a1da: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a1dc: test ah, 0x41 */
	if (!m->zf) goto L_49a267;	/* 49a1df: jne 0x49a267 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x23423c1u)));	/* 49a1e5: fld dword ptr [ebp + 0x23423c1] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49a1eb: fsub dword ptr [ebp + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 49a1ee: fcom dword ptr [0x4a93e8] */
	MF((DWORD)(m->ebp + 0x23423c1u)) = (float)ST(0);	/* 49a1f4: fst dword ptr [ebp + 0x23423c1] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a1fa: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a1fc: test ah, 1 */
	if (m->zf) goto L_49a222;	/* 49a1ff: je 0x49a222 */
	{ DWORD v_ = 0x4d0610u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a201: push 0x4d0610 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49a206: push ebp */
	ST(0) = ST(0); FPOP();	/* 49a207: fstp st(0) */
	M32((DWORD)(m->ebp + 0x23423c1u)) = m->ebx;	/* 49a209: mov dword ptr [ebp + 0x23423c1], ebx */
	m->esp -= 4; M32(m->esp) = 0x49a214u; native_call(m, 0x463450u);	/* 49a20f: call 0x463450 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a214: push 0x64 */
	{ DWORD v_ = 0x17u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a216: push 0x17 */
	m->esp -= 4; M32(m->esp) = 0x49a21du; native_call(m, 0x456e50u);	/* 49a218: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a21d: add esp, 0x10 */
	goto L_49a267;	/* 49a220: jmp 0x49a267 */
L_49a222:
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49a222: call 0x49ec14 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423c5u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a227: cmp dword ptr [ebp + 0x23423c5], eax */
	if (m->zf) goto L_49a267;	/* 49a22d: je 0x49a267 */
	M32((DWORD)(m->ebp + 0x23423c5u)) = m->eax;	/* 49a22f: mov dword ptr [ebp + 0x23423c5], eax */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49a235: inc eax */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49a236: dec eax */
	if (m->zf) goto L_49a24d;	/* 49a237: je 0x49a24d */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49a239: dec eax */
	if (m->zf) goto L_49a246;	/* 49a23a: je 0x49a246 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49a23c: dec eax */
	if (!m->zf) goto L_49a25b;	/* 49a23d: jne 0x49a25b */
	{ DWORD v_ = 0x4d0608u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a23f: push 0x4d0608 */
	goto L_49a252;	/* 49a244: jmp 0x49a252 */
L_49a246:
	{ DWORD v_ = 0x4d0600u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a246: push 0x4d0600 */
	goto L_49a252;	/* 49a24b: jmp 0x49a252 */
L_49a24d:
	{ DWORD v_ = 0x4d05f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a24d: push 0x4d05f8 */
L_49a252:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49a252: push ebp */
	m->esp -= 4; M32(m->esp) = 0x49a258u; native_call(m, 0x463450u);	/* 49a253: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a258: add esp, 8 */
L_49a25b:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a25b: push 0x64 */
	{ DWORD v_ = 0x9u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a25d: push 9 */
	m->esp -= 4; M32(m->esp) = 0x49a264u; native_call(m, 0x456e50u);	/* 49a25f: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a264: add esp, 8 */
L_49a267:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9f0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a267: cmp dword ptr [ebp + 0x233c9f0], edi */
	if (!m->zf) goto L_49a2bd;	/* 49a26d: jne 0x49a2bd */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a26f: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a275: cmp eax, ebx */
	if (m->sf != m->of) goto L_49a2bd;	/* 49a277: jl 0x49a2bd */
	m->edx = m->eax;	/* 49a279: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a27b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a27e: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a280: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a283: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a285: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a288: add edx, eax */
	m->ecx = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb4cu));	/* 49a28a: mov ecx, dword ptr [ebp + edx*8 + 0x1eccb4c] */
	m->eax = (DWORD)(m->ebp + m->edx*8 + 0x0u);	/* 49a291: lea eax, [ebp + edx*8] */
	m->edx = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb50u));	/* 49a295: mov edx, dword ptr [ebp + edx*8 + 0x1eccb50] */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a29c: cmp ecx, edx */
	if (m->zf) goto L_49a2bd;	/* 49a29e: je 0x49a2bd */
	{ DWORD v_ = 0x4d05ecu; m->esp -= 4; M32(m->esp) = v_; }	/* 49a2a0: push 0x4d05ec */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49a2a5: push ebp */
	M32((DWORD)(m->eax + 0x1eccb50u)) = m->ecx;	/* 49a2a6: mov dword ptr [eax + 0x1eccb50], ecx */
	m->esp -= 4; M32(m->esp) = 0x49a2b1u; native_call(m, 0x463450u);	/* 49a2ac: call 0x463450 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a2b1: push 0x64 */
	{ DWORD v_ = 0x18u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a2b3: push 0x18 */
	m->esp -= 4; M32(m->esp) = 0x49a2bau; native_call(m, 0x456e50u);	/* 49a2b5: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a2ba: add esp, 0x10 */
L_49a2bd:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + 0x22f0414u))) & 0xff) << 0);	/* 49a2bd: mov al, byte ptr [ebp + 0x22f0414] */
	m->esi = (DWORD)(m->ebp + 0x22f0414u);	/* 49a2c3: lea esi, [ebp + 0x22f0414] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a2c9: test al, al */
	if (m->zf) goto L_49a2da;	/* 49a2cb: je 0x49a2da */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a2cd: push esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 49a2ce: push ebp */
	m->esp -= 4; M32(m->esp) = 0x49a2d4u; native_call(m, 0x463450u);	/* 49a2cf: call 0x463450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a2d4: add esp, 8 */
	M8((DWORD)(m->esi + 0x0u)) = (BYTE)(0x0u);	/* 49a2d7: mov byte ptr [esi], 0 */
L_49a2da:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2221fb4u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a2da: cmp dword ptr [ebp + 0x2221fb4], edi */
	if (m->zf) goto L_49a2f5;	/* 49a2e0: je 0x49a2f5 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc58u)));	/* 49a2e2: fld dword ptr [ebp + 0x233cc58] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49a2e8: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a2ee: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a2f0: test ah, 0x41 */
	if (m->zf) goto L_49a350;	/* 49a2f3: je 0x49a350 */
L_49a2f5:
	m->ecx = m->ebp;	/* 49a2f5: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a2fcu; native_call(m, 0x462150u);	/* 49a2f7: call 0x462150 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a2fc: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49a302: push eax */
	m->esp -= 4; M32(m->esp) = 0x49a308u; native_call(m, 0x4a8700u);	/* 49a303: call 0x4a8700 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a308: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a30b: cmp eax, edi */
	if (!m->zf) goto L_49a340;	/* 49a30d: jne 0x49a340 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 49a30f: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*4 + 0x2342936u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a315: cmp dword ptr [ebp + ecx*4 + 0x2342936], edi */
	if (!m->zf) goto L_49a340;	/* 49a31c: jne 0x49a340 */
	m->eax = M32((DWORD)(m->ebp + 0x234297au));	/* 49a31e: mov eax, dword ptr [ebp + 0x234297a] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a324: cmp eax, edi */
	if (!m->zf && m->sf == m->of) goto L_49a334;	/* 49a326: jg 0x49a334 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e719cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a328: cmp dword ptr [ebp + 0x22e719c], edi */
	if (!m->zf) goto L_49a340;	/* 49a32e: jne 0x49a340 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a330: cmp eax, edi */
	if (m->zf) goto L_49a340;	/* 49a332: je 0x49a340 */
L_49a334:
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a334: push 0x64 */
	{ DWORD v_ = 0xfu; m->esp -= 4; M32(m->esp) = v_; }	/* 49a336: push 0xf */
	m->esp -= 4; M32(m->esp) = 0x49a33du; native_call(m, 0x456e50u);	/* 49a338: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a33d: add esp, 8 */
L_49a340:
	M32((DWORD)(m->ebp + 0x2221fb4u)) = m->ebx;	/* 49a340: mov dword ptr [ebp + 0x2221fb4], ebx */
	M32((DWORD)(m->ebp + 0x233cc58u)) = 0x40a00000u;	/* 49a346: mov dword ptr [ebp + 0x233cc58], 0x40a00000 */
L_49a350:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340d1du)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a350: cmp dword ptr [ebp + 0x2340d1d], edi */
	if (!m->zf) goto L_49a367;	/* 49a356: jne 0x49a367 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 49a358: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x2340d29u));	/* 49a35b: fadd dword ptr [ebp + 0x2340d29] */
	MF((DWORD)(m->ebp + 0x2340d29u)) = (float)ST(0); FPOP();	/* 49a361: fstp dword ptr [ebp + 0x2340d29] */
L_49a367:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234240du)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a367: cmp dword ptr [ebp + 0x234240d], ebx */
	if (m->sf != m->of) goto L_49a529;	/* 49a36d: jl 0x49a529 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc54u)));	/* 49a373: fld dword ptr [ebp + 0x233cc54] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49a379: fsub dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x233cc54u)) = (float)ST(0);	/* 49a37c: fst dword ptr [ebp + 0x233cc54] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49a382: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a388: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a38a: test ah, 0x41 */
	if (m->zf) goto L_49a3a9;	/* 49a38d: je 0x49a3a9 */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 49a38f: mov edx, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a395: shl edx, 4 */
	M32((DWORD)(m->edx + m->ebp*1 + 0x2343006u)) = m->edi;	/* 49a398: mov dword ptr [edx + ebp + 0x2343006], edi */
	M32((DWORD)(m->ebp + 0x233cc54u)) = 0x40400000u;	/* 49a39f: mov dword ptr [ebp + 0x233cc54], 0x40400000 */
L_49a3a9:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a3a9: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49a3af: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a3b1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a3b4: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a3b6: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a3b9: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a3bb: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a3be: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb88u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a3c0: cmp dword ptr [ebp + ecx*8 + 0x1eccb88], ebx */
	if (m->sf != m->of) goto L_49a3ff;	/* 49a3c7: jl 0x49a3ff */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc5cu)));	/* 49a3c9: fld dword ptr [ebp + 0x233cc5c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49a3cf: fsub dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x233cc5cu)) = (float)ST(0);	/* 49a3d2: fst dword ptr [ebp + 0x233cc5c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49a3d8: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a3de: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a3e0: test ah, 0x41 */
	if (m->zf) goto L_49a3ff;	/* 49a3e3: je 0x49a3ff */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 49a3e5: mov edx, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a3eb: shl edx, 4 */
	M32((DWORD)(m->edx + m->ebp*1 + 0x234300au)) = m->edi;	/* 49a3ee: mov dword ptr [edx + ebp + 0x234300a], edi */
	M32((DWORD)(m->ebp + 0x233cc5cu)) = 0x41700000u;	/* 49a3f5: mov dword ptr [ebp + 0x233cc5c], 0x41700000 */
L_49a3ff:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343106u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a3ff: cmp dword ptr [ebp + 0x2343106], edi */
	if (!m->zf) goto L_49a416;	/* 49a405: jne 0x49a416 */
L_49a407:
	m->ecx = m->ebp;	/* 49a407: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a40eu; native_call(m, 0x48e680u);	/* 49a409: call 0x48e680 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2343106u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a40e: cmp dword ptr [ebp + 0x2343106], edi */
	if (m->zf) goto L_49a407;	/* 49a414: je 0x49a407 */
L_49a416:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 49a416: xor esi, esi */
	m->edi = (DWORD)(m->ebp + 0x1eccb80u);	/* 49a418: lea edi, [ebp + 0x1eccb80] */
	m->ebx = (DWORD)(m->ebp + 0x234300au);	/* 49a41e: lea ebx, [ebp + 0x234300a] */
L_49a424:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0xfffffffcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a424: cmp dword ptr [ebx - 4], 1 */
	if (!m->zf) goto L_49a432;	/* 49a428: jne 0x49a432 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a42a: push esi */
	m->ecx = m->ebp;	/* 49a42b: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a432u; native_call(m, 0x48dbf0u);	/* 49a42d: call 0x48dbf0 */
L_49a432:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a432: cmp dword ptr [ebx], 1 */
	if (!m->zf) goto L_49a43f;	/* 49a435: jne 0x49a43f */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a437: push esi */
	m->ecx = m->ebp;	/* 49a438: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a43fu; native_call(m, 0x48e0f0u);	/* 49a43a: call 0x48e0f0 */
L_49a43f:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a43f: push esi */
	m->esp -= 4; M32(m->esp) = 0x49a445u; native_call(m, 0x4a8700u);	/* 49a440: call 0x4a8700 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a445: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a448: cmp eax, 1 */
	if (!m->zf) goto L_49a494;	/* 49a44b: jne 0x49a494 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2340c74u)));	/* 49a44d: fld dword ptr [ebp + 0x2340c74] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9468u)); FPOP();	/* 49a453: fcomp dword ptr [0x4a9468] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a459: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a45b: test ah, 0x41 */
	if (!m->zf) goto L_49a494;	/* 49a45e: jne 0x49a494 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 49a460: mov ecx, dword ptr [ebp + 0x234240d] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 49a466: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49a469: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49a46c: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49a46e: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 49a471: lea edx, [ecx + eax*8] */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*2 + 0x179d1feu)), b_ = 0x180u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a474: cmp dword ptr [ebp + edx*2 + 0x179d1fe], 0x180 */
	if (m->sf == m->of) goto L_49a494;	/* 49a47f: jge 0x49a494 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a481: push ecx */
	m->ecx = m->ebp;	/* 49a482: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a489u; native_call(m, 0x48e990u);	/* 49a484: call 0x48e990 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 49a489: fld dword ptr [ebp + 0x44] */
	ST(0) = -ST(0);	/* 49a48c: fchs  */
	MF((DWORD)(m->ebp + 0x2340c74u)) = (float)ST(0); FPOP();	/* 49a48e: fstp dword ptr [ebp + 0x2340c74] */
L_49a494:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a494: push esi */
	m->esp -= 4; M32(m->esp) = 0x49a49au; native_call(m, 0x4a8700u);	/* 49a495: call 0x4a8700 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a49a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a49d: cmp eax, 1 */
	if (!m->zf) goto L_49a500;	/* 49a4a0: jne 0x49a500 */
	m->ecx = m->eax;	/* 49a4a2: mov ecx, eax */
	m->eax = M32((DWORD)(m->edi + 0xfffffff8u));	/* 49a4a4: mov eax, dword ptr [edi - 8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a4a7: cmp eax, ecx */
	if (!m->zf) goto L_49a500;	/* 49a4a9: jne 0x49a500 */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 49a4ab: mov eax, dword ptr [edi] */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 49a4ad: mov edx, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a4b3: cmp eax, edx */
	if (!m->zf) goto L_49a500;	/* 49a4b5: jne 0x49a500 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2340c74u)));	/* 49a4b7: fld dword ptr [ebp + 0x2340c74] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9468u)); FPOP();	/* 49a4bd: fcomp dword ptr [0x4a9468] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a4c3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a4c5: test ah, 0x41 */
	if (m->zf) goto L_49a4ed;	/* 49a4c8: je 0x49a4ed */
	{ DWORD a_ = M32((DWORD)(m->edi + 0xdcu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a4ca: cmp dword ptr [edi + 0xdc], ecx */
	if (m->zf) goto L_49a4ed;	/* 49a4d0: je 0x49a4ed */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x424u)));	/* 49a4d2: fld dword ptr [edi + 0x424] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49a4d8: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a4de: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a4e0: test ah, 0x40 */
	if (!m->zf) goto L_49a4ed;	/* 49a4e3: jne 0x49a4ed */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x264u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a4e5: cmp dword ptr [edi + 0x264], ecx */
	if (!m->zf) goto L_49a500;	/* 49a4eb: jne 0x49a500 */
L_49a4ed:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a4ed: push esi */
	m->ecx = m->ebp;	/* 49a4ee: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a4f5u; native_call(m, 0x48e2c0u);	/* 49a4f0: call 0x48e2c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 49a4f5: fld dword ptr [ebp + 0x44] */
	ST(0) = -ST(0);	/* 49a4f8: fchs  */
	MF((DWORD)(m->ebp + 0x2340c74u)) = (float)ST(0); FPOP();	/* 49a4fa: fstp dword ptr [ebp + 0x2340c74] */
L_49a500:
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 49a500: inc esi */
	{ DWORD a_ = m->ebx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 49a501: add ebx, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49a504: add edi, 0x8888 */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a50a: cmp esi, 0x10 */
	if (m->sf != m->of) goto L_49a424;	/* 49a50d: jl 0x49a424 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2340c74u)));	/* 49a513: fld dword ptr [ebp + 0x2340c74] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49a519: fadd dword ptr [ebp + 0x44] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49a51c: xor ebx, ebx */
	m->edi = 0x1u;	/* 49a51e: mov edi, 1 */
	MF((DWORD)(m->ebp + 0x2340c74u)) = (float)ST(0); FPOP();	/* 49a523: fstp dword ptr [ebp + 0x2340c74] */
L_49a529:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x234239du)));	/* 49a529: fld dword ptr [ebp + 0x234239d] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49a52f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a535: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a537: test ah, 0x41 */
	if (!m->zf) goto L_49a670;	/* 49a53a: jne 0x49a670 */
	m->ecx = M32((DWORD)(0x4d05a4u));	/* 49a540: mov ecx, dword ptr [0x4d05a4] */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 49a546: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a54c: push ecx */
	m->ecx = m->esi;	/* 49a54d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49a554u; native_call(m, 0x49a554u + M32(0x49a550u));	/* 0x473780 unless the patch DLL retargets it */	/* 49a54f: call 0x473780 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a554: cmp dword ptr [ebp + 8], edi */
	if (!m->zf) goto L_49a5b1;	/* 49a557: jne 0x49a5b1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a559: cmp dword ptr [ebp + 4], ebx */
	if (!m->zf) goto L_49a5b1;	/* 49a55c: jne 0x49a5b1 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x23423b9u)));	/* 49a55e: fld dword ptr [ebp + 0x23423b9] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 49a564: fcomp dword ptr [0x4a942c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a56a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a56c: test ah, 0x41 */
	if (!m->zf) goto L_49a5a2;	/* 49a56f: jne 0x49a5a2 */
	M32((DWORD)(m->ebp + 0x23423b9u)) = m->ebx;	/* 49a571: mov dword ptr [ebp + 0x23423b9], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x23423b5u));	/* 49a577: mov eax, dword ptr [ebp + 0x23423b5] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49a57d: sub eax, ebx */
	if (m->zf) goto L_49a599;	/* 49a57f: je 0x49a599 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49a581: dec eax */
	if (m->zf) goto L_49a590;	/* 49a582: je 0x49a590 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49a584: dec eax */
	if (!m->zf) goto L_49a5b1;	/* 49a585: jne 0x49a5b1 */
	m->ecx = m->ebp;	/* 49a587: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a58eu; native_call(m, 0x463670u);	/* 49a589: call 0x463670 */
	goto L_49a5b1;	/* 49a58e: jmp 0x49a5b1 */
L_49a590:
	m->ecx = m->ebp;	/* 49a590: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a597u; native_call(m, 0x4636b0u);	/* 49a592: call 0x4636b0 */
	goto L_49a5b1;	/* 49a597: jmp 0x49a5b1 */
L_49a599:
	m->ecx = m->ebp;	/* 49a599: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a5a0u; native_call(m, 0x463690u);	/* 49a59b: call 0x463690 */
	goto L_49a5b1;	/* 49a5a0: jmp 0x49a5b1 */
L_49a5a2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x44u)));	/* 49a5a2: fld dword ptr [ebp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x23423b9u));	/* 49a5a5: fadd dword ptr [ebp + 0x23423b9] */
	MF((DWORD)(m->ebp + 0x23423b9u)) = (float)ST(0); FPOP();	/* 49a5ab: fstp dword ptr [ebp + 0x23423b9] */
L_49a5b1:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x234239du)));	/* 49a5b1: fld dword ptr [ebp + 0x234239d] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49a5b7: fsub dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x234239du)) = (float)ST(0);	/* 49a5ba: fst dword ptr [ebp + 0x234239d] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49a5c0: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49a5c6: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49a5c8: test ah, 1 */
	if (m->zf) goto L_49a670;	/* 49a5cb: je 0x49a670 */
	{ DWORD a_ = M32((DWORD)(0x76d410u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a5d1: cmp dword ptr [0x76d410], ebx */
	if (m->zf) goto L_49a5e5;	/* 49a5d7: je 0x49a5e5 */
	M32((DWORD)(m->ebp + 0x23432cfu)) = m->edi;	/* 49a5d9: mov dword ptr [ebp + 0x23432cf], edi */
	M32((DWORD)(m->ebp + 0x2340cf4u)) = m->ebx;	/* 49a5df: mov dword ptr [ebp + 0x2340cf4], ebx */
L_49a5e5:
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49a5e5: or eax, 0xffffffff */
	M32((DWORD)(m->ebp + 0x2342399u)) = m->ebx;	/* 49a5e8: mov dword ptr [ebp + 0x2342399], ebx */
	M32((DWORD)(m->ebp + 0x23423b5u)) = m->eax;	/* 49a5ee: mov dword ptr [ebp + 0x23423b5], eax */
	M32((DWORD)(m->ebp + 0x233c9fcu)) = m->ebx;	/* 49a5f4: mov dword ptr [ebp + 0x233c9fc], ebx */
	M32((DWORD)(m->ebp + 0x2340cf4u)) = m->ebx;	/* 49a5fa: mov dword ptr [ebp + 0x2340cf4], ebx */
	M32((DWORD)(m->ebp + 0x2340cf0u)) = m->ebx;	/* 49a600: mov dword ptr [ebp + 0x2340cf0], ebx */
	m->ecx = m->ebp;	/* 49a606: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x234239du)) = m->ebx;	/* 49a608: mov dword ptr [ebp + 0x234239d], ebx */
	M32((DWORD)(m->ebp + 0x23424f2u)) = m->eax;	/* 49a60e: mov dword ptr [ebp + 0x23424f2], eax */
	m->esp -= 4; M32(m->esp) = 0x49a619u; native_call(m, 0x487ed0u);	/* 49a614: call 0x487ed0 */
	m->ecx = m->esi;	/* 49a619: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49a620u; native_call(m, 0x45e1c0u);	/* 49a61b: call 0x45e1c0 */
	m->edx = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49a620: mov edx, dword ptr [ebp + 0x233cc10] */
	M32((DWORD)(m->ebp + m->edx*4 + 0x233cb20u)) = m->ebx;	/* 49a626: mov dword ptr [ebp + edx*4 + 0x233cb20], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49a62d: mov eax, dword ptr [ebp + 0x233cc10] */
	M32((DWORD)(m->ebp + m->eax*4 + 0x233cb48u)) = m->ebx;	/* 49a633: mov dword ptr [ebp + eax*4 + 0x233cb48], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 49a63a: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a63d: cmp eax, ebx */
	if (!m->zf) goto L_49a710;	/* 49a63f: jne 0x49a710 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a9u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a645: cmp dword ptr [ebp + 0x23423a9], edi */
	if (!m->zf) goto L_49a710;	/* 49a64b: jne 0x49a710 */
	{ DWORD a_ = M32((DWORD)(0x9dad94u)), b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a651: cmp dword ptr [0x9dad94], 0xe */
	if (!m->zf) goto L_49a710;	/* 49a658: jne 0x49a710 */
	M32((DWORD)(m->ebp + 0x233c9ecu)) = m->edi;	/* 49a65e: mov dword ptr [ebp + 0x233c9ec], edi */
	M32((DWORD)(m->ebp + 0x23423a1u)) = m->edi;	/* 49a664: mov dword ptr [ebp + 0x23423a1], edi */
	M32((DWORD)(m->ebp + 0x23423a5u)) = m->ebx;	/* 49a66a: mov dword ptr [ebp + 0x23423a5], ebx */
L_49a670:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x4u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a670: cmp dword ptr [ebp + 4], ebx */
	if (!m->zf) goto L_49abd1;	/* 49a673: jne 0x49abd1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342399u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a679: cmp dword ptr [ebp + 0x2342399], ebx */
	if (!m->zf) goto L_49abd1;	/* 49a67f: jne 0x49abd1 */
	m->ecx = M32((DWORD)(m->ebp + 0x23423adu));	/* 49a685: mov ecx, dword ptr [ebp + 0x23423ad] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a68b: cmp ecx, ebx */
	if (m->zf || m->sf != m->of) goto L_49aaf7;	/* 49a68d: jle 0x49aaf7 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a693: cmp dword ptr [ebp + 0x22e7184], edi */
	if (!m->zf) goto L_49aa4d;	/* 49a699: jne 0x49aa4d */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a69f: push ebx */
	m->ecx = m->ebp;	/* 49a6a0: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a6a7u; native_call(m, 0x463780u);	/* 49a6a2: call 0x463780 */
	m->eax = M32((DWORD)(m->ebp + m->eax*4 + 0x2221fb8u));	/* 49a6a7: mov eax, dword ptr [ebp + eax*4 + 0x2221fb8] */
	m->ecx = M32((DWORD)(m->ebp + 0x23423adu));	/* 49a6ae: mov ecx, dword ptr [ebp + 0x23423ad] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a6b4: cmp eax, ecx */
	if (m->sf == m->of) goto L_49a6d5;	/* 49a6b6: jge 0x49a6d5 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a6b8: push edi */
	m->ecx = m->ebp;	/* 49a6b9: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a6c0u; native_call(m, 0x463780u);	/* 49a6bb: call 0x463780 */
	m->ecx = M32((DWORD)(m->ebp + m->eax*4 + 0x2221fb8u));	/* 49a6c0: mov ecx, dword ptr [ebp + eax*4 + 0x2221fb8] */
	m->eax = M32((DWORD)(m->ebp + 0x23423adu));	/* 49a6c7: mov eax, dword ptr [ebp + 0x23423ad] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a6cd: cmp ecx, eax */
	if (m->sf != m->of) goto L_49aaf7;	/* 49a6cf: jl 0x49aaf7 */
L_49a6d5:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a6d5: push edi */
	m->ecx = m->ebp;	/* 49a6d6: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a6ddu; native_call(m, 0x463780u);	/* 49a6d8: call 0x463780 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a6dd: push ebx */
	m->ecx = m->ebp;	/* 49a6de: mov ecx, ebp */
	m->esi = m->eax;	/* 49a6e0: mov esi, eax */
	m->esp -= 4; M32(m->esp) = 0x49a6e7u; native_call(m, 0x463780u);	/* 49a6e2: call 0x463780 */
	m->edx = M32((DWORD)(m->ebp + m->eax*4 + 0x2221fb8u));	/* 49a6e7: mov edx, dword ptr [ebp + eax*4 + 0x2221fb8] */
	m->eax = M32((DWORD)(m->ebp + m->esi*4 + 0x2221fb8u));	/* 49a6ee: mov eax, dword ptr [ebp + esi*4 + 0x2221fb8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a6f5: cmp edx, eax */
	if (m->zf || m->sf != m->of) goto L_49a997;	/* 49a6f7: jle 0x49a997 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a6fd: push ebx */
	m->ecx = m->ebp;	/* 49a6fe: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a705u; native_call(m, 0x463780u);	/* 49a700: call 0x463780 */
	M32((DWORD)(m->ebp + 0x23423bdu)) = m->eax;	/* 49a705: mov dword ptr [ebp + 0x23423bd], eax */
	goto L_49a9d5;	/* 49a70b: jmp 0x49a9d5 */
L_49a710:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9f0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a710: cmp dword ptr [ebp + 0x233c9f0], edi */
	if (!m->zf) goto L_49a72a;	/* 49a716: jne 0x49a72a */
	m->eax = M32((DWORD)(0x4de72au));	/* 49a718: mov eax, dword ptr [0x4de72a] */
	m->ecx = m->ebp;	/* 49a71d: mov ecx, ebp */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49a71f: inc eax */
	M32((DWORD)(0x4de72au)) = m->eax;	/* 49a720: mov dword ptr [0x4de72a], eax */
	m->esp -= 4; M32(m->esp) = 0x49a72au; native_call(m, 0x49d150u);	/* 49a725: call 0x49d150 */
L_49a72a:
	m->ecx = m->ebp;	/* 49a72a: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a731u; native_call(m, 0x4620e0u);	/* 49a72c: call 0x4620e0 */
	{ DWORD v_ = 0x42700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a731: push 0x42700000 */
	m->ecx = m->ebp;	/* 49a736: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x234297au)) = 0xffffffffu;	/* 49a738: mov dword ptr [ebp + 0x234297a], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x49a747u; native_call(m, 0x4629c0u);	/* 49a742: call 0x4629c0 */
	m->ecx = m->ebp;	/* 49a747: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a74eu; native_call(m, 0x463480u);	/* 49a749: call 0x463480 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a74e: cmp dword ptr [ebp + 8], ebx */
	if (!m->zf) goto L_49a79d;	/* 49a751: jne 0x49a79d */
	m->ecx = m->ebp;	/* 49a753: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a75au; native_call(m, 0x4636d0u);	/* 49a755: call 0x4636d0 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 49a75a: push -1 */
	m->ecx = m->ebp;	/* 49a75c: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a763u; native_call(m, 0x4613a0u);	/* 49a75e: call 0x4613a0 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a9u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a763: cmp dword ptr [ebp + 0x23423a9], ebx */
	if (!m->zf) goto L_49a786;	/* 49a769: jne 0x49a786 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a76b: push ebx */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 49a76c: push 3 */
	m->ecx = m->ebp;	/* 49a76e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a775u; native_call(m, 0x49ca20u);	/* 49a770: call 0x49ca20 */
	m->edi = M32(m->esp); m->esp += 4;	/* 49a775: pop edi */
	M32((DWORD)(m->ebp + 0x23423a9u)) = m->ebx;	/* 49a776: mov dword ptr [ebp + 0x23423a9], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 49a77c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 49a77d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49a77e: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a77f: add esp, 0x2a0 */
	m->esp += 4 + 0; return;	/* 49a785: ret  */
L_49a786:
	M32((DWORD)(m->ebp + 0x23432cfu)) = m->edi;	/* 49a786: mov dword ptr [ebp + 0x23432cf], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 49a78c: pop edi */
	M32((DWORD)(m->ebp + 0x23423a9u)) = m->ebx;	/* 49a78d: mov dword ptr [ebp + 0x23423a9], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 49a793: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 49a794: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49a795: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a796: add esp, 0x2a0 */
	m->esp += 4 + 0; return;	/* 49a79c: ret  */
L_49a79d:
	{ DWORD a_ = M32((DWORD)(0x9da3e0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a79d: cmp dword ptr [0x9da3e0], ebx */
	if (!m->zf) goto L_49a7f1;	/* 49a7a3: jne 0x49a7f1 */
	m->ecx = (DWORD)(m->ebp + 0x22ee228u);	/* 49a7a5: lea ecx, [ebp + 0x22ee228] */
	M32((DWORD)(m->ebp + 0x22f0408u)) = m->ebx;	/* 49a7ab: mov dword ptr [ebp + 0x22f0408], ebx */
	M32((DWORD)(m->ebp + 0x22f040cu)) = m->ebx;	/* 49a7b1: mov dword ptr [ebp + 0x22f040c], ebx */
	m->edx = (DWORD)(m->ebp + 0x233ca04u);	/* 49a7b7: lea edx, [ebp + 0x233ca04] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 49a7bd: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 49a7bf: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 49a7c1: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 49a7c4: mov dword ptr [edx + 4], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 49a7c7: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 49a7ca: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->ebp + 0x22ee234u));	/* 49a7cd: mov edx, dword ptr [ebp + 0x22ee234] */
	M32((DWORD)(m->ebp + 0x233ca28u)) = m->edx;	/* 49a7d3: mov dword ptr [ebp + 0x233ca28], edx */
	m->eax = M32((DWORD)(m->ebp + 0x22ee238u));	/* 49a7d9: mov eax, dword ptr [ebp + 0x22ee238] */
	m->ecx = m->ebp;	/* 49a7df: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x233ca2cu)) = m->eax;	/* 49a7e1: mov dword ptr [ebp + 0x233ca2c], eax */
	m->esp -= 4; M32(m->esp) = 0x49a7ecu; native_call(m, 0x462850u);	/* 49a7e7: call 0x462850 */
	goto L_49a8aa;	/* 49a7ec: jmp 0x49a8aa */
L_49a7f1:
	m->ecx = M32((DWORD)(m->ebp + 0x1f1ca8u));	/* 49a7f1: mov ecx, dword ptr [ebp + 0x1f1ca8] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a7f7: cmp ecx, ebx */
	if (m->zf || m->sf != m->of) goto L_49a871;	/* 49a7f9: jle 0x49a871 */
	m->eax = M32((DWORD)(m->ebp + 0x1f1cacu));	/* 49a7fb: mov eax, dword ptr [ebp + 0x1f1cac] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49a801: inc eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49a802: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49a803: idiv ecx */
	M32((DWORD)(m->ebp + 0x1f1cacu)) = m->edx;	/* 49a805: mov dword ptr [ebp + 0x1f1cac], edx */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a80b: shl edx, 4 */
	m->ecx = M32((DWORD)(m->edx + m->ebp*1 + 0x1f1668u));	/* 49a80e: mov ecx, dword ptr [edx + ebp + 0x1f1668] */
	M32((DWORD)(0x9dad94u)) = m->ecx;	/* 49a815: mov dword ptr [0x9dad94], ecx */
	m->eax = M32((DWORD)(m->ebp + 0x1f1cacu));	/* 49a81b: mov eax, dword ptr [ebp + 0x1f1cac] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49a821: inc eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49a822: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x1f1ca8u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49a823: idiv dword ptr [ebp + 0x1f1ca8] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a829: shl edx, 4 */
	m->edx = M32((DWORD)(m->edx + m->ebp*1 + 0x1f1668u));	/* 49a82c: mov edx, dword ptr [edx + ebp + 0x1f1668] */
	M32((DWORD)(m->ebp + 0x1f1cb4u)) = m->edx;	/* 49a833: mov dword ptr [ebp + 0x1f1cb4], edx */
	m->eax = M32((DWORD)(m->ebp + 0x1f1cacu));	/* 49a839: mov eax, dword ptr [ebp + 0x1f1cac] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49a83f: inc eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 49a840: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)M32((DWORD)(m->ebp + 0x1f1ca8u)); m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 49a841: idiv dword ptr [ebp + 0x1f1ca8] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a847: shl edx, 4 */
	m->eax = M32((DWORD)(m->edx + m->ebp*1 + 0x1f166cu));	/* 49a84a: mov eax, dword ptr [edx + ebp + 0x1f166c] */
	M32((DWORD)(m->ebp + 0x1f1cb8u)) = m->eax;	/* 49a851: mov dword ptr [ebp + 0x1f1cb8], eax */
	m->ecx = M32((DWORD)(m->ebp + 0x1f1cacu));	/* 49a857: mov ecx, dword ptr [ebp + 0x1f1cac] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a85d: shl ecx, 4 */
	m->edx = M32((DWORD)(m->ecx + m->ebp*1 + 0x1f166cu));	/* 49a860: mov edx, dword ptr [ecx + ebp + 0x1f166c] */
	m->ecx = m->esi;	/* 49a867: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a869: push edx */
	m->esp -= 4; M32(m->esp) = 0x49a86fu; native_call(m, 0x4732f0u);	/* 49a86a: call 0x4732f0 */
	goto L_49a89e;	/* 49a86f: jmp 0x49a89e */
L_49a871:
	m->eax = M32((DWORD)(m->ebp + 0x1f1cb4u));	/* 49a871: mov eax, dword ptr [ebp + 0x1f1cb4] */
	M32((DWORD)(0x9dad94u)) = m->eax;	/* 49a877: mov dword ptr [0x9dad94], eax */
	M32((DWORD)(m->ebp + 0x1f1cb4u)) = 0xffffffffu;	/* 49a87c: mov dword ptr [ebp + 0x1f1cb4], 0xffffffff */
	m->ecx = M32((DWORD)(m->ebp + 0x1f1cb8u));	/* 49a886: mov ecx, dword ptr [ebp + 0x1f1cb8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a88c: push ecx */
	m->ecx = m->esi;	/* 49a88d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49a894u; native_call(m, 0x4732f0u);	/* 49a88f: call 0x4732f0 */
	M32((DWORD)(m->ebp + 0x1f1cb8u)) = 0xffffffffu;	/* 49a894: mov dword ptr [ebp + 0x1f1cb8], 0xffffffff */
L_49a89e:
	M32((DWORD)(m->ebp + 0x233cc20u)) = m->edi;	/* 49a89e: mov dword ptr [ebp + 0x233cc20], edi */
	M32((DWORD)(m->ebp + 0x233cc28u)) = m->ebx;	/* 49a8a4: mov dword ptr [ebp + 0x233cc28], ebx */
L_49a8aa:
	m->ecx = m->ebp;	/* 49a8aa: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a8b1u; native_call(m, 0x4616e0u);	/* 49a8ac: call 0x4616e0 */
	m->ecx = m->esi;	/* 49a8b1: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49a8b8u; native_call(m, 0x470cb0u);	/* 49a8b3: call 0x470cb0 */
	m->ecx = m->ebp;	/* 49a8b8: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a8bfu; native_call(m, 0x461730u);	/* 49a8ba: call 0x461730 */
	M32((DWORD)(m->ebp + 0x2342411u)) = m->ebx;	/* 49a8bf: mov dword ptr [ebp + 0x2342411], ebx */
	M32((DWORD)(m->ebp + 0x234243eu)) = 0xffffffffu;	/* 49a8c5: mov dword ptr [ebp + 0x234243e], 0xffffffff */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a8cf: cmp dword ptr [ebp + 0x22e7184], ebx */
	if (!m->zf) goto L_49a908;	/* 49a8d5: jne 0x49a908 */
	M32((DWORD)(m->ebp + 0x2342415u)) = m->ebx;	/* 49a8d7: mov dword ptr [ebp + 0x2342415], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a8dd: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a8e3: cmp eax, ebx */
	if (m->sf != m->of) goto L_49a8ff;	/* 49a8e5: jl 0x49a8ff */
	m->edx = m->eax;	/* 49a8e7: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a8e9: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a8ec: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a8ee: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a8f1: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a8f3: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a8f6: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb48u)) = m->ebx;	/* 49a8f8: mov dword ptr [ebp + edx*8 + 0x1eccb48], ebx */
L_49a8ff:
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 49a8ff: push -1 */
	m->ecx = m->ebp;	/* 49a901: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a908u; native_call(m, 0x4613a0u);	/* 49a903: call 0x4613a0 */
L_49a908:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a908: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49a90e: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a910: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a913: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a915: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a918: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a91a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a91d: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb60u)) = m->ebx;	/* 49a91f: mov dword ptr [ebp + ecx*8 + 0x1eccb60], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a926: mov eax, dword ptr [ebp + 0x234240d] */
	m->edx = m->eax;	/* 49a92c: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a92e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a931: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a933: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a936: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a938: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a93b: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb54u)) = m->ebx;	/* 49a93d: mov dword ptr [ebp + edx*8 + 0x1eccb54], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a944: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49a94a: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a94c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a94f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a951: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a954: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49a956: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49a959: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb64u)) = m->ebx;	/* 49a95b: mov dword ptr [ebp + ecx*8 + 0x1eccb64], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49a962: mov eax, dword ptr [ebp + 0x234240d] */
	m->edx = m->eax;	/* 49a968: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a96a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a96d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a96f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a972: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49a974: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49a977: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb58u)) = m->ebx;	/* 49a979: mov dword ptr [ebp + edx*8 + 0x1eccb58], ebx */
	M32((DWORD)(m->ebp + 0x2340d04u)) = m->edi;	/* 49a980: mov dword ptr [ebp + 0x2340d04], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 49a986: pop edi */
	M32((DWORD)(m->ebp + 0x23423a9u)) = m->ebx;	/* 49a987: mov dword ptr [ebp + 0x23423a9], ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 49a98d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 49a98e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49a98f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49a990: add esp, 0x2a0 */
	m->esp += 4 + 0; return;	/* 49a996: ret  */
L_49a997:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a997: push edi */
	m->ecx = m->ebp;	/* 49a998: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a99fu; native_call(m, 0x463780u);	/* 49a99a: call 0x463780 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49a99f: push ebx */
	m->ecx = m->ebp;	/* 49a9a0: mov ecx, ebp */
	m->esi = m->eax;	/* 49a9a2: mov esi, eax */
	m->esp -= 4; M32(m->esp) = 0x49a9a9u; native_call(m, 0x463780u);	/* 49a9a4: call 0x463780 */
	m->eax = M32((DWORD)(m->ebp + m->eax*4 + 0x2221fb8u));	/* 49a9a9: mov eax, dword ptr [ebp + eax*4 + 0x2221fb8] */
	m->ecx = M32((DWORD)(m->ebp + m->esi*4 + 0x2221fb8u));	/* 49a9b0: mov ecx, dword ptr [ebp + esi*4 + 0x2221fb8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49a9b7: cmp eax, ecx */
	if (m->sf == m->of) goto L_49a9cb;	/* 49a9b9: jge 0x49a9cb */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49a9bb: push edi */
	m->ecx = m->ebp;	/* 49a9bc: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a9c3u; native_call(m, 0x463780u);	/* 49a9be: call 0x463780 */
	M32((DWORD)(m->ebp + 0x23423bdu)) = m->eax;	/* 49a9c3: mov dword ptr [ebp + 0x23423bd], eax */
	goto L_49a9d5;	/* 49a9c9: jmp 0x49a9d5 */
L_49a9cb:
	M32((DWORD)(m->ebp + 0x23423bdu)) = 0xffffffffu;	/* 49a9cb: mov dword ptr [ebp + 0x23423bd], 0xffffffff */
L_49a9d5:
	M32((DWORD)(m->ebp + 0x22f0410u)) = m->edi;	/* 49a9d5: mov dword ptr [ebp + 0x22f0410], edi */
	M32((DWORD)(m->ebp + 0x2342399u)) = m->edi;	/* 49a9db: mov dword ptr [ebp + 0x2342399], edi */
	M32((DWORD)(m->ebp + 0x234239du)) = 0x41200000u;	/* 49a9e1: mov dword ptr [ebp + 0x234239d], 0x41200000 */
	M32((DWORD)(m->ebp + 0x233c9fcu)) = m->edi;	/* 49a9eb: mov dword ptr [ebp + 0x233c9fc], edi */
	m->esp -= 4; M32(m->esp) = 0x49a9f6u; native_call(m, 0x457310u);	/* 49a9f1: call 0x457310 */
	m->ecx = m->ebp;	/* 49a9f6: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49a9fdu; native_call(m, 0x462f90u);	/* 49a9f8: call 0x462f90 */
	M32((DWORD)(m->ebp + 0x23423b5u)) = m->ebx;	/* 49a9fd: mov dword ptr [ebp + 0x23423b5], ebx */
	M32((DWORD)(m->ebp + 0x23423b9u)) = m->ebx;	/* 49aa03: mov dword ptr [ebp + 0x23423b9], ebx */
	M32((DWORD)(0x9f67ecu)) = m->edi;	/* 49aa09: mov dword ptr [0x9f67ec], edi */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 49aa0f: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aa12: cmp eax, ebx */
	if (!m->zf) goto L_49aaf7;	/* 49aa14: jne 0x49aaf7 */
	m->ecx = M32((DWORD)(m->ebp + 0x234243eu));	/* 49aa1a: mov ecx, dword ptr [ebp + 0x234243e] */
	m->eax = M32((DWORD)(m->ebp + 0x23423adu));	/* 49aa20: mov eax, dword ptr [ebp + 0x23423ad] */
	m->edx = M32((DWORD)(m->ebp + m->ecx*4 + 0x2221fb8u));	/* 49aa26: mov edx, dword ptr [ebp + ecx*4 + 0x2221fb8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aa2d: cmp edx, eax */
	if (m->sf != m->of) goto L_49aaf7;	/* 49aa2f: jl 0x49aaf7 */
	m->eax = M32((DWORD)(0x9dad94u));	/* 49aa35: mov eax, dword ptr [0x9dad94] */
	m->ecx = M32((DWORD)(0x9f181cu));	/* 49aa3a: mov ecx, dword ptr [0x9f181c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aa40: cmp eax, ecx */
	if (!m->zf) goto L_49aaf7;	/* 49aa42: jne 0x49aaf7 */
	goto L_49aaf1;	/* 49aa48: jmp 0x49aaf1 */
L_49aa4d:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342976u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aa4d: cmp dword ptr [ebp + 0x2342976], ebx */
	if (m->zf || m->sf != m->of) goto L_49aaf7;	/* 49aa53: jle 0x49aaf7 */
	m->eax = M32((DWORD)(m->ebp + 0x23428f6u));	/* 49aa59: mov eax, dword ptr [ebp + 0x23428f6] */
	m->edx = m->eax;	/* 49aa5f: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49aa61: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49aa64: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49aa66: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49aa69: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49aa6b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49aa6e: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb54u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aa70: cmp dword ptr [ebp + edx*8 + 0x1eccb54], ecx */
	if (m->sf != m->of) goto L_49aaf7;	/* 49aa77: jl 0x49aaf7 */
	M32((DWORD)(m->ebp + 0x22f0410u)) = m->edi;	/* 49aa79: mov dword ptr [ebp + 0x22f0410], edi */
	M32((DWORD)(m->ebp + 0x2342399u)) = m->edi;	/* 49aa7f: mov dword ptr [ebp + 0x2342399], edi */
	M32((DWORD)(m->ebp + 0x234239du)) = 0x41200000u;	/* 49aa85: mov dword ptr [ebp + 0x234239d], 0x41200000 */
	M32((DWORD)(m->ebp + 0x233c9fcu)) = m->edi;	/* 49aa8f: mov dword ptr [ebp + 0x233c9fc], edi */
	m->esp -= 4; M32(m->esp) = 0x49aa9au; native_call(m, 0x457310u);	/* 49aa95: call 0x457310 */
	m->ecx = m->ebp;	/* 49aa9a: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49aaa1u; native_call(m, 0x462f90u);	/* 49aa9c: call 0x462f90 */
	M32((DWORD)(m->ebp + 0x23423b5u)) = m->ebx;	/* 49aaa1: mov dword ptr [ebp + 0x23423b5], ebx */
	M32((DWORD)(m->ebp + 0x23423b9u)) = m->ebx;	/* 49aaa7: mov dword ptr [ebp + 0x23423b9], ebx */
	M32((DWORD)(0x9f67ecu)) = m->edi;	/* 49aaad: mov dword ptr [0x9f67ec], edi */
	m->eax = M32((DWORD)(m->ebp + 0x8u));	/* 49aab3: mov eax, dword ptr [ebp + 8] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aab6: cmp eax, ebx */
	if (!m->zf) goto L_49aaf7;	/* 49aab8: jne 0x49aaf7 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49aaba: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49aac0: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49aac2: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49aac5: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49aac7: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49aaca: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49aacc: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49aacf: add ecx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x23423adu));	/* 49aad1: mov eax, dword ptr [ebp + 0x23423ad] */
	m->edx = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb54u));	/* 49aad7: mov edx, dword ptr [ebp + ecx*8 + 0x1eccb54] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aade: cmp edx, eax */
	if (m->sf != m->of) goto L_49aaf7;	/* 49aae0: jl 0x49aaf7 */
	m->eax = M32((DWORD)(0x9dad94u));	/* 49aae2: mov eax, dword ptr [0x9dad94] */
	m->ecx = M32((DWORD)(0x9f181cu));	/* 49aae7: mov ecx, dword ptr [0x9f181c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aaed: cmp eax, ecx */
	if (!m->zf) goto L_49aaf7;	/* 49aaef: jne 0x49aaf7 */
L_49aaf1:
	M32((DWORD)(m->ebp + 0x23423a9u)) = m->edi;	/* 49aaf1: mov dword ptr [ebp + 0x23423a9], edi */
L_49aaf7:
	m->eax = M32((DWORD)(m->ebp + 0x23423b1u));	/* 49aaf7: mov eax, dword ptr [ebp + 0x23423b1] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aafd: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_49abd1;	/* 49aaff: jle 0x49abd1 */
	m->ecx = m->eax;	/* 49ab05: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ab07: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ab0a: sub ecx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x22f0408u));	/* 49ab0c: mov eax, dword ptr [ebp + 0x22f0408] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ab12: shl ecx, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ab15: cmp eax, ecx */
	if (m->sf != m->of) goto L_49abd1;	/* 49ab17: jl 0x49abd1 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x22e7184u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ab1d: cmp dword ptr [ebp + 0x22e7184], edi */
	if (!m->zf) goto L_49ab97;	/* 49ab23: jne 0x49ab97 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49ab25: push edi */
	m->ecx = m->ebp;	/* 49ab26: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49ab2du; native_call(m, 0x463780u);	/* 49ab28: call 0x463780 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49ab2d: push ebx */
	m->ecx = m->ebp;	/* 49ab2e: mov ecx, ebp */
	m->esi = m->eax;	/* 49ab30: mov esi, eax */
	m->esp -= 4; M32(m->esp) = 0x49ab37u; native_call(m, 0x463780u);	/* 49ab32: call 0x463780 */
	m->edx = M32((DWORD)(m->ebp + m->eax*4 + 0x2221fb8u));	/* 49ab37: mov edx, dword ptr [ebp + eax*4 + 0x2221fb8] */
	m->eax = M32((DWORD)(m->ebp + m->esi*4 + 0x2221fb8u));	/* 49ab3e: mov eax, dword ptr [ebp + esi*4 + 0x2221fb8] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ab45: cmp edx, eax */
	if (m->zf || m->sf != m->of) goto L_49ab59;	/* 49ab47: jle 0x49ab59 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49ab49: push ebx */
	m->ecx = m->ebp;	/* 49ab4a: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49ab51u; native_call(m, 0x463780u);	/* 49ab4c: call 0x463780 */
	M32((DWORD)(m->ebp + 0x23423bdu)) = m->eax;	/* 49ab51: mov dword ptr [ebp + 0x23423bd], eax */
	goto L_49ab97;	/* 49ab57: jmp 0x49ab97 */
L_49ab59:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49ab59: push edi */
	m->ecx = m->ebp;	/* 49ab5a: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49ab61u; native_call(m, 0x463780u);	/* 49ab5c: call 0x463780 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49ab61: push ebx */
	m->ecx = m->ebp;	/* 49ab62: mov ecx, ebp */
	m->esi = m->eax;	/* 49ab64: mov esi, eax */
	m->esp -= 4; M32(m->esp) = 0x49ab6bu; native_call(m, 0x463780u);	/* 49ab66: call 0x463780 */
	m->eax = M32((DWORD)(m->ebp + m->eax*4 + 0x2221fb8u));	/* 49ab6b: mov eax, dword ptr [ebp + eax*4 + 0x2221fb8] */
	m->ecx = M32((DWORD)(m->ebp + m->esi*4 + 0x2221fb8u));	/* 49ab72: mov ecx, dword ptr [ebp + esi*4 + 0x2221fb8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ab79: cmp eax, ecx */
	if (m->sf == m->of) goto L_49ab8d;	/* 49ab7b: jge 0x49ab8d */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49ab7d: push edi */
	m->ecx = m->ebp;	/* 49ab7e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49ab85u; native_call(m, 0x463780u);	/* 49ab80: call 0x463780 */
	M32((DWORD)(m->ebp + 0x23423bdu)) = m->eax;	/* 49ab85: mov dword ptr [ebp + 0x23423bd], eax */
	goto L_49ab97;	/* 49ab8b: jmp 0x49ab97 */
L_49ab8d:
	M32((DWORD)(m->ebp + 0x23423bdu)) = 0xffffffffu;	/* 49ab8d: mov dword ptr [ebp + 0x23423bd], 0xffffffff */
L_49ab97:
	M32((DWORD)(m->ebp + 0x22f0410u)) = m->edi;	/* 49ab97: mov dword ptr [ebp + 0x22f0410], edi */
	M32((DWORD)(m->ebp + 0x2342399u)) = m->edi;	/* 49ab9d: mov dword ptr [ebp + 0x2342399], edi */
	M32((DWORD)(m->ebp + 0x234239du)) = 0x41200000u;	/* 49aba3: mov dword ptr [ebp + 0x234239d], 0x41200000 */
	M32((DWORD)(m->ebp + 0x233c9fcu)) = m->edi;	/* 49abad: mov dword ptr [ebp + 0x233c9fc], edi */
	m->esp -= 4; M32(m->esp) = 0x49abb8u; native_call(m, 0x457310u);	/* 49abb3: call 0x457310 */
	m->ecx = m->ebp;	/* 49abb8: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49abbfu; native_call(m, 0x462fd0u);	/* 49abba: call 0x462fd0 */
	M32((DWORD)(m->ebp + 0x23423b5u)) = m->edi;	/* 49abbf: mov dword ptr [ebp + 0x23423b5], edi */
	M32((DWORD)(m->ebp + 0x23423b9u)) = m->ebx;	/* 49abc5: mov dword ptr [ebp + 0x23423b9], ebx */
	M32((DWORD)(0x9f67ecu)) = m->edi;	/* 49abcb: mov dword ptr [0x9f67ec], edi */
L_49abd1:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a9u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49abd1: cmp dword ptr [ebp + 0x23423a9], edi */
	if (!m->zf) goto L_49abf3;	/* 49abd7: jne 0x49abf3 */
	m->ecx = M32((DWORD)(0x9dad94u));	/* 49abd9: mov ecx, dword ptr [0x9dad94] */
	m->eax = M32((DWORD)(0x9f181cu));	/* 49abdf: mov eax, dword ptr [0x9f181c] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49abe4: cmp ecx, eax */
	if (!m->zf) goto L_49abf3;	/* 49abe6: jne 0x49abf3 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49abe8: inc eax */
	M32((DWORD)(0x9f181cu)) = m->eax;	/* 49abe9: mov dword ptr [0x9f181c], eax */
	m->esp -= 4; M32(m->esp) = 0x49abf3u; native_call(m, 0x447010u);	/* 49abee: call 0x447010 */
L_49abf3:
	m->eax = M32((DWORD)(m->ebp + 0x233c9fcu));	/* 49abf3: mov eax, dword ptr [ebp + 0x233c9fc] */
	m->edi = 0x3f800000u;	/* 49abf9: mov edi, 0x3f800000 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49abfe: sub eax, ebx */
	if (m->zf) goto L_49b5cd;	/* 49ac00: je 0x49b5cd */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49ac06: dec eax */
	if (!m->zf) goto L_49c239;	/* 49ac07: jne 0x49c239 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342399u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ac0d: cmp dword ptr [ebp + 0x2342399], 1 */
	if (!m->zf) goto L_49acc9;	/* 49ac14: jne 0x49acc9 */
	m->eax = M32((DWORD)(m->ebp + 0x23423b1u));	/* 49ac1a: mov eax, dword ptr [ebp + 0x23423b1] */
	M32((DWORD)(m->ebp + 0x233cc10u)) = 0x9u;	/* 49ac20: mov dword ptr [ebp + 0x233cc10], 9 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ac2a: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_49ac42;	/* 49ac2c: jle 0x49ac42 */
	m->edx = m->eax;	/* 49ac2e: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ac30: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ac33: sub edx, eax */
	m->eax = M32((DWORD)(m->ebp + 0x22f0408u));	/* 49ac35: mov eax, dword ptr [ebp + 0x22f0408] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ac3b: shl edx, 2 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ac3e: cmp eax, edx */
	if (m->sf == m->of) goto L_49ac8e;	/* 49ac40: jge 0x49ac8e */
L_49ac42:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9418u)));	/* 49ac42: fld dword ptr [0x4a9418] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x234239du));	/* 49ac48: fsub dword ptr [ebp + 0x234239d] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu)); FPOP();	/* 49ac4e: fcomp dword ptr [0x4a93fc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49ac54: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49ac56: test ah, 1 */
	if (m->zf) goto L_49ac8e;	/* 49ac59: je 0x49ac8e */
	m->eax = M32((DWORD)(m->ebp + 0x2221fb0u));	/* 49ac5b: mov eax, dword ptr [ebp + 0x2221fb0] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ac61: cmp eax, ebx */
	if (m->sf != m->of) goto L_49ac8e;	/* 49ac63: jl 0x49ac8e */
	m->ecx = m->eax;	/* 49ac65: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ac67: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ac6a: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ac6c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ac6f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ac71: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ac74: add ecx, eax */
	m->eax = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccbbcu));	/* 49ac76: mov eax, dword ptr [ebp + ecx*8 + 0x1eccbbc] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ac7d: cmp eax, 2 */
	m->esi = (DWORD)(m->ebp + m->ecx*8 + 0x0u);	/* 49ac80: lea esi, [ebp + ecx*8] */
	if (!m->zf) goto L_49ac8e;	/* 49ac84: jne 0x49ac8e */
	{ DWORD a_ = m->esi, b_ = 0x1ecca70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 49ac86: add esi, 0x1ecca70 */
	goto L_49acf3;	/* 49ac8c: jmp 0x49acf3 */
L_49ac8e:
	m->ecx = m->ebp;	/* 49ac8e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49ac95u; native_call(m, 0x4625a0u);	/* 49ac90: call 0x4625a0 */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x14cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ac95: cmp dword ptr [eax + 0x14c], 1 */
	if (!m->zf) goto L_49aca9;	/* 49ac9c: jne 0x49aca9 */
	m->ecx = m->ebp;	/* 49ac9e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49aca5u; native_call(m, 0x4625a0u);	/* 49aca0: call 0x4625a0 */
	m->esi = m->eax;	/* 49aca5: mov esi, eax */
	goto L_49acf3;	/* 49aca7: jmp 0x49acf3 */
L_49aca9:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49aca9: mov eax, dword ptr [ebp + 0x234240d] */
	m->edx = m->eax;	/* 49acaf: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49acb1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49acb4: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49acb6: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49acb9: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49acbb: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49acbe: add edx, eax */
	m->esi = (DWORD)(m->ebp + m->edx*8 + 0x1ecca70u);	/* 49acc0: lea esi, [ebp + edx*8 + 0x1ecca70] */
	goto L_49acf3;	/* 49acc7: jmp 0x49acf3 */
L_49acc9:
	m->eax = M32((DWORD)(m->ebp + 0x23424eeu));	/* 49acc9: mov eax, dword ptr [ebp + 0x23424ee] */
	M32((DWORD)(m->ebp + 0x233cc10u)) = m->eax;	/* 49accf: mov dword ptr [ebp + 0x233cc10], eax */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49acd5: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49acdb: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49acdd: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ace0: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ace2: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ace5: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ace7: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49acea: add ecx, eax */
	m->esi = (DWORD)(m->ebp + m->ecx*8 + 0x1ecca70u);	/* 49acec: lea esi, [ebp + ecx*8 + 0x1ecca70] */
L_49acf3:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x14cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49acf3: cmp dword ptr [esi + 0x14c], 1 */
	if (m->zf) goto L_49af5d;	/* 49acfa: je 0x49af5d */
	m->eax = M32((DWORD)(m->esi + 0x4c0u));	/* 49ad00: mov eax, dword ptr [esi + 0x4c0] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49ad06: cmp eax, ebx */
	if (m->sf != m->of) goto L_49af5d;	/* 49ad08: jl 0x49af5d */
	m->edx = m->eax;	/* 49ad0e: mov edx, eax */
	m->edi = (DWORD)(m->esi + 0x4e0u);	/* 49ad10: lea edi, [esi + 0x4e0] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ad16: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ad19: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ad1b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ad1e: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49ad20: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49ad23: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*8 + 0x1eccbc4u)));	/* 49ad25: fld dword ptr [ebp + edx*8 + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 49ad2c: fsub dword ptr [edi] */
	m->eax = (DWORD)(m->ebp + m->edx*8 + 0x1eccbc4u);	/* 49ad2e: lea eax, [ebp + edx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49ad35: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 49ad39: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 49ad3c: fsub dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49ad3f: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49ad43: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 49ad46: fsub dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49ad49: mov ecx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49ad4d: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 49ad51: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 49ad55: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49ad59: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49ad5d: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49ad61: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49ad65: mov dword ptr [esp + 0x24], edx */
	m->esp -= 4; M32(m->esp) = 0x49ad6eu; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49ad69: call 0x467760 */
	ST(0) = ST(0); FPOP();	/* 49ad6e: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3e8u)));	/* 49ad70: fld dword ptr [esi + 0x3e8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94a8u));	/* 49ad76: fmul dword ptr [0x4a94a8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49ad7c: fld dword ptr [esp + 0x1c] */
	m->ebx = (DWORD)(m->ebp + 0x233ca04u);	/* 49ad80: lea ebx, [ebp + 0x233ca04] */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 49ad86: lea eax, [esp + 0x1c] */
	ST(0) = ST(0) * ST(1);	/* 49ad8a: fmul st(1) */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49ad8c: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49ad8d: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49ad8e: push edi */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49ad8f: lea ecx, [ebp + 0x1f36c8] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 49ad95: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 49ad99: fld dword ptr [esp + 0x2c] */
	ST(0) = ST(0) * ST(1);	/* 49ad9d: fmul st(1) */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49ad9f: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 49ada3: fld dword ptr [esp + 0x30] */
	ST(0) = ST(0) * ST(1);	/* 49ada7: fmul st(1) */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49ada9: fstp dword ptr [esp + 0x30] */
	ST(0) = ST(0); FPOP();	/* 49adad: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 49adaf: fld dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 49adb3: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 49adb5: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 49adb9: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 49adbd: fadd dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49adc0: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 49adc4: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 49adc8: fadd dword ptr [edi + 8] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49adcb: fstp dword ptr [esp + 0x30] */
	m->esp -= 4; M32(m->esp) = 0x49add4u; native_call(m, 0x471740u);	/* 49adcf: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49add4: test eax, eax */
	if (!m->zf) goto L_49adee;	/* 49add6: jne 0x49adee */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 49add8: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 49addc: mov eax, dword ptr [esp + 0x20] */
	m->ecx = m->ebx;	/* 49ade0: mov ecx, ebx */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 49ade2: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 49ade4: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 49ade8: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 49adeb: mov dword ptr [ecx + 8], edx */
L_49adee:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 49adee: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 49adf0: fsub dword ptr [edi] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49adf2: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 49adf6: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 49adf9: fsub dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49adfc: mov eax, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49ae00: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 49ae04: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 49ae07: fsub dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49ae0a: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49ae0e: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 49ae12: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 49ae16: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49ae1a: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49ae1e: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49ae22: mov dword ptr [esp + 0x24], edx */
	m->esp -= 4; M32(m->esp) = 0x49ae2bu; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49ae26: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa440u)); FPOP();	/* 49ae2b: fcomp dword ptr [0x4aa440] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49ae31: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49ae33: test ah, 0x41 */
	if (!m->zf) goto L_49ae7a;	/* 49ae36: jne 0x49ae7a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49ae38: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49ae3c: fmul dword ptr [0x4aa440] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 49ae42: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49ae46: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49ae4c: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 49ae50: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49ae54: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49ae5a: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 49ae5e: fld dword ptr [ebx] */
	ST(0) = ST(0) - ST(1);	/* 49ae60: fsub st(1) */
	MF((DWORD)(m->ebx + 0x0u)) = (float)ST(0); FPOP();	/* 49ae62: fstp dword ptr [ebx] */
	ST(0) = ST(0); FPOP();	/* 49ae64: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 49ae66: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 49ae69: fsub dword ptr [esp + 0x14] */
	MF((DWORD)(m->ebx + 0x4u)) = (float)ST(0); FPOP();	/* 49ae6d: fstp dword ptr [ebx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 49ae70: fld dword ptr [ebx + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 49ae73: fsub dword ptr [esp + 0x18] */
	MF((DWORD)(m->ebx + 0x8u)) = (float)ST(0); FPOP();	/* 49ae77: fstp dword ptr [ebx + 8] */
L_49ae7a:
	m->esi = M32((DWORD)(m->esi + 0x4c0u));	/* 49ae7a: mov esi, dword ptr [esi + 0x4c0] */
	m->ecx = (DWORD)(m->ebp + 0x233ca10u);	/* 49ae80: lea ecx, [ebp + 0x233ca10] */
	m->eax = m->esi;	/* 49ae86: mov eax, esi */
	m->edi = 0x3f800000u;	/* 49ae88: mov edi, 0x3f800000 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49ae8d: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49ae90: add eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49ae92: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49ae95: add eax, esi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49ae97: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49ae9a: add eax, esi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->eax*8 + 0x1eccbc4u)));	/* 49ae9c: fld dword ptr [ebp + eax*8 + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc14u));	/* 49aea3: fsub dword ptr [ebp + 0x233cc14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->eax*8 + 0x1eccbc8u)));	/* 49aea9: fld dword ptr [ebp + eax*8 + 0x1eccbc8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc18u));	/* 49aeb0: fsub dword ptr [ebp + 0x233cc18] */
	m->eax = (DWORD)(m->ebp + m->eax*8 + 0x1eccbc4u);	/* 49aeb6: lea eax, [ebp + eax*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49aebd: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49aec1: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc1cu));	/* 49aec4: fsub dword ptr [ebp + 0x233cc1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49aeca: fstp dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49aece: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 49aed4: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49aed8: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 49aede: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 49aee2: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49aee6: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 49aeec: fstp dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc14u));	/* 49aef0: fadd dword ptr [ebp + 0x233cc14] */
	MF((DWORD)(m->ebp + 0x233cc14u)) = (float)ST(0); FPOP();	/* 49aef6: fstp dword ptr [ebp + 0x233cc14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 49aefc: fld dword ptr [esp + 0x64] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc18u));	/* 49af00: fadd dword ptr [ebp + 0x233cc18] */
	MF((DWORD)(m->ebp + 0x233cc18u)) = (float)ST(0); FPOP();	/* 49af06: fstp dword ptr [ebp + 0x233cc18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 49af0c: fld dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc1cu));	/* 49af10: fadd dword ptr [ebp + 0x233cc1c] */
	MF((DWORD)(m->ebp + 0x233cc1cu)) = (float)ST(0); FPOP();	/* 49af16: fstp dword ptr [ebp + 0x233cc1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc14u)));	/* 49af1c: fld dword ptr [ebp + 0x233cc14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 49af22: fsub dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49af24: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc18u)));	/* 49af28: fld dword ptr [ebp + 0x233cc18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 49af2e: fsub dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 49af31: mov edx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49af35: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc1cu)));	/* 49af39: fld dword ptr [ebp + 0x233cc1c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 49af3f: fsub dword ptr [ebx + 8] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 49af42: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 49af46: mov dword ptr [ecx], edx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49af48: xor ebx, ebx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49af4a: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49af4e: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 49af52: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 49af55: mov dword ptr [ecx + 8], edx */
	goto L_49c239;	/* 49af58: jmp 0x49c239 */
L_49af5d:
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49af5d: mov eax, dword ptr [ebp + 0x233cc10] */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->eax*4 + 0x233cb98u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49af63: cmp dword ptr [ebp + eax*4 + 0x233cb98], ebx */
	if (!m->zf) goto L_49b4e9;	/* 49af6a: jne 0x49b4e9 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->eax*4 + 0x233cb20u)));	/* 49af70: fld dword ptr [ebp + eax*4 + 0x233cb20] */
	MF((DWORD)(m->ebp + 0x233ca28u)) = (float)ST(0);	/* 49af77: fst dword ptr [ebp + 0x233ca28] */
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49af7d: mov eax, dword ptr [ebp + 0x233cc10] */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->eax*4 + 0x233cbc0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49af83: cmp dword ptr [ebp + eax*4 + 0x233cbc0], ebx */
	if (!m->zf) goto L_49af9a;	/* 49af8a: jne 0x49af9a */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x160u));	/* 49af8c: fadd dword ptr [esi + 0x160] */
	MF((DWORD)(m->ebp + 0x233ca28u)) = (float)ST(0); FPOP();	/* 49af92: fstp dword ptr [ebp + 0x233ca28] */
	goto L_49af9c;	/* 49af98: jmp 0x49af9c */
L_49af9a:
	ST(0) = ST(0); FPOP();	/* 49af9a: fstp st(0) */
L_49af9c:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49af9c: fld dword ptr [ebp + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9728u)); FPOP();	/* 49afa2: fcomp dword ptr [0x4a9728] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49afa8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49afaa: test ah, 1 */
	if (m->zf) goto L_49afbb;	/* 49afad: je 0x49afbb */
	M32((DWORD)(m->ebp + 0x233ca28u)) = 0xc45e8000u;	/* 49afaf: mov dword ptr [ebp + 0x233ca28], 0xc45e8000 */
	goto L_49afd8;	/* 49afb9: jmp 0x49afd8 */
L_49afbb:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49afbb: fld dword ptr [ebp + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a972cu)); FPOP();	/* 49afc1: fcomp dword ptr [0x4a972c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49afc7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49afc9: test ah, 0x41 */
	if (!m->zf) goto L_49afd8;	/* 49afcc: jne 0x49afd8 */
	M32((DWORD)(m->ebp + 0x233ca28u)) = 0x445e8000u;	/* 49afce: mov dword ptr [ebp + 0x233ca28], 0x445e8000 */
L_49afd8:
	m->ecx = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49afd8: mov ecx, dword ptr [ebp + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->ecx*4 + 0x233cb48u)));	/* 49afde: fld dword ptr [ebp + ecx*4 + 0x233cb48] */
	MF((DWORD)(m->ebp + 0x233ca2cu)) = (float)ST(0);	/* 49afe5: fst dword ptr [ebp + 0x233ca2c] */
	m->edx = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49afeb: mov edx, dword ptr [ebp + 0x233cc10] */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*4 + 0x233cbe8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49aff1: cmp dword ptr [ebp + edx*4 + 0x233cbe8], ebx */
	if (!m->zf) goto L_49b008;	/* 49aff8: jne 0x49b008 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x164u));	/* 49affa: fadd dword ptr [esi + 0x164] */
	MF((DWORD)(m->ebp + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 49b000: fstp dword ptr [ebp + 0x233ca2c] */
	goto L_49b00a;	/* 49b006: jmp 0x49b00a */
L_49b008:
	ST(0) = ST(0); FPOP();	/* 49b008: fstp st(0) */
L_49b00a:
	m->eax = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49b00a: mov eax, dword ptr [ebp + 0x233cc10] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b010: cmp eax, 1 */
	if (!m->zf) goto L_49b2f3;	/* 49b013: jne 0x49b2f3 */
	m->ecx = M32((DWORD)(m->esi + 0x10cu));	/* 49b019: mov ecx, dword ptr [esi + 0x10c] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 49b01f: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49b022: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49b025: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49b027: lea eax, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 49b02a: lea eax, [ecx + eax*8] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49b02d: shl eax, 1 */
	m->ecx = M32((DWORD)(m->eax + m->ebp*1 + 0x1755544u));	/* 49b02f: mov ecx, dword ptr [eax + ebp + 0x1755544] */
	m->edx = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 49b036: lea edx, [ecx + ecx*8] */
	m->ecx = (DWORD)(m->ecx + m->edx*2 + 0x0u);	/* 49b039: lea ecx, [ecx + edx*2] */
	m->edx = M32((DWORD)(m->esi + 0x140u));	/* 49b03c: mov edx, dword ptr [esi + 0x140] */
	{ DWORD a_ = m->ecx, c_ = (0x8u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b042: shl ecx, 8 */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x1755550u);	/* 49b045: lea eax, [eax + edx*4 + 0x1755550] */
	m->edi = (DWORD)(m->ecx + m->ebp*1 + 0x15fff88u);	/* 49b04c: lea edi, [ecx + ebp + 0x15fff88] */
	m->ecx = M32((DWORD)(m->eax + m->ebp*1 + 0x0u));	/* 49b053: mov ecx, dword ptr [eax + ebp] */
	m->eax = m->ecx;	/* 49b056: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49b058: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49b05b: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49b05d: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49b060: sub eax, ecx */
	{ DWORD a_ = m->edx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b062: cmp edx, 4 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49b065: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49b068: lea ecx, [eax + eax*4] */
	m->ecx = (DWORD)(m->ebp + m->ecx*8 + 0x16c517cu);	/* 49b06b: lea ecx, [ebp + ecx*8 + 0x16c517c] */
	if (!m->zf) goto L_49b0ea;	/* 49b072: jne 0x49b0ea */
	m->eax = M32((DWORD)(m->esi + 0x49cu));	/* 49b074: mov eax, dword ptr [esi + 0x49c] */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49b07a: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->esi + 0x484u));	/* 49b07d: mov eax, dword ptr [esi + 0x484] */
	m->edi = M32((DWORD)(m->edi + m->eax*4 + 0x12d8u));	/* 49b083: mov edi, dword ptr [edi + eax*4 + 0x12d8] */
	m->ecx = (DWORD)(m->ecx + m->edx*4 + 0x16b4u);	/* 49b08a: lea ecx, [ecx + edx*4 + 0x16b4] */
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 49b091: lea eax, [edi + edi*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49b094: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->esi + 0x1568u));	/* 49b097: mov eax, dword ptr [esi + 0x1568] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x1cu)));	/* 49b09d: fld dword ptr [eax + edx*4 + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b0a1: fmul dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x2cu)));	/* 49b0a4: fld dword ptr [eax + edx*4 + 0x2c] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0xcu);	/* 49b0a8: lea eax, [eax + edx*4 + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 49b0ac: fmul dword ptr [ecx + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b0af: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 49b0b1: fld dword ptr [ecx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 49b0b3: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b0b5: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 49b0b7: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b0ba: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x14u)));	/* 49b0be: fld dword ptr [eax + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b0c1: fmul dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 49b0c4: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 49b0c7: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b0c9: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x24u)));	/* 49b0cb: fld dword ptr [eax + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 49b0ce: fmul dword ptr [ecx + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b0d1: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 49b0d3: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b0d6: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x18u)));	/* 49b0da: fld dword ptr [eax + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b0dd: fmul dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49b0e0: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 49b0e3: fmul dword ptr [ecx] */
	goto L_49b1d2;	/* 49b0e5: jmp 0x49b1d2 */
L_49b0ea:
	m->eax = M32((DWORD)(m->esi + 0x49cu));	/* 49b0ea: mov eax, dword ptr [esi + 0x49c] */
	{ DWORD a_ = m->edx, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b0f0: cmp edx, 5 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 49b0f3: lea edx, [eax + eax*2] */
	if (!m->zf) goto L_49b16a;	/* 49b0f6: jne 0x49b16a */
	m->eax = M32((DWORD)(m->esi + 0x484u));	/* 49b0f8: mov eax, dword ptr [esi + 0x484] */
	m->ecx = (DWORD)(m->ecx + m->edx*4 + 0x2d70u);	/* 49b0fe: lea ecx, [ecx + edx*4 + 0x2d70] */
	m->edi = M32((DWORD)(m->edi + m->eax*4 + 0x12e0u));	/* 49b105: mov edi, dword ptr [edi + eax*4 + 0x12e0] */
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 49b10c: lea eax, [edi + edi*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49b10f: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->esi + 0x1568u));	/* 49b112: mov eax, dword ptr [esi + 0x1568] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x2cu)));	/* 49b118: fld dword ptr [eax + edx*4 + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 49b11c: fmul dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x1cu)));	/* 49b11f: fld dword ptr [eax + edx*4 + 0x1c] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0xcu);	/* 49b123: lea eax, [eax + edx*4 + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b127: fmul dword ptr [ecx + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b12a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 49b12c: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 49b12e: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b130: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 49b132: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b135: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x24u)));	/* 49b139: fld dword ptr [eax + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 49b13c: fmul dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 49b13f: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 49b142: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b144: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x14u)));	/* 49b146: fld dword ptr [eax + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b149: fmul dword ptr [ecx + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b14c: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 49b14e: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b151: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x28u)));	/* 49b155: fld dword ptr [eax + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 49b158: fmul dword ptr [ecx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49b15b: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 49b15e: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b160: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x18u)));	/* 49b162: fld dword ptr [eax + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b165: fmul dword ptr [ecx + 4] */
	goto L_49b1da;	/* 49b168: jmp 0x49b1da */
L_49b16a:
	m->eax = M32((DWORD)(m->esi + 0x484u));	/* 49b16a: mov eax, dword ptr [esi + 0x484] */
	m->ecx = (DWORD)(m->ecx + m->edx*4 + 0x16b4u);	/* 49b170: lea ecx, [ecx + edx*4 + 0x16b4] */
	m->edi = M32((DWORD)(m->edi + m->eax*4 + 0x12d0u));	/* 49b177: mov edi, dword ptr [edi + eax*4 + 0x12d0] */
	m->eax = (DWORD)(m->edi + m->edi*4 + 0x0u);	/* 49b17e: lea eax, [edi + edi*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 49b181: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->esi + 0x1568u));	/* 49b184: mov eax, dword ptr [esi + 0x1568] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x1cu)));	/* 49b18a: fld dword ptr [eax + edx*4 + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b18e: fmul dword ptr [ecx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x2cu)));	/* 49b191: fld dword ptr [eax + edx*4 + 0x2c] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0xcu);	/* 49b195: lea eax, [eax + edx*4 + 0xc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 49b199: fmul dword ptr [ecx + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b19c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 49b19e: fld dword ptr [ecx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 49b1a0: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b1a2: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 49b1a4: fadd dword ptr [eax + 0x30] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b1a7: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 49b1ab: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 49b1ae: fmul dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x14u)));	/* 49b1b0: fld dword ptr [eax + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b1b3: fmul dword ptr [ecx + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b1b6: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x24u)));	/* 49b1b8: fld dword ptr [eax + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 49b1bb: fmul dword ptr [ecx + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b1be: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x34u));	/* 49b1c0: fadd dword ptr [eax + 0x34] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b1c3: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49b1c7: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 49b1ca: fmul dword ptr [ecx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x18u)));	/* 49b1cc: fld dword ptr [eax + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x4u));	/* 49b1cf: fmul dword ptr [ecx + 4] */
L_49b1d2:
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b1d2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x28u)));	/* 49b1d4: fld dword ptr [eax + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x8u));	/* 49b1d7: fmul dword ptr [ecx + 8] */
L_49b1da:
	ST(1) = ST(1) + ST(0); FPOP();	/* 49b1da: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x38u));	/* 49b1dc: fadd dword ptr [eax + 0x38] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49b1df: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3e8u)));	/* 49b1e3: fld dword ptr [esi + 0x3e8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94fcu));	/* 49b1e9: fmul dword ptr [0x4a94fc] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 49b1ef: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 49b1f7: mov dword ptr [esp + 0x34], 0 */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49b1ff: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49b203: fld dword ptr [ebp + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49b209: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b20e: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49b20f: push 1 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 49b211: lea ecx, [esp + 0x34] */
	m->esp -= 4; M32(m->esp) = 0x49b21au; native_call(m, 0x4677c0u);	/* 49b215: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 49b21a: fld dword ptr [ebp + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49b220: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b225: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49b226: push 2 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 49b228: lea ecx, [esp + 0x34] */
	m->esp -= 4; M32(m->esp) = 0x49b231u; native_call(m, 0x4677c0u);	/* 49b22c: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 49b231: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x154u));	/* 49b235: fadd dword ptr [esi + 0x154] */
	m->edx = (DWORD)(m->ebp + 0x233ca04u);	/* 49b23b: lea edx, [ebp + 0x233ca04] */
	m->edi = 0x3f800000u;	/* 49b241: mov edi, 0x3f800000 */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49b246: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 49b24a: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x158u));	/* 49b24e: fadd dword ptr [esi + 0x158] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49b254: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 49b258: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x15cu));	/* 49b25c: fadd dword ptr [esi + 0x15c] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 49b262: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 49b266: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 49b26a: fsub dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 49b26e: fld dword ptr [esp + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 49b272: fsub dword ptr [esp + 0x30] */
	m->ecx = M32((DWORD)(m->esi + 0x490u));	/* 49b276: mov ecx, dword ptr [esi + 0x490] */
	m->esi = (DWORD)(m->ebp + 0x233ca10u);	/* 49b27c: lea esi, [ebp + 0x233ca10] */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 49b282: mov dword ptr [esp + 0x5c], ecx */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 49b286: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 49b28a: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 49b28e: fsub dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 49b292: fstp dword ptr [esp + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 49b296: fmul dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 49b29a: fld dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 49b29e: fmul dword ptr [esp + 0x5c] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 49b2a2: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 49b2a6: fld dword ptr [esp + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 49b2aa: fmul dword ptr [esp + 0x5c] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49b2ae: fstp dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 49b2b2: fadd dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b2b6: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 49b2ba: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 49b2be: fadd dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49b2c2: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 49b2c6: mov dword ptr [edx], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b2c8: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 49b2cc: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 49b2d0: fadd dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49b2d4: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 49b2d8: mov dword ptr [edx + 4], ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49b2db: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49b2df: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 49b2e3: mov dword ptr [edx + 8], eax */
	M32((DWORD)(m->esi + 0x0u)) = m->ebx;	/* 49b2e6: mov dword ptr [esi], ebx */
	M32((DWORD)(m->esi + 0x4u)) = m->ebx;	/* 49b2e8: mov dword ptr [esi + 4], ebx */
	M32((DWORD)(m->esi + 0x8u)) = m->edi;	/* 49b2eb: mov dword ptr [esi + 8], edi */
	goto L_49c1d7;	/* 49b2ee: jmp 0x49c1d7 */
L_49b2f3:
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b2f3: cmp eax, 9 */
	if (!m->zf) goto L_49b312;	/* 49b2f6: jne 0x49b312 */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 49b2f8: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x0u;	/* 49b300: mov dword ptr [esp + 0x30], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 49b308: mov dword ptr [esp + 0x34], 0 */
	goto L_49b360;	/* 49b310: jmp 0x49b360 */
L_49b312:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x3e8u)));	/* 49b312: fld dword ptr [esi + 0x3e8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa478u));	/* 49b318: fmul dword ptr [0x4aa478] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 49b31e: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 49b326: mov dword ptr [esp + 0x34], 0 */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49b32e: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49b332: fld dword ptr [ebp + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49b338: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b33d: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49b33e: push 1 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 49b340: lea ecx, [esp + 0x34] */
	m->esp -= 4; M32(m->esp) = 0x49b349u; native_call(m, 0x4677c0u);	/* 49b344: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 49b349: fld dword ptr [ebp + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49b34f: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b354: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49b355: push 2 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 49b357: lea ecx, [esp + 0x34] */
	m->esp -= 4; M32(m->esp) = 0x49b360u; native_call(m, 0x4677c0u);	/* 49b35b: call 0x4677c0 */
L_49b360:
	m->ecx = M32((DWORD)(m->ebp + 0x233cc10u));	/* 49b360: mov ecx, dword ptr [ebp + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->ecx*4 + 0x233cb70u)));	/* 49b366: fld dword ptr [ebp + ecx*4 + 0x233cb70] */
	ST(0) = -ST(0);	/* 49b36d: fchs  */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49b36f: fsub dword ptr [0x4aa440] */
	M32((DWORD)(m->esp + 0x6cu)) = 0x0u;	/* 49b375: mov dword ptr [esp + 0x6c], 0 */
	M32((DWORD)(m->esp + 0x70u)) = 0x0u;	/* 49b37d: mov dword ptr [esp + 0x70], 0 */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 49b385: fstp dword ptr [esp + 0x74] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49b389: fld dword ptr [ebp + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49b38f: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b394: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49b395: push 1 */
	m->ecx = (DWORD)(m->esp + 0x74u);	/* 49b397: lea ecx, [esp + 0x74] */
	m->esp -= 4; M32(m->esp) = 0x49b3a0u; native_call(m, 0x4677c0u);	/* 49b39b: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 49b3a0: fld dword ptr [ebp + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49b3a6: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b3ab: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49b3ac: push 2 */
	m->ecx = (DWORD)(m->esp + 0x74u);	/* 49b3ae: lea ecx, [esp + 0x74] */
	m->esp -= 4; M32(m->esp) = 0x49b3b7u; native_call(m, 0x4677c0u);	/* 49b3b2: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 49b3b7: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x154u));	/* 49b3bb: fadd dword ptr [esi + 0x154] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49b3c1: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 49b3c5: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x158u));	/* 49b3c9: fadd dword ptr [esi + 0x158] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49b3cf: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 49b3d3: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x15cu));	/* 49b3d7: fadd dword ptr [esi + 0x15c] */
	m->esi = (DWORD)(m->ebp + 0x233ca04u);	/* 49b3dd: lea esi, [ebp + 0x233ca04] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49b3e3: push esi */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 49b3e4: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 49b3e8: fld dword ptr [esp + 0x70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 49b3ec: fadd dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b3f0: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 49b3f4: fld dword ptr [esp + 0x74] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 49b3f8: fadd dword ptr [esp + 0x34] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 49b3fc: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 49b400: mov dword ptr [esp + 0x20], edx */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 49b404: lea edx, [esp + 0x20] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49b408: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x78u)));	/* 49b40c: fld dword ptr [esp + 0x78] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x38u));	/* 49b410: fadd dword ptr [esp + 0x38] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49b414: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49b418: push edx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 49b419: mov dword ptr [esp + 0x28], eax */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 49b41d: lea eax, [esp + 0x34] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 49b421: fstp dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 49b425: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b429: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 49b42a: mov dword ptr [esp + 0x30], ecx */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49b42e: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x49b439u; native_call(m, 0x471740u);	/* 49b434: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49b439: test eax, eax */
	if (!m->zf) goto L_49b453;	/* 49b43b: jne 0x49b453 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 49b43d: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 49b441: mov eax, dword ptr [esp + 0x20] */
	m->ecx = m->esi;	/* 49b445: mov ecx, esi */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 49b447: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 49b449: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 49b44d: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 49b450: mov dword ptr [ecx + 8], edx */
L_49b453:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49b453: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 49b455: fsub dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b459: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 49b45d: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 49b460: fsub dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49b464: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49b468: mov dword ptr [esp + 0x1c], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b46c: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 49b470: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 49b473: fsub dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49b477: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 49b47b: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 49b47f: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49b483: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49b487: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49b48b: mov dword ptr [esp + 0x24], edx */
	m->esp -= 4; M32(m->esp) = 0x49b494u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49b48f: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa440u)); FPOP();	/* 49b494: fcomp dword ptr [0x4aa440] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49b49a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49b49c: test ah, 0x41 */
	if (!m->zf) goto L_49bba0;	/* 49b49f: jne 0x49bba0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49b4a5: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49b4a9: fmul dword ptr [0x4aa440] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 49b4af: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49b4b3: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 49b4b9: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 49b4bd: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49b4c1: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49b4c7: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49b4cb: fld dword ptr [esi] */
	ST(0) = ST(0) - ST(1);	/* 49b4cd: fsub st(1) */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 49b4cf: fstp dword ptr [esi] */
	ST(0) = ST(0); FPOP();	/* 49b4d1: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 49b4d3: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 49b4d6: fsub dword ptr [esp + 0x48] */
	MF((DWORD)(m->esi + 0x4u)) = (float)ST(0); FPOP();	/* 49b4da: fstp dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 49b4dd: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 49b4e0: fsub dword ptr [esp + 0x4c] */
	goto L_49bb9d;	/* 49b4e4: jmp 0x49bb9d */
L_49b4e9:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x154u)));	/* 49b4e9: fld dword ptr [esi + 0x154] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc14u));	/* 49b4ef: fsub dword ptr [ebp + 0x233cc14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x158u)));	/* 49b4f5: fld dword ptr [esi + 0x158] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc18u));	/* 49b4fb: fsub dword ptr [ebp + 0x233cc18] */
	m->ecx = (DWORD)(m->ebp + 0x233ca10u);	/* 49b501: lea ecx, [ebp + 0x233ca10] */
	m->eax = m->ecx;	/* 49b507: mov eax, ecx */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 49b509: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x15cu)));	/* 49b50d: fld dword ptr [esi + 0x15c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc1cu));	/* 49b513: fsub dword ptr [ebp + 0x233cc1c] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49b519: fstp dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49b51d: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 49b523: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49b527: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 49b52d: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 49b531: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49b535: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 49b53b: fstp dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc14u));	/* 49b53f: fadd dword ptr [ebp + 0x233cc14] */
	MF((DWORD)(m->ebp + 0x233cc14u)) = (float)ST(0); FPOP();	/* 49b545: fstp dword ptr [ebp + 0x233cc14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 49b54b: fld dword ptr [esp + 0x64] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc18u));	/* 49b54f: fadd dword ptr [ebp + 0x233cc18] */
	MF((DWORD)(m->ebp + 0x233cc18u)) = (float)ST(0); FPOP();	/* 49b555: fstp dword ptr [ebp + 0x233cc18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 49b55b: fld dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc1cu));	/* 49b55f: fadd dword ptr [ebp + 0x233cc1c] */
	MF((DWORD)(m->ebp + 0x233cc1cu)) = (float)ST(0); FPOP();	/* 49b565: fstp dword ptr [ebp + 0x233cc1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc14u)));	/* 49b56b: fld dword ptr [ebp + 0x233cc14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233ca04u));	/* 49b571: fsub dword ptr [ebp + 0x233ca04] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b577: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc18u)));	/* 49b57b: fld dword ptr [ebp + 0x233cc18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233ca08u));	/* 49b581: fsub dword ptr [ebp + 0x233ca08] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 49b587: mov edx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b58b: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc1cu)));	/* 49b58f: fld dword ptr [ebp + 0x233cc1c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233ca0cu));	/* 49b595: fsub dword ptr [ebp + 0x233ca0c] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 49b59b: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 49b59d: mov edx, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49b5a1: fstp dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 49b5a5: mov dword ptr [eax + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49b5a8: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 49b5ac: mov dword ptr [eax + 8], edx */
	m->esp -= 4; M32(m->esp) = 0x49b5b4u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49b5af: call 0x467760 */
	M32((DWORD)(m->ebp + 0x233ca1cu)) = m->ebx;	/* 49b5b4: mov dword ptr [ebp + 0x233ca1c], ebx */
	M32((DWORD)(m->ebp + 0x233ca20u)) = m->edi;	/* 49b5ba: mov dword ptr [ebp + 0x233ca20], edi */
	ST(0) = ST(0); FPOP();	/* 49b5c0: fstp st(0) */
	M32((DWORD)(m->ebp + 0x233ca24u)) = m->ebx;	/* 49b5c2: mov dword ptr [ebp + 0x233ca24], ebx */
	goto L_49c239;	/* 49b5c8: jmp 0x49c239 */
L_49b5cd:
	m->edx = M32((DWORD)(m->ebp + 0x23424f2u));	/* 49b5cd: mov edx, dword ptr [ebp + 0x23424f2] */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b5d3: cmp edx, ebx */
	if (m->sf != m->of) goto L_49c07d;	/* 49b5d5: jl 0x49c07d */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49b5db: mov eax, dword ptr [ebp + 0x2340c64] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b5e1: cmp eax, ebx */
	if (m->sf != m->of) goto L_49c07d;	/* 49b5e3: jl 0x49c07d */
	m->ecx = m->eax;	/* 49b5e9: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b5eb: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b5ee: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b5f0: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b5f3: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b5f5: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b5f8: add ecx, eax */
	m->eax = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccbbcu));	/* 49b5fa: mov eax, dword ptr [ebp + ecx*8 + 0x1eccbbc] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b601: cmp eax, 1 */
	m->ecx = (DWORD)(m->ebp + m->ecx*8 + 0x0u);	/* 49b604: lea ecx, [ebp + ecx*8] */
	if (m->zf) goto L_49b8c0;	/* 49b608: je 0x49b8c0 */
	m->eax = M32((DWORD)(m->ecx + 0x1eccf30u));	/* 49b60e: mov eax, dword ptr [ecx + 0x1eccf30] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b614: cmp eax, ebx */
	if (m->sf != m->of) goto L_49b8c0;	/* 49b616: jl 0x49b8c0 */
	m->edx = m->eax;	/* 49b61c: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b61e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b621: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b623: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b626: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b628: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b62b: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*8 + 0x1eccbc4u)));	/* 49b62d: fld dword ptr [ebp + edx*8 + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x1eccf50u));	/* 49b634: fsub dword ptr [ecx + 0x1eccf50] */
	m->eax = (DWORD)(m->ebp + m->edx*8 + 0x1eccbc4u);	/* 49b63a: lea eax, [ebp + edx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b641: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 49b645: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x1eccf54u));	/* 49b648: fsub dword ptr [ecx + 0x1eccf54] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b64e: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49b652: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ecx + 0x1eccf58u));	/* 49b655: fsub dword ptr [ecx + 0x1eccf58] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49b65b: mov ecx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49b65f: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 49b663: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 49b667: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49b66b: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49b66f: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49b673: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49b677: mov dword ptr [esp + 0x24], edx */
	m->esp -= 4; M32(m->esp) = 0x49b680u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49b67b: call 0x467760 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49b680: mov eax, dword ptr [ebp + 0x2340c64] */
	m->esi = (DWORD)(m->ebp + 0x233ca04u);	/* 49b686: lea esi, [ebp + 0x233ca04] */
	m->ecx = m->eax;	/* 49b68c: mov ecx, eax */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 49b68e: lea edx, [esp + 0x1c] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b692: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b695: add ecx, eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49b697: push esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b698: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b69b: add ecx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49b69d: push edx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b69e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b6a1: add ecx, eax */
	ST(0) = ST(0); FPOP();	/* 49b6a3: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->ecx*8 + 0x1ecce58u)));	/* 49b6a5: fld dword ptr [ebp + ecx*8 + 0x1ecce58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94a8u));	/* 49b6ac: fmul dword ptr [0x4a94a8] */
	m->eax = (DWORD)(m->ebp + m->ecx*8 + 0x0u);	/* 49b6b2: lea eax, [ebp + ecx*8] */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49b6b6: lea ecx, [ebp + 0x1f36c8] */
	{ DWORD a_ = m->eax, b_ = 0x1eccf50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49b6bc: add eax, 0x1eccf50 */
	{ long double t = ST(0); FPUSH(t); }	/* 49b6c1: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x24u));	/* 49b6c3: fmul dword ptr [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b6c7: push eax */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 49b6c8: fstp dword ptr [esp + 0x28] */
	{ long double t = ST(0); FPUSH(t); }	/* 49b6cc: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 49b6ce: fmul dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49b6d2: fstp dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 49b6d6: fmul dword ptr [esp + 0x30] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49b6da: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 49b6de: fld dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 49b6e2: fadd dword ptr [eax] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 49b6e4: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 49b6e8: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 49b6ec: fadd dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49b6ef: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 49b6f3: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 49b6f7: fadd dword ptr [eax + 8] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49b6fa: fstp dword ptr [esp + 0x30] */
	m->esp -= 4; M32(m->esp) = 0x49b703u; native_call(m, 0x471740u);	/* 49b6fe: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49b703: test eax, eax */
	if (!m->zf) goto L_49b71d;	/* 49b705: jne 0x49b71d */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 49b707: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 49b70b: mov edx, dword ptr [esp + 0x20] */
	m->eax = m->esi;	/* 49b70f: mov eax, esi */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 49b711: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 49b713: mov ecx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 49b717: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 49b71a: mov dword ptr [eax + 8], ecx */
L_49b71d:
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49b71d: mov eax, dword ptr [ebp + 0x2340c64] */
	m->edx = m->eax;	/* 49b723: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b725: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b728: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b72a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b72d: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49b72f: fld dword ptr [esi] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b731: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b734: add edx, eax */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + m->edx*8 + 0x1eccf50u));	/* 49b736: fsub dword ptr [ebp + edx*8 + 0x1eccf50] */
	m->eax = (DWORD)(m->ebp + m->edx*8 + 0x1eccf50u);	/* 49b73d: lea eax, [ebp + edx*8 + 0x1eccf50] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b744: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 49b748: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 49b74b: fsub dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b74e: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 49b752: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 49b755: fsub dword ptr [eax + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49b758: mov ecx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49b75c: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 49b760: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 49b764: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49b768: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49b76c: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49b770: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49b774: mov dword ptr [esp + 0x24], edx */
	m->esp -= 4; M32(m->esp) = 0x49b77du; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49b778: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa440u)); FPOP();	/* 49b77d: fcomp dword ptr [0x4aa440] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49b783: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49b785: test ah, 0x41 */
	if (!m->zf) goto L_49b7cc;	/* 49b788: jne 0x49b7cc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49b78a: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49b78e: fmul dword ptr [0x4aa440] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 49b794: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49b798: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 49b79e: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 49b7a2: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49b7a6: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49b7ac: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49b7b0: fld dword ptr [esi] */
	ST(0) = ST(0) - ST(1);	/* 49b7b2: fsub st(1) */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 49b7b4: fstp dword ptr [esi] */
	ST(0) = ST(0); FPOP();	/* 49b7b6: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 49b7b8: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 49b7bb: fsub dword ptr [esp + 0x48] */
	MF((DWORD)(m->esi + 0x4u)) = (float)ST(0); FPOP();	/* 49b7bf: fstp dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 49b7c2: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 49b7c5: fsub dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esi + 0x8u)) = (float)ST(0); FPOP();	/* 49b7c9: fstp dword ptr [esi + 8] */
L_49b7cc:
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49b7cc: mov eax, dword ptr [ebp + 0x2340c64] */
	m->ecx = m->eax;	/* 49b7d2: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b7d4: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b7d7: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b7d9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b7dc: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b7de: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b7e1: add ecx, eax */
	m->eax = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccf30u));	/* 49b7e3: mov eax, dword ptr [ebp + ecx*8 + 0x1eccf30] */
	m->edx = m->eax;	/* 49b7ea: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b7ec: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b7ef: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b7f1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b7f4: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b7f6: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b7f9: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*8 + 0x1eccbc4u)));	/* 49b7fb: fld dword ptr [ebp + edx*8 + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc14u));	/* 49b802: fsub dword ptr [ebp + 0x233cc14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*8 + 0x1eccbc8u)));	/* 49b808: fld dword ptr [ebp + edx*8 + 0x1eccbc8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc18u));	/* 49b80f: fsub dword ptr [ebp + 0x233cc18] */
	m->eax = (DWORD)(m->ebp + m->edx*8 + 0x1eccbc4u);	/* 49b815: lea eax, [ebp + edx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 49b81c: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49b820: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc1cu));	/* 49b823: fsub dword ptr [ebp + 0x233cc1c] */
	m->eax = (DWORD)(m->ebp + 0x233ca10u);	/* 49b829: lea eax, [ebp + 0x233ca10] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49b82f: fstp dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49b833: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 49b839: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49b83d: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x64u)) = (float)ST(0); FPOP();	/* 49b843: fstp dword ptr [esp + 0x64] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 49b847: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49b84b: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 49b851: fstp dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc14u));	/* 49b855: fadd dword ptr [ebp + 0x233cc14] */
	MF((DWORD)(m->ebp + 0x233cc14u)) = (float)ST(0); FPOP();	/* 49b85b: fstp dword ptr [ebp + 0x233cc14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 49b861: fld dword ptr [esp + 0x64] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc18u));	/* 49b865: fadd dword ptr [ebp + 0x233cc18] */
	MF((DWORD)(m->ebp + 0x233cc18u)) = (float)ST(0); FPOP();	/* 49b86b: fstp dword ptr [ebp + 0x233cc18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 49b871: fld dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc1cu));	/* 49b875: fadd dword ptr [ebp + 0x233cc1c] */
	MF((DWORD)(m->ebp + 0x233cc1cu)) = (float)ST(0); FPOP();	/* 49b87b: fstp dword ptr [ebp + 0x233cc1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc14u)));	/* 49b881: fld dword ptr [ebp + 0x233cc14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 49b887: fsub dword ptr [esi] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49b889: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc18u)));	/* 49b88d: fld dword ptr [ebp + 0x233cc18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 49b893: fsub dword ptr [esi + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 49b896: mov ecx, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49b89a: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc1cu)));	/* 49b89e: fld dword ptr [ebp + 0x233cc1c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 49b8a4: fsub dword ptr [esi + 8] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 49b8a7: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 49b8ab: mov dword ptr [eax], ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49b8ad: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 49b8b1: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 49b8b5: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 49b8b8: mov dword ptr [eax + 8], ecx */
	goto L_49c239;	/* 49b8bb: jmp 0x49c239 */
L_49b8c0:
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*4 + 0x233cb98u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b8c0: cmp dword ptr [ebp + edx*4 + 0x233cb98], ebx */
	if (!m->zf) goto L_49bbb3;	/* 49b8c7: jne 0x49bbb3 */
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b8cd: cmp edx, 1 */
	if (m->zf) goto L_49bbbc;	/* 49b8d0: je 0x49bbbc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*4 + 0x233cb20u)));	/* 49b8d6: fld dword ptr [ebp + edx*4 + 0x233cb20] */
	MF((DWORD)(m->ebp + 0x233ca28u)) = (float)ST(0);	/* 49b8dd: fst dword ptr [ebp + 0x233ca28] */
	m->edx = M32((DWORD)(m->ebp + 0x23424f2u));	/* 49b8e3: mov edx, dword ptr [ebp + 0x23424f2] */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->edx*4 + 0x233cbc0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b8e9: cmp dword ptr [ebp + edx*4 + 0x233cbc0], ebx */
	if (!m->zf) goto L_49b918;	/* 49b8f0: jne 0x49b918 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49b8f2: mov eax, dword ptr [ebp + 0x2340c64] */
	m->ecx = m->eax;	/* 49b8f8: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b8fa: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b8fd: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b8ff: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b902: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b904: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b907: add ecx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + m->ecx*8 + 0x1eccbd0u));	/* 49b909: fadd dword ptr [ebp + ecx*8 + 0x1eccbd0] */
	MF((DWORD)(m->ebp + 0x233ca28u)) = (float)ST(0); FPOP();	/* 49b910: fstp dword ptr [ebp + 0x233ca28] */
	goto L_49b91a;	/* 49b916: jmp 0x49b91a */
L_49b918:
	ST(0) = ST(0); FPOP();	/* 49b918: fstp st(0) */
L_49b91a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49b91a: fld dword ptr [ebp + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a972cu)); FPOP();	/* 49b920: fcomp dword ptr [0x4a972c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49b926: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49b928: test ah, 0x41 */
	if (!m->zf) goto L_49b937;	/* 49b92b: jne 0x49b937 */
	M32((DWORD)(m->ebp + 0x233ca28u)) = 0x445e8000u;	/* 49b92d: mov dword ptr [ebp + 0x233ca28], 0x445e8000 */
L_49b937:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49b937: fld dword ptr [ebp + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9728u)); FPOP();	/* 49b93d: fcomp dword ptr [0x4a9728] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49b943: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49b945: test ah, 1 */
	if (m->zf) goto L_49b954;	/* 49b948: je 0x49b954 */
	M32((DWORD)(m->ebp + 0x233ca28u)) = 0xc45e8000u;	/* 49b94a: mov dword ptr [ebp + 0x233ca28], 0xc45e8000 */
L_49b954:
	m->edx = M32((DWORD)(m->ebp + 0x23424f2u));	/* 49b954: mov edx, dword ptr [ebp + 0x23424f2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*4 + 0x233cb48u)));	/* 49b95a: fld dword ptr [ebp + edx*4 + 0x233cb48] */
	MF((DWORD)(m->ebp + 0x233ca2cu)) = (float)ST(0);	/* 49b961: fst dword ptr [ebp + 0x233ca2c] */
	m->eax = M32((DWORD)(m->ebp + 0x23424f2u));	/* 49b967: mov eax, dword ptr [ebp + 0x23424f2] */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->eax*4 + 0x233cbe8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49b96d: cmp dword ptr [ebp + eax*4 + 0x233cbe8], ebx */
	if (!m->zf) goto L_49b99c;	/* 49b974: jne 0x49b99c */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49b976: mov eax, dword ptr [ebp + 0x2340c64] */
	m->ecx = m->eax;	/* 49b97c: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b97e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b981: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b983: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b986: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49b988: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49b98b: add ecx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + m->ecx*8 + 0x1eccbd4u));	/* 49b98d: fadd dword ptr [ebp + ecx*8 + 0x1eccbd4] */
	MF((DWORD)(m->ebp + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 49b994: fstp dword ptr [ebp + 0x233ca2c] */
	goto L_49b99e;	/* 49b99a: jmp 0x49b99e */
L_49b99c:
	ST(0) = ST(0); FPOP();	/* 49b99c: fstp st(0) */
L_49b99e:
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49b99e: mov eax, dword ptr [ebp + 0x2340c64] */
	m->edx = m->eax;	/* 49b9a4: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b9a6: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b9a9: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b9ab: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b9ae: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49b9b0: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49b9b3: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*8 + 0x1ecce58u)));	/* 49b9b5: fld dword ptr [ebp + edx*8 + 0x1ecce58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa478u));	/* 49b9bc: fmul dword ptr [0x4aa478] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 49b9c2: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 49b9ca: mov dword ptr [esp + 0x34], 0 */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49b9d2: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49b9d6: fld dword ptr [ebp + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49b9dc: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b9e1: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49b9e2: push 1 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 49b9e4: lea ecx, [esp + 0x34] */
	m->esp -= 4; M32(m->esp) = 0x49b9edu; native_call(m, 0x4677c0u);	/* 49b9e8: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 49b9ed: fld dword ptr [ebp + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49b9f3: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49b9f8: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49b9f9: push 2 */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 49b9fb: lea ecx, [esp + 0x34] */
	m->esp -= 4; M32(m->esp) = 0x49ba04u; native_call(m, 0x4677c0u);	/* 49b9ff: call 0x4677c0 */
	m->eax = M32((DWORD)(m->ebp + 0x23424f2u));	/* 49ba04: mov eax, dword ptr [ebp + 0x23424f2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->eax*4 + 0x233cb70u)));	/* 49ba0a: fld dword ptr [ebp + eax*4 + 0x233cb70] */
	ST(0) = -ST(0);	/* 49ba11: fchs  */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49ba13: fsub dword ptr [0x4aa440] */
	M32((DWORD)(m->esp + 0x6cu)) = 0x0u;	/* 49ba19: mov dword ptr [esp + 0x6c], 0 */
	M32((DWORD)(m->esp + 0x70u)) = 0x0u;	/* 49ba21: mov dword ptr [esp + 0x70], 0 */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 49ba29: fstp dword ptr [esp + 0x74] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49ba2d: fld dword ptr [ebp + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49ba33: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49ba38: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49ba39: push 1 */
	m->ecx = (DWORD)(m->esp + 0x74u);	/* 49ba3b: lea ecx, [esp + 0x74] */
	m->esp -= 4; M32(m->esp) = 0x49ba44u; native_call(m, 0x4677c0u);	/* 49ba3f: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 49ba44: fld dword ptr [ebp + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49ba4a: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49ba4f: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49ba50: push 2 */
	m->ecx = (DWORD)(m->esp + 0x74u);	/* 49ba52: lea ecx, [esp + 0x74] */
	m->esp -= 4; M32(m->esp) = 0x49ba5bu; native_call(m, 0x4677c0u);	/* 49ba56: call 0x4677c0 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49ba5b: mov eax, dword ptr [ebp + 0x2340c64] */
	m->esi = (DWORD)(m->ebp + 0x233ca04u);	/* 49ba61: lea esi, [ebp + 0x233ca04] */
	m->ecx = m->eax;	/* 49ba67: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ba69: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ba6c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ba6e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ba71: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 49ba73: fld dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49ba77: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49ba7a: add ecx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + m->ecx*8 + 0x1eccbc4u));	/* 49ba7c: fadd dword ptr [ebp + ecx*8 + 0x1eccbc4] */
	m->eax = (DWORD)(m->ebp + m->ecx*8 + 0x1eccbc4u);	/* 49ba83: lea eax, [ebp + ecx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 49ba8a: fstp dword ptr [esp + 0x2c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 49ba8e: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 49ba92: fadd dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x30u)) = (float)ST(0); FPOP();	/* 49ba95: fstp dword ptr [esp + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 49ba99: fld dword ptr [esp + 0x34] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 49ba9d: fadd dword ptr [eax + 8] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 49baa0: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x6cu)));	/* 49baa4: fld dword ptr [esp + 0x6c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 49baa8: fadd dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49baac: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 49bab0: fld dword ptr [esp + 0x70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 49bab4: fadd dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 49bab8: mov edx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 49babc: mov dword ptr [esp + 0x1c], edx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49bac0: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 49bac4: fld dword ptr [esp + 0x74] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 49bac8: fadd dword ptr [esp + 0x34] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 49bacc: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 49bad0: mov dword ptr [esp + 0x20], eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49bad4: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 49bad8: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 49badc: mov dword ptr [esp + 0x24], ecx */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 49bae0: lea edx, [esp + 0x1c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49bae4: push esi */
	m->eax = (DWORD)(m->esp + 0x30u);	/* 49bae5: lea eax, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49bae9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49baea: push eax */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49baeb: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x49baf6u; native_call(m, 0x471740u);	/* 49baf1: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49baf6: test eax, eax */
	if (!m->zf) goto L_49bb10;	/* 49baf8: jne 0x49bb10 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 49bafa: mov edx, dword ptr [esp + 0x1c] */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 49bafe: mov eax, dword ptr [esp + 0x20] */
	m->ecx = m->esi;	/* 49bb02: mov ecx, esi */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 49bb04: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0x24u));	/* 49bb06: mov edx, dword ptr [esp + 0x24] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 49bb0a: mov dword ptr [ecx + 4], eax */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 49bb0d: mov dword ptr [ecx + 8], edx */
L_49bb10:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49bb10: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x2cu));	/* 49bb12: fsub dword ptr [esp + 0x2c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49bb16: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 49bb1a: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 49bb1d: fsub dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49bb21: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49bb25: mov dword ptr [esp + 0x1c], eax */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49bb29: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 49bb2d: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x34u));	/* 49bb30: fsub dword ptr [esp + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49bb34: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 49bb38: mov dword ptr [esp + 0x20], ecx */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 49bb3c: lea ecx, [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49bb40: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49bb44: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49bb48: mov dword ptr [esp + 0x24], edx */
	m->esp -= 4; M32(m->esp) = 0x49bb51u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49bb4c: call 0x467760 */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4aa440u)); FPOP();	/* 49bb51: fcomp dword ptr [0x4aa440] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49bb57: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49bb59: test ah, 0x41 */
	if (!m->zf) goto L_49bba0;	/* 49bb5c: jne 0x49bba0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49bb5e: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49bb62: fmul dword ptr [0x4aa440] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 49bb68: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49bb6c: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 49bb72: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 49bb76: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa440u));	/* 49bb7a: fmul dword ptr [0x4aa440] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49bb80: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49bb84: fld dword ptr [esi] */
	ST(0) = ST(0) - ST(1);	/* 49bb86: fsub st(1) */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 49bb88: fstp dword ptr [esi] */
	ST(0) = ST(0); FPOP();	/* 49bb8a: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 49bb8c: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 49bb8f: fsub dword ptr [esp + 0x48] */
	MF((DWORD)(m->esi + 0x4u)) = (float)ST(0); FPOP();	/* 49bb93: fstp dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 49bb96: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x4cu));	/* 49bb99: fsub dword ptr [esp + 0x4c] */
L_49bb9d:
	MF((DWORD)(m->esi + 0x8u)) = (float)ST(0); FPOP();	/* 49bb9d: fstp dword ptr [esi + 8] */
L_49bba0:
	m->esi = (DWORD)(m->ebp + 0x233ca10u);	/* 49bba0: lea esi, [ebp + 0x233ca10] */
	M32((DWORD)(m->esi + 0x0u)) = m->ebx;	/* 49bba6: mov dword ptr [esi], ebx */
	M32((DWORD)(m->esi + 0x4u)) = m->ebx;	/* 49bba8: mov dword ptr [esi + 4], ebx */
	M32((DWORD)(m->esi + 0x8u)) = m->edi;	/* 49bbab: mov dword ptr [esi + 8], edi */
	goto L_49c1d7;	/* 49bbae: jmp 0x49c1d7 */
L_49bbb3:
	{ DWORD a_ = m->edx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49bbb3: cmp edx, 1 */
	if (!m->zf) goto L_49bebe;	/* 49bbb6: jne 0x49bebe */
L_49bbbc:
	m->ebx = M32((DWORD)(m->ebp + 0x2221f90u));	/* 49bbbc: mov ebx, dword ptr [ebp + 0x2221f90] */
	{ DWORD a_ = m->edi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 49bbc2: or edi, 0xffffffff */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 49bbc5: xor edx, edx */
	M32((DWORD)(m->esp + 0x38u)) = 0x7f7fffffu;	/* 49bbc7: mov dword ptr [esp + 0x38], 0x7f7fffff */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49bbcf: test ebx, ebx */
	if (m->zf || m->sf != m->of) goto L_49bcfb;	/* 49bbd1: jle 0x49bcfb */
	m->esi = (DWORD)(m->ebp + 0x1eccbccu);	/* 49bbd7: lea esi, [ebp + 0x1eccbcc] */
L_49bbdd:
	{ DWORD a_ = M32((DWORD)(m->esi + 0xffffffacu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49bbdd: cmp dword ptr [esi - 0x54], 1 */
	if (!m->zf) goto L_49bc5a;	/* 49bbe1: jne 0x49bc5a */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->ebp + 0x2340c64u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49bbe3: cmp edx, dword ptr [ebp + 0x2340c64] */
	if (m->zf) goto L_49bc5a;	/* 49bbe9: je 0x49bc5a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccbc4u)));	/* 49bbeb: fld dword ptr [ecx + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0xfffffff8u));	/* 49bbf1: fsub dword ptr [esi - 8] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49bbf4: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccbc8u)));	/* 49bbf8: fld dword ptr [ecx + 0x1eccbc8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0xfffffffcu));	/* 49bbfe: fsub dword ptr [esi - 4] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49bc01: mov eax, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49bc05: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccbccu)));	/* 49bc09: fld dword ptr [ecx + 0x1eccbcc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 49bc0f: fsub dword ptr [esi] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49bc11: mov dword ptr [esp + 0x1c], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 49bc15: mov eax, dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 49bc19: mov dword ptr [esp + 0x20], eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49bc1d: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 49bc21: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 49bc25: fmul dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 49bc29: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 49bc2d: fmul dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49bc31: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 49bc35: mov dword ptr [esp + 0x24], eax */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49bc39: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 49bc3b: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 49bc3f: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 49bc43: faddp st(1) */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x38u));	/* 49bc45: fcom dword ptr [esp + 0x38] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49bc49: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49bc4b: test ah, 1 */
	if (m->zf) goto L_49bc58;	/* 49bc4e: je 0x49bc58 */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 49bc50: fstp dword ptr [esp + 0x38] */
	m->edi = m->edx;	/* 49bc54: mov edi, edx */
	goto L_49bc5a;	/* 49bc56: jmp 0x49bc5a */
L_49bc58:
	ST(0) = ST(0); FPOP();	/* 49bc58: fstp st(0) */
L_49bc5a:
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 49bc5a: inc edx */
	{ DWORD a_ = m->esi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 49bc5b: add esi, 0x8888 */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49bc61: cmp edx, ebx */
	if (m->sf != m->of) goto L_49bbdd;	/* 49bc63: jl 0x49bbdd */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49bc69: test edi, edi */
	if (m->sf != m->of) goto L_49bcfb;	/* 49bc6b: jl 0x49bcfb */
	m->edx = m->edi;	/* 49bc71: mov edx, edi */
	m->esi = (DWORD)(m->ebp + 0x233cc14u);	/* 49bc73: lea esi, [ebp + 0x233cc14] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49bc79: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49bc7c: add edx, edi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49bc7e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49bc81: add edx, edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccbc4u)));	/* 49bc83: fld dword ptr [ecx + 0x1eccbc4] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49bc89: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49bc8c: add edx, edi */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + m->edx*8 + 0x1eccbc4u));	/* 49bc8e: fadd dword ptr [ebp + edx*8 + 0x1eccbc4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*8 + 0x1eccbc8u)));	/* 49bc95: fld dword ptr [ebp + edx*8 + 0x1eccbc8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x1eccbc8u));	/* 49bc9c: fadd dword ptr [ecx + 0x1eccbc8] */
	m->eax = (DWORD)(m->ebp + m->edx*8 + 0x1eccbc4u);	/* 49bca2: lea eax, [ebp + edx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 49bca9: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49bcad: fld dword ptr [eax + 8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + 0x1eccbccu));	/* 49bcb0: fadd dword ptr [ecx + 0x1eccbcc] */
	m->eax = m->esi;	/* 49bcb6: mov eax, esi */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49bcb8: fstp dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49bcbc: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49bcc2: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 49bcc6: fld dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49bcca: fmul dword ptr [0x4a942c] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 49bcd0: mov ecx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 49bcd4: mov dword ptr [eax], ecx */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49bcd6: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 49bcda: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49bcde: fmul dword ptr [0x4a942c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 49bce4: mov edx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 49bce8: mov dword ptr [eax + 4], edx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49bceb: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 49bcef: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 49bcf3: mov dword ptr [eax + 8], ecx */
	goto L_49bd98;	/* 49bcf6: jmp 0x49bd98 */
L_49bcfb:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1ecce58u)));	/* 49bcfb: fld dword ptr [ecx + 0x1ecce58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 49bd01: fmul dword ptr [0x4a93d0] */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 49bd07: mov dword ptr [esp + 0x1c], 0 */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 49bd0f: mov dword ptr [esp + 0x20], 0 */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 49bd17: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccbd4u)));	/* 49bd1b: fld dword ptr [ecx + 0x1eccbd4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49bd21: call 0x49ec14 */
	m->edx = 0x64u;	/* 49bd26: mov edx, 0x64 */
	m->ecx = (DWORD)(m->esp + 0x1cu);	/* 49bd2b: lea ecx, [esp + 0x1c] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49bd2f: sub edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49bd31: push edx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49bd32: push 2 */
	m->esp -= 4; M32(m->esp) = 0x49bd39u; native_call(m, 0x4677c0u);	/* 49bd34: call 0x4677c0 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49bd39: mov eax, dword ptr [ebp + 0x2340c64] */
	m->esi = (DWORD)(m->ebp + 0x233cc14u);	/* 49bd3f: lea esi, [ebp + 0x233cc14] */
	m->ecx = m->eax;	/* 49bd45: mov ecx, eax */
	m->edx = m->esi;	/* 49bd47: mov edx, esi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bd49: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bd4c: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bd4e: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bd51: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49bd53: fld dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bd57: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bd5a: add ecx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + m->ecx*8 + 0x1eccbc4u));	/* 49bd5c: fadd dword ptr [ebp + ecx*8 + 0x1eccbc4] */
	m->eax = (DWORD)(m->ebp + m->ecx*8 + 0x1eccbc4u);	/* 49bd63: lea eax, [ebp + ecx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49bd6a: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 49bd6e: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 49bd72: fadd dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49bd75: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 49bd79: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 49bd7d: fadd dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49bd80: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49bd84: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 49bd88: mov dword ptr [edx], eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49bd8a: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49bd8e: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 49bd92: mov dword ptr [edx + 4], ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 49bd95: mov dword ptr [edx + 8], eax */
L_49bd98:
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49bd98: mov eax, dword ptr [ebp + 0x2340c64] */
	m->edi = (DWORD)(m->ebp + 0x233ca10u);	/* 49bd9e: lea edi, [ebp + 0x233ca10] */
	m->ecx = m->eax;	/* 49bda4: mov ecx, eax */
	m->ebx = m->edi;	/* 49bda6: mov ebx, edi */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bda8: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bdab: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bdad: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bdb0: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bdb2: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bdb5: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->ecx*8 + 0x1eccbc4u)));	/* 49bdb7: fld dword ptr [ebp + ecx*8 + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 49bdbe: fsub dword ptr [esi] */
	m->eax = (DWORD)(m->ebp + m->ecx*8 + 0x1eccbc4u);	/* 49bdc0: lea eax, [ebp + ecx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49bdc7: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 49bdcb: fld dword ptr [eax + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 49bdce: fsub dword ptr [esi + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49bdd1: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 49bdd5: fld dword ptr [eax + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 49bdd8: fsub dword ptr [esi + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49bddb: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49bddf: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->ebx + 0x0u)) = m->eax;	/* 49bde3: mov dword ptr [ebx], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 49bde5: mov dword ptr [esp + 0x20], ecx */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49bde9: fstp dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 49bded: mov edx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->ebx + 0x4u)) = m->ecx;	/* 49bdf1: mov dword ptr [ebx + 4], ecx */
	m->ecx = m->edi;	/* 49bdf4: mov ecx, edi */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 49bdf6: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 49bdfa: mov dword ptr [esp + 0x24], edx */
	M32((DWORD)(m->ebx + 0x8u)) = m->edx;	/* 49bdfe: mov dword ptr [ebx + 8], edx */
	m->esp -= 4; M32(m->esp) = 0x49be06u; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49be01: call 0x467760 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49be06: mov eax, dword ptr [ebp + 0x2340c64] */
	m->edx = m->eax;	/* 49be0c: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49be0e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49be11: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49be13: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49be16: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49be18: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49be1b: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*8 + 0x1ecce58u)));	/* 49be1d: fld dword ptr [ebp + edx*8 + 0x1ecce58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9534u));	/* 49be24: fmul dword ptr [0x4a9534] */
	{ long double t = ST(0); FPUSH(t); }	/* 49be2a: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 49be2c: fmul dword ptr [edi] */
	MF((DWORD)(m->edi + 0x0u)) = (float)ST(0); FPOP();	/* 49be2e: fstp dword ptr [edi] */
	{ long double t = ST(0); FPUSH(t); }	/* 49be30: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 49be32: fmul dword ptr [edi + 4] */
	MF((DWORD)(m->edi + 0x4u)) = (float)ST(0); FPOP();	/* 49be35: fstp dword ptr [edi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 49be38: fmul dword ptr [edi + 8] */
	MF((DWORD)(m->edi + 0x8u)) = (float)ST(0); FPOP();	/* 49be3b: fstp dword ptr [edi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49be3e: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 49be42: fadd dword ptr [edi] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 49be44: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 49be48: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 49be4c: fadd dword ptr [edi + 4] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 49be4f: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 49be53: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 49be57: fadd dword ptr [edi + 8] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 49be5a: fstp dword ptr [esp + 0x24] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4aa474u));	/* 49be5e: fsub dword ptr [0x4aa474] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa470u));	/* 49be64: fmul dword ptr [0x4aa470] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49be6a: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49be6f: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49be70: push 2 */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 49be72: lea ecx, [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x49be7bu; native_call(m, 0x4677c0u);	/* 49be76: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49be7b: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 49be7f: fadd dword ptr [esi] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49be81: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 49be85: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 49be89: fadd dword ptr [esi + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49be8c: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 49be90: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 49be94: fadd dword ptr [esi + 8] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49be97: fstp dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 49be9b: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 49be9f: mov edx, dword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->ebp + 0x233ca04u);	/* 49bea3: lea edi, [ebp + 0x233ca04] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49bea9: xor ebx, ebx */
	m->eax = m->edi;	/* 49beab: mov eax, edi */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 49bead: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 49beaf: mov ecx, dword ptr [esp + 0x18] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 49beb3: mov dword ptr [eax + 4], edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 49beb6: mov dword ptr [eax + 8], ecx */
	goto L_49c01e;	/* 49beb9: jmp 0x49c01e */
L_49bebe:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccbc4u)));	/* 49bebe: fld dword ptr [ecx + 0x1eccbc4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc14u));	/* 49bec4: fsub dword ptr [ebp + 0x233cc14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccbc8u)));	/* 49beca: fld dword ptr [ecx + 0x1eccbc8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x233cc18u));	/* 49bed0: fsub dword ptr [ebp + 0x233cc18] */
	m->esi = (DWORD)(m->ebp + 0x233cc14u);	/* 49bed6: lea esi, [ebp + 0x233cc14] */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 49bedc: lea edx, [esp + 0x1c] */
	m->edi = (DWORD)(m->ebp + 0x233ca04u);	/* 49bee0: lea edi, [ebp + 0x233ca04] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49bee6: push edx */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 49bee7: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x1eccbccu)));	/* 49beeb: fld dword ptr [ecx + 0x1eccbcc] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 49bef1: fsub dword ptr [esi + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49bef4: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 49bef5: push edi */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49bef6: lea ecx, [ebp + 0x1f36c8] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 49befc: fstp dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49bf00: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 49bf06: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49bf0a: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x70u)) = (float)ST(0); FPOP();	/* 49bf10: fstp dword ptr [esp + 0x70] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x58u)));	/* 49bf14: fld dword ptr [esp + 0x58] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 49bf18: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->esp + 0x74u)) = (float)ST(0); FPOP();	/* 49bf1e: fstp dword ptr [esp + 0x74] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 49bf22: fadd dword ptr [esi] */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 49bf24: fstp dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x70u)));	/* 49bf26: fld dword ptr [esp + 0x70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 49bf2a: fadd dword ptr [esi + 4] */
	MF((DWORD)(m->esi + 0x4u)) = (float)ST(0); FPOP();	/* 49bf2d: fstp dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x74u)));	/* 49bf30: fld dword ptr [esp + 0x74] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 49bf34: fadd dword ptr [esi + 8] */
	MF((DWORD)(m->esi + 0x8u)) = (float)ST(0); FPOP();	/* 49bf37: fstp dword ptr [esi + 8] */
	m->esp -= 4; M32(m->esp) = 0x49bf3fu; native_call(m, 0x471740u);	/* 49bf3a: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49bf3f: test eax, eax */
	if (m->zf) goto L_49c01e;	/* 49bf41: je 0x49c01e */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49bf47: mov eax, dword ptr [ebp + 0x2340c64] */
	m->ecx = m->eax;	/* 49bf4d: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bf4f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bf52: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bf54: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bf57: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bf59: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bf5c: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->ecx*8 + 0x1ecce58u)));	/* 49bf5e: fld dword ptr [ebp + ecx*8 + 0x1ecce58] */
	m->eax = (DWORD)(m->ebp + m->ecx*8 + 0x0u);	/* 49bf65: lea eax, [ebp + ecx*8] */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 49bf69: mov dword ptr [esp + 0x1c], 0 */
	ST(0) = -ST(0);	/* 49bf71: fchs  */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 49bf73: fstp dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 49bf77: mov dword ptr [esp + 0x20], 0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x1eccbd0u)));	/* 49bf7f: fld dword ptr [eax + 0x1eccbd0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49bf85: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49bf8a: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49bf8b: push 1 */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 49bf8d: lea ecx, [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x49bf96u; native_call(m, 0x4677c0u);	/* 49bf91: call 0x4677c0 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49bf96: mov eax, dword ptr [ebp + 0x2340c64] */
	m->edx = m->eax;	/* 49bf9c: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49bf9e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49bfa1: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49bfa3: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49bfa6: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49bfa8: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49bfab: add edx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + m->edx*8 + 0x1eccbd4u)));	/* 49bfad: fld dword ptr [ebp + edx*8 + 0x1eccbd4] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49bfb4: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49bfb9: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49bfba: push 2 */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 49bfbc: lea ecx, [esp + 0x24] */
	m->esp -= 4; M32(m->esp) = 0x49bfc5u; native_call(m, 0x4677c0u);	/* 49bfc0: call 0x4677c0 */
	m->eax = M32((DWORD)(m->ebp + 0x2340c64u));	/* 49bfc5: mov eax, dword ptr [ebp + 0x2340c64] */
	m->edx = m->edi;	/* 49bfcb: mov edx, edi */
	m->ecx = m->eax;	/* 49bfcd: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bfcf: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bfd2: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bfd4: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bfd7: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 49bfd9: fld dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49bfdd: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49bfe0: add ecx, eax */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + m->ecx*8 + 0x1eccbc4u));	/* 49bfe2: fadd dword ptr [ebp + ecx*8 + 0x1eccbc4] */
	m->eax = (DWORD)(m->ebp + m->ecx*8 + 0x1eccbc4u);	/* 49bfe9: lea eax, [ebp + ecx*8 + 0x1eccbc4] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49bff0: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 49bff4: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 49bff8: fadd dword ptr [eax + 4] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49bffb: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 49bfff: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 49c003: fadd dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49c006: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 49c00a: mov ecx, dword ptr [esp + 0x14] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 49c00e: mov dword ptr [edx], eax */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49c010: fstp dword ptr [esp + 0x18] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49c014: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x4u)) = m->ecx;	/* 49c018: mov dword ptr [edx + 4], ecx */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 49c01b: mov dword ptr [edx + 8], eax */
L_49c01e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49c01e: fld dword ptr [esi] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 49c020: fsub dword ptr [edi] */
	m->ecx = (DWORD)(m->ebp + 0x233ca10u);	/* 49c022: lea ecx, [ebp + 0x233ca10] */
	m->edx = m->ecx;	/* 49c028: mov edx, ecx */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 49c02a: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 49c02e: fld dword ptr [esi + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 49c031: fsub dword ptr [edi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 49c034: mov eax, dword ptr [esp + 0x10] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 49c038: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 49c03c: fld dword ptr [esi + 8] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 49c03f: fsub dword ptr [edi + 8] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 49c042: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 49c044: mov eax, dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 49c048: fstp dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 49c04c: mov dword ptr [edx + 4], eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 49c04f: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->edx + 0x8u)) = m->eax;	/* 49c053: mov dword ptr [edx + 8], eax */
	m->esp -= 4; M32(m->esp) = 0x49c05bu; { long double r_ = native_call_fp(m, 0x467760u); FPUSH(r_); }	/* 49c056: call 0x467760 */
	M32((DWORD)(m->ebp + 0x233ca1cu)) = m->ebx;	/* 49c05b: mov dword ptr [ebp + 0x233ca1c], ebx */
	M32((DWORD)(m->ebp + 0x233ca20u)) = 0x3f800000u;	/* 49c061: mov dword ptr [ebp + 0x233ca20], 0x3f800000 */
	ST(0) = ST(0); FPOP();	/* 49c06b: fstp st(0) */
	M32((DWORD)(m->ebp + 0x233ca24u)) = m->ebx;	/* 49c06d: mov dword ptr [ebp + 0x233ca24], ebx */
	m->edi = 0x3f800000u;	/* 49c073: mov edi, 0x3f800000 */
	goto L_49c239;	/* 49c078: jmp 0x49c239 */
L_49c07d:
	m->ecx = (DWORD)(m->esp + 0x160u);	/* 49c07d: lea ecx, [esp + 0x160] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c084: push ebx */
	m->edx = (DWORD)(m->esp + 0xc4u);	/* 49c085: lea edx, [esp + 0xc4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c08c: push ecx */
	m->eax = (DWORD)(m->esp + 0xb0u);	/* 49c08d: lea eax, [esp + 0xb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c094: push edx */
	m->ecx = (DWORD)(m->esp + 0xc0u);	/* 49c095: lea ecx, [esp + 0xc0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c09c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c09d: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c09e: push ebx */
	m->edx = (DWORD)(m->esp + 0x68u);	/* 49c09f: lea edx, [esp + 0x68] */
	m->esi = (DWORD)(m->ebp + 0x233ca04u);	/* 49c0a3: lea esi, [ebp + 0x233ca04] */
	{ DWORD v_ = 0x43fa0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c0a9: push 0x43fa0000 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c0ae: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49c0af: push esi */
	{ DWORD v_ = 0x43fa0000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c0b0: push 0x43fa0000 */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49c0b5: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x49c0c0u; native_call(m, 0x471400u);	/* 49c0bb: call 0x471400 */
	m->edx = M32((DWORD)(m->esp + 0xb4u));	/* 49c0c0: mov edx, dword ptr [esp + 0xb4] */
	m->ecx = m->esi;	/* 49c0c7: mov ecx, esi */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c0c9: cmp eax, 1 */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 49c0cc: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->esp + 0xb8u));	/* 49c0ce: mov edx, dword ptr [esp + 0xb8] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 49c0d5: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0xbcu));	/* 49c0d8: mov edx, dword ptr [esp + 0xbc] */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 49c0df: mov dword ptr [ecx + 8], edx */
	if (!m->zf) goto L_49c115;	/* 49c0e2: jne 0x49c115 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xa8u)));	/* 49c0e4: fld dword ptr [esp + 0xa8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 49c0eb: fadd dword ptr [esi] */
	MF((DWORD)(m->esi + 0x0u)) = (float)ST(0); FPOP();	/* 49c0ed: fstp dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xb0u)));	/* 49c0ef: fld dword ptr [esp + 0xb0] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233ca0cu));	/* 49c0f6: fadd dword ptr [ebp + 0x233ca0c] */
	MF((DWORD)(m->ebp + 0x233ca0cu)) = (float)ST(0); FPOP();	/* 49c0fc: fstp dword ptr [ebp + 0x233ca0c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xacu)));	/* 49c102: fld dword ptr [esp + 0xac] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x233ca08u));	/* 49c109: fadd dword ptr [ebp + 0x233ca08] */
	MF((DWORD)(m->ebp + 0x233ca08u)) = (float)ST(0); FPOP();	/* 49c10f: fstp dword ptr [ebp + 0x233ca08] */
L_49c115:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49c115: fld dword ptr [esi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0xbe2fccu)); FPOP();	/* 49c117: fcomp dword ptr [ebp + 0xbe2fcc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c11d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c11f: test ah, 1 */
	if (m->zf) goto L_49c12e;	/* 49c122: je 0x49c12e */
	m->eax = M32((DWORD)(m->ebp + 0xbe2fccu));	/* 49c124: mov eax, dword ptr [ebp + 0xbe2fcc] */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 49c12a: mov dword ptr [esi], eax */
	goto L_49c145;	/* 49c12c: jmp 0x49c145 */
L_49c12e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 49c12e: fld dword ptr [esi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0xbe2fd8u)); FPOP();	/* 49c130: fcomp dword ptr [ebp + 0xbe2fd8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c136: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c138: test ah, 0x41 */
	if (!m->zf) goto L_49c145;	/* 49c13b: jne 0x49c145 */
	m->ecx = M32((DWORD)(m->ebp + 0xbe2fd8u));	/* 49c13d: mov ecx, dword ptr [ebp + 0xbe2fd8] */
	M32((DWORD)(m->esi + 0x0u)) = m->ecx;	/* 49c143: mov dword ptr [esi], ecx */
L_49c145:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca08u)));	/* 49c145: fld dword ptr [ebp + 0x233ca08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0xbe2fd0u)); FPOP();	/* 49c14b: fcomp dword ptr [ebp + 0xbe2fd0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c151: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c153: test ah, 1 */
	if (m->zf) goto L_49c166;	/* 49c156: je 0x49c166 */
	m->edx = M32((DWORD)(m->ebp + 0xbe2fd0u));	/* 49c158: mov edx, dword ptr [ebp + 0xbe2fd0] */
	M32((DWORD)(m->ebp + 0x233ca08u)) = m->edx;	/* 49c15e: mov dword ptr [ebp + 0x233ca08], edx */
	goto L_49c185;	/* 49c164: jmp 0x49c185 */
L_49c166:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca08u)));	/* 49c166: fld dword ptr [ebp + 0x233ca08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0xbe2fdcu)); FPOP();	/* 49c16c: fcomp dword ptr [ebp + 0xbe2fdc] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c172: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c174: test ah, 0x41 */
	if (!m->zf) goto L_49c185;	/* 49c177: jne 0x49c185 */
	m->eax = M32((DWORD)(m->ebp + 0xbe2fdcu));	/* 49c179: mov eax, dword ptr [ebp + 0xbe2fdc] */
	M32((DWORD)(m->ebp + 0x233ca08u)) = m->eax;	/* 49c17f: mov dword ptr [ebp + 0x233ca08], eax */
L_49c185:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca0cu)));	/* 49c185: fld dword ptr [ebp + 0x233ca0c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0xbe2fd4u)); FPOP();	/* 49c18b: fcomp dword ptr [ebp + 0xbe2fd4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c191: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c193: test ah, 1 */
	if (m->zf) goto L_49c1a6;	/* 49c196: je 0x49c1a6 */
	m->ecx = M32((DWORD)(m->ebp + 0xbe2fd4u));	/* 49c198: mov ecx, dword ptr [ebp + 0xbe2fd4] */
	M32((DWORD)(m->ebp + 0x233ca0cu)) = m->ecx;	/* 49c19e: mov dword ptr [ebp + 0x233ca0c], ecx */
	goto L_49c1c5;	/* 49c1a4: jmp 0x49c1c5 */
L_49c1a6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca0cu)));	/* 49c1a6: fld dword ptr [ebp + 0x233ca0c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0xbe2fe0u)); FPOP();	/* 49c1ac: fcomp dword ptr [ebp + 0xbe2fe0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c1b2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c1b4: test ah, 0x41 */
	if (!m->zf) goto L_49c1c5;	/* 49c1b7: jne 0x49c1c5 */
	m->edx = M32((DWORD)(m->ebp + 0xbe2fe0u));	/* 49c1b9: mov edx, dword ptr [ebp + 0xbe2fe0] */
	M32((DWORD)(m->ebp + 0x233ca0cu)) = m->edx;	/* 49c1bf: mov dword ptr [ebp + 0x233ca0c], edx */
L_49c1c5:
	m->esi = (DWORD)(m->ebp + 0x233ca10u);	/* 49c1c5: lea esi, [ebp + 0x233ca10] */
	M32((DWORD)(m->esi + 0x0u)) = m->ebx;	/* 49c1cb: mov dword ptr [esi], ebx */
	M32((DWORD)(m->esi + 0x4u)) = m->ebx;	/* 49c1cd: mov dword ptr [esi + 4], ebx */
	M32((DWORD)(m->esi + 0x8u)) = 0xbf800000u;	/* 49c1d0: mov dword ptr [esi + 8], 0xbf800000 */
L_49c1d7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49c1d7: fld dword ptr [ebp + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49c1dd: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c1e2: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c1e3: push 1 */
	m->ecx = m->esi;	/* 49c1e5: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49c1ecu; native_call(m, 0x4677c0u);	/* 49c1e7: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 49c1ec: fld dword ptr [ebp + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49c1f2: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c1f7: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c1f8: push 2 */
	m->ecx = m->esi;	/* 49c1fa: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49c201u; native_call(m, 0x4677c0u);	/* 49c1fc: call 0x4677c0 */
	m->esi = (DWORD)(m->ebp + 0x233ca1cu);	/* 49c201: lea esi, [ebp + 0x233ca1c] */
	M32((DWORD)(m->esi + 0x0u)) = m->ebx;	/* 49c207: mov dword ptr [esi], ebx */
	M32((DWORD)(m->esi + 0x4u)) = m->edi;	/* 49c209: mov dword ptr [esi + 4], edi */
	M32((DWORD)(m->esi + 0x8u)) = m->ebx;	/* 49c20c: mov dword ptr [esi + 8], ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca28u)));	/* 49c20f: fld dword ptr [ebp + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49c215: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c21a: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c21b: push 1 */
	m->ecx = m->esi;	/* 49c21d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49c224u; native_call(m, 0x4677c0u);	/* 49c21f: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233ca2cu)));	/* 49c224: fld dword ptr [ebp + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49c22a: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c22f: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c230: push 2 */
	m->ecx = m->esi;	/* 49c232: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49c239u; native_call(m, 0x4677c0u);	/* 49c234: call 0x4677c0 */
L_49c239:
	m->eax = M32((DWORD)(m->ebp + 0x44u));	/* 49c239: mov eax, dword ptr [ebp + 0x44] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c23c: push eax */
	m->esp -= 4; M32(m->esp) = 0x49c242u; { long double r_ = native_call_fp(m, 0x468700u); FPUSH(r_); }	/* 49c23d: call 0x468700 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c242: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 49c243: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x49c24bu; { long double r_ = native_call_fp(m, 0x4686f0u); FPUSH(r_); }	/* 49c246: call 0x4686f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c24b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 49c24c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x49c254u; native_call(m, 0x4685c0u);	/* 49c24f: call 0x4685c0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c254: push eax */
	m->esp -= 4; M32(m->esp) = 0x49c25au; native_call(m, 0x4685b0u);	/* 49c255: call 0x4685b0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c25a: push eax */
	m->esp -= 4; M32(m->esp) = 0x49c260u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 49c25b: call 0x4686d0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c260: push ecx */
	m->ecx = (DWORD)(m->ebp + 0x233ca1cu);	/* 49c261: lea ecx, [ebp + 0x233ca1c] */
	m->edx = (DWORD)(m->ebp + 0x233ca10u);	/* 49c267: lea edx, [ebp + 0x233ca10] */
	m->eax = (DWORD)(m->ebp + 0x233ca04u);	/* 49c26d: lea eax, [ebp + 0x233ca04] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 49c273: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c276: push ecx */
	m->esi = (DWORD)(m->ebp + 0x1f36c8u);	/* 49c277: lea esi, [ebp + 0x1f36c8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c27d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c27e: push eax */
	m->ecx = m->esi;	/* 49c27f: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49c286u; native_call(m, 0x4729b0u);	/* 49c281: call 0x4729b0 */
	m->ecx = M32((DWORD)(m->esi + 0xa08u));	/* 49c286: mov ecx, dword ptr [esi + 0xa08] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c28c: push ecx */
	m->ecx = m->esi;	/* 49c28d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x49c294u; native_call(m, 0x4722e0u);	/* 49c28f: call 0x4722e0 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x234240du)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c294: cmp dword ptr [ebp + 0x234240d], ebx */
	if (m->sf != m->of) goto L_49c50e;	/* 49c29a: jl 0x49c50e */
	m->eax = M32((DWORD)(m->ebp + 0x2340d35u));	/* 49c2a0: mov eax, dword ptr [ebp + 0x2340d35] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49c2a6: sub eax, ebx */
	if (m->zf) goto L_49c490;	/* 49c2a8: je 0x49c490 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49c2ae: dec eax */
	if (m->zf) goto L_49c390;	/* 49c2af: je 0x49c390 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49c2b5: dec eax */
	if (!m->zf) goto L_49c50e;	/* 49c2b6: jne 0x49c50e */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c2bc: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_49c50e;	/* 49c2c2: jne 0x49c50e */
	M32((DWORD)(m->ebp + 0x2340d35u)) = m->ebx;	/* 49c2c8: mov dword ptr [ebp + 0x2340d35], ebx */
	m->esp -= 4; M32(m->esp) = 0x49c2d3u; native_call(m, 0x44ace0u);	/* 49c2ce: call 0x44ace0 */
	m->edi = 0x9f63e4u;	/* 49c2d3: mov edi, 0x9f63e4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c2d8: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49c2db: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 49c2dd: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 49c2df: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 49c2e1: dec ecx */
	if (m->zf) goto L_49c368;	/* 49c2e2: je 0x49c368 */
	m->edx = (DWORD)(m->esp + 0x1b0u);	/* 49c2e8: lea edx, [esp + 0x1b0] */
	m->ecx = m->ebp;	/* 49c2ef: mov ecx, ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c2f1: push edx */
	{ DWORD v_ = 0x9f63e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c2f2: push 0x9f63e4 */
	m->esp -= 4; M32(m->esp) = 0x49c2fcu; native_call(m, 0x462740u);	/* 49c2f7: call 0x462740 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49c2fc: sub eax, ebx */
	if (m->zf) goto L_49c305;	/* 49c2fe: je 0x49c305 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49c300: dec eax */
	if (m->zf) goto L_49c32e;	/* 49c301: je 0x49c32e */
	goto L_49c368;	/* 49c303: jmp 0x49c368 */
L_49c305:
	m->edi = 0x9f63e4u;	/* 49c305: mov edi, 0x9f63e4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c30a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49c30d: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x1b0u);	/* 49c30f: lea edx, [esp + 0x1b0] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 49c316: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 49c318: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49c31a: sub edi, ecx */
	m->eax = m->ecx;	/* 49c31c: mov eax, ecx */
	m->esi = m->edi;	/* 49c31e: mov esi, edi */
	m->edi = m->edx;	/* 49c320: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c322: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 49c325: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 49c327: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c329: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 49c32c: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_49c32e:
	m->ecx = M32((DWORD)(m->ebp + 0x234243eu));	/* 49c32e: mov ecx, dword ptr [ebp + 0x234243e] */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c334: mov eax, dword ptr [ebp + 0x234240d] */
	m->edx = (DWORD)(m->esp + 0x1b0u);	/* 49c33a: lea edx, [esp + 0x1b0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c341: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c342: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c343: push eax */
	m->ecx = m->ebp;	/* 49c344: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c34bu; native_call(m, 0x462c30u);	/* 49c346: call 0x462c30 */
	m->ecx = M32((DWORD)(m->ebp + 0x234243eu));	/* 49c34b: mov ecx, dword ptr [ebp + 0x234243e] */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c351: mov eax, dword ptr [ebp + 0x234240d] */
	m->edx = (DWORD)(m->esp + 0x1b0u);	/* 49c357: lea edx, [esp + 0x1b0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c35e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c35f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c360: push eax */
	m->ecx = m->ebp;	/* 49c361: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c368u; native_call(m, 0x463550u);	/* 49c363: call 0x463550 */
L_49c368:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c368: mov eax, dword ptr [ebp + 0x234240d] */
	m->edi = 0x3f800000u;	/* 49c36e: mov edi, 0x3f800000 */
	m->ecx = m->eax;	/* 49c373: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c375: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c378: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c37a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c37d: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c37f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c382: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1ecce5cu)) = m->ebx;	/* 49c384: mov dword ptr [ebp + ecx*8 + 0x1ecce5c], ebx */
	goto L_49c50e;	/* 49c38b: jmp 0x49c50e */
L_49c390:
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c390: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_49c50e;	/* 49c396: jne 0x49c50e */
	M32((DWORD)(m->ebp + 0x2340d35u)) = m->ebx;	/* 49c39c: mov dword ptr [ebp + 0x2340d35], ebx */
	m->esp -= 4; M32(m->esp) = 0x49c3a7u; native_call(m, 0x44ace0u);	/* 49c3a2: call 0x44ace0 */
	m->edi = 0x9f63e4u;	/* 49c3a7: mov edi, 0x9f63e4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c3ac: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49c3af: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 49c3b1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 49c3b3: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 49c3b5: dec ecx */
	if (m->zf) goto L_49c46b;	/* 49c3b6: je 0x49c46b */
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 49c3bc: mov edx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = 0x9f63e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c3c2: push 0x9f63e4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c3c7: push edx */
	m->ecx = m->ebp;	/* 49c3c8: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c3cfu; native_call(m, 0x462650u);	/* 49c3ca: call 0x462650 */
	m->esi = m->eax;	/* 49c3cf: mov esi, eax */
	{ DWORD a_ = m->esi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c3d1: cmp esi, ebx */
	if (m->sf != m->of) goto L_49c3f5;	/* 49c3d3: jl 0x49c3f5 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c3d5: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49c3db: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c3dc: push eax */
	m->ecx = m->ebp;	/* 49c3dd: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c3e4u; native_call(m, 0x463030u);	/* 49c3df: call 0x463030 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 49c3e4: mov ecx, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49c3ea: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c3eb: push ecx */
	m->ecx = m->ebp;	/* 49c3ec: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c3f3u; native_call(m, 0x48b430u);	/* 49c3ee: call 0x48b430 */
	goto L_49c46b;	/* 49c3f3: jmp 0x49c46b */
L_49c3f5:
	m->edx = (DWORD)(m->esp + 0x1b0u);	/* 49c3f5: lea edx, [esp + 0x1b0] */
	m->ecx = m->ebp;	/* 49c3fc: mov ecx, ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c3fe: push edx */
	{ DWORD v_ = 0x9f63e4u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c3ff: push 0x9f63e4 */
	m->esp -= 4; M32(m->esp) = 0x49c409u; native_call(m, 0x462740u);	/* 49c404: call 0x462740 */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49c409: sub eax, ebx */
	if (m->zf) goto L_49c412;	/* 49c40b: je 0x49c412 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 49c40d: dec eax */
	if (m->zf) goto L_49c43b;	/* 49c40e: je 0x49c43b */
	goto L_49c46b;	/* 49c410: jmp 0x49c46b */
L_49c412:
	m->edi = 0x9f63e4u;	/* 49c412: mov edi, 0x9f63e4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c417: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49c41a: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x1b0u);	/* 49c41c: lea edx, [esp + 0x1b0] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 49c423: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 49c425: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49c427: sub edi, ecx */
	m->eax = m->ecx;	/* 49c429: mov eax, ecx */
	m->esi = m->edi;	/* 49c42b: mov esi, edi */
	m->edi = m->edx;	/* 49c42d: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c42f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 49c432: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 49c434: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c436: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 49c439: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_49c43b:
	m->edx = M32((DWORD)(m->ebp + 0x234240du));	/* 49c43b: mov edx, dword ptr [ebp + 0x234240d] */
	m->ecx = (DWORD)(m->esp + 0x1b0u);	/* 49c441: lea ecx, [esp + 0x1b0] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 49c448: push -1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c44a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c44b: push edx */
	m->ecx = m->ebp;	/* 49c44c: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c453u; native_call(m, 0x462c30u);	/* 49c44e: call 0x462c30 */
	m->ecx = M32((DWORD)(m->ebp + 0x234240du));	/* 49c453: mov ecx, dword ptr [ebp + 0x234240d] */
	m->eax = (DWORD)(m->esp + 0x1b0u);	/* 49c459: lea eax, [esp + 0x1b0] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 49c460: push -1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c462: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c463: push ecx */
	m->ecx = m->ebp;	/* 49c464: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c46bu; native_call(m, 0x463550u);	/* 49c466: call 0x463550 */
L_49c46b:
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c46b: mov eax, dword ptr [ebp + 0x234240d] */
	m->edi = 0x3f800000u;	/* 49c471: mov edi, 0x3f800000 */
	m->edx = m->eax;	/* 49c476: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c478: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c47b: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c47d: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c480: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c482: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c485: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1ecce5cu)) = m->ebx;	/* 49c487: mov dword ptr [ebp + edx*8 + 0x1ecce5c], ebx */
	goto L_49c50e;	/* 49c48e: jmp 0x49c50e */
L_49c490:
	m->eax = M32((DWORD)(m->ebp + 0x23432fbu));	/* 49c490: mov eax, dword ptr [ebp + 0x23432fb] */
	m->esi = 0x1u;	/* 49c496: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c49b: cmp eax, esi */
	if (!m->zf) goto L_49c4d1;	/* 49c49d: jne 0x49c4d1 */
	{ DWORD v_ = 0x38u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c49f: push 0x38 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c4a1: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c4a2: push ebx */
	M32((DWORD)(m->ebp + 0x2340d35u)) = m->esi;	/* 49c4a3: mov dword ptr [ebp + 0x2340d35], esi */
	m->esp -= 4; M32(m->esp) = 0x49c4aeu; native_call(m, 0x44ac90u);	/* 49c4a9: call 0x44ac90 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c4ae: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49c4b4: add esp, 0xc */
	m->ecx = m->eax;	/* 49c4b7: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c4b9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c4bc: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c4be: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c4c1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c4c3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c4c6: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1ecce5cu)) = m->esi;	/* 49c4c8: mov dword ptr [ebp + ecx*8 + 0x1ecce5c], esi */
	goto L_49c513;	/* 49c4cf: jmp 0x49c513 */
L_49c4d1:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23432ffu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c4d1: cmp dword ptr [ebp + 0x23432ff], esi */
	if (!m->zf) goto L_49c513;	/* 49c4d7: jne 0x49c513 */
	{ DWORD v_ = 0x38u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c4d9: push 0x38 */
	m->esi = 0x2u;	/* 49c4db: mov esi, 2 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c4e0: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c4e1: push ebx */
	M32((DWORD)(m->ebp + 0x2340d35u)) = m->esi;	/* 49c4e2: mov dword ptr [ebp + 0x2340d35], esi */
	m->esp -= 4; M32(m->esp) = 0x49c4edu; native_call(m, 0x44ac90u);	/* 49c4e8: call 0x44ac90 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c4ed: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49c4f3: add esp, 0xc */
	m->edx = m->eax;	/* 49c4f6: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c4f8: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c4fb: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c4fd: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c500: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c502: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c505: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1ecce5cu)) = m->esi;	/* 49c507: mov dword ptr [ebp + edx*8 + 0x1ecce5c], esi */
L_49c50e:
	m->esi = 0x1u;	/* 49c50e: mov esi, 1 */
L_49c513:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340d35u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c513: cmp dword ptr [ebp + 0x2340d35], ebx */
	if (m->zf) goto L_49c525;	/* 49c519: je 0x49c525 */
	M32((DWORD)(m->ebp + 0x2340d39u)) = 0x3dcccccdu;	/* 49c51b: mov dword ptr [ebp + 0x2340d39], 0x3dcccccd */
L_49c525:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9f0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c525: cmp dword ptr [ebp + 0x233c9f0], esi */
	if (!m->zf) goto L_49c550;	/* 49c52b: jne 0x49c550 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc50u)));	/* 49c52d: fld dword ptr [ebp + 0x233cc50] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49c533: fsub dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x233cc50u)) = (float)ST(0);	/* 49c536: fst dword ptr [ebp + 0x233cc50] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49c53c: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c542: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c544: test ah, 1 */
	if (m->zf) goto L_49c550;	/* 49c547: je 0x49c550 */
	m->ecx = m->ebp;	/* 49c549: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c550u; native_call(m, 0x49d150u);	/* 49c54b: call 0x49d150 */
L_49c550:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c550: cmp dword ptr [ebp + 8], esi */
	if (!m->zf) goto L_49c62a;	/* 49c553: jne 0x49c62a */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a1u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c559: cmp dword ptr [ebp + 0x23423a1], ebx */
	if (!m->zf) goto L_49c5df;	/* 49c55f: jne 0x49c5df */
	m->esp -= 4; M32(m->esp) = 0x49c566u; native_call(m, 0x4a86d0u);	/* 49c561: call 0x4a86d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49c566: test eax, eax */
	if (!m->zf) goto L_49c5aa;	/* 49c568: jne 0x49c5aa */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2342395u)));	/* 49c56a: fld dword ptr [ebp + 0x2342395] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93d0u)); FPOP();	/* 49c570: fcomp dword ptr [0x4a93d0] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c576: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c578: test ah, 0x41 */
	if (!m->zf) goto L_49c59b;	/* 49c57b: jne 0x49c59b */
	m->ecx = m->ebp;	/* 49c57d: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c584u; native_call(m, 0x463390u);	/* 49c57f: call 0x463390 */
	M32((DWORD)(m->ebp + 0x23423a1u)) = m->esi;	/* 49c584: mov dword ptr [ebp + 0x23423a1], esi */
	M32((DWORD)(m->ebp + 0x23423a5u)) = 0x40400000u;	/* 49c58a: mov dword ptr [ebp + 0x23423a5], 0x40400000 */
	m->esp -= 4; M32(m->esp) = 0x49c599u; native_call(m, 0x457310u);	/* 49c594: call 0x457310 */
	goto L_49c5aa;	/* 49c599: jmp 0x49c5aa */
L_49c59b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2342395u)));	/* 49c59b: fld dword ptr [ebp + 0x2342395] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49c5a1: fadd dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x2342395u)) = (float)ST(0); FPOP();	/* 49c5a4: fstp dword ptr [ebp + 0x2342395] */
L_49c5aa:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a1u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c5aa: cmp dword ptr [ebp + 0x23423a1], ebx */
	if (!m->zf) goto L_49c5df;	/* 49c5b0: jne 0x49c5df */
	m->esp -= 4; M32(m->esp) = 0x49c5b7u; native_call(m, 0x4a8730u);	/* 49c5b2: call 0x4a8730 */
	{ DWORD a_ = m->eax, b_ = 0x80u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c5b7: cmp eax, 0x80 */
	if (m->sf != m->of) goto L_49c5df;	/* 49c5bc: jl 0x49c5df */
	m->esp -= 4; M32(m->esp) = 0x49c5c3u; native_call(m, 0x4a8720u);	/* 49c5be: call 0x4a8720 */
	m->ecx = m->ebp;	/* 49c5c3: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c5cau; native_call(m, 0x4633c0u);	/* 49c5c5: call 0x4633c0 */
	M32((DWORD)(m->ebp + 0x23423a1u)) = m->esi;	/* 49c5ca: mov dword ptr [ebp + 0x23423a1], esi */
	M32((DWORD)(m->ebp + 0x23423a5u)) = 0x40400000u;	/* 49c5d0: mov dword ptr [ebp + 0x23423a5], 0x40400000 */
	m->esp -= 4; M32(m->esp) = 0x49c5dfu; native_call(m, 0x457310u);	/* 49c5da: call 0x457310 */
L_49c5df:
	m->esp -= 4; M32(m->esp) = 0x49c5e4u; native_call(m, 0x4a8730u);	/* 49c5df: call 0x4a8730 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 49c5e4: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_49c5f5;	/* 49c5e6: jle 0x49c5f5 */
	m->esp -= 4; M32(m->esp) = 0x49c5edu; native_call(m, 0x4a8720u);	/* 49c5e8: call 0x4a8720 */
	M32((DWORD)(m->ebp + 0x2340c94u)) = m->edi;	/* 49c5ed: mov dword ptr [ebp + 0x2340c94], edi */
	goto L_49c62a;	/* 49c5f3: jmp 0x49c62a */
L_49c5f5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2340c94u)));	/* 49c5f5: fld dword ptr [ebp + 0x2340c94] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49c5fb: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c601: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c603: test ah, 0x41 */
	if (!m->zf) goto L_49c62a;	/* 49c606: jne 0x49c62a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x2340c94u)));	/* 49c608: fld dword ptr [ebp + 0x2340c94] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49c60e: fsub dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x2340c94u)) = (float)ST(0);	/* 49c611: fst dword ptr [ebp + 0x2340c94] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49c617: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c61d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c61f: test ah, 1 */
	if (m->zf) goto L_49c62a;	/* 49c622: je 0x49c62a */
	M32((DWORD)(m->ebp + 0x2340c94u)) = m->ebx;	/* 49c624: mov dword ptr [ebp + 0x2340c94], ebx */
L_49c62a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc4cu)));	/* 49c62a: fld dword ptr [ebp + 0x233cc4c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49c630: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c636: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c638: test ah, 0x41 */
	if (!m->zf) goto L_49c7e3;	/* 49c63b: jne 0x49c7e3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x233cc4cu)));	/* 49c641: fld dword ptr [ebp + 0x233cc4c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49c647: fsub dword ptr [ebp + 0x44] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 49c64a: fcom dword ptr [0x4a93e8] */
	MF((DWORD)(m->ebp + 0x233cc4cu)) = (float)ST(0);	/* 49c650: fst dword ptr [ebp + 0x233cc4c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c656: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c658: test ah, 0x41 */
	if (m->zf) goto L_49c7c2;	/* 49c65b: je 0x49c7c2 */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c661: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c667: cmp eax, ebx */
	ST(0) = ST(0); FPOP();	/* 49c669: fstp st(0) */
	if (m->sf != m->of) goto L_49c68d;	/* 49c66b: jl 0x49c68d */
	m->ecx = m->eax;	/* 49c66d: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c66f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c672: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c674: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c677: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c679: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c67c: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb88u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c67e: cmp dword ptr [ebp + ecx*8 + 0x1eccb88], ebx */
	if (m->sf != m->of) goto L_49c68d;	/* 49c685: jl 0x49c68d */
	M32((DWORD)(m->ebp + 0x2340d00u)) = m->esi;	/* 49c687: mov dword ptr [ebp + 0x2340d00], esi */
L_49c68d:
	m->ecx = m->ebp;	/* 49c68d: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x234239du)) = m->ebx;	/* 49c68f: mov dword ptr [ebp + 0x234239d], ebx */
	M32((DWORD)(m->ebp + 0x2342399u)) = m->ebx;	/* 49c695: mov dword ptr [ebp + 0x2342399], ebx */
	m->esp -= 4; M32(m->esp) = 0x49c6a0u; native_call(m, 0x487ed0u);	/* 49c69b: call 0x487ed0 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9f0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c6a0: cmp dword ptr [ebp + 0x233c9f0], esi */
	if (!m->zf) goto L_49c6ba;	/* 49c6a6: jne 0x49c6ba */
	m->eax = M32((DWORD)(0x4de72au));	/* 49c6a8: mov eax, dword ptr [0x4de72a] */
	m->ecx = m->ebp;	/* 49c6ad: mov ecx, ebp */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49c6af: inc eax */
	M32((DWORD)(0x4de72au)) = m->eax;	/* 49c6b0: mov dword ptr [0x4de72a], eax */
	m->esp -= 4; M32(m->esp) = 0x49c6bau; native_call(m, 0x49d150u);	/* 49c6b5: call 0x49d150 */
L_49c6ba:
	m->eax = M32((DWORD)(m->ebp + 0x22f0400u));	/* 49c6ba: mov eax, dword ptr [ebp + 0x22f0400] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c6c0: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c6c2: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_49c6df;	/* 49c6c4: jle 0x49c6df */
	m->eax = (DWORD)(m->ebp + 0x22ee4e4u);	/* 49c6c6: lea eax, [ebp + 0x22ee4e4] */
L_49c6cc:
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->ebx;	/* 49c6cc: mov dword ptr [eax - 4], ebx */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 49c6cf: mov dword ptr [eax], ebx */
	m->edx = M32((DWORD)(m->ebp + 0x22f0400u));	/* 49c6d1: mov edx, dword ptr [ebp + 0x22f0400] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 49c6d7: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49c6d8: add eax, 0x28 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c6db: cmp ecx, edx */
	if (m->sf != m->of) goto L_49c6cc;	/* 49c6dd: jl 0x49c6cc */
L_49c6df:
	m->eax = (DWORD)(m->ebp + 0x1eccb58u);	/* 49c6df: lea eax, [ebp + 0x1eccb58] */
	m->ecx = 0x10u;	/* 49c6e5: mov ecx, 0x10 */
L_49c6ea:
	M32((DWORD)(m->eax + 0xfffffffcu)) = m->ebx;	/* 49c6ea: mov dword ptr [eax - 4], ebx */
	M32((DWORD)(m->eax + 0x0u)) = m->ebx;	/* 49c6ed: mov dword ptr [eax], ebx */
	M32((DWORD)(m->eax + 0x8u)) = m->ebx;	/* 49c6ef: mov dword ptr [eax + 8], ebx */
	M32((DWORD)(m->eax + 0xcu)) = m->ebx;	/* 49c6f2: mov dword ptr [eax + 0xc], ebx */
	M32((DWORD)(m->eax + 0x14u)) = m->ebx;	/* 49c6f5: mov dword ptr [eax + 0x14], ebx */
	M32((DWORD)(m->eax + 0x18u)) = m->ebx;	/* 49c6f8: mov dword ptr [eax + 0x18], ebx */
	{ DWORD a_ = m->eax, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 49c6fb: add eax, 0x8888 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 49c700: dec ecx */
	if (!m->zf) goto L_49c6ea;	/* 49c701: jne 0x49c6ea */
	m->ecx = (DWORD)(m->ebp + 0x1f36c8u);	/* 49c703: lea ecx, [ebp + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x49c70eu; native_call(m, 0x45df90u);	/* 49c709: call 0x45df90 */
	m->ecx = m->ebp;	/* 49c70e: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c715u; native_call(m, 0x462150u);	/* 49c710: call 0x462150 */
	{ DWORD v_ = 0x42700000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c715: push 0x42700000 */
	m->ecx = m->ebp;	/* 49c71a: mov ecx, ebp */
	M32((DWORD)(m->ebp + 0x234297au)) = 0xffffffffu;	/* 49c71c: mov dword ptr [ebp + 0x234297a], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x49c72bu; native_call(m, 0x4629c0u);	/* 49c726: call 0x4629c0 */
	m->ecx = m->ebp;	/* 49c72b: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c732u; native_call(m, 0x463480u);	/* 49c72d: call 0x463480 */
	M32((DWORD)(m->ebp + 0x22f0408u)) = m->ebx;	/* 49c732: mov dword ptr [ebp + 0x22f0408], ebx */
	M32((DWORD)(m->ebp + 0x22f040cu)) = m->ebx;	/* 49c738: mov dword ptr [ebp + 0x22f040c], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c73e: mov eax, dword ptr [ebp + 0x234240d] */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c744: push 0x64 */
	m->edx = m->eax;	/* 49c746: mov edx, eax */
	{ DWORD v_ = 0x18u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c748: push 0x18 */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c74a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c74d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c74f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c752: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c754: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c757: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb60u)) = m->ebx;	/* 49c759: mov dword ptr [ebp + edx*8 + 0x1eccb60], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c760: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49c766: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c768: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c76b: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c76d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c770: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c772: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c775: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb54u)) = m->ebx;	/* 49c777: mov dword ptr [ebp + ecx*8 + 0x1eccb54], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c77e: mov eax, dword ptr [ebp + 0x234240d] */
	m->edx = m->eax;	/* 49c784: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c786: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c789: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c78b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c78e: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c790: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c793: add edx, eax */
	M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb64u)) = m->ebx;	/* 49c795: mov dword ptr [ebp + edx*8 + 0x1eccb64], ebx */
	m->eax = M32((DWORD)(m->ebp + 0x234240du));	/* 49c79c: mov eax, dword ptr [ebp + 0x234240d] */
	m->ecx = m->eax;	/* 49c7a2: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c7a4: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c7a7: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c7a9: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c7ac: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c7ae: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c7b1: add ecx, eax */
	M32((DWORD)(m->ebp + m->ecx*8 + 0x1eccb58u)) = m->ebx;	/* 49c7b3: mov dword ptr [ebp + ecx*8 + 0x1eccb58], ebx */
	M32((DWORD)(m->ebp + 0x233cc4cu)) = m->ebx;	/* 49c7ba: mov dword ptr [ebp + 0x233cc4c], ebx */
	goto L_49c7db;	/* 49c7c0: jmp 0x49c7db */
L_49c7c2:
	{ long double t = ST(0); FPUSH(t); }	/* 49c7c2: fld st(0) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49c7c4: fadd dword ptr [ebp + 0x44] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49c7c7: call 0x49ec14 */
	m->edi = m->eax;	/* 49c7cc: mov edi, eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 49c7ce: call 0x49ec14 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c7d3: cmp edi, eax */
	if (m->zf) goto L_49c7e3;	/* 49c7d5: je 0x49c7e3 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c7d7: push 0x64 */
	{ DWORD v_ = 0x9u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c7d9: push 9 */
L_49c7db:
	m->esp -= 4; M32(m->esp) = 0x49c7e0u; native_call(m, 0x456e50u);	/* 49c7db: call 0x456e50 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49c7e0: add esp, 8 */
L_49c7e3:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x23423a1u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c7e3: cmp dword ptr [ebp + 0x23423a1], esi */
	if (!m->zf) goto L_49ca0e;	/* 49c7e9: jne 0x49ca0e */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x23423a5u)));	/* 49c7ef: fld dword ptr [ebp + 0x23423a5] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x44u));	/* 49c7f5: fsub dword ptr [ebp + 0x44] */
	MF((DWORD)(m->ebp + 0x23423a5u)) = (float)ST(0);	/* 49c7f8: fst dword ptr [ebp + 0x23423a5] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 49c7fe: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49c804: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49c806: test ah, 0x41 */
	if (m->zf) goto L_49ca0e;	/* 49c809: je 0x49ca0e */
	{ DWORD a_ = M32((DWORD)(0x9f67f0u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c80f: cmp dword ptr [0x9f67f0], ebx */
	if (!m->zf) goto L_49c9d2;	/* 49c815: jne 0x49c9d2 */
	{ DWORD a_ = M32((DWORD)(0x76d410u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c81b: cmp dword ptr [0x76d410], ebx */
	if (m->zf) goto L_49c9d2;	/* 49c821: je 0x49c9d2 */
	{ DWORD v_ = 0x4b21a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c827: push 0x4b21a4 */
	{ DWORD v_ = 0x4d06e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c82c: push 0x4d06e0 */
	m->esp -= 4; M32(m->esp) = 0x49c836u; native_call(m, 0x49e9cau);	/* 49c831: call 0x49e9ca */
	m->ecx = M32((DWORD)(0x9f67f8u));	/* 49c836: mov ecx, dword ptr [0x9f67f8] */
	m->esi = m->eax;	/* 49c83c: mov esi, eax */
	m->eax = 0x1u;	/* 49c83e: mov eax, 1 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49c843: add esp, 8 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c846: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x3cu)) = m->esi;	/* 49c848: mov dword ptr [esp + 0x3c], esi */
	if (m->zf) goto L_49c85e;	/* 49c84c: je 0x49c85e */
	{ DWORD a_ = M32((DWORD)(0x9f67f4u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c84e: cmp dword ptr [0x9f67f4], eax */
	if (!m->zf) goto L_49c883;	/* 49c854: jne 0x49c883 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2342976u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c856: cmp dword ptr [ebp + 0x2342976], eax */
	if (!m->zf && m->sf == m->of) goto L_49c883;	/* 49c85c: jg 0x49c883 */
L_49c85e:
	m->edx = M32((DWORD)(0x76d408u));	/* 49c85e: mov edx, dword ptr [0x76d408] */
	m->eax = M32((DWORD)(0x4df8e8u));	/* 49c864: mov eax, dword ptr [0x4df8e8] */
	m->ecx = M32((DWORD)(0x9dad94u));	/* 49c869: mov ecx, dword ptr [0x9dad94] */
	{ DWORD v_ = 0x4dedd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c86f: push 0x4dedd8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c874: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c875: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c876: push ecx */
	{ DWORD v_ = 0x67fb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c877: push 0x67fb44 */
	{ DWORD v_ = 0x4d069cu; m->esp -= 4; M32(m->esp) = v_; }	/* 49c87c: push 0x4d069c */
	goto L_49c8a6;	/* 49c881: jmp 0x49c8a6 */
L_49c883:
	m->edx = M32((DWORD)(0x76d408u));	/* 49c883: mov edx, dword ptr [0x76d408] */
	m->eax = M32((DWORD)(0x4df8e8u));	/* 49c889: mov eax, dword ptr [0x4df8e8] */
	m->ecx = M32((DWORD)(0x9dad94u));	/* 49c88e: mov ecx, dword ptr [0x9dad94] */
	{ DWORD v_ = 0x4dedd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c894: push 0x4dedd8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c899: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c89a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c89b: push ecx */
	{ DWORD v_ = 0x67fb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c89c: push 0x67fb44 */
	{ DWORD v_ = 0x4d05a8u; m->esp -= 4; M32(m->esp) = v_; }	/* 49c8a1: push 0x4d05a8 */
L_49c8a6:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49c8a6: push esi */
	m->esp -= 4; M32(m->esp) = 0x49c8acu; native_call(m, 0x49f135u);	/* 49c8a7: call 0x49f135 */
	m->eax = M32((DWORD)(m->ebp + 0x2342976u));	/* 49c8ac: mov eax, dword ptr [ebp + 0x2342976] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49c8b2: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c8b5: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x28u)) = m->ebx;	/* 49c8b7: mov dword ptr [esp + 0x28], ebx */
	if (m->zf || m->sf != m->of) goto L_49c9c2;	/* 49c8bb: jle 0x49c9c2 */
	m->ebx = (DWORD)(m->ebp + 0x23428f6u);	/* 49c8c1: lea ebx, [ebp + 0x23428f6] */
L_49c8c7:
	m->eax = M32((DWORD)(0x76d368u));	/* 49c8c7: mov eax, dword ptr [0x76d368] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c8cc: cmp eax, 1 */
	if (m->zf) goto L_49c8f4;	/* 49c8cf: je 0x49c8f4 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c8d1: cmp eax, 3 */
	if (m->zf) goto L_49c8f4;	/* 49c8d4: je 0x49c8f4 */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c8d6: cmp eax, 5 */
	if (m->zf) goto L_49c8f4;	/* 49c8d9: je 0x49c8f4 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c8db: cmp eax, 7 */
	if (m->zf) goto L_49c8f4;	/* 49c8de: je 0x49c8f4 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c8e0: cmp eax, 9 */
	if (m->zf) goto L_49c8f4;	/* 49c8e3: je 0x49c8f4 */
	{ DWORD a_ = m->eax, b_ = 0xbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c8e5: cmp eax, 0xb */
	if (m->zf) goto L_49c8f4;	/* 49c8e8: je 0x49c8f4 */
	M32((DWORD)(m->esp + 0x40u)) = 0x2u;	/* 49c8ea: mov dword ptr [esp + 0x40], 2 */
	goto L_49c912;	/* 49c8f2: jmp 0x49c912 */
L_49c8f4:
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 49c8f4: mov eax, dword ptr [ebx] */
	m->edx = m->eax;	/* 49c8f6: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c8f8: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c8fb: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c8fd: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c900: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49c902: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49c905: add edx, eax */
	m->eax = M32((DWORD)(m->ebp + m->edx*8 + 0x1eccb88u));	/* 49c907: mov eax, dword ptr [ebp + edx*8 + 0x1eccb88] */
	M32((DWORD)(m->esp + 0x40u)) = m->eax;	/* 49c90e: mov dword ptr [esp + 0x40], eax */
L_49c912:
	m->ecx = 0x10u;	/* 49c912: mov ecx, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49c917: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0xc4u);	/* 49c919: lea edi, [esp + 0xc4] */
	m->esi = (DWORD)(m->esp + 0xc4u);	/* 49c920: lea esi, [esp + 0xc4] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 49c927: rep stosd dword ptr es:[edi], eax */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 49c929: mov eax, dword ptr [ebx] */
	M32((DWORD)(m->esp + 0x38u)) = m->esi;	/* 49c92b: mov dword ptr [esp + 0x38], esi */
	m->ecx = m->eax;	/* 49c92f: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c931: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c934: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c936: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c939: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c93b: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 49c93e: add ecx, eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49c940: xor eax, eax */
	m->edx = (DWORD)(m->ebp + m->ecx*8 + 0x0u);	/* 49c942: lea edx, [ebp + ecx*8] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c946: or ecx, 0xffffffff */
	m->edi = (DWORD)(m->edx + 0x1eccb08u);	/* 49c949: lea edi, [edx + 0x1eccb08] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 49c94f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 49c951: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 49c953: sub edi, ecx */
	m->eax = m->ecx;	/* 49c955: mov eax, ecx */
	m->esi = m->edi;	/* 49c957: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x38u));	/* 49c959: mov edi, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 49c95d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 49c960: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 49c962: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49c964: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 49c967: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->edx + 0x1eccb58u));	/* 49c969: mov ecx, dword ptr [edx + 0x1eccb58] */
	m->eax = M32((DWORD)(m->edx + 0x1eccb54u));	/* 49c96f: mov eax, dword ptr [edx + 0x1eccb54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c975: push ecx */
	m->ecx = M32((DWORD)(m->edx + 0x1eccb6cu));	/* 49c976: mov ecx, dword ptr [edx + 0x1eccb6c] */
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 49c97c: mov edx, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c980: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c981: push ecx */
	m->ecx = (DWORD)(m->esp + 0xd0u);	/* 49c982: lea ecx, [esp + 0xd0] */
	m->eax = M32((DWORD)(m->esp + m->edx*4 + 0xa8u));	/* 49c989: mov eax, dword ptr [esp + edx*4 + 0xa8] */
	m->edx = M32((DWORD)(m->esp + 0x48u));	/* 49c990: mov edx, dword ptr [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 49c994: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c995: push ecx */
	{ DWORD v_ = 0x4d062cu; m->esp -= 4; M32(m->esp) = v_; }	/* 49c996: push 0x4d062c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 49c99b: push edx */
	m->esp -= 4; M32(m->esp) = 0x49c9a1u; native_call(m, 0x49f135u);	/* 49c99c: call 0x49f135 */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 49c9a1: mov eax, dword ptr [esp + 0x44] */
	m->ecx = M32((DWORD)(m->ebp + 0x2342976u));	/* 49c9a5: mov ecx, dword ptr [ebp + 0x2342976] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49c9ab: add esp, 0x1c */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 49c9ae: inc eax */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 49c9af: add ebx, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c9b2: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 49c9b4: mov dword ptr [esp + 0x28], eax */
	if (m->sf != m->of) goto L_49c8c7;	/* 49c9b8: jl 0x49c8c7 */
	m->esi = M32((DWORD)(m->esp + 0x3cu));	/* 49c9be: mov esi, dword ptr [esp + 0x3c] */
L_49c9c2:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49c9c2: push esi */
	m->esp -= 4; M32(m->esp) = 0x49c9c8u; native_call(m, 0x49e7e0u);	/* 49c9c3: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49c9c8: add esp, 4 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 49c9cb: xor ebx, ebx */
	m->esi = 0x1u;	/* 49c9cd: mov esi, 1 */
L_49c9d2:
	m->ecx = m->ebp;	/* 49c9d2: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49c9d9u; native_call(m, 0x487ed0u);	/* 49c9d4: call 0x487ed0 */
	m->esp -= 4; M32(m->esp) = 0x49c9deu; native_call(m, 0x457310u);	/* 49c9d9: call 0x457310 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x2340d35u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c9de: cmp dword ptr [ebp + 0x2340d35], ebx */
	if (m->zf) goto L_49c9f9;	/* 49c9e4: je 0x49c9f9 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c9e6: cmp dword ptr [0x68039c], ebx */
	if (!m->zf) goto L_49c9f9;	/* 49c9ec: jne 0x49c9f9 */
	M32((DWORD)(m->ebp + 0x2340d35u)) = m->ebx;	/* 49c9ee: mov dword ptr [ebp + 0x2340d35], ebx */
	m->esp -= 4; M32(m->esp) = 0x49c9f9u; native_call(m, 0x44ace0u);	/* 49c9f4: call 0x44ace0 */
L_49c9f9:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233c9f0u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49c9f9: cmp dword ptr [ebp + 0x233c9f0], esi */
	if (!m->zf) goto L_49ca08;	/* 49c9ff: jne 0x49ca08 */
	m->ecx = m->ebp;	/* 49ca01: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x49ca08u; native_call(m, 0x49d150u);	/* 49ca03: call 0x49d150 */
L_49ca08:
	M32((DWORD)(m->ebp + 0x23432cfu)) = m->esi;	/* 49ca08: mov dword ptr [ebp + 0x23432cf], esi */
L_49ca0e:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x233cc28u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebp + 0x233cc28u)) = r_; }	/* 49ca0e: inc dword ptr [ebp + 0x233cc28] */
L_49ca14:
	m->edi = M32(m->esp); m->esp += 4;	/* 49ca14: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 49ca15: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 49ca16: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 49ca17: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x2a0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 49ca18: add esp, 0x2a0 */
	m->esp += 4 + 0; return;	/* 49ca1e: ret  */
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
