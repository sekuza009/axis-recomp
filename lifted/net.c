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

static void lift_452170(X86 *m);
static void lift_454220(X86 *m);
static void lift_4520e0(X86 *m);
static void lift_4547d0(X86 *m);
static void lift_48e990(X86 *m);
static void lift_48ead0(X86 *m);
static void lift_48e0f0(X86 *m);
static void lift_48e680(X86 *m);
static void lift_48e2c0(X86 *m);
static void lift_4547c0(X86 *m);

/* inet_addr_wrap_4547c0 (0x4547c0), lifted by tools/lift.py */
static void lift_4547c0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4547c0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4547c4: push eax */
	m->esp -= 4; M32(m->esp) = 0x4547cau; native_call(m, 0x4a82b0u);	/* 4547c5: call 0x4a82b0 */
	m->esp += 4 + 0; return;	/* 4547ca: ret  */
}

/* net_asyncSelect (0x452170), lifted by tools/lift.py */
static void lift_452170(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 452170: mov eax, dword ptr [esp + 8] */
	{ DWORD a_ = m->eax, b_ = 0x64u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 452174: sub eax, 0x64 */
	if (m->zf) goto L_45219f;	/* 452177: je 0x45219f */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 452179: dec eax */
	if (!m->zf) goto L_4521b6;	/* 45217a: jne 0x4521b6 */
	m->eax = M32((DWORD)(0xa05630u));	/* 45217c: mov eax, dword ptr [0xa05630] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 452181: test eax, eax */
	if (m->zf) goto L_4521b6;	/* 452183: je 0x4521b6 */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 452185: mov ecx, dword ptr [esp + 4] */
	{ DWORD v_ = 0x21u; m->esp -= 4; M32(m->esp) = v_; }	/* 452189: push 0x21 */
	{ DWORD v_ = 0x40cu; m->esp -= 4; M32(m->esp) = v_; }	/* 45218b: push 0x40c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452190: push ecx */
L_452191:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452191: push eax */
	m->esp -= 4; M32(m->esp) = 0x452197u; native_call(m, 0x4a82c8u);	/* 452192: call 0x4a82c8 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 452197: cmp eax, -1 */
	if (!m->zf) goto L_4521b6;	/* 45219a: jne 0x4521b6 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45219c: xor eax, eax */
	m->esp += 4 + 0; return;	/* 45219e: ret  */
L_45219f:
	m->eax = M32((DWORD)(0xa055f8u));	/* 45219f: mov eax, dword ptr [0xa055f8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4521a4: test eax, eax */
	if (m->zf) goto L_4521b6;	/* 4521a6: je 0x4521b6 */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 4521a8: mov edx, dword ptr [esp + 4] */
	{ DWORD v_ = 0x21u; m->esp -= 4; M32(m->esp) = v_; }	/* 4521ac: push 0x21 */
	{ DWORD v_ = 0x40au; m->esp -= 4; M32(m->esp) = v_; }	/* 4521ae: push 0x40a */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4521b3: push edx */
	goto L_452191;	/* 4521b4: jmp 0x452191 */
L_4521b6:
	m->eax = 0x1u;	/* 4521b6: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 4521bb: ret  */
}

/* net_getLocalAddress (0x454220), lifted by tools/lift.py */
static void lift_454220(X86 *m)
{
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454220: xor eax, eax */
	{ DWORD a_ = m->esp, b_ = 0xccu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454222: sub esp, 0xcc */
	M32((DWORD)(0xa0b43cu)) = m->eax;	/* 454228: mov dword ptr [0xa0b43c], eax */
	m->ecx = (DWORD)(m->esp + 0x0u);	/* 45422d: lea ecx, [esp] */
	M32((DWORD)(0xa0b440u)) = m->eax;	/* 454231: mov dword ptr [0xa0b440], eax */
	{ DWORD v_ = 0xc8u; m->esp -= 4; M32(m->esp) = v_; }	/* 454236: push 0xc8 */
	M32((DWORD)(0xa0b444u)) = m->eax;	/* 45423b: mov dword ptr [0xa0b444], eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454240: push ecx */
	M32((DWORD)(0xa0b448u)) = m->eax;	/* 454241: mov dword ptr [0xa0b448], eax */
	m->esp -= 4; M32(m->esp) = 0x45424bu; native_call(m, 0x4a82e0u);	/* 454246: call 0x4a82e0 */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45424b: cmp eax, -1 */
	if (m->zf) goto L_454291;	/* 45424e: je 0x454291 */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 454250: lea edx, [esp] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 454254: push edx */
	m->esp -= 4; M32(m->esp) = 0x45425au; native_call(m, 0x4a82a4u);	/* 454255: call 0x4a82a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45425a: test eax, eax */
	if (m->zf) goto L_454291;	/* 45425c: je 0x454291 */
	m->eax = M32((DWORD)(m->eax + 0xcu));	/* 45425e: mov eax, dword ptr [eax + 0xc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 454261: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 454262: push edi */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 454263: mov ecx, dword ptr [eax] */
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 454265: mov eax, dword ptr [ecx] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454267: push eax */
	m->esp -= 4; M32(m->esp) = 0x45426du; native_call(m, 0x4a82dau);	/* 454268: call 0x4a82da */
	m->edi = m->eax;	/* 45426d: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45426f: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454272: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 454274: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 454276: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 454278: sub edi, ecx */
	m->edx = m->ecx;	/* 45427a: mov edx, ecx */
	m->esi = m->edi;	/* 45427c: mov esi, edi */
	m->edi = 0xa0b43cu;	/* 45427e: mov edi, 0xa0b43c */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 454283: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 454286: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 454288: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45428a: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 45428d: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = M32(m->esp); m->esp += 4;	/* 45428f: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 454290: pop esi */
L_454291:
	{ DWORD a_ = m->esp, b_ = 0xccu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454291: add esp, 0xcc */
	m->esp += 4 + 0; return;	/* 454297: ret  */
}

/* FUN_004520e0 (0x4520e0), lifted by tools/lift.py */
static void lift_4520e0(X86 *m)
{
	m->eax = M32((DWORD)(0xa055f8u));	/* 4520e0: mov eax, dword ptr [0xa055f8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4520e5: push esi */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4520e6: xor esi, esi */
	{ DWORD a_ = m->eax, b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4520e8: cmp eax, esi */
	if (m->zf) goto L_45211f;	/* 4520ea: je 0x45211f */
	M32((DWORD)(0x9fd94cu)) = 0x1u;	/* 4520ec: mov dword ptr [0x9fd94c], 1 */
	m->esp -= 4; M32(m->esp) = 0x4520fbu; native_call(m, 0x4a8292u);	/* 4520f6: call 0x4a8292 */
	m->eax = M32((DWORD)(0xa055f8u));	/* 4520fb: mov eax, dword ptr [0xa055f8] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 452100: push 1 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452102: push eax */
	m->esp -= 4; M32(m->esp) = 0x452108u; native_call(m, 0x4a828cu);	/* 452103: call 0x4a828c */
	m->ecx = M32((DWORD)(0xa055f8u));	/* 452108: mov ecx, dword ptr [0xa055f8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45210e: push ecx */
	m->esp -= 4; M32(m->esp) = 0x452114u; native_call(m, 0x4a8286u);	/* 45210f: call 0x4a8286 */
	M32((DWORD)(0xa055f8u)) = m->esi;	/* 452114: mov dword ptr [0xa055f8], esi */
	m->esp -= 4; M32(m->esp) = 0x45211fu; native_call(m, 0x4519b0u);	/* 45211a: call 0x4519b0 */
L_45211f:
	{ DWORD a_ = M32((DWORD)(0xa05630u)), b_ = m->esi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 45211f: cmp dword ptr [0xa05630], esi */
	if (m->zf) goto L_45215a;	/* 452125: je 0x45215a */
	M32((DWORD)(0x9fd94cu)) = 0x1u;	/* 452127: mov dword ptr [0x9fd94c], 1 */
	m->esp -= 4; M32(m->esp) = 0x452136u; native_call(m, 0x4a8292u);	/* 452131: call 0x4a8292 */
	m->edx = M32((DWORD)(0xa05630u));	/* 452136: mov edx, dword ptr [0xa05630] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 45213c: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 45213e: push edx */
	m->esp -= 4; M32(m->esp) = 0x452144u; native_call(m, 0x4a828cu);	/* 45213f: call 0x4a828c */
	m->eax = M32((DWORD)(0xa05630u));	/* 452144: mov eax, dword ptr [0xa05630] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452149: push eax */
	m->esp -= 4; M32(m->esp) = 0x45214fu; native_call(m, 0x4a8286u);	/* 45214a: call 0x4a8286 */
	M32((DWORD)(0xa05630u)) = m->esi;	/* 45214f: mov dword ptr [0xa05630], esi */
	m->esp -= 4; M32(m->esp) = 0x45215au; native_call(m, 0x4519b0u);	/* 452155: call 0x4519b0 */
L_45215a:
	M32((DWORD)(0xa0b300u)) = m->esi;	/* 45215a: mov dword ptr [0xa0b300], esi */
	M32((DWORD)(0xa0b380u)) = m->esi;	/* 452160: mov dword ptr [0xa0b380], esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 452166: pop esi */
	m->esp += 4 + 0; return;	/* 452167: ret  */
}

/* net_resolveHost (0x4547d0), lifted by tools/lift.py */
static void lift_4547d0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4547d0: sub esp, 0x190 */
	m->ecx = 0x19u;	/* 4547d6: mov ecx, 0x19 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4547db: xor eax, eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 4547dd: push ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4547de: push edi */
	m->edi = 0xa0d320u;	/* 4547df: mov edi, 0xa0d320 */
	while (m->ecx) { M32(m->edi) = (DWORD)m->eax; m->edi += 4; m->ecx--; }	/* 4547e4: rep stosd dword ptr es:[edi], eax */
	m->eax = (DWORD)(m->esp + 0x8u);	/* 4547e6: lea eax, [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4547ea: push eax */
	{ DWORD v_ = 0x202u; m->esp -= 4; M32(m->esp) = v_; }	/* 4547eb: push 0x202 */
	m->esp -= 4; M32(m->esp) = 0x4547f5u; native_call(m, 0x4a82c2u);	/* 4547f0: call 0x4a82c2 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4547f5: test eax, eax */
	if (m->zf) goto L_454804;	/* 4547f7: je 0x454804 */
	m->edi = M32(m->esp); m->esp += 4;	/* 4547f9: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4547fa: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4547fc: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4547fd: add esp, 0x190 */
	m->esp += 4 + 0; return;	/* 454803: ret  */
L_454804:
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 454804: push 1 */
	{ DWORD v_ = 0x3u; m->esp -= 4; M32(m->esp) = v_; }	/* 454806: push 3 */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 454808: push 2 */
	m->esp -= 4; M32(m->esp) = 0x45480fu; native_call(m, 0x4a82bcu);	/* 45480a: call 0x4a82bc */
	m->ebx = m->eax;	/* 45480f: mov ebx, eax */
	{ DWORD a_ = m->ebx, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 454811: cmp ebx, -1 */
	if (!m->zf) goto L_454821;	/* 454814: jne 0x454821 */
	m->edi = M32(m->esp); m->esp += 4;	/* 454816: pop edi */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 454817: xor eax, eax */
	m->ebx = M32(m->esp); m->esp += 4;	/* 454819: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45481a: add esp, 0x190 */
	m->esp += 4 + 0; return;	/* 454820: ret  */
L_454821:
	m->ecx = M32((DWORD)(m->esp + 0x19cu));	/* 454821: mov ecx, dword ptr [esp + 0x19c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 454828: push ecx */
	m->esp -= 4; M32(m->esp) = 0x45482eu; native_call(m, 0x4a82a4u);	/* 454829: call 0x4a82a4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45482e: test eax, eax */
	if (!m->zf) goto L_45483b;	/* 454830: jne 0x45483b */
	m->edi = M32(m->esp); m->esp += 4;	/* 454832: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 454833: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 454834: add esp, 0x190 */
	m->esp += 4 + 0; return;	/* 45483a: ret  */
L_45483b:
	m->edx = M32((DWORD)(m->eax + 0xcu));	/* 45483b: mov edx, dword ptr [eax + 0xc] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 45483e: push esi */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 45483f: mov eax, dword ptr [edx] */
	m->eax = M32((DWORD)(m->eax + 0x0u));	/* 454841: mov eax, dword ptr [eax] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 454843: push eax */
	m->esp -= 4; M32(m->esp) = 0x454849u; native_call(m, 0x4a82dau);	/* 454844: call 0x4a82da */
	m->edi = m->eax;	/* 454849: mov edi, eax */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 45484b: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 45484e: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 454850: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 454852: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 454854: sub edi, ecx */
	m->edx = m->ecx;	/* 454856: mov edx, ecx */
	m->esi = m->edi;	/* 454858: mov esi, edi */
	m->edi = 0xa0d320u;	/* 45485a: mov edi, 0xa0d320 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45485f: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 454862: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 454864: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 454866: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 454869: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->edi = 0xa0d320u;	/* 45486b: mov edi, 0xa0d320 */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 454870: or ecx, 0xffffffff */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 454873: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 454875: not ecx */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 454877: dec ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 454878: pop esi */
	if (!m->zf) goto L_454884;	/* 454879: jne 0x454884 */
	m->edi = M32(m->esp); m->esp += 4;	/* 45487b: pop edi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 45487c: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45487d: add esp, 0x190 */
	m->esp += 4 + 0; return;	/* 454883: ret  */
L_454884:
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 454884: test ebx, ebx */
	if (m->zf) goto L_454893;	/* 454886: je 0x454893 */
	m->esp -= 4; M32(m->esp) = 0x45488du; native_call(m, 0x4a8292u);	/* 454888: call 0x4a8292 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 45488d: push ebx */
	m->esp -= 4; M32(m->esp) = 0x454893u; native_call(m, 0x4a8286u);	/* 45488e: call 0x4a8286 */
L_454893:
	m->edi = M32(m->esp); m->esp += 4;	/* 454893: pop edi */
	m->eax = 0x1u;	/* 454894: mov eax, 1 */
	m->ebx = M32(m->esp); m->esp += 4;	/* 454899: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x190u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 45489a: add esp, 0x190 */
	m->esp += 4 + 0; return;	/* 4548a0: ret  */
}

/* match_48e990 (0x48e990), lifted by tools/lift.py */
static void lift_48e990(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e990: sub esp, 0x40 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e993: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48e994: push esi */
	m->esi = m->ecx;	/* 48e995: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48e997: push edi */
	m->ecx = M32((DWORD)(m->esp + 0x50u));	/* 48e998: mov ecx, dword ptr [esp + 0x50] */
	m->ebx = 0x1u;	/* 48e99c: mov ebx, 1 */
	M8((DWORD)(m->esp + 0xdu)) = (BYTE)(0xcu);	/* 48e9a1: mov byte ptr [esp + 0xd], 0xc */
	M8((DWORD)(m->esp + 0xeu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e9a6: mov byte ptr [esp + 0xe], cl */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 48e9aa: lea eax, [ecx + ecx*2] */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48e9ad: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48e9b0: sub eax, ecx */
	m->eax = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48e9b2: lea eax, [eax + eax*2] */
	m->edx = (DWORD)(m->ecx + m->eax*8 + 0x0u);	/* 48e9b5: lea edx, [ecx + eax*8] */
	m->eax = M32((DWORD)(m->esi + m->edx*2 + 0x179d1f6u));	/* 48e9b8: mov eax, dword ptr [esi + edx*2 + 0x179d1f6] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e9bf: cmp eax, ebx */
	m->edi = (DWORD)(m->esi + m->edx*2 + 0x0u);	/* 48e9c1: lea edi, [esi + edx*2] */
	if (m->zf) goto L_48e9e1;	/* 48e9c4: je 0x48e9e1 */
	{ DWORD a_ = M32((DWORD)(m->edi + 0x179d1fau)), b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e9c6: cmp dword ptr [edi + 0x179d1fa], ebx */
	if (m->zf) goto L_48e9e1;	/* 48e9cc: je 0x48e9e1 */
	M16((DWORD)(m->esp + 0xfu)) = (WORD)(0xffffu);	/* 48e9ce: mov word ptr [esp + 0xf], 0xffff */
	M32((DWORD)(m->edi + 0x179d1feu)) = 0x180u;	/* 48e9d5: mov dword ptr [edi + 0x179d1fe], 0x180 */
	goto L_48ea2d;	/* 48e9df: jmp 0x48ea2d */
L_48e9e1:
	m->eax = (m->eax & 0xffff0000u) | ((M16((DWORD)(m->edi + 0x179d1feu))) & 0xffff);	/* 48e9e1: mov ax, word ptr [edi + 0x179d1fe] */
	m->edx = M32((DWORD)(m->edi + 0x179d1feu));	/* 48e9e8: mov edx, dword ptr [edi + 0x179d1fe] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48e9ee: push ebp */
	M16((DWORD)(m->esp + 0x13u)) = (WORD)((m->eax & 0xffff));	/* 48e9ef: mov word ptr [esp + 0x13], ax */
	m->ecx = (DWORD)(m->esp + 0x16u);	/* 48e9f4: lea ecx, [esp + 0x16] */
	m->eax = (DWORD)(m->edi + m->edx*4 + 0x179cbf4u);	/* 48e9f8: lea eax, [edi + edx*4 + 0x179cbf4] */
	m->ebp = 0x10u;	/* 48e9ff: mov ebp, 0x10 */
L_48ea04:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xfffffffeu))) & 0xff) << 0);	/* 48ea04: mov bl, byte ptr [eax - 2] */
	{ DWORD a_ = m->eax, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48ea07: add eax, 4 */
	M8((DWORD)(m->ecx + 0xffffffffu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 48ea0a: mov byte ptr [ecx - 1], bl */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xfffffffbu))) & 0xff) << 0);	/* 48ea0d: mov bl, byte ptr [eax - 5] */
	M8((DWORD)(m->ecx + 0x0u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 48ea10: mov byte ptr [ecx], bl */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->eax + 0xfffffffcu))) & 0xff) << 0);	/* 48ea12: mov bl, byte ptr [eax - 4] */
	M8((DWORD)(m->ecx + 0x1u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 48ea15: mov byte ptr [ecx + 1], bl */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48ea18: add ecx, 3 */
	{ DWORD a_ = m->ebp, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebp = r_; }	/* 48ea1b: dec ebp */
	if (!m->zf) goto L_48ea04;	/* 48ea1c: jne 0x48ea04 */
	{ DWORD a_ = m->edx, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48ea1e: add edx, 0x10 */
	m->ebx = 0x1u;	/* 48ea21: mov ebx, 1 */
	M32((DWORD)(m->edi + 0x179d1feu)) = m->edx;	/* 48ea26: mov dword ptr [edi + 0x179d1fe], edx */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48ea2c: pop ebp */
L_48ea2d:
	m->ecx = (DWORD)(m->esp + 0xcu);	/* 48ea2d: lea ecx, [esp + 0xc] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea31: push ecx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea32: push 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48ea39u; native_call(m, 0x4a8360u);	/* 48ea34: call 0x4a8360 */
	m->ecx = M32((DWORD)(m->esi + 0x2340c78u));	/* 48ea39: mov ecx, dword ptr [esi + 0x2340c78] */
	m->eax = M32((DWORD)(m->esi + 0x2340d1du));	/* 48ea3f: mov eax, dword ptr [esi + 0x2340d1d] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ea45: add esp, 8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48ea48: inc ecx */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48ea49: cmp eax, ebx */
	M32((DWORD)(m->esi + 0x2340c78u)) = m->ecx;	/* 48ea4b: mov dword ptr [esi + 0x2340c78], ecx */
	if (!m->zf) goto L_48eab8;	/* 48ea51: jne 0x48eab8 */
	m->edx = M32((DWORD)(m->esi + 0x2340d08u));	/* 48ea53: mov edx, dword ptr [esi + 0x2340d08] */
	m->eax = (DWORD)(m->esi + 0x2340d29u);	/* 48ea59: lea eax, [esi + 0x2340d29] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea5f: push edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea60: push ebx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea61: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea63: push eax */
	M32((DWORD)(m->esp + 0x60u)) = 0x40u;	/* 48ea64: mov dword ptr [esp + 0x60], 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48ea71u; native_call(m, 0x46cc30u);	/* 48ea6c: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->esi + 0x2340d08u));	/* 48ea71: mov ecx, dword ptr [esi + 0x2340d08] */
	m->edx = (DWORD)(m->esi + 0x234240du);	/* 48ea77: lea edx, [esi + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea7d: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea7e: push ebx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea7f: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea81: push edx */
	m->esp -= 4; M32(m->esp) = 0x48ea87u; native_call(m, 0x46cc30u);	/* 48ea82: call 0x46cc30 */
	m->eax = M32((DWORD)(m->esi + 0x2340d08u));	/* 48ea87: mov eax, dword ptr [esi + 0x2340d08] */
	m->ecx = (DWORD)(m->esp + 0x70u);	/* 48ea8d: lea ecx, [esp + 0x70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea91: push eax */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea92: push ebx */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea93: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ea95: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48ea9bu; native_call(m, 0x46cc30u);	/* 48ea96: call 0x46cc30 */
	m->edx = M32((DWORD)(m->esi + 0x2340d08u));	/* 48ea9b: mov edx, dword ptr [esi + 0x2340d08] */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 48eaa1: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48eaa8: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48eaa9: push eax */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 48eaaa: lea ecx, [esp + 0x44] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48eaae: push ebx */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48eaaf: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48eab5u; native_call(m, 0x46cc30u);	/* 48eab0: call 0x46cc30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48eab5: add esp, 0x40 */
L_48eab8:
	m->edi = M32(m->esp); m->esp += 4;	/* 48eab8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48eab9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48eaba: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48eabb: add esp, 0x40 */
	m->esp += 4 + 4; return;	/* 48eabe: ret 4 */
}

/* net_sendState_48ead0 (0x48ead0), lifted by tools/lift.py */
static void lift_48ead0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ead0: sub esp, 0x44 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ead3: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48ead4: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ead5: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48ead6: push edi */
	m->edi = m->ecx;	/* 48ead7: mov edi, ecx */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 48ead9: xor esi, esi */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0xeu);	/* 48eadb: mov byte ptr [esp + 0x15], 0xe */
	m->eax = M32((DWORD)(m->edi + 0x22f0400u));	/* 48eae0: mov eax, dword ptr [edi + 0x22f0400] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48eae6: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48eb7e;	/* 48eae8: jle 0x48eb7e */
	m->ebp = (DWORD)(m->edi + 0x22ee4e4u);	/* 48eaee: lea ebp, [edi + 0x22ee4e4] */
L_48eaf4:
	{ DWORD a_ = m->esi, b_ = 0x7cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48eaf4: cmp esi, 0x7c */
	if (m->sf == m->of) goto L_48eb7e;	/* 48eaf7: jge 0x48eb7e */
	m->ebx = m->esi;	/* 48eafd: mov ebx, esi */
	{ DWORD a_ = m->ebx, b_ = 0x80000001u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48eaff: and ebx, 0x80000001 */
	if (!m->sf) goto L_48eb0c;	/* 48eb05: jns 0x48eb0c */
	{ DWORD a_ = m->ebx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ebx = r_; }	/* 48eb07: dec ebx */
	{ DWORD a_ = m->ebx, b_ = 0xfffffffeu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 48eb08: or ebx, 0xfffffffe */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 48eb0b: inc ebx */
L_48eb0c:
	if (!m->zf) goto L_48eb1a;	/* 48eb0c: jne 0x48eb1a */
	m->eax = m->esi;	/* 48eb0e: mov eax, esi */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48eb10: cdq  */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48eb11: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48eb13: sar eax, 1 */
	M8((DWORD)(m->esp + m->eax*1 + 0x16u)) = (BYTE)(0x0u);	/* 48eb15: mov byte ptr [esp + eax + 0x16], 0 */
L_48eb1a:
	m->eax = M32((DWORD)(m->ebp + 0xffffffdcu));	/* 48eb1a: mov eax, dword ptr [ebp - 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48eb1d: test eax, eax */
	if (m->sf != m->of) goto L_48eb6c;	/* 48eb1f: jl 0x48eb6c */
	{ DWORD a_ = M32((DWORD)(m->ebp + 0xfffffffcu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48eb21: cmp dword ptr [ebp - 4], 1 */
	if (!m->zf) goto L_48eb6c;	/* 48eb25: jne 0x48eb6c */
	FPUSH(x87_ldm((const float *)(DWORD)(m->ebp + 0x0u)));	/* 48eb27: fld dword ptr [ebp] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48eb2a: call 0x49ec14 */
	m->ecx = m->eax;	/* 48eb2f: mov ecx, eax */
	m->eax = 0x66666667u;	/* 48eb31: mov eax, 0x66666667 */
	{ long long p_ = (long long)(int)m->eax * (int)m->ecx; m->eax = (DWORD)p_; m->edx = (DWORD)((unsigned long long)p_ >> 32); m->cf = m->of = p_ != (long long)(int)m->eax; }	/* 48eb36: imul ecx */
	{ DWORD a_ = m->edx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48eb38: sar edx, 2 */
	m->eax = m->edx;	/* 48eb3b: mov eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1fu) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48eb3d: shr eax, 0x1f */
	m->ecx = (DWORD)(m->edx + m->eax*1 + 0x1u);	/* 48eb40: lea ecx, [edx + eax + 1] */
	{ DWORD a_ = m->ecx, b_ = 0xfu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48eb44: cmp ecx, 0xf */
	if (m->zf || m->sf != m->of) goto L_48eb4e;	/* 48eb47: jle 0x48eb4e */
	m->ecx = 0xfu;	/* 48eb49: mov ecx, 0xf */
L_48eb4e:
	m->eax = m->esi;	/* 48eb4e: mov eax, esi */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48eb50: test ebx, ebx */
	m->edx = (m->eax & 0x80000000u) ? 0xffffffffu : 0;	/* 48eb52: cdq  */
	if (!m->zf) goto L_48eb5f;	/* 48eb53: jne 0x48eb5f */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48eb55: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48eb57: sar eax, 1 */
	m->eax = (DWORD)(m->esp + m->eax*1 + 0x16u);	/* 48eb59: lea eax, [esp + eax + 0x16] */
	goto L_48eb6a;	/* 48eb5d: jmp 0x48eb6a */
L_48eb5f:
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48eb5f: sub eax, edx */
	{ DWORD a_ = m->eax, c_ = (0x1u) & 31; if (c_) { DWORD r_ = (DWORD)((int)a_ >> c_) & 0xffffffffu; m->cf = (int)(((DWORD)((int)a_ >> (c_ - 1))) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48eb61: sar eax, 1 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 48eb63: shl cl, 4 */
	m->eax = (DWORD)(m->esp + m->eax*1 + 0x16u);	/* 48eb66: lea eax, [esp + eax + 0x16] */
L_48eb6a:
	{ DWORD a_ = M8((DWORD)(m->eax + 0x0u)), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; M8((DWORD)(m->eax + 0x0u)) = (BYTE)(r_); }	/* 48eb6a: or byte ptr [eax], cl */
L_48eb6c:
	m->eax = M32((DWORD)(m->edi + 0x22f0400u));	/* 48eb6c: mov eax, dword ptr [edi + 0x22f0400] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 48eb72: inc esi */
	{ DWORD a_ = m->ebp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 48eb73: add ebp, 0x28 */
	{ DWORD a_ = m->esi, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48eb76: cmp esi, eax */
	if (m->sf != m->of) goto L_48eaf4;	/* 48eb78: jl 0x48eaf4 */
L_48eb7e:
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 48eb7e: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48eb82: push ecx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 48eb83: push 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48eb8au; native_call(m, 0x4a8360u);	/* 48eb85: call 0x4a8360 */
	m->ecx = M32((DWORD)(m->edi + 0x2340c78u));	/* 48eb8a: mov ecx, dword ptr [edi + 0x2340c78] */
	m->eax = M32((DWORD)(m->edi + 0x2340d1du));	/* 48eb90: mov eax, dword ptr [edi + 0x2340d1d] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48eb96: add esp, 8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48eb99: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48eb9a: cmp eax, 1 */
	M32((DWORD)(m->edi + 0x2340c78u)) = m->ecx;	/* 48eb9d: mov dword ptr [edi + 0x2340c78], ecx */
	if (!m->zf) goto L_48ec0b;	/* 48eba3: jne 0x48ec0b */
	m->edx = M32((DWORD)(m->edi + 0x2340d08u));	/* 48eba5: mov edx, dword ptr [edi + 0x2340d08] */
	m->eax = (DWORD)(m->edi + 0x2340d29u);	/* 48ebab: lea eax, [edi + 0x2340d29] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebb1: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebb2: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebb4: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebb6: push eax */
	M32((DWORD)(m->esp + 0x20u)) = 0x40u;	/* 48ebb7: mov dword ptr [esp + 0x20], 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48ebc4u; native_call(m, 0x46cc30u);	/* 48ebbf: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->edi + 0x2340d08u));	/* 48ebc4: mov ecx, dword ptr [edi + 0x2340d08] */
	m->edx = (DWORD)(m->edi + 0x234240du);	/* 48ebca: lea edx, [edi + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebd0: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebd1: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebd3: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebd5: push edx */
	m->esp -= 4; M32(m->esp) = 0x48ebdbu; native_call(m, 0x46cc30u);	/* 48ebd6: call 0x46cc30 */
	m->eax = M32((DWORD)(m->edi + 0x2340d08u));	/* 48ebdb: mov eax, dword ptr [edi + 0x2340d08] */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 48ebe1: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebe5: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebe6: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebe8: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebea: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48ebf0u; native_call(m, 0x46cc30u);	/* 48ebeb: call 0x46cc30 */
	m->edx = M32((DWORD)(m->edi + 0x2340d08u));	/* 48ebf0: mov edx, dword ptr [edi + 0x2340d08] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 48ebf6: mov eax, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebfa: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48ebfb: push eax */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 48ebfc: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec00: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48ec02: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48ec08u; native_call(m, 0x46cc30u);	/* 48ec03: call 0x46cc30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ec08: add esp, 0x40 */
L_48ec0b:
	m->edi = M32(m->esp); m->esp += 4;	/* 48ec0b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48ec0c: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48ec0d: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48ec0e: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48ec0f: add esp, 0x44 */
	m->esp += 4 + 0; return;	/* 48ec12: ret  */
}

/* match_48e0f0 (0x48e0f0), lifted by tools/lift.py */
static void lift_48e0f0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e0f0: sub esp, 0x44 */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0f3: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x4cu));	/* 48e0f4: mov ebx, dword ptr [esp + 0x4c] */
	m->eax = m->ebx;	/* 48e0f8: mov eax, ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48e0fa: push ebp */
	m->ebp = m->ecx;	/* 48e0fb: mov ebp, ecx */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48e0fd: shl eax, 4 */
	m->ecx = M32((DWORD)(m->eax + m->ebp*1 + 0x234300au));	/* 48e100: mov ecx, dword ptr [eax + ebp + 0x234300a] */
	m->eax = (DWORD)(m->eax + m->ebp*1 + 0x234300au);	/* 48e107: lea eax, [eax + ebp + 0x234300a] */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48e10e: test ecx, ecx */
	M32((DWORD)(m->esp + 0x8u)) = m->eax;	/* 48e110: mov dword ptr [esp + 8], eax */
	if (m->zf) goto L_48e2b5;	/* 48e114: je 0x48e2b5 */
	m->eax = (DWORD)(m->ebx + m->ebx*2 + 0x0u);	/* 48e11a: lea eax, [ebx + ebx*2] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48e11d: push esi */
	{ DWORD a_ = m->eax, c_ = (0xbu) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 48e11e: shl eax, 0xb */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48e121: sub eax, ebx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48e123: push edi */
	m->esi = (DWORD)(m->esp + 0x16u);	/* 48e124: lea esi, [esp + 0x16] */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0x2u);	/* 48e128: mov byte ptr [esp + 0x15], 2 */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48e12d: lea ecx, [eax + eax*2] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48e130: xor eax, eax */
	M32((DWORD)(m->esp + 0x58u)) = m->esi;	/* 48e132: mov dword ptr [esp + 0x58], esi */
	m->edx = (DWORD)(m->ebx + m->ecx*8 + 0x0u);	/* 48e136: lea edx, [ebx + ecx*8] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e139: or ecx, 0xffffffff */
	m->edx = (DWORD)(m->ebp + m->edx*2 + 0x1755230u);	/* 48e13c: lea edx, [ebp + edx*2 + 0x1755230] */
	m->edi = (DWORD)(m->edx + 0x4u);	/* 48e143: lea edi, [edx + 4] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48e146: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48e148: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48e14a: sub edi, ecx */
	m->eax = m->ecx;	/* 48e14c: mov eax, ecx */
	m->esi = m->edi;	/* 48e14e: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x58u));	/* 48e150: mov edi, dword ptr [esp + 0x58] */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e154: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48e157: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48e159: mov ecx, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x48u))) & 0xff) << 0);	/* 48e15b: mov al, byte ptr [edx + 0x48] */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e15e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48e161: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x44u))) & 0xff) << 0);	/* 48e163: mov cl, byte ptr [edx + 0x44] */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e166: mov byte ptr [esp + 0x28], al */
	M8((DWORD)(m->esp + 0x27u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e16a: mov byte ptr [esp + 0x27], cl */
	m->ecx = m->ebx;	/* 48e16e: mov ecx, ebx */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e170: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e173: add ecx, ebx */
	M8((DWORD)(m->esp + 0x2au)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 48e175: mov byte ptr [esp + 0x2a], bl */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e179: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e17c: add ecx, ebx */
	m->esi = (DWORD)(m->edx + 0x320u);	/* 48e17e: lea esi, [edx + 0x320] */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e184: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e187: add ecx, ebx */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebp + m->ecx*8 + 0x1eccb4cu))) & 0xff) << 0);	/* 48e189: mov al, byte ptr [ebp + ecx*8 + 0x1eccb4c] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x30cu))) & 0xff) << 0);	/* 48e190: mov cl, byte ptr [edx + 0x30c] */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e196: inc cl */
	M8((DWORD)(m->esp + 0x29u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e198: mov byte ptr [esp + 0x29], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x310u))) & 0xff) << 0);	/* 48e19c: mov al, byte ptr [edx + 0x310] */
	M8((DWORD)(m->esp + 0x2bu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e1a2: mov byte ptr [esp + 0x2b], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x314u))) & 0xff) << 0);	/* 48e1a6: mov cl, byte ptr [edx + 0x314] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e1ac: inc al */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e1ae: inc cl */
	M8((DWORD)(m->esp + 0x2cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e1b0: mov byte ptr [esp + 0x2c], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x318u))) & 0xff) << 0);	/* 48e1b4: mov al, byte ptr [edx + 0x318] */
	M8((DWORD)(m->esp + 0x2du)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e1ba: mov byte ptr [esp + 0x2d], cl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x31cu))) & 0xff) << 0);	/* 48e1be: mov cl, byte ptr [edx + 0x31c] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e1c4: inc al */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e1c6: inc cl */
	M8((DWORD)(m->esp + 0x2eu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e1c8: mov byte ptr [esp + 0x2e], al */
	M8((DWORD)(m->esp + 0x2fu)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e1cc: mov byte ptr [esp + 0x2f], cl */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48e1d0: xor eax, eax */
L_48e1d2:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 48e1d2: mov cl, byte ptr [esi] */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48e1d4: add esi, 4 */
	{ DWORD a_ = ((m->ecx >> 0) & 0xff), r_ = (a_ + 1) & 0xffu; FLAGS(r_, 8); m->of = (r_ == 0x80u); m->ecx = (m->ecx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e1d7: inc cl */
	M8((DWORD)(m->esp + m->eax*1 + 0x30u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e1d9: mov byte ptr [esp + eax + 0x30], cl */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48e1dd: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x6u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e1de: cmp eax, 6 */
	if (m->sf != m->of) goto L_48e1d2;	/* 48e1e1: jl 0x48e1d2 */
	m->esi = (DWORD)(m->esp + 0x40u);	/* 48e1e3: lea esi, [esp + 0x40] */
	m->ecx = (DWORD)(m->edx + 0x479aeu);	/* 48e1e7: lea ecx, [edx + 0x479ae] */
	m->edi = 0x5u;	/* 48e1ed: mov edi, 5 */
L_48e1f2:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48e1f2: xor eax, eax */
L_48e1f4:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + m->eax*1 + 0xfffffff6u))) & 0xff) << 0);	/* 48e1f4: mov dl, byte ptr [ecx + eax - 0xa] */
	M8((DWORD)(m->esi + m->eax*1 + 0xfffffff6u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 48e1f8: mov byte ptr [esi + eax - 0xa], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + m->eax*1 + 0x0u))) & 0xff) << 0);	/* 48e1fc: mov dl, byte ptr [ecx + eax] */
	M8((DWORD)(m->esi + m->eax*1 + 0x0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 48e1ff: mov byte ptr [esi + eax], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->ecx + m->eax*1 + 0xau))) & 0xff) << 0);	/* 48e202: mov dl, byte ptr [ecx + eax + 0xa] */
	M8((DWORD)(m->esi + m->eax*1 + 0xau)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 48e206: mov byte ptr [esi + eax + 0xa], dl */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48e20a: inc eax */
	{ DWORD a_ = m->eax, b_ = 0x2u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e20b: cmp eax, 2 */
	if (m->sf != m->of) goto L_48e1f4;	/* 48e20e: jl 0x48e1f4 */
	{ DWORD a_ = m->ecx, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e210: add ecx, 2 */
	{ DWORD a_ = m->esi, b_ = 0x2u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48e213: add esi, 2 */
	{ DWORD a_ = m->edi, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->edi = r_; }	/* 48e216: dec edi */
	if (!m->zf) goto L_48e1f2;	/* 48e217: jne 0x48e1f2 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48e219: mov eax, dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 48e21d: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e221: push ecx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e222: push 0x40 */
	M32((DWORD)(m->eax + 0x0u)) = 0x0u;	/* 48e224: mov dword ptr [eax], 0 */
	m->esp -= 4; M32(m->esp) = 0x48e22fu; native_call(m, 0x4a8360u);	/* 48e22a: call 0x4a8360 */
	m->ecx = M32((DWORD)(m->ebp + 0x2340c78u));	/* 48e22f: mov ecx, dword ptr [ebp + 0x2340c78] */
	m->eax = M32((DWORD)(m->ebp + 0x2340d1du));	/* 48e235: mov eax, dword ptr [ebp + 0x2340d1d] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e23b: add esp, 8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48e23e: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e23f: cmp eax, 1 */
	M32((DWORD)(m->ebp + 0x2340c78u)) = m->ecx;	/* 48e242: mov dword ptr [ebp + 0x2340c78], ecx */
	m->edi = M32(m->esp); m->esp += 4;	/* 48e248: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48e249: pop esi */
	if (!m->zf) goto L_48e2b5;	/* 48e24a: jne 0x48e2b5 */
	m->edx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48e24c: mov edx, dword ptr [ebp + 0x2340d08] */
	m->eax = (DWORD)(m->ebp + 0x2340d29u);	/* 48e252: lea eax, [ebp + 0x2340d29] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e258: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e259: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e25b: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e25d: push eax */
	M32((DWORD)(m->esp + 0x60u)) = 0x40u;	/* 48e25e: mov dword ptr [esp + 0x60], 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48e26bu; native_call(m, 0x46cc30u);	/* 48e266: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48e26b: mov ecx, dword ptr [ebp + 0x2340d08] */
	m->edx = (DWORD)(m->ebp + 0x234240du);	/* 48e271: lea edx, [ebp + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e277: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e278: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e27a: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e27c: push edx */
	m->esp -= 4; M32(m->esp) = 0x48e282u; native_call(m, 0x46cc30u);	/* 48e27d: call 0x46cc30 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48e282: mov eax, dword ptr [ebp + 0x2340d08] */
	m->ecx = (DWORD)(m->esp + 0x70u);	/* 48e288: lea ecx, [esp + 0x70] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e28c: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e28d: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e28f: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e291: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48e297u; native_call(m, 0x46cc30u);	/* 48e292: call 0x46cc30 */
	m->edx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48e297: mov edx, dword ptr [ebp + 0x2340d08] */
	m->eax = M32((DWORD)(m->esp + 0x80u));	/* 48e29d: mov eax, dword ptr [esp + 0x80] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e2a4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e2a5: push eax */
	m->ecx = (DWORD)(m->esp + 0x44u);	/* 48e2a6: lea ecx, [esp + 0x44] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e2aa: push 1 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e2ac: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48e2b2u; native_call(m, 0x46cc30u);	/* 48e2ad: call 0x46cc30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e2b2: add esp, 0x40 */
L_48e2b5:
	m->ebp = M32(m->esp); m->esp += 4;	/* 48e2b5: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48e2b6: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e2b7: add esp, 0x44 */
	m->esp += 4 + 4; return;	/* 48e2ba: ret 4 */
}

/* match_48e680 (0x48e680), lifted by tools/lift.py */
static void lift_48e680(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e680: sub esp, 0x44 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48e683: xor edx, edx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e685: push ebx */
	m->ebx = m->ecx;	/* 48e686: mov ebx, ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48e688: push ebp */
	m->ebp = 0x1u;	/* 48e689: mov ebp, 1 */
	m->eax = M32((DWORD)(m->ebx + 0x2343237u));	/* 48e68e: mov eax, dword ptr [ebx + 0x2343237] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48e694: push esi */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e695: cmp eax, ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48e697: push edi */
	if (!m->zf) goto L_48e6af;	/* 48e698: jne 0x48e6af */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0x3u);	/* 48e69a: mov byte ptr [esp + 0x15], 3 */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(0x6bu);	/* 48e69f: mov byte ptr [esp + 0x16], 0x6b */
	M32((DWORD)(m->ebx + 0x2343237u)) = m->edx;	/* 48e6a4: mov dword ptr [ebx + 0x2343237], edx */
	goto L_48e8a3;	/* 48e6aa: jmp 0x48e8a3 */
L_48e6af:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234323bu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e6af: cmp dword ptr [ebx + 0x234323b], ebp */
	if (!m->zf) goto L_48e6cc;	/* 48e6b5: jne 0x48e6cc */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0x4u);	/* 48e6b7: mov byte ptr [esp + 0x15], 4 */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(0x6bu);	/* 48e6bc: mov byte ptr [esp + 0x16], 0x6b */
	M32((DWORD)(m->ebx + 0x234323bu)) = m->edx;	/* 48e6c1: mov dword ptr [ebx + 0x234323b], edx */
	goto L_48e8a3;	/* 48e6c7: jmp 0x48e8a3 */
L_48e6cc:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234323fu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e6cc: cmp dword ptr [ebx + 0x234323f], ebp */
	if (!m->zf) goto L_48e6e9;	/* 48e6d2: jne 0x48e6e9 */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0x5u);	/* 48e6d4: mov byte ptr [esp + 0x15], 5 */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(0x6bu);	/* 48e6d9: mov byte ptr [esp + 0x16], 0x6b */
	M32((DWORD)(m->ebx + 0x234323fu)) = m->edx;	/* 48e6de: mov dword ptr [ebx + 0x234323f], edx */
	goto L_48e8a3;	/* 48e6e4: jmp 0x48e8a3 */
L_48e6e9:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234324fu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e6e9: cmp dword ptr [ebx + 0x234324f], ebp */
	if (!m->zf) goto L_48e715;	/* 48e6ef: jne 0x48e715 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2343247u))) & 0xff) << 0);	/* 48e6f1: mov al, byte ptr [ebx + 0x2343247] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x234324bu))) & 0xff) << 0);	/* 48e6f7: mov cl, byte ptr [ebx + 0x234324b] */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0x6u);	/* 48e6fd: mov byte ptr [esp + 0x15], 6 */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e702: mov byte ptr [esp + 0x16], al */
	M8((DWORD)(m->esp + 0x17u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e706: mov byte ptr [esp + 0x17], cl */
	M32((DWORD)(m->ebx + 0x234324fu)) = m->edx;	/* 48e70a: mov dword ptr [ebx + 0x234324f], edx */
	goto L_48e8a3;	/* 48e710: jmp 0x48e8a3 */
L_48e715:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234319bu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e715: cmp dword ptr [ebx + 0x234319b], ebp */
	if (!m->zf) goto L_48e76e;	/* 48e71b: jne 0x48e76e */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x234315au))) & 0xff) << 0);	/* 48e71d: mov al, byte ptr [ebx + 0x234315a] */
	m->edi = (DWORD)(m->ebx + 0x234315eu);	/* 48e723: lea edi, [ebx + 0x234315e] */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e729: mov byte ptr [esp + 0x16], al */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e72d: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48e730: xor eax, eax */
	m->esi = (DWORD)(m->esp + 0x17u);	/* 48e732: lea esi, [esp + 0x17] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48e736: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48e738: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48e73a: sub edi, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 48e73c: mov dword ptr [esp + 0x10], esi */
	m->eax = m->ecx;	/* 48e740: mov eax, ecx */
	m->esi = m->edi;	/* 48e742: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 48e744: mov edi, dword ptr [esp + 0x10] */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0x7u);	/* 48e748: mov byte ptr [esp + 0x15], 7 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e74d: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48e750: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48e752: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e754: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48e757: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2343197u))) & 0xff) << 0);	/* 48e759: mov cl, byte ptr [ebx + 0x2343197] */
	M32((DWORD)(m->ebx + 0x234319bu)) = m->edx;	/* 48e75f: mov dword ptr [ebx + 0x234319b], edx */
	M8((DWORD)(m->esp + 0x50u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e765: mov byte ptr [esp + 0x50], cl */
	goto L_48e8a3;	/* 48e769: jmp 0x48e8a3 */
L_48e76e:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234314eu)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e76e: cmp dword ptr [ebx + 0x234314e], ebp */
	if (!m->zf) goto L_48e7bd;	/* 48e774: jne 0x48e7bd */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x234310au))) & 0xff) << 0);	/* 48e776: mov al, byte ptr [ebx + 0x234310a] */
	m->edi = (DWORD)(m->ebx + 0x234310eu);	/* 48e77c: lea edi, [ebx + 0x234310e] */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e782: mov byte ptr [esp + 0x16], al */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e786: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48e789: xor eax, eax */
	m->esi = (DWORD)(m->esp + 0x17u);	/* 48e78b: lea esi, [esp + 0x17] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48e78f: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48e791: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48e793: sub edi, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 48e795: mov dword ptr [esp + 0x10], esi */
	m->eax = m->ecx;	/* 48e799: mov eax, ecx */
	m->esi = m->edi;	/* 48e79b: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 48e79d: mov edi, dword ptr [esp + 0x10] */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0x8u);	/* 48e7a1: mov byte ptr [esp + 0x15], 8 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e7a6: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48e7a9: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48e7ab: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e7ad: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48e7b0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M32((DWORD)(m->ebx + 0x234314eu)) = m->edx;	/* 48e7b2: mov dword ptr [ebx + 0x234314e], edx */
	goto L_48e8a3;	/* 48e7b8: jmp 0x48e8a3 */
