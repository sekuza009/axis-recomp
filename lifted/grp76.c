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

static void lift_424810(X86 *m);

/* setup_424810 (0x424810), lifted by tools/lift.py */
static void lift_424810(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424810: push ecx */
	m->eax = M32((DWORD)(0x4ded6cu));	/* 424811: mov eax, dword ptr [0x4ded6c] */
	m->ecx = M32((DWORD)(0x4ded68u));	/* 424816: mov ecx, dword ptr [0x4ded68] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 42481c: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 42481d: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42481e: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 42481f: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424820: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424821: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424827u; native_call(m, 0x420670u);	/* 424822: call 0x420670 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 424827: push 2 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 424829: mov dword ptr [esp + 0x1c], eax */
	m->esp -= 4; M32(m->esp) = 0x424832u; native_call(m, 0x41ef90u);	/* 42482d: call 0x41ef90 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424832: add esp, 0xc */
	m->esp -= 4; M32(m->esp) = 0x42483bu; native_call(m, M32(0x4a9218u));	/* 424835: call dword ptr [0x4a9218] */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 42483b: mov ebp, dword ptr [0x4a9228] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424841: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424846: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42484b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424850: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424857u; native_call(m, m->ebp);	/* 424855: call ebp */
	m->edx = M32((DWORD)(0x4deb50u));	/* 424857: mov edx, dword ptr [0x4deb50] */
	m->eax = M32((DWORD)(0x4ddadcu));	/* 42485d: mov eax, dword ptr [0x4ddadc] */
	m->ecx = M32((DWORD)(0x4ddad8u));	/* 424862: mov ecx, dword ptr [0x4ddad8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424868: push edx */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424869: mov edx, dword ptr [0x4ddad4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42486f: push eax */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424870: mov eax, dword ptr [0x4ddad0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424875: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424876: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424877: push eax */
	m->esp -= 4; M32(m->esp) = 0x42487du; native_call(m, 0x427a90u);	/* 424878: call 0x427a90 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42487d: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424882: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424887: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42488c: push 0 */
	{ DWORD v_ = 0x9da480u; m->esp -= 4; M32(m->esp) = v_; }	/* 42488e: push 0x9da480 */
	m->esp -= 4; M32(m->esp) = 0x424898u; native_call(m, 0x41f0e0u);	/* 424893: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddadcu));	/* 424898: mov ecx, dword ptr [0x4ddadc] */
	m->edx = M32((DWORD)(0x4ddad8u));	/* 42489e: mov edx, dword ptr [0x4ddad8] */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 4248a4: mov eax, dword ptr [0x4ddad4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4248a9: add ecx, -0x20 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4248ac: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4248ae: push ecx */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 4248af: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xffffffe0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4248b5: add edx, -0x20 */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4248b8: add eax, 0x30 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4248bb: push edx */
	{ DWORD a_ = m->ecx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4248bc: add ecx, 0x20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4248bf: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4248c0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4248c6u; native_call(m, 0x427970u);	/* 4248c1: call 0x427970 */
	m->edx = M32((DWORD)(0x4de054u));	/* 4248c6: mov edx, dword ptr [0x4de054] */
	m->eax = M32((DWORD)(0x4de050u));	/* 4248cc: mov eax, dword ptr [0x4de050] */
	m->ecx = M32((DWORD)(0x4de04cu));	/* 4248d1: mov ecx, dword ptr [0x4de04c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4248d7: push edx */
	m->edx = M32((DWORD)(0x4de048u));	/* 4248d8: mov edx, dword ptr [0x4de048] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4248de: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4248df: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4248e0: push edx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4248e1: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4248ebu; native_call(m, 0x41f0e0u);	/* 4248e6: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 4248eb: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 4248f0: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4248f6: add esp, 0x50 */
	{ DWORD a_ = m->eax, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4248f9: add eax, 0x10 */
	{ DWORD a_ = m->ecx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4248fc: add ecx, 0x50 */
	{ DWORD v_ = 0x7533a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 4248ff: push 0x7533a4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424904: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424905: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42490bu; native_call(m, 0x4028b0u);	/* 424906: call 0x4028b0 */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 42490b: mov eax, dword ptr [0x9db0a4] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424910: add esp, 0xc */
	m->edx = m->eax;	/* 424913: mov edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 424915: and edx, 0x800001ff */
	if (!m->sf) goto L_424925;	/* 42491b: jns 0x424925 */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 42491d: dec edx */
	{ DWORD a_ = m->edx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42491e: or edx, 0xfffffe00 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 424924: inc edx */
L_424925:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424925: push edx */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 424926: mov ecx, dword ptr [0xa0e010] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 42492c: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 42492d: and edx, 0x1ff */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424933: add eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 424935: sar eax, 9 */
	m->ecx = M32((DWORD)(m->ecx + m->eax*4 + 0x4u));	/* 424938: mov ecx, dword ptr [ecx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x424941u; native_call(m, 0x4566c0u);	/* 42493c: call 0x4566c0 */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 424941: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x42494cu; native_call(m, M32(0x4a9224u));	/* 424946: call dword ptr [0x4a9224] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42494c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424951: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424956: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42495b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424962u; native_call(m, m->ebp);	/* 424960: call ebp */
	m->edi = M32((DWORD)(0x4a921cu));	/* 424962: mov edi, dword ptr [0x4a921c] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424968: push 7 */
	m->esp -= 4; M32(m->esp) = 0x42496cu; native_call(m, m->edi);	/* 42496a: call edi */
	m->esi = M32((DWORD)(0x4a920cu));	/* 42496c: mov esi, dword ptr [0x4a920c] */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424972: push 0x3e800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424977: push 0 */
	m->esp -= 4; M32(m->esp) = 0x42497bu; native_call(m, m->esi);	/* 424979: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 42497b: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424981: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424986: add edx, 0x50 */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424989: add eax, 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42498c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42498d: push eax */
	m->esp -= 4; M32(m->esp) = 0x424993u; native_call(m, 0x41ef60u);	/* 42498e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424993: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424996: push 0x3e800000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42499b: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x4249a2u; native_call(m, m->esi);	/* 4249a0: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 4249a2: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 4249a8: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4249ae: add ecx, 0x50 */
	{ DWORD a_ = m->edx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4249b1: add edx, 0x90 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4249b7: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4249b8: push edx */
	m->esp -= 4; M32(m->esp) = 0x4249beu; native_call(m, 0x41ef60u);	/* 4249b9: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4249be: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4249c1: push 0x3ec00000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4249c6: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x4249cdu; native_call(m, m->esi);	/* 4249cb: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 4249cd: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 4249d2: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4249d8: add eax, 0x70 */
	{ DWORD a_ = m->ecx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4249db: add ecx, 0x90 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4249e1: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4249e2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4249e8u; native_call(m, 0x41ef60u);	/* 4249e3: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4249e8: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4249eb: push 0x3ec00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4249f0: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4249f4u; native_call(m, m->esi);	/* 4249f2: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 4249f4: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 4249fa: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4249ff: add edx, 0x70 */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424a02: add eax, 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424a05: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424a06: push eax */
	m->esp -= 4; M32(m->esp) = 0x424a0cu; native_call(m, 0x41ef60u);	/* 424a07: call 0x41ef60 */
	m->ebx = M32((DWORD)(0x4a9220u));	/* 424a0c: mov ebx, dword ptr [0x4a9220] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424a12: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x424a17u; native_call(m, m->ebx);	/* 424a15: call ebx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a17: push 7 */
	m->esp -= 4; M32(m->esp) = 0x424a1bu; native_call(m, m->edi);	/* 424a19: call edi */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a1b: push 0x3e800000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a20: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x424a27u; native_call(m, m->esi);	/* 424a25: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424a27: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424a2d: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424a33: add ecx, 0x50 */
	{ DWORD a_ = m->edx, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424a36: add edx, 0x190 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424a3c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424a3d: push edx */
	m->esp -= 4; M32(m->esp) = 0x424a43u; native_call(m, 0x41ef60u);	/* 424a3e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424a43: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a46: push 0x3e800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a4b: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x424a52u; native_call(m, m->esi);	/* 424a50: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424a52: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424a57: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424a5d: add eax, 0x50 */
	{ DWORD a_ = m->ecx, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424a60: add ecx, 0x1d0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424a66: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424a67: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424a6du; native_call(m, 0x41ef60u);	/* 424a68: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424a6d: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a70: push 0x3ec00000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a75: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x424a7cu; native_call(m, m->esi);	/* 424a7a: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424a7c: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424a82: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424a87: add edx, 0x70 */
	{ DWORD a_ = m->eax, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424a8a: add eax, 0x1d0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424a8f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424a90: push eax */
	m->esp -= 4; M32(m->esp) = 0x424a96u; native_call(m, 0x41ef60u);	/* 424a91: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424a96: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a99: push 0x3ec00000 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424a9e: push 0x3e800000 */
	m->esp -= 4; M32(m->esp) = 0x424aa5u; native_call(m, m->esi);	/* 424aa3: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424aa5: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424aab: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424ab1: add ecx, 0x70 */
	{ DWORD a_ = m->edx, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424ab4: add edx, 0x190 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424aba: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424abb: push edx */
	m->esp -= 4; M32(m->esp) = 0x424ac1u; native_call(m, 0x41ef60u);	/* 424abc: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424ac1: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x424ac6u; native_call(m, m->ebx);	/* 424ac4: call ebx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424ac6: push 7 */
	m->esp -= 4; M32(m->esp) = 0x424acau; native_call(m, m->edi);	/* 424ac8: call edi */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424aca: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424acc: push 0 */
	m->esp -= 4; M32(m->esp) = 0x424ad0u; native_call(m, m->esi);	/* 424ace: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424ad0: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424ad5: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424adb: add eax, 0x50 */
	{ DWORD a_ = m->ecx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424ade: add ecx, 0x90 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424ae4: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424ae5: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424aebu; native_call(m, 0x41ef60u);	/* 424ae6: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424aeb: add esp, 8 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424aee: push 0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424af0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424af7u; native_call(m, m->esi);	/* 424af5: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424af7: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424afd: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424b02: add edx, 0x50 */
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424b05: add eax, 0x190 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424b0a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424b0b: push eax */
	m->esp -= 4; M32(m->esp) = 0x424b11u; native_call(m, 0x41ef60u);	/* 424b0c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424b11: add esp, 8 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424b14: push 0x3e000000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424b19: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424b20u; native_call(m, m->esi);	/* 424b1e: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424b20: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424b26: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424b2c: add ecx, 0x70 */
	{ DWORD a_ = m->edx, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424b2f: add edx, 0x190 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424b35: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424b36: push edx */
	m->esp -= 4; M32(m->esp) = 0x424b3cu; native_call(m, 0x41ef60u);	/* 424b37: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424b3c: add esp, 8 */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424b3f: push 0x3e000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424b44: push 0 */
	m->esp -= 4; M32(m->esp) = 0x424b48u; native_call(m, m->esi);	/* 424b46: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424b48: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424b4d: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424b53: add eax, 0x70 */
	{ DWORD a_ = m->ecx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424b56: add ecx, 0x90 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424b5c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424b5d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424b63u; native_call(m, 0x41ef60u);	/* 424b5e: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424b63: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x424b68u; native_call(m, m->ebx);	/* 424b66: call ebx */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424b68: push 7 */
	m->esp -= 4; M32(m->esp) = 0x424b6cu; native_call(m, m->edi);	/* 424b6a: call edi */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424b6c: push 0x3e000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424b71: push 0 */
	m->esp -= 4; M32(m->esp) = 0x424b75u; native_call(m, m->esi);	/* 424b73: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424b75: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424b7b: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424b80: add edx, 0x50 */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424b83: add eax, 0x90 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424b88: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424b89: push eax */
	m->esp -= 4; M32(m->esp) = 0x424b8fu; native_call(m, 0x41ef60u);	/* 424b8a: call 0x41ef60 */
	FPUSH((long double)(int)M32((DWORD)(0x4dde98u)));	/* 424b8f: fild dword ptr [0x4dde98] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424b95: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 424b98: fmul dword ptr [0x4a9504] */
	{ DWORD v_ = 0x3e000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424b9e: push 0x3e000000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424ba3: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424ba4: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x424ba9u; native_call(m, m->esi);	/* 424ba7: call esi */
	FPUSH((long double)(int)M32((DWORD)(0x4dde98u)));	/* 424ba9: fild dword ptr [0x4dde98] */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424baf: mov ecx, dword ptr [0x4ddad4] */
	{ DWORD a_ = m->ecx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424bb5: add ecx, 0x50 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9500u));	/* 424bb8: fmul dword ptr [0x4a9500] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424bbe: push ecx */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 424bbf: call 0x49ec14 */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424bc4: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424bca: sub edx, eax */
	{ DWORD a_ = m->edx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424bcc: add edx, 0x90 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424bd2: push edx */
	m->esp -= 4; M32(m->esp) = 0x424bd8u; native_call(m, 0x41ef60u);	/* 424bd3: call 0x41ef60 */
	FPUSH((long double)(int)M32((DWORD)(0x4dde98u)));	/* 424bd8: fild dword ptr [0x4dde98] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424bde: add esp, 8 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9504u));	/* 424be1: fmul dword ptr [0x4a9504] */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424be7: push 0x3e800000 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424bec: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 424bed: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x424bf2u; native_call(m, m->esi);	/* 424bf0: call esi */
	FPUSH((long double)(int)M32((DWORD)(0x4dde98u)));	/* 424bf2: fild dword ptr [0x4dde98] */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424bf8: mov eax, dword ptr [0x4ddad4] */
	{ DWORD a_ = m->eax, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424bfd: add eax, 0x70 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9500u));	/* 424c00: fmul dword ptr [0x4a9500] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424c06: push eax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 424c07: call 0x49ec14 */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424c0c: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424c12: sub ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424c14: add ecx, 0x90 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424c1a: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424c20u; native_call(m, 0x41ef60u);	/* 424c1b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424c20: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424c23: push 0x3e800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 424c28: push 0 */
	m->esp -= 4; M32(m->esp) = 0x424c2cu; native_call(m, m->esi);	/* 424c2a: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424c2c: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424c32: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424c37: add edx, 0x70 */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424c3a: add eax, 0x90 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424c3f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424c40: push eax */
	m->esp -= 4; M32(m->esp) = 0x424c46u; native_call(m, 0x41ef60u);	/* 424c41: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424c46: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x424c4bu; native_call(m, m->ebx);	/* 424c49: call ebx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ddb98u)));	/* 424c4b: fld dword ptr [0x4ddb98] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 424c51: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 424c57: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 424c59: test ah, 0x41 */
	if (!m->zf) goto L_424f5f;	/* 424c5c: jne 0x424f5f */
	m->eax = M32((DWORD)(0x4dde90u));	/* 424c62: mov eax, dword ptr [0x4dde90] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 424c67: cmp eax, 3 */
	if (!m->cf && !m->zf) goto L_424f2c;	/* 424c6a: ja 0x424f2c */
	switch (m->eax) { case 0: goto L_424c77; case 1: goto L_424d1a; case 2: goto L_424dc3; case 3: goto L_424e72; default: abort(); }	/* 424c70: jmp dword ptr [eax*4 + 0x425444] */
L_424c77:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424c77: push 7 */
	m->esp -= 4; M32(m->esp) = 0x424c7bu; native_call(m, m->edi);	/* 424c79: call edi */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424c7b: push 0x3e800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424c80: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x424c87u; native_call(m, m->esi);	/* 424c85: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424c87: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424c8d: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424c93: add ecx, 0x50 */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424c96: add edx, 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424c99: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424c9a: push edx */
	m->esp -= 4; M32(m->esp) = 0x424ca0u; native_call(m, 0x41ef60u);	/* 424c9b: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424ca0: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424ca3: push 0x3e800000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424ca8: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x424cafu; native_call(m, m->esi);	/* 424cad: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424caf: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424cb4: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424cba: add eax, 0x50 */
	{ DWORD a_ = m->ecx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424cbd: add ecx, 0x90 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424cc3: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424cc4: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424ccau; native_call(m, 0x41ef60u);	/* 424cc5: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424cca: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424ccd: push 0x3ec00000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424cd2: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x424cd9u; native_call(m, m->esi);	/* 424cd7: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424cd9: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424cdf: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424ce4: add edx, 0x70 */
	{ DWORD a_ = m->eax, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424ce7: add eax, 0x90 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424cec: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424ced: push eax */
	m->esp -= 4; M32(m->esp) = 0x424cf3u; native_call(m, 0x41ef60u);	/* 424cee: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424cf3: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424cf6: push 0x3ec00000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424cfb: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x424d02u; native_call(m, m->esi);	/* 424d00: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424d02: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424d08: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424d0e: add ecx, 0x70 */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424d11: add edx, 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424d14: push ecx */
	goto L_424f21;	/* 424d15: jmp 0x424f21 */
L_424d1a:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424d1a: push 7 */
	m->esp -= 4; M32(m->esp) = 0x424d1eu; native_call(m, m->edi);	/* 424d1c: call edi */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424d1e: push 0x3e800000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424d23: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x424d2au; native_call(m, m->esi);	/* 424d28: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424d2a: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424d2f: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424d35: add eax, 0x50 */
	{ DWORD a_ = m->ecx, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424d38: add ecx, 0x190 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424d3e: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424d3f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424d45u; native_call(m, 0x41ef60u);	/* 424d40: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424d45: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424d48: push 0x3e800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424d4d: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424d54u; native_call(m, m->esi);	/* 424d52: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424d54: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424d5a: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424d5f: add edx, 0x50 */
	{ DWORD a_ = m->eax, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424d62: add eax, 0x1d0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424d67: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424d68: push eax */
	m->esp -= 4; M32(m->esp) = 0x424d6eu; native_call(m, 0x41ef60u);	/* 424d69: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424d6e: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424d71: push 0x3ec00000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424d76: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424d7du; native_call(m, m->esi);	/* 424d7b: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424d7d: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424d83: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424d89: add ecx, 0x70 */
	{ DWORD a_ = m->edx, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424d8c: add edx, 0x1d0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424d92: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424d93: push edx */
	m->esp -= 4; M32(m->esp) = 0x424d99u; native_call(m, 0x41ef60u);	/* 424d94: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424d99: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424d9c: push 0x3ec00000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424da1: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x424da8u; native_call(m, m->esi);	/* 424da6: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424da8: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424dad: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x70u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424db3: add eax, 0x70 */
	{ DWORD a_ = m->ecx, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424db6: add ecx, 0x190 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424dbc: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424dbd: push ecx */
	goto L_424f22;	/* 424dbe: jmp 0x424f22 */
L_424dc3:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424dc3: push 7 */
	m->esp -= 4; M32(m->esp) = 0x424dc7u; native_call(m, m->edi);	/* 424dc5: call edi */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424dc7: push 0x3e800000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424dcc: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x424dd3u; native_call(m, m->esi);	/* 424dd1: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424dd3: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424dd9: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424dde: add edx, 0x8c */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424de4: add eax, 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424de7: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424de8: push eax */
	m->esp -= 4; M32(m->esp) = 0x424deeu; native_call(m, 0x41ef60u);	/* 424de9: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424dee: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424df1: push 0x3e800000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424df6: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x424dfdu; native_call(m, m->esi);	/* 424dfb: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424dfd: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424e03: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424e09: add ecx, 0x8c */
	{ DWORD a_ = m->edx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424e0f: add edx, 0x90 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424e15: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424e16: push edx */
	m->esp -= 4; M32(m->esp) = 0x424e1cu; native_call(m, 0x41ef60u);	/* 424e17: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424e1c: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424e1f: push 0x3ec00000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424e24: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x424e2bu; native_call(m, m->esi);	/* 424e29: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424e2b: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424e30: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0xacu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424e36: add eax, 0xac */
	{ DWORD a_ = m->ecx, b_ = 0x90u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424e3b: add ecx, 0x90 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424e41: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424e42: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424e48u; native_call(m, 0x41ef60u);	/* 424e43: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424e48: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424e4b: push 0x3ec00000 */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424e50: push 0x3f000000 */
	m->esp -= 4; M32(m->esp) = 0x424e57u; native_call(m, m->esi);	/* 424e55: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424e57: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424e5d: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xacu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424e62: add edx, 0xac */
	{ DWORD a_ = m->eax, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424e68: add eax, 0x50 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424e6b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424e6c: push eax */
	goto L_424f22;	/* 424e6d: jmp 0x424f22 */
L_424e72:
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 424e72: push 7 */
	m->esp -= 4; M32(m->esp) = 0x424e76u; native_call(m, m->edi);	/* 424e74: call edi */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424e76: push 0x3e800000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424e7b: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x424e82u; native_call(m, m->esi);	/* 424e80: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424e82: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424e88: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424e8e: add ecx, 0x8c */
	{ DWORD a_ = m->edx, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424e94: add edx, 0x190 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424e9a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424e9b: push edx */
	m->esp -= 4; M32(m->esp) = 0x424ea1u; native_call(m, 0x41ef60u);	/* 424e9c: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424ea1: add esp, 8 */
	{ DWORD v_ = 0x3e800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424ea4: push 0x3e800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424ea9: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424eb0u; native_call(m, m->esi);	/* 424eae: call esi */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424eb0: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 424eb5: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424ebb: add eax, 0x8c */
	{ DWORD a_ = m->ecx, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424ec0: add ecx, 0x1d0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424ec6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424ec7: push ecx */
	m->esp -= 4; M32(m->esp) = 0x424ecdu; native_call(m, 0x41ef60u);	/* 424ec8: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424ecd: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424ed0: push 0x3ec00000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424ed5: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x424edcu; native_call(m, m->esi);	/* 424eda: call esi */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 424edc: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 424ee2: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xacu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424ee7: add edx, 0xac */
	{ DWORD a_ = m->eax, b_ = 0x1d0u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 424eed: add eax, 0x1d0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424ef2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424ef3: push eax */
	m->esp -= 4; M32(m->esp) = 0x424ef9u; native_call(m, 0x41ef60u);	/* 424ef4: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424ef9: add esp, 8 */
	{ DWORD v_ = 0x3ec00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424efc: push 0x3ec00000 */
	{ DWORD v_ = 0x3f400000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424f01: push 0x3f400000 */
	m->esp -= 4; M32(m->esp) = 0x424f08u; native_call(m, m->esi);	/* 424f06: call esi */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424f08: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424f0e: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0xacu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424f14: add ecx, 0xac */
	{ DWORD a_ = m->edx, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424f1a: add edx, 0x190 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424f20: push ecx */
L_424f21:
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424f21: push edx */
L_424f22:
	m->esp -= 4; M32(m->esp) = 0x424f27u; native_call(m, 0x41ef60u);	/* 424f22: call 0x41ef60 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424f27: add esp, 8 */
	m->esp -= 4; M32(m->esp) = 0x424f2cu; native_call(m, m->ebx);	/* 424f2a: call ebx */
L_424f2c:
	FPUSH(x87_ldm((const float *)(DWORD)(0x4ddb98u)));	/* 424f2c: fld dword ptr [0x4ddb98] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 424f32: fsub dword ptr [0x4b071c] */
	MF((DWORD)(0x4ddb98u)) = (float)ST(0);	/* 424f38: fst dword ptr [0x4ddb98] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 424f3e: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 424f44: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 424f46: test ah, 1 */
	if (m->zf) goto L_424f5f;	/* 424f49: je 0x424f5f */
	M32((DWORD)(0x4ddb98u)) = 0x0u;	/* 424f4b: mov dword ptr [0x4ddb98], 0 */
	M32((DWORD)(0x4dde90u)) = 0xffffffffu;	/* 424f55: mov dword ptr [0x4dde90], 0xffffffff */
L_424f5f:
	m->eax = M32((DWORD)(0x4de054u));	/* 424f5f: mov eax, dword ptr [0x4de054] */
	m->ecx = M32((DWORD)(0x4de050u));	/* 424f64: mov ecx, dword ptr [0x4de050] */
	m->edx = M32((DWORD)(0x4de04cu));	/* 424f6a: mov edx, dword ptr [0x4de04c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424f70: push eax */
	m->eax = M32((DWORD)(0x4de048u));	/* 424f71: mov eax, dword ptr [0x4de048] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424f76: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424f77: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 424f78: push eax */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 424f79: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x424f83u; native_call(m, 0x41f0e0u);	/* 424f7e: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 424f83: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424f89: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->ecx, b_ = 0x3cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 424f8f: add ecx, 0x3c */
	{ DWORD v_ = 0x753424u; m->esp -= 4; M32(m->esp) = v_; }	/* 424f92: push 0x753424 */
	{ DWORD a_ = m->edx, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424f97: add edx, 0x50 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424f9a: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424f9b: push edx */
	m->esp -= 4; M32(m->esp) = 0x424fa1u; native_call(m, 0x4028b0u);	/* 424f9c: call 0x4028b0 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424fa1: add esp, 0x20 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 424fa4: xor edi, edi */
	m->esi = 0x7534a4u;	/* 424fa6: mov esi, 0x7534a4 */
L_424fab:
	m->eax = M32((DWORD)(0x4ddad4u));	/* 424fab: mov eax, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 424fb0: mov edx, dword ptr [0x4ddad0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 424fb6: push esi */
	{ DWORD a_ = m->edx, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 424fb7: add edx, 0x8c */
	m->ecx = (DWORD)(m->edi + m->eax*1 + 0x9cu);	/* 424fbd: lea ecx, [edi + eax + 0x9c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 424fc4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 424fc5: push edx */
	m->esp -= 4; M32(m->esp) = 0x424fcbu; native_call(m, 0x402620u);	/* 424fc6: call 0x402620 */
	{ DWORD a_ = m->esi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 424fcb: add esi, 0x80 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 424fd1: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 424fd4: add edi, 0x28 */
	{ DWORD a_ = m->esi, b_ = 0x753624u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 424fd7: cmp esi, 0x753624 */
	if (m->sf != m->of) goto L_424fab;	/* 424fdd: jl 0x424fab */
	m->ecx = M32((DWORD)(0x4dde9cu));	/* 424fdf: mov ecx, dword ptr [0x4dde9c] */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 424fe5: mov edi, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 424fe9: xor eax, eax */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 424feb: push 0x3f800000 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 424ff0: test ecx, ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 424ff2: setg al */
	{ DWORD a_ = m->edi, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 424ff5: cmp edi, 5 */
	m->esi = m->eax;	/* 424ff8: mov esi, eax */
	if (!m->zf) goto L_425170;	/* 424ffa: jne 0x425170 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425000: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 425005: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 42500a: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 42500f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425019u; native_call(m, 0x41f0e0u);	/* 425014: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 425019: mov ecx, dword ptr [0x4ddad4] */
	m->edx = M32((DWORD)(0x4ddad0u));	/* 42501f: mov edx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->esi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 425025: shl esi, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x9eu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425028: add ecx, 0x9e */
	{ DWORD a_ = m->edx, b_ = 0x12du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42502e: add edx, 0x12d */
	m->esi = (DWORD)(m->esi + 0x753624u);	/* 425034: lea esi, [esi + 0x753624] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42503a: push esi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42503b: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42503c: push edx */
	m->esp -= 4; M32(m->esp) = 0x425042u; native_call(m, 0x402620u);	/* 42503d: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425042: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425047: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 425049: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42504e: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425053: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x42505du; native_call(m, 0x41f0e0u);	/* 425058: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddad4u));	/* 42505d: mov eax, dword ptr [0x4ddad4] */
	m->ecx = M32((DWORD)(0x4ddad0u));	/* 425062: mov ecx, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->eax, b_ = 0x9du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425068: add eax, 0x9d */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42506d: push esi */
	{ DWORD a_ = m->ecx, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42506e: add ecx, 0x12c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425074: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425075: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42507bu; native_call(m, 0x402620u);	/* 425076: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42507b: add esp, 0x40 */
L_42507e:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42507e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425083: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425088: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42508d: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425092: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x42509cu; native_call(m, 0x41f0e0u);	/* 425097: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddea0u));	/* 42509c: mov ecx, dword ptr [0x4ddea0] */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 4250a2: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 4250a8: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xc4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4250ad: add edx, 0xc4 */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4250b3: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x753624u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4250b6: add ecx, 0x753624 */
	{ DWORD a_ = m->eax, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4250bc: add eax, 0x12c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4250c1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4250c2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4250c3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4250c9u; native_call(m, 0x402620u);	/* 4250c4: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4250c9: add esp, 0x20 */
	{ DWORD a_ = m->edi, b_ = 0x7u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4250cc: cmp edi, 7 */
	if (!m->zf) goto L_425252;	/* 4250cf: jne 0x425252 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4250d5: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4250da: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4250df: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4250e4: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4250e9: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4250f3u; native_call(m, 0x41f0e0u);	/* 4250ee: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddea4u));	/* 4250f3: mov ecx, dword ptr [0x4ddea4] */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 4250f9: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 4250ff: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xeeu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425104: add edx, 0xee */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 42510a: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x753624u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42510d: add ecx, 0x753624 */
	{ DWORD a_ = m->eax, b_ = 0x12du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425113: add eax, 0x12d */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425118: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425119: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42511a: push eax */
	m->esp -= 4; M32(m->esp) = 0x425120u; native_call(m, 0x402620u);	/* 42511b: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425120: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 425125: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 425127: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42512c: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425131: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x42513bu; native_call(m, 0x41f0e0u);	/* 425136: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddea4u));	/* 42513b: mov ecx, dword ptr [0x4ddea4] */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 425141: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 425147: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xedu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42514c: add edx, 0xed */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 425152: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x753624u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 425155: add ecx, 0x753624 */
	{ DWORD a_ = m->eax, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 42515b: add eax, 0x12c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425160: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425161: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425162: push eax */
	m->esp -= 4; M32(m->esp) = 0x425168u; native_call(m, 0x402620u);	/* 425163: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 425168: add esp, 0x40 */
	goto L_4252a0;	/* 42516b: jmp 0x4252a0 */
L_425170:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425170: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425175: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42517a: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 42517f: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425189u; native_call(m, 0x41f0e0u);	/* 425184: call 0x41f0e0 */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 425189: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 42518f: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->esi, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->esi = r_; } }	/* 425194: shl esi, 7 */
	{ DWORD a_ = m->esi, b_ = 0x753624u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 425197: add esi, 0x753624 */
	{ DWORD a_ = m->edx, b_ = 0x9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 42519d: add edx, 0x9c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4251a3: push esi */
	{ DWORD a_ = m->eax, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4251a4: add eax, 0x12c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4251a9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4251aa: push eax */
	m->esp -= 4; M32(m->esp) = 0x4251b0u; native_call(m, 0x402620u);	/* 4251ab: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4251b0: add esp, 0x20 */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4251b3: cmp edi, 6 */
	if (!m->zf) goto L_42507e;	/* 4251b6: jne 0x42507e */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4251bc: push 0x3f800000 */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4251c1: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4251c6: push 0x3c23d70a */
	{ DWORD v_ = 0x3c23d70au; m->esp -= 4; M32(m->esp) = v_; }	/* 4251cb: push 0x3c23d70a */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4251d0: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4251dau; native_call(m, 0x41f0e0u);	/* 4251d5: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddea0u));	/* 4251da: mov ecx, dword ptr [0x4ddea0] */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 4251e0: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 4251e6: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xc6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4251eb: add edx, 0xc6 */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4251f1: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x753624u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4251f4: add ecx, 0x753624 */
	{ DWORD a_ = m->eax, b_ = 0x12du & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4251fa: add eax, 0x12d */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4251ff: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425200: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425201: push eax */
	m->esp -= 4; M32(m->esp) = 0x425207u; native_call(m, 0x402620u);	/* 425202: call 0x402620 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425207: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42520c: push 0 */
	{ DWORD v_ = 0x3f4ccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 42520e: push 0x3f4ccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425213: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425218: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425222u; native_call(m, 0x41f0e0u);	/* 42521d: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddea0u));	/* 425222: mov ecx, dword ptr [0x4ddea0] */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 425228: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 42522e: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xc5u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425233: add edx, 0xc5 */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 425239: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x753624u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42523c: add ecx, 0x753624 */
	{ DWORD a_ = m->eax, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425242: add eax, 0x12c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425247: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425248: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425249: push eax */
	m->esp -= 4; M32(m->esp) = 0x42524fu; native_call(m, 0x402620u);	/* 42524a: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42524f: add esp, 0x40 */
L_425252:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425252: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425257: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42525c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425261: push 0x3f800000 */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 425266: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x425270u; native_call(m, 0x41f0e0u);	/* 42526b: call 0x41f0e0 */
	m->ecx = M32((DWORD)(0x4ddea4u));	/* 425270: mov ecx, dword ptr [0x4ddea4] */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 425276: mov edx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 42527c: mov eax, dword ptr [0x4ddad0] */
	{ DWORD a_ = m->edx, b_ = 0xecu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 425281: add edx, 0xec */
	{ DWORD a_ = m->ecx, c_ = (0x7u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 425287: shl ecx, 7 */
	{ DWORD a_ = m->ecx, b_ = 0x753624u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42528a: add ecx, 0x753624 */
	{ DWORD a_ = m->eax, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 425290: add eax, 0x12c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425295: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425296: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425297: push eax */
	m->esp -= 4; M32(m->esp) = 0x42529du; native_call(m, 0x402620u);	/* 425298: call 0x402620 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42529d: add esp, 0x20 */
L_4252a0:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 4252a0: xor ebx, ebx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4252a2: xor esi, esi */
	m->edi = 0x753724u;	/* 4252a4: mov edi, 0x753724 */
L_4252a9:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4252a9: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4252b4u; native_call(m, M32(0x4a9224u));	/* 4252ae: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(0x9db0a4u));	/* 4252b4: mov eax, dword ptr [0x9db0a4] */
	m->ecx = m->eax;	/* 4252b9: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4252bb: and ecx, 0x800001ff */
	if (!m->sf) goto L_4252cb;	/* 4252c1: jns 0x4252cb */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4252c3: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4252c4: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 4252ca: inc ecx */
L_4252cb:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4252cb: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4252cc: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4252d2: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4252d3: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 4252d5: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4252db: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 4252de: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4252e7u; native_call(m, 0x4566c0u);	/* 4252e2: call 0x4566c0 */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 4252e7: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->ebx + 0x8u);	/* 4252eb: lea eax, [ebx + 8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4252ee: cmp ecx, eax */
	if (!m->zf) goto L_425354;	/* 4252f0: jne 0x425354 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4252f2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4252f7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4252fc: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425301: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x425308u; native_call(m, m->ebp);	/* 425306: call ebp */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 425308: mov ecx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 42530e: mov eax, dword ptr [0x4ddad0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 425313: push 1 */
	m->edx = (DWORD)(m->ecx + 0x133u);	/* 425315: lea edx, [ecx + 0x133] */
	{ DWORD a_ = m->ecx, b_ = 0x113u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42531b: add ecx, 0x113 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425321: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x108u);	/* 425322: lea edx, [esi + eax + 0x108] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425329: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x90u);	/* 42532a: lea eax, [esi + eax + 0x90] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425331: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425332: push eax */
	m->esp -= 4; M32(m->esp) = 0x425338u; native_call(m, 0x4282f0u);	/* 425333: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4de054u));	/* 425338: mov ecx, dword ptr [0x4de054] */
	m->edx = M32((DWORD)(0x4de050u));	/* 42533e: mov edx, dword ptr [0x4de050] */
	m->eax = M32((DWORD)(0x4de04cu));	/* 425344: mov eax, dword ptr [0x4de04c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425349: push ecx */
	m->ecx = M32((DWORD)(0x4de048u));	/* 42534a: mov ecx, dword ptr [0x4de048] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425350: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425351: push eax */
	goto L_4253b4;	/* 425352: jmp 0x4253b4 */
L_425354:
	{ DWORD v_ = 0x3ecccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 425354: push 0x3ecccccd */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425359: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42535e: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425363: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42536au; native_call(m, m->ebp);	/* 425368: call ebp */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 42536a: mov ecx, dword ptr [0x4ddad4] */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 425370: mov eax, dword ptr [0x4ddad0] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 425375: push 1 */
	m->edx = (DWORD)(m->ecx + 0x133u);	/* 425377: lea edx, [ecx + 0x133] */
	{ DWORD a_ = m->ecx, b_ = 0x113u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 42537d: add ecx, 0x113 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425383: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x108u);	/* 425384: lea edx, [esi + eax + 0x108] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42538b: push edx */
	m->eax = (DWORD)(m->esi + m->eax*1 + 0x90u);	/* 42538c: lea eax, [esi + eax + 0x90] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425393: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425394: push eax */
	m->esp -= 4; M32(m->esp) = 0x42539au; native_call(m, 0x4282f0u);	/* 425395: call 0x4282f0 */
	m->ecx = M32((DWORD)(0x4ddaecu));	/* 42539a: mov ecx, dword ptr [0x4ddaec] */
	m->edx = M32((DWORD)(0x4ddae8u));	/* 4253a0: mov edx, dword ptr [0x4ddae8] */
	m->eax = M32((DWORD)(0x4ddae4u));	/* 4253a6: mov eax, dword ptr [0x4ddae4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4253ab: push ecx */
	m->ecx = M32((DWORD)(0x4ddae0u));	/* 4253ac: mov ecx, dword ptr [0x4ddae0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4253b2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4253b3: push eax */
L_4253b4:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4253b4: push ecx */
	{ DWORD v_ = 0x76d438u; m->esp -= 4; M32(m->esp) = v_; }	/* 4253b5: push 0x76d438 */
	m->esp -= 4; M32(m->esp) = 0x4253bfu; native_call(m, 0x41f0e0u);	/* 4253ba: call 0x41f0e0 */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 4253bf: mov eax, dword ptr [0x4ddad0] */
	m->ecx = M32((DWORD)(0x4ddad4u));	/* 4253c4: mov ecx, dword ptr [0x4ddad4] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4253ca: add esp, 0x28 */
	{ DWORD a_ = m->ecx, b_ = 0x11bu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4253cd: add ecx, 0x11b */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x108u);	/* 4253d3: lea edx, [esi + eax + 0x108] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4253da: push edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4253db: push edx */
	m->edx = (DWORD)(m->esi + m->eax*1 + 0x90u);	/* 4253dc: lea edx, [esi + eax + 0x90] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4253e3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4253e4: push edx */
	m->esp -= 4; M32(m->esp) = 0x4253eau; native_call(m, 0x4029d0u);	/* 4253e5: call 0x4029d0 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4253ea: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4253ed: add edi, 0x80 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4253f3: inc ebx */
	{ DWORD a_ = m->esi, b_ = 0x8cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4253f4: add esi, 0x8c */
	{ DWORD a_ = m->edi, b_ = 0x753824u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4253fa: cmp edi, 0x753824 */
	if (m->sf != m->of) goto L_4252a9;	/* 425400: jl 0x4252a9 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425406: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 42540b: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425410: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 425415: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x42541cu; native_call(m, m->ebp);	/* 42541a: call ebp */
	m->eax = M32((DWORD)(0x4ddadcu));	/* 42541c: mov eax, dword ptr [0x4ddadc] */
	m->ecx = M32((DWORD)(0x4ddad8u));	/* 425421: mov ecx, dword ptr [0x4ddad8] */
	m->edx = M32((DWORD)(0x4ddad4u));	/* 425427: mov edx, dword ptr [0x4ddad4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42542d: push eax */
	m->eax = M32((DWORD)(0x4ddad0u));	/* 42542e: mov eax, dword ptr [0x4ddad0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 425433: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 425434: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 425435: push eax */
	m->esp -= 4; M32(m->esp) = 0x42543bu; native_call(m, 0x428a00u);	/* 425436: call 0x428a00 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42543b: add esp, 0x10 */
	m->edi = M32(m->esp); m->esp += 4;	/* 42543e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 42543f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 425440: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 425441: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 425442: pop ecx */
	m->esp += 4 + 0; return;	/* 425443: ret  */
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
