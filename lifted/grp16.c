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

static void lift_4729b0(X86 *m);

/* camera_setupView (0x4729b0), lifted by tools/lift.py */
static void lift_4729b0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4729b0: sub esp, 0x34 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4729b3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4729b4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4729b5: push esi */
	m->esi = m->ecx;	/* 4729b6: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4729b8: push edi */
	m->edi = (DWORD)(m->esi + 0x20f3970u);	/* 4729b9: lea edi, [esi + 0x20f3970] */
	m->eax = (DWORD)(m->esi + 0x20f3994u);	/* 4729bf: lea eax, [esi + 0x20f3994] */
	m->ecx = m->edi;	/* 4729c5: mov ecx, edi */
	m->ebx = (DWORD)(m->esi + 0x20f39a0u);	/* 4729c7: lea ebx, [esi + 0x20f39a0] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4729cd: push ebx */
	m->edx = M32((DWORD)(m->ecx + 0x0u));	/* 4729ce: mov edx, dword ptr [ecx] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 4729d0: mov dword ptr [eax], edx */
	m->edx = M32((DWORD)(m->ecx + 0x4u));	/* 4729d2: mov edx, dword ptr [ecx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->edx;	/* 4729d5: mov dword ptr [eax + 4], edx */
	m->edx = (DWORD)(m->esi + 0x20f39e0u);	/* 4729d8: lea edx, [esi + 0x20f39e0] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 4729de: mov ecx, dword ptr [ecx + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4729e1: push edx */
	M32((DWORD)(m->eax + 0x8u)) = m->ecx;	/* 4729e2: mov dword ptr [eax + 8], ecx */
	m->esp -= 4; M32(m->esp) = 0x4729eau; native_call(m, 0x47d5a0u);	/* 4729e5: call 0x47d5a0 */
	m->eax = M32((DWORD)(m->esp + 0x50u));	/* 4729ea: mov eax, dword ptr [esp + 0x50] */
	m->ecx = m->edi;	/* 4729ee: mov ecx, edi */
	m->ebp = (DWORD)(m->esi + 0x20f397cu);	/* 4729f0: lea ebp, [esi + 0x20f397c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4729f6: add esp, 8 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 4729f9: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 4729fb: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 4729fd: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 472a00: mov dword ptr [ecx + 4], edx */
	m->edx = m->ebp;	/* 472a03: mov edx, ebp */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 472a05: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 472a08: mov dword ptr [ecx + 8], eax */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 472a0b: mov ecx, dword ptr [esp + 0x4c] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 472a0f: mov eax, dword ptr [ecx] */
	M32((DWORD)(m->edx + 0x0u)) = m->eax;	/* 472a11: mov dword ptr [edx], eax */
	m->eax = M32((DWORD)(m->ecx + 0x4u));	/* 472a13: mov eax, dword ptr [ecx + 4] */
	M32((DWORD)(m->edx + 0x4u)) = m->eax;	/* 472a16: mov dword ptr [edx + 4], eax */
	m->eax = (DWORD)(m->esi + 0x20f3988u);	/* 472a19: lea eax, [esi + 0x20f3988] */
	m->ecx = M32((DWORD)(m->ecx + 0x8u));	/* 472a1f: mov ecx, dword ptr [ecx + 8] */
	M32((DWORD)(m->edx + 0x8u)) = m->ecx;	/* 472a22: mov dword ptr [edx + 8], ecx */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 472a25: mov edx, dword ptr [esp + 0x50] */
	m->ecx = M32((DWORD)(m->edx + 0x0u));	/* 472a29: mov ecx, dword ptr [edx] */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 472a2b: mov dword ptr [eax], ecx */
	m->ecx = M32((DWORD)(m->edx + 0x4u));	/* 472a2d: mov ecx, dword ptr [edx + 4] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 472a30: mov dword ptr [eax + 4], ecx */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 472a33: mov edx, dword ptr [edx + 8] */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 472a36: mov dword ptr [eax + 8], edx */
	m->esp -= 4; M32(m->esp) = 0x472a3fu; native_call(m, M32(0x4a9204u));	/* 472a39: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x472a45u; native_call(m, M32(0x4a9218u));	/* 472a3f: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3990u)));	/* 472a45: fld dword ptr [esi + 0x20f3990] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a4b: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 472a4e: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f398cu)));	/* 472a51: fld dword ptr [esi + 0x20f398c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a57: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 472a5a: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3988u)));	/* 472a5d: fld dword ptr [esi + 0x20f3988] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a63: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 472a66: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3984u)));	/* 472a69: fld dword ptr [esi + 0x20f3984] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3978u));	/* 472a6f: fadd dword ptr [esi + 0x20f3978] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a75: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a78: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 472a7b: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3980u)));	/* 472a7f: fld dword ptr [esi + 0x20f3980] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3974u));	/* 472a85: fadd dword ptr [esi + 0x20f3974] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a8b: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a8e: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x10u)) = (double)ST(0); FPOP();	/* 472a91: fstp qword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x0u)));	/* 472a95: fld dword ptr [ebp] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 472a98: fadd dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a9a: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472a9d: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x18u)) = (double)ST(0); FPOP();	/* 472aa0: fstp qword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3978u)));	/* 472aa4: fld dword ptr [esi + 0x20f3978] */
	MDBL((DWORD)(m->esp + 0x10u)) = (double)ST(0); FPOP();	/* 472aaa: fstp qword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3974u)));	/* 472aae: fld dword ptr [esi + 0x20f3974] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 472ab4: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 472ab8: fld dword ptr [edi] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 472aba: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x472ac2u; native_call(m, 0x4509d2u);	/* 472abd: call 0x4509d2 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 472ac2: push ebx */
	{ DWORD v_ = 0xba6u; m->esp -= 4; M32(m->esp) = v_; }	/* 472ac3: push 0xba6 */
	m->ebp = M32((DWORD)(0x4a9270u));	/* 472ac8: mov ebp, dword ptr [0x4a9270] */
	m->esp -= 4; M32(m->esp) = 0x472ad0u; native_call(m, m->ebp);	/* 472ace: call ebp */
	m->esp -= 4; M32(m->esp) = 0x472ad6u; native_call(m, M32(0x4a9258u));	/* 472ad0: call dword ptr [0x4a9258] */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 472ad6: mov eax, dword ptr [esp + 0x54] */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 472ada: mov ecx, dword ptr [esp + 0x58] */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 472ade: mov edx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->esi + 0x20f3a20u)) = m->eax;	/* 472ae2: mov dword ptr [esi + 0x20f3a20], eax */
	m->eax = M32((DWORD)(m->esp + 0x60u));	/* 472ae8: mov eax, dword ptr [esp + 0x60] */
	M32((DWORD)(m->esi + 0x20f3a24u)) = m->ecx;	/* 472aec: mov dword ptr [esi + 0x20f3a24], ecx */
	m->ecx = M32((DWORD)(m->esp + 0x64u));	/* 472af2: mov ecx, dword ptr [esp + 0x64] */
	{ DWORD v_ = 0x1701u; m->esp -= 4; M32(m->esp) = v_; }	/* 472af6: push 0x1701 */
	M32((DWORD)(m->esi + 0x20f3a28u)) = m->edx;	/* 472afb: mov dword ptr [esi + 0x20f3a28], edx */
	M32((DWORD)(m->esi + 0x20f3a2cu)) = m->eax;	/* 472b01: mov dword ptr [esi + 0x20f3a2c], eax */
	M32((DWORD)(m->esi + 0x20f3a30u)) = m->ecx;	/* 472b07: mov dword ptr [esi + 0x20f3a30], ecx */
	m->esp -= 4; M32(m->esp) = 0x472b13u; native_call(m, M32(0x4a91fcu));	/* 472b0d: call dword ptr [0x4a91fc] */
	m->esp -= 4; M32(m->esp) = 0x472b19u; native_call(m, M32(0x4a9204u));	/* 472b13: call dword ptr [0x4a9204] */
	m->esp -= 4; M32(m->esp) = 0x472b1fu; native_call(m, M32(0x4a9218u));	/* 472b19: call dword ptr [0x4a9218] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a30u)));	/* 472b1f: fld dword ptr [esi + 0x20f3a30] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472b25: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 472b28: fstp qword ptr [esp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a2cu)));	/* 472b2b: fld dword ptr [esi + 0x20f3a2c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472b31: sub esp, 8 */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 472b34: fstp qword ptr [esp] */
	FPUSH((long double)(int)M32((DWORD)(m->esi + 0x20f3a24u)));	/* 472b37: fild dword ptr [esi + 0x20f3a24] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472b3d: sub esp, 8 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472b40: sub esp, 8 */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(m->esi + 0x20f3a28u));	/* 472b43: fidiv dword ptr [esi + 0x20f3a28] */
	MDBL((DWORD)(m->esp + 0x8u)) = (double)ST(0); FPOP();	/* 472b49: fstp qword ptr [esp + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a20u)));	/* 472b4d: fld dword ptr [esi + 0x20f3a20] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 472b53: fstp qword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x472b5bu; native_call(m, 0x4509c6u);	/* 472b56: call 0x4509c6 */
	m->edi = (DWORD)(m->esi + 0x20f3a34u);	/* 472b5b: lea edi, [esi + 0x20f3a34] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 472b61: push edi */
	{ DWORD v_ = 0xba7u; m->esp -= 4; M32(m->esp) = v_; }	/* 472b62: push 0xba7 */
	m->esp -= 4; M32(m->esp) = 0x472b69u; native_call(m, m->ebp);	/* 472b67: call ebp */
	m->esp -= 4; M32(m->esp) = 0x472b6fu; native_call(m, M32(0x4a9258u));	/* 472b69: call dword ptr [0x4a9258] */
	{ DWORD v_ = 0x1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 472b6f: push 0x1700 */
	m->esp -= 4; M32(m->esp) = 0x472b7au; native_call(m, M32(0x4a91fcu));	/* 472b74: call dword ptr [0x4a91fc] */
	m->eax = (DWORD)(m->esi + 0x20f3a74u);	/* 472b7a: lea eax, [esi + 0x20f3a74] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 472b80: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 472b81: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 472b82: push eax */
	m->esp -= 4; M32(m->esp) = 0x472b88u; native_call(m, 0x47d380u);	/* 472b83: call 0x47d380 */
	m->eax = M32((DWORD)(m->esi + 0x2149308u));	/* 472b88: mov eax, dword ptr [esi + 0x2149308] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 472b8e: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472b91: test eax, eax */
	if (m->zf) goto L_472ba3;	/* 472b93: je 0x472ba3 */
	m->eax = M32((DWORD)(m->esi + 0x214930cu));	/* 472b95: mov eax, dword ptr [esi + 0x214930c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472b9b: test eax, eax */
	if (!m->zf) goto L_472d93;	/* 472b9d: jne 0x472d93 */
L_472ba3:
	m->eax = M32((DWORD)(m->esi + 0x13c9b24u));	/* 472ba3: mov eax, dword ptr [esi + 0x13c9b24] */
	M32((DWORD)(m->esp + 0x4cu)) = 0x0u;	/* 472ba9: mov dword ptr [esp + 0x4c], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472bb1: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_472d93;	/* 472bb3: jle 0x472d93 */
	m->ebp = (DWORD)(m->esi + 0x131aea4u);	/* 472bb9: lea ebp, [esi + 0x131aea4] */
L_472bbf:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xffffffa4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472bbf: cmp dword ptr [ebp - 0x5c], 1 */
	if (!m->zf) goto L_472d76;	/* 472bc3: jne 0x472d76 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0xffffffacu)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472bc9: test byte ptr [ebp - 0x54], 1 */
	if (m->zf) goto L_472d76;	/* 472bcd: je 0x472d76 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a94u)));	/* 472bd3: fld dword ptr [esi + 0x20f3a94] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 472bd9: fmul dword ptr [ebp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a84u)));	/* 472bdc: fld dword ptr [esi + 0x20f3a84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0xfffffffcu));	/* 472be2: fmul dword ptr [ebp - 4] */
	m->ecx = (DWORD)(m->ebp + 0xfffffff8u);	/* 472be5: lea ecx, [ebp - 8] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472be8: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0x0u)));	/* 472bea: fld dword ptr [ecx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3a74u));	/* 472bec: fmul dword ptr [esi + 0x20f3a74] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472bf2: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3aa4u));	/* 472bf4: fadd dword ptr [esi + 0x20f3aa4] */
	MF((DWORD)(m->ebp + 0x24cu)) = (float)ST(0); FPOP();	/* 472bfa: fstp dword ptr [ebp + 0x24c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a98u)));	/* 472c00: fld dword ptr [esi + 0x20f3a98] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 472c06: fmul dword ptr [ebp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a78u)));	/* 472c09: fld dword ptr [esi + 0x20f3a78] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 472c0f: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472c11: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a88u)));	/* 472c13: fld dword ptr [esi + 0x20f3a88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0xfffffffcu));	/* 472c19: fmul dword ptr [ebp - 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472c1c: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3aa8u));	/* 472c1e: fadd dword ptr [esi + 0x20f3aa8] */
	MF((DWORD)(m->ebp + 0x250u)) = (float)ST(0); FPOP();	/* 472c24: fstp dword ptr [ebp + 0x250] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a9cu)));	/* 472c2a: fld dword ptr [esi + 0x20f3a9c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 472c30: fmul dword ptr [ebp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a7cu)));	/* 472c33: fld dword ptr [esi + 0x20f3a7c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 472c39: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472c3b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a8cu)));	/* 472c3d: fld dword ptr [esi + 0x20f3a8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0xfffffffcu));	/* 472c43: fmul dword ptr [ebp - 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472c46: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3aacu));	/* 472c48: fadd dword ptr [esi + 0x20f3aac] */
	MF((DWORD)(m->ebp + 0x254u)) = (float)ST(0); FPOP();	/* 472c4e: fstp dword ptr [ebp + 0x254] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3aa0u)));	/* 472c54: fld dword ptr [esi + 0x20f3aa0] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 472c5a: fmul dword ptr [ebp] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a80u)));	/* 472c5d: fld dword ptr [esi + 0x20f3a80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 472c63: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472c65: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x20f3a90u)));	/* 472c67: fld dword ptr [esi + 0x20f3a90] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0xfffffffcu));	/* 472c6d: fmul dword ptr [ebp - 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472c70: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x20f3ab0u));	/* 472c72: fadd dword ptr [esi + 0x20f3ab0] */
	MF((DWORD)(m->ebp + 0x258u)) = (float)ST(0); FPOP();	/* 472c78: fstp dword ptr [ebp + 0x258] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x258u)));	/* 472c7e: fld dword ptr [ebp + 0x258] */
	ST(0) = -ST(0);	/* 472c84: fchs  */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 472c86: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x24cu)));	/* 472c8a: fld dword ptr [ebp + 0x24c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x48u)); FPOP();	/* 472c90: fcomp dword ptr [esp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472c94: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472c96: test ah, 0x41 */
	if (!m->zf) goto L_472d49;	/* 472c99: jne 0x472d49 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x250u)));	/* 472c9f: fld dword ptr [ebp + 0x250] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x48u)); FPOP();	/* 472ca5: fcomp dword ptr [esp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472ca9: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472cab: test ah, 0x41 */
	if (!m->zf) goto L_472d49;	/* 472cae: jne 0x472d49 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x254u)));	/* 472cb4: fld dword ptr [ebp + 0x254] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x48u)); FPOP();	/* 472cba: fcomp dword ptr [esp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472cbe: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472cc0: test ah, 0x41 */
	if (!m->zf) goto L_472d49;	/* 472cc3: jne 0x472d49 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x24cu)));	/* 472cc9: fld dword ptr [ebp + 0x24c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x258u)); FPOP();	/* 472ccf: fcomp dword ptr [ebp + 0x258] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472cd5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472cd7: test ah, 1 */
	if (m->zf) goto L_472d49;	/* 472cda: je 0x472d49 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x250u)));	/* 472cdc: fld dword ptr [ebp + 0x250] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x258u)); FPOP();	/* 472ce2: fcomp dword ptr [ebp + 0x258] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472ce8: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472cea: test ah, 1 */
	if (m->zf) goto L_472d49;	/* 472ced: je 0x472d49 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x254u)));	/* 472cef: fld dword ptr [ebp + 0x254] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->ebp + 0x258u)); FPOP();	/* 472cf5: fcomp dword ptr [ebp + 0x258] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472cfb: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472cfd: test ah, 1 */
	if (m->zf) goto L_472d49;	/* 472d00: je 0x472d49 */
	m->edx = (DWORD)(m->esp + 0x28u);	/* 472d02: lea edx, [esp + 0x28] */
	m->eax = (DWORD)(m->esi + 0x20f3970u);	/* 472d06: lea eax, [esi + 0x20f3970] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 472d0c: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472d0d: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 472d0e: push eax */
	m->ecx = m->esi;	/* 472d0f: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x472d16u; native_call(m, 0x471740u);	/* 472d11: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472d16: test eax, eax */
	if (!m->zf) goto L_472d49;	/* 472d18: jne 0x472d49 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 472d1a: fld dword ptr [esp + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 472d1e: fmul dword ptr [0x4a947c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x248u));	/* 472d24: fadd dword ptr [ebp + 0x248] */
	MF((DWORD)(m->ebp + 0x248u)) = (float)ST(0);	/* 472d2a: fst dword ptr [ebp + 0x248] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 472d30: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472d36: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472d38: test ah, 0x41 */
	if (!m->zf) goto L_472d76;	/* 472d3b: jne 0x472d76 */
	M32((DWORD)(m->ebp + 0x248u)) = 0x3f800000u;	/* 472d3d: mov dword ptr [ebp + 0x248], 0x3f800000 */
	goto L_472d76;	/* 472d47: jmp 0x472d76 */
