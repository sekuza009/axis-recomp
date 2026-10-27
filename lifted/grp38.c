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

static void lift_427b60(X86 *m);
static void lift_428a00(X86 *m);
static void lift_428b50(X86 *m);
static void lift_427a90(X86 *m);

/* menu_drawTexturedRect_427a90 (0x427a90), lifted by tools/lift.py */
static void lift_427a90(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427a90: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427a91: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 427a92: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427a93: push edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427a94: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x427a9fu; native_call(m, M32(0x4a9224u));	/* 427a99: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 427a9f: mov eax, dword ptr [esp + 0x24] */
	m->ecx = m->eax;	/* 427aa3: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427aa5: and ecx, 0x800001ff */
	if (!m->sf) goto L_427ab5;	/* 427aab: jns 0x427ab5 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 427aad: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427aae: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 427ab4: inc ecx */
L_427ab5:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 427ab5: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 427ab6: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427abc: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427abd: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 427abf: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 427ac5: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 427ac8: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x427ad1u; native_call(m, 0x4566c0u);	/* 427acc: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 427ad1: push 7 */
	m->esp -= 4; M32(m->esp) = 0x427ad9u; native_call(m, M32(0x4a921cu));	/* 427ad3: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 427ad9: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427adf: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427ae1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x427ae5u; native_call(m, m->esi);	/* 427ae3: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 427ae5: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 427ae9: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427aed: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427aee: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427af4u; native_call(m, 0x41ef60u);	/* 427aef: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427af4: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427af7: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427af9: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x427b00u; native_call(m, m->esi);	/* 427afe: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427b00: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 427b01: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427b05: push edi */
	m->esp -= 4; M32(m->esp) = 0x427b0bu; native_call(m, 0x41ef60u);	/* 427b06: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427b0b: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427b0e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427b13: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x427b1au; native_call(m, m->esi);	/* 427b18: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 427b1a: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427b1e: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427b1f: push edi */
	m->esp -= 4; M32(m->esp) = 0x427b25u; native_call(m, 0x41ef60u);	/* 427b20: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427b25: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427b28: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427b2d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x427b31u; native_call(m, m->esi);	/* 427b2f: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427b31: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427b32: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427b38u; native_call(m, 0x41ef60u);	/* 427b33: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427b38: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x427b41u; native_call(m, M32(0x4a9220u));	/* 427b3b: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427b41: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x427b4cu; native_call(m, M32(0x4a922cu));	/* 427b46: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 427b4c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 427b4d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 427b4e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 427b4f: pop ebx */
	m->esp += 4 + 0; return;	/* 427b50: ret  */
}

/* menu_drawTexturedRect_427b60 (0x427b60), lifted by tools/lift.py */
static void lift_427b60(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427b60: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427b61: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 427b62: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427b63: push edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427b64: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x427b6fu; native_call(m, M32(0x4a9224u));	/* 427b69: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 427b6f: mov eax, dword ptr [esp + 0x24] */
	m->ecx = m->eax;	/* 427b73: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427b75: and ecx, 0x800001ff */
	if (!m->sf) goto L_427b85;	/* 427b7b: jns 0x427b85 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 427b7d: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427b7e: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 427b84: inc ecx */
L_427b85:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 427b85: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 427b86: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427b8c: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427b8d: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 427b8f: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 427b95: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 427b98: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x427ba1u; native_call(m, 0x4566c0u);	/* 427b9c: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 427ba1: push 7 */
	m->esp -= 4; M32(m->esp) = 0x427ba9u; native_call(m, M32(0x4a921cu));	/* 427ba3: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 427ba9: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427baf: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427bb4: push 0 */
	m->esp -= 4; M32(m->esp) = 0x427bb8u; native_call(m, m->esi);	/* 427bb6: call esi */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 427bb8: mov edi, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 427bbc: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427bc0: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427bc1: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427bc7u; native_call(m, 0x41ef60u);	/* 427bc2: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427bc7: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427bca: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427bcf: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x427bd6u; native_call(m, m->esi);	/* 427bd4: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427bd6: push edi */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 427bd7: mov edi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427bdb: push edi */
	m->esp -= 4; M32(m->esp) = 0x427be1u; native_call(m, 0x41ef60u);	/* 427bdc: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427be1: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427be4: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427be6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x427bedu; native_call(m, m->esi);	/* 427beb: call esi */
	m->ebp = M32((DWORD)(m->esp + 0x20u));	/* 427bed: mov ebp, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427bf1: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 427bf2: push edi */
	m->esp -= 4; M32(m->esp) = 0x427bf8u; native_call(m, 0x41ef60u);	/* 427bf3: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427bf8: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427bfb: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427bfd: push 0 */
	m->esp -= 4; M32(m->esp) = 0x427c01u; native_call(m, m->esi);	/* 427bff: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 427c01: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 427c02: push ebx */
	m->esp -= 4; M32(m->esp) = 0x427c08u; native_call(m, 0x41ef60u);	/* 427c03: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427c08: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x427c11u; native_call(m, M32(0x4a9220u));	/* 427c0b: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427c11: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x427c1cu; native_call(m, M32(0x4a922cu));	/* 427c16: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 427c1c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 427c1d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 427c1e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 427c1f: pop ebx */
	m->esp += 4 + 0; return;	/* 427c20: ret  */
}

