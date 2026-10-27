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

static void lift_496610(X86 *m);

/* hud_drawClock (0x496610), lifted by tools/lift.py */
static void lift_496610(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496610: sub esp, 0x100 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 496616: push ebx */
	m->ebx = M32((DWORD)(0x4a9228u));	/* 496617: mov ebx, dword ptr [0x4a9228] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 49661d: push esi */
	m->esi = m->ecx;	/* 49661e: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 496620: push edi */
	m->ecx = M32((DWORD)(m->esi + 0x23423adu));	/* 496621: mov ecx, dword ptr [esi + 0x23423ad] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 496627: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_49673f;	/* 496629: jle 0x49673f */
	{ DWORD a_ = M32((DWORD)(m->esi + 0x22e7184u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49662f: cmp dword ptr [esi + 0x22e7184], 1 */
	if (!m->zf) goto L_49664c;	/* 496636: jne 0x49664c */
	m->eax = M32((DWORD)(m->esi + 0x2221fb8u));	/* 496638: mov eax, dword ptr [esi + 0x2221fb8] */
	m->edi = M32((DWORD)(m->esi + 0x2221fbcu));	/* 49663e: mov edi, dword ptr [esi + 0x2221fbc] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 496644: cmp eax, edi */
	if (m->sf != m->of) goto L_496678;	/* 496646: jl 0x496678 */
	m->edi = m->eax;	/* 496648: mov edi, eax */
	goto L_496678;	/* 49664a: jmp 0x496678 */
L_49664c:
	m->eax = M32((DWORD)(m->esi + 0x2342976u));	/* 49664c: mov eax, dword ptr [esi + 0x2342976] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 496652: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_496676;	/* 496654: jle 0x496676 */
	m->eax = M32((DWORD)(m->esi + 0x23428f6u));	/* 496656: mov eax, dword ptr [esi + 0x23428f6] */
	m->edx = m->eax;	/* 49665c: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 49665e: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496661: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 496663: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496666: add edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 496668: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 49666b: add edx, eax */
	m->edi = M32((DWORD)(m->esi + m->edx*8 + 0x1eccb54u));	/* 49666d: mov edi, dword ptr [esi + edx*8 + 0x1eccb54] */
	goto L_496678;	/* 496674: jmp 0x496678 */
L_496676:
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 496676: xor edi, edi */
L_496678:
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 496678: sub ecx, edi */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49667a: cmp ecx, 1 */
	if (m->zf || m->sf != m->of) goto L_496690;	/* 49667d: jle 0x496690 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49667f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496684: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496689: push 0x3f800000 */
	goto L_4966b0;	/* 49668e: jmp 0x4966b0 */
L_496690:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x22f040cu)));	/* 496690: fld dword ptr [esi + 0x22f040c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 496696: fcomp dword ptr [0x4a942c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 49669c: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 49669e: test ah, 0x41 */
	if (!m->zf) goto L_4966a7;	/* 4966a1: jne 0x4966a7 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4966a3: push 0 */
	goto L_4966ac;	/* 4966a5: jmp 0x4966ac */
L_4966a7:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4966a7: push 0x3f800000 */
L_4966ac:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4966ac: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4966ae: push 0 */
L_4966b0:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4966b0: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4966bau; native_call(m, 0x44ad30u);	/* 4966b5: call 0x44ad30 */
	m->eax = M32((DWORD)(m->esi + 0x23423adu));	/* 4966ba: mov eax, dword ptr [esi + 0x23423ad] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4966c0: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4966c3: sub eax, edi */
	m->ecx = (DWORD)(m->esp + 0xcu);	/* 4966c5: lea ecx, [esp + 0xc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4966c9: push eax */
	{ DWORD v_ = 0x4b0320u; m->esp -= 4; M32(m->esp) = v_; }	/* 4966ca: push 0x4b0320 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4966cf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4966d5u; native_call(m, 0x49e9ddu);	/* 4966d0: call 0x49e9dd */
	m->edi = (DWORD)(m->esp + 0x18u);	/* 4966d5: lea edi, [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4966d9: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4966dc: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 4966de: lea edx, [esp + 0x18] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4966e2: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4966e4: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 4966e6: dec ecx */
	m->eax = 0x15u;	/* 4966e7: mov eax, 0x15 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4966ec: sub eax, ecx */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4966ee: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4966f0: push edx */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4966f1: push 8 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 4966f3: lea ecx, [eax + eax*2] */
	m->edx = (DWORD)(m->eax + m->ecx*4 + 0x0u);	/* 4966f6: lea edx, [eax + ecx*4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4966f9: push edx */
	m->esp -= 4; M32(m->esp) = 0x4966ffu; native_call(m, 0x44ad60u);	/* 4966fa: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4966ff: add esp, 0x1c */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496702: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496707: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49670c: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496711: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496718u; native_call(m, m->ebx);	/* 496716: call ebx */
	m->edi = (DWORD)(m->esp + 0xcu);	/* 496718: lea edi, [esp + 0xc] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 49671c: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 49671f: xor eax, eax */
	m->edx = 0xf9u;	/* 496721: mov edx, 0xf9 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 496726: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 496728: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 49672a: dec ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 49672b: push 1 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 49672d: push 8 */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 49672f: lea eax, [ecx + ecx*2] */
	m->ecx = (DWORD)(m->ecx + m->eax*4 + 0x0u);	/* 496732: lea ecx, [ecx + eax*4] */
	{ DWORD a_ = m->edx, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 496735: sub edx, ecx */
	m->ecx = m->esi;	/* 496737: mov ecx, esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 496739: push edx */
	m->esp -= 4; M32(m->esp) = 0x49673fu; native_call(m, 0x496820u);	/* 49673a: call 0x496820 */
L_49673f:
	m->ecx = M32((DWORD)(m->esi + 0x23423b1u));	/* 49673f: mov ecx, dword ptr [esi + 0x23423b1] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 496745: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_496812;	/* 496747: jle 0x496812 */
	m->eax = m->ecx;	/* 49674d: mov eax, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49674f: shl eax, 4 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 496752: sub eax, ecx */
	m->ecx = M32((DWORD)(m->esi + 0x22f0408u));	/* 496754: mov ecx, dword ptr [esi + 0x22f0408] */
	{ DWORD a_ = m->eax, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 49675a: shl eax, 2 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 49675d: cmp eax, ecx */
	if (m->zf || m->sf != m->of) goto L_496763;	/* 49675f: jle 0x496763 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 496761: sub eax, ecx */
L_496763:
	m->edi = m->eax;	/* 496763: mov edi, eax */
	{ DWORD a_ = m->edi, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 496765: cmp edi, 0xa */
	if (m->zf || m->sf != m->of) goto L_49677b;	/* 496768: jle 0x49677b */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49676a: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49676f: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496774: push 0x3f800000 */
	goto L_49679b;	/* 496779: jmp 0x49679b */
L_49677b:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x22f040cu)));	/* 49677b: fld dword ptr [esi + 0x22f040c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a942cu)); FPOP();	/* 496781: fcomp dword ptr [0x4a942c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 496787: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 496789: test ah, 0x41 */
	if (!m->zf) goto L_496792;	/* 49678c: jne 0x496792 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 49678e: push 0 */
	goto L_496797;	/* 496790: jmp 0x496797 */
L_496792:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 496792: push 0x3f800000 */
L_496797:
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496797: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 496799: push 0 */
L_49679b:
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 49679b: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4967a5u; native_call(m, 0x44ad30u);	/* 4967a0: call 0x44ad30 */
	m->eax = m->edi;	/* 4967a5: mov eax, edi */
	m->ecx = 0x3cu;	/* 4967a7: mov ecx, 0x3c */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 4967ac: cdq  */
	{ long long n_ = (long long)(((unsigned long long)m->edx << 32) | m->eax); int d_ = (int)m->ecx; m->eax = (DWORD)(int)(n_ / d_); m->edx = (DWORD)(int)(n_ % d_); }	/* 4967ad: idiv ecx */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4967af: add esp, 0x10 */
	m->eax = 0x88888889u;	/* 4967b2: mov eax, 0x88888889 */
	m->ecx = (DWORD)(m->esp + 0xcu);	/* 4967b7: lea ecx, [esp + 0xc] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4967bb: push edx */
	{ long long p_ = (long long)(int)m->eax * (int)m->edi; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 4967bc: imul edi */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4967be: add edx, edi */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 4967c0: sar edx, 5 */
	m->eax = m->edx;	/* 4967c3: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4967c5: shr eax, 0x1f */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 4967c8: add edx, eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4967ca: push edx */
	{ DWORD v_ = 0x4c7cd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4967cb: push 0x4c7cd8 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4967d0: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4967d6u; native_call(m, 0x49e9ddu);	/* 4967d1: call 0x49e9dd */
	m->edx = (DWORD)(m->esp + 0x1cu);	/* 4967d6: lea edx, [esp + 0x1c] */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 4967da: push 0x10 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4967dc: push edx */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4967dd: push 8 */
	{ DWORD v_ = 0x187u; m->esp -= 4; M32(m->esp) = v_; }	/* 4967df: push 0x187 */
	m->esp -= 4; M32(m->esp) = 0x4967e9u; native_call(m, 0x44ad60u);	/* 4967e4: call 0x44ad60 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4967e9: add esp, 0x20 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4967ec: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4967f1: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4967f6: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4967fb: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x496802u; native_call(m, m->ebx);	/* 496800: call ebx */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 496802: push 2 */
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 496804: push 8 */
	{ DWORD v_ = 0x16fu; m->esp -= 4; M32(m->esp) = v_; }	/* 496806: push 0x16f */
	m->ecx = m->esi;	/* 49680b: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x496812u; native_call(m, 0x496820u);	/* 49680d: call 0x496820 */
L_496812:
	m->edi = M32(m->esp); m->esp += 4;	/* 496812: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 496813: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 496814: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x100u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 496815: add esp, 0x100 */
	m->esp += 4 + 0; return;	/* 49681b: ret  */
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
