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

static void lift_44e640(X86 *m);

/* profile_44e640 (0x44e640), lifted by tools/lift.py */
static void lift_44e640(X86 *m)
{
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44e640: push ebp */
	m->ebp = m->esp;	/* 44e641: mov ebp, esp */
	{ DWORD a_ = m->esp, b_ = 0xfffffff8u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esp = r_; }	/* 44e643: and esp, 0xfffffff8 */
	{ DWORD a_ = m->esp, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e646: sub esp, 0x30 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e649: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 44e64a: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e64b: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e64c: push edi */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e64d: push 2 */
	m->esp -= 4; M32(m->esp) = 0x44e654u; native_call(m, 0x41ef90u);	/* 44e64f: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e654: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44e65du; native_call(m, M32(0x4a9218u));	/* 44e657: call dword ptr [0x4a9218] */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 44e65d: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 44e662: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e668: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e669: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44e66fu; native_call(m, 0x44b3e0u);	/* 44e66a: call 0x44b3e0 */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 44e66f: mov ebx, dword ptr [0x4a9228] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e675: add esp, 8 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 44e678: mov dword ptr [esp + 0x28], eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e67c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e681: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e686: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e68b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e692u; native_call(m, m->ebx);	/* 44e690: call ebx */
	m->edx = M32((DWORD)(0x4deb50u));	/* 44e692: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x9f682cu));	/* 44e698: mov eax, dword ptr [0x9f682c] */
	m->ecx = M32((DWORD)(0x9f6830u));	/* 44e69d: mov ecx, dword ptr [0x9f6830] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6a3: push edx */
	m->edx = M32((DWORD)(0x9f8c50u));	/* 44e6a4: mov edx, dword ptr [0x9f8c50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6aa: push eax */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44e6ab: mov eax, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6b0: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6b1: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6b2: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e6b8u; native_call(m, 0x427a90u);	/* 44e6b3: call 0x427a90 */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44e6b8: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44e6be: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44e6c4: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6c9: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44e6ca: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6d0: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6d1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6d2: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6d3: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44e6ddu; native_call(m, 0x41f0e0u);	/* 44e6d8: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x9f8c50u));	/* 44e6dd: mov edx, dword ptr [0x9f8c50] */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44e6e3: mov eax, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44e6e8: add edx, 0x10 */
	{ DWORD v_ = 0x75e7a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6eb: push 0x75e7a4 */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e6f0: add eax, 0x20 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6f3: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6f4: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e6fau; native_call(m, 0x4028b0u);	/* 44e6f5: call 0x4028b0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6fa: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e6ff: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e704: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e709: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e70b: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44e715u; native_call(m, 0x41f0e0u);	/* 44e710: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44e715: mov ecx, dword ptr [0x9f8c50] */
	m->edx = M32((DWORD)(0x9f6830u));	/* 44e71b: mov edx, dword ptr [0x9f6830] */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e721: add esp, 0x48 */
	{ DWORD a_ = m->edx, b_ = 0xfffffff0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44e724: add edx, -0x10 */
	m->eax = (DWORD)(m->ecx + 0x28u);	/* 44e727: lea eax, [ecx + 0x28] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e72a: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e72b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e72c: push eax */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44e72d: mov eax, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e732: add eax, 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e735: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e73bu; native_call(m, 0x427a40u);	/* 44e736: call 0x427a40 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e73b: add esp, 0x10 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e73e: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44e749u; native_call(m, M32(0x4a9224u));	/* 44e743: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x4dfa00u));	/* 44e749: mov eax, dword ptr [0x4dfa00] */
	m->ecx = m->eax;	/* 44e74e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44e750: and ecx, 0x800001ff */
	if (!m->sf) goto L_44e760;	/* 44e756: jns 0x44e760 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44e758: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44e759: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44e75f: inc ecx */
L_44e760:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44e760: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44e761: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e767: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e768: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44e76a: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44e770: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44e773: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44e77cu; native_call(m, 0x4566c0u);	/* 44e777: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e77c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e781: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e786: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e78b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44e792u; native_call(m, m->ebx);	/* 44e790: call ebx */
	m->edi = M32((DWORD)(0x4a921cu));	/* 44e792: mov edi, dword ptr [0x4a921c] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e798: push 7 */
	m->esp -= 4; M32(m->esp) = 0x44e79cu; native_call(m, m->edi);	/* 44e79a: call edi */
	m->esi = M32((DWORD)(0x4a9208u));	/* 44e79c: mov esi, dword ptr [0x4a9208] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7a2: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7a4: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7a6: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7a8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44e7acu; native_call(m, m->esi);	/* 44e7aa: call esi */
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44e7ac: mov eax, dword ptr [0x9f8c50] */
	m->ecx = M32((DWORD)(0x9f8c54u));	/* 44e7b1: mov ecx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->eax, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e7b7: add eax, 0x4c */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e7ba: add ecx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7bd: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7be: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44e7c4u; native_call(m, 0x41ef60u);	/* 44e7bf: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e7c4: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7c7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7c9: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7cb: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7d0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44e7d4u; native_call(m, m->esi);	/* 44e7d2: call esi */
	m->edx = M32((DWORD)(0x9f8c50u));	/* 44e7d4: mov edx, dword ptr [0x9f8c50] */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44e7da: mov eax, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->edx, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44e7df: add edx, 0x4c */
	{ DWORD a_ = m->eax, b_ = 0x120u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e7e2: add eax, 0x120 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7e7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7e8: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e7eeu; native_call(m, 0x41ef60u);	/* 44e7e9: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e7ee: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7f1: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7f6: push 0 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7f8: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e7fd: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44e801u; native_call(m, m->esi);	/* 44e7ff: call esi */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44e801: mov ecx, dword ptr [0x9f8c50] */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44e807: mov edx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->ecx, b_ = 0x14cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e80d: add ecx, 0x14c */
	{ DWORD a_ = m->edx, b_ = 0x120u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44e813: add edx, 0x120 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e819: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e81a: push edx */
	m->esp -= 4; M32(m->esp) = 0x44e820u; native_call(m, 0x41ef60u);	/* 44e81b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e820: add esp, 8 */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e823: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e828: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e82a: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e82c: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44e830u; native_call(m, m->esi);	/* 44e82e: call esi */
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44e830: mov eax, dword ptr [0x9f8c50] */
	m->ecx = M32((DWORD)(0x9f8c54u));	/* 44e835: mov ecx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->eax, b_ = 0x14cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e83b: add eax, 0x14c */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e840: add ecx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e843: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e844: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44e84au; native_call(m, 0x41ef60u);	/* 44e845: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e84a: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x44e853u; native_call(m, M32(0x4a9220u));	/* 44e84d: call dword ptr [0x4a9220] */
	m->ecx = M32((DWORD)(0x9f8d30u));	/* 44e853: mov ecx, dword ptr [0x9f8d30] */
	m->esi = 0x3u;	/* 44e859: mov esi, 3 */
	m->eax = m->ecx;	/* 44e85e: mov eax, ecx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44e860: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->esi; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 44e861: idiv esi */
	m->eax = 0x55555556u;	/* 44e863: mov eax, 0x55555556 */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 44e868: mov dword ptr [esp + 0x1c], edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 44e86c: imul ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 44e86e: fild dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 44e872: fstp dword ptr [esp + 0x1c] */
	m->eax = m->edx;	/* 44e876: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44e878: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44e87b: add edx, eax */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 44e87d: push 7 */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 44e87f: mov dword ptr [esp + 0x1c], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x1cu)));	/* 44e883: fild dword ptr [esp + 0x1c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 44e887: fstp dword ptr [esp + 0x1c] */
	FPUSH((long double)(int)M32((DWORD)(0x9f6828u)));	/* 44e88b: fild dword ptr [0x9f6828] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 44e891: fld dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44e895: fmul dword ptr [0x4a95ec] */
	ST(0) = ST(0) - ST(1);	/* 44e89b: fsub st(1) */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0); FPOP();	/* 44e89d: fstp dword ptr [esp + 0x18] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 44e8a1: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44e8a5: fmul dword ptr [0x4a95ec] */
	ST(0) = ST(0) - ST(1);	/* 44e8ab: fsub st(1) */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0); FPOP();	/* 44e8ad: fstp dword ptr [esp + 0x14] */
	ST(0) = ST(0); FPOP();	/* 44e8b1: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x44e8b5u; native_call(m, m->edi);	/* 44e8b3: call edi */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 44e8b5: fld dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44e8b9: fmul dword ptr [0x4a95ec] */
	m->ebp = M32((DWORD)(0x4a920cu));	/* 44e8bf: mov ebp, dword ptr [0x4a920c] */
	MF((DWORD)(m->esp + 0x18u)) = (float)ST(0);	/* 44e8c5: fst dword ptr [esp + 0x18] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44e8c9: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 44e8cf: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x1cu)));	/* 44e8d3: fld dword ptr [esp + 0x1c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95ecu));	/* 44e8d7: fmul dword ptr [0x4a95ec] */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 44e8dd: mov esi, dword ptr [esp + 0x20] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e8e1: push esi */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0);	/* 44e8e2: fst dword ptr [esp + 0x20] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44e8e6: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 44e8ec: fstp dword ptr [esp + 0x28] */
	m->edi = M32((DWORD)(m->esp + 0x28u));	/* 44e8f0: mov edi, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e8f4: push edi */
	m->esp -= 4; M32(m->esp) = 0x44e8f7u; native_call(m, m->ebp);	/* 44e8f5: call ebp */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44e8f7: mov ecx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->ecx, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e8fd: add ecx, 0x4c */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 44e900: mov dword ptr [esp + 0x24], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44e904: fild dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44e908: fadd dword ptr [esp + 0x10] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44e90c: call 0x49ec14 */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44e911: mov edx, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e917: push eax */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44e918: add edx, 0x20 */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 44e91b: mov dword ptr [esp + 0x28], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 44e91f: fild dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 44e923: fadd dword ptr [esp + 0x18] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44e927: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e92c: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e932u; native_call(m, 0x41ef60u);	/* 44e92d: call 0x41ef60 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 44e932: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44e936: fadd dword ptr [0x4a95e8] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e93c: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44e93f: fmul dword ptr [0x4a957c] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e945: push esi */
	MF((DWORD)(m->esp + 0x28u)) = (float)ST(0); FPOP();	/* 44e946: fstp dword ptr [esp + 0x28] */
	m->esi = M32((DWORD)(m->esp + 0x28u));	/* 44e94a: mov esi, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e94e: push esi */
	m->esp -= 4; M32(m->esp) = 0x44e951u; native_call(m, m->ebp);	/* 44e94f: call ebp */
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44e951: mov eax, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->eax, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e956: add eax, 0x4c */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 44e959: mov dword ptr [esp + 0x24], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44e95d: fild dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44e961: fadd dword ptr [esp + 0x10] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44e965: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x9f6828u));	/* 44e96a: mov ecx, dword ptr [0x9f6828] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e970: push eax */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44e971: mov eax, dword ptr [0x9f8c54] */
	m->edx = (DWORD)(m->ecx + m->ecx*1 + 0x0u);	/* 44e976: lea edx, [ecx + ecx] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44e979: add eax, 0x20 */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 44e97c: mov dword ptr [esp + 0x28], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 44e980: fild dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 44e984: mov dword ptr [esp + 0x28], eax */
	ST(0) = ST(0) + (long double)(int)M32((DWORD)(m->esp + 0x28u));	/* 44e988: fiadd dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 44e98c: fadd dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44e990: fadd dword ptr [0x4a95e8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44e996: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e99b: push eax */
	m->esp -= 4; M32(m->esp) = 0x44e9a1u; native_call(m, 0x41ef60u);	/* 44e99c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44e9a1: add esp, 8 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 44e9a4: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44e9a8: fadd dword ptr [0x4a95e8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a957cu));	/* 44e9ae: fmul dword ptr [0x4a957c] */
	MF((DWORD)(m->esp + 0x1cu)) = (float)ST(0); FPOP();	/* 44e9b4: fstp dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 44e9b8: mov ecx, dword ptr [esp + 0x1c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44e9bc: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44e9bd: push esi */
	m->esp -= 4; M32(m->esp) = 0x44e9c0u; native_call(m, m->ebp);	/* 44e9be: call ebp */
	m->edx = M32((DWORD)(0x9f6828u));	/* 44e9c0: mov edx, dword ptr [0x9f6828] */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44e9c6: mov ecx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->ecx, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44e9cc: add ecx, 0x4c */
	m->eax = (DWORD)(m->edx + m->edx*1 + 0x0u);	/* 44e9cf: lea eax, [edx + edx] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 44e9d2: mov dword ptr [esp + 0x24], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44e9d6: fild dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 44e9da: mov dword ptr [esp + 0x24], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44e9de: fild dword ptr [esp + 0x24] */
	ST(0) = ST(0) + ST(1);	/* 44e9e2: fadd st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44e9e4: fadd dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44e9e8: fadd dword ptr [0x4a95e8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44e9ee: call 0x49ec14 */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44e9f3: mov edx, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44e9f9: push eax */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44e9fa: add edx, 0x20 */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 44e9fd: mov dword ptr [esp + 0x28], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 44ea01: fild dword ptr [esp + 0x28] */
	ST(0) = ST(0) + ST(1);	/* 44ea05: fadd st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 44ea07: fadd dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44ea0b: fadd dword ptr [0x4a95e8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44ea11: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ea16: push eax */
	ST(0) = ST(0); FPOP();	/* 44ea17: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x44ea1eu; native_call(m, 0x41ef60u);	/* 44ea19: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 44ea1e: mov eax, dword ptr [esp + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ea22: add esp, 8 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ea25: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ea26: push edi */
	m->esp -= 4; M32(m->esp) = 0x44ea29u; native_call(m, m->ebp);	/* 44ea27: call ebp */
	m->ecx = M32((DWORD)(0x9f6828u));	/* 44ea29: mov ecx, dword ptr [0x9f6828] */
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44ea2f: mov eax, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->eax, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ea34: add eax, 0x4c */
	m->edx = (DWORD)(m->ecx + m->ecx*1 + 0x0u);	/* 44ea37: lea edx, [ecx + ecx] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 44ea3a: mov dword ptr [esp + 0x24], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44ea3e: fild dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 44ea42: mov dword ptr [esp + 0x24], eax */
	ST(0) = ST(0) + (long double)(int)M32((DWORD)(m->esp + 0x24u));	/* 44ea46: fiadd dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44ea4a: fadd dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a95e8u));	/* 44ea4e: fadd dword ptr [0x4a95e8] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44ea54: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x9f8c54u));	/* 44ea59: mov ecx, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ea5f: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44ea60: add ecx, 0x20 */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 44ea63: mov dword ptr [esp + 0x28], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 44ea67: fild dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 44ea6b: fadd dword ptr [esp + 0x18] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44ea6f: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ea74: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ea7au; native_call(m, 0x41ef60u);	/* 44ea75: call 0x41ef60 */
	m->esi = M32((DWORD)(0x4a9220u));	/* 44ea7a: mov esi, dword ptr [0x4a9220] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ea80: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x44ea85u; native_call(m, m->esi);	/* 44ea83: call esi */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ea85: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44ea90u; native_call(m, M32(0x4a922cu));	/* 44ea8a: call dword ptr [0x4a922c] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ea90: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44ea9bu; native_call(m, M32(0x4a9224u));	/* 44ea95: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9dad90u));	/* 44ea9b: mov eax, dword ptr [0x9dad90] */
	m->edx = m->eax;	/* 44eaa0: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44eaa2: and edx, 0x800001ff */
	if (!m->sf) goto L_44eab2;	/* 44eaa8: jns 0x44eab2 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 44eaaa: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44eaab: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44eab1: inc edx */
