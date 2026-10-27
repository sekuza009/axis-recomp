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

static void lift_482320(X86 *m);
static void lift_4823c0(X86 *m);
static void lift_481eb0(X86 *m);

/* space_buildPlanes (0x481eb0), lifted by tools/lift.py */
static void lift_481eb0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481eb0: sub esp, 0x34 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 481eb3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 481eb4: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x44u));	/* 481eb5: mov ebp, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 481eb9: push esi */
	m->eax = m->ebp;	/* 481eba: mov eax, ebp */
	m->esi = m->ecx;	/* 481ebc: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 481ebe: push edi */
	m->edi = M32((DWORD)(m->esp + 0x50u));	/* 481ebf: mov edi, dword ptr [esp + 0x50] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 481ec3: mov ecx, dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 481ec5: fld dword ptr [edi] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 481ec7: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 481eca: mov dword ptr [esp + 0x14], ecx */
	m->ecx = m->ebp;	/* 481ece: mov ecx, ebp */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 481ed0: mov dword ptr [esp + 0x18], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 481ed4: mov eax, dword ptr [eax + 8] */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 481ed7: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 481ed9: mov dword ptr [esp + 0x1c], eax */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 481edd: mov dword ptr [esp + 0x20], edx */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x20u)); FPOP();	/* 481ee1: fcomp dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 481ee5: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 481ee8: mov dword ptr [esp + 0x24], eax */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 481eec: mov ecx, dword ptr [ecx + 8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481eef: fnstsw ax */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 481ef1: mov dword ptr [esp + 0x28], ecx */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481ef5: test ah, 0x41 */
	if (!m->zf) goto L_481f00;	/* 481ef8: jne 0x481f00 */
	m->edx = M32((DWORD)(m->edi + 0x0u));	/* 481efa: mov edx, dword ptr [edi] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 481efc: mov dword ptr [esp + 0x20], edx */
L_481f00:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 481f00: fld dword ptr [edi] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x14u)); FPOP();	/* 481f02: fcomp dword ptr [esp + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481f06: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481f08: test ah, 1 */
	if (m->zf) goto L_481f13;	/* 481f0b: je 0x481f13 */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 481f0d: mov eax, dword ptr [edi] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 481f0f: mov dword ptr [esp + 0x14], eax */
L_481f13:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 481f13: fld dword ptr [edi + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 481f16: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481f1a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481f1c: test ah, 0x41 */
	if (!m->zf) goto L_481f28;	/* 481f1f: jne 0x481f28 */
	m->ecx = M32((DWORD)(m->edi + 0x4u));	/* 481f21: mov ecx, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 481f24: mov dword ptr [esp + 0x24], ecx */
L_481f28:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x4u)));	/* 481f28: fld dword ptr [edi + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x18u)); FPOP();	/* 481f2b: fcomp dword ptr [esp + 0x18] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481f2f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481f31: test ah, 1 */
	if (m->zf) goto L_481f3d;	/* 481f34: je 0x481f3d */
	m->edx = M32((DWORD)(m->edi + 0x4u));	/* 481f36: mov edx, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 481f39: mov dword ptr [esp + 0x18], edx */
L_481f3d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 481f3d: fld dword ptr [edi + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u)); FPOP();	/* 481f40: fcomp dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481f44: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481f46: test ah, 0x41 */
	if (!m->zf) goto L_481f52;	/* 481f49: jne 0x481f52 */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 481f4b: mov eax, dword ptr [edi + 8] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 481f4e: mov dword ptr [esp + 0x28], eax */
L_481f52:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8u)));	/* 481f52: fld dword ptr [edi + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu)); FPOP();	/* 481f55: fcomp dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481f59: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481f5b: test ah, 1 */
	if (m->zf) goto L_481f67;	/* 481f5e: je 0x481f67 */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 481f60: mov ecx, dword ptr [edi + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 481f63: mov dword ptr [esp + 0x1c], ecx */
L_481f67:
	m->ebx = M32((DWORD)(m->esp + 0x54u));	/* 481f67: mov ebx, dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 481f6b: fld dword ptr [ebx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x20u)); FPOP();	/* 481f6d: fcomp dword ptr [esp + 0x20] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481f71: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481f73: test ah, 0x41 */
	if (!m->zf) goto L_481f7e;	/* 481f76: jne 0x481f7e */
	m->edx = M32((DWORD)(m->ebx + 0x0u));	/* 481f78: mov edx, dword ptr [ebx] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 481f7a: mov dword ptr [esp + 0x20], edx */
L_481f7e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 481f7e: fld dword ptr [ebx] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x14u)); FPOP();	/* 481f80: fcomp dword ptr [esp + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481f84: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481f86: test ah, 1 */
	if (m->zf) goto L_481f91;	/* 481f89: je 0x481f91 */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 481f8b: mov eax, dword ptr [ebx] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 481f8d: mov dword ptr [esp + 0x14], eax */
L_481f91:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 481f91: fld dword ptr [ebx + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 481f94: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481f98: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481f9a: test ah, 0x41 */
	if (!m->zf) goto L_481fa6;	/* 481f9d: jne 0x481fa6 */
	m->ecx = M32((DWORD)(m->ebx + 0x4u));	/* 481f9f: mov ecx, dword ptr [ebx + 4] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 481fa2: mov dword ptr [esp + 0x24], ecx */
L_481fa6:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 481fa6: fld dword ptr [ebx + 4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x18u)); FPOP();	/* 481fa9: fcomp dword ptr [esp + 0x18] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481fad: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481faf: test ah, 1 */
	if (m->zf) goto L_481fbb;	/* 481fb2: je 0x481fbb */
	m->edx = M32((DWORD)(m->ebx + 0x4u));	/* 481fb4: mov edx, dword ptr [ebx + 4] */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 481fb7: mov dword ptr [esp + 0x18], edx */
L_481fbb:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 481fbb: fld dword ptr [ebx + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u)); FPOP();	/* 481fbe: fcomp dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481fc2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481fc4: test ah, 0x41 */
	if (!m->zf) goto L_481fd0;	/* 481fc7: jne 0x481fd0 */
	m->eax = M32((DWORD)(m->ebx + 0x8u));	/* 481fc9: mov eax, dword ptr [ebx + 8] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 481fcc: mov dword ptr [esp + 0x28], eax */