L_48e7bd:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x2343156u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e7bd: cmp dword ptr [ebx + 0x2343156], ebp */
	if (!m->zf) goto L_48e7df;	/* 48e7c3: jne 0x48e7df */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x2343152u))) & 0xff) << 0);	/* 48e7c5: mov cl, byte ptr [ebx + 0x2343152] */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0x9u);	/* 48e7cb: mov byte ptr [esp + 0x15], 9 */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e7d0: mov byte ptr [esp + 0x16], cl */
	M32((DWORD)(m->ebx + 0x2343156u)) = m->edx;	/* 48e7d4: mov dword ptr [ebx + 0x2343156], edx */
	goto L_48e8a3;	/* 48e7da: jmp 0x48e8a3 */
L_48e7df:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x23431e7u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e7df: cmp dword ptr [ebx + 0x23431e7], ebp */
	if (!m->zf) goto L_48e835;	/* 48e7e5: jne 0x48e835 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x234319fu))) & 0xff) << 0);	/* 48e7e7: mov al, byte ptr [ebx + 0x234319f] */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x23431a3u))) & 0xff) << 0);	/* 48e7ed: mov cl, byte ptr [ebx + 0x23431a3] */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e7f3: mov byte ptr [esp + 0x16], al */
	M8((DWORD)(m->esp + 0x17u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e7f7: mov byte ptr [esp + 0x17], cl */
	m->edi = (DWORD)(m->ebx + 0x23431a7u);	/* 48e7fb: lea edi, [ebx + 0x23431a7] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e801: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48e804: xor eax, eax */
	m->esi = (DWORD)(m->esp + 0x18u);	/* 48e806: lea esi, [esp + 0x18] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48e80a: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48e80c: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48e80e: sub edi, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 48e810: mov dword ptr [esp + 0x10], esi */
	m->eax = m->ecx;	/* 48e814: mov eax, ecx */
	m->esi = m->edi;	/* 48e816: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 48e818: mov edi, dword ptr [esp + 0x10] */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0xau);	/* 48e81c: mov byte ptr [esp + 0x15], 0xa */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e821: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48e824: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48e826: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e828: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48e82b: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M32((DWORD)(m->ebx + 0x23431e7u)) = m->edx;	/* 48e82d: mov dword ptr [ebx + 0x23431e7], edx */
	goto L_48e8a3;	/* 48e833: jmp 0x48e8a3 */
L_48e835:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x2343233u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e835: cmp dword ptr [ebx + 0x2343233], ebp */
	if (!m->zf) goto L_48e88b;	/* 48e83b: jne 0x48e88b */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x234240du))) & 0xff) << 0);	/* 48e83d: mov cl, byte ptr [ebx + 0x234240d] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->ebx + 0x23431efu))) & 0xff) << 0);	/* 48e843: mov al, byte ptr [ebx + 0x23431ef] */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 48e849: mov byte ptr [esp + 0x16], cl */
	M8((DWORD)(m->esp + 0x17u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e84d: mov byte ptr [esp + 0x17], al */
	m->edi = (DWORD)(m->ebx + 0x23431f3u);	/* 48e851: lea edi, [ebx + 0x23431f3] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e857: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48e85a: xor eax, eax */
	m->esi = (DWORD)(m->esp + 0x18u);	/* 48e85c: lea esi, [esp + 0x18] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 48e860: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 48e862: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 48e864: sub edi, ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->esi;	/* 48e866: mov dword ptr [esp + 0x10], esi */
	m->eax = m->ecx;	/* 48e86a: mov eax, ecx */
	m->esi = m->edi;	/* 48e86c: mov esi, edi */
	m->edi = M32((DWORD)(m->esp + 0x10u));	/* 48e86e: mov edi, dword ptr [esp + 0x10] */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0xbu);	/* 48e872: mov byte ptr [esp + 0x15], 0xb */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e877: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 48e87a: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 48e87c: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48e87e: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 48e881: rep movsb byte ptr es:[edi], byte ptr [esi] */
	M32((DWORD)(m->ebx + 0x2343233u)) = m->edx;	/* 48e883: mov dword ptr [ebx + 0x2343233], edx */
	goto L_48e8a3;	/* 48e889: jmp 0x48e8a3 */
L_48e88b:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x2343243u)), b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e88b: cmp dword ptr [ebx + 0x2343243], ebp */
	if (!m->zf) goto L_48e8a3;	/* 48e891: jne 0x48e8a3 */
	M8((DWORD)(m->esp + 0x15u)) = (BYTE)(0xdu);	/* 48e893: mov byte ptr [esp + 0x15], 0xd */
	M8((DWORD)(m->esp + 0x16u)) = (BYTE)(0x6bu);	/* 48e898: mov byte ptr [esp + 0x16], 0x6b */
	M32((DWORD)(m->ebx + 0x2343243u)) = m->edx;	/* 48e89d: mov dword ptr [ebx + 0x2343243], edx */
