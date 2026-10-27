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

static void lift_442e10(X86 *m);
static void lift_4038e0(X86 *m);

/* arena_4038e0 (0x4038e0), lifted by tools/lift.py */
static void lift_4038e0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4038e0: sub esp, 0x18 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4038e3: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4038e8: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4038ee: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4038ef: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4038f0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4038f1: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4038f2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4038f3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4038f9u; native_call(m, 0x4033e0u);	/* 4038f4: call 0x4033e0 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 4038f9: push 0x3e99999a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4038fe: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403900: push 0 */
	m->edi = m->eax;	/* 403902: mov edi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403904: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 403906: push 0x9da480 */
	M32((DWORD)(m->esp + 0x2cu)) = m->edi;	/* 40390b: mov dword ptr [esp + 0x2c], edi */
	m->esp -= 4; M32(m->esp) = 0x403914u; native_call(m, 0x41f0e0u);	/* 40390f: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403914: push 1 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403916: push 0x1e0 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 40391b: push 0x280 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403920: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403922: push 0 */
	m->esp -= 4; M32(m->esp) = 0x403929u; native_call(m, 0x427970u);	/* 403924: call 0x427970 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 403929: push 0x3f333333 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40392e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403930: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403932: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 403934: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x40393eu; native_call(m, 0x41f0e0u);	/* 403939: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40393e: add esp, 0x44 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403941: push 1 */
	{ DWORD v_ = 0x1b8u; m->esp -= 4; M32(m->esp) = v_; }	/* 403943: push 0x1b8 */
	{ DWORD v_ = 0x1f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 403948: push 0x1f4 */
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 40394d: push 0x28 */
	{ DWORD v_ = 0x8cu; m->esp -= 4; M32(m->esp) = v_; }	/* 40394f: push 0x8c */
	m->esp -= 4; M32(m->esp) = 0x403959u; native_call(m, 0x427970u);	/* 403954: call 0x427970 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403959: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40395e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403963: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403968: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 40396a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x403974u; native_call(m, 0x41f0e0u);	/* 40396f: call 0x41f0e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403974: push 0 */
	{ DWORD v_ = 0x1b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 403976: push 0x1b4 */
	{ DWORD v_ = 0x1f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40397b: push 0x1f0 */
	{ DWORD v_ = 0x2cu; m->esp -= 4; M32(m->esp) = v_; }	/* 403980: push 0x2c */
	{ DWORD v_ = 0x90u; m->esp -= 4; M32(m->esp) = v_; }	/* 403982: push 0x90 */
	m->esp -= 4; M32(m->esp) = 0x40398cu; native_call(m, 0x427970u);	/* 403987: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 40398c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403991: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403996: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 40399b: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 40399d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4039a7u; native_call(m, 0x41f0e0u);	/* 4039a2: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4039a7: add esp, 0x50 */
	{ DWORD v_ = 0x75d924u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039aa: push 0x75d924 */
	{ DWORD v_ = 0x32u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039af: push 0x32 */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039b1: push 0xc8 */
	m->esp -= 4; M32(m->esp) = 0x4039bbu; native_call(m, 0x402620u);	/* 4039b6: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039bb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039c0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039c5: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039ca: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039cc: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4039d6u; native_call(m, 0x41f0e0u);	/* 4039d1: call 0x41f0e0 */
	{ DWORD v_ = 0x75d9a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039d6: push 0x75d9a4 */
	{ DWORD v_ = 0x32u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039db: push 0x32 */
	{ DWORD v_ = 0x168u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039dd: push 0x168 */
	m->esp -= 4; M32(m->esp) = 0x4039e7u; native_call(m, 0x402620u);	/* 4039e2: call 0x402620 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4039e7: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039ec: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039f1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039f6: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4039f8: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x403a02u; native_call(m, 0x41f0e0u);	/* 4039fd: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403a02: add esp, 0x40 */
	{ DWORD v_ = 0x4bu; m->esp -= 4; M32(m->esp) = v_; }	/* 403a05: push 0x4b */
	{ DWORD v_ = 0x1eau; m->esp -= 4; M32(m->esp) = v_; }	/* 403a07: push 0x1ea */
	{ DWORD v_ = 0x4bu; m->esp -= 4; M32(m->esp) = v_; }	/* 403a0c: push 0x4b */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 403a0e: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x403a18u; native_call(m, 0x427a40u);	/* 403a13: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403a18: add esp, 0x10 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 403a1b: xor ebp, ebp */
	m->esi = 0x57u;	/* 403a1d: mov esi, 0x57 */
L_403a22:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x67ef00u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403a22: cmp ebp, dword ptr [0x67ef00] */
	if (m->sf == m->of) goto L_403c2b;	/* 403a28: jge 0x403c2b */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403a2e: cmp edi, ebp */
	if (!m->zf) goto L_403a69;	/* 403a30: jne 0x403a69 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403a32: push 0x3ecccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403a37: push 0x3f4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403a3c: push 0x3e4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403a41: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 403a46: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x403a50u; native_call(m, 0x41f0e0u);	/* 403a4b: call 0x41f0e0 */
	m->edx = (DWORD)(m->esi + 0x14u);	/* 403a50: lea edx, [esi + 0x14] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403a53: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 403a55: push edx */
	{ DWORD v_ = 0x1a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 403a56: push 0x1a4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403a5b: push esi */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 403a5c: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x403a66u; native_call(m, 0x427970u);	/* 403a61: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403a66: add esp, 0x28 */
L_403a69:
	m->eax = M32((DWORD)(0x4d7350u));	/* 403a69: mov eax, dword ptr [0x4d7350] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 403a6e: add eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0x16u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403a70: cmp eax, 0x16 */
	if (m->sf != m->of) goto L_403a7e;	/* 403a73: jl 0x403a7e */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403a75: cmp eax, 0x18 */
	if (m->zf || m->sf != m->of) goto L_403c1b;	/* 403a78: jle 0x403c1b */
L_403a7e:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403a7e: xor ecx, ecx */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 403a80: lea edx, [esp + 0x14] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 403a84: mov dword ptr [esp + 0x14], ecx */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 403a88: push 0xa */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 403a8a: mov dword ptr [esp + 0x1c], ecx */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 403a8e: inc eax */
	M32((DWORD)(m->esp + 0x20u)) = m->ecx;	/* 403a8f: mov dword ptr [esp + 0x20], ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 403a93: push edx */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 403a94: mov dword ptr [esp + 0x28], ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403a98: push eax */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 403a99: mov dword ptr [esp + 0x30], ecx */
	m->esp -= 4; M32(m->esp) = 0x403aa2u; native_call(m, 0x49fb53u);	/* 403a9d: call 0x49fb53 */
	m->eax = M32((DWORD)(0x4d7350u));	/* 403aa2: mov eax, dword ptr [0x4d7350] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403aa7: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 403aaa: add eax, ebp */
	m->ecx = M32((DWORD)(m->eax*8 + 0x4d7358u));	/* 403aac: mov ecx, dword ptr [eax*8 + 0x4d7358] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 403ab3: test ecx, ecx */
	if (m->zf) goto L_403b08;	/* 403ab5: je 0x403b08 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ab7: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403abc: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ac1: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ac3: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ac8: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x403ad2u; native_call(m, 0x41f0e0u);	/* 403acd: call 0x41f0e0 */
	m->ecx = (DWORD)(m->esi + 0x14u);	/* 403ad2: lea ecx, [esi + 0x14] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ad5: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403ad7: push ecx */
	{ DWORD v_ = 0x154u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ad8: push 0x154 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403add: push esi */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ade: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x403ae8u; native_call(m, 0x427970u);	/* 403ae3: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ae8: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403aed: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403aef: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403af4: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 403af9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x403b03u; native_call(m, 0x41f0e0u);	/* 403afe: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403b03: add esp, 0x3c */
	goto L_403b26;	/* 403b06: jmp 0x403b26 */
L_403b08:
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403b08: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b0d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b12: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b17: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b19: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x403b23u; native_call(m, 0x41f0e0u);	/* 403b1e: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403b23: add esp, 0x14 */
L_403b26:
	m->edi = (DWORD)(m->esp + 0x14u);	/* 403b26: lea edi, [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403b2a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 403b2d: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 403b2f: lea edx, [esp + 0x14] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 403b33: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 403b35: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 403b37: dec ecx */
	m->eax = 0xb4u;	/* 403b38: mov eax, 0xb4 */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 403b3d: shl ecx, 3 */
	m->ebx = (DWORD)(m->esi + 0x3u);	/* 403b40: lea ebx, [esi + 3] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 403b43: push edx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 403b44: sub eax, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 403b46: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403b47: push eax */
	m->esp -= 4; M32(m->esp) = 0x403b4du; native_call(m, 0x402620u);	/* 403b48: call 0x402620 */
	m->ecx = M32((DWORD)(0x4d7350u));	/* 403b4d: mov ecx, dword ptr [0x4d7350] */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 403b53: add ecx, ebp */
	{ DWORD a_ = m->ecx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 403b55: shl ecx, 5 */
	{ DWORD a_ = m->ecx, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 403b58: add ecx, 0x907b30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403b5e: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 403b5f: push ebx */
	{ DWORD v_ = 0xbeu; m->esp -= 4; M32(m->esp) = v_; }	/* 403b60: push 0xbe */
	m->esp -= 4; M32(m->esp) = 0x403b6au; native_call(m, 0x402620u);	/* 403b65: call 0x402620 */
	m->edx = M32((DWORD)(0x4d7350u));	/* 403b6a: mov edx, dword ptr [0x4d7350] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403b70: add esp, 0x18 */
	{ DWORD a_ = m->edx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 403b73: add edx, ebp */
	m->eax = M32((DWORD)(m->edx*8 + 0x4d7358u));	/* 403b75: mov eax, dword ptr [edx*8 + 0x4d7358] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 403b7c: test eax, eax */
	if (m->zf) goto L_403bd1;	/* 403b7e: je 0x403bd1 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b80: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b85: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b8a: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b8c: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b91: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x403b9bu; native_call(m, 0x41f0e0u);	/* 403b96: call 0x41f0e0 */
	m->eax = (DWORD)(m->esi + 0x14u);	/* 403b9b: lea eax, [esi + 0x14] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403b9e: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403ba0: push eax */
	{ DWORD v_ = 0x1a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ba1: push 0x1a4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403ba6: push esi */
	{ DWORD v_ = 0x168u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ba7: push 0x168 */
	m->esp -= 4; M32(m->esp) = 0x403bb1u; native_call(m, 0x427970u);	/* 403bac: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403bb1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403bb6: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403bb8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403bbd: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 403bc2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x403bccu; native_call(m, 0x41f0e0u);	/* 403bc7: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403bcc: add esp, 0x3c */
	goto L_403bef;	/* 403bcf: jmp 0x403bef */
L_403bd1:
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403bd1: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403bd6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403bdb: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403be0: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 403be2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x403becu; native_call(m, 0x41f0e0u);	/* 403be7: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403bec: add esp, 0x14 */
L_403bef:
	m->ecx = M32((DWORD)(0x4d7350u));	/* 403bef: mov ecx, dword ptr [0x4d7350] */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 403bf5: add ecx, ebp */
	m->eax = M32((DWORD)(m->ecx*8 + 0x4d735cu));	/* 403bf7: mov eax, dword ptr [ecx*8 + 0x4d735c] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 403bfe: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx*4 + 0x4db8d8u);	/* 403c01: lea eax, [edx*4 + 0x4db8d8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403c08: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 403c09: push ebx */
	{ DWORD v_ = 0x17cu; m->esp -= 4; M32(m->esp) = v_; }	/* 403c0a: push 0x17c */
	m->esp -= 4; M32(m->esp) = 0x403c14u; native_call(m, 0x402620u);	/* 403c0f: call 0x402620 */
	m->edi = M32((DWORD)(m->esp + 0x1cu));	/* 403c14: mov edi, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403c18: add esp, 0xc */
L_403c1b:
	{ DWORD a_ = m->esi, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 403c1b: add esi, 0x18 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 403c1e: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0x147u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403c1f: cmp esi, 0x147 */
	if (m->sf != m->of) goto L_403a22;	/* 403c25: jl 0x403a22 */
L_403c2b:
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403c2b: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403c30: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403c35: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403c3a: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 403c3c: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x403c46u; native_call(m, 0x41f0e0u);	/* 403c41: call 0x41f0e0 */
	{ DWORD v_ = 0x14fu; m->esp -= 4; M32(m->esp) = v_; }	/* 403c46: push 0x14f */
	{ DWORD v_ = 0x1eau; m->esp -= 4; M32(m->esp) = v_; }	/* 403c4b: push 0x1ea */
	{ DWORD v_ = 0x14fu; m->esp -= 4; M32(m->esp) = v_; }	/* 403c50: push 0x14f */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 403c55: push 0x96 */
	m->esp -= 4; M32(m->esp) = 0x403c5fu; native_call(m, 0x427a40u);	/* 403c5a: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403c5f: add esp, 0x24 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403c62: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x403c6du; native_call(m, M32(0x4a9224u));	/* 403c67: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 403c6d: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 403c72: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403c74: and ecx, 0x800001ff */
	if (!m->sf) goto L_403c84;	/* 403c7a: jns 0x403c84 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 403c7c: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403c7d: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 403c83: inc ecx */
L_403c84:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 403c84: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 403c85: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403c8b: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 403c8c: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 403c8e: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 403c94: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 403c97: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x403ca0u; native_call(m, 0x4566c0u);	/* 403c9b: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ca0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ca5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403caa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403caf: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x403cbau; native_call(m, M32(0x4a9228u));	/* 403cb4: call dword ptr [0x4a9228] */
	{ DWORD a_ = m->edi, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403cba: cmp edi, 0x14 */
	if (!m->zf) goto L_403d09;	/* 403cbd: jne 0x403d09 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403cbf: push 1 */
	{ DWORD v_ = 0xcau; m->esp -= 4; M32(m->esp) = v_; }	/* 403cc1: push 0xca */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403cc6: push 0x1e0 */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ccb: push 0x96 */
	{ DWORD v_ = 0x1c2u; m->esp -= 4; M32(m->esp) = v_; }	/* 403cd0: push 0x1c2 */
	m->esp -= 4; M32(m->esp) = 0x403cdau; native_call(m, 0x4286b0u);	/* 403cd5: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403cda: add esp, 0x14 */
L_403cdd:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403cdd: push 0 */
L_403cdf:
	{ DWORD v_ = 0x110u; m->esp -= 4; M32(m->esp) = v_; }	/* 403cdf: push 0x110 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ce4: push 0x1e0 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 403ce9: push 0xdc */
	{ DWORD v_ = 0x1c2u; m->esp -= 4; M32(m->esp) = v_; }	/* 403cee: push 0x1c2 */
	m->esp -= 4; M32(m->esp) = 0x403cf8u; native_call(m, 0x4287a0u);	/* 403cf3: call 0x4287a0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403cf8: add esp, 0x14 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 403cfb: xor ebx, ebx */
	m->esi = 0xaau;	/* 403cfd: mov esi, 0xaa */
	m->ebp = 0x75db24u;	/* 403d02: mov ebp, 0x75db24 */
	goto L_403d34;	/* 403d07: jmp 0x403d34 */
L_403d09:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d09: push 0 */
	{ DWORD v_ = 0xcau; m->esp -= 4; M32(m->esp) = v_; }	/* 403d0b: push 0xca */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d10: push 0x1e0 */
	{ DWORD v_ = 0x96u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d15: push 0x96 */
	{ DWORD v_ = 0x1c2u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d1a: push 0x1c2 */
	m->esp -= 4; M32(m->esp) = 0x403d24u; native_call(m, 0x4286b0u);	/* 403d1f: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403d24: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0x15u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403d27: cmp edi, 0x15 */
	if (!m->zf) goto L_403cdd;	/* 403d2a: jne 0x403cdd */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d2c: push 1 */
	goto L_403cdf;	/* 403d2e: jmp 0x403cdf */
L_403d30:
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 403d30: mov edi, dword ptr [esp + 0x10] */
L_403d34:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d34: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x403d3fu; native_call(m, M32(0x4a9224u));	/* 403d39: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 403d3f: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 403d44: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403d46: and ecx, 0x800001ff */
	if (!m->sf) goto L_403d56;	/* 403d4c: jns 0x403d56 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 403d4e: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403d4f: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 403d55: inc ecx */
L_403d56:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 403d56: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 403d57: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403d5d: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 403d5e: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 403d60: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 403d66: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 403d69: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x403d72u; native_call(m, 0x4566c0u);	/* 403d6d: call 0x4566c0 */
	m->eax = (DWORD)(m->ebx + 0x16u);	/* 403d72: lea eax, [ebx + 0x16] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403d75: cmp edi, eax */
	if (!m->zf) goto L_403da9;	/* 403d77: jne 0x403da9 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d79: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d7e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d83: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d88: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x403d93u; native_call(m, M32(0x4a9228u));	/* 403d8d: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d93: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d98: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403d9d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403da2: push 0x3f800000 */
	goto L_403dd7;	/* 403da7: jmp 0x403dd7 */
L_403da9:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403da9: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403dae: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403db3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403db8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x403dc3u; native_call(m, M32(0x4a9228u));	/* 403dbd: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403dc3: push 0x3f800000 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 403dc8: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 403dcd: push 0x3f333333 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 403dd2: push 0x3e99999a */
L_403dd7:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 403dd7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x403de1u; native_call(m, 0x41f0e0u);	/* 403ddc: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403de1: add esp, 0x14 */
	m->edi = (DWORD)(m->esi + 0x8cu);	/* 403de4: lea edi, [esi + 0x8c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403dea: push 1 */
	{ DWORD v_ = 0x17eu; m->esp -= 4; M32(m->esp) = v_; }	/* 403dec: push 0x17e */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 403df1: push edi */
	{ DWORD v_ = 0x15eu; m->esp -= 4; M32(m->esp) = v_; }	/* 403df2: push 0x15e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403df7: push esi */
	m->esp -= 4; M32(m->esp) = 0x403dfdu; native_call(m, 0x4282f0u);	/* 403df8: call 0x4282f0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 403dfd: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 403dfe: push edi */
	{ DWORD v_ = 0x166u; m->esp -= 4; M32(m->esp) = v_; }	/* 403dff: push 0x166 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403e04: push esi */
	m->esp -= 4; M32(m->esp) = 0x403e0au; native_call(m, 0x4029d0u);	/* 403e05: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403e0a: add esp, 0x24 */
	{ DWORD a_ = m->ebp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 403e0d: add ebp, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 403e13: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 403e14: add esi, 0xa0 */
	{ DWORD a_ = m->ebp, b_ = 0x75dc24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403e1a: cmp ebp, 0x75dc24 */
	if (m->sf != m->of) goto L_403d30;	/* 403e20: jl 0x403d30 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 403e26: xor ebx, ebx */
	m->esi = 0xaau;	/* 403e28: mov esi, 0xaa */
	m->ebp = 0x75da24u;	/* 403e2d: mov ebp, 0x75da24 */
L_403e32:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403e32: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x403e3du; native_call(m, M32(0x4a9224u));	/* 403e37: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 403e3d: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 403e42: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403e44: and ecx, 0x800001ff */
	if (!m->sf) goto L_403e54;	/* 403e4a: jns 0x403e54 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 403e4c: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 403e4d: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 403e53: inc ecx */
L_403e54:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 403e54: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 403e55: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403e5b: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 403e5c: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 403e5e: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 403e64: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 403e67: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x403e70u; native_call(m, 0x4566c0u);	/* 403e6b: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 403e70: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebx + 0x18u);	/* 403e74: lea eax, [ebx + 0x18] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403e77: cmp ecx, eax */
	if (!m->zf) goto L_403eab;	/* 403e79: jne 0x403eab */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403e7b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403e80: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403e85: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403e8a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x403e95u; native_call(m, M32(0x4a9228u));	/* 403e8f: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403e95: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403e9a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403e9f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ea4: push 0x3f800000 */
	goto L_403ed9;	/* 403ea9: jmp 0x403ed9 */
L_403eab:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 403eab: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403eb0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403eb5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403eba: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x403ec5u; native_call(m, M32(0x4a9228u));	/* 403ebf: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ec5: push 0x3f800000 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 403eca: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ecf: push 0x3f333333 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 403ed4: push 0x3e99999a */
L_403ed9:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ed9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x403ee3u; native_call(m, 0x41f0e0u);	/* 403ede: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403ee3: add esp, 0x14 */
	m->edi = (DWORD)(m->esi + 0x8cu);	/* 403ee6: lea edi, [esi + 0x8c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 403eec: push 1 */
	{ DWORD v_ = 0x1a6u; m->esp -= 4; M32(m->esp) = v_; }	/* 403eee: push 0x1a6 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 403ef3: push edi */
	{ DWORD v_ = 0x186u; m->esp -= 4; M32(m->esp) = v_; }	/* 403ef4: push 0x186 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403ef9: push esi */
	m->esp -= 4; M32(m->esp) = 0x403effu; native_call(m, 0x4282f0u);	/* 403efa: call 0x4282f0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 403eff: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 403f00: push edi */
	{ DWORD v_ = 0x18eu; m->esp -= 4; M32(m->esp) = v_; }	/* 403f01: push 0x18e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403f06: push esi */
	m->esp -= 4; M32(m->esp) = 0x403f0cu; native_call(m, 0x4029d0u);	/* 403f07: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403f0c: add esp, 0x24 */
	{ DWORD a_ = m->ebp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 403f0f: add ebp, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 403f15: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 403f16: add esi, 0xa0 */
	{ DWORD a_ = m->ebp, b_ = 0x75db24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 403f1c: cmp ebp, 0x75db24 */
	if (m->sf != m->of) goto L_403e32;	/* 403f22: jl 0x403e32 */
	m->edi = M32(m->esp); m->esp += 4;	/* 403f28: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 403f29: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 403f2a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 403f2b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 403f2c: add esp, 0x18 */
	m->esp += 4 + 0; return;	/* 403f2f: ret  */
}

/* mainmenu_442e10 (0x442e10), lifted by tools/lift.py */
static void lift_442e10(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e10: push ecx */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 442e11: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 442e16: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e1c: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 442e1d: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442e1e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e1f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x442e25u; native_call(m, 0x440b70u);	/* 442e20: call 0x440b70 */
	m->esi = m->eax;	/* 442e25: mov esi, eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 442e27: push 2 */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 442e29: mov dword ptr [esp + 0x14], esi */
	m->esp -= 4; M32(m->esp) = 0x442e32u; native_call(m, 0x41ef90u);	/* 442e2d: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442e32: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x442e3bu; native_call(m, M32(0x4a9218u));	/* 442e35: call dword ptr [0x4a9218] */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 442e3b: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442e41: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442e46: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442e4b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442e50: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x442e57u; native_call(m, m->ebx);	/* 442e55: call ebx */
	m->edx = M32((DWORD)(0x4deb50u));	/* 442e57: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9dd914u));	/* 442e5d: mov eax, dword ptr [0x9dd914] */
	m->ecx = M32((DWORD)(0x9dd910u));	/* 442e62: mov ecx, dword ptr [0x9dd910] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e68: push edx */
	m->edx = M32((DWORD)(0x9dd90cu));	/* 442e69: mov edx, dword ptr [0x9dd90c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442e6f: push eax */
	m->eax = M32((DWORD)(0x9dd908u));	/* 442e70: mov eax, dword ptr [0x9dd908] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e75: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e76: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442e77: push eax */
	m->esp -= 4; M32(m->esp) = 0x442e7du; native_call(m, 0x427a90u);	/* 442e78: call 0x427a90 */
	m->ecx = M32((DWORD)(0x9eeaa4u));	/* 442e7d: mov ecx, dword ptr [0x9eeaa4] */
	m->edx = M32((DWORD)(0x9eeaa0u));	/* 442e83: mov edx, dword ptr [0x9eeaa0] */
	m->eax = M32((DWORD)(0x9eea9cu));	/* 442e89: mov eax, dword ptr [0x9eea9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e8e: push ecx */
	m->ecx = M32((DWORD)(0x9eea98u));	/* 442e8f: mov ecx, dword ptr [0x9eea98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e95: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442e96: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442e97: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 442e98: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x442ea2u; native_call(m, 0x41f0e0u);	/* 442e9d: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dd90cu));	/* 442ea2: mov edx, dword ptr [0x9dd90c] */
	m->eax = M32((DWORD)(0x9dd908u));	/* 442ea8: mov eax, dword ptr [0x9dd908] */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 442ead: add edx, 0x10 */
	{ DWORD v_ = 0x74e8a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 442eb0: push 0x74e8a4 */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442eb5: add eax, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442eb8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442eb9: push eax */
	m->esp -= 4; M32(m->esp) = 0x442ebfu; native_call(m, 0x4028b0u);	/* 442eba: call 0x4028b0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ebf: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ec4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ec9: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ece: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ed0: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x442edau; native_call(m, 0x41f0e0u);	/* 442ed5: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd90cu));	/* 442eda: mov eax, dword ptr [0x9dd90c] */
	m->edx = M32((DWORD)(0x9dd910u));	/* 442edf: mov edx, dword ptr [0x9dd910] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442ee5: add esp, 0x48 */
	{ DWORD a_ = m->edx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 442ee8: add edx, -0x40 */
	m->ecx = (DWORD)(m->eax + 0xf5u);	/* 442eeb: lea ecx, [eax + 0xf5] */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442ef1: add eax, 0x28 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442ef4: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442ef6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442ef7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442ef8: push eax */
	m->eax = M32((DWORD)(0x9dd908u));	/* 442ef9: mov eax, dword ptr [0x9dd908] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442efe: add eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442f01: push eax */
	m->esp -= 4; M32(m->esp) = 0x442f07u; native_call(m, 0x427970u);	/* 442f02: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442f07: add esp, 0x14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 442f0a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x442f15u; native_call(m, M32(0x4a9224u));	/* 442f0f: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 442f15: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 442f1a: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 442f1c: and ecx, 0x800001ff */
	if (!m->sf) goto L_442f2c;	/* 442f22: jns 0x442f2c */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 442f24: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 442f25: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 442f2b: inc ecx */
L_442f2c:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 442f2c: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 442f2d: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442f33: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442f34: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 442f36: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 442f3c: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 442f3f: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x442f48u; native_call(m, 0x4566c0u);	/* 442f43: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442f48: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442f4d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442f52: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442f57: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x442f5eu; native_call(m, m->ebx);	/* 442f5c: call ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 442f5e: test esi, esi */
	if (!m->zf) goto L_443224;	/* 442f60: jne 0x443224 */
	m->eax = M32((DWORD)(0x9dd90cu));	/* 442f66: mov eax, dword ptr [0x9dd90c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 442f6b: push 1 */
	m->ecx = (DWORD)(m->eax + 0x88u);	/* 442f6d: lea ecx, [eax + 0x88] */
	{ DWORD a_ = m->eax, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442f73: add eax, 0x48 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442f76: push ecx */
	m->ecx = M32((DWORD)(0x9dd910u));	/* 442f77: mov ecx, dword ptr [0x9dd910] */
	m->edx = (DWORD)(m->ecx + 0xffffffeeu);	/* 442f7d: lea edx, [ecx - 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 442f80: add ecx, -0x32 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442f83: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442f84: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442f85: push ecx */
	m->esp -= 4; M32(m->esp) = 0x442f8bu; native_call(m, 0x4286b0u);	/* 442f86: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442f8b: add esp, 0x14 */
L_442f8e:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442f8e: push 0 */
L_442f90:
	m->eax = M32((DWORD)(0x9dd90cu));	/* 442f90: mov eax, dword ptr [0x9dd90c] */
	m->ecx = (DWORD)(m->eax + 0xecu);	/* 442f95: lea ecx, [eax + 0xec] */
	{ DWORD a_ = m->eax, b_ = 0xacu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442f9b: add eax, 0xac */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442fa0: push ecx */
	m->ecx = M32((DWORD)(0x9dd910u));	/* 442fa1: mov ecx, dword ptr [0x9dd910] */
	m->edx = (DWORD)(m->ecx + 0xffffffeeu);	/* 442fa7: lea edx, [ecx - 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 442faa: add ecx, -0x32 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442fad: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442fae: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442faf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x442fb5u; native_call(m, 0x4287a0u);	/* 442fb0: call 0x4287a0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 442fb5: add esp, 0x14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 442fb8: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x442fc3u; native_call(m, M32(0x4a922cu));	/* 442fbd: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442fc3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442fc8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 442fcd: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442fd2: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 442fd4: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x442fdeu; native_call(m, 0x41f0e0u);	/* 442fd9: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd90cu));	/* 442fde: mov eax, dword ptr [0x9dd90c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 442fe3: push 0 */
	m->ecx = (DWORD)(m->eax + 0x10eu);	/* 442fe5: lea ecx, [eax + 0x10e] */
	{ DWORD a_ = m->eax, b_ = 0xfeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 442feb: add eax, 0xfe */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442ff0: push ecx */
	m->ecx = M32((DWORD)(0x9dd908u));	/* 442ff1: mov ecx, dword ptr [0x9dd908] */
	m->edx = (DWORD)(m->ecx + 0x20u);	/* 442ff7: lea edx, [ecx + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 442ffa: add ecx, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 442ffd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 442ffe: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 442fff: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443005u; native_call(m, 0x427970u);	/* 443000: call 0x427970 */
	m->eax = M32((DWORD)(0x4b2a7cu));	/* 443005: mov eax, dword ptr [0x4b2a7c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44300a: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44300d: test eax, eax */
	if (m->zf) goto L_443053;	/* 44300f: je 0x443053 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 443011: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 443016: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 443018: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44301a: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44301f: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x443029u; native_call(m, 0x41f0e0u);	/* 443024: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd90cu));	/* 443029: mov eax, dword ptr [0x9dd90c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44302e: push 1 */
	m->ecx = (DWORD)(m->eax + 0x10bu);	/* 443030: lea ecx, [eax + 0x10b] */
	{ DWORD a_ = m->eax, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 443036: add eax, 0x100 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44303b: push ecx */
	m->ecx = M32((DWORD)(0x9dd908u));	/* 44303c: mov ecx, dword ptr [0x9dd908] */
	m->edx = (DWORD)(m->ecx + 0x1du);	/* 443042: lea edx, [ecx + 0x1d] */
	{ DWORD a_ = m->ecx, b_ = 0x12u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 443045: add ecx, 0x12 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443048: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443049: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44304a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443050u; native_call(m, 0x427970u);	/* 44304b: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443050: add esp, 0x28 */
L_443053:
	m->eax = M32((DWORD)(0x9eeaa4u));	/* 443053: mov eax, dword ptr [0x9eeaa4] */
	m->ecx = M32((DWORD)(0x9eeaa0u));	/* 443058: mov ecx, dword ptr [0x9eeaa0] */
	m->edx = M32((DWORD)(0x9eea9cu));	/* 44305e: mov edx, dword ptr [0x9eea9c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443064: push eax */
	m->eax = M32((DWORD)(0x9eea98u));	/* 443065: mov eax, dword ptr [0x9eea98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44306a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44306b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44306c: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44306d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x443077u; native_call(m, 0x41f0e0u);	/* 443072: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd90cu));	/* 443077: mov ecx, dword ptr [0x9dd90c] */
	m->edx = M32((DWORD)(0x9dd908u));	/* 44307d: mov edx, dword ptr [0x9dd908] */
	{ DWORD a_ = m->ecx, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 443083: add ecx, 0x100 */
	{ DWORD v_ = 0x74e924u; m->esp -= 4; M32(m->esp) = v_; }	/* 443089: push 0x74e924 */
	{ DWORD a_ = m->edx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44308e: add edx, 0x28 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443091: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443092: push edx */
	m->esp -= 4; M32(m->esp) = 0x443098u; native_call(m, 0x4028b0u);	/* 443093: call 0x4028b0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 443098: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44309d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430a2: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430a7: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430a9: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4430b3u; native_call(m, 0x41f0e0u);	/* 4430ae: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd90cu));	/* 4430b3: mov eax, dword ptr [0x9dd90c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430b8: push 0 */
	m->ecx = (DWORD)(m->eax + 0x12cu);	/* 4430ba: lea ecx, [eax + 0x12c] */
	{ DWORD a_ = m->eax, b_ = 0x11cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4430c0: add eax, 0x11c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4430c5: push ecx */
	m->ecx = M32((DWORD)(0x9dd908u));	/* 4430c6: mov ecx, dword ptr [0x9dd908] */
	m->edx = (DWORD)(m->ecx + 0x20u);	/* 4430cc: lea edx, [ecx + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4430cf: add ecx, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4430d2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4430d3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4430d4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4430dau; native_call(m, 0x427970u);	/* 4430d5: call 0x427970 */
	m->eax = M32((DWORD)(0x9eeac0u));	/* 4430da: mov eax, dword ptr [0x9eeac0] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4430df: add esp, 0x48 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4430e2: test eax, eax */
	if (m->zf) goto L_443128;	/* 4430e4: je 0x443128 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430e6: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430eb: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430ed: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430ef: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4430f4: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4430feu; native_call(m, 0x41f0e0u);	/* 4430f9: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd90cu));	/* 4430fe: mov eax, dword ptr [0x9dd90c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443103: push 1 */
	m->ecx = (DWORD)(m->eax + 0x129u);	/* 443105: lea ecx, [eax + 0x129] */
	{ DWORD a_ = m->eax, b_ = 0x11eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44310b: add eax, 0x11e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443110: push ecx */
	m->ecx = M32((DWORD)(0x9dd908u));	/* 443111: mov ecx, dword ptr [0x9dd908] */
	m->edx = (DWORD)(m->ecx + 0x1du);	/* 443117: lea edx, [ecx + 0x1d] */
	{ DWORD a_ = m->ecx, b_ = 0x12u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44311a: add ecx, 0x12 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44311d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44311e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44311f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443125u; native_call(m, 0x427970u);	/* 443120: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443125: add esp, 0x28 */
L_443128:
	m->eax = M32((DWORD)(0x9eeaa4u));	/* 443128: mov eax, dword ptr [0x9eeaa4] */
	m->ecx = M32((DWORD)(0x9eeaa0u));	/* 44312d: mov ecx, dword ptr [0x9eeaa0] */
	m->edx = M32((DWORD)(0x9eea9cu));	/* 443133: mov edx, dword ptr [0x9eea9c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 443139: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44313a: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44313b: push eax */
	m->eax = M32((DWORD)(0x9eea98u));	/* 44313c: mov eax, dword ptr [0x9eea98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443141: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443142: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443143: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 443144: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44314eu; native_call(m, 0x41f0e0u);	/* 443149: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd90cu));	/* 44314e: mov ecx, dword ptr [0x9dd90c] */
	m->edx = M32((DWORD)(0x9dd908u));	/* 443154: mov edx, dword ptr [0x9dd908] */
	{ DWORD a_ = m->ecx, b_ = 0x11cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44315a: add ecx, 0x11c */
	{ DWORD v_ = 0x74e9a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443160: push 0x74e9a4 */
	{ DWORD a_ = m->edx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 443165: add edx, 0x28 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443168: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443169: push edx */
	m->esp -= 4; M32(m->esp) = 0x44316fu; native_call(m, 0x4028b0u);	/* 44316a: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44316f: add esp, 0x20 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 443172: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 443174: xor esi, esi */
	m->edi = 0x74ea24u;	/* 443176: mov edi, 0x74ea24 */
L_44317b:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44317b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x443186u; native_call(m, M32(0x4a9224u));	/* 443180: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 443186: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44318b: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44318d: and ecx, 0x800001ff */
	if (!m->sf) goto L_44319d;	/* 443193: jns 0x44319d */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 443195: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443196: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44319c: inc ecx */
L_44319d:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44319d: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44319e: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4431a4: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4431a5: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4431a7: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4431ad: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4431b0: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4431b9u; native_call(m, 0x4566c0u);	/* 4431b4: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4431b9: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebp + 0x4u);	/* 4431bd: lea eax, [ebp + 4] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4431c0: cmp ecx, eax */
	if (!m->zf) goto L_44325b;	/* 4431c2: jne 0x44325b */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4431c8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4431cd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4431d2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4431d7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4431deu; native_call(m, m->ebx);	/* 4431dc: call ebx */
	m->ecx = M32((DWORD)(0x9dd914u));	/* 4431de: mov ecx, dword ptr [0x9dd914] */
	m->eax = M32((DWORD)(0x9dd908u));	/* 4431e4: mov eax, dword ptr [0x9dd908] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4431e9: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffc4u);	/* 4431eb: lea edx, [ecx - 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4431ee: add ecx, -0x5c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4431f1: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 4431f2: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4431f9: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 4431fa: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4431fe: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4431ff: push eax */
	m->esp -= 4; M32(m->esp) = 0x443205u; native_call(m, 0x4282f0u);	/* 443200: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9eeaa4u));	/* 443205: mov ecx, dword ptr [0x9eeaa4] */
	m->edx = M32((DWORD)(0x9eeaa0u));	/* 44320b: mov edx, dword ptr [0x9eeaa0] */
	m->eax = M32((DWORD)(0x9eea9cu));	/* 443211: mov eax, dword ptr [0x9eea9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443216: push ecx */
	m->ecx = M32((DWORD)(0x9eea98u));	/* 443217: mov ecx, dword ptr [0x9eea98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44321d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44321e: push eax */
	goto L_4432b2;	/* 44321f: jmp 0x4432b2 */
L_443224:
	m->eax = M32((DWORD)(0x9dd90cu));	/* 443224: mov eax, dword ptr [0x9dd90c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 443229: push 0 */
	m->ecx = (DWORD)(m->eax + 0x88u);	/* 44322b: lea ecx, [eax + 0x88] */
	{ DWORD a_ = m->eax, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 443231: add eax, 0x48 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443234: push ecx */
	m->ecx = M32((DWORD)(0x9dd910u));	/* 443235: mov ecx, dword ptr [0x9dd910] */
	m->edx = (DWORD)(m->ecx + 0xffffffeeu);	/* 44323b: lea edx, [ecx - 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44323e: add ecx, -0x32 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443241: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443242: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443243: push ecx */
	m->esp -= 4; M32(m->esp) = 0x443249u; native_call(m, 0x4286b0u);	/* 443244: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443249: add esp, 0x14 */
	{ DWORD a_ = m->esi, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44324c: cmp esi, 1 */
	if (!m->zf) goto L_442f8e;	/* 44324f: jne 0x442f8e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 443255: push esi */
	goto L_442f90;	/* 443256: jmp 0x442f90 */
L_44325b:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44325b: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 443260: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 443265: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44326a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x443271u; native_call(m, m->ebx);	/* 44326f: call ebx */
	m->ecx = M32((DWORD)(0x9dd914u));	/* 443271: mov ecx, dword ptr [0x9dd914] */
	m->eax = M32((DWORD)(0x9dd908u));	/* 443277: mov eax, dword ptr [0x9dd908] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44327c: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffc4u);	/* 44327e: lea edx, [ecx - 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 443281: add ecx, -0x5c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443284: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 443285: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44328c: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 44328d: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443291: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443292: push eax */
	m->esp -= 4; M32(m->esp) = 0x443298u; native_call(m, 0x4282f0u);	/* 443293: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dda7cu));	/* 443298: mov ecx, dword ptr [0x9dda7c] */
	m->edx = M32((DWORD)(0x9dda78u));	/* 44329e: mov edx, dword ptr [0x9dda78] */
	m->eax = M32((DWORD)(0x9dda74u));	/* 4432a4: mov eax, dword ptr [0x9dda74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4432a9: push ecx */
	m->ecx = M32((DWORD)(0x9dda70u));	/* 4432aa: mov ecx, dword ptr [0x9dda70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4432b0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4432b1: push eax */
L_4432b2:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4432b2: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4432b3: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4432bdu; native_call(m, 0x41f0e0u);	/* 4432b8: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd908u));	/* 4432bd: mov eax, dword ptr [0x9dd908] */
	m->ecx = M32((DWORD)(0x9dd914u));	/* 4432c2: mov ecx, dword ptr [0x9dd914] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4432c8: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffacu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4432cb: add ecx, -0x54 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 4432ce: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4432d5: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4432d6: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 4432d7: lea edx, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4432db: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4432dc: push edx */
	m->esp -= 4; M32(m->esp) = 0x4432e2u; native_call(m, 0x4029d0u);	/* 4432dd: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4432e2: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4432e5: add edi, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 4432eb: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4432ec: add esi, 0xa0 */
	{ DWORD a_ = m->edi, b_ = 0x74eb24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4432f2: cmp edi, 0x74eb24 */
	if (m->sf != m->of) goto L_44317b;	/* 4432f8: jl 0x44317b */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4432fe: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 443300: xor esi, esi */
	m->edi = 0x74eb24u;	/* 443302: mov edi, 0x74eb24 */
L_443307:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443307: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x443312u; native_call(m, M32(0x4a9224u));	/* 44330c: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 443312: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 443317: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443319: and ecx, 0x800001ff */
	if (!m->sf) goto L_443329;	/* 44331f: jns 0x443329 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 443321: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 443322: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 443328: inc ecx */
L_443329:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 443329: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44332a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443330: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 443331: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 443333: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 443339: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44333c: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x443345u; native_call(m, 0x4566c0u);	/* 443340: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 443345: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebp + 0x6u);	/* 443349: lea eax, [ebp + 6] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44334c: cmp ecx, eax */
	if (!m->zf) goto L_4433a9;	/* 44334e: jne 0x4433a9 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 443350: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 443355: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44335a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44335f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x443366u; native_call(m, m->ebx);	/* 443364: call ebx */
	m->ecx = M32((DWORD)(0x9dd914u));	/* 443366: mov ecx, dword ptr [0x9dd914] */
	m->eax = M32((DWORD)(0x9dd908u));	/* 44336c: mov eax, dword ptr [0x9dd908] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443371: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffecu);	/* 443373: lea edx, [ecx - 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 443376: add ecx, -0x34 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443379: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 44337a: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443381: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 443382: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443386: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 443387: push eax */
	m->esp -= 4; M32(m->esp) = 0x44338du; native_call(m, 0x4282f0u);	/* 443388: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9eeaa4u));	/* 44338d: mov ecx, dword ptr [0x9eeaa4] */
	m->edx = M32((DWORD)(0x9eeaa0u));	/* 443393: mov edx, dword ptr [0x9eeaa0] */
	m->eax = M32((DWORD)(0x9eea9cu));	/* 443399: mov eax, dword ptr [0x9eea9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44339e: push ecx */
	m->ecx = M32((DWORD)(0x9eea98u));	/* 44339f: mov ecx, dword ptr [0x9eea98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4433a5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4433a6: push eax */
	goto L_443400;	/* 4433a7: jmp 0x443400 */
L_4433a9:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4433a9: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4433ae: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4433b3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4433b8: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4433bfu; native_call(m, m->ebx);	/* 4433bd: call ebx */
	m->ecx = M32((DWORD)(0x9dd914u));	/* 4433bf: mov ecx, dword ptr [0x9dd914] */
	m->eax = M32((DWORD)(0x9dd908u));	/* 4433c5: mov eax, dword ptr [0x9dd908] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4433ca: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffecu);	/* 4433cc: lea edx, [ecx - 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4433cf: add ecx, -0x34 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4433d2: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 4433d3: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4433da: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 4433db: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4433df: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4433e0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4433e6u; native_call(m, 0x4282f0u);	/* 4433e1: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dda7cu));	/* 4433e6: mov ecx, dword ptr [0x9dda7c] */
	m->edx = M32((DWORD)(0x9dda78u));	/* 4433ec: mov edx, dword ptr [0x9dda78] */
	m->eax = M32((DWORD)(0x9dda74u));	/* 4433f2: mov eax, dword ptr [0x9dda74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4433f7: push ecx */
	m->ecx = M32((DWORD)(0x9dda70u));	/* 4433f8: mov ecx, dword ptr [0x9dda70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4433fe: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4433ff: push eax */
L_443400:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443400: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 443401: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44340bu; native_call(m, 0x41f0e0u);	/* 443406: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd908u));	/* 44340b: mov eax, dword ptr [0x9dd908] */
	m->ecx = M32((DWORD)(0x9dd914u));	/* 443410: mov ecx, dword ptr [0x9dd914] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443416: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 443419: add ecx, -0x2c */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 44341c: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 443423: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443424: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 443425: lea edx, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 443429: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44342a: push edx */
	m->esp -= 4; M32(m->esp) = 0x443430u; native_call(m, 0x4029d0u);	/* 44342b: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443430: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 443433: add edi, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 443439: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44343a: add esi, 0xa0 */
	{ DWORD a_ = m->edi, b_ = 0x74ec24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443440: cmp edi, 0x74ec24 */
	if (m->sf != m->of) goto L_443307;	/* 443446: jl 0x443307 */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 44344c: mov esi, dword ptr [esp + 0x10] */
	m->edi = M32(m->esp); m->esp += 4;	/* 443450: pop edi */
	{ DWORD a_ = m->esi, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443451: cmp esi, 7 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 443454: pop ebp */
	if (m->zf || m->sf != m->of) goto L_4434ac;	/* 443455: jle 0x4434ac */
	{ DWORD a_ = m->esi, b_ = 0x12u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 443457: cmp esi, 0x12 */
	if (m->sf == m->of) goto L_4434ac;	/* 44345a: jge 0x4434ac */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 44345c: push 0x3e99999a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 443461: push 0x3f800000 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 443466: push 0x3e99999a */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44346b: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 443470: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44347au; native_call(m, 0x41f0e0u);	/* 443475: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd90cu));	/* 44347a: mov ecx, dword ptr [0x9dd90c] */
	m->eax = (DWORD)(m->esi + m->esi*4 + 0x0u);	/* 443480: lea eax, [esi + esi*4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 443483: push 1 */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 443485: lea eax, [ecx + eax*4] */
	m->ecx = M32((DWORD)(0x9dd910u));	/* 443488: mov ecx, dword ptr [0x9dd910] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffb0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44348e: add ecx, -0x50 */
	m->edx = (DWORD)(m->eax + 0xffffff9du);	/* 443491: lea edx, [eax - 0x63] */
	{ DWORD a_ = m->eax, b_ = 0xffffff8bu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 443494: add eax, -0x75 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 443497: push edx */
	m->edx = M32((DWORD)(0x9dd908u));	/* 443498: mov edx, dword ptr [0x9dd908] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44349e: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44349f: add edx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4434a2: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4434a3: push edx */
	m->esp -= 4; M32(m->esp) = 0x4434a9u; native_call(m, 0x427970u);	/* 4434a4: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4434a9: add esp, 0x28 */
L_4434ac:
	m->esp -= 4; M32(m->esp) = 0x4434b1u; native_call(m, 0x442d10u);	/* 4434ac: call 0x442d10 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4434b1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4434b6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4434bb: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4434c0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4434c7u; native_call(m, m->ebx);	/* 4434c5: call ebx */
	m->eax = M32((DWORD)(0x9dd914u));	/* 4434c7: mov eax, dword ptr [0x9dd914] */
	m->ecx = M32((DWORD)(0x9dd910u));	/* 4434cc: mov ecx, dword ptr [0x9dd910] */
	m->edx = M32((DWORD)(0x9dd90cu));	/* 4434d2: mov edx, dword ptr [0x9dd90c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4434d8: push eax */
	m->eax = M32((DWORD)(0x9dd908u));	/* 4434d9: mov eax, dword ptr [0x9dd908] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4434de: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4434df: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4434e0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4434e6u; native_call(m, 0x428a00u);	/* 4434e1: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4434e6: add esp, 0x10 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4434e9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4434ea: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4434eb: pop ecx */
	m->esp += 4 + 0; return;	/* 4434ec: ret  */
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
