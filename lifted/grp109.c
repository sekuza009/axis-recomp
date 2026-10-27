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

static void lift_4230a0(X86 *m);
static void lift_4081f0(X86 *m);
static void lift_4378e0(X86 *m);
static void lift_436800(X86 *m);
static void lift_44f410(X86 *m);
static void lift_43ed20(X86 *m);
static void lift_40d390(X86 *m);
static void lift_422b30(X86 *m);

/* setup_drawTab (0x422b30), lifted by tools/lift.py */
static void lift_422b30(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 422b30: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 422b35: test eax, eax */
	if (!m->zf) goto L_422b68;	/* 422b37: jne 0x422b68 */
	m->eax = M32((DWORD)(0x4ddac8u));	/* 422b39: mov eax, dword ptr [0x4ddac8] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422b3e: cmp eax, 2 */
	if (!m->zf && m->sf == m->of) goto L_422b5c;	/* 422b41: jg 0x422b5c */
	if (m->zf) goto L_422b57;	/* 422b43: je 0x422b57 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 422b45: sub eax, 0 */
	if (m->zf) goto L_422b52;	/* 422b48: je 0x422b52 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 422b4a: dec eax */
	if (!m->zf) goto L_422b68;	/* 422b4b: jne 0x422b68 */
	native_call(m, 0x422480u); return;	/* 422b4d: jmp 0x422480 */
L_422b52:
	native_call(m, 0x4221d0u); return;	/* 422b52: jmp 0x4221d0 */
L_422b57:
	native_call(m, 0x422830u); return;	/* 422b57: jmp 0x422830 */
L_422b5c:
	{ DWORD a_ = m->eax, b_ = 0x29au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 422b5c: cmp eax, 0x29a */
	if (!m->zf) goto L_422b68;	/* 422b61: jne 0x422b68 */
	native_call(m, 0x4220c0u); return;	/* 422b63: jmp 0x4220c0 */
L_422b68:
	m->esp += 4 + 0; return;	/* 422b68: ret  */
}

/* setup_processTabKeys (0x4230a0), lifted by tools/lift.py */
static void lift_4230a0(X86 *m)
{
	m->eax = M32((DWORD)(0x90d1c4u));	/* 4230a0: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4230a5: test eax, eax */
	if (!m->zf) goto L_4230d8;	/* 4230a7: jne 0x4230d8 */
	m->eax = M32((DWORD)(0x4ddac8u));	/* 4230a9: mov eax, dword ptr [0x4ddac8] */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4230ae: cmp eax, 2 */
	if (!m->zf && m->sf == m->of) goto L_4230cc;	/* 4230b1: jg 0x4230cc */
	if (m->zf) goto L_4230c7;	/* 4230b3: je 0x4230c7 */
	{ DWORD a_ = m->eax, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4230b5: sub eax, 0 */
	if (m->zf) goto L_4230c2;	/* 4230b8: je 0x4230c2 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 4230ba: dec eax */
	if (!m->zf) goto L_4230d8;	/* 4230bb: jne 0x4230d8 */
	native_call(m, 0x422d20u); return;	/* 4230bd: jmp 0x422d20 */
L_4230c2:
	native_call(m, 0x422c60u); return;	/* 4230c2: jmp 0x422c60 */
L_4230c7:
	native_call(m, 0x422e10u); return;	/* 4230c7: jmp 0x422e10 */
L_4230cc:
	{ DWORD a_ = m->eax, b_ = 0x29au & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4230cc: cmp eax, 0x29a */
	if (!m->zf) goto L_4230d8;	/* 4230d1: jne 0x4230d8 */
	native_call(m, 0x422b70u); return;	/* 4230d3: jmp 0x422b70 */
L_4230d8:
	m->esp += 4 + 0; return;	/* 4230d8: ret  */
}

/* lobby_processKeys (0x4081f0), lifted by tools/lift.py */
static void lift_4081f0(X86 *m)
{
	m->eax = M32((DWORD)(0x4db51cu));	/* 4081f0: mov eax, dword ptr [0x4db51c] */
	{ DWORD a_ = m->eax, b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4081f5: cmp eax, 5 */
	if (!m->cf && !m->zf) goto L_40824d;	/* 4081f8: ja 0x40824d */
	switch (m->eax) { case 0: goto L_408206; case 1: goto L_40820b; case 2: goto L_40821e; case 3: goto L_40824d; case 4: goto L_40824d; case 5: goto L_408201; default: abort(); }	/* 4081fa: jmp dword ptr [eax*4 + 0x408250] */
L_408201:
	native_call(m, 0x407750u); return;	/* 408201: jmp 0x407750 */
L_408206:
	native_call(m, 0x407840u); return;	/* 408206: jmp 0x407840 */
L_40820b:
	m->eax = M32((DWORD)(0x907b2cu));	/* 40820b: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408210: test eax, eax */
	if (m->zf) goto L_408219;	/* 408212: je 0x408219 */
	native_call(m, 0x407970u); return;	/* 408214: jmp 0x407970 */
L_408219:
	native_call(m, 0x4079c0u); return;	/* 408219: jmp 0x4079c0 */
L_40821e:
	m->eax = M32((DWORD)(0x907b2cu));	/* 40821e: mov eax, dword ptr [0x907b2c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408223: test eax, eax */
	if (m->zf) goto L_40822c;	/* 408225: je 0x40822c */
	native_call(m, 0x4080c0u); return;	/* 408227: jmp 0x4080c0 */
L_40822c:
	m->eax = M32((DWORD)(0x4db508u));	/* 40822c: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 408231: test eax, eax */
	if (m->zf) goto L_40823a;	/* 408233: je 0x40823a */
	native_call(m, 0x403870u); return;	/* 408235: jmp 0x403870 */
L_40823a:
	m->eax = M32((DWORD)(0x4db55cu));	/* 40823a: mov eax, dword ptr [0x4db55c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40823f: test eax, eax */
	if (m->zf) goto L_408248;	/* 408241: je 0x408248 */
	native_call(m, 0x408110u); return;	/* 408243: jmp 0x408110 */
L_408248:
	native_call(m, 0x407e40u); return;	/* 408248: jmp 0x407e40 */
L_40824d:
	m->esp += 4 + 0; return;	/* 40824d: ret  */
}

/* menu_4378e0 (0x4378e0), lifted by tools/lift.py */
static void lift_4378e0(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd834u));	/* 4378e0: mov eax, dword ptr [0x9dd834] */
	{ DWORD a_ = m->eax, b_ = 0x63u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4378e5: cmp eax, 0x63 */
	if (!m->cf && !m->zf) goto L_43797c;	/* 4378e8: ja 0x43797c */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4378ee: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x4379a4u))) & 0xff) << 0);	/* 4378f0: mov cl, byte ptr [eax + 0x4379a4] */
	switch (m->ecx) { case 0: goto L_437936; case 1: goto L_437944; case 2: goto L_437952; case 3: goto L_43796e; case 4: goto L_4378fd; case 5: goto L_437910; case 6: goto L_437915; case 7: goto L_437928; case 8: goto L_43797c; default: abort(); }	/* 4378f6: jmp dword ptr [ecx*4 + 0x437980] */