L_48e8a3:
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234319bu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8a3: cmp dword ptr [ebx + 0x234319b], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8a9: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234314eu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8ab: cmp dword ptr [ebx + 0x234314e], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8b1: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x2343156u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8b3: cmp dword ptr [ebx + 0x2343156], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8b9: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x23431e7u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8bb: cmp dword ptr [ebx + 0x23431e7], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8c1: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x2343233u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8c3: cmp dword ptr [ebx + 0x2343233], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8c9: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x2343237u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8cb: cmp dword ptr [ebx + 0x2343237], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8d1: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234323bu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8d3: cmp dword ptr [ebx + 0x234323b], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8d9: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234323fu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8db: cmp dword ptr [ebx + 0x234323f], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8e1: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x234324fu)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8e3: cmp dword ptr [ebx + 0x234324f], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8e9: jne 0x48e8f9 */
	{ DWORD a_ = M32((DWORD)(m->ebx + 0x2343243u)), b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e8eb: cmp dword ptr [ebx + 0x2343243], edx */
	if (!m->zf) goto L_48e8f9;	/* 48e8f1: jne 0x48e8f9 */
	M32((DWORD)(m->ebx + 0x2343106u)) = m->edx;	/* 48e8f3: mov dword ptr [ebx + 0x2343106], edx */
L_48e8f9:
	m->ecx = (DWORD)(m->esp + 0x14u);	/* 48e8f9: lea ecx, [esp + 0x14] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e8fd: push ecx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e8fe: push 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48e905u; native_call(m, 0x4a8360u);	/* 48e900: call 0x4a8360 */
	m->ecx = M32((DWORD)(m->ebx + 0x2340c78u));	/* 48e905: mov ecx, dword ptr [ebx + 0x2340c78] */
	m->eax = M32((DWORD)(m->ebx + 0x2340d1du));	/* 48e90b: mov eax, dword ptr [ebx + 0x2340d1d] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e911: add esp, 8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48e914: inc ecx */
	{ DWORD a_ = m->eax, b_ = m->ebp & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e915: cmp eax, ebp */
	M32((DWORD)(m->ebx + 0x2340c78u)) = m->ecx;	/* 48e917: mov dword ptr [ebx + 0x2340c78], ecx */
	if (!m->zf) goto L_48e981;	/* 48e91d: jne 0x48e981 */
	m->edx = M32((DWORD)(m->ebx + 0x2340d08u));	/* 48e91f: mov edx, dword ptr [ebx + 0x2340d08] */
	m->eax = (DWORD)(m->ebx + 0x2340d29u);	/* 48e925: lea eax, [ebx + 0x2340d29] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e92b: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48e92c: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e92d: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e92f: push eax */
	M32((DWORD)(m->esp + 0x20u)) = 0x40u;	/* 48e930: mov dword ptr [esp + 0x20], 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48e93du; native_call(m, 0x46cc30u);	/* 48e938: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->ebx + 0x2340d08u));	/* 48e93d: mov ecx, dword ptr [ebx + 0x2340d08] */
	m->edx = (DWORD)(m->ebx + 0x234240du);	/* 48e943: lea edx, [ebx + 0x234240d] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e949: push ecx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48e94a: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e94b: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e94d: push edx */
	m->esp -= 4; M32(m->esp) = 0x48e953u; native_call(m, 0x46cc30u);	/* 48e94e: call 0x46cc30 */
	m->eax = M32((DWORD)(m->ebx + 0x2340d08u));	/* 48e953: mov eax, dword ptr [ebx + 0x2340d08] */
	m->ecx = (DWORD)(m->esp + 0x30u);	/* 48e959: lea ecx, [esp + 0x30] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e95d: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48e95e: push ebp */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e95f: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e961: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48e967u; native_call(m, 0x46cc30u);	/* 48e962: call 0x46cc30 */
	m->edx = M32((DWORD)(m->ebx + 0x2340d08u));	/* 48e967: mov edx, dword ptr [ebx + 0x2340d08] */
	m->eax = M32((DWORD)(m->esp + 0x40u));	/* 48e96d: mov eax, dword ptr [esp + 0x40] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e971: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e972: push eax */
	m->ecx = (DWORD)(m->esp + 0x4cu);	/* 48e973: lea ecx, [esp + 0x4c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48e977: push ebp */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e978: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48e97eu; native_call(m, 0x46cc30u);	/* 48e979: call 0x46cc30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e97e: add esp, 0x40 */
L_48e981:
	m->edi = M32(m->esp); m->esp += 4;	/* 48e981: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48e982: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48e983: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48e984: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x44u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e985: add esp, 0x44 */
	m->esp += 4 + 0; return;	/* 48e988: ret  */
}

/* match_48e2c0 (0x48e2c0), lifted by tools/lift.py */
static void lift_48e2c0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e2c0: sub esp, 0x48 */
	m->eax = M32((DWORD)(m->esp + 0x4cu));	/* 48e2c3: mov eax, dword ptr [esp + 0x4c] */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 48e2c7: push ebp */
	m->ebp = m->ecx;	/* 48e2c8: mov ebp, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48e2ca: push edi */
	m->ecx = m->eax;	/* 48e2cb: mov ecx, eax */
	M8((DWORD)(m->esp + 0x11u)) = (BYTE)(0x0u);	/* 48e2cd: mov byte ptr [esp + 0x11], 0 */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e2d2: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e2d5: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e2d7: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e2da: add ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 48e2dc: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e2df: add ecx, eax */
	m->edx = (m->edx & 0xffff0000u) | ((M16((DWORD)(m->ebp + m->ecx*8 + 0x1ecce60u))) & 0xffff);	/* 48e2e1: mov dx, word ptr [ebp + ecx*8 + 0x1ecce60] */
	m->edi = (DWORD)(m->ebp + m->ecx*8 + 0x1ecca70u);	/* 48e2e9: lea edi, [ebp + ecx*8 + 0x1ecca70] */
	M16((DWORD)(m->esp + 0x12u)) = (WORD)((m->edx & 0xffff));	/* 48e2f0: mov word ptr [esp + 0x12], dx */
	m->ecx = M32((DWORD)(m->edi + 0x3ecu));	/* 48e2f5: mov ecx, dword ptr [edi + 0x3ec] */
	{ DWORD a_ = m->ecx, b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e2fb: sub ecx, 0 */
	if (m->zf) goto L_48e314;	/* 48e2fe: je 0x48e314 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48e300: dec ecx */
	if (m->zf) goto L_48e30d;	/* 48e301: je 0x48e30d */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48e303: dec ecx */
	if (!m->zf) goto L_48e325;	/* 48e304: jne 0x48e325 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 48e306: shl al, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xeu & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e309: or al, 0xe */
	goto L_48e321;	/* 48e30b: jmp 0x48e321 */
L_48e30d:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 48e30d: shl al, 4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0xcu & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e310: or al, 0xc */
	goto L_48e321;	/* 48e312: jmp 0x48e321 */
L_48e314:
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x140u))) & 0xff) << 0);	/* 48e314: mov dl, byte ptr [edi + 0x140] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 48e31a: shl al, 3 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->edx >> 0) & 0xff) & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e31d: or al, dl */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), c_ = (0x1u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 48e31f: shl al, 1 */
L_48e321:
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e321: mov byte ptr [esp + 0x14], al */
L_48e325:
	m->ecx = M32((DWORD)(m->edi + 0x14cu));	/* 48e325: mov ecx, dword ptr [edi + 0x14c] */
	m->eax = 0x1u;	/* 48e32b: mov eax, 1 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e330: cmp ecx, eax */
	if (!m->zf) goto L_48e338;	/* 48e332: jne 0x48e338 */
	{ DWORD a_ = M8((DWORD)(m->esp + 0x14u)), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; M8((DWORD)(m->esp + 0x14u)) = (BYTE)(r_); }	/* 48e334: or byte ptr [esp + 0x14], al */
L_48e338:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x180u)));	/* 48e338: fld dword ptr [edi + 0x180] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e33e: fmul dword ptr [0x4a93ec] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e344: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48e345: push esi */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e346: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x184u)));	/* 48e34b: fld dword ptr [edi + 0x184] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e351: fmul dword ptr [0x4a93ec] */
	M16((DWORD)(m->esp + 0x1du)) = (WORD)((m->eax & 0xffff));	/* 48e357: mov word ptr [esp + 0x1d], ax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e35c: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x188u)));	/* 48e361: fld dword ptr [edi + 0x188] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e367: fmul dword ptr [0x4a93ec] */
	M16((DWORD)(m->esp + 0x1fu)) = (WORD)((m->eax & 0xffff));	/* 48e36d: mov word ptr [esp + 0x1f], ax */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e372: call 0x49ec14 */
	M16((DWORD)(m->esp + 0x21u)) = (WORD)((m->eax & 0xffff));	/* 48e377: mov word ptr [esp + 0x21], ax */
	m->eax = M32((DWORD)(m->edi + 0x18cu));	/* 48e37c: mov eax, dword ptr [edi + 0x18c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e382: push eax */
	m->esp -= 4; M32(m->esp) = 0x48e388u; { long double r_ = native_call_fp(m, 0x46c100u); FPUSH(r_); }	/* 48e383: call 0x46c100 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa49cu));	/* 48e388: fmul dword ptr [0x4aa49c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e38e: call 0x49ec14 */
	m->ecx = M32((DWORD)(m->edi + 0x190u));	/* 48e393: mov ecx, dword ptr [edi + 0x190] */
	M8((DWORD)(m->esp + 0x27u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e399: mov byte ptr [esp + 0x27], al */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e39d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48e3a3u; { long double r_ = native_call_fp(m, 0x46c100u); FPUSH(r_); }	/* 48e39e: call 0x46c100 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa49cu));	/* 48e3a3: fmul dword ptr [0x4aa49c] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e3a9: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x194u)));	/* 48e3ae: fld dword ptr [edi + 0x194] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48e3b4: fmul dword ptr [0x4a9418] */
	M8((DWORD)(m->esp + 0x2cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e3ba: mov byte ptr [esp + 0x2c], al */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e3be: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x198u)));	/* 48e3c3: fld dword ptr [edi + 0x198] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9418u));	/* 48e3c9: fmul dword ptr [0x4a9418] */
	M8((DWORD)(m->esp + 0x2du)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e3cf: mov byte ptr [esp + 0x2d], al */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e3d3: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x19cu)));	/* 48e3d8: fld dword ptr [edi + 0x19c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa498u));	/* 48e3de: fmul dword ptr [0x4aa498] */
	M8((DWORD)(m->esp + 0x2eu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e3e4: mov byte ptr [esp + 0x2e], al */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e3e8: call 0x49ec14 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x1a4u)));	/* 48e3ed: fld dword ptr [edi + 0x1a4] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa498u));	/* 48e3f3: fmul dword ptr [0x4aa498] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 48e3f9: mov bl, al */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffu; m->cf = (int)((a_ >> (8 - c_)) & 1); FLAGS(r_, 8); m->of = 0; m->ebx = (m->ebx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); } }	/* 48e3fb: shl bl, 4 */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e3fe: call 0x49ec14 */
	m->edx = M32((DWORD)(m->edi + 0x1a0u));	/* 48e403: mov edx, dword ptr [edi + 0x1a0] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->ebx = (m->ebx & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e409: or bl, al */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e40b: push edx */
	M8((DWORD)(m->esp + 0x33u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 48e40c: mov byte ptr [esp + 0x33], bl */
	m->esp -= 4; M32(m->esp) = 0x48e415u; { long double r_ = native_call_fp(m, 0x46c100u); FPUSH(r_); }	/* 48e410: call 0x46c100 */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa49cu));	/* 48e415: fmul dword ptr [0x4aa49c] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e41b: add esp, 0xc */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e41e: call 0x49ec14 */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e423: mov byte ptr [esp + 0x28], al */
	m->eax = M32((DWORD)(m->edi + 0x8850u));	/* 48e427: mov eax, dword ptr [edi + 0x8850] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e42d: cmp eax, 1 */
	M8((DWORD)(m->esp + 0x29u)) = (BYTE)(0x0u);	/* 48e430: mov byte ptr [esp + 0x29], 0 */
	if (!m->zf) goto L_48e465;	/* 48e435: jne 0x48e465 */
	m->ecx = M32((DWORD)(m->edi + 0x128u));	/* 48e437: mov ecx, dword ptr [edi + 0x128] */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0x80u) & 0xff) << 0);	/* 48e43d: mov al, 0x80 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48e43f: test ecx, ecx */
	if (!m->zf && m->sf == m->of) goto L_48e445;	/* 48e441: jg 0x48e445 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((0xc0u) & 0xff) << 0);	/* 48e443: mov al, 0xc0 */
