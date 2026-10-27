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

static void lift_48ec20(X86 *m);
static void lift_490c50(X86 *m);

/* object_addObjectBy (0x490c50), lifted by tools/lift.py */
static void lift_490c50(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490c50: push esi */
	m->esi = m->ecx;	/* 490c51: mov esi, ecx */
	m->ecx = M32((DWORD)(m->esi + 0x13c9b28u));	/* 490c53: mov ecx, dword ptr [esi + 0x13c9b28] */
	{ DWORD a_ = m->ecx, b_ = 0x3e8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490c59: cmp ecx, 0x3e8 */
	if (m->sf != m->of) goto L_490c81;	/* 490c5f: jl 0x490c81 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 490c61: inc ecx */
	{ DWORD v_ = 0x3e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 490c62: push 0x3e8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 490c67: push ecx */
	{ DWORD v_ = 0x4c8398u; m->esp -= 4; M32(m->esp) = v_; }	/* 490c68: push 0x4c8398 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 490c6d: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x490c77u; native_call(m, 0x46c5f0u);	/* 490c72: call 0x46c5f0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 490c77: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 490c7a: or eax, 0xffffffff */
	m->esi = M32(m->esp); m->esp += 4;	/* 490c7d: pop esi */
	m->esp += 4 + 4; return;	/* 490c7e: ret 4 */
L_490c81:
	m->eax = M32((DWORD)(m->esi + 0x13c9b24u));	/* 490c81: mov eax, dword ptr [esi + 0x13c9b24] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490c87: cmp ecx, eax */
	if (!m->zf) goto L_490ca8;	/* 490c89: jne 0x490ca8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 490c8b: inc eax */
	M32((DWORD)(m->esi + 0x13c9b24u)) = m->eax;	/* 490c8c: mov dword ptr [esi + 0x13c9b24], eax */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 490c92: lea ecx, [eax + eax*4] */
	m->ecx = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 490c95: lea ecx, [ecx + ecx*8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 490c98: shl ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 490c9b: sub ecx, eax */
	M32((DWORD)(m->esi + m->ecx*4 + 0x131ae48u)) = 0x0u;	/* 490c9d: mov dword ptr [esi + ecx*4 + 0x131ae48], 0 */
L_490ca8:
	m->edx = M32((DWORD)(m->esp + 0x8u));	/* 490ca8: mov edx, dword ptr [esp + 8] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490cac: push edi */
	m->edi = M32((DWORD)(m->esi + 0x13c9b28u));	/* 490cad: mov edi, dword ptr [esi + 0x13c9b28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 490cb3: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490cb4: push edi */
	m->ecx = m->esi;	/* 490cb5: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x490cbcu; native_call(m, 0x48fee0u);	/* 490cb7: call 0x48fee0 */
	m->eax = M32((DWORD)(m->esi + 0x13c9b28u));	/* 490cbc: mov eax, dword ptr [esi + 0x13c9b28] */
	m->edx = M32((DWORD)(m->esi + 0x13c9b24u));	/* 490cc2: mov edx, dword ptr [esi + 0x13c9b24] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 490cc8: inc eax */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490cc9: cmp eax, edx */
	if (!m->zf && m->sf == m->of) goto L_490cfc;	/* 490ccb: jg 0x490cfc */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 490ccd: lea ecx, [eax + eax*4] */
	m->ecx = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 490cd0: lea ecx, [ecx + ecx*8] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 490cd3: shl ecx, 2 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 490cd6: sub ecx, eax */
	m->ecx = (DWORD)(m->esi + m->ecx*4 + 0x131ae48u);	/* 490cd8: lea ecx, [esi + ecx*4 + 0x131ae48] */
L_490cdf:
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490cdf: cmp dword ptr [ecx], 0 */
	if (m->zf) goto L_490cf6;	/* 490ce2: je 0x490cf6 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 490ce4: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x2ccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 490ce5: add ecx, 0x2cc */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490ceb: cmp eax, edx */
	if (m->zf || m->sf != m->of) goto L_490cdf;	/* 490ced: jle 0x490cdf */
	m->eax = m->edi;	/* 490cef: mov eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 490cf1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 490cf2: pop esi */
	m->esp += 4 + 4; return;	/* 490cf3: ret 4 */
L_490cf6:
	M32((DWORD)(m->esi + 0x13c9b28u)) = m->eax;	/* 490cf6: mov dword ptr [esi + 0x13c9b28], eax */
L_490cfc:
	m->eax = m->edi;	/* 490cfc: mov eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 490cfe: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 490cff: pop esi */
	m->esp += 4 + 4; return;	/* 490d00: ret 4 */
}

/* effect_initTextures (0x48ec20), lifted by tools/lift.py */
static void lift_48ec20(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ec20: sub esp, 0x100 */
	m->eax = 0x64u;	/* 48ec26: mov eax, 0x64 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec2b: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec2c: push ebp */
	m->ebp = m->ecx;	/* 48ec2d: mov ebp, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec2f: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec30: push edi */
	m->ecx = M32((DWORD)(m->ebp + 0x20f2f3cu));	/* 48ec31: mov ecx, dword ptr [ebp + 0x20f2f3c] */
L_48ec37:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48ec37: xor ecx, ecx */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48ec39: dec eax */
	if (!m->zf) goto L_48ec37;	/* 48ec3a: jne 0x48ec37 */
	M32((DWORD)(m->ebp + 0x20f2f3cu)) = m->ecx;	/* 48ec3c: mov dword ptr [ebp + 0x20f2f3c], ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48ec42: xor ebx, ebx */
	m->esi = (DWORD)(m->ebp + 0x19e188cu);	/* 48ec44: lea esi, [ebp + 0x19e188c] */
	m->edi = (DWORD)(m->ebp + 0x20f2dacu);	/* 48ec4a: lea edi, [ebp + 0x20f2dac] */
L_48ec50:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec50: push ebx */
	m->eax = (DWORD)(m->esp + 0x14u);	/* 48ec51: lea eax, [esp + 0x14] */
	{ DWORD v_ = 0x4c8170u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec55: push 0x4c8170 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec5a: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ec60u; native_call(m, 0x49e9ddu);	/* 48ec5b: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ec60: add esp, 0xc */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 48ec63: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec67: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec69: push ecx */
	m->ecx = m->esi;	/* 48ec6a: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48ec71u; native_call(m, 0x466dc0u);	/* 48ec6c: call 0x466dc0 */
	M32((DWORD)(m->edi + 0x0u)) = m->eax;	/* 48ec71: mov dword ptr [edi], eax */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 48ec73: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48ec74: add edi, 4 */
	{ DWORD a_ = m->ebx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ec77: cmp ebx, 8 */
	if (m->sf != m->of) goto L_48ec50;	/* 48ec7a: jl 0x48ec50 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48ec7c: xor ebx, ebx */
	m->edi = (DWORD)(m->ebp + 0x20f2dccu);	/* 48ec7e: lea edi, [ebp + 0x20f2dcc] */
L_48ec84:
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec84: push ebx */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 48ec85: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x4c815cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec89: push 0x4c815c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec8e: push edx */
	m->esp -= 4; M32(m->esp) = 0x48ec94u; native_call(m, 0x49e9ddu);	/* 48ec8f: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ec94: add esp, 0xc */
	m->eax = (DWORD)(m->esp + 0x10u);	/* 48ec97: lea eax, [esp + 0x10] */
	m->ecx = m->esi;	/* 48ec9b: mov ecx, esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec9d: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec9f: push eax */
	m->esp -= 4; M32(m->esp) = 0x48eca5u; native_call(m, 0x466dc0u);	/* 48eca0: call 0x466dc0 */
	M32((DWORD)(m->edi + 0x0u)) = m->eax;	/* 48eca5: mov dword ptr [edi], eax */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 48eca7: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48eca8: add edi, 4 */
	{ DWORD a_ = m->ebx, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ecab: cmp ebx, 8 */
	if (m->sf != m->of) goto L_48ec84;	/* 48ecae: jl 0x48ec84 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 48ecb0: xor edi, edi */
	m->ebx = (DWORD)(m->ebp + 0x20f2decu);	/* 48ecb2: lea ebx, [ebp + 0x20f2dec] */
L_48ecb8:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ecb8: push edi */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 48ecb9: lea ecx, [esp + 0x14] */
	{ DWORD v_ = 0x4c8144u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ecbd: push 0x4c8144 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ecc2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48ecc8u; native_call(m, 0x49e9ddu);	/* 48ecc3: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ecc8: add esp, 0xc */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 48eccb: lea edx, [esp + 0x10] */
	m->ecx = m->esi;	/* 48eccf: mov ecx, esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ecd1: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ecd3: push edx */
	m->esp -= 4; M32(m->esp) = 0x48ecd9u; native_call(m, 0x466dc0u);	/* 48ecd4: call 0x466dc0 */
	M32((DWORD)(m->ebx + 0x0u)) = m->eax;	/* 48ecd9: mov dword ptr [ebx], eax */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 48ecdb: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48ecdc: add ebx, 4 */
	{ DWORD a_ = m->edi, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ecdf: cmp edi, 8 */
	if (m->sf != m->of) goto L_48ecb8;	/* 48ece2: jl 0x48ecb8 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ece4: push 1 */
	{ DWORD v_ = 0x4c8130u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ece6: push 0x4c8130 */
	m->ecx = m->esi;	/* 48eceb: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48ecf2u; native_call(m, 0x466dc0u);	/* 48eced: call 0x466dc0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ecf2: push 1 */
	{ DWORD v_ = 0x4c811cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48ecf4: push 0x4c811c */
	m->ecx = m->esi;	/* 48ecf9: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x20f2e74u)) = m->eax;	/* 48ecfb: mov dword ptr [ebp + 0x20f2e74], eax */
	m->esp -= 4; M32(m->esp) = 0x48ed06u; native_call(m, 0x466dc0u);	/* 48ed01: call 0x466dc0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed06: push 1 */
	{ DWORD v_ = 0x4c8108u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed08: push 0x4c8108 */
	m->ecx = m->esi;	/* 48ed0d: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x20f2e78u)) = m->eax;	/* 48ed0f: mov dword ptr [ebp + 0x20f2e78], eax */
	m->esp -= 4; M32(m->esp) = 0x48ed1au; native_call(m, 0x466dc0u);	/* 48ed15: call 0x466dc0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed1a: push 1 */
	{ DWORD v_ = 0x4c80f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed1c: push 0x4c80f4 */
	m->ecx = m->esi;	/* 48ed21: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x20f2e7cu)) = m->eax;	/* 48ed23: mov dword ptr [ebp + 0x20f2e7c], eax */
	m->esp -= 4; M32(m->esp) = 0x48ed2eu; native_call(m, 0x466dc0u);	/* 48ed29: call 0x466dc0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed2e: push 1 */
	{ DWORD v_ = 0x4c80e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed30: push 0x4c80e0 */
	m->ecx = m->esi;	/* 48ed35: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x20f2e80u)) = m->eax;	/* 48ed37: mov dword ptr [ebp + 0x20f2e80], eax */
	m->esp -= 4; M32(m->esp) = 0x48ed42u; native_call(m, 0x466dc0u);	/* 48ed3d: call 0x466dc0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed42: push 1 */
	{ DWORD v_ = 0x4c80c8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed44: push 0x4c80c8 */
	m->ecx = m->esi;	/* 48ed49: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x20f2e84u)) = m->eax;	/* 48ed4b: mov dword ptr [ebp + 0x20f2e84], eax */
	m->esp -= 4; M32(m->esp) = 0x48ed56u; native_call(m, 0x466dc0u);	/* 48ed51: call 0x466dc0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed56: push 1 */
	{ DWORD v_ = 0x4c80b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed58: push 0x4c80b0 */
	m->ecx = m->esi;	/* 48ed5d: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x20f2e88u)) = m->eax;	/* 48ed5f: mov dword ptr [ebp + 0x20f2e88], eax */
	m->esp -= 4; M32(m->esp) = 0x48ed6au; native_call(m, 0x466dc0u);	/* 48ed65: call 0x466dc0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed6a: push 1 */
	{ DWORD v_ = 0x4c8098u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ed6c: push 0x4c8098 */
	m->ecx = m->esi;	/* 48ed71: mov ecx, esi */
	M32((DWORD)(m->ebp + 0x20f2e8cu)) = m->eax;	/* 48ed73: mov dword ptr [ebp + 0x20f2e8c], eax */
	m->esp -= 4; M32(m->esp) = 0x48ed7eu; native_call(m, 0x466dc0u);	/* 48ed79: call 0x466dc0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 48ed7e: pop edi */
	M32((DWORD)(m->ebp + 0x20f2e90u)) = m->eax;	/* 48ed7f: mov dword ptr [ebp + 0x20f2e90], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 48ed85: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48ed86: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48ed87: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ed88: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 48ed8e: ret  */
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