L_4378fd:
	{ DWORD a_ = M32((DWORD)(0x9dd850u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4378fd: cmp dword ptr [0x9dd850], 1 */
	if (!m->zf) goto L_43790b;	/* 437904: jne 0x43790b */
	native_call(m, 0x436940u); return;	/* 437906: jmp 0x436940 */
L_43790b:
	native_call(m, 0x436990u); return;	/* 43790b: jmp 0x436990 */
L_437910:
	native_call(m, 0x436e10u); return;	/* 437910: jmp 0x436e10 */
L_437915:
	{ DWORD a_ = M32((DWORD)(0x9dd850u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 437915: cmp dword ptr [0x9dd850], 1 */
	if (!m->zf) goto L_437923;	/* 43791c: jne 0x437923 */
	native_call(m, 0x436940u); return;	/* 43791e: jmp 0x436940 */
L_437923:
	native_call(m, 0x4370e0u); return;	/* 437923: jmp 0x4370e0 */
L_437928:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 437928: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43792d: test eax, eax */
	if (!m->zf) goto L_43797c;	/* 43792f: jne 0x43797c */
	native_call(m, 0x437140u); return;	/* 437931: jmp 0x437140 */
L_437936:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 437936: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43793b: test eax, eax */
	if (!m->zf) goto L_43797c;	/* 43793d: jne 0x43797c */
	native_call(m, 0x437240u); return;	/* 43793f: jmp 0x437240 */
L_437944:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 437944: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437949: test eax, eax */
	if (!m->zf) goto L_43797c;	/* 43794b: jne 0x43797c */
	native_call(m, 0x4372f0u); return;	/* 43794d: jmp 0x4372f0 */
L_437952:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 437952: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437957: test eax, eax */
	if (!m->zf) goto L_43797c;	/* 437959: jne 0x43797c */
	m->eax = M32((DWORD)(0x4db508u));	/* 43795b: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437960: test eax, eax */
	if (m->zf) goto L_437969;	/* 437962: je 0x437969 */
	native_call(m, 0x403870u); return;	/* 437964: jmp 0x403870 */
L_437969:
	native_call(m, 0x437630u); return;	/* 437969: jmp 0x437630 */
L_43796e:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 43796e: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 437973: test eax, eax */
	if (!m->zf) goto L_43797c;	/* 437975: jne 0x43797c */
	native_call(m, 0x437810u); return;	/* 437977: jmp 0x437810 */
L_43797c:
	m->esp += 4 + 0; return;	/* 43797c: ret  */
}

/* room_processKeys (0x436800), lifted by tools/lift.py */
static void lift_436800(X86 *m)
{
	m->eax = M32((DWORD)(0x9dd834u));	/* 436800: mov eax, dword ptr [0x9dd834] */
	{ DWORD a_ = m->eax, b_ = 0x63u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 436805: cmp eax, 0x63 */
	if (!m->cf && !m->zf) goto L_4368aa;	/* 436808: ja 0x4368aa */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 43680e: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0x4368d0u))) & 0xff) << 0);	/* 436810: mov cl, byte ptr [eax + 0x4368d0] */
	switch (m->ecx) { case 0: goto L_436856; case 1: goto L_436864; case 2: goto L_436880; case 3: goto L_43689c; case 4: goto L_43681d; case 5: goto L_436830; case 6: goto L_436835; case 7: goto L_436848; case 8: goto L_4368aa; default: abort(); }	/* 436816: jmp dword ptr [ecx*4 + 0x4368ac] */
L_43681d:
	m->eax = M32((DWORD)(0x9dd850u));	/* 43681d: mov eax, dword ptr [0x9dd850] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436822: test eax, eax */
	if (m->zf) goto L_43682b;	/* 436824: je 0x43682b */
	native_call(m, 0x435ab0u); return;	/* 436826: jmp 0x435ab0 */
L_43682b:
	native_call(m, 0x435b00u); return;	/* 43682b: jmp 0x435b00 */
L_436830:
	native_call(m, 0x435c20u); return;	/* 436830: jmp 0x435c20 */
L_436835:
	m->eax = M32((DWORD)(0x9dd850u));	/* 436835: mov eax, dword ptr [0x9dd850] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43683a: test eax, eax */
	if (m->zf) goto L_436843;	/* 43683c: je 0x436843 */
	native_call(m, 0x435ab0u); return;	/* 43683e: jmp 0x435ab0 */
L_436843:
	native_call(m, 0x435ce0u); return;	/* 436843: jmp 0x435ce0 */
L_436848:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 436848: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43684d: test eax, eax */
	if (!m->zf) goto L_4368aa;	/* 43684f: jne 0x4368aa */
	native_call(m, 0x435d30u); return;	/* 436851: jmp 0x435d30 */
L_436856:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 436856: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43685b: test eax, eax */
	if (!m->zf) goto L_4368aa;	/* 43685d: jne 0x4368aa */
	native_call(m, 0x435e70u); return;	/* 43685f: jmp 0x435e70 */
L_436864:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 436864: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436869: test eax, eax */
	if (!m->zf) goto L_4368aa;	/* 43686b: jne 0x4368aa */
	m->eax = M32((DWORD)(0x4db8b4u));	/* 43686d: mov eax, dword ptr [0x4db8b4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436872: test eax, eax */
	if (m->zf) goto L_43687b;	/* 436874: je 0x43687b */
	native_call(m, 0x435f40u); return;	/* 436876: jmp 0x435f40 */
L_43687b:
	native_call(m, 0x435fc0u); return;	/* 43687b: jmp 0x435fc0 */
L_436880:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 436880: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 436885: test eax, eax */
	if (!m->zf) goto L_4368aa;	/* 436887: jne 0x4368aa */
	m->eax = M32((DWORD)(0x4db508u));	/* 436889: mov eax, dword ptr [0x4db508] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43688e: test eax, eax */
	if (m->zf) goto L_436897;	/* 436890: je 0x436897 */
	native_call(m, 0x4036c0u); return;	/* 436892: jmp 0x4036c0 */
L_436897:
	native_call(m, 0x436400u); return;	/* 436897: jmp 0x436400 */
L_43689c:
	m->eax = M32((DWORD)(0x9dd7d8u));	/* 43689c: mov eax, dword ptr [0x9dd7d8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4368a1: test eax, eax */
	if (!m->zf) goto L_4368aa;	/* 4368a3: jne 0x4368aa */
	native_call(m, 0x436620u); return;	/* 4368a5: jmp 0x436620 */
L_4368aa:
	m->esp += 4 + 0; return;	/* 4368aa: ret  */
}

/* profile_44f410 (0x44f410), lifted by tools/lift.py */
static void lift_44f410(X86 *m)
{
	m->eax = M32((DWORD)(0x9f900cu));	/* 44f410: mov eax, dword ptr [0x9f900c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f415: test eax, eax */
	if (m->zf) goto L_44f44c;	/* 44f417: je 0x44f44c */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4b071cu)));	/* 44f419: fld dword ptr [0x4b071c] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x9f8f18u));	/* 44f41f: fadd dword ptr [0x9f8f18] */
	MF((DWORD)(0x9f8f18u)) = (float)ST(0);	/* 44f425: fst dword ptr [0x9f8f18] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a944cu)); FPOP();	/* 44f42b: fcomp dword ptr [0x4a944c] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 44f431: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 44f433: test ah, 0x41 */
	if (!m->zf) goto L_44f44c;	/* 44f436: jne 0x44f44c */
	M32((DWORD)(0x9f900cu)) = 0x0u;	/* 44f438: mov dword ptr [0x9f900c], 0 */
	M32((DWORD)(0x9f8f18u)) = 0x0u;	/* 44f442: mov dword ptr [0x9f8f18], 0 */
