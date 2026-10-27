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

static void lift_456be0(X86 *m);
static void lift_4555b0(X86 *m);

/* tex_allocIdBy (0x4555b0), lifted by tools/lift.py */
static void lift_4555b0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4555b0: sub esp, 0x40 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4555b3: xor eax, eax */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 4555b5: lea edx, [esp] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4555b9: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4555ba: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4555bb: push esi */
	m->ebp = m->ecx;	/* 4555bc: mov ebp, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4555be: push edi */
	m->edi = M32((DWORD)(m->esp + 0x54u));	/* 4555bf: mov edi, dword ptr [esp + 0x54] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4555c3: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4555c6: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4555c8: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4555ca: sub edi, ecx */
	m->eax = m->ecx;	/* 4555cc: mov eax, ecx */
	m->esi = m->edi;	/* 4555ce: mov esi, edi */
	m->edi = m->edx;	/* 4555d0: mov edi, edx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4555d2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4555d5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 4555d7: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4555d9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4555dc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 4555de: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4555e2: push ecx */
	m->esp -= 4; M32(m->esp) = 0x4555e8u; native_call(m, 0x46cb60u);	/* 4555e3: call 0x46cb60 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esp + 0x14u))) & 0xff) << 0);	/* 4555e8: mov al, byte ptr [esp + 0x14] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4555ec: add esp, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4555ef: test al, al */
	if (!m->zf) goto L_455600;	/* 4555f1: jne 0x455600 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4555f3: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4555f4: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4555f5: pop ebp */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4555f6: or eax, 0xffffffff */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4555f9: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4555fa: add esp, 0x40 */
	m->esp += 4 + 32; return;	/* 4555fd: ret 0x20 */
L_455600:
	m->eax = M32((DWORD)(m->ebp + 0xcd128u));	/* 455600: mov eax, dword ptr [ebp + 0xcd128] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 455606: xor edi, edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455608: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_455718;	/* 45560a: jle 0x455718 */
	m->edx = (DWORD)(m->ebp + 0xc0128u);	/* 455610: lea edx, [ebp + 0xc0128] */
L_455616:
	m->esi = (DWORD)(m->esp + 0x10u);	/* 455616: lea esi, [esp + 0x10] */
	m->eax = m->edx;	/* 45561a: mov eax, edx */
L_45561c:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x0u))) & 0xff) << 0);	/* 45561c: mov bl, byte ptr [eax] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 0);	/* 45561e: mov cl, bl */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x0u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 455620: cmp bl, byte ptr [esi] */
	if (!m->zf) goto L_455640;	/* 455622: jne 0x455640 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 455624: test cl, cl */
	if (m->zf) goto L_45563c;	/* 455626: je 0x45563c */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x1u))) & 0xff) << 0);	/* 455628: mov bl, byte ptr [eax + 1] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 0);	/* 45562b: mov cl, bl */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = M8((DWORD)(m->esi + 0x1u)) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 45562d: cmp bl, byte ptr [esi + 1] */
	if (!m->zf) goto L_455640;	/* 455630: jne 0x455640 */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 455632: add eax, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 455635: add esi, 2 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 455638: test cl, cl */
	if (!m->zf) goto L_45561c;	/* 45563a: jne 0x45561c */
L_45563c:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45563c: xor eax, eax */
	goto L_455645;	/* 45563e: jmp 0x455645 */
