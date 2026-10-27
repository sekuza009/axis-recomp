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

static void lift_4566c0(X86 *m);

/* tex_bind (0x4566c0), lifted by tools/lift.py */
static void lift_4566c0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4566c0: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x8u));	/* 4566c1: mov ebx, dword ptr [esp + 8] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4566c5: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4566c6: push esi */
	m->eax = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 4566c7: lea eax, [ebx + ebx*2] */
	m->esi = m->ecx;	/* 4566ca: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4566cc: push edi */
	m->ecx = (DWORD)(m->ebx + m->eax*4 + 0x0u);	/* 4566cd: lea ecx, [ebx + eax*4] */
	m->eax = M32((DWORD)(m->esi + m->ecx*8 + 0xc0168u));	/* 4566d0: mov eax, dword ptr [esi + ecx*8 + 0xc0168] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4566d7: test eax, eax */
	m->ebp = (DWORD)(m->esi + m->ecx*8 + 0x0u);	/* 4566d9: lea ebp, [esi + ecx*8] */
	if (m->sf == m->of) goto L_456726;	/* 4566dc: jge 0x456726 */
	m->edi = M32((DWORD)(m->esi + 0xcd134u));	/* 4566de: mov edi, dword ptr [esi + 0xcd134] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4566e4: push ebx */
	m->ecx = m->esi;	/* 4566e5: mov ecx, esi */
	M32((DWORD)(m->edi + 0x4u)) = m->ebx;	/* 4566e7: mov dword ptr [edi + 4], ebx */
	m->esp -= 4; M32(m->esp) = 0x4566efu; native_call(m, 0x455aa0u);	/* 4566ea: call 0x455aa0 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0xc016cu)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4566ef: test byte ptr [ebp + 0xc016c], 2 */
	if (m->zf) goto L_456700;	/* 4566f6: je 0x456700 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4566f8: push ebx */
	m->ecx = m->esi;	/* 4566f9: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x456700u; native_call(m, 0x456470u);	/* 4566fb: call 0x456470 */