L_481fd0:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 481fd0: fld dword ptr [ebx + 8] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu)); FPOP();	/* 481fd3: fcomp dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481fd7: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481fd9: test ah, 1 */
	if (m->zf) goto L_481fe5;	/* 481fdc: je 0x481fe5 */
	m->ecx = M32((DWORD)(m->ebx + 0x8u));	/* 481fde: mov ecx, dword ptr [ebx + 8] */
	M32((DWORD)(m->esp + 0x1cu)) = m->ecx;	/* 481fe1: mov dword ptr [esp + 0x1c], ecx */
L_481fe5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x68u)));	/* 481fe5: fld dword ptr [esi + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 481fe8: fadd dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x14u)); FPOP();	/* 481fee: fcomp dword ptr [esp + 0x14] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 481ff2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 481ff4: test ah, 0x41 */
	if (!m->zf) goto L_482305;	/* 481ff7: jne 0x482305 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x6cu)));	/* 481ffd: fld dword ptr [esi + 0x6c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482000: fadd dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x18u)); FPOP();	/* 482006: fcomp dword ptr [esp + 0x18] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48200a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48200c: test ah, 0x41 */
	if (!m->zf) goto L_482305;	/* 48200f: jne 0x482305 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x70u)));	/* 482015: fld dword ptr [esi + 0x70] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482018: fadd dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x1cu)); FPOP();	/* 48201e: fcomp dword ptr [esp + 0x1c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482022: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482024: test ah, 0x41 */
	if (!m->zf) goto L_482305;	/* 482027: jne 0x482305 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x5cu)));	/* 48202d: fld dword ptr [esi + 0x5c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482030: fsub dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x20u)); FPOP();	/* 482036: fcomp dword ptr [esp + 0x20] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48203a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48203c: test ah, 1 */
	if (m->zf) goto L_482305;	/* 48203f: je 0x482305 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x60u)));	/* 482045: fld dword ptr [esi + 0x60] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482048: fsub dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x24u)); FPOP();	/* 48204e: fcomp dword ptr [esp + 0x24] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 482052: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482054: test ah, 1 */
	if (m->zf) goto L_482305;	/* 482057: je 0x482305 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x64u)));	/* 48205d: fld dword ptr [esi + 0x64] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482060: fsub dword ptr [esi + 0x8c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x28u)); FPOP();	/* 482066: fcomp dword ptr [esp + 0x28] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48206a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48206c: test ah, 1 */
	if (m->zf) goto L_482305;	/* 48206f: je 0x482305 */
	m->ecx = m->esi;	/* 482075: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48207cu; native_call(m, 0x4815c0u);	/* 482077: call 0x4815c0 */
	m->edx = M32((DWORD)(m->esp + 0x68u));	/* 48207c: mov edx, dword ptr [esp + 0x68] */
	m->ecx = M32((DWORD)(m->esp + 0x64u));	/* 482080: mov ecx, dword ptr [esp + 0x64] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482084: push edx */
	m->edx = M32((DWORD)(m->esp + 0x64u));	/* 482085: mov edx, dword ptr [esp + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482089: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x64u));	/* 48208a: mov ecx, dword ptr [esp + 0x64] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48208e: push edx */
	m->edx = M32((DWORD)(m->esp + 0x64u));	/* 48208f: mov edx, dword ptr [esp + 0x64] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482093: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 482094: mov ecx, dword ptr [esp + 0x58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482098: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 482099: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48209a: push edi */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48209b: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48209c: push ecx */
	m->ecx = m->eax;	/* 48209d: mov ecx, eax */
	M32((DWORD)(m->esp + 0x34u)) = m->eax;	/* 48209f: mov dword ptr [esp + 0x34], eax */
	m->esp -= 4; M32(m->esp) = 0x4820a8u; native_call(m, 0x47db60u);	/* 4820a3: call 0x47db60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 4820a8: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 4820ac: fsub dword ptr [esi + 0x8c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 4820b2: fsub dword ptr [esi + 0x64] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 4820b5: fdiv dword ptr [esi + 0x80] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4820bb: call 0x49ec14 */
	m->ebp = m->eax;	/* 4820c0: mov ebp, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4820c2: xor edi, edi */
	{ DWORD a_ = m->ebp, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4820c4: cmp ebp, edi */
	M32((DWORD)(m->esp + 0x64u)) = m->ebp;	/* 4820c6: mov dword ptr [esp + 0x64], ebp */
	if (m->sf == m->of) goto L_4820d2;	/* 4820ca: jge 0x4820d2 */
	M32((DWORD)(m->esp + 0x64u)) = m->edi;	/* 4820cc: mov dword ptr [esp + 0x64], edi */
	m->ebp = m->edi;	/* 4820d0: mov ebp, edi */
L_4820d2:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 4820d2: fld dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 4820d6: fadd dword ptr [esi + 0x8c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 4820dc: fsub dword ptr [esi + 0x64] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 4820df: fdiv dword ptr [esi + 0x80] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4820e5: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->esi + 0x74u));	/* 4820ea: mov ecx, dword ptr [esi + 0x74] */
	M32((DWORD)(m->esp + 0x68u)) = m->eax;	/* 4820ed: mov dword ptr [esp + 0x68], eax */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4820f1: dec ecx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4820f2: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_4820fa;	/* 4820f4: jle 0x4820fa */
	M32((DWORD)(m->esp + 0x68u)) = m->ecx;	/* 4820f6: mov dword ptr [esp + 0x68], ecx */