L_455640:
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 455640: sbb eax, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 455642: sbb eax, -1 */
L_455645:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455645: test eax, eax */
	if (m->zf) goto L_45565d;	/* 455647: je 0x45565d */
	m->eax = M32((DWORD)(m->ebp + 0xcd128u));	/* 455649: mov eax, dword ptr [ebp + 0xcd128] */
	{ DWORD a_ = m->edi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edi = r_; }	/* 45564f: inc edi */
	{ DWORD a_ = m->edx, b_ = 0x68u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 455650: add edx, 0x68 */
	{ DWORD a_ = m->edi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455653: cmp edi, eax */
	if (m->sf == m->of) goto L_455718;	/* 455655: jge 0x455718 */
	goto L_455616;	/* 45565b: jmp 0x455616 */
L_45565d:
	m->edx = (DWORD)(m->edi + m->edi*2 + 0x0u);	/* 45565d: lea edx, [edi + edi*2] */
	m->eax = (DWORD)(m->edi + m->edx*4 + 0x0u);	/* 455660: lea eax, [edi + edx*4] */
	m->edx = M32((DWORD)(m->esp + 0x58u));	/* 455663: mov edx, dword ptr [esp + 0x58] */
	m->ecx = (DWORD)(m->ebp + m->eax*8 + 0x0u);	/* 455667: lea ecx, [ebp + eax*8] */
	m->eax = M32((DWORD)(m->ebp + m->eax*8 + 0xc016cu));	/* 45566b: mov eax, dword ptr [ebp + eax*8 + 0xc016c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 455672: cmp eax, edx */
	if (!m->zf) goto L_4556e0;	/* 455674: jne 0x4556e0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xc0170u)));	/* 455676: fld dword ptr [ecx + 0xc0170] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x5cu)); FPOP();	/* 45567c: fcomp dword ptr [esp + 0x5c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 455680: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 455682: test ah, 0x40 */
	if (m->zf) goto L_4556e0;	/* 455685: je 0x4556e0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xc0178u)));	/* 455687: fld dword ptr [ecx + 0xc0178] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x64u)); FPOP();	/* 45568d: fcomp dword ptr [esp + 0x64] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 455691: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 455693: test ah, 0x40 */
	if (m->zf) goto L_4556e0;	/* 455696: je 0x4556e0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xc0174u)));	/* 455698: fld dword ptr [ecx + 0xc0174] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x60u)); FPOP();	/* 45569e: fcomp dword ptr [esp + 0x60] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4556a2: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4556a4: test ah, 0x40 */
	if (m->zf) goto L_4556e0;	/* 4556a7: je 0x4556e0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xc017cu)));	/* 4556a9: fld dword ptr [ecx + 0xc017c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x68u)); FPOP();	/* 4556af: fcomp dword ptr [esp + 0x68] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4556b3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4556b5: test ah, 0x40 */
	if (m->zf) goto L_4556e0;	/* 4556b8: je 0x4556e0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xc0184u)));	/* 4556ba: fld dword ptr [ecx + 0xc0184] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x70u)); FPOP();	/* 4556c0: fcomp dword ptr [esp + 0x70] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4556c4: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4556c6: test ah, 0x40 */
	if (m->zf) goto L_4556e0;	/* 4556c9: je 0x4556e0 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ecx + 0xc0180u)));	/* 4556cb: fld dword ptr [ecx + 0xc0180] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->esp + 0x6cu)); FPOP();	/* 4556d1: fcomp dword ptr [esp + 0x6c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4556d5: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x40u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4556d7: test ah, 0x40 */
	if (!m->zf) goto L_4557c5;	/* 4556da: jne 0x4557c5 */
L_4556e0:
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 4556e0: mov eax, dword ptr [esp + 0x68] */
	M32((DWORD)(m->ecx + 0xc016cu)) = m->edx;	/* 4556e4: mov dword ptr [ecx + 0xc016c], edx */
	m->ecx = M32((DWORD)(m->esp + 0x70u));	/* 4556ea: mov ecx, dword ptr [esp + 0x70] */
	m->edx = M32((DWORD)(m->esp + 0x6cu));	/* 4556ee: mov edx, dword ptr [esp + 0x6c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4556f2: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 4556f3: mov ecx, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4556f7: push edx */
	m->edx = M32((DWORD)(m->esp + 0x68u));	/* 4556f8: mov edx, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4556fc: push eax */
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 4556fd: mov eax, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455701: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455702: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455703: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 455704: push edi */
	m->ecx = m->ebp;	/* 455705: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x45570cu; native_call(m, 0x456860u);	/* 455707: call 0x456860 */
	m->eax = m->edi;	/* 45570c: mov eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 45570e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45570f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 455710: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 455711: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455712: add esp, 0x40 */
	m->esp += 4 + 32; return;	/* 455715: ret 0x20 */
L_455718:
	m->ecx = (DWORD)(m->esp + 0x10u);	/* 455718: lea ecx, [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45571c: push ecx */
	m->ecx = m->ebp;	/* 45571d: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x455724u; native_call(m, 0x4557e0u);	/* 45571f: call 0x4557e0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 455724: test eax, eax */
	if (!m->zf) goto L_455735;	/* 455726: jne 0x455735 */
	m->edi = M32(m->esp); m->esp += 4;	/* 455728: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 455729: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 45572a: pop ebp */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45572b: or eax, 0xffffffff */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45572e: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45572f: add esp, 0x40 */
	m->esp += 4 + 32; return;	/* 455732: ret 0x20 */
L_455735:
	m->eax = M32((DWORD)(m->ebp + 0xcd128u));	/* 455735: mov eax, dword ptr [ebp + 0xcd128] */
	{ DWORD a_ = m->eax, b_ = 0x200u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45573b: cmp eax, 0x200 */
	if (m->sf == m->of) goto L_455788;	/* 455740: jge 0x455788 */
	m->edx = M32((DWORD)(m->esp + 0x70u));	/* 455742: mov edx, dword ptr [esp + 0x70] */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 455746: mov ecx, dword ptr [esp + 0x68] */
	m->edi = m->eax;	/* 45574a: mov edi, eax */
	m->eax = M32((DWORD)(m->esp + 0x6cu));	/* 45574c: mov eax, dword ptr [esp + 0x6c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455750: push edx */
	m->edx = M32((DWORD)(m->esp + 0x68u));	/* 455751: mov edx, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455755: push eax */
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 455756: mov eax, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45575a: push ecx */
	m->ecx = M32((DWORD)(m->esp + 0x68u));	/* 45575b: mov ecx, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45575f: push edx */
	m->edx = M32((DWORD)(m->esp + 0x68u));	/* 455760: mov edx, dword ptr [esp + 0x68] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455764: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 455765: push ecx */
	m->ecx = (DWORD)(m->edi + m->edi*2 + 0x0u);	/* 455766: lea ecx, [edi + edi*2] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 455769: push edx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 45576a: lea eax, [esp + 0x2c] */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 45576e: push -1 */
	m->edx = (DWORD)(m->edi + m->ecx*4 + 0x0u);	/* 455770: lea edx, [edi + ecx*4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455773: push eax */
	m->ecx = (DWORD)(m->ebp + m->edx*8 + 0xc0128u);	/* 455774: lea ecx, [ebp + edx*8 + 0xc0128] */
	m->esp -= 4; M32(m->esp) = 0x455780u; native_call(m, 0x454e60u);	/* 45577b: call 0x454e60 */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xcd128u)), r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); M32((DWORD)(m->ebp + 0xcd128u)) = r_; }	/* 455780: inc dword ptr [ebp + 0xcd128] */
	goto L_4557ad;	/* 455786: jmp 0x4557ad */
