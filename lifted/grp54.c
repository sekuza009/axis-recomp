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

static void lift_485af0(X86 *m);

/* render_drawObjects (0x485af0), lifted by tools/lift.py */
static void lift_485af0(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 485af0: push ebp */
	m->ebp = m->esp;	/* 485af1: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 485af3: and esp, 0xfffffff8 */
	m->eax = 0x20dcu;	/* 485af6: mov eax, 0x20dc */
	m->esp -= 4; M32(m->esp) = 0x485b00u; native_call(m, 0x49fc20u);	/* 485afb: call 0x49fc20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 485b00: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 485b01: push esi */
	m->eax = (DWORD)(m->esp + 0x164u);	/* 485b02: lea eax, [esp + 0x164] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 485b09: push edi */
	m->edi = M32((DWORD)(0x4a9270u));	/* 485b0a: mov edi, dword ptr [0x4a9270] */
	m->esi = m->ecx;	/* 485b10: mov esi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485b12: push eax */
	{ DWORD v_ = 0xba7u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b13: push 0xba7 */
	M32((DWORD)(m->esp + 0x1cu)) = m->esi;	/* 485b18: mov dword ptr [esp + 0x1c], esi */
	M32((DWORD)(m->esp + 0x3cu)) = 0x0u;	/* 485b1c: mov dword ptr [esp + 0x3c], 0 */
	M32((DWORD)(m->esp + 0x40u)) = 0x0u;	/* 485b24: mov dword ptr [esp + 0x40], 0 */
	M32((DWORD)(m->esp + 0x5cu)) = 0x0u;	/* 485b2c: mov dword ptr [esp + 0x5c], 0 */
	M32((DWORD)(m->esp + 0x60u)) = 0x0u;	/* 485b34: mov dword ptr [esp + 0x60], 0 */
	m->esp -= 4; M32(m->esp) = 0x485b3eu; native_call(m, m->edi);	/* 485b3c: call edi */
	m->ecx = (DWORD)(m->esp + 0x128u);	/* 485b3e: lea ecx, [esp + 0x128] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 485b45: push ecx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b46: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x485b4du; native_call(m, m->edi);	/* 485b4b: call edi */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485b4d: cmp dword ptr [ebp + 8], 1 */
	if (!m->zf) goto L_485b7d;	/* 485b51: jne 0x485b7d */
	{ DWORD v_ = 0x1b01u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b53: push 0x1b01 */
	{ DWORD v_ = 0x408u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b58: push 0x408 */
	m->esp -= 4; M32(m->esp) = 0x485b63u; native_call(m, M32(0x4a91c4u));	/* 485b5d: call dword ptr [0x4a91c4] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b63: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b68: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b6d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b72: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x485b7du; native_call(m, M32(0x4a9228u));	/* 485b77: call dword ptr [0x4a9228] */
L_485b7d:
	m->edx = (DWORD)(m->esp + 0xfu);	/* 485b7d: lea edx, [esp + 0xf] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485b81: push edx */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b82: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x485b8du; native_call(m, M32(0x4a9250u));	/* 485b87: call dword ptr [0x4a9250] */
	{ DWORD a_ = M8((DWORD)(m->esp + 0xfu)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 485b8d: cmp byte ptr [esp + 0xf], 1 */
	if (!m->zf) goto L_485c1c;	/* 485b92: jne 0x485c1c */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 485b98: lea eax, [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485b9c: push eax */
	{ DWORD v_ = 0xb63u; m->esp -= 4; M32(m->esp) = v_; }	/* 485b9d: push 0xb63 */
	m->esp -= 4; M32(m->esp) = 0x485ba4u; native_call(m, m->edi);	/* 485ba2: call edi */
	m->ecx = (DWORD)(m->esp + 0x38u);	/* 485ba4: lea ecx, [esp + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 485ba8: push ecx */
	{ DWORD v_ = 0xb64u; m->esp -= 4; M32(m->esp) = v_; }	/* 485ba9: push 0xb64 */
	m->esp -= 4; M32(m->esp) = 0x485bb0u; native_call(m, m->edi);	/* 485bae: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 485bb0: fld dword ptr [esp + 0x34] */
	ST(0) = -ST(0);	/* 485bb4: fchs  */
	{ long double t = ST(0); FPUSH(t); }	/* 485bb6: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x90d8u));	/* 485bb8: fmul dword ptr [esi + 0x90d8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x90e8u));	/* 485bbe: fadd dword ptr [esi + 0x90e8] */
	MF((DWORD)(m->esp + 0xe0u)) = (float)ST(0); FPOP();	/* 485bc4: fstp dword ptr [esp + 0xe0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x90dcu));	/* 485bcb: fmul dword ptr [esi + 0x90dc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x90ecu));	/* 485bd1: fadd dword ptr [esi + 0x90ec] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe0u)));	/* 485bd7: fld dword ptr [esp + 0xe0] */
	ST(0) = ST(0) / ST(1);	/* 485bde: fdiv st(1) */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 485be0: fstp dword ptr [esp + 0x54] */
	ST(0) = ST(0); FPOP();	/* 485be4: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 485be6: fld dword ptr [esp + 0x38] */
	ST(0) = -ST(0);	/* 485bea: fchs  */
	{ long double t = ST(0); FPUSH(t); }	/* 485bec: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x90d8u));	/* 485bee: fmul dword ptr [esi + 0x90d8] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x90e8u));	/* 485bf4: fadd dword ptr [esi + 0x90e8] */
	MF((DWORD)(m->esp + 0xe0u)) = (float)ST(0); FPOP();	/* 485bfa: fstp dword ptr [esp + 0xe0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x90dcu));	/* 485c01: fmul dword ptr [esi + 0x90dc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x90ecu));	/* 485c07: fadd dword ptr [esi + 0x90ec] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0xe0u)));	/* 485c0d: fld dword ptr [esp + 0xe0] */
	ST(0) = ST(0) / ST(1);	/* 485c14: fdiv st(1) */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 485c16: fstp dword ptr [esp + 0x58] */
	ST(0) = ST(0); FPOP();	/* 485c1a: fstp st(0) */
L_485c1c:
	m->edi = M32((DWORD)(0x4a91fcu));	/* 485c1c: mov edi, dword ptr [0x4a91fc] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 485c22: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x485c29u; native_call(m, m->edi);	/* 485c27: call edi */
	m->ebx = M32((DWORD)(0x4a926cu));	/* 485c29: mov ebx, dword ptr [0x4a926c] */
	m->eax = (DWORD)(m->esi + 0x90b0u);	/* 485c2f: lea eax, [esi + 0x90b0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485c35: push eax */
	m->esp -= 4; M32(m->esp) = 0x485c38u; native_call(m, m->ebx);	/* 485c36: call ebx */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 485c38: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x485c3fu; native_call(m, m->edi);	/* 485c3d: call edi */
	m->eax = (DWORD)(m->esi + 0x90f0u);	/* 485c3f: lea eax, [esi + 0x90f0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485c45: push eax */
	m->esp -= 4; M32(m->esp) = 0x485c48u; native_call(m, m->ebx);	/* 485c46: call ebx */
	{ DWORD a_ = M8((DWORD)(m->esp + 0xfu)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 485c48: cmp byte ptr [esp + 0xf], 1 */
	if (!m->zf) goto L_485c7c;	/* 485c4d: jne 0x485c7c */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 485c4f: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485c53: push edx */
	{ DWORD v_ = 0xb63u; m->esp -= 4; M32(m->esp) = v_; }	/* 485c54: push 0xb63 */
	m->esp -= 4; M32(m->esp) = 0x485c5fu; native_call(m, M32(0x4a9280u));	/* 485c59: call dword ptr [0x4a9280] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 485c5f: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485c63: push eax */
	{ DWORD v_ = 0xb64u; m->esp -= 4; M32(m->esp) = v_; }	/* 485c64: push 0xb64 */
	m->esp -= 4; M32(m->esp) = 0x485c6fu; native_call(m, M32(0x4a9280u));	/* 485c69: call dword ptr [0x4a9280] */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 485c6f: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x485c7au; native_call(m, M32(0x4a9224u));	/* 485c74: call dword ptr [0x4a9224] */
	goto L_485c87;	/* 485c7a: jmp 0x485c87 */
L_485c7c:
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 485c7c: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x485c87u; native_call(m, M32(0x4a922cu));	/* 485c81: call dword ptr [0x4a922c] */
L_485c87:
	m->ecx = M32((DWORD)(m->esi + 0x3024u));	/* 485c87: mov ecx, dword ptr [esi + 0x3024] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 485c8d: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485c8f: cmp ecx, eax */
	M32((DWORD)(m->esi + 0x9050u)) = m->eax;	/* 485c91: mov dword ptr [esi + 0x9050], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 485c97: mov dword ptr [esp + 0x20], eax */
	if (m->zf || m->sf != m->of) goto L_48692a;	/* 485c9b: jle 0x48692a */
L_485ca1:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 485ca1: mov ecx, dword ptr [esp + 0x20] */
	m->ebx = M32((DWORD)(m->esi + m->ecx*4 + 0x20u));	/* 485ca5: mov ebx, dword ptr [esi + ecx*4 + 0x20] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485ca9: test ebx, ebx */
	m->edi = M32((DWORD)(m->esi + m->ebx*4 + 0x3028u));	/* 485cab: mov edi, dword ptr [esi + ebx*4 + 0x3028] */
	M32((DWORD)(m->esp + 0x24u)) = m->ebx;	/* 485cb2: mov dword ptr [esp + 0x24], ebx */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 485cb6: mov dword ptr [esp + 0x10], edi */
	if (m->zf || m->sf != m->of) goto L_485d04;	/* 485cba: jle 0x485d04 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485cbc: cmp dword ptr [ebp + 8], 2 */
	if (m->zf) goto L_485d04;	/* 485cc0: je 0x485d04 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 485cc2: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x485ccdu; native_call(m, M32(0x4a9224u));	/* 485cc7: call dword ptr [0x4a9224] */
	m->eax = (DWORD)(m->ebx + 0xffffffffu);	/* 485ccd: lea eax, [ebx - 1] */
	m->edx = m->eax;	/* 485cd0: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 485cd2: and edx, 0x800001ff */
	if (!m->sf) goto L_485ce2;	/* 485cd8: jns 0x485ce2 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 485cda: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 485cdb: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 485ce1: inc edx */
L_485ce2:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485ce2: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 485ce3: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 485ce9: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 485cea: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 485cf0: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 485cf2: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 485cf5: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x485cfeu; native_call(m, 0x4566c0u);	/* 485cf9: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x90acu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x90acu)) = r_; }	/* 485cfe: inc dword ptr [esi + 0x90ac] */
L_485d04:
	m->edx = M32((DWORD)(m->esi + 0x90a8u));	/* 485d04: mov edx, dword ptr [esi + 0x90a8] */
	m->ebx = M32((DWORD)(m->edi + 0x0u));	/* 485d0a: mov ebx, dword ptr [edi] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 485d0c: inc edx */
	M32((DWORD)(m->esi + 0x90a8u)) = m->edx;	/* 485d0d: mov dword ptr [esi + 0x90a8], edx */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 485d13: mov eax, dword ptr [edi + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485d16: test eax, eax */
	if (m->zf) goto L_485ec8;	/* 485d18: je 0x485ec8 */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x0u)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 485d1e: test byte ptr [ebx], 2 */
	if (!m->zf) goto L_485ec1;	/* 485d21: jne 0x485ec1 */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 485d27: mov ecx, dword ptr [edi + 8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485d2a: test ecx, ecx */
	if (m->zf) goto L_485e4b;	/* 485d2c: je 0x485e4b */
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 485d32: mov eax, dword ptr [ebx + 0x4c] */
	m->ecx = M32((DWORD)(m->esi + 0x9048u));	/* 485d35: mov ecx, dword ptr [esi + 0x9048] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485d3b: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_4868ec;	/* 485d3d: jg 0x4868ec */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9050u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485d43: cmp dword ptr [esi + 0x9050], eax */
	if (m->sf == m->of) goto L_485d51;	/* 485d49: jge 0x485d51 */
	M32((DWORD)(m->esi + 0x9050u)) = m->eax;	/* 485d4b: mov dword ptr [esi + 0x9050], eax */
L_485d51:
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 485d51: mov ecx, dword ptr [ebx + 0x4c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 485d54: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 485d58: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->edx + 0x904cu));	/* 485d5c: mov edi, dword ptr [edx + 0x904c] */
	m->esi = M32((DWORD)(m->eax + 0x4u));	/* 485d62: mov esi, dword ptr [eax + 4] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 485d65: shl ecx, 2 */
	m->edx = m->ecx;	/* 485d68: mov edx, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 485d6a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 485d6d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 485d6f: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 485d71: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 485d74: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(m->eax + 0x10u));	/* 485d76: mov eax, dword ptr [eax + 0x10] */
	m->ecx = (DWORD)(m->esp + 0x70u);	/* 485d79: lea ecx, [esp + 0x70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485d7d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 485d7e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x485d84u; native_call(m, 0x47d740u);	/* 485d7f: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485d84: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485d87: test eax, eax */
	if (!m->zf) goto L_485dff;	/* 485d89: jne 0x485dff */
	M32((DWORD)(m->esp + 0x70u)) = 0x3f800000u;	/* 485d8b: mov dword ptr [esp + 0x70], 0x3f800000 */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 485d93: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x90u)) = m->eax;	/* 485d9a: mov dword ptr [esp + 0x90], eax */
	M32((DWORD)(m->esp + 0xa0u)) = m->eax;	/* 485da1: mov dword ptr [esp + 0xa0], eax */
	M32((DWORD)(m->esp + 0x74u)) = m->eax;	/* 485da8: mov dword ptr [esp + 0x74], eax */
	M32((DWORD)(m->esp + 0x84u)) = 0x3f800000u;	/* 485dac: mov dword ptr [esp + 0x84], 0x3f800000 */
	M32((DWORD)(m->esp + 0x94u)) = m->eax;	/* 485db7: mov dword ptr [esp + 0x94], eax */
	M32((DWORD)(m->esp + 0xa4u)) = m->eax;	/* 485dbe: mov dword ptr [esp + 0xa4], eax */
	M32((DWORD)(m->esp + 0x78u)) = m->eax;	/* 485dc5: mov dword ptr [esp + 0x78], eax */
	M32((DWORD)(m->esp + 0x88u)) = m->eax;	/* 485dc9: mov dword ptr [esp + 0x88], eax */
	M32((DWORD)(m->esp + 0x98u)) = 0x3f800000u;	/* 485dd0: mov dword ptr [esp + 0x98], 0x3f800000 */
	M32((DWORD)(m->esp + 0xa8u)) = m->eax;	/* 485ddb: mov dword ptr [esp + 0xa8], eax */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 485de2: mov dword ptr [esp + 0x7c], eax */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 485de6: mov dword ptr [esp + 0x8c], eax */
	M32((DWORD)(m->esp + 0x9cu)) = m->eax;	/* 485ded: mov dword ptr [esp + 0x9c], eax */
	M32((DWORD)(m->esp + 0xacu)) = 0x3f800000u;	/* 485df4: mov dword ptr [esp + 0xac], 0x3f800000 */
L_485dff:
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 485dff: mov edi, dword ptr [esp + 0x10] */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 485e03: mov esi, dword ptr [esp + 0x14] */
	m->edx = (DWORD)(m->esp + 0x70u);	/* 485e07: lea edx, [esp + 0x70] */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 485e0b: mov eax, dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->esi + 0x904cu));	/* 485e0e: mov ecx, dword ptr [esi + 0x904c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485e14: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485e15: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 485e16: push ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 485e17: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 485e19: push ecx */
	m->esp -= 4; M32(m->esp) = 0x485e1fu; native_call(m, 0x463b80u);	/* 485e1a: call 0x463b80 */
	m->eax = M32((DWORD)(m->edi + 0xcu));	/* 485e1f: mov eax, dword ptr [edi + 0xc] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485e22: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485e25: test eax, eax */
	if (m->zf) goto L_485e3c;	/* 485e27: je 0x485e3c */
	m->edx = M32((DWORD)(m->esi + 0x904cu));	/* 485e29: mov edx, dword ptr [esi + 0x904c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485e2f: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 485e30: push ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 485e31: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485e33: push edx */
	m->esp -= 4; M32(m->esp) = 0x485e39u; native_call(m, 0x464a70u);	/* 485e34: call 0x464a70 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485e39: add esp, 0x10 */
L_485e3c:
	m->edi = M32((DWORD)(m->esi + 0x904cu));	/* 485e3c: mov edi, dword ptr [esi + 0x904c] */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 485e42: mov esi, dword ptr [esp + 0x14] */
	goto L_485ffe;	/* 485e46: jmp 0x485ffe */
L_485e4b:
	m->ecx = M32((DWORD)(m->edi + 0xcu));	/* 485e4b: mov ecx, dword ptr [edi + 0xc] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485e4e: test ecx, ecx */
	if (m->zf) goto L_485ec1;	/* 485e50: je 0x485ec1 */
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 485e52: mov eax, dword ptr [ebx + 0x4c] */
	m->ecx = M32((DWORD)(m->esi + 0x9048u));	/* 485e55: mov ecx, dword ptr [esi + 0x9048] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485e5b: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_4868ec;	/* 485e5d: jg 0x4868ec */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9050u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485e63: cmp dword ptr [esi + 0x9050], eax */
	if (m->sf == m->of) goto L_485e71;	/* 485e69: jge 0x485e71 */
	M32((DWORD)(m->esi + 0x9050u)) = m->eax;	/* 485e6b: mov dword ptr [esi + 0x9050], eax */
L_485e71:
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 485e71: mov ecx, dword ptr [ebx + 0x4c] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 485e74: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 485e78: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->edx + 0x904cu));	/* 485e7c: mov edi, dword ptr [edx + 0x904c] */
	m->esi = M32((DWORD)(m->eax + 0x4u));	/* 485e82: mov esi, dword ptr [eax + 4] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 485e85: shl ecx, 2 */
	m->edx = m->ecx;	/* 485e88: mov edx, ecx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 485e8a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 485e8d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 485e8f: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 485e91: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 485e94: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 485e96: mov eax, dword ptr [eax + 0xc] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 485e99: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485e9d: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 485e9e: push ebx */
	m->edx = M32((DWORD)(m->ecx + 0x904cu));	/* 485e9f: mov edx, dword ptr [ecx + 0x904c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 485ea5: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485ea7: push edx */
	m->esp -= 4; M32(m->esp) = 0x485eadu; native_call(m, 0x464a70u);	/* 485ea8: call 0x464a70 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 485ead: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485eb1: add esp, 0x10 */
	m->esi = m->eax;	/* 485eb4: mov esi, eax */
	m->edi = M32((DWORD)(m->eax + 0x904cu));	/* 485eb6: mov edi, dword ptr [eax + 0x904c] */
	goto L_485ffe;	/* 485ebc: jmp 0x485ffe */
L_485ec1:
	m->edi = m->eax;	/* 485ec1: mov edi, eax */
	goto L_485ffe;	/* 485ec3: jmp 0x485ffe */
L_485ec8:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x0u)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 485ec8: test byte ptr [ebx], 2 */
	if (m->zf) goto L_485ed8;	/* 485ecb: je 0x485ed8 */
	m->eax = M32((DWORD)(m->edi + 0xcu));	/* 485ecd: mov eax, dword ptr [edi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485ed0: test eax, eax */
	if (m->zf) goto L_485ffb;	/* 485ed2: je 0x485ffb */
L_485ed8:
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 485ed8: mov eax, dword ptr [edi + 8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485edb: test eax, eax */
	if (m->zf) goto L_485fc8;	/* 485edd: je 0x485fc8 */
	m->ecx = M32((DWORD)(m->edi + 0x10u));	/* 485ee3: mov ecx, dword ptr [edi + 0x10] */
	m->edx = (DWORD)(m->esp + 0x70u);	/* 485ee6: lea edx, [esp + 0x70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 485eea: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485eeb: push edx */
	m->esp -= 4; M32(m->esp) = 0x485ef1u; native_call(m, 0x47d740u);	/* 485eec: call 0x47d740 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485ef1: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485ef4: test eax, eax */
	if (!m->zf) goto L_485f6c;	/* 485ef6: jne 0x485f6c */
	M32((DWORD)(m->esp + 0x70u)) = 0x3f800000u;	/* 485ef8: mov dword ptr [esp + 0x70], 0x3f800000 */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 485f00: mov dword ptr [esp + 0x80], eax */
	M32((DWORD)(m->esp + 0x90u)) = m->eax;	/* 485f07: mov dword ptr [esp + 0x90], eax */
	M32((DWORD)(m->esp + 0xa0u)) = m->eax;	/* 485f0e: mov dword ptr [esp + 0xa0], eax */
	M32((DWORD)(m->esp + 0x74u)) = m->eax;	/* 485f15: mov dword ptr [esp + 0x74], eax */
	M32((DWORD)(m->esp + 0x84u)) = 0x3f800000u;	/* 485f19: mov dword ptr [esp + 0x84], 0x3f800000 */
	M32((DWORD)(m->esp + 0x94u)) = m->eax;	/* 485f24: mov dword ptr [esp + 0x94], eax */
	M32((DWORD)(m->esp + 0xa4u)) = m->eax;	/* 485f2b: mov dword ptr [esp + 0xa4], eax */
	M32((DWORD)(m->esp + 0x78u)) = m->eax;	/* 485f32: mov dword ptr [esp + 0x78], eax */
	M32((DWORD)(m->esp + 0x88u)) = m->eax;	/* 485f36: mov dword ptr [esp + 0x88], eax */
	M32((DWORD)(m->esp + 0x98u)) = 0x3f800000u;	/* 485f3d: mov dword ptr [esp + 0x98], 0x3f800000 */
	M32((DWORD)(m->esp + 0xa8u)) = m->eax;	/* 485f48: mov dword ptr [esp + 0xa8], eax */
	M32((DWORD)(m->esp + 0x7cu)) = m->eax;	/* 485f4f: mov dword ptr [esp + 0x7c], eax */
	M32((DWORD)(m->esp + 0x8cu)) = m->eax;	/* 485f53: mov dword ptr [esp + 0x8c], eax */
	M32((DWORD)(m->esp + 0x9cu)) = m->eax;	/* 485f5a: mov dword ptr [esp + 0x9c], eax */
	M32((DWORD)(m->esp + 0xacu)) = 0x3f800000u;	/* 485f61: mov dword ptr [esp + 0xac], 0x3f800000 */
L_485f6c:
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 485f6c: mov eax, dword ptr [ebx + 0x4c] */
	m->ecx = M32((DWORD)(m->esi + 0x9048u));	/* 485f6f: mov ecx, dword ptr [esi + 0x9048] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485f75: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_4868ec;	/* 485f77: jg 0x4868ec */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9050u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485f7d: cmp dword ptr [esi + 0x9050], eax */
	if (m->sf == m->of) goto L_485f8b;	/* 485f83: jge 0x485f8b */
	M32((DWORD)(m->esi + 0x9050u)) = m->eax;	/* 485f85: mov dword ptr [esi + 0x9050], eax */
L_485f8b:
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 485f8b: mov ecx, dword ptr [edi + 8] */
	m->edx = M32((DWORD)(m->esi + 0x904cu));	/* 485f8e: mov edx, dword ptr [esi + 0x904c] */
	m->eax = (DWORD)(m->esp + 0x70u);	/* 485f94: lea eax, [esp + 0x70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485f98: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 485f99: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 485f9a: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 485f9b: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485f9d: push edx */
	m->esp -= 4; M32(m->esp) = 0x485fa3u; native_call(m, 0x463b80u);	/* 485f9e: call 0x463b80 */
	m->edi = M32((DWORD)(m->edi + 0xcu));	/* 485fa3: mov edi, dword ptr [edi + 0xc] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485fa6: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485fa9: test edi, edi */
	if (m->zf) goto L_485fc0;	/* 485fab: je 0x485fc0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 485fad: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 485fae: push ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 485faf: push 0 */
L_485fb1:
	m->eax = M32((DWORD)(m->esi + 0x904cu));	/* 485fb1: mov eax, dword ptr [esi + 0x904c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 485fb7: push eax */
	m->esp -= 4; M32(m->esp) = 0x485fbdu; native_call(m, 0x464a70u);	/* 485fb8: call 0x464a70 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 485fbd: add esp, 0x10 */
L_485fc0:
	m->edi = M32((DWORD)(m->esi + 0x904cu));	/* 485fc0: mov edi, dword ptr [esi + 0x904c] */
	goto L_485ffe;	/* 485fc6: jmp 0x485ffe */
L_485fc8:
	m->eax = M32((DWORD)(m->edi + 0xcu));	/* 485fc8: mov eax, dword ptr [edi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 485fcb: test eax, eax */
	if (m->zf) goto L_485ffb;	/* 485fcd: je 0x485ffb */
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 485fcf: mov eax, dword ptr [ebx + 0x4c] */
	m->ecx = M32((DWORD)(m->esi + 0x9048u));	/* 485fd2: mov ecx, dword ptr [esi + 0x9048] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485fd8: cmp eax, ecx */
	if (!m->zf && m->sf == m->of) goto L_4868ec;	/* 485fda: jg 0x4868ec */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9050u)), b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 485fe0: cmp dword ptr [esi + 0x9050], eax */
	if (m->sf == m->of) goto L_485fee;	/* 485fe6: jge 0x485fee */
	M32((DWORD)(m->esi + 0x9050u)) = m->eax;	/* 485fe8: mov dword ptr [esi + 0x9050], eax */
L_485fee:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 485fee: mov ecx, dword ptr [esp + 0x10] */
	m->edx = M32((DWORD)(m->ecx + 0xcu));	/* 485ff2: mov edx, dword ptr [ecx + 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 485ff5: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 485ff6: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 485ff7: push 1 */
	goto L_485fb1;	/* 485ff9: jmp 0x485fb1 */
L_485ffb:
	m->edi = M32((DWORD)(m->ebx + 0x58u));	/* 485ffb: mov edi, dword ptr [ebx + 0x58] */
L_485ffe:
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 485ffe: test byte ptr [ebx], 1 */
	if (!m->zf) goto L_486339;	/* 486001: jne 0x486339 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 486007: mov ecx, dword ptr [esp + 0x10] */
	m->eax = M32((DWORD)(m->ecx + 0x14u));	/* 48600b: mov eax, dword ptr [ecx + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48600e: test eax, eax */
	if (!m->zf) goto L_486339;	/* 486010: jne 0x486339 */
	{ DWORD v_ = 0x8074u; m->esp -= 4; M32(m->esp) = v_; }	/* 486016: push 0x8074 */
	m->esp -= 4; M32(m->esp) = 0x486021u; native_call(m, M32(0x4a9240u));	/* 48601b: call dword ptr [0x4a9240] */
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 486021: mov eax, dword ptr [esi + 0x14] */
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 486024: mov edx, dword ptr [ebx + 0x50] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486027: test eax, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486029: push edx */
	if (m->zf) goto L_48603d;	/* 48602a: je 0x48603d */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 48602c: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48602f: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 486030: push 0 */
	{ DWORD v_ = 0x1406u; m->esp -= 4; M32(m->esp) = v_; }	/* 486032: push 0x1406 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 486037: push 3 */
	m->esp -= 4; M32(m->esp) = 0x48603bu; native_call(m, m->eax);	/* 486039: call eax */
	goto L_48604c;	/* 48603b: jmp 0x48604c */
L_48603d:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48603d: push 0 */
	{ DWORD v_ = 0x1406u; m->esp -= 4; M32(m->esp) = v_; }	/* 48603f: push 0x1406 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 486044: push 3 */
	m->esp -= 4; M32(m->esp) = 0x48604cu; native_call(m, M32(0x4a9248u));	/* 486046: call dword ptr [0x4a9248] */
L_48604c:
	{ DWORD v_ = 0x8076u; m->esp -= 4; M32(m->esp) = v_; }	/* 48604c: push 0x8076 */
	m->esp -= 4; M32(m->esp) = 0x486057u; native_call(m, M32(0x4a9240u));	/* 486051: call dword ptr [0x4a9240] */
	m->esi = M32((DWORD)(m->esi + 0x18u));	/* 486057: mov esi, dword ptr [esi + 0x18] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48605a: push edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48605b: test esi, esi */
	if (m->zf) goto L_486070;	/* 48605d: je 0x486070 */
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 48605f: mov eax, dword ptr [ebx + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486062: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 486063: push 0 */
	{ DWORD v_ = 0x1401u; m->esp -= 4; M32(m->esp) = v_; }	/* 486065: push 0x1401 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48606a: push 4 */
	m->esp -= 4; M32(m->esp) = 0x48606eu; native_call(m, m->esi);	/* 48606c: call esi */
	goto L_48607f;	/* 48606e: jmp 0x48607f */
L_486070:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 486070: push 0 */
	{ DWORD v_ = 0x1401u; m->esp -= 4; M32(m->esp) = v_; }	/* 486072: push 0x1401 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 486077: push 4 */
	m->esp -= 4; M32(m->esp) = 0x48607fu; native_call(m, M32(0x4a9244u));	/* 486079: call dword ptr [0x4a9244] */
L_48607f:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 48607f: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486083: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_486220;	/* 486085: jle 0x486220 */
	m->ecx = (DWORD)(m->eax + 0xffffffffu);	/* 48608b: lea ecx, [eax - 1] */
	m->eax = m->ecx;	/* 48608e: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 486090: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 486091: and edx, 0x1ff */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 486097: add edx, eax */
	m->eax = m->ecx;	/* 486099: mov eax, ecx */
	{ DWORD a_ = m->edx, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48609b: sar edx, 9 */
	{ DWORD a_ = m->eax, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48609e: and eax, 0x800001ff */
	if (!m->sf) goto L_4860ac;	/* 4860a3: jns 0x4860ac */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4860a5: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4860a6: or eax, 0xfffffe00 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4860ab: inc eax */
L_4860ac:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4860ac: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 4860af: lea eax, [eax + ecx*4] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4860b2: mov ecx, dword ptr [0xa0e010] */
	m->edx = M32((DWORD)(m->ecx + m->edx*4 + 0x4u));	/* 4860b8: mov edx, dword ptr [ecx + edx*4 + 4] */
	m->ecx = M32((DWORD)(m->edx + m->eax*8 + 0xc0188u));	/* 4860bc: mov ecx, dword ptr [edx + eax*8 + 0xc0188] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4860c3: test ecx, ecx */
	if (m->zf) goto L_4861e4;	/* 4860c5: je 0x4861e4 */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 4860cb: mov ecx, dword ptr [ebx + 0x4c] */
	m->esi = M32((DWORD)(m->ebx + 0x5cu));	/* 4860ce: mov esi, dword ptr [ebx + 0x5c] */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4860d1: shl ecx, 3 */
	m->eax = m->ecx;	/* 4860d4: mov eax, ecx */
	m->edi = (DWORD)(m->esp + 0x1a8u);	/* 4860d6: lea edi, [esp + 0x1a8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4860dd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4860e0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4860e2: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4860e4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4860e7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4860e9: mov ecx, dword ptr [esp + 0x24] */
	m->eax = (DWORD)(m->ecx + 0xffffffffu);	/* 4860ed: lea eax, [ecx - 1] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4860f0: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4860f1: and edx, 0x1ff */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4860f7: add edx, eax */
	m->eax = (DWORD)(m->ecx + 0xffffffffu);	/* 4860f9: lea eax, [ecx - 1] */
	{ DWORD a_ = m->edx, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4860fc: sar edx, 9 */
	{ DWORD a_ = m->eax, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4860ff: and eax, 0x800001ff */
	if (!m->sf) goto L_48610d;	/* 486104: jns 0x48610d */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 486106: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 486107: or eax, 0xfffffe00 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48610c: inc eax */
L_48610d:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48610d: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 486110: lea eax, [eax + ecx*4] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 486113: mov ecx, dword ptr [0xa0e010] */
	m->edx = M32((DWORD)(m->ecx + m->edx*4 + 0x4u));	/* 486119: mov edx, dword ptr [ecx + edx*4 + 4] */
	m->eax = M32((DWORD)(m->edx + m->eax*8 + 0xc0188u));	/* 48611d: mov eax, dword ptr [edx + eax*8 + 0xc0188] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 486124: dec eax */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486125: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_4861db;	/* 486128: ja 0x4861db */
	switch (m->eax) { case 0: goto L_486135; case 1: goto L_486166; case 2: goto L_486190; case 3: goto L_4861ba; default: abort(); }	/* 48612e: jmp dword ptr [eax*4 + 0x4873a8] */
L_486135:
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 486135: mov eax, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 486138: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48613a: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4861db;	/* 48613c: jle 0x4861db */
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 486142: lea eax, [esp + 0x1ac] */
L_486149:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 486149: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 48614c: fadd dword ptr [eax] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48614e: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48614f: add eax, 8 */
	MF((DWORD)(m->eax + 0xfffffff8u)) = (float)ST(0); FPOP();	/* 486152: fstp dword ptr [eax - 8] */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->ebx + 0x4cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486155: cmp ecx, dword ptr [ebx + 0x4c] */
	if (m->sf != m->of) goto L_486149;	/* 486158: jl 0x486149 */
	m->esi = (DWORD)(m->esp + 0x1a8u);	/* 48615a: lea esi, [esp + 0x1a8] */
	goto L_4861e7;	/* 486161: jmp 0x4861e7 */
L_486166:
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 486166: mov eax, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 486169: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48616b: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4861db;	/* 48616d: jle 0x4861db */
	m->eax = (DWORD)(m->esp + 0x1a8u);	/* 48616f: lea eax, [esp + 0x1a8] */
L_486176:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0xcu)));	/* 486176: fld dword ptr [ebp + 0xc] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 486179: fadd dword ptr [eax] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48617b: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48617c: add eax, 8 */
	MF((DWORD)(m->eax + 0xfffffff8u)) = (float)ST(0); FPOP();	/* 48617f: fstp dword ptr [eax - 8] */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->ebx + 0x4cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486182: cmp ecx, dword ptr [ebx + 0x4c] */
	if (m->sf != m->of) goto L_486176;	/* 486185: jl 0x486176 */
	m->esi = (DWORD)(m->esp + 0x1a8u);	/* 486187: lea esi, [esp + 0x1a8] */
	goto L_4861e7;	/* 48618e: jmp 0x4861e7 */
L_486190:
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 486190: mov eax, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 486193: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486195: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4861db;	/* 486197: jle 0x4861db */
	m->eax = (DWORD)(m->esp + 0x1acu);	/* 486199: lea eax, [esp + 0x1ac] */
L_4861a0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4861a0: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 4861a2: fsub dword ptr [ebp + 0xc] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4861a5: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4861a6: add eax, 8 */
	MF((DWORD)(m->eax + 0xfffffff8u)) = (float)ST(0); FPOP();	/* 4861a9: fstp dword ptr [eax - 8] */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->ebx + 0x4cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4861ac: cmp ecx, dword ptr [ebx + 0x4c] */
	if (m->sf != m->of) goto L_4861a0;	/* 4861af: jl 0x4861a0 */
	m->esi = (DWORD)(m->esp + 0x1a8u);	/* 4861b1: lea esi, [esp + 0x1a8] */
	goto L_4861e7;	/* 4861b8: jmp 0x4861e7 */
L_4861ba:
	m->eax = M32((DWORD)(m->ebx + 0x4cu));	/* 4861ba: mov eax, dword ptr [ebx + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4861bd: xor ecx, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4861bf: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4861db;	/* 4861c1: jle 0x4861db */
	m->eax = (DWORD)(m->esp + 0x1a8u);	/* 4861c3: lea eax, [esp + 0x1a8] */
L_4861ca:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4861ca: fld dword ptr [eax] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 4861cc: fsub dword ptr [ebp + 0xc] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4861cf: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4861d0: add eax, 8 */
	MF((DWORD)(m->eax + 0xfffffff8u)) = (float)ST(0); FPOP();	/* 4861d3: fstp dword ptr [eax - 8] */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->ebx + 0x4cu)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4861d6: cmp ecx, dword ptr [ebx + 0x4c] */
	if (m->sf != m->of) goto L_4861ca;	/* 4861d9: jl 0x4861ca */
L_4861db:
	m->esi = (DWORD)(m->esp + 0x1a8u);	/* 4861db: lea esi, [esp + 0x1a8] */
	goto L_4861e7;	/* 4861e2: jmp 0x4861e7 */
L_4861e4:
	m->esi = M32((DWORD)(m->ebx + 0x5cu));	/* 4861e4: mov esi, dword ptr [ebx + 0x5c] */
L_4861e7:
	{ DWORD v_ = 0x8078u; m->esp -= 4; M32(m->esp) = v_; }	/* 4861e7: push 0x8078 */
	m->esp -= 4; M32(m->esp) = 0x4861f2u; native_call(m, M32(0x4a9240u));	/* 4861ec: call dword ptr [0x4a9240] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4861f2: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4861f6: push esi */
	m->eax = M32((DWORD)(m->eax + 0x1cu));	/* 4861f7: mov eax, dword ptr [eax + 0x1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4861fa: test eax, eax */
	if (m->zf) goto L_48620f;	/* 4861fc: je 0x48620f */
	m->ecx = M32((DWORD)(m->ebx + 0x4cu));	/* 4861fe: mov ecx, dword ptr [ebx + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486201: push ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 486202: push 0 */
	{ DWORD v_ = 0x1406u; m->esp -= 4; M32(m->esp) = v_; }	/* 486204: push 0x1406 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 486209: push 2 */
	m->esp -= 4; M32(m->esp) = 0x48620du; native_call(m, m->eax);	/* 48620b: call eax */
	goto L_48622b;	/* 48620d: jmp 0x48622b */
L_48620f:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48620f: push 0 */
	{ DWORD v_ = 0x1406u; m->esp -= 4; M32(m->esp) = v_; }	/* 486211: push 0x1406 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 486216: push 2 */
	m->esp -= 4; M32(m->esp) = 0x48621eu; native_call(m, M32(0x4a9234u));	/* 486218: call dword ptr [0x4a9234] */
	goto L_48622b;	/* 48621e: jmp 0x48622b */
L_486220:
	{ DWORD v_ = 0x8078u; m->esp -= 4; M32(m->esp) = v_; }	/* 486220: push 0x8078 */
	m->esp -= 4; M32(m->esp) = 0x48622bu; native_call(m, M32(0x4a923cu));	/* 486225: call dword ptr [0x4a923c] */
L_48622b:
	m->esp -= 4; M32(m->esp) = 0x486231u; native_call(m, M32(0x4a9204u));	/* 48622b: call dword ptr [0x4a9204] */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 486231: mov esi, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(0x4a9238u));	/* 486235: mov edi, dword ptr [0x4a9238] */
	m->edx = M32((DWORD)(m->esi + 0x10u));	/* 48623b: mov edx, dword ptr [esi + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48623e: push edx */
	m->esp -= 4; M32(m->esp) = 0x486241u; native_call(m, m->edi);	/* 48623f: call edi */
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 486241: mov eax, dword ptr [esi + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486244: test eax, eax */
	if (m->zf) goto L_48624b;	/* 486246: je 0x48624b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486248: push eax */
	m->esp -= 4; M32(m->esp) = 0x48624bu; native_call(m, m->edi);	/* 486249: call edi */
L_48624b:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x0u))) & 0xff) << 0);	/* 48624b: mov al, byte ptr [ebx] */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 48624d: push 0xb44 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x4u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 486252: test al, 4 */
	if (m->zf) goto L_486264;	/* 486254: je 0x486264 */
	m->esp -= 4; M32(m->esp) = 0x48625cu; native_call(m, M32(0x4a922cu));	/* 486256: call dword ptr [0x4a922c] */
	m->edi = M32((DWORD)(0x4a9224u));	/* 48625c: mov edi, dword ptr [0x4a9224] */
	goto L_486283;	/* 486262: jmp 0x486283 */
