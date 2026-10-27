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

static void lift_466650(X86 *m);
static void lift_466430(X86 *m);

/* shape_bindTextureBy (0x466430), lifted by tools/lift.py */
static void lift_466430(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466430: sub esp, 0xc */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466433: push esi */
	m->esi = m->ecx;	/* 466434: mov esi, ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 466436: xor eax, eax */
	M32((DWORD)(m->esp + 0xcu)) = m->esi;	/* 466438: mov dword ptr [esp + 0xc], esi */
	m->ecx = M32((DWORD)(m->esi + 0x10u));	/* 46643c: mov ecx, dword ptr [esi + 0x10] */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 46643f: mov dword ptr [esp + 8], eax */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466443: cmp ecx, eax */
	if (m->zf || m->sf != m->of) goto L_46654e;	/* 466445: jle 0x46654e */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 46644b: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46644c: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46644d: push edi */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 46644e: mov dword ptr [esp + 0x10], eax */
L_466452:
	m->edx = M32((DWORD)(m->esp + 0x20u));	/* 466452: mov edx, dword ptr [esp + 0x20] */
	m->ebx = M32((DWORD)(m->esi + 0x14u));	/* 466456: mov ebx, dword ptr [esi + 0x14] */
	m->ecx = M32((DWORD)(m->esp + 0x10u));	/* 466459: mov ecx, dword ptr [esp + 0x10] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x0u))) & 0xff) << 0);	/* 46645d: mov al, byte ptr [edx] */
	{ DWORD a_ = m->ebx, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 46645f: add ebx, ecx */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 466461: test al, al */
	if (m->zf) goto L_4664f4;	/* 466463: je 0x4664f4 */
	m->ebp = (DWORD)(m->ebx + 0x4u);	/* 466469: lea ebp, [ebx + 4] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46646c: or ecx, 0xffffffff */
	m->edi = m->ebp;	/* 46646f: mov edi, ebp */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 466471: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 466473: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 466475: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 466477: dec ecx */
	m->edi = m->edx;	/* 466478: mov edi, edx */
	m->esi = m->ecx;	/* 46647a: mov esi, ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46647c: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46647f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 466481: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 466483: dec ecx */
	{ DWORD a_ = m->esi, b_ = m->ecx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 466484: add esi, ecx */
	{ DWORD a_ = m->esi, b_ = 0x3fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 466486: cmp esi, 0x3f */
	if (m->cf || m->zf) goto L_46649f;	/* 466489: jbe 0x46649f */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46648b: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 46648c: push ebp */
	{ DWORD v_ = 0x4c4c6cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46648d: push 0x4c4c6c */
	{ DWORD v_ = 0xa0e790u; m->esp -= 4; M32(m->esp) = v_; }	/* 466492: push 0xa0e790 */
	m->esp -= 4; M32(m->esp) = 0x46649cu; native_call(m, 0x46c710u);	/* 466497: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46649c: add esp, 0x10 */
L_46649f:
	m->edi = 0x4b12f4u;	/* 46649f: mov edi, 0x4b12f4 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4664a4: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4664a7: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4664a9: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4664ab: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4664ad: sub edi, ecx */
	m->esi = m->edi;	/* 4664af: mov esi, edi */
	m->edx = m->ecx;	/* 4664b1: mov edx, ecx */
	m->edi = m->ebp;	/* 4664b3: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4664b5: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4664b8: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4664ba: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4664bc: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4664bd: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4664c0: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4664c2: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4664c4: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4664c7: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32((DWORD)(m->esp + 0x20u));	/* 4664c9: mov edi, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4664cd: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4664d0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 4664d2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4664d4: sub edi, ecx */
	m->esi = m->edi;	/* 4664d6: mov esi, edi */
	m->edx = m->ecx;	/* 4664d8: mov edx, ecx */
	m->edi = m->ebp;	/* 4664da: mov edi, ebp */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4664dc: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4664df: repne scasb al, byte ptr es:[edi] */
	m->ecx = m->edx;	/* 4664e1: mov ecx, edx */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 4664e3: dec edi */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4664e4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4664e7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4664e9: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4664eb: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4664ee: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = M32((DWORD)(m->esp + 0x18u));	/* 4664f0: mov esi, dword ptr [esp + 0x18] */
L_4664f4:
	m->eax = M32((DWORD)(m->esp + 0x3cu));	/* 4664f4: mov eax, dword ptr [esp + 0x3c] */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 4664f8: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4664fc: push eax */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 4664fd: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466501: push edx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 466502: mov edx, dword ptr [esp + 0x38] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 466506: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46650c: push eax */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 46650d: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466511: push edx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 466512: mov edx, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466516: push eax */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 466517: mov eax, dword ptr [esp + 0x38] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46651b: push edx */
	m->edx = (DWORD)(m->ebx + 0x4u);	/* 46651c: lea edx, [ebx + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46651f: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 466520: push edx */
	m->esp -= 4; M32(m->esp) = 0x466526u; native_call(m, 0x456be0u);	/* 466521: call 0x456be0 */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 466526: mov edx, dword ptr [esp + 0x10] */
	M32((DWORD)(m->ebx + 0x44u)) = m->eax;	/* 46652a: mov dword ptr [ebx + 0x44], eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 46652d: mov eax, dword ptr [esp + 0x14] */
	m->ecx = M32((DWORD)(m->esi + 0x10u));	/* 466531: mov ecx, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 466534: inc eax */
	{ DWORD a_ = m->edx, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 466535: add edx, 0x80 */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46653b: cmp eax, ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 46653d: mov dword ptr [esp + 0x14], eax */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 466541: mov dword ptr [esp + 0x10], edx */
	if (m->sf != m->of) goto L_466452;	/* 466545: jl 0x466452 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46654b: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 46654c: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 46654d: pop ebx */
L_46654e:
	m->esi = M32(m->esp); m->esp += 4;	/* 46654e: pop esi */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46654f: add esp, 0xc */
	m->esp += 4 + 32; return;	/* 466552: ret 0x20 */
}

/* FUN_00466650 (0x466650), lifted by tools/lift.py */
static void lift_466650(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 466650: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466651: push esi */
	m->esi = m->ecx;	/* 466652: mov esi, ecx */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 466654: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x46665fu; native_call(m, M32(0x4a9224u));	/* 466659: call dword ptr [0x4a9224] */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 46665f: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 466662: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466664: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4666b4;	/* 466666: jle 0x4666b4 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 466668: push edi */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 466669: xor edi, edi */
L_46666b:
	m->eax = M32((DWORD)(m->esi + 0x14u));	/* 46666b: mov eax, dword ptr [esi + 0x14] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46666e: add eax, edi */
	m->eax = M32((DWORD)(m->eax + 0x44u));	/* 466670: mov eax, dword ptr [eax + 0x44] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466673: test eax, eax */
	if (m->sf != m->of) goto L_4666a5;	/* 466675: jl 0x4666a5 */
	m->ecx = m->eax;	/* 466677: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x800001ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466679: and ecx, 0x800001ff */
	if (!m->sf) goto L_466689;	/* 46667f: jns 0x466689 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 466681: dec ecx */
	{ DWORD a_ = m->ecx, b_ = 0xfffffe00u & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 466682: or ecx, 0xfffffe00 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 466688: inc ecx */
L_466689:
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 466689: cdq  */
	{ DWORD a_ = m->edx, b_ = 0x1ffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 46668a: and edx, 0x1ff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466690: push ecx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 466691: add eax, edx */
	m->edx = M32((DWORD)(0xa0e010u));	/* 466693: mov edx, dword ptr [0xa0e010] */
	{ DWORD a_ = m->eax, c_ = (0x9u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 466699: sar eax, 9 */
	m->ecx = M32((DWORD)(m->edx + m->eax*4 + 0x4u));	/* 46669c: mov ecx, dword ptr [edx + eax*4 + 4] */
	m->esp -= 4; M32(m->esp) = 0x4666a5u; native_call(m, 0x4566c0u);	/* 4666a0: call 0x4566c0 */
L_4666a5:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 4666a5: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4666a8: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x80u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4666a9: add edi, 0x80 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4666af: cmp ebx, eax */
	if (m->sf != m->of) goto L_46666b;	/* 4666b1: jl 0x46666b */
	m->edi = M32(m->esp); m->esp += 4;	/* 4666b3: pop edi */
L_4666b4:
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4666b4: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x4666bfu; native_call(m, M32(0x4a922cu));	/* 4666b9: call dword ptr [0x4a922c] */
	m->esi = M32(m->esp); m->esp += 4;	/* 4666bf: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4666c0: pop ebx */
	m->esp += 4 + 0; return;	/* 4666c1: ret  */
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
