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

static void lift_48a370(X86 *m);

/* match_inputState3 (0x48a370), lifted by tools/lift.py */
static void lift_48a370(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a370: sub esp, 0x84 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a376: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48a377: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48a378: push esi */
	m->esi = m->ecx;	/* 48a379: mov esi, ecx */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48a37b: xor ebx, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48a37d: push edi */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x233cc28u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a37e: cmp dword ptr [esi + 0x233cc28], ebx */
	if (!m->zf) goto L_48a460;	/* 48a384: jne 0x48a460 */
	M32((DWORD)(m->esi + 0x234240du)) = m->ebx;	/* 48a38a: mov dword ptr [esi + 0x234240d], ebx */
	M32((DWORD)(m->esi + 0x233ca28u)) = m->ebx;	/* 48a390: mov dword ptr [esi + 0x233ca28], ebx */
	M32((DWORD)(m->esi + 0x233ca2cu)) = m->ebx;	/* 48a396: mov dword ptr [esi + 0x233ca2c], ebx */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->ebx;	/* 48a39c: mov dword ptr [esi + 0x233cc10], ebx */
L_48a3a2:
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48a3a2: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca30u));	/* 48a3a8: mov ecx, dword ptr [esi + eax*4 + 0x233ca30] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb20u)) = m->ecx;	/* 48a3af: mov dword ptr [esi + eax*4 + 0x233cb20], ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48a3b6: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca58u));	/* 48a3bc: mov edx, dword ptr [esi + eax*4 + 0x233ca58] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb48u)) = m->edx;	/* 48a3c3: mov dword ptr [esi + eax*4 + 0x233cb48], edx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48a3ca: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233ca80u));	/* 48a3d0: mov ecx, dword ptr [esi + eax*4 + 0x233ca80] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb70u)) = m->ecx;	/* 48a3d7: mov dword ptr [esi + eax*4 + 0x233cb70], ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48a3de: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233caa8u));	/* 48a3e4: mov edx, dword ptr [esi + eax*4 + 0x233caa8] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb98u)) = m->edx;	/* 48a3eb: mov dword ptr [esi + eax*4 + 0x233cb98], edx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48a3f2: mov eax, dword ptr [esi + 0x233cc10] */
	m->ecx = M32((DWORD)(m->esi + m->eax*4 + 0x233cad0u));	/* 48a3f8: mov ecx, dword ptr [esi + eax*4 + 0x233cad0] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cbc0u)) = m->ecx;	/* 48a3ff: mov dword ptr [esi + eax*4 + 0x233cbc0], ecx */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48a406: mov eax, dword ptr [esi + 0x233cc10] */
	m->edx = M32((DWORD)(m->esi + m->eax*4 + 0x233caf8u));	/* 48a40c: mov edx, dword ptr [esi + eax*4 + 0x233caf8] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cbe8u)) = m->edx;	/* 48a413: mov dword ptr [esi + eax*4 + 0x233cbe8], edx */
	m->ecx = M32((DWORD)(m->esi + 0x233cc10u));	/* 48a41a: mov ecx, dword ptr [esi + 0x233cc10] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48a420: inc ecx */
	m->eax = m->ecx;	/* 48a421: mov eax, ecx */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->ecx;	/* 48a423: mov dword ptr [esi + 0x233cc10], ecx */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a429: cmp eax, 0xa */
	if (m->sf != m->of) goto L_48a3a2;	/* 48a42c: jl 0x48a3a2 */
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 48a432: lea ecx, [esi + 0xc] */
	M32((DWORD)(m->esi + 0x233cc10u)) = m->ebx;	/* 48a435: mov dword ptr [esi + 0x233cc10], ebx */
	m->esp -= 4; M32(m->esp) = 0x48a440u; { long double r_ = native_call_fp(m, 0x487490u); FPUSH(r_); }	/* 48a43b: call 0x487490 */
	ST(0) = ST(0); FPOP();	/* 48a440: fstp st(0) */
	m->esp -= 4; M32(m->esp) = 0x48a447u; native_call(m, 0x4685c0u);	/* 48a442: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48a447: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48a448: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48a44a: sar eax, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a44c: push eax */
	m->esp -= 4; M32(m->esp) = 0x48a452u; native_call(m, 0x4685b0u);	/* 48a44d: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48a452: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48a453: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48a455: sar eax, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a457: push eax */
	m->esp -= 4; M32(m->esp) = 0x48a45du; native_call(m, 0x487c80u);	/* 48a458: call 0x487c80 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a45d: add esp, 8 */
L_48a460:
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 48a460: mov eax, dword ptr [esi + 0x234240d] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a466: push 2 */
	m->ecx = m->eax;	/* 48a468: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48a46a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48a46d: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48a46f: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48a472: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48a474: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48a477: add ecx, eax */
	m->edi = (DWORD)(m->esi + m->ecx*8 + 0x1ecca70u);	/* 48a479: lea edi, [esi + ecx*8 + 0x1ecca70] */
	m->ecx = M32((DWORD)(m->esi + m->ecx*8 + 0x1eccb7cu));	/* 48a480: mov ecx, dword ptr [esi + ecx*8 + 0x1eccb7c] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48a487: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48a48a: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48a48d: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48a48f: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 48a492: lea eax, [ecx + edx*8] */
	m->ecx = (DWORD)(m->esi + m->eax*2 + 0x1755230u);	/* 48a495: lea ecx, [esi + eax*2 + 0x1755230] */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 48a49c: mov dword ptr [esp + 0x18], ecx */
	m->esp -= 4; M32(m->esp) = 0x48a4a5u; native_call(m, 0x487ba0u);	/* 48a4a0: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a4a5: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a4a8: test eax, eax */
	if (m->zf) goto L_48a4b9;	/* 48a4aa: je 0x48a4b9 */
	m->ebp = 0x1u;	/* 48a4ac: mov ebp, 1 */
	M32((DWORD)(m->esi + 0x234325fu)) = m->ebp;	/* 48a4b1: mov dword ptr [esi + 0x234325f], ebp */
	goto L_48a4c4;	/* 48a4b7: jmp 0x48a4c4 */
L_48a4b9:
	M32((DWORD)(m->esi + 0x234325fu)) = m->ebx;	/* 48a4b9: mov dword ptr [esi + 0x234325f], ebx */
	m->ebp = 0x1u;	/* 48a4bf: mov ebp, 1 */
