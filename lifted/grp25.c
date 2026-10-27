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

static void lift_46ed80(X86 *m);
static void lift_46eb00(X86 *m);

/* ptx_open (0x46eb00), lifted by tools/lift.py */
static void lift_46eb00(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eb00: sub esp, 0x128 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb06: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb07: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb08: push esi */
	m->esi = M32((DWORD)(m->esp + 0x138u));	/* 46eb09: mov esi, dword ptr [esp + 0x138] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb10: push edi */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb11: push 0x4ad170 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb16: push esi */
	m->esp -= 4; M32(m->esp) = 0x46eb1cu; native_call(m, 0x49e9cau);	/* 46eb17: call 0x49e9ca */
	m->edi = m->eax;	/* 46eb1c: mov edi, eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46eb1e: xor ebx, ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eb20: add esp, 8 */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46eb23: cmp edi, ebx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edi;	/* 46eb25: mov dword ptr [esp + 0x2c], edi */
	if (!m->zf) goto L_46eb3b;	/* 46eb29: jne 0x46eb3b */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb2b: push esi */
	{ DWORD v_ = 0x4b3fd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb2c: push 0x4b3fd8 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb31: push -1 */
	m->esp -= 4; M32(m->esp) = 0x46eb38u; native_call(m, 0x46e1e0u);	/* 46eb33: call 0x46e1e0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eb38: add esp, 0xc */
L_46eb3b:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb3b: push edi */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb3c: push 0x10 */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 46eb3e: lea eax, [esp + 0x20] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb42: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb44: push eax */
	m->esp -= 4; M32(m->esp) = 0x46eb4au; native_call(m, 0x49e836u);	/* 46eb45: call 0x49e836 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x28u))) & 0xff) << 0);	/* 46eb4a: mov al, byte ptr [esp + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eb4e: add esp, 0x10 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x50u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46eb51: cmp al, 0x50 */
	if (!m->zf) goto L_46eb6b;	/* 46eb53: jne 0x46eb6b */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x19u)), b_ = 0x54u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46eb55: cmp byte ptr [esp + 0x19], 0x54 */
	if (!m->zf) goto L_46eb6b;	/* 46eb5a: jne 0x46eb6b */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x1au)), b_ = 0x58u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46eb5c: cmp byte ptr [esp + 0x1a], 0x58 */
	if (!m->zf) goto L_46eb6b;	/* 46eb61: jne 0x46eb6b */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x1bu))) & 0xff) << 0);	/* 46eb63: mov al, byte ptr [esp + 0x1b] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46eb67: test al, al */
	if (m->zf) goto L_46eb7a;	/* 46eb69: je 0x46eb7a */