L_48e445:
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4c0u))) & 0xff) << 0);	/* 48e445: mov cl, byte ptr [edi + 0x4c0] */
	M32((DWORD)(m->edi + 0x8850u)) = 0x0u;	/* 48e44b: mov dword ptr [edi + 0x8850], 0 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->ecx >> 0) & 0xff) & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e455: or al, cl */
	M8((DWORD)(m->esp + 0x29u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e457: mov byte ptr [esp + 0x29], al */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edi + 0x4c4u))) & 0xff) << 0);	/* 48e45b: mov al, byte ptr [edi + 0x4c4] */
	M8((DWORD)(m->esp + 0x2au)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e461: mov byte ptr [esp + 0x2a], al */
L_48e465:
	m->eax = (DWORD)(m->esp + 0x2bu);	/* 48e465: lea eax, [esp + 0x2b] */
	m->ecx = 0x5u;	/* 48e469: mov ecx, 5 */
L_48e46e:
	M8((DWORD)(m->eax + 0x0u)) = (BYTE)(0x0u);	/* 48e46e: mov byte ptr [eax], 0 */
	{ DWORD a_ = m->eax, b_ = 0x9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48e471: add eax, 9 */
	{ DWORD a_ = m->ecx, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->ecx = r_; }	/* 48e474: dec ecx */
	if (!m->zf) goto L_48e46e;	/* 48e475: jne 0x48e46e */
	m->ecx = (DWORD)(m->edi + 0x360u);	/* 48e477: lea ecx, [edi + 0x360] */
	m->esi = (DWORD)(m->esp + 0x2bu);	/* 48e47d: lea esi, [esp + 0x2b] */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 48e481: mov dword ptr [esp + 0x5c], ecx */
	m->ebx = (DWORD)(m->edi + 0x1fcu);	/* 48e485: lea ebx, [edi + 0x1fc] */
	M32((DWORD)(m->esp + 0x10u)) = 0x5u;	/* 48e48b: mov dword ptr [esp + 0x10], 5 */
L_48e493:
	m->eax = M32((DWORD)(m->ecx + 0x0u));	/* 48e493: mov eax, dword ptr [ecx] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48e495: test eax, eax */
	if (m->sf != m->of) goto L_48e5c1;	/* 48e497: jl 0x48e5c1 */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 48e49d: lea edx, [eax + eax*4] */
	{ DWORD a_ = m->edx, c_ = (0x3u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->edx = r_; } }	/* 48e4a0: shl edx, 3 */
	{ DWORD a_ = m->edx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edx = r_; }	/* 48e4a3: sub edx, eax */
	m->eax = (DWORD)(m->eax + m->edx*4 + 0x0u);	/* 48e4a5: lea eax, [eax + edx*4] */
	m->edi = (DWORD)(m->ebp + m->eax*8 + 0x22225fcu);	/* 48e4a8: lea edi, [ebp + eax*8 + 0x22225fc] */
	m->eax = M32((DWORD)(m->ebp + m->eax*8 + 0x2222600u));	/* 48e4af: mov eax, dword ptr [ebp + eax*8 + 0x2222600] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e4b6: cmp eax, 1 */
	if (!m->zf) goto L_48e5bb;	/* 48e4b9: jne 0x48e5bb */
	m->eax = M32((DWORD)(m->ebx + 0x0u));	/* 48e4bf: mov eax, dword ptr [ebx] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e4c1: cmp eax, 1 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 48e4c4: mov al, byte ptr [esi] */
	if (!m->zf) goto L_48e4d4;	/* 48e4c6: jne 0x48e4d4 */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x3u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e4c8: or al, 3 */
	M32((DWORD)(m->ebx + 0x0u)) = 0x0u;	/* 48e4ca: mov dword ptr [ebx], 0 */
	M8((DWORD)(m->esi + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e4d0: mov byte ptr [esi], al */
	goto L_48e4d8;	/* 48e4d2: jmp 0x48e4d8 */
L_48e4d4:
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e4d4: or al, 1 */
	M8((DWORD)(m->esi + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e4d6: mov byte ptr [esi], al */
L_48e4d8:
	m->eax = M32((DWORD)(m->edi + 0xb8u));	/* 48e4d8: mov eax, dword ptr [edi + 0xb8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48e4de: test eax, eax */
	if (m->sf != m->of) goto L_48e4f5;	/* 48e4e0: jl 0x48e4f5 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 48e4e2: mov al, byte ptr [esi] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = 0x4u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; m->eax = (m->eax & ~(0xffu << 0)) | (((r_) & 0xff) << 0); }	/* 48e4e4: or al, 4 */
	M8((DWORD)(m->esi + 0x0u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 48e4e6: mov byte ptr [esi], al */
	m->ecx = (m->ecx & 0xffff0000u) | ((M16((DWORD)(m->edi + 0xb8u))) & 0xffff);	/* 48e4e8: mov cx, word ptr [edi + 0xb8] */
	M16((DWORD)(m->esi + 0x1u)) = (WORD)((m->ecx & 0xffff));	/* 48e4ef: mov word ptr [esi + 1], cx */
	goto L_48e51e;	/* 48e4f3: jmp 0x48e51e */
L_48e4f5:
	m->eax = M32((DWORD)(m->edi + 0x6cu));	/* 48e4f5: mov eax, dword ptr [edi + 0x6c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48e4f8: test eax, eax */
	if (m->zf) goto L_48e518;	/* 48e4fa: je 0x48e518 */
	m->ecx = M32((DWORD)(m->ebp + 0x1f40ecu));	/* 48e4fc: mov ecx, dword ptr [ebp + 0x1f40ec] */
	{ DWORD v_ = 0xacu; m->esp -= 4; M32(m->esp) = v_; }	/* 48e502: push 0xac */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e507: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e508: push eax */
	m->esp -= 4; M32(m->esp) = 0x48e50eu; native_call(m, 0x46cba0u);	/* 48e509: call 0x46cba0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e50e: add esp, 0xc */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48e511: inc eax */
	M16((DWORD)(m->esi + 0x1u)) = (WORD)((m->eax & 0xffff));	/* 48e512: mov word ptr [esi + 1], ax */
	goto L_48e51e;	/* 48e516: jmp 0x48e51e */
L_48e518:
	M16((DWORD)(m->esi + 0x1u)) = (WORD)(0x0u);	/* 48e518: mov word ptr [esi + 1], 0 */
L_48e51e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x70u)));	/* 48e51e: fld dword ptr [edi + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edi + 0x74u)); FPOP();	/* 48e521: fcomp dword ptr [edi + 0x74] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48e524: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48e526: test ah, 0x41 */
	if (!m->zf) goto L_48e52e;	/* 48e529: jne 0x48e52e */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x8u & 0xffu, r_ = a_ | b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; M8((DWORD)(m->esi + 0x0u)) = (BYTE)(r_); }	/* 48e52b: or byte ptr [esi], 8 */
L_48e52e:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x70u)));	/* 48e52e: fld dword ptr [edi + 0x70] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(m->edi + 0x74u)); FPOP();	/* 48e531: fcomp dword ptr [edi + 0x74] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 48e534: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 48e536: test ah, 0x41 */
	if (!m->zf) goto L_48e57a;	/* 48e539: jne 0x48e57a */
	m->eax = M32((DWORD)(m->edi + 0x6cu));	/* 48e53b: mov eax, dword ptr [edi + 0x6c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48e53e: test eax, eax */
	if (m->zf) goto L_48e57a;	/* 48e540: je 0x48e57a */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x60u)));	/* 48e542: fld dword ptr [edi + 0x60] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e545: fmul dword ptr [0x4a93ec] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e54b: call 0x49ec14 */
	M16((DWORD)(m->esi + 0x3u)) = (WORD)((m->eax & 0xffff));	/* 48e550: mov word ptr [esi + 3], ax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x64u)));	/* 48e554: fld dword ptr [edi + 0x64] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e557: fmul dword ptr [0x4a93ec] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e55d: call 0x49ec14 */
	M16((DWORD)(m->esi + 0x5u)) = (WORD)((m->eax & 0xffff));	/* 48e562: mov word ptr [esi + 5], ax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x68u)));	/* 48e566: fld dword ptr [edi + 0x68] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e569: fmul dword ptr [0x4a93ec] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e56f: call 0x49ec14 */
	M16((DWORD)(m->esi + 0x7u)) = (WORD)((m->eax & 0xffff));	/* 48e574: mov word ptr [esi + 7], ax */
	goto L_48e5c1;	/* 48e578: jmp 0x48e5c1 */
