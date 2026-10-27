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

static void lift_43adc0(X86 *m);

/* room_43adc0 (0x43adc0), lifted by tools/lift.py */
static void lift_43adc0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43adc0: sub esp, 0x44 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 43adc3: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 43adc8: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43adce: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43adcf: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43add0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43add1: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43add2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43add3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43add9u; native_call(m, 0x432300u);	/* 43add4: call 0x432300 */
	m->ebx = m->eax;	/* 43add9: mov ebx, eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43addb: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->ebx;	/* 43addd: mov dword ptr [esp + 0x1c], ebx */
	m->esp -= 4; M32(m->esp) = 0x43ade6u; native_call(m, 0x41ef90u);	/* 43ade1: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ade6: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x43adefu; native_call(m, M32(0x4a9218u));	/* 43ade9: call dword ptr [0x4a9218] */
	m->edi = M32((DWORD)(0x4a9228u));	/* 43adef: mov edi, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43adf5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43adfa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43adff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae04: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43ae0bu; native_call(m, m->edi);	/* 43ae09: call edi */
	m->edx = M32((DWORD)(0x4deb50u));	/* 43ae0b: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9dd4b4u));	/* 43ae11: mov eax, dword ptr [0x9dd4b4] */
	m->ecx = M32((DWORD)(0x9dd4b0u));	/* 43ae16: mov ecx, dword ptr [0x9dd4b0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae1c: push edx */
	m->edx = M32((DWORD)(0x9dd4acu));	/* 43ae1d: mov edx, dword ptr [0x9dd4ac] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae23: push eax */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43ae24: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae29: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae2a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae2b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ae31u; native_call(m, 0x427a90u);	/* 43ae2c: call 0x427a90 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae31: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae36: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae3b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae40: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae42: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43ae4cu; native_call(m, 0x41f0e0u);	/* 43ae47: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd4acu));	/* 43ae4c: mov ecx, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4b0u));	/* 43ae52: mov edx, dword ptr [0x9dd4b0] */
	{ DWORD a_ = m->edx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43ae58: add edx, -0x10 */
	m->eax = (DWORD)(m->ecx + 0x28u);	/* 43ae5b: lea eax, [ecx + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae5e: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae5f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae60: push eax */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43ae61: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ae66: add eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae69: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ae6fu; native_call(m, 0x427a40u);	/* 43ae6a: call 0x427a40 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43ae6f: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43ae75: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43ae7b: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae80: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43ae81: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae87: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae88: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae89: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ae8a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43ae94u; native_call(m, 0x41f0e0u);	/* 43ae8f: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dd4acu));	/* 43ae94: mov edx, dword ptr [0x9dd4ac] */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43ae9a: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ae9f: add esp, 0x4c */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43aea2: add edx, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43aea5: add eax, 0x20 */
	{ DWORD v_ = 0x759ca4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aea8: push 0x759ca4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aead: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aeae: push eax */
	m->esp -= 4; M32(m->esp) = 0x43aeb4u; native_call(m, 0x4028b0u);	/* 43aeaf: call 0x4028b0 */
	m->ecx = M32((DWORD)(0x9dd4acu));	/* 43aeb4: mov ecx, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43aeba: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->ecx, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43aec0: add ecx, 0x38 */
	{ DWORD v_ = 0x759d24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aec3: push 0x759d24 */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43aec8: add edx, 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aecb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aecc: push edx */
	m->esp -= 4; M32(m->esp) = 0x43aed2u; native_call(m, 0x402620u);	/* 43aecd: call 0x402620 */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43aed2: mov eax, dword ptr [0x9dd4ac] */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43aed7: mov ecx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->eax, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43aedd: add eax, 0x38 */
	{ DWORD v_ = 0x759da4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43aee0: push 0x759da4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43aee5: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43aee6: add ecx, 0x114 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43aeec: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43aef2u; native_call(m, 0x402620u);	/* 43aeed: call 0x402620 */
	m->edx = M32((DWORD)(0x9dd4acu));	/* 43aef2: mov edx, dword ptr [0x9dd4ac] */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43aef8: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->edx, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43aefd: add edx, 0x38 */
	{ DWORD v_ = 0x759e24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43af00: push 0x759e24 */
	{ DWORD a_ = m->eax, b_ = 0x164u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43af05: add eax, 0x164 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43af0a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43af0b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43af11u; native_call(m, 0x402620u);	/* 43af0c: call 0x402620 */
	m->ecx = M32((DWORD)(0x9dd4acu));	/* 43af11: mov ecx, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43af17: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->ecx, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43af1d: add ecx, 0x38 */
	{ DWORD v_ = 0x759ea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43af20: push 0x759ea4 */
	{ DWORD a_ = m->edx, b_ = 0x1b4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43af25: add edx, 0x1b4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43af2b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43af2c: push edx */
	m->esp -= 4; M32(m->esp) = 0x43af32u; native_call(m, 0x402620u);	/* 43af2d: call 0x402620 */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43af32: mov eax, dword ptr [0x9dd4ac] */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43af37: mov ecx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->eax, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43af3d: add eax, 0x38 */
	{ DWORD v_ = 0x759f24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43af40: push 0x759f24 */
	{ DWORD a_ = m->ecx, b_ = 0x1fcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43af45: add ecx, 0x1fc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43af4b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43af4c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43af52u; native_call(m, 0x402620u);	/* 43af4d: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43af52: add esp, 0x48 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43af55: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43af5a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43af5f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43af64: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43af66: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43af70u; native_call(m, 0x41f0e0u);	/* 43af6b: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dd4acu));	/* 43af70: mov edx, dword ptr [0x9dd4ac] */
	m->ecx = M32((DWORD)(0x9dd4b0u));	/* 43af76: mov ecx, dword ptr [0x9dd4b0] */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43af7c: add ecx, -0x10 */
	m->eax = (DWORD)(m->edx + 0x50u);	/* 43af7f: lea eax, [edx + 0x50] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43af82: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43af88: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43af89: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43af8a: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43af8d: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43af8e: push edx */
	m->esp -= 4; M32(m->esp) = 0x43af94u; native_call(m, 0x427a40u);	/* 43af8f: call 0x427a40 */
	m->eax = M32((DWORD)(0x9dd4b4u));	/* 43af94: mov eax, dword ptr [0x9dd4b4] */
	m->ecx = M32((DWORD)(0x9dd4b0u));	/* 43af99: mov ecx, dword ptr [0x9dd4b0] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43af9f: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->eax, b_ = 0xffffffa2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43afa5: add eax, -0x5e */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43afa8: add ecx, -0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43afab: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43afac: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43afad: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43afb0: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43afb1: push edx */
	m->esp -= 4; M32(m->esp) = 0x43afb7u; native_call(m, 0x427a40u);	/* 43afb2: call 0x427a40 */
	m->eax = M32((DWORD)(0x9dd330u));	/* 43afb7: mov eax, dword ptr [0x9dd330] */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43afbc: add esp, 0x34 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43afbf: test eax, eax */
	if (m->zf) goto L_43b4a4;	/* 43afc1: je 0x43b4a4 */
	m->eax = M32((DWORD)(0x67ef30u));	/* 43afc7: mov eax, dword ptr [0x67ef30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43afcc: test eax, eax */
	if (m->zf) goto L_43b4a4;	/* 43afce: je 0x43b4a4 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 43afd4: xor ebp, ebp */
	m->ebx = 0x60u;	/* 43afd6: mov ebx, 0x60 */
	goto L_43afe3;	/* 43afdb: jmp 0x43afe3 */
L_43afdd:
	m->edi = M32((DWORD)(0x4a9228u));	/* 43afdd: mov edi, dword ptr [0x4a9228] */
L_43afe3:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x67ef30u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43afe3: cmp ebp, dword ptr [0x67ef30] */
	if (m->sf == m->of) goto L_43b3a6;	/* 43afe9: jge 0x43b3a6 */
	m->eax = M32((DWORD)(0x680bb0u));	/* 43afef: mov eax, dword ptr [0x680bb0] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43aff4: add eax, ebp */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 43aff6: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 43aff9: lea edx, [eax + ecx*4] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx*2 + 0x908807u))) & 0xff) << 0);	/* 43affc: mov al, byte ptr [edx*2 + 0x908807] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43b003: test al, al */
	if (m->zf) goto L_43b118;	/* 43b005: je 0x43b118 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b00b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43b016u; native_call(m, M32(0x4a9224u));	/* 43b010: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d448u));	/* 43b016: mov eax, dword ptr [0x76d448] */
	m->ecx = m->eax;	/* 43b01b: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b01d: and ecx, 0x800001ff */
	if (!m->sf) goto L_43b02d;	/* 43b023: jns 0x43b02d */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43b025: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b026: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43b02c: inc ecx */
L_43b02d:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43b02d: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43b02e: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b034: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b035: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43b037: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43b03d: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43b040: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43b049u; native_call(m, 0x4566c0u);	/* 43b044: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b049: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b04e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b053: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b058: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43b05fu; native_call(m, m->edi);	/* 43b05d: call edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b05f: push 7 */
	m->esp -= 4; M32(m->esp) = 0x43b067u; native_call(m, M32(0x4a921cu));	/* 43b061: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(0x4a920cu));	/* 43b067: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b06d: push 0x3f500000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b072: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43b076u; native_call(m, m->esi);	/* 43b074: call esi */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b076: mov eax, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b07b: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b081: add edx, 0xc */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0xffffffffu);	/* 43b084: lea ecx, [ebx + eax - 1] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b088: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b089: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b08fu; native_call(m, 0x41ef60u);	/* 43b08a: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b08f: add esp, 8 */
	{ DWORD v_ = 0x3f500000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b092: push 0x3f500000 */
	{ DWORD v_ = 0x3d800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b097: push 0x3d800000 */
	m->esp -= 4; M32(m->esp) = 0x43b09eu; native_call(m, m->esi);	/* 43b09c: call esi */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b09e: mov eax, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b0a3: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->edx, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b0a9: add edx, 0x1c */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0xffffffffu);	/* 43b0ac: lea ecx, [ebx + eax - 1] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0b0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0b1: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b0b7u; native_call(m, 0x41ef60u);	/* 43b0b2: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b0b7: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0ba: push 0x3f600000 */
	{ DWORD v_ = 0x3d800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0bf: push 0x3d800000 */
	m->esp -= 4; M32(m->esp) = 0x43b0c6u; native_call(m, m->esi);	/* 43b0c4: call esi */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b0c6: mov eax, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b0cb: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->edx, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b0d1: add edx, 0x1c */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0xfu);	/* 43b0d4: lea ecx, [ebx + eax + 0xf] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0d8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0d9: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b0dfu; native_call(m, 0x41ef60u);	/* 43b0da: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b0df: add esp, 8 */
	{ DWORD v_ = 0x3f600000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0e2: push 0x3f600000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0e7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x43b0ebu; native_call(m, m->esi);	/* 43b0e9: call esi */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b0eb: mov eax, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b0f0: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b0f6: add edx, 0xc */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0xfu);	/* 43b0f9: lea ecx, [ebx + eax + 0xf] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0fd: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b0fe: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b104u; native_call(m, 0x41ef60u);	/* 43b0ff: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b104: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x43b10du; native_call(m, M32(0x4a9220u));	/* 43b107: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b10d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43b118u; native_call(m, M32(0x4a922cu));	/* 43b112: call dword ptr [0x4a922c] */
L_43b118:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b118: push 0x3f800000 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43b11d: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43b122: push 0x3f4ccccd */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b127: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b129: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43b133u; native_call(m, 0x41f0e0u);	/* 43b12e: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x680bb0u));	/* 43b133: mov eax, dword ptr [0x680bb0] */
	m->ecx = M32((DWORD)(0x76d41cu));	/* 43b138: mov ecx, dword ptr [0x76d41c] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b13e: add eax, ebp */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b140: add esp, 0x14 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43b143: cmp ecx, eax */
	if (!m->zf) goto L_43b168;	/* 43b145: jne 0x43b168 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b147: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b14c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b151: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b156: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b15b: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43b165u; native_call(m, 0x41f0e0u);	/* 43b160: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b165: add esp, 0x14 */
L_43b168:
	m->ecx = 0xcu;	/* 43b168: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43b16d: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x20u);	/* 43b16f: lea edi, [esp + 0x20] */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b173: push 0x20 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43b175: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x680bb0u));	/* 43b177: mov ecx, dword ptr [0x680bb0] */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43b17d: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->ecx + m->ebp*1 + 0x0u);	/* 43b17f: lea eax, [ecx + ebp] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 43b182: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 43b185: lea eax, [eax + edx*4] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 43b188: lea edx, [esp + 0x24] */
	m->ecx = (DWORD)(m->eax*2 + 0x9087c4u);	/* 43b18c: lea ecx, [eax*2 + 0x9087c4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b193: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b194: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b19au; native_call(m, 0x49ea80u);	/* 43b195: call 0x49ea80 */
	m->ecx = M32((DWORD)(0x9dd4acu));	/* 43b19a: mov ecx, dword ptr [0x9dd4ac] */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 43b1a0: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b1a4: push eax */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43b1a5: mov eax, dword ptr [0x9dd4a8] */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x0u);	/* 43b1aa: lea edx, [ebx + ecx] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b1ad: add eax, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b1b0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b1b1: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b1b7u; native_call(m, 0x402620u);	/* 43b1b2: call 0x402620 */
	m->ecx = M32((DWORD)(0x680bb0u));	/* 43b1b7: mov ecx, dword ptr [0x680bb0] */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b1bd: add esp, 0x18 */
	m->eax = (DWORD)(m->ecx + m->ebp*1 + 0x0u);	/* 43b1c0: lea eax, [ecx + ebp] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 43b1c3: lea edx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 43b1c6: lea edx, [eax + edx*4] */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43b1c9: shl edx, 1 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x9087e4u))) & 0xff) << 0);	/* 43b1cb: mov al, byte ptr [edx + 0x9087e4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43b1d1: test al, al */
	if (m->zf) goto L_43b1fa;	/* 43b1d3: je 0x43b1fa */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b1d5: mov eax, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b1da: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD v_ = 0x75c1a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b1e0: push 0x75c1a4 */
	{ DWORD a_ = m->edx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b1e5: add edx, 0x114 */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0x0u);	/* 43b1eb: lea ecx, [ebx + eax] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b1ee: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b1ef: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b1f5u; native_call(m, 0x402620u);	/* 43b1f0: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b1f5: add esp, 0xc */
	goto L_43b248;	/* 43b1f8: jmp 0x43b248 */
