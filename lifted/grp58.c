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

static void lift_468250(X86 *m);
static void lift_4680d0(X86 *m);

/* glWindow_wndProc (0x4680d0), lifted by tools/lift.py */
static void lift_4680d0(X86 *m)
{
	m->ecx = M32((DWORD)(m->esp + 0x8u));	/* 4680d0: mov ecx, dword ptr [esp + 8] */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4680d4: sub esp, 0x50 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4680d7: push esi */
	m->eax = (DWORD)(m->ecx + 0xffffffffu);	/* 4680d8: lea eax, [ecx - 1] */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4680db: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4680dd: cmp eax, 0xf */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4680e0: push edi */
	if (!m->cf && !m->zf) goto L_468202;	/* 4680e1: ja 0x468202 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4680e7: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x468238u))) & 0xff) << 0);	/* 4680e9: mov dl, byte ptr [eax + 0x468238] */
	switch (m->edx) { case 0: goto L_4680f6; case 1: goto L_4681b3; case 2: goto L_468191; case 3: goto L_468156; case 4: goto L_46817c; case 5: goto L_468202; default: abort(); }	/* 4680ef: jmp dword ptr [edx*4 + 0x468220] */
L_4680f6:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4680f6: push esi */
	m->esp -= 4; M32(m->esp) = 0x4680fdu; native_call(m, M32(0x4a92c8u));	/* 4680f7: call dword ptr [0x4a92c8] */
	m->edi = M32((DWORD)(m->esp + 0x5cu));	/* 4680fd: mov edi, dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 468101: push edi */
	m->esp -= 4; M32(m->esp) = 0x468108u; native_call(m, M32(0x4a9318u));	/* 468102: call dword ptr [0x4a9318] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468108: push eax */
	M32((DWORD)(0xa0e938u)) = m->eax;	/* 468109: mov dword ptr [0xa0e938], eax */
	m->esp -= 4; M32(m->esp) = 0x468113u; native_call(m, 0x467e60u);	/* 46810e: call 0x467e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468113: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468116: test eax, eax */
	if (!m->zf) goto L_468121;	/* 468118: jne 0x468121 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46811a: push esi */
	m->esp -= 4; M32(m->esp) = 0x468121u; native_call(m, M32(0x4a932cu));	/* 46811b: call dword ptr [0x4a932c] */
L_468121:
	m->eax = M32((DWORD)(0xa0e938u));	/* 468121: mov eax, dword ptr [0xa0e938] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468126: push eax */
	m->esp -= 4; M32(m->esp) = 0x46812du; native_call(m, M32(0x4a9230u));	/* 468127: call dword ptr [0x4a9230] */
	m->ecx = M32((DWORD)(0xa0e938u));	/* 46812d: mov ecx, dword ptr [0xa0e938] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468133: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468134: push ecx */
	M32((DWORD)(0xa0e93cu)) = m->eax;	/* 468135: mov dword ptr [0xa0e93c], eax */
	m->esp -= 4; M32(m->esp) = 0x468140u; native_call(m, M32(0x4a9254u));	/* 46813a: call dword ptr [0x4a9254] */
	m->edx = (DWORD)(m->esp + 0x8u);	/* 468140: lea edx, [esp + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468144: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 468145: push edi */
	m->esp -= 4; M32(m->esp) = 0x46814cu; native_call(m, M32(0x4a9310u));	/* 468146: call dword ptr [0x4a9310] */
	m->eax = m->esi;	/* 46814c: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 46814e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46814f: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468150: add esp, 0x50 */
	m->esp += 4 + 16; return;	/* 468153: ret 0x10 */
L_468156:
	m->edi = M32((DWORD)(m->esp + 0x5cu));	/* 468156: mov edi, dword ptr [esp + 0x5c] */
	m->eax = (DWORD)(m->esp + 0x18u);	/* 46815a: lea eax, [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46815e: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46815f: push edi */
	m->esp -= 4; M32(m->esp) = 0x468166u; native_call(m, M32(0x4a9308u));	/* 468160: call dword ptr [0x4a9308] */
	m->ecx = (DWORD)(m->esp + 0x18u);	/* 468166: lea ecx, [esp + 0x18] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46816a: push ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46816b: push edi */
	m->esp -= 4; M32(m->esp) = 0x468172u; native_call(m, M32(0x4a92dcu));	/* 46816c: call dword ptr [0x4a92dc] */
	m->eax = m->esi;	/* 468172: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 468174: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 468175: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468176: add esp, 0x50 */
	m->esp += 4 + 16; return;	/* 468179: ret 0x10 */
L_46817c:
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 46817c: mov edx, dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 468180: push edx */
	m->esp -= 4; M32(m->esp) = 0x468187u; native_call(m, M32(0x4a9344u));	/* 468181: call dword ptr [0x4a9344] */
	m->eax = m->esi;	/* 468187: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 468189: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46818a: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46818b: add esp, 0x50 */
	m->esp += 4 + 16; return;	/* 46818e: ret 0x10 */
L_468191:
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 468191: mov eax, dword ptr [esp + 0x68] */
	m->ecx = m->eax;	/* 468195: mov ecx, eax */
	{ DWORD a_ = m->eax, b_ = 0xffffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 468197: and eax, 0xffff */
	{ DWORD a_ = m->ecx, c_ = (0x10u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46819c: shr ecx, 0x10 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46819f: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4681a0: push eax */
	m->esp -= 4; M32(m->esp) = 0x4681a6u; native_call(m, 0x468450u);	/* 4681a1: call 0x468450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4681a6: add esp, 8 */
	m->eax = m->esi;	/* 4681a9: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4681ab: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4681ac: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4681ad: add esp, 0x50 */
	m->esp += 4 + 16; return;	/* 4681b0: ret 0x10 */
L_4681b3:
	m->eax = M32((DWORD)(0xa0e93cu));	/* 4681b3: mov eax, dword ptr [0xa0e93c] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4681b8: cmp eax, esi */
	if (m->zf) goto L_4681c3;	/* 4681ba: je 0x4681c3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4681bc: push eax */
	m->esp -= 4; M32(m->esp) = 0x4681c3u; native_call(m, M32(0x4a9274u));	/* 4681bd: call dword ptr [0x4a9274] */
L_4681c3:
	m->eax = M32((DWORD)(0xa0e938u));	/* 4681c3: mov eax, dword ptr [0xa0e938] */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4681c8: cmp eax, esi */
	if (m->zf) goto L_4681d8;	/* 4681ca: je 0x4681d8 */
	m->edx = M32((DWORD)(m->esp + 0x5cu));	/* 4681cc: mov edx, dword ptr [esp + 0x5c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4681d0: push eax */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4681d1: push edx */
	m->esp -= 4; M32(m->esp) = 0x4681d8u; native_call(m, M32(0x4a931cu));	/* 4681d2: call dword ptr [0x4a931c] */
L_4681d8:
	M32((DWORD)(0xa0e93cu)) = m->esi;	/* 4681d8: mov dword ptr [0xa0e93c], esi */
	M32((DWORD)(0xa0e938u)) = m->esi;	/* 4681de: mov dword ptr [0xa0e938], esi */
	m->esp -= 4; M32(m->esp) = 0x4681e9u; native_call(m, 0x468050u);	/* 4681e4: call 0x468050 */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 4681e9: push 1 */
	m->esp -= 4; M32(m->esp) = 0x4681f1u; native_call(m, M32(0x4a92c8u));	/* 4681eb: call dword ptr [0x4a92c8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4681f1: push esi */
	m->esp -= 4; M32(m->esp) = 0x4681f8u; native_call(m, M32(0x4a932cu));	/* 4681f2: call dword ptr [0x4a932c] */
	m->eax = m->esi;	/* 4681f8: mov eax, esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4681fa: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4681fb: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4681fc: add esp, 0x50 */
	m->esp += 4 + 16; return;	/* 4681ff: ret 0x10 */
L_468202:
	m->eax = M32((DWORD)(m->esp + 0x68u));	/* 468202: mov eax, dword ptr [esp + 0x68] */
	m->edx = M32((DWORD)(m->esp + 0x64u));	/* 468206: mov edx, dword ptr [esp + 0x64] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46820a: push eax */
	m->eax = M32((DWORD)(m->esp + 0x60u));	/* 46820b: mov eax, dword ptr [esp + 0x60] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46820f: push edx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468210: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468211: push eax */
	m->esp -= 4; M32(m->esp) = 0x468218u; native_call(m, M32(0x4a92f4u));	/* 468212: call dword ptr [0x4a92f4] */
	m->edi = M32(m->esp); m->esp += 4;	/* 468218: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 468219: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x50u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46821a: add esp, 0x50 */
	m->esp += 4 + 16; return;	/* 46821d: ret 0x10 */
}

/* glWindow_init (0x468250), lifted by tools/lift.py */
static void lift_468250(X86 *m)
{
	m->eax = M32((DWORD)(0xa0e930u));	/* 468250: mov eax, dword ptr [0xa0e930] */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468255: sub esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468258: cmp eax, 1 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46825b: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 46825c: push edi */
	if (!m->zf) goto L_468274;	/* 46825d: jne 0x468274 */
	{ DWORD v_ = 0x4c4fd8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46825f: push 0x4c4fd8 */
	m->esp -= 4; M32(m->esp) = 0x468269u; native_call(m, 0x46c840u);	/* 468264: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468269: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46826c: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 46826e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46826f: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468270: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 468273: ret  */
L_468274:
	m->edi = M32((DWORD)(m->esp + 0x34u));	/* 468274: mov edi, dword ptr [esp + 0x34] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 468278: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46827b: xor eax, eax */
	m->edx = M32((DWORD)(m->esp + 0x40u));	/* 46827d: mov edx, dword ptr [esp + 0x40] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 468281: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 468283: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 468285: sub edi, ecx */
	m->eax = m->ecx;	/* 468287: mov eax, ecx */
	m->esi = m->edi;	/* 468289: mov esi, edi */
	m->edi = 0xa0e81cu;	/* 46828b: mov edi, 0xa0e81c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 468290: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 468293: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 468295: mov ecx, eax */
	m->eax = M32((DWORD)(m->esp + 0x38u));	/* 468297: mov eax, dword ptr [esp + 0x38] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46829b: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 46829e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 4682a0: mov ecx, dword ptr [esp + 0x3c] */
	M32((DWORD)(0xa0e818u)) = m->edx;	/* 4682a4: mov dword ptr [0xa0e818], edx */
	m->edx = M32((DWORD)(m->esp + 0x44u));	/* 4682aa: mov edx, dword ptr [esp + 0x44] */
	m->esi = M32((DWORD)(m->esp + 0x50u));	/* 4682ae: mov esi, dword ptr [esp + 0x50] */
	M32((DWORD)(0xa0e924u)) = m->edx;	/* 4682b2: mov dword ptr [0xa0e924], edx */
	m->edx = M32((DWORD)(m->esp + 0x48u));	/* 4682b8: mov edx, dword ptr [esp + 0x48] */
	M32((DWORD)(0xa0e920u)) = m->edx;	/* 4682bc: mov dword ptr [0xa0e920], edx */
	m->edx = M32((DWORD)(m->esp + 0x4cu));	/* 4682c2: mov edx, dword ptr [esp + 0x4c] */
	{ DWORD a_ = m->edi, b_ = m->edi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edi = r_; }	/* 4682c6: xor edi, edi */
	M32((DWORD)(0xa0e810u)) = m->eax;	/* 4682c8: mov dword ptr [0xa0e810], eax */
	{ DWORD a_ = m->edx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4682cd: cmp edx, edi */
	M32((DWORD)(0xa0e928u)) = m->ecx;	/* 4682cf: mov dword ptr [0xa0e928], ecx */
	if (!m->zf) goto L_468419;	/* 4682d5: jne 0x468419 */
	{ DWORD a_ = m->esi, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4682db: cmp esi, edi */
	if (!m->zf) goto L_468419;	/* 4682dd: jne 0x468419 */
	m->esi = M32((DWORD)(0x4a915cu));	/* 4682e3: mov esi, dword ptr [0x4a915c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4682e9: push edi */
	M32((DWORD)(m->esp + 0xcu)) = m->edi;	/* 4682ea: mov dword ptr [esp + 0xc], edi */
	M32((DWORD)(m->esp + 0x10u)) = 0x4680d0u;	/* 4682ee: mov dword ptr [esp + 0x10], 0x4680d0 */
	M32((DWORD)(m->esp + 0x14u)) = m->edi;	/* 4682f6: mov dword ptr [esp + 0x14], edi */
	M32((DWORD)(m->esp + 0x18u)) = m->edi;	/* 4682fa: mov dword ptr [esp + 0x18], edi */
	m->esp -= 4; M32(m->esp) = 0x468300u; native_call(m, m->esi);	/* 4682fe: call esi */
	{ DWORD v_ = 0xa0e81cu; m->esp -= 4; M32(m->esp) = v_; }	/* 468300: push 0xa0e81c */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 468305: push edi */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 468306: mov dword ptr [esp + 0x20], eax */
	m->esp -= 4; M32(m->esp) = 0x46830cu; native_call(m, m->esi);	/* 46830a: call esi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46830c: push eax */
	m->esp -= 4; M32(m->esp) = 0x468313u; native_call(m, M32(0x4a92c4u));	/* 46830d: call dword ptr [0x4a92c4] */
	{ DWORD v_ = 0x7f00u; m->esp -= 4; M32(m->esp) = v_; }	/* 468313: push 0x7f00 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 468318: push edi */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 468319: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x468323u; native_call(m, M32(0x4a933cu));	/* 46831d: call dword ptr [0x4a933c] */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 468323: mov dword ptr [esp + 0x20], eax */
	m->eax = (DWORD)(m->esp + 0x8u);	/* 468327: lea eax, [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46832b: push eax */
	M32((DWORD)(m->esp + 0x28u)) = 0x6u;	/* 46832c: mov dword ptr [esp + 0x28], 6 */
	M32((DWORD)(m->esp + 0x2cu)) = 0xa0e81cu;	/* 468334: mov dword ptr [esp + 0x2c], 0xa0e81c */
	M32((DWORD)(m->esp + 0x30u)) = 0xa0e81cu;	/* 46833c: mov dword ptr [esp + 0x30], 0xa0e81c */
	m->esp -= 4; M32(m->esp) = 0x46834au; native_call(m, M32(0x4a92b8u));	/* 468344: call dword ptr [0x4a92b8] */
	{ DWORD a_ = (m->eax & 0xffff), b_ = (m->eax & 0xffff) & 0xffffu, r_ = a_ & b_; FLAGS(r_, 16); m->cf = 0; m->of = 0; }	/* 46834a: test ax, ax */
	if (!m->zf) goto L_468364;	/* 46834d: jne 0x468364 */
	{ DWORD v_ = 0x4c4fa4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46834f: push 0x4c4fa4 */
	m->esp -= 4; M32(m->esp) = 0x468359u; native_call(m, 0x46c840u);	/* 468354: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468359: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46835c: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 46835e: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46835f: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468360: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 468363: ret  */
L_468364:
	{ DWORD a_ = M32((DWORD)(0xa0e920u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 468364: cmp dword ptr [0xa0e920], 1 */
	if (!m->zf) goto L_4683a0;	/* 46836b: jne 0x4683a0 */
	m->ecx = M32((DWORD)(0xa0e818u));	/* 46836d: mov ecx, dword ptr [0xa0e818] */
	m->edx = M32((DWORD)(0xa0e928u));	/* 468373: mov edx, dword ptr [0xa0e928] */
	m->eax = M32((DWORD)(0xa0e810u));	/* 468379: mov eax, dword ptr [0xa0e810] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46837e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 46837f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 468380: push eax */
	m->esp -= 4; M32(m->esp) = 0x468386u; native_call(m, 0x467f20u);	/* 468381: call 0x467f20 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468386: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 468389: test eax, eax */
	if (!m->zf) goto L_4683a0;	/* 46838b: jne 0x4683a0 */
	{ DWORD v_ = 0x4c4f50u; m->esp -= 4; M32(m->esp) = v_; }	/* 46838d: push 0x4c4f50 */
	m->esp -= 4; M32(m->esp) = 0x468397u; native_call(m, 0x46c840u);	/* 468392: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468397: add esp, 4 */
	M32((DWORD)(0xa0e920u)) = m->edi;	/* 46839a: mov dword ptr [0xa0e920], edi */
L_4683a0:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4683a0: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4683a1: push edi */
	m->esp -= 4; M32(m->esp) = 0x4683a4u; native_call(m, m->esi);	/* 4683a2: call esi */
	m->ecx = M32((DWORD)(0xa0e928u));	/* 4683a4: mov ecx, dword ptr [0xa0e928] */
	m->edx = M32((DWORD)(0xa0e810u));	/* 4683aa: mov edx, dword ptr [0xa0e810] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4683b0: push eax */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4683b1: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4683b2: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4683b3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4683b4: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4683b5: push edi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4683b6: push edi */
	{ DWORD v_ = 0x86000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4683b7: push 0x86000000 */
	{ DWORD v_ = 0xa0e81cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4683bc: push 0xa0e81c */
	{ DWORD v_ = 0xa0e81cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4683c1: push 0xa0e81c */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4683c6: push edi */
	m->esp -= 4; M32(m->esp) = 0x4683cdu; native_call(m, M32(0x4a9350u));	/* 4683c7: call dword ptr [0x4a9350] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4683cd: cmp eax, edi */
	M32((DWORD)(0xa0e934u)) = m->eax;	/* 4683cf: mov dword ptr [0xa0e934], eax */
	if (!m->zf) goto L_4683eb;	/* 4683d4: jne 0x4683eb */
	{ DWORD v_ = 0x4c4f14u; m->esp -= 4; M32(m->esp) = v_; }	/* 4683d6: push 0x4c4f14 */
	m->esp -= 4; M32(m->esp) = 0x4683e0u; native_call(m, 0x46c840u);	/* 4683db: call 0x46c840 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4683e0: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4683e3: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 4683e5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4683e6: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4683e7: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 4683ea: ret  */
L_4683eb:
	{ DWORD v_ = 0xau; m->esp -= 4; M32(m->esp) = v_; }	/* 4683eb: push 0xa */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4683ed: push eax */
	m->esp -= 4; M32(m->esp) = 0x4683f4u; native_call(m, M32(0x4a92bcu));	/* 4683ee: call dword ptr [0x4a92bc] */
	m->eax = M32((DWORD)(0xa0e934u));	/* 4683f4: mov eax, dword ptr [0xa0e934] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4683f9: push eax */
	m->esp -= 4; M32(m->esp) = 0x468400u; native_call(m, M32(0x4a92c0u));	/* 4683fa: call dword ptr [0x4a92c0] */
	m->ecx = M32((DWORD)(0xa0e934u));	/* 468400: mov ecx, dword ptr [0xa0e934] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468406: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46840du; native_call(m, M32(0x4a935cu));	/* 468407: call dword ptr [0x4a935c] */
	M32((DWORD)(0xa0e930u)) = 0x1u;	/* 46840d: mov dword ptr [0xa0e930], 1 */
	goto L_46842f;	/* 468417: jmp 0x46842f */
L_468419:
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 468419: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46841a: push eax */
	M32((DWORD)(0xa0e934u)) = m->edx;	/* 46841b: mov dword ptr [0xa0e934], edx */
	M32((DWORD)(0xa0e938u)) = m->esi;	/* 468421: mov dword ptr [0xa0e938], esi */
	m->esp -= 4; M32(m->esp) = 0x46842cu; native_call(m, 0x468450u);	/* 468427: call 0x468450 */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46842c: add esp, 8 */
L_46842f:
	m->esp -= 4; M32(m->esp) = 0x468434u; native_call(m, 0x4684c0u);	/* 46842f: call 0x4684c0 */
	m->eax = M32((DWORD)(0xa0e934u));	/* 468434: mov eax, dword ptr [0xa0e934] */
	m->edi = M32(m->esp); m->esp += 4;	/* 468439: pop edi */
	M32((DWORD)(0x4c4de8u)) = 0xffffffffu;	/* 46843a: mov dword ptr [0x4c4de8], 0xffffffff */
	m->esi = M32(m->esp); m->esp += 4;	/* 468444: pop esi */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 468445: add esp, 0x28 */
	m->esp += 4 + 0; return;	/* 468448: ret  */
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