L_472d49:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 472d49: fld dword ptr [esp + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a947cu));	/* 472d4d: fmul dword ptr [0x4a947c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(m->ebp + 0x248u));	/* 472d53: fsubr dword ptr [ebp + 0x248] */
	MF((DWORD)(m->ebp + 0x248u)) = (float)ST(0);	/* 472d59: fst dword ptr [ebp + 0x248] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 472d5f: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472d65: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472d67: test ah, 1 */
	if (m->zf) goto L_472d76;	/* 472d6a: je 0x472d76 */
	M32((DWORD)(m->ebp + 0x248u)) = 0x0u;	/* 472d6c: mov dword ptr [ebp + 0x248], 0 */
L_472d76:
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 472d76: mov eax, dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esi + 0x13c9b24u));	/* 472d7a: mov ecx, dword ptr [esi + 0x13c9b24] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 472d80: inc eax */
	{ DWORD a_ = m->ebp, b_ = 0x2ccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 472d81: add ebp, 0x2cc */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472d87: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 472d89: mov dword ptr [esp + 0x4c], eax */
	if (m->sf != m->of) goto L_472bbf;	/* 472d8d: jl 0x472bbf */
L_472d93:
	m->ecx = M32((DWORD)(m->esi + 0x202e8c8u));	/* 472d93: mov ecx, dword ptr [esi + 0x202e8c8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 472d99: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472d9b: test ecx, ecx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 472d9d: mov dword ptr [esp + 0x4c], eax */
	if (m->zf || m->sf != m->of) goto L_4732d8;	/* 472da1: jle 0x4732d8 */
	m->ebp = (DWORD)(m->esi + 0x1cd9500u);	/* 472da7: lea ebp, [esi + 0x1cd9500] */
L_472dad:
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xfffffff4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472dad: cmp dword ptr [ebp - 0xc], 1 */
	if (!m->zf) goto L_4732bb;	/* 472db1: jne 0x4732bb */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x20u)));	/* 472db7: fld dword ptr [ebx + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 472dba: fmul dword ptr [ebp + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x10u)));	/* 472dbd: fld dword ptr [ebx + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 472dc0: fmul dword ptr [ebp] */
	m->ecx = (DWORD)(m->ebp + 0xfffffffcu);	/* 472dc3: lea ecx, [ebp - 4] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472dc6: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x0u)));	/* 472dc8: fld dword ptr [ebx] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 472dca: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472dcc: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x30u));	/* 472dce: fadd dword ptr [ebx + 0x30] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0); FPOP();	/* 472dd1: fstp dword ptr [esp + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x24u)));	/* 472dd5: fld dword ptr [ebx + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 472dd8: fmul dword ptr [ebp + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x14u)));	/* 472ddb: fld dword ptr [ebx + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 472dde: fmul dword ptr [ebp] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472de1: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x4u)));	/* 472de3: fld dword ptr [ebx + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 472de6: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472de8: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x34u));	/* 472dea: fadd dword ptr [ebx + 0x34] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 472ded: fstp dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x28u)));	/* 472df1: fld dword ptr [ebx + 0x28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x4u));	/* 472df4: fmul dword ptr [ebp + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x18u)));	/* 472df7: fld dword ptr [ebx + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ebp + 0x0u));	/* 472dfa: fmul dword ptr [ebp] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472dfd: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x8u)));	/* 472dff: fld dword ptr [ebx + 8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->ecx + 0x0u));	/* 472e02: fmul dword ptr [ecx] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e04: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x38u));	/* 472e06: fadd dword ptr [ebx + 0x38] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 472e09: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 472e0d: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x10u));	/* 472e11: fmul dword ptr [edi + 0x10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 472e14: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x20u));	/* 472e18: fmul dword ptr [edi + 0x20] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e1b: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 472e1d: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 472e21: fmul dword ptr [edi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e23: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 472e25: fadd dword ptr [edi + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 472e28: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 472e2c: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 472e30: fmul dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 472e33: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x14u));	/* 472e37: fmul dword ptr [edi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e3a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 472e3c: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x24u));	/* 472e40: fmul dword ptr [edi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e43: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x34u));	/* 472e45: fadd dword ptr [edi + 0x34] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 472e48: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 472e4c: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x8u));	/* 472e50: fmul dword ptr [edi + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 472e53: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x18u));	/* 472e57: fmul dword ptr [edi + 0x18] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e5a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 472e5c: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x28u));	/* 472e60: fmul dword ptr [edi + 0x28] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e63: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x38u));	/* 472e65: fadd dword ptr [edi + 0x38] */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 472e68: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 472e6c: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 472e70: fmul dword ptr [edi + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 472e73: fld dword ptr [esp + 0x14] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x1cu));	/* 472e77: fmul dword ptr [edi + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e7a: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 472e7c: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 472e80: fmul dword ptr [edi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472e83: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x3cu));	/* 472e85: fadd dword ptr [edi + 0x3c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 472e88: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 472e8c: fld dword ptr [esp + 0x38] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 472e90: fdiv dword ptr [esp + 0x40] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 472e94: fsubr dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esi + 0x20f3a28u));	/* 472e9a: fimul dword ptr [esi + 0x20f3a28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 472ea0: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 472ea6: fld dword ptr [esp + 0x34] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 472eaa: fdiv dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 472eae: fadd dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esi + 0x20f3a24u));	/* 472eb4: fimul dword ptr [esi + 0x20f3a24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 472eba: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->ebp + 0x8664u)) = (float)ST(0); FPOP();	/* 472ec0: fstp dword ptr [ebp + 0x8664] */
	MF((DWORD)(m->ebp + 0x8668u)) = (float)ST(0); FPOP();	/* 472ec6: fstp dword ptr [ebp + 0x8668] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 472ecc: fld dword ptr [esp + 0x18] */
	MF((DWORD)(m->ebp + 0x866cu)) = (float)ST(0); FPOP();	/* 472ed0: fstp dword ptr [ebp + 0x866c] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + 0x202e8d8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472ed6: cmp eax, dword ptr [esi + 0x202e8d8] */
	if (m->zf) goto L_4732ad;	/* 472edc: je 0x4732ad */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x40u)));	/* 472ee2: fld dword ptr [esp + 0x40] */
	ST(0) = -ST(0);	/* 472ee6: fchs  */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 472ee8: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 472eec: fld dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x48u)); FPOP();	/* 472ef0: fcomp dword ptr [esp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472ef4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472ef6: test ah, 0x41 */
	if (!m->zf) goto L_4732ad;	/* 472ef9: jne 0x4732ad */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 472eff: fld dword ptr [esp + 0x38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x48u)); FPOP();	/* 472f03: fcomp dword ptr [esp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472f07: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472f09: test ah, 0x41 */
	if (!m->zf) goto L_4732ad;	/* 472f0c: jne 0x4732ad */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 472f12: fld dword ptr [esp + 0x3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x48u)); FPOP();	/* 472f16: fcomp dword ptr [esp + 0x48] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472f1a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472f1c: test ah, 0x41 */
	if (!m->zf) goto L_4732ad;	/* 472f1f: jne 0x4732ad */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 472f25: fld dword ptr [esp + 0x34] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x40u)); FPOP();	/* 472f29: fcomp dword ptr [esp + 0x40] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472f2d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472f2f: test ah, 1 */
	if (m->zf) goto L_4732ad;	/* 472f32: je 0x4732ad */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 472f38: fld dword ptr [esp + 0x38] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x40u)); FPOP();	/* 472f3c: fcomp dword ptr [esp + 0x40] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472f40: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472f42: test ah, 1 */
	if (m->zf) goto L_4732ad;	/* 472f45: je 0x4732ad */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x3cu)));	/* 472f4b: fld dword ptr [esp + 0x3c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x40u)); FPOP();	/* 472f4f: fcomp dword ptr [esp + 0x40] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 472f53: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 472f55: test ah, 1 */
	if (m->zf) goto L_4732ad;	/* 472f58: je 0x4732ad */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 472f5e: lea eax, [esp + 0x1c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 472f62: push eax */
	m->eax = (DWORD)(m->esi + 0x20f3970u);	/* 472f63: lea eax, [esi + 0x20f3970] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472f69: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 472f6a: push eax */
	m->ecx = m->esi;	/* 472f6b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x472f72u; native_call(m, 0x471740u);	/* 472f6d: call 0x471740 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472f72: test eax, eax */
	if (!m->zf) goto L_4732ad;	/* 472f74: jne 0x4732ad */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 472f7a: fld dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x290u));	/* 472f7e: fsub dword ptr [ebp + 0x290] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 472f84: fstp dword ptr [esp + 0x1c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 472f88: fld dword ptr [esp + 0x14] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x290u));	/* 472f8c: fadd dword ptr [ebp + 0x290] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 472f92: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 472f96: fld dword ptr [esp + 0x18] */
	MF((DWORD)(m->esp + 0x24u)) = (float)ST(0);	/* 472f9a: fst dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x20u));	/* 472f9e: fmul dword ptr [edi + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 472fa1: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x10u));	/* 472fa5: fmul dword ptr [edi + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472fa8: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 472faa: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 472fae: fmul dword ptr [edi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472fb0: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 472fb2: fadd dword ptr [edi + 0x30] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 472fb5: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 472fb9: fmul dword ptr [edi + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472fbc: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x24u));	/* 472fc0: fmul dword ptr [edi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472fc3: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 472fc5: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x14u));	/* 472fc9: fmul dword ptr [edi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472fcc: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x34u));	/* 472fce: fadd dword ptr [edi + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 472fd1: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 472fd5: fmul dword ptr [edi + 0xc] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 472fd8: fld dword ptr [esp + 0x24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 472fdc: fmul dword ptr [edi + 0x2c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472fdf: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 472fe1: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x1cu));	/* 472fe5: fmul dword ptr [edi + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 472fe8: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x3cu));	/* 472fea: fadd dword ptr [edi + 0x3c] */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 472fed: fstp dword ptr [esp + 0x40] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 472ff1: fdiv dword ptr [esp + 0x40] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 472ff5: fsubr dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esi + 0x20f3a28u));	/* 472ffb: fimul dword ptr [esi + 0x20f3a28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 473001: fmul dword ptr [0x4a942c] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 473007: fxch st(1) */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x40u));	/* 473009: fdiv dword ptr [esp + 0x40] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47300d: fadd dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esi + 0x20f3a24u));	/* 473013: fimul dword ptr [esi + 0x20f3a24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 473019: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->ebp + 0x8670u)) = (float)ST(0); FPOP();	/* 47301f: fstp dword ptr [ebp + 0x8670] */
	MF((DWORD)(m->ebp + 0x8674u)) = (float)ST(0); FPOP();	/* 473025: fstp dword ptr [ebp + 0x8674] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47302b: fld dword ptr [esp + 0x18] */
	MF((DWORD)(m->ebp + 0x8678u)) = (float)ST(0); FPOP();	/* 47302f: fstp dword ptr [ebp + 0x8678] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 473035: fld dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x290u));	/* 473039: fadd dword ptr [ebp + 0x290] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 47303f: fld dword ptr [esp + 0x14] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x290u));	/* 473043: fsub dword ptr [ebp + 0x290] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 473049: fld dword ptr [esp + 0x18] */
	{ long double t = ST(0); FPUSH(t); }	/* 47304d: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x20u));	/* 47304f: fmul dword ptr [edi + 0x20] */
	{ long double t = ST(2); FPUSH(t); }	/* 473052: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x10u));	/* 473054: fmul dword ptr [edi + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 473057: faddp st(1) */
	{ long double t = ST(3); FPUSH(t); }	/* 473059: fld st(3) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x0u));	/* 47305b: fmul dword ptr [edi] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47305d: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x30u));	/* 47305f: fadd dword ptr [edi + 0x30] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 473062: fstp dword ptr [esp + 0x34] */
	{ long double t = ST(2); FPUSH(t); }	/* 473066: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x4u));	/* 473068: fmul dword ptr [edi + 4] */
	{ long double t = ST(1); FPUSH(t); }	/* 47306b: fld st(1) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x24u));	/* 47306d: fmul dword ptr [edi + 0x24] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 473070: faddp st(1) */
	{ long double t = ST(2); FPUSH(t); }	/* 473072: fld st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x14u));	/* 473074: fmul dword ptr [edi + 0x14] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 473077: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x34u));	/* 473079: fadd dword ptr [edi + 0x34] */
	m->ecx = M32((DWORD)(m->esp + 0x4cu));	/* 47307c: mov ecx, dword ptr [esp + 0x4c] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 473080: fstp dword ptr [esp + 0x38] */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 473084: fxch st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0xcu));	/* 473086: fmul dword ptr [edi + 0xc] */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 473089: fxch st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x2cu));	/* 47308b: fmul dword ptr [edi + 0x2c] */
	ST(2) = ST(2) + ST(0); FPOP();	/* 47308e: faddp st(2) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->edi + 0x1cu));	/* 473090: fmul dword ptr [edi + 0x1c] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 473093: faddp st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x3cu));	/* 473095: fadd dword ptr [edi + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x38u)));	/* 473098: fld dword ptr [esp + 0x38] */
	ST(0) = ST(0) / ST(1);	/* 47309c: fdiv st(1) */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47309e: fsubr dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esi + 0x20f3a28u));	/* 4730a4: fimul dword ptr [esi + 0x20f3a28] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4730aa: fmul dword ptr [0x4a942c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x34u)));	/* 4730b0: fld dword ptr [esp + 0x34] */
	ST(0) = ST(0) / ST(2);	/* 4730b4: fdiv st(2) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 4730b6: fadd dword ptr [0x4a9424] */
	ST(0) = ST(0) * (long double)(int)M32((DWORD)(m->esi + 0x20f3a24u));	/* 4730bc: fimul dword ptr [esi + 0x20f3a24] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 4730c2: fmul dword ptr [0x4a942c] */
	MF((DWORD)(m->ebp + 0x867cu)) = (float)ST(0); FPOP();	/* 4730c8: fstp dword ptr [ebp + 0x867c] */
	MF((DWORD)(m->ebp + 0x8680u)) = (float)ST(0); FPOP();	/* 4730ce: fstp dword ptr [ebp + 0x8680] */
	ST(0) = ST(0); FPOP();	/* 4730d4: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 4730d6: fld dword ptr [esp + 0x18] */
	MF((DWORD)(m->ebp + 0x8684u)) = (float)ST(0); FPOP();	/* 4730da: fstp dword ptr [ebp + 0x8684] */
	{ DWORD a_ = m->ecx, b_ = M32((DWORD)(m->esi + 0x202e8d8u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4730e0: cmp ecx, dword ptr [esi + 0x202e8d8] */
	if (m->zf) goto L_473128;	/* 4730e6: je 0x473128 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x867cu)));	/* 4730e8: fld dword ptr [ebp + 0x867c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x8670u));	/* 4730ee: fsub dword ptr [ebp + 0x8670] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 4730f4: fstp dword ptr [esp + 0x50] */
	m->esp -= 4; M32(m->esp) = 0x4730fdu; native_call(m, 0x4685b0u);	/* 4730f8: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 4730fd: mov dword ptr [esp + 0x48], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x48u)));	/* 473101: fild dword ptr [esp + 0x48] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 473105: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a940cu));	/* 47310b: fmul dword ptr [0x4a940c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x50u)); FPOP();	/* 473111: fcomp dword ptr [esp + 0x50] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 473115: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 473117: test ah, 0x41 */
	if (!m->zf) goto L_473128;	/* 47311a: jne 0x473128 */
	M32((DWORD)(m->ebp + 0x32cu)) = 0x1u;	/* 47311c: mov dword ptr [ebp + 0x32c], 1 */
	goto L_473132;	/* 473126: jmp 0x473132 */
L_473128:
	M32((DWORD)(m->ebp + 0x32cu)) = 0x0u;	/* 473128: mov dword ptr [ebp + 0x32c], 0 */
L_473132:
	m->eax = M32((DWORD)(m->ebp + 0x298u));	/* 473132: mov eax, dword ptr [ebp + 0x298] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 473138: test ah, 2 */
	if (m->zf) goto L_473167;	/* 47313b: je 0x473167 */
	m->eax = M32((DWORD)(m->esi + 0x202e8d4u));	/* 47313d: mov eax, dword ptr [esi + 0x202e8d4] */
	m->edx = m->eax;	/* 473143: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 473145: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 473148: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47314a: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 47314d: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 47314f: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 473152: add edx, eax */
	m->eax = M32((DWORD)(m->ebp + 0xfffffeb0u));	/* 473154: mov eax, dword ptr [ebp - 0x150] */
	{ DWORD a_ = m->eax, b_ = M32((DWORD)(m->esi + m->edx*8 + 0x1cd93b0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 47315a: cmp eax, dword ptr [esi + edx*8 + 0x1cd93b0] */
	if (m->sf == m->of) goto L_473297;	/* 473161: jge 0x473297 */
L_473167:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x14u)));	/* 473167: fld dword ptr [esp + 0x14] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47316b: fld dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 47316f: fld dword ptr [esp + 0x18] */
	ST(0) = -ST(0);	/* 473173: fchs  */
	{ long double t = ST(1); FPUSH(t); }	/* 473175: fld st(1) */
	ST(0) = ST(0) * ST(2);	/* 473177: fmul st(2) */
	{ long double t = ST(3); FPUSH(t); }	/* 473179: fld st(3) */
	ST(0) = ST(0) * ST(4);	/* 47317b: fmul st(4) */
	ST(1) = ST(1) + ST(0); FPOP();	/* 47317d: faddp st(1) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 47317f: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 473183: fmul dword ptr [esp + 0x10] */
	ST(1) = ST(1) + ST(0); FPOP();	/* 473187: faddp st(1) */
	{ long double t = ST(0); __asm__("fsqrt" : "+t"(t)); ST(0) = t; }	/* 473189: fsqrt  */
	ST(3) = ST(0); FPOP();	/* 47318b: fstp st(3) */
	{ long double t = ST(0); ST(0) = ST(2); ST(2) = t; }	/* 47318d: fxch st(2) */
	ST(2) = ST(2) / ST(0); FPOP();	/* 47318f: fdivp st(2) */
	ST(0) = ST(0); FPOP();	/* 473191: fstp st(0) */
	MF((DWORD)(m->ebp + 0x868cu)) = (float)ST(0);	/* 473193: fst dword ptr [ebp + 0x868c] */
	m->eax = M32((DWORD)(m->esi + 0x202e8d4u));	/* 473199: mov eax, dword ptr [esi + 0x202e8d4] */
	m->ecx = m->eax;	/* 47319f: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4731a1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4731a4: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4731a6: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4731a9: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4731ab: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4731ae: add ecx, eax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*8 + 0x1cd93acu)));	/* 4731b0: fld dword ptr [esi + ecx*8 + 0x1cd93ac] */
	m->eax = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 4731b7: lea eax, [esi + ecx*8] */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 4731ba: mov dword ptr [esp + 0x48], eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 4731be: call 0x49ec14 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4731c3: cdq  */
	m->ecx = 0xe10u;	/* 4731c4: mov ecx, 0xe10 */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4731c9: idiv ecx */
	m->eax = m->edx;	/* 4731cb: mov eax, edx */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4731cd: add eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4731cf: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4731d0: idiv ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edx*4 + 0xa17f38u)));	/* 4731d2: fld dword ptr [edx*4 + 0xa17f38] */
	{ long double t = ST(0); ST(0) = ST(1); ST(1) = t; }	/* 4731d9: fxch st(1) */
	FCOM(ST(0), ST(1)); FPOP(); FPOP();	/* 4731db: fcompp  */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4731dd: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4731df: test ah, 0x41 */
	if (!m->zf) goto L_473297;	/* 4731e2: jne 0x473297 */
	m->eax = M32((DWORD)(m->esi + 0x202e8d4u));	/* 4731e8: mov eax, dword ptr [esi + 0x202e8d4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4731ee: test eax, eax */
	if (m->sf != m->of) goto L_473243;	/* 4731f0: jl 0x473243 */
	m->eax = M32((DWORD)(m->esp + 0x48u));	/* 4731f2: mov eax, dword ptr [esp + 0x48] */
	m->edx = M32((DWORD)(m->ebp + 0xffffffc0u));	/* 4731f6: mov edx, dword ptr [ebp - 0x40] */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->eax + 0x1cd94c0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4731f9: cmp edx, dword ptr [eax + 0x1cd94c0] */
	if (m->zf) goto L_473243;	/* 4731ff: je 0x473243 */
	m->ecx = M32((DWORD)(m->eax + 0x1cd94f0u));	/* 473201: mov ecx, dword ptr [eax + 0x1cd94f0] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 473207: test ecx, ecx */
	if (m->sf != m->of) goto L_473243;	/* 473209: jl 0x473243 */
	m->eax = m->ecx;	/* 47320b: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 47320d: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473210: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 473212: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 473215: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 473217: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 47321a: lea eax, [eax + eax*4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->eax*8 + 0x14d48c4u)));	/* 47321d: fld dword ptr [esi + eax*8 + 0x14d48c4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 473224: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47322a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47322c: test ah, 0x41 */
	if (!m->zf) goto L_473243;	/* 47322f: jne 0x473243 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x68u)));	/* 473231: fld dword ptr [esp + 0x68] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebp + 0x8690u));	/* 473235: fadd dword ptr [ebp + 0x8690] */
	MF((DWORD)(m->ebp + 0x8690u)) = (float)ST(0); FPOP();	/* 47323b: fstp dword ptr [ebp + 0x8690] */
	goto L_47324d;	/* 473241: jmp 0x47324d */
