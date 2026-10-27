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

static void lift_4699d0(X86 *m);

/* skel_loadFrom (0x4699d0), lifted by tools/lift.py */
static void lift_4699d0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4699d0: sub esp, 0x10c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4699d6: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x114u));	/* 4699d7: mov ebp, dword ptr [esp + 0x114] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4699de: push esi */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 4699df: push 0x4ad170 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 4699e4: mov dword ptr [esp + 0x14], ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4699e8: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4699eeu; native_call(m, 0x49e9cau);	/* 4699e9: call 0x49e9ca */
	m->esi = m->eax;	/* 4699ee: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4699f0: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4699f3: test esi, esi */
	M32((DWORD)(m->esp + 0xcu)) = m->esi;	/* 4699f5: mov dword ptr [esp + 0xc], esi */
	if (!m->zf) goto L_469a0e;	/* 4699f9: jne 0x469a0e */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4699fb: push ebp */
	{ DWORD v_ = 0x4c4ae4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4699fc: push 0x4c4ae4 */
	{ DWORD v_ = 0xa0eaa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 469a01: push 0xa0eaa8 */
	m->esp -= 4; M32(m->esp) = 0x469a0bu; native_call(m, 0x46c710u);	/* 469a06: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469a0b: add esp, 0xc */
L_469a0e:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 469a0e: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 469a0f: push edi */
	m->edi = m->ebp;	/* 469a10: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469a12: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469a15: xor eax, eax */
	M32((DWORD)(m->esp + 0x10u)) = 0xffffffffu;	/* 469a17: mov dword ptr [esp + 0x10], 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 469a1f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 469a21: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 469a23: dec ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 469a24: dec ecx */
	if (m->sf) goto L_469af2;	/* 469a25: js 0x469af2 */
L_469a2b:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + m->ebp*1 + 0x0u))) & 0xff) << 0);	/* 469a2b: mov al, byte ptr [ecx + ebp] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2eu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469a2e: cmp al, 0x2e */
	if (m->zf) goto L_469a4a;	/* 469a30: je 0x469a4a */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x5cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469a32: cmp al, 0x5c */
	if (m->zf) goto L_469af2;	/* 469a34: je 0x469af2 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2fu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 469a3a: cmp al, 0x2f */
	if (m->zf) goto L_469af2;	/* 469a3c: je 0x469af2 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 469a42: dec ecx */
	if (!m->sf) goto L_469a2b;	/* 469a43: jns 0x469a2b */
	goto L_469af2;	/* 469a45: jmp 0x469af2 */
L_469a4a:
	m->edi = (DWORD)(m->ecx + m->ebp*1 + 0x1u);	/* 469a4a: lea edi, [ecx + ebp + 1] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469a4e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 469a51: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 469a53: lea edx, [esp + 0x1c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 469a57: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 469a59: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 469a5b: sub edi, ecx */
	m->eax = m->ecx;	/* 469a5d: mov eax, ecx */
	m->esi = m->edi;	/* 469a5f: mov esi, edi */
	m->edi = m->edx;	/* 469a61: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 469a63: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 469a66: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 469a68: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469a6a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 469a6d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x1cu)));	/* 469a6f: movsx esi, byte ptr [esp + 0x1c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469a74: push esi */
	m->esp -= 4; M32(m->esp) = 0x469a7au; native_call(m, 0x49fdafu);	/* 469a75: call 0x49fdaf */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x22u))) & 0xff) << 0);	/* 469a7a: mov bl, byte ptr [esp + 0x22] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469a7e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x73u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469a81: cmp eax, 0x73 */
	if (!m->zf) goto L_469ab4;	/* 469a84: jne 0x469ab4 */
	m->ecx = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x1du)));	/* 469a86: movsx ecx, byte ptr [esp + 0x1d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469a8b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x469a91u; native_call(m, 0x49fdafu);	/* 469a8c: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469a91: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x6bu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469a94: cmp eax, 0x6b */
	if (!m->zf) goto L_469ab4;	/* 469a97: jne 0x469ab4 */
	m->edx = (DWORD)(int)(signed char)(((m->ebx >> 0) & 0xff));	/* 469a99: movsx edx, bl */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469a9c: push edx */
	m->esp -= 4; M32(m->esp) = 0x469aa2u; native_call(m, 0x49fdafu);	/* 469a9d: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469aa2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x65u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469aa5: cmp eax, 0x65 */
	if (!m->zf) goto L_469ab4;	/* 469aa8: jne 0x469ab4 */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 469aaa: mov dword ptr [esp + 0x10], 0 */
	goto L_469aee;	/* 469ab2: jmp 0x469aee */
