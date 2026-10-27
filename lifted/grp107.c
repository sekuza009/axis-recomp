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

static void lift_4014f0(X86 *m);
static void lift_401590(X86 *m);
static void lift_41e760(X86 *m);
static void lift_443c80(X86 *m);
static void lift_447960(X86 *m);
static void lift_4479b0(X86 *m);
static void lift_401540(X86 *m);

/* load_401540 (0x401540), lifted by tools/lift.py */
static void lift_401540(X86 *m)
{
	m->eax = M32((DWORD)(0x4d1fa8u));	/* 401540: mov eax, dword ptr [0x4d1fa8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401545: test eax, eax */
	if (!m->zf) goto L_40154c;	/* 401547: jne 0x40154c */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 401549: xor eax, eax */
	m->esp += 4 + 0; return;	/* 40154b: ret  */
L_40154c:
	m->eax = M32((DWORD)(0x4d1fa0u));	/* 40154c: mov eax, dword ptr [0x4d1fa0] */
	{ DWORD v_ = 0x4d1e9cu; m->esp -= 4; M32(m->esp) = v_; }	/* 401551: push 0x4d1e9c */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 401556: push 0x100 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40155b: push eax */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 40155c: mov ecx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x401561u; native_call(m, M32((DWORD)(m->ecx + 0x24u)));	/* 40155e: call dword ptr [ecx + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401561: test eax, eax */
	if (m->zf) goto L_401574;	/* 401563: je 0x401574 */
	{ DWORD a_ = m->eax, b_ = 0x8007001eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401565: cmp eax, 0x8007001e */
	if (!m->zf) goto L_401571;	/* 40156a: jne 0x401571 */
	m->esp -= 4; M32(m->esp) = 0x401571u; native_call(m, 0x4012c0u);	/* 40156c: call 0x4012c0 */
L_401571:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 401571: xor eax, eax */
	m->esp += 4 + 0; return;	/* 401573: ret  */
L_401574:
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 401574: mov edx, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 401578: xor eax, eax */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->edx + 0x4d1e9cu))) & 0xff) << 0);	/* 40157a: mov al, byte ptr [edx + 0x4d1e9c] */
	{ DWORD a_ = m->eax, c_ = (0x7u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 401580: shr eax, 7 */
	m->esp += 4 + 0; return;	/* 401583: ret  */
}

/* load_4014f0 (0x4014f0), lifted by tools/lift.py */
static void lift_4014f0(X86 *m)
{
	m->eax = M32((DWORD)(0x4d1fa8u));	/* 4014f0: mov eax, dword ptr [0x4d1fa8] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4014f5: test eax, eax */
	if (m->zf) goto L_401531;	/* 4014f7: je 0x401531 */
	m->eax = M32((DWORD)(0x4d1fa0u));	/* 4014f9: mov eax, dword ptr [0x4d1fa0] */
	{ DWORD v_ = 0x4d1e9cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4014fe: push 0x4d1e9c */
	{ DWORD v_ = 0x100u; m->esp -= 4; M32(m->esp) = v_; }	/* 401503: push 0x100 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401508: push eax */
	m->ecx = M32((DWORD)(m->eax + 0x0u));	/* 401509: mov ecx, dword ptr [eax] */
	m->esp -= 4; M32(m->esp) = 0x40150eu; native_call(m, M32((DWORD)(m->ecx + 0x24u)));	/* 40150b: call dword ptr [ecx + 0x24] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40150e: test eax, eax */
	if (m->sf != m->of) goto L_401525;	/* 401510: jl 0x401525 */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 401512: mov edx, dword ptr [esp + 4] */
	{ DWORD a_ = M8((DWORD)(m->edx + 0x4d1e9cu)), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401516: test byte ptr [edx + 0x4d1e9c], 0x80 */
	if (m->zf) goto L_401531;	/* 40151d: je 0x401531 */
	m->eax = 0x1u;	/* 40151f: mov eax, 1 */
	m->esp += 4 + 0; return;	/* 401524: ret  */
L_401525:
	{ DWORD a_ = m->eax, b_ = 0x8007001eu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401525: cmp eax, 0x8007001e */
	if (!m->zf) goto L_401531;	/* 40152a: jne 0x401531 */
	m->esp -= 4; M32(m->esp) = 0x401531u; native_call(m, 0x4012c0u);	/* 40152c: call 0x4012c0 */
L_401531:
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 401531: xor eax, eax */
	m->esp += 4 + 0; return;	/* 401533: ret  */
}

/* input_isDown (0x401590), lifted by tools/lift.py */
static void lift_401590(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 401590: mov eax, dword ptr [esp + 4] */
	{ DWORD a_ = m->eax, b_ = 0xfau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401594: cmp eax, 0xfa */
	if (!m->zf) goto L_4015a1;	/* 401599: jne 0x4015a1 */
	m->eax = M32((DWORD)(0x4ded94u));	/* 40159b: mov eax, dword ptr [0x4ded94] */
	m->esp += 4 + 0; return;	/* 4015a0: ret  */
L_4015a1:
	{ DWORD a_ = m->eax, b_ = 0xfbu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4015a1: cmp eax, 0xfb */
	if (!m->zf) goto L_4015ae;	/* 4015a6: jne 0x4015ae */
	m->eax = M32((DWORD)(0x4ded98u));	/* 4015a8: mov eax, dword ptr [0x4ded98] */
	m->esp += 4 + 0; return;	/* 4015ad: ret  */
L_4015ae:
	{ DWORD a_ = m->eax, b_ = 0xfcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4015ae: cmp eax, 0xfc */
	if (!m->zf) goto L_4015bb;	/* 4015b3: jne 0x4015bb */
	m->eax = M32((DWORD)(0x4ded9cu));	/* 4015b5: mov eax, dword ptr [0x4ded9c] */
	m->esp += 4 + 0; return;	/* 4015ba: ret  */
L_4015bb:
	{ DWORD a_ = m->eax, b_ = 0xfdu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4015bb: cmp eax, 0xfd */
	if (!m->zf) goto L_4015d0;	/* 4015c0: jne 0x4015d0 */
	m->ecx = M32((DWORD)(0x4ded7cu));	/* 4015c2: mov ecx, dword ptr [0x4ded7c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4015c8: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4015ca: test ecx, ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((m->sf != m->of) ? 1u : 0u) & 0xff) << 0);	/* 4015cc: setl al */
	m->esp += 4 + 0; return;	/* 4015cf: ret  */
L_4015d0:
	{ DWORD a_ = m->eax, b_ = 0xfeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4015d0: cmp eax, 0xfe */
	if (!m->zf) goto L_4015e5;	/* 4015d5: jne 0x4015e5 */
	m->ecx = M32((DWORD)(0x4ded7cu));	/* 4015d7: mov ecx, dword ptr [0x4ded7c] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4015dd: xor eax, eax */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4015df: test ecx, ecx */
	m->eax = (m->eax & ~(0xffu << 0)) | ((((!m->zf && m->sf == m->of) ? 1u : 0u) & 0xff) << 0);	/* 4015e1: setg al */
	m->esp += 4 + 0; return;	/* 4015e4: ret  */
L_4015e5:
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4015e5: push eax */
	m->esp -= 4; M32(m->esp) = 0x4015ebu; lift_401540(m);	/* 4015e6: call 0x401540 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4015eb: add esp, 4 */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 4015ee: neg eax */
	{ DWORD a_ = m->eax, b_ = m->eax, c0_ = (DWORD)m->cf; DWORD r_ = a_ - b_ - c0_; m->cf = (unsigned long long)a_ < (unsigned long long)b_ + c0_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1); FLAGS(r_, 32); m->eax = r_; }	/* 4015f0: sbb eax, eax */
	{ DWORD a_ = m->eax, r_ = (0u - a_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ != 0; m->of = r_ == (1u << 31); m->eax = r_; }	/* 4015f2: neg eax */
	m->esp += 4 + 0; return;	/* 4015f4: ret  */
}

/* sound_playMenu (0x41e760), lifted by tools/lift.py */
static void lift_41e760(X86 *m)
{
	{ DWORD a_ = M32((DWORD)(0xa0e80cu)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 41e760: cmp dword ptr [0xa0e80c], 1 */
	if (!m->zf) goto L_41e792;	/* 41e767: jne 0x41e792 */
	m->eax = M32((DWORD)(0x4dd984u));	/* 41e769: mov eax, dword ptr [0x4dd984] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 41e76e: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 41e76f: mov esi, dword ptr [esp + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 41e773: push eax */
	m->ecx = M32((DWORD)(m->esi*4 + 0x4dd4d4u));	/* 41e774: mov ecx, dword ptr [esi*4 + 0x4dd4d4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e77b: push ecx */
	m->esp -= 4; M32(m->esp) = 0x41e781u; native_call(m, 0x467db0u);	/* 41e77c: call 0x467db0 */
	m->edx = M32((DWORD)(m->esi*4 + 0x4dd4d4u));	/* 41e781: mov edx, dword ptr [esi*4 + 0x4dd4d4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 41e788: push edx */
	m->esp -= 4; M32(m->esp) = 0x41e78eu; native_call(m, 0x467d70u);	/* 41e789: call 0x467d70 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 41e78e: add esp, 0xc */
	m->esi = M32(m->esp); m->esp += 4;	/* 41e791: pop esi */
L_41e792:
	m->esp += 4 + 0; return;	/* 41e792: ret  */
}

/* skirmish_443c80 (0x443c80), lifted by tools/lift.py */
static void lift_443c80(X86 *m)
{
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 443c80: push 4 */
	M32((DWORD)(0x9ef1f0u)) = 0x0u;	/* 443c82: mov dword ptr [0x9ef1f0], 0 */
	M32((DWORD)(0x4e1870u)) = 0x3dcccccdu;	/* 443c8c: mov dword ptr [0x4e1870], 0x3dcccccd */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 443c96: mov dword ptr [0x4df028], 0 */
	M32((DWORD)(0x4df02cu)) = 0x44c80000u;	/* 443ca0: mov dword ptr [0x4df02c], 0x44c80000 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 443caa: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0x0u;	/* 443cb4: mov dword ptr [0x680380], 0 */
	m->esp -= 4; M32(m->esp) = 0x443cc3u; lift_41e760(m);	/* 443cbe: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 443cc3: add esp, 4 */
	native_call(m, 0x447910u); return;	/* 443cc6: jmp 0x447910 */
}

/* FUN_00447960 (0x447960), lifted by tools/lift.py */
static void lift_447960(X86 *m)
{
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 447960: push 4 */
	M32((DWORD)(0x9f62f8u)) = 0x0u;	/* 447962: mov dword ptr [0x9f62f8], 0 */
	M32((DWORD)(0x4e1870u)) = 0x3dcccccdu;	/* 44796c: mov dword ptr [0x4e1870], 0x3dcccccd */
	M32((DWORD)(0x4df028u)) = 0x0u;	/* 447976: mov dword ptr [0x4df028], 0 */
	M32((DWORD)(0x4df02cu)) = 0x44c80000u;	/* 447980: mov dword ptr [0x4df02c], 0x44c80000 */
	M32((DWORD)(0x68037cu)) = 0x0u;	/* 44798a: mov dword ptr [0x68037c], 0 */
	M32((DWORD)(0x680380u)) = 0x0u;	/* 447994: mov dword ptr [0x680380], 0 */
	m->esp -= 4; M32(m->esp) = 0x4479a3u; lift_41e760(m);	/* 44799e: call 0x41e760 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4479a3: add esp, 4 */
	native_call(m, 0x447910u); return;	/* 4479a6: jmp 0x447910 */
}

/* mission_4479b0 (0x4479b0), lifted by tools/lift.py */
static void lift_4479b0(X86 *m)
{
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 4479b0: mov eax, dword ptr [esp + 4] */
	{ DWORD v_ = 0x2u; m->esp -= 4; M32(m->esp) = v_; }	/* 4479b4: push 2 */
	M32((DWORD)(0x9f6328u)) = m->eax;	/* 4479b6: mov dword ptr [0x9f6328], eax */
	M32((DWORD)(0x9f63b0u)) = 0x1u;	/* 4479bb: mov dword ptr [0x9f63b0], 1 */
	m->esp -= 4; M32(m->esp) = 0x4479cau; lift_41e760(m);	/* 4479c5: call 0x41e760 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4479ca: pop ecx */
	m->esp += 4 + 0; return;	/* 4479cb: ret  */
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