L_44f44c:
	m->eax = M32((DWORD)(0x90d1c4u));	/* 44f44c: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f451: test eax, eax */
	if (m->zf) goto L_44f48e;	/* 44f453: je 0x44f48e */
	m->eax = M32((DWORD)(0x9f8ea4u));	/* 44f455: mov eax, dword ptr [0x9f8ea4] */
	m->ecx = M32((DWORD)(0x9f8ea0u));	/* 44f45a: mov ecx, dword ptr [0x9f8ea0] */
	m->edx = M32((DWORD)(0x9f8e4cu));	/* 44f460: mov edx, dword ptr [0x9f8e4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f466: push eax */
	m->eax = M32((DWORD)(0x9f8e48u));	/* 44f467: mov eax, dword ptr [0x9f8e48] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f46c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 44f46d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 44f46e: push eax */
	m->esp -= 4; M32(m->esp) = 0x44f474u; native_call(m, 0x428c30u);	/* 44f46f: call 0x428c30 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 44f474: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 44f479: add esp, 0x10 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f47c: test eax, eax */
	if (!m->zf) goto L_44f4ab;	/* 44f47e: jne 0x44f4ab */
	m->eax = M32((DWORD)(0x9f8d70u));	/* 44f480: mov eax, dword ptr [0x9f8d70] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f485: test eax, eax */
	if (m->zf) goto L_44f4ab;	/* 44f487: je 0x44f4ab */
	native_call(m, 0x44b600u); return;	/* 44f489: jmp 0x44b600 */
