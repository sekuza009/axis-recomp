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

static void lift_4875d0(X86 *m);

/* map_loadItemInfoFrom (0x4875d0), lifted by tools/lift.py */
static void lift_4875d0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4875d0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4875d1: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4875d2: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4875d3: push edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 4875d4: mov edi, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 4875d8: push 0x4ad170 */
	m->ebx = m->ecx;	/* 4875dd: mov ebx, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4875df: push edi */
	m->esp -= 4; M32(m->esp) = 0x4875e5u; native_call(m, 0x49e9cau);	/* 4875e0: call 0x49e9ca */
	m->esi = m->eax;	/* 4875e5: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4875e7: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4875ea: test esi, esi */
	if (!m->zf) goto L_487601;	/* 4875ec: jne 0x487601 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4875ee: push edi */
	{ DWORD v_ = 0x4c7bd4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4875ef: push 0x4c7bd4 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4875f4: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x4875feu; native_call(m, 0x46c710u);	/* 4875f9: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4875fe: add esp, 0xc */
L_487601:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487601: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 487602: push 1 */
	m->eax = (DWORD)(m->esp + 0x1cu);	/* 487604: lea eax, [esp + 0x1c] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 487608: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48760a: push eax */
	m->esp -= 4; M32(m->esp) = 0x487610u; native_call(m, 0x49e836u);	/* 48760b: call 0x49e836 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 487610: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 487614: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = 0x1201u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 487617: cmp eax, 0x1201 */
	if (m->zf) goto L_487631;	/* 48761c: je 0x487631 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48761e: push edi */
	{ DWORD v_ = 0x4c7b94u; m->esp -= 4; M32(m->esp) = v_; }	/* 48761f: push 0x4c7b94 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 487624: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48762eu; native_call(m, 0x46c710u);	/* 487629: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48762e: add esp, 0xc */
L_487631:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487631: push esi */
	m->edi = (DWORD)(m->ebx + 0x20f3adcu);	/* 487632: lea edi, [ebx + 0x20f3adc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 487638: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48763a: push 4 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48763c: push edi */
	m->esp -= 4; M32(m->esp) = 0x487642u; native_call(m, 0x46cbe0u);	/* 48763d: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->edi + 0x0u));	/* 487642: mov ecx, dword ptr [edi] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487644: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 487645: push ecx */
	m->edx = (DWORD)(m->ebx + 0x20f3ae0u);	/* 487646: lea edx, [ebx + 0x20f3ae0] */
	{ DWORD v_ = 0x90u; m->esp -= 4; M32(m->esp) = v_; }	/* 48764c: push 0x90 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 487651: push edx */
	m->esp -= 4; M32(m->esp) = 0x487657u; native_call(m, 0x46cbe0u);	/* 487652: call 0x46cbe0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 487657: push esi */
	m->esp -= 4; M32(m->esp) = 0x48765du; native_call(m, 0x49e7e0u);	/* 487658: call 0x49e7e0 */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 48765d: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48765f: add esp, 0x24 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 487662: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 487664: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4876a0;	/* 487666: jle 0x4876a0 */
	m->esi = (DWORD)(m->ebx + 0x20f3b6cu);	/* 487668: lea esi, [ebx + 0x20f3b6c] */
L_48766e:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0xffffff74u))) & 0xff) << 0);	/* 48766e: mov cl, byte ptr [esi - 0x8c] */
	m->eax = (DWORD)(m->esi + 0xffffffc0u);	/* 487674: lea eax, [esi - 0x40] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 487677: test cl, cl */
	if (m->zf) goto L_48768d;	/* 487679: je 0x48768d */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48767b: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48767d: push eax */
	m->ecx = (DWORD)(m->ebx + 0x19e188cu);	/* 48767e: lea ecx, [ebx + 0x19e188c] */
	m->esp -= 4; M32(m->esp) = 0x487689u; native_call(m, 0x466dc0u);	/* 487684: call 0x466dc0 */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 487689: mov dword ptr [esi], eax */
	goto L_487693;	/* 48768b: jmp 0x487693 */
L_48768d:
	M32((DWORD)(m->esi + 0x0u)) = 0x0u;	/* 48768d: mov dword ptr [esi], 0 */
L_487693:
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 487693: mov eax, dword ptr [edi] */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 487695: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 487696: add esi, 0x90 */
	{ DWORD a_ = m->ebp, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48769c: cmp ebp, eax */
	if (m->sf != m->of) goto L_48766e;	/* 48769e: jl 0x48766e */
L_4876a0:
	m->edi = M32(m->esp); m->esp += 4;	/* 4876a0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4876a1: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4876a2: pop ebp */
	m->eax = 0x1u;	/* 4876a3: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4876a8: pop ebx */
	m->esp += 4 + 4; return;	/* 4876a9: ret 4 */
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