L_48e57a:
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x84u)));	/* 48e57a: fld dword ptr [edi + 0x84] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e580: fmul dword ptr [0x4a93ec] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e586: call 0x49ec14 */
	M16((DWORD)(m->esi + 0x3u)) = (WORD)((m->eax & 0xffff));	/* 48e58b: mov word ptr [esi + 3], ax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x88u)));	/* 48e58f: fld dword ptr [edi + 0x88] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e595: fmul dword ptr [0x4a93ec] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e59b: call 0x49ec14 */
	M16((DWORD)(m->esi + 0x5u)) = (WORD)((m->eax & 0xffff));	/* 48e5a0: mov word ptr [esi + 5], ax */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x8cu)));	/* 48e5a4: fld dword ptr [edi + 0x8c] */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a93ecu));	/* 48e5aa: fmul dword ptr [0x4a93ec] */
	{ long long r_ = crt_ftol64(ST(0)); FPOP(); m->eax = (DWORD)r_; m->edx = (DWORD)((unsigned long long)r_ >> 32); }	/* 48e5b0: call 0x49ec14 */
	M16((DWORD)(m->esi + 0x7u)) = (WORD)((m->eax & 0xffff));	/* 48e5b5: mov word ptr [esi + 7], ax */
	goto L_48e5c1;	/* 48e5b9: jmp 0x48e5c1 */