L_4820fa:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 4820fa: fld dword ptr [esp + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 4820fe: fsub dword ptr [esi + 0x8c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 482104: fsub dword ptr [esi + 0x5c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 482107: fdiv dword ptr [esi + 0x84] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48210d: call 0x49ec14 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482112: cmp eax, edi */
	M32((DWORD)(m->esp + 0x50u)) = m->eax;	/* 482114: mov dword ptr [esp + 0x50], eax */
	if (m->sf == m->of) goto L_48211e;	/* 482118: jge 0x48211e */
	M32((DWORD)(m->esp + 0x50u)) = m->edi;	/* 48211a: mov dword ptr [esp + 0x50], edi */
L_48211e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 48211e: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 482122: fadd dword ptr [esi + 0x8c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 482128: fsub dword ptr [esi + 0x5c] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 48212b: fdiv dword ptr [esi + 0x84] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 482131: call 0x49ec14 */
	m->edi = m->eax;	/* 482136: mov edi, eax */
	m->eax = M32((DWORD)(m->esi + 0x78u));	/* 482138: mov eax, dword ptr [esi + 0x78] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48213b: dec eax */
	M32((DWORD)(m->esp + 0x54u)) = m->edi;	/* 48213c: mov dword ptr [esp + 0x54], edi */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482140: cmp edi, eax */
	if (m->zf || m->sf != m->of) goto L_48214a;	/* 482142: jle 0x48214a */
	M32((DWORD)(m->esp + 0x54u)) = m->eax;	/* 482144: mov dword ptr [esp + 0x54], eax */
	m->edi = m->eax;	/* 482148: mov edi, eax */
L_48214a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 48214a: fld dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 48214e: fsub dword ptr [esi + 0x8c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 482154: fsub dword ptr [esi + 0x60] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 482157: fdiv dword ptr [esi + 0x88] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48215d: call 0x49ec14 */
	m->ebx = m->eax;	/* 482162: mov ebx, eax */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482164: test ebx, ebx */
	if (m->sf == m->of) goto L_48216a;	/* 482166: jge 0x48216a */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 482168: xor ebx, ebx */
L_48216a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 48216a: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8cu));	/* 48216e: fadd dword ptr [esi + 0x8c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 482174: fsub dword ptr [esi + 0x60] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 482177: fdiv dword ptr [esi + 0x88] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48217d: call 0x49ec14 */
	m->ecx = m->eax;	/* 482182: mov ecx, eax */
	m->eax = M32((DWORD)(m->esi + 0x7cu));	/* 482184: mov eax, dword ptr [esi + 0x7c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 482187: dec eax */
	M32((DWORD)(m->esp + 0x60u)) = m->ecx;	/* 482188: mov dword ptr [esp + 0x60], ecx */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48218c: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_482194;	/* 48218e: jle 0x482194 */
	M32((DWORD)(m->esp + 0x60u)) = m->eax;	/* 482190: mov dword ptr [esp + 0x60], eax */
L_482194:
	m->eax = M32((DWORD)(m->esp + 0x60u));	/* 482194: mov eax, dword ptr [esp + 0x60] */
	M32((DWORD)(m->esp + 0x4cu)) = m->ebx;	/* 482198: mov dword ptr [esp + 0x4c], ebx */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48219c: cmp ebx, eax */
	if (!m->zf && m->sf == m->of) goto L_4822f7;	/* 48219e: jg 0x4822f7 */
L_4821a4:
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 4821a4: mov eax, dword ptr [esp + 0x68] */
	M32((DWORD)(m->esp + 0x58u)) = m->ebp;	/* 4821a8: mov dword ptr [esp + 0x58], ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4821ac: cmp ebp, eax */
	if (!m->zf && m->sf == m->of) goto L_4822e2;	/* 4821ae: jg 0x4822e2 */
L_4821b4:
	m->ebx = M32((DWORD)(m->esp + 0x50u));	/* 4821b4: mov ebx, dword ptr [esp + 0x50] */
	m->eax = m->ebx;	/* 4821b8: mov eax, ebx */
	M32((DWORD)(m->esp + 0x5cu)) = m->ebx;	/* 4821ba: mov dword ptr [esp + 0x5c], ebx */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4821be: cmp eax, edi */
	if (!m->zf && m->sf == m->of) goto L_4822cd;	/* 4821c0: jg 0x4822cd */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x4cu)));	/* 4821c6: fild dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4821ca: fstp dword ptr [esp + 0x48] */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 4821ce: fild dword ptr [esp + 0x58] */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 4821d2: fstp dword ptr [esp + 0x58] */
L_4821d6:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x5cu)));	/* 4821d6: fild dword ptr [esp + 0x5c] */
	m->edx = M32((DWORD)(m->esi + 0x8cu));	/* 4821da: mov edx, dword ptr [esi + 0x8c] */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 4821e0: lea eax, [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4821e4: push edx */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 4821e5: lea ecx, [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 4821e9: fmul dword ptr [esi + 0x84] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4821ef: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4821f0: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 4821f1: mov ecx, dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x5cu));	/* 4821f5: fadd dword ptr [esi + 0x5c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4821f8: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x54u)));	/* 4821fc: fld dword ptr [esp + 0x54] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 482200: fmul dword ptr [esi + 0x88] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x60u));	/* 482206: fadd dword ptr [esi + 0x60] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482209: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x64u)));	/* 48220d: fld dword ptr [esp + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 482211: fmul dword ptr [esi + 0x80] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x64u));	/* 482217: fadd dword ptr [esi + 0x64] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 48221a: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 48221e: fld dword ptr [esp + 0x38] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x84u));	/* 482222: fadd dword ptr [esi + 0x84] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 482228: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 48222c: fld dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x88u));	/* 482230: fadd dword ptr [esi + 0x88] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 482236: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 48223a: fld dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x80u));	/* 48223e: fadd dword ptr [esi + 0x80] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 482244: fstp dword ptr [esp + 0x4c] */
	m->esp -= 4; M32(m->esp) = 0x48224du; native_call(m, 0x47fce0u);	/* 482248: call 0x47fce0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48224d: cmp eax, 1 */
	if (!m->zf) goto L_4822c0;	/* 482250: jne 0x4822c0 */
	m->edi = M32((DWORD)(m->esi + 0x74u));	/* 482252: mov edi, dword ptr [esi + 0x74] */
	m->edx = M32((DWORD)(m->esi + 0x54u));	/* 482255: mov edx, dword ptr [esi + 0x54] */
	{ long long p_ = (long long)(int)m->edi * (int)M32((DWORD)(m->esp + 0x4cu)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 482258: imul edi, dword ptr [esp + 0x4c] */
	{ DWORD a_ = m->edi, b_ = m->ebp & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48225d: add edi, ebp */
	{ long long p_ = (long long)(int)m->edi * (int)M32((DWORD)(m->esi + 0x78u)); DWORD r_ = (DWORD)p_; FLAGS(r_, 32); m->cf = m->of = p_ != (long long)(int)r_; m->edi = r_; }	/* 48225f: imul edi, dword ptr [esi + 0x78] */
	{ DWORD a_ = m->edi, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 482263: add edi, ebx */
	{ DWORD a_ = M16((DWORD)(m->edx + m->edi*2 + 0x0u)), b_ = 0xffffu & 0xffffu, r_ = (a_ - b_) & 0xffffu; FLAGS(r_, 16); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 15) & 1; }	/* 482265: cmp word ptr [edx + edi*2], 0xffff */
	if (!m->zf) goto L_482294;	/* 48226b: jne 0x482294 */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 48226d: mov eax, dword ptr [esi + 0x44] */
	{ DWORD v_ = 0x50u; m->esp -= 4; M32(m->esp) = v_; }	/* 482270: push 0x50 */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 482272: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482276: push eax */
	m->edx = (DWORD)(m->esp + 0x34u);	/* 482277: lea edx, [esp + 0x34] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48227b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48227c: push edx */
	m->ecx = m->esi;	/* 48227d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x482284u; native_call(m, 0x4818e0u);	/* 48227f: call 0x4818e0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482284: push eax */
	m->esp -= 4; M32(m->esp) = 0x48228au; native_call(m, 0x46cba0u);	/* 482285: call 0x46cba0 */
	m->ecx = M32((DWORD)(m->esi + 0x54u));	/* 48228a: mov ecx, dword ptr [esi + 0x54] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48228d: add esp, 0xc */
	M16((DWORD)(m->ecx + m->edi*2 + 0x0u)) = (WORD)((m->eax & 0xffff));	/* 482290: mov word ptr [ecx + edi*2], ax */
L_482294:
	m->edx = M32((DWORD)(m->esi + 0x94u));	/* 482294: mov edx, dword ptr [esi + 0x94] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48229a: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esi + 0x54u));	/* 48229e: mov ecx, dword ptr [esi + 0x54] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4822a1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4822a2: push eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4822a3: xor eax, eax */
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->ecx + m->edi*2 + 0x0u))) & 0xffff);	/* 4822a5: mov ax, word ptr [ecx + edi*2] */
	m->ecx = M32((DWORD)(m->esi + 0x44u));	/* 4822a9: mov ecx, dword ptr [esi + 0x44] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4822ac: lea edx, [eax + eax*4] */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4822af: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4822b2: add edx, ecx */
	m->ecx = m->esi;	/* 4822b4: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4822b6: push edx */
	m->esp -= 4; M32(m->esp) = 0x4822bcu; native_call(m, 0x481ae0u);	/* 4822b7: call 0x481ae0 */
	m->edi = M32((DWORD)(m->esp + 0x54u));	/* 4822bc: mov edi, dword ptr [esp + 0x54] */