L_456700:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0xc016cu)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 456700: test byte ptr [ebp + 0xc016c], 1 */
	if (m->zf) goto L_456711;	/* 456707: je 0x456711 */
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 456709: mov edx, dword ptr [edi + 8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45670c: push 0 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45670e: push edx */
	goto L_456717;	/* 45670f: jmp 0x456717 */
L_456711:
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 456711: mov eax, dword ptr [edi + 8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 456714: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456716: push eax */
L_456717:
	m->ecx = m->esi;	/* 456717: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x45671eu; native_call(m, 0x456520u);	/* 456719: call 0x456520 */
	{ DWORD a_ = M32((DWORD)(m->esi + 0xcd138u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->esi + 0xcd138u)) = r_; }	/* 45671e: inc dword ptr [esi + 0xcd138] */
	goto L_45679c;	/* 456724: jmp 0x45679c */
L_456726:
	m->edx = M32((DWORD)(m->esi + 0xcd12cu));	/* 456726: mov edx, dword ptr [esi + 0xcd12c] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 45672c: lea ecx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->ebp + 0xc018cu));	/* 45672f: mov eax, dword ptr [ebp + 0xc018c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456735: cmp eax, 1 */
	m->edi = (DWORD)(m->edx + m->ecx*4 + 0x0u);	/* 456738: lea edi, [edx + ecx*4] */
	if (!m->zf) goto L_45678d;	/* 45673b: jne 0x45678d */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45673d: push ebx */
	m->ecx = m->esi;	/* 45673e: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x456745u; native_call(m, 0x455aa0u);	/* 456740: call 0x455aa0 */
	{ DWORD a_ = M8((DWORD)(m->ebp + 0xc016cu)), b_ = 0x2u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 456745: test byte ptr [ebp + 0xc016c], 2 */
	if (m->zf) goto L_456756;	/* 45674c: je 0x456756 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45674e: push ebx */
	m->ecx = m->esi;	/* 45674f: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x456756u; native_call(m, 0x456470u);	/* 456751: call 0x456470 */
L_456756:
	{ DWORD a_ = M8((DWORD)(m->ebp + 0xc016cu)), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 456756: test byte ptr [ebp + 0xc016c], 1 */
	if (m->zf) goto L_456767;	/* 45675d: je 0x456767 */
	m->eax = M32((DWORD)(m->edi + 0x8u));	/* 45675f: mov eax, dword ptr [edi + 8] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 456762: push 0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456764: push eax */
	goto L_45676d;	/* 456765: jmp 0x45676d */
L_456767:
	m->ecx = M32((DWORD)(m->edi + 0x8u));	/* 456767: mov ecx, dword ptr [edi + 8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45676a: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45676c: push ecx */
L_45676d:
	m->ecx = m->esi;	/* 45676d: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x456774u; native_call(m, 0x456520u);	/* 45676f: call 0x456520 */
	m->eax = M32((DWORD)(m->esi + 0xcd138u));	/* 456774: mov eax, dword ptr [esi + 0xcd138] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 45677a: inc eax */
	M32((DWORD)(m->esi + 0xcd138u)) = m->eax;	/* 45677b: mov dword ptr [esi + 0xcd138], eax */
	M32((DWORD)(m->ebp + 0xc018cu)) = 0x0u;	/* 456781: mov dword ptr [ebp + 0xc018c], 0 */
	goto L_45679c;	/* 45678b: jmp 0x45679c */
L_45678d:
	m->edx = M32((DWORD)(m->edi + 0x8u));	/* 45678d: mov edx, dword ptr [edi + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456790: push edx */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 456791: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x45679cu; native_call(m, M32(0x4a9264u));	/* 456796: call dword ptr [0x4a9264] */
L_45679c:
	m->eax = M32((DWORD)(m->esi + 0xcd134u));	/* 45679c: mov eax, dword ptr [esi + 0xcd134] */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4567a2: cmp edi, eax */
	if (!m->zf) goto L_4567d5;	/* 4567a4: jne 0x4567d5 */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 4567a6: mov eax, dword ptr [eax + 0xc] */
	M32((DWORD)(m->esi + 0xcd134u)) = m->eax;	/* 4567a9: mov dword ptr [esi + 0xcd134], eax */
	m->eax = M32((DWORD)(m->eax + 0x4u));	/* 4567af: mov eax, dword ptr [eax + 4] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4567b2: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 4567b5: lea edx, [eax + ecx*4] */
	M32((DWORD)(m->esi + m->edx*8 + 0xc0168u)) = 0xffffffffu;	/* 4567b8: mov dword ptr [esi + edx*8 + 0xc0168], 0xffffffff */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 4567c3: mov eax, dword ptr [edi] */
	M32((DWORD)(m->edi + 0x4u)) = m->ebx;	/* 4567c5: mov dword ptr [edi + 4], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 4567c8: pop edi */
	M32((DWORD)(m->ebp + 0xc0168u)) = m->eax;	/* 4567c9: mov dword ptr [ebp + 0xc0168], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 4567cf: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4567d0: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4567d1: pop ebx */
	m->esp += 4 + 4; return;	/* 4567d2: ret 4 */
L_4567d5:
	m->eax = M32((DWORD)(m->edi + 0xcu));	/* 4567d5: mov eax, dword ptr [edi + 0xc] */
	m->ecx = M32((DWORD)(m->edi + 0x10u));	/* 4567d8: mov ecx, dword ptr [edi + 0x10] */
	M32((DWORD)(m->eax + 0x10u)) = m->ecx;	/* 4567db: mov dword ptr [eax + 0x10], ecx */
	m->edx = M32((DWORD)(m->edi + 0x10u));	/* 4567de: mov edx, dword ptr [edi + 0x10] */
	m->eax = M32((DWORD)(m->edi + 0xcu));	/* 4567e1: mov eax, dword ptr [edi + 0xc] */
	M32((DWORD)(m->edx + 0xcu)) = m->eax;	/* 4567e4: mov dword ptr [edx + 0xc], eax */
	m->ecx = M32((DWORD)(m->esi + 0xcd134u));	/* 4567e7: mov ecx, dword ptr [esi + 0xcd134] */
	M32((DWORD)(m->edi + 0xcu)) = m->ecx;	/* 4567ed: mov dword ptr [edi + 0xc], ecx */
	m->edx = M32((DWORD)(m->esi + 0xcd134u));	/* 4567f0: mov edx, dword ptr [esi + 0xcd134] */
	m->eax = M32((DWORD)(m->edx + 0x10u));	/* 4567f6: mov eax, dword ptr [edx + 0x10] */
	M32((DWORD)(m->edi + 0x10u)) = m->eax;	/* 4567f9: mov dword ptr [edi + 0x10], eax */
	M32((DWORD)(m->ecx + 0x10u)) = m->edi;	/* 4567fc: mov dword ptr [ecx + 0x10], edi */
	m->edx = M32((DWORD)(m->edi + 0x10u));	/* 4567ff: mov edx, dword ptr [edi + 0x10] */
	M32((DWORD)(m->edx + 0xcu)) = m->edi;	/* 456802: mov dword ptr [edx + 0xc], edi */
	m->eax = M32((DWORD)(m->edi + 0x0u));	/* 456805: mov eax, dword ptr [edi] */
	M32((DWORD)(m->edi + 0x4u)) = m->ebx;	/* 456807: mov dword ptr [edi + 4], ebx */
	m->edi = M32(m->esp); m->esp += 4;	/* 45680a: pop edi */
	M32((DWORD)(m->ebp + 0xc0168u)) = m->eax;	/* 45680b: mov dword ptr [ebp + 0xc0168], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 456811: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 456812: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 456813: pop ebx */
	m->esp += 4 + 4; return;	/* 456814: ret 4 */
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