L_44f48e:
	m->eax = M32((DWORD)(0x9f8d68u));	/* 44f48e: mov eax, dword ptr [0x9f8d68] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 44f493: test eax, eax */
	if (m->zf) goto L_44f49c;	/* 44f495: je 0x44f49c */
	m->esp -= 4; M32(m->esp) = 0x44f49cu; native_call(m, 0x44bd20u);	/* 44f497: call 0x44bd20 */
L_44f49c:
	M32((DWORD)(0x9f8f10u)) = 0x1u;	/* 44f49c: mov dword ptr [0x9f8f10], 1 */
	native_call(m, 0x44d720u); return;	/* 44f4a6: jmp 0x44d720 */
L_44f4ab:
	m->esp += 4 + 0; return;	/* 44f4ab: ret  */
}

/* room_43ed20 (0x43ed20), lifted by tools/lift.py */
static void lift_43ed20(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x43ed25u; native_call(m, 0x4388e0u);	/* 43ed20: call 0x4388e0 */
	m->eax = M32((DWORD)(0x9dce48u));	/* 43ed25: mov eax, dword ptr [0x9dce48] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ed2a: cmp eax, 1 */
	if (m->zf) goto L_43ed67;	/* 43ed2d: je 0x43ed67 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ed2f: test eax, eax */
	if (m->zf) goto L_43ed67;	/* 43ed31: je 0x43ed67 */
	{ DWORD a_ = M32((DWORD)(0x9dd834u)), b_ = 0x63u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43ed33: cmp dword ptr [0x9dd834], 0x63 */
	if (m->zf) goto L_43ed67;	/* 43ed3a: je 0x43ed67 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 43ed3c: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43ed41: test eax, eax */
	if (m->zf) goto L_43ed68;	/* 43ed43: je 0x43ed68 */
	m->eax = M32((DWORD)(0x9dd1c4u));	/* 43ed45: mov eax, dword ptr [0x9dd1c4] */
	m->ecx = M32((DWORD)(0x9dd1c0u));	/* 43ed4a: mov ecx, dword ptr [0x9dd1c0] */
	m->edx = M32((DWORD)(0x9dd1bcu));	/* 43ed50: mov edx, dword ptr [0x9dd1bc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ed56: push eax */
	m->eax = M32((DWORD)(0x9dd1b8u));	/* 43ed57: mov eax, dword ptr [0x9dd1b8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ed5c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43ed5d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43ed5e: push eax */
	m->esp -= 4; M32(m->esp) = 0x43ed64u; native_call(m, 0x428c30u);	/* 43ed5f: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43ed64: add esp, 0x10 */
L_43ed67:
	m->esp += 4 + 0; return;	/* 43ed67: ret  */
L_43ed68:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b51u))) & 0xff) << 0);	/* 43ed68: mov al, byte ptr [0x5b1b51] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43ed6d: test al, al */
	if (m->sf != m->of) goto L_43ed75;	/* 43ed6f: jl 0x43ed75 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43ed71: cmp al, 0x10 */
	if (m->zf || m->sf != m->of) goto L_43ed7c;	/* 43ed73: jle 0x43ed7c */