L_486264:
	m->edi = M32((DWORD)(0x4a9224u));	/* 486264: mov edi, dword ptr [0x4a9224] */
	m->esp -= 4; M32(m->esp) = 0x48626cu; native_call(m, m->edi);	/* 48626a: call edi */
	{ DWORD a_ = M8((DWORD)(m->ebx + 0x0u)), b_ = 0x8u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48626c: test byte ptr [ebx], 8 */
	if (m->zf) goto L_486278;	/* 48626f: je 0x486278 */
	{ DWORD v_ = 0x404u; m->esp -= 4; M32(m->esp) = v_; }	/* 486271: push 0x404 */
	goto L_48627d;	/* 486276: jmp 0x48627d */
L_486278:
	{ DWORD v_ = 0x405u; m->esp -= 4; M32(m->esp) = v_; }	/* 486278: push 0x405 */
L_48627d:
	m->esp -= 4; M32(m->esp) = 0x486283u; native_call(m, M32(0x4a91d0u));	/* 48627d: call dword ptr [0x4a91d0] */
L_486283:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x0u))) & 0xff) << 0);	/* 486283: mov al, byte ptr [ebx] */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 486285: push 0xb71 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48628a: test al, 0x10 */
	if (m->zf) goto L_486296;	/* 48628c: je 0x486296 */
	m->esp -= 4; M32(m->esp) = 0x486294u; native_call(m, M32(0x4a922cu));	/* 48628e: call dword ptr [0x4a922c] */
	goto L_486298;	/* 486294: jmp 0x486298 */
