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

static void lift_46b140(X86 *m);
static void lift_455550(X86 *m);
static void lift_4816c0(X86 *m);
static void lift_4817f0(X86 *m);
static void lift_4815c0(X86 *m);
static void lift_4818e0(X86 *m);
static void lift_48b4a0(X86 *m);
static void lift_48b530(X86 *m);
static void lift_483dd0(X86 *m);
static void lift_483e90(X86 *m);
static void lift_483ec0(X86 *m);
static void lift_483f00(X86 *m);
static void lift_472310(X86 *m);
static void lift_43f8b0(X86 *m);
static void lift_452af0(X86 *m);
static void lift_452c80(X86 *m);
static void lift_46c340(X86 *m);
static void lift_46c270(X86 *m);
static void lift_4684c0(X86 *m);
static void lift_42bde0(X86 *m);
static void lift_403060(X86 *m);
static void lift_402420(X86 *m);
static void lift_402010(X86 *m);
static void lift_402210(X86 *m);
static void lift_401870(X86 *m);
static void lift_401aa0(X86 *m);
static void lift_401ce0(X86 *m);
static void lift_401e70(X86 *m);
static void lift_466d60(X86 *m);

/* shape_findDatEntry (0x466d60), lifted by tools/lift.py */
static void lift_466d60(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466d60: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 466d61: mov esi, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466d65: push esi */
	m->esp -= 4; M32(m->esp) = 0x466d6bu; native_call(m, 0x466ce0u);	/* 466d66: call 0x466ce0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466d6b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 466d6e: test eax, eax */
	if (m->sf != m->of) goto L_466d9c;	/* 466d70: jl 0x466d9c */
	m->edx = M32((DWORD)(0xa0e7a0u));	/* 466d72: mov edx, dword ptr [0xa0e7a0] */
	m->ecx = m->eax;	/* 466d78: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 466d7a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 466d7d: add ecx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 466d7f: push 0 */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0x40u));	/* 466d81: mov eax, dword ptr [edx + ecx*4 + 0x40] */
	m->ecx = M32((DWORD)(0xa0e7a4u));	/* 466d85: mov ecx, dword ptr [0xa0e7a4] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 466d8b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 466d8c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x466d92u; native_call(m, 0x49e91eu);	/* 466d8d: call 0x49e91e */
	m->eax = M32((DWORD)(0xa0e7a4u));	/* 466d92: mov eax, dword ptr [0xa0e7a4] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466d97: add esp, 0xc */
	m->esi = M32(m->esp); m->esp += 4;	/* 466d9a: pop esi */
	m->esp += 4 + 0; return;	/* 466d9b: ret  */
L_466d9c:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 466d9c: push esi */
	{ DWORD v_ = 0x4b3f80u; m->esp -= 4; M32(m->esp) = v_; }	/* 466d9d: push 0x4b3f80 */
	{ DWORD v_ = 0xa0e788u; m->esp -= 4; M32(m->esp) = v_; }	/* 466da2: push 0xa0e788 */
	m->esp -= 4; M32(m->esp) = 0x466dacu; native_call(m, 0x46c710u);	/* 466da7: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 466dac: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 466daf: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 466db1: pop esi */
	m->esp += 4 + 0; return;	/* 466db2: ret  */
}

/* skelDat_getItemFileBy (0x46b140), lifted by tools/lift.py */
static void lift_46b140(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46b140: push esi */
	m->esi = M32((DWORD)(m->esp + 0x8u));	/* 46b141: mov esi, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46b145: push esi */
	m->esp -= 4; M32(m->esp) = 0x46b14bu; native_call(m, 0x46b0c0u);	/* 46b146: call 0x46b0c0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b14b: add esp, 4 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46b14e: test eax, eax */
	if (m->sf != m->of) goto L_46b17c;	/* 46b150: jl 0x46b17c */
	m->edx = M32((DWORD)(0xa0eab8u));	/* 46b152: mov edx, dword ptr [0xa0eab8] */
	m->ecx = m->eax;	/* 46b158: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 46b15a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46b15d: add ecx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b15f: push 0 */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0x40u));	/* 46b161: mov eax, dword ptr [edx + ecx*4 + 0x40] */
	m->ecx = M32((DWORD)(0xa0eabcu));	/* 46b165: mov ecx, dword ptr [0xa0eabc] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 46b16b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46b16c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x46b172u; native_call(m, 0x49e91eu);	/* 46b16d: call 0x49e91e */
	m->eax = M32((DWORD)(0xa0eabcu));	/* 46b172: mov eax, dword ptr [0xa0eabc] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b177: add esp, 0xc */
	m->esi = M32(m->esp); m->esp += 4;	/* 46b17a: pop esi */
	m->esp += 4 + 0; return;	/* 46b17b: ret  */
L_46b17c:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46b17c: push esi */
	{ DWORD v_ = 0x4b3f80u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b17d: push 0x4b3f80 */
	{ DWORD v_ = 0xa0eaa0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46b182: push 0xa0eaa0 */
	m->esp -= 4; M32(m->esp) = 0x46b18cu; native_call(m, 0x46c710u);	/* 46b187: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46b18c: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46b18f: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 46b191: pop esi */
	m->esp += 4 + 0; return;	/* 46b192: ret  */
}

/* tex_getItemFileBy (0x455550), lifted by tools/lift.py */
static void lift_455550(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 455550: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 455551: push edi */
	m->edi = M32((DWORD)(m->esp + 0xcu));	/* 455552: mov edi, dword ptr [esp + 0xc] */
	m->esi = m->ecx;	/* 455556: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 455558: push edi */
	m->esp -= 4; M32(m->esp) = 0x45555eu; native_call(m, 0x4554c0u);	/* 455559: call 0x4554c0 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 45555e: test eax, eax */
	if (m->sf != m->of) goto L_455590;	/* 455560: jl 0x455590 */
	m->edx = M32((DWORD)(m->esi + 0x10cu));	/* 455562: mov edx, dword ptr [esi + 0x10c] */
	m->ecx = m->eax;	/* 455568: mov ecx, eax */
	{ DWORD a_ = m->ecx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ecx = r_; } }	/* 45556a: shl ecx, 4 */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 45556d: add ecx, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 45556f: push 0 */
	m->eax = M32((DWORD)(m->edx + m->ecx*4 + 0x40u));	/* 455571: mov eax, dword ptr [edx + ecx*4 + 0x40] */
	m->ecx = M32((DWORD)(m->esi + 0x110u));	/* 455575: mov ecx, dword ptr [esi + 0x110] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 45557b: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 45557c: push ecx */
	m->esp -= 4; M32(m->esp) = 0x455582u; native_call(m, 0x49e91eu);	/* 45557d: call 0x49e91e */
	m->eax = M32((DWORD)(m->esi + 0x110u));	/* 455582: mov eax, dword ptr [esi + 0x110] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 455588: add esp, 0xc */
	m->edi = M32(m->esp); m->esp += 4;	/* 45558b: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 45558c: pop esi */
	m->esp += 4 + 4; return;	/* 45558d: ret 4 */
L_455590:
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 455590: push edi */
	{ DWORD v_ = 0x4b3f80u; m->esp -= 4; M32(m->esp) = v_; }	/* 455591: push 0x4b3f80 */
	{ DWORD v_ = 0xa0dff8u; m->esp -= 4; M32(m->esp) = v_; }	/* 455596: push 0xa0dff8 */
	m->esp -= 4; M32(m->esp) = 0x4555a0u; native_call(m, 0x46c710u);	/* 45559b: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4555a0: add esp, 0xc */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 4555a3: xor eax, eax */
	m->edi = M32(m->esp); m->esp += 4;	/* 4555a5: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4555a6: pop esi */
	m->esp += 4 + 4; return;	/* 4555a7: ret 4 */
}

/* space_getNextFreeNodePtr (0x4816c0), lifted by tools/lift.py */
static void lift_4816c0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4816c0: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x28u));	/* 4816c1: mov esi, dword ptr [ecx + 0x28] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4816c4: xor edx, edx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4816c6: cmp esi, edx */
	if (m->zf) goto L_4816ee;	/* 4816c8: je 0x4816ee */
	m->eax = M32((DWORD)(m->esi + 0xcu));	/* 4816ca: mov eax, dword ptr [esi + 0xc] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4816cd: cmp eax, edx */
	if (m->zf) goto L_4816d9;	/* 4816cf: je 0x4816d9 */
	M32((DWORD)(m->ecx + 0x28u)) = m->eax;	/* 4816d1: mov dword ptr [ecx + 0x28], eax */
	M32((DWORD)(m->eax + 0x8u)) = m->edx;	/* 4816d4: mov dword ptr [eax + 8], edx */
	goto L_4816dc;	/* 4816d7: jmp 0x4816dc */
L_4816d9:
	M32((DWORD)(m->ecx + 0x28u)) = m->edx;	/* 4816d9: mov dword ptr [ecx + 0x28], edx */
L_4816dc:
	m->eax = M32((DWORD)(m->ecx + 0x2cu));	/* 4816dc: mov eax, dword ptr [ecx + 0x2c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4816df: inc eax */
	M32((DWORD)(m->ecx + 0x2cu)) = m->eax;	/* 4816e0: mov dword ptr [ecx + 0x2c], eax */
	m->ecx = m->esi;	/* 4816e3: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4816eau; native_call(m, 0x480430u);	/* 4816e5: call 0x480430 */
	m->eax = m->esi;	/* 4816ea: mov eax, esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4816ec: pop esi */
	m->esp += 4 + 0; return;	/* 4816ed: ret  */
L_4816ee:
	m->eax = M32((DWORD)(m->ecx + 0x40u));	/* 4816ee: mov eax, dword ptr [ecx + 0x40] */
	m->edx = M32((DWORD)(m->ecx + 0x4cu));	/* 4816f1: mov edx, dword ptr [ecx + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4816f4: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x30u));	/* 4816f5: mov eax, dword ptr [ecx + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4816f8: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x3cu));	/* 4816f9: mov edx, dword ptr [ecx + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4816fc: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x20u));	/* 4816fd: mov eax, dword ptr [ecx + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481700: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x2cu));	/* 481701: mov edx, dword ptr [ecx + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481704: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x10u));	/* 481705: mov eax, dword ptr [ecx + 0x10] */
	m->ecx = M32((DWORD)(m->ecx + 0x1cu));	/* 481708: mov ecx, dword ptr [ecx + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48170b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48170c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48170d: push ecx */
	{ DWORD v_ = 0x4c7874u; m->esp -= 4; M32(m->esp) = v_; }	/* 48170e: push 0x4c7874 */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481713: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x48171du; native_call(m, 0x46c710u);	/* 481718: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48171d: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481720: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 481722: pop esi */
	m->esp += 4 + 0; return;	/* 481723: ret  */
}

/* space_getNextFreeUnitPtr (0x4817f0), lifted by tools/lift.py */
static void lift_4817f0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4817f0: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x38u));	/* 4817f1: mov esi, dword ptr [ecx + 0x38] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4817f4: xor edx, edx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4817f6: cmp esi, edx */
	if (m->zf) goto L_48181e;	/* 4817f8: je 0x48181e */
	m->eax = M32((DWORD)(m->esi + 0x10u));	/* 4817fa: mov eax, dword ptr [esi + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4817fd: cmp eax, edx */
	if (m->zf) goto L_481809;	/* 4817ff: je 0x481809 */
	M32((DWORD)(m->ecx + 0x38u)) = m->eax;	/* 481801: mov dword ptr [ecx + 0x38], eax */
	M32((DWORD)(m->eax + 0xcu)) = m->edx;	/* 481804: mov dword ptr [eax + 0xc], edx */
	goto L_48180c;	/* 481807: jmp 0x48180c */
L_481809:
	M32((DWORD)(m->ecx + 0x38u)) = m->edx;	/* 481809: mov dword ptr [ecx + 0x38], edx */
L_48180c:
	m->eax = M32((DWORD)(m->ecx + 0x3cu));	/* 48180c: mov eax, dword ptr [ecx + 0x3c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 48180f: inc eax */
	M32((DWORD)(m->ecx + 0x3cu)) = m->eax;	/* 481810: mov dword ptr [ecx + 0x3c], eax */
	m->ecx = m->esi;	/* 481813: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48181au; native_call(m, 0x480440u);	/* 481815: call 0x480440 */
	m->eax = m->esi;	/* 48181a: mov eax, esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48181c: pop esi */
	m->esp += 4 + 0; return;	/* 48181d: ret  */
L_48181e:
	m->eax = M32((DWORD)(m->ecx + 0x40u));	/* 48181e: mov eax, dword ptr [ecx + 0x40] */
	m->edx = M32((DWORD)(m->ecx + 0x4cu));	/* 481821: mov edx, dword ptr [ecx + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481824: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x30u));	/* 481825: mov eax, dword ptr [ecx + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481828: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x3cu));	/* 481829: mov edx, dword ptr [ecx + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48182c: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x20u));	/* 48182d: mov eax, dword ptr [ecx + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481830: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x2cu));	/* 481831: mov edx, dword ptr [ecx + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481834: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x10u));	/* 481835: mov eax, dword ptr [ecx + 0x10] */
	m->ecx = M32((DWORD)(m->ecx + 0x1cu));	/* 481838: mov ecx, dword ptr [ecx + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48183b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48183c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48183d: push ecx */
	{ DWORD v_ = 0x4c78ccu; m->esp -= 4; M32(m->esp) = v_; }	/* 48183e: push 0x4c78cc */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481843: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x48184du; native_call(m, 0x46c710u);	/* 481848: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48184d: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481850: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 481852: pop esi */
	m->esp += 4 + 0; return;	/* 481853: ret  */
}

/* space_getNextFreePlanePtr (0x4815c0), lifted by tools/lift.py */
static void lift_4815c0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4815c0: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x18u));	/* 4815c1: mov esi, dword ptr [ecx + 0x18] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4815c4: xor edx, edx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4815c6: cmp esi, edx */
	if (m->zf) goto L_4815f4;	/* 4815c8: je 0x4815f4 */
	m->eax = M32((DWORD)(m->esi + 0xa4u));	/* 4815ca: mov eax, dword ptr [esi + 0xa4] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4815d0: cmp eax, edx */
	if (m->zf) goto L_4815df;	/* 4815d2: je 0x4815df */
	M32((DWORD)(m->ecx + 0x18u)) = m->eax;	/* 4815d4: mov dword ptr [ecx + 0x18], eax */
	M32((DWORD)(m->eax + 0xa0u)) = m->edx;	/* 4815d7: mov dword ptr [eax + 0xa0], edx */
	goto L_4815e2;	/* 4815dd: jmp 0x4815e2 */
L_4815df:
	M32((DWORD)(m->ecx + 0x18u)) = m->edx;	/* 4815df: mov dword ptr [ecx + 0x18], edx */
L_4815e2:
	m->eax = M32((DWORD)(m->ecx + 0x1cu));	/* 4815e2: mov eax, dword ptr [ecx + 0x1c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4815e5: inc eax */
	M32((DWORD)(m->ecx + 0x1cu)) = m->eax;	/* 4815e6: mov dword ptr [ecx + 0x1c], eax */
	m->ecx = m->esi;	/* 4815e9: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x4815f0u; native_call(m, 0x47db50u);	/* 4815eb: call 0x47db50 */
	m->eax = m->esi;	/* 4815f0: mov eax, esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4815f2: pop esi */
	m->esp += 4 + 0; return;	/* 4815f3: ret  */
L_4815f4:
	m->eax = M32((DWORD)(m->ecx + 0x40u));	/* 4815f4: mov eax, dword ptr [ecx + 0x40] */
	m->edx = M32((DWORD)(m->ecx + 0x4cu));	/* 4815f7: mov edx, dword ptr [ecx + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4815fa: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x30u));	/* 4815fb: mov eax, dword ptr [ecx + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4815fe: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x3cu));	/* 4815ff: mov edx, dword ptr [ecx + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481602: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x20u));	/* 481603: mov eax, dword ptr [ecx + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481606: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x2cu));	/* 481607: mov edx, dword ptr [ecx + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48160a: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x10u));	/* 48160b: mov eax, dword ptr [ecx + 0x10] */
	m->ecx = M32((DWORD)(m->ecx + 0x1cu));	/* 48160e: mov ecx, dword ptr [ecx + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481611: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481612: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 481613: push ecx */
	{ DWORD v_ = 0x4c7818u; m->esp -= 4; M32(m->esp) = v_; }	/* 481614: push 0x4c7818 */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481619: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x481623u; native_call(m, 0x46c710u);	/* 48161e: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 481623: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481626: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 481628: pop esi */
	m->esp += 4 + 0; return;	/* 481629: ret  */
}