L_48a4c4:
	{ DWORD v_ = 0x41u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a4c4: push 0x41 */
	m->esp -= 4; M32(m->esp) = 0x48a4cbu; native_call(m, 0x487ba0u);	/* 48a4c6: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a4cb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a4ce: test eax, eax */
	if (m->zf) goto L_48a4da;	/* 48a4d0: je 0x48a4da */
	M32((DWORD)(m->esi + 0x234326bu)) = m->ebp;	/* 48a4d2: mov dword ptr [esi + 0x234326b], ebp */
	goto L_48a4e0;	/* 48a4d8: jmp 0x48a4e0 */
L_48a4da:
	M32((DWORD)(m->esi + 0x234326bu)) = m->ebx;	/* 48a4da: mov dword ptr [esi + 0x234326b], ebx */
L_48a4e0:
	{ DWORD v_ = 0x44u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a4e0: push 0x44 */
	m->esp -= 4; M32(m->esp) = 0x48a4e7u; native_call(m, 0x487ba0u);	/* 48a4e2: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a4e7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a4ea: test eax, eax */
	if (m->zf) goto L_48a4f6;	/* 48a4ec: je 0x48a4f6 */
	M32((DWORD)(m->esi + 0x234326fu)) = m->ebp;	/* 48a4ee: mov dword ptr [esi + 0x234326f], ebp */
	goto L_48a4fc;	/* 48a4f4: jmp 0x48a4fc */
L_48a4f6:
	M32((DWORD)(m->esi + 0x234326fu)) = m->ebx;	/* 48a4f6: mov dword ptr [esi + 0x234326f], ebx */
L_48a4fc:
	{ DWORD v_ = 0x57u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a4fc: push 0x57 */
	m->esp -= 4; M32(m->esp) = 0x48a503u; native_call(m, 0x487ba0u);	/* 48a4fe: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a503: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a506: test eax, eax */
	if (m->zf) goto L_48a512;	/* 48a508: je 0x48a512 */
	M32((DWORD)(m->esi + 0x2343263u)) = m->ebp;	/* 48a50a: mov dword ptr [esi + 0x2343263], ebp */
	goto L_48a518;	/* 48a510: jmp 0x48a518 */
L_48a512:
	M32((DWORD)(m->esi + 0x2343263u)) = m->ebx;	/* 48a512: mov dword ptr [esi + 0x2343263], ebx */
L_48a518:
	{ DWORD v_ = 0x53u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a518: push 0x53 */
	m->esp -= 4; M32(m->esp) = 0x48a51fu; native_call(m, 0x487ba0u);	/* 48a51a: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a51f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a522: test eax, eax */
	if (m->zf) goto L_48a52e;	/* 48a524: je 0x48a52e */
	M32((DWORD)(m->esi + 0x2343267u)) = m->ebp;	/* 48a526: mov dword ptr [esi + 0x2343267], ebp */
	goto L_48a534;	/* 48a52c: jmp 0x48a534 */
L_48a52e:
	M32((DWORD)(m->esi + 0x2343267u)) = m->ebx;	/* 48a52e: mov dword ptr [esi + 0x2343267], ebx */
L_48a534:
	{ DWORD v_ = 0x51u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a534: push 0x51 */
	m->esp -= 4; M32(m->esp) = 0x48a53bu; native_call(m, 0x487ba0u);	/* 48a536: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a53b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a53e: test eax, eax */
	if (m->zf) goto L_48a54a;	/* 48a540: je 0x48a54a */
	M32((DWORD)(m->esi + 0x2343273u)) = m->ebp;	/* 48a542: mov dword ptr [esi + 0x2343273], ebp */
	goto L_48a550;	/* 48a548: jmp 0x48a550 */
L_48a54a:
	M32((DWORD)(m->esi + 0x2343273u)) = m->ebx;	/* 48a54a: mov dword ptr [esi + 0x2343273], ebx */
L_48a550:
	{ DWORD v_ = 0x45u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a550: push 0x45 */
	m->esp -= 4; M32(m->esp) = 0x48a557u; native_call(m, 0x487ba0u);	/* 48a552: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a557: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a55a: test eax, eax */
	if (m->zf) goto L_48a566;	/* 48a55c: je 0x48a566 */
	M32((DWORD)(m->esi + 0x2343277u)) = m->ebp;	/* 48a55e: mov dword ptr [esi + 0x2343277], ebp */
	goto L_48a56c;	/* 48a564: jmp 0x48a56c */
L_48a566:
	M32((DWORD)(m->esi + 0x2343277u)) = m->ebx;	/* 48a566: mov dword ptr [esi + 0x2343277], ebx */
L_48a56c:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48a56c: push ebp */
	m->esp -= 4; M32(m->esp) = 0x48a572u; native_call(m, 0x487ba0u);	/* 48a56d: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a572: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a575: test eax, eax */
	if (m->zf) goto L_48a581;	/* 48a577: je 0x48a581 */
	M32((DWORD)(m->esi + 0x234327bu)) = m->ebp;	/* 48a579: mov dword ptr [esi + 0x234327b], ebp */
	goto L_48a587;	/* 48a57f: jmp 0x48a587 */
L_48a581:
	M32((DWORD)(m->esi + 0x234327bu)) = m->ebx;	/* 48a581: mov dword ptr [esi + 0x234327b], ebx */
L_48a587:
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a587: push 0x10 */
	m->esp -= 4; M32(m->esp) = 0x48a58eu; native_call(m, 0x487ba0u);	/* 48a589: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a58e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a591: test eax, eax */
	if (m->zf) goto L_48a59d;	/* 48a593: je 0x48a59d */
	M32((DWORD)(m->esi + 0x2343283u)) = m->ebp;	/* 48a595: mov dword ptr [esi + 0x2343283], ebp */
	goto L_48a5a3;	/* 48a59b: jmp 0x48a5a3 */
L_48a59d:
	M32((DWORD)(m->esi + 0x2343283u)) = m->ebx;	/* 48a59d: mov dword ptr [esi + 0x2343283], ebx */
L_48a5a3:
	{ DWORD v_ = 0x31u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a5a3: push 0x31 */
	M32((DWORD)(m->esi + 0x2343287u)) = 0xffffffffu;	/* 48a5a5: mov dword ptr [esi + 0x2343287], 0xffffffff */
	m->esp -= 4; M32(m->esp) = 0x48a5b4u; native_call(m, 0x487ba0u);	/* 48a5af: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a5b4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a5b7: test eax, eax */
	if (m->zf) goto L_48a5c1;	/* 48a5b9: je 0x48a5c1 */
	M32((DWORD)(m->esi + 0x2343287u)) = m->ebx;	/* 48a5bb: mov dword ptr [esi + 0x2343287], ebx */
L_48a5c1:
	{ DWORD v_ = 0x32u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a5c1: push 0x32 */
	m->esp -= 4; M32(m->esp) = 0x48a5c8u; native_call(m, 0x487ba0u);	/* 48a5c3: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a5c8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a5cb: test eax, eax */
	if (m->zf) goto L_48a5d5;	/* 48a5cd: je 0x48a5d5 */
	M32((DWORD)(m->esi + 0x2343287u)) = m->ebp;	/* 48a5cf: mov dword ptr [esi + 0x2343287], ebp */
L_48a5d5:
	{ DWORD v_ = 0x33u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a5d5: push 0x33 */
	m->esp -= 4; M32(m->esp) = 0x48a5dcu; native_call(m, 0x487ba0u);	/* 48a5d7: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a5dc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a5df: test eax, eax */
	if (m->zf) goto L_48a5ed;	/* 48a5e1: je 0x48a5ed */
	M32((DWORD)(m->esi + 0x2343287u)) = 0x2u;	/* 48a5e3: mov dword ptr [esi + 0x2343287], 2 */
L_48a5ed:
	{ DWORD v_ = 0x34u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a5ed: push 0x34 */
	m->esp -= 4; M32(m->esp) = 0x48a5f4u; native_call(m, 0x487ba0u);	/* 48a5ef: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a5f4: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a5f7: test eax, eax */
	if (m->zf) goto L_48a605;	/* 48a5f9: je 0x48a605 */
	M32((DWORD)(m->esi + 0x2343287u)) = 0x3u;	/* 48a5fb: mov dword ptr [esi + 0x2343287], 3 */
L_48a605:
	{ DWORD v_ = 0x35u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a605: push 0x35 */
	m->esp -= 4; M32(m->esp) = 0x48a60cu; native_call(m, 0x487ba0u);	/* 48a607: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a60c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a60f: test eax, eax */
	if (m->zf) goto L_48a61d;	/* 48a611: je 0x48a61d */
	M32((DWORD)(m->esi + 0x2343287u)) = 0x4u;	/* 48a613: mov dword ptr [esi + 0x2343287], 4 */
L_48a61d:
	{ DWORD v_ = 0x36u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a61d: push 0x36 */
	m->esp -= 4; M32(m->esp) = 0x48a624u; native_call(m, 0x487ba0u);	/* 48a61f: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a624: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a627: test eax, eax */
	if (m->zf) goto L_48a635;	/* 48a629: je 0x48a635 */
	M32((DWORD)(m->esi + 0x2343287u)) = 0x5u;	/* 48a62b: mov dword ptr [esi + 0x2343287], 5 */
L_48a635:
	{ DWORD v_ = 0x11u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a635: push 0x11 */
	m->esp -= 4; M32(m->esp) = 0x48a63cu; native_call(m, 0x487ba0u);	/* 48a637: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a63c: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a63f: test eax, eax */
	if (m->zf) goto L_48a69d;	/* 48a641: je 0x48a69d */
	{ DWORD v_ = 0x26u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a643: push 0x26 */
	m->esp -= 4; M32(m->esp) = 0x48a64au; native_call(m, 0x487ba0u);	/* 48a645: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a64a: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a64d: test eax, eax */
	if (m->zf) goto L_48a659;	/* 48a64f: je 0x48a659 */
	M32((DWORD)(m->esi + 0x23432abu)) = m->ebp;	/* 48a651: mov dword ptr [esi + 0x23432ab], ebp */
	goto L_48a65f;	/* 48a657: jmp 0x48a65f */
L_48a659:
	M32((DWORD)(m->esi + 0x23432abu)) = m->ebx;	/* 48a659: mov dword ptr [esi + 0x23432ab], ebx */
L_48a65f:
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a65f: push 0x28 */
	m->esp -= 4; M32(m->esp) = 0x48a666u; native_call(m, 0x487ba0u);	/* 48a661: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a666: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a669: test eax, eax */
	if (m->zf) goto L_48a675;	/* 48a66b: je 0x48a675 */
	M32((DWORD)(m->esi + 0x23432afu)) = m->ebp;	/* 48a66d: mov dword ptr [esi + 0x23432af], ebp */
	goto L_48a67b;	/* 48a673: jmp 0x48a67b */
L_48a675:
	M32((DWORD)(m->esi + 0x23432afu)) = m->ebx;	/* 48a675: mov dword ptr [esi + 0x23432af], ebx */
L_48a67b:
	M32((DWORD)(m->esi + 0x23432bbu)) = m->ebx;	/* 48a67b: mov dword ptr [esi + 0x23432bb], ebx */
L_48a681:
	M32((DWORD)(m->esi + 0x23432bfu)) = m->ebx;	/* 48a681: mov dword ptr [esi + 0x23432bf], ebx */
L_48a687:
	{ DWORD v_ = 0x25u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a687: push 0x25 */
	m->esp -= 4; M32(m->esp) = 0x48a68eu; native_call(m, 0x487ba0u);	/* 48a689: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a68e: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a691: test eax, eax */
	if (m->zf) goto L_48a6db;	/* 48a693: je 0x48a6db */
	M32((DWORD)(m->esi + 0x23432b3u)) = m->ebp;	/* 48a695: mov dword ptr [esi + 0x23432b3], ebp */
	goto L_48a6e1;	/* 48a69b: jmp 0x48a6e1 */
L_48a69d:
	{ DWORD v_ = 0x26u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a69d: push 0x26 */
	M32((DWORD)(m->esi + 0x23432abu)) = m->ebx;	/* 48a69f: mov dword ptr [esi + 0x23432ab], ebx */
	M32((DWORD)(m->esi + 0x23432afu)) = m->ebx;	/* 48a6a5: mov dword ptr [esi + 0x23432af], ebx */
	m->esp -= 4; M32(m->esp) = 0x48a6b0u; native_call(m, 0x487ba0u);	/* 48a6ab: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a6b0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a6b3: test eax, eax */
	if (m->zf) goto L_48a6bf;	/* 48a6b5: je 0x48a6bf */
	M32((DWORD)(m->esi + 0x23432bbu)) = m->ebp;	/* 48a6b7: mov dword ptr [esi + 0x23432bb], ebp */
	goto L_48a6c5;	/* 48a6bd: jmp 0x48a6c5 */
L_48a6bf:
	M32((DWORD)(m->esi + 0x23432bbu)) = m->ebx;	/* 48a6bf: mov dword ptr [esi + 0x23432bb], ebx */
L_48a6c5:
	{ DWORD v_ = 0x28u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a6c5: push 0x28 */
	m->esp -= 4; M32(m->esp) = 0x48a6ccu; native_call(m, 0x487ba0u);	/* 48a6c7: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a6cc: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a6cf: test eax, eax */
	if (m->zf) goto L_48a681;	/* 48a6d1: je 0x48a681 */
	M32((DWORD)(m->esi + 0x23432bfu)) = m->ebp;	/* 48a6d3: mov dword ptr [esi + 0x23432bf], ebp */
	goto L_48a687;	/* 48a6d9: jmp 0x48a687 */
L_48a6db:
	M32((DWORD)(m->esi + 0x23432b3u)) = m->ebx;	/* 48a6db: mov dword ptr [esi + 0x23432b3], ebx */
L_48a6e1:
	{ DWORD v_ = 0x27u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a6e1: push 0x27 */
	m->esp -= 4; M32(m->esp) = 0x48a6e8u; native_call(m, 0x487ba0u);	/* 48a6e3: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a6e8: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a6eb: test eax, eax */
	if (m->zf) goto L_48a6f7;	/* 48a6ed: je 0x48a6f7 */
	M32((DWORD)(m->esi + 0x23432b7u)) = m->ebp;	/* 48a6ef: mov dword ptr [esi + 0x23432b7], ebp */
	goto L_48a6fd;	/* 48a6f5: jmp 0x48a6fd */
L_48a6f7:
	M32((DWORD)(m->esi + 0x23432b7u)) = m->ebx;	/* 48a6f7: mov dword ptr [esi + 0x23432b7], ebx */
L_48a6fd:
	m->esp -= 4; M32(m->esp) = 0x48a702u; native_call(m, 0x487c30u);	/* 48a6fd: call 0x487c30 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 48a702: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esi + 0x2343257u)) = m->edx;	/* 48a704: mov dword ptr [esi + 0x2343257], edx */
	m->eax = M32((DWORD)(m->eax + 0x4u));	/* 48a70a: mov eax, dword ptr [eax + 4] */
	M32((DWORD)(m->esi + 0x234325bu)) = m->eax;	/* 48a70d: mov dword ptr [esi + 0x234325b], eax */
	m->esp -= 4; M32(m->esp) = 0x48a718u; native_call(m, 0x4685c0u);	/* 48a713: call 0x4685c0 */
	m->ecx = M32((DWORD)(m->esi + 0x234325bu));	/* 48a718: mov ecx, dword ptr [esi + 0x234325b] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48a71e: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48a71f: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48a721: sar eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48a723: sub ecx, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 48a725: mov dword ptr [esp + 0x10], ecx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 48a729: fild dword ptr [esp + 0x10] */
	MF((DWORD)(m->esi + 0x2343293u)) = (float)ST(0); FPOP();	/* 48a72d: fstp dword ptr [esi + 0x2343293] */
	m->esp -= 4; M32(m->esp) = 0x48a738u; native_call(m, 0x4685b0u);	/* 48a733: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48a738: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48a739: sub eax, edx */
	m->edx = M32((DWORD)(m->esi + 0x2343257u));	/* 48a73b: mov edx, dword ptr [esi + 0x2343257] */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48a741: sar eax, 1 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48a743: sub edx, eax */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 48a745: mov dword ptr [esp + 0x10], edx */
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x10u)));	/* 48a749: fild dword ptr [esp + 0x10] */
	ST(0) = -ST(0);	/* 48a74d: fchs  */
	MF((DWORD)(m->esi + 0x2343297u)) = (float)ST(0); FPOP();	/* 48a74f: fstp dword ptr [esi + 0x2343297] */
	m->esp -= 4; M32(m->esp) = 0x48a75au; native_call(m, 0x4685c0u);	/* 48a755: call 0x4685c0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48a75a: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48a75b: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48a75d: sar eax, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a75f: push eax */
	m->esp -= 4; M32(m->esp) = 0x48a765u; native_call(m, 0x4685b0u);	/* 48a760: call 0x4685b0 */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48a765: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48a766: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48a768: sar eax, 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a76a: push eax */
	m->esp -= 4; M32(m->esp) = 0x48a770u; native_call(m, 0x487c80u);	/* 48a76b: call 0x487c80 */
	{ DWORD v_ = 0x20u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a770: push 0x20 */
	m->esp -= 4; M32(m->esp) = 0x48a777u; native_call(m, 0x487bd0u);	/* 48a772: call 0x487bd0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a777: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a77a: test eax, eax */
	if (m->zf) goto L_48a786;	/* 48a77c: je 0x48a786 */
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebp;	/* 48a77e: mov dword ptr [esi + 0x23432cb], ebp */
	goto L_48a78c;	/* 48a784: jmp 0x48a78c */
L_48a786:
	M32((DWORD)(m->esi + 0x23432cbu)) = m->ebx;	/* 48a786: mov dword ptr [esi + 0x23432cb], ebx */
L_48a78c:
	{ DWORD v_ = 0x1bu; m->esp -= 4; M32(m->esp) = v_; }	/* 48a78c: push 0x1b */
	m->esp -= 4; M32(m->esp) = 0x48a793u; native_call(m, 0x487bd0u);	/* 48a78e: call 0x487bd0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a793: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a796: test eax, eax */
	if (m->zf) goto L_48a7a2;	/* 48a798: je 0x48a7a2 */
	M32((DWORD)(m->esi + 0x23432cfu)) = m->ebp;	/* 48a79a: mov dword ptr [esi + 0x23432cf], ebp */
	goto L_48a7a8;	/* 48a7a0: jmp 0x48a7a8 */
L_48a7a2:
	M32((DWORD)(m->esi + 0x23432cfu)) = m->ebx;	/* 48a7a2: mov dword ptr [esi + 0x23432cf], ebx */
L_48a7a8:
	{ DWORD v_ = 0x70u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a7a8: push 0x70 */
	m->esp -= 4; M32(m->esp) = 0x48a7afu; native_call(m, 0x487ba0u);	/* 48a7aa: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a7af: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a7b2: test eax, eax */
	if (m->zf) goto L_48a7be;	/* 48a7b4: je 0x48a7be */
	M32((DWORD)(m->esi + 0x23432d3u)) = m->ebp;	/* 48a7b6: mov dword ptr [esi + 0x23432d3], ebp */
	goto L_48a7c4;	/* 48a7bc: jmp 0x48a7c4 */
L_48a7be:
	M32((DWORD)(m->esi + 0x23432d3u)) = m->ebx;	/* 48a7be: mov dword ptr [esi + 0x23432d3], ebx */
L_48a7c4:
	{ DWORD v_ = 0x71u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a7c4: push 0x71 */
	m->esp -= 4; M32(m->esp) = 0x48a7cbu; native_call(m, 0x487ba0u);	/* 48a7c6: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a7cb: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a7ce: test eax, eax */
	if (m->zf) goto L_48a7da;	/* 48a7d0: je 0x48a7da */
	M32((DWORD)(m->esi + 0x23432d7u)) = m->ebp;	/* 48a7d2: mov dword ptr [esi + 0x23432d7], ebp */
	goto L_48a7e0;	/* 48a7d8: jmp 0x48a7e0 */
L_48a7da:
	M32((DWORD)(m->esi + 0x23432d7u)) = m->ebx;	/* 48a7da: mov dword ptr [esi + 0x23432d7], ebx */
L_48a7e0:
	{ DWORD v_ = 0x72u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a7e0: push 0x72 */
	m->esp -= 4; M32(m->esp) = 0x48a7e7u; native_call(m, 0x487ba0u);	/* 48a7e2: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a7e7: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a7ea: test eax, eax */
	if (m->zf) goto L_48a7f6;	/* 48a7ec: je 0x48a7f6 */
	M32((DWORD)(m->esi + 0x23432dbu)) = m->ebp;	/* 48a7ee: mov dword ptr [esi + 0x23432db], ebp */
	goto L_48a7fc;	/* 48a7f4: jmp 0x48a7fc */
L_48a7f6:
	M32((DWORD)(m->esi + 0x23432dbu)) = m->ebx;	/* 48a7f6: mov dword ptr [esi + 0x23432db], ebx */
L_48a7fc:
	{ DWORD v_ = 0x73u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a7fc: push 0x73 */
	m->esp -= 4; M32(m->esp) = 0x48a803u; native_call(m, 0x487ba0u);	/* 48a7fe: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a803: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a806: test eax, eax */
	if (m->zf) goto L_48a812;	/* 48a808: je 0x48a812 */
	M32((DWORD)(m->esi + 0x23432dfu)) = m->ebp;	/* 48a80a: mov dword ptr [esi + 0x23432df], ebp */
	goto L_48a818;	/* 48a810: jmp 0x48a818 */
L_48a812:
	M32((DWORD)(m->esi + 0x23432dfu)) = m->ebx;	/* 48a812: mov dword ptr [esi + 0x23432df], ebx */
L_48a818:
	{ DWORD v_ = 0x74u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a818: push 0x74 */
	m->esp -= 4; M32(m->esp) = 0x48a81fu; native_call(m, 0x487ba0u);	/* 48a81a: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a81f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a822: test eax, eax */
	if (m->zf) goto L_48a82e;	/* 48a824: je 0x48a82e */
	M32((DWORD)(m->esi + 0x23432e3u)) = m->ebp;	/* 48a826: mov dword ptr [esi + 0x23432e3], ebp */
	goto L_48a834;	/* 48a82c: jmp 0x48a834 */
L_48a82e:
	M32((DWORD)(m->esi + 0x23432e3u)) = m->ebx;	/* 48a82e: mov dword ptr [esi + 0x23432e3], ebx */
L_48a834:
	{ DWORD v_ = 0x75u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a834: push 0x75 */
	m->esp -= 4; M32(m->esp) = 0x48a83bu; native_call(m, 0x487ba0u);	/* 48a836: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a83b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a83e: test eax, eax */
	if (m->zf) goto L_48a84a;	/* 48a840: je 0x48a84a */
	M32((DWORD)(m->esi + 0x23432e7u)) = m->ebp;	/* 48a842: mov dword ptr [esi + 0x23432e7], ebp */
	goto L_48a850;	/* 48a848: jmp 0x48a850 */
L_48a84a:
	M32((DWORD)(m->esi + 0x23432e7u)) = m->ebx;	/* 48a84a: mov dword ptr [esi + 0x23432e7], ebx */
L_48a850:
	{ DWORD v_ = 0x5au; m->esp -= 4; M32(m->esp) = v_; }	/* 48a850: push 0x5a */
	m->esp -= 4; M32(m->esp) = 0x48a857u; native_call(m, 0x487bd0u);	/* 48a852: call 0x487bd0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a857: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a85a: test eax, eax */
	if (!m->zf) goto L_48a882;	/* 48a85c: jne 0x48a882 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a85e: push 0x10 */
	m->esp -= 4; M32(m->esp) = 0x48a865u; native_call(m, 0x487ba0u);	/* 48a860: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a865: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a868: test eax, eax */
	if (m->zf) goto L_48a87a;	/* 48a86a: je 0x48a87a */
	{ DWORD v_ = 0x5au; m->esp -= 4; M32(m->esp) = v_; }	/* 48a86c: push 0x5a */
	m->esp -= 4; M32(m->esp) = 0x48a873u; native_call(m, 0x487ba0u);	/* 48a86e: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a873: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a876: test eax, eax */
	if (!m->zf) goto L_48a882;	/* 48a878: jne 0x48a882 */
L_48a87a:
	M32((DWORD)(m->esi + 0x23432f3u)) = m->ebx;	/* 48a87a: mov dword ptr [esi + 0x23432f3], ebx */
	goto L_48a888;	/* 48a880: jmp 0x48a888 */
L_48a882:
	M32((DWORD)(m->esi + 0x23432f3u)) = m->ebp;	/* 48a882: mov dword ptr [esi + 0x23432f3], ebp */
L_48a888:
	{ DWORD v_ = 0x58u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a888: push 0x58 */
	m->esp -= 4; M32(m->esp) = 0x48a88fu; native_call(m, 0x487bd0u);	/* 48a88a: call 0x487bd0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a88f: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a892: test eax, eax */
	if (!m->zf) goto L_48a8ba;	/* 48a894: jne 0x48a8ba */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a896: push 0x10 */
	m->esp -= 4; M32(m->esp) = 0x48a89du; native_call(m, 0x487ba0u);	/* 48a898: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a89d: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a8a0: test eax, eax */
	if (m->zf) goto L_48a8b2;	/* 48a8a2: je 0x48a8b2 */
	{ DWORD v_ = 0x58u; m->esp -= 4; M32(m->esp) = v_; }	/* 48a8a4: push 0x58 */
	m->esp -= 4; M32(m->esp) = 0x48a8abu; native_call(m, 0x487ba0u);	/* 48a8a6: call 0x487ba0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48a8ab: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48a8ae: test eax, eax */
	if (!m->zf) goto L_48a8ba;	/* 48a8b0: jne 0x48a8ba */
L_48a8b2:
	M32((DWORD)(m->esi + 0x23432f7u)) = m->ebx;	/* 48a8b2: mov dword ptr [esi + 0x23432f7], ebx */
	goto L_48a8c0;	/* 48a8b8: jmp 0x48a8c0 */
L_48a8ba:
	M32((DWORD)(m->esi + 0x23432f7u)) = m->ebp;	/* 48a8ba: mov dword ptr [esi + 0x23432f7], ebp */
L_48a8c0:
	m->ecx = m->esi;	/* 48a8c0: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48a8c7u; { long double r_ = native_call_fp(m, 0x461210u); FPUSH(r_); }	/* 48a8c2: call 0x461210 */
	ST(0) = ST(0); FPOP();	/* 48a8c7: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 48a8c9: fld dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa488u));	/* 48a8cc: fmul dword ptr [0x4aa488] */
	m->eax = M32((DWORD)(m->esi + 0x2343287u));	/* 48a8d2: mov eax, dword ptr [esi + 0x2343287] */
	m->ecx = M32((DWORD)(m->esi + 0x2343283u));	/* 48a8d8: mov ecx, dword ptr [esi + 0x2343283] */
	m->edx = M32((DWORD)(m->esi + 0x234325fu));	/* 48a8de: mov edx, dword ptr [esi + 0x234325f] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a8e4: push ebx */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 48a8e5: fsubr dword ptr [0x4a9424] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a8eb: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a8ec: push eax */
	m->eax = M32((DWORD)(m->esi + 0x234327bu));	/* 48a8ed: mov eax, dword ptr [esi + 0x234327b] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a8f3: push ecx */
	MF((DWORD)(m->esp + 0x20u)) = (float)ST(0); FPOP();	/* 48a8f4: fstp dword ptr [esp + 0x20] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 48a8f8: fld dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa484u));	/* 48a8fb: fmul dword ptr [0x4aa484] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a901: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a902: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a903: push ecx */
	m->edx = M32((DWORD)(m->esi + 0x234326bu));	/* 48a904: mov edx, dword ptr [esi + 0x234326b] */
	m->eax = M32((DWORD)(m->esi + 0x2343267u));	/* 48a90a: mov eax, dword ptr [esi + 0x2343267] */
	m->ebp = (DWORD)(m->esi + 0x1f36c8u);	/* 48a910: lea ebp, [esi + 0x1f36c8] */
	MF((DWORD)(m->esp + 0x4cu)) = (float)ST(0); FPOP();	/* 48a916: fstp dword ptr [esp + 0x4c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x44u)));	/* 48a91a: fld dword ptr [esi + 0x44] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93f4u));	/* 48a91d: fmul dword ptr [0x4a93f4] */
	{ long double t = ST(0); FPUSH(t); }	/* 48a923: fld st(0) */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343297u));	/* 48a925: fmul dword ptr [esi + 0x2343297] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48a92b: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a92e: push ecx */
	m->ecx = M32((DWORD)(m->esi + 0x234326fu));	/* 48a92f: mov ecx, dword ptr [esi + 0x234326f] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + 0x2343293u));	/* 48a935: fmul dword ptr [esi + 0x2343293] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48a93b: fstp dword ptr [esp] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a93e: push ecx */
	m->ecx = M32((DWORD)(m->esi + 0x2343263u));	/* 48a93f: mov ecx, dword ptr [esi + 0x2343263] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a945: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48a946: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a947: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48a948: push ebx */
	m->ecx = m->ebp;	/* 48a949: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48a950u; native_call(m, 0x45eb20u);	/* 48a94b: call 0x45eb20 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432bbu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a950: cmp dword ptr [esi + 0x23432bb], ebx */
	if (m->zf) goto L_48a97f;	/* 48a956: je 0x48a97f */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 48a958: fld dword ptr [esi + 0x233ca28] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 48a95e: fsub dword ptr [esp + 0x30] */
	MF((DWORD)(m->esi + 0x233ca28u)) = (float)ST(0);	/* 48a962: fst dword ptr [esi + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9728u)); FPOP();	/* 48a968: fcomp dword ptr [0x4a9728] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48a96e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48a970: test ah, 1 */
	if (m->zf) goto L_48a97f;	/* 48a973: je 0x48a97f */
	M32((DWORD)(m->esi + 0x233ca28u)) = 0xc45e8000u;	/* 48a975: mov dword ptr [esi + 0x233ca28], 0xc45e8000 */
L_48a97f:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432bfu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a97f: cmp dword ptr [esi + 0x23432bf], ebx */
	if (m->zf) goto L_48a9ae;	/* 48a985: je 0x48a9ae */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 48a987: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x233ca28u));	/* 48a98b: fadd dword ptr [esi + 0x233ca28] */
	MF((DWORD)(m->esi + 0x233ca28u)) = (float)ST(0);	/* 48a991: fst dword ptr [esi + 0x233ca28] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a972cu)); FPOP();	/* 48a997: fcomp dword ptr [0x4a972c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48a99d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48a99f: test ah, 0x41 */
	if (!m->zf) goto L_48a9ae;	/* 48a9a2: jne 0x48a9ae */
	M32((DWORD)(m->esi + 0x233ca28u)) = 0x445e8000u;	/* 48a9a4: mov dword ptr [esi + 0x233ca28], 0x445e8000 */
L_48a9ae:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432b3u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a9ae: cmp dword ptr [esi + 0x23432b3], ebx */
	if (m->zf) goto L_48a9e3;	/* 48a9b4: je 0x48a9e3 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 48a9b6: fld dword ptr [esi + 0x233ca2c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->esp + 0x30u));	/* 48a9bc: fsub dword ptr [esp + 0x30] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u));	/* 48a9c0: fcom dword ptr [0x4a93e8] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0);	/* 48a9c6: fst dword ptr [esi + 0x233ca2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48a9cc: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48a9ce: test ah, 1 */
	if (m->zf) goto L_48a9e1;	/* 48a9d1: je 0x48a9e1 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 48a9d3: fadd dword ptr [0x4a94c8] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 48a9d9: fstp dword ptr [esi + 0x233ca2c] */
	goto L_48a9e3;	/* 48a9df: jmp 0x48a9e3 */
L_48a9e1:
	ST(0) = ST(0); FPOP();	/* 48a9e1: fstp st(0) */
L_48a9e3:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432b7u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48a9e3: cmp dword ptr [esi + 0x23432b7], ebx */
	if (m->zf) goto L_48aa18;	/* 48a9e9: je 0x48aa18 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 48a9eb: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->esi + 0x233ca2cu));	/* 48a9ef: fadd dword ptr [esi + 0x233ca2c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a94c8u));	/* 48a9f5: fcom dword ptr [0x4a94c8] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0);	/* 48a9fb: fst dword ptr [esi + 0x233ca2c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48aa01: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48aa03: test ah, 1 */
	if (!m->zf) goto L_48aa16;	/* 48aa06: jne 0x48aa16 */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4a94c8u));	/* 48aa08: fsub dword ptr [0x4a94c8] */
	MF((DWORD)(m->esi + 0x233ca2cu)) = (float)ST(0); FPOP();	/* 48aa0e: fstp dword ptr [esi + 0x233ca2c] */
	goto L_48aa18;	/* 48aa14: jmp 0x48aa18 */
L_48aa16:
	ST(0) = ST(0); FPOP();	/* 48aa16: fstp st(0) */
L_48aa18:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432abu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48aa18: cmp dword ptr [esi + 0x23432ab], ebx */
	if (m->zf) goto L_48aa61;	/* 48aa1e: je 0x48aa61 */
	m->edx = M32((DWORD)(m->esi + 0x233cc10u));	/* 48aa20: mov edx, dword ptr [esi + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x10u)));	/* 48aa26: fld dword ptr [esp + 0x10] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(m->esi + m->edx*4 + 0x233cb70u));	/* 48aa2a: fmul dword ptr [esi + edx*4 + 0x233cb70] */
	m->eax = (DWORD)(m->esi + m->edx*4 + 0x233cb70u);	/* 48aa31: lea eax, [esi + edx*4 + 0x233cb70] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 48aa38: fstp dword ptr [eax] */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48aa3a: mov eax, dword ptr [esi + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->eax*4 + 0x233cb70u)));	/* 48aa40: fld dword ptr [esi + eax*4 + 0x233cb70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9450u)); FPOP();	/* 48aa47: fcomp dword ptr [0x4a9450] */
	m->ecx = (DWORD)(m->esi + m->eax*4 + 0x233cb70u);	/* 48aa4d: lea ecx, [esi + eax*4 + 0x233cb70] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48aa54: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48aa56: test ah, 1 */
	if (m->zf) goto L_48aa61;	/* 48aa59: je 0x48aa61 */
	M32((DWORD)(m->ecx + 0x0u)) = 0x43fa0000u;	/* 48aa5b: mov dword ptr [ecx], 0x43fa0000 */
L_48aa61:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432afu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48aa61: cmp dword ptr [esi + 0x23432af], ebx */
	if (m->zf) goto L_48aaaa;	/* 48aa67: je 0x48aaaa */
	m->ecx = M32((DWORD)(m->esi + 0x233cc10u));	/* 48aa69: mov ecx, dword ptr [esi + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*4 + 0x233cb70u)));	/* 48aa6f: fld dword ptr [esi + ecx*4 + 0x233cb70] */
	ST(0) = x87_divm(ST(0), (const float *)(DWORD)(m->esp + 0x10u));	/* 48aa76: fdiv dword ptr [esp + 0x10] */
	m->eax = (DWORD)(m->esi + m->ecx*4 + 0x233cb70u);	/* 48aa7a: lea eax, [esi + ecx*4 + 0x233cb70] */
	MF((DWORD)(m->eax + 0x0u)) = (float)ST(0); FPOP();	/* 48aa81: fstp dword ptr [eax] */
	m->edx = M32((DWORD)(m->esi + 0x233cc10u));	/* 48aa83: mov edx, dword ptr [esi + 0x233cc10] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->edx*4 + 0x233cb70u)));	/* 48aa89: fld dword ptr [esi + edx*4 + 0x233cb70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9708u)); FPOP();	/* 48aa90: fcomp dword ptr [0x4a9708] */
	m->ecx = (DWORD)(m->esi + m->edx*4 + 0x233cb70u);	/* 48aa96: lea ecx, [esi + edx*4 + 0x233cb70] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48aa9d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48aa9f: test ah, 0x41 */
	if (!m->zf) goto L_48aaaa;	/* 48aaa2: jne 0x48aaaa */
	M32((DWORD)(m->ecx + 0x0u)) = 0x461c4000u;	/* 48aaa4: mov dword ptr [ecx], 0x461c4000 */
L_48aaaa:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432cbu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48aaaa: cmp dword ptr [esi + 0x23432cb], ebx */
	if (m->zf) goto L_48aae7;	/* 48aab0: je 0x48aae7 */
	m->eax = M32((DWORD)(m->esi + 0x233cc10u));	/* 48aab2: mov eax, dword ptr [esi + 0x233cc10] */
	M32((DWORD)(m->esi + m->eax*4 + 0x233cb70u)) = 0x44fa0000u;	/* 48aab8: mov dword ptr [esi + eax*4 + 0x233cb70], 0x44fa0000 */
	M32((DWORD)(m->esi + 0x233ca28u)) = m->ebx;	/* 48aac3: mov dword ptr [esi + 0x233ca28], ebx */
	M32((DWORD)(m->esi + 0x233ca2cu)) = m->ebx;	/* 48aac9: mov dword ptr [esi + 0x233ca2c], ebx */
	M32((DWORD)(m->edi + 0x160u)) = m->ebx;	/* 48aacf: mov dword ptr [edi + 0x160], ebx */
	M32((DWORD)(m->edi + 0x164u)) = m->ebx;	/* 48aad5: mov dword ptr [edi + 0x164], ebx */
	M32((DWORD)(m->edi + 0x18cu)) = m->ebx;	/* 48aadb: mov dword ptr [edi + 0x18c], ebx */
	M32((DWORD)(m->edi + 0x190u)) = m->ebx;	/* 48aae1: mov dword ptr [edi + 0x190], ebx */
L_48aae7:
	m->eax = M32((DWORD)(m->esi + 0x23432f3u));	/* 48aae7: mov eax, dword ptr [esi + 0x23432f3] */
	m->ecx = 0x1u;	/* 48aaed: mov ecx, 1 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48aaf2: cmp eax, ecx */
	if (!m->zf) goto L_48abfe;	/* 48aaf4: jne 0x48abfe */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432d3u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48aafa: cmp dword ptr [esi + 0x23432d3], ecx */
	if (!m->zf) goto L_48ab25;	/* 48ab00: jne 0x48ab25 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48ab02: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edx + 0x30cu));	/* 48ab06: mov eax, dword ptr [edx + 0x30c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ab0c: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_48ab25;	/* 48ab0e: jle 0x48ab25 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48ab10: dec eax */
	m->ecx = m->ebp;	/* 48ab11: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ab13: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48ab14: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ab1a: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ab20u; native_call(m, 0x473b10u);	/* 48ab1b: call 0x473b10 */
	m->ecx = 0x1u;	/* 48ab20: mov ecx, 1 */
L_48ab25:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432d7u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ab25: cmp dword ptr [esi + 0x23432d7], ecx */
	if (!m->zf) goto L_48ab50;	/* 48ab2b: jne 0x48ab50 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48ab2d: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edx + 0x310u));	/* 48ab31: mov eax, dword ptr [edx + 0x310] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ab37: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_48ab50;	/* 48ab39: jle 0x48ab50 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48ab3b: dec eax */
	m->ecx = m->ebp;	/* 48ab3c: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ab3e: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48ab3f: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ab45: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ab4bu; native_call(m, 0x473c20u);	/* 48ab46: call 0x473c20 */
	m->ecx = 0x1u;	/* 48ab4b: mov ecx, 1 */
L_48ab50:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432dbu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ab50: cmp dword ptr [esi + 0x23432db], ecx */
	if (!m->zf) goto L_48ab7b;	/* 48ab56: jne 0x48ab7b */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48ab58: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edx + 0x314u));	/* 48ab5c: mov eax, dword ptr [edx + 0x314] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ab62: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_48ab7b;	/* 48ab64: jle 0x48ab7b */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48ab66: dec eax */
	m->ecx = m->ebp;	/* 48ab67: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ab69: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48ab6a: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ab70: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ab76u; native_call(m, 0x473d30u);	/* 48ab71: call 0x473d30 */
	m->ecx = 0x1u;	/* 48ab76: mov ecx, 1 */
L_48ab7b:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432dfu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ab7b: cmp dword ptr [esi + 0x23432df], ecx */
	if (!m->zf) goto L_48aba6;	/* 48ab81: jne 0x48aba6 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48ab83: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edx + 0x318u));	/* 48ab87: mov eax, dword ptr [edx + 0x318] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ab8d: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_48aba6;	/* 48ab8f: jle 0x48aba6 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48ab91: dec eax */
	m->ecx = m->ebp;	/* 48ab92: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ab94: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48ab95: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ab9b: push eax */
	m->esp -= 4; M32(m->esp) = 0x48aba1u; native_call(m, 0x473e40u);	/* 48ab9c: call 0x473e40 */
	m->ecx = 0x1u;	/* 48aba1: mov ecx, 1 */
L_48aba6:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432e3u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48aba6: cmp dword ptr [esi + 0x23432e3], ecx */
	if (!m->zf) goto L_48abd1;	/* 48abac: jne 0x48abd1 */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48abae: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edx + 0x31cu));	/* 48abb2: mov eax, dword ptr [edx + 0x31c] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48abb8: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_48abd1;	/* 48abba: jle 0x48abd1 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48abbc: dec eax */
	m->ecx = m->ebp;	/* 48abbd: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48abbf: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48abc0: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48abc6: push eax */
	m->esp -= 4; M32(m->esp) = 0x48abccu; native_call(m, 0x473f50u);	/* 48abc7: call 0x473f50 */
	m->ecx = 0x1u;	/* 48abcc: mov ecx, 1 */
L_48abd1:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432e7u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48abd1: cmp dword ptr [esi + 0x23432e7], ecx */
	if (!m->zf) goto L_48ad4e;	/* 48abd7: jne 0x48ad4e */
	m->ecx = M32((DWORD)(m->edi + 0x140u));	/* 48abdd: mov ecx, dword ptr [edi + 0x140] */
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 48abe3: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0x320u));	/* 48abe7: mov eax, dword ptr [edx + ecx*4 + 0x320] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48abee: cmp eax, ebx */
	if (m->zf || m->sf != m->of) goto L_48ad4e;	/* 48abf0: jle 0x48ad4e */
	m->ecx = (DWORD)(m->eax + 0xffffffffu);	/* 48abf6: lea ecx, [eax - 1] */
	goto L_48ad19;	/* 48abf9: jmp 0x48ad19 */
L_48abfe:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432f7u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48abfe: cmp dword ptr [esi + 0x23432f7], ecx */
	if (!m->zf) goto L_48ad4e;	/* 48ac04: jne 0x48ad4e */
	m->eax = M32((DWORD)(m->esi + 0x23432d3u));	/* 48ac0a: mov eax, dword ptr [esi + 0x23432d3] */
	m->ebx = M32((DWORD)(m->esp + 0x14u));	/* 48ac10: mov ebx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ac14: cmp eax, ecx */
	if (!m->zf) goto L_48ac3e;	/* 48ac16: jne 0x48ac3e */
	m->edx = M32((DWORD)(m->esi + 0x15de6c8u));	/* 48ac18: mov edx, dword ptr [esi + 0x15de6c8] */
	m->eax = M32((DWORD)(m->ebx + 0x30cu));	/* 48ac1e: mov eax, dword ptr [ebx + 0x30c] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48ac24: dec edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ac25: cmp eax, edx */
	if (m->sf == m->of) goto L_48ac3e;	/* 48ac27: jge 0x48ac3e */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48ac29: inc eax */
	m->ecx = m->ebp;	/* 48ac2a: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ac2c: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48ac2d: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ac33: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ac39u; native_call(m, 0x473b10u);	/* 48ac34: call 0x473b10 */
	m->ecx = 0x1u;	/* 48ac39: mov ecx, 1 */
L_48ac3e:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432d7u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ac3e: cmp dword ptr [esi + 0x23432d7], ecx */
	if (!m->zf) goto L_48ac6c;	/* 48ac44: jne 0x48ac6c */
	m->edx = M32((DWORD)(m->esi + 0x15fff84u));	/* 48ac46: mov edx, dword ptr [esi + 0x15fff84] */
	m->eax = M32((DWORD)(m->ebx + 0x310u));	/* 48ac4c: mov eax, dword ptr [ebx + 0x310] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48ac52: dec edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ac53: cmp eax, edx */
	if (m->sf == m->of) goto L_48ac6c;	/* 48ac55: jge 0x48ac6c */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48ac57: inc eax */
	m->ecx = m->ebp;	/* 48ac58: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ac5a: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48ac5b: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ac61: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ac67u; native_call(m, 0x473c20u);	/* 48ac62: call 0x473c20 */
	m->ecx = 0x1u;	/* 48ac67: mov ecx, 1 */
L_48ac6c:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432dbu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ac6c: cmp dword ptr [esi + 0x23432db], ecx */
	if (!m->zf) goto L_48ac9a;	/* 48ac72: jne 0x48ac9a */
	m->edx = M32((DWORD)(m->esi + 0x163b588u));	/* 48ac74: mov edx, dword ptr [esi + 0x163b588] */
	m->eax = M32((DWORD)(m->ebx + 0x314u));	/* 48ac7a: mov eax, dword ptr [ebx + 0x314] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48ac80: dec edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ac81: cmp eax, edx */
	if (m->sf == m->of) goto L_48ac9a;	/* 48ac83: jge 0x48ac9a */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48ac85: inc eax */
	m->ecx = m->ebp;	/* 48ac86: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ac88: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48ac89: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ac8f: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ac95u; native_call(m, 0x473d30u);	/* 48ac90: call 0x473d30 */
	m->ecx = 0x1u;	/* 48ac95: mov ecx, 1 */
L_48ac9a:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432dfu)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ac9a: cmp dword ptr [esi + 0x23432df], ecx */
	if (!m->zf) goto L_48acc8;	/* 48aca0: jne 0x48acc8 */
	m->edx = M32((DWORD)(m->esi + 0x1679b34u));	/* 48aca2: mov edx, dword ptr [esi + 0x1679b34] */
	m->eax = M32((DWORD)(m->ebx + 0x318u));	/* 48aca8: mov eax, dword ptr [ebx + 0x318] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48acae: dec edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48acaf: cmp eax, edx */
	if (m->sf == m->of) goto L_48acc8;	/* 48acb1: jge 0x48acc8 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48acb3: inc eax */
	m->ecx = m->ebp;	/* 48acb4: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48acb6: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48acb7: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48acbd: push eax */
	m->esp -= 4; M32(m->esp) = 0x48acc3u; native_call(m, 0x473e40u);	/* 48acbe: call 0x473e40 */
	m->ecx = 0x1u;	/* 48acc3: mov ecx, 1 */
L_48acc8:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432e3u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48acc8: cmp dword ptr [esi + 0x23432e3], ecx */
	if (!m->zf) goto L_48acf6;	/* 48acce: jne 0x48acf6 */
	m->edx = M32((DWORD)(m->esi + 0x16c5178u));	/* 48acd0: mov edx, dword ptr [esi + 0x16c5178] */
	m->eax = M32((DWORD)(m->ebx + 0x31cu));	/* 48acd6: mov eax, dword ptr [ebx + 0x31c] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48acdc: dec edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48acdd: cmp eax, edx */
	if (m->sf == m->of) goto L_48acf6;	/* 48acdf: jge 0x48acf6 */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48ace1: inc eax */
	m->ecx = m->ebp;	/* 48ace2: mov ecx, ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ace4: push eax */
	m->eax = M32((DWORD)(m->edi + 0x10cu));	/* 48ace5: mov eax, dword ptr [edi + 0x10c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48aceb: push eax */
	m->esp -= 4; M32(m->esp) = 0x48acf1u; native_call(m, 0x473f50u);	/* 48acec: call 0x473f50 */
	m->ecx = 0x1u;	/* 48acf1: mov ecx, 1 */
L_48acf6:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x23432e7u)), b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48acf6: cmp dword ptr [esi + 0x23432e7], ecx */
	if (!m->zf) goto L_48ad4e;	/* 48acfc: jne 0x48ad4e */
	m->ecx = M32((DWORD)(m->edi + 0x140u));	/* 48acfe: mov ecx, dword ptr [edi + 0x140] */
	m->edx = M32((DWORD)(m->esi + 0x175522cu));	/* 48ad04: mov edx, dword ptr [esi + 0x175522c] */
	{ DWORD a_ = m->edx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edx = r_; }	/* 48ad0a: dec edx */
	m->eax = M32((DWORD)(m->ebx + m->ecx*4 + 0x320u));	/* 48ad0b: mov eax, dword ptr [ebx + ecx*4 + 0x320] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ad12: cmp eax, edx */
	if (m->sf == m->of) goto L_48ad4e;	/* 48ad14: jge 0x48ad4e */
	m->ecx = (DWORD)(m->eax + 0x1u);	/* 48ad16: lea ecx, [eax + 1] */
L_48ad19:
	m->eax = m->ecx;	/* 48ad19: mov eax, ecx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad1b: push ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ad1c: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ad1f: sub eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48ad21: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ad24: sub eax, ecx */
	m->ecx = m->ebp;	/* 48ad26: mov ecx, ebp */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48ad28: lea eax, [eax + eax*4] */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48ad2b: lea eax, [eax + eax*4] */
	m->ebx = M32((DWORD)(m->esi + m->eax*8 + 0x16c7f38u));	/* 48ad2e: mov ebx, dword ptr [esi + eax*8 + 0x16c7f38] */
	{ DWORD a_ = m->ebx, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->ebx = r_; }	/* 48ad35: neg ebx */
	{ DWORD a_ = m->ebx, b_ = m->ebx, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->ebx = r_; }	/* 48ad37: sbb ebx, ebx */
	{ DWORD a_ = m->ebx, b_ = 0x4u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48ad39: and ebx, 4 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad3c: push ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad3d: push 0 */
	m->esp -= 4; M32(m->esp) = 0x48ad44u; native_call(m, 0x474060u);	/* 48ad3f: call 0x474060 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad44: push ebx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad45: push 0 */
	m->ecx = m->ebp;	/* 48ad47: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48ad4eu; native_call(m, 0x45e880u);	/* 48ad49: call 0x45e880 */
L_48ad4e:
	m->ecx = M32((DWORD)(m->esi + 0x233cc10u));	/* 48ad4e: mov ecx, dword ptr [esi + 0x233cc10] */
	m->ebx = (DWORD)(m->esi + 0x233ca04u);	/* 48ad54: lea ebx, [esi + 0x233ca04] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + m->ecx*4 + 0x233cb70u)));	/* 48ad5a: fld dword ptr [esi + ecx*4 + 0x233cb70] */
	M32((DWORD)(m->ebx + 0x0u)) = 0x0u;	/* 48ad61: mov dword ptr [ebx], 0 */
	M32((DWORD)(m->ebx + 0x4u)) = 0x0u;	/* 48ad67: mov dword ptr [ebx + 4], 0 */
	MF((DWORD)(m->ebx + 0x8u)) = (float)ST(0); FPOP();	/* 48ad6e: fstp dword ptr [ebx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 48ad71: fld dword ptr [esi + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48ad77: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad7c: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad7d: push 1 */
	m->ecx = m->ebx;	/* 48ad7f: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48ad86u; native_call(m, 0x4677c0u);	/* 48ad81: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 48ad86: fld dword ptr [esi + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48ad8c: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad91: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ad92: push 2 */
	m->ecx = m->ebx;	/* 48ad94: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48ad9bu; native_call(m, 0x4677c0u);	/* 48ad96: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x180u)));	/* 48ad9b: fld dword ptr [edi + 0x180] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 48ada1: fadd dword ptr [ebx] */
	m->eax = (DWORD)(m->esi + 0x233ca10u);	/* 48ada3: lea eax, [esi + 0x233ca10] */
	m->ebp = (DWORD)(m->esi + 0x233ca1cu);	/* 48ada9: lea ebp, [esi + 0x233ca1c] */
	MF((DWORD)(m->ebx + 0x0u)) = (float)ST(0); FPOP();	/* 48adaf: fstp dword ptr [ebx] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x184u)));	/* 48adb1: fld dword ptr [edi + 0x184] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 48adb7: fadd dword ptr [ebx + 4] */
	MF((DWORD)(m->ebx + 0x4u)) = (float)ST(0); FPOP();	/* 48adba: fstp dword ptr [ebx + 4] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x188u)));	/* 48adbd: fld dword ptr [edi + 0x188] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 48adc3: fadd dword ptr [ebx + 8] */
	MF((DWORD)(m->ebx + 0x8u)) = (float)ST(0); FPOP();	/* 48adc6: fstp dword ptr [ebx + 8] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x180u)));	/* 48adc9: fld dword ptr [edi + 0x180] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x0u));	/* 48adcf: fsub dword ptr [ebx] */
	MF((DWORD)(m->esp + 0x34u)) = (float)ST(0); FPOP();	/* 48add1: fstp dword ptr [esp + 0x34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x184u)));	/* 48add5: fld dword ptr [edi + 0x184] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x4u));	/* 48addb: fsub dword ptr [ebx + 4] */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 48adde: mov edx, dword ptr [esp + 0x34] */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 48ade2: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x188u)));	/* 48ade6: fld dword ptr [edi + 0x188] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(m->ebx + 0x8u));	/* 48adec: fsub dword ptr [ebx + 8] */
	m->ecx = M32((DWORD)(m->esp + 0x38u));	/* 48adef: mov ecx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->eax + 0x0u)) = m->edx;	/* 48adf3: mov dword ptr [eax], edx */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 48adf5: fstp dword ptr [esp + 0x3c] */
	m->edx = M32((DWORD)(m->esp + 0x3cu));	/* 48adf9: mov edx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->eax + 0x4u)) = m->ecx;	/* 48adfd: mov dword ptr [eax + 4], ecx */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 48ae00: mov dword ptr [eax + 8], edx */
	M32((DWORD)(m->ebp + 0x0u)) = 0x0u;	/* 48ae03: mov dword ptr [ebp], 0 */
	M32((DWORD)(m->ebp + 0x4u)) = 0x3f800000u;	/* 48ae0a: mov dword ptr [ebp + 4], 0x3f800000 */
	M32((DWORD)(m->ebp + 0x8u)) = 0x0u;	/* 48ae11: mov dword ptr [ebp + 8], 0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca28u)));	/* 48ae18: fld dword ptr [esi + 0x233ca28] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48ae1e: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae23: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae24: push 1 */
	m->ecx = m->ebp;	/* 48ae26: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48ae2du; native_call(m, 0x4677c0u);	/* 48ae28: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x233ca2cu)));	/* 48ae2d: fld dword ptr [esi + 0x233ca2c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48ae33: call 0x49ec14 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae38: push eax */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae39: push 2 */
	m->ecx = m->ebp;	/* 48ae3b: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x48ae42u; native_call(m, 0x4677c0u);	/* 48ae3d: call 0x4677c0 */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 48ae42: mov eax, dword ptr [esi + 0x44] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae45: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ae4bu; { long double r_ = native_call_fp(m, 0x468700u); FPUSH(r_); }	/* 48ae46: call 0x468700 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae4b: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48ae4c: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x48ae54u; { long double r_ = native_call_fp(m, 0x4686f0u); FPUSH(r_); }	/* 48ae4f: call 0x4686f0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae54: push ecx */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48ae55: fstp dword ptr [esp] */
	m->esp -= 4; M32(m->esp) = 0x48ae5du; native_call(m, 0x4685c0u);	/* 48ae58: call 0x4685c0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae5d: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ae63u; native_call(m, 0x4685b0u);	/* 48ae5e: call 0x4685b0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae63: push eax */
	m->esp -= 4; M32(m->esp) = 0x48ae69u; { long double r_ = native_call_fp(m, 0x4686d0u); FPUSH(r_); }	/* 48ae64: call 0x4686d0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae69: push ecx */
	m->eax = (DWORD)(m->esi + 0x233ca10u);	/* 48ae6a: lea eax, [esi + 0x233ca10] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 48ae70: fstp dword ptr [esp] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae73: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae74: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae75: push ebx */
	m->ecx = (DWORD)(m->esi + 0x1f36c8u);	/* 48ae76: lea ecx, [esi + 0x1f36c8] */
	m->esp -= 4; M32(m->esp) = 0x48ae81u; native_call(m, 0x4729b0u);	/* 48ae7c: call 0x4729b0 */
	m->eax = M32((DWORD)(m->esi + 0x2340ce0u));	/* 48ae81: mov eax, dword ptr [esi + 0x2340ce0] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48ae87: test eax, eax */
	if (!m->zf) goto L_48aee7;	/* 48ae89: jne 0x48aee7 */
	m->ecx = M32((DWORD)(m->esi + 0x44u));	/* 48ae8b: mov ecx, dword ptr [esi + 0x44] */
	m->ebx = (DWORD)(m->esi + 0x1f36c8u);	/* 48ae8e: lea ebx, [esi + 0x1f36c8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ae94: push ecx */
	m->ecx = m->ebx;	/* 48ae95: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48ae9cu; native_call(m, 0x45e0c0u);	/* 48ae97: call 0x45e0c0 */
	m->edx = M32((DWORD)(m->esi + 0x44u));	/* 48ae9c: mov edx, dword ptr [esi + 0x44] */
	m->ecx = m->ebx;	/* 48ae9f: mov ecx, ebx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48aea1: push edx */
	m->esp -= 4; M32(m->esp) = 0x48aea7u; native_call(m, 0x47d000u);	/* 48aea2: call 0x47d000 */
	m->eax = M32((DWORD)(m->esi + 0x44u));	/* 48aea7: mov eax, dword ptr [esi + 0x44] */
	m->ecx = m->ebx;	/* 48aeaa: mov ecx, ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48aeac: push eax */
	m->esp -= 4; M32(m->esp) = 0x48aeb2u; native_call(m, 0x479a90u);	/* 48aead: call 0x479a90 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48aeb2: xor ecx, ecx */
L_48aeb4:
	m->eax = M32((DWORD)(m->esi + 0x234240du));	/* 48aeb4: mov eax, dword ptr [esi + 0x234240d] */
	m->edx = m->eax;	/* 48aeba: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48aebc: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48aebf: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48aec1: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48aec4: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48aec6: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48aec9: add edx, eax */
	m->ebx = (DWORD)(m->ecx + m->edx*2 + 0x0u);	/* 48aecb: lea ebx, [ecx + edx*2] */
	m->eax = M32((DWORD)(m->esi + m->ebx*4 + 0x1ecca98u));	/* 48aece: mov eax, dword ptr [esi + ebx*4 + 0x1ecca98] */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48aed5: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48aed6: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48aed8: sar eax, 1 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48aeda: inc ecx */
	M32((DWORD)(m->esi + m->ebx*4 + 0x1eccba0u)) = m->eax;	/* 48aedb: mov dword ptr [esi + ebx*4 + 0x1eccba0], eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48aee2: cmp ecx, 4 */
	if (m->sf != m->of) goto L_48aeb4;	/* 48aee5: jl 0x48aeb4 */
L_48aee7:
	m->ebx = M32((DWORD)(m->esi + 0x233cc28u));	/* 48aee7: mov ebx, dword ptr [esi + 0x233cc28] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48aeed: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48aef2: push 0x3f800000 */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 48aef7: inc ebx */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48aef8: push 0x3f000000 */
	{ DWORD v_ = 0x3dcccccdu; m->esp -= 4; M32(m->esp) = v_; }	/* 48aefd: push 0x3dcccccd */
	M32((DWORD)(m->esi + 0x233cc28u)) = m->ebx;	/* 48af02: mov dword ptr [esi + 0x233cc28], ebx */
	m->esp -= 4; M32(m->esp) = 0x48af0eu; native_call(m, M32(0x4a91e0u));	/* 48af08: call dword ptr [0x4a91e0] */
	{ DWORD v_ = 0x3ff00000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48af0e: push 0x3ff00000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48af13: push 0 */
	m->esp -= 4; M32(m->esp) = 0x48af1bu; native_call(m, M32(0x4a91dcu));	/* 48af15: call dword ptr [0x4a91dc] */
	{ DWORD v_ = 0x4100u; m->esp -= 4; M32(m->esp) = v_; }	/* 48af1b: push 0x4100 */
	m->esp -= 4; M32(m->esp) = 0x48af26u; native_call(m, M32(0x4a91e8u));	/* 48af20: call dword ptr [0x4a91e8] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48af26: push 0x3f800000 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48af2b: push 1 */
	m->esp -= 4; M32(m->esp) = 0x48af32u; native_call(m, 0x4685f0u);	/* 48af2d: call 0x4685f0 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48af32: add esp, 8 */
	m->eax = (DWORD)(m->esi + 0x22e7068u);	/* 48af35: lea eax, [esi + 0x22e7068] */
	m->ebx = (DWORD)(m->esi + 0x74u);	/* 48af3b: lea ebx, [esi + 0x74] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48af3e: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48af3f: push 0 */
	m->ecx = m->ebx;	/* 48af41: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48af48u; native_call(m, 0x4841f0u);	/* 48af43: call 0x4841f0 */
	m->ecx = m->ebx;	/* 48af48: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48af4fu; native_call(m, 0x484260u);	/* 48af4a: call 0x484260 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x2340cd0u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48af4f: cmp dword ptr [esi + 0x2340cd0], 1 */
	if (!m->zf) goto L_48b19f;	/* 48af56: jne 0x48b19f */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48af5c: xor ebp, ebp */
L_48af5e:
	m->ecx = (DWORD)(m->ebp + 0x64u);	/* 48af5e: lea ecx, [ebp + 0x64] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48af61: xor ebx, ebx */
	M32((DWORD)(m->esp + 0x10u)) = m->ecx;	/* 48af63: mov dword ptr [esp + 0x10], ecx */
L_48af67:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48af67: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48af68: push 1 */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 48af6a: lea ecx, [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 48af6e: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x461c4000u;	/* 48af76: mov dword ptr [esp + 0x30], 0x461c4000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 48af7e: mov dword ptr [esp + 0x34], 0 */
	m->esp -= 4; M32(m->esp) = 0x48af8bu; native_call(m, 0x4677c0u);	/* 48af86: call 0x4677c0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48af8b: push ebx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48af8c: push 2 */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 48af8e: lea ecx, [esp + 0x2c] */
	m->esp -= 4; M32(m->esp) = 0x48af97u; native_call(m, 0x4677c0u);	/* 48af92: call 0x4677c0 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 48af97: mov edx, dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 48af9b: lea ecx, [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48af9f: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48afa0: push 1 */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 48afa2: mov dword ptr [esp + 0x20], 0 */
	M32((DWORD)(m->esp + 0x24u)) = 0x461c4000u;	/* 48afaa: mov dword ptr [esp + 0x24], 0x461c4000 */
	M32((DWORD)(m->esp + 0x28u)) = 0x0u;	/* 48afb2: mov dword ptr [esp + 0x28], 0 */
	m->esp -= 4; M32(m->esp) = 0x48afbfu; native_call(m, 0x4677c0u);	/* 48afba: call 0x4677c0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48afbf: push ebx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48afc0: push 2 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 48afc2: lea ecx, [esp + 0x20] */
	m->esp -= 4; M32(m->esp) = 0x48afcbu; native_call(m, 0x4677c0u);	/* 48afc6: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 48afcb: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x154u));	/* 48afcf: fadd dword ptr [edi + 0x154] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48afd5: push 1 */
	MF((DWORD)(m->esp + 0x38u)) = (float)ST(0); FPOP();	/* 48afd7: fstp dword ptr [esp + 0x38] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 48afdb: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x158u));	/* 48afdf: fadd dword ptr [edi + 0x158] */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 48afe5: mov eax, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x68u)) = m->eax;	/* 48afe9: mov dword ptr [esp + 0x68], eax */
	MF((DWORD)(m->esp + 0x3cu)) = (float)ST(0); FPOP();	/* 48afed: fstp dword ptr [esp + 0x3c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 48aff1: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x15cu));	/* 48aff5: fadd dword ptr [edi + 0x15c] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 48affb: mov ecx, dword ptr [esp + 0x3c] */
	M32((DWORD)(m->esp + 0x6cu)) = m->ecx;	/* 48afff: mov dword ptr [esp + 0x6c], ecx */
	MF((DWORD)(m->esp + 0x40u)) = (float)ST(0); FPOP();	/* 48b003: fstp dword ptr [esp + 0x40] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 48b007: fld dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x154u));	/* 48b00b: fadd dword ptr [edi + 0x154] */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 48b011: mov edx, dword ptr [esp + 0x40] */
	M32((DWORD)(m->esp + 0x70u)) = m->edx;	/* 48b015: mov dword ptr [esp + 0x70], edx */
	MF((DWORD)(m->esp + 0x44u)) = (float)ST(0); FPOP();	/* 48b019: fstp dword ptr [esp + 0x44] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 48b01d: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x158u));	/* 48b021: fadd dword ptr [edi + 0x158] */
	m->eax = M32((DWORD)(m->esp + 0x44u));	/* 48b027: mov eax, dword ptr [esp + 0x44] */
	M32((DWORD)(m->esp + 0x80u)) = m->eax;	/* 48b02b: mov dword ptr [esp + 0x80], eax */
	m->eax = (DWORD)(m->esp + 0x68u);	/* 48b032: lea eax, [esp + 0x68] */
	MF((DWORD)(m->esp + 0x48u)) = (float)ST(0); FPOP();	/* 48b036: fstp dword ptr [esp + 0x48] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 48b03a: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x15cu));	/* 48b03e: fadd dword ptr [edi + 0x15c] */
	m->ecx = M32((DWORD)(m->esp + 0x48u));	/* 48b044: mov ecx, dword ptr [esp + 0x48] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b048: push eax */
	M32((DWORD)(m->esp + 0x88u)) = m->ecx;	/* 48b049: mov dword ptr [esp + 0x88], ecx */
	m->ecx = (DWORD)(m->esp + 0x84u);	/* 48b050: lea ecx, [esp + 0x84] */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 48b057: fstp dword ptr [esp + 0x50] */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 48b05b: mov edx, dword ptr [esp + 0x50] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b05f: push ecx */
	{ DWORD v_ = 0xa1f238u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b060: push 0xa1f238 */
	m->ecx = (DWORD)(m->esi + 0x74u);	/* 48b065: lea ecx, [esi + 0x74] */
	M32((DWORD)(m->esp + 0x94u)) = m->edx;	/* 48b068: mov dword ptr [esp + 0x94], edx */
	m->esp -= 4; M32(m->esp) = 0x48b074u; native_call(m, 0x485120u);	/* 48b06f: call 0x485120 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48b074: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b075: push 1 */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 48b077: lea ecx, [esp + 0x2c] */
	M32((DWORD)(m->esp + 0x2cu)) = 0x0u;	/* 48b07b: mov dword ptr [esp + 0x2c], 0 */
	M32((DWORD)(m->esp + 0x30u)) = 0x461c4000u;	/* 48b083: mov dword ptr [esp + 0x30], 0x461c4000 */
	M32((DWORD)(m->esp + 0x34u)) = 0x0u;	/* 48b08b: mov dword ptr [esp + 0x34], 0 */
	m->esp -= 4; M32(m->esp) = 0x48b098u; native_call(m, 0x4677c0u);	/* 48b093: call 0x4677c0 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b098: push ebx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b099: push 2 */
	m->ecx = (DWORD)(m->esp + 0x2cu);	/* 48b09b: lea ecx, [esp + 0x2c] */
	m->esp -= 4; M32(m->esp) = 0x48b0a4u; native_call(m, 0x4677c0u);	/* 48b09f: call 0x4677c0 */
	M32((DWORD)(m->esp + 0x18u)) = 0x0u;	/* 48b0a4: mov dword ptr [esp + 0x18], 0 */
	M32((DWORD)(m->esp + 0x1cu)) = 0x461c4000u;	/* 48b0ac: mov dword ptr [esp + 0x1c], 0x461c4000 */
	M32((DWORD)(m->esp + 0x20u)) = 0x0u;	/* 48b0b4: mov dword ptr [esp + 0x20], 0 */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48b0bc: push ebp */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b0bd: push 1 */
	m->ecx = (DWORD)(m->esp + 0x20u);	/* 48b0bf: lea ecx, [esp + 0x20] */
	m->esp -= 4; M32(m->esp) = 0x48b0c8u; native_call(m, 0x4677c0u);	/* 48b0c3: call 0x4677c0 */
	{ DWORD a_ = m->ebx, b_ = 0x96u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48b0c8: add ebx, 0x96 */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 48b0ce: lea ecx, [esp + 0x18] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b0d2: push ebx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b0d3: push 2 */
	m->esp -= 4; M32(m->esp) = 0x48b0dau; native_call(m, 0x4677c0u);	/* 48b0d5: call 0x4677c0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x18u)));	/* 48b0da: fld dword ptr [esp + 0x18] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x154u));	/* 48b0de: fadd dword ptr [edi + 0x154] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b0e4: push 1 */
	MF((DWORD)(m->esp + 0x50u)) = (float)ST(0); FPOP();	/* 48b0e6: fstp dword ptr [esp + 0x50] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x20u)));	/* 48b0ea: fld dword ptr [esp + 0x20] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x158u));	/* 48b0ee: fadd dword ptr [edi + 0x158] */
	m->edx = M32((DWORD)(m->esp + 0x50u));	/* 48b0f4: mov edx, dword ptr [esp + 0x50] */
	M32((DWORD)(m->esp + 0x74u)) = m->edx;	/* 48b0f8: mov dword ptr [esp + 0x74], edx */
	MF((DWORD)(m->esp + 0x54u)) = (float)ST(0); FPOP();	/* 48b0fc: fstp dword ptr [esp + 0x54] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x24u)));	/* 48b100: fld dword ptr [esp + 0x24] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x15cu));	/* 48b104: fadd dword ptr [edi + 0x15c] */
	m->eax = M32((DWORD)(m->esp + 0x54u));	/* 48b10a: mov eax, dword ptr [esp + 0x54] */
	M32((DWORD)(m->esp + 0x78u)) = m->eax;	/* 48b10e: mov dword ptr [esp + 0x78], eax */
	MF((DWORD)(m->esp + 0x58u)) = (float)ST(0); FPOP();	/* 48b112: fstp dword ptr [esp + 0x58] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x28u)));	/* 48b116: fld dword ptr [esp + 0x28] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x154u));	/* 48b11a: fadd dword ptr [edi + 0x154] */
	m->ecx = M32((DWORD)(m->esp + 0x58u));	/* 48b120: mov ecx, dword ptr [esp + 0x58] */
	M32((DWORD)(m->esp + 0x7cu)) = m->ecx;	/* 48b124: mov dword ptr [esp + 0x7c], ecx */
	MF((DWORD)(m->esp + 0x5cu)) = (float)ST(0); FPOP();	/* 48b128: fstp dword ptr [esp + 0x5c] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x2cu)));	/* 48b12c: fld dword ptr [esp + 0x2c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x158u));	/* 48b130: fadd dword ptr [edi + 0x158] */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 48b136: mov edx, dword ptr [esp + 0x5c] */
	M32((DWORD)(m->esp + 0x8cu)) = m->edx;	/* 48b13a: mov dword ptr [esp + 0x8c], edx */
	m->edx = (DWORD)(m->esp + 0x74u);	/* 48b141: lea edx, [esp + 0x74] */
	MF((DWORD)(m->esp + 0x60u)) = (float)ST(0); FPOP();	/* 48b145: fstp dword ptr [esp + 0x60] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x30u)));	/* 48b149: fld dword ptr [esp + 0x30] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(m->edi + 0x15cu));	/* 48b14d: fadd dword ptr [edi + 0x15c] */
	m->eax = M32((DWORD)(m->esp + 0x60u));	/* 48b153: mov eax, dword ptr [esp + 0x60] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b157: push edx */
	M32((DWORD)(m->esp + 0x94u)) = m->eax;	/* 48b158: mov dword ptr [esp + 0x94], eax */
	m->eax = (DWORD)(m->esp + 0x90u);	/* 48b15f: lea eax, [esp + 0x90] */
	MF((DWORD)(m->esp + 0x68u)) = (float)ST(0); FPOP();	/* 48b166: fstp dword ptr [esp + 0x68] */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 48b16a: mov ecx, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b16e: push eax */
	M32((DWORD)(m->esp + 0x9cu)) = m->ecx;	/* 48b16f: mov dword ptr [esp + 0x9c], ecx */
	{ DWORD v_ = 0xa1f238u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b176: push 0xa1f238 */
	m->ecx = (DWORD)(m->esi + 0x74u);	/* 48b17b: lea ecx, [esi + 0x74] */
	m->esp -= 4; M32(m->esp) = 0x48b183u; native_call(m, 0x485120u);	/* 48b17e: call 0x485120 */
	{ DWORD a_ = m->ebx, b_ = 0xe10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b183: cmp ebx, 0xe10 */
	if (m->sf != m->of) goto L_48af67;	/* 48b189: jl 0x48af67 */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 48b18f: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, b_ = 0x708u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b193: cmp ebp, 0x708 */
	if (m->sf != m->of) goto L_48af5e;	/* 48b199: jl 0x48af5e */
L_48b19f:
	m->edi = (DWORD)(m->esi + 0x74u);	/* 48b19f: lea edi, [esi + 0x74] */
	m->ebx = (DWORD)(m->esi + 0x1f36c8u);	/* 48b1a2: lea ebx, [esi + 0x1f36c8] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b1a8: push -1 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b1aa: push edi */
	m->ecx = m->ebx;	/* 48b1ab: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48b1b2u; native_call(m, 0x45e170u);	/* 48b1ad: call 0x45e170 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b1b2: push edi */
	m->ecx = m->ebx;	/* 48b1b3: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48b1bau; native_call(m, 0x47d060u);	/* 48b1b5: call 0x47d060 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b1ba: push edi */
	m->ecx = m->ebx;	/* 48b1bb: mov ecx, ebx */
	m->esp -= 4; M32(m->esp) = 0x48b1c2u; native_call(m, 0x479af0u);	/* 48b1bd: call 0x479af0 */
	m->ecx = M32((DWORD)(m->esi + 0x1f1664u));	/* 48b1c2: mov ecx, dword ptr [esi + 0x1f1664] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b1c8: push 0 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b1ca: push ecx */
	m->ecx = m->edi;	/* 48b1cb: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x48b1d2u; native_call(m, 0x485af0u);	/* 48b1cd: call 0x485af0 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b1d2: push 0x3f800000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b1d7: push 0 */
	m->esp -= 4; M32(m->esp) = 0x48b1deu; native_call(m, 0x4685f0u);	/* 48b1d9: call 0x4685f0 */
	m->eax = M32((DWORD)(m->esi + 0x23432cfu));	/* 48b1de: mov eax, dword ptr [esi + 0x23432cf] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b1e4: add esp, 8 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48b1e7: dec eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 48b1e8: neg eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 48b1ea: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48b1eb: pop esi */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 48b1ec: sbb eax, eax */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48b1ee: pop ebp */
	{ DWORD a_ = m->eax, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48b1ef: and eax, 3 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48b1f2: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x84u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b1f3: add esp, 0x84 */
	m->esp += 4 + 0; return;	/* 48b1f9: ret  */
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
