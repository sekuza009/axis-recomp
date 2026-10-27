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

static void lift_496b80(X86 *m);
static void lift_456d10(X86 *m);
static void lift_490d40(X86 *m);

/* match_490d40 (0x490d40), lifted by tools/lift.py */
static void lift_490d40(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 490d40: push esi */
	m->esi = m->ecx;	/* 490d41: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490d43: push edi */
	m->eax = M32((DWORD)(m->esi + 0x2149308u));	/* 490d44: mov eax, dword ptr [esi + 0x2149308] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 490d4a: test eax, eax */
	if (m->zf) goto L_490d57;	/* 490d4c: je 0x490d57 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x214930cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490d4e: cmp dword ptr [esi + 0x214930c], 1 */
	if (m->zf) goto L_490d90;	/* 490d55: je 0x490d90 */
L_490d57:
	m->eax = M32((DWORD)(m->esi + 0x13c9b24u));	/* 490d57: mov eax, dword ptr [esi + 0x13c9b24] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 490d5d: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 490d5f: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_490d90;	/* 490d61: jle 0x490d90 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 490d63: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 490d64: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 490d65: mov ebp, dword ptr [esp + 0x14] */
	m->ebx = (DWORD)(m->esi + 0x131ae48u);	/* 490d69: lea ebx, [esi + 0x131ae48] */
L_490d6f:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490d6f: cmp dword ptr [ebx], 1 */
	if (!m->zf) goto L_490d7d;	/* 490d72: jne 0x490d7d */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 490d74: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 490d75: push edi */
	m->ecx = m->esi;	/* 490d76: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x490d7du; native_call(m, 0x490440u);	/* 490d78: call 0x490440 */
L_490d7d:
	m->eax = M32((DWORD)(m->esi + 0x13c9b24u));	/* 490d7d: mov eax, dword ptr [esi + 0x13c9b24] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 490d83: inc edi */
	{ DWORD a_ = m->ebx, b_ = 0x2ccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 490d84: add ebx, 0x2cc */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 490d8a: cmp edi, eax */
	if (m->sf != m->of) goto L_490d6f;	/* 490d8c: jl 0x490d6f */
	m->ebp = M32(m->esp); m->esp += 4;	/* 490d8e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 490d8f: pop ebx */
L_490d90:
	m->edi = M32(m->esp); m->esp += 4;	/* 490d90: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 490d91: pop esi */
	m->esp += 4 + 4; return;	/* 490d92: ret 4 */
}

/* replay_drawFollowedName (0x496b80), lifted by tools/lift.py */
static void lift_496b80(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496b80: sub esp, 0x100 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 496b86: push esi */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b87: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b8c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b91: push 0x3f800000 */
	m->esi = m->ecx;	/* 496b96: mov esi, ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496b98: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496ba2u; native_call(m, 0x44ad30u);	/* 496b9d: call 0x44ad30 */
	m->eax = M32((DWORD)(m->esi + 0x2340c64u));	/* 496ba2: mov eax, dword ptr [esi + 0x2340c64] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496ba8: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 496bab: test eax, eax */
	if (m->sf != m->of) goto L_496bdc;	/* 496bad: jl 0x496bdc */
	m->ecx = m->eax;	/* 496baf: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 496bb1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 496bb4: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 496bb6: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 496bb9: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 496bbb: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 496bbe: add ecx, eax */
	m->eax = (DWORD)(m->esp + 0x4u);	/* 496bc0: lea eax, [esp + 4] */
	m->edx = (DWORD)(m->esi + m->ecx*8 + 0x1eccb08u);	/* 496bc4: lea edx, [esi + ecx*8 + 0x1eccb08] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496bcb: push edx */
	{ DWORD v_ = 0x4b3fd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 496bcc: push 0x4b3fd8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 496bd1: push eax */
	m->esp -= 4; M32(m->esp) = 0x496bd7u; native_call(m, 0x49e9ddu);	/* 496bd2: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496bd7: add esp, 0xc */
	goto L_496bee;	/* 496bda: jmp 0x496bee */
L_496bdc:
	m->ecx = (DWORD)(m->esp + 0x4u);	/* 496bdc: lea ecx, [esp + 4] */
	{ DWORD v_ = 0x4d04fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 496be0: push 0x4d04fc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 496be5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x496bebu; native_call(m, 0x49e9ddu);	/* 496be6: call 0x49e9dd */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496beb: add esp, 8 */
L_496bee:
	m->edx = (DWORD)(m->esp + 0x4u);	/* 496bee: lea edx, [esp + 4] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 496bf2: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496bf4: push edx */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 496bf5: push 0x280 */
	{ DWORD v_ = 0x192u; m->esp -= 4; M32(m->esp) = v_; }	/* 496bfa: push 0x192 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496bff: push 0 */
	m->esp -= 4; M32(m->esp) = 0x496c06u; native_call(m, 0x44ae10u);	/* 496c01: call 0x44ae10 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496c06: add esp, 0x14 */
	m->esi = M32(m->esp); m->esp += 4;	/* 496c09: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496c0a: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 496c10: ret  */
}

/* sound_initSoundTable (0x456d10), lifted by tools/lift.py */
static void lift_456d10(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e80cu));	/* 456d10: mov eax, dword ptr [0xa0e80c] */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456d15: sub esp, 0x104 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456d1b: test eax, eax */
	if (!m->zf) goto L_456d28;	/* 456d1d: jne 0x456d28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 456d1f: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456d21: add esp, 0x104 */
	m->esp += 4 + 0; return;	/* 456d27: ret  */
L_456d28:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456d28: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456d29: push edi */
	m->esp -= 4; M32(m->esp) = 0x456d2fu; native_call(m, 0x456cd0u);	/* 456d2a: call 0x456cd0 */
	m->eax = M32((DWORD)(m->esp + 0x114u));	/* 456d2f: mov eax, dword ptr [esp + 0x114] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456d36: push eax */
	m->esp -= 4; M32(m->esp) = 0x456d3cu; native_call(m, 0x456de0u);	/* 456d37: call 0x456de0 */
	m->edi = M32((DWORD)(m->esp + 0x114u));	/* 456d3c: mov edi, dword ptr [esp + 0x114] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 456d43: push 0x4ad170 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456d48: push edi */
	m->esp -= 4; M32(m->esp) = 0x456d4eu; native_call(m, 0x49e9cau);	/* 456d49: call 0x49e9ca */
	m->esi = m->eax;	/* 456d4e: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456d50: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456d53: test esi, esi */
	if (!m->zf) goto L_456d6a;	/* 456d55: jne 0x456d6a */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456d57: push edi */
	{ DWORD v_ = 0x4b42e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 456d58: push 0x4b42e8 */
	{ DWORD v_ = 0xa0e020u; m->esp -= 4; M32(m->esp) = v_; }	/* 456d5d: push 0xa0e020 */
	m->esp -= 4; M32(m->esp) = 0x456d67u; native_call(m, 0x46c710u);	/* 456d62: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456d67: add esp, 0xc */
L_456d6a:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456d6a: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 456d6b: push 1 */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 456d6d: lea ecx, [esp + 0x10] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 456d71: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 456d73: push ecx */
	m->esp -= 4; M32(m->esp) = 0x456d79u; native_call(m, 0x46cbe0u);	/* 456d74: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 456d79: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456d7d: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456d80: test eax, eax */
	if (m->sf != m->of) goto L_456dc5;	/* 456d82: jl 0x456dc5 */
L_456d84:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456d84: push esi */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 456d85: push 0x100 */
	m->edx = (DWORD)(m->esp + 0x14u);	/* 456d8a: lea edx, [esp + 0x14] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 456d8e: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456d90: push edx */
	m->esp -= 4; M32(m->esp) = 0x456d96u; native_call(m, 0x46cbe0u);	/* 456d91: call 0x46cbe0 */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 456d96: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456d9a: push eax */
	m->esp -= 4; M32(m->esp) = 0x456da0u; native_call(m, 0x467b90u);	/* 456d9b: call 0x467b90 */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 456da0: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456da4: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 456da5: push 1 */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 456da7: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 456dab: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456dad: push edx */
	M32((DWORD)(m->ecx*4 + 0xa0e02cu)) = m->eax;	/* 456dae: mov dword ptr [ecx*4 + 0xa0e02c], eax */
	m->esp -= 4; M32(m->esp) = 0x456dbau; native_call(m, 0x46cbe0u);	/* 456db5: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 456dba: mov eax, dword ptr [esp + 0x2c] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456dbe: add esp, 0x24 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456dc1: test eax, eax */
	if (m->sf == m->of) goto L_456d84;	/* 456dc3: jge 0x456d84 */
L_456dc5:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456dc5: push esi */
	m->esp -= 4; M32(m->esp) = 0x456dcbu; native_call(m, 0x49e7e0u);	/* 456dc6: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456dcb: add esp, 4 */
	m->eax = 0x1u;	/* 456dce: mov eax, 1 */
	m->edi = M32(m->esp); m->esp += 4;	/* 456dd3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 456dd4: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456dd5: add esp, 0x104 */
	m->esp += 4 + 0; return;	/* 456ddb: ret  */
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