/* space_getNextFreeBlockPtrBy (0x4818e0), lifted by tools/lift.py */
static void lift_4818e0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4818e0: push esi */
	m->esi = M32((DWORD)(m->ecx + 0x48u));	/* 4818e1: mov esi, dword ptr [ecx + 0x48] */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4818e4: xor edx, edx */
	{ DWORD a_ = m->esi, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4818e6: cmp esi, edx */
	if (m->zf) goto L_48193e;	/* 4818e8: je 0x48193e */
	m->eax = M32((DWORD)(m->esi + 0x4cu));	/* 4818ea: mov eax, dword ptr [esi + 0x4c] */
	{ DWORD a_ = m->eax, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4818ed: cmp eax, edx */
	if (m->zf) goto L_4818f9;	/* 4818ef: je 0x4818f9 */
	M32((DWORD)(m->ecx + 0x48u)) = m->eax;	/* 4818f1: mov dword ptr [ecx + 0x48], eax */
	M32((DWORD)(m->eax + 0x48u)) = m->edx;	/* 4818f4: mov dword ptr [eax + 0x48], edx */
	goto L_4818fc;	/* 4818f7: jmp 0x4818fc */
L_4818f9:
	M32((DWORD)(m->ecx + 0x48u)) = m->edx;	/* 4818f9: mov dword ptr [ecx + 0x48], edx */
L_4818fc:
	m->eax = M32((DWORD)(m->ecx + 0x4cu));	/* 4818fc: mov eax, dword ptr [ecx + 0x4c] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 4818ff: inc eax */
	M32((DWORD)(m->ecx + 0x4cu)) = m->eax;	/* 481900: mov dword ptr [ecx + 0x4c], eax */
	m->ecx = m->esi;	/* 481903: mov ecx, esi */
	m->esp -= 4; M32(m->esp) = 0x48190au; native_call(m, 0x4804a0u);	/* 481905: call 0x4804a0 */
	m->eax = M32((DWORD)(m->esp + 0x8u));	/* 48190a: mov eax, dword ptr [esp + 8] */
	m->ecx = m->esi;	/* 48190e: mov ecx, esi */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 481910: mov edx, dword ptr [eax] */
	M32((DWORD)(m->ecx + 0x0u)) = m->edx;	/* 481912: mov dword ptr [ecx], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 481914: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->edx;	/* 481917: mov dword ptr [ecx + 4], edx */
	m->edx = M32((DWORD)(m->esp + 0xcu));	/* 48191a: mov edx, dword ptr [esp + 0xc] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 48191e: mov eax, dword ptr [eax + 8] */
	M32((DWORD)(m->ecx + 0x8u)) = m->eax;	/* 481921: mov dword ptr [ecx + 8], eax */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 481924: mov eax, dword ptr [edx] */
	m->ecx = (DWORD)(m->esi + 0xcu);	/* 481926: lea ecx, [esi + 0xc] */
	M32((DWORD)(m->esi + 0xcu)) = m->eax;	/* 481929: mov dword ptr [esi + 0xc], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 48192c: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->ecx + 0x4u)) = m->eax;	/* 48192f: mov dword ptr [ecx + 4], eax */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 481932: mov edx, dword ptr [edx + 8] */
	m->eax = m->esi;	/* 481935: mov eax, esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 481937: pop esi */
	M32((DWORD)(m->ecx + 0x8u)) = m->edx;	/* 481938: mov dword ptr [ecx + 8], edx */
	m->esp += 4 + 8; return;	/* 48193b: ret 8 */
L_48193e:
	m->eax = M32((DWORD)(m->ecx + 0x40u));	/* 48193e: mov eax, dword ptr [ecx + 0x40] */
	m->edx = M32((DWORD)(m->ecx + 0x4cu));	/* 481941: mov edx, dword ptr [ecx + 0x4c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481944: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x30u));	/* 481945: mov eax, dword ptr [ecx + 0x30] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481948: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x3cu));	/* 481949: mov edx, dword ptr [ecx + 0x3c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48194c: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x20u));	/* 48194d: mov eax, dword ptr [ecx + 0x20] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 481950: push edx */
	m->edx = M32((DWORD)(m->ecx + 0x2cu));	/* 481951: mov edx, dword ptr [ecx + 0x2c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 481954: push eax */
	m->eax = M32((DWORD)(m->ecx + 0x10u));	/* 481955: mov eax, dword ptr [ecx + 0x10] */
	m->ecx = M32((DWORD)(m->ecx + 0x1cu));	/* 481958: mov ecx, dword ptr [ecx + 0x1c] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 48195b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48195c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48195d: push ecx */
	{ DWORD v_ = 0x4c7924u; m->esp -= 4; M32(m->esp) = v_; }	/* 48195e: push 0x4c7924 */
	{ DWORD v_ = 0xae2ed0u; m->esp -= 4; M32(m->esp) = v_; }	/* 481963: push 0xae2ed0 */
	m->esp -= 4; M32(m->esp) = 0x48196du; native_call(m, 0x46c710u);	/* 481968: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x28u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48196d: add esp, 0x28 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 481970: xor eax, eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 481972: pop esi */
	m->esp += 4 + 8; return;	/* 481973: ret 8 */
}

/* map_loadWayPointInfoFrom (0x48b4a0), lifted by tools/lift.py */
static void lift_48b4a0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4a0: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x8u));	/* 48b4a1: mov ebx, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4a5: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4a6: push edi */
	m->edi = m->ecx;	/* 48b4a7: mov edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4a9: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4aa: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4ac: push 4 */
	m->esi = (DWORD)(m->edi + 0xe3b034u);	/* 48b4ae: lea esi, [edi + 0xe3b034] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4b4: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b4bau; native_call(m, 0x46cbe0u);	/* 48b4b5: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 48b4ba: mov eax, dword ptr [esi] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4bc: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4bd: push eax */
	m->ecx = (DWORD)(m->edi + 0xe36214u);	/* 48b4be: lea ecx, [edi + 0xe36214] */
	{ DWORD v_ = 0x14u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4c4: push 0x14 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b4c6: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b4ccu; native_call(m, 0x46cbe0u);	/* 48b4c7: call 0x46cbe0 */
	m->ecx = M32((DWORD)(m->esi + 0x0u));	/* 48b4cc: mov ecx, dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b4ce: add esp, 0x20 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 48b4d1: xor eax, eax */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48b4d3: xor edx, edx */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b4d5: test ecx, ecx */
	if (m->zf || m->sf != m->of) goto L_48b4fe;	/* 48b4d7: jle 0x48b4fe */
	m->ecx = (DWORD)(m->edi + 0xe36220u);	/* 48b4d9: lea ecx, [edi + 0xe36220] */
L_48b4df:
	m->ebx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 48b4df: lea ebx, [eax + eax*2] */
	{ DWORD a_ = m->ecx, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48b4e2: add ecx, 0x14 */
	{ DWORD a_ = m->ebx, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->ebx = r_; } }	/* 48b4e5: shl ebx, 4 */
	m->ebx = (DWORD)(m->ebx + m->edi*1 + 0xdc0f10u);	/* 48b4e8: lea ebx, [ebx + edi + 0xdc0f10] */
	M32((DWORD)(m->ecx + 0xfffffff0u)) = m->ebx;	/* 48b4ef: mov dword ptr [ecx - 0x10], ebx */
	m->ebx = M32((DWORD)(m->ecx + 0xffffffecu));	/* 48b4f2: mov ebx, dword ptr [ecx - 0x14] */
	{ DWORD a_ = m->eax, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48b4f5: add eax, ebx */
	m->ebx = M32((DWORD)(m->esi + 0x0u));	/* 48b4f7: mov ebx, dword ptr [esi] */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 48b4f9: inc edx */
	{ DWORD a_ = m->edx, b_ = m->ebx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b4fa: cmp edx, ebx */
	if (m->sf != m->of) goto L_48b4df;	/* 48b4fc: jl 0x48b4df */
L_48b4fe:
	m->edi = M32((DWORD)(m->edi + 0xe36210u));	/* 48b4fe: mov edi, dword ptr [edi + 0xe36210] */
	{ DWORD a_ = m->eax, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b504: cmp eax, edi */
	if (m->zf) goto L_48b51c;	/* 48b506: je 0x48b51c */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b508: push edi */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b509: push eax */
	{ DWORD v_ = 0x4c7d24u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b50a: push 0x4c7d24 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b50f: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48b519u; native_call(m, 0x46c710u);	/* 48b514: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b519: add esp, 0x10 */
L_48b51c:
	m->edi = M32(m->esp); m->esp += 4;	/* 48b51c: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48b51d: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48b51e: pop ebx */
	m->esp += 4 + 4; return;	/* 48b51f: ret 4 */
}

/* map_loadTriggerInfoFrom (0x48b530), lifted by tools/lift.py */
static void lift_48b530(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b530: push ebx */
	m->ebx = M32((DWORD)(m->esp + 0x8u));	/* 48b531: mov ebx, dword ptr [esp + 8] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b535: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b536: push edi */
	m->edi = m->ecx;	/* 48b537: mov edi, ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b539: push ebx */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b53a: push 1 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b53c: push 4 */
	m->esi = (DWORD)(m->edi + 0xe3c938u);	/* 48b53e: lea esi, [edi + 0xe3c938] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b544: push esi */
	m->esp -= 4; M32(m->esp) = 0x48b54au; native_call(m, 0x46cbe0u);	/* 48b545: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 48b54a: mov eax, dword ptr [esi] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b54c: push ebx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 48b54d: push eax */
	m->ecx = (DWORD)(m->edi + 0xe3b038u);	/* 48b54e: lea ecx, [edi + 0xe3b038] */
	{ DWORD v_ = 0x1cu; m->esp -= 4; M32(m->esp) = v_; }	/* 48b554: push 0x1c */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b556: push ecx */
	m->esp -= 4; M32(m->esp) = 0x48b55cu; native_call(m, 0x46cbe0u);	/* 48b557: call 0x46cbe0 */
	m->eax = M32((DWORD)(m->esi + 0x0u));	/* 48b55c: mov eax, dword ptr [esi] */
	{ DWORD a_ = m->esp, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b55e: add esp, 0x20 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 48b561: xor ecx, ecx */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 48b563: xor edx, edx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 48b565: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_48b59a;	/* 48b567: jle 0x48b59a */
	m->eax = (DWORD)(m->edi + 0xe3b04cu);	/* 48b569: lea eax, [edi + 0xe3b04c] */
L_48b56f:
	FPUSH(x87_ldm((const float *)(DWORD)(m->eax + 0x0u)));	/* 48b56f: fld dword ptr [eax] */
	{ long double t = ST(0); FPUSH(t); }	/* 48b571: fld st(0) */
	ST(0) = ST(0) * ST(1);	/* 48b573: fmul st(1) */
	m->ebx = (DWORD)(m->ecx + m->ecx*4 + 0x38d885u);	/* 48b575: lea ebx, [ecx + ecx*4 + 0x38d885] */
	{ DWORD a_ = m->eax, b_ = 0x1cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 48b57c: add eax, 0x1c */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4a9708u));	/* 48b57f: fmul dword ptr [0x4a9708] */
	m->ebx = (DWORD)(m->edi + m->ebx*4 + 0x0u);	/* 48b585: lea ebx, [edi + ebx*4] */
	M32((DWORD)(m->eax + 0xffffffd4u)) = m->ebx;	/* 48b588: mov dword ptr [eax - 0x2c], ebx */
	m->ebx = M32((DWORD)(m->eax + 0xffffffd0u));	/* 48b58b: mov ebx, dword ptr [eax - 0x30] */
	{ DWORD a_ = m->ecx, b_ = m->ebx & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 48b58e: add ecx, ebx */
	{ DWORD a_ = m->edx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->edx = r_; }	/* 48b590: inc edx */
	MF((DWORD)(m->eax + 0xffffffe4u)) = (float)ST(0); FPOP();	/* 48b591: fstp dword ptr [eax - 0x1c] */
	{ DWORD a_ = m->edx, b_ = M32((DWORD)(m->esi + 0x0u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b594: cmp edx, dword ptr [esi] */
	ST(0) = ST(0); FPOP();	/* 48b596: fstp st(0) */
	if (m->sf != m->of) goto L_48b56f;	/* 48b598: jl 0x48b56f */
L_48b59a:
	m->edi = M32((DWORD)(m->edi + 0xe3b034u));	/* 48b59a: mov edi, dword ptr [edi + 0xe3b034] */
	{ DWORD a_ = m->ecx, b_ = m->edi & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 48b5a0: cmp ecx, edi */
	if (m->zf) goto L_48b5b8;	/* 48b5a2: je 0x48b5b8 */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5a4: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5a5: push ecx */
	{ DWORD v_ = 0x4c7d74u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5a6: push 0x4c7d74 */
	{ DWORD v_ = 0xae2eb8u; m->esp -= 4; M32(m->esp) = v_; }	/* 48b5ab: push 0xae2eb8 */
	m->esp -= 4; M32(m->esp) = 0x48b5b5u; native_call(m, 0x46c710u);	/* 48b5b0: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 48b5b5: add esp, 0x10 */
L_48b5b8:
	m->edi = M32(m->esp); m->esp += 4;	/* 48b5b8: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 48b5b9: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 48b5ba: pop ebx */
	m->esp += 4 + 4; return;	/* 48b5bb: ret 4 */
}

/* factor_addFactorBy (0x483dd0), lifted by tools/lift.py */
static void lift_483dd0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 483dd0: push ebx */
	m->ebx = m->ecx;	/* 483dd1: mov ebx, ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 483dd3: push esi */
	m->eax = M32((DWORD)(m->ebx + 0xb008u));	/* 483dd4: mov eax, dword ptr [ebx + 0xb008] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 483dda: push edi */
	{ DWORD a_ = m->eax, b_ = 0x400u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483ddb: cmp eax, 0x400 */
	if (m->sf != m->of) goto L_483df5;	/* 483de0: jl 0x483df5 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483de2: push eax */
	{ DWORD v_ = 0x4c7ae0u; m->esp -= 4; M32(m->esp) = v_; }	/* 483de3: push 0x4c7ae0 */
	{ DWORD v_ = 0xae2ee8u; m->esp -= 4; M32(m->esp) = v_; }	/* 483de8: push 0xae2ee8 */
	m->esp -= 4; M32(m->esp) = 0x483df2u; native_call(m, 0x46c710u);	/* 483ded: call 0x46c710 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483df2: add esp, 0xc */
L_483df5:
	m->eax = M32((DWORD)(m->ebx + 0xb004u));	/* 483df5: mov eax, dword ptr [ebx + 0xb004] */
	m->ecx = M32((DWORD)(m->ebx + 0xb008u));	/* 483dfb: mov ecx, dword ptr [ebx + 0xb008] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483e01: cmp ecx, eax */
	if (!m->zf) goto L_483e1a;	/* 483e03: jne 0x483e1a */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 483e05: inc eax */
	M32((DWORD)(m->ebx + 0xb004u)) = m->eax;	/* 483e06: mov dword ptr [ebx + 0xb004], eax */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 483e0c: lea ecx, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 483e0f: lea edx, [eax + ecx*2] */
	M32((DWORD)(m->ebx + m->edx*4 + 0x8u)) = 0x0u;	/* 483e12: mov dword ptr [ebx + edx*4 + 8], 0 */
L_483e1a:
	m->eax = M32((DWORD)(m->ebx + 0xb008u));	/* 483e1a: mov eax, dword ptr [ebx + 0xb008] */
	m->esi = M32((DWORD)(m->esp + 0x10u));	/* 483e20: mov esi, dword ptr [esp + 0x10] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 483e24: lea ecx, [eax + eax*4] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0x0u);	/* 483e27: lea edx, [eax + ecx*2] */
	m->ecx = 0xbu;	/* 483e2a: mov ecx, 0xb */
	m->eax = (DWORD)(m->ebx + m->edx*4 + 0x4u);	/* 483e2f: lea eax, [ebx + edx*4 + 4] */
	m->edi = m->eax;	/* 483e33: mov edi, eax */
	while (m->ecx) { M32(m->edi) = M32(m->esi); m->esi += 4; m->edi += 4; m->ecx--; }	/* 483e35: rep movsd dword ptr es:[edi], dword ptr [esi] */
	m->ecx = M32((DWORD)(m->ebx + 0xb008u));	/* 483e37: mov ecx, dword ptr [ebx + 0xb008] */
	m->edi = 0x1u;	/* 483e3d: mov edi, 1 */
	M32((DWORD)(m->eax + 0x0u)) = m->ecx;	/* 483e42: mov dword ptr [eax], ecx */
	M32((DWORD)(m->eax + 0x4u)) = m->edi;	/* 483e44: mov dword ptr [eax + 4], edi */
	m->ecx = M32((DWORD)(m->ebx + 0xb008u));	/* 483e47: mov ecx, dword ptr [ebx + 0xb008] */
	m->edx = M32((DWORD)(m->ebx + 0xb004u));	/* 483e4d: mov edx, dword ptr [ebx + 0xb004] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 483e53: inc ecx */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483e54: cmp ecx, edx */
	if (!m->zf && m->sf == m->of) goto L_483e81;	/* 483e56: jg 0x483e81 */
	m->esi = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 483e58: lea esi, [ecx + ecx*4] */
	m->esi = (DWORD)(m->ecx + m->esi*2 + 0x0u);	/* 483e5b: lea esi, [ecx + esi*2] */
	m->esi = (DWORD)(m->ebx + m->esi*4 + 0x8u);	/* 483e5e: lea esi, [ebx + esi*4 + 8] */
L_483e62:
	{ DWORD a_ = M32((DWORD)(m->esi + 0x0u)), b_ = 0x0u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483e62: cmp dword ptr [esi], 0 */
	if (m->zf) goto L_483e7b;	/* 483e65: je 0x483e7b */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 483e67: inc ecx */
	{ DWORD a_ = m->esi, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 483e68: add esi, 0x2c */
	{ DWORD a_ = m->ecx, b_ = m->edx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 483e6b: cmp ecx, edx */
	if (m->zf || m->sf != m->of) goto L_483e62;	/* 483e6d: jle 0x483e62 */
	M32((DWORD)(m->ebx + 0xb00cu)) = m->edi;	/* 483e6f: mov dword ptr [ebx + 0xb00c], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 483e75: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 483e76: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 483e77: pop ebx */
	m->esp += 4 + 4; return;	/* 483e78: ret 4 */
L_483e7b:
	M32((DWORD)(m->ebx + 0xb008u)) = m->ecx;	/* 483e7b: mov dword ptr [ebx + 0xb008], ecx */
L_483e81:
	M32((DWORD)(m->ebx + 0xb00cu)) = m->edi;	/* 483e81: mov dword ptr [ebx + 0xb00c], edi */
	m->edi = M32(m->esp); m->esp += 4;	/* 483e87: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 483e88: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 483e89: pop ebx */
	m->esp += 4 + 4; return;	/* 483e8a: ret 4 */
}

/* load_483e90 (0x483e90), lifted by tools/lift.py */
static void lift_483e90(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483e90: sub esp, 0x2c */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 483e93: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x8u)) = 0x0u;	/* 483e97: mov dword ptr [esp + 8], 0 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 483e9f: mov edx, dword ptr [eax] */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 483ea1: lea eax, [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483ea5: push eax */
	M32((DWORD)(m->esp + 0x10u)) = m->edx;	/* 483ea6: mov dword ptr [esp + 0x10], edx */
	m->esp -= 4; M32(m->esp) = 0x483eafu; lift_483dd0(m);	/* 483eaa: call 0x483dd0 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483eaf: add esp, 0x2c */
	m->esp += 4 + 4; return;	/* 483eb2: ret 4 */
}

/* load_483ec0 (0x483ec0), lifted by tools/lift.py */
static void lift_483ec0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483ec0: sub esp, 0x2c */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 483ec3: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x8u)) = 0x1u;	/* 483ec7: mov dword ptr [esp + 8], 1 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 483ecf: mov edx, dword ptr [eax] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 483ed1: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 483ed5: mov dword ptr [esp + 0xc], edx */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 483ed9: mov edx, dword ptr [eax] */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 483edb: mov dword ptr [esp + 0x1c], edx */
	m->edx = M32((DWORD)(m->eax + 0x4u));	/* 483edf: mov edx, dword ptr [eax + 4] */
	M32((DWORD)(m->esp + 0x20u)) = m->edx;	/* 483ee2: mov dword ptr [esp + 0x20], edx */
	m->edx = (DWORD)(m->esp + 0x0u);	/* 483ee6: lea edx, [esp] */
	m->eax = M32((DWORD)(m->eax + 0x8u));	/* 483eea: mov eax, dword ptr [eax + 8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 483eed: push edx */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 483eee: mov dword ptr [esp + 0x28], eax */
	m->esp -= 4; M32(m->esp) = 0x483ef7u; lift_483dd0(m);	/* 483ef2: call 0x483dd0 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483ef7: add esp, 0x2c */
	m->esp += 4 + 8; return;	/* 483efa: ret 8 */
}

/* match_483f00 (0x483f00), lifted by tools/lift.py */
static void lift_483f00(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483f00: sub esp, 0x2c */
	m->eax = M32((DWORD)(m->esp + 0x30u));	/* 483f03: mov eax, dword ptr [esp + 0x30] */
	M32((DWORD)(m->esp + 0x8u)) = 0x2u;	/* 483f07: mov dword ptr [esp + 8], 2 */
	m->edx = M32((DWORD)(m->eax + 0x0u));	/* 483f0f: mov edx, dword ptr [eax] */
	m->eax = M32((DWORD)(m->esp + 0x34u));	/* 483f11: mov eax, dword ptr [esp + 0x34] */
	M32((DWORD)(m->esp + 0xcu)) = m->edx;	/* 483f15: mov dword ptr [esp + 0xc], edx */
	m->edx = M32((DWORD)(m->esp + 0x38u));	/* 483f19: mov edx, dword ptr [esp + 0x38] */
	M32((DWORD)(m->esp + 0x28u)) = m->eax;	/* 483f1d: mov dword ptr [esp + 0x28], eax */
	m->eax = M32((DWORD)(m->edx + 0x0u));	/* 483f21: mov eax, dword ptr [edx] */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 483f23: mov dword ptr [esp + 0x10], eax */
	m->eax = M32((DWORD)(m->edx + 0x4u));	/* 483f27: mov eax, dword ptr [edx + 4] */
	M32((DWORD)(m->esp + 0x14u)) = m->eax;	/* 483f2a: mov dword ptr [esp + 0x14], eax */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 483f2e: lea eax, [esp] */
	m->edx = M32((DWORD)(m->edx + 0x8u));	/* 483f32: mov edx, dword ptr [edx + 8] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 483f35: push eax */
	M32((DWORD)(m->esp + 0x1cu)) = m->edx;	/* 483f36: mov dword ptr [esp + 0x1c], edx */
	m->esp -= 4; M32(m->esp) = 0x483f3fu; lift_483dd0(m);	/* 483f3a: call 0x483dd0 */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 483f3f: add esp, 0x2c */
	m->esp += 4 + 12; return;	/* 483f42: ret 0xc */
}

/* match_472310 (0x472310), lifted by tools/lift.py */
static void lift_472310(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472310: push ecx */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 472311: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 472312: push ebp */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 472313: push esi */
	m->esi = m->ecx;	/* 472314: mov esi, ecx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 472316: push edi */
	m->ebp = (DWORD)(m->esi + 0x9d8010u);	/* 472317: lea ebp, [esi + 0x9d8010] */
	M32((DWORD)(m->esi + 0x9d800cu)) = 0x1u;	/* 47231d: mov dword ptr [esi + 0x9d800c], 1 */
	m->ecx = m->ebp;	/* 472327: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x47232eu; native_call(m, 0x483d60u);	/* 472329: call 0x483d60 */
	m->eax = M32((DWORD)(m->esi + 0x202e8c8u));	/* 47232e: mov eax, dword ptr [esi + 0x202e8c8] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 472334: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472336: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_47237a;	/* 472338: jle 0x47237a */
	m->edi = (DWORD)(m->esi + 0x1cd94fcu);	/* 47233a: lea edi, [esi + 0x1cd94fc] */
L_472340:
	{ DWORD a_ = M32((DWORD)(m->edi + 0xffffffb4u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472340: cmp dword ptr [edi - 0x4c], 1 */
	if (!m->zf) goto L_472369;	/* 472344: jne 0x472369 */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x398u)));	/* 472346: fld dword ptr [edi + 0x398] */
	ST(0) = x87_addm(ST(0), (const float *)(DWORD)(0x4a9424u));	/* 47234c: fadd dword ptr [0x4a9424] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 472352: push edi */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 472353: push ecx */
	m->ecx = m->ebp;	/* 472354: mov ecx, ebp */
	ST(0) = x87_mulm(ST(0), (const float *)(DWORD)(0x4aa410u));	/* 472356: fmul dword ptr [0x4aa410] */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0); FPOP();	/* 47235c: fstp dword ptr [esp] */
	{ DWORD v_ = 0xa1f23cu; m->esp -= 4; M32(m->esp) = v_; }	/* 47235f: push 0xa1f23c */
	m->esp -= 4; M32(m->esp) = 0x472369u; lift_483f00(m);	/* 472364: call 0x483f00 */
L_472369:
	m->eax = M32((DWORD)(m->esi + 0x202e8c8u));	/* 472369: mov eax, dword ptr [esi + 0x202e8c8] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 47236f: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x8888u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 472370: add edi, 0x8888 */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472376: cmp ebx, eax */
	if (m->sf != m->of) goto L_472340;	/* 472378: jl 0x472340 */
L_47237a:
	m->eax = M32((DWORD)(m->esi + 0x20f2da0u));	/* 47237a: mov eax, dword ptr [esi + 0x20f2da0] */
	{ DWORD a_ = m->ebx, b_ = m->ebx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ebx = r_; }	/* 472380: xor ebx, ebx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 472382: test eax, eax */
	if (m->zf || m->sf != m->of) goto L_4723cd;	/* 472384: jle 0x4723cd */
	m->edi = (DWORD)(m->esi + 0x20a9a3cu);	/* 472386: lea edi, [esi + 0x20a9a3c] */
L_47238c:
	m->eax = M32((DWORD)(m->edi + 0xffffff88u));	/* 47238c: mov eax, dword ptr [edi - 0x78] */
	m->ecx = (DWORD)(m->edi + 0xffffff94u);	/* 47238f: lea ecx, [edi - 0x6c] */
	{ DWORD a_ = m->eax, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 472392: cmp eax, 1 */
	if (!m->zf) goto L_4723bc;	/* 472395: jne 0x4723bc */
	FPUSH(x87_ldm((const float *)(DWORD)(m->edi + 0x0u)));	/* 472397: fld dword ptr [edi] */
	MF((DWORD)(m->esp + 0x10u)) = (float)ST(0);	/* 472399: fst dword ptr [esp + 0x10] */
	FCOM(ST(0), (long double)*(const float *)(DWORD)(0x4a93e8u)); FPOP();	/* 47239d: fcomp dword ptr [0x4a93e8] */
	m->eax = (m->eax & 0xffff0000u) | m->fsw;	/* 4723a3: fnstsw ax */
	{ DWORD a_ = ((m->eax >> 8) & 0xff), b_ = 0x41u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4723a5: test ah, 0x41 */
	if (!m->zf) goto L_4723bc;	/* 4723a8: jne 0x4723bc */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4723aa: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4723ae: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4723af: push eax */
	{ DWORD v_ = 0xa1f23cu; m->esp -= 4; M32(m->esp) = v_; }	/* 4723b0: push 0xa1f23c */
	m->ecx = m->ebp;	/* 4723b5: mov ecx, ebp */
	m->esp -= 4; M32(m->esp) = 0x4723bcu; lift_483f00(m);	/* 4723b7: call 0x483f00 */
L_4723bc:
	m->eax = M32((DWORD)(m->esi + 0x20f2da0u));	/* 4723bc: mov eax, dword ptr [esi + 0x20f2da0] */
	{ DWORD a_ = m->ebx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ebx = r_; }	/* 4723c2: inc ebx */
	{ DWORD a_ = m->edi, b_ = 0x12cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4723c3: add edi, 0x12c */
	{ DWORD a_ = m->ebx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4723c9: cmp ebx, eax */
	if (m->sf != m->of) goto L_47238c;	/* 4723cb: jl 0x47238c */
L_4723cd:
	m->edi = M32(m->esp); m->esp += 4;	/* 4723cd: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4723ce: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4723cf: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4723d0: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4723d1: pop ecx */
	m->esp += 4 + 0; return;	/* 4723d2: ret  */
}

/* app_deleteDataFiles (0x43f8b0), lifted by tools/lift.py */
static void lift_43f8b0(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8b0: push ecx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8b1: push esi */
	{ DWORD v_ = 0x4b29e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8b2: push 0x4b29e8 */
	{ DWORD v_ = 0x4b03c4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8b7: push 0x4b03c4 */
	m->esp -= 4; M32(m->esp) = 0x43f8c1u; native_call(m, 0x49e9cau);	/* 43f8bc: call 0x49e9ca */
	m->esi = m->eax;	/* 43f8c1: mov esi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8c3: push 0 */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8c5: push 0x7d0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8ca: push esi */
	m->esp -= 4; M32(m->esp) = 0x43f8d0u; native_call(m, 0x49e91eu);	/* 43f8cb: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8d0: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8d1: push 1 */
	m->eax = (DWORD)(m->esp + 0x20u);	/* 43f8d3: lea eax, [esp + 0x20] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8d7: push 4 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8d9: push eax */
	M32((DWORD)(m->esp + 0x28u)) = 0xa1a2a3a4u;	/* 43f8da: mov dword ptr [esp + 0x28], 0xa1a2a3a4 */
	m->esp -= 4; M32(m->esp) = 0x43f8e7u; native_call(m, 0x49f58au);	/* 43f8e2: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8e7: push esi */
	m->esp -= 4; M32(m->esp) = 0x43f8edu; native_call(m, 0x49e7e0u);	/* 43f8e8: call 0x49e7e0 */
	{ DWORD v_ = 0x4b29e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8ed: push 0x4b29e8 */
	{ DWORD v_ = 0x4b03dcu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8f2: push 0x4b03dc */
	m->esp -= 4; M32(m->esp) = 0x43f8fcu; native_call(m, 0x49e9cau);	/* 43f8f7: call 0x49e9ca */
	m->esi = m->eax;	/* 43f8fc: mov esi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f8fe: push 0 */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f900: push 0x7d0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f905: push esi */
	m->esp -= 4; M32(m->esp) = 0x43f90bu; native_call(m, 0x49e91eu);	/* 43f906: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f90b: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f90c: push 1 */
	m->ecx = (DWORD)(m->esp + 0x48u);	/* 43f90e: lea ecx, [esp + 0x48] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f912: push 4 */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f914: push ecx */
	M32((DWORD)(m->esp + 0x50u)) = 0xb1b2b3b4u;	/* 43f915: mov dword ptr [esp + 0x50], 0xb1b2b3b4 */
	m->esp -= 4; M32(m->esp) = 0x43f922u; native_call(m, 0x49f58au);	/* 43f91d: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x4cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f922: add esp, 0x4c */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f925: push esi */
	m->esp -= 4; M32(m->esp) = 0x43f92bu; native_call(m, 0x49e7e0u);	/* 43f926: call 0x49e7e0 */
	{ DWORD v_ = 0x4b29e8u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f92b: push 0x4b29e8 */
	{ DWORD v_ = 0x4b03f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f930: push 0x4b03f4 */
	m->esp -= 4; M32(m->esp) = 0x43f93au; native_call(m, 0x49e9cau);	/* 43f935: call 0x49e9ca */
	m->esi = m->eax;	/* 43f93a: mov esi, eax */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f93c: push 0 */
	{ DWORD v_ = 0x7d0u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f93e: push 0x7d0 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f943: push esi */
	m->esp -= 4; M32(m->esp) = 0x43f949u; native_call(m, 0x49e91eu);	/* 43f944: call 0x49e91e */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f949: push esi */
	{ DWORD v_ = 0x1u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f94a: push 1 */
	m->edx = (DWORD)(m->esp + 0x24u);	/* 43f94c: lea edx, [esp + 0x24] */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f950: push 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 43f952: push edx */
	M32((DWORD)(m->esp + 0x2cu)) = 0xc1c2c3c4u;	/* 43f953: mov dword ptr [esp + 0x2c], 0xc1c2c3c4 */
	m->esp -= 4; M32(m->esp) = 0x43f960u; native_call(m, 0x49f58au);	/* 43f95b: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 43f960: push esi */
	m->esp -= 4; M32(m->esp) = 0x43f966u; native_call(m, 0x49e7e0u);	/* 43f961: call 0x49e7e0 */
	m->esi = M32((DWORD)(0x4a9104u));	/* 43f966: mov esi, dword ptr [0x4a9104] */
	{ DWORD a_ = m->esp, b_ = 0x2cu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 43f96c: add esp, 0x2c */
	{ DWORD v_ = 0x4b040cu; m->esp -= 4; M32(m->esp) = v_; }	/* 43f96f: push 0x4b040c */
	m->esp -= 4; M32(m->esp) = 0x43f976u; native_call(m, m->esi);	/* 43f974: call esi */
	{ DWORD v_ = 0x4b0420u; m->esp -= 4; M32(m->esp) = v_; }	/* 43f976: push 0x4b0420 */
	m->esp -= 4; M32(m->esp) = 0x43f97du; native_call(m, m->esi);	/* 43f97b: call esi */
	m->esi = M32(m->esp); m->esp += 4;	/* 43f97d: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 43f97e: pop ecx */
	m->esp += 4 + 0; return;	/* 43f97f: ret  */
}

/* net_452af0 (0x452af0), lifted by tools/lift.py */
static void lift_452af0(X86 *m)
{
	m->eax = M32((DWORD)(0xa0b368u));	/* 452af0: mov eax, dword ptr [0xa0b368] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452af5: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452af6: push esi */
	m->esi = M32((DWORD)(m->esp + 0xcu));	/* 452af7: mov esi, dword ptr [esp + 0xc] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 452afb: lea ecx, [eax + eax*4] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 452afe: push edi */
	m->edi = M32((DWORD)(0x4a911cu));	/* 452aff: mov edi, dword ptr [0x4a911c] */
	m->ebx = (DWORD)(m->esi + 0x33u);	/* 452b05: lea ebx, [esi + 0x33] */
	m->ecx = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 452b08: lea ecx, [ecx + ecx*8] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452b0b: push ebx */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0xa0577bu);	/* 452b0c: lea edx, [eax + ecx*2 + 0xa0577b] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452b13: push edx */
	m->esp -= 4; M32(m->esp) = 0x452b16u; native_call(m, m->edi);	/* 452b14: call edi */
	m->eax = (DWORD)(m->esi + 0x1u);	/* 452b16: lea eax, [esi + 1] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452b19: push eax */
	m->eax = M32((DWORD)(0xa0b368u));	/* 452b1a: mov eax, dword ptr [0xa0b368] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 452b1f: lea ecx, [eax + eax*4] */
	m->ecx = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 452b22: lea ecx, [ecx + ecx*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0xa05749u);	/* 452b25: lea edx, [eax + ecx*2 + 0xa05749] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452b2c: push edx */
	m->esp -= 4; M32(m->esp) = 0x452b2fu; native_call(m, m->edi);	/* 452b2d: call edi */
	m->eax = (DWORD)(m->esi + 0x53u);	/* 452b2f: lea eax, [esi + 0x53] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452b32: push eax */
	m->eax = M32((DWORD)(0xa0b368u));	/* 452b33: mov eax, dword ptr [0xa0b368] */
	m->ecx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 452b38: lea ecx, [eax + eax*4] */
	m->ecx = (DWORD)(m->ecx + m->ecx*8 + 0x0u);	/* 452b3b: lea ecx, [ecx + ecx*8] */
	m->edx = (DWORD)(m->eax + m->ecx*2 + 0xa0579bu);	/* 452b3e: lea edx, [eax + ecx*2 + 0xa0579b] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452b45: push edx */
	m->esp -= 4; M32(m->esp) = 0x452b48u; native_call(m, m->edi);	/* 452b46: call edi */
	m->eax = M32((DWORD)(0xa0b368u));	/* 452b48: mov eax, dword ptr [0xa0b368] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452b4d: push ebx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 452b4e: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*4 + 0xa0bf20u);	/* 452b51: lea ecx, [eax*4 + 0xa0bf20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452b58: push ecx */
	m->esp -= 4; M32(m->esp) = 0x452b5bu; native_call(m, m->edi);	/* 452b59: call edi */
	m->ecx = M32((DWORD)(0xa0b368u));	/* 452b5b: mov ecx, dword ptr [0xa0b368] */
	m->edi = M32(m->esp); m->esp += 4;	/* 452b61: pop edi */
	m->eax = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 452b62: lea eax, [ecx + ecx*4] */
	m->edx = (DWORD)(m->eax + m->eax*8 + 0x0u);	/* 452b65: lea edx, [eax + eax*8] */
	m->eax = (DWORD)(m->ecx + m->edx*2 + 0x0u);	/* 452b68: lea eax, [ecx + edx*2] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 452b6b: mov dl, byte ptr [esi] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 452b6d: inc ecx */
	M8((DWORD)(m->eax + 0xa05748u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452b6e: mov byte ptr [eax + 0xa05748], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x49u))) & 0xff) << 0);	/* 452b74: mov dl, byte ptr [esi + 0x49] */
	M8((DWORD)(m->eax + 0xa05791u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452b77: mov byte ptr [eax + 0xa05791], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x47u))) & 0xff) << 0);	/* 452b7d: mov dl, byte ptr [esi + 0x47] */
	M8((DWORD)(m->eax + 0xa0578fu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452b80: mov byte ptr [eax + 0xa0578f], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x48u))) & 0xff) << 0);	/* 452b86: mov dl, byte ptr [esi + 0x48] */
	M8((DWORD)(m->eax + 0xa05790u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452b89: mov byte ptr [eax + 0xa05790], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x46u))) & 0xff) << 0);	/* 452b8f: mov dl, byte ptr [esi + 0x46] */
	M8((DWORD)(m->eax + 0xa0578eu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452b92: mov byte ptr [eax + 0xa0578e], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x45u))) & 0xff) << 0);	/* 452b98: mov dl, byte ptr [esi + 0x45] */
	M8((DWORD)(m->eax + 0xa0578du)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452b9b: mov byte ptr [eax + 0xa0578d], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x43u))) & 0xff) << 0);	/* 452ba1: mov dl, byte ptr [esi + 0x43] */
	M8((DWORD)(m->eax + 0xa0578bu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452ba4: mov byte ptr [eax + 0xa0578b], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x44u))) & 0xff) << 0);	/* 452baa: mov dl, byte ptr [esi + 0x44] */
	M8((DWORD)(m->eax + 0xa0578cu)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452bad: mov byte ptr [eax + 0xa0578c], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x52u))) & 0xff) << 0);	/* 452bb3: mov dl, byte ptr [esi + 0x52] */
	m->esi = M32(m->esp); m->esp += 4;	/* 452bb6: pop esi */
	M8((DWORD)(m->eax + 0xa0579au)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452bb7: mov byte ptr [eax + 0xa0579a], dl */
	M32((DWORD)(0xa0b368u)) = m->ecx;	/* 452bbd: mov dword ptr [0xa0b368], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452bc3: pop ebx */
	m->esp += 4 + 0; return;	/* 452bc4: ret  */
}