L_44eab2:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44eab2: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 44eab3: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44eab9: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44eaba: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44eac0: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44eac2: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 44eac5: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44eaceu; native_call(m, 0x4566c0u);	/* 44eac9: call 0x4566c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9f8f08u)));	/* 44eace: fld dword ptr [0x9f8f08] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9428u));	/* 44ead4: fmul dword ptr [0x4a9428] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44eada: push ecx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 44eadb: fsubr dword ptr [0x4a9424] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 44eae1: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44eae4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44eae9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44eaee: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44eaf5u; native_call(m, m->ebx);	/* 44eaf3: call ebx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 44eaf5: push 7 */
	m->esp -= 4; M32(m->esp) = 0x44eafdu; native_call(m, M32(0x4a921cu));	/* 44eaf7: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44eafd: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44eb02: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44eb06u; native_call(m, m->ebp);	/* 44eb04: call ebp */
	m->edx = M32((DWORD)(0x9f8c50u));	/* 44eb06: mov edx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->edx, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44eb0c: add edx, 0x4c */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 44eb0f: mov dword ptr [esp + 0x24], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44eb13: fild dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44eb17: fadd dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 44eb1b: fsub dword ptr [0x4a93d0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44eb21: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44eb26: push eax */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44eb27: mov eax, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44eb2c: add eax, 0x20 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 44eb2f: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 44eb33: fild dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 44eb37: fadd dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 44eb3b: fsub dword ptr [0x4a93d0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44eb41: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44eb46: push eax */
	m->esp -= 4; M32(m->esp) = 0x44eb4cu; native_call(m, 0x41ef60u);	/* 44eb47: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44eb4c: add esp, 8 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44eb4f: push 0x3f000000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44eb54: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x44eb5bu; native_call(m, m->ebp);	/* 44eb59: call ebp */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44eb5b: mov ecx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->ecx, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44eb61: add ecx, 0x4c */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 44eb64: mov dword ptr [esp + 0x24], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44eb68: fild dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44eb6c: fadd dword ptr [esp + 0x10] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 44eb70: fsub dword ptr [0x4a93d0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44eb76: call 0x49ec14 */
	m->edx = M32((DWORD)(0x9f6828u));	/* 44eb7b: mov edx, dword ptr [0x9f6828] */
	m->ecx = M32((DWORD)(0x9f8c54u));	/* 44eb81: mov ecx, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44eb87: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44eb88: add ecx, 0x20 */
	m->eax = (DWORD)(m->edx + m->edx*1 + 0x0u);	/* 44eb8b: lea eax, [edx + edx] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 44eb8e: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 44eb92: fild dword ptr [esp + 0x28] */
	M32((DWORD)(m->esp + 0x28u)) = m->ecx;	/* 44eb96: mov dword ptr [esp + 0x28], ecx */
	ST(0) = ST(0) + (long double)(int)M32((DWORD)(m->esp + 0x28u));	/* 44eb9a: fiadd dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 44eb9e: fadd dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9550u));	/* 44eba2: fadd dword ptr [0x4a9550] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44eba8: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ebad: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ebb3u; native_call(m, 0x41ef60u);	/* 44ebae: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ebb3: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ebb6: push 0x3f800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ebbb: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x44ebc2u; native_call(m, m->ebp);	/* 44ebc0: call ebp */
	m->edx = M32((DWORD)(0x9f6828u));	/* 44ebc2: mov edx, dword ptr [0x9f6828] */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44ebc8: mov ecx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->ecx, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44ebce: add ecx, 0x4c */
	m->eax = (DWORD)(m->edx + m->edx*1 + 0x0u);	/* 44ebd1: lea eax, [edx + edx] */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 44ebd4: mov dword ptr [esp + 0x24], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44ebd8: fild dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 44ebdc: mov dword ptr [esp + 0x24], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44ebe0: fild dword ptr [esp + 0x24] */
	ST(0) = ST(0) + ST(1);	/* 44ebe4: fadd st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44ebe6: fadd dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9550u));	/* 44ebea: fadd dword ptr [0x4a9550] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44ebf0: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ebf5: push eax */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44ebf6: mov edx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->edx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44ebfc: add edx, 0x20 */
	M32((DWORD)(m->esp + 0x28u)) = m->edx;	/* 44ebff: mov dword ptr [esp + 0x28], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 44ec03: fild dword ptr [esp + 0x28] */
	ST(0) = ST(0) + ST(1);	/* 44ec07: fadd st(1) */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 44ec09: fadd dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9550u));	/* 44ec0d: fadd dword ptr [0x4a9550] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44ec13: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ec18: push eax */
	ST(0) = ST(0); FPOP();	/* 44ec19: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x44ec20u; native_call(m, 0x41ef60u);	/* 44ec1b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ec20: add esp, 8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ec23: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ec28: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44ec2cu; native_call(m, m->ebp);	/* 44ec2a: call ebp */
	m->eax = M32((DWORD)(0x9f6828u));	/* 44ec2c: mov eax, dword ptr [0x9f6828] */
	m->edx = M32((DWORD)(0x9f8c50u));	/* 44ec31: mov edx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->edx, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44ec37: add edx, 0x4c */
	m->ecx = (DWORD)(m->eax + m->eax*1 + 0x0u);	/* 44ec3a: lea ecx, [eax + eax] */
	M32((DWORD)(m->esp + 0x24u)) = m->ecx;	/* 44ec3d: mov dword ptr [esp + 0x24], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x24u)));	/* 44ec41: fild dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x24u)) = m->edx;	/* 44ec45: mov dword ptr [esp + 0x24], edx */
	ST(0) = ST(0) + (long double)(int)M32((DWORD)(m->esp + 0x24u));	/* 44ec49: fiadd dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 44ec4d: fadd dword ptr [esp + 0x10] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9550u));	/* 44ec51: fadd dword ptr [0x4a9550] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44ec57: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ec5c: push eax */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44ec5d: mov eax, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->eax, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ec62: add eax, 0x20 */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 44ec65: mov dword ptr [esp + 0x28], eax */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x28u)));	/* 44ec69: fild dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esp + 0x18u));	/* 44ec6d: fadd dword ptr [esp + 0x18] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a93d0u));	/* 44ec71: fsub dword ptr [0x4a93d0] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44ec77: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ec7c: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ec82u; native_call(m, 0x41ef60u);	/* 44ec7d: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ec82: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x44ec87u; native_call(m, m->esi);	/* 44ec85: call esi */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 44ec87: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x9f8c48u));	/* 44ec8d: fmul dword ptr [0x9f8c48] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9f8f08u));	/* 44ec93: fadd dword ptr [0x9f8f08] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93fcu));	/* 44ec99: fcom dword ptr [0x4a93fc] */
	MF((DWORD)(0x9f8f08u)) = (float)ST(0);	/* 44ec9f: fst dword ptr [0x9f8f08] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44eca5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44eca7: test ah, 0x41 */
	if (m->zf) goto L_44ecb6;	/* 44ecaa: je 0x44ecb6 */
	M32((DWORD)(0x9f8c48u)) = 0x3f800000u;	/* 44ecac: mov dword ptr [0x9f8c48], 0x3f800000 */