L_473243:
	M32((DWORD)(m->ebp + 0x8690u)) = 0x0u;	/* 473243: mov dword ptr [ebp + 0x8690], 0 */
L_47324d:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x867cu)));	/* 47324d: fld dword ptr [ebp + 0x867c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebp + 0x8670u));	/* 473253: fsub dword ptr [ebp + 0x8670] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 473259: fstp dword ptr [esp + 0x50] */
	m->esp -= 4; M32(m->esp) = 0x473262u; native_call(m, 0x4685b0u);	/* 47325d: call 0x4685b0 */
	M32((DWORD)(m->esp + 0x48u)) = m->eax;	/* 473262: mov dword ptr [esp + 0x48], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x48u)));	/* 473266: fild dword ptr [esp + 0x48] */
	ST(0) = x87_divrm(ST(0), (const float *)(DWORD)(0x4a9510u));	/* 47326a: fdivr dword ptr [0x4a9510] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9414u));	/* 473270: fmul dword ptr [0x4a9414] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x50u)); FPOP();	/* 473276: fcomp dword ptr [esp + 0x50] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 47327a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 47327c: test ah, 0x41 */
	if (m->zf) goto L_4732a1;	/* 47327f: je 0x4732a1 */
	M32((DWORD)(m->ebp + 0x8698u)) = 0x40400000u;	/* 473281: mov dword ptr [ebp + 0x8698], 0x40400000 */
	M32((DWORD)(m->ebp + 0x8688u)) = 0x1u;	/* 47328b: mov dword ptr [ebp + 0x8688], 1 */
	goto L_4732bb;	/* 473295: jmp 0x4732bb */
