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

static void lift_483770(X86 *m);

/* script_processCommandBy (0x483770), lifted by tools/lift.py */
static void lift_483770(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 483770: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->esp, b_ = 0x110u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483774: sub esp, 0x110 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48377a: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48377b: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 48377c: xor ebp, ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48377e: push edi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48377f: cmp eax, ebp */
	m->edi = m->ecx;	/* 483781: mov edi, ecx */
	if (m->sf != m->of) goto L_48379f;	/* 483783: jl 0x48379f */
	m->ecx = m->eax;	/* 483785: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483787: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48378a: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48378c: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48378f: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483791: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483794: add ecx, eax */
	m->ebx = (DWORD)(m->edi + m->ecx*8 + 0x1cd93a8u);	/* 483796: lea ebx, [edi + ecx*8 + 0x1cd93a8] */
	goto L_4837a1;	/* 48379d: jmp 0x4837a1 */
L_48379f:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48379f: xor ebx, ebx */
L_4837a1:
	m->edx = M32((DWORD)(m->esp + 0x124u));	/* 4837a1: mov edx, dword ptr [esp + 0x124] */
	M32((DWORD)(m->esp + 0x14u)) = m->ebp;	/* 4837a8: mov dword ptr [esp + 0x14], ebp */
	m->eax = (DWORD)(m->edx + 0x821b9u);	/* 4837ac: lea eax, [edx + 0x821b9] */
	m->ecx = (DWORD)(m->eax*8 + 0x0u);	/* 4837b2: lea ecx, [eax*8] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 4837b9: sub ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x128u));	/* 4837bb: mov eax, dword ptr [esp + 0x128] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 4837c2: lea edx, [eax + eax*4] */
	m->eax = M32((DWORD)(m->edi + m->ecx*4 + 0x0u));	/* 4837c5: mov eax, dword ptr [edi + ecx*4] */
	m->ecx = M32((DWORD)(m->eax + m->edx*4 + 0xcu));	/* 4837c8: mov ecx, dword ptr [eax + edx*4 + 0xc] */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 4837cc: lea eax, [eax + edx*4] */
	{ DWORD a_ = m->ecx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4837cf: cmp ecx, ebp */
	M32((DWORD)(m->esp + 0x18u)) = m->eax;	/* 4837d1: mov dword ptr [esp + 0x18], eax */
	if (m->zf || m->sf != m->of) goto L_483c49;	/* 4837d5: jle 0x483c49 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4837db: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4837dc: xor esi, esi */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 4837de: mov dword ptr [esp + 0x14], esi */
L_4837e2:
	m->edx = M32((DWORD)(m->eax + 0x10u));	/* 4837e2: mov edx, dword ptr [eax + 0x10] */
	m->eax = M32((DWORD)(m->esi + m->edx*1 + 0x0u));	/* 4837e5: mov eax, dword ptr [esi + edx] */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4837e8: add esi, edx */
	{ DWORD a_ = m->eax, b_ = 0x1fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4837ea: cmp eax, 0x1f */
	if (!m->cf && !m->zf) goto L_483c25;	/* 4837ed: ja 0x483c25 */
	switch (m->eax) { case 0: goto L_4837fa; case 1: goto L_483816; case 2: goto L_48388d; case 3: goto L_4838bd; case 4: goto L_48382e; case 5: goto L_483844; case 6: goto L_483c25; case 7: goto L_48385a; case 8: goto L_483879; case 9: goto L_4838a9; case 10: goto L_4838cd; case 11: goto L_4838dd; case 12: goto L_4838f1; case 13: goto L_483931; case 14: goto L_48394a; case 15: goto L_483961; case 16: goto L_483981; case 17: goto L_4839a1; case 18: goto L_4839b1; case 19: goto L_4839c7; case 20: goto L_4839e6; case 21: goto L_483a52; case 22: goto L_483a68; case 23: goto L_483aa6; case 24: goto L_483ae7; case 25: goto L_483aff; case 26: goto L_483b10; case 27: goto L_483b78; case 28: goto L_483ba7; case 29: goto L_483be2; case 30: goto L_483c0d; case 31: goto L_483c1a; default: abort(); }	/* 4837f3: jmp dword ptr [eax*4 + 0x483c58] */
L_4837fa:
	m->esi = M32((DWORD)(m->esi + 0x4u));	/* 4837fa: mov esi, dword ptr [esi + 4] */
	m->ecx = (DWORD)(m->esi*8 + 0x0u);	/* 4837fd: lea ecx, [esi*8] */
	{ DWORD a_ = m->ecx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483804: sub ecx, esi */
	M32((DWORD)(m->edi + m->ecx*4 + 0xe3b040u)) = 0x1u;	/* 483806: mov dword ptr [edi + ecx*4 + 0xe3b040], 1 */
	goto L_483c25;	/* 483811: jmp 0x483c25 */
L_483816:
	m->esi = M32((DWORD)(m->esi + 0x4u));	/* 483816: mov esi, dword ptr [esi + 4] */
	m->edx = (DWORD)(m->esi*8 + 0x0u);	/* 483819: lea edx, [esi*8] */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 483820: sub edx, esi */
	M32((DWORD)(m->edi + m->edx*4 + 0xe3b040u)) = m->ebp;	/* 483822: mov dword ptr [edi + edx*4 + 0xe3b040], ebp */
	goto L_483c25;	/* 483829: jmp 0x483c25 */
L_48382e:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48382e: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 483830: je 0x483c25 */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 483836: mov edx, dword ptr [esi + 4] */
	M32((DWORD)(m->ebx + 0x8804u)) = m->edx;	/* 483839: mov dword ptr [ebx + 0x8804], edx */
	goto L_483c25;	/* 48383f: jmp 0x483c25 */
L_483844:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483844: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 483846: je 0x483c25 */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 48384c: mov eax, dword ptr [esi + 4] */
	M32((DWORD)(m->ebx + 0x8808u)) = m->eax;	/* 48384f: mov dword ptr [ebx + 0x8808], eax */
	goto L_483c25;	/* 483855: jmp 0x483c25 */
L_48385a:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48385a: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 48385c: je 0x483c25 */
	m->ecx = M32((DWORD)(m->esi + 0x4u));	/* 483862: mov ecx, dword ptr [esi + 4] */
	M32((DWORD)(m->ebx + 0x87f8u)) = m->ecx;	/* 483865: mov dword ptr [ebx + 0x87f8], ecx */
	m->edx = M32((DWORD)(m->esi + 0x8u));	/* 48386b: mov edx, dword ptr [esi + 8] */
	M32((DWORD)(m->ebx + 0x87fcu)) = m->edx;	/* 48386e: mov dword ptr [ebx + 0x87fc], edx */
	goto L_483c25;	/* 483874: jmp 0x483c25 */
L_483879:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483879: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 48387b: je 0x483c25 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x8820u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483881: cmp dword ptr [ebx + 0x8820], ebp */
	if (m->sf != m->of) goto L_483c25;	/* 483887: jl 0x483c25 */
L_48388d:
	m->esi = M32((DWORD)(m->esi + 0x4u));	/* 48388d: mov esi, dword ptr [esi + 4] */
	m->eax = (DWORD)(m->esi*8 + 0x0u);	/* 483890: lea eax, [esi*8] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 483897: sub eax, esi */
	M32((DWORD)(m->edi + m->eax*4 + 0xe3b050u)) = 0x1u;	/* 483899: mov dword ptr [edi + eax*4 + 0xe3b050], 1 */
	goto L_483c25;	/* 4838a4: jmp 0x483c25 */
L_4838a9:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4838a9: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 4838ab: je 0x483c25 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x8820u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4838b1: cmp dword ptr [ebx + 0x8820], ebp */
	if (m->sf != m->of) goto L_483c25;	/* 4838b7: jl 0x483c25 */
L_4838bd:
	m->ecx = M32((DWORD)(m->esi + 0x4u));	/* 4838bd: mov ecx, dword ptr [esi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4838c0: push ecx */
	m->ecx = m->edi;	/* 4838c1: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x4838c8u; native_call(m, 0x483ce0u);	/* 4838c3: call 0x483ce0 */
	goto L_483c25;	/* 4838c8: jmp 0x483c25 */
L_4838cd:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4838cd: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 4838cf: je 0x483c25 */
	M32((DWORD)(m->ebx + 0x78u)) = m->ebp;	/* 4838d5: mov dword ptr [ebx + 0x78], ebp */
	goto L_483c25;	/* 4838d8: jmp 0x483c25 */
L_4838dd:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4838dd: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 4838df: je 0x483c25 */
	M32((DWORD)(m->ebx + 0x78u)) = 0x1u;	/* 4838e5: mov dword ptr [ebx + 0x78], 1 */
	goto L_483c25;	/* 4838ec: jmp 0x483c25 */
L_4838f1:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4838f1: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 4838f3: je 0x483c25 */
	m->edx = M32((DWORD)(m->ebx + 0x68u));	/* 4838f9: mov edx, dword ptr [ebx + 0x68] */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4838fc: or eax, 0xffffffff */
	M32((DWORD)(m->ebx + 0x8804u)) = m->ebp;	/* 4838ff: mov dword ptr [ebx + 0x8804], ebp */
	M32((DWORD)(m->ebx + 0x8808u)) = m->eax;	/* 483905: mov dword ptr [ebx + 0x8808], eax */
	M32((DWORD)(m->ebx + 0x50u)) = m->edx;	/* 48390b: mov dword ptr [ebx + 0x50], edx */
	M32((DWORD)(m->ebx + 0x880cu)) = m->ebp;	/* 48390e: mov dword ptr [ebx + 0x880c], ebp */
	M32((DWORD)(m->ebx + 0x8810u)) = m->eax;	/* 483914: mov dword ptr [ebx + 0x8810], eax */
	M32((DWORD)(m->ebx + 0x8814u)) = m->eax;	/* 48391a: mov dword ptr [ebx + 0x8814], eax */
	M32((DWORD)(m->ebx + 0x8818u)) = m->eax;	/* 483920: mov dword ptr [ebx + 0x8818], eax */
	M32((DWORD)(m->ebx + 0x881cu)) = m->eax;	/* 483926: mov dword ptr [ebx + 0x881c], eax */
	goto L_483c25;	/* 48392c: jmp 0x483c25 */
L_483931:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483931: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 483933: je 0x483c25 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esi + 0x4u)));	/* 483939: fld dword ptr [esi + 4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9750u));	/* 48393c: fmul dword ptr [0x4a9750] */
	MF((DWORD)(m->ebx + 0x50u)) = (float)ST(0); FPOP();	/* 483942: fstp dword ptr [ebx + 0x50] */
	goto L_483c25;	/* 483945: jmp 0x483c25 */
L_48394a:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48394a: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 48394c: je 0x483c25 */
	M32((DWORD)(m->ebx + 0x880cu)) = 0x1u;	/* 483952: mov dword ptr [ebx + 0x880c], 1 */
	goto L_483c25;	/* 48395c: jmp 0x483c25 */
L_483961:
	m->esi = M32((DWORD)(m->esi + 0x4u));	/* 483961: mov esi, dword ptr [esi + 4] */
	m->eax = (DWORD)(m->esi + m->esi*2 + 0x0u);	/* 483964: lea eax, [esi + esi*2] */
	{ DWORD a_ = m->eax, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 483967: shl eax, 3 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48396a: sub eax, esi */
	m->ecx = (DWORD)(m->edi + m->eax*4 + 0x1cd6fb4u);	/* 48396c: lea ecx, [edi + eax*4 + 0x1cd6fb4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483973: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 483974: push esi */
	m->ecx = m->edi;	/* 483975: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x48397cu; native_call(m, 0x45de20u);	/* 483977: call 0x45de20 */
	goto L_483c25;	/* 48397c: jmp 0x483c25 */
L_483981:
	m->esi = M32((DWORD)(m->esi + 0x4u));	/* 483981: mov esi, dword ptr [esi + 4] */
	m->edx = m->esi;	/* 483984: mov edx, esi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 483986: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 483989: add edx, esi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48398b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48398e: add edx, esi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 483990: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 483993: add edx, esi */
	M32((DWORD)(m->edi + m->edx*8 + 0x1cd94d0u)) = m->ebp;	/* 483995: mov dword ptr [edi + edx*8 + 0x1cd94d0], ebp */
	goto L_483c25;	/* 48399c: jmp 0x483c25 */
L_4839a1:
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 4839a1: mov eax, dword ptr [esi + 4] */
	m->ecx = m->edi;	/* 4839a4: mov ecx, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4839a6: push eax */
	m->esp -= 4; M32(m->esp) = 0x4839acu; native_call(m, 0x45dca0u);	/* 4839a7: call 0x45dca0 */
	goto L_483c25;	/* 4839ac: jmp 0x483c25 */
L_4839b1:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4839b1: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 4839b3: je 0x483c25 */
	m->ecx = M32((DWORD)(m->esi + 0x4u));	/* 4839b9: mov ecx, dword ptr [esi + 4] */
	M32((DWORD)(m->ebx + 0x8810u)) = m->ecx;	/* 4839bc: mov dword ptr [ebx + 0x8810], ecx */
	goto L_483c25;	/* 4839c2: jmp 0x483c25 */
L_4839c7:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4839c7: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 4839c9: je 0x483c25 */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 4839cf: mov edx, dword ptr [esi + 4] */
	M32((DWORD)(m->ebx + 0x8814u)) = m->edx;	/* 4839d2: mov dword ptr [ebx + 0x8814], edx */
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 4839d8: mov eax, dword ptr [esi + 8] */
	M32((DWORD)(m->ebx + 0x8818u)) = m->eax;	/* 4839db: mov dword ptr [ebx + 0x8818], eax */
	goto L_483c25;	/* 4839e1: jmp 0x483c25 */
L_4839e6:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4839e6: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 4839e8: je 0x483c25 */
	M32((DWORD)(m->esp + 0x10u)) = m->ebp;	/* 4839ee: mov dword ptr [esp + 0x10], ebp */
	m->ebp = 0x1561e88u;	/* 4839f2: mov ebp, 0x1561e88 */
L_4839f7:
	m->ecx = M32((DWORD)(m->ebx + 0x10cu));	/* 4839f7: mov ecx, dword ptr [ebx + 0x10c] */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 4839fd: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 483a00: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 483a03: sub eax, ecx */
	m->edx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 483a05: lea edx, [eax + eax*2] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 483a08: lea eax, [ecx + edx*8] */
	m->ecx = (DWORD)(m->ebp + m->eax*2 + 0x0u);	/* 483a0b: lea ecx, [ebp + eax*2] */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 483a0f: mov eax, dword ptr [esi + 4] */
	m->edx = M32((DWORD)(m->ecx + m->edi*1 + 0x0u));	/* 483a12: mov edx, dword ptr [ecx + edi] */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483a15: cmp edx, eax */
	if (!m->zf) goto L_483a2d;	/* 483a17: jne 0x483a2d */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 483a19: mov eax, dword ptr [esp + 0x10] */
	m->ecx = M32((DWORD)(m->esp + 0x124u));	/* 483a1d: mov ecx, dword ptr [esp + 0x124] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483a24: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483a25: push ecx */
	m->ecx = m->edi;	/* 483a26: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x483a2du; native_call(m, 0x45e880u);	/* 483a28: call 0x45e880 */
L_483a2d:
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 483a2d: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ebp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 483a31: add ebp, 4 */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 483a34: inc edx */
	{ DWORD a_ = m->ebp, b_ = 0x1561ea0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483a35: cmp ebp, 0x1561ea0 */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 483a3b: mov dword ptr [esp + 0x10], edx */
	if (m->sf != m->of) goto L_4839f7;	/* 483a3f: jl 0x4839f7 */
	M32((DWORD)(m->ebx + 0x46cu)) = 0x1u;	/* 483a41: mov dword ptr [ebx + 0x46c], 1 */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 483a4b: xor ebp, ebp */
	goto L_483c25;	/* 483a4d: jmp 0x483c25 */
L_483a52:
	{ DWORD a_ = m->ebx, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483a52: cmp ebx, ebp */
	if (m->zf) goto L_483c25;	/* 483a54: je 0x483c25 */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 483a5a: mov edx, dword ptr [esi + 4] */
	M32((DWORD)(m->ebx + 0x881cu)) = m->edx;	/* 483a5d: mov dword ptr [ebx + 0x881c], edx */
	goto L_483c25;	/* 483a63: jmp 0x483c25 */
L_483a68:
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 483a68: mov eax, dword ptr [esi + 4] */
	m->ecx = m->eax;	/* 483a6b: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483a6d: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483a70: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483a72: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483a75: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483a77: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483a7a: add ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 483a7c: or eax, 0xffffffff */
	M32((DWORD)(m->edi + m->ecx*8 + 0x1ce1ba0u)) = m->eax;	/* 483a7f: mov dword ptr [edi + ecx*8 + 0x1ce1ba0], eax */
	m->esi = M32((DWORD)(m->esi + 0x4u));	/* 483a86: mov esi, dword ptr [esi + 4] */
	m->edx = m->esi;	/* 483a89: mov edx, esi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 483a8b: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 483a8e: add edx, esi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 483a90: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 483a93: add edx, esi */
	{ DWORD a_ = m->edx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 483a95: shl edx, 4 */
	{ DWORD a_ = m->edx, b_ = m->esi & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 483a98: add edx, esi */
	M32((DWORD)(m->edi + m->edx*8 + 0x1ce1ba4u)) = m->eax;	/* 483a9a: mov dword ptr [edi + edx*8 + 0x1ce1ba4], eax */
	goto L_483c25;	/* 483aa1: jmp 0x483c25 */
L_483aa6:
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 483aa6: mov eax, dword ptr [esi + 4] */
	m->edx = M32((DWORD)(m->esi + 0x8u));	/* 483aa9: mov edx, dword ptr [esi + 8] */
	m->ecx = m->eax;	/* 483aac: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483aae: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483ab1: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483ab3: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483ab6: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483ab8: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483abb: add ecx, eax */
	M32((DWORD)(m->edi + m->ecx*8 + 0x1ce1ba0u)) = m->edx;	/* 483abd: mov dword ptr [edi + ecx*8 + 0x1ce1ba0], edx */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 483ac4: mov eax, dword ptr [esi + 4] */
	m->ecx = m->eax;	/* 483ac7: mov ecx, eax */
	m->edx = M32((DWORD)(m->esi + 0xcu));	/* 483ac9: mov edx, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483acc: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483acf: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483ad1: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483ad4: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483ad6: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483ad9: add ecx, eax */
	M32((DWORD)(m->edi + m->ecx*8 + 0x1ce1ba4u)) = m->edx;	/* 483adb: mov dword ptr [edi + ecx*8 + 0x1ce1ba4], edx */
	goto L_483c25;	/* 483ae2: jmp 0x483c25 */
L_483ae7:
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 483ae7: mov eax, dword ptr [esi + 0xc] */
	m->ecx = M32((DWORD)(m->esi + 0x8u));	/* 483aea: mov ecx, dword ptr [esi + 8] */
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 483aed: mov edx, dword ptr [esi + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483af0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483af1: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483af2: push edx */
	m->ecx = m->edi;	/* 483af3: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x483afau; native_call(m, 0x45dff0u);	/* 483af5: call 0x45dff0 */
	goto L_483c25;	/* 483afa: jmp 0x483c25 */
L_483aff:
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 483aff: push ebp */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 483b00: push -1 */
	{ DWORD v_ = 0xffffffffu; m->esp -= 4; M32(m->esp) = v_; }	/* 483b02: push -1 */
	m->ecx = m->edi;	/* 483b04: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x483b0bu; native_call(m, 0x45dff0u);	/* 483b06: call 0x45dff0 */
	goto L_483c25;	/* 483b0b: jmp 0x483c25 */
L_483b10:
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 483b10: mov eax, dword ptr [esi + 4] */
	m->ecx = m->eax;	/* 483b13: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 483b15: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 483b18: add ecx, eax */
	{ DWORD a_ = M32((DWORD)(m->edi + m->ecx*8 + 0x2104fe8u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483b1a: cmp dword ptr [edi + ecx*8 + 0x2104fe8], ebp */
	if (!m->zf) goto L_483b36;	/* 483b21: jne 0x483b36 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483b23: push eax */
	{ DWORD v_ = 0x4c7a8cu; m->esp -= 4; M32(m->esp) = v_; }	/* 483b24: push 0x4c7a8c */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 483b29: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x483b33u; native_call(m, 0x46c710u);	/* 483b2e: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483b33: add esp, 0xc */
L_483b36:
	m->eax = M32((DWORD)(m->esi + 0x8u));	/* 483b36: mov eax, dword ptr [esi + 8] */
	m->edx = m->eax;	/* 483b39: mov edx, eax */
	{ DWORD a_ = m->edx, c_ = (0x5u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 483b3b: shl edx, 5 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 483b3e: add edx, eax */
	{ DWORD a_ = M32((DWORD)(m->edi + m->edx*8 + 0x210850cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483b40: cmp dword ptr [edi + edx*8 + 0x210850c], ebp */
	if (!m->zf) goto L_483b5c;	/* 483b47: jne 0x483b5c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483b49: push eax */
	{ DWORD v_ = 0x4c7a48u; m->esp -= 4; M32(m->esp) = v_; }	/* 483b4a: push 0x4c7a48 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 483b4f: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x483b59u; native_call(m, 0x46c710u);	/* 483b54: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483b59: add esp, 0xc */
L_483b5c:
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 483b5c: mov eax, dword ptr [esi + 0x10] */
	m->ecx = M32((DWORD)(m->esi + 0xcu));	/* 483b5f: mov ecx, dword ptr [esi + 0xc] */
	m->edx = M32((DWORD)(m->esi + 0x8u));	/* 483b62: mov edx, dword ptr [esi + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483b65: push eax */
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 483b66: mov eax, dword ptr [esi + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483b69: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483b6a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483b6b: push eax */
	m->ecx = m->edi;	/* 483b6c: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x483b73u; native_call(m, 0x48fc40u);	/* 483b6e: call 0x48fc40 */
	goto L_483c25;	/* 483b73: jmp 0x483c25 */
L_483b78:
	m->ecx = (DWORD)(m->esi + 0x4u);	/* 483b78: lea ecx, [esi + 4] */
	m->edx = (DWORD)(m->edi + 0x808u);	/* 483b7b: lea edx, [edi + 0x808] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483b81: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483b82: push edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 483b83: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x4c7a3cu; m->esp -= 4; M32(m->esp) = v_; }	/* 483b87: push 0x4c7a3c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483b8c: push eax */
	m->esp -= 4; M32(m->esp) = 0x483b92u; native_call(m, 0x49e9ddu);	/* 483b8d: call 0x49e9dd */
	m->ecx = M32((DWORD)(m->esi + 0x24u));	/* 483b92: mov ecx, dword ptr [esi + 0x24] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483b95: add esp, 0x10 */
	m->edx = (DWORD)(m->esp + 0x20u);	/* 483b98: lea edx, [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483b9c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483b9d: push edx */
	m->ecx = m->edi;	/* 483b9e: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x483ba5u; native_call(m, 0x48fce0u);	/* 483ba0: call 0x48fce0 */
	goto L_483c25;	/* 483ba5: jmp 0x483c25 */
L_483ba7:
	m->eax = (DWORD)(m->esi + 0x8u);	/* 483ba7: lea eax, [esi + 8] */
	m->ecx = (DWORD)(m->edi + 0x908u);	/* 483baa: lea ecx, [edi + 0x908] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483bb0: push eax */
	m->edx = (DWORD)(m->edi + 0x8u);	/* 483bb1: lea edx, [edi + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483bb4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483bb5: push edx */
	m->eax = (DWORD)(m->esp + 0x2cu);	/* 483bb6: lea eax, [esp + 0x2c] */
	{ DWORD v_ = 0x4c7a30u; m->esp -= 4; M32(m->esp) = v_; }	/* 483bba: push 0x4c7a30 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483bbf: push eax */
	m->esp -= 4; M32(m->esp) = 0x483bc5u; native_call(m, 0x49e9ddu);	/* 483bc0: call 0x49e9dd */
	m->ecx = M32((DWORD)(m->esi + 0x2cu));	/* 483bc5: mov ecx, dword ptr [esi + 0x2c] */
	m->edx = M32((DWORD)(m->esi + 0x28u));	/* 483bc8: mov edx, dword ptr [esi + 0x28] */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483bcb: add esp, 0x14 */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 483bce: lea eax, [esp + 0x20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483bd2: push ecx */
	m->ecx = M32((DWORD)(m->esi + 0x4u));	/* 483bd3: mov ecx, dword ptr [esi + 4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483bd6: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483bd7: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483bd8: push ecx */
	m->ecx = m->edi;	/* 483bd9: mov ecx, edi */
	m->esp -= 4; M32(m->esp) = 0x483be0u; native_call(m, 0x490df0u);	/* 483bdb: call 0x490df0 */
	goto L_483c25;	/* 483be0: jmp 0x483c25 */
L_483be2:
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 483be2: add esi, 4 */
	m->edx = (DWORD)(m->edi + 0x908u);	/* 483be5: lea edx, [edi + 0x908] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 483beb: push esi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483bec: push edx */
	m->eax = (DWORD)(m->esp + 0x28u);	/* 483bed: lea eax, [esp + 0x28] */
	{ DWORD v_ = 0x4c7a20u; m->esp -= 4; M32(m->esp) = v_; }	/* 483bf1: push 0x4c7a20 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483bf6: push eax */
	m->esp -= 4; M32(m->esp) = 0x483bfcu; native_call(m, 0x49e9ddu);	/* 483bf7: call 0x49e9dd */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 483bfc: lea ecx, [esp + 0x30] */
	{ DWORD v_ = 0x64u; m->esp -= 4; M32(m->esp) = v_; }	/* 483c00: push 0x64 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 483c02: push ecx */
	m->esp -= 4; M32(m->esp) = 0x483c08u; native_call(m, 0x457080u);	/* 483c03: call 0x457080 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483c08: add esp, 0x18 */
	goto L_483c25;	/* 483c0b: jmp 0x483c25 */
L_483c0d:
	m->edx = M32((DWORD)(m->esi + 0x4u));	/* 483c0d: mov edx, dword ptr [esi + 4] */
	m->ecx = m->edi;	/* 483c10: mov ecx, edi */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483c12: push edx */
	m->esp -= 4; M32(m->esp) = 0x483c18u; native_call(m, 0x490ee0u);	/* 483c13: call 0x490ee0 */
	goto L_483c25;	/* 483c18: jmp 0x483c25 */
L_483c1a:
	m->eax = M32((DWORD)(m->esi + 0x4u));	/* 483c1a: mov eax, dword ptr [esi + 4] */
	m->ecx = m->edi;	/* 483c1d: mov ecx, edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483c1f: push eax */
	m->esp -= 4; M32(m->esp) = 0x483c25u; native_call(m, 0x490f30u);	/* 483c20: call 0x490f30 */
L_483c25:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 483c25: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 483c29: mov ecx, dword ptr [esp + 0x18] */
	m->esi = M32((DWORD)(m->esp + 0x14u));	/* 483c2d: mov esi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 483c31: inc ecx */
	m->edx = M32((DWORD)(m->eax + 0xcu));	/* 483c32: mov edx, dword ptr [eax + 0xc] */
	{ DWORD a_ = m->esi, b_ = 0x30u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 483c35: add esi, 0x30 */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483c38: cmp ecx, edx */
	M32((DWORD)(m->esp + 0x18u)) = m->ecx;	/* 483c3a: mov dword ptr [esp + 0x18], ecx */
	M32((DWORD)(m->esp + 0x14u)) = m->esi;	/* 483c3e: mov dword ptr [esp + 0x14], esi */
	if (m->sf != m->of) goto L_4837e2;	/* 483c42: jl 0x4837e2 */
	m->esi = M32(m->esp); m->esp += 4;	/* 483c48: pop esi */
L_483c49:
	m->edi = M32(m->esp); m->esp += 4;	/* 483c49: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 483c4a: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 483c4b: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x110u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483c4c: add esp, 0x110 */
	m->esp += 4 + 12; return;	/* 483c52: ret 0xc */
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