L_43b1fa:
	m->ecx = 0xcu;	/* 43b1fa: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43b1ff: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x20u);	/* 43b201: lea edi, [esp + 0x20] */
	{ DWORD v_ = 0xdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43b205: push 0xd */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43b207: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43b209: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->edx + 0x9087e5u)));	/* 43b20b: movsx eax, byte ptr [edx + 0x9087e5] */
	{ DWORD a_ = m->eax, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43b212: shl eax, 5 */
	{ DWORD a_ = m->eax, b_ = 0x907b30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b215: add eax, 0x907b30 */
	m->ecx = (DWORD)(m->esp + 0x24u);	/* 43b21a: lea ecx, [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b21e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b21f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43b225u; native_call(m, 0x49ea80u);	/* 43b220: call 0x49ea80 */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b225: mov eax, dword ptr [0x9dd4ac] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 43b22a: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b22e: push edx */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b22f: mov edx, dword ptr [0x9dd4a8] */
	m->ecx = (DWORD)(m->ebx + m->eax*1 + 0x0u);	/* 43b235: lea ecx, [ebx + eax] */
	{ DWORD a_ = m->edx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b238: add edx, 0x114 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b23e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b23f: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b245u; native_call(m, 0x402620u);	/* 43b240: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b245: add esp, 0x18 */
L_43b248:
	m->eax = M32((DWORD)(0x680bb0u));	/* 43b248: mov eax, dword ptr [0x680bb0] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b24d: add eax, ebp */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 43b24f: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 43b252: lea edx, [eax + ecx*4] */
	m->ecx = M32((DWORD)(0x9dd4acu));	/* 43b255: mov ecx, dword ptr [0x9dd4ac] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->edx*2 + 0x9087ecu)));	/* 43b25b: movsx eax, byte ptr [edx*2 + 0x9087ec] */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43b263: shl eax, 7 */
	{ DWORD a_ = m->eax, b_ = 0x7673a4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b266: add eax, 0x7673a4 */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x0u);	/* 43b26b: lea edx, [ebx + ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b26e: push eax */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43b26f: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->eax, b_ = 0x182u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b274: add eax, 0x182 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b279: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b27a: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b280u; native_call(m, 0x402620u);	/* 43b27b: call 0x402620 */
	m->edx = M32((DWORD)(0x680bb0u));	/* 43b280: mov edx, dword ptr [0x680bb0] */
	m->ecx = 0xcu;	/* 43b286: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43b28b: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x2cu);	/* 43b28d: lea edi, [esp + 0x2c] */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43b291: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43b293: stosw word ptr es:[edi], ax */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 43b295: lea ecx, [esp + 0x2c] */
	m->eax = (DWORD)(m->edx + m->ebp*1 + 0x0u);	/* 43b299: lea eax, [edx + ebp] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43b29c: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b29e: push ecx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 43b29f: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 43b2a2: lea edx, [eax + ecx*4] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->edx*2 + 0x9087e7u)));	/* 43b2a5: movsx eax, byte ptr [edx*2 + 0x9087e7] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b2ad: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b2b3u; native_call(m, 0x49fb53u);	/* 43b2ae: call 0x49fb53 */
	m->edx = M32((DWORD)(0x680bb0u));	/* 43b2b3: mov edx, dword ptr [0x680bb0] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 43b2b9: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43b2bd: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b2bf: push ecx */
	m->eax = (DWORD)(m->edx + m->ebp*1 + 0x0u);	/* 43b2c0: lea eax, [edx + ebp] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 43b2c3: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 43b2c6: lea edx, [eax + ecx*4] */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->edx*2 + 0x9087e6u)));	/* 43b2c9: movsx eax, byte ptr [edx*2 + 0x9087e6] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b2d1: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b2d7u; native_call(m, 0x49fb53u);	/* 43b2d2: call 0x49fb53 */
	m->edi = 0x4ad568u;	/* 43b2d7: mov edi, 0x4ad568 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b2dc: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43b2df: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 43b2e1: lea edx, [esp + 0x44] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b2e5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43b2e7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43b2e9: sub edi, ecx */
	m->esi = m->edi;	/* 43b2eb: mov esi, edi */
	m->edi = m->edx;	/* 43b2ed: mov edi, edx */
	m->edx = m->ecx;	/* 43b2ef: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b2f1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b2f4: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 43b2f6: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43b2f8: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43b2f9: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43b2fc: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43b2fe: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x44u);	/* 43b300: lea edx, [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b304: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43b307: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x38u);	/* 43b309: lea edi, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b30d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b310: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43b312: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43b314: sub edi, ecx */
	m->esi = m->edi;	/* 43b316: mov esi, edi */
	m->edi = m->edx;	/* 43b318: mov edi, edx */
	m->edx = m->ecx;	/* 43b31a: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b31c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b31f: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 43b321: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43b323: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43b324: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43b327: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43b329: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x44u);	/* 43b32b: lea eax, [esp + 0x44] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b32f: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b332: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43b333: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd4acu));	/* 43b335: mov ecx, dword ptr [0x9dd4ac] */
	m->edx = (DWORD)(m->ebx + m->ecx*1 + 0x0u);	/* 43b33b: lea edx, [ebx + ecx] */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43b33e: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b343: push edx */
	{ DWORD a_ = m->eax, b_ = 0x1bcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b344: add eax, 0x1bc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b349: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b34fu; native_call(m, 0x402620u);	/* 43b34a: call 0x402620 */
	m->edx = M32((DWORD)(0x680bb0u));	/* 43b34f: mov edx, dword ptr [0x680bb0] */
	m->ecx = (DWORD)(m->esp + 0x50u);	/* 43b355: lea ecx, [esp + 0x50] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43b359: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b35b: push ecx */
	m->eax = (DWORD)(m->edx + m->ebp*1 + 0x0u);	/* 43b35c: lea eax, [edx + ebp] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 43b35f: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 43b362: lea edx, [eax + ecx*4] */
	m->eax = M32((DWORD)(m->edx*2 + 0x9087e8u));	/* 43b365: mov eax, dword ptr [edx*2 + 0x9087e8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b36c: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b372u; native_call(m, 0x49fb53u);	/* 43b36d: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9dd4acu));	/* 43b372: mov edx, dword ptr [0x9dd4ac] */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 43b378: lea ecx, [esp + 0x5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b37c: push ecx */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43b37d: mov ecx, dword ptr [0x9dd4a8] */
	m->eax = (DWORD)(m->ebx + m->edx*1 + 0x0u);	/* 43b383: lea eax, [ebx + edx] */
	{ DWORD a_ = m->ecx, b_ = 0x200u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b386: add ecx, 0x200 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b38c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b38d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43b393u; native_call(m, 0x402620u);	/* 43b38e: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b393: add esp, 0x48 */
	{ DWORD a_ = m->ebx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 43b396: add ebx, 0x18 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 43b399: inc ebp */
	{ DWORD a_ = m->ebx, b_ = 0x138u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43b39a: cmp ebx, 0x138 */
	if (m->sf != m->of) goto L_43afdd;	/* 43b3a0: jl 0x43afdd */
L_43b3a6:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b3a6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b3ab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b3b0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b3b5: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b3ba: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43b3c4u; native_call(m, 0x41f0e0u);	/* 43b3bf: call 0x41f0e0 */
	m->ecx = 0xcu;	/* 43b3c4: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43b3c9: xor eax, eax */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 43b3cb: lea edi, [esp + 0x34] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43b3cf: xor edx, edx */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43b3d1: rep stosd dword ptr es:[edi], eax */
	m->ecx = M32((DWORD)(0x680bb8u));	/* 43b3d3: mov ecx, dword ptr [0x680bb8] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 43b3d9: mov dword ptr [esp + 0x28], edx */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43b3dd: stosw word ptr es:[edi], ax */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 43b3df: lea eax, [esp + 0x34] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43b3e3: push 0xa */
	M32((DWORD)(m->esp + 0x30u)) = m->edx;	/* 43b3e5: mov dword ptr [esp + 0x30], edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b3e9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b3ea: push ecx */
	M16((DWORD)(m->esp + 0x3cu)) = (WORD)((m->edx & 0xffff));	/* 43b3eb: mov word ptr [esp + 0x3c], dx */
	m->esp -= 4; M32(m->esp) = 0x43b3f5u; native_call(m, 0x49fb53u);	/* 43b3f0: call 0x49fb53 */
	m->edi = 0x4ad564u;	/* 43b3f5: mov edi, 0x4ad564 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b3fa: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43b3fd: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 43b3ff: lea edx, [esp + 0x40] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b403: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43b405: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43b407: sub edi, ecx */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43b409: push 0xa */
	m->esi = m->edi;	/* 43b40b: mov esi, edi */
	m->ebx = m->ecx;	/* 43b40d: mov ebx, ecx */
	m->edi = m->edx;	/* 43b40f: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b411: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b414: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 43b416: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43b418: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43b419: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43b41c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 43b41e: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 43b420: lea eax, [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b424: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b427: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43b428: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0b358u));	/* 43b42a: mov ecx, dword ptr [0xa0b358] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b430: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43b436u; native_call(m, 0x49fb53u);	/* 43b431: call 0x49fb53 */
	m->edi = (DWORD)(m->esp + 0x40u);	/* 43b436: lea edi, [esp + 0x40] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b43a: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43b43d: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 43b43f: lea edx, [esp + 0x4c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b443: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43b445: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43b447: sub edi, ecx */
	m->esi = m->edi;	/* 43b449: mov esi, edi */
	m->ebx = m->ecx;	/* 43b44b: mov ebx, ecx */
	m->edi = m->edx;	/* 43b44d: mov edi, edx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b44f: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b452: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->ebx;	/* 43b454: mov ecx, ebx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43b456: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43b457: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43b45a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->ebx;	/* 43b45c: mov ecx, ebx */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 43b45e: lea eax, [esp + 0x4c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b462: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b465: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43b466: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd4b4u));	/* 43b468: mov ecx, dword ptr [0x9dd4b4] */
	m->edi = (DWORD)(m->esp + 0x50u);	/* 43b46e: lea edi, [esp + 0x50] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffa8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b472: add ecx, -0x58 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43b475: xor eax, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b477: push ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b478: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43b47b: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43b47d: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43b47f: dec ecx */
	m->edx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 43b480: lea edx, [ecx + ecx*2] */
	m->eax = (DWORD)(m->ecx + m->edx*4 + 0x0u);	/* 43b483: lea eax, [ecx + edx*4] */
	m->ecx = M32((DWORD)(0x9dd4b0u));	/* 43b486: mov ecx, dword ptr [0x9dd4b0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b48c: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b48e: sub ecx, 0x3c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b491: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43b497u; native_call(m, 0x4028b0u);	/* 43b492: call 0x4028b0 */
	m->edi = M32((DWORD)(0x4a9228u));	/* 43b497: mov edi, dword ptr [0x4a9228] */
	m->ebx = M32((DWORD)(m->esp + 0x48u));	/* 43b49d: mov ebx, dword ptr [esp + 0x48] */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b4a1: add esp, 0x38 */
L_43b4a4:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4a4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4a9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4ae: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4b3: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4b5: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43b4bfu; native_call(m, 0x41f0e0u);	/* 43b4ba: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dd4b4u));	/* 43b4bf: mov edx, dword ptr [0x9dd4b4] */
	m->ecx = M32((DWORD)(0x9dd4b0u));	/* 43b4c5: mov ecx, dword ptr [0x9dd4b0] */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b4cb: add ecx, -0x10 */
	m->eax = (DWORD)(m->edx + 0xffffffc0u);	/* 43b4ce: lea eax, [edx - 0x40] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b4d1: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4d7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4d8: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b4d9: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4dc: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4dd: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b4e3u; native_call(m, 0x427a40u);	/* 43b4de: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b4e3: add esp, 0x24 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43b4e6: xor esi, esi */
L_43b4e8:
	m->ebp = M32((DWORD)(0x4a9224u));	/* 43b4e8: mov ebp, dword ptr [0x4a9224] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b4ee: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43b4f5u; native_call(m, m->ebp);	/* 43b4f3: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43b4f5: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 43b4fa: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b4fc: and ecx, 0x800001ff */
	if (!m->sf) goto L_43b50c;	/* 43b502: jns 0x43b50c */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43b504: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43b505: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43b50b: inc ecx */
L_43b50c:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43b50c: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43b50d: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b513: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b514: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43b516: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43b51c: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43b51f: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43b528u; native_call(m, 0x4566c0u);	/* 43b523: call 0x4566c0 */
	{ DWORD a_ = m->ebx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43b528: cmp ebx, esi */
	if (!m->zf) goto L_43b669;	/* 43b52a: jne 0x43b669 */
	m->eax = M32((DWORD)(0x9dd6a0u));	/* 43b530: mov eax, dword ptr [0x9dd6a0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43b535: test eax, eax */
	if (m->zf) goto L_43b580;	/* 43b537: je 0x43b580 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43b539: cmp esi, 2 */
	if (!m->zf) goto L_43b669;	/* 43b53c: jne 0x43b669 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b542: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b547: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b54c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b551: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43b558u; native_call(m, m->edi);	/* 43b556: call edi */
	m->eax = M32((DWORD)(0x9dd4b4u));	/* 43b558: mov eax, dword ptr [0x9dd4b4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b55d: push 1 */
	m->ecx = (DWORD)(m->eax + 0xffffffeeu);	/* 43b55f: lea ecx, [eax - 0x12] */
	{ DWORD a_ = m->eax, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b562: add eax, -0x32 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b565: push ecx */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43b566: mov ecx, dword ptr [0x9dd4a8] */
	m->edx = (DWORD)(m->ecx + 0x1b0u);	/* 43b56c: lea edx, [ecx + 0x1b0] */
	{ DWORD a_ = m->ecx, b_ = 0x138u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b572: add ecx, 0x138 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b578: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b579: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b57a: push ecx */
	goto L_43b649;	/* 43b57b: jmp 0x43b649 */
L_43b580:
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43b580: test esi, esi */
	if (!m->zf) goto L_43b603;	/* 43b582: jne 0x43b603 */
	m->eax = M32((DWORD)(0x67ef30u));	/* 43b584: mov eax, dword ptr [0x67ef30] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43b589: test eax, eax */
	if (m->zf) goto L_43b5c8;	/* 43b58b: je 0x43b5c8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b58d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b592: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b597: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b59c: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43b5a3u; native_call(m, m->edi);	/* 43b5a1: call edi */
	m->eax = M32((DWORD)(0x9dd4b4u));	/* 43b5a3: mov eax, dword ptr [0x9dd4b4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5a8: push 1 */
	m->ecx = (DWORD)(m->eax + 0xffffffeeu);	/* 43b5aa: lea ecx, [eax - 0x12] */
	{ DWORD a_ = m->eax, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b5ad: add eax, -0x32 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5b0: push ecx */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43b5b1: mov ecx, dword ptr [0x9dd4a8] */
	m->edx = (DWORD)(m->ecx + 0x98u);	/* 43b5b7: lea edx, [ecx + 0x98] */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b5bd: add ecx, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5c0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5c1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5c2: push ecx */
	goto L_43b649;	/* 43b5c3: jmp 0x43b649 */
L_43b5c8:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5c8: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5cd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5d2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5d7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43b5deu; native_call(m, m->edi);	/* 43b5dc: call edi */
	m->eax = M32((DWORD)(0x9dd4b4u));	/* 43b5de: mov eax, dword ptr [0x9dd4b4] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5e3: push 1 */
	m->ecx = (DWORD)(m->eax + 0xffffffeeu);	/* 43b5e5: lea ecx, [eax - 0x12] */
	{ DWORD a_ = m->eax, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b5e8: add eax, -0x32 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5eb: push ecx */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43b5ec: mov ecx, dword ptr [0x9dd4a8] */
	m->edx = (DWORD)(m->ecx + 0x98u);	/* 43b5f2: lea edx, [ecx + 0x98] */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b5f8: add ecx, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5fb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5fc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b5fd: push ecx */
	goto L_43b6af;	/* 43b5fe: jmp 0x43b6af */
L_43b603:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b603: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b608: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b60d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b612: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43b619u; native_call(m, m->edi);	/* 43b617: call edi */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b619: mov edx, dword ptr [0x9dd4a8] */
	m->eax = (DWORD)(m->esi*8 + 0x0u);	/* 43b61f: lea eax, [esi*8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b626: sub eax, esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b628: push 1 */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43b62a: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 43b62d: lea eax, [edx + ecx*4] */
	m->ecx = M32((DWORD)(0x9dd4b4u));	/* 43b630: mov ecx, dword ptr [0x9dd4b4] */
	m->edx = (DWORD)(m->ecx + 0xffffffeeu);	/* 43b636: lea edx, [ecx - 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b639: add ecx, -0x32 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b63c: push edx */
	m->edx = (DWORD)(m->eax + 0x98u);	/* 43b63d: lea edx, [eax + 0x98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b643: push edx */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b644: add eax, 0x20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b647: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b648: push eax */
L_43b649:
	m->esp -= 4; M32(m->esp) = 0x43b64eu; native_call(m, 0x4282f0u);	/* 43b649: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9dceccu));	/* 43b64e: mov eax, dword ptr [0x9dcecc] */
	m->ecx = M32((DWORD)(0x9dcec8u));	/* 43b653: mov ecx, dword ptr [0x9dcec8] */
	m->edx = M32((DWORD)(0x9dcec4u));	/* 43b659: mov edx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b65f: push eax */
	m->eax = M32((DWORD)(0x9dcec0u));	/* 43b660: mov eax, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b665: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b666: push edx */
	goto L_43b6cd;	/* 43b667: jmp 0x43b6cd */
L_43b669:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43b669: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b66e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b673: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b678: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43b67fu; native_call(m, m->edi);	/* 43b67d: call edi */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b67f: mov edx, dword ptr [0x9dd4a8] */
	m->eax = (DWORD)(m->esi*8 + 0x0u);	/* 43b685: lea eax, [esi*8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b68c: sub eax, esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b68e: push 1 */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43b690: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 43b693: lea eax, [edx + ecx*4] */
	m->ecx = M32((DWORD)(0x9dd4b4u));	/* 43b696: mov ecx, dword ptr [0x9dd4b4] */
	m->edx = (DWORD)(m->ecx + 0xffffffeeu);	/* 43b69c: lea edx, [ecx - 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b69f: add ecx, -0x32 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6a2: push edx */
	m->edx = (DWORD)(m->eax + 0x98u);	/* 43b6a3: lea edx, [eax + 0x98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6a9: push edx */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b6aa: add eax, 0x20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6ad: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6ae: push eax */
L_43b6af:
	m->esp -= 4; M32(m->esp) = 0x43b6b4u; native_call(m, 0x4282f0u);	/* 43b6af: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9dd344u));	/* 43b6b4: mov eax, dword ptr [0x9dd344] */
	m->ecx = M32((DWORD)(0x9dd340u));	/* 43b6b9: mov ecx, dword ptr [0x9dd340] */
	m->edx = M32((DWORD)(0x9dd33cu));	/* 43b6bf: mov edx, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6c5: push eax */
	m->eax = M32((DWORD)(0x9dd338u));	/* 43b6c6: mov eax, dword ptr [0x9dd338] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6cb: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6cc: push edx */
L_43b6cd:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6cd: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6ce: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43b6d8u; native_call(m, 0x41f0e0u);	/* 43b6d3: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd6b4u));	/* 43b6d8: mov eax, dword ptr [0x9dd6b4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b6dd: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43b6e0: test eax, eax */
	if (m->zf) goto L_43b756;	/* 43b6e2: je 0x43b756 */
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6e4: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6e9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6ee: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b6f3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43b6fau; native_call(m, m->edi);	/* 43b6f8: call edi */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b6fa: mov edx, dword ptr [0x9dd4a8] */
	m->eax = (DWORD)(m->esi*8 + 0x0u);	/* 43b700: lea eax, [esi*8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b707: sub eax, esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b709: push 1 */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43b70b: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 43b70e: lea eax, [edx + ecx*4] */
	m->ecx = M32((DWORD)(0x9dd4b4u));	/* 43b711: mov ecx, dword ptr [0x9dd4b4] */
	m->edx = (DWORD)(m->ecx + 0xffffffeeu);	/* 43b717: lea edx, [ecx - 0x12] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffceu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b71a: add ecx, -0x32 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b71d: push edx */
	m->edx = (DWORD)(m->eax + 0x98u);	/* 43b71e: lea edx, [eax + 0x98] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b724: push edx */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b725: add eax, 0x20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b728: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b729: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b72fu; native_call(m, 0x4282f0u);	/* 43b72a: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9dd344u));	/* 43b72f: mov eax, dword ptr [0x9dd344] */
	m->ecx = M32((DWORD)(0x9dd340u));	/* 43b734: mov ecx, dword ptr [0x9dd340] */
	m->edx = M32((DWORD)(0x9dd33cu));	/* 43b73a: mov edx, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b740: push eax */
	m->eax = M32((DWORD)(0x9dd338u));	/* 43b741: mov eax, dword ptr [0x9dd338] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b746: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b747: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b748: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b749: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43b753u; native_call(m, 0x41f0e0u);	/* 43b74e: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b753: add esp, 0x28 */
L_43b756:
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b756: mov edx, dword ptr [0x9dd4a8] */
	m->eax = (DWORD)(m->esi*8 + 0x0u);	/* 43b75c: lea eax, [esi*8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b763: sub eax, esi */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43b765: lea ecx, [eax + eax*4] */
	m->eax = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 43b768: lea eax, [edx + ecx*4] */
	m->ecx = m->esi;	/* 43b76b: mov ecx, esi */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43b76d: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x759fa4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b770: add ecx, 0x759fa4 */
	m->edx = (DWORD)(m->eax + 0x98u);	/* 43b776: lea edx, [eax + 0x98] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b77c: push ecx */
	m->ecx = M32((DWORD)(0x9dd4b4u));	/* 43b77d: mov ecx, dword ptr [0x9dd4b4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b783: add ecx, -0x2a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b786: push edx */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b787: add eax, 0x20 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b78a: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b78b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b791u; native_call(m, 0x4029d0u);	/* 43b78c: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b791: add esp, 0x10 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 43b794: inc esi */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43b795: cmp esi, 4 */
	if (m->sf != m->of) goto L_43b4e8;	/* 43b798: jl 0x43b4e8 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b79e: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43b7a5u; native_call(m, m->ebp);	/* 43b7a3: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43b7a5: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 43b7aa: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43b7ac: and edx, 0x800001ff */
	if (!m->sf) goto L_43b7bc;	/* 43b7b2: jns 0x43b7bc */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 43b7b4: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43b7b5: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 43b7bb: inc edx */
L_43b7bc:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b7bc: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43b7bd: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43b7c3: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43b7c4: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b7ca: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43b7cc: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 43b7cf: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43b7d8u; native_call(m, 0x4566c0u);	/* 43b7d3: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b7d8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b7dd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b7e2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b7e7: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43b7eeu; native_call(m, m->edi);	/* 43b7ec: call edi */
	{ DWORD a_ = m->ebx, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43b7ee: cmp ebx, 0xd */
	if (!m->zf) goto L_43bba7;	/* 43b7f1: jne 0x43bba7 */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b7f7: mov eax, dword ptr [0x9dd4ac] */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43b7fc: mov ecx, dword ptr [0x9dd4a8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b802: push 1 */
	m->edx = (DWORD)(m->eax + 0xaeu);	/* 43b804: lea edx, [eax + 0xae] */
	{ DWORD a_ = m->eax, b_ = 0x6eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b80a: add eax, 0x6e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b80d: push edx */
	m->edx = (DWORD)(m->ecx + 0x246u);	/* 43b80e: lea edx, [ecx + 0x246] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b814: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x226u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b815: add ecx, 0x226 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b81b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b81c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43b822u; native_call(m, 0x4286b0u);	/* 43b81d: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b822: add esp, 0x14 */
L_43b825:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b825: push 0 */
L_43b827:
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b827: mov eax, dword ptr [0x9dd4ac] */
	m->ecx = (DWORD)(m->eax + 0xfeu);	/* 43b82c: lea ecx, [eax + 0xfe] */
	{ DWORD a_ = m->eax, b_ = 0xbeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b832: add eax, 0xbe */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b837: push ecx */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43b838: mov ecx, dword ptr [0x9dd4a8] */
	m->edx = (DWORD)(m->ecx + 0x246u);	/* 43b83e: lea edx, [ecx + 0x246] */
	{ DWORD a_ = m->ecx, b_ = 0x226u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b844: add ecx, 0x226 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b84a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b84b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b84c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43b852u; native_call(m, 0x4287a0u);	/* 43b84d: call 0x4287a0 */
	m->ebx = M32((DWORD)(0x4a922cu));	/* 43b852: mov ebx, dword ptr [0x4a922c] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b858: add esp, 0x14 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b85b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43b862u; native_call(m, m->ebx);	/* 43b860: call ebx */
	m->eax = M32((DWORD)(0x9dd6a0u));	/* 43b862: mov eax, dword ptr [0x9dd6a0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43b867: test eax, eax */
	if (!m->zf) goto L_43b874;	/* 43b869: jne 0x43b874 */
	m->eax = M32((DWORD)(0x9dd3fcu));	/* 43b86b: mov eax, dword ptr [0x9dd3fc] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43b870: test eax, eax */
	if (m->zf) goto L_43b8d6;	/* 43b872: je 0x43b8d6 */
L_43b874:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dba80u)));	/* 43b874: fld dword ptr [0x4dba80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9438u));	/* 43b87a: fmul dword ptr [0x4a9438] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 43b880: call 0x49ec14 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43b885: cdq  */
	m->ecx = 0xfu;	/* 43b886: mov ecx, 0xf */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 43b88b: idiv ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b88d: push ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 43b88e: mov dword ptr [esp + 0x14], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x14u)));	/* 43b892: fild dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9434u));	/* 43b896: fmul dword ptr [0x4a9434] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43b89c: fstp dword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b89f: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8a1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8a6: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8a8: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43b8b2u; native_call(m, 0x41f0e0u);	/* 43b8ad: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd4b4u));	/* 43b8b2: mov eax, dword ptr [0x9dd4b4] */
	m->edx = M32((DWORD)(0x9dd4b0u));	/* 43b8b7: mov edx, dword ptr [0x9dd4b0] */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43b8bd: mov ecx, dword ptr [0x9dd4a8] */
	{ DWORD v_ = 0x75a1a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8c3: push 0x75a1a4 */
	{ DWORD a_ = m->eax, b_ = 0xffffffa9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b8c8: add eax, -0x57 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8cb: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8cc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8cd: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43b8d3u; native_call(m, 0x4029d0u);	/* 43b8ce: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b8d3: add esp, 0x24 */
L_43b8d6:
	m->eax = M32((DWORD)(0x9dd6b4u));	/* 43b8d6: mov eax, dword ptr [0x9dd6b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43b8db: test eax, eax */
	if (m->zf) goto L_43ba53;	/* 43b8dd: je 0x43ba53 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8e3: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8e8: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8ed: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8f2: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b8f7: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43b901u; native_call(m, 0x41f0e0u);	/* 43b8fc: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b901: mov eax, dword ptr [0x9dd4ac] */
	m->ecx = M32((DWORD)(0x9dd4b0u));	/* 43b906: mov ecx, dword ptr [0x9dd4b0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b90c: push 1 */
	{ DWORD a_ = m->ecx, b_ = 0xffffff9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b90e: add ecx, -0x64 */
	m->edx = (DWORD)(m->eax + 0x116u);	/* 43b911: lea edx, [eax + 0x116] */
	{ DWORD a_ = m->eax, b_ = 0x96u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b917: add eax, 0x96 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b91c: push edx */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b91d: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b923: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b924: add edx, 0x64 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b927: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b928: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b92eu; native_call(m, 0x427970u);	/* 43b929: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b92e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b933: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b938: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b93d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b942: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43b94cu; native_call(m, 0x41f0e0u);	/* 43b947: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd4b0u));	/* 43b94c: mov eax, dword ptr [0x9dd4b0] */
	m->ecx = M32((DWORD)(0x9dd4acu));	/* 43b951: mov ecx, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43b957: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->eax, b_ = 0xffffff9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b95d: add eax, -0x64 */
	{ DWORD v_ = 0x74f124u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b960: push 0x74f124 */
	{ DWORD a_ = m->ecx, b_ = 0xa6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43b965: add ecx, 0xa6 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b96b: push eax */
	{ DWORD a_ = m->edx, b_ = 0x64u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b96c: add edx, 0x64 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b96f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b970: push edx */
	m->esp -= 4; M32(m->esp) = 0x43b976u; native_call(m, 0x4029d0u);	/* 43b971: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43b976: add esp, 0x4c */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b979: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b97e: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b980: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b982: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b984: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43b98eu; native_call(m, 0x41f0e0u);	/* 43b989: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b98e: mov eax, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4b0u));	/* 43b993: mov edx, dword ptr [0x9dd4b0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b999: push 1 */
	{ DWORD a_ = m->edx, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b99b: add edx, 0xffffff38 */
	m->ecx = (DWORD)(m->eax + 0xe8u);	/* 43b9a1: lea ecx, [eax + 0xe8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b9a7: add eax, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9ac: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9ad: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9ae: push eax */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43b9af: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b9b4: add eax, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9b9: push eax */
	m->esp -= 4; M32(m->esp) = 0x43b9bfu; native_call(m, 0x427970u);	/* 43b9ba: call 0x427970 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9bf: push 0x3f000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9c4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9c9: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9ce: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9d0: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43b9dau; native_call(m, 0x41f0e0u);	/* 43b9d5: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43b9da: mov eax, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4b0u));	/* 43b9df: mov edx, dword ptr [0x9dd4b0] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9e5: push 0 */
	{ DWORD a_ = m->edx, b_ = 0xffffff38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43b9e7: add edx, 0xffffff38 */
	m->ecx = (DWORD)(m->eax + 0xe8u);	/* 43b9ed: lea ecx, [eax + 0xe8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43b9f3: add eax, 0xc8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9f8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9f9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43b9fa: push eax */
	m->eax = M32((DWORD)(0x9dd4a8u));	/* 43b9fb: mov eax, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43ba00: add eax, 0xc8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba05: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ba0bu; native_call(m, 0x427970u);	/* 43ba06: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ba0b: add esp, 0x50 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba0e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba13: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba18: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba1d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba22: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43ba2cu; native_call(m, 0x41f0e0u);	/* 43ba27: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dd4acu));	/* 43ba2c: mov ecx, dword ptr [0x9dd4ac] */
	m->edx = M32((DWORD)(0x9dd4a8u));	/* 43ba32: mov edx, dword ptr [0x9dd4a8] */
	{ DWORD a_ = m->ecx, b_ = 0xd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ba38: add ecx, 0xd0 */
	{ DWORD v_ = 0x9dcee8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba3e: push 0x9dcee8 */
	{ DWORD a_ = m->edx, b_ = 0xd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43ba43: add edx, 0xd8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba49: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba4a: push edx */
	m->esp -= 4; M32(m->esp) = 0x43ba50u; native_call(m, 0x4028b0u);	/* 43ba4b: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ba50: add esp, 0x20 */
L_43ba53:
	m->eax = M32((DWORD)(0x4db8b4u));	/* 43ba53: mov eax, dword ptr [0x4db8b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ba58: test eax, eax */
	if (m->zf) goto L_43bc60;	/* 43ba5a: je 0x43bc60 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba60: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43ba67u; native_call(m, m->ebx);	/* 43ba65: call ebx */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 43ba67: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 43ba6c: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba72: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba73: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ba79u; native_call(m, 0x432340u);	/* 43ba74: call 0x432340 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba79: push 0x3f333333 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba7e: push 0x3f333333 */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba83: push 0x3e4ccccd */
	{ DWORD v_ = 0x3e4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba88: push 0x3e4ccccd */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba8d: push 0x9da480 */
	m->esi = m->eax;	/* 43ba92: mov esi, eax */
	m->esp -= 4; M32(m->esp) = 0x43ba99u; native_call(m, 0x41f0e0u);	/* 43ba94: call 0x41f0e0 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba99: push 1 */
	{ DWORD v_ = 0x140u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ba9b: push 0x140 */
	{ DWORD v_ = 0x21cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43baa0: push 0x21c */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43baa5: push 0xc8 */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 43baaa: push 0x64 */
	m->esp -= 4; M32(m->esp) = 0x43bab1u; native_call(m, 0x427970u);	/* 43baac: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bab1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bab6: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bab8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43babd: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bac2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43baccu; native_call(m, 0x41f0e0u);	/* 43bac7: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bacc: add esp, 0x44 */
	{ DWORD v_ = 0x752aa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bacf: push 0x752aa4 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bad4: push 0x217 */
	{ DWORD v_ = 0xdcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43bad9: push 0xdc */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bade: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x43bae5u; native_call(m, 0x4029d0u);	/* 43bae0: call 0x4029d0 */
	{ DWORD v_ = 0x752b24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bae5: push 0x752b24 */
	{ DWORD v_ = 0x217u; m->esp -= 4; M32(m->esp) = v_; }	/* 43baea: push 0x217 */
	{ DWORD v_ = 0xf4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43baef: push 0xf4 */
	{ DWORD v_ = 0x69u; m->esp -= 4; M32(m->esp) = v_; }	/* 43baf4: push 0x69 */
	m->esp -= 4; M32(m->esp) = 0x43bafbu; native_call(m, 0x4029d0u);	/* 43baf6: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bafb: add esp, 0x20 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bafe: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43bb05u; native_call(m, m->ebp);	/* 43bb03: call ebp */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43bb05: mov eax, dword ptr [0x9db0a4] */
	m->edx = m->eax;	/* 43bb0a: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43bb0c: and edx, 0x800001ff */
	if (!m->sf) goto L_43bb1c;	/* 43bb12: jns 0x43bb1c */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 43bb14: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43bb15: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 43bb1b: inc edx */
L_43bb1c:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb1c: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 43bb1d: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43bb23: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43bb24: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43bb2a: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43bb2c: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 43bb2f: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43bb38u; native_call(m, 0x4566c0u);	/* 43bb33: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb38: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb3d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb42: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb47: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43bb4eu; native_call(m, m->edi);	/* 43bb4c: call edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43bb4e: test esi, esi */
	if (!m->zf) goto L_43bbe5;	/* 43bb50: jne 0x43bbe5 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb56: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb5b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb60: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb65: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43bb6cu; native_call(m, m->edi);	/* 43bb6a: call edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb6c: push 1 */
	{ DWORD v_ = 0x138u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb6e: push 0x138 */
	{ DWORD v_ = 0x17cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb73: push 0x17c */
	{ DWORD v_ = 0x118u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb78: push 0x118 */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb7d: push 0x104 */
	m->esp -= 4; M32(m->esp) = 0x43bb87u; native_call(m, 0x4282f0u);	/* 43bb82: call 0x4282f0 */
	m->edx = M32((DWORD)(0x9dceccu));	/* 43bb87: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 43bb8d: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 43bb92: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb98: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 43bb99: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bb9f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bba0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bba1: push edx */
	goto L_43bc30;	/* 43bba2: jmp 0x43bc30 */
L_43bba7:
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43bba7: mov eax, dword ptr [0x9dd4ac] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbac: push 0 */
	m->ecx = (DWORD)(m->eax + 0xaeu);	/* 43bbae: lea ecx, [eax + 0xae] */
	{ DWORD a_ = m->eax, b_ = 0x6eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43bbb4: add eax, 0x6e */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbb7: push ecx */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43bbb8: mov ecx, dword ptr [0x9dd4a8] */
	m->edx = (DWORD)(m->ecx + 0x246u);	/* 43bbbe: lea edx, [ecx + 0x246] */
	{ DWORD a_ = m->ecx, b_ = 0x226u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43bbc4: add ecx, 0x226 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbca: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbcb: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbcc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43bbd2u; native_call(m, 0x4286b0u);	/* 43bbcd: call 0x4286b0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bbd2: add esp, 0x14 */
	{ DWORD a_ = m->ebx, b_ = 0xeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43bbd5: cmp ebx, 0xe */
	if (!m->zf) goto L_43b825;	/* 43bbd8: jne 0x43b825 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbde: push 1 */
	goto L_43b827;	/* 43bbe0: jmp 0x43b827 */
L_43bbe5:
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbe5: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbea: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbef: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbf4: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43bbfbu; native_call(m, m->edi);	/* 43bbf9: call edi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbfb: push 1 */
	{ DWORD v_ = 0x138u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bbfd: push 0x138 */
	{ DWORD v_ = 0x17cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc02: push 0x17c */
	{ DWORD v_ = 0x118u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc07: push 0x118 */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc0c: push 0x104 */
	m->esp -= 4; M32(m->esp) = 0x43bc16u; native_call(m, 0x4282f0u);	/* 43bc11: call 0x4282f0 */
	m->eax = M32((DWORD)(0x9dd344u));	/* 43bc16: mov eax, dword ptr [0x9dd344] */
	m->ecx = M32((DWORD)(0x9dd340u));	/* 43bc1b: mov ecx, dword ptr [0x9dd340] */
	m->edx = M32((DWORD)(0x9dd33cu));	/* 43bc21: mov edx, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc27: push eax */
	m->eax = M32((DWORD)(0x9dd338u));	/* 43bc28: mov eax, dword ptr [0x9dd338] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc2d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc2e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc2f: push eax */
L_43bc30:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc30: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43bc3au; native_call(m, 0x41f0e0u);	/* 43bc35: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bc3a: add esp, 0x28 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc3d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43bc44u; native_call(m, m->ebx);	/* 43bc42: call ebx */
	{ DWORD v_ = 0x751824u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc44: push 0x751824 */
	{ DWORD v_ = 0x17cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc49: push 0x17c */
	{ DWORD v_ = 0x120u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc4e: push 0x120 */
	{ DWORD v_ = 0x104u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc53: push 0x104 */
	m->esp -= 4; M32(m->esp) = 0x43bc5du; native_call(m, 0x4029d0u);	/* 43bc58: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bc5d: add esp, 0x10 */
L_43bc60:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc60: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc65: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc6a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc6f: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43bc76u; native_call(m, m->edi);	/* 43bc74: call edi */
	m->ecx = M32((DWORD)(0x9dd4b4u));	/* 43bc76: mov ecx, dword ptr [0x9dd4b4] */
	m->edx = M32((DWORD)(0x9dd4b0u));	/* 43bc7c: mov edx, dword ptr [0x9dd4b0] */
	m->eax = M32((DWORD)(0x9dd4acu));	/* 43bc82: mov eax, dword ptr [0x9dd4ac] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc87: push ecx */
	m->ecx = M32((DWORD)(0x9dd4a8u));	/* 43bc88: mov ecx, dword ptr [0x9dd4a8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc8e: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc8f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43bc90: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43bc96u; native_call(m, 0x428a00u);	/* 43bc91: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bc96: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43bc99: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43bc9a: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43bc9b: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43bc9c: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43bc9d: add esp, 0x44 */
	m->esp += 4 + 0; return;	/* 43bca0: ret  */
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