L_486296:
	m->esp -= 4; M32(m->esp) = 0x486298u; native_call(m, m->edi);	/* 486296: call edi */
L_486298:
	m->eax = M32((DWORD)(m->ebx + 0x60u));	/* 486298: mov eax, dword ptr [ebx + 0x60] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 48629b: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48629d: cmp eax, esi */
	M32((DWORD)(m->esp + 0x1cu)) = m->esi;	/* 48629f: mov dword ptr [esp + 0x1c], esi */
	if (m->zf || m->sf != m->of) goto L_48631c;	/* 4862a3: jle 0x48631c */
L_4862a5:
	m->eax = M32((DWORD)(m->ebx + 0x64u));	/* 4862a5: mov eax, dword ptr [ebx + 0x64] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4862a8: add eax, esi */
	m->ecx = M32((DWORD)(m->eax + 0x8u));	/* 4862aa: mov ecx, dword ptr [eax + 8] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 4862ad: mov edx, dword ptr [eax + 4] */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 4862b0: mov eax, dword ptr [eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4862b2: push ecx */
	{ DWORD v_ = 0x1405u; m->esp -= 4; M32(m->esp) = v_; }	/* 4862b3: push 0x1405 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4862b8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4862b9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4862c0u; native_call(m, M32(0x4a92a8u));	/* 4862ba: call dword ptr [0x4a92a8] */
	m->ecx = M32((DWORD)(m->ebx + 0x64u));	/* 4862c0: mov ecx, dword ptr [ebx + 0x64] */
	m->eax = (DWORD)(m->ecx + m->esi*1 + 0x0u);	/* 4862c3: lea eax, [ecx + esi] */
	m->ecx = M32((DWORD)(m->ecx + m->esi*1 + 0x0u));	/* 4862c6: mov ecx, dword ptr [ecx + esi] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4862c9: sub ecx, 4 */
	if (m->zf) goto L_4862ee;	/* 4862cc: je 0x4862ee */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4862ce: dec ecx */
	if (m->zf) goto L_4862dc;	/* 4862cf: je 0x4862dc */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4862d1: dec ecx */
	if (!m->zf) goto L_486309;	/* 4862d2: jne 0x486309 */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 4862d4: mov edx, dword ptr [eax + 4] */
	{ DWORD a_ = m->edx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4862d7: sub edx, 2 */
	goto L_4862ff;	/* 4862da: jmp 0x4862ff */
L_4862dc:
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 4862dc: mov ecx, dword ptr [eax + 4] */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4862df: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4862e3: sub ecx, 2 */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x90a4u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->eax + 0x90a4u)) = r_; }	/* 4862e6: add dword ptr [eax + 0x90a4], ecx */
	goto L_486309;	/* 4862ec: jmp 0x486309 */
L_4862ee:
	m->ecx = M32((DWORD)(m->eax + 0x4u));	/* 4862ee: mov ecx, dword ptr [eax + 4] */
	m->eax = 0x55555556u;	/* 4862f1: mov eax, 0x55555556 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 4862f6: imul ecx */
	m->eax = m->edx;	/* 4862f8: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4862fa: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4862fd: add edx, eax */
L_4862ff:
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 4862ff: mov eax, dword ptr [esp + 0x14] */
	{ DWORD a_ = M32((DWORD)(m->eax + 0x90a4u)), b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; M32((DWORD)(m->eax + 0x90a4u)) = r_; }	/* 486303: add dword ptr [eax + 0x90a4], edx */
L_486309:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 486309: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->ebx + 0x60u));	/* 48630d: mov ecx, dword ptr [ebx + 0x60] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 486310: inc eax */
	{ DWORD a_ = m->esi, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 486311: add esi, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486314: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 486316: mov dword ptr [esp + 0x1c], eax */
	if (m->sf != m->of) goto L_4862a5;	/* 48631a: jl 0x4862a5 */
L_48631c:
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 48631c: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x486323u; native_call(m, m->edi);	/* 486321: call edi */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 486323: push 0xb44 */
	m->esp -= 4; M32(m->esp) = 0x48632eu; native_call(m, M32(0x4a922cu));	/* 486328: call dword ptr [0x4a922c] */
	m->esp -= 4; M32(m->esp) = 0x486334u; native_call(m, M32(0x4a9258u));	/* 48632e: call dword ptr [0x4a9258] */
	goto L_4868db;	/* 486334: jmp 0x4868db */
L_486339:
	m->eax = M32((DWORD)(m->ebx + 0x60u));	/* 486339: mov eax, dword ptr [ebx + 0x60] */
	M32((DWORD)(m->esp + 0x1cu)) = 0x0u;	/* 48633c: mov dword ptr [esp + 0x1c], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486344: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4868df;	/* 486346: jle 0x4868df */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 48634c: mov dword ptr [esp + 0x28], 0 */
L_486354:
	m->ecx = M32((DWORD)(m->ebx + 0x64u));	/* 486354: mov ecx, dword ptr [ebx + 0x64] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 486357: mov edx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->ecx + m->edx*1 + 0x0u);	/* 48635b: lea eax, [ecx + edx] */
	m->ecx = M32((DWORD)(m->ecx + m->edx*1 + 0x4u));	/* 48635e: mov ecx, dword ptr [ecx + edx + 4] */
	m->edx = M32((DWORD)(m->eax + 0x8u));	/* 486362: mov edx, dword ptr [eax + 8] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 486365: mov eax, dword ptr [esp + 0x10] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 486369: mov dword ptr [esp + 0x18], ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 48636d: mov dword ptr [esp + 0x2c], edx */
	m->eax = M32((DWORD)(m->eax + 0x14u));	/* 486371: mov eax, dword ptr [eax + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486374: test eax, eax */
	if (m->zf) goto L_48639a;	/* 486376: je 0x48639a */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 486378: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48637c: push eax */
	m->eax = (DWORD)(m->esp + 0xecu);	/* 48637d: lea eax, [esp + 0xec] */
	m->edx = M32((DWORD)(m->ecx + 0x10u));	/* 486384: mov edx, dword ptr [ecx + 0x10] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486387: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486388: push eax */
	m->esp -= 4; M32(m->esp) = 0x48638eu; native_call(m, 0x47d380u);	/* 486389: call 0x47d380 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48638e: add esp, 0xc */
	m->esi = (DWORD)(m->esp + 0xe8u);	/* 486391: lea esi, [esp + 0xe8] */
	goto L_4863a1;	/* 486398: jmp 0x4863a1 */
L_48639a:
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 48639a: mov ecx, dword ptr [esp + 0x10] */
	m->esi = M32((DWORD)(m->ecx + 0x10u));	/* 48639e: mov esi, dword ptr [ecx + 0x10] */
L_4863a1:
	m->edx = M32((DWORD)(m->ebx + 0x64u));	/* 4863a1: mov edx, dword ptr [ebx + 0x64] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 4863a4: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = M32((DWORD)(m->edx + m->eax*1 + 0x0u)), b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4863a8: cmp dword ptr [edx + eax], 4 */
	if (!m->zf) goto L_4868bc;	/* 4863ac: jne 0x4868bc */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4863b2: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4863b6: test eax, eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4863b8: mov eax, dword ptr [esp + 0x18] */
	if (m->zf || m->sf != m->of) goto L_4866f9;	/* 4863bc: jle 0x4866f9 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4863c2: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4868bc;	/* 4863c4: jle 0x4868bc */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 4863ca: mov ecx, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 4863ce: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4863d2: dec ecx */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4863d3: add edx, 8 */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 4863d6: mov dword ptr [esp + 0x5c], ecx */
	m->ecx = (DWORD)(m->eax + 0x2u);	/* 4863da: lea ecx, [eax + 2] */
	m->eax = 0xaaaaaaabu;	/* 4863dd: mov eax, 0xaaaaaaab */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 4863e2: mov dword ptr [esp + 0x30], edx */
	{ unsigned long long p_ = (unsigned long long)m->eax * m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)(p_ >> 32); m->cf = m->of = m->edx != 0; }	/* 4863e6: mul ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4863e8: shr edx, 1 */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 4863ea: mov dword ptr [esp + 0x2c], edx */
