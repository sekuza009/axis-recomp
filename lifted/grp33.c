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

static void lift_48b710(X86 *m);

/* map_loadObjectInfoFrom (0x48b710), lifted by tools/lift.py */
static void lift_48b710(X86 *m)
{
	m->eax = 0x288cu;	/* 48b710: mov eax, 0x288c */
	m->esp -= 4; M32(m->esp) = 0x48b71au; native_call(m, 0x49fc20u);	/* 48b715: call 0x49fc20 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b71a: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48b71b: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b71c: push esi */
	m->esi = m->ecx;	/* 48b71d: mov esi, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48b71f: xor ebx, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b721: push edi */
	m->ecx = (DWORD)(m->esi + 0xe3c93cu);	/* 48b722: lea ecx, [esi + 0xe3c93c] */
	M32((DWORD)(m->esi + 0x131ae40u)) = m->ebx;	/* 48b728: mov dword ptr [esi + 0x131ae40], ebx */
	m->esp -= 4; M32(m->esp) = 0x48b733u; native_call(m, 0x467520u);	/* 48b72e: call 0x467520 */
	m->ecx = (DWORD)(m->esi + 0x13016d0u);	/* 48b733: lea ecx, [esi + 0x13016d0] */
	m->esp -= 4; M32(m->esp) = 0x48b73eu; native_call(m, 0x46b7f0u);	/* 48b739: call 0x46b7f0 */
	m->ecx = m->esi;	/* 48b73e: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48b745u; native_call(m, 0x490d10u);	/* 48b740: call 0x490d10 */
	m->eax = M32((DWORD)(m->esp + 0x28a4u));	/* 48b745: mov eax, dword ptr [esp + 0x28a4] */
	M32((DWORD)(m->esi + 0x13016ccu)) = m->ebx;	/* 48b74c: mov dword ptr [esi + 0x13016cc], ebx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b752: cmp eax, ebx */
	if (!m->zf) goto L_48b7f0;	/* 48b754: jne 0x48b7f0 */
	m->ebp = M32((DWORD)(m->esp + 0x28a0u));	/* 48b75a: mov ebp, dword ptr [esp + 0x28a0] */
	m->eax = (DWORD)(m->esp + 0x11cu);	/* 48b761: lea eax, [esp + 0x11c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b768: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48b769: push ebp */
	m->esp -= 4; M32(m->esp) = 0x48b76fu; native_call(m, 0x46cad0u);	/* 48b76a: call 0x46cad0 */
	m->ecx = (DWORD)(m->esp + 0x124u);	/* 48b76f: lea ecx, [esp + 0x124] */
	m->edx = (DWORD)(m->esi + 0x108u);	/* 48b776: lea edx, [esi + 0x108] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b77c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b77d: push edx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 48b77e: lea eax, [esp + 0x2c] */
	{ DWORD v_ = 0x4c7e90u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b782: push 0x4c7e90 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b787: push eax */
	m->esp -= 4; M32(m->esp) = 0x48b78du; native_call(m, 0x49e9ddu);	/* 48b788: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 48b78d: lea ecx, [esp + 0x34] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b791: push 0x4ad170 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b796: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b79cu; native_call(m, 0x49e9cau);	/* 48b797: call 0x49e9ca */
	m->edi = m->eax;	/* 48b79c: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b79e: add esp, 0x20 */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b7a1: cmp edi, ebx */
	if (m->zf) goto L_48b7f7;	/* 48b7a3: je 0x48b7f7 */
	{ DWORD v_ = 0x4c7e74u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7a5: push 0x4c7e74 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7aa: push ebx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7ab: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7ac: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b7b2u; native_call(m, 0x470fc0u);	/* 48b7ad: call 0x470fc0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7b2: push edi */
	m->ebx = (DWORD)(m->esi + 0x13016c8u);	/* 48b7b3: lea ebx, [esi + 0x13016c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7b9: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7bb: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7bd: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48b7c3u; native_call(m, 0x46cbe0u);	/* 48b7be: call 0x46cbe0 */
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 48b7c3: mov edx, dword ptr [ebx] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7c5: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7c6: push edx */
	m->eax = (DWORD)(m->esi + 0xf30dc8u);	/* 48b7c7: lea eax, [esi + 0xf30dc8] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7cd: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7cf: push eax */
	m->esp -= 4; M32(m->esp) = 0x48b7d5u; native_call(m, 0x46cbe0u);	/* 48b7d0: call 0x46cbe0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7d5: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b7dbu; native_call(m, 0x49e7e0u);	/* 48b7d6: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b7db: add esp, 0x34 */
	M32((DWORD)(m->ebx + 0x0u)) = 0x0u;	/* 48b7de: mov dword ptr [ebx], 0 */
	M32((DWORD)(m->esi + 0x13016ccu)) = 0x1u;	/* 48b7e4: mov dword ptr [esi + 0x13016cc], 1 */
	goto L_48b7f7;	/* 48b7ee: jmp 0x48b7f7 */
L_48b7f0:
	m->ebp = M32((DWORD)(m->esp + 0x28a0u));	/* 48b7f0: mov ebp, dword ptr [esp + 0x28a0] */
L_48b7f7:
	m->eax = (DWORD)(m->esi + 0x108u);	/* 48b7f7: lea eax, [esi + 0x108] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7fd: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b7fe: push eax */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 48b7ff: lea ecx, [esp + 0x24] */
	{ DWORD v_ = 0x4c77f0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b803: push 0x4c77f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b808: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b80eu; native_call(m, 0x49e9ddu);	/* 48b809: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 48b80e: lea edx, [esp + 0x2c] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b812: push 0x4ad170 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b817: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b81du; native_call(m, 0x49e9cau);	/* 48b818: call 0x49e9ca */
	m->ebx = m->eax;	/* 48b81d: mov ebx, eax */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b81f: add esp, 0x18 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b822: test ebx, ebx */
	if (!m->zf) goto L_48b83d;	/* 48b824: jne 0x48b83d */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 48b826: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b82a: push eax */
	{ DWORD v_ = 0x4c7e48u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b82b: push 0x4c7e48 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b830: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48b83au; native_call(m, 0x46c710u);	/* 48b835: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b83a: add esp, 0xc */
L_48b83d:
	{ DWORD v_ = 0x4c77b4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b83d: push 0x4c77b4 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b842: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b844: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b846: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b84cu; native_call(m, 0x470fc0u);	/* 48b847: call 0x470fc0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b84c: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b84d: push 1 */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 48b84f: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b853: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b855: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b85bu; native_call(m, 0x49e836u);	/* 48b856: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 48b85b: mov eax, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b85f: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = 0x1201u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b862: cmp eax, 0x1201 */
	if (m->zf) goto L_48b87c;	/* 48b867: je 0x48b87c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48b869: push ebp */
	{ DWORD v_ = 0x4c7768u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b86a: push 0x4c7768 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b86f: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48b879u; native_call(m, 0x46c710u);	/* 48b874: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b879: add esp, 0xc */
L_48b87c:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b87c: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b87d: push 1 */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 48b87f: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b883: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b885: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b88bu; native_call(m, 0x46cbe0u);	/* 48b886: call 0x46cbe0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b88b: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b88c: push 1 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 48b88e: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b892: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b894: push eax */
	m->esp -= 4; M32(m->esp) = 0x48b89au; native_call(m, 0x46cbe0u);	/* 48b895: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 48b89a: mov eax, dword ptr [esp + 0x30] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b89e: add esp, 0x20 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48b8a1: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b8a3: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48b920;	/* 48b8a5: jle 0x48b920 */
L_48b8a7:
	m->ecx = m->edi;	/* 48b8a7: mov ecx, edi */
	{ DWORD a_ = m->ecx, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48b8a9: and ecx, 0x80000001 */
	if (!m->sf) goto L_48b8b6;	/* 48b8af: jns 0x48b8b6 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48b8b1: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48b8b2: or ecx, 0xfffffffe */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48b8b5: inc ecx */
L_48b8b6:
	if (!m->zf) goto L_48b8ca;	/* 48b8b6: jne 0x48b8ca */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8b8: push edi */
	{ DWORD v_ = 0x4c7e38u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8b9: push 0x4c7e38 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8be: push edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8bf: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8c1: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b8c7u; native_call(m, 0x470fc0u);	/* 48b8c2: call 0x470fc0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b8c7: add esp, 0x14 */
L_48b8ca:
	m->eax = m->edi;	/* 48b8ca: mov eax, edi */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48b8cc: xor edx, edx */
	m->ecx = 0x38u;	/* 48b8ce: mov ecx, 0x38 */
	{ unsigned long long n_ = ((unsigned long long)m->edx << 32) | m->eax; DWORD d_ = m->ecx; m->eax = (DWORD)(n_ / d_); m->edx = (DWORD)(n_ % d_); }	/* 48b8d3: div ecx */
	m->ebp = m->edx;	/* 48b8d5: mov ebp, edx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b8d7: test ebp, ebp */
	if (!m->zf) goto L_48b8f2;	/* 48b8d9: jne 0x48b8f2 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8db: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8dc: push ecx */
	m->edx = (DWORD)(m->esp + 0x224u);	/* 48b8dd: lea edx, [esp + 0x224] */
	{ DWORD v_ = 0xb0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8e4: push 0xb0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b8e9: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b8efu; native_call(m, 0x46cbe0u);	/* 48b8ea: call 0x46cbe0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b8ef: add esp, 0x10 */
L_48b8f2:
	m->eax = (DWORD)(m->ebp + m->ebp*4 + 0x0u);	/* 48b8f2: lea eax, [ebp + ebp*4] */
	m->ecx = (DWORD)(m->ebp + m->eax*2 + 0x0u);	/* 48b8f6: lea ecx, [ebp + eax*2] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48b8fa: shl ecx, 4 */
	m->edx = (DWORD)(m->esp + m->ecx*1 + 0x21cu);	/* 48b8fd: lea edx, [esp + ecx + 0x21c] */
	m->ecx = m->esi;	/* 48b904: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b906: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b90cu; native_call(m, 0x490c50u);	/* 48b907: call 0x490c50 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b90c: test eax, eax */
	if (m->sf != m->of) goto L_48b919;	/* 48b90e: jl 0x48b919 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48b910: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 48b914: inc edi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b915: cmp edi, eax */
	if (m->sf != m->of) goto L_48b8a7;	/* 48b917: jl 0x48b8a7 */
L_48b919:
	m->ebp = M32((DWORD)(m->esp + 0x28a0u));	/* 48b919: mov ebp, dword ptr [esp + 0x28a0] */
L_48b920:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b920: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48b926u; native_call(m, 0x49e7e0u);	/* 48b921: call 0x49e7e0 */
	m->eax = (DWORD)(m->esp + 0x120u);	/* 48b926: lea eax, [esp + 0x120] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b92d: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48b92e: push ebp */
	m->esp -= 4; M32(m->esp) = 0x48b934u; native_call(m, 0x46cad0u);	/* 48b92f: call 0x46cad0 */
	m->ecx = (DWORD)(m->esp + 0x128u);	/* 48b934: lea ecx, [esp + 0x128] */
	m->eax = (DWORD)(m->esi + 0x108u);	/* 48b93b: lea eax, [esi + 0x108] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b941: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b942: push eax */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 48b943: lea edx, [esp + 0x30] */
	{ DWORD v_ = 0x4c7e90u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b947: push 0x4c7e90 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b94c: push edx */
	m->esp -= 4; M32(m->esp) = 0x48b952u; native_call(m, 0x49e9ddu);	/* 48b94d: call 0x49e9dd */
	m->eax = M32((DWORD)(m->esp + 0x28c0u));	/* 48b952: mov eax, dword ptr [esp + 0x28c0] */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b959: add esp, 0x1c */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b95c: cmp eax, 1 */
	if (!m->zf) goto L_48b9be;	/* 48b95f: jne 0x48b9be */
	m->eax = M32((DWORD)(m->esi + 0x13016ccu));	/* 48b961: mov eax, dword ptr [esi + 0x13016cc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b967: test eax, eax */
	if (!m->zf) goto L_48b9be;	/* 48b969: jne 0x48b9be */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 48b96b: lea eax, [esp + 0x1c] */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b96f: push 0x4b2ab0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b974: push eax */
	m->esp -= 4; M32(m->esp) = 0x48b97au; native_call(m, 0x49e9cau);	/* 48b975: call 0x49e9ca */
	m->edi = m->eax;	/* 48b97a: mov edi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b97c: add esp, 8 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b97f: test edi, edi */
	if (m->zf) goto L_48b9be;	/* 48b981: je 0x48b9be */
	{ DWORD v_ = 0x4c7e1cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b983: push 0x4c7e1c */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b988: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b98a: push 0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b98c: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b992u; native_call(m, 0x470fc0u);	/* 48b98d: call 0x470fc0 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b992: push edi */
	m->ebx = (DWORD)(m->esi + 0x13016c8u);	/* 48b993: lea ebx, [esi + 0x13016c8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b999: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b99b: push 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b99d: push ebx */
	m->esp -= 4; M32(m->esp) = 0x48b9a3u; native_call(m, 0x46cc30u);	/* 48b99e: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->ebx + 0x0u));	/* 48b9a3: mov ecx, dword ptr [ebx] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9a5: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9a6: push ecx */
	{ DWORD a_ = m->esi, b_ = 0xf30dc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48b9a7: add esi, 0xf30dc8 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9ad: push 4 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9af: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b9b5u; native_call(m, 0x46cc30u);	/* 48b9b0: call 0x46cc30 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b9b5: push edi */
	m->esp -= 4; M32(m->esp) = 0x48b9bbu; native_call(m, 0x49e7e0u);	/* 48b9b6: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b9bb: add esp, 0x34 */
L_48b9be:
	m->edi = M32(m->esp); m->esp += 4;	/* 48b9be: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48b9bf: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48b9c0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48b9c1: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x288cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b9c2: add esp, 0x288c */
	m->esp += 4 + 8; return;	/* 48b9c8: ret 8 */
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