/* net_452c80 (0x452c80), lifted by tools/lift.py */
static void lift_452c80(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452c80: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 452c81: push esi */
	m->esi = M32((DWORD)(m->esp + 0xcu));	/* 452c82: mov esi, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 452c86: push edi */
	m->edi = M32((DWORD)(0x4a911cu));	/* 452c87: mov edi, dword ptr [0x4a911c] */
	m->eax = (DWORD)(m->esi + 0x43u);	/* 452c8d: lea eax, [esi + 0x43] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452c90: push eax */
	m->eax = M32((DWORD)(0xa0b358u));	/* 452c91: mov eax, dword ptr [0xa0b358] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 452c96: lea ecx, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 452c99: lea ecx, [ecx + ecx*4] */
	m->edx = (DWORD)(m->eax + m->ecx*8 + 0x9fd9a3u);	/* 452c9c: lea edx, [eax + ecx*8 + 0x9fd9a3] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452ca3: push edx */
	m->esp -= 4; M32(m->esp) = 0x452ca6u; native_call(m, m->edi);	/* 452ca4: call edi */
	m->eax = M32((DWORD)(0xa0b358u));	/* 452ca6: mov eax, dword ptr [0xa0b358] */
	m->ebx = (DWORD)(m->esi + 0x33u);	/* 452cab: lea ebx, [esi + 0x33] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452cae: push ebx */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 452caf: lea ecx, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 452cb2: lea ecx, [ecx + ecx*4] */
	m->edx = (DWORD)(m->eax + m->ecx*8 + 0x9fd993u);	/* 452cb5: lea edx, [eax + ecx*8 + 0x9fd993] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452cbc: push edx */
	m->esp -= 4; M32(m->esp) = 0x452cbfu; native_call(m, m->edi);	/* 452cbd: call edi */
	m->eax = (DWORD)(m->esi + 0x1u);	/* 452cbf: lea eax, [esi + 1] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452cc2: push eax */
	m->eax = M32((DWORD)(0xa0b358u));	/* 452cc3: mov eax, dword ptr [0xa0b358] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 452cc8: lea ecx, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 452ccb: lea ecx, [ecx + ecx*4] */
	m->edx = (DWORD)(m->eax + m->ecx*8 + 0x9fd961u);	/* 452cce: lea edx, [eax + ecx*8 + 0x9fd961] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452cd5: push edx */
	m->esp -= 4; M32(m->esp) = 0x452cd8u; native_call(m, m->edi);	/* 452cd6: call edi */
	m->eax = (DWORD)(m->esi + 0x71u);	/* 452cd8: lea eax, [esi + 0x71] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 452cdb: push eax */
	m->eax = M32((DWORD)(0xa0b358u));	/* 452cdc: mov eax, dword ptr [0xa0b358] */
	m->ecx = (DWORD)(m->eax + m->eax*2 + 0x0u);	/* 452ce1: lea ecx, [eax + eax*2] */
	m->ecx = (DWORD)(m->ecx + m->ecx*4 + 0x0u);	/* 452ce4: lea ecx, [ecx + ecx*4] */
	m->edx = (DWORD)(m->eax + m->ecx*8 + 0x9fd9d1u);	/* 452ce7: lea edx, [eax + ecx*8 + 0x9fd9d1] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 452cee: push edx */
	m->esp -= 4; M32(m->esp) = 0x452cf1u; native_call(m, m->edi);	/* 452cef: call edi */
	m->eax = M32((DWORD)(0xa0b358u));	/* 452cf1: mov eax, dword ptr [0xa0b358] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 452cf6: push ebx */
	m->eax = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 452cf7: lea eax, [eax + eax*4] */
	m->ecx = (DWORD)(m->eax*4 + 0xa0bf20u);	/* 452cfa: lea ecx, [eax*4 + 0xa0bf20] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 452d01: push ecx */
	m->esp -= 4; M32(m->esp) = 0x452d04u; native_call(m, m->edi);	/* 452d02: call edi */
	m->ecx = M32((DWORD)(0xa0b358u));	/* 452d04: mov ecx, dword ptr [0xa0b358] */
	m->edi = M32(m->esp); m->esp += 4;	/* 452d0a: pop edi */
	m->eax = (DWORD)(m->ecx + m->ecx*2 + 0x0u);	/* 452d0b: lea eax, [ecx + ecx*2] */
	m->edx = (DWORD)(m->eax + m->eax*4 + 0x0u);	/* 452d0e: lea edx, [eax + eax*4] */
	m->eax = (DWORD)(m->ecx + m->edx*8 + 0x0u);	/* 452d11: lea eax, [ecx + edx*8] */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 452d14: mov dl, byte ptr [esi] */
	{ DWORD a_ = m->ecx, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->ecx = r_; }	/* 452d16: inc ecx */
	M8((DWORD)(m->eax + 0x9fd960u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d17: mov byte ptr [eax + 0x9fd960], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x67u))) & 0xff) << 0);	/* 452d1d: mov dl, byte ptr [esi + 0x67] */
	M8((DWORD)(m->eax + 0x9fd9c7u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d20: mov byte ptr [eax + 0x9fd9c7], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x65u))) & 0xff) << 0);	/* 452d26: mov dl, byte ptr [esi + 0x65] */
	M8((DWORD)(m->eax + 0x9fd9c5u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d29: mov byte ptr [eax + 0x9fd9c5], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x64u))) & 0xff) << 0);	/* 452d2f: mov dl, byte ptr [esi + 0x64] */
	M8((DWORD)(m->eax + 0x9fd9c4u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d32: mov byte ptr [eax + 0x9fd9c4], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x63u))) & 0xff) << 0);	/* 452d38: mov dl, byte ptr [esi + 0x63] */
	M8((DWORD)(m->eax + 0x9fd9c3u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d3b: mov byte ptr [eax + 0x9fd9c3], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x61u))) & 0xff) << 0);	/* 452d41: mov dl, byte ptr [esi + 0x61] */
	M8((DWORD)(m->eax + 0x9fd9c1u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d44: mov byte ptr [eax + 0x9fd9c1], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x62u))) & 0xff) << 0);	/* 452d4a: mov dl, byte ptr [esi + 0x62] */
	M8((DWORD)(m->eax + 0x9fd9c2u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d4d: mov byte ptr [eax + 0x9fd9c2], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x66u))) & 0xff) << 0);	/* 452d53: mov dl, byte ptr [esi + 0x66] */
	M8((DWORD)(m->eax + 0x9fd9c6u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d56: mov byte ptr [eax + 0x9fd9c6], dl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x70u))) & 0xff) << 0);	/* 452d5c: mov dl, byte ptr [esi + 0x70] */
	m->esi = M32(m->esp); m->esp += 4;	/* 452d5f: pop esi */
	M8((DWORD)(m->eax + 0x9fd9d0u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 452d60: mov byte ptr [eax + 0x9fd9d0], dl */
	M32((DWORD)(0xa0b358u)) = m->ecx;	/* 452d66: mov dword ptr [0xa0b358], ecx */
	m->ebx = M32(m->esp); m->esp += 4;	/* 452d6c: pop ebx */
	m->esp += 4 + 0; return;	/* 452d6d: ret  */
}

/* math_makeMathFunctionTableFile (0x46c340), lifted by tools/lift.py */
static void lift_46c340(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c340: push ecx */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 46c341: xor eax, eax */
	M32((DWORD)(m->esp + 0x0u)) = m->eax;	/* 46c343: mov dword ptr [esp], eax */
L_46c347:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x0u)));	/* 46c347: fild dword ptr [esp] */
	{ DWORD a_ = m->eax, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->eax = r_; }	/* 46c34b: inc eax */
	{ DWORD a_ = m->eax, b_ = 0xe10u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c34c: cmp eax, 0xe10 */
	ST(0) = ST(0) * (long double)*(const double *)(DWORD)(0x4aa298u);	/* 46c351: fmul qword ptr [0x4aa298] */
	{ long double t = ST(0); FPUSH(t); }	/* 46c357: fld st(0) */
	{ long double t_ = ST(0); __asm__("fsin" : "+t"(t_)); ST(0) = t_; }	/* 46c359: fsin  */
	MF((DWORD)(m->esp + 0x0u)) = (float)ST(0);	/* 46c35b: fst dword ptr [esp] */
	MF((DWORD)(m->eax*4 + 0xa1b774u)) = (float)ST(0); FPOP();	/* 46c35f: fstp dword ptr [eax*4 + 0xa1b774] */
	{ long double t_ = ST(0); __asm__("fcos" : "+t"(t_)); ST(0) = t_; }	/* 46c366: fcos  */
	MF((DWORD)(m->eax*4 + 0xa17f34u)) = (float)ST(0);	/* 46c368: fst dword ptr [eax*4 + 0xa17f34] */
	FPUSH(x87_ldm((const float *)(DWORD)(m->esp + 0x0u)));	/* 46c36f: fld dword ptr [esp] */
	ST(0) = ST(0) / ST(1);	/* 46c373: fdiv st(1) */
	M32((DWORD)(m->esp + 0x0u)) = m->eax;	/* 46c375: mov dword ptr [esp], eax */
	MF((DWORD)(m->eax*4 + 0xa146f4u)) = (float)ST(0); FPOP();	/* 46c379: fstp dword ptr [eax*4 + 0xa146f4] */
	ST(0) = ST(0); FPOP();	/* 46c380: fstp st(0) */
	if (m->sf != m->of) goto L_46c347;	/* 46c382: jl 0x46c347 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c384: push esi */
	m->esi = 0xa106f8u;	/* 46c385: mov esi, 0xa106f8 */
L_46c38a:
	m->esp -= 4; M32(m->esp) = 0x46c38fu; native_call(m, 0x49f92cu);	/* 46c38a: call 0x49f92c */
	M32((DWORD)(m->esi + 0x0u)) = m->eax;	/* 46c38f: mov dword ptr [esi], eax */
	{ DWORD a_ = m->esi, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 46c391: add esi, 4 */
	{ DWORD a_ = m->esi, b_ = 0xa146f8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c394: cmp esi, 0xa146f8 */
	if (m->sf != m->of) goto L_46c38a;	/* 46c39a: jl 0x46c38a */
	{ DWORD v_ = 0x4b2ab0u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c39c: push 0x4b2ab0 */
	{ DWORD v_ = 0x4c575cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3a1: push 0x4c575c */
	m->esp -= 4; M32(m->esp) = 0x46c3abu; native_call(m, 0x49e9cau);	/* 46c3a6: call 0x49e9ca */
	m->esi = m->eax;	/* 46c3ab: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c3ad: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46c3b0: test esi, esi */
	if (!m->zf) goto L_46c3c1;	/* 46c3b2: jne 0x46c3c1 */
	{ DWORD v_ = 0x4c576cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3b4: push 0x4c576c */
	m->esp -= 4; M32(m->esp) = 0x46c3beu; native_call(m, 0x46c950u);	/* 46c3b9: call 0x46c950 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c3be: add esp, 4 */
L_46c3c1:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3c1: push esi */
	{ DWORD v_ = 0xe10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3c2: push 0xe10 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3c7: push 4 */
	{ DWORD v_ = 0xa1b778u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3c9: push 0xa1b778 */
	m->esp -= 4; M32(m->esp) = 0x46c3d3u; native_call(m, 0x49f58au);	/* 46c3ce: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3d3: push esi */
	{ DWORD v_ = 0xe10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3d4: push 0xe10 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3d9: push 4 */
	{ DWORD v_ = 0xa17f38u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3db: push 0xa17f38 */
	m->esp -= 4; M32(m->esp) = 0x46c3e5u; native_call(m, 0x49f58au);	/* 46c3e0: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3e5: push esi */
	{ DWORD v_ = 0xe10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3e6: push 0xe10 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3eb: push 4 */
	{ DWORD v_ = 0xa146f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3ed: push 0xa146f8 */
	m->esp -= 4; M32(m->esp) = 0x46c3f7u; native_call(m, 0x49f58au);	/* 46c3f2: call 0x49f58a */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3f7: push esi */
	{ DWORD v_ = 0x1000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3f8: push 0x1000 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3fd: push 4 */
	{ DWORD v_ = 0xa106f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c3ff: push 0xa106f8 */
	m->esp -= 4; M32(m->esp) = 0x46c409u; native_call(m, 0x49f58au);	/* 46c404: call 0x49f58a */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c409: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c40c: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c412u; native_call(m, 0x49e7e0u);	/* 46c40d: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c412: add esp, 4 */
	m->esi = M32(m->esp); m->esp += 4;	/* 46c415: pop esi */
	m->ecx = M32(m->esp); m->esp += 4;	/* 46c416: pop ecx */
	m->esp += 4 + 0; return;	/* 46c417: ret  */
}

/* math_initMathFunction (0x46c270), lifted by tools/lift.py */
static void lift_46c270(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 46c270: push ecx */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c271: push 0x4ad170 */
	{ DWORD v_ = 0x4c575cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c276: push 0x4c575c */
	m->esp -= 4; M32(m->esp) = 0x46c280u; native_call(m, 0x49e9cau);	/* 46c27b: call 0x49e9ca */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c280: add esp, 8 */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46c283: test eax, eax */
	if (!m->zf) goto L_46c28c;	/* 46c285: jne 0x46c28c */
	m->esp -= 4; M32(m->esp) = 0x46c28cu; lift_46c340(m);	/* 46c287: call 0x46c340 */
L_46c28c:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c28c: push esi */
	{ DWORD v_ = 0x4ad170u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c28d: push 0x4ad170 */
	{ DWORD v_ = 0x4c575cu; m->esp -= 4; M32(m->esp) = v_; }	/* 46c292: push 0x4c575c */
	m->esp -= 4; M32(m->esp) = 0x46c29cu; native_call(m, 0x49e9cau);	/* 46c297: call 0x49e9ca */
	m->esi = m->eax;	/* 46c29c: mov esi, eax */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c29e: add esp, 8 */
	{ DWORD a_ = m->esi, b_ = m->esi & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 46c2a1: test esi, esi */
	if (!m->zf) goto L_46c2b2;	/* 46c2a3: jne 0x46c2b2 */
	{ DWORD v_ = 0x4c5728u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2a5: push 0x4c5728 */
	m->esp -= 4; M32(m->esp) = 0x46c2afu; native_call(m, 0x46c950u);	/* 46c2aa: call 0x46c950 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c2af: add esp, 4 */
L_46c2b2:
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2b2: push esi */
	{ DWORD v_ = 0xe10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2b3: push 0xe10 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2b8: push 4 */
	{ DWORD v_ = 0xa1b778u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2ba: push 0xa1b778 */
	m->esp -= 4; M32(m->esp) = 0x46c2c4u; native_call(m, 0x49e836u);	/* 46c2bf: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2c4: push esi */
	{ DWORD v_ = 0xe10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2c5: push 0xe10 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2ca: push 4 */
	{ DWORD v_ = 0xa17f38u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2cc: push 0xa17f38 */
	m->esp -= 4; M32(m->esp) = 0x46c2d6u; native_call(m, 0x49e836u);	/* 46c2d1: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2d6: push esi */
	{ DWORD v_ = 0xe10u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2d7: push 0xe10 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2dc: push 4 */
	{ DWORD v_ = 0xa146f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2de: push 0xa146f8 */
	m->esp -= 4; M32(m->esp) = 0x46c2e8u; native_call(m, 0x49e836u);	/* 46c2e3: call 0x49e836 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2e8: push esi */
	{ DWORD v_ = 0x1000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2e9: push 0x1000 */
	{ DWORD v_ = 0x4u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2ee: push 4 */
	{ DWORD v_ = 0xa106f8u; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2f0: push 0xa106f8 */
	m->esp -= 4; M32(m->esp) = 0x46c2fau; native_call(m, 0x49e836u);	/* 46c2f5: call 0x49e836 */
	{ DWORD a_ = m->esp, b_ = 0x40u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c2fa: add esp, 0x40 */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 46c2fd: push esi */
	m->esp -= 4; M32(m->esp) = 0x46c303u; native_call(m, 0x49e7e0u);	/* 46c2fe: call 0x49e7e0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 46c303: add esp, 4 */
	m->eax = 0x55u;	/* 46c306: mov eax, 0x55 */
	m->ecx = 0xa106b0u;	/* 46c30b: mov ecx, 0xa106b0 */
	M32((DWORD)(m->esp + 0x4u)) = m->eax;	/* 46c310: mov dword ptr [esp + 4], eax */
	m->esi = M32(m->esp); m->esp += 4;	/* 46c314: pop esi */
L_46c315:
	FPUSH((long double)(int)M32((DWORD)(m->esp + 0x0u)));	/* 46c315: fild dword ptr [esp] */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 46c319: sub eax, 0xa */
	{ DWORD a_ = m->ecx, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ecx = r_; }	/* 46c31c: add ecx, 4 */
	{ DWORD a_ = m->eax, b_ = 0xffffffa1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 46c31f: cmp eax, -0x5f */
	M32((DWORD)(m->esp + 0x0u)) = m->eax;	/* 46c322: mov dword ptr [esp], eax */
	ST(0) = ST(0) * (long double)*(const double *)(DWORD)(0x4aa290u);	/* 46c326: fmul qword ptr [0x4aa290] */
	{ long double t_ = ST(0), one_; __asm__("fptan" : "=t"(one_), "=u"(t_) : "0"(t_)); ST(0) = t_; FPUSH(one_); }	/* 46c32c: fptan  */
	ST(0) = ST(0); FPOP();	/* 46c32e: fstp st(0) */
	MF((DWORD)(m->ecx + 0xfffffffcu)) = (float)ST(0); FPOP();	/* 46c330: fstp dword ptr [ecx - 4] */
	if (!m->zf && m->sf == m->of) goto L_46c315;	/* 46c333: jg 0x46c315 */
	m->ecx = M32(m->esp); m->esp += 4;	/* 46c335: pop ecx */
	m->esp += 4 + 0; return;	/* 46c336: ret  */
}

/* glWindow_4684c0 (0x4684c0), lifted by tools/lift.py */
static void lift_4684c0(X86 *m)
{
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 4684c0: push esi */
	m->esi = M32((DWORD)(0x4a924cu));	/* 4684c1: mov esi, dword ptr [0x4a924c] */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 4684c7: push edi */
	{ DWORD v_ = 0x1102u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684c8: push 0x1102 */
	{ DWORD v_ = 0xc50u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684cd: push 0xc50 */
	m->esp -= 4; M32(m->esp) = 0x4684d4u; native_call(m, m->esi);	/* 4684d2: call esi */
	{ DWORD v_ = 0x46040000u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684d4: push 0x46040000 */
	{ DWORD v_ = 0x2200u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684d9: push 0x2200 */
	{ DWORD v_ = 0x2300u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684de: push 0x2300 */
	m->esp -= 4; M32(m->esp) = 0x4684e9u; native_call(m, M32(0x4a91c8u));	/* 4684e3: call dword ptr [0x4a91c8] */
	{ DWORD v_ = 0x303u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684e9: push 0x303 */
	{ DWORD v_ = 0x302u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684ee: push 0x302 */
	m->esp -= 4; M32(m->esp) = 0x4684f9u; native_call(m, M32(0x4a91ecu));	/* 4684f3: call dword ptr [0x4a91ec] */
	{ DWORD v_ = 0x1102u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684f9: push 0x1102 */
	{ DWORD v_ = 0xc51u; m->esp -= 4; M32(m->esp) = v_; }	/* 4684fe: push 0xc51 */
	m->esp -= 4; M32(m->esp) = 0x468505u; native_call(m, m->esi);	/* 468503: call esi */
	{ DWORD v_ = 0x1102u; m->esp -= 4; M32(m->esp) = v_; }	/* 468505: push 0x1102 */
	{ DWORD v_ = 0xc52u; m->esp -= 4; M32(m->esp) = v_; }	/* 46850a: push 0xc52 */
	m->esp -= 4; M32(m->esp) = 0x468511u; native_call(m, m->esi);	/* 46850f: call esi */
	{ DWORD v_ = 0x203u; m->esp -= 4; M32(m->esp) = v_; }	/* 468511: push 0x203 */
	m->esp -= 4; M32(m->esp) = 0x46851cu; native_call(m, M32(0x4a91ccu));	/* 468516: call dword ptr [0x4a91cc] */
	{ DWORD v_ = 0x1102u; m->esp -= 4; M32(m->esp) = v_; }	/* 46851c: push 0x1102 */
	{ DWORD v_ = 0xc54u; m->esp -= 4; M32(m->esp) = v_; }	/* 468521: push 0xc54 */
	m->esp -= 4; M32(m->esp) = 0x468528u; native_call(m, m->esi);	/* 468526: call esi */
	m->edi = M32((DWORD)(0x4a9224u));	/* 468528: mov edi, dword ptr [0x4a9224] */
	{ DWORD v_ = 0x1d01u; m->esp -= 4; M32(m->esp) = v_; }	/* 46852e: push 0x1d01 */
	m->esp -= 4; M32(m->esp) = 0x468535u; native_call(m, m->edi);	/* 468533: call edi */
	m->esi = M32((DWORD)(0x4a922cu));	/* 468535: mov esi, dword ptr [0x4a922c] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 46853b: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x468542u; native_call(m, m->esi);	/* 468540: call esi */
	{ DWORD v_ = 0xbe2u; m->esp -= 4; M32(m->esp) = v_; }	/* 468542: push 0xbe2 */
	m->esp -= 4; M32(m->esp) = 0x468549u; native_call(m, m->edi);	/* 468547: call edi */
	{ DWORD v_ = 0xb10u; m->esp -= 4; M32(m->esp) = v_; }	/* 468549: push 0xb10 */
	m->esp -= 4; M32(m->esp) = 0x468550u; native_call(m, m->esi);	/* 46854e: call esi */
	{ DWORD v_ = 0xb20u; m->esp -= 4; M32(m->esp) = v_; }	/* 468550: push 0xb20 */
	m->esp -= 4; M32(m->esp) = 0x468557u; native_call(m, m->esi);	/* 468555: call esi */
	{ DWORD v_ = 0xb41u; m->esp -= 4; M32(m->esp) = v_; }	/* 468557: push 0xb41 */
	m->esp -= 4; M32(m->esp) = 0x46855eu; native_call(m, m->esi);	/* 46855c: call esi */
	{ DWORD v_ = 0xb71u; m->esp -= 4; M32(m->esp) = v_; }	/* 46855e: push 0xb71 */
	m->esp -= 4; M32(m->esp) = 0x468565u; native_call(m, m->edi);	/* 468563: call edi */
	{ DWORD v_ = 0xb50u; m->esp -= 4; M32(m->esp) = v_; }	/* 468565: push 0xb50 */
	m->esp -= 4; M32(m->esp) = 0x46856cu; native_call(m, m->esi);	/* 46856a: call esi */
	{ DWORD v_ = 0x4000u; m->esp -= 4; M32(m->esp) = v_; }	/* 46856c: push 0x4000 */
	m->esp -= 4; M32(m->esp) = 0x468573u; native_call(m, m->esi);	/* 468571: call esi */
	{ DWORD v_ = 0xb60u; m->esp -= 4; M32(m->esp) = v_; }	/* 468573: push 0xb60 */
	m->esp -= 4; M32(m->esp) = 0x46857au; native_call(m, m->esi);	/* 468578: call esi */
	{ DWORD v_ = 0x1b02u; m->esp -= 4; M32(m->esp) = v_; }	/* 46857a: push 0x1b02 */
	{ DWORD v_ = 0x408u; m->esp -= 4; M32(m->esp) = v_; }	/* 46857f: push 0x408 */
	m->esp -= 4; M32(m->esp) = 0x46858au; native_call(m, M32(0x4a91c4u));	/* 468584: call dword ptr [0x4a91c4] */
	{ DWORD v_ = 0x901u; m->esp -= 4; M32(m->esp) = v_; }	/* 46858a: push 0x901 */
	m->esp -= 4; M32(m->esp) = 0x468595u; native_call(m, M32(0x4a91c0u));	/* 46858f: call dword ptr [0x4a91c0] */
	{ DWORD v_ = 0x405u; m->esp -= 4; M32(m->esp) = v_; }	/* 468595: push 0x405 */
	m->esp -= 4; M32(m->esp) = 0x4685a0u; native_call(m, M32(0x4a91d0u));	/* 46859a: call dword ptr [0x4a91d0] */
	{ DWORD v_ = 0xb44u; m->esp -= 4; M32(m->esp) = v_; }	/* 4685a0: push 0xb44 */
	m->esp -= 4; M32(m->esp) = 0x4685a7u; native_call(m, m->esi);	/* 4685a5: call esi */
	m->edi = M32(m->esp); m->esp += 4;	/* 4685a7: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4685a8: pop esi */
	m->esp += 4 + 0; return;	/* 4685a9: ret  */
}

/* reg_readServerSettings (0x42bde0), lifted by tools/lift.py */
static void lift_42bde0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bde0: sub esp, 0xc */
	m->eax = (DWORD)(m->esp + 0x0u);	/* 42bde3: lea eax, [esp] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42bde7: push eax */
	{ DWORD v_ = 0xf003fu; m->esp -= 4; M32(m->esp) = v_; }	/* 42bde8: push 0xf003f */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bded: push 0 */
	{ DWORD v_ = 0x4b1728u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bdef: push 0x4b1728 */
	{ DWORD v_ = 0x80000001u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bdf4: push 0x80000001 */
	m->esp -= 4; M32(m->esp) = 0x42bdffu; native_call(m, M32(0x4a9004u));	/* 42bdf9: call dword ptr [0x4a9004] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 42bdff: test eax, eax */
	if (!m->zf) goto L_42bea1;	/* 42be01: jne 0x42bea1 */
	m->ecx = (DWORD)(m->esp + 0x4u);	/* 42be07: lea ecx, [esp + 4] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 42be0b: push esi */
	m->esi = M32((DWORD)(0x4a9008u));	/* 42be0c: mov esi, dword ptr [0x4a9008] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be12: push ecx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42be13: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0xa0b24cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42be17: push 0xa0b24c */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be1c: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42be1d: push eax */
	m->eax = M32((DWORD)(m->esp + 0x14u));	/* 42be1e: mov eax, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x4b1720u; m->esp -= 4; M32(m->esp) = v_; }	/* 42be22: push 0x4b1720 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42be27: push eax */
	M32((DWORD)(m->esp + 0x20u)) = 0x32u;	/* 42be28: mov dword ptr [esp + 0x20], 0x32 */
	m->esp -= 4; M32(m->esp) = 0x42be32u; native_call(m, m->esi);	/* 42be30: call esi */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 42be32: mov eax, dword ptr [esp + 4] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 42be36: lea ecx, [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be3a: push ecx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42be3b: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0xa055fcu; m->esp -= 4; M32(m->esp) = v_; }	/* 42be3f: push 0xa055fc */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be44: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42be45: push 0 */
	{ DWORD v_ = 0x4b1714u; m->esp -= 4; M32(m->esp) = v_; }	/* 42be47: push 0x4b1714 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42be4c: push eax */
	m->esp -= 4; M32(m->esp) = 0x42be4fu; native_call(m, m->esi);	/* 42be4d: call esi */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 42be4f: mov eax, dword ptr [esp + 4] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 42be53: lea ecx, [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be57: push ecx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42be58: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0xa055f4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42be5c: push 0xa055f4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be61: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42be62: push 0 */
	{ DWORD v_ = 0x4b170cu; m->esp -= 4; M32(m->esp) = v_; }	/* 42be64: push 0x4b170c */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42be69: push eax */
	M32((DWORD)(m->esp + 0x20u)) = 0x4u;	/* 42be6a: mov dword ptr [esp + 0x20], 4 */
	m->esp -= 4; M32(m->esp) = 0x42be74u; native_call(m, m->esi);	/* 42be72: call esi */
	m->eax = M32((DWORD)(m->esp + 0x4u));	/* 42be74: mov eax, dword ptr [esp + 4] */
	m->ecx = (DWORD)(m->esp + 0x8u);	/* 42be78: lea ecx, [esp + 8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be7c: push ecx */
	m->edx = (DWORD)(m->esp + 0x10u);	/* 42be7d: lea edx, [esp + 0x10] */
	{ DWORD v_ = 0xa05634u; m->esp -= 4; M32(m->esp) = v_; }	/* 42be81: push 0xa05634 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be86: push edx */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42be87: push 0 */
	{ DWORD v_ = 0x4b1700u; m->esp -= 4; M32(m->esp) = v_; }	/* 42be89: push 0x4b1700 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42be8e: push eax */
	m->esp -= 4; M32(m->esp) = 0x42be91u; native_call(m, m->esi);	/* 42be8f: call esi */
	m->ecx = M32((DWORD)(m->esp + 0x4u));	/* 42be91: mov ecx, dword ptr [esp + 4] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 42be95: push ecx */
	m->esp -= 4; M32(m->esp) = 0x42be9cu; native_call(m, M32(0x4a900cu));	/* 42be96: call dword ptr [0x4a900c] */
	m->esi = M32(m->esp); m->esp += 4;	/* 42be9c: pop esi */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42be9d: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 42bea0: ret  */
L_42bea1:
	{ DWORD a_ = M32((DWORD)(0x9dae74u)), b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 42bea1: cmp dword ptr [0x9dae74], 1 */
	if (!m->zf) goto L_42beb1;	/* 42bea8: jne 0x42beb1 */
	{ DWORD v_ = 0x4b16a4u; m->esp -= 4; M32(m->esp) = v_; }	/* 42beaa: push 0x4b16a4 */
	goto L_42beb6;	/* 42beaf: jmp 0x42beb6 */
L_42beb1:
	{ DWORD v_ = 0x4b1660u; m->esp -= 4; M32(m->esp) = v_; }	/* 42beb1: push 0x4b1660 */
L_42beb6:
	m->esp -= 4; M32(m->esp) = 0x42bebbu; native_call(m, 0x41edf0u);	/* 42beb6: call 0x41edf0 */
	m->edx = M32((DWORD)(m->esp + 0x4u));	/* 42bebb: mov edx, dword ptr [esp + 4] */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bebf: add esp, 4 */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 42bec2: push edx */
	m->esp -= 4; M32(m->esp) = 0x42bec9u; native_call(m, M32(0x4a900cu));	/* 42bec3: call dword ptr [0x4a900c] */
	m->eax = M32((DWORD)(0x4ded18u));	/* 42bec9: mov eax, dword ptr [0x4ded18] */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bece: push 0 */
	{ DWORD v_ = 0x0u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bed0: push 0 */
	{ DWORD v_ = 0x10u; m->esp -= 4; M32(m->esp) = v_; }	/* 42bed2: push 0x10 */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 42bed4: push eax */
	m->esp -= 4; M32(m->esp) = 0x42bedbu; native_call(m, M32(0x4a9328u));	/* 42bed5: call dword ptr [0x4a9328] */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 42bedb: add esp, 0xc */
	m->esp += 4 + 0; return;	/* 42bede: ret  */
}

/* text_ascii5Pass (0x403060), lifted by tools/lift.py */
static void lift_403060(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403060: push ecx */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 403061: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 403065: push ebx */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 403066: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 403067: push edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 403068: mov edi, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40306c: push 7 */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 40306e: mov dword ptr [esp + 0x10], eax */
	m->esp -= 4; M32(m->esp) = 0x403078u; native_call(m, M32(0x4a921cu));	/* 403072: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x1cu));	/* 403078: mov esi, dword ptr [esp + 0x1c] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 40307c: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40307e: test bl, bl */
	if (m->zf) goto L_40315b;	/* 403080: je 0x40315b */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 403086: push ebp */
	m->ebp = M32((DWORD)(0x4a9228u));	/* 403087: mov ebp, dword ptr [0x4a9228] */
L_40308d:
	m->ecx = M32((DWORD)(0x76d444u));	/* 40308d: mov ecx, dword ptr [0x76d444] */
	m->edx = M32((DWORD)(0x76d440u));	/* 403093: mov edx, dword ptr [0x76d440] */
	m->eax = M32((DWORD)(0x76d43cu));	/* 403099: mov eax, dword ptr [0x76d43c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40309e: push ecx */
	m->ecx = M32((DWORD)(0x76d438u));	/* 40309f: mov ecx, dword ptr [0x76d438] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4030a5: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4030a6: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4030a7: push ecx */
	M8((DWORD)(m->esp + 0x2cu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4030a8: mov byte ptr [esp + 0x2c], bl */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4030ac: inc esi */
	m->esp -= 4; M32(m->esp) = 0x4030afu; native_call(m, m->ebp);	/* 4030ad: call ebp */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4030af: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_4030de;	/* 4030b9: je 0x4030de */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4030bb: cmp bl, 0x7c */
	if (!m->zf) goto L_4030de;	/* 4030be: jne 0x4030de */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4030c0: cmp byte ptr [esi], bl */
	if (m->zf) goto L_4030d5;	/* 4030c2: je 0x4030d5 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4030c4: mov eax, dword ptr [esp + 0x10] */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 4030c8: mov edi, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = 0xau & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4030cc: add eax, 0xa */
	M32((DWORD)(m->esp + 0x10u)) = m->eax;	/* 4030cf: mov dword ptr [esp + 0x10], eax */
	goto L_403150;	/* 4030d3: jmp 0x403150 */
L_4030d5:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x7cu) & 0xff) << 0);	/* 4030d5: mov bl, 0x7c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4030d7: inc esi */
	M8((DWORD)(m->esp + 0x1cu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4030d8: mov byte ptr [esp + 0x1c], bl */
	goto L_403129;	/* 4030dc: jmp 0x403129 */
L_4030de:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4030de: cmp bl, 0x24 */
	if (!m->zf) goto L_403129;	/* 4030e1: jne 0x403129 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4030e3: cmp byte ptr [esi], 0x5b */
	if (!m->zf) goto L_403129;	/* 4030e6: jne 0x403129 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x2u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4030e8: cmp byte ptr [esi + 2], 0x5d */
	if (!m->zf) goto L_403129;	/* 4030ec: jne 0x403129 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4u))) & 0xff) << 0);	/* 4030ee: mov al, byte ptr [esi + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4030f1: test al, al */
	if (m->zf) goto L_403129;	/* 4030f3: je 0x403129 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 4030f5: movsx eax, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4030f9: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4030fa: sub eax, 0x30 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4030fd: shl eax, 4 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x3u))) & 0xff) << 0);	/* 403100: mov bl, byte ptr [esi + 3] */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 403103: add esi, 3 */
	m->edx = M32((DWORD)(m->eax + 0x9dadacu));	/* 403106: mov edx, dword ptr [eax + 0x9dadac] */
	m->ecx = M32((DWORD)(m->eax + 0x9dada8u));	/* 40310c: mov ecx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 403112: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada4u));	/* 403113: mov edx, dword ptr [eax + 0x9dada4] */
	m->eax = M32((DWORD)(m->eax + 0x9dada0u));	/* 403119: mov eax, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40311f: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 403120: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 403121: push eax */
	M8((DWORD)(m->esp + 0x2cu)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 403122: mov byte ptr [esp + 0x2c], bl */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 403126: inc esi */
	m->esp -= 4; M32(m->esp) = 0x403129u; native_call(m, m->ebp);	/* 403127: call ebp */
L_403129:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 403129: test bl, 0x80 */
	if (m->zf) goto L_403134;	/* 40312c: je 0x403134 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40312e: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40312f: add edi, 0x10 */
	goto L_403150;	/* 403132: jmp 0x403150 */
L_403134:
	m->ecx = M32((DWORD)(m->esp + 0x1cu));	/* 403134: mov ecx, dword ptr [esp + 0x1c] */
	m->edx = M32((DWORD)(m->esp + 0x10u));	/* 403138: mov edx, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 40313c: and ecx, 0xff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 403142: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 403143: push edx */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 403144: push edi */
	m->esp -= 4; M32(m->esp) = 0x40314au; native_call(m, 0x428240u);	/* 403145: call 0x428240 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 40314a: add esp, 0xc */
	{ DWORD a_ = m->edi, b_ = 0x6u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40314d: add edi, 6 */
L_403150:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 403150: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 403152: test bl, bl */
	if (!m->zf) goto L_40308d;	/* 403154: jne 0x40308d */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40315a: pop ebp */
L_40315b:
	m->esp -= 4; M32(m->esp) = 0x403161u; native_call(m, M32(0x4a9220u));	/* 40315b: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 403161: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 403162: pop esi */
	m->ebx = M32(m->esp); m->esp += 4;	/* 403163: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 403164: pop ecx */
	m->esp += 4 + 0; return;	/* 403165: ret  */
}

/* text_ascii32Pass (0x402420), lifted by tools/lift.py */
static void lift_402420(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402420: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402421: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 402422: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 402426: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 402427: push edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 402428: mov edi, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40242c: push 7 */
	m->esp -= 4; M32(m->esp) = 0x402434u; native_call(m, M32(0x4a921cu));	/* 40242e: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x1cu));	/* 402434: mov esi, dword ptr [esp + 0x1c] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 402438: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40243a: test bl, bl */
	if (m->zf) goto L_402560;	/* 40243c: je 0x402560 */
L_402442:
	m->eax = M32((DWORD)(0x76d444u));	/* 402442: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 402447: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 40244d: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402453: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 402454: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402459: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40245a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40245b: push eax */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 40245c: mov byte ptr [esp + 0x28], bl */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402460: inc esi */
	m->esp -= 4; M32(m->esp) = 0x402467u; native_call(m, M32(0x4a9228u));	/* 402461: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402467: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_4024b8;	/* 402471: je 0x4024b8 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402473: cmp bl, 0x7c */
	if (!m->zf) goto L_4024b8;	/* 402476: jne 0x4024b8 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402478: cmp byte ptr [esi], bl */
	if (m->zf) goto L_402488;	/* 40247a: je 0x402488 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 40247c: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 402480: add ebp, 0x21 */
	goto L_40254a;	/* 402483: jmp 0x40254a */
L_402488:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x7cu) & 0xff) << 0);	/* 402488: mov bl, 0x7c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40248a: inc esi */
	M8((DWORD)(m->esp + 0x18u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 40248b: mov byte ptr [esp + 0x18], bl */
L_40248f:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(0x4ad490u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40248f: cmp edi, dword ptr [0x4ad490] */
	if (m->sf != m->of) goto L_40249e;	/* 402495: jl 0x40249e */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 402497: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 40249b: add ebp, 0x21 */
L_40249e:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4ad494u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40249e: cmp ebp, dword ptr [0x4ad494] */
	if (m->sf == m->of) goto L_402556;	/* 4024a4: jge 0x402556 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4024aa: test bl, 0x80 */
	if (m->zf) goto L_40251f;	/* 4024ad: je 0x40251f */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4024af: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4024b0: add edi, 0x20 */
	goto L_40254a;	/* 4024b3: jmp 0x40254a */
L_4024b8:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4024b8: cmp bl, 0x24 */
	if (!m->zf) goto L_402507;	/* 4024bb: jne 0x402507 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4024bd: cmp byte ptr [esi], 0x5b */
	if (!m->zf) goto L_40248f;	/* 4024c0: jne 0x40248f */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x2u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4024c2: cmp byte ptr [esi + 2], 0x5d */
	if (!m->zf) goto L_40248f;	/* 4024c6: jne 0x40248f */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4u))) & 0xff) << 0);	/* 4024c8: mov al, byte ptr [esi + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4024cb: test al, al */
	if (m->zf) goto L_40248f;	/* 4024cd: je 0x40248f */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 4024cf: movsx eax, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4024d3: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4024d4: sub eax, 0x30 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4024d7: shl eax, 4 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x3u))) & 0xff) << 0);	/* 4024da: mov bl, byte ptr [esi + 3] */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 4024dd: add esi, 3 */
	m->ecx = M32((DWORD)(m->eax + 0x9dadacu));	/* 4024e0: mov ecx, dword ptr [eax + 0x9dadac] */
	m->edx = M32((DWORD)(m->eax + 0x9dada8u));	/* 4024e6: mov edx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4024ec: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x9dada4u));	/* 4024ed: mov ecx, dword ptr [eax + 0x9dada4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4024f3: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada0u));	/* 4024f4: mov edx, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4024fa: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4024fb: push edx */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4024fc: mov byte ptr [esp + 0x28], bl */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402500: inc esi */
	m->esp -= 4; M32(m->esp) = 0x402507u; native_call(m, M32(0x4a9228u));	/* 402501: call dword ptr [0x4a9228] */
L_402507:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402507: cmp bl, 0xd */
	if (!m->zf) goto L_40248f;	/* 40250a: jne 0x40248f */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0xau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40250c: cmp byte ptr [esi], 0xa */
	if (!m->zf) goto L_40248f;	/* 40250f: jne 0x40248f */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 402515: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402519: inc esi */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 40251a: add ebp, 0x21 */
	goto L_40254a;	/* 40251d: jmp 0x40254a */
L_40251f:
	m->eax = M32((DWORD)(m->esp + 0x18u));	/* 40251f: mov eax, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->eax = r_; }	/* 402523: and eax, 0xff */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 402528: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402529: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40252a: push edi */
	m->esp -= 4; M32(m->esp) = 0x402530u; native_call(m, 0x428190u);	/* 40252b: call 0x428190 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 402530: add esp, 0xc */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x20u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402533: cmp bl, 0x20 */
	if (m->zf) goto L_402547;	/* 402536: je 0x402547 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x49u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402538: cmp bl, 0x49 */
	if (m->zf) goto L_402547;	/* 40253b: je 0x402547 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x69u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40253d: cmp bl, 0x69 */
	if (m->zf) goto L_402547;	/* 402540: je 0x402547 */
	{ DWORD a_ = m->edi, b_ = 0x16u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 402542: add edi, 0x16 */
	goto L_40254a;	/* 402545: jmp 0x40254a */
L_402547:
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 402547: add edi, 0x10 */
L_40254a:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 40254a: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40254c: test bl, bl */
	if (!m->zf) goto L_402442;	/* 40254e: jne 0x402442 */
	goto L_402560;	/* 402554: jmp 0x402560 */
L_402556:
	M32((DWORD)(0x4d7348u)) = 0x1u;	/* 402556: mov dword ptr [0x4d7348], 1 */
L_402560:
	M32((DWORD)(0x4d23c8u)) = m->edi;	/* 402560: mov dword ptr [0x4d23c8], edi */
	M32((DWORD)(0x4d23ccu)) = m->ebp;	/* 402566: mov dword ptr [0x4d23cc], ebp */
	m->esp -= 4; M32(m->esp) = 0x402572u; native_call(m, M32(0x4a9220u));	/* 40256c: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 402572: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x40257du; native_call(m, M32(0x4a922cu));	/* 402577: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 40257d: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 40257e: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 40257f: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 402580: pop ebx */
	m->esp += 4 + 0; return;	/* 402581: ret  */
}

/* text_ascii8Pass (0x402010), lifted by tools/lift.py */
static void lift_402010(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402010: push ecx */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 402011: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402015: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402016: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 402017: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40201b: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40201c: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40201d: push 7 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 40201f: mov dword ptr [esp + 0x20], eax */
	M32((DWORD)(0x4d23ccu)) = m->eax;	/* 402023: mov dword ptr [0x4d23cc], eax */
	M32((DWORD)(0x4d23c8u)) = m->ebp;	/* 402028: mov dword ptr [0x4d23c8], ebp */
	m->esp -= 4; M32(m->esp) = 0x402034u; native_call(m, M32(0x4a921cu));	/* 40202e: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 402034: mov esi, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 402038: mov dword ptr [esp + 0x10], 0 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 402040: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 402042: test bl, bl */
	if (m->zf) goto L_4021e5;	/* 402044: je 0x4021e5 */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 40204a: mov edi, dword ptr [esp + 0x18] */
L_40204e:
	m->eax = M32((DWORD)(0x76d3e8u));	/* 40204e: mov eax, dword ptr [0x76d3e8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402053: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402054: cmp eax, 0x270f */
	M8((DWORD)(m->esp + 0x20u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 402059: mov byte ptr [esp + 0x20], bl */
	if (m->zf) goto L_402066;	/* 40205d: je 0x402066 */
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40205f: cmp eax, 0x190 */
	if (!m->zf) goto L_4020bc;	/* 402064: jne 0x4020bc */
L_402066:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402066: cmp bl, 0x24 */
	if (!m->zf) goto L_402091;	/* 402069: jne 0x402091 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x23u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40206b: cmp byte ptr [esi], 0x23 */
	if (!m->zf) goto L_402091;	/* 40206e: jne 0x402091 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x2u))) & 0xff) << 0);	/* 402070: mov al, byte ptr [esi + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 402073: test al, al */
	if (m->zf) goto L_402091;	/* 402075: je 0x402091 */
	m->edi = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 402077: movsx edi, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40207b: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40207c: sub edi, 0x30 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40207f: inc esi */
	M32((DWORD)(m->esp + 0x10u)) = 0x1u;	/* 402080: mov dword ptr [esp + 0x10], 1 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 402088: mov bl, byte ptr [esi] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40208a: inc esi */
	M8((DWORD)(m->esp + 0x20u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 40208b: mov byte ptr [esp + 0x20], bl */
	goto L_402099;	/* 40208f: jmp 0x402099 */
L_402091:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 402091: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 402095: test eax, eax */
	if (m->zf) goto L_4020bc;	/* 402097: je 0x4020bc */
L_402099:
	m->eax = m->edi;	/* 402099: mov eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40209b: shl eax, 4 */
	m->ecx = M32((DWORD)(m->eax + 0x9dadacu));	/* 40209e: mov ecx, dword ptr [eax + 0x9dadac] */
	m->edx = M32((DWORD)(m->eax + 0x9dada8u));	/* 4020a4: mov edx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4020aa: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x9dada4u));	/* 4020ab: mov ecx, dword ptr [eax + 0x9dada4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4020b1: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada0u));	/* 4020b2: mov edx, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4020b8: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4020b9: push edx */
	goto L_4020d6;	/* 4020ba: jmp 0x4020d6 */
L_4020bc:
	m->eax = M32((DWORD)(0x76d444u));	/* 4020bc: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 4020c1: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 4020c7: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4020cd: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 4020ce: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4020d3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4020d4: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4020d5: push eax */
L_4020d6:
	m->esp -= 4; M32(m->esp) = 0x4020dcu; native_call(m, M32(0x4a9228u));	/* 4020d6: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4020dc: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_402143;	/* 4020e6: je 0x402143 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4020e8: cmp bl, 0x7c */
	if (!m->zf) goto L_402143;	/* 4020eb: jne 0x402143 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4020ed: cmp byte ptr [esi], bl */
	if (m->zf) goto L_402105;	/* 4020ef: je 0x402105 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4020f1: mov eax, dword ptr [esp + 0x1c] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 4020f5: mov ebp, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4020f9: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4020fc: mov dword ptr [esp + 0x1c], eax */
	goto L_4021cf;	/* 402100: jmp 0x4021cf */
L_402105:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x7cu) & 0xff) << 0);	/* 402105: mov bl, 0x7c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402107: inc esi */
	M8((DWORD)(m->esp + 0x20u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 402108: mov byte ptr [esp + 0x20], bl */
L_40210c:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4ad490u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40210c: cmp ebp, dword ptr [0x4ad490] */
	if (m->sf != m->of) goto L_402123;	/* 402112: jl 0x402123 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 402114: mov eax, dword ptr [esp + 0x1c] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 402118: mov ebp, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40211c: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 40211f: mov dword ptr [esp + 0x1c], eax */
L_402123:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 402123: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(0x4ad494u));	/* 402127: mov ecx, dword ptr [0x4ad494] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40212d: cmp eax, ecx */
	if (m->sf == m->of) goto L_4021db;	/* 40212f: jge 0x4021db */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 402135: test bl, 0x80 */
	if (m->zf) goto L_4021b7;	/* 402138: je 0x4021b7 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40213a: inc esi */
	{ DWORD a_ = m->ebp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 40213b: add ebp, 0x10 */
	goto L_4021cf;	/* 40213e: jmp 0x4021cf */
L_402143:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402143: cmp bl, 0x24 */
	if (!m->zf) goto L_402193;	/* 402146: jne 0x402193 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402148: cmp byte ptr [esi], 0x5b */
	if (!m->zf) goto L_40210c;	/* 40214b: jne 0x40210c */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x2u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40214d: cmp byte ptr [esi + 2], 0x5d */
	if (!m->zf) goto L_40210c;	/* 402151: jne 0x40210c */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4u))) & 0xff) << 0);	/* 402153: mov al, byte ptr [esi + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 402156: test al, al */
	if (m->zf) goto L_40210c;	/* 402158: je 0x40210c */
	m->edi = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 40215a: movsx edi, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40215e: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 40215f: sub edi, 0x30 */
	m->eax = m->edi;	/* 402162: mov eax, edi */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 402164: add esi, 3 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402167: shl eax, 4 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 40216a: mov bl, byte ptr [esi] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40216c: inc esi */
	m->ecx = M32((DWORD)(m->eax + 0x9dadacu));	/* 40216d: mov ecx, dword ptr [eax + 0x9dadac] */
	m->edx = M32((DWORD)(m->eax + 0x9dada8u));	/* 402173: mov edx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402179: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x9dada4u));	/* 40217a: mov ecx, dword ptr [eax + 0x9dada4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402180: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada0u));	/* 402181: mov edx, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402187: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 402188: push edx */
	M8((DWORD)(m->esp + 0x30u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 402189: mov byte ptr [esp + 0x30], bl */
	m->esp -= 4; M32(m->esp) = 0x402193u; native_call(m, M32(0x4a9228u));	/* 40218d: call dword ptr [0x4a9228] */
L_402193:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402193: cmp bl, 0xd */
	if (!m->zf) goto L_40210c;	/* 402196: jne 0x40210c */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0xau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40219c: cmp byte ptr [esi], 0xa */
	if (!m->zf) goto L_40210c;	/* 40219f: jne 0x40210c */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4021a5: mov eax, dword ptr [esp + 0x1c] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 4021a9: mov ebp, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4021ad: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4021ae: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4021b1: mov dword ptr [esp + 0x1c], eax */
	goto L_4021cf;	/* 4021b5: jmp 0x4021cf */
L_4021b7:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4021b7: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4021bb: and ecx, 0xff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4021c1: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4021c2: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4021c3: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4021c9u; native_call(m, 0x428030u);	/* 4021c4: call 0x428030 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4021c9: add esp, 0xc */
	{ DWORD a_ = m->ebp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4021cc: add ebp, 8 */
L_4021cf:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4021cf: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4021d1: test bl, bl */
	if (!m->zf) goto L_40204e;	/* 4021d3: jne 0x40204e */
	goto L_4021e5;	/* 4021d9: jmp 0x4021e5 */
L_4021db:
	M32((DWORD)(0x4d7348u)) = 0x1u;	/* 4021db: mov dword ptr [0x4d7348], 1 */
L_4021e5:
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4021e5: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(0x4d23c8u)) = m->ebp;	/* 4021e9: mov dword ptr [0x4d23c8], ebp */
	M32((DWORD)(0x4d23ccu)) = m->edx;	/* 4021ef: mov dword ptr [0x4d23cc], edx */
	m->esp -= 4; M32(m->esp) = 0x4021fbu; native_call(m, M32(0x4a9220u));	/* 4021f5: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 4021fb: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 4021fc: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 4021fd: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 4021fe: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 4021ff: pop ecx */
	m->esp += 4 + 0; return;	/* 402200: ret  */
}

/* text_ascii16Pass (0x402210), lifted by tools/lift.py */
static void lift_402210(X86 *m)
{
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 402210: push ecx */
	m->eax = M32((DWORD)(m->esp + 0xcu));	/* 402211: mov eax, dword ptr [esp + 0xc] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 402215: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 402216: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 402217: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40221b: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40221c: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40221d: push 7 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 40221f: mov dword ptr [esp + 0x20], eax */
	m->esp -= 4; M32(m->esp) = 0x402229u; native_call(m, M32(0x4a921cu));	/* 402223: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x20u));	/* 402229: mov esi, dword ptr [esp + 0x20] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 40222d: mov dword ptr [esp + 0x10], 0 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 402235: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 402237: test bl, bl */
	if (m->zf) goto L_4023f4;	/* 402239: je 0x4023f4 */
	m->edi = M32((DWORD)(m->esp + 0x18u));	/* 40223f: mov edi, dword ptr [esp + 0x18] */
L_402243:
	m->eax = M32((DWORD)(0x76d3e8u));	/* 402243: mov eax, dword ptr [0x76d3e8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402248: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402249: cmp eax, 0x270f */
	M8((DWORD)(m->esp + 0x20u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 40224e: mov byte ptr [esp + 0x20], bl */
	if (m->zf) goto L_40225b;	/* 402252: je 0x40225b */
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402254: cmp eax, 0x190 */
	if (!m->zf) goto L_4022b1;	/* 402259: jne 0x4022b1 */
L_40225b:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40225b: cmp bl, 0x24 */
	if (!m->zf) goto L_402286;	/* 40225e: jne 0x402286 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x23u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402260: cmp byte ptr [esi], 0x23 */
	if (!m->zf) goto L_402286;	/* 402263: jne 0x402286 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x2u))) & 0xff) << 0);	/* 402265: mov al, byte ptr [esi + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 402268: test al, al */
	if (m->zf) goto L_402286;	/* 40226a: je 0x402286 */
	m->edi = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 40226c: movsx edi, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402270: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 402271: sub edi, 0x30 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402274: inc esi */
	M32((DWORD)(m->esp + 0x10u)) = 0x1u;	/* 402275: mov dword ptr [esp + 0x10], 1 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 40227d: mov bl, byte ptr [esi] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 40227f: inc esi */
	M8((DWORD)(m->esp + 0x20u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 402280: mov byte ptr [esp + 0x20], bl */
	goto L_40228e;	/* 402284: jmp 0x40228e */
L_402286:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 402286: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 40228a: test eax, eax */
	if (m->zf) goto L_4022b1;	/* 40228c: je 0x4022b1 */
L_40228e:
	m->eax = m->edi;	/* 40228e: mov eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 402290: shl eax, 4 */
	m->edx = M32((DWORD)(m->eax + 0x9dadacu));	/* 402293: mov edx, dword ptr [eax + 0x9dadac] */
	m->ecx = M32((DWORD)(m->eax + 0x9dada8u));	/* 402299: mov ecx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40229f: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada4u));	/* 4022a0: mov edx, dword ptr [eax + 0x9dada4] */
	m->eax = M32((DWORD)(m->eax + 0x9dada0u));	/* 4022a6: mov eax, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4022ac: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4022ad: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4022ae: push eax */
	goto L_4022cc;	/* 4022af: jmp 0x4022cc */
L_4022b1:
	m->ecx = M32((DWORD)(0x76d444u));	/* 4022b1: mov ecx, dword ptr [0x76d444] */
	m->edx = M32((DWORD)(0x76d440u));	/* 4022b7: mov edx, dword ptr [0x76d440] */
	m->eax = M32((DWORD)(0x76d43cu));	/* 4022bd: mov eax, dword ptr [0x76d43c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4022c2: push ecx */
	m->ecx = M32((DWORD)(0x76d438u));	/* 4022c3: mov ecx, dword ptr [0x76d438] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4022c9: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4022ca: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4022cb: push ecx */
L_4022cc:
	m->esp -= 4; M32(m->esp) = 0x4022d2u; native_call(m, M32(0x4a9228u));	/* 4022cc: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4022d2: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_402339;	/* 4022dc: je 0x402339 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4022de: cmp bl, 0x7c */
	if (!m->zf) goto L_402339;	/* 4022e1: jne 0x402339 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4022e3: cmp byte ptr [esi], bl */
	if (m->zf) goto L_4022fb;	/* 4022e5: je 0x4022fb */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 4022e7: mov eax, dword ptr [esp + 0x1c] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 4022eb: mov ebp, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4022ef: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4022f2: mov dword ptr [esp + 0x1c], eax */
	goto L_4023de;	/* 4022f6: jmp 0x4023de */
L_4022fb:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x7cu) & 0xff) << 0);	/* 4022fb: mov bl, 0x7c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4022fd: inc esi */
	M8((DWORD)(m->esp + 0x20u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4022fe: mov byte ptr [esp + 0x20], bl */
L_402302:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4ad490u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402302: cmp ebp, dword ptr [0x4ad490] */
	if (m->sf != m->of) goto L_402319;	/* 402308: jl 0x402319 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 40230a: mov eax, dword ptr [esp + 0x1c] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 40230e: mov ebp, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 402312: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 402315: mov dword ptr [esp + 0x1c], eax */
L_402319:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 402319: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(0x4ad494u));	/* 40231d: mov ecx, dword ptr [0x4ad494] */
	{ DWORD a_ = m->eax, b_ = m->ecx & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 402323: cmp eax, ecx */
	if (m->sf == m->of) goto L_4023ea;	/* 402325: jge 0x4023ea */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40232b: test bl, 0x80 */
	if (m->zf) goto L_4023ad;	/* 40232e: je 0x4023ad */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402330: inc esi */
	{ DWORD a_ = m->ebp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 402331: add ebp, 0x10 */
	goto L_4023de;	/* 402334: jmp 0x4023de */
L_402339:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402339: cmp bl, 0x24 */
	if (!m->zf) goto L_402389;	/* 40233c: jne 0x402389 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40233e: cmp byte ptr [esi], 0x5b */
	if (!m->zf) goto L_402302;	/* 402341: jne 0x402302 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x2u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402343: cmp byte ptr [esi + 2], 0x5d */
	if (!m->zf) goto L_402302;	/* 402347: jne 0x402302 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4u))) & 0xff) << 0);	/* 402349: mov al, byte ptr [esi + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 40234c: test al, al */
	if (m->zf) goto L_402302;	/* 40234e: je 0x402302 */
	m->edi = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 402350: movsx edi, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402354: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 402355: sub edi, 0x30 */
	m->eax = m->edi;	/* 402358: mov eax, edi */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 40235a: add esi, 3 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 40235d: shl eax, 4 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 402360: mov bl, byte ptr [esi] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 402362: inc esi */
	m->edx = M32((DWORD)(m->eax + 0x9dadacu));	/* 402363: mov edx, dword ptr [eax + 0x9dadac] */
	m->ecx = M32((DWORD)(m->eax + 0x9dada8u));	/* 402369: mov ecx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40236f: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada4u));	/* 402370: mov edx, dword ptr [eax + 0x9dada4] */
	m->eax = M32((DWORD)(m->eax + 0x9dada0u));	/* 402376: mov eax, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40237c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40237d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40237e: push eax */
	M8((DWORD)(m->esp + 0x30u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 40237f: mov byte ptr [esp + 0x30], bl */
	m->esp -= 4; M32(m->esp) = 0x402389u; native_call(m, M32(0x4a9228u));	/* 402383: call dword ptr [0x4a9228] */
L_402389:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402389: cmp bl, 0xd */
	if (!m->zf) goto L_402302;	/* 40238c: jne 0x402302 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0xau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 402392: cmp byte ptr [esi], 0xa */
	if (!m->zf) goto L_402302;	/* 402395: jne 0x402302 */
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 40239b: mov eax, dword ptr [esp + 0x1c] */
	m->ebp = M32((DWORD)(m->esp + 0x18u));	/* 40239f: mov ebp, dword ptr [esp + 0x18] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4023a3: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 4023a4: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x1cu)) = m->eax;	/* 4023a7: mov dword ptr [esp + 0x1c], eax */
	goto L_4023de;	/* 4023ab: jmp 0x4023de */
L_4023ad:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 4023ad: mov ecx, dword ptr [esp + 0x20] */
	{ DWORD a_ = m->ecx, b_ = 0xffu & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4023b1: and ecx, 0xff */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4023b7: push ecx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4023b8: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4023b9: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4023bfu; native_call(m, 0x4280e0u);	/* 4023ba: call 0x4280e0 */
	{ DWORD a_ = m->esp, b_ = 0xcu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4023bf: add esp, 0xc */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x20u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4023c2: cmp bl, 0x20 */
	if (!m->zf) goto L_4023cc;	/* 4023c5: jne 0x4023cc */
	{ DWORD a_ = m->ebp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4023c7: add ebp, 8 */
	goto L_4023de;	/* 4023ca: jmp 0x4023de */
L_4023cc:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x49u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4023cc: cmp bl, 0x49 */
	if (m->zf) goto L_4023db;	/* 4023cf: je 0x4023db */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x69u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4023d1: cmp bl, 0x69 */
	if (m->zf) goto L_4023db;	/* 4023d4: je 0x4023db */
	{ DWORD a_ = m->ebp, b_ = 0xdu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4023d6: add ebp, 0xd */
	goto L_4023de;	/* 4023d9: jmp 0x4023de */
L_4023db:
	{ DWORD a_ = m->ebp, b_ = 0xbu & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4023db: add ebp, 0xb */
L_4023de:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4023de: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4023e0: test bl, bl */
	if (!m->zf) goto L_402243;	/* 4023e2: jne 0x402243 */
	goto L_4023f4;	/* 4023e8: jmp 0x4023f4 */
L_4023ea:
	M32((DWORD)(0x4d7348u)) = 0x1u;	/* 4023ea: mov dword ptr [0x4d7348], 1 */
L_4023f4:
	m->edx = M32((DWORD)(m->esp + 0x1cu));	/* 4023f4: mov edx, dword ptr [esp + 0x1c] */
	M32((DWORD)(0x4d23c8u)) = m->ebp;	/* 4023f8: mov dword ptr [0x4d23c8], ebp */
	M32((DWORD)(0x4d23ccu)) = m->edx;	/* 4023fe: mov dword ptr [0x4d23cc], edx */
	m->esp -= 4; M32(m->esp) = 0x40240au; native_call(m, M32(0x4a9220u));	/* 402404: call dword ptr [0x4a9220] */
	{ DWORD v_ = 0xde1u; m->esp -= 4; M32(m->esp) = v_; }	/* 40240a: push 0xde1 */
	m->esp -= 4; M32(m->esp) = 0x402415u; native_call(m, M32(0x4a922cu));	/* 40240f: call dword ptr [0x4a922c] */
	m->edi = M32(m->esp); m->esp += 4;	/* 402415: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 402416: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 402417: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 402418: pop ebx */
	m->ecx = M32(m->esp); m->esp += 4;	/* 402419: pop ecx */
	m->esp += 4 + 0; return;	/* 40241a: ret  */
}

/* text_hanCho (0x401870), lifted by tools/lift.py */
static void lift_401870(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401870: sub esp, 8 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 401873: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 401877: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 401878: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 401879: mov ebp, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 40187d: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 40187e: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 40187f: push 7 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 401881: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x40188bu; native_call(m, M32(0x4a921cu));	/* 401885: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x24u));	/* 40188b: mov esi, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 40188f: mov dword ptr [esp + 0x10], 0 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401897: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401899: test bl, bl */
	if (m->zf) goto L_401a90;	/* 40189b: je 0x401a90 */
	m->edi = M32((DWORD)(m->esp + 0x1cu));	/* 4018a1: mov edi, dword ptr [esp + 0x1c] */
L_4018a5:
	m->eax = M32((DWORD)(0x76d3e8u));	/* 4018a5: mov eax, dword ptr [0x76d3e8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4018aa: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4018ab: cmp eax, 0x270f */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4018b0: mov byte ptr [esp + 0x24], bl */
	if (m->zf) goto L_4018bd;	/* 4018b4: je 0x4018bd */
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4018b6: cmp eax, 0x190 */
	if (!m->zf) goto L_401913;	/* 4018bb: jne 0x401913 */
L_4018bd:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4018bd: cmp bl, 0x24 */
	if (!m->zf) goto L_4018e8;	/* 4018c0: jne 0x4018e8 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x23u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4018c2: cmp byte ptr [esi], 0x23 */
	if (!m->zf) goto L_4018e8;	/* 4018c5: jne 0x4018e8 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x2u))) & 0xff) << 0);	/* 4018c7: mov al, byte ptr [esi + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 4018ca: test al, al */
	if (m->zf) goto L_4018e8;	/* 4018cc: je 0x4018e8 */
	m->edi = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 4018ce: movsx edi, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4018d2: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 4018d3: sub edi, 0x30 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4018d6: inc esi */
	M32((DWORD)(m->esp + 0x10u)) = 0x1u;	/* 4018d7: mov dword ptr [esp + 0x10], 1 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 4018df: mov bl, byte ptr [esi] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4018e1: inc esi */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 4018e2: mov byte ptr [esp + 0x24], bl */
	goto L_4018f0;	/* 4018e6: jmp 0x4018f0 */
L_4018e8:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 4018e8: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 4018ec: test eax, eax */
	if (m->zf) goto L_401913;	/* 4018ee: je 0x401913 */
L_4018f0:
	m->eax = m->edi;	/* 4018f0: mov eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 4018f2: shl eax, 4 */
	m->edx = M32((DWORD)(m->eax + 0x9dadacu));	/* 4018f5: mov edx, dword ptr [eax + 0x9dadac] */
	m->ecx = M32((DWORD)(m->eax + 0x9dada8u));	/* 4018fb: mov ecx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401901: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada4u));	/* 401902: mov edx, dword ptr [eax + 0x9dada4] */
	m->eax = M32((DWORD)(m->eax + 0x9dada0u));	/* 401908: mov eax, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40190e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40190f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401910: push eax */
	goto L_40192e;	/* 401911: jmp 0x40192e */
L_401913:
	m->ecx = M32((DWORD)(0x76d444u));	/* 401913: mov ecx, dword ptr [0x76d444] */
	m->edx = M32((DWORD)(0x76d440u));	/* 401919: mov edx, dword ptr [0x76d440] */
	m->eax = M32((DWORD)(0x76d43cu));	/* 40191f: mov eax, dword ptr [0x76d43c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401924: push ecx */
	m->ecx = M32((DWORD)(0x76d438u));	/* 401925: mov ecx, dword ptr [0x76d438] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 40192b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 40192c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 40192d: push ecx */
L_40192e:
	m->esp -= 4; M32(m->esp) = 0x401934u; native_call(m, M32(0x4a9228u));	/* 40192e: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401934: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_4019f6;	/* 40193e: je 0x4019f6 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401944: cmp bl, 0x7c */
	if (!m->zf) goto L_4019f6;	/* 401947: jne 0x4019f6 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 40194d: cmp byte ptr [esi], bl */
	if (m->zf) goto L_401965;	/* 40194f: je 0x401965 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 401951: mov eax, dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 401955: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 401959: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 40195c: mov dword ptr [esp + 0x20], eax */
	goto L_401a86;	/* 401960: jmp 0x401a86 */
L_401965:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x7cu) & 0xff) << 0);	/* 401965: mov bl, 0x7c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401967: inc esi */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401968: mov byte ptr [esp + 0x24], bl */
L_40196c:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4ad490u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40196c: cmp ebp, dword ptr [0x4ad490] */
	if (m->sf != m->of) goto L_401983;	/* 401972: jl 0x401983 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 401974: mov eax, dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 401978: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 40197c: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 40197f: mov dword ptr [esp + 0x20], eax */
L_401983:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 401983: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(0x4ad494u));	/* 401987: mov eax, dword ptr [0x4ad494] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 40198c: cmp ecx, eax */
	if (m->sf == m->of) goto L_401a90;	/* 40198e: jge 0x401a90 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401994: test bl, 0x80 */
	if (m->zf) goto L_401a76;	/* 401997: je 0x401a76 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 40199d: mov al, byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4d23d0u));	/* 40199f: mov ecx, dword ptr [0x4d23d0] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 4019a5: inc esi */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 4019a6: cmp ecx, 1 */
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4019a9: mov byte ptr [esp + 0x14], al */
	if (!m->zf) goto L_4019ca;	/* 4019ad: jne 0x4019ca */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 4019af: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 8)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 8);	/* 4019b1: mov dh, bl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 4019b3: mov dl, al */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4019b5: push edx */
	m->esp -= 4; M32(m->esp) = 0x4019bbu; native_call(m, 0x44aac0u);	/* 4019b6: call 0x44aac0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4019bb: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 4019be: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 4019c0: mov cl, ah */
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 4019c2: mov byte ptr [esp + 0x14], al */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 4019c6: mov byte ptr [esp + 0x24], cl */
L_4019ca:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 4019ca: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 4019ce: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4019d2: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 4019d3: push eax */
	m->esp -= 4; M32(m->esp) = 0x4019d9u; native_call(m, 0x4017d0u);	/* 4019d4: call 0x4017d0 */
	m->ecx = M32((DWORD)(0x4d60e0u));	/* 4019d9: mov ecx, dword ptr [0x4d60e0] */
	m->edx = M32((DWORD)(m->esp + 0x28u));	/* 4019df: mov edx, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 4019e3: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 4019e4: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 4019e5: push ebp */
	m->esp -= 4; M32(m->esp) = 0x4019ebu; native_call(m, 0x427c30u);	/* 4019e6: call 0x427c30 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 4019eb: add esp, 0x14 */
	{ DWORD a_ = m->ebp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 4019ee: add ebp, 0x10 */
	goto L_401a86;	/* 4019f1: jmp 0x401a86 */
L_4019f6:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4019f6: cmp bl, 0x24 */
	if (!m->zf) goto L_401a52;	/* 4019f9: jne 0x401a52 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 4019fb: cmp byte ptr [esi], 0x5b */
	if (!m->zf) goto L_40196c;	/* 4019fe: jne 0x40196c */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x2u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401a04: cmp byte ptr [esi + 2], 0x5d */
	if (!m->zf) goto L_40196c;	/* 401a08: jne 0x40196c */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4u))) & 0xff) << 0);	/* 401a0e: mov al, byte ptr [esi + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401a11: test al, al */
	if (m->zf) goto L_40196c;	/* 401a13: je 0x40196c */
	m->edi = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 401a19: movsx edi, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401a1d: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401a1e: sub edi, 0x30 */
	m->eax = m->edi;	/* 401a21: mov eax, edi */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 401a23: add esi, 3 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 401a26: shl eax, 4 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401a29: mov bl, byte ptr [esi] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401a2b: inc esi */
	m->edx = M32((DWORD)(m->eax + 0x9dadacu));	/* 401a2c: mov edx, dword ptr [eax + 0x9dadac] */
	m->ecx = M32((DWORD)(m->eax + 0x9dada8u));	/* 401a32: mov ecx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401a38: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada4u));	/* 401a39: mov edx, dword ptr [eax + 0x9dada4] */
	m->eax = M32((DWORD)(m->eax + 0x9dada0u));	/* 401a3f: mov eax, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401a45: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401a46: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401a47: push eax */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401a48: mov byte ptr [esp + 0x34], bl */
	m->esp -= 4; M32(m->esp) = 0x401a52u; native_call(m, M32(0x4a9228u));	/* 401a4c: call dword ptr [0x4a9228] */
L_401a52:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401a52: cmp bl, 0xd */
	if (!m->zf) goto L_40196c;	/* 401a55: jne 0x40196c */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0xau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401a5b: cmp byte ptr [esi], 0xa */
	if (!m->zf) goto L_40196c;	/* 401a5e: jne 0x40196c */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 401a64: mov eax, dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 401a68: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401a6c: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 401a6d: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 401a70: mov dword ptr [esp + 0x20], eax */
	goto L_401a86;	/* 401a74: jmp 0x401a86 */
L_401a76:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x20u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401a76: cmp bl, 0x20 */
	if (!m->zf) goto L_401a80;	/* 401a79: jne 0x401a80 */
	{ DWORD a_ = m->ebp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401a7b: add ebp, 8 */
	goto L_401a86;	/* 401a7e: jmp 0x401a86 */
L_401a80:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4d23d8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401a80: add ebp, dword ptr [0x4d23d8] */
L_401a86:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401a86: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401a88: test bl, bl */
	if (!m->zf) goto L_4018a5;	/* 401a8a: jne 0x4018a5 */
L_401a90:
	m->esp -= 4; M32(m->esp) = 0x401a96u; native_call(m, M32(0x4a9220u));	/* 401a90: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 401a96: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 401a97: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 401a98: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 401a99: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401a9a: add esp, 8 */
	m->esp += 4 + 0; return;	/* 401a9d: ret  */
}

/* text_hanJungJong (0x401aa0), lifted by tools/lift.py */
static void lift_401aa0(X86 *m)
{
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401aa0: sub esp, 8 */
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 401aa3: mov eax, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 401aa7: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 401aa8: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x14u));	/* 401aa9: mov ebp, dword ptr [esp + 0x14] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 401aad: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 401aae: push edi */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 401aaf: push 7 */
	M32((DWORD)(m->esp + 0x24u)) = m->eax;	/* 401ab1: mov dword ptr [esp + 0x24], eax */
	m->esp -= 4; M32(m->esp) = 0x401abbu; native_call(m, M32(0x4a921cu));	/* 401ab5: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x24u));	/* 401abb: mov esi, dword ptr [esp + 0x24] */
	M32((DWORD)(m->esp + 0x10u)) = 0x0u;	/* 401abf: mov dword ptr [esp + 0x10], 0 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401ac7: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401ac9: test bl, bl */
	if (m->zf) goto L_401cc7;	/* 401acb: je 0x401cc7 */
	m->edi = M32((DWORD)(m->esp + 0x1cu));	/* 401ad1: mov edi, dword ptr [esp + 0x1c] */
L_401ad5:
	m->eax = M32((DWORD)(0x76d3e8u));	/* 401ad5: mov eax, dword ptr [0x76d3e8] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401ada: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401adb: cmp eax, 0x270f */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401ae0: mov byte ptr [esp + 0x24], bl */
	if (m->zf) goto L_401aed;	/* 401ae4: je 0x401aed */
	{ DWORD a_ = m->eax, b_ = 0x190u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401ae6: cmp eax, 0x190 */
	if (!m->zf) goto L_401b43;	/* 401aeb: jne 0x401b43 */
L_401aed:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401aed: cmp bl, 0x24 */
	if (!m->zf) goto L_401b18;	/* 401af0: jne 0x401b18 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x23u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401af2: cmp byte ptr [esi], 0x23 */
	if (!m->zf) goto L_401b18;	/* 401af5: jne 0x401b18 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x2u))) & 0xff) << 0);	/* 401af7: mov al, byte ptr [esi + 2] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401afa: test al, al */
	if (m->zf) goto L_401b18;	/* 401afc: je 0x401b18 */
	m->edi = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 401afe: movsx edi, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401b02: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401b03: sub edi, 0x30 */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401b06: inc esi */
	M32((DWORD)(m->esp + 0x10u)) = 0x1u;	/* 401b07: mov dword ptr [esp + 0x10], 1 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401b0f: mov bl, byte ptr [esi] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401b11: inc esi */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401b12: mov byte ptr [esp + 0x24], bl */
	goto L_401b20;	/* 401b16: jmp 0x401b20 */
L_401b18:
	m->eax = M32((DWORD)(m->esp + 0x10u));	/* 401b18: mov eax, dword ptr [esp + 0x10] */
	{ DWORD a_ = m->eax, b_ = m->eax & 0xffffffffu, r_ = a_ & b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; }	/* 401b1c: test eax, eax */
	if (m->zf) goto L_401b43;	/* 401b1e: je 0x401b43 */
L_401b20:
	m->eax = m->edi;	/* 401b20: mov eax, edi */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 401b22: shl eax, 4 */
	m->edx = M32((DWORD)(m->eax + 0x9dadacu));	/* 401b25: mov edx, dword ptr [eax + 0x9dadac] */
	m->ecx = M32((DWORD)(m->eax + 0x9dada8u));	/* 401b2b: mov ecx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401b31: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada4u));	/* 401b32: mov edx, dword ptr [eax + 0x9dada4] */
	m->eax = M32((DWORD)(m->eax + 0x9dada0u));	/* 401b38: mov eax, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401b3e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401b3f: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401b40: push eax */
	goto L_401b5e;	/* 401b41: jmp 0x401b5e */
L_401b43:
	m->ecx = M32((DWORD)(0x76d444u));	/* 401b43: mov ecx, dword ptr [0x76d444] */
	m->edx = M32((DWORD)(0x76d440u));	/* 401b49: mov edx, dword ptr [0x76d440] */
	m->eax = M32((DWORD)(0x76d43cu));	/* 401b4f: mov eax, dword ptr [0x76d43c] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401b54: push ecx */
	m->ecx = M32((DWORD)(0x76d438u));	/* 401b55: mov ecx, dword ptr [0x76d438] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401b5b: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401b5c: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401b5d: push ecx */
L_401b5e:
	m->esp -= 4; M32(m->esp) = 0x401b64u; native_call(m, M32(0x4a9228u));	/* 401b5e: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401b64: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_401c2d;	/* 401b6e: je 0x401c2d */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401b74: cmp bl, 0x7c */
	if (!m->zf) goto L_401c2d;	/* 401b77: jne 0x401c2d */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401b7d: cmp byte ptr [esi], bl */
	if (m->zf) goto L_401b95;	/* 401b7f: je 0x401b95 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 401b81: mov eax, dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 401b85: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 401b89: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 401b8c: mov dword ptr [esp + 0x20], eax */
	goto L_401cbd;	/* 401b90: jmp 0x401cbd */
L_401b95:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x7cu) & 0xff) << 0);	/* 401b95: mov bl, 0x7c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401b97: inc esi */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401b98: mov byte ptr [esp + 0x24], bl */
L_401b9c:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4ad490u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401b9c: cmp ebp, dword ptr [0x4ad490] */
	if (m->sf != m->of) goto L_401bb3;	/* 401ba2: jl 0x401bb3 */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 401ba4: mov eax, dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 401ba8: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 401bac: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 401baf: mov dword ptr [esp + 0x20], eax */
L_401bb3:
	m->ecx = M32((DWORD)(m->esp + 0x20u));	/* 401bb3: mov ecx, dword ptr [esp + 0x20] */
	m->eax = M32((DWORD)(0x4ad494u));	/* 401bb7: mov eax, dword ptr [0x4ad494] */
	{ DWORD a_ = m->ecx, b_ = m->eax & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401bbc: cmp ecx, eax */
	if (m->sf == m->of) goto L_401cc7;	/* 401bbe: jge 0x401cc7 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401bc4: test bl, 0x80 */
	if (m->zf) goto L_401cad;	/* 401bc7: je 0x401cad */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401bcd: mov al, byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4d23d0u));	/* 401bcf: mov ecx, dword ptr [0x4d23d0] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401bd5: inc esi */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401bd6: cmp ecx, 1 */
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 401bd9: mov byte ptr [esp + 0x14], al */
	if (!m->zf) goto L_401bfa;	/* 401bdd: jne 0x401bfa */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 401bdf: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 8)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 8);	/* 401be1: mov dh, bl */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 401be3: mov dl, al */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401be5: push edx */
	m->esp -= 4; M32(m->esp) = 0x401bebu; native_call(m, 0x44aac0u);	/* 401be6: call 0x44aac0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401beb: add esp, 4 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 401bee: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 401bf0: mov cl, ah */
	M8((DWORD)(m->esp + 0x14u)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 401bf2: mov byte ptr [esp + 0x14], al */
	M8((DWORD)(m->esp + 0x24u)) = (BYTE)(((m->ecx >> 0) & 0xff));	/* 401bf6: mov byte ptr [esp + 0x24], cl */
L_401bfa:
	m->edx = M32((DWORD)(m->esp + 0x14u));	/* 401bfa: mov edx, dword ptr [esp + 0x14] */
	m->eax = M32((DWORD)(m->esp + 0x24u));	/* 401bfe: mov eax, dword ptr [esp + 0x24] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401c02: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401c03: push eax */
	m->esp -= 4; M32(m->esp) = 0x401c09u; native_call(m, 0x4017d0u);	/* 401c04: call 0x4017d0 */
	m->ecx = M32((DWORD)(0x4d23dcu));	/* 401c09: mov ecx, dword ptr [0x4d23dc] */
	m->edx = M32((DWORD)(0x4d23d4u));	/* 401c0f: mov edx, dword ptr [0x4d23d4] */
	m->eax = M32((DWORD)(m->esp + 0x28u));	/* 401c15: mov eax, dword ptr [esp + 0x28] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401c19: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401c1a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401c1b: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 401c1c: push ebp */
	m->esp -= 4; M32(m->esp) = 0x401c22u; native_call(m, 0x427ce0u);	/* 401c1d: call 0x427ce0 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401c22: add esp, 0x18 */
	{ DWORD a_ = m->ebp, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401c25: add ebp, 0x10 */
	goto L_401cbd;	/* 401c28: jmp 0x401cbd */
L_401c2d:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401c2d: cmp bl, 0x24 */
	if (!m->zf) goto L_401c89;	/* 401c30: jne 0x401c89 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401c32: cmp byte ptr [esi], 0x5b */
	if (!m->zf) goto L_401b9c;	/* 401c35: jne 0x401b9c */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x2u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401c3b: cmp byte ptr [esi + 2], 0x5d */
	if (!m->zf) goto L_401b9c;	/* 401c3f: jne 0x401b9c */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4u))) & 0xff) << 0);	/* 401c45: mov al, byte ptr [esi + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401c48: test al, al */
	if (m->zf) goto L_401b9c;	/* 401c4a: je 0x401b9c */
	m->edi = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 401c50: movsx edi, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401c54: inc esi */
	{ DWORD a_ = m->edi, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401c55: sub edi, 0x30 */
	m->eax = m->edi;	/* 401c58: mov eax, edi */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 401c5a: add esi, 3 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 401c5d: shl eax, 4 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401c60: mov bl, byte ptr [esi] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401c62: inc esi */
	m->edx = M32((DWORD)(m->eax + 0x9dadacu));	/* 401c63: mov edx, dword ptr [eax + 0x9dadac] */
	m->ecx = M32((DWORD)(m->eax + 0x9dada8u));	/* 401c69: mov ecx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401c6f: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada4u));	/* 401c70: mov edx, dword ptr [eax + 0x9dada4] */
	m->eax = M32((DWORD)(m->eax + 0x9dada0u));	/* 401c76: mov eax, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401c7c: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401c7d: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401c7e: push eax */
	M8((DWORD)(m->esp + 0x34u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401c7f: mov byte ptr [esp + 0x34], bl */
	m->esp -= 4; M32(m->esp) = 0x401c89u; native_call(m, M32(0x4a9228u));	/* 401c83: call dword ptr [0x4a9228] */
L_401c89:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401c89: cmp bl, 0xd */
	if (!m->zf) goto L_401b9c;	/* 401c8c: jne 0x401b9c */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0xau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401c92: cmp byte ptr [esi], 0xa */
	if (!m->zf) goto L_401b9c;	/* 401c95: jne 0x401b9c */
	m->eax = M32((DWORD)(m->esp + 0x20u));	/* 401c9b: mov eax, dword ptr [esp + 0x20] */
	m->ebp = M32((DWORD)(m->esp + 0x1cu));	/* 401c9f: mov ebp, dword ptr [esp + 0x1c] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401ca3: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x11u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 401ca4: add eax, 0x11 */
	M32((DWORD)(m->esp + 0x20u)) = m->eax;	/* 401ca7: mov dword ptr [esp + 0x20], eax */
	goto L_401cbd;	/* 401cab: jmp 0x401cbd */
L_401cad:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x20u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401cad: cmp bl, 0x20 */
	if (!m->zf) goto L_401cb7;	/* 401cb0: jne 0x401cb7 */
	{ DWORD a_ = m->ebp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401cb2: add ebp, 8 */
	goto L_401cbd;	/* 401cb5: jmp 0x401cbd */
L_401cb7:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4d23d8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401cb7: add ebp, dword ptr [0x4d23d8] */
L_401cbd:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401cbd: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401cbf: test bl, bl */
	if (!m->zf) goto L_401ad5;	/* 401cc1: jne 0x401ad5 */
L_401cc7:
	m->esp -= 4; M32(m->esp) = 0x401ccdu; native_call(m, M32(0x4a9220u));	/* 401cc7: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 401ccd: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 401cce: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 401ccf: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 401cd0: pop ebx */
	{ DWORD a_ = m->esp, b_ = 0x8u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401cd1: add esp, 8 */
	m->esp += 4 + 0; return;	/* 401cd4: ret  */
}

/* hud_401ce0 (0x401ce0), lifted by tools/lift.py */
static void lift_401ce0(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 401ce0: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 401ce1: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 401ce2: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 401ce6: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 401ce7: push edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 401ce8: mov edi, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 401cec: push 7 */
	m->esp -= 4; M32(m->esp) = 0x401cf4u; native_call(m, M32(0x4a921cu));	/* 401cee: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x1cu));	/* 401cf4: mov esi, dword ptr [esp + 0x1c] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401cf8: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401cfa: test bl, bl */
	if (m->zf) goto L_401e61;	/* 401cfc: je 0x401e61 */
L_401d02:
	m->eax = M32((DWORD)(0x76d444u));	/* 401d02: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 401d07: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 401d0d: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401d13: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 401d14: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401d19: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401d1a: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401d1b: push eax */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401d1c: mov byte ptr [esp + 0x28], bl */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401d20: inc esi */
	m->esp -= 4; M32(m->esp) = 0x401d27u; native_call(m, M32(0x4a9228u));	/* 401d21: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401d27: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_401dd0;	/* 401d31: je 0x401dd0 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401d37: cmp bl, 0x7c */
	if (!m->zf) goto L_401dd0;	/* 401d3a: jne 0x401dd0 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401d40: cmp byte ptr [esi], bl */
	if (m->zf) goto L_401d50;	/* 401d42: je 0x401d50 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 401d44: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401d48: add ebp, 0x21 */
	goto L_401e57;	/* 401d4b: jmp 0x401e57 */
L_401d50:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x7cu) & 0xff) << 0);	/* 401d50: mov bl, 0x7c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401d52: inc esi */
	M8((DWORD)(m->esp + 0x18u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401d53: mov byte ptr [esp + 0x18], bl */
L_401d57:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(0x4ad490u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401d57: cmp edi, dword ptr [0x4ad490] */
	if (m->sf != m->of) goto L_401d66;	/* 401d5d: jl 0x401d66 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 401d5f: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401d63: add ebp, 0x21 */
L_401d66:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4ad494u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401d66: cmp ebp, dword ptr [0x4ad494] */
	if (m->sf == m->of) goto L_401e61;	/* 401d6c: jge 0x401e61 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401d72: test bl, 0x80 */
	if (m->zf) goto L_401e47;	/* 401d75: je 0x401e47 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401d7b: mov al, byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4d23d0u));	/* 401d7d: mov ecx, dword ptr [0x4d23d0] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401d83: inc esi */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401d84: cmp ecx, 1 */
	M8((DWORD)(m->esp + 0x1cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 401d87: mov byte ptr [esp + 0x1c], al */
	if (!m->zf) goto L_401da8;	/* 401d8b: jne 0x401da8 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 401d8d: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 8)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 8);	/* 401d8f: mov ch, bl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 401d91: mov cl, al */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401d93: push ecx */
	m->esp -= 4; M32(m->esp) = 0x401d99u; native_call(m, 0x44aac0u);	/* 401d94: call 0x44aac0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401d99: add esp, 4 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 401d9c: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 401d9e: mov dl, ah */
	M8((DWORD)(m->esp + 0x1cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 401da0: mov byte ptr [esp + 0x1c], al */
	M8((DWORD)(m->esp + 0x18u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 401da4: mov byte ptr [esp + 0x18], dl */
L_401da8:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 401da8: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 401dac: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401db0: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401db1: push ecx */
	m->esp -= 4; M32(m->esp) = 0x401db7u; native_call(m, 0x4017d0u);	/* 401db2: call 0x4017d0 */
	m->edx = M32((DWORD)(0x4d60e0u));	/* 401db7: mov edx, dword ptr [0x4d60e0] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401dbd: push edx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 401dbe: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 401dbf: push edi */
	m->esp -= 4; M32(m->esp) = 0x401dc5u; native_call(m, 0x427e30u);	/* 401dc0: call 0x427e30 */
	{ DWORD a_ = m->esp, b_ = 0x14u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401dc5: add esp, 0x14 */
	{ DWORD a_ = m->edi, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401dc8: add edi, 0x20 */
	goto L_401e57;	/* 401dcb: jmp 0x401e57 */
L_401dd0:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401dd0: cmp bl, 0x24 */
	if (!m->zf) goto L_401e2b;	/* 401dd3: jne 0x401e2b */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401dd5: cmp byte ptr [esi], 0x5b */
	if (!m->zf) goto L_401d57;	/* 401dd8: jne 0x401d57 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x2u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401dde: cmp byte ptr [esi + 2], 0x5d */
	if (!m->zf) goto L_401d57;	/* 401de2: jne 0x401d57 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4u))) & 0xff) << 0);	/* 401de8: mov al, byte ptr [esi + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401deb: test al, al */
	if (m->zf) goto L_401d57;	/* 401ded: je 0x401d57 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 401df3: movsx eax, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401df7: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 401df8: sub eax, 0x30 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 401dfb: shl eax, 4 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x3u))) & 0xff) << 0);	/* 401dfe: mov bl, byte ptr [esi + 3] */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 401e01: add esi, 3 */
	m->ecx = M32((DWORD)(m->eax + 0x9dadacu));	/* 401e04: mov ecx, dword ptr [eax + 0x9dadac] */
	m->edx = M32((DWORD)(m->eax + 0x9dada8u));	/* 401e0a: mov edx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401e10: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x9dada4u));	/* 401e11: mov ecx, dword ptr [eax + 0x9dada4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401e17: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada0u));	/* 401e18: mov edx, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401e1e: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401e1f: push edx */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401e20: mov byte ptr [esp + 0x28], bl */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401e24: inc esi */
	m->esp -= 4; M32(m->esp) = 0x401e2bu; native_call(m, M32(0x4a9228u));	/* 401e25: call dword ptr [0x4a9228] */
L_401e2b:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401e2b: cmp bl, 0xd */
	if (!m->zf) goto L_401d57;	/* 401e2e: jne 0x401d57 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0xau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401e34: cmp byte ptr [esi], 0xa */
	if (!m->zf) goto L_401d57;	/* 401e37: jne 0x401d57 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 401e3d: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401e41: inc esi */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401e42: add ebp, 0x21 */
	goto L_401e57;	/* 401e45: jmp 0x401e57 */
L_401e47:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x20u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401e47: cmp bl, 0x20 */
	if (!m->zf) goto L_401e51;	/* 401e4a: jne 0x401e51 */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401e4c: add edi, 0x10 */
	goto L_401e57;	/* 401e4f: jmp 0x401e57 */
L_401e51:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(0x4d23d8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401e51: add edi, dword ptr [0x4d23d8] */
L_401e57:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401e57: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401e59: test bl, bl */
	if (!m->zf) goto L_401d02;	/* 401e5b: jne 0x401d02 */
L_401e61:
	m->esp -= 4; M32(m->esp) = 0x401e67u; native_call(m, M32(0x4a9220u));	/* 401e61: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 401e67: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 401e68: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 401e69: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 401e6a: pop ebx */
	m->esp += 4 + 0; return;	/* 401e6b: ret  */
}

/* hud_401e70 (0x401e70), lifted by tools/lift.py */
static void lift_401e70(X86 *m)
{
	{ DWORD v_ = m->ebx; m->esp -= 4; M32(m->esp) = v_; }	/* 401e70: push ebx */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 401e71: push ebp */
	m->ebp = M32((DWORD)(m->esp + 0x10u));	/* 401e72: mov ebp, dword ptr [esp + 0x10] */
	{ DWORD v_ = m->esi; m->esp -= 4; M32(m->esp) = v_; }	/* 401e76: push esi */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 401e77: push edi */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 401e78: mov edi, dword ptr [esp + 0x14] */
	{ DWORD v_ = 0x7u; m->esp -= 4; M32(m->esp) = v_; }	/* 401e7c: push 7 */
	m->esp -= 4; M32(m->esp) = 0x401e84u; native_call(m, M32(0x4a921cu));	/* 401e7e: call dword ptr [0x4a921c] */
	m->esi = M32((DWORD)(m->esp + 0x1cu));	/* 401e84: mov esi, dword ptr [esp + 0x1c] */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401e88: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401e8a: test bl, bl */
	if (m->zf) goto L_401ff7;	/* 401e8c: je 0x401ff7 */
L_401e92:
	m->eax = M32((DWORD)(0x76d444u));	/* 401e92: mov eax, dword ptr [0x76d444] */
	m->ecx = M32((DWORD)(0x76d440u));	/* 401e97: mov ecx, dword ptr [0x76d440] */
	m->edx = M32((DWORD)(0x76d43cu));	/* 401e9d: mov edx, dword ptr [0x76d43c] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401ea3: push eax */
	m->eax = M32((DWORD)(0x76d438u));	/* 401ea4: mov eax, dword ptr [0x76d438] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401ea9: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401eaa: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401eab: push eax */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401eac: mov byte ptr [esp + 0x28], bl */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401eb0: inc esi */
	m->esp -= 4; M32(m->esp) = 0x401eb7u; native_call(m, M32(0x4a9228u));	/* 401eb1: call dword ptr [0x4a9228] */
	{ DWORD a_ = M32((DWORD)(0x76d3e8u)), b_ = 0x270fu & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401eb7: cmp dword ptr [0x76d3e8], 0x270f */
	if (m->zf) goto L_401f66;	/* 401ec1: je 0x401f66 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x7cu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401ec7: cmp bl, 0x7c */
	if (!m->zf) goto L_401f66;	/* 401eca: jne 0x401f66 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401ed0: cmp byte ptr [esi], bl */
	if (m->zf) goto L_401ee0;	/* 401ed2: je 0x401ee0 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 401ed4: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401ed8: add ebp, 0x21 */
	goto L_401fed;	/* 401edb: jmp 0x401fed */
L_401ee0:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((0x7cu) & 0xff) << 0);	/* 401ee0: mov bl, 0x7c */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401ee2: inc esi */
	M8((DWORD)(m->esp + 0x18u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401ee3: mov byte ptr [esp + 0x18], bl */
L_401ee7:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(0x4ad490u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401ee7: cmp edi, dword ptr [0x4ad490] */
	if (m->sf != m->of) goto L_401ef6;	/* 401eed: jl 0x401ef6 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 401eef: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401ef3: add ebp, 0x21 */
L_401ef6:
	{ DWORD a_ = m->ebp, b_ = M32((DWORD)(0x4ad494u)) & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401ef6: cmp ebp, dword ptr [0x4ad494] */
	if (m->sf == m->of) goto L_401ff7;	/* 401efc: jge 0x401ff7 */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x80u & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401f02: test bl, 0x80 */
	if (m->zf) goto L_401fdd;	/* 401f05: je 0x401fdd */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401f0b: mov al, byte ptr [esi] */
	m->ecx = M32((DWORD)(0x4d23d0u));	/* 401f0d: mov ecx, dword ptr [0x4d23d0] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401f13: inc esi */
	{ DWORD a_ = m->ecx, b_ = 0x1u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; }	/* 401f14: cmp ecx, 1 */
	M8((DWORD)(m->esp + 0x1cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 401f17: mov byte ptr [esp + 0x1c], al */
	if (!m->zf) goto L_401f38;	/* 401f1b: jne 0x401f38 */
	{ DWORD a_ = m->ecx, b_ = m->ecx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->ecx = r_; }	/* 401f1d: xor ecx, ecx */
	m->ecx = (m->ecx & ~(0xffu << 8)) | (((((m->ebx >> 0) & 0xff)) & 0xff) << 8);	/* 401f1f: mov ch, bl */
	m->ecx = (m->ecx & ~(0xffu << 0)) | (((((m->eax >> 0) & 0xff)) & 0xff) << 0);	/* 401f21: mov cl, al */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401f23: push ecx */
	m->esp -= 4; M32(m->esp) = 0x401f29u; native_call(m, 0x44aac0u);	/* 401f24: call 0x44aac0 */
	{ DWORD a_ = m->esp, b_ = 0x4u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401f29: add esp, 4 */
	{ DWORD a_ = m->edx, b_ = m->edx & 0xffffffffu, r_ = a_ ^ b_; FLAGS(r_, 32); m->cf = 0; m->of = 0; m->edx = r_; }	/* 401f2c: xor edx, edx */
	m->edx = (m->edx & ~(0xffu << 0)) | (((((m->eax >> 8) & 0xff)) & 0xff) << 0);	/* 401f2e: mov dl, ah */
	M8((DWORD)(m->esp + 0x1cu)) = (BYTE)(((m->eax >> 0) & 0xff));	/* 401f30: mov byte ptr [esp + 0x1c], al */
	M8((DWORD)(m->esp + 0x18u)) = (BYTE)(((m->edx >> 0) & 0xff));	/* 401f34: mov byte ptr [esp + 0x18], dl */
L_401f38:
	m->eax = M32((DWORD)(m->esp + 0x1cu));	/* 401f38: mov eax, dword ptr [esp + 0x1c] */
	m->ecx = M32((DWORD)(m->esp + 0x18u));	/* 401f3c: mov ecx, dword ptr [esp + 0x18] */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401f40: push eax */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401f41: push ecx */
	m->esp -= 4; M32(m->esp) = 0x401f47u; native_call(m, 0x4017d0u);	/* 401f42: call 0x4017d0 */
	m->edx = M32((DWORD)(0x4d23dcu));	/* 401f47: mov edx, dword ptr [0x4d23dc] */
	m->eax = M32((DWORD)(0x4d23d4u));	/* 401f4d: mov eax, dword ptr [0x4d23d4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401f52: push edx */
	{ DWORD v_ = m->eax; m->esp -= 4; M32(m->esp) = v_; }	/* 401f53: push eax */
	{ DWORD v_ = m->ebp; m->esp -= 4; M32(m->esp) = v_; }	/* 401f54: push ebp */
	{ DWORD v_ = m->edi; m->esp -= 4; M32(m->esp) = v_; }	/* 401f55: push edi */
	m->esp -= 4; M32(m->esp) = 0x401f5bu; native_call(m, 0x427ee0u);	/* 401f56: call 0x427ee0 */
	{ DWORD a_ = m->esp, b_ = 0x18u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esp = r_; }	/* 401f5b: add esp, 0x18 */
	{ DWORD a_ = m->edi, b_ = 0x20u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401f5e: add edi, 0x20 */
	goto L_401fed;	/* 401f61: jmp 0x401fed */
L_401f66:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x24u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401f66: cmp bl, 0x24 */
	if (!m->zf) goto L_401fc1;	/* 401f69: jne 0x401fc1 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0x5bu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401f6b: cmp byte ptr [esi], 0x5b */
	if (!m->zf) goto L_401ee7;	/* 401f6e: jne 0x401ee7 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x2u)), b_ = 0x5du & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401f74: cmp byte ptr [esi + 2], 0x5d */
	if (!m->zf) goto L_401ee7;	/* 401f78: jne 0x401ee7 */
	m->eax = (m->eax & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x4u))) & 0xff) << 0);	/* 401f7e: mov al, byte ptr [esi + 4] */
	{ DWORD a_ = ((m->eax >> 0) & 0xff), b_ = ((m->eax >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401f81: test al, al */
	if (m->zf) goto L_401ee7;	/* 401f83: je 0x401ee7 */
	m->eax = (DWORD)(int)(signed char)(M8((DWORD)(m->esi + 0x1u)));	/* 401f89: movsx eax, byte ptr [esi + 1] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401f8d: inc esi */
	{ DWORD a_ = m->eax, b_ = 0x30u & 0xffffffffu, r_ = (a_ - b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->eax = r_; }	/* 401f8e: sub eax, 0x30 */
	{ DWORD a_ = m->eax, c_ = (0x4u) & 31; if (c_) { DWORD r_ = (a_ << c_) & 0xffffffffu; m->cf = (int)((a_ >> (32 - c_)) & 1); FLAGS(r_, 32); m->of = 0; m->eax = r_; } }	/* 401f91: shl eax, 4 */
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x3u))) & 0xff) << 0);	/* 401f94: mov bl, byte ptr [esi + 3] */
	{ DWORD a_ = m->esi, b_ = 0x3u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->esi = r_; }	/* 401f97: add esi, 3 */
	m->ecx = M32((DWORD)(m->eax + 0x9dadacu));	/* 401f9a: mov ecx, dword ptr [eax + 0x9dadac] */
	m->edx = M32((DWORD)(m->eax + 0x9dada8u));	/* 401fa0: mov edx, dword ptr [eax + 0x9dada8] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401fa6: push ecx */
	m->ecx = M32((DWORD)(m->eax + 0x9dada4u));	/* 401fa7: mov ecx, dword ptr [eax + 0x9dada4] */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401fad: push edx */
	m->edx = M32((DWORD)(m->eax + 0x9dada0u));	/* 401fae: mov edx, dword ptr [eax + 0x9dada0] */
	{ DWORD v_ = m->ecx; m->esp -= 4; M32(m->esp) = v_; }	/* 401fb4: push ecx */
	{ DWORD v_ = m->edx; m->esp -= 4; M32(m->esp) = v_; }	/* 401fb5: push edx */
	M8((DWORD)(m->esp + 0x28u)) = (BYTE)(((m->ebx >> 0) & 0xff));	/* 401fb6: mov byte ptr [esp + 0x28], bl */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401fba: inc esi */
	m->esp -= 4; M32(m->esp) = 0x401fc1u; native_call(m, M32(0x4a9228u));	/* 401fbb: call dword ptr [0x4a9228] */
L_401fc1:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0xdu & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401fc1: cmp bl, 0xd */
	if (!m->zf) goto L_401ee7;	/* 401fc4: jne 0x401ee7 */
	{ DWORD a_ = M8((DWORD)(m->esi + 0x0u)), b_ = 0xau & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401fca: cmp byte ptr [esi], 0xa */
	if (!m->zf) goto L_401ee7;	/* 401fcd: jne 0x401ee7 */
	m->edi = M32((DWORD)(m->esp + 0x14u));	/* 401fd3: mov edi, dword ptr [esp + 0x14] */
	{ DWORD a_ = m->esi, r_ = (a_ + 1) & 0xffffffffu; FLAGS(r_, 32); m->of = (r_ == 0x80000000u); m->esi = r_; }	/* 401fd7: inc esi */
	{ DWORD a_ = m->ebp, b_ = 0x21u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->ebp = r_; }	/* 401fd8: add ebp, 0x21 */
	goto L_401fed;	/* 401fdb: jmp 0x401fed */
L_401fdd:
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = 0x20u & 0xffu, r_ = (a_ - b_) & 0xffu; FLAGS(r_, 8); m->cf = a_ < b_; m->of = (((a_ ^ b_) & (a_ ^ r_)) >> 7) & 1; }	/* 401fdd: cmp bl, 0x20 */
	if (!m->zf) goto L_401fe7;	/* 401fe0: jne 0x401fe7 */
	{ DWORD a_ = m->edi, b_ = 0x10u & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401fe2: add edi, 0x10 */
	goto L_401fed;	/* 401fe5: jmp 0x401fed */
L_401fe7:
	{ DWORD a_ = m->edi, b_ = M32((DWORD)(0x4d23d8u)) & 0xffffffffu, r_ = (a_ + b_) & 0xffffffffu; FLAGS(r_, 32); m->cf = r_ < a_; m->of = ((~(a_ ^ b_) & (a_ ^ r_)) >> 31) & 1; m->edi = r_; }	/* 401fe7: add edi, dword ptr [0x4d23d8] */
L_401fed:
	m->ebx = (m->ebx & ~(0xffu << 0)) | (((M8((DWORD)(m->esi + 0x0u))) & 0xff) << 0);	/* 401fed: mov bl, byte ptr [esi] */
	{ DWORD a_ = ((m->ebx >> 0) & 0xff), b_ = ((m->ebx >> 0) & 0xff) & 0xffu, r_ = a_ & b_; FLAGS(r_, 8); m->cf = 0; m->of = 0; }	/* 401fef: test bl, bl */
	if (!m->zf) goto L_401e92;	/* 401ff1: jne 0x401e92 */
L_401ff7:
	m->esp -= 4; M32(m->esp) = 0x401ffdu; native_call(m, M32(0x4a9220u));	/* 401ff7: call dword ptr [0x4a9220] */
	m->edi = M32(m->esp); m->esp += 4;	/* 401ffd: pop edi */
	m->esi = M32(m->esp); m->esp += 4;	/* 401ffe: pop esi */
	m->ebp = M32(m->esp); m->esp += 4;	/* 401fff: pop ebp */
	m->ebx = M32(m->esp); m->esp += 4;	/* 402000: pop ebx */
	m->esp += 4 + 0; return;	/* 402001: ret  */
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
