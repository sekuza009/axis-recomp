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

static void lift_43fcc0(X86 *m);

/* app_init (0x43fcc0), lifted by tools/lift.py */
static void lift_43fcc0(X86 *m)
{
	m->eax = M32((DWORD)(0x76d410u));	/* 43fcc0: mov eax, dword ptr [0x76d410] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fcc5: sub esp, 0x28 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fcc8: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43fcc9: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 43fcca: xor ebp, ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43fccc: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43fccd: cmp eax, ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43fccf: push edi */
	if (!m->zf) goto L_43fd76;	/* 43fcd0: jne 0x43fd76 */
	m->esp -= 4; M32(m->esp) = 0x43fcdbu; native_call(m, 0x41e6d0u);	/* 43fcd6: call 0x41e6d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fcdb: test eax, eax */
	if (!m->zf) goto L_43fcf6;	/* 43fcdd: jne 0x43fcf6 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fcdf: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fce9u; native_call(m, 0x41edf0u);	/* 43fce4: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fce9: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fcec: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fcee: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fcef: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fcf0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fcf1: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fcf2: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fcf5: ret  */
L_43fcf6:
	m->esp -= 4; M32(m->esp) = 0x43fcfbu; native_call(m, 0x41e550u);	/* 43fcf6: call 0x41e550 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fcfb: test eax, eax */
	if (!m->zf) goto L_43fd16;	/* 43fcfd: jne 0x43fd16 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fcff: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fd09u; native_call(m, 0x41edf0u);	/* 43fd04: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fd09: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fd0c: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fd0e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fd0f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fd10: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fd11: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fd12: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fd15: ret  */
L_43fd16:
	m->esp -= 4; M32(m->esp) = 0x43fd1bu; native_call(m, 0x41e5b0u);	/* 43fd16: call 0x41e5b0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fd1b: test eax, eax */
	if (!m->zf) goto L_43fd36;	/* 43fd1d: jne 0x43fd36 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fd1f: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fd29u; native_call(m, 0x41edf0u);	/* 43fd24: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fd29: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fd2c: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fd2e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fd2f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fd30: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fd31: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fd32: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fd35: ret  */
L_43fd36:
	m->esp -= 4; M32(m->esp) = 0x43fd3bu; native_call(m, 0x41e610u);	/* 43fd36: call 0x41e610 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fd3b: test eax, eax */
	if (!m->zf) goto L_43fd56;	/* 43fd3d: jne 0x43fd56 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fd3f: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fd49u; native_call(m, 0x41edf0u);	/* 43fd44: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fd49: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fd4c: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fd4e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fd4f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fd50: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fd51: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fd52: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fd55: ret  */
L_43fd56:
	m->esp -= 4; M32(m->esp) = 0x43fd5bu; native_call(m, 0x41e670u);	/* 43fd56: call 0x41e670 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fd5b: test eax, eax */
	if (!m->zf) goto L_43fd76;	/* 43fd5d: jne 0x43fd76 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fd5f: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fd69u; native_call(m, 0x41edf0u);	/* 43fd64: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fd69: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fd6c: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fd6e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fd6f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fd70: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fd71: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fd72: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fd75: ret  */
L_43fd76:
	M32((DWORD)(0x5b1998u)) = 0x280u;	/* 43fd76: mov dword ptr [0x5b1998], 0x280 */
	M32((DWORD)(0x4e045cu)) = 0x1e0u;	/* 43fd80: mov dword ptr [0x4e045c], 0x1e0 */
	m->esp -= 4; M32(m->esp) = 0x43fd8fu; native_call(m, 0x43f580u);	/* 43fd8a: call 0x43f580 */
	m->esp -= 4; M32(m->esp) = 0x43fd94u; native_call(m, 0x43f5a0u);	/* 43fd8f: call 0x43f5a0 */
	m->esp -= 4; M32(m->esp) = 0x43fd99u; native_call(m, 0x42b3e0u);	/* 43fd94: call 0x42b3e0 */
	goto L_4a8e20;	/* 43fd99: jmp 0x4a8e20 */
	;	/* 43fd9e: nop  */
L_43fd9f:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43fd9f: push ebp */
	M32((DWORD)(0x9dd8f8u)) = m->ebp;	/* 43fda0: mov dword ptr [0x9dd8f8], ebp */
	m->esp -= 4; M32(m->esp) = 0x43fda8u; native_call(m, m->esi);	/* 43fda6: call esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fda8: push 1 */
	M32((DWORD)(0x67eefcu)) = m->eax;	/* 43fdaa: mov dword ptr [0x67eefc], eax */
	m->esp -= 4; M32(m->esp) = 0x43fdb1u; native_call(m, m->esi);	/* 43fdaf: call esi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43fdb1: push ebp */
	M32((DWORD)(0x76d430u)) = m->eax;	/* 43fdb2: mov dword ptr [0x76d430], eax */
	m->esp -= 4; M32(m->esp) = 0x43fdbdu; native_call(m, M32(0x4a9318u));	/* 43fdb7: call dword ptr [0x4a9318] */
	{ DWORD v_ = 0xcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43fdbd: push 0xc */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fdbf: push eax */
	M32((DWORD)(0x76d480u)) = m->eax;	/* 43fdc0: mov dword ptr [0x76d480], eax */
	m->esp -= 4; M32(m->esp) = 0x43fdcbu; native_call(m, M32(0x4a9034u));	/* 43fdc5: call dword ptr [0x4a9034] */
	M32((DWORD)(0x76d3ecu)) = m->eax;	/* 43fdcb: mov dword ptr [0x76d3ec], eax */
	m->esp -= 4; M32(m->esp) = 0x43fdd5u; native_call(m, 0x42fd40u);	/* 43fdd0: call 0x42fd40 */
	m->esp -= 4; M32(m->esp) = 0x43fddau; native_call(m, 0x42eca0u);	/* 43fdd5: call 0x42eca0 */
	m->esp -= 4; M32(m->esp) = 0x43fddfu; native_call(m, 0x43f640u);	/* 43fdda: call 0x43f640 */
	m->eax = M32((DWORD)(0x83a9c4u));	/* 43fddf: mov eax, dword ptr [0x83a9c4] */
	m->ecx = M32((DWORD)(0x4e045cu));	/* 43fde4: mov ecx, dword ptr [0x4e045c] */
	m->edx = M32((DWORD)(0x5b1998u));	/* 43fdea: mov edx, dword ptr [0x5b1998] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 43fdf0: inc eax */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43fdf1: shl eax, 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fdf4: push eax */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fdf5: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fdf7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43fdf8: push edx */
	m->esp -= 4; M32(m->esp) = 0x43fdfeu; native_call(m, 0x42eed0u);	/* 43fdf9: call 0x42eed0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fdfe: push eax */
	m->esp -= 4; M32(m->esp) = 0x43fe04u; native_call(m, 0x42ef30u);	/* 43fdff: call 0x42ef30 */
	m->eax = M32((DWORD)(0x76d410u));	/* 43fe04: mov eax, dword ptr [0x76d410] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe09: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43fe0c: cmp eax, ebp */
	if (!m->zf) goto L_43feb4;	/* 43fe0e: jne 0x43feb4 */
	m->esp -= 4; M32(m->esp) = 0x43fe19u; native_call(m, 0x41e6d0u);	/* 43fe14: call 0x41e6d0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fe19: test eax, eax */
	if (!m->zf) goto L_43fe34;	/* 43fe1b: jne 0x43fe34 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fe1d: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fe27u; native_call(m, 0x41edf0u);	/* 43fe22: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe27: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fe2a: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fe2c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fe2d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fe2e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fe2f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe30: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fe33: ret  */
L_43fe34:
	m->esp -= 4; M32(m->esp) = 0x43fe39u; native_call(m, 0x41e550u);	/* 43fe34: call 0x41e550 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fe39: test eax, eax */
	if (!m->zf) goto L_43fe54;	/* 43fe3b: jne 0x43fe54 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fe3d: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fe47u; native_call(m, 0x41edf0u);	/* 43fe42: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe47: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fe4a: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fe4c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fe4d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fe4e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fe4f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe50: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fe53: ret  */
L_43fe54:
	m->esp -= 4; M32(m->esp) = 0x43fe59u; native_call(m, 0x41e5b0u);	/* 43fe54: call 0x41e5b0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fe59: test eax, eax */
	if (!m->zf) goto L_43fe74;	/* 43fe5b: jne 0x43fe74 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fe5d: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fe67u; native_call(m, 0x41edf0u);	/* 43fe62: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe67: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fe6a: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fe6c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fe6d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fe6e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fe6f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe70: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fe73: ret  */
L_43fe74:
	m->esp -= 4; M32(m->esp) = 0x43fe79u; native_call(m, 0x41e610u);	/* 43fe74: call 0x41e610 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fe79: test eax, eax */
	if (!m->zf) goto L_43fe94;	/* 43fe7b: jne 0x43fe94 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fe7d: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fe87u; native_call(m, 0x41edf0u);	/* 43fe82: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe87: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43fe8a: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43fe8c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fe8d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43fe8e: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43fe8f: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fe90: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43fe93: ret  */
L_43fe94:
	m->esp -= 4; M32(m->esp) = 0x43fe99u; native_call(m, 0x41e670u);	/* 43fe94: call 0x41e670 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43fe99: test eax, eax */
	if (!m->zf) goto L_43feb4;	/* 43fe9b: jne 0x43feb4 */
	{ DWORD v_ = 0x4b04b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fe9d: push 0x4b04b0 */
	m->esp -= 4; M32(m->esp) = 0x43fea7u; native_call(m, 0x41edf0u);	/* 43fea2: call 0x41edf0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43fea7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43feaa: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 43feac: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43fead: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43feae: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43feaf: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43feb0: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43feb3: ret  */
L_43feb4:
	m->ebx = M32((DWORD)(m->esp + 0x3cu));	/* 43feb4: mov ebx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43feb8: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43feb9: push ebx */
	M32((DWORD)(m->esp + 0x18u)) = m->ebp;	/* 43feba: mov dword ptr [esp + 0x18], ebp */
	M32((DWORD)(m->esp + 0x1cu)) = 0x440070u;	/* 43febe: mov dword ptr [esp + 0x1c], 0x440070 */
	M32((DWORD)(m->esp + 0x20u)) = m->ebp;	/* 43fec6: mov dword ptr [esp + 0x20], ebp */
	M32((DWORD)(m->esp + 0x24u)) = m->ebp;	/* 43feca: mov dword ptr [esp + 0x24], ebp */
	M32((DWORD)(m->esp + 0x28u)) = m->ebx;	/* 43fece: mov dword ptr [esp + 0x28], ebx */
	m->esp -= 4; M32(m->esp) = 0x43fed8u; native_call(m, M32(0x4a92c4u));	/* 43fed2: call dword ptr [0x4a92c4] */
	{ DWORD v_ = 0x7f00u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fed8: push 0x7f00 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43fedd: push ebp */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 43fede: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x43fee8u; native_call(m, M32(0x4a933cu));	/* 43fee2: call dword ptr [0x4a933c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43fee8: push 4 */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 43feea: mov dword ptr [esp + 0x2c], eax */
	m->esp -= 4; M32(m->esp) = 0x43fef4u; native_call(m, M32(0x4a903cu));	/* 43feee: call dword ptr [0x4a903c] */
	m->esi = M32((DWORD)(0x4a90fcu));	/* 43fef4: mov esi, dword ptr [0x4a90fc] */
	M32((DWORD)(m->esp + 0x2cu)) = m->eax;	/* 43fefa: mov dword ptr [esp + 0x2c], eax */
	m->eax = 0x4b0714u;	/* 43fefe: mov eax, 0x4b0714 */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 43ff03: mov dword ptr [esp + 0x30], eax */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 43ff07: mov dword ptr [esp + 0x34], eax */
	m->esp -= 4; M32(m->esp) = 0x43ff0du; native_call(m, m->esi);	/* 43ff0b: call esi */
	{ DWORD a_ = m->eax, b_ = 0x80000000u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ff0d: cmp eax, 0x80000000 */
	if (m->cf) goto L_43ff3c;	/* 43ff12: jb 0x43ff3c */
	m->esp -= 4; M32(m->esp) = 0x43ff16u; native_call(m, m->esi);	/* 43ff14: call esi */
	{ DWORD a_ = m->eax, b_ = 0x80000000u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ff16: cmp eax, 0x80000000 */
	if (m->cf) goto L_43ff23;	/* 43ff1b: jb 0x43ff23 */
	m->esp -= 4; M32(m->esp) = 0x43ff1fu; native_call(m, m->esi);	/* 43ff1d: call esi */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x4u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43ff1f: cmp al, 4 */
	if (m->cf) goto L_43ff3c;	/* 43ff21: jb 0x43ff3c */
L_43ff23:
	m->eax = (DWORD)(m->esp + 0x10u);	/* 43ff23: lea eax, [esp + 0x10] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ff27: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ff2du; native_call(m, 0x43f840u);	/* 43ff28: call 0x43f840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ff2d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ff30: test eax, eax */
	if (!m->zf) goto L_43ff56;	/* 43ff32: jne 0x43ff56 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43ff34: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43ff35: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43ff36: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43ff37: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ff38: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43ff3b: ret  */
L_43ff3c:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 43ff3c: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ff40: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ff47u; native_call(m, M32(0x4a92b8u));	/* 43ff41: call dword ptr [0x4a92b8] */
	{ DWORD a_ = (m->eax & 0xffff), b_ = (m->eax & 0xffff) & 0xffffu, r_ = a_ & b_; FLAGS(r_, 16); m->cf = 0; m->of = 0; }	/* 43ff47: test ax, ax */
	if (!m->zf) goto L_43ff56;	/* 43ff4a: jne 0x43ff56 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43ff4c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43ff4d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43ff4e: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43ff4f: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43ff51: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ff52: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43ff55: ret  */
L_43ff56:
	goto L_4a8f50;	/* 43ff56: jmp 0x4a8f50 */
	;	/* 43ff5b: nop  */
	;	/* 43ff5c: nop  */
	;	/* 43ff5d: nop  */
	;	/* 43ff5e: nop  */
	;	/* 43ff5f: nop  */
	;	/* 43ff60: nop  */
	;	/* 43ff61: nop  */
	;	/* 43ff62: nop  */
	;	/* 43ff63: nop  */
	;	/* 43ff64: nop  */
	;	/* 43ff65: nop  */
	;	/* 43ff66: nop  */
	;	/* 43ff67: nop  */
	;	/* 43ff68: nop  */
L_43ff69:
	{ DWORD v_ = 0x86000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ff69: push 0x86000000 */
	m->ecx = 0xau;	/* 43ff6e: mov ecx, 0xa */
	m->esi = (DWORD)(m->esp + 0x34u);	/* 43ff73: lea esi, [esp + 0x34] */
	m->edi = 0x4e0ca8u;	/* 43ff77: mov edi, 0x4e0ca8 */
	{ DWORD v_ = 0x4b2874u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ff7c: push 0x4b2874 */
	{ DWORD v_ = 0x4b0714u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ff81: push 0x4b0714 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43ff86: rep movsd dword ptr es:[edi], dword ptr [esi] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43ff88: push ebp */
	m->esp -= 4; M32(m->esp) = 0x43ff8fu; native_call(m, M32(0x4a9350u));	/* 43ff89: call dword ptr [0x4a9350] */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ff8f: cmp eax, ebp */
	M32((DWORD)(0x4ded18u)) = m->eax;	/* 43ff91: mov dword ptr [0x4ded18], eax */
	if (!m->zf) goto L_43ffa2;	/* 43ff96: jne 0x43ffa2 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43ff98: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43ff99: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43ff9a: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43ff9b: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43ff9d: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ff9e: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 43ffa1: ret  */
L_43ffa2:
	m->edi = M32((DWORD)(m->esp + 0x40u));	/* 43ffa2: mov edi, dword ptr [esp + 0x40] */
	m->esi = M32((DWORD)(0x4a9334u));	/* 43ffa6: mov esi, dword ptr [0x4a9334] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffac: push ebp */
	{ DWORD v_ = 0xea60u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffad: push 0xea60 */
	{ DWORD v_ = 0x29au; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffb2: push 0x29a */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffb7: push eax */
	M32((DWORD)(0x67ef18u)) = m->ebx;	/* 43ffb8: mov dword ptr [0x67ef18], ebx */
	M32((DWORD)(0x4deb54u)) = m->edi;	/* 43ffbe: mov dword ptr [0x4deb54], edi */
	m->esp -= 4; M32(m->esp) = 0x43ffc6u; native_call(m, m->esi);	/* 43ffc4: call esi */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 43ffc6: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffcc: push ebp */
	{ DWORD v_ = 0x7530u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffcd: push 0x7530 */
	{ DWORD v_ = 0x115cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffd2: push 0x115c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffd7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43ffdau; native_call(m, m->esi);	/* 43ffd8: call esi */
	m->edx = M32((DWORD)(0x4ded18u));	/* 43ffda: mov edx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffe0: push ebp */
	{ DWORD v_ = 0xea60u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffe1: push 0xea60 */
	{ DWORD v_ = 0x309u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffe6: push 0x309 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ffeb: push edx */
	m->esp -= 4; M32(m->esp) = 0x43ffeeu; native_call(m, m->esi);	/* 43ffec: call esi */
	m->eax = M32((DWORD)(0x4ded18u));	/* 43ffee: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43fff3: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43fff4: push eax */
	m->esp -= 4; M32(m->esp) = 0x43fffbu; native_call(m, M32(0x4a92bcu));	/* 43fff5: call dword ptr [0x4a92bc] */
	m->ecx = M32((DWORD)(0x4ded18u));	/* 43fffb: mov ecx, dword ptr [0x4ded18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 440001: push ecx */
	m->esp -= 4; M32(m->esp) = 0x440008u; native_call(m, M32(0x4a92c0u));	/* 440002: call dword ptr [0x4a92c0] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 440008: push ebx */
	m->esp -= 4; M32(m->esp) = 0x44000eu; native_call(m, 0x430400u);	/* 440009: call 0x430400 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44000e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 440011: test eax, eax */
	if (!m->zf) goto L_44003c;	/* 440013: jne 0x44003c */
	m->edx = M32((DWORD)(0x76d3ecu));	/* 440015: mov edx, dword ptr [0x76d3ec] */
	m->eax = M32((DWORD)(0x76d430u));	/* 44001b: mov eax, dword ptr [0x76d430] */
	m->ecx = M32((DWORD)(0x67eefcu));	/* 440020: mov ecx, dword ptr [0x67eefc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 440026: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 440027: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 440028: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 440029: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44002fu; native_call(m, 0x42eed0u);	/* 44002a: call 0x42eed0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44002f: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 440032: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 440034: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 440035: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 440036: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 440037: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440038: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 44003b: ret  */
L_44003c:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44003c: push ebp */
	M32((DWORD)(0x76d3e8u)) = 0x64u;	/* 44003d: mov dword ptr [0x76d3e8], 0x64 */
	m->esp -= 4; M32(m->esp) = 0x44004du; native_call(m, M32(0x4a92c8u));	/* 440047: call dword ptr [0x4a92c8] */
	M32((DWORD)(0x9dd904u)) = 0x1u;	/* 44004d: mov dword ptr [0x9dd904], 1 */
	m->esp -= 4; M32(m->esp) = 0x44005cu; native_call(m, 0x43f300u);	/* 440057: call 0x43f300 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44005c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44005d: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44005e: pop ebp */
	m->eax = 0x1u;	/* 44005f: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 440064: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 440065: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 440068: ret  */
L_4a8e20:
	{ DWORD v_ = 0x4ac820u; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8e20: push 0x4ac820 */
	m->esp -= 4; M32(m->esp) = 0x4a8e2bu; native_call(m, M32(0x4a915cu));	/* 4a8e25: call dword ptr [0x4a915c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4a8e2b: test eax, eax */
	if (m->zf) goto L_4a8e49;	/* 4a8e2d: je 0x4a8e49 */
	{ DWORD v_ = 0x4ac82cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8e33: push 0x4ac82c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8e38: push eax */
	m->esp -= 4; M32(m->esp) = 0x4a8e3fu; native_call(m, M32(0x4a907cu));	/* 4a8e39: call dword ptr [0x4a907c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4a8e3f: test eax, eax */
	if (m->zf) goto L_4a8e49;	/* 4a8e41: je 0x4a8e49 */
	m->esp -= 4; M32(m->esp) = 0x4a8e49u; native_call(m, m->eax);	/* 4a8e47: call eax */
L_4a8e49:
	m->esi = M32((DWORD)(0x4a9358u));	/* 4a8e49: mov esi, dword ptr [0x4a9358] */
	goto L_43fd9f;	/* 4a8e4f: jmp 0x43fd9f */
L_4a8f50:
	m->edx = M32((DWORD)(0x4e045cu));	/* 4a8f50: mov edx, dword ptr [0x4e045c] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 4a8f56: inc edx */
	m->eax = M32((DWORD)(0x5b1998u));	/* 4a8f57: mov eax, dword ptr [0x5b1998] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8f5c: push ebp */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8f5d: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8f5e: push ebp */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8f5f: push ebp */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8f60: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8f61: push eax */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8f62: push -1 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4a8f64: push ebp */
	goto L_43ff69;	/* 4a8f65: jmp 0x43ff69 */
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