L_46eb6b:
	{ DWORD v_ = 0x4c6fecu; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb6b: push 0x4c6fec */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb70: push -1 */
	m->esp -= 4; M32(m->esp) = 0x46eb77u; native_call(m, 0x46e260u);	/* 46eb72: call 0x46e260 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eb77: add esp, 8 */
L_46eb7a:
	{ DWORD a_ = M16((DWORD)(m->esp + 0x1cu)), b_ = 0x100u & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 46eb7a: cmp word ptr [esp + 0x1c], 0x100 */
	if (m->zf) goto L_46eb92;	/* 46eb81: je 0x46eb92 */
	{ DWORD v_ = 0x4c6fecu; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb83: push 0x4c6fec */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 46eb88: push -1 */
	m->esp -= 4; M32(m->esp) = 0x46eb8fu; native_call(m, 0x46e260u);	/* 46eb8a: call 0x46e260 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eb8f: add esp, 8 */
L_46eb92:
	m->esi = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x1eu)));	/* 46eb92: movsx esi, word ptr [esp + 0x1e] */
	m->ebp = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x20u)));	/* 46eb97: movsx ebp, word ptr [esp + 0x20] */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x22u)));	/* 46eb9c: movsx eax, word ptr [esp + 0x22] */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46eba1: shl esi, 3 */
	{ DWORD a_ = m->ebp, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 46eba4: shl ebp, 3 */
	{ DWORD a_ = m->eax, b_ = 0x81u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46eba7: sub eax, 0x81 */
	M32((DWORD)(m->esp + 0x28u)) = m->esi;	/* 46ebac: mov dword ptr [esp + 0x28], esi */
	M32((DWORD)(m->esp + 0x34u)) = m->ebp;	/* 46ebb0: mov dword ptr [esp + 0x34], ebp */
	if (m->zf) goto L_46ebdc;	/* 46ebb4: je 0x46ebdc */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46ebb6: dec eax */
	if (m->zf) goto L_46ebd2;	/* 46ebb7: je 0x46ebd2 */
	{ DWORD v_ = 0x4c6fd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ebb9: push 0x4c6fd8 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 46ebbe: push -1 */
	m->esp -= 4; M32(m->esp) = 0x46ebc5u; native_call(m, 0x46e260u);	/* 46ebc0: call 0x46e260 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ebc5: add esp, 8 */
	M32((DWORD)(m->esp + 0x10u)) = 0xffffffffu;	/* 46ebc8: mov dword ptr [esp + 0x10], 0xffffffff */
	goto L_46ebe4;	/* 46ebd0: jmp 0x46ebe4 */
L_46ebd2:
	M32((DWORD)(m->esp + 0x10u)) = 0x4u;	/* 46ebd2: mov dword ptr [esp + 0x10], 4 */
	goto L_46ebe4;	/* 46ebda: jmp 0x46ebe4 */
L_46ebdc:
	M32((DWORD)(m->esp + 0x10u)) = 0x3u;	/* 46ebdc: mov dword ptr [esp + 0x10], 3 */
L_46ebe4:
	m->ecx = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x24u)));	/* 46ebe4: movsx ecx, word ptr [esp + 0x24] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ebe9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46ebefu; native_call(m, 0x46e9b0u);	/* 46ebea: call 0x46e9b0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ebef: push edi */
	{ DWORD v_ = 0x10000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ebf0: push 0x10000 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ebf5: push 1 */
	{ DWORD v_ = 0xaa2e98u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ebf7: push 0xaa2e98 */
	m->esp -= 4; M32(m->esp) = 0x46ec01u; native_call(m, 0x49e836u);	/* 46ebfc: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 46ec01: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ec05: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46ec08: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ec0a: cmp eax, ebx */
	M32((DWORD)(m->esp + 0x14u)) = m->ebx;	/* 46ec0c: mov dword ptr [esp + 0x14], ebx */
	if (m->zf || m->sf != m->of) goto L_46ecb6;	/* 46ec10: jle 0x46ecb6 */
	{ long long p_ = (long long)(int)m->ebp * (int)m->esi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebp = r_; }	/* 46ec16: imul ebp, esi */
	M32((DWORD)(m->esp + 0x30u)) = m->ebp;	/* 46ec19: mov dword ptr [esp + 0x30], ebp */
L_46ec1d:
	{ DWORD a_ = m->edi, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ec1d: cmp edi, 3 */
	if (!m->cf && !m->zf) goto L_46ec3f;	/* 46ec20: ja 0x46ec3f */
	switch (m->edi) { case 0: goto L_46ec35; case 1: goto L_46ec29; case 2: goto L_46ec29; case 3: goto L_46ec35; default: abort(); }	/* 46ec22: jmp dword ptr [edi*4 + 0x46ed6c] */
L_46ec29:
	M32((DWORD)(0xaa2e94u)) = 0x1u;	/* 46ec29: mov dword ptr [0xaa2e94], 1 */
	goto L_46ec3f;	/* 46ec33: jmp 0x46ec3f */
L_46ec35:
	M32((DWORD)(0xaa2e94u)) = 0x0u;	/* 46ec35: mov dword ptr [0xaa2e94], 0 */
L_46ec3f:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46ec3f: mov edx, dword ptr [esp + 0x14] */
	m->esi = m->edi;	/* 46ec43: mov esi, edi */
	{ DWORD a_ = m->esi, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46ec45: shl esi, 0x10 */
	m->eax = (DWORD)(m->edx + 0xaa2e98u);	/* 46ec48: lea eax, [edx + 0xaa2e98] */
	{ DWORD a_ = m->esi, b_ = 0xa6228cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46ec4e: add esi, 0xa6228c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ec54: push eax */
	m->esp -= 4; M32(m->esp) = 0x46ec5au; native_call(m, 0x46f090u);	/* 46ec55: call 0x46f090 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ec5a: add esp, 4 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46ec5d: test ebp, ebp */
	if (m->zf || m->sf != m->of) goto L_46ec8b;	/* 46ec5f: jle 0x46ec8b */
	{ DWORD a_ = m->ebp, b_ = 0x3fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46ec61: add ebp, 0x3f */
	{ DWORD a_ = m->ebp, c_ = (0x6u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 46ec64: shr ebp, 6 */
L_46ec67:
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 46ec67: lea ecx, [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ec6b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46ec71u; native_call(m, 0x46f0b0u);	/* 46ec6c: call 0x46f0b0 */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 46ec71: lea edx, [esp + 0x3c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ec75: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ec76: push edx */
	m->ebx = m->eax;	/* 46ec77: mov ebx, eax */
	m->esp -= 4; M32(m->esp) = 0x46ec7eu; native_call(m, 0x46e380u);	/* 46ec79: call 0x46e380 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ec7e: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46ec81: add esi, 0x40 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 46ec84: dec ebp */
	if (!m->zf) goto L_46ec67;	/* 46ec85: jne 0x46ec67 */
	m->ebp = M32((DWORD)(m->esp + 0x30u));	/* 46ec87: mov ebp, dword ptr [esp + 0x30] */
L_46ec8b:
	m->eax = (DWORD)(m->ebx + 0x7u);	/* 46ec8b: lea eax, [ebx + 7] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46ec8e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46ec8f: and edx, 7 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46ec92: add eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46ec94: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46ec98: sar eax, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46ec9b: add edx, eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46ec9d: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 46eca1: inc edi */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 46eca2: mov dword ptr [esp + 0x14], edx */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46eca6: cmp edi, eax */
	if (m->sf != m->of) goto L_46ec1d;	/* 46eca8: jl 0x46ec1d */
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 46ecae: mov esi, dword ptr [esp + 0x28] */
	m->ebp = M32((DWORD)(m->esp + 0x34u));	/* 46ecb2: mov ebp, dword ptr [esp + 0x34] */
L_46ecb6:
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 46ecb6: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ecba: push eax */
	m->esp -= 4; M32(m->esp) = 0x46ecc0u; native_call(m, 0x49e7e0u);	/* 46ecbb: call 0x49e7e0 */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x26u)));	/* 46ecc0: movsx eax, word ptr [esp + 0x26] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ecc5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x81u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46ecc8: sub eax, 0x81 */
	if (m->zf) goto L_46ece9;	/* 46eccd: je 0x46ece9 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46eccf: dec eax */
	if (!m->zf) goto L_46ed01;	/* 46ecd0: jne 0x46ed01 */
	m->ecx = m->ebp;	/* 46ecd2: mov ecx, ebp */
	{ long long p_ = (long long)(int)m->ecx * (int)m->esi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 46ecd4: imul ecx, esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ecd7: push ecx */
	{ DWORD v_ = 0xa21708u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ecd8: push 0xa21708 */
	{ DWORD v_ = 0xa6228cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46ecdd: push 0xa6228c */
	m->esp -= 4; M32(m->esp) = 0x46ece7u; native_call(m, 0x46e8e0u);	/* 46ece2: call 0x46e8e0 */
	goto L_46ecfe;	/* 46ece7: jmp 0x46ecfe */
L_46ece9:
	m->edx = m->ebp;	/* 46ece9: mov edx, ebp */
	{ long long p_ = (long long)(int)m->edx * (int)m->esi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edx = r_; }	/* 46eceb: imul edx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ecee: push edx */
	{ DWORD v_ = 0xa21708u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ecef: push 0xa21708 */
	{ DWORD v_ = 0xa6228cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46ecf4: push 0xa6228c */
	m->esp -= 4; M32(m->esp) = 0x46ecfeu; native_call(m, 0x46e830u);	/* 46ecf9: call 0x46e830 */
L_46ecfe:
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ecfe: add esp, 0xc */
L_46ed01:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46ed01: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x140u));	/* 46ed05: mov ecx, dword ptr [esp + 0x140] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed0c: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed0d: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed0e: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed0f: push ecx */
	{ DWORD v_ = 0xa21708u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed10: push 0xa21708 */
	m->esp -= 4; M32(m->esp) = 0x46ed1au; native_call(m, 0x46ea30u);	/* 46ed15: call 0x46ea30 */
	m->edx = M32((DWORD)(m->esp + 0x15cu));	/* 46ed1a: mov edx, dword ptr [esp + 0x15c] */
	m->eax = M32((DWORD)(m->esp + 0x160u));	/* 46ed21: mov eax, dword ptr [esp + 0x160] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ed28: add esp, 0x14 */
	M32((DWORD)(m->edx + 0x0u)) = m->esi;	/* 46ed2b: mov dword ptr [edx], esi */
	M32((DWORD)(m->eax + 0x0u)) = m->ebp;	/* 46ed2d: mov dword ptr [eax], ebp */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x22u)));	/* 46ed2f: movsx eax, word ptr [esp + 0x22] */
	m->edi = M32(m->esp); m->esp += 4;	/* 46ed34: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46ed35: pop esi */
	{ DWORD a_ = m->eax, b_ = 0x81u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46ed36: sub eax, 0x81 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46ed3b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46ed3c: pop ebx */
	if (m->zf) goto L_46ed56;	/* 46ed3d: je 0x46ed56 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46ed3f: dec eax */
	if (!m->zf) goto L_46ed63;	/* 46ed40: jne 0x46ed63 */
	m->ecx = M32((DWORD)(m->esp + 0x134u));	/* 46ed42: mov ecx, dword ptr [esp + 0x134] */
	M32((DWORD)(m->ecx + 0x0u)) = 0x3u;	/* 46ed49: mov dword ptr [ecx], 3 */
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ed4f: add esp, 0x128 */
	m->esp += 4 + 0; return;	/* 46ed55: ret  */
L_46ed56:
	m->edx = M32((DWORD)(m->esp + 0x134u));	/* 46ed56: mov edx, dword ptr [esp + 0x134] */
	M32((DWORD)(m->edx + 0x0u)) = 0x2u;	/* 46ed5d: mov dword ptr [edx], 2 */
L_46ed63:
	{ DWORD a_ = m->esp, b_ = 0x128u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ed63: add esp, 0x128 */
	m->esp += 4 + 0; return;	/* 46ed69: ret  */
}

/* ptx_decode (0x46ed80), lifted by tools/lift.py */
static void lift_46ed80(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x124u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ed80: sub esp, 0x124 */
	m->eax = (DWORD)(m->esp + 0x8u);	/* 46ed86: lea eax, [esp + 8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed8a: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed8b: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed8c: push edi */
	m->edi = M32((DWORD)(m->esp + 0x134u));	/* 46ed8d: mov edi, dword ptr [esp + 0x134] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed94: push edi */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed95: push 0x10 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed97: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ed99: push eax */
	m->esp -= 4; M32(m->esp) = 0x46ed9fu; native_call(m, 0x49e836u);	/* 46ed9a: call 0x49e836 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x24u))) & 0xff) << 0);	/* 46ed9f: mov al, byte ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eda3: add esp, 0x10 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x50u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46eda6: cmp al, 0x50 */
	if (!m->zf) goto L_46edc0;	/* 46eda8: jne 0x46edc0 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x15u)), b_ = 0x54u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46edaa: cmp byte ptr [esp + 0x15], 0x54 */
	if (!m->zf) goto L_46edc0;	/* 46edaf: jne 0x46edc0 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x16u)), b_ = 0x58u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 46edb1: cmp byte ptr [esp + 0x16], 0x58 */
	if (!m->zf) goto L_46edc0;	/* 46edb6: jne 0x46edc0 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x17u))) & 0xff) << 0);	/* 46edb8: mov al, byte ptr [esp + 0x17] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 46edbc: test al, al */
	if (m->zf) goto L_46edcf;	/* 46edbe: je 0x46edcf */
L_46edc0:
	{ DWORD v_ = 0x4c6fecu; m->esp -= 4; M32(m->esp) = v_; }	/* 46edc0: push 0x4c6fec */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 46edc5: push -1 */
	m->esp -= 4; M32(m->esp) = 0x46edccu; native_call(m, 0x46e260u);	/* 46edc7: call 0x46e260 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46edcc: add esp, 8 */
L_46edcf:
	{ DWORD a_ = M16((DWORD)(m->esp + 0x18u)), b_ = 0x100u & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 46edcf: cmp word ptr [esp + 0x18], 0x100 */
	if (m->zf) goto L_46ede7;	/* 46edd6: je 0x46ede7 */
	{ DWORD v_ = 0x4c6fecu; m->esp -= 4; M32(m->esp) = v_; }	/* 46edd8: push 0x4c6fec */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 46eddd: push -1 */
	m->esp -= 4; M32(m->esp) = 0x46ede4u; native_call(m, 0x46e260u);	/* 46eddf: call 0x46e260 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ede4: add esp, 8 */
L_46ede7:
	m->esi = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x1au)));	/* 46ede7: movsx esi, word ptr [esp + 0x1a] */
	m->ebp = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x1cu)));	/* 46edec: movsx ebp, word ptr [esp + 0x1c] */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x1eu)));	/* 46edf1: movsx eax, word ptr [esp + 0x1e] */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46edf6: shl esi, 3 */
	{ DWORD a_ = m->ebp, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 46edf9: shl ebp, 3 */
	{ DWORD a_ = m->eax, b_ = 0x81u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46edfc: sub eax, 0x81 */
	M32((DWORD)(m->esp + 0x24u)) = m->esi;	/* 46ee01: mov dword ptr [esp + 0x24], esi */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebp;	/* 46ee05: mov dword ptr [esp + 0x2c], ebp */
	if (m->zf) goto L_46ee31;	/* 46ee09: je 0x46ee31 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46ee0b: dec eax */
	if (m->zf) goto L_46ee27;	/* 46ee0c: je 0x46ee27 */
	{ DWORD v_ = 0x4c6fd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ee0e: push 0x4c6fd8 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 46ee13: push -1 */
	m->esp -= 4; M32(m->esp) = 0x46ee1au; native_call(m, 0x46e260u);	/* 46ee15: call 0x46e260 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ee1a: add esp, 8 */
	M32((DWORD)(m->esp + 0xcu)) = 0xffffffffu;	/* 46ee1d: mov dword ptr [esp + 0xc], 0xffffffff */
	goto L_46ee39;	/* 46ee25: jmp 0x46ee39 */
L_46ee27:
	M32((DWORD)(m->esp + 0xcu)) = 0x4u;	/* 46ee27: mov dword ptr [esp + 0xc], 4 */
	goto L_46ee39;	/* 46ee2f: jmp 0x46ee39 */
L_46ee31:
	M32((DWORD)(m->esp + 0xcu)) = 0x3u;	/* 46ee31: mov dword ptr [esp + 0xc], 3 */
L_46ee39:
	m->ecx = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x20u)));	/* 46ee39: movsx ecx, word ptr [esp + 0x20] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ee3e: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ee3f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46ee45u; native_call(m, 0x46e9b0u);	/* 46ee40: call 0x46e9b0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ee45: push edi */
	{ DWORD v_ = 0x10000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ee46: push 0x10000 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ee4b: push 1 */
	{ DWORD v_ = 0xaa2e98u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ee4d: push 0xaa2e98 */
	m->esp -= 4; M32(m->esp) = 0x46ee57u; native_call(m, 0x49e836u);	/* 46ee52: call 0x49e836 */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 46ee57: mov ecx, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46ee5b: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ee5d: add esp, 0x14 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 46ee60: xor ebx, ebx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 46ee62: xor edi, edi */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ee64: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 46ee66: mov dword ptr [esp + 0x14], eax */
	if (m->zf || m->sf != m->of) goto L_46ef0f;	/* 46ee6a: jle 0x46ef0f */
	{ long long p_ = (long long)(int)m->ebp * (int)m->esi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ebp = r_; }	/* 46ee70: imul ebp, esi */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebp;	/* 46ee73: mov dword ptr [esp + 0x2c], ebp */
	goto L_46ee7b;	/* 46ee77: jmp 0x46ee7b */
L_46ee79:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46ee79: xor eax, eax */
L_46ee7b:
	{ DWORD a_ = m->edi, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46ee7b: cmp edi, 3 */
	if (!m->cf && !m->zf) goto L_46ee98;	/* 46ee7e: ja 0x46ee98 */
	switch (m->edi) { case 0: goto L_46ee93; case 1: goto L_46ee87; case 2: goto L_46ee87; case 3: goto L_46ee93; default: abort(); }	/* 46ee80: jmp dword ptr [edi*4 + 0x46efb8] */
L_46ee87:
	M32((DWORD)(0xaa2e94u)) = 0x1u;	/* 46ee87: mov dword ptr [0xaa2e94], 1 */
	goto L_46ee98;	/* 46ee91: jmp 0x46ee98 */
L_46ee93:
	M32((DWORD)(0xaa2e94u)) = m->eax;	/* 46ee93: mov dword ptr [0xaa2e94], eax */
L_46ee98:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46ee98: mov edx, dword ptr [esp + 0x14] */
	m->esi = m->edi;	/* 46ee9c: mov esi, edi */
	{ DWORD a_ = m->esi, c_ = (0x10u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 46ee9e: shl esi, 0x10 */
	m->eax = (DWORD)(m->edx + 0xaa2e98u);	/* 46eea1: lea eax, [edx + 0xaa2e98] */
	{ DWORD a_ = m->esi, b_ = 0xa6228cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46eea7: add esi, 0xa6228c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46eead: push eax */
	m->esp -= 4; M32(m->esp) = 0x46eeb3u; native_call(m, 0x46f090u);	/* 46eeae: call 0x46f090 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eeb3: add esp, 4 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46eeb6: test ebp, ebp */
	if (m->zf || m->sf != m->of) goto L_46eee4;	/* 46eeb8: jle 0x46eee4 */
	{ DWORD a_ = m->ebp, b_ = 0x3fu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 46eeba: add ebp, 0x3f */
	{ DWORD a_ = m->ebp, c_ = (0x6u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ebp = r_; } }	/* 46eebd: shr ebp, 6 */
L_46eec0:
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 46eec0: lea ecx, [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46eec4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46eecau; native_call(m, 0x46f0b0u);	/* 46eec5: call 0x46f0b0 */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 46eeca: lea edx, [esp + 0x38] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46eece: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46eecf: push edx */
	m->ebx = m->eax;	/* 46eed0: mov ebx, eax */
	m->esp -= 4; M32(m->esp) = 0x46eed7u; native_call(m, 0x46e380u);	/* 46eed2: call 0x46e380 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46eed7: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46eeda: add esi, 0x40 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 46eedd: dec ebp */
	if (!m->zf) goto L_46eec0;	/* 46eede: jne 0x46eec0 */
	m->ebp = M32((DWORD)(m->esp + 0x2cu));	/* 46eee0: mov ebp, dword ptr [esp + 0x2c] */
L_46eee4:
	m->eax = (DWORD)(m->ebx + 0x7u);	/* 46eee4: lea eax, [ebx + 7] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 46eee7: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x7u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46eee8: and edx, 7 */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46eeeb: add eax, edx */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 46eeed: mov edx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 46eef1: sar eax, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 46eef4: add edx, eax */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 46eef6: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 46eefa: inc edi */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 46eefb: mov dword ptr [esp + 0x14], edx */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46eeff: cmp edi, eax */
	if (m->sf != m->of) goto L_46ee79;	/* 46ef01: jl 0x46ee79 */
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 46ef07: mov esi, dword ptr [esp + 0x28] */
	m->ebp = M32((DWORD)(m->esp + 0x30u));	/* 46ef0b: mov ebp, dword ptr [esp + 0x30] */
L_46ef0f:
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x22u)));	/* 46ef0f: movsx eax, word ptr [esp + 0x22] */
	{ DWORD a_ = m->eax, b_ = 0x81u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46ef14: sub eax, 0x81 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46ef19: pop ebx */
	if (m->zf) goto L_46ef36;	/* 46ef1a: je 0x46ef36 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46ef1c: dec eax */
	if (!m->zf) goto L_46ef4e;	/* 46ef1d: jne 0x46ef4e */
	m->eax = m->ebp;	/* 46ef1f: mov eax, ebp */
	{ long long p_ = (long long)(int)m->eax * (int)m->esi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->eax = r_; }	/* 46ef21: imul eax, esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef24: push eax */
	{ DWORD v_ = 0xa21708u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef25: push 0xa21708 */
	{ DWORD v_ = 0xa6228cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef2a: push 0xa6228c */
	m->esp -= 4; M32(m->esp) = 0x46ef34u; native_call(m, 0x46e8e0u);	/* 46ef2f: call 0x46e8e0 */
	goto L_46ef4b;	/* 46ef34: jmp 0x46ef4b */
L_46ef36:
	m->ecx = m->ebp;	/* 46ef36: mov ecx, ebp */
	{ long long p_ = (long long)(int)m->ecx * (int)m->esi; DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->ecx = r_; }	/* 46ef38: imul ecx, esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef3b: push ecx */
	{ DWORD v_ = 0xa21708u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef3c: push 0xa21708 */
	{ DWORD v_ = 0xa6228cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef41: push 0xa6228c */
	m->esp -= 4; M32(m->esp) = 0x46ef4bu; native_call(m, 0x46e830u);	/* 46ef46: call 0x46e830 */
L_46ef4b:
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ef4b: add esp, 0xc */
L_46ef4e:
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 46ef4e: mov edx, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->esp + 0x138u));	/* 46ef52: mov eax, dword ptr [esp + 0x138] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef59: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef5a: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef5b: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef5c: push eax */
	{ DWORD v_ = 0xa21708u; m->esp -= 4; M32(m->esp) = v_; }	/* 46ef5d: push 0xa21708 */
	m->esp -= 4; M32(m->esp) = 0x46ef67u; native_call(m, 0x46ea30u);	/* 46ef62: call 0x46ea30 */
	m->ecx = M32((DWORD)(m->esp + 0x154u));	/* 46ef67: mov ecx, dword ptr [esp + 0x154] */
	m->edx = M32((DWORD)(m->esp + 0x158u));	/* 46ef6e: mov edx, dword ptr [esp + 0x158] */
	m->eax = (DWORD)(int)(short)(M16((DWORD)(m->esp + 0x32u)));	/* 46ef75: movsx eax, word ptr [esp + 0x32] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ef7a: add esp, 0x14 */
	M32((DWORD)(m->ecx + 0x0u)) = m->esi;	/* 46ef7d: mov dword ptr [ecx], esi */
	M32((DWORD)(m->edx + 0x0u)) = m->ebp;	/* 46ef7f: mov dword ptr [edx], ebp */
	{ DWORD a_ = m->eax, b_ = 0x81u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46ef81: sub eax, 0x81 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46ef86: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46ef87: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46ef88: pop ebp */
	if (m->zf) goto L_46efa2;	/* 46ef89: je 0x46efa2 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 46ef8b: dec eax */
	if (!m->zf) goto L_46efaf;	/* 46ef8c: jne 0x46efaf */
	m->eax = M32((DWORD)(m->esp + 0x130u));	/* 46ef8e: mov eax, dword ptr [esp + 0x130] */
	M32((DWORD)(m->eax + 0x0u)) = 0x3u;	/* 46ef95: mov dword ptr [eax], 3 */
	{ DWORD a_ = m->esp, b_ = 0x124u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46ef9b: add esp, 0x124 */
	m->esp += 4 + 0; return;	/* 46efa1: ret  */
L_46efa2:
	m->ecx = M32((DWORD)(m->esp + 0x130u));	/* 46efa2: mov ecx, dword ptr [esp + 0x130] */
	M32((DWORD)(m->ecx + 0x0u)) = 0x2u;	/* 46efa9: mov dword ptr [ecx], 2 */
L_46efaf:
	{ DWORD a_ = m->esp, b_ = 0x124u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46efaf: add esp, 0x124 */
	m->esp += 4 + 0; return;	/* 46efb5: ret  */
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