L_4863ee:
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 4863ee: mov eax, dword ptr [esp + 0x30] */
	m->edx = M32((DWORD)(m->eax + 0xfffffffcu));	/* 4863f2: mov edx, dword ptr [eax - 4] */
	m->ecx = M32((DWORD)(m->eax + 0xfffffff8u));	/* 4863f5: mov ecx, dword ptr [eax - 8] */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 4863f8: mov eax, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x60u)) = m->edx;	/* 4863fa: mov dword ptr [esp + 0x60], edx */
	m->edx = M32((DWORD)(m->ebx + 0x5cu));	/* 4863fe: mov edx, dword ptr [ebx + 0x5c] */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 486401: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0xd4u)) = m->ecx;	/* 486405: mov dword ptr [esp + 0xd4], ecx */
	m->eax = M32((DWORD)(m->edx + m->ecx*8 + 0x0u));	/* 48640c: mov eax, dword ptr [edx + ecx*8] */
	M32((DWORD)(m->esp + 0x3cu)) = m->eax;	/* 48640f: mov dword ptr [esp + 0x3c], eax */
	m->eax = M32((DWORD)(m->esp + 0x60u));	/* 486413: mov eax, dword ptr [esp + 0x60] */
	m->ecx = M32((DWORD)(m->edx + m->ecx*8 + 0x4u));	/* 486417: mov ecx, dword ptr [edx + ecx*8 + 4] */
	M32((DWORD)(m->esp + 0x40u)) = m->ecx;	/* 48641b: mov dword ptr [esp + 0x40], ecx */
	m->edx = M32((DWORD)(m->ebx + 0x5cu));	/* 48641f: mov edx, dword ptr [ebx + 0x5c] */
	m->ecx = M32((DWORD)(m->edx + m->eax*8 + 0x0u));	/* 486422: mov ecx, dword ptr [edx + eax*8] */
	M32((DWORD)(m->esp + 0x44u)) = m->ecx;	/* 486425: mov dword ptr [esp + 0x44], ecx */
	m->edx = M32((DWORD)(m->edx + m->eax*8 + 0x4u));	/* 486429: mov edx, dword ptr [edx + eax*8 + 4] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 48642d: mov eax, dword ptr [esp + 0x18] */
	M32((DWORD)(m->esp + 0x48u)) = m->edx;	/* 486431: mov dword ptr [esp + 0x48], edx */
	m->ecx = M32((DWORD)(m->ebx + 0x5cu));	/* 486435: mov ecx, dword ptr [ebx + 0x5c] */
	m->edx = M32((DWORD)(m->ecx + m->eax*8 + 0x0u));	/* 486438: mov edx, dword ptr [ecx + eax*8] */
	M32((DWORD)(m->esp + 0x4cu)) = m->edx;	/* 48643b: mov dword ptr [esp + 0x4c], edx */
	m->eax = M32((DWORD)(m->ecx + m->eax*8 + 0x4u));	/* 48643f: mov eax, dword ptr [ecx + eax*8 + 4] */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 486443: mov ecx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 486447: mov dword ptr [esp + 0x50], eax */
	m->eax = m->ecx;	/* 48644b: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48644d: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48644e: and edx, 0x1ff */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 486454: add edx, eax */
	m->eax = m->ecx;	/* 486456: mov eax, ecx */
	{ DWORD a_ = m->edx, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 486458: sar edx, 9 */
	{ DWORD a_ = m->eax, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48645b: and eax, 0x800001ff */
	if (!m->sf) goto L_486469;	/* 486460: jns 0x486469 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 486462: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 486463: or eax, 0xfffffe00 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 486468: inc eax */
L_486469:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 486469: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 48646c: lea eax, [eax + ecx*4] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 48646f: mov ecx, dword ptr [0xa0e010] */
	m->edx = M32((DWORD)(m->ecx + m->edx*4 + 0x4u));	/* 486475: mov edx, dword ptr [ecx + edx*4 + 4] */
	m->ecx = M32((DWORD)(m->edx + m->eax*8 + 0xc0188u));	/* 486479: mov ecx, dword ptr [edx + eax*8 + 0xc0188] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486480: test ecx, ecx */
	if (m->zf) goto L_486558;	/* 486482: je 0x486558 */
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 486488: mov ecx, dword ptr [esp + 0x5c] */
	m->eax = m->ecx;	/* 48648c: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48648e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48648f: and edx, 0x1ff */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 486495: add edx, eax */
	m->eax = m->ecx;	/* 486497: mov eax, ecx */
	{ DWORD a_ = m->edx, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 486499: sar edx, 9 */
	{ DWORD a_ = m->eax, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48649c: and eax, 0x800001ff */
	if (!m->sf) goto L_4864aa;	/* 4864a1: jns 0x4864aa */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4864a3: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4864a4: or eax, 0xfffffe00 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4864a9: inc eax */
L_4864aa:
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4864aa: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 4864ad: lea eax, [eax + ecx*4] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4864b0: mov ecx, dword ptr [0xa0e010] */
	m->edx = M32((DWORD)(m->ecx + m->edx*4 + 0x4u));	/* 4864b6: mov edx, dword ptr [ecx + edx*4 + 4] */
	m->eax = M32((DWORD)(m->edx + m->eax*8 + 0xc0188u));	/* 4864ba: mov eax, dword ptr [edx + eax*8 + 0xc0188] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4864c1: dec eax */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4864c2: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_486558;	/* 4864c5: ja 0x486558 */
	switch (m->eax) { case 0: goto L_4864d2; case 1: goto L_4864f5; case 2: goto L_486514; case 3: goto L_486537; default: abort(); }	/* 4864cb: jmp dword ptr [eax*4 + 0x4873b8] */
L_4864d2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 4864d2: fld dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 4864d6: fadd dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 4864d9: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 4864dd: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 4864e1: fadd dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4864e4: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 4864e8: fld dword ptr [esp + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 4864ec: fadd dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4864ef: fstp dword ptr [esp + 0x50] */
	goto L_486558;	/* 4864f3: jmp 0x486558 */
L_4864f5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 4864f5: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 4864f9: fadd dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4864fc: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 486500: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 486504: fadd dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 486507: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 48650b: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 48650f: fadd dword ptr [ebp + 0xc] */
	goto L_486554;	/* 486512: jmp 0x486554 */
L_486514:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 486514: fld dword ptr [esp + 0x40] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 486518: fsub dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 48651b: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 48651f: fld dword ptr [esp + 0x48] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 486523: fsub dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 486526: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x50u)));	/* 48652a: fld dword ptr [esp + 0x50] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 48652e: fsub dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 486531: fstp dword ptr [esp + 0x50] */
	goto L_486558;	/* 486535: jmp 0x486558 */
L_486537:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 486537: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 48653b: fsub dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 48653e: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 486542: fld dword ptr [esp + 0x44] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 486546: fsub dword ptr [ebp + 0xc] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 486549: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4cu)));	/* 48654d: fld dword ptr [esp + 0x4c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0xcu));	/* 486551: fsub dword ptr [ebp + 0xc] */
L_486554:
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 486554: fstp dword ptr [esp + 0x4c] */
L_486558:
	m->eax = M32((DWORD)(m->esp + 0xd4u));	/* 486558: mov eax, dword ptr [esp + 0xd4] */
	m->ecx = M32((DWORD)(m->edi + m->eax*4 + 0x0u));	/* 48655f: mov ecx, dword ptr [edi + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 486562: lea eax, [eax + eax*2] */
	M32((DWORD)(m->esp + 0x64u)) = m->ecx;	/* 486565: mov dword ptr [esp + 0x64], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x60u));	/* 486569: mov ecx, dword ptr [esp + 0x60] */
	m->edx = M32((DWORD)(m->edi + m->ecx*4 + 0x0u));	/* 48656d: mov edx, dword ptr [edi + ecx*4] */
	M32((DWORD)(m->esp + 0x68u)) = m->edx;	/* 486570: mov dword ptr [esp + 0x68], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 486574: mov edx, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->edi + m->edx*4 + 0x0u));	/* 486578: mov edx, dword ptr [edi + edx*4] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 48657b: mov dword ptr [esp + 0x6c], edx */
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 48657f: mov edx, dword ptr [ebx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 486582: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + m->eax*4 + 0x8u));	/* 486585: fmul dword ptr [edx + eax*4 + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + m->eax*4 + 0x0u)));	/* 486589: fld dword ptr [edx + eax*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 48658c: fmul dword ptr [esi] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48658e: lea eax, [edx + eax*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486591: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 486593: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 486596: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486599: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 48659b: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0xb0u)) = (float)ST(0); FPOP();	/* 48659e: fstp dword ptr [esp + 0xb0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 4865a5: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4865a8: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4865ab: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4865ad: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4865b0: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 4865b2: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4865b5: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4865b8: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4865ba: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0xb4u)) = (float)ST(0); FPOP();	/* 4865bd: fstp dword ptr [esp + 0xb4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4865c4: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4865c7: fmul dword ptr [esi + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 4865ca: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4865cd: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4865cf: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4865d1: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 4865d4: fmul dword ptr [esi + 0x28] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 4865d7: lea eax, [ecx + ecx*2] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4865da: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4865dc: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0xb8u)) = (float)ST(0); FPOP();	/* 4865df: fstp dword ptr [esp + 0xb8] */
	m->ecx = M32((DWORD)(m->ebx + 0x50u));	/* 4865e6: mov ecx, dword ptr [ebx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 4865e9: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + m->eax*4 + 0x8u));	/* 4865ec: fmul dword ptr [ecx + eax*4 + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 4865f0: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + m->eax*4 + 0x0u));	/* 4865f2: fmul dword ptr [ecx + eax*4] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 4865f5: lea eax, [ecx + eax*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4865f8: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 4865fa: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4865fd: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486600: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 486602: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0xbcu)) = (float)ST(0); FPOP();	/* 486605: fstp dword ptr [esp + 0xbc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 48660c: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 48660e: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 486611: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 486614: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486617: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 486619: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 48661c: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48661f: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 486621: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0xc0u)) = (float)ST(0); FPOP();	/* 486624: fstp dword ptr [esp + 0xc0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 48662b: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 48662e: fmul dword ptr [esi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 486631: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 486634: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486637: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 486639: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 48663c: fmul dword ptr [eax] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 48663e: mov eax, dword ptr [esp + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486642: faddp st(1) */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 486644: lea edx, [eax + eax*2] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 486647: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0xc4u)) = (float)ST(0); FPOP();	/* 48664a: fstp dword ptr [esp + 0xc4] */
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 486651: mov eax, dword ptr [ebx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 486654: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x8u));	/* 486657: fmul dword ptr [eax + edx*4 + 8] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 48665b: lea eax, [eax + edx*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 48665e: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 486660: fmul dword ptr [esi] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 486662: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 486664: push 2 */
	m->ecx = (DWORD)(m->esp + 0xb8u);	/* 486666: lea ecx, [esp + 0xb8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48666d: push 0 */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48666f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 486671: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 486674: fmul dword ptr [esi + 0x10] */
	m->edx = (DWORD)(m->esp + 0x70u);	/* 486677: lea edx, [esp + 0x70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48667b: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x6cu));	/* 48667c: mov ecx, dword ptr [esp + 0x6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486680: push edx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486681: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 486683: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0xdcu)) = (float)ST(0); FPOP();	/* 486686: fstp dword ptr [esp + 0xdc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 48668d: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 48668f: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 486692: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 486695: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486698: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 48669a: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 48669d: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4866a0: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4866a2: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0xe0u)) = (float)ST(0); FPOP();	/* 4866a5: fstp dword ptr [esp + 0xe0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4866ac: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 4866ae: fmul dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4866b1: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 4866b4: fmul dword ptr [esi + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4866b7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4866b9: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4866bc: fmul dword ptr [esi + 0x18] */
	m->eax = (DWORD)(m->esp + 0x50u);	/* 4866bf: lea eax, [esp + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4866c3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4866c4: push ecx */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4866c5: faddp st(1) */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4866c7: mov ecx, dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4866cb: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0xecu)) = (float)ST(0); FPOP();	/* 4866ce: fstp dword ptr [esp + 0xec] */
	m->esp -= 4; M32(m->esp) = 0x4866dau; native_call(m, 0x4842d0u);	/* 4866d5: call 0x4842d0 */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4866da: mov ecx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4866de: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4866e2: add ecx, 0xc */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4866e5: dec eax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 4866e6: mov dword ptr [esp + 0x30], ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 4866ea: mov dword ptr [esp + 0x2c], eax */
	if (!m->zf) goto L_4863ee;	/* 4866ee: jne 0x4863ee */
	goto L_4868bc;	/* 4866f4: jmp 0x4868bc */
L_4866f9:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4866f9: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4868bc;	/* 4866fb: jle 0x4868bc */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 486701: mov eax, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 486705: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->edx, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 486709: add edx, 8 */
	m->ecx = (DWORD)(m->eax + 0x2u);	/* 48670c: lea ecx, [eax + 2] */
	m->eax = 0xaaaaaaabu;	/* 48670f: mov eax, 0xaaaaaaab */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 486714: mov dword ptr [esp + 0x30], edx */
	{ unsigned long long p_ = (unsigned long long)m->eax * m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)(p_ >> 32); m->cf = m->of = m->edx != 0; }	/* 486718: mul ecx */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48671a: shr edx, 1 */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 48671c: mov dword ptr [esp + 0x2c], edx */
L_486720:
	m->edx = M32((DWORD)(m->esp + 0x30u));	/* 486720: mov edx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->edx + 0xfffffff8u));	/* 486724: mov eax, dword ptr [edx - 8] */
	m->ecx = M32((DWORD)(m->edx + 0xfffffffcu));	/* 486727: mov ecx, dword ptr [edx - 4] */
	m->edx = M32((DWORD)(m->edx + 0x0u));	/* 48672a: mov edx, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 48672c: mov dword ptr [esp + 0x18], edx */
	m->edx = M32((DWORD)(m->edi + m->eax*4 + 0x0u));	/* 486730: mov edx, dword ptr [edi + eax*4] */
	M32((DWORD)(m->esp + 0x64u)) = m->edx;	/* 486733: mov dword ptr [esp + 0x64], edx */
	m->edx = M32((DWORD)(m->edi + m->ecx*4 + 0x0u));	/* 486737: mov edx, dword ptr [edi + ecx*4] */
	M32((DWORD)(m->esp + 0x68u)) = m->edx;	/* 48673a: mov dword ptr [esp + 0x68], edx */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 48673e: mov edx, dword ptr [esp + 0x18] */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 486742: lea eax, [eax + eax*2] */
	m->edx = M32((DWORD)(m->edi + m->edx*4 + 0x0u));	/* 486745: mov edx, dword ptr [edi + edx*4] */
	M32((DWORD)(m->esp + 0x6cu)) = m->edx;	/* 486748: mov dword ptr [esp + 0x6c], edx */
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 48674c: mov edx, dword ptr [ebx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + m->eax*4 + 0x4u)));	/* 48674f: fld dword ptr [edx + eax*4 + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x10u));	/* 486753: fmul dword ptr [esi + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + m->eax*4 + 0x0u)));	/* 486756: fld dword ptr [edx + eax*4] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 486759: lea eax, [edx + eax*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 48675c: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48675e: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 486760: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 486763: fmul dword ptr [esi + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486766: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 486768: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0xb0u)) = (float)ST(0); FPOP();	/* 48676b: fstp dword ptr [esp + 0xb0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 486772: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 486774: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 486777: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 48677a: fmul dword ptr [esi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48677d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 48677f: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 486782: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486785: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 486787: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0xb4u)) = (float)ST(0); FPOP();	/* 48678a: fstp dword ptr [esp + 0xb4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 486791: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 486793: fmul dword ptr [esi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 486796: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 486799: fmul dword ptr [esi + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48679c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 48679e: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4867a1: fmul dword ptr [esi + 0x18] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 4867a4: lea eax, [ecx + ecx*2] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4867a7: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4867a9: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0xb8u)) = (float)ST(0); FPOP();	/* 4867ac: fstp dword ptr [esp + 0xb8] */
	m->ecx = M32((DWORD)(m->ebx + 0x50u));	/* 4867b3: mov ecx, dword ptr [ebx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 4867b6: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + m->eax*4 + 0x0u));	/* 4867b8: fmul dword ptr [ecx + eax*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 4867bb: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + m->eax*4 + 0x8u));	/* 4867be: fmul dword ptr [ecx + eax*4 + 8] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 4867c2: lea eax, [ecx + eax*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4867c5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 4867c7: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4867ca: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4867cd: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 4867cf: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0xbcu)) = (float)ST(0); FPOP();	/* 4867d2: fstp dword ptr [esp + 0xbc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 4867d9: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4867dc: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 4867df: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4867e2: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4867e5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 4867e7: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4867ea: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4867ec: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4867ee: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0xc0u)) = (float)ST(0); FPOP();	/* 4867f1: fstp dword ptr [esp + 0xc0] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4867f8: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 4867fb: fmul dword ptr [esi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4867fe: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 486801: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486804: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 486806: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 486809: fmul dword ptr [eax] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 48680b: mov eax, dword ptr [esp + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48680f: faddp st(1) */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 486811: lea edx, [eax + eax*2] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 486814: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0xc4u)) = (float)ST(0); FPOP();	/* 486817: fstp dword ptr [esp + 0xc4] */
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 48681e: mov eax, dword ptr [ebx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20u)));	/* 486821: fld dword ptr [esi + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x8u));	/* 486824: fmul dword ptr [eax + edx*4 + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 486828: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x0u));	/* 48682a: fmul dword ptr [eax + edx*4] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 48682d: lea eax, [eax + edx*4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 486830: push 1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 486832: push 2 */
	m->ecx = (DWORD)(m->esp + 0xb8u);	/* 486834: lea ecx, [esp + 0xb8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48683b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 48683d: fld dword ptr [esi + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 486840: fmul dword ptr [eax + 4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 486843: push 0 */
	m->edx = (DWORD)(m->esp + 0x70u);	/* 486845: lea edx, [esp + 0x70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486849: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x24u));	/* 48684a: mov ecx, dword ptr [esp + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48684e: faddp st(1) */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486850: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 486851: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 486853: push 0 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 486855: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0xe4u)) = (float)ST(0); FPOP();	/* 486858: fstp dword ptr [esp + 0xe4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x24u)));	/* 48685f: fld dword ptr [esi + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 486862: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x14u)));	/* 486865: fld dword ptr [esi + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 486868: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48686b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 48686d: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 48686f: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486872: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 486874: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0xe8u)) = (float)ST(0); FPOP();	/* 486877: fstp dword ptr [esp + 0xe8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 48687e: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 486881: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 486883: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 486886: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486889: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 48688b: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 48688e: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 486891: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 486893: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0xecu)) = (float)ST(0); FPOP();	/* 486896: fstp dword ptr [esp + 0xec] */
	m->esp -= 4; M32(m->esp) = 0x4868a2u; native_call(m, 0x4842d0u);	/* 48689d: call 0x4842d0 */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 4868a2: mov ecx, dword ptr [esp + 0x30] */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 4868a6: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4868aa: add ecx, 0xc */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4868ad: dec eax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 4868ae: mov dword ptr [esp + 0x30], ecx */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 4868b2: mov dword ptr [esp + 0x2c], eax */
	if (!m->zf) goto L_486720;	/* 4868b6: jne 0x486720 */