L_4822c0:
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4822c0: inc ebx */
	{ DWORD a_ = m->ebx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4822c1: cmp ebx, edi */
	M32((DWORD)(m->esp + 0x5cu)) = m->ebx;	/* 4822c3: mov dword ptr [esp + 0x5c], ebx */
	if (m->zf || m->sf != m->of) goto L_4821d6;	/* 4822c7: jle 0x4821d6 */
L_4822cd:
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 4822cd: mov eax, dword ptr [esp + 0x68] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 4822d1: inc ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4822d2: cmp ebp, eax */
	M32((DWORD)(m->esp + 0x58u)) = m->ebp;	/* 4822d4: mov dword ptr [esp + 0x58], ebp */
	if (m->zf || m->sf != m->of) goto L_4821b4;	/* 4822d8: jle 0x4821b4 */
	m->ebp = M32((DWORD)(m->esp + 0x64u));	/* 4822de: mov ebp, dword ptr [esp + 0x64] */
L_4822e2:
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 4822e2: mov eax, dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esp + 0x60u));	/* 4822e6: mov ecx, dword ptr [esp + 0x60] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4822ea: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4822eb: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 4822ed: mov dword ptr [esp + 0x4c], eax */
	if (m->zf || m->sf != m->of) goto L_4821a4;	/* 4822f1: jle 0x4821a4 */
L_4822f7:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4822f7: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4822fb: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4822fc: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4822fd: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4822fe: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4822ff: add esp, 0x34 */
	m->esp += 4 + 36; return;	/* 482302: ret 0x24 */
L_482305:
	m->edi = M32(m->esp); m->esp += 4;	/* 482305: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 482306: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 482307: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 482308: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48230a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48230b: add esp, 0x34 */
	m->esp += 4 + 36; return;	/* 48230e: ret 0x24 */
}