L_44ecb6:
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93f8u)); FPOP();	/* 44ecb6: fcomp dword ptr [0x4a93f8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44ecbc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44ecbe: test ah, 1 */
	if (!m->zf) goto L_44eccd;	/* 44ecc1: jne 0x44eccd */
	M32((DWORD)(0x9f8c48u)) = 0xbf800000u;	/* 44ecc3: mov dword ptr [0x9f8c48], 0xbf800000 */
L_44eccd:
	{ DWORD a_ = M32((DWORD)(0x9f6828u)), b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44eccd: cmp dword ptr [0x9f6828], 8 */
	if (m->sf == m->of) goto L_44ed0a;	/* 44ecd4: jge 0x44ed0a */
	FPUSH(x87_ldm((const float *)(DWORD)(0x9f8ee4u)));	/* 44ecd6: fld dword ptr [0x9f8ee4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44ecdc: fadd dword ptr [0x4b071c] */
	MF((DWORD)(0x9f8ee4u)) = (float)ST(0);	/* 44ece2: fst dword ptr [0x9f8ee4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 44ece8: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44ecee: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44ecf0: test ah, 0x41 */
	if (!m->zf) goto L_44ed0a;	/* 44ecf3: jne 0x44ed0a */
	m->eax = M32((DWORD)(0x9f6828u));	/* 44ecf5: mov eax, dword ptr [0x9f6828] */
	M32((DWORD)(0x9f8ee4u)) = 0x0u;	/* 44ecfa: mov dword ptr [0x9f8ee4], 0 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44ed04: inc eax */
	M32((DWORD)(0x9f6828u)) = m->eax;	/* 44ed05: mov dword ptr [0x9f6828], eax */
L_44ed0a:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed0a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed0f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed14: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed19: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed1b: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x44ed25u; native_call(m, 0x41f0e0u);	/* 44ed20: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44ed25: mov eax, dword ptr [0x9f8c50] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed2a: push 0 */
	m->ecx = (DWORD)(m->eax + 0x158u);	/* 44ed2c: lea ecx, [eax + 0x158] */
	{ DWORD a_ = m->eax, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ed32: add eax, 0x40 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed35: push ecx */
	m->ecx = M32((DWORD)(0x9f8c54u));	/* 44ed36: mov ecx, dword ptr [0x9f8c54] */
	m->edx = (DWORD)(m->ecx + 0x22au);	/* 44ed3c: lea edx, [ecx + 0x22a] */
	{ DWORD a_ = m->ecx, b_ = 0x130u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44ed42: add ecx, 0x130 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed48: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed49: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed4a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44ed50u; native_call(m, 0x427970u);	/* 44ed4b: call 0x427970 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ed50: add esp, 0x28 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44ed53: xor esi, esi */
	m->edi = 0x75e824u;	/* 44ed55: mov edi, 0x75e824 */
L_44ed5a:
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44ed5a: mov eax, dword ptr [0x9f8c50] */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44ed5f: mov edx, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed65: push edi */
	{ DWORD a_ = m->edx, b_ = 0x138u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44ed66: add edx, 0x138 */
	m->ecx = (DWORD)(m->esi + m->eax*1 + 0x48u);	/* 44ed6c: lea ecx, [esi + eax + 0x48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed70: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed71: push edx */
	m->esp -= 4; M32(m->esp) = 0x44ed77u; native_call(m, 0x402620u);	/* 44ed72: call 0x402620 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44ed77: add edi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ed7d: add esp, 0xc */
	{ DWORD a_ = m->esi, b_ = 0x15u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44ed80: add esi, 0x15 */
	{ DWORD a_ = m->edi, b_ = 0x75eea4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ed83: cmp edi, 0x75eea4 */
	if (m->sf != m->of) goto L_44ed5a;	/* 44ed89: jl 0x44ed5a */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed8b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed90: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed95: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed9a: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ed9f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44eda9u; native_call(m, 0x41f0e0u);	/* 44eda4: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44eda9: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44edae: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44edb1: lea edx, [eax + ecx*2] */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44edb4: mov ecx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->ecx, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44edba: add ecx, 0x48 */
	m->eax = (DWORD)(m->edx*4 + 0x9f9040u);	/* 44edbd: lea eax, [edx*4 + 0x9f9040] */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44edc4: mov edx, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44edca: push eax */
	{ DWORD a_ = m->edx, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44edcb: add edx, 0x184 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44edd1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44edd2: push edx */
	m->esp -= 4; M32(m->esp) = 0x44edd8u; native_call(m, 0x402620u);	/* 44edd3: call 0x402620 */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44edd8: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44eddd: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44ede0: lea edx, [eax + ecx*2] */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44ede3: mov ecx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->ecx, b_ = 0x5du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44ede9: add ecx, 0x5d */
	m->eax = (DWORD)(m->edx*4 + 0x9f9050u);	/* 44edec: lea eax, [edx*4 + 0x9f9050] */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44edf3: mov edx, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44edf9: push eax */
	{ DWORD a_ = m->edx, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44edfa: add edx, 0x184 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee00: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee01: push edx */
	m->esp -= 4; M32(m->esp) = 0x44ee07u; native_call(m, 0x402620u);	/* 44ee02: call 0x402620 */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44ee07: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44ee0c: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44ee0f: lea edx, [eax + ecx*2] */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44ee12: mov ecx, dword ptr [0x9f8c50] */
	{ DWORD a_ = m->ecx, b_ = 0x72u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44ee18: add ecx, 0x72 */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9060u));	/* 44ee1b: mov eax, dword ptr [edx*4 + 0x9f9060] */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44ee22: mov edx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44ee28: shl eax, 7 */
	{ DWORD a_ = m->eax, b_ = 0x75eea4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ee2b: add eax, 0x75eea4 */
	{ DWORD a_ = m->edx, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44ee30: add edx, 0x184 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee36: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee37: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee38: push edx */
	m->esp -= 4; M32(m->esp) = 0x44ee3eu; native_call(m, 0x402620u);	/* 44ee39: call 0x402620 */
	m->eax = (DWORD)(m->esp + 0x64u);	/* 44ee3e: lea eax, [esp + 0x64] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee42: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee44: push eax */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44ee45: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44ee4a: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44ee4d: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9064u));	/* 44ee50: mov eax, dword ptr [edx*4 + 0x9f9064] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee57: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ee5du; native_call(m, 0x49fb53u);	/* 44ee58: call 0x49fb53 */
	m->edx = M32((DWORD)(0x9f8c50u));	/* 44ee5d: mov edx, dword ptr [0x9f8c50] */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44ee63: mov eax, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ee68: add esp, 0x44 */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 44ee6b: lea ecx, [esp + 0x2c] */
	{ DWORD a_ = m->edx, b_ = 0x87u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44ee6f: add edx, 0x87 */
	{ DWORD a_ = m->eax, b_ = 0x184u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ee75: add eax, 0x184 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee7a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee7b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ee7c: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ee82u; native_call(m, 0x402620u);	/* 44ee7d: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ee82: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44ee85: xor eax, eax */
	M32((DWORD)(m->esp + 0x1cu)) = 0x54u;	/* 44ee87: mov dword ptr [esp + 0x1c], 0x54 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 44ee8f: mov dword ptr [esp + 0x10], eax */
	goto L_44ee99;	/* 44ee93: jmp 0x44ee99 */
L_44ee95:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 44ee95: mov eax, dword ptr [esp + 0x10] */
L_44ee99:
	m->esi = 0x8u;	/* 44ee99: mov esi, 8 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ee9e: cmp eax, esi */
	if (!m->cf && !m->zf) goto L_44efb7;	/* 44eea0: ja 0x44efb7 */
	switch (m->eax) { case 0: goto L_44eead; case 1: goto L_44eecb; case 2: goto L_44eeea; case 3: goto L_44ef08; case 4: goto L_44ef27; case 5: goto L_44ef42; case 6: goto L_44ef5e; case 7: goto L_44ef79; case 8: goto L_44ef95; default: abort(); }	/* 44eea6: jmp dword ptr [eax*4 + 0x44f3e4] */
L_44eead:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44eead: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 44eeb2: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44eeb6: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44eeb8: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44eeb9: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44eebc: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9068u));	/* 44eebf: mov ecx, dword ptr [eax*4 + 0x9f9068] */
	goto L_44efae;	/* 44eec6: jmp 0x44efae */
L_44eecb:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44eecb: mov eax, dword ptr [0x9f8d30] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 44eed0: lea edx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44eed4: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44eed6: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44eed7: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44eeda: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f906cu));	/* 44eedd: mov eax, dword ptr [edx*4 + 0x9f906c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44eee4: push eax */
	goto L_44efaf;	/* 44eee5: jmp 0x44efaf */
L_44eeea:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44eeea: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 44eeef: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44eef3: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44eef5: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44eef6: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44eef9: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9070u));	/* 44eefc: mov ecx, dword ptr [eax*4 + 0x9f9070] */
	goto L_44efae;	/* 44ef03: jmp 0x44efae */
L_44ef08:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44ef08: mov eax, dword ptr [0x9f8d30] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 44ef0d: lea edx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef11: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef13: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44ef14: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44ef17: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9074u));	/* 44ef1a: mov eax, dword ptr [edx*4 + 0x9f9074] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef21: push eax */
	goto L_44efaf;	/* 44ef22: jmp 0x44efaf */
L_44ef27:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44ef27: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 44ef2c: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef30: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef32: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44ef33: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44ef36: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9078u));	/* 44ef39: mov ecx, dword ptr [eax*4 + 0x9f9078] */
	goto L_44efae;	/* 44ef40: jmp 0x44efae */