L_455788:
	m->eax = M32((DWORD)(m->ebp + 0xc011cu));	/* 455788: mov eax, dword ptr [ebp + 0xc011c] */
	m->ecx = M32((DWORD)(m->ebp + 0xc0118u));	/* 45578e: mov ecx, dword ptr [ebp + 0xc0118] */
	{ DWORD v_ = 0x200u; m->esp -= 4; M32(m->esp) = v_; }	/* 455794: push 0x200 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 455799: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45579a: push ecx */
	{ DWORD v_ = 0x4b3fa8u; m->esp -= 4; M32(m->esp) = v_; }	/* 45579b: push 0x4b3fa8 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4557a0: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x4557aau; native_call(m, 0x46c710u);	/* 4557a5: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4557aa: add esp, 0x14 */
L_4557ad:
	m->edx = M32((DWORD)(m->ebp + 0xcd128u));	/* 4557ad: mov edx, dword ptr [ebp + 0xcd128] */
	m->eax = M32((DWORD)(m->ebp + 0xcd130u));	/* 4557b3: mov eax, dword ptr [ebp + 0xcd130] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4557b9: cmp edx, eax */
	if (m->sf == m->of) goto L_4557c5;	/* 4557bb: jge 0x4557c5 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4557bd: push edi */
	m->ecx = m->ebp;	/* 4557be: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x4557c5u; native_call(m, 0x4566c0u);	/* 4557c0: call 0x4566c0 */