L_48e5bb:
	M32((DWORD)(m->ecx + 0x0u)) = 0xffffffffu;	/* 48e5bb: mov dword ptr [ecx], 0xffffffff */
L_48e5c1:
	m->ecx = M32((DWORD)(m->esp + 0x5cu));	/* 48e5c1: mov ecx, dword ptr [esp + 0x5c] */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 48e5c5: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48e5c9: add ecx, 4 */
	{ DWORD a_ = m->ebx, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebx = r_; }	/* 48e5cc: add ebx, 0x20 */
	{ DWORD a_ = m->esi, b_ = 0x9u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 48e5cf: add esi, 9 */
	{ DWORD a_ = m->eax, r_ = (a_ - 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (a_ == 0x80000000u); m->eax = r_; }	/* 48e5d2: dec eax */
	M32((DWORD)(m->esp + 0x5cu)) = m->ecx;	/* 48e5d3: mov dword ptr [esp + 0x5c], ecx */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 48e5d7: mov dword ptr [esp + 0x10], eax */
	if (!m->zf) goto L_48e493;	/* 48e5db: jne 0x48e493 */
	m->edx = (DWORD)(m->esp + 0x18u);	/* 48e5e1: lea edx, [esp + 0x18] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e5e5: push edx */
	{ DWORD v_ = 0x40u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e5e6: push 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48e5edu; native_call(m, 0x4a8360u);	/* 48e5e8: call 0x4a8360 */
	m->ecx = M32((DWORD)(m->ebp + 0x2340c78u));	/* 48e5ed: mov ecx, dword ptr [ebp + 0x2340c78] */
	m->eax = M32((DWORD)(m->ebp + 0x2340d1du));	/* 48e5f3: mov eax, dword ptr [ebp + 0x2340d1d] */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e5f9: add esp, 8 */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 48e5fc: inc ecx */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48e5fd: cmp eax, 1 */
	M32((DWORD)(m->ebp + 0x2340c78u)) = m->ecx;	/* 48e600: mov dword ptr [ebp + 0x2340c78], ecx */
	m->esi = M32(m->esp); m->esp += 4;	/* 48e606: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48e607: pop ebx */
	if (!m->zf) goto L_48e670;	/* 48e608: jne 0x48e670 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48e60a: mov eax, dword ptr [ebp + 0x2340d08] */
	m->ecx = (DWORD)(m->ebp + 0x2340d29u);	/* 48e610: lea ecx, [ebp + 0x2340d29] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e616: push eax */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e617: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e619: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e61b: push ecx */
	M32((DWORD)(m->esp + 0x1cu)) = 0x40u;	/* 48e61c: mov dword ptr [esp + 0x1c], 0x40 */
	m->esp -= 4; M32(m->esp) = 0x48e629u; native_call(m, 0x46cc30u);	/* 48e624: call 0x46cc30 */
	m->edx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48e629: mov edx, dword ptr [ebp + 0x2340d08] */
	m->eax = (DWORD)(m->ebp + 0x234240du);	/* 48e62f: lea eax, [ebp + 0x234240d] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e635: push edx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e636: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e638: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e63a: push eax */
	m->esp -= 4; M32(m->esp) = 0x48e640u; native_call(m, 0x46cc30u);	/* 48e63b: call 0x46cc30 */
	m->ecx = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48e640: mov ecx, dword ptr [ebp + 0x2340d08] */
	m->edx = (DWORD)(m->esp + 0x2cu);	/* 48e646: lea edx, [esp + 0x2c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e64a: push ecx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e64b: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e64d: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e64f: push edx */
	m->esp -= 4; M32(m->esp) = 0x48e655u; native_call(m, 0x46cc30u);	/* 48e650: call 0x46cc30 */
	m->eax = M32((DWORD)(m->ebp + 0x2340d08u));	/* 48e655: mov eax, dword ptr [ebp + 0x2340d08] */
	m->ecx = M32((DWORD)(m->esp + 0x3cu));	/* 48e65b: mov ecx, dword ptr [esp + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48e65f: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e660: push ecx */
	m->edx = (DWORD)(m->esp + 0x48u);	/* 48e661: lea edx, [esp + 0x48] */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48e665: push 1 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48e667: push edx */
	m->esp -= 4; M32(m->esp) = 0x48e66du; native_call(m, 0x46cc30u);	/* 48e668: call 0x46cc30 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e66d: add esp, 0x40 */
L_48e670:
	m->edi = M32(m->esp); m->esp += 4;	/* 48e670: pop edi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 48e671: pop ebp */
	{ DWORD a_ = m->esp, b_ = 0x48u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48e672: add esp, 0x48 */
	m->esp += 4 + 4; return;	/* 48e675: ret 4 */
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