L_44ef42:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44ef42: mov eax, dword ptr [0x9f8d30] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 44ef47: lea edx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef4b: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef4d: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44ef4e: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44ef51: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f907cu));	/* 44ef54: mov eax, dword ptr [edx*4 + 0x9f907c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef5b: push eax */
	goto L_44efaf;	/* 44ef5c: jmp 0x44efaf */
L_44ef5e:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44ef5e: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 44ef63: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef67: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef69: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44ef6a: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44ef6d: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9080u));	/* 44ef70: mov ecx, dword ptr [eax*4 + 0x9f9080] */
	goto L_44efae;	/* 44ef77: jmp 0x44efae */
L_44ef79:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44ef79: mov eax, dword ptr [0x9f8d30] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 44ef7e: lea edx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef82: push 0xa */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef84: push edx */
	m->ecx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44ef85: lea ecx, [eax + eax*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 44ef88: lea edx, [eax + ecx*2] */
	m->eax = M32((DWORD)(m->edx*4 + 0x9f9084u));	/* 44ef8b: mov eax, dword ptr [edx*4 + 0x9f9084] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef92: push eax */
	goto L_44efaf;	/* 44ef93: jmp 0x44efaf */
L_44ef95:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44ef95: mov eax, dword ptr [0x9f8d30] */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 44ef9a: lea ecx, [esp + 0x2c] */
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 44ef9e: push 0xa */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44efa0: push ecx */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 44efa1: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->eax + m->edx*2 + 0x0u);	/* 44efa4: lea eax, [eax + edx*2] */
	m->ecx = M32((DWORD)(m->eax*4 + 0x9f9088u));	/* 44efa7: mov ecx, dword ptr [eax*4 + 0x9f9088] */
