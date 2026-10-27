/* ---- emulated machine for lifted functions (tools/lift.py) ---- */
#if 0 /* X86 comes from the earlier lifted file */
typedef struct { DWORD eax, ecx, edx, ebx, esp, ebp, esi, edi; int zf, sf, cf, of; long double fs[8]; int ft; DWORD fsw; } X86;
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

static void lift_482e30(X86 *m);

/* space_testSphere (0x482e30), lifted by tools/lift.py */
static void lift_482e30(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 482e30: sub esp, 0x3c */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 482e33: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x4cu));	/* 482e34: mov ebx, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 482e38: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 482e39: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 482e3a: push edi */
	m->eax = m->ebx;	/* 482e3b: mov eax, ebx */
	m->edi = m->ecx;	/* 482e3d: mov edi, ecx */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 482e3f: mov ecx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 482e41: mov dword ptr [esp + 0x28], ecx */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 482e45: lea ecx, [esp + 0x28] */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 482e49: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x2cu)) = m->edx;	/* 482e4c: mov dword ptr [esp + 0x2c], edx */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 482e50: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->esp + 0x30u)) = m->eax;	/* 482e53: mov dword ptr [esp + 0x30], eax */
	m->esp -= 4; M32(m->esp) = 0x482e5cu; lift_467760(m);	/* 482e57: call 0x467760 */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 482e5c: fdiv dword ptr [esp + 0x5c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 482e60: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 482e65: fld dword ptr [esp + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 482e69: fmul dword ptr [esp + 0x5c] */
	m->ebp = M32((DWORD)(m->esp + 0x7cu));	/* 482e6d: mov ebp, dword ptr [esp + 0x7c] */
	m->esi = M32((DWORD)(m->esp + 0x54u));	/* 482e71: mov esi, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 482e75: test eax, eax */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 482e77: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 482e7b: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 482e7f: fmul dword ptr [esp + 0x5c] */
	m->ecx = M32((DWORD)(m->esp + 0x34u));	/* 482e83: mov ecx, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0x58u)) = m->eax;	/* 482e87: mov dword ptr [esp + 0x58], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 482e8b: mov dword ptr [esp + 0x10], ecx */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 482e8f: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 482e93: fld dword ptr [esp + 0x30] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x5cu));	/* 482e97: fmul dword ptr [esp + 0x5c] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 482e9b: mov edx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x5cu)) = 0x0u;	/* 482e9f: mov dword ptr [esp + 0x5c], 0 */
	M32((DWORD)(m->esp + 0x14u)) = m->edx;	/* 482ea7: mov dword ptr [esp + 0x14], edx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482eab: fstp dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 482eaf: mov ecx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 482eb3: mov dword ptr [esp + 0x18], ecx */
	if (m->zf || m->sf != m->of) goto L_482f65;	/* 482eb7: jle 0x482f65 */
L_482ebd:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x5cu)));	/* 482ebd: fild dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 482ec1: fld dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 482ec5: push ebp */
	ST(0) = ST(0) * ST(1);	/* 482ec6: fmul st(1) */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 482ec8: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 482ecc: fld dword ptr [esp + 0x18] */
	ST(0) = ST(0) * ST(1);	/* 482ed0: fmul st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 482ed2: fstp dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 482ed6: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 482eda: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 482ede: fadd dword ptr [esi] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 482ee0: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 482ee4: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 482ee8: fadd dword ptr [esi + 4] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 482eeb: mov edx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 482eef: mov dword ptr [esp + 0x20], edx */
	m->edx = M32((DWORD)(m->esp + 0x7cu));	/* 482ef3: mov edx, dword ptr [esp + 0x7c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482ef7: fstp dword ptr [esp + 0x3c] */
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 482efb: mov eax, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482eff: push edx */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 482f00: fadd dword ptr [esi + 8] */
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 482f03: mov edx, dword ptr [esp + 0x74] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 482f07: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(m->esp + 0x7cu));	/* 482f0b: mov eax, dword ptr [esp + 0x7c] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 482f0f: fstp dword ptr [esp + 0x44] */
	m->ecx = M32((DWORD)(m->esp + 0x44u));	/* 482f13: mov ecx, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482f17: push eax */
	m->eax = M32((DWORD)(m->esp + 0x74u));	/* 482f18: mov eax, dword ptr [esp + 0x74] */
	M32((DWORD)(m->esp + 0x30u)) = m->ecx;	/* 482f1c: mov dword ptr [esp + 0x30], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x7cu));	/* 482f20: mov ecx, dword ptr [esp + 0x7c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482f24: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x74u));	/* 482f25: mov ecx, dword ptr [esp + 0x74] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482f29: push edx */
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 482f2a: mov edx, dword ptr [esp + 0x74] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482f2e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482f2f: push ecx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 482f30: lea eax, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482f34: push edx */
	m->edx = M32((DWORD)(m->esp + 0x70u));	/* 482f35: mov edx, dword ptr [esp + 0x70] */
	m->ecx = (DWORD)(m->esp + 0x3cu);	/* 482f39: lea ecx, [esp + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482f3d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 482f3e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 482f3f: push edx */
	m->ecx = m->edi;	/* 482f40: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x482f47u; lift_482aa0(m);	/* 482f42: call 0x482aa0 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482f47: cmp eax, 1 */
	if (m->zf) goto L_483051;	/* 482f4a: je 0x483051 */
	m->eax = M32((DWORD)(m->esp + 0x5cu));	/* 482f50: mov eax, dword ptr [esp + 0x5c] */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 482f54: mov ecx, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 482f58: inc eax */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 482f59: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x5cu)) = m->eax;	/* 482f5b: mov dword ptr [esp + 0x5c], eax */
	if (m->sf != m->of) goto L_482ebd;	/* 482f5f: jl 0x482ebd */
