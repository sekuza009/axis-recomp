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

static void lift_425cd0(X86 *m);

/* setup_crosshairScreen (0x425cd0), lifted by tools/lift.py */
static void lift_425cd0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425cd0: push ecx */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 425cd1: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 425cd6: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 425cdc: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 425cdd: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 425cde: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 425cdf: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425ce0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425ce1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x425ce7u; native_call(m, 0x4206f0u);	/* 425ce2: call 0x4206f0 */
	m->edi = m->eax;	/* 425ce7: mov edi, eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 425ce9: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->edi;	/* 425ceb: mov dword ptr [esp + 0x1c], edi */
	m->esp -= 4; M32(m->esp) = 0x425cf4u; native_call(m, 0x41ef90u);	/* 425cef: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425cf4: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x425cfdu; native_call(m, M32(0x4a9218u));	/* 425cf7: call dword ptr [0x4a9218] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425cfd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d02: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d07: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d0c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x425d17u; native_call(m, M32(0x4a9228u));	/* 425d11: call dword ptr [0x4a9228] */
	m->edx = M32((DWORD)(0x4deb50u));	/* 425d17: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x4dde8cu));	/* 425d1d: mov eax, dword ptr [0x4dde8c] */
	m->ecx = M32((DWORD)(0x4dde88u));	/* 425d22: mov ecx, dword ptr [0x4dde88] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425d28: push edx */
	m->edx = M32((DWORD)(0x4dde84u));	/* 425d29: mov edx, dword ptr [0x4dde84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425d2f: push eax */
	m->eax = M32((DWORD)(0x4dde80u));	/* 425d30: mov eax, dword ptr [0x4dde80] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425d35: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425d36: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425d37: push eax */
	m->esp -= 4; M32(m->esp) = 0x425d3du; native_call(m, 0x427a90u);	/* 425d38: call 0x427a90 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d3d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d42: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d47: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d4c: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d4e: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x425d58u; native_call(m, 0x41f0e0u);	/* 425d53: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dde84u));	/* 425d58: mov ecx, dword ptr [0x4dde84] */
	m->edx = M32((DWORD)(0x4dde88u));	/* 425d5e: mov edx, dword ptr [0x4dde88] */
	{ DWORD a_ = m->edx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425d64: add edx, -0x20 */
	m->eax = (DWORD)(m->ecx + 0x30u);	/* 425d67: lea eax, [ecx + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425d6a: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425d6b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425d6c: push eax */
	m->eax = M32((DWORD)(0x4dde80u));	/* 425d6d: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425d72: add eax, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425d75: push eax */
	m->esp -= 4; M32(m->esp) = 0x425d7bu; native_call(m, 0x427a40u);	/* 425d76: call 0x427a40 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d7b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d80: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d85: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d8a: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425d8f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425d99u; native_call(m, 0x41f0e0u);	/* 425d94: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dde84u));	/* 425d99: mov ecx, dword ptr [0x4dde84] */
	m->edx = M32((DWORD)(0x4dde80u));	/* 425d9f: mov edx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425da5: add esp, 0x4c */
	{ DWORD a_ = m->ecx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425da8: add ecx, 0x3c */
	{ DWORD a_ = m->edx, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425dab: add edx, 0x30 */
	{ DWORD v_ = 0x754524u; m->esp -= 4; M32(m->esp) = v_; }	/* 425dae: push 0x754524 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425db3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425db4: push edx */
	m->esp -= 4; M32(m->esp) = 0x425dbau; native_call(m, 0x402620u);	/* 425db5: call 0x402620 */
	m->eax = M32((DWORD)(0x4dde84u));	/* 425dba: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 425dbf: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425dc5: add eax, 0x3c */
	{ DWORD v_ = 0x7545a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 425dc8: push 0x7545a4 */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425dcd: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425dd3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425dd4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x425ddau; native_call(m, 0x402620u);	/* 425dd5: call 0x402620 */
	m->edx = M32((DWORD)(0x4dde84u));	/* 425dda: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 425de0: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425de5: add edx, 0x3c */
	{ DWORD v_ = 0x754624u; m->esp -= 4; M32(m->esp) = v_; }	/* 425de8: push 0x754624 */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425ded: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425df2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425df3: push eax */
	m->esp -= 4; M32(m->esp) = 0x425df9u; native_call(m, 0x402620u);	/* 425df4: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425df9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425dfe: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425e03: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425e08: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 425e0a: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x425e14u; native_call(m, 0x41f0e0u);	/* 425e0f: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4dde84u));	/* 425e14: mov ecx, dword ptr [0x4dde84] */
	m->edx = M32((DWORD)(0x4dde88u));	/* 425e1a: mov edx, dword ptr [0x4dde88] */
	{ DWORD a_ = m->edx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425e20: add edx, -0x20 */
	m->eax = (DWORD)(m->ecx + 0x50u);	/* 425e23: lea eax, [ecx + 0x50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425e26: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425e27: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425e28: push eax */
	m->eax = M32((DWORD)(0x4dde80u));	/* 425e29: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425e2e: add eax, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425e31: push eax */
	m->esp -= 4; M32(m->esp) = 0x425e37u; native_call(m, 0x427a40u);	/* 425e32: call 0x427a40 */
	m->ecx = M32((DWORD)(0x4dde8cu));	/* 425e37: mov ecx, dword ptr [0x4dde8c] */
	m->edx = M32((DWORD)(0x4dde88u));	/* 425e3d: mov edx, dword ptr [0x4dde88] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425e43: add esp, 0x48 */
	{ DWORD a_ = m->edx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425e46: add edx, -0x20 */
	m->eax = (DWORD)(m->ecx + 0xffffffc8u);	/* 425e49: lea eax, [ecx - 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425e4c: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425e4d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425e4e: push eax */
	m->eax = M32((DWORD)(0x4dde80u));	/* 425e4f: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425e54: add eax, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425e57: push eax */
	m->esp -= 4; M32(m->esp) = 0x425e5du; native_call(m, 0x427a40u);	/* 425e58: call 0x427a40 */
	m->ecx = M32((DWORD)(0x4ddaecu));	/* 425e5d: mov ecx, dword ptr [0x4ddaec] */
	m->edx = M32((DWORD)(0x4ddae8u));	/* 425e63: mov edx, dword ptr [0x4ddae8] */
	m->eax = M32((DWORD)(0x4ddae4u));	/* 425e69: mov eax, dword ptr [0x4ddae4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425e6e: push ecx */
	m->ecx = M32((DWORD)(0x4ddae0u));	/* 425e6f: mov ecx, dword ptr [0x4ddae0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425e75: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425e76: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425e77: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425e78: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425e82u; native_call(m, 0x41f0e0u);	/* 425e7d: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425e82: add esp, 0x24 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 425e85: xor ebx, ebx */
	m->esi = 0x754324u;	/* 425e87: mov esi, 0x754324 */
L_425e8c:
	m->edx = M32((DWORD)(0x4dde84u));	/* 425e8c: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 425e92: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x12u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425e97: add edx, 0x12 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 425e9a: push esi */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0x46u);	/* 425e9b: lea ecx, [ebx + eax + 0x46] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425e9f: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425ea0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x425ea6u; native_call(m, 0x4028b0u);	/* 425ea1: call 0x4028b0 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 425ea6: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425eac: add esp, 0xc */
	{ DWORD a_ = m->ebx, b_ = 0x78u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 425eaf: add ebx, 0x78 */
	{ DWORD a_ = m->esi, b_ = 0x754524u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425eb2: cmp esi, 0x754524 */
	if (m->sf != m->of) goto L_425e8c;	/* 425eb8: jl 0x425e8c */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425eba: cmp edi, 6 */
	if (m->zf || m->sf != m->of) goto L_425f88;	/* 425ebd: jle 0x425f88 */
	{ DWORD a_ = m->edi, b_ = 0x12u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425ec3: cmp edi, 0x12 */
	if (m->sf == m->of) goto L_425f88;	/* 425ec6: jge 0x425f88 */
	m->eax = M32((DWORD)(0x4dddc8u));	/* 425ecc: mov eax, dword ptr [0x4dddc8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 425ed1: test eax, eax */
	if (!m->zf) goto L_425f91;	/* 425ed3: jne 0x425f91 */
	m->eax = M32((DWORD)(0x4ddce8u));	/* 425ed9: mov eax, dword ptr [0x4ddce8] */
	m->ecx = (DWORD)(m->edi + 0xfffffff9u);	/* 425ede: lea ecx, [edi - 7] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 425ee1: test eax, eax */
	M32((DWORD)(0x4de040u)) = m->ecx;	/* 425ee3: mov dword ptr [0x4de040], ecx */
	if (!m->zf) goto L_425ef0;	/* 425ee9: jne 0x425ef0 */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425eeb: cmp edi, 0x10 */
	goto L_425f1f;	/* 425eee: jmp 0x425f1f */
L_425ef0:
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425ef0: cmp eax, 2 */
	if (!m->zf) goto L_425f17;	/* 425ef3: jne 0x425f17 */
	{ DWORD a_ = m->edi, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425ef5: cmp edi, 0xf */
	if (m->zf || m->sf != m->of) goto L_425f03;	/* 425ef8: jle 0x425f03 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 425efa: or ecx, 0xffffffff */
	M32((DWORD)(0x4de040u)) = m->ecx;	/* 425efd: mov dword ptr [0x4de040], ecx */
L_425f03:
	{ DWORD a_ = m->edi, b_ = 0xbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425f03: cmp edi, 0xb */
	if (!m->zf) goto L_425f30;	/* 425f06: jne 0x425f30 */
	M32((DWORD)(0x4de040u)) = 0xffffffffu;	/* 425f08: mov dword ptr [0x4de040], 0xffffffff */
	goto L_425fe7;	/* 425f12: jmp 0x425fe7 */
L_425f17:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425f17: cmp eax, 3 */
	if (!m->zf) goto L_425f30;	/* 425f1a: jne 0x425f30 */
	{ DWORD a_ = m->edi, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425f1c: cmp edi, 8 */
L_425f1f:
	if (m->zf || m->sf != m->of) goto L_425f30;	/* 425f1f: jle 0x425f30 */
	M32((DWORD)(0x4de040u)) = 0xffffffffu;	/* 425f21: mov dword ptr [0x4de040], 0xffffffff */
	goto L_425fe7;	/* 425f2b: jmp 0x425fe7 */
L_425f30:
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 425f30: test ecx, ecx */
	if (m->sf != m->of) goto L_425fe7;	/* 425f32: jl 0x425fe7 */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 425f38: push 0x3e99999a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425f3d: push 0x3f800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425f42: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425f47: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 425f49: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x425f53u; native_call(m, 0x41f0e0u);	/* 425f4e: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4de040u));	/* 425f53: mov eax, dword ptr [0x4de040] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 425f58: push 1 */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 425f5a: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 425f5d: mov eax, dword ptr [0x4dde84] */
	m->eax = (DWORD)(m->eax + m->edx*8 + 0x0u);	/* 425f62: lea eax, [eax + edx*8] */
	m->edx = M32((DWORD)(0x4dde88u));	/* 425f65: mov edx, dword ptr [0x4dde88] */
	{ DWORD a_ = m->edx, b_ = 0xffffffdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425f6b: add edx, -0x24 */
	m->ecx = (DWORD)(m->eax + 0x6eu);	/* 425f6e: lea ecx, [eax + 0x6e] */
	{ DWORD a_ = m->eax, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425f71: add eax, 0x58 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425f74: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425f75: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425f76: push eax */
	m->eax = M32((DWORD)(0x4dde80u));	/* 425f77: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425f7c: add eax, 0x24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425f7f: push eax */
	m->esp -= 4; M32(m->esp) = 0x425f85u; native_call(m, 0x427970u);	/* 425f80: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425f85: add esp, 0x28 */
L_425f88:
	m->eax = M32((DWORD)(0x4dddc8u));	/* 425f88: mov eax, dword ptr [0x4dddc8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 425f8d: test eax, eax */
	if (m->zf) goto L_425fe2;	/* 425f8f: je 0x425fe2 */
L_425f91:
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 425f91: push 0x3e99999a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425f96: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425f9b: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425f9d: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 425fa2: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x425facu; native_call(m, 0x41f0e0u);	/* 425fa7: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4de040u));	/* 425fac: mov eax, dword ptr [0x4de040] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 425fb1: mov edx, dword ptr [0x4dde84] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 425fb7: push 1 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 425fb9: lea ecx, [eax + eax*2] */
	m->eax = (DWORD)(m->edx + m->ecx*8 + 0x0u);	/* 425fbc: lea eax, [edx + ecx*8] */
	m->edx = M32((DWORD)(0x4dde88u));	/* 425fbf: mov edx, dword ptr [0x4dde88] */
	{ DWORD a_ = m->edx, b_ = 0xffffffdcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425fc5: add edx, -0x24 */
	m->ecx = (DWORD)(m->eax + 0x6eu);	/* 425fc8: lea ecx, [eax + 0x6e] */
	{ DWORD a_ = m->eax, b_ = 0x58u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425fcb: add eax, 0x58 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425fce: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425fcf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425fd0: push eax */
	m->eax = M32((DWORD)(0x4dde80u));	/* 425fd1: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425fd6: add eax, 0x24 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425fd9: push eax */
	m->esp -= 4; M32(m->esp) = 0x425fdfu; native_call(m, 0x427970u);	/* 425fda: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425fdf: add esp, 0x28 */
L_425fe2:
	m->eax = M32((DWORD)(0x4ddce8u));	/* 425fe2: mov eax, dword ptr [0x4ddce8] */
L_425fe7:
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 425fe7: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_427577;	/* 425fea: ja 0x427577 */
	switch (m->eax) { case 0: goto L_425ff7; case 1: goto L_4264ba; case 2: goto L_4269ed; case 3: goto L_426f14; default: abort(); }	/* 425ff0: jmp dword ptr [eax*4 + 0x427784] */
L_425ff7:
	m->ecx = M32((DWORD)(0x4de054u));	/* 425ff7: mov ecx, dword ptr [0x4de054] */
	m->edx = M32((DWORD)(0x4de050u));	/* 425ffd: mov edx, dword ptr [0x4de050] */
	m->eax = M32((DWORD)(0x4de04cu));	/* 426003: mov eax, dword ptr [0x4de04c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426008: push ecx */
	m->ecx = M32((DWORD)(0x4de048u));	/* 426009: mov ecx, dword ptr [0x4de048] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42600f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426010: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426011: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 426012: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x42601cu; native_call(m, 0x41f0e0u);	/* 426017: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42601c: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426022: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x12u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426027: add edx, 0x12 */
	{ DWORD v_ = 0x754324u; m->esp -= 4; M32(m->esp) = v_; }	/* 42602a: push 0x754324 */
	{ DWORD a_ = m->eax, b_ = 0x46u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42602f: add eax, 0x46 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426032: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426033: push eax */
	m->esp -= 4; M32(m->esp) = 0x426039u; native_call(m, 0x4028b0u);	/* 426034: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426039: add esp, 0x20 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 42603c: xor ebx, ebx */
	m->esi = 0x754a24u;	/* 42603e: mov esi, 0x754a24 */
L_426043:
	m->ecx = M32((DWORD)(0x4dde84u));	/* 426043: mov ecx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426049: mov eax, dword ptr [0x4dde80] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42604e: push esi */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42604f: add eax, 0x30 */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x5cu);	/* 426052: lea edx, [ebx + ecx + 0x5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426056: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426057: push eax */
	m->esp -= 4; M32(m->esp) = 0x42605du; native_call(m, 0x402620u);	/* 426058: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 42605d: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426063: add esp, 0xc */
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 426066: add ebx, 0x18 */
	{ DWORD a_ = m->esi, b_ = 0x754f24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426069: cmp esi, 0x754f24 */
	if (m->sf != m->of) goto L_426043;	/* 42606f: jl 0x426043 */
	m->eax = M32((DWORD)(0x4de0c0u));	/* 426071: mov eax, dword ptr [0x4de0c0] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426076: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42607c: cmp eax, ecx */
	if (m->zf) goto L_4260a5;	/* 42607e: je 0x4260a5 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426080: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426087: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42608d: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426092: add edx, 0x5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426095: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426096: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42609b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42609c: push eax */
	m->esp -= 4; M32(m->esp) = 0x4260a2u; native_call(m, 0x402620u);	/* 42609d: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4260a2: add esp, 0xc */
L_4260a5:
	m->eax = M32((DWORD)(0x4de0c4u));	/* 4260a5: mov eax, dword ptr [0x4de0c4] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4260aa: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4260b0: cmp eax, ecx */
	if (m->zf) goto L_4260d9;	/* 4260b2: je 0x4260d9 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4260b4: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4260bb: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4260c1: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4260c6: add edx, 0x5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4260c9: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4260ca: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4260cf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4260d0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4260d6u; native_call(m, 0x402620u);	/* 4260d1: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4260d6: add esp, 0xc */
L_4260d9:
	m->eax = M32((DWORD)(0x4de0c8u));	/* 4260d9: mov eax, dword ptr [0x4de0c8] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4260de: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4260e4: cmp eax, ecx */
	if (m->zf) goto L_42610d;	/* 4260e6: je 0x42610d */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4260e8: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4260ef: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4260f5: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4260fa: add edx, 0x74 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4260fd: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4260fe: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426103: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426104: push eax */
	m->esp -= 4; M32(m->esp) = 0x42610au; native_call(m, 0x402620u);	/* 426105: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42610a: add esp, 0xc */
L_42610d:
	m->eax = M32((DWORD)(0x4de0ccu));	/* 42610d: mov eax, dword ptr [0x4de0cc] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426112: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426118: cmp eax, ecx */
	if (m->zf) goto L_426141;	/* 42611a: je 0x426141 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42611c: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426123: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426129: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42612e: add edx, 0x74 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426131: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426132: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426137: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426138: push eax */
	m->esp -= 4; M32(m->esp) = 0x42613eu; native_call(m, 0x402620u);	/* 426139: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42613e: add esp, 0xc */
L_426141:
	m->eax = M32((DWORD)(0x4de0d0u));	/* 426141: mov eax, dword ptr [0x4de0d0] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426146: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42614c: cmp eax, ecx */
	if (m->zf) goto L_426178;	/* 42614e: je 0x426178 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426150: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426157: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42615d: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426162: add edx, 0x8c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426168: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426169: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42616e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42616f: push eax */
	m->esp -= 4; M32(m->esp) = 0x426175u; native_call(m, 0x402620u);	/* 426170: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426175: add esp, 0xc */
L_426178:
	m->eax = M32((DWORD)(0x4de0d4u));	/* 426178: mov eax, dword ptr [0x4de0d4] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42617d: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426183: cmp eax, ecx */
	if (m->zf) goto L_4261af;	/* 426185: je 0x4261af */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426187: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42618e: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426194: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426199: add edx, 0x8c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42619f: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4261a0: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4261a5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4261a6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4261acu; native_call(m, 0x402620u);	/* 4261a7: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4261ac: add esp, 0xc */
L_4261af:
	m->eax = M32((DWORD)(0x4de0d8u));	/* 4261af: mov eax, dword ptr [0x4de0d8] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4261b4: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4261ba: cmp eax, ecx */
	if (m->zf) goto L_4261e6;	/* 4261bc: je 0x4261e6 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4261be: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4261c5: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4261cb: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4261d0: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4261d6: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4261d7: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4261dc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4261dd: push eax */
	m->esp -= 4; M32(m->esp) = 0x4261e3u; native_call(m, 0x402620u);	/* 4261de: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4261e3: add esp, 0xc */
L_4261e6:
	m->eax = M32((DWORD)(0x4de0dcu));	/* 4261e6: mov eax, dword ptr [0x4de0dc] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4261eb: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4261f1: cmp eax, ecx */
	if (m->zf) goto L_42621d;	/* 4261f3: je 0x42621d */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4261f5: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4261fc: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426202: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426207: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42620d: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42620e: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426213: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426214: push eax */
	m->esp -= 4; M32(m->esp) = 0x42621au; native_call(m, 0x402620u);	/* 426215: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42621a: add esp, 0xc */
L_42621d:
	m->eax = M32((DWORD)(0x4de0e0u));	/* 42621d: mov eax, dword ptr [0x4de0e0] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426222: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426228: cmp eax, ecx */
	if (m->zf) goto L_426254;	/* 42622a: je 0x426254 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42622c: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426233: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426239: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42623e: add edx, 0xbc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426244: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426245: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42624a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42624b: push eax */
	m->esp -= 4; M32(m->esp) = 0x426251u; native_call(m, 0x402620u);	/* 42624c: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426251: add esp, 0xc */
L_426254:
	m->eax = M32((DWORD)(0x4de0e4u));	/* 426254: mov eax, dword ptr [0x4de0e4] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426259: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42625f: cmp eax, ecx */
	if (m->zf) goto L_42628b;	/* 426261: je 0x42628b */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426263: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42626a: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426270: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426275: add edx, 0xbc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42627b: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42627c: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426281: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426282: push eax */
	m->esp -= 4; M32(m->esp) = 0x426288u; native_call(m, 0x402620u);	/* 426283: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426288: add esp, 0xc */
L_42628b:
	m->eax = M32((DWORD)(0x4de0e8u));	/* 42628b: mov eax, dword ptr [0x4de0e8] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426290: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426296: cmp eax, ecx */
	if (m->zf) goto L_4262c2;	/* 426298: je 0x4262c2 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42629a: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4262a1: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4262a7: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4262ac: add edx, 0xd4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4262b2: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4262b3: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4262b8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4262b9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4262bfu; native_call(m, 0x402620u);	/* 4262ba: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4262bf: add esp, 0xc */
L_4262c2:
	m->eax = M32((DWORD)(0x4de0ecu));	/* 4262c2: mov eax, dword ptr [0x4de0ec] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4262c7: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4262cd: cmp eax, ecx */
	if (m->zf) goto L_4262f9;	/* 4262cf: je 0x4262f9 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4262d1: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4262d8: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4262de: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4262e3: add edx, 0xd4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4262e9: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4262ea: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4262ef: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4262f0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4262f6u; native_call(m, 0x402620u);	/* 4262f1: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4262f6: add esp, 0xc */
L_4262f9:
	m->eax = M32((DWORD)(0x4de0f0u));	/* 4262f9: mov eax, dword ptr [0x4de0f0] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4262fe: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426304: cmp eax, ecx */
	if (m->zf) goto L_426330;	/* 426306: je 0x426330 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426308: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42630f: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426315: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42631a: add edx, 0xec */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426320: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426321: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426326: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426327: push eax */
	m->esp -= 4; M32(m->esp) = 0x42632du; native_call(m, 0x402620u);	/* 426328: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42632d: add esp, 0xc */
L_426330:
	m->eax = M32((DWORD)(0x4de0f4u));	/* 426330: mov eax, dword ptr [0x4de0f4] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426335: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42633b: cmp eax, ecx */
	if (m->zf) goto L_426367;	/* 42633d: je 0x426367 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42633f: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426346: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42634c: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426351: add edx, 0xec */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426357: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426358: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42635d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42635e: push eax */
	m->esp -= 4; M32(m->esp) = 0x426364u; native_call(m, 0x402620u);	/* 42635f: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426364: add esp, 0xc */
L_426367:
	m->eax = M32((DWORD)(0x4de0f8u));	/* 426367: mov eax, dword ptr [0x4de0f8] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42636c: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426372: cmp eax, ecx */
	if (m->zf) goto L_42639e;	/* 426374: je 0x42639e */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426376: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42637d: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426383: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426388: add edx, 0x104 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42638e: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42638f: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426394: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426395: push eax */
	m->esp -= 4; M32(m->esp) = 0x42639bu; native_call(m, 0x402620u);	/* 426396: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42639b: add esp, 0xc */
L_42639e:
	m->eax = M32((DWORD)(0x4de0fcu));	/* 42639e: mov eax, dword ptr [0x4de0fc] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4263a3: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4263a9: cmp eax, ecx */
	if (m->zf) goto L_4263d5;	/* 4263ab: je 0x4263d5 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4263ad: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4263b4: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4263ba: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4263bf: add edx, 0x104 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4263c5: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4263c6: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4263cb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4263cc: push eax */
	m->esp -= 4; M32(m->esp) = 0x4263d2u; native_call(m, 0x402620u);	/* 4263cd: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4263d2: add esp, 0xc */
L_4263d5:
	m->eax = M32((DWORD)(0x4de100u));	/* 4263d5: mov eax, dword ptr [0x4de100] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4263da: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4263e0: cmp eax, ecx */
	if (m->zf) goto L_42640c;	/* 4263e2: je 0x42640c */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4263e4: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4263eb: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4263f1: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x11cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4263f6: add edx, 0x11c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4263fc: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4263fd: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426402: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426403: push eax */
	m->esp -= 4; M32(m->esp) = 0x426409u; native_call(m, 0x402620u);	/* 426404: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426409: add esp, 0xc */
L_42640c:
	m->eax = M32((DWORD)(0x4de104u));	/* 42640c: mov eax, dword ptr [0x4de104] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426411: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426417: cmp eax, ecx */
	if (m->zf) goto L_426443;	/* 426419: je 0x426443 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42641b: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426422: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426428: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x11cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42642d: add edx, 0x11c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426433: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426434: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426439: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42643a: push eax */
	m->esp -= 4; M32(m->esp) = 0x426440u; native_call(m, 0x402620u);	/* 42643b: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426440: add esp, 0xc */
L_426443:
	m->eax = M32((DWORD)(0x4de108u));	/* 426443: mov eax, dword ptr [0x4de108] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426448: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42644e: cmp eax, ecx */
	if (m->zf) goto L_42647a;	/* 426450: je 0x42647a */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426452: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426459: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42645f: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426464: add edx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42646a: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42646b: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426470: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426471: push eax */
	m->esp -= 4; M32(m->esp) = 0x426477u; native_call(m, 0x402620u);	/* 426472: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426477: add esp, 0xc */
L_42647a:
	m->eax = M32((DWORD)(0x4de10cu));	/* 42647a: mov eax, dword ptr [0x4de10c] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42647f: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426485: cmp eax, ecx */
	if (m->zf) goto L_427577;	/* 426487: je 0x427577 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42648d: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426494: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42649a: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42649f: add edx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4264a5: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4264a6: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4264ab: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4264ac: push eax */
	m->esp -= 4; M32(m->esp) = 0x4264b2u; native_call(m, 0x402620u);	/* 4264ad: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4264b2: add esp, 0xc */
	goto L_427577;	/* 4264b5: jmp 0x427577 */
L_4264ba:
	m->ecx = M32((DWORD)(0x4de054u));	/* 4264ba: mov ecx, dword ptr [0x4de054] */
	m->edx = M32((DWORD)(0x4de050u));	/* 4264c0: mov edx, dword ptr [0x4de050] */
	m->eax = M32((DWORD)(0x4de04cu));	/* 4264c6: mov eax, dword ptr [0x4de04c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4264cb: push ecx */
	m->ecx = M32((DWORD)(0x4de048u));	/* 4264cc: mov ecx, dword ptr [0x4de048] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4264d2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4264d3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4264d4: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4264d5: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4264dfu; native_call(m, 0x41f0e0u);	/* 4264da: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4264df: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4264e5: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x12u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4264ea: add edx, 0x12 */
	{ DWORD v_ = 0x7543a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4264ed: push 0x7543a4 */
	{ DWORD a_ = m->eax, b_ = 0xbeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4264f2: add eax, 0xbe */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4264f7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4264f8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4264feu; native_call(m, 0x4028b0u);	/* 4264f9: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4264fe: add esp, 0x20 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 426501: xor ebx, ebx */
	m->esi = 0x7551a4u;	/* 426503: mov esi, 0x7551a4 */
L_426508:
	m->ecx = M32((DWORD)(0x4dde84u));	/* 426508: mov ecx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42650e: mov eax, dword ptr [0x4dde80] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 426513: push esi */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426514: add eax, 0x30 */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x5cu);	/* 426517: lea edx, [ebx + ecx + 0x5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42651b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42651c: push eax */
	m->esp -= 4; M32(m->esp) = 0x426522u; native_call(m, 0x402620u);	/* 42651d: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 426522: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426528: add esp, 0xc */
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 42652b: add ebx, 0x18 */
	{ DWORD a_ = m->esi, b_ = 0x755724u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42652e: cmp esi, 0x755724 */
	if (m->sf != m->of) goto L_426508;	/* 426534: jl 0x426508 */
	m->eax = M32((DWORD)(0x4de110u));	/* 426536: mov eax, dword ptr [0x4de110] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42653b: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426541: cmp eax, ecx */
	if (m->zf) goto L_42656a;	/* 426543: je 0x42656a */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426545: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42654c: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426552: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426557: add edx, 0x5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42655a: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42655b: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426560: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426561: push eax */
	m->esp -= 4; M32(m->esp) = 0x426567u; native_call(m, 0x402620u);	/* 426562: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426567: add esp, 0xc */
L_42656a:
	m->eax = M32((DWORD)(0x4de114u));	/* 42656a: mov eax, dword ptr [0x4de114] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42656f: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426575: cmp eax, ecx */
	if (m->zf) goto L_42659e;	/* 426577: je 0x42659e */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426579: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426580: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426586: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42658b: add edx, 0x5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42658e: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42658f: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426594: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426595: push eax */
	m->esp -= 4; M32(m->esp) = 0x42659bu; native_call(m, 0x402620u);	/* 426596: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42659b: add esp, 0xc */
L_42659e:
	m->eax = M32((DWORD)(0x4de118u));	/* 42659e: mov eax, dword ptr [0x4de118] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4265a3: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4265a9: cmp eax, ecx */
	if (m->zf) goto L_4265d2;	/* 4265ab: je 0x4265d2 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4265ad: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4265b4: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4265ba: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4265bf: add edx, 0x74 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4265c2: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4265c3: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4265c8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4265c9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4265cfu; native_call(m, 0x402620u);	/* 4265ca: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4265cf: add esp, 0xc */
L_4265d2:
	m->eax = M32((DWORD)(0x4de11cu));	/* 4265d2: mov eax, dword ptr [0x4de11c] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4265d7: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4265dd: cmp eax, ecx */
	if (m->zf) goto L_426606;	/* 4265df: je 0x426606 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4265e1: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4265e8: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4265ee: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4265f3: add edx, 0x74 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4265f6: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4265f7: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4265fc: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4265fd: push eax */
	m->esp -= 4; M32(m->esp) = 0x426603u; native_call(m, 0x402620u);	/* 4265fe: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426603: add esp, 0xc */
L_426606:
	m->eax = M32((DWORD)(0x4de120u));	/* 426606: mov eax, dword ptr [0x4de120] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42660b: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426611: cmp eax, ecx */
	if (m->zf) goto L_42663d;	/* 426613: je 0x42663d */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426615: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42661c: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426622: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426627: add edx, 0x8c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42662d: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42662e: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426633: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426634: push eax */
	m->esp -= 4; M32(m->esp) = 0x42663au; native_call(m, 0x402620u);	/* 426635: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42663a: add esp, 0xc */
L_42663d:
	m->eax = M32((DWORD)(0x4de124u));	/* 42663d: mov eax, dword ptr [0x4de124] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426642: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426648: cmp eax, ecx */
	if (m->zf) goto L_426674;	/* 42664a: je 0x426674 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42664c: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426653: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426659: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42665e: add edx, 0x8c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426664: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426665: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42666a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42666b: push eax */
	m->esp -= 4; M32(m->esp) = 0x426671u; native_call(m, 0x402620u);	/* 42666c: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426671: add esp, 0xc */
L_426674:
	m->eax = M32((DWORD)(0x4de138u));	/* 426674: mov eax, dword ptr [0x4de138] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426679: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42667f: cmp eax, ecx */
	if (m->zf) goto L_4266ab;	/* 426681: je 0x4266ab */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426683: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42668a: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426690: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426695: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42669b: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42669c: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4266a1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4266a2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4266a8u; native_call(m, 0x402620u);	/* 4266a3: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4266a8: add esp, 0xc */
L_4266ab:
	m->eax = M32((DWORD)(0x4de13cu));	/* 4266ab: mov eax, dword ptr [0x4de13c] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4266b0: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4266b6: cmp eax, ecx */
	if (m->zf) goto L_4266e2;	/* 4266b8: je 0x4266e2 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4266ba: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4266c1: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4266c7: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4266cc: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4266d2: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4266d3: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4266d8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4266d9: push eax */
	m->esp -= 4; M32(m->esp) = 0x4266dfu; native_call(m, 0x402620u);	/* 4266da: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4266df: add esp, 0xc */
L_4266e2:
	m->eax = M32((DWORD)(0x4de140u));	/* 4266e2: mov eax, dword ptr [0x4de140] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4266e7: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4266ed: cmp eax, ecx */
	if (m->zf) goto L_426719;	/* 4266ef: je 0x426719 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4266f1: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4266f8: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4266fe: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426703: add edx, 0xbc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426709: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42670a: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42670f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426710: push eax */
	m->esp -= 4; M32(m->esp) = 0x426716u; native_call(m, 0x402620u);	/* 426711: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426716: add esp, 0xc */
L_426719:
	m->eax = M32((DWORD)(0x4de144u));	/* 426719: mov eax, dword ptr [0x4de144] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42671e: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426724: cmp eax, ecx */
	if (m->zf) goto L_426750;	/* 426726: je 0x426750 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426728: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42672f: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426735: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42673a: add edx, 0xbc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426740: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426741: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426746: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426747: push eax */
	m->esp -= 4; M32(m->esp) = 0x42674du; native_call(m, 0x402620u);	/* 426748: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42674d: add esp, 0xc */
L_426750:
	m->eax = M32((DWORD)(0x4de148u));	/* 426750: mov eax, dword ptr [0x4de148] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426755: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42675b: cmp eax, ecx */
	if (m->zf) goto L_426787;	/* 42675d: je 0x426787 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42675f: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426766: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42676c: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426771: add edx, 0xd4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426777: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426778: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42677d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42677e: push eax */
	m->esp -= 4; M32(m->esp) = 0x426784u; native_call(m, 0x402620u);	/* 42677f: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426784: add esp, 0xc */
L_426787:
	m->eax = M32((DWORD)(0x4de14cu));	/* 426787: mov eax, dword ptr [0x4de14c] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42678c: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426792: cmp eax, ecx */
	if (m->zf) goto L_4267be;	/* 426794: je 0x4267be */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426796: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42679d: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4267a3: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4267a8: add edx, 0xd4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4267ae: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4267af: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4267b4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4267b5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4267bbu; native_call(m, 0x402620u);	/* 4267b6: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4267bb: add esp, 0xc */
L_4267be:
	m->eax = M32((DWORD)(0x4de150u));	/* 4267be: mov eax, dword ptr [0x4de150] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4267c3: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4267c9: cmp eax, ecx */
	if (m->zf) goto L_4267f5;	/* 4267cb: je 0x4267f5 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4267cd: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4267d4: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4267da: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4267df: add edx, 0xec */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4267e5: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4267e6: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4267eb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4267ec: push eax */
	m->esp -= 4; M32(m->esp) = 0x4267f2u; native_call(m, 0x402620u);	/* 4267ed: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4267f2: add esp, 0xc */
L_4267f5:
	m->eax = M32((DWORD)(0x4de154u));	/* 4267f5: mov eax, dword ptr [0x4de154] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4267fa: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426800: cmp eax, ecx */
	if (m->zf) goto L_42682c;	/* 426802: je 0x42682c */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426804: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42680b: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426811: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426816: add edx, 0xec */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42681c: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42681d: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426822: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426823: push eax */
	m->esp -= 4; M32(m->esp) = 0x426829u; native_call(m, 0x402620u);	/* 426824: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426829: add esp, 0xc */
L_42682c:
	m->eax = M32((DWORD)(0x4de128u));	/* 42682c: mov eax, dword ptr [0x4de128] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426831: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426837: cmp eax, ecx */
	if (m->zf) goto L_426863;	/* 426839: je 0x426863 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42683b: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426842: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426848: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42684d: add edx, 0x104 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426853: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426854: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426859: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42685a: push eax */
	m->esp -= 4; M32(m->esp) = 0x426860u; native_call(m, 0x402620u);	/* 42685b: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426860: add esp, 0xc */
L_426863:
	m->eax = M32((DWORD)(0x4de12cu));	/* 426863: mov eax, dword ptr [0x4de12c] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426868: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42686e: cmp eax, ecx */
	if (m->zf) goto L_42689a;	/* 426870: je 0x42689a */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426872: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426879: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42687f: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426884: add edx, 0x104 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42688a: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42688b: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426890: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426891: push eax */
	m->esp -= 4; M32(m->esp) = 0x426897u; native_call(m, 0x402620u);	/* 426892: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426897: add esp, 0xc */
L_42689a:
	m->eax = M32((DWORD)(0x4de130u));	/* 42689a: mov eax, dword ptr [0x4de130] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42689f: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4268a5: cmp eax, ecx */
	if (m->zf) goto L_4268d1;	/* 4268a7: je 0x4268d1 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4268a9: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4268b0: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4268b6: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x11cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4268bb: add edx, 0x11c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4268c1: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4268c2: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4268c7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4268c8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4268ceu; native_call(m, 0x402620u);	/* 4268c9: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4268ce: add esp, 0xc */
L_4268d1:
	m->eax = M32((DWORD)(0x4de134u));	/* 4268d1: mov eax, dword ptr [0x4de134] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4268d6: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4268dc: cmp eax, ecx */
	if (m->zf) goto L_426908;	/* 4268de: je 0x426908 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4268e0: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4268e7: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4268ed: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x11cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4268f2: add edx, 0x11c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4268f8: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4268f9: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4268fe: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4268ff: push eax */
	m->esp -= 4; M32(m->esp) = 0x426905u; native_call(m, 0x402620u);	/* 426900: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426905: add esp, 0xc */
L_426908:
	m->eax = M32((DWORD)(0x4de158u));	/* 426908: mov eax, dword ptr [0x4de158] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42690d: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426913: cmp eax, ecx */
	if (m->zf) goto L_42693f;	/* 426915: je 0x42693f */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426917: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42691e: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426924: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426929: add edx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42692f: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426930: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426935: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426936: push eax */
	m->esp -= 4; M32(m->esp) = 0x42693cu; native_call(m, 0x402620u);	/* 426937: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42693c: add esp, 0xc */
L_42693f:
	m->eax = M32((DWORD)(0x4de15cu));	/* 42693f: mov eax, dword ptr [0x4de15c] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426944: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42694a: cmp eax, ecx */
	if (m->zf) goto L_426976;	/* 42694c: je 0x426976 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 42694e: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426955: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42695b: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426960: add edx, 0x134 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426966: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426967: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42696c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42696d: push eax */
	m->esp -= 4; M32(m->esp) = 0x426973u; native_call(m, 0x402620u);	/* 42696e: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426973: add esp, 0xc */
L_426976:
	m->eax = M32((DWORD)(0x4de160u));	/* 426976: mov eax, dword ptr [0x4de160] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 42697b: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426981: cmp eax, ecx */
	if (m->zf) goto L_4269ad;	/* 426983: je 0x4269ad */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426985: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42698c: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426992: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x14cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426997: add edx, 0x14c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42699d: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42699e: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4269a3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4269a4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4269aau; native_call(m, 0x402620u);	/* 4269a5: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4269aa: add esp, 0xc */
L_4269ad:
	m->eax = M32((DWORD)(0x4de164u));	/* 4269ad: mov eax, dword ptr [0x4de164] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 4269b2: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4269b8: cmp eax, ecx */
	if (m->zf) goto L_427577;	/* 4269ba: je 0x427577 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 4269c0: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4269c7: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4269cd: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x14cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4269d2: add edx, 0x14c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4269d8: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4269d9: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4269de: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4269df: push eax */
	m->esp -= 4; M32(m->esp) = 0x4269e5u; native_call(m, 0x402620u);	/* 4269e0: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4269e5: add esp, 0xc */
	goto L_427577;	/* 4269e8: jmp 0x427577 */
L_4269ed:
	m->ecx = M32((DWORD)(0x4de054u));	/* 4269ed: mov ecx, dword ptr [0x4de054] */
	m->edx = M32((DWORD)(0x4de050u));	/* 4269f3: mov edx, dword ptr [0x4de050] */
	m->eax = M32((DWORD)(0x4de04cu));	/* 4269f9: mov eax, dword ptr [0x4de04c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4269fe: push ecx */
	m->ecx = M32((DWORD)(0x4de048u));	/* 4269ff: mov ecx, dword ptr [0x4de048] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426a05: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426a06: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426a07: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 426a08: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x426a12u; native_call(m, 0x41f0e0u);	/* 426a0d: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426a12: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426a18: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x12u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426a1d: add edx, 0x12 */
	{ DWORD v_ = 0x754424u; m->esp -= 4; M32(m->esp) = v_; }	/* 426a20: push 0x754424 */
	{ DWORD a_ = m->eax, b_ = 0x136u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426a25: add eax, 0x136 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426a2a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426a2b: push eax */
	m->esp -= 4; M32(m->esp) = 0x426a31u; native_call(m, 0x4028b0u);	/* 426a2c: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426a31: add esp, 0x20 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 426a34: xor ebx, ebx */
	m->esi = 0x755924u;	/* 426a36: mov esi, 0x755924 */
L_426a3b:
	m->ecx = M32((DWORD)(0x4dde84u));	/* 426a3b: mov ecx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426a41: mov eax, dword ptr [0x4dde80] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 426a46: push esi */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426a47: add eax, 0x30 */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x5cu);	/* 426a4a: lea edx, [ebx + ecx + 0x5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426a4e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426a4f: push eax */
	m->esp -= 4; M32(m->esp) = 0x426a55u; native_call(m, 0x402620u);	/* 426a50: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 426a55: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426a5b: add esp, 0xc */
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 426a5e: add ebx, 0x18 */
	{ DWORD a_ = m->esi, b_ = 0x755e24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426a61: cmp esi, 0x755e24 */
	if (m->sf != m->of) goto L_426a3b;	/* 426a67: jl 0x426a3b */
	m->eax = M32((DWORD)(0x4de168u));	/* 426a69: mov eax, dword ptr [0x4de168] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426a6e: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426a74: cmp eax, ecx */
	if (m->zf) goto L_426a9d;	/* 426a76: je 0x426a9d */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426a78: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426a7f: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426a85: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426a8a: add edx, 0x5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426a8d: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426a8e: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426a93: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426a94: push eax */
	m->esp -= 4; M32(m->esp) = 0x426a9au; native_call(m, 0x402620u);	/* 426a95: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426a9a: add esp, 0xc */
L_426a9d:
	m->eax = M32((DWORD)(0x4de16cu));	/* 426a9d: mov eax, dword ptr [0x4de16c] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426aa2: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426aa8: cmp eax, ecx */
	if (m->zf) goto L_426ad1;	/* 426aaa: je 0x426ad1 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426aac: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426ab3: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426ab9: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426abe: add edx, 0x5c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426ac1: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426ac2: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426ac7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426ac8: push eax */
	m->esp -= 4; M32(m->esp) = 0x426aceu; native_call(m, 0x402620u);	/* 426ac9: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426ace: add esp, 0xc */
L_426ad1:
	m->eax = M32((DWORD)(0x4de170u));	/* 426ad1: mov eax, dword ptr [0x4de170] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426ad6: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426adc: cmp eax, ecx */
	if (m->zf) goto L_426b05;	/* 426ade: je 0x426b05 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426ae0: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426ae7: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426aed: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426af2: add edx, 0x74 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426af5: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426af6: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426afb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426afc: push eax */
	m->esp -= 4; M32(m->esp) = 0x426b02u; native_call(m, 0x402620u);	/* 426afd: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426b02: add esp, 0xc */
L_426b05:
	m->eax = M32((DWORD)(0x4de174u));	/* 426b05: mov eax, dword ptr [0x4de174] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426b0a: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426b10: cmp eax, ecx */
	if (m->zf) goto L_426b39;	/* 426b12: je 0x426b39 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426b14: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426b1b: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426b21: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426b26: add edx, 0x74 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426b29: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426b2a: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426b2f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426b30: push eax */
	m->esp -= 4; M32(m->esp) = 0x426b36u; native_call(m, 0x402620u);	/* 426b31: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426b36: add esp, 0xc */
L_426b39:
	m->eax = M32((DWORD)(0x4de178u));	/* 426b39: mov eax, dword ptr [0x4de178] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426b3e: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426b44: cmp eax, ecx */
	if (m->zf) goto L_426b70;	/* 426b46: je 0x426b70 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426b48: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426b4f: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426b55: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426b5a: add edx, 0x8c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426b60: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426b61: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426b66: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426b67: push eax */
	m->esp -= 4; M32(m->esp) = 0x426b6du; native_call(m, 0x402620u);	/* 426b68: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426b6d: add esp, 0xc */
L_426b70:
	m->eax = M32((DWORD)(0x4de17cu));	/* 426b70: mov eax, dword ptr [0x4de17c] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426b75: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426b7b: cmp eax, ecx */
	if (m->zf) goto L_426ba7;	/* 426b7d: je 0x426ba7 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426b7f: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426b86: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426b8c: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426b91: add edx, 0x8c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426b97: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426b98: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426b9d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426b9e: push eax */
	m->esp -= 4; M32(m->esp) = 0x426ba4u; native_call(m, 0x402620u);	/* 426b9f: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426ba4: add esp, 0xc */
L_426ba7:
	m->eax = M32((DWORD)(0x4de180u));	/* 426ba7: mov eax, dword ptr [0x4de180] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426bac: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426bb2: cmp eax, ecx */
	if (m->zf) goto L_426bde;	/* 426bb4: je 0x426bde */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426bb6: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426bbd: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426bc3: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426bc8: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426bce: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426bcf: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426bd4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426bd5: push eax */
	m->esp -= 4; M32(m->esp) = 0x426bdbu; native_call(m, 0x402620u);	/* 426bd6: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426bdb: add esp, 0xc */
L_426bde:
	m->eax = M32((DWORD)(0x4de184u));	/* 426bde: mov eax, dword ptr [0x4de184] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426be3: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426be9: cmp eax, ecx */
	if (m->zf) goto L_426c15;	/* 426beb: je 0x426c15 */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426bed: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426bf4: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426bfa: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426bff: add edx, 0xa4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426c05: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426c06: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426c0b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426c0c: push eax */
	m->esp -= 4; M32(m->esp) = 0x426c12u; native_call(m, 0x402620u);	/* 426c0d: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426c12: add esp, 0xc */
L_426c15:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 426c15: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 426c1a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 426c1c: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 426c1e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 426c23: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x426c2du; native_call(m, 0x41f0e0u);	/* 426c28: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4de188u));	/* 426c2d: mov eax, dword ptr [0x4de188] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426c32: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426c38: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426c3b: cmp eax, ecx */
	if (m->zf) goto L_426c9e;	/* 426c3d: je 0x426c9e */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426c3f: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426c46: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426c4c: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426c51: add edx, 0xbc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426c57: push ecx */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426c58: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426c5d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426c5e: push eax */
	m->esp -= 4; M32(m->esp) = 0x426c64u; native_call(m, 0x4028b0u);	/* 426c5f: call 0x4028b0 */
	m->eax = M32((DWORD)(0x4de188u));	/* 426c64: mov eax, dword ptr [0x4de188] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426c69: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426c6f: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426c72: cmp eax, ecx */
	if (m->zf) goto L_426c9e;	/* 426c74: je 0x426c9e */
	m->ecx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426c76: mov ecx, dword ptr [eax*4 + 0x4b0750] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426c7d: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426c83: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xbcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426c88: add edx, 0xbc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426c8e: push ecx */
	{ DWORD a_ = m->eax, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426c8f: add eax, 0x14a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426c94: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426c95: push eax */
	m->esp -= 4; M32(m->esp) = 0x426c9bu; native_call(m, 0x4028b0u);	/* 426c96: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426c9b: add esp, 0xc */
L_426c9e:
	m->ecx = M32((DWORD)(0x4de054u));	/* 426c9e: mov ecx, dword ptr [0x4de054] */
	m->edx = M32((DWORD)(0x4de050u));	/* 426ca4: mov edx, dword ptr [0x4de050] */
	m->eax = M32((DWORD)(0x4de04cu));	/* 426caa: mov eax, dword ptr [0x4de04c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426caf: push ecx */
	m->ecx = M32((DWORD)(0x4de048u));	/* 426cb0: mov ecx, dword ptr [0x4de048] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426cb6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426cb7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426cb8: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 426cb9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x426cc3u; native_call(m, 0x41f0e0u);	/* 426cbe: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4de190u));	/* 426cc3: mov eax, dword ptr [0x4de190] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426cc8: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426cce: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426cd1: cmp eax, ecx */
	if (m->zf) goto L_426cfd;	/* 426cd3: je 0x426cfd */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426cd5: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426cdc: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426ce1: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0xd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426ce7: add eax, 0xd4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426cec: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426ced: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426cf3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426cf4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426cfau; native_call(m, 0x402620u);	/* 426cf5: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426cfa: add esp, 0xc */
L_426cfd:
	m->eax = M32((DWORD)(0x4de194u));	/* 426cfd: mov eax, dword ptr [0x4de194] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426d02: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426d08: cmp eax, ecx */
	if (m->zf) goto L_426d34;	/* 426d0a: je 0x426d34 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426d0c: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426d13: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426d18: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0xd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426d1e: add eax, 0xd4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426d23: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426d24: add ecx, 0x14a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426d2a: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426d2b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426d31u; native_call(m, 0x402620u);	/* 426d2c: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426d31: add esp, 0xc */
L_426d34:
	m->eax = M32((DWORD)(0x4de1a0u));	/* 426d34: mov eax, dword ptr [0x4de1a0] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426d39: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426d3f: cmp eax, ecx */
	if (m->zf) goto L_426d6b;	/* 426d41: je 0x426d6b */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426d43: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426d4a: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426d4f: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0xecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426d55: add eax, 0xec */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426d5a: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426d5b: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426d61: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426d62: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426d68u; native_call(m, 0x402620u);	/* 426d63: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426d68: add esp, 0xc */
L_426d6b:
	m->eax = M32((DWORD)(0x4de1a4u));	/* 426d6b: mov eax, dword ptr [0x4de1a4] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426d70: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426d76: cmp eax, ecx */
	if (m->zf) goto L_426da2;	/* 426d78: je 0x426da2 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426d7a: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426d81: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426d86: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0xecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426d8c: add eax, 0xec */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426d91: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426d92: add ecx, 0x14a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426d98: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426d99: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426d9fu; native_call(m, 0x402620u);	/* 426d9a: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426d9f: add esp, 0xc */
L_426da2:
	m->eax = M32((DWORD)(0x4de1a8u));	/* 426da2: mov eax, dword ptr [0x4de1a8] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426da7: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426dad: cmp eax, ecx */
	if (m->zf) goto L_426dd9;	/* 426daf: je 0x426dd9 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426db1: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426db8: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426dbd: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426dc3: add eax, 0x104 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426dc8: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426dc9: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426dcf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426dd0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426dd6u; native_call(m, 0x402620u);	/* 426dd1: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426dd6: add esp, 0xc */
L_426dd9:
	m->eax = M32((DWORD)(0x4de1acu));	/* 426dd9: mov eax, dword ptr [0x4de1ac] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426dde: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426de4: cmp eax, ecx */
	if (m->zf) goto L_426e10;	/* 426de6: je 0x426e10 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426de8: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426def: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426df4: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x104u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426dfa: add eax, 0x104 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426dff: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426e00: add ecx, 0x14a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426e06: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426e07: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426e0du; native_call(m, 0x402620u);	/* 426e08: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426e0d: add esp, 0xc */
L_426e10:
	m->eax = M32((DWORD)(0x4de1b0u));	/* 426e10: mov eax, dword ptr [0x4de1b0] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426e15: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426e1b: cmp eax, ecx */
	if (m->zf) goto L_426e47;	/* 426e1d: je 0x426e47 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426e1f: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426e26: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426e2b: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x11cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426e31: add eax, 0x11c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426e36: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426e37: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426e3d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426e3e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426e44u; native_call(m, 0x402620u);	/* 426e3f: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426e44: add esp, 0xc */
L_426e47:
	m->eax = M32((DWORD)(0x4de1b4u));	/* 426e47: mov eax, dword ptr [0x4de1b4] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426e4c: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426e52: cmp eax, ecx */
	if (m->zf) goto L_426e7e;	/* 426e54: je 0x426e7e */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426e56: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426e5d: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426e62: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x11cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426e68: add eax, 0x11c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426e6d: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426e6e: add ecx, 0x14a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426e74: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426e75: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426e7bu; native_call(m, 0x402620u);	/* 426e76: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426e7b: add esp, 0xc */
L_426e7e:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 426e7e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 426e83: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 426e85: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 426e87: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 426e8c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x426e96u; native_call(m, 0x41f0e0u);	/* 426e91: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4de1b8u));	/* 426e96: mov eax, dword ptr [0x4de1b8] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426e9b: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426ea1: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426ea4: cmp eax, ecx */
	if (m->zf) goto L_427577;	/* 426ea6: je 0x427577 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426eac: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426eb3: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426eb8: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426ebe: add eax, 0x134 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426ec3: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426ec4: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426eca: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426ecb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426ed1u; native_call(m, 0x4028b0u);	/* 426ecc: call 0x4028b0 */
	m->eax = M32((DWORD)(0x4de1b8u));	/* 426ed1: mov eax, dword ptr [0x4de1b8] */
	m->ecx = M32((DWORD)(0x4df8e4u));	/* 426ed6: mov ecx, dword ptr [0x4df8e4] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426edc: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426edf: cmp eax, ecx */
	if (m->zf) goto L_427577;	/* 426ee1: je 0x427577 */
	m->edx = M32((DWORD)(m->eax*4 + 0x4b0750u));	/* 426ee7: mov edx, dword ptr [eax*4 + 0x4b0750] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426eee: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426ef3: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x134u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426ef9: add eax, 0x134 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426efe: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x14au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426eff: add ecx, 0x14a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426f05: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426f06: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426f0cu; native_call(m, 0x4028b0u);	/* 426f07: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426f0c: add esp, 0xc */
	goto L_427577;	/* 426f0f: jmp 0x427577 */
L_426f14:
	m->edx = M32((DWORD)(0x4de054u));	/* 426f14: mov edx, dword ptr [0x4de054] */
	m->eax = M32((DWORD)(0x4de050u));	/* 426f1a: mov eax, dword ptr [0x4de050] */
	m->ecx = M32((DWORD)(0x4de04cu));	/* 426f1f: mov ecx, dword ptr [0x4de04c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426f25: push edx */
	m->edx = M32((DWORD)(0x4de048u));	/* 426f26: mov edx, dword ptr [0x4de048] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426f2c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426f2d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426f2e: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 426f2f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x426f39u; native_call(m, 0x41f0e0u);	/* 426f34: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dde84u));	/* 426f39: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426f3e: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x12u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426f44: add eax, 0x12 */
	{ DWORD v_ = 0x7544a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 426f47: push 0x7544a4 */
	{ DWORD a_ = m->ecx, b_ = 0x1aeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426f4c: add ecx, 0x1ae */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426f52: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426f53: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426f59u; native_call(m, 0x4028b0u);	/* 426f54: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426f59: add esp, 0x20 */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 426f5c: xor ebx, ebx */
	m->esi = 0x7560a4u;	/* 426f5e: mov esi, 0x7560a4 */
L_426f63:
	m->edx = M32((DWORD)(0x4dde84u));	/* 426f63: mov edx, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426f69: mov ecx, dword ptr [0x4dde80] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 426f6f: push esi */
	{ DWORD a_ = m->ecx, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426f70: add ecx, 0x30 */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x5cu);	/* 426f73: lea eax, [ebx + edx + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426f77: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426f78: push ecx */
	m->esp -= 4; M32(m->esp) = 0x426f7eu; native_call(m, 0x402620u);	/* 426f79: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 426f7e: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426f84: add esp, 0xc */
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 426f87: add ebx, 0x18 */
	{ DWORD a_ = m->esi, b_ = 0x756224u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426f8a: cmp esi, 0x756224 */
	if (m->sf != m->of) goto L_426f63;	/* 426f90: jl 0x426f63 */
	m->edx = M32((DWORD)(0x4dde84u));	/* 426f92: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 426f98: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xb0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426f9d: add edx, 0xb0 */
	{ DWORD v_ = 0x756224u; m->esp -= 4; M32(m->esp) = v_; }	/* 426fa3: push 0x756224 */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426fa8: add eax, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426fab: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426fac: push eax */
	m->esp -= 4; M32(m->esp) = 0x426fb2u; native_call(m, 0x402620u);	/* 426fad: call 0x402620 */
	m->eax = M32((DWORD)(0x4de1c0u));	/* 426fb2: mov eax, dword ptr [0x4de1c0] */
	m->esi = 0x1u;	/* 426fb7: mov esi, 1 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 426fbc: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 426fbf: cmp eax, esi */
	if (!m->zf) goto L_426fe1;	/* 426fc1: jne 0x426fe1 */
	m->ecx = M32((DWORD)(0x4dde84u));	/* 426fc3: mov ecx, dword ptr [0x4dde84] */
	m->edx = M32((DWORD)(0x4dde80u));	/* 426fc9: mov edx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->ecx, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426fcf: add ecx, 0x5c */
	{ DWORD v_ = 0x7519a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 426fd2: push 0x7519a4 */
	{ DWORD a_ = m->edx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 426fd7: add edx, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426fdd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 426fde: push edx */
	goto L_426ffc;	/* 426fdf: jmp 0x426ffc */
L_426fe1:
	m->eax = M32((DWORD)(0x4dde84u));	/* 426fe1: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 426fe6: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x5cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 426fec: add eax, 0x5c */
	{ DWORD v_ = 0x751924u; m->esp -= 4; M32(m->esp) = v_; }	/* 426fef: push 0x751924 */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 426ff4: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 426ffa: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 426ffb: push ecx */
L_426ffc:
	m->esp -= 4; M32(m->esp) = 0x427001u; native_call(m, 0x402620u);	/* 426ffc: call 0x402620 */
	m->eax = M32((DWORD)(0x4de1c4u));	/* 427001: mov eax, dword ptr [0x4de1c4] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427006: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 427009: cmp eax, esi */
	if (!m->zf) goto L_427029;	/* 42700b: jne 0x427029 */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42700d: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 427013: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 427018: add edx, 0x74 */
	{ DWORD v_ = 0x7519a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42701b: push 0x7519a4 */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427020: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427025: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427026: push eax */
	goto L_427045;	/* 427027: jmp 0x427045 */
L_427029:
	m->ecx = M32((DWORD)(0x4dde84u));	/* 427029: mov ecx, dword ptr [0x4dde84] */
	m->edx = M32((DWORD)(0x4dde80u));	/* 42702f: mov edx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->ecx, b_ = 0x74u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427035: add ecx, 0x74 */
	{ DWORD v_ = 0x751924u; m->esp -= 4; M32(m->esp) = v_; }	/* 427038: push 0x751924 */
	{ DWORD a_ = m->edx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42703d: add edx, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427043: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427044: push edx */
L_427045:
	m->esp -= 4; M32(m->esp) = 0x42704au; native_call(m, 0x402620u);	/* 427045: call 0x402620 */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 42704a: mov eax, dword ptr [0x9db0a4] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42704f: add esp, 0xc */
	m->ecx = m->eax;	/* 427052: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427054: and ecx, 0x800001ff */
	if (!m->sf) goto L_427064;	/* 42705a: jns 0x427064 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 42705c: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 42705d: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 427063: inc ecx */
L_427064:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 427064: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 427065: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42706b: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42706c: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 42706e: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 427074: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 427077: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x427080u; native_call(m, 0x4566c0u);	/* 42707b: call 0x4566c0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427080: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x42708bu; native_call(m, M32(0x4a9224u));	/* 427085: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42708b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427090: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427095: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42709a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4270a5u; native_call(m, M32(0x4a9228u));	/* 42709f: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 4270a5: mov eax, dword ptr [0x4dde84] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4270aa: push 0 */
	m->ecx = (DWORD)(m->eax + 0xa0u);	/* 4270ac: lea ecx, [eax + 0xa0] */
	{ DWORD a_ = m->eax, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4270b2: add eax, 0x88 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4270b7: push ecx */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 4270b8: mov ecx, dword ptr [0x4dde80] */
	m->edx = (DWORD)(m->ecx + 0x108u);	/* 4270be: lea edx, [ecx + 0x108] */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4270c4: add ecx, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4270ca: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4270cb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4270cc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4270d2u; native_call(m, 0x4284d0u);	/* 4270cd: call 0x4284d0 */
	m->eax = M32((DWORD)(0x4dde84u));	/* 4270d2: mov eax, dword ptr [0x4dde84] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4270d7: push 0 */
	m->ecx = (DWORD)(m->eax + 0xa0u);	/* 4270d9: lea ecx, [eax + 0xa0] */
	{ DWORD a_ = m->eax, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4270df: add eax, 0x88 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4270e4: push ecx */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 4270e5: mov ecx, dword ptr [0x4dde80] */
	m->edx = (DWORD)(m->ecx + 0x210u);	/* 4270eb: lea edx, [ecx + 0x210] */
	{ DWORD a_ = m->ecx, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4270f1: add ecx, 0x1d0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4270f7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4270f8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4270f9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4270ffu; native_call(m, 0x4285c0u);	/* 4270fa: call 0x4285c0 */
	m->ebx = M32((DWORD)(0x4a921cu));	/* 4270ff: mov ebx, dword ptr [0x4a921c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427105: add esp, 0x28 */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 427108: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42710cu; native_call(m, m->ebx);	/* 42710a: call ebx */
	m->esi = M32((DWORD)(0x4a920cu));	/* 42710c: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427112: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427114: push 0 */
	m->esp -= 4; M32(m->esp) = 0x427118u; native_call(m, m->esi);	/* 427116: call esi */
	m->eax = M32((DWORD)(0x4dde84u));	/* 427118: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 42711d: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427123: add eax, 0x88 */
	{ DWORD a_ = m->ecx, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427128: add ecx, 0x108 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42712e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42712f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427135u; native_call(m, 0x41ef60u);	/* 427130: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427135: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427138: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42713a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x427141u; native_call(m, m->esi);	/* 42713f: call esi */
	m->edx = M32((DWORD)(0x4dde84u));	/* 427141: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 427147: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42714c: add edx, 0x88 */
	{ DWORD a_ = m->eax, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427152: add eax, 0x1d0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427157: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427158: push eax */
	m->esp -= 4; M32(m->esp) = 0x42715eu; native_call(m, 0x41ef60u);	/* 427159: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42715e: add esp, 8 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427161: push 0x3e000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427166: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42716du; native_call(m, m->esi);	/* 42716b: call esi */
	m->ecx = M32((DWORD)(0x4dde84u));	/* 42716d: mov ecx, dword ptr [0x4dde84] */
	m->edx = M32((DWORD)(0x4dde80u));	/* 427173: mov edx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->ecx, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427179: add ecx, 0xa0 */
	{ DWORD a_ = m->edx, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42717f: add edx, 0x1d0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427185: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427186: push edx */
	m->esp -= 4; M32(m->esp) = 0x42718cu; native_call(m, 0x41ef60u);	/* 427187: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42718c: add esp, 8 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42718f: push 0x3e000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427194: push 0 */
	m->esp -= 4; M32(m->esp) = 0x427198u; native_call(m, m->esi);	/* 427196: call esi */
	m->eax = M32((DWORD)(0x4dde84u));	/* 427198: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 42719d: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4271a3: add eax, 0xa0 */
	{ DWORD a_ = m->ecx, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4271a8: add ecx, 0x108 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4271ae: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4271af: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4271b5u; native_call(m, 0x41ef60u);	/* 4271b0: call 0x41ef60 */
	m->ebp = M32((DWORD)(0x4a9220u));	/* 4271b5: mov ebp, dword ptr [0x4a9220] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4271bb: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4271c0u; native_call(m, m->ebp);	/* 4271be: call ebp */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 4271c0: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4271c4u; native_call(m, m->ebx);	/* 4271c2: call ebx */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4271c4: push 0x3e000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4271c9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4271cdu; native_call(m, m->esi);	/* 4271cb: call esi */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4271cd: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4271d3: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4271d8: add edx, 0x88 */
	{ DWORD a_ = m->eax, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4271de: add eax, 0x108 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4271e3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4271e4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4271eau; native_call(m, 0x41ef60u);	/* 4271e5: call 0x41ef60 */
	FPUSH((long double)(int)M32((DWORD)(0x4de1c8u)));	/* 4271ea: fild dword ptr [0x4de1c8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4271f0: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 4271f3: fmul dword ptr [0x4a9504] */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4271f9: push 0x3e000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4271fe: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 4271ff: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x427204u; native_call(m, m->esi);	/* 427202: call esi */
	FPUSH((long double)(int)M32((DWORD)(0x4de1c8u)));	/* 427204: fild dword ptr [0x4de1c8] */
	m->ecx = M32((DWORD)(0x4dde84u));	/* 42720a: mov ecx, dword ptr [0x4dde84] */
	{ DWORD a_ = m->ecx, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427210: add ecx, 0x88 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94a8u));	/* 427216: fmul dword ptr [0x4a94a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42721c: push ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 42721d: call 0x49ec14 */
	m->edx = M32((DWORD)(0x4dde80u));	/* 427222: mov edx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 427228: sub edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42722a: add edx, 0x108 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427230: push edx */
	m->esp -= 4; M32(m->esp) = 0x427236u; native_call(m, 0x41ef60u);	/* 427231: call 0x41ef60 */
	FPUSH((long double)(int)M32((DWORD)(0x4de1c8u)));	/* 427236: fild dword ptr [0x4de1c8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42723c: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 42723f: fmul dword ptr [0x4a9504] */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427245: push 0x3e800000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42724a: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 42724b: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x427250u; native_call(m, m->esi);	/* 42724e: call esi */
	FPUSH((long double)(int)M32((DWORD)(0x4de1c8u)));	/* 427250: fild dword ptr [0x4de1c8] */
	m->eax = M32((DWORD)(0x4dde84u));	/* 427256: mov eax, dword ptr [0x4dde84] */
	{ DWORD a_ = m->eax, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42725b: add eax, 0xa0 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a94a8u));	/* 427260: fmul dword ptr [0x4a94a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427266: push eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 427267: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 42726c: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427272: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427274: add ecx, 0x108 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42727a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x427280u; native_call(m, 0x41ef60u);	/* 42727b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427280: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427283: push 0x3e800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427288: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42728cu; native_call(m, m->esi);	/* 42728a: call esi */
	m->edx = M32((DWORD)(0x4dde84u));	/* 42728c: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 427292: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 427297: add edx, 0xa0 */
	{ DWORD a_ = m->eax, b_ = 0x108u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42729d: add eax, 0x108 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4272a2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4272a3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4272a9u; native_call(m, 0x41ef60u);	/* 4272a4: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4272a9: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x4272aeu; native_call(m, m->ebp);	/* 4272ac: call ebp */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ddb98u)));	/* 4272ae: fld dword ptr [0x4ddb98] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 4272b4: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4272ba: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4272bc: test ah, 0x41 */
	if (!m->zf) goto L_42732d;	/* 4272bf: jne 0x42732d */
	m->eax = M32((DWORD)(0x4dde90u));	/* 4272c1: mov eax, dword ptr [0x4dde90] */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4272c6: sub eax, 0 */
	if (m->zf) goto L_4272fd;	/* 4272c9: je 0x4272fd */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4272cb: dec eax */
	if (!m->zf) goto L_42732d;	/* 4272cc: jne 0x42732d */
	m->eax = M32((DWORD)(0x4dde84u));	/* 4272ce: mov eax, dword ptr [0x4dde84] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4272d3: push 1 */
	m->ecx = (DWORD)(m->eax + 0xa0u);	/* 4272d5: lea ecx, [eax + 0xa0] */
	{ DWORD a_ = m->eax, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4272db: add eax, 0x88 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4272e0: push ecx */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 4272e1: mov ecx, dword ptr [0x4dde80] */
	m->edx = (DWORD)(m->ecx + 0x210u);	/* 4272e7: lea edx, [ecx + 0x210] */
	{ DWORD a_ = m->ecx, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4272ed: add ecx, 0x1d0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4272f3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4272f4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4272f5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4272fbu; native_call(m, 0x4285c0u);	/* 4272f6: call 0x4285c0 */
	goto L_42732a;	/* 4272fb: jmp 0x42732a */
L_4272fd:
	m->eax = M32((DWORD)(0x4dde84u));	/* 4272fd: mov eax, dword ptr [0x4dde84] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427302: push 1 */
	m->ecx = (DWORD)(m->eax + 0xa0u);	/* 427304: lea ecx, [eax + 0xa0] */
	{ DWORD a_ = m->eax, b_ = 0x88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42730a: add eax, 0x88 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42730f: push ecx */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 427310: mov ecx, dword ptr [0x4dde80] */
	m->edx = (DWORD)(m->ecx + 0x108u);	/* 427316: lea edx, [ecx + 0x108] */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42731c: add ecx, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427322: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427323: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427324: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42732au; native_call(m, 0x4284d0u);	/* 427325: call 0x4284d0 */
L_42732a:
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42732a: add esp, 0x14 */
L_42732d:
	m->eax = M32((DWORD)(0x4de1ccu));	/* 42732d: mov eax, dword ptr [0x4de1cc] */
	m->ecx = M32((DWORD)(0x4b04f8u));	/* 427332: mov ecx, dword ptr [0x4b04f8] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 427338: cmp eax, ecx */
	if (m->zf) goto L_427446;	/* 42733a: je 0x427446 */
	{ DWORD a_ = m->eax, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 427340: cmp eax, 7 */
	if (!m->cf && !m->zf) goto L_427419;	/* 427343: ja 0x427419 */
	switch (m->eax) { case 0: goto L_427350; case 1: goto L_427375; case 2: goto L_42737c; case 3: goto L_42739e; case 4: goto L_4273a5; case 5: goto L_4273c7; case 6: goto L_4273ce; case 7: goto L_4273f0; default: abort(); }	/* 427349: jmp dword ptr [eax*4 + 0x427794] */
L_427350:
	m->edi = 0x4b063cu;	/* 427350: mov edi, 0x4b063c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427355: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 427358: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 42735a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 42735c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42735e: sub edi, ecx */
	m->eax = m->ecx;	/* 427360: mov eax, ecx */
	m->esi = m->edi;	/* 427362: mov esi, edi */
	m->edi = 0x4ddb58u;	/* 427364: mov edi, 0x4ddb58 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 427369: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42736c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42736e: mov ecx, eax */
	goto L_427410;	/* 427370: jmp 0x427410 */
L_427375:
	m->edi = 0x4b061cu;	/* 427375: mov edi, 0x4b061c */
	goto L_4273f5;	/* 42737a: jmp 0x4273f5 */
L_42737c:
	m->edi = 0x4b05fcu;	/* 42737c: mov edi, 0x4b05fc */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427381: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 427384: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 427386: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 427388: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 42738a: sub edi, ecx */
	m->eax = m->ecx;	/* 42738c: mov eax, ecx */
	m->esi = m->edi;	/* 42738e: mov esi, edi */
	m->edi = 0x4ddb58u;	/* 427390: mov edi, 0x4ddb58 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 427395: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 427398: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 42739a: mov ecx, eax */
	goto L_427410;	/* 42739c: jmp 0x427410 */
L_42739e:
	m->edi = 0x4b05dcu;	/* 42739e: mov edi, 0x4b05dc */
	goto L_4273f5;	/* 4273a3: jmp 0x4273f5 */
L_4273a5:
	m->edi = 0x4b05bcu;	/* 4273a5: mov edi, 0x4b05bc */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4273aa: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4273ad: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4273af: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4273b1: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4273b3: sub edi, ecx */
	m->eax = m->ecx;	/* 4273b5: mov eax, ecx */
	m->esi = m->edi;	/* 4273b7: mov esi, edi */
	m->edi = 0x4ddb58u;	/* 4273b9: mov edi, 0x4ddb58 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4273be: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4273c1: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4273c3: mov ecx, eax */
	goto L_427410;	/* 4273c5: jmp 0x427410 */
L_4273c7:
	m->edi = 0x4b059cu;	/* 4273c7: mov edi, 0x4b059c */
	goto L_4273f5;	/* 4273cc: jmp 0x4273f5 */
L_4273ce:
	m->edi = 0x4b057cu;	/* 4273ce: mov edi, 0x4b057c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4273d3: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4273d6: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4273d8: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4273da: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4273dc: sub edi, ecx */
	m->eax = m->ecx;	/* 4273de: mov eax, ecx */
	m->esi = m->edi;	/* 4273e0: mov esi, edi */
	m->edi = 0x4ddb58u;	/* 4273e2: mov edi, 0x4ddb58 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4273e7: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4273ea: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4273ec: mov ecx, eax */
	goto L_427410;	/* 4273ee: jmp 0x427410 */
L_4273f0:
	m->edi = 0x4b055cu;	/* 4273f0: mov edi, 0x4b055c */
L_4273f5:
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4273f5: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4273f8: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4273fa: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4273fc: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4273fe: sub edi, ecx */
	m->edx = m->ecx;	/* 427400: mov edx, ecx */
	m->esi = m->edi;	/* 427402: mov esi, edi */
	m->edi = 0x4ddb58u;	/* 427404: mov edi, 0x4ddb58 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 427409: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 42740c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 42740e: mov ecx, edx */
L_427410:
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427410: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 427413: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 427415: mov edi, dword ptr [esp + 0x10] */
L_427419:
	m->ecx = M32((DWORD)(0xa0e010u));	/* 427419: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42741f: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427421: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427423: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427425: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427427: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427429: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42742b: push 0 */
	{ DWORD v_ = 0x4ddb58u; m->esp -= 4; M32(m->esp) = v_; }	/* 42742d: push 0x4ddb58 */
	m->esp -= 4; M32(m->esp) = 0x427437u; native_call(m, 0x456be0u);	/* 427432: call 0x456be0 */
	M32((DWORD)(0x4e0c8cu)) = m->eax;	/* 427437: mov dword ptr [0x4e0c8c], eax */
	m->eax = M32((DWORD)(0x4de1ccu));	/* 42743c: mov eax, dword ptr [0x4de1cc] */
	M32((DWORD)(0x4b04f8u)) = m->eax;	/* 427441: mov dword ptr [0x4b04f8], eax */
L_427446:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427446: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x427451u; native_call(m, M32(0x4a9224u));	/* 42744b: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x4e0c8cu));	/* 427451: mov eax, dword ptr [0x4e0c8c] */
	m->ecx = m->eax;	/* 427456: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427458: and ecx, 0x800001ff */
	if (!m->sf) goto L_427468;	/* 42745e: jns 0x427468 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 427460: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 427461: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 427467: inc ecx */
L_427468:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 427468: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 427469: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42746f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 427470: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 427472: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 427478: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 42747b: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x427484u; native_call(m, 0x4566c0u);	/* 42747f: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427484: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427489: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42748e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427493: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42749eu; native_call(m, M32(0x4a9228u));	/* 427498: call dword ptr [0x4a9228] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 42749e: push 7 */
	m->esp -= 4; M32(m->esp) = 0x4274a2u; native_call(m, m->ebx);	/* 4274a0: call ebx */
	m->esi = M32((DWORD)(0x4a91d8u));	/* 4274a2: mov esi, dword ptr [0x4a91d8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4274a8: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4274aa: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4274aeu; native_call(m, m->esi);	/* 4274ac: call esi */
	m->eax = M32((DWORD)(0x4dde84u));	/* 4274ae: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 4274b3: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4274b9: add eax, 0xa0 */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4274be: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4274c4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4274c5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4274cbu; native_call(m, 0x41ef60u);	/* 4274c6: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4274cb: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4274ce: push 0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4274d0: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4274d4u; native_call(m, m->esi);	/* 4274d2: call esi */
	m->edx = M32((DWORD)(0x4dde84u));	/* 4274d4: mov edx, dword ptr [0x4dde84] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4274da: mov eax, dword ptr [0x4dde80] */
	{ DWORD a_ = m->edx, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4274df: add edx, 0xa0 */
	{ DWORD a_ = m->eax, b_ = 0xf8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4274e5: add eax, 0xf8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4274ea: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4274eb: push eax */
	m->esp -= 4; M32(m->esp) = 0x4274f1u; native_call(m, 0x41ef60u);	/* 4274ec: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4274f1: add esp, 8 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4274f4: push 1 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4274f6: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4274fau; native_call(m, m->esi);	/* 4274f8: call esi */
	m->ecx = M32((DWORD)(0x4dde84u));	/* 4274fa: mov ecx, dword ptr [0x4dde84] */
	m->edx = M32((DWORD)(0x4dde80u));	/* 427500: mov edx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->ecx, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427506: add ecx, 0xd0 */
	{ DWORD a_ = m->edx, b_ = 0xf8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42750c: add edx, 0xf8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427512: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427513: push edx */
	m->esp -= 4; M32(m->esp) = 0x427519u; native_call(m, 0x41ef60u);	/* 427514: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 427519: add esp, 8 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 42751c: push 1 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42751e: push 0 */
	m->esp -= 4; M32(m->esp) = 0x427522u; native_call(m, m->esi);	/* 427520: call esi */
	m->eax = M32((DWORD)(0x4dde84u));	/* 427522: mov eax, dword ptr [0x4dde84] */
	m->ecx = M32((DWORD)(0x4dde80u));	/* 427527: mov ecx, dword ptr [0x4dde80] */
	{ DWORD a_ = m->eax, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42752d: add eax, 0xd0 */
	{ DWORD a_ = m->ecx, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427532: add ecx, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427538: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427539: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42753fu; native_call(m, 0x41ef60u);	/* 42753a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42753f: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x427544u; native_call(m, m->ebp);	/* 427542: call ebp */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ddb98u)));	/* 427544: fld dword ptr [0x4ddb98] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 42754a: fsub dword ptr [0x4b071c] */
	MF((DWORD)(0x4ddb98u)) = (float)ST(0);	/* 427550: fst dword ptr [0x4ddb98] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 427556: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 42755c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 42755e: test ah, 1 */
	if (m->zf) goto L_427577;	/* 427561: je 0x427577 */
	M32((DWORD)(0x4ddb98u)) = 0x0u;	/* 427563: mov dword ptr [0x4ddb98], 0 */
	M32((DWORD)(0x4dde90u)) = 0xffffffffu;	/* 42756d: mov dword ptr [0x4dde90], 0xffffffff */
L_427577:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 427577: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 427579: xor esi, esi */
	m->ebx = 0x7546a4u;	/* 42757b: mov ebx, 0x7546a4 */
L_427580:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427580: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x42758bu; native_call(m, M32(0x4a9224u));	/* 427585: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 42758b: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 427590: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 427592: and edx, 0x800001ff */
	if (!m->sf) goto L_4275a2;	/* 427598: jns 0x4275a2 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 42759a: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42759b: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4275a1: inc edx */
L_4275a2:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4275a2: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4275a3: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4275a9: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4275aa: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4275b0: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4275b2: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 4275b5: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4275beu; native_call(m, 0x4566c0u);	/* 4275b9: call 0x4566c0 */
	m->edx = (DWORD)(m->ebp + 0x4u);	/* 4275be: lea edx, [ebp + 4] */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4275c1: cmp edi, edx */
	if (!m->zf) goto L_42762b;	/* 4275c3: jne 0x42762b */
	m->eax = M32((DWORD)(0x4dddc8u));	/* 4275c5: mov eax, dword ptr [0x4dddc8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4275ca: test eax, eax */
	if (!m->zf) goto L_42762b;	/* 4275cc: jne 0x42762b */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4275ce: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4275d3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4275d8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4275dd: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4275e8u; native_call(m, M32(0x4a9228u));	/* 4275e2: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x4dde8cu));	/* 4275e8: mov ecx, dword ptr [0x4dde8c] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 4275ee: mov eax, dword ptr [0x4dde80] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4275f3: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 4275f5: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4275f8: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4275fb: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xc8u);	/* 4275fc: lea edx, [esi + eax + 0xc8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427603: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x50u);	/* 427604: lea eax, [esi + eax + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427608: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427609: push eax */
	m->esp -= 4; M32(m->esp) = 0x42760fu; native_call(m, 0x4282f0u);	/* 42760a: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4de054u));	/* 42760f: mov ecx, dword ptr [0x4de054] */
	m->edx = M32((DWORD)(0x4de050u));	/* 427615: mov edx, dword ptr [0x4de050] */
	m->eax = M32((DWORD)(0x4de04cu));	/* 42761b: mov eax, dword ptr [0x4de04c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427620: push ecx */
	m->ecx = M32((DWORD)(0x4de048u));	/* 427621: mov ecx, dword ptr [0x4de048] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427627: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427628: push eax */
	goto L_427686;	/* 427629: jmp 0x427686 */
L_42762b:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 42762b: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427630: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427635: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42763a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x427645u; native_call(m, M32(0x4a9228u));	/* 42763f: call dword ptr [0x4a9228] */
	m->ecx = M32((DWORD)(0x4dde8cu));	/* 427645: mov ecx, dword ptr [0x4dde8c] */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42764b: mov eax, dword ptr [0x4dde80] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 427650: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 427652: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 427655: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427658: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xc8u);	/* 427659: lea edx, [esi + eax + 0xc8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427660: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x50u);	/* 427661: lea eax, [esi + eax + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427665: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427666: push eax */
	m->esp -= 4; M32(m->esp) = 0x42766cu; native_call(m, 0x4282f0u);	/* 427667: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4ddaecu));	/* 42766c: mov ecx, dword ptr [0x4ddaec] */
	m->edx = M32((DWORD)(0x4ddae8u));	/* 427672: mov edx, dword ptr [0x4ddae8] */
	m->eax = M32((DWORD)(0x4ddae4u));	/* 427678: mov eax, dword ptr [0x4ddae4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42767d: push ecx */
	m->ecx = M32((DWORD)(0x4ddae0u));	/* 42767e: mov ecx, dword ptr [0x4ddae0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427684: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427685: push eax */
L_427686:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427686: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 427687: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x427691u; native_call(m, 0x41f0e0u);	/* 42768c: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4dde80u));	/* 427691: mov eax, dword ptr [0x4dde80] */
	m->ecx = M32((DWORD)(0x4dde8cu));	/* 427696: mov ecx, dword ptr [0x4dde8c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42769c: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42769f: add ecx, -0x28 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xc8u);	/* 4276a2: lea edx, [esi + eax + 0xc8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4276a9: push ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4276aa: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x50u);	/* 4276ab: lea edx, [esi + eax + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4276af: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4276b0: push edx */
	m->esp -= 4; M32(m->esp) = 0x4276b6u; native_call(m, 0x4029d0u);	/* 4276b1: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4276b6: add esp, 0x10 */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 4276b9: add ebx, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 4276bf: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4276c0: add esi, 0x8c */
	{ DWORD a_ = m->ebx, b_ = 0x754824u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4276c6: cmp ebx, 0x754824 */
	if (m->sf != m->of) goto L_427580;	/* 4276cc: jl 0x427580 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4276d2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4276d7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4276dc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4276e1: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4276e6: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4276f0u; native_call(m, 0x41f0e0u);	/* 4276eb: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4276f0: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4276f3: cmp edi, 6 */
	if (m->zf || m->sf != m->of) goto L_42771f;	/* 4276f6: jle 0x42771f */
	{ DWORD a_ = m->edi, b_ = 0x12u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4276f8: cmp edi, 0x12 */
	if (m->sf == m->of) goto L_42771f;	/* 4276fb: jge 0x42771f */
	m->eax = M32((DWORD)(0x4dddc8u));	/* 4276fd: mov eax, dword ptr [0x4dddc8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 427702: test eax, eax */
	if (!m->zf) goto L_427728;	/* 427704: jne 0x427728 */
	{ DWORD v_ = 0x754824u; m->esp -= 4; M32(m->esp) = v_; }	/* 427706: push 0x754824 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 42770b: push 0x280 */
	{ DWORD v_ = 0x1bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 427710: push 0x1bc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427715: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42771cu; native_call(m, 0x4029d0u);	/* 427717: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42771c: add esp, 0x10 */
L_42771f:
	m->eax = M32((DWORD)(0x4dddc8u));	/* 42771f: mov eax, dword ptr [0x4dddc8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 427724: test eax, eax */
	if (m->zf) goto L_427741;	/* 427726: je 0x427741 */
L_427728:
	{ DWORD v_ = 0x7548a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 427728: push 0x7548a4 */
	{ DWORD v_ = 0x280u; m->esp -= 4; M32(m->esp) = v_; }	/* 42772d: push 0x280 */
	{ DWORD v_ = 0x1bcu; m->esp -= 4; M32(m->esp) = v_; }	/* 427732: push 0x1bc */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 427737: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42773eu; native_call(m, 0x4029d0u);	/* 427739: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42773e: add esp, 0x10 */
L_427741:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427741: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427746: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42774b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 427750: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42775bu; native_call(m, M32(0x4a9228u));	/* 427755: call dword ptr [0x4a9228] */
	m->eax = M32((DWORD)(0x4dde8cu));	/* 42775b: mov eax, dword ptr [0x4dde8c] */
	m->ecx = M32((DWORD)(0x4dde88u));	/* 427760: mov ecx, dword ptr [0x4dde88] */
	m->edx = M32((DWORD)(0x4dde84u));	/* 427766: mov edx, dword ptr [0x4dde84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42776c: push eax */
	m->eax = M32((DWORD)(0x4dde80u));	/* 42776d: mov eax, dword ptr [0x4dde80] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 427772: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 427773: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 427774: push eax */
	m->esp -= 4; M32(m->esp) = 0x42777au; native_call(m, 0x428a00u);	/* 427775: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42777a: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42777d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42777e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 42777f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 427780: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 427781: pop ecx */
	m->esp += 4 + 0; return;	/* 427782: ret  */
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