L_44efae:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44efae: push ecx */
L_44efaf:
	m->esp -= 4; M32(m->esp) = 0x44efb4u; native_call(m, 0x49fb53u);	/* 44efaf: call 0x49fb53 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44efb4: add esp, 0xc */
L_44efb7:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x2cu))) & 0xff) << 0);	/* 44efb7: mov al, byte ptr [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x14u)) = 0x0u;	/* 44efbb: mov dword ptr [esp + 0x14], 0 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x2du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 44efc3: cmp al, 0x2d */
	if (m->zf) goto L_44efe8;	/* 44efc5: je 0x44efe8 */
	m->edi = (DWORD)(m->esp + 0x2cu);	/* 44efc7: lea edi, [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44efcb: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44efce: xor eax, eax */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 44efd0: mov dword ptr [esp + 0x14], esi */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44efd4: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44efd6: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44efd8: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44efd9: cmp ecx, 2 */
	if (!m->cf) goto L_44efff;	/* 44efdc: jae 0x44efff */
	M32((DWORD)(m->esp + 0x14u)) = 0x10u;	/* 44efde: mov dword ptr [esp + 0x14], 0x10 */
	goto L_44efff;	/* 44efe6: jmp 0x44efff */
L_44efe8:
	m->edi = (DWORD)(m->esp + 0x2cu);	/* 44efe8: lea edi, [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44efec: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44efef: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44eff1: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44eff3: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44eff5: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44eff6: cmp ecx, 3 */
	if (!m->cf) goto L_44efff;	/* 44eff9: jae 0x44efff */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 44effb: mov dword ptr [esp + 0x14], esi */
