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

static void lift_4456b0(X86 *m);
static void lift_444f40(X86 *m);
static void lift_439e00(X86 *m);

/* room_439e00 (0x439e00), lifted by tools/lift.py */
static void lift_439e00(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 439e00: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439e05: sub esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 439e08: test eax, eax */
	if (m->zf) goto L_439e32;	/* 439e0a: je 0x439e32 */
	m->eax = M32((DWORD)(0x9dd1acu));	/* 439e0c: mov eax, dword ptr [0x9dd1ac] */
	m->ecx = M32((DWORD)(0x9dd1a8u));	/* 439e11: mov ecx, dword ptr [0x9dd1a8] */
	m->edx = M32((DWORD)(0x9dd1a4u));	/* 439e17: mov edx, dword ptr [0x9dd1a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439e1d: push eax */
	m->eax = M32((DWORD)(0x9dd1a0u));	/* 439e1e: mov eax, dword ptr [0x9dd1a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439e23: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439e24: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439e25: push eax */
	m->esp -= 4; M32(m->esp) = 0x439e2bu; native_call(m, 0x428c30u);	/* 439e26: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439e2b: add esp, 0x10 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439e2e: add esp, 8 */
	m->esp += 4 + 0; return;	/* 439e31: ret  */
L_439e32:
	m->ecx = M32((DWORD)(0x4ded6cu));	/* 439e32: mov ecx, dword ptr [0x4ded6c] */
	m->edx = M32((DWORD)(0x4ded68u));	/* 439e38: mov edx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 439e3e: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 439e3f: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 439e40: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 439e41: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439e42: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439e43: push edx */
	m->esp -= 4; M32(m->esp) = 0x439e49u; native_call(m, 0x432280u);	/* 439e44: call 0x432280 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 439e49: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 439e4b: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x439e54u; native_call(m, 0x41ef90u);	/* 439e4f: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439e54: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x439e5du; native_call(m, M32(0x4a9218u));	/* 439e57: call dword ptr [0x4a9218] */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 439e5d: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439e63: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439e68: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439e6d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439e72: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x439e79u; native_call(m, m->ebx);	/* 439e77: call ebx */
	m->eax = M32((DWORD)(0x4deb50u));	/* 439e79: mov eax, dword ptr [0x4deb50] */
	m->ecx = M32((DWORD)(0x9dd1acu));	/* 439e7e: mov ecx, dword ptr [0x9dd1ac] */
	m->edx = M32((DWORD)(0x9dd1a8u));	/* 439e84: mov edx, dword ptr [0x9dd1a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439e8a: push eax */
	m->eax = M32((DWORD)(0x9dd1a4u));	/* 439e8b: mov eax, dword ptr [0x9dd1a4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439e90: push ecx */
	m->ecx = M32((DWORD)(0x9dd1a0u));	/* 439e91: mov ecx, dword ptr [0x9dd1a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439e97: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439e98: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439e99: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439e9fu; native_call(m, 0x427b60u);	/* 439e9a: call 0x427b60 */
	m->edx = M32((DWORD)(0x9dceccu));	/* 439e9f: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 439ea5: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 439eaa: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439eb0: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 439eb1: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439eb7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439eb8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439eb9: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 439eba: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x439ec4u; native_call(m, 0x41f0e0u);	/* 439ebf: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1a4u));	/* 439ec4: mov eax, dword ptr [0x9dd1a4] */
	m->ecx = M32((DWORD)(0x9dd1a0u));	/* 439ec9: mov ecx, dword ptr [0x9dd1a0] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439ecf: add eax, 0x10 */
	{ DWORD v_ = 0x758da4u; m->esp -= 4; M32(m->esp) = v_; }	/* 439ed2: push 0x758da4 */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439ed7: add ecx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439eda: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439edb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x439ee1u; native_call(m, 0x4028b0u);	/* 439edc: call 0x4028b0 */
	m->edx = M32((DWORD)(0x9dceccu));	/* 439ee1: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 439ee7: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 439eec: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439ef2: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 439ef3: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439ef9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439efa: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439efb: push edx */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 439efc: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x439f06u; native_call(m, 0x41f0e0u);	/* 439f01: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439f06: add esp, 0x48 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f09: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f0e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f13: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f18: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f1a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x439f24u; native_call(m, 0x41f0e0u);	/* 439f1f: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1a4u));	/* 439f24: mov eax, dword ptr [0x9dd1a4] */
	m->ecx = M32((DWORD)(0x9dd1a8u));	/* 439f29: mov ecx, dword ptr [0x9dd1a8] */
	m->edx = M32((DWORD)(0x9dd1a0u));	/* 439f2f: mov edx, dword ptr [0x9dd1a0] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439f35: add eax, 0x20 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439f38: add ecx, -0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439f3b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439f3c: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 439f3d: add edx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439f40: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439f41: push edx */
	m->esp -= 4; M32(m->esp) = 0x439f47u; native_call(m, 0x427a40u);	/* 439f42: call 0x427a40 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f47: push 0x3f800000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 439f4c: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 439f51: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 439f56: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f5b: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x439f65u; native_call(m, 0x41f0e0u);	/* 439f60: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1a4u));	/* 439f65: mov eax, dword ptr [0x9dd1a4] */
	m->edx = M32((DWORD)(0x9dd1a8u));	/* 439f6a: mov edx, dword ptr [0x9dd1a8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f70: push 1 */
	{ DWORD a_ = m->edx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 439f72: add edx, -0x30 */
	m->ecx = (DWORD)(m->eax + 0x60u);	/* 439f75: lea ecx, [eax + 0x60] */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439f78: add eax, 0x40 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439f7b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439f7c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439f7d: push eax */
	m->eax = M32((DWORD)(0x9dd1a0u));	/* 439f7e: mov eax, dword ptr [0x9dd1a0] */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439f83: add eax, 0x30 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439f86: push eax */
	m->esp -= 4; M32(m->esp) = 0x439f8cu; native_call(m, 0x427970u);	/* 439f87: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 439f8c: add esp, 0x4c */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f8f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f94: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f96: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f9b: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 439f9d: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x439fa7u; native_call(m, 0x41f0e0u);	/* 439fa2: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1a4u));	/* 439fa7: mov eax, dword ptr [0x9dd1a4] */
	m->edx = M32((DWORD)(0x9dd1a8u));	/* 439fac: mov edx, dword ptr [0x9dd1a8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439fb2: push 0 */
	{ DWORD a_ = m->edx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 439fb4: add edx, -0x30 */
	m->ecx = (DWORD)(m->eax + 0x60u);	/* 439fb7: lea ecx, [eax + 0x60] */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439fba: add eax, 0x40 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 439fbd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 439fbe: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439fbf: push eax */
	m->eax = M32((DWORD)(0x9dd1a0u));	/* 439fc0: mov eax, dword ptr [0x9dd1a0] */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 439fc5: add eax, 0x30 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 439fc8: push eax */
	m->esp -= 4; M32(m->esp) = 0x439fceu; native_call(m, 0x427970u);	/* 439fc9: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439fce: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 439fd3: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439fd5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 439fda: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 439fdf: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x439fe9u; native_call(m, 0x41f0e0u);	/* 439fe4: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd1a8u));	/* 439fe9: mov ecx, dword ptr [0x9dd1a8] */
	m->edx = M32((DWORD)(0x9dd1a4u));	/* 439fef: mov edx, dword ptr [0x9dd1a4] */
	m->eax = M32((DWORD)(0x9dd1a0u));	/* 439ff5: mov eax, dword ptr [0x9dd1a0] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 439ffa: add ecx, -0x30 */
	{ DWORD v_ = 0x9dd1d8u; m->esp -= 4; M32(m->esp) = v_; }	/* 439ffd: push 0x9dd1d8 */
	{ DWORD a_ = m->edx, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43a002: add edx, 0x48 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a005: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a006: add eax, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a009: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a00a: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a010u; native_call(m, 0x4029d0u);	/* 43a00b: call 0x4029d0 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43a010: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43a016: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43a01c: mov eax, dword ptr [0x9dcec4] */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a021: add esp, 0x4c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a024: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43a025: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a02b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a02c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a02d: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a02e: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43a038u; native_call(m, 0x41f0e0u);	/* 43a033: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1a4u));	/* 43a038: mov eax, dword ptr [0x9dd1a4] */
	m->edx = M32((DWORD)(0x9dd1a8u));	/* 43a03d: mov edx, dword ptr [0x9dd1a8] */
	m->ecx = M32((DWORD)(0x9dd1a0u));	/* 43a043: mov ecx, dword ptr [0x9dd1a0] */
	{ DWORD v_ = 0x758e24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a049: push 0x758e24 */
	{ DWORD a_ = m->eax, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a04e: add eax, 0x8c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a053: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a054: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a055: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43a05bu; native_call(m, 0x4029d0u);	/* 43a056: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a05b: add esp, 0x24 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 43a05e: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43a060: xor esi, esi */
	m->edi = 0x758f24u;	/* 43a062: mov edi, 0x758f24 */
L_43a067:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a067: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43a072u; native_call(m, M32(0x4a9224u));	/* 43a06c: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43a072: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 43a077: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43a079: and edx, 0x800001ff */
	if (!m->sf) goto L_43a089;	/* 43a07f: jns 0x43a089 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 43a081: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43a082: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 43a088: inc edx */
L_43a089:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a089: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43a08a: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43a090: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43a091: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a097: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43a099: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 43a09c: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43a0a5u; native_call(m, 0x4566c0u);	/* 43a0a0: call 0x4566c0 */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x10u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43a0a5: cmp dword ptr [esp + 0x10], ebp */
	if (!m->zf) goto L_43a104;	/* 43a0a9: jne 0x43a104 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0ab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0b0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0b5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0ba: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43a0c1u; native_call(m, m->ebx);	/* 43a0bf: call ebx */
	m->ecx = M32((DWORD)(0x9dd1acu));	/* 43a0c1: mov ecx, dword ptr [0x9dd1ac] */
	m->eax = M32((DWORD)(0x9dd1a0u));	/* 43a0c7: mov eax, dword ptr [0x9dd1a0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0cc: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 43a0ce: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a0d1: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0d4: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 43a0d5: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0dc: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 43a0dd: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0e1: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0e2: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a0e8u; native_call(m, 0x4282f0u);	/* 43a0e3: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43a0e8: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43a0ee: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43a0f4: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a0f9: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43a0fa: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a100: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a101: push eax */
	goto L_43a15b;	/* 43a102: jmp 0x43a15b */
L_43a104:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a104: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a109: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a10e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a113: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43a11au; native_call(m, m->ebx);	/* 43a118: call ebx */
	m->ecx = M32((DWORD)(0x9dd1acu));	/* 43a11a: mov ecx, dword ptr [0x9dd1ac] */
	m->eax = M32((DWORD)(0x9dd1a0u));	/* 43a120: mov eax, dword ptr [0x9dd1a0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a125: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 43a127: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a12a: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a12d: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 43a12e: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a135: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 43a136: lea eax, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a13a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a13b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a141u; native_call(m, 0x4282f0u);	/* 43a13c: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dd344u));	/* 43a141: mov ecx, dword ptr [0x9dd344] */
	m->edx = M32((DWORD)(0x9dd340u));	/* 43a147: mov edx, dword ptr [0x9dd340] */
	m->eax = M32((DWORD)(0x9dd33cu));	/* 43a14d: mov eax, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a152: push ecx */
	m->ecx = M32((DWORD)(0x9dd338u));	/* 43a153: mov ecx, dword ptr [0x9dd338] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a159: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a15a: push eax */
L_43a15b:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a15b: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a15c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43a166u; native_call(m, 0x41f0e0u);	/* 43a161: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1a0u));	/* 43a166: mov eax, dword ptr [0x9dd1a0] */
	m->ecx = M32((DWORD)(0x9dd1acu));	/* 43a16b: mov ecx, dword ptr [0x9dd1ac] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a171: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43a174: add ecx, -0x38 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xdcu);	/* 43a177: lea edx, [esi + eax + 0xdc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a17e: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a17f: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x64u);	/* 43a180: lea edx, [esi + eax + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a184: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a185: push edx */
	m->esp -= 4; M32(m->esp) = 0x43a18bu; native_call(m, 0x4029d0u);	/* 43a186: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a18b: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43a18e: add edi, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 43a194: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xb4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43a195: add esi, 0xb4 */
	{ DWORD a_ = m->edi, b_ = 0x759024u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43a19b: cmp edi, 0x759024 */
	if (m->sf != m->of) goto L_43a067;	/* 43a1a1: jl 0x43a067 */
	m->eax = M32((DWORD)(0x9dd850u));	/* 43a1a7: mov eax, dword ptr [0x9dd850] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43a1ac: test eax, eax */
	if (m->zf) goto L_43a3d2;	/* 43a1ae: je 0x43a3d2 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 43a1b4: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 43a1b9: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1bf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1c0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43a1c6u; native_call(m, 0x4321c0u);	/* 43a1c1: call 0x4321c0 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1c6: push 0x3f000000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1cb: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1d0: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1d5: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1da: push 0x9da480 */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 43a1df: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x43a1e8u; native_call(m, 0x41f0e0u);	/* 43a1e3: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1e8: push 1 */
	{ DWORD v_ = 0x1e0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1ea: push 0x1e0 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1ef: push 0x280 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1f4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1f6: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43a1fdu; native_call(m, 0x427970u);	/* 43a1f8: call 0x427970 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a1fd: push 0x3f4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a202: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a207: push 0x3dcccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a20c: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a211: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43a21bu; native_call(m, 0x41f0e0u);	/* 43a216: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a21b: add esp, 0x44 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a21e: push 1 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a220: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a225: push 0x21c */
	{ DWORD v_ = 0xb4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a22a: push 0xb4 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a22f: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x43a236u; native_call(m, 0x427970u);	/* 43a231: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a236: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a23b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a240: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a245: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a247: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43a251u; native_call(m, 0x41f0e0u);	/* 43a24c: call 0x41f0e0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a251: push 0 */
	{ DWORD v_ = 0x13cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a253: push 0x13c */
	{ DWORD v_ = 0x218u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a258: push 0x218 */
	{ DWORD v_ = 0xb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a25d: push 0xb8 */
	{ DWORD v_ = 0x68u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a262: push 0x68 */
	m->esp -= 4; M32(m->esp) = 0x43a269u; native_call(m, 0x427970u);	/* 43a264: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a269: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a26e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a273: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a278: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a27d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43a287u; native_call(m, 0x41f0e0u);	/* 43a282: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a287: add esp, 0x50 */
	{ DWORD v_ = 0x74dfa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a28a: push 0x74dfa4 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a28f: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a294: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a299: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x43a2a0u; native_call(m, 0x4029d0u);	/* 43a29b: call 0x4029d0 */
	{ DWORD v_ = 0x74e024u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a2a0: push 0x74e024 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a2a5: push 0x21c */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a2aa: push 0xdc */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a2af: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x43a2b6u; native_call(m, 0x4029d0u);	/* 43a2b1: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a2b6: add esp, 0x20 */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 43a2b9: mov dword ptr [esp + 0x14], 0 */
	m->esi = 0xb4u;	/* 43a2c1: mov esi, 0xb4 */
	m->ebp = 0x7517a4u;	/* 43a2c6: mov ebp, 0x7517a4 */
L_43a2cb:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a2cb: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43a2d6u; native_call(m, M32(0x4a9224u));	/* 43a2d0: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43a2d6: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 43a2db: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43a2dd: and edx, 0x800001ff */
	if (!m->sf) goto L_43a2ed;	/* 43a2e3: jns 0x43a2ed */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 43a2e5: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43a2e6: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 43a2ec: inc edx */
L_43a2ed:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a2ed: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43a2ee: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43a2f4: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43a2f5: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43a2fb: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43a2fd: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 43a300: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43a309u; native_call(m, 0x4566c0u);	/* 43a304: call 0x4566c0 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 43a309: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 43a30d: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43a311: cmp eax, edx */
	if (!m->zf) goto L_43a354;	/* 43a313: jne 0x43a354 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a315: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a31a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a31f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a324: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43a32bu; native_call(m, m->ebx);	/* 43a329: call ebx */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 43a32b: lea edi, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a32e: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a330: push 0x124 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a335: push edi */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a336: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a33b: push esi */
	m->esp -= 4; M32(m->esp) = 0x43a341u; native_call(m, 0x4282f0u);	/* 43a33c: call 0x4282f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a341: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a346: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a34b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a350: push 0 */
	goto L_43a394;	/* 43a352: jmp 0x43a394 */
L_43a354:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a354: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a359: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a35e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a363: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43a36au; native_call(m, m->ebx);	/* 43a368: call ebx */
	m->edi = (DWORD)(m->esi + 0x78u);	/* 43a36a: lea edi, [esi + 0x78] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a36d: push 1 */
	{ DWORD v_ = 0x124u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a36f: push 0x124 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a374: push edi */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a375: push 0x104 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a37a: push esi */
	m->esp -= 4; M32(m->esp) = 0x43a380u; native_call(m, 0x4282f0u);	/* 43a37b: call 0x4282f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a380: push 0x3f800000 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a385: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a38a: push 0x3f333333 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43a38f: push 0x3e99999a */
L_43a394:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a394: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43a39eu; native_call(m, 0x41f0e0u);	/* 43a399: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a39e: add esp, 0x28 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3a1: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3a2: push edi */
	{ DWORD v_ = 0x10cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3a3: push 0x10c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3a8: push esi */
	m->esp -= 4; M32(m->esp) = 0x43a3aeu; native_call(m, 0x4029d0u);	/* 43a3a9: call 0x4029d0 */
	m->edi = M32((DWORD)(m->esp + 0x24u));	/* 43a3ae: mov edi, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a3b2: add esp, 0x10 */
	{ DWORD a_ = m->ebp, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 43a3b5: add ebp, 0x80 */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 43a3bb: inc edi */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43a3bc: add esi, 0xa0 */
	{ DWORD a_ = m->ebp, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43a3c2: cmp ebp, 0x7518a4 */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 43a3c8: mov dword ptr [esp + 0x14], edi */
	if (m->sf != m->of) goto L_43a2cb;	/* 43a3cc: jl 0x43a2cb */
L_43a3d2:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3d2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3d7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3dc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3e1: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43a3e8u; native_call(m, m->ebx);	/* 43a3e6: call ebx */
	m->eax = M32((DWORD)(0x9dd1acu));	/* 43a3e8: mov eax, dword ptr [0x9dd1ac] */
	m->ecx = M32((DWORD)(0x9dd1a8u));	/* 43a3ed: mov ecx, dword ptr [0x9dd1a8] */
	m->edx = M32((DWORD)(0x9dd1a4u));	/* 43a3f3: mov edx, dword ptr [0x9dd1a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3f9: push eax */
	m->eax = M32((DWORD)(0x9dd1a0u));	/* 43a3fa: mov eax, dword ptr [0x9dd1a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a3ff: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43a400: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43a401: push eax */
	m->esp -= 4; M32(m->esp) = 0x43a407u; native_call(m, 0x428b50u);	/* 43a402: call 0x428b50 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a407: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43a40a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43a40b: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43a40c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43a40d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43a40e: add esp, 8 */
	m->esp += 4 + 0; return;	/* 43a411: ret  */
}

/* skirmish_drawScreenB (0x4456b0), lifted by tools/lift.py */
static void lift_4456b0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4456b0: push ecx */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 4456b1: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 4456b6: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4456bc: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4456bd: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4456be: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4456bf: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4456c0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4456c1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4456c7u; native_call(m, 0x443910u);	/* 4456c2: call 0x443910 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4456c7: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4456c9: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x4456d2u; native_call(m, 0x41ef90u);	/* 4456cd: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4456d2: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x4456dbu; native_call(m, M32(0x4a9218u));	/* 4456d5: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4456db: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4456e0: push 0x3f000000 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4456e5: push 0x3e4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 4456ea: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 4456ef: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x4456f9u; native_call(m, 0x41f0e0u);	/* 4456f4: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9f16b4u));	/* 4456f9: mov edx, dword ptr [0x9f16b4] */
	m->eax = M32((DWORD)(0x9f16b0u));	/* 4456ff: mov eax, dword ptr [0x9f16b0] */
	m->ecx = M32((DWORD)(0x9f16acu));	/* 445704: mov ecx, dword ptr [0x9f16ac] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44570a: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44570c: push edx */
	m->edx = M32((DWORD)(0x9f16a8u));	/* 44570d: mov edx, dword ptr [0x9f16a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445713: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445714: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445715: push edx */
	m->esp -= 4; M32(m->esp) = 0x44571bu; native_call(m, 0x427970u);	/* 445716: call 0x427970 */
	m->eax = M32((DWORD)(0x9ef214u));	/* 44571b: mov eax, dword ptr [0x9ef214] */
	m->ecx = M32((DWORD)(0x9ef210u));	/* 445720: mov ecx, dword ptr [0x9ef210] */
	m->edx = M32((DWORD)(0x9ef20cu));	/* 445726: mov edx, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44572c: push eax */
	m->eax = M32((DWORD)(0x9ef208u));	/* 44572d: mov eax, dword ptr [0x9ef208] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445732: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445733: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445734: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 445735: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44573fu; native_call(m, 0x41f0e0u);	/* 44573a: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9f16acu));	/* 44573f: mov ecx, dword ptr [0x9f16ac] */
	m->edx = M32((DWORD)(0x9f16a8u));	/* 445745: mov edx, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->ecx, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44574b: add ecx, 0xa */
	{ DWORD v_ = 0x75e024u; m->esp -= 4; M32(m->esp) = v_; }	/* 44574e: push 0x75e024 */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 445753: add edx, 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445756: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445757: push edx */
	m->esp -= 4; M32(m->esp) = 0x44575du; native_call(m, 0x4028b0u);	/* 445758: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44575d: add esp, 0x48 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445760: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445765: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44576a: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44576f: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 445771: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44577bu; native_call(m, 0x41f0e0u);	/* 445776: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f16b4u));	/* 44577b: mov eax, dword ptr [0x9f16b4] */
	m->ecx = M32((DWORD)(0x9f16b0u));	/* 445780: mov ecx, dword ptr [0x9f16b0] */
	m->edx = M32((DWORD)(0x9f16acu));	/* 445786: mov edx, dword ptr [0x9f16ac] */
	{ DWORD a_ = m->eax, b_ = 0xfffffff8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44578c: add eax, -8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44578f: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445791: push eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 445792: mov eax, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445797: add ecx, -8 */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44579a: add edx, 0x20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44579d: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44579e: add eax, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4457a1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4457a2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4457a8u; native_call(m, 0x427970u);	/* 4457a3: call 0x427970 */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 4457a8: mov ecx, dword ptr [0x9f16b4] */
	m->edx = M32((DWORD)(0x9f16b0u));	/* 4457ae: mov edx, dword ptr [0x9f16b0] */
	{ DWORD a_ = m->edx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4457b4: add edx, -0x18 */
	m->eax = (DWORD)(m->ecx + 0xffffffc0u);	/* 4457b7: lea eax, [ecx - 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4457ba: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4457bb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4457bc: push eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 4457bd: mov eax, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4457c2: add eax, 0x18 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4457c5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4457cbu; native_call(m, 0x427a40u);	/* 4457c6: call 0x427a40 */
	m->ecx = M32((DWORD)(0x9ef214u));	/* 4457cb: mov ecx, dword ptr [0x9ef214] */
	m->edx = M32((DWORD)(0x9ef210u));	/* 4457d1: mov edx, dword ptr [0x9ef210] */
	m->eax = M32((DWORD)(0x9ef20cu));	/* 4457d7: mov eax, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4457dc: push ecx */
	m->ecx = M32((DWORD)(0x9ef208u));	/* 4457dd: mov ecx, dword ptr [0x9ef208] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4457e3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4457e4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4457e5: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4457e6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4457f0u; native_call(m, 0x41f0e0u);	/* 4457eb: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4457f0: add esp, 0x4c */
	m->esp -= 4; M32(m->esp) = 0x4457f8u; native_call(m, 0x445520u);	/* 4457f3: call 0x445520 */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 4457f8: mov ebp, dword ptr [0x4a9228] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4457fe: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 445800: xor esi, esi */
	m->edi = 0x75e2a4u;	/* 445802: mov edi, 0x75e2a4 */
L_445807:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 445807: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x445812u; native_call(m, M32(0x4a9224u));	/* 44580c: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 445812: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 445817: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 445819: and edx, 0x800001ff */
	if (!m->sf) goto L_445829;	/* 44581f: jns 0x445829 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 445821: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 445822: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 445828: inc edx */
L_445829:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445829: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 44582a: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 445830: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 445831: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445837: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 445839: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 44583c: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x445845u; native_call(m, 0x4566c0u);	/* 445840: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445845: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44584a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44584f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445854: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44585bu; native_call(m, m->ebp);	/* 445859: call ebp */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 44585b: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44585f: cmp eax, ebx */
	m->eax = M32((DWORD)(0x9f16b0u));	/* 445861: mov eax, dword ptr [0x9f16b0] */
	if (!m->zf) goto L_4458a9;	/* 445866: jne 0x4458a9 */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 445868: mov ecx, dword ptr [0x9f16b4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44586e: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 445870: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445873: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445876: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xffffff4cu);	/* 445877: lea edx, [esi + eax - 0xb4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44587e: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0xfffffed4u);	/* 44587f: lea eax, [esi + eax - 0x12c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445886: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445887: push eax */
	m->esp -= 4; M32(m->esp) = 0x44588du; native_call(m, 0x4282f0u);	/* 445888: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9ef214u));	/* 44588d: mov ecx, dword ptr [0x9ef214] */
	m->edx = M32((DWORD)(0x9ef210u));	/* 445893: mov edx, dword ptr [0x9ef210] */
	m->eax = M32((DWORD)(0x9ef20cu));	/* 445899: mov eax, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44589e: push ecx */
	m->ecx = M32((DWORD)(0x9ef208u));	/* 44589f: mov ecx, dword ptr [0x9ef208] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4458a5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4458a6: push eax */
	goto L_4458e8;	/* 4458a7: jmp 0x4458e8 */
L_4458a9:
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 4458a9: mov ecx, dword ptr [0x9f16b4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4458af: push 0 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 4458b1: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4458b4: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4458b7: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xffffff4cu);	/* 4458b8: lea edx, [esi + eax - 0xb4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4458bf: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0xfffffed4u);	/* 4458c0: lea eax, [esi + eax - 0x12c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4458c7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4458c8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4458ceu; native_call(m, 0x4282f0u);	/* 4458c9: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9eead4u));	/* 4458ce: mov ecx, dword ptr [0x9eead4] */
	m->edx = M32((DWORD)(0x9eead0u));	/* 4458d4: mov edx, dword ptr [0x9eead0] */
	m->eax = M32((DWORD)(0x9eeaccu));	/* 4458da: mov eax, dword ptr [0x9eeacc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4458df: push ecx */
	m->ecx = M32((DWORD)(0x9eeac8u));	/* 4458e0: mov ecx, dword ptr [0x9eeac8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4458e6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4458e7: push eax */
L_4458e8:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4458e8: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4458e9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4458f3u; native_call(m, 0x41f0e0u);	/* 4458ee: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f16b0u));	/* 4458f3: mov eax, dword ptr [0x9f16b0] */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 4458f8: mov ecx, dword ptr [0x9f16b4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4458fe: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445901: add ecx, -0x28 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xffffff4cu);	/* 445904: lea edx, [esi + eax - 0xb4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44590b: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44590c: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xfffffed4u);	/* 44590d: lea edx, [esi + eax - 0x12c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445914: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445915: push edx */
	m->esp -= 4; M32(m->esp) = 0x44591bu; native_call(m, 0x4029d0u);	/* 445916: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44591b: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44591e: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 445924: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 445925: add esi, 0x8c */
	{ DWORD a_ = m->edi, b_ = 0x75e3a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44592b: cmp edi, 0x75e3a4 */
	if (m->sf != m->of) goto L_445807;	/* 445931: jl 0x445807 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 445937: xor esi, esi */
L_445939:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 445939: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x445944u; native_call(m, M32(0x4a9224u));	/* 44593e: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 445944: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 445949: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44594b: and ecx, 0x800001ff */
	if (!m->sf) goto L_44595b;	/* 445951: jns 0x44595b */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 445953: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 445954: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44595a: inc ecx */
L_44595b:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44595b: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44595c: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445962: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445963: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 445965: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44596b: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44596e: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x445977u; native_call(m, 0x4566c0u);	/* 445972: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445977: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44597c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445981: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445986: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44598du; native_call(m, m->ebp);	/* 44598b: call ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44598d: test esi, esi */
	if (!m->zf) goto L_445a49;	/* 44598f: jne 0x445a49 */
	m->eax = M32((DWORD)(0x4d7348u));	/* 445995: mov eax, dword ptr [0x4d7348] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44599a: test eax, eax */
	if (m->zf) goto L_445a0e;	/* 44599c: je 0x445a0e */
	{ DWORD a_ = M32((DWORD)(m->esp + 0x10u)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44599e: cmp dword ptr [esp + 0x10], 2 */
	if (!m->zf) goto L_4459e9;	/* 4459a3: jne 0x4459e9 */
	m->eax = M32((DWORD)(0x9f16b4u));	/* 4459a5: mov eax, dword ptr [0x9f16b4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4459aa: push 1 */
	m->ecx = (DWORD)(m->eax + 0xfffffff0u);	/* 4459ac: lea ecx, [eax - 0x10] */
	{ DWORD a_ = m->eax, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4459af: add eax, -0x30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4459b2: push ecx */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 4459b3: mov ecx, dword ptr [0x9f16a8] */
	m->edx = (DWORD)(m->ecx + 0xa8u);	/* 4459b9: lea edx, [ecx + 0xa8] */
	{ DWORD a_ = m->ecx, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4459bf: add ecx, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4459c2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4459c3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4459c4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4459cau; native_call(m, 0x4282f0u);	/* 4459c5: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9ef214u));	/* 4459ca: mov eax, dword ptr [0x9ef214] */
	m->ecx = M32((DWORD)(0x9ef210u));	/* 4459cf: mov ecx, dword ptr [0x9ef210] */
	m->edx = M32((DWORD)(0x9ef20cu));	/* 4459d5: mov edx, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4459db: push eax */
	m->eax = M32((DWORD)(0x9ef208u));	/* 4459dc: mov eax, dword ptr [0x9ef208] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4459e1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4459e2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4459e3: push eax */
	goto L_445b5c;	/* 4459e4: jmp 0x445b5c */
L_4459e9:
	m->eax = M32((DWORD)(0x9f16b4u));	/* 4459e9: mov eax, dword ptr [0x9f16b4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4459ee: push 0 */
	m->ecx = (DWORD)(m->eax + 0xfffffff0u);	/* 4459f0: lea ecx, [eax - 0x10] */
	{ DWORD a_ = m->eax, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4459f3: add eax, -0x30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4459f6: push ecx */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 4459f7: mov ecx, dword ptr [0x9f16a8] */
	m->edx = (DWORD)(m->ecx + 0xa8u);	/* 4459fd: lea edx, [ecx + 0xa8] */
	{ DWORD a_ = m->ecx, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445a03: add ecx, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445a06: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445a07: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445a08: push ecx */
	goto L_445adc;	/* 445a09: jmp 0x445adc */
L_445a0e:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445a0e: push 0x3f800000 */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445a13: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445a18: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445a1d: push 0x3f19999a */
	m->esp -= 4; M32(m->esp) = 0x445a24u; native_call(m, m->ebp);	/* 445a22: call ebp */
	m->eax = M32((DWORD)(0x9f16b4u));	/* 445a24: mov eax, dword ptr [0x9f16b4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 445a29: push 0 */
	m->ecx = (DWORD)(m->eax + 0xfffffff0u);	/* 445a2b: lea ecx, [eax - 0x10] */
	{ DWORD a_ = m->eax, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445a2e: add eax, -0x30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445a31: push ecx */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 445a32: mov ecx, dword ptr [0x9f16a8] */
	m->edx = (DWORD)(m->ecx + 0xa8u);	/* 445a38: lea edx, [ecx + 0xa8] */
	{ DWORD a_ = m->ecx, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445a3e: add ecx, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445a41: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445a42: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445a43: push ecx */
	goto L_445b43;	/* 445a44: jmp 0x445b43 */
L_445a49:
	m->eax = M32((DWORD)(0x9f1060u));	/* 445a49: mov eax, dword ptr [0x9f1060] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445a4e: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_445afd;	/* 445a50: jle 0x445afd */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 445a56: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445a5a: cmp eax, 3 */
	m->eax = (DWORD)(m->esi*8 + 0x0u);	/* 445a5d: lea eax, [esi*8] */
	if (!m->zf) goto L_445ab3;	/* 445a64: jne 0x445ab3 */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 445a66: mov ecx, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445a6c: sub eax, esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 445a6e: push 1 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 445a70: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 445a73: lea eax, [ecx + eax*4] */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 445a76: mov ecx, dword ptr [0x9f16b4] */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 445a7c: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445a7f: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445a82: push edx */
	m->edx = (DWORD)(m->eax + 0xa8u);	/* 445a83: lea edx, [eax + 0xa8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445a89: push edx */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445a8a: add eax, 0x30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445a8d: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445a8e: push eax */
	m->esp -= 4; M32(m->esp) = 0x445a94u; native_call(m, 0x4282f0u);	/* 445a8f: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9ef214u));	/* 445a94: mov eax, dword ptr [0x9ef214] */
	m->ecx = M32((DWORD)(0x9ef210u));	/* 445a99: mov ecx, dword ptr [0x9ef210] */
	m->edx = M32((DWORD)(0x9ef20cu));	/* 445a9f: mov edx, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445aa5: push eax */
	m->eax = M32((DWORD)(0x9ef208u));	/* 445aa6: mov eax, dword ptr [0x9ef208] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445aab: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445aac: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445aad: push eax */
	goto L_445b5c;	/* 445aae: jmp 0x445b5c */
L_445ab3:
	m->edx = M32((DWORD)(0x9f16a8u));	/* 445ab3: mov edx, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445ab9: sub eax, esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 445abb: push 0 */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 445abd: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 445ac0: lea eax, [edx + ecx*4] */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 445ac3: mov ecx, dword ptr [0x9f16b4] */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 445ac9: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445acc: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445acf: push edx */
	m->edx = (DWORD)(m->eax + 0xa8u);	/* 445ad0: lea edx, [eax + 0xa8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445ad6: push edx */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445ad7: add eax, 0x30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445ada: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445adb: push eax */
L_445adc:
	m->esp -= 4; M32(m->esp) = 0x445ae1u; native_call(m, 0x4282f0u);	/* 445adc: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9eead4u));	/* 445ae1: mov eax, dword ptr [0x9eead4] */
	m->ecx = M32((DWORD)(0x9eead0u));	/* 445ae6: mov ecx, dword ptr [0x9eead0] */
	m->edx = M32((DWORD)(0x9eeaccu));	/* 445aec: mov edx, dword ptr [0x9eeacc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445af2: push eax */
	m->eax = M32((DWORD)(0x9eeac8u));	/* 445af3: mov eax, dword ptr [0x9eeac8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445af8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445af9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445afa: push eax */
	goto L_445b5c;	/* 445afb: jmp 0x445b5c */
L_445afd:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445afd: push 0x3f800000 */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445b02: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445b07: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445b0c: push 0x3f19999a */
	m->esp -= 4; M32(m->esp) = 0x445b13u; native_call(m, m->ebp);	/* 445b11: call ebp */
	m->edx = M32((DWORD)(0x9f16a8u));	/* 445b13: mov edx, dword ptr [0x9f16a8] */
	m->eax = (DWORD)(m->esi*8 + 0x0u);	/* 445b19: lea eax, [esi*8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445b20: sub eax, esi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 445b22: push 0 */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 445b24: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 445b27: lea eax, [edx + ecx*4] */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 445b2a: mov ecx, dword ptr [0x9f16b4] */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 445b30: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445b33: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445b36: push edx */
	m->edx = (DWORD)(m->eax + 0xa8u);	/* 445b37: lea edx, [eax + 0xa8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445b3d: push edx */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445b3e: add eax, 0x30 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445b41: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445b42: push eax */
L_445b43:
	m->esp -= 4; M32(m->esp) = 0x445b48u; native_call(m, 0x4282f0u);	/* 445b43: call 0x4282f0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445b48: push 0x3f800000 */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445b4d: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445b52: push 0x3f19999a */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445b57: push 0x3f19999a */
L_445b5c:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 445b5c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x445b66u; native_call(m, 0x41f0e0u);	/* 445b61: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 445b66: mov ecx, dword ptr [0x9f16a8] */
	m->eax = (DWORD)(m->esi*8 + 0x0u);	/* 445b6c: lea eax, [esi*8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445b73: sub eax, esi */
	m->edx = m->esi;	/* 445b75: mov edx, esi */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 445b77: shl edx, 7 */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 445b7a: lea eax, [eax + eax*4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445b7d: add esp, 0x28 */
	{ DWORD a_ = m->edx, b_ = 0x75e3a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 445b80: add edx, 0x75e3a4 */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 445b86: lea eax, [ecx + eax*4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445b89: push edx */
	m->edx = M32((DWORD)(0x9f16b4u));	/* 445b8a: mov edx, dword ptr [0x9f16b4] */
	m->ecx = (DWORD)(m->eax + 0xa8u);	/* 445b90: lea ecx, [eax + 0xa8] */
	{ DWORD a_ = m->edx, b_ = 0xffffffd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 445b96: add edx, -0x28 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445b99: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445b9a: add eax, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445b9d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445b9e: push eax */
	m->esp -= 4; M32(m->esp) = 0x445ba4u; native_call(m, 0x4029d0u);	/* 445b9f: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445ba4: add esp, 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 445ba7: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445ba8: cmp esi, 2 */
	if (m->sf != m->of) goto L_445939;	/* 445bab: jl 0x445939 */
	m->edi = M32(m->esp); m->esp += 4;	/* 445bb1: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 445bb2: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 445bb3: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 445bb4: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 445bb5: pop ecx */
	m->esp += 4 + 0; return;	/* 445bb6: ret  */
}

/* skirmish_drawScreenA (0x444f40), lifted by tools/lift.py */
static void lift_444f40(X86 *m)
{
	m->eax = M32((DWORD)(0x4ded6cu));	/* 444f40: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 444f45: mov ecx, dword ptr [0x4ded68] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 444f4b: sub esp, 0xc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 444f4e: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 444f4f: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 444f50: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 444f51: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444f52: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444f53: push ecx */
	m->esp -= 4; M32(m->esp) = 0x444f59u; native_call(m, 0x4438d0u);	/* 444f54: call 0x4438d0 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 444f59: push 2 */
	m->ebp = m->eax;	/* 444f5b: mov ebp, eax */
	m->esp -= 4; M32(m->esp) = 0x444f62u; native_call(m, 0x41ef90u);	/* 444f5d: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 444f62: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x444f6bu; native_call(m, M32(0x4a9218u));	/* 444f65: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444f6b: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444f70: push 0x3f000000 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 444f75: push 0x3e4ccccd */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 444f7a: push 0x3dcccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 444f7f: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x444f89u; native_call(m, 0x41f0e0u);	/* 444f84: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9f16b4u));	/* 444f89: mov edx, dword ptr [0x9f16b4] */
	m->eax = M32((DWORD)(0x9f16b0u));	/* 444f8f: mov eax, dword ptr [0x9f16b0] */
	m->ecx = M32((DWORD)(0x9f16acu));	/* 444f94: mov ecx, dword ptr [0x9f16ac] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 444f9a: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444f9c: push edx */
	m->edx = M32((DWORD)(0x9f16a8u));	/* 444f9d: mov edx, dword ptr [0x9f16a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444fa3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444fa4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444fa5: push edx */
	m->esp -= 4; M32(m->esp) = 0x444fabu; native_call(m, 0x427970u);	/* 444fa6: call 0x427970 */
	m->eax = M32((DWORD)(0x9ef214u));	/* 444fab: mov eax, dword ptr [0x9ef214] */
	m->ecx = M32((DWORD)(0x9ef210u));	/* 444fb0: mov ecx, dword ptr [0x9ef210] */
	m->edx = M32((DWORD)(0x9ef20cu));	/* 444fb6: mov edx, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444fbc: push eax */
	m->eax = M32((DWORD)(0x9ef208u));	/* 444fbd: mov eax, dword ptr [0x9ef208] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444fc2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444fc3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 444fc4: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 444fc5: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x444fcfu; native_call(m, 0x41f0e0u);	/* 444fca: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9f16acu));	/* 444fcf: mov ecx, dword ptr [0x9f16ac] */
	m->edx = M32((DWORD)(0x9f16a8u));	/* 444fd5: mov edx, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->ecx, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 444fdb: add ecx, 0xa */
	{ DWORD v_ = 0x75dda4u; m->esp -= 4; M32(m->esp) = v_; }	/* 444fde: push 0x75dda4 */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 444fe3: add edx, 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 444fe6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 444fe7: push edx */
	m->esp -= 4; M32(m->esp) = 0x444fedu; native_call(m, 0x4028b0u);	/* 444fe8: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 444fed: add esp, 0x48 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ff0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ff5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 444ffa: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 444fff: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 445001: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44500bu; native_call(m, 0x41f0e0u);	/* 445006: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f16b4u));	/* 44500b: mov eax, dword ptr [0x9f16b4] */
	m->ecx = M32((DWORD)(0x9f16b0u));	/* 445010: mov ecx, dword ptr [0x9f16b0] */
	m->edx = M32((DWORD)(0x9f16acu));	/* 445016: mov edx, dword ptr [0x9f16ac] */
	{ DWORD a_ = m->eax, b_ = 0xfffffff8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44501c: add eax, -8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44501f: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445021: push eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 445022: mov eax, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445027: add ecx, -8 */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44502a: add edx, 0x20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44502d: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44502e: add eax, 8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445031: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445032: push eax */
	m->esp -= 4; M32(m->esp) = 0x445038u; native_call(m, 0x427970u);	/* 445033: call 0x427970 */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 445038: mov ecx, dword ptr [0x9f16b4] */
	m->edx = M32((DWORD)(0x9f16b0u));	/* 44503e: mov edx, dword ptr [0x9f16b0] */
	{ DWORD a_ = m->edx, b_ = 0xffffffe8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 445044: add edx, -0x18 */
	m->eax = (DWORD)(m->ecx + 0xffffff60u);	/* 445047: lea eax, [ecx - 0xa0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44504d: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44504e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44504f: push eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 445050: mov eax, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445055: add eax, 0x18 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445058: push eax */
	m->esp -= 4; M32(m->esp) = 0x44505eu; native_call(m, 0x427a40u);	/* 445059: call 0x427a40 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44505e: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 445063: push 0x3f19999a */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 445068: push 0x3e4ccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44506d: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44506f: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x445079u; native_call(m, 0x41f0e0u);	/* 445074: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f16acu));	/* 445079: mov eax, dword ptr [0x9f16ac] */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44507e: add esp, 0x4c */
	m->ecx = (DWORD)(m->eax + 0x3cu);	/* 445081: lea ecx, [eax + 0x3c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 445084: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445086: push ecx */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 445087: mov ecx, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44508d: add eax, 0x24 */
	m->edx = (DWORD)(m->ecx + 0x154u);	/* 445090: lea edx, [ecx + 0x154] */
	{ DWORD a_ = m->ecx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445096: add ecx, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445099: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44509a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44509b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4450a1u; native_call(m, 0x427970u);	/* 44509c: call 0x427970 */
	m->eax = M32((DWORD)(0x9f16acu));	/* 4450a1: mov eax, dword ptr [0x9f16ac] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4450a6: push 1 */
	m->ecx = (DWORD)(m->eax + 0x3cu);	/* 4450a8: lea ecx, [eax + 0x3c] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4450ab: add eax, 0x24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4450ae: push ecx */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 4450af: mov ecx, dword ptr [0x9f16a8] */
	m->edx = (DWORD)(m->ecx + 0x1aeu);	/* 4450b5: lea edx, [ecx + 0x1ae] */
	{ DWORD a_ = m->ecx, b_ = 0x159u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4450bb: add ecx, 0x159 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4450c1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4450c2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4450c3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4450c9u; native_call(m, 0x427970u);	/* 4450c4: call 0x427970 */
	m->eax = M32((DWORD)(0x9f16acu));	/* 4450c9: mov eax, dword ptr [0x9f16ac] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4450ce: push 1 */
	m->ecx = (DWORD)(m->eax + 0x3cu);	/* 4450d0: lea ecx, [eax + 0x3c] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4450d3: add eax, 0x24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4450d6: push ecx */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 4450d7: mov ecx, dword ptr [0x9f16a8] */
	m->edx = (DWORD)(m->ecx + 0x208u);	/* 4450dd: lea edx, [ecx + 0x208] */
	{ DWORD a_ = m->ecx, b_ = 0x1b3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4450e3: add ecx, 0x1b3 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4450e9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4450ea: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4450eb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4450f1u; native_call(m, 0x427970u);	/* 4450ec: call 0x427970 */
	m->eax = M32((DWORD)(0x9f16acu));	/* 4450f1: mov eax, dword ptr [0x9f16ac] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4450f6: push 1 */
	m->ecx = (DWORD)(m->eax + 0x3cu);	/* 4450f8: lea ecx, [eax + 0x3c] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4450fb: add eax, 0x24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4450fe: push ecx */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 4450ff: mov ecx, dword ptr [0x9f16a8] */
	m->edx = (DWORD)(m->ecx + 0x25du);	/* 445105: lea edx, [ecx + 0x25d] */
	{ DWORD a_ = m->ecx, b_ = 0x20du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44510b: add ecx, 0x20d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445111: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445112: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445113: push ecx */
	m->esp -= 4; M32(m->esp) = 0x445119u; native_call(m, 0x427970u);	/* 445114: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445119: add esp, 0x50 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44511c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445121: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445126: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44512b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 445130: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44513au; native_call(m, 0x41f0e0u);	/* 445135: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f16acu));	/* 44513a: mov eax, dword ptr [0x9f16ac] */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 44513f: mov ecx, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->eax, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445145: add eax, 0x28 */
	{ DWORD v_ = 0x75de24u; m->esp -= 4; M32(m->esp) = v_; }	/* 445148: push 0x75de24 */
	{ DWORD a_ = m->ecx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44514d: add ecx, 0x18 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445150: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445151: push ecx */
	m->esp -= 4; M32(m->esp) = 0x445157u; native_call(m, 0x402620u);	/* 445152: call 0x402620 */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 445157: mov eax, dword ptr [0x9f16a8] */
	m->ecx = M32((DWORD)(0x9f16acu));	/* 44515c: mov ecx, dword ptr [0x9f16ac] */
	{ DWORD v_ = 0x75dea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 445162: push 0x75dea4 */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445167: add ecx, 0x28 */
	m->edx = (DWORD)(m->eax + 0x1aeu);	/* 44516a: lea edx, [eax + 0x1ae] */
	{ DWORD a_ = m->eax, b_ = 0x159u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445170: add eax, 0x159 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445175: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445176: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445177: push eax */
	m->esp -= 4; M32(m->esp) = 0x44517du; native_call(m, 0x402740u);	/* 445178: call 0x402740 */
	{ DWORD v_ = 0x75df24u; m->esp -= 4; M32(m->esp) = v_; }	/* 44517d: push 0x75df24 */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 445182: mov eax, dword ptr [0x9f16a8] */
	m->ecx = M32((DWORD)(0x9f16acu));	/* 445187: mov ecx, dword ptr [0x9f16ac] */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44518d: add ecx, 0x28 */
	m->edx = (DWORD)(m->eax + 0x208u);	/* 445190: lea edx, [eax + 0x208] */
	{ DWORD a_ = m->eax, b_ = 0x1b3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445196: add eax, 0x1b3 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44519b: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44519c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44519d: push eax */
	m->esp -= 4; M32(m->esp) = 0x4451a3u; native_call(m, 0x402740u);	/* 44519e: call 0x402740 */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 4451a3: mov eax, dword ptr [0x9f16a8] */
	m->ecx = M32((DWORD)(0x9f16acu));	/* 4451a8: mov ecx, dword ptr [0x9f16ac] */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4451ae: add esp, 0x40 */
	{ DWORD a_ = m->ecx, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4451b1: add ecx, 0x28 */
	m->edx = (DWORD)(m->eax + 0x25du);	/* 4451b4: lea edx, [eax + 0x25d] */
	{ DWORD a_ = m->eax, b_ = 0x20du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4451ba: add eax, 0x20d */
	{ DWORD v_ = 0x75dfa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4451bf: push 0x75dfa4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4451c4: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4451c5: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4451c6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4451ccu; native_call(m, 0x402740u);	/* 4451c7: call 0x402740 */
	m->edx = M32((DWORD)(0x9f16b4u));	/* 4451cc: mov edx, dword ptr [0x9f16b4] */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 4451d2: mov eax, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->edx, b_ = 0xffffff62u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4451d7: add edx, 0xffffff62 */
	{ DWORD v_ = 0x75e024u; m->esp -= 4; M32(m->esp) = v_; }	/* 4451dd: push 0x75e024 */
	{ DWORD a_ = m->eax, b_ = 0xf0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4451e2: add eax, 0xf0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4451e7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4451e8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4451eeu; native_call(m, 0x402620u);	/* 4451e9: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4451ee: add esp, 0x1c */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4451f1: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4451f3: xor esi, esi */
L_4451f5:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(0x9ef2c0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4451f5: cmp edi, dword ptr [0x9ef2c0] */
	if (m->sf == m->of) goto L_445360;	/* 4451fb: jge 0x445360 */
	m->ecx = M32((DWORD)(0x9f16bcu));	/* 445201: mov ecx, dword ptr [0x9f16bc] */
	m->eax = M32((DWORD)(0x9f16a4u));	/* 445207: mov eax, dword ptr [0x9f16a4] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44520c: add ecx, edi */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44520e: cmp eax, ecx */
	if (!m->zf) goto L_44522f;	/* 445210: jne 0x44522f */
	m->edx = M32((DWORD)(0x9ef214u));	/* 445212: mov edx, dword ptr [0x9ef214] */
	m->eax = M32((DWORD)(0x9ef210u));	/* 445218: mov eax, dword ptr [0x9ef210] */
	m->ecx = M32((DWORD)(0x9ef20cu));	/* 44521d: mov ecx, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445223: push edx */
	m->edx = M32((DWORD)(0x9ef208u));	/* 445224: mov edx, dword ptr [0x9ef208] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44522a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44522b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44522c: push edx */
	goto L_445249;	/* 44522d: jmp 0x445249 */
L_44522f:
	m->eax = M32((DWORD)(0x9eead4u));	/* 44522f: mov eax, dword ptr [0x9eead4] */
	m->ecx = M32((DWORD)(0x9eead0u));	/* 445234: mov ecx, dword ptr [0x9eead0] */
	m->edx = M32((DWORD)(0x9eeaccu));	/* 44523a: mov edx, dword ptr [0x9eeacc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445240: push eax */
	m->eax = M32((DWORD)(0x9eeac8u));	/* 445241: mov eax, dword ptr [0x9eeac8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445246: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445247: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445248: push eax */
L_445249:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 445249: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x445253u; native_call(m, 0x41f0e0u);	/* 44524e: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9f16bcu));	/* 445253: mov ecx, dword ptr [0x9f16bc] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445259: add esp, 0x14 */
	m->eax = (DWORD)(m->ecx + m->edi*1 + 0x0u);	/* 44525c: lea eax, [ecx + edi] */
	m->ecx = M32((DWORD)(0x9f16acu));	/* 44525f: mov ecx, dword ptr [0x9f16ac] */
	m->edx = m->eax;	/* 445265: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 445267: shl edx, 6 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44526a: sub edx, eax */
	m->eax = (DWORD)(m->edx*4 + 0x9ef2d4u);	/* 44526c: lea eax, [edx*4 + 0x9ef2d4] */
	m->edx = (DWORD)(m->esi + m->ecx*1 + 0x48u);	/* 445273: lea edx, [esi + ecx + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445277: push eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 445278: mov eax, dword ptr [0x9f16a8] */
	{ DWORD a_ = m->eax, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44527d: add eax, 0x18 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445280: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445281: push eax */
	m->esp -= 4; M32(m->esp) = 0x445287u; native_call(m, 0x402620u);	/* 445282: call 0x402620 */
	m->ecx = M32((DWORD)(0x9f16bcu));	/* 445287: mov ecx, dword ptr [0x9f16bc] */
	m->eax = (DWORD)(m->ecx + m->edi*1 + 0x0u);	/* 44528d: lea eax, [ecx + edi] */
	m->edx = m->eax;	/* 445290: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 445292: shl edx, 6 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 445295: sub edx, eax */
	m->eax = (DWORD)(m->edx*4 + 0x9ef314u);	/* 445297: lea eax, [edx*4 + 0x9ef314] */
	m->edx = M32((DWORD)(0x9f16acu));	/* 44529e: mov edx, dword ptr [0x9f16ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4452a4: push eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 4452a5: mov eax, dword ptr [0x9f16a8] */
	m->ecx = (DWORD)(m->eax + 0x1aeu);	/* 4452aa: lea ecx, [eax + 0x1ae] */
	{ DWORD a_ = m->eax, b_ = 0x159u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4452b0: add eax, 0x159 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4452b5: push ecx */
	m->ecx = (DWORD)(m->esi + m->edx*1 + 0x48u);	/* 4452b6: lea ecx, [esi + edx + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4452ba: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4452bb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4452c1u; native_call(m, 0x402740u);	/* 4452bc: call 0x402740 */
	m->eax = M32((DWORD)(0x9f16bcu));	/* 4452c1: mov eax, dword ptr [0x9f16bc] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 4452c6: lea edx, [esp + 0x2c] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4452ca: add eax, edi */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 4452cc: push 0xa */
	m->ecx = m->eax;	/* 4452ce: mov ecx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4452d0: push edx */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4452d1: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4452d4: sub ecx, eax */
	m->edx = M32((DWORD)(m->ecx*4 + 0x9ef3b4u));	/* 4452d6: mov edx, dword ptr [ecx*4 + 0x9ef3b4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4452dd: push edx */
	m->esp -= 4; M32(m->esp) = 0x4452e3u; native_call(m, 0x49fb53u);	/* 4452de: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9f16acu));	/* 4452e3: mov edx, dword ptr [0x9f16ac] */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 4452e9: lea eax, [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4452ed: push eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 4452ee: mov eax, dword ptr [0x9f16a8] */
	m->ecx = (DWORD)(m->eax + 0x208u);	/* 4452f3: lea ecx, [eax + 0x208] */
	{ DWORD a_ = m->eax, b_ = 0x1b3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4452f9: add eax, 0x1b3 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4452fe: push ecx */
	m->ecx = (DWORD)(m->esi + m->edx*1 + 0x48u);	/* 4452ff: lea ecx, [esi + edx + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445303: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445304: push eax */
	m->esp -= 4; M32(m->esp) = 0x44530au; native_call(m, 0x402740u);	/* 445305: call 0x402740 */
	m->edx = M32((DWORD)(0x9f16bcu));	/* 44530a: mov edx, dword ptr [0x9f16bc] */
	m->eax = (DWORD)(m->edx + m->edi*1 + 0x0u);	/* 445310: lea eax, [edx + edi] */
	m->ecx = m->eax;	/* 445313: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 445315: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445318: sub ecx, eax */
	m->eax = M32((DWORD)(0x9f16a8u));	/* 44531a: mov eax, dword ptr [0x9f16a8] */
	m->edx = M32((DWORD)(m->ecx*4 + 0x9ef3bcu));	/* 44531f: mov edx, dword ptr [ecx*4 + 0x9ef3bc] */
	m->ecx = (DWORD)(m->eax + 0x25du);	/* 445326: lea ecx, [eax + 0x25d] */
	{ DWORD a_ = m->edx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 44532c: shl edx, 7 */
	{ DWORD a_ = m->edx, b_ = 0x75dda4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44532f: add edx, 0x75dda4 */
	{ DWORD a_ = m->eax, b_ = 0x20du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445335: add eax, 0x20d */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44533a: push edx */
	m->edx = M32((DWORD)(0x9f16acu));	/* 44533b: mov edx, dword ptr [0x9f16ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445341: push ecx */
	m->ecx = (DWORD)(m->esi + m->edx*1 + 0x48u);	/* 445342: lea ecx, [esi + edx + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445346: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445347: push eax */
	m->esp -= 4; M32(m->esp) = 0x44534du; native_call(m, 0x402740u);	/* 445348: call 0x402740 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44534d: add esp, 0x48 */
	{ DWORD a_ = m->esi, b_ = 0x1au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 445350: add esi, 0x1a */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 445353: inc edi */
	{ DWORD a_ = m->esi, b_ = 0xd0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445354: cmp esi, 0xd0 */
	if (m->sf != m->of) goto L_4451f5;	/* 44535a: jl 0x4451f5 */
L_445360:
	m->edx = M32((DWORD)(0x9f16b0u));	/* 445360: mov edx, dword ptr [0x9f16b0] */
	{ DWORD a_ = m->edx, b_ = 0xffffffc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 445366: add edx, -0x38 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445369: push edx */
	m->esp -= 4; M32(m->esp) = 0x44536fu; native_call(m, 0x4017b0u);	/* 44536a: call 0x4017b0 */
	m->eax = M32((DWORD)(0x9ef214u));	/* 44536f: mov eax, dword ptr [0x9ef214] */
	m->ecx = M32((DWORD)(0x9ef210u));	/* 445374: mov ecx, dword ptr [0x9ef210] */
	m->edx = M32((DWORD)(0x9ef20cu));	/* 44537a: mov edx, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445380: push eax */
	m->eax = M32((DWORD)(0x9ef208u));	/* 445381: mov eax, dword ptr [0x9ef208] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445386: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445387: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 445388: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 445389: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x445393u; native_call(m, 0x41f0e0u);	/* 44538e: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f16a4u));	/* 445393: mov eax, dword ptr [0x9f16a4] */
	m->ecx = m->eax;	/* 445398: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x6u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44539a: shl ecx, 6 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44539d: sub ecx, eax */
	m->eax = M32((DWORD)(0x9f16b4u));	/* 44539f: mov eax, dword ptr [0x9f16b4] */
	{ DWORD a_ = m->eax, b_ = 0xffffff74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4453a4: add eax, 0xffffff74 */
	m->edx = (DWORD)(m->ecx*4 + 0x9ef334u);	/* 4453a9: lea edx, [ecx*4 + 0x9ef334] */
	m->ecx = M32((DWORD)(0x9f16a8u));	/* 4453b0: mov ecx, dword ptr [0x9f16a8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4453b6: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xf0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4453b7: add ecx, 0xf0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4453bd: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4453be: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4453c4u; native_call(m, 0x402620u);	/* 4453bf: call 0x402620 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 4453c4: push 0x280 */
	m->esp -= 4; M32(m->esp) = 0x4453ceu; native_call(m, 0x4017b0u);	/* 4453c9: call 0x4017b0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4453ce: add esp, 0x28 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4453d1: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4453d3: xor esi, esi */
	m->edi = 0x75e0a4u;	/* 4453d5: mov edi, 0x75e0a4 */
L_4453da:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4453da: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4453e5u; native_call(m, M32(0x4a9224u));	/* 4453df: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 4453e5: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 4453ea: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4453ec: and edx, 0x800001ff */
	if (!m->sf) goto L_4453fc;	/* 4453f2: jns 0x4453fc */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 4453f4: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4453f5: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4453fb: inc edx */
L_4453fc:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4453fc: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4453fd: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 445403: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 445404: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44540a: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44540c: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 44540f: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x445418u; native_call(m, 0x4566c0u);	/* 445413: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445418: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44541d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445422: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 445427: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x445432u; native_call(m, M32(0x4a9228u));	/* 44542c: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x9f16b0u));	/* 445432: mov eax, dword ptr [0x9f16b0] */
	m->edx = (DWORD)(m->ebx + 0x8u);	/* 445437: lea edx, [ebx + 8] */
	{ DWORD a_ = m->ebp, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44543a: cmp ebp, edx */
	if (!m->zf) goto L_44547f;	/* 44543c: jne 0x44547f */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 44543e: mov ecx, dword ptr [0x9f16b4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 445444: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 445446: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 445449: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44544c: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xffffff4cu);	/* 44544d: lea edx, [esi + eax - 0xb4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445454: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0xfffffed4u);	/* 445455: lea eax, [esi + eax - 0x12c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44545c: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44545d: push eax */
	m->esp -= 4; M32(m->esp) = 0x445463u; native_call(m, 0x4282f0u);	/* 44545e: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9ef214u));	/* 445463: mov ecx, dword ptr [0x9ef214] */
	m->edx = M32((DWORD)(0x9ef210u));	/* 445469: mov edx, dword ptr [0x9ef210] */
	m->eax = M32((DWORD)(0x9ef20cu));	/* 44546f: mov eax, dword ptr [0x9ef20c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 445474: push ecx */
	m->ecx = M32((DWORD)(0x9ef208u));	/* 445475: mov ecx, dword ptr [0x9ef208] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44547b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44547c: push eax */
	goto L_4454be;	/* 44547d: jmp 0x4454be */
L_44547f:
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 44547f: mov ecx, dword ptr [0x9f16b4] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 445485: push 0 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 445487: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44548a: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44548d: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xffffff4cu);	/* 44548e: lea edx, [esi + eax - 0xb4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 445495: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0xfffffed4u);	/* 445496: lea eax, [esi + eax - 0x12c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44549d: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44549e: push eax */
	m->esp -= 4; M32(m->esp) = 0x4454a4u; native_call(m, 0x4282f0u);	/* 44549f: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9eead4u));	/* 4454a4: mov ecx, dword ptr [0x9eead4] */
	m->edx = M32((DWORD)(0x9eead0u));	/* 4454aa: mov edx, dword ptr [0x9eead0] */
	m->eax = M32((DWORD)(0x9eeaccu));	/* 4454b0: mov eax, dword ptr [0x9eeacc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4454b5: push ecx */
	m->ecx = M32((DWORD)(0x9eeac8u));	/* 4454b6: mov ecx, dword ptr [0x9eeac8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4454bc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4454bd: push eax */
L_4454be:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4454be: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4454bf: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4454c9u; native_call(m, 0x41f0e0u);	/* 4454c4: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f16b0u));	/* 4454c9: mov eax, dword ptr [0x9f16b0] */
	m->ecx = M32((DWORD)(0x9f16b4u));	/* 4454ce: mov ecx, dword ptr [0x9f16b4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4454d4: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4454d7: add ecx, -0x38 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xffffff4cu);	/* 4454da: lea edx, [esi + eax - 0xb4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4454e1: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4454e2: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xfffffed4u);	/* 4454e3: lea edx, [esi + eax - 0x12c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4454ea: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4454eb: push edx */
	m->esp -= 4; M32(m->esp) = 0x4454f1u; native_call(m, 0x4029d0u);	/* 4454ec: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4454f1: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4454f4: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4454fa: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4454fb: add esi, 0x8c */
	{ DWORD a_ = m->edi, b_ = 0x75e1a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445501: cmp edi, 0x75e1a4 */
	if (m->sf != m->of) goto L_4453da;	/* 445507: jl 0x4453da */
	m->edi = M32(m->esp); m->esp += 4;	/* 44550d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44550e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44550f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 445510: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 445511: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 445514: ret  */
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