L_482f65:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x58u)));	/* 482f65: fild dword ptr [esp + 0x58] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 482f69: push ebp */
	{ long double t = ST(0); FPUSH(t); }	/* 482f6a: fld st(0) */
	{ long double t = ST(0); FPUSH(t); }	/* 482f6c: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 482f6e: fmul dword ptr [esp + 0x14] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 482f72: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 482f76: fld dword ptr [esp + 0x18] */
	ST(0) = ST(0) * ST(1);	/* 482f7a: fmul st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 482f7c: fstp dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 482f80: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x44u)));	/* 482f84: fld dword ptr [esp + 0x44] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x0u));	/* 482f88: fadd dword ptr [esi] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 482f8a: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x48u)));	/* 482f8e: fld dword ptr [esp + 0x48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x4u));	/* 482f92: fadd dword ptr [esi + 4] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 482f95: mov eax, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 482f99: mov dword ptr [esp + 0x20], eax */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482f9d: fstp dword ptr [esp + 0x3c] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 482fa1: mov ecx, dword ptr [esp + 0x3c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x8u));	/* 482fa5: fadd dword ptr [esi + 8] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 482fa8: mov dword ptr [esp + 0x24], ecx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 482fac: fstp dword ptr [esp + 0x40] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 482fb0: mov edx, dword ptr [esp + 0x40] */
	{ long double t = ST(0); FPUSH(t); }	/* 482fb4: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x14u));	/* 482fb6: fmul dword ptr [esp + 0x14] */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 482fba: mov dword ptr [esp + 0x28], edx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 482fbe: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 482fc2: fld dword ptr [esp + 0x18] */
	ST(0) = ST(0) * ST(1);	/* 482fc6: fmul st(1) */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 482fc8: fstp dword ptr [esp + 0x48] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x1cu));	/* 482fcc: fmul dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 482fd0: fld dword ptr [ebx] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x44u));	/* 482fd2: fsub dword ptr [esp + 0x44] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 482fd6: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 482fda: fld dword ptr [ebx + 4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x48u));	/* 482fdd: fsub dword ptr [esp + 0x48] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 482fe1: mov eax, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x44u)) = m->eax;	/* 482fe5: mov dword ptr [esp + 0x44], eax */
	m->eax = M32((DWORD)(m->esp + 0x7cu));	/* 482fe9: mov eax, dword ptr [esp + 0x7c] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 482fed: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 482ff1: fld dword ptr [ebx + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 482ff4: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 482ff8: push eax */
	ST(0) = ST(0) - ST(1);	/* 482ff9: fsub st(1) */
	m->eax = M32((DWORD)(m->esp + 0x74u));	/* 482ffb: mov eax, dword ptr [esp + 0x74] */
	M32((DWORD)(m->esp + 0x4cu)) = m->ecx;	/* 482fff: mov dword ptr [esp + 0x4c], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x7cu));	/* 483003: mov ecx, dword ptr [esp + 0x7c] */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 483007: fstp dword ptr [esp + 0x44] */
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 48300b: mov edx, dword ptr [esp + 0x44] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48300f: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x74u));	/* 483010: mov ecx, dword ptr [esp + 0x74] */
	M32((DWORD)(m->esp + 0x54u)) = m->edx;	/* 483014: mov dword ptr [esp + 0x54], edx */
	m->edx = M32((DWORD)(m->esp + 0x7cu));	/* 483018: mov edx, dword ptr [esp + 0x7c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48301c: push edx */
	m->edx = M32((DWORD)(m->esp + 0x74u));	/* 48301d: mov edx, dword ptr [esp + 0x74] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483021: push eax */
	m->eax = M32((DWORD)(m->esp + 0x74u));	/* 483022: mov eax, dword ptr [esp + 0x74] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483026: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483027: push edx */
	m->ecx = (DWORD)(m->esp + 0x5cu);	/* 483028: lea ecx, [esp + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48302c: push eax */
	m->eax = M32((DWORD)(m->esp + 0x70u));	/* 48302d: mov eax, dword ptr [esp + 0x70] */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 483031: lea edx, [esp + 0x3c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483035: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483036: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483037: push eax */
	m->ecx = m->edi;	/* 483038: mov ecx, edi */
	ST(0) = ST(0); FPOP();	/* 48303a: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x483041u; lift_482aa0(m);	/* 48303c: call 0x482aa0 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 483041: dec eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 483042: pop edi */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 483043: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 483045: sbb eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 483047: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 483048: pop ebp */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 483049: inc eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48304a: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48304b: add esp, 0x3c */
	m->esp += 4 + 48; return;	/* 48304e: ret 0x30 */
L_483051:
	m->edi = M32(m->esp); m->esp += 4;	/* 483051: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 483052: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 483053: pop ebp */
	m->eax = 0x1u;	/* 483054: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 483059: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48305a: add esp, 0x3c */
	m->esp += 4 + 48; return;	/* 48305d: ret 0x30 */
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
