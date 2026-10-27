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

static void lift_469730(X86 *m);
static void lift_4955a0(X86 *m);

/* hud_4955a0 (0x4955a0), lifted by tools/lift.py */
static void lift_4955a0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4955a0: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4955a1: push edi */
	{ DWORD v_ = 0x3f000000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955a2: push 0x3f000000 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955a7: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955a9: push 0 */
	m->edi = m->ecx;	/* 4955ab: mov edi, ecx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955ad: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4955b5u; native_call(m, M32(0x4a9228u));	/* 4955af: call dword ptr [0x4a9228] */
	m->esp -= 4; M32(m->esp) = 0x4955bau; native_call(m, 0x4685c0u);	/* 4955b5: call 0x4685c0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4955ba: push eax */
	m->esp -= 4; M32(m->esp) = 0x4955c0u; native_call(m, 0x4685b0u);	/* 4955bb: call 0x4685b0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4955c0: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955c1: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955c3: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4955cau; native_call(m, 0x46bd60u);	/* 4955c5: call 0x46bd60 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955ca: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955cf: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955d4: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955d9: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4955e3u; native_call(m, 0x44ad30u);	/* 4955de: call 0x44ad30 */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4955e3: add esp, 0x20 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->esi = r_; }	/* 4955e6: xor esi, esi */
	{ DWORD a_ = m->edi, b_ = 0x234334bu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4955e8: add edi, 0x234334b */
L_4955ee:
	{ DWORD v_ = 0x8u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955ee: push 8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4955f0: push edi */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4955f1: push esi */
	{ DWORD v_ = 0xc0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4955f2: push 0xc0 */
	m->esp -= 4; M32(m->esp) = 0x4955fcu; native_call(m, 0x44ad60u);	/* 4955f7: call 0x44ad60 */
	{ DWORD a_ = m->esi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4955fc: add esi, 0x10 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4955ff: add esp, 0x10 */
	{ DWORD a_ = m->edi, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 495602: add edi, 0x40 */
	{ DWORD a_ = m->esi, b_ = 0x1e0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 495605: cmp esi, 0x1e0 */
	if (m->sf != m->of) goto L_4955ee;	/* 49560b: jl 0x4955ee */
	m->edi = M32(m->esp); m->esp += 4;	/* 49560d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 49560e: pop esi */
	m->esp += 4 + 0; return;	/* 49560f: ret  */
}

/* loading_drawCylinder (0x469730), lifted by tools/lift.py */
static void lift_469730(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 469730: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 469731: push edi */
	m->ecx = 0xa0e948u;	/* 469732: mov ecx, 0xa0e948 */
	m->esp -= 4; M32(m->esp) = 0x46973cu; { long double r_ = native_call_fp(m, 0x487490u); FPUSH(r_); }	/* 469737: call 0x487490 */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 46973c: mov eax, dword ptr [esp + 0xc] */
	{ DWORD a_ = m->eax, b_ = 0xfffffffeu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469740: cmp eax, -2 */
	if (m->zf) goto L_46986e;	/* 469743: je 0x46986e */
	{ DWORD a_ = m->eax, b_ = 0xffffffffu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469749: cmp eax, -1 */
	if (m->zf) goto L_46979e;	/* 46974c: je 0x46979e */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0ea88u)));	/* 46974e: fld dword ptr [0xa0ea88] */
	ST(0) = ST(0) + ST(1);	/* 469754: fadd st(1) */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 469756: cmp eax, 1 */
	MF((DWORD)(0xa0ea88u)) = (float)ST(0); FPOP();	/* 469759: fstp dword ptr [0xa0ea88] */
	ST(0) = ST(0); FPOP();	/* 46975f: fstp st(0) */
	if (!m->zf) goto L_469787;	/* 469761: jne 0x469787 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 469763: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469767: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46976a: xor eax, eax */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 46976c: repne scasb al, byte ptr es:[edi] */
	m->ecx = ~m->ecx;	/* 46976e: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 469770: sub edi, ecx */
	m->eax = m->ecx;	/* 469772: mov eax, ecx */
	m->esi = m->edi;	/* 469774: mov esi, edi */
	m->edi = 0xa0e988u;	/* 469776: mov edi, 0xa0e988 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46977b: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 46977e: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->eax;	/* 469780: mov ecx, eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469782: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 469785: rep movsb byte ptr es:[edi], byte ptr [esi] */
L_469787:
	m->ecx = M32((DWORD)(0xa0ea88u));	/* 469787: mov ecx, dword ptr [0xa0ea88] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46978d: push ecx */
	m->esp -= 4; M32(m->esp) = 0x469793u; native_call(m, 0x469320u);	/* 46978e: call 0x469320 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 469793: add esp, 4 */
	m->esp -= 4; M32(m->esp) = 0x46979bu; native_call(m, 0x4685d0u);	/* 469796: call 0x4685d0 */
	m->edi = M32(m->esp); m->esp += 4;	/* 46979b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46979c: pop esi */
	m->esp += 4 + 0; return;	/* 46979d: ret  */
L_46979e:
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 46979e: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4697a2: or ecx, 0xffffffff */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4697a5: xor eax, eax */
	M32((DWORD)(0xa0ea88u)) = 0x0u;	/* 4697a7: mov dword ptr [0xa0ea88], 0 */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 4697b1: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 4697b3: fstp st(0) */
	m->ecx = ~m->ecx;	/* 4697b5: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4697b7: sub edi, ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4697b9: push eax */
	m->edx = m->ecx;	/* 4697ba: mov edx, ecx */
	m->esi = m->edi;	/* 4697bc: mov esi, edi */
	m->edi = 0xa0e988u;	/* 4697be: mov edi, 0xa0e988 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4697c3: push eax */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 4697c4: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 4697c7: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 4697c9: mov ecx, edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4697cb: push eax */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4697cc: and ecx, 3 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4697cf: push eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4697d0: push eax */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4697d1: push eax */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4697d2: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->ecx = M32((DWORD)(0xa0e010u));	/* 4697d4: mov ecx, dword ptr [0xa0e010] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4697da: push eax */
	{ DWORD v_ = 0x4c533cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4697db: push 0x4c533c */
	m->esp -= 4; M32(m->esp) = 0x4697e5u; native_call(m, 0x456be0u);	/* 4697e0: call 0x456be0 */
	m->esi = M32((DWORD)(0x4a9228u));	/* 4697e5: mov esi, dword ptr [0x4a9228] */
	M32((DWORD)(0xa0e980u)) = m->eax;	/* 4697eb: mov dword ptr [0xa0e980], eax */
	M32((DWORD)(0xa0e984u)) = 0x0u;	/* 4697f0: mov dword ptr [0xa0e984], 0 */
L_4697fa:
	m->eax = M32((DWORD)(0xa0ea88u));	/* 4697fa: mov eax, dword ptr [0xa0ea88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4697ff: push eax */
	m->esp -= 4; M32(m->esp) = 0x469805u; native_call(m, 0x469320u);	/* 469800: call 0x469320 */
	FPUSH(x87_ldm((const float *)(DWORD)(0x4a9424u)));	/* 469805: fld dword ptr [0x4a9424] */
	ST(0) = x87_subm(ST(0), (const float *)(DWORD)(0xa0e984u));	/* 46980b: fsub dword ptr [0xa0e984] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 469811: fstp dword ptr [esp] */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 469814: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 469819: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46981e: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x469825u; native_call(m, m->esi);	/* 469823: call esi */
	m->esp -= 4; M32(m->esp) = 0x46982au; native_call(m, 0x4685c0u);	/* 469825: call 0x4685c0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46982a: push eax */
	m->esp -= 4; M32(m->esp) = 0x469830u; native_call(m, 0x4685b0u);	/* 46982b: call 0x4685b0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 469830: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 469831: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 469833: push 0 */
	m->esp -= 4; M32(m->esp) = 0x46983au; native_call(m, 0x46bd60u);	/* 469835: call 0x46bd60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46983a: add esp, 0x10 */
	m->ecx = 0xa0e948u;	/* 46983d: mov ecx, 0xa0e948 */
	m->esp -= 4; M32(m->esp) = 0x469847u; { long double r_ = native_call_fp(m, 0x487490u); FPUSH(r_); }	/* 469842: call 0x487490 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0xa0e984u));	/* 469847: fadd dword ptr [0xa0e984] */
	MF((DWORD)(0xa0e984u)) = (float)ST(0); FPOP();	/* 46984d: fstp dword ptr [0xa0e984] */
	m->esp -= 4; M32(m->esp) = 0x469858u; native_call(m, 0x4685d0u);	/* 469853: call 0x4685d0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e984u)));	/* 469858: fld dword ptr [0xa0e984] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 46985e: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 469864: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469866: test ah, 1 */
	if (!m->zf) goto L_4697fa;	/* 469869: jne 0x4697fa */
	m->edi = M32(m->esp); m->esp += 4;	/* 46986b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46986c: pop esi */
	m->esp += 4 + 0; return;	/* 46986d: ret  */
L_46986e:
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0ea88u)));	/* 46986e: fld dword ptr [0xa0ea88] */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 469874: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ecx, b_ = 0xffffffffu & 0xffffffffu, r_ = a_ | b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 469878: or ecx, 0xffffffff */
	ST(0) = ST(0) + ST(1);	/* 46987b: fadd st(1) */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46987d: xor eax, eax */
	MF((DWORD)(0xa0ea88u)) = (float)ST(0); FPOP();	/* 46987f: fstp dword ptr [0xa0ea88] */
	while (m->ecx) { { DWORD a_ = (m->eax & 0xffu), b_ = M8(m->edi), r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (int)((((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1); m->edi += 1; } m->ecx--; if (m->zf) break; }	/* 469885: repne scasb al, byte ptr es:[edi] */
	ST(0) = ST(0); FPOP();	/* 469887: fstp st(0) */
	m->ecx = ~m->ecx;	/* 469889: not ecx */
	{ DWORD a_ = m->edi, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 46988b: sub edi, ecx */
	m->edx = m->ecx;	/* 46988d: mov edx, ecx */
	m->esi = m->edi;	/* 46988f: mov esi, edi */
	m->edi = 0xa0e988u;	/* 469891: mov edi, 0xa0e988 */
	{ DWORD a_ = m->ecx, c_ = (0x2u) & 31; if (c_) { DWORD r_ = a_ >> c_; m->cf = (int)((a_ >> (c_ - 1)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 469896: shr ecx, 2 */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 469899: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = m->edx;	/* 46989b: mov ecx, edx */
	{ DWORD a_ = m->ecx, b_ = 0x3u & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 46989d: and ecx, 3 */
	while (m->ecx) { M8(m->edi) = M8(m->esi); m->esi += 1; m->edi += 1; m->ecx--; }	/* 4698a0: rep movsb byte ptr es:[edi], byte ptr [esi] */
	m->esi = M32((DWORD)(0x4a9228u));	/* 4698a2: mov esi, dword ptr [0x4a9228] */
	M32((DWORD)(0xa0e984u)) = m->eax;	/* 4698a8: mov dword ptr [0xa0e984], eax */
L_4698ad:
	m->eax = M32((DWORD)(0xa0ea88u));	/* 4698ad: mov eax, dword ptr [0xa0ea88] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4698b2: push eax */
	m->esp -= 4; M32(m->esp) = 0x4698b8u; native_call(m, 0x469320u);	/* 4698b3: call 0x469320 */
	m->ecx = M32((DWORD)(0xa0e984u));	/* 4698b8: mov ecx, dword ptr [0xa0e984] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4698be: add esp, 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4698c1: push ecx */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4698c2: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4698c7: push 0x3f800000 */
	{ DWORD v_ = 0x3f800000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4698cc: push 0x3f800000 */
	m->esp -= 4; M32(m->esp) = 0x4698d3u; native_call(m, m->esi);	/* 4698d1: call esi */
	m->esp -= 4; M32(m->esp) = 0x4698d8u; native_call(m, 0x4685c0u);	/* 4698d3: call 0x4685c0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4698d8: push eax */
	m->esp -= 4; M32(m->esp) = 0x4698deu; native_call(m, 0x4685b0u);	/* 4698d9: call 0x4685b0 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4698de: push eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4698df: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 4698e1: push 0 */
	m->esp -= 4; M32(m->esp) = 0x4698e8u; native_call(m, 0x46bd60u);	/* 4698e3: call 0x46bd60 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4698e8: add esp, 0x10 */
	m->ecx = 0xa0e948u;	/* 4698eb: mov ecx, 0xa0e948 */
	m->esp -= 4; M32(m->esp) = 0x4698f5u; { long double r_ = native_call_fp(m, 0x487490u); FPUSH(r_); }	/* 4698f0: call 0x487490 */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0xa0e984u));	/* 4698f5: fadd dword ptr [0xa0e984] */
	MF((DWORD)(0xa0e984u)) = (float)ST(0); FPOP();	/* 4698fb: fstp dword ptr [0xa0e984] */
	m->esp -= 4; M32(m->esp) = 0x469906u; native_call(m, 0x4685d0u);	/* 469901: call 0x4685d0 */
	FPUSH(x87_ldm((const float *)(DWORD)(0xa0e984u)));	/* 469906: fld dword ptr [0xa0e984] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a9424u)); FPOP();	/* 46990c: fcomp dword ptr [0x4a9424] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 469912: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x1u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 469914: test ah, 1 */
	if (!m->zf) goto L_4698ad;	/* 469917: jne 0x4698ad */
	m->edi = M32(m->esp); m->esp += 4;	/* 469919: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 46991a: pop esi */
	m->esp += 4 + 0; return;	/* 46991b: ret  */
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