L_44efff:
	m->edi = 0x4b3e2cu;	/* 44efff: mov edi, 0x4b3e2c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44f004: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 44f007: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 44f009: lea edx, [esp + 0x2c] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44f00d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 44f00f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44f011: sub edi, ecx */
	m->esi = m->edi;	/* 44f013: mov esi, edi */
	m->edi = m->edx;	/* 44f015: mov edi, edx */
	m->edx = m->ecx;	/* 44f017: mov edx, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44f019: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 44f01c: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 44f01e: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 44f020: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 44f021: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 44f024: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 44f026: mov ecx, edx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 44f028: lea eax, [esp + 0x2c] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44f02c: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f02f: push eax */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44f030: mov eax, dword ptr [0x9f8c54] */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 44f035: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44f037: mov ecx, dword ptr [0x9f8c50] */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 44f03d: mov esi, dword ptr [esp + 0x20] */
	m->edx = (DWORD)(m->esi + m->ecx*1 + 0x48u);	/* 44f041: lea edx, [esi + ecx + 0x48] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 44f045: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f049: push edx */
	m->edx = (DWORD)(m->eax + m->ecx*1 + 0x192u);	/* 44f04a: lea edx, [eax + ecx + 0x192] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f051: push edx */
	m->esp -= 4; M32(m->esp) = 0x44f057u; native_call(m, 0x402620u);	/* 44f052: call 0x402620 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 44f057: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f05b: add esp, 0xc */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44f05e: inc eax */
	{ DWORD a_ = m->esi, b_ = 0x15u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44f05f: add esi, 0x15 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 44f062: mov dword ptr [esp + 0x10], eax */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44f066: add eax, 4 */
	{ DWORD a_ = m->eax, b_ = 0xdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f069: cmp eax, 0xd */
	M32((DWORD)(m->esp + 0x1cu)) = m->esi;	/* 44f06c: mov dword ptr [esp + 0x1c], esi */
	if (m->sf != m->of) goto L_44ee95;	/* 44f070: jl 0x44ee95 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f076: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44f081u; native_call(m, M32(0x4a9224u));	/* 44f07b: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44f081: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44f086: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44f088: and ecx, 0x800001ff */
	if (!m->sf) goto L_44f098;	/* 44f08e: jns 0x44f098 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44f090: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44f091: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44f097: inc ecx */
L_44f098:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44f098: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44f099: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f09f: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44f0a0: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44f0a2: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44f0a8: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44f0ab: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44f0b4u; native_call(m, 0x4566c0u);	/* 44f0af: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0b4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0b9: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0be: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0c3: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44f0cau; native_call(m, m->ebx);	/* 44f0c8: call ebx */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 44f0ca: xor edi, edi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44f0cc: xor esi, esi */
L_44f0ce:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0ce: push 7 */
	m->esp -= 4; M32(m->esp) = 0x44f0d6u; native_call(m, M32(0x4a921cu));	/* 44f0d0: call dword ptr [0x4a921c] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0d6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0db: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0e0: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f0e5: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44f0ecu; native_call(m, m->ebx);	/* 44f0ea: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x9f8ec0u)));	/* 44f0ec: fld dword ptr [esi + 0x9f8ec0] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esi + 0x9f8d34u));	/* 44f0f2: fsub dword ptr [esi + 0x9f8d34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44f0f8: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 44f0fe: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x9f8d34u));	/* 44f104: fadd dword ptr [esi + 0x9f8d34] */
	MF((DWORD)(m->esi + 0x9f8d34u)) = (float)ST(0);	/* 44f10a: fst dword ptr [esi + 0x9f8d34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 44f110: fmul dword ptr [0x4a9420] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9468u));	/* 44f116: fadd dword ptr [0x4a9468] */
	MF((DWORD)(m->esp + 0x14u)) = (float)ST(0);	/* 44f11c: fst dword ptr [esp + 0x14] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a953cu)); FPOP();	/* 44f120: fcomp dword ptr [0x4a953c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44f126: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44f128: test ah, 0x41 */
	if (!m->zf) goto L_44f135;	/* 44f12b: jne 0x44f135 */
	M32((DWORD)(m->esp + 0x14u)) = 0x3f733333u;	/* 44f12d: mov dword ptr [esp + 0x14], 0x3f733333 */
L_44f135:
	{ DWORD v_ = 0x3e400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f135: push 0x3e400000 */
	{ DWORD v_ = 0x3d4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44f13a: push 0x3d4ccccd */
	m->esp -= 4; M32(m->esp) = 0x44f141u; native_call(m, m->ebp);	/* 44f13f: call ebp */
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44f141: mov eax, dword ptr [0x9f8c50] */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44f146: mov edx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->edx, b_ = 0x1bcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44f14c: add edx, 0x1bc */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x9fu);	/* 44f152: lea ecx, [edi + eax + 0x9f] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f159: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f15a: push edx */
	m->esp -= 4; M32(m->esp) = 0x44f160u; native_call(m, 0x41ef60u);	/* 44f15b: call 0x41ef60 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 44f160: mov eax, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f164: add esp, 8 */
	{ DWORD v_ = 0x3e400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f167: push 0x3e400000 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f16c: push eax */
	m->esp -= 4; M32(m->esp) = 0x44f16fu; native_call(m, m->ebp);	/* 44f16d: call ebp */
	m->ecx = M32((DWORD)(0x9f8c50u));	/* 44f16f: mov ecx, dword ptr [0x9f8c50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x9f8d34u)));	/* 44f175: fld dword ptr [esi + 0x9f8d34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95f4u));	/* 44f17b: fmul dword ptr [0x4a95f4] */
	m->edx = (DWORD)(m->edi + m->ecx*1 + 0x9fu);	/* 44f181: lea edx, [edi + ecx + 0x9f] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f188: push edx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44f189: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x9f8c54u));	/* 44f18e: mov ecx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44f194: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x1bcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44f196: add ecx, 0x1bc */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f19c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44f1a2u; native_call(m, 0x41ef60u);	/* 44f19d: call 0x41ef60 */
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 44f1a2: mov edx, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f1a6: add esp, 8 */
	{ DWORD v_ = 0x3e400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f1a9: push 0x3e400000 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f1ae: push edx */
	m->esp -= 4; M32(m->esp) = 0x44f1b1u; native_call(m, m->ebp);	/* 44f1af: call ebp */
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44f1b1: mov eax, dword ptr [0x9f8c50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x9f8d34u)));	/* 44f1b6: fld dword ptr [esi + 0x9f8d34] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a95f4u));	/* 44f1bc: fmul dword ptr [0x4a95f4] */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0xa4u);	/* 44f1c2: lea ecx, [edi + eax + 0xa4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f1c9: push ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 44f1ca: call 0x49ec14 */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44f1cf: mov edx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44f1d5: sub edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x1bcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44f1d7: add edx, 0x1bc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f1dd: push edx */
	m->esp -= 4; M32(m->esp) = 0x44f1e3u; native_call(m, 0x41ef60u);	/* 44f1de: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f1e3: add esp, 8 */
	{ DWORD v_ = 0x3e400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f1e6: push 0x3e400000 */
	{ DWORD v_ = 0x3d4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44f1eb: push 0x3d4ccccd */
	m->esp -= 4; M32(m->esp) = 0x44f1f2u; native_call(m, m->ebp);	/* 44f1f0: call ebp */
	m->eax = M32((DWORD)(0x9f8c50u));	/* 44f1f2: mov eax, dword ptr [0x9f8c50] */
	m->edx = M32((DWORD)(0x9f8c54u));	/* 44f1f7: mov edx, dword ptr [0x9f8c54] */
	{ DWORD a_ = m->edx, b_ = 0x1bcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44f1fd: add edx, 0x1bc */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0xa4u);	/* 44f203: lea ecx, [edi + eax + 0xa4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f20a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f20b: push edx */
	m->esp -= 4; M32(m->esp) = 0x44f211u; native_call(m, 0x41ef60u);	/* 44f20c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f211: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x44f21au; native_call(m, M32(0x4a9220u));	/* 44f214: call dword ptr [0x4a9220] */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44f21a: add esi, 4 */
	{ DWORD a_ = m->edi, b_ = 0x15u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44f21d: add edi, 0x15 */
	{ DWORD a_ = m->esi, b_ = 0x24u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f220: cmp esi, 0x24 */
	if (m->sf != m->of) goto L_44f0ce;	/* 44f223: jl 0x44f0ce */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f229: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44f234u; native_call(m, M32(0x4a922cu));	/* 44f22e: call dword ptr [0x4a922c] */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 44f234: xor ebp, ebp */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 44f236: xor esi, esi */
	m->edi = 0x7517a4u;	/* 44f238: mov edi, 0x7517a4 */
L_44f23d:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f23d: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x44f248u; native_call(m, M32(0x4a9224u));	/* 44f242: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 44f248: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 44f24d: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44f24f: and ecx, 0x800001ff */
	if (!m->sf) goto L_44f25f;	/* 44f255: jns 0x44f25f */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44f257: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 44f258: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 44f25e: inc ecx */
L_44f25f:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44f25f: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 44f260: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f266: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44f267: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 44f269: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 44f26f: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 44f272: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x44f27bu; native_call(m, 0x4566c0u);	/* 44f276: call 0x4566c0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f27b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f280: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f285: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f28a: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44f291u; native_call(m, m->ebx);	/* 44f28f: call ebx */
	m->ecx = M32((DWORD)(m->esp + 0x28u));	/* 44f291: mov ecx, dword ptr [esp + 0x28] */
	m->eax = (DWORD)(m->ebp + 0x9u);	/* 44f295: lea eax, [ebp + 9] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f298: cmp ecx, eax */
	if (!m->zf) goto L_44f2f8;	/* 44f29a: jne 0x44f2f8 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f29c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2a1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2a6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2ab: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44f2b2u; native_call(m, m->ebx);	/* 44f2b0: call ebx */
	m->ecx = M32((DWORD)(0x9f682cu));	/* 44f2b2: mov ecx, dword ptr [0x9f682c] */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44f2b8: mov eax, dword ptr [0x9f8c54] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2bd: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 44f2bf: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44f2c2: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2c5: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x122u);	/* 44f2c6: lea edx, [esi + eax + 0x122] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2cd: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0xaau);	/* 44f2ce: lea eax, [esi + eax + 0xaa] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2d5: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2d6: push eax */
	m->esp -= 4; M32(m->esp) = 0x44f2dcu; native_call(m, 0x4282f0u);	/* 44f2d7: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f8ebcu));	/* 44f2dc: mov ecx, dword ptr [0x9f8ebc] */
	m->edx = M32((DWORD)(0x9f8eb8u));	/* 44f2e2: mov edx, dword ptr [0x9f8eb8] */
	m->eax = M32((DWORD)(0x9f8eb4u));	/* 44f2e8: mov eax, dword ptr [0x9f8eb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2ed: push ecx */
	m->ecx = M32((DWORD)(0x9f8eb0u));	/* 44f2ee: mov ecx, dword ptr [0x9f8eb0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2f4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2f5: push eax */
	goto L_44f352;	/* 44f2f6: jmp 0x44f352 */
L_44f2f8:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2f8: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f2fd: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f302: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f307: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44f30eu; native_call(m, m->ebx);	/* 44f30c: call ebx */
	m->ecx = M32((DWORD)(0x9f682cu));	/* 44f30e: mov ecx, dword ptr [0x9f682c] */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44f314: mov eax, dword ptr [0x9f8c54] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f319: push 1 */
	m->edx = (DWORD)(m->ecx + 0xffffffe0u);	/* 44f31b: lea edx, [ecx - 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44f31e: add ecx, -0x40 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f321: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x122u);	/* 44f322: lea edx, [esi + eax + 0x122] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f329: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0xaau);	/* 44f32a: lea eax, [esi + eax + 0xaa] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f331: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f332: push eax */
	m->esp -= 4; M32(m->esp) = 0x44f338u; native_call(m, 0x4282f0u);	/* 44f333: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x9f8d64u));	/* 44f338: mov ecx, dword ptr [0x9f8d64] */
	m->edx = M32((DWORD)(0x9f8d60u));	/* 44f33e: mov edx, dword ptr [0x9f8d60] */
	m->eax = M32((DWORD)(0x9f8d5cu));	/* 44f344: mov eax, dword ptr [0x9f8d5c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f349: push ecx */
	m->ecx = M32((DWORD)(0x9f8d58u));	/* 44f34a: mov ecx, dword ptr [0x9f8d58] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f350: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f351: push eax */
L_44f352:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f352: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f353: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x44f35du; native_call(m, 0x41f0e0u);	/* 44f358: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44f35d: mov eax, dword ptr [0x9f8c54] */
	m->ecx = M32((DWORD)(0x9f682cu));	/* 44f362: mov ecx, dword ptr [0x9f682c] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f368: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffc8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44f36b: add ecx, -0x38 */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x122u);	/* 44f36e: lea edx, [esi + eax + 0x122] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44f375: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f376: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0xaau);	/* 44f377: lea edx, [esi + eax + 0xaa] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f37e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f37f: push edx */
	m->esp -= 4; M32(m->esp) = 0x44f385u; native_call(m, 0x4029d0u);	/* 44f380: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f385: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 44f388: add edi, 0x80 */
	{ DWORD a_ = m->ebp, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebp = r_; }	/* 44f38e: inc ebp */
	{ DWORD a_ = m->esi, b_ = 0xa0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 44f38f: add esi, 0xa0 */
	{ DWORD a_ = m->edi, b_ = 0x7518a4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44f395: cmp edi, 0x7518a4 */
	if (m->sf != m->of) goto L_44f23d;	/* 44f39b: jl 0x44f23d */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f3a1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f3a6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f3ab: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 44f3b0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x44f3b7u; native_call(m, m->ebx);	/* 44f3b5: call ebx */
	m->eax = M32((DWORD)(0x9f682cu));	/* 44f3b7: mov eax, dword ptr [0x9f682c] */
	m->ecx = M32((DWORD)(0x9f6830u));	/* 44f3bc: mov ecx, dword ptr [0x9f6830] */
	m->edx = M32((DWORD)(0x9f8c50u));	/* 44f3c2: mov edx, dword ptr [0x9f8c50] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f3c8: push eax */
	m->eax = M32((DWORD)(0x9f8c54u));	/* 44f3c9: mov eax, dword ptr [0x9f8c54] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f3ce: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f3cf: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f3d0: push eax */
	m->esp -= 4; M32(m->esp) = 0x44f3d6u; native_call(m, 0x428a00u);	/* 44f3d1: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f3d6: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44f3d9: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44f3da: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44f3db: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44f3dc: pop ebx */
	m->esp = m->ebp;	/* 44f3dd: mov esp, ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 44f3df: pop ebp */
	m->esp += 4 + 0; return;	/* 44f3e0: ret  */
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