L_4868bc:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4868bc: mov eax, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 4868c0: mov edx, dword ptr [esp + 0x28] */
	m->ecx = M32((DWORD)(m->ebx + 0x60u));	/* 4868c4: mov ecx, dword ptr [ebx + 0x60] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4868c7: inc eax */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4868c8: add edx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4868cb: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4868cd: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 4868d1: mov dword ptr [esp + 0x28], edx */
	if (m->sf != m->of) goto L_486354;	/* 4868d5: jl 0x486354 */
L_4868db:
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 4868db: mov esi, dword ptr [esp + 0x14] */
L_4868df:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4868df: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->eax + 0x18u));	/* 4868e3: mov ecx, dword ptr [eax + 0x18] */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 4868e6: mov dword ptr [esp + 0x10], ecx */
	m->edi = m->ecx;	/* 4868ea: mov edi, ecx */
L_4868ec:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4868ec: test edi, edi */
	if (!m->zf) goto L_485d04;	/* 4868ee: jne 0x485d04 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4868f4: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4868f8: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_486907;	/* 4868fa: jle 0x486907 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4868fc: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x486907u; native_call(m, M32(0x4a922cu));	/* 486901: call dword ptr [0x4a922c] */
L_486907:
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 486907: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esi + 0x3024u));	/* 48690b: mov ecx, dword ptr [esi + 0x3024] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 486911: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486912: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 486914: mov dword ptr [esp + 0x20], eax */
	if (m->sf != m->of) goto L_485ca1;	/* 486918: jl 0x485ca1 */
	m->ebx = M32((DWORD)(0x4a926cu));	/* 48691e: mov ebx, dword ptr [0x4a926c] */
	m->edi = M32((DWORD)(0x4a91fcu));	/* 486924: mov edi, dword ptr [0x4a91fc] */