L_43ed75:
	M8((DWORD)(0x5b1b51u)) = (BYTE)(0x8u);	/* 43ed75: mov byte ptr [0x5b1b51], 8 */
L_43ed7c:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b54u))) & 0xff) << 0);	/* 43ed7c: mov cl, byte ptr [0x5b1b54] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0x1eu) & 0xff) << 0);	/* 43ed82: mov al, 0x1e */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), b_ = 0x32u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43ed84: cmp cl, 0x32 */
	if (m->cf || m->zf) goto L_43ed8e;	/* 43ed87: jbe 0x43ed8e */
	M8((DWORD)(0x5b1b54u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 43ed89: mov byte ptr [0x5b1b54], al */
L_43ed8e:
	{ DWORD a_ = M8((DWORD)(0x5b1b55u)), b_ = 0x3cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43ed8e: cmp byte ptr [0x5b1b55], 0x3c */
	if (m->cf || m->zf) goto L_43ed9c;	/* 43ed95: jbe 0x43ed9c */
	M8((DWORD)(0x5b1b55u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 43ed97: mov byte ptr [0x5b1b55], al */
L_43ed9c:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x5b1b53u))) & 0xff) << 0);	/* 43ed9c: mov al, byte ptr [0x5b1b53] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 43eda1: test al, al */
	if (m->sf != m->of) goto L_43eda9;	/* 43eda3: jl 0x43eda9 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xbu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 43eda5: cmp al, 0xb */
	if (m->zf || m->sf != m->of) goto L_43edb0;	/* 43eda7: jle 0x43edb0 */