/* load_482320 (0x482320), lifted by tools/lift.py */
static void lift_482320(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 482320: mov eax, dword ptr [esp + 0x18] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 482324: mov edx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 482328: push ebx */
	m->ebx = m->ecx;	/* 482329: mov ebx, ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 48232b: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48232f: push esi */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 482330: mov esi, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 482334: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482335: push eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 482336: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48233a: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 48233b: mov ecx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48233f: push edx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 482340: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482344: push eax */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 482345: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 482349: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48234a: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 48234b: mov ecx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48234f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482350: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482351: push ecx */
	m->ecx = m->ebx;	/* 482352: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x482359u; lift_481eb0(m);	/* 482354: call 0x481eb0 */
	m->edi = m->eax;	/* 482359: mov edi, eax */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48235b: test edi, edi */
	if (m->zf) goto L_4823ac;	/* 48235d: je 0x4823ac */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 48235f: mov eax, dword ptr [esi + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482362: test eax, eax */
	if (m->zf) goto L_482375;	/* 482364: je 0x482375 */
	M32((DWORD)(m->eax + 0xa0u)) = m->edi;	/* 482366: mov dword ptr [eax + 0xa0], edi */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 48236c: mov edx, dword ptr [esi + 4] */
	M32((DWORD)(m->edi + 0xa4u)) = m->edx;	/* 48236f: mov dword ptr [edi + 0xa4], edx */
L_482375:
	m->ecx = m->ebx;	/* 482375: mov ecx, ebx */
	M32((DWORD)(m->esi + 0x4u)) = m->edi;	/* 482377: mov dword ptr [esi + 4], edi */
	m->esp -= 4; M32(m->esp) = 0x48237fu; native_call(m, 0x4816c0u);	/* 48237a: call 0x4816c0 */
	M32((DWORD)(m->eax + 0x0u)) = m->edi;	/* 48237f: mov dword ptr [eax], edi */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 482381: mov ecx, dword ptr [esi + 8] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482384: test ecx, ecx */
	if (m->zf) goto L_4823a9;	/* 482386: je 0x4823a9 */
	m->ecx = M32((DWORD)(m->ecx + 0x0u));	/* 482388: mov ecx, dword ptr [ecx] */
	M32((DWORD)(m->ecx + 0xa0u)) = m->edi;	/* 48238a: mov dword ptr [ecx + 0xa0], edi */
	m->edx = M32((DWORD)(m->esi + 0x8u));	/* 482390: mov edx, dword ptr [esi + 8] */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 482393: mov ecx, dword ptr [eax] */
	m->edx = M32((DWORD)(m->edx + 0x0u));	/* 482395: mov edx, dword ptr [edx] */
	M32((DWORD)(m->ecx + 0xa4u)) = m->edx;	/* 482397: mov dword ptr [ecx + 0xa4], edx */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 48239d: mov ecx, dword ptr [esi + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 4823a0: mov dword ptr [ecx + 8], eax */
	m->edx = M32((DWORD)(m->esi + 0x8u));	/* 4823a3: mov edx, dword ptr [esi + 8] */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 4823a6: mov dword ptr [eax + 0xc], edx */
L_4823a9:
	M32((DWORD)(m->esi + 0x8u)) = m->eax;	/* 4823a9: mov dword ptr [esi + 8], eax */
L_4823ac:
	m->edi = M32(m->esp); m->esp += 4;	/* 4823ac: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4823ad: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4823ae: pop ebx */
	m->esp += 4 + 36; return;	/* 4823af: ret 0x24 */
}

/* space_buildUnits (0x4823c0), lifted by tools/lift.py */
static void lift_4823c0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4823c0: sub esp, 0x8c */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4823c6: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4823c7: push esi */
	m->esi = M32((DWORD)(m->esp + 0xa0u));	/* 4823c8: mov esi, dword ptr [esp + 0xa0] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4823cf: push edi */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4823d0: xor ebp, ebp */
	m->edi = m->ecx;	/* 4823d2: mov edi, ecx */
	{ DWORD a_ = m->esi, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4823d4: cmp esi, ebp */
	M32((DWORD)(m->esp + 0x4cu)) = m->edi;	/* 4823d6: mov dword ptr [esp + 0x4c], edi */
	if (!m->zf) goto L_4823f0;	/* 4823da: jne 0x4823f0 */
	m->eax = (DWORD)(m->esp + 0x58u);	/* 4823dc: lea eax, [esp + 0x58] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4823e0: push eax */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 4823e1: push 0xba6 */
	m->esp -= 4; M32(m->esp) = 0x4823ecu; native_call(m, M32(0x4a9270u));	/* 4823e6: call dword ptr [0x4a9270] */
	m->esi = (DWORD)(m->esp + 0x58u);	/* 4823ec: lea esi, [esp + 0x58] */
L_4823f0:
	m->ecx = m->edi;	/* 4823f0: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4823f7u; native_call(m, 0x4817f0u);	/* 4823f2: call 0x4817f0 */
	m->ecx = M32((DWORD)(m->esp + 0x9cu));	/* 4823f7: mov ecx, dword ptr [esp + 0x9c] */
	m->edx = m->eax;	/* 4823fe: mov edx, eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 482400: mov dword ptr [esp + 0x18], edx */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 482404: mov dword ptr [esp + 0x14], ebp */
	M32((DWORD)(m->edx + 0x0u)) = m->ecx;	/* 482408: mov dword ptr [edx], ecx */
	m->ecx = M32((DWORD)(m->esp + 0xa0u));	/* 48240a: mov ecx, dword ptr [esp + 0xa0] */
	{ DWORD a_ = M32((DWORD)(m->ecx + 0x10u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482411: cmp dword ptr [ecx + 0x10], ebp */
	if (m->zf || m->sf != m->of) goto L_482a29;	/* 482414: jle 0x482a29 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48241a: push ebx */
	M32((DWORD)(m->esp + 0x54u)) = m->ebp;	/* 48241b: mov dword ptr [esp + 0x54], ebp */
L_48241f:
	m->ebx = M32((DWORD)(m->ecx + 0x14u));	/* 48241f: mov ebx, dword ptr [ecx + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 482422: mov eax, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 482426: add ebx, eax */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 482428: mov eax, dword ptr [ebx] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x20u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48242a: test al, 0x20 */
	if (!m->zf) goto L_4829f8;	/* 48242c: jne 0x4829f8 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 482432: test al, 1 */
	M32((DWORD)(m->esp + 0x30u)) = m->ebp;	/* 482434: mov dword ptr [esp + 0x30], ebp */
	if (m->zf) goto L_482442;	/* 482438: je 0x482442 */
	M32((DWORD)(m->esp + 0x30u)) = 0x10u;	/* 48243a: mov dword ptr [esp + 0x30], 0x10 */
L_482442:
	m->eax = M32((DWORD)(m->ebx + 0x60u));	/* 482442: mov eax, dword ptr [ebx + 0x60] */
	M32((DWORD)(m->esp + 0x58u)) = m->ebp;	/* 482445: mov dword ptr [esp + 0x58], ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482449: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_4829f8;	/* 48244b: jle 0x4829f8 */
	M32((DWORD)(m->esp + 0x4cu)) = m->ebp;	/* 482451: mov dword ptr [esp + 0x4c], ebp */
	goto L_482459;	/* 482455: jmp 0x482459 */
L_482457:
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 482457: xor ebp, ebp */
L_482459:
	m->edi = M32((DWORD)(m->ebx + 0x64u));	/* 482459: mov edi, dword ptr [ebx + 0x64] */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 48245c: mov edx, dword ptr [esp + 0x4c] */
	{ DWORD a_ = m->edi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 482460: add edi, edx */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 482462: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 482464: sub eax, 4 */
	if (m->zf) goto L_482838;	/* 482467: je 0x482838 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48246d: dec eax */
	if (m->zf) goto L_48257a;	/* 48246e: je 0x48257a */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 482474: dec eax */
	if (!m->zf) goto L_4829cc;	/* 482475: jne 0x4829cc */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 48247b: mov eax, dword ptr [edi + 4] */
	m->ebp = 0x2u;	/* 48247e: mov ebp, 2 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482483: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_4829cc;	/* 482485: jle 0x4829cc */
L_48248b:
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 48248b: mov edx, dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->ebx + 0x50u));	/* 48248e: mov ecx, dword ptr [ebx + 0x50] */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 482491: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 482493: mov dword ptr [esp + 0x20], eax */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 482497: lea eax, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + m->eax*4 + 0x8u)));	/* 48249a: fld dword ptr [ecx + eax*4 + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 48249e: fmul dword ptr [esi + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 4824a1: fld dword ptr [esi + 0x10] */
	m->eax = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 4824a4: lea eax, [ecx + eax*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4824a7: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4824aa: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4824ac: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 4824ae: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4824b0: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 4824b2: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4824b5: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4824b9: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 4824bc: fmul dword ptr [esi + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4824bf: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4824c2: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4824c5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4824c7: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4824c9: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4824cc: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4824ce: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4824d1: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4824d5: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 4824d8: fmul dword ptr [esi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4824db: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4824de: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4824e1: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 4824e3: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4824e6: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4824e8: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4824ea: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4824ed: fstp dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 4824f1: mov edx, dword ptr [edi + 8] */
	m->ecx = M32((DWORD)(m->ebx + 0x50u));	/* 4824f4: mov ecx, dword ptr [ebx + 0x50] */
	m->eax = M32((DWORD)(m->edx + m->ebp*4 + 0xfffffffcu));	/* 4824f7: mov eax, dword ptr [edx + ebp*4 - 4] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4824fb: mov dword ptr [esp + 0x10], eax */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4824ff: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 482502: lea edx, [ecx + eax*4] */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 482505: lea eax, [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482509: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48250a: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48250b: push eax */
	m->esp -= 4; M32(m->esp) = 0x482511u; native_call(m, 0x482a40u);	/* 48250c: call 0x482a40 */
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 482511: mov ecx, dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->ecx + m->ebp*4 + 0x0u));	/* 482514: mov eax, dword ptr [ecx + ebp*4] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 482517: mov dword ptr [esp + 0x20], eax */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48251b: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 48251e: mov eax, dword ptr [ebx + 0x50] */
	m->ecx = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 482521: lea ecx, [eax + edx*4] */
	m->edx = (DWORD)(m->esp + 0x4cu);	/* 482524: lea edx, [esp + 0x4c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482528: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 482529: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48252a: push edx */
	m->esp -= 4; M32(m->esp) = 0x482530u; native_call(m, 0x482a40u);	/* 48252b: call 0x482a40 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 482530: add esp, 0x18 */
	m->eax = (DWORD)(m->esp + 0x40u);	/* 482533: lea eax, [esp + 0x40] */
	m->ecx = (DWORD)(m->esp + 0x34u);	/* 482537: lea ecx, [esp + 0x34] */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 48253b: lea edx, [esp + 0x24] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48253f: push eax */
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 482540: mov eax, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482544: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 482545: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482549: push edx */
	m->edx = M32((DWORD)(m->esp + 0x2cu));	/* 48254a: mov edx, dword ptr [esp + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48254e: push eax */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 48254f: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482553: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x30u));	/* 482554: mov ecx, dword ptr [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482558: push edx */
	m->edx = M32((DWORD)(m->esp + 0x48u));	/* 482559: mov edx, dword ptr [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48255d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48255e: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x70u));	/* 48255f: mov ecx, dword ptr [esp + 0x70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482563: push edx */
	m->esp -= 4; M32(m->esp) = 0x482569u; lift_482320(m);	/* 482564: call 0x482320 */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 482569: mov eax, dword ptr [edi + 4] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 48256c: inc ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48256d: cmp ebp, eax */
	if (m->sf != m->of) goto L_48248b;	/* 48256f: jl 0x48248b */
	goto L_4829cc;	/* 482575: jmp 0x4829cc */
L_48257a:
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 48257a: mov eax, dword ptr [edi + 4] */
	m->ebp = 0x2u;	/* 48257d: mov ebp, 2 */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482582: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_4829cc;	/* 482584: jle 0x4829cc */
L_48258a:
	m->eax = m->ebp;	/* 48258a: mov eax, ebp */
	{ DWORD a_ = m->eax, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48258c: and eax, 0x80000001 */
	if (!m->sf) goto L_482598;	/* 482591: jns 0x482598 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 482593: dec eax */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 482594: or eax, 0xfffffffe */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 482597: inc eax */
L_482598:
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 482598: mov ecx, dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 48259b: mov eax, dword ptr [ebx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 48259e: fld dword ptr [esi + 0x10] */
	m->ecx = M32((DWORD)(m->ecx + m->ebp*4 + 0xfffffff8u));	/* 4825a1: mov ecx, dword ptr [ecx + ebp*4 - 8] */
	m->edx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 4825a5: lea edx, [ecx + ecx*2] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x4u));	/* 4825a8: fmul dword ptr [eax + edx*4 + 4] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 4825ac: lea eax, [eax + edx*4] */
	if (!m->zf) goto L_4826d7;	/* 4825af: jne 0x4826d7 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4825b5: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 4825b7: fmul dword ptr [esi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4825b9: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4825bb: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 4825be: fmul dword ptr [esi + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4825c1: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 4825c3: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4825c6: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4825ca: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4825cc: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4825cf: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 4825d2: fmul dword ptr [esi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4825d5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4825d7: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4825da: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4825dd: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4825df: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 4825e2: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 4825e6: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4825e9: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 4825ec: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4825ef: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4825f2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 4825f4: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4825f7: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4825f9: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4825fb: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4825fe: fstp dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 482602: mov edx, dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->edx + m->ebp*4 + 0xfffffffcu));	/* 482605: mov eax, dword ptr [edx + ebp*4 - 4] */
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 482609: mov edx, dword ptr [ebx + 0x50] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 48260c: mov dword ptr [esp + 0x10], eax */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 482610: lea eax, [eax + eax*2] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + m->eax*4 + 0x0u)));	/* 482613: fld dword ptr [edx + eax*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 482616: fmul dword ptr [esi] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 482618: fld dword ptr [esi + 0x10] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 48261b: lea eax, [edx + eax*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 48261e: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482621: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 482623: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 482626: fmul dword ptr [esi + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482629: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 48262b: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 48262e: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 482632: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 482635: fmul dword ptr [esi + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 482638: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 48263b: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48263e: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 482640: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 482642: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482645: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 482647: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 48264a: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 48264e: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 482651: fmul dword ptr [esi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 482654: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 482657: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48265a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 48265c: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 48265e: fmul dword ptr [esi + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482661: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 482663: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482666: fstp dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 48266a: mov eax, dword ptr [edi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 48266d: fld dword ptr [esi + 0x10] */
	m->eax = M32((DWORD)(m->eax + m->ebp*4 + 0x0u));	/* 482670: mov eax, dword ptr [eax + ebp*4] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 482673: mov dword ptr [esp + 0x14], eax */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 482677: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 48267a: mov eax, dword ptr [ebx + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x4u));	/* 48267d: fmul dword ptr [eax + edx*4 + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 482681: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x0u));	/* 482683: fmul dword ptr [eax + edx*4] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 482686: lea eax, [eax + edx*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482689: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 48268b: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 48268e: fmul dword ptr [esi + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482691: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 482693: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 482696: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 48269a: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 48269d: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 48269f: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 4826a2: fmul dword ptr [esi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4826a5: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4826a7: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4826aa: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4826ad: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4826af: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 4826b2: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 4826b6: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 4826b9: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 4826bc: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 4826bf: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4826c2: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 4826c4: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4826c7: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4826c9: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4826cb: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 4826ce: fstp dword ptr [esp + 0x48] */
	goto L_4827f5;	/* 4826d2: jmp 0x4827f5 */