L_469ab4:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469ab4: push esi */
	m->esp -= 4; M32(m->esp) = 0x469abau; native_call(m, 0x49fdafu);	/* 469ab5: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469aba: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x61u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469abd: cmp eax, 0x61 */
	if (!m->zf) goto L_469aee;	/* 469ac0: jne 0x469aee */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esp + 0x1du)));	/* 469ac2: movsx eax, byte ptr [esp + 0x1d] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469ac7: push eax */
	m->esp -= 4; M32(m->esp) = 0x469acdu; native_call(m, 0x49fdafu);	/* 469ac8: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469acd: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x73u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469ad0: cmp eax, 0x73 */
	if (!m->zf) goto L_469aee;	/* 469ad3: jne 0x469aee */
	m->ecx = (DWORD)(int)(signed char)(((m->ebx >> 0) & 0xff));	/* 469ad5: movsx ecx, bl */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469ad8: push ecx */
	m->esp -= 4; M32(m->esp) = 0x469adeu; native_call(m, 0x49fdafu);	/* 469ad9: call 0x49fdaf */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469ade: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x65u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469ae1: cmp eax, 0x65 */
	if (!m->zf) goto L_469aee;	/* 469ae4: jne 0x469aee */
	M32((DWORD)(m->esp + 0x10u)) = 0x1u;	/* 469ae6: mov dword ptr [esp + 0x10], 1 */
L_469aee:
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 469aee: mov esi, dword ptr [esp + 0x14] */
L_469af2:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 469af2: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32(m->esp); m->esp += 4;	/* 469af6: pop edi */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 469af7: sub eax, 0 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 469afa: pop ebx */
	if (m->zf) goto L_469b55;	/* 469afb: je 0x469b55 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 469afd: dec eax */
	if (m->zf) goto L_469b27;	/* 469afe: je 0x469b27 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 469b00: push ebp */
	{ DWORD v_ = 0x4c4aa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 469b01: push 0x4c4aa4 */
	{ DWORD v_ = 0xa0eaa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 469b06: push 0xa0eaa8 */
	m->esp -= 4; M32(m->esp) = 0x469b10u; native_call(m, 0x46c710u);	/* 469b0b: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469b10: add esp, 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469b13: push esi */
	m->esp -= 4; M32(m->esp) = 0x469b19u; native_call(m, 0x49e7e0u);	/* 469b14: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469b19: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 469b1c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 469b1d: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469b1e: add esp, 0x10c */
	m->esp += 4 + 12; return;	/* 469b24: ret 0xc */
L_469b27:
	m->edx = M32((DWORD)(m->esp + 0x120u));	/* 469b27: mov edx, dword ptr [esp + 0x120] */
	m->eax = M32((DWORD)(m->esp + 0x11cu));	/* 469b2e: mov eax, dword ptr [esp + 0x11c] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 469b35: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469b39: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469b3a: push eax */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469b3b: push esi */
	m->esp -= 4; M32(m->esp) = 0x469b41u; native_call(m, 0x469b90u);	/* 469b3c: call 0x469b90 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469b41: push esi */
	m->esp -= 4; M32(m->esp) = 0x469b47u; native_call(m, 0x49e7e0u);	/* 469b42: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469b47: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 469b4a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 469b4b: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469b4c: add esp, 0x10c */
	m->esp += 4 + 12; return;	/* 469b52: ret 0xc */
L_469b55:
	m->ecx = M32((DWORD)(m->esp + 0x120u));	/* 469b55: mov ecx, dword ptr [esp + 0x120] */
	m->edx = M32((DWORD)(m->esp + 0x11cu));	/* 469b5c: mov edx, dword ptr [esp + 0x11c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 469b63: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 469b64: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 469b68: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469b69: push esi */
	m->esp -= 4; M32(m->esp) = 0x469b6fu; native_call(m, 0x46aa10u);	/* 469b6a: call 0x46aa10 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469b6f: push esi */
	m->esp -= 4; M32(m->esp) = 0x469b75u; native_call(m, 0x49e7e0u);	/* 469b70: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469b75: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 469b78: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 469b79: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x10cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469b7a: add esp, 0x10c */
	m->esp += 4 + 12; return;	/* 469b80: ret 0xc */
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