L_43eda9:
	M8((DWORD)(0x5b1b53u)) = (BYTE)(0x0u);	/* 43eda9: mov byte ptr [0x5b1b53], 0 */
L_43edb0:
	m->esp -= 4; M32(m->esp) = 0x43edb5u; native_call(m, 0x43bfe0u);	/* 43edb0: call 0x43bfe0 */
	{ DWORD a_ = M32((DWORD)(0x4db508u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 43edb5: cmp dword ptr [0x4db508], 1 */
	if (!m->zf) goto L_43edc3;	/* 43edbc: jne 0x43edc3 */
	m->esp -= 4; M32(m->esp) = 0x43edc3u; native_call(m, 0x4038e0u);	/* 43edbe: call 0x4038e0 */
L_43edc3:
	m->eax = M32((DWORD)(0x4dba88u));	/* 43edc3: mov eax, dword ptr [0x4dba88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 43edc8: test eax, eax */
	if (m->zf) goto L_43ed67;	/* 43edca: je 0x43ed67 */
	native_call(m, 0x4355b0u); return;	/* 43edcc: jmp 0x4355b0 */
}

/* lobbyCreate_draw (0x40d390), lifted by tools/lift.py */
static void lift_40d390(X86 *m)
{
	m->esp -= 4; M32(m->esp) = 0x40d395u; native_call(m, 0x4091b0u);	/* 40d390: call 0x4091b0 */
	m->eax = M32((DWORD)(0x4dbb3cu));	/* 40d395: mov eax, dword ptr [0x4dbb3c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d39a: cmp eax, 1 */
	if (m->zf) goto L_40d3d7;	/* 40d39d: je 0x40d3d7 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d39f: test eax, eax */
	if (m->zf) goto L_40d3d7;	/* 40d3a1: je 0x40d3d7 */
	{ DWORD a_ = M32((DWORD)(0x4db51cu)), b_ = 0x5u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d3a3: cmp dword ptr [0x4db51c], 5 */
	if (m->zf) goto L_40d3d7;	/* 40d3aa: je 0x40d3d7 */
	m->eax = M32((DWORD)(0x90d1c4u));	/* 40d3ac: mov eax, dword ptr [0x90d1c4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d3b1: test eax, eax */
	if (m->zf) goto L_40d3d8;	/* 40d3b3: je 0x40d3d8 */
	m->eax = M32((DWORD)(0x4dbb0cu));	/* 40d3b5: mov eax, dword ptr [0x4dbb0c] */
	m->ecx = M32((DWORD)(0x4dbb08u));	/* 40d3ba: mov ecx, dword ptr [0x4dbb08] */
	m->edx = M32((DWORD)(0x4dbb04u));	/* 40d3c0: mov edx, dword ptr [0x4dbb04] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d3c6: push eax */
	m->eax = M32((DWORD)(0x4dbb00u));	/* 40d3c7: mov eax, dword ptr [0x4dbb00] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d3cc: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40d3cd: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40d3ce: push eax */
	m->esp -= 4; M32(m->esp) = 0x40d3d4u; native_call(m, 0x428c30u);	/* 40d3cf: call 0x428c30 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40d3d4: add esp, 0x10 */
L_40d3d7:
	m->esp += 4 + 0; return;	/* 40d3d7: ret  */
L_40d3d8:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded41u))) & 0xff) << 0);	/* 40d3d8: mov al, byte ptr [0x4ded41] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d3dd: test al, al */
	if (m->sf != m->of) goto L_40d3e5;	/* 40d3df: jl 0x40d3e5 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x10u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d3e1: cmp al, 0x10 */
	if (m->zf || m->sf != m->of) goto L_40d3ec;	/* 40d3e3: jle 0x40d3ec */
