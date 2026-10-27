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

static void lift_44c850(X86 *m);
static void lift_44c8c0(X86 *m);
static void lift_44ca90(X86 *m);
static void lift_44cc60(X86 *m);
static void lift_44c600(X86 *m);

/* profile_44c600 (0x44c600), lifted by tools/lift.py */
static void lift_44c600(X86 *m)
{
	m->eax = M32((DWORD)(0x9db0a0u));	/* 44c600: mov eax, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c605: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c60bu; native_call(m, 0x401590u);	/* 44c606: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c60b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c60e: test eax, eax */
	if (!m->zf) goto L_44c617;	/* 44c610: jne 0x44c617 */
	M32((DWORD)(0x76d37cu)) = m->eax;	/* 44c612: mov dword ptr [0x76d37c], eax */
L_44c617:
	m->ecx = M32((DWORD)(0x9db0a0u));	/* 44c617: mov ecx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44c61d: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44c61e: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c61f: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c625u; native_call(m, 0x401590u);	/* 44c620: call 0x401590 */
	m->edi = 0x1u;	/* 44c625: mov edi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c62a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c62d: cmp eax, edi */
	if (!m->zf) goto L_44c6a9;	/* 44c62f: jne 0x44c6a9 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d37cu)));	/* 44c631: fld dword ptr [0x76d37c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 44c637: fcomp dword ptr [0x4a93e8] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c63d: mov dword ptr [0x4dda44], 0 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44c647: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44c649: test ah, 0x41 */
	if (!m->zf) goto L_44c663;	/* 44c64c: jne 0x44c663 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d37cu)));	/* 44c64e: fld dword ptr [0x76d37c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44c654: fsub dword ptr [0x4b071c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 44c65a: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44c65b: pop esi */
	MF((DWORD)(0x76d37cu)) = (float)ST(0); FPOP();	/* 44c65c: fstp dword ptr [0x76d37c] */
	m->esp += 4 + 0; return;	/* 44c662: ret  */
L_44c663:
	m->eax = M32((DWORD)(0x9f8c5cu));	/* 44c663: mov eax, dword ptr [0x9f8c5c] */
	M32((DWORD)(0x76d37cu)) = 0x40800000u;	/* 44c668: mov dword ptr [0x76d37c], 0x40800000 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c672: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_44c687;	/* 44c674: jle 0x44c687 */
	m->edx = M32((DWORD)(0x9f8c4cu));	/* 44c676: mov edx, dword ptr [0x9f8c4c] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44c67c: dec eax */
	M32((DWORD)(0x9f8c5cu)) = m->eax;	/* 44c67d: mov dword ptr [0x9f8c5c], eax */
	goto L_44c747;	/* 44c682: jmp 0x44c747 */
L_44c687:
	m->ecx = M32((DWORD)(0x9f8c4cu));	/* 44c687: mov ecx, dword ptr [0x9f8c4c] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c68d: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_44c83f;	/* 44c68f: jle 0x44c83f */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 44c695: dec ecx */
	M32((DWORD)(0x9f8c4cu)) = m->ecx;	/* 44c696: mov dword ptr [0x9f8c4c], ecx */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44c69c: add ecx, eax */
	M32((DWORD)(0x9f8d74u)) = m->ecx;	/* 44c69e: mov dword ptr [0x9f8d74], ecx */
	goto L_44c74f;	/* 44c6a4: jmp 0x44c74f */
L_44c6a9:
	m->eax = M32((DWORD)(0x76d330u));	/* 44c6a9: mov eax, dword ptr [0x76d330] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c6ae: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c6b4u; native_call(m, 0x401590u);	/* 44c6af: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c6b4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c6b7: test eax, eax */
	if (!m->zf) goto L_44c6c0;	/* 44c6b9: jne 0x44c6c0 */
	M32((DWORD)(0x680bb4u)) = m->eax;	/* 44c6bb: mov dword ptr [0x680bb4], eax */
L_44c6c0:
	m->ecx = M32((DWORD)(0x76d330u));	/* 44c6c0: mov ecx, dword ptr [0x76d330] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c6c6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c6ccu; native_call(m, 0x401590u);	/* 44c6c7: call 0x401590 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c6cc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c6cf: cmp eax, edi */
	if (!m->zf) goto L_44c773;	/* 44c6d1: jne 0x44c773 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bb4u)));	/* 44c6d7: fld dword ptr [0x680bb4] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 44c6dd: fcomp dword ptr [0x4a93e8] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c6e3: mov dword ptr [0x4dda44], 0 */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44c6ed: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44c6ef: test ah, 0x41 */
	if (!m->zf) goto L_44c709;	/* 44c6f2: jne 0x44c709 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680bb4u)));	/* 44c6f4: fld dword ptr [0x680bb4] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 44c6fa: fsub dword ptr [0x4b071c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 44c700: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44c701: pop esi */
	MF((DWORD)(0x680bb4u)) = (float)ST(0); FPOP();	/* 44c702: fstp dword ptr [0x680bb4] */
	m->esp += 4 + 0; return;	/* 44c708: ret  */
L_44c709:
	m->edx = M32((DWORD)(0x9f8c4cu));	/* 44c709: mov edx, dword ptr [0x9f8c4c] */
	m->eax = M32((DWORD)(0x9f8c5cu));	/* 44c70f: mov eax, dword ptr [0x9f8c5c] */
	m->esi = M32((DWORD)(0x9f9008u));	/* 44c714: mov esi, dword ptr [0x9f9008] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c71a: push ebx */
	m->ecx = (DWORD)(m->edx + m->eax*1 + 0x0u);	/* 44c71b: lea ecx, [edx + eax] */
	M32((DWORD)(0x680bb4u)) = 0x40800000u;	/* 44c71e: mov dword ptr [0x680bb4], 0x40800000 */
	m->ebx = (DWORD)(m->esi + 0xffffffffu);	/* 44c728: lea ebx, [esi - 1] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c72b: cmp ecx, ebx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 44c72d: pop ebx */
	if (m->sf == m->of) goto L_44c83f;	/* 44c72e: jge 0x44c83f */
	{ DWORD a_ = m->eax, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c734: cmp eax, 0xc */
	if (m->sf == m->of) goto L_44c762;	/* 44c737: jge 0x44c762 */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c739: cmp ecx, esi */
	if (m->sf == m->of) goto L_44c83f;	/* 44c73b: jge 0x44c83f */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44c741: inc eax */
	M32((DWORD)(0x9f8c5cu)) = m->eax;	/* 44c742: mov dword ptr [0x9f8c5c], eax */
L_44c747:
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44c747: add edx, eax */
	M32((DWORD)(0x9f8d74u)) = m->edx;	/* 44c749: mov dword ptr [0x9f8d74], edx */
L_44c74f:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c74f: push 2 */
	M32((DWORD)(0x9f8d68u)) = m->edi;	/* 44c751: mov dword ptr [0x9f8d68], edi */
	m->esp -= 4; M32(m->esp) = 0x44c75cu; native_call(m, 0x41e760u);	/* 44c757: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c75c: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44c75f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44c760: pop esi */
	m->esp += 4 + 0; return;	/* 44c761: ret  */
L_44c762:
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c762: cmp ecx, esi */
	if (m->sf == m->of) goto L_44c83f;	/* 44c764: jge 0x44c83f */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 44c76a: inc edx */
	M32((DWORD)(0x9f8c4cu)) = m->edx;	/* 44c76b: mov dword ptr [0x9f8c4c], edx */
	goto L_44c747;	/* 44c771: jmp 0x44c747 */
L_44c773:
	m->edx = M32((DWORD)(0x4e150cu));	/* 44c773: mov edx, dword ptr [0x4e150c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c779: push edx */
	m->esp -= 4; M32(m->esp) = 0x44c77fu; native_call(m, 0x401600u);	/* 44c77a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c77f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c782: cmp eax, edi */
	if (!m->zf) goto L_44c7a2;	/* 44c784: jne 0x44c7a2 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c786: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c78du; native_call(m, 0x41e760u);	/* 44c788: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c78d: add esp, 4 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c790: mov dword ptr [0x4dda44], 0 */
L_44c79a:
	m->esp -= 4; M32(m->esp) = 0x44c79fu; native_call(m, 0x44b600u);	/* 44c79a: call 0x44b600 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44c79f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44c7a0: pop esi */
	m->esp += 4 + 0; return;	/* 44c7a1: ret  */
L_44c7a2:
	m->eax = M32((DWORD)(0x4e0ce0u));	/* 44c7a2: mov eax, dword ptr [0x4e0ce0] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c7a7: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c7adu; native_call(m, 0x401600u);	/* 44c7a8: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c7ad: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c7b0: cmp eax, edi */
	if (m->zf) goto L_44c7c7;	/* 44c7b2: je 0x44c7c7 */
	m->ecx = M32((DWORD)(0x76d414u));	/* 44c7b4: mov ecx, dword ptr [0x76d414] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c7ba: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c7c0u; native_call(m, 0x401600u);	/* 44c7bb: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c7c0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c7c3: cmp eax, edi */
	if (!m->zf) goto L_44c7d5;	/* 44c7c5: jne 0x44c7d5 */
L_44c7c7:
	m->eax = M32((DWORD)(0x9f9008u));	/* 44c7c7: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c7cc: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_44c7d5;	/* 44c7ce: jle 0x44c7d5 */
	m->esp -= 4; M32(m->esp) = 0x44c7d5u; native_call(m, 0x44b670u);	/* 44c7d0: call 0x44b670 */
L_44c7d5:
	m->edx = M32((DWORD)(0x4e14f4u));	/* 44c7d5: mov edx, dword ptr [0x4e14f4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c7db: push edx */
	m->esp -= 4; M32(m->esp) = 0x44c7e1u; native_call(m, 0x401600u);	/* 44c7dc: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c7e1: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c7e4: cmp eax, edi */
	if (!m->zf) goto L_44c815;	/* 44c7e6: jne 0x44c815 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c7e8: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c7efu; native_call(m, 0x41e760u);	/* 44c7ea: call 0x41e760 */
	m->eax = M32((DWORD)(0x9f9008u));	/* 44c7ef: mov eax, dword ptr [0x9f9008] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c7f4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c7f7: test eax, eax */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c7f9: mov dword ptr [0x4dda44], 0 */
	if (m->zf || m->sf != m->of) goto L_44c79a;	/* 44c803: jle 0x44c79a */
	M32((DWORD)(0x9f6840u)) = m->edi;	/* 44c805: mov dword ptr [0x9f6840], edi */
	M32((DWORD)(0x9f8f10u)) = 0x4u;	/* 44c80b: mov dword ptr [0x9f8f10], 4 */
L_44c815:
	m->eax = M32((DWORD)(0x4e1510u));	/* 44c815: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c81a: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c820u; native_call(m, 0x401600u);	/* 44c81b: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c820: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c823: cmp eax, edi */
	if (m->zf) goto L_44c83a;	/* 44c825: je 0x44c83a */
	m->ecx = M32((DWORD)(0x76d48cu));	/* 44c827: mov ecx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c82d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c833u; native_call(m, 0x401600u);	/* 44c82e: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c833: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c836: test eax, eax */
	if (m->zf) goto L_44c83f;	/* 44c838: je 0x44c83f */
L_44c83a:
	m->esp -= 4; M32(m->esp) = 0x44c83fu; native_call(m, 0x44b6e0u);	/* 44c83a: call 0x44b6e0 */
L_44c83f:
	m->edi = M32(m->esp); m->esp += 4;	/* 44c83f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44c840: pop esi */
	m->esp += 4 + 0; return;	/* 44c841: ret  */
}

/* profile_44c850 (0x44c850), lifted by tools/lift.py */
static void lift_44c850(X86 *m)
{
	m->eax = M32((DWORD)(0x9f8f34u));	/* 44c850: mov eax, dword ptr [0x9f8f34] */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c855: mov dword ptr [0x4dda44], 0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c85f: test eax, eax */
	if (m->zf) goto L_44c8b2;	/* 44c861: je 0x44c8b2 */
	m->eax = M32((DWORD)(0x9dae70u));	/* 44c863: mov eax, dword ptr [0x9dae70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c868: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c86eu; native_call(m, 0x401600u);	/* 44c869: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c86e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c871: cmp eax, 1 */
	if (!m->zf) goto L_44c88a;	/* 44c874: jne 0x44c88a */
	M32((DWORD)(0x9f8f34u)) = 0x0u;	/* 44c876: mov dword ptr [0x9f8f34], 0 */
	M32((DWORD)(0x68039cu)) = m->eax;	/* 44c880: mov dword ptr [0x68039c], eax */
	m->esp -= 4; M32(m->esp) = 0x44c88au; native_call(m, 0x44b600u);	/* 44c885: call 0x44b600 */
L_44c88a:
	m->ecx = M32((DWORD)(0x4e1510u));	/* 44c88a: mov ecx, dword ptr [0x4e1510] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c890: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c896u; native_call(m, 0x401600u);	/* 44c891: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c896: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c899: cmp eax, 1 */
	if (!m->zf) goto L_44c8b2;	/* 44c89c: jne 0x44c8b2 */
	M32((DWORD)(0x9f8f34u)) = 0x0u;	/* 44c89e: mov dword ptr [0x9f8f34], 0 */
	M32((DWORD)(0x68039cu)) = m->eax;	/* 44c8a8: mov dword ptr [0x68039c], eax */
	native_call(m, 0x44b600u); return;	/* 44c8ad: jmp 0x44b600 */
L_44c8b2:
	m->esp += 4 + 0; return;	/* 44c8b2: ret  */
}

/* profile_44c8c0 (0x44c8c0), lifted by tools/lift.py */
static void lift_44c8c0(X86 *m)
{
	m->eax = M32((DWORD)(0x4e1510u));	/* 44c8c0: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44c8c5: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c8c6: push eax */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44c8c7: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x44c8d6u; native_call(m, 0x401600u);	/* 44c8d1: call 0x401600 */
	m->esi = 0x1u;	/* 44c8d6: mov esi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c8db: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c8de: cmp eax, esi */
	if (!m->zf) goto L_44c8f9;	/* 44c8e0: jne 0x44c8f9 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c8e2: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c8e9u; native_call(m, 0x41e760u);	/* 44c8e4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c8e9: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44c8f1u; native_call(m, 0x44ba60u);	/* 44c8ec: call 0x44ba60 */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44c8f1: mov dword ptr [0x9f8f10], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44c8f7: pop esi */
	m->esp += 4 + 0; return;	/* 44c8f8: ret  */
L_44c8f9:
	m->ecx = M32((DWORD)(0x9dae70u));	/* 44c8f9: mov ecx, dword ptr [0x9dae70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c8ff: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c905u; native_call(m, 0x401600u);	/* 44c900: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c905: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c908: cmp eax, esi */
	if (!m->zf) goto L_44c93f;	/* 44c90a: jne 0x44c93f */
	m->edx = M32((DWORD)(0x4ded6cu));	/* 44c90c: mov edx, dword ptr [0x4ded6c] */
	m->eax = M32((DWORD)(0x4ded68u));	/* 44c912: mov eax, dword ptr [0x4ded68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c917: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c918: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c91eu; native_call(m, 0x44b320u);	/* 44c919: call 0x44b320 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c91e: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c921: test eax, eax */
	if (!m->zf) goto L_44c93b;	/* 44c923: jne 0x44c93b */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c925: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c92bu; native_call(m, 0x41e760u);	/* 44c926: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c92b: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44c933u; native_call(m, 0x44ba60u);	/* 44c92e: call 0x44ba60 */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44c933: mov dword ptr [0x9f8f10], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44c939: pop esi */
	m->esp += 4 + 0; return;	/* 44c93a: ret  */
L_44c93b:
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c93b: cmp eax, esi */
	if (m->zf) goto L_44c965;	/* 44c93d: je 0x44c965 */
L_44c93f:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 44c93f: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c945: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44c94bu; native_call(m, 0x401600u);	/* 44c946: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c94b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c94e: cmp eax, esi */
	if (m->zf) goto L_44c965;	/* 44c950: je 0x44c965 */
	m->edx = M32((DWORD)(0x76d48cu));	/* 44c952: mov edx, dword ptr [0x76d48c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44c958: push edx */
	m->esp -= 4; M32(m->esp) = 0x44c95eu; native_call(m, 0x401600u);	/* 44c959: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c95e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c961: test eax, eax */
	if (m->zf) goto L_44c977;	/* 44c963: je 0x44c977 */
L_44c965:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44c965: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44c96cu; native_call(m, 0x41e760u);	/* 44c967: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c96c: add esp, 4 */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44c96f: mov dword ptr [0x9f8f10], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44c975: pop esi */
	m->esp += 4 + 0; return;	/* 44c976: ret  */
L_44c977:
	m->eax = M32((DWORD)(0x9db974u));	/* 44c977: mov eax, dword ptr [0x9db974] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c97c: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c982u; native_call(m, 0x401600u);	/* 44c97d: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c982: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c985: cmp eax, esi */
	if (!m->zf) goto L_44c9c0;	/* 44c987: jne 0x44c9c0 */
	m->eax = M32((DWORD)(0x74de1cu));	/* 44c989: mov eax, dword ptr [0x74de1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44c98e: test eax, eax */
	if (!m->zf) goto L_44c9c0;	/* 44c990: jne 0x44c9c0 */
	m->ecx = M32((DWORD)(0x9f8f1cu));	/* 44c992: mov ecx, dword ptr [0x9f8f1c] */
	M32((DWORD)(0x74de1cu)) = m->esi;	/* 44c998: mov dword ptr [0x74de1c], esi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 44c99e: mov dword ptr [0x76d42c], esi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 44c9a4: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 44c9ae: mov dword ptr [0x9da4a4], 0x3ecccccd */
	{ DWORD a_ = m->ecx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44c9b8: add ecx, 0x114 */
	goto L_44ca0a;	/* 44c9be: jmp 0x44ca0a */
L_44c9c0:
	m->eax = M32((DWORD)(0x9dae14u));	/* 44c9c0: mov eax, dword ptr [0x9dae14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44c9c5: push eax */
	m->esp -= 4; M32(m->esp) = 0x44c9cbu; native_call(m, 0x401600u);	/* 44c9c6: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44c9cb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c9ce: cmp eax, esi */
	if (!m->zf) goto L_44ca2b;	/* 44c9d0: jne 0x44ca2b */
	{ DWORD a_ = M32((DWORD)(0x74de1cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44c9d2: cmp dword ptr [0x74de1c], esi */
	if (!m->zf) goto L_44ca2b;	/* 44c9d8: jne 0x44ca2b */
L_44c9da:
	m->ecx = M32((DWORD)(0x9f8f1cu));	/* 44c9da: mov ecx, dword ptr [0x9f8f1c] */
	M32((DWORD)(0x74de1cu)) = 0x0u;	/* 44c9e0: mov dword ptr [0x74de1c], 0 */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 44c9ea: mov dword ptr [0x76d42c], esi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 44c9f0: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 44c9fa: mov dword ptr [0x9da4a4], 0x3ecccccd */
	{ DWORD a_ = m->ecx, b_ = 0x9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44ca04: add ecx, 0x9c */
L_44ca0a:
	m->edx = M32((DWORD)(0x9f8f0cu));	/* 44ca0a: mov edx, dword ptr [0x9f8f0c] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ca10: push 2 */
	{ DWORD a_ = m->edx, b_ = 0x4au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44ca12: add edx, 0x4a */
	M32((DWORD)(0x67ef34u)) = m->ecx;	/* 44ca15: mov dword ptr [0x67ef34], ecx */
	M32((DWORD)(0x67fb38u)) = m->edx;	/* 44ca1b: mov dword ptr [0x67fb38], edx */
	m->esp -= 4; M32(m->esp) = 0x44ca26u; native_call(m, 0x41e760u);	/* 44ca21: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ca26: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44ca29: pop esi */
	m->esp += 4 + 0; return;	/* 44ca2a: ret  */
L_44ca2b:
	m->eax = M32((DWORD)(0x680390u));	/* 44ca2b: mov eax, dword ptr [0x680390] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ca30: push eax */
	m->esp -= 4; M32(m->esp) = 0x44ca36u; native_call(m, 0x401600u);	/* 44ca31: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ca36: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ca39: cmp eax, esi */
	if (!m->zf) goto L_44ca8e;	/* 44ca3b: jne 0x44ca8e */
	m->eax = M32((DWORD)(0x74de1cu));	/* 44ca3d: mov eax, dword ptr [0x74de1c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44ca42: test eax, eax */
	if (!m->zf) goto L_44c9da;	/* 44ca44: jne 0x44c9da */
	m->eax = M32((DWORD)(0x9f8f1cu));	/* 44ca46: mov eax, dword ptr [0x9f8f1c] */
	m->ecx = M32((DWORD)(0x9f8f0cu));	/* 44ca4b: mov ecx, dword ptr [0x9f8f0c] */
	{ DWORD a_ = m->eax, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44ca51: add eax, 0x114 */
	{ DWORD a_ = m->ecx, b_ = 0x4au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44ca56: add ecx, 0x4a */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ca59: push 2 */
	M32((DWORD)(0x74de1cu)) = m->esi;	/* 44ca5b: mov dword ptr [0x74de1c], esi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 44ca61: mov dword ptr [0x76d42c], esi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 44ca67: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 44ca71: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->eax;	/* 44ca7b: mov dword ptr [0x67ef34], eax */
	M32((DWORD)(0x67fb38u)) = m->ecx;	/* 44ca80: mov dword ptr [0x67fb38], ecx */
	m->esp -= 4; M32(m->esp) = 0x44ca8bu; native_call(m, 0x41e760u);	/* 44ca86: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ca8b: add esp, 4 */
L_44ca8e:
	m->esi = M32(m->esp); m->esp += 4;	/* 44ca8e: pop esi */
	m->esp += 4 + 0; return;	/* 44ca8f: ret  */
}

/* profile_44ca90 (0x44ca90), lifted by tools/lift.py */
static void lift_44ca90(X86 *m)
{
	m->eax = M32((DWORD)(0x4e1510u));	/* 44ca90: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ca95: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44ca96: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ca97: push eax */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44ca98: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x44caa7u; native_call(m, 0x401600u);	/* 44caa2: call 0x401600 */
	m->esi = 0x1u;	/* 44caa7: mov esi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44caac: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44caaf: cmp eax, esi */
	if (!m->zf) goto L_44cac5;	/* 44cab1: jne 0x44cac5 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cab3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44cabau; native_call(m, 0x41e760u);	/* 44cab5: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44caba: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44cac2u; native_call(m, 0x44bc00u);	/* 44cabd: call 0x44bc00 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44cac2: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44cac3: pop esi */
	m->esp += 4 + 0; return;	/* 44cac4: ret  */
L_44cac5:
	m->ecx = M32((DWORD)(0x9dae70u));	/* 44cac5: mov ecx, dword ptr [0x9dae70] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cacb: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44cad1u; native_call(m, 0x401600u);	/* 44cacc: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cad1: add esp, 4 */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 44cad4: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cad6: cmp eax, esi */
	if (!m->zf) goto L_44cb08;	/* 44cad8: jne 0x44cb08 */
	m->edx = M32((DWORD)(0x4ded6cu));	/* 44cada: mov edx, dword ptr [0x4ded6c] */
	m->eax = M32((DWORD)(0x4ded68u));	/* 44cae0: mov eax, dword ptr [0x4ded68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cae5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cae6: push eax */
	m->esp -= 4; M32(m->esp) = 0x44caecu; native_call(m, 0x44b360u);	/* 44cae7: call 0x44b360 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44caec: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44caef: cmp eax, edi */
	if (!m->zf) goto L_44cb04;	/* 44caf1: jne 0x44cb04 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44caf3: push edi */
	m->esp -= 4; M32(m->esp) = 0x44caf9u; native_call(m, 0x41e760u);	/* 44caf4: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44caf9: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44cb01u; native_call(m, 0x44bc00u);	/* 44cafc: call 0x44bc00 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44cb01: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44cb02: pop esi */
	m->esp += 4 + 0; return;	/* 44cb03: ret  */
L_44cb04:
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cb04: cmp eax, esi */
	if (m->zf) goto L_44cb2e;	/* 44cb06: je 0x44cb2e */
L_44cb08:
	m->ecx = M32((DWORD)(0x6803a0u));	/* 44cb08: mov ecx, dword ptr [0x6803a0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cb0e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44cb14u; native_call(m, 0x401600u);	/* 44cb0f: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cb14: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cb17: cmp eax, esi */
	if (m->zf) goto L_44cb2e;	/* 44cb19: je 0x44cb2e */
	m->edx = M32((DWORD)(0x4e0cdcu));	/* 44cb1b: mov edx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cb21: push edx */
	m->esp -= 4; M32(m->esp) = 0x44cb27u; native_call(m, 0x401600u);	/* 44cb22: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cb27: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cb2a: cmp eax, esi */
	if (!m->zf) goto L_44cb46;	/* 44cb2c: jne 0x44cb46 */
L_44cb2e:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 44cb2e: push edi */
	m->esp -= 4; M32(m->esp) = 0x44cb34u; native_call(m, 0x41e760u);	/* 44cb2f: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cb34: add esp, 4 */
	M32((DWORD)(0x76d42cu)) = m->edi;	/* 44cb37: mov dword ptr [0x76d42c], edi */
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44cb3d: mov dword ptr [0x9f8f10], esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 44cb43: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44cb44: pop esi */
	m->esp += 4 + 0; return;	/* 44cb45: ret  */
L_44cb46:
	m->eax = M32((DWORD)(0x9db974u));	/* 44cb46: mov eax, dword ptr [0x9db974] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cb4b: push eax */
	m->esp -= 4; M32(m->esp) = 0x44cb51u; native_call(m, 0x401600u);	/* 44cb4c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cb51: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cb54: cmp eax, esi */
	if (!m->zf) goto L_44cb8e;	/* 44cb56: jne 0x44cb8e */
	{ DWORD a_ = M32((DWORD)(0x74de1cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cb58: cmp dword ptr [0x74de1c], edi */
	if (!m->zf) goto L_44cb8e;	/* 44cb5e: jne 0x44cb8e */
	m->ecx = M32((DWORD)(0x9f6834u));	/* 44cb60: mov ecx, dword ptr [0x9f6834] */
	M32((DWORD)(0x74de1cu)) = m->esi;	/* 44cb66: mov dword ptr [0x74de1c], esi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 44cb6c: mov dword ptr [0x76d42c], esi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 44cb72: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 44cb7c: mov dword ptr [0x9da4a4], 0x3ecccccd */
	{ DWORD a_ = m->ecx, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44cb86: add ecx, 0x114 */
	goto L_44cbd4;	/* 44cb8c: jmp 0x44cbd4 */
L_44cb8e:
	m->eax = M32((DWORD)(0x9dae14u));	/* 44cb8e: mov eax, dword ptr [0x9dae14] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cb93: push eax */
	m->esp -= 4; M32(m->esp) = 0x44cb99u; native_call(m, 0x401600u);	/* 44cb94: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cb99: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cb9c: cmp eax, esi */
	if (!m->zf) goto L_44cbf6;	/* 44cb9e: jne 0x44cbf6 */
	{ DWORD a_ = M32((DWORD)(0x74de1cu)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cba0: cmp dword ptr [0x74de1c], esi */
	if (!m->zf) goto L_44cbf6;	/* 44cba6: jne 0x44cbf6 */
L_44cba8:
	m->ecx = M32((DWORD)(0x9f6834u));	/* 44cba8: mov ecx, dword ptr [0x9f6834] */
	M32((DWORD)(0x74de1cu)) = m->edi;	/* 44cbae: mov dword ptr [0x74de1c], edi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 44cbb4: mov dword ptr [0x76d42c], esi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 44cbba: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 44cbc4: mov dword ptr [0x9da4a4], 0x3ecccccd */
	{ DWORD a_ = m->ecx, b_ = 0x9cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44cbce: add ecx, 0x9c */
L_44cbd4:
	m->edx = M32((DWORD)(0x9f683cu));	/* 44cbd4: mov edx, dword ptr [0x9f683c] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cbda: push 2 */
	{ DWORD a_ = m->edx, b_ = 0x4au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 44cbdc: add edx, 0x4a */
	M32((DWORD)(0x67ef34u)) = m->ecx;	/* 44cbdf: mov dword ptr [0x67ef34], ecx */
	M32((DWORD)(0x67fb38u)) = m->edx;	/* 44cbe5: mov dword ptr [0x67fb38], edx */
	m->esp -= 4; M32(m->esp) = 0x44cbf0u; native_call(m, 0x41e760u);	/* 44cbeb: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cbf0: add esp, 4 */
	m->edi = M32(m->esp); m->esp += 4;	/* 44cbf3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44cbf4: pop esi */
	m->esp += 4 + 0; return;	/* 44cbf5: ret  */
L_44cbf6:
	m->eax = M32((DWORD)(0x680390u));	/* 44cbf6: mov eax, dword ptr [0x680390] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cbfb: push eax */
	m->esp -= 4; M32(m->esp) = 0x44cc01u; native_call(m, 0x401600u);	/* 44cbfc: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cc01: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cc04: cmp eax, esi */
	if (!m->zf) goto L_44cc58;	/* 44cc06: jne 0x44cc58 */
	{ DWORD a_ = M32((DWORD)(0x74de1cu)), b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cc08: cmp dword ptr [0x74de1c], edi */
	if (!m->zf) goto L_44cba8;	/* 44cc0e: jne 0x44cba8 */
	m->eax = M32((DWORD)(0x9f6834u));	/* 44cc10: mov eax, dword ptr [0x9f6834] */
	m->ecx = M32((DWORD)(0x9f683cu));	/* 44cc15: mov ecx, dword ptr [0x9f683c] */
	{ DWORD a_ = m->eax, b_ = 0x114u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cc1b: add eax, 0x114 */
	{ DWORD a_ = m->ecx, b_ = 0x4au & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 44cc20: add ecx, 0x4a */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cc23: push 2 */
	M32((DWORD)(0x74de1cu)) = m->esi;	/* 44cc25: mov dword ptr [0x74de1c], esi */
	M32((DWORD)(0x76d42cu)) = m->esi;	/* 44cc2b: mov dword ptr [0x76d42c], esi */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 44cc31: mov dword ptr [0x680bc0], 0x41a00000 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 44cc3b: mov dword ptr [0x9da4a4], 0x3ecccccd */
	M32((DWORD)(0x67ef34u)) = m->eax;	/* 44cc45: mov dword ptr [0x67ef34], eax */
	M32((DWORD)(0x67fb38u)) = m->ecx;	/* 44cc4a: mov dword ptr [0x67fb38], ecx */
	m->esp -= 4; M32(m->esp) = 0x44cc55u; native_call(m, 0x41e760u);	/* 44cc50: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cc55: add esp, 4 */
L_44cc58:
	m->edi = M32(m->esp); m->esp += 4;	/* 44cc58: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 44cc59: pop esi */
	m->esp += 4 + 0; return;	/* 44cc5a: ret  */
}

/* profile_44cc60 (0x44cc60), lifted by tools/lift.py */
static void lift_44cc60(X86 *m)
{
	m->eax = M32((DWORD)(0x4e1510u));	/* 44cc60: mov eax, dword ptr [0x4e1510] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 44cc65: push esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cc66: push eax */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 44cc67: mov dword ptr [0x4dda44], 0 */
	m->esp -= 4; M32(m->esp) = 0x44cc76u; native_call(m, 0x401600u);	/* 44cc71: call 0x401600 */
	m->esi = 0x1u;	/* 44cc76: mov esi, 1 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cc7b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cc7e: cmp eax, esi */
	if (!m->zf) goto L_44cc93;	/* 44cc80: jne 0x44cc93 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cc82: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44cc89u; native_call(m, 0x41e760u);	/* 44cc84: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cc89: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x44cc91u; native_call(m, 0x44b990u);	/* 44cc8c: call 0x44b990 */
	goto L_44ccc3;	/* 44cc91: jmp 0x44ccc3 */
L_44cc93:
	m->ecx = M32((DWORD)(0x4e0cdcu));	/* 44cc93: mov ecx, dword ptr [0x4e0cdc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cc99: push ecx */
	m->esp -= 4; M32(m->esp) = 0x44cc9fu; native_call(m, 0x401600u);	/* 44cc9a: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cc9f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cca2: cmp eax, esi */
	if (m->zf) goto L_44ccb9;	/* 44cca4: je 0x44ccb9 */
	m->edx = M32((DWORD)(0x6803a0u));	/* 44cca6: mov edx, dword ptr [0x6803a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44ccac: push edx */
	m->esp -= 4; M32(m->esp) = 0x44ccb2u; native_call(m, 0x401600u);	/* 44ccad: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ccb2: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44ccb5: cmp eax, esi */
	if (!m->zf) goto L_44ccd5;	/* 44ccb7: jne 0x44ccd5 */
L_44ccb9:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 44ccb9: push 0 */
	m->esp -= 4; M32(m->esp) = 0x44ccc0u; native_call(m, 0x41e760u);	/* 44ccbb: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44ccc0: add esp, 4 */
L_44ccc3:
	M32((DWORD)(0x9f8f10u)) = m->esi;	/* 44ccc3: mov dword ptr [0x9f8f10], esi */
	M32((DWORD)(0x76d42cu)) = 0x0u;	/* 44ccc9: mov dword ptr [0x76d42c], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 44ccd3: pop esi */
	m->esp += 4 + 0; return;	/* 44ccd4: ret  */
L_44ccd5:
	m->eax = M32((DWORD)(0x9db974u));	/* 44ccd5: mov eax, dword ptr [0x9db974] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44ccda: push eax */
	m->esp -= 4; M32(m->esp) = 0x44cce0u; native_call(m, 0x401600u);	/* 44ccdb: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cce0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cce3: cmp eax, esi */
	if (!m->zf) goto L_44cd0e;	/* 44cce5: jne 0x44cd0e */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44cce7: mov eax, dword ptr [0x9f8d30] */
	m->ecx = 0x3u;	/* 44ccec: mov ecx, 3 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 44ccf1: inc eax */
	M32((DWORD)(0x9f8d30u)) = m->eax;	/* 44ccf2: mov dword ptr [0x9f8d30], eax */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44ccf7: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 44ccf8: idiv ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44ccfa: test edx, edx */
	if (!m->zf) goto L_44cda8;	/* 44ccfc: jne 0x44cda8 */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44cd02: mov eax, dword ptr [0x9f8d30] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cd07: sub eax, ecx */
	goto L_44cda3;	/* 44cd09: jmp 0x44cda3 */
L_44cd0e:
	m->edx = M32((DWORD)(0x9dae14u));	/* 44cd0e: mov edx, dword ptr [0x9dae14] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cd14: push edx */
	m->esp -= 4; M32(m->esp) = 0x44cd1au; native_call(m, 0x401600u);	/* 44cd15: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cd1a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cd1d: cmp eax, esi */
	if (!m->zf) goto L_44cd55;	/* 44cd1f: jne 0x44cd55 */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44cd21: mov eax, dword ptr [0x9f8d30] */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 44cd26: dec eax */
	M32((DWORD)(0x9f8d30u)) = m->eax;	/* 44cd27: mov dword ptr [0x9f8d30], eax */
	if (!m->sf) goto L_44cd3a;	/* 44cd2c: jns 0x44cd3a */
	M32((DWORD)(0x9f8d30u)) = 0x2u;	/* 44cd2e: mov dword ptr [0x9f8d30], 2 */
	goto L_44cda8;	/* 44cd38: jmp 0x44cda8 */
L_44cd3a:
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44cd3a: mov eax, dword ptr [0x9f8d30] */
	m->ecx = 0x3u;	/* 44cd3f: mov ecx, 3 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 44cd44: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 44cd45: idiv ecx */
	{ DWORD a_ = m->edx, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cd47: cmp edx, 2 */
	if (!m->zf) goto L_44cda8;	/* 44cd4a: jne 0x44cda8 */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44cd4c: mov eax, dword ptr [0x9f8d30] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cd51: add eax, ecx */
	goto L_44cda3;	/* 44cd53: jmp 0x44cda3 */
L_44cd55:
	m->edx = M32((DWORD)(0x9db0a0u));	/* 44cd55: mov edx, dword ptr [0x9db0a0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44cd5b: push edx */
	m->esp -= 4; M32(m->esp) = 0x44cd61u; native_call(m, 0x401600u);	/* 44cd5c: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cd61: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cd64: cmp eax, esi */
	if (!m->zf) goto L_44cd7c;	/* 44cd66: jne 0x44cd7c */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44cd68: mov eax, dword ptr [0x9f8d30] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cd6d: sub eax, 3 */
	M32((DWORD)(0x9f8d30u)) = m->eax;	/* 44cd70: mov dword ptr [0x9f8d30], eax */
	if (!m->sf) goto L_44cda8;	/* 44cd75: jns 0x44cda8 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cd77: add eax, 9 */
	goto L_44cda3;	/* 44cd7a: jmp 0x44cda3 */
L_44cd7c:
	m->eax = M32((DWORD)(0x76d330u));	/* 44cd7c: mov eax, dword ptr [0x76d330] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44cd81: push eax */
	m->esp -= 4; M32(m->esp) = 0x44cd87u; native_call(m, 0x401600u);	/* 44cd82: call 0x401600 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cd87: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cd8a: cmp eax, esi */
	if (!m->zf) goto L_44cdcc;	/* 44cd8c: jne 0x44cdcc */
	m->eax = M32((DWORD)(0x9f8d30u));	/* 44cd8e: mov eax, dword ptr [0x9f8d30] */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cd93: add eax, 3 */
	{ DWORD a_ = m->eax, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 44cd96: cmp eax, 8 */
	M32((DWORD)(0x9f8d30u)) = m->eax;	/* 44cd99: mov dword ptr [0x9f8d30], eax */
	if (m->zf || m->sf != m->of) goto L_44cda8;	/* 44cd9e: jle 0x44cda8 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 44cda0: sub eax, 9 */
L_44cda3:
	M32((DWORD)(0x9f8d30u)) = m->eax;	/* 44cda3: mov dword ptr [0x9f8d30], eax */
L_44cda8:
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 44cda8: push 2 */
	M32((DWORD)(0x9f8d68u)) = m->esi;	/* 44cdaa: mov dword ptr [0x9f8d68], esi */
	m->esp -= 4; M32(m->esp) = 0x44cdb5u; native_call(m, 0x41e760u);	/* 44cdb0: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44cdb5: add esp, 4 */
	M32((DWORD)(0x9f8ee4u)) = 0x0u;	/* 44cdb8: mov dword ptr [0x9f8ee4], 0 */
	M32((DWORD)(0x9f6828u)) = 0x0u;	/* 44cdc2: mov dword ptr [0x9f6828], 0 */
L_44cdcc:
	m->esi = M32(m->esp); m->esp += 4;	/* 44cdcc: pop esi */
	m->esp += 4 + 0; return;	/* 44cdcd: ret  */
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