L_4557c5:
	m->eax = m->edi;	/* 4557c5: mov eax, edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4557c7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4557c8: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4557c9: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4557ca: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4557cb: add esp, 0x40 */
	m->esp += 4 + 32; return;	/* 4557ce: ret 0x20 */
}

/* tex_getIdByName (0x456be0), lifted by tools/lift.py */
static void lift_456be0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456be0: sub esp, 8 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 456be3: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x28u));	/* 456be4: mov ebx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 456be8: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x28u));	/* 456be9: mov ebp, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456bed: push esi */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 456bee: mov esi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 456bf2: add ecx, 4 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456bf5: push edi */
	m->edi = M32((DWORD)(m->esp + 0x38u));	/* 456bf6: mov edi, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 456bfa: mov dword ptr [esp + 0x10], 0 */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 456c02: mov dword ptr [esp + 0x14], ecx */
L_456c06:
	m->ecx = M32((DWORD)(m->ecx + 0x0u));	/* 456c06: mov ecx, dword ptr [ecx] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456c08: test ecx, ecx */
	if (m->zf) goto L_456c2f;	/* 456c0a: je 0x456c2f */
	m->eax = M32((DWORD)(m->esp + 0x2cu));	/* 456c0c: mov eax, dword ptr [esp + 0x2c] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 456c10: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 456c14: push edi */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 456c15: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 456c16: push ebp */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456c17: push eax */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 456c18: mov eax, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456c1c: push edx */
	m->edx = M32((DWORD)(m->esp + 0x34u));	/* 456c1d: mov edx, dword ptr [esp + 0x34] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 456c21: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 456c22: push edx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456c23: push esi */
	m->esp -= 4; M32(m->esp) = 0x456c29u; lift_4555b0(m);	/* 456c24: call 0x4555b0 */
	m->ecx = m->eax;	/* 456c29: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 456c2b: test ecx, ecx */
	if (m->sf == m->of) goto L_456c68;	/* 456c2d: jge 0x456c68 */
L_456c2f:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 456c2f: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x14u));	/* 456c33: mov ecx, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 456c37: inc eax */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 456c38: add ecx, 4 */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 456c3b: cmp eax, 6 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 456c3e: mov dword ptr [esp + 0x10], eax */
	M32((DWORD)(m->esp + 0x14u)) = m->ecx;	/* 456c42: mov dword ptr [esp + 0x14], ecx */
	if (m->sf != m->of) goto L_456c06;	/* 456c46: jl 0x456c06 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 456c48: push esi */
	{ DWORD v_ = 0x4b42b0u; m->esp -= 4; M32(m->esp) = v_; }	/* 456c49: push 0x4b42b0 */
	{ DWORD v_ = 0xa0e000u; m->esp -= 4; M32(m->esp) = v_; }	/* 456c4e: push 0xa0e000 */
	m->esp -= 4; M32(m->esp) = 0x456c58u; native_call(m, 0x46c710u);	/* 456c53: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456c58: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 456c5b: or eax, 0xffffffff */
	m->edi = M32(m->esp); m->esp += 4;	/* 456c5e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 456c5f: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 456c60: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 456c61: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456c62: add esp, 8 */
	m->esp += 4 + 32; return;	/* 456c65: ret 0x20 */
L_456c68:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 456c68: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32(m->esp); m->esp += 4;	/* 456c6c: pop edi */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 456c6d: shl eax, 9 */
	m->esi = M32(m->esp); m->esp += 4;	/* 456c70: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 456c71: pop ebp */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 456c72: add eax, ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 456c74: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 456c75: add esp, 8 */
	m->esp += 4 + 32; return;	/* 456c78: ret 0x20 */
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