L_40d3e5:
	M8((DWORD)(0x4ded41u)) = (BYTE)(0x8u);	/* 40d3e5: mov byte ptr [0x4ded41], 8 */
L_40d3ec:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded44u))) & 0xff) << 0);	/* 40d3ec: mov dl, byte ptr [0x4ded44] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0xfau) & 0xff) << 0);	/* 40d3f2: mov al, 0xfa */
	{ DWORD a_ = ((m->edx >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d3f4: cmp dl, al */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((0x1eu) & 0xff) << 0);	/* 40d3f6: mov cl, 0x1e */
	if (m->cf || m->zf) goto L_40d400;	/* 40d3f8: jbe 0x40d400 */
	M8((DWORD)(0x4ded44u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40d3fa: mov byte ptr [0x4ded44], cl */
L_40d400:
	{ DWORD a_ = M8((DWORD)(0x4ded45u)), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d400: cmp byte ptr [0x4ded45], al */
	if (m->cf || m->zf) goto L_40d40e;	/* 40d406: jbe 0x40d40e */
	M8((DWORD)(0x4ded45u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 40d408: mov byte ptr [0x4ded45], cl */
L_40d40e:
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(0x4ded43u))) & 0xff) << 0);	/* 40d40e: mov al, byte ptr [0x4ded43] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40d413: test al, al */
	if (m->sf != m->of) goto L_40d41b;	/* 40d415: jl 0x40d41b */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xeu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40d417: cmp al, 0xe */
	if (m->zf || m->sf != m->of) goto L_40d422;	/* 40d419: jle 0x40d422 */
L_40d41b:
	M8((DWORD)(0x4ded43u)) = (BYTE)(0x0u);	/* 40d41b: mov byte ptr [0x4ded43], 0 */
L_40d422:
	m->esp -= 4; M32(m->esp) = 0x40d427u; native_call(m, 0x40b750u);	/* 40d422: call 0x40b750 */
	{ DWORD a_ = M32((DWORD)(0x4db508u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40d427: cmp dword ptr [0x4db508], 1 */
	if (!m->zf) goto L_40d435;	/* 40d42e: jne 0x40d435 */
	m->esp -= 4; M32(m->esp) = 0x40d435u; native_call(m, 0x4038e0u);	/* 40d430: call 0x4038e0 */
L_40d435:
	m->eax = M32((DWORD)(0x4dba88u));	/* 40d435: mov eax, dword ptr [0x4dba88] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40d43a: test eax, eax */
	if (m->zf) goto L_40d3d7;	/* 40d43c: je 0x40d3d7 */
	native_call(m, 0x405b80u); return;	/* 40d43e: jmp 0x405b80 */
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