/* menu_drawTexturedRect_428a00 (0x428a00), lifted by tools/lift.py */
static void lift_428a00(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428a00: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428a01: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428a02: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428a03: push edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428a04: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x428a0fu; native_call(m, M32(0x4a9224u));	/* 428a09: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x4deb4cu));	/* 428a0f: mov eax, dword ptr [0x4deb4c] */
	m->ecx = m->eax;	/* 428a14: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 428a16: and ecx, 0x800001ff */
	if (!m->sf) goto L_428a26;	/* 428a1c: jns 0x428a26 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 428a1e: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 428a1f: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 428a25: inc ecx */
L_428a26:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 428a26: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 428a27: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428a2d: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 428a2e: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 428a30: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 428a36: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 428a39: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x428a42u; native_call(m, 0x4566c0u);	/* 428a3d: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 428a42: push 7 */
	m->esp -= 4; M32(m->esp) = 0x428a4au; native_call(m, M32(0x4a921cu));	/* 428a44: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 428a4a: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428a50: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428a52: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428a56u; native_call(m, m->esi);	/* 428a54: call esi */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 428a56: mov eax, dword ptr [esp + 0x18] */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 428a5a: mov ebp, dword ptr [esp + 0x14] */
	m->edi = (DWORD)(m->eax + 0xffffffeeu);	/* 428a5e: lea edi, [eax - 0x12] */
	m->ebx = (DWORD)(m->ebp + 0xffffffe2u);	/* 428a61: lea ebx, [ebp - 0x1e] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428a64: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428a65: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428a6bu; native_call(m, 0x41ef60u);	/* 428a66: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428a6b: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428a6e: push 0 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428a70: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x428a77u; native_call(m, m->esi);	/* 428a75: call esi */
	{ DWORD a_ = m->ebp, b_ = 0x62u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 428a77: add ebp, 0x62 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428a7a: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428a7b: push ebp */
	m->esp -= 4; M32(m->esp) = 0x428a81u; native_call(m, 0x41ef60u);	/* 428a7c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428a81: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428a84: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428a89: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x428a90u; native_call(m, m->esi);	/* 428a8e: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 428a90: mov ecx, dword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->ecx + 0x6eu);	/* 428a94: lea edi, [ecx + 0x6e] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428a97: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428a98: push ebp */
	m->esp -= 4; M32(m->esp) = 0x428a9eu; native_call(m, 0x41ef60u);	/* 428a99: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428a9e: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428aa1: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428aa6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x428aaau; native_call(m, m->esi);	/* 428aa8: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428aaa: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428aab: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428ab1u; native_call(m, 0x41ef60u);	/* 428aac: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428ab1: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428abau; native_call(m, M32(0x4a9220u));	/* 428ab4: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 428aba: push 7 */
	m->esp -= 4; M32(m->esp) = 0x428ac2u; native_call(m, M32(0x4a921cu));	/* 428abc: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428ac2: push 0 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428ac4: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x428acbu; native_call(m, m->esi);	/* 428ac9: call esi */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 428acb: mov edx, dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 428acf: mov ebp, dword ptr [esp + 0x1c] */
	m->edi = (DWORD)(m->edx + 0xffffff9cu);	/* 428ad3: lea edi, [edx - 0x64] */
	m->ebx = (DWORD)(m->ebp + 0xffffff9au);	/* 428ad6: lea ebx, [ebp - 0x66] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428ad9: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428ada: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428ae0u; native_call(m, 0x41ef60u);	/* 428adb: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428ae0: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 428ae3: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428ae5: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x428aecu; native_call(m, m->esi);	/* 428aea: call esi */
	{ DWORD a_ = m->ebp, b_ = 0x1au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 428aec: add ebp, 0x1a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428aef: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428af0: push ebp */
	m->esp -= 4; M32(m->esp) = 0x428af6u; native_call(m, 0x41ef60u);	/* 428af1: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428af6: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428af9: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428afe: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x428b05u; native_call(m, m->esi);	/* 428b03: call esi */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 428b05: mov eax, dword ptr [esp + 0x20] */
	m->edi = (DWORD)(m->eax + 0x1cu);	/* 428b09: lea edi, [eax + 0x1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428b0c: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428b0d: push ebp */
	m->esp -= 4; M32(m->esp) = 0x428b13u; native_call(m, 0x41ef60u);	/* 428b0e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428b13: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428b16: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428b1b: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x428b22u; native_call(m, m->esi);	/* 428b20: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428b22: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428b23: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428b29u; native_call(m, 0x41ef60u);	/* 428b24: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428b29: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428b32u; native_call(m, M32(0x4a9220u));	/* 428b2c: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428b32: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x428b3du; native_call(m, M32(0x4a922cu));	/* 428b37: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 428b3d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 428b3e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 428b3f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 428b40: pop ebx */
	m->esp += 4 + 0; return;	/* 428b41: ret  */
}

/* menu_drawTexturedRect_428b50 (0x428b50), lifted by tools/lift.py */
static void lift_428b50(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428b50: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428b51: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 428b52: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428b53: push edi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428b54: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x428b5fu; native_call(m, M32(0x4a9224u));	/* 428b59: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x4deb4cu));	/* 428b5f: mov eax, dword ptr [0x4deb4c] */
	m->ecx = m->eax;	/* 428b64: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 428b66: and ecx, 0x800001ff */
	if (!m->sf) goto L_428b76;	/* 428b6c: jns 0x428b76 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 428b6e: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 428b6f: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 428b75: inc ecx */
L_428b76:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 428b76: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 428b77: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 428b7d: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 428b7e: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 428b80: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 428b86: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 428b89: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x428b92u; native_call(m, 0x4566c0u);	/* 428b8d: call 0x4566c0 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 428b92: push 7 */
	m->esp -= 4; M32(m->esp) = 0x428b9au; native_call(m, M32(0x4a921cu));	/* 428b94: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 428b9a: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428ba0: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428ba5: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x428bacu; native_call(m, m->esi);	/* 428baa: call esi */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 428bac: mov eax, dword ptr [esp + 0x18] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 428bb0: mov ebp, dword ptr [esp + 0x1c] */
	m->edi = (DWORD)(m->eax + 0xffffffeeu);	/* 428bb4: lea edi, [eax - 0x12] */
	m->ebx = (DWORD)(m->ebp + 0xffffff8eu);	/* 428bb7: lea ebx, [ebp - 0x72] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428bba: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428bbb: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428bc1u; native_call(m, 0x41ef60u);	/* 428bbc: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428bc1: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428bc4: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428bc9: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x428bd0u; native_call(m, m->esi);	/* 428bce: call esi */
	{ DWORD a_ = m->ebp, b_ = 0xeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 428bd0: add ebp, 0xe */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428bd3: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428bd4: push ebp */
	m->esp -= 4; M32(m->esp) = 0x428bdau; native_call(m, 0x41ef60u);	/* 428bd5: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428bda: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428bdd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428be2: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x428be9u; native_call(m, m->esi);	/* 428be7: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 428be9: mov ecx, dword ptr [esp + 0x18] */
	m->edi = (DWORD)(m->ecx + 0x6eu);	/* 428bed: lea edi, [ecx + 0x6e] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428bf0: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 428bf1: push ebp */
	m->esp -= 4; M32(m->esp) = 0x428bf7u; native_call(m, 0x41ef60u);	/* 428bf2: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428bf7: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428bfa: push 0x3f800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 428bff: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x428c06u; native_call(m, m->esi);	/* 428c04: call esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 428c06: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 428c07: push ebx */
	m->esp -= 4; M32(m->esp) = 0x428c0du; native_call(m, 0x41ef60u);	/* 428c08: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 428c0d: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x428c16u; native_call(m, M32(0x4a9220u));	/* 428c10: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 428c16: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x428c21u; native_call(m, M32(0x4a922cu));	/* 428c1b: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 428c21: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 428c22: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 428c23: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 428c24: pop ebx */
	m->esp += 4 + 0; return;	/* 428c25: ret  */
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