L_4826d7:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4826d7: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 4826da: fmul dword ptr [esi + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4826dd: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 4826df: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4826e1: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4826e3: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 4826e5: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 4826e8: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 4826ec: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4826ef: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4826f1: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 4826f4: fmul dword ptr [esi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4826f7: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4826f9: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4826fc: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4826ff: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 482701: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 482704: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 482708: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 48270b: fmul dword ptr [esi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 48270e: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 482711: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482714: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 482716: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 482719: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48271b: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 48271d: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 482720: fstp dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 482724: mov edx, dword ptr [edi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 482727: fld dword ptr [esi + 0x10] */
	m->eax = M32((DWORD)(m->edx + m->ebp*4 + 0x0u));	/* 48272a: mov eax, dword ptr [edx + ebp*4] */
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 48272d: mov edx, dword ptr [ebx + 0x50] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 482730: mov dword ptr [esp + 0x14], eax */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 482734: lea eax, [eax + eax*2] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + m->eax*4 + 0x4u));	/* 482737: fmul dword ptr [edx + eax*4 + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 48273b: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + m->eax*4 + 0x0u));	/* 48273d: fmul dword ptr [edx + eax*4] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 482740: lea eax, [edx + eax*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482743: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 482745: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 482748: fmul dword ptr [esi + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48274b: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 48274d: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 482750: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 482754: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 482756: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 482759: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 48275c: fmul dword ptr [esi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48275f: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 482761: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 482764: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482767: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 482769: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 48276c: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 482770: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 482773: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 482776: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 482779: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48277c: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 48277e: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 482781: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482783: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 482785: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 482788: fstp dword ptr [esp + 0x48] */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 48278c: mov eax, dword ptr [edi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 48278f: fld dword ptr [esi + 0x10] */
	m->eax = M32((DWORD)(m->eax + m->ebp*4 + 0xfffffffcu));	/* 482792: mov eax, dword ptr [eax + ebp*4 - 4] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 482796: mov dword ptr [esp + 0x10], eax */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48279a: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 48279d: mov eax, dword ptr [ebx + 0x50] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x4u));	/* 4827a0: fmul dword ptr [eax + edx*4 + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x8u)));	/* 4827a4: fld dword ptr [eax + edx*4 + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 4827a8: fmul dword ptr [esi + 0x20] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 4827ab: lea eax, [eax + edx*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4827ae: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 4827b0: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4827b2: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4827b4: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 4827b6: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 4827b9: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4827bd: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 4827c0: fmul dword ptr [esi + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4827c3: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4827c6: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4827c9: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 4827cb: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 4827cd: fmul dword ptr [esi + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4827d0: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4827d2: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4827d5: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 4827d9: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4827dc: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4827de: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 4827e1: fmul dword ptr [esi + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4827e4: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4827e6: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 4827e9: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4827ec: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4827ee: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 4827f1: fstp dword ptr [esp + 0x3c] */
L_4827f5:
	m->edx = (DWORD)(m->esp + 0x40u);	/* 4827f5: lea edx, [esp + 0x40] */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 4827f9: lea eax, [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4827fd: push edx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 4827fe: lea edx, [esp + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482802: push eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 482803: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482807: push edx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 482808: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48280c: push eax */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 48280d: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482811: push edx */
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 482812: mov edx, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482816: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 482817: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48281b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48281c: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x70u));	/* 48281d: mov ecx, dword ptr [esp + 0x70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482821: push edx */
	m->esp -= 4; M32(m->esp) = 0x482827u; lift_482320(m);	/* 482822: call 0x482320 */
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 482827: mov eax, dword ptr [edi + 4] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 48282a: inc ebp */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48282b: cmp ebp, eax */
	if (m->sf != m->of) goto L_48258a;	/* 48282d: jl 0x48258a */
	goto L_4829cc;	/* 482833: jmp 0x4829cc */
L_482838:
	m->eax = M32((DWORD)(m->edi + 0x4u));	/* 482838: mov eax, dword ptr [edi + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->ebp;	/* 48283b: mov dword ptr [esp + 0x20], ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48283f: cmp eax, ebp */
	if (m->zf || m->sf != m->of) goto L_4829cc;	/* 482841: jle 0x4829cc */
	m->ebp = 0x8u;	/* 482847: mov ebp, 8 */
L_48284c:
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 48284c: mov eax, dword ptr [edi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 48284f: fld dword ptr [esi + 0x10] */
	m->ecx = M32((DWORD)(m->eax + m->ebp*1 + 0xfffffff8u));	/* 482852: mov ecx, dword ptr [eax + ebp - 8] */
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 482856: mov eax, dword ptr [ebx + 0x50] */
	m->edx = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 482859: lea edx, [ecx + ecx*2] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x4u));	/* 48285c: fmul dword ptr [eax + edx*4 + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 482860: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + m->edx*4 + 0x0u));	/* 482862: fmul dword ptr [eax + edx*4] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 482865: lea eax, [eax + edx*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482868: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 48286a: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 48286d: fmul dword ptr [esi + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482870: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 482872: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0); FPOP();	/* 482875: fstp dword ptr [esp + 0x24] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 482879: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 48287c: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 48287e: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 482881: fmul dword ptr [esi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482884: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 482886: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 482889: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48288c: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 48288e: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 482891: fstp dword ptr [esp + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 482895: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 482898: fmul dword ptr [eax + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 48289b: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 48289e: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4828a1: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 4828a3: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4828a6: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4828a8: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 4828aa: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x2cu)) = (float)ST(0); FPOP();	/* 4828ad: fstp dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 4828b1: mov edx, dword ptr [edi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 4828b4: fld dword ptr [esi + 0x10] */
	m->eax = M32((DWORD)(m->edx + m->ebp*1 + 0xfffffffcu));	/* 4828b7: mov eax, dword ptr [edx + ebp - 4] */
	m->edx = M32((DWORD)(m->ebx + 0x50u));	/* 4828bb: mov edx, dword ptr [ebx + 0x50] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4828be: mov dword ptr [esp + 0x10], eax */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4828c2: lea eax, [eax + eax*2] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4828c5: fmul dword ptr [edx + eax*4 + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx + m->eax*4 + 0x8u)));	/* 4828c9: fld dword ptr [edx + eax*4 + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 4828cd: fmul dword ptr [esi + 0x20] */
	m->eax = (DWORD)(m->edx + m->eax*4 + 0x0u);	/* 4828d0: lea eax, [edx + eax*4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4828d3: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 4828d5: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4828d7: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4828d9: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 4828db: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 4828de: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 4828e2: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 4828e5: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4828e7: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 4828ea: fmul dword ptr [esi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4828ed: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 4828ef: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 4828f2: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 4828f5: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 4828f7: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 4828fa: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 4828fe: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x28u));	/* 482901: fmul dword ptr [esi + 0x28] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 482904: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x18u));	/* 482907: fmul dword ptr [esi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48290a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 48290c: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 48290f: fmul dword ptr [eax] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482911: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 482913: fadd dword ptr [esi + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482916: fstp dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 48291a: mov eax, dword ptr [edi + 8] */
	m->eax = M32((DWORD)(m->eax + m->ebp*1 + 0x0u));	/* 48291d: mov eax, dword ptr [eax + ebp] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 482920: mov dword ptr [esp + 0x14], eax */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 482924: lea edx, [eax + eax*2] */
	m->eax = M32((DWORD)(m->ebx + 0x50u));	/* 482927: mov eax, dword ptr [ebx + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + m->edx*4 + 0x8u)));	/* 48292a: fld dword ptr [eax + edx*4 + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20u));	/* 48292e: fmul dword ptr [esi + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x10u)));	/* 482931: fld dword ptr [esi + 0x10] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 482934: lea eax, [eax + edx*4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 482937: fmul dword ptr [eax + 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48293a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x0u)));	/* 48293c: fld dword ptr [esi] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 48293e: fmul dword ptr [eax] */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 482940: lea edx, [esp + 0x40] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482944: push edx */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 482945: lea edx, [esp + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482949: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x30u));	/* 48294b: fadd dword ptr [esi + 0x30] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 48294e: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 482952: fld dword ptr [eax] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 482954: fmul dword ptr [esi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x8u)));	/* 482957: fld dword ptr [eax + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x24u));	/* 48295a: fmul dword ptr [esi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48295d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x4u)));	/* 48295f: fld dword ptr [eax + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x14u));	/* 482962: fmul dword ptr [esi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482965: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x34u));	/* 482967: fadd dword ptr [esi + 0x34] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 48296a: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x8u)));	/* 48296e: fld dword ptr [esi + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x0u));	/* 482971: fmul dword ptr [eax] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x28u)));	/* 482973: fld dword ptr [esi + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x8u));	/* 482976: fmul dword ptr [eax + 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 482979: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x18u)));	/* 48297b: fld dword ptr [esi + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->eax + 0x4u));	/* 48297e: fmul dword ptr [eax + 4] */
	m->eax = (DWORD)(m->esp + 0x38u);	/* 482981: lea eax, [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482985: push eax */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 482986: mov eax, dword ptr [esp + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 48298a: faddp st(1) */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48298c: push edx */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 48298d: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482991: push eax */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 482992: mov eax, dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x38u));	/* 482996: fadd dword ptr [esi + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482999: push edx */
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 48299a: mov edx, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48299e: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 48299f: mov ecx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4829a3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4829a4: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x70u));	/* 4829a5: mov ecx, dword ptr [esp + 0x70] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4829a9: push edx */
	MF((DWORD)(m->esp + 0x6cu)) = (float)ST(0); FPOP();	/* 4829aa: fstp dword ptr [esp + 0x6c] */
	m->esp -= 4; M32(m->esp) = 0x4829b3u; lift_482320(m);	/* 4829ae: call 0x482320 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 4829b3: mov eax, dword ptr [esp + 0x20] */
	m->ecx = M32((DWORD)(m->edi + 0x4u));	/* 4829b7: mov ecx, dword ptr [edi + 4] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4829ba: add eax, 3 */
	{ DWORD a_ = m->ebp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4829bd: add ebp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4829c0: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 4829c2: mov dword ptr [esp + 0x20], eax */
	if (m->sf != m->of) goto L_48284c;	/* 4829c6: jl 0x48284c */
L_4829cc:
	m->eax = M32((DWORD)(m->esp + 0x58u));	/* 4829cc: mov eax, dword ptr [esp + 0x58] */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 4829d0: mov edx, dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->ebx + 0x60u));	/* 4829d4: mov ecx, dword ptr [ebx + 0x60] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4829d7: inc eax */
	{ DWORD a_ = m->edx, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4829d8: add edx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4829db: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 4829dd: mov dword ptr [esp + 0x58], eax */
	M32((DWORD)(m->esp + 0x4cu)) = m->edx;	/* 4829e1: mov dword ptr [esp + 0x4c], edx */
	if (m->sf != m->of) goto L_482457;	/* 4829e5: jl 0x482457 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4829eb: mov edx, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0xa4u));	/* 4829ef: mov ecx, dword ptr [esp + 0xa4] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 4829f6: xor ebp, ebp */
L_4829f8:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 4829f8: mov eax, dword ptr [esp + 0x18] */
	m->ebx = M32((DWORD)(m->esp + 0x54u));	/* 4829fc: mov ebx, dword ptr [esp + 0x54] */
	m->edi = M32((DWORD)(m->ecx + 0x10u));	/* 482a00: mov edi, dword ptr [ecx + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 482a03: inc eax */
	{ DWORD a_ = m->ebx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 482a04: add ebx, 0x80 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482a0a: cmp eax, edi */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 482a0c: mov dword ptr [esp + 0x18], eax */
	M32((DWORD)(m->esp + 0x54u)) = m->ebx;	/* 482a10: mov dword ptr [esp + 0x54], ebx */
	if (m->sf != m->of) goto L_48241f;	/* 482a14: jl 0x48241f */
	m->ebx = M32(m->esp); m->esp += 4;	/* 482a1a: pop ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 482a1b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 482a1c: pop esi */
	m->eax = m->edx;	/* 482a1d: mov eax, edx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 482a1f: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 482a20: add esp, 0x8c */
	m->esp += 4 + 12; return;	/* 482a26: ret 0xc */
L_482a29:
	m->edi = M32(m->esp); m->esp += 4;	/* 482a29: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 482a2a: pop esi */
	m->eax = m->edx;	/* 482a2b: mov eax, edx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 482a2d: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 482a2e: add esp, 0x8c */
	m->esp += 4 + 12; return;	/* 482a34: ret 0xc */
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