L_48692a:
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 48692a: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x486931u; native_call(m, m->edi);	/* 48692f: call edi */
	m->eax = (DWORD)(m->esi + 0x90b0u);	/* 486931: lea eax, [esi + 0x90b0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486937: push eax */
	m->esp -= 4; M32(m->esp) = 0x48693au; native_call(m, m->ebx);	/* 486938: call ebx */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 48693a: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x486941u; native_call(m, m->edi);	/* 48693f: call edi */
	m->eax = (DWORD)(m->esi + 0x90f0u);	/* 486941: lea eax, [esi + 0x90f0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486947: push eax */
	m->esp -= 4; M32(m->esp) = 0x48694au; native_call(m, m->ebx);	/* 486948: call ebx */
	{ DWORD a_ = M8((DWORD)(m->esp + 0xfu)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 48694a: cmp byte ptr [esp + 0xf], 1 */
	if (!m->zf) goto L_48697e;	/* 48694f: jne 0x48697e */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 486951: mov edx, dword ptr [esp + 0x34] */
	m->edi = M32((DWORD)(0x4a9280u));	/* 486955: mov edi, dword ptr [0x4a9280] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48695b: push edx */
	{ DWORD v_ = 0xb63u; m->esp -= 4; M32(m->esp) = v_; }	/* 48695c: push 0xb63 */
	m->esp -= 4; M32(m->esp) = 0x486963u; native_call(m, m->edi);	/* 486961: call edi */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 486963: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486967: push eax */
	{ DWORD v_ = 0xb64u; m->esp -= 4; M32(m->esp) = v_; }	/* 486968: push 0xb64 */
	m->esp -= 4; M32(m->esp) = 0x48696fu; native_call(m, m->edi);	/* 48696d: call edi */
	m->edi = M32((DWORD)(0x4a9224u));	/* 48696f: mov edi, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 486975: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x48697cu; native_call(m, m->edi);	/* 48697a: call edi */
	goto L_48698f;	/* 48697c: jmp 0x48698f */
L_48697e:
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 48697e: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x486989u; native_call(m, M32(0x4a922cu));	/* 486983: call dword ptr [0x4a922c] */
	m->edi = M32((DWORD)(0x4a9224u));	/* 486989: mov edi, dword ptr [0x4a9224] */
L_48698f:
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 48698f: push 0xb44 */
	M32((DWORD)(m->esp + 0x14u)) = 0xffffffffu;	/* 486994: mov dword ptr [esp + 0x14], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x48699eu; native_call(m, m->edi);	/* 48699c: call edi */
	{ DWORD v_ = 0x405u; m->esp -= 4; M32(m->esp) = v_; }	/* 48699e: push 0x405 */
	m->esp -= 4; M32(m->esp) = 0x4869a9u; native_call(m, M32(0x4a91d0u));	/* 4869a3: call dword ptr [0x4a91d0] */
	{ DWORD v_ = 0x8037u; m->esp -= 4; M32(m->esp) = v_; }	/* 4869a9: push 0x8037 */
	m->esp -= 4; M32(m->esp) = 0x4869b0u; native_call(m, m->edi);	/* 4869ae: call edi */
	{ DWORD v_ = 0xbf800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4869b0: push 0xbf800000 */
	{ DWORD v_ = 0xbf800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4869b5: push 0xbf800000 */
	m->esp -= 4; M32(m->esp) = 0x4869c0u; native_call(m, M32(0x4a92a4u));	/* 4869ba: call dword ptr [0x4a92a4] */
	m->ecx = M32((DWORD)(m->esi + 0x905cu));	/* 4869c0: mov ecx, dword ptr [esi + 0x905c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4869c6: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4869c8: cmp ecx, eax */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 4869ca: mov dword ptr [esp + 0x24], eax */
	if (m->zf || m->sf != m->of) goto L_486b38;	/* 4869ce: jle 0x486b38 */
	m->edi = M32((DWORD)(0x4a9290u));	/* 4869d4: mov edi, dword ptr [0x4a9290] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4869da: mov dword ptr [esp + 0x20], eax */
L_4869de:
	m->ecx = M32((DWORD)(m->esi + 0x9058u));	/* 4869de: mov ecx, dword ptr [esi + 0x9058] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 4869e4: mov edx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->edx + m->ecx*1 + 0x5cu));	/* 4869e8: mov eax, dword ptr [edx + ecx + 0x5c] */
	m->ebx = (DWORD)(m->edx + m->ecx*1 + 0x0u);	/* 4869ec: lea ebx, [edx + ecx] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4869ef: cmp eax, 1 */
	if (!m->zf) goto L_486b16;	/* 4869f2: jne 0x486b16 */
	m->esp -= 4; M32(m->esp) = 0x4869feu; native_call(m, M32(0x4a9204u));	/* 4869f8: call dword ptr [0x4a9204] */
	m->eax = M32((DWORD)(m->ebx + 0x58u));	/* 4869fe: mov eax, dword ptr [ebx + 0x58] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486a01: test eax, eax */
	if (m->zf) goto L_486a0c;	/* 486a03: je 0x486a0c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486a05: push eax */
	m->esp -= 4; M32(m->esp) = 0x486a0cu; native_call(m, M32(0x4a9238u));	/* 486a06: call dword ptr [0x4a9238] */
L_486a0c:
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 486a0c: mov eax, dword ptr [ebx] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 486a0e: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486a12: cmp eax, ecx */
	if (m->zf) goto L_486a74;	/* 486a14: je 0x486a74 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486a16: test eax, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 486a18: mov dword ptr [esp + 0x10], eax */
	if (m->sf != m->of) goto L_486a69;	/* 486a1c: jl 0x486a69 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486a1e: cmp dword ptr [ebp + 8], 2 */
	if (m->zf) goto L_486a69;	/* 486a22: je 0x486a69 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 486a24: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x486a2fu; native_call(m, M32(0x4a9224u));	/* 486a29: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 486a2f: mov eax, dword ptr [esp + 0x10] */
	m->ecx = m->eax;	/* 486a33: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 486a35: and ecx, 0x800001ff */
	if (!m->sf) goto L_486a45;	/* 486a3b: jns 0x486a45 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 486a3d: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 486a3e: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 486a44: inc ecx */
L_486a45:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 486a45: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 486a46: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486a4c: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 486a4d: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 486a4f: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 486a55: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 486a58: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x486a61u; native_call(m, 0x4566c0u);	/* 486a5c: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x90acu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x90acu)) = r_; }	/* 486a61: inc dword ptr [esi + 0x90ac] */
	goto L_486a74;	/* 486a67: jmp 0x486a74 */
L_486a69:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 486a69: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x486a74u; native_call(m, M32(0x4a922cu));	/* 486a6e: call dword ptr [0x4a922c] */
L_486a74:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 486a74: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 486a78: push 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486a7a: test eax, eax */
	if (m->sf != m->of) goto L_486ace;	/* 486a7c: jl 0x486ace */
	m->esp -= 4; M32(m->esp) = 0x486a84u; native_call(m, M32(0x4a921cu));	/* 486a7e: call dword ptr [0x4a921c] */
	m->eax = (DWORD)(m->ebx + 0x1cu);	/* 486a84: lea eax, [ebx + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486a87: push eax */
	m->esp -= 4; M32(m->esp) = 0x486a8eu; native_call(m, M32(0x4a92a0u));	/* 486a88: call dword ptr [0x4a92a0] */
	m->ecx = (DWORD)(m->ebx + 0x4u);	/* 486a8e: lea ecx, [ebx + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486a91: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486a98u; native_call(m, M32(0x4a927cu));	/* 486a92: call dword ptr [0x4a927c] */
	m->edx = (DWORD)(m->ebx + 0x28u);	/* 486a98: lea edx, [ebx + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486a9b: push edx */
	m->esp -= 4; M32(m->esp) = 0x486a9eu; native_call(m, m->edi);	/* 486a9c: call edi */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 486a9e: lea eax, [ebx + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486aa1: push eax */
	m->esp -= 4; M32(m->esp) = 0x486aa8u; native_call(m, M32(0x4a92a0u));	/* 486aa2: call dword ptr [0x4a92a0] */
	m->ecx = (DWORD)(m->ebx + 0xcu);	/* 486aa8: lea ecx, [ebx + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486aab: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486ab2u; native_call(m, M32(0x4a927cu));	/* 486aac: call dword ptr [0x4a927c] */
	m->edx = (DWORD)(m->ebx + 0x38u);	/* 486ab2: lea edx, [ebx + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486ab5: push edx */
	m->esp -= 4; M32(m->esp) = 0x486ab8u; native_call(m, m->edi);	/* 486ab6: call edi */
	m->eax = (DWORD)(m->ebx + 0x24u);	/* 486ab8: lea eax, [ebx + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486abb: push eax */
	m->esp -= 4; M32(m->esp) = 0x486ac2u; native_call(m, M32(0x4a92a0u));	/* 486abc: call dword ptr [0x4a92a0] */
	m->ecx = (DWORD)(m->ebx + 0x14u);	/* 486ac2: lea ecx, [ebx + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486ac5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486accu; native_call(m, M32(0x4a927cu));	/* 486ac6: call dword ptr [0x4a927c] */
	goto L_486afe;	/* 486acc: jmp 0x486afe */
L_486ace:
	m->esp -= 4; M32(m->esp) = 0x486ad4u; native_call(m, M32(0x4a921cu));	/* 486ace: call dword ptr [0x4a921c] */
	m->edx = (DWORD)(m->ebx + 0x1cu);	/* 486ad4: lea edx, [ebx + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486ad7: push edx */
	m->esp -= 4; M32(m->esp) = 0x486adeu; native_call(m, M32(0x4a92a0u));	/* 486ad8: call dword ptr [0x4a92a0] */
	m->eax = (DWORD)(m->ebx + 0x28u);	/* 486ade: lea eax, [ebx + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486ae1: push eax */
	m->esp -= 4; M32(m->esp) = 0x486ae4u; native_call(m, m->edi);	/* 486ae2: call edi */
	m->ecx = (DWORD)(m->ebx + 0x20u);	/* 486ae4: lea ecx, [ebx + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486ae7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486aeeu; native_call(m, M32(0x4a92a0u));	/* 486ae8: call dword ptr [0x4a92a0] */
	m->edx = (DWORD)(m->ebx + 0x38u);	/* 486aee: lea edx, [ebx + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486af1: push edx */
	m->esp -= 4; M32(m->esp) = 0x486af4u; native_call(m, m->edi);	/* 486af2: call edi */
	m->eax = (DWORD)(m->ebx + 0x24u);	/* 486af4: lea eax, [ebx + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486af7: push eax */
	m->esp -= 4; M32(m->esp) = 0x486afeu; native_call(m, M32(0x4a92a0u));	/* 486af8: call dword ptr [0x4a92a0] */
L_486afe:
	{ DWORD a_ = m->ebx, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 486afe: add ebx, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 486b01: push ebx */
	m->esp -= 4; M32(m->esp) = 0x486b04u; native_call(m, m->edi);	/* 486b02: call edi */
	m->esp -= 4; M32(m->esp) = 0x486b0au; native_call(m, M32(0x4a9220u));	/* 486b04: call dword ptr [0x4a9220] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x90a4u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x90a4u)) = r_; }	/* 486b0a: inc dword ptr [esi + 0x90a4] */
	m->esp -= 4; M32(m->esp) = 0x486b16u; native_call(m, M32(0x4a9258u));	/* 486b10: call dword ptr [0x4a9258] */
L_486b16:
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 486b16: mov eax, dword ptr [esp + 0x24] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 486b1a: mov edx, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->esi + 0x905cu));	/* 486b1e: mov ecx, dword ptr [esi + 0x905c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 486b24: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 486b25: add edx, 0x60 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486b28: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 486b2a: mov dword ptr [esp + 0x24], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 486b2e: mov dword ptr [esp + 0x20], edx */
	if (m->sf != m->of) goto L_4869de;	/* 486b32: jl 0x4869de */
L_486b38:
	m->edi = M32((DWORD)(0x4a922cu));	/* 486b38: mov edi, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 486b3e: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x486b45u; native_call(m, m->edi);	/* 486b43: call edi */
	{ DWORD v_ = 0x8037u; m->esp -= 4; M32(m->esp) = v_; }	/* 486b45: push 0x8037 */
	m->esp -= 4; M32(m->esp) = 0x486b4cu; native_call(m, m->edi);	/* 486b4a: call edi */
	m->ebx = M32((DWORD)(0x4a91fcu));	/* 486b4c: mov ebx, dword ptr [0x4a91fc] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 486b52: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x486b59u; native_call(m, m->ebx);	/* 486b57: call ebx */
	m->esp -= 4; M32(m->esp) = 0x486b5fu; native_call(m, M32(0x4a9218u));	/* 486b59: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 486b5f: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x486b66u; native_call(m, m->ebx);	/* 486b64: call ebx */
	m->esp -= 4; M32(m->esp) = 0x486b6cu; native_call(m, M32(0x4a9218u));	/* 486b66: call dword ptr [0x4a9218] */
	{ DWORD a_ = M8((DWORD)(m->esp + 0xfu)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 486b6c: cmp byte ptr [esp + 0xf], 1 */
	if (!m->zf) goto L_486b9e;	/* 486b71: jne 0x486b9e */
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 486b73: mov ecx, dword ptr [esp + 0x54] */
	m->edi = M32((DWORD)(0x4a9280u));	/* 486b77: mov edi, dword ptr [0x4a9280] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486b7d: push ecx */
	{ DWORD v_ = 0xb63u; m->esp -= 4; M32(m->esp) = v_; }	/* 486b7e: push 0xb63 */
	m->esp -= 4; M32(m->esp) = 0x486b85u; native_call(m, m->edi);	/* 486b83: call edi */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 486b85: mov edx, dword ptr [esp + 0x58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486b89: push edx */
	{ DWORD v_ = 0xb64u; m->esp -= 4; M32(m->esp) = v_; }	/* 486b8a: push 0xb64 */
	m->esp -= 4; M32(m->esp) = 0x486b91u; native_call(m, m->edi);	/* 486b8f: call edi */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 486b91: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x486b9cu; native_call(m, M32(0x4a9224u));	/* 486b96: call dword ptr [0x4a9224] */
	goto L_486ba5;	/* 486b9c: jmp 0x486ba5 */
L_486b9e:
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 486b9e: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x486ba5u; native_call(m, m->edi);	/* 486ba3: call edi */
L_486ba5:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 486ba5: push 1 */
	m->esp -= 4; M32(m->esp) = 0x486badu; native_call(m, M32(0x4a921cu));	/* 486ba7: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0xffu; m->esp -= 4; M32(m->esp) = v_; }	/* 486bad: push 0xff */
	{ DWORD v_ = 0xffu; m->esp -= 4; M32(m->esp) = v_; }	/* 486bb2: push 0xff */
	{ DWORD v_ = 0xffu; m->esp -= 4; M32(m->esp) = v_; }	/* 486bb7: push 0xff */
	{ DWORD v_ = 0xffu; m->esp -= 4; M32(m->esp) = v_; }	/* 486bbc: push 0xff */
	m->esp -= 4; M32(m->esp) = 0x486bc7u; native_call(m, M32(0x4a929cu));	/* 486bc1: call dword ptr [0x4a929c] */
	m->eax = M32((DWORD)(m->esi + 0x908cu));	/* 486bc7: mov eax, dword ptr [esi + 0x908c] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 486bcd: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486bcf: cmp eax, edi */
	if (m->zf || m->sf != m->of) goto L_486c1e;	/* 486bd1: jle 0x486c1e */
	M32((DWORD)(m->esp + 0x20u)) = m->edi;	/* 486bd3: mov dword ptr [esp + 0x20], edi */
L_486bd7:
	m->ebx = M32((DWORD)(m->esi + 0x9088u));	/* 486bd7: mov ebx, dword ptr [esi + 0x9088] */
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 486bdd: mov edx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ebx, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 486be1: add ebx, edx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2u))) & 0xff) << 0);	/* 486be3: mov al, byte ptr [ebx + 2] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x1u))) & 0xff) << 0);	/* 486be6: mov cl, byte ptr [ebx + 1] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x0u))) & 0xff) << 0);	/* 486be9: mov dl, byte ptr [ebx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486beb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486bec: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486bed: push edx */
	m->esp -= 4; M32(m->esp) = 0x486bf4u; native_call(m, M32(0x4a9298u));	/* 486bee: call dword ptr [0x4a9298] */
	m->eax = (DWORD)(m->ebx + 0x4u);	/* 486bf4: lea eax, [ebx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486bf7: push eax */
	m->esp -= 4; M32(m->esp) = 0x486bfeu; native_call(m, M32(0x4a9294u));	/* 486bf8: call dword ptr [0x4a9294] */
	{ DWORD a_ = m->ebx, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 486bfe: add ebx, 0x14 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 486c01: push ebx */
	m->esp -= 4; M32(m->esp) = 0x486c08u; native_call(m, M32(0x4a9294u));	/* 486c02: call dword ptr [0x4a9294] */
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 486c08: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->esi + 0x908cu));	/* 486c0c: mov eax, dword ptr [esi + 0x908c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 486c12: inc edi */
	{ DWORD a_ = m->ecx, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 486c13: add ecx, 0x24 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486c16: cmp edi, eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 486c18: mov dword ptr [esp + 0x20], ecx */
	if (m->sf != m->of) goto L_486bd7;	/* 486c1c: jl 0x486bd7 */
L_486c1e:
	m->esp -= 4; M32(m->esp) = 0x486c24u; native_call(m, M32(0x4a9220u));	/* 486c1e: call dword ptr [0x4a9220] */
	m->eax = M32((DWORD)(m->esi + 0x905cu));	/* 486c24: mov eax, dword ptr [esi + 0x905c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 486c2a: xor ecx, ecx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 486c2c: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486c2e: cmp eax, ecx */
	M32((DWORD)(m->esi + 0x9064u)) = m->ecx;	/* 486c30: mov dword ptr [esi + 0x9064], ecx */
	if (m->zf || m->sf != m->of) goto L_486c97;	/* 486c36: jle 0x486c97 */
L_486c38:
	m->edx = M32((DWORD)(m->esi + 0x9058u));	/* 486c38: mov edx, dword ptr [esi + 0x9058] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 486c3e: add edx, ecx */
	m->eax = M32((DWORD)(m->edx + 0x5cu));	/* 486c40: mov eax, dword ptr [edx + 0x5c] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 486c43: sub eax, 2 */
	if (!m->zf) goto L_486c87;	/* 486c46: jne 0x486c87 */
	m->eax = M32((DWORD)(m->esi + 0x9064u));	/* 486c48: mov eax, dword ptr [esi + 0x9064] */
	m->ebx = M32((DWORD)(m->esi + 0x9060u));	/* 486c4e: mov ebx, dword ptr [esi + 0x9060] */
	M32((DWORD)(m->ebx + m->eax*8 + 0x0u)) = m->edx;	/* 486c54: mov dword ptr [ebx + eax*8], edx */
	m->edx = M32((DWORD)(m->esi + 0x9058u));	/* 486c57: mov edx, dword ptr [esi + 0x9058] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->edx*1 + 0x50u)));	/* 486c5d: fld dword ptr [ecx + edx + 0x50] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ecx + m->edx*1 + 0x40u));	/* 486c61: fadd dword ptr [ecx + edx + 0x40] */
	m->eax = (DWORD)(m->ecx + m->edx*1 + 0x0u);	/* 486c65: lea eax, [ecx + edx] */
	m->edx = M32((DWORD)(m->esi + 0x9060u));	/* 486c68: mov edx, dword ptr [esi + 0x9060] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x30u));	/* 486c6e: fadd dword ptr [eax + 0x30] */
	m->eax = M32((DWORD)(m->esi + 0x9064u));	/* 486c71: mov eax, dword ptr [esi + 0x9064] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa468u));	/* 486c77: fmul dword ptr [0x4aa468] */
	MF((DWORD)(m->edx + m->eax*8 + 0x4u)) = (float)ST(0); FPOP();	/* 486c7d: fstp dword ptr [edx + eax*8 + 4] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9064u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x9064u)) = r_; }	/* 486c81: inc dword ptr [esi + 0x9064] */
L_486c87:
	m->eax = M32((DWORD)(m->esi + 0x905cu));	/* 486c87: mov eax, dword ptr [esi + 0x905c] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 486c8d: inc edi */
	{ DWORD a_ = m->ecx, b_ = 0x60u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 486c8e: add ecx, 0x60 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486c91: cmp edi, eax */
	if (m->sf != m->of) goto L_486c38;	/* 486c93: jl 0x486c38 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 486c95: xor ecx, ecx */
L_486c97:
	m->eax = M32((DWORD)(m->esi + 0x9070u));	/* 486c97: mov eax, dword ptr [esi + 0x9070] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 486c9d: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486c9f: cmp eax, ecx */
	M32((DWORD)(m->esi + 0x9078u)) = m->ecx;	/* 486ca1: mov dword ptr [esi + 0x9078], ecx */
	M32((DWORD)(m->esi + 0x9080u)) = m->ecx;	/* 486ca7: mov dword ptr [esi + 0x9080], ecx */
	if (m->zf || m->sf != m->of) goto L_486d4c;	/* 486cad: jle 0x486d4c */
L_486cb3:
	m->eax = M32((DWORD)(m->esi + 0x906cu));	/* 486cb3: mov eax, dword ptr [esi + 0x906c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 486cb9: add eax, ecx */
	m->edx = M32((DWORD)(m->eax + 0x58u));	/* 486cbb: mov edx, dword ptr [eax + 0x58] */
	{ DWORD a_ = m->edx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 486cbe: sub edx, 2 */
	if (m->zf) goto L_486d01;	/* 486cc1: je 0x486d01 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 486cc3: dec edx */
	if (!m->zf) goto L_486d3a;	/* 486cc4: jne 0x486d3a */
	m->edx = M32((DWORD)(m->esi + 0x9080u));	/* 486cc6: mov edx, dword ptr [esi + 0x9080] */
	m->ebx = M32((DWORD)(m->esi + 0x907cu));	/* 486ccc: mov ebx, dword ptr [esi + 0x907c] */
	M32((DWORD)(m->ebx + m->edx*8 + 0x0u)) = m->eax;	/* 486cd2: mov dword ptr [ebx + edx*8], eax */
	m->eax = M32((DWORD)(m->esi + 0x906cu));	/* 486cd5: mov eax, dword ptr [esi + 0x906c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 486cdb: add eax, ecx */
	m->edx = M32((DWORD)(m->esi + 0x9080u));	/* 486cdd: mov edx, dword ptr [esi + 0x9080] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x30u)));	/* 486ce3: fld dword ptr [eax + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 486ce6: fadd dword ptr [eax + 0x20] */
	m->eax = M32((DWORD)(m->esi + 0x907cu));	/* 486ce9: mov eax, dword ptr [esi + 0x907c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f4u));	/* 486cef: fmul dword ptr [0x4a94f4] */
	MF((DWORD)(m->eax + m->edx*8 + 0x4u)) = (float)ST(0); FPOP();	/* 486cf5: fstp dword ptr [eax + edx*8 + 4] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9080u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x9080u)) = r_; }	/* 486cf9: inc dword ptr [esi + 0x9080] */
	goto L_486d3a;	/* 486cff: jmp 0x486d3a */
L_486d01:
	m->edx = M32((DWORD)(m->esi + 0x9078u));	/* 486d01: mov edx, dword ptr [esi + 0x9078] */
	m->ebx = M32((DWORD)(m->esi + 0x9074u));	/* 486d07: mov ebx, dword ptr [esi + 0x9074] */
	M32((DWORD)(m->ebx + m->edx*8 + 0x0u)) = m->eax;	/* 486d0d: mov dword ptr [ebx + edx*8], eax */
	m->eax = M32((DWORD)(m->esi + 0x906cu));	/* 486d10: mov eax, dword ptr [esi + 0x906c] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 486d16: add eax, ecx */
	m->edx = M32((DWORD)(m->esi + 0x9078u));	/* 486d18: mov edx, dword ptr [esi + 0x9078] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x30u)));	/* 486d1e: fld dword ptr [eax + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->eax + 0x20u));	/* 486d21: fadd dword ptr [eax + 0x20] */
	m->eax = M32((DWORD)(m->esi + 0x9074u));	/* 486d24: mov eax, dword ptr [esi + 0x9074] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94f4u));	/* 486d2a: fmul dword ptr [0x4a94f4] */
	MF((DWORD)(m->eax + m->edx*8 + 0x4u)) = (float)ST(0); FPOP();	/* 486d30: fstp dword ptr [eax + edx*8 + 4] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9078u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x9078u)) = r_; }	/* 486d34: inc dword ptr [esi + 0x9078] */
L_486d3a:
	m->eax = M32((DWORD)(m->esi + 0x9070u));	/* 486d3a: mov eax, dword ptr [esi + 0x9070] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 486d40: inc edi */
	{ DWORD a_ = m->ecx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 486d41: add ecx, 0x5c */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486d44: cmp edi, eax */
	if (m->sf != m->of) goto L_486cb3;	/* 486d46: jl 0x486cb3 */
L_486d4c:
	m->edi = M32((DWORD)(0x4a91fcu));	/* 486d4c: mov edi, dword ptr [0x4a91fc] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 486d52: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x486d59u; native_call(m, m->edi);	/* 486d57: call edi */
	m->ebx = M32((DWORD)(0x4a9218u));	/* 486d59: mov ebx, dword ptr [0x4a9218] */
	m->esp -= 4; M32(m->esp) = 0x486d61u; native_call(m, m->ebx);	/* 486d5f: call ebx */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 486d61: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x486d68u; native_call(m, m->edi);	/* 486d66: call edi */
	m->esp -= 4; M32(m->esp) = 0x486d6au; native_call(m, m->ebx);	/* 486d68: call ebx */
	{ DWORD a_ = M8((DWORD)(m->esp + 0xfu)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 486d6a: cmp byte ptr [esp + 0xf], 1 */
	if (!m->zf) goto L_486da2;	/* 486d6f: jne 0x486da2 */
	m->ecx = M32((DWORD)(m->esp + 0x54u));	/* 486d71: mov ecx, dword ptr [esp + 0x54] */
	m->edi = M32((DWORD)(0x4a9280u));	/* 486d75: mov edi, dword ptr [0x4a9280] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486d7b: push ecx */
	{ DWORD v_ = 0xb63u; m->esp -= 4; M32(m->esp) = v_; }	/* 486d7c: push 0xb63 */
	m->esp -= 4; M32(m->esp) = 0x486d83u; native_call(m, m->edi);	/* 486d81: call edi */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 486d83: mov edx, dword ptr [esp + 0x58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486d87: push edx */
	{ DWORD v_ = 0xb64u; m->esp -= 4; M32(m->esp) = v_; }	/* 486d88: push 0xb64 */
	m->esp -= 4; M32(m->esp) = 0x486d8fu; native_call(m, m->edi);	/* 486d8d: call edi */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 486d8f: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x486d9au; native_call(m, M32(0x4a9224u));	/* 486d94: call dword ptr [0x4a9224] */
	m->edi = M32((DWORD)(0x4a922cu));	/* 486d9a: mov edi, dword ptr [0x4a922c] */
	goto L_486daf;	/* 486da0: jmp 0x486daf */
L_486da2:
	m->edi = M32((DWORD)(0x4a922cu));	/* 486da2: mov edi, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 486da8: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x486dafu; native_call(m, m->edi);	/* 486dad: call edi */
L_486daf:
	m->eax = M32((DWORD)(m->esi + 0x9064u));	/* 486daf: mov eax, dword ptr [esi + 0x9064] */
	m->ecx = M32((DWORD)(m->esi + 0x9060u));	/* 486db5: mov ecx, dword ptr [esi + 0x9060] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 486dbb: dec eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 486dbc: xor ebx, ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486dbe: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 486dbf: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486dc0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486dc6u; native_call(m, 0x490f80u);	/* 486dc1: call 0x490f80 */
	m->edx = M32((DWORD)(m->esi + 0x9078u));	/* 486dc6: mov edx, dword ptr [esi + 0x9078] */
	m->eax = M32((DWORD)(m->esi + 0x9074u));	/* 486dcc: mov eax, dword ptr [esi + 0x9074] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 486dd2: dec edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486dd3: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 486dd4: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486dd5: push eax */
	m->esp -= 4; M32(m->esp) = 0x486ddbu; native_call(m, 0x491190u);	/* 486dd6: call 0x491190 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 486ddb: add esp, 0x18 */
	M32((DWORD)(m->esp + 0x24u)) = m->ebx;	/* 486dde: mov dword ptr [esp + 0x24], ebx */
	M32((DWORD)(m->esp + 0x18u)) = m->ebx;	/* 486de2: mov dword ptr [esp + 0x18], ebx */
	M32((DWORD)(m->esp + 0x10u)) = 0xffffffffu;	/* 486de6: mov dword ptr [esp + 0x10], 0xffffffff */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 486dee: push 0xb44 */
	M32((DWORD)(m->esp + 0x2cu)) = m->ebx;	/* 486df3: mov dword ptr [esp + 0x2c], ebx */
	m->esp -= 4; M32(m->esp) = 0x486df9u; native_call(m, m->edi);	/* 486df7: call edi */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 486df9: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x486e00u; native_call(m, m->edi);	/* 486dfe: call edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 486e00: push 7 */
	m->esp -= 4; M32(m->esp) = 0x486e08u; native_call(m, M32(0x4a921cu));	/* 486e02: call dword ptr [0x4a921c] */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x9064u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486e08: cmp dword ptr [esi + 0x9064], ebx */
	if (m->zf || m->sf != m->of) goto L_486e18;	/* 486e0e: jle 0x486e18 */
	m->edi = M32((DWORD)(m->esi + 0x9060u));	/* 486e10: mov edi, dword ptr [esi + 0x9060] */
	goto L_486e1a;	/* 486e16: jmp 0x486e1a */
L_486e18:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 486e18: xor edi, edi */
L_486e1a:
	m->eax = M32((DWORD)(m->esi + 0x9078u));	/* 486e1a: mov eax, dword ptr [esi + 0x9078] */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 486e20: mov dword ptr [esp + 0x14], edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486e24: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_486e30;	/* 486e26: jle 0x486e30 */
	m->ebx = M32((DWORD)(m->esi + 0x9074u));	/* 486e28: mov ebx, dword ptr [esi + 0x9074] */
	goto L_486e32;	/* 486e2e: jmp 0x486e32 */
L_486e30:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 486e30: xor ebx, ebx */
L_486e32:
	M32((DWORD)(m->esp + 0x1cu)) = m->ebx;	/* 486e32: mov dword ptr [esp + 0x1c], ebx */
L_486e36:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486e36: test ebx, ebx */
	if (m->zf) goto L_486e52;	/* 486e38: je 0x486e52 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486e3a: test edi, edi */
	if (m->zf) goto L_486e4b;	/* 486e3c: je 0x486e4b */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 486e3e: fld dword ptr [edi + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebx + 0x4u)); FPOP();	/* 486e41: fcomp dword ptr [ebx + 4] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 486e44: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 486e46: test ah, 1 */
	if (!m->zf) goto L_486e5a;	/* 486e49: jne 0x486e5a */
L_486e4b:
	m->eax = 0x1u;	/* 486e4b: mov eax, 1 */
	goto L_486e5f;	/* 486e50: jmp 0x486e5f */
L_486e52:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486e52: test edi, edi */
	if (m->zf) goto L_487160;	/* 486e54: je 0x487160 */
L_486e5a:
	m->eax = 0x2u;	/* 486e5a: mov eax, 2 */
L_486e5f:
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 486e5f: dec eax */
	if (m->zf) goto L_486fe2;	/* 486e60: je 0x486fe2 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 486e66: dec eax */
	if (!m->zf) goto L_486e36;	/* 486e67: jne 0x486e36 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x28u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486e69: cmp dword ptr [esp + 0x28], 1 */
	if (m->zf) goto L_486e99;	/* 486e6e: je 0x486e99 */
	m->esp -= 4; M32(m->esp) = 0x486e76u; native_call(m, M32(0x4a9220u));	/* 486e70: call dword ptr [0x4a9220] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0xfu))) & 0xff) << 0);	/* 486e76: mov al, byte ptr [esp + 0xf] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 486e7a: test al, al */
	if (m->zf) goto L_486e89;	/* 486e7c: je 0x486e89 */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 486e7e: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x486e89u; native_call(m, M32(0x4a9224u));	/* 486e83: call dword ptr [0x4a9224] */
L_486e89:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 486e89: push 4 */
	m->esp -= 4; M32(m->esp) = 0x486e91u; native_call(m, M32(0x4a921cu));	/* 486e8b: call dword ptr [0x4a921c] */
	M32((DWORD)(m->esp + 0x28u)) = 0x1u;	/* 486e91: mov dword ptr [esp + 0x28], 1 */
L_486e99:
	m->ebx = M32((DWORD)(m->edi + 0x0u));	/* 486e99: mov ebx, dword ptr [edi] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 486e9b: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486e9f: cmp dword ptr [ebx], ecx */
	if (m->zf) goto L_486f0f;	/* 486ea1: je 0x486f0f */
	m->esp -= 4; M32(m->esp) = 0x486ea9u; native_call(m, M32(0x4a9220u));	/* 486ea3: call dword ptr [0x4a9220] */
	m->edi = M32((DWORD)(m->ebx + 0x0u));	/* 486ea9: mov edi, dword ptr [ebx] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486eab: test edi, edi */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 486ead: mov dword ptr [esp + 0x10], edi */
	if (m->sf != m->of) goto L_486efc;	/* 486eb1: jl 0x486efc */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486eb3: cmp dword ptr [ebp + 8], 2 */
	if (m->zf) goto L_486efc;	/* 486eb7: je 0x486efc */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 486eb9: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x486ec4u; native_call(m, M32(0x4a9224u));	/* 486ebe: call dword ptr [0x4a9224] */
	m->edx = m->edi;	/* 486ec4: mov edx, edi */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 486ec6: and edx, 0x800001ff */
	if (!m->sf) goto L_486ed6;	/* 486ecc: jns 0x486ed6 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 486ece: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 486ecf: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 486ed5: inc edx */
L_486ed6:
	m->eax = m->edi;	/* 486ed6: mov eax, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486ed8: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 486ed9: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 486edf: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 486ee0: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 486ee6: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 486ee8: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 486eeb: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x486ef4u; native_call(m, 0x4566c0u);	/* 486eef: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x90acu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x90acu)) = r_; }	/* 486ef4: inc dword ptr [esi + 0x90ac] */
	goto L_486f07;	/* 486efa: jmp 0x486f07 */
L_486efc:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 486efc: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x486f07u; native_call(m, M32(0x4a922cu));	/* 486f01: call dword ptr [0x4a922c] */
L_486f07:
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 486f07: push 4 */
	m->esp -= 4; M32(m->esp) = 0x486f0fu; native_call(m, M32(0x4a921cu));	/* 486f09: call dword ptr [0x4a921c] */
L_486f0f:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 486f0f: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486f13: test eax, eax */
	if (m->sf != m->of) goto L_486f67;	/* 486f15: jl 0x486f67 */
	m->edx = (DWORD)(m->ebx + 0x1cu);	/* 486f17: lea edx, [ebx + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f1a: push edx */
	m->esp -= 4; M32(m->esp) = 0x486f21u; native_call(m, M32(0x4a92a0u));	/* 486f1b: call dword ptr [0x4a92a0] */
	m->eax = (DWORD)(m->ebx + 0x4u);	/* 486f21: lea eax, [ebx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486f24: push eax */
	m->esp -= 4; M32(m->esp) = 0x486f2bu; native_call(m, M32(0x4a927cu));	/* 486f25: call dword ptr [0x4a927c] */
	m->edi = M32((DWORD)(0x4a9294u));	/* 486f2b: mov edi, dword ptr [0x4a9294] */
	m->ecx = (DWORD)(m->ebx + 0x28u);	/* 486f31: lea ecx, [ebx + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f34: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486f37u; native_call(m, m->edi);	/* 486f35: call edi */
	m->edx = (DWORD)(m->ebx + 0x20u);	/* 486f37: lea edx, [ebx + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f3a: push edx */
	m->esp -= 4; M32(m->esp) = 0x486f41u; native_call(m, M32(0x4a92a0u));	/* 486f3b: call dword ptr [0x4a92a0] */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 486f41: lea eax, [ebx + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486f44: push eax */
	m->esp -= 4; M32(m->esp) = 0x486f4bu; native_call(m, M32(0x4a927cu));	/* 486f45: call dword ptr [0x4a927c] */
	m->ecx = (DWORD)(m->ebx + 0x38u);	/* 486f4b: lea ecx, [ebx + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f4e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486f51u; native_call(m, m->edi);	/* 486f4f: call edi */
	m->edx = (DWORD)(m->ebx + 0x24u);	/* 486f51: lea edx, [ebx + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f54: push edx */
	m->esp -= 4; M32(m->esp) = 0x486f5bu; native_call(m, M32(0x4a92a0u));	/* 486f55: call dword ptr [0x4a92a0] */
	m->eax = (DWORD)(m->ebx + 0x14u);	/* 486f5b: lea eax, [ebx + 0x14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486f5e: push eax */
	m->esp -= 4; M32(m->esp) = 0x486f65u; native_call(m, M32(0x4a927cu));	/* 486f5f: call dword ptr [0x4a927c] */
	goto L_486f97;	/* 486f65: jmp 0x486f97 */
L_486f67:
	m->ecx = (DWORD)(m->ebx + 0x1cu);	/* 486f67: lea ecx, [ebx + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f6a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486f71u; native_call(m, M32(0x4a92a0u));	/* 486f6b: call dword ptr [0x4a92a0] */
	m->edi = M32((DWORD)(0x4a9294u));	/* 486f71: mov edi, dword ptr [0x4a9294] */
	m->edx = (DWORD)(m->ebx + 0x28u);	/* 486f77: lea edx, [ebx + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f7a: push edx */
	m->esp -= 4; M32(m->esp) = 0x486f7du; native_call(m, m->edi);	/* 486f7b: call edi */
	m->eax = (DWORD)(m->ebx + 0x20u);	/* 486f7d: lea eax, [ebx + 0x20] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 486f80: push eax */
	m->esp -= 4; M32(m->esp) = 0x486f87u; native_call(m, M32(0x4a92a0u));	/* 486f81: call dword ptr [0x4a92a0] */
	m->ecx = (DWORD)(m->ebx + 0x38u);	/* 486f87: lea ecx, [ebx + 0x38] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f8a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x486f8du; native_call(m, m->edi);	/* 486f8b: call edi */
	m->edx = (DWORD)(m->ebx + 0x24u);	/* 486f8d: lea edx, [ebx + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f90: push edx */
	m->esp -= 4; M32(m->esp) = 0x486f97u; native_call(m, M32(0x4a92a0u));	/* 486f91: call dword ptr [0x4a92a0] */
L_486f97:
	{ DWORD a_ = m->ebx, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 486f97: add ebx, 0x48 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 486f9a: push ebx */
	m->esp -= 4; M32(m->esp) = 0x486f9du; native_call(m, m->edi);	/* 486f9b: call edi */
	m->edi = M32((DWORD)(m->esi + 0x90a4u));	/* 486f9d: mov edi, dword ptr [esi + 0x90a4] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 486fa3: mov eax, dword ptr [esp + 0x24] */
	m->ecx = M32((DWORD)(m->esi + 0x9064u));	/* 486fa7: mov ecx, dword ptr [esi + 0x9064] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 486fad: inc edi */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 486fae: inc eax */
	M32((DWORD)(m->esi + 0x90a4u)) = m->edi;	/* 486faf: mov dword ptr [esi + 0x90a4], edi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 486fb5: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 486fb7: mov dword ptr [esp + 0x24], eax */
	if (m->sf == m->of) goto L_486fd3;	/* 486fbb: jge 0x486fd3 */
	m->ecx = M32((DWORD)(m->esi + 0x9060u));	/* 486fbd: mov ecx, dword ptr [esi + 0x9060] */
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 486fc3: mov ebx, dword ptr [esp + 0x1c] */
	m->edi = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 486fc7: lea edi, [ecx + eax*8] */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 486fca: mov dword ptr [esp + 0x14], edi */
	goto L_486e36;	/* 486fce: jmp 0x486e36 */
L_486fd3:
	m->ebx = M32((DWORD)(m->esp + 0x1cu));	/* 486fd3: mov ebx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 486fd7: xor edi, edi */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 486fd9: mov dword ptr [esp + 0x14], edi */
	goto L_486e36;	/* 486fdd: jmp 0x486e36 */
L_486fe2:
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 486fe2: mov eax, dword ptr [esp + 0x28] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 486fe6: test eax, eax */
	if (m->zf) goto L_48700b;	/* 486fe8: je 0x48700b */
	m->esp -= 4; M32(m->esp) = 0x486ff0u; native_call(m, M32(0x4a9220u));	/* 486fea: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 486ff0: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x486ffbu; native_call(m, M32(0x4a922cu));	/* 486ff5: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 486ffb: push 7 */
	m->esp -= 4; M32(m->esp) = 0x487003u; native_call(m, M32(0x4a921cu));	/* 486ffd: call dword ptr [0x4a921c] */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 487003: mov dword ptr [esp + 0x28], 0 */
L_48700b:
	m->ebx = M32((DWORD)(m->ebx + 0x0u));	/* 48700b: mov ebx, dword ptr [ebx] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 48700d: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487011: cmp dword ptr [ebx], edx */
	if (m->zf) goto L_487090;	/* 487013: je 0x487090 */
	m->esp -= 4; M32(m->esp) = 0x48701bu; native_call(m, M32(0x4a9220u));	/* 487015: call dword ptr [0x4a9220] */
	m->edi = M32((DWORD)(m->ebx + 0x0u));	/* 48701b: mov edi, dword ptr [ebx] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48701d: test edi, edi */
	M32((DWORD)(m->esp + 0x10u)) = m->edi;	/* 48701f: mov dword ptr [esp + 0x10], edi */
	if (m->sf != m->of) goto L_48707b;	/* 487023: jl 0x48707b */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487025: cmp dword ptr [ebp + 8], 2 */
	if (m->zf) goto L_48707b;	/* 487029: je 0x48707b */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48702b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x487036u; native_call(m, M32(0x4a9224u));	/* 487030: call dword ptr [0x4a9224] */
	m->eax = m->edi;	/* 487036: mov eax, edi */
	{ DWORD a_ = m->eax, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 487038: and eax, 0x800001ff */
	if (!m->sf) goto L_487046;	/* 48703d: jns 0x487046 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48703f: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 487040: or eax, 0xfffffe00 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 487045: inc eax */
L_487046:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487046: push eax */
	m->eax = m->edi;	/* 487047: mov eax, edi */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 487049: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48704f: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 487050: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 487056: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 487058: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 48705b: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x487064u; native_call(m, 0x4566c0u);	/* 48705f: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esi + 0x90acu));	/* 487064: mov eax, dword ptr [esi + 0x90ac] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 48706a: push 7 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48706c: inc eax */
	M32((DWORD)(m->esi + 0x90acu)) = m->eax;	/* 48706d: mov dword ptr [esi + 0x90ac], eax */
	m->esp -= 4; M32(m->esp) = 0x487079u; native_call(m, M32(0x4a921cu));	/* 487073: call dword ptr [0x4a921c] */
	goto L_487094;	/* 487079: jmp 0x487094 */
L_48707b:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48707b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x487086u; native_call(m, M32(0x4a922cu));	/* 487080: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 487086: push 7 */
	m->esp -= 4; M32(m->esp) = 0x48708eu; native_call(m, M32(0x4a921cu));	/* 487088: call dword ptr [0x4a921c] */
	goto L_487094;	/* 48708e: jmp 0x487094 */
L_487090:
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 487090: mov edi, dword ptr [esp + 0x10] */
L_487094:
	m->edx = (DWORD)(m->ebx + 0x14u);	/* 487094: lea edx, [ebx + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487097: push edx */
	m->esp -= 4; M32(m->esp) = 0x48709eu; native_call(m, M32(0x4a92a0u));	/* 487098: call dword ptr [0x4a92a0] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48709e: test edi, edi */
	if (m->sf != m->of) goto L_4870fb;	/* 4870a0: jl 0x4870fb */
	m->edi = (DWORD)(m->ebx + 0x4u);	/* 4870a2: lea edi, [ebx + 4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4870a5: push edi */
	m->esp -= 4; M32(m->esp) = 0x4870acu; native_call(m, M32(0x4a927cu));	/* 4870a6: call dword ptr [0x4a927c] */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 4870ac: lea eax, [ebx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4870af: push eax */
	m->esp -= 4; M32(m->esp) = 0x4870b6u; native_call(m, M32(0x4a9294u));	/* 4870b0: call dword ptr [0x4a9294] */
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 4870b6: mov ecx, dword ptr [ebx + 8] */
	m->edx = M32((DWORD)(m->ebx + 0xcu));	/* 4870b9: mov edx, dword ptr [ebx + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4870bc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4870bd: push edx */
	m->esp -= 4; M32(m->esp) = 0x4870c4u; native_call(m, M32(0x4a920cu));	/* 4870be: call dword ptr [0x4a920c] */
	m->eax = (DWORD)(m->ebx + 0x38u);	/* 4870c4: lea eax, [ebx + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4870c7: push eax */
	m->esp -= 4; M32(m->esp) = 0x4870ceu; native_call(m, M32(0x4a9294u));	/* 4870c8: call dword ptr [0x4a9294] */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 4870ce: lea eax, [ebx + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4870d1: push eax */
	m->esp -= 4; M32(m->esp) = 0x4870d8u; native_call(m, M32(0x4a927cu));	/* 4870d2: call dword ptr [0x4a927c] */
	m->ecx = (DWORD)(m->ebx + 0x28u);	/* 4870d8: lea ecx, [ebx + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4870db: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4870e2u; native_call(m, M32(0x4a9294u));	/* 4870dc: call dword ptr [0x4a9294] */
	m->edx = M32((DWORD)(m->ebx + 0x10u));	/* 4870e2: mov edx, dword ptr [ebx + 0x10] */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 4870e5: mov eax, dword ptr [edi] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4870e7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4870e8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4870efu; native_call(m, M32(0x4a920cu));	/* 4870e9: call dword ptr [0x4a920c] */
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4870ef: add ebx, 0x18 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4870f2: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4870f9u; native_call(m, M32(0x4a9294u));	/* 4870f3: call dword ptr [0x4a9294] */
	goto L_487119;	/* 4870f9: jmp 0x487119 */
L_4870fb:
	m->edi = M32((DWORD)(0x4a9294u));	/* 4870fb: mov edi, dword ptr [0x4a9294] */
	m->ecx = (DWORD)(m->ebx + 0x48u);	/* 487101: lea ecx, [ebx + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487104: push ecx */
	m->esp -= 4; M32(m->esp) = 0x487107u; native_call(m, m->edi);	/* 487105: call edi */
	m->edx = (DWORD)(m->ebx + 0x38u);	/* 487107: lea edx, [ebx + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48710a: push edx */
	m->esp -= 4; M32(m->esp) = 0x48710du; native_call(m, m->edi);	/* 48710b: call edi */
	m->eax = (DWORD)(m->ebx + 0x28u);	/* 48710d: lea eax, [ebx + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487110: push eax */
	m->esp -= 4; M32(m->esp) = 0x487113u; native_call(m, m->edi);	/* 487111: call edi */
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 487113: add ebx, 0x18 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 487116: push ebx */
	m->esp -= 4; M32(m->esp) = 0x487119u; native_call(m, m->edi);	/* 487117: call edi */
L_487119:
	m->edi = M32((DWORD)(m->esi + 0x90a4u));	/* 487119: mov edi, dword ptr [esi + 0x90a4] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 48711f: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esi + 0x9078u));	/* 487123: mov ecx, dword ptr [esi + 0x9078] */
	{ DWORD a_ = m->edi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 487129: add edi, 2 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48712c: inc eax */
	M32((DWORD)(m->esi + 0x90a4u)) = m->edi;	/* 48712d: mov dword ptr [esi + 0x90a4], edi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487133: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 487135: mov dword ptr [esp + 0x18], eax */
	if (m->sf == m->of) goto L_487151;	/* 487139: jge 0x487151 */
	m->ecx = M32((DWORD)(m->esi + 0x9074u));	/* 48713b: mov ecx, dword ptr [esi + 0x9074] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 487141: mov edi, dword ptr [esp + 0x14] */
	m->ebx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 487145: lea ebx, [ecx + eax*8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebx;	/* 487148: mov dword ptr [esp + 0x1c], ebx */
	goto L_486e36;	/* 48714c: jmp 0x486e36 */
L_487151:
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 487151: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 487155: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebx;	/* 487157: mov dword ptr [esp + 0x1c], ebx */
	goto L_486e36;	/* 48715b: jmp 0x486e36 */
L_487160:
	m->esp -= 4; M32(m->esp) = 0x487166u; native_call(m, M32(0x4a9220u));	/* 487160: call dword ptr [0x4a9220] */
	m->ebx = M32((DWORD)(0x4a922cu));	/* 487166: mov ebx, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48716c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x487173u; native_call(m, m->ebx);	/* 487171: call ebx */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 487173: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x48717eu; native_call(m, M32(0x4a91fcu));	/* 487178: call dword ptr [0x4a91fc] */
	m->edi = M32((DWORD)(0x4a9218u));	/* 48717e: mov edi, dword ptr [0x4a9218] */
	m->esp -= 4; M32(m->esp) = 0x487186u; native_call(m, m->edi);	/* 487184: call edi */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 487186: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x487191u; native_call(m, M32(0x4a91fcu));	/* 48718b: call dword ptr [0x4a91fc] */
	m->esp -= 4; M32(m->esp) = 0x487193u; native_call(m, m->edi);	/* 487191: call edi */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 487193: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x48719au; native_call(m, m->ebx);	/* 487198: call ebx */
	m->edx = M32((DWORD)(m->esi + 0x9080u));	/* 48719a: mov edx, dword ptr [esi + 0x9080] */
	m->eax = M32((DWORD)(m->esi + 0x907cu));	/* 4871a0: mov eax, dword ptr [esi + 0x907c] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4871a6: dec edx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4871a7: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4871a8: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4871aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4871b0u; native_call(m, 0x491190u);	/* 4871ab: call 0x491190 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4871b0: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4871b3: or edi, 0xffffffff */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 4871b6: push 0xb44 */
	m->esp -= 4; M32(m->esp) = 0x4871bdu; native_call(m, m->ebx);	/* 4871bb: call ebx */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 4871bd: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x4871c4u; native_call(m, m->ebx);	/* 4871c2: call ebx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4871c4: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4871ccu; native_call(m, M32(0x4a921cu));	/* 4871c6: call dword ptr [0x4a921c] */
	m->eax = M32((DWORD)(m->esi + 0x9080u));	/* 4871cc: mov eax, dword ptr [esi + 0x9080] */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 4871d2: mov dword ptr [esp + 0x18], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4871da: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_487305;	/* 4871dc: jle 0x487305 */
L_4871e2:
	m->ecx = M32((DWORD)(m->esi + 0x907cu));	/* 4871e2: mov ecx, dword ptr [esi + 0x907c] */
	m->edx = M32((DWORD)(m->esp + 0x18u));	/* 4871e8: mov edx, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->ecx + m->edx*8 + 0x0u));	/* 4871ec: mov ebx, dword ptr [ecx + edx*8] */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4871ef: cmp dword ptr [ebx], edi */
	if (m->zf) goto L_487259;	/* 4871f1: je 0x487259 */
	m->esp -= 4; M32(m->esp) = 0x4871f9u; native_call(m, M32(0x4a9220u));	/* 4871f3: call dword ptr [0x4a9220] */
	m->edi = M32((DWORD)(m->ebx + 0x0u));	/* 4871f9: mov edi, dword ptr [ebx] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4871fb: test edi, edi */
	if (m->sf != m->of) goto L_487246;	/* 4871fd: jl 0x487246 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4871ff: cmp dword ptr [ebp + 8], 2 */
	if (m->zf) goto L_487246;	/* 487203: je 0x487246 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 487205: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x487210u; native_call(m, M32(0x4a9224u));	/* 48720a: call dword ptr [0x4a9224] */
	m->eax = m->edi;	/* 487210: mov eax, edi */
	{ DWORD a_ = m->eax, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 487212: and eax, 0x800001ff */
	if (!m->sf) goto L_487220;	/* 487217: jns 0x487220 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 487219: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48721a: or eax, 0xfffffe00 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48721f: inc eax */
L_487220:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487220: push eax */
	m->eax = m->edi;	/* 487221: mov eax, edi */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 487223: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 487229: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48722a: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 487230: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 487232: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 487235: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x48723eu; native_call(m, 0x4566c0u);	/* 487239: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x90acu)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0x90acu)) = r_; }	/* 48723e: inc dword ptr [esi + 0x90ac] */
	goto L_487251;	/* 487244: jmp 0x487251 */
L_487246:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 487246: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x487251u; native_call(m, M32(0x4a922cu));	/* 48724b: call dword ptr [0x4a922c] */
L_487251:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 487251: push 7 */
	m->esp -= 4; M32(m->esp) = 0x487259u; native_call(m, M32(0x4a921cu));	/* 487253: call dword ptr [0x4a921c] */
L_487259:
	m->edx = (DWORD)(m->ebx + 0x14u);	/* 487259: lea edx, [ebx + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48725c: push edx */
	m->esp -= 4; M32(m->esp) = 0x487263u; native_call(m, M32(0x4a92a0u));	/* 48725d: call dword ptr [0x4a92a0] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487263: test edi, edi */
	if (m->sf != m->of) goto L_4872b7;	/* 487265: jl 0x4872b7 */
	m->eax = (DWORD)(m->ebx + 0x4u);	/* 487267: lea eax, [ebx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48726a: push eax */
	m->esp -= 4; M32(m->esp) = 0x487271u; native_call(m, M32(0x4a927cu));	/* 48726b: call dword ptr [0x4a927c] */
	m->eax = (DWORD)(m->ebx + 0x48u);	/* 487271: lea eax, [ebx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487274: push eax */
	m->esp -= 4; M32(m->esp) = 0x48727bu; native_call(m, M32(0x4a9294u));	/* 487275: call dword ptr [0x4a9294] */
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 48727b: mov ecx, dword ptr [ebx + 8] */
	m->edx = M32((DWORD)(m->ebx + 0xcu));	/* 48727e: mov edx, dword ptr [ebx + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487281: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487282: push edx */
	m->esp -= 4; M32(m->esp) = 0x487289u; native_call(m, M32(0x4a920cu));	/* 487283: call dword ptr [0x4a920c] */
	m->eax = (DWORD)(m->ebx + 0x38u);	/* 487289: lea eax, [ebx + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48728c: push eax */
	m->esp -= 4; M32(m->esp) = 0x487293u; native_call(m, M32(0x4a9294u));	/* 48728d: call dword ptr [0x4a9294] */
	m->eax = (DWORD)(m->ebx + 0xcu);	/* 487293: lea eax, [ebx + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 487296: push eax */
	m->esp -= 4; M32(m->esp) = 0x48729du; native_call(m, M32(0x4a927cu));	/* 487297: call dword ptr [0x4a927c] */
	m->ecx = (DWORD)(m->ebx + 0x28u);	/* 48729d: lea ecx, [ebx + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4872a0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4872a7u; native_call(m, M32(0x4a9294u));	/* 4872a1: call dword ptr [0x4a9294] */
	m->edx = M32((DWORD)(m->ebx + 0x10u));	/* 4872a7: mov edx, dword ptr [ebx + 0x10] */
	m->eax = M32((DWORD)(m->ebx + 0x4u));	/* 4872aa: mov eax, dword ptr [ebx + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4872ad: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4872ae: push eax */
	m->esp -= 4; M32(m->esp) = 0x4872b5u; native_call(m, M32(0x4a920cu));	/* 4872af: call dword ptr [0x4a920c] */
	goto L_4872d5;	/* 4872b5: jmp 0x4872d5 */
L_4872b7:
	m->ecx = (DWORD)(m->ebx + 0x48u);	/* 4872b7: lea ecx, [ebx + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4872ba: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4872c1u; native_call(m, M32(0x4a9294u));	/* 4872bb: call dword ptr [0x4a9294] */
	m->edx = (DWORD)(m->ebx + 0x38u);	/* 4872c1: lea edx, [ebx + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4872c4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4872cbu; native_call(m, M32(0x4a9294u));	/* 4872c5: call dword ptr [0x4a9294] */
	m->eax = (DWORD)(m->ebx + 0x28u);	/* 4872cb: lea eax, [ebx + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4872ce: push eax */
	m->esp -= 4; M32(m->esp) = 0x4872d5u; native_call(m, M32(0x4a9294u));	/* 4872cf: call dword ptr [0x4a9294] */
L_4872d5:
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4872d5: add ebx, 0x18 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4872d8: push ebx */
	m->esp -= 4; M32(m->esp) = 0x4872dfu; native_call(m, M32(0x4a9294u));	/* 4872d9: call dword ptr [0x4a9294] */
	m->ebx = M32((DWORD)(m->esi + 0x90a4u));	/* 4872df: mov ebx, dword ptr [esi + 0x90a4] */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4872e5: mov eax, dword ptr [esp + 0x18] */
	m->ecx = M32((DWORD)(m->esi + 0x9080u));	/* 4872e9: mov ecx, dword ptr [esi + 0x9080] */
	{ DWORD a_ = m->ebx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4872ef: add ebx, 2 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4872f2: inc eax */
	M32((DWORD)(m->esi + 0x90a4u)) = m->ebx;	/* 4872f3: mov dword ptr [esi + 0x90a4], ebx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4872f9: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4872fb: mov dword ptr [esp + 0x18], eax */
	if (m->sf != m->of) goto L_4871e2;	/* 4872ff: jl 0x4871e2 */
L_487305:
	m->esp -= 4; M32(m->esp) = 0x48730bu; native_call(m, M32(0x4a9220u));	/* 487305: call dword ptr [0x4a9220] */
	m->edi = M32((DWORD)(0x4a922cu));	/* 48730b: mov edi, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 487311: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x487318u; native_call(m, m->edi);	/* 487316: call edi */
	m->esi = M32((DWORD)(0x4a9224u));	/* 487318: mov esi, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 48731e: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x487325u; native_call(m, m->esi);	/* 487323: call esi */
	{ DWORD a_ = M8((DWORD)(m->esp + 0xfu)), b_ = 0x1u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 487325: cmp byte ptr [esp + 0xf], 1 */
	if (!m->zf) goto L_487353;	/* 48732a: jne 0x487353 */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 48732c: mov ecx, dword ptr [esp + 0x34] */
	m->edi = M32((DWORD)(0x4a9280u));	/* 487330: mov edi, dword ptr [0x4a9280] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487336: push ecx */
	{ DWORD v_ = 0xb63u; m->esp -= 4; M32(m->esp) = v_; }	/* 487337: push 0xb63 */
	m->esp -= 4; M32(m->esp) = 0x48733eu; native_call(m, m->edi);	/* 48733c: call edi */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 48733e: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487342: push edx */
	{ DWORD v_ = 0xb64u; m->esp -= 4; M32(m->esp) = v_; }	/* 487343: push 0xb64 */
	m->esp -= 4; M32(m->esp) = 0x48734au; native_call(m, m->edi);	/* 487348: call edi */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 48734a: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x487351u; native_call(m, m->esi);	/* 48734f: call esi */
	goto L_48735a;	/* 487351: jmp 0x48735a */
L_487353:
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 487353: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x48735au; native_call(m, m->edi);	/* 487358: call edi */
L_48735a:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0x8u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48735a: cmp dword ptr [ebp + 8], 1 */
	if (!m->zf) goto L_487370;	/* 48735e: jne 0x487370 */
	{ DWORD v_ = 0x1b02u; m->esp -= 4; M32(m->esp) = v_; }	/* 487360: push 0x1b02 */
	{ DWORD v_ = 0x408u; m->esp -= 4; M32(m->esp) = v_; }	/* 487365: push 0x408 */
	m->esp -= 4; M32(m->esp) = 0x487370u; native_call(m, M32(0x4a91c4u));	/* 48736a: call dword ptr [0x4a91c4] */
L_487370:
	m->esi = M32((DWORD)(0x4a91fcu));	/* 487370: mov esi, dword ptr [0x4a91fc] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 487376: push 0x1701 */
	m->esp -= 4; M32(m->esp) = 0x48737du; native_call(m, m->esi);	/* 48737b: call esi */
	m->edi = M32((DWORD)(0x4a926cu));	/* 48737d: mov edi, dword ptr [0x4a926c] */
	m->eax = (DWORD)(m->esp + 0x168u);	/* 487383: lea eax, [esp + 0x168] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48738a: push eax */
	m->esp -= 4; M32(m->esp) = 0x48738du; native_call(m, m->edi);	/* 48738b: call edi */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 48738d: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x487394u; native_call(m, m->esi);	/* 487392: call esi */
	m->ecx = (DWORD)(m->esp + 0x128u);	/* 487394: lea ecx, [esp + 0x128] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48739b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48739eu; native_call(m, m->edi);	/* 48739c: call edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 48739e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48739f: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4873a0: pop ebx */
	m->esp = m->ebp;	/* 4873a1: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4873a3: pop ebp */
	m->esp += 4 + 8; return;	/* 4873a4: ret 8 */
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
