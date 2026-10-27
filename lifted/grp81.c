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

static void lift_43d060(X86 *m);

/* room_43d060 (0x43d060), lifted by tools/lift.py */
static void lift_43d060(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43d060: push ebp */
	m->ebp = m->esp;	/* 43d061: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 43d063: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d066: sub esp, 0x38 */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 43d069: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 43d06e: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d074: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43d075: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43d076: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43d077: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d078: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d079: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d07fu; native_call(m, 0x4323c0u);	/* 43d07a: call 0x4323c0 */
	m->ebp = m->eax;	/* 43d07f: mov ebp, eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d081: push 2 */
	M32((DWORD)(m->esp + 0x28u)) = m->ebp;	/* 43d083: mov dword ptr [esp + 0x28], ebp */
	m->esp -= 4; M32(m->esp) = 0x43d08cu; native_call(m, 0x41ef90u);	/* 43d087: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d08c: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x43d095u; native_call(m, M32(0x4a9218u));	/* 43d08f: call dword ptr [0x4a9218] */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 43d095: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d09b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0a0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0a5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0aa: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43d0b1u; native_call(m, m->ebx);	/* 43d0af: call ebx */
	m->edx = M32((DWORD)(0x4deb50u));	/* 43d0b1: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9dcee4u));	/* 43d0b7: mov eax, dword ptr [0x9dcee4] */
	m->ecx = M32((DWORD)(0x9dcee0u));	/* 43d0bc: mov ecx, dword ptr [0x9dcee0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0c2: push edx */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d0c3: mov edx, dword ptr [0x9dcedc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0c9: push eax */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43d0ca: mov eax, dword ptr [0x9dced8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0cf: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0d0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0d1: push eax */
	m->esp -= 4; M32(m->esp) = 0x43d0d7u; native_call(m, 0x427a90u);	/* 43d0d2: call 0x427a90 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43d0d7: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43d0dd: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43d0e3: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0e8: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43d0e9: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0ef: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0f0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0f1: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d0f2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d0fcu; native_call(m, 0x41f0e0u);	/* 43d0f7: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d0fc: mov edx, dword ptr [0x9dcedc] */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43d102: mov eax, dword ptr [0x9dced8] */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d107: add edx, 0x10 */
	{ DWORD v_ = 0x75aba4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d10a: push 0x75aba4 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d10f: add eax, 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d112: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d113: push eax */
	m->esp -= 4; M32(m->esp) = 0x43d119u; native_call(m, 0x4028b0u);	/* 43d114: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x34u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d119: add esp, 0x34 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d11c: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43d127u; native_call(m, M32(0x4a9224u));	/* 43d121: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43d127: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 43d12c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d12e: and ecx, 0x800001ff */
	if (!m->sf) goto L_43d13e;	/* 43d134: jns 0x43d13e */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d136: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d137: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43d13d: inc ecx */
L_43d13e:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43d13e: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43d13f: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d145: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d146: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43d148: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43d14e: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43d151: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43d15au; native_call(m, 0x4566c0u);	/* 43d155: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d15a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d15f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d164: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d169: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43d170u; native_call(m, m->ebx);	/* 43d16e: call ebx */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43d170: test ebp, ebp */
	if (!m->zf) goto L_43d337;	/* 43d172: jne 0x43d337 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d178: mov eax, dword ptr [0x9dcedc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d17d: push 1 */
	m->ecx = (DWORD)(m->eax + 0x3eu);	/* 43d17f: lea ecx, [eax + 0x3e] */
	{ DWORD a_ = m->eax, b_ = 0x26u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d182: add eax, 0x26 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d185: push ecx */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d186: mov ecx, dword ptr [0x9dced8] */
	m->edx = (DWORD)(m->ecx + 0xe4u);	/* 43d18c: lea edx, [ecx + 0xe4] */
	{ DWORD a_ = m->ecx, b_ = 0xb0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d192: add ecx, 0xb0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d198: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d199: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d19a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d1a0u; native_call(m, 0x4284d0u);	/* 43d19b: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d1a0: add esp, 0x14 */
L_43d1a3:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1a3: push 0 */
L_43d1a5:
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d1a5: mov eax, dword ptr [0x9dcedc] */
	m->ecx = (DWORD)(m->eax + 0x3eu);	/* 43d1aa: lea ecx, [eax + 0x3e] */
	{ DWORD a_ = m->eax, b_ = 0x26u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d1ad: add eax, 0x26 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1b0: push ecx */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d1b1: mov ecx, dword ptr [0x9dced8] */
	m->edx = (DWORD)(m->ecx + 0x17au);	/* 43d1b7: lea edx, [ecx + 0x17a] */
	{ DWORD a_ = m->ecx, b_ = 0x146u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d1bd: add ecx, 0x146 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1c3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1c4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1c5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d1cbu; native_call(m, 0x4285c0u);	/* 43d1c6: call 0x4285c0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d1cb: add esp, 0x14 */
	{ DWORD v_ = 0x3f333333u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1ce: push 0x3f333333 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1d3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1d8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1dd: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43d1e4u; native_call(m, m->ebx);	/* 43d1e2: call ebx */
	m->eax = M32((DWORD)(0x9dd6acu));	/* 43d1e4: mov eax, dword ptr [0x9dd6ac] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1e9: push 0xa */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 43d1eb: lea ecx, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x5u);	/* 43d1ee: lea edx, [eax + eax*4 + 5] */
	m->eax = (DWORD)(m->esp + 0x24u);	/* 43d1f2: lea eax, [esp + 0x24] */
	m->ecx = (DWORD)(m->ecx + m->ecx*1 + 0x1u);	/* 43d1f6: lea ecx, [ecx + ecx + 1] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1fa: push eax */
	{ DWORD a_ = m->edx, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43d1fb: shl edx, 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d1fd: push ecx */
	M32((DWORD)(0x9dd83cu)) = m->ecx;	/* 43d1fe: mov dword ptr [0x9dd83c], ecx */
	M32((DWORD)(0x9dd7dcu)) = m->edx;	/* 43d204: mov dword ptr [0x9dd7dc], edx */
	m->esp -= 4; M32(m->esp) = 0x43d20fu; native_call(m, 0x49fb53u);	/* 43d20a: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9dd7dcu));	/* 43d20f: mov edx, dword ptr [0x9dd7dc] */
	m->ecx = (DWORD)(m->esp + 0x40u);	/* 43d215: lea ecx, [esp + 0x40] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43d219: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d21b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d21c: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d222u; native_call(m, 0x49fb53u);	/* 43d21d: call 0x49fb53 */
	m->edi = 0x4b278cu;	/* 43d222: mov edi, 0x4b278c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d227: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43d22a: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x38u);	/* 43d22c: lea edx, [esp + 0x38] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d230: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43d232: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43d234: sub edi, ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d236: push 1 */
	m->esi = m->edi;	/* 43d238: mov esi, edi */
	m->edi = m->edx;	/* 43d23a: mov edi, edx */
	m->edx = m->ecx;	/* 43d23c: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d23e: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d241: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 43d243: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43d245: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43d246: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43d249: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43d24b: mov ecx, edx */
	m->edx = (DWORD)(m->esp + 0x3cu);	/* 43d24d: lea edx, [esp + 0x3c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d251: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43d254: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = (DWORD)(m->esp + 0x50u);	/* 43d256: lea edi, [esp + 0x50] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d25a: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d25d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43d25f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43d261: sub edi, ecx */
	m->esi = m->edi;	/* 43d263: mov esi, edi */
	m->edi = m->edx;	/* 43d265: mov edi, edx */
	m->edx = m->ecx;	/* 43d267: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d269: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d26c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 43d26e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 43d270: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43d271: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43d274: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d276: mov eax, dword ptr [0x9dcedc] */
	m->ecx = m->edx;	/* 43d27b: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d27d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43d280: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->eax + 0x40u);	/* 43d282: lea ecx, [eax + 0x40] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d285: add eax, 0x24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d288: push ecx */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d289: mov ecx, dword ptr [0x9dced8] */
	m->edx = (DWORD)(m->ecx + 0x146u);	/* 43d28f: lea edx, [ecx + 0x146] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d295: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d296: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d297: add ecx, 0xe6 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d29d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d2a3u; native_call(m, 0x4282f0u);	/* 43d29e: call 0x4282f0 */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d2a3: mov edx, dword ptr [0x9dcedc] */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 43d2a9: lea eax, [esp + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2ad: push eax */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43d2ae: mov eax, dword ptr [0x9dced8] */
	{ DWORD a_ = m->edx, b_ = 0x2au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d2b3: add edx, 0x2a */
	m->ecx = (DWORD)(m->eax + 0x146u);	/* 43d2b6: lea ecx, [eax + 0x146] */
	{ DWORD a_ = m->eax, b_ = 0xe6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d2bc: add eax, 0xe6 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2c1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2c2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2c3: push eax */
	m->esp -= 4; M32(m->esp) = 0x43d2c9u; native_call(m, 0x402740u);	/* 43d2c4: call 0x402740 */
	m->eax = M32((DWORD)(0x9dcee0u));	/* 43d2c9: mov eax, dword ptr [0x9dcee0] */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d2ce: mov edx, dword ptr [0x9dcedc] */
	{ DWORD v_ = 0x75ac24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2d4: push 0x75ac24 */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d2d9: add edx, 0x10 */
	m->ecx = (DWORD)(m->eax + 0xffffffecu);	/* 43d2dc: lea ecx, [eax - 0x14] */
	{ DWORD a_ = m->eax, b_ = 0xffffff88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d2df: add eax, -0x78 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2e2: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2e3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2e4: push eax */
	m->esp -= 4; M32(m->esp) = 0x43d2eau; native_call(m, 0x4029d0u);	/* 43d2e5: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d2ea: add esp, 0x4c */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d2ed: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43d2f8u; native_call(m, M32(0x4a9224u));	/* 43d2f2: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43d2f8: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 43d2fd: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d2ff: and ecx, 0x800001ff */
	if (!m->sf) goto L_43d30f;	/* 43d305: jns 0x43d30f */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d307: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d308: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43d30e: inc ecx */
L_43d30f:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43d30f: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43d310: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d316: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d317: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43d319: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43d31f: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43d322: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43d32bu; native_call(m, 0x4566c0u);	/* 43d326: call 0x4566c0 */
	{ DWORD a_ = m->ebp, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43d32b: cmp ebp, 2 */
	if (!m->zf) goto L_43d371;	/* 43d32e: jne 0x43d371 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d330: push 0x3f800000 */
	goto L_43d376;	/* 43d335: jmp 0x43d376 */
L_43d337:
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d337: mov eax, dword ptr [0x9dcedc] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d33c: push 0 */
	m->ecx = (DWORD)(m->eax + 0x3eu);	/* 43d33e: lea ecx, [eax + 0x3e] */
	{ DWORD a_ = m->eax, b_ = 0x26u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d341: add eax, 0x26 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d344: push ecx */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d345: mov ecx, dword ptr [0x9dced8] */
	m->edx = (DWORD)(m->ecx + 0xe4u);	/* 43d34b: lea edx, [ecx + 0xe4] */
	{ DWORD a_ = m->ecx, b_ = 0xb0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d351: add ecx, 0xb0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d357: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d358: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d359: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d35fu; native_call(m, 0x4284d0u);	/* 43d35a: call 0x4284d0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d35f: add esp, 0x14 */
	{ DWORD a_ = m->ebp, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43d362: cmp ebp, 1 */
	if (!m->zf) goto L_43d1a3;	/* 43d365: jne 0x43d1a3 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43d36b: push ebp */
	goto L_43d1a5;	/* 43d36c: jmp 0x43d1a5 */
L_43d371:
	{ DWORD v_ = 0x3f19999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43d371: push 0x3f19999a */
L_43d376:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d376: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d37b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d380: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43d387u; native_call(m, m->ebx);	/* 43d385: call ebx */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d387: mov eax, dword ptr [0x9dcedc] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d38c: push 1 */
	m->ecx = (DWORD)(m->eax + 0x40u);	/* 43d38e: lea ecx, [eax + 0x40] */
	{ DWORD a_ = m->eax, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d391: add eax, 0x24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d394: push ecx */
	m->ecx = M32((DWORD)(0x9dcee0u));	/* 43d395: mov ecx, dword ptr [0x9dcee0] */
	m->edx = (DWORD)(m->ecx + 0xffffffecu);	/* 43d39b: lea edx, [ecx - 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffff88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d39e: add ecx, -0x78 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3a1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3a2: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3a3: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d3a9u; native_call(m, 0x4282f0u);	/* 43d3a4: call 0x4282f0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d3a9: add esp, 0x14 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3ac: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3b1: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3b3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3b8: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3bd: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d3c7u; native_call(m, 0x41f0e0u);	/* 43d3c2: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43d3c7: mov eax, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d3cc: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43d3cf: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_43d414;	/* 43d3d2: ja 0x43d414 */
	switch (m->eax) { case 0: goto L_43d3db; case 1: goto L_43d3e9; case 2: goto L_43d3f0; case 3: goto L_43d3e2; default: abort(); }	/* 43d3d4: jmp dword ptr [eax*4 + 0x43dee8] */
L_43d3db:
	{ DWORD v_ = 0x75ae24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3db: push 0x75ae24 */
	goto L_43d3f5;	/* 43d3e0: jmp 0x43d3f5 */
L_43d3e2:
	{ DWORD v_ = 0x75aea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3e2: push 0x75aea4 */
	goto L_43d3f5;	/* 43d3e7: jmp 0x43d3f5 */
L_43d3e9:
	{ DWORD v_ = 0x75af24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3e9: push 0x75af24 */
	goto L_43d3f5;	/* 43d3ee: jmp 0x43d3f5 */
L_43d3f0:
	{ DWORD v_ = 0x75b024u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d3f0: push 0x75b024 */
L_43d3f5:
	m->eax = M32((DWORD)(0x9dcee0u));	/* 43d3f5: mov eax, dword ptr [0x9dcee0] */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d3fa: mov edx, dword ptr [0x9dcedc] */
	{ DWORD a_ = m->edx, b_ = 0x2au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d400: add edx, 0x2a */
	m->ecx = (DWORD)(m->eax + 0xffffffecu);	/* 43d403: lea ecx, [eax - 0x14] */
	{ DWORD a_ = m->eax, b_ = 0xffffff88u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d406: add eax, -0x78 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d409: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d40a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d40b: push eax */
	m->esp -= 4; M32(m->esp) = 0x43d411u; native_call(m, 0x402740u);	/* 43d40c: call 0x402740 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d411: add esp, 0x10 */
L_43d414:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d414: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d419: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d41e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d423: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d425: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43d42fu; native_call(m, 0x41f0e0u);	/* 43d42a: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d42f: mov eax, dword ptr [0x9dcedc] */
	m->ecx = M32((DWORD)(0x9dcee0u));	/* 43d434: mov ecx, dword ptr [0x9dcee0] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43d43a: mov edx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->eax, b_ = 0x4au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d440: add eax, 0x4a */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d443: add ecx, -0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d446: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d447: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d448: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d44b: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d44c: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d452u; native_call(m, 0x427a40u);	/* 43d44d: call 0x427a40 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d452: mov eax, dword ptr [0x9dcedc] */
	m->ecx = M32((DWORD)(0x9dcee0u));	/* 43d457: mov ecx, dword ptr [0x9dcee0] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43d45d: mov edx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->eax, b_ = 0x6eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d463: add eax, 0x6e */
	{ DWORD a_ = m->ecx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d466: add ecx, -0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d469: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d46a: push ecx */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d46b: add edx, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d46e: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d46f: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d475u; native_call(m, 0x427a40u);	/* 43d470: call 0x427a40 */
	m->eax = M32((DWORD)(0x9dceccu));	/* 43d475: mov eax, dword ptr [0x9dcecc] */
	m->ecx = M32((DWORD)(0x9dcec8u));	/* 43d47a: mov ecx, dword ptr [0x9dcec8] */
	m->edx = M32((DWORD)(0x9dcec4u));	/* 43d480: mov edx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d486: push eax */
	m->eax = M32((DWORD)(0x9dcec0u));	/* 43d487: mov eax, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d48c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d48d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d48e: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d48f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d499u; native_call(m, 0x41f0e0u);	/* 43d494: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dcedcu));	/* 43d499: mov ecx, dword ptr [0x9dcedc] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43d49f: mov edx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d4a5: add esp, 0x48 */
	{ DWORD a_ = m->ecx, b_ = 0x52u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d4a8: add ecx, 0x52 */
	{ DWORD a_ = m->edx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d4ab: add edx, 0x18 */
	{ DWORD v_ = 0x75aca4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d4ae: push 0x75aca4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d4b3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d4b4: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d4bau; native_call(m, 0x402620u);	/* 43d4b5: call 0x402620 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d4ba: mov eax, dword ptr [0x9dcedc] */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d4bf: mov ecx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->eax, b_ = 0x52u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d4c5: add eax, 0x52 */
	{ DWORD v_ = 0x75ad24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d4c8: push 0x75ad24 */
	{ DWORD a_ = m->ecx, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d4cd: add ecx, 0x48 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d4d0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d4d1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d4d7u; native_call(m, 0x402620u);	/* 43d4d2: call 0x402620 */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d4d7: mov edx, dword ptr [0x9dcedc] */
	m->edi = 0x75ada4u;	/* 43d4dd: mov edi, 0x75ada4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d4e2: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43d4e5: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = 0x52u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d4e7: add edx, 0x52 */
	{ DWORD v_ = 0x75ada4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d4ea: push 0x75ada4 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d4ef: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43d4f1: mov eax, dword ptr [0x9dced8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d4f6: push edx */
	m->ecx = ~m->ecx;	/* 43d4f7: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d4f9: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43d4fa: shl ecx, 3 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d4fd: sub eax, ecx */
	{ DWORD a_ = m->eax, b_ = 0xecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d4ff: add eax, 0xec */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d504: push eax */
	m->esp -= 4; M32(m->esp) = 0x43d50au; native_call(m, 0x402620u);	/* 43d505: call 0x402620 */
	m->edi = 0x75ae24u;	/* 43d50a: mov edi, 0x75ae24 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d50f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43d512: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d514: add esp, 0x24 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d517: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43d519: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d51b: dec ecx */
	m->esi = 0x12cu;	/* 43d51c: mov esi, 0x12c */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43d521: shl ecx, 3 */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43d524: sub esi, ecx */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43d526: mov eax, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43d52b: test eax, eax */
	if (!m->zf) goto L_43d542;	/* 43d52d: jne 0x43d542 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d52f: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d534: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d536: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d53b: push 0x3f800000 */
	goto L_43d55d;	/* 43d540: jmp 0x43d55d */
L_43d542:
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43d542: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43d548: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43d54e: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d553: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43d554: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d55a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d55b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d55c: push ecx */
L_43d55d:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d55d: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d567u; native_call(m, 0x41f0e0u);	/* 43d562: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d567: mov edx, dword ptr [0x9dcedc] */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43d56d: mov eax, dword ptr [0x9dced8] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d572: add esp, 0x14 */
	{ DWORD a_ = m->edx, b_ = 0x52u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d575: add edx, 0x52 */
	m->ecx = (DWORD)(m->eax + m->esi*1 + 0x18u);	/* 43d578: lea ecx, [eax + esi + 0x18] */
	{ DWORD v_ = 0x75ae24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d57c: push 0x75ae24 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d581: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d582: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d588u; native_call(m, 0x402620u);	/* 43d583: call 0x402620 */
	m->edi = 0x75aea4u;	/* 43d588: mov edi, 0x75aea4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d58d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43d590: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d592: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d595: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43d597: mov eax, dword ptr [0x9dd1d0] */
	m->esi = 0x2du;	/* 43d59c: mov esi, 0x2d */
	m->ecx = ~m->ecx;	/* 43d5a1: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d5a3: dec ecx */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43d5a4: sub esi, ecx */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 43d5a6: shl esi, 3 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43d5a9: cmp eax, 3 */
	if (!m->zf) goto L_43d5c1;	/* 43d5ac: jne 0x43d5c1 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5ae: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5b3: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5b5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5ba: push 0x3f800000 */
	goto L_43d5dc;	/* 43d5bf: jmp 0x43d5dc */
L_43d5c1:
	m->edx = M32((DWORD)(0x9dceccu));	/* 43d5c1: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 43d5c7: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 43d5cc: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5d2: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 43d5d3: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5d9: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5da: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5db: push edx */
L_43d5dc:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5dc: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d5e6u; native_call(m, 0x41f0e0u);	/* 43d5e1: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d5e6: mov eax, dword ptr [0x9dcedc] */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d5eb: mov ecx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d5f1: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = 0x52u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d5f4: add eax, 0x52 */
	m->edx = (DWORD)(m->ecx + m->esi*1 + 0x18u);	/* 43d5f7: lea edx, [ecx + esi + 0x18] */
	{ DWORD v_ = 0x75aea4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d5fb: push 0x75aea4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d600: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d601: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d607u; native_call(m, 0x402620u);	/* 43d602: call 0x402620 */
	m->edi = 0x75af24u;	/* 43d607: mov edi, 0x75af24 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d60c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43d60f: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d611: add esp, 0xc */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d614: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43d616: mov eax, dword ptr [0x9dd1d0] */
	m->esi = 0x35u;	/* 43d61b: mov esi, 0x35 */
	m->ecx = ~m->ecx;	/* 43d620: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d622: dec ecx */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43d623: sub esi, ecx */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 43d625: shl esi, 3 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43d628: cmp eax, 1 */
	if (!m->zf) goto L_43d640;	/* 43d62b: jne 0x43d640 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d62d: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d632: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d634: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d639: push 0x3f800000 */
	goto L_43d65a;	/* 43d63e: jmp 0x43d65a */
L_43d640:
	m->eax = M32((DWORD)(0x9dceccu));	/* 43d640: mov eax, dword ptr [0x9dcecc] */
	m->ecx = M32((DWORD)(0x9dcec8u));	/* 43d645: mov ecx, dword ptr [0x9dcec8] */
	m->edx = M32((DWORD)(0x9dcec4u));	/* 43d64b: mov edx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d651: push eax */
	m->eax = M32((DWORD)(0x9dcec0u));	/* 43d652: mov eax, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d657: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d658: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d659: push eax */
L_43d65a:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d65a: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d664u; native_call(m, 0x41f0e0u);	/* 43d65f: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dcedcu));	/* 43d664: mov ecx, dword ptr [0x9dcedc] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43d66a: mov edx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d670: add esp, 0x14 */
	{ DWORD a_ = m->ecx, b_ = 0x52u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d673: add ecx, 0x52 */
	m->eax = (DWORD)(m->edx + m->esi*1 + 0x18u);	/* 43d676: lea eax, [edx + esi + 0x18] */
	{ DWORD v_ = 0x75af24u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d67a: push 0x75af24 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d67f: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d680: push eax */
	m->esp -= 4; M32(m->esp) = 0x43d686u; native_call(m, 0x402620u);	/* 43d681: call 0x402620 */
	m->edi = 0x75afa4u;	/* 43d686: mov edi, 0x75afa4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d68b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43d68e: xor eax, eax */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43d690: mov edx, dword ptr [0x9dcec8] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d696: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43d698: mov eax, dword ptr [0x9dcec4] */
	m->esi = 0x3cu;	/* 43d69d: mov esi, 0x3c */
	m->ecx = ~m->ecx;	/* 43d6a2: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d6a4: dec ecx */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43d6a5: sub esi, ecx */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43d6a7: mov ecx, dword ptr [0x9dcecc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d6ad: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43d6ae: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d6b4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d6b5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d6b6: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d6b7: push 0x76d438 */
	{ DWORD a_ = m->esi, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 43d6bc: shl esi, 3 */
	m->esp -= 4; M32(m->esp) = 0x43d6c4u; native_call(m, 0x41f0e0u);	/* 43d6bf: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d6c4: mov edx, dword ptr [0x9dcedc] */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43d6ca: mov eax, dword ptr [0x9dced8] */
	{ DWORD a_ = m->edx, b_ = 0x52u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d6cf: add edx, 0x52 */
	{ DWORD v_ = 0x75afa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d6d2: push 0x75afa4 */
	m->ecx = (DWORD)(m->eax + m->esi*1 + 0x18u);	/* 43d6d7: lea ecx, [eax + esi + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d6db: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d6dc: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d6e2u; native_call(m, 0x402620u);	/* 43d6dd: call 0x402620 */
	m->edi = 0x75b024u;	/* 43d6e2: mov edi, 0x75b024 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d6e7: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43d6ea: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d6ec: add esp, 0x2c */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d6ef: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43d6f1: mov eax, dword ptr [0x9dd1d0] */
	m->esi = 0x226u;	/* 43d6f6: mov esi, 0x226 */
	m->ecx = ~m->ecx;	/* 43d6fb: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d6fd: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43d6fe: shl ecx, 3 */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43d701: sub esi, ecx */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43d703: cmp eax, 2 */
	if (!m->zf) goto L_43d71b;	/* 43d706: jne 0x43d71b */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d708: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d70d: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d70f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d714: push 0x3f800000 */
	goto L_43d736;	/* 43d719: jmp 0x43d736 */
L_43d71b:
	m->edx = M32((DWORD)(0x9dceccu));	/* 43d71b: mov edx, dword ptr [0x9dcecc] */
	m->eax = M32((DWORD)(0x9dcec8u));	/* 43d721: mov eax, dword ptr [0x9dcec8] */
	m->ecx = M32((DWORD)(0x9dcec4u));	/* 43d726: mov ecx, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d72c: push edx */
	m->edx = M32((DWORD)(0x9dcec0u));	/* 43d72d: mov edx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d733: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d734: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d735: push edx */
L_43d736:
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d736: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d740u; native_call(m, 0x41f0e0u);	/* 43d73b: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d740: mov eax, dword ptr [0x9dcedc] */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d745: mov ecx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d74b: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = 0x52u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d74e: add eax, 0x52 */
	m->edx = (DWORD)(m->ecx + m->esi*1 + 0x18u);	/* 43d751: lea edx, [ecx + esi + 0x18] */
	{ DWORD v_ = 0x75b024u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d755: push 0x75b024 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d75a: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d75b: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d761u; native_call(m, 0x402620u);	/* 43d75c: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d761: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d766: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d76b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d770: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d775: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d77fu; native_call(m, 0x41f0e0u);	/* 43d77a: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd3b0u));	/* 43d77f: mov eax, dword ptr [0x9dd3b0] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d784: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43d787: test eax, eax */
	if (m->zf) goto L_43dc97;	/* 43d789: je 0x43dc97 */
	m->ebp = M32((DWORD)(0x4a920cu));	/* 43d78f: mov ebp, dword ptr [0x4a920c] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43d795: xor esi, esi */
	m->ebx = 0x9dcef4u;	/* 43d797: mov ebx, 0x9dcef4 */
L_43d79c:
	m->edi = m->ebx;	/* 43d79c: mov edi, ebx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d79e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43d7a1: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43d7a3: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43d7a5: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d7a7: dec ecx */
	if (m->zf) goto L_43dc87;	/* 43d7a8: je 0x43dc87 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7ae: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7b3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7b8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7bd: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7c2: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d7ccu; native_call(m, 0x41f0e0u);	/* 43d7c7: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->ebx + 0xfffffffcu));	/* 43d7cc: mov ecx, dword ptr [ebx - 4] */
	m->eax = (DWORD)(m->esp + 0x34u);	/* 43d7cf: lea eax, [esp + 0x34] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7d3: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7d5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7d6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d7dcu; native_call(m, 0x49fb53u);	/* 43d7d7: call 0x49fb53 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d7dc: mov eax, dword ptr [0x9dcedc] */
	m->edx = (DWORD)(m->esp + 0x40u);	/* 43d7e1: lea edx, [esp + 0x40] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7e5: push edx */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43d7e6: mov edx, dword ptr [0x9dced8] */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x78u);	/* 43d7ec: lea ecx, [esi + eax + 0x78] */
	{ DWORD a_ = m->edx, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d7f0: add edx, 0x18 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7f3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d7f4: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d7fau; native_call(m, 0x402620u);	/* 43d7f5: call 0x402620 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d7fa: mov eax, dword ptr [0x9dcedc] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43d7ff: mov edx, dword ptr [0x9dced8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d805: push ebx */
	{ DWORD a_ = m->edx, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d806: add edx, 0x48 */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x78u);	/* 43d809: lea ecx, [esi + eax + 0x78] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d80d: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d80e: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d814u; native_call(m, 0x402620u);	/* 43d80f: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x38u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d814: add esp, 0x38 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d817: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43d822u; native_call(m, M32(0x4a9224u));	/* 43d81c: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x76d448u));	/* 43d822: mov eax, dword ptr [0x76d448] */
	m->ecx = m->eax;	/* 43d827: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d829: and ecx, 0x800001ff */
	if (!m->sf) goto L_43d839;	/* 43d82f: jns 0x43d839 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d831: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43d832: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43d838: inc ecx */
L_43d839:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43d839: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43d83a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d840: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43d841: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43d843: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43d849: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43d84c: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43d855u; native_call(m, 0x4566c0u);	/* 43d850: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->ebx + 0x32u));	/* 43d855: mov ecx, dword ptr [ebx + 0x32] */
	m->edi = 0xau;	/* 43d858: mov edi, 0xa */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43d85d: dec ecx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d85e: push 7 */
	m->eax = m->ecx;	/* 43d860: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43d862: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->edi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 43d863: idiv edi */
	m->eax = 0x66666667u;	/* 43d865: mov eax, 0x66666667 */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 43d86a: mov dword ptr [esp + 0x18], edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 43d86e: imul ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 43d870: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9590u));	/* 43d874: fmul dword ptr [0x4a9590] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 43d87a: fstp dword ptr [esp + 0x14] */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 43d87e: sar edx, 2 */
	m->eax = m->edx;	/* 43d881: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43d883: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d886: add edx, eax */
	M32((DWORD)(m->esp + 0x18u)) = m->edx;	/* 43d888: mov dword ptr [esp + 0x18], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x18u)));	/* 43d88c: fild dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 43d890: fmul dword ptr [0x4a958c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9588u));	/* 43d896: fadd dword ptr [0x4a9588] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 43d89c: fstp dword ptr [esp + 0x18] */
	m->esp -= 4; M32(m->esp) = 0x43d8a6u; native_call(m, M32(0x4a921cu));	/* 43d8a0: call dword ptr [0x4a921c] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 43d8a6: mov edi, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 43d8aa: mov ecx, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43d8ae: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d8af: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d8b2u; native_call(m, m->ebp);	/* 43d8b0: call ebp */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d8b2: mov edx, dword ptr [0x9dcedc] */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d8b8: mov ecx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->ecx, b_ = 0xd2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d8be: add ecx, 0xd2 */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x78u);	/* 43d8c4: lea eax, [esi + edx + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d8c8: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d8c9: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d8cfu; native_call(m, 0x41ef60u);	/* 43d8ca: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 43d8cf: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9590u));	/* 43d8d3: fadd dword ptr [0x4a9590] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d8d9: add esp, 8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43d8dc: push edi */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 43d8dd: fstp dword ptr [esp + 0x1c] */
	m->edi = M32((DWORD)(m->esp + 0x1cu));	/* 43d8e1: mov edi, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43d8e5: push edi */
	m->esp -= 4; M32(m->esp) = 0x43d8e8u; native_call(m, m->ebp);	/* 43d8e6: call ebp */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d8e8: mov edx, dword ptr [0x9dcedc] */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d8ee: mov ecx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->ecx, b_ = 0xeau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d8f4: add ecx, 0xea */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x78u);	/* 43d8fa: lea eax, [esi + edx + 0x78] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d8fe: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d8ff: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d905u; native_call(m, 0x41ef60u);	/* 43d900: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 43d905: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a958cu));	/* 43d909: fadd dword ptr [0x4a958c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d90f: add esp, 8 */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 43d912: fstp dword ptr [esp + 0x14] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 43d916: mov edx, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d91a: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43d91b: push edi */
	m->esp -= 4; M32(m->esp) = 0x43d91eu; native_call(m, m->ebp);	/* 43d91c: call ebp */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d91e: mov eax, dword ptr [0x9dcedc] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43d923: mov edx, dword ptr [0x9dced8] */
	{ DWORD a_ = m->edx, b_ = 0xeau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43d929: add edx, 0xea */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x88u);	/* 43d92f: lea ecx, [esi + eax + 0x88] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d936: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d937: push edx */
	m->esp -= 4; M32(m->esp) = 0x43d93du; native_call(m, 0x41ef60u);	/* 43d938: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 43d93d: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 43d941: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d945: add esp, 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d948: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d949: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d94cu; native_call(m, m->ebp);	/* 43d94a: call ebp */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43d94c: mov edx, dword ptr [0x9dcedc] */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x88u);	/* 43d952: lea eax, [esi + edx + 0x88] */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d959: mov ecx, dword ptr [0x9dced8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d95f: push eax */
	{ DWORD a_ = m->ecx, b_ = 0xd2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d960: add ecx, 0xd2 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d966: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d96cu; native_call(m, 0x41ef60u);	/* 43d967: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d96c: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x43d975u; native_call(m, M32(0x4a9220u));	/* 43d96f: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d975: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43d980u; native_call(m, M32(0x4a922cu));	/* 43d97a: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0x3e99999au; m->esp -= 4; M32(m->esp) = v_; }	/* 43d980: push 0x3e99999a */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d985: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d987: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d98c: push 0x3f800000 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d991: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43d99bu; native_call(m, 0x41f0e0u);	/* 43d996: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43d99b: mov eax, dword ptr [0x9dcedc] */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43d9a0: mov ecx, dword ptr [0x9dced8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9a6: push 0 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x88u);	/* 43d9a8: lea edx, [esi + eax + 0x88] */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x79u);	/* 43d9af: lea eax, [esi + eax + 0x79] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9b3: push edx */
	m->edx = (DWORD)(m->ecx + 0xeau);	/* 43d9b4: lea edx, [ecx + 0xea] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9ba: push edx */
	{ DWORD a_ = m->ecx, b_ = 0xd3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43d9bb: add ecx, 0xd3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9c1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9c2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43d9c8u; native_call(m, 0x427970u);	/* 43d9c3: call 0x427970 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9c8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9cd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9d2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9d7: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9dc: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43d9e6u; native_call(m, 0x41f0e0u);	/* 43d9e1: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43d9e6: mov eax, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->esp, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43d9eb: add esp, 0x3c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43d9ee: test eax, eax */
	if (!m->zf) goto L_43da10;	/* 43d9f0: jne 0x43da10 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9f2: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9f7: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9f9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43d9fe: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da03: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43da0du; native_call(m, 0x41f0e0u);	/* 43da08: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43da0d: add esp, 0x14 */
L_43da10:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x36u)));	/* 43da10: fld dword ptr [ebx + 0x36] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43da13: sub esp, 8 */
	m->ecx = (DWORD)(m->esp + 0x28u);	/* 43da16: lea ecx, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 43da1a: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b2784u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da1d: push 0x4b2784 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43da22: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43da28u; native_call(m, 0x49e9ddu);	/* 43da23: call 0x49e9dd */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43da28: mov eax, dword ptr [0x9dcedc] */
	m->edx = (DWORD)(m->esp + 0x30u);	/* 43da2d: lea edx, [esp + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43da31: push edx */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 43da32: lea edi, [esp + 0x34] */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x78u);	/* 43da36: lea ecx, [esi + eax + 0x78] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43da3a: xor eax, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43da3c: push ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43da3d: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43da40: repne scasb al, byte ptr es:[edi] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43da42: mov edx, dword ptr [0x9dced8] */
	m->ecx = ~m->ecx;	/* 43da48: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43da4a: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43da4b: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43da4e: sub edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x144u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43da50: add edx, 0x144 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43da56: push edx */
	m->esp -= 4; M32(m->esp) = 0x43da5cu; native_call(m, 0x402620u);	/* 43da57: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da5c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da61: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da66: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da6b: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da70: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43da7au; native_call(m, 0x41f0e0u);	/* 43da75: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43da7a: mov eax, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43da7f: add esp, 0x30 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43da82: cmp eax, 3 */
	if (!m->zf) goto L_43daa5;	/* 43da85: jne 0x43daa5 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da87: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da8c: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da8e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da93: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43da98: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43daa2u; native_call(m, 0x41f0e0u);	/* 43da9d: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43daa2: add esp, 0x14 */
L_43daa5:
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebx + 0x2eu)));	/* 43daa5: fld dword ptr [ebx + 0x2e] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43daa8: sub esp, 8 */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 43daab: lea eax, [esp + 0x28] */
	MDBL((DWORD)(m->esp + 0x0u)) = (double)ST(0); FPOP();	/* 43daaf: fstp qword ptr [esp] */
	{ DWORD v_ = 0x4b277cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43dab2: push 0x4b277c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dab7: push eax */
	m->esp -= 4; M32(m->esp) = 0x43dabdu; native_call(m, 0x49e9ddu);	/* 43dab8: call 0x49e9dd */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43dabd: mov edx, dword ptr [0x9dcedc] */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 43dac3: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dac7: push ecx */
	m->edi = (DWORD)(m->esp + 0x34u);	/* 43dac8: lea edi, [esp + 0x34] */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x78u);	/* 43dacc: lea eax, [esi + edx + 0x78] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43dad0: or ecx, 0xffffffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dad3: push eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43dad4: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43dad6: repne scasb al, byte ptr es:[edi] */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43dad8: mov eax, dword ptr [0x9dced8] */
	m->edx = 0x30u;	/* 43dadd: mov edx, 0x30 */
	m->ecx = ~m->ecx;	/* 43dae2: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43dae4: dec ecx */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43dae5: sub edx, ecx */
	m->ecx = (DWORD)(m->eax + m->edx*8 + 0x0u);	/* 43dae7: lea ecx, [eax + edx*8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43daea: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43daf0u; native_call(m, 0x402620u);	/* 43daeb: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43daf0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43daf5: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dafa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43daff: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db04: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43db0eu; native_call(m, 0x41f0e0u);	/* 43db09: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43db0e: mov eax, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43db13: add esp, 0x30 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43db16: cmp eax, 1 */
	if (!m->zf) goto L_43db39;	/* 43db19: jne 0x43db39 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db1b: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db20: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db22: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db27: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db2c: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43db36u; native_call(m, 0x41f0e0u);	/* 43db31: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43db36: add esp, 0x14 */
L_43db39:
	m->eax = M32((DWORD)(m->ebx + 0x26u));	/* 43db39: mov eax, dword ptr [ebx + 0x26] */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 43db3c: lea edx, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43db40: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43db42: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43db43: push eax */
	m->esp -= 4; M32(m->esp) = 0x43db49u; native_call(m, 0x49fb53u);	/* 43db44: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9dcedcu));	/* 43db49: mov edx, dword ptr [0x9dcedc] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 43db4f: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43db53: push ecx */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 43db54: lea edi, [esp + 0x30] */
	m->eax = (DWORD)(m->esi + m->edx*1 + 0x78u);	/* 43db58: lea eax, [esi + edx + 0x78] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43db5c: or ecx, 0xffffffff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43db5f: push eax */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43db60: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43db62: repne scasb al, byte ptr es:[edi] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43db64: mov edx, dword ptr [0x9dced8] */
	m->ecx = ~m->ecx;	/* 43db6a: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43db6c: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43db6d: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43db70: sub edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x1bcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43db72: add edx, 0x1bc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43db78: push edx */
	m->esp -= 4; M32(m->esp) = 0x43db7eu; native_call(m, 0x402620u);	/* 43db79: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db7e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db83: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db88: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db8d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43db92: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43db9cu; native_call(m, 0x41f0e0u);	/* 43db97: call 0x41f0e0 */
	m->ecx = M32((DWORD)(m->ebx + 0x2au));	/* 43db9c: mov ecx, dword ptr [ebx + 0x2a] */
	m->eax = (DWORD)(m->esp + 0x4cu);	/* 43db9f: lea eax, [esp + 0x4c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43dba3: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dba5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dba6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43dbacu; native_call(m, 0x49fb53u);	/* 43dba7: call 0x49fb53 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43dbac: mov eax, dword ptr [0x9dcedc] */
	m->edx = (DWORD)(m->esp + 0x58u);	/* 43dbb1: lea edx, [esp + 0x58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dbb5: push edx */
	m->edi = (DWORD)(m->esp + 0x5cu);	/* 43dbb6: lea edi, [esp + 0x5c] */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x78u);	/* 43dbba: lea ecx, [esi + eax + 0x78] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43dbbe: xor eax, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dbc0: push ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43dbc1: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43dbc4: repne scasb al, byte ptr es:[edi] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43dbc6: mov edx, dword ptr [0x9dced8] */
	m->ecx = ~m->ecx;	/* 43dbcc: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43dbce: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43dbcf: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43dbd2: sub edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x1f4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43dbd4: add edx, 0x1f4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dbda: push edx */
	m->esp -= 4; M32(m->esp) = 0x43dbe0u; native_call(m, 0x402620u);	/* 43dbdb: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43dbe0: add esp, 0x44 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dbe3: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dbe8: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dbed: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dbf2: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dbf7: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43dc01u; native_call(m, 0x41f0e0u);	/* 43dbfc: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dd1d0u));	/* 43dc01: mov eax, dword ptr [0x9dd1d0] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43dc06: add esp, 0x14 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43dc09: cmp eax, 2 */
	if (!m->zf) goto L_43dc2c;	/* 43dc0c: jne 0x43dc2c */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc0e: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc13: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc15: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc1a: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc1f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43dc29u; native_call(m, 0x41f0e0u);	/* 43dc24: call 0x41f0e0 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43dc29: add esp, 0x14 */
L_43dc2c:
	m->ecx = M32((DWORD)(m->ebx + 0x1eu));	/* 43dc2c: mov ecx, dword ptr [ebx + 0x1e] */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 43dc2f: lea eax, [esp + 0x20] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc33: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc35: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc36: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43dc3cu; native_call(m, 0x49fb53u);	/* 43dc37: call 0x49fb53 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43dc3c: mov eax, dword ptr [0x9dcedc] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 43dc41: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc45: push edx */
	m->edi = (DWORD)(m->esp + 0x30u);	/* 43dc46: lea edi, [esp + 0x30] */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x78u);	/* 43dc4a: lea ecx, [esi + eax + 0x78] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43dc4e: xor eax, eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc50: push ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43dc51: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43dc54: repne scasb al, byte ptr es:[edi] */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43dc56: mov edx, dword ptr [0x9dced8] */
	m->ecx = ~m->ecx;	/* 43dc5c: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43dc5e: dec ecx */
	{ DWORD a_ = m->ecx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43dc5f: shl ecx, 3 */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43dc62: sub edx, ecx */
	{ DWORD a_ = m->edx, b_ = 0x23eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43dc64: add edx, 0x23e */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc6a: push edx */
	m->esp -= 4; M32(m->esp) = 0x43dc70u; native_call(m, 0x402620u);	/* 43dc6b: call 0x402620 */
	{ DWORD a_ = m->ebx, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 43dc70: add ebx, 0x44 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43dc73: add esp, 0x18 */
	{ DWORD a_ = m->esi, b_ = 0x16u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43dc76: add esi, 0x16 */
	{ DWORD a_ = m->ebx, b_ = 0x9dd19cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43dc79: cmp ebx, 0x9dd19c */
	if (m->sf != m->of) goto L_43d79c;	/* 43dc7f: jl 0x43d79c */
	goto L_43dc91;	/* 43dc85: jmp 0x43dc91 */
L_43dc87:
	m->eax = M32((DWORD)(0x9dd6acu));	/* 43dc87: mov eax, dword ptr [0x9dd6ac] */
	M32((DWORD)(0x9dd4b8u)) = m->eax;	/* 43dc8c: mov dword ptr [0x9dd4b8], eax */
L_43dc91:
	m->ebx = M32((DWORD)(0x4a9228u));	/* 43dc91: mov ebx, dword ptr [0x4a9228] */
L_43dc97:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc97: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dc9c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dca1: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dca6: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dca8: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x43dcb2u; native_call(m, 0x41f0e0u);	/* 43dcad: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9dcee4u));	/* 43dcb2: mov ecx, dword ptr [0x9dcee4] */
	m->edx = M32((DWORD)(0x9dcee0u));	/* 43dcb8: mov edx, dword ptr [0x9dcee0] */
	{ DWORD a_ = m->edx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43dcbe: add edx, -0x10 */
	m->eax = (DWORD)(m->ecx + 0xffffffc0u);	/* 43dcc1: lea eax, [ecx - 0x40] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dcc4: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dcc5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dcc6: push eax */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43dcc7: mov eax, dword ptr [0x9dced8] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43dccc: add eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dccf: push eax */
	m->esp -= 4; M32(m->esp) = 0x43dcd5u; native_call(m, 0x427a40u);	/* 43dcd0: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43dcd5: add esp, 0x24 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 43dcd8: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 43dcda: xor esi, esi */
	m->edi = 0x75b0a4u;	/* 43dcdc: mov edi, 0x75b0a4 */
L_43dce1:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dce1: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x43dcecu; native_call(m, M32(0x4a9224u));	/* 43dce6: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 43dcec: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 43dcf1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43dcf3: and ecx, 0x800001ff */
	if (!m->sf) goto L_43dd03;	/* 43dcf9: jns 0x43dd03 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 43dcfb: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43dcfc: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 43dd02: inc ecx */
L_43dd03:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43dd03: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 43dd04: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd0a: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43dd0b: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 43dd0d: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 43dd13: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 43dd16: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x43dd1fu; native_call(m, 0x4566c0u);	/* 43dd1a: call 0x4566c0 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 43dd1f: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = (DWORD)(m->ebp + 0x3u);	/* 43dd23: lea ecx, [ebp + 3] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43dd26: cmp eax, ecx */
	if (!m->zf) goto L_43dd91;	/* 43dd28: jne 0x43dd91 */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43dd2a: cmp eax, 3 */
	if (!m->zf) goto L_43dd38;	/* 43dd2d: jne 0x43dd38 */
	m->eax = M32((DWORD)(0x9dd6b8u));	/* 43dd2f: mov eax, dword ptr [0x9dd6b8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43dd34: test eax, eax */
	if (m->zf) goto L_43dd91;	/* 43dd36: je 0x43dd91 */
L_43dd38:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd38: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd3d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd42: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd47: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43dd4eu; native_call(m, m->ebx);	/* 43dd4c: call ebx */
	m->ecx = M32((DWORD)(0x9dcee4u));	/* 43dd4e: mov ecx, dword ptr [0x9dcee4] */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43dd54: mov eax, dword ptr [0x9dced8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd59: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 43dd5b: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43dd5e: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd61: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x11du);	/* 43dd62: lea edx, [esi + eax + 0x11d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd69: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x7du);	/* 43dd6a: lea eax, [esi + eax + 0x7d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd6e: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd6f: push eax */
	m->esp -= 4; M32(m->esp) = 0x43dd75u; native_call(m, 0x4282f0u);	/* 43dd70: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dceccu));	/* 43dd75: mov ecx, dword ptr [0x9dcecc] */
	m->edx = M32((DWORD)(0x9dcec8u));	/* 43dd7b: mov edx, dword ptr [0x9dcec8] */
	m->eax = M32((DWORD)(0x9dcec4u));	/* 43dd81: mov eax, dword ptr [0x9dcec4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd86: push ecx */
	m->ecx = M32((DWORD)(0x9dcec0u));	/* 43dd87: mov ecx, dword ptr [0x9dcec0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd8d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd8e: push eax */
	goto L_43dde8;	/* 43dd8f: jmp 0x43dde8 */
L_43dd91:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd91: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd96: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dd9b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dda0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43dda7u; native_call(m, m->ebx);	/* 43dda5: call ebx */
	m->ecx = M32((DWORD)(0x9dcee4u));	/* 43dda7: mov ecx, dword ptr [0x9dcee4] */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43ddad: mov eax, dword ptr [0x9dced8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43ddb2: push 1 */
	m->edx = (DWORD)(m->ecx + 0xfffffff0u);	/* 43ddb4: lea edx, [ecx - 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43ddb7: add ecx, -0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ddba: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x11du);	/* 43ddbb: lea edx, [esi + eax + 0x11d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ddc2: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x7du);	/* 43ddc3: lea eax, [esi + eax + 0x7d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ddc7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ddc8: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ddceu; native_call(m, 0x4282f0u);	/* 43ddc9: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9dd344u));	/* 43ddce: mov ecx, dword ptr [0x9dd344] */
	m->edx = M32((DWORD)(0x9dd340u));	/* 43ddd4: mov edx, dword ptr [0x9dd340] */
	m->eax = M32((DWORD)(0x9dd33cu));	/* 43ddda: mov eax, dword ptr [0x9dd33c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dddf: push ecx */
	m->ecx = M32((DWORD)(0x9dd338u));	/* 43dde0: mov ecx, dword ptr [0x9dd338] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dde6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43dde7: push eax */
L_43dde8:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dde8: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dde9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43ddf3u; native_call(m, 0x41f0e0u);	/* 43ddee: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dced8u));	/* 43ddf3: mov eax, dword ptr [0x9dced8] */
	m->ecx = M32((DWORD)(0x9dcee4u));	/* 43ddf8: mov ecx, dword ptr [0x9dcee4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ddfe: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffd8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43de01: add ecx, -0x28 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x11du);	/* 43de04: lea edx, [esi + eax + 0x11d] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43de0b: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43de0c: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x7du);	/* 43de0d: lea edx, [esi + eax + 0x7d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43de11: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43de12: push edx */
	m->esp -= 4; M32(m->esp) = 0x43de18u; native_call(m, 0x4029d0u);	/* 43de13: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43de18: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43de1b: add edi, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 43de21: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 43de22: add esi, 0xc8 */
	{ DWORD a_ = m->edi, b_ = 0x75b1a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43de28: cmp edi, 0x75b1a4 */
	if (m->sf != m->of) goto L_43dce1;	/* 43de2e: jl 0x43dce1 */
	m->eax = M32((DWORD)(0x9dd6b8u));	/* 43de34: mov eax, dword ptr [0x9dd6b8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43de39: test eax, eax */
	if (m->zf) goto L_43dea7;	/* 43de3b: je 0x43dea7 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4dba80u)));	/* 43de3d: fld dword ptr [0x4dba80] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9438u));	/* 43de43: fmul dword ptr [0x4a9438] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 43de49: call 0x49ec14 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 43de4e: cdq  */
	m->ecx = 0xau;	/* 43de4f: mov ecx, 0xa */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 43de54: idiv ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43de56: push ecx */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 43de57: mov dword ptr [esp + 0x20], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x20u)));	/* 43de5b: fild dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 43de5f: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 43de65: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 43de6b: fstp dword ptr [esp] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43de6e: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43de70: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43de75: push 0 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 43de77: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x43de81u; native_call(m, 0x41f0e0u);	/* 43de7c: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9dcedcu));	/* 43de81: mov eax, dword ptr [0x9dcedc] */
	m->edx = M32((DWORD)(0x9dcee0u));	/* 43de86: mov edx, dword ptr [0x9dcee0] */
	m->ecx = M32((DWORD)(0x9dced8u));	/* 43de8c: mov ecx, dword ptr [0x9dced8] */
	{ DWORD v_ = 0x75b1a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43de92: push 0x75b1a4 */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 43de97: add eax, 0xc8 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43de9c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43de9d: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43de9e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x43dea4u; native_call(m, 0x4029d0u);	/* 43de9f: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x24u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43dea4: add esp, 0x24 */
L_43dea7:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43dea7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43deac: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43deb1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 43deb6: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x43debdu; native_call(m, m->ebx);	/* 43debb: call ebx */
	m->edx = M32((DWORD)(0x9dcee4u));	/* 43debd: mov edx, dword ptr [0x9dcee4] */
	m->eax = M32((DWORD)(0x9dcee0u));	/* 43dec3: mov eax, dword ptr [0x9dcee0] */
	m->ecx = M32((DWORD)(0x9dcedcu));	/* 43dec8: mov ecx, dword ptr [0x9dcedc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43dece: push edx */
	m->edx = M32((DWORD)(0x9dced8u));	/* 43decf: mov edx, dword ptr [0x9dced8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ded5: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ded6: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ded7: push edx */
	m->esp -= 4; M32(m->esp) = 0x43deddu; native_call(m, 0x428a00u);	/* 43ded8: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43dedd: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 43dee0: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43dee1: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43dee2: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43dee3: pop ebx */
	m->esp = m->ebp;	/* 43dee4: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43dee6: pop ebp */
	m->esp += 4 + 0; return;	/* 43dee7: ret  */
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