L_473297:
	M32((DWORD)(m->ebp + 0x8690u)) = 0x0u;	/* 473297: mov dword ptr [ebp + 0x8690], 0 */
L_4732a1:
	M32((DWORD)(m->ebp + 0x8688u)) = 0x1u;	/* 4732a1: mov dword ptr [ebp + 0x8688], 1 */
	goto L_4732bb;	/* 4732ab: jmp 0x4732bb */
L_4732ad:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4732ad: xor eax, eax */
	M32((DWORD)(m->ebp + 0x8690u)) = m->eax;	/* 4732af: mov dword ptr [ebp + 0x8690], eax */
	M32((DWORD)(m->ebp + 0x8688u)) = m->eax;	/* 4732b5: mov dword ptr [ebp + 0x8688], eax */
L_4732bb:
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 4732bb: mov eax, dword ptr [esp + 0x4c] */
	m->ecx = M32((DWORD)(m->esi + 0x202e8c8u));	/* 4732bf: mov ecx, dword ptr [esi + 0x202e8c8] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4732c5: inc eax */
	{ DWORD a_ = m->ebp, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4732c6: add ebp, 0x8888 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4732cc: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x4cu)) = m->eax;	/* 4732ce: mov dword ptr [esp + 0x4c], eax */
	if (m->sf != m->of) goto L_472dad;	/* 4732d2: jl 0x472dad */
L_4732d8:
	m->edi = M32(m->esp); m->esp += 4;	/* 4732d8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4732d9: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4732da: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4732db: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4732dc: add esp, 0x34 */
	m->esp += 4 + 36; return;	/* 4732df: ret 0x24 */
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
