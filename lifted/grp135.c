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

static void lift_40d450(X86 *m);
static void lift_445e40(X86 *m);
static void lift_43e290(X86 *m);
static void lift_410b50(X86 *m);
static void lift_4076c0(X86 *m);

/* lobby_onStateChange (0x4076c0), lifted by tools/lift.py */
static void lift_4076c0(X86 *m)
{
	m->eax = M32((DWORD)(0x4db51cu));	/* 4076c0: mov eax, dword ptr [0x4db51c] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4076c5: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_40772b;	/* 4076c8: ja 0x40772b */
	switch (m->eax) { case 0: goto L_4076d6; case 1: goto L_4076db; case 2: goto L_4076fc; case 3: goto L_40772b; case 4: goto L_40772b; case 5: goto L_4076d1; default: abort(); }	/* 4076ca: jmp dword ptr [eax*4 + 0x40772c] */
L_4076d1:
	native_call(m, 0x406950u); return;	/* 4076d1: jmp 0x406950 */
L_4076d6:
	native_call(m, 0x406a60u); return;	/* 4076d6: jmp 0x406a60 */
L_4076db:
	m->eax = M32((DWORD)(0x4db8b4u));	/* 4076db: mov eax, dword ptr [0x4db8b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4076e0: test eax, eax */
	if (m->zf) goto L_4076e9;	/* 4076e2: je 0x4076e9 */
	native_call(m, 0x406b60u); return;	/* 4076e4: jmp 0x406b60 */
L_4076e9:
	m->eax = M32((DWORD)(0x907b2cu));	/* 4076e9: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4076ee: test eax, eax */
	if (m->zf) goto L_4076f7;	/* 4076f0: je 0x4076f7 */
	native_call(m, 0x406bd0u); return;	/* 4076f2: jmp 0x406bd0 */
L_4076f7:
	native_call(m, 0x406c30u); return;	/* 4076f7: jmp 0x406c30 */
L_4076fc:
	m->eax = M32((DWORD)(0x907b2cu));	/* 4076fc: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 407701: test eax, eax */
	if (m->zf) goto L_40770a;	/* 407703: je 0x40770a */
	native_call(m, 0x407270u); return;	/* 407705: jmp 0x407270 */
L_40770a:
	m->eax = M32((DWORD)(0x4db508u));	/* 40770a: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40770f: test eax, eax */
	if (m->zf) goto L_407718;	/* 407711: je 0x407718 */
	native_call(m, 0x4036c0u); return;	/* 407713: jmp 0x4036c0 */
L_407718:
	m->eax = M32((DWORD)(0x4db55cu));	/* 407718: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40771d: test eax, eax */
	if (m->zf) goto L_407726;	/* 40771f: je 0x407726 */
	m->esp -= 4; M32(m->esp) = 0x407726u; native_call(m, 0x407300u);	/* 407721: call 0x407300 */
L_407726:
	native_call(m, 0x407410u); return;	/* 407726: jmp 0x407410 */
L_40772b:
	m->esp += 4 + 0; return;	/* 40772b: ret  */
}

/* menuState400_frame (0x40d450), lifted by tools/lift.py */
static void lift_40d450(X86 *m)
{
	m->eax = M32((DWORD)(0x4db51cu));	/* 40d450: mov eax, dword ptr [0x4db51c] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d455: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_40d4b9;	/* 40d458: ja 0x40d4b9 */
	switch (m->eax) { case 0: goto L_40d48c; case 1: goto L_40d49b; case 2: goto L_40d4aa; case 3: goto L_40d4b9; case 4: goto L_40d4b9; case 5: goto L_40d461; default: abort(); }	/* 40d45a: jmp dword ptr [eax*4 + 0x40d4bc] */
L_40d461:
	m->esp -= 4; M32(m->esp) = 0x40d466u; native_call(m, 0x40cef0u);	/* 40d461: call 0x40cef0 */
	{ DWORD a_ = M32((DWORD)(0x67ef14u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d466: cmp dword ptr [0x67ef14], 1 */
	if (!m->zf) goto L_40d482;	/* 40d46d: jne 0x40d482 */
	{ DWORD a_ = M32((DWORD)(0x4dbb3cu)), b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d46f: cmp dword ptr [0x4dbb3c], 2 */
	if (!m->zf) goto L_40d482;	/* 40d476: jne 0x40d482 */
	m->esp -= 4; M32(m->esp) = 0x40d47du; native_call(m, 0x441740u);	/* 40d478: call 0x441740 */
	native_call(m, 0x40ce70u); return;	/* 40d47d: jmp 0x40ce70 */
L_40d482:
	m->esp -= 4; M32(m->esp) = 0x40d487u; native_call(m, 0x441740u);	/* 40d482: call 0x441740 */
	native_call(m, 0x408680u); return;	/* 40d487: jmp 0x408680 */
L_40d48c:
	m->esp -= 4; M32(m->esp) = 0x40d491u; native_call(m, 0x441740u);	/* 40d48c: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x40d496u; native_call(m, 0x408270u);	/* 40d491: call 0x408270 */
	native_call(m, 0x40cf80u); return;	/* 40d496: jmp 0x40cf80 */
L_40d49b:
	m->esp -= 4; M32(m->esp) = 0x40d4a0u; native_call(m, 0x441740u);	/* 40d49b: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x40d4a5u; native_call(m, 0x408270u);	/* 40d4a0: call 0x408270 */
	native_call(m, 0x40cfd0u); return;	/* 40d4a5: jmp 0x40cfd0 */
L_40d4aa:
	m->esp -= 4; M32(m->esp) = 0x40d4afu; native_call(m, 0x441740u);	/* 40d4aa: call 0x441740 */
	m->esp -= 4; M32(m->esp) = 0x40d4b4u; native_call(m, 0x408270u);	/* 40d4af: call 0x408270 */
	native_call(m, 0x40d390u); return;	/* 40d4b4: jmp 0x40d390 */
L_40d4b9:
	m->esp += 4 + 0; return;	/* 40d4b9: ret  */
}

/* menu_onStateChange (0x445e40), lifted by tools/lift.py */
static void lift_445e40(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x445e45u; native_call(m, 0x445c60u);	/* 445e40: call 0x445c60 */
	m->eax = M32((DWORD)(0x680370u));	/* 445e45: mov eax, dword ptr [0x680370] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445e4a: test eax, eax */
	if (!m->zf) goto L_445edd;	/* 445e4c: jne 0x445edd */
	m->eax = M32((DWORD)(0x4df900u));	/* 445e52: mov eax, dword ptr [0x4df900] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 445e57: test eax, eax */
	if (m->zf) goto L_445e60;	/* 445e59: je 0x445e60 */
	native_call(m, 0x445e10u); return;	/* 445e5b: jmp 0x445e10 */
L_445e60:
	m->eax = M32((DWORD)(0x76d3e8u));	/* 445e60: mov eax, dword ptr [0x76d3e8] */
	{ DWORD a_ = m->eax, b_ = 0x258u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445e65: cmp eax, 0x258 */
	if (!m->zf && m->sf == m->of) goto L_445ead;	/* 445e6a: jg 0x445ead */
	if (m->zf) goto L_445ea8;	/* 445e6c: je 0x445ea8 */
	{ DWORD a_ = m->eax, b_ = 0x12cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445e6e: cmp eax, 0x12c */
	if (!m->zf && m->sf == m->of) goto L_445e92;	/* 445e73: jg 0x445e92 */
	if (m->zf) goto L_445e8d;	/* 445e75: je 0x445e8d */
	{ DWORD a_ = m->eax, b_ = 0xc8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445e77: sub eax, 0xc8 */
	if (m->zf) goto L_445e88;	/* 445e7c: je 0x445e88 */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445e7e: sub eax, 0xa */
	if (!m->zf) goto L_445edd;	/* 445e81: jne 0x445edd */
	native_call(m, 0x44c560u); return;	/* 445e83: jmp 0x44c560 */
L_445e88:
	native_call(m, 0x445de0u); return;	/* 445e88: jmp 0x445de0 */
L_445e8d:
	native_call(m, 0x4419d0u); return;	/* 445e8d: jmp 0x4419d0 */
L_445e92:
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445e92: sub eax, 0x190 */
	if (m->zf) goto L_445ea3;	/* 445e97: je 0x445ea3 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445e99: sub eax, 0x64 */
	if (!m->zf) goto L_445edd;	/* 445e9c: jne 0x445edd */
	native_call(m, 0x447b10u); return;	/* 445e9e: jmp 0x447b10 */
L_445ea3:
	lift_4076c0(m); return;	/* 445ea3: jmp 0x4076c0 */
L_445ea8:
	native_call(m, 0x422b30u); return;	/* 445ea8: jmp 0x422b30 */
L_445ead:
	{ DWORD a_ = m->eax, b_ = 0x384u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445ead: cmp eax, 0x384 */
	if (!m->zf && m->sf == m->of) goto L_445ed1;	/* 445eb2: jg 0x445ed1 */
	if (m->zf) goto L_445ecc;	/* 445eb4: je 0x445ecc */
	{ DWORD a_ = m->eax, b_ = 0x2bcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445eb6: sub eax, 0x2bc */
	if (m->zf) goto L_445ec7;	/* 445ebb: je 0x445ec7 */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 445ebd: sub eax, 0x64 */
	if (!m->zf) goto L_445edd;	/* 445ec0: jne 0x445edd */
	native_call(m, 0x436800u); return;	/* 445ec2: jmp 0x436800 */
L_445ec7:
	native_call(m, 0x410190u); return;	/* 445ec7: jmp 0x410190 */
L_445ecc:
	native_call(m, 0x443ef0u); return;	/* 445ecc: jmp 0x443ef0 */
L_445ed1:
	{ DWORD a_ = m->eax, b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 445ed1: cmp eax, 0x270f */
	if (!m->zf) goto L_445edd;	/* 445ed6: jne 0x445edd */
	native_call(m, 0x42ab70u); return;	/* 445ed8: jmp 0x42ab70 */
L_445edd:
	m->esp += 4 + 0; return;	/* 445edd: ret  */
}

/* room_43e290 (0x43e290), lifted by tools/lift.py */
static void lift_43e290(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd4a0u));	/* 43e290: mov eax, dword ptr [0x9dd4a0] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43e295: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43e296: push ebp */
	{ DWORD a_ = m->ebp, b_ = m->ebp & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebp = r_; }	/* 43e297: xor ebp, ebp */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e299: cmp eax, ebp */
	if (m->zf) goto L_43e2af;	/* 43e29b: je 0x43e2af */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43e29d: push ebp */
	m->esp -= 4; M32(m->esp) = 0x43e2a3u; native_call(m, 0x433e60u);	/* 43e29e: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e2a3: add esp, 4 */
	M32((DWORD)(0x9dd4a0u)) = m->ebp;	/* 43e2a6: mov dword ptr [0x9dd4a0], ebp */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e2ac: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e2ad: pop ebx */
	m->esp += 4 + 0; return;	/* 43e2ae: ret  */
L_43e2af:
	{ DWORD a_ = M32((DWORD)(0x4df900u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e2af: cmp dword ptr [0x4df900], ebp */
	if (!m->zf) goto L_43e603;	/* 43e2b5: jne 0x43e603 */
	{ DWORD a_ = M32((DWORD)(0x68039cu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e2bb: cmp dword ptr [0x68039c], ebp */
	if (!m->zf) goto L_43e603;	/* 43e2c1: jne 0x43e603 */
	m->eax = M32((DWORD)(0x9dc428u));	/* 43e2c7: mov eax, dword ptr [0x9dc428] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43e2cc: push esi */
	{ DWORD a_ = m->eax, b_ = 0x14u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e2cd: cmp eax, 0x14 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 43e2d0: push edi */
	m->ebx = 0x1u;	/* 43e2d1: mov ebx, 1 */
	if (!m->zf) goto L_43e43e;	/* 43e2d6: jne 0x43e43e */
	{ DWORD a_ = M32((DWORD)(0x9dd348u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e2dc: cmp dword ptr [0x9dd348], ebx */
	if (!m->zf) goto L_43e32a;	/* 43e2e2: jne 0x43e32a */
	m->ecx = 0x7u;	/* 43e2e4: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e2e9: xor eax, eax */
	m->edi = 0x9dd1d8u;	/* 43e2eb: mov edi, 0x9dd1d8 */
	M32((DWORD)(0x9dd348u)) = m->ebp;	/* 43e2f0: mov dword ptr [0x9dd348], ebp */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43e2f6: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43e2f8: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 43e2fa: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e2ff: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e302: xor eax, eax */
	M32((DWORD)(0x9dd3f8u)) = m->ebx;	/* 43e304: mov dword ptr [0x9dd3f8], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e30a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e30c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e30e: sub edi, ecx */
	m->eax = m->ecx;	/* 43e310: mov eax, ecx */
	m->esi = m->edi;	/* 43e312: mov esi, edi */
	m->edi = 0x9dd1d8u;	/* 43e314: mov edi, 0x9dd1d8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e319: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e31c: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43e31e: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e320: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e323: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_43e5ae;	/* 43e325: jmp 0x43e5ae */
L_43e32a:
	{ DWORD a_ = M32((DWORD)(0x9dd3f8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e32a: cmp dword ptr [0x9dd3f8], ebx */
	if (!m->zf) goto L_43e376;	/* 43e330: jne 0x43e376 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e332: xor ecx, ecx */
	m->edi = 0x9dc92cu;	/* 43e334: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd1f6u)) = m->ecx;	/* 43e339: mov dword ptr [0x9dd1f6], ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e33f: xor eax, eax */
	M32((DWORD)(0x9dd1fau)) = m->ecx;	/* 43e341: mov dword ptr [0x9dd1fa], ecx */
	M32((DWORD)(0x9dd3f8u)) = m->ebp;	/* 43e347: mov dword ptr [0x9dd3f8], ebp */
	M32((DWORD)(0x9dd1feu)) = m->ecx;	/* 43e34d: mov dword ptr [0x9dd1fe], ecx */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e353: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e356: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e358: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e35a: sub edi, ecx */
	m->edx = m->ecx;	/* 43e35c: mov edx, ecx */
	m->esi = m->edi;	/* 43e35e: mov esi, edi */
	m->edi = 0x9dd1f6u;	/* 43e360: mov edi, 0x9dd1f6 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e365: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e368: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43e36a: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e36c: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e36f: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_43e5a8;	/* 43e371: jmp 0x43e5a8 */
L_43e376:
	{ DWORD a_ = M32((DWORD)(0x9dd564u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e376: cmp dword ptr [0x9dd564], ebx */
	if (!m->zf) goto L_43e3c3;	/* 43e37c: jne 0x43e3c3 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e37e: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43e380: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd202u)) = m->eax;	/* 43e385: mov dword ptr [0x9dd202], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e38a: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd206u)) = m->eax;	/* 43e38d: mov dword ptr [0x9dd206], eax */
	M32((DWORD)(0x9dd564u)) = m->ebp;	/* 43e392: mov dword ptr [0x9dd564], ebp */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e398: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e39a: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e39c: sub edi, ecx */
	M32((DWORD)(0x9dd20au)) = m->eax;	/* 43e39e: mov dword ptr [0x9dd20a], eax */
	m->edx = m->ecx;	/* 43e3a3: mov edx, ecx */
	m->esi = m->edi;	/* 43e3a5: mov esi, edi */
	m->edi = 0x9dd202u;	/* 43e3a7: mov edi, 0x9dd202 */
	M32((DWORD)(0x9dd6ccu)) = m->ebx;	/* 43e3ac: mov dword ptr [0x9dd6cc], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e3b2: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e3b5: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43e3b7: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e3b9: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e3bc: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_43e5ae;	/* 43e3be: jmp 0x43e5ae */
L_43e3c3:
	{ DWORD a_ = M32((DWORD)(0x9dd6ccu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e3c3: cmp dword ptr [0x9dd6cc], ebx */
	if (!m->zf) goto L_43e5ae;	/* 43e3c9: jne 0x43e5ae */
	m->ecx = 0xcu;	/* 43e3cf: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e3d4: xor eax, eax */
	m->edi = 0x9dd20eu;	/* 43e3d6: mov edi, 0x9dd20e */
	M32((DWORD)(0x9dd6ccu)) = m->ebp;	/* 43e3db: mov dword ptr [0x9dd6cc], ebp */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43e3e1: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43e3e3: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 43e3e5: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e3ea: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e3ed: xor eax, eax */
	M32((DWORD)(0x9dd348u)) = m->ebp;	/* 43e3ef: mov dword ptr [0x9dd348], ebp */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e3f5: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e3f7: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e3f9: sub edi, ecx */
	M32((DWORD)(0x74de1cu)) = m->ebx;	/* 43e3fb: mov dword ptr [0x74de1c], ebx */
	m->eax = m->ecx;	/* 43e401: mov eax, ecx */
	m->esi = m->edi;	/* 43e403: mov esi, edi */
	m->edi = 0x9dd20eu;	/* 43e405: mov edi, 0x9dd20e */
	M32((DWORD)(0x76d42cu)) = m->ebx;	/* 43e40a: mov dword ptr [0x76d42c], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e410: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e413: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43e415: mov ecx, eax */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 43e417: mov dword ptr [0x680bc0], 0x41a00000 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e421: and ecx, 3 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 43e424: mov dword ptr [0x9da4a4], 0x3ecccccd */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e42e: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd6e8u));	/* 43e430: mov ecx, dword ptr [0x9dd6e8] */
	{ DWORD a_ = m->ecx, b_ = 0xaau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43e436: add ecx, 0xaa */
	goto L_43e4b4;	/* 43e43c: jmp 0x43e4b4 */
L_43e43e:
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e43e: cmp eax, 0xa */
	if (!m->zf) goto L_43e5b4;	/* 43e441: jne 0x43e5b4 */
	{ DWORD a_ = M32((DWORD)(0x9dd348u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e447: cmp dword ptr [0x9dd348], ebx */
	if (!m->zf) goto L_43e4ce;	/* 43e44d: jne 0x43e4ce */
	m->ecx = 0x7u;	/* 43e44f: mov ecx, 7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e454: xor eax, eax */
	m->edi = 0x9dd1d8u;	/* 43e456: mov edi, 0x9dd1d8 */
	M32((DWORD)(0x74de1cu)) = 0x2u;	/* 43e45b: mov dword ptr [0x74de1c], 2 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43e465: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43e467: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 43e469: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e46e: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e471: xor eax, eax */
	M32((DWORD)(0x76d42cu)) = m->ebx;	/* 43e473: mov dword ptr [0x76d42c], ebx */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e479: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e47b: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e47d: sub edi, ecx */
	M32((DWORD)(0x680bc0u)) = 0x41a00000u;	/* 43e47f: mov dword ptr [0x680bc0], 0x41a00000 */
	m->eax = m->ecx;	/* 43e489: mov eax, ecx */
	m->esi = m->edi;	/* 43e48b: mov esi, edi */
	m->edi = 0x9dd1d8u;	/* 43e48d: mov edi, 0x9dd1d8 */
	M32((DWORD)(0x9da4a4u)) = 0x3ecccccdu;	/* 43e492: mov dword ptr [0x9da4a4], 0x3ecccccd */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e49c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e49f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43e4a1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e4a3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e4a6: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0x9dd6e8u));	/* 43e4a8: mov ecx, dword ptr [0x9dd6e8] */
	{ DWORD a_ = m->ecx, b_ = 0x172u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 43e4ae: add ecx, 0x172 */
L_43e4b4:
	m->edx = M32((DWORD)(0x9dd6f4u));	/* 43e4b4: mov edx, dword ptr [0x9dd6f4] */
	M32((DWORD)(0x67ef34u)) = m->ecx;	/* 43e4ba: mov dword ptr [0x67ef34], ecx */
	{ DWORD a_ = m->edx, b_ = 0xffffffd4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 43e4c0: add edx, -0x2c */
	M32((DWORD)(0x67fb38u)) = m->edx;	/* 43e4c3: mov dword ptr [0x67fb38], edx */
	goto L_43e5ae;	/* 43e4c9: jmp 0x43e5ae */
L_43e4ce:
	{ DWORD a_ = M32((DWORD)(0x9dd3f8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e4ce: cmp dword ptr [0x9dd3f8], ebx */
	if (!m->zf) goto L_43e51b;	/* 43e4d4: jne 0x43e51b */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e4d6: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43e4d8: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd1f6u)) = m->eax;	/* 43e4dd: mov dword ptr [0x9dd1f6], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e4e2: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd1fau)) = m->eax;	/* 43e4e5: mov dword ptr [0x9dd1fa], eax */
	M32((DWORD)(0x9dd3f8u)) = m->ebp;	/* 43e4ea: mov dword ptr [0x9dd3f8], ebp */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e4f0: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e4f2: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e4f4: sub edi, ecx */
	M32((DWORD)(0x9dd1feu)) = m->eax;	/* 43e4f6: mov dword ptr [0x9dd1fe], eax */
	m->edx = m->ecx;	/* 43e4fb: mov edx, ecx */
	m->esi = m->edi;	/* 43e4fd: mov esi, edi */
	m->edi = 0x9dd1f6u;	/* 43e4ff: mov edi, 0x9dd1f6 */
	M32((DWORD)(0x9dd348u)) = m->ebx;	/* 43e504: mov dword ptr [0x9dd348], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e50a: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e50d: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43e50f: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e511: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e514: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_43e5ae;	/* 43e516: jmp 0x43e5ae */
L_43e51b:
	{ DWORD a_ = M32((DWORD)(0x9dd564u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e51b: cmp dword ptr [0x9dd564], ebx */
	if (!m->zf) goto L_43e565;	/* 43e521: jne 0x43e565 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e523: xor eax, eax */
	m->edi = 0x9dc92cu;	/* 43e525: mov edi, 0x9dc92c */
	M32((DWORD)(0x9dd202u)) = m->eax;	/* 43e52a: mov dword ptr [0x9dd202], eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e52f: or ecx, 0xffffffff */
	M32((DWORD)(0x9dd206u)) = m->eax;	/* 43e532: mov dword ptr [0x9dd206], eax */
	M32((DWORD)(0x9dd564u)) = m->ebp;	/* 43e537: mov dword ptr [0x9dd564], ebp */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e53d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e53f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e541: sub edi, ecx */
	M32((DWORD)(0x9dd20au)) = m->eax;	/* 43e543: mov dword ptr [0x9dd20a], eax */
	m->edx = m->ecx;	/* 43e548: mov edx, ecx */
	m->esi = m->edi;	/* 43e54a: mov esi, edi */
	m->edi = 0x9dd202u;	/* 43e54c: mov edi, 0x9dd202 */
	M32((DWORD)(0x9dd3f8u)) = m->ebx;	/* 43e551: mov dword ptr [0x9dd3f8], ebx */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e557: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e55a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 43e55c: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e55e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e561: rep movsb byte ptr es:[edi], byte ptr [esi] */
	goto L_43e5ae;	/* 43e563: jmp 0x43e5ae */
L_43e565:
	{ DWORD a_ = M32((DWORD)(0x9dd6ccu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e565: cmp dword ptr [0x9dd6cc], ebx */
	if (!m->zf) goto L_43e5ae;	/* 43e56b: jne 0x43e5ae */
	m->ecx = 0xcu;	/* 43e56d: mov ecx, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e572: xor eax, eax */
	m->edi = 0x9dd20eu;	/* 43e574: mov edi, 0x9dd20e */
	M32((DWORD)(0x9dd6ccu)) = m->ebp;	/* 43e579: mov dword ptr [0x9dd6cc], ebp */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 43e57f: rep stosd dword ptr es:[edi], eax */
	M16(m->edi) = (WORD)(m->eax & 0xffffu); m->edi += 2;	/* 43e581: stosw word ptr es:[edi], ax */
	m->edi = 0x9dc92cu;	/* 43e583: mov edi, 0x9dc92c */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e588: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 43e58b: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 43e58d: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 43e58f: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 43e591: sub edi, ecx */
	m->eax = m->ecx;	/* 43e593: mov eax, ecx */
	m->esi = m->edi;	/* 43e595: mov esi, edi */
	m->edi = 0x9dd20eu;	/* 43e597: mov edi, 0x9dd20e */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 43e59c: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 43e59f: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 43e5a1: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43e5a3: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 43e5a6: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_43e5a8:
	M32((DWORD)(0x9dd564u)) = m->ebx;	/* 43e5a8: mov dword ptr [0x9dd564], ebx */
L_43e5ae:
	M32((DWORD)(0x9dc428u)) = m->ebp;	/* 43e5ae: mov dword ptr [0x9dc428], ebp */
L_43e5b4:
	m->eax = M32((DWORD)(0x9dd348u));	/* 43e5b4: mov eax, dword ptr [0x9dd348] */
	m->edi = M32(m->esp); m->esp += 4;	/* 43e5b9: pop edi */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e5ba: cmp eax, ebx */
	m->esi = M32(m->esp); m->esp += 4;	/* 43e5bc: pop esi */
	if (!m->zf) goto L_43e5cb;	/* 43e5bd: jne 0x43e5cb */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 43e5bf: push ebp */
	m->esp -= 4; M32(m->esp) = 0x43e5c5u; native_call(m, 0x433e60u);	/* 43e5c0: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e5c5: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e5c8: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e5c9: pop ebx */
	m->esp += 4 + 0; return;	/* 43e5ca: ret  */
L_43e5cb:
	{ DWORD a_ = M32((DWORD)(0x9dd3f8u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e5cb: cmp dword ptr [0x9dd3f8], ebx */
	if (!m->zf) goto L_43e5dc;	/* 43e5d1: jne 0x43e5dc */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 43e5d3: push ebx */
	m->esp -= 4; M32(m->esp) = 0x43e5d9u; native_call(m, 0x433e60u);	/* 43e5d4: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e5d9: add esp, 4 */
L_43e5dc:
	{ DWORD a_ = M32((DWORD)(0x9dd564u)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e5dc: cmp dword ptr [0x9dd564], ebx */
	if (!m->zf) goto L_43e5f1;	/* 43e5e2: jne 0x43e5f1 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 43e5e4: push 2 */
	m->esp -= 4; M32(m->esp) = 0x43e5ebu; native_call(m, 0x433e60u);	/* 43e5e6: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e5eb: add esp, 4 */
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e5ee: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e5ef: pop ebx */
	m->esp += 4 + 0; return;	/* 43e5f0: ret  */
L_43e5f1:
	{ DWORD a_ = M32((DWORD)(0x9dd6ccu)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43e5f1: cmp dword ptr [0x9dd6cc], ebx */
	if (!m->zf) goto L_43e603;	/* 43e5f7: jne 0x43e603 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 43e5f9: push 3 */
	m->esp -= 4; M32(m->esp) = 0x43e600u; native_call(m, 0x433e60u);	/* 43e5fb: call 0x433e60 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43e600: add esp, 4 */
L_43e603:
	m->ebp = M32(m->esp); m->esp += 4;	/* 43e603: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 43e604: pop ebx */
	m->esp += 4 + 0; return;	/* 43e605: ret  */
}

/* arena_launchFromFile (0x410b50), lifted by tools/lift.py */
static void lift_410b50(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 410b50: push ecx */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 410b51: fld dword ptr [0x4b071c] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9418u)); FPOP();	/* 410b57: fcomp dword ptr [0x4a9418] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410b5d: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410b5f: test ah, 0x41 */
	if (!m->zf) goto L_410b6e;	/* 410b62: jne 0x410b6e */
	M32((DWORD)(0x4b071cu)) = 0x3f800000u;	/* 410b64: mov dword ptr [0x4b071c], 0x3f800000 */
L_410b6e:
	m->ecx = M32((DWORD)(0x4dc24cu));	/* 410b6e: mov ecx, dword ptr [0x4dc24c] */
	M32((DWORD)(m->esp + 0x0u)) = 0xc4098000u;	/* 410b74: mov dword ptr [esp], 0xc4098000 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9474u)));	/* 410b7c: fld dword ptr [0x4a9474] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410b82: cmp ecx, 3 */
	if (!m->zf) goto L_410b97;	/* 410b85: jne 0x410b97 */
	ST(0) = ST(0); FPOP();	/* 410b87: fstp st(0) */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9470u)));	/* 410b89: fld dword ptr [0x4a9470] */
	M32((DWORD)(m->esp + 0x0u)) = 0xc4ce4000u;	/* 410b8f: mov dword ptr [esp], 0xc4ce4000 */
L_410b97:
	m->eax = M32((DWORD)(0x4dc790u));	/* 410b97: mov eax, dword ptr [0x4dc790] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 410b9c: push esi */
	m->esi = 0x1u;	/* 410b9d: mov esi, 1 */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410ba2: cmp eax, esi */
	if (!m->zf) goto L_410d36;	/* 410ba4: jne 0x410d36 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df870u)));	/* 410baa: fld dword ptr [0x4df870] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 410bb0: fsub dword ptr [0x4df024] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410bb6: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410bbc: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 410bc2: fadd dword ptr [0x4df024] */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 410bc8: fstp dword ptr [0x4df024] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df874u)));	/* 410bce: fld dword ptr [0x4df874] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 410bd4: fsub dword ptr [0x4df028] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410bda: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410be0: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 410be6: fadd dword ptr [0x4df028] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 410bec: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df878u)));	/* 410bf2: fld dword ptr [0x4df878] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 410bf8: fsub dword ptr [0x4df02c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410bfe: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410c04: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 410c0a: fadd dword ptr [0x4df02c] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 410c10: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d388u)));	/* 410c16: fld dword ptr [0x76d388] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x680378u));	/* 410c1c: fsub dword ptr [0x680378] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410c22: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410c28: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680378u));	/* 410c2e: fadd dword ptr [0x680378] */
	MF((DWORD)(0x680378u)) = (float)ST(0); FPOP();	/* 410c34: fstp dword ptr [0x680378] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d38cu)));	/* 410c3a: fld dword ptr [0x76d38c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x68037cu));	/* 410c40: fsub dword ptr [0x68037c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410c46: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410c4c: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x68037cu));	/* 410c52: fadd dword ptr [0x68037c] */
	MF((DWORD)(0x68037cu)) = (float)ST(0); FPOP();	/* 410c58: fstp dword ptr [0x68037c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x76d390u)));	/* 410c5e: fld dword ptr [0x76d390] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x680380u));	/* 410c64: fsub dword ptr [0x680380] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410c6a: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410c70: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x680380u));	/* 410c76: fadd dword ptr [0x680380] */
	MF((DWORD)(0x680380u)) = (float)ST(0);	/* 410c7c: fst dword ptr [0x680380] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 410c82: fld dword ptr [0x4e1870] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 410c88: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410c8e: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410c90: test ah, 0x41 */
	if (!m->zf) goto L_410cad;	/* 410c93: jne 0x410cad */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 410c95: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a946cu));	/* 410c9b: fmul dword ptr [0x4a946c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4e1870u));	/* 410ca1: fsubr dword ptr [0x4e1870] */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 410ca7: fstp dword ptr [0x4e1870] */
L_410cad:
	FCOM(ST(0), ST(1)); FPOP();	/* 410cad: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410caf: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410cb1: test ah, 0x41 */
	ST(0) = ST(0); FPOP();	/* 410cb4: fstp st(0) */
	if (!m->zf) goto L_411101;	/* 410cb6: jne 0x411101 */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410cbc: cmp ecx, 3 */
	M32((DWORD)(0x4df024u)) = 0x0u;	/* 410cbf: mov dword ptr [0x4df024], 0 */
	M32((DWORD)(0x4df028u)) = 0xc3480000u;	/* 410cc9: mov dword ptr [0x4df028], 0xc3480000 */
	M32((DWORD)(0x4df02cu)) = 0x43c80000u;	/* 410cd3: mov dword ptr [0x4df02c], 0x43c80000 */
	if (m->zf) goto L_410ce9;	/* 410cdd: je 0x410ce9 */
	M32((DWORD)(0x4df02cu)) = 0x44bb8000u;	/* 410cdf: mov dword ptr [0x4df02c], 0x44bb8000 */
L_410ce9:
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 410ce9: fild dword ptr [0x5b1998] */
	M32((DWORD)(0x90d1c4u)) = m->esi;	/* 410cef: mov dword ptr [0x90d1c4], esi */
	M32((DWORD)(0x680378u)) = 0x0u;	/* 410cf5: mov dword ptr [0x680378], 0 */
	M32((DWORD)(0x68037cu)) = 0xc3480000u;	/* 410cff: mov dword ptr [0x68037c], 0xc3480000 */
	M32((DWORD)(0x680380u)) = 0x0u;	/* 410d09: mov dword ptr [0x680380], 0 */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(0x4e045cu));	/* 410d13: fidiv dword ptr [0x4e045c] */
	M32((DWORD)(0x4dc790u)) = 0x2u;	/* 410d19: mov dword ptr [0x4dc790], 2 */
	M32((DWORD)(0x4dc868u)) = 0x0u;	/* 410d23: mov dword ptr [0x4dc868], 0 */
	m->esi = M32(m->esp); m->esp += 4;	/* 410d2d: pop esi */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 410d2e: fstp dword ptr [0x4e1870] */
	m->ecx = M32(m->esp); m->esp += 4;	/* 410d34: pop ecx */
	m->esp += 4 + 0; return;	/* 410d35: ret  */
L_410d36:
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 410d36: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 410d38: cmp eax, edx */
	ST(0) = ST(0); FPOP();	/* 410d3a: fstp st(0) */
	if (!m->zf) goto L_411101;	/* 410d3c: jne 0x411101 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4u)));	/* 410d42: fld dword ptr [esp + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 410d46: fadd dword ptr [0x4a9424] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x680380u)); FPOP();	/* 410d4c: fcomp dword ptr [0x680380] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df024u)));	/* 410d52: fld dword ptr [0x4df024] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db090u));	/* 410d58: fsub dword ptr [0x9db090] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410d5e: fnstsw ax */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410d60: fmul dword ptr [0x4b071c] */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410d66: test ah, 1 */
	if (m->zf) goto L_410e6b;	/* 410d69: je 0x410e6b */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410d6f: fmul dword ptr [0x4a93ec] */
	M32((DWORD)(0x4dc868u)) = m->esi;	/* 410d75: mov dword ptr [0x4dc868], esi */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 410d7b: fsubr dword ptr [0x4df024] */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 410d81: fstp dword ptr [0x4df024] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df028u)));	/* 410d87: fld dword ptr [0x4df028] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db094u));	/* 410d8d: fsub dword ptr [0x9db094] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410d93: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410d99: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 410d9f: fsubr dword ptr [0x4df028] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 410da5: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 410dab: fld dword ptr [0x4df02c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db098u));	/* 410db1: fsub dword ptr [0x9db098] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410db7: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410dbd: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 410dc3: fsubr dword ptr [0x4df02c] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 410dc9: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680378u)));	/* 410dcf: fld dword ptr [0x680378] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d3f8u));	/* 410dd5: fsub dword ptr [0x76d3f8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410ddb: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410de1: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x680378u));	/* 410de7: fsubr dword ptr [0x680378] */
	MF((DWORD)(0x680378u)) = (float)ST(0); FPOP();	/* 410ded: fstp dword ptr [0x680378] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68037cu)));	/* 410df3: fld dword ptr [0x68037c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d3fcu));	/* 410df9: fsub dword ptr [0x76d3fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410dff: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410e05: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x68037cu));	/* 410e0b: fsubr dword ptr [0x68037c] */
	MF((DWORD)(0x68037cu)) = (float)ST(0); FPOP();	/* 410e11: fstp dword ptr [0x68037c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680380u)));	/* 410e17: fld dword ptr [0x680380] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d400u));	/* 410e1d: fsub dword ptr [0x76d400] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410e23: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 410e29: fmul dword ptr [0x4a93ec] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x680380u));	/* 410e2f: fsubr dword ptr [0x680380] */
	MF((DWORD)(0x680380u)) = (float)ST(0); FPOP();	/* 410e35: fstp dword ptr [0x680380] */
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 410e3b: fild dword ptr [0x5b1998] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(0x4e045cu));	/* 410e41: fidiv dword ptr [0x4e045c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 410e47: fld dword ptr [0x4e1870] */
	FCOM(ST(0), ST(1)); FPOP();	/* 410e4d: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410e4f: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410e51: test ah, 1 */
	if (m->zf) goto L_410f6a;	/* 410e54: je 0x410f6a */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 410e5a: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9468u));	/* 410e60: fmul dword ptr [0x4a9468] */
	goto L_410f5e;	/* 410e66: jmp 0x410f5e */
L_410e6b:
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410e6b: fmul dword ptr [0x4a942c] */
	M32((DWORD)(0x4dc868u)) = m->esi;	/* 410e71: mov dword ptr [0x4dc868], esi */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df024u));	/* 410e77: fsubr dword ptr [0x4df024] */
	MF((DWORD)(0x4df024u)) = (float)ST(0); FPOP();	/* 410e7d: fstp dword ptr [0x4df024] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df028u)));	/* 410e83: fld dword ptr [0x4df028] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db094u));	/* 410e89: fsub dword ptr [0x9db094] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410e8f: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410e95: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df028u));	/* 410e9b: fsubr dword ptr [0x4df028] */
	MF((DWORD)(0x4df028u)) = (float)ST(0); FPOP();	/* 410ea1: fstp dword ptr [0x4df028] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4df02cu)));	/* 410ea7: fld dword ptr [0x4df02c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x9db098u));	/* 410ead: fsub dword ptr [0x9db098] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410eb3: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410eb9: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x4df02cu));	/* 410ebf: fsubr dword ptr [0x4df02c] */
	MF((DWORD)(0x4df02cu)) = (float)ST(0); FPOP();	/* 410ec5: fstp dword ptr [0x4df02c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680378u)));	/* 410ecb: fld dword ptr [0x680378] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d3f8u));	/* 410ed1: fsub dword ptr [0x76d3f8] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410ed7: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410edd: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x680378u));	/* 410ee3: fsubr dword ptr [0x680378] */
	MF((DWORD)(0x680378u)) = (float)ST(0); FPOP();	/* 410ee9: fstp dword ptr [0x680378] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x68037cu)));	/* 410eef: fld dword ptr [0x68037c] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d3fcu));	/* 410ef5: fsub dword ptr [0x76d3fc] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410efb: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410f01: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x68037cu));	/* 410f07: fsubr dword ptr [0x68037c] */
	MF((DWORD)(0x68037cu)) = (float)ST(0); FPOP();	/* 410f0d: fstp dword ptr [0x68037c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x680380u)));	/* 410f13: fld dword ptr [0x680380] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0x76d400u));	/* 410f19: fsub dword ptr [0x76d400] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4b071cu));	/* 410f1f: fmul dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a942cu));	/* 410f25: fmul dword ptr [0x4a942c] */
	ST(0) = x87_subrm(ST(0), (const float *)(DWORD)(0x680380u));	/* 410f2b: fsubr dword ptr [0x680380] */
	MF((DWORD)(0x680380u)) = (float)ST(0); FPOP();	/* 410f31: fstp dword ptr [0x680380] */
	FPUSH((long double)(int)M32((DWORD)(0x5b1998u)));	/* 410f37: fild dword ptr [0x5b1998] */
	ST(0) = ST(0) / (long double)(int)M32((DWORD)(0x4e045cu));	/* 410f3d: fidiv dword ptr [0x4e045c] */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4e1870u)));	/* 410f43: fld dword ptr [0x4e1870] */
	FCOM(ST(0), ST(1)); FPOP();	/* 410f49: fcomp st(1) */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410f4b: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410f4d: test ah, 1 */
	if (m->zf) goto L_410f6a;	/* 410f50: je 0x410f6a */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 410f52: fld dword ptr [0x4b071c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 410f58: fmul dword ptr [0x4a9420] */
L_410f5e:
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4e1870u));	/* 410f5e: fadd dword ptr [0x4e1870] */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 410f64: fstp dword ptr [0x4e1870] */
L_410f6a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x4u)));	/* 410f6a: fld dword ptr [esp + 4] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9420u));	/* 410f6e: fadd dword ptr [0x4a9420] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x680380u)); FPOP();	/* 410f74: fcomp dword ptr [0x680380] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 410f7a: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 410f7c: test ah, 1 */
	if (!m->zf) goto L_4110ff;	/* 410f7f: jne 0x4110ff */
	m->eax = M32((DWORD)(0x76d3f8u));	/* 410f85: mov eax, dword ptr [0x76d3f8] */
	M32((DWORD)(0x4dc790u)) = 0x2u;	/* 410f8a: mov dword ptr [0x4dc790], 2 */
	M32((DWORD)(0x680378u)) = m->eax;	/* 410f94: mov dword ptr [0x680378], eax */
	m->eax = M32((DWORD)(0x76d3fcu));	/* 410f99: mov eax, dword ptr [0x76d3fc] */
	M32((DWORD)(0x68037cu)) = m->eax;	/* 410f9e: mov dword ptr [0x68037c], eax */
	m->eax = M32((DWORD)(0x76d400u));	/* 410fa3: mov eax, dword ptr [0x76d400] */
	M32((DWORD)(0x680380u)) = m->eax;	/* 410fa8: mov dword ptr [0x680380], eax */
	m->eax = M32((DWORD)(0x9db090u));	/* 410fad: mov eax, dword ptr [0x9db090] */
	M32((DWORD)(0x4df024u)) = m->eax;	/* 410fb2: mov dword ptr [0x4df024], eax */
	m->eax = M32((DWORD)(0x9db094u));	/* 410fb7: mov eax, dword ptr [0x9db094] */
	M32((DWORD)(0x4df028u)) = m->eax;	/* 410fbc: mov dword ptr [0x4df028], eax */
	m->eax = M32((DWORD)(0x9db098u));	/* 410fc1: mov eax, dword ptr [0x9db098] */
	M32((DWORD)(0x4df02cu)) = m->eax;	/* 410fc6: mov dword ptr [0x4df02c], eax */
	m->eax = m->ecx;	/* 410fcb: mov eax, ecx */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410fcd: dec eax */
	M32((DWORD)(0x4dc798u)) = m->edx;	/* 410fce: mov dword ptr [0x4dc798], edx */
	if (m->zf) goto L_4110b8;	/* 410fd4: je 0x4110b8 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410fda: dec eax */
	if (m->zf) goto L_411018;	/* 410fdb: je 0x411018 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 410fdd: dec eax */
	if (!m->zf) goto L_4110e4;	/* 410fde: jne 0x4110e4 */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 410fe4: fstp dword ptr [0x4e1870] */
	m->eax = 0x320u;	/* 410fea: mov eax, 0x320 */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 410fef: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 410ff9: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 410ffe: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 411003: mov dword ptr [0x67ef20], eax */
	M32((DWORD)(0x4dc24cu)) = m->edx;	/* 411008: mov dword ptr [0x4dc24c], edx */
	m->esp -= 4; M32(m->esp) = 0x411013u; native_call(m, 0x433360u);	/* 41100e: call 0x433360 */
	goto L_4110e6;	/* 411013: jmp 0x4110e6 */
L_411018:
	m->ecx = M32((DWORD)(0x4db840u));	/* 411018: mov ecx, dword ptr [0x4db840] */
	m->eax = 0x190u;	/* 41101e: mov eax, 0x190 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 411023: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 411028: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 41102d: mov dword ptr [0x67ef20], eax */
	m->eax = M32((DWORD)(0x4db844u));	/* 411032: mov eax, dword ptr [0x4db844] */
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 411037: fstp dword ptr [0x4e1870] */
	M32((DWORD)(0x4df024u)) = m->ecx;	/* 41103d: mov dword ptr [0x4df024], ecx */
	m->ecx = M32((DWORD)(0x4db848u));	/* 411043: mov ecx, dword ptr [0x4db848] */
	M32((DWORD)(0x4df028u)) = m->eax;	/* 411049: mov dword ptr [0x4df028], eax */
	m->eax = M32((DWORD)(0x4dbab8u));	/* 41104e: mov eax, dword ptr [0x4dbab8] */
	M32((DWORD)(0x4df02cu)) = m->ecx;	/* 411053: mov dword ptr [0x4df02c], ecx */
	m->ecx = M32((DWORD)(0x4dbabcu));	/* 411059: mov ecx, dword ptr [0x4dbabc] */
	M32((DWORD)(0x680378u)) = m->eax;	/* 41105f: mov dword ptr [0x680378], eax */
	m->eax = M32((DWORD)(0x4dbac0u));	/* 411064: mov eax, dword ptr [0x4dbac0] */
	M32((DWORD)(0x68037cu)) = m->ecx;	/* 411069: mov dword ptr [0x68037c], ecx */
	M32((DWORD)(0x680380u)) = m->eax;	/* 41106f: mov dword ptr [0x680380], eax */
	M32((DWORD)(0x9db090u)) = 0x0u;	/* 411074: mov dword ptr [0x9db090], 0 */
	M32((DWORD)(0x9db094u)) = 0x0u;	/* 41107e: mov dword ptr [0x9db094], 0 */
	M32((DWORD)(0x9db098u)) = 0xc4c1c000u;	/* 411088: mov dword ptr [0x9db098], 0xc4c1c000 */
	M32((DWORD)(0x76d3f8u)) = 0x0u;	/* 411092: mov dword ptr [0x76d3f8], 0 */
	M32((DWORD)(0x76d3fcu)) = 0x0u;	/* 41109c: mov dword ptr [0x76d3fc], 0 */
	M32((DWORD)(0x76d400u)) = 0xc4ce4000u;	/* 4110a6: mov dword ptr [0x76d400], 0xc4ce4000 */
	M32((DWORD)(0x4dc24cu)) = m->edx;	/* 4110b0: mov dword ptr [0x4dc24c], edx */
	goto L_4110e6;	/* 4110b6: jmp 0x4110e6 */
L_4110b8:
	MF((DWORD)(0x4e1870u)) = (float)ST(0); FPOP();	/* 4110b8: fstp dword ptr [0x4e1870] */
	m->eax = 0x12cu;	/* 4110be: mov eax, 0x12c */
	M32((DWORD)(0x4dda44u)) = 0x0u;	/* 4110c3: mov dword ptr [0x4dda44], 0 */
	M32((DWORD)(0x76d3e8u)) = m->eax;	/* 4110cd: mov dword ptr [0x76d3e8], eax */
	M32((DWORD)(0x67ef0cu)) = m->eax;	/* 4110d2: mov dword ptr [0x67ef0c], eax */
	M32((DWORD)(0x67ef20u)) = m->eax;	/* 4110d7: mov dword ptr [0x67ef20], eax */
	M32((DWORD)(0x4dc24cu)) = m->edx;	/* 4110dc: mov dword ptr [0x4dc24c], edx */
	goto L_4110e6;	/* 4110e2: jmp 0x4110e6 */
L_4110e4:
	ST(0) = ST(0); FPOP();	/* 4110e4: fstp st(0) */
L_4110e6:
	{ DWORD a_ = M32((DWORD)(0x76d410u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4110e6: cmp dword ptr [0x76d410], esi */
	if (!m->zf) goto L_411101;	/* 4110ec: jne 0x411101 */
	{ DWORD a_ = M32((DWORD)(0x9da49cu)), b_ = 0x67u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4110ee: cmp dword ptr [0x9da49c], 0x67 */
	if (!m->zf) goto L_411101;	/* 4110f5: jne 0x411101 */
	m->esp -= 4; M32(m->esp) = 0x4110fcu; native_call(m, 0x40d840u);	/* 4110f7: call 0x40d840 */
	m->esi = M32(m->esp); m->esp += 4;	/* 4110fc: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4110fd: pop ecx */
	m->esp += 4 + 0; return;	/* 4110fe: ret  */
L_4110ff:
	ST(0) = ST(0); FPOP();	/* 4110ff: fstp st(0) */
L_411101:
	m->esi = M32(m->esp); m->esp += 4;	/* 411101: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 411102: pop ecx */
	m->esp += 4 + 0; return;	/* 411103: ret  */
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
